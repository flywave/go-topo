#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

#include <ifcgeom/profile_helper.h>

#include <array>
#include <boost/optional/optional.hpp>
#include <vector>

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcCShapeProfileDef *inst) {
  const double y = inst->Depth() / 2.0f * length_unit_;
  const double x = inst->Width() / 2.0f * length_unit_;
  const double d1 = inst->WallThickness() * length_unit_;
  const double d2 = inst->Girth() * length_unit_;
  bool doFillet = !!inst->InternalFilletRadius();
  double f1 = 0;
  double f2 = 0;
  if (doFillet) {
    f1 = *inst->InternalFilletRadius() * length_unit_;
    f2 = f1 + d1;
  }

  const double tol = settings_.get<settings::Precision>().get();

  if (x < tol || y < tol || d1 < tol || d2 < tol) {
    Logger::Message(Logger::LOG_NOTICE, " Skipping zero sized profile:", inst);
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

  return profile_helper(m4, {{{-x, -y}, {f2}},
                             {{x, -y}, {f2}},
                             {{x, -y + d2}},
                             {{x - d1, -y + d2}},
                             {{x - d1, -y + d1}, {f1}},
                             {{-x + d1, -y + d1}, {f1}},
                             {{-x + d1, y - d1}, {f1}},
                             {{x - d1, y - d1}, {f1}},
                             {{x - d1, y - d2}},
                             {{x, y - d2}},
                             {{x, y}, {f2}},
                             {{-x, y}, {f2}}});
}
