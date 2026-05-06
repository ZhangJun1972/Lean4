/-
Copyright (c) 2026 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Kyle Miller
-/
module

prelude
public import Lean.Elab.ConfigEval.DeriveEvalTerm
public meta import Lean.Elab.ConfigEval.DeriveEvalTerm
public import Lean.Elab.ConfigEval.DeriveEvalExpr
public meta import Lean.Elab.ConfigEval.DeriveEvalExpr
public import Lean.Elab.ConfigEval.DeriveEvalConfigItem
public meta import Lean.Elab.ConfigEval.DeriveEvalConfigItem
public import Lean.Elab.Tactic.ElabTerm
import Lean.Linter.MissingDocs

public section

namespace Lean.Elab.ConfigEval

open Meta Term Command

/--
`ensure_eval_term_instance t` ensures there is a `ConfigItem.EvalTerm t` instance by
deriving one or more instances if it needs to.
-/
scoped elab vis?:(visibility)? kind:attrKind tk:"ensure_eval_term_instance " t:term : command => do
  let type ← liftTermElabM do withoutErrToSorry <| elabTermAndSynthesize t none
  ensureEvalTerm vis? kind tk t type

/--
`ensure_eval_expr_instance t` ensures there is a `ConfigItem.EvalExpr t` instance by
deriving one or more instances if it needs to.
-/
scoped elab vis?:(visibility)? kind:attrKind tk:"ensure_eval_expr_instance " t:term : command => do
  let type ← liftTermElabM do withoutErrToSorry <| elabTermAndSynthesize t none
  ensureEvalExpr vis? kind tk t type

/--
`ensure_eval_term_expr_instances t` is a macro for running both `ensure_eval_term_instance t`
and `ensure_eval_expr_instance t`, which ensurs there are `ConfigItem.EvalTerm t` and
`ConfigItem.EvalExpr t` instances by deriving one or more instances if it needs to.
-/
scoped macro vis?:(visibility)? kind:attrKind tk:"ensure_eval_term_expr_instances " t:term : command =>
  `($[$vis?]? $kind ensure_eval_term_instance%$tk $t
    $[$vis?]? $kind ensure_eval_expr_instance%$tk $t)

/--
`derive_eval_expr_instance_using_meta_eval type` defines a `ConfigItem.EvalExpr type` instance
using `Meta.evalExpr'` to evaluate expressions. This sort of item evaluator is a reasonable
backup strategy for infrequently used configuration options, if term- or expression-based
evaluation does not work and the cost of compilation is acceptible.

This should be avoided in core Lean due to the difficulties it creates for bootstrapping.
-/
scoped elab vis?:(visibility)? kind:attrKind tk:"derive_eval_expr_instance_using_meta_eval " t:term : command => do
  let type ← liftTermElabM do withoutErrToSorry <| elabTermAndSynthesize t none
  deriveEvalExprUsingMetaEval vis? kind tk t type

section
open Parser
/-- `except f1, f2, f3` disables generating setters for fields `f1`, `f2`, and `f3`
of the structure. -/
meta def configEntryExcept := leading_parser
  nonReservedSymbol "except " >> sepBy1 ident ", " (allowTrailingSep := true)
/--
- `key` matches a specific key
- `key.*` matches any keys for which `key` is a proper prefix
- `*` matches all keys
-/
meta def configEntryHandlerKey := leading_parser
  (ident >> optional (checkNoWsBefore >> "." >> checkNoWsBefore >> "*")) <|> "*"
/--
`option key := fun cfg item => ...` adds a configuration option named `key` with the given
expression as its handler. The handler is only called when the key is an exact match.
The provided value is in `item.value`. Such a handler implies `except key`.

`option key.* := fun cfg item => ...` adds configuration options with `key` as a proper prefix.
The most-specific `*` handler is called if no handlers for exact matches apply.
-/
meta def configEntryHandler := leading_parser
  nonReservedSymbol "option " >> configEntryHandlerKey >> " := " >> termParser
meta def configEntry := leading_parser
  configEntryExcept <|> configEntryHandler
meta def configEntries := leading_parser
  "where" >> (sepByIndent configEntry "; " (allowTrailingSep := true))
end

meta def mkEvalConfigItemView (entries? : Option (TSyntax ``configEntries)) :
    CommandElabM EvalConfigItemView := do
  let mut exceptFields : Array Name := #[]
  let mut handlers : Array EvalConfigItemHandler := #[]
  if let some entries := entries? then
    match entries with
    | `(configEntries| where $[$entries:configEntry];*) =>
      for entry in entries do
        match entry with
        | `(configEntry| except $[$fields],*) =>
          exceptFields := exceptFields ++ fields.map (·.getId.eraseMacroScopes)
        | `(configEntry| option $key:configEntryHandlerKey := $body) =>
          let (optName, kind) ←
            match key with
            | `(configEntryHandlerKey| $opt:ident) => pure (opt.getId.eraseMacroScopes, .exact)
            | `(configEntryHandlerKey| $opt:ident.*) => pure (opt.getId.eraseMacroScopes, .wildcard)
            | `(configEntryHandlerKey| *) => pure (.anonymous, .wildcard)
            | _ => throwUnsupportedSyntax
          handlers := handlers.push { ref := key, key := optName, body, kind }
        | _ => throwUnsupportedSyntax
    | _ => throwUnsupportedSyntax
  return { exceptFields, handlers }

/--
`def_eval_config_item f binders* for struct` defines a `ConfigEval.EvalConfigItem struct` structure named `f`
parameterized by the given binders. This structure contains a setter for updating a configuration
object of type `struct`.

The command will transitively derive any necessary `ConfigEval.EvalTerm`/`ConfigEval.EvalExpr`
instances to support evaluation of configuration options for structure fields.
The syntax supports `public`/`private` modifiers. It also supports `scoped`/`local`, which apply
to any derived instances.

The `EvalConfigItem struct` structure can be customized with a `where` clause.
The possible items of the `where` clause are:
- `except f1, f2, f3` disables generating setters for fields `f1`, `f2`, and `f3` of `struct`
- `option key := fun cfg item => ...` adds a configuration option named `key` with the given
expression as its handler. The handler is only called when the key is an exact match.
The provided value is in `item.value`. Such a handler implies `except key`.
- `option key* := fun cfg item => ...` adds configuration options with `key` as a proper prefix.
The most-specific `*` handler is called if no handlers for exact matches apply.
-/
elab (name := defEvalConfigItemCmd)
    doc?:(docComment)? vis?:(visibility)? kind:attrKind tk:"def_eval_config_item " fn:ident binders:(bracketedBinder)* " for " struct:ident
    entries?:(configEntries)? : command => do
  let view ← mkEvalConfigItemView entries?
  defEvalConfigItem doc? vis? kind tk struct fn binders view

open Linter.MissingDocs in
@[builtin_missing_docs_handler defEvalConfigItemCmd]
private def checkDefEvalConfigItemCmd : SimpleHandler := mkSimpleHandler "config elab"

open Lean.Parser.Term in
private meta def getBracketedBinderArgs (stx : Syntax) : MacroM (Array Term) :=
  match stx with
  | `(bracketedBinderF|($ids:ident* $[: $ty?]? $(_annot?)?)) => return ids
  | `(bracketedBinderF|{$ids:ident* $[: $_]?})               => return ids
  | `(bracketedBinderF|⦃$ids:ident* : $_⦄)                    => return ids
  | `(bracketedBinderF|[$id:ident : $_])                     => return #[id]
  | `(bracketedBinderF|[$_])                                 => return #[mkHole stx]
  | _                                                        => Macro.throwErrorAt stx "Unsupported binder"

/--
`declare_core_config_elab f struct binders* [where ...]` defines a configuration elaborator
```lean
f binders* (cfg : Syntax) (init : struct := {}) (logExceptions : Bool := false) : CoreM struct
```
that evaluates the `cfg` configuration items to update `init`.
Acceptable configuration syntax is documented in `Lean.Elab.ConfigEval.foldConfigM`,
which includes anything that looks like `Lean.Parser.Term.optConfig`, possibly wrapped
in null nodes.

The command will transitively derive any necessary `ConfigEval.EvalTerm`/`ConfigEval.EvalExpr`
instances to support evaluation of configuration options for structure fields.
These instances will be `private local` to this command.

See `ConfigEval.defEvalConfigItemCmd` for further documentation.

See also `declare_term_config_elab`, `declare_config_elab`, and `declare_command_config_elab`.
-/
macro (name := elabDeclareCoreConfigElab) doc?:(docComment)? vis?:(visibility)?
    tk:"declare_core_config_elab" elabName:ident type:ident binders:(bracketedBinder)*
    entries?:(configEntries)? : command => do
  let fnName := mkIdentFrom elabName (elabName.getId ++ `evalConfigItem)
  let binderArgs ← binders.foldlM (init := #[]) fun args binder => do
    pure <| args ++ (← getBracketedBinderArgs binder)
  let cfg := mkIdent `cfg
  let init := mkIdent `init
  let logExceptions := mkIdent `logExceptions
  withRef (mkNullNode #[tk, elabName, type]) do
    `(section
      private local def_eval_config_item $fnName $[$binders]* for $type $[$entries?:configEntries]?
      $[$doc?:docComment]?
      $[$vis?:visibility]? def $elabName $[$binders]* ($cfg : Lean.Syntax) ($init : $type := {}) ($logExceptions : Bool := false) : CoreM $type := do
        let eval : EvalConfigItem $type := @$fnName $binderArgs*
        let onErr := EvalConfigItem.defaultOnErr (cfgType? := mkConst ``$type)
        eval.setConfig' $init $cfg (onErr := onErr) (logExceptions := $logExceptions)
      end)

open Linter.MissingDocs in
@[builtin_missing_docs_handler elabDeclareCoreConfigElab]
private def checkDeclareCoreConfigElab : SimpleHandler := mkSimpleHandler "config elab"

/--
`declare_term_config_elab f struct binders* [where ...]` defines a configuration elaborator
```lean
f binders* (cfg : Syntax) (init : struct := {}) : TermElabM struct
```
that evaluates the `cfg` configuration items to update `init`.
Acceptable configuration syntax is documented in `Lean.Elab.ConfigEval.foldConfigM`,
which includes anything that looks like `Lean.Parser.Term.optConfig`, possibly wrapped
in null nodes.

It uses the current `errToSorry` state to decide whether or not to recover by logging errors
and proceeding when there are invalid options, or raising an exception.

The command will transitively derive any necessary `ConfigEval.EvalTerm`/`ConfigEval.EvalExpr`
instances to support evaluation of configuration options for structure fields.
These instances will be `private local` to this command.

See `ConfigEval.defEvalConfigItemCmd` for further documentation.

See also `declare_core_config_elab`, `declare_config_elab`, and `declare_command_config_elab`.
-/
macro (name := elabDeclareTermConfigElab) doc?:(docComment)? vis?:(visibility)?
    tk:"declare_term_config_elab" elabName:ident type:ident binders:(bracketedBinder)*
    entries?:(configEntries)? : command => do
  let fnName := mkIdentFrom elabName (elabName.getId ++ `evalConfigItem)
  let binderArgs ← binders.foldlM (init := #[]) fun args binder => do
    pure <| args ++ (← getBracketedBinderArgs binder)
  let cfg := mkIdent `cfg
  let init := mkIdent `init
  withRef (mkNullNode #[tk, elabName, type]) do
    `(section
      private local def_eval_config_item $fnName $[$binders]* for $type $[$entries?:configEntries]?
      $[$doc?:docComment]?
      $[$vis?:visibility]? def $elabName $[$binders]* ($cfg : Lean.Syntax) ($init : $type := {}) : TermElabM $type := do
        let eval : EvalConfigItem $type := @$fnName $binderArgs*
        let onErr := EvalConfigItem.defaultOnErr (cfgType? := mkConst ``$type)
        eval.setConfig' $init $cfg (onErr := onErr) (logExceptions := (← read).errToSorry)
      end)

open Linter.MissingDocs in
@[builtin_missing_docs_handler elabDeclareTermConfigElab]
private def checkDeclareTermConfigElab : SimpleHandler := mkSimpleHandler "config elab"

/--
`declare_config_elab f struct binders* [where ...]` defines a configuration elaborator
```lean
f binders* (cfg : Syntax) (init : struct := {}) : TacticM struct
```
that evaluates the `cfg` configuration items to update `init`.
Acceptable configuration syntax is documented in `Lean.Elab.ConfigEval.foldConfigM`,
which includes anything that looks like `Lean.Parser.Term.optConfig`, possibly wrapped
in null nodes.

It uses the current `recover` state to decide whether or not to recover by logging errors
and proceeding when there are invalid options, or raising an exception.

The command will transitively derive any necessary `ConfigEval.EvalTerm`/`ConfigEval.EvalExpr`
instances to support evaluation of configuration options for structure fields.
These instances will be `private local` to this command.

See `ConfigEval.defEvalConfigItemCmd` for further documentation.

See also `declare_core_config_elab`, `declare_term_config_elab`, and `declare_command_config_elab`.
-/
macro (name := elabDeclareTacticConfig) doc?:(docComment)? vis?:(visibility)?
    tk:"declare_config_elab" elabName:ident type:ident binders:(bracketedBinder)*
    entries?:(configEntries)? : command => do
  let fnName := mkIdentFrom elabName (elabName.getId ++ `evalConfigItem)
  let binderArgs ← binders.foldlM (init := #[]) fun args binder => do
    pure <| args ++ (← getBracketedBinderArgs binder)
  let cfg := mkIdent `cfg
  let init := mkIdent `init
  withRef (mkNullNode #[tk, elabName, type]) do
    `(section
      private local def_eval_config_item $fnName $[$binders]* for $type $[$entries?:configEntries]?
      $[$doc?:docComment]?
      $[$vis?:visibility]? def $elabName $[$binders]* ($cfg : Lean.Syntax) ($init : $type := {}) : $(mkCIdent ``Tactic.TacticM) $type := do
        let recover := (← read).recover
        let eval : EvalConfigItem $type := @$fnName $binderArgs*
        let onErr := EvalConfigItem.defaultOnErr (cfgType? := mkConst ``$type)
        Tactic.runTermElab <| eval.setConfig' $init $cfg (onErr := onErr) (logExceptions := recover)
      end)

open Linter.MissingDocs in
@[builtin_missing_docs_handler elabDeclareTacticConfig]
private def checkDeclareTacticConfig : SimpleHandler := mkSimpleHandler "config elab"

/--
`declare_core_config_elab f struct binders* [where ...]` defines a configuration elaborator
```lean
f binders* (cfg : Syntax) (init : struct := {}) (logExceptions : Bool := true) : CommandElabM struct
```
that evaluates the `cfg` configuration items to update `init`.
Acceptable configuration syntax is documented in `Lean.Elab.ConfigEval.foldConfigM`,
which includes anything that looks like `Lean.Parser.Term.optConfig`, possibly wrapped
in null nodes.

The command will transitively derive any necessary `ConfigEval.EvalTerm`/`ConfigEval.EvalExpr`
instances to support evaluation of configuration options for structure fields.
These instances will be `private local` to this command.

See `ConfigEval.defEvalConfigItemCmd` for further documentation.

See also `declare_core_config_elab`, `declare_term_config_elab`, and `declare_config_elab`.
-/
macro (name := elabDeclareCommandConfig) doc?:(docComment)? vis?:(visibility)?
    tk:"declare_command_config_elab" elabName:ident type:ident binders:(bracketedBinder)*
    entries?:(configEntries)? : command => do
  let fnName := mkIdentFrom elabName (elabName.getId ++ `evalConfigItem)
  let binderArgs ← binders.foldlM (init := #[]) fun args binder => do
    pure <| args ++ (← getBracketedBinderArgs binder)
  let cfg := mkIdent `cfg
  let init := mkIdent `init
  let logExceptions := mkIdent `logExceptions
  withRef (mkNullNode #[tk, elabName, type]) do
    `(section
      private local def_eval_config_item $fnName $[$binders]* for $type $[$entries?:configEntries]?
      $[$doc?:docComment]?
      $[$vis?:visibility]? def $elabName $[$binders]* ($cfg : Lean.Syntax) ($init : $type := {}) ($logExceptions : Bool := true) : $(mkCIdent ``CommandElabM) $type := do
        let eval : EvalConfigItem $type := @$fnName $binderArgs*
        let onErr := EvalConfigItem.defaultOnErr (cfgType? := mkConst ``$type)
        Command.liftTermElabM <| eval.setConfig' $init $cfg (onErr := onErr) (logExceptions := $logExceptions)
      end)

open Linter.MissingDocs in
@[builtin_missing_docs_handler elabDeclareCommandConfig]
private def checkCommandConfigElab : SimpleHandler := mkSimpleHandler "config elab"

end Lean.Elab.ConfigEval
