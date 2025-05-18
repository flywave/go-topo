#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)

using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcAxis1Placement *inst) {
  Eigen::Vector3d P(0, 0, 0), axis(0, 0, 1), ref;
  try {
    taxonomy::point3::ptr v =
        taxonomy::cast<taxonomy::point3>(map(inst->Location()));
    P = *v->components_;
  } catch (const std::exception &) {
    Logger::Warning("Placement with invalid Location:", inst);
  }
  const bool hasAxis = inst->Axis();
  if (hasAxis) {
    taxonomy::direction3::ptr v =
        taxonomy::cast<taxonomy::direction3>(map(inst->Axis()));
    axis = *v->components_;
  }

  // @todo not sure what to do with ref, we're probably never reading it,
  // because we just created an Axis1 again from it in the kernel, but
  // to this constructor we need to supply something valid.
  if (std::abs(axis.x()) > std::abs(axis.z())) {
    ref = Eigen::Vector3d(0, 0, 1).cross(axis).normalized();
  } else {
    ref = Eigen::Vector3d(1, 0, 0).cross(axis).normalized();
  }

  return taxonomy::make<taxonomy::matrix4>(P, axis, ref);
}
