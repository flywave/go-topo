#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

#define ALMOST_ZERO 1.e-7;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcCircle *inst) {
  const double r = inst->Radius() * length_unit_;
  if (r < settings_.get<settings::Precision>().get()) {
    Logger::Message(Logger::LOG_ERROR,
                    "Radius not greater than zero for:", inst);
    return nullptr;
  }

  IfcSchema::IfcAxis2Placement *placement = inst->Position();
  auto c = taxonomy::make<taxonomy::circle>();
  c->radius = r;
  c->matrix = taxonomy::cast<taxonomy::matrix4>(map(placement));

  return c;
}
