// 矿山专业参数化图元声明 (minebim P 线, Q/SHJ 0035.3-2012 图例台账)。
// 分类: 井巷(本文件+primitives_mine.cc) / 通风(primitives_mine_vent.cc) /
// 防治水与地质(primitives_mine_water.cc) / 运输(primitives_mine_transport.cc) /
// 管线(primitives_mine_pipeline.cc)。
// 单位: 无量纲 (minebim 以 m 传入); 断面局部系 X=宽向 Y=高向 底板 y=0。
#ifndef GO_PRIMITIVES_MINE_HH
#define GO_PRIMITIVES_MINE_HH

#include <TopoDS_Shape.hxx>
#include <TopoDS_Wire.hxx>
#include <gp_Dir.hxx>
#include <gp_Pln.hxx>
#include <gp_Trsf.hxx>
#include <gp_Vec.hxx>
#include <utility>
#include <vector>

namespace flywave {
namespace topo {

// —— 内部几何助手 (mine 图元族共享, 实现在 primitives_mine.cc; 非公开 API) ——
gp_Trsf mine_translation_trsf(const gp_Vec &v);
gp_Dir mine_left_perp(const gp_Dir &d);  // 水平左法向 (-dy, dx)
gp_Dir mine_right_perp(const gp_Dir &d); // 水平右法向 (dy, -dx)
TopoDS_Wire mine_wire_on_plane(
    const gp_Pnt &origin, const gp_Dir &xdir, const gp_Dir &normal,
    const std::vector<std::pair<double, double>> &pts);
TopoDS_Shape mine_extrude_profile(
    const gp_Pnt &origin, const gp_Dir &xdir, const gp_Dir &normal,
    const std::vector<std::pair<double, double>> &pts, double dist);
TopoDS_Shape mine_fuse_two(const TopoDS_Shape &a, const TopoDS_Shape &b);
TopoDS_Shape mine_compound_all(const std::vector<TopoDS_Shape> &parts);
TopoDS_Shape mine_cylinder_from(const gp_Pnt &base, const gp_Dir &dir,
                                double r, double len);
TopoDS_Shape mine_prism_with_hole(const gp_Pln &pln, const TopoDS_Wire &outer,
                                  const TopoDS_Wire &inner, const gp_Vec &v);

// 断面族 (Q/SHJ 图例 6 枚举 + 马蹄/圆, 值与 Go MineSection 常量对齐)。
enum class mine_section {
  rect = 0,      // 矩形
  trap = 1,      // 梯形
  arch = 2,      // 半圆拱
  arc_arch = 3,  // 圆弧拱
  horseshoe = 4, // 马蹄 (三心圆近似)
  circle = 5,    // 圆形
  ellipse = 6,   // 椭圆
};

// 断面闭环 (局部 2D: X=宽向, Y=高向, 底板 y=0)。
std::vector<std::pair<double, double>> mine_section_loop(mine_section sec,
                                                         double w, double h);
mine_section mine_section_cast(int v); // 越界抛 ConstructionError

// ================= A 井巷工程 =================

// 立井井筒: 断面环沿 -Z 拉伸 depth。shape: 0=圆形 1=矩形。原点=井口中心。
struct mine_shaft_params {
  int shape;
  double innerRadius;
  double outerRadius;
  double innerLength;
  double innerWidth;
  double outerLength;
  double outerWidth;
  double depth;
};
TopoDS_Shape create_mine_shaft(const mine_shaft_params &params);
TopoDS_Shape create_mine_shaft(const mine_shaft_params &params,
                               const gp_Pnt &collarCenter);

// 巷道: 断面沿 3D 中心线逐段扫掠 (拐角楔补); path 顶点自带标高 (变坡)。
struct mine_roadway_params {
  mine_section section;
  double width;
  double height;
  std::vector<gp_Pnt> path; // ≥2 点
};
TopoDS_Shape create_mine_roadway(const mine_roadway_params &params);

// 硐室: 轴对盒体, center = 底面中心。
struct mine_chamber_params {
  gp_Pnt center;
  double length;
  double width;
  double height;
};
TopoDS_Shape create_mine_chamber(const mine_chamber_params &params);

// 长壁工作面: 切眼 (origin→origin+dir×faceLength) × 推进 advance, 采高厚板。
struct mine_workingface_params {
  gp_Pnt origin; // 切眼起点 (运输巷端, 底板)
  gp_Dir dir;    // 切眼方向 (水平)
  double faceLength;
  double advance;
  double seamThickness;
};
TopoDS_Shape create_mine_workingface(const mine_workingface_params &params);

// 掘进迎头: 断面封闭帽。
struct mine_heading_params {
  gp_Pnt center; // 断面底板中心
  gp_Dir dir;    // 掘进方向
  mine_section section;
  double width;
  double height;
};
TopoDS_Shape create_mine_heading(const mine_heading_params &params);

// 面状体 (采空区/水仓/积水区共用): 边界多边形自 baseZ 拉伸 height。
struct mine_area_body_params {
  std::vector<gp_Pnt> boundary; // XY 边界 (z 分量忽略, 用 baseZ)
  double baseZ;
  double height;
};
TopoDS_Shape create_mine_area_body(const mine_area_body_params &params);

// 煤仓/溜煤眼: 站位变径圆放样, 上口圆心 center, 轴沿 -Z。
struct mine_orepass_station {
  double depth;  // ≥0 严格递增
  double radius; // >0
};
struct mine_orepass_params {
  gp_Pnt center;
  std::vector<mine_orepass_station> stations; // ≥2
};
TopoDS_Shape create_mine_orepass(const mine_orepass_params &params);

// ================= B 支护系统 =================

// 锚杆/锚索排: rows 排 (spacing), 每排 perRow 根顶板竖直 + 两帮水平各一根;
// cable=true 加顶板托盘薄板。compound (免布尔)。
struct mine_bolt_row_params {
  gp_Pnt origin; // 首排断面底板中心
  gp_Dir axis;   // 巷道轴向 (水平)
  mine_section section;
  double width;
  double height;
  int rowCount;    // [1,12]
  int perRow;      // [1,8]
  double spacing;
  double boltLength;
  double diameter;
  bool cable;
};
TopoDS_Shape create_mine_bolt_row(const mine_bolt_row_params &params);

// U型钢支架排: count 榀断面环 (榀厚=thickness), 榀距 spacing。compound。
struct mine_usteel_row_params {
  gp_Pnt origin;
  gp_Dir axis;
  mine_section section;
  double width;
  double height;
  double thickness; // 型钢断面高
  double spacing;
  int count; // [1,20]
};
TopoDS_Shape create_mine_usteel_row(const mine_usteel_row_params &params);

// 液压支架排: 通长底座/顶梁板 + 立柱对 (≤maxLegPairs 对封顶)。compound。
struct mine_shield_row_params {
  gp_Pnt origin; // 切眼起点
  gp_Dir dir;    // 切眼方向
  int count;     // 台数 (台账真实值)
  double centerDist;
  double beamWidth;
  double beamThick;
  double height;
  int maxLegPairs; // 几何护栏 (如 24)
};
TopoDS_Shape create_mine_shield_row(const mine_shield_row_params &params);

// 喷浆/砌碹衬砌 (断面枚举式): 断面 loop 布置在 origin (轴上底板中心), 沿 axis 挤 length。
struct mine_shotcrete_params {
  gp_Pnt origin;
  gp_Dir axis;
  mine_section section;
  double width;
  double height;
  double thickness;
  double length;
};
TopoDS_Shape create_mine_shotcrete(const mine_shotcrete_params &params);

// 支护衬砌壳 (喷浆/砌碹): 断面闭合折线逐边外扩 thickness, 沿 dir 拉伸 length。
struct mine_lining_params {
  std::vector<gp_Pnt> section; // ≥3 点非退化
  double thickness;
  double length;
  gp_Dir dir;
};
TopoDS_Shape create_mine_lining(const mine_lining_params &params);

// 水沟 (断面设计 §5.27): 断面沿宿主巷道偏移路径扫掠。
struct mine_trench_params {
  std::vector<gp_Pnt> path; // 沟中心线 (z=底板)
  mine_section section;     // trap(等腰梯形)|rect(矩形)|arc_arch 等 (复用断面族)
  double width;
  double height;
  double sideOffset; // 距巷道中心线横向偏移 (左+/右-)
};
TopoDS_Shape create_mine_trench(const mine_trench_params &params);

// 交岔点: 主巷×支巷棱柱并 + 可选加固衬砌段 (挑棚)。
struct mine_junction_params {
  gp_Pnt center;         // 交点 (底板)
  gp_Dir mainAxis;       // 主巷轴向
  double branchAngleDeg; // 支巷偏角 (自主轴, 度)
  mine_section section;
  double width;
  double height;
  double mainLength;   // 主巷全长 (过交点)
  double branchLength; // 支巷全长
  double reinforceLength; // 加固段长 (0=不建)
};
TopoDS_Shape create_mine_junction(const mine_junction_params &params);

// ================= C 通风设施 =================

// 风墙/密闭: 宿主断面 loop 沿轴向挤 thickness。center = 断面底板中心。
struct mine_vent_wall_params {
  mine_section section;
  double width;
  double height;
  double thickness;
  gp_Pnt center;
  gp_Dir axis; // 宿主巷道轴向 (挤出正向)
};
TopoDS_Shape create_mine_vent_wall(const mine_vent_wall_params &params);

// 矩形墙体 (防爆墙/防火墙/防水墙共用)。
struct mine_box_wall_params {
  double width;
  double height;
  double thickness;
  gp_Pnt center;
  gp_Dir axis;
};
TopoDS_Shape create_mine_box_wall(const mine_box_wall_params &params);

// 风门: 双立柱+门楣门框 + 门板; openAngleDeg>0 时门板绕门洞右边缘竖轴外摆。
struct mine_vent_door_params {
  double width;
  double height;
  double doorWidth;
  double doorHeight;
  double doorThick;
  double frameWidth;
  gp_Pnt center;
  gp_Dir axis;
  double openAngleDeg; // 0=关闭
};
TopoDS_Shape create_mine_vent_door(const mine_vent_door_params &params);

// 调节风窗: 带窗孔墙体 (面挖孔) + 竖向格栅。
struct mine_vent_window_params {
  double width;
  double height;
  double thickness;
  double winWidth;
  double winHeight;
  double winSill;
  int bars; // ≥0
  gp_Pnt center;
  gp_Dir axis;
};
TopoDS_Shape create_mine_vent_window(const mine_vent_window_params &params);

// 风桥: 拱环带 (环面含 axis, 法向垂直 axis), 沿法向挤 width。
struct mine_vent_bridge_params {
  double span;
  double width;
  double thickness;
  double apex;
  gp_Pnt center;
  gp_Dir axis; // 被穿巷道轴向
};
TopoDS_Shape create_mine_vent_bridge(const mine_vent_bridge_params &params);

// 测风站 (199): 断面框标 (两侧立柱 + 顶梁, 轻量标示)。compound。
struct mine_vent_station_params {
  mine_section section;
  double width;
  double height;
  double postWidth; // 立柱宽
  double depth;     // 纵深 (沿轴向厚)
  gp_Pnt center;
  gp_Dir axis;
};
TopoDS_Shape create_mine_vent_station(const mine_vent_station_params &params);

// 栅栏/栅栏门 (192,193): 立柱 + 上下横档 + 竖栅条 (动态宽×高)。compound。
struct mine_fence_params {
  double width;
  double height;
  double postWidth;   // 立柱/横档断面宽
  double barWidth;    // 竖条宽
  double thickness;   // 沿轴向厚
  int bars;           // 竖条数 ≥1
  gp_Pnt center;      // 底板中心
  gp_Dir axis;
};
TopoDS_Shape create_mine_fence(const mine_fence_params &params);

// 风筒: 圆管沿 3D 路径段挤出链。
struct mine_vent_duct_params {
  std::vector<gp_Pnt> path; // 已含吊挂标高
  double diameter;
};
TopoDS_Shape create_mine_vent_duct(const mine_vent_duct_params &params);

// ================= D 防治水与地质 =================

// 陷落柱: 底/顶双椭圆 (ThruSections 平滑锥台放样)。
struct mine_collapse_pillar_params {
  gp_Pnt bottomCenter; // 底面中心
  double bottomLong;
  double bottomShort;
  double topLong;
  double topShort;
  double height; // 底→顶
};
TopoDS_Shape create_mine_collapse_pillar(
    const mine_collapse_pillar_params &params);

// 断层破碎带透镜体 (凸透镜状: 中间厚边缘尖灭), 沿走向居中棱柱。
struct mine_fault_lens_params {
  gp_Pnt center;     // 走向中点 × 顶底高程中点
  gp_Dir strike;     // 走向 (水平)
  gp_Dir dipAzimuth; // 倾向 (水平, 与走向不平行)
  double dipAngle;   // 度 (0,90)
  double zoneWidth;  // 面内最大厚度
  double zoneLength; // 走向长度
  double topElev;
  double bottomElev;
};
TopoDS_Shape create_mine_fault_lens(const mine_fault_lens_params &params);

// 水闸墙: 带行人门洞的宿主断面封堵体 (doorWidth≤0 为实心)。
struct mine_water_gate_wall_params {
  double width;
  double height;
  double thickness;
  double doorWidth;
  double doorHeight;
  gp_Pnt center;
  gp_Dir axis;
};
TopoDS_Shape create_mine_water_gate_wall(
    const mine_water_gate_wall_params &params);

// 水闸门: 门框三块 + 承压门扇 + 3 道横肋。compound。
struct mine_water_gate_params {
  double width;
  double height;
  double doorWidth;
  double doorHeight;
  double doorThick;
  double frameWidth;
  gp_Pnt center;
  gp_Dir axis;
};
TopoDS_Shape create_mine_water_gate(const mine_water_gate_params &params);

// 钻孔: 定向分层圆柱段 (layers 空 = 整孔单段)。compound。
struct mine_borehole_layer {
  double from; // 沿孔轴距孔口
  double to;
};
struct mine_borehole_params {
  gp_Pnt collar;
  gp_Dir axis; // 钻进方向 (含倾角方位)
  double diameter;
  std::vector<mine_borehole_layer> layers; // 可空
};
TopoDS_Shape create_mine_borehole(const mine_borehole_params &params);

// ================= E 运输系统 =================

// 轨道: 复用 create_rail_pair + 轨枕; doubleTrack 时 ±centerDistance/2 双线。
struct mine_rail_track_params {
  std::vector<gp_Pnt> path; // 中心线 (z=轨面标高)
  double gauge;
  bool doubleTrack;
  double centerDistance;
  double sleeperSpacing; // ≤0 不建轨枕
  int sleeperMax;        // 几何护栏 (如 300)
};
TopoDS_Shape create_mine_rail_track(const mine_rail_track_params &params);

// 道岔 (v1 骨架): 直股 + 辙叉角曲股 rail pairs。
struct mine_turnout_params {
  gp_Pnt origin; // 岔心 (岔尖起点)
  gp_Dir axis;
  double gauge;
  double frogNo; // 辙叉号 [2,30]
  double length; // 直股长
};
TopoDS_Shape create_mine_turnout(const mine_turnout_params &params);

// 带式输送机: 带面扫掠 + 头尾滚筒 (path z = 底板标高)。
struct mine_belt_params {
  std::vector<gp_Pnt> path;
  double beltWidth;
  double frameHeight; // 带面距底板
};
TopoDS_Shape create_mine_belt(const mine_belt_params &params);

// 刮板输送机: U 槽断面沿路径。
struct mine_scraper_params {
  std::vector<gp_Pnt> path;
  double panWidth;
  double panHeight;
};
TopoDS_Shape create_mine_scraper(const mine_scraper_params &params);

// 单轨吊: I 断面沿吊挂路径。
struct mine_monorail_params {
  std::vector<gp_Pnt> path; // z = 轨底标高
  double railHeight;
  double flangeWidth;
};
TopoDS_Shape create_mine_monorail(const mine_monorail_params &params);

// ================= F 管线系统 =================

// 管路: 圆管沿路径段挤出链 + 托架环 (bracketSpacing>0)。
struct mine_pipe_run_params {
  std::vector<gp_Pnt> path; // 已含敷设标高
  double diameter;
  double bracketSpacing; // ≤0 不建托架
};
TopoDS_Shape create_mine_pipe_run(const mine_pipe_run_params &params);

// 钢带/W钢带: 长板 + n 孔 (孔径 holeDia, 端部留边 holeEdge); 长度沿局部 X。
struct mine_steel_band_params {
  double length;
  double width;
  double thickness;
  int holeCount; // ≥0
  double holeDia;
  double holeEdge; // 首末孔距端部
};
TopoDS_Shape create_mine_steel_band(const mine_steel_band_params &params);

// 三通/弯通管件: 主管段 + 支管段 (夹角 branchAngleDeg) Union (阀门归模型库)。
struct mine_pipe_fitting_params {
  gp_Pnt center; // 汇交点
  gp_Dir mainAxis;
  double branchAngleDeg;
  double mainLength;
  double branchLength;
  double diameter;
};
TopoDS_Shape create_mine_pipe_fitting(const mine_pipe_fitting_params &params);

// 电缆/通讯线: lines 根并行细缆 (横向间距 = 直径×1.2)。
struct mine_cable_run_params {
  std::vector<gp_Pnt> path;
  double diameter;
  int lines; // [1,6]
};
TopoDS_Shape create_mine_cable_run(const mine_cable_run_params &params);

} // namespace topo
} // namespace flywave

#endif // GO_PRIMITIVES_MINE_HH
