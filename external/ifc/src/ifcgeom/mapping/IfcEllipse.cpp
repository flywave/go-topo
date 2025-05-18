#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcEllipse *inst) {
  double x = inst->SemiAxis1() * length_unit_;
  double y = inst->SemiAxis2() * length_unit_;
  const double tol = settings_.get<settings::Precision>().get();
  if (x < tol || y < tol) {
    Logger::Message(Logger::LOG_ERROR,
                    "Radius not greater than zero for:", inst);
    return nullptr;
  }

  auto el = taxonomy::make<taxonomy::ellipse>();
  el->matrix = taxonomy::cast<taxonomy::matrix4>(map(inst->Position()));

  // Open Cascade does not allow ellipses of which the minor radius
  // is greater than the major radius. Hence, in this case, the
  // ellipse is rotated. Note that special care is taken
  // when creating a trimmed curve off of an ellipse like this.
  if (y > x) {
    // @todo is a copy necesary here or can this be done in place?
    auto m4_copy = *el->matrix;
    el->matrix->components() << m4_copy.components().col(1),
        -m4_copy.components().col(0), m4_copy.components().col(2),
        m4_copy.components().col(3);
    std::swap(x, y);
  }

  el->radius = x;
  el->radius2 = y;

  return el;
}
