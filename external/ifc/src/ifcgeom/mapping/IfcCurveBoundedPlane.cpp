#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcCurveBoundedPlane *inst) {
  taxonomy::plane::ptr pl =
      taxonomy::cast<taxonomy::plane>(map(inst->BasisSurface()));
  auto f = taxonomy::make<taxonomy::face>();
  f->children.push_back(
      taxonomy::cast<taxonomy::loop>(map(inst->OuterBoundary())));

  IfcSchema::IfcCurve::list::ptr boundaries = inst->InnerBoundaries();

  for (IfcSchema::IfcCurve::list::it it = boundaries->begin();
       it != boundaries->end(); ++it) {
    f->children.push_back(taxonomy::cast<taxonomy::loop>(map(*it)));
  }
  f->matrix = pl->matrix;

  return f;
}
