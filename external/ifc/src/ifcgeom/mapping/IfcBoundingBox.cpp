#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)

using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcBoundingBox *inst) {
  if (!settings_.get<settings::KeepBoundingBoxes>().get()) {
    // @todo make sure it doesn't log.
    return nullptr;
  }

  const double dx = inst->XDim() * length_unit_;
  const double dy = inst->YDim() * length_unit_;
  const double dz = inst->ZDim() * length_unit_;

  taxonomy::point3::ptr corner =
      taxonomy::cast<taxonomy::point3>(map(inst->Corner()));
  auto solid = create_box(corner->ccomponents().x(), corner->ccomponents().y(),
                          corner->ccomponents().z(), dx, dy, dz);

  return solid;
}
