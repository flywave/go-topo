// ShapeOperations.h
#pragma once

#include "compound.hh"
#include "edge.hh"
#include "face.hh"
#include "shape.hh"
#include "shell.hh"
#include "vertex.hh"
#include "wire.hh"

#include <BOPAlgo_CheckStatus.hxx>
#include <BRepCheck.hxx>
#include <GeomAbs_JoinType.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Shape.hxx>

#include <map>
#include <utility>
#include <vector>

namespace flywave {
namespace topo {

boost::optional<shape> fuse(const std::vector<shape> &shapes, double tol = 0.0,
                            bool glue = false);

boost::optional<shape> cut(const shape &shp, const shape &tool,
                           double tol = 0.0, bool glue = false);

boost::optional<shape> cut(const shape &shp, const std::vector<shape> &toCuts,
                           double tol = 0.0, bool glue = false);

boost::optional<shape> intersect(const shape &shp, const shape &toIntersect,
                                 double tol = 0.0, bool glue = false);

boost::optional<shape> intersect(const shape &shp,
                                 const std::vector<shape> &toIntersects,
                                 double tol = 0.0, bool glue = false);

boost::optional<shape>
split(const shape &shp, const std::vector<shape> &splitters, double tol = 0.0);

boost::optional<shape> split(const shape &shp, const shape &splitters,
                             double tol = 0.0);

enum class intersection_direction { None, AlongAxis, Opposite };

std::vector<face> faces_intersected_by_line(
    const shape &shp, const gp_Pnt &point, const gp_Dir &axis,
    double tolerance = 1e-4,
    intersection_direction direction = intersection_direction::None);

boost::optional<shape> fill(const shape &shp,
                            const std::vector<shape> &constraints = {});

boost::optional<shape>
shelling(const shape &shp, const std::vector<face> &faceList, double thickness,
         double tolerance = 0.0001,
         GeomAbs_JoinType joinType = GeomAbs_JoinType::GeomAbs_Arc);

boost::optional<shape> fillet(const shape &shp, const std::vector<edge> &edges,
                              double radius);

boost::optional<shape> chamfer(const shape &baseShape,
                               const std::vector<edge> &edges, double distance,
                               boost::optional<double> distance2 = boost::none);

boost::optional<shape> extrude(const shape &shape, const gp_Vec &direction);

boost::optional<shape> extrude_linear(const topo::wire &outerWire,
                                      const std::vector<topo::wire> &innerWires,
                                      const gp_Vec &vecNormal,
                                      double taper = 0.0);

boost::optional<shape> extrude_linear(const topo::face &f,
                                      const gp_Vec &vecNormal,
                                      double taper = 0.0);

boost::optional<shape> extrude_linear_with_rotation(
    const wire &outerWire, const std::vector<wire> &innerWires,
    const gp_Pnt &center, const gp_Vec &normal, double angleDegrees);

boost::optional<shape> extrude_linear_with_rotation(const face &face,
                                                    const gp_Pnt &center,
                                                    const gp_Vec &normal,
                                                    double angleDegrees);

boost::optional<shape> revolve(const shape &shape, const gp_Pnt &axisPoint,
                               const gp_Dir &axisDirection,
                               double angleDegrees = 360.0);

boost::optional<shape> revolve(const wire &outerWire,
                               const std::vector<wire> &innerWires,
                               double angleDegrees, const gp_Pnt &axisStart,
                               const gp_Pnt &axisEnd);

boost::optional<shape> revolve(const face &f, double angleDegrees,
                               const gp_Pnt &axisStart, const gp_Pnt &axisEnd);

boost::optional<shape> offset(const shape &shape, double offset,
                              bool cap = true, bool both = false,
                              double tol = 1e-6);
enum class transition_mode { TRANSFORMED, ROUND, RIGHT };

boost::optional<shape>
sweep(const wire &outerWire, const std::vector<wire> &innerWires,
      const shape &path, bool makeSolid = true, bool isFrenet = false,
      const shape *mode = nullptr,
      transition_mode transitionMode = transition_mode::RIGHT);

boost::optional<shape>
sweep(const face &face, const shape &path, bool makeSolid = true,
      bool isFrenet = false, const shape *mode = nullptr,
      transition_mode transitionMode = transition_mode::RIGHT);

boost::optional<shape> sweep_multi(const std::vector<shape> &profiles,
                                   const shape &path, bool makeSolid = true,
                                   bool isFrenet = false,
                                   const shape *mode = nullptr);

boost::optional<shape>
loft(const std::vector<shape> &profiles, bool cap = false, bool ruled = false,
     const std::string &continuity = "C2",
     const std::string &parametrization = "uniform", int degree = 3,
     bool compat = true, bool smoothing = false,
     const std::array<double, 3> &weights = {1.0, 1.0, 1.0});

boost::optional<shape> loft(const std::vector<face> &faceProfiles,
                            const std::string &continuity = "C2");

boost::optional<shape>
dprism(const shape &shp, const face &basis, const std::vector<wire> &profiles,
       const boost::optional<double> &depth = boost::none, double taper = 0,
       const face *upToFace = nullptr, bool thruAll = true,
       bool additive = true);

boost::optional<shape>
dprism(const shape &shp, const face &basis, const std::vector<face> &faces,
       const boost::optional<double> &depth = boost::none, double taper = 0,
       const face *upToFace = nullptr, bool thruAll = true,
       bool additive = true);

boost::optional<shape> imprint(const std::vector<shape> &shapes,
                               double tol = 0.0, bool glue = true,
                               std::map<std::string, shape> *history = nullptr);

boost::optional<shape> clean(const shape &shape);

bool check(const shape &shp,
           std::vector<std::pair<std::vector<shape>, BOPAlgo_CheckStatus>>
               *results = nullptr,
           double tol = 0.0);

std::pair<gp_Pnt, gp_Pnt> closest(const shape &shape1, const shape &shape2);

gp_Pnt combined_center(const std::vector<shape> &objects);

gp_Pnt combined_center_of_bound_box(const std::vector<shape> &objects);

shape read_shape_from_step(const std::string &filename);

struct wire_sample_point {
  gp_Pnt position;
  gp_Vec tangent;
  flywave::topo::edge edge;
};

std::vector<wire_sample_point>
sample_wire_at_distances(const wire &wire_path,
                         const std::vector<double> &distances);
wire clip_wire_between_distances(const wire &wire_path, double start_distance,
                                 double end_distance);

struct profile_projection {
  gp_Ax2 axes;
  gp_Trsf trsf;
  gp_Vec tangent;
  gp_Pnt position;
};

profile_projection
cacl_profile_projection(wire path, gp_Dir upDir,
                        boost::optional<double> offset = boost::none);

gp_Pnt profile_project_point(profile_projection *proj, gp_Pnt point);

double wrie_length(wire path);

} // namespace topo
} // namespace flywave
