// Direct test of OpenCASCADE 3D primitive APIs, bypassing workplane
#include <iostream>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>
#include <gp_Pnt.hxx>
#include <gp_Ax2.hxx>

static int pass = 0, fail = 0;
#define CHECK(name, expr) do { \
  try { expr; std::cout << "  " << name << "... ok" << std::endl; pass++; } \
  catch (const std::exception &e) { std::cout << "  " << name << "... FAIL: " << e.what() << std::endl; fail++; } \
  catch (...) { std::cout << "  " << name << "... FAIL: unknown exception" << std::endl; fail++; } \
} while(0)

int main() {
  std::cout << "=== OpenCASCADE Raw Primitive Tests ===" << std::endl;

  std::cout << "\n--- 2D primitives (wire/edge) ---" << std::endl;
  CHECK("make_edge", {
    auto e = BRepBuilderAPI_MakeEdge(gp_Pnt(0,0,0), gp_Pnt(10,0,0));
    TopoDS_Edge edge = e.Edge();
  });
  CHECK("make_wire", {
    auto e1 = BRepBuilderAPI_MakeEdge(gp_Pnt(0,0,0), gp_Pnt(10,0,0)).Edge();
    auto e2 = BRepBuilderAPI_MakeEdge(gp_Pnt(10,0,0), gp_Pnt(10,10,0)).Edge();
    auto w = BRepBuilderAPI_MakeWire(e1, e2).Wire();
  });
  CHECK("make_face", {
    auto e1 = BRepBuilderAPI_MakeEdge(gp_Pnt(0,0,0), gp_Pnt(10,0,0)).Edge();
    auto e2 = BRepBuilderAPI_MakeEdge(gp_Pnt(10,0,0), gp_Pnt(10,10,0)).Edge();
    auto e3 = BRepBuilderAPI_MakeEdge(gp_Pnt(10,10,0), gp_Pnt(0,10,0)).Edge();
    auto e4 = BRepBuilderAPI_MakeEdge(gp_Pnt(0,10,0), gp_Pnt(0,0,0)).Edge();
    auto w = BRepBuilderAPI_MakeWire(e1, e2, e3, e4).Wire();
    auto f = BRepBuilderAPI_MakeFace(w).Face();
  });

  std::cout << "\n--- 3D primitives (BRepPrimAPI) ---" << std::endl;
  CHECK("make_box", {
    auto b = BRepPrimAPI_MakeBox(gp_Pnt(0,0,0), 10.0, 20.0, 30.0);
    TopoDS_Shape s = b.Shape();
  });
  CHECK("make_box_ax2", {
    auto b = BRepPrimAPI_MakeBox(gp_Ax2(gp_Pnt(0,0,0), gp_Dir(0,0,1)), 10.0, 20.0, 30.0);
    TopoDS_Shape s = b.Shape();
  });
  CHECK("make_sphere", {
    auto s = BRepPrimAPI_MakeSphere(gp_Pnt(0,0,0), 10.0);
    TopoDS_Shape sh = s.Shape();
  });
  CHECK("make_cylinder", {
    auto c = BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0,0,0), gp_Dir(0,0,1)), 5.0, 20.0);
    TopoDS_Shape s = c.Shape();
  });

  std::cout << "\n--- 2D->3D operations ---" << std::endl;
  CHECK("make_prism", {
    auto e1 = BRepBuilderAPI_MakeEdge(gp_Pnt(0,0,0), gp_Pnt(10,0,0)).Edge();
    auto e2 = BRepBuilderAPI_MakeEdge(gp_Pnt(10,0,0), gp_Pnt(10,10,0)).Edge();
    auto e3 = BRepBuilderAPI_MakeEdge(gp_Pnt(10,10,0), gp_Pnt(0,10,0)).Edge();
    auto e4 = BRepBuilderAPI_MakeEdge(gp_Pnt(0,10,0), gp_Pnt(0,0,0)).Edge();
    auto w = BRepBuilderAPI_MakeWire(e1, e2, e3, e4).Wire();
    auto f = BRepBuilderAPI_MakeFace(w).Face();
    gp_Vec vec(0, 0, 20);
    auto prism = BRepPrimAPI_MakePrism(f, vec);
    TopoDS_Shape s = prism.Shape();
  });

  std::cout << "\n=== Results: " << (pass+fail) << " tests, "
            << pass << " passed, " << fail << " failed ===" << std::endl;
  return fail > 0 ? 1 : 0;
}
