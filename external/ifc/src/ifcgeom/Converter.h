#ifndef ITERATOR_KERNEL_H
#define ITERATOR_KERNEL_H

#include <ifcgeom/AbstractKernel.h>
#include <ifcgeom/ConversionResult.h>
#include <ifcgeom/ConversionSettings.h>
#include <ifcgeom/IfcGeomElement.h>
#include <ifcgeom/abstract_mapping.h>
#include <ifcparse/IfcFile.h>

#include <boost/function.hpp>

namespace ifcopenshell {
namespace geometry {

class Converter {
public:
  typedef boost::shared_ptr<IfcGeom::Representation::BRep> brep_ptr;

private:
  ifcopenshell::geometry::abstract_mapping *mapping_;
  ifcopenshell::geometry::kernels::AbstractKernel *kernel_;
  ifcopenshell::geometry::Settings settings_;
  std::map<ifcopenshell::geometry::taxonomy::ptr, brep_ptr,
           ifcopenshell::geometry::taxonomy::less_functor>
      cache_;

public:
  ifcopenshell::geometry::kernels::AbstractKernel *kernel() { return kernel_; }

  Converter(IfcParse::IfcFile *file,
            ifcopenshell::geometry::Settings &settings);

  ~Converter();

  ifcopenshell::geometry::abstract_mapping *mapping() const { return mapping_; }

  double total_map_time = 0.;
  double total_geom_time = 0.;

  IfcGeom::ConversionResults convert(IfcUtil::IfcBaseClass *item);

  IfcGeom::BRepElement *create_brep_for_representation_and_product(
      const IfcUtil::IfcBaseEntity *representation,
      const IfcUtil::IfcBaseEntity *product);
  // IfcGeom::BRepElement* create_brep_for_processed_representation(const
  // IfcUtil::IfcBaseEntity* representation, const IfcUtil::IfcBaseEntity*
  // product, IfcGeom::BRepElement* brep);

  IfcGeom::BRepElement *create_brep_for_representation_and_product(
      ifcopenshell::geometry::taxonomy::ptr,
      const IfcUtil::IfcBaseEntity *product,
      const ifcopenshell::geometry::taxonomy::matrix4::ptr &place);
  IfcGeom::BRepElement *create_brep_for_processed_representation(
      const IfcUtil::IfcBaseEntity *product,
      const ifcopenshell::geometry::taxonomy::matrix4::ptr &place,
      IfcGeom::BRepElement *);

  const ifcopenshell::geometry::Settings &settings() { return settings_; }
};
} // namespace geometry
} // namespace ifcopenshell

#endif