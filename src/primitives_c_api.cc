#include "primitives_c_api.h"
#include "primitives.hh"
#include "shape.hh"
#include "topo_impl.hh"

using namespace flywave::topo;

#ifdef __cplusplus
extern "C" {
#endif

pnt3d_t *convert_points_to_capi(const std::vector<gp_Pnt> &points,
                                int *out_count) {
  *out_count = static_cast<int>(points.size());
  pnt3d_t *result = (pnt3d_t *)malloc(*out_count * sizeof(pnt3d_t));
  for (int i = 0; i < *out_count; ++i) {
    result[i].x = points[i].X();
    result[i].y = points[i].Y();
    result[i].z = points[i].Z();
  }
  return result;
}

PRIMCAPICALL topo_shape_t *create_sphere(sphere_params_t params) {
  sphere_params cpp_params{params.radius};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_sphere(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_sphere_with_place(sphere_params_t params,
                                                    pnt3d_t center) {
  sphere_params cpp_params{params.radius};
  gp_Pnt cpp_center(center.x, center.y, center.z);

  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_sphere(cpp_params, cpp_center))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_rotational_ellipsoid(rotational_ellipsoid_params_t params) {
  rotational_ellipsoid_params cpp_params{
      params.polarRadius, params.equatorialRadius, params.height};
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(
                                create_rotational_ellipsoid(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_rotational_ellipsoid_with_place(rotational_ellipsoid_params_t params,
                                       pnt3d_t center, dir3d_t xDir) {
  rotational_ellipsoid_params cpp_params{
      params.polarRadius, params.equatorialRadius, params.height};
  gp_Pnt cpp_center(center.x, center.y, center.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_rotational_ellipsoid(cpp_params, cpp_center, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_cuboid(cuboid_params_t params) {
  cuboid_params cpp_params{params.length, params.width, params.height};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cuboid(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_cuboid_with_place(cuboid_params_t params,
                                                    pnt3d_t center,
                                                    dir3d_t xDir,
                                                    dir3d_t zDir) {
  cuboid_params cpp_params{params.length, params.width, params.height};
  gp_Pnt cpp_center(center.x, center.y, center.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  gp_Dir cpp_zDir(zDir.x, zDir.y, zDir.z);
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(create_cuboid(
                                cpp_params, cpp_center, cpp_xDir, cpp_zDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_diamond_frustum(diamond_frustum_t params) {
  diamond_frustum cpp_params{params.topDiag1, params.topDiag2,
                             params.bottomDiag1, params.bottomDiag2,
                             params.height};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_diamond_frustum(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_diamond_frustum_with_place(diamond_frustum_t params, pnt3d_t position,
                                  dir3d_t normal, dir3d_t xDir) {
  diamond_frustum cpp_params{params.topDiag1, params.topDiag2,
                             params.bottomDiag1, params.bottomDiag2,
                             params.height};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_diamond_frustum(
            cpp_params, cpp_position, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_offset_rectangular_table(offset_rectangular_table_params_t params) {
  offset_rectangular_table_params cpp_params{
      params.topLength,   params.topWidth, params.bottomLength,
      params.bottomWidth, params.height,   params.xOffset,
      params.yOffset};
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(
                                create_offset_rectangular_table(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_offset_rectangular_table_with_place(
    offset_rectangular_table_params_t params, pnt3d_t position, dir3d_t normal,
    dir3d_t xDir) {
  offset_rectangular_table_params cpp_params{
      params.topLength,   params.topWidth, params.bottomLength,
      params.bottomWidth, params.height,   params.xOffset,
      params.yOffset};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_offset_rectangular_table(
            cpp_params, cpp_position, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_cylinder(cylinder_params_t params) {
  cylinder_params cpp_params{params.radius, params.height};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cylinder(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_cylinder_with_place(cylinder_params_t params,
                                                      pnt3d_t baseCenter,
                                                      dir3d_t axisDir) {
  cylinder_params cpp_params{params.radius, params.height};
  gp_Pnt cpp_baseCenter(baseCenter.x, baseCenter.y, baseCenter.z);
  gp_Dir cpp_axisDir(axisDir.x, axisDir.y, axisDir.z);
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(create_cylinder(
                                cpp_params, cpp_baseCenter, cpp_axisDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_sharp_bent_cylinder(sharp_bent_cylinder_params_t params) {
  sharp_bent_cylinder_params cpp_params{params.radius, params.length,
                                        params.bendAngle};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_sharp_bent_cylinder(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_sharp_bent_cylinder_with_place(sharp_bent_cylinder_params_t params,
                                      pnt3d_t bendPoint, dir3d_t initialDir,
                                      dir3d_t bendPlaneNormal) {
  sharp_bent_cylinder_params cpp_params{params.radius, params.length,
                                        params.bendAngle};
  gp_Pnt cpp_bendPoint(bendPoint.x, bendPoint.y, bendPoint.z);
  gp_Dir cpp_initialDir(initialDir.x, initialDir.y, initialDir.z);
  gp_Dir cpp_bendPlaneNormal(bendPlaneNormal.x, bendPlaneNormal.y,
                             bendPlaneNormal.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_sharp_bent_cylinder(
            cpp_params, cpp_bendPoint, cpp_initialDir, cpp_bendPlaneNormal))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_truncated_cone(truncated_cone_params_t params) {
  truncated_cone_params cpp_params{params.topRadius, params.bottomRadius,
                                   params.height};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_truncated_cone(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_truncated_cone_with_place(truncated_cone_params_t params,
                                 pnt3d_t baseCenter, dir3d_t axisDir) {
  truncated_cone_params cpp_params{params.topRadius, params.bottomRadius,
                                   params.height};
  gp_Pnt cpp_baseCenter(baseCenter.x, baseCenter.y, baseCenter.z);
  gp_Dir cpp_axisDir(axisDir.x, axisDir.y, axisDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_truncated_cone(cpp_params, cpp_baseCenter, cpp_axisDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_eccentric_truncated_cone(eccentric_truncated_cone_params_t params) {
  eccentric_truncated_cone_params cpp_params{
      params.topRadius, params.bottomRadius, params.height, params.topXOffset,
      params.topYOffset};
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(
                                create_eccentric_truncated_cone(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_eccentric_truncated_cone_with_place(
    eccentric_truncated_cone_params_t params, pnt3d_t baseCenter,
    dir3d_t axisDir) {
  eccentric_truncated_cone_params cpp_params{
      params.topRadius, params.bottomRadius, params.height, params.topXOffset,
      params.topYOffset};
  gp_Pnt cpp_baseCenter(baseCenter.x, baseCenter.y, baseCenter.z);
  gp_Dir cpp_axisDir(axisDir.x, axisDir.y, axisDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_eccentric_truncated_cone(
            cpp_params, cpp_baseCenter, cpp_axisDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_ring(ring_params_t params) {
  ring_params cpp_params{params.ringRadius, params.tubeRadius, params.angle};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_ring(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_ring_with_place(ring_params_t params,
                                                  pnt3d_t center,
                                                  dir3d_t normal,
                                                  dir3d_t xDir) {
  ring_params cpp_params{params.ringRadius, params.tubeRadius, params.angle};
  gp_Pnt cpp_center(center.x, center.y, center.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(create_ring(
                                cpp_params, cpp_center, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_rectangular_ring(rectangular_ring_params_t params) {
  rectangular_ring_params cpp_params{params.tubeRadius, params.filletRadius,
                                     params.length, params.width};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_rectangular_ring(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_rectangular_ring_with_place(rectangular_ring_params_t params,
                                   pnt3d_t center, dir3d_t normal,
                                   dir3d_t xDir) {
  rectangular_ring_params cpp_params{params.tubeRadius, params.filletRadius,
                                     params.length, params.width};
  gp_Pnt cpp_center(center.x, center.y, center.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_rectangular_ring(
            cpp_params, cpp_center, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_elliptic_ring(elliptic_ring_params_t params) {
  elliptic_ring_params cpp_params{params.tubeRadius, params.majorRadius,
                                  params.minorRadius};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_elliptic_ring(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_elliptic_ring_with_place(elliptic_ring_params_t params, pnt3d_t center,
                                dir3d_t normal, dir3d_t xDir) {
  elliptic_ring_params cpp_params{params.tubeRadius, params.majorRadius,
                                  params.minorRadius};
  gp_Pnt cpp_center(center.x, center.y, center.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(create_elliptic_ring(
                                cpp_params, cpp_center, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_circular_gasket(circular_gasket_params_t params) {
  circular_gasket_params cpp_params{params.outerRadius, params.innerRadius,
                                    params.height, params.angle};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_circular_gasket(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_circular_gasket_with_place(circular_gasket_params_t params,
                                  pnt3d_t center, dir3d_t normal,
                                  dir3d_t xDir) {
  circular_gasket_params cpp_params{params.outerRadius, params.innerRadius,
                                    params.height, params.angle};
  gp_Pnt cpp_center(center.x, center.y, center.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_circular_gasket(
            cpp_params, cpp_center, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_table_gasket(table_gasket_params_t params) {
  table_gasket_params cpp_params{params.topRadius, params.outerRadius,
                                 params.innerRadius, params.height,
                                 params.angle};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_table_gasket(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_table_gasket_with_place(table_gasket_params_t params, pnt3d_t center,
                               dir3d_t normal, dir3d_t xDir) {
  table_gasket_params cpp_params{params.topRadius, params.outerRadius,
                                 params.innerRadius, params.height,
                                 params.angle};
  gp_Pnt cpp_center(center.x, center.y, center.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(create_table_gasket(
                                cpp_params, cpp_center, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_square_gasket(square_gasket_params_t params) {
  square_gasket_params cpp_params{params.outerLength, params.outerWidth,
                                  params.innerLength, params.innerWidth,
                                  params.height,      params.cornerType,
                                  params.cornerParam};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_square_gasket(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_square_gasket_with_place(square_gasket_params_t params, pnt3d_t center,
                                dir3d_t normal, dir3d_t xDir) {
  square_gasket_params cpp_params{params.outerLength, params.outerWidth,
                                  params.innerLength, params.innerWidth,
                                  params.height,      params.cornerType,
                                  params.cornerParam};
  gp_Pnt cpp_center(center.x, center.y, center.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(create_square_gasket(
                                cpp_params, cpp_center, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_stretched_body(stretched_body_params_t params) {
  std::vector<gp_Pnt> points;
  for (int i = 0; i < params.numPoints; ++i) {
    points.push_back(
        gp_Pnt(params.points[i].x, params.points[i].y, params.points[i].z));
  }
  stretched_body_params cpp_params{
      points, gp_Dir(params.normal.x, params.normal.y, params.normal.z),
      params.length};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_stretched_body(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_stretched_body_with_place(stretched_body_params_t params,
                                 pnt3d_t basePoint, dir3d_t xDir) {
  std::vector<gp_Pnt> points;
  for (int i = 0; i < params.numPoints; ++i) {
    points.push_back(
        gp_Pnt(params.points[i].x, params.points[i].y, params.points[i].z));
  }
  stretched_body_params cpp_params{
      points, gp_Dir(params.normal.x, params.normal.y, params.normal.z),
      params.length};
  gp_Pnt cpp_basePoint(basePoint.x, basePoint.y, basePoint.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_stretched_body(cpp_params, cpp_basePoint, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_porcelain_bushing(porcelain_bushing_params_t params) {
  porcelain_bushing_params cpp_params{params.height, params.radius,
                                      params.bigSkirtRadius,
                                      params.smallSkirtRadius, params.count};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_porcelain_bushing(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_porcelain_bushing_with_place(porcelain_bushing_params_t params,
                                    pnt3d_t basePoint, dir3d_t axisDir) {
  porcelain_bushing_params cpp_params{params.height, params.radius,
                                      params.bigSkirtRadius,
                                      params.smallSkirtRadius, params.count};
  gp_Pnt cpp_basePoint(basePoint.x, basePoint.y, basePoint.z);
  gp_Dir cpp_axisDir(axisDir.x, axisDir.y, axisDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_porcelain_bushing(cpp_params, cpp_basePoint, cpp_axisDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_cone_porcelain_bushing(cone_porcelain_bushing_params_t params) {
  cone_porcelain_bushing_params cpp_params{params.height,
                                           params.bottomRadius,
                                           params.topRadius,
                                           params.bottomSkirtRadius1,
                                           params.bottomSkirtRadius2,
                                           params.topSkirtRadius1,
                                           params.topSkirtRadius2,
                                           params.count};
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(
                                create_cone_porcelain_bushing(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_cone_porcelain_bushing_with_place(cone_porcelain_bushing_params_t params,
                                         pnt3d_t basePoint, dir3d_t axisDir) {
  cone_porcelain_bushing_params cpp_params{params.height,
                                           params.bottomRadius,
                                           params.topRadius,
                                           params.bottomSkirtRadius1,
                                           params.bottomSkirtRadius2,
                                           params.topSkirtRadius1,
                                           params.topSkirtRadius2,
                                           params.count};
  gp_Pnt cpp_basePoint(basePoint.x, basePoint.y, basePoint.z);
  gp_Dir cpp_axisDir(axisDir.x, axisDir.y, axisDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cone_porcelain_bushing(
            cpp_params, cpp_basePoint, cpp_axisDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_insulator_string(insulator_string_params_t params) {
  insulator_string_params cpp_params{
      params.count,     params.spacing,        params.insulatorCount,
      params.height,    params.bigSkirtRadius, params.smallSkirtRadius,
      params.radius,    params.frontLength,    params.backLength,
      params.splitCount};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_insulator_string(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_insulator_string_with_place(insulator_string_params_t params,
                                   pnt3d_t position, dir3d_t direction,
                                   dir3d_t upDirection) {
  insulator_string_params cpp_params{
      params.count,     params.spacing,        params.insulatorCount,
      params.height,    params.bigSkirtRadius, params.smallSkirtRadius,
      params.radius,    params.frontLength,    params.backLength,
      params.splitCount};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_upDirection(upDirection.x, upDirection.y, upDirection.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_insulator_string(
            cpp_params, cpp_position, cpp_direction, cpp_upDirection))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_vtype_insulator(vtype_insulator_params_t params) {
  vtype_insulator_params cpp_params{
      params.frontSpacing,     params.backSpacing, params.insulatorCount,
      params.height,           params.radius,      params.bigSkirtRadius,
      params.smallSkirtRadius, params.frontLength, params.backLength,
      params.splitCount};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_vtype_insulator(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_vtype_insulator_with_place(vtype_insulator_params_t params,
                                  pnt3d_t position, dir3d_t direction,
                                  dir3d_t upDirection) {
  vtype_insulator_params cpp_params{
      params.frontSpacing,     params.backSpacing, params.insulatorCount,
      params.height,           params.radius,      params.bigSkirtRadius,
      params.smallSkirtRadius, params.frontLength, params.backLength,
      params.splitCount};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_upDirection(upDirection.x, upDirection.y, upDirection.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_vtype_insulator(
            cpp_params, cpp_position, cpp_direction, cpp_upDirection))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_terminal_block(terminal_block_params_t params) {
  terminal_block_params cpp_params{params.length,        params.width,
                                   params.thickness,     params.chamferLength,
                                   params.columnSpacing, params.rowSpacing,
                                   params.holeRadius,    params.columnCount,
                                   params.rowCount,      params.bottomOffset};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_terminal_block(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_terminal_block_with_place(terminal_block_params_t params,
                                 pnt3d_t position, dir3d_t lengthDir,
                                 dir3d_t widthDir) {
  terminal_block_params cpp_params{params.length,        params.width,
                                   params.thickness,     params.chamferLength,
                                   params.columnSpacing, params.rowSpacing,
                                   params.holeRadius,    params.columnCount,
                                   params.rowCount,      params.bottomOffset};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_lengthDir(lengthDir.x, lengthDir.y, lengthDir.z);
  gp_Dir cpp_widthDir(widthDir.x, widthDir.y, widthDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_terminal_block(
            cpp_params, cpp_position, cpp_lengthDir, cpp_widthDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_rectangular_fixed_plate(rectangular_hole_plate_params_t params) {
  rectangular_hole_plate_params cpp_params{
      params.length,        params.width,         params.thickness,
      params.columnSpacing, params.rowSpacing,    params.columnCount,
      params.rowCount,      params.hasMiddleHole, params.holeDiameter};
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(
                                create_rectangular_fixed_plate(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_rectangular_fixed_plate_with_place(
    rectangular_hole_plate_params_t params, pnt3d_t position, dir3d_t lengthDir,
    dir3d_t widthDir) {
  rectangular_hole_plate_params cpp_params{
      params.length,        params.width,         params.thickness,
      params.columnSpacing, params.rowSpacing,    params.columnCount,
      params.rowCount,      params.hasMiddleHole, params.holeDiameter};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_lengthDir(lengthDir.x, lengthDir.y, lengthDir.z);
  gp_Dir cpp_widthDir(widthDir.x, widthDir.y, widthDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_rectangular_fixed_plate(
            cpp_params, cpp_position, cpp_lengthDir, cpp_widthDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_circular_fixed_plate(circular_fixed_plate_params_t params) {
  circular_fixed_plate_params cpp_params{
      params.length,      params.width,     params.thickness,
      params.ringRadius,  params.holeCount, params.hasMiddleHole,
      params.holeDiameter};
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(
                                create_circular_fixed_plate(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_circular_fixed_plate_with_place(circular_fixed_plate_params_t params,
                                       pnt3d_t position, dir3d_t lengthDir,
                                       dir3d_t widthDir) {
  circular_fixed_plate_params cpp_params{
      params.length,      params.width,     params.thickness,
      params.ringRadius,  params.holeCount, params.hasMiddleHole,
      params.holeDiameter};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_lengthDir(lengthDir.x, lengthDir.y, lengthDir.z);
  gp_Dir cpp_widthDir(widthDir.x, widthDir.y, widthDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_circular_fixed_plate(
            cpp_params, cpp_position, cpp_lengthDir, cpp_widthDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_wire(wire_params_t params) {
  std::vector<gp_Pnt> points;
  for (int i = 0; i < params.numFitPoints; i++) {
    points.push_back(gp_Pnt(params.fitPoints[i].x, params.fitPoints[i].y,
                            params.fitPoints[i].z));
  }
  wire_params cpp_params{
      gp_Pnt(params.startPoint.x, params.startPoint.y, params.startPoint.z),
      gp_Pnt(params.endPoint.x, params.endPoint.y, params.endPoint.z),
      gp_Dir(params.startDir.x, params.startDir.y, params.startDir.z),
      gp_Dir(params.endDir.x, params.endDir.y, params.endDir.z),
      params.sag,
      params.diameter,
      points};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_wire(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_wire_with_place(wire_params_t params,
                                                  pnt3d_t position,
                                                  dir3d_t direction,
                                                  dir3d_t upDirection) {
  std::vector<gp_Pnt> points;
  for (int i = 0; i < params.numFitPoints; i++) {
    points.push_back(gp_Pnt(params.fitPoints[i].x, params.fitPoints[i].y,
                            params.fitPoints[i].z));
  }

  wire_params cpp_params{
      gp_Pnt(params.startPoint.x, params.startPoint.y, params.startPoint.z),
      gp_Pnt(params.endPoint.x, params.endPoint.y, params.endPoint.z),
      gp_Dir(params.startDir.x, params.startDir.y, params.startDir.z),
      gp_Dir(params.endDir.x, params.endDir.y, params.endDir.z),
      params.sag,
      params.diameter,
      points,
  };
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_upDirection(upDirection.x, upDirection.y, upDirection.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_wire(
            cpp_params, cpp_position, cpp_direction, cpp_upDirection))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL pnt3d_t *sample_wire_points(wire_params_t params,
                                         double tessellation, int *out_count) {
  std::vector<gp_Pnt> points;
  for (int i = 0; i < params.numFitPoints; i++) {
    points.push_back(gp_Pnt(params.fitPoints[i].x, params.fitPoints[i].y,
                            params.fitPoints[i].z));
  }

  wire_params cppParams{
      gp_Pnt(params.startPoint.x, params.startPoint.y, params.startPoint.z),
      gp_Pnt(params.endPoint.x, params.endPoint.y, params.endPoint.z),
      gp_Dir(params.startDir.x, params.startDir.y, params.startDir.z),
      gp_Dir(params.endDir.x, params.endDir.y, params.endDir.z),
      params.sag,
      params.diameter,
      points,
  };
  auto spoints = sample_wire(cppParams, tessellation);
  return convert_points_to_capi(spoints, out_count);
}

PRIMCAPICALL topo_shape_t *create_cable(cable_params_t params) {
  std::vector<gp_Pnt> points;
  for (int i = 0; i < params.numInflectionPoints; i++) {
    points.push_back(gp_Pnt(params.inflectionPoints[i].x,
                            params.inflectionPoints[i].y,
                            params.inflectionPoints[i].z));
  }
  cable_params cpp_params{
      gp_Pnt(params.startPoint.x, params.startPoint.y, params.startPoint.z),
      gp_Pnt(params.endPoint.x, params.endPoint.y, params.endPoint.z), points,
      std::vector<double>(params.radii, params.radii + params.numRadii),
      params.diameter};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cable(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL pnt3d_t *sample_cable_points(cable_params_t params,
                                          double tessellation, int *out_count) {
  std::vector<gp_Pnt> points;
  for (int i = 0; i < params.numInflectionPoints; i++) {
    points.push_back(gp_Pnt(params.inflectionPoints[i].x,
                            params.inflectionPoints[i].y,
                            params.inflectionPoints[i].z));
  }
  cable_params cppParams{
      gp_Pnt(params.startPoint.x, params.startPoint.y, params.startPoint.z),
      gp_Pnt(params.endPoint.x, params.endPoint.y, params.endPoint.z), points,
      std::vector<double>(params.radii, params.radii + params.numRadii),
      params.diameter};
  auto spoints = sample_cable(cppParams, tessellation);
  return convert_points_to_capi(spoints, out_count);
}

PRIMCAPICALL topo_shape_t *create_cable_with_place(cable_params_t params,
                                                   pnt3d_t position,
                                                   dir3d_t direction,
                                                   dir3d_t upDirection) {
  std::vector<gp_Pnt> points;
  for (int i = 0; i < params.numInflectionPoints; i++) {
    points.push_back(gp_Pnt(params.inflectionPoints[i].x,
                            params.inflectionPoints[i].y,
                            params.inflectionPoints[i].z));
  }
  cable_params cpp_params{
      gp_Pnt(params.startPoint.x, params.startPoint.y, params.startPoint.z),
      gp_Pnt(params.endPoint.x, params.endPoint.y, params.endPoint.z), points,
      std::vector<double>(params.radii, params.radii + params.numRadii),
      params.diameter};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_upDirection(upDirection.x, upDirection.y, upDirection.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cable(
            cpp_params, cpp_position, cpp_direction, cpp_upDirection))};
  } catch (...) {
    return nullptr;
  }
}

// 曲线采样函数实现
PRIMCAPICALL pnt3d_t *
sample_curve_points(const pnt3d_t *control_points, const int *point_counts,
                    int array_count, const curve_type_t *curve_types,
                    int curve_type_count, double tessellation, int *out_count) {
  // 参数检查
  if (!control_points || !point_counts || !curve_types || !out_count ||
      array_count <= 0 || curve_type_count <= 0) {
    return nullptr;
  }

  // 转换输入数据
  std::vector<std::vector<gp_Pnt>> cpp_control_points;
  std::vector<curve_type> cpp_curve_types;

  const pnt3d_t *current_points = control_points;
  for (int i = 0; i < array_count; ++i) {
    std::vector<gp_Pnt> points;
    for (int j = 0; j < point_counts[i]; ++j) {
      points.push_back(
          gp_Pnt(current_points->x, current_points->y, current_points->z));
      ++current_points;
    }
    cpp_control_points.push_back(points);
  }

  for (int i = 0; i < curve_type_count; ++i) {
    cpp_curve_types.push_back(static_cast<curve_type>(curve_types[i]));
  }

  // 调用C++函数
  auto points =
      sample_curve_points(cpp_control_points, cpp_curve_types, tessellation);

  // 转换输出结果
  *out_count = static_cast<int>(points.size());
  pnt3d_t *result = new pnt3d_t[points.size()];
  for (size_t i = 0; i < points.size(); ++i) {
    result[i].x = points[i].X();
    result[i].y = points[i].Y();
    result[i].z = points[i].Z();
  }

  return result;
}

PRIMCAPICALL topo_shape_t *create_curve_cable(curve_cable_params_t params) {
  try {
    std::vector<std::vector<gp_Pnt>> cpp_controlPoints;
    std::vector<curve_type> cpp_curveTypes;

    for (int i = 0; i < params.numSegments; ++i) {
      std::vector<gp_Pnt> segmentPoints;
      for (int j = 0; j < params.segments[i].numPoints; ++j) {
        pnt3d_t point = params.segments[i].controlPoints[j];
        segmentPoints.push_back(gp_Pnt(point.x, point.y, point.z));
      }
      cpp_controlPoints.push_back(segmentPoints);

      switch (params.curveTypes[i]) {
      case CURVE_TYPE_LINE:
        cpp_curveTypes.push_back(curve_type::LINE);
        break;
      case CURVE_TYPE_ARC:
        cpp_curveTypes.push_back(curve_type::ARC);
        break;
      case CURVE_TYPE_BEZIER:
        cpp_curveTypes.push_back(curve_type::BEZIER);
        break;
      }
    }

    curve_cable_params cpp_params{cpp_controlPoints, cpp_curveTypes,
                                  params.diameter};
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_curve_cable(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_curve_cable_with_place(curve_cable_params_t params, pnt3d_t position,
                              dir3d_t direction, dir3d_t upDirection) {
  try {
    std::vector<std::vector<gp_Pnt>> cpp_controlPoints;
    std::vector<curve_type> cpp_curveTypes;

    for (int i = 0; i < params.numSegments; ++i) {
      std::vector<gp_Pnt> segmentPoints;
      for (int j = 0; j < params.segments[i].numPoints; ++j) {
        pnt3d_t point = params.segments[i].controlPoints[j];
        segmentPoints.push_back(gp_Pnt(point.x, point.y, point.z));
      }
      cpp_controlPoints.push_back(segmentPoints);

      switch (params.curveTypes[i]) {
      case CURVE_TYPE_LINE:
        cpp_curveTypes.push_back(curve_type::LINE);
        break;
      case CURVE_TYPE_ARC:
        cpp_curveTypes.push_back(curve_type::ARC);
        break;
      case CURVE_TYPE_BEZIER:
        cpp_curveTypes.push_back(curve_type::BEZIER);
        break;
      }
    }

    curve_cable_params cpp_params{cpp_controlPoints, cpp_curveTypes,
                                  params.diameter};
    gp_Pnt cpp_position(position.x, position.y, position.z);
    gp_Dir cpp_direction(direction.x, direction.y, direction.z);
    gp_Dir cpp_upDirection(upDirection.x, upDirection.y, upDirection.z);

    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_curve_cable(
            cpp_params, cpp_position, cpp_direction, cpp_upDirection))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_angle_steel(angle_steel_params_t params) {
  angle_steel_params cpp_params{params.L1, params.L2, params.X, params.length};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_angle_steel(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_angle_steel_with_place(angle_steel_params_t params, pnt3d_t position,
                              dir3d_t xDir, dir3d_t longEdgeDir) {
  angle_steel_params cpp_params{params.L1, params.L2, params.X, params.length};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  gp_Dir cpp_longEdgeDir(longEdgeDir.x, longEdgeDir.y, longEdgeDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_angle_steel(
            cpp_params, cpp_position, cpp_xDir, cpp_longEdgeDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_i_shaped_steel(i_shaped_steel_params_t params) {
  i_shaped_steel_params cpp_params{params.height, params.flangeWidth,
                                   params.webThickness, params.flangeThickness,
                                   params.length};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_i_shaped_steel(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_i_shaped_steel_with_place(i_shaped_steel_params_t params,
                                 pnt3d_t position, dir3d_t xDir, dir3d_t zDir) {
  i_shaped_steel_params cpp_params{params.height, params.flangeWidth,
                                   params.webThickness, params.flangeThickness,
                                   params.length};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  gp_Dir cpp_zDir(zDir.x, zDir.y, zDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_i_shaped_steel(
            cpp_params, cpp_position, cpp_xDir, cpp_zDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_channel_steel(channel_steel_params_t params) {
  channel_steel_params cpp_params{params.height, params.flangeWidth,
                                  params.webThickness, params.flangeThickness,
                                  params.length};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_channel_steel(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_channel_steel_with_place(channel_steel_params_t params, pnt3d_t position,
                                dir3d_t xDir, dir3d_t zDir) {
  channel_steel_params cpp_params{params.height, params.flangeWidth,
                                  params.webThickness, params.flangeThickness,
                                  params.length};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  gp_Dir cpp_zDir(zDir.x, zDir.y, zDir.z);
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(create_channel_steel(
                                cpp_params, cpp_position, cpp_xDir, cpp_zDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_t_steel(t_steel_params_t params) {
  t_steel_params cpp_params{params.height, params.width, params.webThickness,
                            params.flangeThickness, params.length};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_t_steel(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_t_steel_with_place(t_steel_params_t params,
                                                     pnt3d_t position,
                                                     dir3d_t xDir,
                                                     dir3d_t zDir) {
  t_steel_params cpp_params{params.height, params.width, params.webThickness,
                            params.flangeThickness, params.length};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  gp_Dir cpp_zDir(zDir.x, zDir.y, zDir.z);
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(create_t_steel(
                                cpp_params, cpp_position, cpp_xDir, cpp_zDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_bored_pile_base(bored_pile_params_t params) {
  bored_pile_params cpp_params{params.H1, params.H2, params.H3,
                               params.H4, params.d,  params.D};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_bored_pile_base(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_bored_pile_base_with_place(bored_pile_params_t params, pnt3d_t position,
                                  dir3d_t direction) {
  bored_pile_params cpp_params{params.H1, params.H2, params.H3,
                               params.H4, params.d,  params.D};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_bored_pile_base(cpp_params, cpp_position, cpp_direction))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_pile_cap_base(pile_cap_params_t params) {
  std::vector<gp_Pnt> points;
  for (int i = 0; i < params.ZCOUNT; i++) {
    points.push_back(gp_Pnt(params.ZPOSTARRAY[i].x, params.ZPOSTARRAY[i].y,
                            params.ZPOSTARRAY[i].z));
  }
  pile_cap_params cpp_params{params.H1, params.H2, params.H3,     params.H4,
                             params.H5, params.H6, params.d,      params.D,
                             params.b,  params.B1, params.L1,     params.e1,
                             params.e2, params.cs, params.ZCOUNT, points};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_pile_cap_base(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_pile_cap_base_with_place(pile_cap_params_t params, pnt3d_t position,
                                dir3d_t direction) {
  std::vector<gp_Pnt> points;
  for (int i = 0; i < params.ZCOUNT; i++) {
    points.push_back(gp_Pnt(params.ZPOSTARRAY[i].x, params.ZPOSTARRAY[i].y,
                            params.ZPOSTARRAY[i].z));
  }
  pile_cap_params cpp_params{params.H1, params.H2, params.H3,     params.H4,
                             params.H5, params.H6, params.d,      params.D,
                             params.b,  params.B1, params.L1,     params.e1,
                             params.e2, params.cs, params.ZCOUNT, points};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(create_pile_cap_base(
                                cpp_params, cpp_position, cpp_direction))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_rock_anchor_base(rock_anchor_params_t params) {
  std::vector<gp_Pnt> points;
  for (int i = 0; i < params.ZCOUNT; i++) {
    points.push_back(gp_Pnt(params.ZPOSTARRAY[i].x, params.ZPOSTARRAY[i].y,
                            params.ZPOSTARRAY[i].z));
  }
  rock_anchor_params cpp_params{params.H1, params.H2,     params.d, params.B1,
                                params.L1, params.ZCOUNT, points};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_rock_anchor_base(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_rock_anchor_base_with_place(rock_anchor_params_t params,
                                   pnt3d_t position, dir3d_t direction) {
  std::vector<gp_Pnt> points;
  for (int i = 0; i < params.ZCOUNT; i++) {
    points.push_back(gp_Pnt(params.ZPOSTARRAY[i].x, params.ZPOSTARRAY[i].y,
                            params.ZPOSTARRAY[i].z));
  }
  rock_anchor_params cpp_params{params.H1, params.H2,     params.d, params.B1,
                                params.L1, params.ZCOUNT, points};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_rock_anchor_base(cpp_params, cpp_position, cpp_direction))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_rock_pile_cap_base(rock_pile_cap_params_t params) {
  std::vector<gp_Pnt> points;
  for (int i = 0; i < params.ZCOUNT; i++) {
    points.push_back(gp_Pnt(params.ZPOSTARRAY[i].x, params.ZPOSTARRAY[i].y,
                            params.ZPOSTARRAY[i].z));
  }
  rock_pile_cap_params cpp_params{
      params.H1, params.H2, params.H3, params.d,  params.b,      params.B1,
      params.L1, params.e1, params.e2, params.cs, params.ZCOUNT, points};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_rock_pile_cap_base(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_rock_pile_cap_base_with_place(rock_pile_cap_params_t params,
                                     pnt3d_t position, dir3d_t direction) {
  std::vector<gp_Pnt> points;
  for (int i = 0; i < params.ZCOUNT; i++) {
    points.push_back(gp_Pnt(params.ZPOSTARRAY[i].x, params.ZPOSTARRAY[i].y,
                            params.ZPOSTARRAY[i].z));
  }
  rock_pile_cap_params cpp_params{
      params.H1, params.H2, params.H3, params.d,  params.b,      params.B1,
      params.L1, params.e1, params.e2, params.cs, params.ZCOUNT, points};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_rock_pile_cap_base(
            cpp_params, cpp_position, cpp_direction))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_embedded_rock_anchor_base(embedded_rock_anchor_params_t params) {
  embedded_rock_anchor_params cpp_params{params.H1, params.H2, params.H3,
                                         params.d, params.D};
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(
                                create_embedded_rock_anchor_base(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_embedded_rock_anchor_base_with_place(
    embedded_rock_anchor_params_t params, pnt3d_t position, dir3d_t direction) {
  embedded_rock_anchor_params cpp_params{params.H1, params.H2, params.H3,
                                         params.d, params.D};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_embedded_rock_anchor_base(
            cpp_params, cpp_position, cpp_direction))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_inclined_rock_anchor_base(inclined_rock_anchor_params_t params) {
  inclined_rock_anchor_params cpp_params{
      params.H1, params.H2, params.d,  params.D,      params.B,
      params.L,  params.e1, params.e2, params.alpha1, params.alpha2};
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(
                                create_inclined_rock_anchor_base(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_inclined_rock_anchor_base_with_place(
    inclined_rock_anchor_params_t params, pnt3d_t position, dir3d_t direction) {
  inclined_rock_anchor_params cpp_params{
      params.H1, params.H2, params.d,  params.D,      params.B,
      params.L,  params.e1, params.e2, params.alpha1, params.alpha2};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_inclined_rock_anchor_base(
            cpp_params, cpp_position, cpp_direction))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_excavated_base(excavated_base_params_t params) {
  excavated_base_params cpp_params{params.H1,    params.H2, params.H3,
                                   params.d,     params.D,  params.alpha1,
                                   params.alpha2};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_excavated_base(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_excavated_base_with_place(excavated_base_params_t params,
                                 pnt3d_t position, dir3d_t direction) {
  excavated_base_params cpp_params{params.H1,    params.H2, params.H3,
                                   params.d,     params.D,  params.alpha1,
                                   params.alpha2};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_excavated_base(cpp_params, cpp_position, cpp_direction))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_step_base(step_base_params_t params) {
  step_base_params cpp_params{params.H,  params.H1, params.H2, params.H3,
                              params.b,  params.B1, params.B2, params.B3,
                              params.L1, params.L2, params.L3, params.N};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_step_base(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_step_base_with_place(step_base_params_t params, pnt3d_t position,
                            dir3d_t direction) {
  step_base_params cpp_params{params.H,  params.H1, params.H2, params.H3,
                              params.b,  params.B1, params.B2, params.B3,
                              params.L1, params.L2, params.L3, params.N};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(create_step_base(
                                cpp_params, cpp_position, cpp_direction))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_step_plate_base(step_plate_base_params_t params) {
  step_plate_base_params cpp_params{
      params.H,  params.H1, params.H2, params.H3,     params.b,      params.L1,
      params.L2, params.B1, params.B2, params.alpha1, params.alpha2, params.N};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_step_plate_base(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_step_plate_base_with_place(step_plate_base_params_t params,
                                  pnt3d_t position, dir3d_t direction) {
  step_plate_base_params cpp_params{
      params.H,  params.H1, params.H2, params.H3,     params.b,      params.L1,
      params.L2, params.B1, params.B2, params.alpha1, params.alpha2, params.N};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_step_plate_base(cpp_params, cpp_position, cpp_direction))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_sloped_base_base(sloped_base_base_params_t params) {
  sloped_base_base_params cpp_params{
      params.H1, params.H2, params.H3, params.b,      params.L1,
      params.L2, params.B1, params.B2, params.alpha1, params.alpha2};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_sloped_base_base(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_sloped_base_base_with_place(sloped_base_base_params_t params,
                                   pnt3d_t position, dir3d_t direction) {
  sloped_base_base_params cpp_params{
      params.H1, params.H2, params.H3, params.b,      params.L1,
      params.L2, params.B1, params.B2, params.alpha1, params.alpha2};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_sloped_base_base(cpp_params, cpp_position, cpp_direction))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_composite_caisson_base(composite_caisson_base_params_t params) {
  composite_caisson_base_params cpp_params{
      params.H1, params.H2, params.H3, params.H4, params.b, params.D,
      params.t,  params.B1, params.B2, params.L1, params.L2};
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(
                                create_composite_caisson_base(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_composite_caisson_base_with_place(composite_caisson_base_params_t params,
                                         pnt3d_t position, dir3d_t direction) {
  composite_caisson_base_params cpp_params{
      params.H1, params.H2, params.H3, params.H4, params.b, params.D,
      params.t,  params.B1, params.B2, params.L1, params.L2};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_composite_caisson_base(
            cpp_params, cpp_position, cpp_direction))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_raft_base(raft_base_params_t params) {
  raft_base_params cpp_params{params.H1, params.H2, params.H3,
                              params.b1, params.b2, params.B1,
                              params.B2, params.L1, params.L2};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_raft_base(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_raft_base_with_place(raft_base_params_t params, pnt3d_t position,
                            dir3d_t direction) {
  raft_base_params cpp_params{params.H1, params.H2, params.H3,
                              params.b1, params.b2, params.B1,
                              params.B2, params.L1, params.L2};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(create_raft_base(
                                cpp_params, cpp_position, cpp_direction))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_direct_buried_base(direct_buried_base_params_t params) {
  direct_buried_base_params cpp_params{params.H1, params.H2, params.d,
                                       params.D,  params.B,  params.t};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_direct_buried_base(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_direct_buried_base_with_place(direct_buried_base_params_t params,
                                     pnt3d_t position, dir3d_t direction) {
  direct_buried_base_params cpp_params{params.H1, params.H2, params.d,
                                       params.D,  params.B,  params.t};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_direct_buried_base(
            cpp_params, cpp_position, cpp_direction))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_steel_sleeve_base(steel_sleeve_base_params_t params) {
  steel_sleeve_base_params cpp_params{
      params.H1, params.H2, params.H3, params.H4, params.d,
      params.D1, params.D2, params.t,  params.B1, params.B2};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_steel_sleeve_base(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_steel_sleeve_base_with_place(steel_sleeve_base_params_t params,
                                    pnt3d_t position, dir3d_t direction) {
  steel_sleeve_base_params cpp_params{
      params.H1, params.H2, params.H3, params.H4, params.d,
      params.D1, params.D2, params.t,  params.B1, params.B2};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_steel_sleeve_base(cpp_params, cpp_position, cpp_direction))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_precast_column_base(precast_column_base_params_t params) {
  precast_column_base_params cpp_params{params.H1, params.H2, params.H3,
                                        params.d,  params.B1, params.B2,
                                        params.L1, params.L2};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_precast_column_base(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_precast_column_base_with_place(precast_column_base_params_t params,
                                      pnt3d_t position, dir3d_t direction) {
  precast_column_base_params cpp_params{params.H1, params.H2, params.H3,
                                        params.d,  params.B1, params.B2,
                                        params.L1, params.L2};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_precast_column_base(
            cpp_params, cpp_position, cpp_direction))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_precast_pinned_base(precast_pinned_base_params_t params) {
  precast_pinned_base_params cpp_params{
      params.H1, params.H2, params.H3, params.d, params.B1, params.B2,
      params.L1, params.L2, params.B,  params.H, params.L};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_precast_pinned_base(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_precast_pinned_base_with_place(precast_pinned_base_params_t params,
                                      pnt3d_t position, dir3d_t direction) {
  precast_pinned_base_params cpp_params{
      params.H1, params.H2, params.H3, params.d, params.B1, params.B2,
      params.L1, params.L2, params.B,  params.H, params.L};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_precast_pinned_base(
            cpp_params, cpp_position, cpp_direction))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_precast_metal_support_base(precast_metal_support_base_params_t params) {
  precast_metal_support_base_params cpp_params{
      params.H1,
      params.H2,
      params.H3,
      params.H4,
      params.b1,
      params.b2,
      params.B1,
      params.B2,
      params.L1,
      params.L2,
      params.S1,
      params.S2,
      params.n1,
      params.n2,
      std::vector<double>(params.HX, params.HX + params.HXCount)};
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(
                                create_precast_metal_support_base(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_precast_metal_support_base_with_place(
    precast_metal_support_base_params_t params, pnt3d_t position,
    dir3d_t direction) {
  precast_metal_support_base_params cpp_params{
      params.H1,
      params.H2,
      params.H3,
      params.H4,
      params.b1,
      params.b2,
      params.B1,
      params.B2,
      params.L1,
      params.L2,
      params.S1,
      params.S2,
      params.n1,
      params.n2,
      std::vector<double>(params.HX, params.HX + params.HXCount)};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_precast_metal_support_base(
            cpp_params, cpp_position, cpp_direction))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_precast_concrete_support_base(
    precast_concrete_support_base_params_t params) {
  precast_concrete_support_base_params cpp_params{
      params.H1, params.H2, params.H3, params.H4, params.H5,
      params.b1, params.b2, params.b3, params.B1, params.B2,
      params.L1, params.L2, params.S1, params.n1};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_precast_concrete_support_base(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_precast_concrete_support_base_with_place(
    precast_concrete_support_base_params_t params, pnt3d_t position,
    dir3d_t direction) {
  precast_concrete_support_base_params cpp_params{
      params.H1, params.H2, params.H3, params.H4, params.H5,
      params.b1, params.b2, params.b3, params.B1, params.B2,
      params.L1, params.L2, params.S1, params.n1};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_precast_concrete_support_base(
            cpp_params, cpp_position, cpp_direction))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_transmission_line(transmission_line_params_t params, pnt3d_t startPoint,
                         pnt3d_t endPoint) {
  transmission_line_params cpp_params{params.ctype,
                                      params.sectionalArea,
                                      params.outsideDiameter,
                                      params.wireWeight,
                                      params.coefficientOfElasticity,
                                      params.expansionCoefficient,
                                      params.ratedStrength};
  gp_Pnt cpp_start(startPoint.x, startPoint.y, startPoint.z);
  gp_Pnt cpp_end(endPoint.x, endPoint.y, endPoint.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_transmission_line(cpp_params, cpp_start, cpp_end))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL pnt3d_t *
sample_transmission_line_points(transmission_line_params_t params,
                                pnt3d_t startPoint, pnt3d_t endPoint,
                                double tessellation, int *out_count) {
  transmission_line_params cppParams{params.ctype,
                                     params.sectionalArea,
                                     params.outsideDiameter,
                                     params.wireWeight,
                                     params.coefficientOfElasticity,
                                     params.expansionCoefficient,
                                     params.ratedStrength};
  gp_Pnt cppStart(startPoint.x, startPoint.y, startPoint.z);
  gp_Pnt cppEnd(endPoint.x, endPoint.y, endPoint.z);

  auto spoints =
      sample_transmission_line(cppParams, cppStart, cppEnd, tessellation);
  return convert_points_to_capi(spoints, out_count);
}

PRIMCAPICALL topo_shape_t *
create_composite_insulator(insulator_composite_params_t params) {
  // 转换复合绝缘子参数
  boost::variant<double, composite_insulator_params> radius;
  if (params.insulator.isComposite) {
    composite_insulator_params comp_params{
        params.insulator.radiusData.compositeParams.majorRadius,
        params.insulator.radiusData.compositeParams.minorRadius,
        params.insulator.radiusData.compositeParams.gap};
    radius = comp_params;
  } else {
    radius = params.insulator.radiusData.radius;
  }

  // 构建主参数结构
  insulator_params cpp_params{
      params.ctype,
      params.subNum,
      params.subType,
      params.splitDistance,
      params.vAngleLeft,
      params.vAngleRight,
      params.uLinkLength,
      params.weight,
      {params.fittingLengths.leftUpper, params.fittingLengths.rightUpper,
       params.fittingLengths.leftLower, params.fittingLengths.rightLower},
      {params.multiLink.count, params.multiLink.spacing,
       static_cast<arrangement_type>(params.multiLink.arrangement)},
      {radius, params.insulator.height, params.insulator.leftCount,
       params.insulator.rightCount,
       static_cast<insulator_material>(params.insulator.material)},
      {params.gradingRing.count, params.gradingRing.position,
       params.gradingRing.height, params.gradingRing.radius},
      static_cast<application_type>(params.application),
      static_cast<string_type>(params.stringType)};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_insulator_string(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_composite_insulator_with_place(insulator_composite_params_t params,
                                      pnt3d_t position, dir3d_t direction) {
  // 转换复合绝缘子参数
  boost::variant<double, composite_insulator_params> radius;
  if (params.insulator.isComposite) {
    composite_insulator_params comp_params{
        params.insulator.radiusData.compositeParams.majorRadius,
        params.insulator.radiusData.compositeParams.minorRadius,
        params.insulator.radiusData.compositeParams.gap};
    radius = comp_params;
  } else {
    radius = params.insulator.radiusData.radius;
  }

  // 构建主参数结构
  insulator_params cpp_params{
      params.ctype,
      params.subNum,
      params.subType,
      params.splitDistance,
      params.vAngleLeft,
      params.vAngleRight,
      params.uLinkLength,
      params.weight,
      {params.fittingLengths.leftUpper, params.fittingLengths.rightUpper,
       params.fittingLengths.leftLower, params.fittingLengths.rightLower},
      {params.multiLink.count, params.multiLink.spacing,
       static_cast<arrangement_type>(params.multiLink.arrangement)},
      {radius, params.insulator.height, params.insulator.leftCount,
       params.insulator.rightCount,
       static_cast<insulator_material>(params.insulator.material)},
      {params.gradingRing.count, params.gradingRing.position,
       params.gradingRing.height, params.gradingRing.radius},
      static_cast<application_type>(params.application),
      static_cast<string_type>(params.stringType)};

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_insulator_string(cpp_params, cpp_position, cpp_direction))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_single_hook_anchor(single_hook_anchor_params_t params) {
  single_hook_anchor_params cpp_params{params.boltDiameter,
                                       params.exposedLength,
                                       params.nutCount,
                                       params.nutHeight,
                                       params.nutOD,
                                       params.washerCount,
                                       params.washerShape,
                                       params.washerSize,
                                       params.washerThickness,
                                       params.anchorLength,
                                       params.hookStraightLength,
                                       params.hookDiameter};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_single_hook_anchor(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_single_hook_anchor_with_place(single_hook_anchor_params_t params,
                                     pnt3d_t position, dir3d_t normal,
                                     dir3d_t xDir) {
  single_hook_anchor_params cpp_params{params.boltDiameter,
                                       params.exposedLength,
                                       params.nutCount,
                                       params.nutHeight,
                                       params.nutOD,
                                       params.washerCount,
                                       params.washerShape,
                                       params.washerSize,
                                       params.washerThickness,
                                       params.anchorLength,
                                       params.hookStraightLength,
                                       params.hookDiameter};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_single_hook_anchor(
            cpp_params, cpp_position, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_triple_hook_anchor(triple_hook_anchor_params_t params) {
  triple_hook_anchor_params cpp_params{params.boltDiameter,
                                       params.exposedLength,
                                       params.nutCount,
                                       params.nutHeight,
                                       params.nutOD,
                                       params.washerCount,
                                       params.washerShape,
                                       params.washerSize,
                                       params.washerThickness,
                                       params.anchorLength,
                                       params.hookStraightLengthA,
                                       params.hookStraightLengthB,
                                       params.hookDiameter,
                                       params.anchorBarDiameter};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_triple_hook_anchor(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_triple_hook_anchor_with_place(triple_hook_anchor_params_t params,
                                     pnt3d_t position, dir3d_t normal,
                                     dir3d_t xDir) {
  triple_hook_anchor_params cpp_params{params.boltDiameter,
                                       params.exposedLength,
                                       params.nutCount,
                                       params.nutHeight,
                                       params.nutOD,
                                       params.washerCount,
                                       params.washerShape,
                                       params.washerSize,
                                       params.washerThickness,
                                       params.anchorLength,
                                       params.hookStraightLengthA,
                                       params.hookStraightLengthB,
                                       params.hookDiameter,
                                       params.anchorBarDiameter};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_triple_hook_anchor(
            cpp_params, cpp_position, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_ribbed_anchor(ribbed_anchor_params_t params) {
  ribbed_anchor_params cpp_params{
      params.boltDiameter,    params.exposedLength,
      params.nutCount,        params.nutHeight,
      params.nutOD,           params.washerCount,
      params.washerShape,     params.washerSize,
      params.washerThickness, params.anchorLength,
      params.basePlateSize,   params.ribTopWidth,
      params.ribBottomWidth,  params.basePlateThickness,
      params.ribHeight,       params.ribThickness};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_ribbed_anchor(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_ribbed_anchor_with_place(ribbed_anchor_params_t params, pnt3d_t position,
                                dir3d_t normal, dir3d_t xDir) {
  ribbed_anchor_params cpp_params{
      params.boltDiameter,    params.exposedLength,
      params.nutCount,        params.nutHeight,
      params.nutOD,           params.washerCount,
      params.washerShape,     params.washerSize,
      params.washerThickness, params.anchorLength,
      params.basePlateSize,   params.ribTopWidth,
      params.ribBottomWidth,  params.basePlateThickness,
      params.ribHeight,       params.ribThickness};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_ribbed_anchor(
            cpp_params, cpp_position, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_nut_anchor(nut_anchor_params_t params) {
  nut_anchor_params cpp_params{params.boltDiameter,
                               params.exposedLength,
                               params.nutCount,
                               params.nutHeight,
                               params.nutOD,
                               params.washerCount,
                               params.washerShape,
                               params.washerSize,
                               params.washerThickness,
                               params.anchorLength,
                               params.basePlateSize,
                               params.basePlateThickness,
                               params.boltToPlateDistance};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_nut_anchor(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_nut_anchor_with_place(nut_anchor_params_t params, pnt3d_t position,
                             dir3d_t normal, dir3d_t xDir) {
  nut_anchor_params cpp_params{params.boltDiameter,
                               params.exposedLength,
                               params.nutCount,
                               params.nutHeight,
                               params.nutOD,
                               params.washerCount,
                               params.washerShape,
                               params.washerSize,
                               params.washerThickness,
                               params.anchorLength,
                               params.basePlateSize,
                               params.basePlateThickness,
                               params.boltToPlateDistance};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_nut_anchor(cpp_params, cpp_position, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_triple_arm_anchor(triple_arm_anchor_params_t params) {
  triple_arm_anchor_params cpp_params{
      params.boltDiameter,  params.exposedLength, params.nutCount,
      params.nutHeight,     params.nutOD,         params.washerCount,
      params.washerShape,   params.washerSize,    params.washerThickness,
      params.anchorLength,  params.armDiameter,   params.armStraightLength,
      params.armBendLength, params.armBendAngle};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_triple_arm_anchor(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_triple_arm_anchor_with_place(triple_arm_anchor_params_t params,
                                    pnt3d_t position, dir3d_t normal,
                                    dir3d_t xDir) {
  triple_arm_anchor_params cpp_params{
      params.boltDiameter,  params.exposedLength, params.nutCount,
      params.nutHeight,     params.nutOD,         params.washerCount,
      params.washerShape,   params.washerSize,    params.washerThickness,
      params.anchorLength,  params.armDiameter,   params.armStraightLength,
      params.armBendLength, params.armBendAngle};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_triple_arm_anchor(
            cpp_params, cpp_position, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_positioning_plate_anchor(positioning_plate_anchor_params_t params) {
  positioning_plate_anchor_params cpp_params{params.boltDiameter,
                                             params.exposedLength,
                                             params.nutCount,
                                             params.nutHeight,
                                             params.nutOD,
                                             params.washerCount,
                                             params.washerShape,
                                             params.washerSize,
                                             params.washerThickness,
                                             params.anchorLength,
                                             params.plateLength,
                                             params.plateThickness,
                                             params.toBaseDistance,
                                             params.toBottomDistance,
                                             params.groutHoleDiameter};
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(
                                create_positioning_plate_anchor(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_positioning_plate_anchor_with_place(
    positioning_plate_anchor_params_t params, pnt3d_t position, dir3d_t normal,
    dir3d_t xDir) {
  positioning_plate_anchor_params cpp_params{params.boltDiameter,
                                             params.exposedLength,
                                             params.nutCount,
                                             params.nutHeight,
                                             params.nutOD,
                                             params.washerCount,
                                             params.washerShape,
                                             params.washerSize,
                                             params.washerThickness,
                                             params.anchorLength,
                                             params.plateLength,
                                             params.plateThickness,
                                             params.toBaseDistance,
                                             params.toBottomDistance,
                                             params.groutHoleDiameter};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_positioning_plate_anchor(
            cpp_params, cpp_position, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_stub_angle(stub_angle_params_t params) {
  stub_angle_params cpp_params{params.legWidth, params.thickness, params.slope,
                               params.exposedLength, params.anchorLength};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_stub_angle(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_stub_angle_with_place(stub_angle_params_t params, pnt3d_t position,
                             dir3d_t normal, dir3d_t xDir) {
  stub_angle_params cpp_params{params.legWidth, params.thickness, params.slope,
                               params.exposedLength, params.anchorLength};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_stub_angle(cpp_params, cpp_position, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_stub_tube(stub_tube_params_t params) {
  stub_tube_params cpp_params{params.diameter, params.thickness, params.slope,
                              params.exposedLength, params.anchorLength};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_stub_tube(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_stub_tube_with_place(stub_tube_params_t params, pnt3d_t position,
                            dir3d_t normal, dir3d_t xDir) {
  stub_tube_params cpp_params{params.diameter, params.thickness, params.slope,
                              params.exposedLength, params.anchorLength};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_stub_tube(cpp_params, cpp_position, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_cable_wire(cable_wire_params_t params) {
  try {
    // 将C数组转换为C++ vector
    std::vector<gp_Pnt> points;
    for (int i = 0; i < params.numPoints; ++i) {
      points.push_back(
          gp_Pnt(params.points[i].x, params.points[i].y, params.points[i].z));
    }

    // 创建C++参数结构
    cable_wire_params cpp_params{.points = points,
                                 .outsideDiameter = params.outsideDiameter};

    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cable_wire(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_cable_wire_with_place(cable_wire_params_t params, pnt3d_t position,
                             dir3d_t direction, dir3d_t upDirection) {
  try {
    // 将C数组转换为C++ vector
    std::vector<gp_Pnt> points;
    for (int i = 0; i < params.numPoints; ++i) {
      points.push_back(
          gp_Pnt(params.points[i].x, params.points[i].y, params.points[i].z));
    }

    // 创建C++参数结构
    cable_wire_params cpp_params{.points = points,
                                 .outsideDiameter = params.outsideDiameter};

    // 转换位置和方向参数
    gp_Pnt cpp_position(position.x, position.y, position.z);
    gp_Dir cpp_direction(direction.x, direction.y, direction.z);
    gp_Dir cpp_upDirection(upDirection.x, upDirection.y, upDirection.z);

    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cable_wire(
            cpp_params, cpp_position, cpp_direction, cpp_upDirection))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_pole_tower(pole_tower_params_t params) {
  pole_tower_params cpp_params;

  // 转换呼高信息
  std::vector<pole_tower_height> cpp_heights;
  for (int i = 0; i < params.heightCount; i++) {
    pole_tower_height height;
    height.value = params.heights[i].value;
    height.bodyId = params.heights[i].bodyId;
    height.legId = params.heights[i].legId;
    cpp_heights.push_back(height);
  }
  cpp_params.heights = cpp_heights;

  // 转换本体信息
  std::vector<pole_tower_body> cpp_bodies;
  for (int i = 0; i < params.bodyCount; i++) {
    pole_tower_body body;
    body.id = params.bodies[i].id;
    body.height = params.bodies[i].height;

    // 转换本体节点
    for (int j = 0; j < params.bodies[i].nodeCount; j++) {
      pole_tower_node node;
      node.id = params.bodies[i].nodes[j].id;
      node.position = gp_Pnt(params.bodies[i].nodes[j].position.x,
                             params.bodies[i].nodes[j].position.y,
                             params.bodies[i].nodes[j].position.z);
      body.nodes.push_back(node);
    }

    // 转换接腿信息
    for (int k = 0; k < params.bodies[i].legCount; k++) {
      pole_tower_leg leg;
      leg.id = params.bodies[i].legs[k].id;
      leg.commonHeight = params.bodies[i].legs[k].commonHeight;
      leg.specificHeight = params.bodies[i].legs[k].specificHeight;

      // 转换接腿节点
      for (int m = 0; m < params.bodies[i].legs[k].nodeCount; m++) {
        pole_tower_node node;
        node.id = params.bodies[i].legs[k].nodes[m].id;
        node.position = gp_Pnt(params.bodies[i].legs[k].nodes[m].position.x,
                               params.bodies[i].legs[k].nodes[m].position.y,
                               params.bodies[i].legs[k].nodes[m].position.z);
        leg.nodes.push_back(node);
      }
      body.legs.push_back(leg);
    }
    cpp_bodies.push_back(body);
  }
  cpp_params.bodies = cpp_bodies;

  // 转换杆件信息
  std::vector<pole_tower_member> cpp_members;
  for (int i = 0; i < params.memberCount; i++) {
    pole_tower_member member;
    member.id = params.members[i].id;
    member.startNodeId = params.members[i].startNodeId;
    member.endNodeId = params.members[i].endNodeId;
    member.type = static_cast<member_type>(params.members[i].ctype);
    member.specification = params.members[i].specification;
    member.material = params.members[i].material;
    member.xDirection =
        gp_Dir(params.members[i].xDirection.x, params.members[i].xDirection.y,
               params.members[i].xDirection.z);
    member.yDirection =
        gp_Dir(params.members[i].yDirection.x, params.members[i].yDirection.y,
               params.members[i].yDirection.z);
    member.end1Diameter = params.members[i].end1Diameter;
    member.end2Diameter = params.members[i].end2Diameter;
    member.thickness = params.members[i].thickness;
    member.sides = params.members[i].sides;
    cpp_members.push_back(member);
  }
  cpp_params.members = cpp_members;

  // 转换挂点信息
  std::vector<pole_tower_attachment> cpp_attachments;
  for (int i = 0; i < params.attachmentCount; i++) {
    pole_tower_attachment attachment;
    attachment.name = params.attachments[i].name;
    attachment.type = static_cast<attachment_type>(params.attachments[i].ctype);
    attachment.position = gp_Pnt(params.attachments[i].position.x,
                                 params.attachments[i].position.y,
                                 params.attachments[i].position.z);
    cpp_attachments.push_back(attachment);
  }
  cpp_params.attachments = cpp_attachments;
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_pole_tower(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_pole_tower_with_place(pole_tower_params_t params, pnt3d_t position,
                             dir3d_t normal, dir3d_t xDir) {
  pole_tower_params cpp_params;

  // 转换呼高信息
  std::vector<pole_tower_height> cpp_heights;
  for (int i = 0; i < params.heightCount; i++) {
    pole_tower_height height;
    height.value = params.heights[i].value;
    height.bodyId = params.heights[i].bodyId;
    height.legId = params.heights[i].legId;
    cpp_heights.push_back(height);
  }
  cpp_params.heights = cpp_heights;

  // 转换本体信息
  std::vector<pole_tower_body> cpp_bodies;
  for (int i = 0; i < params.bodyCount; i++) {
    pole_tower_body body;
    body.id = params.bodies[i].id;
    body.height = params.bodies[i].height;

    // 转换本体节点
    for (int j = 0; j < params.bodies[i].nodeCount; j++) {
      pole_tower_node node;
      node.id = params.bodies[i].nodes[j].id;
      node.position = gp_Pnt(params.bodies[i].nodes[j].position.x,
                             params.bodies[i].nodes[j].position.y,
                             params.bodies[i].nodes[j].position.z);
      body.nodes.push_back(node);
    }

    // 转换接腿信息
    for (int k = 0; k < params.bodies[i].legCount; k++) {
      pole_tower_leg leg;
      leg.id = params.bodies[i].legs[k].id;
      leg.commonHeight = params.bodies[i].legs[k].commonHeight;
      leg.specificHeight = params.bodies[i].legs[k].specificHeight;

      // 转换接腿节点
      for (int m = 0; m < params.bodies[i].legs[k].nodeCount; m++) {
        pole_tower_node node;
        node.id = params.bodies[i].legs[k].nodes[m].id;
        node.position = gp_Pnt(params.bodies[i].legs[k].nodes[m].position.x,
                               params.bodies[i].legs[k].nodes[m].position.y,
                               params.bodies[i].legs[k].nodes[m].position.z);
        leg.nodes.push_back(node);
      }
      body.legs.push_back(leg);
    }
    cpp_bodies.push_back(body);
  }
  cpp_params.bodies = cpp_bodies;

  // 转换杆件信息
  std::vector<pole_tower_member> cpp_members;
  for (int i = 0; i < params.memberCount; i++) {
    pole_tower_member member;
    member.id = params.members[i].id;
    member.startNodeId = params.members[i].startNodeId;
    member.endNodeId = params.members[i].endNodeId;
    member.type = static_cast<member_type>(params.members[i].ctype);
    member.specification = params.members[i].specification;
    member.material = params.members[i].material;
    member.xDirection =
        gp_Dir(params.members[i].xDirection.x, params.members[i].xDirection.y,
               params.members[i].xDirection.z);
    member.yDirection =
        gp_Dir(params.members[i].yDirection.x, params.members[i].yDirection.y,
               params.members[i].yDirection.z);
    member.end1Diameter = params.members[i].end1Diameter;
    member.end2Diameter = params.members[i].end2Diameter;
    member.thickness = params.members[i].thickness;
    member.sides = params.members[i].sides;
    cpp_members.push_back(member);
  }
  cpp_params.members = cpp_members;

  // 转换挂点信息
  std::vector<pole_tower_attachment> cpp_attachments;
  for (int i = 0; i < params.attachmentCount; i++) {
    pole_tower_attachment attachment;
    attachment.name = params.attachments[i].name;
    attachment.type = static_cast<attachment_type>(params.attachments[i].ctype);
    attachment.position = gp_Pnt(params.attachments[i].position.x,
                                 params.attachments[i].position.y,
                                 params.attachments[i].position.z);
    cpp_attachments.push_back(attachment);
  }
  cpp_params.attachments = cpp_attachments;
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_pole_tower(cpp_params, cpp_position, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_cable_joint(cable_joint_params_t params) {
  cable_joint_params cpp_params{params.length, params.outerDiameter,
                                params.terminalLength, params.innerDiameter};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cable_joint(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_cable_joint_with_place(cable_joint_params_t params, pnt3d_t position,
                              dir3d_t direction, dir3d_t xDir) {
  cable_joint_params cpp_params{params.length, params.outerDiameter,
                                params.terminalLength, params.innerDiameter};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cable_joint(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_optical_fiber_box(optical_fiber_box_params_t params) {
  optical_fiber_box_params cpp_params{params.length, params.height,
                                      params.width};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_optical_fiber_box(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_optical_fiber_box_with_place(optical_fiber_box_params_t params,
                                    pnt3d_t position, dir3d_t direction,
                                    dir3d_t xDir) {
  optical_fiber_box_params cpp_params{params.length, params.height,
                                      params.width};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_optical_fiber_box(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_cable_terminal(cable_terminal_params_t params) {
  cable_terminal_params cpp_params{
      .sort = params.sort,
      .height = params.height,
      .topDiameter = params.topDiameter,
      .bottomDiameter = params.bottomDiameter,
      .tailDiameter = params.tailDiameter,
      .tailHeight = params.tailHeight,
      .skirtCount = params.skirtCount,
      .upperSkirtTopDiameter = params.upperSkirtTopDiameter,
      .upperSkirtBottomDiameter = params.upperSkirtBottomDiameter,
      .lowerSkirtTopDiameter = params.lowerSkirtTopDiameter,
      .lowerSkirtBottomDiameter = params.lowerSkirtBottomDiameter,
      .skirtSectionHeight = params.skirtSectionHeight,
      .upperTerminalLength = params.upperTerminalLength,
      .upperTerminalDiameter = params.upperTerminalDiameter,
      .lowerTerminalLength = params.lowerTerminalLength,
      .lowerTerminalDiameter = params.lowerTerminalDiameter,
      .hole1Diameter = params.hole1Diameter,
      .hole2Diameter = params.hole2Diameter,
      .hole1Distance = params.hole1Distance,
      .holeSpacing = params.holeSpacing,
      .flangeHoleDiameter = params.flangeHoleDiameter,
      .flangeHoleSpacing = params.flangeHoleSpacing,
      .flangeWidth = params.flangeWidth,
      .flangeCenterHoleRadius = params.flangeCenterHoleRadius,
      .flangeChamferRadius = params.flangeChamferRadius,
      .flangeOpeningWidth = params.flangeOpeningWidth,
      .flangeBoltHeight = params.flangeBoltHeight,
  };
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cable_terminal(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_cable_terminal_with_place(cable_terminal_params_t params,
                                 pnt3d_t position, dir3d_t direction) {
  cable_terminal_params cpp_params{
      .sort = params.sort,
      .height = params.height,
      .topDiameter = params.topDiameter,
      .bottomDiameter = params.bottomDiameter,
      .tailDiameter = params.tailDiameter,
      .tailHeight = params.tailHeight,
      .skirtCount = params.skirtCount,
      .upperSkirtTopDiameter = params.upperSkirtTopDiameter,
      .upperSkirtBottomDiameter = params.upperSkirtBottomDiameter,
      .lowerSkirtTopDiameter = params.lowerSkirtTopDiameter,
      .lowerSkirtBottomDiameter = params.lowerSkirtBottomDiameter,
      .skirtSectionHeight = params.skirtSectionHeight,
      .upperTerminalLength = params.upperTerminalLength,
      .upperTerminalDiameter = params.upperTerminalDiameter,
      .lowerTerminalLength = params.lowerTerminalLength,
      .lowerTerminalDiameter = params.lowerTerminalDiameter,
      .hole1Diameter = params.hole1Diameter,
      .hole2Diameter = params.hole2Diameter,
      .hole1Distance = params.hole1Distance,
      .holeSpacing = params.holeSpacing,
      .flangeHoleDiameter = params.flangeHoleDiameter,
      .flangeHoleSpacing = params.flangeHoleSpacing,
      .flangeWidth = params.flangeWidth,
      .flangeCenterHoleRadius = params.flangeCenterHoleRadius,
      .flangeChamferRadius = params.flangeChamferRadius,
      .flangeOpeningWidth = params.flangeOpeningWidth,
      .flangeBoltHeight = params.flangeBoltHeight,
  };
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_cable_terminal(cpp_params, cpp_position, cpp_direction))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_cable_accessory(cable_accessory_params_t params) {
  cable_accessory_params cpp_params{static_cast<cable_box_type>(params.ctype),
                                    params.length,
                                    params.width,
                                    params.height,
                                    params.portCount,
                                    params.portDiameter,
                                    params.backPanelDistance,
                                    params.sidePanelDistance};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cable_accessory(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_cable_accessory_with_place(cable_accessory_params_t params,
                                  pnt3d_t position, dir3d_t normal,
                                  dir3d_t xDir) {
  cable_accessory_params cpp_params{static_cast<cable_box_type>(params.ctype),
                                    params.length,
                                    params.width,
                                    params.height,
                                    params.portCount,
                                    params.portDiameter,
                                    params.backPanelDistance,
                                    params.sidePanelDistance};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cable_accessory(
            cpp_params, cpp_position, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_cable_bracket(cable_bracket_params_t params) {
  cable_bracket_params cpp_params{params.length,       params.rootHeight,
                                  params.rootWidth,    params.width,
                                  params.topThickness, params.rootThickness};

  if (params.columnMountCount > 0) {
    for (int i = 0; i < params.columnMountCount; i++) {
      pnt3d_t p = params.columnMountPoints[i];
      cpp_params.columnMountPoints.push_back(gp_Pnt(p.x, p.y, p.z));
    }
  }

  if (params.clampMountCount > 0) {
    for (int i = 0; i < params.clampMountCount; i++) {
      pnt3d_t p = params.clampMountPoints[i];
      cpp_params.clampMountPoints.push_back(gp_Pnt(p.x, p.y, p.z));
    }
  }
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cable_bracket(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_cable_bracket_with_place(cable_bracket_params_t params, pnt3d_t position,
                                dir3d_t normal, dir3d_t xDir) {
  cable_bracket_params cpp_params{params.length,       params.rootHeight,
                                  params.rootWidth,    params.width,
                                  params.topThickness, params.rootThickness};

  if (params.columnMountCount > 0) {
    for (int i = 0; i < params.columnMountCount; i++) {
      pnt3d_t p = params.columnMountPoints[i];
      cpp_params.columnMountPoints.push_back(gp_Pnt(p.x, p.y, p.z));
    }
  }

  if (params.clampMountCount > 0) {
    for (int i = 0; i < params.clampMountCount; i++) {
      pnt3d_t p = params.clampMountPoints[i];
      cpp_params.clampMountPoints.push_back(gp_Pnt(p.x, p.y, p.z));
    }
  }

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cable_bracket(
            cpp_params, cpp_position, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_cable_clamp(cable_clamp_params_t params) {
  cable_clamp_params cpp_params{static_cast<cable_clamp_type>(params.ctype),
                                params.diameter, params.thickness,
                                params.width};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cable_clamp(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_cable_clamp_with_place(cable_clamp_params_t params, pnt3d_t position,
                              dir3d_t normal, dir3d_t xDir) {
  cable_clamp_params cpp_params{static_cast<cable_clamp_type>(params.ctype),
                                params.diameter, params.thickness,
                                params.width};

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cable_clamp(
            cpp_params, cpp_position, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_cable_pole(cable_pole_params_t params) {
  cable_pole_params cpp_params{params.specification ? params.specification : "",
                               params.length,
                               params.radius,
                               params.arcAngle,
                               params.width,
                               params.fixedLegLength,
                               params.fixedLegWidth,
                               params.thickness};

  if (params.mountCount > 0) {
    for (int i = 0; i < params.mountCount; i++) {
      pnt3d_t p = params.mountPoints[i];
      cpp_params.mountPoints.push_back(gp_Pnt(p.x, p.y, p.z));
    }
  }
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cable_pole(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_cable_pole_with_place(cable_pole_params_t params, pnt3d_t position,
                             dir3d_t direction) {
  cable_pole_params cpp_params{params.specification ? params.specification : "",
                               params.length,
                               params.radius,
                               params.arcAngle,
                               params.width,
                               params.fixedLegLength,
                               params.fixedLegWidth,
                               params.thickness};

  if (params.mountCount > 0) {
    for (int i = 0; i < params.mountCount; i++) {
      pnt3d_t p = params.mountPoints[i];
      cpp_params.mountPoints.push_back(gp_Pnt(p.x, p.y, p.z));
    }
  }

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(create_cable_pole(
                                cpp_params, cpp_position, cpp_direction))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_ground_flat_iron(ground_flat_iron_params_t params) {
  ground_flat_iron_params cpp_params{params.length, params.height,
                                     params.thickness};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_ground_flat_iron(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_ground_flat_iron_with_place(ground_flat_iron_params_t params,
                                   pnt3d_t position, dir3d_t normal,
                                   dir3d_t xDir) {
  ground_flat_iron_params cpp_params{params.length, params.height,
                                     params.thickness};

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_ground_flat_iron(
            cpp_params, cpp_position, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_embedded_part(embedded_part_params_t params) {
  embedded_part_params cpp_params{params.length, params.radius, params.height,
                                  params.materialRadius, params.lowerLength};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_embedded_part(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_embedded_part_with_place(embedded_part_params_t params, pnt3d_t position,
                                dir3d_t normal, dir3d_t xDir) {
  embedded_part_params cpp_params{params.length, params.radius, params.height,
                                  params.materialRadius, params.lowerLength};

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_embedded_part(
            cpp_params, cpp_position, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_u_shaped_ring(u_shaped_ring_params_t params) {
  u_shaped_ring_params cpp_params{params.thickness, params.height,
                                  params.radius, params.length};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_u_shaped_ring(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_u_shaped_ring_with_place(u_shaped_ring_params_t params, pnt3d_t position,
                                dir3d_t normal, dir3d_t xDir) {
  u_shaped_ring_params cpp_params{params.thickness, params.height,
                                  params.radius, params.length};

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_u_shaped_ring(
            cpp_params, cpp_position, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_lifting_eye(lifting_eye_params_t params) {
  lifting_eye_params cpp_params{params.height, params.ringRadius,
                                params.pipeDiameter};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_lifting_eye(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_lifting_eye_with_place(lifting_eye_params_t params, pnt3d_t position,
                              dir3d_t normal, dir3d_t xDir) {
  lifting_eye_params cpp_params{params.height, params.ringRadius,
                                params.pipeDiameter};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_lifting_eye(
            cpp_params, cpp_position, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_corner_well(corner_well_params_t params) {
  corner_well_params cpp_params{
      params.leftLength,       params.rightLength,     params.width,
      params.height,           params.topThickness,    params.bottomThickness,
      params.wallThickness,    params.angle,           params.cornerRadius,
      params.cushionExtension, params.cushionThickness};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_corner_well(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_corner_well_with_place(corner_well_params_t params, pnt3d_t position,
                              dir3d_t direction, dir3d_t xDir) {
  corner_well_params cpp_params{
      params.leftLength,       params.rightLength,     params.width,
      params.height,           params.topThickness,    params.bottomThickness,
      params.wallThickness,    params.angle,           params.cornerRadius,
      params.cushionExtension, params.cushionThickness};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_corner_well(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_tunnel_well(tunnel_well_params_t params) {
  tunnel_well_params cpp_params{
      static_cast<tunnel_well_type>(params.ctype),
      params.length,
      params.width,
      params.height,
      params.radius,
      params.topThickness,
      params.bottomThickness,
      static_cast<connection_section_style>(params.leftSectionType),
      params.leftLength,
      params.leftWidth,
      params.leftHeight,
      params.leftArcHeight,
      static_cast<connection_section_style>(params.rightSectionType),
      params.rightLength,
      params.rightWidth,
      params.rightHeight,
      params.rightArcHeight,
      params.outerWallThickness,
      params.innerWallThickness,
      params.cushionExtension,
      params.cushionThickness};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_tunnel_well(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_tunnel_well_with_place(tunnel_well_params_t params, pnt3d_t position,
                              dir3d_t direction, dir3d_t xDir) {
  tunnel_well_params cpp_params{
      static_cast<tunnel_well_type>(params.ctype),
      params.length,
      params.width,
      params.height,
      params.radius,
      params.topThickness,
      params.bottomThickness,
      static_cast<connection_section_style>(params.leftSectionType),
      params.leftLength,
      params.leftWidth,
      params.leftHeight,
      params.leftArcHeight,
      static_cast<connection_section_style>(params.rightSectionType),
      params.rightLength,
      params.rightWidth,
      params.rightHeight,
      params.rightArcHeight,
      params.outerWallThickness,
      params.innerWallThickness,
      params.cushionExtension,
      params.cushionThickness};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_tunnel_well(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_three_way_well(three_way_well_params_t params) {
  three_way_well_params cpp_params{
      static_cast<three_way_well_type>(params.ctype),
      static_cast<corner_style>(params.cornerType),
      static_cast<shaft_style>(params.shaftType),
      params.length,
      params.width,
      params.height,
      params.shaftRadius,
      params.cornerRadius,
      params.cornerLength,
      params.cornerWidth,
      params.angle,
      params.branchLength,
      params.branchLeftLength,
      params.branchWidth,
      params.topThickness,
      params.bottomThickness,
      static_cast<connection_section_style>(params.leftSectionStyle),
      params.leftSectionLength,
      params.leftSectionWidth,
      params.leftSectionHeight,
      params.leftSectionArcHeight,
      static_cast<connection_section_style>(params.rightSectionStyle),
      params.rightSectionLength,
      params.rightSectionWidth,
      params.rightSectionHeight,
      params.rightSectionArcHeight,
      static_cast<connection_section_style>(params.branchSectionStyle),
      params.branchSectionLength,
      params.branchSectionWidth,
      params.branchSectionHeight,
      params.branchSectionArcHeight,
      params.outerWallThickness,
      params.innerWallThickness,
      params.isDoubleShaft,
      params.doubleShaftSpacing,
      params.outerWallExtension,
      params.innerWallExtension,
      params.cushionExtension,
      params.cushionThickness,
      params.innerBottomThickness,
      params.outerBottomThickness};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_three_way_well(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_three_way_well_with_place(three_way_well_params_t params,
                                 pnt3d_t position, dir3d_t mainDirection,
                                 dir3d_t branchDirection) {
  three_way_well_params cpp_params{
      static_cast<three_way_well_type>(params.ctype),
      static_cast<corner_style>(params.cornerType),
      static_cast<shaft_style>(params.shaftType),
      params.length,
      params.width,
      params.height,
      params.shaftRadius,
      params.cornerRadius,
      params.cornerLength,
      params.cornerWidth,
      params.angle,
      params.branchLength,
      params.branchLeftLength,
      params.branchWidth,
      params.topThickness,
      params.bottomThickness,
      static_cast<connection_section_style>(params.leftSectionStyle),
      params.leftSectionLength,
      params.leftSectionWidth,
      params.leftSectionHeight,
      params.leftSectionArcHeight,
      static_cast<connection_section_style>(params.rightSectionStyle),
      params.rightSectionLength,
      params.rightSectionWidth,
      params.rightSectionHeight,
      params.rightSectionArcHeight,
      static_cast<connection_section_style>(params.branchSectionStyle),
      params.branchSectionLength,
      params.branchSectionWidth,
      params.branchSectionHeight,
      params.branchSectionArcHeight,
      params.outerWallThickness,
      params.innerWallThickness,
      params.isDoubleShaft,
      params.doubleShaftSpacing,
      params.outerWallExtension,
      params.innerWallExtension,
      params.cushionExtension,
      params.cushionThickness,
      params.innerBottomThickness,
      params.outerBottomThickness};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_mainDir(mainDirection.x, mainDirection.y, mainDirection.z);
  gp_Dir cpp_branchDir(branchDirection.x, branchDirection.y, branchDirection.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_three_way_well(
            cpp_params, cpp_position, cpp_mainDir, cpp_branchDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_four_way_well(four_way_well_params_t params) {
  four_way_well_params cpp_params{
      static_cast<four_way_well_type>(params.ctype),
      params.length,
      params.width,
      params.height,
      params.shaftRadius,
      static_cast<corner_style>(params.cornerStyle),
      params.cornerRadius,
      params.cornerLength,
      params.cornerWidth,
      params.branchLength,
      params.branchWidth,
      params.topThickness,
      params.bottomThickness,
      {static_cast<connection_section_style>(params.leftSection.sectionType),
       params.leftSection.length, params.leftSection.width,
       params.leftSection.height, params.leftSection.arcHeight},
      {static_cast<connection_section_style>(params.rightSection.sectionType),
       params.rightSection.length, params.rightSection.width,
       params.rightSection.height, params.rightSection.arcHeight},
      {static_cast<connection_section_style>(params.branchSection1.sectionType),
       params.branchSection1.length, params.branchSection1.width,
       params.branchSection1.height, params.branchSection1.arcHeight},
      {static_cast<connection_section_style>(params.branchSection2.sectionType),
       params.branchSection2.length, params.branchSection2.width,
       params.branchSection2.height, params.branchSection2.arcHeight},
      params.outerWallThickness,
      params.innerWallThickness,
      params.cushionExtension,
      params.cushionThickness};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_four_way_well(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_four_way_well_with_place(four_way_well_params_t params, pnt3d_t position,
                                dir3d_t direction, dir3d_t xDirection) {
  four_way_well_params cpp_params{
      static_cast<four_way_well_type>(params.ctype),
      params.length,
      params.width,
      params.height,
      params.shaftRadius,
      static_cast<corner_style>(params.cornerStyle),
      params.cornerRadius,
      params.cornerLength,
      params.cornerWidth,
      params.branchLength,
      params.branchWidth,
      params.topThickness,
      params.bottomThickness,
      {static_cast<connection_section_style>(params.leftSection.sectionType),
       params.leftSection.length, params.leftSection.width,
       params.leftSection.height, params.leftSection.arcHeight},
      {static_cast<connection_section_style>(params.rightSection.sectionType),
       params.rightSection.length, params.rightSection.width,
       params.rightSection.height, params.rightSection.arcHeight},
      {static_cast<connection_section_style>(params.branchSection1.sectionType),
       params.branchSection1.length, params.branchSection1.width,
       params.branchSection1.height, params.branchSection1.arcHeight},
      {static_cast<connection_section_style>(params.branchSection2.sectionType),
       params.branchSection2.length, params.branchSection2.width,
       params.branchSection2.height, params.branchSection2.arcHeight},
      params.outerWallThickness,
      params.innerWallThickness,
      params.cushionExtension,
      params.cushionThickness};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDirection.x, xDirection.y, xDirection.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_four_way_well(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

// 通道采样函数实现
PRIMCAPICALL pnt3d_t *sample_channel_points(const channel_point_t *points,
                                            int point_count,
                                            double tessellation,
                                            int *out_count) {
  // 参数检查
  if (!points || !out_count || point_count <= 0) {
    return nullptr;
  }

  // 转换输入数据
  std::vector<channel_point> cpp_points;
  for (int i = 0; i < point_count; ++i) {
    channel_point pt;
    pt.position = gp_Pnt(points[i].position.x, points[i].position.y,
                         points[i].position.z);
    pt.type = static_cast<channel_point_type>(points[i].ctype);
    cpp_points.push_back(pt);
  }

  // 调用C++函数
  auto sampled_points = sample_channel_points(cpp_points, tessellation);

  // 转换输出结果
  *out_count = static_cast<int>(sampled_points.size());
  pnt3d_t *result = new pnt3d_t[sampled_points.size()];
  for (size_t i = 0; i < sampled_points.size(); ++i) {
    result[i].x = sampled_points[i].X();
    result[i].y = sampled_points[i].Y();
    result[i].z = sampled_points[i].Z();
  }

  return result;
}

PRIMCAPICALL topo_shape_t *create_pipe_row(pipe_row_params_t params) {
  pipe_row_params cpp_params{static_cast<pipe_row_type>(params.pipeType),
                             params.hasEnclosure,
                             params.enclosureWidth,
                             params.enclosureHeight,
                             params.baseExtension,
                             params.baseThickness,
                             params.cushionExtension,
                             params.cushionThickness,
                             {},
                             {},
                             {},
                             params.pullPipeInnerDiameter,
                             params.pullPipeThickness,
                             {}};

  if (params.pipeCount > 0) {
    for (int i = 0; i < params.pipeCount; i++) {
      cpp_params.pipePositions.push_back(
          gp_Pnt2d(params.pipePositions[i].x, params.pipePositions[i].y));
      cpp_params.pipeInnerDiameters.push_back(params.pipeInnerDiameters[i]);
      cpp_params.pipeWallThicknesses.push_back(params.pipeWallThicknesses[i]);
    }
  }

  if (params.pointCount > 0) {
    for (int i = 0; i < params.pointCount; i++) {
      cpp_params.points.push_back(
          {gp_Pnt(params.points[i].position.x, params.points[i].position.y,
                  params.points[i].position.z),
           static_cast<channel_point_type>(params.points[i].ctype)});
    }
  }
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_pipe_row(cpp_params))};

  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_pipe_row_with_place(pipe_row_params_t params,
                                                      pnt3d_t position,
                                                      dir3d_t normal,
                                                      dir3d_t xDir) {
  pipe_row_params cpp_params{static_cast<pipe_row_type>(params.pipeType),
                             params.hasEnclosure,
                             params.enclosureWidth,
                             params.enclosureHeight,
                             params.baseExtension,
                             params.baseThickness,
                             params.cushionExtension,
                             params.cushionThickness,
                             {},
                             {},
                             {},
                             params.pullPipeInnerDiameter,
                             params.pullPipeThickness,
                             {}};

  if (params.pipeCount > 0) {
    for (int i = 0; i < params.pipeCount; i++) {
      cpp_params.pipePositions.push_back(
          gp_Pnt2d(params.pipePositions[i].x, params.pipePositions[i].y));
      cpp_params.pipeInnerDiameters.push_back(params.pipeInnerDiameters[i]);
      cpp_params.pipeWallThicknesses.push_back(params.pipeWallThicknesses[i]);
    }
  }

  if (params.pointCount > 0) {
    for (int i = 0; i < params.pointCount; i++) {
      cpp_params.points.push_back(
          {gp_Pnt(params.points[i].position.x, params.points[i].position.y,
                  params.points[i].position.z),
           static_cast<channel_point_type>(params.points[i].ctype)});
    }
  }

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_pipe_row(cpp_params, cpp_position, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_cable_trench(cable_trench_params_t params) {
  cable_trench_params cpp_params{params.width,
                                 params.height,
                                 params.coverWidth,
                                 params.coverThickness,
                                 params.baseExtension,
                                 params.baseThickness,
                                 params.cushionExtension,
                                 params.cushionThickness,
                                 params.wallThickness,
                                 params.wallThickness2,
                                 {}};

  if (params.pointCount > 0) {
    for (int i = 0; i < params.pointCount; i++) {
      cpp_params.points.push_back(
          {gp_Pnt(params.points[i].position.x, params.points[i].position.y,
                  params.points[i].position.z),
           static_cast<channel_point_type>(params.points[i].ctype)});
    }
  }
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cable_trench(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_cable_trench_with_place(cable_trench_params_t params, pnt3d_t position,
                               dir3d_t direction, dir3d_t xDir) {
  cable_trench_params cpp_params{params.width,
                                 params.height,
                                 params.coverWidth,
                                 params.coverThickness,
                                 params.baseExtension,
                                 params.baseThickness,
                                 params.cushionExtension,
                                 params.cushionThickness,
                                 params.wallThickness,
                                 params.wallThickness2,
                                 {}};

  if (params.pointCount > 0) {
    for (int i = 0; i < params.pointCount; i++) {
      cpp_params.points.push_back(
          {gp_Pnt(params.points[i].position.x, params.points[i].position.y,
                  params.points[i].position.z),
           static_cast<channel_point_type>(params.points[i].ctype)});
    }
  }

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cable_trench(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_cable_tunnel(cable_tunnel_params_t params) {
  cable_tunnel_params cpp_params{
      static_cast<connection_section_style>(params.style),
      params.width,
      params.height,
      params.topThickness,
      params.bottomThickness,
      params.outerWallThickness,
      params.innerWallThickness,
      params.arcHeight,
      params.bottomPlatformHeight,
      params.cushionExtension,
      params.cushionThickness,
      {}};

  if (params.pointCount > 0) {
    for (int i = 0; i < params.pointCount; i++) {
      cpp_params.points.push_back(
          {gp_Pnt(params.points[i].position.x, params.points[i].position.y,
                  params.points[i].position.z),
           static_cast<channel_point_type>(params.points[i].ctype)});
    }
  }
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cable_tunnel(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_cable_tunnel_with_place(cable_tunnel_params_t params, pnt3d_t position,
                               dir3d_t direction, dir3d_t xDir) {
  cable_tunnel_params cpp_params{
      static_cast<connection_section_style>(params.style),
      params.width,
      params.height,
      params.topThickness,
      params.bottomThickness,
      params.outerWallThickness,
      params.innerWallThickness,
      params.arcHeight,
      params.bottomPlatformHeight,
      params.cushionExtension,
      params.cushionThickness,
      {}};

  if (params.pointCount > 0) {
    for (int i = 0; i < params.pointCount; i++) {
      cpp_params.points.push_back(
          {gp_Pnt(params.points[i].position.x, params.points[i].position.y,
                  params.points[i].position.z),
           static_cast<channel_point_type>(params.points[i].ctype)});
    }
  }

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cable_tunnel(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_cable_tray(cable_tray_params_t params) {
  cable_tray_params cpp_params{static_cast<cable_tray_style>(params.style),
                               params.columnDiameter,
                               params.columnHeight,
                               params.span,
                               params.width,
                               params.height,
                               params.topPlateHeight,
                               params.arcHeight,
                               params.wallThickness,
                               params.hasProtectionPlate != 0};

  if (params.pipeCount > 0) {
    for (int i = 0; i < params.pipeCount; i++) {
      pnt2d_t pos = params.pipePositions[i];
      cpp_params.pipePositions.push_back(gp_Pnt2d(pos.x, pos.y));
      cpp_params.pipeInnerDiameters.push_back(params.pipeInnerDiameters[i]);
      cpp_params.pipeWallThicknesses.push_back(params.pipeWallThicknesses[i]);
    }
  }

  if (params.pointCount > 0) {
    for (int i = 0; i < params.pointCount; i++) {
      channel_point_t point = params.points[i];
      cpp_params.points.push_back(channel_point{
          gp_Pnt(point.position.x, point.position.y, point.position.z),
          static_cast<channel_point_type>(point.ctype)});
    }
  }
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cable_tray(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_cable_tray_with_place(cable_tray_params_t params, pnt3d_t position,
                             dir3d_t direction, dir3d_t xDir) {
  cable_tray_params cpp_params{static_cast<cable_tray_style>(params.style),
                               params.columnDiameter,
                               params.columnHeight,
                               params.span,
                               params.width,
                               params.height,
                               params.topPlateHeight,
                               params.arcHeight,
                               params.wallThickness,
                               params.hasProtectionPlate != 0};

  if (params.pipeCount > 0) {
    for (int i = 0; i < params.pipeCount; i++) {
      pnt2d_t pos = params.pipePositions[i];
      cpp_params.pipePositions.push_back(gp_Pnt2d(pos.x, pos.y));
      cpp_params.pipeInnerDiameters.push_back(params.pipeInnerDiameters[i]);
      cpp_params.pipeWallThicknesses.push_back(params.pipeWallThicknesses[i]);
    }
  }

  if (params.pointCount > 0) {
    for (int i = 0; i < params.pointCount; i++) {
      channel_point_t point = params.points[i];
      cpp_params.points.push_back(
          {gp_Pnt(point.position.x, point.position.y, point.position.z),
           static_cast<channel_point_type>(point.ctype)});
    }
  }

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cable_tray(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_cable_L_beam(cable_L_beam_params_t params) {
  cable_L_beam_params cpp_params{params.length, params.width, params.height};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cable_L_beam(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_cable_L_beam_with_place(cable_L_beam_params_t params, pnt3d_t position,
                               dir3d_t xDir, dir3d_t zDir) {
  cable_L_beam_params cpp_params{params.length, params.width, params.height};

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  gp_Dir cpp_zDir(zDir.x, zDir.y, zDir.z);
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(create_cable_L_beam(
                                cpp_params, cpp_position, cpp_xDir, cpp_zDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_manhole(manhole_params_t params) {
  manhole_params cpp_params{static_cast<manhole_style>(params.style),
                            params.length, params.width, params.height,
                            params.wallThickness};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_manhole(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_manhole_with_place(manhole_params_t params,
                                                     pnt3d_t position,
                                                     dir3d_t direction,
                                                     dir3d_t xDir) {
  manhole_params cpp_params{static_cast<manhole_style>(params.style),
                            params.length, params.width, params.height,
                            params.wallThickness};

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_manhole(cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_manhole_cover(manhole_cover_params_t params) {
  manhole_cover_params cpp_params{
      static_cast<manhole_cover_style>(params.style), params.length,
      params.width, params.thickness};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_manhole_cover(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_manhole_cover_with_place(manhole_cover_params_t params, pnt3d_t position,
                                dir3d_t direction, dir3d_t xDir) {
  manhole_cover_params cpp_params{
      static_cast<manhole_cover_style>(params.style), params.length,
      params.width, params.thickness};

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_manhole_cover(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_ladder(ladder_params_t params) {
  ladder_params cpp_params{params.length, params.width, params.thickness};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_ladder(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_ladder_with_place(ladder_params_t params,
                                                    pnt3d_t position,
                                                    dir3d_t direction,
                                                    dir3d_t xDir) {
  ladder_params cpp_params{params.length, params.width, params.thickness};

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_ladder(cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_sump(sump_params_t params) {
  sump_params cpp_params{params.length, params.width, params.depth,
                         params.bottomThickness};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_sump(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_sump_with_place(sump_params_t params,
                                                  pnt3d_t position,
                                                  dir3d_t normal,
                                                  dir3d_t xDir) {
  sump_params cpp_params{params.length, params.width, params.depth,
                         params.bottomThickness};

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_sump(cpp_params, cpp_position, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_footpath(footpath_params_t params) {
  footpath_params cpp_params{params.height, params.width};

  if (params.pointCount > 0) {
    for (int i = 0; i < params.pointCount; i++) {
      cpp_params.points.push_back(
          {gp_Pnt(params.points[i].position.x, params.points[i].position.y,
                  params.points[i].position.z),
           static_cast<channel_point_type>(params.points[i].ctype)});
    }
  }
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_footpath(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_footpath_with_place(footpath_params_t params,
                                                      pnt3d_t position,
                                                      dir3d_t direction,
                                                      dir3d_t xDir) {
  footpath_params cpp_params{params.height, params.width};

  if (params.pointCount > 0) {
    for (int i = 0; i < params.pointCount; i++) {
      cpp_params.points.push_back(
          {gp_Pnt(params.points[i].position.x, params.points[i].position.y,
                  params.points[i].position.z),
           static_cast<channel_point_type>(params.points[i].ctype)});
    }
  }

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_footpath(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_shaft_chamber(shaft_chamber_params_t params) {
  shaft_chamber_params cpp_params{
      params.supportWallThickness, params.supportDiameter,
      params.supportHeight,        params.topThickness,
      params.innerDiameter,        params.workingHeight,
      params.outerWallThickness,   params.innerWallThickness};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_shaft_chamber(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_shaft_chamber_with_place(shaft_chamber_params_t params, pnt3d_t position,
                                dir3d_t direction, dir3d_t xDir) {
  shaft_chamber_params cpp_params{
      params.supportWallThickness, params.supportDiameter,
      params.supportHeight,        params.topThickness,
      params.innerDiameter,        params.workingHeight,
      params.outerWallThickness,   params.innerWallThickness};

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_shaft_chamber(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_tunnel_compartment_partition(
    tunnel_compartment_partition_params_t params) {
  try {
    tunnel_compartment_partition_params cpp_params;
    cpp_params.width = params.width;
    cpp_params.thickness = params.thickness;

    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_tunnel_compartment_partition(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_tunnel_compartment_partition_with_place(
    tunnel_compartment_partition_params_t params, pnt3d_t position,
    dir3d_t normal, dir3d_t xDir) {
  try {
    tunnel_compartment_partition_params cpp_params;
    cpp_params.width = params.width;
    cpp_params.thickness = params.thickness;

    gp_Pnt pos(position.x, position.y, position.z);
    gp_Dir norm(normal.x, normal.y, normal.z);
    gp_Dir xdir(xDir.x, xDir.y, xDir.z);

    auto shp = create_tunnel_compartment_partition(cpp_params, pos, norm, xdir);
    if (shp.IsNull()) {
      return nullptr;
    }
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_tunnel_compartment_partition(cpp_params, pos, norm, xdir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_tunnel_partition_board(tunnel_partition_board_params_t params) {
  tunnel_partition_board_params cpp_params{params.style, params.length,
                                           params.width, params.thickness};

  if (params.holeCount > 0) {
    for (int i = 0; i < params.holeCount; i++) {
      pnt2d_t pos = params.holePositions[i];
      cpp_params.holePositions.push_back(gp_Pnt2d(pos.x, pos.y));
      cpp_params.holeStyles.push_back(params.holeStyles[i]);
      cpp_params.holeDiameters.push_back(params.holeDiameters[i]);
      cpp_params.holeWidths.push_back(params.holeWidths[i]);
    }
  }
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(
                                create_tunnel_partition_board(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}
PRIMCAPICALL topo_shape_t *
create_tunnel_partition_board_with_place(tunnel_partition_board_params_t params,
                                         pnt3d_t position, dir3d_t normal,
                                         dir3d_t xDir) {
  tunnel_partition_board_params cpp_params{params.style, params.length,
                                           params.width, params.thickness};

  if (params.holeCount > 0) {
    for (int i = 0; i < params.holeCount; i++) {
      pnt2d_t pos = params.holePositions[i];
      cpp_params.holePositions.push_back(gp_Pnt2d(pos.x, pos.y));
      cpp_params.holeStyles.push_back(params.holeStyles[i]);
      cpp_params.holeDiameters.push_back(params.holeDiameters[i]);
      cpp_params.holeWidths.push_back(params.holeWidths[i]);
    }
  }

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_tunnel_partition_board(
            cpp_params, cpp_position, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_ventilation_pavilion(ventilation_pavilion_params_t params) {
  ventilation_pavilion_params cpp_params{
      params.topLength, params.middleLength, params.bottomLength,
      params.topWidth,  params.middleWidth,  params.bottomWidth,
      params.topHeight, params.height,       params.baseHeight};
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(
                                create_ventilation_pavilion(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_ventilation_pavilion_with_place(ventilation_pavilion_params_t params,
                                       pnt3d_t position, dir3d_t direction,
                                       dir3d_t xDir) {
  ventilation_pavilion_params cpp_params{
      params.topLength, params.middleLength, params.bottomLength,
      params.topWidth,  params.middleWidth,  params.bottomWidth,
      params.topHeight, params.height,       params.baseHeight};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_ventilation_pavilion(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_straight_ventilation_duct(straight_ventilation_duct_params_t params) {
  straight_ventilation_duct_params cpp_params{
      params.diameter, params.wallThickness, params.height};
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(
                                create_straight_ventilation_duct(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_straight_ventilation_duct_with_place(
    straight_ventilation_duct_params_t params, pnt3d_t position,
    dir3d_t direction, dir3d_t xDir) {
  straight_ventilation_duct_params cpp_params{
      params.diameter, params.wallThickness, params.height};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_straight_ventilation_duct(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_oblique_ventilation_duct(oblique_ventilation_duct_params_t params) {
  oblique_ventilation_duct_params cpp_params{params.hoodRoomLength,
                                             params.hoodRoomWidth,
                                             params.hoodRoomHeight,
                                             params.hoodWallThickness,
                                             params.ductCenterHeight,
                                             params.ductLeftDistance,
                                             params.ductDiameter,
                                             params.ductWallThickness,
                                             params.ductLength,
                                             params.ductHeightDifference,
                                             params.baseLength,
                                             params.baseWidth,
                                             params.baseHeight,
                                             params.baseRoomLength,
                                             params.baseRoomWallThickness,
                                             params.baseRoomWidth,
                                             params.baseRoomHeight};
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(
                                create_oblique_ventilation_duct(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_oblique_ventilation_duct_with_place(
    oblique_ventilation_duct_params_t params, pnt3d_t position,
    dir3d_t direction, dir3d_t xDir) {
  oblique_ventilation_duct_params cpp_params{params.hoodRoomLength,
                                             params.hoodRoomWidth,
                                             params.hoodRoomHeight,
                                             params.hoodWallThickness,
                                             params.ductCenterHeight,
                                             params.ductLeftDistance,
                                             params.ductDiameter,
                                             params.ductWallThickness,
                                             params.ductLength,
                                             params.ductHeightDifference,
                                             params.baseLength,
                                             params.baseWidth,
                                             params.baseHeight,
                                             params.baseRoomLength,
                                             params.baseRoomWallThickness,
                                             params.baseRoomWidth,
                                             params.baseRoomHeight};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_oblique_ventilation_duct(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_drainage_well(drainage_well_params_t params) {
  drainage_well_params cpp_params{
      params.length,          params.width,        params.height,
      params.neckDiameter,    params.neckHeight,   params.cushionExtension,
      params.bottomThickness, params.wallThickness};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_drainage_well(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_drainage_well_with_place(drainage_well_params_t params, pnt3d_t position,
                                dir3d_t direction, dir3d_t xDir) {
  drainage_well_params cpp_params{
      params.length,          params.width,        params.height,
      params.neckDiameter,    params.neckHeight,   params.cushionExtension,
      params.bottomThickness, params.wallThickness};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_drainage_well(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

// 辅助函数用于设置 pnt2d_t 数组元素
PRIMCAPICALL void pnt2d_t_array_set(pnt2d_t *array, int index, pnt2d_t value) {
  if (array != NULL) {
    array[index] = value;
  }
}

// 辅助函数用于设置 double 数组元素
PRIMCAPICALL void double_array_set(double *array, int index, double value) {
  if (array != NULL) {
    array[index] = value;
  }
}

PRIMCAPICALL topo_shape_t *create_pipe_support(pipe_support_params_t params) {
  pipe_support_params cpp_params{static_cast<pipe_support_style>(params.style),
                                 params.count};

  if (params.count > 0 && params.positions != nullptr &&
      params.radii != nullptr) {
    for (int i = 0; i < params.count; i++) {
      pnt2d_t p = params.positions[i];
      cpp_params.positions.push_back(gp_Pnt2d(p.x, p.y));
      cpp_params.radii.push_back(params.radii[i]);
    }
  }
  cpp_params.length = params.length;
  cpp_params.height = params.height;
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_pipe_support(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_pipe_support_with_place(pipe_support_params_t params, pnt3d_t position,
                               dir3d_t direction, dir3d_t xDir) {
  pipe_support_params cpp_params{static_cast<pipe_support_style>(params.style),
                                 params.count};

  if (params.count > 0 && params.positions != nullptr &&
      params.radii != nullptr) {
    for (int i = 0; i < params.count; i++) {
      pnt2d_t p = params.positions[i];
      cpp_params.positions.push_back(gp_Pnt2d(p.x, p.y));
      cpp_params.radii.push_back(params.radii[i]);
    }
  }
  cpp_params.length = params.length;
  cpp_params.height = params.height;

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_pipe_support(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_cover_plate(cover_plate_params_t params) {
  cover_plate_params cpp_params{static_cast<cover_plate_style>(params.style),
                                params.length,
                                params.width,
                                params.smallRadius,
                                params.largeRadius,
                                params.thickness};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cover_plate(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_cover_plate_with_place(cover_plate_params_t params, pnt3d_t position,
                              dir3d_t normal, dir3d_t xDir) {
  cover_plate_params cpp_params{static_cast<cover_plate_style>(params.style),
                                params.length,
                                params.width,
                                params.smallRadius,
                                params.largeRadius,
                                params.thickness};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cover_plate(
            cpp_params, cpp_position, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_cable_ray(cable_ray_params_t params) {
  cable_ray_params cpp_params{params.outerLength, params.outerHeight,
                              params.innerLength, params.innerHeight,
                              params.coverThickness};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cable_ray(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_cable_ray_with_place(cable_ray_params_t params, pnt3d_t position,
                            dir3d_t direction, dir3d_t xDir) {
  cable_ray_params cpp_params{params.outerLength, params.outerHeight,
                              params.innerLength, params.innerHeight,
                              params.coverThickness};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cable_ray(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

topo_shape_t *create_revol(revol_params_t params) {
  // 将C结构体转换为C++参数
  revol_params cpp_params;
  cpp_params.angle = params.angle;
  cpp_params.axis = gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)); // 默认轴

  // 根据类型转换剖面
  switch (params.profile.type_) {
  case PROFILE_TYPE_TRIANGLE: {
    auto &tri = params.profile.triangle;
    cpp_params.profile = triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                                          gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                                          gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z));
    break;
  }
  case PROFILE_TYPE_RECTANGLE: {
    auto &rect = params.profile.rectangle;
    cpp_params.profile =
        rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                          gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z));
    break;
  }
  case PROFILE_TYPE_CIRC: {
    auto &circ = params.profile.circ;
    cpp_params.profile = circ_profile(
        gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
        gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius);
    break;
  }
  case PROFILE_TYPE_ELIPS: {
    auto &elips = params.profile.elips;
    cpp_params.profile =
        elips_profile(gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
                      gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
                      gp_Pnt(elips.center.x, elips.center.y, elips.center.z));
    break;
  }
  case PROFILE_TYPE_POLYGON: {
    auto &poly = params.profile.polygon;
    std::vector<gp_Pnt> edges;
    for (int i = 0; i < poly.edgeCount; i++) {
      edges.emplace_back(poly.edges[i].x, poly.edges[i].y, poly.edges[i].z);
    }

    std::vector<std::vector<gp_Pnt>> inners;
    for (int i = 0; i < poly.innerArrayCount; i++) {
      std::vector<gp_Pnt> inner;
      for (int j = 0; j < poly.innerCounts[i]; j++) {
        inner.emplace_back(poly.inners[i][j].x, poly.inners[i][j].y,
                           poly.inners[i][j].z);
      }
      inners.push_back(inner);
    }

    cpp_params.profile = polygon_profile(edges, inners);
    break;
  }
  default:
    return nullptr;
  }

  // 转换旋转轴
  cpp_params.axis =
      gp_Ax1(gp_Pnt(params.axis.p.x, params.axis.p.y, params.axis.p.z),
             gp_Dir(params.axis.d.x, params.axis.d.y, params.axis.d.z));

  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_revol(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

topo_shape_t *create_revol_with_place(revol_params_t params, pnt3d_t position,
                                      dir3d_t direction, dir3d_t xDir) {
  revol_params cpp_params;
  cpp_params.angle = params.angle;
  cpp_params.axis = gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)); // 默认轴

  // 根据类型转换剖面
  switch (params.profile.type_) {
  case PROFILE_TYPE_TRIANGLE: {
    auto &tri = params.profile.triangle;
    cpp_params.profile = triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                                          gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                                          gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z));
    break;
  }
  case PROFILE_TYPE_RECTANGLE: {
    auto &rect = params.profile.rectangle;
    cpp_params.profile =
        rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                          gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z));
    break;
  }
  case PROFILE_TYPE_CIRC: {
    auto &circ = params.profile.circ;
    cpp_params.profile = circ_profile(
        gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
        gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius);
    break;
  }
  case PROFILE_TYPE_ELIPS: {
    auto &elips = params.profile.elips;
    cpp_params.profile =
        elips_profile(gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
                      gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
                      gp_Pnt(elips.center.x, elips.center.y, elips.center.z));
    break;
  }
  case PROFILE_TYPE_POLYGON: {
    auto &poly = params.profile.polygon;
    std::vector<gp_Pnt> edges;
    for (int i = 0; i < poly.edgeCount; i++) {
      edges.emplace_back(poly.edges[i].x, poly.edges[i].y, poly.edges[i].z);
    }

    std::vector<std::vector<gp_Pnt>> inners;
    for (int i = 0; i < poly.innerArrayCount; i++) {
      std::vector<gp_Pnt> inner;
      for (int j = 0; j < poly.innerCounts[i]; j++) {
        inner.emplace_back(poly.inners[i][j].x, poly.inners[i][j].y,
                           poly.inners[i][j].z);
      }
      inners.push_back(inner);
    }

    cpp_params.profile = polygon_profile(edges, inners);
    break;
  }
  default:
    return nullptr;
  }

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_revol(cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_prism(prism_params_t params) {
  prism_params cpp_params;

  // 根据剖面类型转换剖面
  switch (params.profile.type_) {
  case PROFILE_TYPE_TRIANGLE: {
    auto &tri = params.profile.triangle;
    cpp_params.profile = triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                                          gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                                          gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z));
    break;
  }
  case PROFILE_TYPE_RECTANGLE: {
    auto &rect = params.profile.rectangle;
    cpp_params.profile =
        rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                          gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z));
    break;
  }
  case PROFILE_TYPE_CIRC: {
    auto &circ = params.profile.circ;
    cpp_params.profile = circ_profile(
        gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
        gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius);
    break;
  }
  case PROFILE_TYPE_ELIPS: {
    auto &elips = params.profile.elips;
    cpp_params.profile =
        elips_profile(gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
                      gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
                      gp_Pnt(elips.center.x, elips.center.y, elips.center.z));
    break;
  }
  case PROFILE_TYPE_POLYGON: {
    auto &poly = params.profile.polygon;
    std::vector<gp_Pnt> edges;
    for (int i = 0; i < poly.edgeCount; i++) {
      edges.emplace_back(poly.edges[i].x, poly.edges[i].y, poly.edges[i].z);
    }

    std::vector<std::vector<gp_Pnt>> inners;
    for (int i = 0; i < poly.innerArrayCount; i++) {
      std::vector<gp_Pnt> inner;
      for (int j = 0; j < poly.innerCounts[i]; j++) {
        inner.emplace_back(poly.inners[i][j].x, poly.inners[i][j].y,
                           poly.inners[i][j].z);
      }
      inners.push_back(inner);
    }

    cpp_params.profile = polygon_profile(edges, inners);
    break;
  }
  default:
    return nullptr;
  }

  // 设置拉伸方向
  cpp_params.direction =
      gp_Dir(params.direction.x, params.direction.y, params.direction.z);
  cpp_params.height = params.height;

  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_prism(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_prism_with_place(prism_params_t params,
                                                   pnt3d_t position,
                                                   dir3d_t direction,
                                                   dir3d_t xDir) {
  prism_params cpp_params;

  // 根据剖面类型转换剖面
  switch (params.profile.type_) {
  case PROFILE_TYPE_TRIANGLE: {
    auto &tri = params.profile.triangle;
    cpp_params.profile = triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                                          gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                                          gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z));
    break;
  }
  case PROFILE_TYPE_RECTANGLE: {
    auto &rect = params.profile.rectangle;
    cpp_params.profile =
        rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                          gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z));
    break;
  }
  case PROFILE_TYPE_CIRC: {
    auto &circ = params.profile.circ;
    cpp_params.profile = circ_profile(
        gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
        gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius);
    break;
  }
  case PROFILE_TYPE_ELIPS: {
    auto &elips = params.profile.elips;
    cpp_params.profile =
        elips_profile(gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
                      gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
                      gp_Pnt(elips.center.x, elips.center.y, elips.center.z));
    break;
  }
  case PROFILE_TYPE_POLYGON: {
    auto &poly = params.profile.polygon;
    std::vector<gp_Pnt> edges;
    for (int i = 0; i < poly.edgeCount; i++) {
      edges.emplace_back(poly.edges[i].x, poly.edges[i].y, poly.edges[i].z);
    }

    std::vector<std::vector<gp_Pnt>> inners;
    for (int i = 0; i < poly.innerArrayCount; i++) {
      std::vector<gp_Pnt> inner;
      for (int j = 0; j < poly.innerCounts[i]; j++) {
        inner.emplace_back(poly.inners[i][j].x, poly.inners[i][j].y,
                           poly.inners[i][j].z);
      }
      inners.push_back(inner);
    }

    cpp_params.profile = polygon_profile(edges, inners);
    break;
  }
  default:
    return nullptr;
  }

  // 设置拉伸方向
  cpp_params.direction =
      gp_Dir(params.direction.x, params.direction.y, params.direction.z);
  cpp_params.height = params.height;

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);

  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_prism(cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

// 线段采样函数实现
PRIMCAPICALL pnt3d_t *
sample_segment_points(const pnt3d_t *wires, const int *wire_counts,
                      int wire_array_count, const segment_type_t *segments,
                      int segment_count, double tessellation, int *out_count) {
  // 参数检查
  if (!wires || !wire_counts || !segments || !out_count ||
      wire_array_count <= 0 || segment_count <= 0) {
    return nullptr;
  }

  // 转换输入数据
  std::vector<std::vector<gp_Pnt>> cpp_wires;
  std::vector<segment_type> cpp_segments;

  const pnt3d_t *current_wire = wires;
  for (int i = 0; i < wire_array_count; ++i) {
    std::vector<gp_Pnt> wire;
    for (int j = 0; j < wire_counts[i]; ++j) {
      wire.push_back(gp_Pnt(current_wire->x, current_wire->y, current_wire->z));
      ++current_wire;
    }
    cpp_wires.push_back(wire);
  }

  for (int i = 0; i < segment_count; ++i) {
    cpp_segments.push_back(static_cast<segment_type>(segments[i]));
  }

  // 调用C++函数
  auto points = sample_segment_points(cpp_wires, cpp_segments, tessellation);

  // 转换输出结果
  *out_count = static_cast<int>(points.size());
  pnt3d_t *result = new pnt3d_t[points.size()];
  for (size_t i = 0; i < points.size(); ++i) {
    result[i].x = points[i].X();
    result[i].y = points[i].Y();
    result[i].z = points[i].Z();
  }

  return result;
}

PRIMCAPICALL topo_shape_t *create_pipe(pipe_params_t params) {
  pipe_params cpp_params;

  // 转换路径点
  std::vector<gp_Pnt> wire;
  for (int i = 0; i < params.wire_count; i++) {
    wire.emplace_back(params.wire[i].x, params.wire[i].y, params.wire[i].z);
  }
  cpp_params.wire = wire;

  // 转换剖面类型
  std::vector<shape_profile> profiles;
  for (int i = 0; i < params.profile_count; i++) {
    switch (params.profiles[i].type_) {
    case PROFILE_TYPE_TRIANGLE: {
      auto &tri = params.profiles[i].triangle;
      profiles.emplace_back(
          triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                           gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                           gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z)));
      break;
    }
    case PROFILE_TYPE_RECTANGLE: {
      auto &rect = params.profiles[i].rectangle;
      profiles.emplace_back(
          rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                            gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z)));
      break;
    }
    case PROFILE_TYPE_CIRC: {
      auto &circ = params.profiles[i].circ;
      profiles.emplace_back(circ_profile(
          gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
          gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius));
      break;
    }
    case PROFILE_TYPE_ELIPS: {
      auto &elips = params.profiles[i].elips;
      profiles.emplace_back(elips_profile(
          gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
          gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
          gp_Pnt(elips.center.x, elips.center.y, elips.center.z)));
      break;
    }
    case PROFILE_TYPE_POLYGON: {
      auto &poly = params.profiles[i].polygon;
      std::vector<gp_Pnt> edges;
      for (int j = 0; j < poly.edgeCount; j++) {
        edges.emplace_back(poly.edges[j].x, poly.edges[j].y, poly.edges[j].z);
      }

      std::vector<std::vector<gp_Pnt>> inners;
      for (int j = 0; j < poly.innerArrayCount; j++) {
        std::vector<gp_Pnt> inner;
        for (int k = 0; k < poly.innerCounts[j]; k++) {
          inner.emplace_back(poly.inners[j][k].x, poly.inners[j][k].y,
                             poly.inners[j][k].z);
        }
        inners.push_back(inner);
      }

      profiles.emplace_back(polygon_profile(edges, inners));
      break;
    }
    default:
      return nullptr;
    }
  }
  cpp_params.profiles = profiles;

  // 转换内剖面(如果有)
  if (params.inner_profiles != nullptr) {
    std::vector<shape_profile> inner_profiles;
    for (int i = 0; i < params.inner_profile_counts[0]; i++) {
      switch (params.inner_profiles[0][i].type_) {
      case PROFILE_TYPE_TRIANGLE: {
        auto &tri = params.inner_profiles[0][i].triangle;
        inner_profiles.emplace_back(
            triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                             gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                             gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z)));
        break;
      }
      case PROFILE_TYPE_RECTANGLE: {
        auto &rect = params.inner_profiles[0][i].rectangle;
        inner_profiles.emplace_back(
            rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                              gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z)));
        break;
      }
      case PROFILE_TYPE_CIRC: {
        auto &circ = params.inner_profiles[0][i].circ;
        inner_profiles.emplace_back(circ_profile(
            gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
            gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius));
        break;
      }
      case PROFILE_TYPE_ELIPS: {
        auto &elips = params.inner_profiles[0][i].elips;
        inner_profiles.emplace_back(elips_profile(
            gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
            gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
            gp_Pnt(elips.center.x, elips.center.y, elips.center.z)));
        break;
      }
      case PROFILE_TYPE_POLYGON: {
        auto &poly = params.inner_profiles[0][i].polygon;
        std::vector<gp_Pnt> edges;
        for (int j = 0; j < poly.edgeCount; j++) {
          edges.emplace_back(poly.edges[j].x, poly.edges[j].y, poly.edges[j].z);
        }

        std::vector<std::vector<gp_Pnt>> inners;
        for (int j = 0; j < poly.innerArrayCount; j++) {
          std::vector<gp_Pnt> inner;
          for (int k = 0; k < poly.innerCounts[j]; k++) {
            inner.emplace_back(poly.inners[j][k].x, poly.inners[j][k].y,
                               poly.inners[j][k].z);
          }
          inners.push_back(inner);
        }

        inner_profiles.emplace_back(polygon_profile(edges, inners));
        break;
      }
      default:
        return nullptr;
      }
    }
    cpp_params.inner_profiles = inner_profiles;
  }

  // 转换线段类型
  switch (params.segment_type) {
  case SEGMENT_TYPE_LINE:
    cpp_params.segment_type = segment_type::LINE;
    break;
  case SEGMENT_TYPE_THREE_POINT_ARC:
    cpp_params.segment_type = segment_type::THREE_POINT_ARC;
    break;
  case SEGMENT_TYPE_CIRCLE_CENTER_ARC:
    cpp_params.segment_type = segment_type::CIRCLE_CENTER_ARC;
    break;
  case SEGMENT_TYPE_SPLINE:
    cpp_params.segment_type = segment_type::SPLINE;
    break;
  case SEGMENT_TYPE_BEZIER:
    cpp_params.segment_type = segment_type::BEZIER;
    break;
  default:
    return nullptr;
  }

  // 转换过渡模式
  switch (params.transition_mode) {
  case TRANSITION_RIGHT:
    cpp_params.transition_mode = transition_mode::RIGHT;
    break;
  case TRANSITION_ROUND:
    cpp_params.transition_mode = transition_mode::ROUND;
    break;
  case TRANSITION_TRANSFORMED:
    cpp_params.transition_mode = transition_mode::TRANSFORMED;
    break;
  default:
    return nullptr;
  }

  if (params.up_dir != nullptr) {
    cpp_params.upDir =
        gp_Dir(params.up_dir->x, params.up_dir->y, params.up_dir->z);
  }

  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_pipe(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

topo_shape_t *create_pipe_with_split_distances(pipe_params_t params,
                                               double start_distance,
                                               double end_distance) {
  pipe_params cpp_params;

  // 转换路径点
  std::vector<gp_Pnt> wire;
  for (int i = 0; i < params.wire_count; i++) {
    wire.emplace_back(params.wire[i].x, params.wire[i].y, params.wire[i].z);
  }
  cpp_params.wire = wire;

  // 转换剖面类型
  std::vector<shape_profile> profiles;
  for (int i = 0; i < params.profile_count; i++) {
    switch (params.profiles[i].type_) {
    case PROFILE_TYPE_TRIANGLE: {
      auto &tri = params.profiles[i].triangle;
      profiles.emplace_back(
          triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                           gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                           gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z)));
      break;
    }
    case PROFILE_TYPE_RECTANGLE: {
      auto &rect = params.profiles[i].rectangle;
      profiles.emplace_back(
          rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                            gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z)));
      break;
    }
    case PROFILE_TYPE_CIRC: {
      auto &circ = params.profiles[i].circ;
      profiles.emplace_back(circ_profile(
          gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
          gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius));
      break;
    }
    case PROFILE_TYPE_ELIPS: {
      auto &elips = params.profiles[i].elips;
      profiles.emplace_back(elips_profile(
          gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
          gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
          gp_Pnt(elips.center.x, elips.center.y, elips.center.z)));
      break;
    }
    case PROFILE_TYPE_POLYGON: {
      auto &poly = params.profiles[i].polygon;
      std::vector<gp_Pnt> edges;
      for (int j = 0; j < poly.edgeCount; j++) {
        edges.emplace_back(poly.edges[j].x, poly.edges[j].y, poly.edges[j].z);
      }

      std::vector<std::vector<gp_Pnt>> inners;
      for (int j = 0; j < poly.innerArrayCount; j++) {
        std::vector<gp_Pnt> inner;
        for (int k = 0; k < poly.innerCounts[j]; k++) {
          inner.emplace_back(poly.inners[j][k].x, poly.inners[j][k].y,
                             poly.inners[j][k].z);
        }
        inners.push_back(inner);
      }

      profiles.emplace_back(polygon_profile(edges, inners));
      break;
    }
    default:
      return nullptr;
    }
  }
  cpp_params.profiles = profiles;

  // 转换内剖面(如果有)
  if (params.inner_profiles != nullptr) {
    std::vector<shape_profile> inner_profiles;
    for (int i = 0; i < params.inner_profile_counts[0]; i++) {
      switch (params.inner_profiles[0][i].type_) {
      case PROFILE_TYPE_TRIANGLE: {
        auto &tri = params.inner_profiles[0][i].triangle;
        inner_profiles.emplace_back(
            triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                             gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                             gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z)));
        break;
      }
      case PROFILE_TYPE_RECTANGLE: {
        auto &rect = params.inner_profiles[0][i].rectangle;
        inner_profiles.emplace_back(
            rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                              gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z)));
        break;
      }
      case PROFILE_TYPE_CIRC: {
        auto &circ = params.inner_profiles[0][i].circ;
        inner_profiles.emplace_back(circ_profile(
            gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
            gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius));
        break;
      }
      case PROFILE_TYPE_ELIPS: {
        auto &elips = params.inner_profiles[0][i].elips;
        inner_profiles.emplace_back(elips_profile(
            gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
            gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
            gp_Pnt(elips.center.x, elips.center.y, elips.center.z)));
        break;
      }
      case PROFILE_TYPE_POLYGON: {
        auto &poly = params.inner_profiles[0][i].polygon;
        std::vector<gp_Pnt> edges;
        for (int j = 0; j < poly.edgeCount; j++) {
          edges.emplace_back(poly.edges[j].x, poly.edges[j].y, poly.edges[j].z);
        }

        std::vector<std::vector<gp_Pnt>> inners;
        for (int j = 0; j < poly.innerArrayCount; j++) {
          std::vector<gp_Pnt> inner;
          for (int k = 0; k < poly.innerCounts[j]; k++) {
            inner.emplace_back(poly.inners[j][k].x, poly.inners[j][k].y,
                               poly.inners[j][k].z);
          }
          inners.push_back(inner);
        }

        inner_profiles.emplace_back(polygon_profile(edges, inners));
        break;
      }
      default:
        return nullptr;
      }
    }
    cpp_params.inner_profiles = inner_profiles;
  }

  // 转换线段类型
  switch (params.segment_type) {
  case SEGMENT_TYPE_LINE:
    cpp_params.segment_type = segment_type::LINE;
    break;
  case SEGMENT_TYPE_THREE_POINT_ARC:
    cpp_params.segment_type = segment_type::THREE_POINT_ARC;
    break;
  case SEGMENT_TYPE_CIRCLE_CENTER_ARC:
    cpp_params.segment_type = segment_type::CIRCLE_CENTER_ARC;
    break;
  case SEGMENT_TYPE_SPLINE:
    cpp_params.segment_type = segment_type::SPLINE;
    break;
  case SEGMENT_TYPE_BEZIER:
    cpp_params.segment_type = segment_type::BEZIER;
    break;
  default:
    return nullptr;
  }

  // 转换过渡模式
  switch (params.transition_mode) {
  case TRANSITION_RIGHT:
    cpp_params.transition_mode = transition_mode::RIGHT;
    break;
  case TRANSITION_ROUND:
    cpp_params.transition_mode = transition_mode::ROUND;
    break;
  case TRANSITION_TRANSFORMED:
    cpp_params.transition_mode = transition_mode::TRANSFORMED;
    break;
  default:
    return nullptr;
  }

  if (params.up_dir != nullptr) {
    cpp_params.upDir =
        gp_Dir(params.up_dir->x, params.up_dir->y, params.up_dir->z);
  }

  try {
    std::array<double, 2> distances = {start_distance, end_distance};
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_pipe_with_split_distances(cpp_params, distances))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_pipe_with_place(pipe_params_t params,
                                                  pnt3d_t position,
                                                  dir3d_t direction,
                                                  dir3d_t xDir) {
  pipe_params cpp_params;

  // 转换路径点
  std::vector<gp_Pnt> wire;
  for (int i = 0; i < params.wire_count; i++) {
    wire.emplace_back(params.wire[i].x, params.wire[i].y, params.wire[i].z);
  }
  cpp_params.wire = wire;

  // 转换剖面类型
  std::vector<shape_profile> profiles;
  for (int i = 0; i < params.profile_count; i++) {
    switch (params.profiles[i].type_) {
    case PROFILE_TYPE_TRIANGLE: {
      auto &tri = params.profiles[i].triangle;
      profiles.emplace_back(
          triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                           gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                           gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z)));
      break;
    }
    case PROFILE_TYPE_RECTANGLE: {
      auto &rect = params.profiles[i].rectangle;
      profiles.emplace_back(
          rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                            gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z)));
      break;
    }
    case PROFILE_TYPE_CIRC: {
      auto &circ = params.profiles[i].circ;
      profiles.emplace_back(circ_profile(
          gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
          gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius));
      break;
    }
    case PROFILE_TYPE_ELIPS: {
      auto &elips = params.profiles[i].elips;
      profiles.emplace_back(elips_profile(
          gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
          gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
          gp_Pnt(elips.center.x, elips.center.y, elips.center.z)));
      break;
    }
    case PROFILE_TYPE_POLYGON: {
      auto &poly = params.profiles[i].polygon;
      std::vector<gp_Pnt> edges;
      for (int j = 0; j < poly.edgeCount; j++) {
        edges.emplace_back(poly.edges[j].x, poly.edges[j].y, poly.edges[j].z);
      }

      std::vector<std::vector<gp_Pnt>> inners;
      for (int j = 0; j < poly.innerArrayCount; j++) {
        std::vector<gp_Pnt> inner;
        for (int k = 0; k < poly.innerCounts[j]; k++) {
          inner.emplace_back(poly.inners[j][k].x, poly.inners[j][k].y,
                             poly.inners[j][k].z);
        }
        inners.push_back(inner);
      }

      profiles.emplace_back(polygon_profile(edges, inners));
      break;
    }
    default:
      return nullptr;
    }
  }
  cpp_params.profiles = profiles;

  // 转换内剖面(如果有)
  if (params.inner_profiles != nullptr) {
    std::vector<shape_profile> inner_profiles;
    for (int i = 0; i < params.inner_profile_counts[0]; i++) {
      switch (params.inner_profiles[0][i].type_) {
      case PROFILE_TYPE_TRIANGLE: {
        auto &tri = params.inner_profiles[0][i].triangle;
        inner_profiles.emplace_back(
            triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                             gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                             gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z)));
        break;
      }
      case PROFILE_TYPE_RECTANGLE: {
        auto &rect = params.inner_profiles[0][i].rectangle;
        inner_profiles.emplace_back(
            rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                              gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z)));
        break;
      }
      case PROFILE_TYPE_CIRC: {
        auto &circ = params.inner_profiles[0][i].circ;
        inner_profiles.emplace_back(circ_profile(
            gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
            gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius));
        break;
      }
      case PROFILE_TYPE_ELIPS: {
        auto &elips = params.inner_profiles[0][i].elips;
        inner_profiles.emplace_back(elips_profile(
            gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
            gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
            gp_Pnt(elips.center.x, elips.center.y, elips.center.z)));
        break;
      }
      case PROFILE_TYPE_POLYGON: {
        auto &poly = params.inner_profiles[0][i].polygon;
        std::vector<gp_Pnt> edges;
        for (int j = 0; j < poly.edgeCount; j++) {
          edges.emplace_back(poly.edges[j].x, poly.edges[j].y, poly.edges[j].z);
        }

        std::vector<std::vector<gp_Pnt>> inners;
        for (int j = 0; j < poly.innerArrayCount; j++) {
          std::vector<gp_Pnt> inner;
          for (int k = 0; k < poly.innerCounts[j]; k++) {
            inner.emplace_back(poly.inners[j][k].x, poly.inners[j][k].y,
                               poly.inners[j][k].z);
          }
          inners.push_back(inner);
        }

        inner_profiles.emplace_back(polygon_profile(edges, inners));
        break;
      }
      default:
        return nullptr;
      }
    }
    cpp_params.inner_profiles = inner_profiles;
  }

  // 转换线段类型
  switch (params.segment_type) {
  case SEGMENT_TYPE_LINE:
    cpp_params.segment_type = segment_type::LINE;
    break;
  case SEGMENT_TYPE_THREE_POINT_ARC:
    cpp_params.segment_type = segment_type::THREE_POINT_ARC;
    break;
  case SEGMENT_TYPE_CIRCLE_CENTER_ARC:
    cpp_params.segment_type = segment_type::CIRCLE_CENTER_ARC;
    break;
  case SEGMENT_TYPE_SPLINE:
    cpp_params.segment_type = segment_type::SPLINE;
    break;
  case SEGMENT_TYPE_BEZIER:
    cpp_params.segment_type = segment_type::BEZIER;
    break;
  default:
    return nullptr;
  }

  // 转换过渡模式
  switch (params.transition_mode) {
  case TRANSITION_RIGHT:
    cpp_params.transition_mode = transition_mode::RIGHT;
    break;
  case TRANSITION_ROUND:
    cpp_params.transition_mode = transition_mode::ROUND;
    break;
  case TRANSITION_TRANSFORMED:
    cpp_params.transition_mode = transition_mode::TRANSFORMED;
    break;
  default:
    return nullptr;
  }

  if (params.up_dir != nullptr) {
    cpp_params.upDir =
        gp_Dir(params.up_dir->x, params.up_dir->y, params.up_dir->z);
  }

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);

  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_pipe(cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_multi_segment_pipe(multi_segment_pipe_params_t params) {
  multi_segment_pipe_params cpp_params;

  // 转换路径点
  std::vector<std::vector<gp_Pnt>> wires;
  for (int i = 0; i < params.wire_array_count; i++) {
    std::vector<gp_Pnt> wire;
    for (int j = 0; j < params.wire_counts[i]; j++) {
      wire.emplace_back(params.wires[i][j].x, params.wires[i][j].y,
                        params.wires[i][j].z);
    }
    wires.push_back(wire);
  }
  cpp_params.wires = wires;

  // 转换剖面类型
  std::vector<shape_profile> profiles;
  for (int i = 0; i < params.profile_count; i++) {
    switch (params.profiles[i].type_) {
    case PROFILE_TYPE_TRIANGLE: {
      auto &tri = params.profiles[i].triangle;
      profiles.emplace_back(
          triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                           gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                           gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z)));
      break;
    }
    case PROFILE_TYPE_RECTANGLE: {
      auto &rect = params.profiles[i].rectangle;
      profiles.emplace_back(
          rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                            gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z)));
      break;
    }
    case PROFILE_TYPE_CIRC: {
      auto &circ = params.profiles[i].circ;
      profiles.emplace_back(circ_profile(
          gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
          gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius));
      break;
    }
    case PROFILE_TYPE_ELIPS: {
      auto &elips = params.profiles[i].elips;
      profiles.emplace_back(elips_profile(
          gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
          gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
          gp_Pnt(elips.center.x, elips.center.y, elips.center.z)));
      break;
    }
    case PROFILE_TYPE_POLYGON: {
      auto &poly = params.profiles[i].polygon;
      std::vector<gp_Pnt> edges;
      for (int j = 0; j < poly.edgeCount; j++) {
        edges.emplace_back(poly.edges[j].x, poly.edges[j].y, poly.edges[j].z);
      }

      std::vector<std::vector<gp_Pnt>> inners;
      for (int j = 0; j < poly.innerArrayCount; j++) {
        std::vector<gp_Pnt> inner;
        for (int k = 0; k < poly.innerCounts[j]; k++) {
          inner.emplace_back(poly.inners[j][k].x, poly.inners[j][k].y,
                             poly.inners[j][k].z);
        }
        inners.push_back(inner);
      }

      profiles.emplace_back(polygon_profile(edges, inners));
      break;
    }
    default:
      return nullptr;
    }
  }
  cpp_params.profiles = profiles;

  // 转换内剖面(如果有)
  if (params.inner_profiles != nullptr) {
    std::vector<shape_profile> inner_profiles;
    for (int i = 0; i < params.inner_profile_counts[0]; i++) {
      switch (params.inner_profiles[0][i].type_) {
      case PROFILE_TYPE_TRIANGLE: {
        auto &tri = params.inner_profiles[0][i].triangle;
        inner_profiles.emplace_back(
            triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                             gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                             gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z)));
        break;
      }
      case PROFILE_TYPE_RECTANGLE: {
        auto &rect = params.inner_profiles[0][i].rectangle;
        inner_profiles.emplace_back(
            rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                              gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z)));
        break;
      }
      case PROFILE_TYPE_CIRC: {
        auto &circ = params.inner_profiles[0][i].circ;
        inner_profiles.emplace_back(circ_profile(
            gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
            gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius));
        break;
      }
      case PROFILE_TYPE_ELIPS: {
        auto &elips = params.inner_profiles[0][i].elips;
        inner_profiles.emplace_back(elips_profile(
            gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
            gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
            gp_Pnt(elips.center.x, elips.center.y, elips.center.z)));
        break;
      }
      case PROFILE_TYPE_POLYGON: {
        auto &poly = params.inner_profiles[0][i].polygon;
        std::vector<gp_Pnt> edges;
        for (int j = 0; j < poly.edgeCount; j++) {
          edges.emplace_back(poly.edges[j].x, poly.edges[j].y, poly.edges[j].z);
        }

        std::vector<std::vector<gp_Pnt>> inners;
        for (int j = 0; j < poly.innerArrayCount; j++) {
          std::vector<gp_Pnt> inner;
          for (int k = 0; k < poly.innerCounts[j]; k++) {
            inner.emplace_back(poly.inners[j][k].x, poly.inners[j][k].y,
                               poly.inners[j][k].z);
          }
          inners.push_back(inner);
        }

        inner_profiles.emplace_back(polygon_profile(edges, inners));
        break;
      }
      default:
        return nullptr;
      }
    }
    cpp_params.inner_profiles = inner_profiles;
  }

  // 转换线段类型
  if (params.segment_types != nullptr) {
    std::vector<segment_type> segment_types;
    for (int i = 0; i < params.segment_type_count; i++) {
      switch (params.segment_types[i]) {
      case SEGMENT_TYPE_LINE:
        segment_types.push_back(segment_type::LINE);
        break;
      case SEGMENT_TYPE_THREE_POINT_ARC:
        segment_types.push_back(segment_type::THREE_POINT_ARC);
        break;
      case SEGMENT_TYPE_CIRCLE_CENTER_ARC:
        segment_types.push_back(segment_type::CIRCLE_CENTER_ARC);
        break;
      case SEGMENT_TYPE_SPLINE:
        segment_types.push_back(segment_type::SPLINE);
        break;
      case SEGMENT_TYPE_BEZIER:
        segment_types.push_back(segment_type::BEZIER);
        break;
      default:
        return nullptr;
      }
    }
    cpp_params.segment_types = segment_types;
  }

  // 转换过渡模式
  switch (params.transition_mode) {
  case TRANSITION_RIGHT:
    cpp_params.transition_mode = transition_mode::RIGHT;
    break;
  case TRANSITION_ROUND:
    cpp_params.transition_mode = transition_mode::ROUND;
    break;
  case TRANSITION_TRANSFORMED:
    cpp_params.transition_mode = transition_mode::TRANSFORMED;
    break;
  default:
    return nullptr;
  }

  if (params.up_dir != nullptr) {
    cpp_params.upDir =
        gp_Dir(params.up_dir->x, params.up_dir->y, params.up_dir->z);
  }

  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_multi_segment_pipe(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

topo_shape_t *create_multi_segment_pipe_with_split_distances(
    multi_segment_pipe_params_t params, double start_distance,
    double end_distance) {
  multi_segment_pipe_params cpp_params;

  // 转换路径点
  std::vector<std::vector<gp_Pnt>> wires;
  for (int i = 0; i < params.wire_array_count; i++) {
    std::vector<gp_Pnt> wire;
    for (int j = 0; j < params.wire_counts[i]; j++) {
      wire.emplace_back(params.wires[i][j].x, params.wires[i][j].y,
                        params.wires[i][j].z);
    }
    wires.push_back(wire);
  }
  cpp_params.wires = wires;

  // 转换剖面类型
  std::vector<shape_profile> profiles;
  for (int i = 0; i < params.profile_count; i++) {
    switch (params.profiles[i].type_) {
    case PROFILE_TYPE_TRIANGLE: {
      auto &tri = params.profiles[i].triangle;
      profiles.emplace_back(
          triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                           gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                           gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z)));
      break;
    }
    case PROFILE_TYPE_RECTANGLE: {
      auto &rect = params.profiles[i].rectangle;
      profiles.emplace_back(
          rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                            gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z)));
      break;
    }
    case PROFILE_TYPE_CIRC: {
      auto &circ = params.profiles[i].circ;
      profiles.emplace_back(circ_profile(
          gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
          gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius));
      break;
    }
    case PROFILE_TYPE_ELIPS: {
      auto &elips = params.profiles[i].elips;
      profiles.emplace_back(elips_profile(
          gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
          gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
          gp_Pnt(elips.center.x, elips.center.y, elips.center.z)));
      break;
    }
    case PROFILE_TYPE_POLYGON: {
      auto &poly = params.profiles[i].polygon;
      std::vector<gp_Pnt> edges;
      for (int j = 0; j < poly.edgeCount; j++) {
        edges.emplace_back(poly.edges[j].x, poly.edges[j].y, poly.edges[j].z);
      }

      std::vector<std::vector<gp_Pnt>> inners;
      for (int j = 0; j < poly.innerArrayCount; j++) {
        std::vector<gp_Pnt> inner;
        for (int k = 0; k < poly.innerCounts[j]; k++) {
          inner.emplace_back(poly.inners[j][k].x, poly.inners[j][k].y,
                             poly.inners[j][k].z);
        }
        inners.push_back(inner);
      }

      profiles.emplace_back(polygon_profile(edges, inners));
      break;
    }
    default:
      return nullptr;
    }
  }
  cpp_params.profiles = profiles;

  // 转换内剖面(如果有)
  if (params.inner_profiles != nullptr) {
    std::vector<shape_profile> inner_profiles;
    for (int i = 0; i < params.inner_profile_counts[0]; i++) {
      switch (params.inner_profiles[0][i].type_) {
      case PROFILE_TYPE_TRIANGLE: {
        auto &tri = params.inner_profiles[0][i].triangle;
        inner_profiles.emplace_back(
            triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                             gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                             gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z)));
        break;
      }
      case PROFILE_TYPE_RECTANGLE: {
        auto &rect = params.inner_profiles[0][i].rectangle;
        inner_profiles.emplace_back(
            rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                              gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z)));
        break;
      }
      case PROFILE_TYPE_CIRC: {
        auto &circ = params.inner_profiles[0][i].circ;
        inner_profiles.emplace_back(circ_profile(
            gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
            gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius));
        break;
      }
      case PROFILE_TYPE_ELIPS: {
        auto &elips = params.inner_profiles[0][i].elips;
        inner_profiles.emplace_back(elips_profile(
            gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
            gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
            gp_Pnt(elips.center.x, elips.center.y, elips.center.z)));
        break;
      }
      case PROFILE_TYPE_POLYGON: {
        auto &poly = params.inner_profiles[0][i].polygon;
        std::vector<gp_Pnt> edges;
        for (int j = 0; j < poly.edgeCount; j++) {
          edges.emplace_back(poly.edges[j].x, poly.edges[j].y, poly.edges[j].z);
        }

        std::vector<std::vector<gp_Pnt>> inners;
        for (int j = 0; j < poly.innerArrayCount; j++) {
          std::vector<gp_Pnt> inner;
          for (int k = 0; k < poly.innerCounts[j]; k++) {
            inner.emplace_back(poly.inners[j][k].x, poly.inners[j][k].y,
                               poly.inners[j][k].z);
          }
          inners.push_back(inner);
        }

        inner_profiles.emplace_back(polygon_profile(edges, inners));
        break;
      }
      default:
        return nullptr;
      }
    }
    cpp_params.inner_profiles = inner_profiles;
  }

  // 转换线段类型
  if (params.segment_types != nullptr) {
    std::vector<segment_type> segment_types;
    for (int i = 0; i < params.segment_type_count; i++) {
      switch (params.segment_types[i]) {
      case SEGMENT_TYPE_LINE:
        segment_types.push_back(segment_type::LINE);
        break;
      case SEGMENT_TYPE_THREE_POINT_ARC:
        segment_types.push_back(segment_type::THREE_POINT_ARC);
        break;
      case SEGMENT_TYPE_CIRCLE_CENTER_ARC:
        segment_types.push_back(segment_type::CIRCLE_CENTER_ARC);
        break;
      case SEGMENT_TYPE_SPLINE:
        segment_types.push_back(segment_type::SPLINE);
        break;
      case SEGMENT_TYPE_BEZIER:
        segment_types.push_back(segment_type::BEZIER);
        break;
      default:
        return nullptr;
      }
    }
    cpp_params.segment_types = segment_types;
  }

  // 转换过渡模式
  switch (params.transition_mode) {
  case TRANSITION_RIGHT:
    cpp_params.transition_mode = transition_mode::RIGHT;
    break;
  case TRANSITION_ROUND:
    cpp_params.transition_mode = transition_mode::ROUND;
    break;
  case TRANSITION_TRANSFORMED:
    cpp_params.transition_mode = transition_mode::TRANSFORMED;
    break;
  default:
    return nullptr;
  }

  if (params.up_dir != nullptr) {
    cpp_params.upDir =
        gp_Dir(params.up_dir->x, params.up_dir->y, params.up_dir->z);
  }

  try {
    std::array<double, 2> distances = {start_distance, end_distance};
    return new topo_shape_t{.shp = std::make_shared<shape>(
                                create_multi_segment_pipe_with_split_distances(
                                    cpp_params, distances))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_multi_segment_pipe_with_place(multi_segment_pipe_params_t params,
                                     pnt3d_t position, dir3d_t direction,
                                     dir3d_t xDir) {
  multi_segment_pipe_params cpp_params;

  // 转换路径点
  std::vector<std::vector<gp_Pnt>> wires;
  for (int i = 0; i < params.wire_array_count; i++) {
    std::vector<gp_Pnt> wire;
    for (int j = 0; j < params.wire_counts[i]; j++) {
      wire.emplace_back(params.wires[i][j].x, params.wires[i][j].y,
                        params.wires[i][j].z);
    }
    wires.push_back(wire);
  }
  cpp_params.wires = wires;

  // 转换剖面类型
  std::vector<shape_profile> profiles;
  for (int i = 0; i < params.profile_count; i++) {
    switch (params.profiles[i].type_) {
    case PROFILE_TYPE_TRIANGLE: {
      auto &tri = params.profiles[i].triangle;
      profiles.emplace_back(
          triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                           gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                           gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z)));
      break;
    }
    case PROFILE_TYPE_RECTANGLE: {
      auto &rect = params.profiles[i].rectangle;
      profiles.emplace_back(
          rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                            gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z)));
      break;
    }
    case PROFILE_TYPE_CIRC: {
      auto &circ = params.profiles[i].circ;
      profiles.emplace_back(circ_profile(
          gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
          gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius));
      break;
    }
    case PROFILE_TYPE_ELIPS: {
      auto &elips = params.profiles[i].elips;
      profiles.emplace_back(elips_profile(
          gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
          gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
          gp_Pnt(elips.center.x, elips.center.y, elips.center.z)));
      break;
    }
    case PROFILE_TYPE_POLYGON: {
      auto &poly = params.profiles[i].polygon;
      std::vector<gp_Pnt> edges;
      for (int j = 0; j < poly.edgeCount; j++) {
        edges.emplace_back(poly.edges[j].x, poly.edges[j].y, poly.edges[j].z);
      }

      std::vector<std::vector<gp_Pnt>> inners;
      for (int j = 0; j < poly.innerArrayCount; j++) {
        std::vector<gp_Pnt> inner;
        for (int k = 0; k < poly.innerCounts[j]; k++) {
          inner.emplace_back(poly.inners[j][k].x, poly.inners[j][k].y,
                             poly.inners[j][k].z);
        }
        inners.push_back(inner);
      }

      profiles.emplace_back(polygon_profile(edges, inners));
      break;
    }
    default:
      return nullptr;
    }
  }
  cpp_params.profiles = profiles;

  // 转换内剖面(如果有)
  if (params.inner_profiles != nullptr) {
    std::vector<shape_profile> inner_profiles;
    for (int i = 0; i < params.inner_profile_counts[0]; i++) {
      switch (params.inner_profiles[0][i].type_) {
      case PROFILE_TYPE_TRIANGLE: {
        auto &tri = params.inner_profiles[0][i].triangle;
        inner_profiles.emplace_back(
            triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                             gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                             gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z)));
        break;
      }
      case PROFILE_TYPE_RECTANGLE: {
        auto &rect = params.inner_profiles[0][i].rectangle;
        inner_profiles.emplace_back(
            rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                              gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z)));
        break;
      }
      case PROFILE_TYPE_CIRC: {
        auto &circ = params.inner_profiles[0][i].circ;
        inner_profiles.emplace_back(circ_profile(
            gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
            gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius));
        break;
      }
      case PROFILE_TYPE_ELIPS: {
        auto &elips = params.inner_profiles[0][i].elips;
        inner_profiles.emplace_back(elips_profile(
            gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
            gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
            gp_Pnt(elips.center.x, elips.center.y, elips.center.z)));
        break;
      }
      case PROFILE_TYPE_POLYGON: {
        auto &poly = params.inner_profiles[0][i].polygon;
        std::vector<gp_Pnt> edges;
        for (int j = 0; j < poly.edgeCount; j++) {
          edges.emplace_back(poly.edges[j].x, poly.edges[j].y, poly.edges[j].z);
        }

        std::vector<std::vector<gp_Pnt>> inners;
        for (int j = 0; j < poly.innerArrayCount; j++) {
          std::vector<gp_Pnt> inner;
          for (int k = 0; k < poly.innerCounts[j]; k++) {
            inner.emplace_back(poly.inners[j][k].x, poly.inners[j][k].y,
                               poly.inners[j][k].z);
          }
          inners.push_back(inner);
        }

        inner_profiles.emplace_back(polygon_profile(edges, inners));
        break;
      }
      default:
        return nullptr;
      }
    }
    cpp_params.inner_profiles = inner_profiles;
  }

  // 转换线段类型
  if (params.segment_types != nullptr) {
    std::vector<segment_type> segment_types;
    for (int i = 0; i < params.segment_type_count; i++) {
      switch (params.segment_types[i]) {
      case SEGMENT_TYPE_LINE:
        segment_types.push_back(segment_type::LINE);
        break;
      case SEGMENT_TYPE_THREE_POINT_ARC:
        segment_types.push_back(segment_type::THREE_POINT_ARC);
        break;
      case SEGMENT_TYPE_CIRCLE_CENTER_ARC:
        segment_types.push_back(segment_type::CIRCLE_CENTER_ARC);
        break;
      case SEGMENT_TYPE_SPLINE:
        segment_types.push_back(segment_type::SPLINE);
        break;
      case SEGMENT_TYPE_BEZIER:
        segment_types.push_back(segment_type::BEZIER);
        break;
      default:
        return nullptr;
      }
    }
    cpp_params.segment_types = segment_types;
  }

  // 转换过渡模式
  switch (params.transition_mode) {
  case TRANSITION_RIGHT:
    cpp_params.transition_mode = transition_mode::RIGHT;
    break;
  case TRANSITION_ROUND:
    cpp_params.transition_mode = transition_mode::ROUND;
    break;
  case TRANSITION_TRANSFORMED:
    cpp_params.transition_mode = transition_mode::TRANSFORMED;
    break;
  default:
    return nullptr;
  }

  if (params.up_dir != nullptr) {
    cpp_params.upDir =
        gp_Dir(params.up_dir->x, params.up_dir->y, params.up_dir->z);
  }

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);

  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_multi_segment_pipe(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_pipe_joint(pipe_joint_params_t params) {
  pipe_joint_params cpp_params;

  // 转换输入端点
  std::vector<pipe_endpoint> ins;
  for (int i = 0; i < params.in_count; i++) {
    pipe_endpoint_t &ep = params.ins[i];
    pipe_endpoint cpp_ep;
    cpp_ep.id = ep.id;
    cpp_ep.offset = gp_Pnt(ep.offset.x, ep.offset.y, ep.offset.z);
    cpp_ep.normal = gp_Dir(ep.normal.x, ep.normal.y, ep.normal.z);

    // 转换剖面类型
    switch (ep.profile.type_) {
    case PROFILE_TYPE_TRIANGLE: {
      auto &tri = ep.profile.triangle;
      cpp_ep.profile = triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                                        gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                                        gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z));
      break;
    }
    case PROFILE_TYPE_RECTANGLE: {
      auto &rect = ep.profile.rectangle;
      cpp_ep.profile =
          rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                            gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z));
      break;
    }
    case PROFILE_TYPE_CIRC: {
      auto &circ = ep.profile.circ;
      cpp_ep.profile = circ_profile(
          gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
          gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius);
      break;
    }
    case PROFILE_TYPE_ELIPS: {
      auto &elips = ep.profile.elips;
      cpp_ep.profile =
          elips_profile(gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
                        gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
                        gp_Pnt(elips.center.x, elips.center.y, elips.center.z));
      break;
    }
    case PROFILE_TYPE_POLYGON: {
      auto &poly = ep.profile.polygon;
      std::vector<gp_Pnt> edges;
      for (int j = 0; j < poly.edgeCount; j++) {
        edges.emplace_back(poly.edges[j].x, poly.edges[j].y, poly.edges[j].z);
      }

      std::vector<std::vector<gp_Pnt>> inners;
      for (int j = 0; j < poly.innerArrayCount; j++) {
        std::vector<gp_Pnt> inner;
        for (int k = 0; k < poly.innerCounts[j]; k++) {
          inner.emplace_back(poly.inners[j][k].x, poly.inners[j][k].y,
                             poly.inners[j][k].z);
        }
        inners.push_back(inner);
      }

      cpp_ep.profile = polygon_profile(edges, inners);
      break;
    }
    default:
      return nullptr;
    }

    // 转换内剖面(如果有)
    if (ep.inner_profile != nullptr) {
      switch (ep.inner_profile->type_) {
      case PROFILE_TYPE_TRIANGLE: {
        auto &tri = ep.inner_profile->triangle;
        cpp_ep.inner_profile =
            triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                             gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                             gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z));
        break;
      }
      case PROFILE_TYPE_RECTANGLE: {
        auto &rect = ep.inner_profile->rectangle;
        cpp_ep.inner_profile =
            rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                              gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z));
        break;
      }
      case PROFILE_TYPE_CIRC: {
        auto &circ = ep.inner_profile->circ;
        cpp_ep.inner_profile = circ_profile(
            gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
            gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius);
        break;
      }
      case PROFILE_TYPE_ELIPS: {
        auto &elips = ep.inner_profile->elips;
        cpp_ep.inner_profile = elips_profile(
            gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
            gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
            gp_Pnt(elips.center.x, elips.center.y, elips.center.z));
        break;
      }
      case PROFILE_TYPE_POLYGON: {
        auto &poly = ep.inner_profile->polygon;
        std::vector<gp_Pnt> edges;
        for (int j = 0; j < poly.edgeCount; j++) {
          edges.emplace_back(poly.edges[j].x, poly.edges[j].y, poly.edges[j].z);
        }

        std::vector<std::vector<gp_Pnt>> inners;
        for (int j = 0; j < poly.innerArrayCount; j++) {
          std::vector<gp_Pnt> inner;
          for (int k = 0; k < poly.innerCounts[j]; k++) {
            inner.emplace_back(poly.inners[j][k].x, poly.inners[j][k].y,
                               poly.inners[j][k].z);
          }
          inners.push_back(inner);
        }

        cpp_ep.inner_profile = polygon_profile(edges, inners);
        break;
      }
      default:
        return nullptr;
      }
    }

    ins.push_back(cpp_ep);
  }
  cpp_params.ins = ins;

  // 转换输出端点
  std::vector<pipe_endpoint> outs;
  for (int i = 0; i < params.out_count; i++) {
    pipe_endpoint_t &ep = params.outs[i];
    pipe_endpoint cpp_ep;
    cpp_ep.id = ep.id;
    cpp_ep.offset = gp_Pnt(ep.offset.x, ep.offset.y, ep.offset.z);
    cpp_ep.normal = gp_Dir(ep.normal.x, ep.normal.y, ep.normal.z);

    // 转换剖面类型
    switch (ep.profile.type_) {
    case PROFILE_TYPE_TRIANGLE: {
      auto &tri = ep.profile.triangle;
      cpp_ep.profile = triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                                        gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                                        gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z));
      break;
    }
    case PROFILE_TYPE_RECTANGLE: {
      auto &rect = ep.profile.rectangle;
      cpp_ep.profile =
          rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                            gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z));
      break;
    }
    case PROFILE_TYPE_CIRC: {
      auto &circ = ep.profile.circ;
      cpp_ep.profile = circ_profile(
          gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
          gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius);
      break;
    }
    case PROFILE_TYPE_ELIPS: {
      auto &elips = ep.profile.elips;
      cpp_ep.profile =
          elips_profile(gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
                        gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
                        gp_Pnt(elips.center.x, elips.center.y, elips.center.z));
      break;
    }
    case PROFILE_TYPE_POLYGON: {
      auto &poly = ep.profile.polygon;
      std::vector<gp_Pnt> edges;
      for (int j = 0; j < poly.edgeCount; j++) {
        edges.emplace_back(poly.edges[j].x, poly.edges[j].y, poly.edges[j].z);
      }

      std::vector<std::vector<gp_Pnt>> inners;
      for (int j = 0; j < poly.innerArrayCount; j++) {
        std::vector<gp_Pnt> inner;
        for (int k = 0; k < poly.innerCounts[j]; k++) {
          inner.emplace_back(poly.inners[j][k].x, poly.inners[j][k].y,
                             poly.inners[j][k].z);
        }
        inners.push_back(inner);
      }

      cpp_ep.profile = polygon_profile(edges, inners);
      break;
    }
    default:
      throw Standard_ConstructionError("Invalid profile type");
    }

    // 转换内剖面(如果有)
    if (ep.inner_profile != nullptr) {
      switch (ep.inner_profile->type_) {
      case PROFILE_TYPE_TRIANGLE: {
        auto &tri = ep.inner_profile->triangle;
        cpp_ep.inner_profile =
            triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                             gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                             gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z));
        break;
      }
      case PROFILE_TYPE_RECTANGLE: {
        auto &rect = ep.inner_profile->rectangle;
        cpp_ep.inner_profile =
            rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                              gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z));
        break;
      }
      case PROFILE_TYPE_CIRC: {
        auto &circ = ep.inner_profile->circ;
        cpp_ep.inner_profile = circ_profile(
            gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
            gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius);
        break;
      }
      case PROFILE_TYPE_ELIPS: {
        auto &elips = ep.inner_profile->elips;
        cpp_ep.inner_profile = elips_profile(
            gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
            gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
            gp_Pnt(elips.center.x, elips.center.y, elips.center.z));
        break;
      }
      case PROFILE_TYPE_POLYGON: {
        auto &poly = ep.inner_profile->polygon;
        std::vector<gp_Pnt> edges;
        for (int j = 0; j < poly.edgeCount; j++) {
          edges.emplace_back(poly.edges[j].x, poly.edges[j].y, poly.edges[j].z);
        }

        std::vector<std::vector<gp_Pnt>> inners;
        for (int j = 0; j < poly.innerArrayCount; j++) {
          std::vector<gp_Pnt> inner;
          for (int k = 0; k < poly.innerCounts[j]; k++) {
            inner.emplace_back(poly.inners[j][k].x, poly.inners[j][k].y,
                               poly.inners[j][k].z);
          }
          inners.push_back(inner);
        }

        cpp_ep.inner_profile = polygon_profile(edges, inners);
        break;
      }
      default:
        return nullptr;
      }
    }

    outs.push_back(cpp_ep);
  }
  cpp_params.outs = outs;

  // 转换连接模式
  switch (params.mode) {
  case JOINT_SHAPE_MODE_SPHERE:
    cpp_params.mode = joint_shape_mode::SPHERE;
    break;
  case JOINT_SHAPE_MODE_BOX:
    cpp_params.mode = joint_shape_mode::BOX;
    break;
  case JOINT_SHAPE_MODE_CYLINDER:
    cpp_params.mode = joint_shape_mode::CYLINDER;
    break;
  default:
    return nullptr;
  }

  cpp_params.flanged = params.flanged;

  if (params.up_dir != nullptr) {
    cpp_params.upDir =
        gp_Dir(params.up_dir->x, params.up_dir->y, params.up_dir->z);
  }

  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_pipe_joint(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_pipe_joint_with_place(pipe_joint_params_t params, pnt3d_t position,
                             dir3d_t direction, dir3d_t xDir) {
  pipe_joint_params cpp_params;

  // 转换输入端点
  std::vector<pipe_endpoint> ins;
  for (int i = 0; i < params.in_count; i++) {
    pipe_endpoint_t &ep = params.ins[i];
    pipe_endpoint cpp_ep;
    cpp_ep.offset = gp_Pnt(ep.offset.x, ep.offset.y, ep.offset.z);
    cpp_ep.normal = gp_Dir(ep.normal.x, ep.normal.y, ep.normal.z);

    // 转换剖面类型
    switch (ep.profile.type_) {
    case PROFILE_TYPE_TRIANGLE: {
      auto &tri = ep.profile.triangle;
      cpp_ep.profile = triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                                        gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                                        gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z));
      break;
    }
    case PROFILE_TYPE_RECTANGLE: {
      auto &rect = ep.profile.rectangle;
      cpp_ep.profile =
          rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                            gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z));
      break;
    }
    case PROFILE_TYPE_CIRC: {
      auto &circ = ep.profile.circ;
      cpp_ep.profile = circ_profile(
          gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
          gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius);
      break;
    }
    case PROFILE_TYPE_ELIPS: {
      auto &elips = ep.profile.elips;
      cpp_ep.profile =
          elips_profile(gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
                        gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
                        gp_Pnt(elips.center.x, elips.center.y, elips.center.z));
      break;
    }
    case PROFILE_TYPE_POLYGON: {
      auto &poly = ep.profile.polygon;
      std::vector<gp_Pnt> edges;
      for (int j = 0; j < poly.edgeCount; j++) {
        edges.emplace_back(poly.edges[j].x, poly.edges[j].y, poly.edges[j].z);
      }

      std::vector<std::vector<gp_Pnt>> inners;
      for (int j = 0; j < poly.innerArrayCount; j++) {
        std::vector<gp_Pnt> inner;
        for (int k = 0; k < poly.innerCounts[j]; k++) {
          inner.emplace_back(poly.inners[j][k].x, poly.inners[j][k].y,
                             poly.inners[j][k].z);
        }
        inners.push_back(inner);
      }

      cpp_ep.profile = polygon_profile(edges, inners);
      break;
    }
    default:
      return nullptr;
    }

    // 转换内剖面(如果有)
    if (ep.inner_profile != nullptr) {
      switch (ep.inner_profile->type_) {
      case PROFILE_TYPE_TRIANGLE: {
        auto &tri = ep.inner_profile->triangle;
        cpp_ep.inner_profile =
            triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                             gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                             gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z));
        break;
      }
      case PROFILE_TYPE_RECTANGLE: {
        auto &rect = ep.inner_profile->rectangle;
        cpp_ep.inner_profile =
            rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                              gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z));
        break;
      }
      case PROFILE_TYPE_CIRC: {
        auto &circ = ep.inner_profile->circ;
        cpp_ep.inner_profile = circ_profile(
            gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
            gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius);
        break;
      }
      case PROFILE_TYPE_ELIPS: {
        auto &elips = ep.inner_profile->elips;
        cpp_ep.inner_profile = elips_profile(
            gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
            gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
            gp_Pnt(elips.center.x, elips.center.y, elips.center.z));
        break;
      }
      case PROFILE_TYPE_POLYGON: {
        auto &poly = ep.inner_profile->polygon;
        std::vector<gp_Pnt> edges;
        for (int j = 0; j < poly.edgeCount; j++) {
          edges.emplace_back(poly.edges[j].x, poly.edges[j].y, poly.edges[j].z);
        }

        std::vector<std::vector<gp_Pnt>> inners;
        for (int j = 0; j < poly.innerArrayCount; j++) {
          std::vector<gp_Pnt> inner;
          for (int k = 0; k < poly.innerCounts[j]; k++) {
            inner.emplace_back(poly.inners[j][k].x, poly.inners[j][k].y,
                               poly.inners[j][k].z);
          }
          inners.push_back(inner);
        }

        cpp_ep.inner_profile = polygon_profile(edges, inners);
        break;
      }
      default:
        return nullptr;
      }
    }

    ins.push_back(cpp_ep);
  }
  cpp_params.ins = ins;

  // 转换输出端点
  std::vector<pipe_endpoint> outs;
  for (int i = 0; i < params.out_count; i++) {
    pipe_endpoint_t &ep = params.outs[i];
    pipe_endpoint cpp_ep;
    cpp_ep.offset = gp_Pnt(ep.offset.x, ep.offset.y, ep.offset.z);
    cpp_ep.normal = gp_Dir(ep.normal.x, ep.normal.y, ep.normal.z);

    // 转换剖面类型
    switch (ep.profile.type_) {
    case PROFILE_TYPE_TRIANGLE: {
      auto &tri = ep.profile.triangle;
      cpp_ep.profile = triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                                        gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                                        gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z));
      break;
    }
    case PROFILE_TYPE_RECTANGLE: {
      auto &rect = ep.profile.rectangle;
      cpp_ep.profile =
          rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                            gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z));
      break;
    }
    case PROFILE_TYPE_CIRC: {
      auto &circ = ep.profile.circ;
      cpp_ep.profile = circ_profile(
          gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
          gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius);
      break;
    }
    case PROFILE_TYPE_ELIPS: {
      auto &elips = ep.profile.elips;
      cpp_ep.profile =
          elips_profile(gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
                        gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
                        gp_Pnt(elips.center.x, elips.center.y, elips.center.z));
      break;
    }
    case PROFILE_TYPE_POLYGON: {
      auto &poly = ep.profile.polygon;
      std::vector<gp_Pnt> edges;
      for (int j = 0; j < poly.edgeCount; j++) {
        edges.emplace_back(poly.edges[j].x, poly.edges[j].y, poly.edges[j].z);
      }

      std::vector<std::vector<gp_Pnt>> inners;
      for (int j = 0; j < poly.innerArrayCount; j++) {
        std::vector<gp_Pnt> inner;
        for (int k = 0; k < poly.innerCounts[j]; k++) {
          inner.emplace_back(poly.inners[j][k].x, poly.inners[j][k].y,
                             poly.inners[j][k].z);
        }
        inners.push_back(inner);
      }

      cpp_ep.profile = polygon_profile(edges, inners);
      break;
    }
    default:
      return nullptr;
    }

    // 转换内剖面(如果有)
    if (ep.inner_profile != nullptr) {
      switch (ep.inner_profile->type_) {
      case PROFILE_TYPE_TRIANGLE: {
        auto &tri = ep.inner_profile->triangle;
        cpp_ep.inner_profile =
            triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                             gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                             gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z));
        break;
      }
      case PROFILE_TYPE_RECTANGLE: {
        auto &rect = ep.inner_profile->rectangle;
        cpp_ep.inner_profile =
            rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                              gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z));
        break;
      }
      case PROFILE_TYPE_CIRC: {
        auto &circ = ep.inner_profile->circ;
        cpp_ep.inner_profile = circ_profile(
            gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
            gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius);
        break;
      }
      case PROFILE_TYPE_ELIPS: {
        auto &elips = ep.inner_profile->elips;
        cpp_ep.inner_profile = elips_profile(
            gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
            gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
            gp_Pnt(elips.center.x, elips.center.y, elips.center.z));
        break;
      }
      case PROFILE_TYPE_POLYGON: {
        auto &poly = ep.inner_profile->polygon;
        std::vector<gp_Pnt> edges;
        for (int j = 0; j < poly.edgeCount; j++) {
          edges.emplace_back(poly.edges[j].x, poly.edges[j].y, poly.edges[j].z);
        }

        std::vector<std::vector<gp_Pnt>> inners;
        for (int j = 0; j < poly.innerArrayCount; j++) {
          std::vector<gp_Pnt> inner;
          for (int k = 0; k < poly.innerCounts[j]; k++) {
            inner.emplace_back(poly.inners[j][k].x, poly.inners[j][k].y,
                               poly.inners[j][k].z);
          }
          inners.push_back(inner);
        }

        cpp_ep.inner_profile = polygon_profile(edges, inners);
        break;
      }
      default:
        return nullptr;
      }
    }

    outs.push_back(cpp_ep);
  }
  cpp_params.outs = outs;

  // 转换连接模式
  switch (params.mode) {
  case JOINT_SHAPE_MODE_SPHERE:
    cpp_params.mode = joint_shape_mode::SPHERE;
    break;
  case JOINT_SHAPE_MODE_BOX:
    cpp_params.mode = joint_shape_mode::BOX;
    break;
  case JOINT_SHAPE_MODE_CYLINDER:
    cpp_params.mode = joint_shape_mode::CYLINDER;
  default:
    return nullptr;
  }

  cpp_params.flanged = params.flanged;

  if (params.up_dir != nullptr) {
    cpp_params.upDir =
        gp_Dir(params.up_dir->x, params.up_dir->y, params.up_dir->z);
  }

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);

  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_pipe_joint(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_catenary(catenary_params_t params) {
  catenary_params cpp_params;

  // 转换端点
  cpp_params.p1 = gp_Pnt(params.p1.x, params.p1.y, params.p1.z);
  cpp_params.p2 = gp_Pnt(params.p2.x, params.p2.y, params.p2.z);

  // 转换剖面类型
  switch (params.profile.type_) {
  case PROFILE_TYPE_TRIANGLE: {
    auto &tri = params.profile.triangle;
    cpp_params.profile = triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                                          gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                                          gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z));
    break;
  }
  case PROFILE_TYPE_RECTANGLE: {
    auto &rect = params.profile.rectangle;
    cpp_params.profile =
        rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                          gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z));
    break;
  }
  case PROFILE_TYPE_CIRC: {
    auto &circ = params.profile.circ;
    cpp_params.profile = circ_profile(
        gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
        gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius);
    break;
  }
  case PROFILE_TYPE_ELIPS: {
    auto &elips = params.profile.elips;
    cpp_params.profile =
        elips_profile(gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
                      gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
                      gp_Pnt(elips.center.x, elips.center.y, elips.center.z));
    break;
  }
  case PROFILE_TYPE_POLYGON: {
    auto &poly = params.profile.polygon;
    std::vector<gp_Pnt> edges;
    for (int i = 0; i < poly.edgeCount; i++) {
      edges.emplace_back(poly.edges[i].x, poly.edges[i].y, poly.edges[i].z);
    }

    std::vector<std::vector<gp_Pnt>> inners;
    for (int i = 0; i < poly.innerArrayCount; i++) {
      std::vector<gp_Pnt> inner;
      for (int j = 0; j < poly.innerCounts[i]; j++) {
        inner.emplace_back(poly.inners[i][j].x, poly.inners[i][j].y,
                           poly.inners[i][j].z);
      }
      inners.push_back(inner);
    }

    cpp_params.profile = polygon_profile(edges, inners);
    break;
  }
  default:
    return nullptr;
  }

  cpp_params.slack = params.slack;
  cpp_params.maxSag = params.max_sag;
  cpp_params.tessellation = params.tessellation;

  if (params.up_dir != nullptr) {
    cpp_params.upDir =
        gp_Dir(params.up_dir->x, params.up_dir->y, params.up_dir->z);
  }

  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_catenary(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_catenary_with_place(catenary_params_t params,
                                                      pnt3d_t position,
                                                      dir3d_t direction,
                                                      dir3d_t xDir) {
  catenary_params cpp_params;

  // 转换端点
  cpp_params.p1 = gp_Pnt(params.p1.x, params.p1.y, params.p1.z);
  cpp_params.p2 = gp_Pnt(params.p2.x, params.p2.y, params.p2.z);

  // 转换剖面类型
  switch (params.profile.type_) {
  case PROFILE_TYPE_TRIANGLE: {
    auto &tri = params.profile.triangle;
    cpp_params.profile = triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                                          gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                                          gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z));
    break;
  }
  case PROFILE_TYPE_RECTANGLE: {
    auto &rect = params.profile.rectangle;
    cpp_params.profile =
        rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                          gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z));
    break;
  }
  case PROFILE_TYPE_CIRC: {
    auto &circ = params.profile.circ;
    cpp_params.profile = circ_profile(
        gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
        gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius);
    break;
  }
  case PROFILE_TYPE_ELIPS: {
    auto &elips = params.profile.elips;
    cpp_params.profile =
        elips_profile(gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
                      gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
                      gp_Pnt(elips.center.x, elips.center.y, elips.center.z));
    break;
  }
  case PROFILE_TYPE_POLYGON: {
    auto &poly = params.profile.polygon;
    std::vector<gp_Pnt> edges;
    for (int i = 0; i < poly.edgeCount; i++) {
      edges.emplace_back(poly.edges[i].x, poly.edges[i].y, poly.edges[i].z);
    }

    std::vector<std::vector<gp_Pnt>> inners;
    for (int i = 0; i < poly.innerArrayCount; i++) {
      std::vector<gp_Pnt> inner;
      for (int j = 0; j < poly.innerCounts[i]; j++) {
        inner.emplace_back(poly.inners[i][j].x, poly.inners[i][j].y,
                           poly.inners[i][j].z);
      }
      inners.push_back(inner);
    }

    cpp_params.profile = polygon_profile(edges, inners);
    break;
  }
  default:
    throw Standard_ConstructionError("Invalid profile type");
  }

  cpp_params.slack = params.slack;
  cpp_params.maxSag = params.max_sag;
  cpp_params.tessellation = params.tessellation;

  if (params.up_dir != nullptr) {
    cpp_params.upDir =
        gp_Dir(params.up_dir->x, params.up_dir->y, params.up_dir->z);
  }

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);

  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_catenary(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_box_shape(box_shape_params_t params) {
  box_shape_params cpp_params{
      gp_Pnt(params.point1.x, params.point1.y, params.point1.z),
      gp_Pnt(params.point2.x, params.point2.y, params.point2.z)};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_box_shape(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_box_shape_with_place(box_shape_params_t params, pnt3d_t position,
                            dir3d_t direction, dir3d_t xDir) {
  box_shape_params cpp_params{
      gp_Pnt(params.point1.x, params.point1.y, params.point1.z),
      gp_Pnt(params.point2.x, params.point2.y, params.point2.z)};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);

  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_box_shape(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_cone_shape(cone_shape_params_t params) {
  cone_shape_params cpp_params{
      params.radius1, params.radius2, params.height,
      params.angle ? boost::optional<double>(*params.angle) : boost::none};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cone_shape(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_cone_shape_with_place(cone_shape_params_t params, pnt3d_t position,
                             dir3d_t direction, dir3d_t xDir) {
  cone_shape_params cpp_params{
      params.radius1, params.radius2, params.height,
      params.angle ? boost::optional<double>(*params.angle) : boost::none};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);

  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cone_shape(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_cylinder_shape(cylinder_shape_params_t params) {
  cylinder_shape_params cpp_params{
      params.radius, params.height,
      params.angle ? boost::optional<double>(*params.angle) : boost::none};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cylinder_shape(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_cylinder_shape_with_place(cylinder_shape_params_t params,
                                 pnt3d_t position, dir3d_t direction,
                                 dir3d_t xDir) {
  cylinder_shape_params cpp_params{
      params.radius, params.height,
      params.angle ? boost::optional<double>(*params.angle) : boost::none};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);

  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cylinder_shape(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_revolution_shape(revolution_shape_params_t params) {
  revolution_shape_params cpp_params;

  // 转换子午线点
  std::vector<gp_Pnt> meridian;
  for (int i = 0; i < params.meridian_count; i++) {
    meridian.emplace_back(params.meridian[i].x, params.meridian[i].y,
                          params.meridian[i].z);
  }
  cpp_params.meridian = meridian;

  // 设置可选参数
  if (params.angle)
    cpp_params.angle = *params.angle;
  if (params.max)
    cpp_params.max = *params.max;
  if (params.min)
    cpp_params.min = *params.min;

  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_revolution_shape(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_revolution_shape_with_place(revolution_shape_params_t params,
                                   pnt3d_t position, dir3d_t direction,
                                   dir3d_t xDir) {
  revolution_shape_params cpp_params;

  // 转换子午线点
  std::vector<gp_Pnt> meridian;
  for (int i = 0; i < params.meridian_count; i++) {
    meridian.emplace_back(params.meridian[i].x, params.meridian[i].y,
                          params.meridian[i].z);
  }
  cpp_params.meridian = meridian;

  // 设置可选参数
  if (params.angle)
    cpp_params.angle = *params.angle;
  if (params.max)
    cpp_params.max = *params.max;
  if (params.min)
    cpp_params.min = *params.min;

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);

  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_revolution_shape(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_sphere_shape(sphere_shape_params_t params) {
  sphere_shape_params cpp_params{
      params.center ? boost::optional<gp_Pnt>(gp_Pnt(
                          params.center->x, params.center->y, params.center->z))
                    : boost::none,
      params.radius,
      params.angle1 ? boost::optional<double>(*params.angle1) : boost::none,
      params.angle2 ? boost::optional<double>(*params.angle2) : boost::none,
      params.angle ? boost::optional<double>(*params.angle) : boost::none};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_sphere_shape(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_sphere_shape_with_place(sphere_shape_params_t params, pnt3d_t position,
                               dir3d_t direction, dir3d_t xDir) {
  sphere_shape_params cpp_params{
      params.center ? boost::optional<gp_Pnt>(gp_Pnt(
                          params.center->x, params.center->y, params.center->z))
                    : boost::none,
      params.radius,
      params.angle1 ? boost::optional<double>(*params.angle1) : boost::none,
      params.angle2 ? boost::optional<double>(*params.angle2) : boost::none,
      params.angle ? boost::optional<double>(*params.angle) : boost::none};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);

  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_sphere_shape(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_torus_shape(torus_shape_params_t params) {
  torus_shape_params cpp_params{
      params.radius1, params.radius2,
      params.angle1 ? boost::optional<double>(*params.angle1) : boost::none,
      params.angle2 ? boost::optional<double>(*params.angle2) : boost::none,
      params.angle ? boost::optional<double>(*params.angle) : boost::none};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_torus_shape(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_torus_shape_with_place(torus_shape_params_t params, pnt3d_t position,
                              dir3d_t direction, dir3d_t xDir) {
  torus_shape_params cpp_params{
      params.radius1, params.radius2,
      params.angle1 ? boost::optional<double>(*params.angle1) : boost::none,
      params.angle2 ? boost::optional<double>(*params.angle2) : boost::none,
      params.angle ? boost::optional<double>(*params.angle) : boost::none};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);

  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_torus_shape(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_wedge_shape(wedge_shape_params_t params) {
  wedge_shape_params cpp_params;
  cpp_params.edge = gp_Pnt(params.edge.x, params.edge.y, params.edge.z);

  // 转换楔形面限制
  if (params.limit != nullptr) {
    wedge_face_limit limit;
    limit[0] = params.limit->values[0];
    limit[1] = params.limit->values[1];
    limit[2] = params.limit->values[2];
    limit[3] = params.limit->values[3];
    cpp_params.limit = limit;
  }

  // 转换ltx参数
  if (params.ltx != nullptr) {
    cpp_params.ltx = *params.ltx;
  }

  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_wedge_shape(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_wedge_shape_with_place(wedge_shape_params_t params, pnt3d_t position,
                              dir3d_t direction, dir3d_t xDir) {
  wedge_shape_params cpp_params;
  cpp_params.edge = gp_Pnt(params.edge.x, params.edge.y, params.edge.z);

  // 转换楔形面限制
  if (params.limit != nullptr) {
    wedge_face_limit limit;
    limit[0] = params.limit->values[0];
    limit[1] = params.limit->values[1];
    limit[2] = params.limit->values[2];
    limit[3] = params.limit->values[3];
    cpp_params.limit = limit;
  }

  // 转换ltx参数
  if (params.ltx != nullptr) {
    cpp_params.ltx = *params.ltx;
  }

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);

  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_wedge_shape(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *create_pipe_shape(pipe_shape_params_t params) {
  pipe_shape_params cpp_params;

  // 转换管道线
  cpp_params.wire[0] =
      gp_Pnt(params.wire[0].x, params.wire[0].y, params.wire[0].z);
  cpp_params.wire[1] =
      gp_Pnt(params.wire[1].x, params.wire[1].y, params.wire[1].z);

  // 转换剖面类型
  switch (params.profile.type_) {
  case PROFILE_TYPE_TRIANGLE: {
    auto &tri = params.profile.triangle;
    cpp_params.profile = triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                                          gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                                          gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z));
    break;
  }
  case PROFILE_TYPE_RECTANGLE: {
    auto &rect = params.profile.rectangle;
    cpp_params.profile =
        rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                          gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z));
    break;
  }
  case PROFILE_TYPE_CIRC: {
    auto &circ = params.profile.circ;
    cpp_params.profile = circ_profile(
        gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
        gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius);
    break;
  }
  case PROFILE_TYPE_ELIPS: {
    auto &elips = params.profile.elips;
    cpp_params.profile =
        elips_profile(gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
                      gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
                      gp_Pnt(elips.center.x, elips.center.y, elips.center.z));
    break;
  }
  case PROFILE_TYPE_POLYGON: {
    auto &poly = params.profile.polygon;
    std::vector<gp_Pnt> edges;
    for (int i = 0; i < poly.edgeCount; i++) {
      edges.emplace_back(poly.edges[i].x, poly.edges[i].y, poly.edges[i].z);
    }

    std::vector<std::vector<gp_Pnt>> inners;
    for (int i = 0; i < poly.innerArrayCount; i++) {
      std::vector<gp_Pnt> inner;
      for (int j = 0; j < poly.innerCounts[i]; j++) {
        inner.emplace_back(poly.inners[i][j].x, poly.inners[i][j].y,
                           poly.inners[i][j].z);
      }
      inners.push_back(inner);
    }

    cpp_params.profile = polygon_profile(edges, inners);
    break;
  }
  default:
    return nullptr;
  }

  if (params.up_dir != nullptr) {
    cpp_params.upDir =
        gp_Dir(params.up_dir->x, params.up_dir->y, params.up_dir->z);
  }

  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_pipe_shape(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_pipe_shape_with_place(pipe_shape_params_t params, pnt3d_t position,
                             dir3d_t direction, dir3d_t xDir) {
  pipe_shape_params cpp_params;

  // 转换管道线
  cpp_params.wire[0] =
      gp_Pnt(params.wire[0].x, params.wire[0].y, params.wire[0].z);
  cpp_params.wire[1] =
      gp_Pnt(params.wire[1].x, params.wire[1].y, params.wire[1].z);

  // 转换剖面类型
  switch (params.profile.type_) {
  case PROFILE_TYPE_TRIANGLE: {
    auto &tri = params.profile.triangle;
    cpp_params.profile = triangle_profile(gp_Pnt(tri.p1.x, tri.p1.y, tri.p1.z),
                                          gp_Pnt(tri.p2.x, tri.p2.y, tri.p2.z),
                                          gp_Pnt(tri.p3.x, tri.p3.y, tri.p3.z));
    break;
  }
  case PROFILE_TYPE_RECTANGLE: {
    auto &rect = params.profile.rectangle;
    cpp_params.profile =
        rectangle_profile(gp_Pnt(rect.p1.x, rect.p1.y, rect.p1.z),
                          gp_Pnt(rect.p2.x, rect.p2.y, rect.p2.z));
    break;
  }
  case PROFILE_TYPE_CIRC: {
    auto &circ = params.profile.circ;
    cpp_params.profile = circ_profile(
        gp_Pnt(circ.center.x, circ.center.y, circ.center.z),
        gp_Dir(circ.norm.x, circ.norm.y, circ.norm.z), circ.radius);
    break;
  }
  case PROFILE_TYPE_ELIPS: {
    auto &elips = params.profile.elips;
    cpp_params.profile =
        elips_profile(gp_Pnt(elips.s1.x, elips.s1.y, elips.s1.z),
                      gp_Pnt(elips.s2.x, elips.s2.y, elips.s2.z),
                      gp_Pnt(elips.center.x, elips.center.y, elips.center.z));
    break;
  }
  case PROFILE_TYPE_POLYGON: {
    auto &poly = params.profile.polygon;
    std::vector<gp_Pnt> edges;
    for (int i = 0; i < poly.edgeCount; i++) {
      edges.emplace_back(poly.edges[i].x, poly.edges[i].y, poly.edges[i].z);
    }

    std::vector<std::vector<gp_Pnt>> inners;
    for (int i = 0; i < poly.innerArrayCount; i++) {
      std::vector<gp_Pnt> inner;
      for (int j = 0; j < poly.innerCounts[i]; j++) {
        inner.emplace_back(poly.inners[i][j].x, poly.inners[i][j].y,
                           poly.inners[i][j].z);
      }
      inners.push_back(inner);
    }

    cpp_params.profile = polygon_profile(edges, inners);
    break;
  }
  default:
    return nullptr;
  }

  if (params.up_dir != nullptr) {
    cpp_params.upDir =
        gp_Dir(params.up_dir->x, params.up_dir->y, params.up_dir->z);
  }

  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);

  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_pipe_shape(
            cpp_params, cpp_position, cpp_direction, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

#ifdef __cplusplus
}
#endif
