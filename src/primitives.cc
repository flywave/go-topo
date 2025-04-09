#include "primitives.hh"
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepBuilderAPI_MakeShell.hxx>
#include <BRepBuilderAPI_MakeSolid.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_Sewing.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepFilletAPI_MakeChamfer.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <GeomAPI_Interpolate.hxx>
#include <GeomAPI_PointsToBSpline.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Plane.hxx>
#include <Precision.hxx>
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
    throw Standard_ConstructionError(
        "Polar and equatorial radii must be positive");
  }

  if (params.height <= 0.0 || params.height > 2 * params.polarRadius) {
    throw Standard_ConstructionError("Height must be in range (0, 2*LR]");
  }

  // 在YZ平面创建椭圆曲线（X=0平面）
  gp_Elips ellipse(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0)), params.polarRadius,
                   params.equatorialRadius);

  // 创建椭圆边并生成闭合线
  TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(ellipse).Edge();
  TopoDS_Wire wire = BRepBuilderAPI_MakeWire(edge).Wire();

  // 绕X轴旋转360度生成椭球面
  gp_Ax1 revolutionAxis(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0));
  BRepPrimAPI_MakeRevol revolMaker(wire, revolutionAxis);
  TopoDS_Shape fullEllipsoid = revolMaker.Shape();

  // 如果需要切割（H < 2*LR）
  if (params.height < 2 * params.polarRadius) {
    // 创建切割平面（沿X轴在X=H-LR位置切割）
    double cutPosition = params.height - params.polarRadius;
    gp_Pln cutPlane(gp_Pnt(cutPosition, 0, 0), gp_Dir(1, 0, 0));
    TopoDS_Face cuttingFace = BRepBuilderAPI_MakeFace(cutPlane).Face();

    // 执行布尔切割操作
    BRepAlgoAPI_Cut cutter(fullEllipsoid, cuttingFace);
    if (!cutter.IsDone()) {
      throw Standard_ConstructionError("Failed to cut the ellipsoid");
    }
    return cutter.Shape();
  }

  return fullEllipsoid;
}

TopoDS_Shape
create_rotational_ellipsoid(const rotational_ellipsoid_params &params,
                            const gp_Pnt &center, const gp_Dir &xDirection) {
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
  // 参数验证（基于技术图纸要求）
  if (params.topDiag1 < 0 || params.topDiag2 < 0)
    throw Standard_ConstructionError("Top diagonals must be non-negative");
  if (params.bottomDiag1 <= 0 || params.bottomDiag2 <= 0)
    throw Standard_ConstructionError("Bottom diagonals must be positive");
  if (params.height <= 0)
    throw Standard_ConstructionError("Height must be positive");

  // 相似性验证 TL1/LL1 ≈ TL2/LL2
  const double ratioTolerance = 0.01; // 允许1%的误差
  double ratio1 = (params.topDiag1 > Precision::Confusion())
                      ? params.topDiag1 / params.bottomDiag1
                      : 0;
  double ratio2 = (params.topDiag2 > Precision::Confusion())
                      ? params.topDiag2 / params.bottomDiag2
                      : 0;

  if (fabs(ratio1 - ratio2) > ratioTolerance)
    throw Standard_ConstructionError(
        "Diagonals must maintain consistent scaling ratio");

  // 创建底面菱形（技术图纸中的基准面）
  TColgp_Array1OfPnt bottomVerts(1, 5); // 闭合多边形需要回到起点
  auto pnt1 = gp_Pnt(params.bottomDiag1 / 2, 0, 0);  // X+顶点
  auto pnt2 = gp_Pnt(0, params.bottomDiag2 / 2, 0);  // Y+顶点
  auto pnt3 = gp_Pnt(-params.bottomDiag1 / 2, 0, 0); // X-顶点
  auto pnt4 = gp_Pnt(0, -params.bottomDiag2 / 2, 0); // Y-顶点

  TopoDS_Wire bottomWire =
      BRepBuilderAPI_MakePolygon(pnt1, pnt2, pnt3, pnt4, Standard_True).Wire();

  // 创建顶面菱形（按比例缩放）
  double scaleFactor = (ratio1 + ratio2) / 2; // 平均比例因子
  pnt1 = gp_Pnt(params.topDiag1 / 2, 0, params.height);
  pnt2 = gp_Pnt(0, params.topDiag2 / 2, params.height);
  pnt3 = gp_Pnt(-params.topDiag1 / 2, 0, params.height);
  pnt4 = gp_Pnt(0, -params.topDiag2 / 2, params.height);

  // 构建技术实体
  BRepOffsetAPI_ThruSections generator(Standard_True); // 生成实体
  generator.AddWire(bottomWire);

  if (params.topDiag1 > Precision::Confusion() &&
      params.topDiag2 > Precision::Confusion()) {
    TopoDS_Wire topWire =
        BRepBuilderAPI_MakePolygon(pnt1, pnt2, pnt3, pnt4, Standard_True)
            .Wire();
    generator.AddWire(topWire);
  } else {
    BRepBuilderAPI_MakeVertex mkVertex(gp_Pnt(0, 0, params.height));
    generator.AddVertex(mkVertex.Vertex()); // 锥体顶点
  }

  generator.Build();
  if (!generator.IsDone())
    throw Standard_ConstructionError("Failed to generate technical frustum");

  return generator.Shape();
}

TopoDS_Shape create_diamond_frustum(const diamond_frustum &params,
                                    const gp_Pnt &position,
                                    const gp_Dir &normal, const gp_Dir &xDir) {
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
  if (params.bendAngle <= Precision::Angular() || params.bendAngle >= M_PI)
    throw Standard_ConstructionError("Bend angle must be in (0, PI)");

  // 创建第一段圆柱（X轴负方向）
  gp_Ax2 axis1(gp_Pnt(-params.length, 0, 0), gp::DX());
  TopoDS_Shape cylinder1 =
      BRepPrimAPI_MakeCylinder(axis1, params.radius, params.length).Shape();

  // 创建第二段圆柱（旋转后的方向）
  gp_Dir dir2 =
      gp::DX().Rotated(gp_Ax1(gp::Origin(), gp::DZ()), params.bendAngle);
  gp_Ax2 axis2(gp::Origin(), dir2);
  TopoDS_Shape cylinder2 =
      BRepPrimAPI_MakeCylinder(axis2, params.radius, params.length).Shape();

  // 合并两个圆柱
  BRepBuilderAPI_Sewing sewer;
  sewer.Add(cylinder1);
  sewer.Add(cylinder2);
  sewer.Perform();
  TopoDS_Shape mergedShape = sewer.SewedShape();

  // 获取交线进行锐角处理
  TopExp_Explorer edgeExplorer(mergedShape, TopAbs_EDGE);
  TopoDS_Edge sharpEdge;
  for (; edgeExplorer.More(); edgeExplorer.Next()) {
    const TopoDS_Edge &edge = TopoDS::Edge(edgeExplorer.Current());
    if (BRep_Tool::Degenerated(edge))
      continue;
    sharpEdge = edge;
    break;
  }

  // 创建锐角过渡（最小化圆角半径）
  BRepFilletAPI_MakeFillet filletMaker(mergedShape);
  filletMaker.Add(Precision::Confusion() * 0.1, sharpEdge); // 极小圆角模拟锐角
  filletMaker.Build();

  if (!filletMaker.IsDone())
    throw Standard_ConstructionError("Failed to create sharp bend");

  return filletMaker.Shape();
}

TopoDS_Shape
create_sharp_bent_cylinder(const sharp_bent_cylinder_params &params,
                           const gp_Pnt &bendPoint, const gp_Dir &initialDir,
                           const gp_Dir &bendPlaneNormal) {
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
    // 创建路径圆弧（XY平面，中心在原点）
    gp_Circ pathCircle(gp_Ax2(gp::Origin(), gp::DZ()), params.ringRadius);
    Handle_Geom_TrimmedCurve arc =
        GC_MakeArcOfCircle(pathCircle, 0.0, params.angle, true).Value();

    // 将曲线转换为Wire
    TopoDS_Edge pathEdge = BRepBuilderAPI_MakeEdge(arc).Edge();
    TopoDS_Wire pathWire = BRepBuilderAPI_MakeWire(pathEdge).Wire();

    // 创建截面圆（YZ平面）
    gp_Circ sectionCircle(gp_Ax2(gp_Pnt(params.ringRadius, 0, 0), gp::DX()),
                          params.tubeRadius);
    TopoDS_Edge sectionEdge = BRepBuilderAPI_MakeEdge(sectionCircle).Edge();
    TopoDS_Wire sectionWire = BRepBuilderAPI_MakeWire(sectionEdge).Wire();

    // 沿路径扫掠（使用Wire作为路径）
    BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
    pipeMaker.Add(sectionWire);
    pipeMaker.Build();

    if (!pipeMaker.IsDone())
      throw Standard_ConstructionError("Failed to generate pipe");

    return pipeMaker.Shape();
  }
}

TopoDS_Shape create_ring(const ring_params &params, const gp_Pnt &center,
                         const gp_Dir &normal, const gp_Dir &xDir) {
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
  if (params.tubeRadius <= 0.0 || params.tubeRadius >= params.width) {
    throw Standard_ConstructionError("Tube radius must be in (0, W)");
  }
  if (params.filletRadius < 0.0 || params.filletRadius >= params.width / 2) {
    throw Standard_ConstructionError("Fillet radius must be in [0, W/2)");
  }
  if (params.length <= params.width) {
    throw Standard_ConstructionError("Length must be greater than width");
  }
  if (params.width <= 0.0) {
    throw Standard_ConstructionError("Width must be positive");
  }

  // 创建外轮廓路径
  double outerLength = params.length - 2 * params.filletRadius;
  double outerWidth = params.width - 2 * params.filletRadius;

  // 创建外轮廓路径点
  gp_Pnt p1(-outerLength / 2, -outerWidth / 2, 0);
  gp_Pnt p2(outerLength / 2, -outerWidth / 2, 0);
  gp_Pnt p3(outerLength / 2, outerWidth / 2, 0);
  gp_Pnt p4(-outerLength / 2, outerWidth / 2, 0);

  // 创建外轮廓路径
  BRepBuilderAPI_MakeWire outerWireMaker;
  if (params.filletRadius > Precision::Confusion()) {
    // 带倒角的路径
    gp_Pnt corner1(outerLength / 2, -outerWidth / 2, 0);
    gp_Pnt corner2(outerLength / 2, outerWidth / 2, 0);
    gp_Pnt corner3(-outerLength / 2, outerWidth / 2, 0);
    gp_Pnt corner4(-outerLength / 2, -outerWidth / 2, 0);

    // 创建直线段和圆弧段
    TopoDS_Edge edge1 = BRepBuilderAPI_MakeEdge(p1, corner1).Edge();
    TopoDS_Edge arc1 =
        BRepBuilderAPI_MakeEdge(
            GC_MakeArcOfCircle(
                corner1, corner1.Translated(gp_Vec(params.filletRadius, 0, 0)),
                corner2)
                .Value())
            .Edge();
    TopoDS_Edge edge2 = BRepBuilderAPI_MakeEdge(corner2, p3).Edge();
    TopoDS_Edge arc2 =
        BRepBuilderAPI_MakeEdge(
            GC_MakeArcOfCircle(
                corner2, corner2.Translated(gp_Vec(0, params.filletRadius, 0)),
                corner3)
                .Value())
            .Edge();
    TopoDS_Edge edge3 = BRepBuilderAPI_MakeEdge(corner3, p4).Edge();
    TopoDS_Edge arc3 =
        BRepBuilderAPI_MakeEdge(
            GC_MakeArcOfCircle(
                corner3, corner3.Translated(gp_Vec(-params.filletRadius, 0, 0)),
                corner4)
                .Value())
            .Edge();
    TopoDS_Edge edge4 = BRepBuilderAPI_MakeEdge(corner4, p1).Edge();
    TopoDS_Edge arc4 =
        BRepBuilderAPI_MakeEdge(
            GC_MakeArcOfCircle(
                corner4, corner4.Translated(gp_Vec(0, -params.filletRadius, 0)),
                corner1)
                .Value())
            .Edge();

    outerWireMaker.Add(edge1);
    outerWireMaker.Add(arc1);
    outerWireMaker.Add(edge2);
    outerWireMaker.Add(arc2);
    outerWireMaker.Add(edge3);
    outerWireMaker.Add(arc3);
    outerWireMaker.Add(edge4);
    outerWireMaker.Add(arc4);
  } else {
    // 无倒角的路径
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p1).Edge());
  }
  TopoDS_Wire outerWire = outerWireMaker.Wire();

  // 创建内轮廓路径
  double innerLength =
      params.length - 2 * (params.filletRadius + params.tubeRadius);
  double innerWidth =
      params.width - 2 * (params.filletRadius + params.tubeRadius);

  // 创建内轮廓路径点
  gp_Pnt p5(-innerLength / 2, -innerWidth / 2, 0);
  gp_Pnt p6(innerLength / 2, -innerWidth / 2, 0);
  gp_Pnt p7(innerLength / 2, innerWidth / 2, 0);
  gp_Pnt p8(-innerLength / 2, innerWidth / 2, 0);

  // 创建内轮廓路径
  BRepBuilderAPI_MakeWire innerWireMaker;
  if (params.filletRadius > Precision::Confusion()) {
    // 带倒角的路径
    gp_Pnt corner5(innerLength / 2, -innerWidth / 2, 0);
    gp_Pnt corner6(innerLength / 2, innerWidth / 2, 0);
    gp_Pnt corner7(-innerLength / 2, innerWidth / 2, 0);
    gp_Pnt corner8(-innerLength / 2, -innerWidth / 2, 0);

    // 创建直线段和圆弧段
    TopoDS_Edge edge5 = BRepBuilderAPI_MakeEdge(p5, corner5).Edge();
    TopoDS_Edge arc5 =
        BRepBuilderAPI_MakeEdge(
            GC_MakeArcOfCircle(
                corner5, corner5.Translated(gp_Vec(params.filletRadius, 0, 0)),
                corner6)
                .Value())
            .Edge();
    TopoDS_Edge edge6 = BRepBuilderAPI_MakeEdge(corner6, p7).Edge();
    TopoDS_Edge arc6 =
        BRepBuilderAPI_MakeEdge(
            GC_MakeArcOfCircle(
                corner6, corner6.Translated(gp_Vec(0, params.filletRadius, 0)),
                corner7)
                .Value())
            .Edge();

    TopoDS_Edge edge7 = BRepBuilderAPI_MakeEdge(corner7, p8).Edge();
    TopoDS_Edge arc7 =
        BRepBuilderAPI_MakeEdge(
            GC_MakeArcOfCircle(
                corner7, corner7.Translated(gp_Vec(-params.filletRadius, 0, 0)),
                corner8)
                .Value())
            .Edge();

    TopoDS_Edge edge8 = BRepBuilderAPI_MakeEdge(corner8, p5).Edge();
    TopoDS_Edge arc8 =
        BRepBuilderAPI_MakeEdge(
            GC_MakeArcOfCircle(
                corner8, corner8.Translated(gp_Vec(0, -params.filletRadius, 0)),
                corner5)
                .Value())
            .Edge();

    innerWireMaker.Add(edge5);
    innerWireMaker.Add(arc5);
    innerWireMaker.Add(edge6);
    innerWireMaker.Add(arc6);
    innerWireMaker.Add(edge7);
    innerWireMaker.Add(arc7);
    innerWireMaker.Add(edge8);
    innerWireMaker.Add(arc8);
  } else {
    // 无倒角的路径
    innerWireMaker.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge());
    innerWireMaker.Add(BRepBuilderAPI_MakeEdge(p6, p7).Edge());
    innerWireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8).Edge());
    innerWireMaker.Add(BRepBuilderAPI_MakeEdge(p8, p5).Edge());
  }
  TopoDS_Wire innerWire = innerWireMaker.Wire();

  // 创建面
  BRepBuilderAPI_MakeFace outerFaceMaker(outerWire);
  BRepBuilderAPI_MakeFace innerFaceMaker(innerWire);
  if (!outerFaceMaker.IsDone() || !innerFaceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create faces");
  }

  // 执行布尔差操作
  BRepAlgoAPI_Cut cutter(outerFaceMaker.Face(), innerFaceMaker.Face());
  if (!cutter.IsDone()) {
    throw Standard_ConstructionError("Failed to perform boolean operation");
  }

  // 创建扫掠路径
  gp_Circ pathCircle(gp_Ax2(gp::Origin(), gp::DZ()), params.tubeRadius);
  TopoDS_Edge pathEdge = BRepBuilderAPI_MakeEdge(pathCircle).Edge();
  TopoDS_Wire pathWire = BRepBuilderAPI_MakeWire(pathEdge).Wire();

  // 沿路径扫掠
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.Add(cutter.Shape());
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to generate pipe shell");
  }

  return pipeMaker.Shape();
}

TopoDS_Shape create_rectangular_ring(const rectangular_ring_params &params,
                                     const gp_Pnt &center, const gp_Dir &normal,
                                     const gp_Dir &xDir) {
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
  gp_Circ sectionCircle(gp_Ax2(gp_Pnt(params.majorRadius, 0, 0), gp::DX()),
                        params.tubeRadius);
  TopoDS_Edge sectionEdge = BRepBuilderAPI_MakeEdge(sectionCircle).Edge();
  TopoDS_Wire sectionWire = BRepBuilderAPI_MakeWire(sectionEdge).Wire();

  // 沿椭圆路径扫掠
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.Add(sectionWire);
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to generate elliptic ring");
  }

  return pipeMaker.Shape();
}

TopoDS_Shape create_elliptic_ring(const elliptic_ring_params &params,
                                  const gp_Pnt &center, const gp_Dir &normal,
                                  const gp_Dir &xDir) {
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

TopoDS_Shape create_circular_gasket(const circular_gasket_params &params) {
  // 参数验证
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

  // 创建外圆路径
  gp_Circ outerCircle(gp_Ax2(gp::Origin(), gp::DZ()), params.outerRadius);
  Handle_Geom_TrimmedCurve outerArc =
      GC_MakeArcOfCircle(outerCircle, 0.0, params.angle, true).Value();
  TopoDS_Edge outerEdge = BRepBuilderAPI_MakeEdge(outerArc).Edge();
  TopoDS_Wire outerWire = BRepBuilderAPI_MakeWire(outerEdge).Wire();

  // 创建内圆路径
  gp_Circ innerCircle(gp_Ax2(gp::Origin(), gp::DZ()), params.innerRadius);
  Handle_Geom_TrimmedCurve innerArc =
      GC_MakeArcOfCircle(innerCircle, 0.0, params.angle, true).Value();
  TopoDS_Edge innerEdge = BRepBuilderAPI_MakeEdge(innerArc).Edge();
  TopoDS_Wire innerWire = BRepBuilderAPI_MakeWire(innerEdge).Wire();

  // 创建面
  BRepBuilderAPI_MakeFace outerFaceMaker(outerWire);
  BRepBuilderAPI_MakeFace innerFaceMaker(innerWire);
  if (!outerFaceMaker.IsDone() || !innerFaceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create faces");
  }

  // 执行布尔差操作
  BRepAlgoAPI_Cut cutter(outerFaceMaker.Face(), innerFaceMaker.Face());
  if (!cutter.IsDone()) {
    throw Standard_ConstructionError("Failed to perform boolean operation");
  }

  // 创建扫掠路径（直线沿Z轴）
  gp_Pnt startPoint(0, 0, 0);
  gp_Pnt endPoint(0, 0, params.height);
  TopoDS_Edge pathEdge = BRepBuilderAPI_MakeEdge(startPoint, endPoint).Edge();
  TopoDS_Wire pathWire = BRepBuilderAPI_MakeWire(pathEdge).Wire();

  // 沿路径扫掠
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.Add(cutter.Shape());
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to generate circular gasket");
  }

  return pipeMaker.Shape();
}

TopoDS_Shape create_circular_gasket(const circular_gasket_params &params,
                                    const gp_Pnt &center, const gp_Dir &normal,
                                    const gp_Dir &xDir) {
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
  if (params.topRadius <= params.innerRadius ||
      params.topRadius >= params.outerRadius) {
    throw Standard_ConstructionError(
        "Top radius must be between inner and outer radii");
  }
  if (params.outerRadius <= params.topRadius) {
    throw Standard_ConstructionError(
        "Outer radius must be greater than top radius");
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

  // 创建底部外圆路径
  gp_Circ bottomOuterCircle(gp_Ax2(gp::Origin(), gp::DZ()), params.outerRadius);
  Handle_Geom_TrimmedCurve bottomOuterArc =
      GC_MakeArcOfCircle(bottomOuterCircle, 0.0, params.angle, true).Value();
  TopoDS_Edge bottomOuterEdge = BRepBuilderAPI_MakeEdge(bottomOuterArc).Edge();
  TopoDS_Wire bottomOuterWire = BRepBuilderAPI_MakeWire(bottomOuterEdge).Wire();

  // 创建顶部外圆路径
  gp_Circ topOuterCircle(gp_Ax2(gp::Origin(), gp::DZ()), params.topRadius);
  Handle_Geom_TrimmedCurve topOuterArc =
      GC_MakeArcOfCircle(topOuterCircle, 0.0, params.angle, true).Value();
  TopoDS_Edge topOuterEdge = BRepBuilderAPI_MakeEdge(topOuterArc).Edge();
  TopoDS_Wire topOuterWire = BRepBuilderAPI_MakeWire(topOuterEdge).Wire();

  // 创建内圆路径
  gp_Circ innerCircle(gp_Ax2(gp::Origin(), gp::DZ()), params.innerRadius);
  Handle_Geom_TrimmedCurve innerArc =
      GC_MakeArcOfCircle(innerCircle, 0.0, params.angle, true).Value();
  TopoDS_Edge innerEdge = BRepBuilderAPI_MakeEdge(innerArc).Edge();
  TopoDS_Wire innerWire = BRepBuilderAPI_MakeWire(innerEdge).Wire();

  // 创建外轮廓放样
  BRepOffsetAPI_ThruSections outerGenerator(Standard_True);
  outerGenerator.AddWire(bottomOuterWire);
  outerGenerator.AddWire(topOuterWire);
  outerGenerator.Build();
  if (!outerGenerator.IsDone()) {
    throw Standard_ConstructionError("Failed to generate outer profile");
  }

  // 创建内轮廓面
  BRepBuilderAPI_MakeFace innerFaceMaker(innerWire);
  if (!innerFaceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create inner face");
  }

  // 执行布尔差操作
  BRepAlgoAPI_Cut cutter(outerGenerator.Shape(), innerFaceMaker.Face());
  if (!cutter.IsDone()) {
    throw Standard_ConstructionError("Failed to perform boolean operation");
  }

  // 创建扫掠路径（直线沿Z轴）
  gp_Pnt startPoint(0, 0, 0);
  gp_Pnt endPoint(0, 0, params.height);
  TopoDS_Edge pathEdge = BRepBuilderAPI_MakeEdge(startPoint, endPoint).Edge();
  TopoDS_Wire pathWire = BRepBuilderAPI_MakeWire(pathEdge).Wire();

  // 沿路径扫掠
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.Add(cutter.Shape());
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to generate table gasket");
  }

  return pipeMaker.Shape();
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
    throw Standard_ConstructionError(
        "Outer length must be greater than inner length");
  }
  if (params.outerWidth <= params.innerWidth) {
    throw Standard_ConstructionError(
        "Outer width must be greater than inner width");
  }
  if (params.innerLength <= 0.0 || params.innerWidth <= 0.0) {
    throw Standard_ConstructionError("Inner dimensions must be positive");
  }
  if (params.height <= 0.0) {
    throw Standard_ConstructionError("Height must be positive");
  }
  if (params.cornerType < 1 || params.cornerType > 3) {
    throw Standard_ConstructionError("Corner type must be 1, 2 or 3");
  }

  // 创建外轮廓路径点
  gp_Pnt outerP1(-params.outerLength / 2, -params.outerWidth / 2, 0);
  gp_Pnt outerP2(params.outerLength / 2, -params.outerWidth / 2, 0);
  gp_Pnt outerP3(params.outerLength / 2, params.outerWidth / 2, 0);
  gp_Pnt outerP4(-params.outerLength / 2, params.outerWidth / 2, 0);

  // 创建内轮廓路径点
  gp_Pnt innerP1(-params.innerLength / 2, -params.innerWidth / 2, 0);
  gp_Pnt innerP2(params.innerLength / 2, -params.innerWidth / 2, 0);
  gp_Pnt innerP3(params.innerLength / 2, params.innerWidth / 2, 0);
  gp_Pnt innerP4(-params.innerLength / 2, params.innerWidth / 2, 0);

  // 创建外轮廓路径
  BRepBuilderAPI_MakeWire outerWireMaker;
  if (params.cornerType == 2 && params.cornerParam > Precision::Confusion()) {
    // 圆角处理
    gp_Pnt corner1(params.outerLength / 2 - params.cornerParam,
                   -params.outerWidth / 2, 0);
    gp_Pnt corner2(params.outerLength / 2,
                   -params.outerWidth / 2 + params.cornerParam, 0);
    gp_Pnt corner3(params.outerLength / 2,
                   params.outerWidth / 2 - params.cornerParam, 0);
    gp_Pnt corner4(params.outerLength / 2 - params.cornerParam,
                   params.outerWidth / 2, 0);
    gp_Pnt corner5(-params.outerLength / 2 + params.cornerParam,
                   params.outerWidth / 2, 0);
    gp_Pnt corner6(-params.outerLength / 2,
                   params.outerWidth / 2 - params.cornerParam, 0);
    gp_Pnt corner7(-params.outerLength / 2,
                   -params.outerWidth / 2 + params.cornerParam, 0);
    gp_Pnt corner8(-params.outerLength / 2 + params.cornerParam,
                   -params.outerWidth / 2, 0);

    // 创建直线段和圆弧段
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(outerP1, corner1).Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(
                           GC_MakeArcOfCircle(corner1, corner2,
                                              gp_Pnt(params.outerLength / 2,
                                                     -params.outerWidth / 2, 0))
                               .Value())
                           .Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(corner2, outerP2).Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(outerP2, corner3).Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(
                           GC_MakeArcOfCircle(corner3, corner4,
                                              gp_Pnt(params.outerLength / 2,
                                                     params.outerWidth / 2, 0))
                               .Value())
                           .Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(corner4, outerP3).Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(outerP3, corner5).Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(
                           GC_MakeArcOfCircle(corner5, corner6,
                                              gp_Pnt(-params.outerLength / 2,
                                                     params.outerWidth / 2, 0))
                               .Value())
                           .Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(corner6, outerP4).Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(outerP4, corner7).Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(
                           GC_MakeArcOfCircle(corner7, corner8,
                                              gp_Pnt(-params.outerLength / 2,
                                                     -params.outerWidth / 2, 0))
                               .Value())
                           .Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(corner8, outerP1).Edge());
  } else if (params.cornerType == 3 &&
             params.cornerParam > Precision::Confusion()) {
    // 切角处理
    gp_Pnt corner1(params.outerLength / 2 - params.cornerParam,
                   -params.outerWidth / 2, 0);
    gp_Pnt corner2(params.outerLength / 2,
                   -params.outerWidth / 2 + params.cornerParam, 0);
    gp_Pnt corner3(params.outerLength / 2,
                   params.outerWidth / 2 - params.cornerParam, 0);
    gp_Pnt corner4(params.outerLength / 2 - params.cornerParam,
                   params.outerWidth / 2, 0);
    gp_Pnt corner5(-params.outerLength / 2 + params.cornerParam,
                   params.outerWidth / 2, 0);
    gp_Pnt corner6(-params.outerLength / 2,
                   params.outerWidth / 2 - params.cornerParam, 0);
    gp_Pnt corner7(-params.outerLength / 2,
                   -params.outerWidth / 2 + params.cornerParam, 0);
    gp_Pnt corner8(-params.outerLength / 2 + params.cornerParam,
                   -params.outerWidth / 2, 0);

    // 创建直线段和切角段
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(outerP1, corner1).Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(corner1, corner2).Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(corner2, outerP2).Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(outerP2, corner3).Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(corner3, corner4).Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(corner4, outerP3).Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(outerP3, corner5).Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(corner5, corner6).Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(corner6, outerP4).Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(outerP4, corner7).Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(corner7, corner8).Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(corner8, outerP1).Edge());
  } else {
    // 直角处理或无倒角
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(outerP1, outerP2).Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(outerP2, outerP3).Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(outerP3, outerP4).Edge());
    outerWireMaker.Add(BRepBuilderAPI_MakeEdge(outerP4, outerP1).Edge());
  }
  TopoDS_Wire outerWire = outerWireMaker.Wire();

  // 创建内轮廓路径
  BRepBuilderAPI_MakeWire innerWireMaker;
  innerWireMaker.Add(BRepBuilderAPI_MakeEdge(innerP1, innerP2).Edge());
  innerWireMaker.Add(BRepBuilderAPI_MakeEdge(innerP2, innerP3).Edge());
  innerWireMaker.Add(BRepBuilderAPI_MakeEdge(innerP3, innerP4).Edge());
  innerWireMaker.Add(BRepBuilderAPI_MakeEdge(innerP4, innerP1).Edge());
  TopoDS_Wire innerWire = innerWireMaker.Wire();

  // 创建面
  BRepBuilderAPI_MakeFace outerFaceMaker(outerWire);
  BRepBuilderAPI_MakeFace innerFaceMaker(innerWire);
  if (!outerFaceMaker.IsDone() || !innerFaceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create faces");
  }

  // 执行布尔差操作
  BRepAlgoAPI_Cut cutter(outerFaceMaker.Face(), innerFaceMaker.Face());
  if (!cutter.IsDone()) {
    throw Standard_ConstructionError("Failed to perform boolean operation");
  }

  // 创建扫掠路径（直线沿Z轴）
  gp_Pnt startPoint(0, 0, 0);
  gp_Pnt endPoint(0, 0, params.height);
  TopoDS_Edge pathEdge = BRepBuilderAPI_MakeEdge(startPoint, endPoint).Edge();
  TopoDS_Wire pathWire = BRepBuilderAPI_MakeWire(pathEdge).Wire();

  // 沿路径扫掠
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.Add(cutter.Shape());
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to generate square gasket");
  }

  return pipeMaker.Shape();
}

TopoDS_Shape create_square_gasket(const square_gasket_params &params,
                                  const gp_Pnt &center, const gp_Dir &normal,
                                  const gp_Dir &xDir) {
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
  // 参数验证
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

  // 计算每片伞裙的高度
  double segmentHeight =
      params.height / (params.count * 2 + 1); // 伞裙和中间圆柱的高度

  // 创建主圆柱体
  gp_Ax2 axis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  BRepPrimAPI_MakeCylinder mainCylinder(axis, params.radius, params.height);

  // 创建伞裙
  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);
  builder.Add(compound, mainCylinder.Shape());

  for (int i = 0; i < params.count; ++i) {
    // 大伞裙位置
    double zPos = (2 * i + 1) * segmentHeight;

    // 创建大伞裙（碟形）
    gp_Pnt center(0, 0, zPos);
    gp_Dir normal(0, 0, 1);

    // 创建碟形伞裙（使用圆环面）
    gp_Ax2 skirtAxis(center, normal);
    BRepPrimAPI_MakeTorus bigSkirt(skirtAxis,
                                   params.bigSkirtRadius - params.radius,
                                   segmentHeight * 0.4); // 40%高度用于碟形伞裙

    // 小伞裙位置（在大伞裙下方）
    double smallZPos = (2 * i + 2) * segmentHeight;

    // 创建小伞裙（碟形）
    gp_Pnt smallCenter(0, 0, smallZPos);
    gp_Ax2 smallSkirtAxis(smallCenter, normal);
    BRepPrimAPI_MakeTorus smallSkirt(
        smallSkirtAxis, params.smallSkirtRadius - params.radius,
        segmentHeight * 0.4); // 40%高度用于碟形伞裙

    builder.Add(compound, bigSkirt.Shape());
    builder.Add(compound, smallSkirt.Shape());
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
  // 参数验证
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

  // 创建主锥形体
  gp_Ax2 axis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  BRepPrimAPI_MakeCone mainCone(axis, params.bottomRadius, params.topRadius,
                                params.height);

  // 创建伞裙
  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);
  builder.Add(compound, mainCone.Shape());

  // 计算每片伞裙的高度
  double segmentHeight = params.height / (params.count + 1);

  for (int i = 1; i <= params.count; ++i) {
    // 计算当前高度的插值比例
    double ratio = static_cast<double>(i) / (params.count + 1);

    // 插值计算当前半径和伞裙半径
    double currentRadius =
        params.bottomRadius + (params.topRadius - params.bottomRadius) * ratio;
    double currentSkirtRadius1 =
        params.bottomSkirtRadius1 +
        (params.topSkirtRadius1 - params.bottomSkirtRadius1) * ratio;
    double currentSkirtRadius2 =
        params.bottomSkirtRadius2 +
        (params.topSkirtRadius2 - params.bottomSkirtRadius2) * ratio;

    // 交替使用两种伞裙半径
    double skirtRadius =
        (i % 2 == 0) ? currentSkirtRadius1 : currentSkirtRadius2;

    // 创建伞裙位置
    double zPos = i * segmentHeight;

    // 创建碟形伞裙（使用圆环面）
    gp_Pnt center(0, 0, zPos);
    gp_Ax2 skirtAxis(center, gp_Dir(0, 0, 1));
    BRepPrimAPI_MakeTorus skirt(skirtAxis, skirtRadius - currentRadius,
                                segmentHeight * 0.4); // 40%高度用于碟形伞裙

    builder.Add(compound, skirt.Shape());
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
  // 参数验证
  if (params.count <= 0) {
    throw Standard_ConstructionError("Count must be positive");
  }
  if (params.spacing <= 2 * params.bigSkirtRadius) {
    throw Standard_ConstructionError("Spacing must be greater than 2*R1");
  }
  if (params.insulatorCount <= 0) {
    throw Standard_ConstructionError("Insulator count must be positive");
  }
  if (params.height <= 0.0) {
    throw Standard_ConstructionError("Height must be positive");
  }
  if (params.bigSkirtRadius < params.smallSkirtRadius) {
    throw Standard_ConstructionError(
        "Big skirt radius must be >= small skirt radius");
  }
  if (params.smallSkirtRadius <= params.radius) {
    throw Standard_ConstructionError(
        "Small skirt radius must be > tube radius");
  }
  if (params.radius <= 0.0) {
    throw Standard_ConstructionError("Radius must be positive");
  }
  if (params.frontLength <= 0.0 || params.backLength <= 0.0) {
    throw Standard_ConstructionError("Lengths must be positive");
  }
  if (params.splitCount <= 0) {
    throw Standard_ConstructionError("Split count must be positive");
  }

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  // 计算总高度
  double totalHeight = params.insulatorCount * params.height;

  // 创建构架端连接杆（X轴方向）
  gp_Ax2 frameAxis(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0));
  BRepPrimAPI_MakeCylinder frameRod(frameAxis, params.radius / 2,
                                    params.frontLength);
  builder.Add(compound, frameRod.Shape());

  // 创建导线端连接杆（X轴方向）
  gp_Ax2 wireAxis(gp_Pnt(totalHeight, 0, 0), gp_Dir(1, 0, 0));
  BRepPrimAPI_MakeCylinder wireRod(wireAxis, params.radius / 2,
                                   params.backLength);
  builder.Add(compound, wireRod.Shape());

  // 创建绝缘子串
  for (int i = 0; i < params.count; ++i) {
    // 计算Y轴偏移（对称分布）
    double yOffset = (i % 2 == 0) ? params.spacing / 2 : -params.spacing / 2;

    // 创建绝缘子串
    for (int j = 0; j < params.insulatorCount; ++j) {
      // 计算当前高度
      double zPos = j * params.height;

      // 创建绝缘子圆柱
      gp_Ax2 insulatorAxis(gp_Pnt(zPos, yOffset, 0), gp_Dir(0, 1, 0));
      BRepPrimAPI_MakeCylinder insulator(insulatorAxis, params.radius,
                                         params.height);
      builder.Add(compound, insulator.Shape());

      // 创建伞裙（交替大小）
      double skirtRadius =
          (j % 2 == 0) ? params.bigSkirtRadius : params.smallSkirtRadius;

      // 创建碟形伞裙（使用圆环面）
      gp_Ax2 skirtAxis(gp_Pnt(zPos, yOffset, 0), gp_Dir(0, 1, 0));
      BRepPrimAPI_MakeTorus skirt(skirtAxis, skirtRadius - params.radius,
                                  params.height * 0.4);
      builder.Add(compound, skirt.Shape());
    }
  }

  // 创建分裂导线连接件
  if (params.splitCount > 1) {
    double angleStep = 2 * M_PI / params.splitCount;
    for (int k = 0; k < params.splitCount; ++k) {
      double angle = k * angleStep;
      double x = totalHeight + params.backLength;
      double y = params.radius * 2 * cos(angle);
      double z = params.radius * 2 * sin(angle);

      // 创建连接线
      gp_Pnt start(totalHeight, 0, 0);
      gp_Pnt end(x, y, z);
      TopoDS_Edge wire = BRepBuilderAPI_MakeEdge(start, end).Edge();
      builder.Add(compound, wire);
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

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  // 计算V型角度
  double vAngle = atan2(params.backSpacing / 2, params.frontSpacing / 2) * 2;

  // 创建构架端连接杆（Y轴方向，对称分布）
  gp_Ax2 leftFrameAxis(gp_Pnt(-params.frontSpacing / 2, 0, 0), gp_Dir(0, 1, 0));
  BRepPrimAPI_MakeCylinder leftFrameRod(leftFrameAxis, params.radius / 2,
                                        params.frontLength);
  builder.Add(compound, leftFrameRod.Shape());

  gp_Ax2 rightFrameAxis(gp_Pnt(params.frontSpacing / 2, 0, 0), gp_Dir(0, 1, 0));
  BRepPrimAPI_MakeCylinder rightFrameRod(rightFrameAxis, params.radius / 2,
                                         params.frontLength);
  builder.Add(compound, rightFrameRod.Shape());

  // 创建导线端连接杆（Y轴方向）
  gp_Ax2 wireAxis(gp_Pnt(0, params.backSpacing / 2, 0), gp_Dir(0, 1, 0));
  BRepPrimAPI_MakeCylinder wireRod(wireAxis, params.radius / 2,
                                   params.backLength);
  builder.Add(compound, wireRod.Shape());

  // 创建左侧绝缘子串
  for (int j = 0; j < params.insulatorCount; ++j) {
    // 计算当前高度
    double zPos = j * params.height;

    // 计算当前位置（沿V型角度）
    double xPos = -zPos * sin(vAngle / 2);
    double yPos = zPos * cos(vAngle / 2);

    // 创建绝缘子圆柱
    gp_Ax2 insulatorAxis(gp_Pnt(xPos, yPos, 0),
                         gp_Dir(-sin(vAngle / 2), cos(vAngle / 2), 0));
    BRepPrimAPI_MakeCylinder insulator(insulatorAxis, params.radius,
                                       params.height);
    builder.Add(compound, insulator.Shape());

    // 创建伞裙（交替大小）
    double skirtRadius =
        (j % 2 == 0) ? params.bigSkirtRadius : params.smallSkirtRadius;

    // 创建碟形伞裙（使用圆环面）
    gp_Ax2 skirtAxis(gp_Pnt(xPos, yPos, 0),
                     gp_Dir(-sin(vAngle / 2), cos(vAngle / 2), 0));
    BRepPrimAPI_MakeTorus skirt(skirtAxis, skirtRadius - params.radius,
                                params.height * 0.4);
    builder.Add(compound, skirt.Shape());
  }

  // 创建右侧绝缘子串
  for (int j = 0; j < params.insulatorCount; ++j) {
    // 计算当前高度
    double zPos = j * params.height;

    // 计算当前位置（沿V型角度）
    double xPos = zPos * sin(vAngle / 2);
    double yPos = zPos * cos(vAngle / 2);

    // 创建绝缘子圆柱
    gp_Ax2 insulatorAxis(gp_Pnt(xPos, yPos, 0),
                         gp_Dir(sin(vAngle / 2), cos(vAngle / 2), 0));
    BRepPrimAPI_MakeCylinder insulator(insulatorAxis, params.radius,
                                       params.height);
    builder.Add(compound, insulator.Shape());

    // 创建伞裙（交替大小）
    double skirtRadius =
        (j % 2 == 0) ? params.bigSkirtRadius : params.smallSkirtRadius;

    // 创建碟形伞裙（使用圆环面）
    gp_Ax2 skirtAxis(gp_Pnt(xPos, yPos, 0),
                     gp_Dir(sin(vAngle / 2), cos(vAngle / 2), 0));
    BRepPrimAPI_MakeTorus skirt(skirtAxis, skirtRadius - params.radius,
                                params.height * 0.4);
    builder.Add(compound, skirt.Shape());
  }

  // 创建分裂导线连接件
  if (params.splitCount > 1) {
    double angleStep = 2 * M_PI / params.splitCount;
    for (int k = 0; k < params.splitCount; ++k) {
      double angle = k * angleStep;
      double x = params.radius * 2 * cos(angle);
      double y = params.backSpacing / 2 + params.backLength;
      double z = params.radius * 2 * sin(angle);

      // 创建连接线
      gp_Pnt start(0, params.backSpacing / 2, 0);
      gp_Pnt end(x, y, z);
      TopoDS_Edge wire = BRepBuilderAPI_MakeEdge(start, end).Edge();
      builder.Add(compound, wire);
    }
  }

  return compound;
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
 * @param phase 相位信息 (A/B/C/N)
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
  if (params.phase != 'A' && params.phase != 'B' && params.phase != 'C' &&
      params.phase != 'N') {
    throw Standard_ConstructionError("Phase must be A, B, C or N");
  }

  // 创建基础长方体
  gp_Ax2 axis(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0));
  BRepPrimAPI_MakeBox boxMaker(axis, params.width, params.thickness,
                               params.length);
  TopoDS_Shape block = boxMaker.Shape();

  // 添加倒角
  if (params.chamferLength > Precision::Confusion()) {
    TopTools_IndexedMapOfShape edges;
    TopExp::MapShapes(block, TopAbs_EDGE, edges);

    BRepFilletAPI_MakeChamfer chamferMaker(block);

    // 为所有边添加倒角
    for (int i = 1; i <= edges.Extent(); ++i) {
      TopoDS_Edge edge = TopoDS::Edge(edges.FindKey(i));
      chamferMaker.Add(params.chamferLength, edge);
    }

    if (chamferMaker.IsDone()) {
      block = chamferMaker.Shape();
    }
  }

  // 创建孔洞
  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);
  builder.Add(compound, block);

  // 计算孔洞起始位置
  double startX =
      -params.width / 2 +
      (params.width - (params.columnCount - 1) * params.columnSpacing) / 2;
  double startZ = -params.length / 2 + params.bottomOffset;

  // 创建孔洞
  for (int col = 0; col < params.columnCount; ++col) {
    for (int row = 0; row < params.rowCount; ++row) {
      double x = startX + col * params.columnSpacing;
      double z = startZ + row * params.rowSpacing;

      // 创建圆柱孔
      gp_Ax2 holeAxis(gp_Pnt(x, params.thickness / 2, z), gp_Dir(0, 1, 0));
      BRepPrimAPI_MakeCylinder holeMaker(holeAxis, params.holeRadius,
                                         params.thickness * 1.1);

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

  // 根据相位添加标记
  if (params.phase != 'N') {
    // 创建相位标记位置
    double markX = params.width / 2 - params.chamferLength * 2;
    double markZ = params.length / 2 - params.chamferLength * 2;

    // 创建相位标记
    gp_Ax2 markAxis(gp_Pnt(markX, params.thickness / 2, markZ),
                    gp_Dir(0, 1, 0));
    BRepPrimAPI_MakeCylinder markMaker(markAxis, params.chamferLength / 4,
                                       params.thickness * 1.1);

    // 执行布尔差操作
    BRepAlgoAPI_Cut cutter(compound, markMaker.Shape());
    if (!cutter.IsDone()) {
      throw Standard_ConstructionError("Failed to create phase mark");
    }

    TopoDS_Compound newCompound;
    builder.MakeCompound(newCompound);
    builder.Add(newCompound, cutter.Shape());
    compound = newCompound;
  }

  return compound;
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
  gp_Ax2 axis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
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

  // 创建孔洞
  for (int col = 0; col < params.columnCount; ++col) {
    for (int row = 0; row < params.rowCount; ++row) {
      // 跳过中间孔（如果需要单独处理）
      if (params.hasMiddleHole && col == params.columnCount / 2 &&
          row == params.rowCount / 2) {
        continue;
      }

      double x = startX + col * params.columnSpacing;
      double y = startY + row * params.rowSpacing;

      // 创建圆柱孔
      gp_Ax2 holeAxis(gp_Pnt(x, y, params.thickness / 2), gp_Dir(0, 0, 1));
      BRepPrimAPI_MakeCylinder holeMaker(holeAxis, params.holeDiameter / 2,
                                         params.thickness * 1.1);

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
  if (params.hasMiddleHole) {
    gp_Ax2 middleHoleAxis(gp_Pnt(0, 0, params.thickness / 2), gp_Dir(0, 0, 1));
    BRepPrimAPI_MakeCylinder middleHoleMaker(
        middleHoleAxis, params.holeDiameter / 2, params.thickness * 1.1);

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
  gp_Ax2 axis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
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
    gp_Ax2 holeAxis(gp_Pnt(x, y, params.thickness / 2), gp_Dir(0, 0, 1));
    BRepPrimAPI_MakeCylinder holeMaker(holeAxis, params.holeDiameter / 2,
                                       params.thickness * 1.1);

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
    gp_Ax2 middleHoleAxis(gp_Pnt(0, 0, params.thickness / 2), gp_Dir(0, 0, 1));
    BRepPrimAPI_MakeCylinder middleHoleMaker(
        middleHoleAxis, params.holeDiameter / 2, params.thickness * 1.1);

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

  if (!params.fitPoints.empty()) {
    // 使用拟合点集创建样条曲线
    Handle(TColgp_HArray1OfPnt) points =
        new TColgp_HArray1OfPnt(1, params.fitPoints.size());
    for (int i = 0; i < params.fitPoints.size(); ++i) {
      points->SetValue(i + 1, params.fitPoints[i]);
    }

    GeomAPI_Interpolate interpolate(points, false, Precision::Confusion());
    interpolate.Perform();
    if (!interpolate.IsDone()) {
      throw Standard_ConstructionError("Failed to create interpolated curve");
    }

    Handle(Geom_BSplineCurve) curve = interpolate.Curve();
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

  // 创建导线截面圆
  gp_Circ sectionCircle(gp_Ax2(params.startPoint, params.startDir),
                        params.diameter / 2);
  TopoDS_Edge sectionEdge = BRepBuilderAPI_MakeEdge(sectionCircle).Edge();
  TopoDS_Wire sectionWire = BRepBuilderAPI_MakeWire(sectionEdge).Wire();

  // 沿路径扫掠创建导线
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.Add(sectionWire);
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to generate wire");
  }

  return pipeMaker.Shape();
}

TopoDS_Shape create_wire(const wire_params &params, const gp_Pnt &position,
                         const gp_Dir &direction, const gp_Dir &upDirection) {
  // 首先创建标准方向的导线
  TopoDS_Shape wire = create_wire(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0), gp_Dir(1, 0, 0));
  gp_Ax3 targetAx3(position, direction, upDirection);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(wire, transformation);
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

  // 创建样条曲线
  Handle(TColgp_HArray1OfPnt) points =
      new TColgp_HArray1OfPnt(1, allPoints.size());
  for (int i = 0; i < allPoints.size(); ++i) {
    points->SetValue(i + 1, allPoints[i]);
  }

  GeomAPI_Interpolate interpolate(points, false, Precision::Confusion());
  interpolate.Perform();
  if (!interpolate.IsDone()) {
    throw Standard_ConstructionError("Failed to create interpolated curve");
  }

  Handle(Geom_BSplineCurve) curve = interpolate.Curve();
  wireMaker.Add(BRepBuilderAPI_MakeEdge(curve).Edge());

  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create cable path");
  }
  TopoDS_Wire pathWire = wireMaker.Wire();

  // 创建电缆截面圆
  gp_Circ sectionCircle(gp_Ax2(params.startPoint, gp_Dir(0, 0, 1)),
                        params.diameter / 2);
  TopoDS_Edge sectionEdge = BRepBuilderAPI_MakeEdge(sectionCircle).Edge();
  TopoDS_Wire sectionWire = BRepBuilderAPI_MakeWire(sectionEdge).Wire();

  // 沿路径扫掠创建电缆
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.Add(sectionWire);
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to generate cable");
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

/**
 * @brief 创建等边角钢图元
 *
 * @param model 型号 (如"L50X4"表示边宽50mm，厚度4mm)
 * @param length 长度 (Length > 0)
 * @return TopoDS_Shape 生成的等边角钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_equilateral_angle_steel(const std::string &model,
                                            double length) {
  // 参数验证
  if (length <= 0.0) {
    throw Standard_ConstructionError("Length must be positive");
  }
  if (model.empty() || model[0] != 'L') {
    throw Standard_ConstructionError("Invalid model format");
  }

  // 解析型号参数
  size_t xPos = model.find('X');
  if (xPos == std::string::npos) {
    throw Standard_ConstructionError("Invalid model format");
  }

  double width = std::stod(model.substr(1, xPos - 1));
  double thickness = std::stod(model.substr(xPos + 1));

  if (width <= 0.0 || thickness <= 0.0) {
    throw Standard_ConstructionError("Width and thickness must be positive");
  }
  if (thickness >= width) {
    throw Standard_ConstructionError("Thickness must be less than width");
  }

  // 创建角钢截面轮廓
  BRepBuilderAPI_MakeWire wireMaker;

  // 外轮廓点
  gp_Pnt p1(0, 0, 0);
  gp_Pnt p2(width, 0, 0);
  gp_Pnt p3(width, thickness, 0);
  gp_Pnt p4(thickness, thickness, 0);
  gp_Pnt p5(thickness, width, 0);
  gp_Pnt p6(0, width, 0);

  // 创建外轮廓线
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p6, p1).Edge());

  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create angle steel profile");
  }
  TopoDS_Wire profileWire = wireMaker.Wire();

  // 创建截面面
  BRepBuilderAPI_MakeFace faceMaker(profileWire);
  if (!faceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create angle steel face");
  }

  // 沿Z轴拉伸创建角钢
  gp_Vec direction(0, 0, length);
  BRepPrimAPI_MakePrism prismMaker(faceMaker.Face(), direction);

  if (!prismMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to extrude angle steel");
  }

  return prismMaker.Shape();
}

/**
 * @brief 创建带定位的等边角钢
 *
 * @param model 型号
 * @param length 长度
 * @param position 底面中心点位置
 * @param direction 长度方向（默认Z轴）
 * @param xDir 截面X方向（默认X轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape
create_equilateral_angle_steel(const std::string &model, double length,
                               const gp_Pnt &position,
                               const gp_Dir &direction = gp_Dir(0, 0, 1),
                               const gp_Dir &xDir = gp_Dir(1, 0, 0)) {
  // 首先创建标准方向的等边角钢
  TopoDS_Shape angleSteel = create_equilateral_angle_steel(model, length);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  gp_Dir yDir = direction.Crossed(xDir);
  gp_Ax3 targetAx3(position, direction, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(angleSteel, transformation);
  return transform.Shape();
}

/**
 * @brief 创建不等边角钢图元
 *
 * @param model 型号 (如"L100X50X6"表示长边100mm，短边50mm，厚度6mm)
 * @param length 长度 (Length > 0)
 * @return TopoDS_Shape 生成的不等边角钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_scalene_angle_steel(const std::string &model,
                                        double length) {
  // 参数验证
  if (length <= 0.0) {
    throw Standard_ConstructionError("Length must be positive");
  }
  if (model.empty() || model[0] != 'L') {
    throw Standard_ConstructionError("Invalid model format");
  }

  // 解析型号参数
  size_t x1Pos = model.find('X');
  size_t x2Pos = model.find('X', x1Pos + 1);
  if (x1Pos == std::string::npos || x2Pos == std::string::npos) {
    throw Standard_ConstructionError("Invalid model format");
  }

  double longSide = std::stod(model.substr(1, x1Pos - 1));
  double shortSide = std::stod(model.substr(x1Pos + 1, x2Pos - x1Pos - 1));
  double thickness = std::stod(model.substr(x2Pos + 1));

  if (longSide <= 0.0 || shortSide <= 0.0 || thickness <= 0.0) {
    throw Standard_ConstructionError("Dimensions must be positive");
  }
  if (thickness >= longSide || thickness >= shortSide) {
    throw Standard_ConstructionError(
        "Thickness must be less than side lengths");
  }

  // 创建角钢截面轮廓
  BRepBuilderAPI_MakeWire wireMaker;

  // 外轮廓点
  gp_Pnt p1(0, 0, 0);
  gp_Pnt p2(longSide, 0, 0);
  gp_Pnt p3(longSide, thickness, 0);
  gp_Pnt p4(thickness, thickness, 0);
  gp_Pnt p5(thickness, shortSide, 0);
  gp_Pnt p6(0, shortSide, 0);

  // 创建外轮廓线
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p6, p1).Edge());

  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create angle steel profile");
  }
  TopoDS_Wire profileWire = wireMaker.Wire();

  // 创建截面面
  BRepBuilderAPI_MakeFace faceMaker(profileWire);
  if (!faceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create angle steel face");
  }

  // 沿Z轴拉伸创建角钢
  gp_Vec direction(0, 0, length);
  BRepPrimAPI_MakePrism prismMaker(faceMaker.Face(), direction);

  if (!prismMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to extrude angle steel");
  }

  return prismMaker.Shape();
}

/**
 * @brief 创建带定位的不等边角钢
 *
 * @param model 型号
 * @param length 长度
 * @param position 底面中心点位置
 * @param direction 长度方向（默认Z轴）
 * @param xDir 长边方向（默认X轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_scalene_angle_steel(const std::string &model, double length,
                                        const gp_Pnt &position,
                                        const gp_Dir &direction = gp_Dir(0, 0,
                                                                         1),
                                        const gp_Dir &xDir = gp_Dir(1, 0, 0)) {
  // 首先创建标准方向的不等边角钢
  TopoDS_Shape angleSteel = create_scalene_angle_steel(model, length);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  gp_Dir yDir = direction.Crossed(xDir);
  gp_Ax3 targetAx3(position, direction, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(angleSteel, transformation);
  return transform.Shape();
}
/**
 * @brief 创建工字钢截面轮廓（带圆弧过渡）
 * @param height 总高度
 * @param flangeWidth 翼缘宽度
 * @param webThickness 腹板厚度
 * @param flangeThickness 翼缘厚度
 * @param radius 过渡圆弧半径
 * @return TopoDS_Wire 生成的截面轮廓线
 */
TopoDS_Wire create_ibeam_profile(double height, double flangeWidth,
                                 double webThickness, double flangeThickness,
                                 double radius) {
  BRepBuilderAPI_MakeWire wireMaker;

  // 计算关键尺寸
  double halfHeight = height / 2;
  double halfFlangeWidth = flangeWidth / 2;
  double halfWebThickness = webThickness / 2;

  // 外轮廓关键点（右侧）
  gp_Pnt p1(-halfFlangeWidth, -halfHeight, 0);
  gp_Pnt p2(halfFlangeWidth, -halfHeight, 0);
  gp_Pnt p3(halfFlangeWidth, -halfHeight + flangeThickness - radius, 0);
  gp_Pnt p4(halfFlangeWidth, -halfHeight + flangeThickness, 0);
  gp_Pnt p5(halfWebThickness + radius, -halfHeight + flangeThickness, 0);
  gp_Pnt p6(halfWebThickness, -halfHeight + flangeThickness + radius, 0);
  gp_Pnt p7(halfWebThickness, halfHeight - flangeThickness - radius, 0);
  gp_Pnt p8(halfWebThickness + radius, halfHeight - flangeThickness, 0);
  gp_Pnt p9(halfFlangeWidth, halfHeight - flangeThickness, 0);
  gp_Pnt p10(halfFlangeWidth, halfHeight - flangeThickness + radius, 0);
  gp_Pnt p11(halfFlangeWidth, halfHeight, 0);
  gp_Pnt p12(-halfFlangeWidth, halfHeight, 0);

  // 左侧对称点
  gp_Pnt p13(-halfFlangeWidth, halfHeight - flangeThickness + radius, 0);
  gp_Pnt p14(-halfFlangeWidth, halfHeight - flangeThickness, 0);
  gp_Pnt p15(-halfWebThickness - radius, halfHeight - flangeThickness, 0);
  gp_Pnt p16(-halfWebThickness, halfHeight - flangeThickness - radius, 0);
  gp_Pnt p17(-halfWebThickness, -halfHeight + flangeThickness + radius, 0);
  gp_Pnt p18(-halfWebThickness - radius, -halfHeight + flangeThickness, 0);
  gp_Pnt p19(-halfFlangeWidth, -halfHeight + flangeThickness, 0);
  gp_Pnt p20(-halfFlangeWidth, -halfHeight + flangeThickness - radius, 0);

  // 创建所有直线段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge()); // 下翼缘底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge()); // 右下翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p9, p10).Edge()); // 右上翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p11, p12).Edge()); // 上翼缘顶部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p14, p15).Edge()); // 左上翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p19, p20).Edge()); // 左下翼缘垂直段

  // 创建所有圆弧过渡
  if (radius < flangeThickness / 3) { // 小半径过渡（轻型工字钢）
    // 右下翼缘圆弧
    gp_Circ arc1(gp_Ax2(p4, gp_Dir(0, 0, 1)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc1, p4, p5).Edge());

    // 右下腹板圆弧
    gp_Circ arc2(gp_Ax2(p6, gp_Dir(0, 0, 1)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc2, p6, p7).Edge());

    // 右上腹板圆弧
    gp_Circ arc3(gp_Ax2(p8, gp_Dir(0, 0, 1)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc3, p8, p9).Edge());

    // 右上翼缘圆弧
    gp_Circ arc4(gp_Ax2(p10, gp_Dir(0, 0, 1)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc4, p10, p11).Edge());

    // 左上翼缘圆弧
    gp_Circ arc5(gp_Ax2(p13, gp_Dir(0, 0, 1)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc5, p13, p14).Edge());

    // 左上腹板圆弧
    gp_Circ arc6(gp_Ax2(p15, gp_Dir(0, 0, 1)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc6, p15, p16).Edge());

    // 左下腹板圆弧
    gp_Circ arc7(gp_Ax2(p17, gp_Dir(0, 0, 1)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc7, p17, p18).Edge());

    // 左下翼缘圆弧
    gp_Circ arc8(gp_Ax2(p19, gp_Dir(0, 0, 1)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc8, p19, p20).Edge());
  } else { // 大半径过渡（普通工字钢）
    // 右下翼缘圆弧
    gp_Circ arc1(gp_Ax2(p4, gp_Dir(0, 0, 1)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc1, p4, p5).Edge());

    // 右上翼缘圆弧
    gp_Circ arc2(gp_Ax2(p10, gp_Dir(0, 0, 1)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc2, p10, p11).Edge());

    // 左上翼缘圆弧
    gp_Circ arc3(gp_Ax2(p13, gp_Dir(0, 0, 1)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc3, p13, p14).Edge());

    // 左下翼缘圆弧
    gp_Circ arc4(gp_Ax2(p19, gp_Dir(0, 0, 1)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc4, p19, p20).Edge());
  }

  // 创建腹板水平段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p5, p18).Edge()); // 下腹板
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, p15).Edge()); // 上腹板

  // 创建腹板垂直段（仅普通工字钢需要）
  if (radius >= flangeThickness / 3) {
    wireMaker.Add(BRepBuilderAPI_MakeEdge(p6, p17).Edge()); // 右腹板
    wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p16).Edge()); // 左腹板
  }

  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create I-beam profile");
  }
  return wireMaker.Wire();
}

/**
 * @brief 创建工字钢图元
 *
 * @param model 型号
 * (如"I200X100X6X9"表示高度200mm，翼缘宽度100mm，腹板厚度6mm，翼缘厚度9mm)
 * @param length 长度 (Length > 0)
 * @return TopoDS_Shape 生成的工字钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_ibeam(const std::string &model, double length) {
  // 参数验证
  if (length <= 0.0) {
    throw Standard_ConstructionError("Length must be positive");
  }
  if (model.empty() || model[0] != 'I') {
    throw Standard_ConstructionError("Invalid model format");
  }

  // 解析型号参数
  size_t x1Pos = model.find('X');
  size_t x2Pos = model.find('X', x1Pos + 1);
  size_t x3Pos = model.find('X', x2Pos + 1);
  if (x1Pos == std::string::npos || x2Pos == std::string::npos ||
      x3Pos == std::string::npos) {
    throw Standard_ConstructionError("Invalid model format");
  }

  double height = std::stod(model.substr(1, x1Pos - 1));
  double flangeWidth = std::stod(model.substr(x1Pos + 1, x2Pos - x1Pos - 1));
  double webThickness = std::stod(model.substr(x2Pos + 1, x3Pos - x2Pos - 1));
  double flangeThickness = std::stod(model.substr(x3Pos + 1));

  if (height <= 0.0 || flangeWidth <= 0.0 || webThickness <= 0.0 ||
      flangeThickness <= 0.0) {
    throw Standard_ConstructionError("Dimensions must be positive");
  }
  if (webThickness >= flangeWidth) {
    throw Standard_ConstructionError(
        "Web thickness must be less than flange width");
  }

  // 根据工字钢类型确定过渡圆弧半径
  double radius;
  if (model[0] == 'I') {                   // 普通工字钢
    radius = flangeThickness * 0.8;        // 大半径过渡
  } else if (model.substr(0, 2) == "IL") { // 轻型工字钢
    radius = flangeThickness * 0.3;        // 小半径过渡
  }

  // 创建带圆弧过渡的截面
  TopoDS_Wire profileWire = create_ibeam_profile(
      height, flangeWidth, webThickness, flangeThickness, radius);

  // 创建截面面
  BRepBuilderAPI_MakeFace faceMaker(profileWire);
  if (!faceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create I-beam face");
  }

  // 沿Z轴拉伸创建工字钢
  gp_Vec direction(0, 0, length);
  BRepPrimAPI_MakePrism prismMaker(faceMaker.Face(), direction);

  if (!prismMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to extrude I-beam");
  }

  return prismMaker.Shape();
}

/**
 * @brief 创建带定位的工字钢
 *
 * @param model 型号
 * @param length 长度
 * @param position 底面中心点位置
 * @param direction 长度方向（默认Z轴）
 * @param xDir 翼缘宽度方向（默认X轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_ibeam(const std::string &model, double length,
                          const gp_Pnt &position,
                          const gp_Dir &direction = gp_Dir(0, 0, 1),
                          const gp_Dir &xDir = gp_Dir(1, 0, 0)) {
  // 首先创建标准方向的工字钢
  TopoDS_Shape ibeam = create_ibeam(model, length);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  gp_Dir yDir = direction.Crossed(xDir);
  gp_Ax3 targetAx3(position, direction, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(ibeam, transformation);
  return transform.Shape();
}

/**
 * @brief 创建轻型工字钢图元
 *
 * @param model 型号
 * (如"IL200X100X5X8"表示高度200mm，翼缘宽度100mm，腹板厚度5mm，翼缘厚度8mm)
 * @param length 长度 (Length > 0)
 * @return TopoDS_Shape 生成的轻型工字钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_light_ibeam(const std::string &model, double length) {
  // 参数验证
  if (length <= 0.0) {
    throw Standard_ConstructionError("Length must be positive");
  }
  if (model.empty() || model.substr(0, 2) != "IL") {
    throw Standard_ConstructionError("Invalid model format");
  }

  // 解析型号参数
  size_t x1Pos = model.find('X');
  size_t x2Pos = model.find('X', x1Pos + 1);
  size_t x3Pos = model.find('X', x2Pos + 1);
  if (x1Pos == std::string::npos || x2Pos == std::string::npos ||
      x3Pos == std::string::npos) {
    throw Standard_ConstructionError("Invalid model format");
  }

  double height = std::stod(model.substr(2, x1Pos - 2));
  double flangeWidth = std::stod(model.substr(x1Pos + 1, x2Pos - x1Pos - 1));
  double webThickness = std::stod(model.substr(x2Pos + 1, x3Pos - x2Pos - 1));
  double flangeThickness = std::stod(model.substr(x3Pos + 1));

  if (height <= 0.0 || flangeWidth <= 0.0 || webThickness <= 0.0 ||
      flangeThickness <= 0.0) {
    throw Standard_ConstructionError("Dimensions must be positive");
  }
  if (webThickness >= flangeWidth * 0.3) { // 腹板厚度不超过翼缘宽度的30%
    throw Standard_ConstructionError(
        "Web thickness too large for light I-beam");
  }
  if (flangeThickness >= height * 0.1) { // 翼缘厚度不超过高度的10%
    throw Standard_ConstructionError(
        "Flange thickness too large for light I-beam");
  }

  // 使用圆弧过渡函数创建截面，设置小半径过渡
  double radius = flangeThickness * 0.3; // 轻型工字钢使用小半径过渡
  TopoDS_Wire profileWire = create_ibeam_profile(
      height, flangeWidth, webThickness, flangeThickness, radius);

  // 创建截面面
  BRepBuilderAPI_MakeFace faceMaker(profileWire);
  if (!faceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create light I-beam face");
  }

  // 沿Z轴拉伸创建轻型工字钢
  gp_Vec direction(0, 0, length);
  BRepPrimAPI_MakePrism prismMaker(faceMaker.Face(), direction);

  if (!prismMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to extrude light I-beam");
  }

  return prismMaker.Shape();
}

/**
 * @brief 创建带定位的轻型工字钢
 *
 * @param model 型号
 * @param length 长度
 * @param position 底面中心点位置
 * @param direction 长度方向（默认Z轴）
 * @param xDir 翼缘宽度方向（默认X轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_light_ibeam(const std::string &model, double length,
                                const gp_Pnt &position,
                                const gp_Dir &direction = gp_Dir(0, 0, 1),
                                const gp_Dir &xDir = gp_Dir(1, 0, 0)) {
  // 首先创建标准方向的轻型工字钢
  TopoDS_Shape lightIbeam = create_light_ibeam(model, length);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  gp_Dir yDir = direction.Crossed(xDir);
  gp_Ax3 targetAx3(position, direction, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(lightIbeam, transformation);
  return transform.Shape();
}

/**
 * @brief 创建H型钢截面轮廓
 * @param height 总高度
 * @param flangeWidth 翼缘宽度
 * @param webThickness 腹板厚度
 * @param flangeThickness 翼缘厚度
 * @param radius 过渡圆弧半径
 * @return TopoDS_Wire 生成的截面轮廓线
 */
TopoDS_Wire create_hbeam_profile(double height, double flangeWidth,
                                 double webThickness, double flangeThickness,
                                 double radius) {
  BRepBuilderAPI_MakeWire wireMaker;

  // 计算关键尺寸
  double halfHeight = height / 2;
  double halfFlangeWidth = flangeWidth / 2;
  double halfWebThickness = webThickness / 2;

  // 外轮廓关键点（右侧）
  gp_Pnt p1(-halfFlangeWidth, -halfHeight, 0);
  gp_Pnt p2(halfFlangeWidth, -halfHeight, 0);
  gp_Pnt p3(halfFlangeWidth, -halfHeight + flangeThickness, 0);
  gp_Pnt p4(halfWebThickness, -halfHeight + flangeThickness, 0);
  gp_Pnt p5(halfWebThickness, halfHeight - flangeThickness, 0);
  gp_Pnt p6(halfFlangeWidth, halfHeight - flangeThickness, 0);
  gp_Pnt p7(halfFlangeWidth, halfHeight, 0);
  gp_Pnt p8(-halfFlangeWidth, halfHeight, 0);
  gp_Pnt p9(-halfFlangeWidth, halfHeight - flangeThickness, 0);
  gp_Pnt p10(-halfWebThickness, halfHeight - flangeThickness, 0);
  gp_Pnt p11(-halfWebThickness, -halfHeight + flangeThickness, 0);
  gp_Pnt p12(-halfFlangeWidth, -halfHeight + flangeThickness, 0);

  // 创建外轮廓线（H型钢无圆弧过渡）
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p6, p7).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, p9).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p9, p10).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p10, p11).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p11, p12).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p12, p1).Edge());

  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create H-beam profile");
  }
  return wireMaker.Wire();
}

/**
 * @brief 创建H型钢图元
 * @param model 型号
 * (如"H200X100X6X9"表示高度200mm，翼缘宽度100mm，腹板厚度6mm，翼缘厚度9mm)
 * @param length 长度 (Length > 0)
 * @return TopoDS_Shape 生成的H型钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_hbeam(const std::string &model, double length) {
  // 参数验证
  if (length <= 0.0) {
    throw Standard_ConstructionError("Length must be positive");
  }
  if (model.empty() || model[0] != 'H') {
    throw Standard_ConstructionError("Invalid model format");
  }

  // 解析型号参数
  size_t x1Pos = model.find('X');
  size_t x2Pos = model.find('X', x1Pos + 1);
  size_t x3Pos = model.find('X', x2Pos + 1);
  if (x1Pos == std::string::npos || x2Pos == std::string::npos ||
      x3Pos == std::string::npos) {
    throw Standard_ConstructionError("Invalid model format");
  }

  double height = std::stod(model.substr(1, x1Pos - 1));
  double flangeWidth = std::stod(model.substr(x1Pos + 1, x2Pos - x1Pos - 1));
  double webThickness = std::stod(model.substr(x2Pos + 1, x3Pos - x2Pos - 1));
  double flangeThickness = std::stod(model.substr(x3Pos + 1));

  if (height <= 0.0 || flangeWidth <= 0.0 || webThickness <= 0.0 ||
      flangeThickness <= 0.0) {
    throw Standard_ConstructionError("Dimensions must be positive");
  }

  // 创建H型钢截面轮廓（H型钢无圆弧过渡，radius设为0）
  TopoDS_Wire profileWire = create_hbeam_profile(
      height, flangeWidth, webThickness, flangeThickness, 0.0);

  // 创建截面面
  BRepBuilderAPI_MakeFace faceMaker(profileWire);
  if (!faceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create H-beam face");
  }

  // 沿Z轴拉伸创建H型钢
  gp_Vec direction(0, 0, length);
  BRepPrimAPI_MakePrism prismMaker(faceMaker.Face(), direction);

  if (!prismMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to extrude H-beam");
  }

  return prismMaker.Shape();
}

/**
 * @brief 创建带定位的H型钢
 * @param model 型号
 * @param length 长度
 * @param position 底面中心点位置
 * @param direction 长度方向（默认Z轴）
 * @param xDir 翼缘宽度方向（默认X轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_hbeam(const std::string &model, double length,
                          const gp_Pnt &position,
                          const gp_Dir &direction = gp_Dir(0, 0, 1),
                          const gp_Dir &xDir = gp_Dir(1, 0, 0)) {
  // 首先创建标准方向的H型钢
  TopoDS_Shape hbeam = create_hbeam(model, length);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  gp_Dir yDir = direction.Crossed(xDir);
  gp_Ax3 targetAx3(position, direction, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(hbeam, transformation);
  return transform.Shape();
}

/**
 * @brief 创建槽钢截面轮廓
 * @param height 总高度
 * @param flangeWidth 翼缘宽度
 * @param webThickness 腹板厚度
 * @param flangeThickness 翼缘厚度
 * @param radius 过渡圆弧半径
 * @return TopoDS_Wire 生成的截面轮廓线
 */
TopoDS_Wire create_channel_profile(double height, double flangeWidth,
                                   double webThickness, double flangeThickness,
                                   double radius) {
  BRepBuilderAPI_MakeWire wireMaker;

  // 计算关键尺寸
  double halfHeight = height / 2;
  double halfFlangeWidth = flangeWidth / 2;
  double halfWebThickness = webThickness / 2;

  // 外轮廓关键点（从左上角开始顺时针）
  gp_Pnt p1(-halfFlangeWidth, halfHeight, 0);
  gp_Pnt p2(halfFlangeWidth, halfHeight, 0);
  gp_Pnt p3(halfFlangeWidth, halfHeight - flangeThickness + radius, 0);
  gp_Pnt p4(halfFlangeWidth, halfHeight - flangeThickness, 0);
  gp_Pnt p5(halfWebThickness, halfHeight - flangeThickness, 0);
  gp_Pnt p6(halfWebThickness, -halfHeight + flangeThickness, 0);
  gp_Pnt p7(halfFlangeWidth, -halfHeight + flangeThickness, 0);
  gp_Pnt p8(halfFlangeWidth, -halfHeight + flangeThickness - radius, 0);
  gp_Pnt p9(halfFlangeWidth, -halfHeight, 0);
  gp_Pnt p10(-halfFlangeWidth, -halfHeight, 0);

  // 创建直线段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());  // 上翼缘顶部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge());  // 上翼缘底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge());  // 腹板右侧
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p6, p7).Edge());  // 下翼缘顶部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p9, p10).Edge()); // 下翼缘底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p10, p1).Edge()); // 腹板左侧

  // 创建圆弧过渡
  if (radius > Precision::Confusion()) {
    // 上翼缘圆弧
    gp_Circ arc1(gp_Ax2(p3, gp_Dir(0, 0, 1)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc1, p3, p4).Edge());

    // 下翼缘圆弧
    gp_Circ arc2(gp_Ax2(p8, gp_Dir(0, 0, 1)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc2, p8, p7).Edge());
  }

  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create channel profile");
  }
  return wireMaker.Wire();
}

/**
 * @brief 创建槽钢图元
 * @param model 型号
 * (如"C200X75X6X9"表示高度200mm，翼缘宽度75mm，腹板厚度6mm，翼缘厚度9mm)
 * @param length 长度 (Length > 0)
 * @return TopoDS_Shape 生成的槽钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_beam_channel(const std::string &model, double length) {
  // 参数验证
  if (length <= 0.0) {
    throw Standard_ConstructionError("Length must be positive");
  }
  if (model.empty() || model[0] != 'C') {
    throw Standard_ConstructionError("Invalid model format");
  }

  // 解析型号参数
  size_t x1Pos = model.find('X');
  size_t x2Pos = model.find('X', x1Pos + 1);
  size_t x3Pos = model.find('X', x2Pos + 1);
  if (x1Pos == std::string::npos || x2Pos == std::string::npos ||
      x3Pos == std::string::npos) {
    throw Standard_ConstructionError("Invalid model format");
  }

  double height = std::stod(model.substr(1, x1Pos - 1));
  double flangeWidth = std::stod(model.substr(x1Pos + 1, x2Pos - x1Pos - 1));
  double webThickness = std::stod(model.substr(x2Pos + 1, x3Pos - x2Pos - 1));
  double flangeThickness = std::stod(model.substr(x3Pos + 1));

  if (height <= 0.0 || flangeWidth <= 0.0 || webThickness <= 0.0 ||
      flangeThickness <= 0.0) {
    throw Standard_ConstructionError("Dimensions must be positive");
  }

  // 设置过渡圆弧半径（通常为翼缘厚度的0.5倍）
  double radius = flangeThickness * 0.5;

  // 创建槽钢截面轮廓
  TopoDS_Wire profileWire = create_channel_profile(
      height, flangeWidth, webThickness, flangeThickness, radius);

  // 创建截面面
  BRepBuilderAPI_MakeFace faceMaker(profileWire);
  if (!faceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create channel face");
  }

  // 沿Z轴拉伸创建槽钢
  gp_Vec direction(0, 0, length);
  BRepPrimAPI_MakePrism prismMaker(faceMaker.Face(), direction);

  if (!prismMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to extrude channel");
  }

  return prismMaker.Shape();
}

/**
 * @brief 创建带定位的槽钢
 * @param model 型号
 * @param length 长度
 * @param position 底面中心点位置
 * @param direction 长度方向（默认Z轴）
 * @param xDir 开口方向（默认X轴正方向）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_beam_channel(const std::string &model, double length,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction = gp_Dir(0, 0, 1),
                                 const gp_Dir &xDir = gp_Dir(1, 0, 0)) {
  // 首先创建标准方向的槽钢
  TopoDS_Shape channel = create_beam_channel(model, length);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  gp_Dir yDir = direction.Crossed(xDir);
  gp_Ax3 targetAx3(position, direction, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(channel, transformation);
  return transform.Shape();
}

/**
 * @brief 创建轻型槽钢截面轮廓
 * @param height 总高度
 * @param flangeWidth 翼缘宽度
 * @param webThickness 腹板厚度
 * @param flangeThickness 翼缘厚度
 * @param radius 过渡圆弧半径
 * @return TopoDS_Wire 生成的截面轮廓线
 */
TopoDS_Wire create_light_channel_profile(double height, double flangeWidth,
                                         double webThickness,
                                         double flangeThickness,
                                         double radius) {
  BRepBuilderAPI_MakeWire wireMaker;

  // 计算关键尺寸
  double halfHeight = height / 2;
  double halfFlangeWidth = flangeWidth / 2;
  double halfWebThickness = webThickness / 2;

  // 外轮廓关键点（从左上角开始顺时针）
  gp_Pnt p1(-halfFlangeWidth, halfHeight, 0);
  gp_Pnt p2(halfFlangeWidth, halfHeight, 0);
  gp_Pnt p3(halfFlangeWidth, halfHeight - flangeThickness + radius, 0);
  gp_Pnt p4(halfFlangeWidth, halfHeight - flangeThickness, 0);
  gp_Pnt p5(halfWebThickness, halfHeight - flangeThickness, 0);
  gp_Pnt p6(halfWebThickness, -halfHeight + flangeThickness, 0);
  gp_Pnt p7(halfFlangeWidth, -halfHeight + flangeThickness, 0);
  gp_Pnt p8(halfFlangeWidth, -halfHeight + flangeThickness - radius, 0);
  gp_Pnt p9(halfFlangeWidth, -halfHeight, 0);
  gp_Pnt p10(-halfFlangeWidth, -halfHeight, 0);

  // 创建直线段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());  // 上翼缘顶部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge());  // 上翼缘底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge());  // 腹板右侧
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p6, p7).Edge());  // 下翼缘顶部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p9, p10).Edge()); // 下翼缘底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p10, p1).Edge()); // 腹板左侧

  // 创建小半径圆弧过渡（轻型槽钢）
  if (radius > Precision::Confusion()) {
    // 上翼缘圆弧
    gp_Circ arc1(gp_Ax2(p3, gp_Dir(0, 0, 1)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc1, p3, p4).Edge());

    // 下翼缘圆弧
    gp_Circ arc2(gp_Ax2(p8, gp_Dir(0, 0, 1)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc2, p8, p7).Edge());
  }

  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create light channel profile");
  }
  return wireMaker.Wire();
}

/**
 * @brief 创建轻型槽钢图元
 * @param model 型号
 * (如"LC200X75X4X6"表示高度200mm，翼缘宽度75mm，腹板厚度4mm，翼缘厚度6mm)
 * @param length 长度 (Length > 0)
 * @return TopoDS_Shape 生成的轻型槽钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_light_beam_channel(const std::string &model,
                                       double length) {
  // 参数验证
  if (length <= 0.0) {
    throw Standard_ConstructionError("Length must be positive");
  }
  if (model.empty() || model.substr(0, 2) != "LC") {
    throw Standard_ConstructionError("Invalid model format");
  }

  // 解析型号参数
  size_t x1Pos = model.find('X');
  size_t x2Pos = model.find('X', x1Pos + 1);
  size_t x3Pos = model.find('X', x2Pos + 1);
  if (x1Pos == std::string::npos || x2Pos == std::string::npos ||
      x3Pos == std::string::npos) {
    throw Standard_ConstructionError("Invalid model format");
  }

  double height = std::stod(model.substr(2, x1Pos - 2));
  double flangeWidth = std::stod(model.substr(x1Pos + 1, x2Pos - x1Pos - 1));
  double webThickness = std::stod(model.substr(x2Pos + 1, x3Pos - x2Pos - 1));
  double flangeThickness = std::stod(model.substr(x3Pos + 1));

  // 轻型槽钢特有参数验证
  if (height <= 0.0 || flangeWidth <= 0.0 || webThickness <= 0.0 ||
      flangeThickness <= 0.0) {
    throw Standard_ConstructionError("Dimensions must be positive");
  }
  if (webThickness >= flangeWidth * 0.3) { // 腹板厚度不超过翼缘宽度的30%
    throw Standard_ConstructionError(
        "Web thickness too large for light channel");
  }
  if (flangeThickness >= height * 0.1) { // 翼缘厚度不超过高度的10%
    throw Standard_ConstructionError(
        "Flange thickness too large for light channel");
  }

  // 设置小半径过渡（翼缘厚度的0.3倍）
  double radius = flangeThickness * 0.3;

  // 创建轻型槽钢截面轮廓
  TopoDS_Wire profileWire = create_light_channel_profile(
      height, flangeWidth, webThickness, flangeThickness, radius);

  // 创建截面面
  BRepBuilderAPI_MakeFace faceMaker(profileWire);
  if (!faceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create light channel face");
  }

  // 沿Z轴拉伸创建轻型槽钢
  gp_Vec direction(0, 0, length);
  BRepPrimAPI_MakePrism prismMaker(faceMaker.Face(), direction);

  if (!prismMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to extrude light channel");
  }

  return prismMaker.Shape();
}

/**
 * @brief 创建带定位的轻型槽钢
 * @param model 型号
 * @param length 长度
 * @param position 底面中心点位置
 * @param direction 长度方向（默认Z轴）
 * @param xDir 开口方向（默认X轴正方向）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_light_beam_channel(const std::string &model, double length,
                                       const gp_Pnt &position,
                                       const gp_Dir &direction = gp_Dir(0, 0,
                                                                        1),
                                       const gp_Dir &xDir = gp_Dir(1, 0, 0)) {
  // 首先创建标准方向的轻型槽钢
  TopoDS_Shape lightChannel = create_light_beam_channel(model, length);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  gp_Dir yDir = direction.Crossed(xDir);
  gp_Ax3 targetAx3(position, direction, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(lightChannel, transformation);
  return transform.Shape();
}

/**
 * @brief 创建扁钢图元
 * @param model 型号 (如"F50X4"表示宽度50mm，厚度4mm)
 * @param length 长度 (Length > 0)
 * @return TopoDS_Shape 生成的扁钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_flat_steel(const std::string &model, double length) {
  // 参数验证
  if (length <= 0.0) {
    throw Standard_ConstructionError("Length must be positive");
  }
  if (model.empty() || model[0] != 'F') {
    throw Standard_ConstructionError("Invalid model format");
  }

  // 解析型号参数
  size_t xPos = model.find('X');
  if (xPos == std::string::npos) {
    throw Standard_ConstructionError("Invalid model format");
  }

  double width = std::stod(model.substr(1, xPos - 1));
  double thickness = std::stod(model.substr(xPos + 1));

  if (width <= 0.0 || thickness <= 0.0) {
    throw Standard_ConstructionError("Width and thickness must be positive");
  }

  // 创建扁钢截面轮廓
  BRepBuilderAPI_MakeWire wireMaker;

  // 计算关键尺寸
  double halfWidth = width / 2;
  double halfThickness = thickness / 2;

  // 外轮廓点
  gp_Pnt p1(-halfWidth, -halfThickness, 0);
  gp_Pnt p2(halfWidth, -halfThickness, 0);
  gp_Pnt p3(halfWidth, halfThickness, 0);
  gp_Pnt p4(-halfWidth, halfThickness, 0);

  // 创建外轮廓线
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p1).Edge());

  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create flat steel profile");
  }
  TopoDS_Wire profileWire = wireMaker.Wire();

  // 创建截面面
  BRepBuilderAPI_MakeFace faceMaker(profileWire);
  if (!faceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create flat steel face");
  }

  // 沿Z轴拉伸创建扁钢
  gp_Vec direction(0, 0, length);
  BRepPrimAPI_MakePrism prismMaker(faceMaker.Face(), direction);

  if (!prismMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to extrude flat steel");
  }

  return prismMaker.Shape();
}

/**
 * @brief 创建带定位的扁钢
 * @param model 型号
 * @param length 长度
 * @param position 底面中心点位置
 * @param direction 长度方向（默认Z轴）
 * @param widthDir 宽度方向（默认X轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_flat_steel(const std::string &model, double length,
                               const gp_Pnt &position,
                               const gp_Dir &direction = gp_Dir(0, 0, 1),
                               const gp_Dir &widthDir = gp_Dir(1, 0, 0)) {
  // 首先创建标准方向的扁钢
  TopoDS_Shape flatSteel = create_flat_steel(model, length);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  gp_Dir thicknessDir = direction.Crossed(widthDir);
  gp_Ax3 targetAx3(position, direction, widthDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(flatSteel, transformation);
  return transform.Shape();
}

/**
 * @brief 创建L型钢截面轮廓
 * @param longSide 长边长度
 * @param shortSide 短边长度
 * @param thickness 厚度
 * @param radius 过渡圆弧半径
 * @return TopoDS_Wire 生成的截面轮廓线
 */
TopoDS_Wire create_lsteel_profile(double longSide, double shortSide,
                                  double thickness, double radius) {
  BRepBuilderAPI_MakeWire wireMaker;

  // 外轮廓关键点
  gp_Pnt p1(0, 0, 0);
  gp_Pnt p2(longSide, 0, 0);
  gp_Pnt p3(longSide, thickness, 0);
  gp_Pnt p4(thickness, thickness, 0);
  gp_Pnt p5(thickness, shortSide, 0);
  gp_Pnt p6(0, shortSide, 0);

  // 创建外轮廓线
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p6, p1).Edge());

  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create L-steel profile");
  }
  return wireMaker.Wire();
}

/**
 * @brief 创建L型钢图元
 * @param model 型号 (如"L50X4"表示边宽50mm，厚度4mm)
 * @param length 长度 (Length > 0)
 * @return TopoDS_Shape 生成的L型钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_lsteel(const std::string &model, double length) {
  // 参数验证
  if (length <= 0.0) {
    throw Standard_ConstructionError("Length must be positive");
  }
  if (model.empty() || model[0] != 'L') {
    throw Standard_ConstructionError("Invalid model format");
  }

  // 解析型号参数
  size_t xPos = model.find('X');
  if (xPos == std::string::npos) {
    throw Standard_ConstructionError("Invalid model format");
  }

  double side = std::stod(model.substr(1, xPos - 1));
  double thickness = std::stod(model.substr(xPos + 1));

  if (side <= 0.0 || thickness <= 0.0) {
    throw Standard_ConstructionError("Side and thickness must be positive");
  }
  if (thickness >= side) {
    throw Standard_ConstructionError("Thickness must be less than side length");
  }

  // 创建L型钢截面轮廓（等边角钢）
  TopoDS_Wire profileWire = create_lsteel_profile(side, side, thickness, 0.0);

  // 创建截面面
  BRepBuilderAPI_MakeFace faceMaker(profileWire);
  if (!faceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create L-steel face");
  }

  // 沿Z轴拉伸创建L型钢
  gp_Vec direction(0, 0, length);
  BRepPrimAPI_MakePrism prismMaker(faceMaker.Face(), direction);

  if (!prismMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to extrude L-steel");
  }

  return prismMaker.Shape();
}

/**
 * @brief 创建带定位的L型钢
 * @param model 型号
 * @param length 长度
 * @param position 底面中心点位置
 * @param direction 长度方向（默认Z轴）
 * @param xDir 长边方向（默认X轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_lsteel(const std::string &model, double length,
                           const gp_Pnt &position,
                           const gp_Dir &direction = gp_Dir(0, 0, 1),
                           const gp_Dir &xDir = gp_Dir(1, 0, 0)) {
  // 首先创建标准方向的L型钢
  TopoDS_Shape lsteel = create_lsteel(model, length);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  gp_Dir yDir = direction.Crossed(xDir);
  gp_Ax3 targetAx3(position, direction, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(lsteel, transformation);
  return transform.Shape();
}

/**
 * @brief 创建T型钢截面轮廓
 * @param height 总高度
 * @param flangeWidth 翼缘宽度
 * @param webThickness 腹板厚度
 * @param flangeThickness 翼缘厚度
 * @return TopoDS_Wire 生成的截面轮廓线
 */
TopoDS_Wire create_tsteel_profile(double height, double flangeWidth,
                                  double webThickness, double flangeThickness) {
  BRepBuilderAPI_MakeWire wireMaker;

  // 计算关键尺寸
  double halfFlangeWidth = flangeWidth / 2;
  double halfWebThickness = webThickness / 2;

  // 外轮廓关键点（从左上角开始顺时针）
  gp_Pnt p1(-halfFlangeWidth, 0, 0);
  gp_Pnt p2(halfFlangeWidth, 0, 0);
  gp_Pnt p3(halfFlangeWidth, -flangeThickness, 0);
  gp_Pnt p4(halfWebThickness, -flangeThickness, 0);
  gp_Pnt p5(halfWebThickness, -height, 0);
  gp_Pnt p6(-halfWebThickness, -height, 0);
  gp_Pnt p7(-halfWebThickness, -flangeThickness, 0);
  gp_Pnt p8(-halfFlangeWidth, -flangeThickness, 0);

  // 创建外轮廓线
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge()); // 上翼缘顶部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge()); // 右上翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge()); // 右腹板水平段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge()); // 右腹板垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge()); // 下腹板水平段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p6, p7).Edge()); // 左腹板垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8).Edge()); // 左腹板水平段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, p1).Edge()); // 左上翼缘垂直段

  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create T-steel profile");
  }
  return wireMaker.Wire();
}

/**
 * @brief 创建T型钢图元
 * @param model 型号
 * (如"T100X50X6X8"表示高度100mm，翼缘宽度50mm，腹板厚度6mm，翼缘厚度8mm)
 * @param length 长度 (Length > 0)
 * @return TopoDS_Shape 生成的T型钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_tsteel(const std::string &model, double length) {
  // 参数验证
  if (length <= 0.0) {
    throw Standard_ConstructionError("Length must be positive");
  }
  if (model.empty() || model[0] != 'T') {
    throw Standard_ConstructionError("Invalid model format");
  }

  // 解析型号参数
  size_t x1Pos = model.find('X');
  size_t x2Pos = model.find('X', x1Pos + 1);
  size_t x3Pos = model.find('X', x2Pos + 1);
  if (x1Pos == std::string::npos || x2Pos == std::string::npos ||
      x3Pos == std::string::npos) {
    throw Standard_ConstructionError("Invalid model format");
  }

  double height = std::stod(model.substr(1, x1Pos - 1));
  double flangeWidth = std::stod(model.substr(x1Pos + 1, x2Pos - x1Pos - 1));
  double webThickness = std::stod(model.substr(x2Pos + 1, x3Pos - x2Pos - 1));
  double flangeThickness = std::stod(model.substr(x3Pos + 1));

  if (height <= 0.0 || flangeWidth <= 0.0 || webThickness <= 0.0 ||
      flangeThickness <= 0.0) {
    throw Standard_ConstructionError("Dimensions must be positive");
  }
  if (webThickness >= flangeWidth) {
    throw Standard_ConstructionError(
        "Web thickness must be less than flange width");
  }

  // 创建T型钢截面轮廓
  TopoDS_Wire profileWire =
      create_tsteel_profile(height, flangeWidth, webThickness, flangeThickness);

  // 创建截面面
  BRepBuilderAPI_MakeFace faceMaker(profileWire);
  if (!faceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create T-steel face");
  }

  // 沿Z轴拉伸创建T型钢
  gp_Vec direction(0, 0, length);
  BRepPrimAPI_MakePrism prismMaker(faceMaker.Face(), direction);

  if (!prismMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to extrude T-steel");
  }

  return prismMaker.Shape();
}

/**
 * @brief 创建带定位的T型钢
 * @param model 型号
 * @param length 长度
 * @param position 底面中心点位置
 * @param direction 长度方向（默认Z轴）
 * @param xDir 翼缘宽度方向（默认X轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_tsteel(const std::string &model, double length,
                           const gp_Pnt &position,
                           const gp_Dir &direction = gp_Dir(0, 0, 1),
                           const gp_Dir &xDir = gp_Dir(1, 0, 0)) {
  // 首先创建标准方向的T型钢
  TopoDS_Shape tsteel = create_tsteel(model, length);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  gp_Dir yDir = direction.Crossed(xDir);
  gp_Ax3 targetAx3(position, direction, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(tsteel, transformation);
  return transform.Shape();
}

/**
 * @brief 创建圆钢图元
 * @param model 型号 (如"R20"表示直径20mm)
 * @param length 长度 (Length > 0)
 * @return TopoDS_Shape 生成的圆钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_round_steel(const std::string &model, double length) {
  // 参数验证
  if (length <= 0.0) {
    throw Standard_ConstructionError("Length must be positive");
  }
  if (model.empty() || model[0] != 'R') {
    throw Standard_ConstructionError("Invalid model format");
  }

  // 解析型号参数
  double diameter = std::stod(model.substr(1));
  if (diameter <= 0.0) {
    throw Standard_ConstructionError("Diameter must be positive");
  }

  // 创建圆钢截面
  gp_Ax2 axis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  BRepPrimAPI_MakeCylinder cylinderMaker(axis, diameter / 2, length);

  if (!cylinderMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create round steel");
  }

  return cylinderMaker.Shape();
}

/**
 * @brief 创建带定位的圆钢
 * @param model 型号
 * @param length 长度
 * @param position 底面中心点位置
 * @param direction 长度方向（默认Z轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_round_steel(const std::string &model, double length,
                                const gp_Pnt &position,
                                const gp_Dir &direction = gp_Dir(0, 0, 1)) {
  // 首先创建标准方向的圆钢
  TopoDS_Shape roundSteel = create_round_steel(model, length);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(position, direction);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(roundSteel, transformation);
  return transform.Shape();
}

/**
 * @brief 创建圆钢管图元
 * @param model 型号 (如"RT50X4"表示外径50mm，壁厚4mm)
 * @param length 长度 (Length > 0)
 * @return TopoDS_Shape 生成的圆钢管形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_round_steel_tube(const std::string &model, double length) {
  // 参数验证
  if (length <= 0.0) {
    throw Standard_ConstructionError("Length must be positive");
  }
  if (model.empty() || model.substr(0, 2) != "RT") {
    throw Standard_ConstructionError("Invalid model format");
  }

  // 解析型号参数
  size_t xPos = model.find('X');
  if (xPos == std::string::npos) {
    throw Standard_ConstructionError("Invalid model format");
  }

  double outerDiameter = std::stod(model.substr(2, xPos - 2));
  double thickness = std::stod(model.substr(xPos + 1));

  if (outerDiameter <= 0.0 || thickness <= 0.0) {
    throw Standard_ConstructionError("Diameter and thickness must be positive");
  }
  if (thickness >= outerDiameter / 2) {
    throw Standard_ConstructionError("Thickness must be less than radius");
  }

  // 创建圆钢管截面
  gp_Ax2 axis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  BRepPrimAPI_MakeCylinder outerCylinder(axis, outerDiameter / 2, length);
  BRepPrimAPI_MakeCylinder innerCylinder(axis, outerDiameter / 2 - thickness,
                                         length);

  // 执行布尔差操作
  BRepAlgoAPI_Cut cutter(outerCylinder.Shape(), innerCylinder.Shape());
  if (!cutter.IsDone()) {
    throw Standard_ConstructionError("Failed to create round steel tube");
  }

  return cutter.Shape();
}

/**
 * @brief 创建带定位的圆钢管
 * @param model 型号
 * @param length 长度
 * @param position 底面中心点位置
 * @param direction 长度方向（默认Z轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_round_steel_tube(const std::string &model, double length,
                                     const gp_Pnt &position,
                                     const gp_Dir &direction = gp_Dir(0, 0,
                                                                      1)) {
  // 首先创建标准方向的圆钢管
  TopoDS_Shape tube = create_round_steel_tube(model, length);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(position, direction);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(tube, transformation);
  return transform.Shape();
}

/**
 * @brief 创建矩形钢管图元
 * @param model 型号 (如"RT50X30X4"表示宽度50mm，高度30mm，壁厚4mm)
 * @param length 长度 (Length > 0)
 * @return TopoDS_Shape 生成的矩形钢管形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_rectangular_steel_tube(const std::string &model,
                                           double length) {
  // 参数验证
  if (length <= 0.0) {
    throw Standard_ConstructionError("Length must be positive");
  }
  if (model.empty() || model.substr(0, 2) != "RT") {
    throw Standard_ConstructionError("Invalid model format");
  }

  // 解析型号参数
  size_t x1Pos = model.find('X');
  size_t x2Pos = model.find('X', x1Pos + 1);
  if (x1Pos == std::string::npos || x2Pos == std::string::npos) {
    throw Standard_ConstructionError("Invalid model format");
  }

  double width = std::stod(model.substr(2, x1Pos - 2));
  double height = std::stod(model.substr(x1Pos + 1, x2Pos - x1Pos - 1));
  double thickness = std::stod(model.substr(x2Pos + 1));

  if (width <= 0.0 || height <= 0.0 || thickness <= 0.0) {
    throw Standard_ConstructionError("Dimensions must be positive");
  }
  if (thickness >= width / 2 || thickness >= height / 2) {
    throw Standard_ConstructionError(
        "Thickness must be less than half of width/height");
  }

  // 创建外轮廓
  BRepBuilderAPI_MakeWire outerWire;
  double halfWidth = width / 2;
  double halfHeight = height / 2;

  gp_Pnt p1(-halfWidth, -halfHeight, 0);
  gp_Pnt p2(halfWidth, -halfHeight, 0);
  gp_Pnt p3(halfWidth, halfHeight, 0);
  gp_Pnt p4(-halfWidth, halfHeight, 0);

  outerWire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  outerWire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
  outerWire.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
  outerWire.Add(BRepBuilderAPI_MakeEdge(p4, p1).Edge());

  // 创建内轮廓
  BRepBuilderAPI_MakeWire innerWire;
  double innerWidth = width - 2 * thickness;
  double innerHeight = height - 2 * thickness;
  double halfInnerWidth = innerWidth / 2;
  double halfInnerHeight = innerHeight / 2;

  gp_Pnt p5(-halfInnerWidth, -halfInnerHeight, 0);
  gp_Pnt p6(halfInnerWidth, -halfInnerHeight, 0);
  gp_Pnt p7(halfInnerWidth, halfInnerHeight, 0);
  gp_Pnt p8(-halfInnerWidth, halfInnerHeight, 0);

  innerWire.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge());
  innerWire.Add(BRepBuilderAPI_MakeEdge(p6, p7).Edge());
  innerWire.Add(BRepBuilderAPI_MakeEdge(p7, p8).Edge());
  innerWire.Add(BRepBuilderAPI_MakeEdge(p8, p5).Edge());

  // 创建面
  BRepBuilderAPI_MakeFace outerFace(outerWire.Wire());
  BRepBuilderAPI_MakeFace innerFace(innerWire.Wire());

  // 执行布尔差操作
  BRepAlgoAPI_Cut cutter(outerFace.Shape(), innerFace.Shape());
  if (!cutter.IsDone()) {
    throw Standard_ConstructionError("Failed to create rectangular tube face");
  }

  // 沿Z轴拉伸创建矩形钢管
  gp_Vec direction(0, 0, length);
  BRepPrimAPI_MakePrism prismMaker(cutter.Shape(), direction);

  if (!prismMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to extrude rectangular tube");
  }

  return prismMaker.Shape();
}

/**
 * @brief 创建带定位的矩形钢管
 * @param model 型号
 * @param length 长度
 * @param position 底面中心点位置
 * @param direction 长度方向（默认Z轴）
 * @param widthDir 宽度方向（默认X轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape
create_rectangular_steel_tube(const std::string &model, double length,
                              const gp_Pnt &position,
                              const gp_Dir &direction = gp_Dir(0, 0, 1),
                              const gp_Dir &widthDir = gp_Dir(1, 0, 0)) {
  // 首先创建标准方向的矩形钢管
  TopoDS_Shape tube = create_rectangular_steel_tube(model, length);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  gp_Dir heightDir = direction.Crossed(widthDir);
  gp_Ax3 targetAx3(position, direction, widthDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(tube, transformation);
  return transform.Shape();
}

/**
 * @brief 创建方形钢管图元
 * @param model 型号 (如"ST50X4"表示边长50mm，壁厚4mm)
 * @param length 长度 (Length > 0)
 * @return TopoDS_Shape 生成的方形钢管形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_square_steel_tube(const std::string &model, double length) {
  // 参数验证
  if (length <= 0.0) {
    throw Standard_ConstructionError("Length must be positive");
  }
  if (model.empty() || model.substr(0, 2) != "ST") {
    throw Standard_ConstructionError("Invalid model format");
  }

  // 解析型号参数
  size_t xPos = model.find('X');
  if (xPos == std::string::npos) {
    throw Standard_ConstructionError("Invalid model format");
  }

  double side = std::stod(model.substr(2, xPos - 2));
  double thickness = std::stod(model.substr(xPos + 1));

  if (side <= 0.0 || thickness <= 0.0) {
    throw Standard_ConstructionError("Side and thickness must be positive");
  }
  if (thickness >= side / 2) {
    throw Standard_ConstructionError(
        "Thickness must be less than half of side length");
  }

  // 创建外轮廓
  BRepBuilderAPI_MakeWire outerWire;
  double halfSide = side / 2;

  gp_Pnt p1(-halfSide, -halfSide, 0);
  gp_Pnt p2(halfSide, -halfSide, 0);
  gp_Pnt p3(halfSide, halfSide, 0);
  gp_Pnt p4(-halfSide, halfSide, 0);

  outerWire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  outerWire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
  outerWire.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
  outerWire.Add(BRepBuilderAPI_MakeEdge(p4, p1).Edge());

  // 创建内轮廓
  BRepBuilderAPI_MakeWire innerWire;
  double innerSide = side - 2 * thickness;
  double halfInnerSide = innerSide / 2;

  gp_Pnt p5(-halfInnerSide, -halfInnerSide, 0);
  gp_Pnt p6(halfInnerSide, -halfInnerSide, 0);
  gp_Pnt p7(halfInnerSide, halfInnerSide, 0);
  gp_Pnt p8(-halfInnerSide, halfInnerSide, 0);

  innerWire.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge());
  innerWire.Add(BRepBuilderAPI_MakeEdge(p6, p7).Edge());
  innerWire.Add(BRepBuilderAPI_MakeEdge(p7, p8).Edge());
  innerWire.Add(BRepBuilderAPI_MakeEdge(p8, p5).Edge());

  // 创建面
  BRepBuilderAPI_MakeFace outerFace(outerWire.Wire());
  BRepBuilderAPI_MakeFace innerFace(innerWire.Wire());

  // 执行布尔差操作
  BRepAlgoAPI_Cut cutter(outerFace.Shape(), innerFace.Shape());
  if (!cutter.IsDone()) {
    throw Standard_ConstructionError("Failed to create square tube face");
  }

  // 沿Z轴拉伸创建方形钢管
  gp_Vec direction(0, 0, length);
  BRepPrimAPI_MakePrism prismMaker(cutter.Shape(), direction);

  if (!prismMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to extrude square tube");
  }

  return prismMaker.Shape();
}

/**
 * @brief 创建带定位的方形钢管
 * @param model 型号
 * @param length 长度
 * @param position 底面中心点位置
 * @param direction 长度方向（默认Z轴）
 * @param xDir 宽度方向（默认X轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_square_steel_tube(const std::string &model, double length,
                                      const gp_Pnt &position,
                                      const gp_Dir &direction = gp_Dir(0, 0, 1),
                                      const gp_Dir &xDir = gp_Dir(1, 0, 0)) {
  // 首先创建标准方向的方形钢管
  TopoDS_Shape tube = create_square_steel_tube(model, length);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  gp_Dir yDir = direction.Crossed(xDir);
  gp_Ax3 targetAx3(position, direction, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(tube, transformation);
  return transform.Shape();
}

/**
 * @brief 创建双槽钢图元
 * @param model 型号
 * (如"DC200X75X6X9"表示高度200mm，翼缘宽度75mm，腹板厚度6mm，翼缘厚度9mm)
 * @param length 长度 (Length > 0)
 * @param spacing 两槽钢间距 (Spacing >= 0)
 * @return TopoDS_Shape 生成的双槽钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_double_channel_steel(const std::string &model,
                                         double length, double spacing = 0.0) {
  // 参数验证
  if (length <= 0.0) {
    throw Standard_ConstructionError("Length must be positive");
  }
  if (spacing < 0.0) {
    throw Standard_ConstructionError("Spacing must be non-negative");
  }
  if (model.empty() || model.substr(0, 2) != "DC") {
    throw Standard_ConstructionError("Invalid model format");
  }

  // 解析型号参数
  size_t x1Pos = model.find('X');
  size_t x2Pos = model.find('X', x1Pos + 1);
  size_t x3Pos = model.find('X', x2Pos + 1);
  if (x1Pos == std::string::npos || x2Pos == std::string::npos ||
      x3Pos == std::string::npos) {
    throw Standard_ConstructionError("Invalid model format");
  }

  double height = std::stod(model.substr(2, x1Pos - 2));
  double flangeWidth = std::stod(model.substr(x1Pos + 1, x2Pos - x1Pos - 1));
  double webThickness = std::stod(model.substr(x2Pos + 1, x3Pos - x2Pos - 1));
  double flangeThickness = std::stod(model.substr(x3Pos + 1));

  if (height <= 0.0 || flangeWidth <= 0.0 || webThickness <= 0.0 ||
      flangeThickness <= 0.0) {
    throw Standard_ConstructionError("Dimensions must be positive");
  }

  // 创建单个槽钢
  TopoDS_Shape singleChannel = create_beam_channel(
      model.substr(2), length); // 去掉"DC"前缀调用单槽钢函数

  // 创建第二个槽钢（镜像）
  gp_Trsf mirrorTransform;
  mirrorTransform.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0)));
  BRepBuilderAPI_Transform mirrorMaker(singleChannel, mirrorTransform);

  // 移动两个槽钢到正确位置
  double offset = flangeWidth + spacing;
  gp_Trsf moveTransform1, moveTransform2;
  moveTransform1.SetTranslation(gp_Vec(-offset / 2, 0, 0));
  moveTransform2.SetTranslation(gp_Vec(offset / 2, 0, 0));

  BRepBuilderAPI_Transform move1(singleChannel, moveTransform1);
  BRepBuilderAPI_Transform move2(mirrorMaker.Shape(), moveTransform2);

  // 合并两个槽钢
  BRepAlgoAPI_Fuse fuser(move1.Shape(), move2.Shape());
  if (!fuser.IsDone()) {
    throw Standard_ConstructionError("Failed to fuse double channels");
  }

  return fuser.Shape();
}

/**
 * @brief 创建带定位的双槽钢
 * @param model 型号
 * @param length 长度
 * @param position 底面中心点位置
 * @param direction 长度方向（默认Z轴）
 * @param xDir 开口方向（默认X轴正方向）
 * @param spacing 两槽钢间距 (Spacing >= 0)
 * @return TopoDS_Shape
 */
TopoDS_Shape create_double_channel_steel(
    const std::string &model, double length, const gp_Pnt &position,
    const gp_Dir &direction = gp_Dir(0, 0, 1),
    const gp_Dir &xDir = gp_Dir(1, 0, 0), double spacing = 0.0) {
  // 首先创建标准方向的双槽钢
  TopoDS_Shape doubleChannel =
      create_double_channel_steel(model, length, spacing);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  gp_Dir yDir = direction.Crossed(xDir);
  gp_Ax3 targetAx3(position, direction, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(doubleChannel, transformation);
  return transform.Shape();
}

/**
 * @brief 创建等边双角钢图元
 * @param model 型号 (如"EDL50X4"表示边长50mm，厚度4mm)
 * @param length 长度 (Length > 0)
 * @param spacing 两角钢间距 (Spacing >= 0)
 * @return TopoDS_Shape 生成的等边双角钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_equilateral_double_angle_steel(const std::string &model,
                                                   double length,
                                                   double spacing = 0.0) {
  // 参数验证
  if (length <= 0.0) {
    throw Standard_ConstructionError("Length must be positive");
  }
  if (spacing < 0.0) {
    throw Standard_ConstructionError("Spacing must be non-negative");
  }
  if (model.empty() || model.substr(0, 3) != "EDL") {
    throw Standard_ConstructionError("Invalid model format");
  }

  // 解析型号参数
  size_t xPos = model.find('X');
  if (xPos == std::string::npos) {
    throw Standard_ConstructionError("Invalid model format");
  }

  double side = std::stod(model.substr(3, xPos - 3));
  double thickness = std::stod(model.substr(xPos + 1));

  if (side <= 0.0 || thickness <= 0.0) {
    throw Standard_ConstructionError("Side and thickness must be positive");
  }
  if (thickness >= side) {
    throw Standard_ConstructionError("Thickness must be less than side length");
  }

  // 创建单个等边角钢
  TopoDS_Shape singleAngle =
      create_lsteel(model.substr(3), length); // 去掉"ED"前缀调用单角钢函数

  // 创建第二个角钢（镜像）
  gp_Trsf mirrorTransform;
  mirrorTransform.SetMirror(
      gp_Ax2(gp_Pnt(0, 0, 0), gp_Vec(1, 1, 0).Normalized()));
  BRepBuilderAPI_Transform mirrorMaker(singleAngle, mirrorTransform);

  // 移动两个角钢到正确位置
  double offset = side * sqrt(2) + spacing;
  gp_Trsf moveTransform1, moveTransform2;
  moveTransform1.SetTranslation(gp_Vec(-offset / 2, -offset / 2, 0));
  moveTransform2.SetTranslation(gp_Vec(offset / 2, offset / 2, 0));

  BRepBuilderAPI_Transform move1(singleAngle, moveTransform1);
  BRepBuilderAPI_Transform move2(mirrorMaker.Shape(), moveTransform2);

  // 合并两个角钢
  BRepAlgoAPI_Fuse fuser(move1.Shape(), move2.Shape());
  if (!fuser.IsDone()) {
    throw Standard_ConstructionError("Failed to fuse double angles");
  }

  return fuser.Shape();
}

/**
 * @brief 创建带定位的等边双角钢
 * @param model 型号
 * @param length 长度
 * @param position 底面中心点位置
 * @param direction 长度方向（默认Z轴）
 * @param xDir 第一个角钢的长边方向（默认X轴）
 * @param spacing 两角钢间距 (Spacing >= 0)
 * @return TopoDS_Shape
 */
TopoDS_Shape create_equilateral_double_angle_steel(
    const std::string &model, double length, const gp_Pnt &position,
    const gp_Dir &direction = gp_Dir(0, 0, 1),
    const gp_Dir &xDir = gp_Dir(1, 0, 0), double spacing = 0.0) {
  // 首先创建标准方向的等边双角钢
  TopoDS_Shape doubleAngle =
      create_equilateral_double_angle_steel(model, length, spacing);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  gp_Dir yDir = direction.Crossed(xDir);
  gp_Ax3 targetAx3(position, direction, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(doubleAngle, transformation);
  return transform.Shape();
}

/**
 * @brief 创建不等边双角钢图元
 * @param model 型号 (如"UDL50X30X4"表示长边50mm，短边30mm，厚度4mm)
 * @param length 长度 (Length > 0)
 * @param spacing 两角钢间距 (Spacing >= 0)
 * @return TopoDS_Shape 生成的不等边双角钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_unequal_double_angle_steel(const std::string &model,
                                               double length,
                                               double spacing = 0.0) {
  // 参数验证
  if (length <= 0.0) {
    throw Standard_ConstructionError("Length must be positive");
  }
  if (spacing < 0.0) {
    throw Standard_ConstructionError("Spacing must be non-negative");
  }
  if (model.empty() || model.substr(0, 3) != "UDL") {
    throw Standard_ConstructionError("Invalid model format");
  }

  // 解析型号参数
  size_t x1Pos = model.find('X');
  size_t x2Pos = model.find('X', x1Pos + 1);
  if (x1Pos == std::string::npos || x2Pos == std::string::npos) {
    throw Standard_ConstructionError("Invalid model format");
  }

  double longSide = std::stod(model.substr(3, x1Pos - 3));
  double shortSide = std::stod(model.substr(x1Pos + 1, x2Pos - x1Pos - 1));
  double thickness = std::stod(model.substr(x2Pos + 1));

  if (longSide <= 0.0 || shortSide <= 0.0 || thickness <= 0.0) {
    throw Standard_ConstructionError("Dimensions must be positive");
  }
  if (thickness >= longSide || thickness >= shortSide) {
    throw Standard_ConstructionError(
        "Thickness must be less than side lengths");
  }

  // 创建单个不等边角钢
  TopoDS_Shape singleAngle =
      create_lsteel(model.substr(3), length); // 去掉"UD"前缀调用单角钢函数

  // 创建第二个角钢（镜像）
  gp_Trsf mirrorTransform;
  mirrorTransform.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0)));
  BRepBuilderAPI_Transform mirrorMaker(singleAngle, mirrorTransform);

  // 移动两个角钢到正确位置
  double offset = longSide + spacing;
  gp_Trsf moveTransform1, moveTransform2;
  moveTransform1.SetTranslation(gp_Vec(-offset / 2, 0, 0));
  moveTransform2.SetTranslation(gp_Vec(offset / 2, 0, 0));

  BRepBuilderAPI_Transform move1(singleAngle, moveTransform1);
  BRepBuilderAPI_Transform move2(mirrorMaker.Shape(), moveTransform2);

  // 合并两个角钢
  BRepAlgoAPI_Fuse fuser(move1.Shape(), move2.Shape());
  if (!fuser.IsDone()) {
    throw Standard_ConstructionError("Failed to fuse unequal angles");
  }

  return fuser.Shape();
}

/**
 * @brief 创建带定位的不等边双角钢
 * @param model 型号
 * @param length 长度
 * @param position 底面中心点位置
 * @param direction 长度方向（默认Z轴）
 * @param longSideDir 长边方向（默认X轴）
 * @param spacing 两角钢间距 (Spacing >= 0)
 * @return TopoDS_Shape
 */
TopoDS_Shape create_unequal_double_angle_steel(
    const std::string &model, double length, const gp_Pnt &position,
    const gp_Dir &direction = gp_Dir(0, 0, 1),
    const gp_Dir &longSideDir = gp_Dir(1, 0, 0), double spacing = 0.0) {
  // 首先创建标准方向的不等边双角钢
  TopoDS_Shape doubleAngle =
      create_unequal_double_angle_steel(model, length, spacing);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  gp_Dir shortSideDir = direction.Crossed(longSideDir);
  gp_Ax3 targetAx3(position, direction, longSideDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(doubleAngle, transformation);
  return transform.Shape();
}

/**
 * @brief 创建多边形钢管图元
 * @param model 型号 (如"PT6-50X4"表示6边形，外接圆直径50mm，壁厚4mm)
 * @param length 长度 (Length > 0)
 * @return TopoDS_Shape 生成的多边形钢管形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_polygon_tube(const std::string &model, double length) {
  // 参数验证
  if (length <= 0.0) {
    throw Standard_ConstructionError("Length must be positive");
  }
  if (model.empty() || model.substr(0, 2) != "PT") {
    throw Standard_ConstructionError("Invalid model format");
  }

  // 解析型号参数
  size_t dashPos = model.find('-');
  size_t xPos = model.find('X');
  if (dashPos == std::string::npos || xPos == std::string::npos) {
    throw Standard_ConstructionError("Invalid model format");
  }

  int sides = std::stoi(model.substr(2, dashPos - 2));
  double diameter = std::stod(model.substr(dashPos + 1, xPos - dashPos - 1));
  double thickness = std::stod(model.substr(xPos + 1));

  if (sides < 3) {
    throw Standard_ConstructionError("Polygon must have at least 3 sides");
  }
  if (diameter <= 0.0 || thickness <= 0.0) {
    throw Standard_ConstructionError("Diameter and thickness must be positive");
  }
  if (thickness >= diameter / 2) {
    throw Standard_ConstructionError("Thickness must be less than radius");
  }

  // 创建外多边形轮廓
  BRepBuilderAPI_MakeWire outerWire;
  double radius = diameter / 2;
  for (int i = 0; i < sides; i++) {
    double angle1 = 2 * M_PI * i / sides;
    double angle2 = 2 * M_PI * (i + 1) / sides;
    gp_Pnt p1(radius * cos(angle1), radius * sin(angle1), 0);
    gp_Pnt p2(radius * cos(angle2), radius * sin(angle2), 0);
    outerWire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  }

  // 创建内多边形轮廓
  BRepBuilderAPI_MakeWire innerWire;
  double innerRadius = radius - thickness;
  for (int i = 0; i < sides; i++) {
    double angle1 = 2 * M_PI * i / sides;
    double angle2 = 2 * M_PI * (i + 1) / sides;
    gp_Pnt p1(innerRadius * cos(angle1), innerRadius * sin(angle1), 0);
    gp_Pnt p2(innerRadius * cos(angle2), innerRadius * sin(angle2), 0);
    innerWire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  }

  // 创建面
  BRepBuilderAPI_MakeFace outerFace(outerWire.Wire());
  BRepBuilderAPI_MakeFace innerFace(innerWire.Wire());

  // 执行布尔差操作
  BRepAlgoAPI_Cut cutter(outerFace.Shape(), innerFace.Shape());
  if (!cutter.IsDone()) {
    throw Standard_ConstructionError("Failed to create polygon tube face");
  }

  // 沿Z轴拉伸创建多边形钢管
  gp_Vec direction(0, 0, length);
  BRepPrimAPI_MakePrism prismMaker(cutter.Shape(), direction);

  if (!prismMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to extrude polygon tube");
  }

  return prismMaker.Shape();
}

/**
 * @brief 创建带定位的多边形钢管
 * @param model 型号
 * @param length 长度
 * @param position 底面中心点位置
 * @param direction 长度方向（默认Z轴）
 * @param xDir 第一边方向（默认X轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_polygon_tube(const std::string &model, double length,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction = gp_Dir(0, 0, 1),
                                 const gp_Dir &xDir = gp_Dir(1, 0, 0)) {
  // 首先创建标准方向的多边形钢管
  TopoDS_Shape tube = create_polygon_tube(model, length);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  gp_Dir yDir = direction.Crossed(xDir);
  gp_Ax3 targetAx3(position, direction, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(tube, transformation);
  return transform.Shape();
}
/**
 * @brief 创建挖孔桩基础/灌注桩单桩基础
 * @param params 基础参数结构体
 * @return TopoDS_Shape 生成的基础形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_bored_pile_foundation(const bored_pile_params &params) {
  // 参数验证
  if (params.H1 <= 0 || params.H2 <= 0 || params.H3 <= 0 || params.H4 <= 0) {
    throw Standard_ConstructionError("高度参数必须为正数");
  }
  if (params.d <= 0 || params.D <= 0) {
    throw Standard_ConstructionError("直径参数必须为正数");
  }
  if (params.D < params.d) {
    throw Standard_ConstructionError("底部直径D不能小于上部直径d");
  }

  // 上部圆柱段 (H1)
  gp_Ax2 axis1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  BRepPrimAPI_MakeCylinder cylinder1(axis1, params.d / 2, params.H1);

  // 底部圆柱段 (H3)
  gp_Ax2 axis2(gp_Pnt(0, 0, params.H1 + params.H2), gp_Dir(0, 0, 1));
  BRepPrimAPI_MakeCylinder cylinder2(axis2, params.D / 2, params.H3);

  // 桩头段 (H4)
  gp_Ax2 axis3(gp_Pnt(0, 0, -params.H4), gp_Dir(0, 0, 1));
  BRepPrimAPI_MakeCylinder cylinder3(axis3, params.d / 2, params.H4);

  // 合并基本形状
  BRepAlgoAPI_Fuse fuser(cylinder1.Shape(), cylinder2.Shape());
  fuser = BRepAlgoAPI_Fuse(fuser.Shape(), cylinder3.Shape());

  // 创建过渡段 (H2)
  if (params.D != params.d) {
    // 创建过渡段轮廓线
    BRepBuilderAPI_MakeWire transitionWire;
    gp_Pnt p1(params.d / 2, 0, params.H1);
    gp_Pnt p2(params.D / 2, 0, params.H1 + params.H2);
    transitionWire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());

    // 创建旋转面形成过渡段
    gp_Ax1 rotationAxis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
    BRepPrimAPI_MakeRevol transitionMaker(transitionWire.Wire(), rotationAxis);

    if (transitionMaker.IsDone()) {
      // 合并过渡段到整体
      fuser = BRepAlgoAPI_Fuse(fuser.Shape(), transitionMaker.Shape());
    }
  }

  if (!fuser.IsDone()) {
    throw Standard_ConstructionError("基础形状合并失败");
  }

  // 应用圆角过渡
  if (params.filletRadius > 0) {
    BRepFilletAPI_MakeFillet filletMaker(fuser.Shape());

    // 在上部圆柱和过渡段连接处添加圆角
    TopExp_Explorer explorer(fuser.Shape(), TopAbs_EDGE);
    while (explorer.More()) {
      TopoDS_Edge edge = TopoDS::Edge(explorer.Current());
      filletMaker.Add(params.filletRadius, edge);
      explorer.Next();
    }

    if (filletMaker.IsDone()) {
      return filletMaker.Shape();
    }
  }

  return fuser.Shape();
}

/**
 * @brief 创建带定位的挖孔桩基础/灌注桩单桩基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_bored_pile_foundation(const bored_pile_params &params,
                                          const gp_Pnt &position,
                                          const gp_Dir &direction = gp_Dir(0, 0,
                                                                           1)) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_bored_pile_foundation(params);

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
TopoDS_Shape create_pile_cap_foundation(const pile_cap_params &params) {
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
    gp_Ax2 axis(gp_Pnt(0, 0, -params.H4), gp_Dir(0, 0, 1));
    cap = BRepPrimAPI_MakeCylinder(axis, params.b / 2, params.H4).Shape();
  } else { // 方形承台柱
    BRepBuilderAPI_MakeWire wire;
    double halfB = params.b / 2;
    wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfB, -halfB, -params.H4),
                                     gp_Pnt(halfB, -halfB, -params.H4))
                 .Edge());
    // ... 创建方形轮廓
    BRepBuilderAPI_MakeFace face(wire.Wire());
    cap = BRepPrimAPI_MakePrism(face.Face(), gp_Vec(0, 0, params.H4)).Shape();
  }

  // 创建承台底板
  BRepBuilderAPI_MakeWire baseWire;
  double halfB1 = params.B1 / 2;
  double halfL1 = params.L1 / 2;
  baseWire.Add(
      BRepBuilderAPI_MakeEdge(gp_Pnt(-halfB1, -halfL1, -params.H4 - params.H5),
                              gp_Pnt(halfB1, -halfL1, -params.H4 - params.H5))
          .Edge());
  // ... 创建底板轮廓
  BRepBuilderAPI_MakeFace baseFace(baseWire.Wire());
  TopoDS_Shape base =
      BRepPrimAPI_MakePrism(baseFace.Face(), gp_Vec(0, 0, params.H5)).Shape();

  // 合并承台和底板
  BRepAlgoAPI_Fuse fuser(cap, base);

  // 创建桩
  std::vector<TopoDS_Shape> piles;
  for (int i = 0; i < params.ZCOUNT; i++) {
    gp_Pnt position(params.ZPOSTARRAY[i].X(), params.ZPOSTARRAY[i].Y(),
                    params.ZPOSTARRAY[i].Z());

    // 创建单桩
    bored_pile_params pileParams;
    pileParams.H1 = params.H1;
    pileParams.H2 = params.H2;
    pileParams.H3 = params.H3;
    pileParams.H4 = params.H6;
    pileParams.d = params.d;
    pileParams.D = params.D;

    TopoDS_Shape pile = create_bored_pile_foundation(pileParams);

    // 移动桩到正确位置
    gp_Trsf transform;
    transform.SetTranslation(gp_Vec(position.X(), position.Y(), position.Z()));
    BRepBuilderAPI_Transform mover(pile, transform);
    piles.push_back(mover.Shape());
  }

  // 合并所有桩
  for (const auto &pile : piles) {
    fuser = BRepAlgoAPI_Fuse(fuser.Shape(), pile);
    if (!fuser.IsDone()) {
      throw Standard_ConstructionError("桩合并失败");
    }
  }

  // 应用偏心调整
  if (params.e1 != 0 || params.e2 != 0) {
    gp_Trsf eccTransform;
    eccTransform.SetTranslation(gp_Vec(params.e1, params.e2, 0));
    BRepBuilderAPI_Transform eccMover(fuser.Shape(), eccTransform);
    return eccMover.Shape();
  }

  return fuser.Shape();
}

/**
 * @brief 创建带定位的承台挖孔桩基础/灌注桩基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_pile_cap_foundation(const pile_cap_params &params,
                                        const gp_Pnt &position,
                                        const gp_Dir &direction = gp_Dir(0, 0,
                                                                         1)) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_pile_cap_foundation(params);

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
TopoDS_Shape create_rock_anchor_foundation(const rock_anchor_params &params) {
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

  // 创建锚桩
  std::vector<TopoDS_Shape> anchors;
  for (int i = 0; i < params.ZCOUNT; i++) {
    gp_Pnt position(params.ZPOSTARRAY[i].X(), params.ZPOSTARRAY[i].Y(),
                    params.ZPOSTARRAY[i].Z());

    // 创建圆柱形锚桩
    gp_Ax2 axis(position, gp_Dir(0, 0, 1));
    TopoDS_Shape anchor =
        BRepPrimAPI_MakeCylinder(axis, params.d / 2, params.H2).Shape();
    anchors.push_back(anchor);
  }

  // 合并所有部件
  BRepAlgoAPI_Fuse fuser;
  fuser = BRepAlgoAPI_Fuse(base, anchors[0]);

  for (size_t i = 1; i < anchors.size(); i++) {
    fuser = BRepAlgoAPI_Fuse(fuser.Shape(), anchors[i]);
    if (!fuser.IsDone()) {
      throw Standard_ConstructionError("锚桩合并失败");
    }
  }

  return fuser.Shape();
}

/**
 * @brief 创建带定位的直锚式岩石锚桩基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape
create_rock_anchor_foundation(const rock_anchor_params &params,
                              const gp_Pnt &position,
                              const gp_Dir &direction = gp_Dir(0, 0, 1)) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_rock_anchor_foundation(params);

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
TopoDS_Shape
create_rock_pile_cap_foundation(const rock_pile_cap_params &params) {
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

  // 合并承台柱和底板
  BRepAlgoAPI_Fuse fuser(column, base);

  // 创建锚桩
  std::vector<TopoDS_Shape> anchors;
  for (int i = 0; i < params.ZCOUNT; i++) {
    gp_Pnt position(params.ZPOSTARRAY[i].X(), params.ZPOSTARRAY[i].Y(),
                    params.ZPOSTARRAY[i].Z());

    // 创建圆柱形锚桩
    gp_Ax2 axis(position, gp_Dir(0, 0, 1));
    TopoDS_Shape anchor =
        BRepPrimAPI_MakeCylinder(axis, params.d / 2, params.H3).Shape();
    anchors.push_back(anchor);
  }

  // 合并所有锚桩
  for (const auto &anchor : anchors) {
    fuser = BRepAlgoAPI_Fuse(fuser.Shape(), anchor);
    if (!fuser.IsDone()) {
      throw Standard_ConstructionError("锚桩合并失败");
    }
  }

  // 应用偏心调整
  if (params.e1 != 0 || params.e2 != 0) {
    gp_Trsf eccTransform;
    eccTransform.SetTranslation(gp_Vec(params.e1, params.e2, 0));
    BRepBuilderAPI_Transform eccMover(fuser.Shape(), eccTransform);
    return eccMover.Shape();
  }

  return fuser.Shape();
}

/**
 * @brief 创建带定位的承台式岩石锚桩基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape
create_rock_pile_cap_foundation(const rock_pile_cap_params &params,
                                const gp_Pnt &position,
                                const gp_Dir &direction = gp_Dir(0, 0, 1)) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_rock_pile_cap_foundation(params);

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
TopoDS_Shape create_embedded_rock_anchor_foundation(
    const embedded_rock_anchor_params &params) {
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
  gp_Ax2 axis1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  TopoDS_Shape upperCylinder =
      BRepPrimAPI_MakeCylinder(axis1, params.d / 2, params.H1).Shape();

  // 创建底部圆柱段 (H3)
  gp_Ax2 axis2(gp_Pnt(0, 0, params.H1 + params.H2), gp_Dir(0, 0, 1));
  TopoDS_Shape lowerCylinder =
      BRepPrimAPI_MakeCylinder(axis2, params.D / 2, params.H3).Shape();

  // 创建过渡段 (H2)
  TopoDS_Shape transition;
  if (params.D != params.d) {
    BRepBuilderAPI_MakeWire wire;
    gp_Pnt p1(params.d / 2, 0, params.H1);
    gp_Pnt p2(params.D / 2, 0, params.H1 + params.H2);
    wire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());

    gp_Ax1 rotationAxis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
    transition = BRepPrimAPI_MakeRevol(wire.Wire(), rotationAxis).Shape();
  }

  // 合并所有部件
  BRepAlgoAPI_Fuse fuser(upperCylinder, lowerCylinder);
  if (params.D != params.d) {
    fuser = BRepAlgoAPI_Fuse(fuser.Shape(), transition);
  }

  if (!fuser.IsDone()) {
    throw Standard_ConstructionError("基础形状合并失败");
  }

  return fuser.Shape();
}

/**
 * @brief 创建带定位的嵌固式岩石锚桩基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_embedded_rock_anchor_foundation(
    const embedded_rock_anchor_params &params, const gp_Pnt &position,
    const gp_Dir &direction = gp_Dir(0, 0, 1)) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_embedded_rock_anchor_foundation(params);

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
TopoDS_Shape create_inclined_rock_anchor_foundation(
    const inclined_rock_anchor_params &params) {
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

  // 创建斜锚桩
  gp_Ax2 anchorAxis(gp_Pnt(0, 0, -params.H1), gp_Dir(0, 0, 1));

  // 计算斜度方向向量
  double tanAlpha1 = tan(params.alpha1 * M_PI / 180.0);
  double tanAlpha2 = tan(params.alpha2 * M_PI / 180.0);
  gp_Vec slopeDir(tanAlpha1, tanAlpha2, 1.0);
  slopeDir.Normalize();

  // 创建斜圆柱
  BRepPrimAPI_MakeCylinder anchorMaker(anchorAxis, params.d / 2, params.H2);
  gp_Trsf slopeTransform;
  slopeTransform.SetRotation(
      gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(-tanAlpha1, -tanAlpha2, 1.0)),
      atan(sqrt(tanAlpha1 * tanAlpha1 + tanAlpha2 * tanAlpha2)));
  BRepBuilderAPI_Transform slopedAnchor(anchorMaker.Shape(), slopeTransform);

  // 创建底部扩大头
  gp_Ax2 bottomAxis(gp_Pnt(0, 0, -params.H1 - params.H2), slopeDir);
  TopoDS_Shape bottom =
      BRepPrimAPI_MakeCylinder(bottomAxis, params.D / 2, params.H2 / 5).Shape();

  // 合并所有部件
  BRepAlgoAPI_Fuse fuser(base, slopedAnchor.Shape());
  fuser = BRepAlgoAPI_Fuse(fuser.Shape(), bottom);

  // 应用偏心调整
  if (params.e1 != 0 || params.e2 != 0) {
    gp_Trsf eccTransform;
    eccTransform.SetTranslation(gp_Vec(params.e1, params.e2, 0));
    BRepBuilderAPI_Transform eccMover(fuser.Shape(), eccTransform);
    return eccMover.Shape();
  }

  return fuser.Shape();
}

/**
 * @brief 创建带定位的斜锚式岩石锚桩基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_inclined_rock_anchor_foundation(
    const inclined_rock_anchor_params &params, const gp_Pnt &position,
    const gp_Dir &direction = gp_Dir(0, 0, 1)) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_inclined_rock_anchor_foundation(params);

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
TopoDS_Shape
create_excavated_foundation(const excavated_foundation_params &params) {
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
  gp_Ax2 axis1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  TopoDS_Shape upperCylinder =
      BRepPrimAPI_MakeCylinder(axis1, params.d / 2, params.H1).Shape();

  // 创建底部圆柱段 (H3)
  gp_Ax2 axis2(gp_Pnt(0, 0, params.H1 + params.H2), gp_Dir(0, 0, 1));
  TopoDS_Shape lowerCylinder =
      BRepPrimAPI_MakeCylinder(axis2, params.D / 2, params.H3).Shape();

  // 创建过渡段 (H2)
  TopoDS_Shape transition;
  if (params.alpha1 != 0 || params.alpha2 != 0) {
    // 斜柱掏挖基础
    double tanAlpha1 = tan(params.alpha1 * M_PI / 180.0);
    double tanAlpha2 = tan(params.alpha2 * M_PI / 180.0);

    // 创建斜向过渡段
    BRepOffsetAPI_ThruSections generator(true);

    // 上部轮廓
    gp_Circ upperCircle(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), params.d / 2);
    generator.AddWire(
        BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(upperCircle).Edge())
            .Wire());

    // 下部轮廓
    gp_Circ lowerCircle(
        gp_Ax2(gp_Pnt(tanAlpha1 * params.H2, tanAlpha2 * params.H2, params.H2),
               gp_Dir(0, 0, 1)),
        params.D / 2);
    generator.AddWire(
        BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(lowerCircle).Edge())
            .Wire());

    transition = generator.Shape();
  } else {
    // 直柱掏挖基础
    BRepBuilderAPI_MakeWire wire;
    gp_Pnt p1(params.d / 2, 0, 0);
    gp_Pnt p2(params.D / 2, 0, params.H2);
    wire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());

    gp_Ax1 rotationAxis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
    transition = BRepPrimAPI_MakeRevol(wire.Wire(), rotationAxis).Shape();
  }

  // 合并所有部件
  BRepAlgoAPI_Fuse fuser(upperCylinder, lowerCylinder);
  fuser = BRepAlgoAPI_Fuse(fuser.Shape(), transition);

  if (!fuser.IsDone()) {
    throw Standard_ConstructionError("基础形状合并失败");
  }

  return fuser.Shape();
}

/**
 * @brief 创建带定位的掏挖基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape
create_excavated_foundation(const excavated_foundation_params &params,
                            const gp_Pnt &position,
                            const gp_Dir &direction = gp_Dir(0, 0, 1)) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_excavated_foundation(params);

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
TopoDS_Shape create_step_foundation(const step_foundation_params &params) {
  // 参数验证
  if (params.H <= 0 || params.H1 <= 0 || params.H2 <= 0 || params.H3 <= 0) {
    throw Standard_ConstructionError("高度参数必须为正数");
  }
  if (params.b <= 0 || params.B1 <= 0 || params.B2 <= 0 || params.B3 <= 0 ||
      params.L1 <= 0 || params.L2 <= 0 || params.L3 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }
  if (params.N <= 0) {
    throw Standard_ConstructionError("台阶数必须大于0");
  }

  // 创建基础主体
  BRepBuilderAPI_MakeWire baseWire;
  double halfB = params.b / 2;
  baseWire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-halfB, -halfB, -params.H),
                                       gp_Pnt(halfB, -halfB, -params.H))
                   .Edge());
  // ... 创建基础底面轮廓
  BRepBuilderAPI_MakeFace baseFace(baseWire.Wire());
  TopoDS_Shape foundation =
      BRepPrimAPI_MakePrism(baseFace.Face(), gp_Vec(0, 0, params.H)).Shape();

  // 创建台阶
  std::vector<double> heights = {params.H1, params.H2, params.H3};
  std::vector<double> widths = {params.B1, params.B2, params.B3};
  std::vector<double> lengths = {params.L1, params.L2, params.L3};

  double currentHeight = 0;
  for (int i = 0; i < params.N && i < 3; i++) {
    double stepHeight = heights[i];
    double halfWidth = widths[i] / 2;
    double halfLength = lengths[i] / 2;

    // 创建台阶
    BRepBuilderAPI_MakeWire stepWire;
    stepWire.Add(
        BRepBuilderAPI_MakeEdge(gp_Pnt(-halfWidth, -halfLength, currentHeight),
                                gp_Pnt(halfWidth, -halfLength, currentHeight))
            .Edge());
    // ... 创建台阶轮廓
    BRepBuilderAPI_MakeFace stepFace(stepWire.Wire());
    TopoDS_Shape step =
        BRepPrimAPI_MakePrism(stepFace.Face(), gp_Vec(0, 0, stepHeight))
            .Shape();

    // 合并台阶到基础
    BRepAlgoAPI_Fuse fuser(foundation, step);
    if (!fuser.IsDone()) {
      throw Standard_ConstructionError("台阶合并失败");
    }
    foundation = fuser.Shape();
    currentHeight += stepHeight;
  }

  return foundation;
}

/**
 * @brief 创建带定位的台阶基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_step_foundation(const step_foundation_params &params,
                                    const gp_Pnt &position,
                                    const gp_Dir &direction = gp_Dir(0, 0, 1)) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_step_foundation(params);

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
TopoDS_Shape
create_step_plate_foundation(const step_plate_foundation_params &params) {
  // 参数验证
  if (params.H <= 0 || params.H1 <= 0 || params.H2 <= 0) {
    throw Standard_ConstructionError("高度参数必须为正数");
  }
  if (params.b <= 0 || params.L1 <= 0 || params.L2 <= 0 || params.B1 <= 0 ||
      params.B2 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }
  if (params.N < 1 || params.N > 3) {
    throw Standard_ConstructionError("台阶数量必须为1-3");
  }

  // 创建基础底板
  BRepBuilderAPI_MakeWire baseWire;
  double halfB1 = params.B1 / 2;
  double halfL1 = params.L1 / 2;

  gp_Pnt p1(-halfB1, -halfL1, -params.H);
  gp_Pnt p2(-halfB1, halfL1, -params.H);
  gp_Pnt p3(halfB1, halfL1, -params.H);
  gp_Pnt p4(halfB1, -halfL1, -params.H);

  baseWire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  baseWire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
  baseWire.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
  baseWire.Add(BRepBuilderAPI_MakeEdge(p4, p1).Edge());

  BRepBuilderAPI_MakeFace baseFace(baseWire.Wire());
  TopoDS_Shape base =
      BRepPrimAPI_MakePrism(baseFace.Face(), gp_Vec(0, 0, params.H)).Shape();

  // 创建台阶
  TopoDS_Shape steps;
  if (params.N >= 1) {
    // 第一级台阶
    double halfB2 = params.B2 / 2;
    double halfL2 = params.L2 / 2;
    double z1 = -params.H + params.H1;

    gp_Pnt s1(-halfB2, -halfL2, z1);
    gp_Pnt s2(-halfB2, halfL2, z1);
    gp_Pnt s3(halfB2, halfL2, z1);
    gp_Pnt s4(halfB2, -halfL2, z1);

    BRepBuilderAPI_MakeWire step1Wire;
    step1Wire.Add(BRepBuilderAPI_MakeEdge(s1, s2).Edge());
    step1Wire.Add(BRepBuilderAPI_MakeEdge(s2, s3).Edge());
    step1Wire.Add(BRepBuilderAPI_MakeEdge(s3, s4).Edge());
    step1Wire.Add(BRepBuilderAPI_MakeEdge(s4, s1).Edge());

    BRepBuilderAPI_MakeFace step1Face(step1Wire.Wire());
    TopoDS_Shape step1 =
        BRepPrimAPI_MakePrism(step1Face.Face(), gp_Vec(0, 0, params.H1))
            .Shape();

    steps = step1;
  }

  if (params.N >= 2) {
    // 第二级台阶
    double halfB3 = params.b / 2;
    double halfL3 = params.b / 2;
    double z2 = -params.H + params.H1 + params.H2;

    gp_Pnt s5(-halfB3, -halfL3, z2);
    gp_Pnt s6(-halfB3, halfL3, z2);
    gp_Pnt s7(halfB3, halfL3, z2);
    gp_Pnt s8(halfB3, -halfL3, z2);

    BRepBuilderAPI_MakeWire step2Wire;
    step2Wire.Add(BRepBuilderAPI_MakeEdge(s5, s6).Edge());
    step2Wire.Add(BRepBuilderAPI_MakeEdge(s6, s7).Edge());
    step2Wire.Add(BRepBuilderAPI_MakeEdge(s7, s8).Edge());
    step2Wire.Add(BRepBuilderAPI_MakeEdge(s8, s5).Edge());

    BRepBuilderAPI_MakeFace step2Face(step2Wire.Wire());
    TopoDS_Shape step2 =
        BRepPrimAPI_MakePrism(step2Face.Face(), gp_Vec(0, 0, params.H2))
            .Shape();

    BRepAlgoAPI_Fuse fuser(steps, step2);
    steps = fuser.Shape();
  }

  if (params.N >= 3) {
    // 第三级台阶（柱顶）
    double halfB4 = params.b / 2;
    double halfL4 = params.b / 2;
    double z3 = -params.H + params.H1 + params.H2 + params.H3;

    gp_Pnt s9(-halfB4, -halfL4, z3);
    gp_Pnt s10(-halfB4, halfL4, z3);
    gp_Pnt s11(halfB4, halfL4, z3);
    gp_Pnt s12(halfB4, -halfL4, z3);

    BRepBuilderAPI_MakeWire step3Wire;
    step3Wire.Add(BRepBuilderAPI_MakeEdge(s9, s10).Edge());
    step3Wire.Add(BRepBuilderAPI_MakeEdge(s10, s11).Edge());
    step3Wire.Add(BRepBuilderAPI_MakeEdge(s11, s12).Edge());
    step3Wire.Add(BRepBuilderAPI_MakeEdge(s12, s9).Edge());

    BRepBuilderAPI_MakeFace step3Face(step3Wire.Wire());
    TopoDS_Shape step3 =
        BRepPrimAPI_MakePrism(step3Face.Face(), gp_Vec(0, 0, params.H3))
            .Shape();

    BRepAlgoAPI_Fuse fuser(steps, step3);
    steps = fuser.Shape();
  }

  // 合并基础和台阶
  BRepAlgoAPI_Fuse fuser(base, steps);
  if (!fuser.IsDone()) {
    throw Standard_ConstructionError("基础形状合并失败");
  }

  // 处理斜柱情况
  if (params.alpha1 != 0 || params.alpha2 != 0) {
    // 创建斜柱面
    double rad1 = params.alpha1 * M_PI / 180.0;
    double rad2 = params.alpha2 * M_PI / 180.0;

    gp_Pnt topCenter(0, 0, 0);
    gp_Pnt bottomCenter(0, 0, -params.H);

    // 计算斜柱方向
    gp_Vec dirVec(tan(rad1), tan(rad2), 1);
    gp_Pnt slopedTop = bottomCenter.Translated(dirVec * params.H);

    // 创建斜柱
    BRepOffsetAPI_ThruSections generator(Standard_True);

    // 底部截面
    gp_Circ bottomCircle(gp_Ax2(bottomCenter, gp_Dir(0, 0, 1)), params.b / 2);
    TopoDS_Edge bottomEdge = BRepBuilderAPI_MakeEdge(bottomCircle).Edge();
    TopoDS_Wire bottomWire = BRepBuilderAPI_MakeWire(bottomEdge).Wire();
    generator.AddWire(bottomWire);

    // 顶部截面
    gp_Circ topCircle(gp_Ax2(slopedTop, gp_Dir(0, 0, 1)), params.b / 2);
    TopoDS_Edge topEdge = BRepBuilderAPI_MakeEdge(topCircle).Edge();
    TopoDS_Wire topWire = BRepBuilderAPI_MakeWire(topEdge).Wire();
    generator.AddWire(topWire);

    generator.Build();
    if (!generator.IsDone()) {
      throw Standard_ConstructionError("斜柱创建失败");
    }

    // 替换原有柱体
    BRepAlgoAPI_Cut cutter(fuser.Shape(), steps);
    BRepAlgoAPI_Fuse finalFuser(cutter.Shape(), generator.Shape());
    return finalFuser.Shape();
  }

  return fuser.Shape();
}

/**
 * @brief 创建带定位的台阶底板基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape
create_step_plate_foundation(const step_plate_foundation_params &params,
                             const gp_Pnt &position,
                             const gp_Dir &direction = gp_Dir(0, 0, 1)) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_step_plate_foundation(params);

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
TopoDS_Shape
create_sloped_base_foundation(const sloped_base_foundation_params &params) {
  // 参数验证
  if (params.H1 <= 0 || params.H2 <= 0 || params.H3 <= 0) {
    throw Standard_ConstructionError("高度参数必须为正数");
  }
  if (params.b <= 0 || params.L1 <= 0 || params.L2 <= 0 || params.B1 <= 0 ||
      params.B2 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }

  // 创建斜坡底板
  BRepBuilderAPI_MakeWire baseWire;

  // 底部四边形顶点
  gp_Pnt p1(-params.B1 / 2, -params.L1 / 2, -params.H1);
  gp_Pnt p2(params.B1 / 2, -params.L1 / 2, -params.H1);
  gp_Pnt p3(params.B2 / 2, params.L2 / 2, -params.H1 - params.H2);
  gp_Pnt p4(-params.B2 / 2, params.L2 / 2, -params.H1 - params.H2);

  baseWire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  baseWire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
  baseWire.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
  baseWire.Add(BRepBuilderAPI_MakeEdge(p4, p1).Edge());

  BRepBuilderAPI_MakeFace baseFace(baseWire.Wire());
  TopoDS_Shape base = BRepPrimAPI_MakePrism(baseFace.Face(),
                                            gp_Vec(0, 0, params.H1 + params.H2))
                          .Shape();

  // 创建柱体
  TopoDS_Shape column;
  if (params.alpha1 == 0 && params.alpha2 == 0) {
    // 直柱
    gp_Ax2 axis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
    column = BRepPrimAPI_MakeCylinder(axis, params.b / 2, params.H3).Shape();
  } else {
    // 斜柱
    double tanAlpha1 = tan(params.alpha1 * M_PI / 180.0);
    double tanAlpha2 = tan(params.alpha2 * M_PI / 180.0);
    gp_Vec slopeDir(tanAlpha1, tanAlpha2, 1.0);
    slopeDir.Normalize();

    gp_Ax2 axis(gp_Pnt(0, 0, 0), slopeDir);
    column = BRepPrimAPI_MakeCylinder(axis, params.b / 2, params.H3).Shape();
  }

  // 合并柱体和底板
  BRepAlgoAPI_Fuse fuser(base, column);

  if (!fuser.IsDone()) {
    throw Standard_ConstructionError("基础形状合并失败");
  }

  return fuser.Shape();
}

/**
 * @brief 创建带定位的斜坡底板基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape
create_sloped_base_foundation(const sloped_base_foundation_params &params,
                              const gp_Pnt &position,
                              const gp_Dir &direction = gp_Dir(0, 0, 1)) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_sloped_base_foundation(params);

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
TopoDS_Shape create_composite_caisson_foundation(
    const composite_caisson_foundation_params &params) {
  // 参数验证
  if (params.H1 <= 0 || params.H2 <= 0 || params.H3 <= 0 || params.H4 <= 0) {
    throw Standard_ConstructionError("高度参数必须为正数");
  }
  if (params.b <= 0 || params.D <= 0 || params.t <= 0 || params.B1 <= 0 ||
      params.B2 <= 0 || params.L1 <= 0 || params.L2 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }

  // 创建上部沉井
  gp_Ax2 axis1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  TopoDS_Shape upperCaisson =
      BRepPrimAPI_MakeCylinder(axis1, params.D / 2, params.H1).Shape();

  // 创建中部过渡段
  BRepBuilderAPI_MakeWire transitionWire;
  double outerRadius = params.D / 2;
  double innerRadius = (params.D - 2 * params.t) / 2;

  // 外轮廓
  gp_Pnt p1(outerRadius, 0, params.H1);
  gp_Pnt p2(params.B1 / 2, 0, params.H1 + params.H2);
  transitionWire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());

  // 旋转形成过渡段
  gp_Ax1 rotationAxis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  TopoDS_Shape transition =
      BRepPrimAPI_MakeRevol(transitionWire.Wire(), rotationAxis).Shape();

  // 创建下部扩大基础
  BRepBuilderAPI_MakeWire baseWire;
  double halfB2 = params.B2 / 2;
  double halfL2 = params.L2 / 2;
  baseWire.Add(
      BRepBuilderAPI_MakeEdge(gp_Pnt(-halfB2, -halfL2, params.H1 + params.H2),
                              gp_Pnt(halfB2, -halfL2, params.H1 + params.H2))
          .Edge());
  // ... 创建完整矩形轮廓
  BRepBuilderAPI_MakeFace baseFace(baseWire.Wire());
  TopoDS_Shape base =
      BRepPrimAPI_MakePrism(baseFace.Face(), gp_Vec(0, 0, params.H3)).Shape();

  // 创建内部空腔
  gp_Ax2 innerAxis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  TopoDS_Shape innerCavity =
      BRepPrimAPI_MakeCylinder(innerAxis, innerRadius, params.H1 + params.H2)
          .Shape();

  // 合并所有部件
  BRepAlgoAPI_Fuse fuser(upperCaisson, transition);
  fuser = BRepAlgoAPI_Fuse(fuser.Shape(), base);

  // 减去内部空腔
  BRepAlgoAPI_Cut cutter(fuser.Shape(), innerCavity);
  if (!cutter.IsDone()) {
    throw Standard_ConstructionError("基础形状切割失败");
  }

  return cutter.Shape();
}

/**
 * @brief 创建带定位的复合式沉井基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_composite_caisson_foundation(
    const composite_caisson_foundation_params &params, const gp_Pnt &position,
    const gp_Dir &direction = gp_Dir(0, 0, 1)) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_composite_caisson_foundation(params);

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
TopoDS_Shape create_raft_foundation(const raft_foundation_params &params) {
  // 参数验证
  if (params.H1 <= 0 || params.H2 <= 0) {
    throw Standard_ConstructionError("底板高度参数必须为正数");
  }
  if (params.b1 <= 0 || params.b2 <= 0 || params.B1 <= 0 || params.B2 <= 0 ||
      params.L1 <= 0 || params.L2 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }

  // 创建底板
  BRepBuilderAPI_MakeWire baseWire;
  double halfB1 = params.B1 / 2;
  double halfL1 = params.L1 / 2;

  // 底板轮廓
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

  // 创建边梁
  BRepBuilderAPI_MakeWire beamWire;
  double halfB2 = params.B2 / 2;
  double halfL2 = params.L2 / 2;

  // 边梁轮廓
  gp_Pnt p5(-halfB2, -halfL2, -params.H1 - params.H2);
  gp_Pnt p6(halfB2, -halfL2, -params.H1 - params.H2);
  gp_Pnt p7(halfB2, halfL2, -params.H1 - params.H2);
  gp_Pnt p8(-halfB2, halfL2, -params.H1 - params.H2);

  beamWire.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge());
  beamWire.Add(BRepBuilderAPI_MakeEdge(p6, p7).Edge());
  beamWire.Add(BRepBuilderAPI_MakeEdge(p7, p8).Edge());
  beamWire.Add(BRepBuilderAPI_MakeEdge(p8, p5).Edge());

  BRepBuilderAPI_MakeFace beamFace(beamWire.Wire());
  TopoDS_Shape beam =
      BRepPrimAPI_MakePrism(beamFace.Face(), gp_Vec(0, 0, params.H2)).Shape();

  // 合并底板和边梁
  BRepAlgoAPI_Fuse fuser(base, beam);

  // 创建主梁（当H3>0时）
  if (params.H3 > 0) {
    // 纵向主梁
    TopoDS_Shape longBeam =
        create_rectangular_beam(params.b1, params.H3, params.L1,
                                gp_Pnt(0, 0, -params.H1 - params.H3 / 2));

    // 横向主梁
    TopoDS_Shape crossBeam =
        create_rectangular_beam(params.b2, params.H3, params.B1,
                                gp_Pnt(0, 0, -params.H1 - params.H3 / 2));

    // 合并主梁
    fuser = BRepAlgoAPI_Fuse(fuser.Shape(), longBeam);
    fuser = BRepAlgoAPI_Fuse(fuser.Shape(), crossBeam);
  }

  if (!fuser.IsDone()) {
    throw Standard_ConstructionError("基础形状合并失败");
  }

  return fuser.Shape();
}

/**
 * @brief 创建带定位的筏板基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_raft_foundation(const raft_foundation_params &params,
                                    const gp_Pnt &position,
                                    const gp_Dir &direction = gp_Dir(0, 0, 1)) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_raft_foundation(params);

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
create_direct_buried_foundation(const direct_buried_foundation_params &params) {
  // 参数验证
  if (params.H1 <= 0) {
    throw Standard_ConstructionError("基础高度H1必须为正数");
  }
  if (params.t <= 0) {
    throw Standard_ConstructionError("壁厚t必须为正数");
  }

  // 创建基础主体
  gp_Ax2 axis(gp_Pnt(0, 0, -params.H1), gp_Dir(0, 0, 1));
  TopoDS_Shape mainBody =
      BRepPrimAPI_MakeCylinder(axis, params.d / 2, params.H1).Shape();

  // 创建固定盘（如果有）
  if (params.hasBasePlate) {
    TopoDS_Shape basePlate;
    if (params.isCircularPlate) { // 圆形固定盘
      gp_Ax2 plateAxis(gp_Pnt(0, 0, -params.H1 - params.H2), gp_Dir(0, 0, 1));
      basePlate =
          BRepPrimAPI_MakeCylinder(plateAxis, params.D / 2, params.H2).Shape();
    } else { // 方形固定盘
      BRepBuilderAPI_MakeWire wire;
      double halfB = params.B / 2;
      wire.Add(BRepBuilderAPI_MakeEdge(
                   gp_Pnt(-halfB, -halfB, -params.H1 - params.H2),
                   gp_Pnt(halfB, -halfB, -params.H1 - params.H2))
                   .Edge());
      // ... 创建方形轮廓
      BRepBuilderAPI_MakeFace face(wire.Wire());
      basePlate =
          BRepPrimAPI_MakePrism(face.Face(), gp_Vec(0, 0, params.H2)).Shape();
    }

    // 合并主体和固定盘
    BRepAlgoAPI_Fuse fuser(mainBody, basePlate);
    if (!fuser.IsDone()) {
      throw Standard_ConstructionError("固定盘合并失败");
    }
    return fuser.Shape();
  }

  return mainBody;
}

/**
 * @brief 创建带定位的直埋式基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape
create_direct_buried_foundation(const direct_buried_foundation_params &params,
                                const gp_Pnt &position,
                                const gp_Dir &direction = gp_Dir(0, 0, 1)) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_direct_buried_foundation(params);

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
TopoDS_Shape
create_steel_sleeve_foundation(const steel_sleeve_foundation_params &params) {
  // 参数验证
  if (params.H1 <= 0 || params.H2 <= 0 || params.H3 <= 0 || params.H4 <= 0) {
    throw Standard_ConstructionError("高度参数必须为正数");
  }
  if (params.d <= 0 || params.t <= 0) {
    throw Standard_ConstructionError("钢套筒尺寸参数必须为正数");
  }

  // 创建钢套筒
  gp_Ax2 axis(gp_Pnt(0, 0, -params.H1), gp_Dir(0, 0, 1));
  TopoDS_Shape outerTube =
      BRepPrimAPI_MakeCylinder(axis, params.d / 2, params.H1).Shape();

  // 创建内筒（空心部分）
  TopoDS_Shape innerTube =
      BRepPrimAPI_MakeCylinder(axis, (params.d - 2 * params.t) / 2, params.H1)
          .Shape();

  // 布尔差运算得到空心钢套筒
  BRepAlgoAPI_Cut cutter(outerTube, innerTube);
  if (!cutter.IsDone()) {
    throw Standard_ConstructionError("钢套筒创建失败");
  }
  TopoDS_Shape sleeve = cutter.Shape();

  // 创建底部扩大段（H2部分）
  if (params.D1 > 0 && params.D2 > 0) {
    gp_Ax2 baseAxis(gp_Pnt(0, 0, -params.H1 - params.H2), gp_Dir(0, 0, 1));
    TopoDS_Shape base =
        BRepPrimAPI_MakeCylinder(baseAxis, params.D1 / 2, params.H2).Shape();

    // 合并钢套筒和底部扩大段
    BRepAlgoAPI_Fuse fuser(sleeve, base);
    sleeve = fuser.Shape();
  }

  // 创建顶部扩大段（H3部分）
  if (params.B1 > 0 && params.B2 > 0) {
    gp_Ax2 topAxis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
    TopoDS_Shape top =
        BRepPrimAPI_MakeCylinder(topAxis, params.B1 / 2, params.H3).Shape();

    // 合并钢套筒和顶部扩大段
    BRepAlgoAPI_Fuse fuser(sleeve, top);
    sleeve = fuser.Shape();
  }

  // 创建内部填充（H4部分）
  gp_Ax2 fillAxis(gp_Pnt(0, 0, -params.H4), gp_Dir(0, 0, 1));
  TopoDS_Shape fill = BRepPrimAPI_MakeCylinder(
                          fillAxis, (params.d - 2 * params.t) / 2, params.H4)
                          .Shape();

  // 合并填充部分
  BRepAlgoAPI_Fuse fuser(sleeve, fill);
  return fuser.Shape();
}

/**
 * @brief 创建带定位的钢套筒式基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape
create_steel_sleeve_foundation(const steel_sleeve_foundation_params &params,
                               const gp_Pnt &position,
                               const gp_Dir &direction = gp_Dir(0, 0, 1)) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_steel_sleeve_foundation(params);

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
TopoDS_Shape create_precast_column_foundation(
    const precast_column_foundation_params &params) {
  // 参数验证
  if (params.H1 <= 0 || params.H2 <= 0 || params.H3 <= 0) {
    throw Standard_ConstructionError("高度参数必须为正数");
  }
  if (params.d <= 0 || params.B1 <= 0 || params.B2 <= 0 || params.L1 <= 0 ||
      params.L2 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }

  // 创建上部柱体
  gp_Ax2 columnAxis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  TopoDS_Shape column =
      BRepPrimAPI_MakeCylinder(columnAxis, params.d / 2, params.H1).Shape();

  // 创建中部过渡段
  BRepBuilderAPI_MakeWire transitionWire;
  double halfB1 = params.B1 / 2;
  double halfL1 = params.L1 / 2;
  double halfB2 = params.B2 / 2;
  double halfL2 = params.L2 / 2;

  // 过渡段底部四边形
  gp_Pnt p1(-halfB1, -halfL1, -params.H2);
  gp_Pnt p2(halfB1, -halfL1, -params.H2);
  gp_Pnt p3(halfB1, halfL1, -params.H2);
  gp_Pnt p4(-halfB1, halfL1, -params.H2);

  // 过渡段顶部四边形
  gp_Pnt p5(-halfB2, -halfL2, -params.H2 - params.H3);
  gp_Pnt p6(halfB2, -halfL2, -params.H2 - params.H3);
  gp_Pnt p7(halfB2, halfL2, -params.H2 - params.H3);
  gp_Pnt p8(-halfB2, halfL2, -params.H2 - params.H3);

  // 创建过渡段侧面
  BRepBuilderAPI_Sewing sewer;

  // 前侧面
  TopoDS_Edge e1 = BRepBuilderAPI_MakeEdge(p1, p2).Edge();
  TopoDS_Edge e2 = BRepBuilderAPI_MakeEdge(p2, p6).Edge();
  TopoDS_Edge e3 = BRepBuilderAPI_MakeEdge(p6, p5).Edge();
  TopoDS_Edge e4 = BRepBuilderAPI_MakeEdge(p5, p1).Edge();
  BRepBuilderAPI_MakeWire frontWire;
  frontWire.Add(e1);
  frontWire.Add(e2);
  frontWire.Add(e3);
  frontWire.Add(e4);
  TopoDS_Face frontFace = BRepBuilderAPI_MakeFace(frontWire.Wire());
  sewer.Add(frontFace);

  // 右侧面
  TopoDS_Edge e5 = BRepBuilderAPI_MakeEdge(p2, p3).Edge();
  TopoDS_Edge e6 = BRepBuilderAPI_MakeEdge(p3, p7).Edge();
  TopoDS_Edge e7 = BRepBuilderAPI_MakeEdge(p7, p6).Edge();
  TopoDS_Edge e8 = BRepBuilderAPI_MakeEdge(p6, p2).Edge();
  BRepBuilderAPI_MakeWire rightWire;
  rightWire.Add(e5);
  rightWire.Add(e6);
  rightWire.Add(e7);
  rightWire.Add(e8);
  TopoDS_Face rightFace = BRepBuilderAPI_MakeFace(rightWire.Wire());
  sewer.Add(rightFace);

  // 后侧面
  TopoDS_Edge e9 = BRepBuilderAPI_MakeEdge(p3, p4).Edge();
  TopoDS_Edge e10 = BRepBuilderAPI_MakeEdge(p4, p8).Edge();
  TopoDS_Edge e11 = BRepBuilderAPI_MakeEdge(p8, p7).Edge();
  TopoDS_Edge e12 = BRepBuilderAPI_MakeEdge(p7, p3).Edge();
  BRepBuilderAPI_MakeWire backWire;
  backWire.Add(e9);
  backWire.Add(e10);
  backWire.Add(e11);
  backWire.Add(e12);
  TopoDS_Face backFace = BRepBuilderAPI_MakeFace(backWire.Wire());
  sewer.Add(backFace);

  // 左侧面
  TopoDS_Edge e13 = BRepBuilderAPI_MakeEdge(p4, p1).Edge();
  TopoDS_Edge e14 = BRepBuilderAPI_MakeEdge(p1, p5).Edge();
  TopoDS_Edge e15 = BRepBuilderAPI_MakeEdge(p5, p8).Edge();
  TopoDS_Edge e16 = BRepBuilderAPI_MakeEdge(p8, p4).Edge();
  BRepBuilderAPI_MakeWire leftWire;
  leftWire.Add(e13);
  leftWire.Add(e14);
  leftWire.Add(e15);
  leftWire.Add(e16);
  TopoDS_Face leftFace = BRepBuilderAPI_MakeFace(leftWire.Wire());
  sewer.Add(leftFace);

  // 创建过渡段底面
  BRepBuilderAPI_MakeWire bottomWire;
  bottomWire.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge());
  bottomWire.Add(BRepBuilderAPI_MakeEdge(p6, p7).Edge());
  bottomWire.Add(BRepBuilderAPI_MakeEdge(p7, p8).Edge());
  bottomWire.Add(BRepBuilderAPI_MakeEdge(p8, p5).Edge());
  TopoDS_Face bottomFace = BRepBuilderAPI_MakeFace(bottomWire.Wire()).Face();
  sewer.Add(bottomFace);

  // 合并过渡段
  sewer.Perform();
  TopoDS_Shape transition = sewer.SewedShape();

  // 合并所有部件
  BRepAlgoAPI_Fuse fuser(column, transition);

  if (!fuser.IsDone()) {
    throw Standard_ConstructionError("基础形状合并失败");
  }

  return fuser.Shape();
}

/**
 * @brief 创建带定位的装配式直柱固接型基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape
create_precast_column_foundation(const precast_column_foundation_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction = gp_Dir(0, 0, 1)) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_precast_column_foundation(params);

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
TopoDS_Shape create_precast_pinned_foundation(
    const precast_pinned_foundation_params &params) {
  // 参数验证
  if (params.H1 <= 0 || params.H2 <= 0 || params.H3 <= 0) {
    throw Standard_ConstructionError("高度参数必须为正数");
  }
  if (params.d <= 0 || params.B1 <= 0 || params.B2 <= 0 || params.L1 <= 0 ||
      params.L2 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }

  // 创建上部柱体
  gp_Ax2 columnAxis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  TopoDS_Shape column =
      BRepPrimAPI_MakeCylinder(columnAxis, params.d / 2, params.H1).Shape();

  // 创建中部过渡段
  BRepBuilderAPI_Sewing sewer;

  // 过渡段顶点
  double halfB1 = params.B1 / 2;
  double halfL1 = params.L1 / 2;
  double halfB2 = params.B2 / 2;
  double halfL2 = params.L2 / 2;

  gp_Pnt p1(-halfB1, -halfL1, -params.H2);
  gp_Pnt p2(halfB1, -halfL1, -params.H2);
  gp_Pnt p3(halfB1, halfL1, -params.H2);
  gp_Pnt p4(-halfB1, halfL1, -params.H2);
  gp_Pnt p5(-halfB2, -halfL2, -params.H2 - params.H3);
  gp_Pnt p6(halfB2, -halfL2, -params.H2 - params.H3);
  gp_Pnt p7(halfB2, halfL2, -params.H2 - params.H3);
  gp_Pnt p8(-halfB2, halfL2, -params.H2 - params.H3);

  // 前侧面
  TopoDS_Edge e1 = BRepBuilderAPI_MakeEdge(p1, p2).Edge();
  TopoDS_Edge e2 = BRepBuilderAPI_MakeEdge(p2, p6).Edge();
  TopoDS_Edge e3 = BRepBuilderAPI_MakeEdge(p6, p5).Edge();
  TopoDS_Edge e4 = BRepBuilderAPI_MakeEdge(p5, p1).Edge();
  BRepBuilderAPI_MakeWire frontWire;
  frontWire.Add(e1);
  frontWire.Add(e2);
  frontWire.Add(e3);
  frontWire.Add(e4);
  TopoDS_Face frontFace = BRepBuilderAPI_MakeFace(frontWire.Wire());
  sewer.Add(frontFace);

  // 右侧面
  TopoDS_Edge e5 = BRepBuilderAPI_MakeEdge(p2, p3).Edge();
  TopoDS_Edge e6 = BRepBuilderAPI_MakeEdge(p3, p7).Edge();
  TopoDS_Edge e7 = BRepBuilderAPI_MakeEdge(p7, p6).Edge();
  TopoDS_Edge e8 = BRepBuilderAPI_MakeEdge(p6, p2).Edge();
  BRepBuilderAPI_MakeWire rightWire;
  rightWire.Add(e5);
  rightWire.Add(e6);
  rightWire.Add(e7);
  rightWire.Add(e8);
  TopoDS_Face rightFace = BRepBuilderAPI_MakeFace(rightWire.Wire());
  sewer.Add(rightFace);

  // 后侧面
  TopoDS_Edge e9 = BRepBuilderAPI_MakeEdge(p3, p4).Edge();
  TopoDS_Edge e10 = BRepBuilderAPI_MakeEdge(p4, p8).Edge();
  TopoDS_Edge e11 = BRepBuilderAPI_MakeEdge(p8, p7).Edge();
  TopoDS_Edge e12 = BRepBuilderAPI_MakeEdge(p7, p3).Edge();
  BRepBuilderAPI_MakeWire backWire;
  backWire.Add(e9);
  backWire.Add(e10);
  backWire.Add(e11);
  backWire.Add(e12);
  TopoDS_Face backFace = BRepBuilderAPI_MakeFace(backWire.Wire());
  sewer.Add(backFace);

  // 左侧面
  TopoDS_Edge e13 = BRepBuilderAPI_MakeEdge(p4, p1).Edge();
  TopoDS_Edge e14 = BRepBuilderAPI_MakeEdge(p1, p5).Edge();
  TopoDS_Edge e15 = BRepBuilderAPI_MakeEdge(p5, p8).Edge();
  TopoDS_Edge e16 = BRepBuilderAPI_MakeEdge(p8, p4).Edge();
  BRepBuilderAPI_MakeWire leftWire;
  leftWire.Add(e13);
  leftWire.Add(e14);
  leftWire.Add(e15);
  leftWire.Add(e16);
  TopoDS_Face leftFace = BRepBuilderAPI_MakeFace(leftWire.Wire());
  sewer.Add(leftFace);

  // 创建过渡段底面
  BRepBuilderAPI_MakeWire bottomWire;
  bottomWire.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge());
  bottomWire.Add(BRepBuilderAPI_MakeEdge(p6, p7).Edge());
  bottomWire.Add(BRepBuilderAPI_MakeEdge(p7, p8).Edge());
  bottomWire.Add(BRepBuilderAPI_MakeEdge(p8, p5).Edge());
  TopoDS_Face bottomFace = BRepBuilderAPI_MakeFace(bottomWire.Wire()).Face();
  sewer.Add(bottomFace);

  // 合并过渡段
  sewer.Perform();
  TopoDS_Shape transition = sewer.SewedShape();

  // 创建卡盘(如果有)
  if (params.L > 0 && params.H > 0 && params.B > 0) {
    gp_Pnt clampCenter(0, 0, -params.H2 - params.H3 - params.H / 2);
    TopoDS_Shape clamp =
        create_rectangular_beam(params.B, params.H, params.L, clampCenter);

    // 合并所有部件
    BRepAlgoAPI_Fuse fuser(column, transition);
    fuser = BRepAlgoAPI_Fuse(fuser.Shape(), clamp);
    return fuser.Shape();
  }

  // 合并柱体和过渡段
  BRepAlgoAPI_Fuse fuser(column, transition);
  return fuser.Shape();
}

/**
 * @brief 创建带定位的装配式直柱铰接型基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape
create_precast_pinned_foundation(const precast_pinned_foundation_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction = gp_Dir(0, 0, 1)) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_precast_pinned_foundation(params);

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
TopoDS_Shape create_precast_metal_support_foundation(
    const precast_metal_support_foundation_params &params) {
  // 参数验证
  if (params.H1 <= 0 || params.H2 <= 0 || params.H3 <= 0 || params.H4 <= 0) {
    throw Standard_ConstructionError("高度参数必须为正数");
  }
  if (params.b1 <= 0 || params.b2 <= 0 || params.B1 <= 0 || params.B2 <= 0 ||
      params.L1 <= 0 || params.L2 <= 0 || params.S1 <= 0 || params.S2 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }
  if (params.n1 <= 0 || params.n2 <= 0) {
    throw Standard_ConstructionError("数量参数必须为正数");
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

  // 创建支架立柱
  std::vector<TopoDS_Shape> columns;
  double halfB2 = params.B2 / 2;
  double halfL2 = params.L2 / 2;

  // 四个角柱位置
  std::vector<gp_Pnt> columnPositions = {
      gp_Pnt(-halfB2, -halfL2, 0), gp_Pnt(halfB2, -halfL2, 0),
      gp_Pnt(halfB2, halfL2, 0), gp_Pnt(-halfB2, halfL2, 0)};

  for (const auto &pos : columnPositions) {
    gp_Ax2 axis(pos, gp_Dir(0, 0, 1));
    TopoDS_Shape column =
        BRepPrimAPI_MakeCylinder(axis, params.b1 / 2, params.H2).Shape();
    columns.push_back(column);
  }

  // 创建水平连接梁
  std::vector<TopoDS_Shape> beams;
  for (int i = 0; i < 4; i++) {
    gp_Pnt start = columnPositions[i];
    gp_Pnt end = columnPositions[(i + 1) % 4];
    TopoDS_Shape beam =
        create_rectangular_beam(params.b2, params.b2, start.Distance(end),
                                gp_Pnt((start.X() + end.X()) / 2,
                                       (start.Y() + end.Y()) / 2, params.H3));
    beams.push_back(beam);
  }

  // 创建斜撑
  std::vector<TopoDS_Shape> braces;
  for (int i = 0; i < params.n1; i++) {
    double zPos = params.HX[i];
    for (int j = 0; j < 4; j++) {
      gp_Pnt top(columnPositions[j].X(), columnPositions[j].Y(), zPos);
      gp_Pnt bottom(columnPositions[(j + 1) % 4].X(),
                    columnPositions[(j + 1) % 4].Y(), zPos - params.H4);
      TopoDS_Shape brace = create_rectangular_beam(
          params.S2, params.S2, top.Distance(bottom),
          gp_Pnt((top.X() + bottom.X()) / 2, (top.Y() + bottom.Y()) / 2,
                 (top.Z() + bottom.Z()) / 2));
      braces.push_back(brace);
    }
  }

  // 创建板条
  std::vector<TopoDS_Shape> slats;
  if (params.n2 > 0) {
    double slatSpacing = params.H2 / (params.n2 + 1);
    for (int i = 1; i <= params.n2; i++) {
      double zPos = slatSpacing * i;
      for (int j = 0; j < 4; j++) {
        gp_Pnt start(columnPositions[j].X(), columnPositions[j].Y(), zPos);
        gp_Pnt end(columnPositions[(j + 1) % 4].X(),
                   columnPositions[(j + 1) % 4].Y(), zPos);
        TopoDS_Shape slat = create_rectangular_beam(
            params.S1, params.S1 / 5, start.Distance(end),
            gp_Pnt((start.X() + end.X()) / 2, (start.Y() + end.Y()) / 2, zPos));
        slats.push_back(slat);
      }
    }
  }

  // 合并所有部件
  BRepAlgoAPI_Fuse fuser(base, columns[0]);
  for (int i = 1; i < columns.size(); i++) {
    fuser = BRepAlgoAPI_Fuse(fuser.Shape(), columns[i]);
  }
  for (const auto &beam : beams) {
    fuser = BRepAlgoAPI_Fuse(fuser.Shape(), beam);
  }
  for (const auto &brace : braces) {
    fuser = BRepAlgoAPI_Fuse(fuser.Shape(), brace);
  }
  for (const auto &slat : slats) {
    fuser = BRepAlgoAPI_Fuse(fuser.Shape(), slat);
  }

  if (!fuser.IsDone()) {
    throw Standard_ConstructionError("基础形状合并失败");
  }

  return fuser.Shape();
}

/**
 * @brief 创建带定位的装配式金属支架型基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_precast_metal_support_foundation(
    const precast_metal_support_foundation_params &params,
    const gp_Pnt &position, const gp_Dir &direction = gp_Dir(0, 0, 1)) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_precast_metal_support_foundation(params);

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
TopoDS_Shape create_precast_concrete_support_foundation(
    const precast_concrete_support_foundation_params &params) {
  // 参数验证
  if (params.H1 <= 0 || params.H2 <= 0 || params.H3 <= 0 || params.H4 <= 0 ||
      params.H5 <= 0) {
    throw Standard_ConstructionError("高度参数必须为正数");
  }
  if (params.b1 <= 0 || params.b2 <= 0 || params.b3 <= 0 || params.B1 <= 0 ||
      params.B2 <= 0 || params.L1 <= 0 || params.L2 <= 0 || params.S1 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }
  if (params.n1 <= 0) {
    throw Standard_ConstructionError("数量参数必须为正数");
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

  // 创建立柱
  std::vector<TopoDS_Shape> columns;
  double halfB2 = params.B2 / 2;
  double halfL2 = params.L2 / 2;

  // 四个角柱位置
  std::vector<gp_Pnt> columnPositions = {
      gp_Pnt(-halfB2, -halfL2, 0), gp_Pnt(halfB2, -halfL2, 0),
      gp_Pnt(halfB2, halfL2, 0), gp_Pnt(-halfB2, halfL2, 0)};

  for (const auto &pos : columnPositions) {
    gp_Ax2 axis(pos, gp_Dir(0, 0, 1));
    TopoDS_Shape column =
        BRepPrimAPI_MakeCylinder(axis, params.b1 / 2, params.H2).Shape();
    columns.push_back(column);
  }

  // 创建水平连接梁
  std::vector<TopoDS_Shape> beams;
  for (int i = 0; i < 4; i++) {
    gp_Pnt start = columnPositions[i];
    gp_Pnt end = columnPositions[(i + 1) % 4];
    TopoDS_Shape beam =
        create_rectangular_beam(params.b2, params.b2, start.Distance(end),
                                gp_Pnt((start.X() + end.X()) / 2,
                                       (start.Y() + end.Y()) / 2, params.H3));
    beams.push_back(beam);
  }

  // 创建混凝土构件支撑
  std::vector<TopoDS_Shape> supports;
  for (int i = 0; i < params.n1; i++) {
    double angle = 2 * M_PI * i / params.n1;
    double x = halfB2 * 0.8 * cos(angle);
    double y = halfL2 * 0.8 * sin(angle);

    gp_Pnt top(x, y, params.H4);
    gp_Pnt bottom(x, y, params.H5);
    TopoDS_Shape support =
        create_rectangular_beam(params.b3, params.b3, top.Distance(bottom),
                                gp_Pnt(x, y, (params.H4 + params.H5) / 2));
    supports.push_back(support);
  }

  // 创建顶部平台
  TopoDS_Shape platform = create_rectangular_beam(
      params.S1, params.S1, params.S1, gp_Pnt(0, 0, params.H4));

  // 合并所有部件
  BRepAlgoAPI_Fuse fuser(base, columns[0]);
  for (int i = 1; i < columns.size(); i++) {
    fuser = BRepAlgoAPI_Fuse(fuser.Shape(), columns[i]);
  }
  for (const auto &beam : beams) {
    fuser = BRepAlgoAPI_Fuse(fuser.Shape(), beam);
  }
  for (const auto &support : supports) {
    fuser = BRepAlgoAPI_Fuse(fuser.Shape(), support);
  }
  fuser = BRepAlgoAPI_Fuse(fuser.Shape(), platform);

  if (!fuser.IsDone()) {
    throw Standard_ConstructionError("基础形状合并失败");
  }

  return fuser.Shape();
}

/**
 * @brief 创建带定位的装配式混凝土构件支架型基础
 * @param params 基础参数结构体
 * @param position 基础顶面中心位置
 * @param direction 基础方向（默认Z轴向上）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_precast_concrete_support_foundation(
    const precast_concrete_support_foundation_params &params,
    const gp_Pnt &position, const gp_Dir &direction = gp_Dir(0, 0, 1)) {
  // 首先创建标准方向的基础
  TopoDS_Shape foundation = create_precast_concrete_support_foundation(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(position, direction);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(foundation, transformation);
  return transform.Shape();
}

/**
 * @brief 创建螺纹结构
 * @param radius 螺纹半径
 * @param length 螺纹长度
 * @param pitch 螺纹间距
 * @param position 螺纹起始位置
 * @return TopoDS_Shape 生成的螺纹形状
 */
TopoDS_Shape create_thread(double radius, double length, double pitch,
                           const gp_Pnt &position) {
  // 创建螺纹截面三角形
  BRepBuilderAPI_MakeWire threadWire;
  gp_Pnt p1(radius, 0, 0);
  gp_Pnt p2(radius + pitch / 4, 0, pitch / 2);
  gp_Pnt p3(radius, 0, pitch);
  threadWire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  threadWire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
  threadWire.Add(BRepBuilderAPI_MakeEdge(p3, p1).Edge());

  // 创建螺旋路径
  BRepBuilderAPI_MakeWire spineWire;
  gp_Pnt lastPoint(0, 0, 0);
  int turns = ceil(length / pitch);
  int segments = turns * 12; // 每圈12段

  for (int i = 0; i <= segments; i++) {
    double angle = 2 * M_PI * turns * i / segments;
    double z = length * i / segments;
    gp_Pnt point(radius * cos(angle), radius * sin(angle), z);
    if (i > 0) {
      spineWire.Add(BRepBuilderAPI_MakeEdge(lastPoint, point).Edge());
    }
    lastPoint = point;
  }

  // 创建管道生成器
  BRepOffsetAPI_MakePipeShell pipeMaker(spineWire.Wire());
  pipeMaker.SetTolerance(1e-6);
  pipeMaker.SetTransitionMode(BRepBuilderAPI_Transformed);
  pipeMaker.Add(threadWire.Wire());

  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("螺纹创建失败");
  }

  // 移动到指定位置
  gp_Trsf transform;
  transform.SetTranslation(gp_Vec(position.X(), position.Y(), position.Z()));
  BRepBuilderAPI_Transform mover(pipeMaker.Shape(), transform);

  return mover.Shape();
}
/**
 * @brief 创建盘式绝缘子
 * @param diskDiameter 盘直径
 * @param diskThickness 盘厚度
 * @param diskCount 盘数量
 * @param rodDiameter 芯棒直径
 * @param rodLength 芯棒长度
 * @param hasThread 是否包含端部螺纹
 * @param threadLength 螺纹长度
 * @param threadPitch 螺纹间距
 * @return TopoDS_Shape 生成的绝缘子形状
 */
TopoDS_Shape create_disk_insulator(double diskDiameter, double diskThickness,
                                   int diskCount, double rodDiameter,
                                   double rodLength, bool hasThread = false,
                                   double threadLength = 10.0,
                                   double threadPitch = 2.0) {

  // 参数验证
  if (diskDiameter <= 0 || diskThickness <= 0 || diskCount <= 0 ||
      rodDiameter <= 0 || rodLength <= 0) {
    throw Standard_ConstructionError("绝缘子参数必须为正数");
  }

  // 创建芯棒
  gp_Ax2 rodAxis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  TopoDS_Shape rod =
      BRepPrimAPI_MakeCylinder(rodAxis, rodDiameter / 2, rodLength).Shape();

  // 创建绝缘盘
  BRepAlgoAPI_Fuse fuser;
  for (int i = 0; i < diskCount; i++) {
    double zPos = i * (diskThickness * 1.2);
    gp_Ax2 diskAxis(gp_Pnt(0, 0, zPos), gp_Dir(0, 0, 1));
    TopoDS_Shape disk =
        BRepPrimAPI_MakeCylinder(diskAxis, diskDiameter / 2, diskThickness)
            .Shape();
    if (i == 0) {
      fuser = BRepAlgoAPI_Fuse(rod, disk);
    } else {
      fuser = BRepAlgoAPI_Fuse(fuser.Shape(), disk);
    }
  }

  // 添加端部螺纹
  if (hasThread) {
    // 上部螺纹
    TopoDS_Shape upperThread = create_thread(
        rodDiameter / 2, threadLength, threadPitch, gp_Pnt(0, 0, rodLength));
    fuser = BRepAlgoAPI_Fuse(fuser.Shape(), upperThread);

    // 下部螺纹
    TopoDS_Shape lowerThread =
        create_thread(rodDiameter / 2, threadLength, threadPitch,
                      gp_Pnt(0, 0, -threadLength));
    fuser = BRepAlgoAPI_Fuse(fuser.Shape(), lowerThread);
  }

  return fuser.Shape();
}

/**
 * @brief 创建棒式绝缘子
 * @param rodDiameter 芯棒直径
 * @param rodLength 芯棒长度
 * @param shedDiameter 伞裙直径
 * @param shedThickness 伞裙厚度
 * @param shedCount 伞裙数量
 * @param hasThread 是否包含端部螺纹
 * @param threadLength 螺纹长度
 * @param threadPitch 螺纹间距
 * @return TopoDS_Shape 生成的绝缘子形状
 */
TopoDS_Shape create_rod_insulator(double rodDiameter, double rodLength,
                                  double shedDiameter, double shedThickness,
                                  int shedCount, bool hasThread = false,
                                  double threadLength = 10.0,
                                  double threadPitch = 2.0) {

  // 参数验证
  if (rodDiameter <= 0 || rodLength <= 0 || shedDiameter <= 0 ||
      shedThickness <= 0 || shedCount <= 0) {
    throw Standard_ConstructionError("绝缘子参数必须为正数");
  }

  // 创建芯棒
  gp_Ax2 rodAxis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  TopoDS_Shape rod =
      BRepPrimAPI_MakeCylinder(rodAxis, rodDiameter / 2, rodLength).Shape();

  // 创建伞裙
  BRepAlgoAPI_Fuse fuser;
  for (int i = 0; i < shedCount; i++) {
    double zPos = i * (shedThickness * 3);
    double currentDiameter = shedDiameter * (1.0 - 0.1 * (i % 3));

    // 创建伞裙截面
    BRepBuilderAPI_MakeWire wire;
    gp_Pnt p1(currentDiameter / 2, 0, zPos);
    gp_Pnt p2(currentDiameter / 2 * 0.8, 0, zPos + shedThickness);
    wire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());

    // 旋转形成伞裙
    gp_Ax1 axis(gp_Pnt(0, 0, zPos), gp_Dir(0, 0, 1));
    TopoDS_Shape shed =
        BRepPrimAPI_MakeRevol(wire.Wire(), axis, 2 * M_PI).Shape();

    if (i == 0) {
      fuser = BRepAlgoAPI_Fuse(rod, shed);
    } else {
      fuser = BRepAlgoAPI_Fuse(fuser.Shape(), shed);
    }
  }

  // 添加端部螺纹
  if (hasThread) {
    // 上部螺纹
    TopoDS_Shape upperThread = create_thread(
        rodDiameter / 2, threadLength, threadPitch, gp_Pnt(0, 0, rodLength));
    fuser = BRepAlgoAPI_Fuse(fuser.Shape(), upperThread);

    // 下部螺纹
    TopoDS_Shape lowerThread =
        create_thread(rodDiameter / 2, threadLength, threadPitch,
                      gp_Pnt(0, 0, -threadLength));
    fuser = BRepAlgoAPI_Fuse(fuser.Shape(), lowerThread);
  }

  return fuser.Shape();
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

  // 计算悬垂度 (简化公式: sag = (weight * length²) / (8 * tension))
  double weightPerMeter = params.wireWeight / 1000.0; // kg/m
  double tension = params.ratedStrength * 0.25; // 假设使用25%的额定拉断力
  double sag = (weightPerMeter * 9.8 * length * length) / (8 * tension);

  // 创建导地线路径(带悬垂度)
  gp_Pnt midPoint((startPoint.X() + endPoint.X()) / 2,
                  (startPoint.Y() + endPoint.Y()) / 2,
                  (startPoint.Z() + endPoint.Z()) / 2 - sag);

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
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("导地线建模失败");
  }

  return pipeMaker.Shape();
}

/**
 * @brief 创建地脚螺栓
 * @param boltType 螺栓型号 (如"M22"表示直径22mm)
 * @return TopoDS_Shape 生成的螺栓形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_anchor_bolt(const std::string &boltType) {
  // 解析螺栓直径
  double diameter = 0;
  if (sscanf(boltType.c_str(), "M%lf", &diameter) != 1 || diameter <= 0) {
    throw Standard_ConstructionError(
        "Invalid bolt type format (should be like M22)");
  }

  // 根据螺栓直径自动计算其他参数
  double length = diameter * 10;        // 长度=直径×10
  double threadLength = diameter * 4;   // 螺纹长度=直径×4
  double headHeight = diameter * 0.7;   // 螺栓头高度=直径×0.7
  double headDiameter = diameter * 1.6; // 螺栓头直径=直径×1.6

  // 参数验证
  if (length <= 0 || threadLength <= 0 || headHeight <= 0 ||
      headDiameter <= 0) {
    throw Standard_ConstructionError("All dimensions must be positive");
  }
  if (threadLength > length) {
    throw Standard_ConstructionError(
        "Thread length cannot exceed total length");
  }
  if (headDiameter < diameter) {
    throw Standard_ConstructionError(
        "Head diameter cannot be smaller than bolt diameter");
  }

  // 创建螺栓杆(无螺纹部分)
  gp_Ax2 boltAxis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  TopoDS_Shape boltShaft =
      BRepPrimAPI_MakeCylinder(boltAxis, diameter / 2, length - threadLength)
          .Shape();

  // 创建螺纹部分
  gp_Ax2 threadAxis(gp_Pnt(0, 0, length - threadLength), gp_Dir(0, 0, 1));
  TopoDS_Shape thread = create_thread(diameter / 2, threadLength,
                                      diameter / 10, // 螺距约为直径的1/10
                                      gp_Pnt(0, 0, length - threadLength));

  gp_Pnt lastPoint(0, 0, 0);
  // 创建螺栓头(六角头)
  BRepBuilderAPI_MakeWire headWire;
  double radius = headDiameter / 2;
  for (int i = 0; i < 6; i++) {
    double angle = 2 * M_PI * i / 6;
    double x = radius * cos(angle);
    double y = radius * sin(angle);
    gp_Pnt p(x, y, -headHeight);
    if (i > 0) {
      headWire.Add(BRepBuilderAPI_MakeEdge(lastPoint, p).Edge());
    }
    lastPoint = p;
  }
  headWire.Add(
      BRepBuilderAPI_MakeEdge(lastPoint, gp_Pnt(radius, 0, -headHeight))
          .Edge());

  BRepBuilderAPI_MakeFace headFace(headWire.Wire());
  TopoDS_Shape boltHead =
      BRepPrimAPI_MakePrism(headFace.Face(), gp_Vec(0, 0, headHeight)).Shape();

  // 合并所有部件
  BRepAlgoAPI_Fuse fuser(boltShaft, thread);
  fuser = BRepAlgoAPI_Fuse(fuser.Shape(), boltHead);

  if (!fuser.IsDone()) {
    throw Standard_ConstructionError("Failed to assemble anchor bolt");
  }

  return fuser.Shape();
}

/**
 * @brief 创建带定位的地脚螺栓
 * @param boltType 螺栓型号 (如"M22")
 * @param position 螺栓底部中心位置
 * @param direction 螺栓方向(默认Z轴向上)
 * @return TopoDS_Shape
 */
TopoDS_Shape create_anchor_bolt(const std::string &boltType,
                                const gp_Pnt &position,
                                const gp_Dir &direction = gp_Dir(0, 0, 1)) {
  // 首先创建标准方向的螺栓
  TopoDS_Shape bolt = create_anchor_bolt(boltType);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(position, direction);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(bolt, transformation);
  return transform.Shape();
}

} // namespace topo
} // namespace flywave
