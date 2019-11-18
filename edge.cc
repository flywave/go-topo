#include "edge.hh"
#include "face.hh"
#include "vertex.hh"

#include <BRepBuilderAPI_Copy.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeEdge2d.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepGProp.hxx>
#include <BRepLib.hxx>
#include <BRep_Tool.hxx>
#include <GCPnts_TangentialDeflection.hxx>
#include <GProp_GProps.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <TopExp.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopoDS.hxx>

namespace flywave {
namespace topo {

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

    return edge{shp};
  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
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

edge edge::make_polygon(const vector3<Standard_Real> &P1,
                        const vector3<Standard_Real> &P2) {
  BRepBuilderAPI_MakePolygon me(cast_to_gp(P1), cast_to_gp(P2));
  return edge{me.Edge()};
}

edge edge::make_polygon(const vector3<Standard_Real> &P1,
                        const vector3<Standard_Real> &P2,
                        const vector3<Standard_Real> &P3, const bool Close) {
  BRepBuilderAPI_MakePolygon me(cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3),
                                Close);
  return edge{me.Edge()};
}

edge edge::make_polygon(const vector3<Standard_Real> &P1,
                        const vector3<Standard_Real> &P2,
                        const vector3<Standard_Real> &P3,
                        const vector3<Standard_Real> &P4, const bool Close) {
  BRepBuilderAPI_MakePolygon me(cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3),
                                cast_to_gp(P4), Close);
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

edge edge::make_polygon(std::vector<vertex> &vertexs, const bool Close) {
  BRepBuilderAPI_MakePolygon me;
  for (auto _vert : vertexs) {
    me.Add(_vert.value());
  }
  if (Close) {
    me.Close();
  }
  return edge{me.Edge()};
}

edge edge::make_polygon(std::initializer_list<vertex> vertexs,
                        const bool Close) {
  BRepBuilderAPI_MakePolygon me;
  for (auto _vert : vertexs) {
    me.Add(_vert.value());
  }
  if (Close) {
    me.Close();
  }
  return edge{me.Edge()};
}

edge edge::make_polygon(std::vector<vector3<Standard_Real>> &vertexs,
                        const bool Close) {
  BRepBuilderAPI_MakePolygon me;
  for (auto _p : vertexs) {
    me.Add(cast_to_gp(_p));
  }
  if (Close) {
    me.Close();
  }
  return edge{me.Edge()};
}

edge edge::make_polygon(std::initializer_list<vector3<Standard_Real>> vertexs,
                        const bool Close) {
  BRepBuilderAPI_MakePolygon me;
  for (auto _p : vertexs) {
    me.Add(cast_to_gp(_p));
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

edge edge::make_edge(const vector3<Standard_Real> &P1,
                     const vector3<Standard_Real> &P2) {
  BRepBuilderAPI_MakeEdge me(cast_to_gp(P1), cast_to_gp(P2));
  return edge{me.Edge()};
}

edge edge::make_edge(const line &L) {
  BRepBuilderAPI_MakeEdge me(cast_to_gp(L));
  return edge{me.Edge()};
}

edge edge::make_edge(const line &L, const Standard_Real p1,
                     const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge me(cast_to_gp(L), p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge(const line &L, const vector3<Standard_Real> &P1,
                     const vector3<Standard_Real> &P2) {
  BRepBuilderAPI_MakeEdge me(cast_to_gp(L), cast_to_gp(P1), cast_to_gp(P2));
  return edge{me.Edge()};
}

edge edge::make_edge(const line &L, const vertex &V1, const vertex &V2) {
  BRepBuilderAPI_MakeEdge me(cast_to_gp(L), V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge(const circ &L) {
  BRepBuilderAPI_MakeEdge me(cast_to_gp(L));
  return edge{me.Edge()};
}

edge edge::make_edge(const circ &L, const Standard_Real p1,
                     const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge me(cast_to_gp(L), p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge(const circ &L, const vector3<Standard_Real> &P1,
                     const vector3<Standard_Real> &P2) {
  BRepBuilderAPI_MakeEdge me(cast_to_gp(L), cast_to_gp(P1), cast_to_gp(P2));
  return edge{me.Edge()};
}

edge edge::make_edge(const circ &L, const vertex &V1, const vertex &V2) {
  BRepBuilderAPI_MakeEdge me(cast_to_gp(L), V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge(const elips &L) {
  BRepBuilderAPI_MakeEdge me(cast_to_gp(L));
  return edge{me.Edge()};
}

edge edge::make_edge(const elips &L, const Standard_Real p1,
                     const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge me(cast_to_gp(L), p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge(const elips &L, const vector3<Standard_Real> &P1,
                     const vector3<Standard_Real> &P2) {
  BRepBuilderAPI_MakeEdge me(cast_to_gp(L), cast_to_gp(P1), cast_to_gp(P2));
  return edge{me.Edge()};
}

edge edge::make_edge(const elips &L, const vertex &V1, const vertex &V2) {
  BRepBuilderAPI_MakeEdge me(cast_to_gp(L), V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge(const hyperbola &L) {
  BRepBuilderAPI_MakeEdge me(cast_to_gp(L));
  return edge{me.Edge()};
}

edge edge::make_edge(const hyperbola &L, const Standard_Real p1,
                     const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge me(cast_to_gp(L), p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge(const hyperbola &L, const vector3<Standard_Real> &P1,
                     const vector3<Standard_Real> &P2) {
  BRepBuilderAPI_MakeEdge me(cast_to_gp(L), cast_to_gp(P1), cast_to_gp(P2));
  return edge{me.Edge()};
}

edge edge::make_edge(const hyperbola &L, const vertex &V1, const vertex &V2) {
  BRepBuilderAPI_MakeEdge me(cast_to_gp(L), V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge(const parabola &L) {
  BRepBuilderAPI_MakeEdge me(cast_to_gp(L));
  return edge{me.Edge()};
}

edge edge::make_edge(const parabola &L, const Standard_Real p1,
                     const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge me(cast_to_gp(L), p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge(const parabola &L, const vector3<Standard_Real> &P1,
                     const vector3<Standard_Real> &P2) {
  BRepBuilderAPI_MakeEdge me(cast_to_gp(L), cast_to_gp(P1), cast_to_gp(P2));
  return edge{me.Edge()};
}

edge edge::make_edge(const parabola &L, const vertex &V1, const vertex &V2) {
  BRepBuilderAPI_MakeEdge me(cast_to_gp(L), V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge(const geom_curve &L) {
  BRepBuilderAPI_MakeEdge me(L);
  return edge{me.Edge()};
}

edge edge::make_edge(const geom_curve &L, const Standard_Real p1,
                     const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge me(L, p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge(const geom_curve &L, const vector3<Standard_Real> &P1,
                     const vector3<Standard_Real> &P2) {
  BRepBuilderAPI_MakeEdge me(L, cast_to_gp(P1), cast_to_gp(P2));
  return edge{me.Edge()};
}

edge edge::make_edge(const geom_curve &L, const vertex &V1, const vertex &V2) {
  BRepBuilderAPI_MakeEdge me(L, V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge(const geom_curve &L, const vector3<Standard_Real> &P1,
                     const vector3<Standard_Real> &P2, const Standard_Real p1,
                     const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge me(L, cast_to_gp(P1), cast_to_gp(P2), p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge(const geom_curve &L, const vertex &V1, const vertex &V2,
                     const Standard_Real p1, const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge me(L, V1.value(), V2.value(), p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge(const geom2d_curve &L, const geom_surface &S) {
  BRepBuilderAPI_MakeEdge me(L, S);
  return edge{me.Edge()};
}

edge edge::make_edge(const geom2d_curve &L, const geom_surface &S,
                     const Standard_Real p1, const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge me(L, S, p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge(const geom2d_curve &L, const geom_surface &S,
                     const vector3<Standard_Real> &P1,
                     const vector3<Standard_Real> &P2) {
  BRepBuilderAPI_MakeEdge me(L, S, cast_to_gp(P1), cast_to_gp(P2));
  return edge{me.Edge()};
}

edge edge::make_edge(const geom2d_curve &L, const geom_surface &S,
                     const vertex &V1, const vertex &V2) {
  BRepBuilderAPI_MakeEdge me(L, S, V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge(const geom2d_curve &L, const geom_surface &S,
                     const vector3<Standard_Real> &P1,
                     const vector3<Standard_Real> &P2, const Standard_Real p1,
                     const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge me(L, S, cast_to_gp(P1), cast_to_gp(P2), p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge(const geom2d_curve &L, const geom_surface &S,
                     const vertex &V1, const vertex &V2, const Standard_Real p1,
                     const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge me(L, S, V1.value(), V2.value(), p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const vertex &V1, const vertex &V2) {
  BRepBuilderAPI_MakeEdge2d me(V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge2d(const vector2<Standard_Real> &P1,
                       const vector2<Standard_Real> &P2) {
  BRepBuilderAPI_MakeEdge2d me(cast_to_gp(P1), cast_to_gp(P2));
  return edge{me.Edge()};
}

edge edge::make_edge2d(const line2d &L) {
  BRepBuilderAPI_MakeEdge2d me(cast_to_gp(L));
  return edge{me.Edge()};
}

edge edge::make_edge2d(const line2d &L, const Standard_Real p1,
                       const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge2d me(cast_to_gp(L), p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const line2d &L, const vector2<Standard_Real> &P1,
                       const vector2<Standard_Real> &P2) {
  BRepBuilderAPI_MakeEdge2d me(cast_to_gp(L), cast_to_gp(P1), cast_to_gp(P2));
  return edge{me.Edge()};
}

edge edge::make_edge2d(const line2d &L, const vertex &V1, const vertex &V2) {
  BRepBuilderAPI_MakeEdge2d me(cast_to_gp(L), V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge2d(const circ2d &L) {
  BRepBuilderAPI_MakeEdge2d me(cast_to_gp(L));
  return edge{me.Edge()};
}

edge edge::make_edge2d(const circ2d &L, const Standard_Real p1,
                       const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge2d me(cast_to_gp(L), p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const circ2d &L, const vector2<Standard_Real> &P1,
                       const vector2<Standard_Real> &P2) {
  BRepBuilderAPI_MakeEdge2d me(cast_to_gp(L), cast_to_gp(P1), cast_to_gp(P2));
  return edge{me.Edge()};
}

edge edge::make_edge2d(const circ2d &L, const vertex &V1, const vertex &V2) {
  BRepBuilderAPI_MakeEdge2d me(cast_to_gp(L), V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge2d(const elips2d &L) {
  BRepBuilderAPI_MakeEdge2d me(cast_to_gp(L));
  return edge{me.Edge()};
}

edge edge::make_edge2d(const elips2d &L, const Standard_Real p1,
                       const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge2d me(cast_to_gp(L), p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const elips2d &L, const vector2<Standard_Real> &P1,
                       const vector2<Standard_Real> &P2) {
  BRepBuilderAPI_MakeEdge2d me(cast_to_gp(L), cast_to_gp(P1), cast_to_gp(P2));
  return edge{me.Edge()};
}

edge edge::make_edge2d(const elips2d &L, const vertex &V1, const vertex &V2) {
  BRepBuilderAPI_MakeEdge2d me(cast_to_gp(L), V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge2d(const hyperbola2d &L) {
  BRepBuilderAPI_MakeEdge2d me(cast_to_gp(L));
  return edge{me.Edge()};
}

edge edge::make_edge2d(const hyperbola2d &L, const Standard_Real p1,
                       const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge2d me(cast_to_gp(L), p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const hyperbola2d &L, const vector2<Standard_Real> &P1,
                       const vector2<Standard_Real> &P2) {
  BRepBuilderAPI_MakeEdge2d me(cast_to_gp(L), cast_to_gp(P1), cast_to_gp(P2));
  return edge{me.Edge()};
}

edge edge::make_edge2d(const hyperbola2d &L, const vertex &V1,
                       const vertex &V2) {
  BRepBuilderAPI_MakeEdge2d me(cast_to_gp(L), V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge2d(const parabola2d &L) {
  BRepBuilderAPI_MakeEdge2d me(cast_to_gp(L));
  return edge{me.Edge()};
}

edge edge::make_edge2d(const parabola2d &L, const Standard_Real p1,
                       const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge2d me(cast_to_gp(L), p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const parabola2d &L, const vector2<Standard_Real> &P1,
                       const vector2<Standard_Real> &P2) {
  BRepBuilderAPI_MakeEdge2d me(cast_to_gp(L), cast_to_gp(P1), cast_to_gp(P2));
  return edge{me.Edge()};
}

edge edge::make_edge2d(const parabola2d &L, const vertex &V1,
                       const vertex &V2) {
  BRepBuilderAPI_MakeEdge2d me(cast_to_gp(L), V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge2d(const geom2d_curve &L) {
  BRepBuilderAPI_MakeEdge2d me(L);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const geom2d_curve &L, const Standard_Real p1,
                       const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge2d me(L, p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const geom2d_curve &L, const vector2<Standard_Real> &P1,
                       const vector2<Standard_Real> &P2) {
  BRepBuilderAPI_MakeEdge2d me(L, cast_to_gp(P1), cast_to_gp(P2));
  return edge{me.Edge()};
}

edge edge::make_edge2d(const geom2d_curve &L, const vertex &V1,
                       const vertex &V2) {
  BRepBuilderAPI_MakeEdge2d me(L, V1.value(), V2.value());
  return edge{me.Edge()};
}

edge edge::make_edge2d(const geom2d_curve &L, const vector2<Standard_Real> &P1,
                       const vector2<Standard_Real> &P2, const Standard_Real p1,
                       const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge2d me(L, cast_to_gp(P1), cast_to_gp(P2), p1, p2);
  return edge{me.Edge()};
}

edge edge::make_edge2d(const geom2d_curve &L, const vertex &V1,
                       const vertex &V2, const Standard_Real p1,
                       const Standard_Real p2) {
  BRepBuilderAPI_MakeEdge2d me(L, V1.value(), V2.value(), p1, p2);
  return edge{me.Edge()};
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

bool edge::is_inifinite() const {
  return value().Infinite();
}

bool edge::is_curve3d() const { return BRep_Tool::IsGeometric(value()); }

int edge::num_vertices() const {
  TopTools_IndexedMapOfShape anIndices;
  TopExp::MapShapes(value(), TopAbs_VERTEX, anIndices);
  return anIndices.Extent();
}

double edge::length() const {
  GProp_GProps prop;
  BRepGProp::LinearProperties(value(), prop);
  return prop.Mass();
}

float edge::tolerance() const {
  return BRep_Tool::Tolerance(value());
}

void edge::convert_to_curve3d() { BRepLib::BuildCurve3d(value()); }

} // namespace topo
} // namespace flywave
