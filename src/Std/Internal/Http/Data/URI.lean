/-
Copyright (c) 2025 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Sofia Rodrigues
-/
module

prelude
public import Std.Internal.Http.Data.URI.Basic
public import Std.Internal.Http.Data.URI.Parser

public section

/-!
# URI

This module defines the `URI` and `RequestTarget` types that represent and manipulate components of
URIs as defined by RFC 3986. It provides parsing, rendering, and normalization utilities for working
with URIs and request targets in HTTP messages.

References:
* https://www.rfc-editor.org/rfc/rfc3986.html
* https://www.rfc-editor.org/rfc/rfc9112.html#section-3.3
-/

namespace Std.Http.RequestTarget

set_option linter.all true

/--
Attempts to parse a `RequestTarget` from the given string.
-/
@[inline]
def parse? (string : String) : Option RequestTarget :=
  (URI.Parser.parseRequestTarget <* Std.Internal.Parsec.eof).run string.toUTF8 |>.toOption

/--
Parses a `RequestTarget` from the given string. Panics if parsing fails. Use `parse?`
if you need a safe option-returning version.
-/
@[inline]
def parse! (string : String) : RequestTarget :=
  match parse? string with
  | some res => res
  | none => panic! "invalid request target"

/--
Creates an origin-form request target from a path string.
The path should start with '/' (e.g., "/api/users" or "/search?q=test").
Panics if the string is not a valid origin-form request target.
-/
@[inline]
def originForm! (path : String) : RequestTarget :=
  match parse? path with
  | some (.originForm p q) => .originForm p q
  | _ => panic! s!"invalid origin-form request target: {path}"

/--
Returns the path component of the request target, defaulting to the root path `/`
when the target carries no path (asterisk-form or authority-form).
Unlike `RequestTarget.path`, the fallback is the absolute root rather than an
empty relative path — used by clients that need a well-formed absolute path
for cookie matching or logging.
-/
def pathOrRoot : RequestTarget → URI.Path
  | .originForm p _ => p
  | .absoluteForm uri => uri.path
  | _ => { segments := #[], absolute := true }

/--
Inserts or appends a query parameter on this target, preserving its form.
Origin-form and absolute-form targets gain the parameter on their existing
query; authority-form and asterisk-form targets are returned unchanged because
they do not carry a query.
-/
def setQueryParam (target : RequestTarget) (key value : String) : RequestTarget :=
  match target with
  | .originForm path query =>
      .originForm path (some ((query.getD URI.Query.empty).insert key value))
  | .absoluteForm af =>
      .absoluteForm { af with query := af.query.insert key value }
  | other => other

end RequestTarget

namespace URI

/--
Attempts to parse a `URI` from the given string.
-/
@[inline]
def parse? (string : String) : Option URI :=
  (Parser.parseURI <* Std.Internal.Parsec.eof).run string.toUTF8 |>.toOption

/--
Parses a `URI` from the given string. Panics if parsing fails. Use `parse?` if you need a safe
option-returning version.
-/
@[inline]
def parse! (string : String) : URI :=
  match parse? string with
  | some res => res
  | none => panic! "invalid URI"

/--
Extracts the numeric port this URI addresses. When the authority omits the port
(or parses as empty) the scheme's default port is returned (`80` for `http`,
`443` for `https`).
-/
def port (uri : URI) : UInt16 :=
  match uri.authority with
  | some auth =>
    match auth.port with
    | .value p => p
    | _ => URI.Scheme.defaultPort uri.scheme
  | none => URI.Scheme.defaultPort uri.scheme

/--
Extracts the host this URI addresses, returning the `Inhabited` default for
`URI.Host` when the authority is absent.
-/
def host (uri : URI) : URI.Host :=
  (uri.authority.map (·.host)).getD default

/--
Returns the origin-form request target corresponding to this URI, dropping the
scheme, authority, user-info, and fragment. An empty query is reported as
`none` so the target stays canonical.

Reference: https://httpwg.org/specs/rfc9112.html#section-3.2.1
-/
def originTarget (uri : URI) : RequestTarget :=
  .originForm uri.path (if uri.query.isEmpty then none else some uri.query)

/--
Splits this URI into the `(scheme, host, port, origin-form target)` tuple a
client needs to dispatch a request to the referenced origin. Path, query,
scheme, and port fall back to their defaults when the URI or its authority
leave them implicit.
-/
def toOriginRequest (uri : URI) : URI.Scheme × URI.Host × UInt16 × RequestTarget :=
  (uri.scheme, uri.host, uri.port, uri.originTarget)

namespace Path

/--
Attempts to parse a URI path from the given string.
Returns `none` if the string is not a valid path.
-/
@[inline]
def parse? (s : String) : Option Std.Http.URI.Path :=
  (Std.Http.URI.Parser.parsePath {} true true <* Std.Internal.Parsec.eof).run s.toUTF8 |>.toOption

/--
Parses a URI path from the given string. Returns the root path `"/"` if parsing fails.
-/
@[inline]
def parseOrRoot (s : String) : Std.Http.URI.Path :=
  parse? s |>.getD { segments := #[], absolute := true }

end Std.Http.URI.Path
