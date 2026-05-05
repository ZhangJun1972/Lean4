/-
Copyright (c) 2026 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Kyle Miller
-/
module

prelude
public import Lean.Elab.ConfigEval.Types
public import Lean.Elab.ConfigEval.Basic
public import Lean.Elab.ConfigEval.Commands
public import Lean.Elab.ConfigEval.Instances
public import Lean.Elab.ConfigEval.MetaInstances
public import Lean.Elab.ConfigEval.Extra

/-!
# Configuration evaluation

This module is responsible for efficiently elaborating and evaluating syntax
used to configure tactics, commands, and term elaborators.

Users should import this module to ensure they have all the elaborators and
instances available.

The main interface are the `declare_core_config_elab`, `declare_term_config_elab`,
`declare_config_elab` and `declare_command_config_elab` commands, however the
system is designed to be flexible to support custom configurations.

These support user-defined configuration syntaxes without declaring them to the system.
See `Lean.Elab.ConfigEval.foldConfigM` for a specification of what is allowed.

## Notes for core Lean

Builtin elaborators should put their configuration types in, for example,
`Init.MetaTypes` or `Init.Meta.Defs` so that hovers can function when
nothing is imported.
-/
