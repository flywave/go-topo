#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)

using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcBlock* inst) {
	const double dx = inst->XLength() * length_unit_;
	const double dy = inst->YLength() * length_unit_;
	const double dz = inst->ZLength() * length_unit_;

	auto solid = create_box(dx, dy, dz);
	solid->matrix = taxonomy::cast<taxonomy::matrix4>(map(inst->Position()));

	return solid;
}
