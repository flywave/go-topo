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
  std::string type;
};

struct _ifc_triangulation_t {
  boost::shared_ptr<IfcGeom::Representation::Triangulation> tri;
};

struct _ifc_triangulation_material_t {
  ifcopenshell::geometry::taxonomy::style::ptr mtl;
};

struct _ifc_convert_t {
  std::unique_ptr<flywave::ifc::ifc_convert> ct;
};

struct _ifc_data_t {
  std::unique_ptr<ifcopenshell::data::IfcData> data;
};

struct _ifc_header_t {
  ifcopenshell::data::IfcHeader header;
};
struct _ifc_unit_t {
  ifcopenshell::data::IfcUnit unit;
};

struct _ifc_property_t {
  ifcopenshell::data::IfcProperty property;
};

struct _ifc_property_set_t {
  ifcopenshell::data::IfcPropertySet ps;
};

struct _ifc_quantity_t {
  ifcopenshell::data::IfcQuantity quantity;
};

struct _ifc_element_quantity_t {
  ifcopenshell::data::IfcElementQuantity quantity;
};

struct _ifc_task_time_t {
  ifcopenshell::data::IfcTaskTime time;
};

struct _ifc_task_t {
  ifcopenshell::data::IfcTask task;
};

struct _ifc_work_time_t {
  ifcopenshell::data::IfcWorkTime tm;
};

struct _ifc_work_calendar_t {
  ifcopenshell::data::IfcWorkCalendar wc;
};

struct _ifc_work_schedule_t {
  ifcopenshell::data::IfcWorkSchedule ws;
};

struct _ifc_work_plan_t {
  ifcopenshell::data::IfcWorkPlan wp;
};

struct _ifc_connection_t {
  ifcopenshell::data::IfcConnection con;
};

struct _ifc_type_object_t {
  ifcopenshell::data::IfcTypeObject obj;
};

struct _ifc_layer_t {
  ifcopenshell::data::IfcLayer lyr;
};

struct _ifc_material_t {
  ifcopenshell::data::IfcMaterial mtl;
};

struct _ifc_group_t {
  ifcopenshell::data::IfcGroup group;
};

struct _ifc_time_period_t {
  ifcopenshell::data::IfcTimePeriod tp;
};

struct _ifc_recurrence_pattern_t {
  ifcopenshell::data::IfcRecurrencePattern rp;
};

#endif
