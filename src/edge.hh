#ifndef __FLYWAVE_MESH_TOPO_EDGE_HH__
#define __FLYWAVE_MESH_TOPO_EDGE_HH__

#include <BRepAdaptor_Curve.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Surface.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Edge.hxx>
#include <gp_Circ.hxx>
#include <gp_Circ2d.hxx>
#include <gp_Dir.hxx>
#include <gp_Elips.hxx>
#include <gp_Elips2d.hxx>
#include <gp_Hypr.hxx>
#include <gp_Hypr2d.hxx>
#include <gp_Lin2d.hxx>
#include <gp_Parab.hxx>
#include <gp_Parab2d.hxx>

#include "shape1d.hh"

namespace flywave {
namespace topo {

class vertex;
class face;
class wire;

class edge : public shape1d {
public:
  edge() = default;
  virtual ~edge() = default;

  static edge make_edge(const vertex &V1, const vertex &V2);

  static edge make_edge(const gp_Pnt &P1, const gp_Pnt &P2);

  static edge make_edge(const gp_Lin &L);

  static edge make_edge(const gp_Lin &L, const Standard_Real p1,
                        const Standard_Real p2);

  static edge make_edge(const gp_Lin &L, const gp_Pnt &P1, const gp_Pnt &P2);

  static edge make_edge(const gp_Lin &L, const vertex &V1, const vertex &V2);

  static edge make_edge(const gp_Circ &L);

  static edge make_edge(const gp_Circ &L, const Standard_Real p1,
                        const Standard_Real p2);

  static edge make_edge(const gp_Circ &L, const gp_Pnt &P1, const gp_Pnt &P2);

  static edge make_edge(const gp_Circ &L, const vertex &V1, const vertex &V2);

  static edge make_edge(const gp_Elips &L);

  static edge make_edge(const gp_Elips &L, const Standard_Real p1,
                        const Standard_Real p2);

  static edge make_edge(const gp_Elips &L, const gp_Pnt &P1, const gp_Pnt &P2);

  static edge make_edge(const gp_Elips &L, const vertex &V1, const vertex &V2);

  static edge make_edge(const gp_Hypr &L);

  static edge make_edge(const gp_Hypr &L, const Standard_Real p1,
                        const Standard_Real p2);

  static edge make_edge(const gp_Hypr &L, const gp_Pnt &P1, const gp_Pnt &P2);

  static edge make_edge(const gp_Hypr &L, const vertex &V1, const vertex &V2);

  static edge make_edge(const gp_Parab &L);

  static edge make_edge(const gp_Parab &L, const Standard_Real p1,
                        const Standard_Real p2);

  static edge make_edge(const gp_Parab &L, const gp_Pnt &P1, const gp_Pnt &P2);

  static edge make_edge(const gp_Parab &L, const vertex &V1, const vertex &V2);

  static edge make_edge(const Handle(Geom_Curve) & L);

  static edge make_edge(const Handle(Geom_Curve) & L, const Standard_Real p1,
                        const Standard_Real p2);

  static edge make_edge(const Handle(Geom_Curve) & L, const gp_Pnt &P1,
                        const gp_Pnt &P2);

  static edge make_edge(const Handle(Geom_Curve) & L, const vertex &V1,
                        const vertex &V2);

  static edge make_edge(const Handle(Geom_Curve) & L, const gp_Pnt &P1,
                        const gp_Pnt &P2, const Standard_Real p1,
                        const Standard_Real p2);

  static edge make_edge(const Handle(Geom_Curve) & L, const vertex &V1,
                        const vertex &V2, const Standard_Real p1,
                        const Standard_Real p2);

  static edge make_edge(const Handle(Geom2d_Curve) & L,
                        const Handle(Geom_Surface) & S);

  static edge make_edge(const Handle(Geom2d_Curve) & L,
                        const Handle(Geom_Surface) & S, const Standard_Real p1,
                        const Standard_Real p2);

  static edge make_edge(const Handle(Geom2d_Curve) & L,
                        const Handle(Geom_Surface) & S, const gp_Pnt &P1,
                        const gp_Pnt &P2);

  static edge make_edge(const Handle(Geom2d_Curve) & L,
                        const Handle(Geom_Surface) & S, const vertex &V1,
                        const vertex &V2);

  static edge make_edge(const Handle(Geom2d_Curve) & L,
                        const Handle(Geom_Surface) & S, const gp_Pnt &P1,
                        const gp_Pnt &P2, const Standard_Real p1,
                        const Standard_Real p2);

  static edge make_edge(const Handle(Geom2d_Curve) & L,
                        const Handle(Geom_Surface) & S, const vertex &V1,
                        const vertex &V2, const Standard_Real p1,
                        const Standard_Real p2);

  static edge make_edge2d(const vertex &V1, const vertex &V2);

  static edge make_edge2d(const gp_Pnt2d &P1, const gp_Pnt2d &P2);

  static edge make_edge2d(const gp_Lin2d &L);

  static edge make_edge2d(const gp_Lin2d &L, const Standard_Real p1,
                          const Standard_Real p2);

  static edge make_edge2d(const gp_Lin2d &L, const gp_Pnt2d &P1,
                          const gp_Pnt2d &P2);

  static edge make_edge2d(const gp_Lin2d &L, const vertex &V1,
                          const vertex &V2);

  static edge make_edge2d(const gp_Circ2d &L);

  static edge make_edge2d(const gp_Circ2d &L, const Standard_Real p1,
                          const Standard_Real p2);

  static edge make_edge2d(const gp_Circ2d &L, const gp_Pnt2d &P1,
                          const gp_Pnt2d &P2);

  static edge make_edge2d(const gp_Circ2d &L, const vertex &V1,
                          const vertex &V2);

  static edge make_edge2d(const gp_Elips2d &L);

  static edge make_edge2d(const gp_Elips2d &L, const Standard_Real p1,
                          const Standard_Real p2);

  static edge make_edge2d(const gp_Elips2d &L, const gp_Pnt2d &P1,
                          const gp_Pnt2d &P2);

  static edge make_edge2d(const gp_Elips2d &L, const vertex &V1,
                          const vertex &V2);

  static edge make_edge2d(const gp_Hypr2d &L);

  static edge make_edge2d(const gp_Hypr2d &L, const Standard_Real p1,
                          const Standard_Real p2);

  static edge make_edge2d(const gp_Hypr2d &L, const gp_Pnt2d &P1,
                          const gp_Pnt2d &P2);

  static edge make_edge2d(const gp_Hypr2d &L, const vertex &V1,
                          const vertex &V2);

  static edge make_edge2d(const gp_Parab2d &L);

  static edge make_edge2d(const gp_Parab2d &L, const Standard_Real p1,
                          const Standard_Real p2);

  static edge make_edge2d(const gp_Parab2d &L, const gp_Pnt2d &P1,
                          const gp_Pnt2d &P2);

  static edge make_edge2d(const gp_Parab2d &L, const vertex &V1,
                          const vertex &V2);

  static edge make_edge2d(const Handle(Geom2d_Curve) & L);

  static edge make_edge2d(const Handle(Geom2d_Curve) & L,
                          const Standard_Real p1, const Standard_Real p2);

  static edge make_edge2d(const Handle(Geom2d_Curve) & L, const gp_Pnt2d &P1,
                          const gp_Pnt2d &P2);

  static edge make_edge2d(const Handle(Geom2d_Curve) & L, const vertex &V1,
                          const vertex &V2);

  static edge make_edge2d(const Handle(Geom2d_Curve) & L, const gp_Pnt2d &P1,
                          const gp_Pnt2d &P2, const Standard_Real p1,
                          const Standard_Real p2);

  static edge make_edge2d(const Handle(Geom2d_Curve) & L, const vertex &V1,
                          const vertex &V2, const Standard_Real p1,
                          const Standard_Real p2);

  static edge make_polygon();

  static edge make_polygon(const gp_Pnt &P1, const gp_Pnt &P2);

  static edge make_polygon(const gp_Pnt &P1, const gp_Pnt &P2, const gp_Pnt &P3,
                           const bool Close = false);

  static edge make_polygon(const gp_Pnt &P1, const gp_Pnt &P2, const gp_Pnt &P3,
                           const gp_Pnt &P4, const bool Close = false);

  static edge make_polygon(const vertex &V1, const vertex &V2);

  static edge make_polygon(const vertex &V1, const vertex &V2, const vertex &V3,
                           const bool Close = false);

  static edge make_polygon(const vertex &V1, const vertex &V2, const vertex &V3,
                           const vertex &V4, const bool Close = false);

  static edge make_polygon(std::vector<vertex> &vertexs,
                           const bool Close = false);

  static edge make_polygon(std::initializer_list<vertex> vertexs,
                           const bool Close = false);

  static edge make_polygon(std::vector<gp_Pnt> &vertexs,
                           const bool Close = false);

  static edge make_polygon(std::initializer_list<gp_Pnt> vertexs,
                           const bool Close = false);

  static edge make_rect(double width, double height);

  static edge make_spline(const std::vector<gp_Pnt> &points, double tol = 1e-6,
                          bool periodic = false);

  static edge make_spline(const std::vector<gp_Pnt> &points,
                          const std::pair<gp_Vec, gp_Vec> *tangents,
                          const std::vector<double> *parameters,
                          double tol = 1e-6, bool periodic = false,
                          bool scale = true);

  static edge make_spline(const std::vector<gp_Pnt> &points,
                          const std::vector<gp_Vec> *tangents = nullptr,
                          bool periodic = false,
                          const std::vector<double> *parameters = nullptr,
                          bool scale = true, double tol = 1e-6);

  static edge make_spline_approx(
      const std::vector<gp_Pnt> &points, double tolerance = 1e-3,
      const boost::optional<std::tuple<double, double, double>> &smoothing =
          boost::none,
      int minDegree = 1, int maxDegree = 6);

  static edge make_circle(double radius, const gp_Pnt &center = gp_Pnt(0, 0, 0),
                          const gp_Dir &normal = gp_Dir(0, 0, 1),
                          double angle1 = 360.0, double angle2 = 360.0,
                          bool orientation = true);

  static edge make_ellipse(double majorRadius, double minorRadius,
                           const gp_Pnt &center = gp_Pnt(0, 0, 0),
                           const gp_Dir &normal = gp_Dir(0, 0, 1),
                           const gp_Dir &xnormal = gp_Dir(1, 0, 0),
                           double angle1 = 360.0, double angle2 = 360.0,
                           int sense = 1);

  static edge make_three_point_arc(const gp_Pnt &v1, const gp_Pnt &v2,
                                   const gp_Pnt &v3);

  static edge make_tangent_arc(const gp_Pnt &v1, const gp_Vec &tangent,
                               const gp_Pnt &v3);

  static edge make_bezier(const std::vector<gp_Pnt> &points);

  TopoDS_Edge &value();
  const TopoDS_Edge &value() const;

  bool is_seam(const face &f) const;

  bool is_degenerated() const;

  bool is_closed() const;

  bool is_inifinite() const;

  double length() const;

  float tolerance() const;

  bool is_curve3d() const;

  void convert_to_curve3d();

  void reverse();

  virtual Handle(Adaptor3d_Curve) get_geom() const override;

  virtual geometry_object_type type() const override {
    return geometry_object_type::EdgeType;
  }

  virtual shape copy(bool deep = true) const override;

  edge(TopoDS_Shape shp, bool forConstruction = false)
      : shape1d(shp, forConstruction) {}
  edge(const shape &e, TopoDS_Shape shp) : shape1d(e, shp) {}

  boost::variant<wire, edge> close() const;

  gp_Pnt arc_center() const;

  edge trim(double u0, double u1) const;

protected:
  friend class edge_iterator;
  friend class shape;
};

class edge_iterator {
public:
  TopExp_Explorer ex;
  edge_iterator(shape &arg) : ex(arg.value(), TopAbs_EDGE) {}
  void reset() { ex.ReInit(); }
  boost::optional<edge> next() {
    if (ex.More()) {
      edge ret{ex.Current()};
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

template <> struct hash<flywave::topo::edge> {
  size_t operator()(const flywave::topo::edge &v) const {
    return v.hash_code();
  }
};

} // namespace std
#endif // __FLYWAVE_MESH_TOPO_EDGE_HH__
