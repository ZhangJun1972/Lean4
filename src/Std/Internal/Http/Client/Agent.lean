/-
Copyright (c) 2026 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Sofia Rodrigues
-/
module

prelude
public import Std.Internal.Http.Client.Session
public import Std.Internal.Http.Data.Cookie
import Init.Data.Array

public section

namespace Std
namespace Http
namespace Client

set_option linter.all true

open Std Internal IO Async TCP Protocol
open Time

/-!
# Agent

This module defines `Client.Agent`, a transport-agnostic HTTP user-agent that wraps a `Session`
and adds automatic redirect following, cookie jar support, response interceptors, and configurable
retries.

`Agent` is parameterized by the transport type `α` and contains no TCP-specific code.
Use `Agent.ofTransport` to create an `Agent` from any connected transport. Pass an
`Agent.Connector` to enable cross-host redirect following and automatic reconnection on error.

On each redirect the `Location` header is parsed as a URI. If the redirect targets a different
host or port the agent closes the current session and opens a new one via the connector (when
available). A `Array URI` tracks every URI visited in the current redirect chain so that cycles
are detected and broken immediately.

When crossing to a different host the `Authorization` header is stripped from the redirected
request to prevent credential leakage.
-/

/--
Paired session-lifecycle hooks used by an `Agent` to reconnect after a connection
error and to dispose of a broken session.

A pool provides an `acquire` that picks or creates a session for the target
origin and a `release` that evicts the broken one.  A standalone agent can pass
`none` to disable both (no retry on connection error, no cross-origin redirect).
-/
structure Agent.Connector (α : Type) where
  /--
  Open a session for the given origin.  Used for automatic retry after a
  connection error (same origin) and for cross-origin redirects (new origin).
  -/
  acquire : URI.Scheme → URI.Host → UInt16 → Async (Session α)

  /--
  Dispose of a session whose `send` has just failed, identifying it by its
  origin.  For pool transports this evicts the session from the pool; for
  standalone transports it closes the session's request channel.
  -/
  release : Session α → URI.Scheme → URI.Host → UInt16 → Async Unit

  /--
  Called when a cross-origin redirect replaces the current session with a new one,
  passing the origin that session belongs to.
  The default closes the replaced session, which is correct for standalone (non-pool)
  transports.  Pool transports override this to return the session to the idle list
  for its origin so it can be reused by future requests to the same host.
  -/
  releaseHealthy : Session α → URI.Scheme → URI.Host → UInt16 → Async Unit :=
    fun s _ _ _ => discard <| s.close

/--
An HTTP user-agent that manages a connection to a host. It follows redirects, maintains a cookie
jar for automatic cookie handling, applies response interceptors, and retries on connection errors.
-/
structure Agent (α : Type) where
  /--
  The underlying HTTP session over the transport.
  -/
  session : Session α

  /--
  URI scheme for this connection (e.g., `"http"` or `"https"`).
  Used when constructing absolute-form request URIs for proxy requests and some redirects.
  -/
  scheme : URI.Scheme

  /--
  The hostname this agent is currently connected to.
  -/
  host : URI.Host

  /--
  The port this agent is currently connected to.
  -/
  port : UInt16

  /--
  Cookie jar shared across all requests and redirects through this agent.
  -/
  cookieJar : Cookie.Jar

  /--
  Response interceptors applied (in order) after every response, including intermediate
  redirect responses.  Each interceptor receives the response and returns a (possibly
  modified) response.  Interceptors run before cookie processing and redirect evaluation
  so they can, e.g., unwrap envelopes or transparently decompress bodies.
  -/
  interceptors : Array (Response Body.Stream → Async (Response Body.Stream)) := #[]

  /--
  Session-lifecycle hooks used for automatic reconnection on connection error
  (`maxRetries`) and for cross-origin redirect following.  `none` disables both.
  -/
  transport : Option (Agent.Connector α) := none

namespace Agent

/--
The default broken-session disposal: just close the session's request channel.
Used when an `Agent` has no `transport` — i.e. no pool to evict from.
-/
private def defaultRelease (session : Session α) : Async Unit :=
  discard <| session.close

/--
Creates an `Agent` from an already-connected transport `socket`.
Pass a `transport` to enable automatic reconnection on error and cross-host redirect
following; omit it (or pass `none`) to disable both.
-/
def ofTransport [Transport α] (socket : α) (scheme : URI.Scheme)
    (host : URI.Host) (port : UInt16)
    (transport : Option (Agent.Connector α) := none)
    (config : Config := {}) : Async (Agent α) := do

  let session ← Session.new socket config
  let cookieJar ← Cookie.Jar.new
  pure { session, scheme, host, port, cookieJar, transport }

/--
Injects matching cookies from `cookieJar` into the request headers for `host`.
Does nothing if the jar contains no matching cookies.
-/
def injectCookies (cookieJar : Cookie.Jar) (host : URI.Host) (scheme : URI.Scheme)
    (request : Request Body.Any) : Async (Request Body.Any) := do

  -- Respect an explicit Cookie header set by the caller.
  if request.line.headers.contains .cookie then return request

  let path := RequestTarget.pathOrRoot request.line.uri

  match ← cookieJar.cookiesFor host path (secure := scheme.val == "https") with
  | none => return request
  | some cookieValue =>
    let newHeaders := request.line.headers.insert .cookie cookieValue
    return { request with line := { request.line with headers := newHeaders } }

/--
Reads all `Set-Cookie` headers from `responseHeaders` and stores the cookies in
`cookieJar`, using `requestPath` to compute RFC 6265 default-path semantics
when a cookie omits `Path=`.
-/
def processCookies (cookieJar : Cookie.Jar) (host : URI.Host)
    (requestPath : URI.Path) (responseHeaders : Headers) : IO Unit := do
  if let some values := responseHeaders.getAll? Header.Name.setCookie then
    for v in values do
      cookieJar.processSetCookie host requestPath v.value

/--
Applies all response interceptors to `response` in order, returning the final result.
-/
def applyInterceptors
    (interceptors : Array (Response Body.Stream → Async (Response Body.Stream)))
    (response : Response Body.Stream) : Async (Response Body.Stream) :=
  interceptors.foldlM (init := response) (fun r f => f r)

/--
Drains the response body up to `drainLimit` bytes so the underlying connection
can be reused. Failures are swallowed after closing the body.
-/
private def drainBodyForReuse (response : Response Body.Stream) (drainLimit : Nat) : Async Unit := do
  discard <| ContextAsync.run do
    try
      discard <| response.body.readAll (α := ByteArray) (maximumSize := some drainLimit.toUInt64)
    catch _ =>
      response.body.close

/--
Marks `response` as an internally-drained body so the connection loop applies
`redirectBodyDrainLimit` instead of the caller-facing `maxResponseBodySize`.
Must be called before `drainBodyForReuse` whenever the agent discards a response
body internally (redirect follows and `validateStatus` rejections).
-/
private def markRedirectDrain (response : Response Body.Stream) : BaseIO Unit := do
  if let some control := response.extensions.get ResponseBodyControl then
    ResponseBodyControl.markRedirectDrain control

/--
Builds the redirected request from a `RedirectPlan`. For `.replay` body actions
the original body is reset in place; for `.empty` actions a fresh empty body is
attached. Does not drain the redirect response body — the caller must do that
once it has decided the redirect will actually be followed.
-/
private def followRedirect (plan : Std.Http.RedirectPlan)
    (request : Request Body.Any) : Async (Request Body.Any) := do
  let newBody : Body.Any ← match plan.bodyAction with
    | .empty =>
      pure (Body.Any.ofBody Body.Empty.mk)
    | .replay => do
      request.body.resetInPlace
      pure request.body
  return {
    line := { request.line with
      uri := plan.target
      method := plan.method
      headers := plan.headers }
    body := newBody
    extensions := request.extensions
  }

/--
Rewrites `request` to absolute-form when the agent is configured to use a proxy.
No-op otherwise.
-/
private def rewriteForProxy (agent : Agent α)
    (request : Request Body.Any) : Request Body.Any :=
  if agent.session.config.proxy.isSome then
    request.toAbsoluteForm agent.scheme agent.host agent.port
  else
    request

/--
A single HTTP round-trip on `agent.session`: inject cookies, send, apply
interceptors, then harvest any `Set-Cookie` into the cookie jar.  Returns the
response with headers already resolved; the body continues to stream lazily.
-/
private def dispatchHop [Transport α] (agent : Agent α)
    (request : Request Body.Any) : Async (Response Body.Stream) := do
  let request ← injectCookies agent.cookieJar agent.host agent.scheme request
  let response ← agent.session.send request
  let response ← applyInterceptors agent.interceptors response
  processCookies agent.cookieJar agent.host (RequestTarget.pathOrRoot request.line.uri) response.line.headers
  return response

/--
Computes the exponential-backoff delay for the `n`-th retry (0-indexed).  Caps
the result at 32 seconds regardless of configured base.
-/
private def retryDelayFor (cfg : Config) (attempt : Nat) : Time.Millisecond.Offset :=
  ⟨min (cfg.retryDelay.val * (2 : Int) ^ attempt) 32000⟩

/--
Dispatches `request` through `agent`, retrying up to `retriesLeft` times on
connection failure.  On error the broken session is disposed of via the
connector (pool evicts, standalone closes); retry only runs for idempotent
methods with a replayable body and a configured connector.

Returns the (possibly reconnected) agent alongside the response so the caller
can continue with the latest session.
-/
private partial def attemptWithRetry [Transport α] (agent : Agent α)
    (request : Request Body.Any) (retriesLeft : Nat)
    : Async (Agent α × Response Body.Stream) := do
  try
    let response ← dispatchHop agent request
    return (agent, response)
  catch err => do
    -- Dispose of the broken session (pool evicts; standalone closes).
    match agent.transport with
    | some t => t.release agent.session agent.scheme agent.host agent.port
    | none => defaultRelease agent.session

    -- Refuse to retry when the body is non-replayable (e.g. `Body.Stream`):
    -- re-sending would silently ship a partial or empty payload, masking the
    -- connection failure.
    if retriesLeft > 0 && request.line.method.isIdempotent && request.body.isReplayable then
      if let some connector := agent.transport then
        let attempt := agent.session.config.maxRetries - retriesLeft
        sleep (retryDelayFor agent.session.config attempt)
        request.body.resetInPlace
        let newSession ← connector.acquire agent.scheme agent.host agent.port
        return ← attemptWithRetry { agent with session := newSession } request (retriesLeft - 1)
    throw err

/--
Outcome of evaluating a response for redirect follow-up.  All four gates
(remaining hops, redirect policy, cycle detection, connector presence for
cross-origin) are decided here; the caller drains and follows only when the
decision is `.follow`.
-/
private inductive RedirectStep where
  /-- Not a redirectable response; run `validateStatus` and return. -/
  | final
  /-- A redirect was available but a gate blocked it; return the 3xx as-is. -/
  | stop
  /-- All gates passed; drain the body and follow `plan`. -/
  | follow (plan : Std.Http.RedirectPlan) (isCrossOrigin : Bool)

/--
Pure-in-the-caller evaluation of the redirect gates (relies on `Id.run` for
early return only).  Never touches the network or the cookie jar.
-/
private def evaluateRedirect (agent : Agent α) (request : Request Body.Any)
    (response : Response Body.Stream) (remaining : Nat)
    (history : Array (URI.Host × UInt16 × String)) : RedirectStep := Id.run do
  match Std.Http.decideRedirect remaining agent.host agent.port agent.scheme
      request.line request.body.isReplayable response.line.status response.line.headers with
  | .done => return .final
  | .follow plan =>
    -- Gate 1: caller-supplied redirect policy.
    if let some policy := agent.session.config.redirectPolicy then
      if !policy plan.host plan.port then return .stop

    -- Gate 2: cycle detection.
    let nextKey := (plan.host, plan.port, toString plan.target)
    if history.contains nextKey then return .stop

    -- Gate 3: cross-origin redirects need a connector (scheme change on the
    -- same host+port still counts — http↔https needs a fresh transport
    -- because the TLS handshake differs).
    let isCrossOrigin :=
      plan.host != agent.host || plan.port != agent.port || plan.scheme != agent.scheme
    if isCrossOrigin && agent.transport.isNone then return .stop

    return .follow plan isCrossOrigin

/--
Transitions the agent to the redirect target.  Same-origin hops return the
current agent unchanged; cross-origin hops open a fresh session via the
connector (guaranteed present by `evaluateRedirect`).
-/
private def advanceAgent (agent : Agent α)
    (plan : Std.Http.RedirectPlan) (isCrossOrigin : Bool) : Async (Agent α) := do
  if !isCrossOrigin then return agent
  match agent.transport with
  | none => return agent  -- unreachable — evaluateRedirect gated on this
  | some connector =>
    let newSession ← connector.acquire plan.scheme plan.host plan.port
    connector.releaseHealthy agent.session agent.scheme agent.host agent.port
    return {
      session := newSession
      scheme := plan.scheme
      host := plan.host
      port := plan.port
      cookieJar := agent.cookieJar
      interceptors := agent.interceptors
      transport := some connector
    }

/--
Top-level recursive driver.  Dispatches one hop (with retry), then either
returns the response, stops on a blocked redirect gate, or advances to the
next hop.  The 90-line original is now a small orchestrator over `dispatchHop`,
`attemptWithRetry`, `evaluateRedirect`, and `advanceAgent`.
-/
private partial def sendWithRedirects [Transport α]
    (agent : Agent α) (request : Request Body.Any)
    (remaining : Nat) (retriesLeft : Nat)
    (history : Array (URI.Host × UInt16 × String) := #[]) : Async (Response Body.Stream) := do
  -- Record the current URL in the history and detect redirect cycles.
  let history := history.push (agent.host, agent.port, toString request.line.uri)

  let request := rewriteForProxy agent request
  let (agent, response) ← attemptWithRetry agent request retriesLeft

  match evaluateRedirect agent request response remaining history with
  | .final =>
    if let some validate := agent.session.config.validateStatus then
      if !validate response.line.status then
        markRedirectDrain response
        drainBodyForReuse response agent.session.config.redirectBodyDrainLimit
        throw (.userError s!"unexpected HTTP status: {response.line.status.toCode}")
    return response
  | .stop => return response
  | .follow plan isCrossOrigin =>
    markRedirectDrain response
    drainBodyForReuse response agent.session.config.redirectBodyDrainLimit
    let newRequest ← followRedirect plan request
    let agent ← advanceAgent agent plan isCrossOrigin
    sendWithRedirects agent newRequest (remaining - 1) retriesLeft history

/--
Send a request, automatically following redirects up to `config.maxRedirects` hops and
retrying on connection errors up to `config.maxRetries` times.
For cross-host redirects the agent reconnects using its `Agent.Connector` (if set).
Cookies are automatically injected from the jar and `Set-Cookie` responses are stored.
Response interceptors are applied after every response.
-/
def send {β : Type} [Coe β Body.Any] [Transport α] (agent : Agent α) (request : Request β) : Async (Response Body.Stream) :=
  sendWithRedirects
    agent
    { line := request.line, body := (request.body : Body.Any), extensions := request.extensions }
    agent.session.config.maxRedirects
    agent.session.config.maxRetries

end Agent

/-!
# Agent.RequestBuilder

A fluent builder that attaches an `Agent` to a `Request.Builder`, letting callers chain header
and query-parameter setters before dispatching with a typed `send*` terminal.

```lean
let response ←
  agent.get "/api/items"
  |>.header! "Accept" "application/json"
  |>.queryParam "page" "2"
  |>.send
```
-/

/--
A `Request.Builder` bound to a specific `Agent`.  Build up headers, query parameters, and body,
then call one of the `send*` methods to dispatch the request.
-/
structure Agent.RequestBuilder (α : Type) where
  /--
  The agent that will send this request.
  -/
  agent : Agent α

  /--
  The underlying request builder.
  -/
  builder : Request.Builder


namespace Agent.RequestBuilder

/--
Injects a `Host` header derived from the agent's `host` and `port` if no `Host` header
is already present.
-/
private def withHostHeader [Transport α] (rb : Agent.RequestBuilder α) : Agent.RequestBuilder α :=
  { rb with builder := rb.builder.hostDefault rb.agent.scheme rb.agent.host rb.agent.port }

/--
Prepares the builder by injecting the `Host` header, then calls `f` to build and send the
request. Cookie injection is handled by `Agent.injectCookies` inside `sendWithRedirects`.
-/
private def prepare [Transport α] (rb : Agent.RequestBuilder α)
    (f : Agent.RequestBuilder α → Async (Response Body.Stream)) : Async (Response Body.Stream) :=
  f rb.withHostHeader

/--
Adds a typed header to the request.
-/
def header [Transport α] (rb : Agent.RequestBuilder α) (key : Header.Name) (value : Header.Value) : Agent.RequestBuilder α :=
  { rb with builder := rb.builder.header key value }

/--
Adds a header to the request. Panics if the name or value is invalid.
-/
def header! [Transport α] (rb : Agent.RequestBuilder α) (key : String) (value : String) : Agent.RequestBuilder α :=
  { rb with builder := rb.builder.header! key value }

/--
Adds a header to the request. Returns `none` if the name or value is invalid.
-/
def header? [Transport α] (rb : Agent.RequestBuilder α) (key : String) (value : String) : Option (Agent.RequestBuilder α) := do
  let builder ← rb.builder.header? key value
  pure { rb with builder }

/--
Sets the request URI from a string. Panics if the string is not a valid request target.
-/
def uri! [Transport α] (rb : Agent.RequestBuilder α) (u : String) : Agent.RequestBuilder α :=
  { rb with builder := rb.builder.uri! u }

/--
Adds a query parameter to the request URI.
Works for both origin-form (e.g. set by `agent.get "/path"`) and absolute-form targets.
-/
def queryParam [Transport α] (rb : Agent.RequestBuilder α) (key : String) (value : String) : Agent.RequestBuilder α :=
  { rb with builder :=
    { rb.builder with line :=
      { rb.builder.line with uri := rb.builder.line.uri.setQueryParam key value } } }

/--
Sends the request with an empty body.
-/
def send [Transport α] (rb : Agent.RequestBuilder α) : Async (Response Body.Stream) :=
  rb.prepare fun rb => do rb.agent.send (← rb.builder.empty)

/--
Sends the request with a plain-text body.
Sets `Content-Type: text/plain; charset=utf-8`.
-/
def text [Transport α] (rb : Agent.RequestBuilder α) (content : String) : Async (Response Body.Stream) :=
  rb.prepare fun rb => do rb.agent.send (← rb.builder.text content)

/--
Sends the request with a JSON body.
Sets `Content-Type: application/json`.
-/
def json [Transport α] (rb : Agent.RequestBuilder α) (content : String) : Async (Response Body.Stream) :=
  rb.prepare fun rb => do rb.agent.send (← rb.builder.json content)

/--
Sends the request with a raw binary body.
Sets `Content-Type: application/octet-stream`.
-/
def bytes [Transport α] (rb : Agent.RequestBuilder α) (content : ByteArray) : Async (Response Body.Stream) :=
  rb.prepare fun rb => do rb.agent.send (← rb.builder.bytes content)

/--
Sends the request with a streaming body produced by `gen`.
-/
def sendStream [Transport α]
    (rb : Agent.RequestBuilder α)
    (gen : Body.Stream → Async Unit) : Async (Response Body.Stream) :=
  rb.prepare fun rb => do rb.agent.send (← rb.builder.stream gen)

end Agent.RequestBuilder

namespace Agent

/--
Creates a GET request builder for the given path or URL
-/
def get [Transport α] (agent : Agent α) (path : String) : Agent.RequestBuilder α :=
  { agent, builder := Request.get (RequestTarget.parse! path) }

/--
Creates a POST request builder for the given path or URL
-/
def post [Transport α] (agent : Agent α) (path : String) : Agent.RequestBuilder α :=
  { agent, builder := Request.post (RequestTarget.parse! path) }

/--
Creates a PUT request builder for the given path or URL
-/
def put [Transport α] (agent : Agent α) (path : String) : Agent.RequestBuilder α :=
  { agent, builder := Request.put (RequestTarget.parse! path) }

/--
Creates a DELETE request builder for the given path or URL
-/
def delete [Transport α] (agent : Agent α) (path : String) : Agent.RequestBuilder α :=
  { agent, builder := Request.delete (RequestTarget.parse! path) }

/--
Creates a PATCH request builder for the given path or URL
-/
def patch [Transport α] (agent : Agent α) (path : String) : Agent.RequestBuilder α :=
  { agent, builder := Request.patch (RequestTarget.parse! path) }

/--
Creates a HEAD request builder for the given path or URL
-/
def headReq [Transport α] (agent : Agent α) (path : String) : Agent.RequestBuilder α :=
  { agent, builder := Request.head (RequestTarget.parse! path) }

/--
Creates an OPTIONS request builder for the given path or URL.
-/
def options [Transport α] (agent : Agent α) (path : String) : Agent.RequestBuilder α :=
  { agent, builder := Request.options (RequestTarget.parse! path) }

end Std.Http.Client.Agent
