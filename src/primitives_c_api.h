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

typedef enum {
  CURVE_TYPE_LINE = 0,
  CURVE_TYPE_ARC = 1,
  CURVE_TYPE_SPLINE = 2
} curve_type_t;

typedef struct {
  pnt3d_t *controlPoints;
  int numPoints;
} curve_segment_t;

typedef struct {
  curve_segment_t *segments;
  curve_type_t *curveTypes;
  int numSegments;
  double diameter;
} curve_cable_params_t;

PRIMCAPICALL topo_shape_t *create_curve_cable(curve_cable_params_t params);
PRIMCAPICALL topo_shape_t *
create_curve_cable_with_place(curve_cable_params_t params, pnt3d_t position,
                              dir3d_t direction, dir3d_t upDirection);

typedef struct {
  double L1;
  double L2;
  double X;
  double length;
} angle_steel_params_t;

PRIMCAPICALL topo_shape_t *create_angle_steel(angle_steel_params_t params);
PRIMCAPICALL topo_shape_t *
create_angle_steel_with_place(angle_steel_params_t params, pnt3d_t position,
                              dir3d_t xDir, dir3d_t longEdgeDir);

typedef struct {
  double height;
  double flangeWidth;
  double webThickness;
  double flangeThickness;
  double length;
} i_shaped_steel_params_t;

PRIMCAPICALL topo_shape_t *
create_i_shaped_steel(i_shaped_steel_params_t params);
PRIMCAPICALL topo_shape_t *
create_i_shaped_steel_with_place(i_shaped_steel_params_t params,
                                 pnt3d_t position, dir3d_t xDir, dir3d_t zDir);

typedef struct {
  double height;
  double flangeWidth;
  double webThickness;
  double flangeThickness;
  double length;
} channel_steel_params_t;

PRIMCAPICALL topo_shape_t *create_channel_steel(channel_steel_params_t params);
PRIMCAPICALL topo_shape_t *
create_channel_steel_with_place(channel_steel_params_t params, pnt3d_t position,
                                dir3d_t xDir, dir3d_t zDir);

typedef struct {
  double height;
  double width;
  double webThickness;
  double flangeThickness;
  double length;
} t_steel_params_t;

PRIMCAPICALL topo_shape_t *create_t_steel(t_steel_params_t params);
PRIMCAPICALL topo_shape_t *create_t_steel_with_place(t_steel_params_t params,
                                                     pnt3d_t position,
                                                     dir3d_t xDir,
                                                     dir3d_t zDir);

typedef struct {
  double H1;
  double H2;
  double H3;
  double H4;
  double d;
  double D;
} bored_pile_params_t;

PRIMCAPICALL topo_shape_t *create_bored_pile_base(bored_pile_params_t params);
PRIMCAPICALL topo_shape_t *
create_bored_pile_base_with_place(bored_pile_params_t params, pnt3d_t position,
                                  dir3d_t direction);

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
create_rock_pile_cap_base(rock_pile_cap_params_t params);
PRIMCAPICALL topo_shape_t *
create_rock_pile_cap_base_with_place(rock_pile_cap_params_t params,
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

PRIMCAPICALL topo_shape_t *create_pile_cap_base(pile_cap_params_t params);
PRIMCAPICALL topo_shape_t *
create_pile_cap_base_with_place(pile_cap_params_t params, pnt3d_t position,
                                dir3d_t direction);

typedef struct {
  double H1;
  double H2;
  double d;
  double B1;
  double L1;
  int ZCOUNT;
  pnt3d_t *ZPOSTARRAY;
} rock_anchor_params_t;

PRIMCAPICALL topo_shape_t *create_rock_anchor_base(rock_anchor_params_t params);
PRIMCAPICALL topo_shape_t *
create_rock_anchor_base_with_place(rock_anchor_params_t params,
                                   pnt3d_t position, dir3d_t direction);

typedef struct {
  double H1;
  double H2;
  double H3;
  double d;
  double D;
} embedded_rock_anchor_params_t;

PRIMCAPICALL topo_shape_t *
create_embedded_rock_anchor_base(embedded_rock_anchor_params_t params);
PRIMCAPICALL topo_shape_t *create_embedded_rock_anchor_base_with_place(
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
create_inclined_rock_anchor_base(inclined_rock_anchor_params_t params);
PRIMCAPICALL topo_shape_t *create_inclined_rock_anchor_base_with_place(
    inclined_rock_anchor_params_t params, pnt3d_t position, dir3d_t direction);

typedef struct {
  double H1;
  double H2;
  double H3;
  double d;
  double D;
  double alpha1;
  double alpha2;
} excavated_base_params_t;

PRIMCAPICALL topo_shape_t *
create_excavated_base(excavated_base_params_t params);
PRIMCAPICALL topo_shape_t *
create_excavated_base_with_place(excavated_base_params_t params,
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
} step_base_params_t;

PRIMCAPICALL topo_shape_t *create_step_base(step_base_params_t params);
PRIMCAPICALL topo_shape_t *
create_step_base_with_place(step_base_params_t params, pnt3d_t position,
                            dir3d_t direction);

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
} step_plate_base_params_t;

PRIMCAPICALL topo_shape_t *
create_step_plate_base(step_plate_base_params_t params);
PRIMCAPICALL topo_shape_t *
create_step_plate_base_with_place(step_plate_base_params_t params,
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
} sloped_base_base_params_t;

PRIMCAPICALL topo_shape_t *
create_sloped_base_base(sloped_base_base_params_t params);
PRIMCAPICALL topo_shape_t *
create_sloped_base_base_with_place(sloped_base_base_params_t params,
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
} composite_caisson_base_params_t;

PRIMCAPICALL topo_shape_t *
create_composite_caisson_base(composite_caisson_base_params_t params);
PRIMCAPICALL topo_shape_t *
create_composite_caisson_base_with_place(composite_caisson_base_params_t params,
                                         pnt3d_t position, dir3d_t direction);

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
} raft_base_params_t;

PRIMCAPICALL topo_shape_t *create_raft_base(raft_base_params_t params);
PRIMCAPICALL topo_shape_t *
create_raft_base_with_place(raft_base_params_t params, pnt3d_t position,
                            dir3d_t direction);

typedef struct {
  double H1;
  double H2;
  double d;
  double D;
  double B;
  double t;
  bool hasBasePlate;
  bool isCircularPlate;
} direct_buried_base_params_t;

PRIMCAPICALL topo_shape_t *
create_direct_buried_base(direct_buried_base_params_t params);
PRIMCAPICALL topo_shape_t *
create_direct_buried_base_with_place(direct_buried_base_params_t params,
                                     pnt3d_t position, dir3d_t direction);

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
} steel_sleeve_base_params_t;

PRIMCAPICALL topo_shape_t *
create_steel_sleeve_base(steel_sleeve_base_params_t params);
PRIMCAPICALL topo_shape_t *
create_steel_sleeve_base_with_place(steel_sleeve_base_params_t params,
                                    pnt3d_t position, dir3d_t direction);

typedef struct {
  double H1;
  double H2;
  double H3;
  double d;
  double B1;
  double B2;
  double L1;
  double L2;
} precast_column_base_params_t;

PRIMCAPICALL topo_shape_t *
create_precast_column_base(precast_column_base_params_t params);
PRIMCAPICALL topo_shape_t *
create_precast_column_base_with_place(precast_column_base_params_t params,
                                      pnt3d_t position, dir3d_t direction);

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
} precast_pinned_base_params_t;

PRIMCAPICALL topo_shape_t *
create_precast_pinned_base(precast_pinned_base_params_t params);
PRIMCAPICALL topo_shape_t *
create_precast_pinned_base_with_place(precast_pinned_base_params_t params,
                                      pnt3d_t position, dir3d_t direction);
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
} precast_metal_support_base_params_t;

PRIMCAPICALL topo_shape_t *
create_precast_metal_support_base(precast_metal_support_base_params_t params);
PRIMCAPICALL topo_shape_t *create_precast_metal_support_base_with_place(
    precast_metal_support_base_params_t params, pnt3d_t position,
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
} precast_concrete_support_base_params_t;

PRIMCAPICALL topo_shape_t *create_precast_concrete_support_base(
    precast_concrete_support_base_params_t params);
PRIMCAPICALL topo_shape_t *create_precast_concrete_support_base_with_place(
    precast_concrete_support_base_params_t params, pnt3d_t position,
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

// 单钩锚固参数结构体
typedef struct {
  double boltDiameter;
  double exposedLength;
  int nutCount;
  double nutHeight;
  double nutOD;
  int washerCount;
  int washerShape;
  double washerSize;
  double washerThickness;
  double anchorLength;
  double hookStraightLength;
  double hookDiameter;
} single_hook_anchor_params_t;

PRIMCAPICALL topo_shape_t *
create_single_hook_anchor(single_hook_anchor_params_t params);
PRIMCAPICALL topo_shape_t *
create_single_hook_anchor_with_place(single_hook_anchor_params_t params,
                                     pnt3d_t position, dir3d_t normal,
                                     dir3d_t xDir);

// 三钩锚固参数结构体
typedef struct {
  double boltDiameter;
  double exposedLength;
  int nutCount;
  double nutHeight;
  double nutOD;
  int washerCount;
  int washerShape;
  double washerSize;
  double washerThickness;
  double anchorLength;
  double hookStraightLengthA;
  double hookStraightLengthB;
  double hookDiameter;
  double anchorBarDiameter;
} triple_hook_anchor_params_t;

PRIMCAPICALL topo_shape_t *
create_triple_hook_anchor(triple_hook_anchor_params_t params);
PRIMCAPICALL topo_shape_t *
create_triple_hook_anchor_with_place(triple_hook_anchor_params_t params,
                                     pnt3d_t position, dir3d_t normal,
                                     dir3d_t xDir);

// 肋板锚固参数结构体
typedef struct {
  double boltDiameter;
  double exposedLength;
  int nutCount;
  double nutHeight;
  double nutOD;
  int washerCount;
  int washerShape;
  double washerSize;
  double washerThickness;
  double anchorLength;
  double basePlateSize;
  double ribTopWidth;
  double ribBottomWidth;
  double basePlateThickness;
  double ribHeight;
  double ribThickness;
} ribbed_anchor_params_t;

PRIMCAPICALL topo_shape_t *create_ribbed_anchor(ribbed_anchor_params_t params);
PRIMCAPICALL topo_shape_t *
create_ribbed_anchor_with_place(ribbed_anchor_params_t params, pnt3d_t position,
                                dir3d_t normal, dir3d_t xDir);

// 螺帽锚固参数结构体
typedef struct {
  double boltDiameter;
  double exposedLength;
  int nutCount;
  double nutHeight;
  double nutOD;
  int washerCount;
  int washerShape;
  double washerSize;
  double washerThickness;
  double anchorLength;
  double basePlateSize;
  double basePlateThickness;
  double boltToPlateDistance;
} nut_anchor_params_t;

PRIMCAPICALL topo_shape_t *create_nut_anchor(nut_anchor_params_t params);
PRIMCAPICALL topo_shape_t *
create_nut_anchor_with_place(nut_anchor_params_t params, pnt3d_t position,
                             dir3d_t normal, dir3d_t xDir);

// 三支锚固参数结构体
typedef struct {
  double boltDiameter;
  double exposedLength;
  int nutCount;
  double nutHeight;
  double nutOD;
  int washerCount;
  int washerShape;
  double washerSize;
  double washerThickness;
  double anchorLength;
  double armDiameter;
  double armStraightLength;
  double armBendLength;
  double armBendAngle;
} triple_arm_anchor_params_t;

PRIMCAPICALL topo_shape_t *
create_triple_arm_anchor(triple_arm_anchor_params_t params);
PRIMCAPICALL topo_shape_t *
create_triple_arm_anchor_with_place(triple_arm_anchor_params_t params,
                                    pnt3d_t position, dir3d_t normal,
                                    dir3d_t xDir);

// 定位板锚固参数结构体
typedef struct {
  double boltDiameter;
  double exposedLength;
  int nutCount;
  double nutHeight;
  double nutOD;
  int washerCount;
  int washerShape;
  double washerSize;
  double washerThickness;
  double anchorLength;
  double plateLength;
  double plateThickness;
  double toBaseDistance;
  double toBottomDistance;
  double groutHoleDiameter;
} positioning_plate_anchor_params_t;

PRIMCAPICALL topo_shape_t *
create_positioning_plate_anchor(positioning_plate_anchor_params_t params);
PRIMCAPICALL topo_shape_t *create_positioning_plate_anchor_with_place(
    positioning_plate_anchor_params_t params, pnt3d_t position, dir3d_t normal,
    dir3d_t xDir);

// 插入角钢参数结构体
typedef struct {
  double legWidth;
  double thickness;
  double slope;
  double exposedLength;
  double anchorLength;
} stub_angle_params_t;

PRIMCAPICALL topo_shape_t *create_stub_angle(stub_angle_params_t params);
PRIMCAPICALL topo_shape_t *
create_stub_angle_with_place(stub_angle_params_t params, pnt3d_t position,
                             dir3d_t normal, dir3d_t xDir);

// 插入钢管参数结构体
typedef struct {
  double diameter;
  double thickness;
  double slope;
  double exposedLength;
  double anchorLength;
} stub_tube_params_t;

PRIMCAPICALL topo_shape_t *create_stub_tube(stub_tube_params_t params);
PRIMCAPICALL topo_shape_t *
create_stub_tube_with_place(stub_tube_params_t params, pnt3d_t position,
                            dir3d_t normal, dir3d_t xDir);

typedef enum {
  MEMBER_TYPE_ANGLE = 1,       // 角钢
  MEMBER_TYPE_TUBE = 2,        // 等径钢管
  MEMBER_TYPE_TAPERED_TUBE = 3 // 锥形钢管
};

typedef enum {
  ATTACHMENT_TYPE_GROUND_WIRE = 1, // 地线挂点
  ATTACHMENT_TYPE_CONDUCTOR = 2,   // 导线挂点
  ATTACHMENT_TYPE_JUMPER = 3       // 跳线挂点
};

typedef struct {
  char *id;         // 节点编号
  pnt3d_t position; // 节点坐标
} pole_tower_node_t;

typedef struct {
  char *id;            // 杆件编号
  char *startNodeId;   // 起始节点ID
  char *endNodeId;     // 结束节点ID
  int ctype;           // 杆件类型
  char *specification; // 规格
  char *material;      // 材质
  dir3d_t xDirection;  // X肢方向(角钢专用)
  dir3d_t yDirection;  // Y肢方向(角钢专用)
  double end1Diameter; // 端1直径(锥形钢管专用)
  double end2Diameter; // 端2直径(锥形钢管专用)
  double thickness;    // 厚度(钢管专用)
  int sides;           // 边数(锥形钢管专用)
} pole_tower_member_t;

typedef struct {
  char *name;       // 挂点名称
  int ctype;        // 挂点类型
  pnt3d_t position; // 挂点坐标
} pole_tower_attachment_t;

typedef struct {
  char *id;                 // 接腿编号
  double commonHeight;      // 共用部分高度
  double specificHeight;    // 非共用部分高度
  pole_tower_node_t *nodes; // 接腿节点数组
  int nodeCount;            // 节点数量
} pole_tower_leg_t;

typedef struct {
  char *id;                 // 本体编号
  double height;            // 本体高度
  pole_tower_node_t *nodes; // 本体节点数组
  int nodeCount;            // 节点数量
  pole_tower_leg_t *legs;   // 接腿信息数组
  int legCount;             // 接腿数量
} pole_tower_body_t;

typedef struct {
  double value; // 呼高值
  char *bodyId; // 对应本体ID
  char *legId;  // 对应接腿ID
} pole_tower_height_t;

typedef struct {
  pole_tower_height_t *heights;         // 呼高数组
  int heightCount;                      // 呼高数量
  pole_tower_body_t *bodies;            // 本体数组
  int bodyCount;                        // 本体数量
  pole_tower_member_t *members;         // 杆件数组
  int memberCount;                      // 杆件数量
  pole_tower_attachment_t *attachments; // 挂点数组
  int attachmentCount;                  // 挂点数量
} pole_tower_params_t;

PRIMCAPICALL topo_shape_t *create_pole_tower(pole_tower_params_t params);
PRIMCAPICALL topo_shape_t *
create_pole_tower_with_place(pole_tower_params_t params, pnt3d_t position,
                             dir3d_t normal, dir3d_t xDir);

typedef struct {
  double length;
  double outerDiameter;
  double terminalLength;
  double innerDiameter;
} cable_joint_params_t;

PRIMCAPICALL topo_shape_t *create_cable_joint(cable_joint_params_t params);
PRIMCAPICALL topo_shape_t *
create_cable_joint_with_place(cable_joint_params_t params, pnt3d_t position,
                              dir3d_t direction, dir3d_t xDir);

typedef struct {
  double length;
  double height;
  double width;
} optical_fiber_box_params_t;

PRIMCAPICALL topo_shape_t *
create_optical_fiber_box(optical_fiber_box_params_t params);
PRIMCAPICALL topo_shape_t *
create_optical_fiber_box_with_place(optical_fiber_box_params_t params,
                                    pnt3d_t position, dir3d_t direction,
                                    dir3d_t xDir);

enum {
  CABLE_BOX_DIRECT_GROUND = 1,
  CABLE_BOX_PROTECTIVE_GROUND = 2,
  CABLE_BOX_CROSS_INTERCONNECT = 3
};

typedef struct {
  int sort;
  double height;
  double topDiameter;
  double bottomDiameter;
  double tailDiameter;
  double tailHeight;
  double upperTerminalDiameter;
  double lowerTerminalLength;
  double lowerTerminalDiameter;
  double hole1Diameter;
  double hole2Diameter;
  double hole1Distance;
  double holeSpacing;
  double flangeHoleDiameter;
  double flangeHoleSpacing;
  double flangeWidth;
  double flangeCenterHoleRadius;
  double flangeChamferRadius;
  double flangeOpeningWidth;
  double flangeBoltHeight;
} cable_terminal_params_t;

PRIMCAPICALL topo_shape_t *
create_cable_terminal(cable_terminal_params_t params);
PRIMCAPICALL topo_shape_t *
create_cable_terminal_with_place(cable_terminal_params_t params,
                                 pnt3d_t position, dir3d_t direction);

typedef struct {
  int ctype;
  double length;
  double width;
  double height;
  int portCount;
  double portDiameter;
  double backPanelDistance;
  double sidePanelDistance;
} cable_accessory_params_t;

PRIMCAPICALL topo_shape_t *
create_cable_accessory(cable_accessory_params_t params);
PRIMCAPICALL topo_shape_t *
create_cable_accessory_with_place(cable_accessory_params_t params,
                                  pnt3d_t position, dir3d_t normal,
                                  dir3d_t xDir);

enum {
  CABLE_CLAMP_SINGLE = 1,
  CABLE_CLAMP_LINEAR = 2,
  CABLE_CLAMP_CONTACT_TRIPLE = 3,
  CABLE_CLAMP_SEPARATE_TRIPLE = 4
};

typedef struct {
  double length;
  double rootHeight;
  double rootWidth;
  double width;
  double topThickness;
  double rootThickness;
  pnt3d_t *columnMountPoints;
  pnt3d_t *clampMountPoints;
  int columnMountCount;
  int clampMountCount;
} cable_bracket_params_t;

PRIMCAPICALL topo_shape_t *create_cable_bracket(cable_bracket_params_t params);
PRIMCAPICALL topo_shape_t *
create_cable_bracket_with_place(cable_bracket_params_t params, pnt3d_t position,
                                dir3d_t normal, dir3d_t xDir);

typedef struct {
  int ctype;
  double diameter;
  double thickness;
  double width;
} cable_clamp_params_t;

PRIMCAPICALL topo_shape_t *create_cable_clamp(cable_clamp_params_t params);
PRIMCAPICALL topo_shape_t *
create_cable_clamp_with_place(cable_clamp_params_t params, pnt3d_t position,
                              dir3d_t normal, dir3d_t xDir);

typedef struct {
  char *specification;
  double length;
  double radius;
  double arcAngle;
  double width;
  double fixedLegLength;
  double fixedLegWidth;
  double thickness;
  pnt3d_t *mountPoints;
  int mountCount;
} cable_pole_params_t;

PRIMCAPICALL topo_shape_t *create_cable_pole(cable_pole_params_t params);
PRIMCAPICALL topo_shape_t *
create_cable_pole_with_place(cable_pole_params_t params, pnt3d_t position,
                             dir3d_t direction);

typedef struct {
  double length;
  double height;
  double thickness;
} ground_flat_iron_params_t;

PRIMCAPICALL topo_shape_t *
create_ground_flat_iron(ground_flat_iron_params_t params);
PRIMCAPICALL topo_shape_t *
create_ground_flat_iron_with_place(ground_flat_iron_params_t params,
                                   pnt3d_t position, dir3d_t normal,
                                   dir3d_t xDir);

typedef struct {
  double length;
  double radius;
  double height;
  double materialRadius;
  double lowerLength;
} embedded_part_params_t;

PRIMCAPICALL topo_shape_t *create_embedded_part(embedded_part_params_t params);
PRIMCAPICALL topo_shape_t *
create_embedded_part_with_place(embedded_part_params_t params, pnt3d_t position,
                                dir3d_t normal, dir3d_t xDir);

typedef struct {
  double thickness;
  double height;
  double radius;
  double length;
} u_shaped_ring_params_t;

PRIMCAPICALL topo_shape_t *create_u_shaped_ring(u_shaped_ring_params_t params);
PRIMCAPICALL topo_shape_t *
create_u_shaped_ring_with_place(u_shaped_ring_params_t params, pnt3d_t position,
                                dir3d_t normal, dir3d_t xDir);

enum {
  CONNECTION_SECTION_RECTANGULAR = 1,
  CONNECTION_SECTION_HORSESHOE = 2,
  CONNECTION_SECTION_CIRCULAR = 3
};

enum { TUNNEL_WELL_STRAIGHT = 1, TUNNEL_WELL_STRAIGHT_TUNNEL = 2 };

enum {
  THREE_WAY_WELL_WORKING = 1,
  THREE_WAY_WELL_OPEN_CUT = 2,
  THREE_WAY_WELL_UNDERGROUND = 3
};

enum { CORNER_STYLE_ROUNDED = 1, CORNER_STYLE_ANGLED = 2 };

enum { SHAFT_STYLE_CIRCULAR = 1, SHAFT_STYLE_RECTANGULAR = 2 };

typedef struct {
  double height;
  double ringRadius;
  double pipeDiameter;
  pnt3d_t connectionPoint;
} lifting_eye_params_t;

PRIMCAPICALL topo_shape_t *create_lifting_eye(lifting_eye_params_t params);
PRIMCAPICALL topo_shape_t *
create_lifting_eye_with_place(lifting_eye_params_t params, pnt3d_t position,
                              dir3d_t normal, dir3d_t xDir);

typedef struct {
  double leftLength;
  double rightLength;
  double width;
  double height;
  double topThickness;
  double bottomThickness;
  double wallThickness;
  double angle;
  double cornerRadius;
  double cushionExtension;
  double cushionThickness;
} corner_well_params_t;

PRIMCAPICALL topo_shape_t *create_corner_well(corner_well_params_t params);
PRIMCAPICALL topo_shape_t *
create_corner_well_with_place(corner_well_params_t params, pnt3d_t position,
                              dir3d_t direction, dir3d_t xDir);

typedef struct {
  int ctype;
  double length;
  double width;
  double height;
  double radius;
  double topThickness;
  double bottomThickness;
  int leftSectionType;
  double leftLength;
  double leftWidth;
  double leftHeight;
  double leftArchHeight;
  int rightSectionType;
  double rightLength;
  double rightWidth;
  double rightHeight;
  double rightArchHeight;
  double outerWallThickness;
  double innerWallThickness;
  double cushionExtension;
  double cushionThickness;
} tunnel_well_params_t;

PRIMCAPICALL topo_shape_t *create_tunnel_well(tunnel_well_params_t params);
PRIMCAPICALL topo_shape_t *
create_tunnel_well_with_place(tunnel_well_params_t params, pnt3d_t position,
                              dir3d_t direction, dir3d_t xDir);

typedef struct {
  int ctype;
  int cornerType;
  int shaftType;
  double length;
  double width;
  double height;
  double shaftRadius;
  double cornerRadius;
  double cornerLength;
  double cornerWidth;
  double angle;
  double branchLength;
  double branchWidth;
  double topThickness;
  double bottomThickness;
  int leftSectionStyle;
  double leftSectionLength;
  double leftSectionWidth;
  double leftSectionHeight;
  double leftSectionArchHeight;
  int rightSectionStyle;
  double rightSectionLength;
  double rightSectionWidth;
  double rightSectionHeight;
  double rightSectionArchHeight;
  int branchSectionStyle;
  double branchSectionLength;
  double branchSectionWidth;
  double branchSectionHeight;
  double branchSectionArchHeight;
  double outerWallThickness;
  double innerWallThickness;
  bool isDoubleShaft;
  double doubleShaftSpacing;
  double outerWallExtension;
  double innerWallExtension;
  double cushionExtension;
  double cushionThickness;
  double innerBottomThickness;
  double outerBottomThickness;
} three_way_well_params_t;

PRIMCAPICALL topo_shape_t *
create_three_way_well(three_way_well_params_t params);
PRIMCAPICALL topo_shape_t *
create_three_way_well_with_place(three_way_well_params_t params,
                                 pnt3d_t position, dir3d_t mainDirection,
                                 dir3d_t branchDirection);

typedef struct {
  double length;
  double width;
  double height;
  int cornerStyle;
  double cornerRadius;
  double cornerLength;
  double cornerWidth;
  double branchLength;
  double branchWidth;
  double roofThickness;
  double floorThickness;
  struct {
    int sectionType;
    double length;
    double width;
    double height;
    double archHeight;
  } leftSection, rightSection, branchSection1, branchSection2;
  double outerWallThickness;
  double innerWallThickness;
  double cushionExtension;
  double cushionThickness;
} four_way_well_params_t;

PRIMCAPICALL topo_shape_t *create_four_way_well(four_way_well_params_t params);
PRIMCAPICALL topo_shape_t *
create_four_way_well_with_place(four_way_well_params_t params, pnt3d_t position,
                                dir3d_t direction, dir3d_t xDirection);

enum {
  TUNNEL_SECTION_RECTANGULAR = 1,
  TUNNEL_SECTION_HORSESHOE = 2,
  TUNNEL_SECTION_CIRCULAR = 3
};

typedef struct {
  pnt3d_t position;
  int ctype;
} channel_point_t;

typedef struct {
  int pipeType;
  bool hasEnclosure;
  double enclosureWidth;
  double enclosureHeight;
  double baseExtension;
  double baseThickness;
  double cushionExtension;
  double cushionThickness;
  pnt2d_t *pipePositions;
  double *pipeInnerDiameters;
  double *pipeWallThicknesses;
  int pipeCount;
  double pullPipeInnerDiameter;
  double pullPipeThickness;
  channel_point_t *points;
  int pointCount;
} pipe_row_params_t;

PRIMCAPICALL topo_shape_t *create_pipe_row(pipe_row_params_t params);
PRIMCAPICALL topo_shape_t *create_pipe_row_with_place(pipe_row_params_t params,
                                                      pnt3d_t position,
                                                      dir3d_t normal,
                                                      dir3d_t xDir);

typedef struct {
  double width;
  double height;
  double coverWidth;
  double coverThickness;
  double baseExtension;
  double baseThickness;
  double cushionExtension;
  double cushionThickness;
  double wallThickness;
  double wallThickness2;
  channel_point_t *points;
  int pointCount;
} cable_trench_params_t;

PRIMCAPICALL topo_shape_t *create_cable_trench(cable_trench_params_t params);
PRIMCAPICALL topo_shape_t *
create_cable_trench_with_place(cable_trench_params_t params, pnt3d_t position,
                               dir3d_t direction, dir3d_t xDir);

typedef struct {
  int style;
  double width;
  double height;
  double roofThickness;
  double floorThickness;
  double outerWallThickness;
  double innerWallThickness;
  double archHeight;
  double bottomPlatformHeight;
  double cushionExtension;
  double cushionThickness;
  channel_point_t *points;
  int pointCount;
} cable_tunnel_params_t;

PRIMCAPICALL topo_shape_t *create_cable_tunnel(cable_tunnel_params_t params);
PRIMCAPICALL topo_shape_t *
create_cable_tunnel_with_place(cable_tunnel_params_t params, pnt3d_t position,
                               dir3d_t direction, dir3d_t xDir);

enum { CABLE_TRAY_ARCH = 1, CABLE_TRAY_BEAM = 2 };

enum { MANHOLE_CIRCULAR = 1, MANHOLE_RECTANGULAR = 2 };

enum { MANHOLE_COVER_CIRCULAR = 1, MANHOLE_COVER_RECTANGULAR = 2 };

typedef struct {
  int style;
  double columnDiameter;
  double columnHeight;
  double span;
  double width;
  double height;
  double topPlateHeight;
  double archHeight;
  double wallThickness;
  int pipeCount;
  pnt3d_t *pipePositions;
  double *pipeInnerDiameters;
  double *pipeWallThicknesses;
  int hasProtectionPlate;
  channel_point_t *points;
  int pointCount;
} cable_tray_params_t;

PRIMCAPICALL topo_shape_t *create_cable_tray(cable_tray_params_t params);
PRIMCAPICALL topo_shape_t *
create_cable_tray_with_place(cable_tray_params_t params, pnt3d_t position,
                             dir3d_t direction, dir3d_t xDir);

typedef struct {
  double length;
  double width;
  double height;
} cable_L_beam_params_t;

PRIMCAPICALL topo_shape_t *create_cable_L_beam(cable_L_beam_params_t params);
PRIMCAPICALL topo_shape_t *
create_cable_L_beam_with_place(cable_L_beam_params_t params, pnt3d_t position,
                               dir3d_t xDir, dir3d_t zDir);

typedef struct {
  int style;
  double length;
  double width;
  double height;
  double wallThickness;
} manhole_params_t;

PRIMCAPICALL topo_shape_t *create_manhole(manhole_params_t params);
PRIMCAPICALL topo_shape_t *create_manhole_with_place(manhole_params_t params,
                                                     pnt3d_t position,
                                                     dir3d_t direction,
                                                     dir3d_t xDir);

typedef struct {
  int style;
  double length;
  double width;
  double thickness;
} manhole_cover_params_t;

PRIMCAPICALL topo_shape_t *create_manhole_cover(manhole_cover_params_t params);
PRIMCAPICALL topo_shape_t *
create_manhole_cover_with_place(manhole_cover_params_t params, pnt3d_t position,
                                dir3d_t direction, dir3d_t xDir);

typedef struct {
  double length;
  double width;
  double thickness;
} ladder_params_t;

PRIMCAPICALL topo_shape_t *create_ladder(ladder_params_t params);
PRIMCAPICALL topo_shape_t *create_ladder_with_place(ladder_params_t params,
                                                    pnt3d_t position,
                                                    dir3d_t direction,
                                                    dir3d_t xDir);

typedef struct {
  double length;
  double width;
  double depth;
  double floorThickness;
} sump_params_t;

PRIMCAPICALL topo_shape_t *create_sump(sump_params_t params);
PRIMCAPICALL topo_shape_t *create_sump_with_place(sump_params_t params,
                                                  pnt3d_t position,
                                                  dir3d_t normal, dir3d_t xDir);

typedef struct {
  double height;
  double width;
} footpath_params_t;

PRIMCAPICALL topo_shape_t *create_footpath(footpath_params_t params);
PRIMCAPICALL topo_shape_t *create_footpath_with_place(footpath_params_t params,
                                                      pnt3d_t position,
                                                      dir3d_t direction,
                                                      dir3d_t xDir);

typedef struct {
  double supportWallThickness;
  double supportDiameter;
  double supportHeight;
  double roofThickness;
  double innerDiameter;
  double workingHeight;
  double outerWallThickness;
  double innerWallThickness;
} shaft_chamber_params_t;

PRIMCAPICALL topo_shape_t *create_shaft_chamber(shaft_chamber_params_t params);
PRIMCAPICALL topo_shape_t *
create_shaft_chamber_with_place(shaft_chamber_params_t params, pnt3d_t position,
                                dir3d_t direction, dir3d_t xDir);

typedef struct {
  int style;
  double length;
  double width;
  double thickness;
  int holeCount;
  pnt2d_t *holePositions;
  int *holeStyles;
  double *holeDiameters;
  double *holeWidths;
} tunnel_partition_board_params_t;

PRIMCAPICALL topo_shape_t *
create_tunnel_partition_board(tunnel_partition_board_params_t params);
PRIMCAPICALL topo_shape_t *
create_tunnel_partition_board_with_place(tunnel_partition_board_params_t params,
                                         pnt3d_t position, dir3d_t normal,
                                         dir3d_t xDir);

typedef struct {
  double topLength;
  double middleLength;
  double bottomLength;
  double topWidth;
  double middleWidth;
  double bottomWidth;
  double topHeight;
  double height;
  double baseHeight;
} ventilation_pavilion_params_t;

PRIMCAPICALL topo_shape_t *
create_ventilation_pavilion(ventilation_pavilion_params_t params);
PRIMCAPICALL topo_shape_t *
create_ventilation_pavilion_with_place(ventilation_pavilion_params_t params,
                                       pnt3d_t position, dir3d_t direction,
                                       dir3d_t xDir);

typedef struct {
  double diameter;
  double wallThickness;
  double height;
} straight_ventilation_duct_params_t;

PRIMCAPICALL topo_shape_t *
create_straight_ventilation_duct(straight_ventilation_duct_params_t params);
PRIMCAPICALL topo_shape_t *create_straight_ventilation_duct_with_place(
    straight_ventilation_duct_params_t params, pnt3d_t position,
    dir3d_t direction, dir3d_t xDir);

typedef struct {
  double hoodRoomLength;
  double hoodRoomWidth;
  double hoodRoomHeight;
  double hoodWallThickness;
  double ductCenterHeight;
  double ductLeftDistance;
  double ductDiameter;
  double ductWallThickness;
  double ductLength;
  double ductHeightDifference;
  double baseLength;
  double baseWidth;
  double baseHeight;
  double baseRoomLength;
  double baseRoomWallThickness;
  double baseRoomWidth;
  double baseRoomHeight;
} oblique_ventilation_duct_params_t;

PRIMCAPICALL topo_shape_t *
create_oblique_ventilation_duct(oblique_ventilation_duct_params_t params);
PRIMCAPICALL topo_shape_t *create_oblique_ventilation_duct_with_place(
    oblique_ventilation_duct_params_t params, pnt3d_t position,
    dir3d_t direction, dir3d_t xDir);

typedef struct {
  double length;
  double width;
  double height;
  double neckDiameter;
  double neckHeight;
  double cushionExtension;
  double floorThickness;
  double wallThickness;
} drainage_well_params_t;

PRIMCAPICALL topo_shape_t *create_drainage_well(drainage_well_params_t params);
PRIMCAPICALL topo_shape_t *
create_drainage_well_with_place(drainage_well_params_t params, pnt3d_t position,
                                dir3d_t direction, dir3d_t xDir);

typedef enum { PIPE_SUPPORT_SINGLE_SIDE = 1, PIPE_SUPPORT_DOUBLE_SIDE = 2 };

typedef struct {
  int style;
  int count;
  pnt2d_t *positions;
  double *radii;
  double length;
  double height;
} pipe_support_params_t;

PRIMCAPICALL void pnt2d_t_array_set(pnt2d_t *array, int index, pnt2d_t value);
PRIMCAPICALL void double_array_set(double *array, int index, double value);

PRIMCAPICALL topo_shape_t *create_pipe_support(pipe_support_params_t params);
PRIMCAPICALL topo_shape_t *
create_pipe_support_with_place(pipe_support_params_t params, pnt3d_t position,
                               dir3d_t direction, dir3d_t xDir);

typedef enum { COVER_PLATE_RECTANGLE = 0, COVER_PLATE_SECTOR = 1 };

typedef struct {
  int style;
  double length;
  double width;
  double smallRadius;
  double largeRadius;
  double thickness;
} cover_plate_params_t;

PRIMCAPICALL topo_shape_t *create_cover_plate(cover_plate_params_t params);
PRIMCAPICALL topo_shape_t *
create_cover_plate_with_place(cover_plate_params_t params, pnt3d_t position,
                              dir3d_t normal, dir3d_t xDir);

typedef struct {
  double outerLength;
  double outerHeight;
  double innerLength;
  double innerHeight;
  double coverThickness;
} cable_ray_params_t;

PRIMCAPICALL topo_shape_t *create_cable_ray(cable_ray_params_t params);
PRIMCAPICALL topo_shape_t *
create_cable_ray_with_place(cable_ray_params_t params, pnt3d_t position,
                            dir3d_t direction, dir3d_t xDir);

#ifdef __cplusplus
}
#endif

#endif
