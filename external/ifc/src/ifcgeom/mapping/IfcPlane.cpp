#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcPlane *inst) {
  auto p = taxonomy::make<taxonomy::plane>();
  p->matrix = taxonomy::cast<taxonomy::matrix4>(map(inst->Position()));
  return p;
}
