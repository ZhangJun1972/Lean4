/-
Copyright (c) 2026 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Sofia Rodrigues
-/
module

prelude
public import Std.Internal.Http.Client.Agent
import Std.Internal.Async.DNS
import Std.Data.HashMap
import Init.Data.Array

public section

namespace Std
namespace Http
namespace Client

set_option linter.all true

open Std Internal IO Async TCP Protocol
open Time

/-!
# Agent.Pool

A connection pool that maintains multiple reusable sessions per `(host, port)` pair,
enabling parallel request pipelines to the same host.

Use `Pool.new` to create a pool with a shared configuration and cookie jar, then call
`pool.send` to dispatch requests through managed sessions.

```lean
let pool ← Agent.Pool.new (maxPerHost := 4)

-- requests are distributed across up to 4 connections per host
let r1 ← pool.send "api.example.com" 80
  (Request.get (.originForm! "/a") |>.header! "Host" "api.example.com" |>.empty)
```
-/

/--
Resolves `host` via DNS, opens a TCP socket to `port`, and creates an HTTP session.
When `config.proxy` is set the TCP connection is made to the proxy address instead.
-/
private def createTcpSession (host : URI.Host) (port : UInt16) (config : Config) : Async (Session Socket.Client) := do
  let (connectHost, connectPort) := config.proxy.getD (toString host, port)
  let addrs ← DNS.getAddrInfo connectHost (toString connectPort)

  if addrs.isEmpty then
    throw (IO.userError s!"could not resolve host: {connectHost.quote}")

  -- Try each resolved address in order; return on first successful connect.
  -- This handles hosts that resolve to both IPv6 (::1) and IPv4 (127.0.0.1).
  let mut lastErr : IO.Error := IO.userError s!"could not connect to {connectHost.quote}:{connectPort}"

  for ipAddr in addrs do
    let socketAddr : Std.Net.SocketAddress := match ipAddr with
      | .v4 ip => .v4 ⟨ip, connectPort⟩
      | .v6 ip => .v6 ⟨ip, connectPort⟩
    try
      let socket ← Socket.Client.mk
      socket.connect socketAddr
      return ← Session.new socket config
    catch err =>
      lastErr := err

  throw lastErr

/--
Per-origin bucket inside the pool's state map.
-/
structure Agent.Pool.Entry where
  /--
  Sessions that have been explicitly returned (via `releaseHealthy` after a
  cross-origin redirect) and are ready for immediate reuse.
  -/
  idle : Array (Session Socket.Client)
  /--
  All registered sessions for this origin, including both idle and in-use ones.
  Used to enforce `maxPerHost` and for round-robin when all sessions are busy.
  -/
  all : Array (Session Socket.Client)
  /--
  Monotonically advancing round-robin index over `all`.
  -/
  idx : Nat

/--
A connection pool that manages multiple sessions per `(scheme, host, port)` triple.
-/
structure Agent.Pool where
  /--
  Per-origin buckets guarded by a mutex.
  The key is `(scheme, host, port)` so that `http://example.com:443` and
  `https://example.com:443` are never mixed in the same pool.
  -/
  state : Mutex (Std.HashMap (String × String × UInt16) Agent.Pool.Entry)

  /--
  Maximum number of sessions (connections) per host.
  -/
  maxPerHost : Nat

  /--
  Configuration used when creating new sessions.
  -/
  config : Config

  /--
  Cookie jar shared across all sessions in the pool.
  -/
  cookieJar : Cookie.Jar

  /--
  Monotonically increasing counter used to assign unique IDs to pooled sessions.
  -/
  nextId : Mutex UInt64

  /--
  Response interceptors applied (in order) after every response from any session in the pool.
  -/
  interceptors : Array (Response Body.Stream → Async (Response Body.Stream)) := #[]

namespace Agent.Pool

/--
Creates a new, empty connection pool.
-/
def new (config : Config := {}) (maxPerHost : Nat := 4) : Async Agent.Pool := do
  let state ← Mutex.new (∅ : Std.HashMap (String × String × UInt16) Agent.Pool.Entry)
  let cookieJar ← Cookie.Jar.new
  let nextId ← Mutex.new (1 : UInt64)
  pure { state, maxPerHost, config, cookieJar, nextId }

/--
Returns a session for `(scheme, host, port)`.

Priority order:
1. An idle session (returned by `releaseHealthy` after a cross-origin redirect) —
   reuses the existing connection without a new TCP handshake.
2. A new session when the pool is under `maxPerHost` — grows the pool for
   parallel requests.
3. Round-robin among all registered sessions when at capacity.

The scheme is part of the key so that `http://example.com:443` and
`https://example.com:443` never share a pool entry.
-/
def getOrCreateSession (pool : Agent.Pool) (scheme : URI.Scheme) (host : URI.Host) (port : UInt16) : Async (Session Socket.Client) := do
  let key := (scheme.val, toString host, port)

  let maybeSession ← pool.state.atomically do
    let st ← MonadState.get
    let entry := (st.get? key).getD ⟨#[], #[], 0⟩

    -- Priority 1: reuse an idle session if one was returned to the pool.
    if let some s := entry.idle[0]? then
      let entry' := { entry with idle := entry.idle.extract 1 entry.idle.size, idx := entry.idx + 1 }
      MonadState.set (st.insert key entry')
      return some s

    -- Priority 2: pool under capacity — fall through to create a new session.
    if entry.all.size < pool.maxPerHost then
      return none

    -- Priority 3: at capacity — round-robin among all registered sessions.
    match entry.all[entry.idx % entry.all.size]? with
    | none => return none
    | some selected =>
      MonadState.set (st.insert key { entry with idx := entry.idx + 1 })
      return some selected

  if let some session := maybeSession then
    return session

  -- Slow path: create a new session and register it in `all`.
  let session ← createTcpSession host port pool.config

  let newId ← pool.nextId.atomically do
    let id ← MonadState.get
    MonadState.set (id + 1)
    return id
  let session := { session with id := newId }
  pool.state.atomically do
    let st ← MonadState.get
    let entry := (st.get? key).getD ⟨#[], #[], 0⟩
    -- Respect maxPerHost: only register if still under the limit.
    if entry.all.size < pool.maxPerHost then
      MonadState.set (st.insert key { entry with all := entry.all.push session })
    -- If over the limit (concurrent creation race), the session is still
    -- returned for the current request but not stored for future reuse.
  return session

/--
Removes a single broken session from the pool by its unique ID, from both the
`all` and `idle` lists.  Healthy sibling sessions to the same origin are preserved.
-/
private def evictSession (pool : Agent.Pool) (scheme : URI.Scheme) (host : URI.Host) (port : UInt16) (sessionId : UInt64) : Async Unit := do
  let key := (scheme.val, toString host, port)
  pool.state.atomically do
    let st ← MonadState.get
    match st.get? key with
    | none => pure ()
    | some entry =>
      let entry' := { entry with
        all  := entry.all.filter  (fun s => s.id != sessionId)
        idle := entry.idle.filter (fun s => s.id != sessionId) }
      MonadState.set (st.insert key entry')

/--
Returns a healthy session to the idle list for its origin so it can be
reused by the next `getOrCreateSession` call for the same host.
Called by the pool transport's `releaseHealthy` after a cross-origin redirect
replaces this session with one for the new origin.
-/
private def returnToIdle (pool : Agent.Pool) (scheme : URI.Scheme) (host : URI.Host) (port : UInt16) (session : Session Socket.Client) : Async Unit := do
  let key := (scheme.val, toString host, port)
  pool.state.atomically do
    let st ← MonadState.get
    let entry := (st.get? key).getD ⟨#[], #[], 0⟩
    -- Only add to idle if the session is still registered (not already evicted).
    if entry.all.any (fun s => s.id == session.id) then
      MonadState.set (st.insert key { entry with idle := entry.idle.push session })

/--
Sends a request through a pooled session for `(scheme, host, port)`, injecting cookies from the
shared jar, applying response interceptors, storing any `Set-Cookie` responses, following
redirects up to `config.maxRedirects` hops, and evicting dead sessions on connection
failure (retrying up to `config.maxRetries` times).
-/
def send {β : Type} [Coe β Body.Any]
    (pool : Agent.Pool) (host : URI.Host) (port : UInt16) (scheme : URI.Scheme)
    (request : Request β) : Async (Response Body.Stream) := do

  let session ← pool.getOrCreateSession scheme host port

  Agent.send {
    session
    scheme := scheme
    host := host
    port := port
    cookieJar := pool.cookieJar
    interceptors := pool.interceptors
    transport := some {
      acquire := fun s h p => pool.getOrCreateSession s h p
      release := fun broken s h p => pool.evictSession s h p broken.id
      releaseHealthy := fun session s h p => pool.returnToIdle s h p session
    }
  } request

end Agent.Pool

namespace Agent

/--q  q
Resolves `host` via DNS and establishes a TCP connection on `port`, returning a new
`Agent Socket.Client`. Throws if DNS resolution returns no addresses.

When `config.proxy` is set every connection (including cross-host redirects) is routed
through the proxy.
-/
def connect (host : URI.Host) (port : UInt16) (config : Config := {}) : Async (Agent Socket.Client) := do
  let session ← createTcpSession host port config
  let cookieJar ← Cookie.Jar.new
  let scheme := URI.Scheme.ofPort port
  pure { session, scheme, host, port, cookieJar
         transport := some {
           acquire := fun _scheme h p => createTcpSession h p config
           release := fun s _ _ _ => discard <| s.close } }

end Std.Http.Client.Agent
