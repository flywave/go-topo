#include  "ifc.hh"
#include <IfcException.hh>
#include <IfcFile.h>
#include <IfcParse.h>
#include <IfcGeomIterator.h>

namespace flywave {
namespace ifc {

const std::string filter_settings::NAME_ARG = "Name";
const std::string filter_settings::GUID_ARG = "GlobalId";
const std::string filter_settings::DESC_ARG = "Description";
const std::string filter_settings::TAG_ARG = "Tag";
std::array<std::string, 4> filter_settings::supported_args{
    {NAME_ARG, GUID_ARG, DESC_ARG, TAG_ARG}};

#define GEN_CODE(NS)                                                           \
  std::vector<NS::IfcGeom::filter_t> NS##_convert::setup_filters(              \
      const std::vector<geom_filter> &filters) {                               \
    std::vector<NS::IfcGeom::filter_t> filter_funcs;                           \
    BOOST_FOREACH (const geom_filter &f, filters) {                            \
      if (f.type == geom_filter::ENTITY_TYPE) {                                \
        entity_filter.include = f.include;                                     \
        entity_filter.traverse = f.traverse;                                   \
        try {                                                                  \
          entity_filter.populate(f.values);                                    \
        } catch (const parse::ifc_exception &e) {                              \
          return std::vector<NS::IfcGeom::filter_t>();                         \
        }                                                                      \
      } else if (f.type == geom_filter::LAYER_NAME) {                          \
        layer_filter.include = f.include;                                      \
        layer_filter.traverse = f.traverse;                                    \
        layer_filter.populate(f.values);                                       \
      } else if (f.type == geom_filter::ENTITY_ARG) {                          \
        if (f.arg == filter_settings::GUID_ARG) {                              \
          guid_filter.include = f.include;                                     \
          guid_filter.traverse = f.traverse;                                   \
          guid_filter.populate(f.values);                                      \
        } else if (f.arg == filter_settings::NAME_ARG) {                       \
          name_filter.include = f.include;                                     \
          name_filter.traverse = f.traverse;                                   \
          name_filter.populate(f.values);                                      \
        } else if (f.arg == filter_settings::DESC_ARG) {                       \
          desc_filter.include = f.include;                                     \
          desc_filter.traverse = f.traverse;                                   \
          desc_filter.populate(f.values);                                      \
        } else if (f.arg == filter_settings::TAG_ARG) {                        \
          tag_filter.include = f.include;                                      \
          tag_filter.traverse = f.traverse;                                    \
          tag_filter.populate(f.values);                                       \
        }                                                                      \
      }                                                                        \
    }                                                                          \
                                                                               \
    if (entity_filter.values.empty()) {                                        \
      try {                                                                    \
        std::set<std::string> entities;                                        \
        entities.insert("IfcSpace");                                           \
        entities.insert("IfcOpeningElement");                                  \
        entity_filter.populate(entities);                                      \
      } catch (const parse::ifc_exception &e) {                                \
        return std::vector<NS::IfcGeom::filter_t>();                           \
      }                                                                        \
    }                                                                          \
                                                                               \
    if (!layer_filter.values.empty()) {                                        \
      filter_funcs.push_back(std::ref(layer_filter));                          \
    }                                                                          \
    if (!entity_filter.values.empty()) {                                       \
      filter_funcs.push_back(std::ref(entity_filter));                         \
    }                                                                          \
    if (!guid_filter.values.empty()) {                                         \
      filter_funcs.push_back(std::ref(guid_filter));                           \
    }                                                                          \
    if (!name_filter.values.empty()) {                                         \
      filter_funcs.push_back(std::ref(name_filter));                           \
    }                                                                          \
    if (!desc_filter.values.empty()) {                                         \
      filter_funcs.push_back(std::ref(desc_filter));                           \
    }                                                                          \
    if (!tag_filter.values.empty()) {                                          \
      filter_funcs.push_back(std::ref(tag_filter));                            \
    }                                                                          \
    return filter_funcs;                                                       \
  }                                                                            \
                                                                               \
  std::vector<Topo_Shape> NS##_convert::get_shape() {                          \
    NS::IfcGeom::Iterator<double> iter{settings, &file, filter_funcs};         \
    std::vector<TopoShape> shps;                                               \
    if (iter.initialize()) {                                                   \
      do {                                                                     \
        auto ele = iter.get();                                                 \
        for (auto &sp : ele->geometry()) {                                     \
          shps.emplace_back(sp.Shape());                                       \
        }                                                                      \
      } while (iter.next());                                                   \
    }                                                                          \
    return shps;                                                               \
  }                                                                            \
                                                                               \
  void NS##_convert::process_with_callback(visitor &vst) {                     \
    NS::IfcGeom::Iterator<double> iter{settings, &file, filter_funcs};         \
    unsigned int vcount_total = 0;                                             \
    if (iter.initialize()) {                                                   \
      do {                                                                     \
        auto ptr =                                                             \
            reinterpret_cast<NS::IfcGeom::TriangulationElement<double> *>(     \
                iter.get());                                                   \
        vst.apply(ptr);                                                        \
      } while (iter.next());                                                   \
    }                                                                          \
  }

GEN_CODE(ifc23)
GEN_CODE(ifc4)
} // namespace ifc
} // namespace flywave
