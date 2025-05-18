#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

#include <boost/math/constants/constants.hpp>

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcTrimmedCurve *inst) {
  static const double pi = boost::math::constants::pi<double>();

  IfcSchema::IfcCurve *basis_curve = inst->BasisCurve();
  bool isConic = basis_curve->declaration().is(IfcSchema::IfcConic::Class());
  double parameterFactor = isConic ? angle_unit_ : length_unit_;

  auto tc = taxonomy::make<taxonomy::edge>();
  tc->basis = map(inst->BasisCurve());

  bool trim_cartesian =
      inst->MasterRepresentation() !=
      IfcSchema::IfcTrimmingPreference::IfcTrimmingPreference_PARAMETER;
  auto trims1 = inst->Trim1();
  auto trims2 = inst->Trim2();

  // reversed orientation handling happens in geometry kernel
  unsigned sense_agreement = 0;
  double flts[2];
  taxonomy::point3::ptr pnts[2];
  bool has_flts[2] = {false, false};
  bool has_pnts[2] = {false, false};

  tc->curve_sense = inst->SenseAgreement();

  for (auto it = trims1->begin(); it != trims1->end(); it++) {
    auto i = *it;
    if (i->as<IfcSchema::IfcCartesianPoint>()) {
      pnts[sense_agreement] = taxonomy::cast<taxonomy::point3>(map(i));
      has_pnts[sense_agreement] = true;
    } else if (i->as<IfcSchema::IfcParameterValue>()) {
      const double value = *i->as<IfcSchema::IfcParameterValue>();
      flts[sense_agreement] = value * parameterFactor;
      has_flts[sense_agreement] = true;
    }
  }

  for (auto it = trims2->begin(); it != trims2->end(); it++) {
    auto i = *it;
    if (i->as<IfcSchema::IfcCartesianPoint>()) {
      pnts[1 - sense_agreement] = taxonomy::cast<taxonomy::point3>(map(i));
      has_pnts[1 - sense_agreement] = true;
    } else if (i->as<IfcSchema::IfcParameterValue>()) {
      const double value = *i->as<IfcSchema::IfcParameterValue>();
      flts[1 - sense_agreement] = value * parameterFactor;
      has_flts[1 - sense_agreement] = true;
    }
  }

  const double tol = settings_.get<settings::Precision>().get();

  trim_cartesian &= has_pnts[0] && has_pnts[1];
  bool trim_cartesian_failed = !trim_cartesian;
  if (trim_cartesian) {
    if ((pnts[0]->ccomponents() - pnts[1]->ccomponents()).norm() < (2 * tol)) {
      Logger::Message(
          Logger::LOG_WARNING,
          "Skipping segment with length below tolerance level:", inst);
      return nullptr;
    }
    tc->start = pnts[0];
    tc->end = pnts[1];
  } else if (has_flts[0] && has_flts[1]) {
    // The Geom_Line is constructed from a gp_Pnt and gp_Dir, whereas the
    // IfcLine is defined by an IfcCartesianPoint and an IfcVector with
    // Magnitude. Because the vector is normalised when passed to Geom_Line
    // constructor the magnitude needs to be factored in with the
    // IfcParameterValue here.
    if (basis_curve->declaration().is(IfcSchema::IfcLine::Class())) {
      IfcSchema::IfcLine *line = static_cast<IfcSchema::IfcLine *>(basis_curve);
      const double magnitude = line->Dir()->Magnitude();
      flts[0] *= magnitude;
      flts[1] *= magnitude;
    }
    if (basis_curve->declaration().is(IfcSchema::IfcEllipse::Class())) {
      IfcSchema::IfcEllipse *ellipse =
          static_cast<IfcSchema::IfcEllipse *>(basis_curve);
      double x = ellipse->SemiAxis1() * length_unit_;
      double y = ellipse->SemiAxis2() * length_unit_;
      const bool rotated = y > x;
      // @todo do we apply this rotation here or in the kernel.
      if (rotated) {
        flts[0] -= pi / 2.;
        flts[1] -= pi / 2.;
      }
    }

    double radius = 1.0;
    if (auto typed_circle = taxonomy::dcast<taxonomy::circle>(tc->basis)) {
      radius = typed_circle->radius;
    } else if (auto typed_ellipse =
                   taxonomy::dcast<taxonomy::ellipse>(tc->basis)) {
      radius = (typed_ellipse->radius + typed_ellipse->radius2) / 2.;
    }

    // Fix from @sanderboer to compare using model tolerance, see #744
    // Made dependent on radius, see #928

    // A good criterion for determining whether to take full curve
    // or trimmed segment would be whether there are other curve segments or
    // this is the only one.
    boost::optional<size_t> num_segments;
    auto segment = inst->file_->getInverse(
        inst->id(), &IfcSchema::IfcCompositeCurveSegment::Class(), -1);
    if (segment->size() == 1) {
      auto comp =
          (*segment->begin())
              ->file_->getInverse((*segment->begin())->id(),
                                  &IfcSchema::IfcCompositeCurve::Class(), -1);
      if (comp->size() == 1) {
        num_segments = (*comp->begin())
                           ->as<IfcSchema::IfcCompositeCurve>()
                           ->Segments()
                           ->size();
      }
    }

    // @todo is 100. not too much? Check with the original issue.
    const double precision_markup =
        settings_.get<settings::PrecisionFactor>().get() == 1. ? 1. : 100.;

    if (isConic && std::fabs(fmod(flts[1] - flts[0], pi * 2.)) <
                       precision_markup * tol / (2 * pi * radius)) {
      flts[0] = 0.;
      flts[1] = 2 * pi;
    }

    tc->start = flts[0];
    tc->end = flts[1];

    /*
    // @todo
    if (num_segments && *num_segments > 1) {
            TopoDS_Vertex v0, v1;
            TopExp::Vertices(e, v0, v1);
            if (v0.IsSame(v1)) {
                    Logger::Warning("Skipping degenerate segment", l);
                    return false;
            }
    }
    */
  }

  return tc;
}
