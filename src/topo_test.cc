#include "bool_type.hh"
#include "edge.hh"
#include "face.hh"
#include "shape.hh"
#include "shape_ops.hh"
#include "solid.hh"
#include "wire.hh"

#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepCheck_Analyzer.hxx>
#include <BRepGProp.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <GProp_GProps.hxx>
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
  double totalLength = flywave::topo::wrie_length(mixedWire);
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

    double clippedLength = flywave::topo::wrie_length(clippedWire);
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
  gp_Dir refDir = gp::DZ(); // 默认参考方向为全局Y轴

  gp_Ax2 sectionAxes(startPoint, tanDir, refDir);

  // 创建变换对象
  gp_Trsf trsf;
  trsf.SetTransformation(sectionAxes, gp_Ax2(gp::Origin(), gp::DZ()));

  // 创建点数组
  std::vector<gp_Pnt> points = {
      gp_Pnt(-3.4, 3.25, 0), gp_Pnt(-2.773, 4.717, 0), gp_Pnt(-1.553, 5.746, 0),
      gp_Pnt(0, 6.115, 0),   gp_Pnt(1.553, 5.746, 0),  gp_Pnt(2.773, 4.717, 0),
      gp_Pnt(3.4, 3.25, 0),  gp_Pnt(3.4, 0, 0),        gp_Pnt(-3.4, 0, 0),
      gp_Pnt(-3.4, 3.25, 0) // 闭合多边形
  };

  // 创建多边形构建器
  BRepBuilderAPI_MakePolygon polygonMaker;

  // 添加所有点
  for (const auto &point : points) {
    gp_Pnt p = sectionAxes.Location().Translated(
        gp_Vec(point.Y(), point.X(), 0).Transformed(trsf));
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

int main() {
  test_clip_wire_between_distances();
  test_bug();
  return 0;
}
