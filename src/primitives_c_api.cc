#include "primitives_c_api.h"
#include "primitives.hh"
#include "shape.hh"
#include "topo_impl.hh"

using namespace flywave::topo;

#ifdef __cplusplus
extern "C" {
#endif

PRIMCAPICALL topo_shape_t *create_sphere(sphere_params_t params) {
  sphere_params cpp_params{params.radius};
  return new topo_shape_t{std::make_shared<shape>(create_sphere(cpp_params))};
}

PRIMCAPICALL topo_shape_t *create_sphere_with_place(sphere_params_t params,
                                                    pnt3d_t center) {
  sphere_params cpp_params{params.radius};
  gp_Pnt cpp_center(center.x, center.y, center.z);
  return new topo_shape_t{
      std::make_shared<shape>(create_sphere(cpp_params, cpp_center))};
}

PRIMCAPICALL topo_shape_t *
create_rotational_ellipsoid(rotational_ellipsoid_params_t params) {
  rotational_ellipsoid_params cpp_params{
      params.polarRadius, params.equatorialRadius, params.height};
  return new topo_shape_t{
      std::make_shared<shape>(create_rotational_ellipsoid(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_rotational_ellipsoid_with_place(rotational_ellipsoid_params_t params,
                                       pnt3d_t center, dir3d_t xDir) {
  rotational_ellipsoid_params cpp_params{
      params.polarRadius, params.equatorialRadius, params.height};
  gp_Pnt cpp_center(center.x, center.y, center.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_rotational_ellipsoid(cpp_params, cpp_center, cpp_xDir))};
}

PRIMCAPICALL topo_shape_t *create_cuboid(cuboid_params_t params) {
  cuboid_params cpp_params{params.length, params.width, params.height};
  return new topo_shape_t{std::make_shared<shape>(create_cuboid(cpp_params))};
}

PRIMCAPICALL topo_shape_t *create_cuboid_with_place(cuboid_params_t params,
                                                    pnt3d_t center,
                                                    dir3d_t xDir,
                                                    dir3d_t zDir) {
  cuboid_params cpp_params{params.length, params.width, params.height};
  gp_Pnt cpp_center(center.x, center.y, center.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  gp_Dir cpp_zDir(zDir.x, zDir.y, zDir.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_cuboid(cpp_params, cpp_center, cpp_xDir, cpp_zDir))};
}

PRIMCAPICALL topo_shape_t *create_diamond_frustum(diamond_frustum_t params) {
  diamond_frustum cpp_params{params.topDiag1, params.topDiag2,
                             params.bottomDiag1, params.bottomDiag2,
                             params.height};
  return new topo_shape_t{
      std::make_shared<shape>(create_diamond_frustum(cpp_params))};
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
  return new topo_shape_t{std::make_shared<shape>(
      create_diamond_frustum(cpp_params, cpp_position, cpp_normal, cpp_xDir))};
}

PRIMCAPICALL topo_shape_t *
create_offset_rectangular_table(offset_rectangular_table_params_t params) {
  offset_rectangular_table_params cpp_params{
      params.topLength,   params.topWidth, params.bottomLength,
      params.bottomWidth, params.height,   params.xOffset,
      params.yOffset};
  return new topo_shape_t{
      std::make_shared<shape>(create_offset_rectangular_table(cpp_params))};
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
  return new topo_shape_t{
      std::make_shared<shape>(create_offset_rectangular_table(
          cpp_params, cpp_position, cpp_normal, cpp_xDir))};
}

PRIMCAPICALL topo_shape_t *create_cylinder(cylinder_params_t params) {
  cylinder_params cpp_params{params.radius, params.height};
  return new topo_shape_t{std::make_shared<shape>(create_cylinder(cpp_params))};
}

PRIMCAPICALL topo_shape_t *create_cylinder_with_place(cylinder_params_t params,
                                                      pnt3d_t baseCenter,
                                                      dir3d_t axisDir) {
  cylinder_params cpp_params{params.radius, params.height};
  gp_Pnt cpp_baseCenter(baseCenter.x, baseCenter.y, baseCenter.z);
  gp_Dir cpp_axisDir(axisDir.x, axisDir.y, axisDir.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_cylinder(cpp_params, cpp_baseCenter, cpp_axisDir))};
}

PRIMCAPICALL topo_shape_t *
create_sharp_bent_cylinder(sharp_bent_cylinder_params_t params) {
  sharp_bent_cylinder_params cpp_params{params.radius, params.length,
                                        params.bendAngle};
  return new topo_shape_t{
      std::make_shared<shape>(create_sharp_bent_cylinder(cpp_params))};
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
  return new topo_shape_t{std::make_shared<shape>(create_sharp_bent_cylinder(
      cpp_params, cpp_bendPoint, cpp_initialDir, cpp_bendPlaneNormal))};
}

PRIMCAPICALL topo_shape_t *
create_truncated_cone(truncated_cone_params_t params) {
  truncated_cone_params cpp_params{params.topRadius, params.bottomRadius,
                                   params.height};
  return new topo_shape_t{
      std::make_shared<shape>(create_truncated_cone(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_truncated_cone_with_place(truncated_cone_params_t params,
                                 pnt3d_t baseCenter, dir3d_t axisDir) {
  truncated_cone_params cpp_params{params.topRadius, params.bottomRadius,
                                   params.height};
  gp_Pnt cpp_baseCenter(baseCenter.x, baseCenter.y, baseCenter.z);
  gp_Dir cpp_axisDir(axisDir.x, axisDir.y, axisDir.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_truncated_cone(cpp_params, cpp_baseCenter, cpp_axisDir))};
}

PRIMCAPICALL topo_shape_t *
create_eccentric_truncated_cone(eccentric_truncated_cone_params_t params) {
  eccentric_truncated_cone_params cpp_params{
      params.topRadius, params.bottomRadius, params.height, params.topXOffset,
      params.topYOffset};
  return new topo_shape_t{
      std::make_shared<shape>(create_eccentric_truncated_cone(cpp_params))};
}

PRIMCAPICALL topo_shape_t *create_eccentric_truncated_cone_with_place(
    eccentric_truncated_cone_params_t params, pnt3d_t baseCenter,
    dir3d_t axisDir) {
  eccentric_truncated_cone_params cpp_params{
      params.topRadius, params.bottomRadius, params.height, params.topXOffset,
      params.topYOffset};
  gp_Pnt cpp_baseCenter(baseCenter.x, baseCenter.y, baseCenter.z);
  gp_Dir cpp_axisDir(axisDir.x, axisDir.y, axisDir.z);
  return new topo_shape_t{
      std::make_shared<shape>(create_eccentric_truncated_cone(
          cpp_params, cpp_baseCenter, cpp_axisDir))};
}

PRIMCAPICALL topo_shape_t *create_ring(ring_params_t params) {
  ring_params cpp_params{params.ringRadius, params.tubeRadius, params.angle};
  return new topo_shape_t{std::make_shared<shape>(create_ring(cpp_params))};
}

PRIMCAPICALL topo_shape_t *create_ring_with_place(ring_params_t params,
                                                  pnt3d_t center,
                                                  dir3d_t normal,
                                                  dir3d_t xDir) {
  ring_params cpp_params{params.ringRadius, params.tubeRadius, params.angle};
  gp_Pnt cpp_center(center.x, center.y, center.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_ring(cpp_params, cpp_center, cpp_normal, cpp_xDir))};
}

PRIMCAPICALL topo_shape_t *
create_rectangular_ring(rectangular_ring_params_t params) {
  rectangular_ring_params cpp_params{params.tubeRadius, params.filletRadius,
                                     params.length, params.width};
  return new topo_shape_t{
      std::make_shared<shape>(create_rectangular_ring(cpp_params))};
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
  return new topo_shape_t{std::make_shared<shape>(
      create_rectangular_ring(cpp_params, cpp_center, cpp_normal, cpp_xDir))};
}

PRIMCAPICALL topo_shape_t *create_elliptic_ring(elliptic_ring_params_t params) {
  elliptic_ring_params cpp_params{params.tubeRadius, params.majorRadius,
                                  params.minorRadius};
  return new topo_shape_t{
      std::make_shared<shape>(create_elliptic_ring(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_elliptic_ring_with_place(elliptic_ring_params_t params, pnt3d_t center,
                                dir3d_t normal, dir3d_t xDir) {
  elliptic_ring_params cpp_params{params.tubeRadius, params.majorRadius,
                                  params.minorRadius};
  gp_Pnt cpp_center(center.x, center.y, center.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_elliptic_ring(cpp_params, cpp_center, cpp_normal, cpp_xDir))};
}

PRIMCAPICALL topo_shape_t *
create_circular_gasket(circular_gasket_params_t params) {
  circular_gasket_params cpp_params{params.outerRadius, params.innerRadius,
                                    params.height, params.angle};
  return new topo_shape_t{
      std::make_shared<shape>(create_circular_gasket(cpp_params))};
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
  return new topo_shape_t{std::make_shared<shape>(
      create_circular_gasket(cpp_params, cpp_center, cpp_normal, cpp_xDir))};
}

PRIMCAPICALL topo_shape_t *create_table_gasket(table_gasket_params_t params) {
  table_gasket_params cpp_params{params.topRadius, params.outerRadius,
                                 params.innerRadius, params.height,
                                 params.angle};
  return new topo_shape_t{
      std::make_shared<shape>(create_table_gasket(cpp_params))};
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
  return new topo_shape_t{std::make_shared<shape>(
      create_table_gasket(cpp_params, cpp_center, cpp_normal, cpp_xDir))};
}

PRIMCAPICALL topo_shape_t *create_square_gasket(square_gasket_params_t params) {
  square_gasket_params cpp_params{params.outerLength, params.outerWidth,
                                  params.innerLength, params.innerWidth,
                                  params.height,      params.cornerType,
                                  params.cornerParam};
  return new topo_shape_t{
      std::make_shared<shape>(create_square_gasket(cpp_params))};
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
  return new topo_shape_t{std::make_shared<shape>(
      create_square_gasket(cpp_params, cpp_center, cpp_normal, cpp_xDir))};
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
  return new topo_shape_t{
      std::make_shared<shape>(create_stretched_body(cpp_params))};
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
  return new topo_shape_t{std::make_shared<shape>(
      create_stretched_body(cpp_params, cpp_basePoint, cpp_xDir))};
}

PRIMCAPICALL topo_shape_t *
create_porcelain_bushing(porcelain_bushing_params_t params) {
  porcelain_bushing_params cpp_params{params.height, params.radius,
                                      params.bigSkirtRadius,
                                      params.smallSkirtRadius, params.count};
  return new topo_shape_t{
      std::make_shared<shape>(create_porcelain_bushing(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_porcelain_bushing_with_place(porcelain_bushing_params_t params,
                                    pnt3d_t basePoint, dir3d_t axisDir) {
  porcelain_bushing_params cpp_params{params.height, params.radius,
                                      params.bigSkirtRadius,
                                      params.smallSkirtRadius, params.count};
  gp_Pnt cpp_basePoint(basePoint.x, basePoint.y, basePoint.z);
  gp_Dir cpp_axisDir(axisDir.x, axisDir.y, axisDir.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_porcelain_bushing(cpp_params, cpp_basePoint, cpp_axisDir))};
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
  return new topo_shape_t{
      std::make_shared<shape>(create_cone_porcelain_bushing(cpp_params))};
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
  return new topo_shape_t{std::make_shared<shape>(
      create_cone_porcelain_bushing(cpp_params, cpp_basePoint, cpp_axisDir))};
}

PRIMCAPICALL topo_shape_t *
create_insulator_string(insulator_string_params_t params) {
  insulator_string_params cpp_params{
      params.count,     params.spacing,        params.insulatorCount,
      params.height,    params.bigSkirtRadius, params.smallSkirtRadius,
      params.radius,    params.frontLength,    params.backLength,
      params.splitCount};
  return new topo_shape_t{
      std::make_shared<shape>(create_insulator_string(cpp_params))};
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
  return new topo_shape_t{std::make_shared<shape>(create_insulator_string(
      cpp_params, cpp_position, cpp_direction, cpp_upDirection))};
}

PRIMCAPICALL topo_shape_t *
create_vtype_insulator(vtype_insulator_params_t params) {
  vtype_insulator_params cpp_params{
      params.frontSpacing,     params.backSpacing, params.insulatorCount,
      params.height,           params.radius,      params.bigSkirtRadius,
      params.smallSkirtRadius, params.frontLength, params.backLength,
      params.splitCount};
  return new topo_shape_t{
      std::make_shared<shape>(create_vtype_insulator(cpp_params))};
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
  return new topo_shape_t{std::make_shared<shape>(create_vtype_insulator(
      cpp_params, cpp_position, cpp_direction, cpp_upDirection))};
}

PRIMCAPICALL topo_shape_t *
create_terminal_block(terminal_block_params_t params) {
  terminal_block_params cpp_params{
      params.length,        params.width,         params.thickness,
      params.chamferLength, params.columnSpacing, params.rowSpacing,
      params.holeRadius,    params.columnCount,   params.rowCount,
      params.bottomOffset,  params.phase};
  return new topo_shape_t{
      std::make_shared<shape>(create_terminal_block(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_terminal_block_with_place(terminal_block_params_t params,
                                 pnt3d_t position, dir3d_t lengthDir,
                                 dir3d_t widthDir) {
  terminal_block_params cpp_params{
      params.length,        params.width,         params.thickness,
      params.chamferLength, params.columnSpacing, params.rowSpacing,
      params.holeRadius,    params.columnCount,   params.rowCount,
      params.bottomOffset,  params.phase};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_lengthDir(lengthDir.x, lengthDir.y, lengthDir.z);
  gp_Dir cpp_widthDir(widthDir.x, widthDir.y, widthDir.z);
  return new topo_shape_t{std::make_shared<shape>(create_terminal_block(
      cpp_params, cpp_position, cpp_lengthDir, cpp_widthDir))};
}

PRIMCAPICALL topo_shape_t *
create_rectangular_fixed_plate(rectangular_hole_plate_params_t params) {
  rectangular_hole_plate_params cpp_params{
      params.length,        params.width,         params.thickness,
      params.columnSpacing, params.rowSpacing,    params.columnCount,
      params.rowCount,      params.hasMiddleHole, params.holeDiameter};
  return new topo_shape_t{
      std::make_shared<shape>(create_rectangular_fixed_plate(cpp_params))};
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
  return new topo_shape_t{
      std::make_shared<shape>(create_rectangular_fixed_plate(
          cpp_params, cpp_position, cpp_lengthDir, cpp_widthDir))};
}

PRIMCAPICALL topo_shape_t *
create_circular_fixed_plate(circular_fixed_plate_params_t params) {
  circular_fixed_plate_params cpp_params{
      params.length,      params.width,     params.thickness,
      params.ringRadius,  params.holeCount, params.hasMiddleHole,
      params.holeDiameter};
  return new topo_shape_t{
      std::make_shared<shape>(create_circular_fixed_plate(cpp_params))};
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
  return new topo_shape_t{std::make_shared<shape>(create_circular_fixed_plate(
      cpp_params, cpp_position, cpp_lengthDir, cpp_widthDir))};
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
  return new topo_shape_t{std::make_shared<shape>(create_wire(cpp_params))};
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
  return new topo_shape_t{std::make_shared<shape>(
      create_wire(cpp_params, cpp_position, cpp_direction, cpp_upDirection))};
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
  return new topo_shape_t{std::make_shared<shape>(create_cable(cpp_params))};
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
  return new topo_shape_t{std::make_shared<shape>(
      create_cable(cpp_params, cpp_position, cpp_direction, cpp_upDirection))};
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
      case CURVE_TYPE_SPLINE:
        cpp_curveTypes.push_back(curve_type::SPLINE);
        break;
      }
    }

    curve_cable_params cpp_params{cpp_controlPoints, cpp_curveTypes,
                                  params.diameter};
    return new topo_shape_t{
        std::make_shared<shape>(create_curve_cable(cpp_params))};
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
      case CURVE_TYPE_SPLINE:
        cpp_curveTypes.push_back(curve_type::SPLINE);
        break;
      }
    }

    curve_cable_params cpp_params{cpp_controlPoints, cpp_curveTypes,
                                  params.diameter};
    gp_Pnt cpp_position(position.x, position.y, position.z);
    gp_Dir cpp_direction(direction.x, direction.y, direction.z);
    gp_Dir cpp_upDirection(upDirection.x, upDirection.y, upDirection.z);

    return new topo_shape_t{std::make_shared<shape>(create_curve_cable(
        cpp_params, cpp_position, cpp_direction, cpp_upDirection))};
  } catch (...) {
    return nullptr;
  }
}

PRIMCAPICALL topo_shape_t *
create_equilateral_angle_steel(equilateral_angle_steel_params_t params) {
  equilateral_angle_steel_params cpp_params{params.L, params.X, params.length};
  return new topo_shape_t{
      std::make_shared<shape>(create_equilateral_angle_steel(cpp_params))};
}

PRIMCAPICALL topo_shape_t *create_equilateral_angle_steel_with_place(
    equilateral_angle_steel_params_t params, pnt3d_t position, dir3d_t xDir,
    dir3d_t yDir) {
  equilateral_angle_steel_params cpp_params{params.L, params.X, params.length};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  gp_Dir cpp_yDir(yDir.x, yDir.y, yDir.z);
  return new topo_shape_t{
      std::make_shared<shape>(create_equilateral_angle_steel(
          cpp_params, cpp_position, cpp_xDir, cpp_yDir))};
}

PRIMCAPICALL topo_shape_t *
create_scalene_angle_steel(scalene_angle_steel_params_t params) {
  scalene_angle_steel_params cpp_params{params.L1, params.L2, params.X,
                                        params.length};
  return new topo_shape_t{
      std::make_shared<shape>(create_scalene_angle_steel(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_scalene_angle_steel_with_place(scalene_angle_steel_params_t params,
                                      pnt3d_t position, dir3d_t xDir,
                                      dir3d_t longEdgeDir) {
  scalene_angle_steel_params cpp_params{params.L1, params.L2, params.X,
                                        params.length};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  gp_Dir cpp_longEdgeDir(longEdgeDir.x, longEdgeDir.y, longEdgeDir.z);
  return new topo_shape_t{std::make_shared<shape>(create_scalene_angle_steel(
      cpp_params, cpp_position, cpp_xDir, cpp_longEdgeDir))};
}

PRIMCAPICALL topo_shape_t *create_ibeam(ibeam_params_t params) {
  ibeam_params cpp_params{params.height,       params.flangeWidth,
                          params.webThickness, params.flangeThickness,
                          params.radius,       params.length};
  return new topo_shape_t{std::make_shared<shape>(create_ibeam(cpp_params))};
}

PRIMCAPICALL topo_shape_t *create_ibeam_with_place(ibeam_params_t params,
                                                   pnt3d_t position,
                                                   dir3d_t xDir, dir3d_t zDir) {
  ibeam_params cpp_params{params.height,       params.flangeWidth,
                          params.webThickness, params.flangeThickness,
                          params.radius,       params.length};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  gp_Dir cpp_zDir(zDir.x, zDir.y, zDir.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_ibeam(cpp_params, cpp_position, cpp_xDir, cpp_zDir))};
}

PRIMCAPICALL topo_shape_t *create_light_ibeam(light_ibeam_params_t params) {
  light_ibeam_params cpp_params{params.height,       params.flangeWidth,
                                params.webThickness, params.flangeThickness,
                                params.radius,       params.length,
                                params.flangeSlope};
  return new topo_shape_t{
      std::make_shared<shape>(create_light_ibeam(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_light_ibeam_with_place(light_ibeam_params_t params, pnt3d_t position,
                              dir3d_t xDir, dir3d_t zDir) {
  light_ibeam_params cpp_params{params.height,       params.flangeWidth,
                                params.webThickness, params.flangeThickness,
                                params.radius,       params.length,
                                params.flangeSlope};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  gp_Dir cpp_zDir(zDir.x, zDir.y, zDir.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_light_ibeam(cpp_params, cpp_position, cpp_xDir, cpp_zDir))};
}

PRIMCAPICALL topo_shape_t *create_hbeam(hbeam_params_t params) {
  hbeam_params cpp_params{params.height,       params.flangeWidth,
                          params.webThickness, params.flangeThickness,
                          params.radius,       params.length};
  return new topo_shape_t{std::make_shared<shape>(create_hbeam(cpp_params))};
}

PRIMCAPICALL topo_shape_t *create_hbeam_with_place(hbeam_params_t params,
                                                   pnt3d_t position,
                                                   dir3d_t xDir, dir3d_t zDir) {
  hbeam_params cpp_params{params.height,       params.flangeWidth,
                          params.webThickness, params.flangeThickness,
                          params.radius,       params.length};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  gp_Dir cpp_zDir(zDir.x, zDir.y, zDir.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_hbeam(cpp_params, cpp_position, cpp_xDir, cpp_zDir))};
}

PRIMCAPICALL topo_shape_t *create_beam_channel(beam_channel_params_t params) {
  beam_channel_params cpp_params{params.height,       params.flangeWidth,
                                 params.webThickness, params.flangeThickness,
                                 params.radius,       params.length};
  return new topo_shape_t{
      std::make_shared<shape>(create_beam_channel(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_beam_channel_with_place(beam_channel_params_t params, pnt3d_t position,
                               dir3d_t xDir, dir3d_t zDir) {
  beam_channel_params cpp_params{params.height,       params.flangeWidth,
                                 params.webThickness, params.flangeThickness,
                                 params.radius,       params.length};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  gp_Dir cpp_zDir(zDir.x, zDir.y, zDir.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_beam_channel(cpp_params, cpp_position, cpp_xDir, cpp_zDir))};
}

PRIMCAPICALL topo_shape_t *
create_light_beam_channel(light_beam_channel_params_t params) {
  light_beam_channel_params cpp_params{
      params.height,          params.flangeWidth, params.webThickness,
      params.flangeThickness, params.radius,      params.length,
      params.flangeSlope};
  return new topo_shape_t{
      std::make_shared<shape>(create_light_beam_channel(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_light_beam_channel_with_place(light_beam_channel_params_t params,
                                     pnt3d_t position, dir3d_t xDir,
                                     dir3d_t zDir) {
  light_beam_channel_params cpp_params{
      params.height,          params.flangeWidth, params.webThickness,
      params.flangeThickness, params.radius,      params.length,
      params.flangeSlope};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  gp_Dir cpp_zDir(zDir.x, zDir.y, zDir.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_light_beam_channel(cpp_params, cpp_position, cpp_xDir, cpp_zDir))};
}

PRIMCAPICALL topo_shape_t *create_flat_steel(flat_steel_params_t params) {
  flat_steel_params cpp_params{params.width, params.thickness, params.length};
  return new topo_shape_t{
      std::make_shared<shape>(create_flat_steel(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_flat_steel_with_place(flat_steel_params_t params, pnt3d_t position,
                             dir3d_t xDir, dir3d_t zDir) {
  flat_steel_params cpp_params{params.width, params.thickness, params.length};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  gp_Dir cpp_zDir(zDir.x, zDir.y, zDir.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_flat_steel(cpp_params, cpp_position, cpp_xDir, cpp_zDir))};
}

PRIMCAPICALL topo_shape_t *create_lsteel(lsteel_params_t params) {
  lsteel_params cpp_params{params.height, params.width, params.thickness,
                           params.radius, params.length};
  return new topo_shape_t{std::make_shared<shape>(create_lsteel(cpp_params))};
}

PRIMCAPICALL topo_shape_t *create_lsteel_with_place(lsteel_params_t params,
                                                    pnt3d_t position,
                                                    dir3d_t xDir,
                                                    dir3d_t zDir) {
  lsteel_params cpp_params{params.height, params.width, params.thickness,
                           params.radius, params.length};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  gp_Dir cpp_zDir(zDir.x, zDir.y, zDir.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_lsteel(cpp_params, cpp_position, cpp_xDir, cpp_zDir))};
}

PRIMCAPICALL topo_shape_t *create_tsteel(tsteel_params_t params) {
  tsteel_params cpp_params{params.height,       params.width,
                           params.webThickness, params.flangeThickness,
                           params.radius,       params.length};
  return new topo_shape_t{std::make_shared<shape>(create_tsteel(cpp_params))};
}

PRIMCAPICALL topo_shape_t *create_tsteel_with_place(tsteel_params_t params,
                                                    pnt3d_t position,
                                                    dir3d_t xDir,
                                                    dir3d_t zDir) {
  tsteel_params cpp_params{params.height,       params.width,
                           params.webThickness, params.flangeThickness,
                           params.radius,       params.length};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  gp_Dir cpp_zDir(zDir.x, zDir.y, zDir.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_tsteel(cpp_params, cpp_position, cpp_xDir, cpp_zDir))};
}

PRIMCAPICALL topo_shape_t *create_round_steel(round_steel_params_t params) {
  round_steel_params cpp_params{params.diameter, params.length};
  return new topo_shape_t{
      std::make_shared<shape>(create_round_steel(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_round_steel_with_place(round_steel_params_t params, pnt3d_t position,
                              dir3d_t xDir) {
  round_steel_params cpp_params{params.diameter, params.length};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_round_steel(cpp_params, cpp_position, cpp_xDir))};
}

PRIMCAPICALL topo_shape_t *
create_round_steel_tube(round_steel_tube_params_t params) {
  round_steel_tube_params cpp_params{params.outerDiameter, params.innerDiameter,
                                     params.length};
  return new topo_shape_t{
      std::make_shared<shape>(create_round_steel_tube(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_round_steel_tube_with_place(round_steel_tube_params_t params,
                                   pnt3d_t position, dir3d_t xDir) {
  round_steel_tube_params cpp_params{params.outerDiameter, params.innerDiameter,
                                     params.length};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_round_steel_tube(cpp_params, cpp_position, cpp_xDir))};
}

PRIMCAPICALL topo_shape_t *
create_rectangular_steel_tube(rectangular_steel_tube_params_t params) {
  rectangular_steel_tube_params cpp_params{params.height, params.width,
                                           params.thickness, params.length};
  return new topo_shape_t{
      std::make_shared<shape>(create_rectangular_steel_tube(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_rectangular_steel_tube_with_place(rectangular_steel_tube_params_t params,
                                         pnt3d_t position, dir3d_t xDir,
                                         dir3d_t zDir) {
  rectangular_steel_tube_params cpp_params{params.height, params.width,
                                           params.thickness, params.length};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  gp_Dir cpp_zDir(zDir.x, zDir.y, zDir.z);
  return new topo_shape_t{std::make_shared<shape>(create_rectangular_steel_tube(
      cpp_params, cpp_position, cpp_xDir, cpp_zDir))};
}

PRIMCAPICALL topo_shape_t *
create_square_steel_tube(square_steel_tube_params_t params) {
  square_steel_tube_params cpp_params{params.size, params.thickness,
                                      params.length};
  return new topo_shape_t{
      std::make_shared<shape>(create_square_steel_tube(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_square_steel_tube_with_place(square_steel_tube_params_t params,
                                    pnt3d_t position, dir3d_t xDir,
                                    dir3d_t zDir) {
  square_steel_tube_params cpp_params{params.size, params.thickness,
                                      params.length};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  gp_Dir cpp_zDir(zDir.x, zDir.y, zDir.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_square_steel_tube(cpp_params, cpp_position, cpp_xDir, cpp_zDir))};
}

PRIMCAPICALL topo_shape_t *
create_double_channel_steel(double_channel_steel_params_t params) {
  double_channel_steel_params cpp_params;
  cpp_params.height = params.base.height;
  cpp_params.flangeWidth = params.base.flangeWidth;
  cpp_params.webThickness = params.base.webThickness;
  cpp_params.flangeThickness = params.base.flangeThickness;
  cpp_params.radius = params.base.radius;
  cpp_params.length = params.base.length;
  cpp_params.spacing = params.spacing;
  return new topo_shape_t{
      std::make_shared<shape>(create_double_channel_steel(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_double_channel_steel_with_place(double_channel_steel_params_t params,
                                       pnt3d_t position, dir3d_t xDir,
                                       dir3d_t zDir) {
  double_channel_steel_params cpp_params;
  cpp_params.height = params.base.height;
  cpp_params.flangeWidth = params.base.flangeWidth;
  cpp_params.webThickness = params.base.webThickness;
  cpp_params.flangeThickness = params.base.flangeThickness;
  cpp_params.radius = params.base.radius;
  cpp_params.length = params.base.length;
  cpp_params.spacing = params.spacing;
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  gp_Dir cpp_zDir(zDir.x, zDir.y, zDir.z);
  return new topo_shape_t{std::make_shared<shape>(create_double_channel_steel(
      cpp_params, cpp_position, cpp_xDir, cpp_zDir))};
}

PRIMCAPICALL topo_shape_t *create_equilateral_double_angle_steel(
    equilateral_double_angle_steel_params_t params) {
  equilateral_double_angle_steel_params cpp_params;
  cpp_params.L = params.base.L;
  cpp_params.X = params.base.X;
  cpp_params.length = params.base.length;
  cpp_params.spacing = params.spacing;
  return new topo_shape_t{std::make_shared<shape>(
      create_equilateral_double_angle_steel(cpp_params))};
}

PRIMCAPICALL topo_shape_t *create_equilateral_double_angle_steel_with_place(
    equilateral_double_angle_steel_params_t params, pnt3d_t position,
    dir3d_t xDir, dir3d_t zDir) {
  equilateral_double_angle_steel_params cpp_params;
  cpp_params.L = params.base.L;
  cpp_params.X = params.base.X;
  cpp_params.length = params.base.length;
  cpp_params.spacing = params.spacing;
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  gp_Dir cpp_zDir(zDir.x, zDir.y, zDir.z);
  return new topo_shape_t{
      std::make_shared<shape>(create_equilateral_double_angle_steel(
          cpp_params, cpp_position, cpp_xDir, cpp_zDir))};
}

PRIMCAPICALL topo_shape_t *
create_unequal_angle_steel(unequal_angle_steel_params_t params) {
  unequal_angle_steel_params cpp_params;
  cpp_params.L1 = params.base.L1;
  cpp_params.L2 = params.base.L2;
  cpp_params.X = params.base.X;
  cpp_params.length = params.base.length;
  cpp_params.spacing = params.spacing;
  return new topo_shape_t{
      std::make_shared<shape>(create_unequal_angle_steel(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_unequal_angle_steel_with_place(unequal_angle_steel_params_t params,
                                      pnt3d_t position, dir3d_t xDir,
                                      dir3d_t zDir) {
  unequal_angle_steel_params cpp_params;
  cpp_params.L1 = params.base.L1;
  cpp_params.L2 = params.base.L2;
  cpp_params.X = params.base.X;
  cpp_params.length = params.base.length;
  cpp_params.spacing = params.spacing;
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  gp_Dir cpp_zDir(zDir.x, zDir.y, zDir.z);
  return new topo_shape_t{std::make_shared<shape>(create_unequal_angle_steel(
      cpp_params, cpp_position, cpp_xDir, cpp_zDir))};
}

PRIMCAPICALL topo_shape_t *create_polygon_tube(polygon_tube_params_t params) {
  polygon_tube_params cpp_params{params.side_length, params.thickness,
                                 params.length, params.sides};
  return new topo_shape_t{
      std::make_shared<shape>(create_polygon_tube(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_polygon_tube_with_place(polygon_tube_params_t params, pnt3d_t position,
                               dir3d_t xDir) {
  polygon_tube_params cpp_params{params.side_length, params.thickness,
                                 params.length, params.sides};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_polygon_tube(cpp_params, cpp_position, cpp_xDir))};
}

PRIMCAPICALL topo_shape_t *
create_bored_pile_foundation(bored_pile_params_t params) {
  bored_pile_params cpp_params{params.H1,          params.H2, params.H3,
                               params.H4,          params.d,  params.D,
                               params.filletRadius};
  return new topo_shape_t{
      std::make_shared<shape>(create_bored_pile_foundation(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_bored_pile_foundation_with_place(bored_pile_params_t params,
                                        pnt3d_t position, dir3d_t direction) {
  bored_pile_params cpp_params{params.H1,          params.H2, params.H3,
                               params.H4,          params.d,  params.D,
                               params.filletRadius};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_bored_pile_foundation(cpp_params, cpp_position, cpp_direction))};
}

PRIMCAPICALL topo_shape_t *
create_pile_cap_foundation(pile_cap_params_t params) {
  std::vector<gp_Pnt> points;
  for (int i = 0; i < params.ZCOUNT; i++) {
    points.push_back(gp_Pnt(params.ZPOSTARRAY[i].x, params.ZPOSTARRAY[i].y,
                            params.ZPOSTARRAY[i].z));
  }
  pile_cap_params cpp_params{
      params.H1, params.H2,          params.H3, params.H4, params.H5,
      params.H6, params.d,           params.D,  params.b,  params.B1,
      params.L1, params.e1,          params.e2, params.cs, params.ZCOUNT,
      points,    params.filletRadius};
  return new topo_shape_t{
      std::make_shared<shape>(create_pile_cap_foundation(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_pile_cap_foundation_with_place(pile_cap_params_t params,
                                      pnt3d_t position, dir3d_t direction) {
  std::vector<gp_Pnt> points;
  for (int i = 0; i < params.ZCOUNT; i++) {
    points.push_back(gp_Pnt(params.ZPOSTARRAY[i].x, params.ZPOSTARRAY[i].y,
                            params.ZPOSTARRAY[i].z));
  }
  pile_cap_params cpp_params{
      params.H1, params.H2,          params.H3, params.H4, params.H5,
      params.H6, params.d,           params.D,  params.b,  params.B1,
      params.L1, params.e1,          params.e2, params.cs, params.ZCOUNT,
      points,    params.filletRadius};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_pile_cap_foundation(cpp_params, cpp_position, cpp_direction))};
}

PRIMCAPICALL topo_shape_t *
create_rock_anchor_foundation(rock_anchor_params_t params) {
  std::vector<gp_Pnt> points;
  for (int i = 0; i < params.ZCOUNT; i++) {
    points.push_back(gp_Pnt(params.ZPOSTARRAY[i].x, params.ZPOSTARRAY[i].y,
                            params.ZPOSTARRAY[i].z));
  }
  rock_anchor_params cpp_params{params.H1, params.H2,     params.d, params.B1,
                                params.L1, params.ZCOUNT, points};
  return new topo_shape_t{
      std::make_shared<shape>(create_rock_anchor_foundation(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_rock_anchor_foundation_with_place(rock_anchor_params_t params,
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
  return new topo_shape_t{std::make_shared<shape>(
      create_rock_anchor_foundation(cpp_params, cpp_position, cpp_direction))};
}

PRIMCAPICALL topo_shape_t *
create_rock_pile_cap_foundation(rock_pile_cap_params_t params) {
  std::vector<gp_Pnt> points;
  for (int i = 0; i < params.ZCOUNT; i++) {
    points.push_back(gp_Pnt(params.ZPOSTARRAY[i].x, params.ZPOSTARRAY[i].y,
                            params.ZPOSTARRAY[i].z));
  }
  rock_pile_cap_params cpp_params{
      params.H1, params.H2, params.H3, params.d,  params.b,      params.B1,
      params.L1, params.e1, params.e2, params.cs, params.ZCOUNT, points};
  return new topo_shape_t{
      std::make_shared<shape>(create_rock_pile_cap_foundation(cpp_params))};
}

PRIMCAPICALL topo_shape_t *create_rock_pile_cap_foundation_with_place(
    rock_pile_cap_params_t params, pnt3d_t position, dir3d_t direction) {
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
  return new topo_shape_t{
      std::make_shared<shape>(create_rock_pile_cap_foundation(
          cpp_params, cpp_position, cpp_direction))};
}

PRIMCAPICALL topo_shape_t *
create_embedded_rock_anchor_foundation(embedded_rock_anchor_params_t params) {
  embedded_rock_anchor_params cpp_params{params.H1, params.H2, params.H3,
                                         params.d, params.D};
  return new topo_shape_t{std::make_shared<shape>(
      create_embedded_rock_anchor_foundation(cpp_params))};
}

PRIMCAPICALL topo_shape_t *create_embedded_rock_anchor_foundation_with_place(
    embedded_rock_anchor_params_t params, pnt3d_t position, dir3d_t direction) {
  embedded_rock_anchor_params cpp_params{params.H1, params.H2, params.H3,
                                         params.d, params.D};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  return new topo_shape_t{
      std::make_shared<shape>(create_embedded_rock_anchor_foundation(
          cpp_params, cpp_position, cpp_direction))};
}

PRIMCAPICALL topo_shape_t *
create_inclined_rock_anchor_foundation(inclined_rock_anchor_params_t params) {
  inclined_rock_anchor_params cpp_params{
      params.H1, params.H2, params.d,  params.D,      params.B,
      params.L,  params.e1, params.e2, params.alpha1, params.alpha2};
  return new topo_shape_t{std::make_shared<shape>(
      create_inclined_rock_anchor_foundation(cpp_params))};
}

PRIMCAPICALL topo_shape_t *create_inclined_rock_anchor_foundation_with_place(
    inclined_rock_anchor_params_t params, pnt3d_t position, dir3d_t direction) {
  inclined_rock_anchor_params cpp_params{
      params.H1, params.H2, params.d,  params.D,      params.B,
      params.L,  params.e1, params.e2, params.alpha1, params.alpha2};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  return new topo_shape_t{
      std::make_shared<shape>(create_inclined_rock_anchor_foundation(
          cpp_params, cpp_position, cpp_direction))};
}

PRIMCAPICALL topo_shape_t *
create_excavated_foundation(excavated_foundation_params_t params) {
  excavated_foundation_params cpp_params{params.H1,    params.H2, params.H3,
                                         params.d,     params.D,  params.alpha1,
                                         params.alpha2};
  return new topo_shape_t{
      std::make_shared<shape>(create_excavated_foundation(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_excavated_foundation_with_place(excavated_foundation_params_t params,
                                       pnt3d_t position, dir3d_t direction) {
  excavated_foundation_params cpp_params{params.H1,    params.H2, params.H3,
                                         params.d,     params.D,  params.alpha1,
                                         params.alpha2};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_excavated_foundation(cpp_params, cpp_position, cpp_direction))};
}

PRIMCAPICALL topo_shape_t *
create_step_foundation(step_foundation_params_t params) {
  step_foundation_params cpp_params{params.H,  params.H1, params.H2, params.H3,
                                    params.b,  params.B1, params.B2, params.B3,
                                    params.L1, params.L2, params.L3, params.N};
  return new topo_shape_t{
      std::make_shared<shape>(create_step_foundation(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_step_foundation_with_place(step_foundation_params_t params,
                                  pnt3d_t position, dir3d_t direction) {
  step_foundation_params cpp_params{params.H,  params.H1, params.H2, params.H3,
                                    params.b,  params.B1, params.B2, params.B3,
                                    params.L1, params.L2, params.L3, params.N};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_step_foundation(cpp_params, cpp_position, cpp_direction))};
}

PRIMCAPICALL topo_shape_t *
create_step_plate_foundation(step_plate_foundation_params_t params) {
  step_plate_foundation_params cpp_params{
      params.H,  params.H1, params.H2, params.H3,     params.b,      params.L1,
      params.L2, params.B1, params.B2, params.alpha1, params.alpha2, params.N};
  return new topo_shape_t{
      std::make_shared<shape>(create_step_plate_foundation(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_step_plate_foundation_with_place(step_plate_foundation_params_t params,
                                        pnt3d_t position, dir3d_t direction) {
  step_plate_foundation_params cpp_params{
      params.H,  params.H1, params.H2, params.H3,     params.b,      params.L1,
      params.L2, params.B1, params.B2, params.alpha1, params.alpha2, params.N};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_step_plate_foundation(cpp_params, cpp_position, cpp_direction))};
}

PRIMCAPICALL topo_shape_t *
create_sloped_base_foundation(sloped_base_foundation_params_t params) {
  sloped_base_foundation_params cpp_params{
      params.H1, params.H2, params.H3, params.b,      params.L1,
      params.L2, params.B1, params.B2, params.alpha1, params.alpha2};
  return new topo_shape_t{
      std::make_shared<shape>(create_sloped_base_foundation(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_sloped_base_foundation_with_place(sloped_base_foundation_params_t params,
                                         pnt3d_t position, dir3d_t direction) {
  sloped_base_foundation_params cpp_params{
      params.H1, params.H2, params.H3, params.b,      params.L1,
      params.L2, params.B1, params.B2, params.alpha1, params.alpha2};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_sloped_base_foundation(cpp_params, cpp_position, cpp_direction))};
}

PRIMCAPICALL topo_shape_t *create_composite_caisson_foundation(
    composite_caisson_foundation_params_t params) {
  composite_caisson_foundation_params cpp_params{
      params.H1, params.H2, params.H3, params.H4, params.b, params.D,
      params.t,  params.B1, params.B2, params.L1, params.L2};
  return new topo_shape_t{
      std::make_shared<shape>(create_composite_caisson_foundation(cpp_params))};
}

PRIMCAPICALL topo_shape_t *create_composite_caisson_foundation_with_place(
    composite_caisson_foundation_params_t params, pnt3d_t position,
    dir3d_t direction) {
  composite_caisson_foundation_params cpp_params{
      params.H1, params.H2, params.H3, params.H4, params.b, params.D,
      params.t,  params.B1, params.B2, params.L1, params.L2};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  return new topo_shape_t{
      std::make_shared<shape>(create_composite_caisson_foundation(
          cpp_params, cpp_position, cpp_direction))};
}

PRIMCAPICALL topo_shape_t *
create_raft_foundation(raft_foundation_params_t params) {
  raft_foundation_params cpp_params{params.H1, params.H2, params.H3,
                                    params.b1, params.b2, params.B1,
                                    params.B2, params.L1, params.L2};
  return new topo_shape_t{
      std::make_shared<shape>(create_raft_foundation(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_raft_foundation_with_place(raft_foundation_params_t params,
                                  pnt3d_t position, dir3d_t direction) {
  raft_foundation_params cpp_params{params.H1, params.H2, params.H3,
                                    params.b1, params.b2, params.B1,
                                    params.B2, params.L1, params.L2};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_raft_foundation(cpp_params, cpp_position, cpp_direction))};
}

PRIMCAPICALL topo_shape_t *
create_direct_buried_foundation(direct_buried_foundation_params_t params) {
  direct_buried_foundation_params cpp_params{params.H1,
                                             params.H2,
                                             params.d,
                                             params.D,
                                             params.B,
                                             params.t,
                                             params.hasBasePlate,
                                             params.isCircularPlate};
  return new topo_shape_t{
      std::make_shared<shape>(create_direct_buried_foundation(cpp_params))};
}

PRIMCAPICALL topo_shape_t *create_direct_buried_foundation_with_place(
    direct_buried_foundation_params_t params, pnt3d_t position,
    dir3d_t direction) {
  direct_buried_foundation_params cpp_params{params.H1,
                                             params.H2,
                                             params.d,
                                             params.D,
                                             params.B,
                                             params.t,
                                             params.hasBasePlate,
                                             params.isCircularPlate};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  return new topo_shape_t{
      std::make_shared<shape>(create_direct_buried_foundation(
          cpp_params, cpp_position, cpp_direction))};
}

PRIMCAPICALL topo_shape_t *
create_steel_sleeve_foundation(steel_sleeve_foundation_params_t params) {
  steel_sleeve_foundation_params cpp_params{
      params.H1, params.H2, params.H3, params.H4, params.d,
      params.D1, params.D2, params.t,  params.B1, params.B2};
  return new topo_shape_t{
      std::make_shared<shape>(create_steel_sleeve_foundation(cpp_params))};
}

PRIMCAPICALL topo_shape_t *create_steel_sleeve_foundation_with_place(
    steel_sleeve_foundation_params_t params, pnt3d_t position,
    dir3d_t direction) {
  steel_sleeve_foundation_params cpp_params{
      params.H1, params.H2, params.H3, params.H4, params.d,
      params.D1, params.D2, params.t,  params.B1, params.B2};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_steel_sleeve_foundation(cpp_params, cpp_position, cpp_direction))};
}

PRIMCAPICALL topo_shape_t *
create_precast_column_foundation(precast_column_foundation_params_t params) {
  precast_column_foundation_params cpp_params{params.H1, params.H2, params.H3,
                                              params.d,  params.B1, params.B2,
                                              params.L1, params.L2};
  return new topo_shape_t{
      std::make_shared<shape>(create_precast_column_foundation(cpp_params))};
}

PRIMCAPICALL topo_shape_t *create_precast_column_foundation_with_place(
    precast_column_foundation_params_t params, pnt3d_t position,
    dir3d_t direction) {
  precast_column_foundation_params cpp_params{params.H1, params.H2, params.H3,
                                              params.d,  params.B1, params.B2,
                                              params.L1, params.L2};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  return new topo_shape_t{
      std::make_shared<shape>(create_precast_column_foundation(
          cpp_params, cpp_position, cpp_direction))};
}

PRIMCAPICALL topo_shape_t *
create_precast_pinned_foundation(precast_pinned_foundation_params_t params) {
  precast_pinned_foundation_params cpp_params{
      params.H1, params.H2, params.H3, params.d, params.B1, params.B2,
      params.L1, params.L2, params.B,  params.H, params.L};
  return new topo_shape_t{
      std::make_shared<shape>(create_precast_pinned_foundation(cpp_params))};
}

PRIMCAPICALL topo_shape_t *create_precast_pinned_foundation_with_place(
    precast_pinned_foundation_params_t params, pnt3d_t position,
    dir3d_t direction) {
  precast_pinned_foundation_params cpp_params{
      params.H1, params.H2, params.H3, params.d, params.B1, params.B2,
      params.L1, params.L2, params.B,  params.H, params.L};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  return new topo_shape_t{
      std::make_shared<shape>(create_precast_pinned_foundation(
          cpp_params, cpp_position, cpp_direction))};
}

PRIMCAPICALL topo_shape_t *create_precast_metal_support_foundation(
    precast_metal_support_foundation_params_t params) {
  precast_metal_support_foundation_params cpp_params{
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
  return new topo_shape_t{std::make_shared<shape>(
      create_precast_metal_support_foundation(cpp_params))};
}

PRIMCAPICALL topo_shape_t *create_precast_metal_support_foundation_with_place(
    precast_metal_support_foundation_params_t params, pnt3d_t position,
    dir3d_t direction) {
  precast_metal_support_foundation_params cpp_params{
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
  return new topo_shape_t{
      std::make_shared<shape>(create_precast_metal_support_foundation(
          cpp_params, cpp_position, cpp_direction))};
}

PRIMCAPICALL topo_shape_t *create_precast_concrete_support_foundation(
    precast_concrete_support_foundation_params_t params) {
  precast_concrete_support_foundation_params cpp_params{
      params.H1, params.H2, params.H3, params.H4, params.H5,
      params.b1, params.b2, params.b3, params.B1, params.B2,
      params.L1, params.L2, params.S1, params.n1};
  return new topo_shape_t{std::make_shared<shape>(
      create_precast_concrete_support_foundation(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_precast_concrete_support_foundation_with_place(
    precast_concrete_support_foundation_params_t params, pnt3d_t position,
    dir3d_t direction) {
  precast_concrete_support_foundation_params cpp_params{
      params.H1, params.H2, params.H3, params.H4, params.H5,
      params.b1, params.b2, params.b3, params.B1, params.B2,
      params.L1, params.L2, params.S1, params.n1};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_direction(direction.x, direction.y, direction.z);
  return new topo_shape_t{
      std::make_shared<shape>(create_precast_concrete_support_foundation(
          cpp_params, cpp_position, cpp_direction))};
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
  return new topo_shape_t{std::make_shared<shape>(
      create_transmission_line(cpp_params, cpp_start, cpp_end))};
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

  return new topo_shape_t{
      std::make_shared<shape>(create_insulator_string(cpp_params))};
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

  return new topo_shape_t{std::make_shared<shape>(
      create_insulator_string(cpp_params, cpp_position, cpp_direction))};
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
  return new topo_shape_t{
      std::make_shared<shape>(create_single_hook_anchor(cpp_params))};
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
  return new topo_shape_t{std::make_shared<shape>(create_single_hook_anchor(
      cpp_params, cpp_position, cpp_normal, cpp_xDir))};
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
  return new topo_shape_t{
      std::make_shared<shape>(create_triple_hook_anchor(cpp_params))};
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
  return new topo_shape_t{std::make_shared<shape>(create_triple_hook_anchor(
      cpp_params, cpp_position, cpp_normal, cpp_xDir))};
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
  return new topo_shape_t{
      std::make_shared<shape>(create_ribbed_anchor(cpp_params))};
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
  return new topo_shape_t{std::make_shared<shape>(
      create_ribbed_anchor(cpp_params, cpp_position, cpp_normal, cpp_xDir))};
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
  return new topo_shape_t{
      std::make_shared<shape>(create_nut_anchor(cpp_params))};
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
  return new topo_shape_t{std::make_shared<shape>(
      create_nut_anchor(cpp_params, cpp_position, cpp_normal, cpp_xDir))};
}

PRIMCAPICALL topo_shape_t *
create_triple_arm_anchor(triple_arm_anchor_params_t params) {
  triple_arm_anchor_params cpp_params{
      params.boltDiameter,  params.exposedLength, params.nutCount,
      params.nutHeight,     params.nutOD,         params.washerCount,
      params.washerShape,   params.washerSize,    params.washerThickness,
      params.anchorLength,  params.armDiameter,   params.armStraightLength,
      params.armBendLength, params.armBendAngle};
  return new topo_shape_t{
      std::make_shared<shape>(create_triple_arm_anchor(cpp_params))};
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
  return new topo_shape_t{std::make_shared<shape>(create_triple_arm_anchor(
      cpp_params, cpp_position, cpp_normal, cpp_xDir))};
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
  return new topo_shape_t{
      std::make_shared<shape>(create_positioning_plate_anchor(cpp_params))};
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
  return new topo_shape_t{
      std::make_shared<shape>(create_positioning_plate_anchor(
          cpp_params, cpp_position, cpp_normal, cpp_xDir))};
}

PRIMCAPICALL topo_shape_t *create_stub_angle(stub_angle_params_t params) {
  stub_angle_params cpp_params{params.legWidth, params.thickness, params.slope,
                               params.exposedLength, params.anchorLength};
  return new topo_shape_t{
      std::make_shared<shape>(create_stub_angle(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_stub_angle_with_place(stub_angle_params_t params, pnt3d_t position,
                             dir3d_t normal, dir3d_t xDir) {
  stub_angle_params cpp_params{params.legWidth, params.thickness, params.slope,
                               params.exposedLength, params.anchorLength};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_stub_angle(cpp_params, cpp_position, cpp_normal, cpp_xDir))};
}

PRIMCAPICALL topo_shape_t *create_stub_tube(stub_tube_params_t params) {
  stub_tube_params cpp_params{params.diameter, params.thickness, params.slope,
                              params.exposedLength, params.anchorLength};
  return new topo_shape_t{
      std::make_shared<shape>(create_stub_tube(cpp_params))};
}

PRIMCAPICALL topo_shape_t *
create_stub_tube_with_place(stub_tube_params_t params, pnt3d_t position,
                            dir3d_t normal, dir3d_t xDir) {
  stub_tube_params cpp_params{params.diameter, params.thickness, params.slope,
                              params.exposedLength, params.anchorLength};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  return new topo_shape_t{std::make_shared<shape>(
      create_stub_tube(cpp_params, cpp_position, cpp_normal, cpp_xDir))};
}

#ifdef __cplusplus
}
#endif
