/-
Copyright (c) 2026 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Sofia Rodrigues
-/
module

prelude
public import Std.Sync
public import Std.Internal.Http.Data.Body.Any
public import Init.Data.ByteArray

public section

/-!
# Body.Buffered

`Buffered α` eagerly reads all chunks from a body of type `α` into a `ByteArray` and
implements both `Http.Body` (sequential reads) and `Replayable` (reset to the start).

Use `Buffered.ofBody` to create one from any `Http.Body`. Typical use cases:
- Wrapping a `Body.Stream` before a request that may be redirected with 307/308.
- Buffering a response body for multiple reads.

```lean
let buffered ← Buffered.ofBody stream
let req ← client.post url |>.sendStream (fun _ => pure ())
-- or pass buffered directly
```
-/

namespace Std.Http.Body
open Std Internal IO Async

set_option linter.all true

/--
A body that has been fully read into memory and can be replayed from the start.
The type parameter `α` records what kind of body was buffered.
The internal cursor is reset to zero on each `replay`.
-/
structure Buffered (α : Type) where
  private mk ::
  /-- The buffered content. -/
  private data : ByteArray
  /-- Read state: `some pos` = cursor at `pos`; `none` = closed. -/
  private state : Mutex (Option Nat)

namespace Buffered

/--
Reads all chunks from `body` into memory and returns a `Buffered α`.
The original body is fully consumed by this call.
-/
partial def ofBody [Http.Body α] (body : α) : Async (Buffered α) := do
  let rec loop (acc : ByteArray) : Async ByteArray := do
    match ← Http.Body.recv body with
    | none       => pure acc
    | some chunk => loop (acc ++ chunk.data)
  let data  ← loop ByteArray.empty
  let state ← Mutex.new (some 0)
  return { data, state }

/--
Returns the remaining bytes as a single chunk, or `none` at EOF or when closed.
-/
def recv (buf : Buffered α) : Async (Option Chunk) :=
  buf.state.atomically do
    match ← get with
    | none     => pure none
    | some pos =>
      if pos >= buf.data.size then pure none
      else
        set (some buf.data.size)
        pure (some (Chunk.ofByteArray (buf.data.extract pos buf.data.size)))

/--
Closes the body, discarding any unread data.
-/
def close (buf : Buffered α) : Async Unit :=
  buf.state.atomically do
    set (none : Option Nat)

/--
Returns `true` when the body has been closed via `close`.
-/
def isClosed (buf : Buffered α) : Async Bool :=
  buf.state.atomically do
    return (← get).isNone

/--
Returns the number of remaining bytes as a fixed-size length.
-/
def getKnownSize (buf : Buffered α) : Async (Option Body.Length) :=
  buf.state.atomically do
    match ← get with
    | none     => pure (some (.fixed 0))
    | some pos => pure (some (.fixed (buf.data.size - pos)))

/--
Non-blocking receive. Since all data is in memory, this always resolves immediately.
Returns `some none` at EOF or when closed, `some (some chunk)` when data is available.
-/
def tryRecv (buf : Buffered α) : Async (Option (Option Chunk)) :=
  buf.state.atomically do
    match ← get with
    | none     => pure (some none)
    | some pos =>
      if pos >= buf.data.size then pure (some none)
      else
        set (some buf.data.size)
        pure (some (some (Chunk.ofByteArray (buf.data.extract pos buf.data.size))))

/--
Selector that resolves immediately since buffered data is always in memory.
-/
def recvSelector (buf : Buffered α) : Selector (Option Chunk) where
  tryFn := do
    buf.state.atomically do
      match ← get with
      | none     => return some none
      | some pos =>
        if pos >= buf.data.size then return some none
        else
          set (some buf.data.size)
          return some (some (Chunk.ofByteArray (buf.data.extract pos buf.data.size)))

  registerFn waiter := do
    let chunk ← recv buf
    let lose := pure ()
    let win promise := promise.resolve (.ok chunk)
    waiter.race lose win

  unregisterFn := pure ()

/--
Returns a new `Buffered` sharing the same data with a fresh cursor at position zero.
-/
def replay (buf : Buffered α) : Async (Buffered α) := do
  let state ← Mutex.new (some 0)
  return { buf with state }

/--
Resets the cursor to position zero so the body can be re-read from the start.
-/
def resetInPlace (buf : Buffered α) : Async Unit :=
  buf.state.atomically do set (some 0)

end Buffered

instance : Http.Body (Buffered α) where
  recv := Buffered.recv
  close := Buffered.close
  isClosed := Buffered.isClosed
  recvSelector := Buffered.recvSelector
  tryRecv := Buffered.tryRecv
  getKnownSize := Buffered.getKnownSize
  setKnownSize _ _ := pure ()

/--
`Buffered` is replayable.
- `replay`: returns a new `Buffered` sharing the same data with a fresh cursor.
- `resetInPlace`: resets the cursor to zero in the existing body (used by `Body.Any`).
-/
instance : Replayable (Buffered α) where
  replay      := Buffered.replay
  resetInPlace := Buffered.resetInPlace


end Std.Http.Body
