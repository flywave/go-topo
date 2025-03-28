// ShapeOperations.h
#pragma once

#include "edge.hh"
#include "face.hh"
#include "shape.hh"
#include "wire.hh"

#include <BRepCheck.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Shape.hxx>
#include <map>
#include <utility> // for std::pair
#include <vector>

namespace flywave {
namespace topo {

boost::optional<shape> fuse(const std::vector<shape> &shapes, double tol = 0.0,
                            bool glue = false);
                            
boost::optional<shape> cut(const shape &shp, const shape &tool,
                           double tol = 0.0, bool glue = false);

boost::optional<shape> intersect(const shape &shape1, const shape &shape2,
                                 double tol = 0.0, bool glue = false);

boost::optional<shape> split(const shape &shp, const shape &tool,
                             double tol = 0.0);

boost::optional<shape> fill(const shape &shp,
                            const std::vector<shape> &constraints = {});

boost::optional<shape> fillet(const shape &shp, const std::vector<edge> &edges,
                              double radius);

boost::optional<shape> chamfer(const shape &baseShape,
                               const std::vector<edge> &edges, double distance);

boost::optional<shape> extrude(const shape &shape, const gp_Vec &direction);

boost::optional<shape> revolve(const shape &shape, const gp_Pnt &axisPoint,
                               const gp_Dir &axisDirection,
                               double angleDegrees = 360.0);

boost::optional<shape> offset(const shape &shape, double offset,
                              bool cap = true, bool both = false,
                              double tol = 1e-6);

boost::optional<shape> sweep(const shape &profile, const wire &path,
                             const wire *auxiliaryPath = nullptr,
                             bool makeSolid = false);

boost::optional<shape> sweep(const std::vector<shape> &profiles,
                             const wire &path,
                             const wire *auxiliaryPath = nullptr,
                             bool makeSolid = false);

boost::optional<shape>
loft(const std::vector<shape> &profiles, bool cap = false, bool ruled = false,
     const std::string &continuity = "C2",
     const std::string &parametrization = "uniform", int degree = 3,
     bool compat = true, bool smoothing = false,
     const std::array<double, 3> &weights = {1.0, 1.0, 1.0});

boost::optional<shape> loft(const std::vector<face> &faceProfiles,
                            const std::string &continuity = "C2");

boost::optional<shape> imprint(const std::vector<shape> &shapes,
                               double tol = 0.0, bool glue = true,
                               std::map<std::string, shape> *history = nullptr);

boost::optional<shape> clean(const shape &shape);

bool check(const shape &shp,
           std::vector<std::pair<std::vector<shape>, BOPAlgo_CheckStatus>>
               *results = nullptr,
           double tol = 0.0);

std::pair<gp_Pnt, gp_Pnt> closest(const shape &shape1, const shape &shape2);

} // namespace topo
} // namespace flywave
