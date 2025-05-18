#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

#include <boost/math/constants/constants.hpp>

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcRevolvedAreaSolid *inst) {
  const double ang = inst->Angle() * angle_unit_;

  taxonomy::cast<taxonomy::face>(map(inst->SweptArea()));

  boost::optional<double> angle;

  taxonomy::matrix4::ptr matrix;
  bool has_position = true;
#ifdef SCHEMA_IfcSweptAreaSolid_Position_IS_OPTIONAL
  has_position = inst->Position() != nullptr;
#endif
  if (has_position) {
    matrix = taxonomy::cast<taxonomy::matrix4>(map(inst->Position()));
  }

  if (ang < boost::math::constants::pi<double>() * 2. - 1.e-5) {
    angle = ang;
  }

  return taxonomy::make<taxonomy::revolve>(
      matrix, taxonomy::cast<taxonomy::face>(map(inst->SweptArea())),
      taxonomy::cast<taxonomy::point3>(map(inst->Axis()->Location())),
      taxonomy::cast<taxonomy::direction3>(map(inst->Axis()->Axis())), angle);
}
