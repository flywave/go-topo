#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr
mapping::map_impl(const IfcSchema::IfcRightCircularCylinder *inst) {
  // @todo
  return nullptr;
  /*

  const double r = inst->Radius() * length_unit_;
  const double h = inst->Height() * length_unit_;

  BRepPrimAPI_MakeCylinder builder(r, h);
  gp_Trsf trsf;
  IfcGeom::Kernel::convert(inst->Position(),trsf);

  // IfcCsgPrimitive3D.Position has unit scale factor
  shape = builder.Solid().Moved(trsf);

  return true;
  */
}
