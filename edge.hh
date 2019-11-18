#ifndef __FLYWAVE_MESH_TOPO_EDGE_HH__
#define __FLYWAVE_MESH_TOPO_EDGE_HH__

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

  static edge make_edge(const vector3<Standard_Real> &P1,
                        const vector3<Standard_Real> &P2);

  static edge make_edge(const line &L);

  static edge make_edge(const line &L, const Standard_Real p1,
                        const Standard_Real p2);

  static edge make_edge(const line &L, const vector3<Standard_Real> &P1,
                        const vector3<Standard_Real> &P2);

  static edge make_edge(const line &L, const vertex &V1, const vertex &V2);

  static edge make_edge(const circ &L);

  static edge make_edge(const circ &L, const Standard_Real p1,
                        const Standard_Real p2);

  static edge make_edge(const circ &L, const vector3<Standard_Real> &P1,
                        const vector3<Standard_Real> &P2);

  static edge make_edge(const circ &L, const vertex &V1, const vertex &V2);

  static edge make_edge(const elips &L);

  static edge make_edge(const elips &L, const Standard_Real p1,
                        const Standard_Real p2);

  static edge make_edge(const elips &L, const vector3<Standard_Real> &P1,
                        const vector3<Standard_Real> &P2);

  static edge make_edge(const elips &L, const vertex &V1, const vertex &V2);

  static edge make_edge(const hyperbola &L);

  static edge make_edge(const hyperbola &L, const Standard_Real p1,
                        const Standard_Real p2);

  static edge make_edge(const hyperbola &L, const vector3<Standard_Real> &P1,
                        const vector3<Standard_Real> &P2);

  static edge make_edge(const hyperbola &L, const vertex &V1, const vertex &V2);

  static edge make_edge(const parabola &L);

  static edge make_edge(const parabola &L, const Standard_Real p1,
                        const Standard_Real p2);

  static edge make_edge(const parabola &L, const vector3<Standard_Real> &P1,
                        const vector3<Standard_Real> &P2);

  static edge make_edge(const parabola &L, const vertex &V1, const vertex &V2);

  static edge make_edge(const geom_curve &L);

  static edge make_edge(const geom_curve &L, const Standard_Real p1,
                        const Standard_Real p2);

  static edge make_edge(const geom_curve &L, const vector3<Standard_Real> &P1,
                        const vector3<Standard_Real> &P2);

  static edge make_edge(const geom_curve &L, const vertex &V1,
                        const vertex &V2);

  static edge make_edge(const geom_curve &L, const vector3<Standard_Real> &P1,
                        const vector3<Standard_Real> &P2,
                        const Standard_Real p1, const Standard_Real p2);

  static edge make_edge(const geom_curve &L, const vertex &V1, const vertex &V2,
                        const Standard_Real p1, const Standard_Real p2);

  static edge make_edge(const geom2d_curve &L, const geom_surface &S);

  static edge make_edge(const geom2d_curve &L, const geom_surface &S,
                        const Standard_Real p1, const Standard_Real p2);

  static edge make_edge(const geom2d_curve &L, const geom_surface &S,
                        const vector3<Standard_Real> &P1,
                        const vector3<Standard_Real> &P2);

  static edge make_edge(const geom2d_curve &L, const geom_surface &S,
                        const vertex &V1, const vertex &V2);

  static edge make_edge(const geom2d_curve &L, const geom_surface &S,
                        const vector3<Standard_Real> &P1,
                        const vector3<Standard_Real> &P2,
                        const Standard_Real p1, const Standard_Real p2);

  static edge make_edge(const geom2d_curve &L, const geom_surface &S,
                        const vertex &V1, const vertex &V2,
                        const Standard_Real p1, const Standard_Real p2);

  static edge make_edge2d(const vertex &V1, const vertex &V2);

  static edge make_edge2d(const vector2<Standard_Real> &P1,
                          const vector2<Standard_Real> &P2);

  static edge make_edge2d(const line2d &L);

  static edge make_edge2d(const line2d &L, const Standard_Real p1,
                          const Standard_Real p2);

  static edge make_edge2d(const line2d &L, const vector2<Standard_Real> &P1,
                          const vector2<Standard_Real> &P2);

  static edge make_edge2d(const line2d &L, const vertex &V1, const vertex &V2);

  static edge make_edge2d(const circ2d &L);

  static edge make_edge2d(const circ2d &L, const Standard_Real p1,
                          const Standard_Real p2);

  static edge make_edge2d(const circ2d &L, const vector2<Standard_Real> &P1,
                          const vector2<Standard_Real> &P2);

  static edge make_edge2d(const circ2d &L, const vertex &V1, const vertex &V2);

  static edge make_edge2d(const elips2d &L);

  static edge make_edge2d(const elips2d &L, const Standard_Real p1,
                          const Standard_Real p2);

  static edge make_edge2d(const elips2d &L, const vector2<Standard_Real> &P1,
                          const vector2<Standard_Real> &P2);

  static edge make_edge2d(const elips2d &L, const vertex &V1, const vertex &V2);

  static edge make_edge2d(const hyperbola2d &L);

  static edge make_edge2d(const hyperbola2d &L, const Standard_Real p1,
                          const Standard_Real p2);

  static edge make_edge2d(const hyperbola2d &L,
                          const vector2<Standard_Real> &P1,
                          const vector2<Standard_Real> &P2);

  static edge make_edge2d(const hyperbola2d &L, const vertex &V1,
                          const vertex &V2);

  static edge make_edge2d(const parabola2d &L);

  static edge make_edge2d(const parabola2d &L, const Standard_Real p1,
                          const Standard_Real p2);

  static edge make_edge2d(const parabola2d &L, const vector2<Standard_Real> &P1,
                          const vector2<Standard_Real> &P2);

  static edge make_edge2d(const parabola2d &L, const vertex &V1,
                          const vertex &V2);

  static edge make_edge2d(const geom2d_curve &L);

  static edge make_edge2d(const geom2d_curve &L, const Standard_Real p1,
                          const Standard_Real p2);

  static edge make_edge2d(const geom2d_curve &L,
                          const vector2<Standard_Real> &P1,
                          const vector2<Standard_Real> &P2);

  static edge make_edge2d(const geom2d_curve &L, const vertex &V1,
                          const vertex &V2);

  static edge make_edge2d(const geom2d_curve &L,
                          const vector2<Standard_Real> &P1,
                          const vector2<Standard_Real> &P2,
                          const Standard_Real p1, const Standard_Real p2);

  static edge make_edge2d(const geom2d_curve &L, const vertex &V1,
                          const vertex &V2, const Standard_Real p1,
                          const Standard_Real p2);

  static edge make_polygon();

  static edge make_polygon(const vector3<Standard_Real> &P1,
                           const vector3<Standard_Real> &P2);

  static edge make_polygon(const vector3<Standard_Real> &P1,
                           const vector3<Standard_Real> &P2,
                           const vector3<Standard_Real> &P3,
                           const bool Close = false);

  static edge make_polygon(const vector3<Standard_Real> &P1,
                           const vector3<Standard_Real> &P2,
                           const vector3<Standard_Real> &P3,
                           const vector3<Standard_Real> &P4,
                           const bool Close = false);

  static edge make_polygon(const vertex &V1, const vertex &V2);

  static edge make_polygon(const vertex &V1, const vertex &V2, const vertex &V3,
                           const bool Close = false);

  static edge make_polygon(const vertex &V1, const vertex &V2, const vertex &V3,
                           const vertex &V4, const bool Close = false);

  static edge make_polygon(std::vector<vertex> &vertexs,
                           const bool Close = false);

  static edge make_polygon(std::initializer_list<vertex> vertexs,
                           const bool Close = false);

  static edge make_polygon(std::vector<vector3<Standard_Real>> &vertexs,
                           const bool Close = false);

  static edge
  make_polygon(std::initializer_list<vector3<Standard_Real>> vertexs,
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
