#ifndef __FLYWAVE_MESH_TOPO_VERTEX_HH__
#define __FLYWAVE_MESH_TOPO_VERTEX_HH__

#include <TopExp_Explorer.hxx>
#include <TopoDS_Vertex.hxx>

#include "shape.hh"

namespace flywave {
namespace topo {

class vertex_iterator;

class vertex : public shape {
public:
  vertex() = default;
  vertex(Standard_Real x, Standard_Real y, Standard_Real z);
  vertex(const gp_Pnt &P);

  virtual ~vertex() = default;

  static vertex make_vertex(const gp_Pnt &P);

  TopoDS_Vertex &value();
  const TopoDS_Vertex &value() const;

  operator const gp_Pnt() const;

  virtual geometry_object_type type() const override {
    return geometry_object_type::VertexType;
  }

  virtual shape copy(bool deep = true) const override;

  vertex(TopoDS_Shape shp) : shape(shp) {}

protected:
  friend class vertex_iterator;
  friend class shape;
};

class vertex_iterator {
public:
  TopExp_Explorer ex;
  vertex_iterator(shape &arg) : ex(arg.value(), TopAbs_VERTEX) {}

  void reset() { ex.ReInit(); }

  boost::optional<vertex> next() {
    if (ex.More()) {
      vertex ret{ex.Current()};
      ex.Next();
      return {ret};
    } else {
      return boost::none;
    }
  }
};
} // namespace topo
} // namespace flywave

#endif // __FLYWAVE_MESH_TOPO_VERTEX_HH__
