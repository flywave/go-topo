#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcDerivedProfileDef *inst) {
  auto it = map(inst->ParentProfile());
  if (it == nullptr) {
    return nullptr;
  }
  // @todo we mutate it so we need to clone otherwise we alter the cached item.
  it = taxonomy::item::ptr(it->clone_());

  taxonomy::matrix4::ptr m;
  bool is_mirror = false;
#ifdef SCHEMA_HAS_IfcMirroredProfileDef
  if (inst->as<IfcSchema::IfcMirroredProfileDef>()) {
    m = taxonomy::make<taxonomy::matrix4>();
    // @todo test
    m->components().col(0) *= -1.;
    is_mirror = true;
  }
#endif
  if (!is_mirror) {
    m = taxonomy::cast<taxonomy::matrix4>(map(inst->Operator()));
    if (!m) {
      return nullptr;
    }
  }
  if (!taxonomy::cast<taxonomy::geom_item>(it)->matrix) {
    // @todo should this not be initialized by default? matrix4 already has a
    // 'lazy identity' mechanism.
    taxonomy::cast<taxonomy::geom_item>(it)->matrix =
        taxonomy::make<taxonomy::matrix4>();
  }
  taxonomy::cast<taxonomy::geom_item>(it)->matrix->components() *=
      m->ccomponents();
  return it;
}
