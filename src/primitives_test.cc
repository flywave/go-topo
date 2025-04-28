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

bool exportShapeToStep(const TopoDS_Shape &shape, const std::string &path,
                       double tolerance = 0.5, double angularTolerance = 0.3) {
  // 检查输入形状是否有效
  if (shape.IsNull()) {
    return false;
  }

  // 创建STEP写入器和文档
  Handle(TDocStd_Document) doc = new TDocStd_Document("STEP");
  STEPCAFControl_Writer stepWriter;

  // 设置转换参数
  Interface_Static::SetCVal("write.step.unit", "MM");
  Interface_Static::SetIVal("write.step.nonmanifold", 1);

  // 添加形状到文档
  Handle(XCAFDoc_ShapeTool) shapeTool =
      XCAFDoc_DocumentTool::ShapeTool(doc->Main());
  TDF_Label label = shapeTool->AddShape(shape);

  // 执行导出
  if (!stepWriter.Transfer(doc, STEPControl_AsIs)) {
    return false;
  }

  return stepWriter.Write(path.c_str()) == IFSelect_RetDone;
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
                                                        .insulatorCount = 22,
                                                        .height = 5.0,
                                                        .bigSkirtRadius = 8.0,
                                                        .smallSkirtRadius = 6.0,
                                                        .radius = 2,
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
                                                        .insulatorCount = 22,
                                                        .height = 4.0,
                                                        .bigSkirtRadius = 7.0,
                                                        .smallSkirtRadius = 5.0,
                                                        .radius = 2,
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
        .insulatorCount = 22,    // 每串绝缘子片数
        .height = 5.0,           // 单片高度
        .radius = 2.0,           // 绝缘子半径
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
        .H1 = 100.0, // 上部圆柱高度
        .H2 = 30.0,  // 过渡段高度
        .H3 = 50.0,  // 底部圆柱高度
        .H4 = 3.0,   // 桩头高度（必须小于D/2）
        .d = 5.0,    // 上部直径
        .D = 20.0    // 底部直径
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
        .H1 = 100.0, // 桩上部圆柱高度
        .H2 = 30.0,  // 桩过渡段高度
        .H3 = 50.0,  // 桩底部圆柱高度
        .H4 = 40.0,  // 承台柱高度
        .H5 = 20.0,  // 承台底板高度
        .H6 = 3.0,   // 桩头高度

        // 尺寸参数
        .d = 5.0,    // 桩上部直径
        .D = 20.0,   // 桩底部直径
        .b = 15.0,   // 承台柱直径/边长
        .B1 = 200.0, // 承台底板宽度
        .L1 = 300.0, // 承台底板长度

        // 偏心参数
        .e1 = 10.0, // X方向偏心
        .e2 = 5.0,  // Y方向偏心

        // 承台样式
        .cs = 0, // 圆形承台柱

        // 桩参数
        .ZCOUNT = 3, // 桩数量
        .ZPOSTARRAY = {gp_Pnt(0, 0, 0), gp_Pnt(100, 0, 0), gp_Pnt(0, 100, 0)}};

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

void test_make_rock_anchor() {
  std::cout << "\n=== Testing Rock Anchor ===" << std::endl;
  try {
    // 标准参数测试
    rock_anchor_params params{
        // 高度参数
        .H1 = 20.0, // 基础底板高度
        .H2 = 50.0, // 锚桩长度

        // 尺寸参数
        .d = 5.0,    // 锚桩直径
        .B1 = 100.0, // 底板宽度
        .L1 = 150.0, // 底板长度

        // 锚桩参数
        .ZCOUNT = 4, // 锚桩数量
        .ZPOSTARRAY = {gp_Pnt(-40, -60, 0), gp_Pnt(40, -60, 0),
                       gp_Pnt(40, 60, 0), gp_Pnt(-40, 60, 0)}};

    auto shp = create_rock_anchor_base(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create rock anchor" << std::endl;
      return;
    }
    test_export_shape(shp, "./rock_anchor_standard.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_rock_pile_cap() {
  std::cout << "\n=== Testing Rock Pile Cap ===" << std::endl;
  try {
    // 标准参数测试
    rock_pile_cap_params params{
        // 高度参数
        .H1 = 40.0, // 承台柱高度
        .H2 = 20.0, // 承台底板高度
        .H3 = 50.0, // 锚桩长度

        // 尺寸参数
        .d = 5.0,    // 锚桩直径
        .b = 15.0,   // 承台柱直径/边长
        .B1 = 200.0, // 承台底板宽度
        .L1 = 300.0, // 承台底板长度

        // 偏心参数
        .e1 = 10.0, // X方向偏心
        .e2 = 5.0,  // Y方向偏心

        // 承台样式
        .cs = 0, // 圆形承台柱

        // 锚桩参数
        .ZCOUNT = 4, // 锚桩数量
        .ZPOSTARRAY = {gp_Pnt(-50, -50, 0), gp_Pnt(50, -50, 0),
                       gp_Pnt(50, 50, 0), gp_Pnt(-50, 50, 0)}};

    auto shp = create_rock_pile_cap_base(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create rock pile cap" << std::endl;
      return;
    }
    test_export_shape(shp, "./rock_pile_cap_standard.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_embedded_rock_anchor() {
  std::cout << "\n=== Testing Embedded Rock Anchor ===" << std::endl;
  try {
    // 标准参数测试
    embedded_rock_anchor_params params{
        // 高度参数
        .H1 = 100.0, // 上部圆柱高度
        .H2 = 30.0,  // 过渡段高度
        .H3 = 50.0,  // 底部圆柱高度

        // 直径参数
        .d = 5.0, // 上部直径
        .D = 20.0 // 底部直径
    };

    auto shp = create_embedded_rock_anchor_base(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create embedded rock anchor" << std::endl;
      return;
    }
    test_export_shape(shp, "./embedded_rock_anchor_standard.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_inclined_rock_anchor() {
  std::cout << "\n=== Testing Inclined Rock Anchor ===" << std::endl;
  try {
    // 标准参数测试
    inclined_rock_anchor_params params{
        // 高度参数
        .H1 = 20.0, // 基础底板高度
        .H2 = 50.0, // 锚桩长度

        // 直径参数
        .d = 5.0,  // 锚桩直径
        .D = 15.0, // 底部扩大头直径

        // 底板尺寸
        .B = 100.0, // 底板宽度
        .L = 150.0, // 底板长度

        // 偏心参数
        .e1 = 10.0, // X方向偏心
        .e2 = 5.0,  // Y方向偏心

        // 坡度参数
        .alpha1 = 15.0, // X轴坡度(度)
        .alpha2 = 10.0  // Y轴坡度(度)
    };

    auto shp = create_inclined_rock_anchor_base(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create inclined rock anchor" << std::endl;
      return;
    }
    test_export_shape(shp, "./inclined_rock_anchor_standard.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_excavated_base() {
  std::cout << "\n=== Testing Excavated Base ===" << std::endl;
  try {
    // 标准参数测试 - 直柱掏挖基础
    excavated_base_params params1{
        // 高度参数
        .H1 = 100.0, // 上部圆柱高度
        .H2 = 30.0,  // 过渡段高度
        .H3 = 50.0,  // 底部圆柱高度

        // 直径参数
        .d = 5.0,  // 上部直径
        .D = 20.0, // 底部直径

        // 坡度参数
        .alpha1 = 0.0, // 无X轴坡度
        .alpha2 = 0.0  // 无Y轴坡度
    };

    auto shp1 = create_excavated_base(params1);
    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create straight excavated base"
                << std::endl;
      return;
    }
    test_export_shape(shp1, "./straight_excavated_base.stl");

    // 极端参数测试 - 斜柱掏挖基础
    excavated_base_params params2{
        // 高度参数
        .H1 = 150.0, // 上部圆柱高度
        .H2 = 40.0,  // 过渡段高度
        .H3 = 60.0,  // 底部圆柱高度

        // 直径参数
        .d = 8.0,  // 上部直径
        .D = 25.0, // 底部直径

        // 坡度参数
        .alpha1 = 15.0, // X轴坡度15度
        .alpha2 = 10.0  // Y轴坡度10度
    };

    auto shp2 = create_excavated_base(params2);
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create sloped excavated base" << std::endl;
      return;
    }
    test_export_shape(shp2, "./sloped_excavated_base.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_step_base() {
  std::cout << "\n=== Testing Step Base ===" << std::endl;
  try {
    // 标准参数测试 - 3级台阶
    step_base_params params1{
        // 高度参数
        .H = 150.0, // 基础总高度
        .H1 = 50.0, // 第一级台阶高度
        .H2 = 50.0, // 第二级台阶高度
        .H3 = 50.0, // 第三级台阶高度

        // 尺寸参数
        .b = 30.0,   // 基础顶部宽度
        .B1 = 100.0, // 第一级台阶宽度
        .B2 = 150.0, // 第二级台阶宽度
        .B3 = 200.0, // 第三级台阶宽度
        .L1 = 100.0, // 第一级台阶长度
        .L2 = 150.0, // 第二级台阶长度
        .L3 = 200.0, // 第三级台阶长度

        // 台阶参数
        .N = 3 // 台阶数量
    };

    auto shp1 = create_step_base(params1);
    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create 3-step base" << std::endl;
      return;
    }
    test_export_shape(shp1, "./3_step_base.stl");

    // 简化参数测试 - 2级台阶
    step_base_params params2{
        // 高度参数
        .H = 100.0, // 基础总高度
        .H1 = 40.0, // 第一级台阶高度
        .H2 = 60.0, // 第二级台阶高度
        .H3 = 0.0,  // 不使用

        // 尺寸参数
        .b = 20.0,   // 基础顶部宽度
        .B1 = 80.0,  // 第一级台阶宽度
        .B2 = 120.0, // 第二级台阶宽度
        .B3 = 0.0,   // 不使用
        .L1 = 80.0,  // 第一级台阶长度
        .L2 = 120.0, // 第二级台阶长度
        .L3 = 0.0,   // 不使用

        // 台阶参数
        .N = 2 // 台阶数量
    };

    auto shp2 = create_step_base(params2);
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create 2-step base" << std::endl;
      return;
    }
    test_export_shape(shp2, "./2_step_base.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_step_plate_base() {
  std::cout << "\n=== Testing Step Plate Base ===" << std::endl;
  try {
    // 标准参数测试 - 3级台阶
    step_plate_base_params params1{
        // 高度参数
        .H = 150.0, // 基础总高度
        .H1 = 50.0, // 第一级台阶高度
        .H2 = 50.0, // 第二级台阶高度
        .H3 = 50.0, // 第三级台阶高度

        // 尺寸参数
        .b = 30.0,   // 柱顶宽度/直径
        .L1 = 100.0, // 第一级台阶长度
        .L2 = 150.0, // 第二级台阶长度
        .B1 = 200.0, // 基础底板宽度
        .B2 = 300.0, // 第一级台阶宽度

        // 坡度参数
        .alpha1 = 15.0, // X轴坡度15度
        .alpha2 = 10.0, // Y轴坡度10度

        // 台阶参数
        .N = 3 // 台阶数量
    };

    auto shp1 = create_step_plate_base(params1);
    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create 3-step plate base" << std::endl;
      return;
    }
    test_export_shape(shp1, "./3_step_plate_base.stl");

    // 简化参数测试 - 2级台阶
    step_plate_base_params params2{
        // 高度参数
        .H = 100.0, // 基础总高度
        .H1 = 40.0, // 第一级台阶高度
        .H2 = 60.0, // 第二级台阶高度
        .H3 = 0.0,  // 不使用

        // 尺寸参数
        .b = 20.0,   // 柱顶宽度/直径
        .L1 = 80.0,  // 第一级台阶长度
        .L2 = 120.0, // 第二级台阶长度
        .B1 = 180.0, // 基础底板宽度
        .B2 = 200.0, // 第一级台阶宽度

        // 坡度参数
        .alpha1 = 0.0, // 无X轴坡度
        .alpha2 = 0.0, // 无Y轴坡度

        // 台阶参数
        .N = 2 // 台阶数量
    };

    auto shp2 = create_step_plate_base(params2);
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create 2-step plate base" << std::endl;
      return;
    }
    test_export_shape(shp2, "./2_step_plate_base.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}
void test_make_sloped_base_base() {
  std::cout << "\n=== Testing Sloped Base Base ===" << std::endl;
  try {
    // 标准参数测试
    sloped_base_base_params params{.H1 = 100.0,
                                   .H2 = 30.0,
                                   .H3 = 50.0,
                                   .b = 15.0,
                                   .L1 = 200.0,
                                   .L2 = 150.0,
                                   .B1 = 100.0,
                                   .B2 = 80.0,
                                   .alpha1 = 15.0,
                                   .alpha2 = 10.0};

    auto shp = create_sloped_base_base(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create sloped base base" << std::endl;
      return;
    }
    test_export_shape(shp, "./sloped_base_base.stl");

    // 可以添加更多测试用例...

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_composite_caisson_base() {
  std::cout << "\n=== Testing Composite Caisson Base ===" << std::endl;
  try {
    // 标准参数测试
    composite_caisson_base_params params1{
        // 高度参数
        .H1 = 100.0, // 上部沉井高度
        .H2 = 30.0,  // 过渡段高度
        .H3 = 50.0,  // 下部基础高度
        .H4 = 200.0, // 下部沉井高度

        // 尺寸参数
        .b = 15.0,   // 预留参数
        .D = 200.0,  // 沉井直径
        .t = 15.0,   // 沉井壁厚
        .B1 = 200.0, // 过渡段底部宽度
        .B2 = 250.0, // 下部基础宽度
        .L1 = 300.0, // 过渡段底部长度
        .L2 = 350.0  // 下部基础长度
    };

    auto shp1 = create_composite_caisson_base(params1);
    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create standard composite caisson base"
                << std::endl;
      return;
    }
    test_export_shape(shp1, "./standard_composite_caisson_base.stl");

    // 极端参数测试
    composite_caisson_base_params params2{
        // 高度参数
        .H1 = 150.0, // 上部沉井高度
        .H2 = 40.0,  // 过渡段高度
        .H3 = 60.0,  // 下部基础高度
        .H4 = 30.0,  // 预留参数

        // 尺寸参数
        .b = 20.0,   // 预留参数
        .D = 15.0,   // 沉井直径
        .t = 1.5,    // 沉井壁厚
        .B1 = 250.0, // 过渡段底部宽度
        .B2 = 300.0, // 下部基础宽度
        .L1 = 350.0, // 过渡段底部长度
        .L2 = 400.0  // 下部基础长度
    };

    auto shp2 = create_composite_caisson_base(params2);
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create extreme composite caisson base"
                << std::endl;
      return;
    }
    test_export_shape(shp2, "./extreme_composite_caisson_base.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}
void test_make_raft_base() {
  std::cout << "\n=== Testing Raft Base ===" << std::endl;
  try {
    // 标准参数测试 - 带主梁
    raft_base_params params1{
        // 高度参数
        .H1 = 100.0, // 底板高度
        .H2 = 100.0, // 边梁高度
        .H3 = 50.0,  // 主梁高度

        // 尺寸参数
        .b1 = 30.0,  // 纵向主梁宽度
        .b2 = 30.0,  // 横向主梁宽度
        .B1 = 500.0, // 底板宽度
        .B2 = 400.0, // 边梁宽度
        .L1 = 800.0, // 底板长度
        .L2 = 600.0  // 边梁长度
    };

    auto shp1 = create_raft_base(params1);
    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create raft base with beams" << std::endl;
      return;
    }
    test_export_shape(shp1, "./raft_base_with_beams.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_direct_buried_base() {
  std::cout << "\n=== Testing Direct Buried Base ===" << std::endl;
  try {
    // 测试圆形固定盘
    direct_buried_base_params params1{
        // 高度参数
        .H1 = 500.0, // 基础主体高度
        .H2 = 100.0, // 固定盘高度

        // 尺寸参数
        .d = 300.0, // 基础主体直径
        .D = 600.0, // 圆形固定盘直径
        .t = 20.0   // 壁厚
    };

    auto shp1 = create_direct_buried_base(params1);
    if (shp1.IsNull()) {
      std::cerr
          << "Error: Failed to create direct buried base with circular plate"
          << std::endl;
      return;
    }
    test_export_shape(shp1, "./direct_buried_base_circular.stl");

    // 测试方形固定盘
    direct_buried_base_params params2{
        // 高度参数
        .H1 = 500.0, // 基础主体高度
        .H2 = 100.0, // 固定盘高度

        // 尺寸参数
        .d = 300.0, // 基础主体直径
        .B = 600.0, // 方形固定盘边长
        .t = 20.0   // 壁厚
    };

    auto shp2 = create_direct_buried_base(params2);
    if (shp2.IsNull()) {
      std::cerr
          << "Error: Failed to create direct buried base with square plate"
          << std::endl;
      return;
    }
    test_export_shape(shp2, "./direct_buried_base_square.stl");

    // 测试无固定盘
    direct_buried_base_params params3{
        // 高度参数
        .H1 = 500.0, // 基础主体高度

        // 尺寸参数
        .d = 300.0, // 基础主体直径
        .t = 20.0   // 壁厚
    };

    auto shp3 = create_direct_buried_base(params3);
    if (shp3.IsNull()) {
      std::cerr << "Error: Failed to create direct buried base without plate"
                << std::endl;
      return;
    }
    test_export_shape(shp3, "./direct_buried_base_no_plate.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}
void test_make_steel_sleeve_base() {
  std::cout << "\n=== Testing Steel Sleeve Base ===" << std::endl;
  try {
    // 测试带圆形扩大段的基础
    steel_sleeve_base_params params1{
        // 高度参数
        .H1 = 500.0, // 钢套筒高度
        .H2 = 100.0, // 底部扩大段高度
        .H3 = 150.0, // 顶部扩大段高度
        .H4 = 50.0,  // 内部填充高度

        // 直径参数
        .d = 300.0,  // 钢套筒外径
        .D1 = 600.0, // 底部扩大段外径
        .D2 = 400.0, // 底部扩大段内径
        .t = 20.0    // 钢套筒壁厚
    };

    auto shp1 = create_steel_sleeve_base(params1);
    if (shp1.IsNull()) {
      std::cerr
          << "Error: Failed to create steel sleeve base with circular expansion"
          << std::endl;
      return;
    }
    test_export_shape(shp1, "./steel_sleeve_base_circular.stl");

    // 测试带方形扩大段的基础
    steel_sleeve_base_params params2{
        // 高度参数
        .H1 = 500.0, // 钢套筒高度
        .H2 = 100.0, // 底部扩大段高度
        .H3 = 150.0, // 顶部扩大段高度
        .H4 = 50.0,  // 内部填充高度

        // 直径参数
        .d = 300.0, // 钢套筒外径
        .t = 20.0,  // 钢套筒壁厚

        // 顶部扩大段参数
        .B1 = 600.0, // 顶部扩大段外径
        .B2 = 400.0  // 顶部扩大段内径
    };

    auto shp2 = create_steel_sleeve_base(params2);
    if (shp2.IsNull()) {
      std::cerr
          << "Error: Failed to create steel sleeve base with square expansion"
          << std::endl;
      return;
    }
    test_export_shape(shp2, "./steel_sleeve_base_square.stl");

    // 测试无扩大段的简单基础
    steel_sleeve_base_params params3{
        // 高度参数
        .H1 = 500.0, // 钢套筒高度
        .H4 = 50.0,  // 内部填充高度

        // 直径参数
        .d = 300.0, // 钢套筒外径
        .t = 20.0   // 钢套筒壁厚
    };

    auto shp3 = create_steel_sleeve_base(params3);
    if (shp3.IsNull()) {
      std::cerr << "Error: Failed to create simple steel sleeve base"
                << std::endl;
      return;
    }
    test_export_shape(shp3, "./steel_sleeve_base_simple.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_precast_column_base() {
  std::cout << "\n=== Testing Precast Column Base ===" << std::endl;
  try {
    // 标准参数测试
    precast_column_base_params params1{
        // 高度参数
        .H1 = 500.0, // 柱体高度
        .H2 = 200.0, // 过渡段上部高度
        .H3 = 300.0, // 过渡段下部高度

        // 直径参数
        .d = 100.0, // 柱体直径

        // 尺寸参数
        .B1 = 200.0, // 过渡段上部宽度
        .B2 = 400.0, // 过渡段下部宽度
        .L1 = 300.0, // 过渡段上部长度
        .L2 = 600.0  // 过渡段下部长度
    };

    auto shp1 = create_precast_column_base(params1);
    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create precast column base" << std::endl;
      return;
    }
    test_export_shape(shp1, "./precast_column_base.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_precast_pinned_base() {
  std::cout << "\n=== Testing Precast Pinned Base ===" << std::endl;
  try {
    // 标准参数测试 - 带卡盘
    precast_pinned_base_params params1{
        // 高度参数
        .H1 = 500.0, // 柱体高度
        .H2 = 200.0, // 过渡段上部高度
        .H3 = 200.0, // 过渡段下部高度

        // 直径参数
        .d = 100.0, // 柱体直径

        // 尺寸参数
        .B1 = 200.0, // 过渡段上部宽度
        .B2 = 400.0, // 过渡段下部宽度
        .L1 = 300.0, // 过渡段上部长度
        .L2 = 600.0, // 过渡段下部长度

        // 卡盘参数
        .B = 40.0, // 卡盘宽度
        .H = 40.0, // 卡盘高度
        .L = 200.0 // 卡盘长度
    };

    auto shp1 = create_precast_pinned_base(params1);
    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create precast pinned base with clamp"
                << std::endl;
      return;
    }
    test_export_shape(shp1, "./precast_pinned_base_with_clamp.stl");

    // 不带卡盘测试
    precast_pinned_base_params params2 = params1;
    params2.B = 0; // 禁用卡盘
    params2.H = 0;
    params2.L = 0;

    auto shp2 = create_precast_pinned_base(params2);
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create precast pinned base without clamp"
                << std::endl;
      return;
    }
    test_export_shape(shp2, "./precast_pinned_base_without_clamp.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_precast_metal_support_base() {
  std::cout << "\n=== Testing Precast Metal Support Base ===" << std::endl;
  try {
    // 标准参数测试
    precast_metal_support_base_params params1{
        // 高度参数
        .H1 = 40.0,  // 底板高度
        .H2 = 400.0, // 立柱高度
        .H3 = 20.0,  // 连接梁高度
        .H4 = 20.0,  // 斜撑高度差

        // 尺寸参数
        .b1 = 30.0,   // 立柱直径
        .b2 = 30.0,   // 连接梁直径
        .B1 = 800.0,  // 底板宽度
        .B2 = 600.0,  // 支架正面根开
        .L1 = 1000.0, // 底板长度
        .L2 = 800.0,  // 支架侧面根开
        .S1 = 40.0,   // 支架规格
        .S2 = 20.0,   // 斜材规格

        // 数量参数
        .n1 = 3, // 斜材组数
        .n2 = 9, // 板条数量

        // 斜材层高
        .HX = {100.0, 100.0, 100.0} // 斜材层高数组
    };

    auto shp1 = create_precast_metal_support_base(params1);
    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create precast metal support base"
                << std::endl;
      return;
    }
    test_export_shape(shp1, "./precast_metal_support_base.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_precast_concrete_support_base() {
  std::cout << "\n=== Testing Precast Concrete Support Base ===" << std::endl;
  try {
    // 标准参数测试
    precast_concrete_support_base_params params1{
        // 高度参数
        .H1 = 40.0,  // 底板高度
        .H2 = 400.0, // 立柱高度
        .H3 = 20.0,  // 连接梁高度
        .H4 = 20.0,  // 支撑顶部高度
        .H5 = 20.0,  // 支撑底部高度

        // 尺寸参数
        .b1 = 30.0,   // 立柱直径
        .b2 = 40.0,   // 连接梁直径
        .b3 = 20.0,   // 支撑直径
        .B1 = 800.0,  // 底板宽度
        .B2 = 600.0,  // 支架正面根开
        .L1 = 1000.0, // 底板长度
        .L2 = 800.0,  // 支架侧面根开
        .S1 = 40.0,   // 顶部平台尺寸

        // 数量参数
        .n1 = 9 // 支撑数量
    };

    auto shp1 = create_precast_concrete_support_base(params1);
    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create precast concrete support base"
                << std::endl;
      return;
    }
    test_export_shape(shp1, "./precast_concrete_support_base.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_transmission_line() {
  std::cout << "\n=== Testing Transmission Line ===" << std::endl;
  try {
    transmission_line_params params{.type = "LGJ-400/35",
                                    .sectionalArea = 425.24,
                                    .outsideDiameter = 26.82,
                                    .wireWeight = 1349,
                                    .coefficientOfElasticity = 65000,
                                    .expansionCoefficient = 0.0000205,
                                    .ratedStrength = 103900};

    gp_Pnt startPoint(0, 0, 0);
    gp_Pnt endPoint(1000, 0, 50); // 1000米跨度，50米高差

    auto shp = create_transmission_line(params, startPoint, endPoint);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create transmission line" << std::endl;
      return;
    }
    test_export_shape(shp, "./transmission_line.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_gt_insulator_string() {
  std::cout << "\n=== Testing Insulator String ===" << std::endl;
  try {

    // 测试标准悬垂串
    insulator_params params0{
        .type = "XWP-70",
        .subNum = 1,
        .subType = 0,
        .splitDistance = 0,
        .vAngleLeft = 0,
        .vAngleRight = 0,
        .uLinkLength = 0,
        .weight = 5.2,
        .fittingLengths = {.leftUpper = 0.7,
                           .rightUpper = 0.7,
                           .leftLower = 1,
                           .rightLower = 1},
        .multiLink = {.count = 1,
                      .spacing = 0,
                      .arrangement = arrangement_type::VERTICAL},
        .insulator = {.radius = 0.475,
                      .height = 10.146,
                      .leftCount = 20,
                      .rightCount = 20,
                      .material = insulator_material::CERAMIC},
        .gradingRing = {.count = 1,
                        .position = 0.5,
                        .height = 0.03,
                        .radius = 0.15},
        .application = application_type::CONDUCTOR,
        .stringType = string_type::SUSPENSION};

    auto shp0 = create_insulator_string(params0);
    if (shp0.IsNull()) {
      std::cerr << "Error: Failed to create suspension insulator string"
                << std::endl;
      return;
    }
    test_export_shape(shp0, "./insulator_single_string_suspension.stl");

    // 测试标准悬垂串
    insulator_params params1{
        .type = "XWP-70",
        .subNum = 1,
        .subType = 0,
        .splitDistance = 0,
        .vAngleLeft = 0,
        .vAngleRight = 0,
        .uLinkLength = 2,
        .weight = 5.2,
        .fittingLengths = {.leftUpper = 0.7,
                           .rightUpper = 0.7,
                           .leftLower = 1,
                           .rightLower = 1},
        .multiLink = {.count = 1,
                      .spacing = 0,
                      .arrangement = arrangement_type::VERTICAL},
        .insulator = {.radius = 0.475,
                      .height = 10.146,
                      .leftCount = 20,
                      .rightCount = 20,
                      .material = insulator_material::CERAMIC},
        .gradingRing = {.count = 1,
                        .position = 0.5,
                        .height = 0.03,
                        .radius = 0.15},
        .application = application_type::CONDUCTOR,
        .stringType = string_type::SUSPENSION};

    auto shp1 = create_insulator_string(params1);
    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create suspension insulator string"
                << std::endl;
      return;
    }
    test_export_shape(shp1, "./insulator_string_suspension.stl");

    // 测试V型耐张串
    insulator_params params2{
        .type = "FXBW-110/100",
        .subNum = 2,
        .subType = 1,
        .splitDistance = 400,
        .vAngleLeft = 40,
        .vAngleRight = 30,
        .uLinkLength = 0,
        .weight = 8.5,
        .fittingLengths = {.leftUpper = 0.7,
                           .rightUpper = 0.7,
                           .leftLower = 1,
                           .rightLower = 1},
        .multiLink = {.count = 1,
                      .spacing = 0,
                      .arrangement = arrangement_type::HORIZONTAL},
        .insulator = {.radius = composite_insulator_params{.majorRadius = 0.47,
                                                           .minorRadius = 0.55,
                                                           .gap = 0.4},
                      .height = 20.146,
                      .leftCount = 20,
                      .rightCount = 20,
                      .material = insulator_material::COMPOSITE},
        .gradingRing = {.count = 2,
                        .position = 0.4,
                        .height = 0.04,
                        .radius = 0.2},
        .application = application_type::GROUND_WIRE,
        .stringType = string_type::SUSPENSION};

    auto shp2 = create_insulator_string(params2);
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create tension insulator string"
                << std::endl;
      return;
    }
    test_export_shape(shp2, "./insulator_string_tension.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_pole_tower() {
  std::cout << "\n=== Testing Pole Tower ===" << std::endl;
  try {
    // 创建测试杆塔参数
    pole_tower_params params;

    // 添加呼高信息
    params.heights.push_back(
        pole_tower_height{.value = 18.0, .bodyId = "body1", .legId = "leg1"});

    // 添加本体信息
    pole_tower_body body{.id = "body1", .height = 30.0};

    // 添加接腿信息
    pole_tower_leg leg{
        .id = "leg1", .commonHeight = 10.0, .specificHeight = 8.0};

    // 添加节点
    body.nodes.push_back(
        pole_tower_node{.id = "node1", .position = gp_Pnt(0, 0, 0)});
    body.nodes.push_back(
        pole_tower_node{.id = "node2", .position = gp_Pnt(10, 0, 30)});
    // 添加更多测试节点
    body.nodes.push_back(
        pole_tower_node{.id = "node3", .position = gp_Pnt(20, 0, 0)});
    body.nodes.push_back(
        pole_tower_node{.id = "node4", .position = gp_Pnt(30, 0, 30)});
    body.nodes.push_back(
        pole_tower_node{.id = "node5", .position = gp_Pnt(40, 0, 0)});
    body.nodes.push_back(
        pole_tower_node{.id = "node6", .position = gp_Pnt(50, 0, 30)});

    // 添加杆件
    params.members.push_back(pole_tower_member{.id = "member1",
                                               .startNodeId = "node1",
                                               .endNodeId = "node2",
                                               .type = member_type::ANGLE,
                                               .specification = "L5x1",
                                               .material = "Q345",
                                               .xDirection = gp_Dir(1, 0, 0),
                                               .yDirection = gp_Dir(0, 1, 0)});

    // 2. 添加等径钢管测试案例（φ50x5 表示直径50mm，壁厚5mm）
    params.members.push_back(
        pole_tower_member{.id = "member2",
                          .startNodeId = "node3",
                          .endNodeId = "node4",
                          .type = member_type::TUBE,
                          .specification = "φ50x5", // 格式：φ外径x壁厚
                          .material = "Q345",
                          .xDirection = gp_Dir(1, 0, 0),
                          .yDirection = gp_Dir(0, 1, 0)});

    // 3. 添加锥形钢管测试案例（规格格式：锥形管需要单独参数）
    params.members.push_back(pole_tower_member{
        .id = "member3",
        .startNodeId = "node5",
        .endNodeId = "node6",
        .type = member_type::TAPERED_TUBE,
        .specification = "TAPERED", // 锥形管需要单独参数
        .material = "Q345",
        .xDirection = gp_Dir(1, 0, 0),
        .yDirection = gp_Dir(0, 1, 0),
        .end1Diameter = 60.0, // 起始端直径
        .end2Diameter = 40.0, // 终止端直径
    });

    // 添加挂点
    params.attachments.push_back(
        pole_tower_attachment{.name = "ground_wire",
                              .type = attachment_type::GROUND_WIRE,
                              .position = gp_Pnt(50, 0, 30)});

    body.legs.push_back(leg);
    params.bodies.push_back(body);

    // 创建杆塔模型
    auto shp = create_pole_tower(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create pole tower" << std::endl;
      return;
    }
    test_export_shape(shp, "./pole_tower.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_single_hook_anchor() {
  std::cout << "\n=== Testing Single Hook Anchor ===" << std::endl;
  try {
    single_hook_anchor_params params{
        // 基础参数
        // 基础参数 (单位:米)
        .boltDiameter = 0.24, // 24mm → 0.024m
        .exposedLength = 0.2, // 100mm → 0.1m
        .nutCount = 2,
        .nutHeight = 0.075, // 15mm → 0.015m
        .nutOD = 0.6,       // 40mm → 0.04m
        .washerCount = 2,
        .washerShape = 2,         // 圆形垫片
        .washerSize = 0.65,       // 50mm → 0.05m
        .washerThickness = 0.015, // 5mm → 0.005m
        .anchorLength = 1.5,      // 800mm → 0.8m

        // 单钩锚固特有参数 (单位:米)
        .hookStraightLength = 0.6, // 150mm → 0.15m
        .hookDiameter = 0.6        // 60mm → 0.06m0
    };

    auto shp = create_single_hook_anchor(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create single hook anchor" << std::endl;
      return;
    }
    test_export_shape(shp, "./single_hook_anchor.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_triple_hook_anchor() {
  std::cout << "\n=== Testing Triple Hook Anchor ===" << std::endl;
  try {
    triple_hook_anchor_params params{
        .boltDiameter = 0.24, // 24mm → 0.024m
        .exposedLength = 0.2, // 100mm → 0.1m
        .nutCount = 2,
        .nutHeight = 0.1, // 15mm → 0.015m
        .nutOD = 0.6,     // 40mm → 0.04m
        .washerCount = 2,
        .washerShape = 2,         // 圆形垫片
        .washerSize = 0.65,       // 50mm → 0.05m
        .washerThickness = 0.015, // 5mm → 0.005m
        .anchorLength = 1.5,      // 1000mm → 1.0m

        // 三钩锚固特有参数 (单位:米)
        .hookStraightLengthA = 0.6,  // 100mm → 0.1m
        .hookStraightLengthB = 0.25, // 150mm → 0.15m
        .hookDiameter = 0.6,         // 30mm → 0.03m
        .anchorBarDiameter = 0.1     // 25mm → 0.025m
    };

    auto shp = create_triple_hook_anchor(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create triple hook anchor" << std::endl;
      return;
    }
    test_export_shape(shp, "./triple_hook_anchor.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_ribbed_anchor() {
  std::cout << "\n=== Testing Ribbed Anchor ===" << std::endl;
  try {
    ribbed_anchor_params params{
        // 基础参数（单位：米）
        .boltDiameter = 0.2,      // 地脚螺栓直径 20mm → 0.02m
        .exposedLength = 0.40,    // 露头长度 100mm → 0.1m
        .nutCount = 0,            // 蝶帽数量保持不变
        .nutHeight = 0.1,         // 蝶帽高度 10mm → 0.01m
        .nutOD = 0.6,             // 蝶帽外径 40mm → 0.04m
        .washerCount = 0,         // 垫片数量保持不变
        .washerShape = 2,         // 圆形垫片
        .washerSize = 0.65,       // 垫片直径 30mm → 0.03m
        .washerThickness = 0.015, // 垫片厚度 5mm → 0.005m
        .anchorLength = 1.5,      // 锚固长度 500mm → 0.5m

        // 肋板锚固特有参数（单位：米）
        .basePlateSize = 0.60,       // 底板尺寸 200mm → 0.2m
        .ribTopWidth = 0.1,          // 肋板顶部宽度 60mm → 0.06m
        .ribBottomWidth = 0.2,       // 肋板底部宽度 100mm → 0.1m
        .basePlateThickness = 0.030, // 底板厚度 20mm → 0.02m
        .ribHeight = 0.2,            // 肋板高度 150mm → 0.15m
        .ribThickness = 0.025        // 肋板厚度 15mm → 0.015m
    };

    auto shp = create_ribbed_anchor(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create ribbed anchor" << std::endl;
      return;
    }
    test_export_shape(shp, "./ribbed_anchor.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_nut_anchor() {
  std::cout << "\n=== Testing Nut Anchor ===" << std::endl;
  try {
    nut_anchor_params params{                     // 基础参数
                             .boltDiameter = 0.2, // 地脚螺栓直径 20mm → 0.02m
                             .exposedLength = 0.40, // 露头长度 100mm → 0.1m
                             .nutCount = 2,         // 蝶帽数量保持不变
                             .nutHeight = 0.1,   // 蝶帽高度 10mm → 0.01m
                             .nutOD = 0.6,       // 蝶帽外径 40mm → 0.04m
                             .washerCount = 2,   // 垫片数量保持不变
                             .washerShape = 2,   // 圆形垫片
                             .washerSize = 0.65, // 垫片直径 30mm → 0.03m
                             .washerThickness = 0.015, // 垫片厚度 5mm → 0.005m
                             .anchorLength = 1.5, // 锚固长度 500mm → 0.5m

                             // 螺帽锚固特有参数
                             .basePlateSize = 0.60,
                             .basePlateThickness = 0.030,
                             .boltToPlateDistance = 1.4};

    auto shp = create_nut_anchor(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create nut anchor" << std::endl;
      return;
    }
    test_export_shape(shp, "./nut_anchor.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_triple_arm_anchor() {
  std::cout << "\n=== Testing Triple Arm Anchor ===" << std::endl;
  try {
    triple_arm_anchor_params params{
        // 基础参数
        .boltDiameter = 0.2,      // 地脚螺栓直径 20mm → 0.02m
        .exposedLength = 0.40,    // 露头长度 100mm → 0.1m
        .nutCount = 2,            // 蝶帽数量保持不变
        .nutHeight = 0.1,         // 蝶帽高度 10mm → 0.01m
        .nutOD = 0.6,             // 蝶帽外径 40mm → 0.04m
        .washerCount = 2,         // 垫片数量保持不变
        .washerShape = 2,         // 圆形垫片
        .washerSize = 0.65,       // 垫片直径 30mm → 0.03m
        .washerThickness = 0.015, // 垫片厚度 5mm → 0.005m
        .anchorLength = 1.5,      // 锚固长度 500mm → 0.5m

        // 三支锚固特有参数
        .armDiameter = 0.12,      // 弯支规格16mm
        .armStraightLength = 0.6, // 弯支直段长100mm
        .armBendLength = 0.4,     // 弯支弯折段长50mm
        .armBendAngle = M_PI / 4  // 弯支弯折角度45度
    };

    auto shp = create_triple_arm_anchor(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create triple arm anchor" << std::endl;
      return;
    }
    test_export_shape(shp, "./triple_arm_anchor.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_positioning_plate_anchor() {
  std::cout << "\n=== Testing Positioning Plate Anchor ===" << std::endl;
  try {
    positioning_plate_anchor_params params{
        // 基础参数
        .boltDiameter = 0.2,      // 地脚螺栓直径 20mm → 0.02m
        .exposedLength = 0.40,    // 露头长度 100mm → 0.1m
        .nutCount = 2,            // 蝶帽数量保持不变
        .nutHeight = 0.1,         // 蝶帽高度 10mm → 0.01m
        .nutOD = 0.6,             // 蝶帽外径 40mm → 0.04m
        .washerCount = 2,         // 垫片数量保持不变
        .washerShape = 2,         // 圆形垫片
        .washerSize = 0.65,       // 垫片直径 30mm → 0.03m
        .washerThickness = 0.015, // 垫片厚度 5mm → 0.005m
        .anchorLength = 1.5,      // 锚固长度 500mm → 0.5m

        // 定位板锚固特有参数
        .plateLength = 0.60,     // 定位板长度200mm
        .plateThickness = 0.030, // 定位板厚度20mm
        .toBaseDistance = 0.2,   // 到基础面距离100mm
        .toBottomDistance = 0.2, // 到底部距离50mm
        .groutHoleDiameter = 0.3 // 灌注孔径30mm
    };

    auto shp = create_positioning_plate_anchor(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create positioning plate anchor"
                << std::endl;
      return;
    }
    test_export_shape(shp, "./positioning_plate_anchor.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_stub_angle() {
  std::cout << "\n=== Testing Stub Angle ===" << std::endl;
  try {
    stub_angle_params params{
        .legWidth = 0.1,      // 肢宽100mm
        .thickness = 0.01,    // 厚度10mm
        .slope = 0.1,         // 坡度10%
        .exposedLength = 2.0, // 露头长度200mm
        .anchorLength = 5.0   // 锚固长度500mm
    };

    // 创建标准方向的插入角钢
    auto shp = create_stub_angle(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create stub angle" << std::endl;
      return;
    }
    test_export_shape(shp, "./stub_angle.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_stub_tube() {
  std::cout << "\n=== Testing Stub Tube ===" << std::endl;
  try {
    // 测试标准插入钢管
    stub_tube_params params1{.diameter = 0.6,
                             .thickness = 0.1,
                             .slope = 0.1,
                             .exposedLength = 2.0,
                             .anchorLength = 10.0};

    auto shp1 = create_stub_tube(params1);
    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create stub tube" << std::endl;
      return;
    }
    test_export_shape(shp1, "./stub_tube_standard.stl");

    // 测试带坡度的插入钢管
    stub_tube_params params2{.diameter = 0.6,
                             .thickness = 0.1,
                             .slope = 0.2,
                             .exposedLength = 2.0,
                             .anchorLength = 10.0};

    auto shp2 = create_stub_tube(params2);
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create sloped stub tube" << std::endl;
      return;
    }
    test_export_shape(shp2, "./stub_tube_sloped.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_cable_wire() {
  std::cout << "\n=== Testing Cable Wire ===" << std::endl;
  try {
    // 测试简单直线电缆
    std::vector<gp_Pnt> straightPoints = {gp_Pnt(0, 0, 0), gp_Pnt(100, 0, 0)};

    auto shp1 = create_cable_wire(
        cable_wire_params{.points = straightPoints, .outside_diameter = 10.0});

    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create straight cable wire" << std::endl;
      return;
    }
    test_export_shape(shp1, "./straight_cable_wire.stl");

    // 测试曲线电缆
    std::vector<gp_Pnt> curvedPoints = {gp_Pnt(0, 0, 0), gp_Pnt(50, 50, 0),
                                        gp_Pnt(100, 50, 50),
                                        gp_Pnt(150, 0, 100)};

    auto shp2 = create_cable_wire(
        cable_wire_params{.points = curvedPoints, .outside_diameter = 8.0});

    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create curved cable wire" << std::endl;
      return;
    }
    test_export_shape(shp2, "./curved_cable_wire.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_cable_joint() {
  std::cout << "\n=== Testing Cable Joint ===" << std::endl;
  try {
    // 测试标准电缆接头
    auto shp1 = create_cable_joint(cable_joint_params{
        .length = 100.0,        // 总长100mm
        .outerDiameter = 30.0,  // 外径30mm
        .terminalLength = 20.0, // 端子长度20mm
        .innerDiameter = 20.0   // 内径20mm
    });

    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create standard cable joint" << std::endl;
      return;
    }
    test_export_shape(shp1, "./standard_cable_joint.stl");

    // 测试短接头
    auto shp2 = create_cable_joint(cable_joint_params{
        .length = 50.0,         // 总长50mm
        .outerDiameter = 20.0,  // 外径20mm
        .terminalLength = 10.0, // 端子长度10mm
        .innerDiameter = 15.0   // 内径15mm
    });

    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create short cable joint" << std::endl;
      return;
    }
    test_export_shape(shp2, "./short_cable_joint.stl");

    // 测试长端子接头
    auto shp3 = create_cable_joint(cable_joint_params{
        .length = 150.0,        // 总长150mm
        .outerDiameter = 40.0,  // 外径40mm
        .terminalLength = 50.0, // 端子长度50mm
        .innerDiameter = 30.0   // 内径30mm
    });

    if (shp3.IsNull()) {
      std::cerr << "Error: Failed to create long terminal cable joint"
                << std::endl;
      return;
    }
    test_export_shape(shp3, "./long_terminal_cable_joint.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_optical_fiber_box() {
  std::cout << "\n=== Testing Optical Fiber Box ===" << std::endl;
  try {
    // 测试标准光缆接头盒
    auto shp1 = create_optical_fiber_box(optical_fiber_box_params{
        .length = 300.0, // 总长300mm
        .height = 150.0, // 高度150mm
        .width = 200.0   // 宽度200mm
    });

    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create standard optical fiber box"
                << std::endl;
      return;
    }
    test_export_shape(shp1, "./standard_optical_fiber_box.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_cable_accessory() {
  std::cout << "\n=== Testing Cable Accessory ===" << std::endl;
  try {
    // 测试直接接地箱
    auto shp1 = create_cable_accessory(
        cable_accessory_params{.type = cable_box_type::DIRECT_GROUND,
                               .length = 500.0,
                               .width = 400.0,
                               .height = 300.0,
                               .portCount = 3,
                               .portDiameter = 100.0,
                               .portSpacing = 180,
                               .backPanelDistance = 50.0,
                               .sidePanelDistance = 60.0});

    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create direct ground box" << std::endl;
      return;
    }
    test_export_shape(shp1, "./direct_ground_box.stl");

    // 测试带护层保护器的接地箱
    auto shp2 = create_cable_accessory(
        cable_accessory_params{.type = cable_box_type::PROTECTIVE_GROUND,
                               .length = 600.0,
                               .width = 500.0,
                               .height = 400.0,
                               .portCount = 6,
                               .portDiameter = 120.0,
                               .portSpacing = 180,
                               .backPanelDistance = 60.0,
                               .sidePanelDistance = 70.0});

    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create protective ground box" << std::endl;
      return;
    }
    test_export_shape(shp2, "./protective_ground_box.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_cable_terminal() {
  std::cout << "\n=== Testing Cable Terminal ===" << std::endl;

  try {
    // 测试户外终端
    cable_terminal_params outdoor_params{.sort = 1, // 户外终端
                                         .height = 1000,
                                         .topDiameter = 200,
                                         .bottomDiameter = 300,
                                         .tailDiameter = 350,
                                         .tailHeight = 50,
                                         .skirtCount = 18,
                                         .upperSkirtTopDiameter = 330,
                                         .upperSkirtBottomDiameter = 340,
                                         .lowerSkirtTopDiameter = 380,
                                         .lowerSkirtBottomDiameter = 400,
                                         .skirtSectionHeight = 40,
                                         .upperTerminalLength = 100,
                                         .upperTerminalDiameter = 80,
                                         .lowerTerminalLength = 120,
                                         .lowerTerminalDiameter = 100,
                                         .hole1Diameter = 20,
                                         .hole2Diameter = 20,
                                         .hole1Distance = 30,
                                         .holeSpacing = 40,
                                         .flangeHoleDiameter = 25,
                                         .flangeHoleSpacing = 400,
                                         .flangeWidth = 450,
                                         .flangeCenterHoleRadius = 75,
                                         .flangeChamferRadius = 10,
                                         .flangeOpeningWidth = 120,
                                         .flangeBoltHeight = 40};

    auto outdoor_terminal = create_cable_terminal(outdoor_params);
    if (outdoor_terminal.IsNull()) {
      std::cerr << "Error: Failed to create outdoor terminal" << std::endl;
      return;
    }
    test_export_shape(outdoor_terminal, "./outdoor_terminal.stl");

    // 测试户内终端
    cable_terminal_params indoor_params{.sort = 2, // 户内终端
                                        .height = 800,
                                        .topDiameter = 180,
                                        .bottomDiameter = 220,
                                        .tailDiameter = 0, // 户内无尾管
                                        .tailHeight = 0,
                                        .upperTerminalLength = 80,
                                        .upperTerminalDiameter = 70,
                                        .lowerTerminalLength = 100,
                                        .lowerTerminalDiameter = 90};

    auto indoor_terminal = create_cable_terminal(indoor_params);
    if (indoor_terminal.IsNull()) {
      std::cerr << "Error: Failed to create indoor terminal" << std::endl;
      return;
    }
    test_export_shape(indoor_terminal, "./indoor_terminal.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_cable_clamp() {
  std::cout << "\n=== Testing Cable Clamp ===" << std::endl;

  try {
    // 测试单根夹具
    auto singleClamp =
        create_cable_clamp(cable_clamp_params{.type = cable_clamp_type::SINGLE,
                                              .diameter = 50.0,
                                              .thickness = 10.0,
                                              .width = 30.0});
    if (singleClamp.IsNull()) {
      std::cerr << "Error: Failed to create single cable clamp" << std::endl;
      return;
    }
    test_export_shape(singleClamp, "./single_clamp.stl");

    // 测试一字式夹具
    auto linearClamp =
        create_cable_clamp(cable_clamp_params{.type = cable_clamp_type::LINEAR,
                                              .diameter = 60.0,
                                              .thickness = 12.0,
                                              .width = 40.0});
    if (linearClamp.IsNull()) {
      std::cerr << "Error: Failed to create linear cable clamp" << std::endl;
      return;
    }
    test_export_shape(linearClamp, "./linear_clamp.stl");

    // 测试品字接触式夹具
    auto contactTripleClamp = create_cable_clamp(
        cable_clamp_params{.type = cable_clamp_type::CONTACT_TRIPLE,
                           .diameter = 70.0,
                           .thickness = 15.0,
                           .width = 50.0});
    if (contactTripleClamp.IsNull()) {
      std::cerr << "Error: Failed to create contact triple cable clamp"
                << std::endl;
      return;
    }
    test_export_shape(contactTripleClamp, "./contact_triple_clamp.stl");

    // 测试品字分离式夹具
    auto separateTripleClamp = create_cable_clamp(
        cable_clamp_params{.type = cable_clamp_type::SEPARATE_TRIPLE,
                           .diameter = 80.0,
                           .thickness = 18.0,
                           .width = 60.0});
    if (separateTripleClamp.IsNull()) {
      std::cerr << "Error: Failed to create separate triple cable clamp"
                << std::endl;
      return;
    }
    test_export_shape(separateTripleClamp, "./separate_triple_clamp.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_cable_bracket() {
  std::cout << "\n=== Testing Cable Bracket ===" << std::endl;
  try {
    // 创建测试用的安装点
    std::vector<gp_Pnt> columnPoints = {gp_Pnt(10, -8.0, -10),
                                        gp_Pnt(10, -8.0, -35)};
    std::vector<gp_Pnt> clampPoints = {gp_Pnt(90, -5.0, -7.5),
                                       gp_Pnt(50, -5.0, -7.5)};

    // 测试默认参数创建
    auto shp = create_cable_bracket(
        cable_bracket_params{.length = 100.0,      // 支架长度 L
                             .rootHeight = 50.0,   // 根部高度 H
                             .rootWidth = 20.0,    // 根部宽度 B
                             .width = 15.0,        // 支架宽度 C
                             .topThickness = 5.0,  // 顶部厚度 t
                             .rootThickness = 8.0, // 根部厚度 T
                             .columnMountPoints = columnPoints,
                             .clampMountPoints = clampPoints});

    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create cable bracket" << std::endl;
      return;
    }
    test_export_shape(shp, "./cable_bracket.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_cable_pole() {
  std::cout << "\n=== Testing Cable Pole ===" << std::endl;

  // 创建测试用的安装点
  std::vector<gp_Pnt> mountPoints = {
      gp_Pnt(-20, 0, 50),  // 第一个安装点
      gp_Pnt(20, 0, 50),   // 第二个安装点
      gp_Pnt(-20, 0, 100), // 第三个安装点
      gp_Pnt(20, 0, 100),  // 第四个安装点
      gp_Pnt(-20, 0, 150), // 第五个安装点
      gp_Pnt(20, 0, 150),  // 第六个安装点
  };

  // 测试默认参数创建
  auto shp = create_cable_pole(cable_pole_params{
      .specification = "GJ-DLLZ-1", // 规格型号
      .length = 200.0,              // 立柱长度(mm)
      .radius = 0,                  // 立柱半径(mm)
      .arcAngle = M_PI / 4,         // 立柱弧度(π/4)
      .width = 20.0,                // 立柱宽度(mm)
      .fixedLegLength = 20.0,       // 固定肢长度(mm)
      .fixedLegWidth = 10.0,        // 固定肢宽度(mm)
      .thickness = 5.0,             // 立柱厚度(mm)
      .mountPoints = mountPoints    // 安装点
  });

  if (shp.IsNull()) {
    std::cerr << "Error: Failed to create cable pole" << std::endl;
    return;
  }

  test_export_shape(shp, "./cable_pole.stl");

  // 弧形立柱测试参数
  // 弧形立柱测试参数
  cable_pole_params params{
      .specification = "GJ-DLLZ-2",
      .length = 200.0,        // 立柱总高度
      .radius = 50.0,         // 圆弧半径
      .arcAngle = M_PI / 2,   // 90度圆弧
      .width = 20.0,          // 立柱宽度
      .fixedLegLength = 16.0, // 固定肢长度
      .fixedLegWidth = 8.0,   // 固定肢宽度
      .thickness = 3.0        // 立柱厚度
  };
  // 计算弧形立柱上的安装点位置（XZ平面坐标系）
  for (int i = 0; i < 6; i++) {
    double angle = params.arcAngle * i / 5;

    // 圆弧路径坐标（XZ平面）
    double x = params.radius * sin(angle);       // X轴坐标
    double z = params.radius * (1 - cos(angle)); // Z轴坐标

    // 直接使用圆弧路径的z坐标（无需叠加高度参数）
    params.mountPoints.push_back(gp_Pnt(x, params.width / 2 + 8, z));  // 外侧
    params.mountPoints.push_back(gp_Pnt(x, -params.width / 2 - 8, z)); // 内侧
  }
  // 测试弧形立柱（更新相关参数）
  auto arcPole = create_cable_pole(params);

  if (arcPole.IsNull()) {
    std::cerr << "Error: Failed to create arc cable pole" << std::endl;
    return;
  }
  test_export_shape(arcPole, "./arc_cable_pole.stl");
}

void test_make_ground_flat_iron() {
  std::cout << "\n=== Testing Ground Flat Iron ===" << std::endl;

  ground_flat_iron_params params{
      .length = 100.0,  // 100mm长度
      .height = 20.0,   // 20mm高度
      .thickness = 10.0 // 10mm厚度
  };

  auto shp = create_ground_flat_iron(params);
  if (shp.IsNull()) {
    std::cerr << "Error: Failed to create ground flat iron" << std::endl;
    return;
  }
  test_export_shape(shp, "./ground_flat_iron.stl");
}

void test_make_embedded_part() {
  std::cout << "\n=== Testing Embedded Part ===" << std::endl;

  embedded_part_params params{
      .length = 100.0,       // 预埋件主体长度
      .radius = 20.0,        // 半圆钩半径
      .height = 50.0,        // 总高度
      .materialRadius = 5.0, // 材料半径
      .lowerLength = 30.0    // 下部延伸长度
  };

  try {
    auto shp = create_embedded_part(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create embedded part" << std::endl;
      return;
    }
    test_export_shape(shp, "./embedded_part.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_u_shaped_ring() {
  std::cout << "\n=== Testing U-Shaped Ring ===" << std::endl;

  u_shaped_ring_params params{
      .thickness = 5.0, // 材料厚度
      .height = 30.0,   // 开口高度
      .radius = 25.0,   // 弯曲半径
      .length = 100.0   // 总长度
  };

  try {
    auto shp = create_u_shaped_ring(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create U-shaped ring" << std::endl;
      return;
    }
    test_export_shape(shp, "./u_shaped_ring.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_lifting_eye() {
  std::cout << "\n=== Testing Lifting Eye ===" << std::endl;

  lifting_eye_params params{
      .height = 100.0,     // 吊臂高度
      .ringRadius = 25.0,  // 圆环半径
      .pipeDiameter = 10.0 // 钢管直径
  };

  try {
    auto shp = create_lifting_eye(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create lifting eye" << std::endl;
      return;
    }
    test_export_shape(shp, "./lifting_eye.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_tunnel_well() {
  std::cout << "\n=== Testing Tunnel Well ===" << std::endl;

  try {
    // 测试矩形连接段
    auto shp1 = create_tunnel_well(
        tunnel_well_params{.type = tunnel_well_type::STRAIGHT,
                           .length = 800.0,
                           .width = 150.0,
                           .height = 180.0,
                           .topThickness = 20.0,
                           .bottomThickness = 25.0,
                           .outerWallThickness = 30.0,
                           .cushionExtension = 10.0,
                           .cushionThickness = 15.0});
    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create rectangular tunnel well"
                << std::endl;
    } else {
      test_export_shape(shp1, "./tunnel_straight_well.stl");
    }

    // 测试圆形连接段
    auto shp2 = create_tunnel_well(tunnel_well_params{
        .type = tunnel_well_type::STRAIGHT_TUNNEL,
        .length = 150.0,
        .width = 120.0,
        .height = 140.0,
        .radius = 60.0,
        .topThickness = 15.0,
        .bottomThickness = 20.0,
        .leftSectionType = connection_section_style::CIRCULAR,
        .leftLength = 800.0,
        .leftWidth = 100.0,
        .leftHeight = 140.0,
        .rightSectionType = connection_section_style::CIRCULAR,
        .rightLength = 600.0,
        .rightWidth = 80.0,
        .rightHeight = 100.0,
        .outerWallThickness = 20.0,
        .innerWallThickness = 20.0});
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create circular tunnel well" << std::endl;
    } else {
      test_export_shape(shp2, "./tunnel_well_circular.stl");
    }

    // 测试矩形连接段
    auto shp3 = create_tunnel_well(tunnel_well_params{
        .type = tunnel_well_type::STRAIGHT_TUNNEL,
        .length = 150.0,
        .width = 120.0,
        .height = 140.0,
        .radius = 60.0,
        .topThickness = 15.0,
        .bottomThickness = 20.0,
        .leftSectionType = connection_section_style::RECTANGULAR,
        .leftLength = 800.0,
        .leftWidth = 100.0,
        .leftHeight = 140.0,
        .rightSectionType = connection_section_style::RECTANGULAR,
        .rightLength = 600.0,
        .rightWidth = 80.0,
        .rightHeight = 100.0,
        .outerWallThickness = 20.0,
        .innerWallThickness = 20.0});
    if (shp3.IsNull()) {
      std::cerr << "Error: Failed to create rectangular tunnel well"
                << std::endl;
    } else {
      test_export_shape(shp3, "./tunnel_well_rectangular.stl");
    }

    // 测试马蹄形连接段
    auto shp4 = create_tunnel_well(tunnel_well_params{
        .type = tunnel_well_type::STRAIGHT_TUNNEL,
        .length = 150.0,
        .width = 120.0,
        .height = 140.0,
        .radius = 50.0,
        .topThickness = 15.0,
        .bottomThickness = 20.0,
        .leftSectionType = connection_section_style::HORSESHOE,
        .leftLength = 800.0,
        .leftWidth = 100.0,
        .leftHeight = 140.0,
        .leftArchHeight = 30.0,
        .rightSectionType = connection_section_style::HORSESHOE,
        .rightLength = 600.0,
        .rightWidth = 80.0,
        .rightHeight = 100.0,
        .rightArchHeight = 25.0,
        .outerWallThickness = 20.0,
        .innerWallThickness = 20.0});
    if (shp4.IsNull()) {
      std::cerr << "Error: Failed to create horseshoe tunnel well" << std::endl;
    } else {
      test_export_shape(shp4, "./tunnel_well_horseshoe.stl");
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_corner_well() {
  std::cout << "\n=== Testing Corner Well ===" << std::endl;
  try {
    // 测试基本转角井
    corner_well_params params{
        .leftLength = 800.0,      // 左段长800mm
        .rightLength = 600.0,     // 右段长600mm
        .width = 150.0,           // 净宽150mm
        .height = 180.0,          // 净高180mm
        .topThickness = 20.0,     // 顶板厚20mm
        .bottomThickness = 25.0,  // 底板厚25mm
        .wallThickness = 30.0,    // 壁厚30mm
        .angle = 90.0,            // 转角90度
        .cornerRadius = 100.0,    // 转角半径100mm
        .cushionExtension = 10.0, // 垫层滋出10mm
        .cushionThickness = 15.0  // 垫层厚15mm
    };

    auto shp = create_corner_well(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create corner well" << std::endl;
      return;
    }
    test_export_shape(shp, "./corner_well.stl");

    // 测试不同转角角度
    params.angle = 120.0;
    auto shp2 = create_corner_well(params);
    test_export_shape(shp2, "./corner_well_120deg.stl");

    // 测试不同转角半径
    params.angle = 90.0;
    params.cornerRadius = 150.0;
    auto shp3 = create_corner_well(params);
    test_export_shape(shp3, "./corner_well_large_radius.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_three_way_working_well() {
  std::cout << "\n=== Testing Three Way Working Well ===" << std::endl;

  // 1. 圆形转角三通井测试
  try {
    three_way_well_params roundParams{.type = three_way_well_type::WORKING_WELL,
                                      .cornerType = corner_style::ROUNDED,
                                      .shaftType = shaft_style::RECTANGULAR,
                                      .length = 200.0,
                                      .width = 80.0,
                                      .height = 60.0,
                                      .cornerRadius = 30.0,
                                      .angle = 90.0,
                                      .branchLength = 100.0,
                                      .branchWidth = 80.0,
                                      .topThickness = 10.0,
                                      .bottomThickness = 10.0,
                                      .outerWallThickness = 5.0,
                                      .innerWallThickness = 3.0,
                                      .cushionExtension = 10.0,
                                      .cushionThickness = 15.0};

    auto roundShp = create_three_way_well(roundParams);
    if (roundShp.IsNull()) {
      std::cerr << "Error: Failed to create round corner three way well"
                << std::endl;
    } else {
      test_export_shape(roundShp, "./three_way_round_working_well.stl");
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Round Corner Construction Error: " << e.GetMessageString()
              << std::endl;
  }

  // 2. 折角形转角三通井测试
  try {
    three_way_well_params angledParams{.type =
                                           three_way_well_type::WORKING_WELL,
                                       .cornerType = corner_style::ANGLED,
                                       .shaftType = shaft_style::RECTANGULAR,
                                       .length = 200.0,
                                       .width = 80.0,
                                       .height = 60.0,
                                       .cornerLength = 20.0,
                                       .cornerWidth = 20.0,
                                       .angle = 90.0,
                                       .branchLength = 100.0,
                                       .branchWidth = 80.0,
                                       .topThickness = 10.0,
                                       .bottomThickness = 10.0,
                                       .outerWallThickness = 5.0,
                                       .innerWallThickness = 3.0,
                                       .cushionExtension = 10.0,
                                       .cushionThickness = 15.0};

    auto angledShp = create_three_way_well(angledParams);
    if (angledShp.IsNull()) {
      std::cerr << "Error: Failed to create angled corner three way well"
                << std::endl;
    } else {
      test_export_shape(angledShp, "./three_way_angled_working_well.stl");
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Angled Corner Construction Error: " << e.GetMessageString()
              << std::endl;
  }

  // 3. 带角度和倒角的圆形转角三通井测试
  try {
    three_way_well_params chamferParams{.type =
                                            three_way_well_type::WORKING_WELL,
                                        .cornerType = corner_style::ROUNDED,
                                        .shaftType = shaft_style::RECTANGULAR,
                                        .length = 200.0,
                                        .width = 80.0,
                                        .height = 60.0,
                                        .cornerRadius = 80.0,
                                        .angle = 70.0,
                                        .branchLength = 100.0,
                                        .branchLeftLength = 30,
                                        .branchWidth = 80.0,
                                        .topThickness = 10.0,
                                        .bottomThickness = 10.0,
                                        .outerWallThickness = 5.0,
                                        .innerWallThickness = 3.0,
                                        .cushionExtension = 5.0,
                                        .cushionThickness = 5.0};

    auto chamferShp = create_three_way_well(chamferParams);
    if (chamferShp.IsNull()) {
      std::cerr << "Error: Failed to create chamfer round corner three way well"
                << std::endl;
    } else {
      test_export_shape(chamferShp,
                        "./three_way_chamfer_round_working_well.stl");
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Chamfer Round Corner Construction Error: "
              << e.GetMessageString() << std::endl;
  }
}

void test_make_three_way_open_cut_tunnel() {
  std::cout << "\n=== Testing Three Way Open Cut Tunnel ===" << std::endl;
  try {
    three_way_well_params params{
        .type = three_way_well_type::OPEN_CUT_TUNNEL,
        .cornerType = corner_style::ROUNDED,
        .shaftType = shaft_style::RECTANGULAR,
        .length = 200.0,
        .width = 80.0,
        .height = 60.0,
        .cornerRadius = 30.0,
        .angle = 90.0,
        .branchLength = 100.0,
        .branchWidth = 80.0,
        .topThickness = 10.0,
        .bottomThickness = 10.0,
        .leftSectionStyle = connection_section_style::RECTANGULAR,
        .leftSectionLength = 60.0,
        .leftSectionWidth = 80.0,
        .leftSectionHeight = 90.0,
        .leftSectionArchHeight = 15.0,
        .rightSectionStyle = connection_section_style::RECTANGULAR,
        .rightSectionLength = 60.0,
        .rightSectionWidth = 80.0,
        .rightSectionHeight = 90.0,
        .rightSectionArchHeight = 15.0,
        .branchSectionStyle = connection_section_style::HORSESHOE,
        .branchSectionLength = 80.0,
        .branchSectionWidth = 80.0,
        .branchSectionHeight = 50.0,
        .branchSectionArchHeight = 15.0,
        .outerWallThickness = 5.0,
        .innerWallThickness = 3.0,
        .isDoubleShaft = false,
        .doubleShaftSpacing = 0.0,
        .outerWallExtension = 10.0,
        .innerWallExtension = 5.0,
        .cushionExtension = 10.0,
        .cushionThickness = 10.0,
        .innerBottomThickness = 18.0,
        .outerBottomThickness = 20.0};

    auto shp = create_three_way_well(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create three way open cut tunnel"
                << std::endl;
      return;
    }
    test_export_shape(shp, "./three_way_open_cut_tunnel.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_three_way_underground_tunnel() {
  std::cout << "\n=== Testing Three Way UnderGround Tunnel ===" << std::endl;
  try {
    three_way_well_params params{
        .type = three_way_well_type::UNDERGROUND_TUNNEL,
        .cornerType = corner_style::ROUNDED,
        .shaftType = shaft_style::CIRCULAR,
        .length = 200.0,
        .width = 80.0,
        .height = 60.0,
        .shaftRadius = 80.0,
        .cornerRadius = 30.0,
        .cornerLength = 40.0,
        .cornerWidth = 35.0,
        .branchLength = 120.0,
        .branchLeftLength = 80.0,
        .branchWidth = 100.0,
        .topThickness = 20.0,
        .bottomThickness = 25.0,
        .leftSectionStyle = connection_section_style::RECTANGULAR,
        .leftSectionLength = 60.0,
        .leftSectionWidth = 80.0,
        .leftSectionHeight = 90.0,
        .leftSectionArchHeight = 15.0,
        .rightSectionStyle = connection_section_style::RECTANGULAR,
        .rightSectionLength = 60.0,
        .rightSectionWidth = 80.0,
        .rightSectionHeight = 90.0,
        .rightSectionArchHeight = 15.0,
        .branchSectionStyle = connection_section_style::HORSESHOE,
        .branchSectionLength = 80.0,
        .branchSectionWidth = 80.0,
        .branchSectionHeight = 50.0,
        .branchSectionArchHeight = 15.0,
        .outerWallThickness = 5.0,
        .innerWallThickness = 3.0,
        .isDoubleShaft = false,
        .doubleShaftSpacing = 0.0,
        .outerWallExtension = 10.0,
        .innerWallExtension = 5.0,
        .cushionExtension = 15.0,
        .cushionThickness = 10.0,
        .innerBottomThickness = 18.0,
        .outerBottomThickness = 20.0};

    auto shp = create_three_way_well(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create three way open cut tunnel"
                << std::endl;
      return;
    }
    test_export_shape(shp, "./three_way_underground_tunnel.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_three_way_double_shaft_tunnel() {
  std::cout << "\n=== Testing Three Way double shaft Tunnel ===" << std::endl;
  try {
    three_way_well_params params{
        .type = three_way_well_type::UNDERGROUND_TUNNEL,
        .cornerType = corner_style::ROUNDED,
        .shaftType = shaft_style::CIRCULAR,
        .length = 200.0,
        .width = 80.0,
        .height = 60.0,
        .shaftRadius = 80.0,
        .cornerRadius = 30.0,
        .cornerLength = 40.0,
        .cornerWidth = 35.0,
        .branchLength = 120.0,
        .branchLeftLength = 80.0,
        .branchWidth = 100.0,
        .topThickness = 20.0,
        .bottomThickness = 25.0,
        .leftSectionStyle = connection_section_style::RECTANGULAR,
        .leftSectionLength = 60.0,
        .leftSectionWidth = 80.0,
        .leftSectionHeight = 90.0,
        .leftSectionArchHeight = 15.0,
        .rightSectionStyle = connection_section_style::RECTANGULAR,
        .rightSectionLength = 60.0,
        .rightSectionWidth = 80.0,
        .rightSectionHeight = 90.0,
        .rightSectionArchHeight = 15.0,
        .branchSectionStyle = connection_section_style::HORSESHOE,
        .branchSectionLength = 80.0,
        .branchSectionWidth = 80.0,
        .branchSectionHeight = 50.0,
        .branchSectionArchHeight = 15.0,
        .outerWallThickness = 5.0,
        .innerWallThickness = 3.0,
        .isDoubleShaft = true,
        .doubleShaftSpacing = 0.0,
        .outerWallExtension = 10.0,
        .innerWallExtension = 5.0,
        .cushionExtension = 15.0,
        .cushionThickness = 10.0,
        .innerBottomThickness = 18.0,
        .outerBottomThickness = 20.0};

    auto shp = create_three_way_well(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create three way double shaft tunnel"
                << std::endl;
      return;
    }
    test_export_shape(shp, "./three_way_double_shaft_tunnel.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_four_way_working_well() {
  std::cout << "\n=== Testing Four Way Working Well ===" << std::endl;

  // 1. 圆形转角四通井测试
  try {
    four_way_well_params roundParams{.type = four_way_well_type::WORKING_WELL,
                                     .length = 200.0,
                                     .width = 80.0,
                                     .height = 60.0,
                                     .cornerStyle = corner_style::ROUNDED,
                                     .cornerRadius = 30.0,
                                     .branchLength = 100.0,
                                     .branchWidth = 80.0,
                                     .topThickness = 10.0,
                                     .bottomThickness = 10.0,
                                     .outerWallThickness = 5.0,
                                     .innerWallThickness = 3.0,
                                     .cushionExtension = 10.0,
                                     .cushionThickness = 15.0};

    auto roundShp = create_four_way_well(roundParams);
    if (roundShp.IsNull()) {
      std::cerr << "Error: Failed to create round corner four way well"
                << std::endl;
    } else {
      test_export_shape(roundShp, "./four_way_round_working_well.stl");
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Round Corner Construction Error: " << e.GetMessageString()
              << std::endl;
  }

  // 2. 折角形转角四通井测试
  try {
    four_way_well_params angledParams{.type = four_way_well_type::WORKING_WELL,
                                      .length = 200.0,
                                      .width = 80.0,
                                      .height = 60.0,
                                      .cornerStyle = corner_style::ANGLED,
                                      .cornerLength = 20.0,
                                      .cornerWidth = 20.0,
                                      .branchLength = 100.0,
                                      .branchWidth = 80.0,
                                      .topThickness = 10.0,
                                      .bottomThickness = 10.0,
                                      .outerWallThickness = 5.0,
                                      .innerWallThickness = 3.0,
                                      .cushionExtension = 10.0,
                                      .cushionThickness = 15.0};

    auto angledShp = create_four_way_well(angledParams);
    if (angledShp.IsNull()) {
      std::cerr << "Error: Failed to create angled corner four way well"
                << std::endl;
    } else {
      test_export_shape(angledShp, "./four_way_angled_working_well.stl");
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Angled Corner Construction Error: " << e.GetMessageString()
              << std::endl;
  }
}

void test_make_four_way_open_cut_tunnel() {
  std::cout << "\n=== Testing Four Way Open Cut Tunnel ===" << std::endl;
  try {
    four_way_well_params params{
        .type = four_way_well_type::OPEN_CUT_TUNNEL,
        .length = 200.0,
        .width = 80.0,
        .height = 60.0,
        .cornerStyle = corner_style::ROUNDED,
        .cornerRadius = 30.0,
        .branchLength = 100.0,
        .branchWidth = 80.0,
        .topThickness = 10.0,
        .bottomThickness = 10.0,
        .leftSection =
            {
                .sectionType = connection_section_style::RECTANGULAR,
                .length = 60.0,
                .width = 80.0,
                .height = 90.0,
                .archHeight = 15.0,
            },
        .rightSection =
            {
                .sectionType = connection_section_style::RECTANGULAR,
                .length = 60.0,
                .width = 80.0,
                .height = 90.0,
                .archHeight = 15.0,
            },
        .branchSection1 =
            {
                .sectionType = connection_section_style::HORSESHOE,
                .length = 80.0,
                .width = 80.0,
                .height = 50.0,
                .archHeight = 15.0,
            },
        .branchSection2 =
            {
                .sectionType = connection_section_style::HORSESHOE,
                .length = 80.0,
                .width = 80.0,
                .height = 50.0,
                .archHeight = 15.0,
            },
        .outerWallThickness = 5.0,
        .innerWallThickness = 3.0,
        .cushionExtension = 10.0,
        .cushionThickness = 10.0};

    auto shp = create_four_way_well(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create four way open cut tunnel"
                << std::endl;
      return;
    }
    test_export_shape(shp, "./four_way_open_cut_tunnel.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_four_way_underground_tunnel() {
  std::cout << "\n=== Testing Four Way UnderGround Tunnel ===" << std::endl;
  try {
    four_way_well_params params{
        .type = four_way_well_type::UNDERGROUND_TUNNEL,
        .length = 200.0,
        .width = 80.0,
        .height = 60.0,
        .shaftRadius = 80.0,
        .cornerStyle = corner_style::ROUNDED,
        .cornerRadius = 30.0,
        .branchLength = 100.0,
        .branchWidth = 80.0,
        .topThickness = 10.0,
        .bottomThickness = 10.0,
        .leftSection =
            {
                .sectionType = connection_section_style::RECTANGULAR,
                .length = 60.0,
                .width = 80.0,
                .height = 90.0,
                .archHeight = 15.0,
            },
        .rightSection =
            {
                .sectionType = connection_section_style::RECTANGULAR,
                .length = 60.0,
                .width = 80.0,
                .height = 90.0,
                .archHeight = 15.0,
            },
        .branchSection1 =
            {
                .sectionType = connection_section_style::HORSESHOE,
                .length = 80.0,
                .width = 80.0,
                .height = 50.0,
                .archHeight = 15.0,
            },
        .branchSection2 =
            {
                .sectionType = connection_section_style::HORSESHOE,
                .length = 80.0,
                .width = 80.0,
                .height = 50.0,
                .archHeight = 15.0,
            },
        .outerWallThickness = 5.0,
        .innerWallThickness = 3.0,
        .cushionExtension = 10.0,
        .cushionThickness = 10.0};

    auto shp = create_four_way_well(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create four way open cut tunnel"
                << std::endl;
      return;
    }
    test_export_shape(shp, "./four_way_underground_tunnel.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_pipe_row() {
  std::cout << "\n=== Testing Pipe Row ===" << std::endl;

  // 创建测试点集
  std::vector<channel_point> points = {
      {gp_Pnt(0, 0, 0), 0},      // 起点
      {gp_Pnt(300, 0, 30), 0},   // 开始右转
      {gp_Pnt(500, 300, 50), 1}, // 过渡点(最高点)
      {gp_Pnt(300, 600, 20), 0}, // 开始左转
      {gp_Pnt(300, 800, 0), 0}   // 终点
  };

  // 测试普通排管无封包
  try {
    pipe_row_params params{
        .pipeType = 1,
        .hasEnclosure = false,
        .baseExtension = 20,
        .baseThickness = 5,
        .pipePositions = {gp_Pnt2d(-50, 40), gp_Pnt2d(0, 40), gp_Pnt2d(50, 40)},
        .pipeInnerDiameters = {20, 30, 20},
        .pipeWallThicknesses = {4, 4, 4},
        .points = points};

    auto shp = create_pipe_row(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create pipe row without enclosure"
                << std::endl;
      return;
    }
    test_export_shape(shp, "./pipe_row_no_enclosure.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }

  // 测试普通排管有封包
  try {
    pipe_row_params params{
        .pipeType = 1,
        .hasEnclosure = true,
        .enclosureWidth = 200,
        .enclosureHeight = 200,
        .baseExtension = 5,
        .baseThickness = 10,
        .cushionExtension = 5,
        .cushionThickness = 10,
        .pipePositions = {gp_Pnt2d(-50, 40), gp_Pnt2d(0, 40), gp_Pnt2d(50, 40)},
        .pipeInnerDiameters = {20, 30, 20},
        .pipeWallThicknesses = {4, 4, 4},
        .points = points};

    auto shp = create_pipe_row(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create pipe row with enclosure"
                << std::endl;
      return;
    }
    test_export_shape(shp, "./pipe_row_with_enclosure.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }

  // 测试拉管
  try {
    pipe_row_params params{
        .pipeType = 2,
        .pipePositions = {gp_Pnt2d(-50, 40), gp_Pnt2d(50, 40)},
        .pipeInnerDiameters = {50, 50},
        .pipeWallThicknesses = {6, 6},
        .pullPipeInnerDiameter = 200,
        .pullPipeThickness = 8,
        .points = points};

    auto shp = create_pipe_row(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create pull pipe" << std::endl;
      return;
    }
    test_export_shape(shp, "./pull_pipe.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_cable_trench() {
  std::cout << "\n=== Testing Cable Trench ===" << std::endl;

  // 创建测试点集
  std::vector<channel_point> points = {
      {gp_Pnt(0, 0, 0), 0},      // 起点
      {gp_Pnt(300, 0, 30), 0},   // 开始右转
      {gp_Pnt(500, 300, 50), 1}, // 过渡点(最高点)
      {gp_Pnt(300, 600, 20), 0}, // 开始左转
      {gp_Pnt(300, 800, 0), 0}   // 终点
  };

  // 测试标准参数
  try {
    cable_trench_params params{.width = 60.0,            // 600→60
                               .height = 80.0,           // 800→80
                               .coverWidth = 64.0,       // 620→62
                               .coverThickness = 5.0,    // 50→5
                               .baseExtension = 10.0,    // 100→10
                               .baseThickness = 15.0,    // 150→15
                               .cushionExtension = 12.0, // 120→12
                               .cushionThickness = 10.0, // 100→10
                               .wallThickness = 15.0,    // 200→20
                               .wallThickness2 = 10.0,   // 150→15
                               .points = points};

    auto shp = create_cable_trench(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create standard cable trench" << std::endl;
      return;
    }
    test_export_shape(shp, "./standard_cable_trench.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_cable_tunnel() {
  std::cout << "\n=== Testing Cable Tunnel ===" << std::endl;

  // 创建测试点集
  std::vector<channel_point> points = {
      {gp_Pnt(0, 0, 0), 0},      // 起点
      {gp_Pnt(300, 0, 30), 0},   // 开始右转
      {gp_Pnt(500, 300, 50), 1}, // 过渡点(最高点)
      {gp_Pnt(300, 600, 20), 0}, // 开始左转
      {gp_Pnt(300, 800, 0), 0}   // 终点
  };

  // 测试矩形截面隧道 (所有尺寸参数缩小10倍)
  try {
    cable_tunnel_params rect_params{.style =
                                        connection_section_style::RECTANGULAR,
                                    .width = 60.0,             // 600→60
                                    .height = 80.0,            // 800→80
                                    .topThickness = 5.0,       // 50→5
                                    .bottomThickness = 6.0,    // 60→6
                                    .outerWallThickness = 7.0, // 70→7
                                    .cushionExtension = 5.0,   // 100→10
                                    .cushionThickness = 8.0,   // 80→8
                                    .points = points};

    auto rect_shp = create_cable_tunnel(rect_params);
    if (rect_shp.IsNull()) {
      std::cerr << "Error: Failed to create rectangular cable tunnel"
                << std::endl;
    } else {
      test_export_shape(rect_shp, "./rectangular_cable_tunnel.stl");
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }

  // 测试马蹄形截面隧道 (所有尺寸参数缩小10倍)
  try {
    cable_tunnel_params horseshoe_params{
        .style = connection_section_style::HORSESHOE,
        .width = 50.0,             // 500→50
        .height = 70.0,            // 700→70
        .outerWallThickness = 4.0, // 40→4
        .innerWallThickness = 3.0, // 30→3
        .archHeight = 12.0,        // 100→10
        .cushionExtension = 5.0,   // 90→9
        .cushionThickness = 7.0,   // 70→7
        .points = points};

    auto horseshoe_shp = create_cable_tunnel(horseshoe_params);
    if (horseshoe_shp.IsNull()) {
      std::cerr << "Error: Failed to create horseshoe cable tunnel"
                << std::endl;
    } else {
      test_export_shape(horseshoe_shp, "./horseshoe_cable_tunnel.stl");
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }

  // 测试圆形截面隧道 (所有尺寸参数缩小10倍)
  try {
    cable_tunnel_params circular_params{.style =
                                            connection_section_style::CIRCULAR,
                                        .width = 60.0,             // 600→60
                                        .height = 60.0,            // 600→60
                                        .outerWallThickness = 7.0, // 70→7
                                        .bottomPlatformHeight = 10.0, // 100→10
                                        .cushionExtension = 0.0,      // 80→8
                                        .cushionThickness = 0.0,      // 60→6
                                        .points = points};

    auto circular_shp = create_cable_tunnel(circular_params);
    if (circular_shp.IsNull()) {
      std::cerr << "Error: Failed to create circular cable tunnel" << std::endl;
    } else {
      test_export_shape(circular_shp, "./circular_cable_tunnel.stl");
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_cable_tray() {
  std::cout << "\n=== Testing Cable Tray ===" << std::endl;

  // 创建测试点集
  std::vector<channel_point> arcPoints = {
      {gp_Pnt(0, 0, 0), 0},    // 起点
      {gp_Pnt(900, 500, 0), 0} // 终点
  };

  // 测试拱形桥架
  try {
    cable_tray_params arch_params{
        .style = cable_tray_style::ARCH,
        .columnDiameter = 40.0,
        .columnHeight = 100.0,
        .span = 400.0,
        .width = 60.0,
        .height = 30.0,
        .topPlateHeight = 5.0,
        .archHeight = 55.0,
        .wallThickness = 3.0,
        .pipeCount = 3,
        .pipePositions = {gp_Pnt2d(-20, 15), gp_Pnt2d(0, 15), gp_Pnt2d(20, 15)},
        .pipeInnerDiameters = {10.0, 10.0, 10.0},
        .pipeWallThicknesses = {2.0, 2.0, 2.0},
        .hasProtectionPlate = true,
        .points = arcPoints};

    auto arch_shp = create_cable_tray(arch_params);
    if (arch_shp.IsNull()) {
      std::cerr << "Error: Failed to create arch cable tray" << std::endl;
    } else {
      test_export_shape(arch_shp, "./arch_cable_tray.stl");
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }

  // 创建测试点集
  std::vector<channel_point> points = {
      {gp_Pnt(0, 0, 0), 0},      // 起点
      {gp_Pnt(300, 0, 30), 0},   // 开始右转
      {gp_Pnt(500, 300, 50), 1}, // 过渡点(最高点)
      {gp_Pnt(300, 600, 20), 0}, // 开始左转
      {gp_Pnt(300, 800, 0), 0}   // 终点
  };

  // 测试平形桥架
  try {
    cable_tray_params beam_params{
        .style = cable_tray_style::BEAM,
        .columnDiameter = 40.0,
        .columnHeight = 100.0,
        .span = 200.0,
        .width = 60.0,
        .height = 30.0,
        .topPlateHeight = 5.0,
        .archHeight = 15.0,
        .wallThickness = 3.0,
        .pipeCount = 3,
        .pipePositions = {gp_Pnt2d(-20, 15), gp_Pnt2d(0, 15), gp_Pnt2d(20, 15)},
        .pipeInnerDiameters = {10.0, 10.0, 10.0},
        .pipeWallThicknesses = {2.0, 2.0, 2.0},
        .hasProtectionPlate = true,
        .points = points};

    auto beam_shp = create_cable_tray(beam_params);
    if (beam_shp.IsNull()) {
      std::cerr << "Error: Failed to create beam cable tray" << std::endl;
    } else {
      test_export_shape(beam_shp, "./beam_cable_tray.stl");
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

// 添加L型梁测试函数
void test_make_cable_L_beam() {
  std::cout << "\n=== Testing Cable L-Beam ===" << std::endl;
  try {
    // 标准参数测试
    auto shp = create_cable_L_beam(cable_L_beam_params{
        .length = 300.0, // 梁长300mm
        .width = 150.0,  // 梁宽150mm
        .height = 200.0  // 梁高200mm
    });
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create standard L-beam" << std::endl;
      return;
    }
    test_export_shape(shp, "./cable_L_beam.stl");

    // 极端参数测试
    auto shp2 = create_cable_L_beam(cable_L_beam_params{
        .length = 500.0, // 超长梁
        .width = 50.0,   // 窄宽度
        .height = 300.0  // 高梁
    });
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create extreme L-beam" << std::endl;
      return;
    }
    test_export_shape(shp2, "./cable_L_beam_extreme.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_manhole() {
  std::cout << "\n=== Testing Manhole ===" << std::endl;

  // 测试圆形人孔
  try {
    auto shp = create_manhole(manhole_params{
        .style = manhole_style::CIRCULAR,
        .length = 100.0,      // 直径100mm
        .width = 0.0,         // 圆形人孔宽度设为0
        .height = 150.0,      // 高度150mm
        .wallThickness = 10.0 // 壁厚10mm
    });
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create circular manhole" << std::endl;
    } else {
      test_export_shape(shp, "./circular_manhole.stl");
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }

  // 测试方形人孔
  try {
    auto shp = create_manhole(manhole_params{
        .style = manhole_style::RECTANGULAR,
        .length = 120.0,      // 长度120mm
        .width = 80.0,        // 宽度80mm
        .height = 150.0,      // 高度150mm
        .wallThickness = 10.0 // 壁厚10mm
    });
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create rectangular manhole" << std::endl;
    } else {
      test_export_shape(shp, "./rectangular_manhole.stl");
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_manhole_cover() {
  std::cout << "\n=== Testing Manhole Cover ===" << std::endl;

  // 测试圆形井盖
  try {
    auto shp = create_manhole_cover(manhole_cover_params{
        .style = manhole_cover_style::CIRCULAR,
        .length = 100.0,  // 直径100mm
        .width = 0.0,     // 圆形井盖宽度设为0
        .thickness = 10.0 // 厚度10mm
    });
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create circular manhole cover"
                << std::endl;
    } else {
      test_export_shape(shp, "./circular_manhole_cover.stl");
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }

  // 测试方形井盖
  try {
    auto shp = create_manhole_cover(manhole_cover_params{
        .style = manhole_cover_style::RECTANGULAR,
        .length = 120.0,  // 长度120mm
        .width = 80.0,    // 宽度80mm
        .thickness = 10.0 // 厚度10mm
    });
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create rectangular manhole cover"
                << std::endl;
    } else {
      test_export_shape(shp, "./rectangular_manhole_cover.stl");
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_ladder() {
  std::cout << "\n=== Testing Ladder ===" << std::endl;

  // 测试标准爬梯
  try {
    auto shp = create_ladder(ladder_params{
        .length = 3000.0, // 长度3000mm
        .width = 400.0,   // 宽度400mm
        .thickness = 20.0 // 厚度20mm
    });
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create standard ladder" << std::endl;
    } else {
      test_export_shape(shp, "./standard_ladder.stl");
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_sump() {
  std::cout << "\n=== Testing Sump ===" << std::endl;

  // 测试标准集水坑
  try {
    auto shp = create_sump(sump_params{
        .length = 500.0,        // 长度500mm
        .width = 300.0,         // 宽度300mm
        .depth = 400.0,         // 深度400mm
        .bottomThickness = 50.0 // 底板厚度50mm
    });
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create standard sump" << std::endl;
    } else {
      test_export_shape(shp, "./standard_sump.stl");
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }

  // 测试浅集水坑
  try {
    auto shp = create_sump(sump_params{
        .length = 600.0,        // 长度600mm
        .width = 400.0,         // 宽度400mm
        .depth = 200.0,         // 深度200mm
        .bottomThickness = 30.0 // 底板厚度30mm
    });
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create shallow sump" << std::endl;
    } else {
      test_export_shape(shp, "./shallow_sump.stl");
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_footpath() {
  std::cout << "\n=== Testing Footpath ===" << std::endl;

  // 创建测试点集
  std::vector<channel_point> points = {
      {gp_Pnt(0, 0, 0), 0},    // 起点
      {gp_Pnt(100, 0, 0), 0},  // 直线段
      {gp_Pnt(150, 50, 0), 1}, // 转弯点
      {gp_Pnt(150, 100, 0), 0} // 终点
  };

  // 测试标准步道
  try {
    auto shp = create_footpath(footpath_params{
        .height = 15.0,  // 高度150mm
        .width = 80.0,   // 宽度800mm
        .points = points // 路径点集
    });
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create standard footpath" << std::endl;
    } else {
      test_export_shape(shp, "./standard_footpath.stl");
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_shaft_chamber() {
  std::cout << "\n=== Testing Shaft Chamber ===" << std::endl;

  // 测试标准竖井室
  try {
    auto shp = create_shaft_chamber(shaft_chamber_params{
        .supportWallThickness = 20.0, // 支护壁厚20mm
        .supportDiameter = 110.0,     // 支护直径110mm
        .supportHeight = 50.0,        // 支护高度50mm
        .topThickness = 8.0,          // 顶板厚8mm
        .innerDiameter = 80.0,        // 内壁直径80mm
        .workingHeight = 120.0,       // 工作仓高度120mm
        .outerWallThickness = 12.0,   // 外壁厚12mm
        .innerWallThickness = 6.0     // 内壁厚6mm
    });
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create standard shaft chamber"
                << std::endl;
    } else {
      test_export_shape(shp, "./standard_shaft_chamber.stl");
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_tunnel_compartment_partition() {
  std::cout << "\n=== Testing Tunnel Compartment Partition ===" << std::endl;

  try {
    // 测试标准隧道分仓隔板
    auto shp =
        create_tunnel_compartment_partition(tunnel_compartment_partition_params{
            .width = 300.0,   // 隔板宽300mm
            .thickness = 15.0 // 隔板厚15mm
        });

    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create tunnel compartment partition"
                << std::endl;
    } else {
      test_export_shape(shp, "./tunnel_compartment_partition.stl");
    }

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}
void test_make_tunnel_partition_board() {
  std::cout << "\n=== Testing Tunnel Partition Board ===" << std::endl;

  try {
    // 测试圆形隔板
    auto shp1 = create_tunnel_partition_board(tunnel_partition_board_params{
        .style = 1,        // 圆形
        .length = 200.0,   // 直径200mm
        .width = 0.0,      // 圆形不需要宽度
        .thickness = 10.0, // 厚度10mm
        .holeCount = 4,
        .holePositions = {gp_Pnt2d(50, 50), gp_Pnt2d(-50, 50),
                          gp_Pnt2d(-50, -50), gp_Pnt2d(50, -50)},
        .holeStyles = {1, 1, 1, 1},                // 圆形孔
        .holeDiameters = {20.0, 20.0, 20.0, 20.0}, // 直径20mm
        .holeWidths = {0.0, 0.0, 0.0, 0.0}         // 圆形孔不需要宽度
    });

    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create circular partition board"
                << std::endl;
    } else {
      test_export_shape(shp1, "./circular_partition_board.stl");
    }

    // 测试方形隔板
    auto shp2 = create_tunnel_partition_board(tunnel_partition_board_params{
        .style = 2,        // 方形
        .length = 300.0,   // 长度300mm
        .width = 200.0,    // 宽度200mm
        .thickness = 15.0, // 厚度15mm
        .holeCount = 3,
        .holePositions = {gp_Pnt2d(100, 50), gp_Pnt2d(-100, 50),
                          gp_Pnt2d(0, -50)},
        .holeStyles = {1, 2, 1},             // 混合孔型
        .holeDiameters = {30.0, 40.0, 25.0}, // 圆形孔直径/方形孔长度
        .holeWidths = {0.0, 20.0, 0.0}       // 方形孔宽度
    });

    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create rectangular partition board"
                << std::endl;
    } else {
      test_export_shape(shp2, "./rectangular_partition_board.stl");
    }

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_ventilation_pavilion() {
  std::cout << "\n=== Testing Ventilation Pavilion ===" << std::endl;

  try {
    // 测试标准风亭
    auto shp = create_ventilation_pavilion(ventilation_pavilion_params{
        .topLength = 400.0,    // 顶长200mm
        .middleLength = 300.0, // 中部长度300mm
        .bottomLength = 400.0, // 底长400mm
        .topWidth = 350.0,     // 顶宽150mm
        .middleWidth = 250.0,  // 中部宽度250mm
        .bottomWidth = 350.0,  // 底宽350mm
        .topHeight = 100.0,     // 顶高50mm
        .height =  150.0,       // 总高300mm
        .baseHeight = 30.0    // 基础高100mm
    });

    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create ventilation pavilion" << std::endl;
    } else {
      test_export_shape(shp, "./ventilation_pavilion.stl");
    }

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_straight_ventilation_duct() {
  std::cout << "\n=== Testing Straight Ventilation Duct ===" << std::endl;

  try {
    // 测试标准直通风道
    auto shp =
        create_straight_ventilation_duct(straight_ventilation_duct_params{
            .diameter = 200.0,     // 直径200mm
            .wallThickness = 10.0, // 壁厚10mm
            .height = 500.0        // 高度500mm
        });

    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create straight ventilation duct"
                << std::endl;
    } else {
      test_export_shape(shp, "./straight_ventilation_duct.stl");
    }

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_oblique_ventilation_duct() {
  std::cout << "\n=== Testing Oblique Ventilation Duct ===" << std::endl;

  try {
    // 测试标准斜通风道
    auto shp = create_oblique_ventilation_duct(oblique_ventilation_duct_params{
        .hoodRoomLength = 200.0,       // 风帽室长200mm
        .hoodRoomWidth = 150.0,        // 风帽室宽150mm
        .hoodRoomHeight = 100.0,       // 风帽室高100mm
        .hoodWallThickness = 10.0,     // 风帽壁厚10mm
        .ductCenterHeight = 80.0,      // 风通道圆心高80mm
        .ductLeftDistance = 50.0,      // 风通道圆心距左侧50mm
        .ductDiameter = 120.0,         // 风通道直径120mm
        .ductWallThickness = 8.0,      // 风通道壁厚8mm
        .ductLength = 300.0,           // 风通道长300mm
        .ductHeightDifference = 40.0,  // 风通道高度差40mm
        .baseLength = 180.0,           // 风基座长180mm
        .baseWidth = 160.0,            // 风基座宽160mm
        .baseHeight = 60.0,            // 风基座高60mm
        .baseRoomLength = 220.0,       // 风基室长220mm
        .baseRoomWallThickness = 12.0, // 风基室壁厚12mm
        .baseRoomWidth = 140.0,        // 风基室宽140mm
        .baseRoomHeight = 90.0         // 风基室高90mm
    });

    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create oblique ventilation duct"
                << std::endl;
    } else {
      test_export_shape(shp, "./oblique_ventilation_duct.stl");
    }

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_drainage_well() {
  std::cout << "\n=== Testing Drainage Well ===" << std::endl;

  try {
    // 测试标准排水井
    auto shp = create_drainage_well(drainage_well_params{
        .length = 500.0,          // 井净长500mm
        .width = 300.0,           // 井净宽300mm
        .height = 400.0,          // 井净高400mm
        .neckDiameter = 150.0,    // 井脖直径150mm
        .neckHeight = 100.0,      // 井脖高100mm
        .cushionExtension = 50.0, // 垫层滋出距离50mm
        .bottomThickness = 60.0,  // 底板厚60mm
        .wallThickness = 20.0     // 壁厚20mm
    });

    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create drainage well" << std::endl;
    } else {
      test_export_shape(shp, "./drainage_well.stl");
    }

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_pipe_support() {
  std::cout << "\n=== Testing Pipe Support ===" << std::endl;

  try {
    // 测试标准管枕
    auto shp = create_pipe_support(pipe_support_params{
        .style = 1,                       // 单侧管枕
        .count = 2,                       // 2个管枕
        .positions = {{50, 0}, {150, 0}}, // 管枕中心坐标
        .radii = {30, 30},                // 管枕半径30mm
        .length = 100,                    // 管枕长100mm
        .height = 20                      // 管枕高20mm
    });

    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create pipe support" << std::endl;
    } else {
      test_export_shape(shp, "./pipe_support.stl");
    }

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_cover_plate() {
  std::cout << "\n=== Testing Cover Plate ===" << std::endl;

  try {
    // 测试长方形盖板
    auto rectShp = create_cover_plate(cover_plate_params{
        .style = 0,       // 长方形
        .length = 200.0,  // 长度200mm
        .width = 100.0,   // 宽度100mm
        .smallRadius = 0, // 不适用
        .largeRadius = 0, // 不适用
        .thickness = 10.0 // 厚度10mm
    });

    if (rectShp.IsNull()) {
      std::cerr << "Error: Failed to create rectangular cover plate"
                << std::endl;
    } else {
      test_export_shape(rectShp, "./rectangular_cover_plate.stl");
    }

    // 测试扇形盖板
    auto sectorShp = create_cover_plate(cover_plate_params{
        .style = 1,           // 扇形
        .length = 150.0,      // 扇形边长150mm
        .width = 0,           // 不适用
        .smallRadius = 50.0,  // 小半径50mm
        .largeRadius = 100.0, // 大半径100mm
        .thickness = 8.0      // 厚度8mm
    });

    if (sectorShp.IsNull()) {
      std::cerr << "Error: Failed to create sector cover plate" << std::endl;
    } else {
      test_export_shape(sectorShp, "./sector_cover_plate.stl");
    }

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_cable_ray() {
  std::cout << "\n=== Testing Cable Ray ===" << std::endl;

  try {
    // 测试标准槽盒
    auto shp = create_cable_ray(cable_ray_params{
        .outerLength = 300.0, // 外长度300mm
        .outerHeight = 100.0, // 外高度100mm
        .innerLength = 280.0, // 内长度280mm
        .innerHeight = 80.0,  // 内高度80mm
        .coverThickness = 5.0 // 盖板厚度5mm
    });

    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create cable ray" << std::endl;
    } else {
      test_export_shape(shp, "./cable_ray.stl");
    }

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

int main() {
  // 变电
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
  // 输电
  test_make_bored_pile();
  test_make_pile_cap();
  test_make_rock_anchor();
  test_make_rock_pile_cap();
  test_make_embedded_rock_anchor();
  test_make_inclined_rock_anchor();
  test_make_excavated_base();
  test_make_step_base();
  test_make_step_plate_base();
  test_make_sloped_base_base();
  test_make_composite_caisson_base();
  test_make_raft_base();
  test_make_direct_buried_base();
  test_make_steel_sleeve_base();
  test_make_precast_column_base();
  test_make_precast_pinned_base();
  test_make_precast_metal_support_base();
  test_make_precast_concrete_support_base();
  test_make_transmission_line();
  test_make_gt_insulator_string();
  test_make_pole_tower();
  test_make_single_hook_anchor();
  test_make_triple_hook_anchor();
  test_make_ribbed_anchor();
  test_make_nut_anchor();
  test_make_triple_arm_anchor();
  test_make_positioning_plate_anchor();
  test_make_stub_angle();
  test_make_stub_tube();
  // 电缆工程
  test_make_cable_wire();
  test_make_cable_joint();
  test_make_optical_fiber_box();
  test_make_cable_accessory();
  test_make_cable_terminal();
  test_make_cable_clamp();
  test_make_cable_bracket();
  test_make_cable_pole();
  test_make_ground_flat_iron();
  test_make_embedded_part();
  test_make_u_shaped_ring();
  test_make_lifting_eye();
  test_make_tunnel_well();
  test_make_corner_well();
  test_make_three_way_working_well();
  test_make_three_way_open_cut_tunnel();
  test_make_three_way_underground_tunnel();
  test_make_three_way_double_shaft_tunnel();
  test_make_four_way_working_well();
  test_make_four_way_open_cut_tunnel();
  test_make_four_way_underground_tunnel();
  test_make_pipe_row();
  test_make_cable_trench();
  test_make_cable_tunnel();
  test_make_cable_tray();
  test_make_cable_L_beam();
  test_make_manhole();
  test_make_manhole_cover();
  test_make_ladder();
  test_make_sump();
  test_make_footpath();
  test_make_shaft_chamber();
  test_make_tunnel_compartment_partition();
  test_make_tunnel_partition_board();
  test_make_ventilation_pavilion();
  test_make_straight_ventilation_duct();
  test_make_oblique_ventilation_duct();
  test_make_drainage_well();
  test_make_pipe_support();
  test_make_cover_plate();
  test_make_cable_ray();
  return 0;
}
