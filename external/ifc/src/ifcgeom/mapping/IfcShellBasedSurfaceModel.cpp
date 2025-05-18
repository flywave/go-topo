#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr
mapping::map_impl(const IfcSchema::IfcShellBasedSurfaceModel *inst) {
  return map_to_collection(this, inst->SbsmBoundary());
}
