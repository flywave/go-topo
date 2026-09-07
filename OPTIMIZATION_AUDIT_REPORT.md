# go-topo 全面审计报告

> 审计范围:C++ 封装层(`src/`,约 10.4 万行)、Go cgo 绑定层、Go 上层建模代码(合计约 3 万行,不含测试)。
> 审计维度:防御式编程(参数校验)、Bug、内存问题、性能问题。
> 所有 P0 级发现均已人工二次核实源码确认。

## 总体统计

| 层 | 高危 | 中危 | 低危 | 小计 |
|---|---|---|---|---|
| C API 边界层 (`src/*_c_api.cc`) | 24 | 26 | 7 | 57 |
| C++ 核心实现 (`src/*.cc` 非边界) | 10 | 19 | 10 | 39 |
| Go cgo 绑定层 (`*.go` 基础类型) | 7 | 14 | 8 | 29 |
| Go 上层 (primitives/ocs/yard/workplane 等) | 17 | 14 | 13 | 44 |
| **合计** | **58** | **73** | **38** | **169** |

**四类系统性 root cause**(修复策略应针对模式而非逐条打补丁):

1. **异常安全覆盖不均**:C ABI 边界约 1200+ 导出函数中,`assembly_c_api.cc`(24 个)、`dxf_c_api.cc`(23 个)、`geometry_c_api.cc`(~150 个)、`plate_plate_c_api.cc`(31 个)为 0% try/catch 覆盖,`ifc_c_api.cc` ≈1%,`topo_c_api.cc` ≈60%(make_solid/shell/face 全家族裸奔)。任何 OCC 异常逃逸 C ABI 直接 terminate。
2. **内存所有权契约缺失**:11 个 C API 头文件几乎零所有权注释;`*_list_free` 逐元素 delete 的语义与 Go 侧"再包 finalizer"的模式系统性冲突(见 P0-2/3);`new[]` 与 `C.free`/`malloc`/`delete` 混用。
3. **参数校验风格完全不一致**:同类 API 有的判空、有的 panic、有的直通 C;空切片 `&s[0]` panic 族遍布 Go 侧;C 侧 `指针+长度` 对基本不校验。
4. **静默失败**:布尔运算不查 `IsDone()`(shape_ops.cc:184-288),失败 shape 静默传播;DXF/IFC/shell 大量 `catch(...) {}` 吞错。

---

## P0:必崩 / UB / 结果错误(已逐一核实,应最先修复)

### A. Go 侧 use-after-free / double-free(高频调用路径)

| # | 位置 | 问题 |
|---|---|---|
| 1 | `workplane.go:1528/1546/1564` | `All()/Shapes()/Vals()`:`defer C.workplane_list_free(...)`(C 侧逐元素 delete,src/workplane_c_api.cc:1371-1406)后又给同批元素挂 Go finalizer → **double free**;且 defer 在返回前已释放,调用方使用即 **UAF**。三个都是高频 API |
| 2 | `edge.go:580/605`、`wire.go:495` | `Edge/Wire.Locations()`、`Edge.Projected()`:同样模式,C 侧 `topo_location_list_free`/`topo_shape_list_free`(topo_c_api.cc:1225/5253)已逐元素 delete,Go 再挂 finalizer → double free |
| 3 | `wire.go:517` | `Wire.Projected()`:反方向错误——defer 已释放全部元素,返回的 `*Shape` 无 finalizer 无拷贝 → 调用方 UAF。与 Edge.Projected 是同一 API 两种错误写法 |

**修法**:列表类返回统一改为"Go 接管元素所有权,只 free 数组本身"(或 C 侧提供只 free 外层数组的函数),全库统一一种契约。

### B. SetFinalizer 类型不匹配(调用即 panic,Go runtime 立即 throw)

| # | 位置 | 问题 |
|---|---|---|
| 4 | `wire.go:174` | `Wire.GetLocation()` 挂 `(*innerShape).free` 到 `*innerTopoLocation` → **每次调用必 panic** |
| 5 | `workplane.go:867/887/894/903/992` | `Each/EachPoint/EachPointWithLocation/CutEach` 回调内同样错配 → 触发即 panic |
| 6 | `plate_plate.go:446` | `NewLinearScalarConstraintDim2` 挂 `(*innerGlobalTranslationConstraint).free`(copy-paste 错误)→ 调用即 panic |

### C. C++ 侧崩溃 / UB

| # | 位置 | 问题 |
|---|---|---|
| 7 | `src/topo_c_api.cc:4657` | `reinterpret_cast<flywave::topo::solid*>(s.shp)->sweep(...)`:把 shared_ptr 成员地址重解释为对象调虚函数,**调用即崩**。兄弟函数均用 `cast_to_topo(s)` |
| 8 | `src/plate_plate_c_api.cc:116-187` | OCC `Plate_Array1OfPinpointConstraint cons(n, n)` 把 (lower,upper) 传成 (count,count) → 1 元素数组 + SetValue 循环 → 必抛 `Standard_OutOfRange`,且全文件 0 try/catch → **任何非空输入必崩**。5 个约束构造函数全中 |
| 9 | `src/assembly.cc:792/822` | `assembly::solve` 对 `unordered_map::find` 结果不判 `end()` 即解引用,约束引用未知名字即 UB |
| 10 | `src/ifc_c_api.cc:652-656/709-713` | `boost::to_block_range` 按 64 位 block 写入 `(size+7)/8` 字节小缓冲 → **堆越界写**;`:723-749` 锯齿矩阵按第 0 行列数 copy → 堆溢出 |
| 11 | `src/ifc_c_api.cc:1598-1633` | `malloc` 未构造内存上直接对含 `std::string` 成员的 struct 赋值(UB)+ free 函数不释放元素(泄漏)+ `malloc`/`delete` 配对错乱,三重叠加 |
| 12 | `src/ifc.cc:131-137` | `get_version()` 声明返回 `std::string` 却 `return nullptr;` → `std::string(const char*)` 收 null 是 UB |

### D. 静默错误结果(不崩但错)

| # | 位置 | 问题 |
|---|---|---|
| 13 | `standard.go:1005-1007` | `NewColorFromByte` 用 `c[0]/255` 整数除法 → 除 255 外所有分量变 0,**所有字节颜色静默变黑** |
| 14 | `src/topo_c_api.cc:5086-5118` | `topo_compound_cut/fuse/intersect` 根本没执行布尔运算,只是把操作数重新 make_compound(`t` 被完全忽略)→ API 假成功 |
| 15 | 8 个文件 | `GetCurveColour` 全部复制粘贴成调用 `topo_shape_get_surface_colour`(如 shape.go:285)→ 曲线颜色 API 永远返回表面颜色 |
| 16 | `wire.go:317` | `Wire.Length()` 把 C 的 double 返回截断成 `int` |
| 17 | `primitives_railway.go:2045-2046` | `DetectTrackSegments` 最后一段 `make([]Point3, e-s+2)` + `min(e+2,len)` 拷贝 → 尾部残留 (0,0,0) 垃圾点,长度虚增 |
| 18 | `primitives_railway.go:1996-1999` | 三点圆拟合 `k1=(x2-x1)/(y1-y2)` 水平弦除零 → NaN 曲率,直线/曲线误判(GeoJSON 线路极常见水平段) |
| 19 | `src/primitives_railway.cc:3705 vs 3648` | `create_rail_path` 直线快路径 `DZ×t` 与放样路径 `t×DZ` 横向偏移**方向相反**,且快路径丢弃 tiltAngle(超高)→ 两点直线与多段折线生成的左右股互换 |
| 20 | `primitives.go:943-948` | `CurveCableParams.to_struct` 按 `len(CurveTypes)` malloc、按 `len(Segments)` 写入 → 不等长时 **C 堆越界写** |

### E. 高危泄漏

| # | 位置 | 问题 |
|---|---|---|
| 21 | `solid.go:629-642` | `Solid.Chamfer()` malloc 的 `cEdges` 永不释放(对比 Fillet 正确) |
| 22 | `wire.go:703-724` | `TopoMakeWireFromCombineCurve` 每条曲线的点数组永不释放 |
| 23 | `src/topo_c_api.cc:6011-6031` | `read_shapes_from_step_file` 元素(各含 2 个 new)永不释放,`free_shapes_from_step` 只 free 数组 |
| 24 | `src/assembly_c_api.cc:208-217` | `assembly_shapes` 返回 `new topo_shape_t*[n]`,全库无对应 free 函数 → 无论 Go 怎么写都泄漏 |
| 25 | `src/dxf_c_api.cc:292-314` | 写 DXF 循环内每次 `new` entity 从不 delete |
| 26 | `primitives.go:2042-2048`、`:452-472` | `CreateTransmissionCenterline` 的 CString、`StretchedBodyParams` 的 points 缓冲均无 free(同类函数有,漏网) |

---

## P1:边界/防御/正确性风险(按层)

### C API 边界层(src/*_c_api.cc)

- **异常逃逸**:`geometry_c_api.cc`(全文件 0 try)、`assembly_c_api.cc`(0)、`dxf_c_api.cc`(0)、`plate_plate_c_api.cc`(0)、`ifc_c_api.cc`(1 处);`topo_c_api.cc` 的 face make 家族(:2727-2934)、solid make 家族(:3916-4357)、shell make 家族(:3485-3875)、fillet/chamfer(:4713-4802)均无 try;`standard_c_api.cc:315-318/826-833` 3 个函数漏网。
- **BSpline 构造族数组边界系统性写错**:`geometry_c_api.cc:2766-2902` 多处 `{0, count}` 声明 count+1 个元素、末元素未初始化;`:2850-2856` bspline surface 的 `{0,col,0,row}` 与 `Poles[i*col+j]` 行主序不匹配。
- **越界读**:`primitives_c_api.cc:6137-6148` `convert_layers` 外层用 `j`、switch 里读 `profiles[i]`(i/j 错用)。
- **cast_to_topo 失败即解引用**:`topo_c_api.cc` 大量 `*cast_to_topo(V1)`(dynamic_cast 失败返回 null 后直接 `*`),如 :543/572/2742/4719;`:2152-2158` 同;`:3114-3120 to_plane` cast 失败路径无 return。
- **wrapper 类型错装**:`topo_c_api.cc:3341/3357/3417/3449` face_t/edge_t/wire_t 里装 `make_shared<shell>` → 句柄看似有效实则不可用。
- **out 参数不判空**:`*count`/`*min`/`*max` 写入前不检查,遍历遍布 topo/dxf/ifc/workplane/primitives。
- **数组边界**:`dxf_c_api.cc:154` `aci_table[index]` 无 0-255 校验;`:133` 实体索引无上界检查;`ifc_c_api.cc:127` 三角剖分数组无 null 终结符而兄弟接口有(契约不一致)。
- **悬垂返回**:`*_get_name/_error` 返回内部 `c_str()`,头文件未注明有效期。
- 整数除法:`dxf_c_api.cc:158` `rgb.second.r / 255`(恒 0/1,应 /255.0)。

### C++ 核心层(src/*.cc)

- **参数校验缺失**:`create_rail_path`(:3674)零长度线段 null Handle 直接解引用;BEZIER 弦长 0 → 除零 NaN(:3692/3859);`create_straight/curve_track`(:4920/4989)`sleeperSpacing<=0` 时 `(int)inf` UB,极小间距 → 数亿次枕木循环假死;`calculate_frog_params`(:4774)对 turnoutNo/gauge 零值不设防;`create_turnout`(:4715) `asin(swLen/Ri)` 参数无界 → NaN;`create_mast_assembly`(:4039) armLen≤0 时错误信息与真实原因脱节;螺旋挤出 pitch 除零(shape_ops.cc:1309、solid.cc:953);`combined_center` 零质量除零(primitives.cc:1343)。
- **静默失败**:`shape_ops.cc:184-288` fuse/cut/intersect 不查 `IsDone()`,失败 shape 静默返回;叠加 `workplane.cc:2307/2317/2339/2391`、`assembly.cc:128/135` 裸解引用 `boost::optional` → none 时 UB。`shell.cc` 约 20 处 `catch(...) { return shell{}; }`;`dxf_shape.cc:394-475` 实体读取吞错;`wire_length` 失败返回 0.0 伪装零长。
- **内存/线程**:`mesh.cc:365/398` `static int depth` 递归计数(非线程安全、无深度上限);`bounding_pipe.cc:179` 对调用方 shape 就地网格化(副作用 + 0.1 固定偏差内存无界)。
- **逻辑**:`catenary.hh:337` `makeCatenary` 缺垂直线防护(姊妹函数有);`:23` solveBisect 端点同号静默返回错值;`bounding_pipe.cc:138`/`shape_ops.cc:1614` 弧长→参数线性换算对 B 样条系统性偏移。

### Go cgo 绑定层

- **Go 指针存入 C**:`mesh.go:33-40` 把含 Go slice 的 `*MeshReceiver` 指针存入 C 长期持有的回调结构(违反 cgo 指针规则,GC 不扫描 C 内存)。
- **new[] / C.free 失配(UB)**:edge.go:524、wire.go:455、face.go:640/665、solid.go:347 —— C 侧 `new[]` 分配,Go 侧 `C.free`(malloc)释放。
- **LocationAt 泄漏**:edge.go:544、wire.go:475 返回的 TopoLocation 无 finalizer(C 侧每次 new)。
- **GoString(nil)**:ifc.go:73 `GetVersion`、dxf.go:50 `GetError` 对 C 返回的 nullptr 直接 `C.GoString` → 段错误。
- **空切片 `&s[0]` panic 族**:wire.go:379/387/403/435/540/628/638/673、compound.go:456/466、compsolid.go:484/494、face.go、sketch.go:190/347/510/529/540/596、workplane.go:971/1234/1249/1260/1449/1474、primitives.go:1027/5181、primitives_railway.go:1275/2420/2442、plate_plate.go:437/445/468(而 edge.go/solid.go 同类函数有守卫——不一致)。
- **错误码丢弃**:7 个类型的 `Mesh/MeshWithTexture` 丢弃 int 错误码(edge.go:194 等);`ifc_mst.go:16/470` 忽略 `Load()` 返回值。
- **组合 Selector 悬挂**:selector.go:88-107 Go 侧不保持 left/right 引用,可先被 GC → finalizer 释放仍在用的 C 对象。

### Go 上层

- **零值参数直通 C**:`CreateMastAssembly` 无 `withDefaults`(primitives_railway.go:1785,对比同类函数都有)→ RebuildFromParametric 拿到残缺 JSON 时 mastHeight=0 直通 C;`CreateStraightTrack` 零值起终点不校验;`CalcTurnoutSegment` turnoutNo=0 不报错。
- **JSON 往返丢数据(高)**:`Point3/Dir3` 字段为非导出 C struct,`json.Marshal` 产出 `{}`,但 `TrackSegment.Points`、`TurnoutSegment.Position/MainDirection/BranchDirection`、`OcsSpanInput.Centerline`、`StraightTrackParams.Start/EndPoint` 等带 json tag 的结构直接内嵌 → 序列化 `{}`,反序列化回 (0,0,0)。测试只断言 key 存在所以没发现。`AnchorSectionSpec` 用 `[][3]float64` 是正确范例,同域两套表示。
- **往返不对称**:`yard_layout.go:417` 创建路径对零 mainDir 报错,`:586` 重建路径静默回退 {1,0,0};`ocs_layout.go:324` 布局 JSON 中编辑过的吊弦 Top/Bottom/Length 被忽略。
- **配方按 name 覆盖**:assembly.go:193 重名子件配方互相覆盖,`childParametrics` map 未拷贝导致共享。
- **OCS 跨距膨胀**:primitives_railway.go:2251 `MastCount=total/span+1` 可使实际跨距近 2 倍标准跨距,与 ocs_layout.go 弛度/吊弦计算不一致;末尾短跨仍用标准跨距弛度(ocs_layout.go:194-204)→ 吊弦长度错误。
- **plate_plate.go:440-444** `Dim2` 版按 `coffes[j][i]` 转置填充(Dim2XYZ 版是 `coffes[i][j]`),疑似 copy-paste 错误且无行长校验。
- **CString/缓冲泄漏**(见 P0-E #26)。

---

## P2:性能问题(按影响排序)

| # | 位置 | 问题 | 影响 |
|---|---|---|---|
| 1 | `src/primitives_railway.cc:5310-5326` | `sweepProfile` 30mm 一段逐段 prism + 两两 Fuse 拼曲线扫掠;25m 护轨 ≈ 833 次串联布尔,1km ≈ 33000 次 → 实际挂死 | 护轨/翼轨 PLATE 路径不可用 |
| 2 | `src/primitives_railway.cc:3725/3868` | 钢轨/道床放样按固定 500mm 截面距无上限:1km=2000 截面 ThruSections(每截面完整断面 Transform),复杂度超线性 | 长中心线不可用 |
| 3 | `src/primitives_railway.cc:4920/4989` | `len/sleeperSpacing` 无下界:spacing=1e-6 → 数亿次枕木循环(每次含布尔) | 输入异常即假死 |
| 4 | `bounding_pipe.cc:307-412` + `:179` | 固定 0.1 偏差网格(数十万-百万三角形常驻)+ O(seg×points) 全量扫描 + 每步线性最近点 | 大装配内存/耗时爆炸 |
| 5 | `shape_ops.cc:1593-1626`、`primitives.cc:14942/14998` | 每个采样距离从头遍历 wire + 重算 LinearProperties,O(d×e) | 长线索采样慢 |
| 6 | `primitives_railway.go:2258-2285` | `CalcOcsSpanPositions` 每柱从头扫中心线找里程,O(M·N) | 长线路慢 |
| 7 | `yard_layout.go:262-314` | 菱形交叉检测 O(E²·S²) 四重循环 + 内层线性去重 | 站场边多时慢 |
| 8 | `topo_export.go:16-48`、`mesh.go:66-85` | 每顶点/每三角形一次 cgo 回调 + append 无预分配 | 大网格导出慢 |
| 9 | `edge.go:356-656` vs `wire.go:370-543` | 同类 API 两种传输模式并存,edge 侧多两次全量拷贝 | 不一致 + 浪费 |
| 10 | `shape_ops.cc:1348`、`primitives.cc:6010`、`mst.go:30` | compute_mass 每对象算两次 / 斜材截面重复构造 / texture 循环内重建 | 常数放大 |

---

## 修复优先级建议

**第一批(止血,1-2 天量级,均为局部小改)**:
1. P0-A #1/#2/#3:统一列表所有权契约(Go 接管元素、只 free 数组;C 侧补 `*_list_free_shallow` 或文档化)。
2. P0-B #4/#5/#6:修正 finalizer 类型(纯笔误级)。
3. P0-C #7 (cast_to_topo)、#8 (plate 数组 (0,n-1))、#12 (string 返回)、#14 (compound 布尔——若暂不实现应显式返回错误码)。
4. P0-D #13 (颜色 /255.0)、#15 (GetCurveColour 调对函数)、#16 (Length 返回 float64)、#20 (malloc 长度断言)。
5. P0-E 各泄漏补 free/finalizer。

**第二批(防御层系统性加固)**:
1. C API:给 assembly/dxf/geometry/plate_plate/ifc 5 个裸奔文件加统一 try/catch 包裹宏;补齐 out 参数与指针+长度校验;`cast_to_topo` 失败统一返回错误而非解引用。
2. Go 侧:统一空切片守卫(一个 `firstPtr[T](s []T) unsafe.Pointer` 帮助函数即可消除全部 `&s[0]` panic);统一 nil 接收器检查;`C.GoString` 前判 nil。
3. 上层:Create* 参数校验前置(NaN/零/负、空切片);`Point3` JSON 序列化改 `[][3]float64` 或实现 MarshalJSON;`CreateMastAssembly` 补 withDefaults。
4. `DetectTrackSegments` 修补点 + 圆拟合垂直弦防护;`create_rail_path` 统一快慢路径方向约定与 tilt。

**第三批(性能与静默失败)**:
1. `sweepProfile` 改单次 `BRepOffsetAPI_MakePipeShell`(或 ThruSections)替代 Fuse 链;放样截面数设上限并自适应。
2. sleeperSpacing/几何参数下界校验集中到 C 侧公共入口。
3. fuse/cut/intersect 统一查 `IsDone()/HasErrors()` 并通过现有 error 通道上抛;消灭 `catch(...) {}` 静默吞错(改 warn_part_failed 模式,AGENTS.md 已有先例)。
4. 网格导出改批量传输(一次性 C 数组 ↔ Go slice)替代逐元素回调。

## 审计方法说明

- 4 路并行深度分析(C API 边界 / C++ 核心 / cgo 层 / Go 上层),共 250+ 次文件抽查;
- P0 级 26 条全部经人工二次读源码核实(含 C 侧 `list_free` 实现、compound 空操作、plate 数组构造等);
- P1/P2 级发现均有 file:line 证据,个别(如 agent 标注"约"的行号)修复时需现场确认。


---

# 修复实施记录 (2026-09-07)

## 已完成 (P0 全部 + P1/P2 大部分)

### P0 止血 (26/26 条全部落实, 含 2 条审计误报的甄别)

**A. Go 列表返回 UAF/double-free** — 统一所有权契约: C 侧 `topo_shape_list_free` / `topo_location_list_free` / `workplane_list_free` / `shape_list_free` / `shape_objects_free` 全部改为浅释放 (仅 delete[] 数组, src/topo_c_api.cc, src/workplane_c_api.cc), 头文件注明契约 (src+libs 同步); `Wire.Projected` 补挂 finalizer。

**B. SetFinalizer 类型错配** — workplane.go eachFunc/EachPointWithShape/EachPointWithWorkplane/eachFuncWithLocation/cutEachFunc, wire.go GetLocation, plate_plate.go Dim2 全部修正 (Dim2 顺带修复 coffes[j][i] 转置 copy-paste 错误并补空守卫)。

**C. C++ 崩溃/UB** —
- `topo_solid_sweep_compound` reinterpret_cast → `cast_to_topo` + 判空;
- plate_plate_c_api.cc 全部 OCC 数组 `(n,n)` → `(1,n)` + SetValue i+1 + 空守卫;
- `assembly::solve` map find 判 end() (缺失名字抛带名字的异常);
- ifc_c_api.cc bitset 按 block 对齐分配 (修堆越界写), 矩阵拒绝锯齿输入, `::operator delete[]` 统一释放 (修跨类型 delete[] UB), time_period/work_time 的 malloc → new (struct 含 C++ 对象), free_time_periods 改浅释放与 Go finalizer 契约一致;
- ifc.cc `return nullptr` → `return std::string()`;
- **审计误报甄别**: `free_shapes_from_step` 原实现是正确的 (Go finalizer 持有元素所有权), 未按审计建议改深释放 (会 double free), 仅补契约注释。

**D. 静默错误结果** —
- `NewColorFromByte` 整数除法 → float64/255.0;
- `topo_compound_cut/fuse/intersect` 空操作 → 调用 compound 类真实的布尔方法;
- GetCurveColour ×8 文件 → 调 `topo_shape_get_curve_colour`;
- `Wire.Length()` int 截断 → float64;
- `DetectTrackSegments` 尾零点切片 + 三点圆拟合除零 → 精确切片 + 外接圆心公式;
- `create_rail_path` 直线快路径与放样路径偏移方向相反/丢弃超高 → 统一 Hd/Vd 坐标架 + tilt, 并补 LINE 零长度/退化总长防护;
- `CurveCableParams.to_struct` 堆越界写 → 按 Segments 分配 + 长度防御;
- plate `free_g_to_c_constraint_new_3` D3S/D3T 复制粘贴错误修正。

**E. 泄漏** — solid.go Chamfer, wire.go combine-curve 点数组, assembly.go Shapes/Children (新增 C `assembly_list_free_shallow`), dxf 写出 entity 循环, CreateTransmissionCenterline CString, StretchedBodyParams points 缓冲; 新增 C `topo_free_array` 修复 5 处 `new[]`/`C.free` 分配器失配 UB。

### P1 防御加固 (系统性)

- **C ABI 异常安全全覆盖**: 12 个 C API 文件全部处理, 括号配对脚本统一包装 ~980 个无保护函数 (assembly/dxf/ifc/geometry/plate_plate 由 0% → 全覆盖; topo/workplane/sketch/standard/primitives(_railway)/selector 补齐遗漏; 已有 try/SAFE_CALL 的跳过);
- **workplane `safe_call` 出错返回空 shared_ptr 的致命缺陷** (测试崩溃确定性根因, 审计未列) → 出错返回 `shared_from_this()`, 错误经 has_error 传播;
- **workplane/assembly 31 处 `*topo::X(...)` 裸解引用 boost::optional** (审计 P1) → `topo::checked(opt, name)` 统一抛错;
- **selector 回调 use-after-free** (审计未列): C 侧在读取 Go 回调返回值之前就 delete 了输入 wrapper, 透传时 rets 与输入别名 → 读后删 + rets 判空。**这是堆破坏并引爆 Ipopt/edge_free 间歇 SIGABRT 的来源之一**;
- **sketch::solve 三重修复** (审计未列): e2i[tag] 静默插 0 → find+跳过; 空实体越界 SEGV → 提前返回; boost::combine(向量, 哈希表) 顺序错乱 → 顺序表回写;
- **convert_layers i/j 错用** (primitives_c_api.cc, 审计项) → 统一用 j, 修好基线必败的 TestCreateMultiLayerExtrusionStructure;
- Go 侧: 回调注册表 (`cgo_callback.go`) 修复 19 处 "Go 指针指向含 Go 指针内存" 的 cgo 规则违反 (TestSketchEach/FilterMap panic 根因, 审计未列); 空切片守卫 ~30 处 (sketch/workplane/compound/compsolid/primitives(_railway)); GoString(nil) 判空 (ifc/dxf); LocationAt finalizer 泄漏; mesh 回调 KeepAlive;
- `Point3/Dir3` 实现 MarshalJSON/UnmarshalJSON (审计高危项: JSON 往返坐标归零);
- `CreateMastAssemblyParams.withDefaults` (零值参数兜底);
- `CalcOcsSpanPositions` 柱数向上取整 (修跨距膨胀至近 2 倍的不一致)。
- **未实施**: `ocs_layout` 末跨弛度按实际跨长 — 已改后与固化该领域约定的测试冲突, 回退, 留待领域决策; mesh.go Go 指针长期存 C 的完整 handle 化 (已加 KeepAlive 缓解); workplaneApplyFunc 输出数量回传 (需 C API 签名变更)。

### P2 性能

- `sweepProfile` 逐段 prism+Fuse 链 → `BRepOffsetAPI_MakePipeShell` 一次成形 (修挂死);
- 钢轨/道床放样截面数封顶 512 (10km 中心线 20000 截面 → 512);
- sleeperSpacing 正数下界 + 轨枕数 10 万上限 (修极小间距假死)。

## 验证结果

- **基线 (修改前) 全量测试即有 5 处失败/崩溃**: TestCreateUShapedRing 必崩 SIGSEGV、TestSketchEach/FilterMap cgo panic、TestSketchSolver SEGV、TestWorkplaneFilletChamfer SEGV、TestCreateMultiLayerExtrusionStructure FAIL、assembly_solve 间歇 SIGABRT (Ipoort 垃圾 tol, 根因是堆破坏)。
- **修复后**: 全量测试除 `TestCustomPolygonPipe` 外全部通过 (该测试经基线验证为预存在失败, 自定义多边形剖面管道 OCC 生成问题, 与本次审计项无关)。
- 间歇 SIGABRT 在堆破坏修复 (selector UAF + optional UB + safe_call 空指针) 后未再复现。

## 遗留事项

1. `TestCustomPolygonPipe` 预存在失败 — 需单独排查 create_pipe_helper 的剖面有效性;
2. mesh.go 回调结构长期持有 Go 指针 — 建议后续改 handle-id 模式;
3. `workplane_apply` 输出数量无回传参数 — 需 C API 签名变更;
4. OCS 末跨弛度约定 — 需领域确认后统一;
5. C API 错误通道仍以 stderr + 默认返回值为主 — 可考虑统一错误码字符串回传。
