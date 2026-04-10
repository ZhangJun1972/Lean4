/-
Copyright (c) 2022 Mac Malone. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Mac Malone, Gabriel Ebner
-/
module

prelude
public import Lake.Config.Workspace
public import Lake.Load.Manifest
import Lake.Util.IO
import Lake.Util.StoreInsts
import Lake.Config.Monad
import Lake.Build.Topological
import Lake.Load.Materialize
import Lake.Load.Lean.Eval
import Lake.Load.Package
import Init.Data.Range.Polymorphic.Iterators
import Init.TacticsExtra

open System Lean

/-! # Dependency Resolution

This module contains definitions for resolving the dependencies of a package.
-/

namespace Lake

/-- Returns the load configuration of a materialized dependency. -/
@[inline] def mkDepLoadConfig
  (ws : Workspace) (dep : MaterializedDep)
  (lakeOpts : NameMap String) (leanOpts : Options) (reconfigure : Bool)
: LoadConfig where
  lakeEnv := ws.lakeEnv
  wsDir := ws.dir
  pkgIdx := ws.packages.size
  pkgName := dep.name
  pkgDir := dep.pkgDir
  relPkgDir := dep.relPkgDir
  relConfigFile := dep.relConfigFile
  relManifestFile := dep.relManifestFile
  lakeOpts; leanOpts; reconfigure
  scope := dep.scope
  remoteUrl := dep.remoteUrl

def Workspace.addFacetDecls (decls : Array FacetDecl) (self : Workspace) : Workspace :=
  decls.foldl (·.addFacetConfig ·.config) self

theorem Workspace.packages_addFacetDecls :
  (addFacetDecls decls ws).packages = ws.packages
:= by
  simp only [addFacetDecls]
  apply Array.foldl_induction (fun _ (s : Workspace) => s.packages = ws.packages) rfl
  intro i s h
  simp only [packages_addFacetConfig, h]

/--
Loads the package configuration of a materialized dependency.
Adds the package and the facets defined within it to the `Workspace`.
-/
def Workspace.addDepPackage'
  (ws : Workspace) (dep : MaterializedDep)
  (lakeOpts : NameMap String) (leanOpts : Options) (reconfigure : Bool)
: LogIO {ws' : Workspace // ws'.packages.size = ws.packages.size + 1} := do
  let wsIdx := ws.packages.size
  let loadCfg := mkDepLoadConfig ws dep lakeOpts leanOpts reconfigure
  let ⟨loadCfg, h⟩ ← resolveConfigFile dep.prettyName loadCfg
  let fileCfg ← loadConfigFile loadCfg h
  let pkg := mkPackage loadCfg fileCfg wsIdx
  let ws := ws.addPackage' pkg wsIdx_mkPackage |>.addFacetDecls fileCfg.facetDecls
  return ⟨ws, by simp [ws, packages_addFacetDecls, packages_addPackage']⟩

/--
The resolver's call stack of dependencies.
That is, the dependency currently being resolved plus its parents.
-/
abbrev DepStack := CallStack Name

/--
A monad transformer for recursive dependency resolution.
It equips the monad with the stack of dependencies currently being resolved.
-/
abbrev DepStackT m := CallStackT Name m

@[inline] nonrec def DepStackT.run
  (x : DepStackT m α) (stack : DepStack := {})
: m α := x.run stack

/-- Log dependency cycle and error. -/
@[specialize] def depCycleError [MonadError m] (cycle : Cycle Name) : m α :=
  error s!"dependency cycle detected:\n{formatCycle cycle}"

instance [Monad m] [MonadError m] : MonadCycleOf Name (DepStackT m) where
  throwCycle := depCycleError

/-- The monad of the dependency resolver. -/
abbrev ResolveT m := DepStackT <| StateT Workspace m

@[inline] nonrec def ResolveT.run
  (ws : Workspace) (x : ResolveT m α) (stack : DepStack := {})
: m (α × Workspace) := x.run stack |>.run ws

/-- Recursively run a `ResolveT` monad starting from the workspace's root. -/
@[specialize] def Workspace.runResolveT
  [Monad m] [MonadError m] (ws : Workspace)
  (go : RecFetchFn Package PUnit (ResolveT m))
  (root := ws.root) (stack : DepStack  := {})
: m Workspace := do
  let (_, ws) ← ResolveT.run ws (stack := stack) do
    recFetchAcyclic (·.baseName) go root
  return ws

def Workspace.setDepPkgs
  (self : Workspace) (wsIdx : Nat) (depPkgs : Array Package)
: Workspace := {self with
  packages := self.packages.modify wsIdx ({· with depPkgs})
  size_packages_pos := by simp [self.size_packages_pos]
  packages_wsIdx {i} := by
    if h : wsIdx = i then
      simp [h, Array.getElem_modify_self, self.packages_wsIdx]
    else
      simp [Array.getElem_modify_of_ne h, self.packages_wsIdx]
}

structure ResolveState where
  ws : Workspace
  depIdxs : Array Nat
  lt_of_mem : ∀ i ∈ depIdxs, i < ws.packages.size

namespace ResolveState

@[inline] def init (ws : Workspace) (size : Nat) : ResolveState :=
  {ws, depIdxs := Array.mkEmpty size, lt_of_mem := by simp}

@[inline] def reuseDep (s : ResolveState) (wsIdx : Fin s.ws.packages.size) : ResolveState :=
  have lt_of_mem := by
    intro i i_mem
    cases Array.mem_push.mp i_mem with
    | inl i_mem => exact s.lt_of_mem i i_mem
    | inr i_eq => simp only [i_eq, wsIdx.isLt]
  {s with depIdxs := s.depIdxs.push wsIdx, lt_of_mem}

@[inline] def newDep
  (s : ResolveState) (dep : MaterializedDep)
  (lakeOpts : NameMap String) (leanOpts : Options) (reconfigure : Bool)
: LogIO ResolveState := do
  let ⟨ws, depIdxs, lt_of_mem⟩ := s
  let wsIdx := ws.packages.size
  let ⟨ws', h⟩ ← ws.addDepPackage' dep lakeOpts leanOpts reconfigure
  have lt_of_mem := by
    intro i i_mem
    cases Array.mem_push.mp i_mem with
    | inl i_mem => exact h ▸ Nat.lt_add_one_of_lt (lt_of_mem i i_mem)
    | inr i_eq => simp only [wsIdx, i_eq, h, Nat.lt_add_one]
  return ⟨ws', depIdxs.push wsIdx, lt_of_mem⟩

end ResolveState

/-
Recursively visits each node in a package's dependency graph, starting from
the workspace package `root`. Each dependency missing from the workspace is
added to the workspace using the `resolve` function.

Recursion occurs breadth-first. Each direct dependency of a package is
resolved in reverse order before recursing to the dependencies' dependencies.

See `Workspace.updateAndMaterializeCore` for more details.
-/
@[inline] def Workspace.resolveDepsCore
  [Monad m] [MonadError m] [MonadLiftT LogIO m] (ws : Workspace)
  (resolve : Package → Dependency → Workspace → m MaterializedDep)
  (root : Package := ws.root) (stack : DepStack := {})
  (leanOpts : Options := {}) (reconfigure := true)
: m Workspace := do
  ws.runResolveT go root stack
where
  @[specialize] go pkg recurse : ResolveT m Unit := fun depStack ws => do
    let start := ws.packages.size
    -- Materialize and load the missing direct dependencies of `pkg`
    let s := ResolveState.init ws pkg.depConfigs.size
    let ⟨ws, depIdxs, lt_of_mem⟩ ← pkg.depConfigs.foldrM (m := m) (init := s) fun dep s => do
      let isMultiVersion := s.ws.isMultiVersion
      unless isMultiVersion do
        if let some wsIdx := s.ws.packages.findFinIdx? (·.baseName == dep.name) then
          return s.reuseDep wsIdx -- already handled in another branch
      if pkg.baseName = dep.name then
        error s!"{pkg.prettyName}: package requires itself (or a package with the same name)"
      let matDep ← resolve pkg dep s.ws
      if isMultiVersion then
        if let some wsIdx := s.ws.packages.findFinIdx? (·.dir == matDep.pkgDir) then
          return s.reuseDep wsIdx
      s.newDep matDep dep.opts leanOpts reconfigure
    let depsEnd := ws.packages.size
    -- Recursively load the dependencies' dependencies
    let ws ← ws.packages.foldlM (start := start) (init := ws) fun ws pkg =>
      (·.2) <$> recurse pkg depStack ws
    -- Add the package's dependencies to the package
    let ws :=
      if h_le : depsEnd ≤ ws.packages.size then
        ws.setDepPkgs pkg.wsIdx <| depIdxs.attach.map fun ⟨wsIdx, h_mem⟩ =>
          ws.packages[wsIdx]'(Nat.lt_of_lt_of_le (lt_of_mem wsIdx h_mem) h_le)
      else
        have : Inhabited Workspace := ⟨ws⟩
        panic! "workspace shrunk" -- should be unreachable
    return ((), ws)

/-- A map of locked dependencies. -/
abbrev EntryMap := NameMap (Array PackageEntry)

/--
Monad transformer used to update the manifest.
It equips the monad with a map of locked dependencies.
-/
abbrev UpdateT := StateT EntryMap

@[inline] nonrec def UpdateT.run (x : UpdateT m α) (init : EntryMap := {}) : m (α × EntryMap) :=
  x.run init

/-- Monad used to update the manifest. -/
abbrev UpdateM := UpdateT LoggerIO

def EntryMap.resolve?
  (dep : Dependency) (multiVersion inherit : Bool) (self : EntryMap)
: Option PackageEntry :=
  if let some entries := self.get? dep.name then
    if multiVersion then
      match dep.version with
      | .none => entries[0]?
      | .git rev => entries.find? (·.inputRev?.any (· == rev))
      | .ver ver => entries.find? (ver.test ·.version)
    else if inherit then
      entries[0]?
    else
      entries[0]?.filter (!·.inherited)
  else
    none

@[inline] def getEntry?
  (ws : Workspace) (dep : Dependency) (inherit : Bool)
: UpdateM (Option PackageEntry) :=
  return (← getThe EntryMap).resolve? dep ws.isMultiVersion inherit

def EntryMap.add (entry : PackageEntry) (multiVersion : Bool) (self : EntryMap) : EntryMap :=
  self.alter entry.name fun es? =>
    if let some es := es? then
      if multiVersion then
        some <| es.push entry
      else if entry.inherited then -- inherited do not take precedence
        some es
      else
        some #[entry]
    else
      some #[entry]

@[inline] def addEntry (ws : Workspace) (entry : PackageEntry) : UpdateM Unit := do
  modifyThe EntryMap (·.add entry ws.isMultiVersion)

/--
Reuse manifest versions of root packages that should not be updated.
Also, move the packages directory if its location has changed.
-/
def reuseManifest (ws : Workspace) (toUpdate : NameSet) : UpdateM PUnit := do
  let rootName := ws.root.prettyName
  match (← Manifest.load ws.manifestFile |>.toBaseIO) with
  | .ok manifest =>
    -- Reuse manifest versions
    unless toUpdate.isEmpty do
      manifest.packages.forM fun entry => do
        unless entry.inherited || toUpdate.contains entry.name do
          addEntry ws entry
    -- Reuse or delete packages directory
    if let some oldRelPkgsDir := manifest.packagesDir? then
      let oldPkgsDir := ws.dir / oldRelPkgsDir
      if (← oldPkgsDir.pathExists) then
        if manifest.multiVersion != ws.isMultiVersion then
          tryDeletePackagesDir oldPkgsDir
        -- Rename it
        else if oldRelPkgsDir.normalize != ws.relPkgsDir.normalize then
          logInfo s!"workspace packages directory changed, \
            renaming\n  {oldPkgsDir}\nto\n  {ws.pkgsDir}"
          let doRename : IO Unit := do
            createParentDirs ws.pkgsDir
            IO.FS.rename oldPkgsDir ws.pkgsDir
          if let .error e ← doRename.toBaseIO then
            error s!"could not rename workspace packages directory: {e}"
      else if manifest.multiVersion != ws.isMultiVersion then
        tryDeletePackagesDir ws.pkgsDir
  | .error (.noFileOrDirectory ..) =>
    logInfo s!"{rootName}: no previous manifest, creating one from scratch"
  | .error e =>
    unless toUpdate.isEmpty do
      liftM (m := IO) <| throw e -- only ignore manifest on a bare `lake update`
    logWarning s!"{rootName}: ignoring previous manifest because it failed to load: {e}"
where
  tryDeletePackagesDir pkgsDir : LoggerIO PUnit := do
    if System.Platform.isWindows then
      -- Deleting git repositories via IO.FS.removeDirAll does not work reliably on windows
      logInfo s!"mutli-version workspace setting changed; \
        you may need to delete the packages directory manually:\n  {pkgsDir}"
    else
      logInfo s!"mutli-version workspace setting changed, \
        deleting packages directory:\n  {pkgsDir}"
      IO.FS.removeDirAll pkgsDir

/-- Add a package dependency's manifest entries to the update state. -/
def addDependencyEntries (ws : Workspace) (dep : MaterializedDep) : UpdateM PUnit := do
  match (← Manifest.load dep.manifestFile |>.toBaseIO) with
  | .ok manifest =>
    manifest.packages.forM fun entry => do
      addEntry ws <| entry.setInherited.inDirectory dep.relPkgDir
  | .error (.noFileOrDirectory ..) =>
    logWarning s!"{dep.prettyName}: ignoring missing manifest:\n  {dep.manifestFile}"
  | .error e =>
    logWarning s!"{dep.prettyName}: ignoring manifest because it failed to load: {e}"

/-- Materialize a single dependency, updating it if desired. -/
def updateAndMaterializeDep
  (ws : Workspace) (pkg : Package) (dep : Dependency)
: UpdateM MaterializedDep := do
  let inherit := !pkg.isRoot
  if let some entry ← getEntry? ws dep inherit then
    entry.materialize ws.lakeEnv ws.dir ws.relPkgsDir ws.isMultiVersion
  else
    let matDep ← dep.materialize inherit
      ws.lakeEnv ws.dir ws.relPkgsDir pkg.relDir ws.isMultiVersion
    addEntry ws matDep.manifestEntry
    return matDep

/--
Exit code returned if Lake needs a manual restart.
Used, for instance, if the toolchain is updated and no Elan is detected.
-/
def restartCode : ExitCode := 4

/-- The toolchain information of a package. -/
structure ToolchainCandidate where
  /-- The name of the package which provided the toolchain candidate. -/
  src : Name
  /-- The version of the toolchain candidate. -/
  ver : ToolchainVer
  /-- Whether the candidate toolchain been fixed to particular version. -/
  fixed : Bool := false

private structure ToolchainState where
  /-- The name of depedency which provided the current candidate toolchain. -/
  src : Name
  /-- The current candidate toolchain version (if any). -/
  tc? : Option ToolchainVer
  /-- Incompatible candidate toolchains (if any). -/
  clashes : Array ToolchainCandidate
  /--
  Whether the candidate toolchain been fixed to particular version.
  If `false`, the search will update the toolchain further where possible.
  -/
  fixed : Bool

@[inline] def ToolchainState.replace
  (src : Name) (tc? : Option ToolchainVer) (fixed : Bool) (self : ToolchainState)
: ToolchainState := {self with src, tc?, fixed}

@[inline] def ToolchainState.addClash
  (src : Name) (ver : ToolchainVer) (fixed : Bool) (self : ToolchainState)
: ToolchainState := {self with clashes := self.clashes.push {src, ver, fixed}}

/--
Update the workspace's `lean-toolchain` if necessary.

Compares the root's toolchain with that of its direct dependencies to find the
best match. If none can be found, issue warning and return normally. If an
update is found
-/
def Workspace.updateToolchain
  (ws : Workspace) (rootDeps : Array MaterializedDep)
: LoggerIO PUnit := do
  let rootToolchainFile := ws.root.dir / toolchainFileName
  let rootTc? ← ToolchainVer.ofDir? ws.dir
  let s : ToolchainState := ⟨ws.root.baseName, rootTc?, #[], ws.root.fixedToolchain⟩
  let ⟨src, tc?, tcs, fixed⟩ ← rootDeps.foldlM (init := s) fun s dep => do
    let depTc? ← ToolchainVer.ofDir? (ws.dir / dep.relPkgDir)
    let some depTc := depTc?
      | return s
    let some tc := s.tc?
      | return s.replace dep.name depTc? dep.fixedToolchain
    if dep.fixedToolchain then
      if s.fixed then
        if tc = depTc then
          return s
        else
          return s.addClash dep.name depTc dep.fixedToolchain -- true
      else
        if tc ≤ depTc then
          return s.replace dep.name depTc dep.fixedToolchain -- true
        else
          return s.addClash dep.name depTc dep.fixedToolchain -- true
    else
      if depTc ≤ tc then
        return s
      else if !s.fixed && tc < depTc then
        return s.replace dep.name depTc dep.fixedToolchain -- false
      else
        return s.addClash dep.name depTc dep.fixedToolchain -- false
  if 0 < tcs.size then
    let s := "toolchain not updated; multiple toolchain candidates:"
    let addEntry s tc src fixed :=
      let fixed := if fixed then " (fixed toolchain)" else ""
      s!"{s}\n  {tc}\n    from {src}{fixed}"
    let s := if let some tc := tc? then addEntry s tc src fixed else s
    let s := tcs.foldl (init := s) fun s ⟨src, tc, fixed⟩ => addEntry s tc src fixed
    logWarning s
  else if let some tc := tc? then
    if rootTc?.any (· == tc) then
      logInfo "toolchain not updated; already up-to-date"
      return
    logInfo s!"updating toolchain to '{tc}'"
    IO.FS.writeFile rootToolchainFile tc.toString
    let some lakeArgs := ws.lakeArgs?
      | logInfo s!"cannot auto-restart; you will need to manually restart Lake"
        IO.Process.exit restartCode.toUInt8
    let some elanInstall := ws.lakeEnv.elan?
      | logInfo s!"no Elan detected; you will need to manually restart Lake"
        IO.Process.exit restartCode.toUInt8
    logInfo s!"restarting Lake via Elan"
    let child ← IO.Process.spawn {
      cmd := elanInstall.elan.toString
      args := #["run", "--install", tc.toString, "lake"] ++ lakeArgs
      env := ws.lakeEnv.noToolchainVars
    }
    IO.Process.exit (← child.wait).toUInt8
  else
    logInfo s!"toolchain not updated; no toolchain information found"

/--
Updates the workspace, materializing and reconfiguring dependencies.

Dependencies are updated to latest specific revision matching that in `require`
(e.g., if the `require` is `@master`, update to latest commit on master) or
removed if the `require` is removed.
If `tuUpdate` is empty, all direct dependencies of the workspace's root will be
updated and/or remove. Otherwise, only those specified will be updated.

If `updateToolchain := true`, the workspace's toolchain is also updated to the
latest toolchain compatible with the root and its direct dependencies.
If there are multiple incomparable toolchain versions across them,
a warning will be issued and no update performed.
If an update is performed, Lake will automatically restart the update on the new
toolchain (via `elan`). If `elan` is missing, it will instead request a manual
restart from the user and exit immediately with `restartCode`.

**Dependency Traversal Order**

All dependencies of a package are visited in reverse order before recursing
to the dependencies' dependencies. For example, given the dependency graph:

```
R
|- A
|- B
 |- X
 |- Y
|- C
```

Lake follows the order `R`, `C`, `B`, `A`, `Y`, `X`.

The reason for this is two-fold:
1. Like targets, later requires should shadow earlier definitions.
2. Requires written by a user should take priority over those inherited
from dependencies.

Were Lake to use a depth-first traversal, for example, Lake would follow
the order `R`, `A`, `B`, `X`, `Y`, `C`. If `X` and `C` are both the package
`foo`, Lake would use the configuration of `foo` found in `B` rather than in
the root `R`, which would likely confuse the user.
-/
def Workspace.updateAndMaterializeCore
  (ws : Workspace)
  (toUpdate : NameSet := {}) (leanOpts : Options := {})
  (updateToolchain := true)
: LoggerIO (Workspace × EntryMap) := UpdateT.run do
  reuseManifest ws toUpdate
  if updateToolchain then
    let deps := ws.root.depConfigs.reverse
    let matDeps ← deps.mapM fun dep => do
      if ws.root.baseName = dep.name then
        error s!"{ws.root.prettyName}: package requires itself (or a package with the same name)"
      updateAndAddDep ws.root dep ws
    ws.updateToolchain matDeps
    let start := ws.packages.size
    let ws ← (deps.zip matDeps).foldlM (init := ws) fun ws (dep, matDep) => do
      (·.1) <$> ws.addDepPackage' matDep dep.opts leanOpts true
    let stop := ws.packages.size
    let ws ← ws.packages.foldlM (init := ws) (start := start) fun ws pkg =>
      ws.resolveDepsCore updateAndAddDep pkg [ws.root.baseName] leanOpts true
    -- Set dependency packages after `resolveDepsCore` so
    -- that the dependencies' dependencies are also properly set
    return ws.setDepPkgs ws.root.wsIdx ws.packages[start...<stop]
  else
    ws.resolveDepsCore updateAndAddDep (leanOpts := leanOpts) (reconfigure := true)
where
  @[inline] updateAndAddDep pkg dep ws : UpdateM MaterializedDep := do
    logVerbose s!"{ws.root.prettyName}: updating '{dep.resolverDescr}' with {toJson dep.opts}"
    let matDep ← updateAndMaterializeDep ws pkg dep
    addDependencyEntries ws matDep
    return matDep

/-- Write package entries to the workspace manifest. -/
def Workspace.writeManifest
  (ws : Workspace) (entries : EntryMap)
: IO PUnit := do
  let manifestEntries := ws.packages.foldl (init := #[]) fun arr pkg =>
    match entries.get? pkg.baseName with
    | some entries => entries.foldl (init := arr) fun arr entry =>
      arr.push <| entry.finalize pkg.version pkg.relConfigFile pkg.relManifestFile
    | none => arr -- should only be the case for the root
  let manifest : Manifest := {
    name := ws.root.baseName
    fixedToolchain := ws.root.fixedToolchain
    lakeDir := ws.relLakeDir
    multiVersion := ws.isMultiVersion
    packagesDir? := ws.relPkgsDir
    packages := manifestEntries
  }
  manifest.save ws.manifestFile

/-- Run a package's `post_update` hooks. -/
def Package.runPostUpdateHooks (pkg : Package) : LakeT LoggerIO PUnit := do
  unless pkg.postUpdateHooks.isEmpty do
  logInfo s!"{pkg.prettyName}: running post-update hooks"
  pkg.postUpdateHooks.forM fun hook => hook.get.fn pkg

/--
Updates the workspace, writes the new Lake manifest, and runs package
post-update hooks.

See `Workspace.updateAndMaterializeCore` for details on the update process.
-/
public def Workspace.updateAndMaterialize
  (ws : Workspace)
  (toUpdate : NameSet := {}) (leanOpts : Options := {})
  (updateToolchain := true)
: LoggerIO Workspace := do
  let (ws, entries) ←
    ws.updateAndMaterializeCore toUpdate leanOpts updateToolchain
  ws.writeManifest entries
  ws.runLakeT do ws.packages.forM (·.runPostUpdateHooks)
  return ws

/--
Check whether entries in the manifest are up-to-date,
reporting warnings and/or errors as appropriate.
-/
def validateManifest
  (pkgEntries : EntryMap) (deps : Array Dependency) (multiVersion : Bool)
: LoggerIO PUnit := do
  deps.forM fun dep => do
    let warnOutOfDate (what : String) :=
      logWarning <|
        s!"manifest out of date: {what} of dependency '{dep.name}' changed; \
        use `lake update {dep.name}` to update it"
    let some src := dep.src? | return
    let some entry := pkgEntries.resolve? dep multiVersion false | return
    match src, entry.src with
    | .git (url := url) (rev := rev) .., .git (url := url') (inputRev? := rev')  .. =>
      if url ≠ url' then warnOutOfDate "git url"
      if rev ≠ rev' then warnOutOfDate "git revision"
    | .path .., .path .. => pure ()
    | _, _ => warnOutOfDate "source kind (git/path)"

/--
Resolving a workspace's dependencies using a manifest,
downloading and/or updating them as necessary.
-/
public def Workspace.materializeDeps
  (ws : Workspace) (manifest : Manifest)
  (leanOpts : Options := {}) (reconfigure := false)
  (overrides : Array PackageEntry := #[])
: LoggerIO Workspace := do
  -- Check locked configuration
  if !manifest.packages.isEmpty && manifest.packagesDir? != some (mkRelPathString ws.relPkgsDir) then
    logWarning s!"manifest out of date: packages directory changed; \
      use `lake update` to rebuild the manifest \
      (warning: this will update ALL workspace dependencies)"
  if manifest.multiVersion != ws.isMultiVersion then
    logWarning s!"manifest out of date: multi-version setting changed \
      (from `{manifest.multiVersion}` to `{ws.isMultiVersion}`); \
      use `lake update` to rebuild the manifest \
      (warning: this will update ALL workspace dependencies)"
  let multiVersion := manifest.multiVersion
  let relPkgsDir := manifest.packagesDir?.getD ws.relPkgsDir
  -- Collect locked dependencies from the manifest and overides
  let pkgEntries ← id do
    let pkgEntries : EntryMap := {}
    let pkgEntries := manifest.packages.foldl (init := pkgEntries) fun map entry =>
      map.add entry multiVersion
    validateManifest pkgEntries ws.root.depConfigs multiVersion
    let wsOverrides ← Manifest.tryLoadEntries ws.packageOverridesFile
    let pkgEntries := wsOverrides.foldl (init := pkgEntries) fun map entry =>
      map.add entry multiVersion
    let pkgEntries := overrides.foldl (init := pkgEntries) fun map entry =>
      map.add entry multiVersion
    return pkgEntries
  if pkgEntries.isEmpty && !ws.root.depConfigs.isEmpty then
    error "missing manifest; use `lake update` to generate one"
  -- Materialize all dependencies
  ws.resolveDepsCore (leanOpts := leanOpts) (reconfigure := reconfigure) fun pkg dep ws => do
    if let some entry := pkgEntries.resolve? dep multiVersion (!pkg.isRoot) then
      entry.materialize ws.lakeEnv ws.dir relPkgsDir multiVersion
    else
      if pkg.isRoot then
        error <|
          s!"dependency '{dep.name}' not in manifest; \
          use `lake update {dep.name}` to add it"
      else
        error <|
          s!"dependency '{dep.name}' of '{pkg.prettyName}' not in manifest; \
          this suggests that the manifest is corrupt; \
          use `lake update` to generate a new, complete file \
          (warning: this will update ALL workspace dependencies)"
