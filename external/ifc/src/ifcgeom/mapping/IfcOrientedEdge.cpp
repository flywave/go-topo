#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcOrientedEdge *inst) {
  auto e = taxonomy::cast<taxonomy::edge>(map(inst->EdgeElement()));
  e.reset(e->clone_());
  if (!inst->Orientation()) {
    e->reverse();
  }
  return e;
}
