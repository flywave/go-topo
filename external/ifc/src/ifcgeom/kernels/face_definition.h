#ifndef FACE_DEFINITION_H
#define FACE_DEFINITION_H

#include <Geom_Surface.hxx>
#include <TopoDS_Wire.hxx>

#include <map>
#include <vector>

namespace IfcGeom {
namespace util {

/* Returns whether wire conforms to a polyhedron, i.e. only edges with linear
 * curves*/
bool is_polyhedron(const TopoDS_Wire &wire);

/* A temporary structure to store the intermediate data for the face conversion
 */
class face_definition {
private:
  Handle(Geom_Surface) surface_;
  std::vector<TopoDS_Wire> wires_;
  bool all_outer_;

public:
  face_definition() : surface_(), all_outer_(false) {}

  typedef std::vector<TopoDS_Wire>::const_iterator wire_it;

  bool &all_outer() { return all_outer_; }

  bool all_outer() const { return all_outer_; }

  Handle(Geom_Surface) & surface() { return surface_; }

  const Handle(Geom_Surface) & surface() const { return surface_; }

  std::vector<TopoDS_Wire> &wires() { return wires_; }

  const TopoDS_Wire &outer_wire() const { return wires_.front(); }

  std::pair<wire_it, wire_it> inner_wires() const {
    return {wires_.begin() + 1, wires_.end()};
  }
};

} // namespace util
} // namespace IfcGeom

#endif
