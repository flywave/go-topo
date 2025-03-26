#include <BRepBuilderAPI_Copy.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepFilletAPI_MakeFillet2d.hxx>
#include <BRepGProp.hxx>
#include <BRepLib.hxx>
#include <BRepOffsetAPI_MakeOffset.hxx>
#include <BRepOffsetAPI_NormalProjection.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <GProp_GProps.hxx>
#include <Precision.hxx>
#include <ShapeAnalysis_FreeBounds.hxx>
#include <TopExp.hxx>
#include <TopTools_HSequenceOfShape.hxx>
#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopoDS.hxx>

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

int wire::num_vertices() const {
  TopTools_IndexedMapOfShape anIndices;
  TopExp::MapShapes(value(), TopAbs_VERTEX, anIndices);
  return anIndices.Extent();
}

int wire::num_edges() const {
  TopTools_IndexedMapOfShape anIndices;
  TopExp::MapShapes(value(), TopAbs_EDGE, anIndices);
  return anIndices.Extent();
}

bool wire::is_closed() const {
  TopoDS_Vertex aV1, aV2;
  TopExp::Vertices(value(), aV1, aV2);
  if (!aV1.IsNull() && !aV2.IsNull() && aV1.IsSame(aV2))
    return true;
  return false;
}

double wire::length() const {
  GProp_GProps prop;
  BRepGProp::LinearProperties(value(), prop);
  return prop.Mass();
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

int wire::offset(double distance, int joinType) {
  Handle(TopTools_HSequenceOfShape) wires = new TopTools_HSequenceOfShape;
  Handle(TopTools_HSequenceOfShape) edges = new TopTools_HSequenceOfShape;
  TopExp_Explorer ex;

  try {
    GeomAbs_JoinType join = GeomAbs_Arc;
    switch (joinType) {
    case 1:
      join = GeomAbs_Tangent;
      break;
    case 2:
      join = GeomAbs_Intersection;
      break;
    }
    BRepOffsetAPI_MakeOffset MO(value(), join);
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
  int vertices_size = vertices.size();
  int radius_size = radius.size();

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
  int vertices_size = vertices.size();
  int distances_size = distances.size();

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

} // namespace topo
} // namespace flywave
