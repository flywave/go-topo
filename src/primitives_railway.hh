#pragma once

#include <TopoDS_Shape.hxx>
#include <TopoDS_Wire.hxx>
#include <gp_Dir.hxx>
#include <gp_Pnt.hxx>

#include <vector>

namespace flywave {
namespace topo {

// =========================================================================
// 1. Contact Wire (接触线) TYPE=OCS_CW
// =========================================================================
struct contact_wire_params {
  double sectionalArea;      // 截面积(mm²)
  double diameter;           // 标称直径(mm)
  double ratedTension;       // 额定张力(kN)
  double grooveDepth;        // 沟槽深度(mm)
  double grooveWidth;        // 沟槽宽度(mm)
  double bottomRadius;       // 底部接触面圆弧半径(mm)
  double topRadius;          // 顶部夹持面圆弧半径(mm)
};

TopoDS_Shape create_contact_wire(const contact_wire_params &params,
                                 const gp_Pnt &startPoint,
                                 const gp_Pnt &endPoint);

// =========================================================================
// 2. Messenger Wire (承力索) TYPE=OCS_MW
// =========================================================================
struct messenger_wire_params {
  double diameter;      // 直径(mm)
  double ratedTension;  // 额定张力(kN)
  double structuralHeight; // 结构高度(mm) — 与接触线的垂直距离
};

TopoDS_Shape create_messenger_wire(const messenger_wire_params &params,
                                   const gp_Pnt &startPoint,
                                   const gp_Pnt &endPoint);

// =========================================================================
// 3. Cross Arm (横担) TYPE=OCS_CROSS_ARM
// =========================================================================
enum class cross_arm_type {
  DOUBLE_FORK = 1,   // 双叉臂固定横担
  TRIANGLE_BRACE = 2, // 三角撑横担
  TRUSS = 3           // 桁架式横担
};

struct cross_arm_params {
  cross_arm_type type;    // 类型
  double beamLength;      // 横梁长度(mm)
  double beamHeight;      // 横梁截面高(mm)
  double beamWidth;       // 横梁截面宽(mm)
  double beamThickness;   // 横梁壁厚(mm)
  double beamSpacing;     // 上下梁间距(mm), 对应腕臂上下底座安装距
  double braceLength;     // 斜撑长度(mm)
  double braceDiameter;   // 斜撑截面直径(mm)
  double mountHeight;     // 安装高度(mm)
  double boltSpacing;     // 螺栓孔间距(mm)
  double boltDiameter;    // 螺栓孔径(mm)
  int boltCount;          // 螺栓数量
};

TopoDS_Shape create_cross_arm(const cross_arm_params &params);
TopoDS_Shape create_cross_arm(const cross_arm_params &params,
                              const gp_Pnt &position,
                              const gp_Dir &normal = gp::DZ(),
                              const gp_Dir &xDir = gp::DX());

// =========================================================================
// 4. Level Cantilever (平腕臂) TYPE=OCS_CANT_LEVEL
// =========================================================================
struct level_cantilever_params {
  double length;          // 平腕臂总长(mm)
  double outerDiameter;   // 钢管外径(mm)
  double wallThickness;   // 壁厚(mm)
  double mountHeight;     // 安装高度(mm)
  double riseAngle;       // 水平仰角(°)
};

TopoDS_Shape create_level_cantilever(const level_cantilever_params &params);
TopoDS_Shape create_level_cantilever(const level_cantilever_params &params,
                                     const gp_Pnt &basePoint,
                                     const gp_Dir &axisDirection = gp::DX(),
                                     const gp_Dir &upDir = gp::DZ());

// =========================================================================
// 5. Slanted Cantilever (斜腕臂) TYPE=OCS_CANT_SLANT
// =========================================================================
struct slant_cantilever_params {
  double length;          // 斜腕臂总长(mm)
  double outerDiameter;   // 钢管外径(mm)
  double wallThickness;   // 壁厚(mm)
  double slantAngle;      // 安装倾角(°) — 相对铅垂线
};

TopoDS_Shape create_slant_cantilever(const slant_cantilever_params &params);
TopoDS_Shape create_slant_cantilever(const slant_cantilever_params &params,
                                     const gp_Pnt &basePoint,
                                     const gp_Dir &axisDirection = gp::DX(),
                                     const gp_Dir &upDir = gp::DZ());

// =========================================================================
// 6. Curved Arm (弯臂) TYPE=OCS_CURVED_ARM
// =========================================================================
enum class curved_arm_type {
  ARC = 1,   // 弧形弯臂
  L_SHAPE = 2, // L形弯臂
  DOUBLE = 3   // 双弯臂
};

struct curved_arm_params {
  curved_arm_type type;      // 类型
  double verticalLength;     // 竖直段长度(mm)
  double horizontalLength;   // 水平段长度(mm)
  double bendRadius;         // 弯曲半径(mm)
  double bendAngle;          // 弯曲角度(°)
  double outerDiameter;      // 管外径(mm)
  double wallThickness;      // 壁厚(mm)
  double flangeThickness;    // 安装法兰厚度(mm)
  double boltSpacing;        // 法兰螺栓孔间距(mm)
  double boltDiameter;       // 法兰螺栓孔径(mm)
};

TopoDS_Shape create_curved_arm(const curved_arm_params &params);
TopoDS_Shape create_curved_arm(const curved_arm_params &params,
                               const gp_Pnt &position,
                               const gp_Dir &normal = gp::DZ(),
                               const gp_Dir &xDir = gp::DX());

// =========================================================================
// 7. Rod Insulator (棒式绝缘子) TYPE=OCS_ROD_INSULATOR
// =========================================================================
enum class rod_insulator_type {
  SOLID = 1,  // 实心棒式
  HOLLOW = 2  // 空心棒式
};

enum class end_fitting_type {
  FLANGE = 1,   // 法兰式
  BALL = 2,     // 球头
  SCREW = 3     // 螺杆式
};

struct rod_insulator_params {
  rod_insulator_type type;    // 类型
  double height;              // 绝缘子本体长度(mm)
  double outerDiameter;       // 棒体最大外径(mm)
  double innerDiameter;       // 内径(mm, 实心为0)
  double shedDiameter;        // 伞裙大径(mm)
  double shedSpacing;         // 伞裙间距(mm)
  int shedCount;              // 伞裙数量
  end_fitting_type endFitting; // 端部连接方式
  double flangeDiameter;      // 端部法兰直径(mm)
  double flangeBoltSpacing;   // 法兰螺栓孔分度圆直径(mm)
  double flangeBoltDiameter;  // 法兰螺栓孔径(mm)
};

TopoDS_Shape create_rod_insulator(const rod_insulator_params &params);
TopoDS_Shape create_rod_insulator(const rod_insulator_params &params,
                                  const gp_Pnt &basePoint,
                                  const gp_Dir &axisDirection = gp::DZ());

// =========================================================================
// 8. Mast Bracket (支柱连接座) TYPE=OCS_MAST_BRACKET
// =========================================================================
struct mast_bracket_params {
  double boltSpacing;           // 与支柱连接的螺栓孔间距(mm)
  double boltDiameter;          // 安装孔径(mm)
  double height;                // 座体高度(mm)
  double width;                 // 座体宽度(mm)
  double thickness;             // 座体钢板厚度(mm)
  double insulatorBoltSpacing;  // 绝缘子安装孔间距(mm)
  double insulatorBoltDiameter; // 绝缘子安装孔径(mm)
  double mountAngle;            // 安装角度(°)
};

TopoDS_Shape create_mast_bracket(const mast_bracket_params &params);
TopoDS_Shape create_mast_bracket(const mast_bracket_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &normal = gp::DX(),
                                 const gp_Dir &upDir = gp::DZ());

// =========================================================================
// 9. Registration Arm (定位器) TYPE=OCS_REG_ARM
// =========================================================================
enum class registration_arm_type {
  STRAIGHT = 1,   // 直型
  CURVED = 2,     // 弯型
  EXTENDED = 3    // 加长型
};

struct registration_arm_params {
  registration_arm_type type; // 类型: 1-平直 2-弓型 3-加长
  double length;              // 定位管长度(mm)
  double tubeWidth;           // 方管截面宽(mm)
  double tubeHeight;          // 方管截面高(mm)
  double wallThickness;       // 壁厚(mm)
  double angle;               // 抬升/下压角(°)
  bool isReverse;             // 正/反定位器 (反=安装方向相反)
};

TopoDS_Shape create_registration_arm(const registration_arm_params &params);
TopoDS_Shape create_registration_arm(const registration_arm_params &params,
                                     const gp_Pnt &basePoint,
                                     const gp_Dir &axisDirection = gp::DX(),
                                     const gp_Dir &upDir = gp::DZ());

// =========================================================================
// 10. Guy Wire (下锚拉线) TYPE=OCS_GUY_WIRE
// =========================================================================
struct guy_wire_params {
  double length;          // 拉线长度(mm)
  double diameter;        // 钢丝绳直径(mm)
  double angle;           // 拉线与水平面夹角(°)
  double ratedTension;    // 额定张力(kN)
  bool hasInsulator;      // 是否串接绝缘子
  double anchorRodDiameter; // 拉线棒直径(mm)
  double anchorRodLength;   // 拉线棒长度(mm)
  double anchorPlateLength; // 拉线盘长(mm)
  double anchorPlateWidth;  // 拉线盘宽(mm)
};

TopoDS_Shape create_guy_wire(const guy_wire_params &params);
TopoDS_Shape create_guy_wire(const guy_wire_params &params,
                             const gp_Pnt &anchorPoint,
                             const gp_Pnt &mastPoint,
                             const gp_Dir &upDir = gp::DZ());

// =========================================================================
// 11. Steel Mast (钢支柱) TYPE=OCS_STEEL_MAST
// =========================================================================
enum class steel_mast_type {
  LATTICE = 1,    // 格构式钢柱
  H_BEAM = 2      // H型钢柱
};

struct steel_mast_params {
  steel_mast_type type;   // 类型
  double height;          // 柱高(mm)
  double topWidth;        // 柱顶截面宽度(mm)
  double bottomWidth;     // 柱底截面宽度(mm)
  double wallThickness;   // 钢板厚度(mm)
  double flangeThickness; // 法兰厚度(mm)
  double flangeWidth;     // 法兰边长(mm)
  double anchorSpacing;   // 锚栓间距(mm)
  double anchorDiameter;  // 锚栓直径(mm)
  int segmentCount;       // 分段数量
};

TopoDS_Shape create_steel_mast(const steel_mast_params &params);
TopoDS_Shape create_steel_mast(const steel_mast_params &params,
                               const gp_Pnt &baseCenter,
                               const gp_Dir &axisDirection = gp::DZ());

// =========================================================================
// 12. Concrete Mast (混凝土支柱) TYPE=OCS_CONC_MAST
// =========================================================================
enum class concrete_mast_section_type {
  CIRCULAR = 1,     // 环形
  RECTANGULAR = 2,  // 矩形
  CIRCULAR_HOLED = 3, // 带孔环形
  RECTANGULAR_HOLED = 4 // 矩形挖孔
};

struct concrete_mast_params {
  concrete_mast_section_type sectionType; // 截面类型
  double height;                          // 柱高(mm)
  double topWidth;                        // 柱顶外径/宽(mm)
  double bottomWidth;                     // 柱底外径/宽(mm)
  double wallThickness;                   // 壁厚(mm)

  // 安装孔参数 (带孔样式适用)
  double holeDiameter;        // 孔径(mm)
  double holeSpacingV;        // 孔纵向间距(mm)
  double holeSpacingH;        // 孔横向间距(mm)
  double firstHoleOffset;     // 首孔距柱底距离(mm)
  int holeRowCount;           // 沿高度方向的分组数
  int holesPerRow;            // 每列孔数
};

TopoDS_Shape create_concrete_mast(const concrete_mast_params &params);
TopoDS_Shape create_concrete_mast(const concrete_mast_params &params,
                                  const gp_Pnt &baseCenter,
                                  const gp_Dir &axisDirection = gp::DZ());

// =========================================================================
// 13. OCS Foundation (支柱基础) TYPE=FOUNDATION_FLANGE
// =========================================================================
enum class foundation_type {
  DIRECT_BURIED = 1,   // 直埋式
  FLANGE = 2,          // 法兰盘基础
  BORED_PILE = 3,      // 钻孔灌注桩
  EXCAVATED_PILE = 4,  // 挖孔桩
  ANCHOR = 5           // 锚栓基础
};

struct ocs_foundation_params {
  foundation_type type;   // 基础类型
  double height;          // 基础高(mm)
  double width;           // 基础宽(mm)
  double length;          // 基础长(mm)
  double flangeThickness; // 法兰厚(mm)
  int anchorCount;        // 地脚螺栓数量
  double anchorDiameter;  // 螺栓直径(mm)
  double anchorLength;    // 锚固长度(mm)
  double anchorSpacing;   // 螺栓间距(mm)
};

TopoDS_Shape create_ocs_foundation(const ocs_foundation_params &params);
TopoDS_Shape create_ocs_foundation(const ocs_foundation_params &params,
                                   const gp_Pnt &position,
                                   const gp_Dir &normal = gp::DZ(),
                                   const gp_Dir &xDir = gp::DX());

// =========================================================================
// 14. Dropper (吊弦) TYPE=OCS_DROPPER
// =========================================================================
struct dropper_params {
  double length;          // 吊弦长度(mm)
  double wireDiameter;    // 吊弦线径(mm)
  double clampLength;     // 线夹长度(mm)
  double clampWidth;      // 线夹宽度(mm)
  double clampThickness;  // 线夹厚度(mm)
  bool conductive;        // 是否导电型
};

TopoDS_Shape create_dropper(const dropper_params &params);
TopoDS_Shape create_dropper(const dropper_params &params,
                            const gp_Pnt &topPoint,
                            const gp_Dir &direction = gp::DZ());

// =========================================================================
// 15. Cantilever Base / Wrist Base (腕臂底座) TYPE=OCS_CANT_BASE
// =========================================================================
struct cantilever_base_params {
  double length;           // 底座长度(mm)
  double width;            // 底座宽度(mm)
  double height;           // 底座高度(mm)
  double boltSpacing;      // 螺栓孔间距(mm)
  double boltDiameter;     // 螺栓孔径(mm)
  int boltCount;           // 螺栓数量
};

TopoDS_Shape create_cantilever_base(const cantilever_base_params &params);
TopoDS_Shape create_cantilever_base(const cantilever_base_params &params,
                                    const gp_Pnt &position,
                                    const gp_Dir &normal = gp::DX(),
                                    const gp_Dir &upDir = gp::DZ());

// =========================================================================
// 16. Messenger Wire Saddle (承力索座) TYPE=OCS_MW_SADDLE
// =========================================================================
struct mw_saddle_params {
  double length;        // 座体长度(mm)
  double width;         // 座体宽度(mm)
  double height;        // 座体高度(mm)
  double grooveRadius;  // 线槽半径(mm)
  double boltDiameter;  // 螺栓孔径(mm)
};

TopoDS_Shape create_mw_saddle(const mw_saddle_params &params);
TopoDS_Shape create_mw_saddle(const mw_saddle_params &params,
                              const gp_Pnt &position,
                              const gp_Dir &normal = gp::DZ(),
                              const gp_Dir &xDir = gp::DX());

// =========================================================================
// 17. Balance Weight (坠砣) TYPE=OCS_BALANCE_WEIGHT
// =========================================================================
struct balance_weight_params {
  double width;               // 坠砣宽度(mm)
  double thickness;           // 坠砣厚度(mm)
  double height;              // 坠砣高度(mm)
  double centerHoleDiameter;  // 中心孔径(mm)
};

TopoDS_Shape create_balance_weight(const balance_weight_params &params);
TopoDS_Shape create_balance_weight(const balance_weight_params &params,
                                   const gp_Pnt &position,
                                   const gp_Dir &normal = gp::DZ(),
                                   const gp_Dir &xDir = gp::DX());

// =========================================================================
// 18. Weight Rod (坠砣杆) TYPE=OCS_WEIGHT_ROD
// =========================================================================
struct weight_rod_params {
  double rodDiameter;   // 杆径(mm)
  double rodLength;     // 杆长(mm)
  double topHoleDiameter; // 上端连接孔径(mm)
};

TopoDS_Shape create_weight_rod(const weight_rod_params &params);
TopoDS_Shape create_weight_rod(const weight_rod_params &params,
                               const gp_Pnt &position,
                               const gp_Dir &axisDirection = gp::DZ());

// =========================================================================
// 19. Anchor Fitting (下锚金具) TYPE=OCS_ANCHOR_FITTING
// =========================================================================
enum class anchor_fitting_type {
  ROD_AND_RING = 1,  // 杵环杆
  DOUBLE_EAR = 2,    // 双耳连接器
  WEDGE_CLAMP = 3    // 楔形线夹
};

struct anchor_fitting_params {
  anchor_fitting_type type; // 类型
  double length;            // 长度(mm)
  double diameter;          // 直径/规格(mm)
};

TopoDS_Shape create_anchor_fitting(const anchor_fitting_params &params);
TopoDS_Shape create_anchor_fitting(const anchor_fitting_params &params,
                                   const gp_Pnt &position,
                                   const gp_Dir &direction = gp::DX(),
                                   const gp_Dir &upDir = gp::DZ());

// =========================================================================
// 20. Crossing (线岔) TYPE=OCS_CROSSING
// =========================================================================
struct crossing_params {
  double limitPipeLength;  // 限制管长度(mm)
  double pipeDiameter;     // 限制管外径(mm)
  double wireDiameter;     // 接触线直径(mm)
  double heightDiff;       // 导高差(mm)
};

TopoDS_Shape create_crossing(const crossing_params &params);
TopoDS_Shape create_crossing(const crossing_params &params,
                             const gp_Pnt &crossPoint,
                             const gp_Dir &mainDir = gp::DX(),
                             const gp_Dir &branchDir = gp::DY());

// =========================================================================
// 21. Head Span (软横跨) TYPE=OCS_HEAD_SPAN
// =========================================================================
struct head_span_params {
  double span;                    // 跨距(mm)
  int hangPointCount;             // 悬挂点数量
  double hangPointSpacing;        // 悬挂点间距(mm)
  double crossCatenaryDiameter;   // 横向承力索直径(mm)
  double crossCatenarySag;        // 横向承力索弧垂(mm)
  double upperRopeDiameter;       // 上部固定绳直径(mm)
  double lowerRopeDiameter;       // 下部固定绳直径(mm)
  double insulatorLength;         // 绝缘子串长度(mm)
};

TopoDS_Shape create_head_span(const head_span_params &params);
TopoDS_Shape create_head_span(const head_span_params &params,
                              const gp_Pnt &leftMast,
                              const gp_Pnt &rightMast,
                              const gp_Dir &upDir = gp::DZ());

// =========================================================================
// 22. Transverse Span (硬横跨) TYPE=OCS_TRANS_SPAN
// =========================================================================
enum class beam_section_type {
  BOX = 1,      // 箱型
  H_BEAM_T = 2, // H型
  TRUSS = 3,    // 桁架式
  COMBO = 4     // 组合式
};

struct transverse_span_params {
  double span;                // 跨距(mm)
  beam_section_type beamType; // 横梁截面形式
  double beamHeight;          // 横梁截面高(mm)
  double beamWidth;           // 横梁截面宽(mm)
  double beamThickness;       // 板厚(mm)
  double mastHeight;          // 立柱高度(mm)
  double mastWidth;           // 立柱宽度(mm)
};

TopoDS_Shape create_transverse_span(const transverse_span_params &params);
TopoDS_Shape create_transverse_span(const transverse_span_params &params,
                                    const gp_Pnt &position,
                                    const gp_Dir &direction = gp::DX(),
                                    const gp_Dir &upDir = gp::DZ());

// =========================================================================
// 22b. Hanger Post (硬横跨吊柱) TYPE=OCS_HANGER_POST
// =========================================================================
enum class hanger_post_section_type {
  ROUND = 1,    // 圆管
  SQUARE = 2,   // 方管
  H_BEAM_H = 3  // H型钢
};

struct hanger_post_params {
  hanger_post_section_type sectionType; // 截面形式
  double length;                        // 吊柱长度(mm)
  double sectionSize;                   // 截面外径/边长(mm)
  double wallThickness;                 // 壁厚(mm)
  double topFlangeSize;                 // 上端法兰边长(mm)
  double topFlangeThick;               // 上端法兰厚度(mm)
  double bottomFlangeSize;              // 下端法兰边长(mm)
  double bottomFlangeThick;            // 下端法兰厚度(mm)
  double boltDiameter;                  // 法兰螺栓孔径(mm)
  double boltSpacing;                   // 法兰螺栓间距(mm)
};

TopoDS_Shape create_hanger_post(const hanger_post_params &params);
TopoDS_Shape create_hanger_post(const hanger_post_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction = gp::DZ());

// =========================================================================
// 22c. Portal Frame (梁顶门型架) TYPE=OCS_PORTAL_FRAME
// =========================================================================
struct portal_frame_params {
  double frameHeight;       // 门架高度(mm)
  double frameWidth;        // 门架宽度(mm)
  double postDiameter;      // 立柱外径(mm)
  double postWallThick;     // 立柱壁厚(mm)
  double beamDiameter;      // 横杆外径(mm)
  double beamWallThick;     // 横杆壁厚(mm)
  double beamLength;        // 横杆长度(mm)
  double basePlateLength;   // 底座板长(mm)
  double basePlateWidth;    // 底座板宽(mm)
  double basePlateThick;    // 底座板厚(mm)
  int hangPointCount;       // 悬挂点数量
  double hangPointSpacing;  // 悬挂点间距(mm)
  double boltSpacing;       // 底座螺栓孔距(mm)
  double boltDiameter;      // 底座螺栓孔径(mm)
};

TopoDS_Shape create_portal_frame(const portal_frame_params &params);
TopoDS_Shape create_portal_frame(const portal_frame_params &params,
                                  const gp_Pnt &position,
                                  const gp_Dir &direction = gp::DX(),
                                  const gp_Dir &upDir = gp::DZ());

// =========================================================================
// 22d. Suspension Cable (悬索) — shared by HeadSpan & SuspensionHardSpan
// =========================================================================
enum class suspension_cable_type {
  CATENARY = 1,     // 承力索(上凸弧线)
  FIXED_ROPE = 2,   // 固定绳(水平直线)
  DROPPER = 3       // 悬吊索(下凸弧线)
};

struct suspension_cable_params {
  gp_Pnt startPoint;
  gp_Pnt endPoint;
  double diameter;                // 索径(mm)
  double sag;                     // 弧垂(mm)
  suspension_cable_type cableType; // 索类型
  double tension;                 // 张拉力(kN, 仅记录不参与造型)
};

TopoDS_Shape create_suspension_cable(const suspension_cable_params &params);
TopoDS_Wire create_suspension_cable_centerline(const suspension_cable_params &params);

// =========================================================================
// 22e. Suspension Hard Span (悬索式硬横跨)
// =========================================================================
struct suspension_hard_span_params {
  double span;                    // 跨距(mm)
  double mastHeight;              // 立柱高度(mm)
  double mastWidth;               // 立柱宽度(mm)
  double cableDiameter;           // 主悬索直径(mm)
  double cableSag;                // 主悬索弧垂(mm)
  double dropperCableDiameter;    // 悬吊索直径(mm)
  int dropperCount;               // 悬吊索数量
  double dropperSpacing;          // 悬吊索间距(mm)
  double insulatorLength;         // 固定绳端部绝缘子长度(mm, 0=无)
  double insulatorDiameter;       // 固定绳端部绝缘子外径(mm)
};

TopoDS_Shape create_suspension_hard_span(const suspension_hard_span_params &params);
TopoDS_Shape create_suspension_hard_span(const suspension_hard_span_params &params,
                                          const gp_Pnt &position,
                                          const gp_Dir &direction = gp::DX(),
                                          const gp_Dir &upDir = gp::DZ());

// =========================================================================
// 22f. Positioning Cable (定位索) — shared with HeadSpan fixed ropes
// =========================================================================
struct positioning_cable_params {
  double diameter;         // 索径(mm)
  gp_Pnt topPoint;         // 上端锚点
  gp_Pnt bottomPoint;      // 下端锚点
  bool adjustable;         // 是否可调(带螺纹调节器)
};

TopoDS_Shape create_positioning_cable(const positioning_cable_params &params);

// =========================================================================
// 23. Auxiliary Wire Bracket (附加导线安装支架) TYPE=OCS_AUX_BRACKET
// =========================================================================
enum class aux_bracket_type {
  CROSS_ARM = 1,    // 横担式
  WALL_MOUNT = 2,   // 壁挂式
  DOUBLE_MAST = 3   // 双支柱式
};

struct aux_bracket_params {
  aux_bracket_type type;      // 类型
  double mountHeight;         // 安装高度(mm)
  double overhangLength;      // 悬挑长度(mm)
  double bracketLength;       // 支架长度(mm)
  double bracketWidth;        // 支架宽度(mm)
  double boltSpacing;         // 固定螺栓间距(mm)
  double boltDiameter;        // 固定螺栓直径(mm)
};

TopoDS_Shape create_aux_bracket(const aux_bracket_params &params);
TopoDS_Shape create_aux_bracket(const aux_bracket_params &params,
                                const gp_Pnt &position,
                                const gp_Dir &normal = gp::DX(),
                                const gp_Dir &upDir = gp::DZ());

// =========================================================================
// TRACK: 24. Rail (钢轨) TYPE=TRACK_RAIL
// =========================================================================
struct rail_params {
  double railHeight;        // 轨高(mm)
  double headWidth;         // 轨头宽(mm)
  double baseWidth;         // 轨底宽(mm)
  double webThickness;      // 轨腰厚(mm)
  double headHeight;        // 轨头高(mm)
  double baseHeight;        // 轨底高(mm)
  double headRadius;        // 轨头侧面曲率半径(mm)
  double standardLength;    // 标准长度(mm)
};

TopoDS_Shape create_rail(const rail_params &params);
TopoDS_Shape create_rail(const rail_params &params,
                         const gp_Pnt &startPoint,
                         const gp_Pnt &endPoint);

// =========================================================================
// TRACK: 25. Sleeper (轨枕) TYPE=TRACK_SLEEPER_CONC
// =========================================================================
// =========================================================================
// TRACK: 25. Sleeper (轨枕) TYPE=TRACK_SLEEPER_CONC
// =========================================================================

enum class sleeper_shape_type {
  RECTANGULAR = 1,   // 矩形 (木枕/简易)
  TRAPEZOIDAL = 2    // 梯形收腰 (混凝土枕, 底部宽顶部窄, 顶角圆角)
};

struct sleeper_params {
  sleeper_shape_type shapeType; // 类型
  double length;          // 长度(mm)
  double width;           // 宽度(mm)
  double height;          // 高度(mm)
  double gauge;           // 轨距(mm)
  double railBaseWidth;   // 钢轨底宽(mm), 用于承轨槽宽度
  double grooveDepth;     // 承轨槽深度(mm)
  double spacing;         // 间距(mm)
};

TopoDS_Shape create_sleeper(const sleeper_params &params);
TopoDS_Shape create_sleeper(const sleeper_params &params,
                            const gp_Pnt &position,
                            const gp_Dir &direction = gp::DX(),
                            const gp_Dir &upDir = gp::DZ());

// =========================================================================
// TRACK: 26. Ballast Bed (道床) TYPE=TRACK_BALLAST
// =========================================================================

// 曲线中心线类型
enum class centerline_curve_type {
  LINE = 0,  // 直线段
  ARC = 1,   // 圆弧段(3点)
  BEZIER = 2 // 贝塞尔段
};
struct centerline_segment {
  centerline_curve_type type;
  std::vector<gp_Pnt> points;
};

struct ballast_params {
  double topWidth;                            // 道床顶宽(mm)
  double thickness;                           // 道床厚度(mm)
  double sideSlope;                           // 道床边坡(1:n)
  std::vector<centerline_segment> centerlineSegments; // 曲线中心线(直线+圆弧+贝塞尔)
  double tiltAngle;                           // 超高倾角(rad), 绕路径切线旋转
};

TopoDS_Shape create_ballast(const ballast_params &params);

// =========================================================================
// TRACK: 27. Track Slab (轨道板) TYPE=TRACK_SLAB
// =========================================================================
struct track_slab_params {
  double length;                  // 板长(mm)
  double width;                   // 板宽(mm)
  double thickness;               // 板厚(mm)
  int railSeatCount;              // 承轨台数量
  double railSeatSpacing;         // 承轨台间距(mm)
  double cementAsphaltThickness;  // CA砂浆层厚度(mm)
};

TopoDS_Shape create_track_slab(const track_slab_params &params);
TopoDS_Shape create_track_slab(const track_slab_params &params,
                               const gp_Pnt &position,
                               const gp_Dir &direction = gp::DX(),
                               const gp_Dir &upDir = gp::DZ());

// =========================================================================
// TRACK: 28. Fastener (扣件) TYPE=TRACK_FASTENER
// =========================================================================
struct fastener_params {
  double spacing;          // 扣件间距(mm)
  double gauge;            // 轨距(mm)
  double padThickness;     // 轨下垫板厚(mm)
  double padLength;        // 垫板长(mm)
  double padWidth;         // 垫板宽(mm)
};

TopoDS_Shape create_fastener(const fastener_params &params);
TopoDS_Shape create_fastener(const fastener_params &params,
                             const gp_Pnt &position,
                             const gp_Dir &direction = gp::DX(),
                             const gp_Dir &upDir = gp::DZ());

// =========================================================================
// TRACK: 29. Guard Rail (护轨) TYPE=TRACK_GUARD_RAIL
// =========================================================================
struct guard_rail_params {
  double height;              // 护轨高度(mm)
  double headWidth;           // 轨头宽(mm)
  double baseWidth;           // 轨底宽(mm)
  double grooveWidth;         // 槽口宽(mm)
  double totalLength;         // 护轨全长(mm)
  double gaugeDistance;       // 护轨与基本轨距(mm)
};

TopoDS_Shape create_guard_rail(const guard_rail_params &params);
TopoDS_Shape create_guard_rail(const guard_rail_params &params,
                               const gp_Pnt &startPoint,
                               const gp_Pnt &endPoint);

// =========================================================================
// 30. MastAssembly (支柱装配) TYPE=OCS_MAST_ASSEMBLY
// =========================================================================
struct mast_assembly_params {
  int mastType;           // 1-格构式钢柱, 2-混凝土柱
  double mastHeight;      // 柱全高(mm)
  int cantileverType;     // 0-无, 1-单臂, 2-双臂
  bool hasCrossArm;       // 双臂时是否有横担
  double armDiameter;     // 腕臂管外径(mm)
  double stagger;         // 接触线拉出值(mm)
  int compType;           // 0-无, 1-棘轮, 2-滑轮
  double ratedTension;    // 设计补偿张力(kN)
  bool hasGuyWire;        // 是否设下锚拉线
};

TopoDS_Shape create_mast_assembly(const mast_assembly_params &params);
TopoDS_Shape create_mast_assembly(const mast_assembly_params &params,
                                  const gp_Pnt &position,
                                  const gp_Dir &direction = gp::DX(),
                                  const gp_Dir &upDir = gp::DZ());

// =========================================================================
// TRACK: 31. Switch Rail (尖轨)
// =========================================================================
struct switch_rail_params {
  double length;          // 尖轨长度(mm)
  double railHeight;      // 跟端轨高(mm)
  double railHeadWidth;   // 轨头宽(mm)
  double railBaseWidth;   // 轨底宽(mm)
  double webThickness;    // 轨腰厚(mm)
  double tipWidth;        // 尖端宽度(mm, 趋近0)
  double curveRadius;     // 曲线半径(mm, 0=直线尖轨)
  bool isLeftHand;        // 左开道岔使用
};

TopoDS_Shape create_switch_rail(const switch_rail_params &params);
TopoDS_Shape create_switch_rail(const switch_rail_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction = gp::DX(),
                                 const gp_Dir &upDir = gp::DZ());

// =========================================================================
// TRACK: 32. Frog (辙叉)
// =========================================================================
struct frog_params {
  int turnoutNo;             // 道岔号数 N
  double gauge;              // 轨距(mm)
  double railHeight;         // 轨高(mm)
  double railHeadWidth;      // 轨头宽(mm)
  double railBaseWidth;      // 轨底宽(mm)
};

TopoDS_Shape create_frog(const frog_params &params);
TopoDS_Shape create_frog(const frog_params &params,
                          const gp_Pnt &position,
                          const gp_Dir &direction = gp::DX(),
                          const gp_Dir &upDir = gp::DZ());

// =========================================================================
// TRACK: 34. Frog Auto-Calculation (辙叉自动查表) — KEPT, used by create_turnout
// =========================================================================
struct frog_calculated_params {
  int turnoutNo;
  double frogAngle;
  double leadCurveRadius;
  double switchRailLength;
  double frogTotalLength;
  double frogPointLength;
  double wingRailLength;
  double guardRailLength;
  double guardFlangeGroove;
  double throatWidth;
};

frog_calculated_params calculate_frog_params(int turnoutNo, double gauge);

struct turnout_params {
  int turnoutNo;               // 道岔号数
  bool isLeftHand;             // 左开/右开
  double gauge;                 // 轨距(mm)
  double railHeight;            // 轨高(mm)
  double railHeadWidth;         // 轨头宽(mm)
  double railBaseWidth;         // 轨底宽(mm)
  double webThickness;           // 轨腰厚(mm)
  double switchRailLength;      // 尖轨长度(mm)
  double leadCurveRadius;       // 导曲线半径(mm)
  double frogLength;            // 辙叉长度(mm)
  int sleeperCount;             // 岔枕数量
  double sleeperSpacing;        // 岔枕间距(mm)
};

TopoDS_Shape create_turnout(const turnout_params &params);
TopoDS_Shape create_turnout(const turnout_params &params,
                             const gp_Pnt &position,
                             const gp_Dir &direction = gp::DX(),
                              const gp_Dir &upDir = gp::DZ());

// =========================================================================
// TRACK: 35. Rail Pair (轨排对)
// =========================================================================
struct rail_pair_params {
  std::vector<gp_Pnt> centerline;  // 线路中心线坐标序列
  double gauge;                    // 轨距(mm)
  double superElevation;          // 超高(mm)
  double railHeight;               // 轨高(mm)
  double railHeadWidth;            // 轨头宽(mm)
  double railBaseWidth;            // 轨底宽(mm)
};

TopoDS_Shape create_rail_pair(const rail_pair_params &params);
TopoDS_Shape create_rail_pair(const rail_pair_params &params,
                               const gp_Pnt &position,
                               const gp_Dir &direction = gp::DX(),
                               const gp_Dir &upDir = gp::DZ());

// =========================================================================
// TRACK: 36. Sleeper Layout (轨枕阵列)
// =========================================================================
struct sleeper_layout_params {
  std::vector<gp_Pnt> centerline;  // 线路中心线
  double length;                   // 轨枕长度(mm)
  double width;                    // 轨枕宽度(mm)
  double height;                   // 轨枕高度(mm)
  double spacing;                  // 轨枕间距(mm)
  double gauge;                    // 轨距(mm)
};

TopoDS_Shape create_sleeper_layout(const sleeper_layout_params &params);

// =========================================================================
// TRACK: 37. Straight Track (直线轨道段)
// =========================================================================
struct straight_track_params {
  gp_Pnt startPoint;             // 起点
  gp_Pnt endPoint;               // 终点
  double gauge;                  // 轨距(mm)
  double railHeight;             // 轨高(mm)
  double railHeadWidth;          // 轨头宽(mm)
  double railBaseWidth;          // 轨底宽(mm)
  double webThickness;           // 轨腰厚(mm)
  double sleeperLength;          // 轨枕长度(mm)
  double sleeperWidth;           // 轨枕宽度(mm)
  double sleeperHeight;          // 轨枕高度(mm)
  double sleeperSpacing;         // 轨枕间距(mm)
  double ballastTopWidth;        // 道床顶宽(mm)
  double ballastThickness;       // 道床厚度(mm)
  double ballastSlope;           // 道床边坡
};

TopoDS_Shape create_straight_track(const straight_track_params &params);
TopoDS_Shape create_straight_track(const straight_track_params &params,
                                    const gp_Pnt &position,
                                    const gp_Dir &direction = gp::DX(),
                                    const gp_Dir &upDir = gp::DZ());

// =========================================================================
// TRACK: 38. Curve Track (曲线轨道段) — 含超高
// =========================================================================
struct curve_track_params {
  gp_Pnt curveCenter;            // 曲线中心
  double startAngle;             // 起始角度(rad)
  double sweepAngle;             // 扫掠角度(rad)
  double curveRadius;            // 曲线半径(mm)
  double gauge;                  // 轨距(mm)
  double superElevation;         // 超高(mm), 外轨抬高
  double railHeight;             // 轨高(mm)
  double railHeadWidth;          // 轨头宽(mm)
  double railBaseWidth;          // 轨底宽(mm)
  double webThickness;           // 轨腰厚(mm)
  double sleeperLength;          // 轨枕长度(mm)
  double sleeperWidth;           // 轨枕宽度(mm)
  double sleeperHeight;          // 轨枕高度(mm)
  double sleeperSpacing;         // 轨枕间距(mm)
  double ballastTopWidth;        // 道床顶宽(mm)
  double ballastThickness;       // 道床厚度(mm)
  double ballastSlope;           // 道床边坡
};

TopoDS_Shape create_curve_track(const curve_track_params &params);
TopoDS_Shape create_curve_track(const curve_track_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction = gp::DX(),
                                  const gp_Dir &upDir = gp::DZ());

// 支柱位姿计算结果 — 由 CalcOcsSpanPositions 推算
struct OcsMastPosition {
  double mileage;           // 里程(m)
  gp_Pnt position;          // 柱底中心坐标
  double mastHeight;        // 柱全高(mm)
  double beamBottomZ;       // 横梁底部 Z(mm) = contactHeight + structureHeight
  double contactWireZ;      // 接触线 Z(mm) = contactHeight
  double messengerWireZ;    // 承力索 Z(mm) = contactHeight + structureHeight
  double stagger;           // 拉出值 Y(mm), 之字形 ±200~400
  double hangerPostLength;  // 吊柱长度(mm), = mastHeight - beamBottomZ - 腕臂余量
  double bracketMountZ;     // 腕臂底座安装 Z(mm)
  double insulatorMountZ;   // 绝缘子连接座 Z(mm)
  double registrationArmZ;  // 定位器 Z(mm) = contactWireZ
  bool isTensionMast;       // 是否为锚柱(两端)
};

struct OcsSpanCalcInput {
  std::vector<gp_Pnt> centerline;  // 线路中心线 XY 序列
  double contactHeight;            // 导高(mm), 默认 5300
  double structureHeight;          // 结构高度(mm), 默认 1400
  std::vector<double> staggerTable; // 各定位点拉出值(mm)
  double spanLength;               // 标准跨距(mm), 默认 50000
  double mastHeight;               // 支柱高度(mm)
  bool hasCompensator;             // 是否两端设补偿装置
};

struct OcsSpanCalcOutput {
  std::vector<OcsMastPosition> masts;  // 各支柱计算结果
  double totalLength;                  // 总跨距(mm)
  int mastCount;                       // 支柱数量
  double beamBottomZ;                  // 横梁底部 Z(全局)
  double contactWireZ;                 // 接触线 Z
  double messengerWireZ;               // 承力索 Z
};

// 从中心线+高层参数推算各支柱的全部位姿
OcsSpanCalcOutput calc_ocs_span_positions(const OcsSpanCalcInput &input);

// =========================================================================
// 9b. Registration Arm Bracket (定位器底座 L型金具) TYPE=OCS_REG_BRACKET
// =========================================================================
struct reg_arm_bracket_params {
  double tubeDiameter;       // 抱箍内径(mm), 腕臂管径
  double bandWidth;          // 抱箍宽度(mm)
  double bandThickness;      // 抱箍壁厚(mm)
  double bracketHeight;      // L型弯板高度(mm), 从管心到定位器座
  double bracketThickness;   // 弯板厚度(mm)
  double bracketWidth;       // 弯板宽度(mm)
  double mountHoleDiameter;  // 定位器销轴孔径(mm)
};

TopoDS_Shape create_reg_arm_bracket(const reg_arm_bracket_params &params);
  TopoDS_Shape create_reg_arm_bracket(const reg_arm_bracket_params &params,
                                      const gp_Pnt &position,
                                      const gp_Dir &tubeDir = gp::DX(),
                                      const gp_Dir &upDir = gp::DZ());

// =========================================================================
// POINT/LINE-DRIVEN TRACK — element-specific public API
// =========================================================================

// Curve types for track element paths
enum class curve_type { LINE = 0, ARC = 1, BEZIER = 2 };
enum class profile_type { RAIL = 0, CHANNEL = 1, PLATE = 2 };
enum class end_treatment_type { PLANE = 0, SWITCH = 1, SCARF = 2, BELL = 3 };

// End treatment for curve elements (尖轨/斜切/喇叭口)
struct end_treatment_params {
  end_treatment_type type = end_treatment_type::PLANE;
  double toeWidth = 2.0;          // 尖轨尖端宽度
  double switchLength = 0.0;      // 尖轨段长度
  double planedStart = 0.0;       // 刨削起始位置
  int switchType = 1;             // 1-直线尖轨, 2-曲线尖轨
  double dropValue = 0.0;         // 尖端降低值
  double scarfAngle = 45.0;       // 斜切角度°
  double bellLength = 500.0;      // 喇叭口长度
};

// Curve path definition
struct curve_params {
  curve_type type = curve_type::LINE;
  gp_Pnt startPoint;
  gp_Pnt endPoint;
  std::vector<gp_Pnt> controlPoints; // BEZIER
  double radius = 0.0;               // ARC
  int arcDirection = 1;              // 1-left, 2-right
};

// ========== 钢轨（独立曲线） ==========
struct rail_curve_params {
  curve_params curve;                    // 空间路径
  end_treatment_params endStart;         // 起点端部
  end_treatment_params endFinish;        // 终点端部
  double railHeight = 176.0;
  double headWidth = 73.0;
  double baseWidth = 150.0;
  double webThickness = 16.5;
  double headHeight = 48.0;
  double baseHeight = 28.0;
  double headRadius = 13.0;
};

TopoDS_Shape create_rail_curve(const rail_curve_params &params);

// ========== 翼轨（独立曲线） ==========
struct wing_rail_curve_params {
  curve_params curve;
  end_treatment_params endStart;
  end_treatment_params endFinish;
  profile_type profile = profile_type::CHANNEL; // CHANNEL or RAIL
  double channelHeight = 120.0;
  double grooveWidth = 45.0;
  double flangeWidth = 20.0;
  double webThickness = 12.0;
  double grooveThickness = 15.0;
  int endConnection = 1;               // 1-weld, 2-bolt, 3-spacer
};

TopoDS_Shape create_wing_rail_curve(const wing_rail_curve_params &params);

// ========== 护轨（独立曲线） ==========
struct guard_rail_curve_params {
  curve_params curve;
  end_treatment_params endStart;        // BELL end typical
  end_treatment_params endFinish;
  profile_type profile = profile_type::CHANNEL;
  double channelHeight = 120.0;
  double grooveWidth = 45.0;
  double flangeWidth = 20.0;
  double webThickness = 12.0;
  double grooveThickness = 15.0;
  double raiseHeight = 0.0;             // 高出基本轨量
};

TopoDS_Shape create_guard_rail_curve(const guard_rail_curve_params &params);

// ========== 枕木（直线） ==========
struct sleeper_line_params {
  gp_Pnt startPoint;                     // 左端
  gp_Pnt endPoint;                       // 右端
  double width = 260.0;
  double height = 200.0;
  double grooveDepth = 8.0;
  bool hasEndSlope = true;
  int sleeperType = 2;                   // 1-YIIF, 2-III, 3-桥枕
  double gauge = 1435.0;
  double railBaseWidth = 150.0;          // 钢轨底宽(承轨槽宽)
  int shapeType = 1;                     // 1-RECTANGULAR, 2-TRAPEZOIDAL(鱼腹式)
};

TopoDS_Shape create_sleeper_line(const sleeper_line_params &params);

// ========== 扣件（点） ==========
struct fastener_point_params {
  gp_Pnt position;                       // 安装位置
  double rotation = 0.0;                 // 绕Z轴旋转°
  int side = 3;                          // 1-LEFT, 2-RIGHT, 3-BOTH
  int type = 1;                          // 1-弹条I型, 2-II型, 3-III型, 4-WJ-7, 5-WJ-8
  double padThickness = 10.0;
};

TopoDS_Shape create_fastener_point(const fastener_point_params &params);

// ========== 减速顶（点） ==========
struct retarder_point_params {
  gp_Pnt position;
  double rotation = 0.0;
  int side = 1;
  int type = 1;                          // 1-液压, 2-摩擦, 3-可控
  int mountType = 1;                     // 1-轨内侧, 2-轨外侧, 3-双轨双侧
  double height = 80.0;
  double length = 300.0;
  double width = 150.0;
};

TopoDS_Shape create_retarder_point(const retarder_point_params &params);

// ========== 道床（由枕木线驱动） ==========
struct ballast_from_sleepers_params {
  std::vector<sleeper_line_params> sleepers;
  double topWidth = 3600.0;
  double thickness = 300.0;
  double sideSlope = 1.5;
  int sectionType = 1;                   // 1-路基梯形, 2-桥梁梯形, 3-隧道矩形
};

TopoDS_Shape create_ballast_from_sleepers(const ballast_from_sleepers_params &params);

// ========== 道岔（由独立元素组合） ==========
struct turnout_assembly_params {
  int turnoutNo = 12;
  int hand = 1;
  double gauge = 1435.0;
  std::vector<rail_curve_params> rails;
  std::vector<wing_rail_curve_params> wingRails;
  std::vector<guard_rail_curve_params> guardRails;
  std::vector<sleeper_line_params> sleepers;
  std::vector<fastener_point_params> fasteners;
};

TopoDS_Shape create_turnout_assembly(const turnout_assembly_params &params);
TopoDS_Shape create_turnout_assembly(const turnout_assembly_params &params,
                                     const gp_Pnt &position,
                                     const gp_Dir &direction = gp::DX(),
                                     const gp_Dir &upDir = gp::DZ());

// ========== 钢轨伸缩调节器 ==========
struct expansion_joint_params {
  rail_curve_params stockRail;
  rail_curve_params switchRail;
  double expansionCapacity = 400.0;
  double gauge = 1435.0;
};

TopoDS_Shape create_expansion_joint(const expansion_joint_params &params);
TopoDS_Shape create_expansion_joint(const expansion_joint_params &params,
                                    const gp_Pnt &position,
                                    const gp_Dir &direction = gp::DX(),
                                    const gp_Dir &upDir = gp::DZ());

} // namespace topo
} // namespace flywave
