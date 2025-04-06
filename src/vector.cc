#include "vector.hh"
#include "matrix.hh"

namespace flywave {
namespace topo {

topo_vector topo_vector::transform(const class topo_matrix &T) const {
  gp_Vec transformed = T * _value;
  return topo_vector(transformed);
}
} // namespace topo
} // namespace flywave