#ifndef __FLYWAVE_MESH_TOPO_WIRE_HH__
#define __FLYWAVE_MESH_TOPO_WIRE_HH__

#include <BRepAdaptor_CompCurve.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <GeomAbs_JoinType.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>

#include <boost/variant.hpp>

#include "shape1d.hh"

namespace flywave {
namespace topo {

class edge;
class face;
class vertex;
class wire_iterator;

class wire : public shape1d {
public:
  wire() = default;
  virtual ~wire() = default;

  static wire make_polygon();

  static wire make_polygon(const gp_Pnt &P1, const gp_Pnt &P2);

  static wire make_polygon(const gp_Pnt &P1, const gp_Pnt &P2, const gp_Pnt &P3,
                           const bool close = false);

  static wire make_polygon(const gp_Pnt &P1, const gp_Pnt &P2, const gp_Pnt &P3,
                           const gp_Pnt &P4, const bool close = false);

  static wire make_polygon(const vertex &V1, const vertex &V2);

  static wire make_polygon(const vertex &V1, const vertex &V2, const vertex &V3,
                           const bool close = false);

  static wire make_polygon(const vertex &V1, const vertex &V2, const vertex &V3,
                           const vertex &V4, const bool close = false);

  static wire make_polygon(const std::vector<gp_Pnt> &vertices,
                           bool close = false, bool forConstruction = false);

  static wire make_wire(const edge &E);
  static wire make_wire(const edge &E1, const edge &E2);

  static wire make_wire(const edge &E1, const edge &E2, const edge &E3);

  static wire make_wire(const edge &E1, const edge &E2, const edge &E3,
                        const edge &E4);
  static wire make_wire(const wire &W);

  static wire make_wire(const wire &W, const edge &E);

  static wire make_wire(std::vector<edge> &edges);

  static wire make_wire(std::initializer_list<edge> edges);

  static wire make_wire(std::vector<wire> &wires);

  static wire make_wire(std::initializer_list<wire> wires);

  static wire make_rect(double width, double height);

  static wire make_circle(double radius, const gp_Pnt &center,
                          const gp_Dir &normal);

  static wire make_ellipse(double x_radius, double y_radius,
                           const gp_Pnt &center, const gp_Dir &normal,
                           const gp_Dir &xDir, double angle1 = 360.0,
                           double angle2 = 360.0, double rotation_angle = 0.0,
                           bool closed = true);

  static wire make_helix(double pitch, double height, double radius,
                         const gp_Pnt &center = gp_Pnt(0, 0, 0),
                         const gp_Dir &dir = gp_Dir(0, 0, 1),
                         double angle = 360.0, bool lefthand = false);

  static std::vector<wire> combine(std::vector<shape> &wires,
                                   double tol = 1e-9);
  enum class curve_type {
    line,
    three_point_arc,
    circle_center_arc,
    spline,
  };

  static wire make_wire(const std::vector<std::vector<gp_Pnt>> &points,
                        const std::vector<curve_type> &curveTypes);

  wire stitch(const wire &other) const;

  int num_edges() const override;

  std::vector<vertex> vertices() const override;

  double length() const;

  void convert_to_curves3d();

  int project(const face &f);

  int offset(double distance, const GeomAbs_JoinType &kind = GeomAbs_Arc);

  int fillet(std::vector<vertex> &vertices, std::vector<double> radius);

  int chamfer(std::vector<vertex> &vertices, std::vector<double> distances);

  std::vector<wire> offset2d(double distances,
                             const GeomAbs_JoinType &kind = GeomAbs_Arc) const;

  wire fillet2d(double radius, const std::vector<vertex> &vertices) const;

  wire chamfer2d(double distances, const std::vector<vertex> &vertices) const;

  TopoDS_Wire &value();
  const TopoDS_Wire &value() const;

  virtual geometry_object_type type() const override {
    return geometry_object_type::WireType;
  }

  virtual shape copy(bool deep = true) const override;

  wire(TopoDS_Shape shp, bool forConstruction = false)
      : shape1d(shp, forConstruction) {}
  wire(const shape &v, TopoDS_Shape shp) : shape1d(v, shp) {}

  virtual Handle(Adaptor3d_Curve) get_geom() const override;

  wire close() const;

protected:
  friend class wire_iterator;
  friend class shape;
};

class wire_iterator {
public:
  TopExp_Explorer ex;
  wire_iterator(shape &arg) : ex(arg.value(), TopAbs_WIRE) {}
  void reset() { ex.ReInit(); }
  boost::optional<wire> next() {
    if (ex.More()) {
      wire ret{ex.Current()};
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

template <> struct hash<flywave::topo::wire> {
  size_t operator()(const flywave::topo::wire &v) const {
    return v.hash_code();
  }
};

} // namespace std
#endif // __FLYWAVE_MESH_TOPO_WIRE_HH__
