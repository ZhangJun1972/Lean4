/-
Copyright (c) 2026 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Sofia Rodrigues
-/
module

prelude
public import Std.Internal.Http.Data.Body.Basic

public section

/-!
# Body.Replayable

A typeclass for HTTP body types whose content can be re-read from the start.

`Body.Full` and `Body.Buffered` implement `Replayable`; `Body.Stream` does not because its
bytes come from a live producer that has already been consumed and cannot be rewound.

The HTTP client uses this to decide whether to follow method-preserving redirects (307/308):
if the body is not replayable the redirect is not followed and the 307/308 response is returned
to the caller, matching the behavior of reqwest.
-/

namespace Std.Http.Body
open Std Internal IO Async

set_option linter.all true

/--
A body that can be re-read from the start.

- `replay`: returns a fresh body (or `self` for re-readable bodies like `Full`).
- `resetInPlace`: resets the body's read position without allocating. Used by `Body.Any` on
  method-preserving (307/308) redirects. Defaults to a no-op.
-/
class Replayable (α : Type) where
  /--
  Returns a fresh body positioned at the start.
  For `Body.Full` this is `pure self`; for `Body.Buffered` it creates a new cursor at zero.
  -/
  replay : α → Async α

  /--
  Resets this body's read state in place so it can be read from the start again.
  Defaults to a no-op (suitable for `Body.Full`, which is always re-readable).
  `Body.Buffered` overrides this to reset its internal cursor.
  -/
  resetInPlace : α → Async Unit := fun _ => pure ()

end Std.Http.Body
