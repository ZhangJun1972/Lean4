#!/usr/bin/env python3
"""Check that each declaration in `Std.Do.SPred.DerivedLaws` has a counterpart
in `Std.Internal.Do.Assertion.DerivedLaws`.

Compares names of `theorem`, `def`, `abbrev`, and `class` declarations.
`instance` declarations (anonymous) are listed separately by count only.

Exit code is the number of missing declarations.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
SPRED = REPO_ROOT / "src/Std/Do/SPred/DerivedLaws.lean"
ASSERT = REPO_ROOT / "src/Std/Internal/Do/Assertion/DerivedLaws.lean"

# Known renames: SPred name → Assertion name.
RENAMES: dict[str, str] = {
    "PropAsSPredTautology": "PropAsAssertionTautology",
    "entails.trans'": "rel_trans'",
    "entails_true_intro": "top_le_himp_iff",
}

# SPred-specific declarations with no Assertion analog (won't translate via the
# function-space `CompleteLattice` either).
INTENTIONALLY_OMITTED = {
    # `bientails` is replaced by `=`; these wrappers become `Eq.*` / `rel_of_eq`.
    "bientails.rfl",
    "bientails.mp",
    "bientails.mpr",
    "bientails.of_eq",
    "entails.rfl",  # replaced by `rel_refl`
    # SPred-specific cons workarounds (function-space lattice covers `entails_N`):
    "entails_pure_elim_cons",
    "apply_pure_cons_entails_l",
    "apply_pure_cons_entails_r",
    # `SPred [] = ULift Prop` machinery:
    "down_pure_intro",
    "ULift.down_dite",
    "ULift.down_ite",
}

# Match `theorem|def|abbrev|class <name>` possibly preceded by attributes.
DECL_RE = re.compile(
    r"^\s*(?:@\[[^\]]*\]\s*)*"           # optional attributes
    r"(?:protected\s+|private\s+|noncomputable\s+|unsafe\s+)*"
    r"(theorem|def|abbrev|class)\s+"
    r"(?:_root_\.)?"
    r"([A-Za-z_][A-Za-z0-9_'.]*)"
)
INSTANCE_RE = re.compile(r"^\s*(?:@\[[^\]]*\]\s*)*instance\b")


def extract(file: Path) -> tuple[set[str], int]:
    """Return (declaration names, instance count) for `file`."""
    names: set[str] = set()
    instances = 0
    for line in file.read_text().splitlines():
        m = DECL_RE.match(line)
        if m:
            names.add(m.group(2))
            continue
        if INSTANCE_RE.match(line):
            instances += 1
    return names, instances


def main() -> int:
    spred_names, spred_inst = extract(SPRED)
    assert_names, assert_inst = extract(ASSERT)

    # Treat each SPred name as ported if it (a) appears verbatim in Assertion,
    # (b) has a known rename target that appears in Assertion, or (c) is
    # explicitly marked intentionally omitted.
    ported: list[str] = []
    renamed: list[tuple[str, str]] = []
    omitted: list[str] = []
    missing: list[str] = []
    for n in sorted(spred_names):
        if n in assert_names:
            ported.append(n)
        elif n in RENAMES and RENAMES[n] in assert_names:
            renamed.append((n, RENAMES[n]))
        elif n in INTENTIONALLY_OMITTED:
            omitted.append(n)
        else:
            missing.append(n)

    accounted = set(ported) | {n for n, _ in renamed} | set(omitted)
    accounted |= set(RENAMES.values())  # don't list rename targets as extras
    extra = sorted(assert_names - spred_names - set(RENAMES.values()))

    rel_spred = SPRED.relative_to(REPO_ROOT)
    rel_assert = ASSERT.relative_to(REPO_ROOT)
    print(f"=== Comparing {rel_spred} → {rel_assert} ===")
    print(f"SPred named decls:     {len(spred_names)}  (instances: {spred_inst})")
    print(f"Assertion named decls: {len(assert_names)}  (instances: {assert_inst})")
    print(f"Ported (same name):    {len(ported)}")
    print(f"Ported (renamed):      {len(renamed)}")
    print(f"Intentionally omitted: {len(omitted)}")
    print(f"Missing:               {len(missing)}")
    print(f"Extra (Assertion):     {len(extra)}")
    print()

    if renamed:
        print("=== Renamed ===")
        for src, dst in renamed:
            print(f"  {src} → {dst}")
        print()
    if omitted:
        print("=== Intentionally omitted (SPred-specific) ===")
        for n in omitted:
            print(f"  {n}")
        print()
    if missing:
        print("=== MISSING in Assertion port ===")
        for n in missing:
            print(f"  {n}")
        print()
    if extra:
        print("=== EXTRA in Assertion port (not in SPred) ===")
        for n in extra:
            print(f"  {n}")
        print()

    return len(missing)


if __name__ == "__main__":
    sys.exit(main())
