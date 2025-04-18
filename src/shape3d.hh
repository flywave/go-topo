#ifndef __FLYWAVE_MESH_TOPO_SHAPE3D_HH__
#define __FLYWAVE_MESH_TOPO_SHAPE3D_HH__

#include <BRepAdaptor_CompCurve.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>
#include <boost/optional.hpp>
#include <boost/variant.hpp>
#include <memory>

#include "shape.hh"

namespace flywave {
namespace topo {

class shell;
class edge;
class face;
class wire;
class solid;

class shape3d : public shape {
public:
  shape3d() = default;
  virtual ~shape3d() = default;
  shape3d(const shape3d &) = default;
  shape3d &operator=(const shape3d &) = default;

  shape3d(TopoDS_Shape shp, bool forConstruction = false)
      : shape(shp, forConstruction) {}
  shape3d(const shape &v, TopoDS_Shape shp) : shape(v, shp) {}

  bool is_inside(const gp_Pnt &point, double tolerance = 1.0e-6) const;

protected:
  friend class shape;
};

} // namespace topo
} // namespace flywave
#endif // __FLYWAVE_MESH_TOPO_SHAPE3D_HH__
