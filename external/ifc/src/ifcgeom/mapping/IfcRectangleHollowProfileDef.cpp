#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

#include <ifcgeom/profile_helper.h>

taxonomy::ptr
mapping::map_impl(const IfcSchema::IfcRectangleHollowProfileDef *inst) {
  const double x = inst->XDim() / 2.0f * length_unit_;
  const double y = inst->YDim() / 2.0f * length_unit_;
  const double d = inst->WallThickness() * length_unit_;

  const bool fr1 = !!inst->OuterFilletRadius();
  const bool fr2 = !!inst->InnerFilletRadius();

  const double r1 = fr1 ? (*inst->OuterFilletRadius()) * length_unit_ : 0.;
  const double r2 = fr2 ? (*inst->InnerFilletRadius()) * length_unit_ : 0.;

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

  auto s1 = profile_helper(
      m4, {{{-x, -y}, {r1}}, {{x, -y}, {r1}}, {{x, y}, {r1}}, {{-x, y}, {r1}}});

  auto s2 = profile_helper(m4, {{{-x + d, -y + d}, {r2}},
                                {{x - d, -y + d}, {r2}},
                                {{x - d, y - d}, {r2}},
                                {{-x + d, y - d}, {r2}}});

  if (!s1 || !s2) {
    return nullptr;
  }

  auto f = taxonomy::cast<taxonomy::face>(s1);
  s2->external = false;
  f->children.push_back(s2);

  return f;
}
