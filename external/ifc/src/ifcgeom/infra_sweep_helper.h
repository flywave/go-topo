#ifndef LINEAR_SWEEP_HELPER_H
#define LINEAR_SWEEP_HELPER_H

#include <ifcgeom/ConversionSettings.h>
#include <ifcgeom/taxonomy.h>

namespace ifcopenshell {
namespace geometry {

struct cross_section {
  double dist_along;
  taxonomy::geom_item::ptr section_geometry;
  Eigen::Vector3d offset;
  boost::optional<Eigen::Matrix3d> rotation;

  bool operator<(const cross_section &other) const {
    return dist_along < other.dist_along;
  }
};

taxonomy::loft::ptr make_loft(const Settings &settings_,
                              const IfcUtil::IfcBaseClass *inst,
                              const taxonomy::function_item::ptr &directrix,
                              std::vector<cross_section> &cross_sections);
} // namespace geometry
} // namespace ifcopenshell

#endif