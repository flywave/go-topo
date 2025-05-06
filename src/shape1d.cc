#include <BRepAdaptor_Curve.hxx>
#include <BRepBuilderAPI_Copy.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepExtrema_DistShapeShape.hxx>
#include <BRepFilletAPI_MakeFillet2d.hxx>
#include <BRepGProp.hxx>
#include <BRepLib.hxx>
#include <BRepLib_FindSurface.hxx>
#include <BRepOffsetAPI_MakeOffset.hxx>
#include <BRepOffsetAPI_NormalProjection.hxx>
#include <BRepProj_Projection.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <BRep_Tool.hxx>
#include <GCPnts_AbscissaPoint.hxx>
#include <GCPnts_QuasiUniformAbscissa.hxx>
#include <GCPnts_QuasiUniformDeflection.hxx>
#include <GProp_GProps.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <GeomConvert_ApproxCurve.hxx>
#include <GeomFill_CorrectedFrenet.hxx>
#include <GeomFill_Frenet.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Plane.hxx>
#include <LProp3d_CLProps.hxx>
#include <Precision.hxx>
#include <ShapeAnalysis_FreeBounds.hxx>
#include <TopExp.hxx>
#include <TopLoc_Location.hxx>
#include <TopTools_HSequenceOfShape.hxx>
#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopoDS.hxx>
#include <gp_Ax3.hxx>
#include <gp_Dir.hxx>
#include <gp_Pln.hxx>
#include <gp_Trsf.hxx>

#include "edge.hh"
#include "face.hh"
#include "shape1d.hh"
#include "vertex.hh"
#include "wire.hh"

namespace flywave {
namespace topo {
namespace {

gp_Dir find_plane_normal(const TopoDS_Shape &shape) {
  if (shape.IsNull()) {
    throw std::invalid_argument("Input shape is null");
  }

  BRepLib_FindSurface finder(shape, true, true);
  if (!finder.Found()) {
    throw std::runtime_error("No supporting plane found");
  }

  Handle(Geom_Surface) surface = finder.Surface();
  Handle(Geom_Plane) plane = Handle(Geom_Plane)::DownCast(surface);
  if (plane.IsNull()) {
    throw std::runtime_error("Supporting surface is not a plane");
  }

  return plane->Pln().Axis().Direction();
}

bool is_planar(const TopoDS_Shape &shape) {
  if (shape.IsNull()) {
    return false;
  }

  BRepLib_FindSurface finder(shape, true, true);
  if (!finder.Found()) {
    return false;
  }

  return !Handle(Geom_Plane)::DownCast(finder.Surface()).IsNull();
}
} // namespace

Handle(Geom_Curve) shape1d::get_curve() const {
  if (this->is_null()) {
    throw std::invalid_argument("Input shape is null");
  }
  auto curve = this->get_geom();
  if (curve->DynamicType() == STANDARD_TYPE(Geom_Curve)) {
    return Handle(Geom_Curve)::DownCast(curve);
  } else {
    return this->approx_curve();
  }
}

Handle(Geom_Curve) shape1d::approx_curve(double tolerance,
                                         GeomAbs_Shape continuity,
                                         int maxSegments, int maxDegree) const {
  if (this->is_null()) {
    throw std::invalid_argument("Input shape is null");
  }
  GeomConvert_ApproxCurve approx(this->get_geom(), tolerance, continuity,
                                 maxSegments, maxDegree);
  return approx.Curve();
}

gp_Pnt shape1d::start_point() const {
  if (this->is_null()) {
    throw std::invalid_argument("Input shape is null");
  }
  Handle(Geom_Curve) curve = this->get_curve();
  if (curve.IsNull()) {
    throw std::runtime_error("Failed to get curve from shape");
  }
  double umin = curve->FirstParameter();
  return curve->Value(umin);
}

gp_Pnt shape1d::end_point() const {
  if (this->is_null()) {
    throw std::invalid_argument("Input shape is null");
  }
  Handle(Geom_Curve) curve = this->get_curve();
  if (curve.IsNull()) {
    throw std::runtime_error("Failed to get curve from shape");
  }
  double umax = curve->LastParameter();
  return curve->Value(umax);
}

double shape1d::param_at(double d) const {
  if (d < 0.0 || d > 1.0) {
    throw std::invalid_argument("Distance must be in [0, 1] range");
  }

  auto curve = this->get_geom();
  double length = GCPnts_AbscissaPoint::Length(*curve);
  return GCPnts_AbscissaPoint(*curve, length * d, curve->FirstParameter())
      .Parameter();
}

double shape1d::param_at(gp_Pnt point) const {
  auto curve = this->get_geom();

  Handle_Geom_Curve _curve;

  if (curve->DynamicType() == STANDARD_TYPE(BRepAdaptor_Curve)) {
    _curve = Handle(BRepAdaptor_Curve)::DownCast(curve)->Curve().Curve();
  } else {
    _curve = this->approx_curve();
  }

  GeomAPI_ProjectPointOnCurve projector(point, _curve, curve->FirstParameter(),
                                        curve->LastParameter());

  if (projector.NbPoints() == 0) {
    throw std::runtime_error("Projection failed");
  }

  return projector.LowerDistanceParameter();
}

std::vector<double> shape1d::params(const std::vector<gp_Pnt> &points,
                                    double tol) const {
  if (points.empty()) {
    throw std::invalid_argument("Point list is empty");
  }

  auto curve = this->get_geom();

  std::vector<double> parameters;
  parameters.reserve(points.size());

  Handle_Geom_Curve _curve;

  if (curve->DynamicType() == STANDARD_TYPE(BRepAdaptor_Curve)) {
    _curve = Handle(BRepAdaptor_Curve)::DownCast(curve)->Curve().Curve();
  } else {
    _curve = this->approx_curve(tol);
  }

  GeomAPI_ProjectPointOnCurve projector;
  projector.Init(_curve, _curve->FirstParameter(), _curve->LastParameter());

  for (const auto &point : points) {
    projector.Perform(point);
    if (projector.NbPoints() == 0) {
      throw std::runtime_error("Projection failed for point");
    }
    parameters.push_back(projector.LowerDistanceParameter());
  }

  return parameters;
}

std::vector<double>
shape1d::params_length(const std::vector<double> &locations) const {
  auto curve = this->get_geom();

  double totalLength = GCPnts_AbscissaPoint::Length(*curve);
  std::vector<double> parameters;
  parameters.reserve(locations.size());

  for (double loc : locations) {
    if (loc < 0.0 || loc > 1.0) {
      throw std::invalid_argument("Location must be in [0, 1] range");
    }
    parameters.push_back(
        GCPnts_AbscissaPoint(*curve, totalLength * loc, curve->FirstParameter())
            .Parameter());
  }

  return parameters;
}

gp_Dir shape1d::tangent_at(double param) const {
  auto curve = this->get_geom();

  gp_Pnt point;
  gp_Vec tangent;
  curve->D1(param, point, tangent);

  if (tangent.Magnitude() < Precision::Confusion()) {
    throw std::runtime_error("Zero tangent vector");
  }

  return gp_Dir(tangent);
}

std::vector<gp_Dir>
shape1d::tangents(const std::vector<double> &parameters) const {
  std::vector<gp_Dir> tangents;
  tangents.reserve(parameters.size());

  for (double param : parameters) {
    tangents.push_back(this->tangent_at(param));
  }

  return tangents;
}

gp_Dir shape1d::normal() const {
  auto curve = this->get_geom();
  switch (curve->GetType()) {
  case GeomAbs_Circle: {
    gp_Circ circ = curve->Circle();
    return circ.Axis().Direction();
  }
  case GeomAbs_Ellipse: {
    gp_Elips ell = curve->Ellipse();
    return ell.Axis().Direction();
  }
  default:
    return find_plane_normal(this->value());
  }
}

gp_Pnt shape1d::center() const {
  if (this->is_null()) {
    throw std::invalid_argument("Input curve is null");
  }

  GProp_GProps props;
  BRepGProp::LinearProperties(this->value(), props);
  return props.CentreOfMass();
}

std::pair<double, double> shape1d::bounds() const {
  auto adapter = this->get_geom();
  double umin = adapter->FirstParameter();
  double umax = adapter->LastParameter();
  return {umin, umax};
}

double shape1d::length() const {
  auto adapter = this->get_geom();
  return GCPnts_AbscissaPoint::Length(*adapter);
}

double shape1d::radius() const {
  auto adapter = this->get_geom();
  try {
    if (adapter->GetType() != GeomAbs_Circle) {
      throw std::runtime_error("Not a circular curve");
    }
    return adapter->Circle().Radius();
  } catch (Standard_Failure &) {
    throw std::runtime_error("Failed to get circle properties");
  }
}

bool shape1d::is_closed() const { return BRep_Tool::IsClosed(this->value()); }

std::pair<Handle_Adaptor3d_Curve, double>
getCurveAndParam(Handle_Adaptor3d_Curve adapter, double d,
                 shape1d::ParamMode mode) {
  double param = d;
  if (mode == shape1d::ParamMode::LENGTH) {
    double length = GCPnts_AbscissaPoint::Length(*adapter);
    param =
        GCPnts_AbscissaPoint(*adapter, length * d, adapter->FirstParameter())
            .Parameter();
  }
  return {adapter, param};
}

gp_Pnt shape1d::position_at(double d, ParamMode mode) const {
  auto adapter = this->get_geom();
  auto pair = getCurveAndParam(adapter, d, mode);
  return pair.first->Value(pair.second);
}

std::vector<gp_Pnt> shape1d::positions(const std::vector<double> &ds,
                                       ParamMode mode) const {
  std::vector<gp_Pnt> points;
  points.reserve(ds.size());

  for (double d : ds) {
    points.push_back(position_at(d, mode));
  }

  return points;
}

std::pair<std::vector<gp_Pnt>, std::vector<double>>
shape1d::sample_uniform(double n) const {
  std::unique_ptr<GCPnts_AbscissaPoint> sampler;
  auto adapter = this->get_geom();

  if (n == floor(n)) {
    int numPoints = static_cast<int>(n);
    bool isClosed = BRep_Tool::IsClosed(this->value());
    GCPnts_QuasiUniformAbscissa uniformSampler(
        *adapter, isClosed ? numPoints + 1 : numPoints);
    if (!uniformSampler.IsDone()) {
      throw std::runtime_error("Uniform sampling failed");
    }

    std::vector<gp_Pnt> points;
    std::vector<double> params;
    int nbPoints = uniformSampler.NbPoints();

    for (int i = 1; i <= nbPoints; ++i) {
      double param = uniformSampler.Parameter(i);
      params.push_back(param);
      points.push_back(adapter->Value(param));
    }

    return {points, params};
  } else {
    GCPnts_QuasiUniformDeflection deflectionSampler(*adapter, n);
    if (!deflectionSampler.IsDone()) {
      throw std::runtime_error("Deflection sampling failed");
    }

    std::vector<gp_Pnt> points;
    std::vector<double> params;
    int nbPoints = deflectionSampler.NbPoints();

    for (int i = 1; i <= nbPoints; ++i) {
      double param = deflectionSampler.Parameter(i);
      params.push_back(param);
      points.push_back(adapter->Value(param));
    }

    return {points, params};
  }
}

topo_location shape1d::location_at(double d, ParamMode mode, FrameMode frame,
                                   bool planar) const {
  auto adapter = this->get_geom();
  auto pair = getCurveAndParam(adapter, d, mode);
  auto curve = pair.first;
  auto param = pair.second;

  Handle(GeomFill_TrihedronLaw) law;
  if (frame == FRENET) {
    law = new GeomFill_Frenet();
  } else {
    law = new GeomFill_CorrectedFrenet();
  }

  law->SetCurve(curve);

  gp_Vec tangent, normal, binormal;
  law->D0(param, tangent, normal, binormal);
  gp_Pnt pnt = curve->Value(param);

  gp_Trsf T;
  if (planar) {
    T.SetTransformation(gp_Ax3(pnt, gp_Dir(0, 0, 1), gp_Dir(normal.XYZ())),
                        gp_Ax3());
  } else {
    T.SetTransformation(
        gp_Ax3(pnt, gp_Dir(tangent.XYZ()), gp_Dir(normal.XYZ())), gp_Ax3());
  }

  return topo_location(TopLoc_Location(T));
}

std::vector<topo_location> shape1d::locations(const std::vector<double> &ds,
                                              ParamMode mode, FrameMode frame,
                                              bool planar) const {
  std::vector<topo_location> result;
  result.reserve(ds.size());
  for (auto d : ds) {
    result.push_back(location_at(d, mode, frame, planar));
  }
  return result;
}

boost::variant<shape, std::vector<shape>>
shape1d::projected(const face &f, const gp_Vec &direction, bool closest) const {
  BRepProj_Projection bldr(this->value(), f.value(), direction);
  TopoDS_Compound compound = bldr.Shape();

  std::vector<TopoDS_Shape> shapes;
  for (TopExp_Explorer exp(compound, TopAbs_EDGE); exp.More(); exp.Next()) {
    shapes.push_back(exp.Current());
  }

  if (closest) {
    BRepExtrema_DistShapeShape dist_calc;
    dist_calc.LoadS1(this->value());

    double min_dist = std::numeric_limits<double>::max();
    shape closest_proj;

    for (const auto &s : shapes) {
      dist_calc.LoadS2(s);
      dist_calc.Perform();
      double dist = dist_calc.Value();

      if (dist < min_dist) {
        min_dist = dist;
        closest_proj = shape(s);
      }
    }

    return closest_proj;
  } else {
    std::vector<shape> projections;
    projections.reserve(shapes.size());
    for (const auto &shape : shapes) {
      projections.emplace_back(shape);
    }
    return projections;
  }
}

double shape1d::curvature_at(double d, ParamMode mode,
                             double resolution) const {
  auto adapter = this->get_geom();
  auto pair = getCurveAndParam(adapter, d, mode);
  auto curve = pair.first;
  auto param = pair.second;

  LProp3d_CLProps props(curve, param, 2, resolution);
  return props.Curvature();
}

std::vector<double> shape1d::curvatures(const std::vector<double> &ds,
                                        ParamMode mode,
                                        double resolution) const {
  std::vector<double> result;
  result.reserve(ds.size());
  for (auto d : ds) {
    result.push_back(curvature_at(d, mode, resolution));
  }
  return result;
}

} // namespace topo
} // namespace flywave
