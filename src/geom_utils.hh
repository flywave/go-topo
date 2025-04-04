#pragma once

#include <Geom_Curve.hxx>
#include <LProp3d_CLProps.hxx>
#include <TopoDS_Edge.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>

#include <utility>
#include <vector>

class Adaptor3d_Curve;
class gp_Trsf;

namespace flywave {
namespace geom_utils {

double normalized_curve(const Adaptor3d_Curve &curve, double u);

gp_Pnt d0(const Adaptor3d_Curve &curve, double u);
gp_Vec d1(const Adaptor3d_Curve &curve, double u);
std::pair<gp_Pnt, gp_Vec> d0d1(const Adaptor3d_Curve &curve, double u);

bool has_scaling(const gp_Trsf &trsf);

TopoDS_Edge adaptor_curve_to_edge(const Adaptor3d_Curve &crv, double p1,
                                  double p2);

double curvature_at(const Handle(Adaptor3d_Curve) & curve, double d,
                    const std::string &mode = "length",
                    double resolution = 1e-6);

std::vector<double> curvatures(const Handle(Adaptor3d_Curve) & curve,
                               const std::vector<double> &ds,
                               const std::string &mode = "length",
                               double resolution = 1e-6);

} // namespace geom_utils
} // namespace flywave
