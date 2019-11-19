#ifndef __FLYWAVE_MESH_TOPO_EDGE_HH__
#define __FLYWAVE_MESH_TOPO_EDGE_HH__

#include <Geom2d_Curve.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Surface.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Edge.hxx>

#include "shape.hh"

namespace flywave {
namespace topo {

class vertex;
class face;

class edge : public shape {
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

  TopoDS_Edge &value();
  const TopoDS_Edge &value() const;

  bool is_seam(const face &f) const;

  bool is_degenerated() const;

  bool is_closed() const;

  bool is_inifinite() const;

  int num_vertices() const;

  double length() const;

  float tolerance() const;

  bool is_curve3d() const;

  void convert_to_curve3d();

  virtual geometry_object_type type() const override {
    return geometry_object_type::EdgeType;
  }

  virtual shape copy(bool deep = true) const override;

protected:
  friend class edge_iterator;
  friend class shape;

  edge(TopoDS_Shape shp) : shape(shp) {}
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

#endif // __FLYWAVE_MESH_TOPO_EDGE_HH__
