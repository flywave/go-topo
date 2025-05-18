#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr
mapping::map_impl(const IfcSchema::IfcRectangularTrimmedSurface *inst) {
  // @todo we'll need to add support for p-curves at some point, but not now.
  return nullptr;
}
