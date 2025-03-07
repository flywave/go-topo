#include "shape.hh"
#include "solid.hh"
#include "wire.hh"
#include "edge.hh"
#include "face.hh"
#include "bool_type.hh"

#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepCheck_Analyzer.hxx>
#include <BRepGProp.hxx>
#include <GProp_GProps.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>

#include <iostream>
#include <memory>
#include <string>

using namespace flywave::topo;


void ExtractWiresFromFace(
  const TopoDS_Face& face, 
  TopoDS_Wire& outerWire, 
  TopTools_ListOfShape& innerWires
) {
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
      if (outerWire.IsNull() || area >area1 ) {
          if (!outerWire.IsNull()) {
              innerWires.Append(outerWire); // 将之前的外轮廓降级为内孔
          }
          outerWire = wire;
      } else {
          innerWires.Append(wire);
      }
  }
}

TopoDS_Shape CreateHollowPipe(
  const TopoDS_Wire& spineWire, 
  const TopoDS_Face& profileFace
) {
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
  for (TopTools_ListIteratorOfListOfShape it(innerWires); it.More(); it.Next()) {
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

void test_make_wires(){
  gp_Pnt p1{0,0,0};
  gp_Pnt p2{10,0,0};
  gp_Pnt p3{10,10,0};
  gp_Pnt p4{0,10,0};

  gp_Pnt p11{1,1,0};
  gp_Pnt p12{9,1,0};
  gp_Pnt p13{9,9,0};
  gp_Pnt p14{1,9,0};

  gp_Pnt p15{0,0,10};


  auto e1 = flywave::topo::edge::make_edge(p1,p2);
  auto e2 = flywave::topo::edge::make_edge(p2,p3);
  auto e3 = flywave::topo::edge::make_edge(p3,p4);
  auto e4 = flywave::topo::edge::make_edge(p4,p1);

  auto e5 = flywave::topo::edge::make_edge(p11,p12);
  auto e6 = flywave::topo::edge::make_edge(p12,p13);
  auto e7 = flywave::topo::edge::make_edge(p13,p14);
  auto e8 = flywave::topo::edge::make_edge(p14,p11);

 

  std::vector<flywave::topo::edge> edges1{e1,e2,e3,e4};
  std::vector<flywave::topo::edge> edges2{e5,e6,e7,e8};
  std::vector<flywave::topo::edge> edges3{ flywave::topo::edge::make_edge(p1,p15)};
  
  auto w1=flywave::topo::wire::make_wire(edges1);
  auto w2=flywave::topo::wire::make_wire(edges2);
  auto w3=flywave::topo::wire::make_wire(edges3);

  auto out_face = flywave::topo::face::make_face(w1);
  // auto inner_face = flywave::topo::face::make_face(w2);
  // out_face.boolean(inner_face,flywave::topo::bool_op_type::BOOL_CUT);

  CreateHollowPipe(w3.value(),out_face.value());
 }

int main() {
  test_make_wires();
  return 0;
}