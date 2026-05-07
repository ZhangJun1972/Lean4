/-
Copyright (c) 2026 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Sofia Rodrigues
-/
module

prelude
public import Std.Time
public import Std.Internal.UV.TCP
public import Std.Internal.Async.Timer
public import Std.Internal.Async.Select
public import Std.Internal.SSL

public section

namespace Std.Internal.IO.Async.TCP.SSL

open Std.Internal.SSL
open Std.Internal.UV.TCP
open Std.Net

/--
Default chunk size used by TLS I/O loops.
-/
def ioChunkSize : UInt64 := 16 * 1024

-- ## Private helpers: SSL ↔ TCP I/O bridge

/--
Feeds an encrypted chunk into the SSL input BIO.
Raises an error if OpenSSL consumed fewer bytes than supplied.
-/
@[inline]
private def feedEncryptedChunk (ssl : Session r) (encrypted : ByteArray) : IO Unit := do
  if encrypted.size == 0 then return ()
  let consumed ← ssl.feedEncrypted encrypted
  if consumed.toNat != encrypted.size then
    throw <| IO.userError s!"TLS input short write: consumed {consumed} / {encrypted.size} bytes"

/--
Drains all pending encrypted bytes from the SSL output BIO and sends them over TCP.
-/
private partial def flushEncrypted (native : Socket) (ssl : Session r) : Async Unit := do
  let out ← ssl.drainEncrypted
  if out.size == 0 then return ()
  Async.ofPromise <| native.send #[out]
  flushEncrypted native ssl

/--
Runs the TLS handshake loop to completion, interleaving SSL state machine steps
with TCP I/O.
-/
private partial def doHandshake (native : Socket) (ssl : Session r) (chunkSize : UInt64) : Async Unit := do
  let want ← ssl.handshake
  flushEncrypted native ssl
  match want with
  | none =>
    return ()
  | some .write =>
    doHandshake native ssl chunkSize
  | some .read =>
    let encrypted? ← Async.ofPromise <| native.recv? chunkSize
    match encrypted? with
    | none =>
      throw <| IO.userError "connection closed during TLS handshake"
    | some encrypted =>
      feedEncryptedChunk ssl encrypted
      doHandshake native ssl chunkSize

-- ## Types

/--
Represents a TLS-enabled TCP server socket. Carries its own server context so
that each accepted connection gets a session configured from the same context.
-/
structure Server where
  private ofNative ::
    native : Socket
    serverCtx : Context.Server

/--
Represents a TLS-enabled TCP connection, parameterized by TLS role.
Use `Client` for outgoing connections and `ServerConn` for server-accepted connections.
-/
structure Connection (r : Role) where
  private ofNative ::
    native : Socket
    ssl : Session r

/--
An outgoing TLS client connection.
-/
abbrev Client := Connection .client

/--
An incoming TLS connection accepted by a `Server`.
-/
abbrev ServerConn := Connection .server

namespace Server

/--
Creates a new TLS-enabled TCP server socket using the given context.
-/
@[inline]
def mk (serverCtx : Context.Server) : IO Server := do
  let native ← Socket.new
  return Server.ofNative native serverCtx

/--
Configures the server context with a PEM certificate and private key.
-/
@[inline]
def configureServer (s : Server) (certFile keyFile : String) : IO Unit :=
  s.serverCtx.configure certFile keyFile

/--
Binds the server socket to the specified address.
-/
@[inline]
def bind (s : Server) (addr : SocketAddress) : IO Unit :=
  s.native.bind addr

/--
Listens for incoming connections with the given backlog.
-/
@[inline]
def listen (s : Server) (backlog : UInt32) : IO Unit :=
  s.native.listen backlog

@[inline] private def mkServerConn (native : Socket) (ctx : Context.Server) : IO ServerConn := do
  let ssl ← Session.Server.mk ctx
  return ⟨native, ssl⟩

/--
Accepts an incoming TLS connection and performs the TLS handshake.
-/
@[inline]
def accept (s : Server) (chunkSize : UInt64 := ioChunkSize) : Async ServerConn := do
  let native ← Async.ofPromise <| s.native.accept
  let conn ← mkServerConn native s.serverCtx
  doHandshake conn.native conn.ssl chunkSize
  return conn

/--
Creates a `Selector` that resolves once `s` has a connection available and the TLS handshake
has completed.
-/
def acceptSelector (s : Server) : Selector ServerConn :=
  {
    tryFn := do
      let res ← s.native.tryAccept
      match ← IO.ofExcept res with
      | none => return none
      | some native =>
        let conn ← mkServerConn native s.serverCtx
        doHandshake conn.native conn.ssl ioChunkSize
        return some conn

    registerFn waiter := do
      let connTask ← (do
        let native ← Async.ofPromise <| s.native.accept
        let ssl ← Session.Server.mk s.serverCtx
        let conn : ServerConn := ⟨native, ssl⟩
        doHandshake conn.native conn.ssl ioChunkSize
        return conn
      ).asTask

      -- If we get cancelled the promise will be dropped so prepare for that
      discard <| IO.mapTask (t := connTask) fun res => do
        let lose := return ()
        let win promise := do
          try
            let conn ← IO.ofExcept res
            promise.resolve (.ok conn)
          catch e =>
            promise.resolve (.error e)
        waiter.race lose win

    unregisterFn := s.native.cancelAccept
  }

/--
Gets the local address of the server socket.
-/
@[inline]
def getSockName (s : Server) : IO SocketAddress :=
  s.native.getSockName

/--
Disables the Nagle algorithm for all client sockets accepted by this server socket.
-/
@[inline]
def noDelay (s : Server) : IO Unit :=
  s.native.noDelay

/--
Enables TCP keep-alive for all client sockets accepted by this server socket.
-/
@[inline]
def keepAlive (s : Server) (enable : Bool) (delay : Std.Time.Second.Offset) (_ : delay.val ≥ 1 := by decide) : IO Unit :=
  s.native.keepAlive enable.toInt8 delay.val.toNat.toUInt32

end Server

namespace Connection

/--
Attempts to write plaintext data into TLS. Returns true when accepted.
Any encrypted TLS output generated is flushed to the socket.
-/
@[inline]
def write {r : Role} (s : Connection r) (data : ByteArray) : Async Bool := do
  match ← s.ssl.write data with
  | none =>
    flushEncrypted s.native s.ssl
    return true
  | some _ =>
    -- Data was queued internally; flush whatever the SSL engine produced.
    flushEncrypted s.native s.ssl
    return false

/--
Sends data through a TLS-enabled socket.
Fails if OpenSSL reports the write as pending additional I/O.
-/
@[inline]
def send {r : Role} (s : Connection r) (data : ByteArray) : Async Unit := do
  if ← s.write data then
    return ()
  else
    throw <| IO.userError "TLS write is pending additional I/O; call `recv?` or retry later"

/--
Sends multiple data buffers through the TLS-enabled socket.
-/
@[inline]
def sendAll {r : Role} (s : Connection r) (data : Array ByteArray) : Async Unit :=
  data.forM (s.send ·)

/--
Receives decrypted plaintext data from TLS.
If no plaintext is immediately available, this function performs the required socket I/O
(flush or receive) and retries until data arrives or the connection is closed.
-/
partial def recv? {r : Role} (s : Connection r) (size : UInt64) (chunkSize : UInt64 := ioChunkSize) : Async (Option ByteArray) := do
  match ← s.ssl.read? size with
  | .data plain =>
    flushEncrypted s.native s.ssl
    return some plain
  | .closed =>
    return none
  | .wantIO _ =>
    flushEncrypted s.native s.ssl
    let encrypted? ← Async.ofPromise <| s.native.recv? chunkSize
    match encrypted? with
    | none =>
      return none
    | some encrypted =>
      feedEncryptedChunk s.ssl encrypted
      recv? s size chunkSize

/--
Tries to receive decrypted plaintext data without blocking.
Returns `some (some data)` if plaintext is available, `some none` if the peer closed,
or `none` if no data is ready yet.
-/
partial def tryRecv {r : Role} (s : Connection r) (size : UInt64) (chunkSize : UInt64 := ioChunkSize) : Async (Option (Option ByteArray)) := do
  let pending ← s.ssl.pendingPlaintext

  if pending > 0 then
    return some (← s.recv? size)
  else
    let readableWaiter ← s.native.waitReadable

    flushEncrypted s.native s.ssl

    if ← readableWaiter.isResolved then
      let encrypted? ← Async.ofPromise <| s.native.recv? ioChunkSize
      match encrypted? with
      | none =>
        return none
      | some encrypted =>
        feedEncryptedChunk s.ssl encrypted
        tryRecv s size chunkSize
    else
      s.native.cancelRecv
      return none

/--
Feeds encrypted socket data into SSL until plaintext is pending.
Resolves the returned promise once plaintext is available.
-/
partial def waitReadable {r : Role} (s : Connection r) : Async Unit := do
  flushEncrypted s.native s.ssl

  let pending ← s.ssl.pendingPlaintext
  if pending > 0 then
    return ()

  if (← s.ssl.pendingPlaintext) > 0 then
    return ()

  match ← s.ssl.read? 0 with
  | .data _ =>
    flushEncrypted s.native s.ssl
    return ()
  | .closed =>
    return ()
  | .wantIO _ =>
    flushEncrypted s.native s.ssl
    let encrypted? ← Async.ofPromise <| s.native.recv? ioChunkSize
    match encrypted? with
    | none => return ()
    | some encrypted =>
      feedEncryptedChunk s.ssl encrypted
      waitReadable s

/--
Creates a `Selector` that resolves once `s` has plaintext data available.
-/
def recvSelector {r : Role} (s : Connection r) (size : UInt64) : Selector (Option ByteArray) :=
  {
    tryFn := s.tryRecv size

    registerFn waiter := do
      let readableWaiter ← s.waitReadable.asTask

      -- If we get cancelled the promise will be dropped so prepare for that
      discard <| IO.mapTask (t := readableWaiter) fun res => do
        match res with
        | .error _ => return ()
        | .ok _ =>
          let lose := return ()
          let win promise := do
            try
              -- We know that this read should not block.
              let result ← (s.recv? size).block
              promise.resolve (.ok result)
            catch e =>
              promise.resolve (.error e)
          waiter.race lose win

    unregisterFn := s.native.cancelRecv
  }

/--
Shuts down the write side of the socket.
-/
@[inline]
def shutdown {r : Role} (s : Connection r) : Async Unit :=
  Async.ofPromise <| s.native.shutdown

/--
Gets the remote address of the socket.
-/
@[inline]
def getPeerName {r : Role} (s : Connection r) : IO SocketAddress :=
  s.native.getPeerName

/--
Gets the local address of the socket.
-/
@[inline]
def getSockName {r : Role} (s : Connection r) : IO SocketAddress :=
  s.native.getSockName

/--
Returns the X.509 verification result code for this TLS session.
-/
@[inline]
def verifyResult {r : Role} (s : Connection r) : IO UInt64 :=
  s.ssl.verifyResult

/--
Disables the Nagle algorithm for the socket.
-/
@[inline]
def noDelay {r : Role} (s : Connection r) : IO Unit :=
  s.native.noDelay

/--
Enables TCP keep-alive with a specified delay for the socket.
-/
@[inline]
def keepAlive {r : Role} (s : Connection r) (enable : Bool) (delay : Std.Time.Second.Offset) (_ : delay.val ≥ 0 := by decide) : IO Unit :=
  s.native.keepAlive enable.toInt8 delay.val.toNat.toUInt32

end Connection

-- ## Client (outgoing connection setup)

namespace Client

/--
Creates a new outgoing TLS client connection using the given client context.
-/
@[inline]
def mk (ctx : Context.Client) : IO Client := do
  let native ← Socket.new
  let ssl ← Session.Client.mk ctx
  return ⟨native, ssl⟩

/--
Configures the given client context.
`caFile` may be empty to use default trust settings.
-/
@[inline]
def configureContext (ctx : Context.Client) (caFile := "") (verifyPeer := true) : IO Unit :=
  ctx.configure caFile verifyPeer

/--
Binds the client socket to the specified address.
-/
@[inline]
def bind (s : Client) (addr : SocketAddress) : IO Unit :=
  s.native.bind addr

/--
Sets SNI server name used during the TLS handshake.
-/
@[inline]
def setServerName (s : Client) (host : String) : IO Unit :=
  Session.Client.setServerName s.ssl host

/--
Performs the TLS handshake on an established TCP connection.
-/
@[inline]
def handshake (s : Client) (chunkSize : UInt64 := ioChunkSize) : Async Unit :=
  doHandshake (Connection.native s) (Connection.ssl s) chunkSize

/--
Connects the client socket to the given address and performs the TLS handshake.
-/
@[inline]
def connect (s : Client) (addr : SocketAddress) (chunkSize : UInt64 := ioChunkSize) : Async Unit := do
  Async.ofPromise <| (Connection.native s).connect addr
  s.handshake chunkSize

end Std.Internal.IO.Async.TCP.SSL.Client
