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

using constraint_marker =
    boost::variant<gp_Pnt, gp_Dir, gp_Pln, gp_Lin, boost::blank>;

enum class constraint_kind {
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

template <constraint_kind> struct is_unary_constraint : std::false_type {};
template <constraint_kind> struct is_binary_constraint : std::false_type {};

template <>
struct is_unary_constraint<constraint_kind::Fixed> : std::true_type {};
template <>
struct is_unary_constraint<constraint_kind::FixedPoint> : std::true_type {};
template <>
struct is_unary_constraint<constraint_kind::FixedAxis> : std::true_type {};
template <>
struct is_unary_constraint<constraint_kind::FixedRotation> : std::true_type {};

template <>
struct is_binary_constraint<constraint_kind::Point> : std::true_type {};
template <>
struct is_binary_constraint<constraint_kind::Axis> : std::true_type {};
template <>
struct is_binary_constraint<constraint_kind::PointInPlane> : std::true_type {};
template <>
struct is_binary_constraint<constraint_kind::PointOnLine> : std::true_type {};
template <>
struct is_binary_constraint<constraint_kind::Plane> : std::true_type {};

constexpr bool is_unary(constraint_kind kind) {
  switch (kind) {
  case constraint_kind::Fixed:
  case constraint_kind::FixedPoint:
  case constraint_kind::FixedAxis:
  case constraint_kind::FixedRotation:
    return true;
  default:
    return false;
  }
}

constexpr bool is_binary(constraint_kind kind) {
  switch (kind) {
  case constraint_kind::Point:
  case constraint_kind::Axis:
  case constraint_kind::PointInPlane:
  case constraint_kind::PointOnLine:
  case constraint_kind::Plane:
    return true;
  default:
    return false;
  }
}

class constraint_problem;

using assembly_constraint =
    std::tuple<std::vector<constraint_marker>, constraint_kind,
               boost::variant<boost::blank, double, std::array<double, 3>,
                              std::array<double, 2>>,
               std::vector<int>>;
using constraint_param =
    boost::variant<boost::blank, double, std::array<double, 3>,
                   std::array<double, 2>>;
using CostFunction = std::function<double(const std::vector<double> &,
                                          const std::vector<double> &,
                                          const constraint_param &, double)>;

class constraint_spec {
public:
  std::vector<std::string> objects;
  std::vector<shape> args;
  std::vector<topo_location> sublocs;
  constraint_kind kind;
  constraint_param param;

  constraint_spec(const std::vector<std::string> &objects,
                  const std::vector<shape> &args,
                  const std::vector<topo_location> &sublocs,
                  constraint_kind kind,
                  const constraint_param &param = boost::blank{})
      : objects(objects), args(args), sublocs(sublocs), kind(kind),
        param(param) {
    _validate(args, kind, param);
  }

  std::vector<assembly_constraint> to_pods() const {
    std::vector<shape> located_args;
    located_args.reserve(args.size());
    for (size_t i = 0; i < args.size(); ++i) {
      located_args.push_back(args[i].located(sublocs[i] * args[i].location()));
    }

    std::vector<std::vector<constraint_marker>> markers;

    switch (kind) {
    case constraint_kind::Axis:
      markers.push_back(
          {_get_axis(located_args[0]), _get_axis(located_args[1])});
      break;
    case constraint_kind::Point:
      markers.push_back({_get_pnt(located_args[0]), _get_pnt(located_args[1])});
      break;
    case constraint_kind::Plane:
      markers.push_back(
          {_get_axis(located_args[0]), _get_axis(located_args[1])});
      markers.push_back({_get_pnt(located_args[0]), _get_pnt(located_args[1])});
      break;
    case constraint_kind::PointInPlane:
      markers.push_back({_get_pnt(located_args[0]), _get_pln(located_args[1])});
      break;
    case constraint_kind::PointOnLine:
      markers.push_back({_get_pnt(located_args[0]), _get_lin(located_args[1])});
      break;
    case constraint_kind::Fixed:
      markers.push_back({boost::blank{}, boost::blank{}});
      break;
    case constraint_kind::FixedPoint:
      markers.push_back({_get_pnt(located_args[0]), boost::blank{}});
      break;
    case constraint_kind::FixedAxis:
      markers.push_back({_get_axis(located_args[0]), boost::blank{}});
      break;
    default:
      throw std::runtime_error("Unknown constraint kind");
    }

    std::vector<assembly_constraint> constraints;
    for (auto &marker : markers) {
      constraints.emplace_back(marker, kind, param, std::vector<int>{});
    }

    return constraints;
  }

private:
  void _validate(const std::vector<shape> &args, constraint_kind kind,
                 const constraint_param &param) {
    if (is_binary(kind) && args[0].is_null() && args[1].is_null()) {
      throw std::runtime_error("Invalid number of entities for constraint");
    }

    if (is_unary(kind) && (args.size() != 1 || args[0].is_null())) {
      throw std::runtime_error("Invalid number of entities for constraint");
    }
  }

  gp_Dir _to_dir(gp_Vec pnt) const { return gp_Dir(pnt.X(), pnt.Y(), pnt.Z()); }

  gp_Dir _get_axis(const shape &arg) const {
    if (arg.shape_type() == TopAbs_FACE) {
      return _to_dir(arg.cast<face>()->normal_at());
    } else if (arg.shape_type() == TopAbs_EDGE &&
               arg.geom_type() != shape_geom_circle) {
      return _to_dir(arg.cast<edge>()->tangent_at());
    } else if (arg.shape_type() == TopAbs_EDGE &&
               arg.geom_type() == shape_geom_circle) {
      return _to_dir(arg.cast<edge>()->normal());
    }
    throw std::runtime_error("Cannot construct Axis");
  }

  gp_Pln _get_pln(const shape &arg) const {
    if (arg.shape_type() == TopAbs_FACE) {
      return gp_Pln(_get_pnt(arg), _to_dir(arg.cast<face>()->normal_at()));
    } else if (arg.shape_type() == TopAbs_EDGE) {
      auto normal = arg.cast<edge>()->normal();
      auto origin = arg.cast<edge>()->center();
      return gp_Pln(origin, _to_dir(normal));
    } else if (arg.shape_type() == TopAbs_WIRE) {
      auto normal = arg.cast<wire>()->normal();
      auto origin = arg.cast<wire>()->center();
      return gp_Pln(origin, _to_dir(normal));
    }
    throw std::runtime_error("Cannot construct a plane");
  }

  gp_Pnt _get_pnt(const shape &arg) const { return arg.centre_of_mass(); }

  gp_Lin _get_lin(const shape &arg) const {
    if (arg.shape_type() == TopAbs_EDGE) {
      auto center = arg.cast<edge>()->center();
      auto tangent = arg.cast<edge>()->tangent_at();
      return gp_Lin(center, _to_dir(tangent));
    } else if (arg.shape_type() == TopAbs_WIRE) {
      auto center = arg.cast<wire>()->center();
      auto tangent = arg.cast<wire>()->tangent_at();
      return gp_Lin(center, _to_dir(tangent));
    }
    throw std::runtime_error("Cannot construct a line");
  }
};

class constraint_solver {
private:
  std::vector<std::pair<std::array<double, 3>, std::array<double, 3>>>
      variables_;
  std::vector<std::pair<std::array<double, 3>, std::array<double, 3>>>
      start_points_;
  std::vector<assembly_constraint> constraints_;
  std::vector<size_t> locked_;
  std::vector<gp_Trsf> initial_transforms_;
  size_t ne_;
  size_t nc_;
  double scale_;

public:
  constraint_solver(const std::vector<gp_Trsf> &entities,
                    const std::vector<assembly_constraint> &constraints,
                    const std::vector<size_t> &locked = {}, double scale = 1.0);

  std::pair<std::vector<gp_Trsf>, std::map<std::string, double>>
  solve(int verbosity = 0);

private:
  friend class constraint_problem;
};

} // namespace topo
} // namespace flywave
