/-
Copyright (c) 2025 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Sofia Rodrigues
-/
module

prelude
public import Std.Time
public import Std.Internal.Http.Protocol.H1

public section

/-!
# Config

This module exposes the `Config` structure describing timeouts, connection,
and header configurations for an HTTP client.
-/

namespace Std.Http.Client

set_option linter.all true

/--
Client connection configuration with validation.
-/
structure Config where
  /--
  Maximum number of requests per connection (for keep-alive).
  -/
  maxRequestsPerConnection : Nat := 1000

  /--
  Maximum number of headers allowed per response.
  -/
  maxResponseHeaders : Nat := 200

  /--
  Maximum size of a single header name in bytes.
  -/
  maxHeaderNameSize : Nat := 256

  /--
  Maximum size of a single header value in bytes.
  -/
  maxHeaderValueSize : Nat := 16384

  /--
  Maximum waiting time for additional data before timing out.
  -/
  readTimeout : Time.Millisecond.Offset := 30000

  /--
  Timeout duration for keep-alive connections.
  -/
  keepAliveTimeout : { x : Time.Millisecond.Offset // 0 < x } := ⟨4000, by decide⟩

  /--
  Timeout for the request lifecycle (send + receive) per connection.
  DNS resolution and TCP connect are not covered by this timeout.
  -/
  requestTimeout : { x : Time.Millisecond.Offset // 0 < x } := ⟨120000, by decide⟩

  /--
  Whether to enable keep-alive connections.
  -/
  enableKeepAlive : Bool := true

  /--
  Maximum number of bytes to receive in a single read call.
  -/
  maxRecvChunkSize : Nat := 16384

  /--
  Default buffer size for request payloads.
  -/
  defaultRequestBufferSize : Nat := 16384

  /--
  The user-agent string to send by default.
  -/
  userAgent : Option Header.Value := some (.mk "lean-http/1.1")

  /--
  Maximum number of redirects to follow automatically.
  Set to 0 to disable automatic redirect following.
  -/
  maxRedirects : Nat := 10

  /--
  Maximum number of times to retry a request after a connection error.
  Set to 0 to disable automatic retries.
  -/
  maxRetries : Nat := 3

  /--
  Base delay in milliseconds for exponential backoff between retry attempts.
  The actual delay for attempt `n` (0-indexed) is `min(retryDelay * 2^n, 32000)`.
  -/
  retryDelay : Time.Millisecond.Offset := 1000

  /--
  Optional HTTP proxy address as `(host, port)`.
  When set, all TCP connections are routed through this proxy and
  request URIs are rewritten to absolute-form (`GET http://host/path HTTP/1.1`).
  -/
  proxy : Option (String × UInt16) := none

  /--
  Maximum number of bytes allowed in a single response body.
  When `some n`, reading more than `n` bytes from the body resolves the current
  request with an error and closes the connection.
  `none` (default) imposes no limit.
  -/
  maxResponseBodySize : Option Nat := none

  /--
  Optional predicate that decides whether a response status is acceptable.
  When `none`, all status codes are accepted (no error is thrown).
  When `some f`, the final response status is passed to `f`; if `f` returns `false`
  an `IO.Error` is thrown with the numeric status code.
  Only applied to the final (non-redirect) response, not intermediate `3xx` responses.

  Example — reject anything outside 2xx:
  ```lean
  validateStatus := some (fun s => s.toCode / 100 == 2)
  ```
  -/
  validateStatus : Option (Status → Bool) := none

  /--
  Maximum number of bytes drained from an intermediate redirect response body before
  -/
  redirectBodyDrainLimit : Nat := 1024 * 1024

  /--
  Optional predicate called before following each redirect.
  -/
  redirectPolicy : Option (URI.Host → UInt16 → Bool) := none

namespace Config

/--
Convert this client config into an HTTP/1.1 protocol configuration.
-/
def toH1Config (config : Config) : Std.Http.Protocol.H1.Config :=
  { maxMessages := config.maxRequestsPerConnection
    maxHeaders := config.maxResponseHeaders
    maxHeaderNameLength := config.maxHeaderNameSize
    maxHeaderValueLength := config.maxHeaderValueSize
    enableKeepAlive := config.enableKeepAlive
    agentName := config.userAgent
  }

end Config
end Std.Http.Client
