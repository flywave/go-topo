
#include "geom_utils.hh"
#include "math_utils.hh"

#include <Adaptor3d_Curve.hxx>
#include <Standard_Version.hxx>
#include <TopLoc_Location.hxx>
#include <gp_Trsf.hxx>

#include <algorithm>
#include <cmath>

namespace flywave {
namespace geom_utils {

double normalized_curve(const Adaptor3d_Curve &curve, double u) {
  const double uFirst = curve.FirstParameter();
  const double uLast = curve.LastParameter();
  const std::pair<double, double> uRange = std::minmax(uFirst, uLast);
  return math_utils::mapped_value(u, uRange.first, uRange.second, 0, 1);
}

gp_Pnt d0(const Adaptor3d_Curve &curve, double u) {
  gp_Pnt pnt;
  curve.D0(u, pnt);
  return pnt;
}

gp_Vec d1(const Adaptor3d_Curve &curve, double u) {
  gp_Pnt pnt;
  gp_Vec vec;
  curve.D1(u, pnt, vec);
  return vec;
}

std::pair<gp_Pnt, gp_Vec> d0d1(const Adaptor3d_Curve &curve, double u) {
  gp_Pnt pnt;
  gp_Vec vec;
  curve.D1(u, pnt, vec);
  return {pnt, vec};
}

bool has_scaling(const gp_Trsf &trsf) {
#if OCC_VERSION_HEX >= 0x070600
  const double scalePrec = TopLoc_Location::ScalePrec();
#else
  constexpr double scalePrec = 1.e-14;
#endif
  // This test comes from implementation of TopoDS_Shape::Location() function
  return std::abs(std::abs(trsf.ScaleFactor()) - 1.) > scalePrec ||
         trsf.IsNegative();
}
} // namespace geom_utils
} // namespace flywave