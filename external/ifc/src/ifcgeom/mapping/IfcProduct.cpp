#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

using namespace IfcGeom;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcProduct *inst) {
  // @todo decide on this, what happens in the product mapping?
  // currently things like openings, layers and materials are processed in the
  // converter
  auto c = taxonomy::make<taxonomy::collection>();
  if (inst->ObjectPlacement()) {
    c->matrix = taxonomy::cast<taxonomy::matrix4>(map(inst->ObjectPlacement()));
  } else {
    // @todo Otherwise we get crashes in the serializer, but maybe fix them
    // there..?
    c->matrix = taxonomy::make<taxonomy::matrix4>();
  }
  return c;
}
