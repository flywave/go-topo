#include "edge.hh"
#include "face.hh"
#include "vertex.hh"
#include "wire.hh"

#include <BRepBuilderAPI_Copy.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeEdge2d.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepGProp.hxx>
#include <BRepLib.hxx>
#include <BRep_Tool.hxx>
#include <GCPnts_TangentialDeflection.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <GC_MakeArcOfEllipse.hxx>
#include <GProp_GProps.hxx>
#include <GeomAPI_Interpolate.hxx>
#include <GeomAPI_PointsToBSpline.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <GeomConvert_ApproxCurve.hxx>
#include <Geom_BezierCurve.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TColgp_HArray1OfPnt.hxx>
#include <TopExp.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopoDS.hxx>

namespace flywave {
namespace topo {
namespace {

Handle(TColgp_HArray1OfPnt) points_to_array(const std::vector<gp_Pnt> &points) {
  if (points.empty()) {
    throw std::invalid_argument("Point list cannot be empty");
  }

  Handle(TColgp_HArray1OfPnt) array =
      new TColgp_HArray1OfPnt(1, static_cast<int>(points.size()));
  for (int i = 0; i < points.size(); ++i) {
    array->SetValue(i + 1, points[i]);
  }
  return array;
}

Handle(TColStd_HArray1OfReal)
    floats_to_array(const std::vector<double> &values) {
  Handle(TColStd_HArray1OfReal) array =
      new TColStd_HArray1OfReal(1, static_cast<int>(values.size()));
  for (int i = 0; i < values.size(); ++i) {
    array->SetValue(i + 1, values[i]);
  }
  return array;
}

} // namespace

TopoDS_Edge &edge::value() { return TopoDS::Edge(_shape); }

const TopoDS_Edge &edge::value() const { return TopoDS::Edge(_shape); }

shape edge::copy(bool deep) const {
  try {
    BRepBuilderAPI_Copy _copy(_shape, deep);
    _copy.Build();

    if (!_copy.IsDone())
      throw std::runtime_error("Section operation failed");

    auto shp = _copy.Shape();

    if (shp.IsNull())
      throw std::runtime_error("Shell operation resulted in Null shape");

    return edge{*this, shp};
  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
  }
  return edge{};
}

edge edge::make_polygon() {
  BRepBuilderAPI_MakePolygon me;
  return edge{me.Edge()};
}

edge edge::make_polygon(const gp_Pnt &P1, const gp_Pnt &P2) {
  BRepBuilderAPI_MakePolygon me(P1, P2);
  return edge{me.Edge()};
}

edge edge::make_polygon(const gp_Pnt &P1, const gp_Pnt &P2, const gp_Pnt &P3,
                        const bool Close) {
  BRepBuilderAPI_MakePolygon me(P1, P2, P3, Close);
  return edge{me.Edge()};
}

edge edge::make_polygon(const gp_Pnt &P1, const gp_Pnt &P2, const gp_Pnt &P3,
                        const gp_Pnt &P4, const bool Close) {
  BRepBuilderAPI_MakePolygon me(P1, P2, P3, P4, Close);
  return edge{me.Edge()};
}

edge edge::make_polygon(const vertex &V1, const vertex &V2) {
  BRepBuilderAPI_MakePolygon me(V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_polygon(const vertex &V1, const vertex &V2, const vertex &V3,
                        const bool Close) {
  BRepBuilderAPI_MakePolygon me(V1.value(), V2.value(), V3.value(), Close);
  return edge{me.Edge()};
}

edge edge::make_polygon(const vertex &V1, const vertex &V2, const vertex &V3,
                        const vertex &V4, const bool Close) {
  BRepBuilderAPI_MakePolygon me(V1.value(), V2.value(), V3.value(), V4.value(),
                                Close);
  return edge{me.Edge()};
}

edge edge::make_rect(double width, double height) {
  double halfW = width / 2.0;
  double halfH = height / 2.0;

  BRepBuilderAPI_MakePolygon polyBuilder;
  polyBuilder.Add(gp_Pnt(-halfW, -halfH, 0));
  polyBuilder.Add(gp_Pnt(halfW, -halfH, 0));
  polyBuilder.Add(gp_Pnt(halfW, halfH, 0));
  polyBuilder.Add(gp_Pnt(-halfW, halfH, 0));
  polyBuilder.Close();

  return edge{polyBuilder.Edge()};
}

edge edge::make_polygon(std::vector<vertex *> &vertexs, const bool Close) {
  BRepBuilderAPI_MakePolygon me;
  for (auto _vert : vertexs) {
    me.Add(_vert->value());
  }
  if (Close) {
    me.Close();
  }
  return edge{me.Edge()};
}

edge edge::make_polygon(std::initializer_list<vertex *> vertexs,
                        const bool Close) {
  BRepBuilderAPI_MakePolygon me;
  for (auto _vert : vertexs) {
    me.Add(_vert->value());
  }
  if (Close) {
    me.Close();
  }
  return edge{me.Edge()};
}

edge edge::make_polygon(std::vector<gp_Pnt> &vertexs, const bool Close) {
  BRepBuilderAPI_MakePolygon me;
  for (auto _p : vertexs) {
    me.Add(_p);
  }
  if (Close) {
    me.Close();
  }
  return edge{me.Edge()};
}

edge edge::make_polygon(std::initializer_list<gp_Pnt> vertexs,
                        const bool Close) {
  BRepBuilderAPI_MakePolygon me;
  for (auto _p : vertexs) {
    me.Add(_p);
  }
  if (Close) {
    me.Close();
  }
  return edge{me.Edge()};
}

edge edge::make_edge(const vertex &V1, const vertex &V2) {
  BRepBuilderAPI_MakeEdge me(V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge(const gp_Pnt &P1, const gp_Pnt &P2) {
  BRepBuilderAPI_MakeEdge me(P1, P2);
  return edge{me.Edge()};
}

edge edge::make_edge(const gp_Lin &L) {
  BRepBuilderAPI_MakeEdge me(L);
  return edge{me.Edge()};
}

edge edge::make_edge(const gp_Lin &L, const Standard_Real p1,
                     const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge me(L, p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge(const gp_Lin &L, const gp_Pnt &P1, const gp_Pnt &P2) {
  BRepBuilderAPI_MakeEdge me(L, P1, P2);
  return edge{me.Edge()};
}

edge edge::make_edge(const gp_Lin &L, const vertex &V1, const vertex &V2) {
  BRepBuilderAPI_MakeEdge me(L, V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge(const gp_Circ &L) {
  BRepBuilderAPI_MakeEdge me(L);
  return edge{me.Edge()};
}

edge edge::make_edge(const gp_Circ &L, const Standard_Real p1,
                     const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge me(L, p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge(const gp_Circ &L, const gp_Pnt &P1, const gp_Pnt &P2) {
  BRepBuilderAPI_MakeEdge me(L, P1, P2);
  return edge{me.Edge()};
}

edge edge::make_edge(const gp_Circ &L, const vertex &V1, const vertex &V2) {
  BRepBuilderAPI_MakeEdge me(L, V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge(const gp_Elips &L) {
  BRepBuilderAPI_MakeEdge me(L);
  return edge{me.Edge()};
}

edge edge::make_edge(const gp_Elips &L, const Standard_Real p1,
                     const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge me(L, p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge(const gp_Elips &L, const gp_Pnt &P1, const gp_Pnt &P2) {
  BRepBuilderAPI_MakeEdge me(L, P1, P2);
  return edge{me.Edge()};
}

edge edge::make_edge(const gp_Elips &L, const vertex &V1, const vertex &V2) {
  BRepBuilderAPI_MakeEdge me(L, V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge(const gp_Hypr &L) {
  BRepBuilderAPI_MakeEdge me(L);
  return edge{me.Edge()};
}

edge edge::make_edge(const gp_Hypr &L, const Standard_Real p1,
                     const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge me(L, p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge(const gp_Hypr &L, const gp_Pnt &P1, const gp_Pnt &P2) {
  BRepBuilderAPI_MakeEdge me(L, P1, P2);
  return edge{me.Edge()};
}

edge edge::make_edge(const gp_Hypr &L, const vertex &V1, const vertex &V2) {
  BRepBuilderAPI_MakeEdge me(L, V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge(const gp_Parab &L) {
  BRepBuilderAPI_MakeEdge me(L);
  return edge{me.Edge()};
}

edge edge::make_edge(const gp_Parab &L, const Standard_Real p1,
                     const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge me(L, p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge(const gp_Parab &L, const gp_Pnt &P1, const gp_Pnt &P2) {
  BRepBuilderAPI_MakeEdge me(L, P1, P2);
  return edge{me.Edge()};
}

edge edge::make_edge(const gp_Parab &L, const vertex &V1, const vertex &V2) {
  BRepBuilderAPI_MakeEdge me(L, V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge(const Handle(Geom_Curve) & L) {
  BRepBuilderAPI_MakeEdge me(L);
  return edge{me.Edge()};
}

edge edge::make_edge(const Handle(Geom_Curve) & L, const Standard_Real p1,
                     const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge me(L, p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge(const Handle(Geom_Curve) & L, const gp_Pnt &P1,
                     const gp_Pnt &P2) {
  BRepBuilderAPI_MakeEdge me(L, P1, P2);
  return edge{me.Edge()};
}

edge edge::make_edge(const Handle(Geom_Curve) & L, const vertex &V1,
                     const vertex &V2) {
  BRepBuilderAPI_MakeEdge me(L, V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge(const Handle(Geom_Curve) & L, const gp_Pnt &P1,
                     const gp_Pnt &P2, const Standard_Real p1,
                     const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge me(L, P1, P2, p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge(const Handle(Geom_Curve) & L, const vertex &V1,
                     const vertex &V2, const Standard_Real p1,
                     const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge me(L, V1.value(), V2.value(), p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge(const Handle(Geom2d_Curve) & L,
                     const Handle(Geom_Surface) & S) {
  BRepBuilderAPI_MakeEdge me(L, S);
  return edge{me.Edge()};
}

edge edge::make_edge(const Handle(Geom2d_Curve) & L,
                     const Handle(Geom_Surface) & S, const Standard_Real p1,
                     const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge me(L, S, p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge(const Handle(Geom2d_Curve) & L,
                     const Handle(Geom_Surface) & S, const gp_Pnt &P1,
                     const gp_Pnt &P2) {
  BRepBuilderAPI_MakeEdge me(L, S, P1, P2);
  return edge{me.Edge()};
}

edge edge::make_edge(const Handle(Geom2d_Curve) & L,
                     const Handle(Geom_Surface) & S, const vertex &V1,
                     const vertex &V2) {
  BRepBuilderAPI_MakeEdge me(L, S, V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge(const Handle(Geom2d_Curve) & L,
                     const Handle(Geom_Surface) & S, const gp_Pnt &P1,
                     const gp_Pnt &P2, const Standard_Real p1,
                     const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge me(L, S, P1, P2, p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge(const Handle(Geom2d_Curve) & L,
                     const Handle(Geom_Surface) & S, const vertex &V1,
                     const vertex &V2, const Standard_Real p1,
                     const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge me(L, S, V1.value(), V2.value(), p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const vertex &V1, const vertex &V2) {
  BRepBuilderAPI_MakeEdge2d me(V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge2d(const gp_Pnt2d &P1, const gp_Pnt2d &P2) {
  BRepBuilderAPI_MakeEdge2d me(P1, P2);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const gp_Lin2d &L) {
  BRepBuilderAPI_MakeEdge2d me(L);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const gp_Lin2d &L, const Standard_Real p1,
                       const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge2d me(L, p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const gp_Lin2d &L, const gp_Pnt2d &P1,
                       const gp_Pnt2d &P2) {
  BRepBuilderAPI_MakeEdge2d me(L, P1, P2);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const gp_Lin2d &L, const vertex &V1, const vertex &V2) {
  BRepBuilderAPI_MakeEdge2d me(L, V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge2d(const gp_Circ2d &L) {
  BRepBuilderAPI_MakeEdge2d me(L);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const gp_Circ2d &L, const Standard_Real p1,
                       const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge2d me(L, p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const gp_Circ2d &L, const gp_Pnt2d &P1,
                       const gp_Pnt2d &P2) {
  BRepBuilderAPI_MakeEdge2d me(L, P1, P2);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const gp_Circ2d &L, const vertex &V1, const vertex &V2) {
  BRepBuilderAPI_MakeEdge2d me(L, V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge2d(const gp_Elips2d &L) {
  BRepBuilderAPI_MakeEdge2d me(L);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const gp_Elips2d &L, const Standard_Real p1,
                       const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge2d me(L, p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const gp_Elips2d &L, const gp_Pnt2d &P1,
                       const gp_Pnt2d &P2) {
  BRepBuilderAPI_MakeEdge2d me(L, P1, P2);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const gp_Elips2d &L, const vertex &V1,
                       const vertex &V2) {
  BRepBuilderAPI_MakeEdge2d me(L, V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge2d(const gp_Hypr2d &L) {
  BRepBuilderAPI_MakeEdge2d me(L);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const gp_Hypr2d &L, const Standard_Real p1,
                       const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge2d me(L, p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const gp_Hypr2d &L, const gp_Pnt2d &P1,
                       const gp_Pnt2d &P2) {
  BRepBuilderAPI_MakeEdge2d me(L, P1, P2);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const gp_Hypr2d &L, const vertex &V1, const vertex &V2) {
  BRepBuilderAPI_MakeEdge2d me(L, V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge2d(const gp_Parab2d &L) {
  BRepBuilderAPI_MakeEdge2d me(L);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const gp_Parab2d &L, const Standard_Real p1,
                       const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge2d me(L, p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const gp_Parab2d &L, const gp_Pnt2d &P1,
                       const gp_Pnt2d &P2) {
  BRepBuilderAPI_MakeEdge2d me(L, P1, P2);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const gp_Parab2d &L, const vertex &V1,
                       const vertex &V2) {
  BRepBuilderAPI_MakeEdge2d me(L, V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge2d(const Handle(Geom2d_Curve) & L) {
  BRepBuilderAPI_MakeEdge2d me(L);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const Handle(Geom2d_Curve) & L, const Standard_Real p1,
                       const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge2d me(L, p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const Handle(Geom2d_Curve) & L, const gp_Pnt2d &P1,
                       const gp_Pnt2d &P2) {
  BRepBuilderAPI_MakeEdge2d me(L, P1, P2);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const Handle(Geom2d_Curve) & L, const vertex &V1,
                       const vertex &V2) {
  BRepBuilderAPI_MakeEdge2d me(L, V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge2d(const Handle(Geom2d_Curve) & L, const gp_Pnt2d &P1,
                       const gp_Pnt2d &P2, const Standard_Real p1,
                       const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge2d me(L, P1, P2, p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const Handle(Geom2d_Curve) & L, const vertex &V1,
                       const vertex &V2, const Standard_Real p1,
                       const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge2d me(L, V1.value(), V2.value(), p1, p2);
  return edge{me.Edge()};
}

edge edge::make_spline(const std::vector<gp_Pnt> &points, double tol,
                       bool periodic) {
  Handle(TColgp_HArray1OfPnt) pointArray = points_to_array(points);
  GeomAPI_Interpolate interpolator(pointArray, periodic, tol);
  interpolator.Perform();

  if (!interpolator.IsDone()) {
    throw std::runtime_error("Spline interpolation failed");
  }

  return BRepBuilderAPI_MakeEdge(interpolator.Curve()).Edge();
}

edge edge::make_spline(const std::vector<gp_Pnt> &points,
                       const std::pair<gp_Vec, gp_Vec> *tangents,
                       const std::vector<double> *parameters, double tol,
                       bool periodic, bool scale) {
  Handle(TColgp_HArray1OfPnt) pointArray = points_to_array(points);
  GeomAPI_Interpolate interpolator(
      parameters ? GeomAPI_Interpolate(pointArray, floats_to_array(*parameters),
                                       periodic, tol)
                 : GeomAPI_Interpolate(pointArray, periodic, tol));

  if (tangents) {
    interpolator.Load(tangents->first, tangents->second, scale);
  }

  interpolator.Perform();

  if (!interpolator.IsDone()) {
    throw std::runtime_error("Spline interpolation failed");
  }

  return BRepBuilderAPI_MakeEdge(interpolator.Curve()).Edge();
}

edge edge::make_spline(const std::vector<gp_Pnt> &points,
                       const std::vector<gp_Vec> *tangents, bool periodic,
                       const std::vector<double> *parameters, bool scale,
                       double tol) {
  if (points.empty()) {
    throw std::invalid_argument("At least one point is required");
  }

  Handle(TColgp_HArray1OfPnt) pointArray =
      new TColgp_HArray1OfPnt(1, static_cast<int>(points.size()));
  for (int i = 0; i < points.size(); ++i) {
    pointArray->SetValue(i + 1, points[i]);
  }

  std::unique_ptr<GeomAPI_Interpolate> interpolator;

  if (parameters) {
    if (parameters->size() != (points.size() + (periodic ? 1 : 0))) {
      throw std::invalid_argument(
          "Parameter count must match point count (plus one if periodic)");
    }

    Handle(TColStd_HArray1OfReal) paramArray =
        new TColStd_HArray1OfReal(1, static_cast<int>(parameters->size()));
    for (int i = 0; i < parameters->size(); ++i) {
      paramArray->SetValue(i + 1, (*parameters)[i]);
    }

    interpolator.reset(
        new GeomAPI_Interpolate(pointArray, paramArray, periodic, tol));
  } else {
    interpolator.reset(new GeomAPI_Interpolate(pointArray, periodic, tol));
  }

  if (tangents && !tangents->empty()) {
    if (tangents->size() == 2 && points.size() != 2) {
      interpolator->Load((*tangents)[0], (*tangents)[1], scale);
    } else {
      if (tangents->size() != points.size()) {
        throw std::invalid_argument(
            "Tangent count must match point count or be exactly 2");
      }

      TColgp_Array1OfVec tangentArray(1, static_cast<int>(tangents->size()));
      Handle(TColStd_HArray1OfBoolean) tangentEnabled =
          new TColStd_HArray1OfBoolean(1, static_cast<int>(tangents->size()));

      for (int i = 0; i < tangents->size(); ++i) {
        tangentEnabled->SetValue(i + 1, true);
        tangentArray.SetValue(i + 1, (*tangents)[i]);
      }

      interpolator->Load(tangentArray, tangentEnabled, scale);
    }
  }

  interpolator->Perform();
  if (!interpolator->IsDone()) {
    throw std::runtime_error("B-spline interpolation failed");
  }

  Handle(Geom_BSplineCurve) spline = interpolator->Curve();
  BRepBuilderAPI_MakeEdge edgeMaker(spline);
  if (!edgeMaker.IsDone()) {
    throw std::runtime_error("Edge creation failed");
  }

  return edge(edgeMaker.Edge());
}

edge edge::make_spline_approx(
    const std::vector<gp_Pnt> &points, double tolerance,
    const boost::optional<std::tuple<double, double, double>> &smoothing,
    int minDegree, int maxDegree) {
  if (points.empty()) {
    throw std::invalid_argument("Point list cannot be empty");
  }
  if (minDegree < 1 || maxDegree < minDegree) {
    throw std::invalid_argument("Invalid degree parameters");
  }

  TColgp_Array1OfPnt pointArray =
      TColgp_Array1OfPnt(1, static_cast<int>(points.size()));
  for (int i = 0; i < points.size(); i++) {
    pointArray.SetValue(i + 1, points[i]);
  }

  Handle(Geom_BSplineCurve) spline;
  if (smoothing) {
    double weight1, weight2, weight3;
    std::tie(weight1, weight2, weight3) = *smoothing;
    GeomAPI_PointsToBSpline splineBuilder(pointArray, weight1, weight2, weight3,
                                          maxDegree, GeomAbs_C2, tolerance);
    spline = splineBuilder.Curve();
  } else {
    GeomAPI_PointsToBSpline splineBuilder(pointArray, minDegree, maxDegree,
                                          GeomAbs_C2, tolerance);
    spline = splineBuilder.Curve();
  }

  if (spline.IsNull()) {
    throw std::runtime_error("B-spline approximation failed");
  }

  BRepBuilderAPI_MakeEdge edgeMaker(spline);
  if (!edgeMaker.IsDone()) {
    throw std::runtime_error("Edge creation from spline failed");
  }

  return edge(edgeMaker.Edge());
}

edge edge::make_circle(double radius, const gp_Pnt &center,
                       const gp_Dir &normal, double angle1, double angle2,
                       bool orientation) {
  if (radius <= 0) {
    throw std::invalid_argument("Radius must be positive");
  }

  gp_Ax2 axis(center, normal);

  gp_Circ circle(axis, radius);

  if (angle1 == angle2) {
    return BRepBuilderAPI_MakeEdge(circle).Edge();
  } else {
    double rad1 = angle1 * M_PI / 180.0;
    double rad2 = angle2 * M_PI / 180.0;

    Handle(Geom_TrimmedCurve) arc =
        GC_MakeArcOfCircle(circle, rad1, rad2, orientation).Value();

    return BRepBuilderAPI_MakeEdge(arc).Edge();
  }
}

edge edge::make_ellipse(double majorRadius, double minorRadius,
                        const gp_Pnt &center, const gp_Dir &normal,
                        const gp_Dir &xnormal, double angle1, double angle2,
                        int sense) {
  if (majorRadius <= 0 || minorRadius <= 0) {
    throw std::invalid_argument("Radii must be positive");
  }

  gp_Ax1 axis1(center, normal);
  gp_Ax2 axis2(center, normal, xnormal);

  double correction_angle = 0.0;
  gp_Elips ellipse_gp;

  if (minorRadius > majorRadius) {
    correction_angle = M_PI_2;
    ellipse_gp = gp_Elips(axis2, minorRadius, majorRadius)
                     .Rotated(axis1, correction_angle);
  } else {
    ellipse_gp = gp_Elips(axis2, majorRadius, minorRadius);
  }

  if (angle1 == angle2) {
    return BRepBuilderAPI_MakeEdge(ellipse_gp).Edge();
  } else {
    double rad1 = angle1 * M_PI / 180.0 - correction_angle;
    double rad2 = angle2 * M_PI / 180.0 - correction_angle;
    bool isSense = (sense == 1);

    Handle(Geom_TrimmedCurve) arc =
        GC_MakeArcOfEllipse(ellipse_gp, rad1, rad2, isSense).Value();

    return BRepBuilderAPI_MakeEdge(arc).Edge();
  }
}

edge edge::make_three_point_arc(const gp_Pnt &v1, const gp_Pnt &v2,
                                const gp_Pnt &v3) {
  Handle(Geom_TrimmedCurve) circleGeom = GC_MakeArcOfCircle(v1, v2, v3).Value();
  return edge(BRepBuilderAPI_MakeEdge(circleGeom).Edge());
}

edge edge::make_tangent_arc(const gp_Pnt &v1, const gp_Vec &tangent,
                            const gp_Pnt &v3) {
  Handle(Geom_TrimmedCurve) circleGeom =
      GC_MakeArcOfCircle(v1, tangent, v3).Value();
  return edge(BRepBuilderAPI_MakeEdge(circleGeom).Edge());
}

edge edge::make_bezier(const std::vector<gp_Pnt> &points) {
  if (points.size() < 2) {
    throw std::invalid_argument(
        "At least two points required for Bézier curve");
  }

  TColgp_Array1OfPnt arr(1, static_cast<int>(points.size()));
  for (int i = 0; i < points.size(); i++) {
    arr.SetValue(i + 1, points[i]);
  }

  Handle(Geom_BezierCurve) bezier = new Geom_BezierCurve(arr);
  return edge(BRepBuilderAPI_MakeEdge(bezier).Edge());
}

bool edge::is_seam(const face &f) const {
  if (value().IsNull())
    return false;
  return BRep_Tool::IsClosed(value(), f.value());
}

bool edge::is_degenerated() const {
  if (value().IsNull())
    return true;
  return BRep_Tool::Degenerated(value());
}

bool edge::is_closed() const {
  TopoDS_Vertex aV1, aV2;
  TopExp::Vertices(value(), aV1, aV2);
  if (!aV1.IsNull() && !aV2.IsNull() && aV1.IsSame(aV2))
    return true;
  return false;
}

bool edge::is_inifinite() const { return value().Infinite(); }

void edge::reverse() { value().Reverse(); }

bool edge::is_curve3d() const { return BRep_Tool::IsGeometric(value()); }

double edge::length() const {
  GProp_GProps prop;
  BRepGProp::LinearProperties(value(), prop);
  return prop.Mass();
}

float edge::tolerance() const { return BRep_Tool::Tolerance(value()); }

void edge::convert_to_curve3d() { BRepLib::BuildCurve3d(value()); }

Handle(Adaptor3d_Curve) edge::get_geom() const {
  if (this->is_null()) {
    return nullptr;
  }
  return new BRepAdaptor_Curve(this->value());
}

boost::variant<wire, edge> edge::close() const {
  if (!this->is_closed()) {
    return wire::make_wire(*this).close();
  } else {
    return *this;
  }
}

gp_Pnt edge::arc_center() const {
  shape_geom_type g = this->geom_type();
  Handle(Adaptor3d_Curve) curve = this->get_geom();

  Handle_BRepAdaptor_Curve _curve;

  if (curve->DynamicType() == STANDARD_TYPE(BRepAdaptor_Curve)) {
    _curve = Handle(BRepAdaptor_Curve)::DownCast(curve);
  } else {
    throw std::runtime_error(" is not a curve");
  }

  if (g == shape_geom_circle) {
    return (_curve->Circle().Position().Location());
  } else if (g == shape_geom_ellipse) {
    return (_curve->Ellipse().Position().Location());
  } else {
    throw std::runtime_error(" has no arc center");
  }
}

edge edge::trim(double u0, double u1) const {
  Handle(Geom_Curve) curve = this->get_curve();
  BRepBuilderAPI_MakeEdge bldr(curve, u0, u1);
  return edge(bldr.Shape());
}

} // namespace topo
} // namespace flywave
