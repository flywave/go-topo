#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcLine *inst) {
  // @todo test with trimmed curve on non-normalized direction
  auto l = taxonomy::make<taxonomy::line>();
  auto pnt = taxonomy::cast<taxonomy::point3>(map(inst->Pnt()));
  auto dir = taxonomy::cast<taxonomy::direction3>(map(inst->Dir()));
  l->matrix =
      taxonomy::make<taxonomy::matrix4>(pnt->ccomponents(), dir->ccomponents());
  return l;
}
