# go-topo

Go bindings for a C++ 3D topological geometry modeling library (OpenCASCADE-based).

## Project structure

- Go package root: `package topo` — cgo wrappers calling C API layer
- C++ source: `src/` — compiled to `libtopo.a` via CMake
- Prebuilt libs: `libs/{darwin,darwin_arm,linux,linux_arm,windows}/`
- External C++ deps: `external/` (OpenCASCADE, Ipopt, Boost, Eigen, Freetype, Fontconfig, etc.)
- Go-only deps: `github.com/flywave/go3d`, `golang.org/x/image`

## Build

```sh
# Build C++ libs (Apple Silicon example)
cmake -S . -B build -G "Xcode"
cmake --build build --config Release

# Test Go package (requires prebuilt libs in libs/)
go test ./...
```

Go cgo link flags are in the `#cgo` directives of each `.go` file — they reference `./libs/<platform>/`.

## Local dev constraints

- `go.mod` has `replace` directives pointing to `../gltf` and `../go-mst` — those repos must exist as sibling directories
- Go tests require CGO and the prebuilt static libraries; they will fail without them
- After rebuilding the C++ libs, run `go clean -cache` before `go test` — the Go build cache does not notice external `.a` updates and will keep linking the stale archive
- On this machine, prefix cgo builds/tests with `CC=/usr/bin/clang CXX=/usr/bin/clang++` — an OpenHarmony clang earlier in PATH breaks the build
- Tests that read DXF/IFC STEP files may need fixture data not checked into this repo

## C++ primitives file layout

`primitives.cc` 已按专业拆分 (声明统一在 `primitives.hh` 单一入口, CMake GLOB 自动收集):

| 文件 | 职责 |
|------|------|
| `primitives_base.cc` | 基础: 基本几何体、型钢、垫片、通用采样与剖面/过渡辅助 |
| `primitives_substation.cc` | GIM 变电: 套管、支柱绝缘子、端子板、设备固定板 |
| `primitives_transmission.cc` | GIM 输电: 导线与弧垂、杆塔、绝缘子串、杆塔基础、锚具金具 |
| `primitives_cable.cc` | GIM 电缆工程: 电缆本体与附件、桥架、电缆沟、隧道、工井、排管、通风 |
| `primitives_water.cc` | 水利工程: 输水隧道、排水井、集水坑、钻孔 |
| `primitives_railway.cc` | 铁路 (OCS/轨道/道岔), 独立头文件 `primitives_railway.hh` |

新增跨专业使用的内部函数时, 声明加到 `primitives.hh` 末尾的"内部共享辅助函数"区。

## C++ rebuild

```sh
cmake -S . -B build -G "Xcode" && cmake --build build --config Release
cmake --install build --prefix libs/darwin_arm
```

## Key entrypoints

| File | Purpose |
|------|---------|
| `topo.go` | Core types (Shape, Location, constants) |
| `shape.go` | Shape methods |
| `shape_ops.go` | Boolean ops, extrude, sweep, loft, offset |
| `primitives.go` | Box, sphere, cylinder, prism creation |
| `primitives_railway.go` | Railway OCS & track primitives (50+ types) |
| `assembly_parametric.go` | Assembly parametric data (ParametricData, Export/RebuildFromParametric, builder registry) |
| `ocs_layout.go` | Anchor-section layout round-trip (ComputeAnchorSectionLayout / CreateAnchorSectionFromLayout) |
| `geometry.go` | Geometry type constants |
| `geometry_creator.go` | Curve/surface creation helpers |
| `dxf.go` / `ifc.go` | DXF/IFC import |
| `mesh.go` / `topo_export.go` | Mesh export via callback |
| `selector.go` / `workplane.go` / `sketch.go` | Higher-level modeling |

## Railway primitive porting

All 50+ railway types are being ported across 4 layers. See `RAILWAY_PORTING_PLAN.md`.

**Per-type workflow across 4 layers:**
1. 🔍 **Optimize C++ origin** (go-topo layer) — review origin/coordinate system
2. 📝 **Define parametric type** (topotypes layer) — Go struct + JSON tags + Unmarshal
3. 🏗️ **Write parametric builder** (flywave-topovis layer) — ParametricPrimitive -> CreateXxx
4. 🔧 **Write Embind binding** (topo.js layer) — C++→JS binding
5. 📝 **Update TS decls** (topo-wasm) — primitives.d.ts + export.json
6. 📦 **Write TS Object** (topo-primitives) — TypeScript wrapper class
7. ✅ **Build WASM + test** — make rebuild + vitest

## Tests

- `topo_test.go` — basic shape creation, wire ops, multi-segment pipe
- `shape_ops_test.go` — centerline fitting, wire sampling, shape outline, catenary
- `dxf_test.go`, `ifc_test.go` — DXF/IFC import (may require external fixture files)
- `track_geojson_test.go` — GeoJSON 中心线解析 + 正线生成
- `track_yard_test.go` — 站场生成 (道岔识别 / 菱形交叉)

Run: `go test -v -count=1 ./...`
Run one test: `go test -v -run TestSampleCenterlineWire ./...`

## GeoJSON 轨道输入 (track_geojson.go / track_yard.go / yard_layout.go)

- `ParseTrackGeoJSON` / `CreateTrackFromGeoJSON` — 单条中心线 (LineString/Feature/FeatureCollection) → 正线装配 (钢轨×2 + 轨枕 + 道床), 坐标默认米 (coordScale=1000)
- `CreateYardFromGeoJSON` — FeatureCollection 组网: 端点聚类节点 (50mm 容差) → 度=3 节点识别单开道岔 (自动判定开向/号数/裁剪邻边) → `CreateTurnoutWithPlace`; 边中部相交 → 菱形交叉 → `CreateFrogWithPlace`
- 站场布局闭环 (yard_layout.go): `ComputeYardLayout` 纯识别计算 → `YardLayout` (Tracks 原始中心线+TrimS/TrimE 裁剪弧长+Props / Turnouts 开向号数+CreateTurnoutWithPlace 全参 / Crossings, 全 JSON tag, `ToJSON`/`YardLayoutFromJSON`) 可存库/前端编辑校正 → `CreateYardFromLayout` 确定性再生成; `CreateYardFromGeoJSON` = Compute + FromLayout, `CreateYardFromGeoJSONWithLayout` 同时返回装配+布局; 子件命名 `rails_i`/`sleepers_i`/`turnout_i`/`crossing_i` 唯一, 全部经 `AddObjectParams` 挂配方 (type `yard_rails`/`yard_sleepers`/`yard_turnout`/`yard_crossing`, builder 已在 yard_layout.go init 注册), 支持 `ExportParametric`→`RebuildFromParametric` 往返
- 道岔号数估计: 侧股 15~35m 弦方向与主向夹角 → snap 到 {9,12,18,30,42}

## 接触网锚段生成 (ocs_anchor.go / ocs_layout.go)

- `CreateAnchorSection(AnchorSectionInput)` — 线路中心线 + 锚段规格 → 完整锚段装配: 支柱装配×N (`CalcOcsSpanPositions` 柱位, 端柱自动带补偿装置+拉线) + 跨间承力索(弛度 1.5%跨距) + 接触线(之字拉出值, 缺省 ±300) + 吊弦群 (间距 8m, 长度按两索抛物线求差)
- 布局闭环 (ocs_layout.go): `ComputeAnchorSectionLayout` 纯计算全部中间数据 → `AnchorSectionLayout` (Spec/Masts/Spans/Droppers, 全 JSON tag, `ToJSON`/`AnchorSectionLayoutFromJSON`) 可存库/前端编辑 → `CreateAnchorSectionFromLayout` 确定性再生成; `CreateAnchorSectionWithLayout` 同时返回装配+布局
- 装配结构: 根容器 "anchor_section", 子件唯一命名 `mast_i`/`cw_i`/`mw_i`/`dropper_{span}_{idx}`; 支柱局部生成 (原点=柱底中心, +X 朝线路) + Location 放置 (可 `SetLocation` 移动单柱), 线索/吊弦世界坐标烘焙; 所有子件经 `AddObjectParams` 挂配方 (type `ocs_mast`/`ocs_contact_wire`/`ocs_messenger_wire`/`ocs_dropper`, builder 已在 ocs_layout.go init 注册), 支持 `ExportParametric`→`RebuildFromParametric` 往返
- `CreateRatchetCompensator` / `CreateWeightStack` — 棘轮补偿装置 (轮盘+V形绳槽+减重孔+补偿绳+坠砣串)
- `CreateAuxiliaryWire` — 附加导线本体 (带弛度扫掠)
- `create_mast_assembly` 已按导高/结构高度/CX 尺寸链重构: 上下连接座→棒式绝缘子→平腕臂(仰角3°)→斜腕臂(三角桁架 65% 处对接)→承力索座→定位器(拉出值)

## C++ API nil-safety

The C API layer (`src/workplane_c_api.cc`) now handles `nullptr` for optional pointer parameters (those with C++ defaults). The Go wrapper forwards `nil` as `NULL`. Methods with "required" semantics still panic on `nil` — this is intentional.

## Turnout parametric design (道岔参量化)

### Core concept

Any turnout is a **centerline graph**. Each centerline offsets ±gauge/2 to generate two rails.
Rail topology at line junctions determines turnout type (switch, frog, guard rail).

### Data structures

```cpp
struct track_curve {                    // 中心线段
  centerline_curve_type type;           // LINE / ARC / BEZIER
  std::vector<gp_Pnt> points;
};

struct centerline_graph {               // 中心线图
  std::vector<track_curve> edges;       // 所有边

  struct node {
    gp_Pnt pt;
    std::vector<int> edge_ids;          // 关联的边索引
    bool is_crossing;                   // 两条贯穿线交叉 → 辙叉
    bool is_merge;                      // 一条终止于另一条 → 尖轨
  };
  std::vector<node> nodes;              // 由 edges 计算得出

  // 辙叉 — 两条贯穿中心线交叉处
  struct frog_site {
    int node_id; gp_Pnt pt; double angle;
    int edge_a, edge_b;
  };

  // 尖轨 — 一条中心线汇入另一条
  struct switch_site {
    int node_id; gp_Pnt pt;
    int merge_from, merge_into; double radius;
  };
};
```

### Algorithm

```
1. Build node graph from edges
   - Each edge start/end → node
   - Find intersections between edges → add crossing nodes

2. Classify nodes:
   - degree=3, 1 terminating edge → merge (switch rail)
   - degree=4, 4 through edges → crossing (frog + guard rail)
   - degree=2 or 1 → normal end/mid point

3. Generate rails:
   - Each edge → offset ±gauge/2 → two rails via create_rail_path
   - Merge: terminating edge's one rail → switch rail (tapered tip)
   - Crossing: two rail pairs cross → frog + guard rails

4. Generate sleepers + ballast
   - Sleepers along primary path, covering all rail width
   - Ballast via create_ballast along primary path
```

### API design

The `create_turnout` function will take the centerline graph + rail parameters:

```cpp
struct turnout_build_params {
  double gauge;                    // 轨距
  double railHeight;
  double railHeadWidth;
  double railBaseWidth;
  double webThickness;
  double sleeperLength;            // 枕木长度
  double sleeperSpacing;           // 枕木间距
  double ballastTopWidth;          // 道床顶宽
  double ballastThickness;         // 道床厚度
  double ballastSlope;             // 道床边坡
};

// 主入口: 从中心线图生成完整道岔
TopoDS_Shape create_turnout(const centerline_graph &graph,
                            const turnout_build_params &params);

// 内部辅助函数
centerline_graph build_centerline_graph(const std::vector<track_curve> &edges);
// 检测交点, 构建节点, 分类

// 偏移 gauge/2 生成左右钢轨路径
std::pair<std::vector<gp_Pnt>, std::vector<gp_Pnt>>
offset_path(const std::vector<gp_Pnt> &centerline, double halfGauge);
```

### Turnout types mapped to centerline graph

| Type | Edges | Nodes | Merges | Crossings |
|------|-------|-------|--------|-----------|
| 单开道岔 | 2 | 3 | 1 | 1 |
| 双开道岔 | 3 | 3 | 1 (1→2) | 2 |
| 三开道岔 | 4 | 4 | 1 (1→3) | 3 |
| 菱形交叉 | 2 | 1 | 0 | 1 (pure) |
| 复式交分 | 3 | 4 | 2 | 2 |
| 交叉渡线 | 6 | 8 | 2 | 3 |

### Switch rail (尖轨)

A rail that transitions from a normal rail profile (heel) to a thin tip.

**Geometry**: ThruSections loft through N sections, each section a rail profile scaled by `t = 0.05 → 1.0`. The heel matches `create_rail` profile; the tip is `~5%` scale (near-zero width + height).

**Placement**: Along the diverging track, between the stock rail junction and the frog. One edge terminates at another → the terminating edge's outer rail becomes the switch rail.

### Frog (辙叉)

Where two rail pairs cross. Construction:

```
      Wing Rail ───────────
  ──── Rail A ──┐     ┌── Rail A' ────
                │     │
                └──┬──┘     ← frog point (tip)
             ┌─────┴─────┐
  ──── Rail B ─┘         └── Rail B' ────
      Wing Rail ───────────
```

1. **Point rails**: Rail A and Rail B converge to a common point (frog tip, ~2mm wide), forming a V shape. Rail A' and Rail B' diverge from the same point.
2. **Wing rails**: Two additional rails outside the point rails, running parallel through the frog crossing. They guide the wheel across the gap in the point rails.
3. **Guard rails**: On the opposite track from the frog, short straight rails at gauge−42mm to prevent wheel flange strikes.

**Lofting approach**: 
- Bottom profile: trapezoidal base (full base width at heel, tapering to tip)
- Top profile: near-zero rectangle at the tip
- ThruSections transitions from full rail profile → tip → full rail profile

### Guard rail (护轨)

Short rail installed inside the opposite track at a frog crossing, preventing wheel flange strikes.

**Position**: On the opposite rail from the frog point, at `gauge − 42mm` from the running rail (standard Chinese railway: 42mm flange groove width).

**Geometry**: 
- Same profile as stock rail (`create_rail` profile)  
- Short straight segment (~3-6m)
- Placed via `create_rail_path` with LINE path
- Overlaps the frog crossing zone

### Turnout generation algorithm

**Input**: `centerline_graph` (edges + gauge + rail profile + sleeper/ballast params)

**Steps**:

```
1. 构建节点图
    for each edge:
      add start_point, end_point as nodes
    for each pair of edges:
      find intersection → add crossing node

2. 分类节点
    每个节点检查连接的边:
      - 边起点=节点 → "从此出发"
      - 边终点=节点 → "在此终止"  
      - 边贯穿节点(起点≠节点且终点≠节点) → "经过"
    
    统计:
      terminating = 在此终止的边数
      through     = 经过的边数
      
    分类:
      terminating == 0 && through == 2 → 普通中间点
      terminating == 1 && through == 0 → 端点
      terminating == 1 && through == 2 → merge (尖轨)
      terminating == 0 && through == 4 → crossing (辙叉)

3. 生成钢轨
   每条 edge 生成左右两条钢轨路径 (offset ±gauge/2)
   沿每条路径:
     - 路径起始/终止于 merge 节点 → 对应位置用 create_switch_rail
     - 路径经过 crossing 节点 → 在辙叉处截断, 断口两侧加翼轨
     - 其他 → create_rail_path

4. 生成辙叉 (crossing node)
    输入: 两条贯穿边 edge_a, edge_b
    1. 找到交叉点 P
    2. 心轨: 两条钢轨各从全剖面逐渐缩小到~2mm 尖端
       - Rail_A 从 edge_a 入口侧 → 尖端 P
       - Rail_B 从 edge_b 入口侧 → 尖端 P
       - Rail_A' 从尖端 P → edge_a 出口侧
       - Rail_B' 从尖端 P → edge_b 出口侧
    3. 翼轨: 在心轨外侧, 从入口到出口贯通
    4. 护轨: 对侧 track 上, 距基本轨 gauge-42mm, 短直段

5. 生成尖轨 (merge node)
    输入: 终止边 merge_from, 目标边 merge_into
    1. 确定 merge side: merge_from 的哪一侧轨汇入 merge_into
    2. 该侧钢轨 → create_switch_rail (全剖面→5% 尖端)
    3. 对侧钢轨 → 保持直轨 (stock rail)

6. 生成枕木 + 道床
    主路径 = 最长贯穿路径
    沿主路径均匀布置枕木, 覆盖所有钢轨宽度
    沿主路径生成道床

```
Input: centerline_graph (edges + nodes)

1. Build node graph from edges
   - Each edge start/end → node
   - Find intersections between edges → add crossing nodes

2. Classify nodes:
   - degree=3, 1 terminating edge → merge (switch rail)
   - degree=4, 4 through edges → crossing (frog + guard rail)
   - degree=2 or 1 → normal end/mid point

3. Generate rails:
   For each edge:
     - Offset ±gauge/2 → left_rail_path, right_rail_path
     - For each offset path:
       - If path segment leads to a merge node and is the INNER side:
         → create_switch_rail (full profile → tapered tip)
       - If path segment passes through a crossing node:
         → rail is interrupted at frog, continues on other side
       - Otherwise:
         → create_rail_path (normal rail)

4. Generate frog at crossing nodes:
   - Two through edges intersect → find intersection point
   - Create frog body:
     a. Point rail A: full profile → tip (~2mm) (incoming)
     b. Point rail A': tip → full profile (outgoing)
     c. Point rail B: full profile → tip (incoming)
     d. Point rail B': tip → full profile (outgoing)
     e. Wing rails: outside both sides, running full frog length
   - Place guard rails on opposite tracks at gauge−42mm

5. Generate switch rails at merge nodes:
   - Find the terminating edge
   - The rail on the MERGE SIDE (inner) becomes a switch rail
   - The rail on the OPPOSITE SIDE stays as stock rail (straight)
   - Switch rail: ThruSections from tip (5% scale) → full profile at heel

6. Generate sleepers + ballast:
   - Primary path = longest through route
   - Sleepers along primary path, covering all rail width
   - Ballast via create_ballast along primary path
```

### Implementation status

- `create_rail_path` — unified rail generation (LINE→prism, ARC/BEZIER→loft), 真实钢轨断面 (R300 踏面 + R80 侧面 + R13 圆角过渡)
- `create_rail` — 真实断面拉伸; `standard_rail_params` 提供 43/50/60/75kg 查表
- `create_ballast` — 沿完整中心线 (LINE/ARC/BEZIER 多段, 支持坡度) ThruSections 放样梯形断面, 顶面与中心线齐平, 两端沿切向外延 500mm, tiltAngle 超高倾角生效 (绕切向旋转断面); `create_straight_track`/`create_curve_track` 均经此生成道床 (curve_track 超高 → tilt = -sign(sweep)·atan(se/gauge))
- `create_crossing` — 线岔: 交角由 mainDir/branchDir 实算, 限制管横跨两接触线交叉点上方, 两端线夹固定 (线夹距交叉点 s = L/(2·sin(α/2)))
- 格构式钢柱主肢为等边角钢 L 断面放样 (`makeAngleSteelProfile`, 角跟朝外), 不再是圆管
- `create_sleeper` — TRAPEZOIDAL concrete sleeper with rail seats
- `create_turnout` — currently hard-coded for 单开道岔, to be refactored to centerline_graph interface; sleeperSpacing 已生效, frogLength 为 reserved 字段暂未生效
- `CreatePositioningCableWithPlace` / `CreateStraightTrackWithPlace` / `CreateCurveTrackWithPlace` — 几何端点/圆心从 params 移出作显式函数参数 (params 内对应字段已标 Deprecated)
- `create_anchor_fitting` — 三种类型原点统一为连接点; ratchet/pulley with_place 的 wheelAxis、head_span 左端绝缘子方向、sleeper_line TRAPEZOIDAL 端点放置已修复; frog/turnout 等静默 catch 改为 `warn_part_failed` 日志
- `create_switch_rail` — 单侧刨削渐缩 (锚定基本轨侧边缘), 尖端降值, 支持曲线半径
- `create_frog` — 4 段心轨 SWITCH 端刨削汇聚 ~2mm 岔心 + 真实线形翼轨×2 (开口→咽喉→平直→绕岔心, 普通钢轨断面) + 43kg 旧钢轨护轨×2 (端部弯折张开喇叭口) (待按 centerline_graph 重构布局)
- `applyEndTreatment` — PLANE/SCARF(斜切切割)/SWITCH(单侧刨削楔切+降值) 已实现; BELL 由 addBellMouth 放样喇叭口
