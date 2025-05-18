#ifndef GO_IFC_IMPL_H
#define GO_IFC_IMPL_H

#include <TopoDS_Shape.hxx>
#include <string>

#include <boost/shared_ptr.hpp>

#include <ifcgeom/IfcGeomRepresentation.h>

#include "ifc.hh"
#include "shape.hh"

struct _ifc_element_t {
  std::shared_ptr<flywave::topo::shape> shp;
  int id;
  int parent_id;
  std::string name;
  std::string guid;
};

struct _ifc_triangulation_t {
  boost::shared_ptr<IfcGeom::Representation::Triangulation> tri;
};

struct _ifc_material_t {
  ifcopenshell::geometry::taxonomy::style::ptr mtl;
};

struct _ifc_convert_t {
  std::unique_ptr<flywave::ifc::ifc_convert> ct;
};

#endif
