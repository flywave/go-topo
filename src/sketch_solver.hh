#pragma once

#include <array>
#include <map>
#include <memory>
#include <nlopt.hpp>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <boost/optional.hpp>
#include <boost/variant.hpp>

#include <gp_Dir2d.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Vec2d.hxx>

namespace flywave {
namespace topo {

typedef std::array<double, 4> segment_dof;
typedef std::array<double, 5> arc_dof;

typedef boost::variant<segment_dof, arc_dof> sketch_dof;

enum class geom_type { LINE, CIRCLE };

enum class sketch_constraint_kind {
  FIXED,
  FIXED_POINT,
  COINCIDENT,
  ANGLE,
  LENGTH,
  DISTANCE,
  RADIUS,
  ORIENTATION,
  ARC_ANGLE
};

typedef boost::variant<
    boost::blank, double,
    std::tuple<boost::optional<double>, boost::optional<double>, double>,
    std::pair<double, double>>
    sketch_constraint_value;

struct sketch_constraint {
  std::pair<size_t, boost::optional<size_t>> entities;
  sketch_constraint_kind kind;
  sketch_constraint_value value;
};
// Helper functions
gp_Pnt2d arc_first(const arc_dof &x);
gp_Pnt2d arc_last(const arc_dof &x);
gp_Pnt2d arc_point(const arc_dof &x, const boost::optional<double> &val);
gp_Pnt2d line_point(const segment_dof &x, const boost::optional<double> &val);
gp_Vec2d arc_first_tangent(const arc_dof &x);
gp_Vec2d arc_last_tangent(const arc_dof &x);

class sketch_solver {
public:
  sketch_solver(const std::vector<sketch_dof> &entities,
                const std::vector<sketch_constraint> &constraints,
                const std::vector<geom_type> &geoms);

  std::pair<std::vector<std::vector<double>>,
            std::map<std::string, boost::variant<double, int, std::string>>>
  solve();

private:
  // Cost functions
  double fixed_cost(const std::vector<double> &x,
                    const std::vector<double> &x0);
  double fixed_point_cost(const std::vector<double> &x, geom_type t,
                          const std::vector<double> &x0,
                          const boost::optional<double> &val);
  double coincident_cost(const std::vector<double> &x1, geom_type t1,
                         const std::vector<double> &x10,
                         const std::vector<double> &x2, geom_type t2,
                         const std::vector<double> &x20);
  double angle_cost(const std::vector<double> &x1, geom_type t1,
                    const std::vector<double> &x10,
                    const std::vector<double> &x2, geom_type t2,
                    const std::vector<double> &x20, double val);
  double length_cost(const std::vector<double> &x, geom_type t,
                     const std::vector<double> &x0, double val);
  double distance_cost(const std::vector<double> &x1, geom_type t1,
                       const std::vector<double> &x10,
                       const std::vector<double> &x2, geom_type t2,
                       const std::vector<double> &x20,
                       const boost::optional<double> &val1,
                       const boost::optional<double> &val2, double d);
  double radius_cost(const std::vector<double> &x, geom_type t,
                     const std::vector<double> &x0, double val);
  double orientation_cost(const std::vector<double> &x, geom_type t,
                          const std::vector<double> &x0,
                          const std::pair<double, double> &val);
  double arc_angle_cost(const std::vector<double> &x, geom_type t,
                        const std::vector<double> &x0, double val);

  // NLopt objective function
  static double objective_function(const std::vector<double> &x,
                                   std::vector<double> &grad, void *f_data);
  double compute_cost(const std::vector<double> &x, std::vector<double> &grad);

  std::vector<sketch_dof> entities;
  std::vector<sketch_constraint> constraints;
  std::vector<geom_type> geoms;
  std::vector<size_t> ixs;
  std::vector<double> x0; // Initial solution

  const double DIFF_EPS = 1e-10;
  const double TOL = 1e-9;
  const int MAXITER = 0;
};

} // namespace topo
} // namespace flywave
