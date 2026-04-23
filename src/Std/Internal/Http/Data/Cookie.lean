/-
Copyright (c) 2026 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Sofia Rodrigues
-/
module

prelude
public import Std.Sync.Mutex
public import Std.Internal.Http.Data.URI
public import Std.Internal.Http.Data.Cookie.Parser
public import Std.Internal.Http.Data.Headers
public import Init.Data.String
public import Init.Data.Array.Basic
public import Init.Data.List.Basic
public import Std.Time

public section

/-!
# Cookie

This module defines the `Cookie` and `Jar` types, a minimal RFC 6265-compliant
implementation for managing HTTP cookies.

Cookies are parsed from `Set-Cookie` response headers, stored in a thread-safe jar, and
injected as a `Cookie` request header on outgoing requests.

Supported `Set-Cookie` attributes: `Domain`, `Path`, `Secure`, `HttpOnly`,
`Max-Age`, `Expires` (in IMF-fixdate form).

When both `Max-Age` and `Expires` are present, `Max-Age` wins (RFC 6265 §5.3).
Cookies whose resolved expiration has already passed are never stored, and
cookies selected by `cookiesFor` are filtered against the current wall-clock
time so expired entries are never sent on outgoing requests.

Unsupported: `SameSite`.

Reference: https://www.rfc-editor.org/rfc/rfc6265
-/

namespace Std.Http

set_option linter.all true

open Internal Char

namespace Cookie

/--
Proposition asserting that a string is a valid cookie name: a non-empty HTTP token.
Cookie names are case-sensitive.

Reference: https://www.rfc-editor.org/rfc/rfc6265#section-4.1.1
-/
abbrev IsValidCookieName (s : String) : Prop :=
  isToken s

/--
A validated HTTP cookie name. Cookie names are case-sensitive HTTP tokens.

Reference: https://www.rfc-editor.org/rfc/rfc6265#section-4.1.1
-/
@[ext]
structure Name where
  /--
  The cookie name string.
  -/
  value : String

  /--
  Proof that the name is a valid HTTP token.
  -/
  isValidCookieName : IsValidCookieName value := by decide
deriving BEq, DecidableEq, Repr

namespace Name

instance : Inhabited Name where
  default := ⟨"_", by decide⟩

/--
Attempts to create a `Cookie.Name` from a `String`, returning `none` if the string is
not a valid HTTP token or is empty.
-/
def ofString? (s : String) : Option Name :=
  let val := s.trimAscii.toString
  if h : IsValidCookieName val then
    some ⟨val, h⟩
  else
    none

/--
Creates a `Cookie.Name` from a string, panicking if the string is not a valid HTTP token.
-/
def ofString! (s : String) : Name :=
  match ofString? s with
  | some res => res
  | none => panic! s!"invalid cookie name: {s.quote}"

instance : ToString Name where
  toString n := n.value

end Name

/--
`cookie-octet = %x21 / %x23-2B / %x2D-3A / %x3C-5B / %x5D-7E`

US-ASCII visible characters excluding SP, DQUOTE, comma, semicolon, and backslash.

Reference: https://www.rfc-editor.org/rfc/rfc6265#section-4.1.1
-/
def isCookieOctet (c : Char) : Bool :=
  c = '!' ∨
  ('#' ≤ c ∧ c ≤ '+') ∨
  ('-' ≤ c ∧ c ≤ ':') ∨
  ('<' ≤ c ∧ c ≤ '[') ∨
  (']' ≤ c ∧ c ≤ '~')

/--
Proposition asserting that a string is a valid cookie value: all characters are
`cookie-octet` characters. Empty values are permitted.

Reference: https://www.rfc-editor.org/rfc/rfc6265#section-4.1.1
-/
abbrev IsValidCookieValue (s : String) : Prop :=
  s.toList.all isCookieOctet

/--
A validated HTTP cookie value. Empty values are permitted.

Reference: https://www.rfc-editor.org/rfc/rfc6265#section-4.1.1
-/
@[ext]
structure Value where
  /--
  The cookie value string.
  -/
  value : String

  /--
  Proof that the value contains only valid cookie-octet characters.
  -/
  isValidCookieValue : IsValidCookieValue value := by decide
deriving BEq, DecidableEq, Repr

namespace Value

instance : Inhabited Value where
  default := ⟨"", by decide⟩

/--
Attempts to create a `Cookie.Value` from a `String`, returning `none` if the string
contains characters not permitted in cookie values.
-/
def ofString? (s : String) : Option Value :=
  let val := s.trimAscii.toString
  if h : IsValidCookieValue val then
    some ⟨val, h⟩
  else
    none

/--
Creates a `Cookie.Value` from a string, panicking if the string contains characters not
permitted in cookie values.
-/
def ofString! (s : String) : Value :=
  match ofString? s with
  | some res => res
  | none => panic! s!"invalid cookie value: {s.quote}"

instance : ToString Value where
  toString v := v.value

end Value

end Cookie

/--
An HTTP cookie with its matching attributes.

Reference: https://www.rfc-editor.org/rfc/rfc6265#section-4.1
-/
structure Cookie where
  /--
  The cookie name.
  -/
  name : Cookie.Name

  /--
  The cookie value.
  -/
  value : Cookie.Value

  /--
  The effective domain for this cookie. When `Set-Cookie` carries no `Domain` attribute this
  equals the origin host and `hostOnly` is `true` — only that exact host will receive the
  cookie. When `Domain` is set, `hostOnly` is `false` and subdomains also match.
  -/
  domain : URI.Host

  /--
  `true` when the cookie must only be sent to the exact origin host (no subdomain matching).
  -/
  hostOnly : Bool

  /--
  Path prefix for which the cookie is valid. Defaults to `"/"`.
  -/
  path : URI.Path

  /--
  When `true` the cookie must only be sent over a secure (HTTPS) channel.
  -/
  secure : Bool

  /--
  When `true` the cookie must not be exposed to non-HTTP APIs.
  Stored for completeness; no client-side script enforcement applies here.
  -/
  httpOnly : Bool

  /--
  Absolute expiration time for this cookie, or `none` for a session cookie that
  persists until the jar is discarded.  Resolved from `Max-Age` (preferred) or
  `Expires` at the time `Set-Cookie` was ingested.  Cookies whose `expires` has
  already passed are filtered out of `cookiesFor`.
  -/
  expires : Option Std.Time.Timestamp

/--
A HTTP cookie jar.

Reference: https://www.rfc-editor.org/rfc/rfc6265#section-5
-/
structure Cookie.Jar where
  private mk ::
  private cookies : Mutex (Array Cookie)

namespace Cookie.Jar

/--
Creates an empty cookie jar.
-/
def new : BaseIO Jar := do
  let cookies ← Mutex.new #[]
  return .mk cookies

/--
Translates a 3-letter month abbreviation (`Jan`, `Feb`, …) as used in IMF-fixdate to the
1-indexed month number. Returns `none` for any other value.
-/
private def monthFromAbbrev : String → Option Nat
  | "Jan" => some 1  | "Feb" => some 2  | "Mar" => some 3
  | "Apr" => some 4  | "May" => some 5  | "Jun" => some 6
  | "Jul" => some 7  | "Aug" => some 8  | "Sep" => some 9
  | "Oct" => some 10 | "Nov" => some 11 | "Dec" => some 12
  | _ => none

/--
Parses an HTTP-date in IMF-fixdate form (RFC 7231 §7.1.1.1), the only format RFC 6265 §5.1.1
permits in `Set-Cookie: Expires=...`, into an absolute `Timestamp`.

Example input: `"Sun, 06 Nov 1994 08:49:37 GMT"`.  Returns `none` when the string does not match
this layout; the obsolete RFC 850 and asctime forms are intentionally not accepted.

Seconds-since-epoch are computed from the civil date via the well-known Howard Hinnant
algorithm, which is valid for any proleptic-Gregorian date representable as an `Int` without
relying on `PlainDate` ordinal constructors (keeping this function pure and runtime-total).
-/
private def parseImfFixdate (s : String) : Option Std.Time.Timestamp := do
  let parts := (s.trimAscii.toString.splitOn " ").filter (!·.isEmpty)
  guard (parts.length == 6)
  let day ← parts[1]!.toNat?
  let month ← monthFromAbbrev parts[2]!
  let year ← parts[3]!.toInt?
  let hms := (parts[4]!).splitOn ":"
  guard (hms.length == 3)
  let hour ← hms[0]!.toNat?
  let minute ← hms[1]!.toNat?
  let second ← hms[2]!.toNat?
  guard (parts[5]! == "GMT")
  guard (1 ≤ month ∧ month ≤ 12)
  guard (1 ≤ day ∧ day ≤ 31)
  guard (hour ≤ 23 ∧ minute ≤ 59 ∧ second ≤ 60)
  let m : Int := month
  let d : Int := day
  let y : Int := if m ≤ 2 then year - 1 else year
  let era : Int := (if y ≥ 0 then y else y - 399) / 400
  let yoe : Int := y - era * 400
  let doy : Int := (153 * (if m > 2 then m - 3 else m + 9) + 2) / 5 + d - 1
  let doe : Int := yoe * 365 + yoe / 4 - yoe / 100 + doy
  let days : Int := era * 146097 + doe - 719468
  let h : Int := hour
  let mi : Int := minute
  let sc : Int := second
  let totalSeconds : Int := days * 86400 + h * 3600 + mi * 60 + sc
  return Std.Time.Timestamp.ofSecondsSinceUnixEpoch (Std.Time.Second.Offset.ofInt totalSeconds)

/--
Domain matching per RFC 6265 §5.1.3.
-/
private def domainMatches (cookieDomain : URI.Host) (hostOnly : Bool) (host : URI.Host) : Bool :=
  if hostOnly then
    host == cookieDomain
  else
    let d := cookieDomain
    host == d || (toString host).endsWith ("." ++ toString d)

/--
Path matching per RFC 6265 §5.1.4.

A request path matches a cookie path when they are identical, or when the cookie path is a
strict segment-wise prefix of the request path. Segment boundaries correspond to `/`, so
`/foo` never prefix-matches `/foobar` (different segments).

A trailing `/` in the cookie path is normalised away before the prefix test; this covers
both RFC conditions:
- cookie-path ends with `/` → its meaningful segments are a strict prefix of request-path.
- first char after prefix is `/` → satisfied automatically at segment boundaries.
-/
private def pathMatches (cookiePath : URI.Path) (requestPath : URI.Path) : Bool :=
  requestPath == cookiePath ||
  let cp :=
    if cookiePath.hasTrailingSlash && !cookiePath.isEmpty
    then cookiePath.segments.pop
    else cookiePath.segments
  requestPath.segments.size > cp.size &&
  requestPath.startsWith { cookiePath with segments := cp }

/--
Parses a single `Set-Cookie` header value and stores the resulting cookie.
`host` is the origin host of the response (used as the effective domain when no
`Domain` attribute is present). `requestPath` is the request path that produced
the response and is used to compute RFC 6265's default-path when the cookie
omits `Path=`.

Resolves the cookie's absolute expiration from `Max-Age` (preferred) or `Expires` at the
current wall-clock time; cookies whose resolved expiration is not in the future are never
stored, and any previously-stored entry with the same `(name, domain, path)` is removed.

Reference: https://www.rfc-editor.org/rfc/rfc6265#section-5.2
-/
private def defaultPath (requestPath : URI.Path) : URI.Path :=
  if !requestPath.absolute || requestPath.segments.isEmpty then
    URI.Path.parseOrRoot "/"
  else
    requestPath.parent

/--
Parses a single `Set-Cookie` header value and stores the resulting cookie.
-/
def processSetCookie (jar : Jar) (host : URI.Host)
    (requestPath : URI.Path) (headerValue : String) : IO Unit := do
  let .ok parsed := Cookie.Parser.parseSetCookie.run headerValue.toUTF8
    | return ()

  let some cookieName  := Cookie.Name.ofString?  parsed.name
    | return ()

  let some cookieValue := Cookie.Value.ofString? parsed.value
    | return ()

  let cookiePath : URI.Path :=
    if let some p := parsed.path then URI.Path.parseOrRoot p
    else defaultPath requestPath

  -- RFC 6265 §5.2.3: resolve domain; missing or invalid Domain → host-only
  let (domain, hostOnly) :=
    match parsed.domain with
    | some d =>
      match URI.DomainName.ofString? d with
      | some name => (URI.Host.name name, false)
      | none      => (host, true)
    | none => (host, true)

  -- RFC 6265 §5.3 step 6: if domain attribute is set, the origin host must domain-match it.
  -- This prevents a server at api.example.com from setting Domain=evil.com or Domain=com.
  if !hostOnly && !domainMatches domain false host then
    return ()

  -- RFC 6265 §5.3: `Max-Age` takes precedence over `Expires` when both are present.
  -- `Max-Age ≤ 0` (or an `Expires` already in the past) signals deletion — drop any
  -- matching cookie and stop before inserting anything.
  let now ← Std.Time.Timestamp.now
  let expiresAt : Option Std.Time.Timestamp :=
    match parsed.maxAge with
    | some n => some (now.addSeconds (Std.Time.Second.Offset.ofInt n))
    | none   => parsed.expires.bind parseImfFixdate

  if let some t := expiresAt then
    if t ≤ now then
      jar.cookies.atomically do
        let cs ← get
        set (cs.filter fun c => !(c.name == cookieName && c.domain == domain && c.path == cookiePath))
      return ()

  let cookie : Cookie := {
    name := cookieName
    value := cookieValue
    domain
    hostOnly
    path := cookiePath
    secure := parsed.secure
    httpOnly := parsed.httpOnly
    expires := expiresAt
  }

  -- Limit the total cookie count to prevent unbounded memory growth.
  -- RFC 6265 §6.1 recommends supporting at least 3000 cookies total.
  let maxCookies := 3000
  jar.cookies.atomically do
    let cs ← get
    let cs := cs.filter fun c => !(c.name == cookie.name && c.domain == cookie.domain && c.path == cookie.path)
    if cs.size < maxCookies then
      set (cs.push cookie)

/--
Returns the `Cookie` header value for all cookies that should be sent for a request to `host`
at `path`. Pass `secure := true` when the request channel is HTTPS. Returns `none` when no
cookies match.

Cookies whose resolved expiration has already passed (per `Cookie.expires`) are excluded
from the result, satisfying RFC 6265 §5.3's requirement that the user agent purge expired
cookies before selecting them for an outgoing request.

Reference: https://www.rfc-editor.org/rfc/rfc6265#section-5.4
-/
def cookiesFor
    (jar : Jar) (host : URI.Host) (path : URI.Path)
    (secure : Bool := false) : IO (Option Header.Value) := do
  let now ← Std.Time.Timestamp.now
  jar.cookies.atomically do
    let cs ← get
    let matching := cs.filter fun c =>
      domainMatches c.domain c.hostOnly host &&
      pathMatches c.path path &&
      (!c.secure || secure) &&
      (match c.expires with | none => true | some t => now < t)
    if matching.isEmpty then
      return none
    else
      return Header.Value.ofString? (String.intercalate "; " (matching.map (fun c => c.name.value ++ "=" ++ c.value.value)).toList)

end Std.Http.Cookie.Jar
