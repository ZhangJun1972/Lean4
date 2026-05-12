# Lean 4版本治理与库架构标准化提案

## 摘要

本提案旨在解决Lean 4生态系统中普遍存在的版本碎片化问题，通过建立清晰的标准语法、标准库、特色库与待完善库的层级体系，确保代码在不同版本间的可移植性和长期稳定性。

---

## 一、问题分析

### 1.1 当前痛点

经过对Lean 4版本历史的深入研究，我们发现以下核心问题：

#### 版本碎片化
- Lean 4采用约每月一次的小版本发布节奏
- **没有强有力的向后兼容性保证**
- 几乎每个版本都包含破坏性变更

#### 版本号命名问题
当前版本号 `v4.x.y` 容易引起误解：
- `v4.9.0` 看起来像是小版本升级，但实际上已是第9个次版本
- `v4.10.0` 看起来像重大升级，易被误解为"第4版第10次升级"
- 没有清晰表达版本稳定性、兼容性级别
- 建议改为：`v4.xx.yy` 或更清晰的版本号命名方式

#### 工具链与依赖绑定问题
```toml
# lean-toolchain文件
leanprover/lean4:v4.25.0

# lakefile.toml依赖声明
[[require]]
name = "mathlib"
scope = "leanprover-community"
# 如果mathlib期望v4.24.0，导入就会失败
```

### 1.2 当前库架构现状

```
Lean 4核心
├── Init/          # 基础库
│   ├── Data/      # 核心数据类型
│   ├── Control/   # 单子等控制结构
│   ├── Meta/      # 元编程基础
│   └── Tactics/   # 基础战术
├── Lean/          # 编译器与元编程API
│   ├── Elab/      # 精化器
│   ├── Meta/      # 元编程
│   └── Tactic/    # 战术系统
└── Std/           # 标准扩展库
    ├── Data/      # 高级数据结构
    ├── Sync/      # 并发原语
    └── Tactic/    # 扩展战术

Mathlib（第三方）
├── Algebra/       # 代数学
├── Analysis/      # 分析学
├── Topology/      # 拓扑学
└── ...
```

---

## 二、提议的解决方案

### 2.1 四级库架构

我们建议建立以下四级架构：

```
┌─────────────────────────────────────────────────────┐
│  Level 4: 待完善库 (Incubating Libraries)          │
│  - 实验性API，可能随时变更                          │
│  - 不保证稳定性                                    │
│  - 例如：正在开发中的新战术库                       │
├─────────────────────────────────────────────────────┤
│  Level 3: 特色库 (Feature Libraries)               │
│  - 每季度迭代                                      │
│  - 新功能优先在此引入                              │
│  - 例如：Std.Ext, Mathlib.Experimental             │
├─────────────────────────────────────────────────────┤
│  Level 2: 标准库 (Standard Library)                │
│  - 每年迭代                                        │
│  - 提供长期稳定API                                 │
│  - 例如：Init.* (筛选后), Lean.Stable.*             │
├─────────────────────────────────────────────────────┤
│  Level 1: 标准语法 (Standard Syntax)               │
│  - 两年迭代周期                                    │
│  - 语言核心语法，极少变更                           │
│  - 例如：归纳类型、函数定义、基本战术              │
└─────────────────────────────────────────────────────┘
```

### 2.2 具体架构设计

#### Level 1: 标准语法 (Standard Syntax)

**迭代周期**: 2年

**包含内容**:
- 归纳类型定义语法
- 函数定义语法
- 基础表达式构造
- 核心战术：`intro`, `exact`, `apply`, `rfl`
- 类型类核心机制
- 模块系统

**稳定性承诺**:
- 无破坏性变更
- 新语法以扩展方式添加
- 旧语法永远不删除（至少保留两个周期）

**实现方式**:
```lean
-- 核心语法模块（永远稳定）
@[stable_since "v4.0"]
inductive Nat where
  | zero : Nat
  | succ : Nat → Nat

-- 扩展语法可以标注为 @[experimental]
@[experimental_since "v4.30"]
syntax "my_new_syntax" : term
```

#### Level 2: 标准库 (Standard Library)

**迭代周期**: 1年

**包含内容**:
- 核心数据类型的稳定API子集
  - `List`, `Array`, `Option`, `Result`
  - `Nat`, `Int`, `String`, `Bool`
- 标准类型类
  - `BEq`, `Ord`, `Hashable`, `Functor`, `Monad`
- 基础战术库
  - `simp`核心，`rw`, `induction`
- IO基础

**包结构示例**:
```
Lean.Stable/
├── Data/
│   ├── List.Stable.lean      -- 稳定的List API
│   ├── Nat.Stable.lean       -- 稳定的Nat API
│   └── Option.Stable.lean
├── Control/
│   ├── Monad.Stable.lean
│   └── Functor.Stable.lean
└── Tactic/
    └── Core.Stable.lean
```

**版本兼容性**:
```lean
-- 每个版本都保留旧版API
@[deprecated_since "v4.30" "use List.Stable.find instead"]
def List.oldFind : ...

-- 新API在特色库中引入
@[since "v4.30"]
def List.Stable.find : ...
```

#### Level 3: 特色库 (Feature Libraries)

**迭代周期**: 季度

**包含内容**:
- 新添加的数据结构
- 实验性战术
- 性能优化的API
- 新的类型类实例

**包结构示例**:
```
Std.Feature/
├── Data/
│   ├── HashMap.Feature.lean
│   ├── TreeMap.Feature.lean
│   └── Iterator.Feature.lean
├── Tactic/
│   ├── Omega.Feature.lean
│   └── Grind.Feature.lean
└── Control/
    └── NewMonad.Feature.lean
```

**迁移策略**:
- 特色库中的API经过2个季度的验证后，可迁移到标准库
- 迁移时保留别名指向旧位置
- 添加`@[moved_to "Lean.Stable.Data.List"]`注解

#### Level 4: 待完善库 (Incubating Libraries)

**迭代周期**: 无固定周期，随开发推进

**包含内容**:
- 完全实验性的新功能
- 正在设计中的API
- 可能被完全重写的代码
- 第三方贡献的新库

**包结构示例**:
```
Lean.Incubating/
├── Data/
│   ├── NewStructure.Incubating.lean
│   └── ExperimentalType.Incubating.lean
├── Tactic/
│   └── NewTactic.Incubating.lean
└── Meta/
    └── NewMetaProgram.Incubating.lean
```

**使用警告**:
```lean
-- 自动生成导入警告
@[incubating_warning "This API is experimental and may change at any time"]
def Lean.Incubating.someNewFunction : ...
```

---

## 三、版本管理策略

### 3.1 版本号规范

#### 改进的版本号方案

建议采用更清晰的 `vMAJOR.XX.PATCH-LEVEL` 格式：

```
vMAJOR.XX.PATCH-LEVEL
  │    │   │    └─ 稳定级别 (1=标准语法, 2=标准库, 3=特色库, 4=待完善库)
  │    │   └─────── 补丁版本，仅bug修复
  │    └─────────── 双位数的MINOR版本号，避免"v4.9到v4.10"这种看似重大升级的误解
  └─────────────────── 主版本，标准语法迭代
```

**优势**:
- 使用双位数避免误解：`v4.09.0` → `v4.10.0` 看起来更自然
- 清晰表达版本关系，避免单数字版本号造成的"跳跃感"

**示例**:
- `v5.00.0-1`: 标准语法重大更新
- `v4.30.0-2`: 标准库年度更新
- `v4.29.1-3`: 特色库季度更新
- `v4.29.1-4`: 待完善库更新

### 3.2 兼容性矩阵

| 你的代码使用 | 可兼容的Lean版本 |
|------------|----------------|
| 仅标准语法 (Level 1) | v4.x, v5.x (两年内) |
| 标准库 (Level 2) | v4.20-v4.30 (一年内) |
| 特色库 (Level 3) | v4.28-v4.30 (一季度内) |
| 待完善库 (Level 4) | 仅当前版本 |

### 3.3 工具链改进

**lakefile.toml 新配置**:
```toml
[package]
name = "my_project"
version = "0.1.0"

# 按稳定性级别声明依赖
[dependencies.stable]
level = 2  # 使用到标准库级别
lean_version = "v4.29.0-2"

[dependencies.feature]
level = 3
mathlib = { scope = "leanprover-community", rev = "stable-2025q2" }

# 自动兼容性检查工具
[tool.lake.compatibility]
enforce_level = 2
```

**lean-toolchain 增强**:
```
# 支持多级别版本指定
leanprover/lean4:v4.29.0-1#stable
leanprover/lean4:v4.29.0-2#feature
```

### 3.4 共享依赖库规范

#### 问题
- 每个项目独立下载完整工具链和mathlib，浪费存储空间
- 相同版本的依赖被重复下载多次
- 新项目初始化慢，网络传输压力大

#### 解决方案

**1. 全局缓存目录规范**

```toml
# lakefile.toml - 新增全局缓存配置
[package]
name = "my_project"
version = "0.1.0"

# 共享库配置
[shared_dependencies]
enabled = true
cache_dir = "~/.lean4/shared"  # 共享库根目录
# 或使用环境变量: LEAN4_SHARED_CACHE=~/.lean4/shared
```

**2. 标准库分级缓存结构**

```
~/.lean4/shared/
├── toolchains/
│   ├── lean4-v4.29.0/
│   ├── lean4-v4.30.0/
│   └── ...
├── stdlibs/
│   ├── level1/          # 标准语法 (Level 1)
│   │   └── v4.x/
│   ├── level2/          # 标准库 (Level 2)
│   │   └── v4.29/
│   └── level3/          # 特色库 (Level 3)
│       └── v4.29/
└── community/
    ├── mathlib/
    │   ├── stable-v4.29/
    │   └── nightly/
    └── other_libs/
```

**3. 项目引用配置**

```toml
# lakefile.toml 配置示例
[[require]]
name = "mathlib"
scope = "leanprover-community"
source = "shared"           # 优先从共享库加载
rev = "stable-v4.29"
fallback = "git"            # 找不到时回退到Git

# 或显式指定共享路径
[[require]]
name = "my_shared_lib"
path = "~/.lean4/shared/community/my_lib"
```

**4. 环境变量支持**

```bash
# 全局设置
export LEAN4_SHARED_CACHE=~/.lean4/shared
export LEAN4_TOOLCHAIN_CACHE=~/.lean4/shared/toolchains
export LEAN4_STDLIB_CACHE=~/.lean4/shared/stdlibs

# 项目临时覆盖
LEAN4_SHARED_CACHE=/custom/path lake build
```

**5. lake 新增命令**

```bash
# 管理共享库
lake shared list                # 列出所有共享库
lake shared update mathlib      # 更新共享库
lake shared clean               # 清理过期的共享库
lake shared install lean4-v4.30 # 安装新工具链到共享目录
```

**6. 标准库统一规范**

标准库 (Level 2) 需要满足：
- 固定API签名，保证跨版本兼容
- 完整的测试覆盖
- 文档化的使用规范
- 明确的弃用周期（至少1年）

---

## 四、迁移路径

### 4.1 短期（3个月）

1. **建立稳定性注解系统**
   ```lean
   -- 现有代码添加注解
   @[stable_since "v4.0"]
   def List.map : ...

   @[deprecated_since "v4.25" "use List.Stable.find"]
   def List.oldFind : ...
   ```

2. **创建Stable命名空间**
   ```lean
   -- 复制稳定API到新命名空间
   namespace Lean.Stable
     namespace Data
       def List.map := List.map
       -- 只复制稳定的API
     end Data
   end Lean.Stable
   ```

3. **初步文档**
   - 标记现有API的稳定性级别
   - 创建迁移指南

### 4.2 中期（6-12个月）

1. **正式推出四级架构**
   - 按新结构组织代码库
   - 设置CI检查确保稳定性级别

2. **Mathlib对齐**
   - Mathlib也采用类似的四层结构
   - `Mathlib.Stable.*`, `Mathlib.Feature.*` 等

3. **版本管理工具**
   - `lake check-compat`: 检查兼容性
   - `lake migrate`: 自动迁移到新API

### 4.3 长期（2年）

1. **第一个LTS版本**
   - v5.0.0作为第一个长期支持版本
   - 保证5年支持期

2. **完善生态**
   - 所有主要库都采用四级架构
   - 成熟的工具链支持

---

## 五、具体实现建议

### 5.1 注解系统实现

```lean
-- 在Init.Attributes中添加
syntax (name := stableSince) "stable_since" "(" term ")" : attr
syntax (name := deprecatedSince) "deprecated_since" "(" term ")" ("," term)? : attr
syntax (name := experimentalSince) "experimental_since" "(" term ")" : attr
syntax (name := movedTo) "moved_to" "(" term ")" : attr
syntax (name := incubatingWarning) "incubating_warning" "(" term ")" : attr

-- 注解使用示例
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

### 5.2 Lake工具增强

```lean
-- lakefile.toml 示例
[package]
name = "my_project"
compatibility_level = 2  # 保证标准库级别的兼容性

[[lean_lib]]
name = "MyLib"
src_dir = "src"
stability = 2  # 本库提供标准库级别的稳定性

[[require]]
name = "mathlib"
scope = "leanprover-community"
stability = 3  # 可以使用特色库级别功能

[tool.lake]
# 兼容性检查
check_compatibility = true
# 自动修复弃用警告
auto_fix_deprecations = true
```

---

## 六、总结

本提案通过四级库架构和分层版本管理，解决Lean 4生态系统的版本碎片化问题：

1. **标准语法层**：提供长期稳定的基础
2. **标准库层**：年度迭代，平衡稳定与进步
3. **特色库层**：季度迭代，快速引入新功能
4. **待完善库层**：完全实验性，无稳定性承诺

辅以注解系统、增强的工具链和清晰的迁移路径，我们可以建立一个既稳定又充满活力的Lean 4生态系统。
