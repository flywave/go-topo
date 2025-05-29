#include <BRepAdaptor_Curve.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_Sewing.hxx>
#include <BRepLib.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepTools.hxx>
#include <BRep_Tool.hxx>
#include <GCPnts_UniformAbscissa.hxx>
#include <GeomAPI_ExtremaCurveCurve.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Plane.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>
#include <Geom_Surface.hxx>
#include <Poly_Triangulation.hxx>
#include <Precision.hxx>
#include <ShapeFix_Shape.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS_Wire.hxx>
#include <algorithm>
#include <gp_Dir.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>
#include <gp_XYZ.hxx>
#include <math_Jacobi.hxx>
#include <math_Matrix.hxx>
#include <vector>

// 边界管道结构
struct BoundPipeSection {
  gp_Pnt center;    // 截面中心点
  double radius;    // 截面半径
  gp_Dir direction; // 截面方向（管道轴线方向）
};

struct BoundPipe {
  std::vector<BoundPipeSection> sections; // 管道截面序列
  Handle(Geom_Curve) centerline;          // 管道中心线
};

// 创建边界管道形状
TopoDS_Shape CreateBoundPipeShape(const BoundPipe &boundPipe) {
  if (boundPipe.sections.empty() || boundPipe.centerline.IsNull()) {
    return TopoDS_Shape();
  }

  // 1. 创建截面轮廓
  TopoDS_Wire wire;
  BRepBuilderAPI_MakeWire wireMaker;

  for (size_t i = 0; i < boundPipe.sections.size(); ++i) {
    const auto &section = boundPipe.sections[i];
    gp_Ax2 axis(section.center, section.direction);
    Handle(Geom_Circle) circle = new Geom_Circle(axis, section.radius);
    TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(circle);
    wireMaker.Add(edge);
  }

  if (!wireMaker.IsDone()) {
    return TopoDS_Shape();
  }
  wire = wireMaker.Wire();

  BRepBuilderAPI_MakeEdge edgeMaker1(boundPipe.centerline);
  auto path = BRepBuilderAPI_MakeWire(edgeMaker1.Edge()).Wire();
  // 2. 创建放样曲面
  BRepOffsetAPI_MakePipeShell pipeMaker(path);
  pipeMaker.Add(wire);
  if (!pipeMaker.IsDone()) {
    return TopoDS_Shape();
  }

  // 3. 创建端面
  TopoDS_Shape pipeShape = pipeMaker.Shape();

  // 4. 修复形状
  ShapeFix_Shape fixer(pipeShape);
  fixer.Perform();
  return fixer.Shape();
}