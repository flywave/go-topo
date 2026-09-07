#include "primitives.hh"
#include "bounding_pipe.hh"
#include "catenary.hh"

#include <BRepAdaptor_CompCurve.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepBndLib.hxx>
#include <BRepBuilderAPI_Copy.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepBuilderAPI_MakeShell.hxx>
#include <BRepBuilderAPI_MakeSolid.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_Sewing.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepBuilderAPI_TransitionMode.hxx>
#include <BRepCheck_Analyzer.hxx>
#include <BRepCheck_Wire.hxx>
#include <BRepFilletAPI_MakeChamfer.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepGProp.hxx>
#include <BRepOffsetAPI_MakeOffset.hxx>
#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <BRepPrimAPI_MakeRevolution.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakeWedge.hxx>
#include <BRepTools.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <BRep_Tool.hxx>
#include <ChFi2d_AnaFilletAlgo.hxx>
#include <ElCLib.hxx>
#include <GCPnts_AbscissaPoint.hxx>
#include <GCPnts_UniformAbscissa.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <GC_MakeCircle.hxx>
#include <GC_MakeSegment.hxx>
#include <GProp_GProps.hxx>
#include <GeomAPI_IntCS.hxx>
#include <GeomAPI_Interpolate.hxx>
#include <GeomAPI_PointsToBSpline.hxx>
#include <GeomFill_Pipe.hxx>
#include <Geom_BezierCurve.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Line.hxx>
#include <Geom_Plane.hxx>
#include <Geom_SurfaceOfRevolution.hxx>
#include <Law_Linear.hxx>
#include <Precision.hxx>
#include <STEPControl_Reader.hxx>
#include <ShapeFix_Shape.hxx>
#include <Standard_ConstructionError.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Wire.hxx>
#include <gp_Ax2.hxx>
#include <gp_Ax3.hxx>
#include <gp_Circ.hxx>
#include <gp_Dir.hxx>
#include <gp_Elips.hxx>
#include <gp_Pln.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>
#include <StlAPI_Writer.hxx>
#include <BRepMesh_IncrementalMesh.hxx>

// ==================================================================
// 由 primitives.cc 按专业拆分而来; 声明统一见 primitives.hh
// GIM 变电 (substation) — 套管 / 支柱绝缘子 / 端子板 / 设备固定板

namespace flywave {
namespace topo {


TopoDS_Shape create_porcelain_bushing(const porcelain_bushing_params &params) {
  // 参数验证（保持不变）
  if (params.height <= 0.0) {
    throw Standard_ConstructionError("Height must be positive");
  }
  if (params.radius <= 0.0) {
    throw Standard_ConstructionError("Radius must be positive");
  }
  if (params.bigSkirtRadius < params.smallSkirtRadius) {
    throw Standard_ConstructionError(
        "Big skirt radius must be >= small skirt radius");
  }
  if (params.smallSkirtRadius <= params.radius) {
    throw Standard_ConstructionError(
        "Small skirt radius must be > tube radius");
  }
  if (params.count <= 0) {
    throw Standard_ConstructionError("Count must be positive");
  }

  // 创建主圆柱体（保持不变）
  gp_Ax2 axis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  TopoDS_Shape mainCylinder =
      BRepPrimAPI_MakeCylinder(axis, params.radius, params.height).Shape();

  if (params.count == 0) {
    return mainCylinder;
  }

  // 新伞裙生成方式（保持原参数但改用更真实的5点剖面）
  double segmentHeight = params.height / (params.count * 2 + 1);
  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);
  builder.Add(compound, mainCylinder);

  for (int i = 0; i < params.count; ++i) {
    // 大伞裙位置（保持原计算方式）
    double zPos = (2 * i + 1) * segmentHeight;
    double skirtRadius =
        (i % 2 == 0) ? params.bigSkirtRadius : params.smallSkirtRadius;

    // 创建更真实的5点伞裙截面
    BRepBuilderAPI_MakeWire wire;
    gp_Pnt basePoint(params.radius, 0, zPos); // 起始点：主体表面
    gp_Pnt p1(skirtRadius, 0, zPos);
    gp_Pnt p2(skirtRadius * 0.95, 0, zPos + segmentHeight * 0.25);
    gp_Pnt p3(skirtRadius * 0.7, 0, zPos + segmentHeight * 0.4);

    wire.Add(BRepBuilderAPI_MakeEdge(basePoint, p1));
    wire.Add(BRepBuilderAPI_MakeEdge(p1, p2));
    wire.Add(BRepBuilderAPI_MakeEdge(p2, p3));
    wire.Add(BRepBuilderAPI_MakeEdge(p3, basePoint));

    // 验证wire闭合性
    if (!wire.IsDone()) {
      throw Standard_ConstructionError("skirt wire not closed");
    }

    // 旋转生成大伞裙
    BRepPrimAPI_MakeRevol bigSkirtRevol(BRepLib_MakeFace(wire.Wire()).Face(),
                                        gp_Ax1(gp::Origin(), gp::DZ()));
    bigSkirtRevol.Build();
    TopoDS_Shape bigSkirt = bigSkirtRevol.Shape();
    if (bigSkirt.IsNull()) {
      throw Standard_ConstructionError("bigSkirt is null");
    }
    // 修改融合方式
    builder.Add(compound, bigSkirt);
  }

  return compound;
}


TopoDS_Shape create_porcelain_bushing(const porcelain_bushing_params &params,
                                      const gp_Pnt &basePoint,
                                      const gp_Dir &axisDirection) {
  // 首先创建标准方向的瓷套/绝缘子
  TopoDS_Shape bushing = create_porcelain_bushing(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(basePoint, axisDirection);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(bushing, transformation);
  return transform.Shape();
}


TopoDS_Shape
create_cone_porcelain_bushing(const cone_porcelain_bushing_params &params) {
  // 参数验证（保持不变）
  if (params.height <= 0.0) {
    throw Standard_ConstructionError("Height must be positive");
  }
  if (params.bottomRadius <= 0.0 || params.topRadius <= 0.0) {
    throw Standard_ConstructionError("Radii must be positive");
  }
  if (params.bottomSkirtRadius1 <= params.bottomRadius ||
      params.bottomSkirtRadius2 <= params.bottomRadius) {
    throw Standard_ConstructionError(
        "Bottom skirt radii must be greater than bottom radius");
  }
  if (params.topSkirtRadius1 <= params.topRadius ||
      params.topSkirtRadius2 <= params.topRadius) {
    throw Standard_ConstructionError(
        "Top skirt radii must be greater than top radius");
  }
  if (params.count <= 0) {
    throw Standard_ConstructionError("Count must be positive");
  }

  // 创建主锥形体（保持不变）
  gp_Ax2 axis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  TopoDS_Shape mainCone = BRepPrimAPI_MakeCone(axis, params.bottomRadius,
                                               params.topRadius, params.height)
                              .Shape();

  if (params.count == 0) {
    return mainCone;
  }

  // 初始化融合对象（修正构造函数问题）
  double segmentHeight = params.height / (params.count + 1);
  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);
  builder.Add(compound, mainCone);

  for (int i = 1; i <= params.count; ++i) {
    // 计算当前高度的插值比例（保持原计算方式）
    double ratio = static_cast<double>(i) / (params.count + 1);

    // 插值计算当前半径和伞裙半径（保持原计算方式）
    double currentRadius =
        params.bottomRadius + (params.topRadius - params.bottomRadius) * ratio;
    double currentSkirtRadius1 =
        params.bottomSkirtRadius1 +
        (params.topSkirtRadius1 - params.bottomSkirtRadius1) * ratio;
    double currentSkirtRadius2 =
        params.bottomSkirtRadius2 +
        (params.topSkirtRadius2 - params.bottomSkirtRadius2) * ratio;

    // 交替使用两种伞裙半径（保持原逻辑）
    double skirtRadius =
        (i % 2 == 0) ? currentSkirtRadius1 : currentSkirtRadius2;

    // 创建伞裙位置（保持原计算方式）
    double zPos = i * segmentHeight;

    // 创建更真实的5点伞裙截面（新生成方式）
    BRepBuilderAPI_MakeWire wire;
    gp_Pnt basePoint(currentRadius, 0, zPos); // 起始点：主体表面
    gp_Pnt p1(skirtRadius, 0, zPos);          // 伞裙外缘
    gp_Pnt p2(skirtRadius * 0.95, 0, zPos + segmentHeight * 0.25); // 上翘
    gp_Pnt p3(skirtRadius * 0.5, 0, zPos + segmentHeight * 0.4);   // 下凹
    gp_Pnt endPoint(currentRadius, 0,
                    zPos + segmentHeight * 0.3); // 起始点：主体表面

    wire.Add(BRepBuilderAPI_MakeEdge(basePoint, p1));
    wire.Add(BRepBuilderAPI_MakeEdge(p1, p2));
    wire.Add(BRepBuilderAPI_MakeEdge(p2, p3));
    wire.Add(BRepBuilderAPI_MakeEdge(p3, endPoint));
    wire.Add(BRepBuilderAPI_MakeEdge(endPoint, basePoint));

    // 验证wire闭合性
    if (!wire.IsDone()) {
      throw Standard_ConstructionError("skirt wire not closed");
    }

    // 旋转生成伞裙（360度）

    BRepPrimAPI_MakeRevol bigSkirtRevol(BRepLib_MakeFace(wire.Wire()).Face(),
                                        gp_Ax1(gp::Origin(), gp::DZ()));
    bigSkirtRevol.Build();
    TopoDS_Shape bigSkirt = bigSkirtRevol.Shape();
    if (bigSkirt.IsNull()) {
      throw Standard_ConstructionError("bigSkirt is null");
    }
    // 修改融合方式
    builder.Add(compound, bigSkirt);
  }

  return compound;
}


TopoDS_Shape
create_cone_porcelain_bushing(const cone_porcelain_bushing_params &params,
                              const gp_Pnt &basePoint,
                              const gp_Dir &axisDirection) {
  // 首先创建标准方向的锥形瓷套
  TopoDS_Shape bushing = create_cone_porcelain_bushing(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(basePoint, axisDirection);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(bushing, transformation);
  return transform.Shape();
}

/**
 * @brief 创建端子板图元
 *
 * @param length 长度 (L > W)
 * @param width 宽度 (W > 0)
 * @param thickness 厚度 (T > 0)
 * @param chamferLength 倒角边长 (CL > 0)
 * @param columnSpacing 孔列间距 (CS > 0)
 * @param rowSpacing 孔行间距 (RS > 0)
 * @param holeRadius 孔半径 (R > 0)
 * @param columnCount 开孔列数 (CN > 0)
 * @param rowCount 开孔行数 (RN > 0)
 * @param bottomOffset 孔行距底边距离 (BL > 0)
 * @return TopoDS_Shape 生成的端子板形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_terminal_block(const terminal_block_params &params) {
  // 参数验证
  if (params.length <= params.width) {
    throw Standard_ConstructionError("Length must be greater than width");
  }
  if (params.width <= 0.0 || params.thickness <= 0.0 ||
      params.chamferLength <= 0.0) {
    throw Standard_ConstructionError("Dimensions must be positive");
  }
  if (params.columnSpacing <= 0.0 || params.rowSpacing <= 0.0 ||
      params.holeRadius <= 0.0) {
    throw Standard_ConstructionError("Hole parameters must be positive");
  }
  if (params.columnCount <= 0 || params.rowCount <= 0) {
    throw Standard_ConstructionError("Hole counts must be positive");
  }
  if (params.bottomOffset <= 0.0) {
    throw Standard_ConstructionError("Bottom offset must be positive");
  }

  // 创建符合标准坐标系的基准轴系
  gp_Ax2 mainAxis(
      gp_Pnt(-params.width / 2, -params.thickness / 2, 0), // 原点在底面中心
      gp_Dir(0, 0, 1), // Z轴方向（长度方向）
      gp_Dir(1, 0, 0)  // X轴方向（宽度方向）
  );

  // 创建基础长方体（使用修正后的坐标系）
  BRepPrimAPI_MakeBox boxMaker(mainAxis,
                               params.width,     // X方向尺寸（宽度）
                               params.thickness, // Y方向尺寸（厚度）
                               params.length     // Z方向尺寸（长度）
  );
  TopoDS_Shape block = boxMaker.Shape();

  // 创建孔洞集合
  TopoDS_Compound holes;
  BRep_Builder holeBuilder;
  holeBuilder.MakeCompound(holes);

  // 计算孔洞矩阵参数
  const double matrixWidth = (params.columnCount - 1) * params.columnSpacing;
  const double matrixLength = (params.rowCount - 1) * params.rowSpacing;

  // 计算起始位置（矩阵居中）
  const double startX = -matrixWidth / 2.0;
  const double startZ = 0 + params.bottomOffset;

  // 生成孔洞
  for (int col = 0; col < params.columnCount; ++col) {
    for (int row = 0; row < params.rowCount; ++row) {
      // 计算孔中心位置
      const double x = startX + col * params.columnSpacing;
      const double z = startZ + row * params.rowSpacing;

      // 创建穿透孔洞（Y方向完全穿透）
      gp_Ax2 holeAxis(gp_Pnt(x, -params.thickness, z), // 起始于底面（Y=0）
                      gp_Dir(0, 1, 0)                  // 沿Y轴方向（厚度方向）
      );
      BRepPrimAPI_MakeCylinder holeMaker(holeAxis, params.holeRadius,
                                         params.thickness * 2 // 确保完全穿透
      );

      holeBuilder.Add(holes, holeMaker.Shape());
    }
  }

  // 执行批量布尔运算
  BRepAlgoAPI_Cut finalCut(block, holes);
  if (!finalCut.IsDone()) {
    throw Standard_ConstructionError("Hole cutting operation failed");
  }
  TopoDS_Shape result = finalCut.Shape();

  // 添加倒角（仅处理平行Y轴的边）
  if (params.chamferLength > Precision::Confusion()) {
    TopTools_IndexedMapOfShape edges;
    TopExp::MapShapes(result, TopAbs_EDGE, edges);

    BRepFilletAPI_MakeChamfer chamferMaker(result);

    for (int i = 1; i <= edges.Extent(); ++i) {
      const TopoDS_Edge &edge = TopoDS::Edge(edges.FindKey(i));

      // 获取边缘几何信息
      Standard_Real first, last;
      Handle(Geom_Curve) curve = BRep_Tool::Curve(edge, first, last);

      // 仅处理直线边
      if (curve->DynamicType() == STANDARD_TYPE(Geom_Line)) {
        Handle(Geom_Line) line = Handle(Geom_Line)::DownCast(curve);
        gp_Dir edgeDir = line->Lin().Direction();

        // 检查是否平行Y轴（X和Y分量为0）
        if (Abs(edgeDir.X()) < Precision::Angular() &&
            Abs(edgeDir.Z()) < Precision::Angular()) {
          chamferMaker.Add(params.chamferLength, edge);
        }
      }
    }

    chamferMaker.Build();

    if (chamferMaker.IsDone()) {
      result = chamferMaker.Shape();
    }
  }

  return result;
}


TopoDS_Shape create_terminal_block(const terminal_block_params &params,
                                   const gp_Pnt &position,
                                   const gp_Dir &lengthDir,
                                   const gp_Dir &widthDir) {
  // 首先创建标准方向的端子板
  TopoDS_Shape block = create_terminal_block(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0), gp_Dir(1, 0, 0));
  gp_Dir thicknessDir = lengthDir.Crossed(widthDir);
  gp_Ax3 targetAx3(position, thicknessDir, widthDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(block, transformation);
  return transform.Shape();
}


TopoDS_Shape
create_rectangular_fixed_plate(const rectangular_fixed_plate_params &params) {
  // 参数验证
  if (params.length <= 0.0 || params.width <= 0.0) {
    throw Standard_ConstructionError("Dimensions must be positive");
  }
  if (params.thickness <= 0.0) {
    throw Standard_ConstructionError("Thickness must be positive");
  }
  if (params.columnSpacing <= 0.0 || params.rowSpacing <= 0.0) {
    throw Standard_ConstructionError("Spacing must be positive");
  }
  if (params.columnCount <= 0 || params.rowCount <= 0) {
    throw Standard_ConstructionError("Hole counts must be positive");
  }
  if (params.holeDiameter <= 0.0) {
    throw Standard_ConstructionError("Hole diameter must be positive");
  }

  // 创建基础长方体
  gp_Ax2 axis(gp_Pnt(-params.length / 2, -params.width / 2, 0),
              gp_Dir(0, 0, 1));
  BRepPrimAPI_MakeBox boxMaker(axis, params.length, params.width,
                               params.thickness);
  TopoDS_Shape plate = boxMaker.Shape();

  // 创建孔洞
  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);
  builder.Add(compound, plate);

  // 计算孔洞起始位置
  double startX =
      -params.length / 2 +
      (params.length - (params.columnCount - 1) * params.columnSpacing) / 2;
  double startY =
      -params.width / 2 +
      (params.width - (params.rowCount - 1) * params.rowSpacing) / 2;

  bool jumpMiddleHole =
      (params.columnCount % 2 == 1) && (params.rowCount % 2 == 1);

  // 创建孔洞
  for (int col = 0; col < params.columnCount; ++col) {
    for (int row = 0; row < params.rowCount; ++row) {
      // 跳过中间孔（如果需要单独处理）
      if (jumpMiddleHole && col == (params.columnCount - 1) / 2 &&
          row == (params.rowCount - 1) / 2) {
        continue;
      }

      double x = startX + col * params.columnSpacing;
      double y = startY + row * params.rowSpacing;

      // 创建圆柱孔
      gp_Ax2 holeAxis(gp_Pnt(x, y, -params.thickness / 2), gp_Dir(0, 0, 1));
      BRepPrimAPI_MakeCylinder holeMaker(holeAxis, params.holeDiameter / 2,
                                         params.thickness * 2);

      // 执行布尔差操作
      BRepAlgoAPI_Cut cutter(compound, holeMaker.Shape());
      if (!cutter.IsDone()) {
        throw Standard_ConstructionError("Failed to create holes");
      }

      TopoDS_Compound newCompound;
      builder.MakeCompound(newCompound);
      builder.Add(newCompound, cutter.Shape());
      compound = newCompound;
    }
  }

  // 创建中间孔（如果需要）
  if (jumpMiddleHole && params.hasMiddleHole == 1) {
    gp_Ax2 middleHoleAxis(gp_Pnt(0, 0, -params.thickness / 2), gp_Dir(0, 0, 1));
    BRepPrimAPI_MakeCylinder middleHoleMaker(
        middleHoleAxis, params.holeDiameter / 2, params.thickness * 2);

    // 执行布尔差操作
    BRepAlgoAPI_Cut cutter(compound, middleHoleMaker.Shape());
    if (!cutter.IsDone()) {
      throw Standard_ConstructionError("Failed to create middle hole");
    }

    TopoDS_Compound newCompound;
    builder.MakeCompound(newCompound);
    builder.Add(newCompound, cutter.Shape());
    compound = newCompound;
  }

  return compound;
}


TopoDS_Shape
create_rectangular_fixed_plate(const rectangular_fixed_plate_params &params,
                               const gp_Pnt &position, const gp_Dir &lengthDir,
                               const gp_Dir &widthDir) {
  // 首先创建标准方向的矩形开孔板
  TopoDS_Shape plate = create_rectangular_fixed_plate(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  gp_Dir thicknessDir = lengthDir.Crossed(widthDir);
  gp_Ax3 targetAx3(position, thicknessDir, lengthDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(plate, transformation);
  return transform.Shape();
}


TopoDS_Shape
create_circular_fixed_plate(const circular_fixed_plate_params &params) {
  // 参数验证
  if (params.length <= 0.0 || params.width <= 0.0) {
    throw Standard_ConstructionError("Dimensions must be positive");
  }
  if (params.thickness <= 0.0) {
    throw Standard_ConstructionError("Thickness must be positive");
  }
  if (params.ringRadius <= 0.0) {
    throw Standard_ConstructionError("Ring radius must be positive");
  }
  if (params.holeCount <= 0) {
    throw Standard_ConstructionError("Hole count must be positive");
  }
  if (params.holeDiameter <= 0.0) {
    throw Standard_ConstructionError("Hole diameter must be positive");
  }

  // 创建基础长方体
  gp_Ax2 axis(gp_Pnt(-params.length / 2, -params.width / 2, 0),
              gp_Dir(0, 0, 1));
  BRepPrimAPI_MakeBox boxMaker(axis, params.length, params.width,
                               params.thickness);
  TopoDS_Shape plate = boxMaker.Shape();

  // 创建孔洞
  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);
  builder.Add(compound, plate);

  // 计算孔洞位置（圆形分布）
  double angleStep = 2 * M_PI / params.holeCount;
  for (int i = 0; i < params.holeCount; ++i) {
    double angle = i * angleStep;
    double x = params.ringRadius * cos(angle);
    double y = params.ringRadius * sin(angle);

    // 创建圆柱孔
    gp_Ax2 holeAxis(gp_Pnt(x, y, -params.thickness / 2), gp_Dir(0, 0, 1));
    BRepPrimAPI_MakeCylinder holeMaker(holeAxis, params.holeDiameter / 2,
                                       params.thickness * 2);

    // 执行布尔差操作
    BRepAlgoAPI_Cut cutter(compound, holeMaker.Shape());
    if (!cutter.IsDone()) {
      throw Standard_ConstructionError("Failed to create holes");
    }

    TopoDS_Compound newCompound;
    builder.MakeCompound(newCompound);
    builder.Add(newCompound, cutter.Shape());
    compound = newCompound;
  }

  // 创建中间孔（如果需要）
  if (params.hasMiddleHole) {
    gp_Ax2 middleHoleAxis(gp_Pnt(0, 0, -params.thickness / 2), gp_Dir(0, 0, 1));
    BRepPrimAPI_MakeCylinder middleHoleMaker(
        middleHoleAxis, params.holeDiameter / 2, params.thickness * 2);

    // 执行布尔差操作
    BRepAlgoAPI_Cut cutter(compound, middleHoleMaker.Shape());
    if (!cutter.IsDone()) {
      throw Standard_ConstructionError("Failed to create middle hole");
    }

    TopoDS_Compound newCompound;
    builder.MakeCompound(newCompound);
    builder.Add(newCompound, cutter.Shape());
    compound = newCompound;
  }

  return compound;
}


TopoDS_Shape
create_circular_fixed_plate(const circular_fixed_plate_params &params,
                            const gp_Pnt &position, const gp_Dir &lengthDir,
                            const gp_Dir &widthDir) {
  // 首先创建标准方向的圆形开孔板
  TopoDS_Shape plate = create_circular_fixed_plate(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  gp_Dir thicknessDir = lengthDir.Crossed(widthDir);
  gp_Ax3 targetAx3(position, thicknessDir, lengthDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(plate, transformation);
  return transform.Shape();
}


TopoDS_Shape create_rod_insulator(const insulator_params &params) {
  // 参数验证
  bool isComposite = boost::get<composite_insulator_params>(
                         &params.insulator.radius) != nullptr;
  auto compParams =
      isComposite
          ? boost::get<composite_insulator_params>(params.insulator.radius)
          : composite_insulator_params{0, 0, 0};

  double diskDiameter = isComposite
                            ? compParams.majorRadius * 2
                            : boost::get<double>(params.insulator.radius) * 2;

  // 计算伞裙参数
  double shedThickness = isComposite ? compParams.gap * 0.4
                                     : params.insulator.height *
                                           0.05; // 普通绝缘子伞裙厚度为高度的5%
  double gap = isComposite ? compParams.gap
                           : (params.insulator.height -
                              shedThickness * params.insulator.leftCount) /
                                 (params.insulator.leftCount - 1);

  int leftCount =
      isComposite && compParams.gap > 0
          ? params.insulator.height / (compParams.gap + shedThickness)
          : params.insulator.leftCount;
  int rightCount =
      isComposite && compParams.gap > 0
          ? params.insulator.height / (compParams.gap + shedThickness)
          : params.insulator.rightCount;

  double rodDiameter =
      isComposite ? compParams.minorRadius / 4 : diskDiameter / 4;
  if (diskDiameter <= 0 || shedThickness <= 0 ||
      params.insulator.leftCount <= 0 || rodDiameter <= 0 ||
      params.insulator.height <= 0) {
    throw Standard_ConstructionError("绝缘子参数必须为正数");
  }

  // 创建单个绝缘子单元
  auto create_single_insulator = [&](const gp_Pnt &position, int shedCount,
                                     const gp_Pnt &rodPos, double rodHeight) {
    gp_Ax2 rodAxis(rodPos, gp_Dir(0, 0, 1));
    TopoDS_Shape rod =
        BRepPrimAPI_MakeCylinder(rodAxis, rodDiameter / 2, rodHeight).Shape();

    TopoDS_Compound insulator;
    BRep_Builder insulatorBuilder;
    insulatorBuilder.MakeCompound(insulator);
    insulatorBuilder.Add(insulator, rod);
    for (int i = 0; i < shedCount; i++) {
      double zPos = position.Z() + i * (gap + shedThickness); // 伞裙位置计算
      double currentDiameter =
          isComposite
              ? (i % 2 == 0 ? compParams.majorRadius : compParams.minorRadius) *
                    2
              : boost::get<double>(params.insulator.radius) * 2;

      // 铜锣状伞裙截面（与分裂数无关）
      BRepBuilderAPI_MakeWire wire;
      gp_Pnt p_base(position.X(), position.Y(), zPos);

      // 直接计算各点绝对坐标，不使用链式变换
      gp_Pnt p1(p_base.X() + rodDiameter / 2, p_base.Y(),
                p_base.Z() + shedThickness * 0.4);
      gp_Pnt p2(p1.X() + (currentDiameter - rodDiameter) / 5, p1.Y(),
                p_base.Z() + shedThickness * 0.2);
      gp_Pnt p3(p_base.X() + currentDiameter / 2, p_base.Y(),
                p_base.Z() + shedThickness * 0.4);
      gp_Pnt p4(p_base.X() + rodDiameter / 2 +
                    (currentDiameter - rodDiameter) / 6,
                p_base.Y(), p_base.Z() + shedThickness * 0.6);
      gp_Pnt p5(p_base.X() + rodDiameter / 2, p_base.Y(),
                p_base.Z() + shedThickness * 0.65);

      wire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
      wire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
      wire.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
      wire.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge());
      wire.Add(BRepBuilderAPI_MakeEdge(p5, p1).Edge()); // 添加闭合边

      // 需要增加闭合性验证
      if (!wire.IsDone()) {
        throw Standard_ConstructionError("伞裙截面Wire未闭合");
      }

      // 旋转生成伞裙
      gp_Ax1 axis(p_base, gp_Dir(0, 0, 1));
      TopoDS_Shape shed =
          BRepPrimAPI_MakeRevol(BRepLib_MakeFace(wire.Wire()).Face(), axis)
              .Shape();

      insulatorBuilder.Add(insulator, shed);
    }

    return insulator;
  };

  // 创建绝缘子主体

  TopoDS_Compound insulatorBody;
  BRep_Builder insulatorBodyBuilder;
  insulatorBodyBuilder.MakeCompound(insulatorBody);

  // 处理V型、U型和I型绝缘子串
  if (params.vAngleLeft != 0 || params.vAngleRight != 0) { // V型串
    double angleL_rad = params.vAngleLeft * M_PI / 180.0;
    double angleR_rad = params.vAngleRight * M_PI / 180.0;
    // 创建左侧绝缘子串
    gp_Trsf leftTransform;
    leftTransform.SetRotation(
        gp_Ax1(gp_Pnt(0, 0,
                      -params.insulator.height -
                          params.fittingLengths.leftLower -
                          params.fittingLengths.leftUpper),
               gp_Dir(1, 0, 0)),
        angleL_rad);
    TopoDS_Shape leftInsulator = create_single_insulator(
        gp_Pnt(0, 0,
               -params.insulator.height - params.fittingLengths.leftUpper),
        leftCount,
        gp_Pnt(0, 0,
               -params.insulator.height - params.fittingLengths.leftUpper -
                   params.fittingLengths.leftLower),
        params.insulator.height + params.fittingLengths.leftUpper +
            params.fittingLengths.leftLower);
    leftInsulator =
        BRepBuilderAPI_Transform(leftInsulator, leftTransform).Shape();

    // 创建右侧绝缘子串
    gp_Trsf rightTransform;
    rightTransform.SetRotation(
        gp_Ax1(gp_Pnt(0, 0,
                      -params.insulator.height -
                          params.fittingLengths.rightUpper -
                          params.fittingLengths.rightLower),
               gp_Dir(1, 0, 0)),
        -angleR_rad);
    TopoDS_Shape rightInsulator = create_single_insulator(
        gp_Pnt(0, 0,
               -params.insulator.height - params.fittingLengths.rightUpper),
        rightCount,
        gp_Pnt(0, 0,
               -params.insulator.height - params.fittingLengths.rightUpper -
                   params.fittingLengths.rightLower),
        params.insulator.height + params.fittingLengths.rightUpper +
            params.fittingLengths.rightLower);
    rightInsulator =
        BRepBuilderAPI_Transform(rightInsulator, rightTransform).Shape();

    // 计算并应用垂直平移（补偿旋转导致的高度变化）
    Bnd_Box leftBox;
    BRepBndLib::Add(leftInsulator, leftBox);
    double leftMinZ = 0, leftMaxZ = 0;
    leftBox.Get(leftMinZ, leftMinZ, leftMinZ, leftMaxZ, leftMaxZ, leftMaxZ);

    // 计算并应用垂直平移（补偿旋转导致的高度变化）
    Bnd_Box rightBox;
    BRepBndLib::Add(rightInsulator, rightBox);
    double rightMinZ = 0, rightMaxZ = 0;
    rightBox.Get(rightMinZ, rightMinZ, rightMinZ, rightMaxZ, rightMaxZ,
                 rightMaxZ);

    double offsetZ = 0;
    if (leftMaxZ > rightMaxZ) {
      offsetZ = leftMaxZ;
    } else {
      offsetZ = rightMaxZ;
    }

    gp_Trsf leftTranslate;
    leftTranslate.SetTranslation(gp_Vec(0, 0, -offsetZ)); // 将最高点移动到Z=0
    leftInsulator =
        BRepBuilderAPI_Transform(leftInsulator, leftTranslate).Shape();
    gp_Trsf rightTranslate;
    rightTranslate.SetTranslation(gp_Vec(0, 0, -offsetZ)); // 将最高点移动到Z=0
    rightInsulator =
        BRepBuilderAPI_Transform(rightInsulator, rightTranslate).Shape();

    // 合并绝缘子主体
    insulatorBodyBuilder.Add(insulatorBody, leftInsulator);
    insulatorBodyBuilder.Add(insulatorBody, rightInsulator);
  } else if (params.uLinkLength > 0) { // U型串
    // U型串处理（移除连接板）
    TopoDS_Shape leftInsulator = create_single_insulator(
        gp_Pnt(-params.uLinkLength / 2, 0,
               -params.insulator.height - params.fittingLengths.leftUpper),
        leftCount,
        gp_Pnt(-params.uLinkLength / 2, 0,
               -params.insulator.height - params.fittingLengths.leftUpper -
                   params.fittingLengths.leftLower),
        params.insulator.height + params.fittingLengths.leftUpper +
            params.fittingLengths.leftLower);
    TopoDS_Shape rightInsulator = create_single_insulator(
        gp_Pnt(params.uLinkLength / 2, 0,
               -params.insulator.height - params.fittingLengths.rightUpper),
        rightCount,
        gp_Pnt(params.uLinkLength / 2, 0,
               -params.insulator.height - params.fittingLengths.rightUpper -
                   params.fittingLengths.rightLower),
        params.insulator.height + params.fittingLengths.rightUpper +
            params.fittingLengths.rightLower);

    // 创建中间连接部分 - 根据电力行业标准设计
    double connectorWidth = rodDiameter * 1.5; // 连接件宽度为芯棒直径的1.5倍
    double connectorThickness =
        rodDiameter * 0.8; // 连接件厚度为芯棒直径的0.8倍

    // 连接件长度等于U型串的水平长度
    TopoDS_Shape connector1 = create_rectangular_beam(
        params.uLinkLength, connectorThickness, connectorWidth,
        gp_Pnt(0, 0, -connectorWidth / 2));

    // 连接件长度等于U型串的水平长度
    TopoDS_Shape connector2 = create_rectangular_beam(
        params.uLinkLength, connectorThickness, connectorWidth,
        gp_Pnt(0, 0,
               -params.insulator.height - params.fittingLengths.rightUpper -
                   params.fittingLengths.rightLower + connectorWidth / 2));

    insulatorBodyBuilder.Add(insulatorBody, leftInsulator);
    insulatorBodyBuilder.Add(insulatorBody, rightInsulator);
    insulatorBodyBuilder.Add(insulatorBody, connector1);
    insulatorBodyBuilder.Add(insulatorBody, connector2);
  } else { // I型串
    insulatorBodyBuilder.Add(
        insulatorBody,
        create_single_insulator(
            gp_Pnt(0, 0,
                   -params.insulator.height - params.fittingLengths.leftUpper),
            leftCount,
            gp_Pnt(0, 0,
                   -params.insulator.height - params.fittingLengths.leftUpper -
                       params.fittingLengths.leftLower),
            params.insulator.height + params.fittingLengths.leftUpper +
                params.fittingLengths.leftLower));
  }

  return insulatorBody;
}

} // namespace topo
} // namespace flywave
