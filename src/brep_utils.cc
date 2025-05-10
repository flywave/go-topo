#include "brep_utils.hh"
#include "version.hh"

#include "tkernel_utils.hh"
#if OCC_VERSION_HEX >= OCC_VERSION_CHECK(7, 5, 0)
#include "progress_indicator.hh"
#endif

#include <BRepMesh_IncrementalMesh.hxx>
#include <BRepTools.hxx>
#include <BRep_Builder.hxx>
#include <BRep_Tool.hxx>
#include <TopoDS_Compound.hxx>
#include <climits>
#include <sstream>

namespace flywave {

TopoDS_Compound brep_utils::make_empty_compound() {
  TopoDS_Builder builder;
  TopoDS_Compound comp;
  builder.MakeCompound(comp);
  return comp;
}

void brep_utils::add_shape(TopoDS_Shape *ptrTargetShape,
                           const TopoDS_Shape &shape) {
  TopoDS_Builder builder;
  builder.Add(*ptrTargetShape, shape);
}

TopoDS_Edge brep_utils::make_edge(const ogg_handle<Poly_Polygon3D> &polygon) {
  TopoDS_Edge edge;
  BRep_Builder builder;
  builder.MakeEdge(edge);
  builder.UpdateEdge(edge, polygon);
  return edge;
}

TopoDS_Face brep_utils::make_face(const ogg_handle<Poly_Triangulation> &mesh) {
  TopoDS_Face face;
  BRep_Builder builder;
  builder.MakeFace(face);
  builder.UpdateFace(face, mesh);
  return face;
}

bool brep_utils::more_complex(TopAbs_ShapeEnum lhs, TopAbs_ShapeEnum rhs) {
  return lhs < rhs;
}

size_t brep_utils::hash_code(const TopoDS_Shape &shape) {
#if OCC_VERSION_HEX >= OCC_VERSION_CHECK(7, 8, 0)
  return std::hash<TopoDS_Shape>{}(shape);
#else
  return shape.HashCode(INT_MAX);
#endif
}

std::string brep_utils::shape_to_string(const TopoDS_Shape &shape) {
  std::ostringstream oss(std::ios_base::out);
  BRepTools::Write(shape, oss);
  return oss.str();
}

TopoDS_Shape brep_utils::shape_from_string(const std::string &str) {
  TopoDS_Shape shape;
  BRep_Builder brepBuilder;
  std::istringstream iss(str, std::ios_base::in);
  BRepTools::Read(shape, iss, brepBuilder);
  return shape;
}

bool brep_utils::is_geometric(const TopoDS_Edge &edge) {
  return BRep_Tool::IsGeometric(edge);
}

bool brep_utils::is_geometric(const TopoDS_Face &face) {
#if OCC_VERSION_HEX >= OCC_VERSION_CHECK(7, 5, 0)
  return BRep_Tool::IsGeometric(face);
#else
  auto tface = static_cast<const BRep_TFace *>(face.TShape().get());
  return !tface->Surface().IsNull();
#endif
}

void brep_utils::compute_mesh(const TopoDS_Shape &shape,
                              const brep_mesh_parameters &params) {
#if OCC_VERSION_HEX >= OCC_VERSION_CHECK(7, 5, 0)
  auto indicator = make_ogg_handle<progress_indicator>();
  BRepMesh_IncrementalMesh mesher(shape, params,
                                  kernel_utils::start(indicator));
#else
  BRepMesh_IncrementalMesh mesher(shape, params);
#endif
}

} // namespace flywave
