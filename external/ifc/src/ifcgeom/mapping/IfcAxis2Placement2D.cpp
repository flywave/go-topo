#include <ifcgeom/mapping/mapping.h>

#define mapping POSTFIX_SCHEMA(mapping)

using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcAxis2Placement2D *inst) {
  Eigen::Vector3d P(0, 0, 0), axis(0, 0, 1), V(1, 0, 0);
  try {
    taxonomy::point3::ptr v =
        taxonomy::cast<taxonomy::point3>(map(inst->Location()));
    P = *v->components_;
  } catch (const std::exception &) {
    Logger::Warning("Placement with invalid Location:", inst);
  }
  const bool hasRef = !!inst->RefDirection();
  if (hasRef) {
    taxonomy::direction3::ptr v =
        taxonomy::cast<taxonomy::direction3>(map(inst->RefDirection()));
    V = *v->components_;
  }
  return taxonomy::make<taxonomy::matrix4>(P, axis, V);
}
