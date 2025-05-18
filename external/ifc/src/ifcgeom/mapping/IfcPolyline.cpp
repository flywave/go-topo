#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

#include <ifcgeom/profile_helper.h>

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcPolyline *inst) {
  IfcSchema::IfcCartesianPoint::list::ptr points = inst->Points();

  // Parse and store the points in a sequence
  std::vector<taxonomy::point3::ptr> polygon;
  polygon.reserve(points->size());
  std::transform(points->begin(), points->end(), std::back_inserter(polygon),
                 [this](const IfcSchema::IfcCartesianPoint *p) {
                   return taxonomy::cast<taxonomy::point3>(map(p));
                 });

  auto eps = this->settings_.get<settings::Precision>().get();

  const bool closed_by_proximity =
      polygon.size() >= 3 &&
      (polygon.front()->ccomponents() - polygon.back()->ccomponents()).norm() <
          eps;
  if (closed_by_proximity) {
    polygon.resize(polygon.size() - 1);
  }

  // Remove points that are too close to one another
  auto previous_size = polygon.size();
  remove_duplicate_points_from_loop(polygon, closed_by_proximity, eps);
  if (polygon.size() != previous_size) {
    Logger::Warning("Removed " +
                        std::to_string(previous_size - polygon.size()) +
                        " (near) duplicate points from:",
                    inst);
  }

  if (polygon.size() < 2) {
    // We somehow need to signal we fail this curve on purpose not to trigger an
    // error.
    Logger::Warning("Invalid polyline with " + std::to_string(polygon.size()) +
                        " points:",
                    inst);
    return nullptr;
  }

  if (closed_by_proximity) {
    polygon.push_back(polygon.front());
  }

  return polygon_from_points(polygon);
}
