#ifndef __FLYWAVE_IFC_CORE_HH__
#define __FLYWAVE_IFC_CORE_HH__

#include <IGESControl_Controller.hxx>
#include <Standard_Version.hxx>
#include <TopoDS_Shape.hxx>

#include <ifcgeom/IfcGeomElement.h>
#include <ifcgeom/IfcGeomFilter.h>
#include <ifcgeom/IfcGeomRenderStyles.h>
#include <ifcgeom/Iterator.h>
#include <ifcparse/IfcFile.h>

#include <array>

namespace flywave {
namespace ifc {

struct ifc_element_info {
  TopoDS_Shape shp;
  int id;
  int parent_id;
  std::string name;
  std::string guid;
};

struct geom_filter {
  geom_filter(bool include, bool traverse)
      : type(UNUSED), include(include), traverse(traverse) {}
  geom_filter() : type(UNUSED), include(false), traverse(false) {}
  enum filter_type { UNUSED, ENTITY_TYPE, LAYER_NAME, ENTITY_ARG };
  filter_type type;
  bool include;
  bool traverse;
  std::string arg;
  std::set<std::string> values;
};

struct inclusion_filter : public geom_filter {
  inclusion_filter() : geom_filter(true, false) {}
};

struct inclusion_traverse_filter : public geom_filter {
  inclusion_traverse_filter() : geom_filter(true, true) {}
};

struct exclusion_filter : public geom_filter {
  exclusion_filter() : geom_filter(false, false) {}
};

struct exclusion_traverse_filter : public geom_filter {
  exclusion_traverse_filter() : geom_filter(false, true) {}
};

struct filter_settings {

  static const std::string NAME_ARG, GUID_ARG, DESC_ARG, TAG_ARG;
  static std::array<std::string, 4> supported_args;

  inclusion_filter include_filter;
  inclusion_traverse_filter include_traverse_filter;
  exclusion_filter exclude_filter;
  exclusion_traverse_filter exclude_traverse_filter;

  static void parse_filter(geom_filter &filter,
                           const std::vector<std::string> &values) {
    if (values.size() == 0) {
      return;
    }
    std::string type = *values.begin();
    if (type == "entities") {
      filter.type = geom_filter::ENTITY_TYPE;
    } else if (type == "layers") {
      filter.type = geom_filter::LAYER_NAME;
    } else if (type == "arg") {
      filter.type = geom_filter::ENTITY_ARG;
      filter.arg = *(values.begin() + 1);
      if (std::find(supported_args.begin(), supported_args.end(), filter.arg) ==
          supported_args.end()) {
        return;
      }
    } else {
      return;
    }
    filter.values.insert(values.begin() +
                             (filter.type == geom_filter::ENTITY_ARG ? 2 : 1),
                         values.end());
  }

  static bool append_filter(const std::string &type,
                            const std::vector<std::string> &values,
                            geom_filter &filter) {
    geom_filter temp;
    parse_filter(temp, values);
    if ((filter.type != geom_filter::UNUSED && filter.type != temp.type) ||
        (!filter.arg.empty() && filter.arg != temp.arg)) {
      return false;
    }
    filter.type = temp.type;
    filter.values.insert(temp.values.begin(), temp.values.end());
    filter.arg = temp.arg;
    return true;
  }
};

class ifc_convert {
protected:
  IfcGeom::entity_filter entity_filter;
  IfcGeom::layer_filter layer_filter;
  IfcGeom::attribute_filter attribute_filter;

  std::unique_ptr<IfcParse::IfcFile> _file;

  std::vector<IfcGeom::filter_t>
  setup_filters(const std::vector<geom_filter> &);

  std::vector<geom_filter> used_filters;

  std::string _file_name;

  ifcopenshell::geometry::Settings settings;

  std::vector<IfcGeom::filter_t> filter_funcs;

  void append_element(const IfcGeom::TriangulationElement *element,
                      unsigned int &vcount_total);

public:
  ifc_convert(const std::string &filename,
              ifcopenshell::geometry::Settings settings =
                  ifcopenshell::geometry::Settings(),
              filter_settings filters = filter_settings{})
      : _file_name(filename), settings(settings) {
    if (filters.include_filter.type != geom_filter::UNUSED) {
      used_filters.push_back(filters.include_filter);
    }
    if (filters.include_traverse_filter.type != geom_filter::UNUSED) {
      used_filters.push_back(filters.include_traverse_filter);
    }
    if (filters.exclude_filter.type != geom_filter::UNUSED) {
      used_filters.push_back(filters.exclude_filter);
    }
    if (filters.exclude_traverse_filter.type != geom_filter::UNUSED) {
      used_filters.push_back(filters.exclude_traverse_filter);
    }
    setup_filters(used_filters);
  }
  ~ifc_convert() {}

  bool load();

  std::vector<ifc_element_info> get_shape();

  using triangulation_ptr =
      boost::shared_ptr<IfcGeom::Representation::Triangulation>;

  std::vector<triangulation_ptr> get_geometry();

  std::string get_version();

  const std::vector<IfcGeom::filter_t> &get_filter_funcs() {
    return filter_funcs;
  }
};

inline std::string get_version(const std::string &f) {
  IfcParse::IfcFile fl{f};
  return fl.good() == IfcParse::file_open_status::SUCCESS
             ? fl.header().file_description().implementation_level()
             : std::string();
}

inline std::unique_ptr<ifc_convert> get_convert(const std::string &f) {
  return std::unique_ptr<ifc_convert>(new ifc_convert{f});
}

} // namespace ifc
} // namespace flywave

#endif // __FLYWAVE_IFC_CORE_HH__
