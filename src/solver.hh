#pragma once

#include <gp.hxx>
#include <gp_Dir.hxx>
#include <gp_Lin.hxx>
#include <gp_Pln.hxx>
#include <gp_Pnt.hxx>

#include <vector>

#include <boost/variant.hpp>

namespace flywave {
namespace topo {

// 6自由度类型 (平移XYZ + 旋转XYZ)
using DOF6 = std::tuple<std::array<double, 3>, std::array<double, 3>>;

// 类型定义
using ConstraintMarker =
    boost::variant<gp_Pnt, gp_Dir, gp_Pln, gp_Lin, boost::blank>;

enum class ConstraintKind {
  Point,
  Axis,
  PointInPlane,
  PointOnLine,
  Plane,
  Fixed,
  FixedPoint,
  FixedAxis,
  FixedRotation
};

class constraint_problem;

using Constraint =
    std::tuple<std::vector<ConstraintMarker>, ConstraintKind,
               boost::variant<boost::blank, double, std::array<double, 3>,
                              std::array<double, 2>>,
               std::vector<int>>;
using ConstraintParam =
    boost::variant<boost::blank, double, std::array<double, 3>,
                   std::array<double, 2>>;
using CostFunction = std::function<double(const std::vector<double> &,
                                          const std::vector<double> &,
                                          const ConstraintParam &, double)>;

class constraint_solver {
private:
  // Problem data
  std::vector<std::pair<std::array<double, 3>, std::array<double, 3>>>
      variables_;
  std::vector<std::pair<std::array<double, 3>, std::array<double, 3>>>
      start_points_;
  std::vector<Constraint> constraints_;
  std::vector<bool> locked_;
  std::vector<gp_Trsf> initial_transforms_;
  size_t ne_;
  size_t nc_;
  double scale_;

public:
  constraint_solver(const std::vector<gp_Trsf> &entities,
                    const std::vector<Constraint> &constraints,
                    const std::vector<bool> &locked = {}, double scale = 1.0);

  std::pair<std::vector<gp_Trsf>, std::map<std::string, double>>
  solve(int verbosity = 0);

private:
  friend class constraint_problem;
};

} // namespace topo
} // namespace flywave
