/-
Copyright (c) 2024 Amazon.com, Inc. or its affiliates. All Rights Reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Leonardo de Moura
-/
module
prelude
public import Lean.Elab.Tactic.Grind.Basic
import Lean.Elab.ConfigEval

public section
namespace Lean.Elab.Tactic.Grind

private def_eval_config_item evalConfigItem for Grind.Config

def elabConfigItems (init : Grind.Config) (items : Array Syntax)
    : TermElabM Grind.Config := do
  evalConfigItem.setConfigs' init items (logExceptions := false)

def withConfigItems (items : Array Syntax)
    (k : GrindTacticM α) : GrindTacticM α := do
  if items.isEmpty then
    k
  else
    let config := (← read).ctx.config
    let config ← elabConfigItems config items
    withReader (fun c => { c with ctx.config := config }) do k

end Lean.Elab.Tactic.Grind
