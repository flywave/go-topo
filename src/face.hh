#ifndef __FLYWAVE_MESH_TOPO_FACE_HH__
#define __FLYWAVE_MESH_TOPO_FACE_HH__

#include <Geom_Surface.hxx>
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

  static face make_face(const gp_Pln &P);

  static face make_face(const gp_Cylinder &C);

  static face make_face(const gp_Cone &C);

  static face make_face(const gp_Sphere &S);

  static face make_face(const gp_Torus &C);

  static face make_face(const Handle(Geom_Surface) & S,
                        const Standard_Real TolDegen);

  static face make_face(const gp_Pln &P, const Standard_Real UMin,
                        const Standard_Real UMax, const Standard_Real VMin,
                        const Standard_Real VMax);

  static face make_face(const gp_Cylinder &C, const Standard_Real UMin,
                        const Standard_Real UMax, const Standard_Real VMin,
                        const Standard_Real VMax);

  static face make_face(const gp_Cone &C, const Standard_Real UMin,
                        const Standard_Real UMax, const Standard_Real VMin,
                        const Standard_Real VMax);

  static face make_face(const gp_Sphere &S, const Standard_Real UMin,
                        const Standard_Real UMax, const Standard_Real VMin,
                        const Standard_Real VMax);

  static face make_face(const gp_Torus &C, const Standard_Real UMin,
                        const Standard_Real UMax, const Standard_Real VMin,
                        const Standard_Real VMax);

  static face make_face(const Handle(Geom_Surface) & S,
                        const Standard_Real UMin, const Standard_Real UMax,
                        const Standard_Real VMin, const Standard_Real VMax,
                        const Standard_Real TolDegen);

  static face make_face(const wire &W, const bool OnlyPlane = false);

  static face make_face(const gp_Pln &P, const wire &W,
                        const bool Inside = true);

  static face make_face(const gp_Cylinder &C, const wire &W,
                        const bool Inside = true);

  static face make_face(const gp_Cone &C, const wire &W,
                        const bool Inside = true);

  static face make_face(const gp_Sphere &S, const wire &W,
                        const bool Inside = true);

  static face make_face(const gp_Torus &C, const wire &W,
                        const bool Inside = true);

  static face make_face(const Handle(Geom_Surface) & S, const wire &W,
                        const bool Inside = true);

  static face make_face(const face &F, const wire &W);

  static face make_face(std::vector<wire> &wires);

  static face make_face(std::initializer_list<wire> wires);

  static face make_face(std::vector<edge> &edges, std::vector<gp_Pnt> points);

  static face make_face(std::vector<gp_Pnt> points);

  static face make_face(std::initializer_list<gp_Pnt> points);

  int num_wires() const;

  int num_faces() const;

  double area() const;

  float tolerance() const;

  Bnd_Box inertia() const;

  gp_Pnt centre_of_mass() const;

  int offset(double offset, double tolerance = 1e-6);

  int extrude(const shape &shp, gp_Pnt p1, gp_Pnt p2);

  int revolve(const shape &shp, gp_Pnt p1, gp_Pnt p2, double angle);

  int sweep(const wire &spine, std::vector<shape *> profiles, int cornerMode);

  int loft(std::vector<shape> profiles, bool ruled, double tolerance);

  int boolean(const face &tool, bool_op_type op);

  TopoDS_Face &value();
  const TopoDS_Face &value() const;

  operator Handle(Geom_Surface)() const;

  virtual geometry_object_type type() const override {
    return geometry_object_type::FaceType;
  }

  virtual shape copy(bool deep = true) const override;

  face(TopoDS_Shape shp) : shape(shp) {}
  face(const shape &v, TopoDS_Shape shp) : shape(v, shp) {}

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
