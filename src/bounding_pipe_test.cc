#include "bounding_pipe.hh"
#include "shape_ops.hh"

#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Cut.hxx>
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
#include <TopExp.hxx>
#include <Precision.hxx>

#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include <cmath>

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
    Handle(Geom_Curve) curve = fit_centerline_from_shape(box, 10, 0.2);

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
    pipeMaker.SetMode(Standard_True); // 使用Frenet标架
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

        BRepAlgoAPI_Fuse _fuse(pipeShape, newPipeShape);

        if (!exportShapeToStl(_fuse.Shape(),
                              "./test_pipe_centerline_arc_pipe.stl")) {
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

        if (!exportShapeToStl(_fuse.Shape(),
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

  // 复杂曲线测试
  {
    std::cout << "\nTest case 4: Complex BSpline Curve" << std::endl;

    // 1. 创建复杂的B样条曲线路径，使用更多控制点
    std::vector<gp_Pnt> splinePoints = {gp_Pnt(0, 0, 0), gp_Pnt(10, 20, 30),
                                        gp_Pnt(20, 5, 40), gp_Pnt(30, 25, 50)};

    // 转换为TColgp_Array1OfPnt
    TColgp_Array1OfPnt points(1, splinePoints.size());
    for (int i = 0; i < splinePoints.size(); i++) {
      points.SetValue(i + 1, splinePoints[i]);
    }

    // 拟合B样条曲线，提高拟合阶数
    GeomAPI_PointsToBSpline fitter;
    fitter.Init(points, 2, 5); // 提高阶数到 5，最大阶数到 12
    Handle(Geom_BSplineCurve) splineCurve = fitter.Curve();
    if (splineCurve.IsNull()) {
      std::cerr << "Error: Failed to fit complex B-spline curve" << std::endl;
      return;
    }
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
      std::cerr << "Error: Failed to create complex spline pipe" << std::endl;
      return;
    }

    if (!pipeMaker.MakeSolid()) {
      std::cerr << "Error: Failed to make complex spline pipe solid"
                << std::endl;
      return;
    }

    TopoDS_Shape splinePipe = pipeMaker.Shape();
    exportShapeToStl(splinePipe, "./test_complex_spline_pipe.stl");

    // 4. 拟合中心线
    Handle(Geom_Curve) curve = fit_centerline_from_shape(splinePipe, 10, 0.8);

    if (curve.IsNull()) {
      std::cerr << "Error: Failed to fit centerline for complex spline pipe"
                << std::endl;
    } else {
      // 1. 创建圆形截面
      gp_Pnt startPoint = curve->Value(curve->FirstParameter());
      gp_Vec tangent;
      curve->D1(curve->FirstParameter(), startPoint, tangent);
      gp_Ax2 sectionAxis(startPoint, gp_Dir(tangent));
      Handle(Geom_Circle) sectionCircle = new Geom_Circle(sectionAxis, 0.8);
      TopoDS_Edge sectionEdge = BRepBuilderAPI_MakeEdge(sectionCircle).Edge();
      TopoDS_Wire sectionWire2 = BRepBuilderAPI_MakeWire(sectionEdge).Wire();

      // 2. 创建路径线
      TopoDS_Edge pathEdge = BRepBuilderAPI_MakeEdge(curve).Edge();
      TopoDS_Wire pathWire = BRepBuilderAPI_MakeWire(pathEdge).Wire();

      // 3. 创建管道体
      BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
      pipeMaker.Add(sectionWire2, false, true);
      pipeMaker.SetMode(Standard_True);
      pipeMaker.SetTransitionMode(BRepBuilderAPI_Transformed);
      pipeMaker.Build();

      if (!pipeMaker.IsDone()) {
        std::cerr << "Error: Failed to create pipe from complex centerline"
                  << std::endl;
      } else {
        pipeMaker.MakeSolid();

        // 4. 导出管道体
        TopoDS_Shape newPipeShape = pipeMaker.Shape();

        BRepAlgoAPI_Fuse _fuse(splinePipe, newPipeShape);

        if (!exportShapeToStl(
                _fuse.Shape(),
                "./test_pipe_centerline_complex_spline_pipe.stl")) {
          std::cerr << "Error: Failed to export complex centerline pipe"
                    << std::endl;
        } else {
          std::cout << "Successfully exported complex centerline pipe to "
                       "centerline_pipe.stl"
                    << std::endl;
        }
      }
    }

    if (curve.IsNull()) {
      std::cerr << "Error: Failed to fit centerline for complex spline pipe"
                << std::endl;
    } else {
      // 打印起点、中点和终点
      double first = curve->FirstParameter();
      double last = curve->LastParameter();
      double mid = (first + last) / 2;

      gp_Pnt start = curve->Value(first);
      gp_Pnt middle = curve->Value(mid);
      gp_Pnt end = curve->Value(last);

      std::cout << "Complex spline pipe start: (" << start.X() << ", "
                << start.Y() << ", " << start.Z() << ")" << std::endl;
      std::cout << "Complex spline pipe middle: (" << middle.X() << ", "
                << middle.Y() << ", " << middle.Z() << ")" << std::endl;
      std::cout << "Complex spline pipe end: (" << end.X() << ", " << end.Y()
                << ", " << end.Z() << ")" << std::endl;
    }
  }

  // 测试5: 曲线+直线组成的复合线段
  {
    std::cout << "\nTest case 5: Composite Curve (Arc + Line)" << std::endl;

    // 1. 创建复合路径（圆弧+直线）
    gp_Pnt arc_center(0, 0, 0);
    gp_Dir normal(0, 0, 1);
    gp_Ax2 axis(arc_center, normal);

    // 创建圆弧（90度弧）
    Handle(Geom_Circle) arcCircle = new Geom_Circle(axis, 50.0);
    TopoDS_Edge arcEdge = BRepBuilderAPI_MakeEdge(arcCircle, 0, M_PI_2).Edge();

    // 创建直线（从圆弧终点开始沿Z轴延伸）
    gp_Pnt arc_end = arcCircle->Value(M_PI_2);
    gp_Vec atangent;
    arcCircle->D1(M_PI_2, arc_end, atangent); // 获取圆弧终点的切线方向
    gp_Dir atangentDir(atangent);             // 转换为方向向量
    gp_Pnt line_end =
        arc_end.Translated(gp_Vec(atangentDir).Multiplied(100)); // 沿切线方向延伸100单位
    Handle(Geom_Line) line = new Geom_Line(arc_end, atangentDir);
    TopoDS_Edge lineEdge =
        BRepBuilderAPI_MakeEdge(line, arc_end, line_end).Edge();

    // 组合成复合路径
    BRepBuilderAPI_MakeWire wireMaker;
    wireMaker.Add(arcEdge);
    wireMaker.Add(lineEdge);
    TopoDS_Wire pathWire = wireMaker.Wire();

    // 2. 创建圆形截面
    gp_Pnt startPoint = arcCircle->Value(0);
    gp_Vec tangent;
    arcCircle->D1(0, startPoint, tangent);
    gp_Dir tangentDir(tangent);
    gp_Ax2 sectionAxis(startPoint, tangentDir);
    Handle(Geom_Circle) sectionCircle = new Geom_Circle(sectionAxis, 5.0);
    TopoDS_Edge sectionEdge = BRepBuilderAPI_MakeEdge(sectionCircle).Edge();
    TopoDS_Wire sectionWire = BRepBuilderAPI_MakeWire(sectionEdge).Wire();

    // 3. 创建管道体
    BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
    pipeMaker.Add(sectionWire, Standard_False, Standard_True);
    pipeMaker.SetMode(Standard_True);
    pipeMaker.SetTransitionMode(BRepBuilderAPI_Transformed);
    pipeMaker.Build();

    if (!pipeMaker.IsDone()) {
      std::cerr << "Error: Failed to create composite pipe" << std::endl;
      return;
    }

    if (!pipeMaker.MakeSolid()) {
      std::cerr << "Error: Failed to make composite pipe solid" << std::endl;
      return;
    }

    TopoDS_Shape pipeShape = pipeMaker.Shape();
    exportShapeToStl(pipeShape, "./test_arc_line_pipe.stl");

    // 4. 拟合中心线
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

        BRepAlgoAPI_Fuse _fuse(pipeShape, newPipeShape);

        if (!exportShapeToStl(_fuse.Shape(),
                              "./test_pipe_centerline_arc_line_pipe.stl")) {
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

void test_clip_with_bounding_pipe_by_ratios() {
  std::cout << "Testing clip_with_bounding_pipe_by_ratios..." << std::endl;

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
    pipeMaker.SetMode(Standard_True); // 使用Frenet标架
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

    // 创建测试管道
    bounding_pipe pipe =
        extract_bounding_pipe_from_shape(pipeShape, nullptr, 100);

    // 测试按比例裁剪
    std::array<double, 2> ratios = {0.2, 0.8};
    TopoDS_Shape clipped =
        clip_with_bounding_pipe_by_ratios(pipeShape, pipe, ratios);

    if (clipped.IsNull()) {
      std::cerr << "Error: Failed to clip pipe by ratios" << std::endl;
      return;
    }

    exportShapeToStl(clipped, "./test_arc_clipped_pipe.stl");

    // 计算裁剪后体积
    GProp_GProps props;
    BRepGProp::VolumeProperties(clipped, props);
    std::cout << "Clipped pipe volume (by ratios): " << props.Mass()
              << std::endl;
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

    // 创建测试管道
    bounding_pipe pipe =
        extract_bounding_pipe_from_shape(splinePipe, nullptr, 100);

    // 测试按比例裁剪
    std::array<double, 2> ratios = {0.2, 0.8};
    TopoDS_Shape clipped =
        clip_with_bounding_pipe_by_ratios(splinePipe, pipe, ratios);

    if (clipped.IsNull()) {
      std::cerr << "Error: Failed to clip pipe by ratios" << std::endl;
      return;
    }

    exportShapeToStl(clipped, "./test_spline_clipped_spline_pipe.stl");

    // 计算裁剪后体积
    GProp_GProps props;
    BRepGProp::VolumeProperties(clipped, props);
    std::cout << "Clipped pipe volume (by ratios): " << props.Mass()
              << std::endl;
  }

  // 复杂曲线测试
  {
    std::cout << "\nTest case 4: Complex BSpline Curve" << std::endl;

    // 1. 创建复杂的B样条曲线路径，使用更多控制点
    std::vector<gp_Pnt> splinePoints = {gp_Pnt(0, 0, 0), gp_Pnt(10, 20, 30),
                                        gp_Pnt(20, 5, 40), gp_Pnt(30, 25, 50)};

    // 转换为TColgp_Array1OfPnt
    TColgp_Array1OfPnt points(1, splinePoints.size());
    for (int i = 0; i < splinePoints.size(); i++) {
      points.SetValue(i + 1, splinePoints[i]);
    }

    // 拟合B样条曲线，提高拟合阶数
    GeomAPI_PointsToBSpline fitter;
    fitter.Init(points, 2, 5); // 提高阶数到 5，最大阶数到 12
    Handle(Geom_BSplineCurve) splineCurve = fitter.Curve();
    if (splineCurve.IsNull()) {
      std::cerr << "Error: Failed to fit complex B-spline curve" << std::endl;
      return;
    }
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
      std::cerr << "Error: Failed to create complex spline pipe" << std::endl;
      return;
    }

    if (!pipeMaker.MakeSolid()) {
      std::cerr << "Error: Failed to make complex spline pipe solid"
                << std::endl;
      return;
    }

    TopoDS_Shape splinePipe = pipeMaker.Shape();

    // 创建测试管道
    bounding_pipe pipe =
        extract_bounding_pipe_from_shape(splinePipe, nullptr, 100);

    // 测试按比例裁剪
    std::array<double, 2> ratios = {0.2, 0.4};
    TopoDS_Shape clipped =
        clip_with_bounding_pipe_by_ratios(splinePipe, pipe, ratios);

    if (clipped.IsNull()) {
      std::cerr << "Error: Failed to clip pipe by ratios" << std::endl;
      return;
    }

    exportShapeToStl(clipped, "./test_complex_spline_clipped_pipe.stl");

    // 计算裁剪后体积
    GProp_GProps props;
    BRepGProp::VolumeProperties(clipped, props);
    std::cout << "Clipped pipe volume (by ratios): " << props.Mass()
              << std::endl;
  }

  // 测试5: 曲线+直线组成的复合线段
  {
    std::cout << "\nTest case 5: Composite Curve (Arc + Line)" << std::endl;

    // 1. 创建复合路径（圆弧+直线）
    gp_Pnt arc_center(0, 0, 0);
    gp_Dir normal(0, 0, 1);
    gp_Ax2 axis(arc_center, normal);

    // 创建圆弧（90度弧）
    Handle(Geom_Circle) arcCircle = new Geom_Circle(axis, 50.0);
    TopoDS_Edge arcEdge = BRepBuilderAPI_MakeEdge(arcCircle, 0, M_PI_2).Edge();

    // 创建直线（从圆弧终点开始沿Z轴延伸）
    gp_Pnt arc_end = arcCircle->Value(M_PI_2);
    gp_Vec atangent;
    arcCircle->D1(M_PI_2, arc_end, atangent); // 获取圆弧终点的切线方向
    gp_Dir atangentDir(atangent);             // 转换为方向向量
    gp_Pnt line_end =
        arc_end.Translated(gp_Vec(atangentDir).Multiplied(100)); // 沿切线方向延伸100单位
    Handle(Geom_Line) line = new Geom_Line(arc_end, atangentDir);
    TopoDS_Edge lineEdge =
        BRepBuilderAPI_MakeEdge(line, arc_end, line_end).Edge();

    // 组合成复合路径
    BRepBuilderAPI_MakeWire wireMaker;
    wireMaker.Add(arcEdge);
    wireMaker.Add(lineEdge);
    TopoDS_Wire pathWire = wireMaker.Wire();

    // 2. 创建圆形截面
    gp_Pnt startPoint = arcCircle->Value(0);
    gp_Vec tangent;
    arcCircle->D1(0, startPoint, tangent);
    gp_Dir tangentDir(tangent);
    gp_Ax2 sectionAxis(startPoint, tangentDir);
    Handle(Geom_Circle) sectionCircle = new Geom_Circle(sectionAxis, 5.0);
    TopoDS_Edge sectionEdge = BRepBuilderAPI_MakeEdge(sectionCircle).Edge();
    TopoDS_Wire sectionWire = BRepBuilderAPI_MakeWire(sectionEdge).Wire();

    // 3. 创建管道体
    BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
    pipeMaker.Add(sectionWire, Standard_False, Standard_True);
    pipeMaker.SetMode(Standard_True);
    pipeMaker.SetTransitionMode(BRepBuilderAPI_Transformed);
    pipeMaker.Build();

    if (!pipeMaker.IsDone()) {
      std::cerr << "Error: Failed to create composite pipe" << std::endl;
      return;
    }

    if (!pipeMaker.MakeSolid()) {
      std::cerr << "Error: Failed to make composite pipe solid" << std::endl;
      return;
    }

    TopoDS_Shape pipeShape = pipeMaker.Shape();

    exportShapeToStl(pipeShape, "./test_composite_pipeShape_pipe.stl");

    // 4. 创建测试管道
    bounding_pipe pipe =
        extract_bounding_pipe_from_shape(pipeShape, nullptr, 20);

    // 5. 测试按比例裁剪
    std::array<double, 2> ratios = {0.3, 0.7};
    TopoDS_Shape clipped =
        clip_with_bounding_pipe_by_ratios(pipeShape, pipe, ratios);

    if (clipped.IsNull()) {
      std::cerr << "Error: Failed to clip composite pipe by ratios"
                << std::endl;
      return;
    }

    exportShapeToStl(clipped, "./test_composite_clipped_pipe.stl");

    // 6. 计算裁剪后体积
    GProp_GProps props;
    BRepGProp::VolumeProperties(clipped, props);
    std::cout << "Clipped composite pipe volume (by ratios): " << props.Mass()
              << std::endl;
  }
}

void test_sample_centerline_wire() {
  std::cout << "Testing sample_centerline_wire..." << std::endl;

  // 测试1: 圆弧中心线
  {
    std::cout << "\nTest case 1: Arc centerline" << std::endl;
    
    // 1. 创建圆弧路径
    gp_Pnt center(0, 0, 0);
    gp_Dir normal(0, 0, 1); // Z轴方向为法向
    gp_Ax2 axis(center, normal);

    // 创建圆弧（90度弧）
    Handle(Geom_Circle) pathCircle = new Geom_Circle(axis, 50.0);
    TopoDS_Edge arc = BRepBuilderAPI_MakeEdge(pathCircle, 0, M_PI_2).Edge();
    TopoDS_Wire pathWire = BRepBuilderAPI_MakeWire(arc).Wire();

    // 2. 创建topo::wire对象
    flywave::topo::wire centerlineWire(pathWire);
    
    // 3. 采样中心线
    try {
      std::vector<gp_Pnt> points = sample_centerline_wire(centerlineWire, 50);
      
      std::cout << "Sampled " << points.size() << " points from arc centerline" << std::endl;
      
      // 验证采样点的数量
      if (points.size() != 50) {
        std::cerr << "Warning: Expected 50 points, got " << points.size() << std::endl;
      }
      
      // 检查是否有inf或nan值
      bool hasInvalidValues = false;
      for (const auto& point : points) {
        if (!std::isfinite(point.X()) || !std::isfinite(point.Y()) || !std::isfinite(point.Z())) {
          std::cerr << "Error: Found inf/nan values in sampled points" << std::endl;
          hasInvalidValues = true;
          break;
        }
      }
      
      if (!hasInvalidValues) {
        std::cout << "All sampled points are valid (no inf/nan values)" << std::endl;
      }
      
      // 打印前几个和后几个点的坐标
      std::cout << "First 3 points:" << std::endl;
      for (int i = 0; i < std::min(3, (int)points.size()); i++) {
        std::cout << "  Point " << i << ": (" << points[i].X() << ", " 
                  << points[i].Y() << ", " << points[i].Z() << ")" << std::endl;
      }
      
      std::cout << "Last 3 points:" << std::endl;
      int startIdx = std::max(0, (int)points.size() - 3);
      for (int i = startIdx; i < (int)points.size(); i++) {
        std::cout << "  Point " << i << ": (" << points[i].X() << ", " 
                  << points[i].Y() << ", " << points[i].Z() << ")" << std::endl;
      }
    } catch (const std::exception& e) {
      std::cerr << "Error sampling arc centerline: " << e.what() << std::endl;
    }
  }

  // 测试2: B样条曲线中心线
  {
    std::cout << "\nTest case 2: BSpline centerline" << std::endl;
    
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

    // 2. 创建topo::wire对象
    flywave::topo::wire centerlineWire(splineWire);
    
    // 3. 采样中心线
    try {
      std::vector<gp_Pnt> points = sample_centerline_wire(centerlineWire, 100);
      
      std::cout << "Sampled " << points.size() << " points from BSpline centerline" << std::endl;
      
      // 验证采样点的数量
      if (points.size() != 100) {
        std::cerr << "Warning: Expected 100 points, got " << points.size() << std::endl;
      }
      
      // 检查是否有inf或nan值
      bool hasInvalidValues = false;
      for (const auto& point : points) {
        if (!std::isfinite(point.X()) || !std::isfinite(point.Y()) || !std::isfinite(point.Z())) {
          std::cerr << "Error: Found inf/nan values in sampled points" << std::endl;
          hasInvalidValues = true;
          break;
        }
      }
      
      if (!hasInvalidValues) {
        std::cout << "All sampled points are valid (no inf/nan values)" << std::endl;
      }
      
      // 打印前几个和后几个点的坐标
      std::cout << "First 3 points:" << std::endl;
      for (int i = 0; i < std::min(3, (int)points.size()); i++) {
        std::cout << "  Point " << i << ": (" << points[i].X() << ", " 
                  << points[i].Y() << ", " << points[i].Z() << ")" << std::endl;
      }
      
      std::cout << "Last 3 points:" << std::endl;
      int startIdx = std::max(0, (int)points.size() - 3);
      for (int i = startIdx; i < (int)points.size(); i++) {
        std::cout << "  Point " << i << ": (" << points[i].X() << ", " 
                  << points[i].Y() << ", " << points[i].Z() << ")" << std::endl;
      }
    } catch (const std::exception& e) {
      std::cerr << "Error sampling BSpline centerline: " << e.what() << std::endl;
    }
  }

  // 测试3: 复合曲线中心线（圆弧+直线）
  {
    std::cout << "\nTest case 3: Composite curve centerline (Arc + Line)" << std::endl;
    
    // 1. 创建复合路径（圆弧+直线）
    gp_Pnt arc_center(0, 0, 0);
    gp_Dir normal(0, 0, 1);
    gp_Ax2 axis(arc_center, normal);

    // 创建圆弧（90度弧）
    Handle(Geom_Circle) arcCircle = new Geom_Circle(axis, 50.0);
    TopoDS_Edge arcEdge = BRepBuilderAPI_MakeEdge(arcCircle, 0, M_PI_2).Edge();

    // 创建直线（从圆弧终点开始沿Z轴延伸）
    gp_Pnt arc_end = arcCircle->Value(M_PI_2);
    gp_Vec atangent;
    arcCircle->D1(M_PI_2, arc_end, atangent); // 获取圆弧终点的切线方向
    gp_Dir atangentDir(atangent);             // 转换为方向向量
    gp_Pnt line_end =
        arc_end.Translated(gp_Vec(atangentDir).Multiplied(100)); // 沿切线方向延伸100单位
    Handle(Geom_Line) line = new Geom_Line(arc_end, atangentDir);
    TopoDS_Edge lineEdge =
        BRepBuilderAPI_MakeEdge(line, arc_end, line_end).Edge();

    // 组合成复合路径
    BRepBuilderAPI_MakeWire wireMaker;
    wireMaker.Add(arcEdge);
    wireMaker.Add(lineEdge);
    TopoDS_Wire pathWire = wireMaker.Wire();

    // 2. 创建topo::wire对象
    flywave::topo::wire centerlineWire(pathWire);
    
    // 3. 采样中心线
    try {
      std::vector<gp_Pnt> points = sample_centerline_wire(centerlineWire, 80);
      
      std::cout << "Sampled " << points.size() << " points from composite centerline" << std::endl;
      
      // 验证采样点的数量
      if (points.size() != 80) {
        std::cerr << "Warning: Expected 80 points, got " << points.size() << std::endl;
      }
      
      // 检查是否有inf或nan值
      bool hasInvalidValues = false;
      for (const auto& point : points) {
        if (!std::isfinite(point.X()) || !std::isfinite(point.Y()) || !std::isfinite(point.Z())) {
          std::cerr << "Error: Found inf/nan values in sampled points" << std::endl;
          hasInvalidValues = true;
          break;
        }
      }
      
      if (!hasInvalidValues) {
        std::cout << "All sampled points are valid (no inf/nan values)" << std::endl;
      }
      
      // 打印前几个和后几个点的坐标
      std::cout << "First 3 points:" << std::endl;
      for (int i = 0; i < std::min(3, (int)points.size()); i++) {
        std::cout << "  Point " << i << ": (" << points[i].X() << ", " 
                  << points[i].Y() << ", " << points[i].Z() << ")" << std::endl;
      }
      
      std::cout << "Last 3 points:" << std::endl;
      int startIdx = std::max(0, (int)points.size() - 3);
      for (int i = startIdx; i < (int)points.size(); i++) {
        std::cout << "  Point " << i << ": (" << points[i].X() << ", " 
                  << points[i].Y() << ", " << points[i].Z() << ")" << std::endl;
      }
    } catch (const std::exception& e) {
      std::cerr << "Error sampling composite centerline: " << e.what() << std::endl;
    }
  }

  // 测试4: 简化采样
  {
    std::cout << "\nTest case 4: Simplified sampling" << std::endl;
    
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

    // 2. 创建topo::wire对象
    flywave::topo::wire centerlineWire(splineWire);
    
    // 3. 使用简化模式采样中心线
    try {
      std::vector<gp_Pnt> points = sample_centerline_wire(centerlineWire, 50, true);
      
      std::cout << "Sampled " << points.size() << " points from BSpline centerline (simplified)" << std::endl;
      
      // 验证采样点的数量
      if (points.size() != 50) {
        std::cerr << "Warning: Expected 50 points, got " << points.size() << std::endl;
      }
      
      // 检查是否有inf或nan值
      bool hasInvalidValues = false;
      for (const auto& point : points) {
        if (!std::isfinite(point.X()) || !std::isfinite(point.Y()) || !std::isfinite(point.Z())) {
          std::cerr << "Error: Found inf/nan values in sampled points" << std::endl;
          hasInvalidValues = true;
          break;
        }
      }
      
      if (!hasInvalidValues) {
        std::cout << "All sampled points are valid (no inf/nan values)" << std::endl;
      }
      
      // 打印前几个和后几个点的坐标
      std::cout << "First 3 points:" << std::endl;
      for (int i = 0; i < std::min(3, (int)points.size()); i++) {
        std::cout << "  Point " << i << ": (" << points[i].X() << ", " 
                  << points[i].Y() << ", " << points[i].Z() << ")" << std::endl;
      }
      
      std::cout << "Last 3 points:" << std::endl;
      int startIdx = std::max(0, (int)points.size() - 3);
      for (int i = startIdx; i < (int)points.size(); i++) {
        std::cout << "  Point " << i << ": (" << points[i].X() << ", " 
                  << points[i].Y() << ", " << points[i].Z() << ")" << std::endl;
      }
    } catch (const std::exception& e) {
      std::cerr << "Error sampling BSpline centerline with simplification: " << e.what() << std::endl;
    }
  }

  // 测试5: 检查最后一个点是否为inf的特殊情况
  {
    std::cout << "\nTest case 5: Check for inf values in last point" << std::endl;
    
    // 1. 创建一个简单的直线路径
    gp_Pnt start(0, 0, 0);
    gp_Pnt end(100, 0, 0);
    Handle(Geom_Line) line = new Geom_Line(start, gp_Dir(gp_Vec(start, end)));
    TopoDS_Edge lineEdge = BRepBuilderAPI_MakeEdge(line, start, end).Edge();
    TopoDS_Wire lineWire = BRepBuilderAPI_MakeWire(lineEdge).Wire();

    // 2. 创建topo::wire对象
    flywave::topo::wire centerlineWire(lineWire);
    
    // 3. 采样中心线，使用不同的采样点数进行测试
    std::vector<int> sampleCounts = {10, 50, 100, 200};
    
    for (int numSamples : sampleCounts) {
      try {
        std::cout << "Testing with " << numSamples << " samples..." << std::endl;
        std::vector<gp_Pnt> points = sample_centerline_wire(centerlineWire, numSamples);
        
        // 检查最后一个点是否为inf
        if (!points.empty()) {
          const gp_Pnt& lastPoint = points.back();
          if (!std::isfinite(lastPoint.X()) || !std::isfinite(lastPoint.Y()) || !std::isfinite(lastPoint.Z())) {
            std::cerr << "Error: Last point is inf/nan: (" << lastPoint.X() << ", " 
                      << lastPoint.Y() << ", " << lastPoint.Z() << ")" << std::endl;
          } else {
            std::cout << "Last point is valid: (" << lastPoint.X() << ", " 
                      << lastPoint.Y() << ", " << lastPoint.Z() << ")" << std::endl;
          }
        }
      } catch (const std::exception& e) {
        std::cerr << "Error sampling line centerline with " << numSamples << " samples: " << e.what() << std::endl;
      }
    }
  }
}

// 测试 sample_centerline_wire 函数（根据Go测试方法）
void test_sample_centerline_wire_go_style() {
  std::cout << "Testing sample_centerline_wire (Go style)..." << std::endl;

  // 测试1: 单边线框（直线）
  {
    std::cout << "\nTest case 1: Single edge wire (straight line)" << std::endl;
    
    // 创建测试用的线框形状
    gp_Pnt p1(0, 0, 0);
    gp_Pnt p2(100, 0, 0);

    // 创建边和线框
    TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(p1, p2).Edge();
    if (edge.IsNull()) {
      std::cerr << "Failed to create edge" << std::endl;
      return;
    }

    TopoDS_Wire wire = BRepBuilderAPI_MakeWire(edge).Wire();
    if (wire.IsNull()) {
      std::cerr << "Failed to create wire" << std::endl;
      return;
    }

    flywave::topo::wire topoWire(wire);

    // 测试不同的采样点数
    std::vector<int> sampleCounts = {10, 50, 100, 200};

    for (int numSamples : sampleCounts) {
      std::cout << "\nTesting with " << numSamples << " samples" << std::endl;
      
      try {
        std::vector<gp_Pnt> points = sample_centerline_wire(topoWire, numSamples, false);

        // 检查返回值是否为空
        if (points.empty()) {
          std::cerr << "sample_centerline_wire returned empty for " << numSamples << " samples" << std::endl;
          continue;
        }

        // 检查点数是否正确
        if ((int)points.size() != numSamples) {
          std::cerr << "Expected " << numSamples << " points, got " << points.size() << std::endl;
        }

        // 检查是否有inf或nan值
        bool hasInvalidValues = false;
        for (size_t i = 0; i < points.size(); i++) {
          const gp_Pnt& point = points[i];
          if (std::isinf(point.X()) || std::isnan(point.X()) ||
              std::isinf(point.Y()) || std::isnan(point.Y()) ||
              std::isinf(point.Z()) || std::isnan(point.Z())) {
            std::cerr << "Found inf/nan values at point " << i << ": (" 
                      << point.X() << ", " << point.Y() << ", " << point.Z() << ")" << std::endl;
            hasInvalidValues = true;
          }
        }

        if (!hasInvalidValues) {
          std::cout << "All " << points.size() << " sampled points are valid (no inf/nan values)" << std::endl;
        }

        // 特别检查第一个和最后一个点
        if (!points.empty()) {
          const gp_Pnt& firstPoint = points[0];
          const gp_Pnt& lastPoint = points[points.size() - 1];

          std::cout << "First point: (" << firstPoint.X() << ", " << firstPoint.Y() << ", " << firstPoint.Z() << ")" << std::endl;
          std::cout << "Last point: (" << lastPoint.X() << ", " << lastPoint.Y() << ", " << lastPoint.Z() << ")" << std::endl;

          // 验证端点是否正确
          if (!firstPoint.IsEqual(p1, Precision::Confusion())) {
            std::cerr << "First point doesn't match expected start point" << std::endl;
          }
          
          if (!lastPoint.IsEqual(p2, Precision::Confusion())) {
            std::cerr << "Last point doesn't match expected end point" << std::endl;
          }

          // 检查最后一个点是否为inf
          if (std::isinf(lastPoint.X()) || std::isnan(lastPoint.X()) ||
              std::isinf(lastPoint.Y()) || std::isnan(lastPoint.Y()) ||
              std::isinf(lastPoint.Z()) || std::isnan(lastPoint.Z())) {
            std::cerr << "Last point is inf/nan: (" << lastPoint.X() << ", " 
                      << lastPoint.Y() << ", " << lastPoint.Z() << ")" << std::endl;
          }
        }
      } catch (const std::exception& e) {
        std::cerr << "Exception occurred with " << numSamples << " samples: " << e.what() << std::endl;
      }
    }
  }

  // 测试2: 多边线框（两段线）
  {
    std::cout << "\nTest case 2: Multi-edge wire (two segments)" << std::endl;
    
    // 创建测试用的线框形状（两段线）
    gp_Pnt p1(0, 0, 0);
    gp_Pnt p2(50, 0, 0);
    gp_Pnt p3(100, 30, 0);

    // 创建边
    TopoDS_Edge edge1 = BRepBuilderAPI_MakeEdge(p1, p2).Edge();
    TopoDS_Edge edge2 = BRepBuilderAPI_MakeEdge(p2, p3).Edge();
    
    if (edge1.IsNull() || edge2.IsNull()) {
      std::cerr << "Failed to create edges" << std::endl;
      return;
    }

    // 创建线框
    BRepBuilderAPI_MakeWire wireMaker;
    wireMaker.Add(edge1);
    wireMaker.Add(edge2);
    TopoDS_Wire wire = wireMaker.Wire();
    
    if (wire.IsNull()) {
      std::cerr << "Failed to create wire" << std::endl;
      return;
    }

    flywave::topo::wire topoWire(wire);

    // 测试不同的采样点数
    std::vector<int> sampleCounts = {10, 50, 100};

    for (int numSamples : sampleCounts) {
      std::cout << "\nTesting with " << numSamples << " samples" << std::endl;
      
      try {
        std::vector<gp_Pnt> points = sample_centerline_wire(topoWire, numSamples, false);

        // 检查返回值是否为空
        if (points.empty()) {
          std::cerr << "sample_centerline_wire returned empty for " << numSamples << " samples" << std::endl;
          continue;
        }

        // 检查点数是否正确
        if ((int)points.size() != numSamples) {
          std::cerr << "Expected " << numSamples << " points, got " << points.size() << std::endl;
        }

        // 检查是否有inf或nan值
        bool hasInvalidValues = false;
        for (size_t i = 0; i < points.size(); i++) {
          const gp_Pnt& point = points[i];
          if (std::isinf(point.X()) || std::isnan(point.X()) ||
              std::isinf(point.Y()) || std::isnan(point.Y()) ||
              std::isinf(point.Z()) || std::isnan(point.Z())) {
            std::cerr << "Found inf/nan values at point " << i << ": (" 
                      << point.X() << ", " << point.Y() << ", " << point.Z() << ")" << std::endl;
            hasInvalidValues = true;
          }
        }

        if (!hasInvalidValues) {
          std::cout << "All " << points.size() << " sampled points are valid (no inf/nan values)" << std::endl;
        }

        // 特别检查第一个和最后一个点
        if (!points.empty()) {
          const gp_Pnt& firstPoint = points[0];
          const gp_Pnt& lastPoint = points[points.size() - 1];

          std::cout << "First point: (" << firstPoint.X() << ", " << firstPoint.Y() << ", " << firstPoint.Z() << ")" << std::endl;
          std::cout << "Last point: (" << lastPoint.X() << ", " << lastPoint.Y() << ", " << lastPoint.Z() << ")" << std::endl;

          // 验证端点是否正确
          if (!firstPoint.IsEqual(p1, Precision::Confusion())) {
            std::cerr << "First point doesn't match expected start point" << std::endl;
          }
          
          if (!lastPoint.IsEqual(p3, Precision::Confusion())) {
            std::cerr << "Last point doesn't match expected end point" << std::endl;
          }

          // 检查最后一个点是否为inf
          if (std::isinf(lastPoint.X()) || std::isnan(lastPoint.X()) ||
              std::isinf(lastPoint.Y()) || std::isnan(lastPoint.Y()) ||
              std::isinf(lastPoint.Z()) || std::isnan(lastPoint.Z())) {
            std::cerr << "Last point is inf/nan: (" << lastPoint.X() << ", " 
                      << lastPoint.Y() << ", " << lastPoint.Z() << ")" << std::endl;
          }
        }
      } catch (const std::exception& e) {
        std::cerr << "Exception occurred with " << numSamples << " samples: " << e.what() << std::endl;
      }
    }
  }

  // 测试简化模式
  std::cout << "\nTesting simplify mode" << std::endl;
  {
    gp_Pnt p1(0, 0, 0);
    gp_Pnt p2(100, 0, 0);
    TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(p1, p2).Edge();
    TopoDS_Wire wire = BRepBuilderAPI_MakeWire(edge).Wire();
    flywave::topo::wire topoWire(wire);
    
    try {
      std::vector<gp_Pnt> points = sample_centerline_wire(topoWire, 50, true);

      // 检查返回值是否为空
      if (points.empty()) {
        std::cerr << "sample_centerline_wire with simplify returned empty" << std::endl;
        return;
      }

      // 检查是否有inf或nan值
      bool hasInvalidValues = false;
      for (size_t i = 0; i < points.size(); i++) {
        const gp_Pnt& point = points[i];
        if (std::isinf(point.X()) || std::isnan(point.X()) ||
            std::isinf(point.Y()) || std::isnan(point.Y()) ||
            std::isinf(point.Z()) || std::isnan(point.Z())) {
          std::cerr << "Found inf/nan values at point " << i << ": (" 
                    << point.X() << ", " << point.Y() << ", " << point.Z() << ")" << std::endl;
          hasInvalidValues = true;
        }
      }

      if (!hasInvalidValues) {
        std::cout << "All " << points.size() << " sampled points with simplify are valid (no inf/nan values)" << std::endl;
      }

      // 特别检查最后一个点
      if (!points.empty()) {
        const gp_Pnt& lastPoint = points[points.size() - 1];
        
        if (std::isinf(lastPoint.X()) || std::isnan(lastPoint.X()) ||
            std::isinf(lastPoint.Y()) || std::isnan(lastPoint.Y()) ||
            std::isinf(lastPoint.Z()) || std::isnan(lastPoint.Z())) {
          std::cerr << "Last point with simplify is inf/nan: (" << lastPoint.X() << ", " 
                    << lastPoint.Y() << ", " << lastPoint.Z() << ")" << std::endl;
        }
      }
    } catch (const std::exception& e) {
      std::cerr << "Exception occurred in simplify mode: " << e.what() << std::endl;
    }
  }

  // 测试边界情况：0采样点数
  std::cout << "\nTesting zero sample count" << std::endl;
  {
    gp_Pnt p1(0, 0, 0);
    gp_Pnt p2(100, 0, 0);
    TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(p1, p2).Edge();
    TopoDS_Wire wire = BRepBuilderAPI_MakeWire(edge).Wire();
    flywave::topo::wire topoWire(wire);
    
    try {
      std::vector<gp_Pnt> points = sample_centerline_wire(topoWire, 0, false);
      std::cout << "Zero sample count returned " << points.size() << " points" << std::endl;
    } catch (const std::exception& e) {
      std::cout << "Zero sample count correctly threw exception: " << e.what() << std::endl;
    }
  }

  // 测试边界情况：负采样点数
  std::cout << "\nTesting negative sample count" << std::endl;
  {
    gp_Pnt p1(0, 0, 0);
    gp_Pnt p2(100, 0, 0);
    TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(p1, p2).Edge();
    TopoDS_Wire wire = BRepBuilderAPI_MakeWire(edge).Wire();
    flywave::topo::wire topoWire(wire);
    
    try {
      std::vector<gp_Pnt> points = sample_centerline_wire(topoWire, -1, false);
      std::cout << "Negative sample count returned " << points.size() << " points" << std::endl;
    } catch (const std::exception& e) {
      std::cout << "Negative sample count correctly threw exception: " << e.what() << std::endl;
    }
  }
}

// 测试 get_shape_outline 函数
void test_get_shape_outline() {
  std::cout << "Testing get_shape_outline..." << std::endl;

  // 测试1: 简单的立方体形状
  {
    std::cout << "\nTest case 1: Simple box shape" << std::endl;
    
    // 创建一个立方体
    TopoDS_Shape box = BRepPrimAPI_MakeBox(10, 10, 10).Shape();
    flywave::topo::shape boxShape(box);
    
    // 获取形状轮廓
    std::vector<std::vector<gp_Pnt>> outlines = get_shape_outline(boxShape, 50, false);
    
    std::cout << "Found " << outlines.size() << " outlines" << std::endl;
    
    // 验证结果
    if (outlines.size() > 0) {
      std::cout << "First outline has " << outlines[0].size() << " points" << std::endl;
      
      // 检查是否有inf或nan值
      bool hasInvalidValues = false;
      for (const auto& outline : outlines) {
        for (const auto& point : outline) {
          if (!std::isfinite(point.X()) || !std::isfinite(point.Y()) || !std::isfinite(point.Z())) {
            std::cerr << "Error: Found inf/nan values in outline points" << std::endl;
            hasInvalidValues = true;
            break;
          }
        }
        if (hasInvalidValues) break;
      }
      
      if (!hasInvalidValues) {
        std::cout << "All outline points are valid (no inf/nan values)" << std::endl;
      }
    } else {
      std::cerr << "Error: No outlines found for box shape" << std::endl;
    }
  }

  // 测试2: 简化的轮廓
  {
    std::cout << "\nTest case 2: Simplified outline" << std::endl;
    
    // 创建一个立方体
    TopoDS_Shape box = BRepPrimAPI_MakeBox(10, 10, 10).Shape();
    flywave::topo::shape boxShape(box);
    
    // 获取简化形状轮廓
    std::vector<std::vector<gp_Pnt>> outlines = get_shape_outline(boxShape, 50, true);
    
    std::cout << "Found " << outlines.size() << " simplified outlines" << std::endl;
    
    // 验证结果
    if (outlines.size() > 0) {
      std::cout << "First simplified outline has " << outlines[0].size() << " points" << std::endl;
      
      // 检查是否有inf或nan值
      bool hasInvalidValues = false;
      for (const auto& outline : outlines) {
        for (const auto& point : outline) {
          if (!std::isfinite(point.X()) || !std::isfinite(point.Y()) || !std::isfinite(point.Z())) {
            std::cerr << "Error: Found inf/nan values in outline points" << std::endl;
            hasInvalidValues = true;
            break;
          }
        }
        if (hasInvalidValues) break;
      }
      
      if (!hasInvalidValues) {
        std::cout << "All simplified outline points are valid (no inf/nan values)" << std::endl;
      }
    } else {
      std::cerr << "Error: No simplified outlines found for box shape" << std::endl;
    }
  }

  // 测试3: 空形状
  {
    std::cout << "\nTest case 3: Empty shape" << std::endl;
    
    // 创建一个空形状
    flywave::topo::shape emptyShape;
    
    // 获取形状轮廓
    std::vector<std::vector<gp_Pnt>> outlines = get_shape_outline(emptyShape, 50, false);
    
    std::cout << "Found " << outlines.size() << " outlines for empty shape" << std::endl;
    
    if (outlines.size() == 0) {
      std::cout << "Correctly handled empty shape" << std::endl;
    } else {
      std::cerr << "Error: Expected no outlines for empty shape" << std::endl;
    }
  }

  // 测试4: 不同采样点数
  {
    std::cout << "\nTest case 4: Different sample counts" << std::endl;
    
    // 创建一个立方体
    TopoDS_Shape box = BRepPrimAPI_MakeBox(10, 10, 10).Shape();
    flywave::topo::shape boxShape(box);
    
    // 测试不同的采样点数
    std::vector<int> sampleCounts = {10, 50, 100};
    
    for (int numSamples : sampleCounts) {
      std::vector<std::vector<gp_Pnt>> outlines = get_shape_outline(boxShape, numSamples, false);
      
      std::cout << "With " << numSamples << " samples: found " << outlines.size() << " outlines" << std::endl;
      
      if (outlines.size() > 0) {
        std::cout << "  First outline has " << outlines[0].size() << " points" << std::endl;
      }
    }
  }
}

int main() {
  test_fit_centerline_from_shape();
  test_clip_with_bounding_pipe_by_ratios();
  test_sample_centerline_wire();  
  test_sample_centerline_wire_go_style();  // 添加新的Go风格测试函数
  test_get_shape_outline();
  return 0;
}
