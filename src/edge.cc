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

edge edge::make_polygon(std::vector<vertex*> &vertexs, const bool Close) {
  BRepBuilderAPI_MakePolygon me;
  for (auto _vert : vertexs) {
    me.Add(_vert->value());
  }
  if (Close) {
    me.Close();
  }
  return edge{me.Edge()};
}

edge edge::make_polygon(std::initializer_list<vertex*> vertexs,
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

float edge::tolerance() const { return BRep_Tool::Tolerance(value()); }

void edge::convert_to_curve3d() { BRepLib::BuildCurve3d(value()); }

} // namespace topo
} // namespace flywave
