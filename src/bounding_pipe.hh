#ifndef __FLYWAVE_TOPO_BOUND_PIPE_HH__
#define __FLYWAVE_TOPO_BOUND_PIPE_HH__

#include <Geom_Curve.hxx>
#include <TopoDS.hxx>
#include <gp_Pnt.hxx>
#include <TopoDS_Wire.hxx>

namespace flywave {
namespace topo {

// 边界管道结构
struct bounding_pipe_section {
  gp_Pnt center;    // 截面中心点
  double radius;    // 截面半径
  gp_Dir direction; // 截面方向（管道轴线方向）
};

struct bounding_pipe {
  bounding_pipe_section sections; // 管道截面序列
  Handle(Geom_Curve) centerline;  // 管道中心线
};

std::vector<gp_Pnt> extract_shape_points(const TopoDS_Shape &shape);
Handle(Geom_Curve)
    fit_centerline_from_shape(const TopoDS_Shape &shape, int numSamples = 100,
                              int splineDegree = 3,
                              double smoothingFactor = 0.99);
Handle(Geom_Curve)
    optimize_centerline(const Handle(Geom_Curve) & centerline,
                        const std::vector<gp_Pnt> &points,
                        int numIterations = 5, double smoothingFactor = 0.3);
TopoDS_Wire extract_path_wire_from_pipe_shape(const TopoDS_Shape &pipeShape);
bounding_pipe extract_bounding_pipe_from_shape(const TopoDS_Shape &shape,
                                               const gp_Dir *userDir = nullptr,
                                               int numSamplePoints = 100);
TopoDS_Shape create_bounding_pipe_shape(const bounding_pipe_section &section,
                                        const TopoDS_Wire &path);
TopoDS_Shape create_bounding_pipe_shape(const bounding_pipe &boundPipe);
TopoDS_Shape clip_with_bounding_pipe_and_split_distances(
    const TopoDS_Shape &shape, const bounding_pipe &boundPipe,
    std::array<double, 2> splitDistances = {0.0, -1},
    TopoDS_Wire originalPathWire = TopoDS_Wire());
TopoDS_Shape
clip_with_bounding_pipe_by_ratios(const TopoDS_Shape &shape,
                                  const bounding_pipe &boundPipe,
                                  std::array<double, 2> splitRatios,
                                  TopoDS_Wire originalPathWire = TopoDS_Wire());
} // namespace topo
} // namespace flywave

#endif // __FLYWAVE_TOPO_BOUND_PIPE_HH__
