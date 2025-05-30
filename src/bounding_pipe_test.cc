#include "bounding_pipe.hh"
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepGProp.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <GProp_GProps.hxx>
#include <GeomAPI_PointsToBSpline.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Line.hxx>
#include <StlAPI_Writer.hxx>
#include <TopExp_Explorer.hxx>

#include <iostream>
#include <memory>
#include <string>

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

void test_fit_centerline_from_shape() {
  std::cout << "Testing fit_centerline_from_shape..." << std::endl;

  // 测试1: 长方体
  {
    std::cout << "\nTest case 1: Box" << std::endl;
    TopoDS_Shape box = BRepPrimAPI_MakeBox(10, 10, 100).Shape();
    Handle(Geom_Curve) curve = fit_centerline_from_shape(box, 10, 3, 0.2);

    if (curve.IsNull()) {
      std::cerr << "Error: Failed to fit centerline for box" << std::endl;
    } else {
      gp_Pnt start = curve->Value(curve->FirstParameter());
      gp_Pnt end = curve->Value(curve->LastParameter());

      std::cout << "Box start: (" << start.X() << ", " << start.Y() << ", "
                << start.Z() << ")" << std::endl;
      std::cout << "Box end: (" << end.X() << ", " << end.Y() << ", " << end.Z()
                << ")" << std::endl;
    }
  }

  // 测试2: 圆弧
  {
    std::cout << "\nTest case 2: Arc" << std::endl;
    // 1. 创建圆弧路径（不是完整圆！）
    gp_Pnt center(0, 0, 0);
    gp_Dir normal(0, 0, 1); // Z轴方向为法向
    gp_Ax2 axis(center, normal);

    // 创建圆弧（90度弧），而不是完整圆
    Handle(Geom_Circle) pathCircle = new Geom_Circle(axis, 50.0);

    // 参数范围：0到π/2（90度弧）
    TopoDS_Edge arc = BRepBuilderAPI_MakeEdge(pathCircle, 0, M_PI_2).Edge();
    TopoDS_Wire pathWire = BRepBuilderAPI_MakeWire(arc).Wire();

    // 2. 创建圆形截面
    // 将截面放置在路径起点
    gp_Pnt startPoint = pathCircle->Value(0);

    // 获取路径在起点的切线方向
    gp_Vec tangent;
    pathCircle->D1(0, startPoint, tangent);
    gp_Dir tangentDir(tangent);

    // 创建截面坐标系：原点在起点，Z轴为切线方向
    gp_Ax2 sectionAxis(startPoint, tangentDir);
    Handle(Geom_Circle) sectionCircle = new Geom_Circle(sectionAxis, 5.0);

    TopoDS_Edge sectionEdge = BRepBuilderAPI_MakeEdge(sectionCircle).Edge();
    TopoDS_Wire sectionWire = BRepBuilderAPI_MakeWire(sectionEdge).Wire();

    // 3. 创建管道体
    BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);

    // 添加截面，并启用对齐
    pipeMaker.Add(sectionWire, Standard_False, Standard_True);

    // 设置生成模式为实体
    pipeMaker.SetMode(Standard_True);                        // 使用Frenet标架
    pipeMaker.SetTransitionMode(BRepBuilderAPI_RightCorner); // 设置过渡模式

    // 构建管道
    pipeMaker.Build();
    if (!pipeMaker.IsDone()) {
      std::cerr << "Error: Failed to create pipe from arc" << std::endl;
      return;
    }

    if (!pipeMaker.MakeSolid()) {
      std::cerr << "Error: Failed to make pipe solid" << std::endl;
      return;
    }

    TopoDS_Shape pipeShape = pipeMaker.Shape();

    exportShapeToStl(pipeShape, "./test_pipe_shape_debug.stl");

    Handle(Geom_Curve) curve = fit_centerline_from_shape(pipeShape, 20);

    if (curve.IsNull()) {
      std::cerr << "Error: Failed to fit centerline for arc" << std::endl;
    } else {
      // 1. 创建圆形截面
      gp_Pnt startPoint = curve->Value(curve->FirstParameter());
      gp_Vec tangent;
      curve->D1(curve->FirstParameter(), startPoint, tangent);
      gp_Ax2 sectionAxis(startPoint, gp_Dir(tangent));
      Handle(Geom_Circle) sectionCircle = new Geom_Circle(sectionAxis, 1.0);
      TopoDS_Edge sectionEdge = BRepBuilderAPI_MakeEdge(sectionCircle).Edge();
      TopoDS_Wire sectionWire = BRepBuilderAPI_MakeWire(sectionEdge).Wire();

      // 2. 创建路径线
      TopoDS_Edge pathEdge = BRepBuilderAPI_MakeEdge(curve).Edge();
      TopoDS_Wire pathWire = BRepBuilderAPI_MakeWire(pathEdge).Wire();

      // 3. 创建管道体
      BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
      pipeMaker.Add(sectionWire, false, true);
      pipeMaker.SetMode(Standard_True);
      pipeMaker.SetTransitionMode(BRepBuilderAPI_Transformed);
      pipeMaker.Build();

      if (!pipeMaker.IsDone()) {
        std::cerr << "Error: Failed to create pipe from centerline"
                  << std::endl;
      } else {

        pipeMaker.MakeSolid();

        // 4. 导出管道体
        TopoDS_Shape newPipeShape = pipeMaker.Shape();

        // BRepAlgoAPI_Fuse _fuse(pipeShape, newPipeShape);

        if (!exportShapeToStl(newPipeShape,
                              "./test_pipe_centerline_pipe.stl")) {
          std::cerr << "Error: Failed to export centerline pipe" << std::endl;
        } else {
          std::cout
              << "Successfully exported centerline pipe to centerline_pipe.stl"
              << std::endl;
        }
      }
    }

    if (curve.IsNull()) {
      std::cerr << "Error: Failed to fit centerline for arc" << std::endl;
    } else {
      // 打印起点、中点和终点
      double first = curve->FirstParameter();
      double last = curve->LastParameter();
      double mid = (first + last) / 2;

      gp_Pnt start = curve->Value(first);
      gp_Pnt middle = curve->Value(mid);
      gp_Pnt end = curve->Value(last);

      std::cout << "Arc start: (" << start.X() << ", " << start.Y() << ", "
                << start.Z() << ")" << std::endl;
      std::cout << "Arc middle: (" << middle.X() << ", " << middle.Y() << ", "
                << middle.Z() << ")" << std::endl;
      std::cout << "Arc end: (" << end.X() << ", " << end.Y() << ", " << end.Z()
                << ")" << std::endl;
    }
  }

  // 测试3: B样条曲线路径
  {
    std::cout << "\nTest case 3: BSpline Curve" << std::endl;

    // 1. 创建B样条曲线路径
    std::vector<gp_Pnt> splinePoints = {gp_Pnt(0, 0, 0), gp_Pnt(20, 10, 30),
                                        gp_Pnt(40, -10, 60), gp_Pnt(60, 15, 90),
                                        gp_Pnt(80, 0, 120)};

    // 转换为TColgp_Array1OfPnt
    TColgp_Array1OfPnt points(1, splinePoints.size());
    for (int i = 0; i < splinePoints.size(); i++) {
      points.SetValue(i + 1, splinePoints[i]);
    }

    // 拟合B样条曲线
    GeomAPI_PointsToBSpline fitter;
    fitter.Init(points, 3, 8);
    Handle(Geom_BSplineCurve) splineCurve = fitter.Curve();
    GeomAdaptor_Curve adaptor(splineCurve);

    // 创建路径线
    TopoDS_Edge splineEdge = BRepBuilderAPI_MakeEdge(adaptor.Curve()).Edge();
    TopoDS_Wire splineWire = BRepBuilderAPI_MakeWire(splineEdge).Wire();

    // 2. 创建圆形截面
    gp_Pnt startPoint = splineCurve->Value(splineCurve->FirstParameter());
    gp_Vec tangent;
    splineCurve->D1(splineCurve->FirstParameter(), startPoint, tangent);
    gp_Ax2 sectionAxis(startPoint, gp_Dir(tangent));
    Handle(Geom_Circle) sectionCircle = new Geom_Circle(sectionAxis, 4.0);
    TopoDS_Edge sectionEdge = BRepBuilderAPI_MakeEdge(sectionCircle).Edge();
    TopoDS_Wire sectionWire = BRepBuilderAPI_MakeWire(sectionEdge).Wire();

    // 3. 创建管道体
    BRepOffsetAPI_MakePipeShell pipeMaker(splineWire);
    pipeMaker.Add(sectionWire, Standard_False, Standard_True);
    pipeMaker.SetTransitionMode(BRepBuilderAPI_Transformed);
    pipeMaker.Build();

    if (!pipeMaker.IsDone()) {
      std::cerr << "Error: Failed to create spline pipe" << std::endl;
      return;
    }

    if (!pipeMaker.MakeSolid()) {
      std::cerr << "Error: Failed to make spline pipe solid" << std::endl;
      return;
    }

    TopoDS_Shape splinePipe = pipeMaker.Shape();
    exportShapeToStl(splinePipe, "./test_spline_pipe.stl");

    // 4. 拟合中心线
    Handle(Geom_Curve) curve = fit_centerline_from_shape(splinePipe, 20);

    if (curve.IsNull()) {
      std::cerr << "Error: Failed to fit centerline for arc" << std::endl;
    } else {
      // 1. 创建圆形截面
      gp_Pnt startPoint = curve->Value(curve->FirstParameter());
      gp_Vec tangent;
      curve->D1(curve->FirstParameter(), startPoint, tangent);
      gp_Ax2 sectionAxis(startPoint, gp_Dir(tangent));
      Handle(Geom_Circle) sectionCircle = new Geom_Circle(sectionAxis, 1.0);
      TopoDS_Edge sectionEdge = BRepBuilderAPI_MakeEdge(sectionCircle).Edge();
      TopoDS_Wire sectionWire = BRepBuilderAPI_MakeWire(sectionEdge).Wire();

      // 2. 创建路径线
      TopoDS_Edge pathEdge = BRepBuilderAPI_MakeEdge(curve).Edge();
      TopoDS_Wire pathWire = BRepBuilderAPI_MakeWire(pathEdge).Wire();

      // 3. 创建管道体
      BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
      pipeMaker.Add(sectionWire, false, true);
      pipeMaker.SetMode(Standard_True);
      pipeMaker.SetTransitionMode(BRepBuilderAPI_Transformed);
      pipeMaker.Build();

      if (!pipeMaker.IsDone()) {
        std::cerr << "Error: Failed to create pipe from centerline"
                  << std::endl;
      } else {

        pipeMaker.MakeSolid();

        // 4. 导出管道体
        TopoDS_Shape newPipeShape = pipeMaker.Shape();

        BRepAlgoAPI_Fuse _fuse(splinePipe, newPipeShape);

        if (!exportShapeToStl(newPipeShape,
                              "./test_pipe_centerline_spline_pipe.stl")) {
          std::cerr << "Error: Failed to export centerline pipe" << std::endl;
        } else {
          std::cout
              << "Successfully exported centerline pipe to centerline_pipe.stl"
              << std::endl;
        }
      }
    }

    if (curve.IsNull()) {
      std::cerr << "Error: Failed to fit centerline for spline pipe"
                << std::endl;
    } else {
      // 打印起点、中点和终点
      double first = curve->FirstParameter();
      double last = curve->LastParameter();
      double mid = (first + last) / 2;

      gp_Pnt start = curve->Value(first);
      gp_Pnt middle = curve->Value(mid);
      gp_Pnt end = curve->Value(last);

      std::cout << "Spline pipe start: (" << start.X() << ", " << start.Y()
                << ", " << start.Z() << ")" << std::endl;
      std::cout << "Spline pipe middle: (" << middle.X() << ", " << middle.Y()
                << ", " << middle.Z() << ")" << std::endl;
      std::cout << "Spline pipe end: (" << end.X() << ", " << end.Y() << ", "
                << end.Z() << ")" << std::endl;
    }
  }
}

void test_extract_path_wire_from_pipe_shape() {
  std::cout << "Testing extract_path_wire_from_pipe_shape..." << std::endl;

  // 1. 创建螺旋线路径
  double radius = 20.0;
  double pitch = 10.0;
  int turns = 2;
  int segments = 50;

  TColgp_Array1OfPnt helixPoints(1, segments);
  for (int i = 1; i <= segments; ++i) {
    double angle = 2 * M_PI * turns * (i - 1) / (segments - 1);
    double x = radius * cos(angle);
    double y = radius * sin(angle);
    double z = pitch * angle / (2 * M_PI);
    helixPoints.SetValue(i, gp_Pnt(x, y, z));
  }

  // 拟合B样条曲线
  GeomAPI_PointsToBSpline fitter;
  fitter.Init(helixPoints, 3, 8);
  Handle(Geom_BSplineCurve) helixCurve = fitter.Curve();
  GeomAdaptor_Curve adaptor(helixCurve);

  // 创建螺旋线路径
  TopoDS_Edge helixEdge = BRepBuilderAPI_MakeEdge(adaptor.Curve()).Edge();
  TopoDS_Wire helixWire = BRepBuilderAPI_MakeWire(helixEdge).Wire();

  // 2. 创建圆形截面
  gp_Pnt startPoint = helixCurve->Value(helixCurve->FirstParameter());
  gp_Vec tangent;
  helixCurve->D1(helixCurve->FirstParameter(), startPoint, tangent);
  gp_Ax2 sectionAxis(startPoint, gp_Dir(tangent));
  Handle(Geom_Circle) sectionCircle = new Geom_Circle(sectionAxis, 3.0);
  TopoDS_Edge sectionEdge = BRepBuilderAPI_MakeEdge(sectionCircle).Edge();
  TopoDS_Wire sectionWire = BRepBuilderAPI_MakeWire(sectionEdge).Wire();

  // 3. 创建管道体
  BRepOffsetAPI_MakePipeShell pipeMaker(helixWire);
  pipeMaker.Add(sectionWire, Standard_False, Standard_True);
  pipeMaker.SetMode(Standard_True);
  pipeMaker.SetTransitionMode(BRepBuilderAPI_RightCorner);
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    std::cerr << "Error: Failed to create helix pipe" << std::endl;
    return;
  }

  if (!pipeMaker.MakeSolid()) {
    std::cerr << "Error: Failed to create helix pipe" << std::endl;
    return;
  }

  TopoDS_Shape helixPipe = pipeMaker.Shape();

  exportShapeToStl(helixPipe, "./test_helix_pipe.stl");

  // 提取路径线
  TopoDS_Wire wire = extract_path_wire_from_pipe_shape(helixPipe);

  if (wire.IsNull()) {
    std::cerr << "Error: Failed to extract path wire" << std::endl;
    return;
  }

  // 遍历Wire中的Edge并打印起点终点
  for (TopExp_Explorer edgeExp(wire, TopAbs_EDGE); edgeExp.More();
       edgeExp.Next()) {
    TopoDS_Edge edge = TopoDS::Edge(edgeExp.Current());

    // 获取曲线参数范围
    Standard_Real first, last;
    Handle(Geom_Curve) curve = BRep_Tool::Curve(edge, first, last);

    if (!curve.IsNull()) {
      gp_Pnt start = curve->Value(first);
      gp_Pnt end = curve->Value(last);

      std::cout << "Edge start: (" << start.X() << ", " << start.Y() << ", "
                << start.Z() << ")" << std::endl;
      for (int i = 1; i <= 10; ++i) {
        double t = first + (last - first) * i / 10;
        gp_Pnt p = curve->Value(t);
        std::cout << "Edge point " << i << ": (" << p.X() << ", " << p.Y()
                  << ", " << p.Z() << ")" << std::endl;
      }

      std::cout << "Edge end: (" << end.X() << ", " << end.Y() << ", "
                << end.Z() << ")" << std::endl;
    } else {
      std::cerr << "Warning: Edge has no curve geometry" << std::endl;
    }
  }

  // 计算路径长度
  GProp_GProps props;
  BRepGProp::LinearProperties(wire, props);
  std::cout << "Path wire length: " << props.Mass() << std::endl;
}

void test_extract_bounding_pipe_from_shape() {
  std::cout << "Testing extract_bounding_pipe_from_shape..." << std::endl;

  // 创建测试管道
  bounding_pipe pipe;
  pipe.centerline = new Geom_Line(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  pipe.sections = {gp_Pnt(0, 0, 0), 1.0, gp_Dir(0, 0, 1)};

  TopoDS_Shape pipeShape = create_bounding_pipe_shape(pipe);

  // 提取边界管道信息
  bounding_pipe result = extract_bounding_pipe_from_shape(pipeShape);

  if (result.centerline.IsNull()) {
    std::cerr << "Error: Failed to extract centerline" << std::endl;
    return;
  }

  std::cout << "First section radius: " << result.sections.radius << std::endl;
}

void test_create_bounding_pipe_shape() {
  std::cout << "Testing create_bounding_pipe_shape..." << std::endl;

  // 创建测试管道定义
  bounding_pipe pipe;
  pipe.centerline = new Geom_Line(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  pipe.sections = {gp_Pnt(0, 0, 0), 1.0, gp_Dir(0, 0, 1)};

  // 创建管道形状
  TopoDS_Shape pipeShape = create_bounding_pipe_shape(pipe);

  if (pipeShape.IsNull()) {
    std::cerr << "Error: Failed to create pipe shape" << std::endl;
    return;
  }

  // 计算体积
  GProp_GProps props;
  BRepGProp::VolumeProperties(pipeShape, props);
  std::cout << "Pipe volume: " << props.Mass() << std::endl;
}

void test_clip_with_bounding_pipe_and_split_distances() {
  std::cout << "Testing clip_with_bounding_pipe_and_split_distances..."
            << std::endl;

  // 创建测试管道
  bounding_pipe pipe;
  pipe.centerline = new Geom_Line(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  pipe.sections = {gp_Pnt(0, 0, 10), 1.0, gp_Dir(0, 0, 1)};

  TopoDS_Shape pipeShape = create_bounding_pipe_shape(pipe);

  // 测试裁剪
  std::array<double, 2> distances = {2.0, 8.0};
  TopoDS_Shape clipped =
      clip_with_bounding_pipe_and_split_distances(pipeShape, pipe, distances);

  if (clipped.IsNull()) {
    std::cerr << "Error: Failed to clip pipe" << std::endl;
    return;
  }

  // 计算裁剪后体积
  GProp_GProps props;
  BRepGProp::VolumeProperties(clipped, props);
  std::cout << "Clipped pipe volume: " << props.Mass() << std::endl;
}

void test_clip_with_bounding_pipe_by_ratios() {
  std::cout << "Testing clip_with_bounding_pipe_by_ratios..." << std::endl;

  // 创建测试管道
  bounding_pipe pipe;
  pipe.centerline = new Geom_Line(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  pipe.sections = {gp_Pnt(0, 0, 10), 1.0, gp_Dir(0, 0, 1)};

  TopoDS_Shape pipeShape = create_bounding_pipe_shape(pipe);

  // 测试按比例裁剪
  std::array<double, 2> ratios = {0.2, 0.8};
  TopoDS_Shape clipped =
      clip_with_bounding_pipe_by_ratios(pipeShape, pipe, ratios);

  if (clipped.IsNull()) {
    std::cerr << "Error: Failed to clip pipe by ratios" << std::endl;
    return;
  }

  // 计算裁剪后体积
  GProp_GProps props;
  BRepGProp::VolumeProperties(clipped, props);
  std::cout << "Clipped pipe volume (by ratios): " << props.Mass() << std::endl;
}

int main() {
  test_fit_centerline_from_shape();
  test_extract_path_wire_from_pipe_shape();
  /**test_extract_bounding_pipe_from_shape();
  test_create_bounding_pipe_shape();
  test_clip_with_bounding_pipe_and_split_distances();
  test_clip_with_bounding_pipe_by_ratios();**/
  return 0;
}
