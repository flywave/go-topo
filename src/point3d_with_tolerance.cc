#include "point3d_with_tolerance.hh"
#include <cmath>

namespace flywave {
namespace topo {

point3d_with_tolerance::point3d_with_tolerance(double x, double y, double z,
                                               double tolerance)
    : _point(x, y, z), _tolerance(tolerance) {
  calculate_hash_code();
}

point3d_with_tolerance::point3d_with_tolerance(gp_Pnt point, double t)
    : _point(point), _tolerance(t) {
  calculate_hash_code();
}

void point3d_with_tolerance::calculate_hash_code() {
  double gridDim = _tolerance * 10.;
  double xs = _point.X() - std::fmod(_point.X(), gridDim);
  double ys = _point.Y() - std::fmod(_point.Y(), gridDim);
  double zs = _point.Z() - std::fmod(_point.Z(), gridDim);
  size_t hash = 2166136261u;
  hash = hash * 16777619u ^ std::hash<double>()(xs);
  hash = hash * 16777619u ^ std::hash<double>()(ys);
  _hashCode = static_cast<int>(hash * 16777619u ^ std::hash<double>()(zs));
}

} // namespace topo
} // namespace flywave
