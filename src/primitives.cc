#include "primitives.hh"
#include <BRepAdaptor_CompCurve.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepBndLib.hxx>
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
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakeWedge.hxx>
#include <BRepTools.hxx>
#include <BRep_Tool.hxx>
#include <ChFi2d_AnaFilletAlgo.hxx>
#include <ElCLib.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <GC_MakeCircle.hxx>
#include <GC_MakeSegment.hxx>
#include <GProp_GProps.hxx>
#include <GeomAPI_IntCS.hxx>
#include <GeomAPI_Interpolate.hxx>
#include <GeomAPI_PointsToBSpline.hxx>
#include <GeomFill_Pipe.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Line.hxx>
#include <Geom_Plane.hxx>
#include <Geom_SurfaceOfRevolution.hxx>
#include <Law_Linear.hxx>
#include <Precision.hxx>
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

namespace flywave {
namespace topo {
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
  if (params.angle <= 0.0 || params.angle > 2 * M_PI)
    throw Standard_ConstructionError("Angle must be in (0, 2PI]");

  // 完整圆环情况
  if (fabs(params.angle - 2 * M_PI) < Precision::Angular()) {
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

TopoDS_Wire create_oriented_wire(const gp_Ax2 &system, double radius,
                                 double angle, bool isHole) {
  // 创建主圆弧（带容差计算）
  const double adjusted_angle =
      angle < 2 * M_PI ? angle - Precision::Angular() / 100 : angle;
  Handle(Geom_TrimmedCurve) arc =
      GC_MakeArcOfCircle(gp_Circ(system, radius), 0, adjusted_angle, false)
          .Value();

  BRepBuilderAPI_MakeWire wireMaker;

  // 添加圆弧边（精确端点捕捉）
  wireMaker.Add(BRepBuilderAPI_MakeEdge(arc));

  // 非完整圆处理
  if (adjusted_angle < 2 * M_PI - Precision::Angular()) {
    gp_Pnt start = arc->Value(arc->FirstParameter());
    gp_Pnt end = arc->Value(arc->LastParameter());

    // 精确连接线段（使用几何API）
    Handle(Geom_TrimmedCurve) line1 =
        GC_MakeSegment(start, gp::Origin()).Value();
    Handle(Geom_TrimmedCurve) line2 = GC_MakeSegment(gp::Origin(), end).Value();

    if (isHole) {
      wireMaker.Add(BRepBuilderAPI_MakeEdge(line2)); // 终点到圆心
      wireMaker.Add(BRepBuilderAPI_MakeEdge(line1)); // 圆心到起点
    } else {
      wireMaker.Add(BRepBuilderAPI_MakeEdge(line1)); // 起点到圆心
      wireMaker.Add(BRepBuilderAPI_MakeEdge(line2)); // 圆心到终点
    }
  }

  // 强制线框方向
  TopoDS_Wire result = wireMaker.Wire();
  result.Closed(true); // 显式设置闭合标志
  if (isHole) {
    result.Reverse();
  }

  // 增强闭合性检查
  BRepCheck_Wire checker(result);
  if (checker.Closed() != BRepCheck_NoError) {
    throw Standard_ConstructionError("Wire closure verification failed");
  }

  return result;
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
  if (params.angle <= 0.0 || params.angle > 2 * M_PI) {
    throw Standard_ConstructionError("Angle must be in (0, 2PI]");
  }

  // 完整圆环情况保持原逻辑
  if (fabs(params.angle - 2 * M_PI) < Precision::Angular()) {
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
  if (params.angle <= 0 || params.angle > 2 * M_PI) {
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

    // 执行布尔切操作
    return BRepAlgoAPI_Cut(bottomCone.Shape(), topCylinder.Shape());
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
  // 添加正交性校验
  if (Abs(params.normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }
  // 首先创建标准方向的拉伸体
  TopoDS_Shape body = create_stretched_body(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), params.normal, xDir);
  gp_Ax3 targetAx3(basePoint, params.normal, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(body, transformation);
  return transform.Shape();
}

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
  double actual_height = sqrt(pow(hypotenuse, 2) - pow(half_front_spacing, 2));

  // 创建原点坐标系 (原点在V型张开端两前段连线中点)
  gp_Pnt origin(0, 0, 0);
  gp_Dir yDir(0, 1, 0); // Y轴方向为两前段连线方向
  gp_Dir zDir(0, 0, 1); // Z轴向上
  gp_Ax2 baseCS(origin, zDir, yDir);

  // 创建绝缘子串 (两侧各一串)
  for (int side = -1; side <= 1; side += 2) {
    // 计算绝缘子串起点和终点
    gp_Pnt start_point(side * half_front_spacing, 0, 0);
    gp_Pnt end_point(side * half_back_spacing / 2, actual_height, 0);

    // 创建绝缘子串路径
    gp_Vec insulator_dir(end_point.X() - start_point.X(),
                         end_point.Y() - start_point.Y(),
                         end_point.Z() - start_point.Z());
    gp_Vec front_dir(start_point.X() - end_point.X(),
                     start_point.Y() - end_point.Y(),
                     start_point.Z() - end_point.Z());

    gp_Pnt front(side * half_front_spacing, 0, 0);

    // 前端连接
    BRepPrimAPI_MakeCylinder frontCyl(gp_Ax2(front, front_dir),
                                      params.radius / 4, // 使用1/4半径
                                      params.frontLength // 实际长度
    );
    builder.Add(result, frontCyl.Shape());

    gp_Pnt back(side * half_back_spacing / 2, actual_height, 0);

    // 后端连接
    BRepPrimAPI_MakeCylinder backCyl(gp_Ax2(back, insulator_dir),
                                     params.radius / 4, // 使用1/4半径
                                     params.backLength  // 实际长度
    );
    builder.Add(result, backCyl.Shape());

    // 创建每片绝缘子
    for (int i = 0; i < params.insulatorCount; i++) {
      double ratio_start = (double)i / params.insulatorCount;
      double ratio_end = (double)(i + 1) / params.insulatorCount;

      gp_Pnt segment_start(start_point.X() + insulator_dir.X() * ratio_start,
                           start_point.Y() + insulator_dir.Y() * ratio_start,
                           start_point.Z() + insulator_dir.Z() * ratio_start);

      gp_Pnt segment_end(start_point.X() + insulator_dir.X() * ratio_end,
                         start_point.Y() + insulator_dir.Y() * ratio_end,
                         start_point.Z() + insulator_dir.Z() * ratio_end);

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

      gp_Pnt basePoint(segment_start.X(),
                       segment_start.Y() + params.height * 0.8,
                       params.radius); // 外缘点
      gp_Pnt p1(segment_start.X(), segment_start.Y() + params.height * 0.8,
                skirtRadius); // 外缘点
      gp_Pnt p2(segment_start.X(), segment_start.Y() + params.height * 0.7,
                skirtRadius * 0.95); // 上翘
      gp_Pnt p3(segment_start.X(), segment_start.Y() + params.height * 0.5,
                skirtRadius * 0.7); // 下凹
      gp_Pnt endPoint(segment_start.X(),
                      segment_start.Y() + params.height * 0.5,
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
    double box_x_length = params.backSpacing / 2.0; // X方向覆盖间距
    double box_y_thickness = params.radius * 0.8;   // Y方向厚度
    double box_z_height = params.radius * 0.8;      // Z方向高度

    // 计算连接盒参数
    gp_Pnt box_center(-box_x_length / 2,
                      actual_height + params.radius * 2, // 使用计算后的实际高度
                      box_z_height / 2);

    // 创建连接盒坐标系（Y轴保持与绝缘子走向一致）
    gp_Ax2 box_axis(box_center, gp_Dir(0, 1, 0), // 主方向(Y)与绝缘子走向一致
                    gp_Dir(1, 0, 0)              // Z轴保持垂直
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
create_rectangular_fixed_plate(const rectangular_hole_plate_params &params) {
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
create_rectangular_fixed_plate(const rectangular_hole_plate_params &params,
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

TopoDS_Shape create_wire(const wire_params &params) {
  // 参数验证
  if (params.sag <= 0.0) {
    throw Standard_ConstructionError("Sag must be positive");
  }
  if (params.diameter <= 0.0) {
    throw Standard_ConstructionError("Diameter must be positive");
  }
  if (!params.fitPoints.empty() && params.fitPoints.size() < 2) {
    throw Standard_ConstructionError("At least 2 fit points are required");
  }

  // 创建导线路径
  BRepBuilderAPI_MakeWire wireMaker;

  Handle(Geom_BSplineCurve) curve;
  if (!params.fitPoints.empty()) {
    // 使用拟合点集创建样条曲线
    Handle(TColgp_HArray1OfPnt) points =
        new TColgp_HArray1OfPnt(1, params.fitPoints.size());
    for (int i = 0; i < params.fitPoints.size(); ++i) {
      points->SetValue(i + 1, params.fitPoints[i]);
    }

    GeomAPI_Interpolate interpolate(points, false, Precision::Confusion());
    interpolate.Load(gp_Vec(0, 0, 1), gp_Vec(0, 0, 1),
                     true); // 添加首末端导数约束
    interpolate.Perform();
    if (!interpolate.IsDone()) {
      throw Standard_ConstructionError("Failed to create interpolated curve");
    }

    curve = interpolate.Curve();
    if (curve.IsNull()) {
      throw Standard_ConstructionError("Failed to create curve");
    }
    BRepBuilderAPI_MakeEdge edgeMaker(curve);
    if (!edgeMaker.IsDone()) {
      throw Standard_ConstructionError("Failed to create edge from curve");
    }
    wireMaker.Add(edgeMaker.Edge());
  } else {
    // 创建直线段
    wireMaker.Add(
        BRepBuilderAPI_MakeEdge(params.startPoint, params.endPoint).Edge());
  }

  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create wire path");
  }
  TopoDS_Wire pathWire = wireMaker.Wire();

  // 创建圆形截面（直径方向始终垂直于路径）
  gp_Ax2 sectionAxis;
  if (!params.fitPoints.empty() && curve) {
    // 使用曲线起点处的Frenet标架
    gp_Pnt startPnt;
    gp_Vec tangent, normal, binormal;
    curve->D1(0, startPnt, tangent);

    // 自动生成法向量（确保不平行于切线）
    if (tangent.IsParallel(gp_Vec(0, 0, 1), Precision::Angular())) {
      normal = gp_Vec(1, 0, 0);
    } else {
      normal = gp_Vec(0, 0, 1);
    }
    binormal = tangent.Crossed(normal);

    sectionAxis = gp_Ax2(startPnt,
                         gp_Dir(tangent), // X轴沿切线方向
                         gp_Dir(normal)); // Z轴沿法线方向
  } else {
    sectionAxis = gp_Ax2(params.startPoint, gp_Dir(params.endPoint.XYZ() -
                                                   params.startPoint.XYZ()));
  }

  // 创建截面圆
  gp_Circ sectionCircle(sectionAxis, params.diameter / 2);
  TopoDS_Wire sectionWire =
      BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(sectionCircle).Edge())
          .Wire();

  // 配置扫掠生成器（关键修正部分）
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.Add(sectionWire);
  pipeMaker.SetTolerance(1e-6);     // 添加容差设置
  pipeMaker.SetMode(Standard_True); // 启用Frenet坐标系
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to generate wire pipe");
  }
  if (!pipeMaker.MakeSolid()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }

  // 闭合开口端
  if (pipeMaker.Shape().IsNull()) {
    throw Standard_ConstructionError("Generated shape is invalid");
  }

  return pipeMaker.Shape();
}

TopoDS_Shape create_wire(const wire_params &params, const gp_Pnt &position,
                         const gp_Dir &direction, const gp_Dir &upDirection) {
  // 首先创建标准方向的电线
  TopoDS_Shape cable = create_wire(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0), gp_Dir(1, 0, 0));
  gp_Ax3 targetAx3(position, direction, upDirection);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(cable, transformation);
  return transform.Shape();
}

TopoDS_Shape create_cable(const cable_params &params) {
  // 参数验证
  if (params.diameter <= 0.0) {
    throw Standard_ConstructionError("Diameter must be positive");
  }
  if (params.inflectionPoints.size() != params.radii.size()) {
    throw Standard_ConstructionError(
        "Inflection points and radii count mismatch");
  }
  for (double r : params.radii) {
    if (r <= 0.0) {
      throw Standard_ConstructionError("Radius must be positive");
    }
  }

  // 创建路径曲线
  BRepBuilderAPI_MakeWire wireMaker;
  std::vector<gp_Pnt> allPoints;
  allPoints.push_back(params.startPoint);
  allPoints.insert(allPoints.end(), params.inflectionPoints.begin(),
                   params.inflectionPoints.end());
  allPoints.push_back(params.endPoint);

  if (allPoints.size() == 2) {
    wireMaker.Add(
        BRepBuilderAPI_MakeEdge(params.startPoint, params.endPoint).Edge());
  } else {
    // 创建样条曲线
    Handle(TColgp_HArray1OfPnt) points =
        new TColgp_HArray1OfPnt(1, allPoints.size());
    for (int i = 0; i < allPoints.size(); ++i) {
      points->SetValue(i + 1, allPoints[i]);
    }

    GeomAPI_Interpolate interpolate(points, false, Precision::Confusion());
    interpolate.Load(gp_Vec(0, 0, 1), gp_Vec(0, 0, 1),
                     true); // 添加首末端导数约束
    interpolate.Perform();
    if (!interpolate.IsDone()) {
      throw Standard_ConstructionError("Failed to create interpolated curve");
    }

    Handle(Geom_BSplineCurve) curve = interpolate.Curve();
    wireMaker.Add(BRepBuilderAPI_MakeEdge(curve).Edge());
  }

  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create cable path");
  }
  TopoDS_Wire pathWire = wireMaker.Wire();

  // 获取路径起始点的切线方向
  BRepAdaptor_CompCurve curveAdaptor(wireMaker.Wire());
  gp_Pnt startPoint;
  gp_Vec startTangent;
  curveAdaptor.D1(curveAdaptor.FirstParameter(), startPoint, startTangent);

  // 在创建截面圆之前添加方向修正
  gp_Dir initNormal = startTangent.Normalized();
  gp_Dir refDir(0, 1, 0);
  // 确保参考方向与切线不平行
  if (Abs(initNormal.Dot(refDir)) > 0.99) {
    refDir = gp_Dir(1, 0, 0);
  }
  gp_Ax2 sectionAxes(gp::Origin(), initNormal, refDir);

  // 创建电缆截面圆
  gp_Circ sectionCircle(sectionAxes, params.diameter / 2);
  TopoDS_Edge sectionEdge = BRepBuilderAPI_MakeEdge(sectionCircle).Edge();
  TopoDS_Wire sectionWire = BRepBuilderAPI_MakeWire(sectionEdge).Wire();

  // 沿路径扫掠创建电缆
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.Add(sectionWire);
  pipeMaker.SetTolerance(1e-6); // 添加容差设置
  pipeMaker.SetMaxDegree(5);
  pipeMaker.SetMode(Standard_True); // 启用Frenet坐标系
  pipeMaker.SetTransitionMode(BRepBuilderAPI_RoundCorner);
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to generate cable");
  }
  if (!pipeMaker.MakeSolid()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }

  return pipeMaker.Shape();
}

TopoDS_Shape create_cable(const cable_params &params, const gp_Pnt &position,
                          const gp_Dir &direction, const gp_Dir &upDirection) {
  // 首先创建标准方向的电缆
  TopoDS_Shape cable = create_cable(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0), gp_Dir(1, 0, 0));
  gp_Ax3 targetAx3(position, direction, upDirection);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(cable, transformation);
  return transform.Shape();
}

TopoDS_Shape create_curve_cable(const curve_cable_params &params) {
  // 参数验证
  if (params.diameter <= 0) {
    throw Standard_ConstructionError("Cable diameter must be positive");
  }
  if (params.controlPoints.empty()) {
    throw Standard_ConstructionError("Control points cannot be empty");
  }
  if (params.controlPoints.size() != params.curveTypes.size()) {
    throw Standard_ConstructionError(
        "Control points and curve types count mismatch");
  }

  // 创建路径线
  BRepBuilderAPI_MakeWire pathMaker;

  for (size_t i = 0; i < params.controlPoints.size(); ++i) {
    const auto &points = params.controlPoints[i];
    curve_type type = params.curveTypes[i];

    switch (type) {
    case curve_type::LINE: {
      if (points.size() != 2) {
        throw Standard_ConstructionError(
            "Line segment requires exactly 2 points");
      }
      TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(points[0], points[1]).Edge();
      pathMaker.Add(edge);
      break;
    }
    case curve_type::ARC: {
      if (points.size() != 3) {
        throw Standard_ConstructionError(
            "Arc segment requires exactly 3 points");
      }
      // 创建三点圆弧
      GC_MakeArcOfCircle arcMaker(points[0], points[1], points[2]);
      if (!arcMaker.IsDone()) {
        throw Standard_ConstructionError("Failed to create arc segment");
      }
      TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(arcMaker.Value()).Edge();
      pathMaker.Add(edge);
      break;
    }
    case curve_type::SPLINE: {
      if (points.size() < 2) {
        throw Standard_ConstructionError(
            "Spline segment requires at least 2 points");
      }

      // 创建样条曲线
      Handle(TColgp_HArray1OfPnt) array =
          new TColgp_HArray1OfPnt(1, points.size());
      for (size_t j = 0; j < points.size(); ++j) {
        array->SetValue(j + 1, points[j]);
      }
      GeomAPI_Interpolate interpolate(array, false, Precision::Confusion());
      interpolate.Load(gp_Vec(0, 0, 1), gp_Vec(0, 0, 1),
                       true); // 添加首末端导数约束
      interpolate.Perform();
      if (!interpolate.IsDone()) {
        throw Standard_ConstructionError("Failed to create spline segment");
      }
      TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(interpolate.Curve()).Edge();
      pathMaker.Add(edge);
      break;
    }
    default:
      throw Standard_ConstructionError("Unknown curve type");
    }
  }

  if (!pathMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create cable path");
  }

  // 获取路径起始点的切线方向
  BRepAdaptor_CompCurve curveAdaptor(pathMaker.Wire());
  gp_Pnt startPoint;
  gp_Vec startTangent;
  curveAdaptor.D1(curveAdaptor.FirstParameter(), startPoint, startTangent);

  // 在创建截面圆之前添加方向修正
  gp_Dir initNormal = startTangent.Normalized();
  gp_Dir refDir(0, 1, 0);
  // 确保参考方向与切线不平行
  if (Abs(initNormal.Dot(refDir)) > 0.99) {
    refDir = gp_Dir(1, 0, 0);
  }
  gp_Ax2 sectionAxes(gp::Origin(), initNormal, refDir);

  // 创建圆形截面（直径方向始终垂直于路径）
  gp_Circ circle(sectionAxes, params.diameter / 2);
  TopoDS_Wire profile =
      BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(circle).Edge()).Wire();

  // 使用扫掠器自动计算坐标系（添加Frenet模式）
  BRepOffsetAPI_MakePipeShell pipeMaker(pathMaker.Wire());
  pipeMaker.SetMode(true);                   // 设置为实体模式
  pipeMaker.SetMaxDegree(5);                 // 提高最大阶数以适应复杂曲率
  pipeMaker.SetTolerance(1e-5);              // 放宽容差适应复杂路径
  pipeMaker.SetForceApproxC1(Standard_True); // 强制C1连续近似

  // 创建动态调整的圆形截面（直径始终垂直于路径）
  Handle(Law_Linear) law = new Law_Linear();
  law->Set(0, 1, 0, 1);                           // 保持恒定半径
  pipeMaker.SetLaw(profile, law, Standard_False); // 关联截面和变化规律

  pipeMaker.Add(profile);
  pipeMaker.SetTransitionMode(BRepBuilderAPI_RightCorner); // 改进过渡模式

  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create cable by pipe shell");
  }
  if (!pipeMaker.MakeSolid()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }

  return pipeMaker.Shape();
}

TopoDS_Shape create_curve_cable(const curve_cable_params &params,
                                const gp_Pnt &position, const gp_Dir &direction,
                                const gp_Dir &upDirection) {
  // 正交性校验
  if (Abs(direction.Dot(upDirection)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and up direction must be perpendicular");
  }

  // 创建标准方向的电缆
  TopoDS_Shape cable = create_curve_cable(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, upDirection);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(cable, transformation);
  return transform.Shape();
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

        // 计算杆件方向向量
        gp_Vec directionVec(startPos, endPos);
        double length = directionVec.Magnitude();

        // 创建正交坐标系（考虑yDirection）
        gp_Dir Z = directionVec.Normalized();
        gp_Dir X = member.xDirection;

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
            BRepPrimAPI_MakePrism(transform.Shape(), gp_Vec(0, 0, length))
                .Shape();
        break;
      }
      case member_type::TUBE: {
        // 创建等径钢管
        double diameter = std::stod(member.specification.substr(2));
        double thickness = std::stod(
            member.specification.substr(member.specification.find('x') + 1));

        gp_Pnt midPoint((startPos.X() + endPos.X()) / 2,
                        (startPos.Y() + endPos.Y()) / 2,
                        (startPos.Z() + endPos.Z()) / 2);

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
  if (params.washerShape != 1 && params.washerShape != 2)
    throw Standard_ConstructionError(
        "Washer shape must be 1 (square) or 2 (round)");
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
    if (params.washerShape == 1) { // 方形垫片
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
  if (params.washerShape != 1 && params.washerShape != 2)
    throw Standard_ConstructionError(
        "Washer shape must be 1 (square) or 2 (round)");
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
    if (params.washerShape == 1) { // 方形垫片
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
  if (params.washerShape == 1) { // 方形垫片
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
    if (params.washerShape == 1) { // 方形垫片
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
  if (params.washerShape != 1 && params.washerShape != 2)
    throw Standard_ConstructionError(
        "Washer shape must be 1 (square) or 2 (round)");
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
  if (params.washerShape == 1) { // 方形垫片
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
    if (params.washerShape == 1) { // 方形垫片
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
  if (params.washerShape != 1 && params.washerShape != 2)
    throw Standard_ConstructionError(
        "Washer shape must be 1 (square) or 2 (round)");
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
    if (params.washerShape == 1) { // 方形垫片
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
  if (params.washerShape != 1 && params.washerShape != 2)
    throw Standard_ConstructionError(
        "Washer shape must be 1 (square) or 2 (round)");
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
    if (params.washerShape == 1) { // 方形垫片
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

TopoDS_Shape create_cable_wire(const cable_wire_params &params) {
  // 参数验证
  if (params.points.size() < 2) {
    throw Standard_ConstructionError("At least 2 points are required");
  }
  if (params.outsideDiameter <= 0.0) {
    throw Standard_ConstructionError("Outside diameter must be positive");
  }

  // 创建电缆路径
  BRepBuilderAPI_MakeWire wireMaker;

  if (params.points.size() == 2) {
    // 直接创建直线
    wireMaker.Add(
        BRepBuilderAPI_MakeEdge(params.points[0], params.points[1]).Edge());
  } else {

    // 使用拟合点集创建样条曲线
    Handle(TColgp_HArray1OfPnt) points =
        new TColgp_HArray1OfPnt(1, params.points.size());
    for (int i = 0; i < params.points.size(); ++i) {
      points->SetValue(i + 1, params.points[i]);
    }

    GeomAPI_Interpolate interpolate(points, false, Precision::Confusion());
    interpolate.Load(gp_Vec(0, 0, 1), gp_Vec(0, 0, 1),
                     true); // 添加首末端导数约束
    interpolate.Perform();
    if (!interpolate.IsDone()) {
      throw Standard_ConstructionError("Failed to create interpolated curve");
    }

    const Handle(Geom_BSplineCurve) &curve = interpolate.Curve();
    if (curve.IsNull()) {
      throw Standard_ConstructionError("Failed to create curve");
    }
    BRepBuilderAPI_MakeEdge edgeMaker(curve);
    if (!edgeMaker.IsDone()) {
      throw Standard_ConstructionError("Failed to create edge from curve");
    }
    wireMaker.Add(edgeMaker.Edge());
  }

  // 获取路径起始点的切线方向
  BRepAdaptor_CompCurve curveAdaptor(wireMaker.Wire());
  gp_Pnt startPoint;
  gp_Vec startTangent;
  curveAdaptor.D1(curveAdaptor.FirstParameter(), startPoint, startTangent);

  // 在创建截面圆之前添加方向修正
  gp_Dir initNormal = startTangent.Normalized();
  gp_Dir refDir(0, 1, 0);
  // 确保参考方向与切线不平行
  if (Abs(initNormal.Dot(refDir)) > 0.99) {
    refDir = gp_Dir(1, 0, 0);
  }
  gp_Ax2 sectionAxes(gp::Origin(), initNormal, refDir);

  // 创建圆形截面（直径方向始终垂直于路径）
  gp_Circ circle(sectionAxes, params.outsideDiameter / 2);
  TopoDS_Wire profile =
      BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(circle).Edge()).Wire();

  // 沿路径扫掠生成电缆
  BRepOffsetAPI_MakePipeShell pipeMaker(wireMaker.Wire());
  pipeMaker.Add(profile);
  pipeMaker.SetMode(Standard_True); // 使用Frenet坐标系
  pipeMaker.SetTolerance(1e-6);
  pipeMaker.SetMaxDegree(5);
  pipeMaker.SetTransitionMode(BRepBuilderAPI_RoundCorner);
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to generate cable wire");
  }
  if (!pipeMaker.MakeSolid()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }

  return pipeMaker.Shape();
}

TopoDS_Shape create_cable_wire(const cable_wire_params &params,
                               const gp_Pnt &position, const gp_Dir &direction,
                               const gp_Dir &upDirection) {
  // 首先创建标准方向的电缆
  TopoDS_Shape cable = create_cable_wire(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0), gp_Dir(1, 0, 0));
  gp_Ax3 targetAx3(position, direction, upDirection);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(cable, transformation);
  return transform.Shape();
}

TopoDS_Shape create_cable_joint(const cable_joint_params &params) {
  // 参数验证
  if (params.length <= 0 || params.outerDiameter <= 0 ||
      params.terminalLength <= 0 || params.innerDiameter <= 0) {
    throw Standard_ConstructionError("All dimensions must be positive");
  }
  if (params.innerDiameter >= params.outerDiameter) {
    throw Standard_ConstructionError(
        "Inner diameter must be less than outer diameter");
  }
  if (params.terminalLength * 2 >= params.length) {
    throw Standard_ConstructionError(
        "Terminal length too large compared to total length");
  }

  // 计算中间圆柱体长度
  double middleLength = params.length - (2 * params.terminalLength);

  // 创建中间圆柱体
  gp_Ax2 middleAxis(gp_Pnt(-middleLength / 2, 0, 0), gp::DX());
  TopoDS_Shape joint = BRepPrimAPI_MakeCylinder(
                           middleAxis, params.outerDiameter / 2, middleLength)
                           .Shape();

  // 创建两端过渡圆台
  gp_Ax2 leftAxis(gp_Pnt(-params.length / 2, 0, 0), gp::DX());
  TopoDS_Shape leftCone =
      BRepPrimAPI_MakeCone(leftAxis, params.innerDiameter / 2,
                           params.outerDiameter / 2, params.terminalLength)
          .Shape();

  gp_Ax2 rightAxis(gp_Pnt(params.length / 2 - params.terminalLength, 0, 0),
                   gp::DX());
  TopoDS_Shape rightCone =
      BRepPrimAPI_MakeCone(rightAxis, params.outerDiameter / 2,
                           params.innerDiameter / 2, params.terminalLength)
          .Shape();

  // 合并所有部件
  joint = BRepAlgoAPI_Fuse(joint, leftCone).Shape();
  joint = BRepAlgoAPI_Fuse(joint, rightCone).Shape();

  // 创建中间芯体
  gp_Ax2 holeAxis(gp_Pnt(-params.length / 2 - 1, 0, 0), gp::DX());
  TopoDS_Shape middleHole =
      BRepPrimAPI_MakeCylinder(holeAxis, params.innerDiameter / 2,
                               params.length + 2)
          .Shape();

  BRepAlgoAPI_Cut fusHole(joint, middleHole);
  if (!fusHole.IsDone()) {
    throw Standard_ConstructionError("Failed to fuse port with joint");
  }
  joint = fusHole.Shape();

  return joint;
}

TopoDS_Shape create_cable_joint(const cable_joint_params &params,
                                const gp_Pnt &position, const gp_Dir &direction,
                                const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的接头
  TopoDS_Shape joint = create_cable_joint(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(joint, transformation);
  return transform.Shape();
}

TopoDS_Shape create_optical_fiber_box(const optical_fiber_box_params &params) {
  // 参数验证
  if (params.length <= 0 || params.height <= 0 || params.width <= 0) {
    throw Standard_ConstructionError("All dimensions must be positive");
  }

  // 创建主体盒子
  gp_Pnt corner(-params.length / 2, -params.width / 2, -params.height / 2);
  TopoDS_Shape box =
      BRepPrimAPI_MakeBox(corner, params.length, params.width, params.height)
          .Shape();

  // 创建顶部圆角特征
  double radius = std::min(params.width, params.height) * 0.1;
  BRepFilletAPI_MakeFillet fillet(box);

  TopExp_Explorer explorer(box, TopAbs_EDGE);
  while (explorer.More()) {
    TopoDS_Edge edge = TopoDS::Edge(explorer.Current());
    fillet.Add(radius, edge);
    explorer.Next();
  }

  return fillet.Shape();
}

TopoDS_Shape create_optical_fiber_box(const optical_fiber_box_params &params,
                                      const gp_Pnt &position,
                                      const gp_Dir &direction,
                                      const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的接头盒
  TopoDS_Shape box = create_optical_fiber_box(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(box, transformation);
  return transform.Shape();
}

// 创建户外-干式电缆终端
TopoDS_Shape
create_outdoor_cable_terminal(const cable_terminal_params &params) {
  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  double currentZ = -params.lowerTerminalLength;

  // 1. 创建下端电缆连接器 (圆柱)
  gp_Ax2 lowerTerminalAxis(gp_Pnt(0, 0, currentZ), gp::DZ());
  TopoDS_Shape lowerTerminal =
      BRepPrimAPI_MakeCylinder(lowerTerminalAxis,
                               params.lowerTerminalDiameter / 2,
                               params.lowerTerminalLength)
          .Shape();
  builder.Add(compound, lowerTerminal);
  currentZ += params.lowerTerminalLength;

  // 2. 创建法兰盘
  // 法兰盘主体 (矩形)
  double flangeThickness = params.flangeBoltHeight / 2;
  gp_Pnt flangeCorner1(-params.flangeWidth / 2, -params.flangeWidth / 2,
                       currentZ);
  gp_Pnt flangeCorner2(params.flangeWidth / 2, params.flangeWidth / 2,
                       currentZ + flangeThickness);
  TopoDS_Shape flange =
      BRepPrimAPI_MakeBox(flangeCorner1, flangeCorner2).Shape();

  // 边缘倒角（仅处理四个角上平行于Z轴的四条边）
  if (params.flangeChamferRadius > 0) {
    BRepFilletAPI_MakeChamfer chamfer(flange);
    TopExp_Explorer edgeExp(flange, TopAbs_EDGE);

    // 检查每条边是否在四个角上且平行于Z轴
    for (; edgeExp.More(); edgeExp.Next()) {
      TopoDS_Edge edge = TopoDS::Edge(edgeExp.Current());

      // 获取边的两个顶点
      TopoDS_Vertex v1, v2;
      TopExp::Vertices(edge, v1, v2);
      gp_Pnt p1 = BRep_Tool::Pnt(v1);
      gp_Pnt p2 = BRep_Tool::Pnt(v2);

      // 检查边是否平行于Z轴
      if (Abs(p1.X() - p2.X()) < Precision::Confusion() &&
          Abs(p1.Y() - p2.Y()) < Precision::Confusion()) {
        chamfer.Add(params.flangeChamferRadius, edge);
      }
    }
    flange = chamfer.Shape();
  }

  // 中心孔
  gp_Ax2 centerAxis(gp_Pnt(0, 0, currentZ), gp::DZ());
  TopoDS_Shape centerHole =
      BRepPrimAPI_MakeCylinder(centerAxis, params.flangeCenterHoleRadius,
                               flangeThickness)
          .Shape();
  flange = BRepAlgoAPI_Cut(flange, centerHole).Shape();

  // 矩形开口
  if (params.flangeOpeningWidth > 0) {
    gp_Pnt openingCorner1(-params.flangeOpeningWidth / 2, 0, currentZ);
    gp_Pnt openingCorner2(params.flangeOpeningWidth / 2, params.flangeWidth / 2,
                          currentZ + flangeThickness);
    TopoDS_Shape opening =
        BRepPrimAPI_MakeBox(openingCorner1, openingCorner2).Shape();
    flange = BRepAlgoAPI_Cut(flange, opening).Shape();
  }

  // 螺栓孔
  if (params.flangeHoleDiameter > 0) {
    // 创建螺栓（四个角的圆柱体）
    double boltRadius = params.flangeHoleDiameter / 2;
    double boltHeight = params.flangeBoltHeight;
    double boltProtrusion = boltHeight / 4; // 上下各露出1/4高度
    double boltPos = params.flangeHoleSpacing / 2;

    gp_Pnt boltPositions[4] = {
        gp_Pnt(boltPos, boltPos, currentZ - boltProtrusion),
        gp_Pnt(-boltPos, boltPos, currentZ - boltProtrusion),
        gp_Pnt(boltPos, -boltPos, currentZ - boltProtrusion),
        gp_Pnt(-boltPos, -boltPos, currentZ - boltProtrusion)};

    for (int i = 0; i < 4; i++) {
      gp_Ax2 boltAxis(boltPositions[i], gp::DZ());
      TopoDS_Shape bolt =
          BRepPrimAPI_MakeCylinder(boltAxis, boltRadius, boltHeight).Shape();
      flange = BRepAlgoAPI_Fuse(flange, bolt).Shape();
    }
  }

  // 添加法兰盘到组合体
  builder.Add(compound, flange);
  currentZ += flangeThickness;

  // 3. 创建尾管 (圆柱)
  gp_Ax2 tailAxis(gp_Pnt(0, 0, currentZ), gp::DZ());
  TopoDS_Shape tail = BRepPrimAPI_MakeCylinder(
                          tailAxis, params.tailDiameter / 2, params.tailHeight)
                          .Shape();
  builder.Add(compound, tail);
  currentZ += params.tailHeight;

  // 4. 创建绝缘子 (锥形或圆柱)
  gp_Ax2 insulatorAxis(gp_Pnt(0, 0, currentZ), gp::DZ());
  TopoDS_Shape insulator;
  if (fabs(params.topDiameter - params.bottomDiameter) <
      Precision::Confusion()) {
    // 等径圆柱
    insulator = BRepPrimAPI_MakeCylinder(insulatorAxis, params.topDiameter / 2,
                                         params.height)
                    .Shape();
  } else {
    // 锥形
    insulator = BRepPrimAPI_MakeCone(insulatorAxis, params.bottomDiameter / 2,
                                     params.topDiameter / 2, params.height)
                    .Shape();
  }
  builder.Add(compound, insulator);

  // 添加伞裙 (仅当有伞裙参数时)
  if (params.skirtCount > 0) {
    double skirtHeight = params.skirtSectionHeight;
    double skirtSpacing = (params.height - params.skirtCount * skirtHeight) /
                          (params.skirtCount + 1);

    for (int i = 0; i < params.skirtCount; ++i) {
      // 计算当前高度位置
      double zPos = currentZ + skirtSpacing + i * (skirtHeight + skirtSpacing);

      // 计算当前直径 (线性插值)
      double ratio = zPos / params.height;
      double currentDiameter =
          params.bottomDiameter +
          (params.topDiameter - params.bottomDiameter) * ratio;

      // 选择伞裙类型 (交替使用两种伞裙)
      bool useUpperSkirt = (i % 2 == 0);
      double skirtTopDiameter = useUpperSkirt ? params.upperSkirtTopDiameter
                                              : params.lowerSkirtTopDiameter;
      double skirtBottomDiameter = useUpperSkirt
                                       ? params.upperSkirtBottomDiameter
                                       : params.lowerSkirtBottomDiameter;

      // 创建伞裙截面 (5点曲线)
      BRepBuilderAPI_MakeWire wire;
      gp_Pnt basePoint(currentDiameter / 2, 0, zPos); // 起始点：主体表面
      gp_Pnt p1(skirtTopDiameter / 2, 0, zPos);       // 伞裙外缘顶部
      gp_Pnt p2(skirtBottomDiameter / 2, 0,
                zPos + skirtHeight * 0.3); // 伞裙外缘底部
      gp_Pnt p3(currentDiameter / 2 * 0.9, 0,
                zPos + skirtHeight * 0.6); // 内凹点
      gp_Pnt endPoint(currentDiameter / 2, 0,
                      zPos + skirtHeight); // 结束点：主体表面

      wire.Add(BRepBuilderAPI_MakeEdge(basePoint, p1));
      wire.Add(BRepBuilderAPI_MakeEdge(p1, p2));
      wire.Add(BRepBuilderAPI_MakeEdge(p2, p3));
      wire.Add(BRepBuilderAPI_MakeEdge(p3, endPoint));
      wire.Add(BRepBuilderAPI_MakeEdge(endPoint, basePoint));

      if (!wire.IsDone()) {
        throw Standard_ConstructionError("Failed to create skirt wire");
      }

      // 旋转生成伞裙 (360度)
      BRepPrimAPI_MakeRevol skirtRevol(BRepLib_MakeFace(wire.Wire()).Face(),
                                       gp_Ax1(gp::Origin(), gp::DZ()));
      TopoDS_Shape skirt = skirtRevol.Shape();
      if (skirt.IsNull()) {
        throw Standard_ConstructionError("Failed to create skirt");
      }

      builder.Add(compound, skirt);
    }
  }

  currentZ += params.height;

  // 5. 创建顶部连接金具 (带孔的圆柱)
  gp_Ax2 upperTerminalAxis(gp_Pnt(0, 0, currentZ), gp::DZ());
  TopoDS_Shape upperTerminal =
      BRepPrimAPI_MakeCylinder(upperTerminalAxis,
                               params.upperTerminalDiameter / 2,
                               params.upperTerminalLength)
          .Shape();

  // 添加连接孔
  if (params.hole1Diameter > 0 && params.hole2Diameter > 0) {
    double holeZ = currentZ + params.upperTerminalLength - params.hole1Distance;
    gp_Ax2 hole1Axis(gp_Pnt(0, -params.upperTerminalDiameter / 2, holeZ),
                     gp::DY());
    TopoDS_Shape hole1 =
        BRepPrimAPI_MakeCylinder(hole1Axis, params.hole1Diameter / 2,
                                 params.upperTerminalDiameter)
            .Shape();

    gp_Ax2 hole2Axis(gp_Pnt(0, -params.upperTerminalDiameter / 2,
                            holeZ - params.holeSpacing),
                     gp::DY());
    TopoDS_Shape hole2 =
        BRepPrimAPI_MakeCylinder(hole2Axis, params.hole2Diameter / 2,
                                 params.upperTerminalDiameter)
            .Shape();

    upperTerminal = BRepAlgoAPI_Cut(upperTerminal, hole1).Shape();
    upperTerminal = BRepAlgoAPI_Cut(upperTerminal, hole2).Shape();
  }

  builder.Add(compound, upperTerminal);

  return compound;
}

// 创建户内电缆终端
TopoDS_Shape create_indoor_cable_terminal(const cable_terminal_params &params) {
  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  double currentZ = 0;

  // 1. 创建下端电缆连接器 (圆柱)
  gp_Ax2 lowerTerminalAxis(gp_Pnt(0, 0, currentZ), gp::DZ());
  TopoDS_Shape lowerTerminal =
      BRepPrimAPI_MakeCylinder(lowerTerminalAxis,
                               params.lowerTerminalDiameter / 2,
                               params.lowerTerminalLength)
          .Shape();
  builder.Add(compound, lowerTerminal);
  currentZ += params.lowerTerminalLength;

  // 2. 创建主体 (锥形或圆柱)
  gp_Ax2 bodyAxis(gp_Pnt(0, 0, currentZ), gp::DZ());
  TopoDS_Shape body;
  if (fabs(params.topDiameter - params.bottomDiameter) <
      Precision::Confusion()) {
    // 等径圆柱
    body = BRepPrimAPI_MakeCylinder(bodyAxis, params.topDiameter / 2,
                                    params.height)
               .Shape();
  } else {
    // 锥形
    body = BRepPrimAPI_MakeCone(bodyAxis, params.bottomDiameter / 2,
                                params.topDiameter / 2, params.height)
               .Shape();
  }
  builder.Add(compound, body);
  currentZ += params.height;

  // 3. 创建顶部连接金具 (圆柱)
  gp_Ax2 upperTerminalAxis(gp_Pnt(0, 0, currentZ), gp::DZ());
  TopoDS_Shape upperTerminal =
      BRepPrimAPI_MakeCylinder(upperTerminalAxis,
                               params.upperTerminalDiameter / 2,
                               params.upperTerminalLength)
          .Shape();
  builder.Add(compound, upperTerminal);

  return compound;
}

TopoDS_Shape create_cable_terminal(const cable_terminal_params &params) {
  // 参数验证
  if (params.sort < 1 || params.sort > 3) {
    throw Standard_ConstructionError("Invalid terminal type");
  }

  // 根据类型调用不同的创建函数
  if (params.sort == 1 || params.sort == 3) { // 户外或干式
    return create_outdoor_cable_terminal(params);
  } else { // 户内
    return create_indoor_cable_terminal(params);
  }
}

TopoDS_Shape create_cable_terminal(const cable_terminal_params &params,
                                   const gp_Pnt &position,
                                   const gp_Dir &direction) {
  // 创建标准方向的终端
  TopoDS_Shape terminal = create_cable_terminal(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp::DZ());
  gp_Ax3 targetAx3(position, direction);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  // 应用变换
  BRepBuilderAPI_Transform transform(terminal, transformation);
  return transform.Shape();
}

TopoDS_Shape create_cable_accessory(const cable_accessory_params &params) {
  // 参数验证
  if (params.length <= 0 || params.width <= 0 || params.height <= 0) {
    throw Standard_ConstructionError("Box dimensions must be positive");
  }
  if (params.portCount != 3 && params.portCount != 6) {
    throw Standard_ConstructionError("Port count must be 3 or 6");
  }
  if (params.portDiameter <= 0) {
    throw Standard_ConstructionError("Port diameter must be positive");
  }

  // 创建箱体主体
  gp_Pnt origin(-params.length / 2, -params.width / 2, -params.height / 2);
  TopoDS_Shape box =
      BRepPrimAPI_MakeBox(origin, params.length, params.width, params.height)
          .Shape();

  // 创建电缆进出口
  double radius = params.portDiameter / 2;

  std::array<gp_Pnt, 2> portCenters;
  if (params.portCount == 3) {
    portCenters[0] = gp_Pnt(0, -params.width / 2 + params.sidePanelDistance,
                            -params.height / 2);
  } else if (params.portCount == 6) {
    portCenters[0] = gp_Pnt(0, -params.width / 2 + params.sidePanelDistance,
                            -params.height / 2);
    portCenters[1] = gp_Pnt(0, params.width / 2 - params.sidePanelDistance,
                            -params.height / 2);
  }

  int row = params.portCount == 3 ? 1 : 2;

  for (int i = 0; i < row; ++i) {
    gp_Pnt portCenter = portCenters[i];

    gp_Ax2 midAxis(gp_Pnt(portCenter.X(), portCenter.Y(),
                          portCenter.Z() + params.height / 2),
                   gp_Dir(0, 0, -1));
    TopoDS_Shape portMid = BRepPrimAPI_MakeCylinder(
                               midAxis, params.portDiameter / 2, params.height)
                               .Shape();

    gp_Ax2 leftAxis(gp_Pnt(portCenter.X() - params.portSpacing, portCenter.Y(),
                           portCenter.Z() + params.height / 2),
                    gp_Dir(0, 0, -1));
    TopoDS_Shape portLeft =
        BRepPrimAPI_MakeCylinder(leftAxis, params.portDiameter / 2,
                                 params.height)
            .Shape();

    gp_Ax2 rightAxis(gp_Pnt(portCenter.X() + params.portSpacing, portCenter.Y(),
                            portCenter.Z() + params.height / 2),
                     gp_Dir(0, 0, -1));
    TopoDS_Shape portRight =
        BRepPrimAPI_MakeCylinder(rightAxis, params.portDiameter / 2,
                                 params.height)
            .Shape();

    BRepAlgoAPI_Cut fuseMaker0(box, portMid);
    if (!fuseMaker0.IsDone()) {
      throw Standard_ConstructionError("Failed to fuse port with box");
    }
    box = fuseMaker0.Shape();

    BRepAlgoAPI_Cut fuseMaker1(box, portLeft);
    if (!fuseMaker1.IsDone()) {
      throw Standard_ConstructionError("Failed to fuse port with box");
    }
    box = fuseMaker1.Shape();

    BRepAlgoAPI_Cut fuseMaker2(box, portRight);
    if (!fuseMaker2.IsDone()) {
      throw Standard_ConstructionError("Failed to fuse port with box");
    }
    box = fuseMaker2.Shape();
  }

  return box;
}

TopoDS_Shape create_cable_accessory(const cable_accessory_params &params,
                                    const gp_Pnt &position,
                                    const gp_Dir &normal, const gp_Dir &xDir) {
  // 首先创建标准方向的箱体
  TopoDS_Shape box = create_cable_accessory(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(box, transformation);
  return transform.Shape();
}

TopoDS_Shape create_cable_bracket(const cable_bracket_params &params) {
  // 参数验证
  if (params.length <= 0)
    throw Standard_ConstructionError("Length must be positive");
  if (params.rootHeight <= 0)
    throw Standard_ConstructionError("Root height must be positive");
  if (params.rootWidth <= 0)
    throw Standard_ConstructionError("Root width must be positive");
  if (params.width <= 0)
    throw Standard_ConstructionError("Width must be positive");
  if (params.topThickness <= 0)
    throw Standard_ConstructionError("Top thickness must be positive");
  if (params.rootThickness <= 0)
    throw Standard_ConstructionError("Root thickness must be positive");

  // 创建支架根部（垂直部分）
  gp_Pnt rootP1(0, -params.rootThickness / 2, 0);
  gp_Pnt rootP2(0, params.rootThickness / 2, 0);
  gp_Pnt rootP3(0, params.rootThickness / 2, -params.rootHeight);
  gp_Pnt rootP4(0, -params.rootThickness / 2, -params.rootHeight);

  BRepBuilderAPI_MakePolygon rootPoly;
  rootPoly.Add(rootP1);
  rootPoly.Add(rootP2);
  rootPoly.Add(rootP3);
  rootPoly.Add(rootP4);
  rootPoly.Close();

  TopoDS_Face rootFace = BRepBuilderAPI_MakeFace(rootPoly.Wire()).Face();
  TopoDS_Shape root =
      BRepPrimAPI_MakePrism(rootFace, gp_Vec(params.rootWidth, 0, 0)).Shape();

  // 创建支架顶部（水平部分）
  gp_Pnt topP1(params.rootWidth, -params.topThickness / 2, 0);
  gp_Pnt topP2(params.rootWidth, params.topThickness / 2, 0);
  gp_Pnt topP3(params.rootWidth, params.topThickness / 2, -params.width);
  gp_Pnt topP4(params.rootWidth, -params.topThickness / 2, -params.width);

  BRepBuilderAPI_MakePolygon topPoly;
  topPoly.Add(topP1);
  topPoly.Add(topP2);
  topPoly.Add(topP3);
  topPoly.Add(topP4);
  topPoly.Close();

  TopoDS_Face topFace = BRepBuilderAPI_MakeFace(topPoly.Wire()).Face();
  TopoDS_Shape top =
      BRepPrimAPI_MakePrism(topFace, gp_Vec(params.length, 0, 0)).Shape();

  // 合并根部和顶部
  TopoDS_Shape support = BRepAlgoAPI_Fuse(root, top).Shape();

  // 添加三角形加强筋（新增强部分）
  {
    // 定义三角形顶点（Y方向位于底面，后续进行拉伸）
    gp_Pnt ribA(params.rootWidth, -params.topThickness / 4,
                -params.rootHeight);                            // 根部底点
    gp_Pnt ribB(params.rootWidth, -params.topThickness / 4, 0); // 顶部起点
    gp_Pnt ribC(params.rootWidth + params.length / 2, -params.topThickness / 4,
                -params.width); // 顶部终点

    // 构建三角形轮廓
    BRepBuilderAPI_MakePolygon ribPoly;
    ribPoly.Add(ribA);
    ribPoly.Add(ribB);
    ribPoly.Add(ribC);
    ribPoly.Close(); // 闭合为三角形

    // 创建面并沿Y轴拉伸形成实体
    TopoDS_Face ribFace = BRepBuilderAPI_MakeFace(ribPoly.Wire()).Face();
    TopoDS_Shape rib =
        BRepPrimAPI_MakePrism(ribFace, gp_Vec(0, params.topThickness / 2, 0))
            .Shape();

    // 将加强筋融合到主体结构
    support = BRepAlgoAPI_Fuse(support, rib).Shape();
  }

  // 创建立柱安装孔（修正方向轴）
  for (const auto &point : params.columnMountPoints) {
    gp_Ax2 holeAxis(point, gp::DY());
    TopoDS_Shape hole =
        BRepPrimAPI_MakeCylinder(holeAxis, params.rootThickness / 2,
                                 params.rootThickness * 2)
            .Shape();
    support = BRepAlgoAPI_Cut(support, hole).Shape();
  }

  // 创建夹具安装孔（修正方向轴）
  for (const auto &point : params.clampMountPoints) {
    gp_Ax2 holeAxis(point, gp::DY());
    TopoDS_Shape hole =
        BRepPrimAPI_MakeCylinder(holeAxis, params.topThickness / 2,
                                 params.topThickness * 2)
            .Shape();
    support = BRepAlgoAPI_Cut(support, hole).Shape();
  }

  return support;
}

TopoDS_Shape create_cable_bracket(const cable_bracket_params &params,
                                  const gp_Pnt &position, const gp_Dir &normal,
                                  const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 创建标准方向的支架
  TopoDS_Shape support = create_cable_bracket(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(support, transformation);
  return transform.Shape();
}

TopoDS_Shape create_cable_clamp(const cable_clamp_params &params) {
  // 参数验证
  if (params.diameter <= 0 || params.thickness <= 0 || params.width <= 0) {
    throw Standard_ConstructionError("Dimensions must be positive");
  }

  switch (params.type) {
  case cable_clamp_type::SINGLE: {
    // 单根夹具 - 矩形底板 + 环形圆柱
    // 创建底板
    TopoDS_Shape base =
        BRepPrimAPI_MakeBox(gp_Pnt(-(params.diameter) / 2 - params.thickness,
                                   -params.width / 2, 0),
                            params.diameter + params.thickness * 2,
                            params.width, params.thickness)
            .Shape();

    // 创建环形圆柱
    TopoDS_Shape outerCyl =
        BRepPrimAPI_MakeCylinder(
            gp_Ax2(gp_Pnt(0, -params.width / 2,
                          params.thickness + (params.diameter / 2) +
                              params.thickness),
                   gp::DY()),
            params.diameter / 2 + params.thickness, params.width)
            .Shape();
    TopoDS_Shape innerCyl =
        BRepPrimAPI_MakeCylinder(
            gp_Ax2(gp_Pnt(0, -params.width / 2,
                          params.thickness + (params.diameter / 2) +
                              params.thickness),
                   gp::DY()),
            params.diameter / 2, params.width)
            .Shape();
    TopoDS_Shape ring = BRepAlgoAPI_Cut(outerCyl, innerCyl).Shape();

    // 合并底板和环形圆柱
    return BRepAlgoAPI_Fuse(base, ring).Shape();
  }
  case cable_clamp_type::LINEAR: {
    // 一字式夹具 - 长条矩形
    // 创建底板
    TopoDS_Shape base =
        BRepPrimAPI_MakeBox(
            gp_Pnt(-(params.diameter + params.thickness * 2) * 1.5,
                   -params.width / 2, 0),
            (params.diameter + params.thickness * 2) * 3, params.width,
            params.thickness)
            .Shape();

    // 创建三个环形圆柱
    double spacing = params.diameter + params.thickness * 2;
    TopoDS_Shape rings;
    for (int i = -1; i <= 1; i++) {
      gp_Pnt center(i * spacing, -params.width / 2,
                    params.thickness + (params.diameter / 2) +
                        params.thickness);
      TopoDS_Shape outerCyl =
          BRepPrimAPI_MakeCylinder(gp_Ax2(center, gp::DY()),
                                   params.diameter / 2 + params.thickness,
                                   params.width)
              .Shape();
      TopoDS_Shape innerCyl =
          BRepPrimAPI_MakeCylinder(gp_Ax2(center, gp::DY()),
                                   params.diameter / 2, params.width)
              .Shape();
      TopoDS_Shape ring = BRepAlgoAPI_Cut(outerCyl, innerCyl).Shape();

      if (rings.IsNull()) {
        rings = ring;
      } else {
        rings = BRepAlgoAPI_Fuse(rings, ring).Shape();
      }
    }

    // 合并底板和环形圆柱
    return BRepAlgoAPI_Fuse(base, rings).Shape();
  }
  case cable_clamp_type::CONTACT_TRIPLE: {
    // 品字接触式 - 底板 + 带三个圆孔的三角形柱
    // 创建底板
    double circleDiameter = params.diameter + params.thickness * 2;
    double sideLength = circleDiameter * (1 + 2.0 / std::sqrt(3));
    double height = std::sqrt(3.0) * sideLength / 2.0;

    TopoDS_Shape base =
        BRepPrimAPI_MakeBox(gp_Pnt(-sideLength / 2, -params.width / 2, 0),
                            sideLength, params.width, params.thickness)
            .Shape();

    // 创建三角形柱
    gp_Pnt p1(0, -params.width / 2, height + params.thickness);
    gp_Pnt p2(-sideLength / 2, -params.width / 2, params.thickness);
    gp_Pnt p3(sideLength / 2, -params.width / 2, params.thickness);

    BRepBuilderAPI_MakePolygon poly;
    poly.Add(p1);
    poly.Add(p2);
    poly.Add(p3);
    poly.Close();
    TopoDS_Face triangleFace = BRepBuilderAPI_MakeFace(poly.Wire()).Face();
    TopoDS_Shape prism =
        BRepPrimAPI_MakePrism(triangleFace, gp_Vec(0, params.width, 0)).Shape();

    // 添加圆角 - 只处理平行于Y轴的边
    BRepFilletAPI_MakeFillet fillet(prism);
    double filletRadius = sideLength * 0.12; // 圆角半径为边长的1/10

    // 获取所有边
    TopExp_Explorer edgeExp(prism, TopAbs_EDGE);
    for (; edgeExp.More(); edgeExp.Next()) {
      TopoDS_Edge edge = TopoDS::Edge(edgeExp.Current());

      // 获取边的两个顶点
      TopoDS_Vertex v1, v2;
      TopExp::Vertices(edge, v1, v2);
      gp_Pnt p1 = BRep_Tool::Pnt(v1);
      gp_Pnt p2 = BRep_Tool::Pnt(v2);

      // 检查边是否平行于Y轴
      if (Abs(p1.X() - p2.X()) < Precision::Confusion() &&
          Abs(p1.Z() - p2.Z()) < Precision::Confusion()) {
        fillet.Add(filletRadius, edge);
      }
    }

    prism = fillet.Shape();

    std::array<gp_Pnt, 3> holePoints;
    double offset = circleDiameter / 2 / std::sqrt(3.0); // 圆心到三角形边的距离
    double holeRadius = params.diameter / 2;

    // 上方圆的圆心 (C1)
    holePoints[0] =
        gp_Pnt(0, -params.width, (3 * offset) + params.thickness * 2);

    // 下方左侧圆的圆心 (C2)
    holePoints[1] = gp_Pnt(-circleDiameter / 2.0 + params.thickness,
                           -params.width, offset + params.thickness * 1.8);

    // 下方右侧圆的圆心 (C3)
    holePoints[2] = gp_Pnt(circleDiameter / 2.0 - params.thickness,
                           -params.width, offset + params.thickness * 1.8);

    // 创建三个圆孔
    gp_Pnt hole1 = holePoints[0];
    gp_Pnt hole2 = holePoints[1];
    gp_Pnt hole3 = holePoints[2];

    TopoDS_Shape holeShape1 =
        BRepPrimAPI_MakeCylinder(gp_Ax2(hole1, gp::DY()), holeRadius,
                                 params.width * 2)
            .Shape();
    TopoDS_Shape holeShape2 =
        BRepPrimAPI_MakeCylinder(gp_Ax2(hole2, gp::DY()), holeRadius,
                                 params.width * 2)
            .Shape();
    TopoDS_Shape holeShape3 =
        BRepPrimAPI_MakeCylinder(gp_Ax2(hole3, gp::DY()), holeRadius,
                                 params.width * 2)
            .Shape();

    TopoDS_Shape withHoles = BRepAlgoAPI_Cut(prism, holeShape1).Shape();
    withHoles = BRepAlgoAPI_Cut(withHoles, holeShape2).Shape();
    withHoles = BRepAlgoAPI_Cut(withHoles, holeShape3).Shape();

    // 合并底板和带孔三角形柱
    return BRepAlgoAPI_Fuse(base, withHoles).Shape();
  }
  case cable_clamp_type::SEPARATE_TRIPLE: {
    // 品字分离式 - 底板 + 三个环形圆柱
    // 品字接触式 - 底板 + 带三个圆孔的三角形柱
    // 创建底板
    double circleDiameter = params.diameter + params.thickness * 2;
    double sideLength = circleDiameter * (1 + 2.0 / std::sqrt(3));
    double height = std::sqrt(3.0) * sideLength / 2.0;

    TopoDS_Shape base =
        BRepPrimAPI_MakeBox(gp_Pnt(-sideLength / 2, -params.width / 2, 0),
                            sideLength, params.width, params.thickness)
            .Shape();

    // 创建三角形柱
    gp_Pnt p1(0, -params.width / 2, height + params.thickness);
    gp_Pnt p2(-sideLength / 2, -params.width / 2, params.thickness);
    gp_Pnt p3(sideLength / 2, -params.width / 2, params.thickness);

    BRepBuilderAPI_MakePolygon poly;
    poly.Add(p1);
    poly.Add(p2);
    poly.Add(p3);
    poly.Close();
    TopoDS_Face triangleFace = BRepBuilderAPI_MakeFace(poly.Wire()).Face();
    TopoDS_Shape prism =
        BRepPrimAPI_MakePrism(triangleFace, gp_Vec(0, params.width, 0)).Shape();

    // 添加圆角 - 只处理平行于Y轴的边
    BRepFilletAPI_MakeFillet fillet(prism);
    double filletRadius = sideLength * 0.12; // 圆角半径为边长的1/10

    // 获取所有边
    TopExp_Explorer edgeExp(prism, TopAbs_EDGE);
    for (; edgeExp.More(); edgeExp.Next()) {
      TopoDS_Edge edge = TopoDS::Edge(edgeExp.Current());

      // 获取边的两个顶点
      TopoDS_Vertex v1, v2;
      TopExp::Vertices(edge, v1, v2);
      gp_Pnt p1 = BRep_Tool::Pnt(v1);
      gp_Pnt p2 = BRep_Tool::Pnt(v2);

      // 检查边是否平行于Y轴
      if (Abs(p1.X() - p2.X()) < Precision::Confusion() &&
          Abs(p1.Z() - p2.Z()) < Precision::Confusion()) {
        fillet.Add(filletRadius, edge);
      }
    }

    prism = fillet.Shape();

    std::array<gp_Pnt, 3> holePoints;
    double offset = circleDiameter / 2 / std::sqrt(3.0); // 圆心到三角形边的距离
    double holeRadius = params.diameter / 2;

    // 上方圆的圆心 (C1)
    holePoints[0] =
        gp_Pnt(0, -params.width, (3 * offset) + params.thickness * 2);

    // 下方左侧圆的圆心 (C2)
    holePoints[1] = gp_Pnt(-circleDiameter / 2.0 + params.thickness / 1.5,
                           -params.width, offset + params.thickness * 1.5);

    // 下方右侧圆的圆心 (C3)
    holePoints[2] = gp_Pnt(circleDiameter / 2.0 - params.thickness / 1.5,
                           -params.width, offset + params.thickness * 1.5);

    // 创建三个圆孔
    gp_Pnt hole1 = holePoints[0];
    gp_Pnt hole2 = holePoints[1];
    gp_Pnt hole3 = holePoints[2];

    TopoDS_Shape holeShape1 =
        BRepPrimAPI_MakeCylinder(gp_Ax2(hole1, gp::DY()), holeRadius,
                                 params.width * 2)
            .Shape();
    TopoDS_Shape holeShape2 =
        BRepPrimAPI_MakeCylinder(gp_Ax2(hole2, gp::DY()), holeRadius,
                                 params.width * 2)
            .Shape();
    TopoDS_Shape holeShape3 =
        BRepPrimAPI_MakeCylinder(gp_Ax2(hole3, gp::DY()), holeRadius,
                                 params.width * 2)
            .Shape();

    TopoDS_Shape withHoles = BRepAlgoAPI_Cut(prism, holeShape1).Shape();
    withHoles = BRepAlgoAPI_Cut(withHoles, holeShape2).Shape();
    withHoles = BRepAlgoAPI_Cut(withHoles, holeShape3).Shape();

    // 合并底板和带孔三角形柱
    return BRepAlgoAPI_Fuse(base, withHoles).Shape();
  }
  default:
    throw Standard_ConstructionError("Unknown cable clamp type");
  }
}

TopoDS_Shape create_cable_clamp(const cable_clamp_params &params,
                                const gp_Pnt &position, const gp_Dir &normal,
                                const gp_Dir &xDir) {
  // 首先创建标准方向的夹具
  TopoDS_Shape clamp = create_cable_clamp(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(clamp, transformation);
  return transform.Shape();
}

TopoDS_Shape create_cable_pole(const cable_pole_params &params) {
  // 参数验证
  if (params.length <= 0)
    throw Standard_ConstructionError("Pole length must be positive");
  if (params.width <= 0)
    throw Standard_ConstructionError("Pole width must be positive");
  if (params.thickness <= 0)
    throw Standard_ConstructionError("Pole thickness must be positive");
  if (params.thickness >= params.width / 2)
    throw Standard_ConstructionError("Thickness must be less than half width");
  if (params.fixedLegLength < 0)
    throw Standard_ConstructionError("Fixed leg length must be non-negative");
  if (params.fixedLegWidth < 0)
    throw Standard_ConstructionError("Fixed leg width must be non-negative");

  TopoDS_Shape pole;

  // 创建立柱主体
  if (params.radius > 0) {
    // 圆弧立柱
    if (params.arcAngle <= 0 || params.arcAngle > 2 * M_PI)
      throw Standard_ConstructionError("Arc angle must be in (0, 2PI]");

    // 创建圆弧路径
    gp_Ax2 arcAxis(gp_Pnt(0, 0, params.radius), gp_Dir(0, -1, 0));
    gp_Circ arc(arcAxis, params.radius);
    Handle(Geom_Curve) circle = new Geom_Circle(arc);
    TopoDS_Edge path =
        BRepBuilderAPI_MakeEdge(circle, 0, params.arcAngle).Edge();

    // 显式构建路径Wire并检查闭合性
    BRepBuilderAPI_MakeWire wireMaker;
    wireMaker.Add(path);
    if (!wireMaker.IsDone()) {
      throw Standard_ConstructionError("Failed to create arc path wire");
    }
    TopoDS_Wire wire = wireMaker.Wire();

    // 创建矩形截面
    gp_Pnt p1(0, -params.width / 2, 0);
    gp_Pnt p2(0, -params.width / 2, params.thickness);
    gp_Pnt p3(0, params.width / 2, params.thickness);
    gp_Pnt p4(0, params.width / 2, 0);
    TopoDS_Wire profile =
        BRepBuilderAPI_MakePolygon(p1, p2, p3, p4, Standard_True).Wire();

    // 扫掠成圆弧立柱
    BRepOffsetAPI_MakePipeShell pipeMaker(wire);
    pipeMaker.Add(profile);
    pipeMaker.SetMode(Standard_True);
    pipeMaker.SetTolerance(1e-6); // 设置更高精度
    pipeMaker.Build();

    // 添加详细错误检查
    if (!pipeMaker.IsDone()) {
      std::string msg = "PipeShell error: ";
      switch (pipeMaker.GetStatus()) {
      case BRepBuilderAPI_PlaneNotIntersectGuide:
        msg += "Profile plane does not intersect guide";
        break;
      default:
        msg += "Unknown error";
        break;
      }
      throw Standard_ConstructionError(msg.c_str());
    }
    if (!pipeMaker.MakeSolid()) {
      throw std::runtime_error("Failed to create a solid object from sweep");
    }

    pole = pipeMaker.Shape();
  } else {
    // 直立柱
    gp_Pnt p1(-params.width / 2, -params.thickness / 2, 0);
    gp_Pnt p2(-params.width / 2, params.thickness / 2, 0);
    gp_Pnt p3(params.width / 2, params.thickness / 2, 0);
    gp_Pnt p4(params.width / 2, -params.thickness / 2, 0);
    TopoDS_Face face = BRepBuilderAPI_MakeFace(
        BRepBuilderAPI_MakePolygon(p1, p2, p3, p4, Standard_True).Wire());
    pole = BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, params.length)).Shape();
  }

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);
  builder.Add(compound, pole);

  // 创建固定肢
  if (params.fixedLegLength > 0 && params.fixedLegWidth > 0) {
    for (const auto &point : params.mountPoints) {
      if (params.radius > 0) {
        // 计算安装点处的径向方向
        gp_Vec radialDir(point.X(), 0, point.Z() - params.radius);
        if (radialDir.Magnitude() < Precision::Confusion()) {
          throw Standard_ConstructionError(
              "Mount point coincides with circle center");
        }
        radialDir.Normalize();

        // 计算切线方向（与径向垂直且沿圆弧方向）
        gp_Vec tangentDir = radialDir.Crossed(gp_Vec(0, 1, 0));
        tangentDir.Normalize();

        // 确定延伸方向（根据是否需要向外延伸）
        bool isOuterSide = (point.X() * radialDir.X() +
                            (point.Z() - params.radius) * radialDir.Z()) > 0;
        double extension = isOuterSide ? 1.0 : -1.0;
        double fixedThickness = params.thickness / 2;

        // 构建固定肢截面（在切线-Y平面）
        gp_Pnt basePoint = gp_Pnt(point.X(), point.Y(), point.Z());
        double halfLength = params.fixedLegLength / 2;
        double halfThick = fixedThickness / 2;
        double halfWidth = params.fixedLegWidth / 2;

        // 截面点计算（矩形截面）
        gp_Pnt p1 = basePoint.Translated(tangentDir * (-halfWidth) +
                                         radialDir * (-fixedThickness) +
                                         gp_Vec(0, -halfLength, 0));
        gp_Pnt p2 = basePoint.Translated(tangentDir * (halfWidth) +
                                         radialDir * (-fixedThickness) +
                                         gp_Vec(0, -halfLength, 0));
        gp_Pnt p3 =
            basePoint.Translated(tangentDir * (halfWidth) + radialDir * (0) +
                                 gp_Vec(0, -halfLength, 0));
        gp_Pnt p4 =
            basePoint.Translated(tangentDir * (-halfWidth) + radialDir * (0) +
                                 gp_Vec(0, -halfLength, 0));

        gp_Vec extrudeDir = gp_Vec(0, extension, 0) * params.fixedLegLength;

        // 修正3：调整挤出方向为Y轴方向
        TopoDS_Shape leg =
            BRepPrimAPI_MakePrism(
                BRepBuilderAPI_MakeFace(
                    BRepBuilderAPI_MakePolygon(p1, p2, p3, p4, Standard_True)),
                extrudeDir // Y方向挤出厚度
                )
                .Shape();

        // 修正4：安装孔位置调整到固定肢中心
        gp_Pnt holeCenter =
            basePoint.Translated(radialDir * (-params.thickness));
        TopoDS_Shape hole = BRepPrimAPI_MakeCylinder(
                                gp_Ax2(holeCenter, radialDir),
                                params.fixedLegWidth / 4, params.thickness * 2)
                                .Shape();

        // 布尔运算切割孔洞
        leg = BRepAlgoAPI_Cut(leg, hole).Shape();

        builder.Add(compound, leg);
      } else {
        // 判断安装点在立柱的哪一侧
        bool isRightSide = point.X() > 0;
        double legDirection = isRightSide ? 1.0 : -1.0;

        double fixedThickness = params.thickness / 2;

        // 创建固定肢矩形
        gp_Pnt p1(point.X() + legDirection * params.fixedLegLength / 2,
                  point.Y() - fixedThickness / 2,
                  point.Z() - params.fixedLegWidth / 2);
        gp_Pnt p2(point.X() - legDirection * params.fixedLegLength / 2,
                  point.Y() - fixedThickness / 2,
                  point.Z() - params.fixedLegWidth / 2);
        gp_Pnt p3(point.X() - legDirection * params.fixedLegLength / 2,
                  point.Y() + fixedThickness / 2,
                  point.Z() - params.fixedLegWidth / 2);
        gp_Pnt p4(point.X() + legDirection * params.fixedLegLength / 2,
                  point.Y() + fixedThickness / 2,
                  point.Z() - params.fixedLegWidth / 2);

        TopoDS_Face legFace = BRepBuilderAPI_MakeFace(
            BRepBuilderAPI_MakePolygon(p1, p2, p3, p4, Standard_True).Wire());
        TopoDS_Shape leg =
            BRepPrimAPI_MakePrism(legFace, gp_Vec(0, 0, params.fixedLegWidth))
                .Shape();

        // 合并到主体
        leg = BRepAlgoAPI_Fuse(pole, leg).Shape();

        // 创建安装孔
        gp_Pnt holePos(point.X(), point.Y() - params.thickness, point.Z());
        TopoDS_Shape hole = BRepPrimAPI_MakeCylinder(gp_Ax2(holePos, gp::DY()),
                                                     params.fixedLegWidth / 4,
                                                     params.thickness * 2)
                                .Shape();
        leg = BRepAlgoAPI_Cut(leg, hole).Shape();

        builder.Add(compound, leg);
      }
    }
  }

  return compound;
}

TopoDS_Shape create_cable_pole(const cable_pole_params &params,
                               const gp_Pnt &position,
                               const gp_Dir &direction) {
  // 创建标准方向的立柱
  TopoDS_Shape pole = create_cable_pole(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ());
  gp_Ax3 targetAx3(position, direction);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(pole, transformation);
  return transform.Shape();
}

TopoDS_Shape create_ground_flat_iron(const ground_flat_iron_params &params) {
  // 参数验证
  if (params.length <= 0)
    throw Standard_ConstructionError("Length must be positive");
  if (params.height <= 0)
    throw Standard_ConstructionError("Height must be positive");
  if (params.thickness <= 0)
    throw Standard_ConstructionError("Thickness must be positive");
  if (params.thickness >= params.height)
    throw Standard_ConstructionError("Thickness must be less than height");

  // 创建扁铁截面轮廓
  gp_Pnt p1(-params.length / 2, -params.height / 2, 0);
  gp_Pnt p2(params.length / 2, -params.height / 2, 0);
  gp_Pnt p3(params.length / 2, params.height / 2, 0);
  gp_Pnt p4(-params.length / 2, params.height / 2, 0);

  BRepBuilderAPI_MakePolygon polyMaker;
  polyMaker.Add(p1);
  polyMaker.Add(p2);
  polyMaker.Add(p3);
  polyMaker.Add(p4);
  polyMaker.Add(p1);
  TopoDS_Wire wire = polyMaker.Wire();

  // 创建扁铁实体
  TopoDS_Face face = BRepBuilderAPI_MakeFace(wire).Face();
  TopoDS_Shape flatIron =
      BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, params.thickness)).Shape();

  return flatIron;
}

TopoDS_Shape create_ground_flat_iron(const ground_flat_iron_params &params,
                                     const gp_Pnt &position,
                                     const gp_Dir &normal, const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 创建标准方向的扁铁
  TopoDS_Shape flatIron = create_ground_flat_iron(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(flatIron, transformation);
  return transform.Shape();
}

TopoDS_Shape create_embedded_part(const embedded_part_params &params) {
  // 参数验证
  if (params.length <= 0)
    throw Standard_ConstructionError("Length must be positive");
  if (params.radius <= 0)
    throw Standard_ConstructionError("Radius must be positive");
  if (params.height <= 0)
    throw Standard_ConstructionError("Height must be positive");
  if (params.materialRadius <= 0)
    throw Standard_ConstructionError("Material radius must be positive");
  if (params.lowerLength <= 0)
    throw Standard_ConstructionError("Lower length must be positive");
  if (params.materialRadius >= params.radius)
    throw Standard_ConstructionError(
        "Material radius must be less than hook radius");

  // 创建伸部分
  gp_Pnt pathStart(0, -params.materialRadius / 2, -params.height);
  gp_Pnt pathMid(0, -params.materialRadius / 2, 0);              // 路径起点
  gp_Pnt arcStart(params.length, -params.materialRadius / 2, 0); // 路径终点

  gp_Pnt arcEnd(arcStart.X(), arcStart.Y(), arcStart.Z() - params.radius * 2);
  gp_Pnt arcCenter(arcStart.X() + params.radius, arcStart.Y(),
                   arcStart.Z() - params.radius);
  gp_Pnt pathEnd(arcEnd.X() - params.lowerLength, arcEnd.Y(),
                 arcEnd.Z()); // 路径终点

  TopoDS_Edge edge1 = BRepBuilderAPI_MakeEdge(pathStart, pathMid).Edge();
  TopoDS_Edge edge2 = BRepBuilderAPI_MakeEdge(pathMid, arcStart).Edge();
  Handle(Geom_TrimmedCurve) arc =
      GC_MakeArcOfCircle(arcStart, arcCenter, arcEnd).Value();
  TopoDS_Edge arcEdge = BRepBuilderAPI_MakeEdge(arc).Edge();
  TopoDS_Edge edge3 = BRepBuilderAPI_MakeEdge(arcEnd, pathEnd).Edge();

  BRepBuilderAPI_MakeWire wireMaker(edge1, edge2);
  wireMaker.Add(arcEdge);
  wireMaker.Add(edge3);
  TopoDS_Wire pathWire = wireMaker.Wire();

  // 创建圆形截面（与圆柱相同半径）
  gp_Ax2 sectionAxis(pathStart, gp_Dir(0, 0, -1));
  BRepBuilderAPI_MakeWire circleMaker;
  circleMaker.Add(
      BRepBuilderAPI_MakeEdge(gp_Circ(sectionAxis, params.materialRadius))
          .Edge());
  TopoDS_Wire sectionWire = circleMaker.Wire();

  // 沿路径扫掠生成水平延伸
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.Add(sectionWire);
  pipeMaker.SetMode(Standard_True);
  pipeMaker.SetTransitionMode(BRepBuilderAPI_RightCorner);
  pipeMaker.Build();
  if (!pipeMaker.IsDone()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }
  if (!pipeMaker.MakeSolid()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }

  return pipeMaker.Shape();
}

TopoDS_Shape create_embedded_part(const embedded_part_params &params,
                                  const gp_Pnt &position, const gp_Dir &normal,
                                  const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 创建标准方向的预埋件
  TopoDS_Shape embeddedPart = create_embedded_part(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(embeddedPart, transformation);
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
  double arcHeight =
      params.radius - sqrt(pow(params.radius, 2) - pow(half_chord, 2));

  // 创建伸部分
  gp_Pnt pathStart(0, -params.radius / 2, half_chord);
  gp_Pnt arcStart(params.length - arcHeight, -params.radius / 2,
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

TopoDS_Shape create_lifting_eye(const lifting_eye_params &params) {
  // 参数验证
  if (params.height <= 0)
    throw Standard_ConstructionError("Height must be positive");
  if (params.ringRadius <= 0)
    throw Standard_ConstructionError("Ring radius must be positive");
  if (params.pipeDiameter <= 0)
    throw Standard_ConstructionError("Pipe diameter must be positive");
  if (params.pipeDiameter >= 2 * params.ringRadius)
    throw Standard_ConstructionError(
        "Pipe diameter must be less than ring diameter");

  // 创建吊臂部分（垂直圆柱）
  gp_Ax2 armAxis(gp_Pnt(0, 0, -params.height), gp::DZ());
  TopoDS_Shape arm =
      BRepPrimAPI_MakeCylinder(armAxis, params.pipeDiameter / 2, params.height)
          .Shape();

  // 创建圆环部分
  gp_Ax2 ringAxis(gp_Pnt(0, 0, -params.height - params.ringRadius), gp::DX());
  TopoDS_Shape ring = BRepPrimAPI_MakeTorus(ringAxis, params.ringRadius,
                                            params.pipeDiameter / 2)
                          .Shape();

  // 合并吊臂和圆环
  TopoDS_Shape liftingEye = BRepAlgoAPI_Fuse(arm, ring).Shape();

  return liftingEye;
}

TopoDS_Shape create_lifting_eye(const lifting_eye_params &params,
                                const gp_Pnt &position, const gp_Dir &normal,
                                const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 创建标准方向的吊攀
  TopoDS_Shape liftingEye = create_lifting_eye(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(liftingEye, transformation);
  return transform.Shape();
}

/**
 * @brief 创建矩形截面连接段
 * @param length 长度（X方向）
 * @param width 宽度（Y方向）
 * @param height 高度（Z方向）
 * @param wallThickness 壁厚
 * @param isOuter 是否创建外壁
 * @return TopoDS_Shape 连接段形状
 */
TopoDS_Shape create_rectangular_section(double length, double width,
                                        double height, double wallThickness,
                                        double topThickness,
                                        double bottomThickness, bool isOuter) {
  double halfWidth = width / 2;
  double heightOffset = 0;
  double realHeight = height;

  if (isOuter) {
    halfWidth += wallThickness;
    heightOffset = -bottomThickness;
    realHeight += topThickness + bottomThickness;
  }

  gp_Pnt p1(0, -halfWidth, heightOffset);
  gp_Pnt p2(length, -halfWidth, heightOffset);
  gp_Pnt p3(length, halfWidth, heightOffset);
  gp_Pnt p4(0, halfWidth, heightOffset);

  BRepBuilderAPI_MakeWire wireMaker;
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p1));

  TopoDS_Face face = BRepBuilderAPI_MakeFace(wireMaker.Wire());
  gp_Vec vec(0, 0, realHeight);
  return BRepPrimAPI_MakePrism(face, vec).Shape();
}

/**
 * @brief 创建圆形截面连接段
 * @param length 长度（X方向）
 * @param radius 半径
 * @param wallThickness 壁厚
 * @param isOuter 是否创建外壁
 * @return TopoDS_Shape 连接段形状
 */
TopoDS_Shape create_circular_section(double length, double radius,
                                     double wallThickness, bool isOuter) {
  double actualRadius = isOuter ? radius + wallThickness : radius;

  gp_Ax2 axis(gp_Pnt(0, 0, radius), gp_Dir(1, 0, 0));
  TopoDS_Shape cylinder =
      BRepPrimAPI_MakeCylinder(axis, actualRadius, length).Shape();
  return cylinder;
}

/**
 * @brief 创建马蹄形截面连接段
 * @param length 长度（X方向）
 * @param width 宽度（Y方向）
 * @param height 高度（Z方向）
 * @param arcHeight 拱高
 * @param wallThickness 壁厚
 * @param isOuter 是否创建外壁
 * @return TopoDS_Shape 连接段形状
 */
TopoDS_Shape create_horseshoe_section(double length, double width,
                                      double height, double arcHeight,
                                      double wallThickness, bool isOuter) {
  // 计算尺寸参数
  double halfWidth = width / 2.0;
  double baseHeight = height - arcHeight;
  double heightOffset = 0;

  if (isOuter) {
    halfWidth += wallThickness;
    baseHeight += wallThickness;
    arcHeight += wallThickness;
    heightOffset = -wallThickness;
  }

  // 创建截面轮廓线
  BRepBuilderAPI_MakeWire sectionWire;

  // 底部直线段
  gp_Pnt p1(0, -halfWidth, heightOffset);
  gp_Pnt p2(0, halfWidth, heightOffset);
  sectionWire.Add(BRepBuilderAPI_MakeEdge(p1, p2));

  // 右侧垂直线段
  gp_Pnt p3(0, halfWidth, baseHeight + heightOffset);
  sectionWire.Add(BRepBuilderAPI_MakeEdge(p2, p3));

  // 顶部圆弧 (使用三点构造圆弧)
  gp_Pnt arcStart(0, halfWidth, baseHeight + heightOffset);
  gp_Pnt arcMid(0, 0, baseHeight + arcHeight + heightOffset); // 拱顶中点
  gp_Pnt arcEnd(0, -halfWidth, baseHeight + heightOffset);

  Handle(Geom_TrimmedCurve) topArc =
      GC_MakeArcOfCircle(arcStart, arcMid, arcEnd).Value();
  sectionWire.Add(BRepBuilderAPI_MakeEdge(topArc));

  // 左侧垂直线段
  gp_Pnt p4(0, -halfWidth, heightOffset);
  sectionWire.Add(BRepBuilderAPI_MakeEdge(arcEnd, p4));

  // 创建面并拉伸
  TopoDS_Face sectionFace = BRepBuilderAPI_MakeFace(sectionWire.Wire());
  return BRepPrimAPI_MakePrism(sectionFace, gp_Vec(length, 0, 0)).Shape();
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

/**
 * @brief 创建直线井
 * @param params 井参数
 * @return TopoDS_Shape 井形状
 */
TopoDS_Shape create_straight_well(const tunnel_well_params &params) {
  // 1. 创建垫层
  double cushionTotalWidth =
      params.width + 2 * (params.outerWallThickness + params.cushionExtension);
  double cushionTotalLength =
      params.length + 2 * (params.outerWallThickness + params.cushionExtension);

  TopoDS_Shape cushion =
      BRepPrimAPI_MakeBox(
          gp_Pnt(-cushionTotalLength / 2, -cushionTotalWidth / 2,
                 -params.cushionThickness - params.bottomThickness),
          cushionTotalLength, cushionTotalWidth, params.cushionThickness)
          .Shape();

  // 2. 创建井身外壁
  double outerLength = params.length + 2 * params.outerWallThickness;
  double outerWidth = params.width + 2 * params.outerWallThickness;
  double outerHeight =
      params.height + params.topThickness + params.bottomThickness;

  TopoDS_Shape outerWell =
      BRepPrimAPI_MakeBox(
          gp_Pnt(-outerLength / 2, -outerWidth / 2, -params.bottomThickness),
          outerLength, outerWidth, outerHeight)
          .Shape();

  // 3. 创建井身内腔
  TopoDS_Shape innerWell =
      BRepPrimAPI_MakeBox(gp_Pnt(-params.length, -params.width / 2, 0),
                          params.length * 2, params.width, params.height)
          .Shape();

  // 4. 从外壁中减去内腔
  TopoDS_Shape well = BRepAlgoAPI_Cut(outerWell, innerWell).Shape();

  // 5. 合并垫层和井身
  return BRepAlgoAPI_Fuse(cushion, well).Shape();
}

TopoDS_Shape create_straight_tunnel_well(const tunnel_well_params &params) {
  // 参数验证
  if (params.length <= 0 || params.width <= 0 || params.height <= 0) {
    throw Standard_ConstructionError("Well dimensions must be positive");
  }
  if (params.topThickness < 0 || params.bottomThickness < 0) {
    throw Standard_ConstructionError("Thickness must be non-negative");
  }
  TopoDS_Shape result;

  // 2. 创建左连接段
  TopoDS_Shape leftTunnel;
  switch (params.leftSectionType) {
  case connection_section_style::RECTANGULAR:
    leftTunnel = create_rectangular_section(
        params.leftLength, params.leftWidth, params.leftHeight,
        params.outerWallThickness, params.outerWallThickness,
        params.outerWallThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    leftTunnel = create_horseshoe_section(
        params.leftLength, params.leftWidth, params.leftHeight,
        params.leftArcHeight, params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    leftTunnel =
        create_circular_section(params.leftLength, params.leftHeight / 2,
                                params.outerWallThickness, true);
    break;
  }

  // 移动左连接段到正确位置
  gp_Trsf leftTrsf;
  leftTrsf.SetTranslation(gp_Vec(
      -params.leftLength - params.radius - params.outerWallThickness, 0, 0));
  leftTunnel = BRepBuilderAPI_Transform(leftTunnel, leftTrsf).Shape();

  // 3. 创建右连接段
  TopoDS_Shape rightTunnel;
  switch (params.rightSectionType) {
  case connection_section_style::RECTANGULAR:
    rightTunnel = create_rectangular_section(
        params.rightLength, params.rightWidth, params.rightHeight,
        params.outerWallThickness, params.outerWallThickness,
        params.outerWallThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    rightTunnel = create_horseshoe_section(
        params.rightLength, params.rightWidth, params.rightHeight,
        params.rightArcHeight, params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    rightTunnel =
        create_circular_section(params.rightLength, params.rightHeight / 2,
                                params.outerWallThickness, true);
    break;
  }

  // 移动右连接段到正确位置
  gp_Trsf rightTrsf;
  rightTrsf.SetTranslation(
      gp_Vec(params.radius + params.outerWallThickness, 0, 0));
  rightTunnel = BRepBuilderAPI_Transform(rightTunnel, rightTrsf).Shape();

  // 5. 合并所有部分
  TopoDS_Shape tunnel = BRepAlgoAPI_Fuse(leftTunnel, rightTunnel).Shape();

  // 6. 创建内腔
  TopoDS_Shape innerTunnel;
  switch (params.leftSectionType) {
  case connection_section_style::RECTANGULAR:
    innerTunnel = create_rectangular_section(
        params.leftLength, params.leftWidth, params.leftHeight,
        params.outerWallThickness, params.outerWallThickness,
        params.outerWallThickness, false);
    break;
  case connection_section_style::HORSESHOE:
    innerTunnel = create_horseshoe_section(
        params.leftLength, params.leftWidth, params.leftHeight,
        params.leftArcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerTunnel =
        create_circular_section(params.leftLength, params.leftHeight / 2,
                                params.outerWallThickness, false);
    break;
  }

  innerTunnel = BRepBuilderAPI_Transform(innerTunnel, leftTrsf).Shape();

  TopoDS_Shape innerRightTunnel;
  switch (params.rightSectionType) {
  case connection_section_style::RECTANGULAR:
    innerRightTunnel = create_rectangular_section(
        params.rightLength, params.rightWidth, params.rightHeight,
        params.outerWallThickness, params.outerWallThickness,
        params.outerWallThickness, false);
    break;
  case connection_section_style::HORSESHOE:
    innerRightTunnel = create_horseshoe_section(
        params.rightLength, params.rightWidth, params.rightHeight,
        params.rightArcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerRightTunnel =
        create_circular_section(params.rightLength, params.rightHeight / 2,
                                params.outerWallThickness, false);
    break;
  }

  innerRightTunnel =
      BRepBuilderAPI_Transform(innerRightTunnel, rightTrsf).Shape();

  TopoDS_Shape innerShape =
      BRepAlgoAPI_Fuse(innerTunnel, innerRightTunnel).Shape();

  // 7. 从外壁中减去内腔
  TopoDS_Shape well = BRepAlgoAPI_Cut(tunnel, innerShape).Shape();

  {
    // 创建过渡段
    TopoDS_Shape transition = create_transition_section(params, true);
    TopoDS_Shape innerTransition = create_transition_section(params, false);

    // 4. 创建竖井段
    double wellOuterRadius = params.radius + params.outerWallThickness;
    double wellHeight =
        params.height + params.topThickness + params.bottomThickness;

    gp_Ax2 axis(gp_Pnt(0, 0, params.outerWallThickness), gp_Dir(0, 0, 1));

    TopoDS_Shape outerCylinder =
        BRepPrimAPI_MakeCylinder(axis, wellOuterRadius, wellHeight).Shape();

    TopoDS_Shape innerCylinder =
        BRepPrimAPI_MakeCylinder(axis, params.radius, params.height * 2)
            .Shape();
    transition = BRepAlgoAPI_Fuse(transition, outerCylinder).Shape();
    transition = BRepAlgoAPI_Cut(transition, innerTransition).Shape();
    transition = BRepAlgoAPI_Cut(transition, innerCylinder).Shape();

    well = BRepAlgoAPI_Fuse(well, transition).Shape();
  }
  // 8. 合并垫层和井身
  return well;
}

/**
 * @brief 创建隧道井
 * @param params 井参数
 * @return TopoDS_Shape 井形状
 */
TopoDS_Shape create_tunnel_well(const tunnel_well_params &params) {
  switch (params.type) {
  case tunnel_well_type::STRAIGHT:
    return create_straight_well(params);
  case tunnel_well_type::STRAIGHT_TUNNEL:
    return create_straight_tunnel_well(params);
  default:
    return TopoDS_Shape(); // 返回空形状
  }
}

TopoDS_Shape create_tunnel_well(const tunnel_well_params &params,
                                const gp_Pnt &position, const gp_Dir &direction,
                                const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的井
  TopoDS_Shape well = create_tunnel_well(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(well, transformation);
  return transform.Shape();
}

TopoDS_Shape create_corner_well(double leftLength, double rightLength,
                                double baseZ, double realHeight,
                                const gp_Pnt &arcCenter_, double outerRadius,
                                double innerRadius, double theta) {
  gp_Pnt arcCenter(arcCenter_.X(), arcCenter_.Y(), baseZ);
  double startAngle = M_PI / 2;
  double endAngle = M_PI - (2 * theta) + M_PI / 2;
  // 关键点计算
  gp_Pnt outerStart = ElCLib::CircleValue(
      startAngle, gp_Ax2(arcCenter, gp_Dir(0, 0, -1)), outerRadius);
  outerStart.SetZ(baseZ);
  gp_Pnt outerEnd = ElCLib::CircleValue(
      endAngle, gp_Ax2(arcCenter, gp_Dir(0, 0, -1)), outerRadius);
  outerEnd.SetZ(baseZ);
  gp_Pnt innerStart = ElCLib::CircleValue(
      startAngle, gp_Ax2(arcCenter, gp_Dir(0, 0, -1)), innerRadius);
  outerEnd.SetZ(baseZ);
  gp_Pnt innerEnd = ElCLib::CircleValue(
      endAngle, gp_Ax2(arcCenter, gp_Dir(0, 0, -1)), innerRadius);
  innerEnd.SetZ(baseZ);

  // 计算连接段端点
  gp_Pnt leftOuterStart =
      gp_Pnt(outerStart.X() - leftLength, outerStart.Y(), outerStart.Z());
  gp_Pnt leftInnerStart =
      gp_Pnt(innerStart.X() - leftLength, innerStart.Y(), innerStart.Z());

  gp_Vec segmentVec(gp_Vec(innerEnd, outerEnd));
  gp_Vec rightDir(segmentVec.Y(), -segmentVec.X(), 0.0);
  rightDir.Normalize();

  gp_Pnt rightOuterEnd = outerEnd.Translated(rightDir * (rightLength));
  gp_Pnt rightInnerEnd = innerEnd.Translated(rightDir * (rightLength));

  // 创建弧形段
  Handle(Geom_Circle) outerArc =
      new Geom_Circle(gp_Ax2(arcCenter, gp_Dir(0, 0, -1)), outerRadius);
  TopoDS_Edge outerEdge =
      BRepBuilderAPI_MakeEdge(outerArc, startAngle, endAngle).Edge();

  Handle(Geom_Circle) innerArc =
      new Geom_Circle(gp_Ax2(arcCenter, gp_Dir(0, 0, -1)), innerRadius);
  TopoDS_Edge innerEdge =
      BRepBuilderAPI_MakeEdge(innerArc, startAngle, endAngle).Edge();
  innerEdge.Reverse();

  // 创建弧形段外轮廓
  BRepBuilderAPI_MakeWire outerWire;
  outerWire.Add(outerEdge);
  outerWire.Add(BRepBuilderAPI_MakeEdge(outerEnd, innerEnd).Edge());
  outerWire.Add(innerEdge);
  outerWire.Add(BRepBuilderAPI_MakeEdge(innerStart, outerStart).Edge());
  TopoDS_Face arcFace = BRepBuilderAPI_MakeFace(outerWire.Wire()).Face();

  // 创建左连接段
  BRepBuilderAPI_MakeWire leftWire;
  leftWire.Add(BRepBuilderAPI_MakeEdge(leftOuterStart, outerStart).Edge());
  leftWire.Add(BRepBuilderAPI_MakeEdge(outerStart, innerStart).Edge());
  leftWire.Add(BRepBuilderAPI_MakeEdge(innerStart, leftInnerStart).Edge());
  leftWire.Add(BRepBuilderAPI_MakeEdge(leftInnerStart, leftOuterStart).Edge());
  TopoDS_Face leftFace = BRepBuilderAPI_MakeFace(leftWire.Wire()).Face();

  // 创建右连接段
  BRepBuilderAPI_MakeWire rightWire;
  rightWire.Add(BRepBuilderAPI_MakeEdge(outerEnd, rightOuterEnd).Edge());
  rightWire.Add(BRepBuilderAPI_MakeEdge(rightOuterEnd, rightInnerEnd).Edge());
  rightWire.Add(BRepBuilderAPI_MakeEdge(rightInnerEnd, innerEnd).Edge());
  rightWire.Add(BRepBuilderAPI_MakeEdge(innerEnd, outerEnd).Edge());
  TopoDS_Face rightFace = BRepBuilderAPI_MakeFace(rightWire.Wire()).Face();

  // 拉伸所有部分
  TopoDS_Shape arcOuter =
      BRepPrimAPI_MakePrism(arcFace, gp_Vec(0, 0, realHeight)).Shape();
  TopoDS_Shape leftOuter =
      BRepPrimAPI_MakePrism(leftFace, gp_Vec(0, 0, realHeight)).Shape();
  TopoDS_Shape rightOuter =
      BRepPrimAPI_MakePrism(rightFace, gp_Vec(0, 0, realHeight)).Shape();

  // 合并所有部分
  TopoDS_Shape outer = BRepAlgoAPI_Fuse(arcOuter, leftOuter).Shape();
  outer = BRepAlgoAPI_Fuse(outer, rightOuter).Shape();

  return outer;
}

TopoDS_Shape create_corner_well(const corner_well_params &params) {
  const double R = params.cornerRadius + params.width / 2;
  const double theta = params.angle * M_PI / 180.0 / 2; // 转换为半角弧度

  // 圆心坐标计算
  const double arcCenterX = -R * sin(theta); // X轴负方向
  const double arcCenterY = -R * cos(theta); // Y轴负方向
  gp_Pnt arcCenter(arcCenterX, arcCenterY, 0);

  // 外轮廓参数
  double outerRadius =
      params.cornerRadius + params.width + params.wallThickness;
  double innerRadius = params.cornerRadius - params.wallThickness;

  TopoDS_Shape outer = create_corner_well(
      params.leftLength + params.wallThickness,
      params.rightLength + params.wallThickness, -params.bottomThickness,
      params.height + params.topThickness + params.bottomThickness, arcCenter,
      outerRadius, innerRadius, theta);

  // 外轮廓参数
  outerRadius = params.cornerRadius + params.width;
  innerRadius = params.cornerRadius;

  TopoDS_Shape inner = create_corner_well(
      params.leftLength + params.wallThickness,
      params.rightLength + params.wallThickness, 0, params.height, arcCenter,
      outerRadius, innerRadius, theta);

  // 外轮廓参数
  outerRadius = params.cornerRadius + params.width + params.wallThickness +
                params.cushionExtension;
  innerRadius =
      params.cornerRadius - params.wallThickness - params.cushionExtension;

  TopoDS_Shape cushion = create_corner_well(
      params.leftLength + params.wallThickness + params.cushionExtension,
      params.rightLength + params.wallThickness + params.cushionExtension,
      -params.bottomThickness - params.cushionThickness,
      params.cushionThickness, arcCenter, outerRadius, innerRadius, theta);

  // 合并所有部分
  TopoDS_Shape well = BRepAlgoAPI_Cut(outer, inner).Shape();
  well = BRepAlgoAPI_Fuse(well, cushion).Shape();

  return well;
}

TopoDS_Shape create_corner_well(const corner_well_params &params,
                                const gp_Pnt &position, const gp_Dir &direction,
                                const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的转角井
  TopoDS_Shape well = create_corner_well(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(well, transformation);
  return transform.Shape();
}

/**
 * @brief 创建直角三通圆角工作井
 * @param length 直通段长度(mm)
 * @param width 直通段宽度(mm)
 * @param height 直通段高度(mm)
 * @param length1 支线段长度(mm)
 * @param width1 支线段宽度(mm)
 * @param cornerRadius 井转角半径(mm)
 * @return 直角三通圆角工作井的形状
 */
TopoDS_Shape create_three_way_round_working_well_part(
    double length, double width, double height, double length1, double width1,
    double cornerRadius, double zoffset) {
  // 参数校验
  if (length <= 0 || width <= 0 || height <= 0 || length1 <= 0 || width1 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }
  if (cornerRadius <= 0) {
    throw Standard_ConstructionError("圆角半径必须大于0");
  }

  // 1. 计算关键几何参数
  const double halfLength = length / 2;
  const double halfWidth = width / 2;
  const double halfWidth1 = width1 / 2;

  // 2. 定义主直通段四个角点
  const gp_Pnt p1(-halfLength, -halfWidth, zoffset); // 左下角
  const gp_Pnt p2(-halfLength, halfWidth, zoffset);  // 左上角
  const gp_Pnt p3(halfLength, halfWidth, zoffset);   // 右上角
  const gp_Pnt p4(halfLength, -halfWidth, zoffset);  // 右下角

  // 3. 定义支线段端点
  const gp_Pnt p7(-halfWidth1, halfWidth + length1,
                  zoffset);                                  // 支线段左上角点
  const gp_Pnt p8(halfWidth1, halfWidth + length1, zoffset); // 支线段右下角点

  // 4. 计算圆弧关键点（精确几何关系）
  // 右圆弧参数（连接直通段右侧底部与支段底部）
  const gp_Pnt rightArcStart(halfWidth1 + cornerRadius, halfWidth, zoffset);
  const gp_Pnt rightArcEnd(halfWidth1, halfWidth + cornerRadius, zoffset);

  // 左圆弧参数（连接直通段右侧顶部与支段顶部）
  const gp_Pnt leftArcStart(-halfWidth1 - cornerRadius, halfWidth, zoffset);
  const gp_Pnt leftArcEnd(-halfWidth1, halfWidth + cornerRadius, zoffset);

  // 5. 计算圆心位置（Y轴中点）
  // 左圆弧圆心
  const gp_Pnt leftCircleCenter(-halfWidth1 - cornerRadius,
                                halfWidth + cornerRadius, zoffset);

  // 右圆弧圆心
  const gp_Pnt rightCircleCenter(halfWidth1 + cornerRadius,
                                 halfWidth + cornerRadius, zoffset);

  // 6. 构造圆弧几何
  // 左圆弧构造
  gp_Circ leftCircle(gp_Ax2(leftCircleCenter, gp_Dir(0, 0, 1)), cornerRadius);
  Handle(Geom_Circle) leftGeomCircle = new Geom_Circle(leftCircle);
  Standard_Real leftStartParam = ElCLib::Parameter(leftCircle, leftArcStart);
  Standard_Real leftEndParam = ElCLib::Parameter(leftCircle, leftArcEnd);
  TopoDS_Edge leftArc =
      BRepBuilderAPI_MakeEdge(leftGeomCircle, leftStartParam, leftEndParam)
          .Edge();

  // 右圆弧构造
  gp_Circ rightCircle(gp_Ax2(rightCircleCenter, gp_Dir(0, 0, 1)), cornerRadius);
  Handle(Geom_Circle) rightGeomCircle = new Geom_Circle(rightCircle);
  Standard_Real rightStartParam = ElCLib::Parameter(rightCircle, rightArcEnd);
  Standard_Real rightEndParam = ElCLib::Parameter(rightCircle, rightArcStart);
  TopoDS_Edge rightArc =
      BRepBuilderAPI_MakeEdge(rightGeomCircle, rightStartParam, rightEndParam)
          .Edge();
  rightArc.Reverse();

  // 7. 构建完整线框（确保拓扑闭合）
  BRepBuilderAPI_MakeWire wireMaker;

  // 主直通段底边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2));

  // 左过渡段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, leftArcStart));
  wireMaker.Add(leftArc);
  wireMaker.Add(BRepBuilderAPI_MakeEdge(leftArcEnd, p7));

  // 支线段底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8));

  // 右过渡段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, rightArcEnd));
  wireMaker.Add(rightArc);
  wireMaker.Add(BRepBuilderAPI_MakeEdge(rightArcStart, p3));

  // 主直通段顶边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4));

  // 闭合线段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p1));

  // 8. 创建底面并拉伸
  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("线框构造失败");
  }
  TopoDS_Face face = BRepBuilderAPI_MakeFace(wireMaker.Wire());

  return BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, height)).Shape();
}

/**
 * @brief 创建三通折角工作井
 * @param length 直通段长度(mm)
 * @param width 直通段宽度(mm)
 * @param height 直通段高度(mm)
 * @param length1 支线段长度(mm)
 * @param width1 支线段宽度(mm)
 * @param cornerLength 井转角折角长(mm)
 * @param cornerWidth 井转角折角宽(mm)
 * @param angle  井转角角度
 * @return 三通工作井的形状
 */
TopoDS_Shape create_three_way_corner_working_well_part(
    double length, double width, double height, double length1, double width1,
    double cornerLength, double cornerWidth, double zoffset) {
  // 参数校验
  if (length <= 0 || width <= 0 || height <= 0 || length1 <= 0 || width1 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }
  if (length1 <= 0 || width1 <= 0) {
    throw Standard_ConstructionError("支线段尺寸参数必须为正数");
  }

  // 1. 计算关键几何参数
  const double halfLength = length / 2;
  const double halfWidth = width / 2;
  const double halfWidth1 = width1 / 2;

  // 2. 定义主直通段四个角点
  const gp_Pnt p1(-halfLength, -halfWidth, zoffset); // 左下角
  const gp_Pnt p2(-halfLength, halfWidth, zoffset);  // 左上角
  const gp_Pnt p3(halfLength, halfWidth, zoffset);   // 右上角
  const gp_Pnt p4(halfLength, -halfWidth, zoffset);  // 右下角

  // 3. 定义支线段端点
  const gp_Pnt p7(-halfWidth1, halfWidth + length1,
                  zoffset);                                  // 支线段左上角点
  const gp_Pnt p8(halfWidth1, halfWidth + length1, zoffset); // 支线段右下角点

  const gp_Pnt leftStart(-halfWidth1 - cornerLength, halfWidth, zoffset);
  const gp_Pnt leftEnd(-halfWidth1, halfWidth + cornerWidth, zoffset);

  const gp_Pnt rightStart(halfWidth1 + cornerLength, halfWidth, zoffset);
  const gp_Pnt rightEnd(halfWidth1, halfWidth + cornerWidth, zoffset);

  // 7. 构建完整线框（确保拓扑闭合）
  BRepBuilderAPI_MakeWire wireMaker;

  // 主直通段底边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2));

  // 左过渡段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, leftStart));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(leftStart, leftEnd));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(leftEnd, p7));

  // 支线段底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8));

  // 右过渡段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, rightEnd));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(rightEnd, rightStart));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(rightStart, p3));

  // 主直通段顶边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4));

  // 闭合线段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p1));

  // 8. 创建底面并拉伸
  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("线框构造失败");
  }
  TopoDS_Face face = BRepBuilderAPI_MakeFace(wireMaker.Wire());

  return BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, height)).Shape();
}

TopoDS_Shape create_three_way_chamfer_round_corner_working_well_part(
    double length, double width, double height, double length1, double width1,
    double cornerLength2, double cornerRadius, double angle, double yoffset,
    double zoffset) {
  // 1. 计算关键点坐标
  double halfLength = length / 2;

  // 2. 定义主直通段四个角点
  const gp_Pnt p1(-halfLength, yoffset, zoffset);         // 左下角
  const gp_Pnt p2(-halfLength, width + yoffset, zoffset); // 左上角
  const gp_Pnt p3(halfLength, width + yoffset, zoffset);  // 右上角
  const gp_Pnt p4(halfLength, yoffset, zoffset);          // 右下角

  // 3. 计算支线段端点
  const gp_Pnt p9(-halfLength + cornerLength2, yoffset,
                  zoffset); // 支线段起点
  gp_Vec vec19(p1, p9);     // p1指向p9的向量

  // 创建旋转轴(Z轴负方向)
  gp_Ax1 rotationAxis(p9, gp_Dir(0, 0, 1));

  // 旋转指定角度得到p8方向向量
  gp_Vec vec8 = vec19.Rotated(rotationAxis, -(180 - angle) * M_PI / 180.0);
  vec8.Normalize();
  vec8 *= length1;
  const gp_Pnt p8(p9.X() + vec8.X(), p9.Y() + vec8.Y(), p9.Z() + vec8.Z());

  // 4. 计算支线段其他点
  gp_Vec vec98(p9, p8); // p9指向p8的向量

  // 创建新的旋转轴(Z轴正方向)
  gp_Ax1 rotationAxis2(p8, gp_Dir(0, 0, 1));

  // 旋转90度得到垂直向量
  gp_Vec vec7 = vec98.Rotated(rotationAxis2, M_PI_2);

  // 归一化并缩放为宽度width1
  vec7.Normalize();
  vec7 *= width1;
  const gp_Pnt p7(p8.X() + vec7.X(), p8.Y() + vec7.Y(), p8.Z() + vec7.Z());

  // 计算p6点向量(与vec98垂直)
  gp_Vec vec76 = vec7.Crossed(gp_Vec(0, 0, -1)); // 使用叉积计算垂直向量
  vec76.Normalize();
  vec76 *= length1;
  // 改为求vec76和x轴交点
  // 修正后的交点计算逻辑
  gp_Pnt p61(0, yoffset, zoffset); // X轴上交点 (Y保持偏移量)
  gp_Vec vec_p7_p61(p7, p61);      // 从p7指向X轴的向量

  // 计算在vec76方向上的投影参数t
  // 使用向量分解公式：vec_p7_p61 = t*vec76 + normal_component
  double t = vec_p7_p61.Dot(vec76) / vec76.SquareMagnitude();

  // 应用参数得到精确交点
  gp_Pnt p6 = p7.Translated(vec76 * t);

  BRepBuilderAPI_MakeWire wireMaker;
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p6));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p6, p7));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, p9));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p9, p1));

  // 7. 创建三维形状
  TopoDS_Shape well =
      BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(wireMaker.Wire()),
                            gp_Vec(0, 0, height))
          .Shape();

  // 7. 自动添加圆角（替代手动计算）
  BRepFilletAPI_MakeFillet fillet(well);
  TopExp_Explorer edgeExplorer(well, TopAbs_EDGE);

  // 添加p6-p7-p8转角处圆角
  for (; edgeExplorer.More(); edgeExplorer.Next()) {
    TopoDS_Edge edge = TopoDS::Edge(edgeExplorer.Current());

    // 获取端点坐标和几何信息
    TopoDS_Vertex first, last;
    TopExp::Vertices(edge, first, last);
    gp_Pnt firstPnt = BRep_Tool::Pnt(first);
    gp_Pnt lastPnt = BRep_Tool::Pnt(last);

    // 检测与p6连接的边
    const bool connectP6 = firstPnt.IsEqual(p6, Precision::Confusion()) ||
                           lastPnt.IsEqual(p6, Precision::Confusion());

    // 新增Z轴平行性检测
    if (connectP6) {
      // 获取边几何参数
      BRepAdaptor_Curve curve(edge);
      if (curve.GetType() == GeomAbs_Line) {
        gp_Dir edgeDir = curve.Line().Direction();

        // 判断是否平行于Z轴（允许角度误差）
        const bool isZParallel =
            edgeDir.IsParallel(gp::DZ(), Precision::Angular());

        if (isZParallel) {
          fillet.Add(cornerRadius, edge);
        }
      }
    }
  }
  fillet.Build();

  return fillet.Shape();
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

/**
 * @brief 创建三通工作井
 */
TopoDS_Shape
create_three_way_working_well(const three_way_well_params &params) {
  if (params.type != three_way_well_type::WORKING_WELL) {
    throw Standard_ConstructionError(
        "three_way_well_type must be WORKING_WELL");
  }
  TopoDS_Shape outer;
  if (params.angle != 90) {
    double offset =
        calculate_length_difference(params.angle, params.outerWallThickness);
    outer = create_three_way_chamfer_round_corner_working_well_part(
        params.length, params.width + params.outerWallThickness * 2,
        params.height + params.topThickness + params.bottomThickness,
        params.branchLength, params.branchWidth + params.outerWallThickness * 2,
        params.branchLeftLength - offset, params.cornerRadius, params.angle,
        -params.outerWallThickness, -params.bottomThickness);
  } else {
    switch (params.cornerType) {
    case corner_style::ROUNDED:
      outer = create_three_way_round_working_well_part(
          params.length, params.width + params.outerWallThickness * 2,
          params.height + params.topThickness + params.bottomThickness,
          params.branchLength,
          params.branchWidth + params.outerWallThickness * 2,
          params.cornerRadius - params.outerWallThickness,
          -params.bottomThickness);
      break;
    case corner_style::ANGLED:
      outer = create_three_way_corner_working_well_part(
          params.length, params.width + params.outerWallThickness * 2,
          params.height + params.topThickness + params.bottomThickness,
          params.branchLength,
          params.branchWidth + params.outerWallThickness * 2,
          params.cornerLength - params.outerWallThickness,
          params.cornerWidth - params.outerWallThickness,
          -params.bottomThickness);
      break;
    default:
      break;
    }
  }

  TopoDS_Shape inner;
  if (params.angle != 90) {
    inner = create_three_way_chamfer_round_corner_working_well_part(
        params.length, params.width, params.height, params.branchLength * 2,
        params.branchWidth, // 支线宽度保持对称
        params.branchLeftLength,
        params.cornerRadius, // 修正转角半径
        params.angle, 0, 0);
  } else {
    switch (params.cornerType) {
    case corner_style::ROUNDED:
      inner = create_three_way_round_working_well_part(
          params.length + params.outerWallThickness * 2, params.width,
          params.height, params.branchLength + params.outerWallThickness * 2,
          params.branchWidth, params.cornerRadius, 0);
      break;
    case corner_style::ANGLED:
      inner = create_three_way_corner_working_well_part(
          params.length + params.outerWallThickness * 2, params.width,
          params.height, params.branchLength + params.outerWallThickness * 2,
          params.branchWidth, params.cornerLength, params.cornerWidth, 0);
      break;
    default:
      break;
    }
  }

  TopoDS_Shape cushion;
  if (params.angle != 90) {
    double offset = calculate_length_difference(
        params.angle, params.outerWallThickness + params.cushionExtension);
    cushion = create_three_way_chamfer_round_corner_working_well_part(
        params.length,
        params.width + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cushionThickness, params.branchLength,
        params.branchWidth + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.branchLeftLength - offset, params.cornerRadius, params.angle,
        -params.cushionExtension - params.outerWallThickness,
        -params.bottomThickness - params.cushionThickness);
  } else {
    switch (params.cornerType) {
    case corner_style::ROUNDED:
      cushion = create_three_way_round_working_well_part(
          params.length,
          params.width + params.outerWallThickness * 2 +
              params.cushionExtension * 2,
          params.cushionThickness, params.branchLength,
          params.branchWidth + params.outerWallThickness * 2 +
              params.cushionExtension * 2,
          params.cornerRadius - params.outerWallThickness -
              params.cushionExtension,
          -params.bottomThickness - params.cushionThickness);
      break;
    case corner_style::ANGLED:
      cushion = create_three_way_corner_working_well_part(
          params.length,
          params.width + params.outerWallThickness * 2 +
              params.cushionExtension * 2,
          params.cushionThickness, params.branchLength,
          params.branchWidth + params.outerWallThickness * 2 +
              params.cushionExtension * 2,
          params.cornerLength + params.outerWallThickness +
              params.cushionExtension,
          params.cornerWidth + params.outerWallThickness +
              params.cushionExtension,
          -params.bottomThickness - params.cushionThickness);
      break;
    default:
      break;
    }
  }

  // 合并所有部分
  TopoDS_Shape well = BRepAlgoAPI_Cut(outer, inner).Shape();

  well = BRepAlgoAPI_Fuse(well, cushion).Shape();

  return well;
}

/**
 * @brief 创建三通明挖隧道井
 */
TopoDS_Shape
create_three_way_open_cut_tunnel(const three_way_well_params &params) {
  if (params.type != three_way_well_type::OPEN_CUT_TUNNEL) {
    throw Standard_ConstructionError(
        "three_way_open_cut_tunnel must be OPEN_CUT_TUNNEL");
  }
  TopoDS_Shape outer;
  switch (params.cornerType) {
  case corner_style::ROUNDED:
    outer = create_three_way_round_working_well_part(
        params.length + params.outerWallThickness * 2,
        params.width + params.outerWallThickness * 2,
        params.height + params.topThickness + params.bottomThickness,
        params.branchLength + params.outerWallThickness * 2,
        params.branchWidth + params.outerWallThickness * 2,
        params.cornerRadius - params.outerWallThickness,
        -params.bottomThickness);
    break;
  case corner_style::ANGLED:
    outer = create_three_way_corner_working_well_part(
        params.length + params.outerWallThickness * 2,
        params.width + params.outerWallThickness * 2,
        params.height + params.topThickness + params.bottomThickness,
        params.branchLength + params.outerWallThickness * 2,
        params.branchWidth + params.outerWallThickness * 2,
        params.cornerLength - params.outerWallThickness,
        params.cornerWidth - params.outerWallThickness,
        -params.bottomThickness);
    break;
  default:
    break;
  }

  // 2. 创建左连接段
  TopoDS_Shape leftTunnel;
  switch (params.leftSectionStyle) {
  case connection_section_style::RECTANGULAR:
    leftTunnel = create_rectangular_section(
        params.leftSectionLength, params.leftSectionWidth,
        params.leftSectionHeight, params.outerWallThickness,
        params.topThickness, params.bottomThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    leftTunnel = create_horseshoe_section(
        params.leftSectionLength, params.leftSectionWidth,
        params.leftSectionHeight, params.leftSectionArcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    leftTunnel = create_circular_section(params.leftSectionLength,
                                         params.leftSectionHeight / 2,
                                         params.outerWallThickness, true);
    break;
  }

  // 移动左连接段到正确位置
  gp_Trsf leftTrsf;
  leftTrsf.SetTranslation(
      gp_Vec(-params.leftSectionLength - params.length / 2, 0, 0));
  leftTunnel = BRepBuilderAPI_Transform(leftTunnel, leftTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, leftTunnel).Shape();

  // 3. 创建右连接段
  TopoDS_Shape rightTunnel;
  switch (params.rightSectionStyle) {
  case connection_section_style::RECTANGULAR:
    rightTunnel = create_rectangular_section(
        params.rightSectionLength, params.rightSectionWidth,
        params.rightSectionHeight, params.outerWallThickness,
        params.topThickness, params.bottomThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    rightTunnel = create_horseshoe_section(
        params.rightSectionLength, params.rightSectionWidth,
        params.rightSectionHeight, params.rightSectionArcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    rightTunnel = create_circular_section(params.rightSectionLength,
                                          params.rightSectionHeight / 2,
                                          params.outerWallThickness, true);
    break;
  }

  // 移动支连接段到正确位置
  gp_Trsf rightTrsf;
  rightTrsf.SetTranslation(gp_Vec(params.length / 2, 0, 0));
  rightTunnel = BRepBuilderAPI_Transform(rightTunnel, rightTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, rightTunnel).Shape();

  // 3. 创建支连接段
  TopoDS_Shape branchTunnel;
  switch (params.branchSectionStyle) {
  case connection_section_style::RECTANGULAR:
    branchTunnel = create_rectangular_section(
        params.branchSectionLength, params.branchSectionWidth,
        params.branchSectionHeight, params.outerWallThickness,
        params.topThickness, params.bottomThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    branchTunnel = create_horseshoe_section(
        params.branchSectionLength, params.branchSectionWidth,
        params.branchSectionHeight, params.branchSectionArcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    branchTunnel = create_circular_section(params.branchSectionLength,
                                           params.branchSectionHeight / 2,
                                           params.outerWallThickness, true);
    break;
  }

  // 移动右连接段到正确位置
  gp_Trsf branchTrsf;
  gp_Trsf branchModel;
  branchModel.SetTranslation(gp_Vec(-params.branchSectionLength / 2, 0, 0));
  gp_Trsf rotateTrsf;
  rotateTrsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -1)),
                         90 * M_PI / 180.0);

  branchTrsf.SetTranslation(gp_Vec(0,
                                   params.branchLength + params.width / 2 +
                                       params.branchSectionLength / 2,
                                   0));
  branchTunnel = BRepBuilderAPI_Transform(branchTunnel, branchModel).Shape();
  branchTunnel = BRepBuilderAPI_Transform(branchTunnel, rotateTrsf).Shape();
  branchTunnel = BRepBuilderAPI_Transform(branchTunnel, branchTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, branchTunnel).Shape();

  TopoDS_Shape inner;
  switch (params.cornerType) {
  case corner_style::ROUNDED:
    inner = create_three_way_round_working_well_part(
        params.length + params.outerWallThickness * 2, params.width,
        params.height, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth, params.cornerRadius, 0);
    break;
  case corner_style::ANGLED:
    inner = create_three_way_corner_working_well_part(
        params.length + params.outerWallThickness * 2, params.width,
        params.height, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth, params.cornerLength, params.cornerWidth, 0);
    break;
  default:
    break;
  }

  TopoDS_Shape innerLeftTunnel;
  switch (params.leftSectionStyle) {
  case connection_section_style::RECTANGULAR:
    innerLeftTunnel = create_rectangular_section(
        params.leftSectionLength - params.outerWallThickness,
        params.leftSectionWidth, params.leftSectionHeight,
        params.outerWallThickness, params.topThickness, params.bottomThickness,
        false);
    break;
  case connection_section_style::HORSESHOE:
    innerLeftTunnel = create_horseshoe_section(
        params.leftSectionLength - params.outerWallThickness,
        params.leftSectionWidth, params.leftSectionHeight,
        params.leftSectionArcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerLeftTunnel = create_circular_section(
        params.leftSectionLength - params.outerWallThickness,
        params.leftSectionHeight / 2, params.outerWallThickness, false);
    break;
  }

  innerLeftTunnel = BRepBuilderAPI_Transform(innerLeftTunnel, leftTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerLeftTunnel).Shape();

  TopoDS_Shape innerRightTunnel;
  switch (params.rightSectionStyle) {
  case connection_section_style::RECTANGULAR:
    innerRightTunnel = create_rectangular_section(
        params.rightSectionLength - params.outerWallThickness,
        params.rightSectionWidth, params.rightSectionHeight,
        params.outerWallThickness, params.topThickness, params.bottomThickness,
        false);
    break;
  case connection_section_style::HORSESHOE:
    innerRightTunnel = create_horseshoe_section(
        params.rightSectionLength - params.outerWallThickness,
        params.rightSectionWidth, params.rightSectionHeight,
        params.rightSectionArcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerRightTunnel = create_circular_section(
        params.rightSectionLength - params.outerWallThickness,
        params.rightSectionHeight / 2, params.outerWallThickness, false);
    break;
  }

  rightTrsf.SetTranslation(
      gp_Vec(params.length / 2 + params.outerWallThickness, 0, 0));
  innerRightTunnel =
      BRepBuilderAPI_Transform(innerRightTunnel, rightTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerRightTunnel).Shape();

  // 3. 创建右连接段
  TopoDS_Shape innerBranchTunnel;
  switch (params.branchSectionStyle) {
  case connection_section_style::RECTANGULAR:
    innerBranchTunnel = create_rectangular_section(
        params.branchSectionLength - params.outerWallThickness,
        params.branchSectionWidth, params.branchSectionHeight,
        params.outerWallThickness, params.topThickness, params.bottomThickness,
        false);
    break;
  case connection_section_style::HORSESHOE:
    innerBranchTunnel = create_horseshoe_section(
        params.branchSectionLength - params.outerWallThickness,
        params.branchSectionWidth, params.branchSectionHeight,
        params.branchSectionArcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerBranchTunnel = create_circular_section(
        params.branchSectionLength - params.outerWallThickness,
        params.branchSectionHeight / 2, params.outerWallThickness, false);
    break;
  }

  branchModel.SetTranslation(gp_Vec(
      -(params.branchSectionLength - params.outerWallThickness) / 2, 0, 0));
  branchTrsf.SetTranslation(gp_Vec(
      0,
      params.branchLength + params.width / 2 + params.branchSectionLength / 2 +
          params.outerWallThickness + params.outerWallThickness / 2,
      0));
  innerBranchTunnel =
      BRepBuilderAPI_Transform(innerBranchTunnel, branchModel).Shape();
  innerBranchTunnel =
      BRepBuilderAPI_Transform(innerBranchTunnel, rotateTrsf).Shape();
  innerBranchTunnel =
      BRepBuilderAPI_Transform(innerBranchTunnel, branchTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerBranchTunnel).Shape();

  TopoDS_Shape cushion;
  switch (params.cornerType) {
  case corner_style::ROUNDED:
    cushion = create_three_way_round_working_well_part(
        params.length + params.leftSectionLength + params.rightSectionLength,
        params.width + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cushionThickness,
        params.branchLength + params.branchSectionLength,
        params.branchWidth + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cornerRadius - params.outerWallThickness -
            params.cushionExtension,
        -params.bottomThickness - params.cushionThickness);
    break;
  case corner_style::ANGLED:
    cushion = create_three_way_corner_working_well_part(
        params.length + params.leftSectionLength + params.rightSectionLength,
        params.width + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cushionThickness,
        params.branchLength + params.branchSectionLength,
        params.branchWidth + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cornerLength + params.outerWallThickness +
            params.cushionExtension,
        params.cornerWidth + params.outerWallThickness +
            params.cushionExtension,
        -params.bottomThickness - params.cushionThickness);
    break;
  default:
    break;
  }

  // 合并所有部分
  TopoDS_Shape well = BRepAlgoAPI_Cut(outer, inner).Shape();

  well = BRepAlgoAPI_Fuse(well, cushion).Shape();

  return well;
}

TopoDS_Shape create_three_way_circle_well_part(double length, double width,
                                               double height, double length1,
                                               double width1, double wellRadius,
                                               double weelheight,
                                               double zoffset) {
  // 参数校验
  if (length <= 0 || width <= 0 || height <= 0 || length1 <= 0 || width1 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }
  if (length1 <= 0 || width1 <= 0) {
    throw Standard_ConstructionError("支线段尺寸参数必须为正数");
  }

  // 1. 计算关键几何参数
  const double halfLength = length / 2;
  const double halfWidth = width / 2;
  const double halfWidth1 = width1 / 2;

  // 2. 定义主直通段四个角点
  const gp_Pnt p1(-halfLength, -halfWidth, zoffset); // 左下角
  const gp_Pnt p2(-halfLength, halfWidth, zoffset);  // 左上角
  const gp_Pnt p3(halfLength, halfWidth, zoffset);   // 右上角
  const gp_Pnt p4(halfLength, -halfWidth, zoffset);  // 右下角

  // 3. 定义支线段端点
  const gp_Pnt p7(-halfWidth1, halfWidth + length1,
                  zoffset);                                  // 支线段左上角点
  const gp_Pnt p8(halfWidth1, halfWidth + length1, zoffset); // 支线段右下角点
  const gp_Pnt p9(-halfWidth1, halfWidth, zoffset);          // 支线段左下角点
  const gp_Pnt p10(halfWidth1, halfWidth, zoffset);          // 支线段右下角点

  // 7. 构建完整线框（确保拓扑闭合）
  BRepBuilderAPI_MakeWire wireMaker;

  // 主直通段底边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2));

  // 左过渡段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p9));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p9, p7));

  // 支线段底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8));

  // 右过渡段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, p10));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p10, p3));

  // 主直通段顶边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4));

  // 闭合线段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p1));

  // 8. 创建底面并拉伸
  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("线框构造失败");
  }
  TopoDS_Face face = BRepBuilderAPI_MakeFace(wireMaker.Wire());

  TopoDS_Shape tunnel =
      BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, height)).Shape();

  gp_Ax2 wellAxis(gp_Pnt(0, 0, zoffset), gp::DZ());
  TopoDS_Shape well =
      BRepPrimAPI_MakeCylinder(wellAxis, wellRadius, weelheight).Shape();
  return BRepAlgoAPI_Fuse(tunnel, well).Shape();
}

TopoDS_Shape create_three_way_rectangular_well_part(
    double length, double width, double height, double length1, double width1,
    double wellWidth, double weelheight, double zoffset) {
  // 参数校验
  if (length <= 0 || width <= 0 || height <= 0 || length1 <= 0 || width1 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }
  if (length1 <= 0 || width1 <= 0) {
    throw Standard_ConstructionError("支线段尺寸参数必须为正数");
  }

  // 1. 计算关键几何参数
  const double halfLength = length / 2;
  const double halfWidth = width / 2;
  const double halfWidth1 = width1 / 2;

  // 2. 定义主直通段四个角点
  const gp_Pnt p1(-halfLength, -halfWidth, zoffset); // 左下角
  const gp_Pnt p2(-halfLength, halfWidth, zoffset);  // 左上角
  const gp_Pnt p3(halfLength, halfWidth, zoffset);   // 右上角
  const gp_Pnt p4(halfLength, -halfWidth, zoffset);  // 右下角

  // 3. 定义支线段端点
  const gp_Pnt p7(-halfWidth1, halfWidth + length1,
                  zoffset);                                  // 支线段左上角点
  const gp_Pnt p8(halfWidth1, halfWidth + length1, zoffset); // 支线段右上角点
  const gp_Pnt p9(-halfWidth1, halfWidth, zoffset);          // 支线段左下角点
  const gp_Pnt p10(halfWidth1, halfWidth, zoffset);          // 支线段右下角点

  // 7. 构建完整线框（确保拓扑闭合）
  BRepBuilderAPI_MakeWire wireMaker;

  // 主直通段底边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2));

  // 左过渡段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p9));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p9, p7));

  // 支线段底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8));

  // 右过渡段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, p10));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p10, p3));

  // 主直通段顶边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4));

  // 闭合线段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p1));

  // 8. 创建底面并拉伸
  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("线框构造失败");
  }
  TopoDS_Face face = BRepBuilderAPI_MakeFace(wireMaker.Wire());

  TopoDS_Shape tunnel =
      BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, height)).Shape();

  gp_Pnt innerOrigin(-wellWidth / 2, -wellWidth / 2, zoffset);
  BRepPrimAPI_MakeBox well(innerOrigin, wellWidth, wellWidth, weelheight);

  return BRepAlgoAPI_Fuse(tunnel, well).Shape();
}

/**
 * @brief 创建三通暗挖隧道井
 */
TopoDS_Shape
create_three_way_underground_tunnel(const three_way_well_params &params) {
  if (params.type != three_way_well_type::UNDERGROUND_TUNNEL) {
    throw Standard_ConstructionError(
        "three_way_underground_tunnel must be UNDERGROUND_TUNNEL");
  }
  if (params.isDoubleShaft) {
    throw Standard_ConstructionError(
        "three_way_underground_tunnel must be single shaft");
  }
  TopoDS_Shape outer;
  switch (params.shaftType) {
  case shaft_style::CIRCULAR:
    outer = create_three_way_circle_well_part(
        params.length + params.outerWallThickness * 2,
        params.width + params.outerWallThickness * 2,
        params.height + params.outerWallThickness * 2,
        params.branchLength + params.outerWallThickness * 2,
        params.branchWidth + params.outerWallThickness * 2,
        params.shaftRadius + params.outerWallThickness +
            params.innerWallThickness,
        params.height + params.outerWallThickness * 2,
        -params.outerWallThickness);
    break;
  case shaft_style::RECTANGULAR:
    outer = create_three_way_rectangular_well_part(
        params.length + params.outerWallThickness * 2,
        params.width + params.outerWallThickness * 2,
        params.height + params.outerWallThickness * 2,
        params.branchLength + params.outerWallThickness * 2,
        params.branchWidth + params.outerWallThickness * 2,
        (params.shaftRadius + params.outerWallThickness +
         params.innerWallThickness) *
            2,
        params.height + params.outerWallThickness * 2,
        -params.outerWallThickness);
    break;
  default:
    break;
  }

  // 2. 创建左连接段
  TopoDS_Shape leftTunnel;
  switch (params.leftSectionStyle) {
  case connection_section_style::RECTANGULAR:
    leftTunnel = create_rectangular_section(
        params.leftSectionLength, params.leftSectionWidth,
        params.leftSectionHeight, params.outerWallThickness,
        params.outerWallThickness, params.outerWallThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    leftTunnel = create_horseshoe_section(
        params.leftSectionLength, params.leftSectionWidth,
        params.leftSectionHeight, params.leftSectionArcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    leftTunnel = create_circular_section(params.leftSectionLength,
                                         params.leftSectionHeight / 2,
                                         params.outerWallThickness, true);
    break;
  }

  // 移动左连接段到正确位置
  gp_Trsf leftTrsf;
  leftTrsf.SetTranslation(
      gp_Vec(-params.leftSectionLength - params.length / 2, 0, 0));
  leftTunnel = BRepBuilderAPI_Transform(leftTunnel, leftTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, leftTunnel).Shape();

  // 3. 创建右连接段
  TopoDS_Shape rightTunnel;
  switch (params.rightSectionStyle) {
  case connection_section_style::RECTANGULAR:
    rightTunnel = create_rectangular_section(
        params.rightSectionLength, params.rightSectionWidth,
        params.rightSectionHeight, params.outerWallThickness,
        params.outerWallThickness, params.outerWallThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    rightTunnel = create_horseshoe_section(
        params.rightSectionLength, params.rightSectionWidth,
        params.rightSectionHeight, params.rightSectionArcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    rightTunnel = create_circular_section(params.rightSectionLength,
                                          params.rightSectionHeight / 2,
                                          params.outerWallThickness, true);
    break;
  }

  // 移动支连接段到正确位置
  gp_Trsf rightTrsf;
  rightTrsf.SetTranslation(gp_Vec(params.length / 2, 0, 0));
  rightTunnel = BRepBuilderAPI_Transform(rightTunnel, rightTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, rightTunnel).Shape();

  // 3. 创建支连接段
  TopoDS_Shape branchTunnel;
  switch (params.branchSectionStyle) {
  case connection_section_style::RECTANGULAR:
    branchTunnel = create_rectangular_section(
        params.branchSectionLength, params.branchSectionWidth,
        params.branchSectionHeight, params.outerWallThickness,
        params.outerWallThickness, params.outerWallThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    branchTunnel = create_horseshoe_section(
        params.branchSectionLength, params.branchSectionWidth,
        params.branchSectionHeight, params.branchSectionArcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    branchTunnel = create_circular_section(params.branchSectionLength,
                                           params.branchSectionHeight / 2,
                                           params.outerWallThickness, true);
    break;
  }

  // 移动右连接段到正确位置
  gp_Trsf branchTrsf;
  gp_Trsf branchModel;
  branchModel.SetTranslation(gp_Vec(-params.branchSectionLength / 2, 0, 0));
  gp_Trsf rotateTrsf;
  rotateTrsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -1)),
                         90 * M_PI / 180.0);

  branchTrsf.SetTranslation(gp_Vec(0,
                                   params.branchLength + params.width / 2 +
                                       params.branchSectionLength / 2,
                                   0));
  branchTunnel = BRepBuilderAPI_Transform(branchTunnel, branchModel).Shape();
  branchTunnel = BRepBuilderAPI_Transform(branchTunnel, rotateTrsf).Shape();
  branchTunnel = BRepBuilderAPI_Transform(branchTunnel, branchTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, branchTunnel).Shape();

  TopoDS_Shape inner;
  switch (params.shaftType) {
  case shaft_style::CIRCULAR:
    inner = create_three_way_circle_well_part(
        params.length + params.outerWallThickness * 2, params.width,
        params.height, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth, params.shaftRadius,
        params.height + params.outerWallThickness * 2, 0);
    break;
  case shaft_style::RECTANGULAR:
    inner = create_three_way_rectangular_well_part(
        params.length + params.outerWallThickness * 2, params.width,
        params.height, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth, params.shaftRadius * 2,
        params.height + params.outerWallThickness * 2, 0);
    break;
  default:
    break;
  }

  TopoDS_Shape innerLeftTunnel;
  switch (params.leftSectionStyle) {
  case connection_section_style::RECTANGULAR:
    innerLeftTunnel = create_rectangular_section(
        params.leftSectionLength - params.outerWallThickness,
        params.leftSectionWidth, params.leftSectionHeight,
        params.outerWallThickness, params.outerWallThickness,
        params.outerWallThickness, false);
    break;
  case connection_section_style::HORSESHOE:
    innerLeftTunnel = create_horseshoe_section(
        params.leftSectionLength - params.outerWallThickness,
        params.leftSectionWidth, params.leftSectionHeight,
        params.leftSectionArcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerLeftTunnel = create_circular_section(
        params.leftSectionLength - params.outerWallThickness,
        params.leftSectionHeight / 2, params.outerWallThickness, false);
    break;
  }

  innerLeftTunnel = BRepBuilderAPI_Transform(innerLeftTunnel, leftTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerLeftTunnel).Shape();

  TopoDS_Shape innerRightTunnel;
  switch (params.rightSectionStyle) {
  case connection_section_style::RECTANGULAR:
    innerRightTunnel = create_rectangular_section(
        params.rightSectionLength - params.outerWallThickness,
        params.rightSectionWidth, params.rightSectionHeight,
        params.outerWallThickness, params.outerWallThickness,
        params.outerWallThickness, false);
    break;
  case connection_section_style::HORSESHOE:
    innerRightTunnel = create_horseshoe_section(
        params.rightSectionLength - params.outerWallThickness,
        params.rightSectionWidth, params.rightSectionHeight,
        params.rightSectionArcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerRightTunnel = create_circular_section(
        params.rightSectionLength - params.outerWallThickness,
        params.rightSectionHeight / 2, params.outerWallThickness, false);
    break;
  }

  rightTrsf.SetTranslation(
      gp_Vec(params.length / 2 + params.outerWallThickness, 0, 0));
  innerRightTunnel =
      BRepBuilderAPI_Transform(innerRightTunnel, rightTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerRightTunnel).Shape();

  // 3. 创建右连接段
  TopoDS_Shape innerBranchTunnel;
  switch (params.branchSectionStyle) {
  case connection_section_style::RECTANGULAR:
    innerBranchTunnel = create_rectangular_section(
        params.branchSectionLength - params.outerWallThickness,
        params.branchSectionWidth, params.branchSectionHeight,
        params.outerWallThickness, params.outerWallThickness,
        params.outerWallThickness, false);
    break;
  case connection_section_style::HORSESHOE:
    innerBranchTunnel = create_horseshoe_section(
        params.branchSectionLength - params.outerWallThickness,
        params.branchSectionWidth, params.branchSectionHeight,
        params.branchSectionArcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerBranchTunnel = create_circular_section(
        params.branchSectionLength - params.outerWallThickness,
        params.branchSectionHeight / 2, params.outerWallThickness, false);
    break;
  }

  branchModel.SetTranslation(gp_Vec(
      -(params.branchSectionLength - params.outerWallThickness) / 2, 0, 0));
  branchTrsf.SetTranslation(gp_Vec(
      0,
      params.branchLength + params.width / 2 + params.branchSectionLength / 2 +
          params.outerWallThickness + params.outerWallThickness / 2,
      0));
  innerBranchTunnel =
      BRepBuilderAPI_Transform(innerBranchTunnel, branchModel).Shape();
  innerBranchTunnel =
      BRepBuilderAPI_Transform(innerBranchTunnel, rotateTrsf).Shape();
  innerBranchTunnel =
      BRepBuilderAPI_Transform(innerBranchTunnel, branchTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerBranchTunnel).Shape();
  // 合并所有部分
  TopoDS_Shape well = BRepAlgoAPI_Cut(outer, inner).Shape();

  return well;
}

/**
 * @brief 创建三通暗挖隧道双拼井
 */
TopoDS_Shape
create_three_way_double_shaft_tunnel(const three_way_well_params &params) {
  if (params.type != three_way_well_type::UNDERGROUND_TUNNEL) {
    throw Standard_ConstructionError(
        "three_way_underground_tunnel must be UNDERGROUND_TUNNEL");
  }
  if (!params.isDoubleShaft) {
    throw Standard_ConstructionError(
        "three_way_underground_tunnel must be single shaft");
  }
  TopoDS_Shape outer;
  switch (params.shaftType) {
  case shaft_style::CIRCULAR:
    outer = create_three_way_circle_well_part(
        params.length + params.outerWallThickness * 2,
        params.width + params.outerWallThickness * 2,
        params.height + params.outerWallThickness * 2,
        params.branchLength + params.outerWallThickness * 2,
        (params.branchWidth + params.outerWallThickness * 2) * 2,
        params.shaftRadius + params.outerWallThickness +
            params.innerWallThickness,
        params.height + params.outerWallThickness * 2,
        -params.outerWallThickness);
    break;
  case shaft_style::RECTANGULAR:
    outer = create_three_way_rectangular_well_part(
        params.length + params.outerWallThickness * 2,
        params.width + params.outerWallThickness * 2,
        params.height + params.outerWallThickness * 2,
        params.branchLength + params.outerWallThickness * 2,
        (params.branchWidth + params.outerWallThickness * 2) * 2,
        (params.shaftRadius + params.outerWallThickness +
         params.innerWallThickness) *
            2,
        params.height + params.outerWallThickness * 2,
        -params.outerWallThickness);
    break;
  default:
    break;
  }

  // 2. 创建左连接段
  TopoDS_Shape leftTunnel;
  switch (params.leftSectionStyle) {
  case connection_section_style::RECTANGULAR:
    leftTunnel = create_rectangular_section(
        params.leftSectionLength, params.leftSectionWidth,
        params.leftSectionHeight, params.outerWallThickness,
        params.outerWallThickness, params.outerWallThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    leftTunnel = create_horseshoe_section(
        params.leftSectionLength, params.leftSectionWidth,
        params.leftSectionHeight, params.leftSectionArcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    leftTunnel = create_circular_section(params.leftSectionLength,
                                         params.leftSectionHeight / 2,
                                         params.outerWallThickness, true);
    break;
  }

  // 移动左连接段到正确位置
  gp_Trsf leftTrsf;
  leftTrsf.SetTranslation(
      gp_Vec(-params.leftSectionLength - params.length / 2, 0, 0));
  leftTunnel = BRepBuilderAPI_Transform(leftTunnel, leftTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, leftTunnel).Shape();

  // 3. 创建右连接段
  TopoDS_Shape rightTunnel;
  switch (params.rightSectionStyle) {
  case connection_section_style::RECTANGULAR:
    rightTunnel = create_rectangular_section(
        params.rightSectionLength, params.rightSectionWidth,
        params.rightSectionHeight, params.outerWallThickness,
        params.outerWallThickness, params.outerWallThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    rightTunnel = create_horseshoe_section(
        params.rightSectionLength, params.rightSectionWidth,
        params.rightSectionHeight, params.rightSectionArcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    rightTunnel = create_circular_section(params.rightSectionLength,
                                          params.rightSectionHeight / 2,
                                          params.outerWallThickness, true);
    break;
  }

  // 移动支连接段到正确位置
  gp_Trsf rightTrsf;
  rightTrsf.SetTranslation(gp_Vec(params.length / 2, 0, 0));
  rightTunnel = BRepBuilderAPI_Transform(rightTunnel, rightTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, rightTunnel).Shape();

  // 3. 创建左支连接段
  TopoDS_Shape branchLeftTunnel;
  switch (params.branchSectionStyle) {
  case connection_section_style::RECTANGULAR:
    branchLeftTunnel = create_rectangular_section(
        params.branchSectionLength, params.branchSectionWidth,
        params.branchSectionHeight, params.outerWallThickness,
        params.outerWallThickness, params.outerWallThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    branchLeftTunnel = create_horseshoe_section(
        params.branchSectionLength, params.branchSectionWidth,
        params.branchSectionHeight, params.branchSectionArcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    branchLeftTunnel = create_circular_section(params.branchSectionLength,
                                               params.branchSectionHeight / 2,
                                               params.outerWallThickness, true);
    break;
  }

  // 移动右连接段到正确位置
  gp_Trsf branchLeftTrsf;
  gp_Trsf branchLeftModel;
  branchLeftModel.SetTranslation(gp_Vec(-params.branchSectionLength / 2, 0, 0));
  gp_Trsf rotateLeftTrsf;
  rotateLeftTrsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -1)),
                             90 * M_PI / 180.0);

  branchLeftTrsf.SetTranslation(gp_Vec(
      -params.branchSectionWidth / 2 - params.outerWallThickness,
      params.branchLength + params.width / 2 + params.branchSectionLength / 2,
      0));
  branchLeftTunnel =
      BRepBuilderAPI_Transform(branchLeftTunnel, branchLeftModel).Shape();
  branchLeftTunnel =
      BRepBuilderAPI_Transform(branchLeftTunnel, rotateLeftTrsf).Shape();
  branchLeftTunnel =
      BRepBuilderAPI_Transform(branchLeftTunnel, branchLeftTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, branchLeftTunnel).Shape();

  // 3. 创建右支连接段
  TopoDS_Shape branchRightTunnel;
  switch (params.branchSectionStyle) {
  case connection_section_style::RECTANGULAR:
    branchRightTunnel = create_rectangular_section(
        params.branchSectionLength, params.branchSectionWidth,
        params.branchSectionHeight, params.outerWallThickness,
        params.outerWallThickness, params.outerWallThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    branchRightTunnel = create_horseshoe_section(
        params.branchSectionLength, params.branchSectionWidth,
        params.branchSectionHeight, params.branchSectionArcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    branchRightTunnel = create_circular_section(
        params.branchSectionLength, params.branchSectionHeight / 2,
        params.outerWallThickness, true);
    break;
  }

  // 移动右连接段到正确位置
  gp_Trsf branchRightTrsf;
  gp_Trsf branchRightModel;
  branchRightModel.SetTranslation(
      gp_Vec(-params.branchSectionLength / 2, 0, 0));
  gp_Trsf rotateRightTrsf;
  rotateRightTrsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -1)),
                              90 * M_PI / 180.0);

  branchRightTrsf.SetTranslation(gp_Vec(
      params.branchSectionWidth / 2 + params.outerWallThickness,
      params.branchLength + params.width / 2 + params.branchSectionLength / 2,
      0));
  branchRightTunnel =
      BRepBuilderAPI_Transform(branchRightTunnel, branchRightModel).Shape();
  branchRightTunnel =
      BRepBuilderAPI_Transform(branchRightTunnel, rotateRightTrsf).Shape();
  branchRightTunnel =
      BRepBuilderAPI_Transform(branchRightTunnel, branchRightTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, branchRightTunnel).Shape();

  TopoDS_Shape inner;
  switch (params.shaftType) {
  case shaft_style::CIRCULAR:
    inner = create_three_way_circle_well_part(
        params.length + params.outerWallThickness * 2, params.width,
        params.height, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth * 2, params.shaftRadius,
        params.height + params.outerWallThickness * 2, 0);
    break;
  case shaft_style::RECTANGULAR:
    inner = create_three_way_rectangular_well_part(
        params.length + params.outerWallThickness * 2, params.width,
        params.height, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth * 2, params.shaftRadius * 2,
        params.height + params.outerWallThickness * 2, 0);
    break;
  default:
    break;
  }

  TopoDS_Shape innerLeftTunnel;
  switch (params.leftSectionStyle) {
  case connection_section_style::RECTANGULAR:
    innerLeftTunnel = create_rectangular_section(
        params.leftSectionLength - params.outerWallThickness,
        params.leftSectionWidth, params.leftSectionHeight,
        params.outerWallThickness, params.outerWallThickness,
        params.outerWallThickness, false);
    break;
  case connection_section_style::HORSESHOE:
    innerLeftTunnel = create_horseshoe_section(
        params.leftSectionLength - params.outerWallThickness,
        params.leftSectionWidth, params.leftSectionHeight,
        params.leftSectionArcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerLeftTunnel = create_circular_section(
        params.leftSectionLength - params.outerWallThickness,
        params.leftSectionHeight / 2, params.outerWallThickness, false);
    break;
  }

  innerLeftTunnel = BRepBuilderAPI_Transform(innerLeftTunnel, leftTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerLeftTunnel).Shape();

  TopoDS_Shape innerRightTunnel;
  switch (params.rightSectionStyle) {
  case connection_section_style::RECTANGULAR:
    innerRightTunnel = create_rectangular_section(
        params.rightSectionLength - params.outerWallThickness,
        params.rightSectionWidth, params.rightSectionHeight,
        params.outerWallThickness, params.outerWallThickness,
        params.outerWallThickness, false);
    break;
  case connection_section_style::HORSESHOE:
    innerRightTunnel = create_horseshoe_section(
        params.rightSectionLength - params.outerWallThickness,
        params.rightSectionWidth, params.rightSectionHeight,
        params.rightSectionArcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerRightTunnel = create_circular_section(
        params.rightSectionLength - params.outerWallThickness,
        params.rightSectionHeight / 2, params.outerWallThickness, false);
    break;
  }

  rightTrsf.SetTranslation(
      gp_Vec(params.length / 2 + params.outerWallThickness, 0, 0));
  innerRightTunnel =
      BRepBuilderAPI_Transform(innerRightTunnel, rightTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerRightTunnel).Shape();

  // 3. 创建右连接段
  TopoDS_Shape innerLeftBranchTunnel;
  switch (params.branchSectionStyle) {
  case connection_section_style::RECTANGULAR:
    innerLeftBranchTunnel = create_rectangular_section(
        params.branchSectionLength - params.outerWallThickness,
        params.branchSectionWidth, params.branchSectionHeight,
        params.outerWallThickness, params.outerWallThickness,
        params.outerWallThickness, false);
    break;
  case connection_section_style::HORSESHOE:
    innerLeftBranchTunnel = create_horseshoe_section(
        params.branchSectionLength - params.outerWallThickness,
        params.branchSectionWidth, params.branchSectionHeight,
        params.branchSectionArcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerLeftBranchTunnel = create_circular_section(
        params.branchSectionLength - params.outerWallThickness,
        params.branchSectionHeight / 2, params.outerWallThickness, false);
    break;
  }

  branchLeftModel.SetTranslation(gp_Vec(
      -(params.branchSectionLength - params.outerWallThickness) / 2, 0, 0));
  branchLeftTrsf.SetTranslation(gp_Vec(
      -params.branchSectionWidth / 2 - params.outerWallThickness,
      params.branchLength + params.width / 2 + params.branchSectionLength / 2 +
          params.outerWallThickness + params.outerWallThickness / 2,
      0));
  innerLeftBranchTunnel =
      BRepBuilderAPI_Transform(innerLeftBranchTunnel, branchLeftModel).Shape();
  innerLeftBranchTunnel =
      BRepBuilderAPI_Transform(innerLeftBranchTunnel, rotateLeftTrsf).Shape();
  innerLeftBranchTunnel =
      BRepBuilderAPI_Transform(innerLeftBranchTunnel, branchLeftTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerLeftBranchTunnel).Shape();

  // 3. 创建右连接段
  TopoDS_Shape innerRightBranchTunnel;
  switch (params.branchSectionStyle) {
  case connection_section_style::RECTANGULAR:
    innerRightBranchTunnel = create_rectangular_section(
        params.branchSectionLength - params.outerWallThickness,
        params.branchSectionWidth, params.branchSectionHeight,
        params.outerWallThickness, params.outerWallThickness,
        params.outerWallThickness, false);
    break;
  case connection_section_style::HORSESHOE:
    innerRightBranchTunnel = create_horseshoe_section(
        params.branchSectionLength - params.outerWallThickness,
        params.branchSectionWidth, params.branchSectionHeight,
        params.branchSectionArcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerRightBranchTunnel = create_circular_section(
        params.branchSectionLength - params.outerWallThickness,
        params.branchSectionHeight / 2, params.outerWallThickness, false);
    break;
  }

  branchRightModel.SetTranslation(gp_Vec(
      -(params.branchSectionLength - params.outerWallThickness) / 2, 0, 0));
  branchRightTrsf.SetTranslation(gp_Vec(
      params.branchSectionWidth / 2 + params.outerWallThickness,
      params.branchLength + params.width / 2 + params.branchSectionLength / 2 +
          params.outerWallThickness + params.outerWallThickness / 2,
      0));
  innerRightBranchTunnel =
      BRepBuilderAPI_Transform(innerRightBranchTunnel, branchRightModel)
          .Shape();
  innerRightBranchTunnel =
      BRepBuilderAPI_Transform(innerRightBranchTunnel, rotateRightTrsf).Shape();
  innerRightBranchTunnel =
      BRepBuilderAPI_Transform(innerRightBranchTunnel, branchRightTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerRightBranchTunnel).Shape();

  // 合并所有部分
  TopoDS_Shape well = BRepAlgoAPI_Cut(outer, inner).Shape();

  return well;
}

TopoDS_Shape create_three_way_well(const three_way_well_params &params) {
  // 参数验证
  if (params.length <= 0 || params.width <= 0 || params.height <= 0) {
    throw Standard_ConstructionError("Main well dimensions must be positive");
  }

  if (params.type == three_way_well_type::WORKING_WELL &&
      (params.topThickness <= 0 || params.bottomThickness <= 0)) {
    throw Standard_ConstructionError(
        "Working well must have positive top and bottom thickness");
  }
  switch (params.type) {
  case three_way_well_type::WORKING_WELL:
    return create_three_way_working_well(params);
  case three_way_well_type::OPEN_CUT_TUNNEL:
    return create_three_way_open_cut_tunnel(params);
  case three_way_well_type::UNDERGROUND_TUNNEL:
    return params.isDoubleShaft ? create_three_way_double_shaft_tunnel(params)
                                : create_three_way_underground_tunnel(params);
  default:
    return TopoDS_Shape();
  }
}

TopoDS_Shape create_three_way_well(const three_way_well_params &params,
                                   const gp_Pnt &position,
                                   const gp_Dir &mainDirection,
                                   const gp_Dir &branchDirection) {
  // 正交性校验
  if (Abs(mainDirection.Dot(branchDirection)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Main and branch directions must be perpendicular");
  }

  // 创建标准方向的三通井
  TopoDS_Shape well = create_three_way_well(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, mainDirection.Crossed(branchDirection),
                   mainDirection);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(well, transformation);
  return transform.Shape();
}

/**
 * @brief 创建四通圆角工作井
 * @param length 直通段长度(mm)
 * @param width 直通段宽度(mm)
 * @param height 直通段高度(mm)
 * @param length1 支线段长度(mm)
 * @param width1 支线段宽度(mm)
 * @param cornerRadius 井转角半径(mm)
 * @return 四通圆角工作井的形状
 */
TopoDS_Shape create_four_way_round_working_well_part(
    double length, double width, double height, double length1, double width1,
    double length2, double width2, double cornerRadius, double zoffset) {
  // 参数校验
  if (length <= 0 || width <= 0 || height <= 0 || length1 <= 0 || width1 <= 0 ||
      length2 <= 0 || width2 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }
  if (cornerRadius <= 0) {
    throw Standard_ConstructionError("圆角半径必须大于0");
  }

  // 1. 计算关键几何参数
  const double halfLength = length / 2;
  const double halfWidth = width / 2;
  const double halfWidth1 = width1 / 2;
  const double halfWidth2 = width2 / 2;

  // 2. 定义主直通段四个角点
  const gp_Pnt p1(-halfLength, -halfWidth, zoffset); // 左下角
  const gp_Pnt p2(-halfLength, halfWidth, zoffset);  // 左上角
  const gp_Pnt p3(halfLength, halfWidth, zoffset);   // 右上角
  const gp_Pnt p4(halfLength, -halfWidth, zoffset);  // 右下角

  // 3. 定义支线段端点
  const gp_Pnt p7(-halfWidth1, halfWidth + length1,
                  zoffset);                                  // 支线段左上角点
  const gp_Pnt p8(halfWidth1, halfWidth + length1, zoffset); // 支线段右下角点

  // 4. 定义支线段2端点（下方）
  const gp_Pnt p9(-halfWidth2, -halfWidth - length2,
                  zoffset); // 支线段2左下角点
  const gp_Pnt p10(halfWidth2, -halfWidth - length2,
                   zoffset); // 支线段2右下角点

  // 4. 计算圆弧关键点（精确几何关系）
  // 上方圆弧（连接直通段与支线段1）
  const gp_Pnt topRightArcStart(halfWidth1 + cornerRadius, halfWidth, zoffset);
  const gp_Pnt topRightArcEnd(halfWidth1, halfWidth + cornerRadius, zoffset);
  const gp_Pnt topLeftArcStart(-halfWidth1 - cornerRadius, halfWidth, zoffset);
  const gp_Pnt topLeftArcEnd(-halfWidth1, halfWidth + cornerRadius, zoffset);

  // 下方圆弧（连接直通段与支线段2）
  const gp_Pnt bottomRightArcStart(halfWidth2 + cornerRadius, -halfWidth,
                                   zoffset);
  const gp_Pnt bottomRightArcEnd(halfWidth2, -halfWidth - cornerRadius,
                                 zoffset);
  const gp_Pnt bottomLeftArcStart(-halfWidth2 - cornerRadius, -halfWidth,
                                  zoffset);
  const gp_Pnt bottomLeftArcEnd(-halfWidth2, -halfWidth - cornerRadius,
                                zoffset);

  // 6. 构造圆弧几何
  // 上方左圆弧
  gp_Pnt topLeftCircleCenter(-halfWidth1 - cornerRadius,
                             halfWidth + cornerRadius, zoffset);
  gp_Circ topLeftCircle(gp_Ax2(topLeftCircleCenter, gp_Dir(0, 0, 1)),
                        cornerRadius);
  TopoDS_Edge topLeftArc =
      BRepBuilderAPI_MakeEdge(new Geom_Circle(topLeftCircle),
                              ElCLib::Parameter(topLeftCircle, topLeftArcStart),
                              ElCLib::Parameter(topLeftCircle, topLeftArcEnd))
          .Edge();

  // 上方右圆弧
  gp_Pnt topRightCircleCenter(halfWidth1 + cornerRadius,
                              halfWidth + cornerRadius, zoffset);
  gp_Circ topRightCircle(gp_Ax2(topRightCircleCenter, gp_Dir(0, 0, 1)),
                         cornerRadius);
  TopoDS_Edge topRightArc =
      BRepBuilderAPI_MakeEdge(
          new Geom_Circle(topRightCircle),
          ElCLib::Parameter(topRightCircle, topRightArcEnd),
          ElCLib::Parameter(topRightCircle, topRightArcStart))
          .Edge();
  topRightArc.Reverse();

  // 下方左圆弧
  gp_Pnt bottomLeftCircleCenter(-halfWidth2 - cornerRadius,
                                -halfWidth - cornerRadius, zoffset);
  gp_Circ bottomLeftCircle(gp_Ax2(bottomLeftCircleCenter, gp_Dir(0, 0, -1)),
                           cornerRadius);
  TopoDS_Edge bottomLeftArc =
      BRepBuilderAPI_MakeEdge(
          new Geom_Circle(bottomLeftCircle),
          ElCLib::Parameter(bottomLeftCircle, bottomLeftArcStart),
          ElCLib::Parameter(bottomLeftCircle, bottomLeftArcEnd))
          .Edge();

  // 下方右圆弧
  gp_Pnt bottomRightCircleCenter(halfWidth2 + cornerRadius,
                                 -halfWidth - cornerRadius, zoffset);
  gp_Circ bottomRightCircle(gp_Ax2(bottomRightCircleCenter, gp_Dir(0, 0, -1)),
                            cornerRadius);
  TopoDS_Edge bottomRightArc =
      BRepBuilderAPI_MakeEdge(
          new Geom_Circle(bottomRightCircle),
          ElCLib::Parameter(bottomRightCircle, bottomRightArcEnd),
          ElCLib::Parameter(bottomRightCircle, bottomRightArcStart))
          .Edge();
  bottomRightArc.Reverse();

  // 7. 构建完整线框
  BRepBuilderAPI_MakeWire wireMaker;

  // 主直通段左侧边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2));

  // 上方连接段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, topLeftArcStart));
  wireMaker.Add(topLeftArc);
  wireMaker.Add(BRepBuilderAPI_MakeEdge(topLeftArcEnd, p7));

  // 支线段1顶部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8));

  // 上方右侧连接段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, topRightArcEnd));
  wireMaker.Add(topRightArc);
  wireMaker.Add(BRepBuilderAPI_MakeEdge(topRightArcStart, p3));

  // 主直通段右侧边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4));

  // 下方右侧连接段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, bottomRightArcStart));
  wireMaker.Add(bottomRightArc);
  wireMaker.Add(BRepBuilderAPI_MakeEdge(bottomRightArcEnd, p10));

  // 支线段2底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p10, p9));

  // 下方左侧连接段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p9, bottomLeftArcEnd));
  wireMaker.Add(bottomLeftArc);
  wireMaker.Add(BRepBuilderAPI_MakeEdge(bottomLeftArcStart, p1));

  // 8. 创建底面并拉伸
  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("线框构造失败");
  }
  TopoDS_Face face = BRepBuilderAPI_MakeFace(wireMaker.Wire());

  return BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, height)).Shape();
}

/**
 * @brief 创建四通折角工作井
 * @param length 直通段长度(mm)
 * @param width 直通段宽度(mm)
 * @param height 直通段高度(mm)
 * @param length1 支线段长度(mm)
 * @param width1 支线段宽度(mm)
 * @param cornerLength 井转角折角长(mm)
 * @param cornerWidth 井转角折角宽(mm)
 * @param angle  井转角角度
 * @return 四通工作井的形状
 */
TopoDS_Shape create_four_way_corner_working_well_part(
    double length, double width, double height, double length1, double width1,
    double length2, double width2, double cornerLength, double cornerWidth,
    double zoffset) {
  // 参数校验
  if (length <= 0 || width <= 0 || height <= 0 || length1 <= 0 || width1 <= 0 ||
      length2 <= 0 || width2 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }
  if (length1 <= 0 || width1 <= 0) {
    throw Standard_ConstructionError("支线段尺寸参数必须为正数");
  }

  // 1. 计算关键几何参数
  const double halfLength = length / 2;
  const double halfWidth = width / 2;
  const double halfWidth1 = width1 / 2;
  const double halfWidth2 = width2 / 2;

  // 2. 定义主直通段四个角点
  const gp_Pnt p1(-halfLength, -halfWidth, zoffset); // 左下角
  const gp_Pnt p2(-halfLength, halfWidth, zoffset);  // 左上角
  const gp_Pnt p3(halfLength, halfWidth, zoffset);   // 右上角
  const gp_Pnt p4(halfLength, -halfWidth, zoffset);  // 右下角

  // 3. 定义支线段1端点（上方）
  const gp_Pnt p7(-halfWidth1, halfWidth + length1,
                  zoffset); // 支线段1左上角点
  const gp_Pnt p8(halfWidth1, halfWidth + length1,
                  zoffset); // 支线段1右下角点

  // 4. 定义支线段2端点（下方）
  const gp_Pnt p9(-halfWidth2, -halfWidth - length2,
                  zoffset); // 支线段2左下角点
  const gp_Pnt p10(halfWidth2, -halfWidth - length2,
                   zoffset); // 支线段2右下角点

  // 5. 定义转角连接点
  // 上方转角点
  const gp_Pnt topLeftStart(-halfWidth1 - cornerLength, halfWidth, zoffset);
  const gp_Pnt topLeftEnd(-halfWidth1, halfWidth + cornerWidth, zoffset);
  const gp_Pnt topRightStart(halfWidth1 + cornerLength, halfWidth, zoffset);
  const gp_Pnt topRightEnd(halfWidth1, halfWidth + cornerWidth, zoffset);

  // 下方转角点
  const gp_Pnt bottomLeftStart(-halfWidth2 - cornerLength, -halfWidth, zoffset);
  const gp_Pnt bottomLeftEnd(-halfWidth2, -halfWidth - cornerWidth, zoffset);
  const gp_Pnt bottomRightStart(halfWidth2 + cornerLength, -halfWidth, zoffset);
  const gp_Pnt bottomRightEnd(halfWidth2, -halfWidth - cornerWidth, zoffset);

  // 6. 构建完整线框
  BRepBuilderAPI_MakeWire wireMaker;

  // 主直通段左侧边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2));

  // 上方连接段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, topLeftStart));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(topLeftStart, topLeftEnd));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(topLeftEnd, p7));

  // 支线段1顶部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8));

  // 上方右侧连接段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, topRightEnd));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(topRightEnd, topRightStart));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(topRightStart, p3));

  // 主直通段右侧边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4));

  // 下方右侧连接段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, bottomRightStart));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(bottomRightStart, bottomRightEnd));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(bottomRightEnd, p10));

  // 支线段2底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p10, p9));

  // 下方左侧连接段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p9, bottomLeftEnd));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(bottomLeftEnd, bottomLeftStart));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(bottomLeftStart, p1));

  // 7. 创建底面并拉伸
  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("线框构造失败");
  }
  TopoDS_Face face = BRepBuilderAPI_MakeFace(wireMaker.Wire());

  return BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, height)).Shape();
}

TopoDS_Shape create_four_way_working_well(const four_way_well_params &params) {
  if (params.type != four_way_well_type::WORKING_WELL) {
    throw Standard_ConstructionError("four_way_well_type must be WORKING_WELL");
  }
  TopoDS_Shape outer;
  switch (params.cornerStyle) {
  case corner_style::ROUNDED:
    outer = create_four_way_round_working_well_part(
        params.length, params.width + params.outerWallThickness * 2,
        params.height + params.topThickness + params.bottomThickness,
        params.branchLength, params.branchWidth + params.outerWallThickness * 2,
        params.branchLength, params.branchWidth + params.outerWallThickness * 2,
        params.cornerRadius - params.outerWallThickness,
        -params.bottomThickness);
    break;
  case corner_style::ANGLED:
    outer = create_four_way_corner_working_well_part(
        params.length, params.width + params.outerWallThickness * 2,
        params.height + params.topThickness + params.bottomThickness,
        params.branchLength, params.branchWidth + params.outerWallThickness * 2,
        params.branchLength, params.branchWidth + params.outerWallThickness * 2,
        params.cornerLength - params.outerWallThickness,
        params.cornerWidth - params.outerWallThickness,
        -params.bottomThickness);
    break;
  default:
    break;
  }

  TopoDS_Shape inner;
  switch (params.cornerStyle) {
  case corner_style::ROUNDED:
    inner = create_four_way_round_working_well_part(
        params.length + params.outerWallThickness * 2, params.width,
        params.height, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth, params.cornerRadius, 0);
    break;
  case corner_style::ANGLED:
    inner = create_four_way_corner_working_well_part(
        params.length + params.outerWallThickness * 2, params.width,
        params.height, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth, params.cornerLength, params.cornerWidth, 0);
    break;
  default:
    break;
  }

  TopoDS_Shape cushion;
  switch (params.cornerStyle) {
  case corner_style::ROUNDED:
    cushion = create_four_way_round_working_well_part(
        params.length,
        params.width + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cushionThickness, params.branchLength,
        params.branchWidth + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.branchLength,
        params.branchWidth + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cornerRadius - params.outerWallThickness -
            params.cushionExtension,
        -params.bottomThickness - params.cushionThickness);
    break;
  case corner_style::ANGLED:
    cushion = create_four_way_corner_working_well_part(
        params.length,
        params.width + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cushionThickness, params.branchLength,
        params.branchWidth + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.branchLength,
        params.branchWidth + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cornerLength + params.outerWallThickness +
            params.cushionExtension,
        params.cornerWidth + params.outerWallThickness +
            params.cushionExtension,
        -params.bottomThickness - params.cushionThickness);
    break;
  default:
    break;
  }

  // 合并所有部分
  TopoDS_Shape well = BRepAlgoAPI_Cut(outer, inner).Shape();

  well = BRepAlgoAPI_Fuse(well, cushion).Shape();

  return well;
}

TopoDS_Shape
create_four_way_open_cut_tunnel(const four_way_well_params &params) {
  if (params.type != four_way_well_type::OPEN_CUT_TUNNEL) {
    throw Standard_ConstructionError(
        "three_way_open_cut_tunnel must be OPEN_CUT_TUNNEL");
  }
  TopoDS_Shape outer;
  switch (params.cornerStyle) {
  case corner_style::ROUNDED:
    outer = create_four_way_round_working_well_part(
        params.length + params.outerWallThickness * 2,
        params.width + params.outerWallThickness * 2,
        params.height + params.topThickness + params.bottomThickness,
        params.branchLength + params.outerWallThickness * 2,
        params.branchWidth + params.outerWallThickness * 2,
        params.branchLength + params.outerWallThickness * 2,
        params.branchWidth + params.outerWallThickness * 2,
        params.cornerRadius - params.outerWallThickness,
        -params.bottomThickness);
    break;
  case corner_style::ANGLED:
    outer = create_four_way_corner_working_well_part(
        params.length + params.outerWallThickness * 2,
        params.width + params.outerWallThickness * 2,
        params.height + params.topThickness + params.bottomThickness,
        params.branchLength + params.outerWallThickness * 2,
        params.branchWidth + params.outerWallThickness * 2,
        params.branchLength + params.outerWallThickness * 2,
        params.branchWidth + params.outerWallThickness * 2,
        params.cornerLength - params.outerWallThickness,
        params.cornerWidth - params.outerWallThickness,
        -params.bottomThickness);
    break;
  default:
    break;
  }

  // 2. 创建左连接段
  TopoDS_Shape leftTunnel;
  switch (params.leftSection.sectionType) {
  case connection_section_style::RECTANGULAR:
    leftTunnel = create_rectangular_section(
        params.leftSection.length, params.leftSection.width,
        params.leftSection.height, params.outerWallThickness,
        params.topThickness, params.bottomThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    leftTunnel = create_horseshoe_section(
        params.leftSection.length, params.leftSection.width,
        params.leftSection.height, params.leftSection.arcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    leftTunnel = create_circular_section(params.leftSection.length,
                                         params.leftSection.height / 2,
                                         params.outerWallThickness, true);
    break;
  }

  // 移动左连接段到正确位置
  gp_Trsf leftTrsf;
  leftTrsf.SetTranslation(
      gp_Vec(-params.leftSection.length - params.length / 2, 0, 0));
  leftTunnel = BRepBuilderAPI_Transform(leftTunnel, leftTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, leftTunnel).Shape();

  // 3. 创建右连接段
  TopoDS_Shape rightTunnel;
  switch (params.rightSection.sectionType) {
  case connection_section_style::RECTANGULAR:
    rightTunnel = create_rectangular_section(
        params.rightSection.length, params.rightSection.width,
        params.rightSection.height, params.outerWallThickness,
        params.topThickness, params.bottomThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    rightTunnel = create_horseshoe_section(
        params.rightSection.length, params.rightSection.width,
        params.rightSection.height, params.rightSection.arcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    rightTunnel = create_circular_section(params.rightSection.length,
                                          params.rightSection.height / 2,
                                          params.outerWallThickness, true);
    break;
  }

  // 移动支连接段到正确位置
  gp_Trsf rightTrsf;
  rightTrsf.SetTranslation(gp_Vec(params.length / 2, 0, 0));
  rightTunnel = BRepBuilderAPI_Transform(rightTunnel, rightTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, rightTunnel).Shape();

  // 3. 创建上支连接段
  TopoDS_Shape branch1Tunnel;
  switch (params.branchSection1.sectionType) {
  case connection_section_style::RECTANGULAR:
    branch1Tunnel = create_rectangular_section(
        params.branchSection1.length, params.branchSection1.width,
        params.branchSection1.height, params.outerWallThickness,
        params.topThickness, params.bottomThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    branch1Tunnel = create_horseshoe_section(
        params.branchSection1.length, params.branchSection1.width,
        params.branchSection1.height, params.branchSection1.arcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    branch1Tunnel = create_circular_section(params.branchSection1.length,
                                            params.branchSection1.height / 2,
                                            params.outerWallThickness, true);
    break;
  }

  // 移动上连接段到正确位置
  gp_Trsf branch1Trsf;
  gp_Trsf branch1Model;
  branch1Model.SetTranslation(gp_Vec(-params.branchSection1.length / 2, 0, 0));
  gp_Trsf rotate1Trsf;
  rotate1Trsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -1)),
                          90 * M_PI / 180.0);

  branch1Trsf.SetTranslation(gp_Vec(0,
                                    params.branchLength + params.width / 2 +
                                        params.branchSection1.length / 2,
                                    0));
  branch1Tunnel = BRepBuilderAPI_Transform(branch1Tunnel, branch1Model).Shape();
  branch1Tunnel = BRepBuilderAPI_Transform(branch1Tunnel, rotate1Trsf).Shape();
  branch1Tunnel = BRepBuilderAPI_Transform(branch1Tunnel, branch1Trsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, branch1Tunnel).Shape();

  // 4. 创建下支连接段
  TopoDS_Shape branch2Tunnel;
  switch (params.branchSection2.sectionType) {
  case connection_section_style::RECTANGULAR:
    branch2Tunnel = create_rectangular_section(
        params.branchSection2.length, params.branchSection2.width,
        params.branchSection2.height, params.outerWallThickness,
        params.topThickness, params.bottomThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    branch2Tunnel = create_horseshoe_section(
        params.branchSection2.length, params.branchSection2.width,
        params.branchSection2.height, params.branchSection2.arcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    branch2Tunnel = create_circular_section(params.branchSection2.length,
                                            params.branchSection2.height / 2,
                                            params.outerWallThickness, true);
    break;
  }

  // 移动上连接段到正确位置
  gp_Trsf branch2Trsf;
  gp_Trsf branch2Model;
  branch2Model.SetTranslation(gp_Vec(-params.branchSection2.length / 2, 0, 0));
  gp_Trsf rotate2Trsf;
  rotate2Trsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -1)),
                          -90 * M_PI / 180.0);

  branch2Trsf.SetTranslation(gp_Vec(0,
                                    -params.branchLength - params.width / 2 -
                                        params.branchSection2.length / 2,
                                    0));
  branch2Tunnel = BRepBuilderAPI_Transform(branch2Tunnel, branch2Model).Shape();
  branch2Tunnel = BRepBuilderAPI_Transform(branch2Tunnel, rotate2Trsf).Shape();
  branch2Tunnel = BRepBuilderAPI_Transform(branch2Tunnel, branch2Trsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, branch2Tunnel).Shape();

  TopoDS_Shape inner;
  switch (params.cornerStyle) {
  case corner_style::ROUNDED:
    inner = create_four_way_round_working_well_part(
        params.length + params.outerWallThickness * 2, params.width,
        params.height, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth, params.cornerRadius, 0);
    break;
  case corner_style::ANGLED:
    inner = create_four_way_corner_working_well_part(
        params.length + params.outerWallThickness * 2, params.width,
        params.height, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth, params.cornerLength, params.cornerWidth, 0);
    break;
  default:
    break;
  }

  TopoDS_Shape innerLeftTunnel;
  switch (params.leftSection.sectionType) {
  case connection_section_style::RECTANGULAR:
    innerLeftTunnel = create_rectangular_section(
        params.leftSection.length - params.outerWallThickness,
        params.leftSection.width, params.leftSection.height,
        params.outerWallThickness, params.topThickness, params.bottomThickness,
        false);
    break;
  case connection_section_style::HORSESHOE:
    innerLeftTunnel = create_horseshoe_section(
        params.leftSection.length - params.outerWallThickness,
        params.leftSection.width, params.leftSection.height,
        params.leftSection.arcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerLeftTunnel = create_circular_section(
        params.leftSection.length - params.outerWallThickness,
        params.leftSection.height / 2, params.outerWallThickness, false);
    break;
  }

  innerLeftTunnel = BRepBuilderAPI_Transform(innerLeftTunnel, leftTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerLeftTunnel).Shape();

  TopoDS_Shape innerRightTunnel;
  switch (params.rightSection.sectionType) {
  case connection_section_style::RECTANGULAR:
    innerRightTunnel = create_rectangular_section(
        params.rightSection.length - params.outerWallThickness,
        params.rightSection.width, params.rightSection.height,
        params.outerWallThickness, params.topThickness, params.bottomThickness,
        false);
    break;
  case connection_section_style::HORSESHOE:
    innerRightTunnel = create_horseshoe_section(
        params.rightSection.length - params.outerWallThickness,
        params.rightSection.width, params.rightSection.height,
        params.rightSection.arcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerRightTunnel = create_circular_section(
        params.rightSection.length - params.outerWallThickness,
        params.rightSection.height / 2, params.outerWallThickness, false);
    break;
  }

  rightTrsf.SetTranslation(
      gp_Vec(params.length / 2 + params.outerWallThickness, 0, 0));
  innerRightTunnel =
      BRepBuilderAPI_Transform(innerRightTunnel, rightTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerRightTunnel).Shape();

  // 3. 创建上连接段
  TopoDS_Shape innerBranch1Tunnel;
  switch (params.branchSection1.sectionType) {
  case connection_section_style::RECTANGULAR:
    innerBranch1Tunnel = create_rectangular_section(
        params.branchSection1.length - params.outerWallThickness,
        params.branchSection1.width, params.branchSection1.height,
        params.outerWallThickness, params.topThickness, params.bottomThickness,
        false);
    break;
  case connection_section_style::HORSESHOE:
    innerBranch1Tunnel = create_horseshoe_section(
        params.branchSection1.length - params.outerWallThickness,
        params.branchSection1.width, params.branchSection1.height,
        params.branchSection1.arcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerBranch1Tunnel = create_circular_section(
        params.branchSection1.length - params.outerWallThickness,
        params.branchSection1.height / 2, params.outerWallThickness, false);
    break;
  }

  branch1Model.SetTranslation(gp_Vec(
      -(params.branchSection1.length - params.outerWallThickness) / 2, 0, 0));
  branch1Trsf.SetTranslation(gp_Vec(0,
                                    params.branchLength + params.width / 2 +
                                        params.branchSection1.length / 2 +
                                        params.outerWallThickness +
                                        params.outerWallThickness / 2,
                                    0));
  innerBranch1Tunnel =
      BRepBuilderAPI_Transform(innerBranch1Tunnel, branch1Model).Shape();
  innerBranch1Tunnel =
      BRepBuilderAPI_Transform(innerBranch1Tunnel, rotate1Trsf).Shape();
  innerBranch1Tunnel =
      BRepBuilderAPI_Transform(innerBranch1Tunnel, branch1Trsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerBranch1Tunnel).Shape();

  // 4. 创建下连接段
  TopoDS_Shape innerBranch2Tunnel;
  switch (params.branchSection2.sectionType) {
  case connection_section_style::RECTANGULAR:
    innerBranch2Tunnel = create_rectangular_section(
        params.branchSection2.length - params.outerWallThickness,
        params.branchSection2.width, params.branchSection2.height,
        params.outerWallThickness, params.topThickness, params.bottomThickness,
        false);
    break;
  case connection_section_style::HORSESHOE:
    innerBranch2Tunnel = create_horseshoe_section(
        params.branchSection2.length - params.outerWallThickness,
        params.branchSection2.width, params.branchSection2.height,
        params.branchSection2.arcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerBranch2Tunnel = create_circular_section(
        params.branchSection2.length - params.outerWallThickness,
        params.branchSection2.height / 2, params.outerWallThickness, false);
    break;
  }

  branch2Model.SetTranslation(gp_Vec(
      -(params.branchSection2.length - params.outerWallThickness) / 2, 0, 0));
  branch2Trsf.SetTranslation(gp_Vec(0,
                                    -params.branchLength - params.width / 2 -
                                        params.branchSection2.length / 2 -
                                        params.outerWallThickness -
                                        params.outerWallThickness / 2,
                                    0));
  innerBranch2Tunnel =
      BRepBuilderAPI_Transform(innerBranch2Tunnel, branch2Model).Shape();
  innerBranch2Tunnel =
      BRepBuilderAPI_Transform(innerBranch2Tunnel, rotate2Trsf).Shape();
  innerBranch2Tunnel =
      BRepBuilderAPI_Transform(innerBranch2Tunnel, branch2Trsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerBranch2Tunnel).Shape();

  TopoDS_Shape cushion;
  switch (params.cornerStyle) {
  case corner_style::ROUNDED:
    cushion = create_four_way_round_working_well_part(
        params.length + params.leftSection.length + params.rightSection.length,
        params.width + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cushionThickness,
        params.branchLength + params.branchSection1.length,
        params.branchWidth + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.branchLength + params.branchSection2.length,
        params.branchWidth + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cornerRadius - params.outerWallThickness -
            params.cushionExtension,
        -params.bottomThickness - params.cushionThickness);
    break;
  case corner_style::ANGLED:
    cushion = create_four_way_corner_working_well_part(
        params.length + params.leftSection.length + params.rightSection.length,
        params.width + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cushionThickness,
        params.branchLength + params.branchSection1.length,
        params.branchWidth + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.branchLength + params.branchSection2.length,
        params.branchWidth + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cornerLength + params.outerWallThickness +
            params.cushionExtension,
        params.cornerWidth + params.outerWallThickness +
            params.cushionExtension,
        -params.bottomThickness - params.cushionThickness);
    break;
  default:
    break;
  }

  // 合并所有部分
  TopoDS_Shape well = BRepAlgoAPI_Cut(outer, inner).Shape();

  well = BRepAlgoAPI_Fuse(well, cushion).Shape();

  return well;
}

TopoDS_Shape create_four_way_circle_well_part(double length, double width,
                                              double height, double length1,
                                              double width1, double length2,
                                              double width2, double wellRadius,
                                              double weelheight,
                                              double zoffset) {
  // 参数校验
  if (length <= 0 || width <= 0 || height <= 0 || length1 <= 0 || width1 <= 0 ||
      length2 <= 0 || width2 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }

  // 1. 计算关键几何参数
  const double halfLength = length / 2;
  const double halfWidth = width / 2;
  const double halfWidth1 = width1 / 2;
  const double halfWidth2 = width2 / 2;

  // 2. 定义主直通段四个角点
  const gp_Pnt p1(-halfLength, -halfWidth, zoffset); // 左下角
  const gp_Pnt p2(-halfLength, halfWidth, zoffset);  // 左上角
  const gp_Pnt p3(halfLength, halfWidth, zoffset);   // 右上角
  const gp_Pnt p4(halfLength, -halfWidth, zoffset);  // 右下角

  // 3. 定义支线段1端点（上方）
  const gp_Pnt p7(-halfWidth1, halfWidth + length1,
                  zoffset); // 支线段1左上角点
  const gp_Pnt p8(halfWidth1, halfWidth + length1,
                  zoffset);                         // 支线段1右下角点
  const gp_Pnt p9(-halfWidth1, halfWidth, zoffset); // 支线段1左下角点
  const gp_Pnt p10(halfWidth1, halfWidth, zoffset); // 支线段1右下角点

  // 4. 定义支线段2端点（下方）
  const gp_Pnt p11(-halfWidth2, -halfWidth - length2,
                   zoffset); // 支线段2左下角点
  const gp_Pnt p12(halfWidth2, -halfWidth - length2,
                   zoffset);                          // 支线段2右下角点
  const gp_Pnt p13(-halfWidth2, -halfWidth, zoffset); // 支线段2左上角点
  const gp_Pnt p14(halfWidth2, -halfWidth, zoffset);  // 支线段2右上角点

  // 5. 构建完整线框
  BRepBuilderAPI_MakeWire wireMaker;

  // 主直通段左侧边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2));

  // 上方连接段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p9));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p9, p7));

  // 支线段1顶部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8));

  // 上方右侧连接段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, p10));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p10, p3));

  // 主直通段右侧边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4));

  // 下方右侧连接段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p14));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p14, p12));

  // 支线段2底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p12, p11));

  // 下方左侧连接段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p11, p13));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p13, p1));

  // 6. 创建底面并拉伸
  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("线框构造失败");
  }
  TopoDS_Face face = BRepBuilderAPI_MakeFace(wireMaker.Wire());

  TopoDS_Shape tunnel =
      BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, height)).Shape();

  // 创建竖井
  gp_Ax2 wellAxis(gp_Pnt(0, 0, zoffset), gp::DZ());
  TopoDS_Shape well =
      BRepPrimAPI_MakeCylinder(wellAxis, wellRadius, weelheight).Shape();

  return BRepAlgoAPI_Fuse(tunnel, well).Shape();
}

TopoDS_Shape
create_four_way_underground_tunnel(const four_way_well_params &params) {
  if (params.type != four_way_well_type::UNDERGROUND_TUNNEL) {
    throw Standard_ConstructionError(
        "four_way_underground_tunnel must be UNDERGROUND_TUNNEL");
  }
  TopoDS_Shape outer;
  outer = create_four_way_circle_well_part(
      params.length + params.outerWallThickness * 2,
      params.width + params.outerWallThickness * 2,
      params.height + params.outerWallThickness * 2,
      params.branchLength + params.outerWallThickness * 2,
      params.branchWidth + params.outerWallThickness * 2,
      params.branchLength + params.outerWallThickness * 2,
      params.branchWidth + params.outerWallThickness * 2,
      params.shaftRadius + params.outerWallThickness +
          params.innerWallThickness,
      params.height + params.outerWallThickness * 2,
      -params.outerWallThickness);

  // 2. 创建左连接段
  TopoDS_Shape leftTunnel;
  switch (params.leftSection.sectionType) {
  case connection_section_style::RECTANGULAR:
    leftTunnel = create_rectangular_section(
        params.leftSection.length, params.leftSection.width,
        params.leftSection.height, params.outerWallThickness,
        params.topThickness, params.bottomThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    leftTunnel = create_horseshoe_section(
        params.leftSection.length, params.leftSection.width,
        params.leftSection.height, params.leftSection.arcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    leftTunnel = create_circular_section(params.leftSection.length,
                                         params.leftSection.height / 2,
                                         params.outerWallThickness, true);
    break;
  }

  // 移动左连接段到正确位置
  gp_Trsf leftTrsf;
  leftTrsf.SetTranslation(
      gp_Vec(-params.leftSection.length - params.length / 2, 0, 0));
  leftTunnel = BRepBuilderAPI_Transform(leftTunnel, leftTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, leftTunnel).Shape();

  // 3. 创建右连接段
  TopoDS_Shape rightTunnel;
  switch (params.rightSection.sectionType) {
  case connection_section_style::RECTANGULAR:
    rightTunnel = create_rectangular_section(
        params.rightSection.length, params.rightSection.width,
        params.rightSection.height, params.outerWallThickness,
        params.topThickness, params.bottomThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    rightTunnel = create_horseshoe_section(
        params.rightSection.length, params.rightSection.width,
        params.rightSection.height, params.rightSection.arcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    rightTunnel = create_circular_section(params.rightSection.length,
                                          params.rightSection.height / 2,
                                          params.outerWallThickness, true);
    break;
  }

  // 移动支连接段到正确位置
  gp_Trsf rightTrsf;
  rightTrsf.SetTranslation(gp_Vec(params.length / 2, 0, 0));
  rightTunnel = BRepBuilderAPI_Transform(rightTunnel, rightTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, rightTunnel).Shape();

  // 3. 创建上支连接段
  TopoDS_Shape branch1Tunnel;
  switch (params.branchSection1.sectionType) {
  case connection_section_style::RECTANGULAR:
    branch1Tunnel = create_rectangular_section(
        params.branchSection1.length, params.branchSection1.width,
        params.branchSection1.height, params.outerWallThickness,
        params.topThickness, params.bottomThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    branch1Tunnel = create_horseshoe_section(
        params.branchSection1.length, params.branchSection1.width,
        params.branchSection1.height, params.branchSection1.arcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    branch1Tunnel = create_circular_section(params.branchSection1.length,
                                            params.branchSection1.height / 2,
                                            params.outerWallThickness, true);
    break;
  }

  // 移动上连接段到正确位置
  gp_Trsf branch1Trsf;
  gp_Trsf branch1Model;
  branch1Model.SetTranslation(gp_Vec(-params.branchSection1.length / 2, 0, 0));
  gp_Trsf rotate1Trsf;
  rotate1Trsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -1)),
                          90 * M_PI / 180.0);

  branch1Trsf.SetTranslation(gp_Vec(0,
                                    params.branchLength + params.width / 2 +
                                        params.branchSection1.length / 2,
                                    0));
  branch1Tunnel = BRepBuilderAPI_Transform(branch1Tunnel, branch1Model).Shape();
  branch1Tunnel = BRepBuilderAPI_Transform(branch1Tunnel, rotate1Trsf).Shape();
  branch1Tunnel = BRepBuilderAPI_Transform(branch1Tunnel, branch1Trsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, branch1Tunnel).Shape();

  // 4. 创建下支连接段
  TopoDS_Shape branch2Tunnel;
  switch (params.branchSection2.sectionType) {
  case connection_section_style::RECTANGULAR:
    branch2Tunnel = create_rectangular_section(
        params.branchSection2.length, params.branchSection2.width,
        params.branchSection2.height, params.outerWallThickness,
        params.topThickness, params.bottomThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    branch2Tunnel = create_horseshoe_section(
        params.branchSection2.length, params.branchSection2.width,
        params.branchSection2.height, params.branchSection2.arcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    branch2Tunnel = create_circular_section(params.branchSection2.length,
                                            params.branchSection2.height / 2,
                                            params.outerWallThickness, true);
    break;
  }

  // 移动上连接段到正确位置
  gp_Trsf branch2Trsf;
  gp_Trsf branch2Model;
  branch2Model.SetTranslation(gp_Vec(-params.branchSection2.length / 2, 0, 0));
  gp_Trsf rotate2Trsf;
  rotate2Trsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -1)),
                          -90 * M_PI / 180.0);

  branch2Trsf.SetTranslation(gp_Vec(0,
                                    -params.branchLength - params.width / 2 -
                                        params.branchSection2.length / 2,
                                    0));
  branch2Tunnel = BRepBuilderAPI_Transform(branch2Tunnel, branch2Model).Shape();
  branch2Tunnel = BRepBuilderAPI_Transform(branch2Tunnel, rotate2Trsf).Shape();
  branch2Tunnel = BRepBuilderAPI_Transform(branch2Tunnel, branch2Trsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, branch2Tunnel).Shape();

  TopoDS_Shape inner;
  inner = create_four_way_circle_well_part(
      params.length + params.outerWallThickness * 2, params.width,
      params.height, params.branchLength + params.outerWallThickness * 2,
      params.branchWidth, params.branchLength + params.outerWallThickness * 2,
      params.branchWidth, params.shaftRadius,
      params.height + params.outerWallThickness * 2, 0);

  TopoDS_Shape innerLeftTunnel;
  switch (params.leftSection.sectionType) {
  case connection_section_style::RECTANGULAR:
    innerLeftTunnel = create_rectangular_section(
        params.leftSection.length - params.outerWallThickness,
        params.leftSection.width, params.leftSection.height,
        params.outerWallThickness, params.topThickness, params.bottomThickness,
        false);
    break;
  case connection_section_style::HORSESHOE:
    innerLeftTunnel = create_horseshoe_section(
        params.leftSection.length - params.outerWallThickness,
        params.leftSection.width, params.leftSection.height,
        params.leftSection.arcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerLeftTunnel = create_circular_section(
        params.leftSection.length - params.outerWallThickness,
        params.leftSection.height / 2, params.outerWallThickness, false);
    break;
  }

  innerLeftTunnel = BRepBuilderAPI_Transform(innerLeftTunnel, leftTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerLeftTunnel).Shape();

  TopoDS_Shape innerRightTunnel;
  switch (params.rightSection.sectionType) {
  case connection_section_style::RECTANGULAR:
    innerRightTunnel = create_rectangular_section(
        params.rightSection.length - params.outerWallThickness,
        params.rightSection.width, params.rightSection.height,
        params.outerWallThickness, params.topThickness, params.bottomThickness,
        false);
    break;
  case connection_section_style::HORSESHOE:
    innerRightTunnel = create_horseshoe_section(
        params.rightSection.length - params.outerWallThickness,
        params.rightSection.width, params.rightSection.height,
        params.rightSection.arcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerRightTunnel = create_circular_section(
        params.rightSection.length - params.outerWallThickness,
        params.rightSection.height / 2, params.outerWallThickness, false);
    break;
  }

  rightTrsf.SetTranslation(
      gp_Vec(params.length / 2 + params.outerWallThickness, 0, 0));
  innerRightTunnel =
      BRepBuilderAPI_Transform(innerRightTunnel, rightTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerRightTunnel).Shape();

  // 3. 创建上连接段
  TopoDS_Shape innerBranch1Tunnel;
  switch (params.branchSection1.sectionType) {
  case connection_section_style::RECTANGULAR:
    innerBranch1Tunnel = create_rectangular_section(
        params.branchSection1.length - params.outerWallThickness,
        params.branchSection1.width, params.branchSection1.height,
        params.outerWallThickness, params.topThickness, params.bottomThickness,
        false);
    break;
  case connection_section_style::HORSESHOE:
    innerBranch1Tunnel = create_horseshoe_section(
        params.branchSection1.length - params.outerWallThickness,
        params.branchSection1.width, params.branchSection1.height,
        params.branchSection1.arcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerBranch1Tunnel = create_circular_section(
        params.branchSection1.length - params.outerWallThickness,
        params.branchSection1.height / 2, params.outerWallThickness, false);
    break;
  }

  branch1Model.SetTranslation(gp_Vec(
      -(params.branchSection1.length - params.outerWallThickness) / 2, 0, 0));
  branch1Trsf.SetTranslation(gp_Vec(0,
                                    params.branchLength + params.width / 2 +
                                        params.branchSection1.length / 2 +
                                        params.outerWallThickness +
                                        params.outerWallThickness / 2,
                                    0));
  innerBranch1Tunnel =
      BRepBuilderAPI_Transform(innerBranch1Tunnel, branch1Model).Shape();
  innerBranch1Tunnel =
      BRepBuilderAPI_Transform(innerBranch1Tunnel, rotate1Trsf).Shape();
  innerBranch1Tunnel =
      BRepBuilderAPI_Transform(innerBranch1Tunnel, branch1Trsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerBranch1Tunnel).Shape();

  // 4. 创建下连接段
  TopoDS_Shape innerBranch2Tunnel;
  switch (params.branchSection2.sectionType) {
  case connection_section_style::RECTANGULAR:
    innerBranch2Tunnel = create_rectangular_section(
        params.branchSection2.length - params.outerWallThickness,
        params.branchSection2.width, params.branchSection2.height,
        params.outerWallThickness, params.topThickness, params.bottomThickness,
        false);
    break;
  case connection_section_style::HORSESHOE:
    innerBranch2Tunnel = create_horseshoe_section(
        params.branchSection2.length - params.outerWallThickness,
        params.branchSection2.width, params.branchSection2.height,
        params.branchSection2.arcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerBranch2Tunnel = create_circular_section(
        params.branchSection2.length - params.outerWallThickness,
        params.branchSection2.height / 2, params.outerWallThickness, false);
    break;
  }

  branch2Model.SetTranslation(gp_Vec(
      -(params.branchSection2.length - params.outerWallThickness) / 2, 0, 0));
  branch2Trsf.SetTranslation(gp_Vec(0,
                                    -params.branchLength - params.width / 2 -
                                        params.branchSection2.length / 2 -
                                        params.outerWallThickness -
                                        params.outerWallThickness / 2,
                                    0));
  innerBranch2Tunnel =
      BRepBuilderAPI_Transform(innerBranch2Tunnel, branch2Model).Shape();
  innerBranch2Tunnel =
      BRepBuilderAPI_Transform(innerBranch2Tunnel, rotate2Trsf).Shape();
  innerBranch2Tunnel =
      BRepBuilderAPI_Transform(innerBranch2Tunnel, branch2Trsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerBranch2Tunnel).Shape();

  // 合并所有部分
  TopoDS_Shape well = BRepAlgoAPI_Cut(outer, inner).Shape();

  return well;
}

TopoDS_Shape create_four_way_well(const four_way_well_params &params) {
  // 参数验证
  if (params.length <= 0 || params.width <= 0 || params.height <= 0) {
    throw Standard_ConstructionError(
        "Length, width and height must be positive");
  }
  switch (params.type) {
  case four_way_well_type::WORKING_WELL:
    return create_four_way_working_well(params);
  case four_way_well_type::OPEN_CUT_TUNNEL:
    return create_four_way_open_cut_tunnel(params);
  case four_way_well_type::UNDERGROUND_TUNNEL:
    return create_four_way_underground_tunnel(params);
  default:
    break;
  }
}

TopoDS_Shape create_four_way_well(const four_way_well_params &params,
                                  const gp_Pnt &position,
                                  const gp_Dir &direction,
                                  const gp_Dir &xDirection) {
  // 正交性校验
  if (Abs(direction.Dot(xDirection)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDirection must be perpendicular");
  }

  // 创建标准方向的四通井
  TopoDS_Shape junction = create_four_way_well(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDirection);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(junction, transformation);
  return transform.Shape();
}

TopoDS_Shape create_channel_shape(TopoDS_Shape section, TopoDS_Wire pathWire) {
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

// 辅助函数：创建拉管截面
TopoDS_Compound create_pull_pipe_section(const pipe_row_params &params) {
  BRepBuilderAPI_MakeWire outerMaker;

  bool hasArc = false;

  // 创建路径线框
  BRepBuilderAPI_MakeWire pathWire;

  // 处理点序列
  for (size_t i = 0; i < params.points.size() - 1; i++) {
    const gp_Pnt &current = params.points[i].position;
    const gp_Pnt &next = params.points[i + 1].position;

    if (params.points[i].type == 0 &&
        params.points[i + 1].type == 0) { // 普通节点
      // 创建直线段
      pathWire.Add(BRepBuilderAPI_MakeEdge(current, next).Edge());
    } else if (params.points[i].type == 1) { // 弧形节点
      // 确保有前一个点和后一个点
      if (i == 0 || i == params.points.size() - 1) {
        throw Standard_ConstructionError("弧形节点需要前后都有节点");
      }

      const gp_Pnt &prev = params.points[i - 1].position;

      // 创建三点圆弧
      pathWire.Add(BRepBuilderAPI_MakeEdge(
                       GC_MakeArcOfCircle(prev, current, next).Value())
                       .Edge());
      hasArc = true;
    }
  }

  if (!pathWire.IsDone()) {
    throw Standard_ConstructionError("路径线框创建失败");
  }

  TopoDS_Wire path = pathWire.Wire();

  // 获取路径起始点的切线方向
  BRepAdaptor_CompCurve curveAdaptor(path);
  gp_Pnt startPoint;
  gp_Vec startTangent;
  curveAdaptor.D1(curveAdaptor.FirstParameter(), startPoint, startTangent);

  // 在创建截面圆之前添加方向修正
  gp_Dir tanDir = startTangent.Normalized();
  gp_Dir refDir = gp::DZ(); // 默认参考方向为全局Y轴

  // 如果tanDir平行于全局X轴，调整参考方向为全局Z轴
  if (IsParallel(tanDir, gp::DX())) {
    refDir = gp::DZ();
  }
  gp_Ax2 sectionAxes(startPoint, tanDir, refDir);

  // 创建变换对象
  gp_Trsf trsf;
  trsf.SetTransformation(sectionAxes, gp_Ax2(gp::Origin(), gp::DZ()));

  // 创建外管圆
  gp_Circ outerCircle(gp_Ax2(gp::Origin(), gp::DX()),
                      params.pullPipeInnerDiameter / 2 +
                          params.pullPipeThickness);
  outerMaker.Add(BRepBuilderAPI_MakeEdge(outerCircle).Edge());

  BRepBuilderAPI_MakeWire innerMaker;

  // 创建内管圆（挖空）
  gp_Circ innerCircle(gp_Ax2(gp::Origin(), gp::DX()),
                      params.pullPipeInnerDiameter / 2);
  innerMaker.Add(BRepBuilderAPI_MakeEdge(innerCircle).Edge());

  TopoDS_Shape outerPipe = create_channel_shape(outerMaker.Wire(), path);
  TopoDS_Shape innerPipe = create_channel_shape(innerMaker.Wire(), path);

  TopoDS_Shape rpipe = BRepAlgoAPI_Cut(outerPipe, innerPipe).Shape();

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  builder.Add(result, rpipe);

  // 创建内部排管
  for (size_t i = 0; i < params.pipePositions.size(); ++i) {
    BRepBuilderAPI_MakeWire pipeMaker;
    BRepBuilderAPI_MakeWire pipeHoleMaker;

    gp_Pnt localCenter(0, params.pipePositions[i].X(),
                       params.pipePositions[i].Y());
    gp_Pnt projectedPoint = sectionAxes.Location().Translated(
        gp_Vec(localCenter.Z(), localCenter.Y(), 0).Transformed(trsf));

    gp_Circ pipeCircle(gp_Ax2(projectedPoint, tanDir),
                       params.pipeInnerDiameters[i] / 2 +
                           params.pipeWallThicknesses[i]);
    gp_Circ pipeHole(gp_Ax2(projectedPoint, tanDir),
                     params.pipeInnerDiameters[i] / 2);

    pipeMaker.Add(BRepBuilderAPI_MakeEdge(pipeCircle).Edge());
    pipeHoleMaker.Add(BRepBuilderAPI_MakeEdge(pipeHole).Edge());

    TopoDS_Shape outerPipe = create_channel_shape(pipeMaker.Wire(), path);
    TopoDS_Shape holePipe = create_channel_shape(pipeHoleMaker.Wire(), path);

    TopoDS_Shape ipipe = BRepAlgoAPI_Cut(outerPipe, holePipe).Shape();

    builder.Add(result, ipipe);
  }

  return result;
}

// 辅助函数：创建普通排管截面(YZ平面)
TopoDS_Compound create_normal_pipe_section(const pipe_row_params &params) {

  // 创建底板轮廓
  double baseWidth =
      params.hasEnclosure
          ? params.enclosureWidth + 2 * params.baseExtension
          : [&]() {
              // 计算最外侧管道位置(X坐标)
              double minX = std::numeric_limits<double>::max();
              double maxX = std::numeric_limits<double>::lowest();
              for (const auto &pos : params.pipePositions) {
                size_t i = &pos - &params.pipePositions[0];
                double radius = params.pipeInnerDiameters[i] / 2 +
                                params.pipeWallThicknesses[i];
                minX = std::min(minX, pos.X() - radius);
                maxX = std::max(maxX, pos.X() + radius);
              }
              return (maxX - minX) + 2 * params.baseExtension;
            }();
  BRepBuilderAPI_MakeWire baseMaker;

  // 创建路径线框
  BRepBuilderAPI_MakeWire pathWire;

  // 处理点序列
  for (size_t i = 0; i < params.points.size() - 1; i++) {
    const gp_Pnt &current = params.points[i].position;
    const gp_Pnt &next = params.points[i + 1].position;

    if (params.points[i].type == 0 &&
        params.points[i + 1].type == 0) { // 普通节点
      // 创建直线段
      pathWire.Add(BRepBuilderAPI_MakeEdge(current, next).Edge());
    } else if (params.points[i].type == 1) { // 弧形节点
      // 确保有前一个点和后一个点
      if (i == 0 || i == params.points.size() - 1) {
        throw Standard_ConstructionError("弧形节点需要前后都有节点");
      }

      const gp_Pnt &prev = params.points[i - 1].position;

      // 创建三点圆弧
      pathWire.Add(BRepBuilderAPI_MakeEdge(
                       GC_MakeArcOfCircle(prev, current, next).Value())
                       .Edge());
    }
  }

  if (!pathWire.IsDone()) {
    throw Standard_ConstructionError("路径线框创建失败");
  }

  TopoDS_Wire path = pathWire.Wire();

  // 获取路径起始点的切线方向
  BRepAdaptor_CompCurve curveAdaptor(path);
  gp_Pnt startPoint;
  gp_Vec startTangent;
  curveAdaptor.D1(curveAdaptor.FirstParameter(), startPoint, startTangent);

  // 在创建截面圆之前添加方向修正
  gp_Dir tanDir = startTangent.Normalized();
  gp_Dir refDir = gp::DZ(); // 默认参考方向为全局Y轴

  // 如果tanDir平行于全局X轴，调整参考方向为全局Z轴
  if (IsParallel(tanDir, gp::DX())) {
    refDir = gp::DZ();
  }
  gp_Ax2 sectionAxes(startPoint, tanDir, refDir);

  // 创建变换对象
  gp_Trsf trsf;
  trsf.SetTransformation(sectionAxes, gp_Ax2(gp::Origin(), gp::DZ()));

  // YZ平面上的点坐标 (X=0)
  gp_Pnt p1(0, -baseWidth / 2, -params.baseThickness);
  gp_Pnt projectedp1 = sectionAxes.Location().Translated(
      gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));

  gp_Pnt p2(0, baseWidth / 2, -params.baseThickness);
  gp_Pnt projectedp2 = sectionAxes.Location().Translated(
      gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));

  gp_Pnt p3(0, baseWidth / 2, 0);
  gp_Pnt projectedp3 = sectionAxes.Location().Translated(
      gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));

  gp_Pnt p4(0, -baseWidth / 2, 0);
  gp_Pnt projectedp4 = sectionAxes.Location().Translated(
      gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

  baseMaker.Add(BRepBuilderAPI_MakeEdge(projectedp1, projectedp2).Edge());
  baseMaker.Add(BRepBuilderAPI_MakeEdge(projectedp2, projectedp3).Edge());
  baseMaker.Add(BRepBuilderAPI_MakeEdge(projectedp3, projectedp4).Edge());
  baseMaker.Add(BRepBuilderAPI_MakeEdge(projectedp4, projectedp1).Edge());

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  TopoDS_Shape base = create_channel_shape(baseMaker.Wire(), path);

  builder.Add(result, base);

  if (params.cushionExtension > 0 && params.cushionThickness > 0) {
    BRepBuilderAPI_MakeWire cushionMaker;
    gp_Pnt p1(0, -baseWidth / 2 - params.cushionExtension,
              -params.baseThickness - params.cushionThickness);
    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));

    gp_Pnt p2(0, baseWidth / 2 + params.cushionExtension,
              -params.baseThickness - params.cushionThickness);
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));

    gp_Pnt p3(0, baseWidth / 2 + params.cushionExtension,
              -params.baseThickness);
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));

    gp_Pnt p4(0, -baseWidth / 2 - params.cushionExtension,
              -params.baseThickness);
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp1, projectedp2).Edge());
    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp2, projectedp3).Edge());
    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp3, projectedp4).Edge());
    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp4, projectedp1).Edge());

    TopoDS_Shape cushion = create_channel_shape(cushionMaker.Wire(), path);

    builder.Add(result, cushion);
  }

  BRepBuilderAPI_MakeWire wireMaker1;
  TopoDS_Shape enclosure;

  // 创建封包（如果有）
  if (params.hasEnclosure) {
    gp_Pnt e1(0, -params.enclosureWidth / 2, 0);
    gp_Pnt e2(0, -params.enclosureWidth / 2, params.enclosureHeight);
    gp_Pnt e3(0, params.enclosureWidth / 2, params.enclosureHeight);
    gp_Pnt e4(0, params.enclosureWidth / 2, 0);

    gp_Pnt projectede1 = sectionAxes.Location().Translated(
        gp_Vec(e1.Z(), e1.Y(), 0).Transformed(trsf));
    gp_Pnt projectede2 = sectionAxes.Location().Translated(
        gp_Vec(e2.Z(), e2.Y(), 0).Transformed(trsf));
    gp_Pnt projectede3 = sectionAxes.Location().Translated(
        gp_Vec(e3.Z(), e3.Y(), 0).Transformed(trsf));
    gp_Pnt projectede4 = sectionAxes.Location().Translated(
        gp_Vec(e4.Z(), e4.Y(), 0).Transformed(trsf));

    wireMaker1.Add(BRepBuilderAPI_MakeEdge(projectede1, projectede2).Edge());
    wireMaker1.Add(BRepBuilderAPI_MakeEdge(projectede2, projectede3).Edge());
    wireMaker1.Add(BRepBuilderAPI_MakeEdge(projectede3, projectede4).Edge());
    wireMaker1.Add(BRepBuilderAPI_MakeEdge(projectede4, projectede1).Edge());

    enclosure = create_channel_shape(wireMaker1.Wire(), path);
  }

  // 创建管道
  for (size_t i = 0; i < params.pipePositions.size(); ++i) {
    BRepBuilderAPI_MakeWire pipeMaker;
    BRepBuilderAPI_MakeWire pipeHoleMaker;

    // YZ平面上的中心点 (X=0)
    gp_Pnt localCenter(0, params.pipePositions[i].X(),
                       params.pipePositions[i].Y());
    gp_Pnt projectedPoint = sectionAxes.Location().Translated(
        gp_Vec(localCenter.Z(), localCenter.Y(), 0).Transformed(trsf));

    gp_Circ pipeCircle(gp_Ax2(projectedPoint, tanDir), // 法线方向为X轴
                       params.pipeInnerDiameters[i] / 2 +
                           params.pipeWallThicknesses[i]);
    gp_Circ pipeHole(gp_Ax2(projectedPoint, tanDir),
                     params.pipeInnerDiameters[i] / 2);

    pipeMaker.Add(BRepBuilderAPI_MakeEdge(pipeCircle).Edge());
    pipeHoleMaker.Add(BRepBuilderAPI_MakeEdge(pipeHole).Edge());

    TopoDS_Shape pipe = create_channel_shape(pipeMaker.Wire(), path);

    if (params.hasEnclosure) {
      enclosure = BRepAlgoAPI_Cut(enclosure, pipe).Shape();
    } else {
      TopoDS_Shape holePipe = create_channel_shape(pipeHoleMaker.Wire(), path);

      pipe = BRepAlgoAPI_Cut(pipe, holePipe).Shape();
      builder.Add(result, pipe);
    }
  }

  if (params.hasEnclosure) {
    builder.Add(result, enclosure);
  }

  return result;
}

TopoDS_Shape create_pipe_row(const pipe_row_params &params) {
  // 创建截面
  TopoDS_Shape result;
  if (params.pipeType == 1) {
    result = create_normal_pipe_section(params);
  } else {
    result = create_pull_pipe_section(params);
  }

  return result;
}

TopoDS_Shape create_pipe_row(const pipe_row_params &params,
                             const gp_Pnt &position, const gp_Dir &normal,
                             const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 创建标准方向的排管
  TopoDS_Shape pipeRow = create_pipe_row(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(pipeRow, transformation);
  return transform.Shape();
}

TopoDS_Shape create_cable_trench(const cable_trench_params &params) {
  // 参数验证
  if (params.width <= 0 || params.height <= 0) {
    throw Standard_ConstructionError("Width and height must be positive");
  }
  if (params.coverThickness < 0 || params.baseThickness < 0 ||
      params.cushionThickness < 0 || params.wallThickness < 0) {
    throw Standard_ConstructionError("Thickness values must be non-negative");
  }

  BRepBuilderAPI_MakeWire baseMaker;

  // 创建路径线框
  BRepBuilderAPI_MakeWire pathWire;

  // 处理点序列
  for (size_t i = 0; i < params.points.size() - 1; i++) {
    const gp_Pnt &current = params.points[i].position;
    const gp_Pnt &next = params.points[i + 1].position;

    if (params.points[i].type == 0 &&
        params.points[i + 1].type == 0) { // 普通节点
      // 创建直线段
      pathWire.Add(BRepBuilderAPI_MakeEdge(current, next).Edge());
    } else if (params.points[i].type == 1) { // 弧形节点
      // 确保有前一个点和后一个点
      if (i == 0 || i == params.points.size() - 1) {
        throw Standard_ConstructionError("弧形节点需要前后都有节点");
      }

      const gp_Pnt &prev = params.points[i - 1].position;

      // 创建三点圆弧
      pathWire.Add(BRepBuilderAPI_MakeEdge(
                       GC_MakeArcOfCircle(prev, current, next).Value())
                       .Edge());
    }
  }

  if (!pathWire.IsDone()) {
    throw Standard_ConstructionError("路径线框创建失败");
  }

  TopoDS_Wire path = pathWire.Wire();

  // 获取路径起始点的切线方向
  BRepAdaptor_CompCurve curveAdaptor(path);
  gp_Pnt startPoint;
  gp_Vec startTangent;
  curveAdaptor.D1(curveAdaptor.FirstParameter(), startPoint, startTangent);

  // 在创建截面圆之前添加方向修正
  gp_Dir tanDir = startTangent.Normalized();
  gp_Dir refDir = gp::DZ(); // 默认参考方向为全局Y轴

  // 如果tanDir平行于全局X轴，调整参考方向为全局Z轴
  if (IsParallel(tanDir, gp::DX())) {
    refDir = gp::DZ();
  }
  gp_Ax2 sectionAxes(startPoint, tanDir, refDir);

  // 创建变换对象
  gp_Trsf trsf;
  trsf.SetTransformation(sectionAxes, gp_Ax2(gp::Origin(), gp::DZ()));

  double baseWidth =
      params.width + 2 * params.wallThickness + 2 * params.baseExtension;

  // YZ平面上的点坐标 (X=0)
  gp_Pnt p1(0, -baseWidth / 2, -params.baseThickness);
  gp_Pnt p2(0, baseWidth / 2, -params.baseThickness);
  gp_Pnt p3(0, baseWidth / 2, 0);
  gp_Pnt p4(0, -baseWidth / 2, 0);

  gp_Pnt projectedp1 = sectionAxes.Location().Translated(
      gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));
  gp_Pnt projectedp2 = sectionAxes.Location().Translated(
      gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));
  gp_Pnt projectedp3 = sectionAxes.Location().Translated(
      gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));
  gp_Pnt projectedp4 = sectionAxes.Location().Translated(
      gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

  baseMaker.Add(BRepBuilderAPI_MakeEdge(projectedp1, projectedp2).Edge());
  baseMaker.Add(BRepBuilderAPI_MakeEdge(projectedp2, projectedp3).Edge());
  baseMaker.Add(BRepBuilderAPI_MakeEdge(projectedp3, projectedp4).Edge());
  baseMaker.Add(BRepBuilderAPI_MakeEdge(projectedp4, projectedp1).Edge());

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  TopoDS_Shape base = create_channel_shape(baseMaker.Wire(), path);

  builder.Add(result, base);

  if (params.cushionExtension > 0 && params.cushionThickness > 0) {
    BRepBuilderAPI_MakeWire cushionMaker;
    gp_Pnt p1(0, -baseWidth / 2 - params.cushionExtension,
              -params.baseThickness - params.cushionThickness);
    gp_Pnt p2(0, baseWidth / 2 + params.cushionExtension,
              -params.baseThickness - params.cushionThickness);
    gp_Pnt p3(0, baseWidth / 2 + params.cushionExtension,
              -params.baseThickness);
    gp_Pnt p4(0, -baseWidth / 2 - params.cushionExtension,
              -params.baseThickness);

    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp1, projectedp2).Edge());
    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp2, projectedp3).Edge());
    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp3, projectedp4).Edge());
    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp4, projectedp1).Edge());

    TopoDS_Shape cushion = create_channel_shape(cushionMaker.Wire(), path);

    builder.Add(result, cushion);
  }

  // 创建盖板
  TopoDS_Shape cover;
  if (params.coverThickness > 0) {
    BRepBuilderAPI_MakeWire coverMaker;
    double coverWidth = params.coverWidth > 0
                            ? params.coverWidth
                            : params.width + 2 * params.wallThickness;

    gp_Pnt p1(0, -params.coverWidth / 2, params.height);
    gp_Pnt p2(0, params.coverWidth / 2, params.height);
    gp_Pnt p3(0, params.coverWidth / 2, params.height + params.coverThickness);
    gp_Pnt p4(0, -params.coverWidth / 2, params.height + params.coverThickness);

    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    coverMaker.Add(BRepBuilderAPI_MakeEdge(projectedp1, projectedp2).Edge());
    coverMaker.Add(BRepBuilderAPI_MakeEdge(projectedp2, projectedp3).Edge());
    coverMaker.Add(BRepBuilderAPI_MakeEdge(projectedp3, projectedp4).Edge());
    coverMaker.Add(BRepBuilderAPI_MakeEdge(projectedp4, projectedp1).Edge());

    TopoDS_Shape cover = create_channel_shape(coverMaker.Wire(), path);

    builder.Add(result, cover);
  }

  // 创建墙壁
  {
    BRepBuilderAPI_MakeWire wall1Maker;
    double wall1Width = params.width + 2 * params.wallThickness;
    gp_Pnt p1(0, params.width / 2, 0);
    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));

    gp_Pnt p2(0, wall1Width / 2, 0);
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));

    gp_Pnt p3(0, wall1Width / 2, params.height + params.coverThickness);
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));

    gp_Pnt p4(0, wall1Width / 2 - params.wallThickness2,
              params.height + params.coverThickness);
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    gp_Pnt p5(0, wall1Width / 2 - params.wallThickness2, params.height);
    gp_Pnt projectedp5 = sectionAxes.Location().Translated(
        gp_Vec(p5.Z(), p5.Y(), 0).Transformed(trsf));

    gp_Pnt p6(0, params.width / 2, params.height);
    gp_Pnt projectedp6 = sectionAxes.Location().Translated(
        gp_Vec(p6.Z(), p6.Y(), 0).Transformed(trsf));

    wall1Maker.Add(BRepBuilderAPI_MakeEdge(projectedp1, projectedp2).Edge());
    wall1Maker.Add(BRepBuilderAPI_MakeEdge(projectedp2, projectedp3).Edge());
    wall1Maker.Add(BRepBuilderAPI_MakeEdge(projectedp3, projectedp4).Edge());
    wall1Maker.Add(BRepBuilderAPI_MakeEdge(projectedp4, projectedp5).Edge());
    wall1Maker.Add(BRepBuilderAPI_MakeEdge(projectedp5, projectedp6).Edge());
    wall1Maker.Add(BRepBuilderAPI_MakeEdge(projectedp6, projectedp1).Edge());
    TopoDS_Shape wall = create_channel_shape(wall1Maker.Wire(), path);
    builder.Add(result, wall);
  }
  {
    BRepBuilderAPI_MakeWire wall2Maker;
    double wall1Width = params.width + 2 * params.wallThickness;
    gp_Pnt p1(0, -params.width / 2, 0);
    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));

    gp_Pnt p2(0, -wall1Width / 2, 0);
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));

    gp_Pnt p3(0, -wall1Width / 2, params.height + params.coverThickness);
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));

    gp_Pnt p4(0, -wall1Width / 2 + params.wallThickness2,
              params.height + params.coverThickness);
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    gp_Pnt p5(0, -wall1Width / 2 + params.wallThickness2, params.height);
    gp_Pnt projectedp5 = sectionAxes.Location().Translated(
        gp_Vec(p5.Z(), p5.Y(), 0).Transformed(trsf));

    gp_Pnt p6(0, -params.width / 2, params.height);
    gp_Pnt projectedp6 = sectionAxes.Location().Translated(
        gp_Vec(p6.Z(), p6.Y(), 0).Transformed(trsf));

    wall2Maker.Add(BRepBuilderAPI_MakeEdge(projectedp1, projectedp2).Edge());
    wall2Maker.Add(BRepBuilderAPI_MakeEdge(projectedp2, projectedp3).Edge());
    wall2Maker.Add(BRepBuilderAPI_MakeEdge(projectedp3, projectedp4).Edge());
    wall2Maker.Add(BRepBuilderAPI_MakeEdge(projectedp4, projectedp5).Edge());
    wall2Maker.Add(BRepBuilderAPI_MakeEdge(projectedp5, projectedp6).Edge());
    wall2Maker.Add(BRepBuilderAPI_MakeEdge(projectedp6, projectedp1).Edge());
    TopoDS_Shape wall = create_channel_shape(wall2Maker.Wire(), path);
    builder.Add(result, wall);
  }

  return result;
}

TopoDS_Shape create_cable_trench(const cable_trench_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction, const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的电缆沟
  TopoDS_Shape trench = create_cable_trench(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(trench, transformation);

  return transform.Shape();
}

TopoDS_Shape create_cable_tunnel(const cable_tunnel_params &params) {
  // 参数验证
  if (params.width <= 0 || params.height <= 0) {
    throw Standard_ConstructionError("Width and height must be positive");
  }
  if (params.points.size() < 2) {
    throw Standard_ConstructionError("At least 2 points are required");
  }

  // 创建路径线框
  BRepBuilderAPI_MakeWire pathWire;

  // 处理点序列
  for (size_t i = 0; i < params.points.size() - 1; i++) {
    const gp_Pnt &current = params.points[i].position;
    const gp_Pnt &next = params.points[i + 1].position;

    if (params.points[i].type == 0 &&
        params.points[i + 1].type == 0) { // 普通节点
      // 创建直线段
      pathWire.Add(BRepBuilderAPI_MakeEdge(current, next).Edge());
    } else if (params.points[i].type == 1) { // 弧形节点
      // 确保有前一个点和后一个点
      if (i == 0 || i == params.points.size() - 1) {
        throw Standard_ConstructionError("弧形节点需要前后都有节点");
      }

      const gp_Pnt &prev = params.points[i - 1].position;

      // 创建三点圆弧
      pathWire.Add(BRepBuilderAPI_MakeEdge(
                       GC_MakeArcOfCircle(prev, current, next).Value())
                       .Edge());
    }
  }

  if (!pathWire.IsDone()) {
    throw Standard_ConstructionError("路径线框创建失败");
  }

  TopoDS_Wire path = pathWire.Wire();

  // 获取路径起始点的切线方向
  BRepAdaptor_CompCurve curveAdaptor(path);
  gp_Pnt startPoint;
  gp_Vec startTangent;
  curveAdaptor.D1(curveAdaptor.FirstParameter(), startPoint, startTangent);

  // 在创建截面圆之前添加方向修正
  gp_Dir tanDir = startTangent.Normalized();
  gp_Dir refDir = gp::DZ(); // 默认参考方向为全局Y轴

  // 如果tanDir平行于全局X轴，调整参考方向为全局Z轴
  if (IsParallel(tanDir, gp::DX())) {
    refDir = gp::DZ();
  }
  gp_Ax2 sectionAxes(startPoint, tanDir, refDir);

  // 创建变换对象
  gp_Trsf trsf;
  trsf.SetTransformation(sectionAxes, gp_Ax2(gp::Origin(), gp::DZ()));

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  if (params.cushionExtension > 0 && params.cushionThickness > 0 &&
      params.style != connection_section_style::CIRCULAR) {
    double zoffset = -params.cushionThickness;

    if (params.style == connection_section_style::HORSESHOE) {
      zoffset = -params.cushionThickness - params.outerWallThickness -
                params.innerWallThickness;
    }

    double cushionWidth = params.width + 2 * params.cushionExtension +
                          2 * params.outerWallThickness;
    BRepBuilderAPI_MakeWire cushionMaker;
    gp_Pnt p1(0, -cushionWidth / 2 - params.cushionExtension, zoffset);
    gp_Pnt p2(0, cushionWidth / 2 + params.cushionExtension, zoffset);
    gp_Pnt p3(0, cushionWidth / 2 + params.cushionExtension,
              zoffset + params.cushionThickness);
    gp_Pnt p4(0, -cushionWidth / 2 - params.cushionExtension,
              zoffset + params.cushionThickness);

    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp1, projectedp2).Edge());
    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp2, projectedp3).Edge());
    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp3, projectedp4).Edge());
    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp4, projectedp1).Edge());

    TopoDS_Shape cushion = create_channel_shape(cushionMaker.Wire(), path);

    builder.Add(result, cushion);
  }

  // 创建隧道截面轮廓
  TopoDS_Wire outerWire;
  switch (params.style) {
  case connection_section_style::RECTANGULAR: {
    // 矩形截面
    double width = params.width + 2 * params.outerWallThickness;
    gp_Pnt p1(0, -width / 2, -params.bottomThickness);
    gp_Pnt p2(0, width / 2, -params.bottomThickness);
    gp_Pnt p3(0, width / 2, params.height + params.topThickness);
    gp_Pnt p4(0, -width / 2, params.height + params.topThickness);

    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    outerWire = BRepBuilderAPI_MakePolygon(projectedp1, projectedp2,
                                           projectedp3, projectedp4, true)
                    .Wire();
    break;
  }
  case connection_section_style::HORSESHOE: {
    // 马蹄形截面 - 外部轮廓
    double outerWidth = params.width + 2 * params.outerWallThickness +
                        2 * params.innerWallThickness;
    double outerRadius = outerWidth / 2;
    double outerHeight =
        params.height + params.outerWallThickness + params.innerWallThickness;
    double outerArchHeight = params.arcHeight + params.outerWallThickness +
                             params.innerWallThickness;

    // 底部点
    gp_Pnt localBottomLeft(0, -outerRadius,
                           -params.outerWallThickness -
                               params.innerWallThickness);
    gp_Pnt bottomLeft = sectionAxes.Location().Translated(
        gp_Vec(localBottomLeft.Z(), localBottomLeft.Y(), 0).Transformed(trsf));

    gp_Pnt localBottomRight(
        0, outerRadius, -params.outerWallThickness - params.innerWallThickness);
    gp_Pnt bottomRight = sectionAxes.Location().Translated(
        gp_Vec(localBottomRight.Z(), localBottomRight.Y(), 0)
            .Transformed(trsf));

    // 侧壁点
    gp_Pnt localLeftTop(0, -outerRadius, outerHeight);
    gp_Pnt leftTop = sectionAxes.Location().Translated(
        gp_Vec(localLeftTop.Z(), localLeftTop.Y(), 0).Transformed(trsf));

    gp_Pnt localRightTop(0, outerRadius, outerHeight);
    gp_Pnt rightTop = sectionAxes.Location().Translated(
        gp_Vec(localRightTop.Z(), localRightTop.Y(), 0).Transformed(trsf));

    // 顶部圆弧中点
    gp_Pnt localArcMid(0, 0, outerHeight + outerArchHeight);
    gp_Pnt arcMid = sectionAxes.Location().Translated(
        gp_Vec(localArcMid.Z(), localArcMid.Y(), 0).Transformed(trsf));

    // 创建侧壁直线
    TopoDS_Edge leftEdge = BRepBuilderAPI_MakeEdge(bottomLeft, leftTop).Edge();
    TopoDS_Edge rightEdge =
        BRepBuilderAPI_MakeEdge(bottomRight, rightTop).Edge();

    // 创建顶部圆弧 (从右到左)
    Handle(Geom_TrimmedCurve) topArc =
        GC_MakeArcOfCircle(rightTop, arcMid, leftTop).Value();
    TopoDS_Edge topEdge = BRepBuilderAPI_MakeEdge(topArc).Edge();

    // 创建底部直线
    TopoDS_Edge bottomEdge =
        BRepBuilderAPI_MakeEdge(bottomLeft, bottomRight).Edge();

    // 组合成完整轮廓 (确保闭合)
    BRepBuilderAPI_MakeWire wireMaker;
    wireMaker.Add(leftEdge);
    wireMaker.Add(topEdge);
    wireMaker.Add(rightEdge);
    wireMaker.Add(bottomEdge);

    if (!wireMaker.IsDone()) {
      throw Standard_ConstructionError(
          "Failed to create closed wire for horseshoe section");
    }

    outerWire = wireMaker.Wire();

    if (!outerWire.Closed()) {
      throw Standard_ConstructionError("Outer horseshoe section is not closed");
    }
    break;
  }
  case connection_section_style::CIRCULAR: {
    // 圆形截面 - 外部轮廓
    double outerRadius = params.width / 2 + params.outerWallThickness;
    gp_Pnt center(0, 0, 0);
    Handle(Geom_Circle) outerCircle =
        new Geom_Circle(gp_Ax2(center, gp::DX()), outerRadius);
    TopoDS_Edge outerEdge = BRepBuilderAPI_MakeEdge(outerCircle).Edge();
    outerWire = BRepBuilderAPI_MakeWire(outerEdge).Wire();
    break;
  }
  default:
    throw Standard_ConstructionError("Invalid tunnel section style");
  }
  TopoDS_Shape outer = create_channel_shape(outerWire, path);

  // 创建隧道截面轮廓
  TopoDS_Wire innerWire;
  switch (params.style) {
  case connection_section_style::RECTANGULAR: {
    // 矩形截面
    gp_Pnt p1(0, -params.width / 2, 0);
    gp_Pnt p2(0, params.width / 2, 0);
    gp_Pnt p3(0, params.width / 2, params.height);
    gp_Pnt p4(0, -params.width / 2, params.height);

    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    innerWire = BRepBuilderAPI_MakePolygon(projectedp1, projectedp2,
                                           projectedp3, projectedp4, true)
                    .Wire();
    break;
  }
  case connection_section_style::HORSESHOE: {
    // 马蹄形截面 - 内部轮廓
    double innerRadius = params.width / 2;
    double innerHeight = params.height;
    double innerArchHeight = params.arcHeight;

    // 底部点
    gp_Pnt localBottomLeft(0, -innerRadius, 0);
    gp_Pnt bottomLeft = sectionAxes.Location().Translated(
        gp_Vec(localBottomLeft.Z(), localBottomLeft.Y(), 0).Transformed(trsf));

    gp_Pnt localBottomRight(0, innerRadius, 0);
    gp_Pnt bottomRight = sectionAxes.Location().Translated(
        gp_Vec(localBottomRight.Z(), localBottomRight.Y(), 0)
            .Transformed(trsf));

    // 侧壁点
    gp_Pnt localLeftTop(0, -innerRadius, innerHeight);
    gp_Pnt leftTop = sectionAxes.Location().Translated(
        gp_Vec(localLeftTop.Z(), localLeftTop.Y(), 0).Transformed(trsf));

    gp_Pnt localRightTop(0, innerRadius, innerHeight);
    gp_Pnt rightTop = sectionAxes.Location().Translated(
        gp_Vec(localRightTop.Z(), localRightTop.Y(), 0).Transformed(trsf));

    // 顶部圆弧中点
    gp_Pnt localArcMid(0, 0, innerHeight + innerArchHeight);
    gp_Pnt arcMid = sectionAxes.Location().Translated(
        gp_Vec(localArcMid.Z(), localArcMid.Y(), 0).Transformed(trsf));

    // 创建侧壁直线
    TopoDS_Edge leftEdge = BRepBuilderAPI_MakeEdge(bottomLeft, leftTop).Edge();
    TopoDS_Edge rightEdge =
        BRepBuilderAPI_MakeEdge(bottomRight, rightTop).Edge();

    // 创建顶部圆弧 (从右到左)
    Handle(Geom_TrimmedCurve) topArc =
        GC_MakeArcOfCircle(rightTop, arcMid, leftTop).Value();
    TopoDS_Edge topEdge = BRepBuilderAPI_MakeEdge(topArc).Edge();

    // 创建底部直线
    TopoDS_Edge bottomEdge =
        BRepBuilderAPI_MakeEdge(bottomLeft, bottomRight).Edge();

    // 组合成完整轮廓 (确保闭合)
    BRepBuilderAPI_MakeWire wireMaker;
    wireMaker.Add(leftEdge);
    wireMaker.Add(topEdge);
    wireMaker.Add(rightEdge);
    wireMaker.Add(bottomEdge);

    if (!wireMaker.IsDone()) {
      throw Standard_ConstructionError(
          "Failed to create closed wire for inner horseshoe section");
    }

    innerWire = wireMaker.Wire();

    if (!innerWire.Closed()) {
      throw Standard_ConstructionError("Inner horseshoe section is not closed");
    }
    break;
  }
  case connection_section_style::CIRCULAR: {
    // 圆形截面 - 内部轮廓
    double innerRadius = params.width / 2;
    gp_Pnt center(0, 0, 0);
    Handle(Geom_Circle) innerCircle =
        new Geom_Circle(gp_Ax2(center, gp::DX()), innerRadius);
    TopoDS_Edge innerEdge = BRepBuilderAPI_MakeEdge(innerCircle).Edge();
    innerWire = BRepBuilderAPI_MakeWire(innerEdge).Wire();

    break;
  }
  default:
    throw Standard_ConstructionError("Invalid tunnel section style");
  }

  TopoDS_Shape inner = create_channel_shape(innerWire, path);

  // 处理底部平台
  if (params.style == connection_section_style::CIRCULAR &&
      params.bottomPlatformHeight != 0) {
    double innerRadius = params.width / 2;

    double zoffset = -innerRadius;
    gp_Pnt p1(0, -innerRadius, -innerRadius + params.bottomPlatformHeight);
    gp_Pnt p2(0, innerRadius, -innerRadius + params.bottomPlatformHeight);
    gp_Pnt p3(0, innerRadius, -innerRadius);
    gp_Pnt p4(0, -innerRadius, -innerRadius);

    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    TopoDS_Wire tempWire =
        BRepBuilderAPI_MakePolygon(projectedp1, projectedp2, projectedp3,
                                   projectedp4, true)
            .Wire();
    TopoDS_Shape cutBottom = create_channel_shape(tempWire, path);

    inner = BRepAlgoAPI_Cut(inner, cutBottom).Shape();
  }

  TopoDS_Shape tunnel = BRepAlgoAPI_Cut(outer, inner).Shape();
  builder.Add(result, tunnel);

  return result;
}

TopoDS_Shape create_cable_tunnel(const cable_tunnel_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction, const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的电缆隧道
  TopoDS_Shape tunnel = create_cable_tunnel(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(tunnel, transformation);
  return transform.Shape();
}

TopoDS_Shape create_cable_tray(const cable_tray_params &params) {
  // 参数验证
  if (params.width <= 0 || params.height <= 0 || params.span <= 0) {
    throw Standard_ConstructionError("Width, height and span must be positive");
  }
  if (params.points.size() < 2) {
    throw Standard_ConstructionError("At least 2 points are required");
  }

  // 创建路径线框
  BRepBuilderAPI_MakeWire pathWire;

  // 处理点序列
  for (size_t i = 0; i < params.points.size() - 1; i++) {
    const gp_Pnt &current = params.points[i].position;
    const gp_Pnt &next = params.points[i + 1].position;

    if (params.points[i].type == 0 &&
        params.points[i + 1].type == 0) { // 普通节点
      // 创建直线段
      pathWire.Add(BRepBuilderAPI_MakeEdge(current, next).Edge());
    } else if (params.points[i].type == 1) { // 弧形节点
      // 确保有前一个点和后一个点
      if (i == 0 || i == params.points.size() - 1) {
        throw Standard_ConstructionError("弧形节点需要前后都有节点");
      }

      const gp_Pnt &prev = params.points[i - 1].position;

      // 创建三点圆弧
      pathWire.Add(BRepBuilderAPI_MakeEdge(
                       GC_MakeArcOfCircle(prev, current, next).Value())
                       .Edge());
    }
  }

  if (!pathWire.IsDone()) {
    throw Standard_ConstructionError("路径线框创建失败");
  }

  TopoDS_Wire path = pathWire.Wire();

  // 获取路径起始点的切线方向
  BRepAdaptor_CompCurve curveAdaptor(path);
  gp_Pnt startPoint;
  gp_Vec startTangent;
  curveAdaptor.D1(curveAdaptor.FirstParameter(), startPoint, startTangent);

  // 在创建截面圆之前添加方向修正
  gp_Dir tanDir = startTangent.Normalized();
  gp_Dir refDir = gp::DZ(); // 默认参考方向为全局Y轴

  // 如果tanDir平行于全局X轴，调整参考方向为全局Z轴
  if (IsParallel(tanDir, gp::DX())) {
    refDir = gp::DZ();
  }
  gp_Ax2 sectionAxes(startPoint, tanDir, refDir);

  // 创建变换对象
  gp_Trsf trsf;
  trsf.SetTransformation(sectionAxes, gp_Ax2(gp::Origin(), gp::DZ()));

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  // 创建管道
  for (size_t i = 0; i < params.pipePositions.size(); ++i) {
    BRepBuilderAPI_MakeWire pipeMaker;
    BRepBuilderAPI_MakeWire pipeHoleMaker;

    // YZ平面上的中心点 (X=0)
    gp_Pnt localCenter(0, params.pipePositions[i].X(),
                       params.pipePositions[i].Y());

    gp_Pnt projectedPoint = sectionAxes.Location().Translated(
        gp_Vec(localCenter.Z(), localCenter.Y(), 0).Transformed(trsf));

    gp_Circ pipeCircle(gp_Ax2(projectedPoint, tanDir), // 法线方向为X轴
                       params.pipeInnerDiameters[i] / 2 +
                           params.pipeWallThicknesses[i]);
    gp_Circ pipeHole(gp_Ax2(projectedPoint, tanDir),
                     params.pipeInnerDiameters[i] / 2);

    pipeMaker.Add(BRepBuilderAPI_MakeEdge(pipeCircle).Edge());
    pipeHoleMaker.Add(BRepBuilderAPI_MakeEdge(pipeHole).Edge());

    TopoDS_Shape pipe = create_channel_shape(pipeMaker.Wire(), path);

    TopoDS_Shape holePipe = create_channel_shape(pipeHoleMaker.Wire(), path);

    pipe = BRepAlgoAPI_Cut(pipe, holePipe).Shape();
    builder.Add(result, pipe);
  }

  // 创建盖板
  TopoDS_Shape cover;
  if (params.topPlateHeight > 0) {
    BRepBuilderAPI_MakeWire coverMaker;

    gp_Pnt p1(0, -params.width / 2, params.height);
    gp_Pnt p2(0, params.width / 2, params.height);
    gp_Pnt p3(0, params.width / 2, params.height + params.topPlateHeight);
    gp_Pnt p4(0, -params.width / 2, params.height + params.topPlateHeight);

    coverMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
    coverMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
    coverMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
    coverMaker.Add(BRepBuilderAPI_MakeEdge(p4, p1).Edge());

    TopoDS_Shape cover = create_channel_shape(coverMaker.Wire(), path);

    builder.Add(result, cover);
  }

  // 创建墙壁
  {
    BRepBuilderAPI_MakeWire wall1Maker;
    double wall1Width = params.width;
    gp_Pnt p1(0, wall1Width / 2, 0);
    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));

    gp_Pnt p2(0, wall1Width / 2, params.height);
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));

    gp_Pnt p3(0, wall1Width / 2 - params.wallThickness, params.height);
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));

    gp_Pnt p4(0, params.width / 2 - params.wallThickness, 0);
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    wall1Maker.Add(BRepBuilderAPI_MakeEdge(projectedp1, projectedp2).Edge());
    wall1Maker.Add(BRepBuilderAPI_MakeEdge(projectedp2, projectedp3).Edge());
    wall1Maker.Add(BRepBuilderAPI_MakeEdge(projectedp3, projectedp4).Edge());
    wall1Maker.Add(BRepBuilderAPI_MakeEdge(projectedp4, projectedp1).Edge());
    TopoDS_Shape wall = create_channel_shape(wall1Maker.Wire(), path);
    builder.Add(result, wall);
  }
  {
    BRepBuilderAPI_MakeWire wall2Maker;
    double wall1Width = params.width;
    gp_Pnt p1(0, -wall1Width / 2, 0);
    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));

    gp_Pnt p2(0, -wall1Width / 2, params.height);
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));

    gp_Pnt p3(0, -wall1Width / 2 + params.wallThickness, params.height);
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));

    gp_Pnt p4(0, -wall1Width / 2 + params.wallThickness, 0);
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    wall2Maker.Add(BRepBuilderAPI_MakeEdge(projectedp1, projectedp2).Edge());
    wall2Maker.Add(BRepBuilderAPI_MakeEdge(projectedp2, projectedp3).Edge());
    wall2Maker.Add(BRepBuilderAPI_MakeEdge(projectedp3, projectedp4).Edge());
    wall2Maker.Add(BRepBuilderAPI_MakeEdge(projectedp4, projectedp1).Edge());
    TopoDS_Shape wall = create_channel_shape(wall2Maker.Wire(), path);
    builder.Add(result, wall);
  }

  // 计算路径总长度
  GProp_GProps props;
  BRepGProp::LinearProperties(path, props);
  double totalLength = props.Mass();

  // 创建桥柱
  if (params.columnDiameter > 0 && params.columnHeight > 0) {
    // 沿路径生成桥柱
    double currentPos = 0;
    while (currentPos < totalLength) {
      // 获取路径上当前点的位置和切线方向
      gp_Pnt pointOnPath;
      gp_Vec tangent;

      // 遍历Wire中的边来找到当前位置对应的边
      TopExp_Explorer edgeExplorer(path, TopAbs_EDGE);
      double accumulatedLength = 0;
      bool found = false;

      for (; edgeExplorer.More() && !found; edgeExplorer.Next()) {
        const TopoDS_Edge &edge = TopoDS::Edge(edgeExplorer.Current());

        // 计算当前边的长度
        GProp_GProps edgeProps;
        BRepGProp::LinearProperties(edge, edgeProps);
        double edgeLength = edgeProps.Mass();

        if (currentPos <= accumulatedLength + edgeLength) {
          // 找到包含当前点的边
          BRepAdaptor_Curve curveAdaptor(edge);
          double param = curveAdaptor.FirstParameter() +
                         (currentPos - accumulatedLength) / edgeLength *
                             (curveAdaptor.LastParameter() -
                              curveAdaptor.FirstParameter());

          curveAdaptor.D1(param, pointOnPath, tangent);
          found = true;
        }
        accumulatedLength += edgeLength;
      }

      // 创建桥柱坐标系
      gp_Dir upDir(0, 0, 1);

      // 创建圆柱形桥柱
      gp_Ax2 columnAxis(gp_Pnt(pointOnPath.X(), pointOnPath.Y(),
                               pointOnPath.Z() - params.columnHeight),
                        upDir);
      TopoDS_Shape column =
          BRepPrimAPI_MakeCylinder(columnAxis, params.columnDiameter / 2,
                                   params.columnHeight)
              .Shape();

      builder.Add(result, column);
      currentPos += params.span;
    }
  }

  if (params.style == cable_tray_style::ARCH && (params.points.size() == 2) &&
      totalLength >= params.span) {
    // 沿路径生成桥柱
    double currentPos = 0;

    gp_Pnt prepoint;

    while (currentPos < totalLength) {
      // 获取路径上当前点的位置和切线方向
      gp_Pnt pointOnPath;
      gp_Vec tangent;

      // 遍历Wire中的边来找到当前位置对应的边
      TopExp_Explorer edgeExplorer(path, TopAbs_EDGE);
      double accumulatedLength = 0;
      bool found = false;

      for (; edgeExplorer.More() && !found; edgeExplorer.Next()) {
        const TopoDS_Edge &edge = TopoDS::Edge(edgeExplorer.Current());

        // 计算当前边的长度
        GProp_GProps edgeProps;
        BRepGProp::LinearProperties(edge, edgeProps);
        double edgeLength = edgeProps.Mass();

        if (currentPos <= accumulatedLength + edgeLength) {
          // 找到包含当前点的边
          BRepAdaptor_Curve curveAdaptor(edge);
          double param = curveAdaptor.FirstParameter() +
                         (currentPos - accumulatedLength) / edgeLength *
                             (curveAdaptor.LastParameter() -
                              curveAdaptor.FirstParameter());

          curveAdaptor.D1(param, pointOnPath, tangent);
          found = true;
        }
        accumulatedLength += edgeLength;
      }

      if (currentPos == 0) {
        prepoint = pointOnPath;
      } else {
        gp_Pnt startPoint = prepoint;
        gp_Pnt endPoint = pointOnPath;

        // 计算两点连线的中点
        gp_Pnt arcMidPoint((startPoint.X() + endPoint.X()) / 2,
                           (startPoint.Y() + endPoint.Y()) / 2,
                           (startPoint.Z() + endPoint.Z()) / 2 + params.height +
                               params.arcHeight);

        // 创建拱形起点和终点（高度增加桥架高度）
        gp_Pnt arcStartPoint(startPoint.X(), startPoint.Y(),
                             startPoint.Z() + params.height);
        gp_Pnt arcEndPoint(endPoint.X(), endPoint.Y(),
                           endPoint.Z() + params.height);

        // 计算路径方向向量
        gp_Vec pathVec(arcEndPoint.X() - arcStartPoint.X(),
                       arcEndPoint.Y() - arcStartPoint.Y(),
                       arcEndPoint.Z() - arcStartPoint.Z());

        // 计算垂直于路径方向的向量（假设Z轴向上）
        gp_Vec upVec(0, 0, 1);
        gp_Vec sideVec = pathVec.Crossed(upVec);
        sideVec.Normalize();
        pathVec.Normalize();

        // 计算两侧偏移量
        double offset = params.width / 2;

        // 生成加强筋
        double rebarRadius = params.width / 40;
        int rebarCount = 9;
        // 计算左侧圆弧点
        gp_Pnt leftArcStartPoint(arcStartPoint.X() - sideVec.X() * offset,
                                 arcStartPoint.Y() - sideVec.Y() * offset,
                                 arcStartPoint.Z());
        gp_Pnt leftArcMidPoint(arcMidPoint.X() - sideVec.X() * offset,
                               arcMidPoint.Y() - sideVec.Y() * offset,
                               arcMidPoint.Z());
        gp_Pnt leftArcEndPoint(arcEndPoint.X() - sideVec.X() * offset,
                               arcEndPoint.Y() - sideVec.Y() * offset,
                               arcEndPoint.Z());

        // 计算右侧圆弧点
        gp_Pnt rightArcStartPoint(arcStartPoint.X() + sideVec.X() * offset,
                                  arcStartPoint.Y() + sideVec.Y() * offset,
                                  arcStartPoint.Z());
        gp_Pnt rightArcMidPoint(arcMidPoint.X() + sideVec.X() * offset,
                                arcMidPoint.Y() + sideVec.Y() * offset,
                                arcMidPoint.Z());
        gp_Pnt rightArcEndPoint(arcEndPoint.X() + sideVec.X() * offset,
                                arcEndPoint.Y() + sideVec.Y() * offset,
                                arcEndPoint.Z());
        {

          // 创建弧形路径Wire
          BRepBuilderAPI_MakeWire pathWire;
          pathWire.Add(BRepBuilderAPI_MakeEdge(
                           GC_MakeArcOfCircle(leftArcStartPoint,
                                              leftArcMidPoint, leftArcEndPoint)
                               .Value())
                           .Edge());

          // 创建圆形截面（钢管半径5mm）
          double pipeRadius = params.width / 20;
          gp_Circ sectionCircle(gp_Ax2(leftArcStartPoint, pathVec), pipeRadius);
          TopoDS_Wire sectionWire =
              BRepBuilderAPI_MakeWire(
                  BRepBuilderAPI_MakeEdge(sectionCircle).Edge())
                  .Wire();

          // 沿路径扫掠生成钢管
          BRepOffsetAPI_MakePipeShell pipeMaker(pathWire.Wire());
          pipeMaker.Add(sectionWire);
          pipeMaker.SetMode(Standard_True); // 使用Frenet框架
          pipeMaker.Build();

          if (!pipeMaker.IsDone()) {
            throw Standard_ConstructionError("Failed to generate steel pipe");
          }

          if (!pipeMaker.MakeSolid()) {
            throw Standard_ConstructionError("Failed to make steel pipe solid");
          }

          TopoDS_Shape steelPipe = pipeMaker.Shape();

          builder.Add(result, steelPipe);
        }

        {

          // 创建弧形路径Wire
          BRepBuilderAPI_MakeWire pathWire;
          pathWire.Add(
              BRepBuilderAPI_MakeEdge(GC_MakeArcOfCircle(rightArcStartPoint,
                                                         rightArcMidPoint,
                                                         rightArcEndPoint)
                                          .Value())
                  .Edge());

          // 创建圆形截面（钢管半径5mm）
          double pipeRadius = params.width / 20;
          gp_Circ sectionCircle(gp_Ax2(rightArcStartPoint, pathVec),
                                pipeRadius);
          TopoDS_Wire sectionWire =
              BRepBuilderAPI_MakeWire(
                  BRepBuilderAPI_MakeEdge(sectionCircle).Edge())
                  .Wire();

          // 沿路径扫掠生成钢管
          BRepOffsetAPI_MakePipeShell pipeMaker(pathWire.Wire());
          pipeMaker.Add(sectionWire);
          pipeMaker.SetMode(Standard_True); // 使用Frenet框架
          pipeMaker.Build();

          if (!pipeMaker.IsDone()) {
            throw Standard_ConstructionError("Failed to generate steel pipe");
          }

          if (!pipeMaker.MakeSolid()) {
            throw Standard_ConstructionError("Failed to make steel pipe solid");
          }

          TopoDS_Shape steelPipe = pipeMaker.Shape();
          builder.Add(result, steelPipe);
        }

        {
          // 计算左右钢梁之间的加强筋
          for (int i = 1; i <= rebarCount; ++i) {
            double t = i * 1.0 / (rebarCount + 1);

            // 计算当前和下一个加强筋位置
            gp_Pnt leftPoint, rightPoint;
            gp_Pnt nextLeftPoint, nextRightPoint;

            if (leftArcStartPoint.Distance(leftArcEndPoint) >
                Precision::Confusion()) {
              // 创建圆弧
              GC_MakeArcOfCircle arcMaker(leftArcStartPoint, leftArcMidPoint,
                                          leftArcEndPoint);
              if (arcMaker.IsDone()) {
                Handle(Geom_TrimmedCurve) arc = arcMaker.Value();
                leftPoint = arc->Value(
                    arc->FirstParameter() +
                    t * (arc->LastParameter() - arc->FirstParameter()));
              } else {
                // 如果创建圆弧失败，回退到直线计算
                leftPoint = leftArcStartPoint.Translated(
                    gp_Vec(leftArcEndPoint.X() - leftArcStartPoint.X(),
                           leftArcEndPoint.Y() - leftArcStartPoint.Y(),
                           leftArcEndPoint.Z() - leftArcStartPoint.Z()) *
                    t);
              }
            } else {
              // 如果起点和终点重合，直接使用起点
              leftPoint = leftArcStartPoint;
            }

            if (rightArcStartPoint.Distance(rightArcEndPoint) >
                Precision::Confusion()) {
              // 创建圆弧
              GC_MakeArcOfCircle arcMaker(rightArcStartPoint, rightArcMidPoint,
                                          rightArcEndPoint);
              if (arcMaker.IsDone()) {
                Handle(Geom_TrimmedCurve) arc = arcMaker.Value();
                rightPoint = arc->Value(
                    arc->FirstParameter() +
                    t * (arc->LastParameter() - arc->FirstParameter()));
              } else {
                // 如果创建圆弧失败，回退到直线计算
                rightPoint = rightArcStartPoint.Translated(
                    gp_Vec(rightArcEndPoint.X() - rightArcStartPoint.X(),
                           rightArcEndPoint.Y() - rightArcStartPoint.Y(),
                           rightArcEndPoint.Z() - rightArcStartPoint.Z()) *
                    t);
              }
            } else {
              // 如果起点和终点重合，直接使用起点
              rightPoint = rightArcStartPoint;
            }

            // 创建水平加强筋
            TopoDS_Shape horizontalRebar =
                BRepPrimAPI_MakeCylinder(
                    gp_Ax2(leftPoint, gp_Vec(rightPoint.X() - leftPoint.X(),
                                             rightPoint.Y() - leftPoint.Y(),
                                             rightPoint.Z() - leftPoint.Z())),
                    rebarRadius, leftPoint.Distance(rightPoint))
                    .Shape();
            builder.Add(result, horizontalRebar);

            // 创建左侧垂直加强筋
            gp_Pnt leftBottomPoint =
                startPoint.Translated(gp_Vec(endPoint.X() - startPoint.X(),
                                             endPoint.Y() - startPoint.Y(),
                                             endPoint.Z() - startPoint.Z()) *
                                      t);
            // 应用侧向偏移
            leftBottomPoint.SetX(leftBottomPoint.X() - sideVec.X() * offset);
            leftBottomPoint.SetY(leftBottomPoint.Y() - sideVec.Y() * offset);
            leftBottomPoint.SetZ(leftBottomPoint.Z() + params.height);

            TopoDS_Shape leftVerticalRebar =
                BRepPrimAPI_MakeCylinder(
                    gp_Ax2(leftPoint,
                           gp_Vec(leftBottomPoint.X() - leftPoint.X(),
                                  leftBottomPoint.Y() - leftPoint.Y(),
                                  leftBottomPoint.Z() - leftPoint.Z())),
                    rebarRadius, leftPoint.Distance(leftBottomPoint))
                    .Shape();
            builder.Add(result, leftVerticalRebar);

            // 创建右侧垂直加强筋
            gp_Pnt rightBottomPoint =
                startPoint.Translated(gp_Vec(endPoint.X() - startPoint.X(),
                                             endPoint.Y() - startPoint.Y(),
                                             endPoint.Z() - startPoint.Z()) *
                                      t);
            // 应用侧向偏移
            rightBottomPoint.SetX(rightBottomPoint.X() + sideVec.X() * offset);
            rightBottomPoint.SetY(rightBottomPoint.Y() + sideVec.Y() * offset);
            rightBottomPoint.SetZ(rightBottomPoint.Z() + params.height);

            TopoDS_Shape rightVerticalRebar =
                BRepPrimAPI_MakeCylinder(
                    gp_Ax2(rightPoint,
                           gp_Vec(rightBottomPoint.X() - rightPoint.X(),
                                  rightBottomPoint.Y() - rightPoint.Y(),
                                  rightBottomPoint.Z() - rightPoint.Z())),
                    rebarRadius, rightPoint.Distance(rightBottomPoint))
                    .Shape();
            builder.Add(result, rightVerticalRebar);

            // 如果不是最后一个加强筋，添加斜拉筋
            if (i < rebarCount) {
              // 计算下一个加强筋位置
              double nextT = (i + 1) * 1.0 / (rebarCount + 1);
              gp_Pnt nextLeftPoint, nextRightPoint;

              // 计算下一个左侧点
              if (leftArcStartPoint.Distance(leftArcEndPoint) >
                  Precision::Confusion()) {
                GC_MakeArcOfCircle leftArc(leftArcStartPoint, leftArcMidPoint,
                                           leftArcEndPoint);
                if (leftArc.IsDone()) {
                  nextLeftPoint = leftArc.Value()->Value(
                      leftArc.Value()->FirstParameter() +
                      nextT * (leftArc.Value()->LastParameter() -
                               leftArc.Value()->FirstParameter()));
                } else {
                  nextLeftPoint = leftArcStartPoint.Translated(
                      gp_Vec(leftArcEndPoint.X() - leftArcStartPoint.X(),
                             leftArcEndPoint.Y() - leftArcStartPoint.Y(),
                             leftArcEndPoint.Z() - leftArcStartPoint.Z()) *
                      nextT);
                }
              } else {
                nextLeftPoint = leftArcStartPoint;
              }

              // 计算下一个右侧点
              if (rightArcStartPoint.Distance(rightArcEndPoint) >
                  Precision::Confusion()) {
                GC_MakeArcOfCircle rightArc(rightArcStartPoint,
                                            rightArcMidPoint, rightArcEndPoint);
                if (rightArc.IsDone()) {
                  nextRightPoint = rightArc.Value()->Value(
                      rightArc.Value()->FirstParameter() +
                      nextT * (rightArc.Value()->LastParameter() -
                               rightArc.Value()->FirstParameter()));
                } else {
                  nextRightPoint = rightArcStartPoint.Translated(
                      gp_Vec(rightArcEndPoint.X() - rightArcStartPoint.X(),
                             rightArcEndPoint.Y() - rightArcStartPoint.Y(),
                             rightArcEndPoint.Z() - rightArcStartPoint.Z()) *
                      nextT);
                }
              } else {
                nextRightPoint = rightArcStartPoint;
              }

              gp_Pnt nextLeftBottomPoint =
                  startPoint.Translated(gp_Vec(endPoint.X() - startPoint.X(),
                                               endPoint.Y() - startPoint.Y(),
                                               endPoint.Z() - startPoint.Z()) *
                                        nextT);
              nextLeftBottomPoint.SetX(nextLeftBottomPoint.X() -
                                       sideVec.X() * offset);
              nextLeftBottomPoint.SetY(nextLeftBottomPoint.Y() -
                                       sideVec.Y() * offset);
              nextLeftBottomPoint.SetZ(nextLeftBottomPoint.Z() + params.height);

              gp_Pnt nextRightBottomPoint =
                  startPoint.Translated(gp_Vec(endPoint.X() - startPoint.X(),
                                               endPoint.Y() - startPoint.Y(),
                                               endPoint.Z() - startPoint.Z()) *
                                        nextT);
              nextRightBottomPoint.SetX(nextRightBottomPoint.X() +
                                        sideVec.X() * offset);
              nextRightBottomPoint.SetY(nextRightBottomPoint.Y() +
                                        sideVec.Y() * offset);
              nextRightBottomPoint.SetZ(nextRightBottomPoint.Z() +
                                        params.height);

              // 创建左上到右下的斜拉筋
              TopoDS_Shape diagonalRebar1 =
                  BRepPrimAPI_MakeCylinder(
                      gp_Ax2(leftPoint,
                             gp_Vec(nextRightPoint.X() - leftPoint.X(),
                                    nextRightPoint.Y() - leftPoint.Y(),
                                    nextRightPoint.Z() - leftPoint.Z())),
                      rebarRadius, leftPoint.Distance(nextRightPoint))
                      .Shape();
              builder.Add(result, diagonalRebar1);

              // 创建右上到左下的斜拉筋
              TopoDS_Shape diagonalRebar2 =
                  BRepPrimAPI_MakeCylinder(
                      gp_Ax2(rightPoint,
                             gp_Vec(nextLeftPoint.X() - rightPoint.X(),
                                    nextLeftPoint.Y() - rightPoint.Y(),
                                    nextLeftPoint.Z() - rightPoint.Z())),
                      rebarRadius, rightPoint.Distance(nextLeftPoint))
                      .Shape();
              builder.Add(result, diagonalRebar2);

              // 添加左侧斜拉筋 (从当前左点到下一个左底点)
              if (i < 5) {
                TopoDS_Shape leftDiagonalRebar =
                    BRepPrimAPI_MakeCylinder(
                        gp_Ax2(leftPoint,
                               gp_Vec(nextLeftBottomPoint.X() - leftPoint.X(),
                                      nextLeftBottomPoint.Y() - leftPoint.Y(),
                                      nextLeftBottomPoint.Z() - leftPoint.Z())),
                        rebarRadius, leftPoint.Distance(nextLeftBottomPoint))
                        .Shape();
                builder.Add(result, leftDiagonalRebar);
              } else {
                // 后半部分：从当前底端连向下一个顶端
                TopoDS_Shape leftDiagonalRebar =
                    BRepPrimAPI_MakeCylinder(
                        gp_Ax2(nextLeftPoint,
                               gp_Vec(leftBottomPoint.X() - nextLeftPoint.X(),
                                      leftBottomPoint.Y() - nextLeftPoint.Y(),
                                      leftBottomPoint.Z() - nextLeftPoint.Z())),
                        rebarRadius, nextLeftPoint.Distance(leftBottomPoint))
                        .Shape();
                builder.Add(result, leftDiagonalRebar);
              }

              // 添加右侧斜拉筋 (从当前右点到下一个右底点)
              if (i < 5) {
                TopoDS_Shape rightDiagonalRebar =
                    BRepPrimAPI_MakeCylinder(
                        gp_Ax2(
                            rightPoint,
                            gp_Vec(nextRightBottomPoint.X() - rightPoint.X(),
                                   nextRightBottomPoint.Y() - rightPoint.Y(),
                                   nextRightBottomPoint.Z() - rightPoint.Z())),
                        rebarRadius, rightPoint.Distance(nextRightBottomPoint))
                        .Shape();
                builder.Add(result, rightDiagonalRebar);
              } else {
                // 后半部分：从当前底端连向下一个顶端
                TopoDS_Shape rightDiagonalRebar =
                    BRepPrimAPI_MakeCylinder(
                        gp_Ax2(
                            nextRightPoint,
                            gp_Vec(rightBottomPoint.X() - nextRightPoint.X(),
                                   rightBottomPoint.Y() - nextRightPoint.Y(),
                                   rightBottomPoint.Z() - nextRightPoint.Z())),
                        rebarRadius, nextRightPoint.Distance(rightBottomPoint))
                        .Shape();
                builder.Add(result, rightDiagonalRebar);
              }
            }
          }
        }

        prepoint = pointOnPath;
      }

      currentPos += params.span;
    }
  }

  return result;
}

TopoDS_Shape create_cable_tray(const cable_tray_params &params,
                               const gp_Pnt &position, const gp_Dir &direction,
                               const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的电缆桥架
  TopoDS_Shape tray = create_cable_tray(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(tray, transformation);
  return transform.Shape();
}

TopoDS_Shape create_cable_L_beam(const cable_L_beam_params &params) {
  // 参数验证
  if (params.length <= 0 || params.width <= 0 || params.height <= 0) {
    throw Standard_ConstructionError("L, W and H must be positive");
  }

  TopoDS_Shape beam =
      BRepPrimAPI_MakeBox(gp_Pnt(-params.length / 2, -params.width / 2, 0),
                          params.length, params.width, params.height)
          .Shape();

  return beam;
}

TopoDS_Shape create_cable_L_beam(const cable_L_beam_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &xDirection,
                                 const gp_Dir &zDirection) {
  // 正交性校验
  if (Abs(xDirection.Dot(zDirection)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "X and Z directions must be perpendicular");
  }

  // 创建标准方向的L梁
  TopoDS_Shape LBeam = create_cable_L_beam(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, zDirection, xDirection);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(LBeam, transformation);
  return transform.Shape();
}

TopoDS_Shape create_manhole(const manhole_params &params) {
  // 参数验证
  if (params.length <= 0 || params.height <= 0 || params.wallThickness <= 0) {
    throw Standard_ConstructionError(
        "Length, height and wall thickness must be positive");
  }
  if (params.style == manhole_style::RECTANGULAR && params.width <= 0) {
    throw Standard_ConstructionError(
        "Width must be positive for rectangular manhole");
  }

  TopoDS_Shape manhole;

  switch (params.style) {
  case manhole_style::CIRCULAR: {
    // 创建圆形人孔
    double outerRadius = params.length / 2;
    double innerRadius = outerRadius - params.wallThickness;

    // 创建外壁圆柱
    TopoDS_Shape outerCylinder =
        BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp::DZ()), outerRadius,
                                 params.height)
            .Shape();

    // 创建内壁圆柱(空心部分)
    if (innerRadius > 0) {
      TopoDS_Shape innerCylinder =
          BRepPrimAPI_MakeCylinder(
              gp_Ax2(gp_Pnt(0, 0, -params.height), gp::DZ()), innerRadius,
              params.height * 2)
              .Shape();
      manhole = BRepAlgoAPI_Cut(outerCylinder, innerCylinder).Shape();
    } else {
      manhole = outerCylinder;
    }
    break;
  }

  case manhole_style::RECTANGULAR: {
    // 创建方形人孔
    double outerLength = params.length;
    double outerWidth = params.width;
    double innerLength = params.length - 2 * params.wallThickness;
    double innerWidth = params.width - 2 * params.wallThickness;

    // 创建外壁长方体
    TopoDS_Shape outerBox =
        BRepPrimAPI_MakeBox(gp_Pnt(-outerLength / 2, -outerWidth / 2, 0),
                            outerLength, outerWidth, params.height)
            .Shape();

    // 创建内壁长方体(空心部分)
    if (innerLength > 0 && innerWidth > 0) {
      TopoDS_Shape innerBox =
          BRepPrimAPI_MakeBox(gp_Pnt(-innerLength / 2, -innerWidth / 2, -1),
                              innerLength, innerWidth, params.height + 2)
              .Shape();
      manhole = BRepAlgoAPI_Cut(outerBox, innerBox).Shape();
    } else {
      manhole = outerBox;
    }
    break;
  }
  }

  return manhole;
}

TopoDS_Shape create_manhole(const manhole_params &params,
                            const gp_Pnt &position, const gp_Dir &direction,
                            const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的人孔
  TopoDS_Shape manhole = create_manhole(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(manhole, transformation);
  return transform.Shape();
}

TopoDS_Shape create_manhole_cover(const manhole_cover_params &params) {
  // 参数验证
  if (params.length <= 0.0) {
    throw Standard_ConstructionError("Length/diameter must be positive");
  }
  if (params.thickness <= 0.0) {
    throw Standard_ConstructionError("Thickness must be positive");
  }
  if (params.style == manhole_cover_style::RECTANGULAR && params.width <= 0.0) {
    throw Standard_ConstructionError(
        "Width must be positive for rectangle cover");
  }

  TopoDS_Shape cover;

  if (params.style == manhole_cover_style::CIRCULAR) {
    // 创建圆形井盖
    gp_Ax2 axis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
    BRepPrimAPI_MakeCylinder cylinderMaker(axis, params.length / 2,
                                           params.thickness);
    cover = cylinderMaker.Shape();
  } else {
    // 创建矩形井盖
    gp_Pnt corner(-params.length / 2, -params.width / 2, 0);
    BRepPrimAPI_MakeBox boxMaker(corner, params.length, params.width,
                                 params.thickness);
    cover = boxMaker.Shape();

    // 添加倒角处理
    BRepFilletAPI_MakeChamfer chamferMaker(cover);
    TopExp_Explorer edgeExplorer(cover, TopAbs_EDGE);
    for (; edgeExplorer.More(); edgeExplorer.Next()) {
      const TopoDS_Edge &edge = TopoDS::Edge(edgeExplorer.Current());
      chamferMaker.Add(params.thickness / 10, edge); // 倒角大小为厚度的1/10
    }
    if (chamferMaker.IsDone()) {
      cover = chamferMaker.Shape();
    }
  }

  return cover;
}

TopoDS_Shape create_manhole_cover(const manhole_cover_params &params,
                                  const gp_Pnt &position,
                                  const gp_Dir &direction, const gp_Dir &xDir) {
  // 首先创建原点处的井盖
  TopoDS_Shape cover = create_manhole_cover(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  gp_Ax3 targetAx3(position, direction, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(cover, transformation);
  return transform.Shape();
}

TopoDS_Shape create_ladder(const ladder_params &params) {
  // 参数验证
  if (params.length <= 0 || params.width <= 0 || params.thickness <= 0) {
    throw Standard_ConstructionError(
        "Length, width and thickness must be positive");
  }

  // 创建爬梯主体
  TopoDS_Shape ladder =
      BRepPrimAPI_MakeBox(gp_Pnt(-params.length / 2, -params.width, 0),
                          params.length, params.width, params.thickness)
          .Shape();

  return ladder;
}

TopoDS_Shape create_ladder(const ladder_params &params, const gp_Pnt &position,
                           const gp_Dir &direction, const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的爬梯
  TopoDS_Shape ladder = create_ladder(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(ladder, transformation);
  return transform.Shape();
}

TopoDS_Shape create_sump(const sump_params &params) {
  // 参数验证
  if (params.length <= 0 || params.width <= 0 || params.depth <= 0) {
    throw Standard_ConstructionError(
        "Length, width and depth must be positive");
  }
  if (params.bottomThickness < 0) {
    throw Standard_ConstructionError("Floor thickness must be non-negative");
  }

  // 创建集水坑主体（长方体）
  gp_Pnt origin(-params.length / 2 - params.bottomThickness,
                -params.width / 2 - params.bottomThickness,
                -params.depth - params.bottomThickness);
  BRepPrimAPI_MakeBox pitMaker(origin,
                               params.length + 2 * params.bottomThickness,
                               params.width + 2 * params.bottomThickness,
                               params.depth + params.bottomThickness);
  TopoDS_Shape pit = pitMaker.Shape();

  // 创建内部空腔（如果底板厚度大于0）
  if (params.bottomThickness > 0) {
    gp_Pnt innerOrigin(-params.length / 2, -params.width / 2, -params.depth);
    BRepPrimAPI_MakeBox cavityMaker(innerOrigin, params.length, params.width,
                                    params.depth * 2);
    pit = BRepAlgoAPI_Cut(pit, cavityMaker.Shape()).Shape();
  }

  return pit;
}

TopoDS_Shape create_sump(const sump_params &params, const gp_Pnt &position,
                         const gp_Dir &normal, const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 创建标准方向的集水坑
  TopoDS_Shape pit = create_sump(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(pit, transformation);
  return transform.Shape();
}

TopoDS_Shape create_footpath(const footpath_params &params) {
  // 参数验证
  if (params.height <= 0 || params.width <= 0) {
    throw Standard_ConstructionError("Height and width must be positive");
  }

  BRepBuilderAPI_MakeWire baseMaker;

  // 创建路径线框
  BRepBuilderAPI_MakeWire pathWire;

  // 处理点序列
  for (size_t i = 0; i < params.points.size() - 1; i++) {
    const gp_Pnt &current = params.points[i].position;
    const gp_Pnt &next = params.points[i + 1].position;

    if (params.points[i].type == 0 &&
        params.points[i + 1].type == 0) { // 普通节点
      // 创建直线段
      pathWire.Add(BRepBuilderAPI_MakeEdge(current, next).Edge());
    } else if (params.points[i].type == 1) { // 弧形节点
      // 确保有前一个点和后一个点
      if (i == 0 || i == params.points.size() - 1) {
        throw Standard_ConstructionError("弧形节点需要前后都有节点");
      }

      const gp_Pnt &prev = params.points[i - 1].position;

      // 创建三点圆弧
      pathWire.Add(BRepBuilderAPI_MakeEdge(
                       GC_MakeArcOfCircle(prev, current, next).Value())
                       .Edge());
    }
  }

  if (!pathWire.IsDone()) {
    throw Standard_ConstructionError("路径线框创建失败");
  }

  TopoDS_Wire path = pathWire.Wire();

  // 获取路径起始点的切线方向
  BRepAdaptor_CompCurve curveAdaptor(path);
  gp_Pnt startPoint;
  gp_Vec startTangent;
  curveAdaptor.D1(curveAdaptor.FirstParameter(), startPoint, startTangent);

  // 在创建截面圆之前添加方向修正
  gp_Dir tanDir = startTangent.Normalized();
  gp_Dir refDir = gp::DZ(); // 默认参考方向为全局Y轴

  // 如果tanDir平行于全局X轴，调整参考方向为全局Z轴
  if (IsParallel(tanDir, gp::DX())) {
    refDir = gp::DZ();
  }
  gp_Ax2 sectionAxes(startPoint, tanDir, refDir);

  // 创建变换对象
  gp_Trsf trsf;
  trsf.SetTransformation(sectionAxes, gp_Ax2(gp::Origin(), gp::DZ()));

  // YZ平面上的点坐标 (X=0)
  gp_Pnt p1(0, -params.width / 2, -params.height);
  gp_Pnt p2(0, params.width / 2, -params.height);
  gp_Pnt p3(0, params.width / 2, 0);
  gp_Pnt p4(0, -params.width / 2, 0);

  gp_Pnt projectedp1 = sectionAxes.Location().Translated(
      gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));
  gp_Pnt projectedp2 = sectionAxes.Location().Translated(
      gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));
  gp_Pnt projectedp3 = sectionAxes.Location().Translated(
      gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));
  gp_Pnt projectedp4 = sectionAxes.Location().Translated(
      gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

  baseMaker.Add(BRepBuilderAPI_MakeEdge(projectedp1, projectedp2).Edge());
  baseMaker.Add(BRepBuilderAPI_MakeEdge(projectedp2, projectedp3).Edge());
  baseMaker.Add(BRepBuilderAPI_MakeEdge(projectedp3, projectedp4).Edge());
  baseMaker.Add(BRepBuilderAPI_MakeEdge(projectedp4, projectedp1).Edge());

  return create_channel_shape(baseMaker.Wire(), path);
}

TopoDS_Shape create_footpath(const footpath_params &params,
                             const gp_Pnt &position, const gp_Dir &direction,
                             const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的步道
  TopoDS_Shape footpath = create_footpath(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(footpath, transformation);
  return transform.Shape();
}

TopoDS_Shape create_shaft_chamber(const shaft_chamber_params &params) {
  // 参数验证
  if (params.supportDiameter <= 0 || params.workingHeight <= 0) {
    throw Standard_ConstructionError("Diameter and height must be positive");
  }
  if (params.supportWallThickness < 0 || params.outerWallThickness < 0 ||
      params.innerWallThickness < 0 || params.topThickness < 0) {
    throw Standard_ConstructionError("Thickness values must be non-negative");
  }

  // 创建支护结构（外圆柱）
  gp_Ax2 supportAxis(gp_Pnt(0, 0, params.workingHeight), gp::DZ());
  TopoDS_Shape support;
  if (params.supportWallThickness > 0 && params.supportHeight > 0) {
    double supportRadius =
        params.supportDiameter / 2 + params.supportWallThickness;
    support =
        BRepPrimAPI_MakeCylinder(supportAxis, supportRadius,
                                 params.supportHeight + params.topThickness)
            .Shape();

    if (params.supportWallThickness > 0) {
      gp_Ax2 supportInnerAxis(
          gp_Pnt(0, 0, params.workingHeight + params.topThickness), gp::DZ());

      // 创建内壁空腔
      TopoDS_Shape innerCavity =
          BRepPrimAPI_MakeCylinder(supportInnerAxis, params.supportDiameter / 2,
                                   params.supportHeight)
              .Shape();
      support = BRepAlgoAPI_Cut(support, innerCavity).Shape();
    }
  }

  // 创建工作仓外壁
  TopoDS_Shape outerWall;
  if (params.outerWallThickness > 0) {
    gp_Ax2 outerAxis(gp_Pnt(0, 0, 0), gp::DZ());
    double outerRadius = params.innerDiameter / 2 + params.innerWallThickness +
                         params.outerWallThickness;
    outerWall =
        BRepPrimAPI_MakeCylinder(outerAxis, outerRadius, params.workingHeight)
            .Shape();

    if (params.innerWallThickness > 0) {
      // 创建内壁空腔
      TopoDS_Shape innerCavity =
          BRepPrimAPI_MakeCylinder(outerAxis, params.innerDiameter / 2,
                                   params.workingHeight)
              .Shape();
      outerWall = BRepAlgoAPI_Cut(outerWall, innerCavity).Shape();
    }

    if (!support.IsNull()) {
      outerWall = BRepAlgoAPI_Fuse(outerWall, support).Shape();
    }
  }

  return outerWall;
}

TopoDS_Shape create_shaft_chamber(const shaft_chamber_params &params,
                                  const gp_Pnt &position,
                                  const gp_Dir &direction, const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的竖井仓
  TopoDS_Shape well = create_shaft_chamber(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(well, transformation);
  return transform.Shape();
}

TopoDS_Shape create_tunnel_compartment_partition(
    const tunnel_compartment_partition_params &params) {
  try {
    // 创建矩形隔板
    gp_Pnt position(-params.width / 2, -params.width / 2, -params.thickness);
    BRepPrimAPI_MakeBox boxMaker(position, params.width, params.width,
                                 params.thickness);
    return boxMaker.Shape();
  } catch (const Standard_Failure &e) {
    throw Standard_ConstructionError(
        "Failed to create tunnel compartment partition");
  }
}

TopoDS_Shape create_tunnel_compartment_partition(
    const tunnel_compartment_partition_params &params, const gp_Pnt &position,
    const gp_Dir &normal, const gp_Dir &xDir) {
  // 先创建基本形状
  TopoDS_Shape shape = create_tunnel_compartment_partition(params);

  // 创建变换矩阵
  gp_Trsf transform;
  transform.SetTransformation(gp_Ax3(position, normal, xDir));

  // 应用变换
  BRepBuilderAPI_Transform transformer(shape, transform);
  return transformer.Shape();
}

TopoDS_Shape
create_tunnel_partition_board(const tunnel_partition_board_params &params) {
  // 参数验证
  if (params.thickness <= 0) {
    throw Standard_ConstructionError("Partition thickness must be positive");
  }
  if (params.style != 1 && params.style != 2) {
    throw Standard_ConstructionError("Style must be 1 (round) or 2 (square)");
  }
  if (params.holeCount != params.holePositions.size() ||
      params.holeCount != params.holeStyles.size() ||
      params.holeCount != params.holeDiameters.size() ||
      params.holeCount != params.holeWidths.size()) {
    throw Standard_ConstructionError("Hole parameters count mismatch");
  }

  // 创建隔板主体
  TopoDS_Shape partition;
  if (params.style == 1) { // 圆形隔板
    partition = BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DZ()),
                                         params.length / 2, params.thickness)
                    .Shape();
  } else { // 方形隔板
    partition =
        BRepPrimAPI_MakeBox(gp_Pnt(-params.length / 2, -params.width / 2, 0),
                            params.length, params.width, params.thickness)
            .Shape();
  }

  // 创建开孔
  for (int i = 0; i < params.holeCount; ++i) {
    TopoDS_Shape hole;
    gp_Pnt center(params.holePositions[i].X(), params.holePositions[i].Y(), -1);

    if (params.holeStyles[i] == 1) { // 圆形孔
      hole = BRepPrimAPI_MakeCylinder(gp_Ax2(center, gp::DZ()),
                                      params.holeDiameters[i] / 2,
                                      params.thickness + 2)
                 .Shape(); // 加2mm确保完全穿透
    } else {               // 方形孔
      hole =
          BRepPrimAPI_MakeBox(gp_Pnt(center.X() - params.holeDiameters[i] / 2,
                                     center.Y() - params.holeWidths[i] / 2,
                                     -1), // 确保完全穿透
                              params.holeDiameters[i], params.holeWidths[i],
                              params.thickness + 2)
              .Shape();
    }

    // 从隔板中减去孔
    partition = BRepAlgoAPI_Cut(partition, hole).Shape();
  }

  return partition;
}

TopoDS_Shape
create_tunnel_partition_board(const tunnel_partition_board_params &params,
                              const gp_Pnt &position, const gp_Dir &normal,
                              const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 创建标准方向的隔板
  TopoDS_Shape partition = create_tunnel_partition_board(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(partition, transformation);
  return transform.Shape();
}

TopoDS_Shape
create_ventilation_pavilion(const ventilation_pavilion_params &params) {
  // 参数验证
  if (params.height <= 0 || params.baseHeight <= 0) {
    throw Standard_ConstructionError("Height values must be positive");
  }

  // 创建底座

  // 创建底座（改为棱台形状）
  gp_Pnt baseBottom1(-params.bottomLength / 2, -params.bottomWidth / 2, 0);
  gp_Pnt baseBottom2(params.bottomLength / 2, -params.bottomWidth / 2, 0);
  gp_Pnt baseBottom3(params.bottomLength / 2, params.bottomWidth / 2, 0);
  gp_Pnt baseBottom4(-params.bottomLength / 2, params.bottomWidth / 2, 0);

  // 棱台上部与主体相同尺寸
  gp_Pnt baseTop1(-params.middleLength / 2, -params.middleWidth / 2,
                  params.baseHeight);
  gp_Pnt baseTop2(params.middleLength / 2, -params.middleWidth / 2,
                  params.baseHeight);
  gp_Pnt baseTop3(params.middleLength / 2, params.middleWidth / 2,
                  params.baseHeight);
  gp_Pnt baseTop4(-params.middleLength / 2, params.middleWidth / 2,
                  params.baseHeight);

  // 创建上下底面
  BRepBuilderAPI_MakeWire bottomWire;
  bottomWire.Add(BRepBuilderAPI_MakeEdge(baseBottom1, baseBottom2));
  bottomWire.Add(BRepBuilderAPI_MakeEdge(baseBottom2, baseBottom3));
  bottomWire.Add(BRepBuilderAPI_MakeEdge(baseBottom3, baseBottom4));
  bottomWire.Add(BRepBuilderAPI_MakeEdge(baseBottom4, baseBottom1));

  BRepBuilderAPI_MakeWire topWire;
  topWire.Add(BRepBuilderAPI_MakeEdge(baseTop1, baseTop2));
  topWire.Add(BRepBuilderAPI_MakeEdge(baseTop2, baseTop3));
  topWire.Add(BRepBuilderAPI_MakeEdge(baseTop3, baseTop4));
  topWire.Add(BRepBuilderAPI_MakeEdge(baseTop4, baseTop1));

  // 创建棱台的侧面（通过放样）
  TopoDS_Shape base;
  BRepOffsetAPI_ThruSections loftMaker(Standard_True); // 生成实体
  loftMaker.AddWire(bottomWire.Wire());
  loftMaker.AddWire(topWire.Wire());
  loftMaker.Build();
  if (!loftMaker.IsDone())
    throw Standard_ConstructionError("棱台放样失败");
  base = loftMaker.Shape();

  // 创建主体
  gp_Pnt bodyOrigin(-params.middleLength / 2, -params.middleWidth / 2,
                    params.baseHeight);
  TopoDS_Shape body = BRepPrimAPI_MakeBox(bodyOrigin, params.middleLength,
                                          params.middleWidth, params.height)
                          .Shape();

  gp_Pnt roofOrigin(-params.topLength / 2, -params.topWidth / 2,
                    params.height + params.baseHeight);
  TopoDS_Shape roofBody = BRepPrimAPI_MakeBox(roofOrigin, params.topLength,
                                              params.topWidth, params.topHeight)
                              .Shape();

  // 创建屋顶
  gp_Pnt roofBaseCenter(0, 0,
                        params.height + params.baseHeight + params.topHeight);
  gp_Pnt roofTop(0, 0,
                 params.height + params.baseHeight + params.topHeight +
                     params.topHeight);

  // 创建金字塔底面四个角点
  gp_Pnt base1(-params.topLength / 2, -params.topWidth / 2, roofBaseCenter.Z());
  gp_Pnt base2(params.topLength / 2, -params.topWidth / 2, roofBaseCenter.Z());
  gp_Pnt base3(params.topLength / 2, params.topWidth / 2, roofBaseCenter.Z());
  gp_Pnt base4(-params.topLength / 2, params.topWidth / 2, roofBaseCenter.Z());

  // 创建金字塔的四个三角形面
  BRepBuilderAPI_MakeEdge edge1(base1, base2);
  BRepBuilderAPI_MakeEdge edge2(base2, roofTop);
  BRepBuilderAPI_MakeEdge edge3(roofTop, base1);
  BRepBuilderAPI_MakeWire wire1;
  wire1.Add(edge1);
  wire1.Add(edge2);
  wire1.Add(edge3);

  TopoDS_Wire faceWire1 = wire1.Wire();

  if (!faceWire1.Closed()) {
    throw Standard_ConstructionError("Face wire is not closed");
  }

  BRepBuilderAPI_MakeFace face1(faceWire1);

  // 其他三个面也采用同样的方式创建
  BRepBuilderAPI_MakeEdge edge4(base2, base3);
  BRepBuilderAPI_MakeEdge edge5(base3, roofTop);
  BRepBuilderAPI_MakeEdge edge6(roofTop, base2);
  BRepBuilderAPI_MakeWire wire2;
  wire2.Add(edge4);
  wire2.Add(edge5);
  wire2.Add(edge6);

  TopoDS_Wire faceWire2 = wire2.Wire();

  if (!faceWire2.Closed()) {
    throw Standard_ConstructionError("Face wire is not closed");
  }

  BRepBuilderAPI_MakeFace face2(faceWire2);

  BRepBuilderAPI_MakeEdge edge7(base3, base4);
  BRepBuilderAPI_MakeEdge edge8(base4, roofTop);
  BRepBuilderAPI_MakeEdge edge9(roofTop, base3);
  BRepBuilderAPI_MakeWire wire3;
  wire3.Add(edge7);
  wire3.Add(edge8);
  wire3.Add(edge9);

  TopoDS_Wire faceWire3 = wire3.Wire();

  if (!faceWire3.Closed()) {
    throw Standard_ConstructionError("Face wire is not closed");
  }

  BRepBuilderAPI_MakeFace face3(faceWire3);

  BRepBuilderAPI_MakeEdge edge10(base4, base1);
  BRepBuilderAPI_MakeEdge edge11(base1, roofTop);
  BRepBuilderAPI_MakeEdge edge12(roofTop, base4);
  BRepBuilderAPI_MakeWire wire4;
  wire4.Add(edge10);
  wire4.Add(edge11);
  wire4.Add(edge12);

  TopoDS_Wire faceWire4 = wire4.Wire();

  if (!faceWire4.Closed()) {
    throw Standard_ConstructionError("Face wire is not closed");
  }

  BRepBuilderAPI_MakeFace face4(faceWire4);

  // 创建金字塔底面
  BRepBuilderAPI_MakeWire baseWire;
  baseWire.Add(BRepBuilderAPI_MakeEdge(base1, base2));
  baseWire.Add(BRepBuilderAPI_MakeEdge(base2, base3));
  baseWire.Add(BRepBuilderAPI_MakeEdge(base3, base4));
  baseWire.Add(BRepBuilderAPI_MakeEdge(base4, base1));

  TopoDS_Wire faceWire5 = baseWire.Wire();

  if (!faceWire5.Closed()) {
    throw Standard_ConstructionError("Face wire is not closed");
  }

  BRepBuilderAPI_MakeFace baseFace(faceWire5);

  // 组合所有面形成封闭的金字塔形状
  BRepBuilderAPI_Sewing sewer;
  sewer.Add(face1.Face());
  sewer.Add(face2.Face());
  sewer.Add(face3.Face());
  sewer.Add(face4.Face());
  sewer.Add(baseFace.Face());
  sewer.Perform();

  TopoDS_Shape roof = sewer.SewedShape();

  // 添加通风格栅（长条洞）
  double holeWidth = params.middleWidth * 0.8;     // 洞长为面宽的0.8倍
  double holeLength = params.middleLength * 0.8;   // 洞长为面宽的0.8倍
  double holeHeight = (params.height / 8.0) * 0.3; // 洞高为body高的0.05倍

  // 在（前、后）面上均匀挖8个洞
  for (int j = 0; j < 8; ++j) {
    // 计算洞的位置（垂直方向均匀分布）
    double holePosZ = params.baseHeight + (j + 0.5) * (params.height / 8.0);

    // 根据面的方向确定洞的长宽

    TopoDS_Shape hole =
        BRepPrimAPI_MakeBox(
            gp_Pnt(-holeLength / 2, -params.middleLength, holePosZ), holeLength,
            params.middleLength * 2, holeHeight)
            .Shape();

    body = BRepAlgoAPI_Cut(body, hole).Shape();
  }

  // 在（左，右）面上均匀挖8个洞
  for (int j = 0; j < 8; ++j) {
    // 计算洞的位置（垂直方向均匀分布）
    double holePosZ = params.baseHeight + (j + 0.5) * (params.height / 8.0);

    // 创建左右方向的通风格栅
    TopoDS_Shape hole =
        BRepPrimAPI_MakeBox(
            gp_Pnt(-params.middleWidth, -holeWidth / 2, holePosZ),
            params.middleWidth * 2, holeWidth, holeHeight)
            .Shape();

    body = BRepAlgoAPI_Cut(body, hole).Shape();
  }

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);
  builder.Add(compound, roof);
  builder.Add(compound, roofBody);
  builder.Add(compound, body);
  builder.Add(compound, base);

  return compound;
}

TopoDS_Shape
create_ventilation_pavilion(const ventilation_pavilion_params &params,
                            const gp_Pnt &position, const gp_Dir &direction,
                            const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的风亭
  TopoDS_Shape pavilion = create_ventilation_pavilion(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(pavilion, transformation);
  return transform.Shape();
}

TopoDS_Shape create_straight_ventilation_duct(
    const straight_ventilation_duct_params &params) {
  // 参数验证
  if (params.diameter <= 0 || params.height <= 0) {
    throw Standard_ConstructionError("Diameter and height must be positive");
  }
  if (params.wallThickness < 0 || params.wallThickness >= params.diameter / 2) {
    throw Standard_ConstructionError("Wall thickness must be in [0, D/2)");
  }

  // 创建外圆柱
  gp_Ax2 axis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  BRepPrimAPI_MakeCylinder outerCylinder(axis, params.diameter / 2,
                                         params.height);
  TopoDS_Shape duct = outerCylinder.Shape();

  // 如果有壁厚，创建内圆柱并进行布尔减操作
  if (params.wallThickness > 0) {
    double innerRadius = params.diameter / 2 - params.wallThickness;
    BRepPrimAPI_MakeCylinder innerCylinder(axis, innerRadius, params.height);
    duct = BRepAlgoAPI_Cut(duct, innerCylinder.Shape()).Shape();
  }

  return duct;
}

TopoDS_Shape
create_straight_ventilation_duct(const straight_ventilation_duct_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction, const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的直通风道
  TopoDS_Shape duct = create_straight_ventilation_duct(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(duct, transformation);
  return transform.Shape();
}

TopoDS_Shape
create_oblique_ventilation_duct(const oblique_ventilation_duct_params &params) {
  // 参数验证
  if (params.hoodRoomLength <= 0 || params.hoodRoomWidth <= 0 ||
      params.hoodRoomHeight <= 0) {
    throw Standard_ConstructionError("Hood room dimensions must be positive");
  }
  if (params.ductDiameter <= 0 || params.ductLength <= 0) {
    throw Standard_ConstructionError("Duct dimensions must be positive");
  }
  if (params.baseRoomLength <= 0 || params.baseRoomWidth <= 0 ||
      params.baseRoomHeight <= 0) {
    throw Standard_ConstructionError("Base room dimensions must be positive");
  }

  // 创建风帽室（长方体）
  gp_Pnt hoodOrigin(-params.hoodRoomWidth / 2, -params.hoodRoomLength / 2, 0);
  TopoDS_Shape hoodRoom =
      BRepPrimAPI_MakeBox(hoodOrigin, params.hoodRoomWidth,
                          params.hoodRoomLength, params.hoodRoomHeight)
          .Shape();

  // 创建风帽室内腔（如果壁厚大于0）
  if (params.hoodWallThickness > 0) {
    gp_Pnt innerOrigin(-params.hoodRoomWidth / 2 + params.hoodWallThickness,
                       -params.hoodRoomLength / 2 + params.hoodWallThickness,
                       0);
    TopoDS_Shape innerHood =
        BRepPrimAPI_MakeBox(
            innerOrigin, params.hoodRoomWidth - 2 * params.hoodWallThickness,
            params.hoodRoomLength - 2 * params.hoodWallThickness,
            params.hoodRoomHeight - params.hoodWallThickness)
            .Shape();
    hoodRoom = BRepAlgoAPI_Cut(hoodRoom, innerHood).Shape();
  }

  // 创建风基座（长方体）
  double baseCenterX =
      params.ductLength + params.hoodRoomWidth / 2 + params.baseRoomWidth / 2;
  gp_Pnt baseOrigin(baseCenterX - params.baseWidth / 2, -params.baseLength / 2,
                    params.ductHeightDifference);
  TopoDS_Shape base = BRepPrimAPI_MakeBox(baseOrigin, params.baseWidth,
                                          params.baseLength, params.baseHeight)
                          .Shape();

  // 创建风基室（长方体）
  gp_Pnt baseRoomOrigin(
      baseCenterX - params.baseRoomWidth / 2 - params.baseRoomWallThickness,
      -params.baseRoomLength / 2 - params.baseRoomWallThickness,
      params.ductHeightDifference + params.baseHeight);
  TopoDS_Shape baseRoom =
      BRepPrimAPI_MakeBox(
          baseRoomOrigin,
          params.baseRoomWidth + (2 * params.baseRoomWallThickness),
          params.baseRoomLength + (2 * params.baseRoomWallThickness),
          params.baseRoomHeight)
          .Shape();

  // 创建风基室内腔（如果壁厚大于0）
  if (params.baseRoomWallThickness > 0) {
    gp_Pnt innerBaseRoomOrigin(baseCenterX - params.baseRoomWidth / 2,
                               -params.baseRoomLength / 2,
                               params.ductHeightDifference + params.baseHeight);
    TopoDS_Shape innerBaseRoom =
        BRepPrimAPI_MakeBox(innerBaseRoomOrigin, params.baseRoomWidth,
                            params.baseRoomLength, params.baseRoomHeight)
            .Shape();
    baseRoom = BRepAlgoAPI_Cut(baseRoom, innerBaseRoom).Shape();
  }

  // 创建风通道（倾斜圆柱）
  gp_Pnt ductStart(params.hoodRoomWidth / 2 - 2 * params.hoodWallThickness,
                   params.ductLeftDistance - params.hoodRoomLength / 2,
                   params.ductCenterHeight);
  gp_Pnt ductEnd(params.hoodRoomWidth / 2 + params.ductLength + 2 +
                     2 * params.baseRoomWallThickness,
                 params.ductLeftDistance - params.hoodRoomLength / 2,
                 params.ductCenterHeight + params.ductHeightDifference +
                     params.baseHeight);

  // 创建风通道外壁
  gp_Vec ductDir(ductEnd.X() - ductStart.X(), 0, ductEnd.Z() - ductStart.Z());
  TopoDS_Shape duct = BRepPrimAPI_MakeCylinder(gp_Ax2(ductStart, ductDir),
                                               params.ductDiameter / 2 +
                                                   params.ductWallThickness,
                                               ductDir.Magnitude())
                          .Shape();

  hoodRoom = BRepAlgoAPI_Cut(hoodRoom, duct).Shape();
  baseRoom = BRepAlgoAPI_Cut(baseRoom, duct).Shape();

  // 创建风通道内腔（如果壁厚大于0）
  if (params.ductWallThickness > 0) {
    TopoDS_Shape innerDuct =
        BRepPrimAPI_MakeCylinder(
            gp_Ax2(ductStart, ductDir), params.ductDiameter / 2,
            ductDir.Magnitude() + 2 * params.ductWallThickness)
            .Shape();
    duct = BRepAlgoAPI_Cut(duct, innerDuct).Shape();
  }

  // 合并所有部件
  TopoDS_Shape ventilationDuct = BRepAlgoAPI_Fuse(hoodRoom, duct).Shape();
  ventilationDuct = BRepAlgoAPI_Fuse(ventilationDuct, base).Shape();
  ventilationDuct = BRepAlgoAPI_Fuse(ventilationDuct, baseRoom).Shape();

  return ventilationDuct;
}

TopoDS_Shape
create_oblique_ventilation_duct(const oblique_ventilation_duct_params &params,
                                const gp_Pnt &position, const gp_Dir &direction,
                                const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的斜通风道
  TopoDS_Shape duct = create_oblique_ventilation_duct(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(duct, transformation);
  return transform.Shape();
}

TopoDS_Shape create_drainage_well(const drainage_well_params &params) {
  // 参数验证
  if (params.length <= 0 || params.width <= 0 || params.height <= 0) {
    throw Standard_ConstructionError(
        "Length, width and height must be positive");
  }
  if (params.wallThickness < 0 || params.bottomThickness < 0) {
    throw Standard_ConstructionError("Thickness values must be non-negative");
  }

  // 创建井主体外壁
  double outerLength = params.length + 2 * params.wallThickness;
  double outerWidth = params.width + 2 * params.wallThickness;
  double outerHeight = params.height + params.bottomThickness;

  gp_Pnt baseOrigin(-outerLength / 2, 0, 0);
  TopoDS_Shape outerBox =
      BRepPrimAPI_MakeBox(baseOrigin, outerLength, outerWidth, outerHeight)
          .Shape();

  // 创建井主体内腔
  gp_Pnt innerOrigin(-params.length / 2, params.wallThickness, 0);
  TopoDS_Shape innerBox = BRepPrimAPI_MakeBox(innerOrigin, params.length,
                                              params.width, params.height)
                              .Shape();

  // 从外壁中减去内腔
  TopoDS_Shape wellBody = BRepAlgoAPI_Cut(outerBox, innerBox).Shape();

  // 创建井脖
  if (params.neckDiameter > 0 && params.neckHeight > 0) {
    double neckDiameter = params.neckDiameter + 2 * params.wallThickness;

    gp_Ax2 neckAxis(
        gp_Pnt(0, outerWidth - params.wallThickness - params.neckDiameter / 2,
               outerHeight - 3 * params.wallThickness),
        gp::DZ());
    TopoDS_Shape neck =
        BRepPrimAPI_MakeCylinder(neckAxis, neckDiameter / 2,
                                 params.neckHeight + 3 * params.wallThickness)
            .Shape();

    // 合并井脖和主体
    wellBody = BRepAlgoAPI_Cut(wellBody, neck).Shape();

    gp_Ax2 innerNeckAxis(
        gp_Pnt(0, outerWidth - params.wallThickness - params.neckDiameter / 2,
               outerHeight - 4 * params.wallThickness),
        gp::DZ());
    TopoDS_Shape innerNseck =
        BRepPrimAPI_MakeCylinder(innerNeckAxis, params.neckDiameter / 2,
                                 params.neckHeight + 5 * params.wallThickness)
            .Shape();

    neck = BRepAlgoAPI_Cut(neck, innerNseck).Shape();
    wellBody = BRepAlgoAPI_Fuse(wellBody, neck).Shape();
  }

  // 创建垫层
  if (params.cushionExtension > 0) {
    double cushionLength = outerLength + 2 * params.cushionExtension;
    double cushionWidth = outerWidth + 2 * params.cushionExtension;

    gp_Pnt cushionOrigin(-cushionLength / 2, -params.cushionExtension,
                         -params.bottomThickness);
    TopoDS_Shape cushion =
        BRepPrimAPI_MakeBox(cushionOrigin, cushionLength, cushionWidth,
                            params.bottomThickness)
            .Shape();

    wellBody = BRepAlgoAPI_Fuse(wellBody, cushion).Shape();
  }

  return wellBody;
}

TopoDS_Shape create_drainage_well(const drainage_well_params &params,
                                  const gp_Pnt &position,
                                  const gp_Dir &direction, const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的排水井
  TopoDS_Shape well = create_drainage_well(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(well, transformation);
  return transform.Shape();
}

TopoDS_Shape create_pipe_support(const pipe_support_params &params) {
  // 参数验证
  if (params.length <= 0 || params.height <= 0) {
    throw Standard_ConstructionError("Length and height must be positive");
  }
  if (params.style != 1 && params.style != 2) {
    throw Standard_ConstructionError("Style must be 1 or 2");
  }
  if (params.count != params.positions.size() ||
      params.count != params.radii.size()) {
    throw Standard_ConstructionError("Position and radius count mismatch");
  }

  TopoDS_Shape support;
  if (params.style == 1) {
    gp_Pnt baseOrigin(-params.width / 2, -params.length / 2, 0);
    support = BRepPrimAPI_MakeBox(baseOrigin, params.width, params.length,
                                  params.height)
                  .Shape();
  } else {
    gp_Pnt baseOrigin(-params.width / 2, -params.length / 2,
                      -params.height / 2);
    support = BRepPrimAPI_MakeBox(baseOrigin, params.width, params.length,
                                  params.height)
                  .Shape();
  }

  // 创建管枕孔
  for (int i = 0; i < params.count; ++i) {
    if (params.radii[i] <= 0)
      continue;

    // 创建圆柱形孔
    gp_Pnt center(-params.width, params.positions[i].X(),
                  params.positions[i].Y());
    TopoDS_Shape hole =
        BRepPrimAPI_MakeCylinder(gp_Ax2(center, gp::DX()), params.radii[i],
                                 params.width * 2)
            .Shape();

    // 从基础中减去孔
    support = BRepAlgoAPI_Cut(support, hole).Shape();
  }

  return support;
}

TopoDS_Shape create_pipe_support(const pipe_support_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction, const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的管枕
  TopoDS_Shape support = create_pipe_support(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(support, transformation);
  return transform.Shape();
}

TopoDS_Shape create_cover_plate(const cover_plate_params &params) {
  // 参数验证
  if (params.thickness <= 0) {
    throw Standard_ConstructionError("Thickness must be positive");
  }

  TopoDS_Shape cover;

  if (params.style == 0) { // 长方形盖板
    if (params.length <= 0 || params.width <= 0) {
      throw Standard_ConstructionError(
          "Length and width must be positive for rectangular cover");
    }

    // 创建长方体盖板
    gp_Pnt origin(-params.length / 2, -params.width / 2, 0);
    cover = BRepPrimAPI_MakeBox(origin, params.length, params.width,
                                params.thickness)
                .Shape();

  } else if (params.style == 1) { // 扇形盖板
    // 参数验证
    if (params.length <= 0 || params.largeRadius <= 0 ||
        params.smallRadius <= 0) {
      throw Standard_ConstructionError(
          "参数必须满足：length > 0, largeRadius > 0, smallRadius > 0");
    }
    // 参数验证
    if (params.largeRadius <= params.smallRadius) {
      throw Standard_ConstructionError(
          "参数必须满足：largeRadius > smallRadius");
    }

    // 计算连接边长度
    double L3 = params.length;
    double L1 = params.smallRadius; // 小圆弧弧长
    double L2 = params.largeRadius; // 大圆弧弧长

    // 计算半径和角度
    double r1 = (L1 * L3) / (L2 - L1); // 小圆半径
    double theta = (L2 - L1) / L3;     // 扇形角度(弧度)
    double r2 = r1 + L3;               // 大圆半径

    // 创建内圆弧 - 修改坐标系使弧线对齐X轴
    gp_Pnt O(0, 0, 0);

    // 定义点
    gp_Pnt A(r1 * cos(-theta / 2), r1 * sin(-theta / 2), 0);
    gp_Pnt B(r1 * cos(theta / 2), r1 * sin(theta / 2), 0);
    gp_Pnt C(r2 * cos(-theta / 2), r2 * sin(-theta / 2), 0);
    gp_Pnt D(r2 * cos(theta / 2), r2 * sin(theta / 2), 0);

    // 使用 gp_Circ 创建圆，对称于 X 轴构造圆弧
    gp_Circ innerCircle(gp_Ax2(O, gp::DZ()), r1);
    gp_Circ outerCircle(gp_Ax2(O, gp::DZ()), r2);

    // 构造内圆弧
    Handle(Geom_TrimmedCurve) innerArc =
        GC_MakeArcOfCircle(innerCircle, -theta / 2, theta / 2, Standard_True)
            .Value();

    // 构造外圆弧
    Handle(Geom_TrimmedCurve) outerArc =
        GC_MakeArcOfCircle(outerCircle, -theta / 2, theta / 2, Standard_True)
            .Value();

    // 构造边
    TopoDS_Edge edgeInner = BRepBuilderAPI_MakeEdge(innerArc).Edge();
    TopoDS_Edge edgeOuter = BRepBuilderAPI_MakeEdge(outerArc).Edge();
    edgeOuter.Reverse();
    TopoDS_Edge edgeBD = BRepBuilderAPI_MakeEdge(B, D).Edge();
    TopoDS_Edge edgeAC = BRepBuilderAPI_MakeEdge(C, A).Edge();

    // 构建闭合Wire
    BRepBuilderAPI_MakeWire wireBuilder;
    wireBuilder.Add(edgeInner);
    wireBuilder.Add(edgeBD);
    wireBuilder.Add(edgeOuter);
    wireBuilder.Add(edgeAC);
    TopoDS_Wire wire = wireBuilder.Wire();

    // 创建面并拉伸
    TopoDS_Face face = BRepBuilderAPI_MakeFace(wire).Face();
    cover = BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, params.thickness)).Shape();

  } else {
    throw Standard_ConstructionError("Invalid cover plate style");
  }

  return cover;
}

TopoDS_Shape create_cover_plate(const cover_plate_params &params,
                                const gp_Pnt &position, const gp_Dir &normal,
                                const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 创建标准方向的盖板
  TopoDS_Shape cover = create_cover_plate(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(cover, transformation);
  return transform.Shape();
}

TopoDS_Shape create_cable_ray(const cable_ray_params &params) {
  // 参数验证
  if (params.outerLength <= 0 || params.outerHeight <= 0 ||
      params.innerLength <= 0 || params.innerHeight <= 0 ||
      params.coverThickness <= 0) {
    throw Standard_ConstructionError("All dimensions must be positive");
  }
  if (params.innerLength >= params.outerLength ||
      params.innerHeight >= params.outerHeight) {
    throw Standard_ConstructionError(
        "Inner dimensions must be smaller than outer dimensions");
  }

  // 创建槽盒主体外轮廓
  gp_Pnt outerOrigin(-params.outerLength / 2, -params.outerLength / 2, 0);
  TopoDS_Shape outerBox =
      BRepPrimAPI_MakeBox(outerOrigin, params.outerLength, params.outerLength,
                          params.outerLength)
          .Shape();

  // 创建槽盒主体内轮廓
  gp_Pnt innerOrigin(-params.innerLength / 2, -params.innerLength / 2,
                     params.outerHeight - params.innerHeight);
  TopoDS_Shape innerBox =
      BRepPrimAPI_MakeBox(innerOrigin, params.innerLength, params.innerLength,
                          params.outerLength + 2)
          .Shape();

  // 从外轮廓中减去内轮廓形成槽盒主体
  TopoDS_Shape troughBody = BRepAlgoAPI_Cut(outerBox, innerBox).Shape();

  // 创建盖板
  gp_Pnt coverOrigin(-params.outerLength / 2, -params.outerLength / 2,
                     params.outerLength + params.coverThickness);
  TopoDS_Shape cover =
      BRepPrimAPI_MakeBox(coverOrigin, params.outerLength, params.outerLength,
                          params.coverThickness)
          .Shape();

  // 合并槽盒主体和盖板
  return BRepAlgoAPI_Fuse(troughBody, cover).Shape();
}

TopoDS_Shape create_cable_ray(const cable_ray_params &params,
                              const gp_Pnt &position, const gp_Dir &direction,
                              const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的槽盒
  TopoDS_Shape trough = create_cable_ray(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(trough, transformation);
  return transform.Shape();
}

TopoDS_Shape create_water_tunnel(const water_tunnel_params &params) {
  // 参数验证
  if (params.width <= 0 || params.height <= 0) {
    throw Standard_ConstructionError("Width and height must be positive");
  }
  if (params.points.size() < 2) {
    throw Standard_ConstructionError("At least 2 points are required");
  }

  // 创建路径线框
  BRepBuilderAPI_MakeWire pathWire;

  // 处理点序列
  for (size_t i = 0; i < params.points.size() - 1; i++) {
    const gp_Pnt &current = params.points[i].position;
    const gp_Pnt &next = params.points[i + 1].position;

    if (params.points[i].type == 0 &&
        params.points[i + 1].type == 0) { // 普通节点
      // 创建直线段
      pathWire.Add(BRepBuilderAPI_MakeEdge(current, next).Edge());
    } else if (params.points[i].type == 1) { // 弧形节点
      // 确保有前一个点和后一个点
      if (i == 0 || i == params.points.size() - 1) {
        throw Standard_ConstructionError("弧形节点需要前后都有节点");
      }

      const gp_Pnt &prev = params.points[i - 1].position;

      // 创建三点圆弧
      pathWire.Add(BRepBuilderAPI_MakeEdge(
                       GC_MakeArcOfCircle(prev, current, next).Value())
                       .Edge());
    }
  }

  if (!pathWire.IsDone()) {
    throw Standard_ConstructionError("路径线框创建失败");
  }

  TopoDS_Wire path = pathWire.Wire();

  // 获取路径起始点的切线方向
  BRepAdaptor_CompCurve curveAdaptor(path);
  gp_Pnt startPoint;
  gp_Vec startTangent;
  curveAdaptor.D1(curveAdaptor.FirstParameter(), startPoint, startTangent);

  // 在创建截面圆之前添加方向修正
  gp_Dir tanDir = startTangent.Normalized();
  gp_Dir refDir = gp::DZ(); // 默认参考方向为全局Y轴

  // 如果tanDir平行于全局X轴，调整参考方向为全局Z轴
  if (IsParallel(tanDir, gp::DX())) {
    refDir = gp::DZ();
  }
  gp_Ax2 sectionAxes(startPoint, tanDir, refDir);

  // 创建变换对象
  gp_Trsf trsf;

  trsf.SetTransformation(sectionAxes, gp_Ax2(gp::Origin(), gp::DZ()));

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  if (params.cushionExtension > 0 && params.cushionThickness > 0 &&
      params.style == water_tunnel_section_style::RECTANGULAR) {
    double zoffset = -params.cushionThickness;

    double cushionWidth = params.width + 2 * params.cushionExtension +
                          2 * params.outerWallThickness;
    BRepBuilderAPI_MakeWire cushionMaker;
    gp_Pnt p1(0, -cushionWidth / 2 - params.cushionExtension, zoffset);
    gp_Pnt p2(0, cushionWidth / 2 + params.cushionExtension, zoffset);
    gp_Pnt p3(0, cushionWidth / 2 + params.cushionExtension,
              zoffset + params.cushionThickness);
    gp_Pnt p4(0, -cushionWidth / 2 - params.cushionExtension,
              zoffset + params.cushionThickness);

    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp1, projectedp2).Edge());
    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp2, projectedp3).Edge());
    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp3, projectedp4).Edge());
    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp4, projectedp1).Edge());

    TopoDS_Shape cushion = create_channel_shape(cushionMaker.Wire(), path);

    builder.Add(result, cushion);
  }

  // 创建隧道截面轮廓
  TopoDS_Wire outerWire;
  switch (params.style) {
  case water_tunnel_section_style::RECTANGULAR: {
    // 矩形截面
    double width = params.width + 2 * params.outerWallThickness;

    gp_Pnt p1(0, -width / 2, -params.bottomThickness);
    gp_Pnt p2(0, width / 2, -params.bottomThickness);
    gp_Pnt p3(0, width / 2, params.height + params.topThickness);
    gp_Pnt p4(0, -width / 2, params.height + params.topThickness);

    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    outerWire = BRepBuilderAPI_MakePolygon(projectedp1, projectedp2,
                                           projectedp3, projectedp4, true)
                    .Wire();
    break;
  }
  case water_tunnel_section_style::CITYOPENING: {
    // 城门洞截面 - 外部轮廓
    double arcHeight = params.arcHeight;
    if (arcHeight == 0 && params.arcRadius == 0) {
      throw Standard_ConstructionError(
          "Either arcHeight or arcRadius must be non-zero");
    }

    double outerWidth = params.width + 2 * params.outerWallThickness +
                        2 * params.innerWallThickness;
    double outerRadius = outerWidth / 2;
    double outerHeight =
        params.height + params.outerWallThickness + params.innerWallThickness;
    double outerArchHeight;

    // 计算拱高或拱半径
    if (arcHeight == 0) {
      // 根据拱半径计算拱高
      double halfWidth = params.width / 2;
      if (params.arcRadius < halfWidth) {
        throw Standard_ConstructionError(
            "Arc radius must be greater than or equal to half width");
      }
      arcHeight = params.arcRadius - sqrt(params.arcRadius * params.arcRadius -
                                          halfWidth * halfWidth);
      outerArchHeight =
          arcHeight + params.outerWallThickness + params.innerWallThickness;
    } else {
      // 使用提供的拱高
      outerArchHeight =
          arcHeight + params.outerWallThickness + params.innerWallThickness;
    }

    // 底部点
    gp_Pnt localBottomLeft(0, -outerRadius,
                           -params.outerWallThickness -
                               params.innerWallThickness);
    gp_Pnt bottomLeft = sectionAxes.Location().Translated(
        gp_Vec(localBottomLeft.Z(), localBottomLeft.Y(), 0).Transformed(trsf));

    gp_Pnt localBottomRight(
        0, outerRadius, -params.outerWallThickness - params.innerWallThickness);
    gp_Pnt bottomRight = sectionAxes.Location().Translated(
        gp_Vec(localBottomRight.Z(), localBottomRight.Y(), 0)
            .Transformed(trsf));

    // 侧壁点
    gp_Pnt localLeftTop(0, -outerRadius, outerHeight);
    gp_Pnt leftTop = sectionAxes.Location().Translated(
        gp_Vec(localLeftTop.Z(), localLeftTop.Y(), 0).Transformed(trsf));

    gp_Pnt localRightTop(0, outerRadius, outerHeight);
    gp_Pnt rightTop = sectionAxes.Location().Translated(
        gp_Vec(localRightTop.Z(), localRightTop.Y(), 0).Transformed(trsf));

    // 顶部圆弧中点
    gp_Pnt localArcMid(0, 0, outerHeight + outerArchHeight);
    gp_Pnt arcMid = sectionAxes.Location().Translated(
        gp_Vec(localArcMid.Z(), localArcMid.Y(), 0).Transformed(trsf));

    // 创建侧壁直线
    TopoDS_Edge leftEdge = BRepBuilderAPI_MakeEdge(bottomLeft, leftTop).Edge();
    TopoDS_Edge rightEdge =
        BRepBuilderAPI_MakeEdge(bottomRight, rightTop).Edge();

    // 创建顶部圆弧 (从右到左)
    Handle(Geom_TrimmedCurve) topArc =
        GC_MakeArcOfCircle(rightTop, arcMid, leftTop).Value();
    TopoDS_Edge topEdge = BRepBuilderAPI_MakeEdge(topArc).Edge();

    // 创建底部直线
    TopoDS_Edge bottomEdge =
        BRepBuilderAPI_MakeEdge(bottomLeft, bottomRight).Edge();

    // 组合成完整轮廓 (确保闭合)
    BRepBuilderAPI_MakeWire wireMaker;
    wireMaker.Add(leftEdge);
    wireMaker.Add(topEdge);
    wireMaker.Add(rightEdge);
    wireMaker.Add(bottomEdge);

    if (!wireMaker.IsDone()) {
      throw Standard_ConstructionError(
          "Failed to create closed wire for horseshoe section");
    }

    outerWire = wireMaker.Wire();

    if (!outerWire.Closed()) {
      throw Standard_ConstructionError("Outer horseshoe section is not closed");
    }
    break;
  }
  case water_tunnel_section_style::CIRCULAR: {
    // 圆形截面 - 外部轮廓
    double outerRadius = params.width / 2 + params.outerWallThickness;
    gp_Pnt center(0, 0, 0);
    Handle(Geom_Circle) outerCircle =
        new Geom_Circle(gp_Ax2(center, gp::DX()), outerRadius);
    TopoDS_Edge outerEdge = BRepBuilderAPI_MakeEdge(outerCircle).Edge();
    outerWire = BRepBuilderAPI_MakeWire(outerEdge).Wire();
    break;
  }
  case water_tunnel_section_style::HORSESHOE: {
    // 马蹄形截面 - 外部轮廓
    double outerWidth = params.width + 2 * params.outerWallThickness +
                        2 * params.innerWallThickness;
    double outerRadius = outerWidth / 2;
    double outerHeight =
        params.height + params.outerWallThickness + params.innerWallThickness;

    // 计算圆心位置
    double arcRadius = params.arcRadius + params.outerWallThickness +
                       params.innerWallThickness;

    // 底部连接段点
    gp_Pnt localBottomLeft(0, -outerRadius,
                           -params.outerWallThickness -
                               params.innerWallThickness);
    gp_Pnt bottomLeft = sectionAxes.Location().Translated(
        gp_Vec(localBottomLeft.Z(), localBottomLeft.Y(), 0).Transformed(trsf));

    gp_Pnt localBottomRight(
        0, outerRadius, -params.outerWallThickness - params.innerWallThickness);
    gp_Pnt bottomRight = sectionAxes.Location().Translated(
        gp_Vec(localBottomRight.Z(), localBottomRight.Y(), 0)
            .Transformed(trsf));

    // 计算钝角情况下的圆弧起点和终点
    double angle =
        (360 - params.arcAngle) * M_PI / 180.0; // 正确转换补角为 360-θ

    // 圆弧起点和终点计算(使用360补角)
    gp_Pnt localArcEnd(
        0, -arcRadius * sin(angle), // 当 angle>180° 时 sin 值为负，负负得正
        params.height - arcRadius * (1 - cos(angle)));
    gp_Pnt arcEnd = sectionAxes.Location().Translated(
        gp_Vec(localArcEnd.Z(), localArcEnd.Y(), 0).Transformed(trsf));

    gp_Pnt localArcStart(0,
                         arcRadius * sin(angle), // 当 angle>180° 时 sin 值为负
                         params.height - arcRadius * (1 - cos(angle)));
    gp_Pnt arcStart = sectionAxes.Location().Translated(
        gp_Vec(localArcStart.Z(), localArcStart.Y(), 0).Transformed(trsf));

    // 创建左侧连接段(从底部到顶部)
    TopoDS_Edge leftSegment =
        BRepBuilderAPI_MakeEdge(bottomLeft, arcStart).Edge();

    // 创建右侧连接段(从顶部到底部)
    TopoDS_Edge rightSegment =
        BRepBuilderAPI_MakeEdge(arcEnd, bottomRight).Edge();

    // 创建顶部圆弧(从右到左)
    gp_Pnt localArcMid(0, 0, outerHeight);
    gp_Pnt arcMid = sectionAxes.Location().Translated(
        gp_Vec(localArcMid.Z(), localArcMid.Y(), 0).Transformed(trsf));

    Handle(Geom_TrimmedCurve) topArc =
        GC_MakeArcOfCircle(arcStart, arcMid, arcEnd).Value();

    TopoDS_Edge bootomEgde =
        BRepBuilderAPI_MakeEdge(bottomRight, bottomLeft).Edge();
    bootomEgde.Reversed();

    // 修正连接顺序和边方向
    BRepBuilderAPI_MakeWire wireMaker;
    wireMaker.Add(leftSegment);                            // 左侧连接段
    wireMaker.Add(BRepBuilderAPI_MakeEdge(topArc).Edge()); // 顶部圆弧
    wireMaker.Add(rightSegment);                           // 右侧连接段
    wireMaker.Add(bootomEgde);                             // 底部边

    // 添加完整性检查
    if (!wireMaker.IsDone() || !wireMaker.Wire().Closed()) {
      // 输出调试信息
      throw Standard_ConstructionError(
          "Failed to create closed wire for horseshoe section");
    }

    outerWire = wireMaker.Wire();

    break;
  }
  default:
    throw Standard_ConstructionError("Invalid tunnel section style");
  }
  TopoDS_Shape outer = create_channel_shape(outerWire, path);

  // 创建隧道截面轮廓
  TopoDS_Wire innerWire;
  switch (params.style) {
  case water_tunnel_section_style::RECTANGULAR: {
    // 矩形截面
    gp_Pnt p1(0, -params.width / 2, 0);
    gp_Pnt p2(0, params.width / 2, 0);
    gp_Pnt p3(0, params.width / 2, params.height);
    gp_Pnt p4(0, -params.width / 2, params.height);

    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    innerWire = BRepBuilderAPI_MakePolygon(projectedp1, projectedp2,
                                           projectedp3, projectedp4, true)
                    .Wire();
    break;
  }
  case water_tunnel_section_style::CITYOPENING: {
    double arcHeight = params.arcHeight;
    if (arcHeight == 0 && params.arcRadius == 0) {
      throw Standard_ConstructionError(
          "Either arcHeight or arcRadius must be non-zero");
    }

    // 马蹄形截面 - 内部轮廓
    double innerRadius = params.width / 2;
    double innerHeight = params.height;
    double innerArchHeight = params.arcHeight;

    // 计算拱高或拱半径
    if (arcHeight == 0) {
      // 根据拱半径计算拱高
      double halfWidth = innerRadius;
      if (params.arcRadius < halfWidth) {
        throw Standard_ConstructionError(
            "Arc radius must be greater than or equal to half width");
      }
      innerArchHeight =
          params.arcRadius -
          sqrt(params.arcRadius * params.arcRadius - halfWidth * halfWidth);
    } else {
      // 使用提供的拱高
      innerArchHeight = arcHeight;
    }

    // 底部点
    gp_Pnt localBottomLeft(0, -innerRadius, 0);
    gp_Pnt bottomLeft = sectionAxes.Location().Translated(
        gp_Vec(localBottomLeft.Z(), localBottomLeft.Y(), 0).Transformed(trsf));

    gp_Pnt localBottomRight(0, innerRadius, 0);
    gp_Pnt bottomRight = sectionAxes.Location().Translated(
        gp_Vec(localBottomRight.Z(), localBottomRight.Y(), 0)
            .Transformed(trsf));

    // 侧壁点
    gp_Pnt localLeftTop(0, -innerRadius, innerHeight);
    gp_Pnt leftTop = sectionAxes.Location().Translated(
        gp_Vec(localLeftTop.Z(), localLeftTop.Y(), 0).Transformed(trsf));

    gp_Pnt localRightTop(0, innerRadius, innerHeight);
    gp_Pnt rightTop = sectionAxes.Location().Translated(
        gp_Vec(localRightTop.Z(), localRightTop.Y(), 0).Transformed(trsf));

    // 顶部圆弧中点
    gp_Pnt localArcMid(0, 0, innerHeight + innerArchHeight);
    gp_Pnt arcMid = sectionAxes.Location().Translated(
        gp_Vec(localArcMid.Z(), localArcMid.Y(), 0).Transformed(trsf));

    // 创建侧壁直线
    TopoDS_Edge leftEdge = BRepBuilderAPI_MakeEdge(bottomLeft, leftTop).Edge();
    TopoDS_Edge rightEdge =
        BRepBuilderAPI_MakeEdge(bottomRight, rightTop).Edge();

    // 创建顶部圆弧 (从右到左)
    Handle(Geom_TrimmedCurve) topArc =
        GC_MakeArcOfCircle(rightTop, arcMid, leftTop).Value();
    TopoDS_Edge topEdge = BRepBuilderAPI_MakeEdge(topArc).Edge();

    // 创建底部直线
    TopoDS_Edge bottomEdge =
        BRepBuilderAPI_MakeEdge(bottomLeft, bottomRight).Edge();

    // 组合成完整轮廓 (确保闭合)
    BRepBuilderAPI_MakeWire wireMaker;
    wireMaker.Add(leftEdge);
    wireMaker.Add(topEdge);
    wireMaker.Add(rightEdge);
    wireMaker.Add(bottomEdge);

    if (!wireMaker.IsDone()) {
      throw Standard_ConstructionError(
          "Failed to create closed wire for inner horseshoe section");
    }

    innerWire = wireMaker.Wire();

    if (!innerWire.Closed()) {
      throw Standard_ConstructionError("Inner horseshoe section is not closed");
    }
    break;
  }
  case water_tunnel_section_style::CIRCULAR: {
    // 圆形截面 - 内部轮廓
    double innerRadius = params.width / 2;
    gp_Pnt center(0, 0, 0);
    Handle(Geom_Circle) innerCircle =
        new Geom_Circle(gp_Ax2(center, gp::DX()), innerRadius);
    TopoDS_Edge innerEdge = BRepBuilderAPI_MakeEdge(innerCircle).Edge();
    innerWire = BRepBuilderAPI_MakeWire(innerEdge).Wire();
    break;
  }
  case water_tunnel_section_style::HORSESHOE: {
    // 马蹄形截面 - 内部轮廓
    double innerWidth = params.width; // 内净宽
    double innerRadius = innerWidth / 2;
    double innerHeight = params.height; // 内净高

    // 计算内轮廓圆心位置
    double innerArcRadius = params.arcRadius;

    // 内轮廓底部点
    gp_Pnt localBottomLeft(0, -innerRadius, 0);
    gp_Pnt innerBottomLeft = sectionAxes.Location().Translated(
        gp_Vec(localBottomLeft.Z(), localBottomLeft.Y(), 0).Transformed(trsf));

    gp_Pnt localBottomRight(0, innerRadius, 0);
    gp_Pnt innerBottomRight = sectionAxes.Location().Translated(
        gp_Vec(localBottomRight.Z(), localBottomRight.Y(), 0)
            .Transformed(trsf));

    // 计算内轮廓圆弧起点和终点
    double innerAngle =
        (360 - params.arcAngle) * M_PI / 180.0; // 正确转换补角为 360-θ

    gp_Pnt localArcEnd(0, -innerArcRadius * sin(innerAngle),
                       params.height - innerArcRadius * (1 - cos(innerAngle)));
    gp_Pnt innerArcEnd = sectionAxes.Location().Translated(
        gp_Vec(localArcEnd.Z(), localArcEnd.Y(), 0).Transformed(trsf));

    gp_Pnt localArcStart(0, innerArcRadius * sin(innerAngle),
                         params.height -
                             innerArcRadius * (1 - cos(innerAngle)));
    gp_Pnt innerArcStart = sectionAxes.Location().Translated(
        gp_Vec(localArcStart.Z(), localArcStart.Y(), 0).Transformed(trsf));

    // 创建内轮廓左侧连接段
    TopoDS_Edge innerLeftSegment =
        BRepBuilderAPI_MakeEdge(innerBottomLeft, innerArcStart).Edge();

    // 创建内轮廓右侧连接段
    TopoDS_Edge innerRightSegment =
        BRepBuilderAPI_MakeEdge(innerArcEnd, innerBottomRight).Edge();

    // 创建顶部圆弧(从右到左)
    gp_Pnt localArcMid(0, 0, innerHeight);
    gp_Pnt innerArcMid = sectionAxes.Location().Translated(
        gp_Vec(localArcMid.Z(), localArcMid.Y(), 0).Transformed(trsf));

    Handle(Geom_TrimmedCurve) innerTopArc =
        GC_MakeArcOfCircle(innerArcStart, innerArcMid, innerArcEnd).Value();

    TopoDS_Edge innerTopEdge = BRepBuilderAPI_MakeEdge(innerTopArc).Edge();

    // 创建内轮廓底部边
    TopoDS_Edge innerBottomEdge =
        BRepBuilderAPI_MakeEdge(innerBottomRight, innerBottomLeft).Edge();
    innerBottomEdge.Reversed();

    // 组合内轮廓线框
    BRepBuilderAPI_MakeWire innerWireMaker;
    innerWireMaker.Add(innerLeftSegment);
    innerWireMaker.Add(innerTopEdge);
    innerWireMaker.Add(innerRightSegment);
    innerWireMaker.Add(innerBottomEdge);

    if (!innerWireMaker.IsDone() || !innerWireMaker.Wire().Closed()) {
      throw Standard_ConstructionError(
          "Failed to create closed wire for inner horseshoe section");
    }

    innerWire = innerWireMaker.Wire();
    break;
  }
  default:
    throw Standard_ConstructionError("Invalid tunnel section style");
  }

  TopoDS_Shape inner = create_channel_shape(innerWire, path);

  // 处理底部平台
  if (params.style == water_tunnel_section_style::CIRCULAR &&
      params.bottomPlatformHeight != 0) {
    double innerRadius = params.width / 2;

    double zoffset = -innerRadius;
    gp_Pnt p1(0, -innerRadius, -innerRadius + params.bottomPlatformHeight);
    gp_Pnt p2(0, innerRadius, -innerRadius + params.bottomPlatformHeight);
    gp_Pnt p3(0, innerRadius, -innerRadius);
    gp_Pnt p4(0, -innerRadius, -innerRadius);

    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    TopoDS_Wire tempWire =
        BRepBuilderAPI_MakePolygon(projectedp1, projectedp2, projectedp3,
                                   projectedp4, true)
            .Wire();
    TopoDS_Shape cutBottom = create_channel_shape(tempWire, path);

    inner = BRepAlgoAPI_Cut(inner, cutBottom).Shape();
  }

  TopoDS_Shape tunnel = BRepAlgoAPI_Cut(outer, inner).Shape();
  builder.Add(result, tunnel);

  return result;
}

TopoDS_Shape create_water_tunnel(const water_tunnel_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction, const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的输水隧洞
  TopoDS_Shape tunnel = create_water_tunnel(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(tunnel, transformation);
  return transform.Shape();
}

} // namespace topo
} // namespace flywave
