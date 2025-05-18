#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcVector *inst) {
  auto d = taxonomy::cast<taxonomy::direction3>(map(inst->Orientation()));
  d = taxonomy::direction3::ptr(d->clone_());
  d->components() *= inst->Magnitude() * length_unit_;
  return d;
}
