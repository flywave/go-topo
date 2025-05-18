#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcDirection *inst) {
  auto coords = inst->DirectionRatios();
  return taxonomy::make<taxonomy::direction3>(
      coords.size() >= 1 ? coords[0] : 0., coords.size() >= 2 ? coords[1] : 0.,
      coords.size() >= 3 ? coords[2] : 0.);
}