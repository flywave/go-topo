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
// 基础 (base) — 基本几何体 / 型钢 / 垫片 / 通用采样与剖面辅助

namespace flywave {
namespace topo {


bool IsOuterWireCCW(const TopoDS_Wire &wire) {
  // 计算线框的面积来确定方向
  GProp_GProps props;
  BRepGProp::LinearProperties(wire, props);
  return props.Mass() > 0;
}


// 判断两个方向是否平行（考虑浮点误差）
bool IsParallel(const gp_Dir &dir1, const gp_Dir &dir2) {
  return Abs(dir1.Dot(dir2)) > 1 - Precision::Angular();
}


TopoDS_Shape create_sphere(const sphere_params &params) {
  // 验证参数有效性
  if (params.radius <= 0.0) {
    throw Standard_ConstructionError("Sphere radius must be positive");
  }

  // 创建球体（默认中心在原点(0,0,0)）
  BRepPrimAPI_MakeSphere sphereMaker(params.radius);

  // 返回构建的球体形状
  return sphereMaker.Shape();
}


TopoDS_Shape create_sphere(const sphere_params &params, const gp_Pnt &center) {
  // 首先创建原点处的球体
  TopoDS_Shape sphere = create_sphere(params);

  // 将球体移动到指定位置
  gp_Trsf translation;
  translation.SetTranslation(gp_Vec(center.X(), center.Y(), center.Z()));

  BRepBuilderAPI_Transform transform(sphere, translation);
  return transform.Shape();
}


TopoDS_Shape
create_rotational_ellipsoid(const rotational_ellipsoid_params &params) {
  // 参数验证
  if (params.polarRadius <= 0.0 || params.equatorialRadius <= 0.0) {
    throw Standard_ConstructionError("Radii must be positive");
  }
  if (params.height <= 0.0 || params.height > 2 * params.polarRadius) {
    throw Standard_ConstructionError("Height must be in (0, 2*polarRadius]");
  }

  // 修正坐标系定义：
  // - 旋转轴为X轴（极半径方向）
  // - 椭圆在XY平面（Z=0）
  // - 长轴（polarRadius）沿X方向
  gp_Ax2 ellipseAxes(gp_Pnt(0, 0, 0), // 中心点
                     gp_Dir(0, 0, 1), // Z方向为法向量（定义XY平面）
                     gp_Dir(1, 0, 0)  // X方向为参考方向
  );

  // 创建椭圆（主半径X方向=polarRadius，次半径Y方向=equatorialRadius）
  gp_Elips ellipse(ellipseAxes, params.polarRadius, params.equatorialRadius);

  // 生成半椭圆边（0-PI弧度）
  TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(ellipse, 0, M_PI).Edge();
  TopoDS_Wire wire = BRepBuilderAPI_MakeWire(edge).Wire();

  // 绕X轴旋转360度生成完整椭球
  gp_Ax1 revolutionAxis(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0));
  BRepPrimAPI_MakeRevol revolMaker(BRepLib_MakeFace(wire).Face(),
                                   revolutionAxis);

  if (!revolMaker.IsDone()) {
    throw Standard_ConstructionError("Revol operation failed");
  }

  TopoDS_Shape fullEllipsoid = revolMaker.Shape();

  // 高度切割（沿X轴方向）
  if (params.height < 2 * params.polarRadius) {
    // 计算切割范围
    double startX = params.polarRadius - params.height;
    double endX = params.polarRadius;

    // 创建足够大的Box
    double boxSize = 2 * params.polarRadius; // 确保足够大
    gp_Pnt boxCorner1(startX, -boxSize, -boxSize);
    gp_Pnt boxCorner2(endX, boxSize, boxSize);

    // 创建切割Box
    TopoDS_Shape cutterBox =
        BRepPrimAPI_MakeBox(boxCorner1, boxCorner2).Shape();

    // 执行布尔运算（求交集）
    BRepAlgoAPI_Common cutOperation(fullEllipsoid, cutterBox);
    cutOperation.SetFuzzyValue(1e-5); // 设置容差
    cutOperation.Build();

    if (!cutOperation.IsDone()) {
      throw Standard_ConstructionError("Cut operation failed");
    }

    TopoDS_Shape cutResult = cutOperation.Shape();

    if (cutResult.ShapeType() == TopAbs_COMPOUND) {
      TopTools_IndexedMapOfShape shapeMap;
      TopExp::MapShapes(cutResult, TopAbs_SOLID, shapeMap);
      if (shapeMap.Extent() == 1) {
        return shapeMap(1);
      }
    }

    return cutResult;
  }
  return fullEllipsoid;
}


TopoDS_Shape
create_rotational_ellipsoid(const rotational_ellipsoid_params &params,
                            const gp_Pnt &center, const gp_Dir &xDirection) {
  // 添加正交性校验
  if (Abs(xDirection.Dot(gp::DZ())) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "X direction must be perpendicular to Z axis");
  }
  // 首先创建原点处的椭球体
  TopoDS_Shape ellipsoid = create_rotational_ellipsoid(params);

  // 创建变换：从标准方向旋转到指定方向，然后平移到指定位置
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0));
  gp_Ax3 targetAx3(center, xDirection);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(ellipsoid, transformation);
  return transform.Shape();
}


TopoDS_Shape create_cuboid(const cuboid_params &params) {
  // 参数验证
  if (params.length <= 0.0 || params.width <= 0.0 || params.height <= 0.0) {
    throw Standard_ConstructionError(
        "Length, width and height must be positive");
  }

  // 创建长方体（原点位于几何中心）
  // OCCT的MakeBox默认使用左下角为原点，所以需要偏移
  gp_Pnt origin(-params.length / 2, -params.width / 2, 0); // 底面中心在原点
  BRepPrimAPI_MakeBox boxMaker(origin, params.length, params.width,
                               params.height);

  return boxMaker.Shape();
}


TopoDS_Shape create_cuboid(const cuboid_params &params, const gp_Pnt &center,
                           const gp_Dir &xDirection, const gp_Dir &zDirection) {
  // 参数验证
  if (Abs(xDirection.Dot(zDirection)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "X and Z directions must be perpendicular");
  }
  // 首先创建原点处的长方体
  TopoDS_Shape cuboid = create_cuboid(params);

  // 创建变换：从标准方向旋转到指定方向，然后平移到指定位置
  gp_Dir yDirection = zDirection.Crossed(xDirection); // 计算Y方向
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  gp_Ax3 targetAx3(center, zDirection, xDirection);

  // 验证方向向量是否正交
  if (Abs(xDirection.Dot(zDirection)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "X and Z directions must be perpendicular");
  }

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(cuboid, transformation);
  return transform.Shape();
}


TopoDS_Shape create_diamond_frustum(const diamond_frustum &params) {
  // 增强参数验证
  const double geometricTolerance = Precision::Confusion();

  // 基础参数检查
  if (params.topDiag1 < 0 || params.topDiag2 < 0)
    throw Standard_ConstructionError("Top diagonals must be non-negative");
  if (params.bottomDiag1 <= geometricTolerance ||
      params.bottomDiag2 <= geometricTolerance)
    throw Standard_ConstructionError("Bottom diagonals must be positive");
  if (params.height <= geometricTolerance)
    throw Standard_ConstructionError("Height must be positive");

  // 相似性验证 (TL1/LL1 ≈ TL2/LL2)
  const double ratioTolerance = 0.01; // 1%公差

  bool isTopPoint1 = (params.topDiag1 <= geometricTolerance);
  bool isTopPoint2 = (params.topDiag2 <= geometricTolerance);

  double ratio1 = isTopPoint1 ? 0 : params.topDiag1 / params.bottomDiag1;
  double ratio2 = isTopPoint2 ? 0 : params.topDiag2 / params.bottomDiag2;

  // 处理特殊情况：锥体(上底面退化为点)
  if (isTopPoint1 != isTopPoint2) {
    throw Standard_ConstructionError(
        "Both top diagonals must be zero for pyramid");
  }

  // 对于截锥体检查比例一致性
  if (!isTopPoint1 && fabs(ratio1 - ratio2) > ratioTolerance) {
    throw Standard_ConstructionError(
        "Diagonals must maintain consistent scaling ratio");
  }

  // 创建下底面菱形 (技术图纸基准面)
  gp_Pnt bottomP1(params.bottomDiag1 / 2, 0, 0);  // +X
  gp_Pnt bottomP2(0, params.bottomDiag2 / 2, 0);  // +Y
  gp_Pnt bottomP3(-params.bottomDiag1 / 2, 0, 0); // -X
  gp_Pnt bottomP4(0, -params.bottomDiag2 / 2, 0); // -Y

  TopoDS_Wire bottomWire =
      BRepBuilderAPI_MakePolygon(bottomP1, bottomP2, bottomP3, bottomP4,
                                 Standard_True)
          .Wire();

  // 构建技术实体
  BRepOffsetAPI_ThruSections generator(Standard_True); // 生成实体
  generator.AddWire(bottomWire);

  // 创建上底面或顶点
  if (!isTopPoint1) {
    // 截锥体情况
    gp_Pnt topP1(params.topDiag1 / 2, 0, params.height);  // +X
    gp_Pnt topP2(0, params.topDiag2 / 2, params.height);  // +Y
    gp_Pnt topP3(-params.topDiag1 / 2, 0, params.height); // -X
    gp_Pnt topP4(0, -params.topDiag2 / 2, params.height); // -Y

    TopoDS_Wire topWire =
        BRepBuilderAPI_MakePolygon(topP1, topP2, topP3, topP4, Standard_True)
            .Wire();
    generator.AddWire(topWire);
  } else {
    // 锥体情况
    gp_Pnt apex(0, 0, params.height); // 顶点
    generator.AddVertex(BRepBuilderAPI_MakeVertex(apex).Vertex());
  }

  // 设置生成参数
  generator.SetSmoothing(Standard_True); // 启用平滑过渡
  generator.Build();

  if (!generator.IsDone()) {
    throw Standard_ConstructionError("Failed to generate technical frustum");
  }

  // 验证结果
  TopoDS_Shape result = generator.Shape();
  if (result.IsNull()) {
    throw Standard_ConstructionError("Resulting shape is null");
  }

  return result;
}


TopoDS_Shape create_diamond_frustum(const diamond_frustum &params,
                                    const gp_Pnt &position,
                                    const gp_Dir &normal, const gp_Dir &xDir) {
  // 添加正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }
  // 首先创建标准方向的棱台
  TopoDS_Shape frustum = create_diamond_frustum(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  gp_Ax3 targetAx3(position, normal, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(frustum, transformation);
  return transform.Shape();
}


TopoDS_Shape
create_offset_rectangular_table(const offset_rectangular_table_params &params) {
  // 参数验证
  if (params.topLength < 0 || params.topWidth < 0)
    throw Standard_ConstructionError("Top dimensions must be non-negative");
  if (params.bottomLength < params.topLength ||
      params.bottomWidth < params.topWidth)
    throw Standard_ConstructionError(
        "Bottom dimensions must be larger than top");
  if (params.height <= 0)
    throw Standard_ConstructionError("Height must be positive");

  // 创建底面矩形（中心在原点）
  auto pnt1 = gp_Pnt(-params.bottomLength / 2, -params.bottomWidth / 2, 0);
  auto pnt2 = gp_Pnt(-params.bottomLength / 2, params.bottomWidth / 2, 0);
  auto pnt3 = gp_Pnt(params.bottomLength / 2, params.bottomWidth / 2, 0);
  auto pnt4 = gp_Pnt(params.bottomLength / 2, -params.bottomWidth / 2, 0);

  TopoDS_Wire bottomWire =
      BRepBuilderAPI_MakePolygon(pnt1, pnt2, pnt3, pnt4, Standard_True).Wire();

  // 创建顶面矩形（带偏移量）
  pnt1 = gp_Pnt(params.xOffset - params.topLength / 2,
                params.yOffset - params.topWidth / 2, params.height);
  pnt2 = gp_Pnt(params.xOffset - params.topLength / 2,
                params.yOffset + params.topWidth / 2, params.height);
  pnt3 = gp_Pnt(params.xOffset + params.topLength / 2,
                params.yOffset + params.topWidth / 2, params.height);
  pnt4 = gp_Pnt(params.xOffset + params.topLength / 2,
                params.yOffset - params.topWidth / 2, params.height);

  // 构建技术实体
  BRepOffsetAPI_ThruSections generator(Standard_True); // 生成实体
  generator.AddWire(bottomWire);

  if (params.topLength > Precision::Confusion() &&
      params.topWidth > Precision::Confusion()) {
    TopoDS_Wire topWire =
        BRepBuilderAPI_MakePolygon(pnt1, pnt2, pnt3, pnt4, Standard_True)
            .Wire();
    generator.AddWire(topWire);
  } else {
    BRepBuilderAPI_MakeVertex mkVertex(
        gp_Pnt(params.xOffset, params.yOffset, params.height));
    generator.AddVertex(mkVertex.Vertex()); // 退化情况
  }

  generator.Build();
  if (!generator.IsDone())
    throw Standard_ConstructionError("Failed to generate offset table");

  return generator.Shape();
}


TopoDS_Shape
create_offset_rectangular_table(const offset_rectangular_table_params &params,
                                const gp_Pnt &position, const gp_Dir &normal,
                                const gp_Dir &xDir) {
  // 添加正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 首先创建标准方向的矩形台
  TopoDS_Shape table = create_offset_rectangular_table(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  gp_Ax3 targetAx3(position, normal, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(table, transformation);
  return transform.Shape();
}


TopoDS_Shape create_cylinder(const cylinder_params &params) {
  // 参数验证
  if (params.radius <= 0.0) {
    throw Standard_ConstructionError("Radius must be positive");
  }
  if (params.height <= 0.0) {
    throw Standard_ConstructionError("Height must be positive");
  }

  // 创建圆柱体（底面中心在原点，Z轴方向为高度方向）
  gp_Ax2 axis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  BRepPrimAPI_MakeCylinder cylinderMaker(axis, params.radius, params.height);

  return cylinderMaker.Shape();
}


TopoDS_Shape create_cylinder(const cylinder_params &params,
                             const gp_Pnt &baseCenter,
                             const gp_Dir &axisDirection) {
  if (Abs(axisDirection.Dot(gp::DX())) > Precision::Angular() &&
      Abs(axisDirection.Dot(gp::DY())) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Axis direction must be perpendicular to at least one base axis");
  }
  // 首先创建原点处的圆柱体
  TopoDS_Shape cylinder = create_cylinder(params);

  // 创建变换：旋转到指定方向，然后平移到指定位置
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(baseCenter, axisDirection);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(cylinder, transformation);
  return transform.Shape();
}


TopoDS_Shape
create_sharp_bent_cylinder(const sharp_bent_cylinder_params &params) {
  // 参数验证
  if (params.radius <= Precision::Confusion())
    throw Standard_ConstructionError("Radius must be positive");
  if (params.length <= Precision::Confusion())
    throw Standard_ConstructionError("Length must be positive");
  if (params.bendAngle <= Precision::Angular() || params.bendAngle >= M_PI * 2)
    throw Standard_ConstructionError("Bend angle must be in (0, 2PI)");

  const double R = params.radius;
  const double L = params.length; // 延长原始长度
  const double Rad = params.bendAngle;

  // 关键修正点：计算第二段路径的方向向量
  // 第一段路径方向：沿X轴正方向 (1,0,0)
  // 第二段路径方向：旋转 (π - bend_angle) 弧度
  const double dir_angle = M_PI - Rad;
  gp_Dir second_dir(cos(dir_angle), sin(dir_angle), 0.0);

  // 定义路径的三个关键点
  gp_Pnt startPoint(-L, 0.0, 0.0); // 起点：沿X轴负方向L
  gp_Pnt bendPoint(0.0, 0.0, 0.0); // 弯折点：原点
  gp_Pnt endPoint = bendPoint.Translated(L * second_dir);

  // 构建路径的两条线段
  BRepBuilderAPI_MakeEdge edgeMaker1(startPoint, bendPoint);
  BRepBuilderAPI_MakeEdge edgeMaker2(bendPoint, endPoint);
  TopoDS_Edge edge1 = edgeMaker1.Edge();
  TopoDS_Edge edge2 = edgeMaker2.Edge();

  // 将边组合成路径Wire
  BRepBuilderAPI_MakeWire wireMaker;
  wireMaker.Add(edge1);
  wireMaker.Add(edge2);
  TopoDS_Wire pathWire = wireMaker.Wire();

  // 在起点处创建圆形截面（YZ平面，法线沿X轴）
  gp_Ax2 circleAx(startPoint, gp_Dir(1.0, 0.0, 0.0));
  gp_Circ circle(circleAx, R);
  Handle(Geom_Circle) geomCircle = new Geom_Circle(circle);

  // 创建圆形截面的Wire并确保闭合
  BRepBuilderAPI_MakeEdge circleEdgeMaker(geomCircle);
  TopoDS_Edge circleEdge = circleEdgeMaker.Edge();
  BRepBuilderAPI_MakeWire circleWireMaker;
  circleWireMaker.Add(circleEdge);
  TopoDS_Wire circleWire = circleWireMaker.Wire();

  // 修复Wire确保闭合
  ShapeFix_Wire wireFixer;
  wireFixer.Load(circleWire);
  wireFixer.Perform();
  TopoDS_Wire closedCircleWire = wireFixer.Wire();

  // 沿路径扫掠生成弯折圆柱
  BRepOffsetAPI_MakePipeShell pipeShell(pathWire);
  pipeShell.SetMode(Standard_True); // Frenet模式，截面跟随路径旋转
  pipeShell.Add(circleWire);
  pipeShell.SetTransitionMode(BRepBuilderAPI_RightCorner);
  pipeShell.Build();

  if (!pipeShell.IsDone()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }
  if (!pipeShell.MakeSolid()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }

  return pipeShell.Shape();
}


TopoDS_Shape
create_sharp_bent_cylinder(const sharp_bent_cylinder_params &params,
                           const gp_Pnt &bendPoint, const gp_Dir &initialDir,
                           const gp_Dir &bendPlaneNormal) {
  if (Abs(initialDir.Dot(bendPlaneNormal)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Initial direction and bend plane normal must be perpendicular");
  }
  // 创建标准形状
  TopoDS_Shape cylinder = create_sharp_bent_cylinder(params);

  // 计算旋转（使X轴对齐initialDir）
  gp_Trsf rotation;
  rotation.SetRotation(
      gp_Ax1(gp::Origin(), bendPlaneNormal.Crossed(initialDir)),
      initialDir.Angle(gp::DX()));

  // 验证弯折平面法向
  gp_Dir rotatedNormal = bendPlaneNormal.Transformed(rotation);
  if (Abs(rotatedNormal.Angle(gp::DZ())) > Precision::Angular()) {
    gp_Trsf normalRot;
    normalRot.SetRotation(gp_Ax1(gp::Origin(), initialDir),
                          rotatedNormal.Angle(gp::DZ()));
    rotation = normalRot * rotation;
  }

  // 应用变换
  gp_Trsf translation;
  translation.SetTranslation(gp_Vec(bendPoint.XYZ()));

  BRepBuilderAPI_Transform transform(cylinder, translation * rotation);
  return transform.Shape();
}


TopoDS_Shape create_truncated_cone(const truncated_cone_params &params) {
  // 参数验证
  if (params.topRadius < 0.0) {
    throw Standard_ConstructionError("Top radius must be non-negative");
  }
  if (params.topRadius > 0.0 && params.topRadius < Precision::Confusion()) {
    throw Standard_ConstructionError(
        "Top radius is too small (near zero), consider using 0 for cone");
  }
  if (params.bottomRadius < params.topRadius) {
    throw Standard_ConstructionError(
        "Bottom radius must be greater than or equal to top radius");
  }
  if (params.height <= 0.0) {
    throw Standard_ConstructionError("Height must be positive");
  }

  // 创建圆台体（底面中心在原点，Z轴方向为高度方向）
  gp_Ax2 axis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));

  // OCCT的MakeCone需要半角参数，通过半径和高度计算
  double angle = atan((params.bottomRadius - params.topRadius) / params.height);
  BRepPrimAPI_MakeCone coneMaker(axis, params.bottomRadius, params.topRadius,
                                 params.height);

  return coneMaker.Shape();
}


TopoDS_Shape create_truncated_cone(const truncated_cone_params &params,
                                   const gp_Pnt &baseCenter,
                                   const gp_Dir &axisDirection) {
  // 添加正交性校验
  if (Abs(axisDirection.Dot(gp::DX())) > Precision::Angular() &&
      Abs(axisDirection.Dot(gp::DY())) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Axis direction must be perpendicular to at least one base axis");
  }

  // 首先创建原点处的圆台体
  TopoDS_Shape cone = create_truncated_cone(params);

  // 创建变换：从标准方向旋转到指定方向，然后平移到指定位置
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(baseCenter, axisDirection);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(cone, transformation);
  return transform.Shape();
}


TopoDS_Shape
create_eccentric_truncated_cone(const eccentric_truncated_cone_params &params) {
  // 参数验证
  if (params.topRadius < 0.0)
    throw Standard_ConstructionError("Top radius must be non-negative");
  if (params.bottomRadius < params.topRadius)
    throw Standard_ConstructionError(
        "Bottom radius must be greater than or equal to top radius");
  if (params.height <= 0.0)
    throw Standard_ConstructionError("Height must be positive");
  if (params.topXOffset < 0.0 || params.topYOffset < 0.0)
    throw Standard_ConstructionError("Offset values must be non-negative");

  // 创建底面圆（中心在原点）
  gp_Circ bottomCircle(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)),
                       params.bottomRadius);
  TopoDS_Edge bottomEdge = BRepBuilderAPI_MakeEdge(bottomCircle).Edge();
  TopoDS_Wire bottomWire = BRepBuilderAPI_MakeWire(bottomEdge).Wire();

  // 创建顶面圆（带偏移量）
  gp_Circ topCircle(
      gp_Ax2(gp_Pnt(params.topXOffset, params.topYOffset, params.height),
             gp_Dir(0, 0, 1)),
      params.topRadius);
  TopoDS_Edge topEdge = BRepBuilderAPI_MakeEdge(topCircle).Edge();
  TopoDS_Wire topWire = BRepBuilderAPI_MakeWire(topEdge).Wire();

  // 使用放样操作创建偏心圆台体
  BRepOffsetAPI_ThruSections generator(Standard_True); // 生成实体
  generator.AddWire(bottomWire);

  if (params.topRadius > Precision::Confusion()) {
    generator.AddWire(topWire);
  } else {
    BRepBuilderAPI_MakeVertex mkVertex(
        gp_Pnt(params.topXOffset, params.topYOffset, params.height));
    generator.AddVertex(mkVertex.Vertex()); //  圆锥情况
  }

  generator.Build();
  if (!generator.IsDone())
    throw Standard_ConstructionError("Failed to generate eccentric cone");

  return generator.Shape();
}


TopoDS_Shape
create_eccentric_truncated_cone(const eccentric_truncated_cone_params &params,
                                const gp_Pnt &baseCenter,
                                const gp_Dir &axisDirection) {
  // 添加正交性校验
  if (Abs(axisDirection.Dot(gp::DX())) > Precision::Angular() &&
      Abs(axisDirection.Dot(gp::DY())) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Axis direction must be perpendicular to at least one base axis");
  }
  // 首先创建原点处的偏心圆台体
  TopoDS_Shape cone = create_eccentric_truncated_cone(params);

  // 创建变换：旋转到指定方向，然后平移到指定位置
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(baseCenter, axisDirection);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(cone, transformation);
  return transform.Shape();
}


/**
 * @brief 创建圆环/弯管图元
 *
 * @param ringRadius 圆环半径 (R > 0)
 * @param tubeRadius 管半径 (0 < DR < R)
 * @param angle 弧度 (0 < Rad ≤ 2PI)
 * @return TopoDS_Shape 生成的圆环/弯管形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_ring(const ring_params &params) {
  // 参数验证
  if (params.ringRadius <= 0.0)
    throw Standard_ConstructionError("Ring radius must be positive");
  if (params.tubeRadius <= 0.0 || params.tubeRadius >= params.ringRadius)
    throw Standard_ConstructionError("Tube radius must be in (0, R)");
  if (params.angle <= 0.0 || params.angle > 2 * M_PI + 1e-6)
    throw Standard_ConstructionError("Angle must be in (0, 2PI]");

  // 完整圆环情况
  if (std::fabs(params.angle - 2 * M_PI) < 1e-6) { // float32 的 2π 与 double 2π 差 ~1.7e-7
    gp_Ax2 axis(gp::Origin(), gp::DZ(), gp::DX());
    return BRepPrimAPI_MakeTorus(axis, params.ringRadius, params.tubeRadius)
        .Shape();
  } else { // 部分圆环（弯管）情况
    // 1. 创建路径圆弧（XY平面）
    gp_Circ pathCircle(gp_Ax2(gp::Origin(), gp::DZ()), params.ringRadius);
    GC_MakeArcOfCircle maker(pathCircle, 0.0, params.angle, true);
    if (!maker.IsDone())
      throw Standard_ConstructionError("Failed to create arc");
    Handle(Geom_TrimmedCurve) arc = maker.Value();

    // 2. 将路径曲线转为Wire
    TopoDS_Edge pathEdge = BRepBuilderAPI_MakeEdge(arc).Edge();
    TopoDS_Wire pathWire = BRepBuilderAPI_MakeWire(pathEdge).Wire();

    // 3. 创建截面圆（关键修正：初始朝向应为路径起点的切线方向）
    gp_Pnt startPoint = arc->Value(arc->FirstParameter());
    gp_Vec startTangent;
    arc->D1(arc->FirstParameter(), startPoint, startTangent); // 获取起点切线

    gp_Ax2 sectionAxes(startPoint,           // 截面中心位于路径起点
                       gp_Dir(startTangent), // Z轴沿路径切线（法线方向）
                       gp_Dir(0, 0, 1) // X轴保持全局Z方向（可根据需要调整）
    );
    gp_Circ sectionCircle(sectionAxes, params.tubeRadius);
    TopoDS_Edge sectionEdge = BRepBuilderAPI_MakeEdge(sectionCircle).Edge();
    TopoDS_Wire sectionWire = BRepBuilderAPI_MakeWire(sectionEdge).Wire();

    // 4. 扫掠生成管状几何
    BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
    pipeMaker.Add(sectionWire);
    pipeMaker.SetMode(Standard_True); // Frenet模式确保截面跟随路径旋转
    pipeMaker.Build();

    if (!pipeMaker.IsDone())
      throw Standard_ConstructionError("Pipe generation failed");
    if (!pipeMaker.MakeSolid()) {
      throw std::runtime_error("Failed to create a solid object from sweep");
    }

    return pipeMaker.Shape();
  }
}


TopoDS_Shape create_ring(const ring_params &params, const gp_Pnt &center,
                         const gp_Dir &normal, const gp_Dir &xDir) {
  // 添加正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 首先创建标准方向的圆环
  TopoDS_Shape ring = create_ring(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(center, normal, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(ring, transformation);
  return transform.Shape();
}


static bool areColinear(const gp_Pnt &p1, const gp_Pnt &p2, const gp_Pnt &p3) {
  gp_Vec v1(p1, p2);
  gp_Vec v2(p1, p3);
  return v1.CrossMagnitude(v2) < Precision::Confusion();
}

/**
 * @brief 创建矩形环图元
 *
 * @param tubeRadius 管半径 (0 < DR < W)
 * @param filletRadius 倒角半径 (R < W/2)
 * @param length 环长度 (L > W)
 * @param width 环宽度 (W > 0)
 * @return TopoDS_Shape 生成的矩形环形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_rectangular_ring(const rectangular_ring_params &params) {
  // 参数验证
  if (params.tubeRadius <= Precision::Confusion() ||
      params.tubeRadius >= (params.width / 2 - Precision::Confusion()))
    throw Standard_ConstructionError("Tube radius must be in (0, width/2)");
  if (params.filletRadius < 0 ||
      params.filletRadius > (params.width / 2 - Precision::Confusion()))
    throw Standard_ConstructionError("Fillet radius must be in [0, width/2)");
  if (params.length <= params.width + 2 * Precision::Confusion())
    throw Standard_ConstructionError("Length must be greater than width");
  if (params.width <= Precision::Confusion())
    throw Standard_ConstructionError("Width must be positive");

  const double L = params.length;
  const double W = params.width;
  const double R = params.filletRadius;
  const double DR = params.tubeRadius;

  // 计算有效几何尺寸（精确计算）
  const double straight_length = L - 2 * R;
  const double straight_width = W - 2 * R;

  // 验证有效尺寸
  if (straight_length < Precision::Confusion() ||
      straight_width < Precision::Confusion())
    throw Standard_ConstructionError(
        "Fillet radius too large for given dimensions");

  // 新增检查：有效边长是否足够容纳倒角半径
  if (R > Precision::Confusion()) {
    if (straight_length < R - Precision::Confusion() ||
        straight_width < R - Precision::Confusion()) {
      throw Standard_ConstructionError(
          "Fillet radius is too large for the available edge lengths");
    }
  }
  // 创建带精确圆角的矩形路径
  BRepBuilderAPI_MakeWire pathWire;
  BRepBuilderAPI_TransitionMode mode = BRepBuilderAPI_Transformed;

  // 创建圆形截面（修正截面方向）
  gp_Pnt sectionStart;
  gp_Vec sectionDir;

  // 添加倒角圆弧（如果半径大于0）
  if (R > Precision::Confusion()) {
    // 定义四个角点参数
    struct CornerInfo {
      gp_Pnt center;
      gp_Pnt start;
      gp_Pnt end;
    } corners[4];

    // 右下角 (i=0)
    corners[0].center = gp_Pnt(L / 2 - R, -W / 2 + R, 0);
    corners[0].start = gp_Pnt(L / 2 - R, -W / 2, 0); // 东向直边终点
    corners[0].end = gp_Pnt(L / 2, -W / 2 + R, 0);   // 南向直边起点

    // 右上角 (i=1)
    corners[1].center = gp_Pnt(L / 2 - R, W / 2 - R, 0);
    corners[1].start = gp_Pnt(L / 2, W / 2 - R, 0); // 东向直边终点
    corners[1].end = gp_Pnt(L / 2 - R, W / 2, 0);   // 北向直边起点

    // 左上角 (i=2)
    corners[2].center = gp_Pnt(-L / 2 + R, W / 2 - R, 0);
    corners[2].start = gp_Pnt(-L / 2 + R, W / 2, 0); // 北向直边终点
    corners[2].end = gp_Pnt(-L / 2, W / 2 - R, 0);   // 西向直边起点

    // 左下角 (i=3)
    corners[3].center = gp_Pnt(-L / 2 + R, -W / 2 + R, 0);
    corners[3].start = gp_Pnt(-L / 2, -W / 2 + R, 0); // 西向直边终点
    corners[3].end = gp_Pnt(-L / 2 + R, -W / 2, 0);   // 南向直边起点

    // 圆角模式下使用第一个圆角的起点和方向
    sectionStart = corners[0].start;
    sectionDir = gp_Vec(corners[0].end.XYZ() - corners[0].start.XYZ());

    // 构建路径：直边段 -> 圆角
    for (int i = 0; i < 4; ++i) {
      // 添加直线段（连接上一个圆角终点到当前圆角起点）
      if (i == 0) {
        // 从最后一个圆角终点连接到第一个圆角起点
        pathWire.Add(
            BRepBuilderAPI_MakeEdge(corners[3].end, corners[0].start).Edge());
      } else {
        // 连接前一个圆角终点到当前圆角起点
        pathWire.Add(
            BRepBuilderAPI_MakeEdge(corners[i - 1].end, corners[i].start)
                .Edge());
      }

      gp_Circ arc(gp_Ax2(corners[i].center, gp_Dir(0, 0, 1)), R);
      Handle(Geom_TrimmedCurve) arcCurve =
          GC_MakeArcOfCircle(arc, corners[i].start, corners[i].end,
                             true // 确保顺时针方向
          );
      pathWire.Add(BRepBuilderAPI_MakeEdge(arcCurve).Edge());
    }

    mode = BRepBuilderAPI_RoundCorner;
  } else {
    // 定义基准角点（修正坐标系）
    const gp_Pnt base_points[4] = {
        gp_Pnt(straight_length / 2, -straight_width / 2, 0), // 右下基准点
        gp_Pnt(straight_length / 2, straight_width / 2, 0),  // 右上基准点
        gp_Pnt(-straight_length / 2, straight_width / 2, 0), // 左上基准点
        gp_Pnt(-straight_length / 2, -straight_width / 2, 0) // 左下基准点
    };
    // 直角处理
    for (int i = 0; i < 4; i++) {
      int next_i = (i + 1) % 4;
      pathWire.Add(
          BRepBuilderAPI_MakeEdge(base_points[i], base_points[next_i]).Edge());
    }
    sectionStart = base_points[0];
    sectionDir = gp_Vec(base_points[1].XYZ() - base_points[0].XYZ());

    mode = BRepBuilderAPI_RightCorner;
  }

  // 创建圆形截面（修正截面方向）
  const gp_Ax2 section_axis(sectionStart, // 截面起点
                            sectionDir,   // 法线方向沿路径切线
                            gp::DZ()      // 垂直方向
  );
  gp_Circ sectionCircle(section_axis, DR);
  TopoDS_Wire sectionWire =
      BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(sectionCircle).Edge())
          .Wire();

  // 执行扫掠（增强容错处理）
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire.Wire());
  pipeMaker.Add(sectionWire);
  pipeMaker.SetMode(Standard_True);  // Frenet框架
  pipeMaker.SetTransitionMode(mode); // 设置圆角过渡模式
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Pipe generation failed. Error code");
  }
  if (!pipeMaker.MakeSolid()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }

  return pipeMaker.Shape();
}


TopoDS_Shape create_rectangular_ring(const rectangular_ring_params &params,
                                     const gp_Pnt &center, const gp_Dir &normal,
                                     const gp_Dir &xDir) {
  // 添加正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }
  // 首先创建标准方向的矩形环
  TopoDS_Shape ring = create_rectangular_ring(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(center, normal, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(ring, transformation);
  return transform.Shape();
}


TopoDS_Shape create_elliptic_ring(const elliptic_ring_params &params) {
  // 参数验证
  if (params.tubeRadius <= 0.0 || params.tubeRadius >= params.minorRadius) {
    throw Standard_ConstructionError("Tube radius must be in (0, W)");
  }
  if (params.majorRadius <= params.minorRadius) {
    throw Standard_ConstructionError(
        "Major radius must be greater than minor radius");
  }
  if (params.minorRadius <= 0.0) {
    throw Standard_ConstructionError("Minor radius must be positive");
  }

  // 创建椭圆路径（XY平面）
  gp_Elips ellipse(gp_Ax2(gp::Origin(), gp::DZ()), params.majorRadius,
                   params.minorRadius);
  TopoDS_Edge pathEdge = BRepBuilderAPI_MakeEdge(ellipse).Edge();
  TopoDS_Wire pathWire = BRepBuilderAPI_MakeWire(pathEdge).Wire();

  // 创建截面圆（YZ平面）
  gp_Circ sectionCircle(gp_Ax2(gp_Pnt(params.majorRadius, 0, 0), gp::DY()),
                        params.tubeRadius);
  TopoDS_Edge sectionEdge = BRepBuilderAPI_MakeEdge(sectionCircle).Edge();
  TopoDS_Wire sectionWire = BRepBuilderAPI_MakeWire(sectionEdge).Wire();

  // 沿椭圆路径扫掠
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.Add(sectionWire);
  pipeMaker.SetMode(Standard_True); // Frenet框架
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to generate elliptic ring");
  }
  if (!pipeMaker.MakeSolid()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }

  return pipeMaker.Shape();
}


TopoDS_Shape create_elliptic_ring(const elliptic_ring_params &params,
                                  const gp_Pnt &center, const gp_Dir &normal,
                                  const gp_Dir &xDir) {
  // 添加正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }
  // 首先创建标准方向的椭圆环
  TopoDS_Shape ring = create_elliptic_ring(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(center, normal, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(ring, transformation);
  return transform.Shape();
}


// 创建带孔的环形截面
TopoDS_Face create_annular_face(double OR, double IR, double angle) {
  const gp_Ax2 system(gp::Origin(), gp::DZ());

  // 创建完整外轮廓线框
  TopoDS_Wire outerWire = create_oriented_wire(system, OR, angle, false);

  // 创建内孔线框（注意方向反转）
  TopoDS_Wire innerWire = create_oriented_wire(system, IR, angle, true);

  // 构造带孔平面
  BRepBuilderAPI_MakeFace faceMaker(outerWire);
  faceMaker.Add(innerWire);

  if (!faceMaker.IsDone()) {
    throw Standard_ConstructionError("Face creation failed");
  }

  return faceMaker.Face();
}


TopoDS_Shape create_circular_gasket(const circular_gasket_params &params) {
  // 参数验证保持不变
  if (params.outerRadius <= params.innerRadius) {
    throw Standard_ConstructionError(
        "Outer radius must be greater than inner radius");
  }
  if (params.innerRadius <= 0.0) {
    throw Standard_ConstructionError("Inner radius must be positive");
  }
  if (params.height <= 0.0) {
    throw Standard_ConstructionError("Height must be positive");
  }
  if (params.angle <= 0.0 || params.angle > 2 * M_PI + 1e-6) {
    throw Standard_ConstructionError("Angle must be in (0, 2PI]");
  }

  // 完整圆环情况保持原逻辑
  if (std::fabs(params.angle - 2 * M_PI) < 1e-6) { // float32 的 2π 与 double 2π 差 ~1.7e-7
    TopoDS_Face baseFace = create_annular_face(
        params.outerRadius, params.innerRadius, params.angle);
    gp_Vec extrusionVec(0, 0, params.height);
    return BRepPrimAPI_MakePrism(baseFace, extrusionVec).Shape();
  }

  // 扇形情况使用扫掠方式
  // 创建截面轮廓 - 矩形条带 (位于XY平面)
  double thickness = params.outerRadius - params.innerRadius;
  gp_Pnt p1(0, params.innerRadius, 0);             // 起始点在内径位置
  gp_Pnt p2(0, params.innerRadius + thickness, 0); // Y方向延伸厚度
  gp_Pnt p3(0, params.innerRadius + thickness, params.height);
  gp_Pnt p4(0, params.innerRadius, params.height);

  // 在XY平面构建截面（Y方向为径向，Z方向为高度）
  TopoDS_Wire profileWire =
      BRepBuilderAPI_MakePolygon(p1, p2, p3, p4, Standard_True).Wire();

  // 创建扫掠路径 - 以平均半径为路径的圆弧
  double pathRadius = (params.innerRadius + params.outerRadius) / 2.0;
  gp_Circ pathCircle(gp_Ax2(gp::Origin(), gp::DZ()), pathRadius);
  Handle(Geom_TrimmedCurve) pathArc =
      GC_MakeArcOfCircle(pathCircle, 0, params.angle, false).Value();

  TopoDS_Wire pathWire =
      BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(pathArc).Edge()).Wire();

  // 执行扫掠（修正框架模式）
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.Add(profileWire);
  pipeMaker.SetMode(Standard_False); // 固定截面方向（避免Frenet旋转）
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Sweep operation failed");
  }
  if (!pipeMaker.MakeSolid()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }

  return pipeMaker.Shape();
}


TopoDS_Shape create_circular_gasket(const circular_gasket_params &params,
                                    const gp_Pnt &center, const gp_Dir &normal,
                                    const gp_Dir &xDir) {
  // 添加正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }
  // 首先创建标准方向的圆形垫片
  TopoDS_Shape gasket = create_circular_gasket(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(center, normal, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(gasket, transformation);
  return transform.Shape();
}


TopoDS_Shape create_table_gasket(const table_gasket_params &params) {
  // 参数验证
  if (params.innerRadius <= 0 || params.topRadius <= params.innerRadius ||
      params.outerRadius <= params.topRadius || params.height <= 0) {
    throw Standard_ConstructionError("Invalid parameters");
  }
  if (params.angle <= 0 || params.angle > 2 * M_PI + 1e-6) {
    throw Standard_ConstructionError("Angle must be in (0, 2PI]");
  }
  gp_Ax2 axis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));

  // 完整圆形情况
  if (std::abs(params.angle - 2 * M_PI) < 1e-6) {
    // 创建底部大圆台（IR到OR）
    BRepPrimAPI_MakeCone bottomCone(axis, params.outerRadius, params.topRadius,
                                    params.height);

    // 创建顶部小圆柱（IR到TR）
    BRepPrimAPI_MakeCylinder topCylinder(axis, params.innerRadius,
                                         params.height);

    // 执行布尔切操作 (显式 Build + Shape, 隐式转换可能返回未完成结果)
    BRepAlgoAPI_Cut cutOp(bottomCone.Shape(), topCylinder.Shape());
    cutOp.Build();
    if (!cutOp.IsDone()) {
      throw Standard_ConstructionError("Failed to cut circular gasket");
    }
    return cutOp.Shape();
  }
  // 扇形情况
  else {
    // 1. 创建截面线（从内到外：内径→平台→斜坡顶点）
    BRepBuilderAPI_MakeWire wireBuilder;

    // 截面点定义（XZ平面）
    gp_Pnt innerBottom(params.innerRadius, 0, 0);          // 内径底部
    gp_Pnt platformEdge(params.outerRadius, 0, 0);         // 平台边缘
    gp_Pnt slopeTop(params.topRadius, 0, params.height);   // 斜坡顶部
    gp_Pnt innerTop(params.innerRadius, 0, params.height); // 内径顶部

    // 按梯形顺序添加边
    wireBuilder.Add(BRepBuilderAPI_MakeEdge(innerBottom, platformEdge));
    wireBuilder.Add(BRepBuilderAPI_MakeEdge(platformEdge, slopeTop));
    wireBuilder.Add(BRepBuilderAPI_MakeEdge(slopeTop, innerTop));
    wireBuilder.Add(BRepBuilderAPI_MakeEdge(innerTop, innerBottom));

    TopoDS_Wire profileWire = wireBuilder.Wire();

    // 2. 创建扫掠路径（绕Z轴的圆弧）
    gp_Circ pathCircle(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 1.0);
    Handle(Geom_Curve) pathCurve = new Geom_Circle(pathCircle);
    TopoDS_Edge pathEdge = BRepBuilderAPI_MakeEdge(pathCurve, 0, params.angle);
    TopoDS_Wire pathWire = BRepBuilderAPI_MakeWire(pathEdge).Wire();

    // 3. 扫掠生成扇形
    BRepOffsetAPI_MakePipeShell pipeShell(pathWire);
    pipeShell.SetMode(Standard_True); // 使用Frenet框架保证正确朝向
    pipeShell.Add(profileWire);

    if (!pipeShell.IsReady()) {
      throw std::runtime_error("Pipe shell preparation failed");
    }

    pipeShell.Build();

    if (pipeShell.Shape().IsNull()) {
      throw std::runtime_error("Pipe shell generation failed");
    }
    if (!pipeShell.MakeSolid()) {
      throw std::runtime_error("Failed to create a solid object from sweep");
    }

    return pipeShell.Shape();
  }
}


TopoDS_Shape create_table_gasket(const table_gasket_params &params,
                                 const gp_Pnt &center, const gp_Dir &normal,
                                 const gp_Dir &xDir) {
  // 首先创建标准方向的台型垫片
  TopoDS_Shape gasket = create_table_gasket(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(center, normal, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(gasket, transformation);
  return transform.Shape();
}


TopoDS_Shape create_square_gasket(const square_gasket_params &params) {
  // 参数验证
  if (params.outerLength <= params.innerLength) {
    throw Standard_ConstructionError("外框长度必须大于内框长度");
  }
  if (params.outerWidth <= params.innerWidth) {
    throw Standard_ConstructionError("外框宽度必须大于内框宽度");
  }
  if (params.innerLength <= 0.0 || params.innerWidth <= 0.0) {
    throw Standard_ConstructionError("内框尺寸必须为正数");
  }
  if (params.height <= 0.0) {
    throw Standard_ConstructionError("高度必须为正数");
  }
  if (params.cornerType < 1 || params.cornerType > 3) {
    throw Standard_ConstructionError("拐角类型必须是1、2或3");
  }

  // 计算半长半宽
  double outerHalfLength = params.outerLength / 2.0;
  double outerHalfWidth = params.outerWidth / 2.0;
  double innerHalfLength = params.innerLength / 2.0;
  double innerHalfWidth = params.innerWidth / 2.0;
  // 创建坐标系，原点位于底部中心
  gp_Ax2 coordSystem1(gp_Pnt(-outerHalfLength, -outerHalfWidth, 0),
                      gp_Dir(0, 0, 1));
  gp_Ax2 coordSystem2(gp_Pnt(-innerHalfLength, -innerHalfWidth, 0),
                      gp_Dir(0, 0, 1));

  // 创建外框实体
  TopoDS_Shape outerSolid =
      BRepPrimAPI_MakeBox(coordSystem1, params.outerLength, params.outerWidth,
                          params.height)
          .Shape();

  // 创建内框实体（将被减去）
  TopoDS_Shape innerSolid =
      BRepPrimAPI_MakeBox(coordSystem2, params.innerLength, params.innerWidth,
                          params.height)
          .Shape();

  // 执行布尔切割操作创建基本垫圈
  BRepAlgoAPI_Cut cutter(outerSolid, innerSolid);
  TopoDS_Shape gasket = cutter.Shape();

  // 处理拐角类型
  switch (params.cornerType) {
  case 1: // 直角（无需额外处理）
    break;

  case 2: // 圆角
    if (params.cornerParam > 0 &&
        params.cornerParam <=
            std::min(params.outerWidth, params.outerLength) / 2.0) {
      BRepFilletAPI_MakeFillet fillet(gasket);

      // 获取所有边
      TopExp_Explorer edgeExplorer(gasket, TopAbs_EDGE);

      // 用于存储需要添加圆角的边
      TopTools_IndexedMapOfShape edgesToFillet;

      for (; edgeExplorer.More(); edgeExplorer.Next()) {
        TopoDS_Edge edge = TopoDS::Edge(edgeExplorer.Current());

        // 获取边的两个顶点
        TopExp_Explorer vertexExplorer(edge, TopAbs_VERTEX);
        gp_Pnt p1 = BRep_Tool::Pnt(TopoDS::Vertex(vertexExplorer.Current()));
        vertexExplorer.Next();
        gp_Pnt p2 = BRep_Tool::Pnt(TopoDS::Vertex(vertexExplorer.Current()));

        // 计算边的方向向量
        gp_Vec edgeDir(p1, p2);

        // 只选择垂直边（Z方向）或水平边（X/Y方向）
        // 这里我们选择所有外边缘（包括垂直和水平边）
        // 或者可以根据需要只选择垂直边：
        if (edgeDir.Z() != 0) { // 只选择垂直边
          edgesToFillet.Add(edge);
        }
      }

      // 为选中的边添加圆角
      for (int i = 1; i <= edgesToFillet.Extent(); i++) {
        fillet.Add(params.cornerParam, TopoDS::Edge(edgesToFillet.FindKey(i)));
      }

      fillet.Build();

      if (fillet.IsDone()) {
        gasket = fillet.Shape();
      } else {
        // 圆角操作失败，返回原始形状
        std::cerr << "警告：圆角操作失败，返回直角形状" << std::endl;
      }
    }
    break;

  case 3: // 倒角
    if (params.cornerParam > 0) {
      // 创建倒角工具 - 一个足够大的立方体
      double chamferSize = params.cornerParam * 2.0;
      TopoDS_Shape chamferTool =
          BRepPrimAPI_MakeBox(
              gp_Ax2(gp_Pnt(-params.cornerParam, -params.cornerParam, 0),
                     gp_Dir(0, 0, 1)),
              chamferSize, chamferSize, params.height)
              .Shape();

      // 在每个角落放置倒角工具并执行切割
      for (int i = 0; i < 4; i++) {
        // 确定角落位置和旋转角度
        double xSign = (i % 2) ? -1.0 : 1.0;
        double ySign = (i / 2) ? -1.0 : 1.0;
        double angle = (i % 2) == (i / 2) ? M_PI / 4 : -M_PI / 4;

        double xPos = xSign * (outerHalfLength);
        double yPos = ySign * (outerHalfWidth);

        // 创建变换：先旋转45度再平移到角落
        gp_Trsf cornerTransform;
        cornerTransform.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)),
                                    angle);
        cornerTransform.SetTranslationPart(gp_Vec(xPos, yPos, 0));

        // 应用变换
        BRepBuilderAPI_Transform chamferTransform(chamferTool, cornerTransform);
        TopoDS_Shape positionedChamfer = chamferTransform.Shape();

        // 执行切割操作
        BRepAlgoAPI_Cut cornerCutter(gasket, positionedChamfer);
        if (cornerCutter.IsDone()) {
          gasket = cornerCutter.Shape();
        }
      }
    }
    break;
  }

  return gasket;
}


TopoDS_Shape create_square_gasket(const square_gasket_params &params,
                                  const gp_Pnt &center, const gp_Dir &normal,
                                  const gp_Dir &xDir) {
  // 添加正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }
  // 首先创建标准方向的方形垫片
  TopoDS_Shape gasket = create_square_gasket(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(center, normal, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(gasket, transformation);
  return transform.Shape();
}


/**
 * @brief 创建拉伸体图元
 *
 * @param points 底面顶点坐标数组
 * @param normal 拉伸方向向量
 * @param length 拉伸长度 (L > 0)
 * @return TopoDS_Shape 生成的拉伸体形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_stretched_body(const stretched_body_params &params) {
  // 参数验证
  if (params.length <= 0.0) {
    throw Standard_ConstructionError("Length must be positive");
  }
  if (params.points.size() < 3) {
    throw Standard_ConstructionError("At least 3 points are required");
  }
  if (gp_Vec(params.normal).Magnitude() < Precision::Confusion()) {
    throw Standard_ConstructionError("Normal vector must not be zero");
  }

  // 创建底面多边形
  BRepBuilderAPI_MakePolygon polygonMaker;
  for (const auto &point : params.points) {
    polygonMaker.Add(point);
  }
  polygonMaker.Close();

  if (!polygonMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create base polygon");
  }
  TopoDS_Wire baseWire = polygonMaker.Wire();

  // 创建底面面
  BRepBuilderAPI_MakeFace faceMaker(baseWire);
  if (!faceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create base face");
  }
  TopoDS_Face baseFace = faceMaker.Face();

  // 执行拉伸操作
  gp_Vec direction(params.normal);
  direction.Scale(params.length);
  BRepPrimAPI_MakePrism prismMaker(baseFace, direction);

  if (!prismMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to perform extrusion");
  }

  return prismMaker.Shape();
}


TopoDS_Shape create_stretched_body(const stretched_body_params &params,
                                   const gp_Pnt &basePoint,
                                   const gp_Dir &xDir) {
  // xDir 与 normal 共线时 (调用方常把拉伸轴当 xDir 传入) 自动派生正交 xDir,
  // 而不是直接抛错 —— 旧实现此处必然抛错, 且被 is_null 缺陷掩盖成"成功"
  gp_Dir effXDir(xDir);
  if (Abs(params.normal.Dot(effXDir)) > 1.0 - Precision::Angular()) {
    effXDir = Abs(gp_Vec(params.normal).Dot(gp_Vec(gp_Dir(1, 0, 0)))) > 0.9
                  ? gp_Dir(0, 1, 0)
                  : gp_Dir(1, 0, 0);
  } else if (Abs(gp_Vec(params.normal).Dot(gp_Vec(effXDir))) >
             Precision::Angular()) {
    // 非严格正交: 投影到正交平面并归一化
    gp_Vec proj = gp_Vec(effXDir) -
                  gp_Vec(params.normal) * gp_Vec(params.normal).Dot(gp_Vec(effXDir));
    effXDir = gp_Dir(proj);
  }
  // 首先创建标准方向的拉伸体
  TopoDS_Shape body = create_stretched_body(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), params.normal, effXDir);
  gp_Ax3 targetAx3(basePoint, params.normal, effXDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(body, transformation);
  return transform.Shape();
}


// 辅助函数：检测是否孔洞边缘
bool IsHoleEdge(const TopoDS_Edge &edge, const TopoDS_Compound &holes) {
  TopExp_Explorer holeExplorer(holes, TopAbs_EDGE);
  for (; holeExplorer.More(); holeExplorer.Next()) {
    if (edge.IsSame(holeExplorer.Current())) {
      return true;
    }
  }
  return false;
}


std::vector<gp_Pnt> sample_wire(const wire_params &params,
                                double tessellation) {
  // 参数验证
  if (params.diameter <= 0) {
    throw Standard_ConstructionError("导线直径必须为正数");
  }
  if (params.sag <= 0) {
    throw Standard_ConstructionError("导线弧垂必须为正数");
  }

  std::vector<gp_Pnt> samples;
  Handle(Geom_BSplineCurve) curve;

  if (!params.fitPoints.empty()) {
    // 使用拟合点集创建样条曲线
    Handle(TColgp_HArray1OfPnt) points =
        new TColgp_HArray1OfPnt(1, params.fitPoints.size());
    for (int i = 0; i < params.fitPoints.size(); ++i) {
      points->SetValue(i + 1, params.fitPoints[i]);
    }

    GeomAPI_Interpolate interpolate(points, false, Precision::Confusion());
    interpolate.Load(gp_Vec(0, 0, 1), gp_Vec(0, 0, 1), true);
    interpolate.Perform();

    if (!interpolate.IsDone()) {
      throw Standard_ConstructionError("Failed to create interpolated curve");
    }

    curve = interpolate.Curve();
    if (curve.IsNull()) {
      throw Standard_ConstructionError("Failed to create curve");
    }

    // 计算采样点数量
    double length = 0.0;
    for (size_t i = 1; i < params.fitPoints.size(); ++i) {
      length += params.fitPoints[i - 1].Distance(params.fitPoints[i]);
    }

    int sampleCount =
        tessellation > 0 ? static_cast<int>(length / tessellation) : 20;
    sampleCount = std::max(sampleCount, 2); // 至少2个点

    samples.reserve(sampleCount);

    // 曲线参数化采样
    for (int i = 0; i < sampleCount; ++i) {
      double t = static_cast<double>(i) / (sampleCount - 1);
      gp_Pnt point;
      curve->D0(t * curve->LastParameter(), point);
      samples.push_back(point);
    }
  } else {
    // 直线采样
    samples.push_back(params.startPoint);
    samples.push_back(params.endPoint);
  }

  return samples;
}


std::vector<gp_Pnt>
sample_curve_points(const std::vector<std::vector<gp_Pnt>> &controlPoints,
                    std::vector<curve_type> segments, double tessellation) {
  // 参数验证
  if (controlPoints.size() != segments.size()) {
    throw Standard_ConstructionError(
        "Control points and segments count mismatch");
  }

  std::vector<gp_Pnt> points;

  // 处理每条曲线段
  for (size_t i = 0; i < controlPoints.size(); ++i) {
    const auto &pointsGroup = controlPoints[i];
    curve_type type = segments[i];

    switch (type) {
    case curve_type::LINE: {
      // 直线直接采样起点和终点
      if (pointsGroup.size() != 2) {
        throw Standard_ConstructionError(
            "Line segment requires exactly 2 points");
      }
      points.push_back(pointsGroup[0]);
      points.push_back(pointsGroup[1]);
      break;
    }
    case curve_type::ARC: {
      // 圆弧采样
      if (pointsGroup.size() != 3) {
        throw Standard_ConstructionError(
            "Arc segment requires exactly 3 points");
      }

      // 创建圆弧
      GC_MakeArcOfCircle arcMaker(pointsGroup[0], pointsGroup[1],
                                  pointsGroup[2]);
      if (!arcMaker.IsDone()) {
        throw Standard_ConstructionError("Failed to create arc segment");
      }

      // 计算默认采样数
      Handle(Geom_TrimmedCurve) arc = arcMaker.Value();
      GeomAdaptor_Curve curveAdaptor(arc);
      double arcLength = GCPnts_AbscissaPoint::Length(curveAdaptor);
      int sampleCount = tessellation > 0
                            ? tessellation
                            : std::max(8, static_cast<int>(arcLength * 10));

      // 均匀采样圆弧
      double first = arcMaker.Value()->FirstParameter();
      double last = arcMaker.Value()->LastParameter();
      double step = (last - first) / sampleCount;

      for (int j = 0; j <= sampleCount; ++j) {
        double param = first + j * step;
        points.push_back(arcMaker.Value()->Value(param));
      }
      break;
    }
    case curve_type::BEZIER: {
      // 贝塞尔曲线采样
      if (pointsGroup.size() < 3) {
        throw Standard_ConstructionError(
            "Bezier segment requires at least 3 points");
      }

      // 创建贝塞尔曲线
      TColgp_Array1OfPnt poles(1, pointsGroup.size());
      for (size_t j = 0; j < pointsGroup.size(); ++j) {
        poles.SetValue(j + 1, pointsGroup[j]);
      }
      Handle(Geom_BezierCurve) curve = new Geom_BezierCurve(poles);

      // 计算默认采样数
      double approxLength = 0;
      for (size_t j = 1; j < pointsGroup.size(); ++j) {
        approxLength += pointsGroup[j - 1].Distance(pointsGroup[j]);
      }
      int sampleCount = tessellation > 0
                            ? tessellation
                            : std::max(12, static_cast<int>(approxLength * 15));

      // 均匀采样贝塞尔曲线
      double first = curve->FirstParameter();
      double last = curve->LastParameter();
      double step = (last - first) / sampleCount;

      for (int j = 0; j <= sampleCount; ++j) {
        double param = first + j * step;
        points.push_back(curve->Value(param));
      }
      break;
    }
    default:
      throw Standard_ConstructionError("Unknown curve type");
    }
  }

  // 去除连续重复点
  auto last = std::unique(points.begin(), points.end(),
                          [](const gp_Pnt &a, const gp_Pnt &b) {
                            return a.Distance(b) < Precision::Confusion();
                          });
  points.erase(last, points.end());

  return points;
}


/**
 * @brief 创建角钢
 * @param params 角钢参数
 * @return TopoDS_Shape 生成的角钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_angle_steel(const angle_steel_params &params) {
  // 参数验证
  if (params.L1 <= 0 || params.L2 <= 0 || params.X <= 0 || params.length <= 0) {
    throw Standard_ConstructionError("All dimensions must be positive");
  }
  if (params.L2 >= params.L1) {
    throw Standard_ConstructionError("L2 must be less than L1");
  }
  if (params.X >= params.L1 || params.X >= params.L2) {
    throw Standard_ConstructionError(
        "Thickness must be less than both L1 and L2");
  }

  // 创建角钢截面轮廓（调整到ZY平面）
  BRepBuilderAPI_MakeWire wireMaker;

  // 关键点定义（工业标准不等边角钢形状）
  gp_Pnt p1(0, 0, 0);                 // 原点(角钢内角点)
  gp_Pnt p2(0, 0, params.L1);         // 长边顶点
  gp_Pnt p3(0, -params.X, params.L1); // 长边厚度点
  gp_Pnt p4(0, -params.X, params.X);  // 新增折角点
  gp_Pnt p5(0, -params.L2, params.X); // 短边顶点
  gp_Pnt p6(0, -params.L2, 0);        // 短边端点
  gp_Pnt p7(0, -params.X, 0);         // 厚度点

  // 添加边线（按工业标准顺序连接）
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge()); // 长边外缘
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge()); // 长边厚度
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge()); // 长边折角
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge()); // 斜边连接
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge()); // 短边外缘
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p6, p7).Edge()); // 短边厚度
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p1).Edge()); // 闭合边

  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create angle steel profile");
  }

  // 创建截面面
  BRepBuilderAPI_MakeFace faceMaker(wireMaker.Wire());
  if (!faceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create angle steel face");
  }

  // 沿X轴拉伸
  BRepPrimAPI_MakePrism prismMaker(faceMaker.Face(),
                                   gp_Vec(params.length, 0, 0));

  return prismMaker.Shape();
}


/**
 * @brief 创建带定位的不等边角钢
 * @param params 不等边角钢参数
 * @param position 角钢起点位置
 * @param xDirection 长度方向（默认X轴）
 * @param longEdgeDir 长边方向（默认Z轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_angle_steel(const angle_steel_params &params,
                                const gp_Pnt &position,
                                const gp_Dir &xDirection,
                                const gp_Dir &longEdgeDir) {
  // 首先创建标准方向的角钢
  TopoDS_Shape angleSteel = create_angle_steel(params);

  // 计算短边方向
  gp_Dir shortEdgeDir = xDirection.Crossed(longEdgeDir).Reversed();

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DX(), gp::DZ());
  gp_Ax3 targetAx3(position, xDirection, longEdgeDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(angleSteel, transformation);
  return transform.Shape();
}


/**
 * @brief 创建工字钢截面轮廓（无圆弧过渡）
 * @param height 总高度 (Z轴方向)
 * @param flangeWidth 翼缘宽度 (Y轴方向)
 * @param webThickness 腹板厚度 (Y轴方向)
 * @param flangeThickness 翼缘厚度 (Z轴方向)
 * @return TopoDS_Wire 生成的截面轮廓线
 */
TopoDS_Wire create_ibeam_profile(double height, double flangeWidth,
                                 double webThickness, double flangeThickness) {
  BRepBuilderAPI_MakeWire wireMaker;

  // 计算关键尺寸
  double halfFlangeWidth = flangeWidth / 2;
  double halfWebThickness = webThickness / 2;

  // 定义所有关键点（按顺时针顺序）
  // 右侧轮廓点
  gp_Pnt p1(0, halfFlangeWidth, 0);
  gp_Pnt p2(0, halfFlangeWidth, flangeThickness);
  gp_Pnt p3(0, halfWebThickness, flangeThickness);
  gp_Pnt p4(0, halfWebThickness, height - flangeThickness);
  gp_Pnt p5(0, halfFlangeWidth, height - flangeThickness);
  gp_Pnt p6(0, halfFlangeWidth, height);

  // 左侧轮廓点
  gp_Pnt p7(0, -halfFlangeWidth, height);
  gp_Pnt p8(0, -halfFlangeWidth, height - flangeThickness);
  gp_Pnt p9(0, -halfWebThickness, height - flangeThickness);
  gp_Pnt p10(0, -halfWebThickness, flangeThickness);
  gp_Pnt p11(0, -halfFlangeWidth, flangeThickness);
  gp_Pnt p12(0, -halfFlangeWidth, 0);

  // 构建轮廓线（按顺序连接所有点）
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p12, p1).Edge());  // 下翼缘
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());   // 右下翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());   // 右下腹板水平段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());   // 右腹板垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge());   // 右上腹板水平段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge());   // 右上翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p6, p7).Edge());   // 上翼缘
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8).Edge());   // 左上翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, p9).Edge());   // 左上腹板水平段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p9, p10).Edge());  // 左腹板垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p10, p11).Edge()); // 左下腹板水平段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p11, p12).Edge()); // 左下翼缘垂直段

  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create I-Beam profile");
  }

  return wireMaker.Wire();
}


/**
 * @brief 创建工字钢
 * @param params 工字钢参数
 * @return TopoDS_Shape 生成的工字钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_i_shaped_steel(const i_shaped_steel_params &params) {
  // 参数验证
  if (params.height <= 0 || params.length <= 0) {
    throw Standard_ConstructionError("All dimensions must be positive");
  }

  // 创建工字钢截面轮廓
  TopoDS_Wire profile =
      create_ibeam_profile(params.height, params.flangeWidth,
                           params.webThickness, params.flangeThickness);

  // 创建截面面
  BRepBuilderAPI_MakeFace faceMaker(profile);
  if (!faceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create I-beam face");
  }

  // 沿X轴拉伸
  BRepPrimAPI_MakePrism prismMaker(faceMaker.Face(),
                                   gp_Vec(params.length, 0, 0));

  return prismMaker.Shape();
}


/**
 * @brief 创建带定位的工字钢
 * @param params 工字钢参数
 * @param position 工字钢起点位置
 * @param xDirection 长度方向（默认X轴）
 * @param zDirection 腹板方向（默认Z轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_i_shaped_steel(const i_shaped_steel_params &params,
                                   const gp_Pnt &position,
                                   const gp_Dir &xDirection,
                                   const gp_Dir &zDirection) {
  // 首先创建标准方向的工字钢
  TopoDS_Shape ibeam = create_i_shaped_steel(params);

  // 计算Y方向（确保右手坐标系）
  gp_Dir yDirection = xDirection.Crossed(zDirection);

  // 创建坐标系变换（明确指定源坐标系）
  gp_Ax3 sourceAx3(gp::Origin(), gp::DX(), gp::DZ()); // X:长度, Z:腹板
  gp_Ax3 targetAx3(position, xDirection, zDirection);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(ibeam, transformation);
  return transform.Shape();
}


/**
 * @brief 创建槽钢截面轮廓（无圆弧过渡）
 * @param height 总高度 (Z轴方向)
 * @param flangeWidth 翼缘宽度 (Y轴方向)
 * @param webThickness 腹板厚度 (Y轴方向)
 * @param flangeThickness 翼缘厚度 (Z轴方向)
 * @return TopoDS_Wire 生成的截面轮廓线
 */
TopoDS_Wire create_channel_profile(double height, double flangeWidth,
                                   double webThickness,
                                   double flangeThickness) {
  BRepBuilderAPI_MakeWire wireMaker;

  // 调整关键尺寸计算（Y轴负方向为开口）
  double halfHeight = height / 2;
  double webEndY = -webThickness; // 腹板末端Y坐标（保持厚度绝对值）

  // 重新定义关键点（腹板中心在原点，开口方向-Y）
  gp_Pnt p1(0, 0, -halfHeight);            // 腹板底部中心
  gp_Pnt p2(0, -flangeWidth, -halfHeight); // 下翼缘端部
  gp_Pnt p3(0, -flangeWidth, -halfHeight + flangeThickness);
  gp_Pnt p4(0, webEndY, -halfHeight + flangeThickness); // 腹板-翼缘连接点
  gp_Pnt p5(0, webEndY, halfHeight - flangeThickness);  // 腹板上部连接点
  gp_Pnt p6(0, -flangeWidth, halfHeight - flangeThickness);
  gp_Pnt p7(0, -flangeWidth, halfHeight); // 上翼缘端部
  gp_Pnt p8(0, 0, halfHeight);            // 腹板顶部中心

  // 构建轮廓线（按顺序连接所有点）
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge()); // 下翼缘底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge()); // 右下翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge()); // 右下翼缘水平段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge()); // 腹板垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge()); // 右上翼缘水平段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p6, p7).Edge()); // 右上翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8).Edge()); // 上翼缘顶部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, p1).Edge()); // 闭合轮廓

  // 验证几何完整性
  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create channel profile");
  }

  TopoDS_Wire result = wireMaker.Wire();
  if (!result.Closed()) {
    throw Standard_ConstructionError("Channel profile is not closed");
  }

  return result;
}

/**
 * @brief 创建槽钢
 * @param params 槽钢参数
 * @return TopoDS_Shape 生成的槽钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_channel_steel(const channel_steel_params &params) {
  // 参数验证
  if (params.height <= 0 || params.flangeWidth <= 0 ||
      params.webThickness <= 0 || params.flangeThickness <= 0 ||
      params.length <= 0) {
    throw Standard_ConstructionError("All dimensions must be positive");
  }
  if (params.webThickness >= params.flangeWidth) {
    throw Standard_ConstructionError(
        "Web thickness must be less than flange width");
  }
  if (2 * params.flangeThickness >= params.height) {
    throw Standard_ConstructionError("Flange thickness too large for height");
  }

  // 创建槽钢截面轮廓
  TopoDS_Wire profile =
      create_channel_profile(params.height, params.flangeWidth,
                             params.webThickness, params.flangeThickness);

  // 创建截面面
  BRepBuilderAPI_MakeFace faceMaker(profile);
  if (!faceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create channel face");
  }

  // 沿X轴拉伸
  BRepPrimAPI_MakePrism prismMaker(faceMaker.Face(),
                                   gp_Vec(params.length, 0, 0));

  return prismMaker.Shape();
}


/**
 * @brief 创建带定位的槽钢
 * @param params 槽钢参数
 * @param position 槽钢起点位置
 * @param xDirection 长度方向（默认X轴）
 * @param zDirection 腹板方向（默认Z轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_channel_steel(const channel_steel_params &params,
                                  const gp_Pnt &position,
                                  const gp_Dir &xDirection,
                                  const gp_Dir &zDirection) {
  // 首先创建标准方向的槽钢
  TopoDS_Shape channel = create_channel_steel(params);

  // 计算Y方向
  gp_Dir yDirection = xDirection.Crossed(zDirection);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DX(), gp::DZ()); // X:长度, Z:腹板
  gp_Ax3 targetAx3(position, xDirection, zDirection);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(channel, transformation);
  return transform.Shape();
}


/**
 * @brief 创建T型钢截面轮廓
 * @param height 高度 (Z轴方向)
 * @param width 宽度 (Y轴方向)
 * @param webThickness 腹板厚度
 * @param flangeThickness 翼缘厚度
 * @param radius 过渡圆弧半径
 * @return TopoDS_Wire 生成的截面轮廓线
 */
TopoDS_Wire create_t_steel_profile(double height, double width,
                                   double webThickness,
                                   double flangeThickness) {
  BRepBuilderAPI_MakeWire wireMaker;

  // 计算关键尺寸
  double halfWidth = width / 2;
  double halfWeb = webThickness / 2;

  // 重新定义关键点（新增4个连接点）
  // 腹板底部点
  gp_Pnt p1(0, 0, -height);                 // 底部中心
  gp_Pnt p2(0, -halfWeb, -height);          // 底部左侧
  gp_Pnt p3(0, -halfWeb, -flangeThickness); // 新增：腹板顶部左侧
  gp_Pnt p4(0, -halfWeb, 0);                // 顶部左侧
  gp_Pnt p5(0, halfWeb, 0);                 // 顶部右侧
  gp_Pnt p6(0, halfWeb, -flangeThickness);  // 新增：腹板顶部右侧
  gp_Pnt p7(0, halfWeb, -height);           // 底部右侧

  // 翼缘部分点
  gp_Pnt p8(0, -halfWidth, 0);                // 左侧端点
  gp_Pnt p9(0, -halfWidth, -flangeThickness); // 新增：左侧翼缘底部
  gp_Pnt p10(0, halfWidth, -flangeThickness); // 新增：右侧翼缘底部
  gp_Pnt p11(0, halfWidth, 0);                // 右侧端点

  // 构建完整轮廓（顺时针连接）
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());   // 底部中心→左
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());   // 腹板左侧垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p9).Edge());   // 新增：左侧翼缘连接
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p9, p8).Edge());   // 左侧翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, p4).Edge());   // 顶部翼缘左段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge());   // 腹板顶部水平段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p5, p11).Edge());  // 顶部翼缘右段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p11, p10).Edge()); // 右侧翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p10, p6).Edge());  // 新增：右侧翼缘连接
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p6, p7).Edge());   // 腹板右侧垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p1).Edge());   // 底部右侧→中心

  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create T-steel profile");
  }

  // 验证轮廓闭合性
  if (!wireMaker.Wire().Closed()) {
    throw Standard_ConstructionError("T-steel profile is not closed");
  }

  return wireMaker.Wire();
}


/**
 * @brief 创建T型钢
 * @param params T型钢参数
 * @return TopoDS_Shape 生成的T型钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_t_steel(const t_steel_params &params) {
  // 参数验证
  if (params.height <= 0 || params.width <= 0 || params.webThickness <= 0 ||
      params.flangeThickness <= 0 || params.length <= 0) {
    throw Standard_ConstructionError("All dimensions must be positive");
  }
  if (params.webThickness >= params.width) {
    throw Standard_ConstructionError("Web thickness must be less than width");
  }
  if (params.flangeThickness >= params.height) {
    throw Standard_ConstructionError(
        "Flange thickness must be less than height");
  }

  // 创建截面轮廓
  TopoDS_Wire profile = create_t_steel_profile(
      params.height, params.width, params.webThickness, params.flangeThickness);

  // 创建截面面
  BRepBuilderAPI_MakeFace faceMaker(profile);
  if (!faceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create T-steel face");
  }

  // 沿X轴拉伸
  BRepPrimAPI_MakePrism prismMaker(faceMaker.Face(),
                                   gp_Vec(params.length, 0, 0));

  return prismMaker.Shape();
}


/**
 * @brief 创建带定位的T型钢
 * @param params T型钢参数
 * @param position T型钢起点位置
 * @param xDirection 长度方向（默认X轴）
 * @param zDirection 高度方向（默认Z轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_t_steel(const t_steel_params &params,
                            const gp_Pnt &position, const gp_Dir &xDirection,
                            const gp_Dir &zDirection) {
  // 首先创建标准方向的T型钢
  TopoDS_Shape tsteel = create_t_steel(params);

  // 计算Y方向（根据右手定则）
  gp_Dir yDirection = zDirection.Crossed(xDirection);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX()); // Z:高度, X:长度
  gp_Ax3 targetAx3(position, zDirection, xDirection);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(tsteel, transformation);
  return transform.Shape();
}


/**
 * @brief 创建矩形梁
 * @param width 梁宽度
 * @param height 梁高度
 * @param length 梁长度
 * @param center 梁中心位置
 * @return TopoDS_Shape
 */
TopoDS_Shape create_rectangular_beam(double width, double height, double length,
                                     const gp_Pnt &center) {
  BRepBuilderAPI_MakeWire wire;
  double halfW = width / 2;
  double halfH = height / 2;

  // 创建矩形轮廓
  wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfW, -halfH, 0),
                                   gp_Pnt(halfW, -halfH, 0))
               .Edge());
  wire.Add(
      BRepBuilderAPI_MakeEdge(gp_Pnt(halfW, -halfH, 0), gp_Pnt(halfW, halfH, 0))
          .Edge());
  wire.Add(
      BRepBuilderAPI_MakeEdge(gp_Pnt(halfW, halfH, 0), gp_Pnt(-halfW, halfH, 0))
          .Edge());
  wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfW, halfH, 0),
                                   gp_Pnt(-halfW, -halfH, 0))
               .Edge());

  BRepBuilderAPI_MakeFace face(wire.Wire());

  // 创建梁并移动到指定位置
  TopoDS_Shape beam =
      BRepPrimAPI_MakePrism(face.Face(), gp_Vec(0, 0, length)).Shape();

  gp_Trsf transform;
  transform.SetTranslation(
      gp_Vec(center.X(), center.Y(), center.Z() - length / 2));
  BRepBuilderAPI_Transform mover(beam, transform);

  return mover.Shape();
}


TopoDS_Shape create_transition_section(const tunnel_well_params &params,
                                       bool isOuter) {
  // 创建过渡路径 (沿X轴方向)
  double startX = -params.radius - params.outerWallThickness - 0.01;
  double endX = params.radius + params.outerWallThickness + 0.01;
  // 计算实际使用的尺寸参数
  double leftWidth = params.leftWidth;
  double leftHeight = params.leftHeight;
  double leftArcHeight = params.leftArcHeight;
  double rightWidth = params.rightWidth;
  double rightHeight = params.rightHeight;
  double rightArcHeight = params.rightArcHeight;
  double heightOffset = 0;

  if (isOuter) {
    // 外轮廓需要加上壁厚
    leftWidth += 2 * params.outerWallThickness;
    leftHeight += 2 * params.outerWallThickness;
    leftArcHeight += params.outerWallThickness;
    rightWidth += 2 * params.outerWallThickness;
    rightHeight += 2 * params.outerWallThickness;
    rightArcHeight += params.outerWallThickness;
    heightOffset = -params.outerWallThickness;
  }

  // 创建左端截面 (YZ平面)
  TopoDS_Wire leftSection;
  switch (params.leftSectionType) {
  case connection_section_style::RECTANGULAR:
    leftSection = BRepBuilderAPI_MakePolygon(
                      gp_Pnt(startX, -leftWidth / 2, heightOffset),
                      gp_Pnt(startX, leftWidth / 2, heightOffset),
                      gp_Pnt(startX, leftWidth / 2, leftHeight + heightOffset),
                      gp_Pnt(startX, -leftWidth / 2, leftHeight + heightOffset),
                      Standard_True)
                      .Wire();
    break;
  case connection_section_style::HORSESHOE: {
    double radius = leftWidth / 2;
    gp_Pnt startPoint(startX, -radius,
                      leftHeight - leftArcHeight + heightOffset);
    gp_Pnt midPoint(startX, 0, leftHeight + heightOffset); // 拱顶中点
    gp_Pnt endPoint(startX, radius, leftHeight - leftArcHeight + heightOffset);

    // 使用三点法创建圆弧
    Handle(Geom_TrimmedCurve) arc =
        GC_MakeArcOfCircle(startPoint, midPoint, endPoint).Value();

    BRepBuilderAPI_MakeWire wireMaker;
    // 添加左侧垂直线
    wireMaker.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(startX, -radius, heightOffset),
                                          startPoint)
                      .Edge());
    // 添加顶部圆弧
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc).Edge());
    // 添加右侧垂直线
    wireMaker.Add(
        BRepBuilderAPI_MakeEdge(endPoint, gp_Pnt(startX, radius, heightOffset))
            .Edge());
    // 添加底部水平线
    wireMaker.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(startX, radius, heightOffset),
                                          gp_Pnt(startX, -radius, heightOffset))
                      .Edge());

    leftSection = wireMaker.Wire();
    break;
  }
  case connection_section_style::CIRCULAR:
    leftSection =
        BRepBuilderAPI_MakeWire(
            BRepBuilderAPI_MakeEdge(
                gp_Circ(
                    gp_Ax2(gp_Pnt(startX, 0, params.leftHeight / 2), gp::DX()),
                    leftHeight / 2))
                .Edge())
            .Wire();
    break;
  }

  // 创建右端截面 (YZ平面) - 类似左端截面修改
  TopoDS_Wire rightSection;
  switch (params.rightSectionType) {
  case connection_section_style::RECTANGULAR:
    rightSection =
        BRepBuilderAPI_MakePolygon(
            gp_Pnt(endX, -rightWidth / 2, heightOffset),
            gp_Pnt(endX, rightWidth / 2, heightOffset),
            gp_Pnt(endX, rightWidth / 2, rightHeight + heightOffset),
            gp_Pnt(endX, -rightWidth / 2, rightHeight + heightOffset),
            Standard_True)
            .Wire();
    break;
  case connection_section_style::HORSESHOE: {
    double radius = rightWidth / 2;
    gp_Pnt arcStart(endX, -radius, rightHeight - rightArcHeight + heightOffset);
    gp_Pnt arcMid(endX, 0, rightHeight + heightOffset); // 拱顶中点
    gp_Pnt arcEnd(endX, radius, rightHeight - rightArcHeight + heightOffset);

    // 使用三点法创建圆弧
    Handle(Geom_TrimmedCurve) arc =
        GC_MakeArcOfCircle(arcStart, arcMid, arcEnd).Value();

    BRepBuilderAPI_MakeWire wireMaker;
    // 添加左侧垂直线
    wireMaker.Add(
        BRepBuilderAPI_MakeEdge(gp_Pnt(endX, -radius, heightOffset), arcStart)
            .Edge());
    // 添加顶部圆弧
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc).Edge());
    // 添加右侧垂直线
    wireMaker.Add(
        BRepBuilderAPI_MakeEdge(arcEnd, gp_Pnt(endX, radius, heightOffset))
            .Edge());
    // 添加底部水平线
    wireMaker.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(endX, radius, heightOffset),
                                          gp_Pnt(endX, -radius, heightOffset))
                      .Edge());

    rightSection = wireMaker.Wire();
    break;
  }
  case connection_section_style::CIRCULAR:
    rightSection =
        BRepBuilderAPI_MakeWire(
            BRepBuilderAPI_MakeEdge(
                gp_Circ(
                    gp_Ax2(gp_Pnt(endX, 0, params.rightHeight / 2), gp::DX()),
                    rightHeight / 2))
                .Edge())
            .Wire();
    break;
  }

  BRepOffsetAPI_ThruSections transitionMaker(Standard_True, Standard_True);
  transitionMaker.AddWire(leftSection);
  transitionMaker.AddWire(rightSection);
  transitionMaker.Build();

  if (!transitionMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create transition section");
  }
  TopoDS_Shape transition = transitionMaker.Shape();

  // 检查是否为 Shell
  if (transition.ShapeType() == TopAbs_SHELL) {
    TopoDS_Shell shell = TopoDS::Shell(transition);
    BRepBuilderAPI_MakeSolid solidMaker(shell);
    if (solidMaker.IsDone()) {
      TopoDS_Solid transitionSolid = solidMaker.Solid();
      return transitionSolid;
    } else {
      std::cerr << "无法将 Shell 转换为 Solid！" << std::endl;
    }
  }
  return transitionMaker.Shape();
}


// 计算单个拐角内外长度差的核心函数
// 参数说明：
//   angle_deg - 拐角角度（单位：度）
//   thickness - 墙体厚度（单位：米）
double calculate_length_difference(double angle_deg, double thickness) {
  // 角度有效性检查
  if (angle_deg <= 0 || angle_deg >= 180) {
    throw std::invalid_argument("角度应在0到180度之间");
  }

  // 厚度有效性检查
  if (thickness <= 0) {
    throw std::invalid_argument("厚度必须大于0");
  }

  // 角度转换为弧度
  const double angle_rad = angle_deg * M_PI / 180.0;

  // 计算长度差（核心公式）
  return angle_rad * thickness;
}


TopoDS_Wire
create_channel_centerline(const std::vector<channel_point> &points) {
  if (points.size() < 2) {
    throw Standard_ConstructionError("At least 2 points are required");
  }

  // 创建路径线框
  BRepBuilderAPI_MakeWire pathWire;

  // 处理点序列
  for (size_t i = 0; i < points.size() - 1; i++) {
    const gp_Pnt &current = points[i].position;
    const gp_Pnt &next = points[i + 1].position;

    if (points[i].type == channel_point_type::LINE &&
        points[i + 1].type == channel_point_type::LINE) { // 普通节点
      // 创建直线段
      pathWire.Add(BRepBuilderAPI_MakeEdge(current, next).Edge());
    } else if (points[i].type == channel_point_type::ARC) { // 弧形节点
      // 确保有前一个点和后一个点
      if (i == 0 || i == points.size() - 1) {
        throw Standard_ConstructionError("弧形节点需要前后都有节点");
      }

      const gp_Pnt &prev = points[i - 1].position;

      // 创建三点圆弧
      pathWire.Add(BRepBuilderAPI_MakeEdge(
                       GC_MakeArcOfCircle(prev, current, next).Value())
                       .Edge());
    }
  }

  if (!pathWire.IsDone()) {
    throw Standard_ConstructionError("路径线框创建失败");
  }

  return pathWire.Wire();
}


std::vector<gp_Pnt>
sample_channel_points(const std::vector<channel_point> &points,
                      double tessellation) {
  if (points.size() < 2) {
    throw Standard_ConstructionError("At least 2 points are required");
  }

  std::vector<gp_Pnt> sampledPoints;

  // 处理点序列
  for (size_t i = 0; i < points.size() - 1; i++) {
    const gp_Pnt &current = points[i].position;
    const gp_Pnt &next = points[i + 1].position;

    if (points[i].type == channel_point_type::LINE &&
        points[i + 1].type == channel_point_type::LINE) { // 直线段
      // 计算默认采样数
      double length = current.Distance(next);
      int sampleCount = tessellation > 0
                            ? tessellation
                            : std::max(2, static_cast<int>(length * 10));

      // 直线均匀采样
      for (int j = 0; j <= sampleCount; j++) {
        double ratio = static_cast<double>(j) / sampleCount;
        sampledPoints.push_back(
            gp_Pnt(current.X() * (1 - ratio) + next.X() * ratio,
                   current.Y() * (1 - ratio) + next.Y() * ratio,
                   current.Z() * (1 - ratio) + next.Z() * ratio));
      }
    } else if (points[i].type == channel_point_type::ARC) { // 弧线段
      // 验证弧线点位置
      if (i == 0 || i == points.size() - 1) {
        throw Standard_ConstructionError(
            "Arc point must have both previous and next points");
      }

      const gp_Pnt &prev = points[i - 1].position;

      // 创建三点圆弧
      GC_MakeArcOfCircle arcMaker(prev, current, next);
      if (!arcMaker.IsDone()) {
        throw Standard_ConstructionError("Failed to create arc segment");
      }

      // 计算默认采样数
      Handle(Geom_TrimmedCurve) arc = arcMaker.Value();

      // Create adaptor for the arc
      GeomAdaptor_Curve curveAdaptor(arc);

      double arcLength = GCPnts_AbscissaPoint::Length(curveAdaptor);
      int sampleCount = tessellation > 0
                            ? tessellation
                            : std::max(8, static_cast<int>(arcLength * 15));

      // 均匀采样圆弧
      double first = arcMaker.Value()->FirstParameter();
      double last = arcMaker.Value()->LastParameter();
      double step = (last - first) / sampleCount;

      for (int j = 0; j <= sampleCount; j++) {
        double param = first + j * step;
        sampledPoints.push_back(arcMaker.Value()->Value(param));
      }
    }
  }

  // 去除连续重复点
  auto last = std::unique(sampledPoints.begin(), sampledPoints.end(),
                          [](const gp_Pnt &a, const gp_Pnt &b) {
                            return a.Distance(b) < Precision::Confusion();
                          });
  sampledPoints.erase(last, sampledPoints.end());

  return sampledPoints;
}


TopoDS_Shape create_channel_shape(
    TopoDS_Shape section, TopoDS_Wire pathWire,
    BRepBuilderAPI_TransitionMode mode) {
  // 参数校验
  if (section.IsNull()) {
    throw Standard_ConstructionError("截面形状不能为空");
  }
  if (section.ShapeType() != TopAbs_WIRE) {
    throw Standard_ConstructionError("截面形状必须是线框");
  }
  if (!BRep_Tool::IsClosed(section)) {
    throw Standard_ConstructionError("截面形状必须是闭合的");
  }

  // 创建管道形状
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.Add(section, Standard_False, Standard_True);
  pipeMaker.SetTransitionMode(mode);
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }

  if (!pipeMaker.MakeSolid()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }

  return pipeMaker.Shape();
}

TopoDS_Shape create_shape_from_profile(const shape_profile &profile,
                                       bool isFace,
                                       gp_Ax2 *sectionAxes) {
  struct profile_visitor : public boost::static_visitor<TopoDS_Shape> {
    bool _is_face;
    gp_Trsf _transform;
    gp_Ax2 *_axes;

    profile_visitor(bool isFace, gp_Ax2 *sectionAxes)
        : _is_face(isFace), _transform(), _axes(nullptr) {
      if (sectionAxes != nullptr) {
        _transform.SetTransformation(*sectionAxes,
                                     gp_Ax2(gp::Origin(), gp::DZ()));
        _axes = sectionAxes;
      }
    }

    TopoDS_Shape operator()(const triangle_profile &prof) const {
      BRepBuilderAPI_MakePolygon polyBuilder;
      polyBuilder.Add(prof.p1.Transformed(_transform));
      polyBuilder.Add(prof.p2.Transformed(_transform));
      polyBuilder.Add(prof.p3.Transformed(_transform));
      polyBuilder.Add(prof.p1.Transformed(_transform));
      TopoDS_Wire wire = polyBuilder.Wire();
      if (_is_face) {
        return BRepBuilderAPI_MakeFace(wire).Face();
      }
      return wire;
    }

    TopoDS_Shape operator()(const rectangle_profile &prof) const {
      BRepBuilderAPI_MakePolygon polyBuilder;
      gp_Pnt p1 = prof.p1;
      gp_Pnt p2 = prof.p2;
      gp_Pnt p3 = gp_Pnt(p2.X(), p1.Y(), p1.Z());
      gp_Pnt p4 = gp_Pnt(p1.X(), p2.Y(), p2.Z());

      p1 = p1.Transformed(_transform);
      p2 = p2.Transformed(_transform);
      p3 = p3.Transformed(_transform);
      p4 = p4.Transformed(_transform);

      polyBuilder.Add(p1);
      polyBuilder.Add(p3);
      polyBuilder.Add(p2);
      polyBuilder.Add(p4);
      polyBuilder.Add(p1);

      TopoDS_Wire wire = polyBuilder.Wire();
      if (_is_face) {
        return BRepBuilderAPI_MakeFace(wire).Face();
      }
      return wire;
    }

    TopoDS_Shape operator()(const circ_profile &prof) const {
      gp_Pnt center = prof.center.Transformed(_transform);

      gp_Ax2 axis(center, this->_axes != nullptr ? this->_axes->Direction()
                                                 : prof.norm);
      gp_Circ circle(axis, prof.radius);

      TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(circle).Edge();
      BRepBuilderAPI_MakeWire wireBuilder(edge);
      TopoDS_Wire wire = wireBuilder.Wire();

      if (_is_face) {
        return BRepBuilderAPI_MakeFace(wire).Face();
      }
      return wire;
    }

    TopoDS_Shape operator()(const elips_profile &prof) const {
      gp_Pnt center = prof.center.Transformed(_transform);
      gp_Pnt s1 = prof.s1.Transformed(_transform);
      gp_Pnt s2 = prof.s2.Transformed(_transform);

      gp_Dir majorDir = gp_Dir(s1.XYZ() - center.XYZ());
      gp_Dir minorDir = gp_Dir(s2.XYZ() - center.XYZ());
      gp_Dir normal = majorDir.Crossed(minorDir);

      gp_Ax2 axis(center, normal);
      double majorRadius = s1.Distance(center);
      double minorRadius = s2.Distance(center);
      gp_Elips ellipse(axis, majorRadius, minorRadius);

      TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(ellipse).Edge();
      BRepBuilderAPI_MakeWire wireBuilder(edge);
      TopoDS_Wire wire = wireBuilder.Wire();

      if (_is_face) {
        return BRepBuilderAPI_MakeFace(wire).Face();
      }
      return wire;
    }

    TopoDS_Shape operator()(const polygon_profile &prof) const {
      // 创建外轮廓线框(应确保是逆时针方向)
      BRepBuilderAPI_MakePolygon polyBuilder;
      for (const auto &point : prof.edges) {
        polyBuilder.Add(point.Transformed(_transform));
      }
      if (!prof.edges.empty() &&
          !prof.edges.front().IsEqual(prof.edges.back(),
                                      Precision::Confusion())) {
        polyBuilder.Add(prof.edges.front().Transformed(_transform));
      }
      TopoDS_Wire outerWire = polyBuilder.Wire();

      // 检查并修正外轮廓方向
      if (!outerWire.IsNull()) {
        BRepTools_WireExplorer explorer(outerWire);
        if (!explorer.More()) {
          return TopoDS_Shape();
        }
        if (!IsOuterWireCCW(outerWire)) {
          outerWire.Reverse();
        }
      }

      if (_is_face) {
        BRepBuilderAPI_MakeFace faceBuilder(outerWire);

        // 处理内轮廓(孔)
        for (const auto &inner : prof.inners) {
          BRepBuilderAPI_MakePolygon innerPolyBuilder;
          for (const auto &point : inner) {
            innerPolyBuilder.Add(point.Transformed(_transform));
          }
          if (!inner.empty() &&
              !inner.front().IsEqual(inner.back(), Precision::Confusion())) {
            innerPolyBuilder.Add(inner.front().Transformed(_transform));
          }
          TopoDS_Wire innerWire = innerPolyBuilder.Wire();

          // 检查并修正内轮廓方向(应为顺时针)
          if (!innerWire.IsNull()) {
            if (IsOuterWireCCW(innerWire)) {
              innerWire.Reverse();
            }
            faceBuilder.Add(innerWire);
          }
        }

        return faceBuilder.Face();
      }
      return outerWire;
    }
  };

  return boost::apply_visitor(profile_visitor(isFace, sectionAxes), profile);
}


TopoDS_Shape create_revol(const revol_params &params) {
  TopoDS_Shape profileFace = create_shape_from_profile(params.profile, true);

  if (profileFace.IsNull()) {
    throw Standard_ConstructionError("Invalid profile for revolution");
  }

  BRepPrimAPI_MakeRevol revolMaker(profileFace, params.axis, params.angle);

  if (!revolMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create revolution shape");
  }

  return revolMaker.Shape();
}


TopoDS_Shape create_revol(const revol_params &params, const gp_Pnt &position,
                          const gp_Dir &direction, const gp_Dir &xDir) {
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  TopoDS_Shape revolved = create_revol(params);

  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(revolved, transformation);
  return transform.Shape();
}


TopoDS_Shape create_prism(const prism_params &params) {
  TopoDS_Shape profileFace = create_shape_from_profile(params.profile, true);

  if (profileFace.IsNull()) {
    throw Standard_ConstructionError("Invalid profile for prism");
  }

  gp_Vec extVec = gp_Vec(params.direction).Multiplied(params.height);

  BRepPrimAPI_MakePrism prismMaker(profileFace, extVec);

  if (!prismMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create prism");
  }

  return prismMaker.Shape();
}


TopoDS_Shape create_prism(const prism_params &params, const gp_Pnt &position,
                          const gp_Dir &direction, const gp_Dir &xDir) {
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  TopoDS_Shape prism = create_prism(params);

  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(prism, transformation);
  return transform.Shape();
}


TopoDS_Wire make_wire_from_segments(
    const std::vector<std::vector<gp_Pnt>> &wires,
    const boost::optional<std::vector<segment_type>> &segment_types) {
  if (wires.empty()) {
    throw std::runtime_error("Control points cannot be empty");
  }

  try {
    BRepBuilderAPI_MakeWire wireMaker;

    for (size_t i = 0; i < wires.size(); ++i) {
      const auto &pts = wires[i];
      segment_type type =
          segment_types ? (*segment_types)[i] : segment_type::LINE;

      switch (type) {
      case segment_type::LINE: {
        if (pts.size() != 2) {
          throw Standard_ConstructionError("Line requires exactly 2 points");
        }
        wireMaker.Add(BRepBuilderAPI_MakeEdge(pts[0], pts[1]));
        break;
      }
      case segment_type::THREE_POINT_ARC: {
        if (pts.size() != 3) {
          throw Standard_ConstructionError("Three-point arc requires 3 points");
        }
        GC_MakeArcOfCircle arcMaker(pts[0], pts[1], pts[2]);
        if (!arcMaker.IsDone()) {
          throw Standard_ConstructionError("Failed to create three-point arc");
        }
        wireMaker.Add(BRepBuilderAPI_MakeEdge(arcMaker.Value()));
        break;
      }
      case segment_type::CIRCLE_CENTER_ARC: {
        if (pts.size() != 3) {
          throw Standard_ConstructionError(
              "Center arc requires [start, center, end] points");
        }
        gp_Vec vec1(pts[0], pts[1]);
        gp_Vec vec2(pts[1], pts[2]);

        gp_Dir upDir = gp::DZ();
        gp_Vec cross = vec2.Crossed(vec1);
        // 检查叉积结果是否有效
        if (cross.Magnitude() < Precision::Confusion()) {
          upDir = gp::DZ();
        } else {
          upDir = cross.Normalized();
        }
        gp_Circ circle(gp_Ax2(pts[1], upDir), pts[0].Distance(pts[1]));
        GC_MakeArcOfCircle arcMaker(circle, pts[0], pts[2], true);
        if (!arcMaker.IsDone()) {
          throw Standard_ConstructionError("Failed to create center arc");
        }
        wireMaker.Add(BRepBuilderAPI_MakeEdge(arcMaker.Value()));
        break;
      }
      case segment_type::SPLINE: {
        if (pts.size() < 2) {
          throw Standard_ConstructionError("Spline requires at least 2 points");
        }
        Handle(TColgp_HArray1OfPnt) array = new TColgp_HArray1OfPnt(
            1, static_cast<Standard_Integer>(pts.size()));
        for (size_t j = 0; j < pts.size(); ++j) {
          array->SetValue(static_cast<Standard_Integer>(j + 1), pts[j]);
        }
        GeomAPI_Interpolate interpolate(array, false, Precision::Confusion());
        interpolate.Perform();
        if (!interpolate.IsDone()) {
          throw Standard_ConstructionError("Failed to create spline");
        }
        wireMaker.Add(BRepBuilderAPI_MakeEdge(interpolate.Curve()));
        break;
      }
      case segment_type::BEZIER: {
        if (pts.size() < 3) { // 贝塞尔曲线至少需要起点、控制点和终点
          throw Standard_ConstructionError(
              "Bezier segment requires at least 3 points");
        }

        // 创建贝塞尔曲线控制点数组
        TColgp_Array1OfPnt poles(1, pts.size());
        for (size_t j = 0; j < pts.size(); ++j) {
          poles.SetValue(j + 1, pts[j]);
        }

        // 创建二次或三次贝塞尔曲线
        Handle(Geom_BezierCurve) bezierCurve;
        if (pts.size() == 3) { // 二次贝塞尔曲线
          bezierCurve = new Geom_BezierCurve(poles);
        } else { // 三次或更高阶贝塞尔曲线
          bezierCurve = new Geom_BezierCurve(poles);
        }

        // 创建边并添加到线框
        wireMaker.Add(BRepBuilderAPI_MakeEdge(bezierCurve).Edge());
        break;
      }
      default:
        throw Standard_ConstructionError("Unknown segment type");
      }
    }

    if (!wireMaker.IsDone()) {
      throw Standard_ConstructionError("Failed to create wire");
    }
    return wireMaker.Wire();
  } catch (const Standard_Failure &e) {
    throw std::runtime_error(e.GetMessageString());
  }
}


std::tuple<TopoDS_Shape, TopoDS_Wire, std::pair<gp_Dir, gp_Dir>>
create_pipe_helper(const pipe_params &params) {
  if (params.profiles.size() != 1 && params.profiles.size() != 2) {
    throw Standard_ConstructionError("Pipe requires exactly 1 or 2 profiles");
  }
  if (params.inner_profiles &&
      params.inner_profiles->size() != params.profiles.size()) {
    throw Standard_ConstructionError(
        "Inner profiles must match the number of profiles");
  }

  // 创建管道路径
  TopoDS_Wire pathWire =
      make_wire_from_segments({params.wire}, {{params.segment_type}});
  TopExp_Explorer edgeExplorer(pathWire, TopAbs_EDGE);
  TopoDS_Edge edge = TopoDS::Edge(edgeExplorer.Current());

  Standard_Real first, last;
  Handle(Geom_Curve) curve = BRep_Tool::Curve(edge, first, last);
  gp_Pnt pt;
  gp_Vec firstTangent;
  curve->D1(first, pt, firstTangent);
  gp_Vec lastTangent;
  curve->D1(last, pt, lastTangent);

  // 直线段 + 单剖面: 直接棱柱拉伸。
  // MakePipeShell 对直线脊线常产出 BRepCheck 无效的壳体 (实测),
  // 而直线扫掠与棱柱拉伸在几何上完全等价且结果稳定。
  TopoDS_Vertex v1, v2;
  TopExp::Vertices(edge, v1, v2);
  Handle(Geom_Line) lineGeom = Handle(Geom_Line)::DownCast(curve);
  if (!lineGeom.IsNull() && params.profiles.size() == 1) {
    gp_Ax2 straightAxes(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
    // 按原逻辑构造局部剖面 (upDir/refDir 约定保持一致)
    gp_Dir tanDir = firstTangent.Normalized();
    gp_Dir upDir = params.upDir ? *params.upDir : gp::DZ();
    gp_Dir refDir = gp_Vec(upDir.Crossed(tanDir)).Normalized();
    if (gp_Vec(refDir).SquareMagnitude() < Precision::SquareConfusion()) {
      refDir = gp::DY();
    }
    straightAxes = gp_Ax2(gp_Pnt(0, 0, 0), tanDir, refDir);

    TopoDS_Shape outer = create_shape_from_profile(
        params.profiles[0], false, &straightAxes);
    if (outer.IsNull()) {
      throw Standard_ConstructionError("Invalid outer profile for pipe");
    }
    gp_Vec extrusionVec(BRep_Tool::Pnt(v1), BRep_Tool::Pnt(v2));
    TopoDS_Shape result = BRepPrimAPI_MakePrism(outer, extrusionVec).Shape();
    if (params.inner_profiles &&
        !params.inner_profiles->empty()) {
      TopoDS_Shape inner = create_shape_from_profile(
          (*params.inner_profiles)[0], false, &straightAxes);
      if (inner.IsNull()) {
        throw Standard_ConstructionError("Invalid inner profile for pipe");
      }
      TopoDS_Shape innerSolid =
          BRepPrimAPI_MakePrism(inner, extrusionVec).Shape();
      BRepAlgoAPI_Cut cutOp(result, innerSolid);
      cutOp.Build();
      if (!cutOp.IsDone()) {
        throw Standard_ConstructionError("Failed to cut pipe inner");
      }
      result = cutOp.Shape();
    }
    return {result, pathWire, {firstTangent, lastTangent}};
  }

  // 创建管道
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  auto addOuterProfileAtVertex =
      [&](const TopoDS_Edge &edge, const shape_profile &profile,
          const TopoDS_Vertex &vertex, bool isFirst) {
        gp_Pnt point = BRep_Tool::Pnt(vertex);

        gp_Vec tangent = isFirst ? firstTangent : lastTangent;

        gp_Dir tanDir = tangent.Normalized();
        gp_Dir upDir = params.upDir ? *params.upDir : gp::DZ();
        gp_Dir refDir = gp_Vec(upDir.Crossed(tanDir)).Normalized();
        if (gp_Vec(refDir).SquareMagnitude() < Precision::SquareConfusion()) {
          refDir = gp::DY();
        }

        // 创建局部坐标系并添加截面
        gp_Ax2 localAxes(point, tanDir, refDir);

        TopoDS_Shape profileFace =
            create_shape_from_profile(profile, false, &localAxes);
        if (profileFace.IsNull()) {
          throw Standard_ConstructionError("Invalid outer profile for pipe");
        }
        pipeMaker.Add(profileFace, vertex);
      };

  // 获取外轮廓截面形状(作为面)
  addOuterProfileAtVertex(edge, params.profiles[0], v1, true);
  if (params.profiles.size() > 1) {
    addOuterProfileAtVertex(edge, params.profiles[1], v2, false);
  }

  pipeMaker.SetMode(Standard_True);

  // 设置过渡模式
  switch (params.transition_mode) {
  case transition_mode::RIGHT:
    pipeMaker.SetTransitionMode(BRepBuilderAPI_RightCorner);
    break;
  case transition_mode::ROUND:
    pipeMaker.SetTransitionMode(BRepBuilderAPI_RoundCorner);
    break;
  case transition_mode::TRANSFORMED:
    pipeMaker.SetTransitionMode(BRepBuilderAPI_Transformed);
    break;
  }

  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create pipe");
  }

  if (!pipeMaker.MakeSolid()) {
    throw Standard_ConstructionError("Failed to make pipe solid");
  }

  TopoDS_Shape outerShape = pipeMaker.Shape();

  if (params.inner_profiles) {
    BRepOffsetAPI_MakePipeShell innerMaker(pathWire);
    auto addProfileAtVertex = [&](const TopoDS_Edge &edge,
                                  const shape_profile &profile,
                                  const TopoDS_Vertex &vertex, bool isFirst) {
      gp_Pnt point = BRep_Tool::Pnt(vertex);

      gp_Vec tangent = isFirst ? firstTangent : lastTangent;

      gp_Dir tanDir = tangent.Normalized();
      gp_Dir upDir = params.upDir ? *params.upDir : gp::DZ();
      gp_Dir refDir = gp_Vec(upDir.Crossed(tanDir)).Normalized();
      if (gp_Vec(refDir).SquareMagnitude() < Precision::SquareConfusion()) {
        refDir = gp::DY();
      }

      // 创建局部坐标系并添加截面
      gp_Ax2 localAxes(point, tanDir, refDir);

      TopoDS_Shape profileFace =
          create_shape_from_profile(profile, false, &localAxes);
      if (profileFace.IsNull()) {
        throw Standard_ConstructionError("Invalid outer profile for pipe");
      }

      innerMaker.Add(profileFace, vertex);
    };

    addProfileAtVertex(edge, (*params.inner_profiles)[0], v1, true);
    if (params.inner_profiles->size() > 1) {
      addProfileAtVertex(edge, (*params.inner_profiles)[1], v2, false);
    }
    innerMaker.SetMode(Standard_True);

    // 设置过渡模式
    switch (params.transition_mode) {
    case transition_mode::RIGHT:
      innerMaker.SetTransitionMode(BRepBuilderAPI_RightCorner);
      break;
    case transition_mode::ROUND:
      innerMaker.SetTransitionMode(BRepBuilderAPI_RoundCorner);
      break;
    case transition_mode::TRANSFORMED:
      innerMaker.SetTransitionMode(BRepBuilderAPI_Transformed);
      break;
    }

    innerMaker.Build();

    if (!innerMaker.IsDone()) {
      throw Standard_ConstructionError("Failed to create pipe");
    }

    if (!innerMaker.MakeSolid()) {
      throw Standard_ConstructionError("Failed to make pipe solid");
    }

    TopoDS_Shape innerPipe = innerMaker.Shape();

    TopoDS_Shape result = BRepAlgoAPI_Cut(outerShape, innerPipe).Shape();
    return {result, pathWire, {firstTangent, lastTangent}};
  }
  return {outerShape, pathWire, {firstTangent, lastTangent}};
}


TopoDS_Shape create_pipe(const pipe_params &params) {
  auto pair = create_pipe_helper(params);
  return std::get<0>(pair);
}


TopoDS_Shape create_simple_pipe(flywave::topo::circ_profile maxProfile,
                                TopoDS_Wire pathWire, const gp_Dir &upDir) {
  // 获取路径起始点和切线方向
  gp_Pnt startPoint, endPoint;
  gp_Vec startTangent, endTangent;

  // 获取起始点信息
  BRepAdaptor_CompCurve curveAdaptor(pathWire);
  curveAdaptor.D1(curveAdaptor.FirstParameter(), startPoint, startTangent);

  // 获取结束点信息
  curveAdaptor.D1(curveAdaptor.LastParameter(), endPoint, endTangent);

  // 创建起始端截面
  gp_Dir startTanDir = startTangent.Normalized();
  gp_Dir startRefDir = gp_Vec(upDir.Crossed(startTanDir)).Normalized();
  gp_Ax2 startAxis(startPoint, startTanDir, startRefDir);
  gp_Circ startCircle(startAxis, maxProfile.radius);
  TopoDS_Edge startEdge = BRepBuilderAPI_MakeEdge(startCircle).Edge();
  TopoDS_Wire startWire = BRepBuilderAPI_MakeWire(startEdge).Wire();

  // 创建结束端截面
  gp_Dir endTanDir = endTangent.Normalized();
  gp_Dir endRefDir = gp_Vec(upDir.Crossed(endTanDir)).Normalized();
  gp_Ax2 endAxis(endPoint, endTanDir, endRefDir);
  gp_Circ endCircle(endAxis, maxProfile.radius);
  TopoDS_Edge endEdge = BRepBuilderAPI_MakeEdge(endCircle).Edge();
  TopoDS_Wire endWire = BRepBuilderAPI_MakeWire(endEdge).Wire();

  // 创建管道
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.Add(startWire, false, true); // 添加起始端截面
  pipeMaker.Add(endWire, false, true);   // 添加结束端截面
  pipeMaker.SetMode(true);
  pipeMaker.SetTransitionMode(BRepBuilderAPI_Transformed);

  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create simple pipe");
  }

  if (!pipeMaker.MakeSolid()) {
    throw Standard_ConstructionError("Failed to make simple pipe solid");
  }

  return pipeMaker.Shape();
}


std::pair<double, gp_Pnt>
compute_profile_radius_and_center(const shape_profile &profile) {
  struct ProfileVisitor
      : public boost::static_visitor<std::pair<double, gp_Pnt>> {

    ProfileVisitor() {}

    std::pair<double, gp_Pnt> operator()(const circ_profile &prof) const {
      return {prof.radius, prof.center};
    }

    std::pair<double, gp_Pnt> operator()(const triangle_profile &prof) const {
      // Calculate bounding box and center
      double min_x = std::min({prof.p1.X(), prof.p2.X(), prof.p3.X()});
      double min_y = std::min({prof.p1.Y(), prof.p2.Y(), prof.p3.Y()});
      double min_z = std::min({prof.p1.Z(), prof.p2.Z(), prof.p3.Z()});

      double max_x = std::max({prof.p1.X(), prof.p2.X(), prof.p3.X()});
      double max_y = std::max({prof.p1.Y(), prof.p2.Y(), prof.p3.Y()});
      double max_z = std::max({prof.p1.Z(), prof.p2.Z(), prof.p3.Z()});

      gp_Vec size(max_x - min_x, max_y - min_y, max_z - min_z);
      gp_Pnt center((prof.p1.X() + prof.p2.X() + prof.p3.X()) / 3,
                    (prof.p1.Y() + prof.p2.Y() + prof.p3.Y()) / 3,
                    (prof.p1.Z() + prof.p2.Z() + prof.p3.Z()) / 3);

      return {size.Magnitude() / 2, center};
    }

    std::pair<double, gp_Pnt> operator()(const rectangle_profile &prof) const {
      // Calculate diagonal vector and center
      gp_Vec diagonal(prof.p1, prof.p2);
      gp_Pnt center((prof.p1.X() + prof.p2.X()) / 2,
                    (prof.p1.Y() + prof.p2.Y()) / 2,
                    (prof.p1.Z() + prof.p2.Z()) / 2);

      return {diagonal.Magnitude() / 2, center};
    }

    std::pair<double, gp_Pnt> operator()(const elips_profile &prof) const {
      // Calculate major axis vector and center
      gp_Vec major_axis(prof.s1, prof.s2);
      return {major_axis.Magnitude() / 2, prof.center};
    }

    std::pair<double, gp_Pnt> operator()(const polygon_profile &prof) const {
      if (prof.edges.empty()) {
        return {0.0, gp_Pnt()};
      }

      // Calculate centroid
      double sum_x = 0, sum_y = 0, sum_z = 0;
      for (const auto &edge : prof.edges) {
        sum_x += edge.X();
        sum_y += edge.Y();
        sum_z += edge.Z();
      }
      gp_Pnt center(sum_x / prof.edges.size(), sum_y / prof.edges.size(),
                    sum_z / prof.edges.size());

      // Find maximum distance from center to any vertex
      double max_dist = 0.0;
      for (const auto &edge : prof.edges) {
        double dist = gp_Pnt(edge.X(), edge.Y(), edge.Z()).Distance(center);
        if (dist > max_dist) {
          max_dist = dist;
        }
      }

      return {max_dist, center};
    }

    std::pair<double, gp_Pnt>
    operator()(const std::vector<shape_profile> &profiles) const {
      if (profiles.empty()) {
        return {0.0, gp_Pnt()};
      }
      // For compound profiles, use the first profile
      return boost::apply_visitor(*this, profiles[0]);
    }
  };

  return boost::apply_visitor(ProfileVisitor{}, profile);
}


TopoDS_Shape
create_pipe_with_split_distances(const pipe_params &params,
                                 std::array<double, 2> splitDistances) {
  // 参数验证
  // NaN/Inf 区间会穿透所有比较校验, 产出不可复现的垃圾几何, 必须先拒绝
  if (splitDistances[0] != splitDistances[0] ||
      splitDistances[1] != splitDistances[1] ||
      splitDistances[0] < 0) {
    throw Standard_ConstructionError(
        "Split distances must be finite and start >= 0");
  }

  // 创建完整管道
  auto pair = create_pipe_helper(params);

  TopoDS_Shape fullPipe = std::get<0>(pair);
  TopoDS_Wire pathWire = std::get<1>(pair);

  // 计算路径总长度
  GProp_GProps lengthProps;
  BRepGProp::LinearProperties(pathWire, lengthProps);
  double totalLength = lengthProps.Mass();
  if (totalLength != totalLength || totalLength <= 0.0) {
    throw Standard_ConstructionError(
        "Pipe path has invalid (zero or NaN) length");
  }

  // 处理第二个分割距离
  if (splitDistances[1] < 0) {
    splitDistances[1] = totalLength;
  } else if (splitDistances[1] > totalLength) {
    splitDistances[1] = totalLength; // 越界钳制到全长 (与多段版语义统一)
  }
  if (splitDistances[1] <= splitDistances[0]) {
    // 含 start==end==0 等退化区间: 确定性拒绝
    throw Standard_ConstructionError("Invalid split interval (end <= start)");
  }

  // 如果不需要分割，直接返回完整管道
  if (splitDistances[0] == 0 && splitDistances[1] >= totalLength) {
    return fullPipe;
  }

  // 计算管道最大半径
  double maxRadius = 0;
  auto pair0 = compute_profile_radius_and_center(params.profiles[0]);
  maxRadius = std::max(maxRadius, pair0.first);

  if (params.profiles.size() == 2) {
    auto pair1 = compute_profile_radius_and_center(params.profiles[1]);
    maxRadius = std::max(maxRadius, pair1.first);
  }

  // 创建圆形截面
  circ_profile maxProfile;
  maxProfile.radius = maxRadius * 1.5;
  maxProfile.center = gp_Pnt(0, 0, 0);
  maxProfile.norm = gp_Dir(0, 0, 1);

  // 创建前段裁切体
  TopoDS_Shape frontCut;
  if (splitDistances[0] > 0) {
    TopoDS_Wire frontWire =
        clip_wire_between_distances_helper(pathWire, 0, splitDistances[0]);

    if (!frontWire.IsNull()) {
      // 使用最大圆形截面创建裁切体
      frontCut =
          create_simple_pipe(maxProfile, frontWire,
                             params.upDir ? *params.upDir : gp_Dir(0, 0, 1));
    }
  }

  // 创建后段裁切体
  TopoDS_Shape backCut;
  if (splitDistances[1] < totalLength) {
    TopoDS_Wire backWire = clip_wire_between_distances_helper(
        pathWire, splitDistances[1], totalLength);

    if (!backWire.IsNull()) {
      // 使用最大圆形截面创建裁切体
      backCut = create_simple_pipe(
          maxProfile, backWire, params.upDir ? *params.upDir : gp_Dir(0, 0, 1));
    }
  }

  // 执行裁切操作
  TopoDS_Shape result = fullPipe;
  if (!frontCut.IsNull()) {
    result = BRepAlgoAPI_Cut(result, frontCut).Shape();
  }
  if (!backCut.IsNull()) {
    result = BRepAlgoAPI_Cut(result, backCut).Shape();
  }

  return result;
}


TopoDS_Wire create_pipe_centerline(const pipe_params &params) {
  return make_wire_from_segments({params.wire}, {{params.segment_type}});
}


TopoDS_Shape create_pipe(const pipe_params &params, const gp_Pnt &position,
                         const gp_Dir &direction, const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的管道
  TopoDS_Shape pipe = create_pipe(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(pipe, transformation);
  return transform.Shape();
}


// 新增辅助函数：创建两个截面之间的过渡面
TopoDS_Shape
create_pipe_transition(const shape_profile &profile1, const gp_Dir &normal1,
                       const shape_profile &profile2, const gp_Dir &normal2,
                       const gp_Pnt &position, const gp_Dir &upDir) {
  // 计算两个法向量的夹角
  double angle = normal1.Angle(normal2);
  if (angle < Precision::Angular()) {
    return TopoDS_Shape(); // 角度太小不需要过渡
  }

  auto pair1 = compute_profile_radius_and_center(profile1);
  double radius1 = pair1.first;

  auto pair2 = compute_profile_radius_and_center(profile2);
  double radius2 = pair2.first;
  double maxRadius1 = radius1 * 5;
    double maxRadius2 = radius1 * 10;

  gp_Dir tan1Dir = gp_Vec(normal1).Normalized();
  gp_Dir ref1Dir = gp_Vec(upDir.Crossed(tan1Dir)).Normalized();

  // 如果参考方向长度接近0(切线几乎与径向平行)，使用全局Y轴作为备用
  if (gp_Vec(ref1Dir).SquareMagnitude() < Precision::SquareConfusion()) {
    ref1Dir = gp::DY();
  }

  gp_Dir tan2Dir = gp_Vec(normal2).Normalized();
  gp_Dir ref2Dir = gp_Vec(upDir.Crossed(tan2Dir)).Normalized();

  // 如果参考方向长度接近0(切线几乎与径向平行)，使用全局Y轴作为备用
  if (gp_Vec(ref2Dir).SquareMagnitude() < Precision::SquareConfusion()) {
    ref2Dir = gp::DY();
  }

  // 创建两个截面的局部坐标系
  gp_Ax2 ax1(position, tan1Dir, ref1Dir);
  gp_Ax2 ax2(position, tan2Dir, ref2Dir);

  TopoDS_Shape shape1 = create_shape_from_profile(profile1, false, &ax1);
  TopoDS_Shape shape2 = create_shape_from_profile(profile2, false, &ax2);

  TopoDS_Shape part1;
  {
    gp_Pnt position1 =
        position.Translated((gp_Vec(normal1).Normalized() * maxRadius1).XYZ());
      gp_Pnt position2 =
          position.Translated((gp_Vec(normal1.Reversed()).Normalized() * maxRadius1).XYZ());
    BRepBuilderAPI_MakeWire wireMaker;
      
    wireMaker.Add(BRepBuilderAPI_MakeEdge(position, position1));

    TopoDS_Wire wire = wireMaker.Wire();

    BRepOffsetAPI_MakePipeShell pipeMaker(wire);
    pipeMaker.Add(shape1);

    pipeMaker.Build();

    if (!pipeMaker.IsDone()) {
      throw Standard_ConstructionError("Failed to create pipe");
    }

    if (!pipeMaker.MakeSolid()) {
      throw Standard_ConstructionError("Failed to make pipe solid");
    }

    part1 = pipeMaker.Shape();
      
      
      std::string debugFileName = "./debug_part1_segment.stl";
      
      // 对形状进行网格化（三角剖分）
      BRepMesh_IncrementalMesh mesher(part1,  0.5, false, 0.3);
      mesher.Perform();
      
      StlAPI_Writer stlWriter;
      stlWriter.Write(part1, debugFileName.c_str());
      
  }

  TopoDS_Shape part2;
  {

    gp_Pnt position2 = position.Translated(
        (gp_Vec(normal2.Reversed()).Normalized() * maxRadius2).XYZ());
    BRepBuilderAPI_MakeWire wireMaker;
    wireMaker.Add(BRepBuilderAPI_MakeEdge(position, position2));

    TopoDS_Wire wire = wireMaker.Wire();

    BRepOffsetAPI_MakePipeShell pipeMaker(wire);
    pipeMaker.Add(shape2);

    pipeMaker.Build();

    if (!pipeMaker.IsDone()) {
      throw Standard_ConstructionError("Failed to create pipe");
    }

    if (!pipeMaker.MakeSolid()) {
      throw Standard_ConstructionError("Failed to make pipe solid");
    }

    part2 = pipeMaker.Shape();
      
      
      
      std::string debugFileName = "./debug_part2_segment.stl";
      
      // 对形状进行网格化（三角剖分）
      BRepMesh_IncrementalMesh mesher(part2,  0.5, false, 0.3);
      mesher.Perform();
      
      StlAPI_Writer stlWriter;
      stlWriter.Write(part2, debugFileName.c_str());
  }
    
    

  return BRepAlgoAPI_Common(part1, part2).Shape();
}


std::vector<gp_Pnt>
sample_segment_points(const std::vector<std::vector<gp_Pnt>> &wires,
                      std::vector<segment_type> segments, double tessellation) {
  // 创建线框
  TopoDS_Wire wire = make_wire_from_segments(wires, segments);

  // 计算线框长度和复杂度
  GProp_GProps props;
  BRepGProp::LinearProperties(wire, props);
  double wireLength = props.Mass();

  // 自动计算采样数
  if (tessellation <= 0) {
    int edgeCount = 0;
    int curveCount = 0;
    double totalCurvature = 0.0;

    // 分析线框中的边类型
    for (TopExp_Explorer explorer(wire, TopAbs_EDGE); explorer.More();
         explorer.Next()) {
      const TopoDS_Edge &edge = TopoDS::Edge(explorer.Current());
      BRepAdaptor_Curve curve(edge);

      edgeCount++;
      if (curve.GetType() != GeomAbs_Line) {
        curveCount++;
        // 估算曲率变化
        double edgeLength = GCPnts_AbscissaPoint::Length(curve);
        totalCurvature += edgeLength * 2; // 曲线权重加倍
      }
    }

    // 基础采样数 + 曲线额外采样 + 长度比例采样
    tessellation = 8 + curveCount * 3 + static_cast<int>(wireLength * 10);

    // 如果总曲率较大，增加采样点
    if (totalCurvature > wireLength * 1.5) {
      tessellation += static_cast<int>(totalCurvature / wireLength * 5);
    }
  }

  std::vector<gp_Pnt> points;

  // 遍历所有边进行采样
  for (TopExp_Explorer explorer(wire, TopAbs_EDGE); explorer.More();
       explorer.Next()) {
    const TopoDS_Edge &edge = TopoDS::Edge(explorer.Current());

    BRepAdaptor_Curve curve(edge);
    double first = curve.FirstParameter();
    double last = curve.LastParameter();

    // 根据曲线类型调整采样密度
    if (curve.GetType() == GeomAbs_Line) {
      // 直线只需首尾点
      points.push_back(curve.Value(first));
      points.push_back(curve.Value(last));
    } else {
      // 曲线增加采样点
      int edgeTessellation = static_cast<int>(
          tessellation * (GCPnts_AbscissaPoint::Length(curve) / wireLength));
      edgeTessellation = std::max(3, edgeTessellation); // 每条曲线至少3个点

      double step = (last - first) / edgeTessellation;
      for (int i = 0; i <= edgeTessellation; i++) {
        double param = first + i * step;
        points.push_back(curve.Value(param));
      }
    }
  }

  // 去除连续重复点
  auto last = std::unique(points.begin(), points.end(),
                          [](const gp_Pnt &a, const gp_Pnt &b) {
                            return a.Distance(b) < Precision::Confusion();
                          });
  points.erase(last, points.end());

  return points;
}


TopoDS_Shape
create_multi_segment_pipe(const multi_segment_pipe_params &params) {
  // 参数验证
  if (params.wires.empty()) {
    throw Standard_ConstructionError("Wire paths cannot be empty");
  }
  if (params.profiles.size() != params.wires.size() &&
      params.profiles.size() != params.wires.size() + 1 &&
      params.profiles.size() != 1) {
    throw Standard_ConstructionError("Profile count must match wire count");
  }
  if (params.inner_profiles &&
      (params.inner_profiles->size() != params.profiles.size())) {
    throw Standard_ConstructionError(
        "Inner profile count must match wire count");
  }

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);
  std::vector<TopoDS_Shape> transitions;

  // 保存上一段的末端截面信息
  shape_profile prev_profile;
  boost::optional<shape_profile> prev_inner_profile;
  gp_Dir prev_normal;
  bool has_prev = false;

  // 逐个创建每段管道
  for (size_t i = 0; i < params.wires.size(); i++) {
    // 创建当前段的管道参数
    pipe_params seg_params;
    seg_params.upDir = params.upDir;
    seg_params.segment_type =
        params.segment_types ? (*params.segment_types)[i] : segment_type::LINE;
    seg_params.wire = params.wires[i];
    seg_params.transition_mode = params.transition_mode;
    if (params.profiles.size() == 1) {
      // 单剖面保持 1 个: 直线段走棱柱短路, 弧段 PipeShell 单截面本就支持
      seg_params.profiles = {params.profiles[0]};
    } else {
      int nextId = i + 1;
      if (nextId == params.profiles.size()) {
        nextId = i;
      }
      seg_params.profiles = {params.profiles[i], params.profiles[nextId]};
    }

    // 如果有内轮廓，设置内轮廓
    if (params.inner_profiles) {
      if (params.inner_profiles->size() == 1) {
        seg_params.inner_profiles = std::vector<shape_profile>{(*params.inner_profiles)[0]};
      } else {
        int nextId = i + 1;
        if (nextId == params.inner_profiles->size()) {
          nextId = i;
        }
        seg_params.inner_profiles = {
            {(*params.inner_profiles)[i], (*params.inner_profiles)[nextId]}};
      }
    }

    // 创建当前段管道
    auto pair = create_pipe_helper(seg_params);
    TopoDS_Shape segment = std::get<0>(pair);
    gp_Dir start_normal = std::get<2>(pair).first;
    gp_Dir end_normal = std::get<2>(pair).second;

    // 添加到结果中
    builder.Add(result, segment);

    // 如果有上一段，创建过渡面
    if (has_prev) {
      const auto &wire = params.wires[i - 1];
      TopoDS_Shape transition = create_pipe_transition(
          prev_profile, prev_normal, seg_params.profiles[0], start_normal,
          wire.back(), params.upDir ? *params.upDir : gp_Dir(0, 0, 1));

      if (prev_inner_profile) {
        TopoDS_Shape inner_transition = create_pipe_transition(
            prev_inner_profile.get(), prev_normal,
            seg_params.inner_profiles.get()[0], start_normal, wire.back(),
            params.upDir ? *params.upDir : gp_Dir(0, 0, 1));
        transition = BRepAlgoAPI_Cut(transition, inner_transition).Shape();
      }
      if (!transition.IsNull()) {
        transitions.push_back(transition);
      }
    }

    // 保存当前段信息供下一段使用
    // (单剖面时只有 [0], 不得越界取 [1])
    prev_profile = seg_params.profiles.back();
    if (seg_params.inner_profiles &&
        !seg_params.inner_profiles->empty()) {
      prev_inner_profile = seg_params.inner_profiles->back();
    }
    prev_normal = end_normal;
    has_prev = true;
  }

  for (size_t i = 0; i < transitions.size(); i++) {
    builder.Add(result, transitions[i]);
  }
  return result;
}


TopoDS_Shape create_multi_segment_pipe(const multi_segment_pipe_params &params,
                                       const gp_Pnt &position,
                                       const gp_Dir &direction,
                                       const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的管道
  TopoDS_Shape pipe = create_multi_segment_pipe(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(pipe, transformation);
  return transform.Shape();
}


TopoDS_Wire
create_multi_segment_pipe_centerline(const multi_segment_pipe_params &params) {
  return make_wire_from_segments(params.wires, params.segment_types);
}


TopoDS_Shape create_multi_segment_pipe_with_split_distances(
    const multi_segment_pipe_params &params,
    std::array<double, 2> splitDistances) {
  // 参数验证
  // NaN/Inf 区间会穿透所有比较校验, 产出不可复现的垃圾几何, 必须先拒绝
  if (splitDistances[0] != splitDistances[0] ||
      splitDistances[1] != splitDistances[1] ||
      splitDistances[0] < 0) {
    throw Standard_ConstructionError(
        "Split distances must be finite and start >= 0");
  }

  // 获取路径线框
  TopoDS_Wire pathWire =
      make_wire_from_segments(params.wires, params.segment_types);

  // 计算路径总长度
  GProp_GProps lengthProps;
  BRepGProp::LinearProperties(pathWire, lengthProps);
  double totalLength = lengthProps.Mass();
  if (totalLength != totalLength || totalLength <= 0.0) {
    throw Standard_ConstructionError(
        "Pipe path has invalid (zero or NaN) length");
  }

  // 处理第二个分割距离 (end<0 视为全长哨兵; 越界钳制到全长)
  if (splitDistances[1] < 0 || splitDistances[1] > totalLength) {
    splitDistances[1] = totalLength;
  }
  if (splitDistances[1] <= splitDistances[0]) {
    // 含 start==end==0 等退化区间: 确定性拒绝
    throw Standard_ConstructionError("Invalid split interval (end <= start)");
  }

  // 如果不需要分割，直接返回完整管道
  if (splitDistances[0] == 0 && splitDistances[1] >= totalLength) {
    return create_multi_segment_pipe(params);
  }

  // 计算管道最大半径
  double maxRadius = 0;
  for (const auto &profile : params.profiles) {
    auto [radius, _] = compute_profile_radius_and_center(profile);
    maxRadius = std::max(maxRadius, radius);
  }
  if (params.inner_profiles) {
    for (const auto &profile : *params.inner_profiles) {
      auto [radius, _] = compute_profile_radius_and_center(profile);
      maxRadius = std::max(maxRadius, radius);
    }
  }

  // 创建圆形截面
  circ_profile maxProfile;
  maxProfile.radius = maxRadius * 3.5; // 增加50%余量确保完全包裹
  maxProfile.center = gp_Pnt(0, 0, 0);
  maxProfile.norm = gp_Dir(0, 0, 1);

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  double accumulatedLength = 0;
  shape_profile prev_profile;
  boost::optional<shape_profile> prev_inner_profile;
  std::vector<TopoDS_Shape> transitions;

  gp_Dir prev_normal;
  bool has_prev = false;

  for (size_t i = 0; i < params.wires.size(); i++) {
    // 创建当前段的路径线框
    TopoDS_Wire currentWire = make_wire_from_segments(
        {params.wires[i]},
        params.segment_types
            ? boost::optional<std::vector<segment_type>>(
                  std::vector<segment_type>{(*params.segment_types)[i]})
            : boost::none);

    // 计算当前段长度
    GProp_GProps lengthProps;
    BRepGProp::LinearProperties(currentWire, lengthProps);
    double segmentLength = lengthProps.Mass();

    // 计算当前段的起始和结束距离
    double segmentStart = accumulatedLength;
    double segmentEnd = accumulatedLength + segmentLength;

    // 判断当前段是否需要裁切
    bool noCut =
        (splitDistances[0] <= segmentStart && splitDistances[1] >= segmentEnd);
    bool needFrontCut =
        (splitDistances[0] > segmentStart && splitDistances[0] < segmentEnd);
    bool needBackCut =
        (splitDistances[1] > segmentStart && splitDistances[1] < segmentEnd);

    bool needTrans = splitDistances[0] == segmentEnd;
    TopoDS_Shape segment;
    if (noCut || needFrontCut || needBackCut || needTrans) {
      pipe_params seg_params;
      seg_params.upDir = params.upDir;
      seg_params.segment_type = params.segment_types
                                    ? (*params.segment_types)[i]
                                    : segment_type::LINE;
      seg_params.wire = params.wires[i];
      seg_params.transition_mode = params.transition_mode;

      if (params.profiles.size() == 1) {
        seg_params.profiles = {params.profiles[0], params.profiles[0]};
      } else {
        size_t nextId = i + 1;
        if (nextId == params.profiles.size()) {
          nextId = i;
        }
        seg_params.profiles = {params.profiles[i], params.profiles[nextId]};
      }

      // 如果有内轮廓，设置内轮廓
      if (params.inner_profiles) {
        if (params.inner_profiles->size() == 1) {
          seg_params.inner_profiles = {
              {(*params.inner_profiles)[0], (*params.inner_profiles)[0]}};
        } else {
          size_t nextId = i + 1;
          if (nextId == params.inner_profiles->size()) {
            nextId = i;
          }
          seg_params.inner_profiles = {
              {(*params.inner_profiles)[i], (*params.inner_profiles)[nextId]}};
        }
      }

      // 创建当前段管道
      auto pair = create_pipe_helper(seg_params);
      segment = std::get<0>(pair);
      gp_Dir start_normal = std::get<2>(pair).first;
      gp_Dir end_normal = std::get<2>(pair).second;

      if (has_prev) {
        bool needTransition = false;
        if (noCut || needBackCut || needFrontCut) {
          needTransition = true;
        }
        if (needTransition) {
          const auto &wire = params.wires[i - 1];
          TopoDS_Shape transition = create_pipe_transition(
              prev_profile, prev_normal, seg_params.profiles[0], start_normal,
              wire.back(), params.upDir ? *params.upDir : gp_Dir(0, 0, 1));
          if (prev_inner_profile) {
            TopoDS_Shape inner_transition = create_pipe_transition(
                prev_inner_profile.value(), prev_normal,
                seg_params.inner_profiles.get()[0], start_normal, wire.back(),
                params.upDir ? *params.upDir : gp_Dir(0, 0, 1));
            transition = BRepAlgoAPI_Cut(transition, inner_transition).Shape();
          }
            if (!transition.IsNull()) {
                auto tr = BRepAlgoAPI_Fuse(segment, transition).Shape();
                BRepCheck_Analyzer aChecker(transition);
                if (aChecker.IsValid()) {
                    transitions.push_back(transition);
                }
            }
        }
      }

      // 保存当前段信息供下一段使用
      prev_profile = seg_params.profiles[1];
      if (seg_params.inner_profiles) {
        prev_inner_profile = seg_params.inner_profiles.get()[1];
      }
      prev_normal = end_normal;
      has_prev = true;
    }

    if (!segment.IsNull() && (needFrontCut || needBackCut)) {
      const double EPSILON = 1e-3;
      TopoDS_Shape cutterFront;
      TopoDS_Shape cutterBack;
      if (needFrontCut) {
        // 仅前部裁切
        auto dist = splitDistances[0] - segmentStart;
        if (dist > EPSILON) {
          TopoDS_Wire frontWire = clip_wire_between_distances_helper(
              currentWire, 0, splitDistances[0] - segmentStart);
          cutterFront = create_simple_pipe(maxProfile, frontWire,
                                           params.upDir ? *params.upDir
                                                        : gp_Dir(0, 0, 1));
        }
      }
      if (needBackCut) {
        auto dist = segmentLength - (splitDistances[1] - segmentStart);
        if (dist > EPSILON) {
          // 仅后部裁切
          TopoDS_Wire backWire = clip_wire_between_distances_helper(
              currentWire, splitDistances[1] - segmentStart, segmentLength);
          cutterBack = create_simple_pipe(maxProfile, backWire,
                                          params.upDir ? *params.upDir
                                                       : gp_Dir(0, 0, 1));
        }
      }

      if (!cutterFront.IsNull()) {
        segment = BRepAlgoAPI_Cut(segment, cutterFront).Shape();
      }

      if (!cutterBack.IsNull()) {
        segment = BRepAlgoAPI_Cut(segment, cutterBack).Shape();
      }
    }

    if (!segment.IsNull() && !needTrans) {
      builder.Add(result, segment);
    }

    accumulatedLength += segmentLength;
  }

  for (size_t i = 0; i < transitions.size(); i++) {
    builder.Add(result, transitions[i]);
  }

  return result;
}


std::map<std::string, TopoDS_Shape> create_multi_layer_extrusion_structure(
    const multi_layer_extrusion_structure_params &params) {
  // 参数验证
  if (params.wires.empty()) {
    throw Standard_ConstructionError("Wire paths cannot be empty");
  }

  std::map<std::string, TopoDS_Shape> results;

  for (size_t i = 0; i < params.layers.size(); i++) {
    auto layer = params.layers[i];
    if (layer.profiles.size() != params.wires.size() &&
        layer.profiles.size() != params.wires.size() + 1 &&
        layer.profiles.size() != 1) {
      throw Standard_ConstructionError("Profile count must match wire count");
    }
    if (layer.inner_profiles &&
        (layer.inner_profiles->size() != layer.profiles.size())) {
      throw Standard_ConstructionError(
          "Inner profile count must match wire count");
    }

    auto shp =
        create_multi_segment_pipe({.wires = params.wires,
                                   .profiles = layer.profiles,
                                   .inner_profiles = layer.inner_profiles,
                                   .segment_types = params.segment_types,
                                   .transition_mode = params.transition_mode,
                                   .upDir = params.upDir});

    results.emplace(layer.name, shp);
  }

  return results;
}


TopoDS_Wire create_multi_layer_extrusion_structure_centerline(
    const multi_layer_extrusion_structure_params &params) {
  return make_wire_from_segments(params.wires, params.segment_types);
}


std::map<std::string, TopoDS_Shape> create_multi_layer_extrusion_structure(
    const multi_layer_extrusion_structure_params &params,
    const gp_Pnt &position, const gp_Dir &normal, const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 创建标准方向的排管
  std::map<std::string, TopoDS_Shape> extrusionStructure =
      create_multi_layer_extrusion_structure(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  for (auto &pair : extrusionStructure) {
    BRepBuilderAPI_Transform transform(pair.second, transformation);
    extrusionStructure.emplace(pair.first, transform.Shape());
  }

  return extrusionStructure;
}


shape_profile scale_profile(const shape_profile &profile, double scale) {
  struct ProfileVisitor : public boost::static_visitor<shape_profile> {
    double scale;

    ProfileVisitor(double s) : scale(s) {}

    shape_profile operator()(const circ_profile &prof) const {
      circ_profile scaled = prof;
      scaled.radius *= scale;
      return scaled;
    }

    shape_profile operator()(const triangle_profile &prof) const {
      triangle_profile scaled = prof;
      scaled.p1.Scale(gp_Pnt(), scale);
      scaled.p2.Scale(gp_Pnt(), scale);
      scaled.p3.Scale(gp_Pnt(), scale);
      return scaled;
    }

    shape_profile operator()(const rectangle_profile &prof) const {
      rectangle_profile scaled = prof;
      scaled.p1.Scale(gp_Pnt(), scale);
      scaled.p2.Scale(gp_Pnt(), scale);
      return scaled;
    }

    shape_profile operator()(const elips_profile &prof) const {
      elips_profile scaled = prof;
      scaled.s1.Scale(gp_Pnt(), scale);
      scaled.s2.Scale(gp_Pnt(), scale);
      scaled.center.Scale(gp_Pnt(), scale);
      return scaled;
    }

    shape_profile operator()(const polygon_profile &prof) const {
      polygon_profile scaled = prof;
      for (auto &point : scaled.edges) {
        point.Scale(gp_Pnt(), scale);
      }
      for (auto &inner : scaled.inners) {
        for (auto &point : inner) {
          point.Scale(gp_Pnt(), scale);
        }
      }
      return scaled;
    }
  };

  return boost::apply_visitor(ProfileVisitor{scale}, profile);
}


// 辅助函数：创建过渡形状
TopoDS_Shape create_transition_shape(const TopoDS_Shape &profile,
                                     const pipe_endpoint &endpoint,
                                     const gp_Vec &direction, double scale) {
  // 计算过渡向量
  double length = direction.Magnitude();
  gp_Vec transition_vec = direction.Normalized() * (length * 0.98);

  // 创建放样生成器
  BRepOffsetAPI_ThruSections generator(true, true);

  // 添加原始剖面
  generator.AddWire(TopoDS::Wire(profile));

  // 创建缩放后的剖面
  shape_profile smaller_profile = scale_profile(endpoint.profile, scale);
  gp_Pnt mid_point = endpoint.offset.Translated(transition_vec);
  gp_Ax2 midAxis(mid_point, direction);
  TopoDS_Shape smaller_shape =
      create_shape_from_profile(smaller_profile, false, &midAxis);
  generator.AddWire(TopoDS::Wire(smaller_shape));

  return generator.Shape();
}


std::pair<TopoDS_Shape, TopoDS_Shape>
create_pipe_connection(const pipe_endpoint &endpoint,
                       const gp_Pnt &joint_center, const gp_Ax3 &joint_coord,
                       bool is_output, double scale) {
  // Calculate direction vector from joint to pipe endpoint
  gp_Vec direction(endpoint.offset, joint_center);

  // Create coordinate system for the pipe
  gp_Ax2 pipe_axis;
  if (endpoint.normal.IsParallel(gp::DX(), Precision::Angular())) {
    // 如果法线平行于X轴，使用Y轴作为参考方向
    pipe_axis = gp_Ax2(endpoint.offset, endpoint.normal, gp::DY());
  } else if (endpoint.normal.IsParallel(gp::DY(), Precision::Angular())) {
    // 如果法线平行于Y轴，使用Z轴作为参考方向
    pipe_axis = gp_Ax2(endpoint.offset, endpoint.normal, gp::DZ());
  } else {
    // 默认情况，使用X轴作为参考方向
    pipe_axis = gp_Ax2(endpoint.offset, endpoint.normal, gp::DX());
  }

  if (endpoint.normal.IsParallel(direction, Precision::Angular())) {
    // Adjust axis if normal is parallel to direction
    gp_Vec ortho = endpoint.normal.Crossed(pipe_axis.XDirection());
    if (ortho.Magnitude() < Precision::Confusion()) {
      ortho = endpoint.normal.Crossed(pipe_axis.YDirection());
    }
    pipe_axis = gp_Ax2(endpoint.offset, endpoint.normal, ortho);
  }

  // 创建外径管道形状
  TopoDS_Shape outer_profile =
      create_shape_from_profile(endpoint.profile, false, &pipe_axis);

  // 创建过渡形状
  TopoDS_Shape outer_transition =
      create_transition_shape(outer_profile, endpoint, direction, scale);

  TopoDS_Shape cut_shape;

  // 如果有内径，创建内径管道并做布尔减
  if (endpoint.inner_profile) {
    // 创建内径管道形状
    TopoDS_Shape inner_profile =
        create_shape_from_profile(*endpoint.inner_profile, false, &pipe_axis);

    // 创建内径过渡形状
    TopoDS_Shape inner_transition =
        create_transition_shape(inner_profile, endpoint, direction, scale);

    cut_shape = inner_transition;

    // 从外径中减去内径
    outer_transition =
        BRepAlgoAPI_Cut(outer_transition, inner_transition).Shape();
  }

  return {outer_transition, cut_shape};
}


TopoDS_Shape create_pipe_joint(const pipe_joint_params &params) {
  double max_radius = 0;
  gp_XYZ center_sum(0, 0, 0);
  int center_count = 0;

  std::vector<double> inscales;

  // Process input pipes
  for (const auto &in : params.ins) {
    auto [radius, center] = compute_profile_radius_and_center(in.profile);
    max_radius = std::max(max_radius, radius);
    center_sum += gp_XYZ(center.X(), center.Y(), center.Z());
    center_count++;
    inscales.push_back(radius);
  }

  for (size_t i = 0; i < inscales.size(); i++) {
    inscales[i] = max_radius / inscales[i];
  }

  std::vector<double> outscales;

  // Process output pipes
  for (const auto &out : params.outs) {
    auto [radius, center] = compute_profile_radius_and_center(out.profile);
    max_radius = std::max(max_radius, radius);
    center_sum += gp_XYZ(center.X(), center.Y(), center.Z());
    center_count++;
    outscales.push_back(radius);
  }

  for (size_t i = 0; i < outscales.size(); i++) {
    outscales[i] = max_radius / outscales[i];
  }

  // Calculate average center point
  gp_Pnt joint_center = gp_Pnt(0, 0, 0);
  if (center_count > 0) {
    joint_center.ChangeCoord() += center_sum / center_count;
  }

  // Create coordinate system for the joint
  gp_Ax2 joint_coord(joint_center, gp::DZ(), gp::DX());

  // Create center shape (sphere or box)
  TopoDS_Shape center_shape;
  std::vector<TopoDS_Shape> cutShapes;

  if (params.mode == joint_shape_mode::SPHERE) {
    // 创建外球体
    center_shape =
        BRepPrimAPI_MakeSphere(joint_coord, max_radius * 1.04).Shape();
    // 创建内球体 (厚度为半径的20%)
    TopoDS_Shape inner_sphere =
        BRepPrimAPI_MakeSphere(joint_coord, max_radius * 0.84).Shape();
    cutShapes.push_back(inner_sphere);
  } else if (params.mode == joint_shape_mode::CYLINDER) {
    double size = max_radius * 1.04;      // 外盒尺寸
    double height = size * 2;             // 外盒高度
    double inner_size = size * 0.84;      // 内盒尺寸
    double inner_height = inner_size * 2; // 内盒高度

    // 创建外圆柱
    center_shape =
        BRepPrimAPI_MakeCylinder(
            joint_coord.Translated(gp_Vec(0, 0, -height / 2)), size, height)
            .Shape();
    // 创建内圆柱 (厚度为半径的20%)
    TopoDS_Shape inner_cylinder =
        BRepPrimAPI_MakeCylinder(
            joint_coord.Translated(gp_Vec(0, 0, -inner_height / 2)), inner_size,
            inner_height)
            .Shape();
    cutShapes.push_back(inner_cylinder);
  } else {                           // BOX
    double size = max_radius * 2.04; // 外盒尺寸
    double inner_size = size * 0.84; // 内盒尺寸 (厚度为外盒的20%)

    // 创建内盒
    TopoDS_Shape inner_box =
        BRepPrimAPI_MakeBox(
            joint_coord.Translated(
                gp_Vec(-inner_size / 2, -inner_size / 2, -inner_size / 2)),
            inner_size, inner_size, inner_size)
            .Shape();
    {
      // 添加圆角
      BRepFilletAPI_MakeFillet filletMaker(inner_box);
      TopExp_Explorer explorer(inner_box, TopAbs_EDGE);
      double filletRadius = max_radius * 0.5;

      while (explorer.More()) {
        TopoDS_Edge edge = TopoDS::Edge(explorer.Current());
        filletMaker.Add(filletRadius, edge);
        explorer.Next();
      }

      filletMaker.Build();

      if (filletMaker.IsDone()) {
        inner_box = filletMaker.Shape();
      }
    }
    cutShapes.push_back(inner_box);

    // 从外盒中减去内盒
    TopoDS_Shape outer_shape =
        BRepPrimAPI_MakeBox(
            joint_coord.Translated(gp_Vec(-size / 2, -size / 2, -size / 2)),
            size, size, size)
            .Shape();

    // 添加圆角
    {
      BRepFilletAPI_MakeFillet filletMaker2(outer_shape);
      TopExp_Explorer explorer2(outer_shape, TopAbs_EDGE);
      double filletRadius = max_radius * 0.5;

      while (explorer2.More()) {
        TopoDS_Edge edge = TopoDS::Edge(explorer2.Current());
        filletMaker2.Add(filletRadius, edge);
        explorer2.Next();
      }

      filletMaker2.Build();

      if (filletMaker2.IsDone()) {
        center_shape = filletMaker2.Shape();
      }
    }
  }

  // Create and connect all pipes to the center
  TopoDS_Shape result = center_shape;

  for (size_t i = 0; i < params.ins.size(); i++) {
    auto pair = create_pipe_connection(params.ins[i], joint_center, joint_coord,
                                       false, inscales[i]);
    TopoDS_Shape pipe = pair.first;
    cutShapes.push_back(pair.second);
    result = BRepAlgoAPI_Fuse(result, pipe).Shape();
  }
  for (size_t i = 0; i < params.outs.size(); i++) {
    auto pair = create_pipe_connection(params.outs[i], joint_center,
                                       joint_coord, true, outscales[i]);
    TopoDS_Shape pipe = pair.first;
    cutShapes.push_back(pair.second);
    result = BRepAlgoAPI_Fuse(result, pipe).Shape();
  }

  for (const auto &cutShape : cutShapes) {
    if (cutShape.IsNull()) {
      continue;
    }
    result = BRepAlgoAPI_Cut(result, cutShape).Shape();
  }

  return result;
}


TopoDS_Shape create_pipe_joint(const pipe_joint_params &params,
                               const gp_Pnt &position, const gp_Dir &direction,
                               const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的管道连接件
  TopoDS_Shape joint = create_pipe_joint(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(joint, transformation);
  return transform.Shape();
}


TopoDS_Shape create_box_shape(const box_shape_params &params) {
  // 创建长方体
  BRepPrimAPI_MakeBox boxMaker(params.point1, params.point2);
  return boxMaker.Shape();
}


TopoDS_Shape create_box_shape(const box_shape_params &params,
                              const gp_Pnt &position, const gp_Dir &direction,
                              const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的长方体
  TopoDS_Shape box = create_box_shape(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(box, transformation);
  return transform.Shape();
}


TopoDS_Shape create_cone_shape(const cone_shape_params &params) {
  // 创建圆锥或圆台
  gp_Ax2 axis(gp::Origin(), gp::DZ());
  if (params.angle) {
    BRepPrimAPI_MakeCone coneMaker(axis, params.radius1, params.radius2,
                                   params.height, *params.angle);
    return coneMaker.Shape();
  } else {
    BRepPrimAPI_MakeCone coneMaker(axis, params.radius1, params.radius2,
                                   params.height);
    return coneMaker.Shape();
  }
}


TopoDS_Shape create_cone_shape(const cone_shape_params &params,
                               const gp_Pnt &position, const gp_Dir &direction,
                               const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的圆锥
  TopoDS_Shape cone = create_cone_shape(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(cone, transformation);
  return transform.Shape();
}


TopoDS_Shape create_cylinder_shape(const cylinder_shape_params &params) {
  // 创建圆柱或圆柱段
  gp_Ax2 axis(gp::Origin(), gp::DZ());
  if (params.angle) {
    BRepPrimAPI_MakeCylinder cylMaker(axis, params.radius, params.height,
                                      *params.angle);
    return cylMaker.Shape();
  } else {
    BRepPrimAPI_MakeCylinder cylMaker(axis, params.radius, params.height);
    return cylMaker.Shape();
  }
}


TopoDS_Shape create_cylinder_shape(const cylinder_shape_params &params,
                                   const gp_Pnt &position,
                                   const gp_Dir &direction,
                                   const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的圆柱
  TopoDS_Shape cylinder = create_cylinder_shape(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(cylinder, transformation);
  return transform.Shape();
}


TopoDS_Shape create_revolution_shape(const revolution_shape_params &params) {
  // 创建旋转体
  if (params.meridian.empty()) {
    throw Standard_ConstructionError("Meridian points are empty");
  }

  if (params.meridian.size() == 1) {
    throw Standard_ConstructionError("Meridian points must be at least two");
  }

  // 创建旋转曲线
  Handle(Geom_Curve) curve;

  // 创建样条曲线
  Handle(TColgp_HArray1OfPnt) points =
      new TColgp_HArray1OfPnt(1, params.meridian.size());
  for (int i = 0; i < params.meridian.size(); ++i) {
    points->SetValue(i + 1,
                     gp_Pnt(params.meridian[i].X(), params.meridian[i].Z(),
                            params.meridian[i].Y()));
  }

  GeomAPI_Interpolate interpolate(points, false, Precision::Confusion());
  interpolate.Perform();
  if (!interpolate.IsDone()) {
    throw Standard_ConstructionError("Failed to create meridian curve");
  }
  curve = interpolate.Curve();

  // 创建旋转轴
  gp_Vec normal(0, 0, 0);
  for (size_t i = 0; i < params.meridian.size() - 1; ++i) {
    gp_Vec v1(params.meridian[i], params.meridian[i + 1]);
    if (i < params.meridian.size() - 2) {
      gp_Vec v2(params.meridian[i + 1], params.meridian[i + 2]);
      normal += v1.Crossed(v2);
    }
  }

  // 如果法向长度过小，使用默认Z轴
  gp_Dir axisDir =
      normal.Magnitude() < Precision::Confusion() ? gp::DZ() : gp_Dir(normal);

  // 创建旋转轴(使用点集第一个点作为轴位置)
  gp_Ax2 axis(params.meridian.front(), axisDir);

  // 创建旋转体
  double angle = params.angle ? *params.angle : 2 * M_PI;

  if (params.max && params.min) {
    // 使用VMin和VMax版本
    BRepPrimAPI_MakeRevolution revMaker(axis, curve, *params.min, *params.max,
                                        angle);
    return revMaker.Shape();
  } else if (params.max) {
    // 使用VMax版本
    BRepPrimAPI_MakeRevolution revMaker(axis, curve, 0, *params.max, angle);
    return revMaker.Shape();
  } else {
    // 基本版本
    BRepPrimAPI_MakeRevolution revMaker(axis, curve, angle);
    return revMaker.Shape();
  }
}


TopoDS_Shape create_revolution_shape(const revolution_shape_params &params,
                                     const gp_Pnt &position,
                                     const gp_Dir &direction,
                                     const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的旋转体
  TopoDS_Shape rev = create_revolution_shape(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(rev, transformation);
  return transform.Shape();
}


TopoDS_Shape create_sphere_shape(const sphere_shape_params &params) {
  // 创建球体或球面段
  gp_Pnt center = params.center ? *params.center : gp::Origin();
  gp_Ax2 axis(center, gp::DZ());

  if (params.angle1 && params.angle2 && params.angle) {
    BRepPrimAPI_MakeSphere sphereMaker(axis, params.radius, *params.angle1,
                                       *params.angle2, *params.angle);
    return sphereMaker.Shape();
  } else if (params.angle1 && params.angle2) {
    BRepPrimAPI_MakeSphere sphereMaker(axis, params.radius, *params.angle1,
                                       *params.angle2);
    return sphereMaker.Shape();
  } else if (params.angle) {
    BRepPrimAPI_MakeSphere sphereMaker(axis, params.radius, *params.angle);
    return sphereMaker.Shape();
  } else {
    BRepPrimAPI_MakeSphere sphereMaker(axis, params.radius);
    return sphereMaker.Shape();
  }
}


TopoDS_Shape create_sphere_shape(const sphere_shape_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction, const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的球体
  TopoDS_Shape sphere = create_sphere_shape(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(sphere, transformation);
  return transform.Shape();
}


TopoDS_Shape create_torus_shape(const torus_shape_params &params) {
  // 创建圆环或圆环段
  gp_Ax2 axis(gp::Origin(), gp::DZ());

  if (params.angle1 && params.angle2 && params.angle) {
    BRepPrimAPI_MakeTorus torusMaker(axis, params.radius1, params.radius2,
                                     *params.angle1, *params.angle2,
                                     *params.angle);
    return torusMaker.Shape();
  } else if (params.angle1 && params.angle2) {
    BRepPrimAPI_MakeTorus torusMaker(axis, params.radius1, params.radius2,
                                     *params.angle1, *params.angle2);
    return torusMaker.Shape();
  } else if (params.angle) {
    BRepPrimAPI_MakeTorus torusMaker(axis, params.radius1, params.radius2,
                                     *params.angle);
    return torusMaker.Shape();
  } else {
    BRepPrimAPI_MakeTorus torusMaker(axis, params.radius1, params.radius2);
    return torusMaker.Shape();
  }
}


TopoDS_Shape create_torus_shape(const torus_shape_params &params,
                                const gp_Pnt &position, const gp_Dir &direction,
                                const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的圆环体
  TopoDS_Shape torus = create_torus_shape(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(torus, transformation);
  return transform.Shape();
}


TopoDS_Shape create_wedge_shape(const wedge_shape_params &params) {
  // 创建楔形体
  gp_Ax2 axis(gp_Pnt(-params.edge.X() / 2, 0, -params.edge.Z() / 2), gp::DZ());

  TopoDS_Shape wedgeShape;
  if (params.limit) {
    const auto &limit = *params.limit;
    BRepPrimAPI_MakeWedge wedgeMaker(axis, params.edge.X(), params.edge.Y(),
                                     params.edge.Z(),    // dx, dy, dz
                                     limit[0], limit[1], // xmin, zmin
                                     limit[2], limit[3]  // xmax, zmax
    );
    wedgeShape = wedgeMaker.Shape();
  } else {
    double ltx = params.edge.X() / 2.0;
    if (params.ltx) {
      ltx = *params.ltx;
    }
    BRepPrimAPI_MakeWedge wedgeMaker(axis, params.edge.X(), params.edge.Y(),
                                     params.edge.Z(), // dx, dy, dz
                                     ltx);            // ltx
    wedgeShape = wedgeMaker.Shape();
  }
  gp_Trsf rotation;
  rotation.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0)), M_PI / 2);
  return BRepBuilderAPI_Transform(wedgeShape, rotation).Shape();
}


TopoDS_Shape create_wedge_shape(const wedge_shape_params &params,
                                const gp_Pnt &position, const gp_Dir &direction,
                                const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的楔形体
  TopoDS_Shape wedge = create_wedge_shape(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(wedge, transformation);
  return transform.Shape();
}


TopoDS_Shape create_pipe_shape(const pipe_shape_params &params) {
  // 参数验证
  if (params.wire.size() != 2) {
    throw Standard_ConstructionError("Pipe wire must have 2 points");
  }

  // 创建路径线框
  TopoDS_Edge edge =
      BRepBuilderAPI_MakeEdge(params.wire[0], params.wire[1]).Edge();
  BRepBuilderAPI_MakeWire wireBuilder(edge);
  TopoDS_Wire pathWire = wireBuilder.Wire();

  // 创建截面形状
  gp_Ax2 pipeAxis(params.wire.front(),
                  gp_Dir(params.wire[1].XYZ() - params.wire[0].XYZ()));
  TopoDS_Shape profileShape =
      create_shape_from_profile(params.profile, false, &pipeAxis);

  // 创建管道
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.Add(profileShape, false, true);
  pipeMaker.SetMode(true);
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create pipe");
  }

  if (!pipeMaker.MakeSolid()) {
    throw Standard_ConstructionError("Failed to create pipe");
  }

  return pipeMaker.Shape();
}


TopoDS_Shape create_pipe_shape(const pipe_shape_params &params,
                               const gp_Pnt &position, const gp_Dir &direction,
                               const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的管道
  TopoDS_Shape pipe = create_pipe_shape(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(pipe, transformation);
  return transform.Shape();
}


TopoDS_Shape create_step_shap(const step_shape_params &params) {
  // 检查输入参数
  if (params.step.empty()) {
    throw std::runtime_error("STEP content is empty");
  }

  STEPControl_Reader reader;

  try {
    // 创建输入流并读取STEP内容
    std::istringstream in(params.step, std::ios_base::in);

    // 读取STEP流
    IFSelect_ReturnStatus status = reader.ReadStream(params.name.c_str(), in);
    if (status != IFSelect_RetDone) {
      throw std::runtime_error("Failed to read STEP stream, status: " +
                               std::to_string(static_cast<int>(status)));
    }

    // 转换根实体
    if (!reader.TransferRoots()) {
      throw std::runtime_error("Failed to transfer STEP roots");
    }

    // 获取合并后的形状
    TopoDS_Shape result = reader.OneShape();
    if (result.IsNull()) {
      throw std::runtime_error("Resulting shape is null");
    }

    return result;
  } catch (const Standard_Failure &e) {
    throw std::runtime_error("OCCT error: " +
                             std::string(e.GetMessageString()));
  } catch (const std::exception &e) {
    throw std::runtime_error("Error processing STEP: " + std::string(e.what()));
  }
}


TopoDS_Shape create_step_shap(const step_shape_params &params,
                              const gp_Pnt &position, const gp_Dir &direction,
                              const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的Shape
  TopoDS_Shape pipe = create_step_shap(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(pipe, transformation);
  return transform.Shape();
}

} // namespace topo
} // namespace flywave
