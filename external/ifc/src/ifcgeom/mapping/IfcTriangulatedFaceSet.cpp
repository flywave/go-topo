#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

#ifdef SCHEMA_HAS_IfcTriangulatedFaceSet

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcTriangulatedFaceSet *inst) {
  IfcSchema::IfcCartesianPointList3D *point_list = inst->Coordinates();
  auto coordinates = point_list->CoordList();
  std::vector<std::vector<int>> indices_list = inst->CoordIndex();

  std::vector<taxonomy::point3::ptr> points;
  points.reserve(coordinates.size());
  for (auto &coords : coordinates) {
    points.push_back(taxonomy::make<taxonomy::point3>(
        coords.size() < 1 ? 0. : coords[0] * length_unit_,
        coords.size() < 2 ? 0. : coords[1] * length_unit_,
        coords.size() < 3 ? 0. : coords[2] * length_unit_));
  }

  int max_index = (int)points.size();

  auto shell = taxonomy::make<taxonomy::shell>();

  for (auto &indices : indices_list) {
    auto fa = taxonomy::make<taxonomy::face>();
    shell->children.push_back(fa);

    {
      auto loop = taxonomy::make<taxonomy::loop>();
      fa->children = {loop};
      loop->external = true;
      taxonomy::point3::ptr first, previous;
      for (std::vector<int>::const_iterator jt = indices.begin();
           jt != indices.end(); ++jt) {
        if (*jt < 1 || *jt > max_index) {
          throw IfcParse::IfcException(
              "IfcTriangulatedFaceSet index out of bounds for index " +
              boost::lexical_cast<std::string>(*jt));
        }
        const taxonomy::point3::ptr &current = points[(*jt) - 1];
        if (jt == indices.begin()) {
          first = current;
        } else {
          loop->children.push_back(
              taxonomy::make<taxonomy::edge>(previous, current));
        }
        previous = current;
      }
      if (first && previous != first) {
        loop->children.push_back(
            taxonomy::make<taxonomy::edge>(previous, first));
      }
    }
  }

  return shell;
}

#endif