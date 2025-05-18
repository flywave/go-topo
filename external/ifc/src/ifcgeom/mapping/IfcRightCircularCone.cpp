#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcRightCircularCone* inst) {
	// @todo
	return nullptr;
	/*
	const double r = inst->BottomRadius() * length_unit_;
	const double h = inst->Height() * length_unit_;

	BRepPrimAPI_MakeCone builder(r, 0., h);
	gp_Trsf trsf;
	IfcGeom::Kernel::convert(inst->Position(),trsf);

	// IfcCsgPrimitive3D.Position has unit scale factor
	shape = builder.Solid().Moved(trsf);

	return true;
	*/
}
