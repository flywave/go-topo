#include <ifcgeom/mapping/mapping.h>

#define mapping POSTFIX_SCHEMA(mapping)

using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcAxis2Placement3D *inst) {
  Eigen::Vector3d o(0, 0, 0), axis(0, 0, 1), refDirection, X(1, 0, 0);
  try {
    taxonomy::point3::ptr v =
        taxonomy::cast<taxonomy::point3>(map(inst->Location()));
    o = *v->components_;
  } catch (const std::exception &) {
    Logger::Warning("Placement with invalid Location:", inst);
  }
  const bool hasAxis = !!inst->Axis();
  const bool hasRef = !!inst->RefDirection();

  if (hasAxis != hasRef) {
    Logger::Warning("Axis and RefDirection should be specified together", inst);
  }

  if (hasAxis) {
    taxonomy::direction3::ptr v =
        taxonomy::cast<taxonomy::direction3>(map(inst->Axis()));
    axis = *v->components_;
  }

  if (hasRef) {
    taxonomy::direction3::ptr v =
        taxonomy::cast<taxonomy::direction3>(map(inst->RefDirection()));
    refDirection = *v->components_;
  } else {
    if (acos(axis.dot(X)) > 1.e-5) {
      refDirection = {1., 0., 0.};
    } else {
      refDirection = {0., 0., 1.};
    }
    auto Xvec = axis.dot(refDirection) * axis;
    auto Xaxis = refDirection - Xvec;
    refDirection = Xaxis;
  }
  return taxonomy::make<taxonomy::matrix4>(o, axis, refDirection);
}
