import Std.Internal.Http.Test.Helpers

open Std.Internal.IO Async
open Std Http Internal Test

/-!
# HTTP Server Edge-Case Tests

Server-side counterparts to the client edge cases in `async_http_client_edge.lean`:

1. Client closes mid-upload → handler's `readAll` must surface an error (mirror
   of the client "server close mid-body" test).
2. HEAD request: handler returns a body, server must strip it from the wire and
   keep the connection reusable.
3. 204 No Content handler response, followed by a second request on the same
   keep-alive connection.
4. Chunked request body delivered to the handler with all parts intact.
5. Sequential mixed-method pipeline: GET, POST (body), HEAD — all complete in
   order on one keep-alive connection.
6. Default `Server` header is injected.
7. `OPTIONS *` request-target parses and is dispatched to the handler.
-/

private def checkH {σ : Type} [Std.Http.Server.Handler σ]
    (name : String)
    (raw : String)
    (handler : σ)
    (expect : ByteArray → IO Unit)
    (config : Config := defaultConfig) : IO Unit := do
  let (client, server) ← Mock.new
  let response ← Async.block do
    client.send raw.toUTF8
    Std.Http.Server.serveConnection server handler config |>.run
    return (← client.recv?).getD .empty

  try expect response
  catch e => throw (IO.userError s!"[{name}] {e}")

-- ============================================================
-- Section 1 — Client closes mid-upload
-- ============================================================
-- With `Content-Length: 10` declared but only 3 bytes sent, the handler's
-- `readAll` must error so a caller cannot confuse a truncated upload with a
-- complete 3-byte body.

#eval show IO _ from Async.block do
  let (client, server) ← Mock.new
  let sawError ← IO.mkRef false

  let handler : TestHandler := fun req => do
    let _ : String ← try
        let s ← req.body.readAll
        pure s
      catch _ =>
        sawError.set true
        pure ""
    Response.ok |>.text "done"

  -- Send headers + 3 of 10 bytes, then close the client's send channel.
  client.send "POST /upload HTTP/1.1\r\nHost: example.com\r\nContent-Length: 10\r\nConnection: close\r\n\r\n".toUTF8
  client.send "abc".toUTF8
  client.getSendChan.close

  Std.Http.Server.serveConnection server handler defaultConfig |>.run

  unless ← sawError.get do
    throw <| IO.userError
      "handler's readAll silently returned truncated body instead of erroring"

-- ============================================================
-- Section 2 — HEAD request: response body is stripped
-- ============================================================
-- The handler returns a response carrying a `text/plain` body, but because the
-- request method is HEAD the server must suppress body bytes on the wire
-- (RFC 9110 §9.3.2) while keeping the `Content-Length` header. Keep-alive on a
-- follow-up request must still work.

#eval runGroup "HEAD: body stripped but framing preserved" do
  check "HEAD: handler body omitted, Content-Length preserved"
    (raw := "HEAD /doc HTTP/1.1\x0d\nHost: example.com\x0d\nConnection: close\x0d\n\x0d\n")
    (handler := fun _ => Response.ok |>.text "lots-of-bytes")
    (expect := fun r =>
      assertStatus r "HTTP/1.1 200" *>
      assertContains r "Content-Length: 13" *>
      assertAbsent r "lots-of-bytes")

  check "HEAD then GET on keep-alive: both responses delivered"
    (raw :=
      "HEAD /first HTTP/1.1\x0d\nHost: example.com\x0d\n\x0d\n" ++
      "GET /second HTTP/1.1\x0d\nHost: example.com\x0d\nConnection: close\x0d\n\x0d\n")
    (handler := fun req =>
      if req.line.method == .head then
        Response.ok |>.text "head-payload"
      else
        Response.ok |>.text "get-payload")
    (expect := fun r =>
      assertResponseCount r 2 *>
      assertAbsent r "head-payload" *>
      assertContains r "get-payload")

-- ============================================================
-- Section 3 — 204 No Content keep-alive
-- ============================================================
-- A handler returning 204 must not put body bytes on the wire, and a follow-up
-- request on the same keep-alive connection must succeed.

#eval runGroup "204: keep-alive" do
  check "204 followed by GET on keep-alive"
    (raw :=
      "DELETE /item/1 HTTP/1.1\x0d\nHost: example.com\x0d\n\x0d\n" ++
      "GET /after HTTP/1.1\x0d\nHost: example.com\x0d\nConnection: close\x0d\n\x0d\n")
    (handler := fun req =>
      if req.line.method == .delete then
        Response.withStatus .noContent |>.empty
      else
        Response.ok |>.text "after")
    (expect := fun r =>
      assertResponseCount r 2 *>
      assertContains r "HTTP/1.1 204" *>
      assertContains r "after")

-- ============================================================
-- Section 4 — Chunked request body
-- ============================================================
-- A client uploading with `Transfer-Encoding: chunked` must have every chunk
-- byte delivered to the handler's body stream.

#eval runGroup "chunked request body" do
  check "chunked POST: handler sees full reassembled body"
    (raw := mkChunked "/c"
      (chunk "Hello," ++ chunk " " ++ chunk "World!" ++ chunkEnd)
      "Connection: close\x0d\n")
    (handler := echoHandler)
    (expect := fun r =>
      assertStatus r "HTTP/1.1 200" *>
      assertContains r "Hello, World!")

  check "chunked POST with zero-size first chunk: empty body delivered"
    (raw := mkChunked "/empty" chunkEnd "Connection: close\x0d\n")
    (handler := echoHandler)
    (expect := fun r =>
      assertStatus r "HTTP/1.1 200" *>
      -- The response has Content-Length: 0 for an empty echo.
      assertContains r "Content-Length: 0")

-- ============================================================
-- Section 5 — Sequential mixed-method keep-alive
-- ============================================================
-- Pipeline GET /a, POST /b with Content-Length body, HEAD /c on the same
-- connection. All three must be served in order.

#eval runGroup "sequential mixed-method keep-alive" do
  check "GET, POST, HEAD pipelined → 3 responses"
    (raw :=
      "GET /a HTTP/1.1\x0d\nHost: example.com\x0d\n\x0d\n" ++
      "POST /b HTTP/1.1\x0d\nHost: example.com\x0d\nContent-Length: 5\x0d\n\x0d\nhello" ++
      "HEAD /c HTTP/1.1\x0d\nHost: example.com\x0d\nConnection: close\x0d\n\x0d\n")
    (handler := fun (req : Request Body.Stream) => do
      let body : String ← req.body.readAll
      Response.ok |>.text s!"{toString req.line.uri}:{body}")
    (expect := fun r =>
      assertResponseCount r 3 *>
      assertContains r "/a:" *>
      assertContains r "/b:hello" *>
      -- HEAD path: response includes the Content-Length for /c: but no body bytes
      -- for the HEAD response. We still see "/b:hello" (from the POST response
      -- body), and the HEAD's Content-Length header references "/c:" length.
      assertContains r "HTTP/1.1 200")

-- ============================================================
-- Section 6 — Default Server header
-- ============================================================
-- When `serverName` is the default and the handler does not set `Server`,
-- the response must include `Server: LeanHTTP/1.1`.

#eval runGroup "default Server header" do
  check "default config injects Server: LeanHTTP/1.1"
    (raw := mkGetClose "/")
    (handler := fun _ => Response.ok |>.text "ok")
    (expect := fun r => assertContains r "Server: LeanHTTP/1.1")

  check "serverName: none suppresses Server header"
    (raw := mkGetClose "/")
    (handler := fun _ => Response.ok |>.text "ok")
    (config := { defaultConfig with serverName := none })
    (expect := fun r =>
      assertStatus r "HTTP/1.1 200" *>
      assertAbsent r "Server:")

-- ============================================================
-- Section 7 — OPTIONS * request-target
-- ============================================================
-- RFC 9110 §9.3.7: `OPTIONS *` is valid only for OPTIONS. The server must
-- dispatch it to the handler, not reject as malformed.

#eval runGroup "OPTIONS * target" do
  check "OPTIONS * → handler sees asteriskForm target"
    (raw := "OPTIONS * HTTP/1.1\x0d\nHost: example.com\x0d\nConnection: close\x0d\n\x0d\n")
    (handler := fun req =>
      match req.line.uri with
      | .asteriskForm => Response.ok |>.text "star"
      | _ => Response.ok |>.text "other")
    (expect := fun r =>
      assertStatus r "HTTP/1.1 200" *>
      assertContains r "star")

  check "OPTIONS / → handler sees originForm target"
    (raw := "OPTIONS / HTTP/1.1\x0d\nHost: example.com\x0d\nConnection: close\x0d\n\x0d\n")
    (handler := fun req =>
      match req.line.uri with
      | .asteriskForm => Response.ok |>.text "star"
      | _ => Response.ok |>.text "other")
    (expect := fun r =>
      assertStatus r "HTTP/1.1 200" *>
      assertContains r "other")

  -- Non-OPTIONS with * target is malformed (isValidRequestTargetForMethod rejects).
  check "GET * → 400"
    (raw := "GET * HTTP/1.1\x0d\nHost: example.com\x0d\nConnection: close\x0d\n\x0d\n")
    (handler := okHandler)
    (expect := fun r => assertStatus r "HTTP/1.1 400")
