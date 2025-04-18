#include "vertex.hh"
#include <BRepBuilderAPI_Copy.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRep_Tool.hxx>
#include <Standard_Failure.hxx>
#include <TopoDS.hxx>

namespace flywave {
namespace topo {

vertex::vertex(Standard_Real x, Standard_Real y, Standard_Real z) {
  gp_Pnt aPnt;
  aPnt = gp_Pnt(x, y, z);
  BRepBuilderAPI_MakeVertex mkVertex(aPnt);
  _shape = mkVertex.Vertex();
}

vertex::vertex(const gp_Pnt &P) : vertex(P.X(), P.Y(), P.Z()) {}

TopoDS_Vertex &vertex::value() { return TopoDS::Vertex(_shape); }

const TopoDS_Vertex &vertex::value() const { return TopoDS::Vertex(_shape); }

shape vertex::copy(bool deep) const {
  try {
    BRepBuilderAPI_Copy _copy(_shape, deep);
    _copy.Build();

    if (!_copy.IsDone())
      throw std::runtime_error("Section operation failed");

    auto shp = _copy.Shape();

    if (shp.IsNull())
      throw std::runtime_error("Shell operation resulted in Null shape");

    return vertex{shp};
  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
  }
  return vertex{};
}

vertex vertex::make_vertex(const gp_Pnt &P) {
  BRepBuilderAPI_MakeVertex mkVertex(P);
  return vertex{mkVertex.Vertex()};
}
vertex vertex::make_vertex(const gp_Vec &P) {
  BRepBuilderAPI_MakeVertex mkVertex(gp_Pnt(P.X(), P.Y(), P.Z()));
  return vertex{mkVertex.Vertex()};
}

vertex::operator const gp_Pnt() const {
  gp_Pnt pnt = BRep_Tool::Pnt(value());
  return {pnt.X(), pnt.Y(), pnt.Z()};
}

gp_Pnt vertex::point() const {
  gp_Pnt pnt = BRep_Tool::Pnt(value()); 
  return {pnt.X(), pnt.Y(), pnt.Z()};
}

} // namespace topo
} // namespace flywave
