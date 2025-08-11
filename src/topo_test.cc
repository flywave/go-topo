#include "bool_type.hh"
#include "edge.hh"
#include "face.hh"
#include "shape.hh"
#include "shape_ops.hh"
#include "solid.hh"
#include "wire.hh"

#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepCheck_Analyzer.hxx>
#include <BRepGProp.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <GC_MakeCircle.hxx>
#include <GProp_GProps.hxx>
#include <STEPControl_Writer.hxx>
#include <StlAPI_Writer.hxx>
#include <TopExp_Explorer.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <TopoDS.hxx>

#include <iostream>
#include <memory>
#include <string>

using namespace flywave::topo;

void ExtractWiresFromFace(const TopoDS_Face &face, TopoDS_Wire &outerWire,
                          TopTools_ListOfShape &innerWires) {
  TopExp_Explorer explorer(face, TopAbs_WIRE);
  GProp_GProps props;

  // 遍历所有 Wire
  for (; explorer.More(); explorer.Next()) {
    TopoDS_Wire wire = TopoDS::Wire(explorer.Current());

    // 计算 Wire 的面积（假设为平面）
    BRepGProp::SurfaceProperties(wire, props);
    double area = props.Mass();

    BRepGProp::SurfaceProperties(outerWire, props);
    double area1 = props.Mass();

    // 假设外轮廓是面积最大的 Wire
    if (outerWire.IsNull() || area > area1) {
      if (!outerWire.IsNull()) {
        innerWires.Append(outerWire); // 将之前的外轮廓降级为内孔
      }
      outerWire = wire;
    } else {
      innerWires.Append(wire);
    }
  }
}

TopoDS_Shape CreateHollowPipe(const TopoDS_Wire &spineWire,
                              const TopoDS_Face &profileFace) {
  TopoDS_Wire outerWire;
  TopTools_ListOfShape innerWires;
  ExtractWiresFromFace(profileFace, outerWire, innerWires);

  if (outerWire.IsNull()) {
    Standard_Failure::Raise("No outer wire found.");
    return TopoDS_Shape();
  }

  // 创建复合 Wire（外轮廓 + 内孔）
  BRepBuilderAPI_MakeWire compoundWireMaker;
  compoundWireMaker.Add(outerWire);
  for (TopTools_ListIteratorOfListOfShape it(innerWires); it.More();
       it.Next()) {
    compoundWireMaker.Add(TopoDS::Wire(it.Value()));
  }
  TopoDS_Wire compoundWire = compoundWireMaker.Wire();

  // 扫掠生成管道
  BRepOffsetAPI_MakePipeShell pipeMaker(spineWire);
  pipeMaker.Add(compoundWire);
  if (!pipeMaker.IsDone()) {
    Standard_Failure::Raise("Pipe generation failed.");
    return TopoDS_Shape();
  }

  // 验证结果
  TopoDS_Shape pipeShape = pipeMaker.Shape();
  BRepCheck_Analyzer analyzer(pipeShape);
  if (!analyzer.IsValid()) {
    Standard_Failure::Raise("Invalid pipe shape.");
    return TopoDS_Shape();
  }

  return pipeShape;
}

class mock_mesh_receiver : public flywave::topo::mesh_receiver {
public:
  mock_mesh_receiver() {}
  virtual ~mock_mesh_receiver() {}

  void begin() override {}

  void end() override {}

  int append_face(Quantity_Color color) override { return 1; }

  void append_node(int face, gp_Pnt p, gp_Pnt n) override {}

  void append_node(int face, gp_Pnt p, gp_Pnt n, gp_Pnt2d uv) override {}

  void append_node(int face, gp_Pnt p) override {}

  void append_triangle(int face, int tri[3]) override {}
};

void test_make_wires() {
  gp_Pnt p1{0, 0, 0};
  gp_Pnt p2{10, 0, 0};
  gp_Pnt p3{10, 10, 0};
  gp_Pnt p4{0, 10, 0};

  gp_Pnt p11{1, 1, 0};
  gp_Pnt p12{9, 1, 0};
  gp_Pnt p13{9, 9, 0};
  gp_Pnt p14{1, 9, 0};

  gp_Pnt p15{0, 0, 10};

  auto e1 = flywave::topo::edge::make_edge(p1, p2);
  auto e2 = flywave::topo::edge::make_edge(p2, p3);
  auto e3 = flywave::topo::edge::make_edge(p3, p4);
  auto e4 = flywave::topo::edge::make_edge(p4, p1);

  auto e5 = flywave::topo::edge::make_edge(p11, p12);
  auto e6 = flywave::topo::edge::make_edge(p12, p13);
  auto e7 = flywave::topo::edge::make_edge(p13, p14);
  auto e8 = flywave::topo::edge::make_edge(p14, p11);

  std::vector<flywave::topo::edge> edges1{e1, e2, e3, e4};
  std::vector<flywave::topo::edge> edges2{e5, e6, e7, e8};
  std::vector<flywave::topo::edge> edges3{
      flywave::topo::edge::make_edge(p1, p15)};

  auto w1 = flywave::topo::wire::make_wire(edges1);
  auto w2 = flywave::topo::wire::make_wire(edges2);
  auto w3 = flywave::topo::wire::make_wire(edges3);

  auto out_face = flywave::topo::face::make_face(w1);
  // auto inner_face = flywave::topo::face::make_face(w2);
  // out_face.boolean(inner_face,flywave::topo::bool_op_type::BOOL_CUT);

  CreateHollowPipe(w3.value(), out_face.value());
}

void test_clip_wire_between_distances() {
  std::cout << "\n=== Testing clip_wire_between_distances ===" << std::endl;

  // 创建混合路径（直线+圆弧）
  gp_Pnt p1(0, 0, 0);
  gp_Pnt p2(100, 0, 0);
  gp_Pnt p3(150, 50, 0);
  gp_Pnt p4(200, 0, 0);

  // 创建直线段
  auto lineEdge = flywave::topo::edge::make_edge(p1, p2);

  // 创建圆弧段
  GC_MakeArcOfCircle arc(p2, p3, p4);
  if (!arc.IsDone()) {
    std::cerr << "Error: Failed to create arc" << std::endl;
    return;
  }

  auto arcEdge = flywave::topo::edge(BRepLib_MakeEdge(arc.Value()).Shape());

  // 组合成wire
  std::vector<flywave::topo::edge> edges{lineEdge, arcEdge};
  auto mixedWire = flywave::topo::wire::make_wire(edges);

  // 计算总长度
  double totalLength = flywave::topo::wire_length(mixedWire);
  std::cout << "Total wire length: " << totalLength << " mm" << std::endl;

  // 测试不同裁剪范围
  std::vector<std::pair<double, double>> testRanges = {
      {0, totalLength / 4},                   // 第一段直线部分
      {totalLength / 4, totalLength / 2},     // 直线到圆弧过渡部分
      {totalLength / 2, totalLength * 3 / 4}, // 圆弧段部分
      {totalLength / 4, totalLength * 3 / 4}, // 跨直线和圆弧
      {totalLength - 10, totalLength}         // 最后一段
  };

  for (const auto &range : testRanges) {
    double start = range.first;
    double end = range.second;

    std::cout << "\nClipping wire from " << start << " to " << end << " mm"
              << std::endl;

    // 裁剪wire
    auto clippedWire =
        flywave::topo::clip_wire_between_distances(mixedWire, start, end);

    // 验证结果
    if (clippedWire.is_null()) {
      std::cerr << "Error: Failed to clip wire" << std::endl;
      continue;
    }

    double clippedLength = flywave::topo::wire_length(clippedWire);
    std::cout << "Clipped wire length: " << clippedLength << " mm" << std::endl;

    // 采样点验证
    auto samples = flywave::topo::sample_wire_at_distances(
        clippedWire, {0, clippedLength / 2, clippedLength});

    for (const auto &sample : samples) {
      std::cout << "Sample point at (" << sample.position.X() << ", "
                << sample.position.Y() << ", " << sample.position.Z() << ")"
                << std::endl;
    }
  }
}

void test_make_arc() {
  std::cout << "\n=== Testing make_arc ===" << std::endl;

  std::vector<gp_Pnt> points = {
      gp_Pnt(88.27510582562536, 47.17234171088785, 1.3518126332201064),
      gp_Pnt(-2.002824238501489, 61.12643328495324, -79.24088457413018),
      gp_Pnt(0, 0, 0)};

  auto arc = (points[0], points[1], points[2]);

  try {
    Handle(Geom_TrimmedCurve) arsc =
        GC_MakeArcOfCircle(points[0], points[1], points[2]).Value();

    Handle_Geom_Curve curve = Handle(Geom_Curve)::DownCast(arsc);

    TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(curve).Edge();

    if (!edge.IsNull()) {
      std::cout << "Arc created successfully." << std::endl;
    }

  } catch (const Standard_Failure &e) {
    std::cerr << "Error: " << e.GetMessageString() << std::endl;
  }
}

void test_bug() {

  std::vector<gp_Pnt> points2 = {
      gp_Pnt(88.27510582562536, 47.17234171088785, 1.3518126332201064),
      gp_Pnt(-2.002824238501489, 61.12643328495324, -7.24088457413018),
      gp_Pnt(0, 0, 0)};

  Handle(Geom_TrimmedCurve) arsc =
      GC_MakeArcOfCircle(points2[0], points2[1], points2[2]).Value();

  Handle_Geom_Curve curve = Handle(Geom_Curve)::DownCast(arsc);

  TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(curve).Edge();
  TopoDS_Wire path = BRepLib_MakeWire(edge).Wire();

  // 获取路径起始点的切线方向
  BRepAdaptor_CompCurve curveAdaptor(path);
  gp_Pnt startPoint;
  gp_Vec startTangent;
  curveAdaptor.D1(curveAdaptor.FirstParameter(), startPoint, startTangent);

  // 在创建截面圆之前添加方向修正
  gp_Dir tanDir = startTangent.Normalized();
  gp_Dir refDir = gp::DZ(); // 默认参考方向为全局Z轴

  gp_Ax2 sectionAxes(startPoint, tanDir, refDir);

  // 创建变换对象
  gp_Trsf trsf;
  trsf.SetTransformation(sectionAxes, gp_Ax2(gp::Origin(), gp::DZ()));

  // 创建点数组
  std::vector<gp_Pnt> points = {
      gp_Pnt(0, -3.4, 3.25), // X=0, Y=-3.4, Z=3.25
      gp_Pnt(0, -2.773, 4.717), gp_Pnt(0, -1.553, 5.746),
      gp_Pnt(0, 0, 6.115),      gp_Pnt(0, 1.553, 5.746),
      gp_Pnt(0, 2.773, 4.717),  gp_Pnt(0, 3.4, 3.25),
      gp_Pnt(0, 3.4, 0),        gp_Pnt(0, -3.4, 0),
      gp_Pnt(0, -3.4, 3.25) // 闭合多边形
  };
  // 创建多边形构建器
  BRepBuilderAPI_MakePolygon polygonMaker;

  // 添加所有点
  for (const auto &point : points) {
    gp_Pnt p = sectionAxes.Location().Translated(
        gp_Vec(point.Z(), point.Y(), 0).Transformed(trsf));
    polygonMaker.Add(p);
  }

  // 检查是否成功创建
  if (!polygonMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create polygon");
  }

  // 获取结果Wire
  TopoDS_Wire section = polygonMaker.Wire();

  // 创建管道形状
  BRepOffsetAPI_MakePipeShell pipeMaker(BRepLib_MakeWire(edge).Wire());
  pipeMaker.Add(section, Standard_False, Standard_True);
  pipeMaker.SetTransitionMode(BRepBuilderAPI_Transformed);
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }

  if (!pipeMaker.MakeSolid()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }

  auto shp = pipeMaker.Shape();
  if (shp.IsNull()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }

  // 对形状进行网格化（三角剖分）
  BRepMesh_IncrementalMesh mesher(shp, 0.5, false, 0.3);
  mesher.Perform();

  // 创建 STL 写入器
  StlAPI_Writer stlWriter;

  // 执行导出
  bool success = stlWriter.Write(shp, "./output_bug.stl");
}

void test_profile() {
  std::vector<gp_Pnt> arcPoints = {gp_Pnt(100, 0, 0),
                                   gp_Pnt(125, 25, 0), // 原150,50改为125,25
                                   gp_Pnt(150, 0, 0)}; // 原200,0改为150,0

  GC_MakeArcOfCircle arcMaker(arcPoints[0], arcPoints[1], arcPoints[2]);
  if (!arcMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create three-point arc");
  }
  BRepBuilderAPI_MakeWire pathMaker;
  pathMaker.Add(BRepBuilderAPI_MakeEdge(arcMaker.Value()));

  TopoDS_Wire pathWire = pathMaker.Wire();

  TopTools_IndexedMapOfShape vertices;
  TopExp::MapShapes(pathWire, TopAbs_VERTEX, vertices);

  for (int i = 0; i < vertices.Extent(); ++i) {
    gp_Pnt v = BRep_Tool::Pnt(TopoDS::Vertex(vertices(i + 1)));
    std::cout << "Vertex " << i + 1 << ": (" << v.X() << ", " << v.Y() << ", "
              << v.Z() << ")" << std::endl;
  }
  // 创建扫掠器
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.SetTransitionMode(BRepBuilderAPI_Transformed);

  // 创建路径参数化工具
  BRepAdaptor_CompCurve pathAdaptor(pathWire);
  gp_Pnt startParam, endParam;
  pathAdaptor.D0(pathAdaptor.FirstParameter(),
                 startParam);                            // 获取精确起点参数
  pathAdaptor.D0(pathAdaptor.LastParameter(), endParam); // 获取精确终点参数

  // 创建起始圆形截面 (半径10)
  gp_Pnt center1(0, 0, 0);
  Handle(Geom_Circle) outerCircle1 =
      new Geom_Circle(gp_Ax2(center1, gp::DX()), 10);
  TopoDS_Edge outerEdge1 = BRepBuilderAPI_MakeEdge(outerCircle1).Edge();
  TopoDS_Wire circleWire1 = BRepBuilderAPI_MakeWire(outerEdge1).Wire();

  pipeMaker.Add(circleWire1, TopoDS::Vertex(vertices(1)), false, true);

  // 添加第二个截面（添加坐标系旋转）
  gp_Ax2 endAxes(
      endParam,
      pathAdaptor.DN(pathAdaptor.LastParameter(), 1).Normalized(), // 切线方向
      gp_Dir(0, 0, 1)); // 法向保持Z轴
  Handle(Geom_Circle) outerCircle2 = new Geom_Circle(endAxes, 30);
  TopoDS_Edge outerEdge2 = BRepBuilderAPI_MakeEdge(outerCircle2).Edge();
  TopoDS_Wire circleWire2 = BRepBuilderAPI_MakeWire(outerEdge2).Wire();

  pipeMaker.Add(circleWire2, TopoDS::Vertex(vertices(2)), false, true);

  pipeMaker.Build();
  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Sweep operation failed");
  }

  if (!pipeMaker.MakeSolid()) {
    throw Standard_ConstructionError("Failed to make solid from sweep");
  }

  auto shp = pipeMaker.Shape();

  // 导出结果
  BRepMesh_IncrementalMesh mesher(shp, 0.5);
  mesher.Perform();

  StlAPI_Writer stlWriter;
  if (!stlWriter.Write(shp, "./test_profile.stl")) {
    std::cerr << "Error: Failed to export sweep result" << std::endl;
  } else {
    std::cout << "Sweep result exported to test_profile.stl" << std::endl;
  }
}

void test_sweep2() {

  std::vector<gp_Pnt> linePoints = {gp_Pnt(0, 0, 0), gp_Pnt(100, 0, 0)};

  // 创建起始圆形截面 (半径10)
  gp_Pnt center1(0, 0, 0);
  Handle(Geom_Circle) outerCircle1 =
      new Geom_Circle(gp_Ax2(center1, gp::DX()), 10);
  TopoDS_Edge outerEdge1 = BRepBuilderAPI_MakeEdge(outerCircle1).Edge();
  TopoDS_Wire circleWire1 = BRepBuilderAPI_MakeWire(outerEdge1).Wire();

  Handle(Geom_Circle) outerCircle3 =
      new Geom_Circle(gp_Ax2(center1, gp::DX()), 15);
  TopoDS_Edge outerEdge3 = BRepBuilderAPI_MakeEdge(outerCircle3).Edge();
  TopoDS_Wire circleWire3 = BRepBuilderAPI_MakeWire(outerEdge3).Wire();

  TopoDS_Wire pathWire1;
  {
    BRepBuilderAPI_MakeWire pathMaker1;
    pathMaker1.Add(BRepBuilderAPI_MakeEdge(linePoints[0], linePoints[1]));

    pathWire1 = pathMaker1.Wire();
  }

  flywave::topo::solid shp;
  std::vector<shape> ps0{circleWire1};
  // 执行扫掠
  int result = shp.sweep(pathWire1, ps0, 0);

  if (result != 1) {
    std::cerr << "Error: Sweep operation failed with code " << result
              << std::endl;
    return;
  }

  // 计算路径总长度
  GProp_GProps props;
  BRepGProp::LinearProperties(pathWire1, props);
  double totalLength = props.Mass();

  // 按比例0.3-1.0截取子线段
  double startDist = totalLength * 0.3;
  double endDist = totalLength * 0.7;
  auto clippedWire =
      flywave::topo::clip_wire_between_distances(pathWire1, startDist, endDist);

  std::cout << "Original wire length: " << totalLength << " mm" << std::endl;
  std::cout << "Clipped wire from " << startDist << " to " << endDist << " mm"
            << std::endl;

  // 使用截取后的路径进行扫掠
  flywave::topo::solid shp2;
  std::vector<shape> ps1{circleWire3};
  result = shp2.sweep(clippedWire, ps1, 0);

  if (result != 1) {
    std::cerr << "Error: Sweep operation failed with code " << result
              << std::endl;
    return;
  }

  // 合并两个形状
  auto compound =
      flywave::topo::compound::make_compound({shp.value(), shp2.value()});

  // 导出结果
  BRepMesh_IncrementalMesh mesher(compound, 0.5);
  mesher.Perform();

  StlAPI_Writer stlWriter;
  if (!stlWriter.Write(compound, "./sweep_result2.stl")) {
    std::cerr << "Error: Failed to export sweep result" << std::endl;
  } else {
    std::cout << "Sweep result exported to sweep_result.stl" << std::endl;
  }
}

void test_sweep() {
  std::cout << "\n=== Testing Sweep Function ===" << std::endl;

  try {
    // 准备测试数据 - 直线段 (保持原样)

    // 准备测试数据 - 三点圆弧 (调整中间点高度，使过渡更平缓)
    std::vector<gp_Pnt> arcPoints = {
        gp_Pnt(0, 0, 0),
        gp_Pnt(-33.91682722046971, 21.064596123062074, -50.42796690296382),
        gp_Pnt(-90.27793006412685, 13.954091574065387, -80.59269720735028)};

    std::vector<gp_Pnt> linePoints = {
        gp_Pnt(-90.27793006412685, 13.954091574065387, -80.59269720735028),
        gp_Pnt(-351.1830200678669, -87.76781802345067, -152.73005951102823)};
    // 组合控制点
    std::vector<std::vector<gp_Pnt>> controlPoints = {arcPoints, linePoints};

    // 指定曲线类型
    std::vector<flywave::topo::wire::curve_type> curveTypes = {
        flywave::topo::wire::curve_type::three_point_arc,
        flywave::topo::wire::curve_type::line,
    };

    flywave::topo::wire pathWire =
        flywave::topo::wire::make_wire(controlPoints, curveTypes);

    // 准备扫掠截面
    std::vector<flywave::topo::solid::sweep_profile> profiles;

    // 创建起始圆形截面 (半径10)
    gp_Pnt center1(0, 0, 0);
    Handle(Geom_Circle) outerCircle1 =
        new Geom_Circle(gp_Ax2(center1, gp::DX()), 10);
    TopoDS_Edge outerEdge1 = BRepBuilderAPI_MakeEdge(outerCircle1).Edge();
    TopoDS_Wire circleWire1 = BRepBuilderAPI_MakeWire(outerEdge1).Wire();

    flywave::topo::solid::sweep_profile profile1;
    profile1.profile = circleWire1;
    profile1.index = 0; // 在直线中点位置
    profiles.push_back(profile1);

    // 创建路径参数化工具
    BRepAdaptor_CompCurve pathAdaptor(pathWire.value());
    gp_Pnt startParam, endParam;
    pathAdaptor.D0(pathAdaptor.FirstParameter(),
                   startParam);                            // 获取精确起点参数
    pathAdaptor.D0(pathAdaptor.LastParameter(), endParam); // 获取精确终点参数

    gp_Pnt midParam;
    pathAdaptor.D0((pathAdaptor.FirstParameter() + pathAdaptor.LastParameter() -
                    pathAdaptor.FirstParameter()) *
                       0.2,
                   midParam); // 获取精确终点参数

    // 创建中间圆形截面 (半径15)
    gp_Ax2 startAxes(midParam,
                     pathAdaptor.DN(pathAdaptor.FirstParameter(), 1)
                         .Normalized(), // 切线方向
                     gp_Dir(0, 0, 1));  // 法向保持Z轴
    Handle(Geom_Circle) outerCircle2 = new Geom_Circle(startAxes, 30);
    TopoDS_Edge outerEdge2 = BRepBuilderAPI_MakeEdge(outerCircle2).Edge();
    TopoDS_Wire circleWire2 = BRepBuilderAPI_MakeWire(outerEdge2).Wire();

    flywave::topo::solid::sweep_profile profile2;
    profile2.profile = circleWire2;
    profile2.index = 0; // 在直线中点位置
    // profiles.push_back(profile2);

    gp_Ax2 endAxes(
        endParam,
        pathAdaptor.DN(pathAdaptor.LastParameter(), 1).Normalized(), // 切线方向
        gp_Dir(0, 0, 1)); // 法向保持Z轴
    Handle(Geom_Circle) outerCircle3 = new Geom_Circle(endAxes, 15);
    TopoDS_Edge outerEdge3 = BRepBuilderAPI_MakeEdge(outerCircle3).Edge();
    TopoDS_Wire circleWire3 = BRepBuilderAPI_MakeWire(outerEdge3).Wire();

    flywave::topo::solid::sweep_profile profile3;
    profile3.profile = circleWire3;
    profile3.index = 1; // 在直线中点位置
    profiles.push_back(profile3);

    flywave::topo::solid shp;
    std::vector<shape> ps0{circleWire1};
    // 执行扫掠
    int result = shp.sweep(pathWire, ps0, 0);

    if (result != 1) {
      std::cerr << "Error: Sweep operation failed with code " << result
                << std::endl;
      return;
    }

    // 计算路径总长度
    GProp_GProps props;
    BRepGProp::LinearProperties(pathWire, props);
    double totalLength = props.Mass();

    // 按比例0.3-1.0截取子线段
    double startDist = totalLength * 0.2;
    double endDist = totalLength * 0.8;
    auto clippedWire = flywave::topo::clip_wire_between_distances(
        pathWire, startDist, endDist);

    std::cout << "Original wire length: " << totalLength << " mm" << std::endl;
    std::cout << "Clipped wire from " << startDist << " to " << endDist << " mm"
              << std::endl;

    // 使用截取后的路径进行扫掠
    flywave::topo::solid shp2;
    std::vector<shape> ps1{circleWire2};
    result = shp2.sweep(clippedWire, ps1, 0);

    if (result != 1) {
      std::cerr << "Error: Sweep operation failed with code " << result
                << std::endl;
      return;
    }

    // 合并两个形状
    auto compound =
        flywave::topo::compound::make_compound({shp.value(), shp2.value()});

    // 导出结果
    BRepMesh_IncrementalMesh mesher(compound, 0.5);
    mesher.Perform();

    StlAPI_Writer stlWriter;
    if (!stlWriter.Write(compound, "./sweep_result.stl")) {
      std::cerr << "Error: Failed to export sweep result" << std::endl;
    } else {
      std::cout << "Sweep result exported to sweep_result.stl" << std::endl;
    }

  } catch (const Standard_Failure &e) {
    std::cerr << "Error: " << e.GetMessageString() << std::endl;
  }
}

void test_profile_projection() {
  std::cout << "\n=== Testing Profile Projection ===" << std::endl;

  // 创建路径 (直线+圆弧)
  std::vector<gp_Pnt> arcPoints = {
      gp_Pnt(0, 0, 0),
      gp_Pnt(-33.91682722046971, 21.064596123062074, -50.42796690296382),
      gp_Pnt(-90.27793006412685, 13.954091574065387, -80.59269720735028)};

  std::vector<gp_Pnt> linePoints = {
      gp_Pnt(-90.27793006412685, 13.954091574065387, -80.59269720735028),
      gp_Pnt(-351.1830200678669, -87.76781802345067, -152.73005951102823)};
  // 组合控制点
  std::vector<std::vector<gp_Pnt>> controlPoints = {arcPoints, linePoints};

  // 指定曲线类型
  std::vector<flywave::topo::wire::curve_type> curveTypes = {
      flywave::topo::wire::curve_type::three_point_arc,
      flywave::topo::wire::curve_type::line,
  };

  flywave::topo::wire pathWire =
      flywave::topo::wire::make_wire(controlPoints, curveTypes);

  // 计算路径总长度
  GProp_GProps props;
  BRepGProp::LinearProperties(pathWire, props);
  double totalLength = props.Mass();

  double len = totalLength * 0.99;

  double ratio = len / totalLength;

  BRepAdaptor_CompCurve pathAdaptor(pathWire.value());
  gp_Pnt _pos;
  pathAdaptor.D0(
      pathAdaptor.FirstParameter() +
          (pathAdaptor.LastParameter() - pathAdaptor.FirstParameter()) * ratio,
      _pos); // 获取精确终点参数

  // 测试不同位置的投影
  gp_Dir upDir(-0.37125487348195574, 0.7200820747659262,
               0.5862180690806932); // Z-up方向
  // gp_Pnt(59.5161544248291,19.575167920556733,13.548451730851868)

  // 计算带位置的投影
  auto proj = flywave::topo::cacl_profile_projection(pathWire, upDir, len);

  // 测试投影点
  gp_Pnt testPoint(59.5161544248291, 19.575167920556733,
                   13.548451730851868); // 原始点 (profile space)
  gp_Pnt projectedPoint =
      flywave::topo::profile_project_point(&proj, testPoint);

  std::cout << "Original point: (" << testPoint.X() << ", " << testPoint.Y()
            << ", " << testPoint.Z() << ")" << std::endl;
  std::cout << "Projected point: (" << projectedPoint.X() << ", "
            << projectedPoint.Y() << ", " << projectedPoint.Z() << ")"
            << std::endl;
}

void test_edge_spline() {
  std::vector<gp_Pnt> points = {
      gp_Pnt(0, 0, 0),
      gp_Pnt(52.78164688870311, 59.195349629968405, -37.40780537482351),
      gp_Pnt(-17.32372961891815, 73.13395502977073, -97.36982350004837),
      gp_Pnt(45.607606910169125, 140.1405232809484, -137.74216024577618),
      gp_Pnt(88.24622735986486, 177.25549516826868, -155.28305072896183)};
  auto e = flywave::topo::edge::make_spline(points, 1e-6, false);

  auto l = e.length();
  std::cout << "length: " << l << std::endl;
}

void test_save_step() {
  std::cout << "\n=== Testing Save STEP Function ===" << std::endl;

  BRepPrimAPI_MakeSphere sphereMaker(20);

  STEPControl_Writer writer;
  writer.Transfer(sphereMaker.Shape(), STEPControl_AsIs);

  if (writer.Write("./output.stp") != IFSelect_RetDone) {
    std::cerr << "Error: Failed to write STEP file" << std::endl;
    return;
  }
}

void test_clip_with_topo4d() {
  std::cout << "\n=== Testing clip_with_topo4d ===" << std::endl;

  // 创建一个简单的立方体作为被裁剪的形状
  double size = 10.0;
  gp_Pnt corner1(0, 0, 0);
  gp_Pnt corner2(size, size, size);
  auto cube = flywave::topo::solid::make_solid_from_box(corner1, corner2);

  // 情况1: original_path 不为空，radius 为空
  {
    std::cout << "Case 1: original_path non-null, radius null" << std::endl;
    work_progress_params params;
    params.original_path = flywave::topo::wire::make_wire(
        {flywave::topo::edge::make_edge(gp_Pnt(0, 0, 0), gp_Pnt(10, 0, 0)),
         flywave::topo::edge::make_edge(gp_Pnt(10, 0, 0), gp_Pnt(10, 10, 0)),
         flywave::topo::edge::make_edge(gp_Pnt(10, 10, 0), gp_Pnt(0, 10, 0)),
         flywave::topo::edge::make_edge(gp_Pnt(0, 10, 0), gp_Pnt(0, 0, 0))});
    params.radius = boost::none; // 显式设置为空
    params.type = progress_type::DISTANCE;
    params.range = {{0, 5}}; // 距离范围

    try {
      auto result = clip_with_topo4d(cube, params);
      std::cout << "Case 1 succeeded." << std::endl;
    } catch (const std::exception &e) {
      std::cerr << "Error in case 1: " << e.what() << std::endl;
    }
  }

  // 情况2: original_path 不为空，radius 不为空
  {
    std::cout << "Case 2: original_path non-null, radius non-null" << std::endl;
    work_progress_params params;
    params.original_path = flywave::topo::wire::make_wire(
        {flywave::topo::edge::make_edge(gp_Pnt(0, 0, 0), gp_Pnt(10, 0, 0)),
         flywave::topo::edge::make_edge(gp_Pnt(10, 0, 0), gp_Pnt(10, 10, 0)),
         flywave::topo::edge::make_edge(gp_Pnt(10, 10, 0), gp_Pnt(0, 10, 0)),
         flywave::topo::edge::make_edge(gp_Pnt(0, 10, 0), gp_Pnt(0, 0, 0))});
    params.radius = 5.0; // 给定半径
    params.type = progress_type::DISTANCE;
    params.range = {{0, 5}};

    try {
      auto result = clip_with_topo4d(cube, params);
      std::cout << "Case 2 succeeded." << std::endl;
    } catch (const std::exception &e) {
      std::cerr << "Error in case 2: " << e.what() << std::endl;
    }
  }

  // 情况3: original_path 为空，points 不为空且 radius 不为空
  {
    std::cout
        << "Case 3: original_path null, points non-empty and radius non-null"
        << std::endl;
    work_progress_params params;
    params.points = {gp_Pnt(0, 0, 0), gp_Pnt(5, 0, 0), gp_Pnt(5, 5, 0),
                     gp_Pnt(0, 5, 0)};
    params.radius = 2.0;
    params.type = progress_type::RATIO;
    params.range = {{0.2, 0.8}}; // 比例范围

    try {
      auto result = clip_with_topo4d(cube, params);
      std::cout << "Case 3 succeeded." << std::endl;
    } catch (const std::exception &e) {
      std::cerr << "Error in case 3: " << e.what() << std::endl;
    }
  }

  // 情况4: 其他情况（original_path 为空，且不满足情况3的条件）
  {
    std::cout << "Case 4: other cases" << std::endl;
    work_progress_params params;
    params.points = {}; // 空点集
    params.radius = boost::none;
    params.direction = gp_Dir(1, 0, 0); // 需要提供方向
    params.type = progress_type::RATIO;
    params.range = {{0.0, 1.0}};

    try {
      auto result = clip_with_topo4d(cube, params);
      std::cout << "Case 4 succeeded." << std::endl;
    } catch (const std::exception &e) {
      std::cerr << "Error in case 4: " << e.what() << std::endl;
    }
  }

  // 情况5: 测试无效的进度类型（应抛出异常）
  {
    std::cout << "Case 5: invalid progress type" << std::endl;
    work_progress_params params;
    params.points = {};
    params.radius = boost::none;
    params.direction = gp_Dir(1, 0, 0);
    params.type = static_cast<progress_type>(2); // 无效类型
    params.range = {{0.0, 1.0}};

    try {
      auto result = clip_with_topo4d(cube, params);
      std::cerr << "Error: expected exception not thrown in case 5."
                << std::endl;
    } catch (const std::invalid_argument &e) {
      std::cout << "Case 5 succeeded with expected exception: " << e.what()
                << std::endl;
    } catch (const std::exception &e) {
      std::cerr << "Unexpected exception in case 5: " << e.what() << std::endl;
    }
  }
}

int main() {
  test_save_step();
  test_clip_with_topo4d();
  return 0;
}
