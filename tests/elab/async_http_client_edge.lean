import Std.Internal.Http
import Std.Internal.Async
import Std.Internal.Async.Timer

open Std.Internal.IO Async
open Std Http Internal

/-!
# HTTP Client Edge-Case Tests

These tests exercise subtle paths in `Std.Http.Client` that are easy to break during refactors:

1. Redirect method/body rewrites per RFC 9110 §15.4:
   - 303 always changes to GET (not just POST)
   - 301/302 preserve method for non-POST requests
   - 307/308 preserve method AND body when body is replayable
2. Cross-origin header scrubbing: `Authorization`, `Proxy-Authorization`, `Cookie`
3. Redirect policy: `maxRedirects = 0`, missing Location header, cycle detection
4. `Expect: 100-continue` state machine: success, 4xx rejection, server bypass
5. Informational responses (103 Early Hints) skipped before the final response
6. `maxResponseBodySize` enforcement closes connection and errors the request
-/

-- ============================================================
-- Shared helpers
-- ============================================================

private def runWithTimeout (name : String) (timeoutMs : Nat := 3000) (action : IO Unit) : IO Unit := do
  let task ← IO.asTask action
  let ticks := (timeoutMs + 9) / 10
  let rec loop (remaining : Nat) : IO Unit := do
    if (← IO.getTaskState task) == .finished then
      match (← IO.wait task) with
      | .ok x => pure x
      | .error err => throw err
    else
      match remaining with
      | 0 =>
        IO.cancel task
        throw <| IO.userError s!"Test '{name}' timed out after {timeoutMs}ms"
      | n + 1 =>
        IO.sleep 10
        loop n
  loop ticks

private def rawResp
    (status : String) (hdrs : Array (String × String)) (body : String) : ByteArray :=
  let hdrLines := hdrs.foldl (fun s (k, v) => s ++ s!"{k}: {v}\r\n") ""
  s!"HTTP/1.1 {status}\r\n{hdrLines}\r\n{body}".toUTF8

/-- Parse `Content-Length` from a raw HTTP header block. Returns 0 when absent. -/
private def parseContentLength (headerText : String) : Nat := Id.run do
  let lines := headerText.splitOn "\r\n"
  for line in lines do
    let lower := line.toLower
    if lower.startsWith "content-length:" then
      let rest := line.drop "content-length:".length
      return rest.trimAscii.toNat?.getD 0
  return 0

/-- Drain the mock until we've consumed a full request: headers + CL-sized body
    or chunked body terminated by `0\r\n\r\n`. -/
private def drainRequest (mockClient : Mock.Client) : Async ByteArray := do
  let mut bytes := ByteArray.empty
  -- Phase 1: accumulate until we see the header terminator.
  let mut headerEnd : Nat := 0
  repeat
    if (String.fromUTF8! bytes).contains "\r\n\r\n" then
      -- Find the byte index of the terminator end.
      let mut i := 0
      while i + 4 ≤ bytes.size do
        if bytes[i]! == 13 && bytes[i+1]! == 10 && bytes[i+2]! == 13 && bytes[i+3]! == 10 then
          headerEnd := i + 4
          break
        i := i + 1
      break
    let some chunk ← mockClient.recv?
      | throw (IO.userError "connection closed before headers")
    bytes := bytes ++ chunk
  -- Phase 2: framing based on headers.
  let headerText := String.fromUTF8! (bytes.extract 0 headerEnd)
  if headerText.toLower.contains "transfer-encoding:" then
    while !(String.fromUTF8! bytes).endsWith "0\r\n\r\n" do
      let some chunk ← mockClient.recv?
        | throw (IO.userError "connection closed mid-chunked")
      bytes := bytes ++ chunk
  else
    let cl := parseContentLength headerText
    while bytes.size < headerEnd + cl do
      let some chunk ← mockClient.recv?
        | throw (IO.userError "connection closed before full CL body")
      bytes := bytes ++ chunk
  pure bytes

private def mkAgent (mockServer : Mock.Server) (config : Client.Config := {})
    (port : UInt16 := 80) (scheme : String := "http") : Async (Client.Agent Mock.Server) := do
  let session ← Client.Session.new mockServer config
  let cookieJar ← Cookie.Jar.new
  let some domain := URI.DomainName.ofString? "example.com"
    | throw (IO.userError "DomainName parse failed")
  pure {
    session
    scheme := URI.Scheme.ofString! scheme
    host := .name domain
    port := port
    cookieJar
  }

private def sendInBackground {β : Type} [Coe β Body.Any]
    (agent : Client.Agent Mock.Server) (request : Request β)
    : Async (IO.Promise (Except String (Response Body.Stream))) := do
  let resultPromise : IO.Promise (Except String (Response Body.Stream)) ← IO.Promise.new
  background do
    let result ← try
        let resp ← Client.Agent.send agent request
        pure (Except.ok resp)
      catch e => pure (Except.error (toString e))
    discard <| resultPromise.resolve result
  pure resultPromise

-- ============================================================
-- Section 1 — Redirect method/body rewrites (RFC 9110 §15.4)
-- ============================================================

-- 303 See Other: any method → GET, body dropped.
-- The existing tests cover 302 POST→GET; this one covers the non-POST path.

#eval show IO _ from runWithTimeout "303 See Other converts PUT to GET and drops body" 3000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer

  let request ← Request.new
    |>.method .put
    |>.uri! "/upload"
    |>.header! "Host" "example.com"
    |>.text "original-body"

  let resultPromise ← sendInBackground agent request

  let _ ← drainRequest mockClient
  mockClient.send (rawResp "303 See Other"
    #[("Location", "/after-put"),
      ("Content-Length", "0"),
      ("Connection", "keep-alive")] "")

  let redirectBytes ← drainRequest mockClient
  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "2"), ("Connection", "close")] "ok")

  match ← await resultPromise.result! with
  | Except.error e => throw (IO.userError s!"agent error: {e}")
  | Except.ok _ => pure ()

  let redirectText := String.fromUTF8! redirectBytes
  unless redirectText.startsWith "GET " do
    throw <| IO.userError
      s!"expected GET after 303, got:\n{redirectText.quote}"
  if redirectText.contains "original-body" then
    throw <| IO.userError
      s!"303 must drop body, but redirect request contained it:\n{redirectText.quote}"

-- 301/302 preserve method for non-POST requests.
-- Current code only rewrites POST → GET on 301/302; a PUT must remain PUT.

#eval show IO _ from runWithTimeout "301 Moved Permanently preserves PUT method" 3000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer

  let request ← Request.new
    |>.method .put
    |>.uri! "/v1/resource"
    |>.header! "Host" "example.com"
    |>.text "payload-x"

  let resultPromise ← sendInBackground agent request

  let _ ← drainRequest mockClient
  mockClient.send (rawResp "301 Moved Permanently"
    #[("Location", "/v2/resource"),
      ("Content-Length", "0"),
      ("Connection", "keep-alive")] "")

  let redirectBytes ← drainRequest mockClient
  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "2"), ("Connection", "close")] "ok")

  match ← await resultPromise.result! with
  | Except.error e => throw (IO.userError s!"agent error: {e}")
  | Except.ok _ => pure ()

  let redirectText := String.fromUTF8! redirectBytes
  unless redirectText.startsWith "PUT " do
    throw <| IO.userError
      s!"301 on PUT must preserve method, got:\n{redirectText.quote}"
  unless redirectText.contains "PUT /v2/resource" do
    throw <| IO.userError
      s!"expected PUT /v2/resource, got:\n{redirectText.quote}"

-- 308 Permanent Redirect preserves method AND replayable body.
-- This is the distinguishing behavior vs. 301: with a replayable full body the
-- bytes must be sent again on the redirected request.

#eval show IO _ from runWithTimeout "308 Permanent Redirect replays body for PUT" 4000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer

  let request ← Request.new
    |>.method .put
    |>.uri! "/v1/resource"
    |>.header! "Host" "example.com"
    |>.text "replay-me"

  let resultPromise ← sendInBackground agent request

  -- First request must contain the original body.
  let mut firstBytes := ByteArray.empty
  repeat
    let some chunk ← mockClient.recv?
      | throw (IO.userError "connection closed before first body fully received")
    firstBytes := firstBytes ++ chunk
    let t := String.fromUTF8! firstBytes
    if t.endsWith "replay-me" || t.endsWith "0\r\n\r\n" then break
  mockClient.send (rawResp "308 Permanent Redirect"
    #[("Location", "/v2/resource"),
      ("Content-Length", "0"),
      ("Connection", "keep-alive")] "")

  -- Second request must contain the body again.
  let mut redirectBytes := ByteArray.empty
  repeat
    let some chunk ← mockClient.recv?
      | throw (IO.userError "connection closed before redirect body fully received")
    redirectBytes := redirectBytes ++ chunk
    let t := String.fromUTF8! redirectBytes
    if t.endsWith "replay-me" || t.endsWith "0\r\n\r\n" then break
  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "2"), ("Connection", "close")] "ok")

  match ← await resultPromise.result! with
  | Except.error e => throw (IO.userError s!"agent error: {e}")
  | Except.ok _ => pure ()

  let redirectText := String.fromUTF8! redirectBytes
  unless redirectText.startsWith "PUT " do
    throw <| IO.userError s!"308 must preserve PUT:\n{redirectText.quote}"
  unless redirectText.contains "replay-me" do
    throw <| IO.userError
      s!"308 with replayable body must retransmit payload, redirect request:\n{redirectText.quote}"

-- ============================================================
-- Section 2 — Cross-origin header scrubbing
-- ============================================================

-- Proxy-Authorization must be stripped alongside Authorization on cross-origin redirects.

-- Setup: two mocks — the agent redirects from http://example.com:443 to
-- https://example.com:443 (scheme change) and opens the follow-up on a fresh
-- session via the `connectTo` factory. The second mock carries the redirected
-- request and lets us inspect the headers the agent actually sent.
#eval show IO _ from runWithTimeout "cross-origin strips Proxy-Authorization" 4000 <| Async.block do
  let (mockClient1, mockServer1) ← Mock.new
  let (mockClient2, mockServer2) ← Mock.new
  let session1 ← Client.Session.new mockServer1 (config := {})
  let cookieJar ← Cookie.Jar.new
  let some domain := URI.DomainName.ofString? "example.com"
    | throw (IO.userError "DomainName parse failed")
  let agent : Client.Agent Mock.Server := {
    session := session1
    scheme := URI.Scheme.ofString! "http"
    host := .name domain
    port := 443
    cookieJar
    transport := some {
      acquire := fun _ _ _ => Client.Session.new mockServer2 (config := {})
      release := fun s _ _ _ => discard <| s.close
    }
  }

  let request ← Request.new
    |>.method .get
    |>.uri! "/"
    |>.header! "Host" "example.com:443"
    |>.header! "Proxy-Authorization" "Basic c2VjcmV0OnNlY3JldA=="
    |>.empty

  let resultPromise ← sendInBackground agent request

  -- First exchange on mock 1.
  let _ ← drainRequest mockClient1
  mockClient1.send (rawResp "302 Found"
    #[("Location", "https://example.com:443/after"),
      ("Content-Length", "0"),
      ("Connection", "close")] "")

  -- Second exchange (redirected request) on mock 2.
  let redirectBytes ← drainRequest mockClient2
  mockClient2.send (rawResp "200 OK"
    #[("Content-Length", "2"), ("Connection", "close")] "ok")

  match ← await resultPromise.result! with
  | Except.error e => throw (IO.userError s!"agent error: {e}")
  | Except.ok _ => pure ()

  let redirectText := String.fromUTF8! redirectBytes
  if redirectText.contains "Proxy-Authorization:" then
    throw <| IO.userError
      s!"Proxy-Authorization must be stripped on cross-origin redirect:\n{redirectText.quote}"

-- Cookie header set explicitly on the request must be stripped on cross-origin redirects.
-- (Jar cookies are per-host anyway; this tests the explicit Cookie header path.)

#eval show IO _ from runWithTimeout "cross-origin strips explicit Cookie header" 4000 <| Async.block do
  let (mockClient1, mockServer1) ← Mock.new
  let (mockClient2, mockServer2) ← Mock.new
  let session1 ← Client.Session.new mockServer1 (config := {})
  let cookieJar ← Cookie.Jar.new
  let some domain := URI.DomainName.ofString? "example.com"
    | throw (IO.userError "DomainName parse failed")
  let agent : Client.Agent Mock.Server := {
    session := session1
    scheme := URI.Scheme.ofString! "http"
    host := .name domain
    port := 443
    cookieJar
    transport := some {
      acquire := fun _ _ _ => Client.Session.new mockServer2 (config := {})
      release := fun s _ _ _ => discard <| s.close
    }
  }

  let request ← Request.new
    |>.method .get
    |>.uri! "/"
    |>.header! "Host" "example.com:443"
    |>.header! "Cookie" "session=abc123"
    |>.empty

  let resultPromise ← sendInBackground agent request

  -- First exchange on mock 1.
  let _ ← drainRequest mockClient1
  mockClient1.send (rawResp "302 Found"
    #[("Location", "https://example.com:443/after"),
      ("Content-Length", "0"),
      ("Connection", "close")] "")

  -- Second exchange on mock 2.
  let redirectBytes ← drainRequest mockClient2
  mockClient2.send (rawResp "200 OK"
    #[("Content-Length", "2"), ("Connection", "close")] "ok")

  match ← await resultPromise.result! with
  | Except.error e => throw (IO.userError s!"agent error: {e}")
  | Except.ok _ => pure ()

  let redirectText := String.fromUTF8! redirectBytes
  if redirectText.contains "session=abc123" then
    throw <| IO.userError
      s!"explicit Cookie must be stripped on cross-origin redirect:\n{redirectText.quote}"

-- A `Set-Cookie` without `Path=` must default to the directory of the request URI,
-- not to `/`. A cookie set on `/app/login` should be sent to `/app/profile` but not
-- to `/other`.

#eval show IO _ from runWithTimeout "default cookie path stays scoped to request directory" 4000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer

  let loginReq ← Request.new |>.method .get |>.uri! "/app/login"
    |>.header! "Host" "example.com" |>.empty
  let loginPromise ← sendInBackground agent loginReq

  let _ ← drainRequest mockClient
  mockClient.send (rawResp "200 OK"
    #[("Set-Cookie", "sid=1"),
      ("Content-Length", "2"),
      ("Connection", "keep-alive")] "ok")

  match ← await loginPromise.result! with
  | Except.error e => throw (IO.userError s!"login request failed: {e}")
  | Except.ok resp =>
    let _ ← resp.body.readAll (α := String)

  let siblingReq ← Request.new |>.method .get |>.uri! "/other"
    |>.header! "Host" "example.com" |>.empty
  let siblingPromise ← sendInBackground agent siblingReq

  let siblingBytes ← drainRequest mockClient
  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "2"),
      ("Connection", "keep-alive")] "ok")

  match ← await siblingPromise.result! with
  | Except.error e => throw (IO.userError s!"sibling request failed: {e}")
  | Except.ok resp =>
    let _ ← resp.body.readAll (α := String)

  let siblingText := String.fromUTF8! siblingBytes
  if siblingText.contains "Cookie: sid=1" then
    throw <| IO.userError
      s!"cookie without Path= must not be sent to /other:\n{siblingText.quote}"

  let childReq ← Request.new |>.method .get |>.uri! "/app/profile"
    |>.header! "Host" "example.com" |>.empty
  let childPromise ← sendInBackground agent childReq

  let childBytes ← drainRequest mockClient
  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "2"),
      ("Connection", "close")] "ok")

  match ← await childPromise.result! with
  | Except.error e => throw (IO.userError s!"child-path request failed: {e}")
  | Except.ok resp =>
    let _ ← resp.body.readAll (α := String)

  let childText := String.fromUTF8! childBytes
  unless childText.contains "Cookie: sid=1" do
    throw <| IO.userError
      s!"cookie without Path= must be sent to /app/profile:\n{childText.quote}"

-- ============================================================
-- Section 3 — Redirect policy
-- ============================================================

-- With maxRedirects = 0 the agent must return the 3xx response as-is.

#eval show IO _ from runWithTimeout "maxRedirects=0 returns 302 unfollowed" 3000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer (config := { maxRedirects := 0 })

  let request ← Request.new
    |>.method .get
    |>.uri! "/"
    |>.header! "Host" "example.com"
    |>.empty

  let resultPromise ← sendInBackground agent request

  let _ ← mockClient.recv?
  mockClient.send (rawResp "302 Found"
    #[("Location", "/elsewhere"),
      ("Content-Length", "0")] "")

  -- A second recv must not occur. Run it in the background as a safety net.
  background do
    let _ ← mockClient.recv?
    pure ()

  match ← await resultPromise.result! with
  | Except.error e => throw (IO.userError s!"agent error: {e}")
  | Except.ok resp =>
    unless resp.line.status == .found do
      throw <| IO.userError
        s!"expected 302 returned unfollowed, got {resp.line.status.toCode}"

-- A 3xx response without a Location header must be returned as the final response.

#eval show IO _ from runWithTimeout "302 without Location returned as-is" 3000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer

  let request ← Request.new
    |>.method .get
    |>.uri! "/"
    |>.header! "Host" "example.com"
    |>.empty

  let resultPromise ← sendInBackground agent request

  let _ ← mockClient.recv?
  mockClient.send (rawResp "302 Found"
    #[("Content-Length", "0"), ("Connection", "close")] "")

  match ← await resultPromise.result! with
  | Except.error e => throw (IO.userError s!"agent error: {e}")
  | Except.ok resp =>
    unless resp.line.status == .found do
      throw <| IO.userError
        s!"expected 302 (no Location) returned as-is, got {resp.line.status.toCode}"

-- A same-origin redirect loop (A → /a → /a → /a) must be broken.
-- The agent records each (host, port, uri) tuple in its history and stops when
-- it would revisit a tuple it already served in the current chain.

#eval show IO _ from runWithTimeout "redirect cycle detection stops and returns last 3xx" 4000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer

  let request ← Request.new
    |>.method .get
    |>.uri! "/start"
    |>.header! "Host" "example.com"
    |>.empty

  let resultPromise ← sendInBackground agent request

  -- /start → /cycle → /start (cycle).
  let _ ← drainRequest mockClient
  mockClient.send (rawResp "302 Found"
    #[("Location", "/cycle"),
      ("Content-Length", "0"),
      ("Connection", "keep-alive")] "")

  let _ ← drainRequest mockClient
  mockClient.send (rawResp "302 Found"
    #[("Location", "/start"),
      ("Content-Length", "0"),
      ("Connection", "keep-alive")] "")

  -- Cycle detected: no further requests.
  background do
    let _ ← mockClient.recv?
    pure ()

  match ← await resultPromise.result! with
  | Except.error e => throw (IO.userError s!"agent error: {e}")
  | Except.ok resp =>
    unless resp.line.status == .found do
      throw <| IO.userError
        s!"expected 302 (cycle stop), got {resp.line.status.toCode}"

-- ============================================================
-- Section 4 — Expect: 100-continue
-- ============================================================

-- Happy path: server sends 100, client pumps body, server sends 200.

#eval show IO _ from runWithTimeout "Expect: 100-continue happy path sends body after 100" 4000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer

  let request ← Request.new
    |>.method .post
    |>.uri! "/submit"
    |>.header! "Host" "example.com"
    |>.header! "Expect" "100-continue"
    |>.text "actual-body"

  let resultPromise ← sendInBackground agent request

  -- Read the header-only request first: the client must NOT send the body yet.
  let mut headerBytes := ByteArray.empty
  repeat
    let some chunk ← mockClient.recv?
      | throw (IO.userError "connection closed before headers received")
    headerBytes := headerBytes ++ chunk
    let t := String.fromUTF8! headerBytes
    if t.contains "\r\n\r\n" then break
  let headerText := String.fromUTF8! headerBytes
  if headerText.contains "actual-body" then
    throw <| IO.userError
      s!"client sent body before 100 Continue:\n{headerText.quote}"

  -- Send 100 Continue.
  mockClient.send "HTTP/1.1 100 Continue\r\n\r\n".toUTF8

  -- Now the client should push the body. Read until we see "actual-body".
  let mut bodyBytes := headerBytes
  repeat
    let t := String.fromUTF8! bodyBytes
    if t.contains "actual-body" then break
    let some chunk ← mockClient.recv?
      | throw (IO.userError "connection closed before body received")
    bodyBytes := bodyBytes ++ chunk

  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "2"), ("Connection", "close")] "ok")

  match ← await resultPromise.result! with
  | Except.error e => throw (IO.userError s!"agent error: {e}")
  | Except.ok resp =>
    unless resp.line.status.toCode == 200 do
      throw <| IO.userError s!"expected 200, got {resp.line.status.toCode}"

-- 4xx rejection: server rejects with 417 before reading body; body must not be sent.

#eval show IO _ from runWithTimeout "Expect: 100-continue 417 rejection discards body" 4000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer

  let request ← Request.new
    |>.method .post
    |>.uri! "/submit"
    |>.header! "Host" "example.com"
    |>.header! "Expect" "100-continue"
    |>.text "rejected-body"

  let resultPromise ← sendInBackground agent request

  -- Read header-only.
  let mut headerBytes := ByteArray.empty
  repeat
    let some chunk ← mockClient.recv?
      | throw (IO.userError "connection closed before headers received")
    headerBytes := headerBytes ++ chunk
    let t := String.fromUTF8! headerBytes
    if t.contains "\r\n\r\n" then break
  let headerText := String.fromUTF8! headerBytes
  if headerText.contains "rejected-body" then
    throw <| IO.userError
      s!"client sent body before server response:\n{headerText.quote}"

  -- Reject with 417 Expectation Failed (instead of 100). Close after.
  mockClient.send (rawResp "417 Expectation Failed"
    #[("Content-Length", "0"), ("Connection", "close")] "")

  -- Observe the wire: the rejected body must never appear.
  let leakedRef ← IO.mkRef false
  background do
    let mut acc := ByteArray.empty
    repeat
      match ← mockClient.recv? with
      | none => break
      | some c =>
        acc := acc ++ c
        if (String.fromUTF8! acc).contains "rejected-body" then
          leakedRef.set true
          break

  match ← await resultPromise.result! with
  | Except.error _ =>
    -- Error from the agent is acceptable — key check is no body leak.
    pure ()
  | Except.ok resp =>
    unless resp.line.status.toCode == 417 do
      throw <| IO.userError s!"expected 417, got {resp.line.status.toCode}"

  -- Give the drain task a brief moment to observe any stray writes.
  IO.sleep 50
  if ← leakedRef.get then
    throw (IO.userError "body was sent after 417 Expectation Failed")

-- Server bypass: no 100 is sent, the server jumps straight to a 2xx response
-- before the body has been pumped. The pending body must be discarded so the
-- connection is not stuck.

#eval show IO _ from runWithTimeout "Expect: 100-continue bypass with early 200 discards pending body" 4000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer

  let request ← Request.new
    |>.method .post
    |>.uri! "/submit"
    |>.header! "Host" "example.com"
    |>.header! "Expect" "100-continue"
    |>.text "unused-body"

  let resultPromise ← sendInBackground agent request

  -- Read only headers.
  let mut headerBytes := ByteArray.empty
  repeat
    let some chunk ← mockClient.recv?
      | throw (IO.userError "connection closed before headers")
    headerBytes := headerBytes ++ chunk
    let t := String.fromUTF8! headerBytes
    if t.contains "\r\n\r\n" then break

  -- Send a direct 200 (bypass 100-continue). Close the connection so the agent
  -- does not hang waiting for more responses.
  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "2"), ("Connection", "close")] "ok")

  match ← await resultPromise.result! with
  | Except.error e => throw (IO.userError s!"agent error on bypass: {e}")
  | Except.ok resp =>
    unless resp.line.status.toCode == 200 do
      throw <| IO.userError s!"expected 200 on bypass, got {resp.line.status.toCode}"

-- ============================================================
-- Section 5 — Informational responses (1xx) are transparent
-- ============================================================

-- 103 Early Hints must not resolve the caller — the final response must arrive.

#eval show IO _ from runWithTimeout "103 Early Hints is transparent" 3000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer

  let request ← Request.new
    |>.method .get
    |>.uri! "/"
    |>.header! "Host" "example.com"
    |>.empty

  let resultPromise ← sendInBackground agent request

  let _ ← mockClient.recv?
  -- 103 with a couple of hint headers, then the real 200.
  mockClient.send "HTTP/1.1 103 Early Hints\r\nLink: </style.css>; rel=preload\r\n\r\n".toUTF8
  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "2"), ("Connection", "close")] "ok")

  match ← await resultPromise.result! with
  | Except.error e => throw (IO.userError s!"agent error: {e}")
  | Except.ok resp =>
    unless resp.line.status.toCode == 200 do
      throw <| IO.userError
        s!"103 must be transparent; expected 200, got {resp.line.status.toCode}"

-- Multiple consecutive 1xx responses must all be skipped before the real response.

#eval show IO _ from runWithTimeout "multiple 103 responses all skipped" 3000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer

  let request ← Request.new
    |>.method .get
    |>.uri! "/"
    |>.header! "Host" "example.com"
    |>.empty

  let resultPromise ← sendInBackground agent request

  let _ ← mockClient.recv?
  mockClient.send "HTTP/1.1 103 Early Hints\r\nLink: </a.css>; rel=preload\r\n\r\n".toUTF8
  mockClient.send "HTTP/1.1 103 Early Hints\r\nLink: </b.css>; rel=preload\r\n\r\n".toUTF8
  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "2"), ("Connection", "close")] "ok")

  match ← await resultPromise.result! with
  | Except.error e => throw (IO.userError s!"agent error: {e}")
  | Except.ok resp =>
    unless resp.line.status.toCode == 200 do
      throw <| IO.userError
        s!"expected 200 after repeated 103s, got {resp.line.status.toCode}"

-- ============================================================
-- Section 6 — Response body size limit
-- ============================================================

-- A response body longer than `maxResponseBodySize` must fail the request with an error.
-- The body must be reported via the body stream; reading it should see the error
-- bubble up through the agent.send promise.

#eval show IO _ from runWithTimeout "maxResponseBodySize exceeded errors the request" 4000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer (config := { maxResponseBodySize := some 4 })

  let request ← Request.new
    |>.method .get
    |>.uri! "/big"
    |>.header! "Host" "example.com"
    |>.empty

  let resultPromise ← sendInBackground agent request

  let _ ← drainRequest mockClient
  -- Advertise 16 bytes (well over the 4-byte limit) and send them all.
  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "16"), ("Connection", "close")] "0123456789ABCDEF")

  match ← await resultPromise.result! with
  | Except.error _ =>
    -- Agent surfaced an error up-front — acceptable: the limit was enforced.
    pure ()
  | Except.ok resp =>
    -- Headers may resolve before the limit triggers. Reading the body must
    -- either error or stop short of the full 16 bytes.
    let got : Except String String ← try
        let s ← resp.body.readAll (α := String)
        pure (Except.ok s)
      catch e => pure (Except.error (toString e))
    match got with
    | Except.ok s =>
      if s.toUTF8.size > 4 then
        throw (IO.userError s!"response body limit not enforced; read {s.toUTF8.size} bytes")
    | Except.error _ => pure ()

-- The body-size counter must reset on `.next` so a second keep-alive response
-- is checked against its own size, not the cumulative bytes from the previous
-- response.

#eval show IO _ from runWithTimeout "maxResponseBodySize resets between keep-alive requests" 4000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer (config := { maxResponseBodySize := some 4 })

  let req1 ← Request.new |>.method .get |>.uri! "/first"
    |>.header! "Host" "example.com" |>.empty
  let p1 ← sendInBackground agent req1

  let _ ← drainRequest mockClient
  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "4"), ("Connection", "keep-alive")] "1234")

  match ← await p1.result! with
  | Except.error e => throw (IO.userError s!"first request failed: {e}")
  | Except.ok resp =>
    let body ← resp.body.readAll (α := String)
    unless body == "1234" do
      throw (IO.userError s!"expected first body '1234', got {body.quote}")

  let req2 ← Request.new |>.method .get |>.uri! "/second"
    |>.header! "Host" "example.com" |>.empty
  let p2 ← sendInBackground agent req2

  let _ ← drainRequest mockClient
  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "2"), ("Connection", "close")] "ok")

  match ← await p2.result! with
  | Except.error e => throw (IO.userError s!"second request failed: {e}")
  | Except.ok resp =>
    let body ← resp.body.readAll (α := String)
    unless body == "ok" do
      throw (IO.userError s!"expected second body 'ok', got {body.quote}")

-- An unfollowed 3xx response is caller-facing, so its body must still respect
-- `maxResponseBodySize` rather than the internal redirect drain limit.

#eval show IO _ from runWithTimeout "maxResponseBodySize applies to unfollowed 302 body" 4000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer (config := { maxRedirects := 0, maxResponseBodySize := some 5 })

  let request ← Request.new |>.method .get |>.uri! "/"
    |>.header! "Host" "example.com" |>.empty

  let resultPromise ← sendInBackground agent request

  let _ ← drainRequest mockClient
  mockClient.send (rawResp "302 Found"
    #[("Location", "/next"),
      ("Content-Length", "10"),
      ("Connection", "close")] "0123456789")

  match ← await resultPromise.result! with
  | Except.error e => throw (IO.userError s!"agent errored before returning 302: {e}")
  | Except.ok resp =>
    unless resp.line.status.toCode == 302 do
      throw (IO.userError s!"expected 302, got {resp.line.status.toCode}")
    let got : Except String String ← try
        let s ← resp.body.readAll (α := String)
        pure (Except.ok s)
      catch e => pure (Except.error (toString e))
    match got with
    | Except.error _ => pure ()
    | Except.ok s =>
      if s.toUTF8.size > 5 then
        throw (IO.userError s!"unfollowed 302 ignored maxResponseBodySize and returned {s.toUTF8.size} bytes")

-- A rejected `validateStatus` must not strand unread body bytes on the session.
-- After the error, the same keep-alive connection should still handle the next request.

#eval show IO _ from runWithTimeout "validateStatus rejection preserves keep-alive reuse" 4000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer
    (config := { validateStatus := some (fun s => s.toCode / 100 == 2) })

  let badReq ← Request.new |>.method .get |>.uri! "/bad"
    |>.header! "Host" "example.com" |>.empty
  let badPromise ← sendInBackground agent badReq

  let _ ← drainRequest mockClient
  mockClient.send (rawResp "404 Not Found"
    #[("Content-Length", "5"),
      ("Connection", "keep-alive")] "error")

  match ← await badPromise.result! with
  | Except.ok _ =>
    throw (IO.userError "expected validateStatus to reject 404")
  | Except.error _ => pure ()

  let goodReq ← Request.new |>.method .get |>.uri! "/good"
    |>.header! "Host" "example.com" |>.empty
  let goodPromise ← sendInBackground agent goodReq

  let goodBytes ← drainRequest mockClient
  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "2"),
      ("Connection", "close")] "ok")

  match ← await goodPromise.result! with
  | Except.error e => throw (IO.userError s!"follow-up request failed after validateStatus rejection: {e}")
  | Except.ok resp =>
    let body ← resp.body.readAll (α := String)
    unless body == "ok" do
      throw (IO.userError s!"expected follow-up body 'ok', got {body.quote}")

  let goodText := String.fromUTF8! goodBytes
  unless goodText.startsWith "GET /good" do
    throw <| IO.userError
      s!"follow-up request never reached the wire after validateStatus rejection:\n{goodText.quote}"

-- ============================================================
-- Section 7 — Keep-alive and Connection: close
-- ============================================================

-- Two sequential requests on the same session must both succeed, exercising the
-- `.next` reset path in the connection state machine.

#eval show IO _ from runWithTimeout "two sequential GETs on keep-alive succeed" 4000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer

  -- First request.
  let req1 ← Request.new |>.method .get |>.uri! "/one"
    |>.header! "Host" "example.com" |>.empty
  let p1 ← sendInBackground agent req1

  let _ ← drainRequest mockClient
  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "3"), ("Connection", "keep-alive")] "one")

  match ← await p1.result! with
  | Except.error e => throw (IO.userError s!"first request failed: {e}")
  | Except.ok resp =>
    let body ← resp.body.readAll (α := String)
    unless body == "one" do
      throw (IO.userError s!"expected 'one', got {body.quote}")

  -- Second request on same session must succeed.
  let req2 ← Request.new |>.method .get |>.uri! "/two"
    |>.header! "Host" "example.com" |>.empty
  let p2 ← sendInBackground agent req2

  let _ ← drainRequest mockClient
  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "3"), ("Connection", "close")] "two")

  match ← await p2.result! with
  | Except.error e => throw (IO.userError s!"second request failed: {e}")
  | Except.ok resp =>
    let body ← resp.body.readAll (α := String)
    unless body == "two" do
      throw (IO.userError s!"expected 'two', got {body.quote}")

-- `Connection: close` on the response must close the session; a follow-up request
-- on the same session must error out rather than hang.

#eval show IO _ from runWithTimeout "Connection: close prevents reuse" 4000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer

  let req1 ← Request.new |>.method .get |>.uri! "/"
    |>.header! "Host" "example.com" |>.empty
  let p1 ← sendInBackground agent req1

  let _ ← drainRequest mockClient
  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "2"), ("Connection", "close")] "ok")

  match ← await p1.result! with
  | Except.error e => throw (IO.userError s!"first request failed: {e}")
  | Except.ok resp =>
    let _ ← resp.body.readAll (α := String)

  -- Close the mock's receive side so the session observes EOF.
  mockClient.close

  -- Second send must not hang; it must fail because the session is closed.
  let req2 ← Request.new |>.method .get |>.uri! "/"
    |>.header! "Host" "example.com" |>.empty
  let p2 ← sendInBackground agent req2

  match ← await p2.result! with
  | Except.ok _ =>
    throw (IO.userError "second request unexpectedly succeeded after Connection: close")
  | Except.error _ => pure ()

-- ============================================================
-- Section 8 — Methods that do not carry a body
-- ============================================================

-- A HEAD response with `Content-Length: N` must not cause the client to wait for N
-- body bytes (RFC 9110 §8.6); the response should be delivered and the connection
-- reusable.

#eval show IO _ from runWithTimeout "HEAD response with Content-Length has no body" 4000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer

  let req ← Request.new |>.method .head |>.uri! "/doc.html"
    |>.header! "Host" "example.com" |>.empty
  let p ← sendInBackground agent req

  let _ ← drainRequest mockClient
  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "1234"), ("Connection", "keep-alive")] "")

  match ← await p.result! with
  | Except.error e => throw (IO.userError s!"HEAD request failed: {e}")
  | Except.ok resp =>
    unless resp.line.status.toCode == 200 do
      throw (IO.userError s!"expected 200, got {resp.line.status.toCode}")

  let req2 ← Request.new |>.method .get |>.uri! "/follow"
    |>.header! "Host" "example.com" |>.empty
  let p2 ← sendInBackground agent req2

  let _ ← drainRequest mockClient
  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "2"), ("Connection", "close")] "ok")

  match ← await p2.result! with
  | Except.error e => throw (IO.userError s!"follow-up GET after HEAD failed: {e}")
  | Except.ok _ => pure ()

-- A 204 No Content response has no body regardless of framing headers. Keep-alive
-- must be preserved so a second request on the same connection succeeds.

#eval show IO _ from runWithTimeout "204 No Content supports keep-alive" 4000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer

  let req ← Request.new |>.method .delete |>.uri! "/item/1"
    |>.header! "Host" "example.com" |>.empty
  let p ← sendInBackground agent req

  let _ ← drainRequest mockClient
  mockClient.send "HTTP/1.1 204 No Content\r\nConnection: keep-alive\r\n\r\n".toUTF8

  match ← await p.result! with
  | Except.error e => throw (IO.userError s!"DELETE failed: {e}")
  | Except.ok resp =>
    unless resp.line.status.toCode == 204 do
      throw (IO.userError s!"expected 204, got {resp.line.status.toCode}")

  let req2 ← Request.new |>.method .get |>.uri! "/other"
    |>.header! "Host" "example.com" |>.empty
  let p2 ← sendInBackground agent req2

  let _ ← drainRequest mockClient
  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "2"), ("Connection", "close")] "ok")

  match ← await p2.result! with
  | Except.error e => throw (IO.userError s!"follow-up after 204 failed: {e}")
  | Except.ok _ => pure ()

-- ============================================================
-- Section 9 — 301/302 non-POST methods (RFC 9110 §15.4)
-- ============================================================
-- The "POST → GET on 301/302" rule is a narrow exception. HEAD, PATCH, DELETE,
-- OPTIONS must all preserve their method across 301/302.

#eval show IO _ from runWithTimeout "301 preserves HEAD method" 3000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer

  let req ← Request.new |>.method .head |>.uri! "/old"
    |>.header! "Host" "example.com" |>.empty
  let p ← sendInBackground agent req

  let _ ← drainRequest mockClient
  mockClient.send (rawResp "301 Moved Permanently"
    #[("Location", "/new"),
      ("Content-Length", "0"),
      ("Connection", "keep-alive")] "")

  let redirectBytes ← drainRequest mockClient
  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "0"), ("Connection", "close")] "")

  match ← await p.result! with
  | Except.error e => throw (IO.userError s!"agent error: {e}")
  | Except.ok _ => pure ()

  let redirectText := String.fromUTF8! redirectBytes
  unless redirectText.startsWith "HEAD " do
    throw <| IO.userError s!"301 must preserve HEAD:\n{redirectText.quote}"

#eval show IO _ from runWithTimeout "301 preserves PATCH method" 3000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer

  let req ← Request.new |>.method .patch |>.uri! "/res"
    |>.header! "Host" "example.com" |>.text "patch-body"
  let p ← sendInBackground agent req

  let _ ← drainRequest mockClient
  mockClient.send (rawResp "302 Found"
    #[("Location", "/res-new"),
      ("Content-Length", "0"),
      ("Connection", "keep-alive")] "")

  let redirectBytes ← drainRequest mockClient
  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "0"), ("Connection", "close")] "")

  match ← await p.result! with
  | Except.error e => throw (IO.userError s!"agent error: {e}")
  | Except.ok _ => pure ()

  let redirectText := String.fromUTF8! redirectBytes
  unless redirectText.startsWith "PATCH " do
    throw <| IO.userError s!"302 must preserve PATCH:\n{redirectText.quote}"
  -- PATCH is replayable (text body is Body.Full), so the body must be retransmitted.
  unless redirectText.contains "patch-body" do
    throw <| IO.userError
      s!"302 PATCH with replayable body must retransmit payload:\n{redirectText.quote}"

-- ============================================================
-- Section 10 — Relative Location preserves scheme and host
-- ============================================================
-- A `Location: /path` (relative) must not change the request's scheme, host or
-- port. The earlier redirect tests implicitly rely on this but none asserts it.

#eval show IO _ from runWithTimeout "relative Location preserves host and scheme" 3000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer

  let req ← Request.new |>.method .get |>.uri! "/old"
    |>.header! "Host" "example.com" |>.empty
  let p ← sendInBackground agent req

  let _ ← drainRequest mockClient
  mockClient.send (rawResp "302 Found"
    #[("Location", "/new"),
      ("Content-Length", "0"),
      ("Connection", "keep-alive")] "")

  let redirectBytes ← drainRequest mockClient
  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "0"), ("Connection", "close")] "")

  match ← await p.result! with
  | Except.error e => throw (IO.userError s!"agent error: {e}")
  | Except.ok _ => pure ()

  let redirectText := String.fromUTF8! redirectBytes
  -- Host header must still reference example.com.
  unless redirectText.contains "Host: example.com" do
    throw <| IO.userError
      s!"relative redirect must preserve Host header:\n{redirectText.quote}"
  -- And the target must be /new (origin-form, not absolute-form).
  unless redirectText.startsWith "GET /new" do
    throw <| IO.userError
      s!"expected GET /new, got:\n{redirectText.quote}"

-- ============================================================
-- Section 11 — Server closes mid-response body
-- ============================================================
-- If the server drops the connection after headers but before the full body,
-- reading the body must surface an error rather than silently returning
-- truncated data — otherwise a caller cannot tell a complete 3-byte body from a
-- truncated 10-byte body.

#eval show IO _ from runWithTimeout "server close mid-body errors body read" 4000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer

  let req ← Request.new |>.method .get |>.uri! "/short"
    |>.header! "Host" "example.com" |>.empty
  let p ← sendInBackground agent req

  let _ ← drainRequest mockClient
  mockClient.send "HTTP/1.1 200 OK\r\nContent-Length: 10\r\nConnection: close\r\n\r\n".toUTF8
  mockClient.send "abc".toUTF8
  mockClient.close

  match ← await p.result! with
  | Except.error _ => pure ()
  | Except.ok resp =>
    let got : Except String String ← try
        let s ← resp.body.readAll (α := String)
        pure (Except.ok s)
      catch e => pure (Except.error (toString e))
    match got with
    | Except.ok s =>
      if s.toUTF8.size == 10 then
        pure ()
      else
        throw (IO.userError s!"partial body silently returned ({s.toUTF8.size} of 10 bytes, expected error)")
    | Except.error _ => pure ()

-- ============================================================
-- Section 12 — Default User-Agent is present
-- ============================================================
-- The default `Config.userAgent` ("lean-http/1.1") must be injected when the
-- request does not set one.

#eval show IO _ from runWithTimeout "default User-Agent injected" 3000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer

  let req ← Request.new |>.method .get |>.uri! "/"
    |>.header! "Host" "example.com" |>.empty
  let p ← sendInBackground agent req

  let firstBytes ← drainRequest mockClient
  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "0"), ("Connection", "close")] "")

  match ← await p.result! with
  | Except.error e => throw (IO.userError s!"agent error: {e}")
  | Except.ok _ => pure ()

  let reqText := String.fromUTF8! firstBytes
  unless reqText.toLower.contains "user-agent:" do
    throw <| IO.userError
      s!"default User-Agent must be present:\n{reqText.quote}"

-- ============================================================
-- Section 13 — Streaming request body uses chunked encoding
-- ============================================================
-- A request body whose size is not known in advance (`.stream`) must be framed
-- with `Transfer-Encoding: chunked`, not a bogus Content-Length.

#eval show IO _ from runWithTimeout "stream body uses Transfer-Encoding: chunked" 4000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let agent ← mkAgent mockServer

  let req ← Request.new |>.method .post |>.uri! "/upload"
    |>.header! "Host" "example.com"
    |>.stream (fun out => do
      out.send (Chunk.ofByteArray "part-1".toUTF8)
      out.send (Chunk.ofByteArray "part-2".toUTF8)
      out.close)
  let p ← sendInBackground agent req

  let firstBytes ← drainRequest mockClient
  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "2"), ("Connection", "close")] "ok")

  match ← await p.result! with
  | Except.error e => throw (IO.userError s!"agent error: {e}")
  | Except.ok _ => pure ()

  let reqText := String.fromUTF8! firstBytes
  let lower := reqText.toLower
  unless lower.contains "transfer-encoding: chunked" do
    throw <| IO.userError
      s!"stream body must use chunked encoding:\n{reqText.quote}"
  if lower.contains "content-length:" then
    throw <| IO.userError
      s!"stream body must NOT have Content-Length:\n{reqText.quote}"
  -- The chunked body must carry both parts and end with the zero chunk.
  unless lower.endsWith "0\r\n\r\n" do
    throw <| IO.userError
      s!"chunked body must terminate with 0\\r\\n\\r\\n:\n{reqText.quote}"
  unless reqText.contains "part-1" && reqText.contains "part-2" do
    throw <| IO.userError
      s!"chunked body must contain all streamed parts:\n{reqText.quote}"
