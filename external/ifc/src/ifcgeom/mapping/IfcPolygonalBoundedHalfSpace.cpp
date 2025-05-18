#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr
mapping::map_impl(const IfcSchema::IfcPolygonalBoundedHalfSpace *inst) {
  auto s = taxonomy::cast<taxonomy::solid>(
      map_impl((IfcSchema::IfcHalfSpaceSolid *)inst));
  auto f = s->children[0]->children[0];
  f->children = {
      taxonomy::cast<taxonomy::loop>(map(inst->PolygonalBoundary()))};
  f->matrix = taxonomy::cast<taxonomy::matrix4>(map(inst->Position()));
  return s;
}
