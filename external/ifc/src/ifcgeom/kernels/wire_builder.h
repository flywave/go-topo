#ifndef WIRE_BUILDER_H
#define WIRE_BUILDER_H

#include <ifcparse/IfcBaseClass.h>

#include <Geom_Curve.hxx>

#include <TopoDS_Edge.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Wire.hxx>

#include <BRepBuilderAPI_MakeWire.hxx>
#include <Extrema_ExtPC.hxx>

namespace IfcGeom {
namespace util {
// Returns the first edge of a wire
TopoDS_Edge first_edge(const TopoDS_Wire &w);

// Returns new wire with the edge replaced by a linear edge with the vertex v
// moved to p
TopoDS_Wire adjust(const TopoDS_Wire &w, const TopoDS_Vertex &v,
                   const gp_Pnt &p);

// A wrapper around BRepBuilderAPI_MakeWire that makes sure segments are
// connected either by moving end points or by adding intermediate segments
class wire_builder {
private:
  BRepBuilderAPI_MakeWire mw_;
  double p_;
  bool override_next_;
  gp_Pnt next_override_;
  const IfcUtil::IfcBaseClass *inst_;

public:
  wire_builder(double p, const IfcUtil::IfcBaseClass *inst = 0)
      : p_(p), override_next_(false), inst_(inst) {}

  void operator()(const TopoDS_Shape &a);

  void operator()(const TopoDS_Shape &a, const TopoDS_Shape &b, bool last);

  const TopoDS_Wire &wire() { return mw_.Wire(); }
};

template <typename Fn>
void shape_pair_enumerate(TopTools_ListIteratorOfListOfShape &it, Fn &fn,
                          bool closed) {
  bool is_first = true;
  TopoDS_Shape first, previous, current;
  for (; it.More(); it.Next(), is_first = false) {
    current = it.Value();
    if (is_first) {
      first = current;
    } else {
      fn(previous, current, false);
    }
    previous = current;
  }
  if (closed) {
    fn(current, first, true);
  } else {
    fn(current);
  }
}

/*
Below is code to deduce the formula below in SageMath

| R, b = var('R b')
|
| Bxy = R * cos(b), R * sin(b)
| Cxy = R * cos(b/2), R * sin(b/2)
|
| def dot(v, w):
|     return v[0] * w[0] + v[1] * w[1]
|
| def norm(v):
|     l = sqrt(v[0]^2 + v[1]^2)
|     return v[0] / l, v[1] / l
|
| (R - R*dot(norm(Cxy), norm(Bxy))).full_simplify()
*/

double deflection_for_approximating_circle(double radius, double param);

bool create_edge_over_curve_with_log_messages(const Handle_Geom_Curve &crv,
                                              const double eps,
                                              const gp_Pnt &p1,
                                              const gp_Pnt &p2,
                                              TopoDS_Edge &result);
} // namespace util
} // namespace IfcGeom

#endif
