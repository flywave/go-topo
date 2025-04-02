#pragma once

#include <gp.hxx>
#include <gp_Dir.hxx>
#include <gp_Lin.hxx>
#include <gp_Pln.hxx>
#include <gp_Pnt.hxx>

#include <vector>

#include <boost/variant.hpp>

#include "edge.hh"
#include "face.hh"
#include "shape.hh"
#include "wire.hh"

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

template <ConstraintKind> struct is_unary_constraint : std::false_type {};
template <ConstraintKind> struct is_binary_constraint : std::false_type {};

// Then provide specializations
template <> struct is_unary_constraint<ConstraintKind::Fixed> : std::true_type {};
template <> struct is_unary_constraint<ConstraintKind::FixedPoint> : std::true_type {};
template <> struct is_unary_constraint<ConstraintKind::FixedAxis> : std::true_type {};
template <> struct is_unary_constraint<ConstraintKind::FixedRotation> : std::true_type {};

template <> struct is_binary_constraint<ConstraintKind::Point> : std::true_type {};
template <> struct is_binary_constraint<ConstraintKind::Axis> : std::true_type {};
template <> struct is_binary_constraint<ConstraintKind::PointInPlane> : std::true_type {};
template <> struct is_binary_constraint<ConstraintKind::PointOnLine> : std::true_type {};
template <> struct is_binary_constraint<ConstraintKind::Plane> : std::true_type {};

// 约束检查函数
constexpr bool is_unary(ConstraintKind kind) {
  switch (kind) {
  case ConstraintKind::Fixed:
  case ConstraintKind::FixedPoint:
  case ConstraintKind::FixedAxis:
  case ConstraintKind::FixedRotation:
    return true;
  default:
    return false;
  }
}

constexpr bool is_binary(ConstraintKind kind) {
  switch (kind) {
  case ConstraintKind::Point:
  case ConstraintKind::Axis:
  case ConstraintKind::PointInPlane:
  case ConstraintKind::PointOnLine:
  case ConstraintKind::Plane:
    return true;
  default:
    return false;
  }
}

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

class constraint_spec {
public:
  std::vector<std::string> objects;
  std::vector<shape> args;
  std::vector<topo_location> sublocs;
  ConstraintKind kind;
  ConstraintParam param;

  constraint_spec(const std::vector<std::string> &objects,
                  const std::vector<shape> &args,
                  const std::vector<topo_location> &sublocs,
                  ConstraintKind kind,
                  const ConstraintParam &param = boost::blank{})
      : objects(objects), args(args), sublocs(sublocs), kind(kind),
        param(param) {
    _validate(args, kind, param);
  }

  std::vector<Constraint> to_pods() const {
    // Apply sublocation
    std::vector<shape> located_args;
    located_args.reserve(args.size());
    for (size_t i = 0; i < args.size(); ++i) {
      located_args.push_back(args[i].located(sublocs[i] * args[i].location()));
    }

    std::vector<std::vector<ConstraintMarker>> markers;

    switch (kind) {
    case ConstraintKind::Axis:
      markers.push_back(
          {_get_axis(located_args[0]), _get_axis(located_args[1])});
      break;
    case ConstraintKind::Point:
      markers.push_back({_get_pnt(located_args[0]), _get_pnt(located_args[1])});
      break;
    case ConstraintKind::Plane:
      markers.push_back(
          {_get_axis(located_args[0]), _get_axis(located_args[1])});
      markers.push_back({_get_pnt(located_args[0]), _get_pnt(located_args[1])});
      break;
    case ConstraintKind::PointInPlane:
      markers.push_back({_get_pnt(located_args[0]), _get_pln(located_args[1])});
      break;
    case ConstraintKind::PointOnLine:
      markers.push_back({_get_pnt(located_args[0]), _get_lin(located_args[1])});
      break;
    case ConstraintKind::Fixed:
      markers.push_back({boost::blank{}, boost::blank{}});
      break;
    case ConstraintKind::FixedPoint:
      markers.push_back({_get_pnt(located_args[0]), boost::blank{}});
      break;
    case ConstraintKind::FixedAxis:
      markers.push_back({_get_axis(located_args[0]), boost::blank{}});
      break;
    default:
      throw std::runtime_error("Unknown constraint kind");
    }

    std::vector<Constraint> constraints;
    for (auto &marker : markers) {
      constraints.emplace_back(marker, kind, param, std::vector<int>{});
    }

    return constraints;
  }

private:
  void _validate(const std::vector<shape> &args, ConstraintKind kind,
                 const ConstraintParam &param) {
    if (is_binary(kind) && args[0].is_null() && args[1].is_null()) {
      throw std::runtime_error("Invalid number of entities for constraint");
    }

    // Additional validation logic here...
  }

  gp_Dir _to_dir(gp_Vec pnt) const { return gp_Dir(pnt.X(), pnt.Y(), pnt.Z()); }

  gp_Dir _get_axis(const shape &arg) const {
    if (arg.shape_type() == "Face") {
      return _to_dir(arg.cast<face>()->normal_at());
    } else if (arg.shape_type() == "Edge" && arg.geom_type() != "CIRCLE") {
      return _to_dir(arg.cast<edge>()->tangent_at());
    } else if (arg.shape_type() == "Edge" && arg.geom_type() == "CIRCLE") {
      return _to_dir(arg.cast<edge>()->normal());
    }
    throw std::runtime_error("Cannot construct Axis");
  }

  gp_Pln _get_pln(const shape &arg) const {
    if (arg.shape_type() == "Face") {
      return gp_Pln(_get_pnt(arg), _to_dir(arg.cast<face>()->normal_at()));
    } else if (arg.shape_type() == "Edge") {
      auto normal = arg.cast<edge>()->normal();
      auto origin = arg.cast<edge>()->center();
      return gp_Pln(origin, _to_dir(normal));
    } else if (arg.shape_type() == "Wire") {
      auto normal = arg.cast<wire>()->normal();
      auto origin = arg.cast<wire>()->center();
      return gp_Pln(origin, _to_dir(normal));
    }
    throw std::runtime_error("Cannot construct a plane");
  }

  gp_Pnt _get_pnt(const shape &arg) const { return arg.centre_of_mass(); }

  gp_Lin _get_lin(const shape &arg) const {
    if (arg.shape_type() == "Edge") {
      auto center = arg.cast<edge>()->center();
      auto tangent = arg.cast<edge>()->tangent_at();
      return gp_Lin(center, _to_dir(tangent));
    } else if (arg.shape_type() == "Wire") {
      auto center = arg.cast<wire>()->center();
      auto tangent = arg.cast<wire>()->tangent_at();
      return gp_Lin(center, _to_dir(tangent));
    }
    throw std::runtime_error("Cannot construct a line");
  }
};

class constraint_solver {
private:
  // Problem data
  std::vector<std::pair<std::array<double, 3>, std::array<double, 3>>>
      variables_;
  std::vector<std::pair<std::array<double, 3>, std::array<double, 3>>>
      start_points_;
  std::vector<Constraint> constraints_;
  std::vector<size_t> locked_;
  std::vector<gp_Trsf> initial_transforms_;
  size_t ne_;
  size_t nc_;
  double scale_;

public:
  constraint_solver(const std::vector<gp_Trsf> &entities,
                    const std::vector<Constraint> &constraints,
                    const std::vector<size_t> &locked = {}, double scale = 1.0);

  std::pair<std::vector<gp_Trsf>, std::map<std::string, double>>
  solve(int verbosity = 0);

private:
  friend class constraint_problem;
};

} // namespace topo
} // namespace flywave
