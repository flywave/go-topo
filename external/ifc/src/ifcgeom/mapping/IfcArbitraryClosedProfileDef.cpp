#include <ifcgeom/mapping/mapping.h>

#define mapping POSTFIX_SCHEMA(mapping)

using namespace ifcopenshell::geometry;

taxonomy::ptr
mapping::map_impl(const IfcSchema::IfcArbitraryClosedProfileDef *inst) {
  auto loop = taxonomy::cast<taxonomy::loop>(map(inst->OuterCurve()));
  if (loop) {
    if (inst->ProfileType() ==
        IfcSchema::IfcProfileTypeEnum::IfcProfileType_CURVE) {
      return loop;
    }

    auto face = taxonomy::make<taxonomy::face>();
    loop->external = true;
    face->children = {loop};

    if (inst->as<IfcSchema::IfcArbitraryProfileDefWithVoids>()) {
      auto with_voids = inst->as<IfcSchema::IfcArbitraryProfileDefWithVoids>();
      auto voids = with_voids->InnerCurves();
      for (auto &v : *voids) {
        auto inner_loop = taxonomy::cast<taxonomy::loop>(map(v));
        if (inner_loop) {
          inner_loop->external = false;
          face->children.push_back(inner_loop);
        }
      }
    }

    return face;
  } else {
    return nullptr;
  }
}
