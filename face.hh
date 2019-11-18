#ifndef __FLYWAVE_MESH_TOPO_FACE_HH__
#define __FLYWAVE_MESH_TOPO_FACE_HH__

#include <TopExp_Explorer.hxx>
#include <TopoDS_Face.hxx>

#include "bool_type.hh"
#include "shape.hh"

namespace flywave {
namespace topo {

class wire;
class solid;
class edge;
class face_iterator;

class face : public shape {
public:
  face() = default;
  virtual ~face() = default;

  static face make_face(const face &F);

  static face make_face(const plane &P);

  static face make_face(const cylinder &C);

  static face make_face(const cone &C);

  static face make_face(const sphere &S);

  static face make_face(const torus &C);

  static face make_face(const geom_surface &S, const Standard_Real TolDegen);

  static face make_face(const plane &P, const Standard_Real UMin,
                        const Standard_Real UMax, const Standard_Real VMin,
                        const Standard_Real VMax);

  static face make_face(const cylinder &C, const Standard_Real UMin,
                        const Standard_Real UMax, const Standard_Real VMin,
                        const Standard_Real VMax);

  static face make_face(const cone &C, const Standard_Real UMin,
                        const Standard_Real UMax, const Standard_Real VMin,
                        const Standard_Real VMax);

  static face make_face(const sphere &S, const Standard_Real UMin,
                        const Standard_Real UMax, const Standard_Real VMin,
                        const Standard_Real VMax);

  static face make_face(const torus &C, const Standard_Real UMin,
                        const Standard_Real UMax, const Standard_Real VMin,
                        const Standard_Real VMax);

  static face make_face(const geom_surface &S, const Standard_Real UMin,
                        const Standard_Real UMax, const Standard_Real VMin,
                        const Standard_Real VMax, const Standard_Real TolDegen);

  static face make_face(const wire &W, const bool OnlyPlane = false);

  static face make_face(const plane &P, const wire &W,
                        const bool Inside = true);

  static face make_face(const cylinder &C, const wire &W,
                        const bool Inside = true);

  static face make_face(const cone &C, const wire &W, const bool Inside = true);

  static face make_face(const sphere &S, const wire &W,
                        const bool Inside = true);

  static face make_face(const torus &C, const wire &W,
                        const bool Inside = true);

  static face make_face(const geom_surface &S, const wire &W,
                        const bool Inside = true);

  static face make_face(const face &F, const wire &W);

  static face make_face(std::vector<wire> &wires);

  static face make_face(std::initializer_list<wire> wires);

  static face make_face(std::vector<edge> &edges,
                        std::vector<vector3<Standard_Real>> points);

  static face make_face(std::vector<vector3<Standard_Real>> points);

  static face make_face(std::initializer_list<vector3<Standard_Real>> points);

  int num_wires() const;

  int num_faces() const;

  double area() const;

  float tolerance() const;

  bbox3d inertia() const;

  double3 centre_of_mass() const;

  int offset(double offset, double tolerance = 1e-6);

  int extrude(const shape &shp, double3 p1, double3 p2);

  int revolve(const shape &shp, double3 p1, double3 p2, double angle);

  int sweep(const wire &spine, std::vector<shape *> profiles, int cornerMode);

  int loft(std::vector<shape> profiles, bool ruled, double tolerance);

  int boolean(const face &tool, bool_op_type op);

  TopoDS_Face &value();
  const TopoDS_Face &value() const;

  operator geom_surface() const;

  virtual geometry_object_type type() const override {
    return geometry_object_type::FaceType;
  }

  virtual shape copy(bool deep = true) const override;

  face(TopoDS_Shape shp) : shape(shp) {}

protected:
  friend class face_iterator;
  friend class shape;
};

class face_iterator {
public:
  TopExp_Explorer ex;
  face_iterator(shape &arg) : ex(arg.value(), TopAbs_FACE) {}
  void reset() { ex.ReInit(); }
  boost::optional<face> next() {
    if (ex.More()) {
      face ret{ex.Current()};
      ex.Next();
      return {ret};
    } else {
      return boost::none;
    }
  }
};

} // namespace topo
} // namespace flywave

#endif // __FLYWAVE_MESH_TOPO_FACE_HH__
