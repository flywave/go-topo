#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

#ifdef SCHEMA_HAS_IfcCylindricalSurface

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcCylindricalSurface *inst) {
  auto c = taxonomy::make<taxonomy::cylinder>();
  c->radius = inst->Radius() * length_unit_;
  c->matrix = taxonomy::cast<taxonomy::matrix4>(map(inst->Position()));
  return c;
}

#endif
