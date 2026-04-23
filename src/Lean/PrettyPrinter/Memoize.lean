/-
Copyright (c) 2026 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Kim Morrison
-/
module

prelude
import Lean.PrettyPrinter.Delaborator.Options
import Lean.Util.ShareCommon
import Lean.Data.SMap
public import Lean.Expr
import Init.While

public section

/-!
# Memoized pretty-printing

Pretty-prints `Expr` values with shared subexpression identification using
`memoized%`/`memo` syntax. When `pp.memoize` is `true`, shared closed subexpressions
are printed once with `(memo _s0 := ...)` and referenced by name thereafter.

The output is designed to round-trip: `memoized%` elaborates the expression back
by floating `memo` bindings to `let` declarations.
-/

namespace Lean.PrettyPrinter

private def isTrivial (e : Expr) : Bool :=
  e.isFVar || e.isBVar || e.isLit || e.isConst || e.isSort || e.isMVar

private partial def exprWeight (e : Expr) : Nat :=
  match e with
  | .app f a => 1 + exprWeight f + exprWeight a
  | .lam _ t b _ => 1 + exprWeight t + exprWeight b
  | .forallE _ t b _ => 1 + exprWeight t + exprWeight b
  | .letE _ t v b _ => 1 + exprWeight t + exprWeight v + exprWeight b
  | .mdata _ e => exprWeight e
  | .proj _ _ e => 1 + exprWeight e
  | _ => 1

/-- Zeta-reduce all `letE` bindings and beta-reduce all redexes. -/
partial def zetaBetaReduce (e : Expr) : Expr :=
  match e with
  | .letE _ _ v b _ =>
    zetaBetaReduce (b.instantiate1 (zetaBetaReduce v))
  | .app f a =>
    let f' := zetaBetaReduce f
    let a' := zetaBetaReduce a
    match f' with
    | .lam _ _ b _ => zetaBetaReduce (b.instantiate1 a')
    | _ => .app f' a'
  | .lam n t b bi => .lam n (zetaBetaReduce t) (zetaBetaReduce b) bi
  | .forallE n t b bi => .forallE n (zetaBetaReduce t) (zetaBetaReduce b) bi
  | .mdata m e => .mdata m (zetaBetaReduce e)
  | .proj s i e => .proj s i (zetaBetaReduce e)
  | _ => e

-- ── Subexpression counting ──

private partial def countSubexprs (e : Expr)
    (counts : IO.Ref (Std.HashMap Expr Nat)) : IO Unit := do
  if isTrivial e then return
  let c ← counts.get
  let prev := c.getD e 0
  counts.set (c.insert e (prev + 1))
  if prev == 0 then
    match e with
    | .app f a => countSubexprs f counts; countSubexprs a counts
    | .lam _ t b _ => countSubexprs t counts; countSubexprs b counts
    | .forallE _ t b _ => countSubexprs t counts; countSubexprs b counts
    | .letE _ t v b _ =>
      countSubexprs t counts; countSubexprs v counts; countSubexprs b counts
    | .mdata _ e => countSubexprs e counts
    | .proj _ _ e => countSubexprs e counts
    | _ => pure ()

-- ── Printing ──

private def escapeString (s : String) : String :=
  s.toList.foldl (fun acc c =>
    acc ++ match c with
    | '\\' => "\\\\"
    | '"' => "\\\""
    | '\n' => "\\n"
    | '\t' => "\\t"
    | '\r' => "\\r"
    | c => c.toString) ""

private def hasSpace (s : String) : Bool :=
  s.toList.any (· == ' ')

private def strStartsWith (s prefix_ : String) : Bool :=
  s.toList.take prefix_.toList.length == prefix_.toList

private def wrapParens (s : String) : String :=
  if hasSpace s && !strStartsWith s "(" && !strStartsWith s "(memo " then
    "(" ++ s ++ ")"
  else s

private partial def ppLevel : Level → String
  | .zero => "0"
  | .succ .zero => "1"
  | .succ (.param n) => toString n ++ " + 1"
  | .succ l => "(" ++ ppLevel l ++ ") + 1"
  | .max l1 l2 => "max (" ++ ppLevel l1 ++ ") (" ++ ppLevel l2 ++ ")"
  | .imax l1 l2 => "imax (" ++ ppLevel l1 ++ ") (" ++ ppLevel l2 ++ ")"
  | .param name => toString name
  | .mvar id => "?u." ++ toString id.name

/-- Pretty-print a level for use after `Sort`, wrapping in parens only when needed. -/
private def ppLevelAtom (l : Level) : String :=
  match l with
  | .zero => "0"
  | .succ .zero => "1"
  | _ => "(" ++ ppLevel l ++ ")"

/-- Pretty-print a level for Sort, using `_` for universe params to let Lean infer them. -/
private partial def ppLevelInfer : Level → String
  | .zero => "0"
  | .succ .zero => "1"
  | .succ l => "(" ++ ppLevelInfer l ++ " + 1)"
  | .param _ => "_"
  | .mvar _ => "_"
  | .max l1 l2 => "(max (" ++ ppLevelInfer l1 ++ ") (" ++ ppLevelInfer l2 ++ "))"
  | .imax l1 l2 => "(imax (" ++ ppLevelInfer l1 ++ ") (" ++ ppLevelInfer l2 ++ "))"

/-- Pretty-print a Sort level for round-tripping — uses `_` for params. -/
private def ppSortLevel (l : Level) : String :=
  if l.hasParam then ppLevelInfer l else ppLevelAtom l

private def binderOpen : BinderInfo → String
  | .default => "("
  | .implicit => "{"
  | .strictImplicit => "⦃"
  | .instImplicit => "["

private def binderClose : BinderInfo → String
  | .default => ")"
  | .implicit => "}"
  | .strictImplicit => "⦄"
  | .instImplicit => "]"

/-- Format a name for use in syntax, quoting with «» if needed. -/
private def quoteName (n : Name) : String :=
  match n with
  | .str .anonymous s =>
    match Name.escapePart s (needsEscape s) with
    | some escaped => escaped
    | none => toString n
  | _ => toString n
where
  needsEscape (s : String) : Bool :=
    -- Keywords and reserved words that conflict with binder position
    s == "let" || s == "if" || s == "then" || s == "else" || s == "do" || s == "return" ||
    s == "match" || s == "fun" || s == "where" || s == "have" || s == "show" || s == "by" ||
    s == "in" || s == "for" || s == "with" || s == "def" || s == "theorem" || s == "class" ||
    s == "instance" || s == "structure" || s == "inductive" || s == "section" || s == "namespace" ||
    s == "end" || s == "import" || s == "open" || s == "variable" || s == "set_option" ||
    s == "mutual" || s == "noncomputable" || s == "unsafe" || s == "private" || s == "protected" ||
    s == "abbrev" || s == "opaque" || s == "axiom" || s == "example" || s == "macro" ||
    s == "syntax" || s == "notation" || s == "prefix" || s == "infix" || s == "infixl" ||
    s == "infixr" || s == "postfix"

/-- Sanitize a binder name: strip macro scopes and avoid shadowing existing bvars. -/
private partial def freshBinderName (n : Name) (bvars : Array Name) : Name :=
  let base := if n.isAnonymous then `_a else n.eraseMacroScopes
  if !bvars.contains base then base
  else go base 1
where
  go (base : Name) (i : Nat) : Name :=
    let candidate := Name.mkSimple (toString base ++ "_" ++ toString i)
    if !bvars.contains candidate then candidate else go base (i + 1)

private def ppAtom (e : Expr) (bvars : Array Name) : String :=
  match e with
  | .bvar n =>
    if n < bvars.size then quoteName bvars[bvars.size - 1 - n]!
    else "#bound" ++ toString n
  | .fvar id => toString id.name
  | .mvar id => "?m." ++ toString id.name
  | .sort .zero => "Prop"
  | .sort (.succ .zero) => "Type"
  | .sort l => "Sort " ++ ppSortLevel l
  | .const name [] => "@" ++ toString name
  | .const name us =>
    let lvls := ", ".intercalate (us.map ppLevelInfer)
    "@" ++ toString name ++ ".{" ++ lvls ++ "}"
  | .lit (.natVal n) => toString n
  | .lit (.strVal s) => "\"" ++ escapeString s ++ "\""
  | _ => "<expr>"

private structure PPCtx where
  sharedSet : Std.HashSet Expr
  names : IO.Ref (Std.HashMap Expr Name)
  emitted : IO.Ref (Std.HashSet Expr)
  nextId : IO.Ref Nat
  binderNames : Std.HashSet Name
  outer? : Option PPCtx := none  -- outer scope for closed sharing

/-- Check if `e` is shared in this context or any outer context. -/
private partial def PPCtx.isShared (ctx : PPCtx) (e : Expr) : Bool :=
  ctx.sharedSet.contains e || (match ctx.outer? with | some o => o.isShared e | none => false)

/-- Get the context that owns a shared expression (innermost first). -/
private partial def PPCtx.ownerOf? (ctx : PPCtx) (e : Expr) : Option PPCtx :=
  if ctx.sharedSet.contains e then some ctx
  else match ctx.outer? with | some o => o.ownerOf? e | none => none

private def PPCtx.nameFor (ctx : PPCtx) (e : Expr) : IO Name := do
  let names ← ctx.names.get
  match names.get? e with
  | some name => return name
  | none =>
    let mut id ← ctx.nextId.get
    let mut name := Name.mkSimple ("s" ++ toString id)
    while ctx.binderNames.contains name do
      id := id + 1
      name := Name.mkSimple ("s" ++ toString id)
    ctx.nextId.set (id + 1)
    ctx.names.modify (·.insert e name)
    return name

private def PPCtx.markFirstEmit (ctx : PPCtx) (e : Expr) : IO Bool := do
  let s ← ctx.emitted.get
  if s.contains e then return false
  ctx.emitted.modify (·.insert e)
  return true

/-- Count open (has loose bvars) subexpr occurrences within a binder body. -/
private partial def countBodySubexprs (e : Expr)
    (counts : IO.Ref (Std.HashMap Expr Nat)) : IO Unit := do
  if isTrivial e then return
  if !e.hasLooseBVars then return
  let c ← counts.get
  let prev := c.getD e 0
  counts.set (c.insert e (prev + 1))
  if prev == 0 then
    match e with
    | .app f a => countBodySubexprs f counts; countBodySubexprs a counts
    | .lam _ t b _ => countBodySubexprs t counts; countBodySubexprs b counts
    | .forallE _ t b _ => countBodySubexprs t counts; countBodySubexprs b counts
    | .letE _ t v b _ =>
      countBodySubexprs t counts; countBodySubexprs v counts; countBodySubexprs b counts
    | .mdata _ e => countBodySubexprs e counts
    | .proj _ _ e => countBodySubexprs e counts
    | _ => pure ()

mutual

private partial def ppExpr (ctx : PPCtx) (e : Expr) (bvars : Array Name)
    (allowMemo : Bool := true) : IO String := do
  if isTrivial e then return ppAtom e bvars
  if allowMemo then
    if let some owner := ctx.ownerOf? e then
      let name ← owner.nameFor e
      if ← owner.markFirstEmit e then
        let val ← ppExprInner ctx e bvars
        return "(memo " ++ toString name ++ " := " ++ val ++ ")"
      else
        return toString name
  ppExprInner ctx e bvars

private partial def ppExprInner (ctx : PPCtx) (e : Expr) (bvars : Array Name) : IO String := do
  match e with
  | .app .. =>
    let fn := e.getAppFn
    let args := e.getAppArgs
    let fnStr ← ppExpr ctx fn bvars
    if args.isEmpty then return fnStr
    let fnStr := if strStartsWith fnStr "fun " || strStartsWith fnStr "∀ " || strStartsWith fnStr "let "
      then "(" ++ fnStr ++ ")" else fnStr
    let mut parts := #[fnStr]
    for arg in args do
      parts := parts.push (wrapParens (← ppExpr ctx arg bvars))
    return " ".intercalate parts.toList
  | .lam n t b bi =>
    let tStr ← ppExpr ctx t bvars (allowMemo := false)
    let name := freshBinderName n bvars
    let bStr ← ppBinderBody ctx b (bvars.push name)
    return "fun " ++ binderOpen bi ++ quoteName name ++ " : " ++ tStr
      ++ binderClose bi ++ " => " ++ bStr
  | .forallE n t b bi =>
    let tStr ← ppExpr ctx t bvars (allowMemo := false)
    if !b.hasLooseBVar 0 && bi == .default then
      let bStr ← ppExpr ctx b (bvars.push `_)
      return wrapParens tStr ++ " → " ++ bStr
    else
      let name := freshBinderName n bvars
      let bStr ← ppBinderBody ctx b (bvars.push name)
      return "∀ " ++ binderOpen bi ++ quoteName name ++ " : " ++ tStr
        ++ binderClose bi ++ ", " ++ bStr
  | .letE n t v b _ =>
    let tStr ← ppExpr ctx t bvars (allowMemo := false)
    let vStr ← ppExpr ctx v bvars
    let name := freshBinderName n bvars
    let bStr ← ppBinderBody ctx b (bvars.push name)
    return "let " ++ quoteName name ++ " : " ++ tStr ++ " := " ++ vStr ++ "; " ++ bStr
  | .mdata _ inner => ppExpr ctx inner bvars
  | .proj typeName idx struct =>
    let sStr ← ppExpr ctx struct bvars
    return "@" ++ toString typeName ++ "." ++ toString (idx + 1) ++ " " ++ wrapParens sStr
  | _ => return ppAtom e bvars

/-- Print a binder body with scope-local open sharing detection.
    If the body has repeated open subexprs, wraps output in `memoized%`. -/
private partial def ppBinderBody (ctx : PPCtx) (body : Expr) (bvars : Array Name)
    (minWeight : Nat := 3) : IO String := do
  if !body.hasLooseBVars then
    return ← ppExpr ctx body bvars
  let countsRef ← IO.mkRef (∅ : Std.HashMap Expr Nat)
  countBodySubexprs body countsRef
  let counts ← countsRef.get
  let bodyShared : Std.HashSet Expr := counts.fold (fun acc expr count =>
    if count > 1 && exprWeight expr >= minWeight
    then acc.insert expr else acc) ∅
  if bodyShared.isEmpty then
    return ← ppExpr ctx body bvars
  -- Create a child context with open sharing, linked to outer for closed sharing
  let childCtx : PPCtx := {
    sharedSet := bodyShared
    binderNames := ctx.binderNames
    names := ← IO.mkRef ∅
    emitted := ← IO.mkRef ∅
    nextId := ctx.nextId  -- share counter with outer to avoid name collisions
    outer? := some ctx
  }
  let bodyStr ← ppExpr childCtx body bvars
  let localNames ← childCtx.names.get
  if localNames.isEmpty then return bodyStr
  else return "memoized% " ++ bodyStr

end

-- ── Binder name collection ──

private partial def collectBinderNames (e : Expr) (acc : Std.HashSet Name := ∅) :
    Std.HashSet Name :=
  match e with
  | .lam n t b _ => collectBinderNames b (collectBinderNames t (acc.insert n))
  | .forallE n t b _ => collectBinderNames b (collectBinderNames t (acc.insert n))
  | .letE n t v b _ =>
    collectBinderNames b (collectBinderNames v (collectBinderNames t (acc.insert n)))
  | .app f a => collectBinderNames a (collectBinderNames f acc)
  | .mdata _ e => collectBinderNames e acc
  | .proj _ _ e => collectBinderNames e acc
  | _ => acc

-- ── Level parameter collection ──

private partial def collectLevelParams (e : Expr) (acc : Std.HashSet Name := ∅) :
    Std.HashSet Name :=
  match e with
  | .sort l => collectLevelParamsLevel l acc
  | .const _ us => us.foldl (fun acc l => collectLevelParamsLevel l acc) acc
  | .app f a => collectLevelParams a (collectLevelParams f acc)
  | .lam _ t b _ => collectLevelParams b (collectLevelParams t acc)
  | .forallE _ t b _ => collectLevelParams b (collectLevelParams t acc)
  | .letE _ t v b _ => collectLevelParams b (collectLevelParams v (collectLevelParams t acc))
  | .mdata _ e => collectLevelParams e acc
  | .proj _ _ e => collectLevelParams e acc
  | _ => acc
where
  collectLevelParamsLevel (l : Level) (acc : Std.HashSet Name) : Std.HashSet Name :=
    match l with
    | .param n => acc.insert n
    | .succ l => collectLevelParamsLevel l acc
    | .max l1 l2 => collectLevelParamsLevel l2 (collectLevelParamsLevel l1 acc)
    | .imax l1 l2 => collectLevelParamsLevel l2 (collectLevelParamsLevel l1 acc)
    | _ => acc

-- ── Public API ──

/-- Pretty-print an expression with memoized subexpression sharing.
    Zeta+beta reduces first, then identifies shared closed subexpressions and
    emits `memoized% ... (memo _s0 := ...) _s0` format. -/
def ppMemoized (e : Expr) (minWeight : Nat := 3) : IO String := do
  let e := zetaBetaReduce e
  let e := ShareCommon.shareCommon e
  let countsRef ← IO.mkRef (∅ : Std.HashMap Expr Nat)
  countSubexprs e countsRef
  let counts ← countsRef.get
  let sharedSet : Std.HashSet Expr := counts.fold (fun acc expr count =>
    if count > 1 && exprWeight expr >= minWeight && !expr.hasLooseBVars
    then acc.insert expr else acc) ∅
  let ctx : PPCtx := {
    sharedSet
    binderNames := collectBinderNames e
    names := ← IO.mkRef ∅
    emitted := ← IO.mkRef ∅
    nextId := ← IO.mkRef 0
  }
  let body ← ppExpr ctx e #[]
  let names ← ctx.names.get
  if names.isEmpty then return body
  else return "memoized% " ++ body

end Lean.PrettyPrinter
