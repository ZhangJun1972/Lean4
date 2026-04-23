/-
Copyright (c) 2026 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Sofia Rodrigues
-/
module

prelude
import Init.Data.String
public import Std.Internal.Parsec
public import Std.Internal.Parsec.ByteArray
public import Std.Internal.Http.Internal.Char

public section

/-!
# Cookie Parser

This module provides a `Set-Cookie` response-header parser following RFC 6265 §4.1. The
`parseSetCookie` combinator returns a `Parsed` structure with raw `String` fields; callers are
responsible for validating cookie-name and cookie-value semantics (e.g. via `Cookie.Name.ofString?`
and `Cookie.Value.ofString?`).

On parse failure the cookie is silently discarded per RFC 6265 §5.2.

Reference: https://www.rfc-editor.org/rfc/rfc6265#section-4.1
-/

namespace Std.Http.Cookie.Parser

set_option linter.all true

open Std Internal Parsec ByteArray Internal.Char

/-
cookie-octet = %x21 / %x23-2B / %x2D-3A / %x3C-5B / %x5D-7E
             ; US-ASCII visible characters excluding SP, DQUOTE,
             ; comma, semicolon, and backslash.
             ; Reference: https://www.rfc-editor.org/rfc/rfc6265#section-4.1.1
-/
@[inline]
private def isCookieOctetByte (c : UInt8) : Bool :=
  c == 0x21 ||
  (0x23 ≤ c && c ≤ 0x2B) ||
  (0x2D ≤ c && c ≤ 0x3A) ||
  (0x3C ≤ c && c ≤ 0x5B) ||
  (0x5D ≤ c && c ≤ 0x7E)

/-
av-octet = %x20-3A / %x3C-7E
         ; any CHAR except CTLs or ";"
         ; Reference: https://www.rfc-editor.org/rfc/rfc6265#section-4.1.1
-/
@[inline]
private def isAvOctetByte (c : UInt8) : Bool :=
  (0x20 ≤ c && c ≤ 0x3A) || (0x3C ≤ c && c ≤ 0x7E)

/-
token = 1*tchar
tchar = "!" / "#" / "$" / "%" / "&" / "'" / "*" / "+" / "-" / "." /
        "^" / "_" / "`" / "|" / "~" / DIGIT / ALPHA
      ; Reference: https://www.rfc-editor.org/rfc/rfc9110#section-5.6.2
-/
@[inline]
private def parseToken (limit : Nat) : Parser ByteSlice :=
  takeWhile1AtMost (fun c => tchar (Char.ofUInt8 c)) limit

/--
Parsed result of a `Set-Cookie` header value, prior to semantic validation.

Cookie-name and cookie-value are raw strings that callers must validate
(e.g. via `Cookie.Name.ofString?` and `Cookie.Value.ofString?`).

- `domain`: the `Domain` attribute value with any leading `.` already stripped;
  `none` if the attribute is absent.
- `path`: the `Path` attribute value (guaranteed to start with `/`);
  `none` if the attribute is absent or does not start with `/`.
- `secure`: `true` when the `Secure` attribute is present.
- `httpOnly`: `true` when the `HttpOnly` attribute is present.
-/
structure Parsed where

  /--
  Raw cookie name (an HTTP token).
  -/
  name : String

  /--
  Raw cookie value (`*cookie-octet` or double-quoted).
  -/
  value  : String

  /--
  `Domain` attribute value with any leading `.` stripped, or `none` if absent.
  -/
  domain : Option String

  /--
  `Path` attribute value starting with `/`, or `none` if absent or invalid.
  -/
  path : Option String

  /--
  `true` when the `Secure` attribute is present.
  -/
  secure : Bool

  /-- `true` when the `HttpOnly` attribute is present. -/
  httpOnly : Bool

  /-- `Max-Age` attribute value in seconds, or `none` if absent or unparseable.
      Values ≤ 0 signal cookie deletion per RFC 6265 §5.2.2. -/
  maxAge : Option Int := none

  /-- Raw `Expires` attribute value (an HTTP-date), or `none` if absent.
      Callers parse this when resolving the cookie's absolute expiration time;
      if both `Max-Age` and `Expires` are present, RFC 6265 §5.3 mandates that
      `Max-Age` takes precedence. -/
  expires : Option String := none

-- cookie-name = token
private def parseCookieName : Parser String := do
  let bytes ← parseToken 4096

  let some str := String.fromUTF8? bytes.toByteArray
    | fail "invalid cookie name encoding"

  return str

/-
cookie-value = *cookie-octet / ( DQUOTE *cookie-octet DQUOTE )
-/
private def parseCookieValue : Parser String := do
  let bytes ←
    if (← peekWhen? (· == '"'.toUInt8)).isSome then
      skipByte '"'.toUInt8
      let inner ← takeWhileAtMost isCookieOctetByte 4096
      skipByte '"'.toUInt8
      pure inner
    else
      takeWhileAtMost isCookieOctetByte 4096
  let some str := String.fromUTF8? bytes.toByteArray
    | fail "invalid cookie value encoding"
  return str

-- av-name = token (parsed case-insensitively)
private def parseAttrName : Parser String := do
  let bytes ← takeWhileAtMost (fun c => tchar (Char.ofUInt8 c)) 256
  return (String.fromUTF8! bytes.toByteArray).toLower

-- av-value = *av-octet
private def parseAttrValue : Parser String := do
  let bytes ← takeWhileAtMost isAvOctetByte 4096
  let some str := String.fromUTF8? bytes.toByteArray
    | fail "invalid attribute value encoding"
  return str

/-
cookie-av   = expires-av / max-age-av / domain-av / path-av / secure-av /
              httponly-av / extension-av
domain-av   = "Domain=" domain-value
domain-value = <subdomain>         ; as per RFC 1034, Section 3.5
path-av     = "Path=" path-value
path-value  = *av-octet
secure-av   = "Secure"
httponly-av = "HttpOnly"
extension-av = *av-octet
-/
private def parseCookieAv : Parser (String × Option String) := do
  let name  ← parseAttrName
  let value ← optional (attempt (skipByte '='.toUInt8 *> parseAttrValue))
  return (name, value)

/-
set-cookie-string = cookie-pair *( ";" SP cookie-av )
cookie-pair       = cookie-name "=" cookie-value
-/

/--
Parses a `Set-Cookie` header value and returns a `Parsed` result.

Attribute processing follows RFC 6265 §5.2:
- `Domain`: leading `.` is stripped; invalid domain strings set `domain` to `none`.
- `Path`: values not starting with `/` set `path` to `none` (caller uses the default `/`).
- `Secure`: sets `secure` to `true` regardless of whether a value follows the attribute name.
- `HttpOnly`: sets `httpOnly` to `true`.
- `Max-Age`: parsed as a signed integer number of seconds; see `Parsed.maxAge`.
- `Expires`: preserved as its raw HTTP-date string; see `Parsed.expires`.
- All other attributes (including `SameSite`) are ignored.
-/
def parseSetCookie : Parser Parsed := do
  let name  ← parseCookieName
  skipByte '='.toUInt8
  let value ← parseCookieValue

  -- *( ";" SP cookie-av )
  let attrs ← many (attempt do
    skipByte ';'.toUInt8
    let _ ← optional (skipByte ' '.toUInt8)
    parseCookieAv)

  let mut domain : Option String := none
  let mut path : Option String := none
  let mut secure := false
  let mut httpOnly := false
  let mut maxAge : Option Int := none
  let mut expires : Option String := none

  for (attrName, attrVal) in attrs do
    match attrName with
    | "domain" =>
      let v := (attrVal.getD "").trimAscii.toString
      -- RFC 6265 §5.2.3: ignore a leading U+002E FULL STOP character
      let v := if v.startsWith "." then (v.drop 1).toString else v
      if !v.isEmpty then domain := some v
    | "path" =>
      let v := (attrVal.getD "").trimAscii.toString
      -- RFC 6265 §5.2.4: if av-value is empty or does not start with "/", use default
      if !v.isEmpty && v.startsWith "/" then path := some v
    | "secure" => secure := true
    | "httponly" => httpOnly := true
    | "max-age" =>
      -- RFC 6265 §5.2.2: parse an optional leading '-' followed by one or more digits.
      if let some v := attrVal then
        let s := v.trimAscii.toString
        let (neg, digits) := if s.startsWith "-" then (true, s.drop 1) else (false, s)
        if !digits.isEmpty && digits.all Char.isDigit then
          let absVal : Nat := digits.foldl (fun acc c => acc * 10 + (c.toNat - '0'.toNat)) 0
          maxAge := some (if neg then -(absVal : Int) else (absVal : Int))
    | "expires" =>
      -- RFC 6265 §5.2.1: keep the raw value; semantic parsing happens later.
      if let some v := attrVal then
        let s := v.trimAscii.toString
        if !s.isEmpty then expires := some s
    | _ => pure ()

  return { name, value, domain, path, secure, httpOnly, maxAge, expires }

end Std.Http.Cookie.Parser
