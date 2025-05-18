#include <ifcgeom/mapping/mapping.h>

#define mapping POSTFIX_SCHEMA(mapping)

using namespace ifcopenshell::geometry;

#ifdef SCHEMA_HAS_IfcBSplineCurveWithKnots
taxonomy::ptr
mapping::map_impl(const IfcSchema::IfcBSplineCurveWithKnots *inst) {
  auto bc = taxonomy::make<taxonomy::bspline_curve>();

  const IfcSchema::IfcCartesianPoint::list::ptr cps = inst->ControlPointsList();
  std::vector<taxonomy::point3::ptr> points;
  std::transform(cps->begin(), cps->end(), std::back_inserter(points),
                 [this](IfcSchema::IfcCartesianPoint *cp) {
                   return taxonomy::cast<taxonomy::point3>(map(cp));
                 });
  bc->control_points = points;

  bc->multiplicities = inst->KnotMultiplicities();
  bc->knots = inst->Knots();
  if (inst->as<IfcSchema::IfcRationalBSplineCurveWithKnots>()) {
    bc->weights =
        inst->as<IfcSchema::IfcRationalBSplineCurveWithKnots>()->WeightsData();
  }
  bc->degree = inst->Degree();

  return bc;
}
#endif