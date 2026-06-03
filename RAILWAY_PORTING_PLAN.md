# Railway Primitive Porting Plan (铁路图元移植计划)

## Architecture (5-Layer)

```
go-topo/                           ← C++ kernel + Go cgo bindings (ALREADY DONE)
  └── src/primitives_railway.{hh,cc}     ← 52+ C++ types + C API
  └── primitives_railway.go             ← Go CreateXxx() functions

topotypes/                         ← Parametric type definitions (Go structs)
  └── railway/railway.go          ← {Base, Shape, Xxx struct, NewXxx(), Unmarshal}
  └── parametric.go               ← case railway.Major: dispatch (已添加，后续免改)

flywave-topovis/                   ← Parametric builders (topotypes → go-topo shapes)
  └── railway/
      ├── railway.go              ← BasePrimitive + CreatePrimitive() type switch
      └── rod_insulator.go        ← RodInsulatorPrimitive (每类型一个文件)
  └── parametric.go               ← case railway.Major: dispatch (已添加，后续免改)

topo.js/                           ← WASM/JS SDK
  └── src/primitives_bindings.cc  ← Embind C++→JS bindings
  └── src/primitives.d.ts         ← TS type declarations (手工维护)
  └── src/primitives.export.json  ← TS export manifest
  └── packages/topo-wasm/         ← Auto-generated WASM .wasm/.js/.d.ts

topo-primitives/                   ← TS Object wrappers (可序列化)
  └── lib/types/railway.ts       ← TS Object interface (XxxObject)
  └── lib/railway/index.ts       ← Primitive class + createRLPrimitive()
  └── lib/index.ts               ← export * from "./railway" (已添加，后续免改)

topo-example/                      ← 演示应用 (手动添加 GUI 选项)
  └── src/primitives.ts           ← createShapePrimitive() dispatch
  └── src/world.ts                ← shape type list + color
```

## Per-Type Workflow (8 Steps)

| # | Layer | 操作 | 需修改文件 |
|---|-------|------|-----------|
| 0 | **go-topo** 🔍 | 坐标系原点优化：确定一端圆心为原点；检查 C++ 枚举名与 `primitives.hh` 不冲突 | `src/primitives_railway.hh` (如有冲突改名) |
| 1 | **topotypes** 📝 | 定义 Go struct + JSON tags + NewXxx() + Unmarshal case | `topotypes/railway/railway.go` |
| 2 | **flywave-topovis** 🏗️ | 实现 `ParametricPrimitive` (ValidParams + BuildShape + BuildOutline) + 注册 | `flywave-topovis/railway/xxx.go`, `railway.go` |
| 3 | **topo.js** 🔧 | Embind `value_object` + `function` 绑定 | `topo.js/src/primitives_bindings.cc` |
| 4 | **topo.js** 📝 | TS 声明接口 + export.json 注册 | `primitives.d.ts`, `export.json` |
| 5 | **topo-primitives** 📦 | TS Object 接口 + Primitive 类 + createRLPrimitive case | `types/railway.ts`, `railway/index.ts` |
| 6 | **flywave-topovis** ✅ | 写 Go 测试 → `go test -run TestXxx` | `flywave-topovis/railway_test.go` |
| 7 | **WASM** 🔨 | `make topo-bindings && make run && make gen-ts` | — |
| 8 | **topo-example** 🖥️ | 添加 RLPrimitiveType 到 GUI 下拉列表 + 颜色 | `primitives.ts`, `world.ts` |

## 每个步骤的精确操作指南

### Step 0: C++ 坐标系优化 + 枚举冲突检查

**坐标系：** 确定原点位置。原则：一端端面圆心（如圆柱底面圆心）。检查 `create_xxx` 函数以 `gp::Origin()` 构建，通过 `WithPlace` 变换定位。

**枚举冲突：** `primitives_railway.hh` 中的枚举可能和 `primitives.hh` 冲突。已发现的冲突及修复方式：

| 冲突枚举 | primitives.hh | primitives_railway.hh | 修复 |
|----------|---------------|----------------------|------|
| `curve_type` | `enum class curve_type { LINE, ARC, BEZIER }` (line 392) | `enum class curve_type { LINE, ARC, BEZIER }` (line 989) | 改名为 `rail_curve_type` |
| `profile_type` | `enum profile_type { TYPE_NONE, ... }` (line 2265) | `enum class profile_type { RAIL, CHANNEL, PLATE }` (line 990) | 改名为 `rail_profile_type` |

**改名后必须在 `.cc` 文件中同步更新所有引用。**

### Step 1: topotypes — `topotypes/railway/railway.go`

```go
package railway

import (
    "encoding/json"
    "fmt"
)

const Major = "RAILWAY"

type Shape interface {
    GetType() string
}

type Base struct {
    Version int    `json:"version"`
    Type    string `json:"type"`
}

func (b *Base) GetType() string { return b.Type }

// Xxx — 中文名
type Xxx struct {
    Base
    Field1 float64 `json:"field1"`
    Field2 int     `json:"field2"`
}

func NewXxx() *Xxx {
    return &Xxx{Base: Base{Type: "RAILWAY/Xxx"}}
}

func Unmarshal(ty string, bt []byte) (Shape, error) {
    switch ty {
    case "RAILWAY/RodInsulator":
        // 已有，勿删
    case "RAILWAY/Xxx":
        shape := Xxx{}
        err := json.Unmarshal(bt, &shape)
        return &shape, err
    default:
        return nil, fmt.Errorf("invalid railway type: %s", ty)
    }
}
```

### Step 2: flywave-topovis — builder + 注册

**`flywave-topovis/railway/xxx.go`** (每类型一个文件):
```go
package railway

import (
    "github.com/flywave/flywave-topovis/iface"
    "github.com/flywave/flywave-topovis/outline"
    topo "github.com/flywave/go-topo"
    trailway "github.com/flywave/topotypes/railway"
)

type XxxPrimitive struct {
    BasePrimitive
    shape trailway.Xxx
}

func NewXxxPrimitive(iface iface.Parametric, shape *trailway.Xxx) *XxxPrimitive {
    if shape == nil { return nil }
    return &XxxPrimitive{BasePrimitive: BasePrimitive{iface: iface}, shape: *shape}
}

func (p *XxxPrimitive) BuildOutline() ([]outline.Outline, error) {
    shps, err := p.BuildShape()
    if err != nil { return nil, err }
    return outline.BuildOutline(shps, 100)
}

func (p *XxxPrimitive) BuildShape() ([]*topo.Shape, error) {
    param := topo.XxxParams{
        Field1: p.shape.Field1,
        Field2: p.shape.Field2,
    }
    shp := topo.CreateXxx(param)
    return []*topo.Shape{shp}, nil
}

func (p *XxxPrimitive) ValidParams() bool {
    return p.shape.Field1 > 0
}
```

**`flywave-topovis/railway/railway.go`** 添加 switch case:
```go
func CreatePrimitive(iface iface.Parametric, shap topotypes.ParametricShape) iface.ParametricPrimitive {
    switch t := shap.(type) {
    case *trailway.RodInsulator:
        return NewRodInsulatorPrimitive(iface, t)
    case *trailway.Xxx:           // ← 新增
        return NewXxxPrimitive(iface, t) // ← 新增
    }
    return nil
}
```

### Step 3: Embind 绑定 — `topo.js/src/primitives_bindings.cc`

在 `EMSCRIPTEN_BINDINGS(Primitive)` 块末尾（`}` 前）添加：

```cpp
  // ==========================================================================
  // Xxx (中文名) — from primitives_railway.hh
  // ==========================================================================
  // (枚举只有 C++ 参数结构体包含 enum 字段时才需要)
  // enum_<xxx_type>("XxxType")
  //     .value("VAL1", xxx_type::VAL1);
  //
  value_object<xxx_params>("XxxParams")
      .field("field1", &xxx_params::field1)
      .field("field2", &xxx_params::field2);

  function("createXxx",
           select_overload<TopoDS_Shape(const xxx_params &)>(
               &create_xxx));
  function("createXxxWithPosition",
           select_overload<TopoDS_Shape(const xxx_params &,
                                        const gp_Pnt &, const gp_Dir &)>(
               &create_xxx));
```

⚠️ 注意：
- 确保添加 `#include "primitives_railway.hh"`（已在文件顶部，后续免改）
- 函数名用 `camelCase`：`createXxx` / `createXxxWithPosition`
- 带 `WithPlace` 的重载用 `select_overload` 区分
- enum 值名用全大写：`SOLID`, `HOLLOW`, `FLANGE`

### Step 4: TS 声明 — `topo.js/src/primitives.d.ts`

在 `Borehole` 段落之前（该文件按字母序组织）添加：

```typescript
// Xxx 参数结构体
export declare interface XxxParams {
    field1: number;
    field2: number;
}

export declare function createXxx(params: XxxParams): TopoDS_Shape;
export declare function createXxxWithPosition(params: XxxParams, basePoint: gp_Pnt, axisDirection: gp_Dir): TopoDS_Shape;
```

同时更新 `topo.js/src/primitives.export.json`：

```json
// interfaces 列表添加 "XxxParams"
// functions 列表添加 "createXxx", "createXxxWithPosition"  
// enums 列表添加 (有枚举时) "XxxType"
```

### Step 5: topo-primitives — TS Object + Primitive 类

**`topo-primitives/lib/types/railway.ts`** — 添加 Object 接口：

```typescript
import { Version } from "./types";

export interface XxxObject extends Version {
    type: 'RAILWAY/Xxx';
    // 可选：如果 C++ params 有 enum 字段且名称与 type 冲突，用不同字段名
    // xxxType?: number;
    field1: number;
    field2: number;
}
```

**`topo-primitives/lib/railway/index.ts`** — 添加 Primitive 类 + createRLPrimitive case：

```typescript
import {
    Shape,
    TopoInstance,
    XxxParams,
} from "topo-wasm";
import { BasePrimitive, Primitive } from "../primitive";
import { XxxObject } from "../types/railway";

export enum RLPrimitiveType {
    RodInsulator = "RAILWAY/RodInsulator",
    Xxx = "RAILWAY/Xxx",
}

export type RLPrimitive = RodInsulatorPrimitive | XxxPrimitive;

export class XxxPrimitive extends BasePrimitive<XxxParams, XxxObject> {

    constructor(tp: TopoInstance, params?: XxxObject) {
        super(tp, params);
    }

    getType(): string {
        return RLPrimitiveType.Xxx;
    }

    setDefault(): Primitive<XxxParams, XxxObject> {
        this.params = {
            field1: 100,
            field2: 5,
        } as any;
        return this;
    }

    public setParams(params: XxxParams): Primitive<XxxParams, XxxObject> {
        this.params = params;
        return this;
    }

    public valid(): boolean {
        return this.params.field1 > 0;
    }

    public build(): Shape | undefined {
        if (this.valid()) {
            return new this.tp.Shape(this.tp.createXxx(this.params), false);
        }
        throw new Error("Invalid parameters for Xxx");
    }

    fromObject(o?: XxxObject): Primitive<XxxParams, XxxObject> {
        if (o === undefined) return this;
        if (o['version']) this.version = o['version'];
        this.params = {
            field1: o['field1'],
            field2: o['field2'],
        } as any;
        return this;
    }

    toObject(): XxxObject | undefined {
        return BasePrimitive.buildObject(new Map<string, any>([
            ['type', this.getType()],
            ['version', this.getVersion()],
            ['field1', this.params.field1],
            ['field2', this.params.field2],
        ])) as XxxObject;
    }
};

// createRLPrimitive 的 switch 中添加：
export function createRLPrimitive(tp: TopoInstance, args?: RLPrimitiveType | any): RLPrimitive | undefined {
    ...
    switch (type) {
        case RLPrimitiveType.RodInsulator:
            primitive = new RodInsulatorPrimitive(tp);
            break;
        case RLPrimitiveType.Xxx:
            primitive = new XxxPrimitive(tp);  // ← 新增
            break;
    }
    ...
}
```

⚠️ **Embind enum 字段的关键陷阱**：

当 C++ struct 包含 `enum class` 类型字段时（如 `rod_insulator_params::type`），**必须通过 `this.tp.EnumType.VALUE` 访问枚举值**，不能直接赋数字：

```typescript
// ❌ 错误：Embind 校验报 "Missing field"
this.params.type = 1;

// ✅ 正确
this.params = {
    type: this.tp.RodInsulatorType.SOLID as any,
    ...
} as any;
```

同时 Object 接口中 `type` 字段已被 TS 判别器占用，C++ 枚举值需用不同字段名（如 `rodType`）：
```typescript
// Object 接口
export interface XxxObject extends Version {
    type: 'RAILWAY/Xxx';
    xxxType?: number;  // 存储 C++ enum 值
}

// toObject
toObject() {
    return BasePrimitive.buildObject(new Map([
        ['type', this.getType()],
        ['xxxType', this.params.type],  // C++ enum 值
        ...
    ]));
}
```

### Step 6: flywave-topovis 测试 — `flywave-topovis/railway_test.go`

```go
package topovis_test

import (
    "fmt"
    "testing"

    topovis "github.com/flywave/flywave-topovis"
    mst "github.com/flywave/go-mst"
    trailway "github.com/flywave/topotypes/railway"

    "github.com/flywave/flywave-topovis/model"
    "github.com/flywave/gltf"
    "github.com/flywave/go-geom"
    "github.com/flywave/go-geom/general"
    "github.com/flywave/topotypes"
)

func TestXxx(t *testing.T) {
    xxx := &trailway.Xxx{
        Base:   trailway.NewXxx().Base,
        Field1: 100,
        Field2: 5,
    }

    param := &topotypes.TopoParametric{
        Topos: topotypes.NewTopoParametric().Topos,
        Shape: xxx,
    }

    topodata := &model.TopoData{
        Topo: param,
        Geom: general.GeometryDataAsGeometry(geom.NewLineStringGeometryData([][]float64{
            {116.3974, 39.9087, 0},
            {116.3983, 39.9087, 0},
        })),
        SRID: 4326,
    }
    topodata.ToJson()

    ctx := topovis.NewContext()
    parms, err := topovis.NewParametric(ctx, topodata)
    if err != nil {
        t.Fatalf("NewParametric failed: %v", err)
    }
    if err := parms.Build(); err != nil {
        t.Fatalf("Build failed: %v", err)
    }
    if len(parms.Shapes) == 0 {
        t.Fatal("no shapes produced")
    }
    for i, s := range parms.Shapes {
        if s == nil || !s.IsValid() || s.IsNull() {
            t.Fatalf("shape %d is invalid", i)
        }
        s.WriteToStl(fmt.Sprintf("primitive_test/xxx_%d.stl", i))
    }

    mh, err := parms.CreateMesh()
    if err != nil {
        t.Fatalf("CreateMesh failed: %v", err)
    }
    doc, err := mst.MstToGltf([]*mst.Mesh{mh})
    if err != nil {
        t.Fatalf("MstToGltf failed: %v", err)
    }
    if err := gltf.SaveBinary(doc, "primitive_test/xxx.glb"); err != nil {
        t.Fatalf("SaveBinary failed: %v", err)
    }
}
```

运行：
```sh
cd flywave-topovis && mkdir -p primitive_test
go test -v -run TestXxx -count=1
```

### Step 7: WASM 编译

```sh
cd topo.js
make topo-bindings      # 编译 primitives_bindings.cc
make run                # 链接 WASM (耗时约2-5分钟)
make gen-ts             # 生成 TS 声明
```

验证 WASM 产物是否包含新类型：
```sh
grep 'createXxx\|XxxParams' packages/topo-wasm/src/topo.full.d.ts
```

### Step 8: topo-example GUI 添加

**`topo-example/src/world.ts`** 中：
```typescript
// 1. import 添加 RLPrimitiveType
import { ..., RLPrimitiveType } from "topo-primitives"

// 2. selectedShape 类型添加 RLPrimitiveType
selectedShape: ... | RLPrimitiveType = BasePrimitiveType.Pipe

// 3. allShapeTypes 添加
...Object.values(RLPrimitiveType),

// 4. getColorForShapeType 添加颜色
if (shapeType.includes('RAILWAY')) return 0xff69b4; // 粉红
```

**`topo-example/src/primitives.ts`** 中：
```typescript
// import 添加 RLPrimitiveType + createRLPrimitive
import { ..., RLPrimitiveType, createRLPrimitive } from "topo-primitives"

// shapeType 参数类型添加 RLPrimitiveType
shapeType: ... | RLPrimitiveType

// dispatch 添加:
if (Object.values(RLPrimitiveType).includes(shapeType as RLPrimitiveType)) {
    return createRLPrimitive(tp, shapeType as RLPrimitiveType);
}
```

## 已知陷阱清单

| # | 陷阱 | 现象 | 解决 |
|---|------|------|------|
| 1 | C++ enum 名与 `primitives.hh` 冲突 | WASM 编译报 `redefinition of 'xxx'` | 改名为 `rail_xxx`，同步改 `.cc` 引用 |
| 2 | Embind value_object 字段未初始化 | `Missing field: "xxx"` | `setDefault()` 必须用完整对象赋值 |
| 3 | Embind enum 字段赋值数字 | 同上或类型不匹配 | 用 `this.tp.EnumType.VALUE as any` |
| 4 | TS Object type 字段被判别器占用 | C++ enum 值无法存储 | 用不同字段名如 `rodType` |
| 5 | `float64` vs `float32` 类型不匹配 | go build 报类型错误 | flywave-topovis builder 用 `p.shape.Field` 直接赋值（类型一致） |
| 6 | WASM link 超时 | make run 卡住 | 设置 `timeout=600000` (10分钟) |
| 7 | ❌ `tsc` 编译源码目录 | `.js`/`.d.ts`/`.js.map` 被写入 `lib/` 源码目录 | **不要运行 `tsc`**，用 `rollup -c rollup.config.js` 构建。如需类型检查用 `npx tsc --noEmit` |
| 8 | ❌ `cmake` 编译 go-topo | C++ 静态库由用户手动维护 | **不要运行 cmake**，go-topo 的 C++ 代码修改后由用户手动编译 `cmake --build build/build --config Release && cmake --install build/build --prefix libs/darwin_arm` |

## 完成的类型

- [x] **1. RodInsulator** (棒式绝缘子) `RAILWAY/RodInsulator`
  - C++ 原点: 最底面（法兰底部或棒体底部）✓
  - topotypes: `railway/railway.go` ✓
  - flywave-topovis: `railway/rod_insulator.go` ✓
  - flywave-topovis 测试: `railway_test.go - TestRodInsulator` ✓
  - Embind 绑定: `primitives_bindings.cc` ✓
  - TS 声明: `primitives.d.ts` + `export.json` ✓
  - TS Object: `types/railway.ts` + `railway/index.ts` ✓
  - WASM 编译: `make topo-bindings run gen-ts` ✓
  - Example GUI: `primitives.ts` + `world.ts` ✓

---

## 待移植类型清单 (51 types)

### Group A: OCS Individual Components (14 remaining)

- [x] **2. ContactWire** (接触线) `RAILWAY/ContactWire`
  - C++: 3-point arc + MakePipeShell 驰度支持 ✓
  - C API: contact_wire_params_t 含 sag ✓
  - topotypes: `railway/railway.go` ✓
  - flywave-topovis: `railway/contact_wire.go` ✓
  - flywave-topovis 测试: `railway_test.go - TestContactWire` ✓
  - Embind 绑定: `primitives_bindings.cc` ✓
  - TS 声明: `primitives.d.ts` + `export.json` ✓
  - TS Object: `types/railway.ts` + `railway/index.ts` ✓
  - C++ 测试: `primitives_railway_test.cc - test_contact_wire` ✓
  - ⏳ C++ 编译: 需 `cmake --build`
- [x] **3. MessengerWire** (承力索) `RAILWAY/MessengerWire`
  - C++: MakePipeShell 驰度扫掠 ✓
  - C API: messenger_wire_params_t ✓
  - topotypes: `railway/railway.go` ✓
  - flywave-topovis: `railway/messenger_wire.go` ✓
  - flywave-topovis 测试: `railway_test.go - TestMessengerWire` ✓
  - Embind 绑定: `primitives_bindings.cc` ✓
  - TS 声明: `primitives.d.ts` + `export.json` ✓
  - TS Object: `types/railway.ts` + `railway/index.ts` ✓
  - C++ 测试: `primitives_railway_test.cc - test_messenger_wire` ✓
  - ⏳ C++ 编译: 需 `cmake --build`
- [x] **4. CrossArm** (横担) `RAILWAY/CrossArm`
  - ✅ C++ 原点: 几何中心（X 居中, Z 居中于 gap/2）
  - ✅ topotypes: `railway/railway.go`
  - ✅ flywave-topovis: `railway/crossarm.go`
  - ✅ flywave-topovis 测试: `railway_test.go - TestCrossArm`
  - ✅ Embind 绑定: `primitives_bindings.cc`
  - ✅ TS 声明: `primitives.d.ts` + `export.json`
  - ✅ TS Object: `types/railway.ts` + `railway/index.ts`
  - ✅ WASM 编译: `make topo topo-bindings run gen-ts`
- [x] **5. LevelCantilever** (平腕臂) `RAILWAY/LevelCantilever`
  - ✅ C++ 原点: 端面圆心，沿 X 正方向延伸（无需修改）
  - ✅ topotypes: `railway/railway.go`
  - ✅ flywave-topovis: `railway/levelcantilever.go`
  - ✅ flywave-topovis 测试: `railway_test.go - TestLevelCantilever`
  - ✅ Embind 绑定: `primitives_bindings.cc`
  - ✅ TS 声明: `primitives.d.ts` + `export.json`
  - ✅ TS Object: `types/railway.ts` + `railway/index.ts`
  - ✅ WASM 编译: `make topo-bindings run gen-ts`
- [x] **6. SlantCantilever** (斜腕臂) `RAILWAY/SlantCantilever`
  - ✅ C++ 原点: 端面圆心；沿 X 创建、绕 Y 旋转实现 +X → +Z 方向倾斜
  - ✅ topotypes: `railway/railway.go`
  - ✅ flywave-topovis: `railway/slantcantilever.go`
  - ✅ flywave-topovis 测试: `railway_test.go - TestSlantCantilever`
  - ✅ Embind 绑定: `primitives_bindings.cc`
  - ✅ TS 声明: `primitives.d.ts` + `export.json`
  - ✅ TS Object: `types/railway.ts` + `railway/index.ts`
  - ✅ WASM 编译: `make topo topo-bindings run gen-ts`
- [ ] **7. CantileverBrace** (斜撑) `RAILWAY/CantileverBrace`
  - 连接平腕臂和斜腕臂的自由端，组成三角支撑结构
  - 参数：length / outerDiameter / wallThickness
  - 长度可根据平腕臂+斜腕臂几何关系自动推算
  - C++ 实现需新增 struct + function (`create_cantilever_brace`)
  - 注意：需对 `primitives_railway.{hh,cc}` 新增，go-topo 层需新增
- [x] **8. CurvedArm** (弯臂) `RAILWAY/CurvedArm`
  - ✅ C++ 原点: 安装法兰底面中心（z 偏移 flangeThickness）
  - ✅ topotypes: `railway/railway.go`
  - ✅ flywave-topovis: `railway/curvedarm.go` + 测试 `TestCurvedArm`
  - ✅ Embind: `primitives_bindings.cc`
  - ✅ TS: `primitives.d.ts` + `export.json`
  - ✅ TS Object: `types/railway.ts` + `railway/index.ts`
  - ⏳ C++ 编译: 需 `cmake --build` 后 `cmake --install`
- [x] **9. MastBracket** (支柱连接座) `RAILWAY/MastBracket`
  - ✅ C++ 原点: 座体板底面中心（Z=0 底面, plateOrg 居中）
  - ✅ topotypes: `railway/railway.go`
  - ✅ flywave-topovis: `railway/mastbracket.go`
  - ✅ flywave-topovis 测试: `railway_test.go - TestMastBracket`
  - ✅ Embind 绑定: `primitives_bindings.cc`
  - ✅ TS 声明: `primitives.d.ts` + `export.json`
  - ✅ TS Object: `types/railway.ts` + `railway/index.ts`
  - ✅ C++ 测试: `primitives_railway_test.cc - test_mast_bracket`
  - ⏳ C++ 编译: 需 `cmake --build`
- [x] **10. RegistrationArm** (定位器) `RAILWAY/RegistrationArm`
- [x] **11. RegArmBracket** (定位器底座) `RAILWAY/RegArmBracket`
- [x] **12. GuyWire** (下锚拉线) `RAILWAY/GuyWire`
  - ✅ C++ 重写: 底座(YZ板)+安装环+缆绳+地锚环+锚筋+锚板+绝缘子
  - ✅ topotypes: `railway/railway.go`
  - ✅ flywave-topovis: `railway/guy_wire.go`
  - ✅ flywave-topovis 测试: `railway_test.go - TestGuyWire`
  - ✅ Embind 绑定: `primitives_bindings.cc`
  - ✅ TS 声明: `primitives.d.ts` + `export.json`
  - ✅ TS Object: `types/railway.ts` + `railway/index.ts`
  - ✅ C++ 测试: `primitives_railway_test.cc - test_guy_wire`
  - ⏳ C++ 编译: 需 `cmake --build`
- [x] **13. SteelMast** (钢支柱) `RAILWAY/SteelMast`
  - C++ 原点: 柱底法兰顶面（体从 Z=0 开始, 法兰低于原点）
  - topotypes: `railway/railway.go` ✓
  - flywave-topovis: `railway/steel_mast.go` ✓
  - flywave-topovis 测试: `railway_test.go - TestSteelMast` ✓
  - Embind 绑定: `primitives_bindings.cc` ✓
  - TS 声明: `primitives.d.ts` + `export.json` ✓
  - TS Object: `types/railway.ts` + `railway/index.ts` ✓
  - C++ 测试: `primitives_railway_test.cc` 已有 ✓
  - ⏳ C++ 编译: 需 `cmake --build`
- [x] **14. ConcreteMast** (混凝土支柱) `RAILWAY/ConcreteMast`
  - C++ 原点: 柱底截面中心 ✓
  - topotypes: `railway/railway.go` ✓
  - flywave-topovis: `railway/concrete_mast.go` ✓
  - flywave-topovis 测试: `railway_test.go - TestConcreteMast` ✓
  - Embind 绑定: `primitives_bindings.cc` ✓
  - TS 声明: `primitives.d.ts` + `export.json` ✓
  - TS Object: `types/railway.ts` + `railway/index.ts` ✓
  - C++ 测试: `primitives_railway_test.cc` 已有 ✓
  - ⏳ C++ 编译: 需 `cmake --build`
- [x] **15. OcsFoundation** (支柱基础) `RAILWAY/OcsFoundation`
  - ✅ C++ 原点: 顶部中心 Z=0, 整体 -Z 方向延伸
  - ✅ Go const: FoundationDirectBuried/Flange/BoredPile/ExcavatedPile/Anchor
  - ✅ topotypes: `railway/railway.go`
  - ✅ flywave-topovis: `railway/ocs_foundation.go`
  - ✅ flywave-topovis 测试: `railway_test.go - TestOcsFoundation`
  - ✅ Embind 绑定: `primitives_bindings.cc`
  - ✅ TS 声明: `primitives.d.ts` + `export.json`
  - ✅ TS Object: `types/railway.ts` + `railway/index.ts`
  - ✅ C++ 测试: `primitives_railway_test.cc - test_ocs_foundation`
  - ⏳ C++ 编译: 需 `cmake --build`
- [x] **16. Dropper** (吊弦) `RAILWAY/Dropper`
  - C++ 重写: 线夹+心形护环(环形托orus)+吊弦线
  - topotypes: `railway/railway.go` ✓
  - flywave-topovis: `railway/dropper.go` ✓
  - flywave-topovis 测试: `railway_test.go - TestDropper` ✓
  - Embind 绑定: `primitives_bindings.cc` ✓
  - TS 声明: `primitives.d.ts` + `export.json` ✓
  - TS Object: `types/railway.ts` + `railway/index.ts` ✓
  - C++ 测试: `primitives_railway_test.cc - test_dropper` ✓
  - ⏳ C++ 编译: 需 `cmake --build`

### Group B: OCS Connectors & Hardware (8 types)

- [ ] **17. CantileverBase** (腕臂底座) `RAILWAY/CantileverBase`
- [ ] **18. MWSaddle** (承力索座) `RAILWAY/MWSaddle`
- [ ] **19. BalanceWeight** (坠砣) `RAILWAY/BalanceWeight`
- [ ] **20. WeightRod** (坠砣杆) `RAILWAY/WeightRod`
- [ ] **21. AnchorFitting** (下锚金具) `RAILWAY/AnchorFitting`
- [ ] **22. Crossing** (线岔) `RAILWAY/Crossing`
- [ ] **23. HangerPost** (硬横跨吊柱) `RAILWAY/HangerPost`
- [ ] **24. PortalFrame** (梁顶门型架) `RAILWAY/PortalFrame`

### Group C: OCS Composite (5 types)

- [ ] **25. AuxBracket** (附加导线支架) `RAILWAY/AuxBracket`
- [ ] **26. HeadSpan** (软横跨) `RAILWAY/HeadSpan`
- [ ] **27. TransverseSpan** (硬横跨) `RAILWAY/TransverseSpan`
- [ ] **28. SuspensionHardSpan** (悬索式硬横跨) `RAILWAY/SuspensionHardSpan`
- [ ] **29. MastAssembly** (支柱装配) `RAILWAY/MastAssembly`

### Group D: Track Components (6 types)

- [ ] **30. Rail** (钢轨) `RAILWAY/Rail`
- [ ] **31. Sleeper** (轨枕) `RAILWAY/Sleeper`
- [ ] **32. Ballast** (道床) `RAILWAY/Ballast`
- [ ] **33. TrackSlab** (轨道板) `RAILWAY/TrackSlab`
- [ ] **34. Fastener** (扣件) `RAILWAY/Fastener`
- [ ] **35. GuardRail** (护轨) `RAILWAY/GuardRail`

### Group E: Turnout Components (6 types)

- [ ] **36. SwitchRail** (尖轨) `RAILWAY/SwitchRail`
- [ ] **37. Frog** (辙叉) `RAILWAY/Frog`
- [ ] **38. Turnout** (道岔) `RAILWAY/Turnout`
- [ ] **39. SleeperLayout** (轨枕阵列) `RAILWAY/SleeperLayout`
- [ ] **40. StraightTrack** (直线轨道段) `RAILWAY/StraightTrack`
- [ ] **41. CurveTrack** (曲线轨道段) `RAILWAY/CurveTrack`

### Group F: Point/Line API (5 types)

- [ ] **42. RailCurve** (钢轨曲线) `RAILWAY/RailCurve`
- [ ] **43. WingRailCurve** (翼轨曲线) `RAILWAY/WingRailCurve`
- [ ] **44. GuardRailCurve** (护轨曲线) `RAILWAY/GuardRailCurve`
- [ ] **45. SleeperLine** (枕木线) `RAILWAY/SleeperLine`
- [ ] **46. FastenerPoint** (扣件点) `RAILWAY/FastenerPoint`

### Group G: Special (6 types)

- [ ] **47. SuspensionCable** (悬索) `RAILWAY/SuspensionCable`
- [ ] **48. PositioningCable** (定位索) `RAILWAY/PositioningCable`
- [ ] **49. BallastFromSleepers** (枕木道床) `RAILWAY/BallastFromSleepers`
- [ ] **50. TurnoutAssembly** (道岔组合) `RAILWAY/TurnoutAssembly`
- [ ] **51. ExpansionJoint** (钢轨伸缩调节器) `RAILWAY/ExpansionJoint`
- [ ] **52. RetarderPoint** (减速顶) `RAILWAY/RetarderPoint`
- [ ] **53. RailPair** (轨排对) `RAILWAY/RailPair`
