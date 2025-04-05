#ifndef __FLYWAVE_MESH_TOPO_FACE_HH__
#define __FLYWAVE_MESH_TOPO_FACE_HH__

#include <Geom_Surface.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Face.hxx>
#include <gp_Cone.hxx>
#include <gp_Cylinder.hxx>
#include <gp_Sphere.hxx>
#include <gp_Torus.hxx>
#include <tuple>

#include <boost/variant.hpp>

#include "bool_type.hh"
#include "shape.hh"

namespace flywave {
namespace topo {

class wire;
class solid;
class edge;
class vertex;
class face_iterator;

class face : public shape {
public:
  face() = default;
  virtual ~face() = default;

  static face make_face(const face &F);

  static face make_face(const gp_Pln &P);

  static face make_face(const gp_Cylinder &C);

  static face make_face(const gp_Cone &C);

  static face make_face(const gp_Sphere &S);

  static face make_face(const gp_Torus &C);

  static face make_face(const Handle(Geom_Surface) & S,
                        const Standard_Real TolDegen);

  static face make_face(const gp_Pln &P, const Standard_Real UMin,
                        const Standard_Real UMax, const Standard_Real VMin,
                        const Standard_Real VMax);

  static face make_face(const gp_Cylinder &C, const Standard_Real UMin,
                        const Standard_Real UMax, const Standard_Real VMin,
                        const Standard_Real VMax);

  static face make_face(const gp_Cone &C, const Standard_Real UMin,
                        const Standard_Real UMax, const Standard_Real VMin,
                        const Standard_Real VMax);

  static face make_face(const gp_Sphere &S, const Standard_Real UMin,
                        const Standard_Real UMax, const Standard_Real VMin,
                        const Standard_Real VMax);

  static face make_face(const gp_Torus &C, const Standard_Real UMin,
                        const Standard_Real UMax, const Standard_Real VMin,
                        const Standard_Real VMax);

  static face make_face(const Handle(Geom_Surface) & S,
                        const Standard_Real UMin, const Standard_Real UMax,
                        const Standard_Real VMin, const Standard_Real VMax,
                        const Standard_Real TolDegen);

  static face make_face(const wire &W, const bool OnlyPlane = false);

  static face make_face(const gp_Pln &P, const wire &W,
                        const bool Inside = true);

  static face make_face(const gp_Cylinder &C, const wire &W,
                        const bool Inside = true);

  static face make_face(const gp_Cone &C, const wire &W,
                        const bool Inside = true);

  static face make_face(const gp_Sphere &S, const wire &W,
                        const bool Inside = true);

  static face make_face(const gp_Torus &C, const wire &W,
                        const bool Inside = true);

  static face make_face(const Handle(Geom_Surface) & S, const wire &W,
                        const bool Inside = true);

  static face make_face(const face &F, const wire &W);

  static face make_face(const face &F, const wire &outer,
                        const std::vector<wire> &inners);

  static face make_face(const edge &edge1, const edge &edge2);

  static face make_face(const wire &wire1, const wire &wire2);

  static face make_face(std::vector<wire> &wires);

  static face make_face(std::initializer_list<wire> wires);

  static face make_face(std::vector<edge> &edges, std::vector<gp_Pnt> points);

  static face make_face(std::vector<gp_Pnt> points);

  static face make_face(std::initializer_list<gp_Pnt> points);

  static face make_face(const wire &outerWire,
                        const std::vector<wire> &innerWires);

  static std::vector<face>
  make_from_wires(const wire &outer, const std::vector<wire> &inners = {});

  static face
  make_face(const std::vector<boost::variant<edge, wire>> &edges,
            const std::vector<boost::variant<edge, wire, gp_Pnt>> &constraints,
            GeomAbs_Shape continuity = GeomAbs_C0, int degree = 3,
            int nbPtsOnCur = 15, int nbIter = 2, bool anisotropy = false,
            double tol2d = 0.00001, double tol3d = 0.0001, double tolAng = 0.01,
            double tolCurv = 0.1, int maxDeg = 8, int maxSegments = 9);

  static face make_plane(const gp_Pnt &basePnt = gp_Pnt(0, 0, 0),
                         const gp_Dir &dir = gp_Dir(0, 0, 1),
                         boost::optional<double> length = boost::none,
                         boost::optional<double> width = boost::none);

  static face make_spline_approx(
      const std::vector<std::vector<gp_Pnt>> &points, double tol = 1e-2,
      const std::tuple<double, double, double> *smoothing = nullptr,
      int minDeg = 1, int maxDeg = 3);

  double area() const;

  float tolerance() const;

  Bnd_Box inertia() const;

  gp_Pnt centre_of_mass() const;

  gp_Pnt center() const;

  gp_Pln to_plane() const;

  std::tuple<double, double, double, double> uv_bounds() const;

  std::pair<double, double> param_at(const gp_Pnt &pt) const;

  std::pair<std::vector<double>, std::vector<double>>
  params(const std::vector<gp_Pnt> &pts, double tol = 1e-9) const;

  gp_Pnt position_at(double u, double v) const;

  std::vector<gp_Pnt>
  positions(const std::vector<std::pair<double, double>> &uvs) const;

  gp_Vec normal_at(const gp_Pnt *locationVector = nullptr) const;

  std::pair<gp_Vec, gp_Pnt> normal_at(double u, double v) const;

  std::pair<std::vector<gp_Vec>, std::vector<gp_Pnt>>
  normals(const std::vector<double> &us, const std::vector<double> &vs) const;

  int offset(double offset, double tolerance = 1e-6);

  int extrude(const shape &shp, gp_Pnt p1, gp_Pnt p2);

  int revolve(const shape &shp, gp_Pnt p1, gp_Pnt p2, double angle);

  int sweep(const wire &spine, std::vector<shape *> profiles, int cornerMode);

  int loft(std::vector<shape> profiles, bool ruled, double tolerance);

  int boolean(const face &tool, bool_op_type op);

  face fillet2d(double radius, const std::vector<vertex> &vertices) const;

  face chamfer2d(double distances, const std::vector<vertex> &vertices) const;

  solid thicken(double thickness) const;

  face project(const face &other, const gp_Vec &direction) const;

  face to_arcs(double tolerance = 1e-3) const;

  face trim(double u0, double u1, double v0, double v1,
            double tol = 1e-6) const;

  edge isoline(double param, const std::string &direction = "v") const;

  std::vector<edge> isolines(const std::vector<double> &params,
                             const std::string &direction = "v") const;

  wire outer_wire() const;

  std::vector<wire> inner_wires() const;

  TopoDS_Face &value();
  const TopoDS_Face &value() const;

  operator Handle(Geom_Surface)() const;

  Handle_Geom_Surface get_geom() const;

  virtual geometry_object_type type() const override {
    return geometry_object_type::FaceType;
  }

  virtual shape copy(bool deep = true) const override;

  face(TopoDS_Shape shp, bool forConstruction = false)
      : shape(shp, forConstruction) {}
  face(const shape &v, TopoDS_Shape shp) : shape(v, shp) {}

protected:
  friend class face_iterator;
  friend class shape;
};

class face_iterator {
public:
  TopExp_Explorer ex;
  face_iterator(shape &arg) : ex(arg.value(), TopAbs_FACE) {}
  void reset() { ex.ReInit(); }
  boost::optional<face> next() {
    if (ex.More()) {
      face ret{ex.Current()};
      ex.Next();
      return {ret};
    } else {
      return boost::none;
    }
  }
};

} // namespace topo
} // namespace flywave

namespace std {

template <> struct hash<flywave::topo::face> {
  size_t operator()(const flywave::topo::face &v) const {
    return v.hash_code();
  }
};

} // namespace std
#endif // __FLYWAVE_MESH_TOPO_FACE_HH__
