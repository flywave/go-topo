#ifndef __FLYWAVE_TOPO_BOUND_PIPE_HH__
#define __FLYWAVE_TOPO_BOUND_PIPE_HH__

#include <Geom_BSplineCurve.hxx>
#include <Geom_Curve.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Wire.hxx>
#include <array>
#include <gp_Pnt.hxx>
#include <vector>

namespace flywave {
namespace topo {

struct bounding_pipe {
  double radius;                 // 管道截面半径
  std::vector<gp_Pnt> points;    // 管道中心线上的点
  Handle(Geom_Curve) centerline; // 管道中心线
};

std::vector<gp_Pnt> extract_shape_points(const TopoDS_Shape &shape);
Handle(Geom_Curve)
    fit_centerline_from_shape(const TopoDS_Shape &shape, int numSamples = 100,
                              double smoothingFactor = 0.99);
bounding_pipe compute_simple_bounding_pipe_from_shape(const TopoDS_Shape &shape,
                                                      const gp_Dir userDir);
bounding_pipe extract_bounding_pipe_from_shape(const TopoDS_Shape &shape,
                                               const gp_Dir *userDir = nullptr,
                                               int numSamplePoints = 100);
TopoDS_Shape clip_with_bounding_pipe_and_split_distances(
    const TopoDS_Shape &shape, const bounding_pipe &boundPipe,
    const std::array<double, 2> &splitDistances = {0.0, -1.0},
    TopoDS_Wire originalPathWire = TopoDS_Wire());
TopoDS_Shape
clip_with_bounding_pipe_by_ratios(const TopoDS_Shape &shape,
                                  const bounding_pipe &boundPipe,
                                  const std::array<double, 2> &splitRatios,
                                  TopoDS_Wire originalPathWire = TopoDS_Wire());
std::vector<gp_Pnt> sample_centerline(Handle(Geom_Curve) centerline,
                                      int numSamples = 200,
                                      bool simplify = false);
Handle(Geom_Curve) centerline_to_curve(const std::vector<gp_Pnt> &points);

} // namespace topo
} // namespace flywave

#endif // __FLYWAVE_TOPO_BOUND_PIPE_HH__
