/-
Copyright (c) 2025 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Sofia Rodrigues
-/
module

prelude
public import Std.Internal.Async.TCP
public import Std.Internal.Async.ContextAsync
public import Std.Internal.Http.Transport
public import Std.Internal.Http.Protocol.H1
public import Std.Internal.Http.Client.Config
public import Std.Sync.Watch

public section

namespace Std.Http.Client

open Std Internal IO Async TCP Protocol
open Time

/-!
# Connection

This module defines the `Connection.handle` loop, used to manage one persistent HTTP/1.1 client
connection and handle sequential request/response exchanges over it.
-/

set_option linter.all true

/--
A request packet queued to the background connection loop.
-/
structure ResponseBodyControl where
  /--
  Flipped to `true` by the agent when it will drain the response body internally
  (redirect follow or `validateStatus` rejection). Tells `onBodyInterest` to
  apply `redirectBodyDrainLimit` instead of the caller-facing `maxResponseBodySize`.
  -/
  useRedirectDrainLimit : IO.Ref Bool
deriving TypeName

namespace ResponseBodyControl

/--
Creates a new response-body control in its default "caller-facing body limit"
mode.
-/
def new : BaseIO ResponseBodyControl :=
  return { useRedirectDrainLimit := ← IO.mkRef false }

/--
Switches this response into redirect-drain mode so the connection loop applies
`redirectBodyDrainLimit` instead of `maxResponseBodySize`.
-/
def markRedirectDrain (control : ResponseBodyControl) : BaseIO Unit :=
  control.useRedirectDrainLimit.set true

/--
Returns `true` when the agent has marked the response as an internally-drained
redirect body.
-/
def isRedirectDrain (control : ResponseBodyControl) : BaseIO Bool :=
  control.useRedirectDrainLimit.get

end ResponseBodyControl

/--
A request packet queued to the background connection loop.
-/
structure RequestPacket where
  /--
  The request to send.
  -/
  request : Request Body.Any

  /--
  Promise resolved with the eventual response.
  -/
  responsePromise : IO.Promise (Except Error (Response Body.Stream))

  /--
  Shared response-body mode flag used by the connection loop to determine whether
  to apply `redirectBodyDrainLimit` or `maxResponseBodySize` when body bytes arrive.
  Set by `markRedirectDrain` before any internally-consumed drain (redirect follows
  and `validateStatus` rejections).
  -/
  responseBodyControl : ResponseBodyControl

  /--
  Watch channel updated with the cumulative number of request-body bytes sent.
  `none` when the caller does not need upload-progress tracking.
  -/
  uploadProgress : Option (Watch UInt64) := none

  /--
  Watch channel updated with the cumulative number of response bytes received.
  `none` when the caller does not need download-progress tracking.
  -/
  downloadProgress : Option (Watch UInt64) := none

namespace RequestPacket

/--
Resolve the packet with an error.
-/
def onError (packet : RequestPacket) (error : Error) : BaseIO Unit :=
  discard <| packet.responsePromise.resolve (.error error)

/--
Resolve the packet with a response.
-/
def onResponse (packet : RequestPacket) (response : Response Body.Stream) : BaseIO Unit :=
  discard <| packet.responsePromise.resolve (.ok response)

end RequestPacket

namespace Connection

/--
Events produced by the async select loop in `pollNextEvent`.
Each variant corresponds to one possible outcome of waiting for I/O.
-/
private inductive Recv
  | bytes (x : Option ByteArray)
  | requestBody (x : Option Chunk)
  | bodyInterest (x : Bool)
  | packet (x : Option RequestPacket)
  | timeout
  | shutdown
  | close

/--
Mutable state that belongs to a single in-flight request/response exchange.
Kept in one struct so a `.next` transition can reset every per-request field
at once (impossible to forget one) and so `closeAllRequestState` has a
self-contained target.
-/
structure InFlightState where

  /--
  The request packet whose promise is pending (or just resolved).
  -/
  packet : RequestPacket

  /--
  Body the writer pump is currently consuming.  `none` while waiting for
  `100 Continue` (the body is stashed in `pendingRequestBody` until the
  server permits it).
  -/
  requestBody : Option Body.Any

  /--
  Body parked while waiting for a `100 Continue`.
  -/
  pendingRequestBody : Option Body.Any

  /--
  The outgoing response-body stream handed to the caller.
  -/
  responseStream : Option Body.Stream

  /--
  `true` while the machine is waiting for `100 Continue`.
  -/
  waitingForContinue : Bool

  /--
  `true` if the most recent `endHeaders` event was an informational 1xx.
  -/
  isInformationalResponse : Bool

  /--
  Watch the caller subscribes to for request-body upload progress.
  -/
  uploadProgress : Option (Watch UInt64)

  /--
  Cumulative request-body bytes handed to the wire.
  -/
  uploadBytes : UInt64

  /--
  Watch the caller subscribes to for response download progress.
  -/
  downloadProgress : Option (Watch UInt64)

  /--
  Cumulative wire bytes received for this response (headers + body).
  -/
  downloadBytes : UInt64

  /--
  Cumulative response-body bytes pulled from the machine.
  -/
  downloadBodyBytes : UInt64

namespace InFlightState

/--
Builds the initial `InFlightState` for a packet that has just arrived, given
its pre-fetched body-size probe and the stream allocated for the response.
-/
def ofPacket (packet : RequestPacket) (responseStream : Body.Stream)
    (hasExpect : Bool) : InFlightState where
  packet := packet
  requestBody := if hasExpect then none else some packet.request.body
  pendingRequestBody := if hasExpect then some packet.request.body else none
  responseStream := some responseStream
  waitingForContinue := hasExpect
  isInformationalResponse := false
  uploadProgress := packet.uploadProgress
  uploadBytes := 0
  downloadProgress := packet.downloadProgress
  downloadBytes := 0
  downloadBodyBytes := 0

/--
Closes every open resource tied to this in-flight exchange: both request
body handles, the response stream, and the upload/download progress watches.
Each close is guarded by an `isClosed` check so this is idempotent.
-/
def closeAll (s : InFlightState) : Async Unit := do
  if let some body := s.requestBody then
    if ¬(← body.isClosed) then body.close
  if let some body := s.pendingRequestBody then
    if ¬(← body.isClosed) then body.close
  if let some body := s.responseStream then
    if ¬(← Body.isClosed body) then Body.close body
  if let some w := s.uploadProgress then Watch.close w
  if let some w := s.downloadProgress then Watch.close w

end InFlightState

/--
All mutable state carried through the connection processing loop.

Connection-level fields (`machine`, timeouts, read-pump flags) live here
directly; per-exchange fields are wrapped in `inFlight : Option InFlightState`
so that every transition to or from idle is a single field update that cannot
accidentally leave a stale per-request value behind.
-/
structure ConnectionState where
  /--
  The HTTP/1.1 state machine driving reads, writes, and parser events for
  this socket.
  -/
  machine : H1.Machine .sending

  /--
  The timeout currently armed for the next blocking wait.
  -/
  currentTimeout : Millisecond.Offset

  /--
  The idle keep-alive timeout to use between requests, or `none` while a
  request/response exchange is active.
  -/
  keepAliveTimeout : Option Millisecond.Offset

  /--
  Set when the H1 machine has requested more socket input.
  -/
  requiresData : Bool

  /--
  Preferred socket recv size from the most recent `.needMoreData` event.
  -/
  expectData : Option Nat

  /--
  `none` when the connection is idle (waiting for the next request).
  -/
  inFlight : Option InFlightState

namespace ConnectionState

/--
`true` when the connection is waiting for the next request packet.
-/
@[inline] def waitingForRequest (s : ConnectionState) : Bool :=
  s.inFlight.isNone

/--
Applies `f` to the current in-flight state, if any.
-/
@[inline] def mapInFlight (s : ConnectionState) (f : InFlightState → InFlightState) : ConnectionState :=
  { s with inFlight := s.inFlight.map f }

/--
The packet currently bound to the in-flight exchange, if any.
-/
@[inline] def currentRequest (s : ConnectionState) : Option RequestPacket :=
  s.inFlight.map (·.packet)

/--
The request body currently being pumped to the wire, if any.
-/
@[inline] def requestBody (s : ConnectionState) : Option Body.Any :=
  s.inFlight.bind (·.requestBody)

/--
The request body parked behind `Expect: 100-continue`, if any.
-/
@[inline] def pendingRequestBody (s : ConnectionState) : Option Body.Any :=
  s.inFlight.bind (·.pendingRequestBody)

/--
The response stream currently exposed to the caller, if any.
-/
@[inline] def responseStream (s : ConnectionState) : Option Body.Stream :=
  s.inFlight.bind (·.responseStream)

/--
`true` when the in-flight request is still waiting for `100 Continue`
before its body may be sent.
-/
@[inline] def waitingForContinue (s : ConnectionState) : Bool :=
  s.inFlight.map (·.waitingForContinue) |>.getD false

/--
`true` when the most recent header block was informational (1xx).
-/
@[inline] def isInformationalResponse (s : ConnectionState) : Bool :=
  s.inFlight.map (·.isInformationalResponse) |>.getD false

/--
The upload-progress watch for the in-flight request, if any.
-/
@[inline] def uploadProgress (s : ConnectionState) : Option (Watch UInt64) :=
  s.inFlight.bind (·.uploadProgress)

/--
The cumulative request-body bytes sent for the in-flight request.
-/
@[inline] def uploadBytes (s : ConnectionState) : UInt64 :=
  s.inFlight.map (·.uploadBytes) |>.getD 0

/--
The download-progress watch for the in-flight response, if any.
-/
@[inline] def downloadProgress (s : ConnectionState) : Option (Watch UInt64) :=
  s.inFlight.bind (·.downloadProgress)

/--
The cumulative wire bytes received for the in-flight response, including
headers and body.
-/
@[inline] def downloadBytes (s : ConnectionState) : UInt64 :=
  s.inFlight.map (·.downloadBytes) |>.getD 0

/--
The cumulative response-body bytes pulled from the H1 machine for the
in-flight response.
-/
@[inline] def downloadBodyBytes (s : ConnectionState) : UInt64 :=
  s.inFlight.map (·.downloadBodyBytes) |>.getD 0

end ConnectionState

@[inline]
private def requestHasExpectContinue (request : Request Body.Any) : Bool :=
  match request.line.headers.getAll? Header.Name.expect with
  | some #[value] => Header.Expect.parse value |>.isSome
  | _ => false

/--
Closes every open per-request resource held by `state`.  Idempotent.
-/
private def closeAllRequestState (state : ConnectionState) : Async Unit :=
  match state.inFlight with
  | some f => f.closeAll
  | none => pure ()

/--
Waits for the next I/O event across all sources relevant to `state`. Computes
the socket recv size from `config`, then races all active selectables. Returns
`.close` on transport errors.
-/
private def pollNextEvent
    [Transport α]
    (config : Config) (socket : α)
    (requestChannel : Std.CloseableChannel RequestPacket)
    (connectionContext : CancellationContext)
    (state : ConnectionState) : Async Recv := do

  let responseStreamClosed ← match state.responseStream with
    | some body => Body.isClosed body
    | none => pure true

  let responseBodySource :=
    if state.machine.canPullBodyNow then
      match state.responseStream with
      | some body => if responseStreamClosed then none else some body
      | none => none
    else none

  let pollSocket :=
    state.requiresData ∨
    state.machine.writer.sentMessage ∨
    !state.waitingForRequest ∨
    state.requestBody.isSome ∨
    state.machine.canPullBody

  let expectedBytes := state.expectData
    |>.getD config.defaultRequestBufferSize
    |>.min config.maxRecvChunkSize
    |>.toUInt64

  let mut selectables : Array (Selectable Recv) := #[
    .case connectionContext.doneSelector (fun _ => do
      let reason ← connectionContext.getCancellationReason
      match reason with
      | some .deadline => pure .timeout
      | _ => pure .shutdown)
  ]

  if pollSocket then
    selectables := selectables.push (.case (Transport.recvSelector socket expectedBytes) (Recv.bytes · |> pure))

    let timeout := state.keepAliveTimeout.getD state.currentTimeout
    selectables := selectables.push (.case (← Selector.sleep timeout) (fun _ => pure .timeout))
  else if let some idleTimeout := state.keepAliveTimeout then
    -- Idle connection with no active I/O: still arm the keepalive timer so the
    -- connection is closed after the keepalive window expires.
    selectables := selectables.push (.case (← Selector.sleep idleTimeout) (fun _ => pure .timeout))

  -- Always include an active request body, even if already closed. A closed
  -- body's recvSelector resolves immediately with `none`, which triggers
  -- `userClosedBody` so the H1 machine can finalize chunked encoding.
  if let some requestBody := state.requestBody then
    selectables := selectables.push (.case requestBody.recvSelector (Recv.requestBody · |> pure))

  if state.waitingForRequest then
    selectables := selectables.push (.case requestChannel.recvSelector (Recv.packet · |> pure))

  if let some responseBody := responseBodySource then
    selectables := selectables.push (.case responseBody.interestSelector (Recv.bodyInterest · |> pure))

  try Selectable.one selectables catch _ => pure .close

/--
Processes all H1 events from a single machine step, executing side effects
inline and returning the updated state together with a `sawFailure` flag
that tells the main loop to exit. Handles keep-alive resets, body-size
tracking, `Expect: 100-continue`, and parse errors.
-/
private def processH1Events
    (config : Config)
    (events : Array (H1.Event .sending))
    (state : ConnectionState) : Async (ConnectionState × Bool) := do

  let mut st := state
  let mut sawFailure := false

  for event in events do
    match event with
    | .needMoreData expect =>
      st := { st with requiresData := true, expectData := expect }

    | .needAnswer =>
      pure ()

    | .endHeaders head =>
      if head.status.isInformational then
        st := st.mapInFlight ({ · with isInformationalResponse := true })

        -- A `100 Continue` response authorises the body: move it from the
        -- pending slot into `requestBody` so the pump loop starts sending.
        if head.status == .continue && st.waitingForContinue then
          st := st.mapInFlight fun flight =>
            { flight with
              requestBody := flight.pendingRequestBody
              pendingRequestBody := none
              waitingForContinue := false
            }
      else
        st := { st with
          currentTimeout := config.readTimeout
          keepAliveTimeout := none
        }
        st := st.mapInFlight fun flight =>
          { flight with
            isInformationalResponse := false
          }

        -- A non-informational response while we were still waiting for
        -- `100 Continue`: the server rejected (or bypassed) the expectation.
        -- Discard the pending body — it must not be sent.
        if st.waitingForContinue then
          if let some body := st.pendingRequestBody then
            if ¬(← body.isClosed) then body.close
          st := st.mapInFlight fun flight =>
            { flight with pendingRequestBody := none, waitingForContinue := false }

        if let some body := st.responseStream then
          if let some length := head.getSize true then
            Body.setKnownSize body (some length)

        if let some packet := st.currentRequest then
          if let some incoming := st.responseStream then
            let extensions := Extensions.empty.insert packet.responseBodyControl
            packet.onResponse {
              line := head
              body := incoming
              extensions := extensions
            }

    | .closeBody =>
      -- Skip closing for informational (1xx) responses; the channel stays
      -- open for the real response body that follows.
      if !st.isInformationalResponse then
        if let some body := st.responseStream then
          if ¬(← Body.isClosed body) then Body.close body

    | .next =>
      -- Reset all per-request state for the next pipelined request.
      closeAllRequestState st
      st := { st with
        inFlight := none
        keepAliveTimeout := some config.keepAliveTimeout.val
        currentTimeout := config.keepAliveTimeout.val
      }

    | .failed err =>
      let ioErr : IO.Error := .userError (toString err)
      if let some packet := st.currentRequest then
        packet.onError ioErr
      -- If the response body was already handed off to the caller, surface the
      -- error through the stream so a pending `recv`/`readAll` sees it instead
      -- of silently truncating at whatever bytes happened to arrive.
      if let some body := st.responseStream then
        if ¬(← Body.isClosed body) then body.closeWithError ioErr
      sawFailure := true

    | .«continue» => pure ()

    | .close => pure ()

  return (st, sawFailure)

/--
Terminal transition applied when a caller-facing problem forces the connection
to end (request timeout, shutdown signal, response body limit exceeded).
Rejects any in-flight request, closes all per-request resources, and parks
the H1 machine.
-/
private def abortState
    (state : ConnectionState) (err : IO.Error) : Async ConnectionState := do
  if let some packet := state.currentRequest then
    packet.onError err
  closeAllRequestState state
  return { state with
    machine := state.machine.closeWriter.closeReader.noMoreInput
    inFlight := none
  }

/--
Pure transition for a new request packet that has already had its known body
size resolved and its response stream allocated by the async caller.
-/
private def onNewPacket
    (config : Config) (packet : RequestPacket) (knownSize : Option Body.Length)
    (responseStream : Body.Stream) (state : ConnectionState) : ConnectionState :=
  let machine0 := state.machine.send packet.request.line
  let hasExpect := requestHasExpectContinue packet.request
  let machine1 := match knownSize with
    | some size => machine0.setKnownSize size
    | none => machine0
  { state with
    machine := machine1
    currentTimeout := config.requestTimeout.val
    keepAliveTimeout := none
    inFlight := some <| InFlightState.ofPacket packet responseStream hasExpect
  }

/--
Transition for a `.bodyInterest true` event: pulls the next chunk out of
the H1 machine, enforces `maxResponseBodySize`, and publishes the chunk.
-/
private def onBodyInterest
    (config : Config) (state : ConnectionState) : Async ConnectionState := do
  let (newMachine, pulledChunk) := state.machine.pullBody
  let mut st := { state with machine := newMachine }

  if let some pulled := pulledChunk then
    let newBodyBytes := st.downloadBodyBytes + pulled.chunk.data.size.toUInt64
    st := st.mapInFlight fun flight =>
      { flight with downloadBodyBytes := newBodyBytes }

    let useRedirectDrainLimit ←
      match st.currentRequest with
      | some packet => ResponseBodyControl.isRedirectDrain packet.responseBodyControl
      | none => pure false

    let maxSize? : Option UInt64 :=
      if useRedirectDrainLimit then
        some config.redirectBodyDrainLimit.toUInt64
      else
        config.maxResponseBodySize.map (·.toUInt64)
    if let some maxSize := maxSize? then
      if newBodyBytes > maxSize then
        let err : IO.Error :=
          if useRedirectDrainLimit then
            .userError "redirect response body exceeds redirectBodyDrainLimit"
          else
            .userError "response body exceeds maximum allowed size"
        -- Header stage already resolved `packet`, so rejecting here is typically a
        -- no-op. The caller is listening on the response stream; surface the error
        -- through `closeWithError` so a pending `recv`/`readAll` sees it instead
        -- of a silent truncated EOF.
        if let some body := st.responseStream then
          if ¬(← Body.isClosed body) then body.closeWithError err
        return ← abortState (st.mapInFlight fun flight => { flight with responseStream := none }) err

    if let some body := st.responseStream then
      -- If the caller has dropped/closed the incoming side, the write fails.
      -- Silently swallowing the error is correct: the loop must continue pulling
      -- wire bytes to keep the connection in a valid state for reuse.
      try body.send pulled.chunk pulled.incomplete catch _ => pure ()

      if pulled.final then
        if ¬(← Body.isClosed body) then Body.close body
        st := st.mapInFlight fun flight => { flight with responseStream := none }

  return st

/--
Processes a single async I/O event, returning the updated state and a `shouldClose` flag that tells the main loop to exit.
-/
private def handleRecvEvent (config : Config) (state : ConnectionState) : Recv → Async (ConnectionState × Bool)
  | .bytes (some bytes) => do
    let newDownloadBytes := state.downloadBytes + bytes.size.toUInt64
    if let some w := state.downloadProgress then Watch.send w newDownloadBytes
    let st := { state with machine := state.machine.feed bytes }
    return (st.mapInFlight ({ · with downloadBytes := newDownloadBytes }), false)

  | .bytes none => do
    return ({ state with machine := state.machine.noMoreInput }, false)

  | .requestBody (some chunk) => do
    let newUploadBytes := state.uploadBytes + chunk.data.size.toUInt64
    if let some w := state.uploadProgress then Watch.send w newUploadBytes
    let st := { state with machine := state.machine.sendData #[chunk] }
    return (st.mapInFlight ({ · with uploadBytes := newUploadBytes }), false)

  | .requestBody none => do
    if let some body := state.requestBody then
      if ¬(← body.isClosed) then body.close
    let st := { state with machine := state.machine.userClosedBody }
    return (st.mapInFlight ({ · with requestBody := none }), false)

  | .bodyInterest interested => do
    return (← if interested then onBodyInterest config state else pure state, false)

  | .packet (some packet) => do
    let knownSize ← packet.request.body.getKnownSize
    let responseStream ← Body.mkStream
    return (onNewPacket config packet knownSize responseStream state, false)

  | .packet none => do
    return (state, true)

  | .close => do
    return (state, true)

  | .timeout => do
    return (← abortState state (.userError "request timeout"), true)

  | .shutdown => do
    return (← abortState state (.userError "connection shutdown"), false)

/--
Runs the main request/response processing loop for a single connection.
Drives the HTTP/1.1 state machine through four phases each iteration:
close finished readers, send buffered output, process H1 events, poll for I/O.
-/
protected def handle
    [Transport α]
    (socket : α)
    (machine : H1.Machine .sending)
    (config : Config)
    (connectionContext : CancellationContext)
    (requestChannel : Std.CloseableChannel RequestPacket) : Async Unit := do

  let mut state : ConnectionState := {
    machine := machine
    currentTimeout := config.keepAliveTimeout.val
    keepAliveTimeout := some config.keepAliveTimeout.val
    requiresData := false
    expectData := none
    inFlight := none
  }

  while ¬state.machine.halted do

    -- Phase 1: close any reader that the user has signalled is done.
    if let some body := state.requestBody then
      if ← body.isClosed then
        let newState := { state with machine := state.machine.userClosedBody }
        state := newState.mapInFlight fun flight => { flight with requestBody := none }

    -- Phase 1b: Auto-drain buffered response body bytes when the caller closed
    -- the response stream without consuming them. Without this, `canPullBody`
    -- stays true, `pollSocket` stays true, and the connection never reaches
    -- the idle keep-alive state needed to fire the idle timeout.
    let responseBodyClosed ← match state.responseStream with
      | some body => Body.isClosed body
      | none => pure true
    if state.machine.canPullBodyNow && responseBodyClosed then
      let mut m := state.machine
      while m.canPullBodyNow do
        let (m', _) := m.pullBody
        m := m'
      state := { state with machine := m }

    -- Phase 2: advance the state machine and flush any output.
    let (newMachine, step) := state.machine.step
    state := { state with machine := newMachine }

    if step.output.size > 0 then
      try Transport.sendAll socket #[step.output.toByteArray]
      catch _ =>
        state ← abortState state (.userError "connection write failed")
        break

    -- Phase 3: process all events emitted by this step.
    let (newState, sawFailure) ← processH1Events config step.events state

    state := newState

    if sawFailure then
      break

    -- Phase 4: wait for the next IO event.
    state := { state with requiresData := false }
    let event ← pollNextEvent config socket requestChannel connectionContext state
    let (newState, shouldClose) ← handleRecvEvent config state event
    state := newState
    if shouldClose then break

  -- Clean up: notify any in-flight request and close all open streams.
  discard <| abortState state (.userError "connection closed")

  discard <| EIO.toBaseIO requestChannel.close

  -- Drain any remaining queued packets.
  repeat do
    match ← requestChannel.tryRecv with
    | some packet => packet.onError (.userError "connection closed")
    | none => break

  Transport.close socket

end Connection

end Std.Http.Client
