#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcCartesianPoint *inst) {
  std::vector<double> xyz = inst->Coordinates();
  return taxonomy::make<taxonomy::point3>(
      xyz.size() >= 1 ? xyz[0] * length_unit_ : 0.,
      xyz.size() >= 2 ? xyz[1] * length_unit_ : 0.,
      xyz.size() >= 3 ? xyz[2] * length_unit_ : 0.);
}
