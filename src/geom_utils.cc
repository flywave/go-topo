#include "geom_utils.hh"
#include "math_utils.hh"

#include <Adaptor3d_Curve.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <GeomAbs_CurveType.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_BezierCurve.hxx>
#include <Geom_OffsetCurve.hxx>
#include <Standard_Version.hxx>
#include <TopLoc_Location.hxx>
#include <gp_Trsf.hxx>
#include <stdexcept>

#include <algorithm>
#include <cmath>
#include <limits>

namespace flywave {
namespace geom_utils {

double normalized_curve(const Adaptor3d_Curve &curve, double u) {
  const double uFirst = curve.FirstParameter();
  const double uLast = curve.LastParameter();
  const std::pair<double, double> uRange = std::minmax(uFirst, uLast);
  return math_utils::mapped_value(u, uRange.first, uRange.second, 0, 1);
}

gp_Pnt d0(const Adaptor3d_Curve &curve, double u) {
  gp_Pnt pnt;
  curve.D0(u, pnt);
  return pnt;
}

gp_Vec d1(const Adaptor3d_Curve &curve, double u) {
  gp_Pnt pnt;
  gp_Vec vec;
  curve.D1(u, pnt, vec);
  return vec;
}

std::pair<gp_Pnt, gp_Vec> d0d1(const Adaptor3d_Curve &curve, double u) {
  gp_Pnt pnt;
  gp_Vec vec;
  curve.D1(u, pnt, vec);
  return {pnt, vec};
}

bool has_scaling(const gp_Trsf &trsf) {
#if OCC_VERSION_HEX >= 0x070600
  const double scalePrec = TopLoc_Location::ScalePrec();
#else
  constexpr double scalePrec = 1.e-14;
#endif
  return std::abs(std::abs(trsf.ScaleFactor()) - 1.) > scalePrec ||
         trsf.IsNegative();
}

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

} // namespace geom_utils
} // namespace flywave
