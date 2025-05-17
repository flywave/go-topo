#include "ifc.hh"
#include <IfcFile.h>
#include <IfcParse.h>
#include <boost/program_options.hpp>

#include <ifcgeom/kernels/OpenCascadeConversionResult.h>
#include <ifcparse/utils.h>

namespace flywave {
namespace ifc {

const std::string filter_settings::NAME_ARG = "Name";
const std::string filter_settings::GUID_ARG = "GlobalId";
const std::string filter_settings::DESC_ARG = "Description";
const std::string filter_settings::TAG_ARG = "Tag";
std::array<std::string, 4> filter_settings::supported_args{
    {NAME_ARG, GUID_ARG, DESC_ARG, TAG_ARG}};

std::vector<IfcGeom::filter_t>
ifc_convert::setup_filters(const std::vector<geom_filter> &filters) {
  std::vector<IfcGeom::filter_t> filter_funcs;
  for (auto &f : filters) {
    if (f.type == geom_filter::ENTITY_TYPE) {
      entity_filter.include = f.include;
      entity_filter.traverse = f.traverse;
      entity_filter.entity_names = f.values;
    } else if (f.type == geom_filter::LAYER_NAME) {
      layer_filter.include = f.include;
      layer_filter.traverse = f.traverse;
      layer_filter.populate(f.values);
    } else if (f.type == geom_filter::ENTITY_ARG) {
      attribute_filter.include = f.include;
      attribute_filter.traverse = attribute_filter.traverse_openings =
          f.traverse;
      attribute_filter.attribute_name = f.arg;
      attribute_filter.populate(f.values);
    }
  }

  if (entity_filter.entity_names.empty()) {
    std::set<std::string> entities;
    entities.insert("IfcSpace");
    entities.insert("IfcOpeningElement");
    entity_filter.entity_names = entities;
  }

  if (!layer_filter.values.empty()) {
    filter_funcs.push_back(boost::ref(layer_filter));
  }
  if (!entity_filter.entity_names.empty()) {
    filter_funcs.push_back(boost::ref(entity_filter));
  }
  if (!attribute_filter.values.empty()) {
    filter_funcs.push_back(boost::ref(attribute_filter));
  }

  return filter_funcs;
}

std::vector<ifc_element_info> ifc_convert::get_shape() {
  IfcParse::IfcFile fl{_file_name};
  IfcGeom::Iterator iter{settings, &fl, this->filter_funcs, 1};
  std::vector<ifc_element_info> shps;
  if (iter.initialize()) {
    do {
      auto ele = iter.get_native();
      auto ele2 = iter.get();
      auto itm = ele->geometry().as_compound();
      TopoDS_Shape compound =
          ((ifcopenshell::geometry::OpenCascadeShape *)itm)->shape();
      shps.emplace_back(ifc_element_info{
          .shp = compound,
          .id = ele2->id(),
          .parent_id = ele2->parent_id(),
          .name = ele2->name(),
          .guid = ele2->guid(),
      });
    } while (iter.next());
  }
  return shps;
}

void ifc_convert::process_with_callback(visitor *vst) {
  IfcParse::IfcFile fl{_file_name};
  IfcGeom::Iterator iter{settings, &fl, filter_funcs, 1};
  unsigned int vcount_total = 0;
  if (iter.initialize()) {
    do {
      auto ptr = reinterpret_cast<IfcGeom::TriangulationElement *>(iter.get());
      vst->apply(ptr);
    } while (iter.next());
  }
}
} // namespace ifc
} // namespace flywave
