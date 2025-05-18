#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcCompositeCurve *inst) {
  auto loop = taxonomy::make<taxonomy::loop>();
  taxonomy::piecewise_function::spans_t spans;

#ifdef SCHEMA_HAS_IfcSegment
  // 4x3
  IfcSchema::IfcSegment::list::ptr segments = inst->Segments();
#else
  IfcSchema::IfcCompositeCurveSegment::list::ptr segments = inst->Segments();
#endif

  for (auto &segment : *segments) {
    if (segment->as<IfcSchema::IfcCompositeCurveSegment>() &&
        segment->as<IfcSchema::IfcCompositeCurveSegment>()
            ->ParentCurve()
            ->as<IfcSchema::IfcLine>()) {
      Logger::Notice("Infinite IfcLine used as ParentCurve of segment, "
                     "treating as a segment",
                     segment);
      double u0 = 0.0;
      double u1 = segment->as<IfcSchema::IfcCompositeCurveSegment>()
                      ->ParentCurve()
                      ->as<IfcSchema::IfcLine>()
                      ->Dir()
                      ->Magnitude() *
                  length_unit_;
      if (u1 < settings_.get<settings::Precision>().get()) {
        Logger::Warning("Segment length below tolerance", segment);
      }

      auto e = taxonomy::make<taxonomy::edge>();
      e->basis = map(
          segment->as<IfcSchema::IfcCompositeCurveSegment>()->ParentCurve());
      e->start = u0;
      e->end = u1;
      e->curve_sense.reset(
          segment->as<IfcSchema::IfcCompositeCurveSegment>()->SameSense());

      loop->children.push_back(e);
    } else if (segment->as<IfcSchema::IfcCompositeCurveSegment>()) {
      auto crv = map(
          segment->as<IfcSchema::IfcCompositeCurveSegment>()->ParentCurve());
      if (crv) {
        if (!segment->as<IfcSchema::IfcCompositeCurveSegment>()->SameSense()) {
          crv->reverse();
        }
        if (crv->kind() == taxonomy::EDGE) {
          auto ecrv = taxonomy::cast<taxonomy::edge>(crv);
          loop->children.push_back(ecrv);
        } else if (crv->kind() == taxonomy::LOOP) {
          for (auto &s : taxonomy::cast<taxonomy::loop>(crv)->children) {
            loop->children.push_back(s);
          }
        }
      }
    }
#ifdef SCHEMA_HAS_IfcCurveSegment
    else if (segment->as<IfcSchema::IfcCurveSegment>()) {
      // @todo check that we don't get a mixture of implicit and explicit
      // definitions
      auto crv = map(segment->as<IfcSchema::IfcCurveSegment>());
      if (crv && crv->kind() == taxonomy::LOOP) {
        for (auto &s : taxonomy::cast<taxonomy::loop>(crv)->children) {
          loop->children.push_back(s);
        }
      } else if (auto fi = taxonomy::dcast<taxonomy::function_item>(crv);
                 crv && fi /*crv->kind() == taxonomy::FUNCTION_ITEM*/) {
        // crv->kind() is polymorphic and the kind of the actual function_item
        // is returned. PWF can have spans of any FUNCTION_ITEM for this reason,
        // a dynamic cast is used and if crv is a function_item it is added to
        // the span
        spans.push_back(fi);
      } else if (!crv) {
        return nullptr;
      }
    }
#endif
  }

  if (spans.empty()) {
    aggregate_of_instance::ptr profile = inst->file_->getInverse(
        inst->id(), &IfcSchema::IfcProfileDef::Class(), -1);
    const bool force_close = profile && profile->size() > 0;
    loop->closed = force_close;
    loop->instance = inst;
    return loop;
  } else {
    auto pwf = taxonomy::make<taxonomy::piecewise_function>(0.0, spans, inst);
    return pwf;
  }
}
