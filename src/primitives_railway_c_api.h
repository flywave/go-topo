#ifndef GO_RAILWAY_C_API_H
#define GO_RAILWAY_C_API_H

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define RAILCAPICALL __declspec(dllexport)
#else
#define RAILCAPICALL
#endif

#include "standard_c_api.h"
#include "topo_c_api.h"

#ifdef __cplusplus
extern "C" {
#endif

// ===========================================================================
// 1. Contact Wire (接触线)
// ===========================================================================
typedef struct {
  double sectionalArea;
  double diameter;
  double ratedTension;
  double grooveDepth;
  double grooveWidth;
  double bottomRadius;
  double topRadius;
} contact_wire_params_t;

RAILCAPICALL topo_shape_t *
create_contact_wire(contact_wire_params_t params, pnt3d_t startPoint,
                    pnt3d_t endPoint);

// ===========================================================================
// 2. Messenger Wire (承力索)
// ===========================================================================
typedef struct {
  double diameter;
  double ratedTension;
  double structuralHeight;
} messenger_wire_params_t;

RAILCAPICALL topo_shape_t *
create_messenger_wire(messenger_wire_params_t params, pnt3d_t startPoint,
                      pnt3d_t endPoint);

// ===========================================================================
// 3. Cross Arm (横担)
// ===========================================================================
typedef struct {
  int ctype;              // cross_arm_type
  double beamLength;
  double beamHeight;
  double beamWidth;
  double beamThickness;
  double braceLength;
  double braceDiameter;
  double mountHeight;
  double boltSpacing;
  double boltDiameter;
  int boltCount;
} cross_arm_params_t;

RAILCAPICALL topo_shape_t *create_cross_arm(cross_arm_params_t params);
RAILCAPICALL topo_shape_t *create_cross_arm_with_place(cross_arm_params_t params,
                                                       pnt3d_t position,
                                                       dir3d_t normal,
                                                       dir3d_t xDir);

// ===========================================================================
// 4. Level Cantilever (平腕臂)
// ===========================================================================
typedef struct {
  double length;
  double outerDiameter;
  double wallThickness;
  double mountHeight;
  double riseAngle;
} level_cantilever_params_t;

RAILCAPICALL topo_shape_t *
create_level_cantilever(level_cantilever_params_t params);
RAILCAPICALL topo_shape_t *
create_level_cantilever_with_place(level_cantilever_params_t params,
                                   pnt3d_t basePoint, dir3d_t axisDir,
                                   dir3d_t upDir);

// ===========================================================================
// 5. Slanted Cantilever (斜腕臂)
// ===========================================================================
typedef struct {
  double length;
  double outerDiameter;
  double wallThickness;
  double slantAngle;
} slant_cantilever_params_t;

RAILCAPICALL topo_shape_t *
create_slant_cantilever(slant_cantilever_params_t params);
RAILCAPICALL topo_shape_t *
create_slant_cantilever_with_place(slant_cantilever_params_t params,
                                   pnt3d_t basePoint, dir3d_t axisDir,
                                   dir3d_t upDir);

// ===========================================================================
// 6. Curved Arm (弯臂)
// ===========================================================================
typedef struct {
  int ctype;               // curved_arm_type
  double verticalLength;
  double horizontalLength;
  double bendRadius;
  double bendAngle;
  double outerDiameter;
  double wallThickness;
  double flangeThickness;
  double boltSpacing;
  double boltDiameter;
} curved_arm_params_t;

RAILCAPICALL topo_shape_t *create_curved_arm(curved_arm_params_t params);
RAILCAPICALL topo_shape_t *
create_curved_arm_with_place(curved_arm_params_t params, pnt3d_t position,
                             dir3d_t normal, dir3d_t xDir);

// ===========================================================================
// 7. Rod Insulator (棒式绝缘子)
// ===========================================================================
typedef struct {
  int ctype;               // rod_insulator_type
  double height;
  double outerDiameter;
  double innerDiameter;
  double shedDiameter;
  double shedSpacing;
  int shedCount;
  int endFitting;          // end_fitting_type
  double flangeDiameter;
  double flangeBoltSpacing;
  double flangeBoltDiameter;
} rod_insulator_params_t;

RAILCAPICALL topo_shape_t *
create_rod_insulator(rod_insulator_params_t params);
RAILCAPICALL topo_shape_t *
create_rod_insulator_with_place(rod_insulator_params_t params, pnt3d_t basePoint,
                                dir3d_t axisDir);

// ===========================================================================
// 8. Mast Bracket (支柱连接座)
// ===========================================================================
typedef struct {
  double boltSpacing;
  double boltDiameter;
  double height;
  double width;
  double thickness;
  double insulatorBoltSpacing;
  double insulatorBoltDiameter;
  double mountAngle;
} mast_bracket_params_t;

RAILCAPICALL topo_shape_t *create_mast_bracket(mast_bracket_params_t params);
RAILCAPICALL topo_shape_t *
create_mast_bracket_with_place(mast_bracket_params_t params, pnt3d_t position,
                               dir3d_t normal, dir3d_t upDir);

// ===========================================================================
// 9. Registration Arm (定位器)
// ===========================================================================
typedef struct {
  int ctype;               // registration_arm_type
  double length;
  double outerDiameter;
  double wallThickness;
  double angle;
} registration_arm_params_t;

RAILCAPICALL topo_shape_t *
create_registration_arm(registration_arm_params_t params);
RAILCAPICALL topo_shape_t *
create_registration_arm_with_place(registration_arm_params_t params,
                                   pnt3d_t basePoint, dir3d_t axisDir,
                                   dir3d_t upDir);

// ===========================================================================
// 10. Guy Wire (下锚拉线)
// ===========================================================================
typedef struct {
  double length;
  double diameter;
  double angle;
  double ratedTension;
  bool hasInsulator;
  double anchorRodDiameter;
  double anchorRodLength;
  double anchorPlateLength;
  double anchorPlateWidth;
} guy_wire_params_t;

RAILCAPICALL topo_shape_t *create_guy_wire(guy_wire_params_t params);
RAILCAPICALL topo_shape_t *create_guy_wire_with_place(guy_wire_params_t params,
                                                      pnt3d_t anchorPoint,
                                                      pnt3d_t mastPoint,
                                                      dir3d_t upDir);

// ===========================================================================
// 11. Steel Mast (钢支柱)
// ===========================================================================
typedef struct {
  int ctype;               // steel_mast_type
  double height;
  double topWidth;
  double bottomWidth;
  double wallThickness;
  double flangeThickness;
  double flangeWidth;
  double anchorSpacing;
  double anchorDiameter;
  int segmentCount;
} steel_mast_params_t;

RAILCAPICALL topo_shape_t *create_steel_mast(steel_mast_params_t params);
RAILCAPICALL topo_shape_t *
create_steel_mast_with_place(steel_mast_params_t params, pnt3d_t baseCenter,
                             dir3d_t axisDir);

// ===========================================================================
// 12. Concrete Mast (混凝土支柱)
// ===========================================================================
typedef struct {
  int sectionType;         // concrete_mast_section_type
  double height;
  double topWidth;
  double bottomWidth;
  double wallThickness;
  double holeDiameter;
  double holeSpacingV;
  double holeSpacingH;
  double firstHoleOffset;
  int holeRowCount;
  int holesPerRow;
} concrete_mast_params_t;

RAILCAPICALL topo_shape_t *create_concrete_mast(concrete_mast_params_t params);
RAILCAPICALL topo_shape_t *
create_concrete_mast_with_place(concrete_mast_params_t params, pnt3d_t baseCenter,
                                dir3d_t axisDir);

// ===========================================================================
// 13. OCS Foundation (支柱基础)
// ===========================================================================
typedef struct {
  int ctype;               // foundation_type
  double height;
  double width;
  double length;
  double flangeThickness;
  int anchorCount;
  double anchorDiameter;
  double anchorLength;
  double anchorSpacing;
} ocs_foundation_params_t;

RAILCAPICALL topo_shape_t *
create_ocs_foundation(ocs_foundation_params_t params);
RAILCAPICALL topo_shape_t *
create_ocs_foundation_with_place(ocs_foundation_params_t params, pnt3d_t position,
                                 dir3d_t normal, dir3d_t xDir);

// ===========================================================================
// 14. Dropper (吊弦)
// ===========================================================================
typedef struct {
  double length;
  double wireDiameter;
  double clampLength;
  double clampWidth;
  double clampThickness;
  bool conductive;
} dropper_params_t;

RAILCAPICALL topo_shape_t *create_dropper(dropper_params_t params);
RAILCAPICALL topo_shape_t *create_dropper_with_place(dropper_params_t params,
                                                      pnt3d_t topPoint,
                                                      dir3d_t direction);

// ===========================================================================
// 15. Cantilever Base (腕臂底座)
// ===========================================================================
typedef struct {
  double length;
  double width;
  double height;
  double boltSpacing;
  double boltDiameter;
  int boltCount;
} cantilever_base_params_t;

RAILCAPICALL topo_shape_t *
create_cantilever_base(cantilever_base_params_t params);
RAILCAPICALL topo_shape_t *
create_cantilever_base_with_place(cantilever_base_params_t params, pnt3d_t position,
                                  dir3d_t normal, dir3d_t upDir);

// ===========================================================================
// 16. Messenger Wire Saddle (承力索座)
// ===========================================================================
typedef struct {
  double length;
  double width;
  double height;
  double grooveRadius;
  double boltDiameter;
} mw_saddle_params_t;

RAILCAPICALL topo_shape_t *create_mw_saddle(mw_saddle_params_t params);
RAILCAPICALL topo_shape_t *create_mw_saddle_with_place(mw_saddle_params_t params,
                                                       pnt3d_t position,
                                                       dir3d_t normal,
                                                       dir3d_t xDir);

// ===========================================================================
// 17. Balance Weight (坠砣)
// ===========================================================================
typedef struct {
  double width;
  double thickness;
  double height;
  double centerHoleDiameter;
} balance_weight_params_t;

RAILCAPICALL topo_shape_t *
create_balance_weight(balance_weight_params_t params);
RAILCAPICALL topo_shape_t *
create_balance_weight_with_place(balance_weight_params_t params, pnt3d_t position,
                                 dir3d_t normal, dir3d_t xDir);

// ===========================================================================
// 18. Weight Rod (坠砣杆)
// ===========================================================================
typedef struct {
  double rodDiameter;
  double rodLength;
  double topHoleDiameter;
} weight_rod_params_t;

RAILCAPICALL topo_shape_t *create_weight_rod(weight_rod_params_t params);
RAILCAPICALL topo_shape_t *create_weight_rod_with_place(weight_rod_params_t params,
                                                        pnt3d_t position,
                                                        dir3d_t axisDir);

// ===========================================================================
// 19. Anchor Fitting (下锚金具)
// ===========================================================================
typedef struct {
  int ctype;          // anchor_fitting_type
  double length;
  double diameter;
} anchor_fitting_params_t;

RAILCAPICALL topo_shape_t *
create_anchor_fitting(anchor_fitting_params_t params);
RAILCAPICALL topo_shape_t *
create_anchor_fitting_with_place(anchor_fitting_params_t params, pnt3d_t position,
                                  dir3d_t direction, dir3d_t upDir);

// ===========================================================================
// 20. Crossing (线岔)
// ===========================================================================
typedef struct {
  double limitPipeLength;
  double pipeDiameter;
  double wireDiameter;
  double heightDiff;
} crossing_params_t;

RAILCAPICALL topo_shape_t *create_crossing(crossing_params_t params);
RAILCAPICALL topo_shape_t *create_crossing_with_place(crossing_params_t params,
                                                      pnt3d_t crossPoint,
                                                      dir3d_t mainDir,
                                                      dir3d_t branchDir);

// ===========================================================================
// 21. Head Span (软横跨)
// ===========================================================================
typedef struct {
  double span;
  int hangPointCount;
  double hangPointSpacing;
  double crossCatenaryDiameter;
  double crossCatenarySag;
  double upperRopeDiameter;
  double lowerRopeDiameter;
  double insulatorLength;
} head_span_params_t;

RAILCAPICALL topo_shape_t *create_head_span(head_span_params_t params);
RAILCAPICALL topo_shape_t *create_head_span_with_place(head_span_params_t params,
                                                       pnt3d_t leftMast,
                                                       pnt3d_t rightMast,
                                                       dir3d_t upDir);

// ===========================================================================
// 22. Transverse Span (硬横跨)
// ===========================================================================
typedef struct {
  double span;
  int beamType;          // beam_section_type
  double beamHeight;
  double beamWidth;
  double beamThickness;
  double mastHeight;
  double mastWidth;
} transverse_span_params_t;

RAILCAPICALL topo_shape_t *
create_transverse_span(transverse_span_params_t params);
RAILCAPICALL topo_shape_t *
 create_transverse_span_with_place(transverse_span_params_t params, pnt3d_t position,
                                    dir3d_t direction, dir3d_t upDir);

// ===========================================================================
// 22b. Hanger Post (硬横跨吊柱)
// ===========================================================================
typedef struct {
  int sectionType;         // hanger_post_section_type
  double length;
  double sectionSize;
  double wallThickness;
  double topFlangeSize;
  double topFlangeThick;
  double bottomFlangeSize;
  double bottomFlangeThick;
  double boltDiameter;
  double boltSpacing;
} hanger_post_params_t;

RAILCAPICALL topo_shape_t *create_hanger_post(hanger_post_params_t params);
RAILCAPICALL topo_shape_t *create_hanger_post_with_place(hanger_post_params_t params,
                                                         pnt3d_t position,
                                                         dir3d_t direction);

// ===========================================================================
// 22c. Portal Frame (梁顶门型架)
// ===========================================================================
typedef struct {
  double frameHeight;
  double frameWidth;
  double postDiameter;
  double postWallThick;
  double beamDiameter;
  double beamWallThick;
  double beamLength;
  double basePlateLength;
  double basePlateWidth;
  double basePlateThick;
  int hangPointCount;
  double hangPointSpacing;
  double boltSpacing;
  double boltDiameter;
} portal_frame_params_t;

RAILCAPICALL topo_shape_t *create_portal_frame(portal_frame_params_t params);
RAILCAPICALL topo_shape_t *create_portal_frame_with_place(portal_frame_params_t params,
                                                          pnt3d_t position,
                                                          dir3d_t direction,
                                                          dir3d_t upDir);

// ===========================================================================
// 22e. Suspension Hard Span (悬索式硬横跨)
// ===========================================================================
typedef struct {
  double span;
  double mastHeight;
  double mastWidth;
  double cableDiameter;
  double cableSag;
  double dropperCableDiameter;
  int dropperCount;
  double dropperSpacing;
  double insulatorLength;
  double insulatorDiameter;
} suspension_hard_span_params_t;

RAILCAPICALL topo_shape_t *
create_suspension_hard_span(suspension_hard_span_params_t params);
RAILCAPICALL topo_shape_t *
create_suspension_hard_span_with_place(suspension_hard_span_params_t params,
                                        pnt3d_t position,
                                        dir3d_t direction,
                                        dir3d_t upDir);

// ===========================================================================
// 22f. Positioning Cable (定位索)
// ===========================================================================
typedef struct {
  double diameter;
  pnt3d_t topPoint;
  pnt3d_t bottomPoint;
  bool adjustable;
} positioning_cable_params_t;

RAILCAPICALL topo_shape_t *
create_positioning_cable(positioning_cable_params_t params);

// ===========================================================================
// 23. Auxiliary Bracket (附加导线安装支架)
// ===========================================================================
typedef struct {
  int ctype;             // aux_bracket_type
  double mountHeight;
  double overhangLength;
  double bracketLength;
  double bracketWidth;
  double boltSpacing;
  double boltDiameter;
} aux_bracket_params_t;

RAILCAPICALL topo_shape_t *create_aux_bracket(aux_bracket_params_t params);
RAILCAPICALL topo_shape_t *create_aux_bracket_with_place(aux_bracket_params_t params,
                                                         pnt3d_t position,
                                                         dir3d_t normal,
                                                         dir3d_t upDir);

// ===========================================================================
// 24. Rail (钢轨)
// ===========================================================================
typedef struct {
  double railHeight;
  double headWidth;
  double baseWidth;
  double webThickness;
  double headHeight;
  double baseHeight;
  double headRadius;
  double standardLength;
} rail_params_t;

RAILCAPICALL topo_shape_t *create_rail(rail_params_t params);
RAILCAPICALL topo_shape_t *create_rail_with_place(rail_params_t params,
                                                  pnt3d_t startPoint,
                                                  pnt3d_t endPoint);

// ===========================================================================
// 25. Sleeper (轨枕)
// ===========================================================================
typedef struct {
  double length;
  double width;
  double height;
  double gauge;
  double grooveDepth;
  double spacing;
} sleeper_params_t;

RAILCAPICALL topo_shape_t *create_sleeper(sleeper_params_t params);
RAILCAPICALL topo_shape_t *create_sleeper_with_place(sleeper_params_t params,
                                                     pnt3d_t position,
                                                     dir3d_t direction,
                                                     dir3d_t upDir);

// ===========================================================================
// 26. Ballast (道床)
// ===========================================================================
typedef struct {
  double topWidth;
  double thickness;
  double sideSlope;
  pnt3d_t *centerline;
  int pointCount;
} ballast_params_t;

RAILCAPICALL topo_shape_t *create_ballast(ballast_params_t params);

// ===========================================================================
// 27. Track Slab (轨道板)
// ===========================================================================
typedef struct {
  double length;
  double width;
  double thickness;
  int railSeatCount;
  double railSeatSpacing;
  double cementAsphaltThickness;
} track_slab_params_t;

RAILCAPICALL topo_shape_t *create_track_slab(track_slab_params_t params);
RAILCAPICALL topo_shape_t *create_track_slab_with_place(track_slab_params_t params,
                                                        pnt3d_t position,
                                                        dir3d_t direction,
                                                        dir3d_t upDir);

// ===========================================================================
// 28. Fastener (扣件)
// ===========================================================================
typedef struct {
  double spacing;
  double gauge;
  double padThickness;
  double padLength;
  double padWidth;
} fastener_params_t;

RAILCAPICALL topo_shape_t *create_fastener(fastener_params_t params);
RAILCAPICALL topo_shape_t *create_fastener_with_place(fastener_params_t params,
                                                      pnt3d_t position,
                                                      dir3d_t direction,
                                                      dir3d_t upDir);

// ===========================================================================
// 29. Guard Rail (护轨)
// ===========================================================================
typedef struct {
  double height;
  double headWidth;
  double baseWidth;
  double grooveWidth;
  double totalLength;
  double gaugeDistance;
} guard_rail_params_t;

RAILCAPICALL topo_shape_t *create_guard_rail(guard_rail_params_t params);
RAILCAPICALL topo_shape_t *create_guard_rail_with_place(guard_rail_params_t params,
                                                        pnt3d_t startPoint,
                                                        pnt3d_t endPoint);

// ===========================================================================
// 30. Mast Assembly (支柱装配)
// ===========================================================================
typedef struct {
  int mastType;
  double mastHeight;
  int cantileverType;
  bool hasCrossArm;
  double armDiameter;
  double stagger;
  int compType;
  double ratedTension;
  bool hasGuyWire;
} mast_assembly_params_t;

RAILCAPICALL topo_shape_t *
create_mast_assembly(mast_assembly_params_t params);
RAILCAPICALL topo_shape_t *
create_mast_assembly_with_place(mast_assembly_params_t params, pnt3d_t position,
                                dir3d_t direction, dir3d_t upDir);

// ===========================================================================
// 31. Switch Rail (尖轨)
// ===========================================================================
typedef struct {
  double length;
  double railHeight;
  double railHeadWidth;
  double railBaseWidth;
  double tipWidth;
  double curveRadius;
  bool isLeftHand;
} switch_rail_params_t;

RAILCAPICALL topo_shape_t *create_switch_rail(switch_rail_params_t params);
RAILCAPICALL topo_shape_t *create_switch_rail_with_place(switch_rail_params_t params,
                                                          pnt3d_t position,
                                                          dir3d_t direction,
                                                          dir3d_t upDir);

// ===========================================================================
// 32. Frog (辙叉)
// ===========================================================================
typedef struct {
  int turnoutNo;
  double gauge;
  double railHeight;
  double railHeadWidth;
  double railBaseWidth;
} frog_params_t;

RAILCAPICALL topo_shape_t *create_frog(frog_params_t params);
RAILCAPICALL topo_shape_t *create_frog_with_place(frog_params_t params,
                                                   pnt3d_t position,
                                                   dir3d_t direction,
                                                   dir3d_t upDir);

// ===========================================================================
// 33. Turnout (单开道岔)
// ===========================================================================
typedef struct {
  int turnoutNo;
  bool isLeftHand;
  double gauge;
  double railHeight;
  double railHeadWidth;
  double railBaseWidth;
  double switchRailLength;
  double leadCurveRadius;
  double frogLength;
  int sleeperCount;
  double sleeperSpacing;
} turnout_params_t;

RAILCAPICALL topo_shape_t *create_turnout(turnout_params_t params);
RAILCAPICALL topo_shape_t *create_turnout_with_place(turnout_params_t params,
                                                       pnt3d_t position,
                                                       dir3d_t direction,
                                                       dir3d_t upDir);

// ===========================================================================
// 35. Rail Pair (轨排对)
// ===========================================================================
typedef struct { pnt3d_t *centerline; int pointCount; double gauge;
  double superElevation; double railHeight; double railHeadWidth; double railBaseWidth;
} rail_pair_params_t;
RAILCAPICALL topo_shape_t *create_rail_pair(rail_pair_params_t params);
RAILCAPICALL topo_shape_t *create_rail_pair_with_place(rail_pair_params_t params,
                                                        pnt3d_t position, dir3d_t direction, dir3d_t upDir);

// ===========================================================================
// 36. Sleeper Layout (轨枕阵列)
// ===========================================================================
typedef struct { pnt3d_t *centerline; int pointCount; double length;
  double width; double height; double spacing; double gauge;
} sleeper_layout_params_t;
RAILCAPICALL topo_shape_t *create_sleeper_layout(sleeper_layout_params_t params);

// ===========================================================================
// 37. Straight Track (直线轨道段)
// ===========================================================================
typedef struct { pnt3d_t startPoint; pnt3d_t endPoint; double gauge;
  double railHeight; double railHeadWidth; double railBaseWidth;
  double sleeperLength; double sleeperWidth; double sleeperHeight; double sleeperSpacing;
  double ballastTopWidth; double ballastThickness; double ballastSlope;
} straight_track_params_t;
RAILCAPICALL topo_shape_t *create_straight_track(straight_track_params_t params);
RAILCAPICALL topo_shape_t *create_straight_track_with_place(straight_track_params_t params,
                                                             pnt3d_t position, dir3d_t direction, dir3d_t upDir);

// ===========================================================================
// 38. Curve Track (曲线轨道段)
// ===========================================================================
typedef struct { pnt3d_t curveCenter; double startAngle; double sweepAngle; double curveRadius;
  double gauge; double superElevation; double railHeight; double railHeadWidth; double railBaseWidth;
  double sleeperLength; double sleeperWidth; double sleeperHeight; double sleeperSpacing;
  double ballastTopWidth; double ballastThickness; double ballastSlope;
} curve_track_params_t;
RAILCAPICALL topo_shape_t *create_curve_track(curve_track_params_t params);
RAILCAPICALL topo_shape_t *create_curve_track_with_place(curve_track_params_t params,
                                                          pnt3d_t position, dir3d_t direction, dir3d_t upDir);

#ifdef __cplusplus
}
#endif

#endif // GO_RAILWAY_C_API_H
