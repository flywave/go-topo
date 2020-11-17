#ifndef __FLYWAVE_IFC_CORE_HH__
#define __FLYWAVE_IFC_CORE_HH__

#include <IGESControl_Controller.hxx>
#include <Standard_Version.hxx>
#include <TopoDS_Shape.hxx>

#include <array>

#include <ifc23.h>
#include <ifc4.h>

namespace flywave {
namespace ifc {

class visitor {
public:
  virtual ~visitor() {}
  virtual void
  apply(const ifc23::IfcGeom::TriangulationElement<double> *element);
  virtual void
  apply(const ifc4::IfcGeom::TriangulationElement<double> *element);
};

class base_convert {
public:
  virtual std::vector<TopoDS_Shape> get_shape()=0;

  virtual void process_with_callback(visitor &vst)=0;
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

#define GEN_CONVERT(NAME_SPACE)                                                \
  class NAME_SPACE##_serializer_settings                                       \
      : public NAME_SPACE::IfcGeom::IteratorSettings {                         \
  public:                                                                      \
    enum Setting {                                                             \
      USE_ELEMENT_NAMES =                                                      \
          1 << (NAME_SPACE::IfcGeom::IteratorSettings::NUM_SETTINGS + 1),      \
      USE_ELEMENT_GUIDS =                                                      \
          1 << (NAME_SPACE::IfcGeom::IteratorSettings::NUM_SETTINGS + 2),      \
      USE_MATERIAL_NAMES =                                                     \
          1 << (NAME_SPACE::IfcGeom::IteratorSettings::NUM_SETTINGS + 3),      \
      USE_ELEMENT_TYPES =                                                      \
          1 << (NAME_SPACE::IfcGeom::IteratorSettings::NUM_SETTINGS + 4),      \
      USE_ELEMENT_HIERARCHY =                                                  \
          1 << (NAME_SPACE::IfcGeom::IteratorSettings::NUM_SETTINGS + 5),      \
      NUM_SETTINGS = 5                                                         \
    };                                                                         \
                                                                               \
    NAME_SPACE##_serializer_settings() : precision(DEFAULT_PRECISION) {        \
      memset(offset, 0, sizeof(offset));                                       \
    }                                                                          \
    double offset[3];                                                          \
                                                                               \
    short precision;                                                           \
                                                                               \
    enum { DEFAULT_PRECISION = 15 };                                           \
  };                                                                           \
                                                                               \
  class NAME_SPACE##_convert : public base_convert {                           \
  protected:                                                                   \
    NAME_SPACE::IfcGeom::entity_filter entity_filter;                          \
    NAME_SPACE::IfcGeom::layer_filter layer_filter;                            \
    NAME_SPACE::IfcGeom::attribute_filter attribute_filter;                    \
                                                                               \
    std::vector<NAME_SPACE::IfcGeom::filter_t>                                 \
    setup_filters(const std::vector<geom_filter> &);                           \
                                                                               \
    std::vector<geom_filter> used_filters;                                     \
                                                                               \
    NAME_SPACE##_serializer_settings settings;                                 \
                                                                               \
    std::string _file_name;                                                    \
                                                                               \
    std::vector<NAME_SPACE::IfcGeom::filter_t> filter_funcs;                   \
                                                                               \
    void append_element(                                                       \
        const NAME_SPACE::IfcGeom::TriangulationElement<double> *element,      \
        unsigned int &vcount_total);                                           \
                                                                               \
  public:                                                                      \
    NAME_SPACE##_convert(const std::string &filename,                          \
                         NAME_SPACE##_serializer_settings set =                \
                             NAME_SPACE##_serializer_settings{},               \
                         filter_settings filters = filter_settings{})          \
        : settings(set), _file_name(filename) {                                \
      if (filters.include_filter.type != geom_filter::UNUSED) {                \
        used_filters.push_back(filters.include_filter);                        \
      }                                                                        \
      if (filters.include_traverse_filter.type != geom_filter::UNUSED) {       \
        used_filters.push_back(filters.include_traverse_filter);               \
      }                                                                        \
      if (filters.exclude_filter.type != geom_filter::UNUSED) {                \
        used_filters.push_back(filters.exclude_filter);                        \
      }                                                                        \
      if (filters.exclude_traverse_filter.type != geom_filter::UNUSED) {       \
        used_filters.push_back(filters.exclude_traverse_filter);               \
      }                                                                        \
      filter_funcs = setup_filters(used_filters);                              \
    }                                                                          \
    ~NAME_SPACE##_convert() {}                                                 \
                                                                               \
    std::vector<TopoDS_Shape> get_shape();                                     \
                                                                               \
    void process_with_callback(visitor &vst);                                  \
  };

GEN_CONVERT(ifc23)
GEN_CONVERT(ifc4)

inline std::unique_ptr<base_convert> get_convert(const std::string &f) {
   ifc23::IfcParse::IfcFile fl{&ifc23::Ifc2x3::get_schema()};
  auto v = fl.GetVersion(f);
  if (v == ifc23::Ifc2x3::Identifier) {
    return std::make_unique<ifc23_convert>(ifc23_convert{f});
  } else if (v == ifc4::Ifc4::Identifier) {
    return std::make_unique<ifc4_convert>(ifc4_convert{f});
  }
  return std::unique_ptr<ifc23_convert>(nullptr);
}

inline void ifc_register_schema() {
  static ifc23::IfcParse::schema_definition schem23 = ifc23::Ifc2x3::get_schema();
  static ifc4::IfcParse::schema_definition schem4 = ifc4::Ifc4::get_schema();
  ifc23::IfcParse::register_schema(&schem23);
  ifc4::IfcParse::register_schema(&schem4);
}

} // namespace ifc
} // namespace flywave

#endif // __FLYWAVE_IFC_CORE_HH__
