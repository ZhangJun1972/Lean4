/-
Copyright (c) 2025 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Sofia Rodrigues
-/
module

prelude
public import Std.Sync
public import Std.Internal.Http.Data.Request
public import Std.Internal.Http.Data.Response
public import Std.Internal.Http.Data.Body.Any
public import Init.Data.ByteArray

public section

/-!
# Body.Full

A body backed by a fixed `ByteArray`. The body uses a cursor: the first call to `recv`
returns the full byte array as a single chunk; subsequent calls return `none` (end-of-stream).
Closing the body discards any unconsumed data. `resetInPlace` resets the cursor to zero so
the body can be re-sent (e.g. on 307/308 redirects).
-/

namespace Std.Http.Body
open Std Internal IO Async

set_option linter.all true

/--
A body backed by a fixed `ByteArray` with a cursor.

The cursor tracks whether the data has been sent:
- `some 0` = ready to send
- `some n` (n > 0) = data sent, at EOF
- `none` = closed

Unlike `Body.Stream`, a `Full` body is replayable: `resetInPlace` resets the cursor
to zero so the same body can be re-sent on redirects (307/308), matching the behavior
of reqwest, axios, and curl.
-/
structure Full where
  private mk ::
  private data : ByteArray
  private state : Mutex (Option Nat)
deriving Nonempty

namespace Full

private def takeChunk (full : Full) : AtomicT (Option Nat) Async (Option Chunk) := do
  match ← get with
  | none => pure none
  | some 0 =>
    if full.data.isEmpty then pure none
    else
      set (some full.data.size)
      pure (some (Chunk.ofByteArray full.data))
  | some _ => pure none

/--
Creates a `Full` body from a `ByteArray`.
-/
def ofByteArray (data : ByteArray) : Async Full := do
  let state ← Mutex.new (some 0)
  return { data, state }

/--
Creates a `Full` body from a `String`.
-/
def ofString (data : String) : Async Full := do
  let state ← Mutex.new (some 0)
  return { data := data.toUTF8, state }

/--
Receives the body data. Returns the full byte array on the first call as a single chunk,
then `none` on all subsequent calls until the cursor is reset.
-/
def recv (full : Full) : Async (Option Chunk) :=
  full.state.atomically do
    takeChunk full

/--
Closes the body, discarding any unconsumed data.
-/
def close (full : Full) : Async Unit :=
  full.state.atomically do
    set (none : Option Nat)

/--
Returns `true` when the body has been closed via `close`.
-/
def isClosed (full : Full) : Async Bool :=
  full.state.atomically do
    return (← get).isNone

/--
Returns the known size of the remaining data.
Returns `some (.fixed n)` with the byte count if not yet consumed, `some (.fixed 0)` otherwise.
-/
def getKnownSize (full : Full) : Async (Option Body.Length) :=
  full.state.atomically do
    match ← get with
    | none => pure (some (.fixed 0))
    | some 0 => pure (some (.fixed full.data.size))
    | some _ => pure (some (.fixed 0))

/--
Non-blocking receive. `Full` bodies are always in-memory, so data is always
immediately available. Returns `some chunk` on first call, `some none` (EOF)
once consumed or closed.
-/
def tryRecv (full : Full) : Async (Option (Option Chunk)) := do
  return some (← full.state.atomically (takeChunk full))

/--
Selector that immediately resolves to the remaining chunk (or EOF).
-/
def recvSelector (full : Full) : Selector (Option Chunk) where
  tryFn := do
    let chunk ← full.state.atomically do
      takeChunk full
    pure (some chunk)

  registerFn waiter := do
    full.state.atomically do
      let lose := pure (())

      let win promise := do
        let chunk ← takeChunk full
        promise.resolve (.ok chunk)

      waiter.race lose win

  unregisterFn := pure ()

/--
Returns a new `Full` sharing the same data with a fresh cursor at position zero.
-/
def replay (full : Full) : Async Full := do
  let state ← Mutex.new (some 0)
  return { full with state }

/--
Resets the cursor to position zero so the body can be re-read from the start.
Since `Full.data` is always preserved in the struct, this always works regardless of
whether `close` was previously called (e.g. by the connection loop after EOF).
-/
def resetInPlace (full : Full) : Async Unit :=
  full.state.atomically do
    set (some 0)

end Full

instance : Http.Body Full where
  recv := Full.recv
  close := Full.close
  isClosed := Full.isClosed
  recvSelector := Full.recvSelector
  tryRecv := Full.tryRecv
  getKnownSize := Full.getKnownSize
  setKnownSize _ _ := pure ()

/--
`Full` is replayable: `resetInPlace` resets the cursor to zero so the body can be re-read
from the start. `replay` creates a new `Full` sharing the same data with a fresh cursor.
-/
instance : Replayable Full where
  replay      := Full.replay
  resetInPlace := Full.resetInPlace

instance : Coe Full Any := ⟨Any.ofReplayableBody⟩

instance : Coe (Response Full) (Response Any) where
  coe f := { f with }

instance : Coe (ContextAsync (Response Full)) (ContextAsync (Response Any)) where
  coe action := do
    let response ← action
    pure (response : Response Any)

instance : Coe (Async (Response Full)) (ContextAsync (Response Any)) where
  coe action := do
    let response ← action
    pure (response : Response Any)

end Body

namespace Request.Builder

open Internal.IO.Async

/--
Inserts `Content-Type: default` only when the builder does not already carry
one. Prevents the body-setting helpers (`text` / `bytes` / `json` / `html`) from
appending a duplicate header when the caller has pre-set `Content-Type`.
-/
@[inline]
private def defaultContentType (builder : Builder) (default_ : String) : Builder :=
  if builder.line.headers.contains Header.Name.contentType then builder
  else builder.header Header.Name.contentType (Header.Value.ofString! default_)

/--
Builds a request body from raw bytes without setting any headers.
Use `bytes` instead if you want `Content-Type: application/octet-stream` set automatically.
-/
def fromBytes (builder : Builder) (content : ByteArray) : Async (Request Body.Full) := do
  return builder.body (← Body.Full.ofByteArray content)

/--
Builds a request with a binary body.
Sets `Content-Type: application/octet-stream` unless the caller already set a
`Content-Type` on the builder.
Use `fromBytes` instead if you need to set a different `Content-Type` or none at all.
-/
def bytes (builder : Builder) (content : ByteArray) : Async (Request Body.Full) :=
  fromBytes (defaultContentType builder "application/octet-stream") content

/--
Builds a request with a text body.
Sets `Content-Type: text/plain; charset=utf-8` unless the caller already set
a `Content-Type` on the builder.
-/
def text (builder : Builder) (content : String) : Async (Request Body.Full) :=
  fromBytes (defaultContentType builder "text/plain; charset=utf-8") content.toUTF8

/--
Builds a request with a JSON body.
Sets `Content-Type: application/json` unless the caller already set a
`Content-Type` on the builder.
-/
def json (builder : Builder) (content : String) : Async (Request Body.Full) :=
  fromBytes (defaultContentType builder "application/json") content.toUTF8

/--
Builds a request with an HTML body.
Sets `Content-Type: text/html; charset=utf-8` unless the caller already set a
`Content-Type` on the builder.
-/
def html (builder : Builder) (content : String) : Async (Request Body.Full) :=
  fromBytes (defaultContentType builder "text/html; charset=utf-8") content.toUTF8

end Request.Builder

namespace Response.Builder
open Internal.IO.Async

/--
Inserts `Content-Type: default` only when the builder does not already carry
one. Prevents the body-setting helpers (`text` / `bytes` / `json` / `html`) from
appending a duplicate header when the caller has pre-set `Content-Type`.
-/
@[inline]
private def defaultContentType (builder : Builder) (default_ : String) : Builder :=
  if builder.line.headers.contains Header.Name.contentType then builder
  else builder.header Header.Name.contentType (Header.Value.ofString! default_)

/--
Builds a response body from raw bytes without setting any headers.
Use `bytes` instead if you want `Content-Type: application/octet-stream` set automatically.
-/
def fromBytes (builder : Builder) (content : ByteArray) : Async (Response Body.Full) := do
  return builder.body (← Body.Full.ofByteArray content)

/--
Builds a response with a binary body.
Sets `Content-Type: application/octet-stream` unless the caller already set a
`Content-Type` on the builder.
Use `fromBytes` instead if you need to set a different `Content-Type` or none at all.
-/
def bytes (builder : Builder) (content : ByteArray) : Async (Response Body.Full) :=
  fromBytes (defaultContentType builder "application/octet-stream") content

/--
Builds a response with a text body.
Sets `Content-Type: text/plain; charset=utf-8` unless the caller already set a
`Content-Type` on the builder.
-/
def text (builder : Builder) (content : String) : Async (Response Body.Full) :=
  fromBytes (defaultContentType builder "text/plain; charset=utf-8") content.toUTF8

/--
Builds a response with a JSON body.
Sets `Content-Type: application/json` unless the caller already set a
`Content-Type` on the builder.
-/
def json (builder : Builder) (content : String) : Async (Response Body.Full) :=
  fromBytes (defaultContentType builder "application/json") content.toUTF8

/--
Builds a response with an HTML body.
Sets `Content-Type: text/html; charset=utf-8` unless the caller already set a
`Content-Type` on the builder.
-/
def html (builder : Builder) (content : String) : Async (Response Body.Full) :=
  fromBytes (defaultContentType builder "text/html; charset=utf-8") content.toUTF8

end Response.Builder
