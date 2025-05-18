#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcHalfSpaceSolid *inst) {
  IfcSchema::IfcSurface *surface = inst->BaseSurface();
  if (!surface->declaration().is(IfcSchema::IfcPlane::Class())) {
    Logger::Message(Logger::LOG_ERROR, "Unsupported BaseSurface:", surface);
    return nullptr;
  }
  auto p = taxonomy::make<taxonomy::plane>();
  p->matrix = taxonomy::cast<taxonomy::matrix4>(
      map(((IfcSchema::IfcPlane *)surface)->Position()));
  auto f = taxonomy::make<taxonomy::face>();
  f->orientation.reset(!inst->AgreementFlag());
  f->basis = p;
  auto sh = taxonomy::make<taxonomy::shell>();
  sh->children.push_back(f);
  auto so = taxonomy::make<taxonomy::solid>();
  so->children.push_back(sh);
  return so;
}
