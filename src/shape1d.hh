#ifndef __FLYWAVE_MESH_TOPO_SHAPE1D_HH__
#define __FLYWAVE_MESH_TOPO_SHAPE1D_HH__

#include <BRepAdaptor_CompCurve.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>
#include <boost/variant.hpp>

#include "shape.hh"

namespace flywave {
namespace topo {

class face;

class shape1d : public shape {
public:
  shape1d() = default;
  virtual ~shape1d() = default;
  shape1d(const shape1d &) = default;
  shape1d &operator=(const shape1d &) = default;

  shape1d(TopoDS_Shape shp, bool forConstruction = false)
      : shape(shp, forConstruction) {}
  shape1d(const shape &v, TopoDS_Shape shp) : shape(v, shp) {}

  Handle(Geom_Curve) get_curve() const;

  virtual Handle(Adaptor3d_Curve) get_geom() const = 0;

  std::pair<double, double> bounds() const;

  double length() const;

  bool is_closed() const;

  gp_Pnt start_point() const;

  gp_Pnt end_point() const;

  double param_at(double d) const;
  double param_at(gp_Pnt point) const;

  std::vector<double> params(const std::vector<gp_Pnt> &points,
                             double tol = 1e-6) const;

  std::vector<double> params_length(const std::vector<double> &locations) const;

  gp_Dir tangent_at(double param = 0.5) const;

  std::vector<gp_Dir> tangents(const std::vector<double> &parameters) const;

  gp_Dir normal() const;

  gp_Pnt center() const;

  double radius() const;

  typedef enum { LENGTH, PARAM } ParamMode;
  typedef enum { FRENET, CORRECTED_FRENET } FrameMode;

  gp_Pnt position_at(double d, ParamMode mode = LENGTH) const;

  std::vector<gp_Pnt> positions(const std::vector<double> &ds,
                                ParamMode mode = LENGTH) const;

  std::pair<std::vector<gp_Pnt>, std::vector<double>>
  sample_uniform(double n) const;

  topo_location location_at(double d, ParamMode mode = LENGTH,
                            FrameMode frame = FRENET,
                            bool planar = false) const;
  std::vector<topo_location> locations(const std::vector<double> &ds,
                                       ParamMode mode = LENGTH,
                                       FrameMode frame = FRENET,
                                       bool planar = false) const;

  boost::variant<shape, std::vector<shape>>
  projected(const face &f, const gp_Vec &direction, bool closest = true) const;

  double curvature_at(double d, ParamMode mode = LENGTH,
                      double resolution = 1e-6) const;

  std::vector<double> curvatures(const std::vector<double> &ds,
                                 ParamMode mode = LENGTH,
                                 double resolution = 1e-6) const;

protected:
  Handle(Geom_Curve)
      approx_curve(double tolerance = 1e-6,
                   GeomAbs_Shape continuity = GeomAbs_C2, int maxSegments = 100,
                   int maxDegree = 3) const;

  friend class shape;
};

} // namespace topo
} // namespace flywave
#endif // __FLYWAVE_MESH_TOPO_SHAPE1D_HH__
