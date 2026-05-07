/-
Copyright (c) 2026 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Sofia Rodrigues
-/
module

prelude
public import Std.Internal.SSL.Context

public section

namespace Std.Internal.SSL

private opaque SessionImpl : Role → NonemptyType.{0}

/--
Indicates what kind of socket I/O OpenSSL needs before the current operation can proceed.
-/
inductive IOWant where

  /--
  OpenSSL needs more encrypted bytes from the socket (`SSL_ERROR_WANT_READ`).
  -/
  | read

  /--
  OpenSSL needs to flush encrypted bytes to the socket (`SSL_ERROR_WANT_WRITE`).
  -/
  | write

/--
Result of a `Session.read?` call.
-/
inductive ReadResult where

  /--
  Plaintext data was successfully decrypted.
  -/
  | data (bytes : ByteArray)

  /--
  OpenSSL needs socket I/O before it can produce plaintext.
  -/
  | wantIO (want : IOWant)

  /--
  The peer closed the TLS session cleanly (`SSL_ERROR_ZERO_RETURN`).
  -/
  | closed

/--
Represents an OpenSSL SSL session parameterized by role.
Use `Session.Server` or `Session.Client` for the concrete aliases.
-/
def Session (r : Role) : Type := (SessionImpl r).type

/--
Server-side TLS session.
-/
abbrev Session.Server := Session .server

/--
Client-side TLS session.
-/
abbrev Session.Client := Session .client

instance (r : Role) : Nonempty (Session r) := (SessionImpl r).property

namespace Session

namespace Server

/--
Creates a new server-side SSL session from the given context.
-/
@[extern "lean_uv_ssl_mk_server"]
opaque mk (ctx : @& Context.Server) : IO Session.Server

end Server

namespace Client

/--
Creates a new client-side SSL session from the given context.
-/
@[extern "lean_uv_ssl_mk_client"]
opaque mk (ctx : @& Context.Client) : IO Session.Client

/--
Sets the SNI host name for client-side handshakes.
-/
@[extern "lean_uv_ssl_set_server_name"]
opaque setServerName (ssl : @& Session.Client) (host : @& String) : IO Unit

end Client

/--
Gets the X.509 verify result code after handshake.
-/
@[extern "lean_uv_ssl_verify_result"]
opaque verifyResult {r : Role} (ssl : @& Session r) : IO UInt64

/--
Runs one handshake step.
Returns `none` when the handshake is complete, or `some w` when OpenSSL needs socket I/O of
kind `w` before the handshake can proceed.
-/
@[extern "lean_uv_ssl_handshake"]
opaque handshake {r : Role} (ssl : @& Session r) : IO (Option IOWant)

/--
Attempts to write plaintext application data into SSL.
Returns `none` when the data was accepted, or `some w` when OpenSSL needs socket I/O of kind
`w` before the write can complete (the data is queued internally and retried after the next read).
-/
@[extern "lean_uv_ssl_write"]
opaque write {r : Role} (ssl : @& Session r) (data : @& ByteArray) : IO (Option IOWant)

/--
Attempts to read decrypted plaintext data.
-/
@[extern "lean_uv_ssl_read"]
opaque read? {r : Role} (ssl : @& Session r) (maxBytes : UInt64) : IO ReadResult

/--
Feeds encrypted TLS bytes into the SSL input BIO.
-/
@[extern "lean_uv_ssl_feed_encrypted"]
opaque feedEncrypted {r : Role} (ssl : @& Session r) (data : @& ByteArray) : IO UInt64

/--
Drains encrypted TLS bytes from the SSL output BIO.
-/
@[extern "lean_uv_ssl_drain_encrypted"]
opaque drainEncrypted {r : Role} (ssl : @& Session r) : IO ByteArray

/--
Returns the amount of encrypted TLS bytes currently pending in the output BIO.
-/
@[extern "lean_uv_ssl_pending_encrypted"]
opaque pendingEncrypted {r : Role} (ssl : @& Session r) : IO UInt64

/--
Returns the amount of decrypted plaintext bytes currently buffered inside the SSL object.
-/
@[extern "lean_uv_ssl_pending_plaintext"]
opaque pendingPlaintext {r : Role} (ssl : @& Session r) : IO UInt64

end Session

end Std.Internal.SSL
