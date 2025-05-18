#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

#include <ifcgeom/profile_helper.h>

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcRectangleProfileDef *inst) {
  const double x = inst->XDim() / 2.0f * length_unit_;
  const double y = inst->YDim() / 2.0f * length_unit_;

  const double tol = settings_.get<settings::Precision>().get();

  if (x < tol || y < tol) {
    Logger::Message(Logger::LOG_NOTICE, "Skipping zero sized profile:", inst);
    return nullptr;
  }

  taxonomy::matrix4::ptr m4;
  bool has_position = true;
#ifdef SCHEMA_IfcParameterizedProfileDef_Position_IS_OPTIONAL
  has_position = !!inst->Position();
#endif
  if (has_position) {
    m4 = taxonomy::cast<taxonomy::matrix4>(map(inst->Position()));
  }

  return profile_helper(m4, {{{-x, -y}}, {{x, -y}}, {{x, y}}, {{-x, y}}});
}
