#include <ifcgeom/mapping/mapping.h>

#define mapping POSTFIX_SCHEMA(mapping)

using namespace ifcopenshell::geometry;

#ifdef SCHEMA_HAS_IfcBSplineSurfaceWithKnots

taxonomy::ptr
mapping::map_impl(const IfcSchema::IfcBSplineSurfaceWithKnots *inst) {
  auto bs = taxonomy::make<taxonomy::bspline_surface>();

  auto cps = inst->ControlPointsList();
  std::transform(
      cps->begin(), cps->end(), std::back_inserter(bs->control_points),
      [this](const std::vector<IfcSchema::IfcCartesianPoint *> &inner) {
        std::vector<taxonomy::point3::ptr> ps;
        std::transform(inner.begin(), inner.end(), std::back_inserter(ps),
                       [this](IfcSchema::IfcCartesianPoint *cp) {
                         return taxonomy::cast<taxonomy::point3>(map(cp));
                       });
        return ps;
      });

  bs->multiplicities = {inst->UMultiplicities(), inst->VMultiplicities()};
  bs->knots = {inst->UKnots(), inst->VKnots()};
  if (inst->as<IfcSchema::IfcRationalBSplineSurfaceWithKnots>()) {
    bs->weights = inst->as<IfcSchema::IfcRationalBSplineSurfaceWithKnots>()
                      ->WeightsData();
  }
  bs->degree = {inst->UDegree(), inst->VDegree()};

  return bs;
}

#endif
