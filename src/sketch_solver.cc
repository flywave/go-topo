#include "sketch_solver.hh"

namespace flywave {
namespace topo {

// Helper functions implementation
gp_Pnt2d sketch_solver::arc_first(const ArcDOF &x) {
  return gp_Pnt2d(x.data[0] + x.data[2] * std::sin(x.data[3]),
                  x.data[1] + x.data[2] * std::cos(x.data[3]));
}

gp_Pnt2d sketch_solver::arc_last(const ArcDOF &x) {
  return gp_Pnt2d(x.data[0] + x.data[2] * std::sin(x.data[3] + x.data[4]),
                  x.data[1] + x.data[2] * std::cos(x.data[3] + x.data[4]));
}

gp_Pnt2d sketch_solver::arc_point(const ArcDOF &x,
                                  const boost::optional<double> &val) {
  if (!val) {
    return gp_Pnt2d(x.data[0], x.data[1]);
  }
  double a = x.data[3] + *val * x.data[4];
  return gp_Pnt2d(x.data[0] + x.data[2] * std::sin(a),
                  x.data[1] + x.data[2] * std::cos(a));
}

gp_Pnt2d sketch_solver::line_point(const SegmentDOF &x,
                                   const boost::optional<double> &val) {
  if (!val) {
    return gp_Pnt2d(x.data[0], x.data[1]);
  }
  double t = *val;
  return gp_Pnt2d(x.data[0] + t * (x.data[2] - x.data[0]),
                  x.data[1] + t * (x.data[3] - x.data[1]));
}

gp_Vec2d sketch_solver::arc_first_tangent(const ArcDOF &x) {
  double sign_da = x.data[4] > 0 ? 1.0 : -1.0;
  return gp_Vec2d(sign_da * std::cos(x.data[3]),
                  -sign_da * std::sin(x.data[3]));
}

gp_Vec2d sketch_solver::arc_last_tangent(const ArcDOF &x) {
  double sign_da = x.data[4] > 0 ? 1.0 : -1.0;
  return gp_Vec2d(sign_da * std::cos(x.data[3] + x.data[4]),
                  -sign_da * std::sin(x.data[3] + x.data[4]));
}

// Cost functions implementation
double sketch_solver::fixed_cost(const std::vector<double> &x,
                                 const std::vector<double> &x0) {
  double sum = 0.0;
  for (size_t i = 0; i < x.size(); ++i) {
    double diff = x[i] - x0[i];
    sum += diff * diff;
  }
  return std::sqrt(sum);
}

double sketch_solver::fixed_point_cost(const std::vector<double> &x, GeomType t,
                                       const std::vector<double> &x0,
                                       const boost::optional<double> &val) {
  gp_Pnt2d p, p0;

  if (t == GeomType::LINE) {
    SegmentDOF seg{{x[0], x[1], x[2], x[3]}};
    SegmentDOF seg0{{x0[0], x0[1], x0[2], x0[3]}};
    p = line_point(seg, val);
    p0 = line_point(seg0, val);
  } else if (t == GeomType::CIRCLE) {
    ArcDOF arc{{x[0], x[1], x[2], x[3], x[4]}};
    ArcDOF arc0{{x0[0], x0[1], x0[2], x0[3], x0[4]}};
    p = arc_point(arc, val);
    p0 = arc_point(arc0, val);
  } else {
    throw std::invalid_argument("Invalid geometry type");
  }

  return p.Distance(p0);
}

// NLopt objective function implementation
double sketch_solver::objective_function(const std::vector<double> &x,
                                         std::vector<double> &grad,
                                         void *f_data) {
  sketch_solver *solver = static_cast<sketch_solver *>(f_data);
  return solver->compute_cost(x, grad);
}

double sketch_solver::compute_cost(const std::vector<double> &x,
                                   std::vector<double> &grad) {
  double cost = 0.0;

  if (!grad.empty()) {
    std::fill(grad.begin(), grad.end(), 0.0);
  }

  for (const auto &constraint : constraints) {
    auto entities = constraint.entities;
    auto kind = constraint.kind;
    size_t e1 = entities.first;
    boost::optional<size_t> e2 = entities.second;

    // Extract current and initial values
    std::vector<double> x1(x.begin() + ixs[e1], x.begin() + ixs[e1 + 1]);
    std::vector<double> x10(x0.begin() + ixs[e1], x0.begin() + ixs[e1 + 1]);

    std::vector<double> x2, x20;
    if (e2) {
      x2 = std::vector<double>(x.begin() + ixs[*e2], x.begin() + ixs[*e2 + 1]);
      x20 =
          std::vector<double>(x0.begin() + ixs[*e2], x0.begin() + ixs[*e2 + 1]);
    }

    // Calculate current constraint cost
    double constraint_cost = 0.0;

    try {
      switch (kind) {
      case sketch_constraint_kind::FIXED:
        constraint_cost = fixed_cost(x1, x10);
        break;
      case sketch_constraint_kind::FIXED_POINT: {
        if (auto val = boost::get<double>(&constraint.value)) {
          constraint_cost = fixed_point_cost(x1, geoms[e1], x10, *val);
        }
        break;
      }
      case sketch_constraint_kind::COINCIDENT:
        if (e2) {
          constraint_cost =
              coincident_cost(x1, geoms[e1], x10, x2, geoms[*e2], x20);
        }
        break;
      case sketch_constraint_kind::ANGLE: {
        if (auto val = boost::get<double>(&constraint.value)) {
          constraint_cost =
              angle_cost(x1, geoms[e1], x10, x2, geoms[*e2], x20, *val);
        }
        break;
      }
      case sketch_constraint_kind::LENGTH: {
        if (auto val = boost::get<double>(&constraint.value)) {
          constraint_cost = length_cost(x1, geoms[e1], x10, *val);
        }
        break;
      }
      case sketch_constraint_kind::DISTANCE: {
        if (auto vals = boost::get<std::tuple<boost::optional<double>,
                                              boost::optional<double>, double>>(
                &constraint.value)) {
          constraint_cost = distance_cost(
              x1, geoms[e1], x10, x2, geoms[*e2], x20, std::get<0>(*vals),
              std::get<1>(*vals), std::get<2>(*vals));
        }
        break;
      }
      case sketch_constraint_kind::RADIUS: {
        if (auto val = boost::get<double>(&constraint.value)) {
          constraint_cost = radius_cost(x1, geoms[e1], x10, *val);
        }
        break;
      }
      case sketch_constraint_kind::ORIENTATION: {
        if (auto val =
                boost::get<std::pair<double, double>>(&constraint.value)) {
          constraint_cost = orientation_cost(x1, geoms[e1], x10, *val);
        }
        break;
      }
      case sketch_constraint_kind::ARC_ANGLE: {
        if (auto val = boost::get<double>(&constraint.value)) {
          constraint_cost = arc_angle_cost(x1, geoms[e1], x10, *val);
        }
        break;
      }
      default:
        throw std::invalid_argument("Unknown constraint type");
      }
    } catch (const boost::bad_get &e) {
      std::cerr << "Bad get in constraint: " << e.what() << std::endl;
      continue;
    }

    cost += constraint_cost * constraint_cost;

    // Compute gradient if needed
    if (!grad.empty()) {
      // Numerical gradient computation
      std::vector<double> x_perturbed = x;
      double original_cost = constraint_cost;

      // Gradient for first entity
      for (size_t j = ixs[e1]; j < ixs[e1 + 1]; ++j) {
        x_perturbed[j] += DIFF_EPS;

        // Recompute cost with perturbed x1
        std::vector<double> x1_perturbed(x_perturbed.begin() + ixs[e1],
                                         x_perturbed.begin() + ixs[e1 + 1]);
        double perturbed_cost = 0.0;

        // Rebuild arguments for each constraint type
        switch (kind) {
        case sketch_constraint_kind::FIXED:
          perturbed_cost = fixed_cost(x1_perturbed, x10);
          break;
        case sketch_constraint_kind::FIXED_POINT: {
          if (auto val = boost::get<double>(&constraint.value)) {
            perturbed_cost =
                fixed_point_cost(x1_perturbed, geoms[e1], x10, *val);
          }
          break;
        }
        case sketch_constraint_kind::COINCIDENT:
          perturbed_cost = coincident_cost(x1_perturbed, geoms[e1], x10, x2,
                                           geoms[*e2], x20);
          break;
        case sketch_constraint_kind::ANGLE: {
          double val = boost::get<double>(constraint.value);
          perturbed_cost = angle_cost(x1_perturbed, geoms[e1], x10, x2,
                                      geoms[*e2], x20, val);
          break;
        }
        case sketch_constraint_kind::LENGTH: {
          double val = boost::get<double>(constraint.value);
          perturbed_cost = length_cost(x1_perturbed, geoms[e1], x10, val);
          break;
        }
        case sketch_constraint_kind::DISTANCE: {
          auto vals = boost::get<std::tuple<boost::optional<double>,
                                            boost::optional<double>, double>>(
              constraint.value);
          perturbed_cost = distance_cost(x1_perturbed, geoms[e1], x10, x2,
                                         geoms[*e2], x20, std::get<0>(vals),
                                         std::get<1>(vals), std::get<2>(vals));
          break;
        }
        case sketch_constraint_kind::RADIUS: {
          double val = boost::get<double>(constraint.value);
          perturbed_cost = radius_cost(x1_perturbed, geoms[e1], x10, val);
          break;
        }
        case sketch_constraint_kind::ORIENTATION: {
          auto val = boost::get<std::pair<double, double>>(constraint.value);
          perturbed_cost = orientation_cost(x1_perturbed, geoms[e1], x10, val);
          break;
        }
        case sketch_constraint_kind::ARC_ANGLE: {
          double val = boost::get<double>(constraint.value);
          perturbed_cost = arc_angle_cost(x1_perturbed, geoms[e1], x10, val);
          break;
        }
        default:
          break;
        }

        grad[j] +=
            2 * original_cost * (perturbed_cost - original_cost) / DIFF_EPS;
        x_perturbed[j] = x[j]; // Reset the perturbation
      }

      // Gradient for second entity if present
      if (e2) {
        for (size_t j = ixs[*e2]; j < ixs[*e2 + 1]; ++j) {
          x_perturbed[j] += DIFF_EPS;

          // Recompute cost with perturbed x2
          std::vector<double> x2_perturbed(x_perturbed.begin() + ixs[*e2],
                                           x_perturbed.begin() + ixs[*e2 + 1]);
          double perturbed_cost = 0.0;

          switch (kind) {
          case sketch_constraint_kind::COINCIDENT:
            perturbed_cost = coincident_cost(x1, geoms[e1], x10, x2_perturbed,
                                             geoms[*e2], x20);
            break;
          case sketch_constraint_kind::ANGLE: {
            double val = boost::get<double>(constraint.value);
            perturbed_cost = angle_cost(x1, geoms[e1], x10, x2_perturbed,
                                        geoms[*e2], x20, val);
            break;
          }
          case sketch_constraint_kind::DISTANCE: {
            auto vals = boost::get<std::tuple<boost::optional<double>,
                                              boost::optional<double>, double>>(
                constraint.value);
            perturbed_cost = distance_cost(
                x1, geoms[e1], x10, x2_perturbed, geoms[*e2], x20,
                std::get<0>(vals), std::get<1>(vals), std::get<2>(vals));
            break;
          }
          default:
            break;
          }

          grad[j] +=
              2 * original_cost * (perturbed_cost - original_cost) / DIFF_EPS;
          x_perturbed[j] = x[j]; // Reset the perturbation
        }
      }
    }
  }

  return cost;
}

// Constructor implementation
sketch_solver::sketch_solver(const std::vector<DOF> &entities,
                             const std::vector<sketch_constraint> &constraints,
                             const std::vector<GeomType> &geoms)
    : entities(entities), constraints(constraints), geoms(geoms) {

  // Initialize index offsets
  ixs.push_back(0);
  for (const auto &e : entities) {
    size_t size = 0;
    if (e.type() == typeid(SegmentDOF)) {
      size = 4;
    } else if (e.type() == typeid(ArcDOF)) {
      size = 5;
    }
    ixs.push_back(ixs.back() + size);
  }

  // Flatten initial solution
  x0.reserve(ixs.back());
  for (const auto &e : entities) {
    if (e.type() == typeid(SegmentDOF)) {
      const SegmentDOF &seg = boost::get<SegmentDOF>(e);
      x0.insert(x0.end(), seg.data.begin(), seg.data.end());
    } else if (e.type() == typeid(ArcDOF)) {
      const ArcDOF &arc = boost::get<ArcDOF>(e);
      x0.insert(x0.end(), arc.data.begin(), arc.data.end());
    }
  }
}

// Solve method implementation
std::pair<std::vector<std::vector<double>>,
          std::map<std::string, boost::variant<double, int, std::string>>>
sketch_solver::solve() {
  nlopt::opt opt(nlopt::LD_SLSQP, static_cast<int>(x0.size()));

  // Set objective function
  opt.set_min_objective(objective_function, this);

  // Set bounds
  std::vector<double> lb(x0.size(), -std::numeric_limits<double>::infinity());
  std::vector<double> ub(x0.size(), std::numeric_limits<double>::infinity());

  // Set radius lower bound to 0 for circles
  for (size_t i = 0; i < geoms.size(); ++i) {
    if (geoms[i] == GeomType::CIRCLE) {
      lb[ixs[i] + 2] = 0.0;
    }
  }

  opt.set_lower_bounds(lb);
  opt.set_upper_bounds(ub);

  // Set optimization parameters
  opt.set_ftol_abs(0.0);
  opt.set_ftol_rel(0.0);
  opt.set_xtol_rel(TOL);
  opt.set_xtol_abs(TOL * 1e-3);
  opt.set_maxeval(MAXITER);

  // Run optimization
  std::vector<double> x = x0;
  double min_cost;
  nlopt::result result = opt.optimize(x, min_cost);

  // Prepare results
  std::vector<std::vector<double>> solution;
  for (size_t i = 0; i < ixs.size() - 1; ++i) {
    size_t start = ixs[i];
    size_t end = ixs[i + 1];
    solution.emplace_back(x.begin() + start, x.begin() + end);
  }

  std::map<std::string, boost::variant<double, int, std::string>> status;
  status["cost"] = min_cost;
  status["iters"] = static_cast<int>(opt.get_numevals());
  status["status"] = result;

  return std::make_pair(solution, status);
}

} // namespace topo
} // namespace flywave
