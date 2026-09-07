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
// GIM 输电 (transmission) — 导线与弧垂 / 杆塔 / 绝缘子串 / 杆塔基础 / 锚具金具

namespace flywave {
namespace topo {


TopoDS_Shape create_insulator_string(const insulator_string_params &params) {
  // 参数验证（保持不变）
  if (params.count <= 0)
    throw Standard_ConstructionError("Count must be positive");
  if (params.spacing < 0)
    throw Standard_ConstructionError("Spacing must be non-negative");
  if (params.insulatorCount <= 0)
    throw Standard_ConstructionError("Insulator count must be positive");
  if (params.height <= 0.0)
    throw Standard_ConstructionError("Height must be positive");
  if (params.bigSkirtRadius < params.smallSkirtRadius)
    throw Standard_ConstructionError(
        "Big skirt radius must be >= small skirt radius");
  if (params.smallSkirtRadius <= params.radius)
    throw Standard_ConstructionError(
        "Small skirt radius must be > tube radius");
  if (params.radius <= 0.0)
    throw Standard_ConstructionError("Radius must be positive");
  if (params.frontLength <= 0.0 || params.backLength <= 0.0)
    throw Standard_ConstructionError("Lengths must be positive");
  if (params.splitCount <= 0)
    throw Standard_ConstructionError("Split count must be positive");

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  // 计算总高度（X轴方向）
  double totalHeight = params.insulatorCount * params.height;

  // 如果是双联绝缘子，创建上部连接板
  if (params.count == 2) {
    // 创建框架杆（前端连接杆塔部分）
    gp_Ax2 frameAxis(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0));
    BRepPrimAPI_MakeCylinder frameRod(frameAxis, params.radius / 4,
                                      params.frontLength / 3);
    builder.Add(compound, frameRod.Shape());

    // 金具各部分高度比例（调整顺序）
    const double topTrapezoidRatio = 0.5;    // 上部梯形占50%
    const double middleRectRatio = 0.2;      // 中部矩形占20%
    const double bottomCylindersRatio = 0.3; // 下部圆柱占30%

    double offset = params.frontLength / 3;

    // 计算各部分绝对高度
    double topHeight = params.frontLength / 3 * 2 * topTrapezoidRatio;
    double middleHeight = params.frontLength / 3 * 2 * middleRectRatio;
    double bottomHeight = params.frontLength / 3 * 2 * bottomCylindersRatio;

    // 下部梯形连接板（最靠近绝缘子）
    double plateBottomWidth = params.radius * 1.5;             // 底部窄端
    double plateTopWidth = params.spacing + params.radius * 2; // 顶部宽端

    // 创建梯形剖面线（从下往上构建）
    BRepBuilderAPI_MakeWire trapezoidWire;
    gp_Pnt p1(offset, -plateBottomWidth / 2, params.radius / 4);
    gp_Pnt p2(offset, plateBottomWidth / 2, params.radius / 4);
    gp_Pnt p3(offset + topHeight, plateTopWidth / 2, params.radius / 4);
    gp_Pnt p4(offset + topHeight, -plateTopWidth / 2, params.radius / 4);

    trapezoidWire.Add(BRepBuilderAPI_MakeEdge(p1, p2));
    trapezoidWire.Add(BRepBuilderAPI_MakeEdge(p2, p3));
    trapezoidWire.Add(BRepBuilderAPI_MakeEdge(p3, p4));
    trapezoidWire.Add(BRepBuilderAPI_MakeEdge(p4, p1));

    // 拉伸梯形成为实体（Z方向厚度为半径的1.5倍）
    TopoDS_Shape trapezoidPlate =
        BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(trapezoidWire.Wire()),
                              gp_Vec(0, 0, -params.radius / 2));
    builder.Add(compound, trapezoidPlate);

    // 中部矩形连接板（在梯形上方）
    double rectWidth = params.spacing + params.radius * 2;
    BRepPrimAPI_MakeBox middleRect(
        gp_Pnt(offset + topHeight, -rectWidth / 2, -params.radius / 4),
        gp_Pnt(offset + topHeight + middleHeight, rectWidth / 2,
               params.radius / 4));
    builder.Add(compound, middleRect.Shape());

    // 上部两个圆柱形连接杆（最顶端）
    double cylinderYOffset = params.spacing / 2;
    for (int i = 0; i < 2; ++i) {
      double yPos = (i == 0) ? cylinderYOffset : -cylinderYOffset;
      gp_Ax2 cylAxis(gp_Pnt(offset + topHeight + middleHeight, yPos, 0),
                     gp_Dir(1, 0, 0));

      BRepPrimAPI_MakeCylinder connectorCyl(cylAxis, params.radius / 3,
                                            topHeight);
      builder.Add(compound, connectorCyl.Shape());
    }

  } else {
    // 单联情况保持原样
    gp_Ax2 wireAxis(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0));
    BRepPrimAPI_MakeCylinder wireRod(wireAxis, params.radius / 4,
                                     params.frontLength);
    builder.Add(compound, wireRod.Shape());
  }

  // 创建绝缘子串
  for (int i = 0; i < params.count; ++i) {
    // 计算Y轴偏移（对称分布）
    double yOffset = (i == 0) ? params.spacing / 2 : -params.spacing / 2;

    // 创建绝缘子串
    for (int j = 0; j < params.insulatorCount; ++j) {
      // 计算当前X轴位置
      double xPos = j * params.height + params.frontLength;

      // 创建绝缘子圆柱（X轴方向）
      gp_Ax2 insulatorAxis(gp_Pnt(xPos, yOffset, 0), gp_Dir(1, 0, 0));
      TopoDS_Shape insulator =
          BRepPrimAPI_MakeCylinder(insulatorAxis, params.radius, params.height)
              .Shape();
      builder.Add(compound, insulator);

      // 伞裙生成（保持不变）
      double skirtRadius =
          (j % 2 == 0) ? params.bigSkirtRadius : params.smallSkirtRadius;

      BRepBuilderAPI_MakeWire wire;
      gp_Pnt basePoint(xPos + params.height * 0.2, yOffset, params.radius);
      gp_Pnt p1(xPos + params.height * 0.3, yOffset, skirtRadius);
      gp_Pnt p2(xPos + params.height * 0.1, yOffset, skirtRadius * 0.95);
      gp_Pnt p3(xPos, yOffset, skirtRadius * 0.7);
      gp_Pnt endPoint(xPos + params.height * 0.1, yOffset, params.radius);

      wire.Add(BRepBuilderAPI_MakeEdge(basePoint, p1));
      wire.Add(BRepBuilderAPI_MakeEdge(p1, p2));
      wire.Add(BRepBuilderAPI_MakeEdge(p2, p3));
      wire.Add(BRepBuilderAPI_MakeEdge(p3, endPoint));
      wire.Add(BRepBuilderAPI_MakeEdge(endPoint, basePoint));

      gp_Ax1 rotAxis(gp_Pnt(xPos, yOffset, 0), gp_Dir(1, 0, 0));
      TopoDS_Shape skirt =
          BRepPrimAPI_MakeRevol(BRepLib_MakeFace(wire.Wire()).Face(), rotAxis)
              .Shape();
      builder.Add(compound, skirt);
    }
  }

  if (params.count == 2) {
    // 金具各部分高度比例（调整顺序）
    const double topCylindersRatio = 0.4; // 上部圆柱占40%
    const double middleRectRatio = 0.6;   // 中部矩形占60%

    // 计算各部分绝对高度
    double topHeight = params.backLength * 0.6 * topCylindersRatio;
    double middleHeight = params.backLength * 0.6 * middleRectRatio;

    // 上部两个圆柱形连接杆（最顶端）
    double cylinderYOffset = params.spacing / 2;
    for (int i = 0; i < 2; ++i) {
      double yPos = (i == 0) ? cylinderYOffset : -cylinderYOffset;
      gp_Ax2 cylAxis(gp_Pnt(params.frontLength + totalHeight, yPos, 0),
                     gp_Dir(1, 0, 0));

      BRepPrimAPI_MakeCylinder connectorCyl(cylAxis, params.radius / 3,
                                            topHeight);
      builder.Add(compound, connectorCyl.Shape());
    }

    // 中部矩形连接板
    double rectWidth = params.spacing + params.radius * 2;
    BRepPrimAPI_MakeBox middleRect(
        gp_Pnt(params.frontLength + totalHeight + topHeight, -rectWidth / 2,
               -params.radius / 4),
        gp_Pnt(params.frontLength + totalHeight + topHeight + middleHeight,
               rectWidth / 2, params.radius / 4));
    builder.Add(compound, middleRect.Shape());

    if (params.splitCount == 2) {
      for (int i = 0; i < 2; ++i) {
        double yPos = (i == 0) ? cylinderYOffset : -cylinderYOffset;
        gp_Ax2 cylAxis(
            gp_Pnt(totalHeight + params.frontLength + (params.backLength * 0.6),
                   yPos, 0),
            gp_Dir(1, 0, 0));

        BRepPrimAPI_MakeCylinder connectorCyl(cylAxis, params.radius / 3,
                                              params.backLength * 0.4);
        builder.Add(compound, connectorCyl.Shape());
      }
    } else {
      // 单联情况保持原样
      gp_Ax2 wireAxis(
          gp_Pnt(totalHeight + params.frontLength + (params.backLength * 0.6),
                 0, 0),
          gp_Dir(1, 0, 0));
      BRepPrimAPI_MakeCylinder wireRod(wireAxis, params.radius / 4,
                                       params.backLength * 0.4);
      builder.Add(compound, wireRod.Shape());
    }

  } else {
    if (params.splitCount == 2) {
      // 下部梯形连接板（最靠近绝缘子）
      double plateBottomWidth = params.radius * 4; // 底部窄端
      double plateTopWidth = params.radius / 3;    // 顶部宽端

      // 创建梯形剖面线（从下往上构建）
      BRepBuilderAPI_MakeWire trapezoidWire;
      gp_Pnt p1(params.frontLength + totalHeight + params.backLength / 2,
                -plateBottomWidth / 2, params.radius / 4);
      gp_Pnt p2(params.frontLength + totalHeight + params.backLength / 2,
                plateBottomWidth / 2, params.radius / 4);
      gp_Pnt p3(params.frontLength + totalHeight, plateTopWidth / 2,
                params.radius / 4);
      gp_Pnt p4(params.frontLength + totalHeight, -plateTopWidth / 2,
                params.radius / 4);

      trapezoidWire.Add(BRepBuilderAPI_MakeEdge(p1, p2));
      trapezoidWire.Add(BRepBuilderAPI_MakeEdge(p2, p3));
      trapezoidWire.Add(BRepBuilderAPI_MakeEdge(p3, p4));
      trapezoidWire.Add(BRepBuilderAPI_MakeEdge(p4, p1));

      // 拉伸梯形成为实体（Z方向厚度为半径的1.5倍）
      TopoDS_Shape trapezoidPlate =
          BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(trapezoidWire.Wire()),
                                gp_Vec(0, 0, -params.radius / 2));
      builder.Add(compound, trapezoidPlate);

      for (int i = 0; i < 2; ++i) {
        double yPos = (i == 0) ? params.radius * 2 - (params.radius / 4)
                               : -params.radius * 2 + (params.radius / 4);
        gp_Ax2 cylAxis(
            gp_Pnt(params.frontLength + totalHeight + params.backLength / 2,
                   yPos, 0),
            gp_Dir(1, 0, 0));

        BRepPrimAPI_MakeCylinder connectorCyl(cylAxis, params.radius / 4,
                                              params.backLength / 2);
        builder.Add(compound, connectorCyl.Shape());
      }
    } else {
      // 单联情况保持原样
      gp_Ax2 wireAxis(gp_Pnt(params.frontLength + totalHeight, 0, 0),
                      gp_Dir(1, 0, 0));
      BRepPrimAPI_MakeCylinder wireRod(wireAxis, params.radius / 4,
                                       params.backLength);
      builder.Add(compound, wireRod.Shape());
    }
  }

  return compound;
}


TopoDS_Shape create_insulator_string(const insulator_string_params &params,
                                     const gp_Pnt &position,
                                     const gp_Dir &direction,
                                     const gp_Dir &upDirection) {
  // 首先创建标准方向的绝缘子串
  TopoDS_Shape insulator = create_insulator_string(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0), gp_Dir(1, 0, 0));
  gp_Ax3 targetAx3(position, direction, upDirection);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(insulator, transformation);
  return transform.Shape();
}


TopoDS_Shape create_vtype_insulator(const vtype_insulator_params &params) {
  // 参数验证
  if (params.frontSpacing <= 0.0 || params.backSpacing <= 0.0) {
    throw Standard_ConstructionError("Spacing must be positive");
  }
  if (params.insulatorCount <= 0) {
    throw Standard_ConstructionError("Insulator count must be positive");
  }
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
  if (params.smallSkirtRadius <= 0.0) {
    throw Standard_ConstructionError("Small skirt radius must be positive");
  }
  if (params.frontLength <= 0.0 || params.backLength <= 0.0) {
    throw Standard_ConstructionError("Lengths must be positive");
  }
  if (params.splitCount <= 0) {
    throw Standard_ConstructionError("Split count must be positive");
  }
  // 创建结果复合体
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  // 计算基本参数
  double total_insulator_height = params.insulatorCount * params.height;
  double half_front_spacing = params.frontSpacing / 2.0;
  double half_back_spacing = params.backSpacing / 2.0;

  double hypotenuse =
      params.frontLength + params.backLength + total_insulator_height;
  double actual_height =
      sqrt(pow(hypotenuse, 2) -
           pow(half_front_spacing - half_back_spacing, 2)); // 已有计算

  // 创建原点坐标系 (原点在V型张开端两前段连线中点)
  gp_Pnt origin(0, 0, 0);
  gp_Dir yDir(0, 1, 0); // Y轴方向为两前段连线方向
  gp_Dir zDir(0, 0, 1); // Z轴向上
  gp_Ax2 baseCS(origin, zDir, yDir);

  // 创建绝缘子串 (两侧各一串)
  for (int side = -1; side <= 1; side += 2) {
    // 计算绝缘子串起点和终点
    gp_Pnt front_point(0, side * half_front_spacing, 0);
    gp_Pnt end_point(actual_height, side * half_back_spacing, 0);

    // 创建绝缘子串路径
    gp_XYZ insulator_dir(end_point.X() - front_point.X(),
                         end_point.Y() - front_point.Y(),
                         end_point.Z() - front_point.Z());
    gp_XYZ front_dir(front_point.X() - end_point.X(),
                     front_point.Y() - end_point.Y(),
                     front_point.Z() - end_point.Z());

    gp_Vec front_dir_normalized =
        gp_Vec(insulator_dir).Normalized(); // 归一化方向向量
    gp_Pnt start_point =
        front_point.Translated(front_dir_normalized * params.frontLength);

    gp_XYZ insulator_len(end_point.X() - start_point.X(),
                         end_point.Y() - start_point.Y(),
                         end_point.Z() - start_point.Z());
    // 前端连接
    BRepPrimAPI_MakeCylinder frontCyl(
        gp_Ax2(front_point, gp_Dir(gp_Vec(insulator_dir).Normalized())),
        params.radius / 4, params.frontLength);
    builder.Add(result, frontCyl.Shape());

    // 后端连接
    BRepPrimAPI_MakeCylinder backCyl(
        gp_Ax2(end_point, gp_Dir(gp_Vec(insulator_dir).Normalized())),
        params.radius / 4, params.backLength);
    builder.Add(result, backCyl.Shape());

    // 创建每片绝缘子
    for (int i = 0; i < params.insulatorCount; i++) {
      double ratio_start = (double)i / params.insulatorCount;
      double ratio_end = (double)(i + 1) / params.insulatorCount;

      gp_Pnt segment_start(start_point.X() + insulator_len.X() * ratio_start,
                           start_point.Y() + insulator_len.Y() * ratio_start,
                           start_point.Z() + insulator_len.Z() * ratio_start);

      gp_Pnt segment_end(start_point.X() + insulator_len.X() * ratio_end,
                         start_point.Y() + insulator_len.Y() * ratio_end,
                         start_point.Z() + insulator_len.Z() * ratio_end);

      // 创建绝缘子柱体
      gp_Vec segment_vec(segment_end.X() - segment_start.X(),
                         segment_end.Y() - segment_start.Y(),
                         segment_end.Z() - segment_start.Z());

      // 创建绝缘子柱芯（新增部分）
      gp_Ax2 cylinderAxis(segment_start, gp_Dir(segment_vec));
      TopoDS_Shape cylinder =
          BRepPrimAPI_MakeCylinder(cylinderAxis,
                                   params.radius,          // 使用绝缘子半径参数
                                   segment_vec.Magnitude() // 实际长度
                                   )
              .Shape();
      builder.Add(result, cylinder);

      // 新伞裙生成方式（5点曲线剖面）
      double skirtRadius =
          (i % 2 == 0) ? params.bigSkirtRadius : params.smallSkirtRadius;

      // 在绝缘子轴线坐标系中创建剖面线
      BRepBuilderAPI_MakeWire skirtWire;

      gp_Pnt basePoint(segment_start.X() + params.height * 0.8,
                       segment_start.Y(),
                       params.radius); // 外缘点
      gp_Pnt p1(segment_start.X() + params.height * 0.8, segment_start.Y(),
                skirtRadius); // 外缘点
      gp_Pnt p2(segment_start.X() + params.height * 0.7, segment_start.Y(),
                skirtRadius * 0.95); // 上翘
      gp_Pnt p3(segment_start.X() + params.height * 0.5, segment_start.Y(),
                skirtRadius * 0.7); // 下凹
      gp_Pnt endPoint(segment_start.X() + params.height * 0.5,
                      segment_start.Y(),
                      params.radius); // 外缘点

      skirtWire.Add(BRepBuilderAPI_MakeEdge(basePoint, p1));
      skirtWire.Add(BRepBuilderAPI_MakeEdge(p1, p2));
      skirtWire.Add(BRepBuilderAPI_MakeEdge(p2, p3));
      skirtWire.Add(BRepBuilderAPI_MakeEdge(p3, endPoint));
      skirtWire.Add(BRepBuilderAPI_MakeEdge(endPoint, basePoint));

      // 创建旋转轴（沿绝缘子轴线方向）
      gp_Ax1 rotAxis(segment_start, segment_vec.Normalized());

      // 生成旋转体（360度旋转）
      BRepPrimAPI_MakeRevol skirtRevol(
          BRepLib_MakeFace(skirtWire.Wire()).Face(), rotAxis);
      if (!skirtRevol.IsDone()) {
        throw Standard_ConstructionError("Failed to create insulator skirt");
      }

      // 将伞裙添加到结果
      builder.Add(result, skirtRevol.Shape());
    }
  }
  {
    // 计算盒体尺寸（需覆盖两后端连接点间距）
    double box_x_length = params.backSpacing;     // X方向覆盖间距
    double box_y_thickness = params.radius * 0.8; // Y方向厚度
    double box_z_height = params.radius * 0.8;    // Z方向高度

    // 计算连接盒参数
    gp_Pnt box_center(actual_height + params.radius * 2,
                      -box_x_length / 2, // 使用计算后的实际高度
                      -box_z_height / 2);

    // 创建连接盒坐标系（Y轴保持与绝缘子走向一致）
    gp_Ax2 box_axis(box_center, gp_Dir(1, 0, 0), // 主方向(Y)与绝缘子走向一致
                    gp_Dir(0, 1, 0)              // Z轴保持垂直
    );

    // 创建连接盒（参数顺序：X长度，Y长度，Z长度）
    BRepPrimAPI_MakeBox connector_box(box_axis,
                                      box_x_length,    // X方向尺寸（沿全局X轴）
                                      box_y_thickness, // Y方向尺寸（沿全局Y轴）
                                      box_z_height     // Z方向尺寸（沿全局Z轴）
    );

    connector_box.Build();
    // 验证盒体创建
    if (!connector_box.IsDone()) {
      throw Standard_ConstructionError("Failed to create connector box");
    }

    builder.Add(result, connector_box.Shape());
  }
  return result;
}


TopoDS_Shape create_vtype_insulator(const vtype_insulator_params &params,
                                    const gp_Pnt &position,
                                    const gp_Dir &direction,
                                    const gp_Dir &upDirection) {
  // 首先创建标准方向的V型绝缘子串
  TopoDS_Shape insulator = create_vtype_insulator(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0), gp_Dir(1, 0, 0));
  gp_Ax3 targetAx3(position, direction, upDirection);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(insulator, transformation);
  return transform.Shape();
}


TopoDS_Shape create_rounded_base(double D, double H4, double z_bottom) {
  // 1. 定义母线（圆弧）
  const double R = (D * D + 4 * H4 * H4) / (8 * H4);
  Handle(Geom_TrimmedCurve) profile =
      GC_MakeArcOfCircle(gp_Pnt(D / 2, 0, z_bottom),
                         gp_Pnt(0, 0, z_bottom - H4),
                         gp_Pnt(-D / 2, 0, z_bottom))
          .Value();

  // 2. 创建旋转曲面
  Handle(Geom_SurfaceOfRevolution) revolSurface = new Geom_SurfaceOfRevolution(
      profile, gp_Ax1(gp_Pnt(0, 0, z_bottom), gp_Dir(0, 0, -1)) // 旋转轴
  );

  // 3. 转换为拓扑面
  TopoDS_Face face =
      BRepBuilderAPI_MakeFace(revolSurface, Precision::Confusion()).Face();

  BRepBuilderAPI_MakeWire wireMaker(BRepBuilderAPI_MakeEdge(
      new Geom_Circle(gp_Ax2(gp_Pnt(0, 0, z_bottom), gp_Dir(0, 0, 1)), D / 2)));

  // 4. 封闭底部（添加圆形平面）
  TopoDS_Face bottom_face = BRepBuilderAPI_MakeFace(wireMaker.Wire()).Face();

  // 5. 缝合为壳体
  BRepBuilderAPI_Sewing sewer;
  sewer.Add(face);
  sewer.Add(bottom_face);
  sewer.Perform();
  TopoDS_Shell shell = TopoDS::Shell(sewer.SewedShape());

  // 6. 转换为实体
  BRepBuilderAPI_MakeSolid solidMaker(shell);
  if (!solidMaker.IsDone()) {
    throw Standard_ConstructionError("实体转换失败");
  }
  return solidMaker.Shape();
}


/**
 * @brief 创建挖孔桩基础/灌注桩单桩基础
 * @param params 基础参数结构体
 * @return TopoDS_Shape 生成的基础形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_bored_pile_base(const bored_pile_params &params) {
  // 参数验证
  if (params.H1 <= 0 || params.H2 <= 0 || params.H3 <= 0 || params.H4 <= 0) {
    throw Standard_ConstructionError("所有高度参数必须为正数");
  }
  if (params.d <= 0 || params.D <= 0) {
    throw Standard_ConstructionError("直径参数必须为正数");
  }
  if (params.D < params.d) {
    throw Standard_ConstructionError("底部直径D不能小于上部直径d");
  }

  // 计算HA段高度
  const double HA = params.H1 - params.H3 + params.H2;
  if (HA <= 0) {
    throw Standard_ConstructionError("HA高度必须为正数 (H1 + H2 > H3)");
  }

  // 创建HA段（上部圆柱段）
  const gp_Ax2 ha_axis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -1));
  BRepPrimAPI_MakeCylinder ha_cylinder(ha_axis, params.d / 2, HA);

  // 创建过渡段（锥形段）
  TopoDS_Shape transition;
  if (params.D != params.d) {
    // 计算锥形段参数
    const double bottomRadius = params.D / 2; // 底部半径
    const double topRadius = params.d / 2;    // 顶部半径
    const double coneHeight = params.H2;      // 锥体高度

    // 创建锥形轴（从HA段底部向下延伸）
    const gp_Ax2 coneAxis(gp_Pnt(0, 0, -HA), // 起始点：HA段底部位置
                          gp_Dir(0, 0, -1),  // 主方向：向下
                          gp_Dir(1, 0, 0));  // 参考方向：X轴

    // 直接生成锥形实体
    BRepPrimAPI_MakeCone coneMaker(coneAxis, topRadius, bottomRadius,
                                   coneHeight);
    coneMaker.Build(); // 显式构建

    if (!coneMaker.IsDone()) {
      throw Standard_ConstructionError("锥形段创建失败");
    }

    transition = coneMaker.Shape();
  }

  // 创建H3段（下部圆柱段）
  const gp_Ax2 h3_axis(gp_Pnt(0, 0, -(HA + params.H2)), gp_Dir(0, 0, -1));
  BRepPrimAPI_MakeCylinder h3_cylinder(h3_axis, params.D / 2, params.H3);
  // H4段构建部分(H4段为一个圆底)
  const double z_h3_bottom = -(HA + params.H2 + params.H3);
  auto h4Shape = create_rounded_base(params.D, params.H4, z_h3_bottom);

  // 组合所有部件
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  builder.Add(result, ha_cylinder.Shape());
  if (params.D != params.d)
    builder.Add(result, transition);
  builder.Add(result, h3_cylinder.Shape());
  builder.Add(result, h4Shape);

  return result;
}


/**
 * @brief 创建带定位的挖孔桩基础/灌注桩单桩基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_bored_pile_base(const bored_pile_params &params,
                                    const gp_Pnt &position,
                                    const gp_Dir &direction) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_bored_pile_base(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(position, direction);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(foundation, transformation);
  return transform.Shape();
}


/**
 * @brief 创建承台挖孔桩基础/灌注桩基础
 * @param params 基础参数结构体
 * @return TopoDS_Shape 生成的基础形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_pile_cap_base(const pile_cap_params &params) {
  // 参数验证
  if (params.H1 <= 0 || params.H2 <= 0 || params.H3 <= 0 || params.H4 <= 0 ||
      params.H5 <= 0 || params.H6 <= 0) {
    throw Standard_ConstructionError("高度参数必须为正数");
  }
  if (params.d <= 0 || params.D <= 0 || params.b <= 0 || params.B1 <= 0 ||
      params.L1 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }
  if (params.D < params.d) {
    throw Standard_ConstructionError("底部直径D不能小于上部直径d");
  }
  if (params.ZCOUNT <= 0) {
    throw Standard_ConstructionError("桩数量必须大于0");
  }

  // 创建承台
  TopoDS_Shape cap;
  if (params.cs == 0) { // 圆形承台柱
    gp_Ax2 axis(gp_Pnt(0, 0, -params.H1), gp_Dir(0, 0, 1));
    cap = BRepPrimAPI_MakeCylinder(axis, params.b / 2, params.H1).Shape();
  } else { // 方形承台柱
    BRepBuilderAPI_MakeWire wire;
    double halfB = params.b / 2;
    // 创建闭合矩形轮廓（四个顶点）
    gp_Pnt p1(-halfB, -halfB, -params.H1); // 左下角
    gp_Pnt p2(halfB, -halfB, -params.H1);  // 右下角
    gp_Pnt p3(halfB, halfB, -params.H1);   // 右上角
    gp_Pnt p4(-halfB, halfB, -params.H1);  // 左上角

    wire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge()); // 底边
    wire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge()); // 右边
    wire.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge()); // 顶边
    wire.Add(BRepBuilderAPI_MakeEdge(p4, p1).Edge()); // 左边（闭合）

    BRepBuilderAPI_MakeFace face(wire.Wire());
    if (!face.IsDone()) {
      throw Standard_ConstructionError("Failed to create square column face");
    }
    cap = BRepPrimAPI_MakePrism(face.Face(), gp_Vec(0, 0, params.H4)).Shape();
  }

  // 创建承台底板
  BRepBuilderAPI_MakeWire baseWire;
  double halfB1 = params.B1 / 2;
  double halfL1 = params.L1 / 2;
  gp_Pnt p1(-halfB1, -halfL1, -params.H1 - params.H2); // 左下角
  gp_Pnt p2(halfB1, -halfL1, -params.H1 - params.H2);  // 右下角
  gp_Pnt p3(halfB1, halfL1, -params.H1 - params.H2);   // 右上角
  gp_Pnt p4(-halfB1, halfL1, -params.H1 - params.H2);  // 左上角

  baseWire.Add(BRepBuilderAPI_MakeEdge(p1, p2)); // 底边
  baseWire.Add(BRepBuilderAPI_MakeEdge(p2, p3)); // 右边
  baseWire.Add(BRepBuilderAPI_MakeEdge(p3, p4)); // 顶边
  baseWire.Add(BRepBuilderAPI_MakeEdge(p4, p1)); // 左边（闭合）

  // ... 创建底板轮廓
  BRepBuilderAPI_MakeFace baseFace(baseWire.Wire());
  TopoDS_Shape base =
      BRepPrimAPI_MakePrism(baseFace.Face(), gp_Vec(0, 0, params.H2)).Shape();

  // 组合所有部件
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);
  builder.Add(result, cap);
  builder.Add(result, base);

  // 创建桩
  std::vector<TopoDS_Shape> piles;
  for (int i = 0; i < params.ZCOUNT; i++) {
    gp_Pnt position(params.ZPOSTARRAY[i].X(), params.ZPOSTARRAY[i].Y(),
                    params.ZPOSTARRAY[i].Z() - params.H1 - params.H2);

    // 创建单桩
    bored_pile_params pileParams;
    pileParams.H1 = params.H3;
    pileParams.H2 = params.H4;
    pileParams.H3 = params.H5;
    pileParams.H4 = params.H6;
    pileParams.d = params.d;
    pileParams.D = params.D;

    TopoDS_Shape pile = create_bored_pile_base(pileParams);

    // 移动桩到正确位置
    gp_Trsf transform;
    transform.SetTranslation(gp_Vec(position.X(), position.Y(), position.Z()));
    BRepBuilderAPI_Transform mover(pile, transform);
    piles.push_back(mover.Shape());
  }

  // 合并所有桩
  for (const auto &pile : piles) {
    builder.Add(result, pile);
  }

  // 应用偏心调整
  if (params.e1 != 0 || params.e2 != 0) {
    gp_Trsf eccTransform;
    eccTransform.SetTranslation(gp_Vec(params.e1, params.e2, 0));
    BRepBuilderAPI_Transform eccMover(result, eccTransform);
    return eccMover.Shape();
  }

  return result;
}


/**
 * @brief 创建带定位的承台挖孔桩基础/灌注桩基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_pile_cap_base(const pile_cap_params &params,
                                  const gp_Pnt &position,
                                  const gp_Dir &direction) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_pile_cap_base(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(position, direction);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(foundation, transformation);
  return transform.Shape();
}


/**
 * @brief 创建直锚式岩石锚桩基础
 * @param params 基础参数结构体
 * @return TopoDS_Shape 生成的基础形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_rock_anchor_base(const rock_anchor_params &params) {
  // 参数验证
  if (params.H1 <= 0 || params.H2 <= 0) {
    throw Standard_ConstructionError("高度参数必须为正数");
  }
  if (params.d <= 0 || params.B1 <= 0 || params.L1 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }
  if (params.ZCOUNT <= 0) {
    throw Standard_ConstructionError("锚桩数量必须大于0");
  }

  // 创建基础底板
  BRepBuilderAPI_MakeWire baseWire;
  double halfB1 = params.B1 / 2;
  double halfL1 = params.L1 / 2;

  gp_Pnt p1(-halfB1, -halfL1, -params.H1);
  gp_Pnt p2(halfB1, -halfL1, -params.H1);
  gp_Pnt p3(halfB1, halfL1, -params.H1);
  gp_Pnt p4(-halfB1, halfL1, -params.H1);

  baseWire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  baseWire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
  baseWire.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
  baseWire.Add(BRepBuilderAPI_MakeEdge(p4, p1).Edge());

  BRepBuilderAPI_MakeFace baseFace(baseWire.Wire());
  TopoDS_Shape base =
      BRepPrimAPI_MakePrism(baseFace.Face(), gp_Vec(0, 0, params.H1)).Shape();

  // 组合所有部件
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);
  builder.Add(result, base);

  // 创建锚桩
  for (int i = 0; i < params.ZCOUNT; i++) {
    gp_Pnt position(params.ZPOSTARRAY[i].X(), params.ZPOSTARRAY[i].Y(),
                    params.ZPOSTARRAY[i].Z() - params.H1 - params.H2);

    // 创建圆柱形锚桩
    gp_Ax2 axis(position, gp_Dir(0, 0, 1));
    TopoDS_Shape anchor =
        BRepPrimAPI_MakeCylinder(axis, params.d / 2, params.H2).Shape();
    builder.Add(result, anchor);
  }

  return result;
}


/**
 * @brief 创建带定位的直锚式岩石锚桩基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_rock_anchor_base(const rock_anchor_params &params,
                                     const gp_Pnt &position,
                                     const gp_Dir &direction) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_rock_anchor_base(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(position, direction);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(foundation, transformation);
  return transform.Shape();
}


/**
 * @brief 创建承台式岩石锚桩基础
 * @param params 基础参数结构体
 * @return TopoDS_Shape 生成的基础形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_rock_pile_cap_base(const rock_pile_cap_params &params) {
  // 参数验证
  if (params.H1 <= 0 || params.H2 <= 0 || params.H3 <= 0) {
    throw Standard_ConstructionError("高度参数必须为正数");
  }
  if (params.d <= 0 || params.b <= 0 || params.B1 <= 0 || params.L1 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }
  if (params.ZCOUNT <= 0) {
    throw Standard_ConstructionError("锚桩数量必须大于0");
  }

  // 创建承台柱
  TopoDS_Shape column;
  if (params.cs == 0) { // 圆形承台柱
    gp_Ax2 axis(gp_Pnt(0, 0, -params.H1), gp_Dir(0, 0, 1));
    column = BRepPrimAPI_MakeCylinder(axis, params.b / 2, params.H1).Shape();
  } else { // 方形承台柱
    BRepBuilderAPI_MakeWire wire;
    double halfB = params.b / 2;
    wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfB, -halfB, -params.H1),
                                     gp_Pnt(halfB, -halfB, -params.H1))
                 .Edge());
    wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfB, -halfB, -params.H1),
                                     gp_Pnt(halfB, halfB, -params.H1))
                 .Edge());
    wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfB, halfB, -params.H1),
                                     gp_Pnt(-halfB, halfB, -params.H1))
                 .Edge());
    wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfB, halfB, -params.H1),
                                     gp_Pnt(-halfB, -halfB, -params.H1))
                 .Edge());
    BRepBuilderAPI_MakeFace face(wire.Wire());
    column =
        BRepPrimAPI_MakePrism(face.Face(), gp_Vec(0, 0, params.H1)).Shape();
  }

  // 创建承台底板
  BRepBuilderAPI_MakeWire baseWire;
  double halfB1 = params.B1 / 2;
  double halfL1 = params.L1 / 2;
  baseWire.Add(
      BRepBuilderAPI_MakeEdge(gp_Pnt(-halfB1, -halfL1, -params.H1 - params.H2),
                              gp_Pnt(halfB1, -halfL1, -params.H1 - params.H2))
          .Edge());
  baseWire.Add(
      BRepBuilderAPI_MakeEdge(gp_Pnt(halfB1, -halfL1, -params.H1 - params.H2),
                              gp_Pnt(halfB1, halfL1, -params.H1 - params.H2))
          .Edge());
  baseWire.Add(
      BRepBuilderAPI_MakeEdge(gp_Pnt(halfB1, halfL1, -params.H1 - params.H2),
                              gp_Pnt(-halfB1, halfL1, -params.H1 - params.H2))
          .Edge());
  baseWire.Add(
      BRepBuilderAPI_MakeEdge(gp_Pnt(-halfB1, halfL1, -params.H1 - params.H2),
                              gp_Pnt(-halfB1, -halfL1, -params.H1 - params.H2))
          .Edge());
  BRepBuilderAPI_MakeFace baseFace(baseWire.Wire());
  TopoDS_Shape base =
      BRepPrimAPI_MakePrism(baseFace.Face(), gp_Vec(0, 0, params.H2)).Shape();

  // 组合所有部件
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);
  builder.Add(result, column);
  builder.Add(result, base);

  // 创建锚桩
  for (int i = 0; i < params.ZCOUNT; i++) {
    gp_Pnt position(params.ZPOSTARRAY[i].X(), params.ZPOSTARRAY[i].Y(),
                    params.ZPOSTARRAY[i].Z() - params.H1 - params.H2 -
                        params.H3);

    // 创建圆柱形锚桩
    gp_Ax2 axis(position, gp_Dir(0, 0, 1));
    TopoDS_Shape anchor =
        BRepPrimAPI_MakeCylinder(axis, params.d / 2, params.H3).Shape();
    builder.Add(result, anchor);
  }

  // 应用偏心调整
  if (params.e1 != 0 || params.e2 != 0) {
    gp_Trsf eccTransform;
    eccTransform.SetTranslation(gp_Vec(params.e1, params.e2, 0));
    BRepBuilderAPI_Transform eccMover(result, eccTransform);
    return eccMover.Shape();
  }

  return result;
}


/**
 * @brief 创建带定位的承台式岩石锚桩基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_rock_pile_cap_base(const rock_pile_cap_params &params,
                                       const gp_Pnt &position,
                                       const gp_Dir &direction) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_rock_pile_cap_base(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(position, direction);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(foundation, transformation);
  return transform.Shape();
}


/**
 * @brief 创建嵌固式岩石锚桩基础
 * @param params 基础参数结构体
 * @return TopoDS_Shape 生成的基础形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape
create_embedded_rock_anchor_base(const embedded_rock_anchor_params &params) {
  // 参数验证
  if (params.H1 <= 0 || params.H2 <= 0 || params.H3 <= 0) {
    throw Standard_ConstructionError("高度参数必须为正数");
  }
  if (params.d <= 0 || params.D <= 0) {
    throw Standard_ConstructionError("直径参数必须为正数");
  }
  if (params.D < params.d) {
    throw Standard_ConstructionError("底部直径D不能小于上部直径d");
  }

  // 创建上部圆柱段 (H1)
  gp_Ax2 axis1(gp_Pnt(0, 0, -params.H1), gp_Dir(0, 0, 1));
  TopoDS_Shape upperCylinder =
      BRepPrimAPI_MakeCylinder(axis1, params.d / 2, params.H1).Shape();

  // 创建底部圆柱段 (H3)
  gp_Ax2 axis2(gp_Pnt(0, 0, -params.H1 - params.H2 - params.H3),
               gp_Dir(0, 0, 1));
  TopoDS_Shape lowerCylinder =
      BRepPrimAPI_MakeCylinder(axis2, params.D / 2, params.H3).Shape();

  // 创建过渡段 (H2)
  TopoDS_Shape transition;
  if (params.D != params.d) {

    // 计算锥形段参数
    const double bottomRadius = params.D / 2; // 底部半径
    const double topRadius = params.d / 2;    // 顶部半径
    const double coneHeight = params.H2;      // 锥体高度

    // 创建锥形轴（从HA段底部向下延伸）
    const gp_Ax2 coneAxis(gp_Pnt(0, 0, -params.H1), // 起始点：HA段底部位置
                          gp_Dir(0, 0, -1),         // 主方向：向下
                          gp_Dir(1, 0, 0));         // 参考方向：X轴

    // 直接生成锥形实体
    BRepPrimAPI_MakeCone coneMaker(coneAxis, topRadius, bottomRadius,
                                   coneHeight);
    coneMaker.Build(); // 显式构建

    if (!coneMaker.IsDone()) {
      throw Standard_ConstructionError("锥形段创建失败");
    }

    transition = coneMaker.Shape();
  }

  // 组合所有部件
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);
  builder.Add(result, upperCylinder);
  builder.Add(result, lowerCylinder);

  if (params.D != params.d) {
    builder.Add(result, transition);
  }

  return result;
}


/**
 * @brief 创建带定位的嵌固式岩石锚桩基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape
create_embedded_rock_anchor_base(const embedded_rock_anchor_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_embedded_rock_anchor_base(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(position, direction);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(foundation, transformation);
  return transform.Shape();
}


/**
 * @brief 创建斜锚式岩石锚桩基础
 * @param params 基础参数结构体
 * @return TopoDS_Shape 生成的基础形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape
create_inclined_rock_anchor_base(const inclined_rock_anchor_params &params) {
  // 参数验证
  if (params.H1 <= 0 || params.H2 <= 0) {
    throw Standard_ConstructionError("高度参数必须为正数");
  }
  if (params.d <= 0 || params.D <= 0 || params.B <= 0 || params.L <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }
  if (params.D < params.d) {
    throw Standard_ConstructionError("底部直径D不能小于上部直径d");
  }

  // 创建基础底板
  BRepBuilderAPI_MakeWire baseWire;
  double halfB = params.B / 2;
  double halfL = params.L / 2;

  gp_Pnt p1(-halfB, -halfL, 0);
  gp_Pnt p2(halfB, -halfL, 0);
  gp_Pnt p3(halfB, halfL, 0);
  gp_Pnt p4(-halfB, halfL, 0);

  baseWire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  baseWire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
  baseWire.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
  baseWire.Add(BRepBuilderAPI_MakeEdge(p4, p1).Edge());

  BRepBuilderAPI_MakeFace baseFace(baseWire.Wire());
  TopoDS_Shape base =
      BRepPrimAPI_MakePrism(baseFace.Face(), gp_Vec(0, 0, -params.H1)).Shape();

  // 计算斜度方向向量
  double tanAlpha1 = tan(params.alpha1 * M_PI / 180.0);
  double tanAlpha2 = tan(params.alpha2 * M_PI / 180.0);
  gp_Vec slopeDir(tanAlpha1, tanAlpha2, 1.0);
  slopeDir.Normalize();

  // 创建斜圆台路径
  gp_Pnt startPoint(0, 0, -params.H1);
  gp_Pnt endPoint = startPoint.Translated(slopeDir * -params.H2);

  BRepBuilderAPI_MakeEdge pathEdge(startPoint, endPoint);
  BRepBuilderAPI_MakeWire pathWire(pathEdge);

  // 创建截面轮廓（从d渐变到D的圆）
  BRepBuilderAPI_MakeWire sectionWire;
  Handle(Geom_Circle) startCircle =
      new Geom_Circle(gp_Ax2(startPoint, slopeDir), params.d / 2);
  Handle(Geom_Circle) endCircle =
      new Geom_Circle(gp_Ax2(endPoint, slopeDir), params.D / 2);

  // 创建斜圆台
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.SetMode(Standard_True); // 使用渐变模式
  pipeMaker.Add(BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(startCircle)));
  pipeMaker.Add(BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(endCircle)));
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("斜圆台创建失败");
  }
  if (!pipeMaker.MakeSolid()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }

  TopoDS_Shape slopedAnchor = pipeMaker.Shape();

  // 组合所有部件
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);
  builder.Add(result, base);
  builder.Add(result, slopedAnchor);

  // 应用偏心调整
  if (params.e1 != 0 || params.e2 != 0) {
    gp_Trsf eccTransform;
    eccTransform.SetTranslation(gp_Vec(params.e1, params.e2, 0));
    BRepBuilderAPI_Transform eccMover(result, eccTransform);
    return eccMover.Shape();
  }

  return result;
}


/**
 * @brief 创建带定位的斜锚式岩石锚桩基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape
create_inclined_rock_anchor_base(const inclined_rock_anchor_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_inclined_rock_anchor_base(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(position, direction);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(foundation, transformation);
  return transform.Shape();
}


/**
 * @brief 创建掏挖基础
 * @param params 基础参数结构体
 * @return TopoDS_Shape 生成的基础形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_excavated_base(const excavated_base_params &params) {
  // 参数验证
  if (params.H1 <= 0 || params.H2 <= 0 || params.H3 <= 0) {
    throw Standard_ConstructionError("高度参数必须为正数");
  }
  if (params.d <= 0 || params.D <= 0) {
    throw Standard_ConstructionError("直径参数必须为正数");
  }
  if (params.D < params.d) {
    throw Standard_ConstructionError("底部直径D不能小于上部直径d");
  }

  // 计算单位化的斜率向量（方向向下）
  double tanAlpha1 = tan(params.alpha1 * M_PI / 180.0);
  double tanAlpha2 = tan(params.alpha2 * M_PI / 180.0);
  gp_Vec slopeVec(tanAlpha1, tanAlpha2, 1.0); // 原始向量
  slopeVec.Normalize();                       // 单位化
  slopeVec.Reverse();                         // 将方向调整为向下

  // 创建H1段（斜圆柱，顶部中心在原点）
  gp_Pnt h1Top(0, 0, 0); // 顶部中心始终在原点
  gp_Pnt h1Bottom = h1Top.Translated(slopeVec * params.H1);
  gp_Ax2 h1Axis(h1Top, gp_Dir(slopeVec)); // 轴从原点沿反向延伸
  TopoDS_Shape h1Cylinder =
      BRepPrimAPI_MakeCylinder(h1Axis, params.d / 2, params.H1).Shape();

  // 创建H2段（垂直偏心圆台）
  gp_Pnt h2Start = h1Bottom;
  gp_Pnt h2End = h2Start.Translated(gp_Vec(0, 0, -params.H2));

  BRepOffsetAPI_MakePipeShell pipeMaker(
      BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(h2Start, h2End)));
  pipeMaker.SetMode(Standard_True); // 渐变模式

  // 上部截面（与H1段直径相同）
  Handle(Geom_Circle) topCircle =
      new Geom_Circle(gp_Ax2(h2Start, gp_Dir(0, 0, 1)), params.d / 2);
  pipeMaker.Add(BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(topCircle)));

  // 下部截面（与H3段直径相同）
  Handle(Geom_Circle) bottomCircle =
      new Geom_Circle(gp_Ax2(h2End, gp_Dir(0, 0, 1)), params.D / 2);
  pipeMaker.Add(BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(bottomCircle)));

  pipeMaker.Build();
  if (!pipeMaker.IsDone()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }
  if (!pipeMaker.MakeSolid()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }

  TopoDS_Shape h2Transition = pipeMaker.Shape();

  // 创建H3段（垂直圆柱）
  gp_Ax2 h3Axis(h2End, gp_Dir(0, 0, -1));
  TopoDS_Shape h3Cylinder =
      BRepPrimAPI_MakeCylinder(h3Axis, params.D / 2, params.H3).Shape();

  // 组合所有部件
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);
  builder.Add(result, h1Cylinder);
  builder.Add(result, h2Transition);
  builder.Add(result, h3Cylinder);

  return result;
}


/**
 * @brief 创建带定位的掏挖基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_excavated_base(const excavated_base_params &params,
                                   const gp_Pnt &position,
                                   const gp_Dir &direction) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_excavated_base(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(position, direction);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(foundation, transformation);
  return transform.Shape();
}


/**
 * @brief 创建台阶基础
 * @param params 基础参数结构体
 * @return TopoDS_Shape 生成的基础形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_step_base(const step_base_params &params) {
  // 参数验证
  if (params.H < 0 || params.H1 < 0 || params.H2 < 0 || params.H3 < 0) {
    throw Standard_ConstructionError("高度参数必须为正数");
  }
  if (params.b <= 0 || params.B1 < 0 || params.B2 < 0 || params.B3 < 0 ||
      params.L1 < 0 || params.L2 < 0 || params.L3 < 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }
  if (params.N <= 0) {
    throw Standard_ConstructionError("台阶数必须大于0");
  }

  // 创建基础主体 (从原点向下延伸)
  BRepBuilderAPI_MakeWire baseWire;
  double halfB = params.b / 2;

  // 创建矩形轮廓的四个边 (Z坐标为0到-H)
  gp_Pnt p1(-halfB, -halfB, 0); // 左下角
  gp_Pnt p2(halfB, -halfB, 0);  // 右下角
  gp_Pnt p3(halfB, halfB, 0);   // 右上角
  gp_Pnt p4(-halfB, halfB, 0);  // 左上角

  baseWire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  baseWire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
  baseWire.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
  baseWire.Add(BRepBuilderAPI_MakeEdge(p4, p1).Edge());

  BRepBuilderAPI_MakeFace baseFace(baseWire.Wire());
  TopoDS_Shape foundation =
      BRepPrimAPI_MakePrism(baseFace.Face(), gp_Vec(0, 0, -params.H)).Shape();

  // 组合所有部件
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);
  builder.Add(result, foundation);

  // 创建台阶 (从-H开始向下堆叠)
  std::vector<double> heights = {params.H1, params.H2, params.H3};
  std::vector<double> widths = {params.B1, params.B2, params.B3};
  std::vector<double> lengths = {params.L1, params.L2, params.L3};

  double currentHeight = -params.H; // 从基础底部开始
  for (int i = 0; i < params.N && i < 3; i++) {
    if (heights[i] <= 0)
      continue;

    double halfWidth = widths[i] / 2;
    double halfLength = lengths[i] / 2;

    // 创建台阶 (Z坐标为currentHeight到currentHeight-heights[i])
    BRepBuilderAPI_MakeWire stepWire;
    gp_Pnt p1(-halfWidth, -halfLength, currentHeight);
    gp_Pnt p2(halfWidth, -halfLength, currentHeight);
    gp_Pnt p3(halfWidth, halfLength, currentHeight);
    gp_Pnt p4(-halfWidth, halfLength, currentHeight);

    stepWire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
    stepWire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
    stepWire.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
    stepWire.Add(BRepBuilderAPI_MakeEdge(p4, p1).Edge());

    BRepBuilderAPI_MakeFace stepFace(stepWire.Wire());
    TopoDS_Shape step =
        BRepPrimAPI_MakePrism(stepFace.Face(), gp_Vec(0, 0, -heights[i]))
            .Shape();

    builder.Add(result, step);
    currentHeight -= heights[i]; // 向下堆叠
  }
  return result;
}


/**
 * @brief 创建带定位的台阶基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_step_base(const step_base_params &params,
                              const gp_Pnt &position, const gp_Dir &direction) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_step_base(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(position, direction);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(foundation, transformation);
  return transform.Shape();
}


/**
 * @brief 创建台阶底板基础
 * @param params 基础参数结构体
 * @return TopoDS_Shape 生成的基础形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_step_plate_base(const step_plate_base_params &params) {
  // 参数验证
  if (params.H <= 0 || params.H1 < 0 || params.H2 < 0) {
    throw Standard_ConstructionError("高度参数必须为正数");
  }
  if (params.b <= 0 || params.L1 < 0 || params.L2 < 0 || params.B1 < 0 ||
      params.B2 < 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }
  if (params.N < 1 || params.N > 3) {
    throw Standard_ConstructionError("台阶数量必须为1-3");
  }

  // 组合所有部件
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  gp_Pnt columnBottom(0, 0, 0); // 柱底中心点初始化为原点
  // 处理柱体部分 (直柱或斜柱)
  TopoDS_Shape column;
  if (params.alpha1 == 0 && params.alpha2 == 0) {
    // 直柱情况 - 创建矩形柱
    BRepBuilderAPI_MakeWire columnWire;
    double halfB = params.b / 2;
    columnWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfB, -halfB, 0),
                                           gp_Pnt(halfB, -halfB, 0))
                       .Edge());
    columnWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfB, -halfB, 0),
                                           gp_Pnt(halfB, halfB, 0))
                       .Edge());
    columnWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfB, halfB, 0),
                                           gp_Pnt(-halfB, halfB, 0))
                       .Edge());
    columnWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfB, halfB, 0),
                                           gp_Pnt(-halfB, -halfB, 0))
                       .Edge());

    BRepBuilderAPI_MakeFace columnFace(columnWire.Wire());
    column = BRepPrimAPI_MakePrism(columnFace.Face(), gp_Vec(0, 0, -params.H1))
                 .Shape();
    columnBottom = gp_Pnt(0, 0, -params.H1); // 直柱底部中心点
  } else {
    // 斜柱情况
    double tanAlpha1 = tan(params.alpha1 * M_PI / 180.0);
    double tanAlpha2 = tan(params.alpha2 * M_PI / 180.0);
    gp_Vec slopeDir(tanAlpha1, tanAlpha2, 1.0);
    slopeDir.Normalize();
    slopeDir.Reverse();

    gp_Pnt top(0, 0, 0);
    columnBottom = top.Translated(slopeDir * params.H1);

    // 创建斜矩形柱
    BRepOffsetAPI_ThruSections generator(Standard_True);

    // 顶部截面
    BRepBuilderAPI_MakeWire topWire;
    double halfB = params.b / 2;
    topWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfB, -halfB, 0),
                                        gp_Pnt(halfB, -halfB, 0))
                    .Edge());
    topWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfB, -halfB, 0),
                                        gp_Pnt(halfB, halfB, 0))
                    .Edge());
    topWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfB, halfB, 0),
                                        gp_Pnt(-halfB, halfB, 0))
                    .Edge());
    topWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfB, halfB, 0),
                                        gp_Pnt(-halfB, -halfB, 0))
                    .Edge());
    generator.AddWire(topWire.Wire());

    // 底部截面
    BRepBuilderAPI_MakeWire bottomWire;

    // 底部四个角点
    gp_Pnt b1 = gp_Pnt(-halfB, -halfB, 0).Translated(slopeDir * params.H1);
    gp_Pnt b2 = gp_Pnt(halfB, -halfB, 0).Translated(slopeDir * params.H1);
    gp_Pnt b3 = gp_Pnt(halfB, halfB, 0).Translated(slopeDir * params.H1);
    gp_Pnt b4 = gp_Pnt(-halfB, halfB, 0).Translated(slopeDir * params.H1);

    // 添加四条边
    bottomWire.Add(BRepBuilderAPI_MakeEdge(b1, b2).Edge()); // 底边
    bottomWire.Add(BRepBuilderAPI_MakeEdge(b2, b3).Edge()); // 右边
    bottomWire.Add(BRepBuilderAPI_MakeEdge(b3, b4).Edge()); // 顶边
    bottomWire.Add(BRepBuilderAPI_MakeEdge(b4, b1).Edge()); // 左边

    generator.AddWire(bottomWire.Wire());
    generator.Build();
    column = generator.Shape();
  }

  // 创建台阶 (从-H开始向下堆叠)
  gp_Pnt currentCenter = columnBottom; // 使用完整的柱底中心点坐标

  if (params.N >= 1 && params.H1 > 0) {
    // 第一级台阶
    double halfB1 = params.B1 / 2;
    double halfL1 = params.L1 / 2;

    BRepBuilderAPI_MakeWire step1Wire;
    gp_Pnt s1(currentCenter.X() - halfB1, currentCenter.Y() - halfL1,
              currentCenter.Z());
    gp_Pnt s2(currentCenter.X() + halfB1, currentCenter.Y() - halfL1,
              currentCenter.Z());
    gp_Pnt s3(currentCenter.X() + halfB1, currentCenter.Y() + halfL1,
              currentCenter.Z());
    gp_Pnt s4(currentCenter.X() - halfB1, currentCenter.Y() + halfL1,
              currentCenter.Z());

    step1Wire.Add(BRepBuilderAPI_MakeEdge(s1, s2).Edge());
    step1Wire.Add(BRepBuilderAPI_MakeEdge(s2, s3).Edge());
    step1Wire.Add(BRepBuilderAPI_MakeEdge(s3, s4).Edge());
    step1Wire.Add(BRepBuilderAPI_MakeEdge(s4, s1).Edge());

    BRepBuilderAPI_MakeFace step1Face(step1Wire.Wire());
    TopoDS_Shape step1 =
        BRepPrimAPI_MakePrism(step1Face.Face(), gp_Vec(0, 0, -params.H1))
            .Shape();

    builder.Add(result, step1);
    currentCenter.SetZ(currentCenter.Z() - params.H1);
  }

  if (params.N >= 2 && params.H2 > 0) {
    // 第二级台阶
    double halfB2 = params.B2 / 2;
    double halfL2 = params.L2 / 2;

    BRepBuilderAPI_MakeWire step2Wire;
    gp_Pnt s5(currentCenter.X() - halfB2, currentCenter.Y() - halfL2,
              currentCenter.Z());
    gp_Pnt s6(currentCenter.X() + halfB2, currentCenter.Y() - halfL2,
              currentCenter.Z());
    gp_Pnt s7(currentCenter.X() + halfB2, currentCenter.Y() + halfL2,
              currentCenter.Z());
    gp_Pnt s8(currentCenter.X() - halfB2, currentCenter.Y() + halfL2,
              currentCenter.Z());

    step2Wire.Add(BRepBuilderAPI_MakeEdge(s5, s6).Edge());
    step2Wire.Add(BRepBuilderAPI_MakeEdge(s6, s7).Edge());
    step2Wire.Add(BRepBuilderAPI_MakeEdge(s7, s8).Edge());
    step2Wire.Add(BRepBuilderAPI_MakeEdge(s8, s5).Edge());

    BRepBuilderAPI_MakeFace step2Face(step2Wire.Wire());
    TopoDS_Shape step2 =
        BRepPrimAPI_MakePrism(step2Face.Face(), gp_Vec(0, 0, -params.H2))
            .Shape();

    builder.Add(result, step2);
  }

  // 添加柱体
  builder.Add(result, column);

  return result;
}


/**
 * @brief 创建带定位的台阶底板基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_step_plate_base(const step_plate_base_params &params,
                                    const gp_Pnt &position,
                                    const gp_Dir &direction) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_step_plate_base(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(position, direction);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(foundation, transformation);
  return transform.Shape();
}


/**
 * @brief 创建斜坡底板基础
 * @param params 基础参数结构体
 * @return TopoDS_Shape 生成的基础形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_sloped_base_base(const sloped_base_base_params &params) {
  // 参数验证
  if (params.H1 <= 0 || params.H2 < 0 || params.H3 < 0) {
    throw Standard_ConstructionError("高度参数必须为正数");
  }
  if (params.b <= 0 || params.L1 <= 0 || params.L2 <= 0 || params.B1 <= 0 ||
      params.B2 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }

  // 组合所有部件
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  // 处理柱体部分 (直柱或斜柱)
  TopoDS_Shape column;
  gp_Pnt columnTop(0, 0, 0); // 柱顶中心点(原点)
  gp_Pnt columnBottom;       // 柱底中心点

  if (params.alpha1 == 0 && params.alpha2 == 0) {
    // 直柱情况
    gp_Ax2 axis(columnTop, gp_Dir(0, 0, -1));
    column = BRepPrimAPI_MakeCylinder(axis, params.b / 2, params.H1).Shape();
    columnBottom = gp_Pnt(0, 0, -params.H1);
  } else {
    // 斜柱情况
    double tanAlpha1 = tan(params.alpha1 * M_PI / 180.0);
    double tanAlpha2 = tan(params.alpha2 * M_PI / 180.0);
    gp_Vec slopeDir(tanAlpha1, tanAlpha2, 1.0);
    slopeDir.Normalize();
    slopeDir.Reverse();

    gp_Ax2 axis(columnTop, slopeDir);
    column = BRepPrimAPI_MakeCylinder(axis, params.b / 2, params.H1).Shape();
    columnBottom = columnTop.Translated(slopeDir * params.H1);
  }

  // 创建梯形台部分 (从柱底开始向下延伸)
  gp_Pnt currentCenter = columnBottom;
  double halfL2 = params.L2 / 2;
  double halfB2 = params.B2 / 2;

  // 梯形台顶部四边形 (与柱底中心对齐)
  BRepBuilderAPI_MakeWire topWire;
  gp_Pnt t1(currentCenter.X() - halfL2, currentCenter.Y() - halfB2,
            currentCenter.Z());
  gp_Pnt t2(currentCenter.X() + halfL2, currentCenter.Y() - halfB2,
            currentCenter.Z());
  gp_Pnt t3(currentCenter.X() + halfL2, currentCenter.Y() + halfB2,
            currentCenter.Z());
  gp_Pnt t4(currentCenter.X() - halfL2, currentCenter.Y() + halfB2,
            currentCenter.Z());

  topWire.Add(BRepBuilderAPI_MakeEdge(t1, t2).Edge());
  topWire.Add(BRepBuilderAPI_MakeEdge(t2, t3).Edge());
  topWire.Add(BRepBuilderAPI_MakeEdge(t3, t4).Edge());
  topWire.Add(BRepBuilderAPI_MakeEdge(t4, t1).Edge());

  // 梯形台底部四边形 (向下延伸H2)
  double halfL1 = params.L1 / 2;
  double halfB1 = params.B1 / 2;
  gp_Pnt bottomCenter = gp_Pnt(currentCenter.X(), currentCenter.Y(),
                               currentCenter.Z() - params.H2);

  BRepBuilderAPI_MakeWire bottomWire;
  gp_Pnt b1(bottomCenter.X() - halfL1, bottomCenter.Y() - halfB1,
            bottomCenter.Z());
  gp_Pnt b2(bottomCenter.X() + halfL1, bottomCenter.Y() - halfB1,
            bottomCenter.Z());
  gp_Pnt b3(bottomCenter.X() + halfL1, bottomCenter.Y() + halfB1,
            bottomCenter.Z());
  gp_Pnt b4(bottomCenter.X() - halfL1, bottomCenter.Y() + halfB1,
            bottomCenter.Z());

  bottomWire.Add(BRepBuilderAPI_MakeEdge(b1, b2).Edge());
  bottomWire.Add(BRepBuilderAPI_MakeEdge(b2, b3).Edge());
  bottomWire.Add(BRepBuilderAPI_MakeEdge(b3, b4).Edge());
  bottomWire.Add(BRepBuilderAPI_MakeEdge(b4, b1).Edge());

  // 创建梯形台侧面
  BRepOffsetAPI_ThruSections generator(Standard_True);
  generator.AddWire(topWire.Wire());
  generator.AddWire(bottomWire.Wire());
  generator.Build();
  TopoDS_Shape trapezoid = generator.Shape();

  // 创建底部矩形部分 (从梯形台底部向下延伸H3)
  BRepBuilderAPI_MakeWire rectWire;
  gp_Pnt r1(bottomCenter.X() - halfL1, bottomCenter.Y() - halfB1,
            bottomCenter.Z());
  gp_Pnt r2(bottomCenter.X() + halfL1, bottomCenter.Y() - halfB1,
            bottomCenter.Z());
  gp_Pnt r3(bottomCenter.X() + halfL1, bottomCenter.Y() + halfB1,
            bottomCenter.Z());
  gp_Pnt r4(bottomCenter.X() - halfL1, bottomCenter.Y() + halfB1,
            bottomCenter.Z());

  rectWire.Add(BRepBuilderAPI_MakeEdge(r1, r2).Edge());
  rectWire.Add(BRepBuilderAPI_MakeEdge(r2, r3).Edge());
  rectWire.Add(BRepBuilderAPI_MakeEdge(r3, r4).Edge());
  rectWire.Add(BRepBuilderAPI_MakeEdge(r4, r1).Edge());

  BRepBuilderAPI_MakeFace rectFace(rectWire.Wire());
  TopoDS_Shape rectangle =
      BRepPrimAPI_MakePrism(rectFace.Face(), gp_Vec(0, 0, -params.H3)).Shape();

  // 合并所有部件
  builder.Add(result, column);
  builder.Add(result, trapezoid);
  builder.Add(result, rectangle);

  return result;
}


/**
 * @brief 创建带定位的斜坡底板基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_sloped_base_base(const sloped_base_base_params &params,
                                     const gp_Pnt &position,
                                     const gp_Dir &direction) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_sloped_base_base(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(position, direction);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(foundation, transformation);
  return transform.Shape();
}


/**
 * @brief 创建复合式沉井基础
 * @param params 基础参数结构体
 * @return TopoDS_Shape 生成的基础形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape
create_composite_caisson_base(const composite_caisson_base_params &params) {
  // 参数验证
  if (params.H1 <= 0 || params.H2 <= 0 || params.H3 <= 0 || params.H4 <= 0) {
    throw Standard_ConstructionError("高度参数必须为正数");
  }
  if (params.b <= 0 || params.D <= 0 || params.t <= 0 || params.B1 <= 0 ||
      params.B2 <= 0 || params.L1 <= 0 || params.L2 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }

  // 组合所有部件
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  gp_Pnt currentCenter(0, 0, 0); // 原点位于H1顶部中心

  // 1. 创建H1部分(矩形柱)
  double halfB = params.b / 2;
  BRepBuilderAPI_MakeWire h1Wire;
  h1Wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfB, -halfB, 0),
                                     gp_Pnt(halfB, -halfB, 0))
                 .Edge());
  h1Wire.Add(
      BRepBuilderAPI_MakeEdge(gp_Pnt(halfB, -halfB, 0), gp_Pnt(halfB, halfB, 0))
          .Edge());
  h1Wire.Add(
      BRepBuilderAPI_MakeEdge(gp_Pnt(halfB, halfB, 0), gp_Pnt(-halfB, halfB, 0))
          .Edge());
  h1Wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfB, halfB, 0),
                                     gp_Pnt(-halfB, -halfB, 0))
                 .Edge());

  BRepBuilderAPI_MakeFace h1Face(h1Wire.Wire());
  TopoDS_Shape h1 =
      BRepPrimAPI_MakePrism(h1Face.Face(), gp_Vec(0, 0, -params.H1)).Shape();
  builder.Add(result, h1);
  currentCenter.SetZ(currentCenter.Z() - params.H1);

  // 2. 创建H2部分(第一级台阶)
  double halfL1 = params.L1 / 2;
  double halfB1 = params.B1 / 2;
  BRepBuilderAPI_MakeWire h2Wire;
  h2Wire.Add(
      BRepBuilderAPI_MakeEdge(gp_Pnt(-halfL1, -halfB1, currentCenter.Z()),
                              gp_Pnt(halfL1, -halfB1, currentCenter.Z()))
          .Edge());
  h2Wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfL1, -halfB1, currentCenter.Z()),
                                     gp_Pnt(halfL1, halfB1, currentCenter.Z()))
                 .Edge());
  h2Wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfL1, halfB1, currentCenter.Z()),
                                     gp_Pnt(-halfL1, halfB1, currentCenter.Z()))
                 .Edge());
  h2Wire.Add(
      BRepBuilderAPI_MakeEdge(gp_Pnt(-halfL1, halfB1, currentCenter.Z()),
                              gp_Pnt(-halfL1, -halfB1, currentCenter.Z()))
          .Edge());

  BRepBuilderAPI_MakeFace h2Face(h2Wire.Wire());
  TopoDS_Shape h2 =
      BRepPrimAPI_MakePrism(h2Face.Face(), gp_Vec(0, 0, -params.H2)).Shape();
  builder.Add(result, h2);
  currentCenter.SetZ(currentCenter.Z() - params.H2);

  // 3. 创建H3部分(第二级台阶)
  double halfL2 = params.L2 / 2;
  double halfB2 = params.B2 / 2;
  BRepBuilderAPI_MakeWire h3Wire;
  h3Wire.Add(
      BRepBuilderAPI_MakeEdge(gp_Pnt(-halfL2, -halfB2, currentCenter.Z()),
                              gp_Pnt(halfL2, -halfB2, currentCenter.Z()))
          .Edge());
  h3Wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfL2, -halfB2, currentCenter.Z()),
                                     gp_Pnt(halfL2, halfB2, currentCenter.Z()))
                 .Edge());
  h3Wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfL2, halfB2, currentCenter.Z()),
                                     gp_Pnt(-halfL2, halfB2, currentCenter.Z()))
                 .Edge());
  h3Wire.Add(
      BRepBuilderAPI_MakeEdge(gp_Pnt(-halfL2, halfB2, currentCenter.Z()),
                              gp_Pnt(-halfL2, -halfB2, currentCenter.Z()))
          .Edge());

  BRepBuilderAPI_MakeFace h3Face(h3Wire.Wire());
  TopoDS_Shape h3 =
      BRepPrimAPI_MakePrism(h3Face.Face(), gp_Vec(0, 0, -params.H3)).Shape();
  builder.Add(result, h3);
  currentCenter.SetZ(currentCenter.Z() - params.H3);

  // 4. 创建H4部分(圆管)
  gp_Ax2 axis(currentCenter, gp_Dir(0, 0, -1));
  TopoDS_Shape outerCylinder =
      BRepPrimAPI_MakeCylinder(axis, params.D / 2, params.H4).Shape();
  TopoDS_Shape innerCylinder =
      BRepPrimAPI_MakeCylinder(axis, (params.D - 2 * params.t) / 2, params.H4)
          .Shape();
  TopoDS_Shape h4 = BRepAlgoAPI_Cut(outerCylinder, innerCylinder).Shape();
  builder.Add(result, h4);

  return result;
}


/**
 * @brief 创建带定位的复合式沉井基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape
create_composite_caisson_base(const composite_caisson_base_params &params,
                              const gp_Pnt &position, const gp_Dir &direction) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_composite_caisson_base(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(position, direction);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(foundation, transformation);
  return transform.Shape();
}


/**
 * @brief 创建筏板基础
 * @param params 基础参数结构体
 * @return TopoDS_Shape 生成的基础形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_raft_base(const raft_base_params &params) {
  // 参数验证
  if (params.H1 <= 0 || params.H2 <= 0) {
    throw Standard_ConstructionError("底板高度参数必须为正数");
  }
  if (params.b1 <= 0 || params.b2 <= 0 || params.B1 <= 0 || params.B2 <= 0 ||
      params.L1 <= 0 || params.L2 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  // 1. 创建四角支柱
  double halfB1 = params.B2 / 2;
  double halfL1 = params.L2 / 2;
  double pillarHalfSize = params.b1 / 2; // 支柱半宽

  std::vector<gp_Pnt> pillarPositions = {
      gp_Pnt(-halfB1 + pillarHalfSize, -halfL1 + pillarHalfSize,
             -params.H1), // 左下
      gp_Pnt(halfB1 - pillarHalfSize, -halfL1 + pillarHalfSize,
             -params.H1), // 右下
      gp_Pnt(halfB1 - pillarHalfSize, halfL1 - pillarHalfSize,
             -params.H1), // 右上
      gp_Pnt(-halfB1 + pillarHalfSize, halfL1 - pillarHalfSize,
             -params.H1) // 左上
  };

  for (const auto &pos : pillarPositions) {
    gp_Ax2 axis(pos, gp_Dir(0, 0, 1));
    TopoDS_Shape pillar =
        BRepPrimAPI_MakeBox(axis, params.b1, params.b1, params.H1).Shape();
    builder.Add(result, pillar);
  }

  // 2. 创建主梁 (当H3>0时)
  if (params.H3 > 0) {
    // X方向主梁 (两条)
    double xBeamYPos[2] = {-(params.L2 - params.b2) / 2,
                           (params.L2 - params.b2) / 2};
    for (double yPos : xBeamYPos) {
      gp_Pnt center(-params.B1 / 2, yPos, -params.H1);
      TopoDS_Shape xBeam = BRepPrimAPI_MakeBox(gp_Ax2(center, gp_Dir(0, 0, 1)),
                                               params.B1, params.b2, params.H3)
                               .Shape();
      builder.Add(result, xBeam);
    }

    // Y方向主梁 (两条)
    double yBeamXPos[2] = {-(params.B2 - params.b2) / 2,
                           (params.B2 - params.b2) / 2};
    for (double xPos : yBeamXPos) {
      gp_Pnt center(xPos, -params.L1 / 2, -params.H1);
      TopoDS_Shape yBeam = BRepPrimAPI_MakeBox(gp_Ax2(center, gp_Dir(0, 0, 1)),
                                               params.b2, params.L1, params.H3)
                               .Shape();
      builder.Add(result, yBeam);
    }
  }

  // 3. 创建底板
  gp_Pnt baseCenter(params.B1 / 2, -params.L1 / 2, -params.H1);
  TopoDS_Shape base = BRepPrimAPI_MakeBox(gp_Ax2(baseCenter, gp_Dir(0, 0, -1)),
                                          params.B1, params.L1, params.H2)
                          .Shape();
  builder.Add(result, base);

  return result;
}


/**
 * @brief 创建带定位的筏板基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_raft_base(const raft_base_params &params,
                              const gp_Pnt &position, const gp_Dir &direction) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_raft_base(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(position, direction);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(foundation, transformation);
  return transform.Shape();
}


/**
 * @brief 创建直埋式基础
 * @param params 基础参数结构体
 * @return TopoDS_Shape 生成的基础形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape
create_direct_buried_base(const direct_buried_base_params &params) {
  // 参数验证
  if (params.H1 <= 0) {
    throw Standard_ConstructionError("基础高度H1必须为正数");
  }
  if (params.t <= 0) {
    throw Standard_ConstructionError("壁厚t必须为正数");
  }

  // 创建基础主体
  gp_Ax2 axis(gp_Pnt(0, 0, -params.H1), gp_Dir(0, 0, 1));
  TopoDS_Shape outerCylinder =
      BRepPrimAPI_MakeCylinder(axis, params.d / 2, params.H1).Shape();
  TopoDS_Shape innerCylinder =
      BRepPrimAPI_MakeCylinder(axis, (params.d - 2 * params.t) / 2, params.H1)
          .Shape();
  TopoDS_Shape mainBody = BRepAlgoAPI_Cut(outerCylinder, innerCylinder).Shape();

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);
  builder.Add(result, mainBody);

  // 创建固定盘（如果有）
  TopoDS_Shape basePlate;
  if (params.D > 0) { // 圆形固定盘
    gp_Ax2 plateAxis(gp_Pnt(0, 0, -params.H2), gp_Dir(0, 0, 1));
    TopoDS_Shape outerPlate =
        BRepPrimAPI_MakeCylinder(plateAxis, params.D / 2, params.H2).Shape();
    TopoDS_Shape innerPlate =
        BRepPrimAPI_MakeCylinder(plateAxis, params.d / 2, params.H2).Shape();
    basePlate = BRepAlgoAPI_Cut(outerPlate, innerPlate).Shape();
    builder.Add(result, basePlate);
  } else if (params.B > 0) { // 方形固定盘
    BRepBuilderAPI_MakeWire wire;
    double halfB = params.B / 2;
    // 创建方形轮廓的四条边
    wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfB, -halfB, -params.H2),
                                     gp_Pnt(halfB, -halfB, -params.H2))
                 .Edge()); // 底边
    wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfB, -halfB, -params.H2),
                                     gp_Pnt(halfB, halfB, -params.H2))
                 .Edge()); // 右边
    wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfB, halfB, -params.H2),
                                     gp_Pnt(-halfB, halfB, -params.H2))
                 .Edge()); // 顶边
    wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfB, halfB, -params.H2),
                                     gp_Pnt(-halfB, -halfB, -params.H2))
                 .Edge()); // 左边

    BRepBuilderAPI_MakeFace face(wire.Wire());
    TopoDS_Shape outerPlate =
        BRepPrimAPI_MakePrism(face.Face(), gp_Vec(0, 0, params.H2)).Shape();

    // 创建开洞用的圆柱
    gp_Ax2 holeAxis(gp_Pnt(0, 0, -params.H2), gp_Dir(0, 0, 1));
    TopoDS_Shape hole =
        BRepPrimAPI_MakeCylinder(holeAxis, params.d / 2, params.H2).Shape();

    basePlate = BRepAlgoAPI_Cut(outerPlate, hole).Shape();
    builder.Add(result, basePlate);
  }

  return result;
}


/**
 * @brief 创建带定位的直埋式基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_direct_buried_base(const direct_buried_base_params &params,
                                       const gp_Pnt &position,
                                       const gp_Dir &direction) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_direct_buried_base(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(position, direction);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(foundation, transformation);
  return transform.Shape();
}


/**
 * @brief 创建钢套筒式基础
 * @param params 基础参数结构体
 * @return TopoDS_Shape 生成的基础形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_steel_sleeve_base(const steel_sleeve_base_params &params) {
  // 参数验证
  if (params.H1 <= 0 || params.H2 < 0 || params.H3 < 0 || params.H4 < 0) {
    throw Standard_ConstructionError("高度参数必须为正数");
  }
  if (params.d <= 0 || params.t <= 0) {
    throw Standard_ConstructionError("钢套筒尺寸参数必须为正数");
  }

  // 创建钢套筒（空心圆管）
  gp_Ax2 axis(gp_Pnt(0, 0, -params.H1 - params.H2 - params.H3),
              gp_Dir(0, 0, 1));
  TopoDS_Shape outerTube =
      BRepPrimAPI_MakeCylinder(axis, params.d / 2, params.H1).Shape();
  TopoDS_Shape innerTube =
      BRepPrimAPI_MakeCylinder(axis, (params.d - 2 * params.t) / 2, params.H1)
          .Shape();
  TopoDS_Shape sleeve = BRepAlgoAPI_Cut(outerTube, innerTube).Shape();

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);
  builder.Add(result, sleeve);

  // 处理圆形卡盘
  if (params.D1 > 0 && params.D2 > 0) {
    // 创建底部圆柱
    gp_Ax2 baseAxis(gp_Pnt(0, 0, -params.H2 - params.H3 - params.H4),
                    gp_Dir(0, 0, 1));
    TopoDS_Shape baseCylinder =
        BRepPrimAPI_MakeCylinder(baseAxis, params.D1 / 2, params.H4).Shape();

    // 创建中部圆柱
    gp_Ax2 midAxis(gp_Pnt(0, 0, -params.H2 - params.H3), gp_Dir(0, 0, 1));
    TopoDS_Shape midCylinder =
        BRepPrimAPI_MakeCylinder(midAxis, params.D2 / 2, params.H3).Shape();

    // 创建顶部圆锥
    gp_Ax2 coneAxis(gp_Pnt(0, 0, -params.H2), gp_Dir(0, 0, 1));
    TopoDS_Shape cone =
        BRepPrimAPI_MakeCone(coneAxis, params.D2 / 2, params.d / 2, params.H2)
            .Shape();

    // 合并卡盘部件
    TopoDS_Shape chuck =
        BRepAlgoAPI_Fuse(BRepAlgoAPI_Fuse(baseCylinder, midCylinder).Shape(),
                         cone)
            .Shape();

    // 在卡盘上开洞
    TopoDS_Shape hole =
        BRepPrimAPI_MakeCylinder(baseAxis, params.d / 2, params.H1).Shape();
    chuck = BRepAlgoAPI_Cut(chuck, hole).Shape();

    builder.Add(result, chuck);
  }

  // 处理方形卡盘
  if (params.B1 > 0 && params.B2 > 0) {
    // 创建底部矩形柱
    double halfB1 = params.B1 / 2;
    gp_Pnt baseMinPoint(-halfB1, -halfB1, -params.H2 - params.H3 - params.H4);
    gp_Pnt baseMaxPoint(halfB1, halfB1, -params.H2 - params.H3);
    TopoDS_Shape baseBox =
        BRepPrimAPI_MakeBox(baseMinPoint, baseMaxPoint).Shape();

    // 创建中部矩形柱
    double halfB2 = params.B2 / 2;
    gp_Pnt midMinPoint(-halfB2, -halfB2, -params.H2 - params.H3);
    gp_Pnt midMaxPoint(halfB2, halfB2, -params.H2);
    TopoDS_Shape midBox = BRepPrimAPI_MakeBox(midMinPoint, midMaxPoint).Shape();

    // 创建顶部金字塔
    // 创建台型结构（截头金字塔）
    BRepOffsetAPI_ThruSections loftMaker(Standard_True);

    // 底部四边形（大）
    BRepBuilderAPI_MakeWire bottomWire;
    bottomWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfB2, -halfB2, -params.H2),
                                           gp_Pnt(halfB2, -halfB2, -params.H2))
                       .Edge());
    bottomWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfB2, -halfB2, -params.H2),
                                           gp_Pnt(halfB2, halfB2, -params.H2))
                       .Edge());
    bottomWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfB2, halfB2, -params.H2),
                                           gp_Pnt(-halfB2, halfB2, -params.H2))
                       .Edge());
    bottomWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfB2, halfB2, -params.H2),
                                           gp_Pnt(-halfB2, -halfB2, -params.H2))
                       .Edge());
    loftMaker.AddWire(bottomWire.Wire());

    // 顶部四边形（小）
    double halfD = params.d / 2;
    BRepBuilderAPI_MakeWire topWire;
    topWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfD, -halfD, 0),
                                        gp_Pnt(halfD, -halfD, 0))
                    .Edge());
    topWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfD, -halfD, 0),
                                        gp_Pnt(halfD, halfD, 0))
                    .Edge());
    topWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfD, halfD, 0),
                                        gp_Pnt(-halfD, halfD, 0))
                    .Edge());
    topWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfD, halfD, 0),
                                        gp_Pnt(-halfD, -halfD, 0))
                    .Edge());
    loftMaker.AddWire(topWire.Wire());

    loftMaker.Build();
    TopoDS_Shape frustum = loftMaker.Shape();

    // 合并卡盘部件
    TopoDS_Shape chuck =
        BRepAlgoAPI_Fuse(BRepAlgoAPI_Fuse(baseBox, midBox).Shape(), frustum)
            .Shape();

    // 在卡盘上开洞
    gp_Ax2 holeAxis(gp_Pnt(0, 0, -params.H2 - params.H4 - params.H3),
                    gp_Dir(0, 0, 1));
    TopoDS_Shape hole =
        BRepPrimAPI_MakeCylinder(holeAxis, params.d / 2, params.H1).Shape();
    chuck = BRepAlgoAPI_Cut(chuck, hole).Shape();

    builder.Add(result, chuck);
  }
  return result;
}


/**
 * @brief 创建带定位的钢套筒式基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_steel_sleeve_base(const steel_sleeve_base_params &params,
                                      const gp_Pnt &position,
                                      const gp_Dir &direction) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_steel_sleeve_base(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(position, direction);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(foundation, transformation);
  return transform.Shape();
}


/**
 * @brief 创建装配式直柱固接型基础
 * @param params 基础参数结构体
 * @return TopoDS_Shape 生成的基础形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape
create_precast_column_base(const precast_column_base_params &params) {
  // 参数验证
  if (params.H1 <= 0 || params.H2 <= 0 || params.H3 <= 0) {
    throw Standard_ConstructionError("高度参数必须为正数");
  }
  if (params.d <= 0 || params.B1 <= 0 || params.B2 <= 0 || params.L1 <= 0 ||
      params.L2 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }

  // 创建上部柱体
  gp_Ax2 columnAxis(gp_Pnt(0, 0, -params.H1), gp_Dir(0, 0, 1));
  TopoDS_Shape column =
      BRepPrimAPI_MakeCylinder(columnAxis, params.d / 2, params.H1).Shape();

  // 创建中部过渡段
  // 创建中部过渡段
  double halfB1 = params.B1 / 2;
  double halfL1 = params.L1 / 2;
  double halfB2 = params.B2 / 2;
  double halfL2 = params.L2 / 2;

  // 创建底部截面
  BRepBuilderAPI_MakeWire bottomWire;
  gp_Pnt p1(-halfB1, -halfL1, -params.H1);
  gp_Pnt p2(halfB1, -halfL1, -params.H1);
  gp_Pnt p3(halfB1, halfL1, -params.H1);
  gp_Pnt p4(-halfB1, halfL1, -params.H1);
  bottomWire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  bottomWire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
  bottomWire.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
  bottomWire.Add(BRepBuilderAPI_MakeEdge(p4, p1).Edge());

  // 创建顶部截面
  BRepBuilderAPI_MakeWire topWire;
  gp_Pnt p5(-halfB2, -halfL2, -params.H1 - params.H2);
  gp_Pnt p6(halfB2, -halfL2, -params.H1 - params.H2);
  gp_Pnt p7(halfB2, halfL2, -params.H1 - params.H2);
  gp_Pnt p8(-halfB2, halfL2, -params.H1 - params.H2);
  topWire.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge());
  topWire.Add(BRepBuilderAPI_MakeEdge(p6, p7).Edge());
  topWire.Add(BRepBuilderAPI_MakeEdge(p7, p8).Edge());
  topWire.Add(BRepBuilderAPI_MakeEdge(p8, p5).Edge());

  // 使用BRepOffsetAPI_ThruSections创建过渡段
  BRepOffsetAPI_ThruSections loftMaker(Standard_True);
  loftMaker.AddWire(bottomWire.Wire());
  loftMaker.AddWire(topWire.Wire());
  loftMaker.Build();
  TopoDS_Shape transition = loftMaker.Shape();

  // 添加H3段 一个box
  gp_Pnt boxMinPoint(-halfB2, -halfL2, -params.H1 - params.H2 - params.H3);
  gp_Pnt boxMaxPoint(halfB2, halfL2, -params.H1 - params.H2);
  TopoDS_Shape h3Box = BRepPrimAPI_MakeBox(boxMinPoint, boxMaxPoint).Shape();

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);
  builder.Add(result, column);
  builder.Add(result, transition);
  builder.Add(result, h3Box);

  return result;
}


/**
 * @brief 创建带定位的装配式直柱固接型基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape
create_precast_column_base(const precast_column_base_params &params,
                           const gp_Pnt &position, const gp_Dir &direction) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_precast_column_base(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(position, direction);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(foundation, transformation);
  return transform.Shape();
}


/**
 * @brief 创建装配式直柱铰接型基础
 * @param params 基础参数结构体
 * @return TopoDS_Shape 生成的基础形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape
create_precast_pinned_base(const precast_pinned_base_params &params) {
  // 参数验证
  if (params.H1 <= 0 || params.H2 <= 0 || params.H3 <= 0) {
    throw Standard_ConstructionError("高度参数必须为正数");
  }
  if (params.d <= 0 || params.B1 <= 0 || params.B2 <= 0 || params.L1 <= 0 ||
      params.L2 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }

  // 创建上部柱体
  gp_Ax2 columnAxis(gp_Pnt(0, 0, -params.H1), gp_Dir(0, 0, 1));
  TopoDS_Shape column =
      BRepPrimAPI_MakeCylinder(columnAxis, params.d / 2, params.H1).Shape();

  // 创建中部过渡段
  double halfB1 = params.B1 / 2;
  double halfL1 = params.L1 / 2;
  double halfB2 = params.B2 / 2;
  double halfL2 = params.L2 / 2;

  // 创建底部截面
  BRepBuilderAPI_MakeWire bottomWire;
  gp_Pnt p1(-halfB1, -halfL1, -params.H1);
  gp_Pnt p2(halfB1, -halfL1, -params.H1);
  gp_Pnt p3(halfB1, halfL1, -params.H1);
  gp_Pnt p4(-halfB1, halfL1, -params.H1);
  bottomWire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  bottomWire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
  bottomWire.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
  bottomWire.Add(BRepBuilderAPI_MakeEdge(p4, p1).Edge());

  // 创建顶部截面
  BRepBuilderAPI_MakeWire topWire;
  gp_Pnt p5(-halfB2, -halfL2, -params.H1 - params.H2);
  gp_Pnt p6(halfB2, -halfL2, -params.H1 - params.H2);
  gp_Pnt p7(halfB2, halfL2, -params.H1 - params.H2);
  gp_Pnt p8(-halfB2, halfL2, -params.H1 - params.H2);
  topWire.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge());
  topWire.Add(BRepBuilderAPI_MakeEdge(p6, p7).Edge());
  topWire.Add(BRepBuilderAPI_MakeEdge(p7, p8).Edge());
  topWire.Add(BRepBuilderAPI_MakeEdge(p8, p5).Edge());

  // 使用BRepOffsetAPI_ThruSections创建过渡段
  BRepOffsetAPI_ThruSections loftMaker(Standard_True);
  loftMaker.AddWire(bottomWire.Wire());
  loftMaker.AddWire(topWire.Wire());
  loftMaker.Build();
  TopoDS_Shape transition = loftMaker.Shape();

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);
  builder.Add(result, column);
  builder.Add(result, transition);

  // 创建卡盘(如果有)
  if (params.L > 0 && params.H > 0 && params.B > 0) {
    double halfL3 = params.L / 2;
    double halfB3 = params.B / 2;

    gp_Pnt boxMinPoint(-halfB3 + params.d / 2, -halfL3,
                       -params.H1 + params.H3 + params.H / 2);
    gp_Pnt boxMaxPoint(halfB3 + params.d / 2, halfL3,
                       -params.H1 + params.H3 - params.H / 2);
    TopoDS_Shape clamp = BRepPrimAPI_MakeBox(boxMinPoint, boxMaxPoint).Shape();

    builder.Add(result, clamp);
  }

  return result;
}


/**
 * @brief 创建带定位的装配式直柱铰接型基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape
create_precast_pinned_base(const precast_pinned_base_params &params,
                           const gp_Pnt &position, const gp_Dir &direction) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_precast_pinned_base(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(position, direction);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(foundation, transformation);
  return transform.Shape();
}


/**
 * @brief 创建装配式金属支架型基础
 * @param params 基础参数结构体
 * @return TopoDS_Shape 生成的基础形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_precast_metal_support_base(
    const precast_metal_support_base_params &params) {
  // 参数验证
  if (params.H1 <= 0 || params.H2 <= 0 || params.H3 <= 0 || params.H4 <= 0) {
    throw Standard_ConstructionError("All height parameters must be positive");
  }
  if (params.b1 <= 0 || params.b2 <= 0 || params.B1 <= 0 || params.B2 <= 0 ||
      params.L1 <= 0 || params.L2 <= 0 || params.S1 <= 0 || params.S2 <= 0) {
    throw Standard_ConstructionError(
        "All dimension parameters must be positive");
  }
  if (params.n1 <= 0 || params.n2 <= 0) {
    throw Standard_ConstructionError("Count parameters must be positive");
  }
  if (params.HX.empty()) {
    throw Standard_ConstructionError("HX array cannot be empty");
  }

  // 1. 创建底板
  TopoDS_Compound basePlate;
  BRep_Builder baseBuilder;
  baseBuilder.MakeCompound(basePlate);

  double spacing = (params.B1 / params.n2 - params.b1) / 2;
  for (int i = 0; i < params.n2; i++) {
    double xPos =
        -params.B1 / 2 + params.b1 / 2 + i * (params.b1 + 2 * spacing);

    // 创建板条
    gp_Pnt p1(xPos - params.b1 / 2, -params.L1 / 2,
              -params.H1 - params.H2 - params.H3 - params.H4);
    gp_Pnt p2(xPos + params.b1 / 2, params.L1 / 2,
              -params.H1 - params.H2 - params.H3);
    TopoDS_Shape plank = BRepPrimAPI_MakeBox(p1, p2).Shape();

    baseBuilder.Add(basePlate, plank);
  }

  // 2. 创建连接梁
  TopoDS_Compound beams;
  BRep_Builder beamBuilder;
  beamBuilder.MakeCompound(beams);

  // 第一条连接梁
  gp_Pnt beam1P1(-params.B1 / 2, -params.L2 / 2,
                 -params.H1 - params.H2 - params.H3);
  gp_Pnt beam1P2(params.B1 / 2, -params.L2 / 2 + params.b2,
                 -params.H1 - params.H2);
  TopoDS_Shape beam1 = BRepPrimAPI_MakeBox(beam1P1, beam1P2).Shape();

  // 第二条连接梁
  gp_Pnt beam2P1(-params.B1 / 2, params.L2 / 2 - params.b2,
                 -params.H1 - params.H2 - params.H3);
  gp_Pnt beam2P2(params.B1 / 2, params.L2 / 2, -params.H1 - params.H2);
  TopoDS_Shape beam2 = BRepPrimAPI_MakeBox(beam2P1, beam2P2).Shape();

  beamBuilder.Add(beams, beam1);
  beamBuilder.Add(beams, beam2);

  // 3. 创建立柱
  TopoDS_Compound columns;
  BRep_Builder columnBuilder;
  columnBuilder.MakeCompound(columns);

  // 定义四个立柱的底部中心点
  std::vector<gp_Pnt> basePoints = {
      gp_Pnt(params.B2 / 2, params.L2 / 2,
             -params.H1 - params.H2), // 前右立柱
      gp_Pnt(params.B2 / 2, -params.L2 / 2,
             -params.H1 - params.H2), // 后右立柱
      gp_Pnt(-params.B2 / 2, -params.L2 / 2,
             -params.H1 - params.H2), // 后左立柱
      gp_Pnt(-params.B2 / 2, params.L2 / 2,
             -params.H1 - params.H2) // 前左立柱
  };

  std::vector<gp_Pnt> topPoints = {
      gp_Pnt(params.S1 / 2, 0, -params.H1),  // 前右立柱顶
      gp_Pnt(params.S1 / 2, 0, -params.H1),  // 后右立柱顶
      gp_Pnt(-params.S1 / 2, 0, -params.H1), // 后左立柱顶
      gp_Pnt(-params.S1 / 2, 0, -params.H1)  // 前左立柱顶
  };

  for (int i = 0; i < 4; i++) {
    // 创建倾斜段
    gp_Pnt basePoint = basePoints[i];
    gp_Pnt topPoint = topPoints[i];

    // 创建方形截面轮廓
    BRepBuilderAPI_MakeWire wire;
    double halfS1 = params.S1 / 2;
    wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfS1, -halfS1, 0),
                                     gp_Pnt(halfS1, -halfS1, 0))
                 .Edge());
    wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfS1, -halfS1, 0),
                                     gp_Pnt(halfS1, halfS1, 0))
                 .Edge());
    wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfS1, halfS1, 0),
                                     gp_Pnt(-halfS1, halfS1, 0))
                 .Edge());
    wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfS1, halfS1, 0),
                                     gp_Pnt(-halfS1, -halfS1, 0))
                 .Edge());

    BRepBuilderAPI_MakeFace face(wire.Wire());

    // 创建倾斜段
    gp_Trsf transform;
    transform.SetTransformation(
        gp_Ax3(basePoint, gp_Dir(topPoint.XYZ() - basePoint.XYZ())),
        gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));

    TopoDS_Shape inclinedColumn =
        BRepPrimAPI_MakePrism(
            BRepBuilderAPI_Transform(face.Face(), transform).Shape(),
            gp_Vec(topPoint.XYZ() - basePoint.XYZ()))
            .Shape();

    // 创建垂直段
    BRepBuilderAPI_MakeWire vertWire;
    // 底部边
    vertWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfS1, -halfS1, 0),
                                         gp_Pnt(halfS1, -halfS1, 0))
                     .Edge());
    // 右侧边
    vertWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfS1, -halfS1, 0),
                                         gp_Pnt(halfS1, halfS1, 0))
                     .Edge());
    // 顶部边
    vertWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfS1, halfS1, 0),
                                         gp_Pnt(-halfS1, halfS1, 0))
                     .Edge());
    // 左侧边
    vertWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfS1, halfS1, 0),
                                         gp_Pnt(-halfS1, -halfS1, 0))
                     .Edge());

    BRepBuilderAPI_MakeFace vertFace(vertWire.Wire());

    gp_Trsf trsf;
    trsf.SetTranslation(gp_Vec(topPoint.XYZ()));
    TopoDS_Shape verticalColumn =
        BRepPrimAPI_MakePrism(
            BRepBuilderAPI_Transform(vertFace.Face(), trsf).Shape(),
            gp_Vec(0, 0, params.H1))
            .Shape();

    columnBuilder.Add(columns, inclinedColumn);
    columnBuilder.Add(columns, verticalColumn);
  }

  // 4. 创建斜材
  TopoDS_Compound braces;
  BRep_Builder braceBuilder;
  braceBuilder.MakeCompound(braces);

  std::vector<double> realHeight;
  realHeight.push_back(0); // 添加最底层高度0
  for (size_t i = 0; i < params.HX.size(); i++) {
    realHeight.push_back(realHeight.back() + params.HX[i]);
  }
  realHeight.push_back(params.H2); // 添加最顶层高度

  // 创建每层的斜材和横梁
  for (size_t i = 0; i < realHeight.size() - 1; i++) {
    double currentHeight = realHeight[i];
    double nextHeight = realHeight[i + 1];

    // 计算四个立柱在当前层的实际位置
    std::vector<gp_Pnt> currentLayerPoints;
    for (int k = 0; k < 4; k++) {
      gp_Pnt basePoint = basePoints[k];
      gp_Pnt topPoint = topPoints[k];

      double ratio = currentHeight / (params.H4 + params.H3 + params.H2);
      gp_Pnt currentPoint =
          gp_Pnt(basePoint.X() + ratio * (topPoint.X() - basePoint.X()),
                 basePoint.Y() + ratio * (topPoint.Y() - basePoint.Y()),
                 basePoint.Z() + ratio * (topPoint.Z() - basePoint.Z()));
      currentLayerPoints.push_back(currentPoint);
    }

    // 1. 创建横向加强筋（连接同一层的相邻立柱）
    for (int k = 0; k < 4; k++) {
      gp_Pnt start = currentLayerPoints[k];
      gp_Pnt end = currentLayerPoints[(k + 1) % 4];

      BRepOffsetAPI_ThruSections lateralGenerator(true);
      double halfS2 = params.S2 / 2;

      // 起点截面
      BRepBuilderAPI_MakeWire startWire;
      startWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfS2, -halfS2, 0),
                                            gp_Pnt(halfS2, -halfS2, 0))
                        .Edge());
      startWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfS2, -halfS2, 0),
                                            gp_Pnt(halfS2, halfS2, 0))
                        .Edge());
      startWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfS2, halfS2, 0),
                                            gp_Pnt(-halfS2, halfS2, 0))
                        .Edge());
      startWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfS2, halfS2, 0),
                                            gp_Pnt(-halfS2, -halfS2, 0))
                        .Edge());

      gp_Trsf startTrsf;
      startTrsf.SetTransformation(
          gp_Ax3(start, gp_Dir(end.XYZ() - start.XYZ())),
          gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
      TopoDS_Shape transformedStartWire =
          BRepBuilderAPI_Transform(startWire.Wire(), startTrsf).Shape();
      lateralGenerator.AddWire(TopoDS::Wire(transformedStartWire));

      // 终点截面
      BRepBuilderAPI_MakeWire endWire;
      endWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfS2, -halfS2, 0),
                                          gp_Pnt(halfS2, -halfS2, 0))
                      .Edge());
      endWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfS2, -halfS2, 0),
                                          gp_Pnt(halfS2, halfS2, 0))
                      .Edge());
      endWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfS2, halfS2, 0),
                                          gp_Pnt(-halfS2, halfS2, 0))
                      .Edge());
      endWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfS2, halfS2, 0),
                                          gp_Pnt(-halfS2, -halfS2, 0))
                      .Edge());

      gp_Trsf endTrsf;
      endTrsf.SetTransformation(gp_Ax3(end, gp_Dir(end.XYZ() - start.XYZ())),
                                gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
      TopoDS_Shape transformedEndWire =
          BRepBuilderAPI_Transform(endWire.Wire(), endTrsf).Shape();
      lateralGenerator.AddWire(TopoDS::Wire(transformedEndWire));

      lateralGenerator.Build();
      if (lateralGenerator.IsDone()) {
        braceBuilder.Add(braces, lateralGenerator.Shape());
      }
    }

    // 2. 创建斜筋 (连接当前层到下一层)
    if (i < realHeight.size() - 2) {
      std::vector<gp_Pnt> nextLayerPoints;

      for (int k = 0; k < 4; k++) {
        gp_Pnt basePoint = basePoints[k];
        gp_Pnt topPoint = topPoints[k];

        double nextRatio =
            realHeight[i + 1] / (params.H4 + params.H3 + params.H2);
        gp_Pnt nextPoint =
            gp_Pnt(basePoint.X() + nextRatio * (topPoint.X() - basePoint.X()),
                   basePoint.Y() + nextRatio * (topPoint.Y() - basePoint.Y()),
                   basePoint.Z() + nextRatio * (topPoint.Z() - basePoint.Z()));
        nextLayerPoints.push_back(nextPoint);
      }

      // 创建四个斜筋 (连接相邻立柱)
      for (int k = 0; k < 4; k++) {
        gp_Pnt start = currentLayerPoints[k];
        gp_Pnt end = nextLayerPoints[(k + 1) % 4];

        BRepOffsetAPI_ThruSections generator(true);
        double halfS2 = params.S2 / 2;

        // 起点截面
        BRepBuilderAPI_MakeWire startWire;
        startWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfS2, -halfS2, 0),
                                              gp_Pnt(halfS2, -halfS2, 0))
                          .Edge());
        startWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfS2, -halfS2, 0),
                                              gp_Pnt(halfS2, halfS2, 0))
                          .Edge());
        startWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfS2, halfS2, 0),
                                              gp_Pnt(-halfS2, halfS2, 0))
                          .Edge());
        startWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfS2, halfS2, 0),
                                              gp_Pnt(-halfS2, -halfS2, 0))
                          .Edge());

        gp_Trsf startTrsf;
        startTrsf.SetTransformation(
            gp_Ax3(start, gp_Dir(end.XYZ() - start.XYZ())),
            gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
        TopoDS_Shape transformedStartWire =
            BRepBuilderAPI_Transform(startWire.Wire(), startTrsf).Shape();
        generator.AddWire(TopoDS::Wire(transformedStartWire));

        // 终点截面
        BRepBuilderAPI_MakeWire endWire;
        endWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfS2, -halfS2, 0),
                                            gp_Pnt(halfS2, -halfS2, 0))
                        .Edge());
        endWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfS2, -halfS2, 0),
                                            gp_Pnt(halfS2, halfS2, 0))
                        .Edge());
        endWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfS2, halfS2, 0),
                                            gp_Pnt(-halfS2, halfS2, 0))
                        .Edge());
        endWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfS2, halfS2, 0),
                                            gp_Pnt(-halfS2, -halfS2, 0))
                        .Edge());

        gp_Trsf endTrsf;
        endTrsf.SetTransformation(gp_Ax3(end, gp_Dir(end.XYZ() - start.XYZ())),
                                  gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
        TopoDS_Shape transformedEndWire =
            BRepBuilderAPI_Transform(endWire.Wire(), endTrsf).Shape();
        generator.AddWire(TopoDS::Wire(transformedEndWire));

        generator.Build();
        if (generator.IsDone()) {
          braceBuilder.Add(braces, generator.Shape());
        }
      }
    }
  }

  // 组合所有部件
  TopoDS_Compound result;
  BRep_Builder resultBuilder;
  resultBuilder.MakeCompound(result);

  resultBuilder.Add(result, basePlate);
  resultBuilder.Add(result, beams);
  resultBuilder.Add(result, columns);
  resultBuilder.Add(result, braces);

  return result;
}


/**
 * @brief 创建带定位的装配式金属支架型基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_precast_metal_support_base(
    const precast_metal_support_base_params &params, const gp_Pnt &position,
    const gp_Dir &direction) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_precast_metal_support_base(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(position, direction);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(foundation, transformation);
  return transform.Shape();
}


/**
 * @brief 创建装配式混凝土构件支架型基础
 * @param params 基础参数结构体
 * @return TopoDS_Shape 生成的基础形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_precast_concrete_support_base(
    const precast_concrete_support_base_params &params) {
  // 参数验证
  if (params.H1 <= 0 || params.H2 <= 0 || params.H3 <= 0 || params.H4 <= 0) {
    throw Standard_ConstructionError("All height parameters must be positive");
  }
  if (params.b1 <= 0 || params.b2 <= 0 || params.B1 <= 0 || params.B2 <= 0 ||
      params.L1 <= 0 || params.L2 <= 0 || params.S1 <= 0) {
    throw Standard_ConstructionError(
        "All dimension parameters must be positive");
  }
  if (params.n1 <= 0) {
    throw Standard_ConstructionError("Count parameters must be positive");
  }

  // 1. 创建底板
  TopoDS_Compound basePlate;
  BRep_Builder baseBuilder;
  baseBuilder.MakeCompound(basePlate);

  // 计算板条1的中心位置
  double spacing1 = (params.B1 / params.n1 - params.b2) / 2;
  std::vector<double> centerPositions;
  for (int i = 0; i < params.n1; i++) {
    centerPositions.push_back(-params.B1 / 2 + params.b2 / 2 +
                              i * (params.b2 + 2 * spacing1));
  }

  // 创建板条1 (底部)
  for (int i = 0; i < params.n1; i++) {
    double xPos = centerPositions[i];

    gp_Pnt p1(xPos - params.b2 / 2, -params.L1 / 2,
              -params.H1 - params.H2 - params.H3 - params.H4 - params.H5);
    gp_Pnt p2(xPos + params.b2 / 2, params.L1 / 2,
              -params.H1 - params.H2 - params.H3 - params.H4);
    baseBuilder.Add(basePlate, BRepPrimAPI_MakeBox(p1, p2).Shape());
  }

  // 创建板条2 (上部) - 使用相同的中心位置
  for (int i = 0; i < params.n1; i++) {
    double xPos = centerPositions[i];

    gp_Pnt p1(xPos - params.b3 / 2, -params.L1 / 2,
              -params.H1 - params.H2 - params.H3 - params.H4);
    gp_Pnt p2(xPos + params.b3 / 2, params.L1 / 2,
              -params.H1 - params.H2 - params.H3);
    baseBuilder.Add(basePlate, BRepPrimAPI_MakeBox(p1, p2).Shape());
  }

  // 2. 创建连接梁
  TopoDS_Compound beams;
  BRep_Builder beamBuilder;
  beamBuilder.MakeCompound(beams);

  // 第一条连接梁
  gp_Pnt beam1P1(-params.B1 / 2, -params.L2 / 2,
                 -params.H1 - params.H2 - params.H3);
  gp_Pnt beam1P2(params.B1 / 2, -params.L2 / 2 + params.b1,
                 -params.H1 - params.H2);
  TopoDS_Shape beam1 = BRepPrimAPI_MakeBox(beam1P1, beam1P2).Shape();

  // 第二条连接梁
  gp_Pnt beam2P1(-params.B1 / 2, params.L2 / 2 - params.b1,
                 -params.H1 - params.H2 - params.H3);
  gp_Pnt beam2P2(params.B1 / 2, params.L2 / 2, -params.H1 - params.H2);
  TopoDS_Shape beam2 = BRepPrimAPI_MakeBox(beam2P1, beam2P2).Shape();

  beamBuilder.Add(beams, beam1);
  beamBuilder.Add(beams, beam2);

  // 3. 创建立柱
  TopoDS_Compound columns;
  BRep_Builder columnBuilder;
  columnBuilder.MakeCompound(columns);

  // 定义四个立柱的底部中心点
  std::vector<gp_Pnt> basePoints = {
      gp_Pnt(params.B2 / 2, params.L2 / 2,
             -params.H1 - params.H2), // 前右立柱
      gp_Pnt(params.B2 / 2, -params.L2 / 2,
             -params.H1 - params.H2), // 后右立柱
      gp_Pnt(-params.B2 / 2, -params.L2 / 2,
             -params.H1 - params.H2), // 后左立柱
      gp_Pnt(-params.B2 / 2, params.L2 / 2,
             -params.H1 - params.H2) // 前左立柱
  };

  std::vector<gp_Pnt> topPoints = {
      gp_Pnt(params.S1 / 2, 0, -params.H1),  // 前右立柱顶
      gp_Pnt(params.S1 / 2, 0, -params.H1),  // 后右立柱顶
      gp_Pnt(-params.S1 / 2, 0, -params.H1), // 后左立柱顶
      gp_Pnt(-params.S1 / 2, 0, -params.H1)  // 前左立柱顶
  };

  for (int i = 0; i < 4; i++) {
    // 创建倾斜段
    gp_Pnt basePoint = basePoints[i];
    gp_Pnt topPoint = topPoints[i];

    // 创建方形截面轮廓
    BRepBuilderAPI_MakeWire wire;
    double halfS1 = params.S1 / 2;
    wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfS1, -halfS1, 0),
                                     gp_Pnt(halfS1, -halfS1, 0))
                 .Edge());
    wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfS1, -halfS1, 0),
                                     gp_Pnt(halfS1, halfS1, 0))
                 .Edge());
    wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfS1, halfS1, 0),
                                     gp_Pnt(-halfS1, halfS1, 0))
                 .Edge());
    wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfS1, halfS1, 0),
                                     gp_Pnt(-halfS1, -halfS1, 0))
                 .Edge());

    BRepBuilderAPI_MakeFace face(wire.Wire());

    // 创建倾斜段
    gp_Trsf transform;
    transform.SetTransformation(
        gp_Ax3(basePoint, gp_Dir(topPoint.XYZ() - basePoint.XYZ())),
        gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));

    TopoDS_Shape inclinedColumn =
        BRepPrimAPI_MakePrism(
            BRepBuilderAPI_Transform(face.Face(), transform).Shape(),
            gp_Vec(topPoint.XYZ() - basePoint.XYZ()))
            .Shape();

    // 创建垂直段
    BRepBuilderAPI_MakeWire vertWire;
    // 底部边
    vertWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfS1, -halfS1, 0),
                                         gp_Pnt(halfS1, -halfS1, 0))
                     .Edge());
    // 右侧边
    vertWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfS1, -halfS1, 0),
                                         gp_Pnt(halfS1, halfS1, 0))
                     .Edge());
    // 顶部边
    vertWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(halfS1, halfS1, 0),
                                         gp_Pnt(-halfS1, halfS1, 0))
                     .Edge());
    // 左侧边
    vertWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfS1, halfS1, 0),
                                         gp_Pnt(-halfS1, -halfS1, 0))
                     .Edge());

    BRepBuilderAPI_MakeFace vertFace(vertWire.Wire());

    gp_Trsf trsf;
    trsf.SetTranslation(gp_Vec(topPoint.XYZ()));
    TopoDS_Shape verticalColumn =
        BRepPrimAPI_MakePrism(
            BRepBuilderAPI_Transform(vertFace.Face(), trsf).Shape(),
            gp_Vec(0, 0, params.H1))
            .Shape();

    columnBuilder.Add(columns, inclinedColumn);
    columnBuilder.Add(columns, verticalColumn);
  }

  // 组合所有部件
  TopoDS_Compound result;
  BRep_Builder resultBuilder;
  resultBuilder.MakeCompound(result);

  resultBuilder.Add(result, basePlate);
  resultBuilder.Add(result, beams);
  resultBuilder.Add(result, columns);

  return result;
}


/**
 * @brief 创建带定位的装配式混凝土构件支架型基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_precast_concrete_support_base(
    const precast_concrete_support_base_params &params, const gp_Pnt &position,
    const gp_Dir &direction) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_precast_concrete_support_base(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(position, direction);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(foundation, transformation);
  return transform.Shape();
}


/**
 * @brief 创建导地线(含OPGW)模型
 * @param params 导地线参数结构体
 * @param startPoint 起始点坐标
 * @param endPoint 结束点坐标
 * @return TopoDS_Shape 生成的导地线形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_transmission_line(const transmission_line_params &params,
                                      const gp_Pnt &startPoint,
                                      const gp_Pnt &endPoint) {
  // 参数验证
  if (params.sectionalArea <= 0) {
    throw Standard_ConstructionError("截面积必须为正数");
  }
  if (params.outsideDiameter <= 0) {
    throw Standard_ConstructionError("外径必须为正数");
  }
  if (params.wireWeight <= 0) {
    throw Standard_ConstructionError("单位长度质量必须为正数");
  }

  // 计算导地线长度和悬垂度
  double length = startPoint.Distance(endPoint);
  if (length <= Precision::Confusion()) {
    throw Standard_ConstructionError("起点和终点距离过小");
  }

  // 计算悬垂度 (带高差修正)
  double weightPerMeter = params.wireWeight / 1000.0; // kg/m
  double tension = params.ratedStrength * 0.25;       // (25%额定强度)

  // 计算高差修正系数 (cosθ ≈ 1/cosh(β), β=高差/水平档距)
  double heightDiff = endPoint.Z() - startPoint.Z();
  double lengthHorizontal =
      sqrt(pow(endPoint.X() - startPoint.X(), 2) +
           pow(endPoint.Y() - startPoint.Y(), 2)); // 水平投影档距
  double beta = heightDiff / lengthHorizontal;
  double coshBeta = std::cosh(beta);
  double sag = (weightPerMeter * 9.8 * lengthHorizontal * lengthHorizontal) /
               (8 * tension * coshBeta);
  double sagAtMid = sag * (1 - pow(heightDiff / (2 * lengthHorizontal), 2));

  // 创建导地线路径(带悬垂度)
  gp_Pnt midPoint((startPoint.X() + endPoint.X()) / 2,
                  (startPoint.Y() + endPoint.Y()) / 2,
                  (startPoint.Z() + endPoint.Z()) / 2 - sagAtMid);

  TColgp_Array1OfPnt points(1, 3);
  points.SetValue(1, startPoint);
  points.SetValue(2, midPoint);
  points.SetValue(3, endPoint);

  Handle_Geom_BSplineCurve curve = GeomAPI_PointsToBSpline(points).Curve();
  BRepBuilderAPI_MakeWire wireMaker;
  wireMaker.Add(BRepBuilderAPI_MakeEdge(curve).Edge());
  TopoDS_Wire wirePath = wireMaker.Wire();

  // 创建导地线截面圆
  gp_Ax2 axis(startPoint, gp_Dir(endPoint.XYZ() - startPoint.XYZ()));
  TopoDS_Wire section =
      BRepBuilderAPI_MakeWire(
          BRepBuilderAPI_MakeEdge(gp_Circ(axis, params.outsideDiameter / 2))
              .Edge())
          .Wire();

  // 扫掠生成导地线
  BRepOffsetAPI_MakePipeShell pipeMaker(wirePath);
  pipeMaker.Add(section);
  pipeMaker.SetMode(Standard_True);
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("导地线建模失败");
  }
  if (!pipeMaker.MakeSolid()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }
  return pipeMaker.Shape();
}


TopoDS_Wire
create_transmission_centerline(const transmission_line_params &params,
                               const gp_Pnt &startPoint,
                               const gp_Pnt &endPoint) {
  // 参数验证
  if (params.sectionalArea <= 0) {
    throw Standard_ConstructionError("截面积必须为正数");
  }
  if (params.outsideDiameter <= 0) {
    throw Standard_ConstructionError("外径必须为正数");
  }
  if (params.wireWeight <= 0) {
    throw Standard_ConstructionError("单位长度质量必须为正数");
  }

  // 计算导地线长度和悬垂度
  double length = startPoint.Distance(endPoint);
  if (length <= Precision::Confusion()) {
    throw Standard_ConstructionError("起点和终点距离过小");
  }

  // 计算悬垂度 (带高差修正)
  double weightPerMeter = params.wireWeight / 1000.0; // kg/m
  double tension = params.ratedStrength * 0.25;       // (25%额定强度)

  // 计算高差修正系数 (cosθ ≈ 1/cosh(β), β=高差/水平档距)
  double heightDiff = endPoint.Z() - startPoint.Z();
  double lengthHorizontal =
      sqrt(pow(endPoint.X() - startPoint.X(), 2) +
           pow(endPoint.Y() - startPoint.Y(), 2)); // 水平投影档距
  double beta = heightDiff / lengthHorizontal;
  double coshBeta = std::cosh(beta);
  double sag = (weightPerMeter * 9.8 * lengthHorizontal * lengthHorizontal) /
               (8 * tension * coshBeta);
  double sagAtMid = sag * (1 - pow(heightDiff / (2 * lengthHorizontal), 2));

  // 创建导地线路径(带悬垂度)
  gp_Pnt midPoint((startPoint.X() + endPoint.X()) / 2,
                  (startPoint.Y() + endPoint.Y()) / 2,
                  (startPoint.Z() + endPoint.Z()) / 2 - sagAtMid);

  TColgp_Array1OfPnt points(1, 3);
  points.SetValue(1, startPoint);
  points.SetValue(2, midPoint);
  points.SetValue(3, endPoint);

  Handle_Geom_BSplineCurve curve = GeomAPI_PointsToBSpline(points).Curve();
  BRepBuilderAPI_MakeWire wireMaker;
  wireMaker.Add(BRepBuilderAPI_MakeEdge(curve).Edge());
  return wireMaker.Wire();
}


std::vector<gp_Pnt>
sample_transmission_line(const transmission_line_params &params,
                         const gp_Pnt &startPoint, const gp_Pnt &endPoint,
                         double tessellation) {
  // 参数验证
  if (params.sectionalArea <= 0) {
    throw Standard_ConstructionError("截面积必须为正数");
  }
  if (params.outsideDiameter <= 0) {
    throw Standard_ConstructionError("外径必须为正数");
  }
  if (params.wireWeight <= 0) {
    throw Standard_ConstructionError("单位长度质量必须为正数");
  }

  // 计算导地线长度
  double length = startPoint.Distance(endPoint);
  if (length <= Precision::Confusion()) {
    throw Standard_ConstructionError("起点和终点距离过小");
  }

  // 计算悬垂度 (带高差修正)
  double weightPerMeter = params.wireWeight / 1000.0; // kg/m
  double tension = params.ratedStrength * 0.25;       // (25%额定强度)

  // 计算高差修正系数
  double heightDiff = endPoint.Z() - startPoint.Z();
  double lengthHorizontal = sqrt(pow(endPoint.X() - startPoint.X(), 2) +
                                 pow(endPoint.Y() - startPoint.Y(), 2));
  double beta = heightDiff / lengthHorizontal;
  double coshBeta = std::cosh(beta);
  double sag = (weightPerMeter * 9.8 * lengthHorizontal * lengthHorizontal) /
               (8 * tension * coshBeta);
  double sagAtMid = sag * (1 - pow(heightDiff / (2 * lengthHorizontal), 2));

  // 计算采样点数量
  int sampleCount =
      tessellation > 0 ? static_cast<int>(length / tessellation) : 20;
  sampleCount = std::max(sampleCount, 2); // 至少2个点

  // 创建采样点
  std::vector<gp_Pnt> points;
  points.reserve(sampleCount);

  // 计算中间点(悬垂最低点)
  gp_Pnt midPoint((startPoint.X() + endPoint.X()) / 2,
                  (startPoint.Y() + endPoint.Y()) / 2,
                  (startPoint.Z() + endPoint.Z()) / 2 - sagAtMid);

  // 生成采样点(二次贝塞尔曲线)
  for (int i = 0; i < sampleCount; ++i) {
    double t = static_cast<double>(i) / (sampleCount - 1);
    // 二次贝塞尔曲线公式: B(t) = (1-t)²P0 + 2(1-t)tP1 + t²P2
    double x = (1 - t) * (1 - t) * startPoint.X() +
               2 * (1 - t) * t * midPoint.X() + t * t * endPoint.X();
    double y = (1 - t) * (1 - t) * startPoint.Y() +
               2 * (1 - t) * t * midPoint.Y() + t * t * endPoint.Y();
    double z = (1 - t) * (1 - t) * startPoint.Z() +
               2 * (1 - t) * t * midPoint.Z() + t * t * endPoint.Z();
    points.emplace_back(x, y, z);
  }

  return points;
}


// 创建绝缘子串
TopoDS_Shape create_disk_insulator(const insulator_params &params) {
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
  double diskThickness = isComposite ? compParams.gap * 0.4
                                     : params.insulator.height *
                                           0.05; // 普通绝缘子伞裙厚度为高度的5%

  // 计算伞裙间距
  double diskSpacing = isComposite
                           ? compParams.gap
                           : (params.insulator.height -
                              diskThickness * params.insulator.leftCount) /
                                 (params.insulator.leftCount - 1);

  int leftCount =
      isComposite && compParams.gap > 0
          ? params.insulator.height / (compParams.gap + diskThickness)
          : params.insulator.leftCount;
  int rightCount =
      isComposite && compParams.gap > 0
          ? params.insulator.height / (compParams.gap + diskThickness)
          : params.insulator.rightCount;

  double rodDiameter =
      isComposite ? compParams.minorRadius / 4 : diskDiameter / 4;

  if (diskDiameter <= 0 || diskThickness <= 0 ||
      params.insulator.leftCount <= 0 || rodDiameter <= 0 ||
      params.insulator.height <= 0) {
    throw Standard_ConstructionError("绝缘子参数必须为正数");
  }

  auto create_single_insulator = [&](const gp_Pnt &basePos, int diskCount,
                                     const gp_Pnt &rodPos, double rodHeight) {
    gp_Ax2 rodAxis(rodPos, gp_Dir(0, 0, 1));
    TopoDS_Shape rod =
        BRepPrimAPI_MakeCylinder(rodAxis, rodDiameter / 2, rodHeight).Shape();

    // 组合所有部件
    TopoDS_Compound result;
    BRep_Builder resultBuilder;
    resultBuilder.MakeCompound(result);
    resultBuilder.Add(result, rod);

    for (int i = 0; i < diskCount; i++) {
      double zPos = basePos.Z() + i * (diskSpacing + diskThickness);
      double currentDiameter =
          isComposite
              ? (i % 2 == 0 ? compParams.majorRadius : compParams.minorRadius) *
                    2
              : diskDiameter;

      // 创建伞裙剖面线
      BRepBuilderAPI_MakeWire wire;
      gp_Pnt p1(basePos.X() + rodDiameter / 2, basePos.Y(),
                zPos + diskThickness * 0.5);
      gp_Pnt p2(basePos.X() + currentDiameter * 0.65, basePos.Y(),
                zPos + diskThickness * 0.3);
      wire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());

      gp_Pnt p3 = p2;
      gp_Pnt p4(basePos.X() + currentDiameter * 0.85, basePos.Y(),
                zPos + diskThickness * 0.5);
      gp_Pnt p5(basePos.X() + currentDiameter / 2, basePos.Y(),
                zPos + diskThickness);
      wire.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
      wire.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge());

      gp_Pnt p6(basePos.X() + rodDiameter / 2, basePos.Y(),
                zPos + diskThickness);

      wire.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge());
      wire.Add(BRepBuilderAPI_MakeEdge(p6, p1).Edge());

      gp_Ax1 axis(basePos, gp_Dir(0, 0, 1));
      TopoDS_Shape shed =
          BRepPrimAPI_MakeRevol(BRepLib_MakeFace(wire.Wire()).Face(), axis)
              .Shape();

      resultBuilder.Add(result, shed);
    }
    return result;
  };

  // 创建绝缘子主体
  TopoDS_Compound insulatorBody;
  BRep_Builder insulatorBodyBuilder;
  insulatorBodyBuilder.MakeCompound(insulatorBody);

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


TopoDS_Shape create_insulator_string(const insulator_params &params) {
  // 参数验证
  if (params.subNum <= 0 || params.subNum > 8 ||
      (params.subNum != 1 && params.subNum != 2 && params.subNum != 3 &&
       params.subNum != 4 && params.subNum != 6 && params.subNum != 8)) {
    throw Standard_ConstructionError("分裂数必须为1,2,3,4,6,8");
  }

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  // 1. 创建绝缘子主体（根据材质选择不同类型）
  TopoDS_Shape insulator;
  switch (params.insulator.material) {
  case insulator_material::CERAMIC:
  case insulator_material::GLASS:
    insulator = create_disk_insulator(params);
    break;
  case insulator_material::COMPOSITE:
    insulator = create_rod_insulator(params);
    break;
  default:
    throw Standard_ConstructionError("无效的绝缘子材质");
  }
  builder.Add(result, insulator);

  // 2. 处理多联情况（V串、I串等）
  if (params.multiLink.count > 1) {
    TopoDS_Compound multiResult;
    BRep_Builder multiBuilder;
    multiBuilder.MakeCompound(multiResult);

    for (int i = 0; i < params.multiLink.count; i++) {
      gp_Trsf transform;
      // 水平排列
      if (params.multiLink.arrangement == arrangement_type::HORIZONTAL) {
        double offset =
            i * params.multiLink.spacing -
            (params.multiLink.count - 1) * params.multiLink.spacing / 2;
        transform.SetTranslation(gp_Vec(offset, 0, 0));
      }
      // 垂直排列
      else {
        int row = i / 2;
        int col = i % 2;
        double offset = (col - 0.5) * params.multiLink.spacing;
        double verticalOffset = row * params.multiLink.spacing;
        transform.SetTranslation(gp_Vec(offset, verticalOffset, 0));
      }

      BRepBuilderAPI_Transform mover(result, transform);
      multiBuilder.Add(multiResult, mover.Shape());
    }
    return multiResult;
  }

  return result;
}


/**
 * @brief 创建带定位的绝缘子串
 * @param params 绝缘子参数结构体
 * @param position 绝缘子串与杆塔连接点位置
 * @param direction 绝缘子串方向（默认Z轴向上）
 * @return TopoDS_Shape 生成的绝缘子串形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_insulator_string(const insulator_params &params,
                                     const gp_Pnt &position,
                                     const gp_Dir &direction) {
  // 首先创建标准方向(Z轴向上)的绝缘子串
  TopoDS_Shape insulator = create_insulator_string(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)); // 原始坐标系
  gp_Ax3 targetAx3(position, direction);              // 目标坐标系

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  // 应用变换
  BRepBuilderAPI_Transform transform(insulator, transformation);
  return transform.Shape();
}


TopoDS_Shape create_pole_tower(const pole_tower_params &params) {
  // 创建杆塔主体形状
  TopoDS_Compound tower;
  BRep_Builder builder;
  builder.MakeCompound(tower);

  // 处理所有本体
  for (const auto &body : params.bodies) {
    // 处理本体节点
    std::map<std::string, gp_Pnt> nodePositions;
    for (const auto &node : body.nodes) {
      nodePositions[node.id] = node.position;
    }

    // 处理接腿
    for (const auto &leg : body.legs) {
      for (const auto &node : leg.nodes) {
        nodePositions[node.id] = node.position;
      }
    }

    // 创建杆件
    for (const auto &member : params.members) {
      // 检查杆件是否属于当前本体或接腿
      if (nodePositions.find(member.startNodeId) == nodePositions.end() ||
          nodePositions.find(member.endNodeId) == nodePositions.end()) {
        continue;
      }

      gp_Pnt startPos = nodePositions[member.startNodeId];
      gp_Pnt endPos = nodePositions[member.endNodeId];

      TopoDS_Shape memberShape;
      switch (member.type) {
      case member_type::ANGLE: {
        // 创建角钢杆件
        double legWidth = std::stod(member.specification.substr(1));
        double thickness = std::stod(
            member.specification.substr(member.specification.find('x') + 1));

        // 检查起点和终点是否相同
        if (startPos.IsEqual(endPos, Precision::Confusion())) {
          continue; // 跳过相同位置的杆件
        }

        // 计算杆件方向向量
        gp_Vec directionVec(startPos, endPos);
        double length = directionVec.Magnitude();

        // 创建正交坐标系（考虑yDirection）
        gp_Dir Z = directionVec.Normalized();
        gp_Dir X = member.xDirection;

        // 检查X方向是否与Z方向平行
        if (X.IsParallel(Z, Precision::Angular())) {
          // 如果平行，使用默认正交方向
          X = Z.IsParallel(gp::DX(), Precision::Angular()) ? gp::DY()
                                                           : gp::DX();
        }
        // 计算两种可能的Y方向
        gp_Dir Y1 = gp_Vec(Z.Crossed(X)).Normalized();
        gp_Dir Y2 = -Y1;

        // 选择与yDirection最接近的方向
        gp_Dir Y =
            (Y1.Dot(member.yDirection) > Y2.Dot(member.yDirection)) ? Y1 : Y2;

        // 创建最终坐标系（确保正交性）
        gp_Ax3 localAxes(startPos, Z, X);
        localAxes.SetYDirection(Y); // 强制设置Y方向

        // 创建角钢截面（局部坐标系XY平面）
        gp_Pnt p1(0, 0, 0);
        gp_Pnt p2(legWidth, 0, 0);
        gp_Pnt p3(legWidth, thickness, 0);
        gp_Pnt p4(thickness, thickness, 0);
        gp_Pnt p5(thickness, legWidth, 0);
        gp_Pnt p6(0, legWidth, 0);

        BRepBuilderAPI_MakePolygon polyMaker;
        polyMaker.Add(p1);
        polyMaker.Add(p2);
        polyMaker.Add(p3);
        polyMaker.Add(p4);
        polyMaker.Add(p5);
        polyMaker.Add(p6);
        polyMaker.Add(p1);
        TopoDS_Wire wire = polyMaker.Wire();

        // 创建坐标系变换（增加正交性校验）
        gp_Trsf transformation;
        transformation.SetTransformation(localAxes, gp_Ax2());

        TopoDS_Face face = BRepBuilderAPI_MakeFace(wire);

        BRepBuilderAPI_Transform transform(face, transformation, true);
        memberShape =
            BRepPrimAPI_MakePrism(transform.Shape(), directionVec).Shape();
        break;
      }
      case member_type::TUBE: {
        // 创建等径钢管
        double diameter = std::stod(member.specification.substr(2));
        double thickness = std::stod(
            member.specification.substr(member.specification.find('x') + 1));

        // 检查起点和终点是否相同
        if (startPos.IsEqual(endPos, Precision::Confusion())) {
          continue; // 跳过相同位置的杆件
        }

        gp_Pnt midPoint(endPos.X(), endPos.Y(), endPos.Z());

        gp_Dir axisDir(startPos.X() - endPos.X(), startPos.Y() - endPos.Y(),
                       startPos.Z() - endPos.Z());

        memberShape =
            BRepPrimAPI_MakeCylinder(gp_Ax2(midPoint, axisDir), diameter / 2,
                                     startPos.Distance(endPos))
                .Shape();
        break;
      }
      case member_type::TAPERED_TUBE: {
        // 创建锥形钢管
        double length = startPos.Distance(endPos);

        // 检查起点和终点是否相同
        if (startPos.IsEqual(endPos, Precision::Confusion())) {
          continue; // 跳过相同位置的杆件
        }

        gp_Dir axisDir(startPos.X() - endPos.X(), startPos.Y() - endPos.Y(),
                       startPos.Z() - endPos.Z());

        // 创建底部圆
        gp_Circ bottomCircle(gp_Ax2(startPos, axisDir),
                             member.end1Diameter / 2);
        TopoDS_Edge bottomEdge = BRepBuilderAPI_MakeEdge(bottomCircle).Edge();
        TopoDS_Wire bottomWire = BRepBuilderAPI_MakeWire(bottomEdge).Wire();

        // 创建顶部圆
        gp_Circ topCircle(gp_Ax2(endPos, axisDir), member.end2Diameter / 2);
        TopoDS_Edge topEdge = BRepBuilderAPI_MakeEdge(topCircle).Edge();
        TopoDS_Wire topWire = BRepBuilderAPI_MakeWire(topEdge).Wire();

        // 放样生成锥形管
        BRepOffsetAPI_ThruSections generator(Standard_True);
        generator.AddWire(bottomWire);
        generator.AddWire(topWire);
        generator.Build();

        memberShape = generator.Shape();
        break;
      }
      }

      // 将杆件添加到杆塔
      if (!memberShape.IsNull()) {
        builder.Add(tower, memberShape);
      }
    }
  }

  return tower;
}


TopoDS_Shape create_pole_tower(const pole_tower_params &params,
                               const gp_Pnt &position, const gp_Dir &direction,
                               const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的杆塔
  TopoDS_Shape tower = create_pole_tower(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(tower, transformation);
  return transform.Shape();
}


TopoDS_Shape
create_single_hook_anchor(const single_hook_anchor_params &params) {
  // 参数验证
  if (params.boltDiameter <= 0)
    throw Standard_ConstructionError("Bolt diameter must be positive");
  if (params.exposedLength < 0)
    throw Standard_ConstructionError("Exposed length must be non-negative");
  if (params.nutCount < 0)
    throw Standard_ConstructionError("Nut count must be non-negative");
  if (params.nutHeight <= 0)
    throw Standard_ConstructionError("Nut height must be positive");
  if (params.nutOD <= params.boltDiameter)
    throw Standard_ConstructionError(
        "Nut OD must be greater than bolt diameter");
  if (params.washerCount < 0)
    throw Standard_ConstructionError("Washer count must be non-negative");
  if (params.washerSize <= 0)
    throw Standard_ConstructionError("Washer size must be positive");
  if (params.washerThickness <= 0)
    throw Standard_ConstructionError("Washer thickness must be positive");
  if (params.anchorLength <= 0)
    throw Standard_ConstructionError("Anchor length must be positive");
  if (params.hookStraightLength <= 0)
    throw Standard_ConstructionError("Hook straight length must be positive");
  if (params.hookDiameter <= 0)
    throw Standard_ConstructionError("Hook diameter must be positive");

  // 创建螺栓主体（圆柱）
  gp_Ax2 boltAxis(gp_Pnt(0, 0, -params.anchorLength + params.exposedLength),
                  gp::DZ());
  TopoDS_Shape bolt =
      BRepPrimAPI_MakeCylinder(boltAxis, params.boltDiameter / 2,
                               params.exposedLength + params.anchorLength)
          .Shape();

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);
  builder.Add(result, bolt);

  // 创建弯钩部分
  if (params.hookDiameter > 0 && params.hookStraightLength > 0) {
    // 定义圆弧控制点（YZ平面）
    gp_Pnt arcStart(0, 0, -params.anchorLength + params.exposedLength);
    gp_Pnt arcEnd(0, params.hookDiameter, arcStart.Z());
    gp_Pnt arcCenter(0, params.hookDiameter / 2, arcStart.Z());

    // 验证三点共圆性
    const double radius = params.hookDiameter / 2;

    // 使用三点构造圆弧
    Handle(Geom_TrimmedCurve) arc;
    gp_Circ circle(gp_Ax2(arcCenter, gp::DX()), radius);
    arc = GC_MakeArcOfCircle(circle, arcStart, arcEnd, Standard_True).Value();

    // 创建路径拓扑结构
    TopoDS_Edge arcEdge = BRepBuilderAPI_MakeEdge(arc).Edge();
    TopoDS_Wire arcPath = BRepBuilderAPI_MakeWire(arcEdge);
    if (arcPath.IsNull()) {
      throw Standard_ConstructionError("路径拓扑结构创建失败");
    }

    // 创建圆形截面（正确坐标系设置）
    gp_Ax2 sectionAxis;
    {
      // 获取路径起点处的切线方向
      double paramFirst;
      double paramLaset;
      Handle(Geom_Curve) curve =
          BRep_Tool::Curve(arcEdge, paramFirst, paramLaset);
      gp_Pnt p;
      gp_Vec tangent;
      curve->D1(paramFirst, p, tangent);

      // 定义截面坐标系：Z轴沿路径切线，Y轴垂直圆弧平面
      sectionAxis = gp_Ax2(arcStart,
                           tangent.Normalized(), // 截面Z轴沿路径方向
                           gp_Dir(0, 0, 1));     // Y轴垂直圆弧平面（YZ平面）
    }

    // 创建截面圆（直径参数验证）
    if (params.boltDiameter <= 0) {
      throw Standard_ConstructionError("螺栓直径必须大于0");
    }
    TopoDS_Wire section = BRepBuilderAPI_MakeWire(
                              BRepBuilderAPI_MakeEdge(
                                  gp_Circ(sectionAxis, params.boltDiameter / 2))
                                  .Edge())
                              .Wire();

    // 构造扫掠特征（严格参数设置）
    BRepOffsetAPI_MakePipeShell pipeMaker(arcPath);
    pipeMaker.Add(section);
    pipeMaker.SetMode(Standard_True); // 使用Frenet坐标系
    pipeMaker.SetTolerance(1e-6);
    pipeMaker.SetMaxDegree(5);
    pipeMaker.Build();

    if (!pipeMaker.IsDone()) {
      Standard_Failure::Raise("扫掠操作失败");
    }
    if (!pipeMaker.MakeSolid()) {
      throw std::runtime_error("Failed to create a solid object from sweep");
    }
    TopoDS_Shape arcTube = pipeMaker.Shape();

    // 1. 创建直段圆管
    gp_Pnt straightStart = arcEnd;
    gp_Pnt straightEnd(arcEnd.X(), arcEnd.Y(),
                       arcEnd.Z() + params.hookStraightLength);

    gp_Ax2 straightAxis(straightStart,
                        gp_Dir(straightEnd.XYZ() - straightStart.XYZ()));
    TopoDS_Shape straightTube =
        BRepPrimAPI_MakeCylinder(straightAxis,
                                 params.boltDiameter /
                                     2, // 使用螺栓直径作为圆管直径
                                 straightStart.Distance(straightEnd))
            .Shape();

    builder.Add(result, straightTube);
    builder.Add(result, arcTube);
  }

  // 创建蝶帽(螺母)
  for (int i = 0; i < params.nutCount; ++i) {
    // 创建六角形螺母
    gp_Pnt nutPos(0, 0,
                  params.washerCount * (params.washerThickness * 1.1) +
                      i * params.nutHeight);

    // 添加随机角度扰动 (0-5度)
    double angleOffset = (i % 2) * (M_PI / 36); // 每隔一个螺母旋转5度(π/36弧度)

    // 创建六边形截面
    BRepBuilderAPI_MakeWire hexWire;
    for (int j = 0; j < 6; j++) {
      double angle = j * M_PI / 3 + angleOffset; // 添加扰动
      gp_Pnt p(params.nutOD / 2 * cos(angle), params.nutOD / 2 * sin(angle), 0);
      hexWire.Add(BRepBuilderAPI_MakeEdge(
                      p, gp_Pnt(params.nutOD / 2 * cos(angle + M_PI / 3),
                                params.nutOD / 2 * sin(angle + M_PI / 3), 0))
                      .Edge());
    }

    // 拉伸成六角柱
    TopoDS_Shape nut =
        BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(hexWire.Wire()).Face(),
                              gp_Vec(0, 0, params.nutHeight))
            .Shape();

    // 移动到正确位置
    gp_Trsf nutTransform;
    nutTransform.SetTranslation(gp_Vec(nutPos.X(), nutPos.Y(), nutPos.Z()));
    BRepBuilderAPI_Transform nutMover(nut, nutTransform);
    builder.Add(result, nutMover.Shape());
  }

  // 创建垫片
  for (int i = 0; i < params.washerCount; ++i) {
    gp_Pnt washerPos(0, 0, i * (params.washerThickness * 1.1));

    TopoDS_Shape washer;
    if (params.washerShape == washer_shape_type::SQUARE) { // 方形垫片
      gp_Pnt corner(-params.washerSize / 2, -params.washerSize / 2,
                    washerPos.Z());
      washer = BRepPrimAPI_MakeBox(corner, params.washerSize, params.washerSize,
                                   params.washerThickness)
                   .Shape();
    } else { // 圆形垫片
      washer = BRepPrimAPI_MakeCylinder(gp_Ax2(washerPos, gp::DZ()),
                                        params.washerSize / 2,
                                        params.washerThickness)
                   .Shape();
    }
    builder.Add(result, washer);
  }

  return result;
}


TopoDS_Shape create_single_hook_anchor(const single_hook_anchor_params &params,
                                       const gp_Pnt &position,
                                       const gp_Dir &normal,
                                       const gp_Dir &xDir) {
  // 验证方向向量
  gp_Dir n = normal;
  gp_Dir x = xDir;

  // 确保方向向量正交
  if (n.IsParallel(x, 1e-6)) {
    // 如果给定方向平行，选择一个默认正交方向
    x = n.IsParallel(gp::DX(), 1e-6) ? gp::DY() : gp::DX();
  }

  // 首先创建标准方向的单钩锚固
  TopoDS_Shape anchor = create_single_hook_anchor(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, n, x);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  // 应用变换
  BRepBuilderAPI_Transform transform(anchor, transformation);
  return transform.Shape();
}


TopoDS_Shape
create_triple_hook_anchor(const triple_hook_anchor_params &params) {
  // 参数验证
  if (params.boltDiameter <= 0)
    throw Standard_ConstructionError("Bolt diameter must be positive");
  if (params.exposedLength < 0)
    throw Standard_ConstructionError("Exposed length must be non-negative");
  if (params.nutCount < 0)
    throw Standard_ConstructionError("Nut count must be non-negative");
  if (params.nutHeight <= 0)
    throw Standard_ConstructionError("Nut height must be positive");
  if (params.nutOD <= params.boltDiameter)
    throw Standard_ConstructionError(
        "Nut OD must be greater than bolt diameter");
  if (params.washerCount < 0)
    throw Standard_ConstructionError("Washer count must be non-negative");
  if (params.washerSize <= 0)
    throw Standard_ConstructionError("Washer size must be positive");
  if (params.washerThickness <= 0)
    throw Standard_ConstructionError("Washer thickness must be positive");
  if (params.anchorLength <= 0)
    throw Standard_ConstructionError("Anchor length must be positive");
  if (params.hookStraightLengthA <= 0 || params.hookStraightLengthB <= 0)
    throw Standard_ConstructionError("Hook straight lengths must be positive");
  if (params.hookDiameter <= 0)
    throw Standard_ConstructionError("Hook diameter must be positive");
  if (params.anchorBarDiameter <= 0)
    throw Standard_ConstructionError("Anchor bar diameter must be positive");

  // 创建螺栓主体（圆柱）
  gp_Ax2 boltAxis(gp_Pnt(0, 0, -params.anchorLength + params.exposedLength),
                  gp::DZ());
  TopoDS_Shape bolt =
      BRepPrimAPI_MakeCylinder(boltAxis, params.boltDiameter / 2,
                               params.exposedLength + params.anchorLength)
          .Shape();

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);
  builder.Add(result, bolt);

  // 创建蝶帽(螺母)
  for (int i = 0; i < params.nutCount; ++i) {
    // 创建六角形螺母
    gp_Pnt nutPos(0, 0,
                  params.washerCount * (params.washerThickness * 1.1) +
                      i * params.nutHeight);

    // 添加随机角度扰动 (0-5度)
    double angleOffset = (i % 2) * (M_PI / 36); // 每隔一个螺母旋转5度(π/36弧度)

    // 创建六边形截面
    BRepBuilderAPI_MakeWire hexWire;
    for (int j = 0; j < 6; j++) {
      double angle = j * M_PI / 3 + angleOffset; // 添加扰动
      gp_Pnt p(params.nutOD / 2 * cos(angle), params.nutOD / 2 * sin(angle), 0);
      hexWire.Add(BRepBuilderAPI_MakeEdge(
                      p, gp_Pnt(params.nutOD / 2 * cos(angle + M_PI / 3),
                                params.nutOD / 2 * sin(angle + M_PI / 3), 0))
                      .Edge());
    }

    // 拉伸成六角柱
    TopoDS_Shape nut =
        BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(hexWire.Wire()).Face(),
                              gp_Vec(0, 0, params.nutHeight))
            .Shape();

    // 移动到正确位置
    gp_Trsf nutTransform;
    nutTransform.SetTranslation(gp_Vec(nutPos.X(), nutPos.Y(), nutPos.Z()));
    BRepBuilderAPI_Transform nutMover(nut, nutTransform);
    builder.Add(result, nutMover.Shape());
  }

  // 创建垫片
  for (int i = 0; i < params.washerCount; ++i) {
    gp_Pnt washerPos(0, 0, i * (params.washerThickness * 1.1));

    TopoDS_Shape washer;
    if (params.washerShape == washer_shape_type::SQUARE) { // 方形垫片
      gp_Pnt corner(-params.washerSize / 2, -params.washerSize / 2,
                    washerPos.Z());
      washer = BRepPrimAPI_MakeBox(corner, params.washerSize, params.washerSize,
                                   params.washerThickness)
                   .Shape();
    } else { // 圆形垫片
      washer = BRepPrimAPI_MakeCylinder(gp_Ax2(washerPos, gp::DZ()),
                                        params.washerSize / 2,
                                        params.washerThickness)
                   .Shape();
    }
    builder.Add(result, washer);
  }

  // 创建三个弯钩
  for (int i = 0; i < 3; i++) {
    // 计算每个钩子的角度 (0°, 120°, 240°)
    double angle = i * (2 * M_PI / 3);

    // 1. 创建直段A (圆柱)
    gp_Pnt straightAStart(
        (params.boltDiameter / 2 + params.anchorBarDiameter / 2) * cos(angle),
        (params.boltDiameter / 2 + params.anchorBarDiameter / 2) * sin(angle),
        -params.anchorLength + params.exposedLength +
            params.hookStraightLengthA + params.hookStraightLengthB);
    gp_Pnt straightAEnd(
        (params.boltDiameter / 2 + params.anchorBarDiameter / 2) * cos(angle),
        (params.boltDiameter / 2 + params.anchorBarDiameter / 2) * sin(angle),
        -params.anchorLength + params.exposedLength);

    gp_Ax2 straightAAxis(straightAStart,
                         gp_Dir(straightAEnd.XYZ() - straightAStart.XYZ()));
    TopoDS_Shape straightATube =
        BRepPrimAPI_MakeCylinder(straightAAxis, params.anchorBarDiameter / 2,
                                 straightAStart.Distance(straightAEnd))
            .Shape();
    builder.Add(result, straightATube);

    // 2. 创建弯段 (使用BRepOffsetAPI_MakePipeShell)
    gp_Pnt arcStart = straightAEnd;
    // 圆弧中心点计算修正 - 确保圆弧开口指向+Z方向
    gp_Pnt arcCenter(
        arcStart.X() + params.hookDiameter / 2 * cos(angle), // 垂直偏移
        arcStart.Y() + params.hookDiameter / 2 * sin(angle),
        arcStart.Z() - params.hookDiameter / 2); // Z坐标下移直径的一半

    gp_Pnt arcEnd(arcStart.X() - params.hookDiameter * cos(angle + M_PI),
                  arcStart.Y() - params.hookDiameter * sin(angle + M_PI),
                  arcStart.Z()); // 终点保持与起点相同Z坐标

    const double radius = params.hookDiameter / 2;

    // 创建圆弧路径
    Handle(Geom_TrimmedCurve) arc =
        GC_MakeArcOfCircle(arcStart, arcCenter, arcEnd).Value();
    TopoDS_Edge arcEdge = BRepBuilderAPI_MakeEdge(arc).Edge();
    TopoDS_Wire arcPath = BRepBuilderAPI_MakeWire(arcEdge);

    // 创建截面坐标系（沿圆弧切线方向）
    gp_Ax2 sectionAxis(arcStart, gp_Dir(0, 0, 1),           // Z轴向上
                       gp_Dir(-sin(angle), cos(angle), 0)); // 切线方向
    TopoDS_Wire section =
        BRepBuilderAPI_MakeWire(
            BRepBuilderAPI_MakeEdge(
                gp_Circ(sectionAxis, params.anchorBarDiameter / 2))
                .Edge())
            .Wire();

    // 扫掠生成弯段
    BRepOffsetAPI_MakePipeShell pipeMaker(arcPath);
    pipeMaker.Add(section);
    pipeMaker.SetMode(Standard_True); // 使用Frenet坐标系
    pipeMaker.SetTolerance(1e-6);
    pipeMaker.SetMaxDegree(5);
    pipeMaker.Build();

    if (!pipeMaker.IsDone()) {
      Standard_Failure::Raise("扫掠操作失败");
    }
    if (!pipeMaker.MakeSolid()) {
      throw std::runtime_error("Failed to create a solid object from sweep");
    }
    builder.Add(result, pipeMaker.Shape());

    // 3. 创建直段B (圆柱)
    gp_Pnt straightBEnd(arcEnd.X(), arcEnd.Y(),
                        arcEnd.Z() + params.hookStraightLengthB);

    gp_Ax2 straightBAxis(arcEnd, gp_Dir(straightBEnd.XYZ() - arcEnd.XYZ()));
    TopoDS_Shape straightBTube =
        BRepPrimAPI_MakeCylinder(straightBAxis, params.anchorBarDiameter / 2,
                                 arcEnd.Distance(straightBEnd))
            .Shape();
    builder.Add(result, straightBTube);
  }

  return result;
}


TopoDS_Shape create_triple_hook_anchor(const triple_hook_anchor_params &params,
                                       const gp_Pnt &position,
                                       const gp_Dir &normal,
                                       const gp_Dir &xDir) {
  // 首先创建标准方向的三钩锚固
  TopoDS_Shape anchor = create_triple_hook_anchor(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(anchor, transformation);
  return transform.Shape();
}

TopoDS_Shape create_ribbed_anchor(const ribbed_anchor_params &params) {
  // 参数验证
  if (params.boltDiameter <= 0.0)
    throw Standard_ConstructionError("Bolt diameter must be positive");
  if (params.exposedLength < 0.0)
    throw Standard_ConstructionError("Exposed length must be non-negative");
  if (params.nutCount < 0)
    throw Standard_ConstructionError("Nut count must be non-negative");
  if (params.washerCount < 0)
    throw Standard_ConstructionError("Washer count must be non-negative");
  if (params.anchorLength <= 0.0)
    throw Standard_ConstructionError("Anchor length must be positive");
  if (params.basePlateSize <= 0.0)
    throw Standard_ConstructionError("Base plate size must be positive");
  if (params.ribTopWidth <= 0.0 || params.ribBottomWidth <= 0.0)
    throw Standard_ConstructionError("Rib widths must be positive");
  if (params.basePlateThickness <= 0.0 || params.ribThickness <= 0.0)
    throw Standard_ConstructionError(
        "Plate and rib thickness must be positive");
  if (params.ribHeight <= 0.0)
    throw Standard_ConstructionError("Rib height must be positive");

  // 创建螺栓主体 (Z轴方向)
  gp_Ax2 boltAxis(gp_Pnt(0, 0, -params.anchorLength + params.exposedLength),
                  gp::DZ());
  TopoDS_Shape bolt =
      BRepPrimAPI_MakeCylinder(boltAxis, params.boltDiameter / 2,
                               params.exposedLength + params.anchorLength)
          .Shape();

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);
  builder.Add(result, bolt);

  // 创建下锚板
  gp_Pnt basePlateCenter(0, 0, 0);
  TopoDS_Shape basePlate;
  if (params.washerShape == washer_shape_type::SQUARE) { // 方形垫片
    basePlate = BRepPrimAPI_MakeBox(gp_Pnt(-params.basePlateSize / 2,
                                           -params.basePlateSize / 2,
                                           -params.basePlateThickness / 2),
                                    params.basePlateSize, params.basePlateSize,
                                    params.basePlateThickness)
                    .Shape();
  } else { // 圆形垫片
    basePlate = BRepPrimAPI_MakeCylinder(gp_Ax2(basePlateCenter, gp::DZ()),
                                         params.basePlateSize / 2,
                                         params.basePlateThickness)
                    .Shape();
  }
  builder.Add(result, basePlate);

  // 创建肋板 (4个对称肋板)
  for (int i = 0; i < 4; ++i) {
    double angle = i * M_PI_2; // 0, 90, 180, 270度

    // 创建肋板多边形点
    gp_Pnt p1(params.boltDiameter / 2 * cos(angle),
              params.boltDiameter / 2 * sin(angle),
              params.basePlateThickness + params.ribHeight);
    gp_Pnt p2(params.boltDiameter / 2 * cos(angle) +
                  params.ribTopWidth / 2 * cos(angle),
              params.boltDiameter / 2 * sin(angle) +
                  params.ribTopWidth / 2 * sin(angle),
              params.basePlateThickness + params.ribHeight);
    gp_Pnt p3(params.boltDiameter / 2 * cos(angle) +
                  params.ribBottomWidth / 2 * cos(angle),
              params.boltDiameter / 2 * sin(angle) +
                  params.ribBottomWidth / 2 * sin(angle),
              params.basePlateThickness);
    gp_Pnt p4(params.boltDiameter / 2 * cos(angle),
              params.boltDiameter / 2 * sin(angle), params.basePlateThickness);

    // 创建肋板面
    BRepBuilderAPI_MakePolygon poly;
    poly.Add(p1);
    poly.Add(p2);
    poly.Add(p3);
    poly.Add(p4);
    poly.Close();
    TopoDS_Face face = BRepBuilderAPI_MakeFace(poly.Wire()).Face();

    // 拉伸成肋板
    gp_Vec ribVec(params.ribThickness * cos(angle + M_PI_4),
                  params.ribThickness * sin(angle + M_PI_4), 0);
    TopoDS_Shape rib = BRepPrimAPI_MakePrism(face, ribVec).Shape();

    builder.Add(result, rib);
  }

  // 创建蝶帽(螺母)
  for (int i = 0; i < params.nutCount; ++i) {
    // 创建六角形螺母
    gp_Pnt nutPos(0, 0,
                  params.basePlateThickness + params.ribHeight +
                      params.washerCount * (params.washerThickness * 1.1) +
                      i * params.nutHeight);

    // 添加随机角度扰动 (0-5度)
    double angleOffset = (i % 2) * (M_PI / 36); // 每隔一个螺母旋转5度(π/36弧度)

    // 创建六边形截面
    BRepBuilderAPI_MakeWire hexWire;
    for (int j = 0; j < 6; j++) {
      double angle = j * M_PI / 3 + angleOffset; // 添加扰动
      gp_Pnt p(params.nutOD / 2 * cos(angle), params.nutOD / 2 * sin(angle), 0);
      hexWire.Add(BRepBuilderAPI_MakeEdge(
                      p, gp_Pnt(params.nutOD / 2 * cos(angle + M_PI / 3),
                                params.nutOD / 2 * sin(angle + M_PI / 3), 0))
                      .Edge());
    }

    // 拉伸成六角柱
    TopoDS_Shape nut =
        BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(hexWire.Wire()).Face(),
                              gp_Vec(0, 0, params.nutHeight))
            .Shape();

    // 移动到正确位置
    gp_Trsf nutTransform;
    nutTransform.SetTranslation(gp_Vec(nutPos.X(), nutPos.Y(), nutPos.Z()));
    BRepBuilderAPI_Transform nutMover(nut, nutTransform);
    builder.Add(result, nutMover.Shape());
  }

  // 创建垫片
  for (int i = 0; i < params.washerCount; ++i) {
    gp_Pnt washerPos(0, 0,
                     params.basePlateThickness + params.ribHeight +
                         i * (params.washerThickness * 1.1));

    TopoDS_Shape washer;
    if (params.washerShape == washer_shape_type::SQUARE) { // 方形垫片
      gp_Pnt corner(-params.washerSize / 2, -params.washerSize / 2,
                    washerPos.Z());
      washer = BRepPrimAPI_MakeBox(corner, params.washerSize, params.washerSize,
                                   params.washerThickness)
                   .Shape();
    } else { // 圆形垫片
      washer = BRepPrimAPI_MakeCylinder(gp_Ax2(washerPos, gp::DZ()),
                                        params.washerSize / 2,
                                        params.washerThickness)
                   .Shape();
    }
    builder.Add(result, washer);
  }

  return result;
}


TopoDS_Shape create_ribbed_anchor(const ribbed_anchor_params &params,
                                  const gp_Pnt &position, const gp_Dir &normal,
                                  const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 创建标准方向的锚固
  TopoDS_Shape anchor = create_ribbed_anchor(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(anchor, transformation);
  return transform.Shape();
}


TopoDS_Shape create_nut_anchor(const nut_anchor_params &params) {
  // 参数验证
  if (params.boltDiameter <= 0)
    throw Standard_ConstructionError("Bolt diameter must be positive");
  if (params.exposedLength < 0)
    throw Standard_ConstructionError("Exposed length must be non-negative");
  if (params.nutCount < 0)
    throw Standard_ConstructionError("Nut count must be non-negative");
  if (params.nutHeight <= 0)
    throw Standard_ConstructionError("Nut height must be positive");
  if (params.nutOD <= params.boltDiameter)
    throw Standard_ConstructionError(
        "Nut OD must be greater than bolt diameter");
  if (params.washerCount < 0)
    throw Standard_ConstructionError("Washer count must be non-negative");
  if (params.washerSize <= 0)
    throw Standard_ConstructionError("Washer size must be positive");
  if (params.washerThickness <= 0)
    throw Standard_ConstructionError("Washer thickness must be positive");
  if (params.anchorLength <= 0)
    throw Standard_ConstructionError("Anchor length must be positive");
  if (params.basePlateSize <= 0)
    throw Standard_ConstructionError("Base plate size must be positive");
  if (params.basePlateThickness <= 0)
    throw Standard_ConstructionError("Base plate thickness must be positive");
  if (params.boltToPlateDistance < 0)
    throw Standard_ConstructionError(
        "Bolt to plate distance must be non-negative");

  // 创建螺栓主体 (Z轴方向)
  gp_Ax2 boltAxis(gp_Pnt(0, 0, -params.anchorLength + params.exposedLength),
                  gp::DZ());
  TopoDS_Shape bolt =
      BRepPrimAPI_MakeCylinder(boltAxis, params.boltDiameter / 2,
                               params.exposedLength + params.anchorLength)
          .Shape();

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);
  builder.Add(result, bolt);

  // 创建下锚板
  double plateZ = -params.anchorLength + params.boltToPlateDistance;
  TopoDS_Shape basePlate;
  if (params.washerShape == washer_shape_type::SQUARE) { // 方形垫片
    basePlate = BRepPrimAPI_MakeBox(gp_Pnt(-params.basePlateSize / 2,
                                           -params.basePlateSize / 2, plateZ),
                                    params.basePlateSize, params.basePlateSize,
                                    params.basePlateThickness)
                    .Shape();
  } else { // 圆形垫片
    basePlate = BRepPrimAPI_MakeCylinder(
                    gp_Ax2(gp_Pnt(0, 0, plateZ + params.basePlateThickness / 2),
                           gp::DZ()),
                    params.basePlateSize / 2, params.basePlateThickness)
                    .Shape();
  }
  builder.Add(result, basePlate);

  // 创建蝶帽(螺母)
  for (int i = 0; i < params.nutCount; ++i) {
    // 创建六角形螺母
    gp_Pnt nutPos(0, 0,
                  plateZ + params.washerCount * (params.washerThickness * 1.1) +
                      i * params.nutHeight);

    // 添加随机角度扰动 (0-5度)
    double angleOffset = (i % 2) * (M_PI / 36); // 每隔一个螺母旋转5度(π/36弧度)

    // 创建六边形截面
    BRepBuilderAPI_MakeWire hexWire;
    for (int j = 0; j < 6; j++) {
      double angle = j * M_PI / 3 + angleOffset; // 添加扰动
      gp_Pnt p(params.nutOD / 2 * cos(angle), params.nutOD / 2 * sin(angle), 0);
      hexWire.Add(BRepBuilderAPI_MakeEdge(
                      p, gp_Pnt(params.nutOD / 2 * cos(angle + M_PI / 3),
                                params.nutOD / 2 * sin(angle + M_PI / 3), 0))
                      .Edge());
    }

    // 拉伸成六角柱
    TopoDS_Shape nut =
        BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(hexWire.Wire()).Face(),
                              gp_Vec(0, 0, params.nutHeight))
            .Shape();

    // 移动到正确位置
    gp_Trsf nutTransform;
    nutTransform.SetTranslation(gp_Vec(nutPos.X(), nutPos.Y(), nutPos.Z()));
    BRepBuilderAPI_Transform nutMover(nut, nutTransform);
    builder.Add(result, nutMover.Shape());
  }

  // 创建垫片
  for (int i = 0; i < params.washerCount; ++i) {
    gp_Pnt washerPos(0, 0, plateZ + i * (params.washerThickness * 1.1));

    TopoDS_Shape washer;
    if (params.washerShape == washer_shape_type::SQUARE) { // 方形垫片
      gp_Pnt corner(-params.washerSize / 2, -params.washerSize / 2,
                    washerPos.Z());
      washer = BRepPrimAPI_MakeBox(corner, params.washerSize, params.washerSize,
                                   params.washerThickness)
                   .Shape();
    } else { // 圆形垫片
      washer = BRepPrimAPI_MakeCylinder(gp_Ax2(washerPos, gp::DZ()),
                                        params.washerSize / 2,
                                        params.washerThickness)
                   .Shape();
    }
    builder.Add(result, washer);
  }

  return result;
}


TopoDS_Shape create_nut_anchor(const nut_anchor_params &params,
                               const gp_Pnt &position, const gp_Dir &normal,
                               const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 创建标准方向的锚固
  TopoDS_Shape anchor = create_nut_anchor(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(anchor, transformation);
  return transform.Shape();
}


TopoDS_Shape create_triple_arm_anchor(const triple_arm_anchor_params &params) {
  // 参数验证
  if (params.boltDiameter <= 0)
    throw Standard_ConstructionError("Bolt diameter must be positive");
  if (params.exposedLength < 0)
    throw Standard_ConstructionError("Exposed length must be non-negative");
  if (params.nutCount < 0)
    throw Standard_ConstructionError("Nut count must be non-negative");
  if (params.nutHeight <= 0)
    throw Standard_ConstructionError("Nut height must be positive");
  if (params.nutOD <= params.boltDiameter)
    throw Standard_ConstructionError(
        "Nut OD must be greater than bolt diameter");
  if (params.washerCount < 0)
    throw Standard_ConstructionError("Washer count must be non-negative");
  if (params.washerSize <= 0)
    throw Standard_ConstructionError("Washer size must be positive");
  if (params.washerThickness <= 0)
    throw Standard_ConstructionError("Washer thickness must be positive");
  if (params.anchorLength <= 0)
    throw Standard_ConstructionError("Anchor length must be positive");
  if (params.armDiameter <= 0)
    throw Standard_ConstructionError("Arm diameter must be positive");
  if (params.armStraightLength <= 0)
    throw Standard_ConstructionError("Arm straight length must be positive");
  if (params.armBendLength <= 0)
    throw Standard_ConstructionError("Arm bend length must be positive");
  if (params.armBendAngle <= 0 || params.armBendAngle >= M_PI)
    throw Standard_ConstructionError("Arm bend angle must be between 0 and PI");

  // 创建螺栓主体（圆柱）
  gp_Ax2 boltAxis(gp_Pnt(0, 0, -params.anchorLength + params.exposedLength),
                  gp::DZ());
  TopoDS_Shape bolt =
      BRepPrimAPI_MakeCylinder(boltAxis, params.boltDiameter / 2,
                               params.exposedLength + params.anchorLength)
          .Shape();

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);
  builder.Add(result, bolt);

  // 创建蝶帽(螺母)
  for (int i = 0; i < params.nutCount; ++i) {
    // 创建六角形螺母
    gp_Pnt nutPos(0, 0,
                  params.washerCount * (params.washerThickness * 1.1) +
                      i * params.nutHeight);

    // 添加随机角度扰动 (0-5度)
    double angleOffset = (i % 2) * (M_PI / 36); // 每隔一个螺母旋转5度(π/36弧度)

    // 创建六边形截面
    BRepBuilderAPI_MakeWire hexWire;
    for (int j = 0; j < 6; j++) {
      double angle = j * M_PI / 3 + angleOffset; // 添加扰动
      gp_Pnt p(params.nutOD / 2 * cos(angle), params.nutOD / 2 * sin(angle), 0);
      hexWire.Add(BRepBuilderAPI_MakeEdge(
                      p, gp_Pnt(params.nutOD / 2 * cos(angle + M_PI / 3),
                                params.nutOD / 2 * sin(angle + M_PI / 3), 0))
                      .Edge());
    }

    // 拉伸成六角柱
    TopoDS_Shape nut =
        BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(hexWire.Wire()).Face(),
                              gp_Vec(0, 0, params.nutHeight))
            .Shape();

    // 移动到正确位置
    gp_Trsf nutTransform;
    nutTransform.SetTranslation(gp_Vec(nutPos.X(), nutPos.Y(), nutPos.Z()));
    BRepBuilderAPI_Transform nutMover(nut, nutTransform);
    builder.Add(result, nutMover.Shape());
  }

  // 创建垫片
  for (int i = 0; i < params.washerCount; ++i) {
    gp_Pnt washerPos(0, 0, i * (params.washerThickness * 1.1));

    TopoDS_Shape washer;
    if (params.washerShape == washer_shape_type::SQUARE) { // 方形垫片
      gp_Pnt corner(-params.washerSize / 2, -params.washerSize / 2,
                    washerPos.Z());
      washer = BRepPrimAPI_MakeBox(corner, params.washerSize, params.washerSize,
                                   params.washerThickness)
                   .Shape();
    } else { // 圆形垫片
      washer = BRepPrimAPI_MakeCylinder(gp_Ax2(washerPos, gp::DZ()),
                                        params.washerSize / 2,
                                        params.washerThickness)
                   .Shape();
    }
    builder.Add(result, washer);
  }

  // 创建三支弯臂
  TopoDS_Shape arms;
  for (int i = 0; i < 3; ++i) {
    double angle = i * (2 * M_PI / 3); // 0°, 120°, 240°

    // 创建直段
    gp_Pnt startPoint(
        (params.boltDiameter / 2 + params.armDiameter / 2) * cos(angle),
        (params.boltDiameter / 2 + params.armDiameter / 2) * sin(angle),
        -params.anchorLength + params.exposedLength + params.armStraightLength);
    gp_Pnt endPoint(
        (params.boltDiameter / 2 + params.armDiameter / 2) * cos(angle),
        (params.boltDiameter / 2 + params.armDiameter / 2) * sin(angle),
        -params.anchorLength + params.exposedLength);

    // 创建弯折段
    gp_Pnt bendEndPoint(endPoint.X() + params.armBendLength * cos(angle) *
                                           cos(params.armBendAngle),
                        endPoint.Y() + params.armBendLength * sin(angle) *
                                           cos(params.armBendAngle),
                        endPoint.Z() -
                            params.armBendLength * sin(params.armBendAngle));

    BRepBuilderAPI_MakeWire endWire;
    endWire.Add(BRepBuilderAPI_MakeEdge(startPoint, endPoint).Edge());
    endWire.Add(BRepBuilderAPI_MakeEdge(endPoint, bendEndPoint).Edge());

    // 创建截面坐标系（沿圆弧切线方向）
    gp_Ax2 sectionAxis(startPoint, gp_Dir(0, 0, 1),         // Z轴向上
                       gp_Dir(-sin(angle), cos(angle), 0)); // 切线方向
    TopoDS_Wire section = BRepBuilderAPI_MakeWire(
                              BRepBuilderAPI_MakeEdge(
                                  gp_Circ(sectionAxis, params.armDiameter / 2))
                                  .Edge())
                              .Wire();

    // 扫掠生成弯段
    BRepOffsetAPI_MakePipeShell pipeMaker(endWire);
    pipeMaker.Add(section);
    pipeMaker.SetMode(Standard_True); // 使用Frenet坐标系
    pipeMaker.SetTolerance(1e-6);
    pipeMaker.SetMaxDegree(5);
    pipeMaker.Build();

    if (!pipeMaker.IsDone()) {
      Standard_Failure::Raise("扫掠操作失败");
    }
    if (!pipeMaker.MakeSolid()) {
      throw std::runtime_error("Failed to create a solid object from sweep");
    }
    builder.Add(result, pipeMaker.Shape());
  }

  return result;
}


TopoDS_Shape create_triple_arm_anchor(const triple_arm_anchor_params &params,
                                      const gp_Pnt &position,
                                      const gp_Dir &normal,
                                      const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 创建标准方向的锚固
  TopoDS_Shape anchor = create_triple_arm_anchor(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(anchor, transformation);
  return transform.Shape();
}


TopoDS_Shape
create_positioning_plate_anchor(const positioning_plate_anchor_params &params) {
  // 参数验证
  if (params.boltDiameter <= 0)
    throw Standard_ConstructionError("Bolt diameter must be positive");
  if (params.exposedLength < 0)
    throw Standard_ConstructionError("Exposed length must be non-negative");
  if (params.nutCount < 0)
    throw Standard_ConstructionError("Nut count must be non-negative");
  if (params.nutHeight <= 0)
    throw Standard_ConstructionError("Nut height must be positive");
  if (params.nutOD <= params.boltDiameter)
    throw Standard_ConstructionError(
        "Nut OD must be greater than bolt diameter");
  if (params.washerCount < 0)
    throw Standard_ConstructionError("Washer count must be non-negative");
  if (params.washerSize <= 0)
    throw Standard_ConstructionError("Washer size must be positive");
  if (params.washerThickness <= 0)
    throw Standard_ConstructionError("Washer thickness must be positive");
  if (params.anchorLength <= 0)
    throw Standard_ConstructionError("Anchor length must be positive");
  if (params.plateLength <= 0)
    throw Standard_ConstructionError("Plate length must be positive");
  if (params.plateThickness <= 0)
    throw Standard_ConstructionError("Plate thickness must be positive");
  if (params.toBaseDistance < 0)
    throw Standard_ConstructionError("To base distance must be non-negative");
  if (params.toBottomDistance < 0)
    throw Standard_ConstructionError("To bottom distance must be non-negative");
  if (params.groutHoleDiameter <= 0)
    throw Standard_ConstructionError("Grout hole diameter must be positive");

  // 创建螺栓主体（圆柱）
  gp_Ax2 boltAxis(gp_Pnt(0, 0, -params.anchorLength + params.exposedLength),
                  gp::DZ());
  TopoDS_Shape bolt =
      BRepPrimAPI_MakeCylinder(boltAxis, params.boltDiameter / 2,
                               params.exposedLength + params.anchorLength)
          .Shape();

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);
  builder.Add(result, bolt);

  // 创建定位板
  double plateTopZ = -params.toBaseDistance + params.plateThickness / 2;
  TopoDS_Shape plateTop =
      BRepPrimAPI_MakeBox(
          gp_Pnt(-params.plateLength / 2, -params.plateLength / 2, plateTopZ),
          params.plateLength, params.plateLength, params.plateThickness)
          .Shape();

  double plateBottomZ = -params.anchorLength + params.exposedLength +
                        params.toBottomDistance - params.plateThickness / 2;
  TopoDS_Shape plateBottom =
      BRepPrimAPI_MakeBox(gp_Pnt(-params.plateLength / 2,
                                 -params.plateLength / 2, plateBottomZ),
                          params.plateLength, params.plateLength,
                          params.plateThickness)
          .Shape();

  // 创建灌注孔
  if (params.groutHoleDiameter > 0) {
    TopoDS_Shape hole =
        BRepPrimAPI_MakeCylinder(
            gp_Ax2(gp_Pnt(0, 0, -params.anchorLength + params.exposedLength),
                   gp::DZ()),
            params.groutHoleDiameter / 2,
            params.exposedLength + params.anchorLength)
            .Shape();
    plateTop = BRepAlgoAPI_Cut(plateTop, hole).Shape();
    plateBottom = BRepAlgoAPI_Cut(plateBottom, hole).Shape();
  }

  builder.Add(result, plateTop);
  builder.Add(result, plateBottom);

  // 创建蝶帽(螺母)
  for (int i = 0; i < params.nutCount; ++i) {
    // 创建六角形螺母
    gp_Pnt nutPos(0, 0,
                  params.washerCount * (params.washerThickness * 1.1) +
                      i * params.nutHeight);

    // 添加随机角度扰动 (0-5度)
    double angleOffset = (i % 2) * (M_PI / 36); // 每隔一个螺母旋转5度(π/36弧度)

    // 创建六边形截面
    BRepBuilderAPI_MakeWire hexWire;
    for (int j = 0; j < 6; j++) {
      double angle = j * M_PI / 3 + angleOffset; // 添加扰动
      gp_Pnt p(params.nutOD / 2 * cos(angle), params.nutOD / 2 * sin(angle), 0);
      hexWire.Add(BRepBuilderAPI_MakeEdge(
                      p, gp_Pnt(params.nutOD / 2 * cos(angle + M_PI / 3),
                                params.nutOD / 2 * sin(angle + M_PI / 3), 0))
                      .Edge());
    }

    // 拉伸成六角柱
    TopoDS_Shape nut =
        BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(hexWire.Wire()).Face(),
                              gp_Vec(0, 0, params.nutHeight))
            .Shape();

    // 移动到正确位置
    gp_Trsf nutTransform;
    nutTransform.SetTranslation(gp_Vec(nutPos.X(), nutPos.Y(), nutPos.Z()));
    BRepBuilderAPI_Transform nutMover(nut, nutTransform);
    builder.Add(result, nutMover.Shape());
  }

  // 创建垫片
  for (int i = 0; i < params.washerCount; ++i) {
    gp_Pnt washerPos(0, 0, i * (params.washerThickness * 1.1));

    TopoDS_Shape washer;
    if (params.washerShape == washer_shape_type::SQUARE) { // 方形垫片
      gp_Pnt corner(-params.washerSize / 2, -params.washerSize / 2,
                    washerPos.Z());
      washer = BRepPrimAPI_MakeBox(corner, params.washerSize, params.washerSize,
                                   params.washerThickness)
                   .Shape();
    } else { // 圆形垫片
      washer = BRepPrimAPI_MakeCylinder(gp_Ax2(washerPos, gp::DZ()),
                                        params.washerSize / 2,
                                        params.washerThickness)
                   .Shape();
    }
    builder.Add(result, washer);
  }

  return result;
}


TopoDS_Shape
create_positioning_plate_anchor(const positioning_plate_anchor_params &params,
                                const gp_Pnt &position, const gp_Dir &normal,
                                const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 创建标准方向的锚固
  TopoDS_Shape anchor = create_positioning_plate_anchor(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(anchor, transformation);
  return transform.Shape();
}


TopoDS_Shape create_stub_angle(const stub_angle_params &params) {
  // 参数验证
  if (params.legWidth <= 0)
    throw Standard_ConstructionError("Leg width must be positive");
  if (params.thickness <= 0)
    throw Standard_ConstructionError("Thickness must be positive");
  if (params.thickness >= params.legWidth)
    throw Standard_ConstructionError("Thickness must be less than leg width");
  if (params.exposedLength < 0)
    throw Standard_ConstructionError("Exposed length must be non-negative");
  if (params.anchorLength <= 0)
    throw Standard_ConstructionError("Anchor length must be positive");

  // 创建角钢截面轮廓
  gp_Pnt p1(0, 0, 0);
  gp_Pnt p2(params.legWidth, 0, 0);
  gp_Pnt p3(params.legWidth, params.thickness, 0);
  gp_Pnt p4(params.thickness, params.thickness, 0);
  gp_Pnt p5(params.thickness, params.legWidth, 0);
  gp_Pnt p6(0, params.legWidth, 0);

  BRepBuilderAPI_MakePolygon polyMaker;
  polyMaker.Add(p1);
  polyMaker.Add(p2);
  polyMaker.Add(p3);
  polyMaker.Add(p4);
  polyMaker.Add(p5);
  polyMaker.Add(p6);
  polyMaker.Add(p1);
  TopoDS_Wire wire = polyMaker.Wire();

  // 考虑坡度创建拉伸方向向量
  gp_Vec extrusionVec(0, 0, -params.anchorLength);
  if (params.slope != 0) {
    double slopeRad = params.slope * M_PI / 180.0;
    extrusionVec.SetX(-tan(slopeRad) * params.anchorLength);
  }

  // 创建角钢主体
  TopoDS_Shape angleSteel =
      BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(wire).Face(), extrusionVec)
          .Shape();

  // 创建露头部分
  if (params.exposedLength > 0) {
    gp_Vec exposedVec(0, 0, params.exposedLength);
    if (params.slope != 0) {
      double slopeRad = params.slope * M_PI / 180.0;
      exposedVec.SetX(tan(slopeRad) * params.exposedLength);
    }
    TopoDS_Shape exposedPart =
        BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(wire).Face(), exposedVec)
            .Shape();
    angleSteel = BRepAlgoAPI_Fuse(angleSteel, exposedPart).Shape();
  }

  return angleSteel;
}


TopoDS_Shape create_stub_angle(const stub_angle_params &params,
                               const gp_Pnt &position, const gp_Dir &normal,
                               const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 创建标准方向的角钢
  TopoDS_Shape angleSteel = create_stub_angle(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(angleSteel, transformation);
  return transform.Shape();
}


TopoDS_Shape create_stub_tube(const stub_tube_params &params) {
  // 参数验证
  if (params.diameter <= 0)
    throw Standard_ConstructionError("Diameter must be positive");
  if (params.thickness <= 0)
    throw Standard_ConstructionError("Thickness must be positive");
  if (params.thickness >= params.diameter / 2)
    throw Standard_ConstructionError("Thickness must be less than radius");
  if (params.exposedLength < 0)
    throw Standard_ConstructionError("Exposed length must be non-negative");
  if (params.anchorLength <= 0)
    throw Standard_ConstructionError("Anchor length must be positive");

  // 创建路径线（沿Z轴）
  gp_Pnt startPoint(0, 0, 0);
  gp_Pnt endPoint(0, 0, -params.anchorLength);
  if (params.slope != 0) {
    double slopeRad = params.slope * M_PI / 180.0;
    endPoint.SetX(-tan(slopeRad) *
                  (params.anchorLength + params.exposedLength));
  }

  BRepBuilderAPI_MakeWire pathWire;
  pathWire.Add(BRepBuilderAPI_MakeEdge(startPoint, endPoint).Edge());

  // 创建圆形截面
  gp_Circ circle(gp_Ax2(gp::Origin(), gp::DZ()), params.diameter / 2);
  TopoDS_Edge circleEdge = BRepBuilderAPI_MakeEdge(circle).Edge();
  BRepBuilderAPI_MakeWire circleWire;
  circleWire.Add(circleEdge);

  // 使用管道生成器创建钢管
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire.Wire());
  pipeMaker.Add(circleWire.Wire());
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create pipe");
  }
  if (!pipeMaker.MakeSolid()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }

  TopoDS_Shape tube = pipeMaker.Shape();

  // 创建露头部分（如果存在）
  if (params.exposedLength > 0) {
    gp_Pnt exposedEnd(0, 0, params.exposedLength);
    if (params.slope != 0) {
      double slopeRad = params.slope * M_PI / 180.0;
      exposedEnd.SetX(tan(slopeRad) * params.exposedLength);
    }

    BRepBuilderAPI_MakeWire exposedPath;
    exposedPath.Add(BRepBuilderAPI_MakeEdge(startPoint, exposedEnd).Edge());

    BRepOffsetAPI_MakePipeShell exposedPipe(exposedPath.Wire());
    exposedPipe.Add(circleWire.Wire());
    exposedPipe.Build();

    if (!exposedPipe.IsDone()) {
      throw Standard_ConstructionError("Failed to create exposed pipe");
    }
    if (!exposedPipe.MakeSolid()) {
      throw std::runtime_error("Failed to create a solid object from sweep");
    }
    tube = BRepAlgoAPI_Fuse(tube, exposedPipe.Shape()).Shape();
  }

  return tube;
}


TopoDS_Shape create_stub_tube(const stub_tube_params &params,
                              const gp_Pnt &position, const gp_Dir &normal,
                              const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 创建标准方向的钢管
  TopoDS_Shape tube = create_stub_tube(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(tube, transformation);
  return transform.Shape();
}


TopoDS_Shape create_u_shaped_ring(const u_shaped_ring_params &params) {
  // 参数验证
  if (params.thickness <= 0)
    throw Standard_ConstructionError("Thickness must be positive");
  if (params.height <= 0)
    throw Standard_ConstructionError("Height must be positive");
  if (params.radius <= 0)
    throw Standard_ConstructionError("Radius must be positive");
  if (params.length <= 0)
    throw Standard_ConstructionError("Length must be positive");

  double chord = params.height + params.thickness; // 开口高度即弦长
  double half_chord = chord / 2;
  // 弦长超过 2*radius 时圆弧不存在, sqrt 会得到 NaN 并在后续 MakeEdge 崩溃
  if (half_chord >= params.radius) {
    throw Standard_ConstructionError(
        "U-shaped ring: (height+thickness)/2 must be smaller than radius");
  }
  double arcHeight =
      params.radius - sqrt(pow(params.radius, 2) - pow(half_chord, 2));

  // 创建伸部分
  gp_Pnt pathStart(0, 0, half_chord);
  gp_Pnt arcStart(params.length - arcHeight, 0,
                  half_chord); // 路径起点

  gp_Pnt arcEnd(arcStart.X(), arcStart.Y(), -half_chord);
  double radius = params.radius;             // 用户输入的圆弧半径
  double center_offset = radius - arcHeight; // 中心偏移量
  gp_Pnt arcCenter(arcStart.X() + center_offset, arcStart.Y(),
                   arcStart.Z() - half_chord // 垂直方向中心位置
  );
  gp_Pnt pathEnd(0, arcEnd.Y(),
                 arcEnd.Z()); // 路径终点

  TopoDS_Edge edge1 = BRepBuilderAPI_MakeEdge(pathStart, arcStart).Edge();
  Handle(Geom_TrimmedCurve) arc =
      GC_MakeArcOfCircle(arcStart, arcCenter, arcEnd).Value();
  if (arc.IsNull()) {
    throw Standard_ConstructionError(
        "U-shaped ring: failed to build the arc segment");
  }
  TopoDS_Edge arcEdge = BRepBuilderAPI_MakeEdge(arc).Edge();
  TopoDS_Edge edge3 = BRepBuilderAPI_MakeEdge(arcEnd, pathEnd).Edge();

  BRepBuilderAPI_MakeWire wireMaker(edge1);
  wireMaker.Add(arcEdge);
  wireMaker.Add(edge3);
  TopoDS_Wire pathWire = wireMaker.Wire();

  // 创建圆形截面（与圆柱相同半径）
  gp_Ax2 sectionAxis(pathStart, gp_Dir(1, 0, 0));
  BRepBuilderAPI_MakeWire circleMaker;
  circleMaker.Add(
      BRepBuilderAPI_MakeEdge(gp_Circ(sectionAxis, params.thickness / 2))
          .Edge());
  TopoDS_Wire sectionWire = circleMaker.Wire();

  // 沿路径扫掠生成水平延伸
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.Add(sectionWire);
  pipeMaker.SetMode(Standard_True);
  pipeMaker.SetTransitionMode(BRepBuilderAPI_Transformed);
  pipeMaker.Build();
  if (!pipeMaker.IsDone()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }
  if (!pipeMaker.MakeSolid()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }

  return pipeMaker.Shape();
}


TopoDS_Shape create_u_shaped_ring(const u_shaped_ring_params &params,
                                  const gp_Pnt &position, const gp_Dir &normal,
                                  const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError("Normal and xDir must be perpendicular");
  }

  // 创建标准方向的U型环
  TopoDS_Shape ring = create_u_shaped_ring(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(ring, transformation);
  return transform.Shape();
}


TopoDS_Shape create_catenary(const catenary_params &params) {
  // 参数验证
  if (params.slack <= 0) {
    throw Standard_ConstructionError("Slack must be positive");
  }
  if (params.p1.Distance(params.p2) < Precision::Confusion()) {
    throw Standard_ConstructionError("Points p1 and p2 are too close");
  }

  // 获取截面形状
  TopoDS_Shape profileFace = create_shape_from_profile(params.profile, false);
  if (profileFace.IsNull()) {
    throw Standard_ConstructionError("Invalid profile for catenary");
  }
  gp_Ax3 rot = createOrientation(
      params.p1, params.p2, params.upDir ? *params.upDir : gp_Dir(0, 0, 1));
  Handle(Geom_BSplineCurve) curve =
      makeCatenaryCurve(params.p1, params.p2, rot, params.slack, params.maxSag,
                        params.tessellation);
  if (!curve) {
    throw std::runtime_error("Failed to generate catenary curves");
  }

  // 创建路径线框
  TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(curve).Edge();
  TopoDS_Wire wire = BRepBuilderAPI_MakeWire(edge).Wire();

  // 创建管道
  BRepOffsetAPI_MakePipeShell pipeMaker(wire);
  pipeMaker.Add(profileFace, false, true);

  pipeMaker.SetMode(true);

  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create catenary pipe");
  }

  if (!pipeMaker.MakeSolid()) {
    throw Standard_ConstructionError("Failed to make catenary solid");
  }

  return pipeMaker.Shape();
}


TopoDS_Wire create_catenary_centerline(const catenary_params &params) {
  // 参数验证
  if (params.slack <= 0) {
    throw Standard_ConstructionError("Slack must be positive");
  }
  if (params.p1.Distance(params.p2) < Precision::Confusion()) {
    throw Standard_ConstructionError("Points p1 and p2 are too close");
  }

  gp_Ax3 rot = createOrientation(
      params.p1, params.p2, params.upDir ? *params.upDir : gp_Dir(0, 0, 1));
  Handle(Geom_BSplineCurve) curve =
      makeCatenaryCurve(params.p1, params.p2, rot, params.slack, params.maxSag,
                        params.tessellation);
  if (!curve) {
    throw std::runtime_error("Failed to generate catenary curves");
  }

  // 创建路径线框
  TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(curve).Edge();
  TopoDS_Wire wire = BRepBuilderAPI_MakeWire(edge).Wire();

  return wire;
}


TopoDS_Shape create_catenary(const catenary_params &params,
                             const gp_Pnt &position, const gp_Dir &direction,
                             const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的悬垂线
  TopoDS_Shape catenary = create_catenary(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(catenary, transformation);
  return transform.Shape();
}

} // namespace topo
} // namespace flywave
