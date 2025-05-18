#ifndef IFCGEOMRENDERSTYLES_H
#define IFCGEOMRENDERSTYLES_H

#include <ifcgeom/ifc_geom_api.h>
#include <ifcgeom/taxonomy.h>

#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/optional.hpp>

#include <memory>
#include <sstream>

namespace IfcGeom {
IFC_GEOM_API const ifcopenshell::geometry::taxonomy::style::ptr &
get_default_style(const std::string &ifc_type);

IFC_GEOM_API ifcopenshell::geometry::taxonomy::style::ptr &
update_default_style(const std::string &ifc_type);

IFC_GEOM_API void set_default_style_file(const std::string &json_file);
} // namespace IfcGeom

#endif
