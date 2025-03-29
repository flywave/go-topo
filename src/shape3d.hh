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

  shape3d(TopoDS_Shape shp) : shape(shp) {}
  shape3d(const shape &v, TopoDS_Shape shp) : shape(v, shp) {}

  std::vector<shell> shells() const;

  shape fillet(double radius, const std::vector<edge> &edgeList) const;

  shape chamfer(double length, const boost::optional<double> &length2,
                const std::vector<edge> &edgeList) const;

  shape shelling(const std::vector<face> &faceList, double thickness,
                   double tolerance = 0.0001,
                   const std::string &kind = "arc") const;

  bool is_inside(const gp_Pnt &point, double tolerance = 1.0e-6) const;

  solid dprism(const std::shared_ptr<face> &basis,
               const std::vector<wire> &profiles,
               const boost::optional<double> &depth = boost::none,
               double taper = 0,
               const std::shared_ptr<face> &upToFace = nullptr,
               bool thruAll = true, bool additive = true) const;

  solid dprism(const std::shared_ptr<face> &basis,
               const std::vector<face> &faces,
               const boost::optional<double> &depth = boost::none,
               double taper = 0,
               const std::shared_ptr<face> &upToFace = nullptr,
               bool thruAll = true, bool additive = true) const;

protected:
  friend class shape;
};

} // namespace topo
} // namespace flywave
#endif // __FLYWAVE_MESH_TOPO_SHAPE3D_HH__
