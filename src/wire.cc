#include <BRepAdaptor_Curve.hxx>
#include <BRepBuilderAPI_Copy.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepExtrema_DistShapeShape.hxx>
#include <BRepFilletAPI_MakeChamfer.hxx>
#include <BRepFilletAPI_MakeFillet2d.hxx>
#include <BRepGProp.hxx>
#include <BRepLib.hxx>
#include <BRepLib_FindSurface.hxx>
#include <BRepOffsetAPI_MakeOffset.hxx>
#include <BRepOffsetAPI_NormalProjection.hxx>
#include <BRepProj_Projection.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <BRep_Tool.hxx>
#include <ChFi2d_FilletAPI.hxx>
#include <GCE2d_MakeSegment.hxx>
#include <GCPnts_AbscissaPoint.hxx>
#include <GCPnts_QuasiUniformAbscissa.hxx>
#include <GCPnts_QuasiUniformDeflection.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <GProp_GProps.hxx>
#include <Geom2d_Line.hxx>
#include <GeomAPI_Interpolate.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <GeomConvert_ApproxCurve.hxx>
#include <GeomFill_CorrectedFrenet.hxx>
#include <GeomFill_Frenet.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_ConicalSurface.hxx>
#include <Geom_Curve.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <Geom_Plane.hxx>
#include <LProp3d_CLProps.hxx>
#include <Precision.hxx>
#include <ShapeAnalysis_FreeBounds.hxx>
#include <ShapeAnalysis_Wire.hxx>
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

#include <unordered_set>

#include "compound.hh"
#include "edge.hh"
#include "face.hh"
#include "vertex.hh"
#include "wire.hh"

namespace flywave {
namespace topo {

TopoDS_Wire &wire::value() { return TopoDS::Wire(_shape); }

const TopoDS_Wire &wire::value() const { return TopoDS::Wire(_shape); }

shape wire::copy(bool deep) const {
  try {
    BRepBuilderAPI_Copy _copy(_shape, deep);
    _copy.Build();

    if (!_copy.IsDone())
      throw std::runtime_error("Section operation failed");

    auto shp = _copy.Shape();

    if (shp.IsNull())
      throw std::runtime_error("Shell operation resulted in Null shape");

    return wire{shp};
  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
  }
  return wire{};
}

wire wire::make_polygon() {
  BRepBuilderAPI_MakePolygon me;
  return wire{me.Wire()};
}

wire wire::make_polygon(const gp_Pnt &P1, const gp_Pnt &P2) {
  BRepBuilderAPI_MakePolygon me(P1, P2);
  return wire{me.Wire()};
}

wire wire::make_polygon(const gp_Pnt &P1, const gp_Pnt &P2, const gp_Pnt &P3,
                        const bool Close) {
  BRepBuilderAPI_MakePolygon me(P1, P2, P3, Close);
  return wire{me.Wire()};
}

wire wire::make_polygon(const gp_Pnt &P1, const gp_Pnt &P2, const gp_Pnt &P3,
                        const gp_Pnt &P4, const bool Close) {
  BRepBuilderAPI_MakePolygon me(P1, P2, P3, P4, Close);
  return wire{me.Wire()};
}

wire wire::make_polygon(const vertex &V1, const vertex &V2) {
  BRepBuilderAPI_MakePolygon me(V1.value(), V2.value());
  return wire{me.Wire()};
}

wire wire::make_polygon(const vertex &V1, const vertex &V2, const vertex &V3,
                        const bool Close) {
  BRepBuilderAPI_MakePolygon me(V1.value(), V2.value(), V3.value(), Close);
  return wire{me.Wire()};
}

wire wire::make_polygon(const vertex &V1, const vertex &V2, const vertex &V3,
                        const vertex &V4, const bool Close) {
  BRepBuilderAPI_MakePolygon me(V1.value(), V2.value(), V3.value(), V4.value(),
                                Close);
  return wire{me.Wire()};
}

wire wire::make_wire(const edge &E) {
  BRepBuilderAPI_MakeWire mw(E.value());
  return wire{mw.Wire()};
}
wire wire::make_wire(const edge &E1, const edge &E2) {
  BRepBuilderAPI_MakeWire mw(E1.value(), E2.value());
  return wire{mw.Wire()};
}

wire wire::make_wire(const edge &E1, const edge &E2, const edge &E3) {
  BRepBuilderAPI_MakeWire mw(E1.value(), E2.value(), E3.value());
  return wire{mw.Wire()};
}

wire wire::make_wire(const edge &E1, const edge &E2, const edge &E3,
                     const edge &E4) {
  BRepBuilderAPI_MakeWire mw(E1.value(), E2.value(), E3.value(), E4.value());
  return wire{mw.Wire()};
}
wire wire::make_wire(const wire &W) {
  BRepBuilderAPI_MakeWire mw(W.value());
  return wire{mw.Wire()};
}

wire wire::make_wire(const wire &W, const edge &E) {
  BRepBuilderAPI_MakeWire mw(W.value(), E.value());
  return wire{mw.Wire()};
}

wire wire::make_wire(std::vector<edge> &edges) {
  wire ret;
  try {
    BRepBuilderAPI_MakeWire MW;
    for (unsigned i = 0; i < edges.size(); i++) {
      edge *e = &edges[i];
      MW.Add(e->value());
    }

    MW.Build();

    BRepBuilderAPI_WireError error = MW.Error();
    switch (error) {
    case BRepBuilderAPI_EmptyWire: {
      throw std::runtime_error("Wire empty");
      break;
    }
    case BRepBuilderAPI_DisconnectedWire: {
      throw std::runtime_error("Disconnected wire");
      break;
    }
    case BRepBuilderAPI_NonManifoldWire: {
      throw std::runtime_error("non-manifold wire");
      break;
    }
    default:
      break;
    }

    ret = wire(MW.Wire());

    if (!ret.fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to create wire");
    }
  }
  return ret;
}

wire wire::make_wire(std::initializer_list<edge> edges) {
  wire ret;
  try {
    BRepBuilderAPI_MakeWire MW;
    for (auto e_ : edges) {
      edge *e = &e_;
      MW.Add(e->value());
    }

    MW.Build();

    BRepBuilderAPI_WireError error = MW.Error();
    switch (error) {
    case BRepBuilderAPI_EmptyWire: {
      throw std::runtime_error("Wire empty");
      break;
    }
    case BRepBuilderAPI_DisconnectedWire: {
      throw std::runtime_error("Disconnected wire");
      break;
    }
    case BRepBuilderAPI_NonManifoldWire: {
      throw std::runtime_error("non-manifold wire");
      break;
    }
    default:
      break;
    }

    ret = wire(MW.Wire());

    if (!ret.fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to create wire");
    }
  }
  return ret;
}

wire wire::make_wire(std::vector<wire> &wires) {
  wire ret;
  try {
    BRepBuilderAPI_MakeWire MW;
    for (auto w_ : wires) {
      wire *e = &w_;
      MW.Add(e->value());
    }

    MW.Build();

    BRepBuilderAPI_WireError error = MW.Error();
    switch (error) {
    case BRepBuilderAPI_EmptyWire: {
      throw std::runtime_error("Wire empty");
      break;
    }
    case BRepBuilderAPI_DisconnectedWire: {
      throw std::runtime_error("Disconnected wire");
      break;
    }
    case BRepBuilderAPI_NonManifoldWire: {
      throw std::runtime_error("non-manifold wire");
      break;
    }
    default:
      break;
    }

    ret = wire(MW.Wire());

    if (!ret.fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to create wire");
    }
  }
  return ret;
}

wire wire::make_wire(std::initializer_list<wire> wires) {
  wire ret;
  try {
    BRepBuilderAPI_MakeWire MW;
    for (auto w_ : wires) {
      wire *e = &w_;
      MW.Add(e->value());
    }

    MW.Build();

    BRepBuilderAPI_WireError error = MW.Error();
    switch (error) {
    case BRepBuilderAPI_EmptyWire: {
      throw std::runtime_error("Wire empty");
      break;
    }
    case BRepBuilderAPI_DisconnectedWire: {
      throw std::runtime_error("Disconnected wire");
      break;
    }
    case BRepBuilderAPI_NonManifoldWire: {
      throw std::runtime_error("non-manifold wire");
      break;
    }
    default:
      break;
    }

    ret = wire(MW.Wire());

    if (!ret.fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to create wire");
    }
  }
  return ret;
}

wire wire::make_rect(double width, double height) {
  double halfW = width / 2.0;
  double halfH = height / 2.0;

  BRepBuilderAPI_MakePolygon polyBuilder;
  polyBuilder.Add(gp_Pnt(-halfW, -halfH, 0));
  polyBuilder.Add(gp_Pnt(halfW, -halfH, 0));
  polyBuilder.Add(gp_Pnt(halfW, halfH, 0));
  polyBuilder.Add(gp_Pnt(-halfW, halfH, 0));
  polyBuilder.Close();

  return wire{polyBuilder.Wire()};
}

wire wire::make_circle(double radius, const gp_Pnt &center,
                       const gp_Dir &normal) {
  if (radius <= 0) {
    throw std::invalid_argument("Radius must be positive");
  }

  gp_Ax2 axis(center, normal);
  gp_Circ circle(axis, radius);
  TopoDS_Edge e = BRepBuilderAPI_MakeEdge(circle).Edge();

  return wire::make_wire({edge(e)});
}

wire wire::make_ellipse(double x_radius, double y_radius, const gp_Pnt &center,
                        const gp_Dir &normal, const gp_Dir &xDir, double angle1,
                        double angle2, double rotation_angle, bool closed) {
  if (x_radius <= 0 || y_radius <= 0) {
    throw std::invalid_argument("Radii must be positive");
  }

  gp_Ax2 axis(center, normal, xDir);
  gp_Elips ellipse(axis, x_radius, y_radius);

  TopoDS_Edge e;
  if (angle1 == angle2) {
    e = BRepBuilderAPI_MakeEdge(ellipse).Edge();
  } else {
    e = BRepBuilderAPI_MakeEdge(ellipse, angle1 * M_PI / 180.0,
                                angle2 * M_PI / 180.0)
            .Edge();
  }

  std::vector<edge> edges;
  edges.emplace_back(e);

  if (angle1 != angle2 && closed) {
    edge startEdge(e);
    edge endEdge(e);
    gp_Pnt start = startEdge.start_point();
    gp_Pnt end = endEdge.end_point();

    if (!start.IsEqual(end, Precision::Confusion())) {
      edge line = edge::make_edge(end, start);
      edges.push_back(line);
    }
  }

  wire result = wire::make_wire(edges);

  if (rotation_angle != 0.0) {
    gp_Ax1 rotationAxis(center, normal);
    result.rotate(rotation_angle * M_PI / 180.0, rotationAxis);
  }

  return result;
}

wire wire::make_polygon(const std::vector<gp_Pnt> &vertices, bool close,
                        bool forConstruction) {
  if (vertices.size() < 2) {
    throw std::invalid_argument("At least two vertices required");
  }

  BRepBuilderAPI_MakePolygon polyBuilder;
  for (const auto &vertex : vertices) {
    polyBuilder.Add(vertex);
  }

  if (close) {
    polyBuilder.Close();
  }

  if (!polyBuilder.IsDone()) {
    throw std::runtime_error("Failed to create polygon wire");
  }

  return wire(polyBuilder.Wire(), forConstruction);
}

wire wire::make_helix(double pitch, double height, double radius,
                      const gp_Pnt &center, const gp_Dir &dir, double angle,
                      bool lefthand) {
  Handle(Geom_Surface) geom_surf;
  gp_Ax3 axis(center, dir);

  if (angle == 360.0) {
    geom_surf = new Geom_CylindricalSurface(axis, radius);
  } else {
    double angle_rad = angle * M_PI / 180.0;
    geom_surf = new Geom_ConicalSurface(axis, angle_rad, radius);
  }

  gp_Pnt2d origin(0.0, 0.0);
  gp_Dir2d line_dir;

  if (lefthand) {
    line_dir = gp_Dir2d(-2 * M_PI, pitch);
  } else {
    line_dir = gp_Dir2d(2 * M_PI, pitch);
  }

  Handle(Geom2d_Line) geom_line = new Geom2d_Line(origin, line_dir);

  double n_turns = height / pitch;
  double param_length = n_turns * sqrt(pow(2 * M_PI, 2) + pow(pitch, 2));

  gp_Pnt2d u_start = geom_line->Value(0.0);
  gp_Pnt2d u_stop = geom_line->Value(param_length);

  Handle(Geom2d_TrimmedCurve) geom_seg =
      GCE2d_MakeSegment(u_start, u_stop).Value();

  BRepBuilderAPI_MakeEdge edgeMaker(geom_seg, geom_surf);
  TopoDS_Edge e = edgeMaker.Edge();

  BRepBuilderAPI_MakeWire wireMaker(e);
  TopoDS_Shape w = wireMaker.Wire();

  BRepLib::BuildCurves3d(w, 1e-6, GeomAbs_C1, 14, 2000);

  return wire(w);
}

wire wire::make_wire(const std::vector<std::vector<gp_Pnt>> &points,
                     const std::vector<curve_type> &curveTypes) {
  if (points.empty()) {
    throw std::runtime_error("Control points cannot be empty");
  }
  if (points.size() != curveTypes.size()) {
    throw std::runtime_error("Points and curve types count mismatch");
  }

  try {
    // 创建路径线
    BRepBuilderAPI_MakeWire pathMaker;

    for (size_t i = 0; i < points.size(); ++i) {
      const auto &pts = points[i];
      curve_type type = curveTypes[i];

      switch (type) {
      case curve_type::line: {
        if (pts.size() != 2) {
          throw Standard_ConstructionError("Line requires exactly 2 points");
        }
        pathMaker.Add(BRepBuilderAPI_MakeEdge(pts[0], pts[1]).Edge());
        break;
      }
      case curve_type::three_point_arc: {
        if (pts.size() != 3) {
          throw Standard_ConstructionError("Three-point arc requires 3 points");
        }
        GC_MakeArcOfCircle arcMaker(pts[0], pts[1], pts[2]);
        if (!arcMaker.IsDone()) {
          throw Standard_ConstructionError("Failed to create three-point arc");
        }
        pathMaker.Add(BRepBuilderAPI_MakeEdge(arcMaker.Value()));
        break;
      }
      case curve_type::circle_center_arc: {
        if (pts.size() != 3) {
          throw Standard_ConstructionError(
              "Center arc requires [start, center, end] points");
        }
        gp_Circ circle(gp_Ax2(pts[1], gp_Dir(0, 0, -1)),
                       pts[0].Distance(pts[1]));
        GC_MakeArcOfCircle arcMaker(circle, pts[0], pts[2], true);
        if (!arcMaker.IsDone()) {
          throw Standard_ConstructionError("Failed to create center arc");
        }
        pathMaker.Add(BRepBuilderAPI_MakeEdge(arcMaker.Value()));
        break;
      }
      case curve_type::spline: {
        if (pts.size() < 2) {
          throw Standard_ConstructionError("Spline requires at least 2 points");
        }
        Handle(TColgp_HArray1OfPnt) array =
            new TColgp_HArray1OfPnt(1, pts.size());
        for (size_t j = 0; j < pts.size(); ++j) {
          array->SetValue(j + 1, pts[j]);
        }
        GeomAPI_Interpolate interpolate(array, false, Precision::Confusion());
        interpolate.Perform();
        if (!interpolate.IsDone()) {
          throw Standard_ConstructionError("Failed to create spline");
        }
        pathMaker.Add(BRepBuilderAPI_MakeEdge(interpolate.Curve()));
        break;
      }
      default:
        throw Standard_ConstructionError("Unknown curve type");
      }
    }

    if (!pathMaker.IsDone()) {
      throw Standard_ConstructionError("Failed to create path wire");
    }
    return pathMaker.Wire();
  } catch (const Standard_ConstructionError &e) {
    return wire();
  }
}

int wire::project(const face &f) {
  Handle(TopTools_HSequenceOfShape) wires = new TopTools_HSequenceOfShape;
  Handle(TopTools_HSequenceOfShape) edges = new TopTools_HSequenceOfShape;
  TopExp_Explorer ex;
  try {
    BRepOffsetAPI_NormalProjection NP(f.value());
    NP.SetLimit(Standard_True);
    NP.Add(value());
    NP.Build();
    if (!NP.IsDone())
      throw std::runtime_error("project operation failed");

    for (ex.Init(NP.Shape(), TopAbs_EDGE); ex.More(); ex.Next()) {
      if (!ex.Current().IsNull()) {
        edges->Append(TopoDS::Edge(ex.Current()));
      }
    }
    ShapeAnalysis_FreeBounds::ConnectEdgesToWires(edges, Precision::Confusion(),
                                                  Standard_True, wires);
    if (wires->Length() != 1)
      throw std::runtime_error("project operation created empty result");

    _shape = wires->Value(1);

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to project wire");
    }
    return 0;
  }
  return 1;
}

int wire::num_edges() const {
  ShapeAnalysis_Wire analyzer;
  analyzer.Load(this->value());
  return analyzer.NbEdges();
}

std::vector<wire> wire::offset2d(double distance,
                                 const GeomAbs_JoinType &joinType) const {
  BRepOffsetAPI_MakeOffset offset;
  offset.Init(joinType);
  offset.AddWire(TopoDS::Wire(this->value()));
  offset.Perform(distance);

  TopoDS_Shape result = offset.Shape();
  std::vector<wire> resultWires;

  if (result.ShapeType() == TopAbs_COMPOUND) {
    TopoDS_Compound compound = TopoDS::Compound(result);
    TopExp_Explorer exp(compound, TopAbs_WIRE);
    for (; exp.More(); exp.Next()) {
      resultWires.emplace_back(TopoDS::Wire(exp.Current()));
    }
  } else {
    resultWires.emplace_back(TopoDS::Wire(result));
  }

  return resultWires;
}

wire wire::fillet2d(double radius, const std::vector<vertex> &vertices) const {
  face f = face::make_face({*this});
  return f.fillet2d(radius, vertices).outer_wire();
}

wire wire::chamfer2d(double d, const std::vector<vertex> &vertices) const {
  face f = face::make_face({*this});
  return f.chamfer2d(d, vertices).outer_wire();
}

int wire::offset(double distance, const GeomAbs_JoinType &joinType) {
  Handle(TopTools_HSequenceOfShape) wires = new TopTools_HSequenceOfShape;
  Handle(TopTools_HSequenceOfShape) edges = new TopTools_HSequenceOfShape;
  TopExp_Explorer ex;

  try {
    BRepOffsetAPI_MakeOffset MO(value(), joinType);
    MO.Perform(distance);

    for (ex.Init(MO.Shape(), TopAbs_EDGE); ex.More(); ex.Next()) {
      if (!ex.Current().IsNull()) {
        edges->Append(TopoDS::Edge(ex.Current()));
      }
    }
    ShapeAnalysis_FreeBounds::ConnectEdgesToWires(edges, Precision::Confusion(),
                                                  Standard_True, wires);
    if (wires->Length() != 1)
      throw std::runtime_error("offset operation created empty result");

    _shape = wires->Value(1);

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset wire");
    }
    return 0;
  }
  return 1;
}

int wire::fillet(std::vector<vertex> &vertices, std::vector<double> radius) {
  size_t vertices_size = vertices.size();
  size_t radius_size = radius.size();

  BRepFilletAPI_MakeFillet2d MF;
  try {
    if (value().IsNull()) {
      throw std::runtime_error("Shapes is Null");
    }

    MF.Init(BRepBuilderAPI_MakeFace(value()));

    for (unsigned i = 0; i < vertices.size(); i++) {
      vertex *v = &vertices[i];

      if (radius_size == 1) {
        MF.AddFillet(v->value(), radius[0]);
      } else if (radius_size == vertices_size) {
        MF.AddFillet(v->value(), radius[i]);
      } else {
        throw std::runtime_error("radius argument has wrong size");
      }
    }

    if (MF.Status() != ChFi2d_IsDone)
      throw std::runtime_error("fillet not completed");

    BRepBuilderAPI_MakeWire wire;
    TopTools_IndexedMapOfShape aMap;
    BRepTools_WireExplorer Ex;

    TopExp::MapShapes(MF.Shape(), TopAbs_WIRE, aMap);
    if (aMap.Extent() != 1)
      throw std::runtime_error(
          "Fillet operation did not result in single wire");

    Ex.Clear();
    for (Ex.Init(TopoDS::Wire(aMap(1))); Ex.More(); Ex.Next()) {
      wire.Add(Ex.Current());
    }

    _shape = wire;

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to fillet wire");
    }
    return 0;
  }
  return 1;
}

int wire::chamfer(std::vector<vertex> &vertices,
                  std::vector<double> distances) {
  size_t vertices_size = vertices.size();
  size_t distances_size = distances.size();

  BRepFilletAPI_MakeFillet2d MF;
  try {
    if (_shape.IsNull()) {
      throw std::runtime_error("Shapes is Null");
    }

    MF.Init(BRepBuilderAPI_MakeFace(value()));

    TopTools_IndexedMapOfShape vertMap;
    for (unsigned i = 0; i < vertices.size(); i++)
      vertMap.Add(vertices[i].value());

    bool first = true;
    TopoDS_Edge firstEdge, nextEdge;
    TopoDS_Vertex vertex;

    BRepTools_WireExplorer Ex1;
    for (Ex1.Init(value()); Ex1.More();) {
      if (first == true) {
        firstEdge = Ex1.Current();
        first = false;
      }

      Ex1.Next();

      if (Ex1.More() == Standard_False)
        break;

      nextEdge = Ex1.Current();

      if (!TopExp::CommonVertex(firstEdge, nextEdge, vertex)) {
        first = true;
        continue;
      }

      if (vertMap.Contains(vertex)) {
        int i = vertMap.FindIndex(vertex) - 1;

        if (distances_size == 1) {
          MF.AddChamfer(firstEdge, nextEdge, distances[0], distances[0]);
        } else if (distances_size == vertices_size) {
          MF.AddChamfer(firstEdge, nextEdge, distances[i], distances[i]);
        } else {
          throw std::runtime_error("distances argument has wrong size");
        }
      }

      firstEdge = nextEdge;
    }

    if (is_closed()) {
      TopoDS_Vertex aV1;
      TopExp::Vertices(value(), vertex, aV1);

      if (vertMap.Contains(vertex)) {
        int i = vertMap.FindIndex(vertex) - 1;

        TopTools_IndexedDataMapOfShapeListOfShape mapVertexEdge;
        TopExp::MapShapesAndAncestors(value(), TopAbs_VERTEX, TopAbs_EDGE,
                                      mapVertexEdge);

        const TopTools_ListOfShape &edges = mapVertexEdge.FindFromKey(vertex);
        firstEdge = TopoDS::Edge(edges.First());
        nextEdge = TopoDS::Edge(edges.Last());

        if (distances_size == 1) {
          MF.AddChamfer(firstEdge, nextEdge, distances[0], distances[0]);
        } else if (distances_size == vertices_size) {
          MF.AddChamfer(firstEdge, nextEdge, distances[i], distances[i]);
        } else {
          throw std::runtime_error("distances argument has wrong size");
        }
      }
    }

    if (MF.Status() != ChFi2d_IsDone)
      throw std::runtime_error("chamfer operation failed");

    TopTools_IndexedMapOfShape aMap;
    TopExp::MapShapes(MF.Shape(), TopAbs_WIRE, aMap);
    if (aMap.Extent() != 1)
      throw std::runtime_error("chamfer result did not result in single wire");
    ;

    BRepBuilderAPI_MakeWire wire;
    BRepTools_WireExplorer Ex2;
    for (Ex2.Init(TopoDS::Wire(aMap(1))); Ex2.More(); Ex2.Next()) {
      wire.Add(Ex2.Current());
    }

    _shape = wire.Shape();

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to chamfer wire");
    }
    return 0;
  }
  return 1;
}

void wire::convert_to_curves3d() { BRepLib::BuildCurves3d(value()); }

Handle(Adaptor3d_Curve) wire::get_geom() const {
  if (this->is_null()) {
    throw std::invalid_argument("Input shape is null");
  }

  int edgeCount = 0;
  for (TopExp_Explorer exp(this->value(), TopAbs_EDGE); exp.More();
       exp.Next()) {
    edgeCount++;
  }

  if (edgeCount == 0) {
    throw std::invalid_argument("Shape contains no edges");
  }

  if (edgeCount == 1) {
    TopExp_Explorer exp(this->value(), TopAbs_EDGE);
    const TopoDS_Edge &edge = TopoDS::Edge(exp.Current());
    return new BRepAdaptor_Curve(edge);
  } else if (this->value().ShapeType() == TopAbs_WIRE) {
    return new BRepAdaptor_CompCurve(TopoDS::Wire(this->value()));
  } else {
    throw std::invalid_argument("Unsupported shape type for compound curve");
  }
}

wire wire::close() const {
  if (!this->is_closed()) {
    gp_Pnt start = this->start_point();
    gp_Pnt end = this->end_point();
    edge e = edge::make_edge(end, start);

    std::vector<shape> wires{*this, e};
    return wire::combine(wires)[0];
  } else {
    return *this;
  }
}

std::vector<wire> wire::combine(std::vector<shape> &wires, double tol) {
  Handle(TopTools_HSequenceOfShape) edges_in = new TopTools_HSequenceOfShape();
  Handle(TopTools_HSequenceOfShape) wires_out = new TopTools_HSequenceOfShape();
  std::vector<shape> listOfWires;
  for (auto &w : wires) {
    listOfWires.push_back(w);
  }

  compound comp = compound::make_compound(listOfWires);
  std::vector<edge> edges;
  for (TopExp_Explorer exp(comp.value(), TopAbs_EDGE); exp.More(); exp.Next()) {
    const TopoDS_Edge &edge = TopoDS::Edge(exp.Current());
    if (!BRep_Tool::Degenerated(edge)) {
      edges.emplace_back(edge);
    }
  }

  for (const auto &edge : edges) {
    edges_in->Append(edge.value());
  }

  ShapeAnalysis_FreeBounds::ConnectEdgesToWires(edges_in, tol, false,
                                                wires_out);

  std::vector<wire> result;
  for (int i = 1; i <= wires_out->Length(); ++i) {
    result.emplace_back(wires_out->Value(i));
  }

  return result;
}

wire wire::stitch(const wire &other) const {
  BRepBuilderAPI_MakeWire wireBuilder;

  wireBuilder.Add(TopoDS::Wire(this->value()));
  wireBuilder.Add(TopoDS::Wire(other.value()));

  wireBuilder.Build();

  if (!wireBuilder.IsDone()) {
    throw std::runtime_error("Failed to stitch wires");
  }

  return wire(wireBuilder.Wire());
}

std::vector<vertex> wire::vertices() const {
  std::vector<vertex> vertices;

  BRepTools_WireExplorer exp(this->value());

  vertices.push_back(exp.CurrentVertex());

  while (exp.More()) {
    exp.Next();
    vertices.push_back(exp.CurrentVertex());
  }

  if (this->is_closed()) {
    vertices.pop_back();
  }

  return vertices;
}

double wire::length() const {
  GProp_GProps props;
  BRepGProp::LinearProperties(_shape, props);
  return props.Mass();
}

} // namespace topo
} // namespace flywave
