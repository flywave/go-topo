#include "sketch_solver.hh"

namespace flywave {
namespace topo {

gp_Pnt2d arc_first(const arc_dof &x) {
  return gp_Pnt2d(x[0] + x[2] * std::sin(x[3]), x[1] + x[2] * std::cos(x[3]));
}

gp_Pnt2d arc_last(const arc_dof &x) {
  return gp_Pnt2d(x[0] + x[2] * std::sin(x[3] + x[4]),
                  x[1] + x[2] * std::cos(x[3] + x[4]));
}

gp_Pnt2d arc_point(const arc_dof &x, const boost::optional<double> &val) {
  if (!val) {
    return gp_Pnt2d(x[0], x[1]);
  }
  double a = x[3] + *val * x[4];
  return gp_Pnt2d(x[0] + x[2] * std::sin(a), x[1] + x[2] * std::cos(a));
}

gp_Pnt2d line_point(const segment_dof &x, const boost::optional<double> &val) {
  if (!val) {
    return gp_Pnt2d(x[0], x[1]);
  }
  double t = *val;
  return gp_Pnt2d(x[0] + t * (x[2] - x[0]), x[1] + t * (x[3] - x[1]));
}

gp_Vec2d arc_first_tangent(const arc_dof &x) {
  double sign_da = x[4] > 0 ? 1.0 : -1.0;
  return gp_Vec2d(sign_da * std::cos(x[3]), -sign_da * std::sin(x[3]));
}

gp_Vec2d arc_last_tangent(const arc_dof &x) {
  double sign_da = x[4] > 0 ? 1.0 : -1.0;
  return gp_Vec2d(sign_da * std::cos(x[3] + x[4]),
                  -sign_da * std::sin(x[3] + x[4]));
}

double sketch_solver::fixed_cost(const std::vector<double> &x,
                                 const std::vector<double> &x0) {
  double sum = 0.0;
  for (size_t i = 0; i < x.size(); ++i) {
    double diff = x[i] - x0[i];
    sum += diff * diff;
  }
  return std::sqrt(sum);
}

double sketch_solver::fixed_point_cost(const std::vector<double> &x,
                                       geom_type t,
                                       const std::vector<double> &x0,
                                       const boost::optional<double> &val) {
  gp_Pnt2d p, p0;

  if (t == geom_type::LINE) {
    segment_dof seg{{x[0], x[1], x[2], x[3]}};
    segment_dof seg0{{x0[0], x0[1], x0[2], x0[3]}};
    p = line_point(seg, val);
    p0 = line_point(seg0, val);
  } else if (t == geom_type::CIRCLE) {
    arc_dof arc{{x[0], x[1], x[2], x[3], x[4]}};
    arc_dof arc0{{x0[0], x0[1], x0[2], x0[3], x0[4]}};
    p = arc_point(arc, val);
    p0 = arc_point(arc0, val);
  } else {
    throw std::invalid_argument("Invalid geometry type");
  }

  return p.Distance(p0);
}

double sketch_solver::coincident_cost(
    const std::vector<double> &x1, geom_type t1, const std::vector<double> &x10,
    const std::vector<double> &x2, geom_type t2, const std::vector<double> &x20,
    const boost::optional<double> &val) {
  gp_Pnt2d p1, p2;

  if (t1 == geom_type::LINE) {
    segment_dof seg1{{x1[0], x1[1], x1[2], x1[3]}};
    p1 = line_point(seg1, val); // 使用val参数
  } else if (t1 == geom_type::CIRCLE) {
    arc_dof arc1{{x1[0], x1[1], x1[2], x1[3], x1[4]}};
    p1 = arc_point(arc1, val); // 使用val参数
  }

  if (t2 == geom_type::LINE) {
    segment_dof seg2{{x2[0], x2[1], x2[2], x2[3]}};
    p2 = line_point(seg2, val); // 使用val参数
  } else if (t2 == geom_type::CIRCLE) {
    arc_dof arc2{{x2[0], x2[1], x2[2], x2[3], x2[4]}};
    p2 = arc_point(arc2, val); // 使用val参数
  }

  return p1.Distance(p2);
}
double sketch_solver::angle_cost(const std::vector<double> &x1, geom_type t1,
                                 const std::vector<double> &x10,
                                 const std::vector<double> &x2, geom_type t2,
                                 const std::vector<double> &x20, double val) {
  gp_Vec2d v1, v2;

  if (t1 == geom_type::LINE) {
    segment_dof seg1{{x1[0], x1[1], x1[2], x1[3]}};
    gp_Pnt2d p1 = line_point(seg1, 0);
    gp_Pnt2d p2 = line_point(seg1, 1);
    v1 = gp_Vec2d(p2.X() - p1.X(), p2.Y() - p1.Y());
  } else if (t1 == geom_type::CIRCLE) {
    arc_dof arc1{{x1[0], x1[1], x1[2], x1[3], x1[4]}};
    v1 = arc_first_tangent(arc1);
  }

  if (t2 == geom_type::LINE) {
    segment_dof seg2{{x2[0], x2[1], x2[2], x2[3]}};
    gp_Pnt2d p1 = line_point(seg2, 0);
    gp_Pnt2d p2 = line_point(seg2, 1);
    v2 = gp_Vec2d(p2.X() - p1.X(), p2.Y() - p1.Y());
  } else if (t2 == geom_type::CIRCLE) {
    arc_dof arc2{{x2[0], x2[1], x2[2], x2[3], x2[4]}};
    v2 = arc_first_tangent(arc2);
  }

  double angle = v1.Angle(v2);
  return std::abs(angle - val);
}

double sketch_solver::length_cost(const std::vector<double> &x, geom_type t,
                                  const std::vector<double> &x0, double val) {
  if (t == geom_type::LINE) {
    segment_dof seg{{x[0], x[1], x[2], x[3]}};
    gp_Pnt2d p1 = line_point(seg, 0);
    gp_Pnt2d p2 = line_point(seg, 1);
    double len = p1.Distance(p2);
    return std::abs(len - val);
  } else if (t == geom_type::CIRCLE) {
    arc_dof arc{{x[0], x[1], x[2], x[3], x[4]}};
    double circumference = 2 * M_PI * arc[2];
    double arc_len = circumference * std::abs(arc[4]) / (2 * M_PI);
    return std::abs(arc_len - val);
  }
  return 0.0;
}

double sketch_solver::distance_cost(const std::vector<double> &x1, geom_type t1,
                                    const std::vector<double> &x10,
                                    const std::vector<double> &x2, geom_type t2,
                                    const std::vector<double> &x20,
                                    const boost::optional<double> &val1,
                                    const boost::optional<double> &val2,
                                    double d) {
  gp_Pnt2d p1, p2;

  if (t1 == geom_type::LINE) {
    segment_dof seg1{{x1[0], x1[1], x1[2], x1[3]}};
    p1 = line_point(seg1, val1);
  } else if (t1 == geom_type::CIRCLE) {
    arc_dof arc1{{x1[0], x1[1], x1[2], x1[3], x1[4]}};
    p1 = arc_point(arc1, val1);
  }

  if (t2 == geom_type::LINE) {
    segment_dof seg2{{x2[0], x2[1], x2[2], x2[3]}};
    p2 = line_point(seg2, val2);
  } else if (t2 == geom_type::CIRCLE) {
    arc_dof arc2{{x2[0], x2[1], x2[2], x2[3], x2[4]}};
    p2 = arc_point(arc2, val2);
  }

  return std::abs(p1.Distance(p2) - d);
}

double sketch_solver::orientation_cost(const std::vector<double> &x,
                                       geom_type t,
                                       const std::vector<double> &x0,
                                       const std::pair<double, double> &val) {
  gp_Vec2d v;

  if (t == geom_type::LINE) {
    segment_dof seg{{x[0], x[1], x[2], x[3]}};
    gp_Pnt2d p1 = line_point(seg, 0);
    gp_Pnt2d p2 = line_point(seg, 1);
    v = gp_Vec2d(p2.X() - p1.X(), p2.Y() - p1.Y());
  } else if (t == geom_type::CIRCLE) {
    arc_dof arc{{x[0], x[1], x[2], x[3], x[4]}};
    v = arc_first_tangent(arc);
  }

  double angle = v.Angle(gp_Vec2d(val.first, val.second));
  return std::abs(angle);
}

double sketch_solver::arc_angle_cost(const std::vector<double> &x, geom_type t,
                                     const std::vector<double> &x0,
                                     double val) {
  if (t != geom_type::CIRCLE) {
    return 0.0;
  }

  arc_dof arc{{x[0], x[1], x[2], x[3], x[4]}};
  return std::abs(arc[4] - val);
}

double sketch_solver::radius_cost(const std::vector<double> &x, geom_type t,
                                  const std::vector<double> &x0, double val) {
  if (t != geom_type::CIRCLE) {
    throw std::invalid_argument("radius constraint only applies to circles");
  }

  arc_dof arc{{x[0], x[1], x[2], x[3], x[4]}};
  return std::abs(arc[2] - val);
}

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

    std::vector<double> x1(x.begin() + ixs[e1], x.begin() + ixs[e1 + 1]);
    std::vector<double> x10(x0.begin() + ixs[e1], x0.begin() + ixs[e1 + 1]);

    std::vector<double> x2, x20;
    if (e2) {
      x2 = std::vector<double>(x.begin() + ixs[*e2], x.begin() + ixs[*e2 + 1]);
      x20 =
          std::vector<double>(x0.begin() + ixs[*e2], x0.begin() + ixs[*e2 + 1]);
    }

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

    if (!grad.empty()) {
      std::vector<double> x_perturbed = x;
      double original_cost = constraint_cost;

      for (size_t j = ixs[e1]; j < ixs[e1 + 1]; ++j) {
        x_perturbed[j] += DIFF_EPS;

        std::vector<double> x1_perturbed(x_perturbed.begin() + ixs[e1],
                                         x_perturbed.begin() + ixs[e1 + 1]);
        double perturbed_cost = 0.0;

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
        x_perturbed[j] = x[j];
      }

      if (e2) {
        for (size_t j = ixs[*e2]; j < ixs[*e2 + 1]; ++j) {
          x_perturbed[j] += DIFF_EPS;

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
          x_perturbed[j] = x[j];
        }
      }
    }
  }

  return cost;
}

sketch_solver::sketch_solver(const std::vector<sketch_dof> &entities,
                             const std::vector<sketch_constraint> &constraints,
                             const std::vector<geom_type> &geoms)
    : entities(entities), constraints(constraints), geoms(geoms) {

  ixs.push_back(0);
  for (const auto &e : entities) {
    size_t size = 0;
    if (e.type() == typeid(segment_dof)) {
      size = 4;
    } else if (e.type() == typeid(arc_dof)) {
      size = 5;
    }
    ixs.push_back(ixs.back() + size);
  }

  x0.reserve(ixs.back());
  for (const auto &e : entities) {
    if (e.type() == typeid(segment_dof)) {
      const segment_dof &seg = boost::get<segment_dof>(e);
      x0.insert(x0.end(), seg.begin(), seg.end());
    } else if (e.type() == typeid(arc_dof)) {
      const arc_dof &arc = boost::get<arc_dof>(e);
      x0.insert(x0.end(), arc.begin(), arc.end());
    }
  }
}

std::pair<std::vector<std::vector<double>>,
          std::map<std::string, boost::variant<double, int, std::string>>>
sketch_solver::solve() {
  nlopt::opt opt(nlopt::LD_SLSQP, static_cast<int>(x0.size()));

  opt.set_min_objective(objective_function, this);

  std::vector<double> lb(x0.size(), -std::numeric_limits<double>::infinity());
  std::vector<double> ub(x0.size(), std::numeric_limits<double>::infinity());

  for (size_t i = 0; i < geoms.size(); ++i) {
    if (geoms[i] == geom_type::CIRCLE) {
      lb[ixs[i] + 2] = 0.0;
    }
  }

  opt.set_lower_bounds(lb);
  opt.set_upper_bounds(ub);

  opt.set_ftol_abs(0.0);
  opt.set_ftol_rel(0.0);
  opt.set_xtol_rel(TOL);
  opt.set_xtol_abs(TOL * 1e-3);
  opt.set_maxeval(MAXITER);

  std::vector<double> x = x0;
  double min_cost;
  nlopt::result result = opt.optimize(x, min_cost);

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
