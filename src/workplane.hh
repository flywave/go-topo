#pragma once

#include "comp_solid.hh"
#include "compound.hh"
#include "edge.hh"
#include "face.hh"
#include "location.hh"
#include "plane.hh"
#include "shell.hh"
#include "solid.hh"
#include "vertex.hh"
#include "wire.hh"

#include "context.hh"
#include "shape_ops.hh"
#include "sketch.hh"

#include <boost/optional.hpp>
#include <boost/variant.hpp>
#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <vector>

#include <TopoDS_Shape.hxx>
#include <gp_Pnt.hxx>

namespace flywave {
namespace topo {

// Forward declarations
class compound;
class vertex;
class wire;
class edge;
class face;
class shell;
class solid;
class comp_solid;
class shape;
class sketch;
class topo_location;
class topo_plane;
class topo_vector;

using shape_object = boost::variant<shape, topo_vector, topo_location,
                                    std::shared_ptr<sketch>, boost::blank>;

class workplane : public std::enable_shared_from_this<workplane> {
public:
  // Constructors
  workplane();
  workplane(topo_plane plane, topo_vector *origin = nullptr,
            shape_object obj = {});
  workplane(const std::string &planeName, topo_vector *origin = nullptr,
            shape_object obj = {});

  shape value() const;

  // Core methods
  template <typename T>
  std::shared_ptr<workplane> newShapeObject(const std::vector<T> &objlist);
  std::shared_ptr<workplane>
  newObject(const std::vector<shape_object> &objlist);
  std::shared_ptr<workplane>
  create(double offset = 0.0, bool invert = false,
         const std::string &centerOption = "ProjectedOrigin",
         topo_vector *origin = nullptr);

  std::shared_ptr<workplane> split(bool keepTop, bool keepBottom);
  std::shared_ptr<workplane> split(const shape &splitter);
  std::shared_ptr<workplane> split(const workplane &splitter);

  workplane &add(const workplane &other);
  workplane &add(const shape_object &obj);
  workplane &add(const std::vector<shape_object> &objs);

  std::shared_ptr<workplane> copy_workplane(const workplane &obj);
  std::shared_ptr<workplane> workplane_from_tagged(const std::string &name);
  std::shared_ptr<workplane> first();
  std::shared_ptr<workplane> item(size_t i);
  std::shared_ptr<workplane> last();
  std::shared_ptr<workplane> end(int n = 1);
  std::shared_ptr<workplane> clean();
  workplane &tag(const std::string &name);

  shape find_solid(bool searchStack, bool searchParents);

  std::shared_ptr<workplane> vertices(
      const boost::optional<
          boost::variant<std::shared_ptr<selector>, std::string>> &selector =
          boost::none,
      const boost::optional<std::string> &tag = boost::none);
  std::shared_ptr<workplane>
  faces(const boost::optional<
            boost::variant<std::shared_ptr<selector>, std::string>> &selector =
            boost::none,
        const boost::optional<std::string> &tag = boost::none);
  std::shared_ptr<workplane>
  edges(const boost::optional<
            boost::variant<std::shared_ptr<selector>, std::string>> &selector =
            boost::none,
        const boost::optional<std::string> &tag = boost::none);

  std::shared_ptr<workplane>
  wires(const boost::optional<
            boost::variant<std::shared_ptr<selector>, std::string>> &selector =
            boost::none,
        const boost::optional<std::string> &tag = boost::none);

  std::shared_ptr<workplane>
  solids(const boost::optional<
             boost::variant<std::shared_ptr<selector>, std::string>> &selector =
             boost::none,
         const boost::optional<std::string> &tag = boost::none);

  std::shared_ptr<workplane>
  shells(const boost::optional<
             boost::variant<std::shared_ptr<selector>, std::string>> &selector =
             boost::none,
         const boost::optional<std::string> &tag = boost::none);

  std::shared_ptr<workplane> compounds(
      const boost::optional<
          boost::variant<std::shared_ptr<selector>, std::string>> &selector =
          boost::none,
      const boost::optional<std::string> &tag = boost::none);

  std::shared_ptr<workplane>
  ancestors(TopAbs_ShapeEnum kind,
            const boost::optional<std::string> &tag = boost::none);

  std::shared_ptr<workplane>
  siblings(TopAbs_ShapeEnum kind, int level,
           const boost::optional<std::string> &tag = boost::none);

  std::shared_ptr<workplane> rotate_about_center(const gp_Pnt &axisEndPoint,
                                                 double angleDegrees);
  std::shared_ptr<workplane> rotate(const gp_Pnt &axisStartPoint,
                                    const gp_Pnt &axisEndPoint,
                                    double angleDegrees);
  std::shared_ptr<workplane> mirror(
      const boost::variant<std::string, gp_Vec, face, workplane> &mirrorPlane,
      const boost::optional<gp_Pnt> &basePointVector, bool unionResult);

  std::shared_ptr<workplane> translate(const gp_Vec &vec);

  std::shared_ptr<workplane> shell(double thickness, const std::string &kind);

  std::shared_ptr<workplane> fillet(double radius);

  std::shared_ptr<workplane> chamfer(double length,
                                     boost::optional<double> length2);

  std::shared_ptr<workplane> transformed(const gp_Vec &rotate,
                                         const gp_Vec &offset);

  std::shared_ptr<workplane>
  rarray(double xSpacing, double ySpacing, int xCount, int yCount,
         const boost::variant<bool, std::tuple<bool, bool>> &center);

  std::shared_ptr<workplane> polar_array(double radius, double startAngle,
                                         double angle, int count, bool fill,
                                         bool rotate);
  std::shared_ptr<workplane>
  push_points(const std::vector<topo_location> &pntList);

  std::shared_ptr<workplane>
  push_points(const std::vector<topo_vector> &pntList);

  std::shared_ptr<workplane> center(double x, double y);

  std::shared_ptr<workplane> lineTo(double x, double y,
                                    bool forConstruction = false);
  std::shared_ptr<workplane> bezier(const std::vector<gp_Pnt> &listOfPoints,
                                    bool forConstruction, bool includeCurrent,
                                    bool makeWire);
  std::shared_ptr<workplane> line(double xDist, double yDist,
                                  bool forConstruction);
  std::shared_ptr<workplane> vLine(double distance, bool forConstruction);
  std::shared_ptr<workplane> hLine(double distance, bool forConstruction);
  std::shared_ptr<workplane> vLineTo(double yCoord, bool forConstruction);
  std::shared_ptr<workplane> hLineTo(double xCoord, bool forConstruction);
  std::shared_ptr<workplane> polarLine(double distance, double angle,
                                       bool forConstruction);
  std::shared_ptr<workplane> polarLineTo(double distance, double angle,
                                         bool forConstruction);

  std::shared_ptr<workplane> moveTo(double x, double y);
  std::shared_ptr<workplane> move(double xDist, double yDist);
  std::shared_ptr<workplane> slot2D(double length, double diameter,
                                    double angle);
  std::shared_ptr<workplane>
  spline(const std::vector<gp_Pnt> &points,
         const boost::optional<std::vector<gp_Vec>> &tangents, bool periodic,
         const boost::optional<std::vector<double>> &parameters, bool scale,
         boost::optional<double> tol, bool forConstruction, bool includeCurrent,
         bool makeWire);
  std::shared_ptr<workplane> splineApprox(
      const std::vector<gp_Pnt> &points, boost::optional<double> tol,
      int minDeg, int maxDeg,
      const boost::optional<std::tuple<double, double, double>> &smoothing,
      bool forConstruction, bool includeCurrent, bool makeWire);
  std::shared_ptr<workplane>
  parametricCurve(std::function<gp_Pnt(double)> func, int N, double start,
                  double stop, double tol, int minDeg, int maxDeg,
                  const std::tuple<double, double, double> &smoothing,
                  bool makeWire);
  std::shared_ptr<workplane>
  parametricSurface(std::function<gp_Pnt(double, double)> func, int N,
                    double start, double stop, double tol, int minDeg,
                    int maxDeg,
                    const std::tuple<double, double, double> &smoothing);
  std::shared_ptr<workplane> ellipseArc(double x_radius, double y_radius,
                                        double angle1, double angle2,
                                        double rotation_angle, int sense,
                                        bool forConstruction,
                                        bool startAtCurrent, bool makeWire);
  std::shared_ptr<workplane> threePointArc(const gp_Pnt &point1,
                                           const gp_Pnt &point2,
                                           bool forConstruction = false);

  std::shared_ptr<workplane> sagittaArc(const gp_Pnt &endPoint, double sag,
                                        bool forConstruction);
  std::shared_ptr<workplane> radiusArc(const gp_Pnt &endPoint, double radius,
                                       bool forConstruction);
  std::shared_ptr<workplane>
  tangentArcPoint(const gp_Pnt &endpoint, bool forConstruction, bool relative);
  std::shared_ptr<workplane> mirrorY();
  std::shared_ptr<workplane> mirrorX();
  std::shared_ptr<workplane> consolidateWires();

  std::shared_ptr<workplane>
  each(std::function<shape_object(shape_object &)> callback,
       bool useLocalCoordinates = false, bool combine = true,
       bool clean = true);
  std::shared_ptr<workplane>
  eachpoint(const boost::variant<shape, workplane,
                                 std::function<shape(topo_location)>> &arg,
            bool useLocalCoordinates = false, bool combine = false,
            bool clean = true);
  std::shared_ptr<workplane>
  rect(double xLen, double yLen,
       const boost::variant<bool, std::tuple<bool, bool>> &centered = {},
       bool forConstruction = false);
  std::shared_ptr<workplane> circle(double radius,
                                    bool forConstruction = false);
  std::shared_ptr<workplane> ellipse(double x_radius, double y_radius,
                                     double rotation_angle,
                                     bool forConstruction);
  std::shared_ptr<workplane> polygon(int nSides, double diameter,
                                     bool forConstruction, bool circumscribed);
  std::shared_ptr<workplane> polyline(const std::vector<gp_Pnt> &points,
                                      bool forConstruction = false,
                                      bool includeCurrent = false);
  std::shared_ptr<workplane> close();

  std::shared_ptr<workplane> wire(bool forConstruction = false);

  double largestDimension();

  std::shared_ptr<workplane> cutEach(std::function<shape(topo_location)> fcn,
                                     bool useLocalCoords, bool clean);
  std::shared_ptr<workplane> cboreHole(double diameter, double cboreDiameter,
                                       double cboreDepth,
                                       boost::optional<double> depth,
                                       bool clean);
  std::shared_ptr<workplane> cskHole(double diameter, double cskDiameter,
                                     double cskAngle,
                                     boost::optional<double> depth, bool clean);
  std::shared_ptr<workplane> hole(double diameter,
                                  boost::optional<double> depth, bool clean);
  std::shared_ptr<workplane> twistExtrude(double distance, double angleDegrees,
                                          bool combine, bool clean);
  std::shared_ptr<workplane>
  extrude(boost::variant<double, std::string, face> &until,
          const boost::variant<bool, std::string> &combine, bool clean,
          bool both, boost::optional<double> taper);
  std::shared_ptr<workplane> revolve(double angleDegrees,
                                     const boost::optional<gp_Pnt> &axisStart,
                                     const boost::optional<gp_Pnt> &axisEnd,
                                     bool combine, bool clean);
  std::shared_ptr<workplane>
  sweep(boost::variant<std::shared_ptr<workplane>, topo::wire, edge> path,
        bool multisection, bool makeSolid, bool isFrenet, bool combine,
        bool clean, const transition_mode &transition,
        const boost::optional<gp_Vec> &normal,
        const boost::optional<workplane> &auxSpine);
  std::shared_ptr<workplane> combine(bool clean, bool glue,
                                     const boost::optional<double> &tol);
  std::shared_ptr<workplane>
  union_(boost::variant<std::shared_ptr<workplane>, solid, compound> toUnion,
         bool clean = true, bool glue = false,
         const boost::optional<double> &tol = boost::none);

  std::shared_ptr<workplane>
  cut(boost::variant<std::shared_ptr<workplane>, solid, compound> toCut,
      bool clean, const boost::optional<double> &tol);

  std::shared_ptr<workplane> intersect(
      boost::variant<std::shared_ptr<workplane>, solid, compound> toIntersect,
      bool clean, const boost::optional<double> &tol);

  std::shared_ptr<workplane>
  cutBlind(boost::variant<double, std::string, face> &until, bool clean,
           bool both, const boost::optional<double> &taper);

  std::shared_ptr<workplane> cutThruAll(bool clean, double taper);

  std::shared_ptr<workplane> loft(bool ruled, bool combine, bool clean);

  std::shared_ptr<workplane>
  interpPlate(boost::variant<std::vector<gp_Pnt>, std::vector<edge>, workplane>
                  &surf_edges,
              const std::vector<gp_Pnt> &surf_pts, double thickness,
              bool combine, bool clean, int degree, int nbPtsOnCur, int nbIter,
              bool anisotropy, double tol2d, double tol3d, double tolAng,
              double tolCurv, int maxDeg, int maxSegments);

  std::shared_ptr<workplane>
  box(double length, double width, double height,
      const boost::variant<bool, std::tuple<bool, bool, bool>> &centered = true,
      bool combine = true, bool clean = true);

  std::shared_ptr<workplane> sphere(
      double radius, const gp_Vec &direct = gp_Vec(0, 0, 1),
      double angle1 = -90, double angle2 = 90, double angle3 = 360,
      const boost::variant<bool, std::tuple<bool, bool, bool>> &centered = true,
      bool combine = true, bool clean = true);

  std::shared_ptr<workplane> cylinder(
      double height, double radius, const gp_Vec &direct = gp_Vec(0, 0, 1),
      double angle = 360,
      const boost::variant<bool, std::tuple<bool, bool, bool>> &centered = true,
      bool combine = true, bool clean = true);

  std::shared_ptr<workplane> wedge(
      double dx, double dy, double dz, double xmin, double zmin, double xmax,
      double zmax, const gp_Pnt &pnt = gp_Pnt(0, 0, 0),
      const gp_Vec &dir = gp_Vec(0, 0, 1),
      const boost::variant<bool, std::tuple<bool, bool, bool>> &centered = true,
      bool combine = true, bool clean = true);

  std::shared_ptr<workplane>
  text(const std::string &txt, double fontsize, double distance,
       bool cut = true, bool combine = false, bool clean = true,
       const std::string &font = "Arial",
       const boost::optional<std::string> &fontPath = boost::none,
       const std::string &kind = "regular",
       const std::string &halign = "center",
       const std::string &valign = "center");

  std::shared_ptr<workplane> section(double height = 0.0);

  workplane &toPending();

  std::shared_ptr<workplane> offset2D(double d, const std::string &kind = "arc",
                                      bool forConstruction = false);

  std::shared_ptr<topo::sketch> sketch();

  std::shared_ptr<workplane>
  placeSketch(const std::vector<topo::sketch> &sketches);

  std::shared_ptr<workplane> operator[](
      const boost::variant<int, std::vector<int>, std::pair<int, int>> &item);

  // Iterator support
  class iterator {
  public:
    iterator(std::vector<shape_object>::iterator it) : _it(it) {}

    shape &operator*();

    iterator &operator++() {
      ++_it;
      return *this;
    }

    bool operator!=(const iterator &other) const { return _it != other._it; }

  private:
    std::vector<shape_object>::iterator _it;
  };

  iterator begin() { return iterator(_objects.begin()); }

  iterator end() { return iterator(_objects.end()); }

  std::shared_ptr<workplane>
  filter(const std::function<bool(const shape_object &)> &predicate);

  std::shared_ptr<workplane>
  map(const std::function<shape_object(const shape_object &)> &mapper);

  std::shared_ptr<workplane>
  apply(const std::function<
        std::vector<shape_object>(const std::vector<shape_object> &)> &applier);

  std::shared_ptr<workplane>
  sort(const std::function<bool(const shape_object &, const shape_object &)>
           &comparator);

  workplane &
  invoke(const boost::variant<std::function<workplane &(workplane &)>,
                              std::function<void(workplane &)>,
                              std::function<void()>> &func);

  // Accessors
  std::vector<std::shared_ptr<workplane>> all();
  std::vector<shape_object> vals() const;
  shape_object val() const;
  size_t size() const;

protected:
  // Properties
  std::vector<shape_object> _objects;
  std::shared_ptr<context> _ctx;
  std::shared_ptr<workplane> _parent = nullptr;
  std::shared_ptr<topo_plane> _plane;
  boost::optional<std::string> _tag;

private:
  friend class assembly;

  static constexpr double TOL = 1e-6;

  gp_Vec plane_string_to_normal(const std::string &planeStr);
  shape_object find_type(const std::vector<std::string> &types,
                         bool searchStack, bool searchParents);
  std::shared_ptr<workplane> select_objects(
      const std::string &objType,
      const boost::optional<
          boost::variant<std::shared_ptr<selector>, std::string>> &selector,
      const boost::optional<std::string> &tag);
  std::vector<shape>
  filter(const std::vector<shape> &objs,
         const boost::optional<
             boost::variant<std::shared_ptr<selector>, std::string>> &selector);
  gp_Pnt find_from_point(bool useLocalCoords = false);
  edge find_from_edge(bool useLocalCoords = false);

  // Internal helper methods
  std::vector<face> getFaces();
  std::vector<shape> getFacesVertices();
  bool areFacesCoplanar(const std::vector<face> &faces) const;
  shape
  _extrude(const boost::optional<double> &distance, bool both = false,
           const boost::optional<double> &taper = boost::none,
           boost::optional<boost::variant<int, face>> upToFace = boost::none,
           bool additive = true);
  std::vector<face>
  _getIntersectedFaces(const face &face, const gp_Vec &eDir,
                       const flywave::topo::intersection_direction &direction,
                       bool both);
  shape _revolve(double angleDegrees, const gp_Pnt &axisStart,
                 const gp_Pnt &axisEnd);
  shape _sweep(boost::variant<std::shared_ptr<workplane>, topo::wire, topo::edge> &path,
               bool multisection, bool makeSolid, bool isFrenet,
               const transition_mode &transition,
               const boost::optional<gp_Vec> &normal,
               const boost::optional<workplane> &auxSpine);
  gp_Vec computeXDir(const gp_Vec &normal) const;
  std::vector<shape> collectProperty(const std::string &propName);
  std::shared_ptr<workplane>
  combineWithBase(const boost::variant<shape, std::vector<shape>> &obj,
                  const boost::variant<bool, std::string> &mode = true,
                  bool clean = false);
  shape fuseWithBase(const shape &obj);
  shape cutFromBase(const shape &obj);
  shape &findType(const std::vector<std::string> &types, bool searchStack,
                  bool searchParents);
  solid &findSolid(bool searchStack = true, bool searchParents = true);
  std::shared_ptr<workplane> getTagged(const std::string &name);
  workplane &mergeTags(const workplane &other);
  void addPendingEdge(const edge &e);
  void addPendingWire(const topo::wire &w);
  std::vector<topo::wire> _consolidateWires();
  std::vector<topo_location> locs();
};

} // namespace topo
} // namespace flywave
