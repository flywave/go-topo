#include "primitives.hh"
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <BRep_Builder.hxx>
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

#include <array>
#include <vector>

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
    // 测试完整椭球
    auto fullShp = create_rotational_ellipsoid(rotational_ellipsoid_params{
        .polarRadius = 8,
        .equatorialRadius = 4,
        .height = 16 // 2*polarRadius 表示完整椭球
    });
    if (fullShp.IsNull()) {
      std::cerr << "Error: Failed to create full rotational ellipsoid"
                << std::endl;
      return;
    }
    test_export_shape(fullShp, "./full_rotational_ellipsoid.stl");

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
                                                        .filletRadius = 0.0,
                                                        .length = 100.0,
                                                        .width = 80.0});
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create rectangular ring" << std::endl;
      return;
    }
    test_export_shape(shp, "./rectangular_ring.stl");

    // 测试默认参数创建
    auto shp2 =
        create_rectangular_ring(rectangular_ring_params{.tubeRadius = 5.0,
                                                        .filletRadius = 12.0,
                                                        .length = 100.0,
                                                        .width = 80.0});
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create rectangular ring" << std::endl;
      return;
    }
    test_export_shape(shp2, "./rectangular_ring_round.stl");

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
        .frontSpacing = 50.0,    // 前端间距
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
    auto shp = create_rectangular_fixed_plate(rectangular_fixed_plate_params{
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
        rectangular_fixed_plate_params{.length = 120.0,
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
                    .startDir = gp_Dir(1, 0, 0),     // 初始方向沿X轴
                    .endDir = gp_Dir(0, 0, 1),       // 结束方向沿Z轴
                    .sag = 25.0,                     // 合理弧垂值
                    .diameter = 8.0,                 // 典型导线直径
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

    std::vector<gp_Pnt> splinePoints = {gp_Pnt(200, 0, 0), gp_Pnt(300, 0, 100),
                                        gp_Pnt(350, -50, 150)};

    auto shp2 = create_curve_cable(curve_cable_params{
        .controlPoints = {linePoints, arcPoints, splinePoints},
        .curveTypes = {curve_type::LINE, curve_type::ARC, curve_type::BEZIER},
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

struct NodeMemberResult {
  std::vector<pole_tower_node> nodeList;
  std::vector<pole_tower_member> memberList;
};

NodeMemberResult
organizeNodes(const std::vector<std::vector<std::array<double, 3>>> &nodes) {
  NodeMemberResult result;
  std::map<std::string, pole_tower_node> nodeMap;
  int nodeIdCounter = 1;
  int memberIdCounter = 1;

  for (size_t segmentIndex = 0; segmentIndex < nodes.size(); ++segmentIndex) {
    const auto &segment = nodes[segmentIndex];
    if (segment.size() != 2)
      continue;

    // Process start point
    std::string startKey = std::to_string(segment[0][0]) + "," +
                           std::to_string(segment[0][1]) + "," +
                           std::to_string(segment[0][2]);

    if (nodeMap.find(startKey) == nodeMap.end()) {
      pole_tower_node startNode;
      startNode.id = "node_" + std::to_string(nodeIdCounter++);
      startNode.position = gp_Pnt(segment[0][0], segment[0][1], segment[0][2]);
      nodeMap[startKey] = startNode;
      result.nodeList.push_back(startNode);
    }

    // Process end point
    std::string endKey = std::to_string(segment[1][0]) + "," +
                         std::to_string(segment[1][1]) + "," +
                         std::to_string(segment[1][2]);

    if (nodeMap.find(endKey) == nodeMap.end()) {
      pole_tower_node endNode;
      endNode.id = "node_" + std::to_string(nodeIdCounter++);
      endNode.position = gp_Pnt(segment[1][0], segment[1][1], segment[1][2]);
      nodeMap[endKey] = endNode;
      result.nodeList.push_back(endNode);
    }

    // Create member
    pole_tower_member member;
    member.id = "member_" + std::to_string(memberIdCounter++);
    member.startNodeId = nodeMap[startKey].id;
    member.endNodeId = nodeMap[endKey].id;
    member.type = member_type::ANGLE;
    member.specification = "L0.2x0.05";
    member.material = "Q345";
    member.xDirection = gp_Dir(1, 0, 0);
    member.yDirection = gp_Dir(0, 1, 0);
    member.end1Diameter = 0.0;
    member.end2Diameter = 0.0;
    member.thickness = 0.0;
    member.sides = 0;

    result.memberList.push_back(member);
  }

  return result;
}

void test_make_pole_tower() {
  std::cout << "\n=== Testing Pole Tower ===" << std::endl;
  try {

    std::vector<std::vector<std::array<double, 3>>> nodes = {
        {{-2.0265226742107814, -9.382245879547408, -0.015621793753579638},
         {-0.6267873559426036, -2.82250799450396, 38.558215350489895}},
        {{-0.6267873559426036, -2.82250799450396, 38.558215350489895},
         {-0.47044549314588835, -2.186319757328146, 49.20256873592615}},
        {{-0.47044549314588835, -2.186319757328146, 49.20256873592615},
         {-0.33634366111258274, -1.553915879033302, 58.413209580997425}},
        {{-0.33634366111258274, -1.553915879033302, 58.413209580997425},
         {4.360279466762972, -8.446010253137615, 63.267466193294204}},
        {{4.360279466762972, -8.446010253137615, 63.267466193294204},
         {4.964124149792788, -8.095003451991559, 63.43793484312452}},
        {{4.964124149792788, -8.095003451991559, 63.43793484312452},
         {4.6297462382405055, -7.531456638705673, 62.93328131038123}},
        {{4.6297462382405055, -7.531456638705673, 62.93328131038123},
         {1.9068842752500768, -0.6304330536115104, 58.56008365504745}},
        {{1.9068842752500768, -0.6304330536115104, 58.56008365504745},
         {0.8341216758958083, 1.4387987184271598, 58.42892811152461}},
        {{0.8341216758958083, 1.4387987184271598, 58.42892811152461},
         {-0.2485711383284137, 3.4561698372687966, 59.58348318873629}},
        {{-0.2485711383284137, 3.4561698372687966, 59.58348318873629},
         {-3.5299701716037006, 8.65660610719942, 62.99574353330713}},
        {{-3.5299701716037006, 8.65660610719942, 62.99574353330713},
         {-4.50875905216704, 8.078909138307793, 63.138189173675435}},
        {{-4.50875905216704, 8.078909138307793, 63.138189173675435},
         {-1.2638895047908179, 0.22802640493759974, 58.555938089970475}},
        {{-1.2638895047908179, 0.22802640493759974, 58.555938089970475},
         {-1.7888512566921104, 0.29547000758132924, 49.17524187248124}},
        {{-1.7888512566921104, 0.29547000758132924, 49.17524187248124},
         {-2.179595492350419, 0.42320774919833903, 38.195928279048}},
        {{-2.179595492350419, 0.42320774919833903, 38.195928279048},
         {-7.442983819026345, 1.0596820675211518, 0.7843780059003285}},
        {{-2.1719056171733753, 0.42069386108741824, 38.41200197472486},
         {-0.6313348913297498, -2.84381962376223, 38.43289459367103}},
        {{-2.091975346560319, 0.3945639496947479, 40.65791996041241},
         {-0.5953142207795881, -2.694437124555392, 40.70102705063152}},
        {{-2.0896852183444445, 0.39381528655499276, 40.722269050064085},
         {-0.5568543126728489, -2.5379355919352737, 43.3195250379034}},
        {{-0.5568543126728489, -2.5379355919352737, 43.3195250379034},
         {-1.9035991135435573, 0.3329820954177658, 45.95100312606985}},
        {{-1.9035991135435573, 0.3329820954177658, 45.95100312606985},
         {-0.47035223770392887, -2.18587997882346, 49.208973886174384}},
        {{-0.47035223770392887, -2.18587997882346, 49.208973886174384},
         {-1.7888744686509537, 0.2954775957756788, 49.174589652046485}},
        {{-1.7888744686509537, 0.2954775957756788, 49.174589652046485},
         {-0.5162136740001143, -2.372560203588235, 46.08649552235322}},
        {{-0.5162136740001143, -2.372560203588235, 46.08649552235322},
         {-1.9980025919833009, 0.36384342627365585, 43.29841020334986}},
        {{-1.9980025919833009, 0.36384342627365585, 43.29841020334986},
         {-0.6019287409637715, -2.6807852299463613, 40.70083653808768}},
        {{-1.6221533463667939, 0.2740537661412583, 52.154015947332475},
         {-0.42690692810937925, -1.9809984953662492, 52.1929684894617}},
        {{-0.42690692810937925, -1.9809984953662492, 52.1929684894617},
         {-1.784741331522532, 0.2949419916658295, 49.248683336269394}},
        {{-1.609599641276198, 0.25036889194090756, 52.154425066924006},
         {-0.469262479759318, -2.180740845821881, 49.28382274456568}},
        {{-1.5954133835779223, 0.22360390690002785, 52.15488739066931},
         {-0.3958617581588176, -1.8345941876743028, 54.32527276937493}},
        {{-0.3958617581588176, -1.8345941876743028, 54.32527276937493},
         {-1.385413324942892, 0.24363897901256892, 56.3843931423497}},
        {{-1.385413324942892, 0.24363897901256892, 56.3843931423497},
         {-0.3175878874574891, -1.5814391779164971, 58.4325948575685}},
        {{-0.3175878874574891, -1.5814391779164971, 58.4325948575685},
         {-1.2647185080690746, 0.228132909778165, 58.54112438613688}},
        {{-1.259500491684781, 0.21816345403820137, 58.54052646559042},
         {-0.36360331614774544, -1.6824682731641663, 56.54090934257067}},
        {{-0.36360331614774544, -1.6824682731641663, 56.54090934257067},
         {-1.499463915154137, 0.25829144209131977, 54.34638954242608}},
        {{-1.499463915154137, 0.25829144209131977, 54.34638954242608},
         {-0.42626842294110306, -1.9779874019411503, 52.236823533748144}},
        {{-0.5958795445138929, -2.696737546870487, 40.6625376435241},
         {-2.1719056171733753, 0.42069386108741824, 38.41200197472486}},
        {{-2.092976068540551, 0.39489109454827603, 40.629801207944304},
         {-0.6313348913297498, -2.84381962376223, 38.43289459367103}},
        {{-1.4743707980638243, -1.0574023956672527, 38.42146166971508},
         {-2.351925213469145, 0.4440466907637758, 36.97102872289794}},
        {{-2.351925213469145, 0.4440466907637758, 36.97102872289794},
         {-0.7681212988562647, -3.4848572313013726, 34.663341494159255}},
        {{-0.7681212988562647, -3.4848572313013726, 34.663341494159255},
         {-0.7868010528127038, -3.572398274320098, 34.14856575219847}},
        {{-0.7868010528127038, -3.572398274320098, 34.14856575219847},
         {-3.11294570764736, 0.5360729617130203, 31.561783820228044}},
        {{-3.11294570764736, 0.5360729617130203, 31.561783820228044},
         {-0.9892219003740004, -4.521025979244552, 28.570261978246542}},
        {{-0.9892219003740004, -4.521025979244552, 28.570261978246542},
         {-4.13566842751119, 0.6597455288043564, 24.292390023886217}},
        {{-4.13566842751119, 0.6597455288043564, 24.292390023886217},
         {-1.2854365452095273, -5.909210161262895, 20.407193346269374}},
        {{-1.2854365452095273, -5.909210161262895, 20.407193346269374},
         {-5.504418821476232, 0.8252614322268137, 14.563471882755348}},
        {{-5.504418821476232, 0.8252614322268137, 14.563471882755348},
         {-1.6943267818849008, -7.825438709144645, 9.13901628912295}},
        {{-1.6943267818849008, -7.825438709144645, 9.13901628912295},
         {-4.521736402391138, -3.3905472938041807, 6.280214615515183}},
        {{-4.521736402391138, -3.3905472938041807, 6.280214615515183},
         {-6.295327953933891, 0.9209019815636308, 8.941782025583397}},
        {{-6.295327953933891, 0.9209019815636308, 8.941782025583397},
         {-1.4951684076124803, -6.892100301669984, 14.627412984436436}},
        {{-1.4951684076124803, -6.892100301669984, 14.627412984436436},
         {-4.7472044548908325, 0.733695416595006, 19.945663274464827}},
        {{-4.7472044548908325, 0.733695416595006, 19.945663274464827},
         {-1.1374110897983587, -5.215501732863138, 24.48647157531161}},
        {{-1.1374110897983587, -5.215501732863138, 24.48647157531161},
         {-3.5471610790948995, 0.5885803800136378, 28.475431609437933}},
        {{-3.5471610790948995, 0.5885803800136378, 28.475431609437933},
         {-0.8792309336367583, -4.005562875540395, 31.601387636710058}},
        {{-0.8792309336367583, -4.005562875540395, 31.601387636710058},
         {-2.709328050222981, 0.48726556666100607, 34.430651048840566}},
        {{-2.709328050222981, 0.48726556666100607, 34.430651048840566},
         {-0.6786295973857999, -3.0654621521951855, 37.12954940734816}},
        {{-0.6786295973857999, -3.0654621521951855, 37.12954940734816},
         {-1.3272005215510756, -1.3692604260616892, 38.42345753556908}},
        {{-6.661666642226774, 0.9652014237546539, 6.337889361117256},
         {-1.794101076005064, -8.293022264800921, 6.389441192786306}},
        {{-4.503776464509832, -3.4187180879304275, 6.298373958293317},
         {-7.4389514523859095, 1.059194454286215, 0.8130395976213549}},
        {{-4.519580175765459, -3.3939294110900518, 6.282394782209623},
         {-2.0265226742107814, -9.382245879547408, -0.015621793753579638}},
        {{-2.024427977723924, -9.372429266561243, 0.04210374913736544},
         {3.3331521537271485, -5.7125041478754035, 6.542564997349087}},
        {{3.3331521537271485, -5.7125041478754035, 6.542564997349087},
         {-1.7961744572109186, -8.30273898557568, 6.332303055362208}},
        {{2.735431672351001, -1.2228870632779973, 38.46798532334256},
         {8.54438024692842, -3.553320898489263, -0.07993568082441982}},
        {{3.3326922356036333, -5.712736399793906, 6.542546144332865},
         {8.54438024692842, -3.553320898489263, -0.07993568082441982}},
        {{2.735431672351001, -1.2228870632779973, 38.46798532334256},
         {1.2109572628240552, 2.2348386940144818, 38.50973639332398}},
        {{1.2109572628240552, 2.2348386940144818, 38.50973639332398},
         {-3.061483070052674, 7.664664858303284, 38.29345187550644}},
        {{-3.061483070052674, 7.664664858303284, 38.29345187550644},
         {-4.27150171443789, 6.966805146309159, 38.46358216947882}},
        {{-4.27150171443789, 6.966805146309159, 38.46358216947882},
         {-2.168950213836389, 0.41972771363498557, 38.49504427470194}},
        {{-4.267665846690354, 6.969017424255425, 38.463042841171315},
         {-2.089339435397722, 0.38912361836480763, 40.65799588037741}},
        {{-0.5958795445138929, -2.696737546870487, 40.6625376435241},
         {3.6551080400377938, -8.277833097179268, 38.601943591143154}},
        {{3.6551080400377938, -8.277833097179268, 38.601943591143154},
         {-0.6313348913297498, -2.84381962376223, 38.43289459367103}},
        {{3.6059169025446787, -8.213250354200872, 38.6257881598068},
         {4.958665535821215, -7.553428521768804, 38.82278146840369}},
        {{4.958665535821215, -7.553428521768804, 38.82278146840369},
         {2.735431672351001, -1.2228870632779973, 38.46798532334256}},
        {{2.735431672351001, -1.2228870632779973, 38.46798532334256},
         {1.7930131477314493, -0.4107891593135157, 58.54616181471646}},
        {{0.8341216758958083, 1.4387987184271598, 58.42892811152461},
         {1.1118262087931825, 1.9619470380044728, 40.6125072452199}},
        {{1.1118262087931825, 1.9619470380044728, 40.6125072452199},
         {2.951763109558768, 7.02699383602876, -0.1836274885877387}},
        {{2.6338461035872673, -1.1353490689464754, 40.63226045729988},
         {1.113143727877937, 1.9655739535898904, 40.58329445750221}},
        {{1.113143727877937, 1.9655739535898904, 40.58329445750221},
         {-3.061483070052674, 7.664664858303284, 38.29345187550644}},
        {{2.6338752298236723, -1.1353741675145923, 40.63163992438399},
         {4.958665535821215, -7.553428521768804, 38.82278146840369}},
        {{1.1140540062710966, 1.968079801838635, 40.563111243633756},
         {2.7290858247793026, -1.2131579138448758, 38.467794262630896}},
        {{2.6338752298236723, -1.1353741675145923, 40.63163992438399},
         {1.205963851229949, 2.2210926446823445, 38.525233522531174}},
        {{1.2072013417884766, 2.2244992547614437, 38.49779517313099},
         {-2.170839751088537, 0.4184352603308103, 38.412016429584725}},
        {{-0.5953142207795881, -2.694437124555392, 40.70102705063152},
         {2.6373829791388648, -1.1450580197346936, 40.628910636502034}},
        {{-0.5952236628838654, -2.6940686252487347, 40.70719257934321},
         {3.2209078459350553, -2.755996564383313, 40.1748852188736}},
        {{3.2209078459350553, -2.755996564383313, 40.1748852188736},
         {1.6536788001014584, -5.650168912541433, 39.57210243212906}},
        {{1.6536788001014584, -5.650168912541433, 39.57210243212906},
         {4.3336348700398295, -5.827904815087937, 39.30910146127743}},
        {{3.7882257481059884, -4.322192501660406, 39.73347001599552},
         {0.5365153904328555, -4.183451917806485, 40.11362842619839}},
        {{0.5365153904328555, -4.183451917806485, 40.11362842619839},
         {2.6011693419817536, -1.1624146260763584, 40.62971850605889}},
        {{4.954571084275756, -7.54176978640848, 38.822128052832646},
         {2.397441520817045, -6.683462911937893, 38.55234366233675}},
        {{2.397441520817045, -6.683462911937893, 38.55234366233675},
         {4.020584171302676, -4.882291190200448, 38.67307717622214}},
        {{4.020584171302676, -4.882291190200448, 38.67307717622214},
         {1.488996443613987, -5.531808062352421, 38.51651635003642}},
        {{1.488996443613987, -5.531808062352421, 38.51651635003642},
         {3.097558832987968, -2.254025101126887, 38.525775609253095}},
        {{3.097558832987968, -2.254025101126887, 38.525775609253095},
         {-0.6338365675951256, -2.8555435121002084, 38.36395352203499}},
        {{-2.0896852183444445, 0.39381528655499276, 40.722269050064085},
         {0.0568513266454711, 3.4075966080618834, 40.00390294864215}},
        {{0.0568513266454711, 3.4075966080618834, 40.00390294864215},
         {-3.15485296465038, 3.6076338631457383, 39.58434954931149}},
        {{-3.15485296465038, 3.6076338631457383, 39.58434954931149},
         {-1.8852990532987155, 6.058969317931973, 38.9386056524048}},
        {{-1.8852990532987155, 6.058969317931973, 38.9386056524048},
         {-4.243368316600662, 6.895623847008783, 38.48752582831185}},
        {{-3.204343218813002, 3.643809585062056, 38.47955088789998},
         {0.24517613524361848, 3.462245802584136, 38.46084548105339}},
        {{0.24517613524361848, 3.462245802584136, 38.46084548105339},
         {-0.2953482565848675, 1.421163636615633, 38.45964086620554}},
        {{-0.2953482565848675, 1.421163636615633, 38.45964086620554},
         {-2.6903359057732756, 2.0432563151568246, 38.48724237710426}},
        {{-2.6903359057732756, 2.0432563151568246, 38.48724237710426},
         {-0.8094804684484782, 4.802604374007757, 38.40745540952042}},
        {{-0.8094804684484782, 4.802604374007757, 38.40745540952042},
         {-3.777561658990431, 5.4287387592605, 38.47097337677812}},
        {{-3.777561658990431, 5.4287387592605, 38.47097337677812},
         {-3.061483070052674, 7.664664858303284, 38.29345187550644}},
        {{-3.061483070052674, 7.664664858303284, 38.29345187550644},
         {-3.061483070052674, 7.664664858303284, 38.29345187550644}},
        {{-3.187200544484724, 3.642907288691645, 38.479457929819496},
         {-1.9547040085425744, 6.25806407794127, 38.34948055162562}},
        {{-0.6784626565659135, -3.064679798555553, 37.13414995426226},
         {2.9278642472319962, -1.300087158569273, 37.19101142696396}},
        {{2.9278642472319962, -1.300087158569273, 37.19101142696396},
         {-0.7845934387044695, -3.562052482717684, 34.209403073352675}},
        {{-0.7845934387044695, -3.562052482717684, 34.209403073352675},
         {3.381715919926424, -1.4821633605937101, 34.17927217638769}},
        {{3.381715919926424, -1.4821633605937101, 34.17927217638769},
         {-0.8792309336367583, -4.005562875540395, 31.601387636710058}},
        {{-0.8792309336367583, -4.005562875540395, 31.601387636710058},
         {3.864602908514418, -1.6758879498788894, 30.97485587780061}},
        {{3.864602908514418, -1.6758879498788894, 30.97485587780061},
         {-0.9892219003740004, -4.521025979244552, 28.570261978246542}},
        {{-0.9892219003740004, -4.521025979244552, 28.570261978246542},
         {4.261155163254644, -1.8349767729269, 28.343352982999626}},
        {{4.261155163254644, -1.8349767729269, 28.343352982999626},
         {-1.1413516035859628, -5.233968608165723, 24.37787908991534}},
        {{-1.1413516035859628, -5.233968608165723, 24.37787908991534},
         {4.892059882447226, -2.0880831114535434, 24.15669769343012}},
        {{4.892059882447226, -2.0880831114535434, 24.15669769343012},
         {-1.296998563991827, -5.8907545049092755, 20.391178769080994}},
        {{-1.296998563991827, -5.8907545049092755, 20.391178769080994},
         {5.514668938521464, -2.3378613960702053, 20.025092050532066}},
        {{5.514668938521464, -2.3378613960702053, 20.025092050532066},
         {-1.4941406092878637, -6.887283614171869, 14.655737000179597}},
        {{-1.4941406092878637, -6.887283614171869, 14.655737000179597},
         {6.35291187211558, -2.6741476739559737, 14.462549712336578}},
        {{6.35291187211558, -2.6741476739559737, 14.462549712336578},
         {-1.694326781884901, -7.825438709144645, 9.13901628912295}},
        {{-1.694326781884901, -7.825438709144645, 9.13901628912295},
         {7.156427943396341, -2.996502230139135, 9.130453267746756}},
        {{7.156427943396341, -2.996502230139135, 9.130453267746756},
         {3.333152153727149, -5.7125041478754035, 6.542564997349087}},
        {{7.523951582761596, -3.1439453540402758, 6.691582956617101},
         {2.6657135258680853, 6.2395458929249425, 6.158827707532836}},
        {{8.532840179109838, -3.5486912543876175, -0.0033563107469802844},
         {5.264990913770966, 1.2191462475816843, 6.443864928026054}},
        {{5.264990913770966, 1.2191462475816843, 6.443864928026054},
         {2.9461072989465364, 7.011424310019583, -0.05822361649327945}},
        {{2.6657135258680853, 6.239545892924942, 6.158827707532836},
         {-6.661666642226774, 0.9652014237546539, 6.337889361117256}},
        {{2.9461072989465364, 7.011424310019583, -0.05822361649327945},
         {-2.0522765418386975, 3.571668700106253, 6.249400954027945}},
        {{-2.0522765418386975, 3.571668700106253, 6.249400954027945},
         {-7.4389514523859095, 1.0591944542862155, 0.8130395976213549}},
        {{-5.497509428714041, 0.809573862392914, 14.553634930306952},
         {2.5406232516401412, 5.895192729140578, 8.932400909509898}},
        {{2.5406232516401412, 5.895192729140578, 8.932400909509898},
         {5.248857788287108, 1.250306730042845, 6.442095766617122}},
        {{-4.742241255362548, 0.7255157094762009, 19.951906550834806},
         {2.2978328288286543, 5.226830214567064, 14.315689215198084}},
        {{-4.115908067619831, 0.6573560107199841, 24.432844357028298},
         {2.0457760478940745, 4.532958924382175, 19.904436520227023}},
        {{2.0457760478940745, 4.532958924382175, 19.904436520227023},
         {6.335911891457021, -2.667327622165874, 14.575360818010065}},
        {{2.2947828359654188, 5.2184340806673095, 14.383315403755926},
         {7.1564279433963405, -2.996502230139135, 9.130453267746756}},
        {{6.35291187211558, -2.6741476739559733, 14.462549712336578},
         {2.5406793946699193, 5.895096438376453, 8.932349284263303}},
        {{2.2955058016686816, 5.220424287569985, 14.36728539412573},
         {5.438022307702625, -2.387612767228357, 19.966374094012863}},
        {{5.438022307702625, -2.387612767228357, 19.966374094012863},
         {1.8384689356008348, 3.962276187984189, 24.500968543076585}},
        {{1.8384689356008348, 3.962276187984189, 24.500968543076585},
         {4.248990957178231, -1.84119987951164, 28.343878691485955}},
        {{4.248990957178231, -1.84119987951164, 28.343878691485955},
         {1.4892301700911597, 3.0008787127475633, 32.24449046824317}},
        {{1.4892301700911597, 3.0008787127475633, 32.24449046824317},
         {3.3893434080285068, -1.4852233560683745, 34.12865650901785}},
        {{3.3893434080285068, -1.4852233560683745, 34.12865650901785},
         {1.06896004868039, 2.4153023467612122, 38.50254804273283}},
        {{1.06896004868039, 2.4153023467612122, 38.50254804273283},
         {2.727205544322527, -1.2042290296704237, 38.4682106138721}},
        {{2.630001071307996, -1.132035739917918, 40.71417866529501},
         {1.0725300593168832, 1.8879197459401331, 43.13359226385623}},
        {{1.0725300593168832, 1.8879197459401331, 43.13359226385623},
         {2.3676645600728605, -0.9059759529528728, 46.30324407000645}},
        {{2.3676645600728605, -0.9059759529528728, 46.30324407000645},
         {0.978975338276866, 1.7116784920075008, 49.13569192959934}},
        {{0.978975338276866, 1.7116784920075008, 49.13569192959934},
         {2.22739545794049, -0.7851037068574731, 49.29166982281859}},
        {{2.22739545794049, -0.7851037068574731, 49.29166982281859},
         {5.778580708526443, -9.00594012100905, 49.39964955913595}},
        {{5.778580708526443, -9.00594012100905, 49.39964955913595},
         {2.0951399919856453, -0.6711369459291118, 52.109365483525444}},
        {{2.0951399919856453, -0.6711369459291118, 52.109365483525444},
         {0.9320339006656565, 1.6232487715825816, 52.14726829756507}},
        {{0.9320339006656565, 1.6232487715825816, 52.14726829756507},
         {-3.8037142086057134, 9.354553322090993, 49.11960076503621}},
        {{-3.8037142086057134, 9.354553322090993, 49.11960076503621},
         {0.97877468841737, 1.7113005016458613, 49.14856482838226}},
        {{2.2183046976253804, -0.7669226088669749, 49.29053402116066},
         {1.0204684961462185, 1.7898445758910855, 46.47365557045356}},
        {{1.0204684961462185, 1.7898445758910855, 46.47365557045356},
         {2.4989802080168224, -1.019132856883724, 43.50557118198427}},
        {{2.4989802080168224, -1.019132856883724, 43.50557118198427},
         {1.144728806091545, 1.901167599154162, 40.58431148421179}},
        {{2.0989338995290114, -0.6744062199122887, 52.02853648530683},
         {0.9782326432157357, 1.7102793802640408, 49.18334029761973}},
        {{0.948235268321054, 1.5912893597713045, 52.146740334183214},
         {2.2183046976253804, -0.7669226088669749, 49.29053402116066}},
        {{0.835096036207966, 1.440634248278437, 58.366417020273396},
         {1.8951693452723948, -0.49881887406628334, 56.369729465041694}},
        {{1.8951693452723948, -0.49881887406628334, 56.369729465041694},
         {0.8979238694546878, 1.5589912482264812, 54.33563254742768}},
        {{0.8979238694546878, 1.5589912482264812, 54.33563254742768},
         {2.0753814836905904, -0.6321605880802234, 52.110009365516255}},
        {{0.9658589185504218, 1.5565243012109167, 52.14616602205268},
         {1.9897131376104091, -0.5802888511357068, 54.35547900292055}},
        {{1.9897131376104091, -0.5802888511357068, 54.35547900292055},
         {0.8704919610802305, 1.5073141775673589, 56.09555493567999}},
        {{0.8704919610802305, 1.5073141775673589, 56.09555493567999},
         {1.7939800494962, -0.41162235483756426, 58.525562024097624}},
        {{-3.5424564152751983, 0.5772488081724454, 28.46764378247076},
         {1.8442376469833395, 3.952099737489668, 24.493701317421284}},
        {{-3.090610349203798, 0.5333720623764061, 31.720540942716063},
         {1.6634610155259817, 3.4805078703667798, 28.38134437764264}},
        {{1.6634610155259817, 3.4805078703667798, 28.38134437764264},
         {4.875829403101468, -2.0815717681797214, 24.264402423063665}},
        {{4.875829403101468, -2.081571768179722, 24.264402423063665},
         {2.0626549141565818, 4.504630526843606, 19.883470108122506}},
        {{3.8498756229004103, -1.6699796578265362, 31.072585481560424},
         {1.6616192603510576, 3.4754378181559606, 28.42218082819246}},
        {{3.8297410456395857, -1.6619020686546069, 31.20619762904944},
         {1.4048126203089613, 2.768490938991046, 34.1162447296961}},
        {{1.4048126203089613, 2.768490938991046, 34.1162447296961},
         {2.942427111241262, -1.305929487966593, 37.09437291756479}},
        {{-2.692464737876784, 0.4458666875238988, 34.40458098283368},
         {1.5054104131385277, 2.9724900173056286, 32.22162151276099}},
        {{0.8197502460766481, 1.4655768655366028, 58.44425342545162},
         {0.8219031025143639, 1.384287791604308, 60.49325359269882}},
        {{0.8219031025143639, 1.384287791604308, 60.49325359269882},
         {-3.511632205484858, 8.509534334801922, 63.622339210198426}},
        {{-3.511632205484858, 8.509534334801922, 63.622339210198426},
         {-3.5299701716037006, 8.65660610719942, 62.99574353330713}},
        {{1.7930131477314493, -0.4107891593135157, 58.54616181471646},
         {1.6316573003029222, -0.30004388336357835, 60.606157103147886}},
        {{1.632120953390905, -0.3003621078964478, 60.61207653884931},
         {0.8219031025143639, 1.384287791604308, 60.49325359269882}},
        {{1.6316573003029222, -0.30004388336357835, 60.606157103147886},
         {0.819781841494329, 1.4643838634400483, 58.47432464384688}},
        {{0.8279958884793706, 1.3716193330501998, 60.49414713358766},
         {1.792975209680951, -0.4107631208405481, 58.5466461616213}},
        {{-1.259500491684781, 0.21816345403820137, 58.54052646559042},
         {-0.3122329025204147, -1.3045911630016835, 60.47894957685571}},
        {{-0.3122329025204147, -1.3045911630016835, 60.47894957685571},
         {3.9155085331650277, -8.16254422003267, 63.8864755028298}},
        {{3.9155085331650277, -8.16254422003267, 63.8864755028298},
         {4.35019974882181, -8.431218696433284, 63.25704816822944}},
        {{-0.31246971265018547, -1.5889498814229663, 58.43788481446408},
         {-0.2550883726885808, -1.3972871116576082, 60.52500761278146}},
        {{-0.2550883726885808, -1.3972871116576082, 60.52500761278146},
         {-1.1586221961857692, 0.3531215730395476, 60.52654546819159}},
        {{-1.1586221961857692, 0.3531215730395476, 60.52654546819159},
         {-0.3099786940405118, -1.5926053451206224, 58.44045943951449}},
        {{-1.1586221961857692, 0.3531215730395476, 60.52654546819159},
         {-1.2655326373550946, 0.22823750370689996, 58.52657647005299}},
        {{-1.1586221961857692, 0.3531215730395476, 60.52654546819159},
         {-4.428217800970454, 8.003580007453998, 63.65285111403193}},
        {{-4.42717128251611, 8.001131280790649, 63.65185045922695},
         {-4.505464259008917, 8.070937466615767, 63.13353642283323}},
        {{-3.5118741963180393, 8.511475118229553, 63.61407055003535},
         {-4.425436508229243, 7.9970721186865195, 63.65019171138689}},
        {{-1.1586221961857692, 0.3531215730395476, 60.52654546819159},
         {0.7792719705700906, 1.4543823688788562, 60.52403595682963}},
        {{-1.1375971904625035, 0.3123900014517065, 60.52650968268146},
         {1.556383814126959, -0.34572109117601557, 60.60904351708991}},
        {{0.7052616831525631, 1.5760708996286543, 60.577476048912814},
         {-0.24242707182004286, -1.4178254081258976, 60.53521252044254}},
        {{1.632120953390905, -0.3003621078964478, 60.61207653884931},
         {4.8060430110648165, -7.957107156046931, 63.921261198320416}},
        {{4.8060430110648165, -7.957107156046931, 63.921261198320416},
         {4.924320530086191, -8.065162037529277, 63.376130069530866}},
        {{1.632120953390905, -0.3003621078964478, 60.61207653884931},
         {2.376248197974022, -1.8200238388722054, 59.3139306124967}},
        {{2.376248197974022, -1.8200238388722054, 59.3139306124967},
         {2.1503008740578755, -1.7903893154106054, 61.313662832034105}},
        {{2.1503008740578755, -1.7903893154106054, 61.313662832034105},
         {3.0031315716822515, -3.4088436196269507, 60.320770084100936}},
        {{3.0031315716822515, -3.4088436196269507, 60.320770084100936},
         {2.8104815273911017, -3.3233498224654032, 61.961875611843254}},
        {{2.8104815273911017, -3.3233498224654032, 61.961875611843254},
         {3.6066645573956313, -4.938482442821667, 61.290106419880374}},
        {{3.6066645573956313, -4.938482442821667, 61.290106419880374},
         {3.5632950468110227, -5.0714067953878885, 62.7010419924957}},
        {{3.5632950468110227, -5.0714067953878885, 62.7010419924957},
         {4.160222271088484, -6.341460224960014, 62.17917730504372}},
        {{4.160222271088484, -6.341460224960014, 62.17917730504372},
         {4.123928730283094, -6.373216067362341, 63.251512407802835}},
        {{4.123928730283094, -6.373216067362341, 63.251512407802835},
         {4.53060868265979, -7.280195054927214, 62.7740561526193}},
        {{4.53060868265979, -7.280195054927214, 62.7740561526193},
         {4.452488765572223, -7.136142935563884, 63.57411624772702}},
        {{0.8219031025143639, 1.384287791604308, 60.49325359269882},
         {0.11202974976281155, 2.7842656669385155, 59.198947907146675}},
        {{0.11202974976281155, 2.7842656669385155, 59.198947907146675},
         {0.012968065077778701, 2.714347701010611, 61.0773556736169}},
        {{0.012968065077778701, 2.714347701010611, 61.0773556736169},
         {-0.775714757677984, 4.2915991068360935, 60.13164915391142}},
        {{-0.775714757677984, 4.2915991068360935, 60.13164915391142},
         {-0.8220341710521546, 4.087267585974925, 61.680279914901206}},
        {{-0.8220341710521546, 4.087267585974925, 61.680279914901206},
         {-1.600612189696614, 5.59891543165395, 60.98944327375852}},
        {{-1.600612189696614, 5.59891543165395, 60.98944327375852},
         {-1.7454780843450068, 5.605604251856304, 62.34706462121673}},
        {{-1.7454780843450068, 5.605604251856304, 62.34706462121673},
         {-2.7203260729604866, 7.373463614127859, 62.15381104566984}},
        {{-2.7203260729604866, 7.373463614127859, 62.15381104566984},
         {-2.682275915372063, 7.145897576541903, 63.023491697779534}},
        {{-2.682275915372063, 7.145897576541903, 63.023491697779534},
         {-3.5054204429930302, 8.61769913557261, 62.97021476811926}},
        {{-1.823333670720349, 1.9084660625425636, 61.16212597626765},
         {-1.9110864642019627, 1.793903664268151, 59.46987898199501}},
        {{-1.9110864642019627, 1.793903664268151, 59.46987898199501},
         {-1.1586221961857692, 0.3531215730395476, 60.52654546819159}},
        {{-1.8791883347968188, 2.039159223880281, 61.21553281086006},
         {-2.522311123597274, 3.272746821009809, 60.33302149574138}},
        {{-2.522311123597274, 3.272746821009809, 60.33302149574138},
         {-2.510616866694004, 3.516625651383897, 61.819289000563174}},
        {{-2.510616866694004, 3.516625651383897, 61.819289000563174},
         {-3.0977854771628315, 4.665092984681756, 61.14567912088456}},
        {{-3.0977854771628315, 4.665092984681756, 61.14567912088456},
         {-3.103108755789056, 4.902985042011931, 62.38581494501998}},
        {{-3.103108755789056, 4.902985042011931, 62.38581494501998},
         {-3.87881784253359, 6.554781744727809, 62.24861603417979}},
        {{-3.87881784253359, 6.554781744727809, 62.24861603417979},
         {-3.762603350593132, 6.446122663645063, 63.01640720301054}},
        {{-3.762603350593132, 6.446122663645063, 63.01640720301054},
         {-4.462622071918179, 7.967281839793277, 63.07303671541555}},
        {{-2.0895323134331036, 0.3937653005890477, 40.726565443506104},
         {1.0704084008180281, 1.8839229005634568, 43.26970945415122}},
        {{-1.9872860278609326, 0.3603400868153554, 43.59952921524108},
         {1.026307833285928, 1.8008448983568814, 46.099026870749356}},
        {{1.026307833285928, 1.8008448983568814, 46.099026870749356},
         {-1.7936614103704631, 0.29704248930116406, 49.04008393322651}},
        {{-1.8914509272209934, 0.32901074601840086, 46.29234852557951},
         {0.9842028966109897, 1.7215263267887924, 48.80031253045095}},
        {{2.6011693419817536, -1.1624146260763584, 40.62971850605889},
         {-0.556229459409449, -2.535392931325858, 43.36206744356937}},
        {{-0.556229459409449, -2.535392931325858, 43.36206744356937},
         {2.3542461209243637, -0.8944130581006429, 46.58912320164921}},
        {{2.3542461209243637, -0.8944130581006429, 46.58912320164921},
         {-0.4700725832499648, -2.1845611708803636, 49.22818165311636}},
        {{-0.4692624797593179, -2.180740845821881, 49.28382274456568},
         {4.384900961010555, -9.737269162796126, 49.30922032540953}},
        {{4.384900961010555, -9.737269162796126, 49.30922032540953},
         {-0.4262684229411031, -1.9779874019411503, 52.236823533748144}},
        {{4.384900961010555, -9.737269162796126, 49.30922032540953},
         {5.778580708526443, -9.00594012100905, 49.39964955913595}},
        {{3.3132743243513625, -8.00898808335376, 49.96130661239196},
         {5.003990182052164, -7.253214863221357, 49.96947555770387}},
        {{5.003990182052164, -7.253214863221357, 49.96947555770387},
         {2.4121625786566487, -6.55570731627374, 50.50963435295482}},
        {{2.4121625786566487, -6.55570731627374, 50.50963435295482},
         {3.5230247647565895, -3.902121086462855, 51.05894485652963}},
        {{3.5230247647565895, -3.902121086462855, 51.05894485652963},
         {0.5491073361402168, -3.551038511441602, 51.64330603857386}},
        {{0.5491073361402168, -3.551038511441602, 51.64330603857386},
         {2.08789471047189, -0.6648935649075765, 52.26372582042734}},
        {{-0.4256065817105338, -1.9748662591895476, 52.28228139050374},
         {2.0844310777232606, -0.6619088942736877, 52.33751833172837}},
        {{-0.402798567299477, -1.962935780621804, 52.282783313232564},
         {2.835481600386963, -2.346364555983344, 51.56473463423159}},
        {{2.835481600386963, -2.346364555983344, 51.56473463423159},
         {0.5491073361402168, -3.551038511441602, 51.64330603857386}},
        {{2.6334900508040735, -2.4527924329981903, 51.57167608732795},
         {1.5598576303548564, -5.181140404931132, 51.02826308996299}},
        {{1.5598576303548564, -5.181140404931132, 51.02826308996299},
         {4.291923368171585, -5.641966794384636, 50.49330610997445}},
        {{4.286219314419144, -5.6290597954710435, 50.49750228590777},
         {3.3322189712924555, -8.03954133179398, 49.949778768589454}},
        {{3.040600547721399, -2.6676374364457063, 49.31639668581511},
         {1.4680898912433555, -5.196638070971152, 49.293959210728374}},
        {{1.4680898912433555, -5.196638070971152, 49.293959210728374},
         {4.527299841478937, -6.109280389034216, 49.36160226828835}},
        {{4.527299841478937, -6.109280389034216, 49.36160226828835},
         {3.435323880935374, -8.259052332585771, 49.30425202119955}},
        {{3.435323880935374, -8.259052332585771, 49.30425202119955},
         {5.755386212010805, -8.952245889897844, 49.398944291615095}},
        {{2.460653517233177, -6.741772518483937, 49.299152425839765},
         {3.621354378832077, -4.012056807883716, 49.33405547890067}},
        {{3.621354378832077, -4.012056807883716, 49.33405547890067},
         {0.40658430251686895, -3.544180930268462, 49.288405282778726}},
        {{0.40658430251686895, -3.544180930268462, 49.288405282778726},
         {2.2304152758246847, -0.7877059347530875, 49.22733276357504}},
        {{2.232840491150928, -0.7897957836171043, 49.1756636801712},
         {-0.29321874970404105, -2.1037743817513954, 49.06292848837829}},
        {{-1.7605658721106074, 0.3146913165981722, 49.005567292041654},
         {0.9801989723104703, 1.7139836113434324, 49.057188425527684}},
        {{-1.6109212711736256, 0.3910920838758108, 49.00838578409002},
         {-0.08586008982313098, 3.4127728828145507, 49.14211710841441}},
        {{-0.08586008982313098, 3.4127728828145507, 49.14211710841441},
         {-2.8397060879776257, 3.7075602869713156, 49.020680426259986}},
        {{-2.8397060879776257, 3.7075602869713156, 49.020680426259986},
         {-1.9396041952050098, 6.375379836416266, 49.13089032611512}},
        {{-1.9396041952050098, 6.375379836416266, 49.13089032611512},
         {-4.0931152653540686, 6.8302814847824065, 48.901101046529575}},
        {{-4.0931152653540686, 6.8302814847824065, 48.901101046529575},
         {-3.8037142086057134, 9.354553322090993, 49.11960076503621}},
        {{-2.100079678689563, 2.1405666866303976, 48.961297874576445},
         {-0.9622563412909768, 4.81340721048204, 49.13680941254928}},
        {{-0.9622563412909768, 4.81340721048204, 49.13680941254928},
         {-3.5542799163059087, 5.327640799877077, 49.08032411301837}},
        {{-3.5542799163059087, 5.327640799877077, 49.08032411301837},
         {-2.851732113978315, 7.833119611224815, 49.12536622948094}},
        {{-2.851732113978315, 7.833119611224815, 49.12536622948094},
         {-4.997166417813119, 8.688803564099302, 48.91712732605103}},
        {{-1.784741331522532, 0.29494199166582935, 49.248683336269394},
         {-4.997166417813119, 8.688803564099302, 48.91712732605103}},
        {{-4.997166417813119, 8.688803564099302, 48.91712732605103},
         {-3.8037142086057134, 9.354553322090993, 49.11960076503621}},
        {{-1.6204990928672516, 0.27093271257584506, 52.15406985870853},
         {-4.997166417813119, 8.688803564099302, 48.91712732605103}},
        {{0.8042010270583559, 1.831941221987582, 52.065541940486874},
         {-1.618605969489815, 0.27359802269775596, 52.21740506993305}},
        {{0.7807475943978459, 1.8702299203029031, 52.050547647092436},
         {-2.3134426596397883, 1.9984080280716485, 51.48979994753113}},
        {{-2.3134426596397883, 1.9984080280716485, 51.48979994753113},
         {-0.8933202569539832, 4.603214888755453, 50.9802793887648}},
        {{-0.8933202569539832, 4.603214888755453, 50.9802793887648},
         {-3.5938619851095357, 5.190432435679496, 50.26236372850233}},
        {{-3.5938619851095357, 5.190432435679496, 50.26236372850233},
         {-2.6990636777665733, 7.551165667439703, 49.825828053701485}},
        {{-2.6990636777665733, 7.551165667439703, 49.825828053701485},
         {-4.296637087491819, 6.942417301294019, 49.58866910570427}},
        {{-1.9135517984950026, 6.268785053740828, 50.32802300968537},
         {-2.965474747912607, 3.623892975783434, 50.86474861848983}},
        {{-2.965474747912607, 3.623892975783434, 50.86474861848983},
         {0.027958268230367733, 3.0991896134036923, 51.56927293630081}},
        {{0.027958268230367733, 3.0991896134036923, 51.56927293630081},
         {-1.6186059694898147, 0.2735980226977559, 52.21740506993305}},
        {{-0.2710873614933849, -1.366292401529428, 60.52503484378361},
         {0.6112753791360422, -2.944506454063305, 59.392633704845736}},
        {{0.6112753791360422, -2.944506454063305, 59.392633704845736},
         {0.6266867381037932, -2.8276423991474102, 61.23571132931954}},
        {{0.6266867381037932, -2.8276423991474102, 61.23571132931954},
         {1.46375954798562, -4.1954906578563, 60.27372993097368}},
        {{1.46375954798562, -4.1954906578563, 60.27372993097368},
         {1.4967237781369254, -4.238956990920224, 61.936954254311715}},
        {{1.4967237781369254, -4.238956990920224, 61.936954254311715},
         {2.3925374922999056, -5.55843272719286, 61.23368059228689}},
        {{2.3925374922999056, -5.55843272719286, 61.23368059228689},
         {2.330451031667011, -5.591372329950931, 62.60893178056607}},
        {{2.330451031667011, -5.591372329950931, 62.60893178056607},
         {3.26501697039925, -6.83875919555268, 62.1354432333044}},
        {{3.26501697039925, -6.83875919555268, 62.1354432333044},
         {3.2552932527199414, -7.091588138705319, 63.354347244972864}},
        {{3.2552932527199414, -7.091588138705319, 63.354347244972864},
         {4.332300622669709, -8.420155582724675, 63.28296587454557}},
        {{-3.2408382690485356, 5.225255452102347, 62.51750846524366},
         {-2.717855496760321, 7.209514695528584, 63.0211888569158}},
        {{-2.717855496760321, 7.209514695528584, 63.0211888569158},
         {-4.40339366926198, 7.9454945403925095, 63.62911489937599}},
        {{-3.2064964074807283, 5.144899647824763, 62.48467163504025},
         {-0.9692383511263454, 4.32930232220559, 61.786570610596186}},
        {{-0.9692383511263454, 4.32930232220559, 61.786570610596186},
         {-1.8791883347968188, 2.039159223880281, 61.21553281086006}},
        {{-1.8791883347968188, 2.039159223880281, 61.21553281086006},
         {0.6581654863095244, 1.4272866821333958, 60.575375727002616}},
        {{-1.2165443587411118, 0.48865243086568766, 60.5819291931853},
         {-0.06571097837637119, 2.843712651922389, 61.13416690181125}},
        {{-0.06571097837637119, 2.843712651922389, 61.13416690181125},
         {-2.4681406393523675, 3.4172364146072196, 61.77867429299572}},
        {{-2.4681406393523675, 3.4172364146072196, 61.77867429299572},
         {-1.8639851222231885, 5.800454830419134, 62.43263417158191}},
        {{-1.8639851222231885, 5.800454830419134, 62.43263417158191},
         {-3.8115378024434, 6.5524585203788925, 63.020365860205935}},
        {{-3.8115378024434, 6.5524585203788925, 63.020365860205935},
         {-3.4922857938107636, 8.47772475137712, 63.608369881644}},
        {{0.8364021215429003, 1.4430946919055778, 58.2826237678849},
         {-1.3824648495992744, 0.237446659727806, 56.37825777168985}},
        {{-1.3824648495992744, 0.237446659727806, 56.37825777168985},
         {0.9359962552046677, 1.4881416677914507, 54.26366835670748}},
        {{0.9359962552046677, 1.4881416677914507, 54.26366835670748},
         {-1.6168318856416026, 0.2733701001763872, 52.24910669692618}},
        {{0.7807475943978459, 1.8702299203029031, 52.050547647092436},
         {-1.5068773858212214, 0.2592438756125638, 54.21391605079871}},
        {{-1.5068773858212214, 0.2592438756125638, 54.21391605079871},
         {0.8613317552782978, 1.490057900825076, 56.68323739115331}},
        {{-0.3038273147623701, -1.6016322321757563, 58.446817278481475},
         {1.8862080861000539, -0.5905511379484722, 58.55755579210034}},
        {{1.8862080861000539, -0.5905511379484722, 58.55755579210034},
         {-0.3667843092362318, -1.677033149130424, 56.53476355996063}},
        {{-0.3667843092362318, -1.677033149130424, 56.53476355996063},
         {1.9897235375431936, -0.5802978129328223, 54.355257432906285}},
        {{1.9897235375431936, -0.5802978129328223, 54.355257432906285},
         {-0.39361106566157156, -1.9581299571333288, 52.282985497246045}},
        {{2.0822726132558977, -0.6600489091142969, 52.38350430228595},
         {-0.3967300959715432, -1.838689136953604, 54.265631915823995}},
        {{-0.3967300959715432, -1.838689136953604, 54.265631915823995},
         {1.8903228370353522, -0.4946425563496536, 56.472984064997185}},
        {{1.8903228370353522, -0.4946425563496536, 56.472984064997185},
         {-0.2837632350380666, -1.5923691802295077, 58.447831812933714}},
        {{1.8569579514598389, -0.5341310987241609, 58.553979681869464},
         {0.6125498715971541, -2.946376717459346, 59.39395097329334}},
        {{0.6125498715971541, -2.946376717459346, 59.39395097329334},
         {2.9863513882061143, -3.3769991278091194, 60.34030610986649}},
        {{2.9863513882061143, -3.3769991278091194, 60.34030610986649},
         {2.4192537768049585, -5.597637736647714, 61.26129355955797}},
        {{2.4192537768049585, -5.597637736647714, 61.26129355955797},
         {4.157229653829, -6.335092976727358, 62.18179360600516}},
        {{4.157229653829, -6.335092976727358, 62.18179360600516},
         {4.336949075471284, -8.4117738977416, 63.243352760491184}},
        {{-0.28376323503806655, -1.592369180229508, 58.447831812933714},
         {2.439089885596016, -1.9792944792135225, 59.41486085600559}},
        {{2.439089885596016, -1.9792944792135225, 59.41486085600559},
         {1.464726017953359, -4.1967650363362825, 60.322493586328015}},
        {{1.464726017953359, -4.1967650363362825, 60.322493586328015},
         {3.6066036529891328, -4.938669110337465, 61.292087816315316}},
        {{3.6066036529891328, -4.938669110337465, 61.292087816315316},
         {3.264926059204502, -6.841123001459727, 62.14683928815072}},
        {{3.264926059204502, -6.841123001459727, 62.14683928815072},
         {4.868630572314036, -8.150512585553235, 63.4109764849941}},
        {{0.16261761000200636, -2.2861202897159885, 58.928917565998894},
         {2.1517613179085533, -1.2510676174651598, 58.95338148775249}},
        {{-1.6525750886441362, 1.1684416957314525, 59.104821461652556},
         {0.46614260034059907, 2.1244505945736156, 58.82133129773615}},
        {{-1.2654092191225752, 0.2282216477512939, 58.52878186681336},
         {0.10928640724458327, 2.7893773106962416, 59.201873335293364}},
        {{0.10928640724458327, 2.7893773106962416, 59.201873335293364},
         {-2.519333673473663, 3.267035710149613, 60.337107237173726}},
        {{-2.519333673473663, 3.267035710149613, 60.337107237173726},
         {-1.600612189696614, 5.59891543165395, 60.98944327375852}},
        {{-1.600612189696614, 5.59891543165395, 60.98944327375852},
         {-3.8690768120566053, 6.534039172160476, 62.250338920755105}},
        {{-3.8690768120566053, 6.534039172160476, 62.250338920755105},
         {-3.5299701716037006, 8.65660610719942, 62.99574353330713}},
        {{0.8280926581588693, 1.4385796451237272, 58.275492083236394},
         {-1.9107353938657345, 1.7943619910983928, 59.47664911087284}},
        {{-1.9107353938657345, 1.7943619910983928, 59.47664911087284},
         {-0.7762534944082228, 4.289222546180106, 60.14966113229688}},
        {{-0.7762534944082228, 4.289222546180106, 60.14966113229688},
         {-3.0946329188206407, 4.65746544665803, 61.14122722731256}},
        {{3.040600547721399, -2.6676374364457063, 49.31639668581511},
         {2.8234483782787514, -2.344939761531448, 51.567402852789435}},
        {{3.6007906319571066, -4.009063971417099, 49.33376347074595},
         {3.525330455522787, -3.9073383493965457, 51.057248679648644}},
        {{3.5276719030242387, -3.9126365218312875, 51.05552619839563},
         {3.0206313510465836, -2.637962331870846, 49.52339800189638}},
        {{3.5279974863184522, -3.9133732440655233, 51.05528668368508},
         {4.391735931165451, -6.068838129965117, 49.35860477627651}},
        {{4.391735931165451, -6.068838129965117, 49.35860477627651},
         {4.291923368171585, -5.641966794384636, 50.49330610997445}},
        {{5.003990182052164, -7.253214863221357, 49.96947555770387},
         {4.382783597978218, -6.066167414896529, 49.35840682870215}},
        {{-0.10563224357284984, 3.444372238958981, 49.141997362832974},
         {0.027958268230367733, 3.0991896134036923, 51.56927293630081}},
        {{0.027958268230367733, 3.0991896134036923, 51.56927293630081},
         {-0.9568077004137785, 4.804699330411861, 49.13684241101157}},
        {{-0.9568077004137785, 4.804699330411861, 49.13684241101157},
         {-0.9069101678030813, 4.606169938117779, 50.97666662851066}},
        {{-0.9069101678030813, 4.606169938117779, 50.97666662851066},
         {-1.938701794206824, 6.3739376419599765, 49.130895791302855}},
        {{-1.938701794206824, 6.3739376419599765, 49.130895791302855},
         {-1.8618577828062528, 6.184392436247924, 50.361072126596895}},
        {{-1.8618577828062528, 6.184392436247924, 50.361072126596895},
         {-2.817793054787455, 7.778879065042833, 49.125571773724005}},
        {{-4.296637087491819, 6.942417301294019, 49.58866910570427},
         {-4.316904719882983, 6.91132319581855, 48.98733747832279}},
        {{-4.316904719882983, 6.91132319581855, 48.98733747832279},
         {-3.578985723401661, 5.1533466236170495, 50.27662441799739}},
        {{-3.578985723401661, 5.1533466236170495, 50.27662441799739},
         {-3.017178345555328, 3.7069466023821627, 49.118043816009376}},
        {{-3.017178345555328, 3.7069466023821627, 49.118043816009376},
         {-2.3134426596397883, 1.9984080280716485, 51.48979994753113}},
        {{-2.3134426596397883, 1.9984080280716485, 51.48979994753113},
         {-1.828400656280883, 0.4090210187321637, 49.244177235383965}},
        {{3.4054175265220303, -8.212496789753441, 49.304095547470716},
         {3.3132743243513625, -8.00898808335376, 49.96130661239196}},
        {{3.3132743243513625, -8.00898808335376, 49.96130661239196},
         {2.460653517233177, -6.741772518483937, 49.299152425839765}},
        {{2.460653517233177, -6.741772518483937, 49.299152425839765},
         {2.4658962614160855, -6.5701680192930665, 50.498435798967}},
        {{2.4658962614160855, -6.5701680192930665, 50.498435798967},
         {1.6261165658262262, -5.243781559961177, 49.2974533832823}},
        {{1.6261165658262262, -5.243781559961177, 49.2974533832823},
         {1.6379938525077589, -5.19431989495652, 51.01296348832748}},
        {{1.6379938525077589, -5.19431989495652, 51.01296348832748},
         {0.39367707413059316, -3.524088109335536, 49.28833775057046}},
        {{0.39367707413059316, -3.524088109335536, 49.28833775057046},
         {0.5491073361402168, -3.551038511441602, 51.64330603857386}},
        {{0.5491073361402168, -3.551038511441602, 51.64330603857386},
         {-0.4667940445888829, -2.16910008035706, 49.453364573036545}},
        {{-3.7751874241700816, 5.4814278210274034, 38.95928022995312},
         {-3.204343218813002, 3.643809585062056, 38.47955088789998}},
        {{-3.204343218813002, 3.643809585062056, 38.47955088789998},
         {-3.1416314446427274, 3.567696690666987, 39.59767198591845}},
        {{-3.1416314446427274, 3.567696690666987, 39.59767198591845},
         {-2.611713783338218, 2.1586005338664167, 38.483907181528025}},
        {{-2.611713783338218, 2.1586005338664167, 38.483907181528025},
         {-2.0895323134331036, 0.3937653005890477, 40.726565443506104}},
        {{-0.6303280127324766, -2.8391009747476836, 38.460642104595664},
         {0.4787264977830321, -4.107581234768672, 40.14164061068951}},
        {{0.4787264977830321, -4.107581234768672, 40.14164061068951},
         {1.4238023731335319, -5.4491601738700535, 38.51394522231296}},
        {{1.4238023731335319, -5.4491601738700535, 38.51394522231296},
         {2.391254638792601, -6.618527711398883, 39.214575067920784}},
        {{4.018584161477747, -4.8845105645350335, 38.67292841036111},
         {4.108851601895614, -5.207345090129241, 39.4839994356438}},
        {{4.108851601895614, -5.207345090129241, 39.4839994356438},
         {3.080842793689424, -2.2880875342372797, 38.52567938784324}},
        {{3.080842793689424, -2.2880875342372797, 38.52567938784324},
         {3.107647979725407, -2.4433197712920007, 40.26300975474593}},
        {{0.27456528882209497, 3.4248952528716567, 38.462333253477475},
         {1.144728806091545, 1.901167599154162, 40.58431148421179}},
        {{0.27635849884726016, 3.42175519511235, 38.46670617024658},
         {-0.0026884629389329062, 3.4113049743984147, 39.996125108950224}},
        {{-0.0026884629389329062, 3.4113049743984147, 39.996125108950224},
         {-0.7937633400751498, 4.782629542712331, 38.408251060545794}},
        {{-0.7937633400751498, 4.782629542712331, 38.408251060545794},
         {-1.674961615830989, 5.771822170458272, 39.05397874902274}},
        {{5.248857788287108, 1.250306730042845, 6.442095766617122},
         {-2.0522765418386975, 3.571668700106253, 6.249400954027945}},
        {{-2.0522765418386975, 3.571668700106253, 6.249400954027945},
         {-4.481638029818607, -3.453443001239455, 6.3207581907325485}},
        {{-4.484094959560476, -3.449589220541645, 6.318273982287105},
         {3.304613889556744, -5.731999499754101, 6.507938939356615}},
        {{3.304613889556744, -5.731999499754101, 6.507938939356615},
         {5.264990913770966, 1.2191462475816843, 6.443864928026054}},
        {{3.2993424631112, -5.735600570682765, 6.501543010132728},
         {7.523334060406356, -3.142752634468418, 6.691515239005833}},
        {{4.80416648339442, -7.952749799019594, 63.91941868868086},
         {3.905779464538461, -8.146762390196425, 63.87863395100244}},
        {{3.905779464538461, -8.146762390196425, 63.87863395100244},
         {4.452488765572223, -7.136142935563884, 63.57411624772702}},
        {{4.452488765572223, -7.136142935563884, 63.57411624772702},
         {3.2558022010279837, -7.0783548397670435, 63.290548690257026}},
        {{3.2558022010279837, -7.0783548397670435, 63.290548690257026},
         {4.123928730283094, -6.373216067362341, 63.251512407802835}},
        {{4.123928730283094, -6.373216067362341, 63.251512407802835},
         {2.334140905301988, -5.589414689419893, 62.52719893496053}},
        {{2.334140905301988, -5.589414689419893, 62.52719893496053},
         {3.5632950468110227, -5.0714067953878885, 62.7010419924957}},
        {{3.5632950468110227, -5.0714067953878885, 62.7010419924957},
         {1.5036331285228222, -4.250164866643441, 61.9425231356943}},
        {{1.5036331285228222, -4.250164866643441, 61.9425231356943},
         {2.818330812771007, -3.3268331604246644, 61.89501081732329}},
        {{2.818330812771007, -3.3268331604246644, 61.89501081732329},
         {0.6266867381037932, -2.8276423991474102, 61.23571132931954}},
        {{0.6266867381037932, -2.8276423991474102, 61.23571132931954},
         {2.1503008740578755, -1.7903893154106054, 61.313662832034105}},
        {{-0.24008411847216676, -1.4216259868318049, 60.53710092218084},
         {1.632120953390905, -0.3003621078964478, 60.61207653884931}}};

    // 组织节点和杆件
    auto result = organizeNodes(nodes);

    // 初始化杆塔参数
    pole_tower_params params;

    // 添加呼高信息
    params.heights.push_back(
        pole_tower_height{.value = 18.0, .bodyId = "body1", .legId = "leg1"});

    // 添加本体信息
    pole_tower_body body{.id = "body1", .height = 30.0};

    // 添加接腿信息
    pole_tower_leg leg{
        .id = "leg1", .commonHeight = 10.0, .specificHeight = 8.0};

    // 添加动态生成的节点
    for (const auto &node : result.nodeList) {
      body.nodes.push_back(node);
    }

    // 添加动态生成的杆件
    for (const auto &member : result.memberList) {
      params.members.push_back(member);
    }

    // 添加挂点
    params.attachments.push_back(
        pole_tower_attachment{.name = "ground_wire",
                              .type = attachment_type::GROUND_WIRE,
                              .position = gp_Pnt(50, 0, 30)});

    body.legs.push_back(leg);
    params.bodies.push_back(body);

    // 创建杆塔形状
    try {
      auto shp = create_pole_tower(params);
      if (shp.IsNull()) {
        std::cerr << "Error: Failed to create pole tower" << std::endl;
        return;
      }
      test_export_shape(shp, "./pole_tower.stl");
    } catch (const Standard_ConstructionError &e) {
      std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
    }

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
        .washerShape = washer_shape_type::ROUND, // 圆形垫片
        .washerSize = 0.65,                      // 50mm → 0.05m
        .washerThickness = 0.015,                // 5mm → 0.005m
        .anchorLength = 1.5,                     // 800mm → 0.8m

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
        .washerShape = washer_shape_type::ROUND, // 圆形垫片
        .washerSize = 0.65,                      // 50mm → 0.05m
        .washerThickness = 0.015,                // 5mm → 0.005m
        .anchorLength = 1.5,                     // 1000mm → 1.0m

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
        .boltDiameter = 0.2,                     // 地脚螺栓直径 20mm → 0.02m
        .exposedLength = 0.40,                   // 露头长度 100mm → 0.1m
        .nutCount = 0,                           // 蝶帽数量保持不变
        .nutHeight = 0.1,                        // 蝶帽高度 10mm → 0.01m
        .nutOD = 0.6,                            // 蝶帽外径 40mm → 0.04m
        .washerCount = 0,                        // 垫片数量保持不变
        .washerShape = washer_shape_type::ROUND, // 圆形垫片
        .washerSize = 0.65,                      // 垫片直径 30mm → 0.03m
        .washerThickness = 0.015,                // 垫片厚度 5mm → 0.005m
        .anchorLength = 1.5,                     // 锚固长度 500mm → 0.5m

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
    nut_anchor_params params{                       // 基础参数
                             .boltDiameter = 0.2,   // 地脚螺栓直径 20mm → 0.02m
                             .exposedLength = 0.40, // 露头长度 100mm → 0.1m
                             .nutCount = 2,         // 蝶帽数量保持不变
                             .nutHeight = 0.1,      // 蝶帽高度 10mm → 0.01m
                             .nutOD = 0.6,          // 蝶帽外径 40mm → 0.04m
                             .washerCount = 2,      // 垫片数量保持不变
                             .washerShape =
                                 washer_shape_type::ROUND, // 圆形垫片
                             .washerSize = 0.65,       // 垫片直径 30mm → 0.03m
                             .washerThickness = 0.015, // 垫片厚度 5mm → 0.005m
                             .anchorLength = 1.5,      // 锚固长度 500mm → 0.5m

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
        .boltDiameter = 0.2,                     // 地脚螺栓直径 20mm → 0.02m
        .exposedLength = 0.40,                   // 露头长度 100mm → 0.1m
        .nutCount = 2,                           // 蝶帽数量保持不变
        .nutHeight = 0.1,                        // 蝶帽高度 10mm → 0.01m
        .nutOD = 0.6,                            // 蝶帽外径 40mm → 0.04m
        .washerCount = 2,                        // 垫片数量保持不变
        .washerShape = washer_shape_type::ROUND, // 圆形垫片
        .washerSize = 0.65,                      // 垫片直径 30mm → 0.03m
        .washerThickness = 0.015,                // 垫片厚度 5mm → 0.005m
        .anchorLength = 1.5,                     // 锚固长度 500mm → 0.5m

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
        .boltDiameter = 0.2,                     // 地脚螺栓直径 20mm → 0.02m
        .exposedLength = 0.40,                   // 露头长度 100mm → 0.1m
        .nutCount = 2,                           // 蝶帽数量保持不变
        .nutHeight = 0.1,                        // 蝶帽高度 10mm → 0.01m
        .nutOD = 0.6,                            // 蝶帽外径 40mm → 0.04m
        .washerCount = 2,                        // 垫片数量保持不变
        .washerShape = washer_shape_type::ROUND, // 圆形垫片
        .washerSize = 0.65,                      // 垫片直径 30mm → 0.03m
        .washerThickness = 0.015,                // 垫片厚度 5mm → 0.005m
        .anchorLength = 1.5,                     // 锚固长度 500mm → 0.5m

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
        cable_wire_params{.points = straightPoints, .outsideDiameter = 10.0});

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
        cable_wire_params{.points = curvedPoints, .outsideDiameter = 8.0});

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
    cable_terminal_params outdoor_params{
        .sort = cable_terminal_type::OUTDOOR, // 户外终端
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
    cable_terminal_params indoor_params{
        .sort = cable_terminal_type::GIS, // 户内终端
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
        .leftArcHeight = 30.0,
        .rightSectionType = connection_section_style::HORSESHOE,
        .rightLength = 600.0,
        .rightWidth = 80.0,
        .rightHeight = 100.0,
        .rightArcHeight = 25.0,
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
        .leftSectionArcHeight = 15.0,
        .rightSectionStyle = connection_section_style::RECTANGULAR,
        .rightSectionLength = 60.0,
        .rightSectionWidth = 80.0,
        .rightSectionHeight = 90.0,
        .rightSectionArcHeight = 15.0,
        .branchSectionStyle = connection_section_style::HORSESHOE,
        .branchSectionLength = 80.0,
        .branchSectionWidth = 80.0,
        .branchSectionHeight = 50.0,
        .branchSectionArcHeight = 15.0,
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
        .leftSectionArcHeight = 15.0,
        .rightSectionStyle = connection_section_style::RECTANGULAR,
        .rightSectionLength = 60.0,
        .rightSectionWidth = 80.0,
        .rightSectionHeight = 90.0,
        .rightSectionArcHeight = 15.0,
        .branchSectionStyle = connection_section_style::HORSESHOE,
        .branchSectionLength = 80.0,
        .branchSectionWidth = 80.0,
        .branchSectionHeight = 50.0,
        .branchSectionArcHeight = 15.0,
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
        .leftSectionArcHeight = 15.0,
        .rightSectionStyle = connection_section_style::RECTANGULAR,
        .rightSectionLength = 60.0,
        .rightSectionWidth = 80.0,
        .rightSectionHeight = 90.0,
        .rightSectionArcHeight = 15.0,
        .branchSectionStyle = connection_section_style::HORSESHOE,
        .branchSectionLength = 80.0,
        .branchSectionWidth = 80.0,
        .branchSectionHeight = 50.0,
        .branchSectionArcHeight = 15.0,
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
                .arcHeight = 15.0,
            },
        .rightSection =
            {
                .sectionType = connection_section_style::RECTANGULAR,
                .length = 60.0,
                .width = 80.0,
                .height = 90.0,
                .arcHeight = 15.0,
            },
        .branchSection1 =
            {
                .sectionType = connection_section_style::HORSESHOE,
                .length = 80.0,
                .width = 80.0,
                .height = 50.0,
                .arcHeight = 15.0,
            },
        .branchSection2 =
            {
                .sectionType = connection_section_style::HORSESHOE,
                .length = 80.0,
                .width = 80.0,
                .height = 50.0,
                .arcHeight = 15.0,
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
                .arcHeight = 15.0,
            },
        .rightSection =
            {
                .sectionType = connection_section_style::RECTANGULAR,
                .length = 60.0,
                .width = 80.0,
                .height = 90.0,
                .arcHeight = 15.0,
            },
        .branchSection1 =
            {
                .sectionType = connection_section_style::HORSESHOE,
                .length = 80.0,
                .width = 80.0,
                .height = 50.0,
                .arcHeight = 15.0,
            },
        .branchSection2 =
            {
                .sectionType = connection_section_style::HORSESHOE,
                .length = 80.0,
                .width = 80.0,
                .height = 50.0,
                .arcHeight = 15.0,
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
      {gp_Pnt(0, 0, 0), channel_point_type::LINE},      // 起点
      {gp_Pnt(300, 0, 30), channel_point_type::LINE},   // 开始右转
      {gp_Pnt(500, 300, 50), channel_point_type::ARC},  // 过渡点(最高点)
      {gp_Pnt(300, 600, 20), channel_point_type::LINE}, // 开始左转
      {gp_Pnt(300, 800, 0), channel_point_type::LINE}   // 终点
  };

  // 测试普通排管无封包
  try {
    pipe_row_params params{
        .pipeType = pipe_row_type::NORMAL,
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
        .pipeType = pipe_row_type::NORMAL,
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
        .pipeType = pipe_row_type::PULL,
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
      {gp_Pnt(0, 0, 0), channel_point_type::LINE},      // 起点
      {gp_Pnt(300, 0, 30), channel_point_type::LINE},   // 开始右转
      {gp_Pnt(500, 300, 50), channel_point_type::ARC},  // 过渡点(最高点)
      {gp_Pnt(300, 600, 20), channel_point_type::LINE}, // 开始左转
      {gp_Pnt(300, 800, 0), channel_point_type::LINE}   // 终点
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
      {gp_Pnt(0, 0, 0), channel_point_type::LINE},      // 起点
      {gp_Pnt(300, 0, 30), channel_point_type::LINE},   // 开始右转
      {gp_Pnt(500, 300, 50), channel_point_type::ARC},  // 过渡点(最高点)
      {gp_Pnt(300, 600, 20), channel_point_type::LINE}, // 开始左转
      {gp_Pnt(300, 800, 0), channel_point_type::LINE}   // 终点
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
        .arcHeight = 12.0,         // 100→10
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
                                        .width = 60.0,                // 600→60
                                        .height = 60.0,               // 600→60
                                        .outerWallThickness = 7.0,    // 70→7
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
      {gp_Pnt(0, 0, 0), channel_point_type::LINE},    // 起点
      {gp_Pnt(900, 500, 0), channel_point_type::LINE} // 终点
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
        .arcHeight = 55.0,
        .wallThickness = 3.0,
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
      {gp_Pnt(0, 0, 0), channel_point_type::LINE},      // 起点
      {gp_Pnt(300, 0, 30), channel_point_type::LINE},   // 开始右转
      {gp_Pnt(500, 300, 50), channel_point_type::ARC},  // 过渡点(最高点)
      {gp_Pnt(300, 600, 20), channel_point_type::LINE}, // 开始左转
      {gp_Pnt(300, 800, 0), channel_point_type::LINE}   // 终点
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
        .arcHeight = 15.0,
        .wallThickness = 3.0,
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
  std::vector<channel_point> points1 = {
      {gp_Pnt(0, 0, 0), channel_point_type::LINE},    // 起点
      {gp_Pnt(900, 500, 0), channel_point_type::LINE} // 终点
  };

  // 创建测试点集
  std::vector<channel_point> points = {
      {gp_Pnt(0, 0, 0), channel_point_type::LINE},    // 起点
      {gp_Pnt(100, 0, 0), channel_point_type::LINE},  // 直线段
      {gp_Pnt(150, 50, 0), channel_point_type::ARC},  // 转弯点
      {gp_Pnt(150, 100, 0), channel_point_type::LINE} // 终点
  };

  // 测试标准步道
  try {
    auto shp = create_footpath(footpath_params{
        .height = 15.0,   // 高度150mm
        .width = 80.0,    // 宽度800mm
        .points = points1 // 路径点集
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
        .style = tunnel_partition_board_style::CIRCULAR, // 圆形
        .length = 200.0,                                 // 直径200mm
        .width = 0.0,                                    // 圆形不需要宽度
        .thickness = 10.0,                               // 厚度10mm
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
        .style = tunnel_partition_board_style::RECTANGULAR, // 方形
        .length = 300.0,                                    // 长度300mm
        .width = 200.0,                                     // 宽度200mm
        .thickness = 15.0,                                  // 厚度15mm
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
        .topHeight = 50.0,     // 顶高50mm
        .height = 150.0,       // 总高300mm
        .baseHeight = 30.0     // 基础高100mm
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
        .hoodRoomHeight = 200.0,       // 风帽室高200mm
        .hoodWallThickness = 10.0,     // 风帽壁厚10mm
        .ductCenterHeight = 80.0,      // 风通道圆心高80mm
        .ductLeftDistance = 80.0,      // 风通道圆心距左侧80mm
        .ductDiameter = 120.0,         // 风通道直径120mm
        .ductWallThickness = 8.0,      // 风通道壁厚8mm
        .ductLength = 300.0,           // 风通道长300mm
        .ductHeightDifference = 50.0,  // 风通道高度差50mm
        .baseLength = 220.0,           // 风基座长220mm
        .baseWidth = 180.0,            // 风基座宽180mm
        .baseHeight = 10.0,            // 风基座高10mm
        .baseRoomLength = 200.0,       // 风基室长200mm
        .baseRoomWallThickness = 12.0, // 风基室壁厚12mm
        .baseRoomWidth = 150.0,        // 风基室宽150mm
        .baseRoomHeight = 220.0        // 风基室高220mm
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
        .height = 300.0,          // 井净高300mm
        .neckDiameter = 150.0,    // 井脖直径150mm
        .neckHeight = 400.0,      // 井脖高400mm
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
    // 测试单侧管枕
    auto shp = create_pipe_support(pipe_support_params{
        .style = pipe_support_style::SINGLE_SIDED, // 单侧管枕
        .count = 2,                                // 2个管枕
        .positions = {{-20, 16}, {20, 16}},        // 管枕中心坐标
        .radii = {8, 8},                           // 管枕半径30mm
        .length = 100,                             // 管枕长100mm
        .width = 18,                               // 管枕宽18mm
        .height = 20                               // 管枕高20mm
    });

    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create pipe support" << std::endl;
    } else {
      test_export_shape(shp, "./pipe_support.stl");
    }

    // 测试双侧管枕
    auto shp1 = create_pipe_support(pipe_support_params{
        .style = pipe_support_style::DOUBLE_SIDED, // 双侧管枕
        .count = 8,                                // 8个管枕
        .positions = {{-10, 12},
                      {-30, 12},
                      {10, 12},
                      {30, 12},
                      {-10, -12},
                      {-30, -12},
                      {10, -12},
                      {30, -12}},          // 管枕中心坐标
        .radii = {8, 8, 8, 8, 8, 8, 8, 8}, // 管枕半径8mm
        .length = 100,                     // 管枕长100mm
        .width = 18,                       // 管枕宽18mm
        .height = 26                       // 管枕高26mm
    });

    if (shp1.IsNull()) {
      std::cerr << "Error: Failed to create pipe double support" << std::endl;
    } else {
      test_export_shape(shp1, "./pipe_double_support.stl");
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
        .style = cover_plate_style::RECTANGULAR, // 长方形
        .length = 200.0,                         // 长度200mm
        .width = 100.0,                          // 宽度100mm
        .smallRadius = 0,                        // 不适用
        .largeRadius = 0,                        // 不适用
        .thickness = 10.0                        // 厚度10mm
    });

    if (rectShp.IsNull()) {
      std::cerr << "Error: Failed to create rectangular cover plate"
                << std::endl;
    } else {
      test_export_shape(rectShp, "./rectangular_cover_plate.stl");
    }

    // 测试扇形盖板
    auto sectorShp = create_cover_plate(cover_plate_params{
        .style = cover_plate_style::SECTOR, // 扇形
        .length = 250.0,                    // 扇形边长150mm
        .width = 0,                         // 不适用
        .smallRadius = 20.0,                // 小半径50mm
        .largeRadius = 100.0,               // 大半径100mm
        .thickness = 8.0                    // 厚度8mm
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

void test_water_tunnel() {
  std::cout << "\n=== Testing Water Tunnel ===" << std::endl;

  // 创建测试点集
  std::vector<channel_point> points = {
      {gp_Pnt(0, 0, 0), channel_point_type::LINE},    // 起点
      {gp_Pnt(100, 0, 0), channel_point_type::LINE},  // 直线段
      {gp_Pnt(150, 50, 0), channel_point_type::ARC},  // 转弯点
      {gp_Pnt(150, 100, 0), channel_point_type::LINE} // 终点
  };

  // 创建测试点集
  std::vector<channel_point> points1 = {
      {gp_Pnt(0, 0, 0), channel_point_type::LINE},    // 起点
      {gp_Pnt(900, 500, 0), channel_point_type::LINE} // 终点
  };

  // 测试矩形截面隧道 (所有尺寸参数缩小10倍)
  try {
    water_tunnel_params rect_params{.style =
                                        water_tunnel_section_style::RECTANGULAR,
                                    .width = 60.0,             // 600→60
                                    .height = 80.0,            // 800→80
                                    .topThickness = 5.0,       // 50→5
                                    .bottomThickness = 6.0,    // 60→6
                                    .outerWallThickness = 7.0, // 70→7
                                    .cushionExtension = 5.0,   // 100→10
                                    .cushionThickness = 8.0,   // 80→8
                                    .points = points};

    auto rect_shp = create_water_tunnel(rect_params);
    if (rect_shp.IsNull()) {
      std::cerr << "Error: Failed to create rectangular water tunnel"
                << std::endl;
    } else {
      test_export_shape(rect_shp, "./rectangular_water_tunnel.stl");
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }

  // 测试城门洞形截面隧道 (所有尺寸参数缩小10倍)
  try {
    water_tunnel_params cityopening_params{
        .style = water_tunnel_section_style::CITYOPENING,
        .width = 50.0,             // 500→50
        .height = 70.0,            // 700→70
        .outerWallThickness = 4.0, // 40→4
        .innerWallThickness = 3.0, // 30→3
        .arcRadius = 40.0,         // 100→10
        .cushionExtension = 5.0,   // 90→9
        .cushionThickness = 7.0,   // 70→7
        .points = points};

    auto cityopening_shp = create_water_tunnel(cityopening_params);
    if (cityopening_shp.IsNull()) {
      std::cerr << "Error: Failed to create cityopening water tunnel"
                << std::endl;
    } else {
      test_export_shape(cityopening_shp, "./cityopening_water_tunnel.stl");
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }

  // 测试马蹄形截面隧道 (所有尺寸参数缩小10倍)
  try {
    water_tunnel_params horseshoe_params{
        .style = water_tunnel_section_style::HORSESHOE,
        .width = 60.0,             // 500→50
        .height = 120.0,           // 700→70
        .outerWallThickness = 4.0, // 40→4
        .innerWallThickness = 3.0, // 30→3
        .arcRadius = 50.0,         // 100→10
        .arcAngle = 120.0,         // 120度
        .cushionExtension = 5.0,   // 90→9
        .cushionThickness = 7.0,   // 70→7
        .points = points};

    auto horseshoe_shp = create_water_tunnel(horseshoe_params);
    if (horseshoe_shp.IsNull()) {
      std::cerr << "Error: Failed to create horseshoe water tunnel"
                << std::endl;
    } else {
      test_export_shape(horseshoe_shp, "./horseshoe_water_tunnel.stl");
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }

  // 测试圆形截面隧道 (所有尺寸参数缩小10倍)
  try {
    water_tunnel_params circular_params{
        .style = water_tunnel_section_style::CIRCULAR,
        .width = 60.0,                // 600→60
        .height = 60.0,               // 600→60
        .outerWallThickness = 7.0,    // 70→7
        .bottomPlatformHeight = 10.0, // 100→10
        .cushionExtension = 0.0,      // 80→8
        .cushionThickness = 0.0,      // 60→6
        .points = points};

    auto circular_shp = create_water_tunnel(circular_params);
    if (circular_shp.IsNull()) {
      std::cerr << "Error: Failed to create circular water tunnel" << std::endl;
    } else {
      test_export_shape(circular_shp, "./circular_water_tunnel.stl");
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_revol() {
  std::cout << "\n=== Testing Profile Types ===" << std::endl;

  // 测试三角形剖面
  triangle_profile tri_prof{gp_Pnt(0, 0, 0), gp_Pnt(10, 0, 0), gp_Pnt(5, 0, 8)};
  revol_params tri_params{tri_prof, gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)),
                          M_PI / 4};
  auto tri_shp = create_revol(tri_params);
  if (tri_shp.IsNull()) {
    std::cerr << "Error: Failed to create triangle profile revolved shape"
              << std::endl;
    return;
  }
  test_export_shape(tri_shp, "./triangle_profile_revol.stl");

  // 测试矩形剖面
  rectangle_profile rect_prof{gp_Pnt(0, 0, 0), gp_Pnt(10, 0, 5)};
  revol_params rect_params{rect_prof, gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)),
                           M_PI / 4};
  auto rect_shp = create_revol(rect_params);
  if (rect_shp.IsNull()) {
    std::cerr << "Error: Failed to create rectangle profile revolved shape"
              << std::endl;
    return;
  }
  test_export_shape(rect_shp, "./rectangle_profile_revol.stl");

  // 测试圆形剖面
  circ_profile circ_prof{gp_Pnt(10, 0, 0), gp_Dir(0, 1, 0), 5.0};
  revol_params circ_params{circ_prof, gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)),
                           M_PI / 4};
  auto circ_shp = create_revol(circ_params);
  if (circ_shp.IsNull()) {
    std::cerr << "Error: Failed to create circle profile revolved shape"
              << std::endl;
    return;
  }
  test_export_shape(circ_shp, "./circle_profile_revol.stl");

  // 测试椭圆剖面
  elips_profile elips_prof{
      gp_Pnt(20, 0, 0), // 长轴端点1 (X轴方向)
      gp_Pnt(10, 0, 5), // 短轴端点1 (Z轴方向)
      gp_Pnt(10, 0, 0)  // 中心点
  };
  revol_params elips_params{elips_prof,
                            gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), M_PI / 4};
  auto elips_shp = create_revol(elips_params);
  if (elips_shp.IsNull()) {
    std::cerr << "Error: Failed to create ellipse profile revolved shape"
              << std::endl;
    return;
  }
  test_export_shape(elips_shp, "./ellipse_profile_revol.stl");

  // 测试多边形剖面
  polygon_profile poly_prof{
      {gp_Pnt(0, 0, 0),   // 左下角
       gp_Pnt(10, 0, 0),  // 右下角
       gp_Pnt(15, 0, 5),  // 右顶点
       gp_Pnt(10, 0, 10), // 上顶点
       gp_Pnt(0, 0, 10)}  // 左上角
  };
  revol_params poly_params{poly_prof, gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)),
                           M_PI / 4};
  auto poly_shp = create_revol(poly_params);
  if (poly_shp.IsNull()) {
    std::cerr << "Error: Failed to create polygon profile revolved shape"
              << std::endl;
    return;
  }
  test_export_shape(poly_shp, "./polygon_profile_revol.stl");
}

void test_make_prism() {
  std::cout << "\n=== Testing Prism ===" << std::endl;

  try {
    // 测试三角形剖面棱柱
    triangle_profile tri_prof{gp_Pnt(0, 0, 0), gp_Pnt(10, 0, 0),
                              gp_Pnt(5, 8, 0)};
    prism_params tri_params{tri_prof, gp_Dir(0, 0, 1), 20};
    auto tri_shp = create_prism(tri_params);
    if (tri_shp.IsNull()) {
      std::cerr << "Error: Failed to create triangle profile prism"
                << std::endl;
    } else {
      test_export_shape(tri_shp, "./triangle_profile_prism.stl");
    }

    // 测试矩形剖面棱柱
    rectangle_profile rect_prof{gp_Pnt(0, 0, 0), gp_Pnt(10, 5, 0)};
    prism_params rect_params{rect_prof, gp_Dir(0, 0, 1), 20};
    auto rect_shp = create_prism(rect_params);
    if (rect_shp.IsNull()) {
      std::cerr << "Error: Failed to create rectangle profile prism"
                << std::endl;
    } else {
      test_export_shape(rect_shp, "./rectangle_profile_prism.stl");
    }

    // 测试圆形剖面棱柱
    circ_profile circ_prof{gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 5.0};
    prism_params circ_params{circ_prof, gp_Dir(0, 0, 1), 20};
    auto circ_shp = create_prism(circ_params);
    if (circ_shp.IsNull()) {
      std::cerr << "Error: Failed to create circle profile prism" << std::endl;
    } else {
      test_export_shape(circ_shp, "./circle_profile_prism.stl");
    }

    // 测试椭圆剖面棱柱
    elips_profile elips_prof{gp_Pnt(10, 0, 0), gp_Pnt(0, 5, 0),
                             gp_Pnt(0, 0, 0)};
    prism_params elips_params{elips_prof, gp_Dir(0, 0, 1), 20};
    auto elips_shp = create_prism(elips_params);
    if (elips_shp.IsNull()) {
      std::cerr << "Error: Failed to create ellipse profile prism" << std::endl;
    } else {
      test_export_shape(elips_shp, "./ellipse_profile_prism.stl");
    }

    // 测试多边形剖面棱柱
    polygon_profile poly_prof{{gp_Pnt(0, 0, 0), gp_Pnt(10, 0, 0),
                               gp_Pnt(15, 5, 0), gp_Pnt(10, 10, 0),
                               gp_Pnt(0, 10, 0)}};
    prism_params poly_params{poly_prof, gp_Dir(0, 0, 1), 20};
    auto poly_shp = create_prism(poly_params);
    if (poly_shp.IsNull()) {
      std::cerr << "Error: Failed to create polygon profile prism" << std::endl;
    } else {
      test_export_shape(poly_shp, "./polygon_profile_prism.stl");
    }

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_pipe() {
  std::cout << "\n=== Testing Pipe Creation ===" << std::endl;
  try {
    // 测试圆形截面直线管道
    {
      std::vector<gp_Pnt> wire = {gp_Pnt(0, 0, 0), gp_Pnt(100, 0, 0)};
      circ_profile profile(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 5.0);
      circ_profile profile2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 10.0);

      pipe_params params{.wire = wire,
                         .profiles = {profile, profile2},
                         .segment_type = segment_type::LINE,
                         .transition_mode = transition_mode::TRANSFORMED};

      auto shp = create_pipe(params);
      if (shp.IsNull()) {
        std::cerr << "Error: Failed to create circular line pipe" << std::endl;
        return;
      }
      test_export_shape(shp, "./circular_line_pipe.stl");
    }

    // 测试圆形截面三点弧线管道
    {
      std::vector<gp_Pnt> wire = {gp_Pnt(0, 0, 0), gp_Pnt(50, 50, 0),
                                  gp_Pnt(100, 0, 0)};
      circ_profile profile(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 5.0);
      circ_profile profile2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 10.0);

      pipe_params params{.wire = wire,
                         .profiles = {profile, profile2},
                         .segment_type = segment_type::THREE_POINT_ARC,
                         .transition_mode = transition_mode::TRANSFORMED};

      auto shp = create_pipe(params);
      if (shp.IsNull()) {
        std::cerr << "Error: Failed to create circular arc pipe" << std::endl;
        return;
      }
      test_export_shape(shp, "./circular_arc_pipe.stl");
    }

    // 测试圆形截面圆心弧线管道
    {
      std::vector<gp_Pnt> wire = {
          gp_Pnt(0, 0, 0),  // 起点
          gp_Pnt(50, 0, 0), // 圆心
          gp_Pnt(100, 0, 0) // 终点
      };
      circ_profile profile(gp_Pnt(50, 0, 0), gp_Dir(0, 0, 1), 6.0);
      circ_profile profile2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 10.0);

      pipe_params params{.wire = wire,
                         .profiles = {profile, profile2},
                         .segment_type = segment_type::CIRCLE_CENTER_ARC,
                         .transition_mode = transition_mode::TRANSFORMED};

      auto shp = create_pipe(params);
      if (shp.IsNull()) {
        std::cerr << "Error: Failed to create circular center arc pipe"
                  << std::endl;
        return;
      }
      test_export_shape(shp, "./circular_center_arc_pipe.stl");
    }

    // 测试圆形截面样条曲线管道
    {
      std::vector<gp_Pnt> wire = {gp_Pnt(0, 0, 0), gp_Pnt(30, 30, 20),
                                  gp_Pnt(70, 30, 40), gp_Pnt(100, 0, 50)};
      circ_profile profile(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 5.0);
      circ_profile profile2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 10.0);

      pipe_params params{.wire = wire,
                         .profiles = {profile, profile2},
                         .segment_type = segment_type::SPLINE,
                         .transition_mode = transition_mode::TRANSFORMED};

      auto shp = create_pipe(params);
      if (shp.IsNull()) {
        std::cerr << "Error: Failed to create circular spline pipe"
                  << std::endl;
        return;
      }
      test_export_shape(shp, "./circular_spline_pipe.stl");
    }

    // 测试多边形截面直线管道
    {
      std::vector<gp_Pnt> wire = {gp_Pnt(0, 0, 0), gp_Pnt(100, 0, 0)};
      std::vector<gp_Pnt> edges = {gp_Pnt(0, 0, 0), gp_Pnt(10, 0, 0),
                                   gp_Pnt(10, 5, 0), gp_Pnt(0, 5, 0),
                                   gp_Pnt(0, 0, 0)};
      polygon_profile profile(edges);
      pipe_params params{.wire = wire,
                         .profiles = {profile},
                         .segment_type = segment_type::LINE,
                         .transition_mode = transition_mode::TRANSFORMED};

      auto shp = create_pipe(params);
      if (shp.IsNull()) {
        std::cerr << "Error: Failed to create polygon line pipe" << std::endl;
        return;
      }
      test_export_shape(shp, "./polygon_line_pipe.stl");
    }

    // 测试圆形截面样条曲线管道
    {
      std::vector<gp_Pnt> wire = {gp_Pnt(0, 0, 0), gp_Pnt(30, 30, 20),
                                  gp_Pnt(70, 30, 40), gp_Pnt(100, 0, 50)};
      circ_profile profile(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 5.0);
      circ_profile innerProfile(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 3.0);

      pipe_params params{.wire = wire,
                         .profiles = {profile},
                         .inner_profiles = {{innerProfile}},
                         .segment_type = segment_type::SPLINE,
                         .transition_mode = transition_mode::TRANSFORMED};

      auto shp = create_pipe(params);
      if (shp.IsNull()) {
        std::cerr << "Error: Failed to create circular spline pipe"
                  << std::endl;
        return;
      }
      test_export_shape(shp, "./circular_spline_inner_pipe.stl");
    }

    {
      std::vector<gp_Pnt> wire = {gp_Pnt(0, 0, 0), gp_Pnt(100, 0, 0)};
      circ_profile profile(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 5.0);
      circ_profile profile2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 10.0);

      pipe_params params{.wire = wire,
                         .profiles = {profile, profile2},
                         .segment_type = segment_type::LINE,
                         .transition_mode = transition_mode::TRANSFORMED};

      // 测试从20mm到80mm的分割
      auto shp = create_pipe_with_split_distances(params, {20.0, 80.0});
      if (shp.IsNull()) {
        std::cerr
            << "Error: Failed to create circular line pipe with split distances"
            << std::endl;
        return;
      }
      test_export_shape(shp, "./circular_line_pipe_split.stl");
    }

    {
      std::vector<gp_Pnt> wire = {gp_Pnt(0, 0, 0), gp_Pnt(30, 30, 20),
                                  gp_Pnt(70, 30, 40), gp_Pnt(100, 0, 50)};
      circ_profile profile(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 5.0);
      circ_profile innerProfile(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 3.0);

      pipe_params params{.wire = wire,
                         .profiles = {profile},
                         .inner_profiles = {{innerProfile}},
                         .segment_type = segment_type::SPLINE,
                         .transition_mode = transition_mode::TRANSFORMED};

      // 测试从10mm到80mm的分割
      auto splitShp = create_pipe_with_split_distances(params, {10.0, 80.0});
      if (splitShp.IsNull()) {
        std::cerr << "Error: Failed to create split circular spline pipe"
                  << std::endl;
        return;
      }
      test_export_shape(splitShp, "./circular_spline_inner_pipe_split.stl");
    }

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_multi_segment_pipe() {
  std::cout << "\n=== Testing Multi-Segment Pipe Creation ===" << std::endl;
  try {
    // 准备测试数据 - 直线段
    std::vector<gp_Pnt> linePoints = {gp_Pnt(50, -50, 0), gp_Pnt(100, 0, 0)};

    // 准备测试数据 - 三点圆弧
    std::vector<gp_Pnt> arcPoints = {gp_Pnt(100, 0, 0), gp_Pnt(150, 50, 0),
                                     gp_Pnt(200, 0, 0)};

    // 准备测试数据 - 圆心弧线
    std::vector<gp_Pnt> centerArcPoints = {gp_Pnt(200, 0, 0),
                                           gp_Pnt(250, 0, 0), // 圆心
                                           gp_Pnt(300, 0, 0)};

    // 准备测试数据 - 样条曲线
    std::vector<gp_Pnt> splinePoints = {gp_Pnt(300, 0, 0), gp_Pnt(350, 50, 50),
                                        gp_Pnt(400, 0, 100)};

    // 创建圆形剖面
    circ_profile profile(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 10.0);

    // 创建内孔剖面
    circ_profile innerProfile(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 8.0);

    // 设置多段管道参数
    multi_segment_pipe_params params{
        .wires = {linePoints, arcPoints, centerArcPoints, splinePoints},
        .profiles = {profile, profile, profile, profile},
        .inner_profiles = {{innerProfile, innerProfile, innerProfile,
                            innerProfile}},
        .segment_types = {{segment_type::LINE, segment_type::THREE_POINT_ARC,
                           segment_type::CIRCLE_CENTER_ARC,
                           segment_type::SPLINE}},
        .transition_mode = transition_mode::ROUND};

    auto shp = create_multi_segment_pipe(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create multi-segment pipe" << std::endl;
      return;
    }
    test_export_shape(shp, "./multi_segment_pipe.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }

  try {
    std::vector<std::vector<gp_Pnt>> points = {
        {gp_Pnt(0, 0, 0),
         gp_Pnt(13.363751136232167, -26.227833716198802, 40.422308564186096)},
        {gp_Pnt(13.363751136232167, -26.227833716198802, 40.422308564186096),
         gp_Pnt(46.29231750732288, -90.69991450663656, 108.94551491551101)},
        {gp_Pnt(46.29231750732288, -90.69991450663656, 108.94551491551101),
         gp_Pnt(132.02422594139352, -257.1274096108973, -1.525045077316463)},
        {gp_Pnt(132.02422594139352, -257.1274096108973, -1.525045077316463),
         gp_Pnt(155.7862730268389, -461.9796159574762, 275.57995436759666)},
        {gp_Pnt(155.7862730268389, -461.9796159574762, 275.57995436759666),
         gp_Pnt(277.5595232350752, -1029.277987377718, 560.3984563779086)}};
    gp_Dir upDir =
        gp_Vec(-2365550.686973459, 4588616.347934356, 3734082.7681595744)
            .Normalized();
    std::vector<gp_Pnt> polygons = {
        gp_Pnt(-3.171, 2.538, 0), gp_Pnt(-3.136, 3.954, 0),
        gp_Pnt(-2.498, 5.219, 0), gp_Pnt(-1.382, 6.09, 0),
        gp_Pnt(0, 6.4, 0),        gp_Pnt(1.382, 6.09, 0),
        gp_Pnt(2.498, 5.219, 0),  gp_Pnt(3.136, 3.954, 0),
        gp_Pnt(3.171, 2.538, 0),  gp_Pnt(2.5, 0, 0),
        gp_Pnt(-2.5, 0, 0),       gp_Pnt(-3.171, 2.538, 0)};

    // 创建多边形剖面
    polygon_profile profile(polygons);

    // 设置多段管道参数
    multi_segment_pipe_params params{
        .wires = points,
        .profiles = {profile, profile, profile, profile, profile},
        .segment_types = {{segment_type::LINE, segment_type::LINE,
                           segment_type::LINE, segment_type::LINE,
                           segment_type::LINE}},
        .transition_mode = transition_mode::TRANSFORMED,
        .upDir = upDir};

    auto shp = create_multi_segment_pipe(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create multi-segment pipe" << std::endl;
      return;
    }
    test_export_shape(shp, "./multi_segment_bug.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }

  try {
    // 准备测试数据 - 直线段
    std::vector<gp_Pnt> linePoints = {gp_Pnt(50, -50, 0), gp_Pnt(100, 0, 0)};

    // 准备测试数据 - 三点圆弧
    std::vector<gp_Pnt> arcPoints = {gp_Pnt(100, 0, 0), gp_Pnt(150, 50, 0),
                                     gp_Pnt(200, 0, 0)};

    // 准备测试数据 - 圆心弧线
    std::vector<gp_Pnt> centerArcPoints = {gp_Pnt(200, 0, 0),
                                           gp_Pnt(250, 0, 0), // 圆心
                                           gp_Pnt(300, 0, 0)};

    // 准备测试数据 - 样条曲线
    std::vector<gp_Pnt> splinePoints = {gp_Pnt(300, 0, 0), gp_Pnt(350, 50, 50),
                                        gp_Pnt(400, 0, 100)};

    // 创建圆形剖面
    circ_profile profile(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 10.0);

    // 创建内孔剖面
    circ_profile innerProfile(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 8.0);

    // 设置多段管道参数
    multi_segment_pipe_params params{
        .wires = {linePoints, arcPoints, centerArcPoints, splinePoints},
        .profiles = {profile, profile, profile, profile},
        .inner_profiles = {{innerProfile, innerProfile, innerProfile,
                            innerProfile}},
        .segment_types = {{segment_type::LINE, segment_type::THREE_POINT_ARC,
                           segment_type::CIRCLE_CENTER_ARC,
                           segment_type::SPLINE}},
        .transition_mode = transition_mode::ROUND};

    // 测试2: 前部裁切(needFrontCut)
    std::cout << "\nTest Case 2: Front Cut (splitDistances = {50, -1})"
              << std::endl;
    auto shp2 =
        create_multi_segment_pipe_with_split_distances(params, {50.0, -1});
    if (shp2.IsNull()) {
      std::cerr << "Error: Failed to create pipe with front cut" << std::endl;
    } else {
      test_export_shape(shp2, "./multi_segment_pipe_front_cut.stl");
    }

    // 测试3: 后部裁切(needBackCut)
    std::cout << "\nTest Case 3: Back Cut (splitDistances = {0, 250})"
              << std::endl;
    auto shp3 =
        create_multi_segment_pipe_with_split_distances(params, {0.0, 250.0});
    if (shp3.IsNull()) {
      std::cerr << "Error: Failed to create pipe with back cut" << std::endl;
    } else {
      test_export_shape(shp3, "./multi_segment_pipe_back_cut.stl");
    }

    // 测试4: 前后都裁切(needFrontCut && needBackCut)
    std::cout
        << "\nTest Case 4: Both Front and Back Cut (splitDistances = {50, 250})"
        << std::endl;
    auto shp4 =
        create_multi_segment_pipe_with_split_distances(params, {50.0, 250.0});
    if (shp4.IsNull()) {
      std::cerr << "Error: Failed to create pipe with both cuts" << std::endl;
    } else {
      test_export_shape(shp4, "./multi_segment_pipe_both_cuts.stl");
    }

    // 测试5: 中间段裁切(裁切范围在第二段)
    std::cout
        << "\nTest Case 5: Middle Segment Cut (splitDistances = {120, 180})"
        << std::endl;
    auto shp5 =
        create_multi_segment_pipe_with_split_distances(params, {120.0, 180.0});
    if (shp5.IsNull()) {
      std::cerr << "Error: Failed to create pipe with middle segment cut"
                << std::endl;
    } else {
      test_export_shape(shp5, "./multi_segment_pipe_middle_cut.stl");
    }

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

void test_make_pipe_joint() {
  std::cout << "\n=== Testing Pipe Joint Creation ===" << std::endl;

  try {
    // 创建圆形剖面
    circ_profile profile(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 10.0);
    circ_profile innerProfile(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 8.0);

    circ_profile profile2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 8.0);
    circ_profile innerProfile2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 4.0);

    // 1. 测试两根管子的连接(直通接头)
    {
      pipe_joint_params params{.ins = {{.offset = gp_Pnt(-50, 0, 0),
                                        .normal = gp_Dir(1, 0, 0),
                                        .profile = {profile},
                                        .inner_profile = {{innerProfile}}}},
                               .outs = {{.offset = gp_Pnt(50, 0, 0),
                                         .normal = gp_Dir(-1, 0, 0),
                                         .profile = {profile},
                                         .inner_profile = {{innerProfile}}}},
                               .mode = joint_shape_mode::SPHERE,
                               .flanged = true};

      auto shp = create_pipe_joint(params);
      test_export_shape(shp, "./pipe_joint_2.stl");
    }

    // 2. 测试三根T型管子的连接
    {
      pipe_joint_params params{.ins = {{.offset = gp_Pnt(-50, 0, 0),
                                        .normal = gp_Dir(1, 0, 0),
                                        .profile = {profile},
                                        .inner_profile = {{innerProfile}}},
                                       {.offset = gp_Pnt(0, -50, 0),
                                        .normal = gp_Dir(0, 1, 0),
                                        .profile = {profile},
                                        .inner_profile = {{innerProfile}}}},
                               .outs = {{.offset = gp_Pnt(50, 0, 0),
                                         .normal = gp_Dir(-1, 0, 0),
                                         .profile = {profile2},
                                         .inner_profile = {{innerProfile2}}}},
                               .mode = joint_shape_mode::BOX,
                               .flanged = true};

      auto shp = create_pipe_joint(params);
      test_export_shape(shp, "./pipe_joint_T.stl");
    }

    // 3. 测试四根管子的连接(十字接头)
    {
      pipe_joint_params params{.ins = {{.offset = gp_Pnt(-50, 0, 0),
                                        .normal = gp_Dir(1, 0, 0),
                                        .profile = {profile},
                                        .inner_profile = {{innerProfile}}},
                                       {.offset = gp_Pnt(0, -50, 0),
                                        .normal = gp_Dir(0, 1, 0),
                                        .profile = {profile2},
                                        .inner_profile = {{innerProfile2}}}},
                               .outs = {{.offset = gp_Pnt(50, 0, 0),
                                         .normal = gp_Dir(-1, 0, 0),
                                         .profile = {profile},
                                         .inner_profile = {{innerProfile}}},
                                        {.offset = gp_Pnt(0, 50, 0),
                                         .normal = gp_Dir(0, -1, 0),
                                         .profile = {profile2},
                                         .inner_profile = {{innerProfile2}}}},
                               .mode = joint_shape_mode::CYLINDER,
                               .flanged = false};

      auto shp = create_pipe_joint(params);
      test_export_shape(shp, "./pipe_joint_4.stl");
    }

    // 4. 测试三根Y型管子的连接
    {
      pipe_joint_params params{.ins = {{.offset = gp_Pnt(-50, -50, 0),
                                        .normal = gp_Vec(1, 1, 0).Normalized(),
                                        .profile = {profile2},
                                        .inner_profile = {{innerProfile2}}},
                                       {.offset = gp_Pnt(-50, 50, 0),
                                        .normal = gp_Vec(1, -1, 0).Normalized(),
                                        .profile = {profile2},
                                        .inner_profile = {{innerProfile2}}}},
                               .outs = {{.offset = gp_Pnt(50, 0, 0),
                                         .normal = gp_Dir(-1, 0, 0),
                                         .profile = {profile},
                                         .inner_profile = {{innerProfile}}}},
                               .mode = joint_shape_mode::SPHERE,
                               .flanged = true};

      auto shp = create_pipe_joint(params);
      test_export_shape(shp, "./pipe_joint_Y.stl");
    }

  } catch (const Standard_Failure &e) {
    std::cerr << "Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_multi_layer_extrusion_structure() {
  std::cout << "\n=== Testing Multi-Layer Extrusion Structure ===" << std::endl;

  try {
    // 1. 创建路径线

    // 准备测试数据 - 直线段
    std::vector<gp_Pnt> linePoints = {gp_Pnt(50, -50, 0), gp_Pnt(100, 0, 0)};

    // 准备测试数据 - 三点圆弧
    std::vector<gp_Pnt> arcPoints = {gp_Pnt(100, 0, 0), gp_Pnt(150, 50, 0),
                                     gp_Pnt(200, 0, 0)};

    // 准备测试数据 - 圆心弧线
    std::vector<gp_Pnt> centerArcPoints = {gp_Pnt(200, 0, 0),
                                           gp_Pnt(250, 0, 0), // 圆心
                                           gp_Pnt(300, 0, 0)};

    // 准备测试数据 - 样条曲线
    std::vector<gp_Pnt> splinePoints = {gp_Pnt(300, 0, 0), gp_Pnt(350, 50, 50),
                                        gp_Pnt(400, 0, 100)};

    // 2. 定义剖面层
    std::vector<profile_layer> layers;

    // 第一层 - 矩形剖面
    profile_layer layer1;
    layer1.name = "base_layer";
    layer1.profiles.push_back(
        rectangle_profile{gp_Pnt(-10, -50, 0), gp_Pnt(10, -30, 0)});
    layers.push_back(layer1);

    // 第二层 - 圆形剖面
    profile_layer layer2;
    layer2.name = "middle_layer";
    layer2.profiles.push_back(
        circ_profile{gp_Pnt(0, -20, 0), gp_Dir(0, 0, 1), 16.0});
    layers.push_back(layer2);

    // 第三层 - 多边形剖面
    profile_layer layer3;
    layer3.name = "top_layer";
    std::vector<gp_Pnt> polygonPoints = {gp_Pnt(-5, -5, 0), gp_Pnt(5, -5, 0),
                                         gp_Pnt(5, 5, 0), gp_Pnt(0, 8, 0),
                                         gp_Pnt(-5, 5, 0)};
    layer3.profiles.push_back(polygon_profile{polygonPoints});
    layers.push_back(layer3);

    // 3. 创建参数结构
    multi_layer_extrusion_structure_params params{
        .wires = {linePoints, arcPoints, centerArcPoints, splinePoints},
        .segment_types = {{segment_type::LINE, segment_type::THREE_POINT_ARC,
                           segment_type::CIRCLE_CENTER_ARC,
                           segment_type::SPLINE}},
        .layers = layers,
        .transition_mode = transition_mode::TRANSFORMED,
        .upDir = gp_Dir(0, 0, 1)};

    // 4. 创建多层挤出结构
    auto shapes = create_multi_layer_extrusion_structure(params);

    BRep_Builder builder;
    TopoDS_Compound compound;
    builder.MakeCompound(compound);

    for (const auto &[name, shape] : shapes) {
      builder.Add(compound, shape);
    }

    std::string filename = "./multi_layer_extrusion.stl";
    test_export_shape(compound, filename);

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_catenary() {
  std::cout << "\n=== Testing Catenary ===" << std::endl;
  try {
    // 创建圆形剖面
    circ_profile circ_prof{gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 0.2};

    // 测试标准悬垂线
    catenary_params params{
        .p1 = gp_Pnt(0, 0, 0),     // 起点
        .p2 = gp_Pnt(100, 100, 0), // 终点
        .profile = circ_prof,      // 圆形剖面
        .slack = 2,                // 悬垂度
        .maxSag = 10.0,            // 最大垂度
        .tessellation = 0.0        // 分段数
    };

    auto shp = create_catenary(params);
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create catenary" << std::endl;
      return;
    }
    test_export_shape(shp, "./catenary.stl");

    // 测试带高度的悬垂线
    catenary_params height_params{.p1 = gp_Pnt(0, 0, 0),     // 起点高度0
                                  .p2 = gp_Pnt(100, 50, 20), // 终点高度20
                                  .profile = circ_prof,
                                  .slack = 2.0,
                                  .maxSag = 10.0,
                                  .tessellation = 0.0};

    auto height_shp = create_catenary(height_params);
    if (height_shp.IsNull()) {
      std::cerr << "Error: Failed to create height catenary" << std::endl;
      return;
    }
    test_export_shape(height_shp, "./height_catenary.stl");

    gp_Dir upDir =
        gp_Vec(-2365550.686973459, 4588616.347934356, 3734082.7681595744)
            .Normalized();
    // 测试标准悬垂线
    catenary_params bug_params{.p1 = gp_Pnt(0, 0, 0), // 起点
                               .p2 = gp_Pnt(26.363751136232167,
                                            -26.227833716198802,
                                            30.422308564186096), // 终点
                               .profile = circ_prof,             // 圆形剖面
                               .slack = 2,                       // 悬垂度
                               .maxSag = 10.0,                   // 最大垂度
                               .tessellation = 0.0,              // 分段数
                               .upDir = upDir};

    auto bug_shp = create_catenary(bug_params);
    if (bug_shp.IsNull()) {
      std::cerr << "Error: Failed to create catenary" << std::endl;
      return;
    }
    test_export_shape(bug_shp, "./catenary_bug.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_box_shape() {
  std::cout << "\n=== Testing Box Shape ===" << std::endl;
  try {
    auto shp = create_box_shape(box_shape_params{
        .point1 = gp_Pnt(0, 0, 0), .point2 = gp_Pnt(100, 50, 30)});
    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create box shape" << std::endl;
      return;
    }
    test_export_shape(shp, "./box_shape.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_cone_shape() {
  std::cout << "\n=== Testing Cone Shape ===" << std::endl;
  try {
    // 测试完整圆锥
    auto fullShp = create_cone_shape(
        cone_shape_params{.radius1 = 20.0, .radius2 = 10.0, .height = 30.0});
    if (fullShp.IsNull()) {
      std::cerr << "Error: Failed to create full cone" << std::endl;
      return;
    }
    test_export_shape(fullShp, "./full_cone_shape.stl");

    // 测试部分圆锥
    auto partialShp =
        create_cone_shape(cone_shape_params{.radius1 = 15.0,
                                            .radius2 = 5.0,
                                            .height = 25.0,
                                            .angle = 270.0 * M_PI / 180});
    if (partialShp.IsNull()) {
      std::cerr << "Error: Failed to create partial cone" << std::endl;
      return;
    }
    test_export_shape(partialShp, "./partial_cone_shape.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_cylinder_shape() {
  std::cout << "\n=== Testing Cylinder Shape ===" << std::endl;
  try {
    // 测试完整圆柱
    auto fullShp = create_cylinder_shape(
        cylinder_shape_params{.radius = 15.0, .height = 25.0});
    if (fullShp.IsNull()) {
      std::cerr << "Error: Failed to create full cylinder" << std::endl;
      return;
    }
    test_export_shape(fullShp, "./full_cylinder_shape.stl");

    // 测试部分圆柱
    auto partialShp = create_cylinder_shape(cylinder_shape_params{
        .radius = 10.0, .height = 20.0, .angle = 270.0 * M_PI / 180});
    if (partialShp.IsNull()) {
      std::cerr << "Error: Failed to create partial cylinder" << std::endl;
      return;
    }
    test_export_shape(partialShp, "./partial_cylinder_shape.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_revolution_shape() {
  std::cout << "\n=== Testing Revolution Shape ===" << std::endl;
  try {
    std::vector<gp_Pnt> meridian = {gp_Pnt(0, 0, 0), gp_Pnt(10, 0, 0),
                                    gp_Pnt(15, 5, 0), gp_Pnt(10, 10, 0),
                                    gp_Pnt(0, 10, 0)};
    // 测试完整旋转体(360度)
    auto fullShp =
        create_revolution_shape(revolution_shape_params{.meridian = meridian});
    if (fullShp.IsNull()) {
      std::cerr << "Error: Failed to create full revolution shape" << std::endl;
      return;
    }
    test_export_shape(fullShp, "./full_revolution_shape.stl");

    // 测试部分旋转体(270度)
    auto partialShp = create_revolution_shape(revolution_shape_params{
        .meridian = meridian, .angle = 270.0 * M_PI / 180});
    if (partialShp.IsNull()) {
      std::cerr << "Error: Failed to create partial revolution shape"
                << std::endl;
      return;
    }
    test_export_shape(partialShp, "./partial_revolution_shape.stl");

    // 测试带VMin/VMax参数的旋转体
    auto rangedShp = create_revolution_shape(
        revolution_shape_params{.meridian = meridian,
                                .angle = 180.0 * M_PI / 180,
                                .max = 8.0,
                                .min = 2.0});
    if (rangedShp.IsNull()) {
      std::cerr << "Error: Failed to create ranged revolution shape"
                << std::endl;
      return;
    }
    test_export_shape(rangedShp, "./ranged_revolution_shape.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_sphere_shape() {
  std::cout << "\n=== Testing Sphere Shape ===" << std::endl;
  try {
    // 测试完整球体
    auto fullShp = create_sphere_shape(sphere_shape_params{.radius = 20.0});
    if (fullShp.IsNull()) {
      std::cerr << "Error: Failed to create full sphere" << std::endl;
      return;
    }
    test_export_shape(fullShp, "./full_sphere_shape.stl");

    // 测试部分球体
    auto partialShp =
        create_sphere_shape(sphere_shape_params{.radius = 15.0,
                                                .angle1 = 0.0,
                                                .angle2 = 90.0 * M_PI / 180,
                                                .angle = 270.0 * M_PI / 180});
    if (partialShp.IsNull()) {
      std::cerr << "Error: Failed to create partial sphere" << std::endl;
      return;
    }
    test_export_shape(partialShp, "./partial_sphere_shape.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_torus_shape() {
  std::cout << "\n=== Testing Torus Shape ===" << std::endl;
  try {
    // 测试完整圆环
    auto fullShp = create_torus_shape(
        torus_shape_params{.radius1 = 30.0, .radius2 = 10.0});
    if (fullShp.IsNull()) {
      std::cerr << "Error: Failed to create full torus" << std::endl;
      return;
    }
    test_export_shape(fullShp, "./full_torus_shape.stl");

    // 测试部分圆环
    auto partialShp = create_torus_shape(torus_shape_params{
        .radius1 = 25.0,              // 主半径保持不变
        .radius2 = 8.0,               // 次半径保持不变
        .angle1 = -30.0 * M_PI / 180, // 起始纬度角度（南纬30度）
        .angle2 = 30.0 * M_PI / 180,  // 结束纬度角度（北纬30度）
        .angle = 270.0 * M_PI / 180   // 经度扫掠角度保持不变
    });
    if (partialShp.IsNull()) {
      std::cerr << "Error: Failed to create partial torus" << std::endl;
      return;
    }
    test_export_shape(partialShp, "./partial_torus_shape.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_wedge_shape() {
  std::cout << "\n=== Testing Wedge Shape ===" << std::endl;
  try {
    // 测试完整楔形
    auto fullShp =
        create_wedge_shape(wedge_shape_params{.edge = gp_Pnt(30, 20, 10)});
    if (fullShp.IsNull()) {
      std::cerr << "Error: Failed to create full wedge" << std::endl;
      return;
    }
    test_export_shape(fullShp, "./full_wedge_shape.stl");

    // 测试有限制面的楔形
    auto limitedShp = create_wedge_shape(
        wedge_shape_params{.edge = gp_Pnt(25, 15, 8),
                           .limit = wedge_face_limit{10.0, 5.0, 15.0, 7.0},
                           .ltx = 12.0});
    if (limitedShp.IsNull()) {
      std::cerr << "Error: Failed to create limited wedge" << std::endl;
      return;
    }
    test_export_shape(limitedShp, "./limited_wedge_shape.stl");
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_pipe_shape() {
  std::cout << "\n=== Testing Pipe Shape ===" << std::endl;

  try {
    // 测试基本管道形状
    auto basicShp = create_pipe_shape(pipe_shape_params{
        .wire = {gp_Pnt(0, 0, 0), gp_Pnt(100, 0, 0)},
        .profile = circ_profile{gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 10.0}});
    if (basicShp.IsNull()) {
      std::cerr << "Error: Failed to create basic pipe shape" << std::endl;
      return;
    }
    test_export_shape(basicShp, "./basic_pipe_shape.stl");

    // 测试带方向的管道形状
    auto dirShp = create_pipe_shape(pipe_shape_params{
        .wire = {gp_Pnt(0, 0, 0), gp_Pnt(0, 100, 50)},
        .profile = circ_profile{gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), 8.0},
        .upDir = gp_Dir(1, 0, 0)});
    if (dirShp.IsNull()) {
      std::cerr << "Error: Failed to create pipe shape with direction"
                << std::endl;
      return;
    }
    test_export_shape(dirShp, "./directed_pipe_shape.stl");

    // 测试复杂剖面管道形状
    auto complexShp = create_pipe_shape(pipe_shape_params{
        .wire = {gp_Pnt(0, 0, 0), gp_Pnt(50, 50, 30)},
        .profile = polygon_profile{{gp_Pnt(0, 0, 0), gp_Pnt(10, 0, 0),
                                    gp_Pnt(15, 5, 0), gp_Pnt(10, 10, 0),
                                    gp_Pnt(0, 10, 0)}}});
    if (complexShp.IsNull()) {
      std::cerr << "Error: Failed to create complex profile pipe shape"
                << std::endl;
      return;
    }
    test_export_shape(complexShp, "./complex_profile_pipe_shape.stl");

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}

void test_make_wire_from_segments() {
  std::cout << "\n=== Testing Wire From Segments ===" << std::endl;
  try {
    // 测试基本线
    BRepBuilderAPI_MakeWire wireMaker;
    wireMaker.Add(BRepBuilderAPI_MakeEdge(
        gp_Pnt(0, 0, 0),
        gp_Pnt(-15.676352151669562, 22.01439344789833, -36.72105858521536)));
    if (!wireMaker.IsDone()) {
      std::cerr << "Error: Failed to create basic wire from segments"
                << std::endl;
      return;
    }
    auto basicWire = wireMaker.Wire();
    if (basicWire.IsNull()) {
      std::cerr << "Error: Failed to create basic wire from segments"
                << std::endl;
      return;
    }
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  }
}


void test_multi_segment_pipe_with_split_distances() {
  
  try {
    // 准备测试数据 - 直线段 (两段Z轴方向的直线)
    std::vector<gp_Pnt> segment1Points = {gp_Pnt(0, 0, 0), gp_Pnt(13.363751136232167, -26.227833716198802, 40.422308564186096)};
    std::vector<gp_Pnt> segment2Points = {gp_Pnt(13.363751136232167, -26.227833716198802, 40.422308564186096), gp_Pnt(46.29231750732288, -90.69991450663656, 108.94551491551101)};

    // 创建第一个多边形剖面 (12个点)
    std::vector<gp_Pnt> polygon1 = {
        gp_Pnt(-3.171, 2.538, 0),
        gp_Pnt(-3.136, 3.954, 0),
        gp_Pnt(-2.498, 5.219, 0),
        gp_Pnt(-1.382, 6.09, 0),
        gp_Pnt(0, 6.4, 0),
        gp_Pnt(1.382, 6.09, 0),
        gp_Pnt(2.498, 5.219, 0),
        gp_Pnt(3.136, 3.954, 0),
        gp_Pnt(3.171, 2.538, 0),
        gp_Pnt(2.5, 0, 0),
        gp_Pnt(-2.5, 0, 0),
        gp_Pnt(-3.171, 2.538, 0)};
    
    // 创建第二个多边形剖面 (10个点)
    std::vector<gp_Pnt> polygon2 = {
        gp_Pnt(-3.4, 3.25, 0),
        gp_Pnt(-2.773, 4.717, 0),
        gp_Pnt(-1.553, 5.746, 0),
        gp_Pnt(0, 6.115, 0),
        gp_Pnt(1.553, 5.746, 0),
        gp_Pnt(2.773, 4.717, 0),
        gp_Pnt(3.4, 3.25, 0),
        gp_Pnt(3.4, 0, 0),
        gp_Pnt(-3.4, 0, 0),
        gp_Pnt(-3.4, 3.25, 0)};


    // 创建第一个多边形剖面 (12个点) - polygon3
      std::vector<gp_Pnt> polygon3 = {
          gp_Pnt(-3.078273455639578, 2.575440459011272, 0),
          gp_Pnt(-3.036354153205542, 3.945591360596666, 0),
          gp_Pnt(-2.415107425541498, 5.163064134049417, 0),
          gp_Pnt(-1.339465963909452, 5.999496653245043, 0),
          gp_Pnt(-0.00978236558095332, 6.3004796235756695, 0),
          gp_Pnt(1.3250857438602934, 6.007776113883715, 0),
          gp_Pnt(2.410219147892808, 5.171098830877157, 0),
          gp_Pnt(3.0362530020384777, 3.946891104328797, 0),
          gp_Pnt(3.0763705290048873, 2.57033053075941, 0),
          gp_Pnt(2.4402700090676666, 0.08020179663338835, 0),
          gp_Pnt(-2.4484020179459174, 0.08566007382641323, 0),
          gp_Pnt(-3.078273455639578, 2.575440459011272, 0) // 闭合多边形
      };
    
    // 创建第二个多边形剖面 (10个点) - polygon4
    std::vector<gp_Pnt> polygon4 = {
        gp_Pnt(-3.3009689384399516, 3.2638870027828157, 0),
        gp_Pnt(-2.681019727080062, 4.6777618885065335, 0),
        gp_Pnt(-1.5023855429647655, 5.659755134999072, 0),
        gp_Pnt(-0.013823869618346543, 6.0159601058725585, 0),
        gp_Pnt(1.4854596950468153, 5.672255120809437, 0),
        gp_Pnt(2.678133803605064, 4.68537082388747, 0),
        gp_Pnt(3.30065175118932, 3.2613984849103375, 0),
        gp_Pnt(3.328711291934881, 0.07012788391507485, 0),
        gp_Pnt(-3.336054557835377, 0.07688290074113246, 0),
        gp_Pnt(-3.3009689384399516, 3.2638870027828157, 0)};


    // 创建多边形剖面
    polygon_profile profile1(polygon1);
    polygon_profile profile2(polygon2);

    // 设置多段管道参数
    multi_segment_pipe_params params{
        .wires = {segment1Points, segment2Points},
        .profiles = {polygon1, polygon2},
        .inner_profiles = {{polygon3, polygon4}},
        .segment_types = {
            {segment_type::LINE, 
             segment_type::LINE}},
        .transition_mode = transition_mode::TRANSFORMED,
        .upDir = gp_Dir(-0.37127704827582503, 0.7201908387390975, 0.586070396129907)  // Z轴方向
    };

    // 测试6: 多边形剖面的多段管道
    std::cout << "\nTest Case 6: Polygonal Profiles (splitDistances = {1.0, 1.0})" << std::endl;
    auto shp6 = create_multi_segment_pipe_with_split_distances(params, {2, 5});
    if (shp6.IsNull()) {
      std::cerr << "Error: Failed to create polygonal profile pipe" << std::endl;
    } else {
      test_export_shape(shp6, "./multi_segment_polygonal_pipe.stl");
    }

  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

}
void test_multi_segment_pipe2() {
  std::cout << "\n=== Testing Multi-Segment Pipe With Split Distances ===" << std::endl;
  
  try {
    // 创建路径线段数据，对应Go代码中的wires数据
    std::vector<std::vector<gp_Pnt>> wires = {
        // 第一段：直线段
        {
            gp_Pnt(0.000000, 0.000000, 0.000000),
            gp_Pnt(-18.381608, -16.456729, 23.967570)
        },
        // 第二段：直线段
        {
            gp_Pnt(-18.381608, -16.456729, 23.967570),
            gp_Pnt(-20.049600, -17.830275, 26.141186)
        },
        // 第三段：三点圆弧
        {
            gp_Pnt(-20.049600, -17.830275, 26.141186),
            gp_Pnt(-29.312281, -23.429547, 34.741874),
            gp_Pnt(-55.277435, -31.565721, 41.815130)
        },
        // 第四段：直线段
        {
            gp_Pnt(-55.277435, -31.565721, 41.815130),
            gp_Pnt(-255.585003, -75.656772, 31.748227)
        },
        // 第五段：三点圆弧
        {
            gp_Pnt(-255.585003, -75.656772, 31.748227),
            gp_Pnt(-328.386169, -107.483284, 77.701580),
            gp_Pnt(-331.303108, -111.641479, 87.604189)
        },
        // 第六段：直线段
        {
            gp_Pnt(-331.303108, -111.641479, 87.604189),
            gp_Pnt(-334.263097, -118.631098, 102.370422)
        }
    };

    // 创建多边形剖面数据，对应Go代码中的polygonPoints
    std::vector<gp_Pnt> polygonPoints = {
        gp_Pnt(-3.900000, 4.000000, 0.000000),
        gp_Pnt(-2.652000, 5.403000, 0.000000),
        gp_Pnt(-0.939000, 6.172000, 0.000000),
        gp_Pnt(0.939000, 6.172000, 0.000000),
        gp_Pnt(2.652000, 5.403000, 0.000000),
        gp_Pnt(3.900000, 4.000000, 0.000000),
        gp_Pnt(3.900000, 0.000000, 0.000000),
        gp_Pnt(-3.900000, 0.000000, 0.000000),
        gp_Pnt(-3.900000, 4.000000, 0.000000)
    };

    // 创建剖面数据
    std::vector<shape_profile> profiles;
    // 为每一段创建相同的剖面（6段）
    for (size_t i = 0; i < wires.size(); ++i) {
        profiles.push_back(polygon_profile{polygonPoints});
    }

    // 创建线段类型，对应Go代码中的segmentTypes
    std::vector<segment_type> segmentTypes = {
        segment_type::LINE,              // 第一段：直线
        segment_type::LINE,              // 第二段：直线
        segment_type::THREE_POINT_ARC,   // 第三段：三点圆弧
        segment_type::LINE,              // 第四段：直线
        segment_type::THREE_POINT_ARC,   // 第五段：三点圆弧
        segment_type::LINE               // 第六段：直线
    };

    // 设置过渡模式
    transition_mode transitionMode = transition_mode::TRANSFORMED;

    // 创建上方向向量
    gp_Dir upDir = gp_Vec(-0.301612, 0.874964, 0.378773).Normalized();

    // 构建参数
    multi_segment_pipe_params params;
    params.wires = wires;
    params.profiles = profiles;
    params.segment_types = segmentTypes;
    params.transition_mode = transitionMode;
    params.upDir = upDir;

    // 创建多段管道
    auto shp = create_multi_segment_pipe(params);

    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create multi-segment pipe" << std::endl;
      return;
    }

    // 导出形状以供检查
    test_export_shape(shp, "./test_multi_segment_pipe2.stl");

    std::cout << "Successfully created multi-segment pipe with split distances" << std::endl;
    std::cout << "Segment types used: LINE, LINE, THREE_POINT_ARC, LINE, THREE_POINT_ARC, LINE" << std::endl;

  } catch (const Standard_ConstructionError& e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

void test_multi_segment_pipe3() {
  std::cout << "\n=== Testing Multi-Segment Pipe 3 (Based on TestBug3) ===" << std::endl;
  
  try {
    // 创建路径线段数据，对应Go代码中的wires数据
    std::vector<std::vector<gp_Pnt>> wires = {
        // 第一段：直线段
        {
            gp_Pnt(0.000000, 0.000000, 0.000000),
            gp_Pnt(-35.691625, -32.978268, 46.548679)
        },
        // 第二段：三点圆弧
        {
            gp_Pnt(-35.691625, -32.978268, 46.548679),
            gp_Pnt(-37.229320, -36.179758, 52.584004),
            gp_Pnt(-33.071860, -37.840417, 59.567516)
        },
        // 第三段：直线段
        {
            gp_Pnt(-33.071860, -37.840417, 59.567516),
            gp_Pnt(150.857507, -37.395352, 200.922442)
        }
    };

    // 创建多边形剖面数据
    std::vector<gp_Pnt> polygonPoints = {
        gp_Pnt(-1.500000, 2.100000, 0.000000),
        gp_Pnt(-0.875000, 2.758000, 0.000000),
        gp_Pnt(0.000000, 3.000000, 0.000000),
        gp_Pnt(0.875000, 2.758000, 0.000000),
        gp_Pnt(1.500000, 2.100000, 0.000000),
        gp_Pnt(1.500000, 0.000000, 0.000000),
        gp_Pnt(-1.500000, 0.000000, 0.000000),
        gp_Pnt(-1.500000, 2.100000, 0.000000)
    };

    // 创建剖面
    polygon_profile profile(polygonPoints);
    std::vector<shape_profile> profiles = {profile, profile, profile};

    // 创建线段类型
    std::vector<segment_type> segmentTypes = {
        segment_type::LINE,
        segment_type::THREE_POINT_ARC,
        segment_type::LINE
    };

    // 设置过渡模式
    transition_mode transitionMode = transition_mode::TRANSFORMED;

    // 创建上方向
    gp_Dir upDir(-0.301639, 0.874967, 0.378744);

    // 构建参数
    multi_segment_pipe_params params;
    params.wires = wires;
    params.profiles = profiles;
    params.segment_types = segmentTypes;
    params.transition_mode = transitionMode;
    params.upDir = upDir;

    // 创建多段管道
    auto shp = create_multi_segment_pipe_with_split_distances(params, {67.292182, 83.000373});

    if (shp.IsNull()) {
      std::cerr << "Error: Failed to create multi-segment pipe 3" << std::endl;
      return;
    }

    // 导出形状以供检查
    test_export_shape(shp, "./test_multi_segment_pipe3.stl");

    std::cout << "Successfully created multi-segment pipe 3 based on TestBug3 data" << std::endl;
    std::cout << "Segment types used: LINE, THREE_POINT_ARC, LINE" << std::endl;

    // 67.292182 83.000373
    
  } catch (const Standard_ConstructionError &e) {
    std::cerr << "Construction Error: " << e.GetMessageString() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

int main() {
  // 基础图形
  // test_revol();
  // test_make_prism();
  // test_make_pipe();
  // test_make_multi_segment_pipe();
  // test_make_multi_layer_extrusion_structure();
  // test_make_pipe_joint();
  // test_make_catenary();
  // test_make_box_shape();
  // test_make_cone_shape();
  // test_make_cylinder_shape();
  // test_make_revolution_shape();
  // test_make_sphere_shape();
  // test_make_torus_shape();
  // test_make_wedge_shape();
  // test_make_pipe_shape();
  // // 变电
  // test_make_sphere();
  // test_make_rotational_ellipsoid();
  // test_make_diamond_frustum();
  // test_make_offset_rectangular_table();
  // test_make_cylinder();
  // test_make_sharp_bent_cylinder();
  // test_make_truncated_cone();
  // test_make_eccentric_truncated_cone();
  // test_make_ring();
  // test_make_rectangular_ring();
  // test_make_elliptic_ring();
  // test_make_circular_gasket();
  // test_make_table_gasket();
  // test_make_square_gasket();
  // test_make_stretched_body();
  // test_make_porcelain_bushing();
  // test_make_cone_porcelain_bushing();
  // test_make_insulator_string();
  // test_make_vtype_insulator();
  // test_make_terminal_block();
  // test_make_rectangular_fixed_plate();
  // test_make_circular_fixed_plate();
  // test_make_wire();
  // test_make_cable();
  // test_make_curve_cable();
  // test_make_angle_steel();
  // test_make_i_shaped_steel();
  // test_make_channel_steel();
  // test_make_t_steel();
  // // 输电
  // test_make_bored_pile();
  // test_make_pile_cap();
  // test_make_rock_anchor();
  // test_make_rock_pile_cap();
  // test_make_embedded_rock_anchor();
  // test_make_inclined_rock_anchor();
  // test_make_excavated_base();
  // test_make_step_base();
  // test_make_step_plate_base();
  // test_make_sloped_base_base();
  // test_make_composite_caisson_base();
  // test_make_raft_base();
  // test_make_direct_buried_base();
  // test_make_steel_sleeve_base();
  // test_make_precast_column_base();
  // test_make_precast_pinned_base();
  // test_make_precast_metal_support_base();
  // test_make_precast_concrete_support_base();
  // test_make_transmission_line();
  // test_make_gt_insulator_string();
  // test_make_pole_tower();
  // test_make_single_hook_anchor();
  // test_make_triple_hook_anchor();
  // test_make_ribbed_anchor();
  // test_make_nut_anchor();
  // test_make_triple_arm_anchor();
  // test_make_positioning_plate_anchor();
  // test_make_stub_angle();
  // test_make_stub_tube();
  // // 电缆工程
  // test_make_cable_wire();
  // test_make_cable_joint();
  // test_make_optical_fiber_box();
  // test_make_cable_accessory();
  // test_make_cable_terminal();
  // test_make_cable_clamp();
  // test_make_cable_bracket();
  // test_make_cable_pole();
  // test_make_ground_flat_iron();
  // test_make_embedded_part();
  // test_make_u_shaped_ring();
  // test_make_lifting_eye();
  // test_make_tunnel_well();
  // test_make_corner_well();
  // test_make_three_way_working_well();
  // test_make_three_way_open_cut_tunnel();
  // test_make_three_way_underground_tunnel();
  // test_make_three_way_double_shaft_tunnel();
  // test_make_four_way_working_well();
  // test_make_four_way_open_cut_tunnel();
  // test_make_four_way_underground_tunnel();
  // test_make_pipe_row();
  // test_make_cable_trench();
  // test_make_cable_tunnel();
  // test_make_cable_tray();
  // test_make_cable_L_beam();
  // test_make_manhole();
  // test_make_manhole_cover();
  // test_make_ladder();
  // test_make_sump();
  // test_make_footpath();
  // test_make_shaft_chamber();
  // test_make_tunnel_compartment_partition();
  // test_make_tunnel_partition_board();
  // test_make_ventilation_pavilion();
  // test_make_straight_ventilation_duct();
  // test_make_oblique_ventilation_duct();
  // test_make_drainage_well();
  // test_make_pipe_support();
  // test_make_cover_plate();
  // test_make_cable_ray();
  // 水利工程
  // test_water_tunnel();
  //test_make_wire_from_segments();
  test_multi_segment_pipe2();
  test_multi_segment_pipe3();
  return 0;
}
