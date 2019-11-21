#ifndef __FLYWAVE_MESH_TOPO_WIRE_HH__
#define __FLYWAVE_MESH_TOPO_WIRE_HH__

#include <TopExp_Explorer.hxx>
#include <TopoDS_Wire.hxx>

#include "shape.hh"

namespace flywave {
namespace topo {

class edge;
class face;
class vertex;
class wire_iterator;

class wire : public shape {
public:
  wire() = default;
  virtual ~wire() = default;

  static wire make_polygon();

  static wire make_polygon(const gp_Pnt &P1, const gp_Pnt &P2);

  static wire make_polygon(const gp_Pnt &P1, const gp_Pnt &P2, const gp_Pnt &P3,
                           const bool Close = false);

  static wire make_polygon(const gp_Pnt &P1, const gp_Pnt &P2, const gp_Pnt &P3,
                           const gp_Pnt &P4, const bool Close = false);

  static wire make_polygon(const vertex &V1, const vertex &V2);

  static wire make_polygon(const vertex &V1, const vertex &V2, const vertex &V3,
                           const bool Close = false);

  static wire make_polygon(const vertex &V1, const vertex &V2, const vertex &V3,
                           const vertex &V4, const bool Close = false);

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

  int num_vertices() const;

  int num_edges() const;

  bool is_closed() const;

  double length() const;

  void convert_to_curves3d();

  int project(const face &f);

  int offset(double distance, int joinType);

  int fillet(std::vector<vertex> &vertices, std::vector<double> radius);

  int chamfer(std::vector<vertex> &vertices, std::vector<double> distances);

  TopoDS_Wire &value();
  const TopoDS_Wire &value() const;

  virtual geometry_object_type type() const override {
    return geometry_object_type::WireType;
  }

  virtual shape copy(bool deep = true) const override;

  wire(TopoDS_Shape shp) : shape(shp) {}

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

#endif // __FLYWAVE_MESH_TOPO_WIRE_HH__
