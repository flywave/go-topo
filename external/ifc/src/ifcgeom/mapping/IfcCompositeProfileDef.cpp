#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcCompositeProfileDef* inst) {
	// @todo double check that this is actually supported
	IfcSchema::IfcProfileDef::list::ptr profiles = inst->Profiles();
	return map_to_collection<>(this, profiles);
}
