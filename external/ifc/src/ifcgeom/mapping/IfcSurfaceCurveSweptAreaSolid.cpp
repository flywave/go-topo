#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcSurfaceCurveSweptAreaSolid* inst) {
	taxonomy::face::ptr f = taxonomy::cast<taxonomy::face>(map(inst->SweptArea()));

	taxonomy::matrix4::ptr matrix;
	bool has_position = true;
#ifdef SCHEMA_IfcSweptAreaSolid_Position_IS_OPTIONAL
	has_position = inst->Position() != nullptr;
#endif
	if (has_position) {
		matrix = taxonomy::cast<taxonomy::matrix4>(map(inst->Position()));
	}

	auto scs = taxonomy::make<taxonomy::sweep_along_curve>(matrix, f, map(inst->ReferenceSurface()), map(inst->Directrix()));
	scs->matrix = matrix;

	return scs;
}
