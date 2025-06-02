#ifndef __FLYWAVE_TOPO_BOUND_PIPE_HH__
#define __FLYWAVE_TOPO_BOUND_PIPE_HH__

#include <Geom_Curve.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Wire.hxx>
#include <gp_Pnt.hxx>

namespace flywave {
namespace topo {

struct bounding_pipe {
  double radius;                 // 管道截面半径
  Handle(Geom_Curve) centerline; // 管道中心线
};

std::vector<gp_Pnt> extract_shape_points(const TopoDS_Shape &shape);
Handle(Geom_Curve)
    fit_centerline_from_shape(const TopoDS_Shape &shape, int numSamples = 100,
                              int splineDegree = 3,
                              double smoothingFactor = 0.99);
bounding_pipe extract_bounding_pipe_from_shape(const TopoDS_Shape &shape,
                                               const gp_Dir *userDir = nullptr,
                                               int numSamplePoints = 100);
TopoDS_Shape clip_with_bounding_pipe_and_split_distances(
    const TopoDS_Shape &shape, const bounding_pipe &boundPipe,
    std::array<double, 2> splitDistances = {0.0, -1},
    TopoDS_Wire originalPathWire = TopoDS_Wire());
TopoDS_Shape
clip_with_bounding_pipe_by_ratios(const TopoDS_Shape &shape,
                                  const bounding_pipe &boundPipe,
                                  std::array<double, 2> splitRatios,
                                  TopoDS_Wire originalPathWire = TopoDS_Wire());
std::vector<gp_Pnt> sample_centerline(Handle(Geom_Curve) centerline,
                                      int numSamples = 100);

} // namespace topo
} // namespace flywave

#endif // __FLYWAVE_TOPO_BOUND_PIPE_HH__
