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
  if (!_file && !this->load()) {
    return {};
  }
  IfcGeom::Iterator iter{settings, _file.get(), this->filter_funcs, 1};
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
          .type = ele2->type()
      });
    } while (iter.next());
  }
  return shps;
}

std::vector<ifc_convert::triangulation_ptr> ifc_convert::get_geometry() {
  if (!_file && !this->load()) {
    return {};
  }
  IfcGeom::Iterator iter{settings, _file.get(), this->filter_funcs, 1};
  std::vector<boost::shared_ptr<IfcGeom::Representation::Triangulation>> shps;
  if (iter.initialize()) {
    do {
      auto ptr = reinterpret_cast<IfcGeom::TriangulationElement *>(iter.get());
      shps.push_back(ptr->geometry_pointer());
    } while (iter.next());
  }
  return shps;
}

bool ifc_convert::load() {
  try {
    _file = std::make_unique<IfcParse::IfcFile>(_file_name);
    if (!_file || !_file->good()) {
      return false;
    }
    return true;
  } catch (const std::exception &e) {
    return false;
  }
}

std::string ifc_convert::get_version() {
  if (!_file) {
    return nullptr;
  }
  return _file->good() == IfcParse::file_open_status::SUCCESS
             ? _file->header().file_description().implementation_level()
             : std::string();
}

std::unique_ptr<ifcopenshell::data::IfcData> ifc_convert::get_data() {
  if (!_file) {
    return nullptr;
  }
  return std::make_unique<ifcopenshell::data::IfcData>(
      ifcopenshell::data::read_data(_file.get()));
}

} // namespace ifc
} // namespace flywave
