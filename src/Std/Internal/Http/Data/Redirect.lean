/-
Copyright (c) 2026 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Sofia Rodrigues
-/
module

prelude
public import Std.Internal.Http.Data.Request
public import Std.Internal.Http.Data.Status

public section

/-!
# Redirect planning

Pure HTTP redirect-decision logic split out of the async client so it can be
reused by other agents (tests, CLIs, non-async clients) without pulling in
sockets or the cookie jar.

`decideRedirect` inspects a response-line `Status` and `Location` header and
produces a `RedirectOutcome` describing whether to stop or follow, plus the
full rewrite required by RFC 9110 §15.4 and RFC 9112 §3.2.

The function is pure: body draining and any `resetInPlace` on a replayable
body stay at the call site so this module never touches `IO` or `Async`.

References:
* https://httpwg.org/specs/rfc9110.html#status.3xx
* https://httpwg.org/specs/rfc9112.html#section-3.2
-/

namespace Std.Http

set_option linter.all true

/--
What the caller must do with the body of the original request when following
a redirect.
-/
inductive RedirectBodyAction where
  /--
  Send an empty body on the redirected request. Chosen when the method changes
  (303 See Other, or 301/302 on `POST`) or when the original body cannot be
  replayed.
  -/
  | empty

  /--
  Reset the original body and resend it on the redirected request. Chosen for
  method-preserving redirects (307/308) when the body is marked replayable.
  -/
  | replay
deriving DecidableEq, Repr, Inhabited

/--
The concrete work the caller must perform to follow a redirect.
-/
structure RedirectPlan where
  /--
  Target host for the redirected request.
  -/
  host : URI.Host

  /--
  Target port for the redirected request.
  -/
  port : UInt16

  /--
  Target scheme for the redirected request.
  -/
  scheme : URI.Scheme

  /--
  Rewritten request target put on the wire: origin-form for same-origin
  redirects, absolute-form for cross-origin redirects, with any `userinfo`
  stripped per RFC 9110 §4.2.4.
  -/
  target : RequestTarget

  /--
  Method to use for the redirected request — possibly downgraded to `GET`
  for 301/302 on `POST` or for 303.
  -/
  method : Method

  /--
  Headers for the redirected request after cross-origin and
  method-change scrubbing.
  -/
  headers : Headers

  /--
  What to do with the original request body.
  -/
  bodyAction : RedirectBodyAction

  /--
  Whether the redirect crosses origin boundaries (different host, port, or
  scheme). Useful for credential-handling decisions at the call site.
  -/
  isCrossOrigin : Bool
deriving Repr

/--
Result of evaluating whether to follow a redirect.
-/
inductive RedirectOutcome where
  /--
  Response is final — stop redirecting and return it.
  -/
  | done

  /--
  Follow the redirect described by `plan`.
  -/
  | follow (plan : RedirectPlan)

namespace RedirectOutcome

instance : Inhabited RedirectOutcome := ⟨.done⟩

end RedirectOutcome

namespace RedirectPlan

/--
Computes the `(host, port, scheme)` triple the redirect addresses, folding in
the current origin when the `Location` target does not carry an authority.
-/
private def resolveOrigin
    (currentHost : URI.Host) (currentPort : UInt16) (currentScheme : URI.Scheme)
    : RequestTarget → URI.Host × UInt16 × URI.Scheme
  | .absoluteForm af =>
    let h := af.authority.map URI.Authority.host |>.getD currentHost
    let p : UInt16 :=
      match af.authority with
      | some auth =>
        match auth.port with
        | .value v => v
        | _ => URI.Scheme.defaultPort af.scheme
      | none => URI.Scheme.defaultPort af.scheme
    (h, p, af.scheme)
  | _ => (currentHost, currentPort, currentScheme)

/--
Computes the method for the redirected request per RFC 9110 §15.4:
303 always becomes GET, 301/302 downgrade POST to GET, everything else keeps
the original method.
-/
private def chooseMethod (originalMethod : Method) : Status → Method
  | .seeOther => .get
  | .movedPermanently | .found =>
      if originalMethod == .post then .get else originalMethod
  | _ => originalMethod

/--
Strips headers that must not survive a cross-origin hop or a method-changing
redirect. `Authorization`, `Proxy-Authorization`, and `Cookie` never cross
origins; `Content-Type`/`Content-Length` are dropped when the method changes
because the redirected request will carry no body.
-/
private def scrubHeaders (headers : Headers) (isCrossOrigin methodChanged : Bool) : Headers :=
  let afterOrigin :=
    if isCrossOrigin then
      headers
        |>.erase Header.Name.authorization
        |>.erase Header.Name.proxyAuthorization
        |>.erase Header.Name.cookie
    else headers
  if methodChanged then
    afterOrigin
      |>.erase Header.Name.contentType
      |>.erase Header.Name.contentLength
  else afterOrigin

/--
Rewrites the `Host` header for a cross-origin redirect. The redirected
request is dispatched on a fresh connection to `(scheme, host, port)`; the
original `Host` would route the request to the wrong virtual host.

Only rewrites when the original request already carried a `Host` header, so
callers who intentionally omitted it (e.g. HTTP/1.0 tests) are left alone.
-/
private def rewriteHostHeader (headers : Headers)
    (scheme : URI.Scheme) (host : URI.Host) (port : UInt16) : Headers :=
  if headers.contains Header.Name.host then
    let defaultPort := URI.Scheme.defaultPort scheme
    let hostValue :=
      if port == defaultPort then toString host
      else s!"{host}:{port}"
    headers.insert Header.Name.host (Header.Value.ofString! hostValue)
  else headers

/--
Rewrites the target actually placed on the wire. Strips any `userinfo` from
an absolute-form target per RFC 9110 §4.2.4, and collapses a same-origin
absolute-form target back to origin-form so direct (non-proxy) hops stay
RFC 9112 compliant.
-/
private def rewriteTarget (target : RequestTarget) (isCrossOrigin : Bool) : RequestTarget :=
  match target with
  | .absoluteForm af =>
    let stripped :=
      { af with authority := af.authority.map (fun auth => { auth with userInfo := none }) }
    if isCrossOrigin then
      .absoluteForm stripped
    else
      .originForm stripped.path
        (if stripped.query.isEmpty then none else some stripped.query)
  | _ => target

end RedirectPlan

/--
Decides whether to follow a redirect given the server's response-line status
and headers, the pending request, and whether the request body is replayable.

Returns `.done` when:
* `remaining` reached zero,
* the status is not a 3xx redirection,
* no `Location` header is present, or
* the `Location` value does not parse as a `RequestTarget`, or
* the target resolves to a non-`http(s)` scheme (SSRF guard).

Returns `.follow plan` otherwise. The caller is expected to drain the
redirect response body and, when `plan.bodyAction == .replay`, reset the
original body before dispatching the rewritten request.
-/
def decideRedirect
    (remaining : Nat)
    (currentHost : URI.Host) (currentPort : UInt16) (currentScheme : URI.Scheme)
    (request : Request.Head) (bodyReplayable : Bool)
    (status : Status) (responseHeaders : Headers)
    : RedirectOutcome := Id.run do

  if remaining == 0 ∨ !status.isRedirection then
    return .done

  let some locationValue := responseHeaders.get? .location
    | return .done

  let some target := RequestTarget.parse? locationValue.value
    | return .done

  let newMethod := RedirectPlan.chooseMethod request.method status

  let (newHost, newPort, newScheme) :=
    RedirectPlan.resolveOrigin currentHost currentPort currentScheme target

  if newScheme.val != "http" && newScheme.val != "https" then
    return .done

  let isCrossOrigin :=
    newHost != currentHost || newPort != currentPort || newScheme != currentScheme

  let methodChanged := newMethod != request.method

  let scrubbed := RedirectPlan.scrubHeaders request.headers isCrossOrigin methodChanged
  let newHeaders :=
    if isCrossOrigin then
      RedirectPlan.rewriteHostHeader scrubbed newScheme newHost newPort
    else scrubbed

  -- RFC 9110 §15.4.8: for method-preserving redirects (307/308), if the body cannot be
  -- replayed, the user agent MUST NOT automatically redirect.
  if !methodChanged && newMethod != .get && newMethod != .head && !bodyReplayable then
    return .done

  let bodyAction : RedirectBodyAction :=
    if newMethod == .get || newMethod == .head || methodChanged then
      .empty
    else
      .replay  -- bodyReplayable is true here (non-replayable case returned .done above)

  let rewrittenTarget := RedirectPlan.rewriteTarget target isCrossOrigin

  return .follow {
    host := newHost
    port := newPort
    scheme := newScheme
    target := rewrittenTarget
    method := newMethod
    headers := newHeaders
    bodyAction := bodyAction
    isCrossOrigin := isCrossOrigin
  }

end Std.Http
