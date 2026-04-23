import Std.Internal.Http.Data.Cookie

open Std.Http

/-!
# Cookie Parser Tests

Tests for `Set-Cookie` header parsing following RFC 6265 §4.1.
-/

-- Helper: parse a Set-Cookie header value, throw on failure.
def parseCookie (s : String) : IO Cookie.Parser.Parsed :=
  IO.ofExcept (Cookie.Parser.parseSetCookie.run s.toUTF8)

-- Helper: assert parsing fails.
def parseShouldFail (label : String) (s : String) : IO Unit := do
  match Cookie.Parser.parseSetCookie.run s.toUTF8 with
  | .ok _ => throw <| IO.userError s!"Test '{label}' failed: expected parse failure but succeeded"
  | .error _ => pure ()

-- ============================================================================
-- Basic cookie-pair
-- ============================================================================

#eval show IO _ from do
  -- Minimal name=value
  let p ← parseCookie "foo=bar"
  unless p.name == "foo" do
    throw <| IO.userError s!"Test 'basic name' failed: expected 'foo', got {p.name.quote}"
  unless p.value == "bar" do
    throw <| IO.userError s!"Test 'basic value' failed: expected 'bar', got {p.value.quote}"
  unless p.domain == none do
    throw <| IO.userError s!"Test 'basic domain absent' failed: expected none, got {repr p.domain}"
  unless p.path == none do
    throw <| IO.userError s!"Test 'basic path absent' failed: expected none, got {repr p.path}"
  unless p.secure == false do
    throw <| IO.userError "Test 'basic secure absent' failed: expected false"

  -- Empty value is allowed (cookie-value = *cookie-octet)
  let pEmpty ← parseCookie "session="
  unless pEmpty.value == "" do
    throw <| IO.userError s!"Test 'empty value' failed: expected '', got {pEmpty.value.quote}"

  -- Numeric name is not a valid token (digits alone are not all tchar? Actually digits ARE tchar)
  -- tchar includes DIGIT, so "123" is a valid token
  let pNum ← parseCookie "123=abc"
  unless pNum.name == "123" do
    throw <| IO.userError s!"Test 'numeric name' failed: expected '123', got {pNum.name.quote}"

-- ============================================================================
-- Quoted cookie values
-- ============================================================================

#eval show IO _ from do
  -- Double-quoted value: quotes are stripped, inner value is returned
  let p ← parseCookie "id=\"abc123\""
  unless p.value == "abc123" do
    throw <| IO.userError s!"Test 'quoted value' failed: expected 'abc123', got {p.value.quote}"

  -- Empty quoted value
  let pEq ← parseCookie "id=\"\""
  unless pEq.value == "" do
    throw <| IO.userError s!"Test 'empty quoted value' failed: expected '', got {pEq.value.quote}"

  -- Quoted value with all valid cookie-octets (excluding DQUOTE, SP, comma, semicolon, backslash)
  let pOctets ← parseCookie "t=\"!#$%&'*+-.^_`|~\""
  unless pOctets.value == "!#$%&'*+-.^_`|~" do
    throw <| IO.userError s!"Test 'quoted cookie-octets' failed: got {pOctets.value.quote}"

-- ============================================================================
-- Domain attribute
-- ============================================================================

#eval show IO _ from do
  -- Domain present
  let p ← parseCookie "x=y; Domain=example.com"
  unless p.domain == some "example.com" do
    throw <| IO.userError s!"Test 'domain' failed: expected some \"example.com\", got {repr p.domain}"

  -- Leading dot is stripped per RFC 6265 §5.2.3
  let pDot ← parseCookie "x=y; Domain=.example.com"
  unless pDot.domain == some "example.com" do
    throw <| IO.userError s!"Test 'domain leading dot stripped' failed: expected some \"example.com\", got {repr pDot.domain}"

  -- Empty domain attribute → domain is none
  let pEmpty ← parseCookie "x=y; Domain="
  unless pEmpty.domain == none do
    throw <| IO.userError s!"Test 'empty domain' failed: expected none, got {repr pEmpty.domain}"

  -- Dot-only domain → stripped to empty → domain is none
  let pDotOnly ← parseCookie "x=y; Domain=."
  unless pDotOnly.domain == none do
    throw <| IO.userError s!"Test 'dot-only domain' failed: expected none, got {repr pDotOnly.domain}"

-- ============================================================================
-- Path attribute
-- ============================================================================

#eval show IO _ from do
  -- Valid path starting with /
  let p ← parseCookie "x=y; Path=/foo/bar"
  unless p.path == some "/foo/bar" do
    throw <| IO.userError s!"Test 'path' failed: expected some \"/foo/bar\", got {repr p.path}"

  -- Root path
  let pRoot ← parseCookie "x=y; Path=/"
  unless pRoot.path == some "/" do
    throw <| IO.userError s!"Test 'root path' failed: expected some \"/\", got {repr pRoot.path}"

  -- Path not starting with / → none per RFC 6265 §5.2.4
  let pNoSlash ← parseCookie "x=y; Path=noslash"
  unless pNoSlash.path == none do
    throw <| IO.userError s!"Test 'path without leading slash' failed: expected none, got {repr pNoSlash.path}"

  -- Empty path → none
  let pEmpty ← parseCookie "x=y; Path="
  unless pEmpty.path == none do
    throw <| IO.userError s!"Test 'empty path' failed: expected none, got {repr pEmpty.path}"

-- ============================================================================
-- Secure attribute
-- ============================================================================

#eval show IO _ from do
  -- Secure present
  let p ← parseCookie "x=y; Secure"
  unless p.secure == true do
    throw <| IO.userError "Test 'secure' failed: expected true"

  -- Secure absent
  let pNo ← parseCookie "x=y"
  unless pNo.secure == false do
    throw <| IO.userError "Test 'secure absent' failed: expected false"

  -- Secure= (with a value — treated as Secure since we match the attr name)
  let pVal ← parseCookie "x=y; Secure=true"
  unless pVal.secure == true do
    throw <| IO.userError "Test 'secure with value' failed: expected true"

-- ============================================================================
-- Combined attributes
-- ============================================================================

#eval show IO _ from do
  let p ← parseCookie "sessionId=abc123; Domain=example.com; Path=/app; Secure"
  unless p.name == "sessionId" do
    throw <| IO.userError s!"Test 'combined name' failed: got {p.name.quote}"
  unless p.value == "abc123" do
    throw <| IO.userError s!"Test 'combined value' failed: got {p.value.quote}"
  unless p.domain == some "example.com" do
    throw <| IO.userError s!"Test 'combined domain' failed: got {repr p.domain}"
  unless p.path == some "/app" do
    throw <| IO.userError s!"Test 'combined path' failed: got {repr p.path}"
  unless p.secure == true do
    throw <| IO.userError "Test 'combined secure' failed: expected true"

-- ============================================================================
-- Case-insensitive attribute names (RFC 6265 §5.2)
-- ============================================================================

#eval show IO _ from do
  -- Uppercase attribute names must be recognized
  let p ← parseCookie "x=y; DOMAIN=example.com; PATH=/; SECURE"
  unless p.domain == some "example.com" do
    throw <| IO.userError s!"Test 'uppercase domain' failed: got {repr p.domain}"
  unless p.path == some "/" do
    throw <| IO.userError s!"Test 'uppercase path' failed: got {repr p.path}"
  unless p.secure == true do
    throw <| IO.userError "Test 'uppercase secure' failed: expected true"

  -- Mixed-case attribute names
  let pMixed ← parseCookie "x=y; Domain=a.com; Secure; Path=/x"
  unless pMixed.domain == some "a.com" do
    throw <| IO.userError s!"Test 'mixed-case domain' failed: got {repr pMixed.domain}"
  unless pMixed.secure == true do
    throw <| IO.userError "Test 'mixed-case secure' failed: expected true"
  unless pMixed.path == some "/x" do
    throw <| IO.userError s!"Test 'mixed-case path' failed: got {repr pMixed.path}"

-- ============================================================================
-- Unknown attributes are silently ignored
-- ============================================================================

#eval show IO _ from do
  -- HttpOnly is silently ignored
  let p ← parseCookie "x=y; HttpOnly"
  unless p.name == "x" && p.value == "y" do
    throw <| IO.userError s!"Test 'HttpOnly ignored' failed: name={p.name.quote} value={p.value.quote}"

  -- Expires is silently ignored
  let pExp ← parseCookie "x=y; Expires=Thu, 01 Jan 2026 00:00:00 GMT"
  unless pExp.name == "x" && pExp.value == "y" do
    throw <| IO.userError s!"Test 'Expires ignored' failed"

  -- SameSite is silently ignored
  let pSS ← parseCookie "x=y; SameSite=Strict"
  unless pSS.name == "x" && pSS.value == "y" do
    throw <| IO.userError s!"Test 'SameSite ignored' failed"

  -- Max-Age is silently ignored
  let pMaxAge ← parseCookie "x=y; Max-Age=3600"
  unless pMaxAge.name == "x" && pMaxAge.value == "y" do
    throw <| IO.userError s!"Test 'Max-Age ignored' failed"

  -- Multiple unknown attributes
  let pMulti ← parseCookie "x=y; Foo=bar; HttpOnly; Baz; Path=/p"
  unless pMulti.path == some "/p" do
    throw <| IO.userError s!"Test 'unknown attrs + path' failed: got {repr pMulti.path}"

-- ============================================================================
-- Duplicate attribute handling (last-write-wins is fine, RFC 6265 §5.3)
-- ============================================================================

#eval show IO _ from do
  -- Last Domain wins
  let p ← parseCookie "x=y; Domain=first.com; Domain=second.com"
  unless p.domain == some "second.com" do
    throw <| IO.userError s!"Test 'duplicate domain last wins' failed: got {repr p.domain}"

  -- Last Path wins
  let pPath ← parseCookie "x=y; Path=/first; Path=/second"
  unless pPath.path == some "/second" do
    throw <| IO.userError s!"Test 'duplicate path last wins' failed: got {repr pPath.path}"

-- ============================================================================
-- Semicolon spacing: RFC 6265 §4.1 allows optional SP after ";"
-- ============================================================================

#eval show IO _ from do
  -- No space after semicolon
  let pNoSp ← parseCookie "x=y;Secure"
  unless pNoSp.secure == true do
    throw <| IO.userError "Test 'no space after semicolon' failed: expected Secure=true"

  -- Space after semicolon (standard)
  let pSp ← parseCookie "x=y; Secure"
  unless pSp.secure == true do
    throw <| IO.userError "Test 'space after semicolon' failed: expected Secure=true"

-- ============================================================================
-- Invalid cookie names → parse failure
-- ============================================================================

#eval show IO _ from do
  -- Empty name is not a valid token (token = 1*tchar, requires at least one char)
  parseShouldFail "empty name" "=value"

  -- Space in name (space is not a tchar)
  parseShouldFail "space in name" "foo bar=value"

  -- Semicolon in name (not a tchar)
  parseShouldFail "semicolon in name" "foo;bar=value"

  -- Missing '=' separator
  parseShouldFail "missing equals" "nameonly"
