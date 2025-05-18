#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcSphere *inst) {
  auto sol = taxonomy::make<taxonomy::solid>();
  auto shl = taxonomy::make<taxonomy::shell>();
  auto fac = taxonomy::make<taxonomy::face>();
  auto spr = taxonomy::make<taxonomy::sphere>();
  spr->matrix = taxonomy::cast<taxonomy::matrix4>(map(inst->Position()));
  spr->radius = inst->Radius() * length_unit_;
  fac->basis = spr;
  shl->children.push_back(fac);
  sol->children.push_back(shl);
  return sol;
}
