#ifndef IFC_DATA_STRUCTS_HH
#define IFC_DATA_STRUCTS_HH

#include <ifcparse/IfcFile.h>
#include <ifcdata/ifc_data.h>

#include <boost/dynamic_bitset.hpp>
#include <boost/optional.hpp>
#include <boost/variant.hpp>

#include <map>
#include <string>
#include <vector>

namespace ifcopenshell {
namespace data {

struct IfcHeader {
  struct FileDescription {
    std::string implementation_level;
    std::vector<std::string> description;
  } file_description;

  struct FileName {
    std::string name;
    std::vector<std::string> author;
    std::vector<std::string> organization;
    std::string time_stamp;
    std::string preprocessor_version;
    std::string originating_system;
    std::string authorization;
  } file_name;

  struct FileSchema {
    std::vector<std::string> schema_identifiers;
  } file_schema;
};

struct IfcUnit {
  std::string type;
  std::string name;
  boost::optional<double> SI_equivalent;
};

struct IfcProperty {
  std::string name;
  boost::variant<boost::blank, int, bool, double, std::string,
                 boost::dynamic_bitset<>, std::vector<int>, std::vector<double>,
                 std::vector<std::string>, std::vector<boost::dynamic_bitset<>>,
                 std::vector<std::vector<int>>,
                 std::vector<std::vector<double>>>
      value;
  std::string type;
};

struct IfcPropertySet {
  std::string id;
  std::string name;
  std::vector<IfcProperty> properties;
};

struct IfcQuantity {
  std::string type;
  std::string name;
  double value;
  std::string unit;
};

struct IfcElementQuantity {
  std::string id;
  std::string name;
  std::vector<IfcQuantity> quantities;
};

struct IfcTaskTime {
  std::string schedule_start;
  std::string schedule_finish;
  std::string actual_start;
  std::string actual_finish;
  std::string free_float;
  std::string total_float;
  bool is_critical;
};

struct IfcTask {
  std::string id;
  std::string name;
  std::string status;
  std::string description;
  std::string object_type;
  std::string start_time;
  std::string end_time;
  std::string duration;

  boost::optional<IfcTaskTime> task_time;
  std::vector<std::string> predecessor_tasks;
  std::vector<std::string> successor_tasks;
  std::vector<std::string> input_objects;
  std::vector<std::string> output_objects;
  std::vector<std::string> resources;
  std::vector<std::string> controls;
  std::vector<IfcTask> subtasks;
};

struct IfcWorkTime {
  std::string name;
  std::string start_time;
  std::string end_time;
};

struct IfcWorkCalendar {
  std::string id;
  std::string name;
  std::vector<IfcWorkTime> working_times;
};

struct IfcWorkSchedule {
  std::string id;
  std::string name;
  std::vector<IfcTask> tasks;
};

struct IfcWorkPlan {
  std::string id;
  std::string name;
  std::vector<std::string> work_schedule_ids;
};

struct IfcConnection {
  std::string id;
  std::string relating_element_id;
  std::string related_element_id;
};

struct IfcTypeObject {
  std::string id;
  std::string name;
  std::vector<IfcPropertySet> property_sets;
};

struct IfcLayer {
  std::string name;
  std::string id;
  std::vector<std::string> assigned_elements;
  std::string description;
};

struct IfcMaterial {
  std::string id;
  std::string name;
  std::string description;
  std::string category;
};

struct IfcGroup {
  std::string id;
  std::string name;
  std::vector<std::string> member_ids;
};

struct IfcData {
  IfcHeader header;
  std::vector<IfcUnit> units;
  std::vector<IfcPropertySet> properties;
  std::vector<IfcElementQuantity> quantities;
  std::vector<IfcWorkSchedule> work_schedules;
  std::vector<IfcWorkPlan> work_plans;
  std::vector<IfcWorkCalendar> calendars;
  std::vector<IfcConnection> connections;
  std::vector<IfcTypeObject> types;
  std::vector<IfcLayer> layers;
  std::vector<IfcMaterial> materials;
  std::vector<IfcGroup> groups;
};

IfcData read_data(IfcParse::IfcFile *file);


} // namespace data
} // namespace ifcopenshell

#endif // IFC_DATA_STRUCTS_HH
