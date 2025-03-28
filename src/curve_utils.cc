#include "curve_utils.hh"
#include <Adaptor3d_Curve.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <GeomAbs_CurveType.hxx>
#include <Geom_BSplineCurve.hxx>
#include <stdexcept>
#include <Geom_BezierCurve.hxx>
#include <Geom_OffsetCurve.hxx>
#include <Geom_BSplineCurve.hxx>

namespace flywave {
namespace topo {
namespace curve_utils {

TopoDS_Edge adaptor_curve_to_edge(const Adaptor3d_Curve &crv, double p1,
                                  double p2) {
  const GeomAbs_CurveType t = crv.GetType();
  BRepBuilderAPI_MakeEdge builder;

  switch (t) {
  case GeomAbs_BSplineCurve: {
    Handle(Geom_Curve) spline =
        opencascade::handle<Geom_Curve>::DownCast(crv.BSpline());
    builder = BRepBuilderAPI_MakeEdge(spline, p1, p2);
    break;
  }
  case GeomAbs_BezierCurve: {
    Handle(Geom_Curve) bezier =
        opencascade::handle<Geom_Curve>::DownCast(crv.Bezier());
    builder = BRepBuilderAPI_MakeEdge(bezier, p1, p2);
    break;
  }
  case GeomAbs_Circle:
    builder = BRepBuilderAPI_MakeEdge(crv.Circle(), p1, p2);
    break;
  case GeomAbs_Line:
    builder = BRepBuilderAPI_MakeEdge(crv.Line(), p1, p2);
    break;
  case GeomAbs_Ellipse:
    builder = BRepBuilderAPI_MakeEdge(crv.Ellipse(), p1, p2);
    break;
  case GeomAbs_Hyperbola:
    builder = BRepBuilderAPI_MakeEdge(crv.Hyperbola(), p1, p2);
    break;
  case GeomAbs_Parabola:
    builder = BRepBuilderAPI_MakeEdge(crv.Parabola(), p1, p2);
    break;
  case GeomAbs_OffsetCurve: {
    Handle(Geom_Curve) curve =
        opencascade::handle<Geom_Curve>::DownCast(crv.OffsetCurve());
    builder = BRepBuilderAPI_MakeEdge(curve, p1, p2);
    break;
  }
  default:
    throw std::runtime_error("Unsupported curve type in adaptor");
  }

  if (!builder.IsDone()) {
    throw std::runtime_error("Failed to create edge from adaptor curve");
  }

  return builder.Edge();
}

double curvature_at(const Handle(Adaptor3d_Curve) & curve, double d,
                    const std::string &mode, double resolution) {
  if (curve.IsNull()) {
    throw std::invalid_argument("Curve is null");
  }

  double param = d;
  if (mode == "length") {
    param = curve->FirstParameter() +
            (curve->LastParameter() - curve->FirstParameter()) * d;
  }

  if (param < curve->FirstParameter() || param > curve->LastParameter()) {
    throw std::invalid_argument("Parameter out of curve range");
  }

  LProp3d_CLProps props(curve, param, 2, resolution);
  if (!props.IsTangentDefined()) {
    throw std::runtime_error("Could not compute curve properties");
  }

  return props.Curvature();
}

std::vector<double> curvatures(const Handle(Adaptor3d_Curve) & curve,
                               const std::vector<double> &ds,
                               const std::string &mode, double resolution) {
  std::vector<double> results;
  results.reserve(ds.size());

  for (double d : ds) {
    try {
      results.push_back(curvature_at(curve, d, mode, resolution));
    } catch (const std::exception &e) {
      std::cerr << "Error computing curvature at " << d << ": " << e.what()
                << std::endl;
      results.push_back(std::numeric_limits<double>::quiet_NaN());
    }
  }

  return results;
}

} // namespace curve_utils
} // namespace topo
} // namespace flywave
