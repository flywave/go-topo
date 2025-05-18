#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr
mapping::map_impl(const IfcSchema::IfcSurfaceOfLinearExtrusion *inst) {
  taxonomy::matrix4::ptr matrix;
  bool has_position = true;
#ifdef SCHEMA_IfcSweptAreaSolid_Position_IS_OPTIONAL
  has_position = inst->Position() != nullptr;
#endif
  if (has_position) {
    matrix = taxonomy::cast<taxonomy::matrix4>(map(inst->Position()));
  }

  return taxonomy::make<taxonomy::extrusion>(
      matrix, map(inst->SweptCurve()),
      taxonomy::cast<taxonomy::direction3>(map(inst->ExtrudedDirection())),
      std::numeric_limits<double>::infinity());
}
