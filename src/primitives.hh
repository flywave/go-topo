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
  char phase;           // 相位信息 (A/B/C/N)
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

/**
 * @brief 等边角钢参数结构体
 */
struct equilateral_angle_steel_params {
  double L;      // 边长 (L > 0)
  double X;      // 厚度 (X > 0)
  double length; // 长度 (length > 0)
};

TopoDS_Shape
create_equilateral_angle_steel(const equilateral_angle_steel_params &params);
TopoDS_Shape
create_equilateral_angle_steel(const equilateral_angle_steel_params &params,
                               const gp_Pnt &position,
                               const gp_Dir &xDirection = gp::DX(),
                               const gp_Dir &yDirection = gp::DY().Reversed());

/**
 * @brief 不等边角钢参数结构体
 */
struct scalene_angle_steel_params {
  double L1;     // 长边长度 (L1 > 0)
  double L2;     // 短边长度 (0 < L2 < L1)
  double X;      // 厚度 (0 < X < min(L1,L2))
  double length; // 长度 (length > 0)
};

TopoDS_Shape
create_scalene_angle_steel(const scalene_angle_steel_params &params);
TopoDS_Shape create_scalene_angle_steel(
    const scalene_angle_steel_params &params, const gp_Pnt &position,
    const gp_Dir &xDirection = gp::DX(), const gp_Dir &longEdgeDir = gp::DZ());

/**
 * @brief 工字钢参数结构体
 */
struct ibeam_params {
  double height;          // 总高度 (H > 0)
  double flangeWidth;     // 翼缘宽度 (B > 0)
  double webThickness;    // 腹板厚度 (t1 > 0)
  double flangeThickness; // 翼缘厚度 (t2 > 0)
  double radius;          // 过渡圆弧半径 (r > 0)
  double length;          // 长度 (L > 0)
};

TopoDS_Shape create_ibeam(const ibeam_params &params);
TopoDS_Shape create_ibeam(const ibeam_params &params, const gp_Pnt &position,
                          const gp_Dir &xDirection = gp::DX(),
                          const gp_Dir &zDirection = gp::DZ());

/**
 * @brief 轻型工字钢参数结构体
 */
struct light_ibeam_params {
  double height;          // 总高度 (H > 0)
  double flangeWidth;     // 翼缘宽度 (B > 0)
  double webThickness;    // 腹板厚度 (t1 > 0)
  double flangeThickness; // 翼缘厚度 (t2 > 0)
  double radius;          // 过渡圆弧半径 (r > 0)
  double length;          // 长度 (L > 0)
  double flangeSlope;     // 翼缘坡度 (0 ≤ S < 1)
};

TopoDS_Shape create_light_ibeam(const light_ibeam_params &params);
TopoDS_Shape create_light_ibeam(const light_ibeam_params &params,
                                const gp_Pnt &position,
                                const gp_Dir &xDirection = gp::DX(),
                                const gp_Dir &zDirection = gp::DZ());

/**
 * @brief H型钢参数结构体
 */
struct hbeam_params {
  double height;          // 总高度 (H > 0)
  double flangeWidth;     // 翼缘宽度 (B > 0)
  double webThickness;    // 腹板厚度 (t1 > 0)
  double flangeThickness; // 翼缘厚度 (t2 > 0)
  double radius;          // 过渡圆弧半径 (r > 0)
  double length;          // 长度 (L > 0)
};
TopoDS_Shape create_hbeam(const hbeam_params &params);
TopoDS_Shape create_hbeam(const hbeam_params &params, const gp_Pnt &position,
                          const gp_Dir &xDirection = gp::DX(),
                          const gp_Dir &zDirection = gp::DZ());
/**
 * @brief 槽钢参数结构体
 */
struct beam_channel_params {
  double height;          // 总高度 (H > 0)
  double flangeWidth;     // 翼缘宽度 (B > 0)
  double webThickness;    // 腹板厚度 (t1 > 0)
  double flangeThickness; // 翼缘厚度 (t2 > 0)
  double radius;          // 过渡圆弧半径 (r > 0)
  double length;          // 长度 (L > 0)
};

TopoDS_Shape create_beam_channel(const beam_channel_params &params);
TopoDS_Shape create_beam_channel(const beam_channel_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &xDirection = gp::DX(),
                                 const gp_Dir &zDirection = gp::DZ());

/**
 * @brief 轻型槽钢参数结构体
 */
struct light_beam_channel_params {
  double height;          // 总高度 (H > 0)
  double flangeWidth;     // 翼缘宽度 (B > 0)
  double webThickness;    // 腹板厚度 (t1 > 0)
  double flangeThickness; // 翼缘厚度 (t2 > 0)
  double radius;          // 过渡圆弧半径 (r > 0)
  double length;          // 长度 (L > 0)
  double flangeSlope;     // 翼缘坡度 (0 ≤ S < 1)
};

TopoDS_Shape create_light_beam_channel(const light_beam_channel_params &params);
TopoDS_Shape create_light_beam_channel(const light_beam_channel_params &params,
                                       const gp_Pnt &position,
                                       const gp_Dir &xDirection = gp::DX(),
                                       const gp_Dir &zDirection = gp::DZ());

/**
 * @brief 扁钢参数结构体
 */
struct flat_steel_params {
  double width;     // 宽度 (W > 0)
  double thickness; // 厚度 (T > 0)
  double length;    // 长度 (L > 0)
};
TopoDS_Shape create_flat_steel(const flat_steel_params &params);
TopoDS_Shape create_flat_steel(const flat_steel_params &params,
                               const gp_Pnt &position,
                               const gp_Dir &xDirection = gp::DX(),
                               const gp_Dir &zDirection = gp::DZ());

/**
 * @brief L型钢参数结构体
 */
struct lsteel_params {
  double height;    // 高度 (H > 0)
  double width;     // 宽度 (W > 0)
  double thickness; // 厚度 (T > 0)
  double radius;    // 过渡圆弧半径 (R ≥ 0)
  double length;    // 长度 (L > 0)
};

TopoDS_Shape create_lsteel(const lsteel_params &params);
TopoDS_Shape create_lsteel(const lsteel_params &params, const gp_Pnt &position,
                           const gp_Dir &xDirection = gp::DX(),
                           const gp_Dir &zDirection = gp::DZ());

/**
 * @brief T型钢参数结构体
 */
struct tsteel_params {
  double height;          // 高度 (H > 0)
  double width;           // 宽度 (W > 0)
  double webThickness;    // 腹板厚度 (T1 > 0)
  double flangeThickness; // 翼缘厚度 (T2 > 0)
  double radius;          // 过渡圆弧半径 (R ≥ 0)
  double length;          // 长度 (L > 0)
};

TopoDS_Shape create_tsteel(const tsteel_params &params);
TopoDS_Shape create_tsteel(const tsteel_params &params, const gp_Pnt &position,
                           const gp_Dir &xDirection = gp::DX(),
                           const gp_Dir &zDirection = gp::DZ());

/**
 * @brief 圆钢参数结构体
 */
struct round_steel_params {
  double diameter; // 直径 (D > 0)
  double length;   // 长度 (L > 0)
};

TopoDS_Shape create_round_steel(const round_steel_params &params);
TopoDS_Shape create_round_steel(const round_steel_params &params,
                                const gp_Pnt &position,
                                const gp_Dir &xDirection = gp::DX());

/**
 * @brief 圆钢管参数结构体
 */
struct round_steel_tube_params {
  double outerDiameter; // 外径 (OD > ID)
  double innerDiameter; // 内径 (ID > 0)
  double length;        // 长度 (L > 0)
};

TopoDS_Shape create_round_steel_tube(const round_steel_tube_params &params);
TopoDS_Shape create_round_steel_tube(const round_steel_tube_params &params,
                                     const gp_Pnt &position,
                                     const gp_Dir &xDirection = gp::DX());

/**
 * @brief 矩形钢管参数结构体
 */
struct rectangular_steel_tube_params {
  double height;    // 高度 (H > 0)
  double width;     // 宽度 (W > 0)
  double thickness; // 厚度 (T > 0)
  double length;    // 长度 (L > 0)
};

TopoDS_Shape
create_rectangular_steel_tube(const rectangular_steel_tube_params &params);
TopoDS_Shape create_rectangular_steel_tube(
    const rectangular_steel_tube_params &params, const gp_Pnt &position,
    const gp_Dir &xDirection = gp::DX(), const gp_Dir &zDirection = gp::DZ());

/**
 * @brief 方形钢管参数结构体
 */
struct square_steel_tube_params {
  double size;      // 外形尺寸 (S > 0)
  double thickness; // 壁厚 (T > 0)
  double length;    // 长度 (L > 0)
};

TopoDS_Shape create_square_steel_tube(const square_steel_tube_params &params);
TopoDS_Shape create_square_steel_tube(const square_steel_tube_params &params,
                                      const gp_Pnt &position,
                                      const gp_Dir &xDirection = gp::DX(),
                                      const gp_Dir &zDirection = gp::DZ());

/**
 * @brief 双槽钢参数结构体
 */
struct double_channel_steel_params : public beam_channel_params {
  double spacing; // 间距 (S >= 0)
};

TopoDS_Shape
create_double_channel_steel(const double_channel_steel_params &params);
TopoDS_Shape create_double_channel_steel(
    const double_channel_steel_params &params, const gp_Pnt &position,
    const gp_Dir &xDirection = gp::DX(), const gp_Dir &zDirection = gp::DZ());

struct equilateral_double_angle_steel_params
    : public equilateral_angle_steel_params {
  double spacing; // 间距 (S >= 0)
};

TopoDS_Shape create_equilateral_double_angle_steel(
    const equilateral_double_angle_steel_params &params);
TopoDS_Shape create_equilateral_double_angle_steel(
    const equilateral_double_angle_steel_params &params, const gp_Pnt &position,
    const gp_Dir &xDirection = gp::DX(), const gp_Dir &zDirection = gp::DZ());

struct unequal_angle_steel_params : public scalene_angle_steel_params {
  double spacing; // 间距 (S >= 0)
};

TopoDS_Shape
create_unequal_angle_steel(const unequal_angle_steel_params &params);
TopoDS_Shape create_unequal_angle_steel(
    const unequal_angle_steel_params &params, const gp_Pnt &position,
    const gp_Dir &xDirection = gp::DX(), const gp_Dir &zDirection = gp::DZ());

struct polygon_tube_params {
  double side_length; // 边长 (L > 0)
  double thickness;   // 壁厚 (T > 0)
  double length;      // 长度 (Len > 0)
  int sides;          // 边数 (N >= 3)
};

TopoDS_Shape create_polygon_tube(const polygon_tube_params &params);
TopoDS_Shape create_polygon_tube(const polygon_tube_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &xDirection = gp::DX());

struct bored_pile_params {
  double H1;                 // 上部圆柱高度
  double H2;                 // 过渡段高度
  double H3;                 // 底部圆柱高度
  double H4;                 // 桩头高度
  double d;                  // 上部直径
  double D;                  // 底部直径
  double filletRadius = 0.0; // 圆角半径，默认为0
};
TopoDS_Shape create_bored_pile_foundation(const bored_pile_params &params);
TopoDS_Shape create_bored_pile_foundation(const bored_pile_params &params,
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

  // 圆角参数
  double filletRadius = 0.0; // 圆角半径
};

TopoDS_Shape create_pile_cap_foundation(const pile_cap_params &params);
TopoDS_Shape create_pile_cap_foundation(const pile_cap_params &params,
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

TopoDS_Shape create_rock_anchor_foundation(const rock_anchor_params &params);
TopoDS_Shape create_rock_anchor_foundation(const rock_anchor_params &params,
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

TopoDS_Shape
create_rock_pile_cap_foundation(const rock_pile_cap_params &params);
TopoDS_Shape
create_rock_pile_cap_foundation(const rock_pile_cap_params &params,
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

TopoDS_Shape create_embedded_rock_anchor_foundation(
    const embedded_rock_anchor_params &params);
TopoDS_Shape create_embedded_rock_anchor_foundation(
    const embedded_rock_anchor_params &params, const gp_Pnt &position,
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

TopoDS_Shape create_inclined_rock_anchor_foundation(
    const inclined_rock_anchor_params &params);
TopoDS_Shape create_inclined_rock_anchor_foundation(
    const inclined_rock_anchor_params &params, const gp_Pnt &position,
    const gp_Dir &direction = gp::DZ());

struct excavated_foundation_params {
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

TopoDS_Shape
create_excavated_foundation(const excavated_foundation_params &params);
TopoDS_Shape
create_excavated_foundation(const excavated_foundation_params &params,
                            const gp_Pnt &position,
                            const gp_Dir &direction = gp::DZ());

struct step_foundation_params {
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

TopoDS_Shape create_step_foundation(const step_foundation_params &params);
TopoDS_Shape create_step_foundation(const step_foundation_params &params,
                                    const gp_Pnt &position,
                                    const gp_Dir &direction = gp::DZ());

struct step_plate_foundation_params {
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

TopoDS_Shape
create_step_plate_foundation(const step_plate_foundation_params &params);
TopoDS_Shape
create_step_plate_foundation(const step_plate_foundation_params &params,
                             const gp_Pnt &position,
                             const gp_Dir &direction = gp::DZ());

struct sloped_base_foundation_params {
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

TopoDS_Shape
create_sloped_base_foundation(const sloped_base_foundation_params &params);
TopoDS_Shape
create_sloped_base_foundation(const sloped_base_foundation_params &params,
                              const gp_Pnt &position,
                              const gp_Dir &direction = gp::DZ());

struct composite_caisson_foundation_params {
  // 高度参数
  double H1; // 上部沉井高度
  double H2; // 过渡段高度
  double H3; // 下部基础高度
  double H4; // 预留参数

  // 尺寸参数
  double b;  // 预留参数
  double D;  // 沉井直径
  double t;  // 沉井壁厚
  double B1; // 过渡段底部宽度
  double B2; // 下部基础宽度
  double L1; // 过渡段底部长度
  double L2; // 下部基础长度
};

TopoDS_Shape create_composite_caisson_foundation(
    const composite_caisson_foundation_params &params);
TopoDS_Shape create_composite_caisson_foundation(
    const composite_caisson_foundation_params &params, const gp_Pnt &position,
    const gp_Dir &direction = gp::DZ());

struct raft_foundation_params {
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

TopoDS_Shape create_raft_foundation(const raft_foundation_params &params);
TopoDS_Shape create_raft_foundation(const raft_foundation_params &params,
                                    const gp_Pnt &position,
                                    const gp_Dir &direction = gp::DZ());

struct direct_buried_foundation_params {
  // 高度参数
  double H1; // 基础主体高度
  double H2; // 固定盘高度（可选）

  // 尺寸参数
  double d; // 基础主体直径
  double D; // 圆形固定盘直径（可选）
  double B; // 方形固定盘边长（可选）
  double t; // 壁厚

  // 固定盘标志
  bool hasBasePlate = false;   // 是否有固定盘
  bool isCircularPlate = true; // 是否为圆形固定盘
};

TopoDS_Shape
create_direct_buried_foundation(const direct_buried_foundation_params &params);
TopoDS_Shape
create_direct_buried_foundation(const direct_buried_foundation_params &params,
                                const gp_Pnt &position,
                                const gp_Dir &direction = gp::DZ());

struct steel_sleeve_foundation_params {
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

TopoDS_Shape
create_steel_sleeve_foundation(const steel_sleeve_foundation_params &params);
TopoDS_Shape
create_steel_sleeve_foundation(const steel_sleeve_foundation_params &params,
                               const gp_Pnt &position,
                               const gp_Dir &direction = gp::DZ());

struct precast_column_foundation_params {
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

TopoDS_Shape create_precast_column_foundation(
    const precast_column_foundation_params &params);
TopoDS_Shape
create_precast_column_foundation(const precast_column_foundation_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction = gp::DZ());

struct precast_pinned_foundation_params {
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

TopoDS_Shape create_precast_pinned_foundation(
    const precast_pinned_foundation_params &params);
TopoDS_Shape
create_precast_pinned_foundation(const precast_pinned_foundation_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction = gp::DZ());

struct precast_metal_support_foundation_params {
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

TopoDS_Shape create_precast_metal_support_foundation(
    const precast_metal_support_foundation_params &params);
TopoDS_Shape create_precast_metal_support_foundation(
    const precast_metal_support_foundation_params &params,
    const gp_Pnt &position, const gp_Dir &direction = gp::DZ());

struct precast_concrete_support_foundation_params {
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

TopoDS_Shape create_precast_concrete_support_foundation(
    const precast_concrete_support_foundation_params &params);
TopoDS_Shape create_precast_concrete_support_foundation(
    const precast_concrete_support_foundation_params &params,
    const gp_Pnt &position, const gp_Dir &direction = gp::DZ());

struct disk_insulator_params {
  double diskDiameter;     // 盘直径
  double diskThickness;    // 盘厚度
  int diskCount;           // 盘数量
  double rodDiameter;      // 芯棒直径
  double rodLength;        // 芯棒长度
  bool hasThread;          // 是否包含端部螺纹
  double threadLength;     // 螺纹长度
  double threadPitch;      // 螺纹间距
  double angleL;           // 左侧V串夹角(度)，与angleR同时为0表示I串
  double angleR;           // 右侧V串夹角(度)，与angleL同时为0表示I串
  double horizontalLength; // U串连接长度(mm)，非U串为0
};

TopoDS_Shape create_disk_insulator(const disk_insulator_params &params);
TopoDS_Shape create_disk_insulator(double diskDiameter, double diskHeight,
                                   int diskCount, const gp_Pnt &position,
                                   const gp_Dir &axisDirection = gp::DZ());

struct rod_insulator_params {
  double rodDiameter;      // 芯棒直径
  double rodLength;        // 芯棒长度
  double shedDiameter;     // 伞裙直径
  double shedThickness;    // 伞裙厚度
  int shedCount;           // 伞裙数量
  bool hasThread;          // 是否包含端部螺纹
  double threadLength;     // 螺纹长度
  double threadPitch;      // 螺纹间距
  double angleL;           // 左侧V串夹角(度)，与angleR同时为0表示I串
  double angleR;           // 右侧V串夹角(度)，与angleL同时为0表示I串
  double horizontalLength; // U串连接长度(mm)，非U串为0
};

TopoDS_Shape create_rod_insulator(const rod_insulator_params &params);
TopoDS_Shape create_rod_insulator(double rodDiameter, double rodLength,
                                  double shedDiameter, double shedHeight,
                                  double shedSpacing, const gp_Pnt &position,
                                  const gp_Dir &axisDirection = gp::DZ());
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
TopoDS_Shape create_transmission_line(double conductorRadius,
                                      double bundleSpacing, int bundleCount,
                                      double spanLength, double sag,
                                      const gp_Pnt &position,
                                      const gp_Dir &direction = gp::DX(),
                                      const gp_Dir &normal = gp::DZ());

/**
 * 双分裂时：垂直排列-1 水平排列-2；三分裂时： 正三角排列-1
倒三角排列-2。其他分裂时取0。 四分裂、六分裂、八分裂为正多边形
 */
// 线夹基础参数
struct fitting_params {
  double subNum;            // 分裂数量
  double conductorDiameter; // 子导线直径(mm)
  double splitDistance;     // 分裂间距(mm)
  int subType; // 排列方式(1/2) 双分裂时：  1: 垂直排列，2: 水平排列 三分裂时：
               // 1: 正三角排列，2: 倒三角排列
  double fittingLength;   // 金具长度(mm)
  int gradingRingCount;   // 均压环个数
  double gradingRingPos;  // 安装位置(mm)
  double gradingRingHigh; // 高度(mm)
  double gradingRingRad;  // 半径(mm)
};

// 绝缘子材质
enum class InsulatorMaterial {
  CERAMIC = 1,  // 陶瓷
  GLASS = 2,    // 玻璃
  COMPOSITE = 3 // 复合
};

// 排列方式
enum class ArrangementType {
  HORIZONTAL = 1, // 水平
  VERTICAL = 2    // 垂直
};

// 串用途
enum class ApplicationType {
  CONDUCTOR = 1,  // 导线
  GROUND_WIRE = 2 // 地线
};

// 串类型
enum class StringType {
  SUSPENSION = 1, // 悬垂
  TENSION = 2     // 耐张
};

// 复合绝缘子参数子结构
struct CompositeInsulatorParams {
  double majorRadius; // 大半径(mm)
  double minorRadius; // 小半径(mm)
  double gap;         // 间隙(mm)
};

// 主参数结构体
struct PowerTowerComponent {
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
    int count;                   // 联数
    double spacing;              // 联间距(mm)
    ArrangementType arrangement; // 排列方式
  } multiLink;

  // 绝缘子参数
  struct {
    boost::variant<double, CompositeInsulatorParams> radius; // 半径或复合参数
    double height;                                           // 结构高度(mm)
    int leftCount;                                           // 左侧片数
    int rightCount;                                          // 右侧片数
    InsulatorMaterial material;                              // 材质
  } insulator;

  // 均压环配置
  struct {
    int count;       // 个数
    double position; // 安装位置(mm)
    double height;   // 环高度(mm)
    double radius;   // 环半径(mm)
  } gradingRing;

  // 用途类型
  ApplicationType application;
  StringType stringType;
};

} // namespace topo
} // namespace flywave
