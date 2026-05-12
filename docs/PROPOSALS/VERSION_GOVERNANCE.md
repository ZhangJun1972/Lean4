# Proposal: Four-Tier Library Architecture & Version Governance for Lean 4

## Summary

This proposal aims to solve the pervasive version fragmentation problem in the Lean 4 ecosystem by establishing a clear hierarchical system and improved version management.

## Motivation

The Lean 4 ecosystem currently faces significant challenges:

1. **Version Churn**: Lean 4 adopts a monthly minor release cadence with frequent breaking changes
2. **Compatibility Issues**: Code written for v4.20 often fails to compile on v4.21 without modification
3. **Mathlib & Toolchain Coupling**: Mathlib is tightly bound to specific Lean versions, creating cascading compatibility issues
4. **Duplicated Dependencies**: Every project downloads complete toolchains and dependencies independently
5. **Version Number Confusion**: `v4.9.0` to `v4.10.0` appears like a major version jump when it's actually just the 10th minor release

These issues create significant friction for users, library authors, and the community at large.

## Proposed Solution

### 1. Four-Tier Library Architecture

We propose establishing a hierarchical stability system:

```
Level 1: Standard Syntax (2-year cycle)
  └─ Core language syntax, inductive types, basic tactics
  └─ No breaking changes guaranteed
  └─ Example: `intro`, `exact`, `apply`, `rfl`

Level 2: Standard Library (1-year cycle)
  └─ Stable API subset of core data structures
  └─ `List`, `Array`, `Option`, standard typeclasses
  └─ `BEq`, `Ord`, `Hashable`, `Functor`, `Monad`
  └─ Core `simp` framework

Level 3: Feature Libraries (quarterly cycle)
  └─ New features, performance optimizations
  └─ `Std.Data.HashMap`, `Lean.Meta.Omega`
  └─ Can migrate to Level 2 after validation

Level 4: Incubating Libraries (no fixed cycle)
  └─ Experimental features, third-party contributions
  └─ No stability guarantees
  └─ Warnings on import
```

### 2. Improved Version Numbering

Current: `vMAJOR.MINOR.PATCH`
Proposed: `vMAJOR.XX.PATCH-LEVEL`

**Advantages**:
- Two-digit minor versions avoid confusion (`v4.09.0` → `v4.10.0` appears natural)
- `LEVEL` suffix indicates stability level:
  - `-1`: Standard Syntax level compatibility
  - `-2`: Standard Library level compatibility
  - `-3`: Feature Libraries level compatibility
  - `-4`: Incubating Libraries level compatibility

**Examples**:
- `v5.00.0-1`: Major Standard Syntax update
- `v4.30.0-2`: Standard Library annual update
- `v4.29.1-3`: Feature Libraries quarterly update

### 3. Shared Dependency Library Specification

Establish a global cache system:

```
~/.lean4/shared/
├── toolchains/
│   ├── lean4-v4.29.0/
│   └── lean4-v4.30.0/
├── stdlibs/
│   ├── level1/v4.x/
│   ├── level2/v4.29/
│   └── level3/v4.29/
└── community/
    ├── mathlib/stable-v4.29/
    └── other_libs/
```

**New Lake Configuration**:
```toml
[shared_dependencies]
enabled = true
cache_dir = "~/.lean4/shared"
```

**New Lake Commands**:
```bash
lake shared list                # List all shared libraries
lake shared update mathlib      # Update shared library
lake shared clean               # Clean up expired shared libraries
lake shared install lean4-v4.30 # Install new toolchain to shared directory
```

### 4. Stability Annotation System

Add standardized attributes:

```lean
-- Core attributes
@[stable_since "v4.0"]
def List.map (f : α → β) (l : List α) : List β := ...

@[deprecated_since "v4.25" "use List.Stable.find instead"]
def List.find (p : α → Bool) (l : List α) : Option α := ...

@[experimental_since "v4.30"]
def List.newFeature : ... := ...

@[moved_to "Lean.Stable.Data.List.find"]
def List.oldFind : ... := ...

@[incubating_warning "This API may change without notice"]
def Lean.Incubating.experimental : ... := ...
```

## Compatibility Matrix

| Your Code Uses | Compatible Lean Versions |
|--------------|-----------------------|
| Standard Syntax only (Level 1) | v4.x, v5.x (2 years) |
| Standard Library (Level 2) | v4.20-v4.30 (1 year) |
| Feature Libraries (Level 3) | v4.28-v4.30 (1 quarter) |
| Incubating Libraries (Level 4) | Current version only |

## Migration Path

### Short-Term (3 months)
1. Establish stability annotation system
2. Create `Lean.Stable` namespace with curated stable APIs
3. Document stability levels of existing APIs

### Medium-Term (6-12 months)
1. Officially launch four-tier architecture
2. Align mathlib with similar structure (`Mathlib.Stable.*`, `Mathlib.Feature.*`)
3. Implement version management tools:
   - `lake check-compat`: Check compatibility
   - `lake migrate`: Auto-migrate to new APIs

### Long-Term (2 years)
1. First LTS version (v5.0.0) with 5-year support
2. Complete ecosystem adoption of four-tier architecture

## Impact

This proposal would:
- ✅ Reduce maintenance burden for library authors
- ✅ Make user code more portable across versions
- ✅ Save disk space with shared dependencies
- ✅ Provide clear stability expectations
- ✅ Still allow rapid iteration in feature/incubating tiers

## References

- Based on analysis of Lean 4 version history (v4.0.0 through v4.29.1)
- Inspired by other languages with strong stability guarantees (Rust editions, Python stdlib)

---

[Comment]: # (This is a community proposal - feel free to discuss and contribute!)
