#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

#include <ifcgeom/profile_helper.h>

#ifdef SCHEMA_HAS_IfcCraneRailAShapeProfileDef

taxonomy::ptr
mapping::map_impl(const IfcSchema::IfcCraneRailAShapeProfileDef *inst) {
  double oh = inst->OverallHeight() * length_unit_;
  double bw2 = inst->BaseWidth2() * length_unit_;
  double hw = inst->HeadWidth() * length_unit_;
  double hd2 = inst->HeadDepth2() * length_unit_;
  double hd3 = inst->HeadDepth3() * length_unit_;
  double wt = inst->WebThickness() * length_unit_;
  double bw4 = inst->BaseWidth4() * length_unit_;
  double bd1 = inst->BaseDepth1() * length_unit_;
  double bd2 = inst->BaseDepth2() * length_unit_;
  double bd3 = inst->BaseDepth3() * length_unit_;

  taxonomy::matrix4::ptr m4;
  bool has_position = true;
#ifdef SCHEMA_IfcParameterizedProfileDef_Position_IS_OPTIONAL
  has_position = !!inst->Position();
#endif
  if (has_position) {
    m4 = taxonomy::cast<taxonomy::matrix4>(map(inst->Position()));
  }

  return profile_helper(m4, {{{-hw / 2., +oh / 2.}},
                             {{-hw / 2., +oh / 2. - hd3}},
                             {{-wt / 2., +oh / 2. - hd2}},
                             {{-wt / 2., -oh / 2. + bd2}},
                             {{-bw4 / 2., -oh / 2. + bd3}},
                             {{-bw2 / 2., -oh / 2. + bd1}},
                             {{-bw2 / 2., -oh / 2.}},
                             {{+bw2 / 2., -oh / 2.}},
                             {{+bw2 / 2., -oh / 2. + bd1}},
                             {{+bw4 / 2., -oh / 2. + bd3}},
                             {{+wt / 2., -oh / 2. + bd2}},
                             {{+wt / 2., +oh / 2. - hd2}},
                             {{+hw / 2., +oh / 2. - hd3}},
                             {{+hw / 2., +oh / 2.}}});
}
#endif
