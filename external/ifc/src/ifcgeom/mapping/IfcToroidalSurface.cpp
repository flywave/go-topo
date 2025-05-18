#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

#ifdef SCHEMA_HAS_IfcToroidalSurface

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcToroidalSurface *inst) {
  return nullptr;
}

#endif
