#ifndef GO_PRMITIVES_C_API_H
#define GO_PRMITIVES_C_API_H

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define PRIMCAPICALL __declspec(dllexport)
#else
#define PRIMCAPICALL
#endif

#include "standard_c_api.h"
#include "topo_c_api.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  double radius;
} sphere_params_t;

PRIMCAPICALL topo_shape_t *create_sphere(sphere_params_t params);
PRIMCAPICALL topo_shape_t *create_sphere_with_place(sphere_params_t params,
                                                    pnt3d_t center);

typedef struct {
  double polarRadius;
  double equatorialRadius;
  double height;
} rotational_ellipsoid_params_t;

PRIMCAPICALL topo_shape_t *
create_rotational_ellipsoid(rotational_ellipsoid_params_t params);
PRIMCAPICALL topo_shape_t *
create_rotational_ellipsoid_with_place(rotational_ellipsoid_params_t params,
                                       pnt3d_t center, dir3d_t xDir);

typedef struct {
  double length;
  double width;
  double height;
} cuboid_params_t;

PRIMCAPICALL topo_shape_t *create_cuboid(cuboid_params_t params);
PRIMCAPICALL topo_shape_t *create_cuboid_with_place(cuboid_params_t params,
                                                    pnt3d_t center,
                                                    dir3d_t xDir, dir3d_t zDir);

typedef struct {
  double topDiag1;
  double topDiag2;
  double bottomDiag1;
  double bottomDiag2;
  double height;
} diamond_frustum_t;

PRIMCAPICALL topo_shape_t *create_diamond_frustum(diamond_frustum_t params);
PRIMCAPICALL topo_shape_t *
create_diamond_frustum_with_place(diamond_frustum_t params, pnt3d_t position,
                                  dir3d_t normal, dir3d_t xDir);

typedef struct {
  double topLength;
  double topWidth;
  double bottomLength;
  double bottomWidth;
  double height;
  double xOffset;
  double yOffset;
} offset_rectangular_table_params_t;

PRIMCAPICALL topo_shape_t *
create_offset_rectangular_table(offset_rectangular_table_params_t params);
PRIMCAPICALL topo_shape_t *create_offset_rectangular_table_with_place(
    offset_rectangular_table_params_t params, pnt3d_t position, dir3d_t normal,
    dir3d_t xDir);

typedef struct {
  double radius;
  double height;
} cylinder_params_t;

PRIMCAPICALL topo_shape_t *create_cylinder(cylinder_params_t params);
PRIMCAPICALL topo_shape_t *create_cylinder_with_place(cylinder_params_t params,
                                                      pnt3d_t baseCenter,
                                                      dir3d_t axisDir);

typedef struct {
  double radius;
  double length;
  double bendAngle;
} sharp_bent_cylinder_params_t;

PRIMCAPICALL topo_shape_t *
create_sharp_bent_cylinder(sharp_bent_cylinder_params_t params);
PRIMCAPICALL topo_shape_t *
create_sharp_bent_cylinder_with_place(sharp_bent_cylinder_params_t params,
                                      pnt3d_t bendPoint, dir3d_t initialDir,
                                      dir3d_t bendPlaneNormal);

typedef struct {
  double topRadius;
  double bottomRadius;
  double height;
} truncated_cone_params_t;

PRIMCAPICALL topo_shape_t *
create_truncated_cone(truncated_cone_params_t params);
PRIMCAPICALL topo_shape_t *
create_truncated_cone_with_place(truncated_cone_params_t params,
                                 pnt3d_t baseCenter, dir3d_t axisDir);

typedef struct {
  double topRadius;
  double bottomRadius;
  double height;
  double topXOffset;
  double topYOffset;
} eccentric_truncated_cone_params_t;

PRIMCAPICALL topo_shape_t *
create_eccentric_truncated_cone(eccentric_truncated_cone_params_t params);
PRIMCAPICALL topo_shape_t *create_eccentric_truncated_cone_with_place(
    eccentric_truncated_cone_params_t params, pnt3d_t baseCenter,
    dir3d_t axisDir);

typedef struct {
  double ringRadius;
  double tubeRadius;
  double angle;
} ring_params_t;

PRIMCAPICALL topo_shape_t *create_ring(ring_params_t params);
PRIMCAPICALL topo_shape_t *create_ring_with_place(ring_params_t params,
                                                  pnt3d_t center,
                                                  dir3d_t normal, dir3d_t xDir);

typedef struct {
  double tubeRadius;
  double filletRadius;
  double length;
  double width;
} rectangular_ring_params_t;

PRIMCAPICALL topo_shape_t *
create_rectangular_ring(rectangular_ring_params_t params);
PRIMCAPICALL topo_shape_t *
create_rectangular_ring_with_place(rectangular_ring_params_t params,
                                   pnt3d_t center, dir3d_t normal,
                                   dir3d_t xDir);

typedef struct {
  double tubeRadius;
  double majorRadius;
  double minorRadius;
} elliptic_ring_params_t;

PRIMCAPICALL topo_shape_t *create_elliptic_ring(elliptic_ring_params_t params);
PRIMCAPICALL topo_shape_t *
create_elliptic_ring_with_place(elliptic_ring_params_t params, pnt3d_t center,
                                dir3d_t normal, dir3d_t xDir);

typedef struct {
  double outerRadius;
  double innerRadius;
  double height;
  double angle;
} circular_gasket_params_t;

PRIMCAPICALL topo_shape_t *
create_circular_gasket(circular_gasket_params_t params);
PRIMCAPICALL topo_shape_t *
create_circular_gasket_with_place(circular_gasket_params_t params,
                                  pnt3d_t center, dir3d_t normal, dir3d_t xDir);

typedef struct {
  double topRadius;
  double outerRadius;
  double innerRadius;
  double height;
  double angle;
} table_gasket_params_t;

PRIMCAPICALL topo_shape_t *create_table_gasket(table_gasket_params_t params);
PRIMCAPICALL topo_shape_t *
create_table_gasket_with_place(table_gasket_params_t params, pnt3d_t center,
                               dir3d_t normal, dir3d_t xDir);

typedef struct {
  double outerLength;
  double outerWidth;
  double innerLength;
  double innerWidth;
  double height;
  int cornerType;
  double cornerParam;
} square_gasket_params_t;

PRIMCAPICALL topo_shape_t *create_square_gasket(square_gasket_params_t params);
PRIMCAPICALL topo_shape_t *
create_square_gasket_with_place(square_gasket_params_t params, pnt3d_t center,
                                dir3d_t normal, dir3d_t xDir);

typedef struct {
  pnt3d_t *points;
  int numPoints;
  dir3d_t normal;
  double length;
} stretched_body_params_t;

PRIMCAPICALL topo_shape_t *
create_stretched_body(stretched_body_params_t params);
PRIMCAPICALL topo_shape_t *
create_stretched_body_with_place(stretched_body_params_t params,
                                 pnt3d_t basePoint, dir3d_t xDir);

typedef struct {
  double height;
  double radius;
  double bigSkirtRadius;
  double smallSkirtRadius;
  int count;
} porcelain_bushing_params_t;

PRIMCAPICALL topo_shape_t *
create_porcelain_bushing(porcelain_bushing_params_t params);
PRIMCAPICALL topo_shape_t *
create_porcelain_bushing_with_place(porcelain_bushing_params_t params,
                                    pnt3d_t basePoint, dir3d_t axisDir);

typedef struct {
  double height;
  double bottomRadius;
  double topRadius;
  double bottomSkirtRadius1;
  double bottomSkirtRadius2;
  double topSkirtRadius1;
  double topSkirtRadius2;
  int count;
} cone_porcelain_bushing_params_t;

PRIMCAPICALL topo_shape_t *
create_cone_porcelain_bushing(cone_porcelain_bushing_params_t params);
PRIMCAPICALL topo_shape_t *
create_cone_porcelain_bushing_with_place(cone_porcelain_bushing_params_t params,
                                         pnt3d_t basePoint, dir3d_t axisDir);

typedef struct {
  int count;
  double spacing;
  int insulatorCount;
  double height;
  double bigSkirtRadius;
  double smallSkirtRadius;
  double radius;
  double frontLength;
  double backLength;
  int splitCount;
} insulator_string_params_t;

PRIMCAPICALL topo_shape_t *
create_insulator_string(insulator_string_params_t params);
PRIMCAPICALL topo_shape_t *
create_insulator_string_with_place(insulator_string_params_t params,
                                   pnt3d_t position, dir3d_t direction,
                                   dir3d_t upDirection);

typedef struct {
  double frontSpacing;
  double backSpacing;
  int insulatorCount;
  double height;
  double radius;
  double bigSkirtRadius;
  double smallSkirtRadius;
  double frontLength;
  double backLength;
  int splitCount;
} vtype_insulator_params_t;

PRIMCAPICALL topo_shape_t *
create_vtype_insulator(vtype_insulator_params_t params);
PRIMCAPICALL topo_shape_t *
create_vtype_insulator_with_place(vtype_insulator_params_t params,
                                  pnt3d_t position, dir3d_t direction,
                                  dir3d_t upDirection);

typedef struct {
  double length;
  double width;
  double thickness;
  double chamferLength;
  double columnSpacing;
  double rowSpacing;
  double holeRadius;
  int columnCount;
  int rowCount;
  double bottomOffset;
  char phase;
} terminal_block_params_t;

PRIMCAPICALL topo_shape_t *
create_terminal_block(terminal_block_params_t params);
PRIMCAPICALL topo_shape_t *
create_terminal_block_with_place(terminal_block_params_t params,
                                 pnt3d_t position, dir3d_t lengthDir,
                                 dir3d_t widthDir);

typedef struct {
  double length;
  double width;
  double thickness;
  double columnSpacing;
  double rowSpacing;
  int columnCount;
  int rowCount;
  bool hasMiddleHole;
  double holeDiameter;
} rectangular_hole_plate_params_t;

PRIMCAPICALL topo_shape_t *
create_rectangular_fixed_plate(rectangular_hole_plate_params_t params);
PRIMCAPICALL topo_shape_t *create_rectangular_fixed_plate_with_place(
    rectangular_hole_plate_params_t params, pnt3d_t position, dir3d_t lengthDir,
    dir3d_t widthDir);

typedef struct {
  double length;
  double width;
  double thickness;
  double ringRadius;
  int holeCount;
  bool hasMiddleHole;
  double holeDiameter;
} circular_fixed_plate_params_t;

PRIMCAPICALL topo_shape_t *
create_circular_fixed_plate(circular_fixed_plate_params_t params);
PRIMCAPICALL topo_shape_t *
create_circular_fixed_plate_with_place(circular_fixed_plate_params_t params,
                                       pnt3d_t position, dir3d_t lengthDir,
                                       dir3d_t widthDir);

typedef struct {
  pnt3d_t startPoint;
  pnt3d_t endPoint;
  dir3d_t startDir;
  dir3d_t endDir;
  double sag;
  double diameter;
  pnt3d_t *fitPoints;
  int numFitPoints;
} wire_params_t;

PRIMCAPICALL topo_shape_t *create_wire(wire_params_t params);
PRIMCAPICALL topo_shape_t *create_wire_with_place(wire_params_t params,
                                                  pnt3d_t position,
                                                  dir3d_t direction,
                                                  dir3d_t upDirection);

typedef struct {
  pnt3d_t startPoint;
  pnt3d_t endPoint;
  pnt3d_t *inflectionPoints;
  int numInflectionPoints;
  double *radii;
  int numRadii;
  double diameter;
} cable_params_t;

PRIMCAPICALL topo_shape_t *create_cable(cable_params_t params);
PRIMCAPICALL topo_shape_t *create_cable_with_place(cable_params_t params,
                                                   pnt3d_t position,
                                                   dir3d_t direction,
                                                   dir3d_t upDirection);

typedef struct {
  double L;
  double X;
  double length;
} equilateral_angle_steel_params_t;
PRIMCAPICALL topo_shape_t *
create_equilateral_angle_steel(equilateral_angle_steel_params_t params);
PRIMCAPICALL topo_shape_t *create_equilateral_angle_steel_with_place(
    equilateral_angle_steel_params_t params, pnt3d_t position, dir3d_t xDir,
    dir3d_t yDir);

typedef struct {
  double L1;
  double L2;
  double X;
  double length;
} scalene_angle_steel_params_t;

PRIMCAPICALL topo_shape_t *
create_scalene_angle_steel(scalene_angle_steel_params_t params);
PRIMCAPICALL topo_shape_t *
create_scalene_angle_steel_with_place(scalene_angle_steel_params_t params,
                                      pnt3d_t position, dir3d_t xDir,
                                      dir3d_t longEdgeDir);

typedef struct {
  double height;
  double flangeWidth;
  double webThickness;
  double flangeThickness;
  double radius;
  double length;
} ibeam_params_t;

PRIMCAPICALL topo_shape_t *create_ibeam(ibeam_params_t params);
PRIMCAPICALL topo_shape_t *create_ibeam_with_place(ibeam_params_t params,
                                                   pnt3d_t position,
                                                   dir3d_t xDir, dir3d_t zDir);

typedef struct {
  double height;
  double flangeWidth;
  double webThickness;
  double flangeThickness;
  double radius;
  double length;
  double flangeSlope;
} light_ibeam_params_t;

PRIMCAPICALL topo_shape_t *create_light_ibeam(light_ibeam_params_t params);
PRIMCAPICALL topo_shape_t *
create_light_ibeam_with_place(light_ibeam_params_t params, pnt3d_t position,
                              dir3d_t xDir, dir3d_t zDir);

typedef struct {
  double height;
  double flangeWidth;
  double webThickness;
  double flangeThickness;
  double radius;
  double length;
} hbeam_params_t;

PRIMCAPICALL topo_shape_t *create_hbeam(hbeam_params_t params);
PRIMCAPICALL topo_shape_t *create_hbeam_with_place(hbeam_params_t params,
                                                   pnt3d_t position,
                                                   dir3d_t xDir, dir3d_t zDir);

typedef struct {
  double height;
  double flangeWidth;
  double webThickness;
  double flangeThickness;
  double radius;
  double length;
} beam_channel_params_t;

PRIMCAPICALL topo_shape_t *create_beam_channel(beam_channel_params_t params);
PRIMCAPICALL topo_shape_t *
create_beam_channel_with_place(beam_channel_params_t params, pnt3d_t position,
                               dir3d_t xDir, dir3d_t zDir);

typedef struct {
  double height;
  double flangeWidth;
  double webThickness;
  double flangeThickness;
  double radius;
  double length;
  double flangeSlope;
} light_beam_channel_params_t;

PRIMCAPICALL topo_shape_t *
create_light_beam_channel(light_beam_channel_params_t params);
PRIMCAPICALL topo_shape_t *
create_light_beam_channel_with_place(light_beam_channel_params_t params,
                                     pnt3d_t position, dir3d_t xDir,
                                     dir3d_t zDir);

typedef struct {
  double width;
  double thickness;
  double length;
} flat_steel_params_t;

PRIMCAPICALL topo_shape_t *create_flat_steel(flat_steel_params_t params);
PRIMCAPICALL topo_shape_t *
create_flat_steel_with_place(flat_steel_params_t params, pnt3d_t position,
                             dir3d_t xDir, dir3d_t zDir);

typedef struct {
  double height;
  double width;
  double thickness;
  double radius;
  double length;
} lsteel_params_t;

PRIMCAPICALL topo_shape_t *create_lsteel(lsteel_params_t params);
PRIMCAPICALL topo_shape_t *create_lsteel_with_place(lsteel_params_t params,
                                                    pnt3d_t position,
                                                    dir3d_t xDir, dir3d_t zDir);

typedef struct {
  double height;
  double width;
  double webThickness;
  double flangeThickness;
  double radius;
  double length;
} tsteel_params_t;

PRIMCAPICALL topo_shape_t *create_tsteel(tsteel_params_t params);
PRIMCAPICALL topo_shape_t *create_tsteel_with_place(tsteel_params_t params,
                                                    pnt3d_t position,
                                                    dir3d_t xDir, dir3d_t zDir);

typedef struct {
  double diameter;
  double length;
} round_steel_params_t;

PRIMCAPICALL topo_shape_t *create_round_steel(round_steel_params_t params);
PRIMCAPICALL topo_shape_t *
create_round_steel_with_place(round_steel_params_t params, pnt3d_t position,
                              dir3d_t xDir);

typedef struct {
  double outerDiameter;
  double innerDiameter;
  double length;
} round_steel_tube_params_t;

PRIMCAPICALL topo_shape_t *
create_round_steel_tube(round_steel_tube_params_t params);
PRIMCAPICALL topo_shape_t *
create_round_steel_tube_with_place(round_steel_tube_params_t params,
                                   pnt3d_t position, dir3d_t xDir);

typedef struct {
  double height;
  double width;
  double thickness;
  double length;
} rectangular_steel_tube_params_t;

PRIMCAPICALL topo_shape_t *
create_rectangular_steel_tube(rectangular_steel_tube_params_t params);
PRIMCAPICALL topo_shape_t *
create_rectangular_steel_tube_with_place(rectangular_steel_tube_params_t params,
                                         pnt3d_t position, dir3d_t xDir,
                                         dir3d_t zDir);

typedef struct {
  double size;
  double thickness;
  double length;
} square_steel_tube_params_t;

PRIMCAPICALL topo_shape_t *
create_square_steel_tube(square_steel_tube_params_t params);
PRIMCAPICALL topo_shape_t *
create_square_steel_tube_with_place(square_steel_tube_params_t params,
                                    pnt3d_t position, dir3d_t xDir,
                                    dir3d_t zDir);

typedef struct {
  beam_channel_params_t base;
  double spacing;
} double_channel_steel_params_t;

PRIMCAPICALL topo_shape_t *
create_double_channel_steel(double_channel_steel_params_t params);
PRIMCAPICALL topo_shape_t *
create_double_channel_steel_with_place(double_channel_steel_params_t params,
                                       pnt3d_t position, dir3d_t xDir,
                                       dir3d_t zDir);

typedef struct {
  equilateral_angle_steel_params_t base;
  double spacing;
} equilateral_double_angle_steel_params_t;

PRIMCAPICALL topo_shape_t *create_equilateral_double_angle_steel(
    equilateral_double_angle_steel_params_t params);
PRIMCAPICALL topo_shape_t *create_equilateral_double_angle_steel_with_place(
    equilateral_double_angle_steel_params_t params, pnt3d_t position,
    dir3d_t xDir, dir3d_t zDir);

typedef struct {
  scalene_angle_steel_params_t base;
  double spacing;
} unequal_angle_steel_params_t;

PRIMCAPICALL topo_shape_t *
create_unequal_angle_steel(unequal_angle_steel_params_t params);
PRIMCAPICALL topo_shape_t *
create_unequal_angle_steel_with_place(unequal_angle_steel_params_t params,
                                      pnt3d_t position, dir3d_t xDir,
                                      dir3d_t zDir);

typedef struct {
  double side_length;
  double thickness;
  double length;
  int sides;
} polygon_tube_params_t;

PRIMCAPICALL topo_shape_t *create_polygon_tube(polygon_tube_params_t params);
PRIMCAPICALL topo_shape_t *
create_polygon_tube_with_place(polygon_tube_params_t params, pnt3d_t position,
                               dir3d_t xDir);

typedef struct {
  double H1;
  double H2;
  double H3;
  double H4;
  double d;
  double D;
  double filletRadius;
} bored_pile_params_t;

PRIMCAPICALL topo_shape_t *
create_bored_pile_foundation(bored_pile_params_t params);
PRIMCAPICALL topo_shape_t *
create_bored_pile_foundation_with_place(bored_pile_params_t params,
                                        pnt3d_t position, dir3d_t direction);

typedef struct {
  double H1;
  double H2;
  double H3;

  double d;
  double b;
  double B1;
  double L1;

  double e1;
  double e2;

  int cs;

  int ZCOUNT;
  pnt3d_t *ZPOSTARRAY;
} rock_pile_cap_params_t;

PRIMCAPICALL topo_shape_t *
create_rock_pile_cap_foundation(rock_pile_cap_params_t params);
PRIMCAPICALL topo_shape_t *
create_rock_pile_cap_foundation_with_place(rock_pile_cap_params_t params,
                                           pnt3d_t position, dir3d_t direction);

typedef struct {
  double H1;
  double H2;
  double H3;
  double H4;
  double H5;
  double H6;
  double d;
  double D;
  double b;
  double B1;
  double L1;
  double e1;
  double e2;
  int cs;
  int ZCOUNT;
  pnt3d_t *ZPOSTARRAY;
  double filletRadius;
} pile_cap_params_t;

PRIMCAPICALL topo_shape_t *create_pile_cap_foundation(pile_cap_params_t params);
PRIMCAPICALL topo_shape_t *
create_pile_cap_foundation_with_place(pile_cap_params_t params,
                                      pnt3d_t position, dir3d_t direction);

typedef struct {
  double H1;
  double H2;
  double d;
  double B1;
  double L1;
  int ZCOUNT;
  pnt3d_t *ZPOSTARRAY;
} rock_anchor_params_t;

PRIMCAPICALL topo_shape_t *
create_rock_anchor_foundation(rock_anchor_params_t params);
PRIMCAPICALL topo_shape_t *
create_rock_anchor_foundation_with_place(rock_anchor_params_t params,
                                         pnt3d_t position, dir3d_t direction);

typedef struct {
  double H1;
  double H2;
  double H3;
  double d;
  double D;
} embedded_rock_anchor_params_t;

PRIMCAPICALL topo_shape_t *
create_embedded_rock_anchor_foundation(embedded_rock_anchor_params_t params);
PRIMCAPICALL topo_shape_t *create_embedded_rock_anchor_foundation_with_place(
    embedded_rock_anchor_params_t params, pnt3d_t position, dir3d_t direction);

typedef struct {
  double H1;
  double H2;
  double d;
  double D;
  double B;
  double L;
  double e1;
  double e2;
  double alpha1;
  double alpha2;
} inclined_rock_anchor_params_t;

PRIMCAPICALL topo_shape_t *
create_inclined_rock_anchor_foundation(inclined_rock_anchor_params_t params);
PRIMCAPICALL topo_shape_t *create_inclined_rock_anchor_foundation_with_place(
    inclined_rock_anchor_params_t params, pnt3d_t position, dir3d_t direction);

typedef struct {
  double H1;
  double H2;
  double H3;
  double d;
  double D;
  double alpha1;
  double alpha2;
} excavated_foundation_params_t;

PRIMCAPICALL topo_shape_t *
create_excavated_foundation(excavated_foundation_params_t params);
PRIMCAPICALL topo_shape_t *
create_excavated_foundation_with_place(excavated_foundation_params_t params,
                                       pnt3d_t position, dir3d_t direction);

typedef struct {
  double H;
  double H1;
  double H2;
  double H3;
  double b;
  double B1;
  double B2;
  double B3;
  double L1;
  double L2;
  double L3;
  int N;
} step_foundation_params_t;

PRIMCAPICALL topo_shape_t *
create_step_foundation(step_foundation_params_t params);
PRIMCAPICALL topo_shape_t *
create_step_foundation_with_place(step_foundation_params_t params,
                                  pnt3d_t position, dir3d_t direction);

typedef struct {
  double H;
  double H1;
  double H2;
  double H3;
  double b;
  double L1;
  double L2;
  double B1;
  double B2;
  double alpha1;
  double alpha2;
  int N;
} step_plate_foundation_params_t;

PRIMCAPICALL topo_shape_t *
create_step_plate_foundation(step_plate_foundation_params_t params);
PRIMCAPICALL topo_shape_t *
create_step_plate_foundation_with_place(step_plate_foundation_params_t params,
                                        pnt3d_t position, dir3d_t direction);

typedef struct {
  double H1;
  double H2;
  double H3;
  double b;
  double L1;
  double L2;
  double B1;
  double B2;
  double alpha1;
  double alpha2;
} sloped_base_foundation_params_t;

PRIMCAPICALL topo_shape_t *
create_sloped_base_foundation(sloped_base_foundation_params_t params);
PRIMCAPICALL topo_shape_t *
create_sloped_base_foundation_with_place(sloped_base_foundation_params_t params,
                                         pnt3d_t position, dir3d_t direction);

typedef struct {
  double H1;
  double H2;
  double H3;
  double H4;
  double b;
  double D;
  double t;
  double B1;
  double B2;
  double L1;
  double L2;
} composite_caisson_foundation_params_t;

PRIMCAPICALL topo_shape_t *create_composite_caisson_foundation(
    composite_caisson_foundation_params_t params);
PRIMCAPICALL topo_shape_t *create_composite_caisson_foundation_with_place(
    composite_caisson_foundation_params_t params, pnt3d_t position,
    dir3d_t direction);

typedef struct {
  double H1;
  double H2;
  double H3;
  double b1;
  double b2;
  double B1;
  double B2;
  double L1;
  double L2;
} raft_foundation_params_t;

PRIMCAPICALL topo_shape_t *
create_raft_foundation(raft_foundation_params_t params);
PRIMCAPICALL topo_shape_t *
create_raft_foundation_with_place(raft_foundation_params_t params,
                                  pnt3d_t position, dir3d_t direction);

typedef struct {
  double H1;
  double H2;
  double d;
  double D;
  double B;
  double t;
  bool hasBasePlate;
  bool isCircularPlate;
} direct_buried_foundation_params_t;

PRIMCAPICALL topo_shape_t *
create_direct_buried_foundation(direct_buried_foundation_params_t params);
PRIMCAPICALL topo_shape_t *create_direct_buried_foundation_with_place(
    direct_buried_foundation_params_t params, pnt3d_t position,
    dir3d_t direction);

typedef struct {
  double H1;
  double H2;
  double H3;
  double H4;
  double d;
  double D1;
  double D2;
  double t;
  double B1;
  double B2;
} steel_sleeve_foundation_params_t;

PRIMCAPICALL topo_shape_t *
create_steel_sleeve_foundation(steel_sleeve_foundation_params_t params);
PRIMCAPICALL topo_shape_t *create_steel_sleeve_foundation_with_place(
    steel_sleeve_foundation_params_t params, pnt3d_t position,
    dir3d_t direction);

typedef struct {
  double H1;
  double H2;
  double H3;
  double d;
  double B1;
  double B2;
  double L1;
  double L2;
} precast_column_foundation_params_t;

PRIMCAPICALL topo_shape_t *
create_precast_column_foundation(precast_column_foundation_params_t params);
PRIMCAPICALL topo_shape_t *create_precast_column_foundation_with_place(
    precast_column_foundation_params_t params, pnt3d_t position,
    dir3d_t direction);

typedef struct {
  double H1;
  double H2;
  double H3;
  double d;
  double B1;
  double B2;
  double L1;
  double L2;
  double B;
  double H;
  double L;
} precast_pinned_foundation_params_t;

PRIMCAPICALL topo_shape_t *
create_precast_pinned_foundation(precast_pinned_foundation_params_t params);
PRIMCAPICALL topo_shape_t *create_precast_pinned_foundation_with_place(
    precast_pinned_foundation_params_t params, pnt3d_t position,
    dir3d_t direction);
typedef struct {
  double H1;
  double H2;
  double H3;
  double H4;

  double b1;
  double b2;
  double B1;
  double B2;
  double L1;
  double L2;
  double S1;
  double S2;

  int n1;
  int n2;

  double *HX;
  int HXCount;
} precast_metal_support_foundation_params_t;

PRIMCAPICALL topo_shape_t *create_precast_metal_support_foundation(
    precast_metal_support_foundation_params_t params);
PRIMCAPICALL topo_shape_t *create_precast_metal_support_foundation_with_place(
    precast_metal_support_foundation_params_t params, pnt3d_t position,
    dir3d_t direction);

typedef struct {
  double H1;
  double H2;
  double H3;
  double H4;
  double H5;
  double b1;
  double b2;
  double b3;
  double B1;
  double B2;
  double L1;
  double L2;
  double S1;
  int n1;
} precast_concrete_support_foundation_params_t;

PRIMCAPICALL topo_shape_t *create_precast_concrete_support_foundation(
    precast_concrete_support_foundation_params_t params);
PRIMCAPICALL topo_shape_t *
create_precast_concrete_support_foundation_with_place(
    precast_concrete_support_foundation_params_t params, pnt3d_t position,
    dir3d_t direction);

typedef struct {
  char *ctype;
  double sectionalArea;
  double outsideDiameter;
  double wireWeight;
  double coefficientOfElasticity;
  double expansionCoefficient;
  double ratedStrength;
} transmission_line_params_t;

PRIMCAPICALL topo_shape_t *
create_transmission_line(transmission_line_params_t params, pnt3d_t startPoint,
                         pnt3d_t endPoint);

typedef enum {
  INSULATOR_MATERIAL_CERAMIC = 1,
  INSULATOR_MATERIAL_GLASS = 2,
  INSULATOR_MATERIAL_COMPOSITE = 3
};

typedef enum { ARRANGEMENT_HORIZONTAL = 1, ARRANGEMENT_VERTICAL = 2 };

typedef enum { APPLICATION_CONDUCTOR = 1, APPLICATION_GROUND_WIRE = 2 };

typedef enum { STRING_TYPE_SUSPENSION = 1, STRING_TYPE_TENSION = 2 };

typedef struct {
  double majorRadius;
  double minorRadius;
  double gap;
} composite_insulator_params_t;

typedef struct {
  double leftUpper;
  double rightUpper;
  double leftLower;
  double rightLower;
} fitting_lengths_t;

typedef struct {
  int count;
  double spacing;
  int arrangement;
} multi_link_t;

typedef struct {
  bool isComposite;
  union {
    double radius;
    composite_insulator_params_t compositeParams;
  } radiusData;
  double height;
  int leftCount;
  int rightCount;
  int material;
} insulator_params_t;

typedef struct {
  int count;
  double position;
  double height;
  double radius;
} grading_ring_t;

typedef struct {
  char *ctype;
  int subNum;
  int subType;
  double splitDistance;
  double vAngleLeft;
  double vAngleRight;
  double uLinkLength;
  double weight;
  fitting_lengths_t fittingLengths;
  multi_link_t multiLink;
  insulator_params_t insulator;
  grading_ring_t gradingRing;
  int application;
  int stringType;
} insulator_composite_params_t;

PRIMCAPICALL topo_shape_t *
create_composite_insulator(insulator_composite_params_t params);
PRIMCAPICALL topo_shape_t *
create_composite_insulator_with_place(insulator_composite_params_t params,
                                      pnt3d_t position, dir3d_t direction);
#ifdef __cplusplus
}
#endif

#endif
