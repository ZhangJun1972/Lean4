/-
Copyright (c) 2026 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Kyle Miller
-/
module

prelude
public import Lean.Elab.ConfigEval.Types
public import Lean.Elab.SyntheticMVars
import Lean.Elab.ConfigEval.Util

/-!
# Basic interface for configuration evaluation
-/

public section

namespace Lean.Elab.ConfigEval

open Meta Term

def evalTermWithRef {α : Type} [EvalTerm α] (stx : Term) : TermElabM α :=
  withRef stx <| Prod.fst <$> evalTerm stx

/--
Evaluate `stx` using either `evalExpr`.
-/
def evalExprWithElab {α : Type} [EvalExpr α] (stx : Term) : TermElabM α :=
  withRef stx do
    let ty? := EvalExpr.expectedType? α
    let e ← Term.withSynthesize <| Term.elabTermEnsuringType stx ty?
    let e ← instantiateMVars e
    if e.hasSorry then
      if e.hasSyntheticSorry then
        -- An error has already been logged.
        throwAbortTerm
      throwError "Expression contains `sorry`:{indentExpr e}"
    if (← Term.logUnassignedUsingErrorInfos (← getMVars e)) then
      throwAbortTerm
    catchInternalId unsupportedSyntaxExceptionId
      (evalExpr e)
      (fun _ => do
        let extra := if let some ty := ty? then m!"\nof type `{ty}`" else m!""
        throwError "Could not evaluate the expression{indentExpr e}{extra}")

/--
Evaluate `stx` using either `evalStx` or `evalExpr`.
-/
def evalTermOrExprWithElab {α : Type} [EvalTerm α] [EvalExpr α] (stx : Term) : TermElabM α :=
  withRef stx do
    catchInternalId unsupportedSyntaxExceptionId
      (Prod.fst <$> evalTerm stx)
      (fun _ => do
        evalExprWithElab stx)

private partial def stripParens : Term → Term
  | `(($t)) => stripParens t
  | t => t

@[inline] def EvalTerm.evalTermWithInfo {α : Type}
    (expectedType? : Option Expr) (f : Term → TermElabM (α × Expr)) (stx : Term) :
    TermElabM (α × Expr) := do
  let (v, e) ← withRef stx <| f (stripParens stx)
  if (← getInfoState).enabled then
    addTermInfo' stx e (expectedType? := expectedType?)
  return (v, e)

/-- Like `evalTermWithInfo`, but uses an existing `ToExpr` instance
for `expectedType?` and for constructing the expression. -/
@[inline] def EvalTerm.evalTermWithInfo' {α : Type} [ToExpr α]
    (f : Term → TermElabM α) :
    Term → TermElabM (α × Expr) :=
  evalTermWithInfo (toTypeExpr α) (fun stx => do
    let v ← f stx
    return (v, toExpr v))

/--
Evaluates `f e`, and if that does `throwUnsupportedExpr`, evaluates `f (← whnf e)`.
If either throw another exception, aborts immediately with that exception.
If both do `throwUnsupportedExpr`, then this generates an exception.
-/
def EvalExpr.withWHNF {α : Type} (f : Expr → MetaM α) (e : Expr) (errMsg : MessageData) : MetaM α := do
  catchInternalId unsupportedExprExceptionId
    (f e)
    (fun _ =>
      catchInternalId unsupportedExprExceptionId
        (do f (← whnf e))
        (fun _ =>
          throwError "Could not evaluate the expression:{indentExpr e}{errMsg}"))

def ConfigItem.isAnonymous (item : ConfigItem) : Bool := item.optionComps.isEmpty

def ConfigItem.root (item : ConfigItem) : Syntax :=
  match item.optionComps with
  | c :: _ => c
  | _      => .missing

def ConfigItem.getRootStr (item : ConfigItem) : String :=
  if let .str _ s := item.root.getId then
    s
  else
    ""

def ConfigItem.prevRoot? (item : ConfigItem) : Option Syntax :=
  item.prevOptionComps[0]?

def ConfigItem.prevRoot (item : ConfigItem) : Syntax :=
  match item.prevOptionComps with
  | c :: _ => c
  | _      => .missing

/--
Gets the current name of the option after any shifting.
For example, if an option is named `a.b.c.d` and there is a handler
for `a.b.*`, then the handler receives a `ConfigItem` whose current option
name is `c.d`.
-/
def ConfigItem.getCurrOptionName (item : ConfigItem) : Name :=
  (item.optionComps.map (·.getId)).foldl (init := .anonymous) Name.appendCore

/--
Drops the first component of the `optionName`, returning the new config item.
The first component is stored at the front of `prevOptionComps`.
-/
def ConfigItem.shift (item : ConfigItem) : ConfigItem :=
  { item with
    optionComps := item.optionComps.tail
    prevOptionComps := item.root :: item.prevOptionComps }

def ConfigItem.checkNotBool (item : ConfigItem) : TermElabM Unit := do
  if item.bool?.isSome then
    throwErrorAt item.option m!"Option is not boolean-valued, so `({item.origOptionName} := ...)` syntax must be used"

def ConfigItem.throwInvalidOption {α} (item : ConfigItem) (structName? : Option Name) : TermElabM α :=
  let name := item.origOptionName
  let nameMsg := if name.isAnonymous then m!"" else m!" `{name}`"
  let structMsg := if let some structName := structName? then m!" for `{.ofConstName structName}`" else m!""
  throwErrorAt item.option "Invalid configuration option{nameMsg}{structMsg}"

def ConfigItem.addConstInfoForPrevRoot (item : ConfigItem) (n : Name) : TermElabM Unit := do
  if (← getInfoState).enabled then
    if (← getEnv).contains n then -- in case we are in Lean prelude
      addConstInfo item.prevRoot n

mutual
/--
Interprets `cfg` as configuration item or list of configuration items.

Items are interpreted in a way that allows user-defined configurations.
Nearly anything that looks like configuration items or lists of configuration items
will be interpreted. We're expecting an item that has one of the following formats:
- `"(" ident/atom ":=" syntax ")"`
- `"+" ident/atom`
- `"-" ident/atom`

The specification:
- A null node is a list of configurations
- A one-argument node wrapping a node is considered to be a wrapper like `optConfig` or `configItem`.
- A node with at most two arguments starting with a "+"/"-" atom, and whose second
  argument is an ident or atom or missing is a `posConfigItem`/`negConfigItem`
- A node with at most five arguments starting with a "(" atom and whose second argument
  is an ident or atom or missing is a `valConfigItem`. The fourth argument is the value,
  and it is allowed to have arbitary syntax (it does not need to be a `Term`).

We trust that any atoms are valid as idents. The atom will be parsed using `String.toName`
to form the name. (Small optimization: if the name doesn't contain `.`, we use `Name.mkSimple`
to skip parsing. Atoms must not contain numerals or `«»` escapes.)

On interpretation error, `onErr` is called with the current configuration object and the offending
syntax item. It process the item itself or otherwise throw an error. We do not call `onErr`
if `cfg` is `Syntax.missing`.
-/
@[specialize] partial def foldConfigM {m α} [Monad m] [MonadRef m] (init : α) (cfg : Syntax)
    (k : α → ConfigItem → m α)
    (onErr : α → Syntax → m α) :
    m α := do
  let doFail (_ : Unit) := withRef cfg do onErr init cfg
  -- Matches ident/atom/missing. Trusts that atoms are valid as idents and converts to idents,
  -- preserving the original source info.
  let getIdent? (stx : Syntax) : Option Ident :=
    match stx with
    | .missing => some ⟨.missing⟩
    | .ident .. => some ⟨stx⟩
    | .atom si val =>
      let n := if val.contains '.' then String.toName val else Name.mkSimple val
      some ⟨.ident si val.toRawSubstring n []⟩
    | _ => none
  let isPosNeg? (val : String) : Option Bool :=
    if val == "+" then some true
    else if val == "-" then some false
    else none
  if cfg.isOfKind nullKind || cfg.getNumArgs == 1 then
    foldConfigsM init cfg.getArgs k onErr
  else if cfg.getNumArgs ≥ 1 then
    let arg0 := cfg.getArg 0
    match arg0 with
    | .atom _ val =>
      if let some b := isPosNeg? val then
        if cfg.getNumArgs ≤ 2 then
          if let some ident := getIdent? (cfg.getArg 1) then
            let value := if b then mkCIdentFrom arg0 ``true else mkCIdentFrom arg0 ``false
            return ← k init { ref := cfg, option := ident, bool? := some b, value }
      else if val == "(" then
        if cfg.getNumArgs ≤ 5 then
          if let some ident := getIdent? (cfg.getArg 1) then
            -- Assuming `cfg.getArg 2` is `:=`
            return ← k init { ref := cfg, option := ident, value := cfg.getArg 3 }
      doFail ()
    | _ => doFail ()
  else if cfg.isMissing then
    return init
  else
    doFail ()

/--
Like `foldConfigM` but takes an array of configurations or configuration items.
-/
@[specialize] partial def foldConfigsM {m α} [Monad m] [MonadRef m] (init : α) (cfgs : Array Syntax)
    (k : α → ConfigItem → m α)
    (onErr : α → Syntax → m α) :
    m α := do
  cfgs.foldlM (init := init) fun x cfg' => foldConfigM x cfg' k onErr

end

def EvalConfigItem.trySet {α} (eval : EvalConfigItem α)
    (config : α) (item : ConfigItem) (logExceptions : Bool) := do
  try
    eval.set config item
  catch ex =>
    if logExceptions then
      logException ex
      return config
    else
      throw ex

/--
Applies the configuration `cfg` to `init` using `eval.set`.
If `logExceptions` is true, then catches and logs exceptions.

The `onErr` callback is used for invalid configuration syntax.

Note: this should be run from within `runConfigElab`.
-/
def EvalConfigItem.setConfig {α} (eval : EvalConfigItem α)
    (init : α) (cfg : Syntax)
    (onErr : α → Syntax → TermElabM α := fun _ _ => throwUnsupportedSyntax)
    (logExceptions : Bool := false) : TermElabM α :=
  foldConfigM init cfg (eval.trySet (logExceptions := logExceptions)) onErr

/--
Applies the configuration `cfg` to `init` using `eval.set`.
If `logExceptions` is true, then catches and logs exceptions.

The `onErr` callback is used for invalid configuration syntax.

Note: this should be run from within `runConfigElab`.
-/
def EvalConfigItem.setConfigs {α} (eval : EvalConfigItem α)
    (init : α) (cfgs : Array Syntax)
    (onErr : α → Syntax → TermElabM α := fun _ _ => throwUnsupportedSyntax)
    (logExceptions : Bool := false) : TermElabM α :=
  foldConfigsM init cfgs (eval.trySet (logExceptions := logExceptions)) onErr

/--
Runs `mx` using a fresh meta and term state, and ensures the environment is not modified.
This should be used around any configuration elaboration.
-/
def runConfigElab {α} (mx : TermElabM α) (errToSorry : Bool) : CoreM α :=
  withoutModifyingEnv do
    MetaM.run' <| TermElabM.run' (ctx := { errToSorry }) <| withSaveInfoContext mx

/--
Calls `EvalConfigItem.setConfig'` from within `runConfigElab`.
If `logExceptions` is true, then `errToSorry` is enabled.
-/
def EvalConfigItem.setConfig' {α : Type} (eval : EvalConfigItem α)
    (init : α) (cfg : Syntax)
    (onErr : α → Syntax → TermElabM α := fun _ _ => throwUnsupportedSyntax)
    (logExceptions : Bool := false) : CoreM α :=
  runConfigElab (eval.setConfig init cfg onErr logExceptions) logExceptions

/--
Calls `EvalConfigItem.setConfigs'` from within `runConfigElab`.
If `logExceptions` is true, then `errToSorry` is enabled.
-/
def EvalConfigItem.setConfigs' {α : Type} (eval : EvalConfigItem α)
    (init : α) (cfgs : Array Syntax)
    (onErr : α → Syntax → TermElabM α := fun _ _ => throwUnsupportedSyntax)
    (logExceptions : Bool := false) : CoreM α :=
  runConfigElab (eval.setConfigs init cfgs onErr logExceptions) logExceptions

end Lean.Elab.ConfigEval
