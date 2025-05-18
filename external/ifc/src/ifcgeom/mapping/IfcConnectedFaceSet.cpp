#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcConnectedFaceSet* inst) {
	auto shell = map_to_collection<taxonomy::shell>(this, inst->CfsFaces());
	if (!shell) {
		return nullptr;
	}
	shell->closed = inst->declaration().is(IfcSchema::IfcClosedShell::Class());
	return shell;
}
