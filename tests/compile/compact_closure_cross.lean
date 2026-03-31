import Lean.Environment

open Lean

unsafe def main (args : List String) : IO UInt32 := do
  let tmpFile : System.FilePath := "./_compact_closure_cross_test.olean"

  match args with
  | ["save"] =>
    let captured := "cross"
    let f : Nat → String := fun n => s!"{captured} {n}"
    saveModuleData tmpFile `test (unsafeCast f)
    return 0
  | ["load"] =>
    let (data, _region) ← readModuleData tmpFile
    let g : Nat → String := unsafeCast data
    IO.println (g 7)
    IO.println (g 99)
    IO.FS.removeFile tmpFile
    return 0
  | _ =>
    -- Default: run save in one process, load in another
    let self ← IO.appPath
    let _ ← IO.Process.run { cmd := self.toString, args := #["save"] }
    let loadResult ← IO.Process.run { cmd := self.toString, args := #["load"] }
    IO.print loadResult
    return 0
