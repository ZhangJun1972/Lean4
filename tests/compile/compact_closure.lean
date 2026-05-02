import Lean.Environment

open Lean

unsafe def main : IO Unit := do
  let tmpFile : System.FilePath := "./_compact_closure_test.olean"

  -- Simple closure with captured string
  let captured := "hello"
  let f : Nat → String := fun n => s!"{captured} {n}"
  saveModuleData tmpFile `test (unsafeCast f)
  let (data, _region) ← readModuleData tmpFile
  let g : Nat → String := unsafeCast data
  IO.println (g 42)
  IO.println (g 0)

  -- Closure capturing an array
  let xs := #[10, 20, 30]
  let h : Nat → Nat := fun i => xs.foldl (· + ·) i
  saveModuleData tmpFile `test2 (unsafeCast h)
  let (data2, _region2) ← readModuleData tmpFile
  let h' : Nat → Nat := unsafeCast data2
  IO.println (toString (h' 1))
  IO.println (toString (h' 100))

  IO.FS.removeFile tmpFile
