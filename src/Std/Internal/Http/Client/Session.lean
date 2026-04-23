/-
Copyright (c) 2026 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Sofia Rodrigues
-/
module

prelude
public import Std.Internal.Http.Client.Connection

public section

namespace Std.Http.Client

open Std Internal IO Async TCP Protocol
open Time

set_option linter.all true

/-!
# Session

This module defines `Client.Session`, an HTTP/1.1 client session that manages a single
persistent connection and dispatches sequential request/response exchanges over it.
A background task drives the `Connection` loop; callers interact through a channel.
-/

/--
An HTTP client session that sends sequential requests over a persistent connection.
-/
structure Session (α : Type) where
  /--
  Queue of requests sent by users.
  -/
  requestChannel : Std.CloseableChannel RequestPacket

  /--
  Resolves when the background loop exits.
  -/
  shutdown : IO.Promise Unit

  /--
  Configuration for this session.
  -/
  config : Config

  /--
  Unique identifier assigned by the pool when this session is registered.
  Zero for sessions created outside a pool.
  -/
  id : UInt64 := 0

namespace Session

/--
Queue a request and await its response.
-/
def send [Transport α] {β : Type} [Body β]
    (session : Session α) (request : Request β) : Async (Response Body.Stream) := do

  let responsePromise ← IO.Promise.new
  let responseBodyControl ← ResponseBodyControl.new

  let task ← session.requestChannel.send {
    request := { line := request.line, body := Body.Any.ofBody request.body, extensions := request.extensions }
    responsePromise
    responseBodyControl
  }

  let .ok _ ← await task
    | throw (.userError "connection closed, cannot send more requests")

  match ← await responsePromise.result! with
  | .ok response => pure response
  | .error error => throw error

/--
Wait for background loop shutdown.
-/
def waitShutdown (session : Session α) : Async Unit := do
  await session.shutdown.result!

/--
Close the session's request channel.
-/
def close (session : Session α) : Async Unit := do
  discard <| EIO.toBaseIO session.requestChannel.close

/--
Creates an HTTP client session over the given transport and starts its background loop.
-/
def new [Transport t] (client : t) (config : Config := {}) : Async (Session t) := do
  let requestChannel ← Std.CloseableChannel.new
  let shutdown ← IO.Promise.new

  let context ← CancellationContext.new

  background do
    try
      Std.Http.Client.Connection.handle client
        ({ config := config.toH1Config } : H1.Machine .sending)
        config context requestChannel
    finally
      discard <| shutdown.resolve ()

  pure { requestChannel, shutdown, config }

end Session

end Std.Http.Client
