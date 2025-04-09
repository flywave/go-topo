#pragma once

#include <TopoDS_Shape.hxx>
#include <gp_Ax2.hxx>
#include <gp_Dir.hxx>
#include <gp_Pnt.hxx>

namespace flywave {
namespace topo {

TopoDS_Shape create_sphere(double radius);
TopoDS_Shape create_sphere(double radius, const gp_Pnt &center);
TopoDS_Shape create_rotational_ellipsoid(double polarRadius,
                                         double equatorialRadius,
                                         double height);
TopoDS_Shape
create_rotational_ellipsoid(double polarRadius, double equatorialRadius,
                            double height, const gp_Pnt &center,
                            const gp_Dir &xDirection = gp_Dir(1, 0, 0));

struct bored_pile_params {
  double H1;                 // 上部圆柱高度
  double H2;                 // 过渡段高度
  double H3;                 // 底部圆柱高度
  double H4;                 // 桩头高度
  double d;                  // 上部直径
  double D;                  // 底部直径
  double filletRadius = 0.0; // 圆角半径，默认为0
};

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

struct embedded_rock_anchor_params {
  // 高度参数
  double H1; // 上部圆柱高度
  double H2; // 过渡段高度
  double H3; // 底部圆柱高度

  // 直径参数
  double d; // 上部直径
  double D; // 底部直径
};

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

struct wire_params {
  std::string type;               // 型号
  double sectionalArea;           // 截面积(mm²)
  double outsideDiameter;         // 外径(mm)
  double wireWeight;              // 单位长度质量(kg/km)
  double coefficientOfElasticity; // 弹性系数(N/mm²)
  double expansionCoefficient;    // 线膨胀系数(1/℃)
  double ratedStrength;           // 额定拉断力(N)
};

} // namespace topo
} // namespace flywave