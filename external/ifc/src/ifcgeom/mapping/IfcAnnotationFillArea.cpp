#include <ifcgeom/mapping/mapping.h>

#define mapping POSTFIX_SCHEMA(mapping)

using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcAnnotationFillArea *inst) {
  auto loop = taxonomy::cast<taxonomy::loop>(map(inst->OuterBoundary()));
  if (loop) {
    auto face = taxonomy::make<taxonomy::face>();
    loop->external = true;
    face->children = {loop};

    if (inst->InnerBoundaries()) {
      IfcSchema::IfcCurve::list::ptr inner_boundaries =
          *inst->InnerBoundaries();
      for (auto &v : *inner_boundaries) {
        auto inner_loop = taxonomy::cast<taxonomy::loop>(map(v));
        if (inner_loop) {
          inner_loop->external = false;
          face->children.push_back(inner_loop);
        }
      }
    }

    return face;
  } else {
    return nullptr;
  }
}
