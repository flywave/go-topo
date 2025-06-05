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
} rectangular_fixed_plate_params_t;

PRIMCAPICALL topo_shape_t *
create_rectangular_fixed_plate(rectangular_fixed_plate_params_t params);
PRIMCAPICALL topo_shape_t *create_rectangular_fixed_plate_with_place(
    rectangular_fixed_plate_params_t params, pnt3d_t position,
    dir3d_t lengthDir, dir3d_t widthDir);

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
PRIMCAPICALL topo_wire_t create_wire_centerline(wire_params_t params);
PRIMCAPICALL topo_shape_t *create_wire_with_place(wire_params_t params,
                                                  pnt3d_t position,
                                                  dir3d_t direction,
                                                  dir3d_t upDirection);
PRIMCAPICALL pnt3d_t *sample_wire_points(wire_params_t params,
                                         double tessellation, int *out_count);

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
PRIMCAPICALL topo_wire_t create_cable_centerline(cable_params_t params);
PRIMCAPICALL topo_shape_t *create_cable_with_place(cable_params_t params,
                                                   pnt3d_t position,
                                                   dir3d_t direction,
                                                   dir3d_t upDirection);
PRIMCAPICALL pnt3d_t *sample_cable_points(cable_params_t params,
                                          double tessellation, int *out_count);

typedef enum {
  CURVE_TYPE_LINE = 0,
  CURVE_TYPE_ARC = 1,
  CURVE_TYPE_BEZIER = 2
} curve_type_t;

typedef struct {
  pnt3d_t *controlPoints;
  int numPoints;
} curve_segment_t;
PRIMCAPICALL pnt3d_t *
sample_curve_points(const pnt3d_t *control_points, const int *point_counts,
                    int array_count, const curve_type_t *curve_types,
                    int curve_type_count, double tessellation, int *out_count);

typedef struct {
  curve_segment_t *segments;
  curve_type_t *curveTypes;
  int numSegments;
  double diameter;
} curve_cable_params_t;

PRIMCAPICALL topo_shape_t *create_curve_cable(curve_cable_params_t params);
PRIMCAPICALL topo_wire_t
create_curve_cable_centerline(curve_cable_params_t params);
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
PRIMCAPICALL topo_wire_t create_transmission_centerline(
    transmission_line_params_t params, pnt3d_t startPoint, pnt3d_t endPoint);
PRIMCAPICALL pnt3d_t *
sample_transmission_line_points(transmission_line_params_t params,
                                pnt3d_t startPoint, pnt3d_t endPoint,
                                double tessellation, int *out_count);

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

enum washer_shape_type_t {
  WASHER_SHAPE_TYPE_SQUARE = 1, // 方形垫片
  WASHER_SHAPE_TYPE_ROUND = 2   // 圆形垫片
};

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

typedef struct {
  pnt3d_t *points;        // 电缆路径点集
  int numPoints;          // 点数量
  double outsideDiameter; // 电缆外径(mm)
} cable_wire_params_t;

PRIMCAPICALL topo_shape_t *create_cable_wire(cable_wire_params_t params);
PRIMCAPICALL topo_shape_t *
create_cable_wire_with_place(cable_wire_params_t params, pnt3d_t position,
                             dir3d_t direction, dir3d_t upDirection);

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

enum {
  CABLE_TERMINAL_TYPE_OUTDOOR = 1, // 户外
  CABLE_TERMINAL_TYPE_GIS = 2,     // 户内
  CABLE_TERMINAL_TYPE_DRY = 3      // 干式
};

typedef struct {
  int sort;              // 类型 SORT: 1-户外, 2-户内(GIS), 3-干式
  double height;         // 总高度 H (mm)
  double topDiameter;    // 上部直径 L1 (mm)
  double bottomDiameter; // 下部直径 d (mm)
  double tailDiameter;   // 尾管直径 D3 (mm)
  double tailHeight;     // 尾管高度 WH (mm)

  // 伞裙参数 (仅户外和干式终端使用)
  int skirtCount;                  // 伞裙片数 N
  double upperSkirtTopDiameter;    // 伞裙1上部直径 SD (mm)
  double upperSkirtBottomDiameter; // 伞裙1下部直径 SDI (mm)
  double lowerSkirtTopDiameter;    // 伞裙2上部直径 BD (mm)
  double lowerSkirtBottomDiameter; // 伞裙2下部直径 BDI (mm)
  double skirtSectionHeight;       // 伞裙节高度 h (mm)

  // 端子参数
  double upperTerminalLength;   // 上端子长度 LI (mm)
  double upperTerminalDiameter; // 上端子直径 ZDI (mm)
  double lowerTerminalLength;   // 下端子长度 L2 (mm)
  double lowerTerminalDiameter; // 下端子直径 ZD2 (mm)

  // 连接孔参数
  double hole1Diameter; // 连接孔1直径 Φ1 (mm)
  double hole2Diameter; // 连接孔2直径 Φ2 (mm)
  double hole1Distance; // 连接孔1端距离 dl (mm)
  double holeSpacing;   // 连接孔1到2间距 d2 (mm)

  // 户外终端专用参数
  double flangeHoleDiameter;     // 法兰盘连接孔直径 FD (mm)
  double flangeHoleSpacing;      // 法兰盘连接孔间距 KD (mm)
  double flangeWidth;            // 法兰盘宽度 PD (mm)
  double flangeCenterHoleRadius; // 法兰盘中心孔半径 PR (mm)
  double flangeChamferRadius;    // 法兰盘边缘倒角半径 BR (mm)
  double flangeOpeningWidth;     // 法兰盘开口宽度 K (mm)
  double flangeBoltHeight;       // 法兰盘螺栓高度 H1 (mm)
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
  double leftArcHeight;
  int rightSectionType;
  double rightLength;
  double rightWidth;
  double rightHeight;
  double rightArcHeight;
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
  double branchLeftLength;
  double branchWidth;
  double topThickness;
  double bottomThickness;
  int leftSectionStyle;
  double leftSectionLength;
  double leftSectionWidth;
  double leftSectionHeight;
  double leftSectionArcHeight;
  int rightSectionStyle;
  double rightSectionLength;
  double rightSectionWidth;
  double rightSectionHeight;
  double rightSectionArcHeight;
  int branchSectionStyle;
  double branchSectionLength;
  double branchSectionWidth;
  double branchSectionHeight;
  double branchSectionArcHeight;
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

enum {
  FOUR_WAY_WELL_WORKING = 1,
  FOUR_WAY_WELL_OPEN_CUT = 2,
  FOUR_WAY_WELL_UNDERGROUND = 3
};

typedef struct {
  int ctype;
  double length;
  double width;
  double height;
  double shaftRadius;
  int cornerStyle;
  double cornerRadius;
  double cornerLength;
  double cornerWidth;
  double branchLength;
  double branchWidth;
  double topThickness;
  double bottomThickness;
  struct {
    int sectionType;
    double length;
    double width;
    double height;
    double arcHeight;
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

enum cable_tunnel_type_t {
  CABLE_TUNNEL_TYPE_LINE = 0, // 直道
  CABLE_TUNNEL_TYPE_ARC = 1   // 弧形
};

typedef struct {
  pnt3d_t position;
  int ctype;
} channel_point_t;

PRIMCAPICALL topo_wire_t create_channel_centerline(channel_point_t *points,
                                                   int pointCount);
PRIMCAPICALL pnt3d_t *sample_channel_points(const channel_point_t *points,
                                            int point_count,
                                            double tessellation,
                                            int *out_count);

enum pipe_row_type_t {
  PIPE_ROW_TYPE_NORMAL = 0, // 普通排管
  PIPE_ROW_TYPE_PULL = 1    // 拉管
};

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
  double topThickness;
  double bottomThickness;
  double outerWallThickness;
  double innerWallThickness;
  double arcHeight;
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
  double arcHeight;
  double wallThickness;
  int pipeCount;
  pnt2d_t *pipePositions;
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
  double bottomThickness;
} sump_params_t;

PRIMCAPICALL topo_shape_t *create_sump(sump_params_t params);
PRIMCAPICALL topo_shape_t *create_sump_with_place(sump_params_t params,
                                                  pnt3d_t position,
                                                  dir3d_t normal, dir3d_t xDir);

typedef struct {
  double height;
  double width;
  channel_point_t *points;
  int pointCount;
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
  double topThickness;
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
  double width;     // 隔板宽 W (mm)
  double thickness; // 隔板厚 T (mm)
} tunnel_compartment_partition_params_t;

PRIMCAPICALL topo_shape_t *create_tunnel_compartment_partition(
    tunnel_compartment_partition_params_t params);
PRIMCAPICALL topo_shape_t *create_tunnel_compartment_partition_with_place(
    tunnel_compartment_partition_params_t params, pnt3d_t position,
    dir3d_t normal, dir3d_t xDir);

enum {
  TUNNEL_PARTITION_STYLE_CIRCULAR = 1,   // 圆形
  TUNNEL_PARTITION_STYLE_RECTANGULAR = 2 // 方形
};

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
  double bottomThickness;
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
  double width;
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

// 剖面类型枚举
typedef enum {
  PROFILE_TYPE_NONE = 0,
  PROFILE_TYPE_TRIANGLE,
  PROFILE_TYPE_RECTANGLE,
  PROFILE_TYPE_CIRC,
  PROFILE_TYPE_ELIPS,
  PROFILE_TYPE_POLYGON
} profile_type_t;

// 三角形剖面
typedef struct {
  pnt3d_t p1;
  pnt3d_t p2;
  pnt3d_t p3;
} triangle_profile_t;

// 矩形剖面
typedef struct {
  pnt3d_t p1;
  pnt3d_t p2;
} rectangle_profile_t;

// 圆形剖面
typedef struct {
  pnt3d_t center;
  dir3d_t norm;
  double radius;
} circ_profile_t;

// 椭圆剖面
typedef struct {
  pnt3d_t s1;
  pnt3d_t s2;
  pnt3d_t center;
} elips_profile_t;

// 多边形剖面
typedef struct {
  pnt3d_t *edges;
  int edgeCount;
  pnt3d_t **inners;
  int *innerCounts;
  int innerArrayCount;
} polygon_profile_t;

// 剖面结构体
typedef struct {
  profile_type_t type_;
  triangle_profile_t triangle;
  rectangle_profile_t rectangle;
  circ_profile_t circ;
  elips_profile_t elips;
  polygon_profile_t polygon;
} shape_profile_t;

// 旋转参数
typedef struct {
  shape_profile_t profile;
  axis1_t axis;
  double angle;
} revol_params_t;

PRIMCAPICALL topo_shape_t *create_revol(revol_params_t params);
PRIMCAPICALL topo_shape_t *create_revol_with_place(revol_params_t params,
                                                   pnt3d_t position,
                                                   dir3d_t direction,
                                                   dir3d_t xDir);

// 拉伸参数
typedef struct {
  shape_profile_t profile;
  dir3d_t direction;
  double height;
} prism_params_t;

PRIMCAPICALL topo_shape_t *create_prism(prism_params_t params);
PRIMCAPICALL topo_shape_t *create_prism_with_place(prism_params_t params,
                                                   pnt3d_t position,
                                                   dir3d_t direction,
                                                   dir3d_t xDir);
// 线段类型枚举
typedef enum {
  SEGMENT_TYPE_LINE = 0,              // 直线
  SEGMENT_TYPE_THREE_POINT_ARC = 1,   // 弧线
  SEGMENT_TYPE_CIRCLE_CENTER_ARC = 2, // 圆心角
  SEGMENT_TYPE_SPLINE = 3,            // 样条曲线
  SEGMENT_TYPE_BEZIER = 4             // 贝塞尔曲线
} segment_type_t;

PRIMCAPICALL pnt3d_t *
sample_segment_points(const pnt3d_t *wires, const int *wire_counts,
                      int wire_array_count, const segment_type_t *segments,
                      int segment_count, double tessellation, int *out_count);

// 管道端点参数
typedef struct {
  char *id;
  pnt3d_t offset;
  dir3d_t normal;
  shape_profile_t profile;
  shape_profile_t *inner_profile; // 可为NULL
} pipe_endpoint_t;

// 连接形状模式枚举
typedef enum {
  JOINT_SHAPE_MODE_SPHERE = 0,
  JOINT_SHAPE_MODE_BOX = 1,
  JOINT_SHAPE_MODE_CYLINDER = 2,
} joint_shape_mode_t;

// 管道参数
typedef struct {
  pnt3d_t *wire;
  int wire_count;
  shape_profile_t *profiles;
  int profile_count;
  shape_profile_t **inner_profiles; // 可为NULL
  int *inner_profile_counts;
  segment_type_t segment_type;
  transition_mode_t transition_mode;
  dir3d_t *up_dir;
} pipe_params_t;

// 创建管道
PRIMCAPICALL topo_shape_t *create_pipe(pipe_params_t params);
PRIMCAPICALL topo_shape_t *
create_pipe_with_split_distances(pipe_params_t params, double start_distance,
                                 double end_distance);
PRIMCAPICALL topo_wire_t create_pipe_centerline(pipe_params_t params);
PRIMCAPICALL topo_shape_t *create_pipe_with_place(pipe_params_t params,
                                                  pnt3d_t position,
                                                  dir3d_t direction,
                                                  dir3d_t xDir);
// 多段管道参数
typedef struct {
  pnt3d_t **wires;
  int *wire_counts;
  int wire_array_count;
  shape_profile_t *profiles;
  int profile_count;
  shape_profile_t **inner_profiles; // 可为NULL
  int *inner_profile_counts;
  segment_type_t *segment_types;
  int segment_type_count;
  transition_mode_t transition_mode;
  dir3d_t *up_dir;
} multi_segment_pipe_params_t;

// 创建多段管道
PRIMCAPICALL topo_shape_t *
create_multi_segment_pipe(multi_segment_pipe_params_t params);
PRIMCAPICALL topo_shape_t *create_multi_segment_pipe_with_split_distances(
    multi_segment_pipe_params_t params, double start_distance,
    double end_distance);
PRIMCAPICALL topo_wire_t
create_multi_segment_pipe_centerline(multi_segment_pipe_params_t params);
PRIMCAPICALL topo_shape_t *
create_multi_segment_pipe_with_place(multi_segment_pipe_params_t params,
                                     pnt3d_t position, dir3d_t direction,
                                     dir3d_t xDir);

typedef struct {
  char *name;
  shape_profile_t *profiles;
  int profile_count;
  shape_profile_t *inner_profiles;
  int inner_profile_count;
} profile_layer_t;

typedef struct {
  pnt3d_t **wires;
  int *wire_counts;
  int wire_array_count;
  segment_type_t *segment_types;
  int segment_type_count;
  profile_layer_t *layers;
  int layer_count;
  int transition_mode;
  dir3d_t *upDir;
} multi_layer_extrusion_structure_params_t;

PRIMCAPICALL topo_shape_t **create_multi_layer_extrusion_structure(
    multi_layer_extrusion_structure_params_t params, int *out_count);
PRIMCAPICALL topo_wire_t create_multi_layer_extrusion_structure_centerline(
    multi_layer_extrusion_structure_params_t params);
PRIMCAPICALL topo_shape_t **create_multi_layer_extrusion_structure_with_place(
    multi_layer_extrusion_structure_params_t params, pnt3d_t position,
    dir3d_t direction, dir3d_t xDir, int *out_count);

// 管道连接参数
typedef struct {
  pipe_endpoint_t *ins;
  int in_count;
  pipe_endpoint_t *outs;
  int out_count;
  joint_shape_mode_t mode;
  bool flanged;
  dir3d_t *up_dir;
} pipe_joint_params_t;

// 创建管道连接
PRIMCAPICALL topo_shape_t *create_pipe_joint(pipe_joint_params_t params);
PRIMCAPICALL topo_shape_t *
create_pipe_joint_with_place(pipe_joint_params_t params, pnt3d_t position,
                             dir3d_t direction, dir3d_t xDir);

// 悬链线参数
typedef struct {
  pnt3d_t p1;
  pnt3d_t p2;
  shape_profile_t profile;
  double slack;
  double max_sag;
  double tessellation;
  dir3d_t *up_dir;
} catenary_params_t;

// 创建悬链线
PRIMCAPICALL topo_shape_t *create_catenary(catenary_params_t params);
PRIMCAPICALL topo_shape_t *create_catenary_with_place(catenary_params_t params,
                                                      pnt3d_t position,
                                                      dir3d_t direction,
                                                      dir3d_t xDir);

// 长方体参数
typedef struct {
  pnt3d_t point1;
  pnt3d_t point2;
} box_shape_params_t;

PRIMCAPICALL topo_shape_t *create_box_shape(box_shape_params_t params);
PRIMCAPICALL topo_shape_t *
create_box_shape_with_place(box_shape_params_t params, pnt3d_t position,
                            dir3d_t direction, dir3d_t xDir);

// 圆锥参数
typedef struct {
  double radius1;
  double radius2;
  double height;
  double *angle; // 可为NULL
} cone_shape_params_t;

PRIMCAPICALL topo_shape_t *create_cone_shape(cone_shape_params_t params);
PRIMCAPICALL topo_shape_t *
create_cone_shape_with_place(cone_shape_params_t params, pnt3d_t position,
                             dir3d_t direction, dir3d_t xDir);

// 圆柱参数
typedef struct {
  double radius;
  double height;
  double *angle; // 可为NULL
} cylinder_shape_params_t;

PRIMCAPICALL topo_shape_t *
create_cylinder_shape(cylinder_shape_params_t params);
PRIMCAPICALL topo_shape_t *
create_cylinder_shape_with_place(cylinder_shape_params_t params,
                                 pnt3d_t position, dir3d_t direction,
                                 dir3d_t xDir);

// 旋转体参数
typedef struct {
  pnt3d_t *meridian;
  int meridian_count;
  double *angle; // 可为NULL
  double *max;   // 可为NULL
  double *min;   // 可为NULL
} revolution_shape_params_t;

PRIMCAPICALL topo_shape_t *
create_revolution_shape(revolution_shape_params_t params);
PRIMCAPICALL topo_shape_t *
create_revolution_shape_with_place(revolution_shape_params_t params,
                                   pnt3d_t position, dir3d_t direction,
                                   dir3d_t xDir);

// 球体参数
typedef struct {
  pnt3d_t *center; // 可为NULL
  double radius;
  double *angle1; // 可为NULL
  double *angle2; // 可为NULL
  double *angle;  // 可为NULL
} sphere_shape_params_t;

PRIMCAPICALL topo_shape_t *create_sphere_shape(sphere_shape_params_t params);
PRIMCAPICALL topo_shape_t *
create_sphere_shape_with_place(sphere_shape_params_t params, pnt3d_t position,
                               dir3d_t direction, dir3d_t xDir);

// 圆环参数
typedef struct {
  double radius1;
  double radius2;
  double *angle1; // 可为NULL
  double *angle2; // 可为NULL
  double *angle;  // 可为NULL
} torus_shape_params_t;

PRIMCAPICALL topo_shape_t *create_torus_shape(torus_shape_params_t params);
PRIMCAPICALL topo_shape_t *
create_torus_shape_with_place(torus_shape_params_t params, pnt3d_t position,
                              dir3d_t direction, dir3d_t xDir);

// 楔形面限制
typedef struct {
  double values[4];
} wedge_face_limit_t;

// 楔形体参数
typedef struct {
  pnt3d_t edge;
  wedge_face_limit_t *limit; // 可为NULL
  double *ltx;               // 可为NULL
} wedge_shape_params_t;

PRIMCAPICALL topo_shape_t *create_wedge_shape(wedge_shape_params_t params);
PRIMCAPICALL topo_shape_t *
create_wedge_shape_with_place(wedge_shape_params_t params, pnt3d_t position,
                              dir3d_t direction, dir3d_t xDir);

// 管道参数
typedef struct {
  pnt3d_t wire[2];
  shape_profile_t profile;
  dir3d_t *up_dir;
} pipe_shape_params_t;

PRIMCAPICALL topo_shape_t *create_pipe_shape(pipe_shape_params_t params);
PRIMCAPICALL topo_shape_t *
create_pipe_shape_with_place(pipe_shape_params_t params, pnt3d_t position,
                             dir3d_t direction, dir3d_t xDir);

typedef struct {
  char *name;
  char *step;
} step_shape_params_t;

PRIMCAPICALL topo_shape_t *create_step_shape(step_shape_params_t params);
PRIMCAPICALL topo_shape_t *
create_step_shape_with_place(step_shape_params_t params, pnt3d_t position,
                             dir3d_t direction, dir3d_t xDir);

typedef struct {
  char *name;
  double depth_from;
  double depth_to;
} borehole_sample_t;

typedef struct {
  borehole_sample_t *samples;
  int sample_count;
  double diameter;
} borehole_params_t;

PRIMCAPICALL topo_shape_t **create_borehole(borehole_params_t params,
                                            int *out_count);
PRIMCAPICALL void free_borehole_results(topo_shape_t **results, int count);

#ifdef __cplusplus
}
#endif

#endif
