#include "solver.hh"

#include <nlopt.hpp>

#include <boost/variant.hpp>
#include <gp_Dir.hxx>
#include <gp_Lin.hxx>
#include <gp_Pln.hxx>
#include <gp_Pnt.hxx>
#include <gp_Quaternion.hxx>
#include <gp_Trsf.hxx>
#include <cmath>
#include <chrono>
#include <memory>
#include <set>
#include <stdexcept>
#include <vector>

namespace flywave {
namespace topo {
namespace {

DOF6 location_to_dof6(const gp_Trsf &loc) {
  gp_Vec v = loc.TranslationPart();
  gp_Quaternion q = loc.GetRotation();

  double w = q.W();
  double alpha_2, a, b, c;

  if (std::abs(w + 1.0) < 1e-12) {
    double norm = std::sqrt(q.X() * q.X() + q.Y() * q.Y() + q.Z() * q.Z());
    if (norm < 1e-12) {
      a = b = c = 0.0;
    } else {
      a = q.X() / norm * 1e6;
      b = q.Y() / norm * 1e6;
      c = q.Z() / norm * 1e6;
    }
  } else {
    alpha_2 = (1 - w) / (1 + w);
    a = (alpha_2 + 1) * q.X() / 2;
    b = (alpha_2 + 1) * q.Y() / 2;
    c = (alpha_2 + 1) * q.Z() / 2;
  }

  std::array<double, 3> T{v.X(), v.Y(), v.Z()};
  std::array<double, 3> R{a, b, c};

  return {T, R};
}
} // namespace

class constraint_problem {
private:
  constraint_solver &solver_;
  std::vector<gp_Trsf> initial_transforms_;
  std::vector<assembly_constraint> constraints_;
  std::vector<size_t> lockedEntities_;
  double scale_;
  size_t ne_;
  std::vector<gp_Trsf> final_transforms_;
  std::set<size_t> lockedSet_;

public:
  bool is_locked(size_t entityIdx) const {
    return lockedSet_.count(entityIdx) > 0;
  }

  constraint_problem(constraint_solver &solver)
      : solver_(solver), initial_transforms_(solver.initial_transforms_),
        constraints_(solver.constraints_), lockedEntities_(solver.locked_),
        scale_(solver.scale_), ne_(solver.ne_) {
    lockedSet_.insert(lockedEntities_.begin(), lockedEntities_.end());
  }

  static void transform_to_variables(const gp_Trsf &trsf, double *T,
                                     double *R) {
    gp_Vec translation = trsf.TranslationPart();
    gp_Quaternion quat = trsf.GetRotation();

    T[0] = translation.X();
    T[1] = translation.Y();
    T[2] = translation.Z();

    double w = quat.W();
    if (std::abs(w + 1.0) < 1e-12) {
      double norm = std::sqrt(quat.X() * quat.X() + quat.Y() * quat.Y() +
                              quat.Z() * quat.Z());
      if (norm < 1e-12) {
        R[0] = R[1] = R[2] = 0.0;
      } else {
        R[0] = quat.X() / norm * 1e6;
        R[1] = quat.Y() / norm * 1e6;
        R[2] = quat.Z() / norm * 1e6;
      }
    } else {
      double alpha_2 = (1 - w) / (1 + w);
      R[0] = (alpha_2 + 1) * quat.X() / 2;
      R[1] = (alpha_2 + 1) * quat.Y() / 2;
      R[2] = (alpha_2 + 1) * quat.Z() / 2;
    }
  }

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

  size_t num_entities() const { return ne_; }
  size_t num_constraints() const { return constraints_.size(); }

  void set_final_transforms(const std::vector<double> &x) {
    final_transforms_.clear();
    final_transforms_.reserve(initial_transforms_.size());

    for (size_t i = 0; i < initial_transforms_.size(); ++i) {
      const double *T = &x[i * 6];
      const double *R = &x[i * 6 + 3];

      gp_Trsf delta = build_transform(T, R);
      final_transforms_.push_back(initial_transforms_[i] * delta);
    }
  }

  const std::vector<gp_Trsf> &final_transforms() const {
    return final_transforms_;
  }

  static double compute_constraint_value(
      constraint_kind kind, const std::vector<double> &inits,
      const std::vector<double> &vars,
      const boost::variant<boost::blank, double, std::array<double, 3>,
                           std::array<double, 2>> &param,
      double scale) {
    switch (kind) {
    case constraint_kind::Point: {
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

      gp_Pnt p1(0, 0, 0), p2(0, 0, 0);
      return point_cost(p1, p2, T1_0, R1_0, T2_0, R2_0, T1, R1, T2, R2,
                        tolerance, scale);
    }

    case constraint_kind::Axis: {
      if (vars.size() != 12 || inits.size() != 12)
        throw std::runtime_error(
            "Invalid number of variables for Axis constraint");

      gp_Vec R1_0(inits[3], inits[4], inits[5]);
      gp_Vec R1(vars[3], vars[4], vars[5]);

      gp_Vec R2_0(inits[9], inits[10], inits[11]);
      gp_Vec R2(vars[9], vars[10], vars[11]);

      double angle = M_PI;
      if (param.type() == typeid(double)) {
        angle = boost::get<double>(param);
      }

      gp_Dir d1(0, 0, 1), d2(0, 0, 1);
      return axis_cost(d1, d2, gp_Vec(), R1_0, gp_Vec(), R2_0, gp_Vec(), R1,
                       gp_Vec(), R2, angle, scale);
    }

    case constraint_kind::PointInPlane: {
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

      gp_Pnt p(0, 0, 0);
      gp_Pln pln(gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
      return point_in_plane_cost(p, pln, T1_0, R1_0, T2_0, R2_0, T1, R1, T2,
                                 R2, offset, scale);
    }

    case constraint_kind::PointOnLine: {
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

      gp_Pnt p(0, 0, 0);
      gp_Lin line(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
      return point_on_line_cost(p, line, T1_0, R1_0, T2_0, R2_0, T1, R1, T2,
                                R2, tolerance, scale);
    }

    case constraint_kind::FixedPoint: {
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

      gp_Pnt p(0, 0, 0);
      return fixed_point_cost(p, T1_0, R1_0, T1, R1, target, scale);
    }

    case constraint_kind::FixedAxis: {
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

      gp_Dir d(0, 0, 1);
      return fixed_axis_cost(d, gp_Vec(), R1_0, gp_Vec(), R1, target, scale);
    }

    case constraint_kind::FixedRotation: {
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

    case constraint_kind::Plane: {
      if (vars.size() != 12 || inits.size() != 12)
        throw std::runtime_error(
            "Invalid number of variables for Plane constraint");

      double angleTol = 0.0, distTol = 0.0;
      if (param.type() == typeid(std::array<double, 2>)) {
        auto p = boost::get<std::array<double, 2>>(param);
        angleTol = std::get<0>(p);
        distTol = std::get<1>(p);
      }

      gp_Vec R1_0(inits[3], inits[4], inits[5]);
      gp_Vec R1(vars[3], vars[4], vars[5]);
      gp_Vec R2_0(inits[9], inits[10], inits[11]);
      gp_Vec R2(vars[9], vars[10], vars[11]);
      gp_Dir d1(0, 0, 1), d2(0, 0, 1);
      double axisCost = axis_cost(d1, d2, gp_Vec(), R1_0, gp_Vec(), R2_0,
                                  gp_Vec(), R1, gp_Vec(), R2, angleTol, scale);

      gp_Vec T1_0(inits[0], inits[1], inits[2]);
      gp_Vec T1(vars[0], vars[1], vars[2]);
      gp_Vec T2_0(inits[6], inits[7], inits[8]);
      gp_Vec T2(vars[6], vars[7], vars[8]);
      gp_Pnt p1(0, 0, 0), p2(0, 0, 0);
      double pointCost = point_cost(p1, p2, T1_0, R1_0, T2_0, R2_0, T1, R1,
                                    T2, R2, distTol, scale);

      return axisCost + pointCost;
    }

    case constraint_kind::Fixed: {
      return 0.0;
    }

    default:
      throw std::runtime_error(
          "Unsupported constraint type in compute_constraint_value");
    }
  }

  static void compute_constraint_gradient(
      constraint_kind kind, const std::vector<double> &inits,
      const std::vector<double> &vars,
      const boost::variant<boost::blank, double, std::array<double, 3>,
                           std::array<double, 2>> &param,
      double scale, std::vector<double> &grad) {
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

  static void compute_constraint_jacobian(
      constraint_kind kind, const std::vector<double> &inits,
      const std::vector<double> &vars,
      const boost::variant<boost::blank, double, std::array<double, 3>,
                           std::array<double, 2>> &param,
      double scale, std::vector<double> &jac) {
    compute_constraint_gradient(kind, inits, vars, param, scale, jac);
  }

  // --- NLopt callbacks ---

  static double nlopt_objective(const std::vector<double> &x,
                                std::vector<double> &grad, void *data) {
    auto *self = static_cast<constraint_problem *>(data);
    double obj = 0.0;

    try {
      // Sum of constraint values
      for (const auto &constraint : self->constraints_) {
        const auto &entityIndices = std::get<3>(constraint);
        constraint_kind kind = std::get<1>(constraint);
        const auto &param = std::get<2>(constraint);

        // Skip marker-only constraints (e.g. Fixed) with no entity indices
        if (entityIndices.empty())
          continue;

        std::vector<double> vars;
        std::vector<double> inits;

        for (int entityIdx : entityIndices) {
          auto dof = location_to_dof6(self->initial_transforms_[entityIdx]);
          auto T0 = std::get<0>(dof);
          auto R0 = std::get<1>(dof);
          inits.insert(inits.end(), T0.begin(), T0.end());
          inits.insert(inits.end(), R0.begin(), R0.end());

          for (int i = 0; i < 6; i++) {
            vars.push_back(x[entityIdx * 6 + i]);
          }
        }

        obj += compute_constraint_value(kind, inits, vars, param,
                                        self->scale_);
      }

      // Tikhonov regularization
      for (size_t i = 0; i < x.size(); i++) {
        if (!self->is_locked(i / 6)) {
          obj += 1e-16 * x[i] * x[i];
        }
      }

      // Gradient
      if (!grad.empty()) {
        std::fill(grad.begin(), grad.end(), 0.0);

        for (const auto &constraint : self->constraints_) {
          constraint_kind kind = std::get<1>(constraint);
          const auto &param = std::get<2>(constraint);
          const auto &entityIndices = std::get<3>(constraint);

          if (entityIndices.empty())
            continue;

          std::vector<double> vars;
          std::vector<double> inits;
          std::vector<size_t> var_indices;

          for (int entityIdx : entityIndices) {
            auto dof = location_to_dof6(self->initial_transforms_[entityIdx]);
            auto T0 = std::get<0>(dof);
            auto R0 = std::get<1>(dof);

            inits.insert(inits.end(), T0.begin(), T0.end());
            inits.insert(inits.end(), R0.begin(), R0.end());

            for (int i = 0; i < 6; i++) {
              vars.push_back(x[entityIdx * 6 + i]);
              var_indices.push_back(entityIdx * 6 + i);
            }
          }

          std::vector<double> constraint_grad(vars.size(), 0.0);
          compute_constraint_gradient(kind, inits, vars, param, self->scale_,
                                      constraint_grad);

          for (size_t i = 0; i < var_indices.size(); i++) {
            grad[var_indices[i]] += constraint_grad[i];
          }
        }

        for (size_t i = 0; i < x.size(); i++) {
          if (!self->is_locked(i / 6)) {
            grad[i] += 2.0 * 1e-16 * x[i];
          }
        }
      }
    } catch (const std::exception &e) {
      return 1e20;
    } catch (...) {
      return 1e20;
    }

    return obj;
  }

  // NLopt mfunc callback (C-style signature with gradient pointer)
  // IMPORTANT: must evaluate at the CURRENT iterate x, not at initial_transforms_,
  // otherwise the Jacobian is constant and SLSQP may converge prematurely.
  static void nlopt_constraint(unsigned m, double *result, unsigned n,
                                const double *x,
                                double * /*gradient — not needed*/,
                                void *data) {
    auto *self = static_cast<constraint_problem *>(data);

    for (unsigned i = 0; i < m; i++) {
      const auto &entityIndices = std::get<3>(self->constraints_[i]);
      constraint_kind kind = std::get<1>(self->constraints_[i]);
      const auto &param = std::get<2>(self->constraints_[i]);

      // Marker-only constraints are always satisfied (return 0)
      if (entityIndices.empty()) {
        result[i] = 0.0;
        continue;
      }

      std::vector<double> vars;
      std::vector<double> inits;

      for (int entityIdx : entityIndices) {
        // Read initial transform for reference
        auto dof = location_to_dof6(self->initial_transforms_[entityIdx]);
        auto T0 = std::get<0>(dof);
        auto R0 = std::get<1>(dof);
        inits.insert(inits.end(), T0.begin(), T0.end());
        inits.insert(inits.end(), R0.begin(), R0.end());

        // Read CURRENT iterate from x
        for (int j = 0; j < 6; j++) {
          vars.push_back(x[entityIdx * 6 + j]);
        }
      }

      result[i] =
          compute_constraint_value(kind, inits, vars, param, self->scale_);
    }
  }

  // --- Geometry helpers (unchanged) ---

  static gp_Trsf build_transform(const double *T, const double *R) {
    gp_Trsf transform;
    double a = R[0], b = R[1], c = R[2];
    double m = a * a + b * b + c * c;

    transform.SetRotation(gp_Quaternion(2 * a / (m + 1), 2 * b / (m + 1),
                                        2 * c / (m + 1), (1 - m) / (m + 1)));
    transform.SetTranslationPart(gp_Vec(T[0], T[1], T[2]));
    return transform;
  }

  static std::pair<double, gp_Vec> quaternion(const gp_Vec &R) {
    double m = R.SquareMagnitude();
    double denominator = 1.0 + m;

    gp_Vec u = R.Multiplied(2.0 / denominator);
    double s = (1.0 - m) / denominator;

    return {s, u};
  }

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

  static gp_Vec transform(const gp_Vec &v, const gp_Vec &T, const gp_Vec &R) {
    return rotate(v, R).Added(T);
  }

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

constraint_solver::constraint_solver(
    const std::vector<gp_Trsf> &entities,
    const std::vector<assembly_constraint> &constraints,
    const std::vector<size_t> &locked, double scale)
    : scale_(scale), locked_(locked), constraints_(constraints) {

  ne_ = entities.size();
  nc_ = constraints.size();
  initial_transforms_ = entities;
}

std::pair<std::vector<gp_Trsf>, std::map<std::string, double>>
constraint_solver::solve(int verbosity) {
  size_t n = ne_ * 6;
  size_t m = constraints_.size();

  constraint_problem problem(*this);

  if (n == 0) {
    throw std::runtime_error("No entities to solve");
  }

  auto start_time = std::chrono::high_resolution_clock::now();

  try {
    nlopt::opt opt(nlopt::LD_SLSQP, static_cast<unsigned>(n));

    opt.set_min_objective(constraint_problem::nlopt_objective, &problem);

    // Variable bounds
    std::vector<double> lb(n, -1e20);
    std::vector<double> ub(n, 1e20);

    for (size_t i = 0; i < ne_; i++) {
      if (problem.is_locked(i)) {
        lb[i * 6] = ub[i * 6] = 0;
        lb[i * 6 + 1] = ub[i * 6 + 1] = 0;
        lb[i * 6 + 2] = ub[i * 6 + 2] = 0;
        lb[i * 6 + 3] = ub[i * 6 + 3] = 0;
        lb[i * 6 + 4] = ub[i * 6 + 4] = 0;
        lb[i * 6 + 5] = ub[i * 6 + 5] = 0;
      }
    }

    opt.set_lower_bounds(lb);
    opt.set_upper_bounds(ub);

    // Tolerances — no equality constraints; the objective already encodes
    // all constraint violations as penalties, so SLSQP minimizes them freely.
    opt.set_xtol_rel(1e-12);
    opt.set_ftol_rel(0.0);
    opt.set_ftol_abs(0.0);
    opt.set_maxeval(500);

    // Starting point
    std::vector<double> x(n, 0.0);

    // Optimize
    double minf = 0.0;
    nlopt::result result = nlopt::FAILURE;
    try {
      result = opt.optimize(x, minf);
    } catch (const nlopt::roundoff_limited &) {
      // 部分结果可用 (NLopt 文档建议), 继续使用当前 x
    } catch (const nlopt::forced_stop &) {
      // 同上
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    double solve_time =
        std::chrono::duration<double>(end_time - start_time).count();

    // Build final transforms from solution
    problem.set_final_transforms(x);

    std::map<std::string, double> stats;
    stats["iter_count"] = static_cast<double>(opt.get_numevals());
    stats["solve_time"] = solve_time;
    stats["final_obj"] = minf;

    return std::make_pair(problem.final_transforms(), stats);

  } catch (const std::exception &e) {
    throw std::runtime_error(
        std::string("NLopt solver error: ") + e.what());
  }
}

} // namespace topo
} // namespace flywave
