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
    auto shp2 = create_stretched_body(
        stretched_body_params{.points = {gp_Pnt(0, 0, 0), gp_Pnt(20, 0, 0),
                                         gp_Pnt(20, 10, 0), gp_Pnt(0, 10, 0)},
                              .normal = gp_Dir(0, 1, 1),
                              .length = 25.0});
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create quadrilateral stretched body"
                << std::endl;
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
      std::cerr << "Error: Failed to create pentagon stretched body"
                << std::endl;
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
    auto shp = create_porcelain_bushing(
        porcelain_bushing_params{.height = 100.0,
                                 .radius = 10.0,
                                 .bigSkirtRadius = 15.0,
                                 .smallSkirtRadius = 12.0,
                                 .count = 20});
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create standard porcelain bushing"
                << std::endl;
      return;
    }
    test_export_shape(shp, "./porcelain_bushing_standard.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_cone_porcelain_bushing() {
  std::cout << "\n=== Testing Cone Porcelain Bushing ===" << std::endl;
  try {
    // 测试默认参数创建 - 标准尺寸锥形瓷套管
    auto shp = create_cone_porcelain_bushing(
        cone_porcelain_bushing_params{.height = 100.0,
                                      .bottomRadius = 15.0,
                                      .topRadius = 10.0,
                                      .bottomSkirtRadius1 = 20.0,
                                      .bottomSkirtRadius2 = 18.0,
                                      .topSkirtRadius1 = 15.0,
                                      .topSkirtRadius2 = 12.0,
                                      .count = 20});
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create standard cone porcelain bushing"
                << std::endl;
      return;
    }
    test_export_shape(shp, "./cone_porcelain_bushing.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_insulator_string() {
  std::cout << "\n=== Testing Insulator String ===" << std::endl;
  try {
    // 测试默认参数创建 - 标准绝缘子串
    auto shp =
        create_insulator_string(insulator_string_params{.count = 2,
                                                        .spacing = 30.0,
                                                        .insulatorCount = 10,
                                                        .height = 5.0,
                                                        .bigSkirtRadius = 8.0,
                                                        .smallSkirtRadius = 6.0,
                                                        .radius = 4.0,
                                                        .frontLength = 15.0,
                                                        .backLength = 10.0,
                                                        .splitCount = 2});
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create standard insulator string"
                << std::endl;
      return;
    }
    test_export_shape(shp, "./insulator_string_standard.stl");

    // 测试单联绝缘子串
    auto shp2 =
        create_insulator_string(insulator_string_params{.count = 1,
                                                        .spacing = 0.0,
                                                        .insulatorCount = 8,
                                                        .height = 4.0,
                                                        .bigSkirtRadius = 7.0,
                                                        .smallSkirtRadius = 5.0,
                                                        .radius = 3.5,
                                                        .frontLength = 6.0,
                                                        .backLength = 5.0,
                                                        .splitCount = 2});
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create single insulator string"
                << std::endl;
      return;
    }
    test_export_shape(shp2, "./insulator_string_single.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_vtype_insulator() {
  std::cout << "\n=== Testing V-Type Insulator ===" << std::endl;
  try {
    // 测试标准V型绝缘子串
    auto shp = create_vtype_insulator(vtype_insulator_params{
        .frontSpacing = 30.0,    // 前端间距
        .backSpacing = 20.0,     // 后端间距
        .insulatorCount = 8,     // 每串绝缘子片数
        .height = 5.0,           // 单片高度
        .radius = 3.0,           // 绝缘子半径
        .bigSkirtRadius = 6.0,   // 大伞半径
        .smallSkirtRadius = 5.0, // 小伞半径
        .frontLength = 10.0,     // 构架端长度
        .backLength = 8.0,       // 导线端长度
        .splitCount = 2          // 分裂数
    });
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create standard V-type insulator"
                << std::endl;
      return;
    }
    test_export_shape(shp, "./vtype_insulator_standard.stl");

    // 测试不同参数的V型绝缘子串
    auto shp2 = create_vtype_insulator(vtype_insulator_params{
        .frontSpacing = 40.0,    // 更大的前端间距
        .backSpacing = 15.0,     // 更小的后端间距
        .insulatorCount = 6,     // 更少的绝缘子片数
        .height = 4.0,           // 更低的单片高度
        .radius = 2.5,           // 更小的绝缘子半径
        .bigSkirtRadius = 5.0,   // 更小的大伞半径
        .smallSkirtRadius = 4.0, // 更小的小伞半径
        .frontLength = 8.0,      // 更短的构架端长度
        .backLength = 6.0,       // 更短的导线端长度
        .splitCount = 1          // 单分裂
    });
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create alternative V-type insulator"
                << std::endl;
      return;
    }
    test_export_shape(shp2, "./vtype_insulator_alternative.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_terminal_block() {
  std::cout << "\n=== Testing Terminal Block ===" << std::endl;
  try {
    auto shp = create_terminal_block(terminal_block_params{
        .length = 100.0,       // 长度
        .width = 50.0,         // 宽度
        .thickness = 10.0,     // 厚度
        .chamferLength = 5.0,  // 倒角长度
        .columnSpacing = 15.0, // 列间距
        .rowSpacing = 20.0,    // 行间距
        .holeRadius = 3.0,     // 孔半径
        .columnCount = 3,      // 列数
        .rowCount = 4,         // 行数
        .bottomOffset = 20.0,  // 底边偏移
    });
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create terminal block" << std::endl;
      return;
    }
    test_export_shape(shp, "./terminal_block.stl");

    // 测试极端参数情况
    auto shp2 =
        create_terminal_block(terminal_block_params{.length = 200.0,
                                                    .width = 30.0,
                                                    .thickness = 5.0,
                                                    .chamferLength = 1.0,
                                                    .columnSpacing = 10.0,
                                                    .rowSpacing = 15.0,
                                                    .holeRadius = 2.0,
                                                    .columnCount = 5,
                                                    .rowCount = 6,
                                                    .bottomOffset = 5.0});
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create extreme terminal block"
                << std::endl;
      return;
    }
    test_export_shape(shp2, "./terminal_block_extreme.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_rectangular_fixed_plate() {
  std::cout << "\n=== Testing Rectangular Fixed Plate ===" << std::endl;
  try {
    auto shp = create_rectangular_fixed_plate(rectangular_hole_plate_params{
        .length = 100.0,       // 长度
        .width = 80.0,         // 宽度
        .thickness = 10.0,     // 厚度
        .columnSpacing = 20.0, // 列间距
        .rowSpacing = 15.0,    // 行间距
        .columnCount = 4,      // 列数
        .rowCount = 5,         // 行数
        .hasMiddleHole = 1,    // 有中间孔
        .holeDiameter = 8.0    // 孔直径
    });
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create rectangular fixed plate"
                << std::endl;
      return;
    }
    test_export_shape(shp, "./rectangular_fixed_plate.stl");

    // 测试无中间孔的情况
    auto shp2 = create_rectangular_fixed_plate(
        rectangular_hole_plate_params{.length = 120.0,
                                      .width = 120.0,
                                      .thickness = 8.0,
                                      .columnSpacing = 25.0,
                                      .rowSpacing = 20.0,
                                      .columnCount = 3,
                                      .rowCount = 5,
                                      .hasMiddleHole = 0,
                                      .holeDiameter = 6.0});
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create rectangular fixed plate without "
                   "middle hole"
                << std::endl;
      return;
    }
    test_export_shape(shp2, "./rectangular_fixed_plate_no_middle.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_circular_fixed_plate() {
  std::cout << "\n=== Testing Circular Fixed Plate ===" << std::endl;
  try {
    // 基本测试用例 - 带中间孔
    auto shp1 = create_circular_fixed_plate(
        circular_fixed_plate_params{.length = 200.0,
                                    .width = 200.0,
                                    .thickness = 12.0,
                                    .ringRadius = 60.0,
                                    .holeCount = 8,
                                    .hasMiddleHole = 1,
                                    .holeDiameter = 15.0});

    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create circular plate with middle hole"
                << std::endl;
      return;
    }
    test_export_shape(shp1, "./circular_plate_with_middle_hole.stl");

    // 测试无中间孔的情况
    auto shp2 = create_circular_fixed_plate(
        circular_fixed_plate_params{.length = 180.0,
                                    .width = 180.0,
                                    .thickness = 10.0,
                                    .ringRadius = 50.0,
                                    .holeCount = 6,
                                    .hasMiddleHole = 0,
                                    .holeDiameter = 12.0});

    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create circular plate without middle hole"
                << std::endl;
      return;
    }
    test_export_shape(shp2, "./circular_plate_no_middle_hole.stl");

    // 极端参数测试 - 小尺寸多孔
    auto shp3 = create_circular_fixed_plate(
        circular_fixed_plate_params{.length = 100.0,
                                    .width = 100.0,
                                    .thickness = 5.0,
                                    .ringRadius = 30.0,
                                    .holeCount = 12,
                                    .hasMiddleHole = 1,
                                    .holeDiameter = 8.0});

    if (shp3.IsNull()) {
      std::cerr << "Error: Failed to create extreme circular plate"
                << std::endl;
      return;
    }
    test_export_shape(shp3, "./circular_plate_extreme.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_wire() {
  std::cout << "\n=== Testing Wire ===" << std::endl;
  try {
    // 测试直线导线
    auto shp1 = create_wire(wire_params{.startPoint = gp_Pnt(0, 0, 0),
                                        .endPoint = gp_Pnt(100, 100, 50),
                                        .startDir = gp_Dir(1, 1, 0.5),
                                        .endDir = gp_Dir(1, 1, 0.5),
                                        .sag = 10.0,
                                        .diameter = 5.0});

    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create straight wire" << std::endl;
      return;
    }
    test_export_shape(shp1, "./straight_wire.stl");

    // 测试带拟合点的曲线导线
    std::vector<gp_Pnt> fitPoints = {gp_Pnt(0, 0, 0), gp_Pnt(100, 100, 50),
                                     gp_Pnt(200, 50, 100), gp_Pnt(300, 0, 150)};

    auto shp2 = create_wire(
        wire_params{.startPoint = gp_Pnt(0, 0, 0),
                    .endPoint = gp_Pnt(300, 0, 150), // 与最后一个拟合点一致
                    .startDir = gp_Dir(1, 0, 0), // 初始方向沿X轴
                    .endDir = gp_Dir(0, 0, 1),   // 结束方向沿Z轴
                    .sag = 25.0,                 // 合理弧垂值
                    .diameter = 8.0,             // 典型导线直径
                    .fitPoints = fitPoints});

    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create curved wire" << std::endl;
      return;
    }
    test_export_shape(shp2, "./curved_wire.stl");

    // 测试极端参数 - 小直径大弧垂
    auto shp3 = create_wire(wire_params{.startPoint = gp_Pnt(0, 0, 0),
                                        .endPoint = gp_Pnt(200, 0, 0),
                                        .startDir = gp_Dir(1, 0, 0),
                                        .endDir = gp_Dir(1, 0, 0),
                                        .sag = 50.0,
                                        .diameter = 2.0});

    if (shp3.IsNull()) {
      std::cerr << "Error: Failed to create extreme wire" << std::endl;
      return;
    }
    test_export_shape(shp3, "./extreme_wire.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_cable() {
  std::cout << "\n=== Testing Cable ===" << std::endl;
  try {
    // 测试简单直线电缆
    auto shp1 = create_cable(cable_params{.startPoint = gp_Pnt(0, 0, 0),
                                          .endPoint = gp_Pnt(100, 0, 0),
                                          .diameter = 10.0});

    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create straight cable" << std::endl;
      return;
    }
    test_export_shape(shp1, "./straight_cable.stl");

    // 测试带转弯半径的曲线电缆
    std::vector<gp_Pnt> inflectionPoints = {gp_Pnt(50, 50, 0),
                                            gp_Pnt(100, 50, 50)};
    std::vector<double> radii = {20.0, 15.0};

    auto shp2 = create_cable(cable_params{.startPoint = gp_Pnt(0, 0, 0),
                                          .endPoint = gp_Pnt(150, 50, 50),
                                          .inflectionPoints = inflectionPoints,
                                          .radii = radii,
                                          .diameter = 8.0});

    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create curved cable" << std::endl;
      return;
    }
    test_export_shape(shp2, "./curved_cable.stl");

    // 测试极端参数 - 小直径大转弯半径
    std::vector<gp_Pnt> extremePoints = {gp_Pnt(50, 100, 0),
                                         gp_Pnt(100, 100, 100)};
    std::vector<double> extremeRadii = {50.0, 30.0};

    auto shp3 = create_cable(cable_params{.startPoint = gp_Pnt(0, 0, 0),
                                          .endPoint = gp_Pnt(200, 100, 100),
                                          .inflectionPoints = extremePoints,
                                          .radii = extremeRadii,
                                          .diameter = 2.0});

    if (shp3.IsNull()) {
      std::cerr << "Error: Failed to create extreme cable" << std::endl;
      return;
    }
    test_export_shape(shp3, "./extreme_cable.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_curve_cable() {
  std::cout << "\n=== Testing Curve Cable ===" << std::endl;
  try {
    // 测试简单直线段电缆
    std::vector<gp_Pnt> linePoints = {gp_Pnt(0, 0, 0), gp_Pnt(100, 0, 0)};

    auto shp1 =
        create_curve_cable(curve_cable_params{.controlPoints = {linePoints},
                                              .curveTypes = {curve_type::LINE},
                                              .diameter = 10.0});

    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create straight curve cable" << std::endl;
      return;
    }
    test_export_shape(shp1, "./straight_curve_cable.stl");

    // 测试混合曲线电缆(直线+圆弧+样条)
    std::vector<gp_Pnt> arcPoints = {gp_Pnt(100, 0, 0), gp_Pnt(150, 50, 0),
                                     gp_Pnt(200, 0, 0)};

    std::vector<gp_Pnt> splinePoints = {gp_Pnt(200, 0, 0), gp_Pnt(250, 50, 50),
                                        gp_Pnt(300, 0, 100),
                                        gp_Pnt(350, -50, 150)};

    auto shp2 = create_curve_cable(curve_cable_params{
        .controlPoints = {linePoints, arcPoints, splinePoints},
        .curveTypes = {curve_type::LINE, curve_type::ARC, curve_type::SPLINE},
        .diameter = 8.0});

    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create mixed curve cable" << std::endl;
      return;
    }
    test_export_shape(shp2, "./mixed_curve_cable.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_angle_steel() {
  std::cout << "\n=== Testing  Angle Steel ===" << std::endl;
  try {
    // 标准尺寸测试
    auto shp1 = create_angle_steel(angle_steel_params{
        .L1 = 60.0,     // 长边60mm
        .L2 = 40.0,     // 短边40mm
        .X = 5.0,       // 厚度5mm
        .length = 200.0 // 长度200mm
    });

    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create standard scalene angle steel"
                << std::endl;
      return;
    }
    test_export_shape(shp1, "./angle_steel_standard.stl");

    // 极端尺寸测试
    auto shp2 = create_angle_steel(angle_steel_params{
        .L1 = 100.0,    // 大长边
        .L2 = 30.0,     // 小短边
        .X = 3.0,       // 薄壁
        .length = 500.0 // 超长
    });

    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create extreme scalene angle steel"
                << std::endl;
      return;
    }
    test_export_shape(shp2, "./angle_steel_extreme.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_i_shaped_steel() {
  std::cout << "\n=== Testing I-Beam ===" << std::endl;
  try {
    // 标准参数测试
    auto shp1 = create_i_shaped_steel(
        i_shaped_steel_params{.height = 200.0,
                              .flangeWidth = 150.0,
                              .webThickness = 12.0, // 腹板厚度12mm
                              .flangeThickness = 8.0,
                              .length = 1000.0});

    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create standard I-beam" << std::endl;
      return;
    }
    test_export_shape(shp1, "./i_shaped_steel_standard.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_channel_steel() {
  std::cout << "\n=== Testing Channel Steel ===" << std::endl;
  try {
    // 标准参数测试
    auto shp1 =
        create_channel_steel(channel_steel_params{.height = 100.0,
                                                  .flangeWidth = 50.0,
                                                  .webThickness = 6.0,
                                                  .flangeThickness = 8.0,
                                                  .length = 500.0});

    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create standard channel steel"
                << std::endl;
      return;
    }
    test_export_shape(shp1, "./channel_steel_standard.stl");

    // 极端参数测试
    auto shp2 =
        create_channel_steel(channel_steel_params{.height = 200.0,
                                                  .flangeWidth = 30.0,
                                                  .webThickness = 4.0,
                                                  .flangeThickness = 5.0,
                                                  .length = 1000.0});

    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create extreme channel steel" << std::endl;
      return;
    }
    test_export_shape(shp2, "./channel_steel_extreme.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_t_steel() {
  std::cout << "\n=== Testing T-Steel ===" << std::endl;
  try {
    // 标准参数测试
    auto shp1 = create_t_steel(t_steel_params{.height = 120.0,
                                              .width = 60.0,
                                              .webThickness = 8.0,
                                              .flangeThickness = 10.0,
                                              .length = 600.0});

    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create standard T-steel" << std::endl;
      return;
    }
    test_export_shape(shp1, "./t_steel_standard.stl");

    // 极端参数测试
    auto shp2 = create_t_steel(t_steel_params{.height = 150.0,
                                              .width = 40.0,
                                              .webThickness = 5.0,
                                              .flangeThickness = 6.0,
                                              .length = 800.0});

    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create extreme T-steel" << std::endl;
      return;
    }
    test_export_shape(shp2, "./t_steel_extreme.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}
void test_make_bored_pile() {
  std::cout << "\n=== Testing Bored Pile ===" << std::endl;
  try {
    // 标准参数测试 
    auto shp1 = create_bored_pile_base(bored_pile_params{
      .H1 = 100.0,  // 上部圆柱高度
      .H2 = 30.0,   // 过渡段高度
      .H3 = 50.0,   // 底部圆柱高度
      .H4 = 3.0,    // 桩头高度（必须小于D/2）
      .d = 5.0,    // 上部直径
      .D = 20.0     // 底部直径
    });
    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create standard bored pile" << std::endl;
      return;
    }
    test_export_shape(shp1, "./bored_pile_standard.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_pile_cap() {
  std::cout << "\n=== Testing Pile Cap ===" << std::endl;
  try {
    // 标准参数测试
    pile_cap_params params{
        // 高度参数
        .H1 = 100.0,   // 桩上部圆柱高度
        .H2 = 30.0,    // 桩过渡段高度
        .H3 = 50.0,    // 桩底部圆柱高度
        .H4 = 40.0,    // 承台柱高度
        .H5 = 20.0,    // 承台底板高度
        .H6 = 3.0,     // 桩头高度
        
        // 尺寸参数
        .d = 5.0,      // 桩上部直径
        .D = 20.0,     // 桩底部直径
        .b = 15.0,     // 承台柱直径/边长
        .B1 = 200.0,   // 承台底板宽度
        .L1 = 300.0,   // 承台底板长度
        
        // 偏心参数
        .e1 = 10.0,     // X方向偏心
        .e2 = 5.0,      // Y方向偏心
        
        // 承台样式
        .cs = 0,        // 圆形承台柱
        
        // 桩参数
        .ZCOUNT = 3,    // 桩数量
        .ZPOSTARRAY = {gp_Pnt(0,0,0), gp_Pnt(100,0,0), gp_Pnt(0,100,0)}
    };

    auto shp = create_pile_cap_base(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create pile cap" << std::endl;
      return;
    }
    test_export_shape(shp, "./pile_cap_standard.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

int main() {
  //变电
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
  test_make_cone_porcelain_bushing();
  test_make_insulator_string();
  test_make_vtype_insulator();
  test_make_terminal_block();
  test_make_rectangular_fixed_plate();
  test_make_circular_fixed_plate();
  test_make_wire();
  test_make_cable();
  test_make_curve_cable();
  test_make_angle_steel();
  test_make_i_shaped_steel();
  test_make_channel_steel();
  test_make_t_steel();
  //输电
  test_make_bored_pile();
  test_make_pile_cap();
  return 0;
}
