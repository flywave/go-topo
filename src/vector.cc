#include "vector.hh"
#include "matrix.hh"
#include "plane.hh"

namespace flywave {
namespace topo {

topo_vector topo_vector::project_to_plane(const class topo_plane &plane) const {
  auto base = plane.origin();
  auto normal = plane.z_dir();
  return *this - normal * ((this->dot(normal)) / normal.length());
}

topo_vector topo_vector::transform(const class topo_matrix &T) const {
  gp_Vec transformed = T * _value;
  return topo_vector(transformed);
}
} // namespace topo
} // namespace flywave