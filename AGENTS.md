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
cmake -S . -B build/build -G "Xcode"
cmake --build build/build --config Release

# Test Go package (requires prebuilt libs in libs/)
go test ./...
```

Go cgo link flags are in the `#cgo` directives of each `.go` file — they reference `./libs/<platform>/`.

## Local dev constraints

- `go.mod` has `replace` directives pointing to `../gltf` and `../go-mst` — those repos must exist as sibling directories
- Go tests require CGO and the prebuilt static libraries; they will fail without them
- Tests that read DXF/IFC STEP files may need fixture data not checked into this repo

## C++ rebuild

```sh
cmake -S . -B build/build -G "Xcode" && cmake --build build/build --config Release
cmake --install build/build --prefix libs/darwin_arm
```

## Key entrypoints

| File | Purpose |
|------|---------|
| `topo.go` | Core types (Shape, Location, constants) |
| `shape.go` | Shape methods |
| `shape_ops.go` | Boolean ops, extrude, sweep, loft, offset |
| `primitives.go` | Box, sphere, cylinder, prism creation |
| `primitives_railway.go` | Railway OCS & track primitives (30 types) |
| `geometry.go` | Geometry type constants |
| `geometry_creator.go` | Curve/surface creation helpers |
| `dxf.go` / `ifc.go` | DXF/IFC import |
| `mesh.go` / `topo_export.go` | Mesh export via callback |
| `selector.go` / `workplane.go` / `sketch.go` | Higher-level modeling |

## Key entrypoints

| File | Purpose |
|------|---------|
| `topo.go` | Core types (Shape, Location, constants) |
| `shape.go` | Shape methods |
| `shape_ops.go` | Boolean ops, extrude, sweep, loft, offset |
| `primitives.go` | Box, sphere, cylinder, prism creation |
| `geometry.go` | Geometry type constants |
| `geometry_creator.go` | Curve/surface creation helpers |
| `dxf.go` / `ifc.go` | DXF/IFC import |
| `mesh.go` / `topo_export.go` | Mesh export via callback |
| `selector.go` / `workplane.go` / `sketch.go` | Higher-level modeling |

## Tests

- `topo_test.go` — basic shape creation, wire ops, multi-segment pipe
- `shape_ops_test.go` — centerline fitting, wire sampling, shape outline, catenary
- `dxf_test.go`, `ifc_test.go` — DXF/IFC import (may require external fixture files)

Run: `go test -v -count=1 ./...`
Run one test: `go test -v -run TestSampleCenterlineWire ./...`

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

- `create_rail_path` — unified rail generation (LINE→prism, ARC/BEZIER→loft)
- `create_ballast` — loft-based ballast with optional tiltAngle
- `create_sleeper` — TRAPEZOIDAL concrete sleeper with rail seats
- `create_turnout` — currently hard-coded for 单开道岔, to be refactored to centerline_graph interface
- `create_switch_rail` — exists, hard-coded taper without centerline alignment
- `create_frog` — exists, uses simplified box geometry; needs redesign to match centerline graph approach
