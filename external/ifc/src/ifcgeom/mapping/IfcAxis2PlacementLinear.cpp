#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

#if defined SCHEMA_HAS_IfcAxis2PlacementLinear

taxonomy::ptr
mapping::map_impl(const IfcSchema::IfcAxis2PlacementLinear *inst) {

  if (!inst->Location()->as<IfcSchema::IfcPointByDistanceExpression>())
    Logger::Error(
        std::runtime_error("Location must be IfcPointByDistanceExpression for "
                           "IfcAxis2PlacementLinear"));

  Eigen::Vector3d o, axis(0, 0, 1), refDirection;

  taxonomy::matrix4::ptr m =
      taxonomy::cast<taxonomy::matrix4>(map(inst->Location()));
  o = m->components().col(3).head<3>();

  // From 8.9.3.4 IfcAxis2PlacementLinear there are 4 cases that need to be
  // considered 1) Axis is given but not RefDirection 2) RefDirection is given
  // but not Axis
  // 3) Neither Axis or RefDirection are provided
  // 4) Both Axis and RefDirection are provided

  const bool hasAxis = inst->Axis() != nullptr;
  const bool hasRef = inst->RefDirection() != nullptr;

  if (hasAxis != hasRef) {
    Logger::Warning("Axis and RefDirection should be specified together", inst);
  }

  if (hasAxis && !hasRef) {
    taxonomy::direction3::ptr a =
        taxonomy::cast<taxonomy::direction3>(map(inst->Axis()));
    axis = *a->components_;

    refDirection =
        m->components()
            .col(0)
            .head<3>(); // RefDirection is the curve tangent when omitted
    // refDirection is not necessarily orthogonal to axis.
    // axis.cross(refDirection) gives y. y.cross(axis) gives x=refDirection
    refDirection = axis.cross(refDirection).cross(axis);
  } else if (!hasAxis && hasRef) {
    taxonomy::direction3::ptr r =
        taxonomy::cast<taxonomy::direction3>(map(inst->RefDirection()));
    refDirection = *r->components_;
    Eigen::Vector3d up(0, 0, 1);
    axis = refDirection.cross(up.cross(refDirection));
  } else if (!hasAxis && !hasRef) {
    refDirection =
        m->components()
            .col(0)
            .head<3>(); // RefDirection is the curve tangent when omitted
    Eigen::Vector3d up(0, 0, 1);
    axis = refDirection.cross(up.cross(refDirection));
  } else {
    taxonomy::direction3::ptr a =
        taxonomy::cast<taxonomy::direction3>(map(inst->Axis()));
    axis = *a->components_;

    taxonomy::direction3::ptr r =
        taxonomy::cast<taxonomy::direction3>(map(inst->RefDirection()));
    refDirection = *r->components_;
    refDirection =
        axis.cross(refDirection)
            .cross(axis); // refDirection needs to be orthogonal to axis
  }

  // axis and refDirection need to be orthogonal
  return taxonomy::make<taxonomy::matrix4>(o, axis, refDirection);
}

#endif
