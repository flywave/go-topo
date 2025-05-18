#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

#ifdef SCHEMA_HAS_IfcSurfaceCurve
taxonomy::ptr mapping::map_impl(const IfcSchema::IfcSurfaceCurve* inst) {
	// @todo take into account PCurves.
	return map(inst->Curve3D());
}
#endif
