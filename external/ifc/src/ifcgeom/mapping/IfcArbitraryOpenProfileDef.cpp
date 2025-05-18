#include <ifcgeom/mapping/mapping.h>
#define _USE_MATH_DEFINES
#define mapping POSTFIX_SCHEMA(mapping)

using namespace ifcopenshell::geometry;

taxonomy::ptr
mapping::map_impl(const IfcSchema::IfcArbitraryOpenProfileDef *inst) {
  return map(inst->Curve());
}
