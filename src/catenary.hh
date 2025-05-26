#pragma once

#include <GeomAPI_PointsToBSpline.hxx>
#include <Geom_BSplineCurve.hxx>
#include <gp_Ax3.hxx>
#include <gp_Mat.hxx>
#include <gp_Pnt.hxx>
#include <gp_Trsf.hxx>
#include <gp_Vec.hxx>
#include <math.hxx>
#include <math_BissecNewton.hxx>
#include <math_FunctionWithDerivative.hxx>
#include <vector>

namespace flywave {

// Helper function to solve using bisection method
template <typename Func>
double solveBisect(const Func &func, double x0, double x1, double tolerance,
                   int maxIterations = 8) {
  double f0 = func(x0);
  double f1 = func(x1);
  if (f0 * f1 > 0) // same sign
  {
    return x0;
  }

  double midPoint = 0.0;
  for (int i = 0; i < maxIterations; ++i) {
    midPoint = (x0 + x1) / 2.0;
    double fMidpoint = func(midPoint);
    if (fabs(fMidpoint) <= tolerance) {
      return midPoint;
    } else if (f0 * fMidpoint > 0) {
      x0 = midPoint;
      f0 = fMidpoint;
    } else {
      x1 = midPoint;
      f1 = fMidpoint;
    }
  }
  return midPoint;
}

namespace {
// Function for a in terms of arc length L, height difference h,
// and horizontal distance d
class GFunc : public math_FunctionWithDerivative {
public:
  GFunc(double d_, double L, double h) : d(d_), rootLh(sqrt(L * L - h * h)) {}

  virtual Standard_Boolean Value(double a, double &F) override {
    F = 2.0 * a * sinh(d / (2.0 * a)) - rootLh;
    return Standard_True;
  }

  virtual Standard_Boolean Derivative(double a, double &D) override {
    double da = d / a;
    D = 2.0 * sinh(da / 2.0) - da * cosh(da / 2.0);
    return Standard_True;
  }

  virtual Standard_Boolean Values(double a, double &F, double &D) override {
    Value(a, F);
    Derivative(a, D);
    return Standard_True;
  }

  double d;
  double rootLh;
};

// Catenary function and solver
struct CatenaryFunc {
  double a;
  double x1;
  double C;
  double L;
  double d;
  double h;

  CatenaryFunc(double a_, double x1_, double C_, double L_ = 0.0,
               double d_ = 0.0, double h_ = 0.0)
      : a(a_), x1(x1_), C(C_), L(L_), d(d_), h(h_) {}

  double operator()(double x) const { return a * cosh((x + x1) / a) + C; }

  static CatenaryFunc solveIt(double L, double d, double h) {
    if (L <= fabs(h)) {
      throw Standard_ConstructionError(
          "Invalid parameters: L must be greater than |h|");
    }

    GFunc gfunc(d, L, h);
    math_BissecNewton solver(1e-6);

    // 改进求解器参数范围
    double lower = std::max(0.1 * d, 1e-3); // 防止极小值
    double upper = std::min(2.0 * d, 1e5);  // 限制最大搜索范围
    int maxIterations = 200;                // 增加最大迭代次数

    // 验证函数值符号变化
    double flow = 0.0, fupp = 0.0;
    gfunc.Value(lower, flow);
    gfunc.Value(upper, fupp);

    // 自动扩展搜索范围直到找到有效区间
    while (flow * fupp > 0 && upper < 1e6) {
      upper *= 2.0;
      gfunc.Value(upper, fupp);
    }

    solver.Perform(gfunc, lower, upper, maxIterations);

    if (!solver.IsDone()) {
      throw Standard_ConstructionError(
          "Failed to converge in parameter solving");
    }
    double a = solver.Root();
    if (a <= 0.0) {
      throw Standard_ConstructionError("Invalid catenary parameter a");
    }

    double x1 = (a * log((L + h) / (L - h)) - d) / 2.0;
    double C = -a * cosh(x1 / a);

    return CatenaryFunc(a, x1, C, L, d, h);
  }
};

// Function to find minimum height difference
class MinCatHeight {
public:
  MinCatHeight(double d_, double h_, double refHeight_ = 0.0)
      : d(d_), h(h_), refHeight(refHeight_) {}

  double operator()(double L) const {
    if (L * L < d * d + h * h)
      return 0.0;

    CatenaryFunc func = CatenaryFunc::solveIt(L, d, h);
    if (func.x1 > 0.0)
      return 0.0;

    return (func(-func.x1) - refHeight);
  }

  double d;
  double h;
  double refHeight;
};
} // namespace

inline Handle(Geom_BSplineCurve)
    makeCatenaryCurve(const gp_Pnt &p1, const gp_Pnt &p2,
                      const gp_Ax3 &orientation, double slack, double maxSag,
                      double tessellation = 0.0) {
  // 增强参数验证
  if (slack <= 1.0 || slack > 100.0) {
    throw Standard_ConstructionError("Slack must be in range (1.0, 100.0]");
  }
  if (maxSag <= 0.0 || maxSag > 1e6) {
    throw Standard_ConstructionError("Max sag must be in range (0.0, 1e6]");
  }
  double dist = p1.Distance(p2);
  if (dist < Precision::Confusion()) {
    throw Standard_ConstructionError("Points p1 and p2 are too close");
  }
  if (dist > 1e6) {
    throw Standard_ConstructionError("Distance between points is too large");
  }

  // Create transformation to local frame at p1
  gp_Trsf trsf;
  const gp_Ax3 worldAx3;

  // 修改判断逻辑：即使p1是原点，只要orientation与默认坐标系不一致就需要创建变换
  if (orientation.IsCoplanar(worldAx3, Precision::Confusion(),
                             Precision::Angular())) {
    // 当orientation与世界坐标系一致时，仅平移原点
    gp_Ax3 localFrame(p1, worldAx3.Direction(), worldAx3.XDirection());
    trsf.SetTransformation(localFrame, worldAx3);
  } else {
    // 自定义orientation时，总是需要创建变换
    gp_Ax3 targetFrame(p1, orientation.Direction(), orientation.XDirection());
    trsf.SetTransformation(orientation, targetFrame);
  }

  // Transform p2 to local frame
  gp_Pnt p2local = p2.Transformed(trsf);

  // Determine if we need to swap points
  bool swapped = (p2local.Z() < 0.0);
  gp_Vec Xaxis;
  if (swapped) {
    Xaxis = gp_Vec(-p2local.X(), -p2local.Y(), 0.0);
  } else {
    Xaxis = gp_Vec(p2local.X(), p2local.Y(), 0.0);
  }

  // Horizontal distance and height difference
  double d = Xaxis.Magnitude();

  // 修改为设置默认X轴方向
  if (d < Precision::Confusion()) {
    // 当水平距离接近零时，使用默认X轴方向
    Xaxis = gp_Vec(1.0, 0.0, 0.0); // 默认X轴方向
    d = 1.0;                       // 设置最小有效距离
    swapped = false;               // 重置交换状态
  }

  Xaxis.Normalize();

  // Create catenary frame
  gp_Ax3 catFrame(p1, gp_Dir(0, 0, 1), gp_Dir(Xaxis.X(), Xaxis.Y(), 0));

  double h = swapped ? -p2local.Z() : p2local.Z();
  double straightDist = p2local.Distance(gp_Pnt(0, 0, 0));

  // Solve for catenary parameters
  CatenaryFunc func = CatenaryFunc::solveIt(straightDist * slack, d, h);

  // Check for excessive sag
  double xMin = -func.x1;
  double yMin = func(xMin);
  if (0.0 < xMin && yMin < -maxSag) {
    MinCatHeight minimum(d, h, -maxSag);
    double newGuess = ((slack - 1.0) * 0.01 + 1.0) * straightDist;
    double Lmin = solveBisect(minimum, newGuess, straightDist * slack, 0.01, 8);
    func = CatenaryFunc::solveIt(Lmin, d, h);
  }

  // 自动计算最优细分尺寸
  if (tessellation <= 0.0 || tessellation > straightDist / 20 ||
      tessellation < straightDist / 1000.0) {
    // 基础细分尺寸基于距离和松弛度
    double baseTess = straightDist / 20.0; // 基础细分尺寸为距离的1/20
    // 考虑松弛度影响 - 松弛度越大，需要更细的细分
    double slackFactor = 1.0 + (slack - 1.0) * 0.5;
    // 考虑高度差影响 - 高度差越大，需要更细的细分
    double heightFactor = 1.0 + std::abs(h) / (straightDist + 1e-12) * 2.0;
    // 计算最终细分尺寸
    tessellation = baseTess / (slackFactor * heightFactor);
    // 确保在合理范围内 (不小于1mm)
    tessellation = std::max(1.0, tessellation);
  }

  int numSteps = ceil(straightDist / tessellation);

  double begin, inc;
  if (swapped) {
    inc = -d / numSteps;
    begin = d + inc;
  } else {
    inc = d / numSteps;
    begin = inc;
  }

  // 生成悬垂线控制点
  TColgp_Array1OfPnt poles(1, numSteps + 1);
  double x = begin;
  for (int i = 1; i <= numSteps + 1; ++i, x += inc) {
    double z = func(x);
    poles.SetValue(i, gp_Pnt(x, 0, z));
  }

  if (swapped) {
    poles.SetValue(1, gp_Pnt(d, 0, -h));            // 起点对应p2位置
    poles.SetValue(poles.Upper(), gp_Pnt(0, 0, 0)); // 终点对应p1位置
  } else {
    poles.SetValue(1, gp_Pnt(0, 0, 0));             // 起点对应p1位置
    poles.SetValue(poles.Upper(), gp_Pnt(d, 0, h)); // 终点对应p2位置
  }

  // 创建BSpline曲线
  GeomAPI_PointsToBSpline approx(poles);
  if (!approx.IsDone()) {
    throw Standard_ConstructionError("Failed to create catenary curve");
  }

  // 应用坐标系变换
  gp_Trsf catToWorld;
  catToWorld.SetTransformation(catFrame, gp_Ax3());

  Handle(Geom_BSplineCurve) curve = approx.Curve();
  curve->Transform(catToWorld);

  return curve;
}

inline void makeCatenary(const gp_Pnt &p1, const gp_Pnt &p2,
                         const gp_Ax3 &orientation, double slack, double maxSag,
                         std::vector<gp_Pnt> &result, double tessellation) {
  // 增强参数验证
  if (slack <= 1.0 || slack > 100.0) {
    throw Standard_ConstructionError("Slack must be in range (1.0, 100.0]");
  }
  if (maxSag <= 0.0 || maxSag > 1e6) {
    throw Standard_ConstructionError("Max sag must be in range (0.0, 1e6]");
  }
  double dist = p1.Distance(p2);
  if (dist < Precision::Confusion()) {
    throw Standard_ConstructionError("Points p1 and p2 are too close");
  }
  if (dist > 1e6) {
    throw Standard_ConstructionError("Distance between points is too large");
  }

  // Create transformation to local frame at p1
  gp_Trsf trsf;
  const gp_Ax3 worldAx3;

  // 修改判断逻辑：即使p1是原点，只要orientation与默认坐标系不一致就需要创建变换
  if (orientation.IsCoplanar(worldAx3, Precision::Confusion(),
                             Precision::Angular())) {
    // 当orientation与世界坐标系一致时，仅平移原点
    gp_Ax3 localFrame(p1, worldAx3.Direction(), worldAx3.XDirection());
    trsf.SetTransformation(localFrame, worldAx3);
  } else {
    // 自定义orientation时，总是需要创建变换
    gp_Ax3 targetFrame(p1, orientation.Direction(), orientation.XDirection());
    trsf.SetTransformation(orientation, targetFrame);
  }

  // Transform p2 to local frame
  gp_Pnt p2local = p2.Transformed(trsf);

  // Determine if we need to swap points
  bool swapped = (p2local.Z() < 0.0);
  gp_Vec Xaxis;
  if (swapped) {
    Xaxis = gp_Vec(-p2local.X(), -p2local.Y(), 0.0);
  } else {
    Xaxis = gp_Vec(p2local.X(), p2local.Y(), 0.0);
  }

  // Horizontal distance and height difference
  double d = Xaxis.Magnitude();
  Xaxis.Normalize();
  gp_Vec Yaxis = gp_Dir(0, 0, 1).Crossed(Xaxis);

  // Create catenary frame
  gp_Ax3 catFrame(p1, gp_Dir(0, 0, 1), gp_Dir(Xaxis.X(), Xaxis.Y(), 0));

  double h = swapped ? -p2local.Z() : p2local.Z();
  double straightDist = p2local.Distance(gp_Pnt(0, 0, 0));

  // Solve for catenary parameters
  CatenaryFunc func = CatenaryFunc::solveIt(straightDist * slack, d, h);

  // Check for excessive sag
  double xMin = -func.x1;
  double yMin = func(xMin);
  if (0.0 < xMin && yMin < -maxSag) {
    MinCatHeight minimum(d, h, -maxSag);
    double newGuess = ((slack - 1.0) * 0.01 + 1.0) * straightDist;
    double Lmin = solveBisect(minimum, newGuess, straightDist * slack, 0.01, 8);
    func = CatenaryFunc::solveIt(Lmin, d, h);
  }

  // 自动计算最优细分尺寸
  if (tessellation <= 0.0 || tessellation > straightDist / 20 ||
      tessellation < straightDist / 1000.0) {
    // 基础细分尺寸基于距离和松弛度
    double baseTess = straightDist / 20.0; // 基础细分尺寸为距离的1/20
    // 考虑松弛度影响 - 松弛度越大，需要更细的细分
    double slackFactor = 1.0 + (slack - 1.0) * 0.5;
    // 考虑高度差影响 - 高度差越大，需要更细的细分
    double heightFactor = 1.0 + std::abs(h) / (straightDist + 1e-12) * 2.0;
    // 计算最终细分尺寸
    tessellation = baseTess / (slackFactor * heightFactor);
    // 确保在合理范围内 (不小于1mm)
    tessellation = std::max(1.0, tessellation);
  }

  // Generate points along the catenary
  std::vector<gp_Pnt> cablePts;
  int numSteps = ceil(straightDist / tessellation);
  double begin, inc;

  if (swapped) {
    inc = -d / numSteps;
    begin = d + inc;
    cablePts.push_back(gp_Pnt(d, 0, h));
  } else {
    inc = d / numSteps;
    begin = inc;
    cablePts.push_back(gp_Pnt(0, 0, 0));
  }

  double x = begin;
  for (int i = 1; i <= numSteps; ++i, x += inc) {
    double z = func(x);
    cablePts.push_back(gp_Pnt(x, 0, z));
  }

  // 生成悬垂线控制点时添加端点修正
  if (swapped) {
    cablePts.front() = gp_Pnt(d, 0, -h); // 强制设置起点为p2位置
    cablePts.back() = gp_Pnt(0, 0, 0);   // 强制设置终点为p1位置
  } else {
    cablePts.front() = gp_Pnt(0, 0, 0); // 强制设置起点为p1位置
    cablePts.back() = gp_Pnt(d, 0, h);  // 强制设置终点为p2位置
  }

  // Transform points back to world coordinates
  gp_Trsf catToWorld;
  catToWorld.SetTransformation(catFrame, gp_Ax3());

  for (auto &pt : cablePts) {
    result.push_back(pt.Transformed(catToWorld));
  }
}

inline gp_Ax3 createOrientation(const gp_Pnt &p1, const gp_Pnt &p2,
                                const gp_Dir &upDir) {
  // 计算从p1到p2的方向向量
  gp_Vec dirVec(p1, p2);
  if (dirVec.Magnitude() < Precision::Confusion()) {
    throw Standard_ConstructionError("Points are too close");
  }
  dirVec.Normalize();

  // Z轴方向为指定的upDir
  gp_Dir zAxis = upDir; 

  // 计算X轴方向（与p1-p2方向正交）
  if (dirVec.Magnitude() < Precision::Confusion()) {
    // 当p1-p2方向与upDir平行时，使用默认X轴
    dirVec = gp_Vec(1, 0, 0);
  }

  return gp_Ax3(p1, zAxis, dirVec);
}
} // namespace flywave
