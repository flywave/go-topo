#include "primitives_railway_c_api.h"
#include "primitives_railway.hh"
#include "shape.hh"
#include "topo_impl.hh"

using namespace flywave::topo;

#ifdef __cplusplus
extern "C" {
#endif

// ===========================================================================
// 1. Contact Wire
// ===========================================================================
RAILCAPICALL topo_shape_t *
create_contact_wire(contact_wire_params_t params, pnt3d_t startPoint,
                    pnt3d_t endPoint) {
  contact_wire_params cpp_params{
      params.sectionalArea, params.diameter,       params.ratedTension,
      params.grooveDepth,   params.grooveWidth,    params.bottomRadius,
      params.topRadius};
  gp_Pnt cpp_start(startPoint.x, startPoint.y, startPoint.z);
  gp_Pnt cpp_end(endPoint.x, endPoint.y, endPoint.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_contact_wire(cpp_params, cpp_start, cpp_end))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 2. Messenger Wire
// ===========================================================================
RAILCAPICALL topo_shape_t *
create_messenger_wire(messenger_wire_params_t params, pnt3d_t startPoint,
                      pnt3d_t endPoint) {
  messenger_wire_params cpp_params{params.diameter, params.ratedTension,
                                    params.structuralHeight};
  gp_Pnt cpp_start(startPoint.x, startPoint.y, startPoint.z);
  gp_Pnt cpp_end(endPoint.x, endPoint.y, endPoint.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_messenger_wire(cpp_params, cpp_start, cpp_end))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 3. Cross Arm
// ===========================================================================
RAILCAPICALL topo_shape_t *create_cross_arm(cross_arm_params_t params) {
  cross_arm_params cpp_params{
      static_cast<cross_arm_type>(params.ctype),
      params.beamLength,    params.beamHeight,      params.beamWidth,
      params.beamThickness, params.beamSpacing, params.braceLength,     params.braceDiameter,
      params.mountHeight,   params.boltSpacing,     params.boltDiameter,
      params.boltCount};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cross_arm(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_cross_arm_with_place(cross_arm_params_t params, pnt3d_t position,
                            dir3d_t normal, dir3d_t xDir) {
  cross_arm_params cpp_params{
      static_cast<cross_arm_type>(params.ctype),
      params.beamLength,    params.beamHeight,      params.beamWidth,
      params.beamThickness, params.beamSpacing, params.braceLength,     params.braceDiameter,
      params.mountHeight,   params.boltSpacing,     params.boltDiameter,
      params.boltCount};
  gp_Pnt cpp_position(position.x, position.y, position.z);
  gp_Dir cpp_normal(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_cross_arm(cpp_params, cpp_position, cpp_normal, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 4. Level Cantilever
// ===========================================================================
RAILCAPICALL topo_shape_t *
create_level_cantilever(level_cantilever_params_t params) {
  level_cantilever_params cpp_params{params.length,   params.outerDiameter,
                                      params.wallThickness, params.mountHeight,
                                      params.riseAngle};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_level_cantilever(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_level_cantilever_with_place(level_cantilever_params_t params,
                                   pnt3d_t basePoint, dir3d_t axisDir,
                                   dir3d_t upDir) {
  level_cantilever_params cpp_params{params.length,   params.outerDiameter,
                                      params.wallThickness, params.mountHeight,
                                      params.riseAngle};
  gp_Pnt cpp_base(basePoint.x, basePoint.y, basePoint.z);
  gp_Dir cpp_axis(axisDir.x, axisDir.y, axisDir.z);
  gp_Dir cpp_up(upDir.x, upDir.y, upDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_level_cantilever(
            cpp_params, cpp_base, cpp_axis, cpp_up))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 5. Slanted Cantilever
// ===========================================================================
RAILCAPICALL topo_shape_t *
create_slant_cantilever(slant_cantilever_params_t params) {
  slant_cantilever_params cpp_params{params.length, params.outerDiameter,
                                      params.wallThickness, params.slantAngle};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_slant_cantilever(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_slant_cantilever_with_place(slant_cantilever_params_t params,
                                   pnt3d_t basePoint, dir3d_t axisDir,
                                   dir3d_t upDir) {
  slant_cantilever_params cpp_params{params.length, params.outerDiameter,
                                      params.wallThickness, params.slantAngle};
  gp_Pnt cpp_base(basePoint.x, basePoint.y, basePoint.z);
  gp_Dir cpp_axis(axisDir.x, axisDir.y, axisDir.z);
  gp_Dir cpp_up(upDir.x, upDir.y, upDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_slant_cantilever(
            cpp_params, cpp_base, cpp_axis, cpp_up))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 6. Curved Arm
// ===========================================================================
RAILCAPICALL topo_shape_t *create_curved_arm(curved_arm_params_t params) {
  curved_arm_params cpp_params{
      static_cast<curved_arm_type>(params.ctype),
      params.verticalLength,   params.horizontalLength, params.bendRadius,
      params.bendAngle,        params.outerDiameter,    params.wallThickness,
      params.flangeThickness,  params.boltSpacing,      params.boltDiameter};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_curved_arm(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_curved_arm_with_place(curved_arm_params_t params, pnt3d_t position,
                             dir3d_t normal, dir3d_t xDir) {
  curved_arm_params cpp_params{
      static_cast<curved_arm_type>(params.ctype),
      params.verticalLength,   params.horizontalLength, params.bendRadius,
      params.bendAngle,        params.outerDiameter,    params.wallThickness,
      params.flangeThickness,  params.boltSpacing,      params.boltDiameter};
  gp_Pnt cpp_pos(position.x, position.y, position.z);
  gp_Dir cpp_norm(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_curved_arm(cpp_params, cpp_pos, cpp_norm, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 7. Rod Insulator
// ===========================================================================
RAILCAPICALL topo_shape_t *
create_rod_insulator(rod_insulator_params_t params) {
  rod_insulator_params cpp_params{
      static_cast<rod_insulator_type>(params.ctype),
      params.height,           params.outerDiameter,
      params.innerDiameter,    params.shedDiameter,
      params.shedSpacing,      params.shedCount,
      static_cast<end_fitting_type>(params.endFitting),
      params.flangeDiameter,   params.flangeBoltSpacing,
      params.flangeBoltDiameter};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_rod_insulator(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_rod_insulator_with_place(rod_insulator_params_t params, pnt3d_t basePoint,
                                dir3d_t axisDir) {
  rod_insulator_params cpp_params{
      static_cast<rod_insulator_type>(params.ctype),
      params.height,           params.outerDiameter,
      params.innerDiameter,    params.shedDiameter,
      params.shedSpacing,      params.shedCount,
      static_cast<end_fitting_type>(params.endFitting),
      params.flangeDiameter,   params.flangeBoltSpacing,
      params.flangeBoltDiameter};
  gp_Pnt cpp_base(basePoint.x, basePoint.y, basePoint.z);
  gp_Dir cpp_axis(axisDir.x, axisDir.y, axisDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_rod_insulator(cpp_params, cpp_base, cpp_axis))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 8. Mast Bracket
// ===========================================================================
RAILCAPICALL topo_shape_t *create_mast_bracket(mast_bracket_params_t params) {
  mast_bracket_params cpp_params{
      params.boltSpacing,          params.boltDiameter,
      params.height,               params.width,
      params.thickness,            params.insulatorBoltSpacing,
      params.insulatorBoltDiameter, params.mountAngle};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_mast_bracket(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_mast_bracket_with_place(mast_bracket_params_t params, pnt3d_t position,
                               dir3d_t normal, dir3d_t upDir) {
  mast_bracket_params cpp_params{
      params.boltSpacing,          params.boltDiameter,
      params.height,               params.width,
      params.thickness,            params.insulatorBoltSpacing,
      params.insulatorBoltDiameter, params.mountAngle};
  gp_Pnt cpp_pos(position.x, position.y, position.z);
  gp_Dir cpp_norm(normal.x, normal.y, normal.z);
  gp_Dir cpp_up(upDir.x, upDir.y, upDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_mast_bracket(cpp_params, cpp_pos, cpp_norm, cpp_up))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 9. Registration Arm
// ===========================================================================
RAILCAPICALL topo_shape_t *
create_registration_arm(registration_arm_params_t params) {
  registration_arm_params cpp_params{
      static_cast<registration_arm_type>(params.ctype),
      params.length, params.tubeWidth, params.tubeHeight, params.wallThickness, params.angle, params.isReverse != 0};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_registration_arm(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_registration_arm_with_place(registration_arm_params_t params,
                                   pnt3d_t basePoint, dir3d_t axisDir,
                                   dir3d_t upDir) {
  registration_arm_params cpp_params{
      static_cast<registration_arm_type>(params.ctype),
      params.length, params.tubeWidth, params.tubeHeight, params.wallThickness, params.angle, params.isReverse != 0};
  gp_Pnt cpp_base(basePoint.x, basePoint.y, basePoint.z);
  gp_Dir cpp_axis(axisDir.x, axisDir.y, axisDir.z);
  gp_Dir cpp_up(upDir.x, upDir.y, upDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_registration_arm(
            cpp_params, cpp_base, cpp_axis, cpp_up))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 9b. Reg Arm Bracket
// ===========================================================================
RAILCAPICALL topo_shape_t *create_reg_arm_bracket(reg_arm_bracket_params_t params) {
  reg_arm_bracket_params p{params.tubeDiameter, params.bandWidth, params.bandThickness,
    params.bracketHeight, params.bracketThickness, params.bracketWidth, params.mountHoleDiameter};
  try { return new topo_shape_t{.shp = std::make_shared<shape>(create_reg_arm_bracket(p))}; } catch (...) { return nullptr; }
}
RAILCAPICALL topo_shape_t *create_reg_arm_bracket_with_place(reg_arm_bracket_params_t params,
    pnt3d_t position, dir3d_t tubeDir, dir3d_t upDir) {
  reg_arm_bracket_params p{params.tubeDiameter, params.bandWidth, params.bandThickness,
    params.bracketHeight, params.bracketThickness, params.bracketWidth, params.mountHoleDiameter};
  try { return new topo_shape_t{.shp = std::make_shared<shape>(create_reg_arm_bracket(p,
    gp_Pnt(position.x,position.y,position.z), gp_Dir(tubeDir.x,tubeDir.y,tubeDir.z),
    gp_Dir(upDir.x,upDir.y,upDir.z)))}; } catch (...) { return nullptr; }
}

// ===========================================================================
// 10. Guy Wire
// ===========================================================================
RAILCAPICALL topo_shape_t *create_guy_wire(guy_wire_params_t params) {
  guy_wire_params cpp_params{
      params.length,           params.diameter,
      params.angle,            params.ratedTension,
      params.hasInsulator != 0, params.anchorRodDiameter,
      params.anchorRodLength,  params.anchorPlateLength,
      params.anchorPlateWidth};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_guy_wire(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_guy_wire_with_place(guy_wire_params_t params, pnt3d_t anchorPoint,
                           pnt3d_t mastPoint, dir3d_t upDir) {
  guy_wire_params cpp_params{
      params.length,           params.diameter,
      params.angle,            params.ratedTension,
      params.hasInsulator != 0, params.anchorRodDiameter,
      params.anchorRodLength,  params.anchorPlateLength,
      params.anchorPlateWidth};
  gp_Pnt cpp_anchor(anchorPoint.x, anchorPoint.y, anchorPoint.z);
  gp_Pnt cpp_mast(mastPoint.x, mastPoint.y, mastPoint.z);
  gp_Dir cpp_up(upDir.x, upDir.y, upDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_guy_wire(cpp_params, cpp_anchor, cpp_mast, cpp_up))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 11. Steel Mast
// ===========================================================================
RAILCAPICALL topo_shape_t *create_steel_mast(steel_mast_params_t params) {
  steel_mast_params cpp_params{
      static_cast<steel_mast_type>(params.ctype),
      params.height,         params.topWidth,       params.bottomWidth,
      params.wallThickness,  params.flangeThickness, params.flangeWidth,
      params.anchorSpacing,  params.anchorDiameter,  params.segmentCount};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_steel_mast(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_steel_mast_with_place(steel_mast_params_t params, pnt3d_t baseCenter,
                             dir3d_t axisDir) {
  steel_mast_params cpp_params{
      static_cast<steel_mast_type>(params.ctype),
      params.height,         params.topWidth,       params.bottomWidth,
      params.wallThickness,  params.flangeThickness, params.flangeWidth,
      params.anchorSpacing,  params.anchorDiameter,  params.segmentCount};
  gp_Pnt cpp_center(baseCenter.x, baseCenter.y, baseCenter.z);
  gp_Dir cpp_axis(axisDir.x, axisDir.y, axisDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_steel_mast(cpp_params, cpp_center, cpp_axis))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 12. Concrete Mast
// ===========================================================================
RAILCAPICALL topo_shape_t *create_concrete_mast(concrete_mast_params_t params) {
  concrete_mast_params cpp_params{
      static_cast<concrete_mast_section_type>(params.sectionType),
      params.height,        params.topWidth,    params.bottomWidth,
      params.wallThickness, params.holeDiameter, params.holeSpacingV,
      params.holeSpacingH,  params.firstHoleOffset, params.holeRowCount,
      params.holesPerRow};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_concrete_mast(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_concrete_mast_with_place(concrete_mast_params_t params,
                                pnt3d_t baseCenter, dir3d_t axisDir) {
  concrete_mast_params cpp_params{
      static_cast<concrete_mast_section_type>(params.sectionType),
      params.height,        params.topWidth,    params.bottomWidth,
      params.wallThickness, params.holeDiameter, params.holeSpacingV,
      params.holeSpacingH,  params.firstHoleOffset, params.holeRowCount,
      params.holesPerRow};
  gp_Pnt cpp_center(baseCenter.x, baseCenter.y, baseCenter.z);
  gp_Dir cpp_axis(axisDir.x, axisDir.y, axisDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_concrete_mast(cpp_params, cpp_center, cpp_axis))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 13. OCS Foundation
// ===========================================================================
RAILCAPICALL topo_shape_t *
create_ocs_foundation(ocs_foundation_params_t params) {
  ocs_foundation_params cpp_params{
      static_cast<foundation_type>(params.ctype),
      params.height,          params.width,
      params.length,          params.flangeThickness,
      params.anchorCount,     params.anchorDiameter,
      params.anchorLength,    params.anchorSpacing};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_ocs_foundation(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_ocs_foundation_with_place(ocs_foundation_params_t params,
                                 pnt3d_t position, dir3d_t normal,
                                 dir3d_t xDir) {
  ocs_foundation_params cpp_params{
      static_cast<foundation_type>(params.ctype),
      params.height,          params.width,
      params.length,          params.flangeThickness,
      params.anchorCount,     params.anchorDiameter,
      params.anchorLength,    params.anchorSpacing};
  gp_Pnt cpp_pos(position.x, position.y, position.z);
  gp_Dir cpp_norm(normal.x, normal.y, normal.z);
  gp_Dir cpp_xDir(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_ocs_foundation(cpp_params, cpp_pos, cpp_norm, cpp_xDir))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 14. Dropper
// ===========================================================================
RAILCAPICALL topo_shape_t *create_dropper(dropper_params_t params) {
  dropper_params cpp_params{params.length,     params.wireDiameter,
                             params.clampLength, params.clampWidth,
                             params.clampThickness,
                             params.conductive != 0};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_dropper(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_dropper_with_place(dropper_params_t params, pnt3d_t topPoint,
                          dir3d_t direction) {
  dropper_params cpp_params{params.length,     params.wireDiameter,
                             params.clampLength, params.clampWidth,
                             params.clampThickness,
                             params.conductive != 0};
  gp_Pnt cpp_top(topPoint.x, topPoint.y, topPoint.z);
  gp_Dir cpp_dir(direction.x, direction.y, direction.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_dropper(cpp_params, cpp_top, cpp_dir))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 15. Cantilever Base
// ===========================================================================
RAILCAPICALL topo_shape_t *
create_cantilever_base(cantilever_base_params_t params) {
  cantilever_base_params cpp_params{params.length, params.width, params.height,
                                     params.boltSpacing, params.boltDiameter,
                                     params.boltCount};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_cantilever_base(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_cantilever_base_with_place(cantilever_base_params_t params, pnt3d_t position,
                                  dir3d_t normal, dir3d_t upDir) {
  cantilever_base_params cpp_params{params.length, params.width, params.height,
                                     params.boltSpacing, params.boltDiameter,
                                     params.boltCount};
  gp_Pnt cpp_pos(position.x, position.y, position.z);
  gp_Dir cpp_norm(normal.x, normal.y, normal.z);
  gp_Dir cpp_up(upDir.x, upDir.y, upDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_cantilever_base(cpp_params, cpp_pos, cpp_norm, cpp_up))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 16. MW Saddle
// ===========================================================================
RAILCAPICALL topo_shape_t *create_mw_saddle(mw_saddle_params_t params) {
  mw_saddle_params cpp_params{params.length, params.width, params.height,
                               params.grooveRadius, params.boltDiameter};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_mw_saddle(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_mw_saddle_with_place(mw_saddle_params_t params, pnt3d_t position,
                            dir3d_t normal, dir3d_t xDir) {
  mw_saddle_params cpp_params{params.length, params.width, params.height,
                               params.grooveRadius, params.boltDiameter};
  gp_Pnt cpp_pos(position.x, position.y, position.z);
  gp_Dir cpp_norm(normal.x, normal.y, normal.z);
  gp_Dir cpp_x(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_mw_saddle(cpp_params, cpp_pos, cpp_norm, cpp_x))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 17. Balance Weight
// ===========================================================================
RAILCAPICALL topo_shape_t *
create_balance_weight(balance_weight_params_t params) {
  balance_weight_params cpp_params{
      params.width, params.thickness, params.height, params.centerHoleDiameter};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_balance_weight(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_balance_weight_with_place(balance_weight_params_t params, pnt3d_t position,
                                 dir3d_t normal, dir3d_t xDir) {
  balance_weight_params cpp_params{
      params.width, params.thickness, params.height, params.centerHoleDiameter};
  gp_Pnt cpp_pos(position.x, position.y, position.z);
  gp_Dir cpp_norm(normal.x, normal.y, normal.z);
  gp_Dir cpp_x(xDir.x, xDir.y, xDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_balance_weight(cpp_params, cpp_pos, cpp_norm, cpp_x))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 18. Weight Rod
// ===========================================================================
RAILCAPICALL topo_shape_t *create_weight_rod(weight_rod_params_t params) {
  weight_rod_params cpp_params{params.rodDiameter, params.rodLength,
                                params.topHoleDiameter};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_weight_rod(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_weight_rod_with_place(weight_rod_params_t params, pnt3d_t position,
                             dir3d_t axisDir) {
  weight_rod_params cpp_params{params.rodDiameter, params.rodLength,
                                params.topHoleDiameter};
  gp_Pnt cpp_pos(position.x, position.y, position.z);
  gp_Dir cpp_axis(axisDir.x, axisDir.y, axisDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_weight_rod(cpp_params, cpp_pos, cpp_axis))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 19. Anchor Fitting
// ===========================================================================
RAILCAPICALL topo_shape_t *
create_anchor_fitting(anchor_fitting_params_t params) {
  anchor_fitting_params cpp_params{
      static_cast<anchor_fitting_type>(params.ctype), params.length,
      params.diameter};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_anchor_fitting(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_anchor_fitting_with_place(anchor_fitting_params_t params, pnt3d_t position,
                                  dir3d_t direction, dir3d_t upDir) {
  anchor_fitting_params cpp_params{
      static_cast<anchor_fitting_type>(params.ctype), params.length,
      params.diameter};
  gp_Pnt cpp_pos(position.x, position.y, position.z);
  gp_Dir cpp_dir(direction.x, direction.y, direction.z);
  gp_Dir cpp_up(upDir.x, upDir.y, upDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_anchor_fitting(cpp_params, cpp_pos, cpp_dir, cpp_up))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 20. Crossing
// ===========================================================================
RAILCAPICALL topo_shape_t *create_crossing(crossing_params_t params) {
  crossing_params cpp_params{params.limitPipeLength, params.pipeDiameter,
                              params.wireDiameter, params.heightDiff};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_crossing(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_crossing_with_place(crossing_params_t params, pnt3d_t crossPoint,
                           dir3d_t mainDir, dir3d_t branchDir) {
  crossing_params cpp_params{params.limitPipeLength, params.pipeDiameter,
                              params.wireDiameter, params.heightDiff};
  gp_Pnt cpp_cp(crossPoint.x, crossPoint.y, crossPoint.z);
  gp_Dir cpp_md(mainDir.x, mainDir.y, mainDir.z);
  gp_Dir cpp_bd(branchDir.x, branchDir.y, branchDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_crossing(cpp_params, cpp_cp, cpp_md, cpp_bd))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 21. Head Span
// ===========================================================================
RAILCAPICALL topo_shape_t *create_head_span(head_span_params_t params) {
  head_span_params cpp_params{
      params.span,          params.hangPointCount, params.hangPointSpacing,
      params.crossCatenaryDiameter, params.crossCatenarySag,
      params.upperRopeDiameter,     params.lowerRopeDiameter,
      params.insulatorLength};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_head_span(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_head_span_with_place(head_span_params_t params, pnt3d_t leftMast,
                            pnt3d_t rightMast, dir3d_t upDir) {
  head_span_params cpp_params{
      params.span,          params.hangPointCount, params.hangPointSpacing,
      params.crossCatenaryDiameter, params.crossCatenarySag,
      params.upperRopeDiameter,     params.lowerRopeDiameter,
      params.insulatorLength};
  gp_Pnt cpp_left(leftMast.x, leftMast.y, leftMast.z);
  gp_Pnt cpp_right(rightMast.x, rightMast.y, rightMast.z);
  gp_Dir cpp_up(upDir.x, upDir.y, upDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_head_span(cpp_params, cpp_left, cpp_right, cpp_up))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 22. Transverse Span
// ===========================================================================
RAILCAPICALL topo_shape_t *
create_transverse_span(transverse_span_params_t params) {
  transverse_span_params cpp_params{
      params.span,           static_cast<beam_section_type>(params.beamType),
      params.beamHeight,     params.beamWidth,
      params.beamThickness,  params.mastHeight,
      params.mastWidth};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_transverse_span(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_transverse_span_with_place(transverse_span_params_t params, pnt3d_t position,
                                   dir3d_t direction, dir3d_t upDir) {
  transverse_span_params cpp_params{
      params.span,           static_cast<beam_section_type>(params.beamType),
      params.beamHeight,     params.beamWidth,
      params.beamThickness,  params.mastHeight,
      params.mastWidth};
  gp_Pnt cpp_pos(position.x, position.y, position.z);
  gp_Dir cpp_dir(direction.x, direction.y, direction.z);
  gp_Dir cpp_up(upDir.x, upDir.y, upDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_transverse_span(cpp_params, cpp_pos, cpp_dir, cpp_up))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 22b. Hanger Post
// ===========================================================================
RAILCAPICALL topo_shape_t *create_hanger_post(hanger_post_params_t params) {
  hanger_post_params cpp_params{
      static_cast<hanger_post_section_type>(params.sectionType),
      params.length,         params.sectionSize,    params.wallThickness,
      params.topFlangeSize,  params.topFlangeThick, params.bottomFlangeSize,
      params.bottomFlangeThick, params.boltDiameter, params.boltSpacing};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_hanger_post(cpp_params))};
  } catch (...) { return nullptr; }
}

RAILCAPICALL topo_shape_t *
create_hanger_post_with_place(hanger_post_params_t params, pnt3d_t position,
                               dir3d_t direction) {
  hanger_post_params cpp_params{
      static_cast<hanger_post_section_type>(params.sectionType),
      params.length,         params.sectionSize,    params.wallThickness,
      params.topFlangeSize,  params.topFlangeThick, params.bottomFlangeSize,
      params.bottomFlangeThick, params.boltDiameter, params.boltSpacing};
  gp_Pnt cpp_pos(position.x, position.y, position.z);
  gp_Dir cpp_dir(direction.x, direction.y, direction.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_hanger_post(cpp_params, cpp_pos, cpp_dir))};
  } catch (...) { return nullptr; }
}

// ===========================================================================
// 22c. Portal Frame
// ===========================================================================
RAILCAPICALL topo_shape_t *create_portal_frame(portal_frame_params_t params) {
  portal_frame_params cpp_params{
      params.frameHeight,    params.frameWidth,     params.postDiameter,
      params.postWallThick,  params.beamDiameter,   params.beamWallThick,
      params.beamLength,     params.basePlateLength, params.basePlateWidth,
      params.basePlateThick, params.hangPointCount,  params.hangPointSpacing,
      params.boltSpacing,    params.boltDiameter};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_portal_frame(cpp_params))};
  } catch (...) { return nullptr; }
}

RAILCAPICALL topo_shape_t *
create_portal_frame_with_place(portal_frame_params_t params, pnt3d_t position,
                                dir3d_t direction, dir3d_t upDir) {
  portal_frame_params cpp_params{
      params.frameHeight,    params.frameWidth,     params.postDiameter,
      params.postWallThick,  params.beamDiameter,   params.beamWallThick,
      params.beamLength,     params.basePlateLength, params.basePlateWidth,
      params.basePlateThick, params.hangPointCount,  params.hangPointSpacing,
      params.boltSpacing,    params.boltDiameter};
  gp_Pnt cpp_pos(position.x, position.y, position.z);
  gp_Dir cpp_dir(direction.x, direction.y, direction.z);
  gp_Dir cpp_up(upDir.x, upDir.y, upDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_portal_frame(cpp_params, cpp_pos, cpp_dir, cpp_up))};
  } catch (...) { return nullptr; }
}

// ===========================================================================
// 22e. Suspension Hard Span
// ===========================================================================
RAILCAPICALL topo_shape_t *
create_suspension_hard_span(suspension_hard_span_params_t params) {
  suspension_hard_span_params cpp_params{
      params.span,           params.mastHeight, params.mastWidth,
      params.cableDiameter,  params.cableSag,   params.dropperCableDiameter,
      params.dropperCount,   params.dropperSpacing,
      params.insulatorLength, params.insulatorDiameter};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_suspension_hard_span(cpp_params))};
  } catch (...) { return nullptr; }
}

RAILCAPICALL topo_shape_t *
create_suspension_hard_span_with_place(suspension_hard_span_params_t params,
                                        pnt3d_t position,
                                        dir3d_t direction, dir3d_t upDir) {
  suspension_hard_span_params cpp_params{
      params.span,           params.mastHeight, params.mastWidth,
      params.cableDiameter,  params.cableSag,   params.dropperCableDiameter,
      params.dropperCount,   params.dropperSpacing,
      params.insulatorLength, params.insulatorDiameter};
  gp_Pnt cpp_pos(position.x, position.y, position.z);
  gp_Dir cpp_dir(direction.x, direction.y, direction.z);
  gp_Dir cpp_up(upDir.x, upDir.y, upDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_suspension_hard_span(cpp_params, cpp_pos, cpp_dir, cpp_up))};
  } catch (...) { return nullptr; }
}

// ===========================================================================
// 22f. Positioning Cable
// ===========================================================================
RAILCAPICALL topo_shape_t *
create_positioning_cable(positioning_cable_params_t params) {
  positioning_cable_params cpp_params{
      params.diameter,
      gp_Pnt(params.topPoint.x, params.topPoint.y, params.topPoint.z),
      gp_Pnt(params.bottomPoint.x, params.bottomPoint.y, params.bottomPoint.z),
      params.adjustable != 0};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_positioning_cable(cpp_params))};
  } catch (...) { return nullptr; }
}

// ===========================================================================
// 23. Aux Bracket
// ===========================================================================
RAILCAPICALL topo_shape_t *create_aux_bracket(aux_bracket_params_t params) {
  aux_bracket_params cpp_params{
      static_cast<aux_bracket_type>(params.ctype),
      params.mountHeight,   params.overhangLength, params.bracketLength,
      params.bracketWidth,  params.boltSpacing,    params.boltDiameter};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_aux_bracket(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_aux_bracket_with_place(aux_bracket_params_t params, pnt3d_t position,
                              dir3d_t normal, dir3d_t upDir) {
  aux_bracket_params cpp_params{
      static_cast<aux_bracket_type>(params.ctype),
      params.mountHeight,   params.overhangLength, params.bracketLength,
      params.bracketWidth,  params.boltSpacing,    params.boltDiameter};
  gp_Pnt cpp_pos(position.x, position.y, position.z);
  gp_Dir cpp_norm(normal.x, normal.y, normal.z);
  gp_Dir cpp_up(upDir.x, upDir.y, upDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_aux_bracket(cpp_params, cpp_pos, cpp_norm, cpp_up))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 24. Rail
// ===========================================================================
RAILCAPICALL topo_shape_t *create_rail(rail_params_t params) {
  rail_params cpp_params{params.railHeight, params.headWidth,  params.baseWidth,
                          params.webThickness, params.headHeight, params.baseHeight,
                          params.headRadius,   params.standardLength};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_rail(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *create_rail_with_place(rail_params_t params,
                                                  pnt3d_t startPoint,
                                                  pnt3d_t endPoint) {
  rail_params cpp_params{params.railHeight, params.headWidth,  params.baseWidth,
                          params.webThickness, params.headHeight, params.baseHeight,
                          params.headRadius,   params.standardLength};
  gp_Pnt cpp_start(startPoint.x, startPoint.y, startPoint.z);
  gp_Pnt cpp_end(endPoint.x, endPoint.y, endPoint.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_rail(cpp_params, cpp_start, cpp_end))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 25. Sleeper
// ===========================================================================
RAILCAPICALL topo_shape_t *create_sleeper(sleeper_params_t params) {
  sleeper_params cpp_params{static_cast<sleeper_shape_type>(params.shapeType), params.length, params.width, params.height,
                             params.gauge, params.grooveDepth, params.spacing};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_sleeper(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_sleeper_with_place(sleeper_params_t params, pnt3d_t position,
                          dir3d_t direction, dir3d_t upDir) {
  sleeper_params cpp_params{static_cast<sleeper_shape_type>(params.shapeType), params.length, params.width, params.height,
                             params.gauge, params.grooveDepth, params.spacing};
  gp_Pnt cpp_pos(position.x, position.y, position.z);
  gp_Dir cpp_dir(direction.x, direction.y, direction.z);
  gp_Dir cpp_up(upDir.x, upDir.y, upDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_sleeper(cpp_params, cpp_pos, cpp_dir, cpp_up))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 26. Ballast
// ===========================================================================
RAILCAPICALL topo_shape_t *create_ballast(ballast_params_t params) {
  ballast_params cpp_params; cpp_params.topWidth = params.topWidth;
  cpp_params.thickness = params.thickness; cpp_params.sideSlope = params.sideSlope;
  for (int i = 0; i < params.pointCount - 1; ++i)
    cpp_params.centerlineSegments.push_back({centerline_curve_type::LINE,
      {gp_Pnt(params.centerline[i].x, params.centerline[i].y, params.centerline[i].z),
       gp_Pnt(params.centerline[i+1].x, params.centerline[i+1].y, params.centerline[i+1].z)}});
  try { return new topo_shape_t{.shp = std::make_shared<shape>(create_ballast(cpp_params))}; } catch (...) { return nullptr; }
}

// ===========================================================================
// 27. Track Slab
// ===========================================================================
RAILCAPICALL topo_shape_t *create_track_slab(track_slab_params_t params) {
  track_slab_params cpp_params{
      params.length, params.width, params.thickness, params.railSeatCount,
      params.railSeatSpacing, params.cementAsphaltThickness};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_track_slab(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_track_slab_with_place(track_slab_params_t params, pnt3d_t position,
                             dir3d_t direction, dir3d_t upDir) {
  track_slab_params cpp_params{
      params.length, params.width, params.thickness, params.railSeatCount,
      params.railSeatSpacing, params.cementAsphaltThickness};
  gp_Pnt cpp_pos(position.x, position.y, position.z);
  gp_Dir cpp_dir(direction.x, direction.y, direction.z);
  gp_Dir cpp_up(upDir.x, upDir.y, upDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_track_slab(cpp_params, cpp_pos, cpp_dir, cpp_up))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 28. Fastener
// ===========================================================================
RAILCAPICALL topo_shape_t *create_fastener(fastener_params_t params) {
  fastener_params cpp_params{params.spacing,  params.gauge,
                              params.padThickness, params.padLength,
                              params.padWidth};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_fastener(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_fastener_with_place(fastener_params_t params, pnt3d_t position,
                           dir3d_t direction, dir3d_t upDir) {
  fastener_params cpp_params{params.spacing,  params.gauge,
                              params.padThickness, params.padLength,
                              params.padWidth};
  gp_Pnt cpp_pos(position.x, position.y, position.z);
  gp_Dir cpp_dir(direction.x, direction.y, direction.z);
  gp_Dir cpp_up(upDir.x, upDir.y, upDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_fastener(cpp_params, cpp_pos, cpp_dir, cpp_up))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 29. Guard Rail
// ===========================================================================
RAILCAPICALL topo_shape_t *create_guard_rail(guard_rail_params_t params) {
  guard_rail_params cpp_params{
      params.height,    params.headWidth, params.baseWidth,
      params.grooveWidth, params.totalLength, params.gaugeDistance};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_guard_rail(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_guard_rail_with_place(guard_rail_params_t params, pnt3d_t startPoint,
                             pnt3d_t endPoint) {
  guard_rail_params cpp_params{
      params.height,    params.headWidth, params.baseWidth,
      params.grooveWidth, params.totalLength, params.gaugeDistance};
  gp_Pnt cpp_start(startPoint.x, startPoint.y, startPoint.z);
  gp_Pnt cpp_end(endPoint.x, endPoint.y, endPoint.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_guard_rail(cpp_params, cpp_start, cpp_end))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 30. Mast Assembly
// ===========================================================================
RAILCAPICALL topo_shape_t *
create_mast_assembly(mast_assembly_params_t params) {
  mast_assembly_params cpp_params{
      params.mastType,   params.mastHeight,    params.cantileverType,
      params.hasCrossArm != 0, params.armDiameter, params.stagger,
      params.compType,   params.ratedTension,  params.hasGuyWire != 0};
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(create_mast_assembly(cpp_params))};
  } catch (...) {
    return nullptr;
  }
}

RAILCAPICALL topo_shape_t *
create_mast_assembly_with_place(mast_assembly_params_t params, pnt3d_t position,
                                dir3d_t direction, dir3d_t upDir) {
  mast_assembly_params cpp_params{
      params.mastType,   params.mastHeight,    params.cantileverType,
      params.hasCrossArm != 0, params.armDiameter, params.stagger,
      params.compType,   params.ratedTension,  params.hasGuyWire != 0};
  gp_Pnt cpp_pos(position.x, position.y, position.z);
  gp_Dir cpp_dir(direction.x, direction.y, direction.z);
  gp_Dir cpp_up(upDir.x, upDir.y, upDir.z);
  try {
    return new topo_shape_t{
        .shp = std::make_shared<shape>(
            create_mast_assembly(cpp_params, cpp_pos, cpp_dir, cpp_up))};
  } catch (...) {
    return nullptr;
  }
}

// ===========================================================================
// 31. Switch Rail
// ===========================================================================
RAILCAPICALL topo_shape_t *create_switch_rail(switch_rail_params_t params) {
  switch_rail_params cpp_params{params.length, params.railHeight, params.railHeadWidth,
                                 params.railBaseWidth, params.tipWidth, params.curveRadius,
                                 params.isLeftHand != 0};
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(create_switch_rail(cpp_params))};
  } catch (...) { return nullptr; }
}

RAILCAPICALL topo_shape_t *create_switch_rail_with_place(switch_rail_params_t params,
                                                          pnt3d_t position,
                                                          dir3d_t direction, dir3d_t upDir) {
  switch_rail_params cpp_params{params.length, params.railHeight, params.railHeadWidth,
                                 params.railBaseWidth, params.tipWidth, params.curveRadius,
                                 params.isLeftHand != 0};
  gp_Pnt p(position.x, position.y, position.z);
  gp_Dir d(direction.x, direction.y, direction.z);
  gp_Dir u(upDir.x, upDir.y, upDir.z);
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(create_switch_rail(cpp_params, p, d, u))};
  } catch (...) { return nullptr; }
}

// ===========================================================================
// 32. Frog
// ===========================================================================
RAILCAPICALL topo_shape_t *create_frog(frog_params_t params) {
  frog_params cpp_params{params.turnoutNo, params.gauge, params.railHeight,
                          params.railHeadWidth, params.railBaseWidth};
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(create_frog(cpp_params))};
  } catch (...) { return nullptr; }
}

RAILCAPICALL topo_shape_t *create_frog_with_place(frog_params_t params,
                                                   pnt3d_t position,
                                                   dir3d_t direction, dir3d_t upDir) {
  frog_params cpp_params{params.turnoutNo, params.gauge, params.railHeight,
                          params.railHeadWidth, params.railBaseWidth};
  gp_Pnt p(position.x, position.y, position.z);
  gp_Dir d(direction.x, direction.y, direction.z);
  gp_Dir u(upDir.x, upDir.y, upDir.z);
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(create_frog(cpp_params, p, d, u))};
  } catch (...) { return nullptr; }
}

// ===========================================================================
// 33. Turnout
// ===========================================================================
RAILCAPICALL topo_shape_t *create_turnout(turnout_params_t params) {
  turnout_params cpp_params{params.turnoutNo, params.isLeftHand != 0, params.gauge,
                             params.railHeight, params.railHeadWidth, params.railBaseWidth,
                             params.switchRailLength, params.leadCurveRadius, params.frogLength,
                             params.sleeperCount, params.sleeperSpacing};
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(create_turnout(cpp_params))};
  } catch (...) { return nullptr; }
}

RAILCAPICALL topo_shape_t *create_turnout_with_place(turnout_params_t params,
                                                      pnt3d_t position,
                                                      dir3d_t direction, dir3d_t upDir) {
  turnout_params cpp_params{params.turnoutNo, params.isLeftHand != 0, params.gauge,
                             params.railHeight, params.railHeadWidth, params.railBaseWidth,
                             params.switchRailLength, params.leadCurveRadius, params.frogLength,
                             params.sleeperCount, params.sleeperSpacing};
  gp_Pnt p(position.x, position.y, position.z);
  gp_Dir d(direction.x, direction.y, direction.z);
  gp_Dir u(upDir.x, upDir.y, upDir.z);
  try {
    return new topo_shape_t{.shp = std::make_shared<shape>(create_turnout(cpp_params, p, d, u))};
  } catch (...) { return nullptr; }
}

// ===========================================================================
// 35. Rail Pair
// ===========================================================================
RAILCAPICALL topo_shape_t *create_rail_pair(rail_pair_params_t params) {
  std::vector<gp_Pnt> pts; for (int i = 0; i < params.pointCount; ++i) pts.push_back(gp_Pnt(params.centerline[i].x, params.centerline[i].y, params.centerline[i].z));
  rail_pair_params cpp_params{pts, params.gauge, params.superElevation, params.railHeight, params.railHeadWidth, params.railBaseWidth};
  try { return new topo_shape_t{.shp = std::make_shared<shape>(create_rail_pair(cpp_params))}; } catch (...) { return nullptr; }
}
RAILCAPICALL topo_shape_t *create_rail_pair_with_place(rail_pair_params_t params, pnt3d_t position, dir3d_t direction, dir3d_t upDir) {
  std::vector<gp_Pnt> pts; for (int i = 0; i < params.pointCount; ++i) pts.push_back(gp_Pnt(params.centerline[i].x, params.centerline[i].y, params.centerline[i].z));
  rail_pair_params cpp_params{pts, params.gauge, params.superElevation, params.railHeight, params.railHeadWidth, params.railBaseWidth};
  try { return new topo_shape_t{.shp = std::make_shared<shape>(create_rail_pair(cpp_params, gp_Pnt(position.x,position.y,position.z), gp_Dir(direction.x,direction.y,direction.z), gp_Dir(upDir.x,upDir.y,upDir.z)))}; } catch (...) { return nullptr; }
}

// ===========================================================================
// 36. Sleeper Layout
// ===========================================================================
RAILCAPICALL topo_shape_t *create_sleeper_layout(sleeper_layout_params_t params) {
  std::vector<gp_Pnt> pts; for (int i = 0; i < params.pointCount; ++i) pts.push_back(gp_Pnt(params.centerline[i].x, params.centerline[i].y, params.centerline[i].z));
  sleeper_layout_params cpp_params{pts, params.length, params.width, params.height, params.spacing, params.gauge};
  try { return new topo_shape_t{.shp = std::make_shared<shape>(create_sleeper_layout(cpp_params))}; } catch (...) { return nullptr; }
}

// ===========================================================================
// 37. Straight Track
// ===========================================================================
RAILCAPICALL topo_shape_t *create_straight_track(straight_track_params_t params) {
  straight_track_params p{ gp_Pnt(params.startPoint.x,params.startPoint.y,params.startPoint.z),
    gp_Pnt(params.endPoint.x,params.endPoint.y,params.endPoint.z), params.gauge,
    params.railHeight, params.railHeadWidth, params.railBaseWidth,
    params.sleeperLength, params.sleeperWidth, params.sleeperHeight, params.sleeperSpacing,
    params.ballastTopWidth, params.ballastThickness, params.ballastSlope };
  try { return new topo_shape_t{.shp = std::make_shared<shape>(create_straight_track(p))}; } catch (...) { return nullptr; }
}
RAILCAPICALL topo_shape_t *create_straight_track_with_place(straight_track_params_t params,
    pnt3d_t position, dir3d_t direction, dir3d_t upDir) {
  straight_track_params p{ gp_Pnt(params.startPoint.x,params.startPoint.y,params.startPoint.z),
    gp_Pnt(params.endPoint.x,params.endPoint.y,params.endPoint.z), params.gauge,
    params.railHeight, params.railHeadWidth, params.railBaseWidth,
    params.sleeperLength, params.sleeperWidth, params.sleeperHeight, params.sleeperSpacing,
    params.ballastTopWidth, params.ballastThickness, params.ballastSlope };
  try { return new topo_shape_t{.shp = std::make_shared<shape>(create_straight_track(p,
    gp_Pnt(position.x,position.y,position.z), gp_Dir(direction.x,direction.y,direction.z),
    gp_Dir(upDir.x,upDir.y,upDir.z)))}; } catch (...) { return nullptr; }
}

// ===========================================================================
// 38. Curve Track
// ===========================================================================
RAILCAPICALL topo_shape_t *create_curve_track(curve_track_params_t params) {
  curve_track_params p{ gp_Pnt(params.curveCenter.x,params.curveCenter.y,params.curveCenter.z),
    params.startAngle, params.sweepAngle, params.curveRadius, params.gauge, params.superElevation,
    params.railHeight, params.railHeadWidth, params.railBaseWidth, params.sleeperLength,
    params.sleeperWidth, params.sleeperHeight, params.sleeperSpacing,
    params.ballastTopWidth, params.ballastThickness, params.ballastSlope };
  try { return new topo_shape_t{.shp = std::make_shared<shape>(create_curve_track(p))}; } catch (...) { return nullptr; }
}
RAILCAPICALL topo_shape_t *create_curve_track_with_place(curve_track_params_t params,
    pnt3d_t position, dir3d_t direction, dir3d_t upDir) {
  curve_track_params p{ gp_Pnt(params.curveCenter.x,params.curveCenter.y,params.curveCenter.z),
    params.startAngle, params.sweepAngle, params.curveRadius, params.gauge, params.superElevation,
    params.railHeight, params.railHeadWidth, params.railBaseWidth, params.sleeperLength,
    params.sleeperWidth, params.sleeperHeight, params.sleeperSpacing,
    params.ballastTopWidth, params.ballastThickness, params.ballastSlope };
  try { return new topo_shape_t{.shp = std::make_shared<shape>(create_curve_track(p,
    gp_Pnt(position.x,position.y,position.z), gp_Dir(direction.x,direction.y,direction.z),
    gp_Dir(upDir.x,upDir.y,upDir.z)))}; } catch (...) { return nullptr; }
}

#ifdef __cplusplus
}
#endif
