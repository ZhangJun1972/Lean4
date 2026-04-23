import Lean

-- ═══════════════════════════════════════════════════════════════
-- Manual round-trip: memoized%/memo syntax elaborates correctly
-- ═══════════════════════════════════════════════════════════════

example : memoized% @Nat.add
    (memo s0 := @Nat.mul (memo s1 := @Nat.succ @Nat.zero) s1)
    s0 = 2 := rfl

example : memoized% @Nat.add
    (memo s0 := @Nat.mul
      (memo s1 := @Nat.add (memo s2 := @Nat.succ @Nat.zero) (@Nat.succ s2))
      s1)
    s0 = 18 := rfl

-- ═══════════════════════════════════════════════════════════════
-- pp.memoize output via #print
-- ═══════════════════════════════════════════════════════════════

noncomputable def test_shared :=
  @Nat.add (@Nat.mul (@Nat.succ @Nat.zero) (@Nat.succ @Nat.zero))
           (@Nat.mul (@Nat.succ @Nat.zero) (@Nat.succ @Nat.zero))

set_option pp.memoize true in
/--
info: def test_shared : @Nat :=
memoized% @Nat.add (memo s0 := @Nat.mul (memo s1 := @Nat.succ @Nat.zero) s1) s0
-/
#guard_msgs in
#print test_shared

-- ═══════════════════════════════════════════════════════════════
-- Automated round-trip: ppMemoized → parse → re-elaborate → isDefEq
-- ═══════════════════════════════════════════════════════════════

open Lean Meta Elab Term in
elab "#roundtrip " id:ident : command => do
  Command.liftTermElabM do
    let name ← resolveGlobalConstNoOverload id
    let info ← getConstInfo name
    let origVal ← match info with
      | .defnInfo v => pure v.value
      | .thmInfo v => pure v.value
      | _ => throwError s!"{name}: not a def/theorem"
    let origType ← inferType origVal
    let s ← Lean.PrettyPrinter.ppMemoized origVal
    let env ← getEnv
    let stx ← match Parser.runParserCategory env `term s with
      | .ok stx => pure stx
      | .error err => throwError "parse failed for {name}: {err}\nOutput was:\n{s}"
    let newVal ← elabTermEnsuringType stx origType
    unless ← isDefEq origVal newVal do
      throwError "round-trip FAILED for {name}\nPP output: {s}"
    logInfo m!"{s}"

open Lean Meta Elab Term in
elab "#roundtrip_type " id:ident : command => do
  Command.liftTermElabM do
    let name ← resolveGlobalConstNoOverload id
    let info ← getConstInfo name
    let origType := info.type
    let s ← Lean.PrettyPrinter.ppMemoized origType
    let env ← getEnv
    let stx ← match Parser.runParserCategory env `term s with
      | .ok stx => pure stx
      | .error err => throwError "parse failed for type of {name}: {err}\nOutput was:\n{s}"
    let newType ← elabTerm stx none
    unless ← isDefEq origType newType do
      throwError "round-trip FAILED for type of {name}\nPP output: {s}"
    logInfo m!"{s}"

-- Stdlib definitions

/-- info: fun (x : @Nat) => fun (x_1 : @Nat) => @Nat.brecOn.{1} (fun (x_2 : @Nat) => @Nat → @Nat) x_1 @Nat.add._f x -/
#guard_msgs in #roundtrip Nat.add
/-- info: fun {α : Sort (_ + 1)} => fun {β : Sort (_ + 1)} => fun (f : α → β) => fun (x : @List.{_} α) => @List.brecOn.{(_ + 1), _} α (fun (x_1 : @List.{_} α) => @List.{_} β) x (@List.map._f.{_, _} α β f) -/
#guard_msgs in #roundtrip List.map
/-- info: fun (x : @Bool) => fun (y : @Bool) => @Bool.and.match_1.{1} (fun (x_1 : @Bool) => @Bool) x (fun (_ : @Unit) => @Bool.false) (fun (_ : @Unit) => y) -/
#guard_msgs in #roundtrip Bool.and
/-- info: fun {α : Sort _} => fun {β : Sort _} => fun {δ : Sort _} => fun (f : β → δ) => fun (g : α → β) => fun (x : α) => f (g x) -/
#guard_msgs in #roundtrip Function.comp
/-- info: fun {α : Sort (_ + 1)} => fun {β : Sort (_ + 1)} => fun (f : α → β) => fun (x : @Option.{_} α) => @Option.getD.match_1.{_, (_ + 1)} α (fun (x_1 : @Option.{_} α) => @Option.{_} β) x (fun (x_1 : α) => @Option.some.{_} β (f x_1)) (fun (_ : @Unit) => @Option.none.{_} β) -/
#guard_msgs in #roundtrip Option.map

-- Theorems

/-- info: fun (x : @Nat) => fun (x_1 : @Nat) => @Nat.brecOn.{0} (fun (x_2 : @Nat) => ∀ (x_3 : @Nat), @Eq.{1} @Nat (@HAdd.hAdd.{0, 0, 0} @Nat @Nat @Nat (@instHAdd.{0} @Nat @instAddNat) x_3 x_2) (@HAdd.hAdd.{0, 0, 0} @Nat @Nat @Nat (@instHAdd.{0} @Nat @instAddNat) x_2 x_3)) x_1 @Nat.add_comm._f x -/
#guard_msgs in #roundtrip Nat.add_comm
/-- info: fun (n : @Nat) => @rfl.{1} @Nat (@HAdd.hAdd.{0, 0, 0} @Nat @Nat @Nat (@instHAdd.{0} @Nat @instAddNat) n (@OfNat.ofNat.{0} @Nat 0 (@instOfNatNat 0))) -/
#guard_msgs in #roundtrip Nat.add_zero
/-- info: fun (x : @Nat) => @Nat.brecOn.{0} (fun (x_1 : @Nat) => @Eq.{1} @Nat (@HAdd.hAdd.{0, 0, 0} @Nat @Nat @Nat (@instHAdd.{0} @Nat @instAddNat) (@OfNat.ofNat.{0} @Nat 0 (@instOfNatNat 0)) x_1) x_1) x @Nat.zero_add._f -/
#guard_msgs in #roundtrip Nat.zero_add

-- Types of stdlib functions

/-- info: @Nat → @Nat → @Nat -/
#guard_msgs in #roundtrip_type Nat.add
/-- info: ∀ {α : Sort (_ + 1)}, ∀ {β : Sort (_ + 1)}, (α → β) → (@List.{_} α) → @List.{_} β -/
#guard_msgs in #roundtrip_type List.map
/-- info: ∀ {α : Sort (_ + 1)}, (@List.{_} α) → (@List.{_} α) → @List.{_} α -/
#guard_msgs in #roundtrip_type List.append
/-- info: ∀ {α : Sort _}, ∀ {β : Sort _}, ∀ {δ : Sort _}, (β → δ) → (α → β) → α → δ -/
#guard_msgs in #roundtrip_type Function.comp
/-- info: ∀ {α : Sort (_ + 1)}, ∀ {β : Sort (_ + 1)}, (α → β) → (@Option.{_} α) → @Option.{_} β -/
#guard_msgs in #roundtrip_type Option.map
/-- info: ∀ {a : Prop}, ∀ {b : Prop}, a → b → @And a b -/
#guard_msgs in #roundtrip_type And.intro
/-- info: ∀ {a : Prop}, ∀ {b : Prop}, a → @Or a b -/
#guard_msgs in #roundtrip_type Or.inl
/-- info: ∀ {α : Sort _}, ∀ {motive : α → Prop}, ∀ {a : α}, ∀ {b : α}, (@Eq.{_} α a b) → (motive a) → motive b -/
#guard_msgs in #roundtrip_type Eq.subst
/-- info: ∀ {α : Sort (_ + 1)}, (@List.{_} α) → (@List.{_} α) → @List.{_} α -/
#guard_msgs in #roundtrip_type List.reverseAux

-- Instances

/-- info: @Inhabited.mk.{1} @Nat @Nat.zero -/
#guard_msgs in #roundtrip instInhabitedNat

-- User definitions with sharing

noncomputable def rt_shared :=
  @Nat.add (@Nat.mul (@Nat.succ @Nat.zero) (@Nat.succ @Nat.zero))
           (@Nat.mul (@Nat.succ @Nat.zero) (@Nat.succ @Nat.zero))
noncomputable def rt_deep :=
  let a := @Nat.succ @Nat.zero
  let b := @Nat.succ (@Nat.succ @Nat.zero)
  let ab := @Nat.add a b
  let sq := @Nat.mul ab ab
  @Nat.add sq sq
noncomputable def rt_lam2 := fun (x y : Nat) => Nat.add (Nat.mul x y) (Nat.mul x y)
noncomputable def rt_ho := @Function.comp Nat Nat Nat (· + 1) (· * 2)
noncomputable def rt_str := @List.cons String "hello" (@List.cons String "hello" (@List.nil String))
noncomputable def rt_pair := @Prod.mk Nat Nat (@Nat.succ @Nat.zero) (@Nat.succ @Nat.zero)
noncomputable def rt_nested :=
  @Nat.add (@Nat.add (@Nat.succ @Nat.zero) (@Nat.succ @Nat.zero))
           (@Nat.add (@Nat.succ @Nat.zero) (@Nat.succ @Nat.zero))
theorem rt_proof : 1 + 1 = 2 ∧ 1 + 1 = 2 := ⟨rfl, rfl⟩

/-- info: memoized% @Nat.add (memo s0 := @Nat.mul (memo s1 := @Nat.succ @Nat.zero) s1) s0 -/
#guard_msgs in #roundtrip rt_shared
/-- info: memoized% @Nat.add (memo s0 := @Nat.mul (memo s1 := @Nat.add (memo s2 := @Nat.succ @Nat.zero) (@Nat.succ s2)) s1) s0 -/
#guard_msgs in #roundtrip rt_deep
/-- info: fun (x : @Nat) => fun (y : @Nat) => memoized% @Nat.add (memo s0 := @Nat.mul x y) s0 -/
#guard_msgs in #roundtrip rt_lam2
/-- info: @Function.comp.{1, 1, 1} @Nat @Nat @Nat (fun (x : @Nat) => @HAdd.hAdd.{0, 0, 0} @Nat @Nat @Nat (@instHAdd.{0} @Nat @instAddNat) x (@OfNat.ofNat.{0} @Nat 1 (@instOfNatNat 1))) (fun (x : @Nat) => @HMul.hMul.{0, 0, 0} @Nat @Nat @Nat (@instHMul.{0} @Nat @instMulNat) x (@OfNat.ofNat.{0} @Nat 2 (@instOfNatNat 2))) -/
#guard_msgs in #roundtrip rt_ho
/-- info: @List.cons.{0} @String "hello" (@List.cons.{0} @String "hello" (@List.nil.{0} @String)) -/
#guard_msgs in #roundtrip rt_str
/-- info: memoized% @Prod.mk.{0, 0} @Nat @Nat (memo s0 := @Nat.succ @Nat.zero) s0 -/
#guard_msgs in #roundtrip rt_pair
/-- info: memoized% @Nat.add (memo s0 := @Nat.add (memo s1 := @Nat.succ @Nat.zero) s1) s0 -/
#guard_msgs in #roundtrip rt_nested
/-- info: memoized% @And.intro (memo s0 := @Eq.{1} @Nat (memo s1 := @HAdd.hAdd.{0, 0, 0} @Nat @Nat @Nat (@instHAdd.{0} @Nat @instAddNat) (memo s2 := @OfNat.ofNat.{0} @Nat 1 (@instOfNatNat 1)) s2) (@OfNat.ofNat.{0} @Nat 2 (@instOfNatNat 2))) s0 (memo s3 := @rfl.{1} @Nat s1) s3 -/
#guard_msgs in #roundtrip rt_proof

-- String escaping

def rt_str_quote := "\""
def rt_str_backslash := "\\"
def rt_str_newline := "\n"
def rt_str_mix := "a\"b\\c\nd"

/-- info: "\"" -/
#guard_msgs in #roundtrip rt_str_quote
/-- info: "\\" -/
#guard_msgs in #roundtrip rt_str_backslash
/-- info: "\n" -/
#guard_msgs in #roundtrip rt_str_newline
/-- info: "a\"b\\c\nd" -/
#guard_msgs in #roundtrip rt_str_mix

-- Keyword binder names

def rt_kw_let := fun («let» : Nat) => «let»
def rt_kw_match := fun («match» : Nat) => «match»

/-- info: fun («let» : @Nat) => «let» -/
#guard_msgs in #roundtrip rt_kw_let
/-- info: fun («match» : @Nat) => «match» -/
#guard_msgs in #roundtrip rt_kw_match

-- Scoped sharing under binders (nested memoized%)

noncomputable def rt_open_sharing := fun (x : Nat) => Nat.add (Nat.mul x x) (Nat.mul x x)
noncomputable def rt_nested_open := fun (x : Nat) => fun (y : Nat) =>
  Nat.add (Nat.mul x y) (Nat.mul x y)

/-- info: fun (x : @Nat) => memoized% @Nat.add (memo s0 := @Nat.mul x x) s0 -/
#guard_msgs in #roundtrip rt_open_sharing
/-- info: fun (x : @Nat) => fun (y : @Nat) => memoized% @Nat.add (memo s0 := @Nat.mul x y) s0 -/
#guard_msgs in #roundtrip rt_nested_open

-- Sibling lambdas: same raw Expr `g #0` under different binders gets independent sharing
noncomputable def rt_sibling_lam :=
  @Prod.mk (Nat → Nat) (Nat → Nat)
    (fun x => Nat.add (Nat.mul x x) (Nat.mul x x))
    (fun y => Nat.add (Nat.mul y y) (Nat.mul y y))

/-- info: memoized% @Prod.mk.{0, 0} (memo s0 := @Nat → @Nat) s0 (memo s1 := fun (x : @Nat) => memoized% @Nat.add (memo s2 := @Nat.mul x x) s2) s1 -/
#guard_msgs in #roundtrip rt_sibling_lam

-- Sharing at nested depth with closed+open mix
noncomputable def rt_depth2 := fun (x : Nat) => fun (y : Nat) =>
  Nat.add (Nat.add (Nat.mul x y) (Nat.mul x y))
          (Nat.add (Nat.mul x y) (Nat.mul x y))

/-- info: fun (x : @Nat) => fun (y : @Nat) => memoized% @Nat.add (memo s0 := @Nat.add (memo s1 := @Nat.mul x y) s1) s0 -/
#guard_msgs in #roundtrip rt_depth2

-- Name collision avoidance: outer and inner scopes use distinct names
noncomputable def rt_outer_sharing := fun (x : Nat) =>
  @Prod.mk (Nat → Nat) (Nat → Nat)
    (fun y => Nat.add x y)
    (fun z => Nat.add x z)

/-- info: memoized% fun (x : @Nat) => memoized% @Prod.mk.{0, 0} (memo s0 := @Nat → @Nat) s0 (memo s1 := fun (y : @Nat) => @Nat.add x y) s1 -/
#guard_msgs in #roundtrip rt_outer_sharing

-- Sharing across let value and body under binder (zeta-reduced)
noncomputable def rt_let_cross := fun (x : Nat) =>
  let a := Nat.mul x x
  let b := Nat.mul x x
  Nat.add a b

/-- info: fun (x : @Nat) => memoized% @Nat.add (memo s0 := @Nat.mul x x) s0 -/
#guard_msgs in #roundtrip rt_let_cross
