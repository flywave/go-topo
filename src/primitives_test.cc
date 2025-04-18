#include "primitives.hh"
#include <BRepMesh_IncrementalMesh.hxx>
#include <Interface_Static.hxx>
#include <Message_ProgressRange.hxx>
#include <RWGltf_CafWriter.hxx>
#include <STEPCAFControl_Writer.hxx>
#include <StlAPI.hxx>
#include <StlAPI_Writer.hxx>
#include <TColStd_IndexedDataMapOfStringString.hxx>
#include <TCollection_AsciiString.hxx>
#include <TDocStd_Document.hxx>
#include <TopoDS_Shape.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <gp_Ax1.hxx>
#include <gp_Dir.hxx>
#include <gp_Pnt.hxx>
#include <gp_Trsf.hxx>

#include <boost/optional.hpp>

using namespace flywave::topo;

bool exportShapeToStl(const TopoDS_Shape &shape, const std::string &path,
                      double tolerance = 0.5, double angularTolerance = 0.3) {
  // 检查输入形状是否有效
  if (shape.IsNull()) {
    return false;
  }

  // 对形状进行网格化（三角剖分）
  BRepMesh_IncrementalMesh mesher(shape, tolerance, false, angularTolerance);
  mesher.Perform();

  // 创建 STL 写入器
  StlAPI_Writer stlWriter;

  // 执行导出
  bool success = stlWriter.Write(shape, path.c_str());

  return success;
}

bool test_export_shape(const TopoDS_Shape &shape, const std::string &filename) {
  std::cout << "Exporting " << filename << "... ";
  bool result = exportShapeToStl(shape, filename);
  if (result) {
    std::cout << "Success" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }
  return result;
}

void test_make_sphere() {
  std::cout << "=== Testing Sphere ===" << std::endl;
  auto shp = create_sphere(sphere_params{.radius = 20});
  if (shp.IsNull()) {
    std::cerr << "Error: Failed to create sphere" << std::endl;
    return;
  }
  test_export_shape(shp, "./sphere.stl");
}

void test_make_rotational_ellipsoid() {
  std::cout << "\n=== Testing Rotational Ellipsoid ===" << std::endl;
  try {
    auto shp = create_rotational_ellipsoid(rotational_ellipsoid_params{
        .polarRadius = 5,
        .equatorialRadius = 3, // 小于极半径
        .height = 6            // 等于极半径，生成上半部分
    });
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create rotational ellipsoid" << std::endl;
      return;
    }
    test_export_shape(shp, "./rotational_ellipsoid.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_diamond_frustum() {
  std::cout << "\n=== Testing Diamond Frustum ===" << std::endl;
  try {
    auto shp = create_diamond_frustum(diamond_frustum{
        .topDiag1 = 10.0,    // 顶面第一条对角线长度
        .topDiag2 = 7.5,     // 顶面第二条对角线长度
        .bottomDiag1 = 20.0, // 底面第一条对角线长度
        .bottomDiag2 = 15.0, // 底面第二条对角线长度
        .height = 12.0       // 高度
    });
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create diamond frustum" << std::endl;
      return;
    }
    test_export_shape(shp, "./diamond_frustum.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_offset_rectangular_table() {
  std::cout << "\n=== Testing Offset Rectangular Table ===" << std::endl;
  try {
    auto shp = create_offset_rectangular_table(offset_rectangular_table_params{
        .topLength = 15.0,    // 上部矩形长度
        .topWidth = 10.0,     // 上部矩形宽度
        .bottomLength = 20.0, // 下部矩形长度
        .bottomWidth = 12.0,  // 下部矩形宽度
        .height = 8.0,        // 高度
        .xOffset = 2.0,       // X方向偏移
        .yOffset = 1.5        // Y方向偏移
    });
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create offset rectangular table"
                << std::endl;
      return;
    }
    test_export_shape(shp, "./offset_rectangular_table.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_cylinder() {
  std::cout << "\n=== Testing Cylinder ===" << std::endl;
  auto shp = create_cylinder(cylinder_params{.radius = 15, .height = 25});
  if (shp.IsNull()) {
    std::cerr << "Error: Failed to create cylinder" << std::endl;
    return;
  }
  test_export_shape(shp, "./cylinder.stl");
}

void test_make_sharp_bent_cylinder() {
  std::cout << "\n=== Testing Sharp Bent Cylinder ===" << std::endl;
  try {
    // 测试默认参数创建
    auto shp = create_sharp_bent_cylinder(sharp_bent_cylinder_params{
        .radius = 5.0, .length = 70.0, .bendAngle = M_PI / 4});
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create sharp bent cylinder" << std::endl;
      return;
    }
    test_export_shape(shp, "./sharp_bent_cylinder.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_truncated_cone() {
  std::cout << "\n=== Testing Truncated Cone ===" << std::endl;
  try {
    // 测试默认参数创建
    auto shp = create_truncated_cone(truncated_cone_params{
        .topRadius = 5.0, .bottomRadius = 10.0, .height = 15.0});
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create truncated cone" << std::endl;
      return;
    }
    test_export_shape(shp, "./truncated_cone.stl");

    // 测试极端参数情况
    auto shp2 = create_truncated_cone(truncated_cone_params{
        .topRadius = 0.1, .bottomRadius = 20.0, .height = 30.0});
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create extreme truncated cone"
                << std::endl;
      return;
    }
    test_export_shape(shp2, "./truncated_cone_extreme.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_eccentric_truncated_cone() {
  std::cout << "\n=== Testing Eccentric Truncated Cone ===" << std::endl;
  try {
    // 测试默认参数创建
    auto shp = create_eccentric_truncated_cone(
        eccentric_truncated_cone_params{.topRadius = 5.0,
                                        .bottomRadius = 10.0,
                                        .height = 15.0,
                                        .topXOffset = 2.0,
                                        .topYOffset = 3.0});
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create eccentric truncated cone"
                << std::endl;
      return;
    }
    test_export_shape(shp, "./eccentric_truncated_cone.stl");

    // 测试极端参数情况
    auto shp2 = create_eccentric_truncated_cone(
        eccentric_truncated_cone_params{.topRadius = 1.0,
                                        .bottomRadius = 20.0,
                                        .height = 30.0,
                                        .topXOffset = 5.0,
                                        .topYOffset = 8.0});
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create extreme eccentric truncated cone"
                << std::endl;
      return;
    }
    test_export_shape(shp2, "./eccentric_truncated_cone_extreme.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_ring() {
  std::cout << "\n=== Testing Ring ===" << std::endl;
  try {
    // 测试默认参数创建
    auto shp = create_ring(ring_params{
        .ringRadius = 20.0, .tubeRadius = 5.0, .angle = M_PI * 1.5});
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create ring" << std::endl;
      return;
    }
    test_export_shape(shp, "./ring.stl");

    // 测试完整圆环
    auto shp2 = create_ring(ring_params{
        .ringRadius = 15.0, .tubeRadius = 3.0, .angle = M_PI * 2.0});
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create full ring" << std::endl;
      return;
    }
    test_export_shape(shp2, "./full_ring.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_rectangular_ring() {
  std::cout << "\n=== Testing Rectangular Ring ===" << std::endl;
  try {
    // 测试默认参数创建
    auto shp =
        create_rectangular_ring(rectangular_ring_params{.tubeRadius = 5.0,
                                                        .filletRadius = 5.0,
                                                        .length = 100.0,
                                                        .width = 50.0});
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create rectangular ring" << std::endl;
      return;
    }
    test_export_shape(shp, "./rectangular_ring.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_elliptic_ring() {
  std::cout << "\n=== Testing Elliptic Ring ===" << std::endl;
  try {
    // 测试默认参数创建
    auto shp = create_elliptic_ring(elliptic_ring_params{
        .tubeRadius = 3.0, .majorRadius = 20.0, .minorRadius = 10.0});
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create elliptic ring" << std::endl;
      return;
    }
    test_export_shape(shp, "./elliptic_ring.stl");

    // 测试极端参数情况
    auto shp2 = create_elliptic_ring(elliptic_ring_params{
        .tubeRadius = 1.0, .majorRadius = 30.0, .minorRadius = 5.0});
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create extreme elliptic ring" << std::endl;
      return;
    }
    test_export_shape(shp2, "./elliptic_ring_extreme.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_circular_gasket() {
  std::cout << "\n=== Testing Circular Gasket ===" << std::endl;
  try {
    // 测试默认参数创建
    auto shp =
        create_circular_gasket(circular_gasket_params{.outerRadius = 20.0,
                                                      .innerRadius = 15.0,
                                                      .height = 5.0,
                                                      .angle = M_PI * 1.5});
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create circular gasket" << std::endl;
      return;
    }
    test_export_shape(shp, "./circular_gasket.stl");

    // 测试完整圆形垫片
    auto shp2 =
        create_circular_gasket(circular_gasket_params{.outerRadius = 25.0,
                                                      .innerRadius = 20.0,
                                                      .height = 8.0,
                                                      .angle = M_PI * 2.0});
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create full circular gasket" << std::endl;
      return;
    }
    test_export_shape(shp2, "./full_circular_gasket.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_table_gasket() {
  std::cout << "\n=== Testing Table Gasket ===" << std::endl;
  try {
    // 测试默认参数创建
    auto shp = create_table_gasket(table_gasket_params{.topRadius = 15.0,
                                                       .outerRadius = 20.0,
                                                       .innerRadius = 10.0,
                                                       .height = 6.0,
                                                       .angle = M_PI * 1.5});
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create table gasket" << std::endl;
      return;
    }
    test_export_shape(shp, "./table_gasket.stl");

    // 测试完整圆形台型垫片
    auto shp2 = create_table_gasket(table_gasket_params{.topRadius = 18.0,
                                                        .outerRadius = 25.0,
                                                        .innerRadius = 12.0,
                                                        .height = 8.0,
                                                        .angle = M_PI * 2.0});
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create full table gasket" << std::endl;
      return;
    }
    test_export_shape(shp2, "./full_table_gasket.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_square_gasket() {
  std::cout << "\n=== Testing Square Gasket ===" << std::endl;
  try {
    // 测试默认参数创建
    auto shp = create_square_gasket(square_gasket_params{.outerLength = 30.0,
                                                         .outerWidth = 20.0,
                                                         .innerLength = 25.0,
                                                         .innerWidth = 15.0,
                                                         .height = 5.0,
                                                         .cornerType = 1,
                                                         .cornerParam = 0});
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create square gasket" << std::endl;
      return;
    }
    test_export_shape(shp, "./square_gasket.stl");

    // 测试极端参数情况
    auto shp2 = create_square_gasket(square_gasket_params{
        .outerLength = 40.0,
        .outerWidth = 30.0,
        .innerLength = 15.0,
        .innerWidth = 10.0,
        .height = 8.0,
        .cornerType = 2,   //  圆形角点
        .cornerParam = 3.0 // 圆角半径
    });
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create round square gasket" << std::endl;
      return;
    }
    test_export_shape(shp2, "./square_gasket_round.stl");

    // 测试极端参数情况
    auto shp3 = create_square_gasket(square_gasket_params{
        .outerLength = 40.0,
        .outerWidth = 30.0,
        .innerLength = 15.0,
        .innerWidth = 10.0,
        .height = 8.0,
        .cornerType = 3,   //  圆形角点
        .cornerParam = 5.0 // 圆角半径
    });
    if (shp3.IsNull()) {
      std::cerr << "Error: Failed to create cut square gasket" << std::endl;
      return;
    }
    test_export_shape(shp3, "./square_gasket_cut.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_stretched_body() {
  std::cout << "\n=== Testing Stretched Body ===" << std::endl;
  try {
    // 测试默认参数创建 - 三角形拉伸体
    auto shp = create_stretched_body(stretched_body_params{
        .points = {gp_Pnt(0, 0, 0), gp_Pnt(10, 0, 0), gp_Pnt(5, 8, 0)},
        .normal = gp_Dir(0, 0, 1),
        .length = 15.0});
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create stretched body" << std::endl;
      return;
    }
    test_export_shape(shp, "./stretched_body_triangle.stl");

    // 测试四边形拉伸体
    auto shp2 = create_stretched_body(stretched_body_params{
        .points = {gp_Pnt(0, 0, 0), gp_Pnt(20, 0, 0), 
                  gp_Pnt(20, 10, 0), gp_Pnt(0, 10, 0)},
        .normal = gp_Dir(0, 1, 1),
        .length = 25.0});
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create quadrilateral stretched body" << std::endl;
      return;
    }
    test_export_shape(shp2, "./stretched_body_quadrilateral.stl");

    // 测试五边形拉伸体
    auto shp3 = create_stretched_body(stretched_body_params{
        .points = {gp_Pnt(0, 0, 0), gp_Pnt(15, 0, 0), gp_Pnt(20, 10, 0),
                  gp_Pnt(10, 15, 0), gp_Pnt(-5, 8, 0)},
        .normal = gp_Dir(1, 0, 1),
        .length = 12.0});
    if (shp3.IsNull()) {
      std::cerr << "Error: Failed to create pentagon stretched body" << std::endl;
      return;
    }
    test_export_shape(shp3, "./stretched_body_pentagon.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}


void test_make_porcelain_bushing() {
  std::cout << "\n=== Testing Porcelain Bushing ===" << std::endl;
  try {
    // 测试默认参数创建 - 标准尺寸瓷套管
    auto shp = create_porcelain_bushing(porcelain_bushing_params{
        .height = 100.0,
        .radius = 10.0,
        .bigSkirtRadius = 15.0,
        .smallSkirtRadius = 12.0,
        .count = 20});
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create standard porcelain bushing" << std::endl;
      return;
    }
    test_export_shape(shp, "./porcelain_bushing_standard.stl");
/**
    // 测试大伞裙瓷套管
    auto shp2 = create_porcelain_bushing(porcelain_bushing_params{
        .height = 120.0,
        .radius = 8.0,
        .bigSkirtRadius = 20.0,
        .smallSkirtRadius = 15.0,
        .count = 7});
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create large skirt porcelain bushing" << std::endl;
      return;
    }
    test_export_shape(shp2, "./porcelain_bushing_large_skirt.stl");

    // 测试小伞裙瓷套管
    auto shp3 = create_porcelain_bushing(porcelain_bushing_params{
        .height = 80.0,
        .radius = 6.0,
        .bigSkirtRadius = 10.0,
        .smallSkirtRadius = 8.0,
        .count = 3});
    if (shp3.IsNull()) {
      std::cerr << "Error: Failed to create small skirt porcelain bushing" << std::endl;
      return;
    }
    test_export_shape(shp3, "./porcelain_bushing_small_skirt.stl");

    // 测试极端参数情况 - 超高瓷套管
    auto shp4 = create_porcelain_bushing(porcelain_bushing_params{
        .height = 200.0,
        .radius = 12.0,
        .bigSkirtRadius = 25.0,
        .smallSkirtRadius = 20.0,
        .count = 10});
    if (shp4.IsNull()) {
      std::cerr << "Error: Failed to create extreme height porcelain bushing" << std::endl;
      return;
    }
    test_export_shape(shp4, "./porcelain_bushing_extreme_height.stl");
 */
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

int main() {
  test_make_sphere();
  test_make_rotational_ellipsoid();
  test_make_diamond_frustum();
  test_make_offset_rectangular_table();
  test_make_cylinder();
  test_make_sharp_bent_cylinder();
  test_make_truncated_cone();
  test_make_eccentric_truncated_cone();
  test_make_ring();
  test_make_rectangular_ring();
  test_make_elliptic_ring();
  test_make_circular_gasket();
  test_make_table_gasket();
  test_make_square_gasket();
  test_make_stretched_body();
  test_make_porcelain_bushing();
  return 0;
}
