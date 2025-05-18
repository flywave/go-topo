#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcManifoldSolidBrep *inst) {
  IfcSchema::IfcClosedShell::list::ptr voids(
      new IfcSchema::IfcClosedShell::list);
  if (inst->declaration().is(IfcSchema::IfcFacetedBrepWithVoids::Class())) {
    voids = inst->as<IfcSchema::IfcFacetedBrepWithVoids>()->Voids();
  }
#ifdef SCHEMA_HAS_IfcAdvancedBrepWithVoids
  if (inst->declaration().is(IfcSchema::IfcAdvancedBrepWithVoids::Class())) {
    voids = inst->as<IfcSchema::IfcAdvancedBrepWithVoids>()->Voids();
  }
#endif

  taxonomy::solid::ptr solid;
  if (voids->size()) {
    solid = map_to_collection<taxonomy::solid>(this, voids);
  } else {
    solid = taxonomy::make<taxonomy::solid>();
  }
  solid->children.insert(solid->children.begin(),
                         taxonomy::cast<taxonomy::shell>(map(inst->Outer())));

  return solid;
}
