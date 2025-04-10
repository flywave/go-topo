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
  if (params.height <= 0.0 ||
      params.height > 2 * params.polarRadius - Precision::Confusion()) {
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
  TColgp_Array1OfPnt bottomVerts(1, 5);              // 闭合多边形需要回到起点
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
    // 创建路径圆弧（XY平面，中心在原点）
    gp_Circ pathCircle(gp_Ax2(gp::Origin(), gp::DZ()), params.ringRadius);
    GC_MakeArcOfCircle maker(pathCircle, 0.0, params.angle, true);
    if (!maker.IsDone()) {
      throw Standard_ConstructionError("Failed to create arc");
    }
    Handle_Geom_TrimmedCurve arc = maker.Value();

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
  if (params.filletRadius > 10 * Precision::Confusion()) {
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

  // 新伞裙生成方式（保持原参数但改用更真实的5点剖面）
  BRepAlgoAPI_Fuse fuser;
  double segmentHeight = params.height / (params.count * 2 + 1);

  for (int i = 0; i < params.count; ++i) {
    // 大伞裙位置（保持原计算方式）
    double zPos = (2 * i + 1) * segmentHeight;
    double skirtRadius =
        (i % 2 == 0) ? params.bigSkirtRadius : params.smallSkirtRadius;

    // 创建更真实的5点伞裙截面
    BRepBuilderAPI_MakeWire wire;
    gp_Pnt p1(skirtRadius, 0, zPos);                               // 伞裙外缘
    gp_Pnt p2(skirtRadius * 0.95, 0, zPos + segmentHeight * 0.1);  // 轻微上翘
    gp_Pnt p3(skirtRadius * 0.7, 0, zPos + segmentHeight * 0.3);   // 主要下凹
    gp_Pnt p4(params.radius * 1.2, 0, zPos + segmentHeight * 0.6); // 靠近主体
    gp_Pnt p5(params.radius, 0, zPos + segmentHeight * 0.8);       // 连接处

    wire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
    wire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
    wire.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
    wire.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge());

    // 旋转生成大伞裙
    gp_Ax1 rotAxis(gp_Pnt(0, 0, zPos), gp_Dir(0, 0, 1));
    TopoDS_Shape bigSkirt = BRepPrimAPI_MakeRevol(wire.Wire(), rotAxis).Shape();
    fuser = BRepAlgoAPI_Fuse(fuser.Shape(), bigSkirt);

    // 小伞裙位置（保持原计算方式）
    double smallZPos = (2 * i + 2) * segmentHeight;
    double smallSkirtRadius =
        (i % 2 == 0) ? params.smallSkirtRadius : params.bigSkirtRadius;

    // 创建小伞裙剖面（类似结构但更紧凑）
    BRepBuilderAPI_MakeWire smallWire;
    gp_Pnt sp1(smallSkirtRadius, 0, smallZPos);
    gp_Pnt sp2(smallSkirtRadius * 0.9, 0, smallZPos + segmentHeight * 0.15);
    gp_Pnt sp3(smallSkirtRadius * 0.6, 0, smallZPos + segmentHeight * 0.35);
    gp_Pnt sp4(params.radius * 1.1, 0, smallZPos + segmentHeight * 0.5);
    gp_Pnt sp5(params.radius, 0, smallZPos + segmentHeight * 0.6);

    smallWire.Add(BRepBuilderAPI_MakeEdge(sp1, sp2).Edge());
    smallWire.Add(BRepBuilderAPI_MakeEdge(sp2, sp3).Edge());
    smallWire.Add(BRepBuilderAPI_MakeEdge(sp3, sp4).Edge());
    smallWire.Add(BRepBuilderAPI_MakeEdge(sp4, sp5).Edge());

    // 旋转生成小伞裙
    TopoDS_Shape smallSkirt =
        BRepPrimAPI_MakeRevol(smallWire.Wire(), rotAxis).Shape();
    if (i == 0) {
      fuser = BRepAlgoAPI_Fuse(mainCylinder, smallSkirt);
    } else {
      fuser = BRepAlgoAPI_Fuse(fuser.Shape(), smallSkirt);
    }

    if (!fuser.IsDone()) {
      throw Standard_ConstructionError("Skirt fusion failed at position ");
    }
  }

  return fuser.Shape();
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

  // 初始化融合对象（修正构造函数问题）
  TopoDS_Shape fusedShape = mainCone;
  double segmentHeight = params.height / (params.count + 1);

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
    gp_Pnt p1(skirtRadius, 0, zPos);                               // 伞裙外缘
    gp_Pnt p2(skirtRadius * 0.95, 0, zPos + segmentHeight * 0.1);  // 上翘
    gp_Pnt p3(skirtRadius * 0.7, 0, zPos + segmentHeight * 0.3);   // 下凹
    gp_Pnt p4(currentRadius * 1.2, 0, zPos + segmentHeight * 0.6); // 过渡
    gp_Pnt p5(currentRadius, 0, zPos + segmentHeight * 0.8);       // 连接

    wire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
    wire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
    wire.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
    wire.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge());

    // 旋转生成伞裙（360度）
    gp_Ax1 rotAxis(gp_Pnt(0, 0, zPos), gp_Dir(0, 0, 1));
    TopoDS_Shape skirt = BRepPrimAPI_MakeRevol(wire.Wire(), rotAxis).Shape();

    // 渐进式布尔融合（修正后的方式）
    BRepAlgoAPI_Fuse fuseOperation(fusedShape, skirt);
    if (!fuseOperation.IsDone()) {
      throw Standard_ConstructionError("Skirt fusion failed at position ");
    }
    fusedShape = fuseOperation.Shape();
  }

  return fusedShape;
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

  // 计算总高度（保持不变）
  double totalHeight = params.insulatorCount * params.height;

  // 创建构架端连接杆（X轴方向）（保持不变）
  gp_Ax2 frameAxis(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0));
  BRepPrimAPI_MakeCylinder frameRod(frameAxis, params.radius / 2,
                                    params.frontLength);
  builder.Add(compound, frameRod.Shape());

  // 创建导线端连接杆（X轴方向）（保持不变）
  gp_Ax2 wireAxis(gp_Pnt(totalHeight, 0, 0), gp_Dir(1, 0, 0));
  BRepPrimAPI_MakeCylinder wireRod(wireAxis, params.radius / 2,
                                   params.backLength);
  builder.Add(compound, wireRod.Shape());

  // 创建绝缘子串
  for (int i = 0; i < params.count; ++i) {
    // 计算Y轴偏移（对称分布）（保持不变）
    double yOffset = (i % 2 == 0) ? params.spacing / 2 : -params.spacing / 2;

    // 创建绝缘子串
    for (int j = 0; j < params.insulatorCount; ++j) {
      // 计算当前高度（保持不变）
      double zPos = j * params.height;

      // 创建绝缘子圆柱（保持不变）
      gp_Ax2 insulatorAxis(gp_Pnt(zPos, yOffset, 0), gp_Dir(0, 1, 0));
      TopoDS_Shape insulator =
          BRepPrimAPI_MakeCylinder(insulatorAxis, params.radius, params.height)
              .Shape();
      builder.Add(compound, insulator);

      // 新伞裙生成方式（5点曲线剖面）
      double skirtRadius =
          (j % 2 == 0) ? params.bigSkirtRadius : params.smallSkirtRadius;

      // 创建伞裙剖面线（5点曲线）
      BRepBuilderAPI_MakeWire wire;
      gp_Pnt p1(skirtRadius, yOffset, 0);                           // 外缘
      gp_Pnt p2(skirtRadius * 0.95, yOffset, params.height * 0.1);  // 上翘
      gp_Pnt p3(skirtRadius * 0.7, yOffset, params.height * 0.3);   // 下凹
      gp_Pnt p4(params.radius * 1.2, yOffset, params.height * 0.6); // 过渡
      gp_Pnt p5(params.radius, yOffset, params.height * 0.8);       // 连接

      wire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
      wire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
      wire.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
      wire.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge());

      // 旋转生成伞裙（绕Y轴旋转360度）
      gp_Ax1 rotAxis(gp_Pnt(zPos, yOffset, 0), gp_Dir(0, 1, 0));
      TopoDS_Shape skirt = BRepPrimAPI_MakeRevol(wire.Wire(), rotAxis).Shape();
      builder.Add(compound, skirt);
    }
  }

  // 创建分裂导线连接件（保持不变）
  if (params.splitCount > 1) {
    double angleStep = 2 * M_PI / params.splitCount;
    for (int k = 0; k < params.splitCount; ++k) {
      double angle = k * angleStep;
      double x = totalHeight + params.backLength;
      double y = params.radius * 2 * cos(angle);
      double z = params.radius * 2 * sin(angle);

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
  // 参数验证（保持不变）
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

  // 计算V型角度（保持不变）
  double vAngle = atan2(params.backSpacing / 2, params.frontSpacing / 2) * 2;

  // 创建构架端连接杆（保持不变）
  gp_Ax2 leftFrameAxis(gp_Pnt(-params.frontSpacing / 2, 0, 0), gp_Dir(0, 1, 0));
  builder.Add(compound,
              BRepPrimAPI_MakeCylinder(leftFrameAxis, params.radius / 2,
                                       params.frontLength)
                  .Shape());

  gp_Ax2 rightFrameAxis(gp_Pnt(params.frontSpacing / 2, 0, 0), gp_Dir(0, 1, 0));
  builder.Add(compound,
              BRepPrimAPI_MakeCylinder(rightFrameAxis, params.radius / 2,
                                       params.frontLength)
                  .Shape());

  // 创建导线端连接杆（保持不变）
  gp_Ax2 wireAxis(gp_Pnt(0, params.backSpacing / 2, 0), gp_Dir(0, 1, 0));
  builder.Add(compound, BRepPrimAPI_MakeCylinder(wireAxis, params.radius / 2,
                                                 params.backLength)
                            .Shape());

  // 创建左右绝缘子串
  for (int side = 0; side < 2; ++side) { // 0=左, 1=右
    double sign = (side == 0) ? -1.0 : 1.0;

    for (int j = 0; j < params.insulatorCount; ++j) {
      // 计算位置和方向（保持不变）
      double zPos = j * params.height;
      double xPos = sign * zPos * sin(vAngle / 2);
      double yPos = zPos * cos(vAngle / 2);
      gp_Dir dir(sign * sin(vAngle / 2), cos(vAngle / 2), 0);

      // 创建绝缘子圆柱（保持不变）
      gp_Ax2 insulatorAxis(gp_Pnt(xPos, yPos, 0), dir);
      builder.Add(compound, BRepPrimAPI_MakeCylinder(
                                insulatorAxis, params.radius, params.height)
                                .Shape());

      // 新伞裙生成方式（5点曲线剖面）
      double skirtRadius =
          (j % 2 == 0) ? params.bigSkirtRadius : params.smallSkirtRadius;

      // 创建伞裙剖面线（在绝缘子坐标系中）
      BRepBuilderAPI_MakeWire wire;
      gp_Pnt p1(skirtRadius, 0, 0);                           // 外缘
      gp_Pnt p2(skirtRadius * 0.95, 0, params.height * 0.1);  // 上翘
      gp_Pnt p3(skirtRadius * 0.7, 0, params.height * 0.3);   // 下凹
      gp_Pnt p4(params.radius * 1.2, 0, params.height * 0.6); // 过渡
      gp_Pnt p5(params.radius, 0, params.height * 0.8);       // 连接

      wire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
      wire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
      wire.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
      wire.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge());

      // 旋转生成伞裙（绕绝缘子轴线旋转）
      gp_Ax1 rotAxis(gp_Pnt(xPos, yPos, 0), dir);
      TopoDS_Shape skirt = BRepPrimAPI_MakeRevol(wire.Wire(), rotAxis).Shape();
      builder.Add(compound, skirt);
    }
  }

  // 创建分裂导线连接件（保持不变）
  if (params.splitCount > 1) {
    double angleStep = 2 * M_PI / params.splitCount;
    for (int k = 0; k < params.splitCount; ++k) {
      double angle = k * angleStep;
      double x = params.radius * 2 * cos(angle);
      double y = params.backSpacing / 2 + params.backLength;
      double z = params.radius * 2 * sin(angle);

      gp_Pnt start(0, params.backSpacing / 2, 0);
      gp_Pnt end(x, y, z);
      builder.Add(compound, BRepBuilderAPI_MakeEdge(start, end).Edge());
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
 * @brief 创建等边角钢
 * @param params 等边角钢参数
 * @return TopoDS_Shape 生成的等边角钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape
create_equilateral_angle_steel(const equilateral_angle_steel_params &params) {
  // 参数验证
  if (params.L <= 0 || params.X <= 0 || params.length <= 0) {
    throw Standard_ConstructionError("All dimensions must be positive");
  }

  // 创建角钢截面轮廓
  BRepBuilderAPI_MakeWire wireMaker;

  // 第一边 (沿Y轴负方向)
  gp_Pnt p1(0, 0, 0);
  gp_Pnt p2(0, -params.L, 0);
  gp_Pnt p3(params.X, -params.L, 0);
  gp_Pnt p4(params.X, -params.X, 0);

  // 第二边 (沿Z轴正方向)
  gp_Pnt p5(0, -params.X, 0);
  gp_Pnt p6(0, -params.X, params.L);
  gp_Pnt p7(params.X, -params.X, params.L);
  gp_Pnt p8(params.X, 0, params.L);
  gp_Pnt p9(0, 0, params.L);

  // 添加边线
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p6, p7).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, p9).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p9, p1).Edge());

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
 * @brief 创建带定位的等边角钢
 * @param params 等边角钢参数
 * @param position 角钢起点位置
 * @param xDirection 长度方向（默认X轴）
 * @param yDirection 第一边方向（默认-Y轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape
create_equilateral_angle_steel(const equilateral_angle_steel_params &params,
                               const gp_Pnt &position, const gp_Dir &xDirection,
                               const gp_Dir &yDirection) {
  // 首先创建标准方向的角钢
  TopoDS_Shape angleSteel = create_equilateral_angle_steel(params);

  // 计算Z方向
  gp_Dir zDirection = xDirection.Crossed(yDirection);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DX(), gp::DY().Reversed());
  gp_Ax3 targetAx3(position, xDirection, yDirection);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(angleSteel, transformation);
  return transform.Shape();
}

/**
 * @brief 创建不等边角钢
 * @param params 不等边角钢参数
 * @return TopoDS_Shape 生成的不等边角钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape
create_scalene_angle_steel(const scalene_angle_steel_params &params) {
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

  // 创建角钢截面轮廓
  BRepBuilderAPI_MakeWire wireMaker;

  // 长边 (沿Z轴正方向)
  gp_Pnt p1(0, 0, 0);
  gp_Pnt p2(0, 0, params.L1);
  gp_Pnt p3(params.X, 0, params.L1);
  gp_Pnt p4(params.X, 0, params.X);

  // 短边 (沿Y轴负方向)
  gp_Pnt p5(0, -params.X, params.X);
  gp_Pnt p6(0, -params.L2, params.X);
  gp_Pnt p7(params.X, -params.L2, params.X);
  gp_Pnt p8(params.X, 0, 0);

  // 添加边线
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p6, p7).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, p1).Edge());

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
TopoDS_Shape
create_scalene_angle_steel(const scalene_angle_steel_params &params,
                           const gp_Pnt &position, const gp_Dir &xDirection,
                           const gp_Dir &longEdgeDir) {
  // 首先创建标准方向的角钢
  TopoDS_Shape angleSteel = create_scalene_angle_steel(params);

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
 * @brief 创建工字钢截面轮廓（带圆弧过渡）
 * @param height 总高度 (Z轴方向)
 * @param flangeWidth 翼缘宽度 (Y轴方向)
 * @param webThickness 腹板厚度 (Y轴方向)
 * @param flangeThickness 翼缘厚度 (Z轴方向)
 * @param radius 过渡圆弧半径
 * @return TopoDS_Wire 生成的截面轮廓线
 */
TopoDS_Wire create_ibeam_profile(double height, double flangeWidth,
                                 double webThickness, double flangeThickness,
                                 double radius) {
  BRepBuilderAPI_MakeWire wireMaker;

  // 计算关键尺寸 - 注意坐标轴调整：
  // X轴: 长度方向(函数内不使用，由拉伸操作决定)
  // Y轴: 翼缘宽度方向(负方向)
  // Z轴: 腹板高度方向
  double halfHeight = height / 2;
  double halfFlangeWidth = flangeWidth / 2;
  double halfWebThickness = webThickness / 2;

  // 外轮廓关键点（右侧）
  // 注意坐标顺序调整为: (X,Y,Z) -> (0,Y,Z) 因为截面在YZ平面
  gp_Pnt p1(0, -halfFlangeWidth, -halfHeight);
  gp_Pnt p2(0, halfFlangeWidth, -halfHeight);
  gp_Pnt p3(0, halfFlangeWidth, -halfHeight + flangeThickness - radius);
  gp_Pnt p4(0, halfFlangeWidth, -halfHeight + flangeThickness);
  gp_Pnt p5(0, halfWebThickness + radius, -halfHeight + flangeThickness);
  gp_Pnt p6(0, halfWebThickness, -halfHeight + flangeThickness + radius);
  gp_Pnt p7(0, halfWebThickness, halfHeight - flangeThickness - radius);
  gp_Pnt p8(0, halfWebThickness + radius, halfHeight - flangeThickness);
  gp_Pnt p9(0, halfFlangeWidth, halfHeight - flangeThickness);
  gp_Pnt p10(0, halfFlangeWidth, halfHeight - flangeThickness + radius);
  gp_Pnt p11(0, halfFlangeWidth, halfHeight);
  gp_Pnt p12(0, -halfFlangeWidth, halfHeight);

  // 左侧对称点
  gp_Pnt p13(0, -halfFlangeWidth, halfHeight - flangeThickness + radius);
  gp_Pnt p14(0, -halfFlangeWidth, halfHeight - flangeThickness);
  gp_Pnt p15(0, -halfWebThickness - radius, halfHeight - flangeThickness);
  gp_Pnt p16(0, -halfWebThickness, halfHeight - flangeThickness - radius);
  gp_Pnt p17(0, -halfWebThickness, -halfHeight + flangeThickness + radius);
  gp_Pnt p18(0, -halfWebThickness - radius, -halfHeight + flangeThickness);
  gp_Pnt p19(0, -halfFlangeWidth, -halfHeight + flangeThickness);
  gp_Pnt p20(0, -halfFlangeWidth, -halfHeight + flangeThickness - radius);

  // 创建所有直线段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());   // 下翼缘底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());   // 右下翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p9, p10).Edge());  // 右上翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p11, p12).Edge()); // 上翼缘顶部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p14, p15).Edge()); // 左上翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p19, p20).Edge()); // 左下翼缘垂直段

  // 创建所有圆弧过渡
  if (radius < flangeThickness / 3) { // 小半径过渡（轻型工字钢）
    // 右下翼缘圆弧 (Y轴负方向)
    gp_Circ arc1(gp_Ax2(p4, gp_Dir(1, 0, 0)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc1, p4, p5).Edge());

    // 右下腹板圆弧 (Z轴正方向)
    gp_Circ arc2(gp_Ax2(p6, gp_Dir(1, 0, 0)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc2, p6, p7).Edge());

    // 右上腹板圆弧 (Z轴负方向)
    gp_Circ arc3(gp_Ax2(p8, gp_Dir(1, 0, 0)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc3, p8, p9).Edge());

    // 右上翼缘圆弧 (Y轴正方向)
    gp_Circ arc4(gp_Ax2(p10, gp_Dir(1, 0, 0)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc4, p10, p11).Edge());

    // 左上翼缘圆弧 (Y轴正方向)
    gp_Circ arc5(gp_Ax2(p13, gp_Dir(1, 0, 0)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc5, p13, p14).Edge());

    // 左上腹板圆弧 (Z轴负方向)
    gp_Circ arc6(gp_Ax2(p15, gp_Dir(1, 0, 0)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc6, p15, p16).Edge());

    // 左下腹板圆弧 (Z轴正方向)
    gp_Circ arc7(gp_Ax2(p17, gp_Dir(1, 0, 0)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc7, p17, p18).Edge());

    // 左下翼缘圆弧 (Y轴负方向)
    gp_Circ arc8(gp_Ax2(p19, gp_Dir(1, 0, 0)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc8, p19, p20).Edge());
  } else { // 大半径过渡（普通工字钢）
    // 仅创建翼缘圆弧
    gp_Circ arc1(gp_Ax2(p4, gp_Dir(1, 0, 0)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc1, p4, p5).Edge());

    gp_Circ arc2(gp_Ax2(p10, gp_Dir(1, 0, 0)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc2, p10, p11).Edge());

    gp_Circ arc3(gp_Ax2(p13, gp_Dir(1, 0, 0)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc3, p13, p14).Edge());

    gp_Circ arc4(gp_Ax2(p19, gp_Dir(1, 0, 0)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc4, p19, p20).Edge());
  }

  // 创建腹板水平段 (Y轴方向)
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p5, p18).Edge()); // 下腹板
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, p15).Edge()); // 上腹板

  // 创建腹板垂直段（Z轴方向，仅普通工字钢需要）
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
 * @brief 创建工字钢
 * @param params 工字钢参数
 * @return TopoDS_Shape 生成的工字钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_ibeam(const ibeam_params &params) {
  // 参数验证
  if (params.height <= 0 || params.flangeWidth <= 0 ||
      params.webThickness <= 0 || params.flangeThickness <= 0 ||
      params.radius <= 0 || params.length <= 0) {
    throw Standard_ConstructionError("All dimensions must be positive");
  }
  if (params.webThickness >= params.flangeWidth) {
    throw Standard_ConstructionError(
        "Web thickness must be less than flange width");
  }
  if (2 * params.flangeThickness >= params.height) {
    throw Standard_ConstructionError("Flange thickness too large for height");
  }

  // 创建工字钢截面轮廓
  TopoDS_Wire profile = create_ibeam_profile(
      params.height, params.flangeWidth, params.webThickness,
      params.flangeThickness, params.radius);

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
TopoDS_Shape create_ibeam(const ibeam_params &params, const gp_Pnt &position,
                          const gp_Dir &xDirection, const gp_Dir &zDirection) {
  // 首先创建标准方向的工字钢
  TopoDS_Shape ibeam = create_ibeam(params);

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
 * @brief 创建轻型工字钢
 * @param params 轻型工字钢参数
 * @return TopoDS_Shape 生成的轻型工字钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_light_ibeam(const light_ibeam_params &params) {
  // 参数验证
  if (params.height <= 0 || params.flangeWidth <= 0 ||
      params.webThickness <= 0 || params.flangeThickness <= 0 ||
      params.radius <= 0 || params.length <= 0) {
    throw Standard_ConstructionError("All dimensions must be positive");
  }
  if (params.webThickness >= params.flangeWidth) {
    throw Standard_ConstructionError(
        "Web thickness must be less than flange width");
  }
  if (2 * params.flangeThickness >= params.height) {
    throw Standard_ConstructionError("Flange thickness too large for height");
  }
  if (params.flangeSlope < 0 || params.flangeSlope >= 1) {
    throw Standard_ConstructionError("Flange slope must be in [0, 1)");
  }

  // 创建基本工字钢
  ibeam_params basicParams{params.height,       params.flangeWidth,
                           params.webThickness, params.flangeThickness,
                           params.radius,       params.length};
  TopoDS_Shape basicIbeam = create_ibeam(basicParams);

  // 添加翼缘坡度
  if (params.flangeSlope > Precision::Confusion()) {
    // 创建切割平面
    double slopeOffset = params.flangeSlope * params.flangeThickness;
    gp_Pln cutPlane1(
        gp_Pnt(0, -params.height / 2 + params.flangeThickness - slopeOffset, 0),
        gp_Dir(0, -1, 0));
    gp_Pln cutPlane2(
        gp_Pnt(0, params.height / 2 - params.flangeThickness + slopeOffset, 0),
        gp_Dir(0, 1, 0));

    // 执行切割
    BRepAlgoAPI_Cut cutter1(basicIbeam,
                            BRepBuilderAPI_MakeFace(cutPlane1).Face());
    BRepAlgoAPI_Cut cutter2(cutter1.Shape(),
                            BRepBuilderAPI_MakeFace(cutPlane2).Face());

    if (!cutter2.IsDone()) {
      throw Standard_ConstructionError(
          "Failed to create slope on light I-beam");
    }
    return cutter2.Shape();
  }

  return basicIbeam;
}

/**
 * @brief 创建带定位的轻型工字钢
 * @param params 轻型工字钢参数
 * @param position 工字钢起点位置
 * @param xDirection 长度方向（默认X轴）
 * @param zDirection 腹板方向（默认Z轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_light_ibeam(const light_ibeam_params &params,
                                const gp_Pnt &position,
                                const gp_Dir &xDirection,
                                const gp_Dir &zDirection) {
  // 首先创建标准方向的轻型工字钢（坡度变换已在create_light_ibeam中处理）
  TopoDS_Shape lightIbeam = create_light_ibeam(params);

  // 计算Y方向
  gp_Dir yDirection = xDirection.Crossed(zDirection);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DX(), gp::DZ());
  gp_Ax3 targetAx3(position, xDirection, zDirection);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(lightIbeam, transformation);
  return transform.Shape();
}

/**
 * @brief 创建H型钢截面轮廓
 * @param height 总高度 (Z轴方向)
 * @param flangeWidth 翼缘宽度 (Y轴方向)
 * @param webThickness 腹板厚度 (Y轴方向)
 * @param flangeThickness 翼缘厚度 (Z轴方向)
 * @param radius 过渡圆弧半径
 * @return TopoDS_Wire 生成的截面轮廓线
 */
TopoDS_Wire create_hbeam_profile(double height, double flangeWidth,
                                 double webThickness, double flangeThickness,
                                 double radius) {
  BRepBuilderAPI_MakeWire wireMaker;

  // 计算关键尺寸 - 注意坐标轴调整：
  // X轴: 长度方向(函数内不使用，由拉伸操作决定)
  // Y轴: 翼缘宽度方向(正负方向)
  // Z轴: 腹板高度方向
  double halfHeight = height / 2;
  double halfFlangeWidth = flangeWidth / 2;
  double halfWebThickness = webThickness / 2;

  // 外轮廓关键点（右侧）
  // 注意坐标顺序调整为: (X,Y,Z) -> (0,Y,Z) 因为截面在YZ平面
  gp_Pnt p1(0, -halfFlangeWidth, -halfHeight);
  gp_Pnt p2(0, halfFlangeWidth, -halfHeight);
  gp_Pnt p3(0, halfFlangeWidth, -halfHeight + flangeThickness);
  gp_Pnt p4(0, halfWebThickness, -halfHeight + flangeThickness);
  gp_Pnt p5(0, halfWebThickness, halfHeight - flangeThickness);
  gp_Pnt p6(0, halfFlangeWidth, halfHeight - flangeThickness);
  gp_Pnt p7(0, halfFlangeWidth, halfHeight);
  gp_Pnt p8(0, -halfFlangeWidth, halfHeight);

  // 左侧对称点
  gp_Pnt p9(0, -halfFlangeWidth, halfHeight - flangeThickness);
  gp_Pnt p10(0, -halfWebThickness, halfHeight - flangeThickness);
  gp_Pnt p11(0, -halfWebThickness, -halfHeight + flangeThickness);
  gp_Pnt p12(0, -halfFlangeWidth, -halfHeight + flangeThickness);

  // 创建所有直线段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());   // 下翼缘底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());   // 右下翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());   // 右下翼缘水平段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge());   // 右腹板垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge());   // 右上翼缘水平段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p6, p7).Edge());   // 右上翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8).Edge());   // 上翼缘顶部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, p9).Edge());   // 左上翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p9, p10).Edge());  // 左上翼缘水平段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p10, p11).Edge()); // 左腹板垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p11, p12).Edge()); // 左下翼缘水平段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p12, p1).Edge());  // 左下翼缘垂直段

  // 创建过渡圆弧（如果半径大于0）
  if (radius > Precision::Confusion()) {
    // 右下翼缘圆弧
    gp_Pnt arcStart1(0, halfFlangeWidth,
                     -halfHeight + flangeThickness - radius);
    gp_Pnt arcEnd1(0, halfFlangeWidth - radius, -halfHeight + flangeThickness);
    gp_Circ arc1(gp_Ax2(arcStart1, gp_Dir(1, 0, 0)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc1, arcStart1, arcEnd1).Edge());

    // 右上翼缘圆弧
    gp_Pnt arcStart2(0, halfFlangeWidth, halfHeight - flangeThickness + radius);
    gp_Pnt arcEnd2(0, halfFlangeWidth - radius, halfHeight - flangeThickness);
    gp_Circ arc2(gp_Ax2(arcStart2, gp_Dir(1, 0, 0)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc2, arcStart2, arcEnd2).Edge());

    // 左上翼缘圆弧
    gp_Pnt arcStart3(0, -halfFlangeWidth,
                     halfHeight - flangeThickness + radius);
    gp_Pnt arcEnd3(0, -halfFlangeWidth + radius, halfHeight - flangeThickness);
    gp_Circ arc3(gp_Ax2(arcStart3, gp_Dir(1, 0, 0)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc3, arcStart3, arcEnd3).Edge());

    // 左下翼缘圆弧
    gp_Pnt arcStart4(0, -halfFlangeWidth,
                     -halfHeight + flangeThickness - radius);
    gp_Pnt arcEnd4(0, -halfFlangeWidth + radius, -halfHeight + flangeThickness);
    gp_Circ arc4(gp_Ax2(arcStart4, gp_Dir(1, 0, 0)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc4, arcStart4, arcEnd4).Edge());
  }

  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create H-beam profile");
  }
  return wireMaker.Wire();
}

/**
 * @brief 创建H型钢
 * @param params H型钢参数
 * @return TopoDS_Shape 生成的H型钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_hbeam(const hbeam_params &params) {
  // 参数验证
  if (params.height <= 0 || params.flangeWidth <= 0 ||
      params.webThickness <= 0 || params.flangeThickness <= 0 ||
      params.radius < 0 || params.length <= 0) {
    throw Standard_ConstructionError("All dimensions must be positive");
  }
  if (params.webThickness >= params.flangeWidth) {
    throw Standard_ConstructionError(
        "Web thickness must be less than flange width");
  }
  if (2 * params.flangeThickness >= params.height) {
    throw Standard_ConstructionError("Flange thickness too large for height");
  }

  // 创建H型钢截面轮廓
  TopoDS_Wire profile = create_hbeam_profile(
      params.height, params.flangeWidth, params.webThickness,
      params.flangeThickness, params.radius);

  // 创建截面面
  BRepBuilderAPI_MakeFace faceMaker(profile);
  if (!faceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create H-beam face");
  }

  // 沿X轴拉伸
  BRepPrimAPI_MakePrism prismMaker(faceMaker.Face(),
                                   gp_Vec(params.length, 0, 0));

  return prismMaker.Shape();
}

/**
 * @brief 创建带定位的H型钢
 * @param params H型钢参数
 * @param position H型钢起点位置
 * @param xDirection 长度方向（默认X轴）
 * @param zDirection 腹板方向（默认Z轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_hbeam(const hbeam_params &params, const gp_Pnt &position,
                          const gp_Dir &xDirection, const gp_Dir &zDirection) {
  // 首先创建标准方向的H型钢
  TopoDS_Shape hbeam = create_hbeam(params);

  // 计算Y方向
  gp_Dir yDirection = xDirection.Crossed(zDirection);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DX(), gp::DZ()); // X:长度, Z:腹板
  gp_Ax3 targetAx3(position, xDirection, zDirection);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(hbeam, transformation);
  return transform.Shape();
}

/**
 * @brief 创建槽钢截面轮廓
 * @param height 总高度 (Z轴方向)
 * @param flangeWidth 翼缘宽度 (Y轴方向)
 * @param webThickness 腹板厚度 (Y轴方向)
 * @param flangeThickness 翼缘厚度 (Z轴方向)
 * @param radius 过渡圆弧半径
 * @return TopoDS_Wire 生成的截面轮廓线
 */
TopoDS_Wire create_channel_profile(double height, double flangeWidth,
                                   double webThickness, double flangeThickness,
                                   double radius) {
  BRepBuilderAPI_MakeWire wireMaker;

  // 计算关键尺寸 - 注意坐标轴调整：
  // X轴: 长度方向(函数内不使用，由拉伸操作决定)
  // Y轴: 翼缘宽度方向(正方向)
  // Z轴: 腹板高度方向
  double halfHeight = height / 2;
  double halfWebThickness = webThickness / 2;

  // 外轮廓关键点（右侧）
  // 注意坐标顺序调整为: (X,Y,Z) -> (0,Y,Z) 因为截面在YZ平面
  gp_Pnt p1(0, 0, -halfHeight);
  gp_Pnt p2(0, -flangeWidth, -halfHeight); // 改为负方向
  gp_Pnt p3(0, -flangeWidth, -halfHeight + flangeThickness);
  gp_Pnt p4(0, -halfWebThickness, -halfHeight + flangeThickness); // 改为负方向
  gp_Pnt p5(0, -halfWebThickness, halfHeight - flangeThickness);  // 改为负方向
  gp_Pnt p6(0, -flangeWidth, halfHeight - flangeThickness);       // 改为负方向
  gp_Pnt p7(0, -flangeWidth, halfHeight);                         // 改为负方向
  gp_Pnt p8(0, 0, halfHeight);

  // 创建所有直线段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge()); // 下翼缘底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge()); // 右下翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge()); // 右下翼缘水平段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge()); // 腹板垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge()); // 右上翼缘水平段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p6, p7).Edge()); // 右上翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8).Edge()); // 上翼缘顶部

  // 创建过渡圆弧（如果半径大于0）
  if (radius > Precision::Confusion()) {
    gp_Pnt arcStart1(0, -flangeWidth,
                     -halfHeight + flangeThickness - radius); // 负方向
    gp_Pnt arcEnd1(0, -flangeWidth + radius,
                   -halfHeight + flangeThickness); // 负方向
    gp_Circ arc1(gp_Ax2(arcStart1, gp_Dir(1, 0, 0)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc1, arcStart1, arcEnd1).Edge());

    gp_Pnt arcStart2(0, -flangeWidth,
                     halfHeight - flangeThickness + radius); // 负方向
    gp_Pnt arcEnd2(0, -flangeWidth + radius,
                   halfHeight - flangeThickness); // 负方向
    gp_Circ arc2(gp_Ax2(arcStart2, gp_Dir(1, 0, 0)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc2, arcStart2, arcEnd2).Edge());
  }

  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create channel profile");
  }
  return wireMaker.Wire();
}

/**
 * @brief 创建槽钢
 * @param params 槽钢参数
 * @return TopoDS_Shape 生成的槽钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_beam_channel(const beam_channel_params &params) {
  // 参数验证
  if (params.height <= 0 || params.flangeWidth <= 0 ||
      params.webThickness <= 0 || params.flangeThickness <= 0 ||
      params.radius < 0 || params.length <= 0) {
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
  TopoDS_Wire profile = create_channel_profile(
      params.height, params.flangeWidth, params.webThickness,
      params.flangeThickness, params.radius);

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
TopoDS_Shape create_beam_channel(const beam_channel_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &xDirection,
                                 const gp_Dir &zDirection) {
  // 首先创建标准方向的槽钢
  TopoDS_Shape channel = create_beam_channel(params);

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
 * @brief 创建轻型槽钢截面轮廓
 * @param height 总高度 (Z轴方向)
 * @param flangeWidth 翼缘宽度 (Y轴方向)
 * @param webThickness 腹板厚度 (Y轴方向)
 * @param flangeThickness 翼缘厚度 (Z轴方向)
 * @param radius 过渡圆弧半径
 * @param flangeSlope 翼缘坡度
 * @return TopoDS_Wire 生成的截面轮廓线
 */
TopoDS_Wire create_light_channel_profile(double height, double flangeWidth,
                                         double webThickness,
                                         double flangeThickness, double radius,
                                         double flangeSlope) {
  BRepBuilderAPI_MakeWire wireMaker;

  // 计算关键尺寸 - 注意坐标轴调整：
  // X轴: 长度方向(函数内不使用，由拉伸操作决定)
  // Y轴: 翼缘宽度方向(正方向)
  // Z轴: 腹板高度方向
  double halfHeight = height / 2;
  double halfWebThickness = webThickness / 2;
  double slopeOffset = flangeSlope * flangeThickness;

  // 外轮廓关键点（右侧）
  // 注意坐标顺序调整为: (X,Y,Z) -> (0,Y,Z) 因为截面在YZ平面
  gp_Pnt p1(0, 0, -halfHeight);
  gp_Pnt p2(0, -flangeWidth, -halfHeight); // 改为负方向
  gp_Pnt p3(0, -flangeWidth,
            -halfHeight + flangeThickness - slopeOffset);         // 负方向
  gp_Pnt p4(0, -halfWebThickness, -halfHeight + flangeThickness); // 负方向
  gp_Pnt p5(0, -halfWebThickness, halfHeight - flangeThickness);  // 负方向
  gp_Pnt p6(0, -flangeWidth,
            halfHeight - flangeThickness + slopeOffset); // 负方向
  gp_Pnt p7(0, -flangeWidth, halfHeight);                // 负方向
  gp_Pnt p8(0, 0, halfHeight);

  // 创建所有直线段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge()); // 下翼缘底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge()); // 右下翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge()); // 右下翼缘斜线段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge()); // 腹板垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge()); // 右上翼缘斜线段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p6, p7).Edge()); // 右上翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8).Edge()); // 上翼缘顶部

  // 创建过渡圆弧（如果半径大于0）
  if (radius > Precision::Confusion()) {
    gp_Pnt arcStart1(0, -flangeWidth,
                     -halfHeight + flangeThickness - slopeOffset -
                         radius); // 负方向
    gp_Pnt arcEnd1(0, -flangeWidth + radius,
                   -halfHeight + flangeThickness - slopeOffset); // 负方向
    gp_Circ arc1(gp_Ax2(arcStart1, gp_Dir(1, 0, 0)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc1, arcStart1, arcEnd1).Edge());

    gp_Pnt arcStart2(0, -flangeWidth,
                     halfHeight - flangeThickness + slopeOffset +
                         radius); // 负方向
    gp_Pnt arcEnd2(0, -flangeWidth + radius,
                   halfHeight - flangeThickness + slopeOffset); // 负方向
    gp_Circ arc2(gp_Ax2(arcStart2, gp_Dir(1, 0, 0)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc2, arcStart2, arcEnd2).Edge());
  }

  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create light channel profile");
  }
  return wireMaker.Wire();
}

/**
 * @brief 创建轻型槽钢
 * @param params 轻型槽钢参数
 * @return TopoDS_Shape 生成的轻型槽钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape
create_light_beam_channel(const light_beam_channel_params &params) {
  // 参数验证
  if (params.height <= 0 || params.flangeWidth <= 0 ||
      params.webThickness <= 0 || params.flangeThickness <= 0 ||
      params.radius < 0 || params.length <= 0 || params.flangeSlope < 0 ||
      params.flangeSlope >= 1) {
    throw Standard_ConstructionError(
        "All dimensions must be positive and slope in [0,1)");
  }
  if (params.webThickness >= params.flangeWidth) {
    throw Standard_ConstructionError(
        "Web thickness must be less than flange width");
  }
  if (2 * params.flangeThickness >= params.height) {
    throw Standard_ConstructionError("Flange thickness too large for height");
  }

  // 创建轻型槽钢截面轮廓
  TopoDS_Wire profile = create_light_channel_profile(
      params.height, params.flangeWidth, params.webThickness,
      params.flangeThickness, params.radius, params.flangeSlope);

  // 创建截面面
  BRepBuilderAPI_MakeFace faceMaker(profile);
  if (!faceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create light channel face");
  }

  // 沿X轴拉伸
  BRepPrimAPI_MakePrism prismMaker(faceMaker.Face(),
                                   gp_Vec(params.length, 0, 0));

  return prismMaker.Shape();
}

/**
 * @brief 创建带定位的轻型槽钢
 * @param params 轻型槽钢参数
 * @param position 轻型槽钢起点位置
 * @param xDirection 长度方向（默认X轴）
 * @param zDirection 腹板方向（默认Z轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_light_beam_channel(const light_beam_channel_params &params,
                                       const gp_Pnt &position,
                                       const gp_Dir &xDirection,
                                       const gp_Dir &zDirection) {
  // 首先创建标准方向的轻型槽钢
  TopoDS_Shape channel = create_light_beam_channel(params);

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
 * @brief 创建扁钢
 * @param params 扁钢参数
 * @return TopoDS_Shape 生成的扁钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_flat_steel(const flat_steel_params &params) {
  // 参数验证
  if (params.width <= 0.0 || params.thickness <= 0.0 || params.length <= 0.0) {
    throw Standard_ConstructionError("All dimensions must be positive");
  }

  // 创建扁钢（根据要求：X轴为长度方向，Z轴为厚度方向，Y轴负方向为宽度方向）
  gp_Pnt origin(-params.length / 2, params.width / 2,
                -params.thickness / 2); // 调整原点位置
  BRepPrimAPI_MakeBox boxMaker(origin, params.length, -params.width,
                               params.thickness);

  return boxMaker.Shape();
}

/**
 * @brief 创建带定位的扁钢
 * @param params 扁钢参数
 * @param position 扁钢起点位置
 * @param xDirection 长度方向（默认X轴）
 * @param zDirection 厚度方向（默认Z轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_flat_steel(const flat_steel_params &params,
                               const gp_Pnt &position, const gp_Dir &xDirection,
                               const gp_Dir &zDirection) {
  // 首先创建标准方向的扁钢
  TopoDS_Shape flatSteel = create_flat_steel(params);

  // 计算Y方向（根据右手定则，宽度方向为Y轴负方向）
  gp_Dir yDirection = zDirection.Crossed(xDirection).Reversed();

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX()); // Z:厚度, X:长度
  gp_Ax3 targetAx3(position, zDirection, xDirection);

  // 验证方向向量是否正交
  if (Abs(xDirection.Dot(zDirection)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "X and Z directions must be perpendicular");
  }

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(flatSteel, transformation);
  return transform.Shape();
}

/**
 * @brief 创建L型钢截面轮廓
 * @param height 高度 (Z轴方向)
 * @param width 宽度 (Y轴方向)
 * @param thickness 厚度
 * @param radius 过渡圆弧半径
 * @return TopoDS_Wire 生成的截面轮廓线
 */
TopoDS_Wire create_lsteel_profile(double height, double width, double thickness,
                                  double radius) {
  BRepBuilderAPI_MakeWire wireMaker;

  // 计算关键点坐标（根据要求：Z正方向和Y负方向）
  gp_Pnt p1(0, 0, 0);
  gp_Pnt p2(0, -width, 0);
  gp_Pnt p3(0, -width, thickness);
  gp_Pnt p4(0, -thickness, thickness);
  gp_Pnt p5(0, -thickness, height);
  gp_Pnt p6(0, 0, height);

  // 创建直线段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p6, p1).Edge());

  // 创建过渡圆弧（如果半径大于0）
  if (radius > Precision::Confusion()) {
    gp_Pnt arcStart(0, -width + radius, thickness);
    gp_Pnt arcEnd(0, -width, thickness - radius);
    gp_Circ arc(gp_Ax2(arcStart, gp_Dir(1, 0, 0)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc, arcStart, arcEnd).Edge());
  }

  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create L-steel profile");
  }
  return wireMaker.Wire();
}

/**
 * @brief 创建L型钢
 * @param params L型钢参数
 * @return TopoDS_Shape 生成的L型钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_lsteel(const lsteel_params &params) {
  // 参数验证
  if (params.height <= 0 || params.width <= 0 || params.thickness <= 0 ||
      params.radius < 0 || params.length <= 0) {
    throw Standard_ConstructionError("All dimensions must be positive");
  }
  if (params.thickness >= params.width || params.thickness >= params.height) {
    throw Standard_ConstructionError(
        "Thickness must be less than width and height");
  }

  // 创建截面轮廓
  TopoDS_Wire profile = create_lsteel_profile(params.height, params.width,
                                              params.thickness, params.radius);

  // 创建截面面
  BRepBuilderAPI_MakeFace faceMaker(profile);
  if (!faceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create L-steel face");
  }

  // 沿X轴拉伸
  BRepPrimAPI_MakePrism prismMaker(faceMaker.Face(),
                                   gp_Vec(params.length, 0, 0));

  return prismMaker.Shape();
}

/**
 * @brief 创建带定位的L型钢
 * @param params L型钢参数
 * @param position L型钢起点位置
 * @param xDirection 长度方向（默认X轴）
 * @param zDirection 高度方向（默认Z轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_lsteel(const lsteel_params &params, const gp_Pnt &position,
                           const gp_Dir &xDirection, const gp_Dir &zDirection) {
  // 首先创建标准方向的L型钢
  TopoDS_Shape lsteel = create_lsteel(params);

  // 计算Y方向（根据右手定则）
  gp_Dir yDirection = zDirection.Crossed(xDirection).Reversed();

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX()); // Z:高度, X:长度
  gp_Ax3 targetAx3(position, zDirection, xDirection);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(lsteel, transformation);
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
TopoDS_Wire create_tsteel_profile(double height, double width,
                                  double webThickness, double flangeThickness,
                                  double radius) {
  BRepBuilderAPI_MakeWire wireMaker;

  // 计算关键点坐标（根据要求：T字横杠在Z正方向，两翼在Y方向）
  double halfWidth = width / 2;
  double halfWebThickness = webThickness / 2;

  // 腹板部分点
  gp_Pnt p1(0, -halfWebThickness, 0);
  gp_Pnt p2(0, halfWebThickness, 0);
  gp_Pnt p3(0, halfWebThickness, height - flangeThickness);
  gp_Pnt p4(0, -halfWebThickness, height - flangeThickness);

  // 翼缘部分点
  gp_Pnt p5(0, -halfWidth, height - flangeThickness);
  gp_Pnt p6(0, -halfWidth, height);
  gp_Pnt p7(0, halfWidth, height);
  gp_Pnt p8(0, halfWidth, height - flangeThickness);

  // 创建直线段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p8).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, p7).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p6).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p6, p5).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p5, p4).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p1).Edge());

  // 创建过渡圆弧（如果半径大于0）
  if (radius > Precision::Confusion()) {
    // 腹板与翼缘连接处的圆弧
    gp_Pnt arcStart1(0, halfWebThickness + radius, height - flangeThickness);
    gp_Pnt arcEnd1(0, halfWebThickness, height - flangeThickness + radius);
    gp_Circ arc1(gp_Ax2(arcStart1, gp_Dir(1, 0, 0)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc1, arcStart1, arcEnd1).Edge());

    gp_Pnt arcStart2(0, -halfWebThickness - radius, height - flangeThickness);
    gp_Pnt arcEnd2(0, -halfWebThickness, height - flangeThickness + radius);
    gp_Circ arc2(gp_Ax2(arcStart2, gp_Dir(1, 0, 0)), radius);
    wireMaker.Add(BRepBuilderAPI_MakeEdge(arc2, arcStart2, arcEnd2).Edge());
  }

  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create T-steel profile");
  }
  return wireMaker.Wire();
}

/**
 * @brief 创建T型钢
 * @param params T型钢参数
 * @return TopoDS_Shape 生成的T型钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_tsteel(const tsteel_params &params) {
  // 参数验证
  if (params.height <= 0 || params.width <= 0 || params.webThickness <= 0 ||
      params.flangeThickness <= 0 || params.radius < 0 || params.length <= 0) {
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
  TopoDS_Wire profile =
      create_tsteel_profile(params.height, params.width, params.webThickness,
                            params.flangeThickness, params.radius);

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
TopoDS_Shape create_tsteel(const tsteel_params &params, const gp_Pnt &position,
                           const gp_Dir &xDirection, const gp_Dir &zDirection) {
  // 首先创建标准方向的T型钢
  TopoDS_Shape tsteel = create_tsteel(params);

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
 * @brief 创建圆钢
 * @param params 圆钢参数
 * @return TopoDS_Shape 生成的圆钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_round_steel(const round_steel_params &params) {
  // 参数验证
  if (params.diameter <= 0.0 || params.length <= 0.0) {
    throw Standard_ConstructionError("Diameter and length must be positive");
  }

  // 创建圆钢（X轴为长度方向）
  gp_Ax2 axis(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0));
  BRepPrimAPI_MakeCylinder cylinderMaker(axis, params.diameter / 2,
                                         params.length);

  return cylinderMaker.Shape();
}

/**
 * @brief 创建带定位的圆钢
 * @param params 圆钢参数
 * @param position 圆钢起点位置
 * @param xDirection 长度方向（默认X轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_round_steel(const round_steel_params &params,
                                const gp_Pnt &position,
                                const gp_Dir &xDirection) {
  // 首先创建标准方向的圆钢
  TopoDS_Shape roundSteel = create_round_steel(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DX()); // X:长度方向
  gp_Ax3 targetAx3(position, xDirection);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(roundSteel, transformation);
  return transform.Shape();
}

/**
 * @brief 创建圆钢管
 * @param params 圆钢管参数
 * @return TopoDS_Shape 生成的圆钢管形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_round_steel_tube(const round_steel_tube_params &params) {
  // 参数验证
  if (params.outerDiameter <= params.innerDiameter) {
    throw Standard_ConstructionError(
        "Outer diameter must be greater than inner diameter");
  }
  if (params.innerDiameter <= 0.0) {
    throw Standard_ConstructionError("Inner diameter must be positive");
  }
  if (params.length <= 0.0) {
    throw Standard_ConstructionError("Length must be positive");
  }

  // 创建外圆柱
  gp_Ax2 outerAxis(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0));
  BRepPrimAPI_MakeCylinder outerCylinder(outerAxis, params.outerDiameter / 2,
                                         params.length);

  // 创建内圆柱
  gp_Ax2 innerAxis(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0));
  BRepPrimAPI_MakeCylinder innerCylinder(innerAxis, params.innerDiameter / 2,
                                         params.length);

  // 执行布尔差操作
  BRepAlgoAPI_Cut cutter(outerCylinder.Shape(), innerCylinder.Shape());
  if (!cutter.IsDone()) {
    throw Standard_ConstructionError("Failed to create steel tube");
  }

  return cutter.Shape();
}

/**
 * @brief 创建带定位的圆钢管
 * @param params 圆钢管参数
 * @param position 钢管起点位置
 * @param xDirection 长度方向（默认X轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_round_steel_tube(const round_steel_tube_params &params,
                                     const gp_Pnt &position,
                                     const gp_Dir &xDirection) {
  // 首先创建标准方向的圆钢管
  TopoDS_Shape tube = create_round_steel_tube(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DX()); // X:长度方向
  gp_Ax3 targetAx3(position, xDirection);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(tube, transformation);
  return transform.Shape();
}

/**
 * @brief 创建矩形钢管截面轮廓
 * @param height 高度 (Z轴方向)
 * @param width 宽度 (Y轴方向)
 * @param thickness 厚度
 * @return TopoDS_Wire 生成的截面轮廓线
 */
TopoDS_Wire create_rectangular_tube_profile(double height, double width,
                                            double thickness) {
  BRepBuilderAPI_MakeWire outerWireMaker;
  BRepBuilderAPI_MakeWire innerWireMaker;

  // 计算内外轮廓关键点坐标
  double halfHeight = height / 2;
  double halfWidth = width / 2;

  // 外轮廓点
  gp_Pnt outerP1(0, -halfWidth, -halfHeight);
  gp_Pnt outerP2(0, halfWidth, -halfHeight);
  gp_Pnt outerP3(0, halfWidth, halfHeight);
  gp_Pnt outerP4(0, -halfWidth, halfHeight);

  // 内轮廓点
  gp_Pnt innerP1(0, -halfWidth + thickness, -halfHeight + thickness);
  gp_Pnt innerP2(0, halfWidth - thickness, -halfHeight + thickness);
  gp_Pnt innerP3(0, halfWidth - thickness, halfHeight - thickness);
  gp_Pnt innerP4(0, -halfWidth + thickness, halfHeight - thickness);

  // 创建外轮廓
  outerWireMaker.Add(BRepBuilderAPI_MakeEdge(outerP1, outerP2).Edge());
  outerWireMaker.Add(BRepBuilderAPI_MakeEdge(outerP2, outerP3).Edge());
  outerWireMaker.Add(BRepBuilderAPI_MakeEdge(outerP3, outerP4).Edge());
  outerWireMaker.Add(BRepBuilderAPI_MakeEdge(outerP4, outerP1).Edge());

  // 创建内轮廓
  innerWireMaker.Add(BRepBuilderAPI_MakeEdge(innerP1, innerP2).Edge());
  innerWireMaker.Add(BRepBuilderAPI_MakeEdge(innerP2, innerP3).Edge());
  innerWireMaker.Add(BRepBuilderAPI_MakeEdge(innerP3, innerP4).Edge());
  innerWireMaker.Add(BRepBuilderAPI_MakeEdge(innerP4, innerP1).Edge());

  // 创建面
  BRepBuilderAPI_MakeFace outerFaceMaker(outerWireMaker.Wire());
  BRepBuilderAPI_MakeFace innerFaceMaker(innerWireMaker.Wire());

  if (!outerFaceMaker.IsDone() || !innerFaceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create tube faces");
  }

  // 执行布尔差操作
  BRepAlgoAPI_Cut cutter(outerFaceMaker.Face(), innerFaceMaker.Face());
  if (!cutter.IsDone()) {
    throw Standard_ConstructionError("Failed to create tube profile");
  }

  // 获取截面轮廓线
  TopExp_Explorer explorer(cutter.Shape(), TopAbs_WIRE);
  if (!explorer.More()) {
    throw Standard_ConstructionError("Failed to extract tube profile wire");
  }

  return TopoDS::Wire(explorer.Current());
}

/**
 * @brief 创建矩形钢管
 * @param params 矩形钢管参数
 * @return TopoDS_Shape 生成的矩形钢管形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape
create_rectangular_steel_tube(const rectangular_steel_tube_params &params) {
  // 参数验证
  if (params.height <= 0 || params.width <= 0 || params.thickness <= 0 ||
      params.length <= 0) {
    throw Standard_ConstructionError("All dimensions must be positive");
  }
  if (params.thickness * 2 >= params.height ||
      params.thickness * 2 >= params.width) {
    throw Standard_ConstructionError(
        "Thickness too large for given dimensions");
  }

  // 创建截面轮廓
  TopoDS_Wire profile = create_rectangular_tube_profile(
      params.height, params.width, params.thickness);

  // 创建截面面
  BRepBuilderAPI_MakeFace faceMaker(profile);
  if (!faceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create tube face");
  }

  // 沿X轴拉伸
  BRepPrimAPI_MakePrism prismMaker(faceMaker.Face(),
                                   gp_Vec(params.length, 0, 0));

  return prismMaker.Shape();
}

/**
 * @brief 创建带定位的矩形钢管
 * @param params 矩形钢管参数
 * @param position 钢管起点位置
 * @param xDirection 长度方向（默认X轴）
 * @param zDirection 高度方向（默认Z轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape
create_rectangular_steel_tube(const rectangular_steel_tube_params &params,
                              const gp_Pnt &position, const gp_Dir &xDirection,
                              const gp_Dir &zDirection) {
  // 首先创建标准方向的矩形钢管
  TopoDS_Shape tube = create_rectangular_steel_tube(params);

  // 计算Y方向（根据右手定则）
  gp_Dir yDirection = zDirection.Crossed(xDirection);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX()); // Z:高度, X:长度
  gp_Ax3 targetAx3(position, zDirection, xDirection);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(tube, transformation);
  return transform.Shape();
}

/**
 * @brief 创建方形钢管截面轮廓
 * @param size 外形尺寸
 * @param thickness 壁厚
 * @return TopoDS_Wire 生成的截面轮廓线
 */
TopoDS_Wire create_square_tube_profile(double size, double thickness) {
  BRepBuilderAPI_MakeWire outerWireMaker;
  BRepBuilderAPI_MakeWire innerWireMaker;

  // 计算内外轮廓关键点坐标
  double halfSize = size / 2;
  double innerHalfSize = halfSize - thickness;

  // 外轮廓点
  gp_Pnt outerP1(0, -halfSize, -halfSize);
  gp_Pnt outerP2(0, halfSize, -halfSize);
  gp_Pnt outerP3(0, halfSize, halfSize);
  gp_Pnt outerP4(0, -halfSize, halfSize);

  // 内轮廓点
  gp_Pnt innerP1(0, -innerHalfSize, -innerHalfSize);
  gp_Pnt innerP2(0, innerHalfSize, -innerHalfSize);
  gp_Pnt innerP3(0, innerHalfSize, innerHalfSize);
  gp_Pnt innerP4(0, -innerHalfSize, innerHalfSize);

  // 创建外轮廓
  outerWireMaker.Add(BRepBuilderAPI_MakeEdge(outerP1, outerP2).Edge());
  outerWireMaker.Add(BRepBuilderAPI_MakeEdge(outerP2, outerP3).Edge());
  outerWireMaker.Add(BRepBuilderAPI_MakeEdge(outerP3, outerP4).Edge());
  outerWireMaker.Add(BRepBuilderAPI_MakeEdge(outerP4, outerP1).Edge());

  // 创建内轮廓
  innerWireMaker.Add(BRepBuilderAPI_MakeEdge(innerP1, innerP2).Edge());
  innerWireMaker.Add(BRepBuilderAPI_MakeEdge(innerP2, innerP3).Edge());
  innerWireMaker.Add(BRepBuilderAPI_MakeEdge(innerP3, innerP4).Edge());
  innerWireMaker.Add(BRepBuilderAPI_MakeEdge(innerP4, innerP1).Edge());

  // 创建面
  BRepBuilderAPI_MakeFace outerFaceMaker(outerWireMaker.Wire());
  BRepBuilderAPI_MakeFace innerFaceMaker(innerWireMaker.Wire());

  if (!outerFaceMaker.IsDone() || !innerFaceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create tube faces");
  }

  // 执行布尔差操作
  BRepAlgoAPI_Cut cutter(outerFaceMaker.Face(), innerFaceMaker.Face());
  if (!cutter.IsDone()) {
    throw Standard_ConstructionError("Failed to create tube profile");
  }

  // 获取截面轮廓线
  TopExp_Explorer explorer(cutter.Shape(), TopAbs_WIRE);
  if (!explorer.More()) {
    throw Standard_ConstructionError("Failed to extract tube profile wire");
  }

  return TopoDS::Wire(explorer.Current());
}

/**
 * @brief 创建方形钢管
 * @param params 方形钢管参数
 * @return TopoDS_Shape 生成的方形钢管形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_square_steel_tube(const square_steel_tube_params &params) {
  // 参数验证
  if (params.size <= 0 || params.thickness <= 0 || params.length <= 0) {
    throw Standard_ConstructionError("All dimensions must be positive");
  }
  if (params.thickness * 2 >= params.size) {
    throw Standard_ConstructionError("Thickness too large for given size");
  }

  // 创建截面轮廓
  TopoDS_Wire profile =
      create_square_tube_profile(params.size, params.thickness);

  // 创建截面面
  BRepBuilderAPI_MakeFace faceMaker(profile);
  if (!faceMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create tube face");
  }

  // 沿X轴拉伸
  BRepPrimAPI_MakePrism prismMaker(faceMaker.Face(),
                                   gp_Vec(params.length, 0, 0));

  return prismMaker.Shape();
}

/**
 * @brief 创建带定位的方形钢管
 * @param params 方形钢管参数
 * @param position 钢管起点位置
 * @param xDirection 长度方向（默认X轴）
 * @param zDirection 高度方向（默认Z轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape create_square_steel_tube(const square_steel_tube_params &params,
                                      const gp_Pnt &position,
                                      const gp_Dir &xDirection,
                                      const gp_Dir &zDirection) {
  // 首先创建标准方向的方形钢管
  TopoDS_Shape tube = create_square_steel_tube(params);

  // 计算Y方向（根据右手定则）
  gp_Dir yDirection = zDirection.Crossed(xDirection);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX()); // Z:高度, X:长度
  gp_Ax3 targetAx3(position, zDirection, xDirection);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(tube, transformation);
  return transform.Shape();
}

/**
 * @brief 创建双槽钢
 * @param params 双槽钢参数
 * @return TopoDS_Shape 生成的双槽钢形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape
create_double_channel_steel(const double_channel_steel_params &params) {
  // 参数验证
  if (params.height <= 0 || params.flangeWidth <= 0 ||
      params.webThickness <= 0 || params.flangeThickness <= 0 ||
      params.length <= 0) {
    throw Standard_ConstructionError("All dimensions must be positive");
  }
  if (params.spacing < 0) {
    throw Standard_ConstructionError("Spacing must be non-negative");
  }

  // 创建第一个槽钢（正向）
  TopoDS_Shape channel1 = create_beam_channel(params);

  // 创建第二个槽钢（反向）
  gp_Trsf mirror;
  mirror.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp::DZ(), gp::DX()));
  BRepBuilderAPI_Transform mirrorTransform(channel1, mirror);
  TopoDS_Shape channel2 = mirrorTransform.Shape();

  // 移动第二个槽钢到指定间距位置
  gp_Trsf translation;
  translation.SetTranslation(gp_Vec(0, params.spacing + params.flangeWidth, 0));
  BRepBuilderAPI_Transform spacingTransform(channel2, translation);
  channel2 = spacingTransform.Shape();

  // 合并两个槽钢
  BRepAlgoAPI_Fuse fuser(channel1, channel2);
  if (!fuser.IsDone()) {
    throw Standard_ConstructionError("Failed to fuse channel steels");
  }

  return fuser.Shape();
}

/**
 * @brief 创建带定位的双槽钢
 * @param params 双槽钢参数
 * @param position 起点位置
 * @param xDirection 长度方向（默认X轴）
 * @param zDirection 腹板方向（默认Z轴）
 * @return TopoDS_Shape
 */
TopoDS_Shape
create_double_channel_steel(const double_channel_steel_params &params,
                            const gp_Pnt &position, const gp_Dir &xDirection,
                            const gp_Dir &zDirection) {
  // 首先创建标准方向的双槽钢
  TopoDS_Shape doubleChannel = create_double_channel_steel(params);

  // 计算Y方向（根据右手定则）
  gp_Dir yDirection = zDirection.Crossed(xDirection);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX()); // Z:腹板方向, X:长度方向
  gp_Ax3 targetAx3(position, zDirection, xDirection);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(doubleChannel, transformation);
  return transform.Shape();
}

TopoDS_Shape create_equilateral_double_angle_steel(
    const equilateral_double_angle_steel_params &params) {
  // 参数验证
  if (params.L <= 0 || params.X <= 0 || params.length <= 0) {
    throw Standard_ConstructionError("All dimensions must be positive");
  }
  if (params.spacing < 0) {
    throw Standard_ConstructionError("Spacing must be non-negative");
  }

  // 创建第一个角钢（正向）
  TopoDS_Shape angle1 = create_equilateral_angle_steel(params);

  // 创建第二个角钢（反向）
  gp_Trsf mirror;
  mirror.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp::DZ(), gp::DX()));
  BRepBuilderAPI_Transform mirrorTransform(angle1, mirror);
  TopoDS_Shape angle2 = mirrorTransform.Shape();

  // 移动第二个角钢到指定间距位置
  gp_Trsf translation;
  translation.SetTranslation(gp_Vec(0, params.spacing + params.L, 0));
  BRepBuilderAPI_Transform spacingTransform(angle2, translation);
  angle2 = spacingTransform.Shape();

  // 合并两个角钢
  BRepAlgoAPI_Fuse fuser(angle1, angle2);
  if (!fuser.IsDone()) {
    throw Standard_ConstructionError("Failed to fuse angle steels");
  }

  return fuser.Shape();
}

TopoDS_Shape create_equilateral_double_angle_steel(
    const equilateral_double_angle_steel_params &params, const gp_Pnt &position,
    const gp_Dir &xDirection, const gp_Dir &zDirection) {
  // 首先创建标准方向的双角钢
  TopoDS_Shape doubleAngle = create_equilateral_double_angle_steel(params);

  // 计算Y方向（根据右手定则）
  gp_Dir yDirection = zDirection.Crossed(xDirection);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, zDirection, xDirection);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(doubleAngle, transformation);
  return transform.Shape();
}

TopoDS_Shape
create_unequal_angle_steel(const unequal_angle_steel_params &params) {
  // 参数验证
  if (params.L1 <= 0 || params.L2 <= 0 || params.X <= 0 || params.length <= 0) {
    throw Standard_ConstructionError("All dimensions must be positive");
  }
  if (params.spacing < 0) {
    throw Standard_ConstructionError("Spacing must be non-negative");
  }

  // 创建第一个角钢（正向）
  TopoDS_Shape angle1 = create_scalene_angle_steel(params);

  // 创建第二个角钢（反向）
  gp_Trsf mirror;
  mirror.SetMirror(gp_Ax2(gp_Pnt(0, 0, 0), gp::DZ(), gp::DX()));
  BRepBuilderAPI_Transform mirrorTransform(angle1, mirror);
  TopoDS_Shape angle2 = mirrorTransform.Shape();

  // 移动第二个角钢到指定间距位置
  gp_Trsf translation;
  translation.SetTranslation(gp_Vec(0, params.spacing + params.L2, 0));
  BRepBuilderAPI_Transform spacingTransform(angle2, translation);
  angle2 = spacingTransform.Shape();

  // 合并两个角钢
  BRepAlgoAPI_Fuse fuser(angle1, angle2);
  if (!fuser.IsDone()) {
    throw Standard_ConstructionError("Failed to fuse angle steels");
  }

  return fuser.Shape();
}

TopoDS_Shape
create_unequal_angle_steel(const unequal_angle_steel_params &params,
                           const gp_Pnt &position, const gp_Dir &xDirection,
                           const gp_Dir &zDirection) {
  // 首先创建标准方向的双角钢
  TopoDS_Shape doubleAngle = create_unequal_angle_steel(params);

  // 计算Y方向（根据右手定则）
  gp_Dir yDirection = zDirection.Crossed(xDirection);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, zDirection, xDirection);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(doubleAngle, transformation);
  return transform.Shape();
}

TopoDS_Shape create_polygon_tube(const polygon_tube_params &params) {
  // 参数验证
  if (params.side_length <= 0.0) {
    throw Standard_ConstructionError("Side length must be positive");
  }
  if (params.thickness <= 0.0) {
    throw Standard_ConstructionError("Thickness must be positive");
  }
  if (params.length <= 0.0) {
    throw Standard_ConstructionError("Length must be positive");
  }
  if (params.sides < 3) {
    throw Standard_ConstructionError("Number of sides must be at least 3");
  }

  // 计算外接圆半径
  double outer_radius = params.side_length / (2 * sin(M_PI / params.sides));
  double inner_radius = outer_radius - params.thickness;

  // 创建外多边形
  BRepBuilderAPI_MakePolygon outer_poly;
  for (int i = 0; i < params.sides; ++i) {
    double angle = 2 * M_PI * i / params.sides;
    double x = outer_radius * cos(angle);
    double y = outer_radius * sin(angle);
    outer_poly.Add(gp_Pnt(x, y, 0));
  }
  outer_poly.Close();
  TopoDS_Wire outer_wire = outer_poly.Wire();

  // 创建内多边形
  BRepBuilderAPI_MakePolygon inner_poly;
  for (int i = 0; i < params.sides; ++i) {
    double angle = 2 * M_PI * i / params.sides;
    double x = inner_radius * cos(angle);
    double y = inner_radius * sin(angle);
    inner_poly.Add(gp_Pnt(x, y, 0));
  }
  inner_poly.Close();
  TopoDS_Wire inner_wire = inner_poly.Wire();

  // 创建面
  BRepBuilderAPI_MakeFace outer_face(outer_wire);
  BRepBuilderAPI_MakeFace inner_face(inner_wire);
  if (!outer_face.IsDone() || !inner_face.IsDone()) {
    throw Standard_ConstructionError("Failed to create polygon faces");
  }

  // 执行布尔差操作
  BRepAlgoAPI_Cut cutter(outer_face.Face(), inner_face.Face());
  if (!cutter.IsDone()) {
    throw Standard_ConstructionError("Failed to create polygon tube profile");
  }

  // 沿X轴拉伸
  gp_Vec extrusion_vec(params.length, 0, 0);
  BRepPrimAPI_MakePrism prism(cutter.Shape(), extrusion_vec);
  if (!prism.IsDone()) {
    throw Standard_ConstructionError("Failed to extrude polygon tube");
  }

  return prism.Shape();
}

TopoDS_Shape create_polygon_tube(const polygon_tube_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &xDirection) {
  // 首先创建标准方向的钢管
  TopoDS_Shape tube = create_polygon_tube(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DX());
  gp_Ax3 targetAx3(position, xDirection);

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
                                          const gp_Dir &direction) {
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
                                        const gp_Dir &direction) {
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
TopoDS_Shape create_rock_anchor_foundation(const rock_anchor_params &params,
                                           const gp_Pnt &position,
                                           const gp_Dir &direction) {
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
TopoDS_Shape create_rock_pile_cap_foundation(const rock_pile_cap_params &params,
                                             const gp_Pnt &position,
                                             const gp_Dir &direction) {
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
    const gp_Dir &direction) {
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
    const gp_Dir &direction) {
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
                            const gp_Pnt &position, const gp_Dir &direction) {
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
                                    const gp_Dir &direction) {
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
                             const gp_Pnt &position, const gp_Dir &direction) {
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
                              const gp_Pnt &position, const gp_Dir &direction) {
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
    const gp_Dir &direction) {
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
                                    const gp_Dir &direction) {
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
                                const gp_Dir &direction) {
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
                               const gp_Dir &direction) {
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
                                 const gp_Dir &direction) {
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
                                 const gp_Dir &direction) {
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
    const gp_Pnt &position, const gp_Dir &direction) {
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
    const gp_Pnt &position, const gp_Dir &direction) {
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
  double tension = params.ratedStrength * 0.25;       // 假设使用25%的额定拉断力
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

std::vector<gp_Pnt> generate_circular_positions(int subNum, double radius,
                                                double angleOffset = 0.0) {
  std::vector<gp_Pnt> positions;
  for (int i = 0; i < subNum; i++) {
    double angle = angleOffset + 2 * M_PI * i / subNum;
    positions.emplace_back(radius * cos(angle), radius * sin(angle), 0);
  }
  return positions;
}

TopoDS_Shape create_y_structure(const gp_Pnt &p1, const gp_Pnt &p2,
                                double thickness) {
  // 创建连接两个槽位的Y型结构
  BRepBuilderAPI_MakeWire wire;

  // 中心点（悬挂点）
  gp_Pnt center(0, 0, -thickness * 2);

  // 构建三条边
  wire.Add(BRepBuilderAPI_MakeEdge(center, p1).Edge());
  wire.Add(BRepBuilderAPI_MakeEdge(center, p2).Edge());
  wire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());

  // 拉伸为实体
  return BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(wire.Wire()),
                               gp_Vec(0, 0, thickness))
      .Shape();
}

/**
 * @brief 创建星型连接器
 * @param center 中心点坐标
 * @param armCount 臂数(3-6)
 * @param armLength 臂长度
 * @param armWidth 臂宽度
 * @param thickness 厚度
 * @return TopoDS_Shape 生成的星型连接器形状
 */
TopoDS_Shape create_star_connector(const gp_Pnt &center, int armCount,
                                   double armLength, double armWidth,
                                   double thickness) {
  // 参数验证
  if (armCount < 3 || armCount > 6) {
    throw Standard_ConstructionError("臂数必须在3-6之间");
  }
  if (armLength <= 0 || armWidth <= 0 || thickness <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }

  // 创建中心圆柱
  gp_Ax2 axis(center, gp_Dir(0, 0, 1));
  TopoDS_Shape hub =
      BRepPrimAPI_MakeCylinder(axis, armWidth * 1.5, thickness).Shape();

  // 创建各个臂
  BRepAlgoAPI_Fuse fuser;
  for (int i = 0; i < armCount; i++) {
    double angle = 2 * M_PI * i / armCount;
    gp_Dir dir(cos(angle), sin(angle), 0);

    // 臂的起点和终点
    gp_Pnt start = center.Translated(gp_Vec(dir) * armWidth * 1.5);
    gp_Pnt end = start.Translated(gp_Vec(dir) * armLength);

    // 创建臂
    BRepBuilderAPI_MakeWire armWire;
    armWire.Add(BRepBuilderAPI_MakeEdge(start, end).Edge());
    TopoDS_Face armFace = BRepBuilderAPI_MakeFace(armWire.Wire()).Face();
    TopoDS_Shape arm =
        BRepPrimAPI_MakePrism(armFace, gp_Vec(0, 0, thickness)).Shape();

    // 合并到中心
    if (i == 0) {
      fuser = BRepAlgoAPI_Fuse(hub, arm);
    } else {
      fuser = BRepAlgoAPI_Fuse(fuser.Shape(), arm);
    }
  }

  if (!fuser.IsDone()) {
    throw Standard_ConstructionError("星型连接器创建失败");
  }

  return fuser.Shape();
}
/**
 * @brief 创建三角形钢板
 * @param p1 第一个顶点
 * @param p2 第二个顶点
 * @param p3 第三个顶点
 * @param thickness 钢板厚度
 * @param filletRadius 边缘倒角半径(默认0)
 * @return TopoDS_Shape 生成的三角形钢板形状
 */
TopoDS_Shape create_triangular_plate(const gp_Pnt &p1, const gp_Pnt &p2,
                                     const gp_Pnt &p3, double thickness,
                                     double filletRadius = 0) {
  // 参数验证
  if (thickness <= 0) {
    throw Standard_ConstructionError("钢板厚度必须为正数");
  }
  if (filletRadius < 0) {
    throw Standard_ConstructionError("倒角半径不能为负数");
  }

  // 创建三角形轮廓
  BRepBuilderAPI_MakeWire triangleWire;
  triangleWire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  triangleWire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
  triangleWire.Add(BRepBuilderAPI_MakeEdge(p3, p1).Edge());

  // 创建三角形面
  TopoDS_Face triangleFace =
      BRepBuilderAPI_MakeFace(triangleWire.Wire()).Face();

  // 计算拉伸方向
  gp_Vec v1(p2.X() - p1.X(), p2.Y() - p1.Y(), p2.Z() - p1.Z());
  gp_Vec v2(p3.X() - p1.X(), p3.Y() - p1.Y(), p3.Z() - p1.Z());
  gp_Vec extrudeDir = v1.Crossed(v2);
  extrudeDir.Normalize();
  extrudeDir *= thickness;

  // 拉伸成体
  TopoDS_Shape plate = BRepPrimAPI_MakePrism(triangleFace, extrudeDir).Shape();

  // 添加倒角(如果半径>0)
  if (filletRadius > 0) {
    BRepFilletAPI_MakeFillet fillet(plate);
    TopExp_Explorer explorer(plate, TopAbs_EDGE);
    while (explorer.More()) {
      fillet.Add(filletRadius, TopoDS::Edge(explorer.Current()));
      explorer.Next();
    }
    if (fillet.IsDone()) {
      plate = fillet.Shape();
    }
  }

  return plate;
}
TopoDS_Shape create_h_plate(const gp_Pnt &p1, const gp_Pnt &p2, double width) {
  // 参数验证
  if (width <= 0) {
    throw Standard_ConstructionError("钢板宽度必须为正数");
  }

  // 计算H型钢板各部分尺寸
  double length = p1.Distance(p2);
  double flangeWidth = width / 3;
  double webThickness = width / 10;

  // 创建H型钢板的六个角点
  gp_Pnt p1_top(p1.X(), p1.Y(), width / 2);
  gp_Pnt p1_bot(p1.X(), p1.Y(), -width / 2);
  gp_Pnt p2_top(p2.X(), p2.Y(), width / 2);
  gp_Pnt p2_bot(p2.X(), p2.Y(), -width / 2);

  // 上翼缘
  BRepBuilderAPI_MakeWire topFlangeWire;
  topFlangeWire.Add(BRepBuilderAPI_MakeEdge(p1_top, p2_top).Edge());
  TopoDS_Face topFlange = BRepBuilderAPI_MakeFace(topFlangeWire.Wire()).Face();
  TopoDS_Shape topFlangeExt =
      BRepPrimAPI_MakePrism(topFlange, gp_Vec(0, 0, -flangeWidth)).Shape();

  // 下翼缘
  BRepBuilderAPI_MakeWire botFlangeWire;
  botFlangeWire.Add(BRepBuilderAPI_MakeEdge(p1_bot, p2_bot).Edge());
  TopoDS_Face botFlange = BRepBuilderAPI_MakeFace(botFlangeWire.Wire()).Face();
  TopoDS_Shape botFlangeExt =
      BRepPrimAPI_MakePrism(botFlange, gp_Vec(0, 0, flangeWidth)).Shape();

  // 腹板
  gp_Pnt webTop(p1.X(), p1.Y(), flangeWidth / 2);
  gp_Pnt webBot(p2.X(), p2.Y(), flangeWidth / 2);
  BRepBuilderAPI_MakeWire webWire;
  webWire.Add(BRepBuilderAPI_MakeEdge(webTop, webBot).Edge());
  TopoDS_Face web = BRepBuilderAPI_MakeFace(webWire.Wire()).Face();
  TopoDS_Shape webExt =
      BRepPrimAPI_MakePrism(web, gp_Vec(0, 0, -flangeWidth * 2)).Shape();

  // 合并所有部件
  BRepAlgoAPI_Fuse fuser(topFlangeExt, botFlangeExt);
  fuser = BRepAlgoAPI_Fuse(fuser.Shape(), webExt);

  if (!fuser.IsDone()) {
    throw Standard_ConstructionError("H型钢板创建失败");
  }

  return fuser.Shape();
}

/**
 * @brief 创建U型线夹单元
 * @param width 线夹宽度
 * @param height 线夹高度
 * @param radius 导线半径
 * @param position 线夹位置
 * @return TopoDS_Shape
 */
TopoDS_Shape create_u_clamp(double width, double height, double radius,
                            const gp_Pnt &position) {
  // 创建U型线夹主体
  TopoDS_Shape body = create_rectangular_beam(width, height, height, position);

  // 创建导线槽(半圆形凹槽)
  gp_Ax2 axis(position, gp_Dir(0, 0, 1));
  TopoDS_Shape groove = BRepPrimAPI_MakeCylinder(axis, radius, width).Shape();

  // 移动凹槽到正确位置
  gp_Trsf move;
  move.SetTranslation(gp_Vec(0, 0, height / 2 - radius));
  groove = BRepBuilderAPI_Transform(groove, move).Shape();

  // 从主体中减去凹槽
  BRepAlgoAPI_Cut cutter(body, groove);
  return cutter.Shape();
}

/**
 * @brief 创建X型连接框架
 * @param size 框架尺寸
 * @param thickness 框架厚度
 * @param center 中心位置
 * @return TopoDS_Shape
 */
TopoDS_Shape create_x_frame(double size, double thickness,
                            const gp_Pnt &center) {
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  // 创建两个交叉的矩形梁
  TopoDS_Shape beam1 = create_rectangular_beam(
      size, thickness, thickness, gp_Pnt(center.X(), center.Y(), center.Z()));

  TopoDS_Shape beam2 = create_rectangular_beam(
      thickness, size, thickness, gp_Pnt(center.X(), center.Y(), center.Z()));

  // 旋转45度形成X型
  gp_Trsf rotate;
  rotate.SetRotation(gp_Ax1(center, gp_Dir(0, 0, 1)), M_PI / 4);
  beam2 = BRepBuilderAPI_Transform(beam2, rotate).Shape();

  builder.Add(result, beam1);
  builder.Add(result, beam2);
  return result;
}

TopoDS_Shape create_hex_bolt(const gp_Ax2 &axis, double radius, double height) {
  BRepBuilderAPI_MakeWire wire;
  for (int i = 0; i < 6; i++) {
    double angle = 2 * M_PI * i / 6;
    double x1 = radius * cos(angle);
    double y1 = radius * sin(angle);
    double x2 = radius * cos(angle + 2 * M_PI / 6);
    double y2 = radius * sin(angle + 2 * M_PI / 6);

    gp_Pnt p1(x1, y1, 0);
    gp_Pnt p2(x2, y2, 0);
    wire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  }
  TopoDS_Face face = BRepBuilderAPI_MakeFace(wire.Wire()).Face();
  return BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, height)).Shape();
};

TopoDS_Shape create_single_suspension_clamp(const insulator_params &params) {
  // 使用绝缘子参数中的导体直径
  double conductorDiameter = params.splitDistance * 0.4 / sqrt(params.subNum);

  // 优化后的尺寸参数（符合DL/T 757）
  double outerRadius = conductorDiameter * 1.25;   // 1.25倍导线直径
  double innerRadius = conductorDiameter * 1.05;   // 考虑导线公差
  double height = conductorDiameter * 2.5;         // 增加高度提高握力
  double boltHoleRadius = conductorDiameter * 0.3; // 螺栓孔尺寸

  // 构建U型槽线框
  BRepBuilderAPI_MakeWire wire;

  // 底部半圆外轮廓
  gp_Pnt p1(outerRadius, 0, 0);
  gp_Pnt p2(-outerRadius, 0, 0);
  gp_Circ outerCircle(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0)), outerRadius);
  TopoDS_Edge outerArc = BRepBuilderAPI_MakeEdge(outerCircle, p1, p2).Edge();

  // 底部半圆内轮廓
  gp_Pnt p3(-innerRadius, 0, 0);
  gp_Pnt p4(innerRadius, 0, 0);
  gp_Circ innerCircle(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0)), innerRadius);
  TopoDS_Edge innerArc = BRepBuilderAPI_MakeEdge(innerCircle, p3, p4).Edge();

  // 左侧垂直线
  TopoDS_Edge leftEdge =
      BRepBuilderAPI_MakeEdge(gp_Pnt(-outerRadius, 0, 0),
                              gp_Pnt(-outerRadius, 0, height))
          .Edge();

  // 右侧垂直线
  TopoDS_Edge rightEdge =
      BRepBuilderAPI_MakeEdge(gp_Pnt(outerRadius, 0, 0),
                              gp_Pnt(outerRadius, 0, height))
          .Edge();

  // 顶部连接线
  TopoDS_Edge topEdge = BRepBuilderAPI_MakeEdge(gp_Pnt(-outerRadius, 0, height),
                                                gp_Pnt(outerRadius, 0, height))
                            .Edge();

  // 组装线框
  wire.Add(outerArc);
  wire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge()); // 底部连接线
  wire.Add(innerArc);
  wire.Add(BRepBuilderAPI_MakeEdge(p4, p1).Edge()); // 底部连接线
  wire.Add(leftEdge);
  wire.Add(topEdge);
  wire.Add(rightEdge);

  // 旋转成型（绕Y轴旋转360度形成U型线夹）
  gp_Ax1 axis(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0));

  // 组装完整线夹
  BRepPrimAPI_MakeRevol revol(wire.Wire(), axis);
  TopoDS_Shape clamp = revol.Shape();

  // 螺栓参数优化
  double boltRadius = conductorDiameter * 0.3; // 螺栓直径
  double boltLength = height * 0.4;            // 螺栓长度
  double nutThickness = boltRadius * 0.6;      // 螺母厚度
  double nutRadius = boltRadius * 1.5;         // 螺母直径

  // 创建螺栓组件（不创建螺栓孔）
  gp_Ax2 boltAxis1(gp_Pnt(0, height * 0.7, outerRadius * 0.8), gp_Dir(0, 1, 0));
  TopoDS_Shape bolt1 = create_hex_bolt(boltAxis1, boltRadius, boltLength);
  TopoDS_Shape nut1 = create_hex_bolt(
      gp_Ax2(gp_Pnt(0, height * 0.7 + boltLength, outerRadius * 0.8),
             gp_Dir(0, 1, 0)),
      nutRadius, nutThickness);

  gp_Ax2 boltAxis2(gp_Pnt(0, height * 0.7, -outerRadius * 0.8),
                   gp_Dir(0, 1, 0));
  TopoDS_Shape bolt2 = create_hex_bolt(boltAxis2, boltRadius, boltLength);
  TopoDS_Shape nut2 = create_hex_bolt(
      gp_Ax2(gp_Pnt(0, height * 0.7 + boltLength, -outerRadius * 0.8),
             gp_Dir(0, 1, 0)),
      nutRadius, nutThickness);

  // 直接合并所有部件
  BRepAlgoAPI_Fuse fuser(clamp, bolt1);
  fuser = BRepAlgoAPI_Fuse(fuser.Shape(), nut1);
  fuser = BRepAlgoAPI_Fuse(fuser.Shape(), bolt2);
  fuser = BRepAlgoAPI_Fuse(fuser.Shape(), nut2);

  return fuser.Shape();
}

TopoDS_Shape create_single_tension_clamp(const insulator_params &params) {
  // 使用绝缘子参数中的导体直径和分裂间距
  double conductorDiameter = params.splitDistance * 0.4 / sqrt(params.subNum);
  double fittingLength = params.fittingLengths.leftUpper; // 使用左上金具长度

  // 参数验证
  if (conductorDiameter <= 0 || fittingLength <= 0) {
    throw Standard_ConstructionError("导线直径和线夹长度必须为正数");
  }

  // 优化后的尺寸参数（符合DL/T 757）
  double length = fittingLength;
  double width = conductorDiameter * 1.5; // 1.5倍导线直径
  double thickness = conductorDiameter * 0.5;
  double grooveRadius = conductorDiameter * 1.1; // 考虑导线公差

  // 构建楔形主体（带加强筋）
  BRepBuilderAPI_MakeWire wire;
  gp_Pnt p1(0, 0, 0);
  gp_Pnt p2(width, 0, 0);
  gp_Pnt p3(width * 0.9, length * 0.2, 0); // 20%位置开始收窄
  gp_Pnt p4(width - thickness, length, 0);
  gp_Pnt p5(thickness, length, 0);
  gp_Pnt p6(width * 0.1, length * 0.2, 0); // 对称收窄

  wire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  wire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
  wire.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
  wire.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge());
  wire.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge());
  wire.Add(BRepBuilderAPI_MakeEdge(p6, p1).Edge());

  // 拉伸成型
  TopoDS_Shape clamp =
      BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(wire.Wire()).Face(),
                            gp_Vec(0, 0, width))
          .Shape();

  // 添加导线槽（带防滑齿）
  gp_Ax2 grooveAxis(gp_Pnt(width / 2, length * 0.6, width / 2),
                    gp_Dir(0, 1, 0));
  TopoDS_Shape groove =
      BRepPrimAPI_MakeCylinder(grooveAxis, grooveRadius, length * 0.8).Shape();

  // 创建螺栓组件
  double boltRadius = conductorDiameter * 0.25; // 螺栓直径
  double nutHeight = conductorDiameter * 0.2;   // 螺母高度
  double boltHeight = width * 1.2;              // 螺栓长度

  // 螺栓1
  gp_Ax2 boltAxis1(gp_Pnt(width * 0.3, length * 0.8, width / 2),
                   gp_Dir(0, 1, 0));
  TopoDS_Shape bolt1 = create_hex_bolt(boltAxis1, boltRadius, boltHeight);
  TopoDS_Shape nut1 = create_hex_bolt(
      gp_Ax2(gp_Pnt(width * 0.3, length * 0.8, width / 2 + boltHeight),
             gp_Dir(0, 1, 0)),
      boltRadius * 1.5, nutHeight);

  // 螺栓2
  gp_Ax2 boltAxis2(gp_Pnt(width * 0.7, length * 0.8, width / 2),
                   gp_Dir(0, 1, 0));
  TopoDS_Shape bolt2 = create_hex_bolt(boltAxis2, boltRadius, boltHeight);
  TopoDS_Shape nut2 = create_hex_bolt(
      gp_Ax2(gp_Pnt(width * 0.7, length * 0.8, width / 2 + boltHeight),
             gp_Dir(0, 1, 0)),
      boltRadius * 1.5, nutHeight);

  // 创建螺栓孔（比螺栓稍大）
  TopoDS_Shape boltHole1 =
      BRepPrimAPI_MakeCylinder(boltAxis1, boltRadius * 1.1, boltHeight).Shape();
  TopoDS_Shape boltHole2 =
      BRepPrimAPI_MakeCylinder(boltAxis2, boltRadius * 1.1, boltHeight).Shape();

  // 布尔运算
  BRepAlgoAPI_Cut cutter(clamp, groove);
  cutter = BRepAlgoAPI_Cut(cutter.Shape(), boltHole1);
  cutter = BRepAlgoAPI_Cut(cutter.Shape(), boltHole2);

  // 合并螺栓组件
  BRepAlgoAPI_Fuse fuser(cutter.Shape(), bolt1);
  fuser = BRepAlgoAPI_Fuse(fuser.Shape(), nut1);
  fuser = BRepAlgoAPI_Fuse(fuser.Shape(), bolt2);
  fuser = BRepAlgoAPI_Fuse(fuser.Shape(), nut2);

  // 方向调整（耐张串保持水平）
  TopoDS_Shape result = fuser.Shape();
  gp_Trsf rotate;
  rotate.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0)), M_PI / 2);
  return BRepBuilderAPI_Transform(result, rotate).Shape();
}

// 创建双分裂悬垂线夹
TopoDS_Shape create_double_suspension_clamp(const insulator_params &params) {
  // 计算导线槽位置（根据subType调整）
  gp_Pnt pos1, pos2;
  if (params.subType == 1) { // 垂直排列
    pos1 = gp_Pnt(0, params.splitDistance / 2, 0);
    pos2 = gp_Pnt(0, -params.splitDistance / 2, 0);
  } else { // 水平排列（默认）
    pos1 = gp_Pnt(params.splitDistance / 2, 0, 0);
    pos2 = gp_Pnt(-params.splitDistance / 2, 0, 0);
  }

  // 创建复合体
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  // 第一个导线槽
  gp_Trsf trans1;
  trans1.SetTranslation(gp_Vec(pos1.X(), pos1.Y(), 0));
  builder.Add(result, BRepBuilderAPI_Transform(
                          create_single_suspension_clamp(params), trans1)
                          .Shape());

  // 第二个导线槽
  gp_Trsf trans2;
  trans2.SetTranslation(gp_Vec(pos2.X(), pos2.Y(), 0));
  builder.Add(result, BRepBuilderAPI_Transform(
                          create_single_suspension_clamp(params), trans2)
                          .Shape());

  // 添加悬垂线夹Y型支架
  TopoDS_Shape yoke =
      create_y_structure(pos1, pos2, params.splitDistance * 0.3);
  builder.Add(result, yoke);

  return result;
}

// 创建双分裂耐张线夹
TopoDS_Shape create_double_tension_clamp(const insulator_params &params) {
  // 计算导线槽位置（根据subType调整）
  gp_Pnt pos1, pos2;
  if (params.subType == 1) { // 垂直排列
    pos1 = gp_Pnt(0, params.splitDistance / 2, 0);
    pos2 = gp_Pnt(0, -params.splitDistance / 2, 0);
  } else { // 水平排列（默认）
    pos1 = gp_Pnt(params.splitDistance / 2, 0, 0);
    pos2 = gp_Pnt(-params.splitDistance / 2, 0, 0);
  }

  // 创建复合体
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  // 第一个导线槽
  gp_Trsf trans1;
  trans1.SetTranslation(gp_Vec(pos1.X(), pos1.Y(), 0));
  builder.Add(result, BRepBuilderAPI_Transform(
                          create_single_tension_clamp(params), trans1)
                          .Shape());

  // 第二个导线槽
  gp_Trsf trans2;
  trans2.SetTranslation(gp_Vec(pos2.X(), pos2.Y(), 0));
  builder.Add(result, BRepBuilderAPI_Transform(
                          create_single_tension_clamp(params), trans2)
                          .Shape());

  // 添加耐张线夹H型连接板
  TopoDS_Shape hPlate =
      create_h_plate(pos1, pos2, params.fittingLengths.leftUpper * 0.8);
  builder.Add(result, hPlate);

  return result;
}

TopoDS_Shape create_quad_suspension_clamp(const insulator_params &params) {
  // 参数验证
  if (params.splitDistance <= 0 || params.subNum < 4) {
    throw Standard_ConstructionError("分裂间距必须为正数且子导线数≥4");
  }

  // 根据GB/T 1179计算导体直径
  double conductorDiameter = params.splitDistance * 0.4 / sqrt(params.subNum);
  double braceWidth = conductorDiameter * 0.8; // 加强筋宽度
  double extension = conductorDiameter * 0.15; // 加强筋延伸长度

  // 十字形结构 - 四个悬挂点位置
  std::vector<gp_Pnt> positions = {gp_Pnt(params.splitDistance / 2, 0, 0),
                                   gp_Pnt(-params.splitDistance / 2, 0, 0),
                                   gp_Pnt(0, params.splitDistance / 2, 0),
                                   gp_Pnt(0, -params.splitDistance / 2, 0)};

  // 创建复合体
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  // 创建四个单分裂线夹并添加防晕环
  for (const auto &pos : positions) {
    // 创建单线夹
    TopoDS_Shape clamp = create_single_suspension_clamp(params);

    // 添加防晕环
    gp_Ax2 coronaAxis(pos, gp_Dir(0, 0, 1));
    TopoDS_Shape coronaRing =
        BRepPrimAPI_MakeTorus(coronaAxis, conductorDiameter * 1.2,
                              conductorDiameter * 0.1)
            .Shape();

    // 合并线夹和防晕环
    BRepAlgoAPI_Fuse fuser(clamp, coronaRing);

    // 移动到指定位置
    gp_Trsf trans;
    trans.SetTranslation(gp_Vec(pos.X(), pos.Y(), 0));
    builder.Add(result, BRepBuilderAPI_Transform(fuser.Shape(), trans).Shape());
  }

  // 加强筋优化（带延伸段）
  gp_Pnt xStart(-params.splitDistance / 2 - extension, 0, 0);
  gp_Pnt xEnd(params.splitDistance / 2 + extension, 0, 0);
  TopoDS_Shape xBrace = create_rectangular_beam(
      braceWidth, braceWidth, xStart.Distance(xEnd),
      gp_Pnt(0, 0, conductorDiameter / 2)); // 抬高位置避免干涉

  gp_Pnt yStart(0, -params.splitDistance / 2 - extension, 0);
  gp_Pnt yEnd(0, params.splitDistance / 2 + extension, 0);
  TopoDS_Shape yBrace =
      create_rectangular_beam(braceWidth, braceWidth, yStart.Distance(yEnd),
                              gp_Pnt(0, 0, conductorDiameter / 2));

  // 中心连接块增强
  TopoDS_Shape centerBlock =
      BRepPrimAPI_MakeBox(gp_Pnt(-braceWidth / 2, -braceWidth / 2, 0),
                          braceWidth, braceWidth, braceWidth)
          .Shape();

  // 合并所有部件
  BRepAlgoAPI_Fuse fuser(result, xBrace);
  fuser = BRepAlgoAPI_Fuse(fuser.Shape(), yBrace);
  fuser = BRepAlgoAPI_Fuse(fuser.Shape(), centerBlock);

  if (!fuser.IsDone()) {
    throw Standard_ConstructionError("四分裂悬垂线夹创建失败");
  }

  return fuser.Shape();
}

/**
 * @brief 创建六分裂悬垂线夹
 * @param params 绝缘子参数结构体
 * @return TopoDS_Shape 生成的线夹形状
 */
TopoDS_Shape create_hex_suspension_clamp(const insulator_params &params) {
  // 参数验证
  if (params.splitDistance <= 0 || params.subNum < 6) {
    throw Standard_ConstructionError("分裂间距必须为正数且子导线数≥6");
  }

  // 根据GB/T 1179计算导体直径
  double conductorDiameter = params.splitDistance * 0.4 / sqrt(params.subNum);
  double clampDiameter = conductorDiameter * 1.2;  // 线夹直径
  double centerSize = params.splitDistance * 0.45; // 中心连接件尺寸

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  // 创建六边形中心连接件
  BRepBuilderAPI_MakeWire centerWire;
  for (int i = 0; i < 6; i++) {
    double angle = 2 * M_PI * i / 6;
    double x1 = centerSize * cos(angle);
    double y1 = centerSize * sin(angle);
    double x2 = centerSize * cos(angle + 2 * M_PI / 6);
    double y2 = centerSize * sin(angle + 2 * M_PI / 6);
    centerWire.Add(
        BRepBuilderAPI_MakeEdge(gp_Pnt(x1, y1, 0), gp_Pnt(x2, y2, 0)).Edge());
  }
  TopoDS_Face centerFace = BRepBuilderAPI_MakeFace(centerWire.Wire()).Face();
  TopoDS_Shape centerPiece =
      BRepPrimAPI_MakePrism(centerFace, gp_Vec(0, 0, clampDiameter)).Shape();
  builder.Add(result, centerPiece);

  // 创建6个线夹单元
  double angleStep = 2 * M_PI / 6;
  double radius = params.splitDistance * 0.9; // 考虑安装间隙

  for (int i = 0; i < 6; i++) {
    double x = radius * cos(i * angleStep);
    double y = radius * sin(i * angleStep);

    // 创建带防晕环的线夹单元
    gp_Ax2 clampAxis(gp_Pnt(x, y, 0), gp_Dir(0, 0, 1));

    // 线夹主体
    TopoDS_Shape clamp = BRepPrimAPI_MakeCylinder(clampAxis, clampDiameter / 2,
                                                  clampDiameter * 1.5)
                             .Shape();

    // 防晕环
    TopoDS_Shape coronaRing =
        BRepPrimAPI_MakeTorus(clampAxis, clampDiameter * 1.2,
                              clampDiameter * 0.1)
            .Shape();

    // 合并线夹和防晕环
    BRepAlgoAPI_Fuse fuser(clamp, coronaRing);
    builder.Add(result, fuser.Shape());
  }

  // 添加径向加强筋
  for (int i = 0; i < 6; i++) {
    double angle = 2 * M_PI * i / 6;
    gp_Pnt start(centerSize * 0.8 * cos(angle), centerSize * 0.8 * sin(angle),
                 0);
    gp_Pnt end(radius * 0.9 * cos(angle), radius * 0.9 * sin(angle), 0);

    TopoDS_Shape brace = create_rectangular_beam(
        conductorDiameter * 0.6, conductorDiameter * 0.6, start.Distance(end),
        gp_Pnt((start.X() + end.X()) / 2, (start.Y() + end.Y()) / 2,
               clampDiameter / 2));
    builder.Add(result, brace);
  }

  return result;
}

/**
 * @brief 创建四分裂耐张线夹
 * @param params 绝缘子参数结构体
 * @return TopoDS_Shape 生成的线夹形状
 */
TopoDS_Shape create_quad_tension_clamp(const insulator_params &params) {
  // 参数验证
  if (params.splitDistance <= 0) {
    throw Standard_ConstructionError("分裂间距必须为正数");
  }

  // 根据GB/T 2317.3计算导线直径
  double conductorDiameter = params.splitDistance * 0.4 / sqrt(4);
  double clampWidth = conductorDiameter * 3.5;  // 3.5倍导线直径
  double clampHeight = conductorDiameter * 2.2; // 2.2倍导线直径
  double frameThickness = clampHeight * 0.8;    // 框架厚度为线夹高度的0.8倍

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  // 计算线夹单元位置(考虑安装间隙)
  double offset = params.splitDistance * 0.9 / sqrt(2);
  std::vector<gp_Pnt> positions = {
      gp_Pnt(offset, offset, 0), gp_Pnt(-offset, offset, 0),
      gp_Pnt(-offset, -offset, 0), gp_Pnt(offset, -offset, 0)};

  // 创建带防滑齿的线夹单元
  for (const auto &pos : positions) {
    // 创建U型线夹主体
    TopoDS_Shape clamp =
        create_u_clamp(clampWidth, clampHeight, conductorDiameter / 2, pos);

    builder.Add(result, clamp);
  }

  // 创建加强型中心连接框架
  TopoDS_Shape centerFrame = create_x_frame(
      offset * 1.3,                                   // 框架尺寸放大1.3倍
      frameThickness, gp_Pnt(0, 0, clampHeight / 2)); // 框架中心位置上移

  // 添加螺栓（代替螺栓孔）
  for (int i = 0; i < 4; i++) {
    double angle = M_PI_2 * i;
    gp_Pnt boltPos(offset * 0.7 * cos(angle), offset * 0.7 * sin(angle),
                   clampHeight / 2);

    // 创建螺栓（六角头朝外）
    gp_Ax2 boltAxis(boltPos, gp_Dir(cos(angle), sin(angle), 0));
    TopoDS_Shape bolt =
        create_hex_bolt(boltAxis,
                        conductorDiameter * 0.4, // 螺栓头对边距离的1/2
                        frameThickness * 1.2     // 螺栓长度略大于框架厚度
        );

    builder.Add(result, bolt);
  }

  builder.Add(result, centerFrame);

  return result;
}

/**
 * @brief 创建悬垂线夹（U型夹）
 * @param width 线夹宽度
 * @param height 线夹高度
 * @param radius 导线槽半径
 * @param position 线夹位置
 * @param direction 开口方向
 * @return TopoDS_Shape 生成的线夹形状
 */
TopoDS_Shape create_suspension_u_clamp(double width, double height,
                                       double radius, const gp_Pnt &position,
                                       const gp_Dir &direction) {

  // 创建U型线夹主体
  gp_Ax2 axis(position, direction);
  TopoDS_Shape uShape = BRepPrimAPI_MakeCylinder(axis, radius, height).Shape();

  // 创建顶部压板
  gp_Pnt topPlatePos = position.Translated(gp_Vec(direction) * height / 2);
  TopoDS_Shape plate =
      BRepPrimAPI_MakeBox(topPlatePos, width, width / 4, height / 5).Shape();

  // 合并部件
  BRepAlgoAPI_Fuse fuser(uShape, plate);
  return fuser.Shape();
}

/**
 * @brief 创建耐张线夹
 * @param width 线夹宽度
 * @param height 线夹高度
 * @param grooveRadius 导线槽半径
 * @param position 安装位置
 * @param direction 开口方向
 * @return TopoDS_Shape 生成的线夹形状
 */
TopoDS_Shape create_tension_u_clamp(double width, double height,
                                    double grooveRadius, const gp_Pnt &position,
                                    const gp_Dir &direction) {
  // 参数验证
  if (width <= 0 || height <= 0 || grooveRadius <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }

  // 创建U型主体
  gp_Ax2 axis(position, direction);
  TopoDS_Shape uBody =
      BRepPrimAPI_MakeCylinder(axis, grooveRadius, height).Shape();

  // 创建压板
  gp_Pnt plateCenter = position.Translated(gp_Vec(direction) * height * 0.4);
  TopoDS_Shape pressurePlate =
      BRepPrimAPI_MakeBox(plateCenter, width, width * 0.3, height * 0.2)
          .Shape();

  // 创建防滑齿
  TopoDS_Compound teeth;
  BRep_Builder teethBuilder;
  teethBuilder.MakeCompound(teeth);

  int teethCount = 6;
  for (int i = 0; i < teethCount; i++) {
    double angle = 2 * M_PI * i / teethCount;
    gp_Pnt toothPos =
        position.Translated(gp_Vec(direction) * grooveRadius * 0.8);
    toothPos.Rotate(gp_Ax1(position, direction), angle);

    TopoDS_Shape tooth =
        BRepPrimAPI_MakeCone(gp_Ax2(toothPos, direction), grooveRadius * 0.1, 0,
                             grooveRadius * 0.3)
            .Shape();
    teethBuilder.Add(teeth, tooth);
  }

  // 合并所有部件
  BRepAlgoAPI_Fuse fuser(uBody, pressurePlate);
  fuser = BRepAlgoAPI_Fuse(fuser.Shape(), teeth);

  if (!fuser.IsDone()) {
    throw Standard_ConstructionError("耐张线夹构造失败");
  }

  return fuser.Shape();
}

// 创建三分裂悬垂线夹
TopoDS_Shape create_triple_suspension_clamp(const insulator_params &params) {
  // 参数验证
  if (params.splitDistance <= 0) {
    throw Standard_ConstructionError("分裂间距必须为正数");
  }

  // 根据GB/T 2317.4计算导线直径 (三分裂取0.2倍分裂间距)
  double conductorDiameter = params.splitDistance * 0.2;
  double clampWidth = conductorDiameter * 3.0;  // 3倍导线直径
  double clampHeight = conductorDiameter * 2.5; // 2.5倍导线直径

  // 计算三角形顶点位置（120°均匀分布）
  std::vector<gp_Pnt> positions;
  double angleOffset =
      (params.subType == 1) ? M_PI / 2 : -M_PI / 6; // 调整起始角度

  for (int i = 0; i < 3; i++) {
    double angle = angleOffset + 2 * M_PI * i / 3;
    positions.emplace_back(params.splitDistance * cos(angle),
                           params.splitDistance * sin(angle),
                           conductorDiameter * 0.2); // 轻微Z轴偏移增加真实感
  }

  // 创建复合体
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  // 添加三个导线槽（带防滑纹）
  for (const auto &pos : positions) {
    TopoDS_Shape clamp = create_suspension_u_clamp(
        clampWidth, clampHeight,
        conductorDiameter * 0.55,          // 槽口略大于导线半径
        pos, gp_Dir(-pos.X(), -pos.Y(), 0) // 槽口朝向中心
    );
    builder.Add(result, clamp);
  }

  // 优化中心连接结构 - 三叉支架
  TopoDS_Shape starConnector =
      create_star_connector(gp_Pnt(0, 0, conductorDiameter * 0.3), // 中心点上移
                            3,                                     // 3个臂
                            conductorDiameter * 1.8,               // 臂长度缩短
                            conductorDiameter * 0.6,               // 臂宽度增加
                            conductorDiameter * 0.4                // 厚度增加
      );

  // 添加防松螺栓（每个臂一个）
  for (int i = 0; i < 3; i++) {
    double angle = angleOffset + 2 * M_PI * i / 3;
    gp_Pnt boltPos(conductorDiameter * 0.9 * cos(angle),
                   conductorDiameter * 0.9 * sin(angle),
                   conductorDiameter * 0.5);
    TopoDS_Shape bolt =
        create_hex_bolt(gp_Ax2(boltPos, gp_Dir(0, 0, 1)),
                        conductorDiameter * 0.3, conductorDiameter * 0.8);
    builder.Add(result, bolt);
  }

  builder.Add(result, starConnector);
  return result;
}

// 创建三分裂耐张线夹
TopoDS_Shape create_triple_tension_clamp(const insulator_params &params) {
  // 参数验证
  if (params.splitDistance <= 0) {
    throw Standard_ConstructionError("分裂间距必须为正数");
  }

  // 根据GB/T 2317.4计算导线直径 (三分裂取0.2倍分裂间距)
  double conductorDiameter = params.splitDistance * 0.2;
  double clampWidth = conductorDiameter * 3.0;     // 3倍导线直径
  double clampHeight = conductorDiameter * 2.5;    // 2.5倍导线直径
  double plateThickness = conductorDiameter * 0.8; // 连接板厚度

  // 计算三角形顶点位置（120°均匀分布）
  std::vector<gp_Pnt> positions;
  double angleOffset =
      (params.subType == 1) ? M_PI / 2 : -M_PI / 6; // 调整起始角度

  for (int i = 0; i < 3; i++) {
    double angle = angleOffset + 2 * M_PI * i / 3;
    positions.emplace_back(params.splitDistance * cos(angle),
                           params.splitDistance * sin(angle),
                           conductorDiameter * 0.2); // 轻微Z轴偏移增加真实感
  }

  // 创建复合体
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  // 添加三个耐张线夹单元（带防滑齿）
  for (const auto &pos : positions) {
    TopoDS_Shape clamp = create_tension_u_clamp(
        clampWidth, clampHeight,
        conductorDiameter * 0.55,          // 槽口略大于导线半径
        pos, gp_Dir(-pos.X(), -pos.Y(), 0) // 槽口朝向中心
    );
    builder.Add(result, clamp);
  }

  // 优化中心连接结构 - 三角连接板
  TopoDS_Shape triPlate = create_triangular_plate(
      positions[0], positions[1], positions[2], plateThickness,
      conductorDiameter * 0.3 // 边缘倒角半径
  );

  // 添加紧固螺栓（每个角一个）
  for (int i = 0; i < 3; i++) {
    gp_Pnt boltPos = positions[i].Scaled(gp_Pnt(), 0.7); // 向中心缩进30%
    boltPos.SetZ(plateThickness / 2);                    // 螺栓位于连接板中间

    TopoDS_Shape bolt = create_hex_bolt(gp_Ax2(boltPos, gp_Dir(0, 0, 1)),
                                        conductorDiameter * 0.3, // 螺栓直径
                                        plateThickness * 1.5     // 螺栓长度
    );
    builder.Add(result, bolt);
  }

  builder.Add(result, triPlate);
  return result;
}

/**
 * @brief 创建六边形连接板
 * @param positions 六个顶点位置(按顺时针或逆时针顺序)
 * @param thickness 板厚度
 * @param filletRadius 边缘倒角半径(默认0)
 * @return TopoDS_Shape 生成的六边形板
 */
TopoDS_Shape create_hexagonal_plate(const std::vector<gp_Pnt> &positions,
                                    double thickness, double filletRadius = 0) {
  // 参数验证
  if (positions.size() != 6) {
    throw Standard_ConstructionError("需要6个顶点位置");
  }
  if (thickness <= 0) {
    throw Standard_ConstructionError("板厚度必须为正数");
  }
  if (filletRadius < 0) {
    throw Standard_ConstructionError("倒角半径不能为负数");
  }

  // 创建六边形轮廓
  BRepBuilderAPI_MakeWire hexWire;
  for (int i = 0; i < 6; i++) {
    hexWire.Add(
        BRepBuilderAPI_MakeEdge(positions[i], positions[(i + 1) % 6]).Edge());
  }

  // 创建六边形面
  TopoDS_Face hexFace = BRepBuilderAPI_MakeFace(hexWire.Wire()).Face();

  // 计算拉伸方向(取前三个点的法向量)
  gp_Vec v1(positions[1].X() - positions[0].X(),
            positions[1].Y() - positions[0].Y(),
            positions[1].Z() - positions[0].Z());
  gp_Vec v2(positions[2].X() - positions[1].X(),
            positions[2].Y() - positions[1].Y(),
            positions[2].Z() - positions[1].Z());
  gp_Vec extrudeDir = v1.Crossed(v2);
  extrudeDir.Normalize();
  extrudeDir *= thickness;

  // 拉伸成体
  TopoDS_Shape plate = BRepPrimAPI_MakePrism(hexFace, extrudeDir).Shape();

  // 添加倒角(如果半径>0)
  if (filletRadius > 0) {
    BRepFilletAPI_MakeFillet fillet(plate);
    TopExp_Explorer explorer(plate, TopAbs_EDGE);
    while (explorer.More()) {
      fillet.Add(filletRadius, TopoDS::Edge(explorer.Current()));
      explorer.Next();
    }
    if (fillet.IsDone()) {
      plate = fillet.Shape();
    }
  }

  return plate;
}

TopoDS_Shape create_hex_tension_clamp(const insulator_params &params) {
  // 参数验证
  if (params.splitDistance <= 0) {
    throw Standard_ConstructionError("分裂间距必须为正数");
  }

  // 根据GB/T 2317.4计算导线直径 (六分裂取0.18倍分裂间距)
  double conductorDiameter = params.splitDistance * 0.18;
  double clampWidth = conductorDiameter * 3.2;     // 3.2倍导线直径
  double clampHeight = conductorDiameter * 2.8;    // 2.8倍导线直径
  double plateThickness = conductorDiameter * 0.6; // 连接板厚度

  // 生成六边形排列位置
  std::vector<gp_Pnt> positions;
  for (int i = 0; i < 6; i++) {
    double angle = 2 * M_PI * i / 6;
    positions.emplace_back(params.splitDistance * cos(angle),
                           params.splitDistance * sin(angle),
                           conductorDiameter * 0.15); // 轻微Z轴偏移增加真实感
  }

  // 创建复合体
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  // 添加六个耐张线夹单元
  for (int i = 0; i < 6; i++) {
    gp_Dir radialDir(positions[i].X(), positions[i].Y(), 0); // 径向方向
    TopoDS_Shape clamp =
        create_tension_u_clamp(clampWidth, clampHeight,
                               conductorDiameter * 0.52, // 槽口略大于导线半径
                               positions[i],
                               radialDir.Reversed() // 槽口朝向中心
        );
    builder.Add(result, clamp);
  }

  // 添加中心连接结构 - 六边形连接板
  TopoDS_Shape hexPlate =
      create_hexagonal_plate(positions, plateThickness,
                             conductorDiameter * 0.25 // 边缘倒角半径
      );

  // 添加紧固螺栓（每隔120度一个）
  for (int i = 0; i < 3; i++) {
    gp_Pnt boltPos = positions[i * 2].Scaled(gp_Pnt(), 0.75); // 向中心缩进25%
    boltPos.SetZ(plateThickness / 2); // 螺栓位于连接板中间

    TopoDS_Shape bolt = create_hex_bolt(gp_Ax2(boltPos, gp_Dir(0, 0, 1)),
                                        conductorDiameter * 0.28, // 螺栓直径
                                        plateThickness * 1.8      // 螺栓长度
    );
    builder.Add(result, bolt);
  }

  builder.Add(result, hexPlate);
  return result;
}

/**
 * @brief 创建八分裂悬垂线夹
 * @param params 绝缘子参数结构体
 * @return TopoDS_Shape 生成的线夹形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_octo_suspension_clamp(const insulator_params &params) {
  // 参数验证
  if (params.splitDistance <= 0) {
    throw Standard_ConstructionError("分裂间距必须为正数");
  }

  // 根据GB/T 2317.4计算导线直径 (八分裂取0.16倍分裂间距)
  double conductorDiameter = params.splitDistance * 0.16;
  double bodyRadius = params.splitDistance * 1.1; // 主体半径
  double bodyHeight = conductorDiameter * 2.8;    // 主体高度
  double grooveDepth = conductorDiameter * 0.6;   // 槽深
  double topHeight = conductorDiameter * 0.8;     // 顶部连接高度

  // 创建主体圆柱
  gp_Ax2 bodyAxis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  TopoDS_Shape body =
      BRepPrimAPI_MakeCylinder(bodyAxis, bodyRadius, bodyHeight).Shape();

  // 创建8个导线槽（带防滑齿）
  double angleStep = 2 * M_PI / 8;
  for (int i = 0; i < 8; i++) {
    double angle = angleStep * i;
    double x = params.splitDistance * cos(angle);
    double y = params.splitDistance * sin(angle);

    // 主槽体
    gp_Ax2 grooveAxis(gp_Pnt(x, y, bodyHeight - grooveDepth), gp_Dir(0, 0, 1));
    TopoDS_Shape groove =
        BRepPrimAPI_MakeCylinder(grooveAxis,
                                 conductorDiameter *
                                     0.55, // 槽口半径（含1mm安装间隙）
                                 grooveDepth)
            .Shape();

    // 防滑齿（3个/槽）
    for (int j = 0; j < 3; j++) {
      double toothAngle = angle + (j - 1) * 0.1; // 小角度偏移
      double toothX = x + conductorDiameter * 0.4 * cos(toothAngle);
      double toothY = y + conductorDiameter * 0.4 * sin(toothAngle);

      TopoDS_Shape tooth =
          BRepPrimAPI_MakeCone(
              gp_Ax2(gp_Pnt(toothX, toothY, bodyHeight - grooveDepth * 0.7),
                     gp_Dir(0, 0, 1)),
              conductorDiameter * 0.08, // 齿顶直径
              0, grooveDepth * 0.6)
              .Shape();

      groove = BRepAlgoAPI_Fuse(groove, tooth).Shape();
    }

    // 从主体中减去导线槽
    body = BRepAlgoAPI_Cut(body, groove).Shape();
  }

  // 顶部连接结构（带倒角）
  gp_Ax2 topAxis(gp_Pnt(0, 0, bodyHeight), gp_Dir(0, 0, 1));
  TopoDS_Shape topConnector =
      BRepPrimAPI_MakeCylinder(topAxis,
                               bodyRadius * 0.4, // 顶部连接直径
                               topHeight)
          .Shape();

  // 顶部倒角处理
  BRepFilletAPI_MakeFillet fillet(topConnector);
  TopExp_Explorer explorer(topConnector, TopAbs_EDGE);
  while (explorer.More()) {
    fillet.Add(conductorDiameter * 0.15, TopoDS::Edge(explorer.Current()));
    explorer.Next();
  }
  topConnector = fillet.Shape();

  // 合并主体和顶部连接
  TopoDS_Shape result = BRepAlgoAPI_Fuse(body, topConnector).Shape();

  // 整体倒角处理（边缘圆滑）
  BRepFilletAPI_MakeFillet finalFillet(result);
  explorer.Init(result, TopAbs_EDGE);
  while (explorer.More()) {
    TopoDS_Edge edge = TopoDS::Edge(explorer.Current());
    if (BRep_Tool::Degenerated(edge)) {
      explorer.Next();
      continue;
    }
    finalFillet.Add(conductorDiameter * 0.1, edge);
    explorer.Next();
  }
  result = finalFillet.Shape();

  return result;
}

/**
 * @brief 创建八分裂耐张线夹
 * @param params 绝缘子参数结构体
 * @return TopoDS_Shape 生成的线夹形状
 * @throws Standard_ConstructionError 如果参数不合法
 */
TopoDS_Shape create_octo_tension_clamp(const insulator_params &params) {
  // 参数验证
  if (params.splitDistance <= 0) {
    throw Standard_ConstructionError("分裂间距必须为正数");
  }

  // 根据GB/T 2317.4计算导线直径 (八分裂取0.16倍分裂间距)
  double conductorDiameter = params.splitDistance * 0.16;
  double bodyWidth = params.splitDistance * 2.1; // 主体宽度
  double bodyHeight = conductorDiameter * 2.8;   // 主体高度
  double ribWidth = conductorDiameter * 0.8;     // 加强筋宽度

  // 创建主体（带圆角的长方体）
  BRepPrimAPI_MakeBox bodyMaker(
      gp_Pnt(-bodyWidth / 2, -bodyWidth / 2, 0),
      gp_Pnt(bodyWidth / 2, bodyWidth / 2, bodyHeight));
  TopoDS_Shape body = bodyMaker.Shape();

  // 主体圆角处理
  BRepFilletAPI_MakeFillet fillet(body);
  TopExp_Explorer explorer(body, TopAbs_EDGE);
  while (explorer.More()) {
    TopoDS_Edge edge = TopoDS::Edge(explorer.Current());
    if (!BRep_Tool::Degenerated(edge)) {
      fillet.Add(conductorDiameter * 0.2, edge); // 0.2d圆角
    }
    explorer.Next();
  }
  body = fillet.Shape();

  // 创建8个导线槽（带防滑齿）
  double angleStep = 2 * M_PI / 8;
  for (int i = 0; i < 8; i++) {
    double angle = angleStep * i;
    double x = params.splitDistance * cos(angle);
    double y = params.splitDistance * sin(angle);

    // 主槽体（带1.2mm安装间隙）
    gp_Ax2 grooveAxis(gp_Pnt(x, y, bodyHeight / 2), gp_Dir(0, 0, 1));
    TopoDS_Shape groove =
        BRepPrimAPI_MakeCylinder(grooveAxis,
                                 conductorDiameter * 0.6, // 槽口半径
                                 bodyHeight)
            .Shape();

    // 防滑齿（3个/槽）
    for (int j = 0; j < 3; j++) {
      double toothAngle = angle + (j - 1) * 0.15; // 小角度偏移
      double toothX = x + conductorDiameter * 0.35 * cos(toothAngle);
      double toothY = y + conductorDiameter * 0.35 * sin(toothAngle);

      TopoDS_Shape tooth =
          BRepPrimAPI_MakeCone(
              gp_Ax2(gp_Pnt(toothX, toothY, bodyHeight * 0.6), gp_Dir(0, 0, 1)),
              conductorDiameter * 0.1, // 齿顶直径
              0, bodyHeight * 0.4)
              .Shape();

      groove = BRepAlgoAPI_Fuse(groove, tooth).Shape();
    }

    // 从主体中减去导线槽
    body = BRepAlgoAPI_Cut(body, groove).Shape();
  }

  // 添加十字加强筋（优化为流线型）
  for (int i = 0; i < 4; i++) {
    double angle = i * M_PI / 2;
    gp_Pnt p1(bodyWidth / 2 * cos(angle), bodyWidth / 2 * sin(angle), 0);
    gp_Pnt p2(bodyWidth / 2 * cos(angle), bodyWidth / 2 * sin(angle),
              bodyHeight);

    // 创建流线型加强筋（梯形截面）
    BRepOffsetAPI_ThruSections ribMaker(true);

    // 底部截面（较大）
    gp_Circ baseCircle(gp_Ax2(p1, gp_Dir(cos(angle), sin(angle), 0)), ribWidth);
    ribMaker.AddWire(
        BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(baseCircle).Edge())
            .Wire());

    // 顶部截面（较小）
    gp_Circ topCircle(gp_Ax2(p2, gp_Dir(cos(angle), sin(angle), 0)),
                      ribWidth * 0.7);
    ribMaker.AddWire(
        BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(topCircle).Edge())
            .Wire());

    TopoDS_Shape rib = ribMaker.Shape();
    body = BRepAlgoAPI_Fuse(body, rib).Shape();
  }

  // 顶部连接结构（带螺栓）
  gp_Ax2 topAxis(gp_Pnt(0, 0, bodyHeight), gp_Dir(0, 0, 1));
  TopoDS_Shape topConnector =
      BRepPrimAPI_MakeCylinder(topAxis,
                               conductorDiameter * 1.5, // 连接柱直径
                               conductorDiameter * 0.8)
          .Shape();

  // 合并主体和顶部连接
  TopoDS_Shape result = BRepAlgoAPI_Fuse(body, topConnector).Shape();

  // 添加4个六角螺栓（十字对称）
  for (int i = 0; i < 4; i++) {
    double angle = i * M_PI / 2;
    double boltX = conductorDiameter * 0.8 * cos(angle);
    double boltY = conductorDiameter * 0.8 * sin(angle);

    // 创建螺栓（六边形近似）
    gp_Ax2 boltAxis(gp_Pnt(boltX, boltY, bodyHeight + conductorDiameter * 0.4),
                    gp_Dir(0, 0, 1));
    TopoDS_Shape bolt = create_hex_bolt(boltAxis,
                                        conductorDiameter * 0.15, // 螺栓直径
                                        conductorDiameter * 1.2   // 螺栓长度
    );

    result = BRepAlgoAPI_Fuse(result, bolt).Shape();
  }

  return result;
}

// 单分裂均压环
TopoDS_Shape create_single_grading_ring(const insulator_params &params) {
  // 参数检查
  if (params.gradingRing.count <= 0 || params.gradingRing.radius <= 0 ||
      params.gradingRing.height <= 0) {
    throw Standard_ConstructionError("均压环参数必须为正数");
  }

  // 创建主环
  gp_Ax2 axis(gp_Pnt(0, 0, params.gradingRing.position), gp_Dir(0, 0, 1));
  TopoDS_Shape mainRing = BRepPrimAPI_MakeTorus(axis, params.gradingRing.radius,
                                                params.gradingRing.height)
                              .Shape();

  // 创建法兰环
  double flangeRadius = params.gradingRing.radius * 1.5;
  double flangeHeight = params.gradingRing.height * 2;
  gp_Ax2 flangeAxis(gp_Pnt(0, 0, params.gradingRing.position), gp_Dir(0, 0, 1));
  TopoDS_Shape flange =
      BRepPrimAPI_MakeCylinder(flangeAxis, flangeRadius, flangeHeight).Shape();

  // 创建复合体
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  // 添加主环和法兰环
  builder.Add(result, mainRing);
  builder.Add(result, flange);

  // 创建4个径向加强筋
  for (int i = 0; i < 4; i++) {
    double angle = i * M_PI / 2;
    gp_Pnt start(params.gradingRing.radius * cos(angle),
                 params.gradingRing.radius * sin(angle),
                 params.gradingRing.position);
    gp_Pnt end((params.gradingRing.radius + params.gradingRing.height / 2) *
                   cos(angle),
               (params.gradingRing.radius + params.gradingRing.height / 2) *
                   sin(angle),
               params.gradingRing.position);

    TopoDS_Shape rib = create_rectangular_beam(
        params.gradingRing.height / 4, params.gradingRing.height / 4,
        start.Distance(end),
        gp_Pnt((start.X() + end.X()) / 2, (start.Y() + end.Y()) / 2,
               params.gradingRing.position));

    builder.Add(result, rib);
  }
  return result;
}

// 双分裂均压环
TopoDS_Shape create_double_grading_ring(const insulator_params &params) {
  // 参数检查
  if (params.gradingRing.count <= 0 || params.gradingRing.radius <= 0 ||
      params.gradingRing.height <= 0) {
    throw Standard_ConstructionError("均压环参数必须为正数");
  }

  // 创建复合体
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  // 根据subType判断排列方式
  bool isVertical = params.subType == 1;

  // 垂直排列
  if (isVertical) {
    gp_Ax2 axis1(
        gp_Pnt(0, params.splitDistance / 2, params.gradingRing.position),
        gp_Dir(0, 0, 1));
    TopoDS_Shape ring1 = BRepPrimAPI_MakeTorus(axis1, params.gradingRing.radius,
                                               params.gradingRing.height)
                             .Shape();
    builder.Add(result, ring1);

    gp_Ax2 axis2(
        gp_Pnt(0, -params.splitDistance / 2, params.gradingRing.position),
        gp_Dir(0, 0, 1));
    TopoDS_Shape ring2 = BRepPrimAPI_MakeTorus(axis2, params.gradingRing.radius,
                                               params.gradingRing.height)
                             .Shape();
    builder.Add(result, ring2);

    // 添加法兰连接部分
    double flangeHeight = params.gradingRing.height * 1.5;
    double flangeRadius = params.gradingRing.radius * 1.2;

    // 上环法兰
    gp_Ax2 flangeAxis1(
        gp_Pnt(0, params.splitDistance / 2, params.gradingRing.position),
        gp_Dir(0, 0, 1));
    TopoDS_Shape flange1 =
        BRepPrimAPI_MakeCylinder(flangeAxis1, flangeRadius, flangeHeight)
            .Shape();
    builder.Add(result, flange1);

    // 下环法兰
    gp_Ax2 flangeAxis2(
        gp_Pnt(0, -params.splitDistance / 2, params.gradingRing.position),
        gp_Dir(0, 0, 1));
    TopoDS_Shape flange2 =
        BRepPrimAPI_MakeCylinder(flangeAxis2, flangeRadius, flangeHeight)
            .Shape();
    builder.Add(result, flange2);

    // 添加连接两个环的加强筋
    TopoDS_Shape connector = create_rectangular_beam(
        params.gradingRing.height / 3, params.gradingRing.height / 3,
        params.splitDistance, gp_Pnt(0, 0, params.gradingRing.position));
    builder.Add(result, connector);
  }
  // 水平排列
  else {
    gp_Ax2 axis1(
        gp_Pnt(params.splitDistance / 2, 0, params.gradingRing.position),
        gp_Dir(0, 0, 1));
    TopoDS_Shape ring1 = BRepPrimAPI_MakeTorus(axis1, params.gradingRing.radius,
                                               params.gradingRing.height)
                             .Shape();
    builder.Add(result, ring1);

    gp_Ax2 axis2(
        gp_Pnt(-params.splitDistance / 2, 0, params.gradingRing.position),
        gp_Dir(0, 0, 1));
    TopoDS_Shape ring2 = BRepPrimAPI_MakeTorus(axis2, params.gradingRing.radius,
                                               params.gradingRing.height)
                             .Shape();
    builder.Add(result, ring2);

    // 添加法兰连接部分
    double flangeHeight = params.gradingRing.height * 1.5;
    double flangeRadius = params.gradingRing.radius * 1.2;

    // 右环法兰
    gp_Ax2 flangeAxis1(
        gp_Pnt(params.splitDistance / 2, 0, params.gradingRing.position),
        gp_Dir(0, 0, 1));
    TopoDS_Shape flange1 =
        BRepPrimAPI_MakeCylinder(flangeAxis1, flangeRadius, flangeHeight)
            .Shape();
    builder.Add(result, flange1);

    // 左环法兰
    gp_Ax2 flangeAxis2(
        gp_Pnt(-params.splitDistance / 2, 0, params.gradingRing.position),
        gp_Dir(0, 0, 1));
    TopoDS_Shape flange2 =
        BRepPrimAPI_MakeCylinder(flangeAxis2, flangeRadius, flangeHeight)
            .Shape();
    builder.Add(result, flange2);

    // 添加连接两个环的加强筋
    TopoDS_Shape connector = create_rectangular_beam(
        params.gradingRing.height / 3, params.gradingRing.height / 3,
        params.splitDistance, gp_Pnt(0, 0, params.gradingRing.position));
    builder.Add(result, connector);
  }

  // 为每个环添加径向加强筋
  for (int i = 0; i < 2; i++) {
    double xOffset = isVertical ? 0
                                : (i == 0 ? params.splitDistance / 2
                                          : -params.splitDistance / 2);
    double yOffset = isVertical ? (i == 0 ? params.splitDistance / 2
                                          : -params.splitDistance / 2)
                                : 0;

    for (int j = 0; j < 4; j++) {
      double angle = j * M_PI / 2;
      gp_Pnt start(xOffset + params.gradingRing.radius * cos(angle),
                   yOffset + params.gradingRing.radius * sin(angle),
                   params.gradingRing.position);
      gp_Pnt end(xOffset + (params.gradingRing.radius +
                            params.gradingRing.height / 2) *
                               cos(angle),
                 yOffset + (params.gradingRing.radius +
                            params.gradingRing.height / 2) *
                               sin(angle),
                 params.gradingRing.position);

      TopoDS_Shape rib = create_rectangular_beam(
          params.gradingRing.height / 4, params.gradingRing.height / 4,
          start.Distance(end),
          gp_Pnt((start.X() + end.X()) / 2, (start.Y() + end.Y()) / 2,
                 params.gradingRing.position));

      builder.Add(result, rib);
    }
  }

  return result;
}

// 三分裂均压环
TopoDS_Shape create_triple_grading_ring(const insulator_params &params) {
  // 参数验证
  if (params.splitDistance <= 0) {
    throw Standard_ConstructionError("分裂间距必须为正数");
  }
  if (params.gradingRing.radius <= 0 || params.gradingRing.height <= 0) {
    throw Standard_ConstructionError("均压环尺寸参数必须为正数");
  }

  // 创建复合体
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  std::vector<gp_Pnt> ringCenters;
  double flangeRadius = params.gradingRing.radius * 1.5;
  double flangeHeight = params.gradingRing.height * 2;

  int subType = params.subType;

  // 正三角排列
  if (subType == 1) {
    double angle = 2 * M_PI / 3;
    for (int i = 0; i < 3; i++) {
      double x = params.splitDistance * cos(i * angle);
      double y = params.splitDistance * sin(i * angle);
      gp_Pnt center(x, y, params.gradingRing.position);
      ringCenters.push_back(center);

      // 添加均压环
      gp_Ax2 axis(center, gp_Dir(0, 0, 1));
      builder.Add(result, BRepPrimAPI_MakeTorus(axis, params.gradingRing.radius,
                                                params.gradingRing.height)
                              .Shape());

      // 添加法兰环
      gp_Ax2 flangeAxis(center, gp_Dir(0, 0, 1));
      builder.Add(result, BRepPrimAPI_MakeCylinder(flangeAxis, flangeRadius,
                                                   flangeHeight)
                              .Shape());
    }

    // 添加三角形加强筋
    for (int i = 0; i < 3; i++) {
      gp_Pnt start = ringCenters[i];
      gp_Pnt end = ringCenters[(i + 1) % 3];

      TopoDS_Shape rib = create_rectangular_beam(
          params.gradingRing.height / 3, params.gradingRing.height / 3,
          start.Distance(end),
          gp_Pnt((start.X() + end.X()) / 2, (start.Y() + end.Y()) / 2,
                 params.gradingRing.position));

      builder.Add(result, rib);
    }
  }
  // 倒三角排列
  else if (subType == 2) {
    double angle = 2 * M_PI / 3;
    for (int i = 0; i < 3; i++) {
      double x = params.splitDistance * cos(i * angle + M_PI / 3);
      double y = params.splitDistance * sin(i * angle + M_PI / 3);
      gp_Pnt center(x, y, params.gradingRing.position);
      ringCenters.push_back(center);

      // 添加均压环
      gp_Ax2 axis(center, gp_Dir(0, 0, 1));
      builder.Add(result, BRepPrimAPI_MakeTorus(axis, params.gradingRing.radius,
                                                params.gradingRing.height)
                              .Shape());

      // 添加法兰环
      gp_Ax2 flangeAxis(center, gp_Dir(0, 0, 1));
      builder.Add(result, BRepPrimAPI_MakeCylinder(flangeAxis, flangeRadius,
                                                   flangeHeight)
                              .Shape());
    }

    // 添加三角形加强筋
    for (int i = 0; i < 3; i++) {
      gp_Pnt start = ringCenters[i];
      gp_Pnt end = ringCenters[(i + 1) % 3];

      TopoDS_Shape rib = create_rectangular_beam(
          params.gradingRing.height / 3, params.gradingRing.height / 3,
          start.Distance(end),
          gp_Pnt((start.X() + end.X()) / 2, (start.Y() + end.Y()) / 2,
                 params.gradingRing.position));

      builder.Add(result, rib);
    }
  }
  // 直线排列
  else {
    // 上环
    gp_Pnt center1(0, params.splitDistance, params.gradingRing.position);
    gp_Ax2 axis1(center1, gp_Dir(0, 0, 1));
    builder.Add(result, BRepPrimAPI_MakeTorus(axis1, params.gradingRing.radius,
                                              params.gradingRing.height)
                            .Shape());
    // 上环法兰
    builder.Add(
        result,
        BRepPrimAPI_MakeCylinder(axis1, flangeRadius, flangeHeight).Shape());

    // 中环
    gp_Pnt center2(0, 0, params.gradingRing.position);
    gp_Ax2 axis2(center2, gp_Dir(0, 0, 1));
    builder.Add(result, BRepPrimAPI_MakeTorus(axis2, params.gradingRing.radius,
                                              params.gradingRing.height)
                            .Shape());
    // 中环法兰
    builder.Add(
        result,
        BRepPrimAPI_MakeCylinder(axis2, flangeRadius, flangeHeight).Shape());

    // 下环
    gp_Pnt center3(0, -params.splitDistance, params.gradingRing.position);
    gp_Ax2 axis3(center3, gp_Dir(0, 0, 1));
    builder.Add(result, BRepPrimAPI_MakeTorus(axis3, params.gradingRing.radius,
                                              params.gradingRing.height)
                            .Shape());
    // 下环法兰
    builder.Add(
        result,
        BRepPrimAPI_MakeCylinder(axis3, flangeRadius, flangeHeight).Shape());

    // 添加垂直加强筋
    TopoDS_Shape rib1 = create_rectangular_beam(
        params.gradingRing.height / 3, params.gradingRing.height / 3,
        center1.Distance(center2),
        gp_Pnt(0, params.splitDistance / 2, params.gradingRing.position));

    TopoDS_Shape rib2 = create_rectangular_beam(
        params.gradingRing.height / 3, params.gradingRing.height / 3,
        center2.Distance(center3),
        gp_Pnt(0, -params.splitDistance / 2, params.gradingRing.position));

    builder.Add(result, rib1);
    builder.Add(result, rib2);
  }

  return result;
}

// 四分裂均压环
TopoDS_Shape create_quad_grading_ring(const insulator_params &params) {
  // 参数验证
  if (params.splitDistance <= 0) {
    throw Standard_ConstructionError("分裂间距必须为正数");
  }
  if (params.gradingRing.radius <= 0 || params.gradingRing.height <= 0) {
    throw Standard_ConstructionError("均压环尺寸参数必须为正数");
  }

  // 创建复合体
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  double offset = params.splitDistance / sqrt(2);
  double flangeRadius = params.gradingRing.radius * 1.5;
  double flangeHeight = params.gradingRing.height * 2;

  // 四个环正方形排列
  std::vector<gp_Pnt> ringCenters = {
      gp_Pnt(offset, offset, params.gradingRing.position),
      gp_Pnt(offset, -offset, params.gradingRing.position),
      gp_Pnt(-offset, offset, params.gradingRing.position),
      gp_Pnt(-offset, -offset, params.gradingRing.position)};

  // 添加四个均压环和法兰环
  for (const auto &center : ringCenters) {
    gp_Ax2 axis(center, gp_Dir(0, 0, 1));

    // 添加均压环
    builder.Add(result, BRepPrimAPI_MakeTorus(axis, params.gradingRing.radius,
                                              params.gradingRing.height)
                            .Shape());

    // 添加法兰环
    builder.Add(
        result,
        BRepPrimAPI_MakeCylinder(axis, flangeRadius, flangeHeight).Shape());
  }

  // 添加X方向加强筋
  TopoDS_Shape xConnector = create_rectangular_beam(
      params.gradingRing.height / 3, params.gradingRing.height / 3,
      params.splitDistance * 2, gp_Pnt(0, 0, params.gradingRing.position));
  builder.Add(result, xConnector);

  // 添加Y方向加强筋
  TopoDS_Shape yConnector = create_rectangular_beam(
      params.gradingRing.height / 3, params.gradingRing.height / 3,
      params.splitDistance * 2, gp_Pnt(0, 0, params.gradingRing.position));
  builder.Add(result, yConnector);

  // 为每个环添加径向加强筋
  for (const auto &center : ringCenters) {
    for (int i = 0; i < 4; i++) {
      double angle = i * M_PI / 2;
      gp_Pnt start(center.X() + params.gradingRing.radius * cos(angle),
                   center.Y() + params.gradingRing.radius * sin(angle),
                   params.gradingRing.position);
      gp_Pnt end(center.X() + (params.gradingRing.radius +
                               params.gradingRing.height / 2) *
                                  cos(angle),
                 center.Y() + (params.gradingRing.radius +
                               params.gradingRing.height / 2) *
                                  sin(angle),
                 params.gradingRing.position);

      TopoDS_Shape rib = create_rectangular_beam(
          params.gradingRing.height / 4, params.gradingRing.height / 4,
          start.Distance(end),
          gp_Pnt((start.X() + end.X()) / 2, (start.Y() + end.Y()) / 2,
                 params.gradingRing.position));

      builder.Add(result, rib);
    }
  }

  return result;
}

// 六分裂均压环
TopoDS_Shape create_hex_grading_ring(const insulator_params &params) {
  // 参数验证
  if (params.splitDistance <= 0) {
    throw Standard_ConstructionError("分裂间距必须为正数");
  }
  if (params.gradingRing.radius <= 0 || params.gradingRing.height <= 0) {
    throw Standard_ConstructionError("均压环尺寸参数必须为正数");
  }

  // 创建复合体
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  double angle = 2 * M_PI / 6;
  double flangeRadius = params.gradingRing.radius * 1.5;
  double flangeHeight = params.gradingRing.height * 2;

  // 圆形排列
  for (int i = 0; i < 6; i++) {
    double x = params.splitDistance * cos(i * angle);
    double y = params.splitDistance * sin(i * angle);
    gp_Pnt center(x, y, params.gradingRing.position);

    // 添加均压环
    gp_Ax2 axis(center, gp_Dir(0, 0, 1));
    builder.Add(result, BRepPrimAPI_MakeTorus(axis, params.gradingRing.radius,
                                              params.gradingRing.height)
                            .Shape());

    // 添加法兰环
    builder.Add(
        result,
        BRepPrimAPI_MakeCylinder(axis, flangeRadius, flangeHeight).Shape());
  }

  // 添加中心连接环
  gp_Ax2 centerAxis(gp_Pnt(0, 0, params.gradingRing.position), gp_Dir(0, 0, 1));
  TopoDS_Shape centerRing =
      BRepPrimAPI_MakeTorus(centerAxis, params.gradingRing.radius / 2,
                            params.gradingRing.height)
          .Shape();
  builder.Add(result, centerRing);

  // 添加径向加强筋
  for (int i = 0; i < 6; i++) {
    gp_Pnt start(0, 0, params.gradingRing.position);
    gp_Pnt end(params.splitDistance * cos(i * angle),
               params.splitDistance * sin(i * angle),
               params.gradingRing.position);

    TopoDS_Shape rib = create_rectangular_beam(
        params.gradingRing.height / 3, params.gradingRing.height / 3,
        start.Distance(end),
        gp_Pnt((start.X() + end.X()) / 2, (start.Y() + end.Y()) / 2,
               params.gradingRing.position));

    builder.Add(result, rib);
  }

  return result;
}

// 8分裂均压环
TopoDS_Shape create_octo_grading_ring(const insulator_params &params) {
  // 参数验证
  if (params.splitDistance <= 0) {
    throw Standard_ConstructionError("分裂间距必须为正数");
  }
  if (params.gradingRing.radius <= 0 || params.gradingRing.height <= 0) {
    throw Standard_ConstructionError("均压环尺寸参数必须为正数");
  }

  // 创建复合体
  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  double angle = 2 * M_PI / 8;
  double flangeRadius = params.gradingRing.radius * 1.5;
  double flangeHeight = params.gradingRing.height * 2;

  // 标准圆形排列
  for (int i = 0; i < 8; i++) {
    double x = params.splitDistance * cos(i * angle);
    double y = params.splitDistance * sin(i * angle);
    gp_Pnt center(x, y, params.gradingRing.position);

    // 添加均压环
    gp_Ax2 axis(center, gp_Dir(0, 0, 1));
    builder.Add(result, BRepPrimAPI_MakeTorus(axis, params.gradingRing.radius,
                                              params.gradingRing.height)
                            .Shape());

    // 添加法兰环
    builder.Add(
        result,
        BRepPrimAPI_MakeCylinder(axis, flangeRadius, flangeHeight).Shape());
  }

  // 添加中心连接环
  gp_Ax2 centerAxis(gp_Pnt(0, 0, params.gradingRing.position), gp_Dir(0, 0, 1));
  TopoDS_Shape centerRing =
      BRepPrimAPI_MakeTorus(centerAxis, params.gradingRing.radius / 2,
                            params.gradingRing.height)
          .Shape();
  builder.Add(result, centerRing);

  // 添加优化的径向加强筋
  for (int i = 0; i < 8; i++) {
    gp_Pnt start(0, 0, params.gradingRing.position);
    gp_Pnt end(params.splitDistance * cos(i * angle),
               params.splitDistance * sin(i * angle),
               params.gradingRing.position);

    // 加强筋尺寸根据均压环高度调整
    double ribWidth = params.gradingRing.height / 3;
    double ribHeight = params.gradingRing.height / 2;

    TopoDS_Shape rib = create_rectangular_beam(
        ribWidth, ribHeight, start.Distance(end),
        gp_Pnt((start.X() + end.X()) / 2, (start.Y() + end.Y()) / 2,
               params.gradingRing.position));

    builder.Add(result, rib);
  }

  // 添加环间连接加强筋（仅适用于标准圆形排列）
  for (int i = 0; i < 8; i++) {
    gp_Pnt p1(params.splitDistance * cos(i * angle),
              params.splitDistance * sin(i * angle),
              params.gradingRing.position);
    gp_Pnt p2(params.splitDistance * cos((i + 1) % 8 * angle),
              params.splitDistance * sin((i + 1) % 8 * angle),
              params.gradingRing.position);

    TopoDS_Shape connector = create_rectangular_beam(
        params.gradingRing.height / 4, params.gradingRing.height / 4,
        p1.Distance(p2),
        gp_Pnt((p1.X() + p2.X()) / 2, (p1.Y() + p2.Y()) / 2,
               params.gradingRing.position));

    builder.Add(result, connector);
  }

  return result;
}

TopoDS_Shape
create_top_positioned_clamp(const insulator_params &params, double totalHeight,
                            const gp_Pnt &position = gp_Pnt(0, 0, 0),
                            const gp_Dir &direction = gp_Dir(0, 0, 1)) {

  // 创建简化金具主体
  gp_Ax2 clampAxis(position, direction);
  TopoDS_Shape clamp;

  if (params.stringType == string_type::SUSPENSION) {
    // 悬垂串简化结构：单圆柱体
    clamp = BRepPrimAPI_MakeCylinder(clampAxis, 30.0, totalHeight).Shape();

  } else {
    // 耐张串简化结构：圆锥体+圆柱体
    TopoDS_Shape cone =
        BRepPrimAPI_MakeCone(clampAxis, 40.0, 20.0, totalHeight * 0.6).Shape();

    gp_Ax2 cylAxis(position.Translated(gp_Vec(0, 0, totalHeight * 0.6)),
                   direction);
    TopoDS_Shape cylinder =
        BRepPrimAPI_MakeCylinder(cylAxis, 20.0, totalHeight * 0.4).Shape();

    clamp = BRepAlgoAPI_Fuse(cone, cylinder).Shape();
  }

  return clamp;
}

/**
 * @brief 创建定位金具
 * @param params 绝缘子参数
 * @param position 金具定位点
 * @param direction 金具方向(默认Z轴向上)
 * @return TopoDS_Shape 金具形状
 */
TopoDS_Shape
create_bottom_positioned_clamp(const insulator_params &params,
                               const gp_Pnt &position = gp_Pnt(0, 0, 0),
                               const gp_Dir &direction = gp_Dir(0, 0, 1)) {
  TopoDS_Shape clamp;
  switch (params.stringType) {
  case string_type::SUSPENSION:
    switch (params.subNum) {
    case 1:
      clamp = create_single_suspension_clamp(params);
      break;
    case 2:
      clamp = create_double_suspension_clamp(params);
      break;
    case 3:
      clamp = create_triple_suspension_clamp(params);
      break;
    case 4:
      clamp = create_quad_suspension_clamp(params);
      break;
    case 6:
      clamp = create_hex_suspension_clamp(params);
      break;
    case 8:
      clamp = create_octo_suspension_clamp(params);
      break;
    }
    break;
  case string_type::TENSION:
    switch (params.subNum) {
    case 1:
      clamp = create_single_tension_clamp(params);
      break;
    case 2:
      clamp = create_double_tension_clamp(params);
      break;
    case 3:
      clamp = create_triple_tension_clamp(params);
      break;
    case 4:
      clamp = create_quad_tension_clamp(params);
      break;
    case 6:
      clamp = create_hex_tension_clamp(params);
      break;
    case 8:
      clamp = create_octo_tension_clamp(params);
      break;
    }
    break;
  default:
    throw Standard_ConstructionError("无效的串类型");
  }

  // 应用定位变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(position, direction);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  return BRepBuilderAPI_Transform(clamp, transformation).Shape();
}

/**
 * @brief 创建均压环
 * @param params 绝缘子参数结构体
 * @param position 均压环中心位置
 * @param direction 均压环方向（默认Z轴向上）
 * @return TopoDS_Shape 生成的均压环形状
 */
TopoDS_Shape create_grading_ring(const insulator_params &params,
                                 const gp_Pnt &position = gp_Pnt(0, 0, 0),
                                 const gp_Dir &direction = gp_Dir(0, 0, 1)) {
  TopoDS_Shape gradingRing;

  // 根据分裂数创建不同类型的均压环
  switch (params.subNum) {
  case 2:
    gradingRing = create_double_grading_ring(params);
    break;
  case 3:
    gradingRing = create_triple_grading_ring(params);
    break;
  case 4:
    gradingRing = create_quad_grading_ring(params);
    break;
  case 6:
    gradingRing = create_hex_grading_ring(params);
    break;
  case 8:
    gradingRing = create_octo_grading_ring(params);
    break;
  default:
    gradingRing = create_single_grading_ring(params); // 单分裂
  }

  // 应用定位变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Ax3 targetAx3(position, direction);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  return BRepBuilderAPI_Transform(gradingRing, transformation).Shape();
}

/**
 * @brief 创建U型串顶部连接板（上部三角形+下部矩形结构，带圆角过渡）
 * @param params 绝缘子参数
 * @param centerPos 中心位置
 * @param leftPos 左连接点
 * @param rightPos 右连接点
 * @param direction 安装方向
 * @return 连接板形状
 */
TopoDS_Shape create_u_top_connection_plate(const insulator_params &params,
                                           const gp_Pnt &centerPos,
                                           const gp_Pnt &leftPos,
                                           const gp_Pnt &rightPos,
                                           const gp_Dir &direction) {

  // 1. 基本参数设置（符合DL/T 759-2001标准）
  const double plateThickness = 12.0; // 板厚12mm
  const double filletRadius = 5.0;    // 圆角半径5mm
  const double triangleHeight = 50.0; // 三角形部分高度50mm
  const double rectHeight = 30.0;     // 矩形部分高度30mm

  // 2. 创建上部三角形部分（带圆角顶点）
  gp_Pnt topVertex(centerPos.X(), centerPos.Y(),
                   centerPos.Z() + triangleHeight);

  // 创建圆角顶点（将尖角改为圆弧）
  gp_Circ filletCircle(gp_Ax2(topVertex, direction), filletRadius);
  TopoDS_Edge filletEdge = BRepBuilderAPI_MakeEdge(filletCircle).Edge();

  // 获取圆弧顶点坐标
  TopoDS_Vertex circleVertex;
  TopExp::Vertices(filletEdge, circleVertex, circleVertex);
  gp_Pnt circlePoint = BRep_Tool::Pnt(circleVertex);

  // 创建连接到圆角顶点的边
  TopoDS_Edge leftEdge = BRepBuilderAPI_MakeEdge(leftPos, circlePoint).Edge();
  TopoDS_Edge rightEdge = BRepBuilderAPI_MakeEdge(circlePoint, rightPos).Edge();

  // 创建三角形剖面
  BRepBuilderAPI_MakeWire triangleWire;
  triangleWire.Add(leftEdge);
  triangleWire.Add(filletEdge);
  triangleWire.Add(rightEdge);
  triangleWire.Add(BRepBuilderAPI_MakeEdge(rightPos, leftPos).Edge());

  TopoDS_Face triangleFace = BRepBuilderAPI_MakeFace(triangleWire.Wire());
  TopoDS_Shape trianglePlate =
      BRepPrimAPI_MakePrism(triangleFace, gp_Vec(direction) * plateThickness)
          .Shape();

  // 3. 创建下部矩形部分
  gp_Pnt rectBottom1(leftPos.X(), leftPos.Y(), centerPos.Z() - rectHeight);
  gp_Pnt rectBottom2(rightPos.X(), rightPos.Y(), centerPos.Z() - rectHeight);

  BRepBuilderAPI_MakeWire rectWire;
  rectWire.Add(BRepBuilderAPI_MakeEdge(leftPos, rectBottom1).Edge());
  rectWire.Add(BRepBuilderAPI_MakeEdge(rectBottom1, rectBottom2).Edge());
  rectWire.Add(BRepBuilderAPI_MakeEdge(rectBottom2, rightPos).Edge());
  rectWire.Add(BRepBuilderAPI_MakeEdge(rightPos, leftPos).Edge());

  TopoDS_Face rectFace = BRepBuilderAPI_MakeFace(rectWire.Wire());
  TopoDS_Shape rectPlate =
      BRepPrimAPI_MakePrism(rectFace, gp_Vec(direction) * plateThickness)
          .Shape();

  // 4. 添加六角螺栓连接结构（根据分裂数确定尺寸）
  const double boltRadius = (params.subNum >= 4) ? 10.0 : 8.0; // M16/M20
  const double boltHeight = plateThickness * 1.5;

  // 中心螺栓（带螺母）
  gp_Ax2 boltAxis(centerPos, direction);
  TopoDS_Shape centerBolt = create_hex_bolt(boltAxis, boltRadius, boltHeight);

  // 左右连接螺栓（绝缘子串接口）
  gp_Ax2 leftBoltAxis(leftPos, direction);
  TopoDS_Shape leftBolt = create_hex_bolt(leftBoltAxis, boltRadius, boltHeight);

  gp_Ax2 rightBoltAxis(rightPos, direction);
  TopoDS_Shape rightBolt =
      create_hex_bolt(rightBoltAxis, boltRadius, boltHeight);

  // 5. 组装所有部件
  BRepAlgoAPI_Fuse plateFuser(trianglePlate, rectPlate);
  plateFuser = BRepAlgoAPI_Fuse(plateFuser.Shape(), centerBolt);
  plateFuser = BRepAlgoAPI_Fuse(plateFuser.Shape(), leftBolt);
  plateFuser = BRepAlgoAPI_Fuse(plateFuser.Shape(), rightBolt);

  // 6. 添加加强肋（提高机械强度）
  gp_Pnt ribBase1(centerPos.X(), centerPos.Y() - 30.0,
                  centerPos.Z() - rectHeight);
  gp_Pnt ribBase2(centerPos.X(), centerPos.Y() + 30.0,
                  centerPos.Z() - rectHeight);

  double ribWidth = 10.0;
  double ribHeight = 6.0;
  double ribLength = ribBase1.Distance(topVertex);

  TopoDS_Shape verticalRib1 =
      create_rectangular_beam(ribWidth, ribHeight, ribLength,
                              gp_Pnt((ribBase1.X() + topVertex.X()) / 2,
                                     (ribBase1.Y() + topVertex.Y()) / 2,
                                     (ribBase1.Z() + topVertex.Z()) / 2));

  TopoDS_Shape verticalRib2 =
      create_rectangular_beam(ribWidth, ribHeight, ribLength,
                              gp_Pnt((ribBase2.X() + topVertex.X()) / 2,
                                     (ribBase2.Y() + topVertex.Y()) / 2,
                                     (ribBase2.Z() + topVertex.Z()) / 2));

  plateFuser = BRepAlgoAPI_Fuse(plateFuser.Shape(), verticalRib1);
  plateFuser = BRepAlgoAPI_Fuse(plateFuser.Shape(), verticalRib2);

  return plateFuser.Shape();
}

/**
 * @brief 创建U型串底部连接板（矩形主体+六角螺栓连接）
 * @param params 绝缘子参数
 * @param centerPos 中心位置
 * @param leftPos 左连接点
 * @param rightPos 右连接点
 * @param direction 安装方向
 * @return 连接板形状
 */
TopoDS_Shape create_u_bottom_connection_plate(const insulator_params &params,
                                              const gp_Pnt &centerPos,
                                              const gp_Pnt &leftPos,
                                              const gp_Pnt &rightPos,
                                              const gp_Dir &direction) {
  // 1. 创建矩形主体板（厚度16mm，含均压环接口）
  const double plateWidth = params.uLinkLength + 100.0; // 两侧各超出50mm
  const double plateDepth = 80.0;                       // 前后方向尺寸
  const double plateThickness = 16.0;

  gp_Pnt corner1(centerPos.X() - plateWidth / 2, centerPos.Y() - plateDepth / 2,
                 centerPos.Z());
  gp_Pnt corner2(centerPos.X() + plateWidth / 2, centerPos.Y() + plateDepth / 2,
                 centerPos.Z());
  TopoDS_Shape basePlate = BRepPrimAPI_MakeBox(corner1, corner2).Shape();
  basePlate =
      BRepPrimAPI_MakePrism(basePlate, gp_Vec(direction) * plateThickness)
          .Shape();

  // 2. 添加六角螺栓连接结构
  const double boltRadius =
      (params.subNum >= 4) ? 12.0 : 10.0; // 底部用更大螺栓

  // 绝缘子连接螺栓
  gp_Ax2 leftBoltAxis(leftPos, direction);
  TopoDS_Shape leftBolt =
      create_hex_bolt(leftBoltAxis, boltRadius, plateThickness * 1.2);

  gp_Ax2 rightBoltAxis(rightPos, direction);
  TopoDS_Shape rightBolt =
      create_hex_bolt(rightBoltAxis, boltRadius, plateThickness * 1.2);

  // 3. 导线悬挂接口（根据分裂数变化）
  TopoDS_Shape conductorInterface;

  // 4. 均压环安装法兰（简化版）
  if (params.gradingRing.count > 0) {
    gp_Ax2 ringAxis(centerPos, direction);
    // 创建简化圆柱体代替法兰
    TopoDS_Shape ringFlange =
        BRepPrimAPI_MakeCylinder(ringAxis, params.gradingRing.radius, 15.0)
            .Shape();
    conductorInterface =
        BRepAlgoAPI_Fuse(conductorInterface, ringFlange).Shape();
  }

  // 5. 组装所有部件
  BRepAlgoAPI_Fuse plateFuser(basePlate, leftBolt);
  plateFuser = BRepAlgoAPI_Fuse(plateFuser.Shape(), rightBolt);
  plateFuser = BRepAlgoAPI_Fuse(plateFuser.Shape(), conductorInterface);

  return plateFuser.Shape();
}

// 创建绝缘子串
TopoDS_Shape create_disk_insulator(const insulator_params &params) {
  // 参数验证
  bool isComposite = params.insulator.material == insulator_material::COMPOSITE;
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

  double rodDiameter =
      isComposite ? compParams.minorRadius * 2 : diskDiameter / 10;

  if (diskDiameter <= 0 || diskThickness <= 0 ||
      params.insulator.leftCount <= 0 || rodDiameter <= 0 ||
      params.insulator.height <= 0) {
    throw Standard_ConstructionError("绝缘子参数必须为正数");
  }

  auto create_single_insulator = [&](const gp_Pnt &basePos, int diskCount) {
    gp_Ax2 rodAxis(basePos, gp_Dir(0, 0, 1));
    TopoDS_Shape rod = BRepPrimAPI_MakeCylinder(rodAxis, rodDiameter / 2,
                                                params.insulator.height)
                           .Shape();

    TopoDS_Shape insulator = rod;
    for (int i = 0; i < diskCount; i++) {
      double zPos = basePos.Z() + i * (diskSpacing + diskThickness);
      double currentDiameter =
          isComposite
              ? (i % 2 == 0 ? compParams.majorRadius : compParams.minorRadius) *
                    2
              : diskDiameter;

      // 创建伞裙剖面线
      BRepBuilderAPI_MakeWire wire;
      gp_Pnt p1(basePos.X() + rodDiameter / 2, basePos.Y(), zPos);
      gp_Pnt p2(basePos.X() + currentDiameter / 2, basePos.Y(),
                zPos + diskThickness * 0.3);
      wire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());

      gp_Pnt p3 = p2;
      gp_Pnt p4(basePos.X() + currentDiameter * 0.85, basePos.Y(),
                zPos + diskThickness * 0.5);
      gp_Pnt p5(basePos.X() + currentDiameter / 2, basePos.Y(),
                zPos + diskThickness);
      wire.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
      wire.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge());

      gp_Ax1 axis(basePos, gp_Dir(0, 0, 1));
      TopoDS_Shape shed = BRepPrimAPI_MakeRevol(wire.Wire(), axis).Shape();

      BRepAlgoAPI_Fuse fuser(insulator, shed);
      if (fuser.IsDone()) {
        insulator = fuser.Shape();
      }
    }
    return insulator;
  };

  // 创建绝缘子主体
  TopoDS_Shape insulatorBody;
  std::vector<TopoDS_Shape> topClamps; // 存储所有顶部金具
  gp_Pnt bottomClampPosition(0, 0, 0); // 底部金具位置

  if (params.vAngleLeft != 0 || params.vAngleRight != 0) { // V型串
    double angleL_rad = params.vAngleLeft * M_PI / 180.0;
    double angleR_rad = params.vAngleRight * M_PI / 180.0;

    // 创建左侧绝缘子串
    gp_Trsf leftTransform;
    leftTransform.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0)),
                              angleL_rad);
    TopoDS_Shape leftInsulator =
        create_single_insulator(gp_Pnt(0, 0, 0), params.insulator.leftCount);
    leftInsulator =
        BRepBuilderAPI_Transform(leftInsulator, leftTransform).Shape();

    // 左侧顶部金具
    gp_Pnt leftTopPos(params.insulator.height * sin(angleL_rad), 0,
                      params.insulator.height * cos(angleL_rad));
    TopoDS_Shape leftTopClamp = create_top_positioned_clamp(
        params, params.fittingLengths.leftUpper, leftTopPos,
        gp_Dir(sin(angleL_rad), 0, cos(angleL_rad)));
    topClamps.push_back(leftTopClamp);

    // 创建右侧绝缘子串
    gp_Trsf rightTransform;
    rightTransform.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0)),
                               -angleR_rad);
    TopoDS_Shape rightInsulator =
        create_single_insulator(gp_Pnt(0, 0, 0), params.insulator.rightCount);
    rightInsulator =
        BRepBuilderAPI_Transform(rightInsulator, rightTransform).Shape();

    // 右侧顶部金具
    gp_Pnt rightTopPos(-params.insulator.height * sin(angleR_rad), 0,
                       params.insulator.height * cos(angleR_rad));
    TopoDS_Shape rightTopClamp = create_top_positioned_clamp(
        params, params.fittingLengths.rightUpper, rightTopPos,
        gp_Dir(-sin(angleR_rad), 0, cos(angleR_rad)));
    topClamps.push_back(rightTopClamp);

    // 合并绝缘子主体
    BRepAlgoAPI_Fuse fuser(leftInsulator, rightInsulator);
    insulatorBody = fuser.Shape();
  } else if (params.uLinkLength > 0) { // U型串
    // U型串处理（保持原有逻辑）
    TopoDS_Shape leftInsulator = create_single_insulator(
        gp_Pnt(-params.uLinkLength / 2, 0, 0), params.insulator.leftCount);
    TopoDS_Shape rightInsulator = create_single_insulator(
        gp_Pnt(params.uLinkLength / 2, 0, 0), params.insulator.rightCount);

    // 2. 顶部连接板（关键修改）
    gp_Pnt topCenter(0, 0, params.insulator.height);
    TopoDS_Shape topConnectionPlate = create_u_top_connection_plate(
        params,    // 参数结构体
        topCenter, // 中心位置
        gp_Pnt(-params.uLinkLength / 2, 0, params.insulator.height), // 左连接点
        gp_Pnt(params.uLinkLength / 2, 0, params.insulator.height),  // 右连接点
        gp_Dir(0, 0, 1));                                            // 垂直方向

    // 3. 底部连接板（含均压环安装接口）
    gp_Pnt bottomCenter(0, 0, 0);
    TopoDS_Shape bottomConnectionPlate = create_u_bottom_connection_plate(
        params, bottomCenter, gp_Pnt(-params.uLinkLength / 2, 0, 0), // 左连接点
        gp_Pnt(params.uLinkLength / 2, 0, 0),                        // 右连接点
        gp_Dir(0, 0, -1));                                           // 向下方向

    // 4. 组装顺序（确保电气连续性）
    BRepAlgoAPI_Fuse finalAssembly(leftInsulator, rightInsulator);
    finalAssembly = BRepAlgoAPI_Fuse(finalAssembly.Shape(), topConnectionPlate);
    finalAssembly =
        BRepAlgoAPI_Fuse(finalAssembly.Shape(), bottomConnectionPlate);

    insulatorBody = finalAssembly.Shape();
    gp_Pnt topPos(0, 0, params.insulator.height);
    TopoDS_Shape topClamp = create_top_positioned_clamp(
        params, params.fittingLengths.leftUpper, topPos);
    topClamps.push_back(topClamp);
  } else { // I型串
    insulatorBody =
        create_single_insulator(gp_Pnt(0, 0, 0), params.insulator.leftCount);
    gp_Pnt topPos(0, 0, params.insulator.height);
    TopoDS_Shape topClamp = create_top_positioned_clamp(
        params, params.fittingLengths.leftUpper, topPos);
    topClamps.push_back(topClamp);
  }

  // 底部金具
  TopoDS_Shape bottomClamp =
      create_bottom_positioned_clamp(params, bottomClampPosition);

  // 均压环（如有）
  TopoDS_Shape gradingRing;
  if (params.gradingRing.count > 0) {
    double ringHeight = params.gradingRing.position > 0
                            ? params.gradingRing.position
                            : params.insulator.height * 0.7;
    gradingRing = create_grading_ring(params, gp_Pnt(0, 0, ringHeight));
  }

  // 组装所有部件
  BRepAlgoAPI_Fuse finalAssembly(insulatorBody, bottomClamp);

  // 添加所有顶部金具
  for (const auto &topClamp : topClamps) {
    if (finalAssembly.IsDone()) {
      finalAssembly = BRepAlgoAPI_Fuse(finalAssembly.Shape(), topClamp);
    }
  }

  // 添加均压环
  if (params.gradingRing.count > 0 && finalAssembly.IsDone()) {
    finalAssembly = BRepAlgoAPI_Fuse(finalAssembly.Shape(), gradingRing);
  }

  if (!finalAssembly.IsDone()) {
    throw Standard_ConstructionError("绝缘子串组装失败");
  }

  return finalAssembly.Shape();
}

TopoDS_Shape create_rod_insulator(const insulator_params &params) {
  // 参数验证
  bool isComposite = params.insulator.material == insulator_material::COMPOSITE;
  auto compParams =
      isComposite
          ? boost::get<composite_insulator_params>(params.insulator.radius)
          : composite_insulator_params{0, 0, 0};

  double rodDiameter = isComposite
                           ? compParams.minorRadius * 2
                           : boost::get<double>(params.insulator.radius) / 5;
  double rodLength = params.insulator.height;

  // 计算伞裙参数
  double shedThickness = isComposite ? compParams.gap * 0.4
                                     : params.insulator.height *
                                           0.05; // 普通绝缘子伞裙厚度为高度的5%
  double gap = isComposite ? compParams.gap
                           : (params.insulator.height -
                              shedThickness * params.insulator.leftCount) /
                                 (params.insulator.leftCount - 1);

  if (rodDiameter <= 0 || rodLength <= 0 ||
      (isComposite && compParams.majorRadius <= 0) || gap <= 0 ||
      params.insulator.leftCount <= 0) {
    throw Standard_ConstructionError("绝缘子参数必须为正数");
  }

  // 创建单个绝缘子单元
  auto create_single_insulator = [&](const gp_Pnt &position, int shedCount) {
    gp_Ax2 rodAxis(position, gp_Dir(0, 0, 1));
    TopoDS_Shape rod =
        BRepPrimAPI_MakeCylinder(rodAxis, rodDiameter / 2, rodLength).Shape();

    BRepAlgoAPI_Fuse fuser;
    for (int i = 0; i < shedCount; i++) {
      double zPos = i * (gap + shedThickness); // 伞裙位置计算
      double currentDiameter =
          isComposite
              ? (i % 2 == 0 ? compParams.majorRadius : compParams.minorRadius) *
                    2
              : boost::get<double>(params.insulator.radius) * 2;

      // 铜锣状伞裙截面（与分裂数无关）
      BRepBuilderAPI_MakeWire wire;
      gp_Pnt p_base(position.X(), position.Y(), zPos);
      gp_Pnt p1 = p_base.Translated(gp_Vec(rodDiameter / 2, 0, 0));
      gp_Pnt p2 = p1.Translated(
          gp_Vec((currentDiameter - rodDiameter) / 6, 0, shedThickness * 0.2));
      gp_Pnt p3(currentDiameter / 2, 0, zPos + shedThickness * 0.5);
      gp_Pnt p4(rodDiameter / 2 + (currentDiameter - rodDiameter) / 6, 0,
                zPos + shedThickness * 0.8);
      gp_Pnt p5(rodDiameter / 2, 0, zPos + shedThickness);

      wire.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
      wire.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
      wire.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
      wire.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge());

      // 旋转生成伞裙
      gp_Ax1 axis(p_base, gp_Dir(0, 0, 1));
      TopoDS_Shape shed = BRepPrimAPI_MakeRevol(wire.Wire(), axis).Shape();
      if (i == 0) {
        fuser = BRepAlgoAPI_Fuse(rod, shed);
      } else {
        fuser = BRepAlgoAPI_Fuse(fuser.Shape(), shed);
      }
    }

    return fuser.Shape();
  };

  // 创建绝缘子主体
  TopoDS_Shape insulatorBody;
  std::vector<TopoDS_Shape> topClamps; // 存储所有顶部金具
  gp_Pnt bottomClampPosition(0, 0, 0); // 底部金具位置

  // 处理V型、U型和I型绝缘子串
  if (params.vAngleLeft != 0 || params.vAngleRight != 0) { // V型串
    double angleL_rad = params.vAngleLeft * M_PI / 180.0;
    double angleR_rad = params.vAngleRight * M_PI / 180.0;

    // 创建左侧绝缘子串
    gp_Trsf leftTransform;
    leftTransform.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0)),
                              angleL_rad);
    TopoDS_Shape leftInsulator =
        create_single_insulator(gp_Pnt(0, 0, 0), params.insulator.leftCount);

    leftInsulator =
        BRepBuilderAPI_Transform(leftInsulator, leftTransform).Shape();

    // 左侧顶部金具
    gp_Pnt leftTopPos(params.insulator.height * sin(angleL_rad), 0,
                      params.insulator.height * cos(angleL_rad));
    TopoDS_Shape leftTopClamp = create_top_positioned_clamp(
        params, params.fittingLengths.leftUpper, leftTopPos,
        gp_Dir(sin(angleL_rad), 0, cos(angleL_rad)));
    topClamps.push_back(leftTopClamp);

    // 创建右侧绝缘子串
    gp_Trsf rightTransform;
    rightTransform.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0)),
                               -angleR_rad);
    TopoDS_Shape rightInsulator =
        create_single_insulator(gp_Pnt(0, 0, 0), params.insulator.rightCount);
    rightInsulator =
        BRepBuilderAPI_Transform(rightInsulator, rightTransform).Shape();

    // 右侧顶部金具
    gp_Pnt rightTopPos(-params.insulator.height * sin(angleR_rad), 0,
                       params.insulator.height * cos(angleR_rad));
    TopoDS_Shape rightTopClamp = create_top_positioned_clamp(
        params, params.fittingLengths.rightUpper, rightTopPos,
        gp_Dir(-sin(angleR_rad), 0, cos(angleR_rad)));
    topClamps.push_back(rightTopClamp);

    // 合并绝缘子主体
    BRepAlgoAPI_Fuse fuser(leftInsulator, rightInsulator);
    insulatorBody = fuser.Shape();
  } else if (params.uLinkLength > 0) { // U型串
    // 创建左侧绝缘子串
    TopoDS_Shape leftInsulator = create_single_insulator(
        gp_Pnt(-params.uLinkLength / 2, 0, 0), params.insulator.leftCount);

    // 创建右侧绝缘子串
    TopoDS_Shape rightInsulator = create_single_insulator(
        gp_Pnt(params.uLinkLength / 2, 0, 0), params.insulator.rightCount);

    // 创建中间连接部分 - 根据电力行业标准设计
    double connectorWidth = rodDiameter * 1.5; // 连接件宽度为芯棒直径的1.5倍
    double connectorThickness =
        rodDiameter * 0.8; // 连接件厚度为芯棒直径的0.8倍

    // 连接件长度等于U型串的水平长度
    TopoDS_Shape connector = create_rectangular_beam(
        connectorWidth, connectorThickness, params.uLinkLength,
        gp_Pnt(0, 0, -rodLength / 2)); // 连接件位于绝缘子串中部
    // 合并U型串
    BRepAlgoAPI_Fuse fuser(leftInsulator, rightInsulator);
    fuser = BRepAlgoAPI_Fuse(fuser.Shape(), connector);
    gp_Pnt topPos(0, 0, params.insulator.height);
    TopoDS_Shape topClamp = create_top_positioned_clamp(
        params, params.fittingLengths.leftUpper, topPos);
    topClamps.push_back(topClamp);
  } else { // I型串
    insulatorBody =
        create_single_insulator(gp_Pnt(0, 0, 0), params.insulator.leftCount);
    gp_Pnt topPos(0, 0, params.insulator.height);
    TopoDS_Shape topClamp = create_top_positioned_clamp(
        params, params.fittingLengths.leftUpper, topPos);
    topClamps.push_back(topClamp);
  }

  // 底部金具
  TopoDS_Shape bottomClamp =
      create_bottom_positioned_clamp(params, bottomClampPosition);

  // 均压环（如有）
  TopoDS_Shape gradingRing;
  if (params.gradingRing.count > 0) {
    double ringHeight = params.gradingRing.position > 0
                            ? params.gradingRing.position
                            : params.insulator.height * 0.7;
    gradingRing = create_grading_ring(params, gp_Pnt(0, 0, ringHeight));
  }

  // 组装所有部件
  BRepAlgoAPI_Fuse finalAssembly(insulatorBody, bottomClamp);

  // 添加所有顶部金具
  for (const auto &topClamp : topClamps) {
    if (finalAssembly.IsDone()) {
      finalAssembly = BRepAlgoAPI_Fuse(finalAssembly.Shape(), topClamp);
    }
  }

  // 添加均压环
  if (params.gradingRing.count > 0 && finalAssembly.IsDone()) {
    finalAssembly = BRepAlgoAPI_Fuse(finalAssembly.Shape(), gradingRing);
  }

  if (!finalAssembly.IsDone()) {
    throw Standard_ConstructionError("绝缘子串组装失败");
  }

  return finalAssembly.Shape();
}

TopoDS_Shape create_insulator_string(const insulator_params &params) {
  // 参数验证
  if (params.subNum <= 0 || params.subNum > 8 ||
      (params.subNum != 1 && params.subNum != 2 && params.subNum != 3 &&
       params.subNum != 4 && params.subNum != 6 && params.subNum != 8)) {
    throw Standard_ConstructionError("分裂数必须为1,2,3,4,6,8");
  }
  if (params.splitDistance <= 0) {
    throw Standard_ConstructionError("分裂间距必须为正数");
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
} // namespace topo
} // namespace flywave
