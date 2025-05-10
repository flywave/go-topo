#pragma once

#include <TopoDS_Shape.hxx>
#include <gp_Ax2.hxx>
#include <gp_Dir.hxx>
#include <gp_Pnt.hxx>
#include <vector>

#include <boost/variant.hpp>

namespace flywave {
namespace topo {

struct sphere_params {
  double radius;
};

TopoDS_Shape create_sphere(const sphere_params &params);
TopoDS_Shape create_sphere(const sphere_params &params, const gp_Pnt &center);

struct rotational_ellipsoid_params {
  double polarRadius;      // 极半径 (LR)
  double equatorialRadius; // 赤道半径 (ER)
  double height;           // 高度 (H)
};

TopoDS_Shape
create_rotational_ellipsoid(const rotational_ellipsoid_params &params);
TopoDS_Shape
create_rotational_ellipsoid(const rotational_ellipsoid_params &params,
                            const gp_Pnt &center,
                            const gp_Dir &xDirection = gp_Dir(1, 0, 0));

struct cuboid_params {
  double length; // 长度 (L, X轴方向)
  double width;  // 宽度 (W, Y轴方向)
  double height; // 高度 (H, Z轴方向)
};

TopoDS_Shape create_cuboid(const cuboid_params &params);

TopoDS_Shape create_cuboid(const cuboid_params &params, const gp_Pnt &center,
                           const gp_Dir &xDirection = gp_Dir(1, 0, 0),
                           const gp_Dir &zDirection = gp_Dir(0, 0, 1));
struct diamond_frustum {
  double topDiag1;    // 顶面对角线1长度 (TL1=1680)
  double topDiag2;    // 顶面对角线2长度 (TL2=970)
  double bottomDiag1; // 底面对角线1长度 (LL1=1080)
  double bottomDiag2; // 底面对角线2长度 (LL2=620)
  double height;      // 高度 (H)
};

TopoDS_Shape create_diamond_frustum(const diamond_frustum &params);

TopoDS_Shape create_diamond_frustum(const diamond_frustum &params,
                                    const gp_Pnt &position,
                                    const gp_Dir &normal = gp_Dir(0, 0, 1),
                                    const gp_Dir &xDir = gp_Dir(1, 0, 0));
struct offset_rectangular_table_params {
  double topLength;    // 上部矩形长度 (L1)
  double topWidth;     // 上部矩形宽度 (W1)
  double bottomLength; // 下部矩形长度 (L2)
  double bottomWidth;  // 下部矩形宽度 (W2)
  double height;       // 高度 (H)
  double xOffset;      // X方向偏移 (X)
  double yOffset;      // Y方向偏移 (Y)
};

TopoDS_Shape
create_offset_rectangular_table(const offset_rectangular_table_params &params);
TopoDS_Shape
create_offset_rectangular_table(const offset_rectangular_table_params &params,
                                const gp_Pnt &position,
                                const gp_Dir &normal = gp_Dir(0, 0, 1),
                                const gp_Dir &xDir = gp_Dir(1, 0, 0));

struct cylinder_params {
  double radius; // 半径 (R)
  double height; // 高度 (H)
};
TopoDS_Shape create_cylinder(const cylinder_params &params);

TopoDS_Shape create_cylinder(const cylinder_params &params,
                             const gp_Pnt &baseCenter,
                             const gp_Dir &axisDirection = gp_Dir(0, 0, 1));

struct sharp_bent_cylinder_params {
  double radius;    // 圆柱半径 (R > 0)
  double length;    // 直线段长度 (L > 0)
  double bendAngle; // 弯折弧度 (0 < Rad < PI)
};

TopoDS_Shape
create_sharp_bent_cylinder(const sharp_bent_cylinder_params &params);
TopoDS_Shape
create_sharp_bent_cylinder(const sharp_bent_cylinder_params &params,
                           const gp_Pnt &bendPoint,
                           const gp_Dir &initialDir = gp::DX(),
                           const gp_Dir &bendPlaneNormal = gp::DZ());

struct truncated_cone_params {
  double topRadius;    // 顶部半径 (R1 > 0)
  double bottomRadius; // 底部半径 (R2 > 0)
  double height;       // 高度 (H > 0)
};
TopoDS_Shape create_truncated_cone(const truncated_cone_params &params);
TopoDS_Shape create_truncated_cone(const truncated_cone_params &params,
                                   const gp_Pnt &baseCenter,
                                   const gp_Dir &axisDirection = gp_Dir(0, 0,
                                                                        1));
struct eccentric_truncated_cone_params {
  double topRadius;    // 顶部半径 (TR ≥ 0)
  double bottomRadius; // 底部半径 (BR ≥ TR)
  double height;       // 高度 (H > 0)
  double topXOffset;   // X方向顶部偏移 (TOPXOFF ≥ 0)
  double topYOffset;   // Y方向顶部偏移  (TOPYOFF ≥ 0)
};
TopoDS_Shape
create_eccentric_truncated_cone(const eccentric_truncated_cone_params &params);
TopoDS_Shape
create_eccentric_truncated_cone(const eccentric_truncated_cone_params &params,
                                const gp_Pnt &baseCenter,
                                const gp_Dir &axisDirection = gp_Dir(0, 0, 1));

struct ring_params {
  double ringRadius; // 环半径 (R > 0)
  double tubeRadius; // 管半径 (0 < DR < R)
  double angle;      // 旋转角度(弧度) (0 < Rad ≤ 2PI)
};
TopoDS_Shape create_ring(const ring_params &params);
TopoDS_Shape create_ring(const ring_params &params, const gp_Pnt &center,
                         const gp_Dir &normal = gp::DZ(),
                         const gp_Dir &xDir = gp::DX());

struct rectangular_ring_params {
  double tubeRadius;   // 管半径 (0 < DR < W)
  double filletRadius; // 倒角半径 (R < W/2)
  double length;       // 环长度 (L > W)
  double width;        // 环宽度 (W > 0)
};
TopoDS_Shape create_rectangular_ring(const rectangular_ring_params &params);
TopoDS_Shape create_rectangular_ring(const rectangular_ring_params &params,
                                     const gp_Pnt &center,
                                     const gp_Dir &normal = gp::DZ(),
                                     const gp_Dir &xDir = gp::DX());
struct elliptic_ring_params {
  double tubeRadius;  // 管半径 (0 < DR < W)
  double majorRadius; // 长半轴 (L > W)
  double minorRadius; // 短半轴 (W > 0)
};

TopoDS_Shape create_elliptic_ring(const elliptic_ring_params &params);
TopoDS_Shape create_elliptic_ring(const elliptic_ring_params &params,
                                  const gp_Pnt &center,
                                  const gp_Dir &normal = gp::DZ(),
                                  const gp_Dir &xDir = gp::DX());
struct circular_gasket_params {
  double outerRadius; // 外围半径 (OR > IR)
  double innerRadius; // 内围半径 (0 < IR < OR)
  double height;      // 高度 (H > 0)
  double angle;       // 弧度 (0 < Rad ≤ 2PI)
};

TopoDS_Shape create_circular_gasket(const circular_gasket_params &params);
TopoDS_Shape create_circular_gasket(const circular_gasket_params &params,
                                    const gp_Pnt &center,
                                    const gp_Dir &normal = gp::DZ(),
                                    const gp_Dir &xDir = gp::DX());
struct table_gasket_params {
  double topRadius;   // 顶部外围半径 (IR < TR < OR)
  double outerRadius; // 底部外围半径 (OR > TR)
  double innerRadius; // 内围半径 (0 < IR < TR)
  double height;      // 高度 (H > 0)
  double angle;       // 弧度 (0 < Rad ≤ 2PI)
};

TopoDS_Shape create_table_gasket(const table_gasket_params &params);
TopoDS_Shape create_table_gasket(const table_gasket_params &params,
                                 const gp_Pnt &center,
                                 const gp_Dir &normal = gp::DZ(),
                                 const gp_Dir &xDir = gp::DX());
struct square_gasket_params {
  double outerLength; // 外围长度 (L > W)
  double outerWidth;  // 外围宽度 (W > 0)
  double innerLength; // 内围长度 (0 < IL < L)
  double innerWidth;  // 内围宽度 (0 < IW < W)
  double height;      // 高度 (H > 0)
  int cornerType;     // 角点类型 (1: 圆形, 2: 矩形, 3: 椭圆)
  double cornerParam; // 角点参数 (根据cornerType设置)
};

TopoDS_Shape create_square_gasket(const square_gasket_params &params);
TopoDS_Shape create_square_gasket(const square_gasket_params &params,
                                  const gp_Pnt &center,
                                  const gp_Dir &normal = gp::DZ(),
                                  const gp_Dir &xDir = gp::DX());
struct stretched_body_params {
  std::vector<gp_Pnt> points; // 底面顶点坐标数组
  gp_Dir normal;              // 拉伸方向向量
  double length;              // 拉伸长度 (L > 0)
};

TopoDS_Shape create_stretched_body(const stretched_body_params &params);
TopoDS_Shape create_stretched_body(const stretched_body_params &params,
                                   const gp_Pnt &basePoint,
                                   const gp_Dir &xDir = gp::DX());
struct porcelain_bushing_params {
  double height;           // 总高度 (H > 0)
  double radius;           // 瓷套外半径 (R > 0)
  double bigSkirtRadius;   // 大伞裙半径 (R1 ≥ R2)
  double smallSkirtRadius; // 小伞裙半径 (R2 > R)
  int count;               // 伞裙片数 (N > 0)
};
TopoDS_Shape create_porcelain_bushing(const porcelain_bushing_params &params);
TopoDS_Shape create_porcelain_bushing(const porcelain_bushing_params &params,
                                      const gp_Pnt &basePoint,
                                      const gp_Dir &axisDirection = gp::DZ());

struct cone_porcelain_bushing_params {
  double height;             // 总高度 (H > 0)
  double bottomRadius;       // 底部绝缘子半径 (BR > 0)
  double topRadius;          // 顶部绝缘子半径 (TR > 0)
  double bottomSkirtRadius1; // 底部伞裙半径1 (BR1 > BR)
  double bottomSkirtRadius2; // 底部伞裙半径2 (BR2 > BR)
  double topSkirtRadius1;    // 顶部伞裙半径1 (TR1 > TR)
  double topSkirtRadius2;    // 顶部伞裙半径2 (TR2 > TR)
  int count;                 // 伞裙片数 (N > 0)
};

TopoDS_Shape
create_cone_porcelain_bushing(const cone_porcelain_bushing_params &params);
TopoDS_Shape
create_cone_porcelain_bushing(const cone_porcelain_bushing_params &params,
                              const gp_Pnt &basePoint,
                              const gp_Dir &axisDirection = gp::DZ());

struct insulator_string_params {
  int count;               // 联数 (N > 0)
  double spacing;          // 双串间距 (D > 2*R1)
  int insulatorCount;      // 单串绝缘子片数量 (N1 > 0)
  double height;           // 绝缘子单片连接高度 (H1 > 0)
  double bigSkirtRadius;   // 大伞裙半径 (R1 ≥ R2)
  double smallSkirtRadius; // 小伞裙半径 (R2 > R)
  double radius;           // 绝缘子串半径 (R > 0)
  double frontLength;      // 前端长度（构架端） (FL > 0)
  double backLength;       // 后端长度（导线端） (AL > 0)
  int splitCount;          // 连接导线分裂数 (LN > 0)
};
TopoDS_Shape create_insulator_string(const insulator_string_params &params);
TopoDS_Shape create_insulator_string(const insulator_string_params &params,
                                     const gp_Pnt &position,
                                     const gp_Dir &direction = gp_Dir(0, 1, 0),
                                     const gp_Dir &upDirection = gp_Dir(1, 0,
                                                                        0));

struct vtype_insulator_params {
  double frontSpacing;     // 前端间距 (X > 0)
  double backSpacing;      // 后端间距 (AD > 0)
  int insulatorCount;      // 单串绝缘子片数量 (N1 > 0)
  double height;           // 绝缘子单片连接高度 (H1 > 0)
  double radius;           // 伞顶面半径 (R > 0)
  double bigSkirtRadius;   // 大伞半径 (R1 > R2)
  double smallSkirtRadius; // 小伞半径 (R2 > 0)
  double frontLength;      // 前段长度（构架端） (FL > 0)
  double backLength;       // 后段长度（导线端） (AL > 0)
  int splitCount;          // 连接导线分裂数 (LN > 0)
};
TopoDS_Shape create_vtype_insulator(const vtype_insulator_params &params);
TopoDS_Shape create_vtype_insulator(const vtype_insulator_params &params,
                                    const gp_Pnt &position,
                                    const gp_Dir &direction = gp_Dir(0, 1, 0),
                                    const gp_Dir &upDirection = gp_Dir(1, 0,
                                                                       0));

struct terminal_block_params {
  double length;        // 长度 (L > W)
  double width;         // 宽度 (W > 0)
  double thickness;     // 厚度 (T > 0)
  double chamferLength; // 倒角边长 (CL > 0)
  double columnSpacing; // 孔列间距 (CS > 0)
  double rowSpacing;    // 孔行间距 (RS > 0)
  double holeRadius;    // 孔半径 (R > 0)
  int columnCount;      // 开孔列数 (CN > 0)
  int rowCount;         // 开孔行数 (RN > 0)
  double bottomOffset;  // 孔行距底边距离 (BL > 0)
};
TopoDS_Shape create_terminal_block(const terminal_block_params &params);
TopoDS_Shape create_terminal_block(const terminal_block_params &params,
                                   const gp_Pnt &position,
                                   const gp_Dir &lengthDir = gp_Dir(0, 0, 1),
                                   const gp_Dir &widthDir = gp_Dir(1, 0, 0));

struct rectangular_hole_plate_params {
  double length;        // 长度 (L > 0)
  double width;         // 宽度 (W > 0)
  double thickness;     // 厚度 (T > 0)
  double columnSpacing; // 孔列间距 (CS > 0)
  double rowSpacing;    // 孔行间距 (RS > 0)
  int columnCount;      // 开孔列数 (CN > 0)
  int rowCount;         // 开孔行数 (RN > 0)
  int hasMiddleHole;    // 是否有中间孔 (MH = 1/0)
  double holeDiameter;  // 孔直径 (D > 0)
};
TopoDS_Shape
create_rectangular_fixed_plate(const rectangular_hole_plate_params &params);
TopoDS_Shape
create_rectangular_fixed_plate(const rectangular_hole_plate_params &params,
                               const gp_Pnt &position,
                               const gp_Dir &lengthDir = gp_Dir(1, 0, 0),
                               const gp_Dir &widthDir = gp_Dir(0, 1, 0));

struct circular_fixed_plate_params {
  double length;       // 长度 (L > 0)
  double width;        // 宽度 (W > 0)
  double thickness;    // 厚度 (T > 0)
  double ringRadius;   // 开孔环半径 (CS > 0)
  int holeCount;       // 开孔数 (N > 0)
  int hasMiddleHole;   // 是否有中间孔 (MH = 1/0)
  double holeDiameter; // 孔直径 (D > 0)
};
TopoDS_Shape
create_circular_fixed_plate(const circular_fixed_plate_params &params);
TopoDS_Shape
create_circular_fixed_plate(const circular_fixed_plate_params &params,
                            const gp_Pnt &position,
                            const gp_Dir &lengthDir = gp_Dir(1, 0, 0),
                            const gp_Dir &widthDir = gp_Dir(0, 1, 0));

/**
 * @brief 创建导线图元
 *
 * @param startPoint 起点坐标
 * @param endPoint 终点坐标
 * @param startDir 起始出线方向
 * @param endDir 终止出线方向
 * @param sag 导线弧垂 (Sag > 0)
 * @param diameter 导线直径 (D > 0)
 * @param fitPoints 拟合点集 (至少2个点)
 * @return TopoDS_Shape 生成的导线形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
struct wire_params {
  gp_Pnt startPoint;             // 起点坐标
  gp_Pnt endPoint;               // 终点坐标
  gp_Dir startDir;               // 起始出线方向
  gp_Dir endDir;                 // 终止出线方向
  double sag;                    // 导线弧垂 (Sag > 0)
  double diameter;               // 导线直径 (D > 0)
  std::vector<gp_Pnt> fitPoints; // 拟合点集 (至少2个点)
};
TopoDS_Shape create_wire(const wire_params &params);
TopoDS_Shape create_wire(const wire_params &params, const gp_Pnt &position,
                         const gp_Dir &direction = gp_Dir(0, 1, 0),
                         const gp_Dir &upDirection = gp_Dir(1, 0, 0));

/**
 * @brief 创建电缆图元
 *
 * @param startPoint 起点坐标
 * @param endPoint 终点坐标
 * @param inflectionPoints 虚交点坐标数组
 * @param radii 虚交点转弯半径数组
 * @param diameter 电缆直径 (D > 0)
 * @return TopoDS_Shape 生成的电缆形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
struct cable_params {
  gp_Pnt startPoint;                    // 起点坐标
  gp_Pnt endPoint;                      // 终点坐标
  std::vector<gp_Pnt> inflectionPoints; // 虚交点坐标数组
  std::vector<double> radii;            // 虚交点转弯半径数组
  double diameter;                      // 电缆直径 (D > 0)
};
TopoDS_Shape create_cable(const cable_params &params);
TopoDS_Shape create_cable(const cable_params &params, const gp_Pnt &position,
                          const gp_Dir &direction = gp_Dir(0, 1, 0),
                          const gp_Dir &upDirection = gp_Dir(1, 0, 0));

// 曲线类型枚举
enum class curve_type {
  LINE = 0,  // 直线
  ARC = 1,   // 弧线
  SPLINE = 2 // 样条曲线
};

// 曲线电缆参数结构体
struct curve_cable_params {
  std::vector<std::vector<gp_Pnt>> controlPoints; // 控制点集合
  std::vector<curve_type> curveTypes;             // 曲线类型数组
  double diameter;                                // 电缆直径
};

/**
 * @brief 创建曲线电缆
 * @param params 曲线电缆参数结构体
 * @return TopoDS_Shape 生成的电缆形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_curve_cable(const curve_cable_params &params);
TopoDS_Shape create_curve_cable(const curve_cable_params &params,
                                const gp_Pnt &position,
                                const gp_Dir &direction = gp_Dir(0, 1, 0),
                                const gp_Dir &upDirection = gp_Dir(1, 0, 0));

/**
 * @brief 角钢参数结构体
 */
struct angle_steel_params {
  double L1;     // 长边长度 (L1 > 0)
  double L2;     // 短边长度 (0 < L2 < L1)
  double X;      // 厚度 (0 < X < min(L1,L2))
  double length; // 长度 (length > 0)
};

TopoDS_Shape create_angle_steel(const angle_steel_params &params);
TopoDS_Shape create_angle_steel(const angle_steel_params &params,
                                const gp_Pnt &position,
                                const gp_Dir &xDirection = gp::DX(),
                                const gp_Dir &longEdgeDir = gp::DZ());

/**
 * @brief 工字钢参数结构体
 */
struct i_shaped_steel_params {
  double height;          // 总高度 (H > 0)
  double flangeWidth;     // 翼缘宽度 (B > 0)
  double webThickness;    // 腹板厚度 (t1 > 0)
  double flangeThickness; // 翼缘厚度 (t2 > 0)
  double length;          // 长度 (L > 0)
};

TopoDS_Shape create_i_shaped_steel(const i_shaped_steel_params &params);
TopoDS_Shape create_i_shaped_steel(const i_shaped_steel_params &params,
                                   const gp_Pnt &position,
                                   const gp_Dir &xDirection = gp::DX(),
                                   const gp_Dir &zDirection = gp::DZ());

/**
 * @brief 槽钢参数结构体
 */
struct channel_steel_params {
  double height;          // 总高度 (H > 0)
  double flangeWidth;     // 翼缘宽度 (B > 0)
  double webThickness;    // 腹板厚度 (t1 > 0)
  double flangeThickness; // 翼缘厚度 (t2 > 0)
  double length;          // 长度 (L > 0)
};

TopoDS_Shape create_channel_steel(const channel_steel_params &params);
TopoDS_Shape create_channel_steel(const channel_steel_params &params,
                                  const gp_Pnt &position,
                                  const gp_Dir &xDirection = gp::DX(),
                                  const gp_Dir &zDirection = gp::DZ());

/**
 * @brief T型钢参数结构体
 */
struct t_steel_params {
  double height;          // 高度 (H > 0)
  double width;           // 宽度 (W > 0)
  double webThickness;    // 腹板厚度 (T1 > 0)
  double flangeThickness; // 翼缘厚度 (T2 > 0)
  double length;          // 长度 (L > 0)
};

TopoDS_Shape create_t_steel(const t_steel_params &params);
TopoDS_Shape create_t_steel(const t_steel_params &params,
                            const gp_Pnt &position,
                            const gp_Dir &xDirection = gp::DX(),
                            const gp_Dir &zDirection = gp::DZ());

struct bored_pile_params {
  double H1; // 上部圆柱高度
  double H2; // 过渡段高度
  double H3; // 底部圆柱高度
  double H4; // 桩头高度
  double d;  // 上部直径
  double D;  // 底部直径
};
TopoDS_Shape create_bored_pile_base(const bored_pile_params &params);
TopoDS_Shape create_bored_pile_base(const bored_pile_params &params,
                                    const gp_Pnt &position,
                                    const gp_Dir &direction = gp::DZ());

struct pile_cap_params {
  // 高度参数
  double H1; // 桩上部圆柱高度
  double H2; // 桩过渡段高度
  double H3; // 桩底部圆柱高度
  double H4; // 承台柱高度
  double H5; // 承台底板高度
  double H6; // 桩头高度

  // 直径/尺寸参数
  double d;  // 桩上部直径
  double D;  // 桩底部直径
  double b;  // 承台柱直径/边长
  double B1; // 承台底板宽度
  double L1; // 承台底板长度

  // 偏心参数
  double e1; // X方向偏心
  double e2; // Y方向偏心

  // 承台柱样式
  int cs; // 0=圆形, 1=方形

  // 桩参数
  int ZCOUNT;                     // 桩数量
  std::vector<gp_Pnt> ZPOSTARRAY; // 桩位置数组
};

TopoDS_Shape create_pile_cap_base(const pile_cap_params &params);
TopoDS_Shape create_pile_cap_base(const pile_cap_params &params,
                                  const gp_Pnt &position,
                                  const gp_Dir &direction = gp::DZ());

struct rock_anchor_params {
  // 高度参数
  double H1; // 基础底板高度
  double H2; // 锚桩长度

  // 尺寸参数
  double d;  // 锚桩直径
  double B1; // 底板宽度
  double L1; // 底板长度

  // 锚桩参数
  int ZCOUNT;                     // 锚桩数量
  std::vector<gp_Pnt> ZPOSTARRAY; // 锚桩位置数组
};

TopoDS_Shape create_rock_anchor_base(const rock_anchor_params &params);
TopoDS_Shape create_rock_anchor_base(const rock_anchor_params &params,
                                     const gp_Pnt &position,
                                     const gp_Dir &direction = gp::DZ());

struct rock_pile_cap_params {
  // 高度参数
  double H1; // 承台柱高度
  double H2; // 承台底板高度
  double H3; // 锚桩长度

  // 尺寸参数
  double d;  // 锚桩直径
  double b;  // 承台柱直径/边长
  double B1; // 承台底板宽度
  double L1; // 承台底板长度

  // 偏心参数
  double e1; // X方向偏心
  double e2; // Y方向偏心

  // 承台柱样式
  int cs; // 0=圆形, 1=方形

  // 锚桩参数
  int ZCOUNT;                     // 锚桩数量
  std::vector<gp_Pnt> ZPOSTARRAY; // 锚桩位置数组
};

TopoDS_Shape create_rock_pile_cap_base(const rock_pile_cap_params &params);
TopoDS_Shape create_rock_pile_cap_base(const rock_pile_cap_params &params,
                                       const gp_Pnt &position,
                                       const gp_Dir &direction = gp::DZ());

struct embedded_rock_anchor_params {
  // 高度参数
  double H1; // 上部圆柱高度
  double H2; // 过渡段高度
  double H3; // 底部圆柱高度

  // 直径参数
  double d; // 上部直径
  double D; // 底部直径
};

TopoDS_Shape
create_embedded_rock_anchor_base(const embedded_rock_anchor_params &params);
TopoDS_Shape
create_embedded_rock_anchor_base(const embedded_rock_anchor_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction = gp::DZ());

struct inclined_rock_anchor_params {
  // 高度参数
  double H1; // 基础底板高度
  double H2; // 锚桩长度

  // 直径参数
  double d; // 锚桩直径
  double D; // 底部扩大头直径

  // 底板尺寸
  double B; // 底板宽度
  double L; // 底板长度

  // 偏心参数
  double e1; // X方向偏心
  double e2; // Y方向偏心

  // 坡度参数(度)
  double alpha1; // X轴坡度
  double alpha2; // Y轴坡度
};

TopoDS_Shape
create_inclined_rock_anchor_base(const inclined_rock_anchor_params &params);
TopoDS_Shape
create_inclined_rock_anchor_base(const inclined_rock_anchor_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction = gp::DZ());

struct excavated_base_params {
  // 高度参数
  double H1; // 上部圆柱高度
  double H2; // 过渡段高度
  double H3; // 底部圆柱高度

  // 直径参数
  double d; // 上部直径
  double D; // 底部直径

  // 坡度参数(度)
  double alpha1; // X轴坡度
  double alpha2; // Y轴坡度
};

TopoDS_Shape create_excavated_base(const excavated_base_params &params);
TopoDS_Shape create_excavated_base(const excavated_base_params &params,
                                   const gp_Pnt &position,
                                   const gp_Dir &direction = gp::DZ());

struct step_base_params {
  // 高度参数
  double H;  // 基础总高度
  double H1; // 第一级台阶高度
  double H2; // 第二级台阶高度
  double H3; // 第三级台阶高度

  // 尺寸参数
  double b;  // 基础顶部宽度
  double B1; // 第一级台阶宽度
  double B2; // 第二级台阶宽度
  double B3; // 第三级台阶宽度
  double L1; // 第一级台阶长度
  double L2; // 第二级台阶长度
  double L3; // 第三级台阶长度

  // 台阶参数
  int N; // 台阶数量(1-3)
};

TopoDS_Shape create_step_base(const step_base_params &params);
TopoDS_Shape create_step_base(const step_base_params &params,
                              const gp_Pnt &position,
                              const gp_Dir &direction = gp::DZ());

struct step_plate_base_params {
  // 高度参数
  double H;  // 基础总高度
  double H1; // 第一级台阶高度
  double H2; // 第二级台阶高度
  double H3; // 第三级台阶高度

  // 尺寸参数
  double b;  // 柱顶宽度/直径
  double L1; // 第一级台阶长度
  double L2; // 第二级台阶长度
  double B1; // 基础底板宽度
  double B2; // 第一级台阶宽度

  // 坡度参数(度)
  double alpha1; // X轴坡度
  double alpha2; // Y轴坡度

  // 台阶参数
  int N; // 台阶数量(1-3)
};

TopoDS_Shape create_step_plate_base(const step_plate_base_params &params);
TopoDS_Shape create_step_plate_base(const step_plate_base_params &params,
                                    const gp_Pnt &position,
                                    const gp_Dir &direction = gp::DZ());

struct sloped_base_base_params {
  // 高度参数
  double H1; // 底板前部高度
  double H2; // 底板后部高度差
  double H3; // 柱体高度

  // 尺寸参数
  double b;  // 柱体直径
  double L1; // 底板前部长度
  double L2; // 底板后部长度
  double B1; // 底板前部宽度
  double B2; // 底板后部宽度

  // 坡度参数(度)
  double alpha1; // X轴坡度
  double alpha2; // Y轴坡度
};

TopoDS_Shape create_sloped_base_base(const sloped_base_base_params &params);
TopoDS_Shape create_sloped_base_base(const sloped_base_base_params &params,
                                     const gp_Pnt &position,
                                     const gp_Dir &direction = gp::DZ());

struct composite_caisson_base_params {
  // 高度参数
  double H1; // 上部沉井高度
  double H2; // 过渡段高度
  double H3; // 下部基础高度
  double H4; // 沉井底部圆管部分高度

  // 尺寸参数
  double b;  // 上部沉井圆筒直径/边长
  double D;  // 沉井底部圆管外径
  double t;  // 沉井壁厚
  double B1; // 过渡段底部宽度
  double B2; // 下部基础宽度
  double L1; // 过渡段底部长度
  double L2; // 下部基础长度
};

TopoDS_Shape
create_composite_caisson_base(const composite_caisson_base_params &params);
TopoDS_Shape
create_composite_caisson_base(const composite_caisson_base_params &params,
                              const gp_Pnt &position,
                              const gp_Dir &direction = gp::DZ());

struct raft_base_params {
  // 高度参数
  double H1; // 底板高度
  double H2; // 边梁高度
  double H3; // 主梁高度（0表示无主梁）

  // 尺寸参数
  double b1; // 纵向主梁宽度
  double b2; // 横向主梁宽度
  double B1; // 底板宽度
  double B2; // 边梁宽度
  double L1; // 底板长度
  double L2; // 边梁长度
};

TopoDS_Shape create_raft_base(const raft_base_params &params);
TopoDS_Shape create_raft_base(const raft_base_params &params,
                              const gp_Pnt &position,
                              const gp_Dir &direction = gp::DZ());

struct direct_buried_base_params {
  // 高度参数
  double H1; // 基础主体高度
  double H2; // 固定盘高度（可选）

  // 尺寸参数
  double d; // 基础主体直径
  double D; // 圆形固定盘直径（可选）
  double B; // 方形固定盘边长（可选）
  double t; // 壁厚
};

TopoDS_Shape create_direct_buried_base(const direct_buried_base_params &params);
TopoDS_Shape create_direct_buried_base(const direct_buried_base_params &params,
                                       const gp_Pnt &position,
                                       const gp_Dir &direction = gp::DZ());

struct steel_sleeve_base_params {
  // 高度参数
  double H1; // 钢套筒高度
  double H2; // 底部扩大段高度
  double H3; // 顶部扩大段高度
  double H4; // 内部填充高度

  // 直径参数
  double d;  // 钢套筒外径
  double D1; // 底部扩大段外径（可选）
  double D2; // 底部扩大段内径（可选）
  double t;  // 钢套筒壁厚

  // 顶部扩大段参数
  double B1; // 顶部扩大段外径（可选）
  double B2; // 顶部扩大段内径（可选）
};

TopoDS_Shape create_steel_sleeve_base(const steel_sleeve_base_params &params);
TopoDS_Shape create_steel_sleeve_base(const steel_sleeve_base_params &params,
                                      const gp_Pnt &position,
                                      const gp_Dir &direction = gp::DZ());

struct precast_column_base_params {
  // 高度参数
  double H1; // 柱体高度
  double H2; // 过渡段上部高度
  double H3; // 过渡段下部高度

  // 直径参数
  double d; // 柱体直径

  // 尺寸参数
  double B1; // 过渡段上部宽度
  double B2; // 过渡段下部宽度
  double L1; // 过渡段上部长度
  double L2; // 过渡段下部长度
};

TopoDS_Shape
create_precast_column_base(const precast_column_base_params &params);
TopoDS_Shape
create_precast_column_base(const precast_column_base_params &params,
                           const gp_Pnt &position,
                           const gp_Dir &direction = gp::DZ());

struct precast_pinned_base_params {
  // 高度参数
  double H1; // 柱体高度
  double H2; // 过渡段上部高度
  double H3; // 过渡段下部高度

  // 直径参数
  double d; // 柱体直径

  // 尺寸参数
  double B1; // 过渡段上部宽度
  double B2; // 过渡段下部宽度
  double L1; // 过渡段上部长度
  double L2; // 过渡段下部长度

  // 卡盘参数(可选)
  double B; // 卡盘宽度
  double H; // 卡盘高度
  double L; // 卡盘长度
};

TopoDS_Shape
create_precast_pinned_base(const precast_pinned_base_params &params);
TopoDS_Shape
create_precast_pinned_base(const precast_pinned_base_params &params,
                           const gp_Pnt &position,
                           const gp_Dir &direction = gp::DZ());

struct precast_metal_support_base_params {
  // 高度参数
  double H1; // 底板高度
  double H2; // 立柱高度
  double H3; // 连接梁高度
  double H4; // 斜撑高度差

  // 尺寸参数
  double b1; // 立柱直径
  double b2; // 连接梁直径
  double B1; // 底板宽度
  double B2; // 支架正面根开
  double L1; // 底板长度
  double L2; // 支架侧面根开
  double S1; // 支架规格
  double S2; // 斜材规格

  // 数量参数
  int n1; // 斜材组数
  int n2; // 板条数量

  // 斜材层高
  std::vector<double> HX; // 斜材层高数组
};

TopoDS_Shape create_precast_metal_support_base(
    const precast_metal_support_base_params &params);
TopoDS_Shape create_precast_metal_support_base(
    const precast_metal_support_base_params &params, const gp_Pnt &position,
    const gp_Dir &direction = gp::DZ());

struct precast_concrete_support_base_params {
  // 高度参数
  double H1; // 底板高度
  double H2; // 立柱高度
  double H3; // 连接梁高度
  double H4; // 支撑顶部高度
  double H5; // 支撑底部高度

  // 尺寸参数
  double b1; // 立柱直径
  double b2; // 连接梁直径
  double b3; // 支撑直径
  double B1; // 底板宽度
  double B2; // 支架正面根开
  double L1; // 底板长度
  double L2; // 支架侧面根开
  double S1; // 顶部平台尺寸

  // 数量参数
  int n1; // 支撑数量
};

TopoDS_Shape create_precast_concrete_support_base(
    const precast_concrete_support_base_params &params);
TopoDS_Shape create_precast_concrete_support_base(
    const precast_concrete_support_base_params &params, const gp_Pnt &position,
    const gp_Dir &direction = gp::DZ());

struct transmission_line_params {
  std::string type;               // 型号
  double sectionalArea;           // 截面积(mm²)
  double outsideDiameter;         // 外径(mm)
  double wireWeight;              // 单位长度质量(kg/km)
  double coefficientOfElasticity; // 弹性系数(N/mm²)
  double expansionCoefficient;    // 线膨胀系数(1/℃)
  double ratedStrength;           // 额定拉断力(N)
};

TopoDS_Shape create_transmission_line(const transmission_line_params &params,
                                      const gp_Pnt &startPoint,
                                      const gp_Pnt &endPoint);

// 绝缘子材质
enum class insulator_material {
  CERAMIC = 1,  // 陶瓷
  GLASS = 2,    // 玻璃
  COMPOSITE = 3 // 复合
};

// 排列方式
enum class arrangement_type {
  HORIZONTAL = 1, // 水平
  VERTICAL = 2    // 垂直
};

// 串用途
enum class application_type {
  CONDUCTOR = 1,  // 导线
  GROUND_WIRE = 2 // 地线
};

// 串类型
enum class string_type {
  SUSPENSION = 1, // 悬垂
  TENSION = 2     // 耐张
};

// 复合绝缘子参数子结构
struct composite_insulator_params {
  double majorRadius; // 大半径(mm)
  double minorRadius; // 小半径(mm)
  double gap;         // 间隙(mm)
};

// 主参数结构体
struct insulator_params {
  // 基础标识
  std::string type; // 型号
  int subNum;       // 分裂数(1/2/4/6/8)
  int subType;      // 分裂排列方式(0/1/2)

  // 几何参数
  double splitDistance; // 分裂间距(mm)
  double vAngleLeft;    // V串左夹角(°)
  double vAngleRight;   // V串右夹角(°)
  double uLinkLength;   // U串连接长度(mm)

  // 物理特性
  double weight; // 重量(kg)

  // 金具尺寸
  struct {
    double leftUpper;  // 左上金具长度(mm)
    double rightUpper; // 右上
    double leftLower;  // 左下
    double rightLower; // 右下
  } fittingLengths;

  // 多联配置
  struct {
    int count;                    // 联数
    double spacing;               // 联间距(mm)
    arrangement_type arrangement; // 排列方式
  } multiLink;

  // 绝缘子参数
  struct {
    boost::variant<double, composite_insulator_params> radius; // 半径或复合参数
    double height;                                             // 结构高度(mm)
    int leftCount;                                             // 左侧片数
    int rightCount;                                            // 右侧片数
    insulator_material material;                               // 材质
  } insulator;

  // 均压环配置
  struct {
    int count;       // 个数
    double position; // 安装位置(mm)
    double height;   // 环高度(mm)
    double radius;   // 环半径(mm)
  } gradingRing;

  // 用途类型
  application_type application;
  string_type stringType;
};

/**
 * @brief 创建带定位的绝缘子串
 * @param params 绝缘子参数结构体
 * @param position 绝缘子串与杆塔连接点位置
 * @param direction 绝缘子串方向（默认Z轴向上）
 * @return TopoDS_Shape 生成的绝缘子串形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_insulator_string(const insulator_params &params);
TopoDS_Shape create_insulator_string(const insulator_params &params,
                                     const gp_Pnt &position,
                                     const gp_Dir &direction = gp_Dir(0, 0, 1));

// 杆件类型枚举
enum class member_type {
  ANGLE = 1,       // 角钢
  TUBE = 2,        // 等径钢管
  TAPERED_TUBE = 3 // 锥形钢管
};

// 挂点类型枚举
enum class attachment_type {
  GROUND_WIRE = 1, // 地线挂点
  CONDUCTOR = 2,   // 导线挂点
  JUMPER = 3       // 跳线挂点
};

// 杆塔节点信息
struct pole_tower_node {
  std::string id;  // 节点编号
  gp_Pnt position; // 节点坐标
};

// 杆塔杆件信息
struct pole_tower_member {
  std::string id;            // 杆件编号
  std::string startNodeId;   // 起始节点ID
  std::string endNodeId;     // 结束节点ID
  member_type type;          // 杆件类型
  std::string specification; // 规格
  std::string material;      // 材质
  gp_Dir xDirection;         // X肢方向(角钢专用)
  gp_Dir yDirection;         // Y肢方向(角钢专用)
  double end1Diameter;       // 端1直径(锥形钢管专用)
  double end2Diameter;       // 端2直径(锥形钢管专用)
  double thickness;          // 厚度(钢管专用)
  int sides;                 // 边数(锥形钢管专用)
};

// 杆塔挂点信息
struct pole_tower_attachment {
  std::string name;     // 挂点名称
  attachment_type type; // 挂点类型
  gp_Pnt position;      // 挂点坐标
};

// 杆塔接腿信息
struct pole_tower_leg {
  std::string id;                     // 接腿编号
  double commonHeight;                // 共用部分高度
  double specificHeight;              // 非共用部分高度
  std::vector<pole_tower_node> nodes; // 接腿节点
};

// 杆塔本体信息
struct pole_tower_body {
  std::string id;                     // 本体编号
  double height;                      // 本体高度
  std::vector<pole_tower_node> nodes; // 本体节点
  std::vector<pole_tower_leg> legs;   // 接腿信息
};

// 杆塔呼高信息
struct pole_tower_height {
  double value;       // 呼高值
  std::string bodyId; // 对应本体ID
  std::string legId;  // 对应接腿ID
};

// 杆塔参数结构体
struct pole_tower_params {
  std::vector<pole_tower_height> heights;         // 呼高集合
  std::vector<pole_tower_body> bodies;            // 本体集合
  std::vector<pole_tower_member> members;         // 杆件集合
  std::vector<pole_tower_attachment> attachments; // 挂点集合
};

// 创建杆塔函数声明
TopoDS_Shape create_pole_tower(const pole_tower_params &params);
TopoDS_Shape create_pole_tower(const pole_tower_params &params,
                               const gp_Pnt &position,
                               const gp_Dir &normal = gp::DX(),
                               const gp_Dir &xDirection = gp::DZ());

// 单钩锚固参数结构体
struct single_hook_anchor_params {
  // 基础参数
  double boltDiameter;    // 地脚螺栓直径
  double exposedLength;   // 露头长度
  int nutCount;           // 蝶帽数量
  double nutHeight;       // 蝶帽高度
  double nutOD;           // 蝶帽外径
  int washerCount;        // 垫片数量
  int washerShape;        // 垫片形状 (1-方形, 2-圆形)
  double washerSize;      // 垫片长/直径
  double washerThickness; // 垫片厚度
  double anchorLength;    // 锚固长度

  // 单钩锚固特有参数
  double hookStraightLength; // 弯钩直段长度 (B)
  double hookDiameter;       // 弯钩直径 (C)
};
// 创建单钩锚固函数声明
TopoDS_Shape create_single_hook_anchor(const single_hook_anchor_params &params);
TopoDS_Shape create_single_hook_anchor(const single_hook_anchor_params &params,
                                       const gp_Pnt &position,
                                       const gp_Dir &normal = gp::DZ(),
                                       const gp_Dir &xDir = gp::DX());

// 三钩锚固参数结构体
struct triple_hook_anchor_params {
  // 基础参数
  double boltDiameter;    // 地脚螺栓直径
  double exposedLength;   // 露头长度
  int nutCount;           // 蝶帽数量
  double nutHeight;       // 蝶帽高度
  double nutOD;           // 蝶帽外径
  int washerCount;        // 垫片数量
  int washerShape;        // 垫片形状 (1-方形, 2-圆形)
  double washerSize;      // 垫片长/直径
  double washerThickness; // 垫片厚度
  double anchorLength;    // 锚固长度

  // 三钩锚固特有参数
  double hookStraightLengthA; // 弯钩直段A长度
  double hookStraightLengthB; // 弯钩直段B长度
  double hookDiameter;        // 弯钩直径
  double anchorBarDiameter;   // 锚筋规格 (D)
};

TopoDS_Shape create_triple_hook_anchor(const triple_hook_anchor_params &params);
TopoDS_Shape create_triple_hook_anchor(const triple_hook_anchor_params &params,
                                       const gp_Pnt &position,
                                       const gp_Dir &normal = gp::DZ(),
                                       const gp_Dir &xDir = gp::DX());

struct ribbed_anchor_params {
  // 基础参数
  double boltDiameter;    // 地脚螺栓直径
  double exposedLength;   // 露头长度
  int nutCount;           // 蝶帽数量
  double nutHeight;       // 蝶帽高度
  double nutOD;           // 蝶帽外径
  int washerCount;        // 垫片数量
  int washerShape;        // 垫片形状 (1-方形, 2-圆形)
  double washerSize;      // 垫片长/直径
  double washerThickness; // 垫片厚度
  double anchorLength;    // 锚固长度

  // 肋板锚固特有参数
  double basePlateSize;      // 下锚板边长 (B)
  double ribTopWidth;        // 肋板上口宽 (B1)
  double ribBottomWidth;     // 肋板下口宽 (B2)
  double basePlateThickness; // 下锚板厚度 (T1)
  double ribHeight;          // 下肋板高度 (H)
  double ribThickness;       // 下肋板厚度 (T2)
};
TopoDS_Shape create_ribbed_anchor(const ribbed_anchor_params &params);
TopoDS_Shape create_ribbed_anchor(const ribbed_anchor_params &params,
                                  const gp_Pnt &position,
                                  const gp_Dir &normal = gp::DZ(),
                                  const gp_Dir &xDir = gp::DX());

// 螺帽锚固参数结构体
struct nut_anchor_params {
  // 基础参数
  double boltDiameter;    // 地脚螺栓直径
  double exposedLength;   // 露头长度
  int nutCount;           // 蝶帽数量
  double nutHeight;       // 蝶帽高度 (T2)
  double nutOD;           // 蝶帽外接圆直径 (D)
  int washerCount;        // 垫片数量
  int washerShape;        // 垫片形状 (1-方形, 2-圆形)
  double washerSize;      // 垫片长度/直径 (B2)
  double washerThickness; // 垫片厚度 (T3)
  double anchorLength;    // 锚固长度

  // 螺帽锚固特有参数
  double basePlateSize;       // 下锚板边长 (B1)
  double basePlateThickness;  // 下锚板厚度 (T1)
  double boltToPlateDistance; // 基础下锚板到螺栓下端距离 (S)
};
// 创建螺帽锚固函数声明
TopoDS_Shape create_nut_anchor(const nut_anchor_params &params);
TopoDS_Shape create_nut_anchor(const nut_anchor_params &params,
                               const gp_Pnt &position,
                               const gp_Dir &normal = gp::DZ(),
                               const gp_Dir &xDir = gp::DX());

// 三支锚固参数结构体
struct triple_arm_anchor_params {
  // 基础参数
  double boltDiameter;    // 地脚螺栓直径
  double exposedLength;   // 露头长度
  int nutCount;           // 蝶帽数量
  double nutHeight;       // 蝶帽高度
  double nutOD;           // 蝶帽外径
  int washerCount;        // 垫片数量
  int washerShape;        // 垫片形状 (1-方形, 2-圆形)
  double washerSize;      // 垫片长/直径
  double washerThickness; // 垫片厚度
  double anchorLength;    // 锚固长度

  // 三支锚固特有参数
  double armDiameter;       // 弯支规格 (D)
  double armStraightLength; // 弯支直径长 (A)
  double armBendLength;     // 弯支弯折段长 (B)
  double armBendAngle;      // 弯支弯折弧度 (C)
};
// 创建三支锚固函数声明
TopoDS_Shape create_triple_arm_anchor(const triple_arm_anchor_params &params);
TopoDS_Shape create_triple_arm_anchor(const triple_arm_anchor_params &params,
                                      const gp_Pnt &position,
                                      const gp_Dir &normal = gp::DZ(),
                                      const gp_Dir &xDir = gp::DX());

// 定位板锚固参数结构体
struct positioning_plate_anchor_params {
  // 基础参数
  double boltDiameter;    // 地脚螺栓直径
  double exposedLength;   // 露头长度
  int nutCount;           // 蝶帽数量
  double nutHeight;       // 蝶帽高度
  double nutOD;           // 蝶帽外径
  int washerCount;        // 垫片数量
  int washerShape;        // 垫片形状 (1-方形, 2-圆形)
  double washerSize;      // 垫片长/直径
  double washerThickness; // 垫片厚度
  double anchorLength;    // 锚固长度

  // 定位板锚固特有参数
  double plateLength;       // 定位板长度 (B)
  double plateThickness;    // 定位板厚度 (T)
  double toBaseDistance;    // 到基础面距离 (H1)
  double toBottomDistance;  // 到底部距离 (H2)
  double groutHoleDiameter; // 灌注孔径 (D)
};

// 创建定位板锚固函数声明
TopoDS_Shape
create_positioning_plate_anchor(const positioning_plate_anchor_params &params);
TopoDS_Shape create_positioning_plate_anchor(
    const positioning_plate_anchor_params &params, const gp_Pnt &position,
    const gp_Dir &normal = gp::DZ(), const gp_Dir &xDir = gp::DX());

// 插入角钢参数结构体
struct stub_angle_params {
  double legWidth;      // 肢宽 (mm)
  double thickness;     // 厚度 (mm)
  double slope;         // 坡度 (与塔腿主材坡度一致，单面坡度)
  double exposedLength; // 露头长度 (mm)
  double anchorLength;  // 锚固长度 (mm)
};

// 创建插入角钢函数声明
TopoDS_Shape create_stub_angle(const stub_angle_params &params);
TopoDS_Shape create_stub_angle(const stub_angle_params &params,
                               const gp_Pnt &position,
                               const gp_Dir &normal = gp::DZ(),
                               const gp_Dir &xDir = gp::DX());

// 插入钢管参数结构体
struct stub_tube_params {
  double diameter;      // 直径 (mm)
  double thickness;     // 壁厚 (mm)
  double slope;         // 坡度 (与塔腿主材坡度一致，单面坡度)
  double exposedLength; // 露头长度 (mm)
  double anchorLength;  // 锚固长度 (mm)
};
// 创建插入钢管函数声明
TopoDS_Shape create_stub_tube(const stub_tube_params &params);
TopoDS_Shape create_stub_tube(const stub_tube_params &params,
                              const gp_Pnt &position,
                              const gp_Dir &normal = gp::DZ(),
                              const gp_Dir &xDir = gp::DX());

struct cable_wire_params {
  std::vector<gp_Pnt> points; // 电缆路径点集
  double outsideDiameter;    // 电缆外径(mm)
};

TopoDS_Shape create_cable_wire(const cable_wire_params &params);
TopoDS_Shape create_cable_wire(const cable_wire_params &params,
                               const gp_Pnt &position,
                               const gp_Dir &direction = gp_Dir(0, 1, 0),
                               const gp_Dir &upDirection = gp_Dir(1, 0, 0));

/**
 * @brief 中间接头参数结构体 DL_JT
 */
struct cable_joint_params {
  double length;         // 接头总长 (L > 0)
  double outerDiameter;  // 接头外径 (D > d)
  double terminalLength; // 端子长度 (L1 > 0)
  double innerDiameter;  // 接头内径 (d > 0)
};

TopoDS_Shape create_cable_joint(const cable_joint_params &params);
TopoDS_Shape create_cable_joint(const cable_joint_params &params,
                                const gp_Pnt &position,
                                const gp_Dir &direction = gp::DZ(),
                                const gp_Dir &xDir = gp::DX());
/**
 * @brief 光缆接头盒类型参数结构体 DL_GLJTH
 */
struct optical_fiber_box_params {
  double length; // 接头总长 (L > 0)
  double height; // 接头侧高 (H > 0)
  double width;  // 接头侧宽 (W > 0)
};

TopoDS_Shape create_optical_fiber_box(const optical_fiber_box_params &params);
TopoDS_Shape create_optical_fiber_box(const optical_fiber_box_params &params,
                                      const gp_Pnt &position,
                                      const gp_Dir &direction = gp::DZ(),
                                      const gp_Dir &xDir = gp::DX());
/**
 * @brief 电缆终端类型参数结构体 DL_ZDJT
 */
struct cable_terminal_params {
  int sort;              // 类型 SORT: 1-户外, 2-户内(GIS), 3-干式
  double height;         // 总高度 H (mm)
  double topDiameter;    // 上部直径 L1 (mm)
  double bottomDiameter; // 下部直径 d (mm)
  double tailDiameter;   // 尾管直径 D3 (mm)
  double tailHeight;     // 尾管高度 WH (mm)

  // 伞裙参数 (仅户外和干式终端使用)
  int skirtCount;                  // 伞裙片数 N
  double upperSkirtTopDiameter;    // 伞裙1上部直径 SD (mm)
  double upperSkirtBottomDiameter; // 伞裙1下部直径 SDI (mm)
  double lowerSkirtTopDiameter;    // 伞裙2上部直径 BD (mm)
  double lowerSkirtBottomDiameter; // 伞裙2下部直径 BDI (mm)
  double skirtSectionHeight;       // 伞裙节高度 h (mm)

  // 端子参数
  double upperTerminalLength;   // 上端子长度 LI (mm)
  double upperTerminalDiameter; // 上端子直径 ZDI (mm)
  double lowerTerminalLength;   // 下端子长度 L2 (mm)
  double lowerTerminalDiameter; // 下端子直径 ZD2 (mm)

  // 连接孔参数
  double hole1Diameter; // 连接孔1直径 Φ1 (mm)
  double hole2Diameter; // 连接孔2直径 Φ2 (mm)
  double hole1Distance; // 连接孔1端距离 dl (mm)
  double holeSpacing;   // 连接孔1到2间距 d2 (mm)

  // 户外终端专用参数
  double flangeHoleDiameter;     // 法兰盘连接孔直径 FD (mm)
  double flangeHoleSpacing;      // 法兰盘连接孔间距 KD (mm)
  double flangeWidth;            // 法兰盘宽度 PD (mm)
  double flangeCenterHoleRadius; // 法兰盘中心孔半径 PR (mm)
  double flangeChamferRadius;    // 法兰盘边缘倒角半径 BR (mm)
  double flangeOpeningWidth;     // 法兰盘开口宽度 K (mm)
  double flangeBoltHeight;       // 法兰盘螺栓高度 LH (mm)
};

TopoDS_Shape create_cable_terminal(const cable_terminal_params &params);
TopoDS_Shape create_cable_terminal(const cable_terminal_params &params,
                                   const gp_Pnt &position,
                                   const gp_Dir &direction = gp::DZ());

// 接地箱类型枚举
enum class cable_box_type {
  DIRECT_GROUND = 1,     // 直接接地箱
  PROTECTIVE_GROUND = 2, // 带护层保护器的接地箱
  CROSS_INTERCONNECT = 3 // 交叉互联箱
};

// ZJJDX HCBHX JCHLX
struct cable_accessory_params {
  cable_box_type type;      // 箱体类型
  double length;            // 箱体长度(mm)
  double width;             // 箱体宽度(mm)
  double height;            // 箱体高度(mm)
  int portCount;            // 电缆进出口数目(3或6)
  double portDiameter;      // 进出口直径(mm)
  double portSpacing;       // 进出口间距(mm)
  double backPanelDistance; // 进出口距箱后面板距离(mm)
  double sidePanelDistance; // 进出口距箱侧面板距离(mm)
};

TopoDS_Shape create_cable_accessory(const cable_accessory_params &params);
TopoDS_Shape create_cable_accessory(const cable_accessory_params &params,
                                    const gp_Pnt &position,
                                    const gp_Dir &normal = gp::DZ(),
                                    const gp_Dir &xDir = gp::DX());

// GJ_DLZJ
struct cable_bracket_params {
  double length;                         // 支架长度 L (mm)
  double rootHeight;                     // 支架根部高度 H (mm)
  double rootWidth;                      // 支架根部宽度 B (mm)
  double width;                          // 支架宽度 C (mm)
  double topThickness;                   // 支架顶部厚度 t (mm)
  double rootThickness;                  // 支架根部厚度 T (mm)
  std::vector<gp_Pnt> columnMountPoints; // 立柱安装点坐标
  std::vector<gp_Pnt> clampMountPoints;  // 夹具安装点坐标
};

TopoDS_Shape create_cable_bracket(const cable_bracket_params &params);
TopoDS_Shape create_cable_bracket(const cable_bracket_params &params,
                                  const gp_Pnt &position,
                                  const gp_Dir &normal = gp::DZ(),
                                  const gp_Dir &xDir = gp::DX());

// 电缆夹具类型枚举
enum class cable_clamp_type {
  SINGLE = 1,         // 单根夹具
  LINEAR = 2,         // 一字式
  CONTACT_TRIPLE = 3, // 品字接触式
  SEPARATE_TRIPLE = 4 // 品字分离式
};

// GJ_DLJV
struct cable_clamp_params {
  cable_clamp_type type; // 夹具类型
  double diameter;       // 夹具直径(mm)
  double thickness;      // 夹具厚度(mm)
  double width;          // 夹具宽度(mm)
};

TopoDS_Shape create_cable_clamp(const cable_clamp_params &params);
TopoDS_Shape create_cable_clamp(const cable_clamp_params &params,
                                const gp_Pnt &position,
                                const gp_Dir &normal = gp::DZ(),
                                const gp_Dir &xDir = gp::DX());
// GJ_DLLZ
struct cable_pole_params {
  std::string specification;       // 规格型号
  double length;                   // 立柱长度 L (mm)
  double radius;                   // 立柱半径 R (mm)
  double arcAngle;                 // 立柱弧度 A (弧度)
  double width;                    // 立柱宽度 B (mm)
  double fixedLegLength;           // 固定肢长度 C (mm)
  double fixedLegWidth;            // 固定肢宽度 S (mm)
  double thickness;                // 立柱厚度 t (mm)
  std::vector<gp_Pnt> mountPoints; // 支架安装点坐标
};

TopoDS_Shape create_cable_pole(const cable_pole_params &params);
TopoDS_Shape create_cable_pole(const cable_pole_params &params,
                               const gp_Pnt &position,
                               const gp_Dir &direction = gp::DZ());

// GJ_JDBT
struct ground_flat_iron_params {
  double length;    // 长度 L (mm)
  double height;    // 高度 H (mm)
  double thickness; // 厚度 T (mm)
};

TopoDS_Shape create_ground_flat_iron(const ground_flat_iron_params &params);
TopoDS_Shape create_ground_flat_iron(const ground_flat_iron_params &params,
                                     const gp_Pnt &position,
                                     const gp_Dir &normal = gp::DZ(),
                                     const gp_Dir &xDir = gp::DX());

// GJ_YMJ
struct embedded_part_params {
  double length;         // 预埋件长度 L (mm)
  double radius;         // 半圆钩半径 R (mm)
  double height;         // 预埋件高度 H (mm)
  double materialRadius; // 材料半径 R1 (mm)
  double lowerLength;    // 下部长度 L1 (mm)
};

TopoDS_Shape create_embedded_part(const embedded_part_params &params);
TopoDS_Shape create_embedded_part(const embedded_part_params &params,
                                  const gp_Pnt &position,
                                  const gp_Dir &normal = gp::DZ(),
                                  const gp_Dir &xDir = gp::DX());
// GJ_UXLH
struct u_shaped_ring_params {
  double thickness; // 材料厚度 T (mm)
  double height;    // 拉环开口高度 H (mm)
  double radius;    // 拉环半径 R (mm)
  double length;    // 拉环长度 L (mm)
};

TopoDS_Shape create_u_shaped_ring(const u_shaped_ring_params &params);
TopoDS_Shape create_u_shaped_ring(const u_shaped_ring_params &params,
                                  const gp_Pnt &position,
                                  const gp_Dir &normal = gp::DZ(),
                                  const gp_Dir &xDir = gp::DX());

// GJ_DP
struct lifting_eye_params {
  double height;       // 吊臂高度 H (mm)
  double ringRadius;   // 圆环半径 R (mm)
  double pipeDiameter; // 钢管直径 I (mm)
};

TopoDS_Shape create_lifting_eye(const lifting_eye_params &params);
TopoDS_Shape create_lifting_eye(const lifting_eye_params &params,
                                const gp_Pnt &position,
                                const gp_Dir &normal = gp::DZ(),
                                const gp_Dir &xDir = gp::DX());

/**
 * @brief 转角井参数结构体 DLJ_ZJJ
 */
struct corner_well_params {
  double leftLength;       // 井左段净长 L1 > 0
  double rightLength;      // 井右段净长 L2 > 0
  double width;            // 井净宽 W > 0
  double height;           // 井净高 H > 0
  double topThickness;     // 井顶板厚 H1 > 0
  double bottomThickness;  // 井底板厚 H2 > 0
  double wallThickness;    // 井外壁厚 T1 > 0
  double angle;            // 井转角角度 A (0 < A < 180)
  double cornerRadius;     // 井转角段半径 R > 0
  double cushionExtension; // 垫层滋出距离 T3 >= 0
  double cushionThickness; // 垫层厚 HB > 0
};

TopoDS_Shape create_corner_well(const corner_well_params &params);
TopoDS_Shape create_corner_well(const corner_well_params &params,
                                const gp_Pnt &position,
                                const gp_Dir &direction = gp::DZ(),
                                const gp_Dir &xDir = gp::DX());

/**
 * @brief 连接段截面样式枚举
 */
enum class connection_section_style {
  RECTANGULAR = 1, // 矩形
  HORSESHOE = 2,   // 马蹄形
  CIRCULAR = 3     // 圆形
};

// 井类型枚举
enum class tunnel_well_type {
  STRAIGHT = 1,       // 直线井
  STRAIGHT_TUNNEL = 2 // 直线暗挖隧道井
};

struct tunnel_well_params {
  tunnel_well_type type;  // 井类型
  double length;          // 井净长(mm)
  double width;           // 井净宽(mm)
  double height;          // 井净高(mm)
  double radius;          // 井内径(mm)，仅竖井使用
  double topThickness;    // 井顶板厚(mm)
  double bottomThickness; // 井底板厚(mm)

  // 左连接段参数
  connection_section_style leftSectionType; // 左连接段截面形式
  double leftLength;                        // 左连接段长(mm)
  double leftWidth;                         // 左连接段宽(mm)
  double leftHeight;                        // 左连接段高/半径(mm)
  double leftArcHeight;                     // 左连接段拱高(mm)

  // 右连接段参数
  connection_section_style rightSectionType; // 右连接段截面形式
  double rightLength;                        // 右连接段长(mm)
  double rightWidth;                         // 右连接段宽(mm)
  double rightHeight;                        // 右连接段高/半径(mm)
  double rightArcHeight;                     // 右连接段拱高(mm)

  double outerWallThickness; // 井外壁厚(mm)
  double innerWallThickness; // 井内壁厚(mm)，仅竖井使用
  double cushionExtension;   // 垫层滋出距离(mm)
  double cushionThickness;   // 垫层厚(mm)
};

TopoDS_Shape create_tunnel_well(const tunnel_well_params &params);
TopoDS_Shape create_tunnel_well(const tunnel_well_params &params,
                                const gp_Pnt &position,
                                const gp_Dir &direction = gp::DZ(),
                                const gp_Dir &xDir = gp::DX());

/**
 * @brief 三通井类型枚举
 */
enum class three_way_well_type {
  WORKING_WELL = 1,      // 工作井
  OPEN_CUT_TUNNEL = 2,   // 明挖隧道井
  UNDERGROUND_TUNNEL = 3 // 暗挖隧道井
};

/**
 * @brief 转角样式枚举
 */
enum class corner_style {
  ROUNDED = 1, // 圆形
  ANGLED = 2   // 折角形
};

/**
 * @brief 竖井样式枚举
 */
enum class shaft_style {
  CIRCULAR = 1,   // 圆形竖井
  RECTANGULAR = 2 // 矩形竖井
};

/**
 * @brief 三通井参数结构体 DLJ_3T/DLJ_3TMS/DLJ_3TAS
 */
struct three_way_well_params {
  three_way_well_type type; // 三通井类型
  corner_style cornerType;  // 转角样式
  shaft_style shaftType;    // 竖井样式

  // 主井尺寸
  double length; // 井净长(mm)
  double width;  // 井净宽(mm)
  double height; // 井净高(mm)

  // 竖井参数
  double shaftRadius; // 竖井内半径(mm)

  // 转角参数
  double cornerRadius; // 井转角半径(mm)
  double cornerLength; // 井转角折角长(mm)
  double cornerWidth;  // 井转角折角宽(mm)
  double angle;        // 支线段转角度数(度)

  // 支线井参数
  double branchLength;     // 支线井净长(mm)
  double branchLeftLength; // 左侧到支线井距离(mm)
  double branchWidth;      // 支线井净宽(mm)

  // 结构厚度
  double topThickness;    // 井顶板厚(mm)
  double bottomThickness; // 井底板厚(mm)

  // 连接段参数
  connection_section_style leftSectionStyle; // 左侧连接段截面样式
  double leftSectionLength;                  // 左侧连接段长(mm)
  double leftSectionWidth;                   // 左侧连接段宽(mm)
  double leftSectionHeight;                  // 左侧连接段高/半径(mm)
  double leftSectionArcHeight;               // 左侧连接段拱高(mm)

  connection_section_style rightSectionStyle; // 右侧连接段截面样式
  double rightSectionLength;                  // 右侧连接段长(mm)
  double rightSectionWidth;                   // 右侧连接段宽(mm)
  double rightSectionHeight;                  // 右侧连接段高/半径(mm)
  double rightSectionArcHeight;               // 右侧连接段拱高(mm)

  connection_section_style branchSectionStyle; // 支线连接段截面样式
  double branchSectionLength;                  // 支线连接段长(mm)
  double branchSectionWidth;                   // 支线连接段宽(mm)
  double branchSectionHeight;                  // 支线连接段高/半径(mm)
  double branchSectionArcHeight;               // 支线连接段拱高(mm)

  // 壁厚参数
  double outerWallThickness; // 井外壁厚(mm)
  double innerWallThickness; // 井内壁厚(mm)

  // 双拼井参数
  bool isDoubleShaft;        // 是否是双拼三通竖井
  double doubleShaftSpacing; // 支线段双拼电缆井间距(mm)

  // 其他参数
  double outerWallExtension;   // 井室外壁滋出距离(mm)
  double innerWallExtension;   // 井室内壁滋出距离(mm)
  double cushionExtension;     // 垫层滋出距离(mm)
  double cushionThickness;     // 垫层厚(mm)
  double innerBottomThickness; // 井室底面内壁厚(mm)
  double outerBottomThickness; // 井室底面外壁厚(mm)
};

TopoDS_Shape create_three_way_well(const three_way_well_params &params);
TopoDS_Shape create_three_way_well(const three_way_well_params &params,
                                   const gp_Pnt &position,
                                   const gp_Dir &mainDirection = gp::DX(),
                                   const gp_Dir &branchDirection = gp::DY());

/**
 * @brief  四通井类型枚举
 */
enum class four_way_well_type {
  WORKING_WELL = 1,      // 工作井
  OPEN_CUT_TUNNEL = 2,   // 明挖隧道井
  UNDERGROUND_TUNNEL = 3 // 暗挖隧道井
};

// DLJ_4T/DLJ_4TMS/DLJ_4TAS
struct four_way_well_params {
  four_way_well_type type; // 四通井类型

  // 主井参数
  double length; // 井净长 L (mm)
  double width;  // 井净宽 W (mm)
  double height; // 井净高 H (mm)

  // 竖井参数
  double shaftRadius; // 竖井内半径(mm)

  // 转角样式参数
  corner_style cornerStyle; // 1=圆形, 2=折角形
  double cornerRadius;      // 转角半径 RZ (mm)
  double cornerLength;      // 折角长 LZ1 (mm)
  double cornerWidth;       // 折角宽 WZ1 (mm)

  // 支线段参数
  double branchLength; // 支线段净长 L1 (mm)
  double branchWidth;  // 支线段净宽 W1 (mm)

  // 顶底板参数
  double topThickness;    // 顶板厚 H1 (mm)
  double bottomThickness; // 底板厚 H2 (mm)

  // 连接段参数
  struct {
    connection_section_style sectionType; // 截面样式
    double length;                        // 连接段长
    double width;                         // 连接段宽
    double height;                        // 高度/半径
    double arcHeight;                     // 拱高
  } leftSection, rightSection, branchSection1, branchSection2;

  // 壁厚参数
  double outerWallThickness; // 外壁厚 T1 (mm)
  double innerWallThickness; // 内壁厚 T2 (mm)

  // 垫层参数
  double cushionExtension; // 垫层滋出距离 T3 (mm)
  double cushionThickness; // 垫层厚 H3 (mm)
};

TopoDS_Shape create_four_way_well(const four_way_well_params &params);
TopoDS_Shape create_four_way_well(const four_way_well_params &params,
                                  const gp_Pnt &position,
                                  const gp_Dir &direction = gp::DZ(),
                                  const gp_Dir &xDirection = gp::DX());

struct channel_point {
  gp_Pnt position; // 点坐标
  int type;        // 点类型 (0-普通节点
                   // 1-弧形节点（弧形节点为圆弧顶点，与前后点三点成弧）)
};

// TD_PG
struct pipe_row_params {
  int pipeType;            // 1=普通排管, 2=拉管
  bool hasEnclosure;       // 是否有包封
  double enclosureWidth;   // 包封宽 W (mm)
  double enclosureHeight;  // 包封高 H (mm)
  double baseExtension;    // 底板滋出距离 W1 (mm)
  double baseThickness;    // 底板厚 H1 (mm)
  double cushionExtension; // 垫层滋出距离 W2 (mm)
  double cushionThickness; // 垫层厚 H2 (mm)

  // 普通排管参数
  std::vector<gp_Pnt2d> pipePositions;     // 排管中心点坐标 (x,y)
  std::vector<double> pipeInnerDiameters;  // 排管内径 DI (mm)
  std::vector<double> pipeWallThicknesses; // 排管壁厚 TI (mm)

  // 拉管参数
  double pullPipeInnerDiameter; // 拉管内径 D (mm)
  double pullPipeThickness;     // 拉管厚 T (mm)

  std::vector<channel_point> points; // 通道点集
};

TopoDS_Shape create_pipe_row(const pipe_row_params &params);
TopoDS_Shape create_pipe_row(const pipe_row_params &params,
                             const gp_Pnt &position,
                             const gp_Dir &normal = gp::DZ(),
                             const gp_Dir &xDir = gp::DX());

// TD_DLG
struct cable_trench_params {
  double width;            // 沟内净宽 W (mm)
  double height;           // 沟内净高 H (mm)
  double coverWidth;       // 盖板宽 W1 (mm)
  double coverThickness;   // 盖板厚 H1 (mm)
  double baseExtension;    // 底板滋出距离 W2 (mm)
  double baseThickness;    // 底板厚 H2 (mm)
  double cushionExtension; // 垫层滋出距离 W3 (mm)
  double cushionThickness; // 垫层厚 H3 (mm)
  double wallThickness;    // 壁厚 T (mm)
  double wallThickness2;   // 壁厚2 T1 (mm)

  std::vector<channel_point> points; // 通道点集
};

TopoDS_Shape create_cable_trench(const cable_trench_params &params);
TopoDS_Shape create_cable_trench(const cable_trench_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction = gp::DZ(),
                                 const gp_Dir &xDir = gp::DX());

// TD_DLSD
struct cable_tunnel_params {
  connection_section_style style; // 截面样式

  // 基本尺寸参数
  double width;  // 内净宽/内径 W (mm)
  double height; // 内净高 H (mm)

  // 矩形隧道参数
  double topThickness;    // 顶板厚 H1 (mm)
  double bottomThickness; // 底板厚 H2 (mm)

  // 马蹄形隧道参数
  double outerWallThickness; // 外壁厚 T (mm)
  double innerWallThickness; // 内壁厚 T1 (mm)
  double arcHeight;          // 拱高 H4 (mm)

  // 圆形隧道参数
  double bottomPlatformHeight; // 底部平台高 H5 (mm)

  // 通用参数
  double cushionExtension; // 垫层滋出 W2 (mm)
  double cushionThickness; // 垫层厚 H3 (mm)

  std::vector<channel_point> points;
};

TopoDS_Shape create_cable_tunnel(const cable_tunnel_params &params);
TopoDS_Shape create_cable_tunnel(const cable_tunnel_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction = gp::DZ(),
                                 const gp_Dir &xDir = gp::DX());

// 桥架样式枚举
enum class cable_tray_style {
  ARCH = 1, // 拱形桥架
  BEAM = 2  // 平形桥架
};

// TD_DLQJ
struct cable_tray_params {
  cable_tray_style style; // 桥架样式

  // 桥柱参数
  double columnDiameter; // 桥柱直径 DZ (mm)
  double columnHeight;   // 桥柱高度 HZ (mm)

  // 桥架主体参数
  double span;           // 桥架跨距 L (mm)
  double width;          // 桥架宽 W (mm)
  double height;         // 桥架高 H (mm)
  double topPlateHeight; // 桥顶板高 H1 (mm)
  double arcHeight;      // 桥拱高 H2 (mm)
  double wallThickness;  // 桥架壁厚 TQ (mm)

  // 排管参数
  int pipeCount;                           // 排管数 N
  std::vector<gp_Pnt2d> pipePositions;     // 排管坐标 POS
  std::vector<double> pipeInnerDiameters;  // 排管内径 DI (mm)
  std::vector<double> pipeWallThicknesses; // 排管壁厚 T1 (mm)

  bool hasProtectionPlate; // 是否有防护隔板 FH

  std::vector<channel_point> points;
};

TopoDS_Shape create_cable_tray(const cable_tray_params &params);
TopoDS_Shape create_cable_tray(const cable_tray_params &params,
                               const gp_Pnt &position,
                               const gp_Dir &direction = gp::DZ(),
                               const gp_Dir &xDir = gp::DX());

struct cable_L_beam_params {
  double length; // 梁长 (L > 0)
  double width;  // 梁宽 (W > 0)
  double height; // 梁高 (H > 0)
};

TopoDS_Shape create_cable_L_beam(const cable_L_beam_params &params);
TopoDS_Shape create_cable_L_beam(const cable_L_beam_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &xDirection = gp::DX(),
                                 const gp_Dir &zDirection = gp::DZ());

// 人孔样式枚举
enum class manhole_style {
  CIRCULAR = 1,   // 圆形
  RECTANGULAR = 2 // 方形
};

// GZW_RK
struct manhole_params {
  manhole_style style; // 人孔样式

  // 尺寸参数
  double length;        // 人孔长/直径 L (mm)
  double width;         // 人孔宽 W (mm)
  double height;        // 人孔高 H (mm)
  double wallThickness; // 人孔壁厚 T (mm)
};

TopoDS_Shape create_manhole(const manhole_params &params);
TopoDS_Shape create_manhole(const manhole_params &params,
                            const gp_Pnt &position,
                            const gp_Dir &direction = gp::DZ(),
                            const gp_Dir &xDir = gp::DX());

// 井盖样式枚举
enum class manhole_cover_style {
  CIRCULAR = 1,   // 圆形
  RECTANGULAR = 2 // 方形
};

// GZW_JG
struct manhole_cover_params {
  manhole_cover_style style; // 井盖样式

  // 尺寸参数
  double length;    // 井盖长/直径 L (mm)
  double width;     // 井盖宽 W (mm) - 圆形井盖时为0
  double thickness; // 井盖厚 H (mm)
};

TopoDS_Shape create_manhole_cover(const manhole_cover_params &params);
TopoDS_Shape create_manhole_cover(const manhole_cover_params &params,
                                  const gp_Pnt &position,
                                  const gp_Dir &direction = gp::DZ(),
                                  const gp_Dir &xDir = gp::DX());

// GZW_PT
struct ladder_params {
  double length;    // 爬梯长 L (mm)
  double width;     // 爬梯宽 W (mm)
  double thickness; // 爬梯厚 T (mm)
};

TopoDS_Shape create_ladder(const ladder_params &params);
TopoDS_Shape create_ladder(const ladder_params &params, const gp_Pnt &position,
                           const gp_Dir &direction = gp::DZ(),
                           const gp_Dir &xDir = gp::DX());

// GZW_JSK
struct sump_params {
  double length;          // 集水坑长 L (mm)
  double width;           // 集水坑宽 W (mm)
  double depth;           // 集水坑深 H (mm)
  double bottomThickness; // 集水坑底板厚 T (mm)
};

TopoDS_Shape create_sump(const sump_params &params);
TopoDS_Shape create_sump(const sump_params &params, const gp_Pnt &position,
                         const gp_Dir &normal = gp::DZ(),
                         const gp_Dir &xDir = gp::DX());

// GZW_BD
struct footpath_params {
  double height; // 步道高 H (mm)
  double width;  // 步道宽 W (mm)

  std::vector<channel_point> points;
};

TopoDS_Shape create_footpath(const footpath_params &params);
TopoDS_Shape create_footpath(const footpath_params &params,
                             const gp_Pnt &position,
                             const gp_Dir &direction = gp::DZ(),
                             const gp_Dir &xDir = gp::DX());
// GZW_SJC
struct shaft_chamber_params {
  double supportWallThickness; // 支护壁厚 T1 (mm)
  double supportDiameter;      // 支护直径 D1 (mm)
  double supportHeight;        // 支护高度 H1 (mm)
  double topThickness;         // 顶板厚 T2 (mm)
  double innerDiameter;        // 内壁直径 D (mm)
  double workingHeight;        // 工作仓高度 H (mm)
  double outerWallThickness;   // 外壁厚 T3 (mm)
  double innerWallThickness;   // 内壁厚 T4 (mm)
};

TopoDS_Shape create_shaft_chamber(const shaft_chamber_params &params);
TopoDS_Shape create_shaft_chamber(const shaft_chamber_params &params,
                                  const gp_Pnt &position,
                                  const gp_Dir &direction = gp::DZ(),
                                  const gp_Dir &xDir = gp::DX());

// GZW_SDFCGB
struct tunnel_compartment_partition_params {
  double width;     // 隔板宽 W (mm)
  double thickness; // 隔板厚 T (mm)
};

TopoDS_Shape create_tunnel_compartment_partition(
    const tunnel_compartment_partition_params &params);
TopoDS_Shape create_tunnel_compartment_partition(
    const tunnel_compartment_partition_params &params, const gp_Pnt &position,
    const gp_Dir &normal = gp::DZ(), const gp_Dir &xDir = gp::DX());

// GZW_SDJGB
struct tunnel_partition_board_params {
  int style;                           // 样式 (1-圆形, 2-方形)
  double length;                       // 隔板长/直径 L (mm)
  double width;                        // 隔板宽 W (mm)
  double thickness;                    // 隔板厚 T (mm)
  int holeCount;                       // 开孔数量 NUM
  std::vector<gp_Pnt2d> holePositions; // 开孔中心坐标 POS
  std::vector<int> holeStyles;         // 开孔形式 P1 (1-圆形, 2-方形)
  std::vector<double> holeDiameters;   // 开孔直径/长 L1...n (mm)
  std::vector<double> holeWidths;      // 开孔宽 W1...n (mm)
};

TopoDS_Shape
create_tunnel_partition_board(const tunnel_partition_board_params &params);
TopoDS_Shape create_tunnel_partition_board(
    const tunnel_partition_board_params &params, const gp_Pnt &position,
    const gp_Dir &normal = gp::DZ(), const gp_Dir &xDir = gp::DX());

// GZW_FT
struct ventilation_pavilion_params {
  double topLength;    // 风亭顶长 L1 (mm)
  double middleLength; // 风亭长 L2 (mm)
  double bottomLength; // 风亭底长 L3 (mm)
  double topWidth;     // 风亭顶宽 W1 (mm)
  double middleWidth;  // 风亭宽 W2 (mm)
  double bottomWidth;  // 风亭底宽 W3 (mm)
  double topHeight;    // 风亭顶高 H1 (mm)
  double height;       // 风亭高 H2 (mm)
  double baseHeight;   // 风亭底高 H3 (mm)
};

TopoDS_Shape
create_ventilation_pavilion(const ventilation_pavilion_params &params);
TopoDS_Shape create_ventilation_pavilion(
    const ventilation_pavilion_params &params, const gp_Pnt &position,
    const gp_Dir &direction = gp::DZ(), const gp_Dir &xDir = gp::DX());

// GZW_ZTFD
struct straight_ventilation_duct_params {
  double diameter;      // 直通直径 D (mm)
  double wallThickness; // 直通壁厚 T (mm)
  double height;        // 直通高 H (mm)
};

TopoDS_Shape create_straight_ventilation_duct(
    const straight_ventilation_duct_params &params);
TopoDS_Shape create_straight_ventilation_duct(
    const straight_ventilation_duct_params &params, const gp_Pnt &position,
    const gp_Dir &direction = gp::DZ(), const gp_Dir &xDir = gp::DX());

// GZW_XTFD
struct oblique_ventilation_duct_params {
  double hoodRoomLength;        // 风帽室长 L1 (mm)
  double hoodRoomWidth;         // 风帽室宽 W1 (mm)
  double hoodRoomHeight;        // 风帽室高 H1 (mm)
  double hoodWallThickness;     // 风帽壁厚 T (mm)
  double ductCenterHeight;      // 风通道圆心高 H5 (mm)
  double ductLeftDistance;      // 风通道圆心距左侧距离 L5 (mm)
  double ductDiameter;          // 风通道直径 D1 (mm)
  double ductWallThickness;     // 风通道壁厚 T1 (mm)
  double ductLength;            // 风通道长 L4 (mm)
  double ductHeightDifference;  // 风通道高度差 H2 (mm)
  double baseLength;            // 风基座长 L2 (mm)
  double baseWidth;             // 风基座宽 W2 (mm)
  double baseHeight;            // 风基座高 H4 (mm)
  double baseRoomLength;        // 风基室长 L3 (mm)
  double baseRoomWallThickness; // 风基室壁厚 T2 (mm)
  double baseRoomWidth;         // 风基室宽 W3 (mm)
  double baseRoomHeight;        // 风基室高 H3 (mm)
};

TopoDS_Shape
create_oblique_ventilation_duct(const oblique_ventilation_duct_params &params);
TopoDS_Shape create_oblique_ventilation_duct(
    const oblique_ventilation_duct_params &params, const gp_Pnt &position,
    const gp_Dir &direction = gp::DZ(), const gp_Dir &xDir = gp::DX());

// GZW_PSJ
struct drainage_well_params {
  double length;           // 井净长 L (mm)
  double width;            // 井净宽 W (mm)
  double height;           // 井净高 H (mm)
  double neckDiameter;     // 井脖直径 D (mm)
  double neckHeight;       // 井脖高 H1 (mm)
  double cushionExtension; // 垫层滋出距离 T1 (mm)
  double bottomThickness;  // 排水井底板厚 H2 (mm)
  double wallThickness;    // 排水井壁厚 T (mm)
};

TopoDS_Shape create_drainage_well(const drainage_well_params &params);
TopoDS_Shape create_drainage_well(const drainage_well_params &params,
                                  const gp_Pnt &position,
                                  const gp_Dir &direction = gp::DZ(),
                                  const gp_Dir &xDir = gp::DX());
// GZW_GZ
struct pipe_support_params {
  int style;                       // 管枕形式 (1-单侧管枕, 2-两侧管枕)
  int count;                       // 管枕数量 N
  std::vector<gp_Pnt2d> positions; // 管枕中心坐标 POS (mm)
  std::vector<double> radii;       // 管枕半径 R (mm)
  double length;                   // 管枕长 L (mm)
  double width;                    // 管枕宽 W (mm)
  double height;                   // 管枕高 h (mm)
};

TopoDS_Shape create_pipe_support(const pipe_support_params &params);
TopoDS_Shape create_pipe_support(const pipe_support_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction = gp::DZ(),
                                 const gp_Dir &xDir = gp::DX());

// GZW_GB
struct cover_plate_params {
  int style;          // 盖板形式 (0-长方形, 1-扇形)
  double length;      // 盖板长度/扇形边长 L (mm)
  double width;       // 盖板宽度 W (mm)
  double smallRadius; // 扇形小半径 A (mm)
  double largeRadius; // 扇形大半径 B (mm)
  double thickness;   // 盖板厚度 H (mm)
};

TopoDS_Shape create_cover_plate(const cover_plate_params &params);
TopoDS_Shape create_cover_plate(const cover_plate_params &params,
                                const gp_Pnt &position,
                                const gp_Dir &normal = gp::DZ(),
                                const gp_Dir &xDir = gp::DX());

// GZW_GLCH
struct cable_ray_params {
  double outerLength;    // 槽盒外长度 L1 (mm)
  double outerHeight;    // 槽盒外高度 H1 (mm)
  double innerLength;    // 槽盒内长度 L2 (mm)
  double innerHeight;    // 槽盒内高度 H2 (mm)
  double coverThickness; // 槽盒盖板厚度 D (mm)
};

TopoDS_Shape create_cable_ray(const cable_ray_params &params);
TopoDS_Shape create_cable_ray(const cable_ray_params &params,
                              const gp_Pnt &position,
                              const gp_Dir &direction = gp::DZ(),
                              const gp_Dir &xDir = gp::DX());

/**
 * @brief 截面样式枚举
 */
enum class water_tunnel_section_style {
  RECTANGULAR = 1, // 矩形
  CITYOPENING = 2, // 城市洞形
  CIRCULAR = 3,    // 圆形
  HORSESHOE = 4,   // 马蹄形
};

// Water Tunnel
struct water_tunnel_params {
  water_tunnel_section_style style; // 截面样式

  // 基本尺寸参数
  double width;  // 内净宽/内径 W (mm)
  double height; // 内净高 H (mm)

  // 矩形隧道参数
  double topThickness;    // 顶板厚 H1 (mm)
  double bottomThickness; // 底板厚 H2 (mm)

  // 城市洞形隧道参数 （拱半径和拱高只需要提供一个）
  double outerWallThickness; // 外壁厚 T (mm)
  double innerWallThickness; // 内壁厚 T1 (mm)
  double arcHeight;          // 拱高 H4 (mm)
  double arcRadius;          // 拱半径 R (mm)

  // 马蹄形隧道参数
  double arcAngle; // 拱角 α (°)

  // 圆形隧道参数
  double bottomPlatformHeight; // 底部平台高 H5 (mm)

  // 通用参数
  double cushionExtension; // 垫层滋出 W2 (mm)
  double cushionThickness; // 垫层厚 H3 (mm)

  std::vector<channel_point> points;
};

TopoDS_Shape create_water_tunnel(const water_tunnel_params &params);
TopoDS_Shape create_water_tunnel(const water_tunnel_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction = gp::DZ(),
                                 const gp_Dir &xDir = gp::DX());

} // namespace topo
} // namespace flywave
