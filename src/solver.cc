#include "solver.hh"
#include <IpIpoptApplication.hpp>
#include <IpSolveStatistics.hpp>
#include <IpTNLP.hpp>
#include <boost/variant.hpp>
#include <gp_Dir.hxx>
#include <gp_Lin.hxx>
#include <gp_Pln.hxx>
#include <gp_Pnt.hxx>
#include <gp_Quaternion.hxx>
#include <gp_Trsf.hxx>
#include <memory>
#include <stdexcept>
#include <vector>

using namespace Ipopt;

namespace flywave {
namespace topo {
namespace {

DOF6 location_to_dof6(const gp_Trsf &loc) {
  gp_Vec v = loc.TranslationPart();
  gp_Quaternion q = loc.GetRotation();

  double alpha_2 = (1 - q.W()) / (1 + q.W());
  double a = (alpha_2 + 1) * q.X() / 2;
  double b = (alpha_2 + 1) * q.Y() / 2;
  double c = (alpha_2 + 1) * q.Z() / 2;

  std::array<double, 3> T{v.X(), v.Y(), v.Z()};
  std::array<double, 3> R{a, b, c};

  return {T, R};
}
} // namespace

class constraint_problem : public TNLP {
private:
  constraint_solver &solver_;
  std::vector<gp_Trsf> initial_transforms_;
  std::vector<Constraint> constraints_;
  std::vector<size_t> lockedEntities_;
  double scale_;
  size_t ne_;
  std::vector<gp_Trsf> final_transforms_;

  static gp_Trsf build_transform(const double *T, const double *R) {
    gp_Trsf transform;
    double a = R[0], b = R[1], c = R[2];
    double m = a * a + b * b + c * c;

    transform.SetRotation(gp_Quaternion(2 * a / (m + 1), 2 * b / (m + 1),
                                        2 * c / (m + 1), (1 - m) / (m + 1)));
    transform.SetTranslationPart(gp_Vec(T[0], T[1], T[2]));
    return transform;
  }

public:
  constraint_problem(constraint_solver &solver)
      : solver_(solver), initial_transforms_(solver.initial_transforms_),
        constraints_(solver.constraints_), lockedEntities_(solver.locked_),
        scale_(solver.scale_), ne_(solver.ne_) {}

  // 转换位置到优化参数
  static void transform_to_variables(const gp_Trsf &trsf, double *T,
                                     double *R) {
    gp_Vec translation = trsf.TranslationPart();
    gp_Quaternion quat = trsf.GetRotation();

    double alpha_2 = (1 - quat.W()) / (1 + quat.W());
    T[0] = translation.X();
    T[1] = translation.Y();
    T[2] = translation.Z();
    R[0] = (alpha_2 + 1) * quat.X() / 2;
    R[1] = (alpha_2 + 1) * quat.Y() / 2;
    R[2] = (alpha_2 + 1) * quat.Z() / 2;
  }

  // 转换优化参数到位置
  static gp_Trsf variables_to_transform(const double *T, const double *R) {
    gp_Trsf transform;
    double a = R[0], b = R[1], c = R[2];
    double m = a * a + b * b + c * c;

    gp_Quaternion quat(2 * a / (m + 1), 2 * b / (m + 1), 2 * c / (m + 1),
                       (1 - m) / (m + 1));

    transform.SetRotation(quat);
    transform.SetTranslationPart(gp_Vec(T[0], T[1], T[2]));
    return transform;
  }

  // Ipopt接口实现
  bool get_nlp_info(Index &n, Index &m, Index &nnz_jac_g, Index &nnz_h_lag,
                    IndexStyleEnum &index_style) override {
    n = static_cast<Index>(ne_ * 6); // 每个实体6个自由度(3平移+3旋转)
    m = static_cast<Index>(constraints_.size());
    nnz_jac_g = m * n; // 稠密雅可比矩阵
    nnz_h_lag = 0;     // 不使用二阶导数
    index_style = TNLP::C_STYLE;
    return true;
  }

  bool get_bounds_info(Index n, Number *x_l, Number *x_u, Index m, Number *g_l,
                       Number *g_u) override {
    // 设置变量边界
    for (Index i = 0; i < n; i++) {
      x_l[i] = -1e20; // 无下界
      x_u[i] = 1e20;  // 无上界
    }

    // 锁定实体的变量固定为0
    for (Index i = 0; i < ne_; i++) {
      if (lockedEntities_[i]) {
        x_l[i * 6] = x_u[i * 6] = 0;
        x_l[i * 6 + 1] = x_u[i * 6 + 1] = 0;
        x_l[i * 6 + 2] = x_u[i * 6 + 2] = 0;
        x_l[i * 6 + 3] = x_u[i * 6 + 3] = 0;
        x_l[i * 6 + 4] = x_u[i * 6 + 4] = 0;
        x_l[i * 6 + 5] = x_u[i * 6 + 5] = 0;
      }
    }

    // 设置约束边界(等式约束)
    for (Index i = 0; i < m; i++) {
      g_l[i] = g_u[i] = 0;
    }

    return true;
  }

  bool get_starting_point(Index n, bool init_x, Number *x, bool init_z,
                          Number *z_L, Number *z_U, Index m, bool init_lambda,
                          Number *lambda) override {
    // 设置初始点为0(相对于初始变换的偏移)
    for (Index i = 0; i < n; i++) {
      x[i] = 0;
    }
    return true;
  }

  bool eval_f(Index n, const Number *x, bool new_x,
              Number &obj_value) override {
    obj_value = 0.0;

    // 计算目标函数(所有约束成本之和)
    for (const auto &c : constraints_) {
      double cost = evaluate_constraint(c, x);
      obj_value += cost;
    }

    // 添加小的正则化项
    for (Index i = 0; i < n; i++) {
      if (!lockedEntities_[i / 6]) {
        obj_value += 1e-16 * x[i] * x[i];
      }
    }

    return true;
  }

  bool eval_grad_f(Index n, const Number *x, bool new_x,
                   Number *grad_f) override {
    // 初始化梯度为0
    std::fill(grad_f, grad_f + n, 0.0);

    // 计算每个约束对梯度的贡献
    for (const auto &constraint : constraints_) {
      const auto &markers = std::get<0>(constraint);
      ConstraintKind kind = std::get<1>(constraint);
      const auto &param = std::get<2>(constraint);
      const auto &entityIndices = std::get<3>(constraint);

      // 收集相关变量和初始状态
      std::vector<double> vars;
      std::vector<double> inits;
      std::vector<Index> var_indices;

      for (int entityIdx : entityIndices) { // 使用entityIndices而不是indices
        auto dof = location_to_dof6(initial_transforms_[entityIdx]);
        auto T0 = std::get<0>(dof);
        auto R0 = std::get<1>(dof);

        inits.insert(inits.end(), T0.begin(), T0.end());
        inits.insert(inits.end(), R0.begin(), R0.end());

        for (int i = 0; i < 6; i++) {
          vars.push_back(x[entityIdx * 6 + i]);
          var_indices.push_back(entityIdx * 6 + i);
        }
      }

      // 计算当前约束的梯度
      std::vector<double> constraint_grad(vars.size(), 0.0);
      compute_constraint_gradient(kind, inits, vars, param, scale_,
                                  constraint_grad);

      // 累加到全局梯度
      for (size_t i = 0; i < var_indices.size(); i++) {
        grad_f[var_indices[i]] += constraint_grad[i];
      }
    }

    // 添加正则化项的梯度
    for (Index i = 0; i < n; i++) {
      if (!lockedEntities_[i / 6]) {
        grad_f[i] += 2.0 * 1e-16 * x[i];
      }
    }

    return true;
  }

  bool eval_g(Index n, const Number *x, bool new_x, Index m,
              Number *g) override {
    // 计算所有约束值
    for (Index i = 0; i < m; i++) {
      const auto &markers = std::get<0>(constraints_[i]);
      ConstraintKind kind = std::get<1>(constraints_[i]);
      const auto &param = std::get<2>(constraints_[i]);
      const auto &entityIndices = std::get<3>(constraints_[i]);

      std::vector<double> vars;
      std::vector<double> inits;

      for (int entityIdx : entityIndices) { // 使用entityIndices
        auto dof = location_to_dof6(initial_transforms_[entityIdx]);
        auto T0 = std::get<0>(dof);
        auto R0 = std::get<1>(dof);
        inits.insert(inits.end(), T0.begin(), T0.end());
        inits.insert(inits.end(), R0.begin(), R0.end());

        for (int j = 0; j < 6; j++) {
          vars.push_back(x[entityIdx * 6 + j]);
        }
      }

      g[i] = compute_constraint_value(kind, inits, vars, param, scale_);
    }

    return true;
  }

  bool eval_jac_g(Index n, const Number *x, bool new_x, Index m, Index nele_jac,
                  Index *iRow, Index *jCol, Number *values) override {
    // 计算雅可比矩阵结构
    if (values == nullptr) {
      Index index = 0;
      for (Index i = 0; i < m; i++) {
        const auto &entityIndices =
            std::get<3>(constraints_[i]); // 获取entityIndices
        for (int entityIdx : entityIndices) {
          for (Index j = 0; j < 6; j++) {
            iRow[index] = i;
            jCol[index] = entityIdx * 6 + j;
            index++;
          }
        }
      }
      return true;
    }

    // 计算雅可比矩阵值
    Index index = 0;
    for (Index i = 0; i < m; i++) {
      const auto &markers = std::get<0>(constraints_[i]);
      ConstraintKind kind = std::get<1>(constraints_[i]);
      const auto &param = std::get<2>(constraints_[i]);
      const auto &entityIndices = std::get<3>(constraints_[i]);

      std::vector<double> vars;
      std::vector<double> inits;
      std::vector<Index> var_indices;

      for (int entityIdx : entityIndices) {
        auto dof = location_to_dof6(initial_transforms_[entityIdx]);
        auto T0 = std::get<0>(dof);
        auto R0 = std::get<1>(dof);
        inits.insert(inits.end(), T0.begin(), T0.end());
        inits.insert(inits.end(), R0.begin(), R0.end());

        for (int j = 0; j < 6; j++) {
          vars.push_back(x[entityIdx * 6 + j]);
          var_indices.push_back(entityIdx * 6 + j);
        }
      }

      // 计算当前约束的雅可比行
      std::vector<double> constraint_jac(vars.size(), 0.0);
      compute_constraint_jacobian(kind, inits, vars, param, scale_,
                                  constraint_jac);

      // 填充雅可比矩阵
      for (double val : constraint_jac) {
        values[index++] = val;
      }
    }

    return true;
  }
  // 获取最终变换结果
  const std::vector<gp_Trsf> &final_transforms() const {
    return final_transforms_;
  }

  void finalize_solution(SolverReturn status, Index n, const Number *x,
                         const Number *z_L, const Number *z_U, Index m,
                         const Number *g, const Number *lambda,
                         Number obj_value, const IpoptData *ip_data,
                         IpoptCalculatedQuantities *ip_cq) override {
    final_transforms_.clear();
    final_transforms_.reserve(initial_transforms_.size());

    for (size_t i = 0; i < initial_transforms_.size(); ++i) {
      const double *T = &x[i * 6];
      const double *R = &x[i * 6 + 3];

      // 组合初始变换和优化增量
      gp_Trsf delta = build_transform(T, R);
      final_transforms_.push_back(initial_transforms_[i] * delta);
    }
  }

  // 辅助函数：计算约束值
  static double compute_constraint_value(
      ConstraintKind kind, const std::vector<double> &inits,
      const std::vector<double> &vars,
      const boost::variant<boost::blank, double, std::array<double, 3>,
                           std::array<double, 2>> &param,
      double scale) {
    switch (kind) {
    case ConstraintKind::Point: {
      // 点约束：需要2个实体，每个实体有6个变量(3平移+3旋转)
      if (vars.size() != 12 || inits.size() != 12)
        throw std::runtime_error(
            "Invalid number of variables for Point constraint");

      gp_Vec T1_0(inits[0], inits[1], inits[2]);
      gp_Vec R1_0(inits[3], inits[4], inits[5]);
      gp_Vec T1(vars[0], vars[1], vars[2]);
      gp_Vec R1(vars[3], vars[4], vars[5]);

      gp_Vec T2_0(inits[6], inits[7], inits[8]);
      gp_Vec R2_0(inits[9], inits[10], inits[11]);
      gp_Vec T2(vars[6], vars[7], vars[8]);
      gp_Vec R2(vars[9], vars[10], vars[11]);

      double tolerance = 0.0;
      if (param.type() == typeid(double)) {
        tolerance = boost::get<double>(param);
      }

      // 使用虚拟点，因为实际点标记在调用函数中处理
      gp_Pnt p1(0, 0, 0), p2(0, 0, 0);
      return point_cost(p1, p2, T1_0, R1_0, T2_0, R2_0, T1, R1, T2, R2,
                        tolerance, scale);
    }

    case ConstraintKind::Axis: {
      // 轴约束：需要2个实体，每个实体有6个变量
      if (vars.size() != 12 || inits.size() != 12)
        throw std::runtime_error(
            "Invalid number of variables for Axis constraint");

      gp_Vec R1_0(inits[3], inits[4], inits[5]);
      gp_Vec R1(vars[3], vars[4], vars[5]);

      gp_Vec R2_0(inits[9], inits[10], inits[11]);
      gp_Vec R2(vars[9], vars[10], vars[11]);

      double angle = M_PI; // 默认平行
      if (param.type() == typeid(double)) {
        angle = boost::get<double>(param);
      }

      // 使用虚拟方向
      gp_Dir d1(0, 0, 1), d2(0, 0, 1);
      return axis_cost(d1, d2, gp_Vec(), R1_0, gp_Vec(), R2_0, gp_Vec(), R1,
                       gp_Vec(), R2, angle, scale);
    }

    case ConstraintKind::PointInPlane: {
      // 点在平面内约束：需要2个实体
      if (vars.size() != 12 || inits.size() != 12)
        throw std::runtime_error(
            "Invalid number of variables for PointInPlane constraint");

      gp_Vec T1_0(inits[0], inits[1], inits[2]);
      gp_Vec R1_0(inits[3], inits[4], inits[5]);
      gp_Vec T1(vars[0], vars[1], vars[2]);
      gp_Vec R1(vars[3], vars[4], vars[5]);

      gp_Vec T2_0(inits[6], inits[7], inits[8]);
      gp_Vec R2_0(inits[9], inits[10], inits[11]);
      gp_Vec T2(vars[6], vars[7], vars[8]);
      gp_Vec R2(vars[9], vars[10], vars[11]);

      double offset = 0.0;
      if (param.type() == typeid(double)) {
        offset = boost::get<double>(param);
      }

      // 使用虚拟点和平面
      gp_Pnt p(0, 0, 0);
      gp_Pln pln(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
      return point_in_plane_cost(p, pln, T1_0, R1_0, T2_0, R2_0, T1, R1, T2, R2,
                                 offset, scale);
    }

    case ConstraintKind::PointOnLine: {
      // 点在线上约束：需要2个实体
      if (vars.size() != 12 || inits.size() != 12)
        throw std::runtime_error(
            "Invalid number of variables for PointOnLine constraint");

      gp_Vec T1_0(inits[0], inits[1], inits[2]);
      gp_Vec R1_0(inits[3], inits[4], inits[5]);
      gp_Vec T1(vars[0], vars[1], vars[2]);
      gp_Vec R1(vars[3], vars[4], vars[5]);

      gp_Vec T2_0(inits[6], inits[7], inits[8]);
      gp_Vec R2_0(inits[9], inits[10], inits[11]);
      gp_Vec T2(vars[6], vars[7], vars[8]);
      gp_Vec R2(vars[9], vars[10], vars[11]);

      double tolerance = 0.0;
      if (param.type() == typeid(double)) {
        tolerance = boost::get<double>(param);
      }

      // 使用虚拟点和线
      gp_Pnt p(0, 0, 0);
      gp_Lin line(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
      return point_on_line_cost(p, line, T1_0, R1_0, T2_0, R2_0, T1, R1, T2, R2,
                                tolerance, scale);
    }

    case ConstraintKind::FixedPoint: {
      // 固定点约束：需要1个实体
      if (vars.size() != 6 || inits.size() != 6)
        throw std::runtime_error(
            "Invalid number of variables for FixedPoint constraint");

      gp_Vec T1_0(inits[0], inits[1], inits[2]);
      gp_Vec R1_0(inits[3], inits[4], inits[5]);
      gp_Vec T1(vars[0], vars[1], vars[2]);
      gp_Vec R1(vars[3], vars[4], vars[5]);

      gp_Vec target;
      if (param.type() == typeid(std::array<double, 3>)) {
        auto t = boost::get<std::array<double, 3>>(param);
        target = gp_Vec(std::get<0>(t), std::get<1>(t), std::get<2>(t));
      } else {
        throw std::runtime_error(
            "FixedPoint constraint requires target position");
      }

      // 使用虚拟点
      gp_Pnt p(0, 0, 0);
      return fixed_point_cost(p, T1_0, R1_0, T1, R1, target, scale);
    }

    case ConstraintKind::FixedAxis: {
      // 固定轴约束：需要1个实体
      if (vars.size() != 6 || inits.size() != 6)
        throw std::runtime_error(
            "Invalid number of variables for FixedAxis constraint");

      gp_Vec R1_0(inits[3], inits[4], inits[5]);
      gp_Vec R1(vars[3], vars[4], vars[5]);

      gp_Vec target;
      if (param.type() == typeid(std::array<double, 3>)) {
        auto t = boost::get<std::array<double, 3>>(param);
        target = gp_Vec(std::get<0>(t), std::get<1>(t), std::get<2>(t));
      } else {
        throw std::runtime_error(
            "FixedAxis constraint requires target direction");
      }

      // 使用虚拟方向
      gp_Dir d(0, 0, 1);
      return fixed_axis_cost(d, gp_Vec(), R1_0, gp_Vec(), R1, target, scale);
    }

    case ConstraintKind::FixedRotation: {
      // 固定旋转约束：需要1个实体
      if (vars.size() != 6 || inits.size() != 6)
        throw std::runtime_error(
            "Invalid number of variables for FixedRotation constraint");

      gp_Vec R1_0(inits[3], inits[4], inits[5]);
      gp_Vec R1(vars[3], vars[4], vars[5]);

      std::array<double, 3> eulerAngles;
      if (param.type() == typeid(std::array<double, 3>)) {
        eulerAngles = boost::get<std::array<double, 3>>(param);
      } else {
        throw std::runtime_error(
            "FixedRotation constraint requires Euler angles");
      }

      return fixed_rotation_cost(gp_Vec(), R1_0, gp_Vec(), R1, eulerAngles,
                                 scale);
    }

    case ConstraintKind::Plane: {
      // 平面约束：复合约束，需要2个实体
      if (vars.size() != 12 || inits.size() != 12)
        throw std::runtime_error(
            "Invalid number of variables for Plane constraint");

      double angleTol = 0.0, distTol = 0.0;
      if (param.type() == typeid(std::array<double, 2>)) {
        auto p = boost::get<std::array<double, 2>>(param);
        angleTol = std::get<0>(p);
        distTol = std::get<1>(p);
      }

      // 计算轴约束部分
      gp_Vec R1_0(inits[3], inits[4], inits[5]);
      gp_Vec R1(vars[3], vars[4], vars[5]);
      gp_Vec R2_0(inits[9], inits[10], inits[11]);
      gp_Vec R2(vars[9], vars[10], vars[11]);
      gp_Dir d1(0, 0, 1), d2(0, 0, 1);
      double axisCost = axis_cost(d1, d2, gp_Vec(), R1_0, gp_Vec(), R2_0,
                                  gp_Vec(), R1, gp_Vec(), R2, angleTol, scale);

      // 计算点约束部分
      gp_Vec T1_0(inits[0], inits[1], inits[2]);
      gp_Vec T1(vars[0], vars[1], vars[2]);
      gp_Vec T2_0(inits[6], inits[7], inits[8]);
      gp_Vec T2(vars[6], vars[7], vars[8]);
      gp_Pnt p1(0, 0, 0), p2(0, 0, 0);
      double pointCost = point_cost(p1, p2, T1_0, R1_0, T2_0, R2_0, T1, R1, T2,
                                    R2, distTol, scale);

      return axisCost + pointCost;
    }

    case ConstraintKind::Fixed: {
      // 固定约束已在变量边界中处理，这里返回0
      return 0.0;
    }

    default:
      throw std::runtime_error(
          "Unsupported constraint type in compute_constraint_value");
    }
  }

  // 辅助函数：计算约束梯度
  static void compute_constraint_gradient(
      ConstraintKind kind, const std::vector<double> &inits,
      const std::vector<double> &vars,
      const boost::variant<boost::blank, double, std::array<double, 3>,
                           std::array<double, 2>> &param,
      double scale, std::vector<double> &grad) {
    // 实现数值梯度计算 (或解析梯度)
    const double eps = 1e-8;
    std::vector<double> vars_perturbed = vars;

    double base_value =
        compute_constraint_value(kind, inits, vars, param, scale);

    for (size_t i = 0; i < vars.size(); i++) {
      vars_perturbed[i] += eps;
      double perturbed_value =
          compute_constraint_value(kind, inits, vars_perturbed, param, scale);
      grad[i] = (perturbed_value - base_value) / eps;
      vars_perturbed[i] = vars[i];
    }
  }

  // 辅助函数：计算约束雅可比
  static void compute_constraint_jacobian(
      ConstraintKind kind, const std::vector<double> &inits,
      const std::vector<double> &vars,
      const boost::variant<boost::blank, double, std::array<double, 3>,
                           std::array<double, 2>> &param,
      double scale, std::vector<double> &jac) {
    // 对于简单实现可以直接调用梯度计算
    compute_constraint_gradient(kind, inits, vars, param, scale, jac);
  }

private:
  double evaluate_constraint(const Constraint &c, const Number *x) const {
    const auto &markers = std::get<0>(c);
    ConstraintKind kind = std::get<1>(c);
    const auto &param = std::get<2>(c);
    const auto &entityIndices = std::get<3>(c);

    std::vector<const double *> Ts, Rs;
    for (int entityIdx : entityIndices) {
      Ts.push_back(&x[entityIdx * 6]);
      Rs.push_back(&x[entityIdx * 6 + 3]);
    }

    // 辅助函数：从double数组创建gp_Vec
    auto make_vec = [](const double *data) {
      return gp_Vec(data[0], data[1], data[2]);
    };

    // 初始变换设为0（根据实际情况可能需要从initialTransforms_获取）
    gp_Vec zero_vec(0, 0, 0);

    switch (kind) {
    case ConstraintKind::Point: {
      auto p1 = boost::get<gp_Pnt>(markers[0]);
      auto p2 = boost::get<gp_Pnt>(markers[1]);
      double tolerance =
          param.type() == typeid(double) ? boost::get<double>(param) : 0.0;

      return point_cost(p1, p2, zero_vec, zero_vec,       // T1_0, R1_0
                        zero_vec, zero_vec,               // T2_0, R2_0
                        make_vec(Ts[0]), make_vec(Rs[0]), // T1, R1
                        make_vec(Ts[1]), make_vec(Rs[1]), // T2, R2
                        tolerance, scale_);
    }
    case ConstraintKind::Axis: {
      auto d1 = boost::get<gp_Dir>(markers[0]);
      auto d2 = boost::get<gp_Dir>(markers[1]);
      double angle =
          param.type() == typeid(double) ? boost::get<double>(param) : M_PI;

      return axis_cost(d1, d2, zero_vec, zero_vec,       // T1_0, R1_0
                       zero_vec, zero_vec,               // T2_0, R2_0
                       make_vec(Ts[0]), make_vec(Rs[0]), // T1, R1
                       make_vec(Ts[1]), make_vec(Rs[1]), // T2, R2
                       angle, scale_);
    }
    case ConstraintKind::PointInPlane: {
      auto p = boost::get<gp_Pnt>(markers[0]);
      auto plane = boost::get<gp_Pln>(markers[1]);
      double offset =
          param.type() == typeid(double) ? boost::get<double>(param) : 0.0;

      return point_in_plane_cost(p, plane, zero_vec, zero_vec,     // T1_0, R1_0
                                 zero_vec, zero_vec,               // T2_0, R2_0
                                 make_vec(Ts[0]), make_vec(Rs[0]), // T1, R1
                                 make_vec(Ts[1]), make_vec(Rs[1]), // T2, R2
                                 offset, scale_);
    }
    case ConstraintKind::PointOnLine: {
      auto p = boost::get<gp_Pnt>(markers[0]);
      auto line = boost::get<gp_Lin>(markers[1]);
      double tolerance =
          param.type() == typeid(double) ? boost::get<double>(param) : 0.0;

      return point_on_line_cost(p, line, zero_vec, zero_vec,      // T1_0, R1_0
                                zero_vec, zero_vec,               // T2_0, R2_0
                                make_vec(Ts[0]), make_vec(Rs[0]), // T1, R1
                                make_vec(Ts[1]), make_vec(Rs[1]), // T2, R2
                                tolerance, scale_);
    }
    case ConstraintKind::FixedPoint: {
      auto p = boost::get<gp_Pnt>(markers[0]);
      gp_Vec target;
      if (param.type() == typeid(std::array<double, 3>)) {
        auto t = boost::get<std::array<double, 3>>(param);
        target = gp_Vec(std::get<0>(t), std::get<1>(t), std::get<2>(t));
      }

      return fixed_point_cost(p, zero_vec, zero_vec,            // T1_0, R1_0
                              make_vec(Ts[0]), make_vec(Rs[0]), // T1, R1
                              target, scale_);
    }
    case ConstraintKind::FixedAxis: {
      auto d = boost::get<gp_Dir>(markers[0]);
      gp_Vec target;
      if (param.type() == typeid(std::array<double, 3>)) {
        auto t = boost::get<std::array<double, 3>>(param);
        target = gp_Vec(std::get<0>(t), std::get<1>(t), std::get<2>(t));
      }

      return fixed_axis_cost(d, zero_vec, zero_vec,            // T1_0, R1_0
                             make_vec(Ts[0]), make_vec(Rs[0]), // T1, R1
                             target, scale_);
    }
    case ConstraintKind::FixedRotation: {
      std::array<double, 3> eulerAngles{0, 0, 0};
      if (param.type() == typeid(std::array<double, 3>)) {
        eulerAngles = boost::get<std::array<double, 3>>(param);
      }

      return fixed_rotation_cost(zero_vec, zero_vec,               // T1_0, R1_0
                                 make_vec(Ts[0]), make_vec(Rs[0]), // T1, R1
                                 eulerAngles, scale_);
    }
    case ConstraintKind::Plane: {
      auto d1 = boost::get<gp_Dir>(markers[0]);
      auto d2 = boost::get<gp_Dir>(markers[1]);
      auto p1 = boost::get<gp_Pnt>(markers[2]);
      auto p2 = boost::get<gp_Pnt>(markers[3]);

      double angleTol = 0.0, distTol = 0.0;
      if (param.type() == typeid(std::array<double, 2>)) {
        auto p = boost::get<std::array<double, 2>>(param);
        angleTol = std::get<0>(p);
        distTol = std::get<1>(p);
      }

      double axisCost = axis_cost(
          d1, d2, zero_vec, zero_vec, zero_vec, zero_vec, make_vec(Ts[0]),
          make_vec(Rs[0]), make_vec(Ts[1]), make_vec(Rs[1]), angleTol, scale_);

      double pointCost = point_cost(
          p1, p2, zero_vec, zero_vec, zero_vec, zero_vec, make_vec(Ts[0]),
          make_vec(Rs[0]), make_vec(Ts[1]), make_vec(Rs[1]), distTol, scale_);

      return axisCost + pointCost;
    }
    case ConstraintKind::Fixed: {
      return 0.0; // 固定约束已在变量边界处理
    }
    default:
      throw std::runtime_error("Unsupported constraint type");
    }
  }

  // 四元数辅助函数
  static std::pair<double, gp_Vec> quaternion(const gp_Vec &R) {
    double m = R.SquareMagnitude();
    double denominator = 1.0 + m;

    gp_Vec u = R.Multiplied(2.0 / denominator);
    double s = (1.0 - m) / denominator;

    return {s, u};
  }

  // 旋转向量
  static gp_Vec rotate(const gp_Vec &v, const gp_Vec &R) {
    auto su = quaternion(R);
    auto s = std::get<0>(su);
    auto u = std::get<1>(su);

    double uDotV = u.Dot(v);
    double uDotU = u.Dot(u);

    return u.Multiplied(2.0 * uDotV)
        .Added(v.Multiplied(s * s - uDotU))
        .Added(u.Crossed(v).Multiplied(2.0 * s));
  }

  // 变换向量
  static gp_Vec transform(const gp_Vec &v, const gp_Vec &T, const gp_Vec &R) {
    return rotate(v, R).Added(T);
  }

  // 点约束成本
  static double point_cost(const gp_Pnt &m1, const gp_Pnt &m2,
                           const gp_Vec &T1_0, const gp_Vec &R1_0,
                           const gp_Vec &T2_0, const gp_Vec &R2_0,
                           const gp_Vec &T1, const gp_Vec &R1, const gp_Vec &T2,
                           const gp_Vec &R2, double val = 0.0,
                           double scale = 1.0) {
    gp_Vec m1_vec(m1.X(), m1.Y(), m1.Z());
    gp_Vec m2_vec(m2.X(), m2.Y(), m2.Z());

    gp_Vec T1_total = T1_0.Added(T1);
    gp_Vec R1_total = R1_0.Added(R1);
    gp_Vec T2_total = T2_0.Added(T2);
    gp_Vec R2_total = R2_0.Added(R2);

    gp_Vec transformed1 = transform(m1_vec, T1_total, R1_total);
    gp_Vec transformed2 = transform(m2_vec, T2_total, R2_total);
    gp_Vec diff = transformed1.Subtracted(transformed2).Divided(scale);

    double diffSq = diff.SquareMagnitude();

    if (std::abs(val) < 1e-12) {
      return diffSq;
    } else {
      double target = val / scale;
      return std::pow(diffSq - target * target, 2);
    }
  }

  // 轴约束成本
  static double axis_cost(const gp_Dir &m1, const gp_Dir &m2,
                          const gp_Vec &T1_0, const gp_Vec &R1_0,
                          const gp_Vec &T2_0, const gp_Vec &R2_0,
                          const gp_Vec &T1, const gp_Vec &R1, const gp_Vec &T2,
                          const gp_Vec &R2, double val = M_PI,
                          double scale = 1.0) {
    gp_Vec m1_vec(m1.X(), m1.Y(), m1.Z());
    gp_Vec m2_vec(m2.X(), m2.Y(), m2.Z());

    gp_Vec R1_total = R1_0.Added(R1);
    gp_Vec R2_total = R2_0.Added(R2);

    gp_Vec d1 = rotate(m1_vec, R1_total);
    gp_Vec d2 = rotate(m2_vec, R2_total);

    if (std::abs(val) < 1e-12) {
      gp_Vec diff = d1.Subtracted(d2);
      return diff.SquareMagnitude();
    } else if (std::abs(val - M_PI) < 1e-12) {
      gp_Vec sum = d1.Added(d2);
      return sum.SquareMagnitude();
    } else {
      double dot = d1.Dot(d2);
      double diff = dot - std::cos(val);
      return diff * diff;
    }
  }

  // 点在平面内约束成本
  static double point_in_plane_cost(const gp_Pnt &m1, const gp_Pln &m2,
                                    const gp_Vec &T1_0, const gp_Vec &R1_0,
                                    const gp_Vec &T2_0, const gp_Vec &R2_0,
                                    const gp_Vec &T1, const gp_Vec &R1,
                                    const gp_Vec &T2, const gp_Vec &R2,
                                    double val = 0.0, double scale = 1.0) {
    gp_Vec m1_vec(m1.X(), m1.Y(), m1.Z());

    gp_Dir m2_dir = m2.Axis().Direction();
    gp_Pnt m2_pnt =
        m2.Axis().Location().Translated(gp_Vec(m2_dir).Multiplied(val));

    gp_Vec m2_dir_vec(m2_dir.X(), m2_dir.Y(), m2_dir.Z());
    gp_Vec m2_pnt_vec(m2_pnt.X(), m2_pnt.Y(), m2_pnt.Z());

    gp_Vec R2_total = R2_0.Added(R2);
    gp_Vec rotatedDir = rotate(m2_dir_vec, R2_total);

    gp_Vec T1_total = T1_0.Added(T1);
    gp_Vec R1_total = R1_0.Added(R1);
    gp_Vec T2_total = T2_0.Added(T2);

    gp_Vec transformedPoint = transform(m1_vec, T1_total, R1_total);
    gp_Vec transformedPlanePoint = transform(m2_pnt_vec, T2_total, R2_total);

    gp_Vec diff = transformedPlanePoint.Subtracted(transformedPoint);
    double dot = rotatedDir.Dot(diff) / scale;

    return dot * dot;
  }

  // 点在线上约束成本
  static double point_on_line_cost(const gp_Pnt &m1, const gp_Lin &m2,
                                   const gp_Vec &T1_0, const gp_Vec &R1_0,
                                   const gp_Vec &T2_0, const gp_Vec &R2_0,
                                   const gp_Vec &T1, const gp_Vec &R1,
                                   const gp_Vec &T2, const gp_Vec &R2,
                                   double val = 0.0, double scale = 1.0) {
    gp_Vec m1_vec(m1.X(), m1.Y(), m1.Z());

    gp_Dir m2_dir = m2.Direction();
    gp_Pnt m2_pnt = m2.Location();

    gp_Vec m2_dir_vec(m2_dir.X(), m2_dir.Y(), m2_dir.Z());
    gp_Vec m2_pnt_vec(m2_pnt.X(), m2_pnt.Y(), m2_pnt.Z());

    gp_Vec T1_total = T1_0.Added(T1);
    gp_Vec R1_total = R1_0.Added(R1);
    gp_Vec T2_total = T2_0.Added(T2);
    gp_Vec R2_total = R2_0.Added(R2);

    gp_Vec transformedPoint = transform(m1_vec, T1_total, R1_total);
    gp_Vec transformedLinePoint = transform(m2_pnt_vec, T2_total, R2_total);
    gp_Vec rotatedDir = rotate(m2_dir_vec, R2_total);

    gp_Vec d = transformedPoint.Subtracted(transformedLinePoint);
    double dot = rotatedDir.Dot(d);
    gp_Vec projection = rotatedDir.Multiplied(dot);
    gp_Vec perpendicular = d.Subtracted(projection);

    gp_Vec dummy = perpendicular.Divided(scale);
    double dummySq = dummy.SquareMagnitude();

    if (std::abs(val) < 1e-12) {
      return dummySq;
    } else {
      return std::pow(dummySq - val, 2);
    }
  }

  // 固定点约束成本
  static double fixed_point_cost(const gp_Pnt &m1, const gp_Vec &T1_0,
                                 const gp_Vec &R1_0, const gp_Vec &T1,
                                 const gp_Vec &R1, const gp_Vec &target,
                                 double scale = 1.0) {
    gp_Vec m1_vec(m1.X(), m1.Y(), m1.Z());
    gp_Vec T1_total = T1_0.Added(T1);
    gp_Vec R1_total = R1_0.Added(R1);

    gp_Vec transformed = transform(m1_vec, T1_total, R1_total);
    gp_Vec diff = transformed.Subtracted(target).Divided(scale);

    return diff.SquareMagnitude();
  }

  // 固定轴约束成本
  static double fixed_axis_cost(const gp_Dir &m1, const gp_Vec &T1_0,
                                const gp_Vec &R1_0, const gp_Vec &T1,
                                const gp_Vec &R1, const gp_Vec &target,
                                double scale = 1.0) {
    gp_Vec m1_vec(m1.X(), m1.Y(), m1.Z());
    gp_Vec R1_total = R1_0.Added(R1);

    gp_Vec rotated = rotate(m1_vec, R1_total);
    gp_Vec normalizedTarget = target.Normalized();
    gp_Vec diff = rotated.Subtracted(normalizedTarget);

    return diff.SquareMagnitude();
  }

  // 固定旋转约束成本
  static double fixed_rotation_cost(const gp_Vec &T1_0, const gp_Vec &R1_0,
                                    const gp_Vec &T1, const gp_Vec &R1,
                                    const std::array<double, 3> &eulerAngles,
                                    double scale = 1.0) {
    gp_Quaternion q;
    q.SetEulerAngles(gp_Extrinsic_XYZ, std::get<0>(eulerAngles),
                     std::get<1>(eulerAngles), std::get<2>(eulerAngles));

    gp_Vec R_total = R1_0.Added(R1);
    auto su = quaternion(R_total);
    auto s = std::get<0>(su);
    auto u = std::get<1>(su);

    double q_dot = q.W() * s + q.X() * u.X() + q.Y() * u.Y() + q.Z() * u.Z();
    double dummy = 1.0 - q_dot * q_dot;

    return dummy;
  }
};

constraint_solver::constraint_solver(const std::vector<gp_Trsf> &entities,
                                     const std::vector<Constraint> &constraints,
                                     const std::vector<size_t> &locked,
                                     double scale)
    : scale_(scale), locked_(locked), constraints_(constraints) {

  ne_ = entities.size();
  nc_ = constraints.size();
  initial_transforms_ = entities;

  // Initialize variables and starting points
  for (size_t i = 0; i < entities.size(); ++i) {
    auto dof = location_to_dof6(entities[i]);
    auto T0 = std::get<0>(dof);
    auto R0 = std::get<1>(dof);
    std::array<double, 3> T{3, 0.0}, R{3, 0.0};
    std::array<double, 3> T_init = T0;
    std::array<double, 3> R_init = R0;

    if (std::find(locked.begin(), locked.end(), i) != locked.end()) {
      // Locked entities get zero variables
      T = {0.0, 0.0, 0.0};
      R = {0.0, 0.0, 0.0};
    } else {
      // Small initial rotation for free entities
      R = {1e-2, 1e-2, 1e-2};
    }

    variables_.emplace_back(T, R);
    start_points_.emplace_back(T_init, R_init);
  }
}

std::pair<std::vector<gp_Trsf>, std::map<std::string, double>>
constraint_solver::solve(int verbosity) {
  // Create Ipopt problem and solver
  Ipopt::SmartPtr<Ipopt::IpoptApplication> app = IpoptApplicationFactory();

  // Set Ipopt options
  app->Options()->SetNumericValue("tol", 1e-14);
  app->Options()->SetNumericValue("acceptable_obj_change_tol", 1e-12);
  app->Options()->SetIntegerValue("acceptable_iter", 1);
  app->Options()->SetStringValue("hessian_approximation", "exact");
  app->Options()->SetStringValue("nlp_scaling_method", "none");
  app->Options()->SetStringValue("honor_original_bounds", "yes");
  app->Options()->SetNumericValue("bound_relax_factor", 0);
  app->Options()->SetIntegerValue("print_level", verbosity);
  app->Options()->SetStringValue("sb", verbosity == 0 ? "yes" : "no");
  app->Options()->SetStringValue("print_timing_statistics", "no");
  app->Options()->SetStringValue("linear_solver", "mumps");

  // Create and solve the NLP
  Ipopt::SmartPtr<constraint_problem> nlp = new constraint_problem(*this);
  app->Initialize();
  Ipopt::ApplicationReturnStatus status = app->OptimizeTNLP(nlp);

  // Process results
  std::vector<gp_Trsf> trans;
  std::map<std::string, double> stats;

  if (status == Ipopt::Solve_Succeeded ||
      status == Ipopt::Solved_To_Acceptable_Level) {
    trans = nlp->final_transforms();
    // Collect statistics
    stats["iter_count"] = app->Statistics()->IterationCount();
    stats["solve_time"] = app->Statistics()->TotalWallclockTime();
    stats["final_obj"] = app->Statistics()->FinalObjective();
  } else {
    throw std::runtime_error("Ipopt failed to solve the problem");
  }

  return std::make_pair(trans, stats);
}

} // namespace topo
} // namespace flywave
