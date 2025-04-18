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
                      double tolerance = 0.8, double angularTolerance = 0.4) {
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

void test_make_cylinder() {
  std::cout << "\n=== Testing Cylinder ===" << std::endl;
  auto shp = create_cylinder(cylinder_params{.radius = 15, .height = 25});
  if (shp.IsNull()) {
    std::cerr << "Error: Failed to create cylinder" << std::endl;
    return;
  }
  test_export_shape(shp, "./cylinder.stl");
}

/**
 * // 参数验证


 */
void test_make_rotational_ellipsoid() {
  std::cout << "\n=== Testing Rotational Ellipsoid ===" << std::endl;
  try {
    auto shp = create_rotational_ellipsoid(rotational_ellipsoid_params{
        .polarRadius = 7.0,
        .equatorialRadius = 7.0, // 小于极半径
        .height = 7.0           // 等于极半径，生成上半部分
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

int main() {
  test_make_sphere();
  test_make_cylinder();
  test_make_rotational_ellipsoid();
  return 0;
}