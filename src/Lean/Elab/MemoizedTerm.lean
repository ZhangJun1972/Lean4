/-
Copyright (c) 2026 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Kim Morrison
-/
module

prelude
public import Lean.Elab.Term
import Init.Syntax

public section

/-!
# `memoized%` and `memo` syntax

`memoized%` provides a compact representation of expressions with shared subexpressions.
At each first DFS occurrence of a shared subexpression, `(memo _s0 := expr)` names it;
subsequent occurrences use the bare name `_s0`.

```
memoized% @Nat.add (memo _s0 := @Nat.mul (memo _s1 := @Nat.succ @Nat.zero) _s1) _s0
```

This elaborates by floating all `memo` bindings to `let` declarations:
```
let _s1 := @Nat.succ @Nat.zero; let _s0 := @Nat.mul _s1 _s1; @Nat.add _s0 _s0
```

The output of `set_option pp.memoize true` uses this format, enabling round-tripping.
-/

namespace Lean.Elab.Term.Memoized

open Lean Elab Term

syntax (name := memoBind) "memo " ident " := " term : term
syntax (name := memoBlock) "memoized%" term : term

private partial def extractBindings (stx : Syntax) :
    StateM (Array (Ident × Syntax)) Syntax := do
  if stx.isOfKind ``memoBind then
    let name := stx[1]
    let val ← extractBindings stx[3]
    modify (·.push (⟨name⟩, val))
    return name
  else if stx.isOfKind ``memoBlock then
    return stx
  else
    let args := stx.getArgs
    if args.size == 0 then return stx
    let mut newArgs := args
    for i in [:args.size] do
      newArgs := newArgs.set! i (← extractBindings args[i]!)
    return stx.setArgs newArgs

@[builtin_term_elab memoBlock]
def elabMemoBlock : TermElab := fun stx expectedType? => do
  let inner := stx[1]
  let (rewritten, bindings) := (extractBindings inner).run #[]
  if bindings.isEmpty then
    elabTerm inner expectedType?
  else
    let mut result : Term := ⟨rewritten⟩
    for (name, val) in bindings.reverse do
      let valTerm : Term := ⟨val⟩
      result ← `(let $name := $valTerm; $result)
    elabTerm result expectedType?

@[builtin_term_elab memoBind]
def elabMemoBind : TermElab := fun _stx _expectedType? =>
  throwError "`memo` must appear inside a `memoized%` block"

end Lean.Elab.Term.Memoized
