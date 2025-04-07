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

namespace flywave {
namespace topo {

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

enum class shape_object_type {
  compound = TopAbs_COMPOUND,
  comp_solid = TopAbs_COMPSOLID,
  solid = TopAbs_SOLID,
  shell = TopAbs_SHELL,
  face = TopAbs_FACE,
  wire = TopAbs_WIRE,
  edge = TopAbs_EDGE,
  vertex = TopAbs_VERTEX,
  shape = TopAbs_SHAPE,
  vector = 100,
  location = 101,
  sketch = 102,
  blank = 103
};

enum class combine_mode_type {
  cut,
  additive,
  subtractive,
};

typedef boost::variant<bool, combine_mode_type> combine_mode;

enum class center_option { CenterOfMass, ProjectedOrigin, CenterOfBoundBox };

enum class face_index_type {
  curent = 0,
  next = -1,
};

class workplane : public std::enable_shared_from_this<workplane> {
public:
  workplane();
  workplane(topo_plane plane, topo_vector *origin = nullptr,
            shape_object obj = {});
  workplane(const std::string &planeName, topo_vector *origin = nullptr,
            shape_object obj = {});

  workplane(const workplane &) = delete;
  workplane &operator=(const workplane &) = delete;

  ~workplane() = default;

  workplane(workplane &&) noexcept;
  workplane &operator=(workplane &&) noexcept;

  shape value() const;

  template <typename T>
  std::shared_ptr<workplane>
  new_shape_object(const std::vector<T> &objlist) const;
  std::shared_ptr<workplane>
  new_object(const std::vector<shape_object> &objlist) const;
  std::shared_ptr<workplane>
  create(double offset = 0.0, bool invert = false,
         const center_option &centerOption = center_option::ProjectedOrigin,
         topo_vector *origin = nullptr);

  std::shared_ptr<workplane> split(bool keepTop, bool keepBottom);
  std::shared_ptr<workplane> split(const shape &splitter);
  std::shared_ptr<workplane> split(const workplane &splitter);

  workplane &add(const workplane &other);
  workplane &add(const shape_object &obj);
  workplane &add(const std::vector<shape_object> &objs);

  std::shared_ptr<workplane> copy_workplane(const workplane &obj);
  std::shared_ptr<workplane> from_tagged(const std::string &name);
  std::shared_ptr<workplane> first();
  std::shared_ptr<workplane> item(size_t i);
  std::shared_ptr<workplane> last();
  std::shared_ptr<workplane> end(int n = 1);
  std::shared_ptr<workplane> clean();

  workplane &tag(const std::string &name);

  solid find_solid(bool searchStack = true, bool searchParents = true) const;

  std::shared_ptr<workplane> vertices(const std::string &selector = "",
                                      const std::string &tag = "") const;
  std::shared_ptr<workplane> vertices(const selector_ptr &sel,
                                      const std::string &tag = "") const;

  std::shared_ptr<workplane> faces(const std::string &selector = "",
                                   const std::string &tag = "") const;
  std::shared_ptr<workplane> faces(const selector_ptr &sel,
                                   const std::string &tag = "") const;

  std::shared_ptr<workplane> edges(const std::string &selector = "",
                                   const std::string &tag = "") const;
  std::shared_ptr<workplane> edges(const selector_ptr &sel,
                                   const std::string &tag = "") const;

  std::shared_ptr<workplane> wires(const std::string &selector = "",
                                   const std::string &tag = "") const;
  std::shared_ptr<workplane> wires(const selector_ptr &sel,
                                   const std::string &tag = "") const;

  std::shared_ptr<workplane> solids(const std::string &selector = "",
                                    const std::string &tag = "") const;
  std::shared_ptr<workplane> solids(const selector_ptr &sel,
                                    const std::string &tag = "") const;

  std::shared_ptr<workplane> shells(const std::string &selector = "",
                                    const std::string &tag = "") const;
  std::shared_ptr<workplane> shells(const selector_ptr &sel,
                                    const std::string &tag = "") const;

  std::shared_ptr<workplane> compounds(const std::string &selector = "",
                                       const std::string &tag = "") const;
  std::shared_ptr<workplane> compounds(const selector_ptr &sel,
                                       const std::string &tag = "") const;

  std::shared_ptr<workplane>
  ancestors(TopAbs_ShapeEnum kind,
            const boost::optional<std::string> &tag = boost::none) const;
  std::shared_ptr<workplane>
  siblings(TopAbs_ShapeEnum kind, int level,
           const boost::optional<std::string> &tag = boost::none) const;

  std::shared_ptr<workplane> rotate_about_center(const gp_Pnt &axisEndPoint,
                                                 double angleDegrees);
  std::shared_ptr<workplane> rotate(const gp_Pnt &axisStartPoint,
                                    const gp_Pnt &axisEndPoint,
                                    double angleDegrees);

  std::shared_ptr<workplane> mirror(const std::string &planeName,
                                    const gp_Pnt &basePoint = gp_Pnt(),
                                    bool unionResult = false);
  std::shared_ptr<workplane> mirror(const gp_Vec &normal,
                                    const gp_Pnt &basePoint = gp_Pnt(),
                                    bool unionResult = false);
  std::shared_ptr<workplane> mirror(const face &mirrorFace,
                                    const gp_Pnt &basePoint = gp_Pnt(),
                                    bool unionResult = false);
  std::shared_ptr<workplane> mirror(const workplane &mirrorPlane,
                                    const gp_Pnt &basePoint = gp_Pnt(),
                                    bool unionResult = false);

  std::shared_ptr<workplane> translate(const gp_Vec &vec);

  std::shared_ptr<workplane> shell(double thickness, const std::string &kind);

  std::shared_ptr<workplane> fillet(double radius);

  std::shared_ptr<workplane> chamfer(double length,
                                     boost::optional<double> length2);

  std::shared_ptr<workplane> transformed(const gp_Vec &rotate,
                                         const gp_Vec &offset);

  std::shared_ptr<workplane>
  rarray(double xSpacing, double ySpacing, int xCount, int yCount,
         std::pair<bool, bool> center = {false, false});

  std::shared_ptr<workplane> rarray(double xSpacing, double ySpacing,
                                    int xCount, int yCount,
                                    bool centerAll = false);

  std::shared_ptr<workplane> polar_array(double radius, double startAngle,
                                         double angle, int count, bool fill,
                                         bool rotate);
  std::shared_ptr<workplane>
  push_points(const std::vector<topo_location> &pntList);

  std::shared_ptr<workplane>
  push_points(const std::vector<topo_vector> &pntList);

  std::shared_ptr<workplane> center(double x, double y);

  std::shared_ptr<workplane> line_to(double x, double y,
                                     bool forConstruction = false);
  std::shared_ptr<workplane>
  bezier(const std::vector<topo_vector> &listOfPoints, bool forConstruction,
         bool includeCurrent, bool makeWire);
  std::shared_ptr<workplane> line(double xDist, double yDist,
                                  bool forConstruction);
  std::shared_ptr<workplane> vline(double distance, bool forConstruction);
  std::shared_ptr<workplane> hline(double distance, bool forConstruction);
  std::shared_ptr<workplane> vline_to(double yCoord, bool forConstruction);
  std::shared_ptr<workplane> hline_to(double xCoord, bool forConstruction);
  std::shared_ptr<workplane> polar_line(double distance, double angle,
                                        bool forConstruction);
  std::shared_ptr<workplane> polar_line_to(double distance, double angle,
                                           bool forConstruction);

  std::shared_ptr<workplane> move_to(double x, double y);
  std::shared_ptr<workplane> move(double xDist, double yDist);
  std::shared_ptr<workplane> slot2d(double length, double diameter,
                                    double angle);
  std::shared_ptr<workplane>
  spline(const std::vector<gp_Pnt> &points,
         const boost::optional<std::vector<gp_Vec>> &tangents, bool periodic,
         const boost::optional<std::vector<double>> &parameters, bool scale,
         boost::optional<double> tol, bool forConstruction, bool includeCurrent,
         bool makeWire);
  std::shared_ptr<workplane> spline_approx(
      const std::vector<gp_Pnt> &points, boost::optional<double> tol,
      int minDeg, int maxDeg,
      const boost::optional<std::tuple<double, double, double>> &smoothing,
      bool forConstruction, bool includeCurrent, bool makeWire);
  std::shared_ptr<workplane>
  parametric_curve(std::function<gp_Pnt(double)> func, int N, double start,
                   double stop, double tol, int minDeg, int maxDeg,
                   const std::tuple<double, double, double> &smoothing,
                   bool makeWire);
  std::shared_ptr<workplane>
  parametric_surface(std::function<gp_Pnt(double, double)> func, int N,
                     double start, double stop, double tol, int minDeg,
                     int maxDeg,
                     const std::tuple<double, double, double> &smoothing);
  std::shared_ptr<workplane> ellipse_arc(double x_radius, double y_radius,
                                         double angle1, double angle2,
                                         double rotation_angle, int sense,
                                         bool forConstruction,
                                         bool startAtCurrent, bool makeWire);
  std::shared_ptr<workplane> three_point_arc(const gp_Pnt &point1,
                                             const gp_Pnt &point2,
                                             bool forConstruction = false);

  std::shared_ptr<workplane> sagitta_arc(const gp_Pnt &endPoint, double sag,
                                         bool forConstruction);
  std::shared_ptr<workplane> radius_arc(const gp_Pnt &endPoint, double radius,
                                        bool forConstruction);
  std::shared_ptr<workplane> tangent_arc_point(const gp_Pnt &endpoint,
                                               bool forConstruction,
                                               bool relative);
  std::shared_ptr<workplane> mirror_y();
  std::shared_ptr<workplane> mirror_x();
  std::shared_ptr<workplane> consolidate_wires();

  std::shared_ptr<workplane>
  each(std::function<shape_object(shape_object &)> callback,
       bool useLocalCoordinates = false, bool combine = true,
       bool clean = true);

  std::shared_ptr<workplane> eachpoint(const shape &shapeObj,
                                       bool useLocalCoordinates = false,
                                       bool combine = true, bool clean = true);
  std::shared_ptr<workplane> eachpoint(std::function<shape(topo_location)> func,
                                       bool useLocalCoordinates = false,
                                       bool combine = true, bool clean = true);
  std::shared_ptr<workplane> eachpoint(const workplane &wp,
                                       bool useLocalCoordinates = false,
                                       bool combine = true, bool clean = true);

  std::shared_ptr<workplane> rect(double xLen, double yLen,
                                  std::pair<bool, bool> center = {false, false},
                                  bool forConstruction = false);
  std::shared_ptr<workplane> rect(double xLen, double yLen,
                                  bool centerAll = false,
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

  double largest_dimension() const;

  std::shared_ptr<workplane> cut_each(std::function<shape(topo_location)> fcn,
                                      bool useLocalCoords, bool clean);
  std::shared_ptr<workplane> cbore_hole(double diameter, double cboreDiameter,
                                        double cboreDepth,
                                        boost::optional<double> depth,
                                        bool clean);
  std::shared_ptr<workplane> csk_hole(double diameter, double cskDiameter,
                                      double cskAngle,
                                      boost::optional<double> depth,
                                      bool clean);
  std::shared_ptr<workplane> hole(double diameter,
                                  boost::optional<double> depth, bool clean);
  std::shared_ptr<workplane> twist_extrude(double distance, double angleDegrees,
                                           bool combine, bool clean);

  std::shared_ptr<workplane>
  extrude(double distance, const combine_mode &combine = true,
          bool clean = true, bool both = false,
          boost::optional<double> taper = boost::none);
  std::shared_ptr<workplane>
  extrude(face_index_type untilFace, const combine_mode &combine = true,
          bool clean = true, bool both = false,
          boost::optional<double> taper = boost::none);
  std::shared_ptr<workplane>
  extrude(const face &untilFace, const combine_mode &combine = true,
          bool clean = true, bool both = false,
          boost::optional<double> taper = boost::none);

  std::shared_ptr<workplane>
  sweep(workplane &path, bool multisection = false, bool makeSolid = true,
        bool isFrenet = false, bool combine = true, bool clean = true,
        const transition_mode &transition = transition_mode::RIGHT,
        const boost::optional<topo_vector> &normal = boost::none,
        const std::shared_ptr<workplane> &auxSpine = nullptr);
  std::shared_ptr<workplane>
  sweep(const topo::wire &path, bool multisection = false,
        bool makeSolid = true, bool isFrenet = false, bool combine = true,
        bool clean = true,
        const transition_mode &transition = transition_mode::RIGHT,
        const boost::optional<topo_vector> &normal = boost::none,
        const std::shared_ptr<workplane> &auxSpine = nullptr);
  std::shared_ptr<workplane>
  sweep(const edge &path, bool multisection = false, bool makeSolid = true,
        bool isFrenet = false, bool combine = true, bool clean = true,
        const transition_mode &transition = transition_mode::RIGHT,
        const boost::optional<topo_vector> &normal = boost::none,
        const std::shared_ptr<workplane> &auxSpine = nullptr);

  std::shared_ptr<workplane> union_(const workplane &other, bool clean = true,
                                    bool glue = false, double tol = 1e-6);
  std::shared_ptr<workplane> union_(const solid &other, bool clean = true,
                                    bool glue = false, double tol = 1e-6);
  std::shared_ptr<workplane> union_(const compound &other, bool clean = true,
                                    bool glue = false, double tol = 1e-6);

  std::shared_ptr<workplane> cut(const workplane &other, bool clean = true,
                                 double tol = 1e-6);
  std::shared_ptr<workplane> cut(const solid &other, bool clean = true,
                                 double tol = 1e-6);
  std::shared_ptr<workplane> cut(const compound &other, bool clean = true,
                                 double tol = 1e-6);

  std::shared_ptr<workplane> intersect(const workplane &other,
                                       bool clean = true, double tol = 1e-6);
  std::shared_ptr<workplane> intersect(const solid &other, bool clean = true,
                                       double tol = 1e-6);
  std::shared_ptr<workplane> intersect(const compound &other, bool clean = true,
                                       double tol = 1e-6);

  std::shared_ptr<workplane>
  cut_blind(double distance, bool clean = true, bool both = false,
            const boost::optional<double> &taper = boost::none);
  std::shared_ptr<workplane>
  cut_blind(face_index_type untilFace, bool clean = true, bool both = false,
            const boost::optional<double> &taper = boost::none);
  std::shared_ptr<workplane>
  cut_blind(const face &untilFace, bool clean = true, bool both = false,
            const boost::optional<double> &taper = boost::none);

  std::shared_ptr<workplane> revolve(double angleDegrees,
                                     const boost::optional<gp_Pnt> &axisStart,
                                     const boost::optional<gp_Pnt> &axisEnd,
                                     bool combine, bool clean);

  std::shared_ptr<workplane>
  interp_plate(const std::vector<gp_Pnt> &points, double thickness,
               bool combine = true, bool clean = true, int degree = 3,
               int nbPtsOnCur = 15, int nbIter = 2, bool anisotropy = false,
               double tol2d = 1e-6, double tol3d = 1e-4, double tolAng = 1e-2,
               double tolCurv = 1e-1, int maxDeg = 8, int maxSegments = 9);
  std::shared_ptr<workplane>
  interp_plate(const std::vector<edge> &edges,
               const std::vector<gp_Pnt> &points, double thickness,
               bool combine = true, bool clean = true, int degree = 3,
               int nbPtsOnCur = 15, int nbIter = 2, bool anisotropy = false,
               double tol2d = 1e-6, double tol3d = 1e-4, double tolAng = 1e-2,
               double tolCurv = 1e-1, int maxDeg = 8, int maxSegments = 9);
  std::shared_ptr<workplane>
  interp_plate(const workplane &wp, const std::vector<gp_Pnt> &points,
               double thickness, bool combine = true, bool clean = true,
               int degree = 3, int nbPtsOnCur = 15, int nbIter = 2,
               bool anisotropy = false, double tol2d = 1e-6,
               double tol3d = 1e-4, double tolAng = 1e-2, double tolCurv = 1e-1,
               int maxDeg = 8, int maxSegments = 9);

  std::shared_ptr<workplane>
  box(double length, double width, double height,
      const std::array<bool, 3> &center = {false, false, false},
      bool combine = true, bool clean = true);
  std::shared_ptr<workplane> box(double length, double width, double height,
                                 bool centerAll = true, bool combine = true,
                                 bool clean = true);

  std::shared_ptr<workplane>
  sphere(double radius, const gp_Vec &direct = gp_Vec(0, 0, 1),
         double angle1 = -90, double angle2 = 90, double angle3 = 360,
         const std::array<bool, 3> &center = {false, false, false},
         bool combine = true, bool clean = true);
  std::shared_ptr<workplane> sphere(double radius,
                                    const gp_Vec &direct = gp_Vec(0, 0, 1),
                                    double angle1 = -90, double angle2 = 90,
                                    double angle3 = 360, bool centerAll = true,
                                    bool combine = true, bool clean = true);

  std::shared_ptr<workplane>
  cylinder(double height, double radius, const gp_Vec &direct = gp_Vec(0, 0, 1),
           double angle = 360,
           const std::array<bool, 3> &center = {false, false, false},
           bool combine = true, bool clean = true);
  std::shared_ptr<workplane> cylinder(double height, double radius,
                                      const gp_Vec &direct = gp_Vec(0, 0, 1),
                                      double angle = 360, bool centerAll = true,
                                      bool combine = true, bool clean = true);

  std::shared_ptr<workplane>
  wedge(double dx, double dy, double dz, double xmin, double zmin, double xmax,
        double zmax, const gp_Pnt &pnt = gp_Pnt(0, 0, 0),
        const gp_Vec &dir = gp_Vec(0, 0, 1),
        const std::array<bool, 3> &center = {false, false, false},
        bool combine = true, bool clean = true);
  std::shared_ptr<workplane> wedge(double dx, double dy, double dz, double xmin,
                                   double zmin, double xmax, double zmax,
                                   const gp_Pnt &pnt = gp_Pnt(0, 0, 0),
                                   const gp_Vec &dir = gp_Vec(0, 0, 1),
                                   bool centerAll = true, bool combine = true,
                                   bool clean = true);

  std::shared_ptr<workplane> combine(bool clean, bool glue,
                                     const boost::optional<double> &tol);

  std::shared_ptr<workplane> cut_thru_all(bool clean, double taper);

  std::shared_ptr<workplane> loft(bool ruled, bool combine, bool clean);

  std::shared_ptr<workplane>
  text(const std::string &txt, double fontsize, double distance,
       bool cut = true, bool combine = false, bool clean = true,
       const std::string &font = "Arial",
       const boost::optional<std::string> &fontPath = boost::none,
       const font_kind &kind = font_kind::REGULAR,
       const horizontal_align &halign = horizontal_align::CENTER,
       const vertical_align &valign = vertical_align::CENTER);

  std::shared_ptr<workplane> section(double height = 0.0);

  workplane &to_pending();

  std::shared_ptr<workplane>
  offset2d(double d, const GeomAbs_JoinType &kind = GeomAbs_Arc,
           bool forConstruction = false);

  std::shared_ptr<topo::sketch> sketch();

  std::shared_ptr<workplane>
  place_sketch(const std::vector<std::shared_ptr<topo::sketch>> &sketches);

  std::shared_ptr<workplane> operator[](int index);

  std::shared_ptr<workplane> operator[](const std::vector<int> &indices);

  std::shared_ptr<workplane> operator[](const std::pair<int, int> &range);

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

  std::shared_ptr<workplane>
  invoke(const boost::variant<
         std::function<std::shared_ptr<workplane>(workplane &)>,
         std::function<void(workplane &)>, std::function<void()>> &func);

  workplane &export_to(const std::string &path);

  std::vector<std::shared_ptr<workplane>> all();
  std::vector<shape> shapes() const;
  std::vector<shape_object> vals() const;
  shape_object val() const;
  size_t size() const;
  bool has_parent() const;
  std::shared_ptr<workplane> parent() const;
  bool has_error() const;
  const std::string &error() const;
  std::shared_ptr<context> ctx() const;

protected:
  std::vector<shape_object> _objects;
  std::shared_ptr<context> _ctx;
  std::weak_ptr<workplane> _parent;
  std::shared_ptr<topo_plane> _plane;
  boost::optional<std::string> _tag;

private:
  friend class assembly;

  static constexpr double TOL = 1e-6;

  std::shared_ptr<workplane>
  _extrude(boost::variant<double, face_index_type, face> until,
           const combine_mode &combine, bool clean, bool both,
           boost::optional<double> taper);

  std::shared_ptr<workplane> _sweep(
      boost::variant<std::reference_wrapper<workplane>, topo::wire, edge> path,
      bool multisection, bool makeSolid, bool isFrenet, bool combine,
      bool clean, const transition_mode &transition,
      const boost::optional<topo_vector> &normal,
      const std::shared_ptr<workplane> &auxSpine);

  std::shared_ptr<workplane> _union_(
      boost::variant<std::reference_wrapper<const workplane>, solid, compound>
          toUnion,
      bool clean = true, bool glue = false,
      const boost::optional<double> &tol = boost::none);

  std::shared_ptr<workplane>
  _cut(boost::variant<std::reference_wrapper<const workplane>, solid, compound>
           toCut,
       bool clean, const boost::optional<double> &tol);

  std::shared_ptr<workplane> _intersect(
      boost::variant<std::reference_wrapper<const workplane>, solid, compound>
          toIntersect,
      bool clean, const boost::optional<double> &tol);

  std::shared_ptr<workplane>
  _cut_blind(boost::variant<double, face_index_type, face> until, bool clean,
             bool both, const boost::optional<double> &taper);

  std::shared_ptr<workplane>
  _interp_plate(boost::variant<std::vector<gp_Pnt>, std::vector<edge>,
                               std::reference_wrapper<const workplane>>
                    surf_edges,
                const std::vector<gp_Pnt> &surf_pts, double thickness,
                bool combine, bool clean, int degree, int nbPtsOnCur,
                int nbIter, bool anisotropy, double tol2d, double tol3d,
                double tolAng, double tolCurv, int maxDeg, int maxSegments);

  std::shared_ptr<workplane> _box(
      double length, double width, double height,
      const boost::variant<bool, std::tuple<bool, bool, bool>> &centered = true,
      bool combine = true, bool clean = true);

  std::shared_ptr<workplane> _sphere(
      double radius, const gp_Vec &direct = gp_Vec(0, 0, 1),
      double angle1 = -90, double angle2 = 90, double angle3 = 360,
      const boost::variant<bool, std::tuple<bool, bool, bool>> &centered = true,
      bool combine = true, bool clean = true);

  std::shared_ptr<workplane> _cylinder(
      double height, double radius, const gp_Vec &direct = gp_Vec(0, 0, 1),
      double angle = 360,
      const boost::variant<bool, std::tuple<bool, bool, bool>> &centered = true,
      bool combine = true, bool clean = true);

  std::shared_ptr<workplane> _wedge(
      double dx, double dy, double dz, double xmin, double zmin, double xmax,
      double zmax, const gp_Pnt &pnt = gp_Pnt(0, 0, 0),
      const gp_Vec &dir = gp_Vec(0, 0, 1),
      const boost::variant<bool, std::tuple<bool, bool, bool>> &centered = true,
      bool combine = true, bool clean = true);

  std::shared_ptr<workplane>
  _rect(double xLen, double yLen,
        const boost::variant<bool, std::tuple<bool, bool>> &centered = {},
        bool forConstruction = false);

  std::shared_ptr<workplane> _eachpoint(
      const boost::variant<shape, std::reference_wrapper<const workplane>,
                           std::function<shape(topo_location)>> &arg,
      bool useLocalCoordinates = false, bool combine = false,
      bool clean = true);

  std::shared_ptr<workplane>
  _mirror(const boost::variant<std::string, gp_Vec, face,
                               std::reference_wrapper<const workplane>>
              &mirrorPlane,
          const boost::optional<gp_Pnt> &basePointVector, bool unionResult);

  std::shared_ptr<workplane>
  _rarray(double xSpacing, double ySpacing, int xCount, int yCount,
          const boost::variant<bool, std::tuple<bool, bool>> &center);

  std::shared_ptr<workplane>
  _vertices(const boost::optional<boost::variant<selector_ptr, std::string>>
                &selector = boost::none,
            const boost::optional<std::string> &tag = boost::none) const;
  std::shared_ptr<workplane>
  _faces(const boost::optional<boost::variant<selector_ptr, std::string>>
             &selector = boost::none,
         const boost::optional<std::string> &tag = boost::none) const;
  std::shared_ptr<workplane>
  _edges(const boost::optional<boost::variant<selector_ptr, std::string>>
             &selector = boost::none,
         const boost::optional<std::string> &tag = boost::none) const;

  std::shared_ptr<workplane>
  _wires(const boost::optional<boost::variant<selector_ptr, std::string>>
             &selector = boost::none,
         const boost::optional<std::string> &tag = boost::none) const;

  std::shared_ptr<workplane>
  _solids(const boost::optional<boost::variant<selector_ptr, std::string>>
              &selector = boost::none,
          const boost::optional<std::string> &tag = boost::none) const;

  std::shared_ptr<workplane>
  _shells(const boost::optional<boost::variant<selector_ptr, std::string>>
              &selector = boost::none,
          const boost::optional<std::string> &tag = boost::none) const;

  std::shared_ptr<workplane>
  _compounds(const boost::optional<boost::variant<selector_ptr, std::string>>
                 &selector = boost::none,
             const boost::optional<std::string> &tag = boost::none) const;

  gp_Vec plane_string_to_normal(const std::string &planeStr);
  shape find_type(const std::vector<shape_object_type> &types, bool searchStack,
                  bool searchParents) const;
  std::shared_ptr<workplane> select_objects(
      const shape_object_type &objType,
      const boost::optional<
          boost::variant<std::shared_ptr<selector>, std::string>> &selector,
      const boost::optional<std::string> &tag) const;
  std::vector<shape>
  filter(const std::vector<shape> &objs,
         const boost::optional<boost::variant<std::shared_ptr<selector>,
                                              std::string>> &selector) const;
  gp_Pnt find_from_point(bool useLocalCoords = false);
  edge find_from_edge(bool useLocalCoords = false);

  std::vector<face> get_faces();
  std::vector<shape> get_faces_vertices();
  bool are_faces_coplanar(const std::vector<face> &faces) const;
  shape
  _extrude(const boost::optional<double> &distance, bool both = false,
           const boost::optional<double> &taper = boost::none,
           boost::optional<boost::variant<int, face>> upToFace = boost::none,
           bool additive = true);
  std::vector<face>
  _get_intersected_faces(const face &face, const gp_Vec &eDir,
                         const flywave::topo::intersection_direction &direction,
                         bool both);
  shape _revolve(double angleDegrees, const gp_Pnt &axisStart,
                 const gp_Pnt &axisEnd);
  shape _sweep(
      boost::variant<std::shared_ptr<workplane>, topo::wire, topo::edge> &path,
      bool multisection, bool makeSolid, bool isFrenet,
      const transition_mode &transition,
      const boost::optional<topo_vector> &normal,
      const std::shared_ptr<workplane> &auxSpine);
  gp_Vec compute_x_dir(const gp_Vec &normal) const;
  std::vector<shape> collect_property(const shape_object_type &propName) const;
  std::shared_ptr<workplane>
  combine_with_base(const boost::variant<shape, std::vector<shape>> &obj,
                    const combine_mode &mode = true, bool clean = false);
  shape fuse_with_base(const shape &obj);
  shape cut_from_base(const shape &obj);
  std::shared_ptr<workplane> get_tagged(const std::string &name) const;
  workplane &merge_tags(const workplane &other);
  void add_pending_edge(const edge &e);
  void add_pending_wire(const topo::wire &w);
  std::vector<topo::wire> _consolidate_wires();
  std::vector<topo_location> locs();
  void add_error(const std::string &error);
};

} // namespace topo
} // namespace flywave

namespace std {
template <> struct hash<flywave::topo::shape_object> {
  size_t operator()(const flywave::topo::shape_object &obj) const {
    size_t seed = 0;
    struct hasher : public boost::static_visitor<> {
      hasher(size_t &seed) : seed_(seed) {}

      void operator()(const flywave::topo::shape &value) const {
        boost::hash_combine(seed_, value.hash_code());
      }

      void operator()(const flywave::topo::topo_vector &value) const {
        boost::hash_combine(seed_, value.x());
        boost::hash_combine(seed_, value.y());
        boost::hash_combine(seed_, value.z());
      }

      void operator()(const flywave::topo::topo_location &value) const {
        boost::hash_combine(seed_, value.hash_code());
      }

      void
      operator()(const std::shared_ptr<flywave::topo::sketch> &value) const {
        if (value) {
          boost::hash_combine(seed_, value->hash_code());
        } else {
          boost::hash_combine(seed_, 0);
        }
      }

      void operator()(const boost::blank &) const {
        boost::hash_combine(seed_, 0);
      }

      size_t &seed_;
    };

    boost::apply_visitor(hasher(seed), obj);
    return seed;
  }
};
} // namespace std