/-
Copyright (c) 2026 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Sofia Rodrigues
-/
module

prelude
public import Init.Data.Queue
public import Std.Sync.Mutex
public import Std.Internal.Async.Select

public section

open Std.Internal.IO.Async

/-!
This module contains the implementation of `Std.Watch`. `Std.Watch` is a single-value watch
channel, inspired by [tokio's watch implementation](https://github.com/tokio-rs/tokio/blob/master/tokio/src/sync/watch.rs).

A watch channel holds a single value that can be updated by the sender. Multiple receivers
can independently observe the current value and wait for it to change.

Unlike `Std.Channel`, a watch channel:
- Retains only the latest value, not a queue of messages.
- Allows receivers to read the current value without consuming it.
- Notifies all receivers when the value changes (broadcast semantics on change).
- Returns an error on `changed` if the sender has been dropped.
-/

namespace Std

/--
Errors that may be thrown while interacting with the watch channel API.
-/
inductive Watch.Error where
  /--
  The sender was dropped, so no new values will ever be sent.
  -/
  | closed
deriving Repr, DecidableEq, Hashable

instance : ToString Watch.Error where
  toString
    | .closed => "watch channel sender was dropped"

instance : MonadLift (EIO Watch.Error) IO where
  monadLift x := EIO.toIO (.userError <| toString ·) x

private inductive Watch.Waiter (α : Type) where
  | normal (promise : IO.Promise α)
  | select (waiter : Internal.IO.Async.Waiter α)

private def Watch.Waiter.resolve (c : Watch.Waiter α) (x : α) : BaseIO Bool := do
  match c with
  | .normal promise =>
    promise.resolve x
    return true
  | .select waiter =>
    waiter.race (return false) fun promise => do
      promise.resolve (.ok x)
      return true

/--
The shared state of a watch channel.
-/
private structure Watch.State (α : Type) where
  /--
  The current value held by the watch channel.
  -/
  value : α
  /--
  Monotonically increasing version. Incremented on every `send`.
  -/
  version : Nat
  /--
  Whether the sender has been dropped (closed).
  -/
  closed : Bool
  /--
  Receivers waiting for the value to change.
  -/
  waiters : Std.Queue (Watch.Waiter (Except Watch.Error Unit))
deriving Nonempty

/--
A watch channel sender. Holds a reference to the shared state and can update the value.
-/
structure Watch (α : Type) where
  private mk ::
  private state : Mutex (Watch.State α)
deriving Nonempty

/--
A watch channel receiver. Each receiver independently tracks the version it last observed.
-/
structure Watch.Receiver (α : Type) where
  private mk ::
  private state : Mutex (Watch.State α)
  private lastSeen : IO.Ref Nat
deriving Nonempty

namespace Watch

/--
Creates a new watch channel with an initial value. Returns the sender and a receiver.
-/
def new (initial : α) : BaseIO (Watch α × Watch.Receiver α) := do
  let state ← Mutex.new {
    value    := initial
    version  := 0
    closed   := false
    waiters  := ∅
  }
  let lastSeen ← IO.mkRef 0
  return (⟨state⟩, ⟨state, lastSeen⟩)

/--
Sends a new value, updating the watched value and notifying all waiting receivers.
-/
def send (w : Watch α) (v : α) : BaseIO Unit := do
  w.state.atomically do
    let st ← get
    let newVersion := st.version + 1
    set { st with value := v, version := newVersion, waiters := ∅ }
    for waiter in st.waiters.toArray do
      discard <| waiter.resolve (.ok ())

/--
Closes the watch channel, signaling to receivers that no more values will be sent.
Waiting receivers will be woken up and their `changed` call will return `Watch.Error.closed`.
-/
def close (w : Watch α) : BaseIO Unit := do
  w.state.atomically do
    let st ← get
    set { st with closed := true, waiters := ∅ }
    for waiter in st.waiters.toArray do
      discard <| waiter.resolve (.error .closed)

/--
Returns `true` if the sender has been closed.
-/
def isClosed (w : Watch α) : BaseIO Bool :=
  w.state.atomically do
    return (← get).closed

/--
Returns the current value held by the watch channel, as seen from the sender side.
-/
def current (w : Watch α) : BaseIO α :=
  w.state.atomically do
    return (← MonadState.get).value

namespace Receiver

/--
Borrow the current value without marking it as seen.
-/
def borrow (r : Watch.Receiver α) : BaseIO α :=
  r.state.atomically do
    return (← get).value

/--
Borrow the current value and mark the current version as seen, so that
the next `changed` call will only wake on a strictly newer value.
-/
def borrowAndUpdate (r : Watch.Receiver α) : BaseIO α := do
  r.state.atomically do
    let st ← get
    r.lastSeen.set st.version
    return st.value

/--
Returns `true` if the watched value has changed since this receiver last called
`borrowAndUpdate` or `changed`.
-/
def hasChanged (r : Watch.Receiver α) : BaseIO Bool := do
  r.state.atomically do
    let st ← get
    let seen ← r.lastSeen.get
    return st.version > seen

/--
Wait until the watched value changes relative to the version last seen by this receiver.
Returns `ok ()` on success or `error Watch.Error.closed` if the sender was dropped.

After a successful return the new value can be retrieved with `borrow` or `borrowAndUpdate`.
-/
partial def changed (r : Watch.Receiver α) : BaseIO (Task (Except Watch.Error Unit)) := do
  r.state.atomically do
    let st ← get
    let seen ← r.lastSeen.get
    if st.version > seen then
      r.lastSeen.set st.version
      return .pure <| .ok ()
    else if st.closed then
      return .pure <| .error .closed
    else
      let promise ← IO.Promise.new
      modify fun s => { s with waiters := s.waiters.enqueue (.normal promise) }
      BaseIO.bindTask promise.result? fun
        | none => return .pure <| .error .closed
        | some (Except.error e) => return .pure <| .error e
        | some (Except.ok ()) =>
            /- A notification arrived; recurse so `lastSeen` is updated atomically. -/
            r.changed

/--
Creates a `Selector` that resolves when the watched value changes.
-/
def changedSelector (r : Watch.Receiver α) : Selector (Except Watch.Error Unit) where
  tryFn := do
    r.state.atomically do
      let st ← get
      let seen ← r.lastSeen.get
      if st.version > seen then
        r.lastSeen.set st.version
        return some (.ok ())
      else if st.closed then
        return some (.error .closed)
      else
        return none

  registerFn waiter := do
    r.state.atomically do
      let st ← get
      let seen ← r.lastSeen.get
      if st.version > seen || st.closed then
        let result : Except Watch.Error Unit :=
          if st.version > seen then .ok () else .error .closed
        if st.version > seen then r.lastSeen.set st.version
        waiter.race (return ()) fun promise =>
          promise.resolve (.ok result)
      else
        modify fun s => { s with waiters := s.waiters.enqueue (.select waiter) }

  unregisterFn := do
    r.state.atomically do
      let st ← get
      let waiters ← st.waiters.filterM fun
        | .normal _ => return true
        | .select w => return !(← w.checkFinished)
      set { st with waiters }

end Receiver

/--
A sync wrapper around `Watch.Receiver` for blocking use.
-/
@[expose] def Sync (α : Type) : Type := Watch α

/--
A sync wrapper around `Watch.Receiver` for blocking use.
-/
@[expose] def Sync.Receiver (α : Type) : Type := Watch.Receiver α

namespace Sync

/--
Creates a new watch channel with an initial value. Returns the sender and a sync receiver.
-/
@[inline]
def new (initial : α) : BaseIO (Sync α × Sync.Receiver α) :=
  Watch.new initial

/--
Sends a new value, updating the watched value and notifying all waiting receivers.
-/
@[inline]
def send (w : Sync α) (v : α) : BaseIO Unit :=
  Watch.send w v

/--
Closes the watch channel.
-/
@[inline]
def close (w : Sync α) : BaseIO Unit :=
  Watch.close w

/--
Returns `true` if the sender has been closed.
-/
@[inline]
def isClosed (w : Sync α) : BaseIO Bool :=
  Watch.isClosed w

namespace Receiver

/--
Borrow the current value without marking it as seen.
-/
@[inline]
def borrow (r : Sync.Receiver α) : BaseIO α :=
  Watch.Receiver.borrow r

/--
Borrow the current value and mark it as seen.
-/
@[inline]
def borrowAndUpdate (r : Sync.Receiver α) : BaseIO α :=
  Watch.Receiver.borrowAndUpdate r

/--
Returns `true` if the watched value has changed since last seen.
-/
@[inline]
def hasChanged (r : Sync.Receiver α) : BaseIO Bool :=
  Watch.Receiver.hasChanged r

/--
Block until the watched value changes. Returns `ok ()` or `error Watch.Error.closed`.
-/
def changed (r : Sync.Receiver α) : BaseIO (Except Watch.Error Unit) := do
  IO.wait (← Watch.Receiver.changed r)

end Receiver
end Sync
end Watch
end Std
