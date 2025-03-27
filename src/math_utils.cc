#include "math_utils.hh"
#include "bnd_utils.hh"

#include <Precision.hxx>
#include <algorithm>
#include <cmath>
#include <limits>

namespace flywave {
namespace math_utils {

bool is_reversed_standard_dir(const gp_Dir &n) {
  for (int i = 0; i < 3; ++i) {
    const double c = n.XYZ().GetData()[i];
    if (c < 0 && (std::abs(c) - 1) < Precision::Confusion())
      return true;
  }

  return false;
}

double plane_position(const gp_Pln &plane) {
  const gp_Vec vecLoc(plane.Location().XYZ());
  const gp_Vec vecNormal(plane.Axis().Direction());
  return vecLoc.Dot(vecNormal);
}

std::pair<double, double> plane_range(const bnd_box_coords &bbc,
                                      const gp_Dir &planeNormal) {
  const gp_Vec n(is_reversed_standard_dir(planeNormal) ? planeNormal.Reversed()
                                                       : planeNormal);
  bool isMaxValid = false;
  bool isMinValid = false;
  double rmax = std::numeric_limits<double>::lowest();
  double rmin = std::numeric_limits<double>::max();
  for (const gp_Pnt &bndPoint : bbc.vertices()) {
    const gp_Vec vec(bndPoint.XYZ());
    const double dot = n.Dot(vec);
    rmax = isMaxValid ? std::max(rmax, dot) : dot;
    rmin = isMinValid ? std::min(rmin, dot) : dot;
    isMaxValid = true;
    isMinValid = true;
  }

  if (isMaxValid && isMinValid)
    return {rmin, rmax};

  return {};
}

} // namespace math_utils
} // namespace flywave