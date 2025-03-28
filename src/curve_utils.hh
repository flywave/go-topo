
#include <Geom_Curve.hxx>
#include <LProp3d_CLProps.hxx>
#include <TopoDS_Edge.hxx>
#include <stdexcept>
#include <vector>

namespace flywave {
namespace topo {
namespace curve_utils {

TopoDS_Edge adaptor_curve_to_edge(const Adaptor3d_Curve &crv, double p1,
                                  double p2);

double curvature_at(const Handle(Adaptor3d_Curve) & curve, double d,
                    const std::string &mode = "length",
                    double resolution = 1e-6);

std::vector<double> curvatures(const Handle(Adaptor3d_Curve) & curve,
                               const std::vector<double> &ds,
                               const std::string &mode = "length",
                               double resolution = 1e-6);
} // namespace curve_utils
} // namespace topo
} // namespace flywave