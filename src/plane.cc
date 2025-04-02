#include "plane.hh"
#include "shape.hh"

namespace flywave {
namespace topo {

shape topo_plane::toWorldCoords(const shape &v) const {
  return v.transformed(rG);
}
shape topo_plane::toLocalCoords(const shape &v) const {
  return v.transformed(fG);
}

std::vector<shape> topo_plane::mirrorInPlane(const std::vector<shape> &shapes,
    const std::string &axis) const {
// Create local coordinate system
gp_Ax3 localCoordSystem(origin.toPnt(), zDir, xDir);

gp_Trsf transformation;

// Set up the mirror transformation based on the specified axis
if (axis == "X") {
transformation.SetMirror(
gp_Ax1(origin.toPnt(), localCoordSystem.XDirection()));
} else if (axis == "Y") {
transformation.SetMirror(
gp_Ax1(origin.toPnt(), localCoordSystem.YDirection()));
} else {
throw std::invalid_argument(
"Unsupported mirror axis. Only 'X' and 'Y' are supported.");
}

// Mirror each shape and collect results
std::vector<shape> mirroredShapes;
for (const auto &s : shapes) {
shape mirrored = s.transformed(topo_matrix(transformation));
mirroredShapes.push_back(mirrored);
}

return mirroredShapes;
}

} // namespace topo
} // namespace flywave
