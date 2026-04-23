import Std.Internal.Http
import Std.Internal.Async
import Std.Internal.Async.Timer

open Std.Internal.IO Async
open Std Http Internal

/-!
# HTTP Client Redirect Tests

Tests for redirect behavior of the HTTP client:

- Streaming request body must NOT be forwarded to the redirect target.
  A 302 redirect changes POST → GET; the original body is a stream that has
  already been (or is being) sent on the first connection.  Forwarding it to the
  redirect target would (a) send garbage bytes on a GET and (b) leak data that
  the caller did not intend to share with the redirect destination.
-/

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

-- ============================================================
-- Redirect: streaming body NOT forwarded on 302 (POST → GET)
-- ============================================================
-- A POST with a streaming body receives a 302 Found redirect.  The client must
-- follow the redirect as GET /redirected (RFC 9110 §15.4.3) and must NOT
-- include the original streaming body in the redirect request.
--
-- This matters because:
--   1. The body is a live stream — consuming it on the redirect would steal
--      data intended for the original endpoint.
--   2. A GET request must not carry a body (RFC 9110 §9.3.1).
--   3. The stream has already been (partially) sent; retransmitting whatever
--      bytes remain would produce a malformed or empty body at the new target.
-- ============================================================

#eval show IO _ from runWithTimeout "streaming body not sent on 302 redirect" 3000 <| Async.block do
  let (mockClient, mockServer) ← Mock.new
  let session ← Client.Session.new mockServer (config := {})
  let cookieJar ← Cookie.Jar.new
  let some domain := URI.DomainName.ofString? "example.com"
    | throw (IO.userError "DomainName parse failed")

  let agent : Client.Agent Mock.Server := {
    session
    scheme := URI.Scheme.ofString! "http"
    host := .name domain
    port := 80
    cookieJar
  }

  -- POST with a streaming body.
  let request ← Request.new
    |>.method .post
    |>.uri! "/upload"
    |>.header! "Host" "example.com"
    |>.stream (fun out => do
        out.send (Chunk.ofByteArray "secret-payload".toUTF8)
        out.close)

  let resultPromise : IO.Promise (Except String (Response Body.Stream)) ← IO.Promise.new

  background do
    let result ← try
        let resp ← Client.Agent.send agent request
        pure (Except.ok resp)
      catch e => pure (Except.error (toString e))
    discard <| resultPromise.resolve result

  -- First request: drain the POST body completely before replying with 302.
  -- Accept chunked (ends with "0\r\n\r\n") or fixed-length (ends with body bytes).
  let mut firstBytes := ByteArray.empty
  repeat
    let some chunk ← mockClient.recv?
      | throw (IO.userError "Test failed: connection closed before first request")
    firstBytes := firstBytes ++ chunk
    let t := String.fromUTF8! firstBytes
    if t.endsWith "0\r\n\r\n" || t.endsWith "secret-payload" then break
  mockClient.send (rawResp "302 Found"
    #[("Location", "/redirected"),
      ("Content-Length", "0"),
      ("Connection", "keep-alive")] "")

  -- Second request: the redirect.  Must be GET /redirected with no body.
  let some redirectBytes ← mockClient.recv?
    | throw (IO.userError "Test failed: no redirect request received")
  mockClient.send (rawResp "200 OK"
    #[("Content-Length", "2"), ("Connection", "close")] "ok")

  match ← await resultPromise.result! with
  | Except.error e => throw (IO.userError s!"agent error: {e}")
  | Except.ok _ => pure ()

  let redirectText := String.fromUTF8! redirectBytes

  -- The redirect must use GET.
  unless redirectText.startsWith "GET " do
    throw <| IO.userError
      s!"Test 'streaming body not sent on 302 redirect' FAILED: \
         expected GET request, got:\n{redirectText.quote}"

  -- The redirect target must be /redirected.
  unless redirectText.contains "GET /redirected" do
    throw <| IO.userError
      s!"Test 'streaming body not sent on 302 redirect' FAILED: \
         expected GET /redirected, got:\n{redirectText.quote}"

  -- The streaming body must not appear in the redirect request.
  if redirectText.contains "secret-payload" then
    throw <| IO.userError
      s!"Test 'streaming body not sent on 302 redirect' FAILED: \
         streaming body 'secret-payload' present in redirect request\n{redirectText.quote}"
