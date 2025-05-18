#include <ifcgeom/function_item_evaluator.h>
#include <ifcgeom/mapping/mapping.h>
#include <ifcgeom/profile_helper.h>

#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

#if defined SCHEMA_HAS_IfcPointByDistanceExpression

taxonomy::ptr
mapping::map_impl(const IfcSchema::IfcPointByDistanceExpression *inst) {
  auto u = (*inst->DistanceAlong()->as<IfcSchema::IfcLengthMeasure>()) *
           length_unit_;
  auto basis_curve = map(inst->BasisCurve());
  taxonomy::function_item::ptr curve =
      taxonomy::dcast<taxonomy::function_item>(basis_curve);
  if (!curve) {
    curve = taxonomy::dcast<taxonomy::piecewise_function>(basis_curve);
  }

  function_item_evaluator evaluator(settings_, curve);
  auto m = evaluator.evaluate(u);

  auto o = m.col(3).head<3>();
  auto z = m.col(2).head<3>();
  auto x = m.col(0).head<3>();

  if (inst->OffsetLateral().is_initialized()) {
    auto offset_lateral = inst->OffsetLateral().get() * length_unit_;
    auto y = Eigen::Vector3d(m.col(1)(0), m.col(1)(1), m.col(1)(2));
    o += offset_lateral * y;
  }

  if (inst->OffsetVertical().is_initialized()) {
    auto offset_vertical = inst->OffsetVertical().get() * length_unit_;
    o += offset_vertical * z;
  }

  if (inst->OffsetLongitudinal().is_initialized()) {
    auto offset_longitudinal = inst->OffsetLongitudinal().get() * length_unit_;
    o += offset_longitudinal * x;
  }

  return taxonomy::make<taxonomy::matrix4>(o, z, x);
}

#endif
