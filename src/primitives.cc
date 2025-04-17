#include "primitives.hh"
#include <BRepAlgoAPI_Common.hxx>
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
    throw Standard_ConstructionError("Radii must be positive");
  }
  if (params.height <= 0.0 || params.height > 2 * params.polarRadius) {
    throw Standard_ConstructionError("Height must be in (0, 2*polarRadius]");
  }

  // 正确的坐标系定义：
  // - 旋转轴为Z轴
  // - 椭圆在XZ平面（Y=0）
  // - 长轴（polarRadius）沿Z方向
  gp_Ax2 ellipseAxes(gp_Pnt(0, 0, 0), // 中心点
                     gp_Dir(0, -1, 0), // Y轴负方向为法向量（定义XZ平面）
                     gp_Dir(1, 0, 0) // X方向为参考方向
  );

  // 创建椭圆（主半径X方向=equatorialRadius，次半径Z方向=polarRadius）
  gp_Elips ellipse(ellipseAxes, params.equatorialRadius, params.polarRadius);

  // 生成半椭圆边（0-PI弧度）
  TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(ellipse, 0, M_PI).Edge();
  TopoDS_Wire wire = BRepBuilderAPI_MakeWire(edge).Wire();

  // 绕Z轴旋转360度生成完整椭球
  gp_Ax1 revolutionAxis(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0));
  BRepPrimAPI_MakeRevol revolMaker(wire, revolutionAxis);

  if (!revolMaker.IsDone()) {
    throw Standard_ConstructionError("Revol operation failed");
  }

  TopoDS_Shape fullEllipsoid = revolMaker.Shape();

  // 高度切割（沿X轴方向）
  if (params.height < 2 * params.polarRadius) {
    // 计算切割位置（注意：现在是沿X轴切割）
    double cutOffset = params.polarRadius - params.height / 2;

    // 创建切割工具（两个平行平面）
    gp_Pln cutPlane1(gp_Pnt(cutOffset, 0, 0), gp_Dir(0, 0, 1));
    gp_Pln cutPlane2(gp_Pnt(-cutOffset, 0, 0), gp_Dir(0, 0, -1));

    TopoDS_Shape cutter1 = BRepBuilderAPI_MakeFace(cutPlane1).Face();
    TopoDS_Shape cutter2 = BRepBuilderAPI_MakeFace(cutPlane2).Face();

    // 执行切割（先切割一侧，再切割另一侧）
    BRepAlgoAPI_Cut firstCut(fullEllipsoid, cutter1);
    if (!firstCut.IsDone()) {
      throw Standard_ConstructionError("First cut failed");
    }

    BRepAlgoAPI_Cut finalCut(firstCut.Shape(), cutter2);
    if (!finalCut.IsDone()) {
      throw Standard_ConstructionError("Second cut failed");
    }

    return finalCut.Shape();
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
  filletMaker.Add(Precision::Confusion() * 0.1,
                  sharpEdge); // 极小圆角模拟锐角
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
    gp_Pnt p1(skirtRadius, 0, zPos); // 伞裙外缘
    gp_Pnt p2(skirtRadius * 0.95, 0, zPos + segmentHeight * 0.1); // 轻微上翘
    gp_Pnt p3(skirtRadius * 0.7, 0, zPos + segmentHeight * 0.3); // 主要下凹
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
    gp_Pnt p1(skirtRadius, 0, zPos); // 伞裙外缘
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

  // 创建圆形截面
  gp_Circ circle(gp_Ax2(gp::Origin(), gp::DZ()), params.diameter / 2);
  TopoDS_Wire profile =
      BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(circle).Edge()).Wire();

  // 沿路径扫掠生成电缆
  BRepOffsetAPI_MakePipeShell pipeMaker(pathMaker.Wire());
  pipeMaker.SetMode(true); // 设置为实体模式
  pipeMaker.Add(profile);
  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create cable by pipe shell");
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
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge()); // 下翼缘底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge()); // 右下翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p9, p10).Edge()); // 右上翼缘垂直段
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
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge()); // 下翼缘底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge()); // 右下翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge()); // 右下翼缘水平段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge()); // 右腹板垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p5, p6).Edge()); // 右上翼缘水平段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p6, p7).Edge()); // 右上翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8).Edge()); // 上翼缘顶部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, p9).Edge()); // 左上翼缘垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p9, p10).Edge()); // 左上翼缘水平段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p10, p11).Edge()); // 左腹板垂直段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p11, p12).Edge()); // 左下翼缘水平段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p12, p1).Edge()); // 左下翼缘垂直段

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
  gp_Pnt p4(0, -halfWebThickness,
            -halfHeight + flangeThickness); // 改为负方向
  gp_Pnt p5(0, -halfWebThickness, halfHeight - flangeThickness); // 改为负方向
  gp_Pnt p6(0, -flangeWidth, halfHeight - flangeThickness); // 改为负方向
  gp_Pnt p7(0, -flangeWidth, halfHeight);                   // 改为负方向
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
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(),
                   gp::DX()); // Z:腹板方向, X:长度方向
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
TopoDS_Shape create_bored_pile_base(const bored_pile_params &params) {
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

    TopoDS_Shape pile = create_bored_pile_base(pileParams);

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

    // 创建右侧绝缘子串
    gp_Trsf rightTransform;
    rightTransform.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0)),
                               -angleR_rad);
    TopoDS_Shape rightInsulator =
        create_single_insulator(gp_Pnt(0, 0, 0), params.insulator.rightCount);
    rightInsulator =
        BRepBuilderAPI_Transform(rightInsulator, rightTransform).Shape();

    // 合并绝缘子主体
    BRepAlgoAPI_Fuse fuser(leftInsulator, rightInsulator);
    insulatorBody = fuser.Shape();
  } else if (params.uLinkLength > 0) { // U型串
    // U型串处理（移除连接板）
    TopoDS_Shape leftInsulator = create_single_insulator(
        gp_Pnt(-params.uLinkLength / 2, 0, 0), params.insulator.leftCount);
    TopoDS_Shape rightInsulator = create_single_insulator(
        gp_Pnt(params.uLinkLength / 2, 0, 0), params.insulator.rightCount);

    // 仅合并左右绝缘子
    BRepAlgoAPI_Fuse finalAssembly(leftInsulator, rightInsulator);
    insulatorBody = finalAssembly.Shape();
  } else { // I型串
    insulatorBody =
        create_single_insulator(gp_Pnt(0, 0, 0), params.insulator.leftCount);
  }

  return insulatorBody;
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

    // 创建右侧绝缘子串
    gp_Trsf rightTransform;
    rightTransform.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0)),
                               -angleR_rad);
    TopoDS_Shape rightInsulator =
        create_single_insulator(gp_Pnt(0, 0, 0), params.insulator.rightCount);
    rightInsulator =
        BRepBuilderAPI_Transform(rightInsulator, rightTransform).Shape();

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
    insulatorBody = fuser.Shape();
  } else { // I型串
    insulatorBody =
        create_single_insulator(gp_Pnt(0, 0, 0), params.insulator.leftCount);
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

TopoDS_Shape create_pole_tower(const pole_tower_params &params) {
  // 计算模型原点位置 - 通过腿的数量判断杆塔类型
  gp_Pnt origin;
  bool isLatticeTower = false;

  // 检查所有本体的腿数量
  for (const auto &body : params.bodies) {
    if (body.legs.size() > 1) {
      isLatticeTower = true;
      break;
    }
  }

  if (isLatticeTower) { // 桁架塔（腿数>1）
    // 找到最长腿的最低节点作为原点
    double minZ = DBL_MAX;
    for (const auto &body : params.bodies) {
      for (const auto &leg : body.legs) {
        for (const auto &node : leg.nodes) {
          if (node.position.Z() < minZ) {
            minZ = node.position.Z();
            origin = node.position;
          }
        }
      }
    }
  } else { // 输电杆（腿数<=1）
    // 原点在杆底中心
    origin = gp::Origin();
  }

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

        // 创建角钢截面
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
        polyMaker.Add(p1); // 闭合多边形
        TopoDS_Wire wire = polyMaker.Wire();

        // 计算杆件长度和方向
        double length = startPos.Distance(endPos);
        gp_Vec direction(startPos, endPos);

        // 创建角钢实体
        memberShape = BRepPrimAPI_MakePrism(
                          BRepBuilderAPI_MakeFace(wire).Face(), direction)
                          .Shape();
        break;
      }
      case member_type::TUBE: {
        // 创建等径钢管
        double diameter = std::stod(member.specification.substr(2));
        double thickness = std::stod(
            member.specification.substr(member.specification.find('X') + 1));

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

  // 创建挂点标识
  for (const auto &attachment : params.attachments) {
    // 创建小球标识挂点位置
    TopoDS_Shape attachmentMarker =
        BRepPrimAPI_MakeSphere(attachment.position,
                               50.0 // 挂点标记球半径50mm
                               )
            .Shape();

    builder.Add(tower, attachmentMarker);
  }

  gp_Trsf moveToOrigin;
  moveToOrigin.SetTranslation(gp_Vec(-origin.X(), -origin.Y(), -origin.Z()));
  BRepBuilderAPI_Transform moveTransform(tower, moveToOrigin);

  return moveTransform.Shape();
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
  gp_Ax2 boltAxis(gp::Origin(), gp::DZ());
  TopoDS_Shape bolt =
      BRepPrimAPI_MakeCylinder(boltAxis, params.boltDiameter / 2,
                               params.exposedLength + params.anchorLength)
          .Shape();

  // 创建弯钩部分
  if (params.hookDiameter > 0 && params.hookStraightLength > 0) {
    // 弯钩的起点(基础顶面处)
    gp_Pnt hookStart(0, 0, params.exposedLength);

    // 创建弯钩的直段
    gp_Pnt hookStraightEnd(0, 0,
                           params.exposedLength - params.hookStraightLength);
    TopoDS_Edge straightEdge =
        BRepBuilderAPI_MakeEdge(hookStart, hookStraightEnd).Edge();

    // 创建弯钩的圆弧段
    gp_Pnt circleCenter(0, params.hookDiameter / 2,
                        params.exposedLength - params.hookStraightLength);
    gp_Ax2 hookCircleAxis(circleCenter, gp::DX());

    TopoDS_Edge arcEdge =
        BRepBuilderAPI_MakeEdge(
            gp_Circ(hookCircleAxis, params.hookDiameter / 2), 0, M_PI)
            .Edge();

    // 将直段和圆弧段组合成弯钩
    BRepBuilderAPI_MakeWire hookWire;
    hookWire.Add(straightEdge);
    hookWire.Add(arcEdge);
    TopoDS_Wire hookProfile = hookWire.Wire();

    // 扫掠成弯钩实体(沿X方向)
    TopoDS_Shape hook =
        BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(hookProfile).Face(),
                              gp_Vec(params.boltDiameter, 0, 0))
            .Shape();

    // 将弯钩与螺栓主体融合
    bolt = BRepAlgoAPI_Fuse(bolt, hook).Shape();
  }

  // 创建蝶帽(螺母)
  for (int i = 0; i < params.nutCount; ++i) {
    gp_Pnt nutPos(0, 0, params.exposedLength + i * params.nutHeight);
    TopoDS_Shape nut =
        BRepPrimAPI_MakeCylinder(gp_Ax2(nutPos, gp::DZ()), params.nutOD / 2,
                                 params.nutHeight)
            .Shape();
    bolt = BRepAlgoAPI_Fuse(bolt, nut).Shape();
  }

  // 创建垫片
  for (int i = 0; i < params.washerCount; ++i) {
    gp_Pnt washerPos(0, 0,
                     params.exposedLength + params.nutCount * params.nutHeight +
                         i * params.washerThickness);

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
    bolt = BRepAlgoAPI_Fuse(bolt, washer).Shape();
  }

  return bolt;
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
  gp_Ax2 boltAxis(gp::Origin(), gp::DZ());
  BRepPrimAPI_MakeCylinder boltMaker(boltAxis, params.boltDiameter / 2,
                                     params.exposedLength +
                                         params.anchorLength);
  TopoDS_Shape bolt = boltMaker.Shape();

  // 创建蝶帽
  TopoDS_Shape nuts;
  if (params.nutCount > 0) {
    BRepPrimAPI_MakeCylinder nutMaker(boltAxis, params.nutOD / 2,
                                      params.nutHeight);
    TopoDS_Shape nut = nutMaker.Shape();

    // 移动蝶帽到螺栓顶部
    gp_Trsf nutTrsf;
    nutTrsf.SetTranslation(gp_Vec(0, 0, params.exposedLength));
    BRepBuilderAPI_Transform nutTransform(nut, nutTrsf);
    nuts = nutTransform.Shape();

    // 如果有多个蝶帽，创建堆叠
    for (int i = 1; i < params.nutCount; i++) {
      gp_Trsf nextNutTrsf;
      nextNutTrsf.SetTranslation(
          gp_Vec(0, 0, params.exposedLength + i * params.nutHeight));
      BRepBuilderAPI_Transform nextNutTransform(nut, nextNutTrsf);
      nuts = BRepAlgoAPI_Fuse(nuts, nextNutTransform.Shape()).Shape();
    }
  }

  // 创建垫片
  TopoDS_Shape washers;
  if (params.washerCount > 0) {
    TopoDS_Shape washer;
    if (params.washerShape == 1) { // 方形垫片
      BRepPrimAPI_MakeBox washerMaker(params.washerSize, params.washerSize,
                                      params.washerThickness);
      washer = washerMaker.Shape();
    } else { // 圆形垫片
      BRepPrimAPI_MakeCylinder washerMaker(boltAxis, params.washerSize / 2,
                                           params.washerThickness);
      washer = washerMaker.Shape();
    }

    // 移动垫片到螺栓底部
    gp_Trsf washerTrsf;
    washerTrsf.SetTranslation(gp_Vec(0, 0, -params.washerThickness));
    BRepBuilderAPI_Transform washerTransform(washer, washerTrsf);
    washers = washerTransform.Shape();

    // 如果有多个垫片，创建堆叠
    for (int i = 1; i < params.washerCount; i++) {
      gp_Trsf nextWasherTrsf;
      nextWasherTrsf.SetTranslation(gp_Vec(0, 0, -i * params.washerThickness));
      BRepBuilderAPI_Transform nextWasherTransform(washer, nextWasherTrsf);
      washers = BRepAlgoAPI_Fuse(washers, nextWasherTransform.Shape()).Shape();
    }
  }

  // 创建三钩锚固部分
  // 创建三个弯钩
  TopoDS_Shape hooks;
  for (int i = 0; i < 3; i++) {
    // 计算每个钩子的角度 (0°, 120°, 240°)
    double angle = i * (2 * M_PI / 3);

    // 创建直段A
    gp_Pnt startPoint(0, 0, -params.anchorLength);
    gp_Pnt endPoint(params.hookStraightLengthA * cos(angle),
                    params.hookStraightLengthA * sin(angle),
                    -params.anchorLength);
    TopoDS_Edge straightA =
        BRepBuilderAPI_MakeEdge(startPoint, endPoint).Edge();

    // 创建弯钩圆弧
    gp_Pnt arcCenter(
        endPoint.X() + params.hookDiameter / 2 * cos(angle + M_PI / 2),
        endPoint.Y() + params.hookDiameter / 2 * sin(angle + M_PI / 2),
        endPoint.Z());
    gp_Pnt arcEnd(endPoint.X() + params.hookDiameter * cos(angle + M_PI),
                  endPoint.Y() + params.hookDiameter * sin(angle + M_PI),
                  endPoint.Z());
    Handle(Geom_TrimmedCurve) arc =
        GC_MakeArcOfCircle(endPoint, arcCenter, arcEnd).Value();
    TopoDS_Edge hookArc = BRepBuilderAPI_MakeEdge(arc).Edge();

    // 创建直段B
    gp_Pnt straightBEnd(
        arcEnd.X() + params.hookStraightLengthB * cos(angle + M_PI),
        arcEnd.Y() + params.hookStraightLengthB * sin(angle + M_PI),
        arcEnd.Z());
    TopoDS_Edge straightB =
        BRepBuilderAPI_MakeEdge(arcEnd, straightBEnd).Edge();

    // 创建整个钩子的线
    BRepBuilderAPI_MakeWire hookWire;
    hookWire.Add(straightA);
    hookWire.Add(hookArc);
    hookWire.Add(straightB);

    // 扫掠成实体
    BRepOffsetAPI_MakePipe pipeMaker(
        hookWire.Wire(),
        BRepBuilderAPI_MakeEdge(gp_Circ(gp_Ax2(gp::Origin(), gp::DZ()),
                                        params.anchorBarDiameter / 2))
            .Edge());
    TopoDS_Shape hook = pipeMaker.Shape();

    // 合并钩子
    if (hooks.IsNull()) {
      hooks = hook;
    } else {
      hooks = BRepAlgoAPI_Fuse(hooks, hook).Shape();
    }
  }

  // 合并所有部件
  TopoDS_Shape result = bolt;
  if (!nuts.IsNull())
    result = BRepAlgoAPI_Fuse(result, nuts).Shape();
  if (!washers.IsNull())
    result = BRepAlgoAPI_Fuse(result, washers).Shape();
  if (!hooks.IsNull())
    result = BRepAlgoAPI_Fuse(result, hooks).Shape();

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
  gp_Ax2 boltAxis(gp::Origin(), gp::DZ());
  TopoDS_Shape bolt =
      BRepPrimAPI_MakeCylinder(boltAxis, params.boltDiameter / 2,
                               params.exposedLength + params.anchorLength)
          .Shape();

  // 创建下锚板
  gp_Pnt basePlateCenter(0, 0, -params.anchorLength);
  TopoDS_Shape basePlate;
  if (params.washerShape == 1) { // 方形垫片
    basePlate = BRepPrimAPI_MakeBox(
                    gp_Pnt(-params.basePlateSize / 2, -params.basePlateSize / 2,
                           -params.anchorLength - params.basePlateThickness),
                    params.basePlateSize, params.basePlateSize,
                    params.basePlateThickness)
                    .Shape();
  } else { // 圆形垫片
    basePlate = BRepPrimAPI_MakeCylinder(gp_Ax2(basePlateCenter, gp::DZ()),
                                         params.basePlateSize / 2,
                                         params.basePlateThickness)
                    .Shape();
  }

  // 创建肋板 (4个对称肋板)
  TopoDS_Shape ribs;
  for (int i = 0; i < 4; ++i) {
    double angle = i * M_PI_2; // 0, 90, 180, 270度

    // 创建肋板多边形点
    gp_Pnt p1(0, 0, -params.anchorLength);
    gp_Pnt p2(params.ribTopWidth / 2 * cos(angle),
              params.ribTopWidth / 2 * sin(angle), -params.anchorLength);
    gp_Pnt p3(params.ribBottomWidth / 2 * cos(angle),
              params.ribBottomWidth / 2 * sin(angle),
              -params.anchorLength - params.ribHeight);
    gp_Pnt p4(0, 0, -params.anchorLength - params.ribHeight);

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

    if (ribs.IsNull()) {
      ribs = rib;
    } else {
      ribs = BRepAlgoAPI_Fuse(ribs, rib).Shape();
    }
  }

  // 创建蝶帽和垫片
  TopoDS_Shape nutsAndWashers;
  double zPos = 0.0;
  for (int i = 0; i < params.nutCount; ++i) {
    // 垫片
    TopoDS_Shape washer;
    if (params.washerShape == 1) { // 方形垫片
      washer = BRepPrimAPI_MakeBox(
                   gp_Pnt(-params.washerSize / 2, -params.washerSize / 2, zPos),
                   params.washerSize, params.washerSize, params.washerThickness)
                   .Shape();
    } else { // 圆形垫片
      washer = BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, zPos), gp::DZ()),
                                        params.washerSize / 2,
                                        params.washerThickness)
                   .Shape();
    }

    // 蝶帽
    TopoDS_Shape nut =
        BRepPrimAPI_MakeCylinder(
            gp_Ax2(gp_Pnt(0, 0, zPos + params.washerThickness), gp::DZ()),
            params.nutOD / 2, params.nutHeight)
            .Shape();

    // 合并
    TopoDS_Shape nutAndWasher = BRepAlgoAPI_Fuse(washer, nut).Shape();
    if (nutsAndWashers.IsNull()) {
      nutsAndWashers = nutAndWasher;
    } else {
      nutsAndWashers = BRepAlgoAPI_Fuse(nutsAndWashers, nutAndWasher).Shape();
    }

    zPos += params.washerThickness + params.nutHeight;
  }

  // 合并所有部件
  TopoDS_Shape anchor = BRepAlgoAPI_Fuse(bolt, basePlate).Shape();
  anchor = BRepAlgoAPI_Fuse(anchor, ribs).Shape();
  if (!nutsAndWashers.IsNull()) {
    anchor = BRepAlgoAPI_Fuse(anchor, nutsAndWashers).Shape();
  }

  return anchor;
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
  gp_Ax2 boltAxis(gp::Origin(), gp::DZ());
  TopoDS_Shape bolt =
      BRepPrimAPI_MakeCylinder(boltAxis, params.boltDiameter / 2,
                               params.exposedLength + params.anchorLength)
          .Shape();

  // 创建下锚板
  double plateZ = -params.anchorLength - params.boltToPlateDistance -
                  params.basePlateThickness;
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

  // 创建蝶帽和垫片
  TopoDS_Shape nutsAndWashers;
  double zPos = 0.0;
  for (int i = 0; i < params.nutCount; ++i) {
    // 垫片
    TopoDS_Shape washer;
    if (params.washerShape == 1) { // 方形垫片
      washer = BRepPrimAPI_MakeBox(
                   gp_Pnt(-params.washerSize / 2, -params.washerSize / 2, zPos),
                   params.washerSize, params.washerSize, params.washerThickness)
                   .Shape();
    } else { // 圆形垫片
      washer =
          BRepPrimAPI_MakeCylinder(
              gp_Ax2(gp_Pnt(0, 0, zPos + params.washerThickness / 2), gp::DZ()),
              params.washerSize / 2, params.washerThickness)
              .Shape();
    }

    // 蝶帽
    TopoDS_Shape nut =
        BRepPrimAPI_MakeCylinder(
            gp_Ax2(gp_Pnt(0, 0, zPos + params.washerThickness), gp::DZ()),
            params.nutOD / 2, params.nutHeight)
            .Shape();

    // 合并
    TopoDS_Shape nutAndWasher = BRepAlgoAPI_Fuse(washer, nut).Shape();
    if (nutsAndWashers.IsNull()) {
      nutsAndWashers = nutAndWasher;
    } else {
      nutsAndWashers = BRepAlgoAPI_Fuse(nutsAndWashers, nutAndWasher).Shape();
    }

    zPos += params.washerThickness + params.nutHeight;
  }

  // 合并所有部件
  TopoDS_Shape anchor = BRepAlgoAPI_Fuse(bolt, basePlate).Shape();
  if (!nutsAndWashers.IsNull()) {
    anchor = BRepAlgoAPI_Fuse(anchor, nutsAndWashers).Shape();
  }

  return anchor;
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

  // 创建螺栓主体 (Z轴方向)
  gp_Ax2 boltAxis(gp::Origin(), gp::DZ());
  TopoDS_Shape bolt =
      BRepPrimAPI_MakeCylinder(boltAxis, params.boltDiameter / 2,
                               params.exposedLength + params.anchorLength)
          .Shape();

  // 创建三支弯臂
  TopoDS_Shape arms;
  for (int i = 0; i < 3; ++i) {
    double angle = i * (2 * M_PI / 3); // 0°, 120°, 240°

    // 创建直段
    gp_Pnt startPoint(0, 0, -params.anchorLength);
    gp_Pnt endPoint(params.armStraightLength * cos(angle),
                    params.armStraightLength * sin(angle),
                    -params.anchorLength);
    TopoDS_Edge straightEdge =
        BRepBuilderAPI_MakeEdge(startPoint, endPoint).Edge();

    // 创建弯折段
    gp_Pnt bendEndPoint(endPoint.X() + params.armBendLength * cos(angle) *
                                           cos(params.armBendAngle),
                        endPoint.Y() + params.armBendLength * sin(angle) *
                                           cos(params.armBendAngle),
                        endPoint.Z() -
                            params.armBendLength * sin(params.armBendAngle));

    // 创建弯折圆弧
    gp_Pnt arcCenter(endPoint.X() + params.armBendLength * cos(angle) *
                                        (1 - cos(params.armBendAngle)) /
                                        sin(params.armBendAngle),
                     endPoint.Y() + params.armBendLength * sin(angle) *
                                        (1 - cos(params.armBendAngle)) /
                                        sin(params.armBendAngle),
                     endPoint.Z());

    Handle(Geom_TrimmedCurve) arc =
        GC_MakeArcOfCircle(endPoint, bendEndPoint, arcCenter).Value();
    TopoDS_Edge bendEdge = BRepBuilderAPI_MakeEdge(arc).Edge();

    // 组合成线
    BRepBuilderAPI_MakeWire armWire;
    armWire.Add(straightEdge);
    armWire.Add(bendEdge);

    // 扫掠成实体
    BRepOffsetAPI_MakePipe pipeMaker(
        armWire.Wire(),
        BRepBuilderAPI_MakeEdge(
            gp_Circ(gp_Ax2(gp::Origin(), gp::DZ()), params.armDiameter / 2))
            .Edge());
    TopoDS_Shape arm = pipeMaker.Shape();

    if (arms.IsNull()) {
      arms = arm;
    } else {
      arms = BRepAlgoAPI_Fuse(arms, arm).Shape();
    }
  }

  // 创建蝶帽和垫片
  TopoDS_Shape nutsAndWashers;
  double zPos = 0.0;
  for (int i = 0; i < params.nutCount; ++i) {
    // 垫片
    TopoDS_Shape washer;
    if (params.washerShape == 1) { // 方形垫片
      washer = BRepPrimAPI_MakeBox(
                   gp_Pnt(-params.washerSize / 2, -params.washerSize / 2, zPos),
                   params.washerSize, params.washerSize, params.washerThickness)
                   .Shape();
    } else { // 圆形垫片
      washer = BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, zPos), gp::DZ()),
                                        params.washerSize / 2,
                                        params.washerThickness)
                   .Shape();
    }

    // 蝶帽
    TopoDS_Shape nut =
        BRepPrimAPI_MakeCylinder(
            gp_Ax2(gp_Pnt(0, 0, zPos + params.washerThickness), gp::DZ()),
            params.nutOD / 2, params.nutHeight)
            .Shape();

    // 合并
    TopoDS_Shape nutAndWasher = BRepAlgoAPI_Fuse(washer, nut).Shape();
    if (nutsAndWashers.IsNull()) {
      nutsAndWashers = nutAndWasher;
    } else {
      nutsAndWashers = BRepAlgoAPI_Fuse(nutsAndWashers, nutAndWasher).Shape();
    }

    zPos += params.washerThickness + params.nutHeight;
  }

  // 合并所有部件
  TopoDS_Shape anchor = BRepAlgoAPI_Fuse(bolt, arms).Shape();
  if (!nutsAndWashers.IsNull()) {
    anchor = BRepAlgoAPI_Fuse(anchor, nutsAndWashers).Shape();
  }

  return anchor;
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

  // 创建螺栓主体 (Z轴方向)
  gp_Ax2 boltAxis(gp::Origin(), gp::DZ());
  TopoDS_Shape bolt =
      BRepPrimAPI_MakeCylinder(boltAxis, params.boltDiameter / 2,
                               params.exposedLength + params.anchorLength)
          .Shape();

  // 创建定位板
  double plateZ = -params.anchorLength + params.toBaseDistance;
  TopoDS_Shape plate =
      BRepPrimAPI_MakeBox(
          gp_Pnt(-params.plateLength / 2, -params.plateLength / 2, plateZ),
          params.plateLength, params.plateLength, params.plateThickness)
          .Shape();

  // 创建灌注孔
  if (params.groutHoleDiameter > 0) {
    TopoDS_Shape hole =
        BRepPrimAPI_MakeCylinder(
            gp_Ax2(gp_Pnt(0, 0, plateZ + params.plateThickness / 2), gp::DZ()),
            params.groutHoleDiameter / 2, params.plateThickness)
            .Shape();
    plate = BRepAlgoAPI_Cut(plate, hole).Shape();
  }

  // 创建蝶帽和垫片
  TopoDS_Shape nutsAndWashers;
  double zPos = 0.0;
  for (int i = 0; i < params.nutCount; ++i) {
    // 垫片
    TopoDS_Shape washer;
    if (params.washerShape == 1) { // 方形垫片
      washer = BRepPrimAPI_MakeBox(
                   gp_Pnt(-params.washerSize / 2, -params.washerSize / 2, zPos),
                   params.washerSize, params.washerSize, params.washerThickness)
                   .Shape();
    } else { // 圆形垫片
      washer =
          BRepPrimAPI_MakeCylinder(
              gp_Ax2(gp_Pnt(0, 0, zPos + params.washerThickness / 2), gp::DZ()),
              params.washerSize / 2, params.washerThickness)
              .Shape();
    }

    // 蝶帽
    TopoDS_Shape nut =
        BRepPrimAPI_MakeCylinder(
            gp_Ax2(gp_Pnt(0, 0, zPos + params.washerThickness), gp::DZ()),
            params.nutOD / 2, params.nutHeight)
            .Shape();

    // 合并
    TopoDS_Shape nutAndWasher = BRepAlgoAPI_Fuse(washer, nut).Shape();
    if (nutsAndWashers.IsNull()) {
      nutsAndWashers = nutAndWasher;
    } else {
      nutsAndWashers = BRepAlgoAPI_Fuse(nutsAndWashers, nutAndWasher).Shape();
    }

    zPos += params.washerThickness + params.nutHeight;
  }

  // 合并所有部件
  TopoDS_Shape anchor = BRepAlgoAPI_Fuse(bolt, plate).Shape();
  if (!nutsAndWashers.IsNull()) {
    anchor = BRepAlgoAPI_Fuse(anchor, nutsAndWashers).Shape();
  }

  return anchor;
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

  // 创建钢管截面轮廓
  gp_Circ outerCircle(gp_Ax2(gp::Origin(), gp::DZ()), params.diameter / 2);
  gp_Circ innerCircle(gp_Ax2(gp::Origin(), gp::DZ()),
                      params.diameter / 2 - params.thickness);

  TopoDS_Edge outerEdge = BRepBuilderAPI_MakeEdge(outerCircle).Edge();
  TopoDS_Edge innerEdge = BRepBuilderAPI_MakeEdge(innerCircle).Edge();

  BRepBuilderAPI_MakeWire wireMaker;
  wireMaker.Add(outerEdge);
  wireMaker.Add(innerEdge);
  TopoDS_Wire wire = wireMaker.Wire();

  // 考虑坡度创建拉伸方向向量
  gp_Vec extrusionVec(0, 0, -params.anchorLength);
  if (params.slope != 0) {
    double slopeRad = params.slope * M_PI / 180.0;
    extrusionVec.SetX(-tan(slopeRad) * params.anchorLength);
  }

  // 创建钢管主体
  TopoDS_Shape tube =
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
    tube = BRepAlgoAPI_Fuse(tube, exposedPart).Shape();
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
  if (params.outside_diameter <= 0.0) {
    throw Standard_ConstructionError("Outside diameter must be positive");
  }

  // 创建电缆路径
  BRepBuilderAPI_MakePolygon polyMaker;
  for (const auto &point : params.points) {
    polyMaker.Add(point);
  }
  if (!polyMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create cable path");
  }
  TopoDS_Wire pathWire = polyMaker.Wire();

  // 创建截面圆
  gp_Circ sectionCircle(
      gp_Ax2(params.points[0],
             gp_Vec(params.points[0], params.points[1]).Normalized()),
      params.outside_diameter / 2);
  TopoDS_Edge sectionEdge = BRepBuilderAPI_MakeEdge(sectionCircle).Edge();
  TopoDS_Wire sectionWire = BRepBuilderAPI_MakeWire(sectionEdge).Wire();

  // 沿路径扫掠生成电缆
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.Add(sectionWire);
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to generate cable wire");
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
  double middleLength = params.length - 2 * params.terminalLength;

  // 创建中间圆柱体
  gp_Ax2 middleAxis(gp_Pnt(0, 0, -middleLength / 2), gp::DZ());
  TopoDS_Shape middleCyl =
      BRepPrimAPI_MakeCylinder(middleAxis, params.outerDiameter / 2,
                               middleLength)
          .Shape();

  // 创建两端过渡圆台
  gp_Ax2 leftAxis(gp_Pnt(0, 0, -params.length / 2), gp::DZ());
  TopoDS_Shape leftCone =
      BRepPrimAPI_MakeCone(leftAxis, params.outerDiameter / 2,
                           params.innerDiameter / 2, params.terminalLength)
          .Shape();

  gp_Ax2 rightAxis(gp_Pnt(0, 0, params.length / 2 - params.terminalLength),
                   gp::DZ());
  TopoDS_Shape rightCone =
      BRepPrimAPI_MakeCone(rightAxis, params.innerDiameter / 2,
                           params.outerDiameter / 2, params.terminalLength)
          .Shape();

  // 合并所有部件
  TopoDS_Shape joint = BRepAlgoAPI_Fuse(middleCyl, leftCone).Shape();
  joint = BRepAlgoAPI_Fuse(joint, rightCone).Shape();

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
  gp_Pnt corner(-params.length / 2, -params.width / 2, 0);
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

TopoDS_Shape create_cable_terminal(const cable_terminal_params &params) {
  // 参数验证
  if (params.height <= 0) {
    throw Standard_ConstructionError("Terminal height must be positive");
  }
  if (params.sort < 1 || params.sort > 3) {
    throw Standard_ConstructionError("Terminal type must be 1, 2 or 3");
  }

  // 创建主套管（锥形套管）
  gp_Ax2 axis(gp::Origin(), gp::DZ());
  BRepPrimAPI_MakeCone mainBodyMaker(axis, params.bottomDiameter / 2,
                                     params.topDiameter / 2, params.height);
  TopoDS_Shape terminal = mainBodyMaker.Shape();

  // 创建尾管（圆柱体）
  if (params.tailHeight > 0 && params.tailDiameter > 0) {
    BRepPrimAPI_MakeCylinder tailMaker(
        gp_Ax2(gp_Pnt(0, 0, -params.tailHeight), gp::DZ()),
        params.tailDiameter / 2, params.tailHeight);
    terminal = BRepAlgoAPI_Fuse(terminal, tailMaker.Shape()).Shape();
  }

  // 创建上端子（圆柱体）
  if (params.upperTerminalDiameter > 0) {
    BRepPrimAPI_MakeCylinder upperTerminalMaker(
        gp_Ax2(gp_Pnt(0, 0, params.height), gp::DZ()),
        params.upperTerminalDiameter / 2,
        params.height * 0.1); // 假设高度为总高的10%
    terminal = BRepAlgoAPI_Fuse(terminal, upperTerminalMaker.Shape()).Shape();
  }

  // 创建下端子（圆柱体）
  if (params.lowerTerminalLength > 0 && params.lowerTerminalDiameter > 0) {
    BRepPrimAPI_MakeCylinder lowerTerminalMaker(
        gp_Ax2(gp_Pnt(0, 0, -params.tailHeight - params.lowerTerminalLength),
               gp::DZ()),
        params.lowerTerminalDiameter / 2, params.lowerTerminalLength);
    terminal = BRepAlgoAPI_Fuse(terminal, lowerTerminalMaker.Shape()).Shape();
  }

  // 创建连接孔
  if (params.hole1Diameter > 0) {
    // 孔1
    BRepPrimAPI_MakeCylinder hole1Maker(
        gp_Ax2(gp_Pnt(params.hole1Distance, 0, params.height * 0.5), gp::DY()),
        params.hole1Diameter / 2, params.topDiameter);
    terminal = BRepAlgoAPI_Cut(terminal, hole1Maker.Shape()).Shape();

    // 孔2（如果有）
    if (params.hole2Diameter > 0 && params.holeSpacing > 0) {
      BRepPrimAPI_MakeCylinder hole2Maker(
          gp_Ax2(gp_Pnt(params.hole1Distance + params.holeSpacing, 0,
                        params.height * 0.5),
                 gp::DY()),
          params.hole2Diameter / 2, params.topDiameter);
      terminal = BRepAlgoAPI_Cut(terminal, hole2Maker.Shape()).Shape();
    }
  }

  // 如果是户外终端，创建法兰盘
  if (params.sort == 1) {
    // 创建法兰盘基座（圆柱体）
    BRepPrimAPI_MakeCylinder flangeBaseMaker(
        gp_Ax2(gp_Pnt(0, 0, -params.tailHeight), gp::DZ()),
        params.bottomDiameter / 2 + params.flangeWidth,
        params.flangeBoltHeight);

    // 创建中心孔
    BRepPrimAPI_MakeCylinder centerHoleMaker(
        gp_Ax2(gp_Pnt(0, 0, -params.tailHeight), gp::DZ()),
        params.flangeCenterHoleRadius, params.flangeBoltHeight * 2);

    // 组合法兰盘
    TopoDS_Shape flange =
        BRepAlgoAPI_Cut(flangeBaseMaker.Shape(), centerHoleMaker.Shape())
            .Shape();

    // 创建连接孔
    if (params.flangeHoleDiameter > 0 && params.flangeHoleSpacing > 0) {
      double holeRadius = params.bottomDiameter / 2 + params.flangeWidth / 2;
      for (int i = 0; i < 4; i++) { // 4个连接孔
        double angle = i * M_PI / 2;
        gp_Pnt holePos(holeRadius * cos(angle), holeRadius * sin(angle),
                       -params.tailHeight);
        BRepPrimAPI_MakeCylinder holeMaker(gp_Ax2(holePos, gp::DZ()),
                                           params.flangeHoleDiameter / 2,
                                           params.flangeBoltHeight * 2);
        flange = BRepAlgoAPI_Cut(flange, holeMaker.Shape()).Shape();
      }
    }

    // 添加法兰盘到终端
    terminal = BRepAlgoAPI_Fuse(terminal, flange).Shape();
  }

  return terminal;
}

TopoDS_Shape create_cable_terminal(const cable_terminal_params &params,
                                   const gp_Pnt &position,
                                   const gp_Dir &direction) {
  // 首先创建标准方向的终端
  TopoDS_Shape terminal = create_cable_terminal(params);

  // 创建变换：从标准方向旋转到指定方向，然后平移到指定位置
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ());
  gp_Ax3 targetAx3(position, direction);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

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
  gp_Pnt origin(-params.length / 2, -params.width / 2, 0);
  TopoDS_Shape box =
      BRepPrimAPI_MakeBox(origin, params.length, params.width, params.height)
          .Shape();

  // 创建电缆进出口
  double angleStep = 2 * M_PI / params.portCount;
  double radius = std::min(params.length, params.width) * 0.4;

  for (int i = 0; i < params.portCount; ++i) {
    double angle = i * angleStep;
    double x = radius * cos(angle);
    double y = radius * sin(angle);

    // 计算端口位置
    gp_Pnt portCenter;
    if (params.type == cable_box_type::DIRECT_GROUND) {
      // 直接接地箱端口在侧面
      portCenter = gp_Pnt(x,
                          y > 0 ? params.width / 2 + params.sidePanelDistance
                                : -params.width / 2 - params.sidePanelDistance,
                          params.height / 2);
    } else {
      // 其他类型端口在后面
      portCenter = gp_Pnt(params.length / 2 + params.backPanelDistance, y,
                          params.height / 2);
    }

    // 创建端口圆柱
    gp_Ax2 portAxis(portCenter, gp_Dir(x, y, 0));
    TopoDS_Shape port =
        BRepPrimAPI_MakeCylinder(portAxis, params.portDiameter / 2, 50).Shape();

    // 合并到主体
    BRepAlgoAPI_Fuse fuseMaker(box, port);
    if (!fuseMaker.IsDone()) {
      throw Standard_ConstructionError("Failed to fuse port with box");
    }
    box = fuseMaker.Shape();
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
  gp_Pnt rootP1(0, 0, 0);
  gp_Pnt rootP2(params.rootThickness, 0, 0);
  gp_Pnt rootP3(params.rootThickness, params.rootWidth, 0);
  gp_Pnt rootP4(0, params.rootWidth, 0);

  BRepBuilderAPI_MakePolygon rootPoly;
  rootPoly.Add(rootP1);
  rootPoly.Add(rootP2);
  rootPoly.Add(rootP3);
  rootPoly.Add(rootP4);
  rootPoly.Close();

  TopoDS_Face rootFace = BRepBuilderAPI_MakeFace(rootPoly.Wire()).Face();
  TopoDS_Shape root =
      BRepPrimAPI_MakePrism(rootFace, gp_Vec(0, 0, params.rootHeight)).Shape();

  // 创建支架顶部（水平部分）
  gp_Pnt topP1(0, 0, params.rootHeight);
  gp_Pnt topP2(params.topThickness, 0, params.rootHeight);
  gp_Pnt topP3(params.topThickness, params.width, params.rootHeight);
  gp_Pnt topP4(0, params.width, params.rootHeight);

  BRepBuilderAPI_MakePolygon topPoly;
  topPoly.Add(topP1);
  topPoly.Add(topP2);
  topPoly.Add(topP3);
  topPoly.Add(topP4);
  topPoly.Close();

  TopoDS_Face topFace = BRepBuilderAPI_MakeFace(topPoly.Wire()).Face();
  TopoDS_Shape top =
      BRepPrimAPI_MakePrism(topFace, gp_Vec(0, 0, params.length)).Shape();

  // 合并根部和顶部
  TopoDS_Shape support = BRepAlgoAPI_Fuse(root, top).Shape();

  // 创建立柱安装孔
  for (const auto &point : params.columnMountPoints) {
    gp_Pnt holePos(point.X(), point.Y(), point.Z());
    TopoDS_Shape hole = BRepPrimAPI_MakeCylinder(gp_Ax2(holePos, gp::DX()),
                                                 params.rootThickness / 2,
                                                 params.rootThickness * 2)
                            .Shape();
    support = BRepAlgoAPI_Cut(support, hole).Shape();
  }

  // 创建夹具安装孔
  for (const auto &point : params.clampMountPoints) {
    gp_Pnt holePos(point.X(), point.Y(), point.Z());
    TopoDS_Shape hole = BRepPrimAPI_MakeCylinder(gp_Ax2(holePos, gp::DZ()),
                                                 params.topThickness / 2,
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

  // 创建基础圆柱体
  gp_Ax2 axis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  TopoDS_Shape baseCylinder =
      BRepPrimAPI_MakeCylinder(axis, params.diameter / 2, params.width).Shape();

  // 根据不同类型创建夹具
  switch (params.type) {
  case cable_clamp_type::SINGLE: {
    // 单根夹具 - 简单圆柱体
    return baseCylinder;
  }
  case cable_clamp_type::LINEAR: {
    // 一字式夹具 - 带槽的圆柱体
    double slotWidth = params.diameter * 0.3;
    gp_Pnt slotPos1(-params.diameter / 2, 0, params.width / 2);

    // 使用尺寸构造盒子
    double dx = params.diameter;  // X方向长度
    double dy = params.thickness; // Y方向长度
    double dz = params.thickness; // Z方向长度

    TopoDS_Shape slot = BRepPrimAPI_MakeBox(slotPos1, dx, dy, dz).Shape();

    BRepAlgoAPI_Cut cutter(baseCylinder, slot);
    if (!cutter.IsDone()) {
      throw Standard_ConstructionError("Failed to create linear clamp");
    }
    return cutter.Shape();
  }
  case cable_clamp_type::CONTACT_TRIPLE: {
    // 品字接触式夹具 - 三个半圆槽
    double radius = params.diameter / 3;
    gp_Pnt center1(0, radius, params.width / 2);
    gp_Pnt center2(-radius * 0.866, -radius / 2, params.width / 2);
    gp_Pnt center3(radius * 0.866, -radius / 2, params.width / 2);

    TopoDS_Shape clamp = baseCylinder;
    for (const auto &center : {center1, center2, center3}) {
      gp_Ax2 slotAxis(center, gp_Dir(0, 0, 1));
      TopoDS_Shape slot =
          BRepPrimAPI_MakeCylinder(slotAxis, radius, params.thickness).Shape();
      BRepAlgoAPI_Cut cutter(clamp, slot);
      if (!cutter.IsDone()) {
        throw Standard_ConstructionError(
            "Failed to create contact triple clamp");
      }
      clamp = cutter.Shape();
    }
    return clamp;
  }
  case cable_clamp_type::SEPARATE_TRIPLE: {
    // 品字分离式夹具 - 三个独立夹持部分
    double radius = params.diameter / 3;
    gp_Pnt center1(0, radius, 0);
    gp_Pnt center2(-radius * 0.866, -radius / 2, 0);
    gp_Pnt center3(radius * 0.866, -radius / 2, 0);

    TopoDS_Compound result;
    BRep_Builder builder;
    builder.MakeCompound(result);

    for (const auto &center : {center1, center2, center3}) {
      gp_Ax2 clampAxis(center, gp_Dir(0, 0, 1));
      TopoDS_Shape clamp =
          BRepPrimAPI_MakeCylinder(clampAxis, radius, params.width).Shape();
      builder.Add(result, clamp);
    }
    return result;
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
    gp_Circ arc(gp_Ax2(gp_Pnt(0, 0, 0), gp::DZ()), params.radius);
    TopoDS_Edge path = BRepBuilderAPI_MakeEdge(arc, 0, params.arcAngle).Edge();
    TopoDS_Wire wire = BRepBuilderAPI_MakeWire(path).Wire();

    // 创建矩形截面
    gp_Pnt p1(0, -params.width / 2, 0);
    gp_Pnt p2(params.thickness, -params.width / 2, 0);
    gp_Pnt p3(params.thickness, params.width / 2, 0);
    gp_Pnt p4(0, params.width / 2, 0);
    TopoDS_Wire profile =
        BRepBuilderAPI_MakePolygon(p1, p2, p3, p4, Standard_True).Wire();

    // 扫掠成圆弧立柱
    BRepOffsetAPI_MakePipeShell pipeMaker(wire);
    pipeMaker.Add(BRepBuilderAPI_MakeFace(profile).Face());
    if (!pipeMaker.IsDone())
      throw Standard_ConstructionError("Failed to create arc pole");
    pole = pipeMaker.Shape();
  } else {
    // 直立柱
    gp_Pnt p1(0, -params.width / 2, 0);
    gp_Pnt p2(params.thickness, -params.width / 2, 0);
    gp_Pnt p3(params.thickness, params.width / 2, 0);
    gp_Pnt p4(0, params.width / 2, 0);
    TopoDS_Face face = BRepBuilderAPI_MakeFace(
        BRepBuilderAPI_MakePolygon(p1, p2, p3, p4, Standard_True).Wire());
    pole = BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, params.length)).Shape();
  }

  // 创建固定肢
  if (params.fixedLegLength > 0 && params.fixedLegWidth > 0) {
    gp_Pnt p1(params.thickness, -params.fixedLegWidth / 2, 0);
    gp_Pnt p2(params.thickness + params.fixedLegLength,
              -params.fixedLegWidth / 2, 0);
    gp_Pnt p3(params.thickness + params.fixedLegLength,
              params.fixedLegWidth / 2, 0);
    gp_Pnt p4(params.thickness, params.fixedLegWidth / 2, 0);
    TopoDS_Face legFace = BRepBuilderAPI_MakeFace(
        BRepBuilderAPI_MakePolygon(p1, p2, p3, p4, Standard_True).Wire());
    TopoDS_Shape leg =
        BRepPrimAPI_MakePrism(legFace, gp_Vec(0, 0, params.length)).Shape();
    pole = BRepAlgoAPI_Fuse(pole, leg).Shape();
  }

  // 创建安装孔
  for (const auto &point : params.mountPoints) {
    gp_Pnt holePos(point.X(), point.Y(), point.Z());
    TopoDS_Shape hole =
        BRepPrimAPI_MakeCylinder(gp_Ax2(holePos, gp::DX()), params.thickness,
                                 params.thickness * 2)
            .Shape();
    pole = BRepAlgoAPI_Cut(pole, hole).Shape();
  }

  return pole;
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

  // 创建主体部分（圆柱）
  gp_Ax2 mainAxis(gp_Pnt(0, 0, 0), gp::DZ());
  TopoDS_Shape mainPart =
      BRepPrimAPI_MakeCylinder(mainAxis, params.materialRadius, params.height)
          .Shape();

  // 创建水平延伸部分
  gp_Ax2 horizontalAxis(gp_Pnt(0, 0, params.height), gp::DX());
  TopoDS_Shape horizontalPart =
      BRepPrimAPI_MakeCylinder(horizontalAxis, params.materialRadius,
                               params.length)
          .Shape();
  mainPart = BRepAlgoAPI_Fuse(mainPart, horizontalPart).Shape();

  // 创建半圆钩部分
  gp_Pnt hookCenter(params.length, 0, params.height + params.radius);
  gp_Ax2 hookAxis(hookCenter, gp::DY());

  // 创建半圆路径
  gp_Circ hookCircle(hookAxis, params.radius);
  TopoDS_Edge hookEdge = BRepBuilderAPI_MakeEdge(hookCircle, 0, M_PI).Edge();
  TopoDS_Wire hookWire = BRepBuilderAPI_MakeWire(hookEdge).Wire();

  // 创建截面圆
  gp_Circ sectionCircle(gp_Ax2(gp::Origin(), gp::DX()), params.materialRadius);
  TopoDS_Edge sectionEdge = BRepBuilderAPI_MakeEdge(sectionCircle).Edge();

  // 扫掠成半圆钩
  BRepOffsetAPI_MakePipeShell pipeMaker(hookWire);
  pipeMaker.Add(sectionEdge);
  if (!pipeMaker.IsDone())
    throw Standard_ConstructionError("Failed to create hook part");

  TopoDS_Shape hookPart = pipeMaker.Shape();
  mainPart = BRepAlgoAPI_Fuse(mainPart, hookPart).Shape();

  // 创建下部延伸部分
  gp_Ax2 lowerAxis(gp_Pnt(0, 0, 0), gp::DY());
  TopoDS_Shape lowerPart =
      BRepPrimAPI_MakeCylinder(lowerAxis, params.materialRadius,
                               params.lowerLength)
          .Shape();
  mainPart = BRepAlgoAPI_Fuse(mainPart, lowerPart).Shape();

  return mainPart;
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
  if (params.thickness >= params.radius)
    throw Standard_ConstructionError("Thickness must be less than radius");

  // 创建U型路径
  gp_Pnt p1(0, 0, 0);
  gp_Pnt p2(0, params.height, 0);
  gp_Pnt p3(0, params.height, params.radius);
  gp_Pnt p4(0, params.height + params.radius, params.radius);
  gp_Pnt p5(0, params.height + params.radius, -params.radius);
  gp_Pnt p6(0, params.height, -params.radius);
  gp_Pnt p7(0, 0, -params.radius);

  // 创建U型线
  BRepBuilderAPI_MakeWire wireMaker;
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());

  // 创建圆弧部分
  gp_Circ arc1(gp_Ax2(p3, gp::DY()), params.radius);
  Handle(Geom_TrimmedCurve) arcSegment1 =
      GC_MakeArcOfCircle(arc1, p3, p4, Standard_True).Value();
  wireMaker.Add(BRepBuilderAPI_MakeEdge(arcSegment1).Edge());

  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p5).Edge());

  gp_Circ arc2(gp_Ax2(p6, gp::DY()), params.radius);
  Handle(Geom_TrimmedCurve) arcSegment2 =
      GC_MakeArcOfCircle(arc2, p5, p6, Standard_True).Value();
  wireMaker.Add(BRepBuilderAPI_MakeEdge(arcSegment2).Edge());

  wireMaker.Add(BRepBuilderAPI_MakeEdge(p6, p7).Edge());
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p1).Edge());

  TopoDS_Wire path = wireMaker.Wire();

  // 创建矩形截面
  gp_Pnt rectP1(0, -params.thickness / 2, 0);
  gp_Pnt rectP2(params.length, -params.thickness / 2, 0);
  gp_Pnt rectP3(params.length, params.thickness / 2, 0);
  gp_Pnt rectP4(0, params.thickness / 2, 0);
  TopoDS_Wire profile =
      BRepBuilderAPI_MakePolygon(rectP1, rectP2, rectP3, rectP4, Standard_True)
          .Wire();

  // 扫掠成U型拉环
  BRepOffsetAPI_MakePipeShell pipeMaker(path);
  pipeMaker.Add(BRepBuilderAPI_MakeFace(profile).Face());
  if (!pipeMaker.IsDone())
    throw Standard_ConstructionError("Failed to create U-shaped ring");

  return pipeMaker.Shape();
}

TopoDS_Shape create_u_shaped_ring(const u_shaped_ring_params &params,
                                  const gp_Pnt &position, const gp_Dir &normal,
                                  const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 创建标准方向的U型拉环
  TopoDS_Shape uRing = create_u_shaped_ring(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(uRing, transformation);
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
  gp_Ax2 armAxis(gp::Origin(), gp::DZ());
  TopoDS_Shape arm =
      BRepPrimAPI_MakeCylinder(armAxis, params.pipeDiameter / 2, params.height)
          .Shape();

  // 创建圆环部分
  gp_Ax2 ringAxis(gp_Pnt(0, 0, params.height), gp::DX());
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

TopoDS_Shape create_corner_well(const corner_well_params &params) {
  // 参数验证
  if (params.leftLength <= 0 || params.rightLength <= 0 || params.width <= 0 ||
      params.height <= 0) {
    throw Standard_ConstructionError(
        "Length, width and height must be positive");
  }
  if (params.topThickness <= 0 || params.bottomThickness <= 0 ||
      params.wallThickness <= 0) {
    throw Standard_ConstructionError("Thickness must be positive");
  }
  if (params.angle <= 0 || params.angle >= 180) {
    throw Standard_ConstructionError("Angle must be between 0 and 180 degrees");
  }
  if (params.cornerRadius <= 0) {
    throw Standard_ConstructionError("Corner radius must be positive");
  }

  // 将角度转换为弧度
  double angleRad = params.angle * M_PI / 180.0;

  // 创建井体主体
  // 1. 创建左段直井
  gp_Pnt leftStart(-params.leftLength, -params.width / 2, 0);
  TopoDS_Shape leftSection = BRepPrimAPI_MakeBox(leftStart, params.leftLength,
                                                 params.width, params.height)
                                 .Shape();

  // 2. 创建转角段
  gp_Ax2 cornerAxis(gp_Pnt(0, 0, 0), gp::DZ());
  TopoDS_Shape cornerSection =
      BRepPrimAPI_MakeCylinder(
          cornerAxis, params.cornerRadius + params.width / 2, params.height)
          .Shape();

  // 切割转角段为所需角度
  gp_Pln cutPlane1(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0));
  gp_Pln cutPlane2(gp_Pnt(0, 0, 0), gp_Dir(cos(angleRad), sin(angleRad), 0));

  // 使用正确的楔形参数
  TopoDS_Shape cornerCut =
      BRepPrimAPI_MakeWedge(params.cornerRadius + params.width, // dx
                            params.height,                      // dy
                            params.wallThickness, // dz - 使用wallThickness
                            angleRad // ltx - X方向的倾斜长度
                            )
          .Shape();
  cornerSection = BRepAlgoAPI_Common(cornerSection, cornerCut).Shape();

  // 3. 创建右段直井
  gp_Pnt rightStart(0, 0, 0);
  gp_Trsf rotation;
  rotation.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp::DZ()), angleRad);
  TopoDS_Shape rightSection =
      BRepPrimAPI_MakeBox(gp_Pnt(0, -params.width / 2, 0), params.rightLength,
                          params.width, params.height)
          .Shape();
  rightSection = BRepBuilderAPI_Transform(rightSection, rotation).Shape();

  // 合并三段井体
  TopoDS_Shape wellBody = BRepAlgoAPI_Fuse(leftSection, cornerSection).Shape();
  wellBody = BRepAlgoAPI_Fuse(wellBody, rightSection).Shape();

  // 创建内壁空腔
  double innerWidth = params.width - 2 * params.wallThickness;
  double innerHeight =
      params.height - params.topThickness - params.bottomThickness;

  // 1. 左段内腔
  gp_Pnt innerLeftStart(-params.leftLength + params.wallThickness,
                        -innerWidth / 2, params.bottomThickness);
  TopoDS_Shape innerLeft =
      BRepPrimAPI_MakeBox(innerLeftStart,
                          params.leftLength - params.wallThickness, innerWidth,
                          innerHeight)
          .Shape();

  // 2. 转角段内腔
  gp_Ax2 innerCornerAxis(gp_Pnt(0, 0, params.bottomThickness), gp::DZ());
  TopoDS_Shape innerCorner =
      BRepPrimAPI_MakeCylinder(
          innerCornerAxis, params.cornerRadius + innerWidth / 2, innerHeight)
          .Shape();
  innerCorner = BRepAlgoAPI_Common(innerCorner, cornerCut).Shape();

  // 3. 右段内腔
  TopoDS_Shape innerRight =
      BRepPrimAPI_MakeBox(
          gp_Pnt(params.wallThickness, -innerWidth / 2, params.bottomThickness),
          params.rightLength - params.wallThickness, innerWidth, innerHeight)
          .Shape();
  innerRight = BRepBuilderAPI_Transform(innerRight, rotation).Shape();

  // 合并内腔
  TopoDS_Shape innerSpace = BRepAlgoAPI_Fuse(innerLeft, innerCorner).Shape();
  innerSpace = BRepAlgoAPI_Fuse(innerSpace, innerRight).Shape();

  // 从井体中减去内腔
  wellBody = BRepAlgoAPI_Cut(wellBody, innerSpace).Shape();

  // 创建垫层
  if (params.cushionThickness > 0) {
    double cushionWidth = params.width + 2 * params.cushionExtension;
    double cushionLength = params.leftLength + params.rightLength +
                           params.cornerRadius * angleRad +
                           2 * params.cushionExtension;

    gp_Pnt cushionStart(-params.leftLength - params.cushionExtension,
                        -cushionWidth / 2, -params.cushionThickness);
    TopoDS_Shape cushion =
        BRepPrimAPI_MakeBox(cushionStart, cushionLength, cushionWidth,
                            params.cushionThickness)
            .Shape();

    // 合并垫层和井体
    wellBody = BRepAlgoAPI_Fuse(wellBody, cushion).Shape();
  }

  return wellBody;
}

TopoDS_Shape create_tunnel_well(const tunnel_well_params &params) {
  // 参数验证
  if (params.length <= 0 || params.width <= 0 || params.height <= 0) {
    throw Standard_ConstructionError("Well dimensions must be positive");
  }
  if (params.topThickness < 0 || params.bottomThickness < 0) {
    throw Standard_ConstructionError("Thickness must be non-negative");
  }

  // 创建井主体
  gp_Pnt origin(-params.length / 2, -params.width / 2, 0);
  TopoDS_Shape mainWell =
      BRepPrimAPI_MakeBox(origin, params.length, params.width, params.height)
          .Shape();

  // 创建顶板和底板
  if (params.topThickness > 0) {
    gp_Pnt topOrigin(-params.length / 2, -params.width / 2, params.height);
    TopoDS_Shape topPlate =
        BRepPrimAPI_MakeBox(topOrigin, params.length, params.width,
                            params.topThickness)
            .Shape();
    mainWell = BRepAlgoAPI_Fuse(mainWell, topPlate).Shape();
  }

  if (params.bottomThickness > 0) {
    gp_Pnt bottomOrigin(-params.length / 2, -params.width / 2,
                        -params.bottomThickness);
    TopoDS_Shape bottomPlate =
        BRepPrimAPI_MakeBox(bottomOrigin, params.length, params.width,
                            params.bottomThickness)
            .Shape();
    mainWell = BRepAlgoAPI_Fuse(mainWell, bottomPlate).Shape();
  }

  // 创建连接段
  auto createConnection = [](connection_section_style type, double length,
                             double width, double height, double archHeight) {
    switch (type) {
    case connection_section_style::HORSESHOE: {
      // 创建马蹄形连接段
      // 1. 创建底部矩形部分
      gp_Pnt rectOrigin(-length / 2, -width / 2, 0);
      TopoDS_Shape rectPart =
          BRepPrimAPI_MakeBox(rectOrigin, length, width, height - archHeight)
              .Shape();

      // 2. 创建顶部拱形部分
      gp_Pnt arcCenter(0, 0, height - archHeight);
      gp_Circ arcCircle(gp_Ax2(arcCenter, gp::DZ()), width / 2);
      TopoDS_Edge arcEdge =
          BRepBuilderAPI_MakeEdge(arcCircle, -M_PI / 2, M_PI / 2).Edge();

      // 3. 创建拱形截面
      BRepBuilderAPI_MakeWire arcWire;
      arcWire.Add(arcEdge);
      arcWire.Add(BRepBuilderAPI_MakeEdge(
                      gp_Pnt(-length / 2, width / 2, height - archHeight),
                      gp_Pnt(-length / 2, -width / 2, height - archHeight))
                      .Edge());
      arcWire.Add(BRepBuilderAPI_MakeEdge(
                      gp_Pnt(length / 2, -width / 2, height - archHeight),
                      gp_Pnt(length / 2, width / 2, height - archHeight))
                      .Edge());

      // 4. 拉伸成拱形实体
      TopoDS_Shape archPart =
          BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(arcWire.Wire()).Face(),
                                gp_Vec(0, 0, archHeight))
              .Shape();

      // 5. 合并矩形和拱形部分
      return BRepAlgoAPI_Fuse(rectPart, archPart).Shape();
    }
    case connection_section_style::CIRCULAR: {
      // 创建圆形连接段
      gp_Ax2 axis(gp_Pnt(0, 0, 0), gp::DZ());
      TopoDS_Shape cylinder =
          BRepPrimAPI_MakeCylinder(axis, height / 2, length).Shape();

      // 旋转90度使其与主井方向一致
      gp_Trsf rotation;
      rotation.SetRotation(gp_Ax1(gp::Origin(), gp::DY()), M_PI / 2);
      return BRepBuilderAPI_Transform(cylinder, rotation).Shape();
    }
    case connection_section_style::RECTANGULAR: {
      // 创建方形连接段
      gp_Pnt origin(-length / 2, -width / 2, 0);
      return BRepPrimAPI_MakeBox(origin, length, width, height).Shape();
    }
    default:
      throw Standard_ConstructionError("Invalid connection section type");
    }
  };

  // 创建左连接段
  if (params.leftLength > 0 && params.leftWidth > 0 && params.leftHeight > 0) {
    TopoDS_Shape leftConn = createConnection(
        params.leftSectionType, params.leftLength, params.leftWidth,
        params.leftHeight, params.leftArchHeight);
    gp_Pnt leftPos(-params.length / 2 - params.leftLength / 2, 0, 0);
    gp_Trsf leftTransform;
    leftTransform.SetTranslation(gp_Vec(leftPos.X(), leftPos.Y(), leftPos.Z()));
    leftConn = BRepBuilderAPI_Transform(leftConn, leftTransform).Shape();
    mainWell = BRepAlgoAPI_Fuse(mainWell, leftConn).Shape();
  }

  // 创建右连接段
  if (params.rightLength > 0 && params.rightWidth > 0 &&
      params.rightHeight > 0) {
    TopoDS_Shape rightConn = createConnection(
        params.rightSectionType, params.rightLength, params.rightWidth,
        params.rightHeight, params.rightArchHeight);
    gp_Pnt rightPos(params.length / 2 + params.rightLength / 2, 0, 0);
    gp_Trsf rightTransform;
    rightTransform.SetTranslation(
        gp_Vec(rightPos.X(), rightPos.Y(), rightPos.Z()));

    rightConn = BRepBuilderAPI_Transform(rightConn, rightTransform).Shape();
    mainWell = BRepAlgoAPI_Fuse(mainWell, rightConn).Shape();
  }

  // 创建垫层
  if (params.cushionThickness > 0) {
    double cushionLength = params.length + 2 * params.cushionExtension;
    double cushionWidth = params.width + 2 * params.cushionExtension;
    gp_Pnt cushionOrigin(-cushionLength / 2, -cushionWidth / 2,
                         -params.bottomThickness - params.cushionThickness);
    TopoDS_Shape cushion =
        BRepPrimAPI_MakeBox(cushionOrigin, cushionLength, cushionWidth,
                            params.cushionThickness)
            .Shape();
    mainWell = BRepAlgoAPI_Fuse(mainWell, cushion).Shape();
  }

  return mainWell;
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

  // 创建主井体
  gp_Pnt mainCorner(-params.length / 2, -params.width / 2, 0);
  TopoDS_Shape mainWell = BRepPrimAPI_MakeBox(mainCorner, params.length,
                                              params.width, params.height)
                              .Shape();

  // 根据不同类型添加特征
  switch (params.type) {
  case three_way_well_type::WORKING_WELL: {
    // 工作井特征 - 添加顶板和底板
    gp_Pnt topPlateCorner(-params.length / 2 - params.outerWallExtension,
                          -params.width / 2 - params.outerWallExtension,
                          params.height);
    TopoDS_Shape topPlate =
        BRepPrimAPI_MakeBox(
            topPlateCorner, params.length + 2 * params.outerWallExtension,
            params.width + 2 * params.outerWallExtension, params.topThickness)
            .Shape();

    gp_Pnt bottomPlateCorner(-params.length / 2 - params.outerWallExtension,
                             -params.width / 2 - params.outerWallExtension,
                             -params.bottomThickness);
    TopoDS_Shape bottomPlate =
        BRepPrimAPI_MakeBox(bottomPlateCorner,
                            params.length + 2 * params.outerWallExtension,
                            params.width + 2 * params.outerWallExtension,
                            params.bottomThickness)
            .Shape();

    mainWell = BRepAlgoAPI_Fuse(mainWell, topPlate).Shape();
    mainWell = BRepAlgoAPI_Fuse(mainWell, bottomPlate).Shape();
    break;
  }

  case three_way_well_type::OPEN_CUT_TUNNEL: {
    // 明挖隧道井特征 - 添加连接段
    if (params.leftSectionLength > 0 && params.leftSectionWidth > 0) {
      gp_Pnt leftSectionCorner(-params.length / 2 - params.leftSectionLength,
                               -params.leftSectionWidth / 2, 0);
      TopoDS_Shape leftSection;

      if (params.leftSectionStyle == connection_section_style::RECTANGULAR) {
        leftSection = BRepPrimAPI_MakeBox(
                          leftSectionCorner, params.leftSectionLength,
                          params.leftSectionWidth, params.leftSectionHeight)
                          .Shape();
      } else if (params.leftSectionStyle ==
                 connection_section_style::HORSESHOE) {
        // 1. 创建底部矩形部分
        gp_Pnt rectCorner = leftSectionCorner;
        TopoDS_Shape rectPart =
            BRepPrimAPI_MakeBox(
                rectCorner, params.leftSectionLength, params.leftSectionWidth,
                params.leftSectionHeight - params.leftSectionArchHeight)
                .Shape();

        // 2. 创建顶部拱形部分
        gp_Pnt arcCenter(leftSectionCorner.X() + params.leftSectionLength / 2,
                         leftSectionCorner.Y() + params.leftSectionWidth / 2,
                         leftSectionCorner.Z() + params.leftSectionHeight -
                             params.leftSectionArchHeight);

        // 创建拱形截面
        gp_Circ arcCircle(gp_Ax2(arcCenter, gp::DZ()),
                          params.leftSectionWidth / 2);
        TopoDS_Edge arcEdge =
            BRepBuilderAPI_MakeEdge(arcCircle, -M_PI / 2, M_PI / 2).Edge();

        // 创建拱形截面线
        BRepBuilderAPI_MakeWire arcWire;
        arcWire.Add(arcEdge);
        arcWire.Add(BRepBuilderAPI_MakeEdge(
                        gp_Pnt(leftSectionCorner.X(),
                               leftSectionCorner.Y() + params.leftSectionWidth,
                               arcCenter.Z()),
                        gp_Pnt(leftSectionCorner.X(), leftSectionCorner.Y(),
                               arcCenter.Z()))
                        .Edge());
        arcWire.Add(BRepBuilderAPI_MakeEdge(
                        gp_Pnt(leftSectionCorner.X() + params.leftSectionLength,
                               leftSectionCorner.Y(), arcCenter.Z()),
                        gp_Pnt(leftSectionCorner.X() + params.leftSectionLength,
                               leftSectionCorner.Y() + params.leftSectionWidth,
                               arcCenter.Z()))
                        .Edge());

        // 拉伸成拱形实体
        TopoDS_Shape archPart =
            BRepPrimAPI_MakePrism(
                BRepBuilderAPI_MakeFace(arcWire.Wire()).Face(),
                gp_Vec(0, 0, params.leftSectionArchHeight))
                .Shape();

        // 3. 合并矩形和拱形部分
        leftSection = BRepAlgoAPI_Fuse(rectPart, archPart).Shape();
      } else if (params.leftSectionStyle ==
                 connection_section_style::CIRCULAR) {
        // 创建圆形连接段
        gp_Ax2 leftAxis(leftSectionCorner, gp::DX());
        leftSection =
            BRepPrimAPI_MakeCylinder(leftAxis, params.leftSectionHeight,
                                     params.leftSectionLength)
                .Shape();
      }

      mainWell = BRepAlgoAPI_Fuse(mainWell, leftSection).Shape();
    }
    break;
  }

  case three_way_well_type::UNDERGROUND_TUNNEL: {
    // 暗挖隧道井特征 - 添加竖井
    if (params.shaftRadius > 0) {
      gp_Ax2 shaftAxis(gp_Pnt(0, 0, 0), gp::DZ());
      TopoDS_Shape shaft;

      if (params.shaftType == shaft_style::CIRCULAR) {
        shaft = BRepPrimAPI_MakeCylinder(shaftAxis, params.shaftRadius,
                                         params.height)
                    .Shape();
      } else {
        // 矩形竖井
        gp_Pnt shaftCorner(-params.shaftRadius, -params.shaftRadius, 0);
        shaft = BRepPrimAPI_MakeBox(shaftCorner, 2 * params.shaftRadius,
                                    2 * params.shaftRadius, params.height)
                    .Shape();
      }

      mainWell = BRepAlgoAPI_Fuse(mainWell, shaft).Shape();
    }
    break;
  }
  }

  // 添加支线井
  if (params.branchLength > 0 && params.branchWidth > 0) {
    gp_Pnt branchCorner;

    if (params.cornerType == corner_style::ROUNDED) {
      // 圆形转角
      branchCorner = gp_Pnt(params.length / 2 + params.cornerRadius,
                            -params.branchWidth / 2, 0);
    } else {
      // 折角形转角
      branchCorner = gp_Pnt(params.length / 2 + params.cornerLength,
                            -params.branchWidth / 2, 0);
    }

    TopoDS_Shape branchWell =
        BRepPrimAPI_MakeBox(branchCorner, params.branchLength,
                            params.branchWidth, params.height)
            .Shape();

    mainWell = BRepAlgoAPI_Fuse(mainWell, branchWell).Shape();
  }

  // 如果是双拼井，添加第二个井
  if (params.isDoubleShaft && params.doubleShaftSpacing > 0) {
    // 创建第二个井的变换
    gp_Trsf secondShaftTransform;
    secondShaftTransform.SetTranslation(
        gp_Vec(params.doubleShaftSpacing, 0, 0));

    // 复制并平移第一个井
    BRepBuilderAPI_Transform secondShaftMaker(mainWell, secondShaftTransform);
    TopoDS_Shape secondShaft = secondShaftMaker.Shape();

    // 创建连接两个井的连接段
    double connectorLength = params.doubleShaftSpacing - params.width;
    if (connectorLength > 0) {
      gp_Pnt connectorOrigin(params.width / 2, -params.width / 2, 0);
      TopoDS_Shape connector =
          BRepPrimAPI_MakeBox(connectorOrigin, connectorLength, params.width,
                              params.height)
              .Shape();

      // 合并所有部件
      mainWell = BRepAlgoAPI_Fuse(mainWell, secondShaft).Shape();
      mainWell = BRepAlgoAPI_Fuse(mainWell, connector).Shape();
    } else {
      // 如果间距不足，直接合并两个井
      mainWell = BRepAlgoAPI_Fuse(mainWell, secondShaft).Shape();
    }
  }

  return mainWell;
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

TopoDS_Shape create_four_way_well(const four_way_well_params &params) {
  // 参数验证
  if (params.length <= 0 || params.width <= 0 || params.height <= 0) {
    throw Standard_ConstructionError(
        "Length, width and height must be positive");
  }

  // 创建主井体
  gp_Pnt origin(-params.length / 2, -params.width / 2, 0);
  BRepPrimAPI_MakeBox mainBox(origin, params.length, params.width,
                              params.height);
  TopoDS_Shape junction = mainBox.Shape();

  // 创建顶板
  if (params.roofThickness > 0) {
    BRepPrimAPI_MakeBox roofMaker(
        gp_Pnt(-params.length / 2, -params.width / 2, params.height),
        params.length, params.width, params.roofThickness);
    junction = BRepAlgoAPI_Fuse(junction, roofMaker.Shape()).Shape();
  }

  // 创建底板
  if (params.floorThickness > 0) {
    BRepPrimAPI_MakeBox floorMaker(
        gp_Pnt(-params.length / 2, -params.width / 2, -params.floorThickness),
        params.length, params.width, params.floorThickness);
    junction = BRepAlgoAPI_Fuse(junction, floorMaker.Shape()).Shape();
  }

  // 创建连接段
  auto createSection = [](const auto &section) -> TopoDS_Shape {
    if (section.length <= 0 || section.width <= 0 || section.height <= 0) {
      throw Standard_ConstructionError("连接段尺寸必须为正数");
    }

    switch (section.sectionType) {
    case junction_section_type::RECTANGULAR:
      return BRepPrimAPI_MakeBox(
                 gp_Pnt(-section.length / 2, -section.width / 2, 0),
                 section.length, section.width, section.height)
          .Shape();

    case junction_section_type::CIRCULAR: {
      if (section.height <= 0) {
        throw Standard_ConstructionError("圆形连接段半径必须为正数");
      }
      return BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp::DZ()),
                                      section.height, section.length)
          .Shape();
    }

    case junction_section_type::HORSESHOE: {
      if (section.archHeight <= 0) {
        throw Standard_ConstructionError("马蹄形连接段拱高必须为正数");
      }

      // 1. 创建底部矩形部分
      TopoDS_Shape rect =
          BRepPrimAPI_MakeBox(
              gp_Pnt(-section.length / 2, -section.width / 2, 0),
              section.length, section.width,
              section.height - section.archHeight)
              .Shape();

      // 2. 创建顶部拱形部分
      gp_Pnt arcCenter(0, 0, section.height - section.archHeight);
      gp_Circ arcCircle(gp_Ax2(arcCenter, gp::DY()), section.width / 2);

      // 创建拱形截面线
      BRepBuilderAPI_MakeWire arcWire;
      arcWire.Add(BRepBuilderAPI_MakeEdge(
                      gp_Pnt(-section.length / 2, -section.width / 2,
                             section.height - section.archHeight),
                      gp_Pnt(-section.length / 2, section.width / 2,
                             section.height - section.archHeight))
                      .Edge());
      arcWire.Add(BRepBuilderAPI_MakeEdge(
                      gp_Circ(gp_Ax2(arcCenter, gp::DY()), section.width / 2),
                      -M_PI / 2, M_PI / 2)
                      .Edge());
      arcWire.Add(
          BRepBuilderAPI_MakeEdge(gp_Pnt(section.length / 2, section.width / 2,
                                         section.height - section.archHeight),
                                  gp_Pnt(section.length / 2, -section.width / 2,
                                         section.height - section.archHeight))
              .Edge());

      // 拉伸成拱形实体
      TopoDS_Shape arch =
          BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(arcWire.Wire()).Face(),
                                gp_Vec(0, 0, section.archHeight))
              .Shape();

      // 3. 合并矩形和拱形部分
      return BRepAlgoAPI_Fuse(rect, arch).Shape();
    }

    default:
      throw Standard_ConstructionError("无效的连接段类型");
    }
  };

  // 左侧连接段
  if (params.leftSection.length > 0) {
    TopoDS_Shape leftSection = createSection(params.leftSection);
    gp_Trsf leftTransform;
    leftTransform.SetTranslation(
        gp_Vec(-params.length / 2 - params.leftSection.length / 2, 0, 0));
    BRepBuilderAPI_Transform leftTransformMaker(leftSection, leftTransform);
    junction = BRepAlgoAPI_Fuse(junction, leftTransformMaker.Shape()).Shape();
  }

  // 右侧连接段
  if (params.rightSection.length > 0) {
    TopoDS_Shape rightSection = createSection(params.rightSection);
    gp_Trsf rightTransform;
    rightTransform.SetTranslation(
        gp_Vec(params.length / 2 + params.rightSection.length / 2, 0, 0));
    BRepBuilderAPI_Transform rightTransformMaker(rightSection, rightTransform);
    junction = BRepAlgoAPI_Fuse(junction, rightTransformMaker.Shape()).Shape();
  }

  // 支线连接段1
  if (params.branchSection1.length > 0) {
    TopoDS_Shape branchSection1 = createSection(params.branchSection1);
    gp_Trsf branch1Transform;
    branch1Transform.SetTranslation(
        gp_Vec(0, params.width / 2 + params.branchSection1.width / 2, 0));
    BRepBuilderAPI_Transform branch1TransformMaker(branchSection1,
                                                   branch1Transform);
    junction =
        BRepAlgoAPI_Fuse(junction, branch1TransformMaker.Shape()).Shape();
  }

  // 支线连接段2
  if (params.branchSection2.length > 0) {
    TopoDS_Shape branchSection2 = createSection(params.branchSection2);
    gp_Trsf branch2Transform;
    branch2Transform.SetTranslation(
        gp_Vec(0, -params.width / 2 - params.branchSection2.width / 2, 0));
    BRepBuilderAPI_Transform branch2TransformMaker(branchSection2,
                                                   branch2Transform);
    junction =
        BRepAlgoAPI_Fuse(junction, branch2TransformMaker.Shape()).Shape();
  }

  // 创建转角
  if (params.cornerStyle == 1 && params.cornerRadius > 0) {
    // 圆形转角
    TopoDS_Shape corner =
        BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp::DZ()),
                                 params.cornerRadius, params.height)
            .Shape();
    junction = BRepAlgoAPI_Fuse(junction, corner).Shape();
  } else if (params.cornerStyle == 2 && params.cornerLength > 0 &&
             params.cornerWidth > 0) {
    // 折角形转角
    TopoDS_Shape corner =
        BRepPrimAPI_MakeBox(
            gp_Pnt(-params.cornerLength / 2, -params.cornerWidth / 2, 0),
            params.cornerLength, params.cornerWidth, params.height)
            .Shape();
    junction = BRepAlgoAPI_Fuse(junction, corner).Shape();
  }

  // 创建垫层
  if (params.cushionThickness > 0) {
    double cushionLength = params.length + 2 * params.cushionExtension;
    double cushionWidth = params.width + 2 * params.cushionExtension;
    BRepPrimAPI_MakeBox cushionMaker(
        gp_Pnt(-cushionLength / 2, -cushionWidth / 2,
               -params.floorThickness - params.cushionThickness),
        cushionLength, cushionWidth, params.cushionThickness);
    junction = BRepAlgoAPI_Fuse(junction, cushionMaker.Shape()).Shape();
  }

  return junction;
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

TopoDS_Shape create_pipe_row(const pipe_row_params &params) {
  // 参数验证
  if (params.pipeType != 1 && params.pipeType != 2) {
    throw Standard_ConstructionError(
        "Pipe type must be 1 (normal) or 2 (pull)");
  }

  if (params.pipeType == 1) {
    if (params.pipePositions.empty()) {
      throw Standard_ConstructionError("Normal pipe must have positions");
    }
    if (params.pipePositions.size() != params.pipeInnerDiameters.size() ||
        params.pipePositions.size() != params.pipeWallThicknesses.size()) {
      throw Standard_ConstructionError("Pipe parameters count mismatch");
    }
  } else {
    if (params.pullPipeInnerDiameter <= 0 || params.pullPipeThickness <= 0) {
      throw Standard_ConstructionError("Pull pipe dimensions must be positive");
    }
  }

  if (params.points.size() < 2) {
    throw Standard_ConstructionError("At least 2 points are required");
  }

  // 创建路径线
  BRepBuilderAPI_MakePolygon pathMaker;
  for (size_t i = 0; i < params.points.size(); ++i) {
    const auto &point = params.points[i];
    if (point.type == 1 && (i == 0 || i == params.points.size() - 1)) {
      throw Standard_ConstructionError(
          "First and last points cannot be arc points");
    }
    pathMaker.Add(point.position);
  }
  TopoDS_Wire pathWire = pathMaker.Wire();

  // 创建截面轮廓
  TopoDS_Shape section;
  if (params.pipeType == 1) {
    // 普通排管截面
    for (size_t i = 0; i < params.pipePositions.size(); ++i) {
      double outerRadius =
          params.pipeInnerDiameters[i] / 2 + params.pipeWallThicknesses[i];
      gp_Pnt center(params.pipePositions[i].X(), params.pipePositions[i].Y(),
                    0);

      TopoDS_Shape pipe =
          BRepPrimAPI_MakeCylinder(gp_Ax2(center, gp::DZ()), outerRadius,
                                   params.pipeInnerDiameters[i] / 2)
              .Shape();

      if (section.IsNull()) {
        section = pipe;
      } else {
        section = BRepAlgoAPI_Fuse(section, pipe).Shape();
      }
    }
  } else {
    // 拉管截面
    double outerRadius =
        params.pullPipeInnerDiameter / 2 + params.pullPipeThickness;
    section =
        BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DZ()), outerRadius,
                                 params.pullPipeInnerDiameter / 2)
            .Shape();
  }

  // 沿路径扫掠
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.Add(section);
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create pipe row");
  }

  TopoDS_Shape pipes = pipeMaker.Shape();

  // 创建包封
  if (params.hasEnclosure) {
    gp_Pnt enclosureCorner(-params.enclosureWidth / 2,
                           -params.enclosureHeight / 2, 0);
    TopoDS_Shape enclosure =
        BRepPrimAPI_MakeBox(enclosureCorner, params.enclosureWidth,
                            params.enclosureHeight, 1000)
            .Shape();

    pipes = BRepAlgoAPI_Fuse(pipes, enclosure).Shape();
  }

  // 创建底板
  if (params.baseThickness > 0) {
    double baseWidth = params.enclosureWidth + 2 * params.baseExtension;
    double baseHeight = params.enclosureHeight + 2 * params.baseExtension;
    gp_Pnt baseCorner(-baseWidth / 2, -baseHeight / 2, -params.baseThickness);
    TopoDS_Shape base = BRepPrimAPI_MakeBox(baseCorner, baseWidth, baseHeight,
                                            params.baseThickness)
                            .Shape();

    pipes = BRepAlgoAPI_Fuse(pipes, base).Shape();
  }

  // 创建垫层
  if (params.cushionThickness > 0) {
    double cushionWidth = params.enclosureWidth + 2 * params.baseExtension +
                          2 * params.cushionExtension;
    double cushionHeight = params.enclosureHeight + 2 * params.baseExtension +
                           2 * params.cushionExtension;
    gp_Pnt cushionCorner(-cushionWidth / 2, -cushionHeight / 2,
                         -params.baseThickness - params.cushionThickness);
    TopoDS_Shape cushion =
        BRepPrimAPI_MakeBox(cushionCorner, cushionWidth, cushionHeight,
                            params.cushionThickness)
            .Shape();

    pipes = BRepAlgoAPI_Fuse(pipes, cushion).Shape();
  }

  return pipes;
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

  // 创建路径线
  BRepBuilderAPI_MakePolygon pathMaker;
  for (size_t i = 0; i < params.points.size(); ++i) {
    const auto &point = params.points[i];
    if (point.type == 1 && (i == 0 || i == params.points.size() - 1)) {
      throw Standard_ConstructionError(
          "First and last points cannot be arc points");
    }
    pathMaker.Add(point.position);
  }
  TopoDS_Wire pathWire = pathMaker.Wire();

  // 创建垫层
  double cushionWidth =
      params.width + 2 * params.wallThickness + 2 * params.cushionExtension;
  double cushionLength = params.width * 2; // 假设长度为宽度的2倍
  TopoDS_Shape cushion;
  if (params.cushionThickness > 0) {
    cushion = BRepPrimAPI_MakeBox(gp_Pnt(-cushionWidth / 2, -cushionLength / 2,
                                         -params.cushionThickness),
                                  cushionWidth, cushionLength,
                                  params.cushionThickness)
                  .Shape();
  }

  // 创建底板
  double baseWidth =
      params.width + 2 * params.wallThickness + 2 * params.baseExtension;
  TopoDS_Shape base;
  if (params.baseThickness > 0) {
    base = BRepPrimAPI_MakeBox(gp_Pnt(-baseWidth / 2, -cushionLength / 2, 0),
                               baseWidth, cushionLength, params.baseThickness)
               .Shape();
    if (!cushion.IsNull()) {
      base = BRepAlgoAPI_Fuse(base, cushion).Shape();
    }
  } else if (!cushion.IsNull()) {
    base = cushion;
  }

  // 创建侧壁
  TopoDS_Shape walls;
  if (params.wallThickness > 0) {
    // 左侧壁
    TopoDS_Shape leftWall =
        BRepPrimAPI_MakeBox(gp_Pnt(-params.width / 2 - params.wallThickness,
                                   -cushionLength / 2, params.baseThickness),
                            params.wallThickness, cushionLength, params.height)
            .Shape();

    // 右侧壁
    TopoDS_Shape rightWall =
        BRepPrimAPI_MakeBox(
            gp_Pnt(params.width / 2, -cushionLength / 2, params.baseThickness),
            params.wallThickness, cushionLength, params.height)
            .Shape();

    walls = BRepAlgoAPI_Fuse(leftWall, rightWall).Shape();

    // 如果有第二层壁厚
    if (params.wallThickness2 > 0) {
      TopoDS_Shape leftWall2 =
          BRepPrimAPI_MakeBox(gp_Pnt(-params.width / 2 - params.wallThickness -
                                         params.wallThickness2,
                                     -cushionLength / 2, params.baseThickness),
                              params.wallThickness2, cushionLength,
                              params.height)
              .Shape();

      TopoDS_Shape rightWall2 =
          BRepPrimAPI_MakeBox(gp_Pnt(params.width / 2 + params.wallThickness,
                                     -cushionLength / 2, params.baseThickness),
                              params.wallThickness2, cushionLength,
                              params.height)
              .Shape();

      walls = BRepAlgoAPI_Fuse(walls, leftWall2).Shape();
      walls = BRepAlgoAPI_Fuse(walls, rightWall2).Shape();
    }

    if (!base.IsNull()) {
      walls = BRepAlgoAPI_Fuse(walls, base).Shape();
    }
  }

  // 创建盖板
  TopoDS_Shape cover;
  if (params.coverThickness > 0) {
    double coverWidth = params.coverWidth > 0
                            ? params.coverWidth
                            : params.width + 2 * params.wallThickness;
    cover =
        BRepPrimAPI_MakeBox(gp_Pnt(-coverWidth / 2, -cushionLength / 2,
                                   params.baseThickness + params.height),
                            coverWidth, cushionLength, params.coverThickness)
            .Shape();

    if (!walls.IsNull()) {
      cover = BRepAlgoAPI_Fuse(cover, walls).Shape();
    } else if (!base.IsNull()) {
      cover = BRepAlgoAPI_Fuse(cover, base).Shape();
    }
  }

  // 返回最终形状
  if (!cover.IsNull()) {
    return cover;
  } else if (!walls.IsNull()) {
    return walls;
  } else if (!base.IsNull()) {
    return base;
  } else {
    return TopoDS_Shape(); // 返回空形状
  }
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

  // 创建路径线
  BRepBuilderAPI_MakePolygon pathMaker;
  for (size_t i = 0; i < params.points.size(); ++i) {
    const auto &point = params.points[i];
    if (point.type == 1 && (i == 0 || i == params.points.size() - 1)) {
      throw Standard_ConstructionError(
          "First and last points cannot be arc points");
    }
    pathMaker.Add(point.position);
  }
  TopoDS_Wire pathWire = pathMaker.Wire();

  // 创建隧道截面轮廓
  TopoDS_Wire sectionWire;
  switch (params.style) {
  case tunnel_section_style::RECTANGULAR: {
    // 矩形截面
    gp_Pnt p1(0, -params.width / 2, 0);
    gp_Pnt p2(0, params.width / 2, 0);
    gp_Pnt p3(0, params.width / 2, params.height);
    gp_Pnt p4(0, -params.width / 2, params.height);
    sectionWire = BRepBuilderAPI_MakePolygon(p1, p2, p3, p4, true).Wire();
    break;
  }
  case tunnel_section_style::HORSESHOE: {
    // 马蹄形截面
    double radius = params.width / 2;
    gp_Pnt center(0, 0, radius);

    // 创建半圆
    Handle(Geom_Circle) circle =
        new Geom_Circle(gp_Ax2(center, gp::DX(), gp::DZ()), radius);
    TopoDS_Edge arcEdge = BRepBuilderAPI_MakeEdge(circle, 0, M_PI).Edge();

    // 创建直线段
    gp_Pnt p1(0, -radius, 0);
    gp_Pnt p2(0, -radius, params.height - radius);
    gp_Pnt p3(0, radius, params.height - radius);
    gp_Pnt p4(0, radius, 0);

    TopoDS_Wire wire =
        BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(p1, p2).Edge(),
                                BRepBuilderAPI_MakeEdge(p2, p3).Edge(),
                                BRepBuilderAPI_MakeEdge(p3, p4).Edge(), arcEdge)
            .Wire();
    sectionWire = wire;
    break;
  }
  case tunnel_section_style::CIRCULAR: {
    // 圆形截面
    gp_Pnt center(0, 0, 0);
    Handle(Geom_Circle) circle =
        new Geom_Circle(gp_Ax2(center, gp::DX(), gp::DZ()), params.width / 2);
    TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(circle).Edge();
    sectionWire = BRepBuilderAPI_MakeWire(edge).Wire();
    break;
  }
  default:
    throw Standard_ConstructionError("Invalid tunnel section style");
  }

  // 沿路径扫掠创建隧道主体
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.Add(sectionWire);
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create cable tunnel");
  }
  TopoDS_Shape tunnel = pipeMaker.Shape();

  // 创建垫层
  if (params.cushionThickness > 0) {
    double cushionWidth = params.width + 2 * params.cushionExtension;
    double cushionHeight = params.height + 2 * params.cushionExtension;

    // 创建垫层路径
    BRepOffsetAPI_MakePipeShell cushionPipeMaker(pathWire);
    gp_Pnt cp1(0, -cushionWidth / 2, -params.cushionThickness);
    gp_Pnt cp2(0, cushionWidth / 2, -params.cushionThickness);
    gp_Pnt cp3(0, cushionWidth / 2, 0);
    gp_Pnt cp4(0, -cushionWidth / 2, 0);
    TopoDS_Wire cushionSection =
        BRepBuilderAPI_MakePolygon(cp1, cp2, cp3, cp4, true).Wire();
    cushionPipeMaker.Add(cushionSection);
    cushionPipeMaker.Build();

    if (cushionPipeMaker.IsDone()) {
      tunnel = BRepAlgoAPI_Fuse(tunnel, cushionPipeMaker.Shape()).Shape();
    }
  }

  return tunnel;
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

  // 创建路径线
  BRepBuilderAPI_MakePolygon pathMaker;
  for (size_t i = 0; i < params.points.size(); ++i) {
    const auto &point = params.points[i];
    if (point.type == 1 && (i == 0 || i == params.points.size() - 1)) {
      throw Standard_ConstructionError(
          "First and last points cannot be arc points");
    }
    pathMaker.Add(point.position);
  }
  TopoDS_Wire pathWire = pathMaker.Wire();

  // 创建桥架截面轮廓
  TopoDS_Wire sectionWire;
  switch (params.style) {
  case cable_tray_style::ARCH: {
    // 拱形桥架截面
    gp_Pnt p1(0, -params.width / 2, 0);
    gp_Pnt p2(0, params.width / 2, 0);
    gp_Pnt p3(0, params.width / 2, params.height - params.archHeight);

    // 创建拱形顶部
    gp_Pnt arcCenter(0, 0, params.height - params.archHeight);
    Handle(Geom_Circle) arc =
        new Geom_Circle(gp_Ax2(arcCenter, gp::DX()), params.width / 2);
    TopoDS_Edge arcEdge =
        BRepBuilderAPI_MakeEdge(arc, -M_PI / 2, M_PI / 2).Edge();

    gp_Pnt p4(0, -params.width / 2, params.height - params.archHeight);
    sectionWire =
        BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(p1, p2).Edge(),
                                BRepBuilderAPI_MakeEdge(p2, p3).Edge(), arcEdge,
                                BRepBuilderAPI_MakeEdge(p4, p1).Edge())
            .Wire();
    break;
  }
  case cable_tray_style::BEAM: {
    // 平形桥架截面
    gp_Pnt p1(0, -params.width / 2, 0);
    gp_Pnt p2(0, params.width / 2, 0);
    gp_Pnt p3(0, params.width / 2, params.height);
    gp_Pnt p4(0, -params.width / 2, params.height);
    sectionWire = BRepBuilderAPI_MakePolygon(p1, p2, p3, p4, true).Wire();
    break;
  }
  default:
    throw Standard_ConstructionError("Invalid cable tray style");
  }

  // 沿路径扫掠创建桥架主体
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.Add(sectionWire);
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create cable tray");
  }
  TopoDS_Shape tray = pipeMaker.Shape();

  // 创建排管
  if (params.pipeCount > 0) {
    for (int i = 0; i < params.pipeCount; ++i) {
      double outerRadius =
          params.pipeInnerDiameters[i] / 2 + params.pipeWallThicknesses[i];
      gp_Pnt center(params.pipePositions[i].X(), params.pipePositions[i].Y(),
                    0);

      TopoDS_Shape pipe =
          BRepPrimAPI_MakeCylinder(gp_Ax2(center, gp::DZ()), outerRadius,
                                   params.pipeInnerDiameters[i] / 2)
              .Shape();

      tray = BRepAlgoAPI_Fuse(tray, pipe).Shape();
    }
  }

  // 创建桥柱
  if (params.columnDiameter > 0 && params.columnHeight > 0) {
    for (const auto &point : params.points) {
      gp_Pnt columnBase(point.position.X(), point.position.Y(),
                        -params.columnHeight);
      TopoDS_Shape column = BRepPrimAPI_MakeCylinder(
                                gp_Ax2(columnBase, gp::DZ()),
                                params.columnDiameter / 2, params.columnHeight)
                                .Shape();

      tray = BRepAlgoAPI_Fuse(tray, column).Shape();
    }
  }

  return tray;
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

  // 创建L型梁的主体部分
  gp_Pnt p1(0, 0, 0);
  gp_Pnt p2(params.length, 0, 0);
  gp_Pnt p3(params.length, params.width, 0);
  gp_Pnt p4(params.width, params.width, 0);
  gp_Pnt p5(params.width, params.height, 0);
  gp_Pnt p6(0, params.height, 0);

  // 创建多边形轮廓
  BRepBuilderAPI_MakePolygon polyMaker;
  polyMaker.Add(p1);
  polyMaker.Add(p2);
  polyMaker.Add(p3);
  polyMaker.Add(p4);
  polyMaker.Add(p5);
  polyMaker.Add(p6);
  polyMaker.Add(p1);
  TopoDS_Wire wire = polyMaker.Wire();

  // 拉伸成实体
  TopoDS_Shape LBeam =
      BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(wire).Face(),
                            gp_Vec(0, 0, params.height))
          .Shape();

  return LBeam;
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
          BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, -1), gp::DZ()),
                                   innerRadius, params.height + 2)
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
      BRepPrimAPI_MakeBox(gp_Pnt(-params.width / 2, 0, 0), params.width,
                          params.length, params.thickness)
          .Shape();

  // 创建横档
  double stepWidth = params.width * 0.8;
  double stepThickness = params.thickness * 1.5;
  double stepSpacing = params.length / 10; // 假设10级横档

  TopoDS_Shape steps;
  for (double z = stepSpacing; z < params.length; z += stepSpacing) {
    TopoDS_Shape step =
        BRepPrimAPI_MakeBox(
            gp_Pnt(-stepWidth / 2, z - stepThickness / 2, -params.thickness),
            stepWidth, stepThickness, params.thickness * 3)
            .Shape();

    if (steps.IsNull()) {
      steps = step;
    } else {
      steps = BRepAlgoAPI_Fuse(steps, step).Shape();
    }
  }

  // 合并主体和横档
  if (!steps.IsNull()) {
    ladder = BRepAlgoAPI_Fuse(ladder, steps).Shape();
  }

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
  if (params.floorThickness < 0) {
    throw Standard_ConstructionError("Floor thickness must be non-negative");
  }

  // 创建集水坑主体（长方体）
  gp_Pnt origin(-params.length / 2, -params.width / 2, -params.floorThickness);
  BRepPrimAPI_MakeBox pitMaker(origin, params.length, params.width,
                               params.depth + params.floorThickness);
  TopoDS_Shape pit = pitMaker.Shape();

  // 创建内部空腔（如果底板厚度大于0）
  if (params.floorThickness > 0) {
    gp_Pnt innerOrigin(-params.length / 2 + 1, -params.width / 2 + 1,
                       -params.floorThickness + 1);
    BRepPrimAPI_MakeBox cavityMaker(innerOrigin, params.length - 2,
                                    params.width - 2, params.depth - 1);
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

  // 创建步道主体（长方体）
  gp_Pnt origin(-params.width / 2, -params.width / 2, 0); // 底面中心在原点
  BRepPrimAPI_MakeBox footpathMaker(origin, params.width, params.width,
                                    params.height);

  return footpathMaker.Shape();
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
      params.innerWallThickness < 0 || params.roofThickness < 0) {
    throw Standard_ConstructionError("Thickness values must be non-negative");
  }

  // 创建支护结构（外圆柱）
  gp_Ax2 supportAxis(gp::Origin(), gp::DZ());
  TopoDS_Shape support;
  if (params.supportWallThickness > 0 && params.supportHeight > 0) {
    support = BRepPrimAPI_MakeCylinder(supportAxis, params.supportDiameter / 2,
                                       params.supportHeight)
                  .Shape();
  }

  // 创建工作仓外壁
  TopoDS_Shape outerWall;
  if (params.outerWallThickness > 0) {
    double outerRadius = params.innerDiameter / 2 + params.innerWallThickness;
    outerWall =
        BRepPrimAPI_MakeCylinder(supportAxis, outerRadius, params.workingHeight)
            .Shape();

    if (params.innerWallThickness > 0) {
      // 创建内壁空腔
      TopoDS_Shape innerCavity =
          BRepPrimAPI_MakeCylinder(supportAxis, params.innerDiameter / 2,
                                   params.workingHeight)
              .Shape();
      outerWall = BRepAlgoAPI_Cut(outerWall, innerCavity).Shape();
    }

    if (!support.IsNull()) {
      outerWall = BRepAlgoAPI_Fuse(outerWall, support).Shape();
    }
  }

  // 创建顶板
  TopoDS_Shape roof;
  if (params.roofThickness > 0) {
    double roofRadius = params.supportDiameter / 2;
    roof = BRepPrimAPI_MakeCylinder(
               gp_Ax2(gp_Pnt(0, 0, params.workingHeight), gp::DZ()), roofRadius,
               params.roofThickness)
               .Shape();

    if (!outerWall.IsNull()) {
      roof = BRepAlgoAPI_Fuse(roof, outerWall).Shape();
    } else if (!support.IsNull()) {
      roof = BRepAlgoAPI_Fuse(roof, support).Shape();
    }
  }

  // 返回最终形状
  if (!roof.IsNull()) {
    return roof;
  } else if (!outerWall.IsNull()) {
    return outerWall;
  } else if (!support.IsNull()) {
    return support;
  } else {
    return TopoDS_Shape(); // 返回空形状
  }
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
    gp_Pnt center(params.holePositions[i].X(), params.holePositions[i].Y(),
                  params.thickness / 2);

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
  gp_Pnt baseOrigin(-params.bottomLength / 2, -params.bottomWidth / 2, 0);
  TopoDS_Shape base = BRepPrimAPI_MakeBox(baseOrigin, params.bottomLength,
                                          params.bottomWidth, params.baseHeight)
                          .Shape();

  // 创建主体
  gp_Pnt bodyOrigin(-params.middleLength / 2, -params.middleWidth / 2,
                    params.baseHeight);
  TopoDS_Shape body =
      BRepPrimAPI_MakeBox(bodyOrigin, params.middleLength, params.middleWidth,
                          params.height - params.baseHeight - params.topHeight)
          .Shape();
  body = BRepAlgoAPI_Fuse(base, body).Shape();

  // 创建屋顶
  gp_Pnt roofOrigin(-params.topLength / 2, -params.topWidth / 2,
                    params.height - params.topHeight);
  TopoDS_Shape roof = BRepPrimAPI_MakeBox(roofOrigin, params.topLength,
                                          params.topWidth, params.topHeight)
                          .Shape();

  // 组合所有部件
  TopoDS_Shape pavilion = BRepAlgoAPI_Fuse(body, roof).Shape();

  // 添加通风格栅（长条洞）
  double grilleWidth = params.middleWidth * 0.8; // 格栅宽度
  double grilleHeight =
      (params.height - params.baseHeight - params.topHeight) * 0.6; // 格栅高度
  double grilleThickness = params.middleLength * 0.05; // 格栅厚度

  // 四个方向的格栅
  for (int i = 0; i < 4; ++i) {
    double angle = i * M_PI_2; // 0, 90, 180, 270度

    // 创建格栅板
    gp_Pnt grilleCenter(
        (params.middleLength / 2 - grilleThickness / 2) * cos(angle),
        (params.middleWidth / 2 - grilleThickness / 2) * sin(angle),
        params.baseHeight +
            (params.height - params.baseHeight - params.topHeight) / 2);

    TopoDS_Shape grille =
        BRepPrimAPI_MakeBox(gp_Pnt(grilleCenter.X() - grilleThickness / 2,
                                   grilleCenter.Y() - grilleWidth / 2,
                                   grilleCenter.Z() - grilleHeight / 2),
                            grilleThickness, grilleWidth, grilleHeight)
            .Shape();

    // 创建格栅孔洞
    int holeCount = 5; // 每面格栅孔洞数量
    for (int j = 0; j < holeCount; ++j) {
      double holePos = -grilleWidth / 2 + (j + 0.5) * (grilleWidth / holeCount);
      TopoDS_Shape hole =
          BRepPrimAPI_MakeBox(gp_Pnt(grilleCenter.X() - grilleThickness,
                                     holePos - grilleWidth / holeCount * 0.4,
                                     grilleCenter.Z() - grilleHeight * 0.4),
                              grilleThickness * 2,
                              grilleWidth / holeCount * 0.8, grilleHeight * 0.8)
              .Shape();
      grille = BRepAlgoAPI_Cut(grille, hole).Shape();
    }

    pavilion = BRepAlgoAPI_Fuse(pavilion, grille).Shape();
  }

  return pavilion;
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
  gp_Pnt hoodOrigin(-params.hoodRoomLength / 2, -params.hoodRoomWidth / 2, 0);
  TopoDS_Shape hoodRoom =
      BRepPrimAPI_MakeBox(hoodOrigin, params.hoodRoomLength,
                          params.hoodRoomWidth, params.hoodRoomHeight)
          .Shape();

  // 创建风帽室内腔（如果壁厚大于0）
  if (params.hoodWallThickness > 0) {
    gp_Pnt innerOrigin(-params.hoodRoomLength / 2 + params.hoodWallThickness,
                       -params.hoodRoomWidth / 2 + params.hoodWallThickness,
                       params.hoodWallThickness);
    TopoDS_Shape innerHood =
        BRepPrimAPI_MakeBox(
            innerOrigin, params.hoodRoomLength - 2 * params.hoodWallThickness,
            params.hoodRoomWidth - 2 * params.hoodWallThickness,
            params.hoodRoomHeight - params.hoodWallThickness)
            .Shape();
    hoodRoom = BRepAlgoAPI_Cut(hoodRoom, innerHood).Shape();
  }

  // 创建风通道（倾斜圆柱）
  gp_Pnt ductStart(-params.ductLeftDistance, 0, params.ductCenterHeight);
  gp_Pnt ductEnd(-params.ductLeftDistance + params.ductLength, 0,
                 params.ductCenterHeight - params.ductHeightDifference);

  // 创建风通道外壁
  gp_Vec ductDir(ductEnd.X() - ductStart.X(), 0, ductEnd.Z() - ductStart.Z());
  TopoDS_Shape duct =
      BRepPrimAPI_MakeCylinder(gp_Ax2(ductStart, ductDir),
                               params.ductDiameter / 2, ductDir.Magnitude())
          .Shape();

  // 创建风通道内腔（如果壁厚大于0）
  if (params.ductWallThickness > 0) {
    TopoDS_Shape innerDuct =
        BRepPrimAPI_MakeCylinder(gp_Ax2(ductStart, ductDir),
                                 params.ductDiameter / 2 -
                                     params.ductWallThickness,
                                 ductDir.Magnitude())
            .Shape();
    duct = BRepAlgoAPI_Cut(duct, innerDuct).Shape();
  }

  // 创建风基座（长方体）
  gp_Pnt baseOrigin(-params.baseLength / 2, -params.baseWidth / 2,
                    -params.baseHeight);
  TopoDS_Shape base = BRepPrimAPI_MakeBox(baseOrigin, params.baseLength,
                                          params.baseWidth, params.baseHeight)
                          .Shape();

  // 创建风基室（长方体）
  gp_Pnt baseRoomOrigin(-params.baseRoomLength / 2, -params.baseRoomWidth / 2,
                        -params.baseRoomHeight);
  TopoDS_Shape baseRoom =
      BRepPrimAPI_MakeBox(baseRoomOrigin, params.baseRoomLength,
                          params.baseRoomWidth, params.baseRoomHeight)
          .Shape();

  // 创建风基室内腔（如果壁厚大于0）
  if (params.baseRoomWallThickness > 0) {
    gp_Pnt innerBaseRoomOrigin(
        -params.baseRoomLength / 2 + params.baseRoomWallThickness,
        -params.baseRoomWidth / 2 + params.baseRoomWallThickness,
        -params.baseRoomHeight + params.baseRoomWallThickness);
    TopoDS_Shape innerBaseRoom =
        BRepPrimAPI_MakeBox(
            innerBaseRoomOrigin,
            params.baseRoomLength - 2 * params.baseRoomWallThickness,
            params.baseRoomWidth - 2 * params.baseRoomWallThickness,
            params.baseRoomHeight - params.baseRoomWallThickness)
            .Shape();
    baseRoom = BRepAlgoAPI_Cut(baseRoom, innerBaseRoom).Shape();
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
  if (params.wallThickness < 0 || params.floorThickness < 0) {
    throw Standard_ConstructionError("Thickness values must be non-negative");
  }

  // 创建井主体外壁
  double outerLength = params.length + 2 * params.wallThickness;
  double outerWidth = params.width + 2 * params.wallThickness;
  double outerHeight = params.height + params.floorThickness;

  gp_Pnt baseOrigin(-outerLength / 2, -outerWidth / 2, 0);
  TopoDS_Shape outerBox =
      BRepPrimAPI_MakeBox(baseOrigin, outerLength, outerWidth, outerHeight)
          .Shape();

  // 创建井主体内腔
  gp_Pnt innerOrigin(-params.length / 2, -params.width / 2,
                     params.floorThickness);
  TopoDS_Shape innerBox = BRepPrimAPI_MakeBox(innerOrigin, params.length,
                                              params.width, params.height)
                              .Shape();

  // 从外壁中减去内腔
  TopoDS_Shape wellBody = BRepAlgoAPI_Cut(outerBox, innerBox).Shape();

  // 创建井脖
  if (params.neckDiameter > 0 && params.neckHeight > 0) {
    gp_Ax2 neckAxis(gp_Pnt(0, 0, outerHeight), gp::DZ());
    TopoDS_Shape neck =
        BRepPrimAPI_MakeCylinder(neckAxis, params.neckDiameter / 2,
                                 params.neckHeight)
            .Shape();

    // 合并井脖和主体
    wellBody = BRepAlgoAPI_Fuse(wellBody, neck).Shape();
  }

  // 创建垫层
  if (params.cushionExtension > 0) {
    double cushionLength = outerLength + 2 * params.cushionExtension;
    double cushionWidth = outerWidth + 2 * params.cushionExtension;

    gp_Pnt cushionOrigin(-cushionLength / 2, -cushionWidth / 2, 0);
    TopoDS_Shape cushion =
        BRepPrimAPI_MakeBox(cushionOrigin, cushionLength, cushionWidth,
                            params.floorThickness)
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

  // 创建基础长方体
  gp_Pnt baseOrigin(-params.length / 2, -params.length / 2, 0);
  TopoDS_Shape support = BRepPrimAPI_MakeBox(baseOrigin, params.length,
                                             params.length, params.height)
                             .Shape();

  // 创建管枕孔
  for (int i = 0; i < params.count; ++i) {
    if (params.radii[i] <= 0)
      continue;

    // 创建圆柱形孔
    gp_Pnt center(params.positions[i].X(), params.positions[i].Y(),
                  params.height / 2);
    TopoDS_Shape hole =
        BRepPrimAPI_MakeCylinder(gp_Ax2(center, gp::DZ()), params.radii[i],
                                 params.height + 2)
            .Shape(); // 加2mm确保完全穿透

    // 从基础中减去孔
    support = BRepAlgoAPI_Cut(support, hole).Shape();
  }

  // 根据样式处理两侧管枕
  if (params.style == 2) {
    // 创建对称部分
    gp_Trsf mirror;
    mirror.SetMirror(gp_Ax2(gp::Origin(), gp::DY()));
    BRepBuilderAPI_Transform mirrorTransform(support, mirror);
    support = BRepAlgoAPI_Fuse(support, mirrorTransform.Shape()).Shape();
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
    if (params.length <= 0 || params.smallRadius <= 0 ||
        params.largeRadius <= params.smallRadius) {
      throw Standard_ConstructionError("Invalid parameters for sector cover");
    }

    // 创建扇形面
    gp_Circ outerCircle(gp_Ax2(gp::Origin(), gp::DZ()), params.largeRadius);
    gp_Circ innerCircle(gp_Ax2(gp::Origin(), gp::DZ()), params.smallRadius);

    // 计算扇形角度
    double angle = 2 * asin(params.length / (2 * params.largeRadius));

    // 创建外弧
    Handle(Geom_TrimmedCurve) outerArc =
        GC_MakeArcOfCircle(outerCircle, -angle / 2, angle / 2, true).Value();

    // 创建内弧
    Handle(Geom_TrimmedCurve) innerArc =
        GC_MakeArcOfCircle(innerCircle, -angle / 2, angle / 2, true).Value();

    // 创建边
    TopoDS_Edge outerEdge = BRepBuilderAPI_MakeEdge(outerArc).Edge();
    TopoDS_Edge innerEdge = BRepBuilderAPI_MakeEdge(innerArc).Edge();
    TopoDS_Edge startEdge =
        BRepBuilderAPI_MakeEdge(gp_Pnt(params.smallRadius * cos(-angle / 2),
                                       params.smallRadius * sin(-angle / 2), 0),
                                gp_Pnt(params.largeRadius * cos(-angle / 2),
                                       params.largeRadius * sin(-angle / 2), 0))
            .Edge();
    TopoDS_Edge endEdge =
        BRepBuilderAPI_MakeEdge(gp_Pnt(params.smallRadius * cos(angle / 2),
                                       params.smallRadius * sin(angle / 2), 0),
                                gp_Pnt(params.largeRadius * cos(angle / 2),
                                       params.largeRadius * sin(angle / 2), 0))
            .Edge();

    // 创建线框
    TopoDS_Wire wire =
        BRepBuilderAPI_MakeWire(startEdge, outerEdge, endEdge, innerEdge)
            .Wire();

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
  gp_Pnt outerOrigin(-params.outerLength / 2, -params.outerHeight / 2, 0);
  TopoDS_Shape outerBox =
      BRepPrimAPI_MakeBox(outerOrigin, params.outerLength, params.outerHeight,
                          params.outerLength)
          .Shape();

  // 创建槽盒主体内轮廓
  gp_Pnt innerOrigin(-params.innerLength / 2, -params.innerHeight / 2, 0);
  TopoDS_Shape innerBox =
      BRepPrimAPI_MakeBox(innerOrigin, params.innerLength, params.innerHeight,
                          params.outerLength + 2)
          .Shape();

  // 从外轮廓中减去内轮廓形成槽盒主体
  TopoDS_Shape troughBody = BRepAlgoAPI_Cut(outerBox, innerBox).Shape();

  // 创建盖板
  gp_Pnt coverOrigin(-params.outerLength / 2, -params.outerHeight / 2,
                     params.outerLength);
  TopoDS_Shape cover =
      BRepPrimAPI_MakeBox(coverOrigin, params.outerLength, params.outerHeight,
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

} // namespace topo
} // namespace flywave
