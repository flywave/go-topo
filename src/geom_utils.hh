#pragma once

#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>
#include <utility>

class Adaptor3d_Curve;
class gp_Trsf;

namespace flywave {
namespace geom_utils {

double normalized_curve(const Adaptor3d_Curve &curve, double u);

gp_Pnt d0(const Adaptor3d_Curve &curve, double u);
gp_Vec d1(const Adaptor3d_Curve &curve, double u);
std::pair<gp_Pnt, gp_Vec> d0d1(const Adaptor3d_Curve &curve, double u);

bool has_scaling(const gp_Trsf &trsf);

} // namespace geom_utils
} // namespace flywave
