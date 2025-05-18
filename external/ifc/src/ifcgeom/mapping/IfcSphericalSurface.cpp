#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

#ifdef SCHEMA_HAS_IfcSphericalSurface

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcSphericalSurface *inst) {
  return nullptr;

  /*
  gp_Trsf trsf;
  IfcGeom::Kernel::convert(inst->Position(), trsf);

  // IfcElementarySurface.Position has unit scale factor
  face = BRepBuilderAPI_MakeFace(new Geom_SphericalSurface(gp::XOY(),
  inst->Radius() * length_unit_), getValue(GV_PRECISION)).Face().Moved(trsf);
  return true;
  */
}

#endif
