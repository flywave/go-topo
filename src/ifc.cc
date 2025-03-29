#include "ifc.hh"
#include <IfcFile.h>
#include <IfcGeomIterator.h>
#include <IfcParse.h>
#include <boost/program_options.hpp>

namespace flywave {
namespace ifc {

const std::string filter_settings::NAME_ARG = "Name";
const std::string filter_settings::GUID_ARG = "GlobalId";
const std::string filter_settings::DESC_ARG = "Description";
const std::string filter_settings::TAG_ARG = "Tag";
std::array<std::string, 4> filter_settings::supported_args{
    {NAME_ARG, GUID_ARG, DESC_ARG, TAG_ARG}};

#define GEN_CODE(NS)                                                           \
  void NS##_convert::setup_filters(const std::vector<geom_filter> &filters) {  \
    BOOST_FOREACH (const geom_filter &f, filters) {                            \
      if (f.type == geom_filter::ENTITY_TYPE) {                                \
        entity_filter.include = f.include;                                     \
        entity_filter.traverse = f.traverse;                                   \
        entity_filter.entity_names = f.values;                                 \
      } else if (f.type == geom_filter::LAYER_NAME) {                          \
        layer_filter.include = f.include;                                      \
        layer_filter.traverse = f.traverse;                                    \
        layer_filter.populate(f.values);                                       \
      } else if (f.type == geom_filter::ENTITY_ARG) {                          \
        attribute_filter.include = f.include;                                  \
        attribute_filter.traverse = f.traverse;                                \
        attribute_filter.attribute_name = f.arg;                               \
        attribute_filter.populate(f.values);                                   \
      }                                                                        \
    }                                                                          \
                                                                               \
    if (entity_filter.entity_names.empty()) {                                  \
      std::set<std::string> entities;                                          \
      entity_filter.include = false;                                           \
      entities.emplace("IfcSpace");                                            \
      entities.emplace("IfcOpeningElement");                                   \
      entity_filter.entity_names = entities;                                   \
    }                                                                          \
                                                                               \
    if (!layer_filter.values.empty()) {                                        \
      filter_funcs.push_back(boost::ref(layer_filter));                        \
    }                                                                          \
    if (!entity_filter.entity_names.empty()) {                                 \
      filter_funcs.push_back(boost::ref(entity_filter));                       \
    }                                                                          \
    if (!attribute_filter.values.empty()) {                                    \
      filter_funcs.push_back(boost::ref(attribute_filter));                    \
    }                                                                          \
  }                                                                            \
                                                                               \
  std::vector<ifc_element_info> NS##_convert::get_shape() {                    \
    NS::IfcParse::IfcFile fl{_file_name};                                      \
    NS::IfcGeom::Iterator<double> iter{settings, &fl, this->filter_funcs};     \
    std::vector<ifc_element_info> shps;                                        \
    if (iter.initialize()) {                                                   \
      do {                                                                     \
        auto ele = iter.get_native();                                          \
        auto ele2 = iter.get();                                                \
        for (auto &sp : ele->geometry()) {                                     \
          shps.emplace_back(ifc_element_info{                                  \
              .shp = sp.Shape(),                                               \
              .id = ele2->id(),                                                \
              .parent_id = ele2->parent_id(),                                  \
              .name = ele2->name(),                                            \
              .guid = ele2->guid(),                                            \
          });                                                                  \
        }                                                                      \
      } while (iter.next());                                                   \
    }                                                                          \
    return shps;                                                               \
  }                                                                            \
                                                                               \
  void NS##_convert::process_with_callback(visitor *vst) {                     \
    NS::IfcParse::IfcFile fl{_file_name};                                      \
    NS::IfcGeom::Iterator<double> iter{settings, &fl, filter_funcs};           \
    unsigned int vcount_total = 0;                                             \
    if (iter.initialize()) {                                                   \
      do {                                                                     \
        auto ptr =                                                             \
            reinterpret_cast<NS::IfcGeom::TriangulationElement<double> *>(     \
                iter.get());                                                   \
        vst->apply(ptr);                                                       \
      } while (iter.next());                                                   \
    }                                                                          \
  }

GEN_CODE(ifc23)
GEN_CODE(ifc4)
GEN_CODE(ifc41)
GEN_CODE(ifc42)
GEN_CODE(ifc43_rc1)
} // namespace ifc
} // namespace flywave
