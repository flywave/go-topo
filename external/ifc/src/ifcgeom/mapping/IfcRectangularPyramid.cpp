#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

#include <ifcgeom/profile_helper.h>

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcRectangularPyramid *inst) {
  const double dx = inst->XLength() * length_unit_;
  const double dy = inst->YLength() * length_unit_;
  const double dz = inst->Height() * length_unit_;

  auto solid = taxonomy::make<taxonomy::solid>();
  auto shell = taxonomy::make<taxonomy::shell>();
  solid->children.push_back(shell);

  // Base
  {
    auto face = taxonomy::make<taxonomy::face>();
    shell->children.push_back(face);

    std::vector<taxonomy::point3::ptr> points{
        taxonomy::make<taxonomy::point3>(0, 0, 0),
        taxonomy::make<taxonomy::point3>(0, dy, 0),
        taxonomy::make<taxonomy::point3>(dx, dy, 0),
        taxonomy::make<taxonomy::point3>(dx, 0, 0),
    };

    points.push_back(points.front());
    face->children.push_back(polygon_from_points(points));
  }

  // Lateral faces
  {
    auto face = taxonomy::make<taxonomy::face>();
    shell->children.push_back(face);

    std::vector<taxonomy::point3::ptr> points{
        taxonomy::make<taxonomy::point3>(0, 0, 0),
        taxonomy::make<taxonomy::point3>(0, dy, 0),
        taxonomy::make<taxonomy::point3>(0.5 * dx, 0.5 * dy, dz)};

    points.push_back(points.front());
    face->children.push_back(polygon_from_points(points));
  }

  {
    auto face = taxonomy::make<taxonomy::face>();
    shell->children.push_back(face);

    std::vector<taxonomy::point3::ptr> points{
        taxonomy::make<taxonomy::point3>(0, dy, 0),
        taxonomy::make<taxonomy::point3>(dx, dy, 0),
        taxonomy::make<taxonomy::point3>(0.5 * dx, 0.5 * dy, dz)};

    points.push_back(points.front());
    face->children.push_back(polygon_from_points(points));
  }

  {
    auto face = taxonomy::make<taxonomy::face>();
    shell->children.push_back(face);

    std::vector<taxonomy::point3::ptr> points{
        taxonomy::make<taxonomy::point3>(dx, dy, 0),
        taxonomy::make<taxonomy::point3>(dx, 0, 0),
        taxonomy::make<taxonomy::point3>(0.5 * dx, 0.5 * dy, dz)};

    points.push_back(points.front());
    face->children.push_back(polygon_from_points(points));
  }

  {
    auto face = taxonomy::make<taxonomy::face>();
    shell->children.push_back(face);

    std::vector<taxonomy::point3::ptr> points{
        taxonomy::make<taxonomy::point3>(dx, 0, 0),
        taxonomy::make<taxonomy::point3>(0, 0, 0),
        taxonomy::make<taxonomy::point3>(0.5 * dx, 0.5 * dy, dz)};

    points.push_back(points.front());
    face->children.push_back(polygon_from_points(points));
  }

  solid->matrix = taxonomy::cast<taxonomy::matrix4>(map(inst->Position()));

  return solid;
}
