#ifndef __FLYWAVE_MESH_TOPO_SHELL_HH__
#define __FLYWAVE_MESH_TOPO_SHELL_HH__

#include <TopExp_Explorer.hxx>
#include <TopoDS_Shell.hxx>

#include "shape.hh"

namespace flywave {
namespace topo {

class wire;

class shell : public shape {
public:
  shell() = default;
  virtual ~shell() = default;

  static shell make_shell(const Handle(Geom_Surface) & S,
                          const bool segment = false);

  static shell make_shell(const Handle(Geom_Surface) & S,
                          const Standard_Real UMin, const Standard_Real UMax,
                          const Standard_Real VMin, const Standard_Real VMax,
                          const bool segment = false);

  static shell make_shell_from_box(const Standard_Real dx,
                                   const Standard_Real dy,
                                   const Standard_Real dz);

  static shell make_shell_from_box(const gp_Pnt &P, const Standard_Real dx,
                                   const Standard_Real dy,
                                   const Standard_Real dz);

  static shell make_shell_from_box(const gp_Pnt &P1, const gp_Pnt &P2);

  static shell make_shell_from_box(const gp_Ax2 &Axes, const Standard_Real dx,
                                   const Standard_Real dy,
                                   const Standard_Real dz);

  static shell make_shell_from_cylinder(const Standard_Real R,
                                        const Standard_Real H);

  static shell make_shell_from_cylinder(const Standard_Real R,
                                        const Standard_Real H,
                                        const Standard_Real Angle);

  static shell make_shell_from_cylinder(const gp_Ax2 &Axes,
                                        const Standard_Real R,
                                        const Standard_Real H);

  static shell make_shell_from_cylinder(const gp_Ax2 &Axes,
                                        const Standard_Real R,
                                        const Standard_Real H,
                                        const Standard_Real Angle);

  static shell make_shell_from_cone(const Standard_Real R1,
                                    const Standard_Real R2,
                                    const Standard_Real H);

  static shell make_shell_from_cone(const Standard_Real R1,
                                    const Standard_Real R2,
                                    const Standard_Real H,
                                    const Standard_Real angle);

  static shell make_shell_from_cone(const gp_Ax2 &Axes, const Standard_Real R1,
                                    const Standard_Real R2,
                                    const Standard_Real H);

  static shell make_shell_from_cone(const gp_Ax2 &Axes, const Standard_Real R1,
                                    const Standard_Real R2,
                                    const Standard_Real H,
                                    const Standard_Real angle);

  static shell make_shell_from_revolution(const Handle(Geom_Curve) & Meridian);

  static shell make_shell_from_revolution(const Handle(Geom_Curve) & Meridian,
                                          const Standard_Real angle);

  static shell make_shell_from_revolution(const Handle(Geom_Curve) & Meridian,
                                          const Standard_Real VMin,
                                          const Standard_Real VMax);

  static shell make_shell_from_revolution(const Handle(Geom_Curve) & Meridian,
                                          const Standard_Real VMin,
                                          const Standard_Real VMax,
                                          const Standard_Real angle);

  static shell make_shell_from_revolution(const gp_Ax2 &Axes,
                                          const Handle(Geom_Curve) & Meridian);

  static shell make_shell_from_revolution(const gp_Ax2 &Axes,
                                          const Handle(Geom_Curve) & Meridian,
                                          const Standard_Real angle);

  static shell make_shell_from_revolution(const gp_Ax2 &Axes,
                                          const Handle(Geom_Curve) & Meridian,
                                          const Standard_Real VMin,
                                          const Standard_Real VMax);

  static shell make_shell_from_revolution(const gp_Ax2 &Axes,
                                          const Handle(Geom_Curve) & Meridian,
                                          const Standard_Real VMin,
                                          const Standard_Real VMax,
                                          const Standard_Real angle);

  static shell make_shell_from_sphere(const Standard_Real R);

  static shell make_shell_from_sphere(const Standard_Real R,
                                      const Standard_Real angle);

  static shell make_shell_from_sphere(const Standard_Real R,
                                      const Standard_Real angle1,
                                      const Standard_Real angle2);

  static shell make_shell_from_sphere(const Standard_Real R,
                                      const Standard_Real angle1,
                                      const Standard_Real angle2,
                                      const Standard_Real angle3);

  static shell make_shell_from_sphere(const gp_Pnt &Center,
                                      const Standard_Real R);

  static shell make_shell_from_sphere(const gp_Pnt &Center,
                                      const Standard_Real R,
                                      const Standard_Real angle);

  static shell make_shell_from_sphere(const gp_Pnt &Center,
                                      const Standard_Real R,
                                      const Standard_Real angle1,
                                      const Standard_Real angle2);

  static shell make_shell_from_sphere(const gp_Pnt &Center,
                                      const Standard_Real R,
                                      const Standard_Real angle1,
                                      const Standard_Real angle2,
                                      const Standard_Real angle3);

  static shell make_shell_from_sphere(const gp_Ax2 &Axis,
                                      const Standard_Real R);

  static shell make_shell_from_sphere(const gp_Ax2 &Axis, const Standard_Real R,
                                      const Standard_Real angle);

  static shell make_shell_from_sphere(const gp_Ax2 &Axis, const Standard_Real R,
                                      const Standard_Real angle1,
                                      const Standard_Real angle2);

  static shell make_shell_from_sphere(const gp_Ax2 &Axis, const Standard_Real R,
                                      const Standard_Real angle1,
                                      const Standard_Real angle2,
                                      const Standard_Real angle3);

  static shell make_shell_from_torus(const Standard_Real R1,
                                     const Standard_Real R2);

  static shell make_shell_from_torus(const Standard_Real R1,
                                     const Standard_Real R2,
                                     const Standard_Real angle);

  static shell make_shell_from_torus(const Standard_Real R1,
                                     const Standard_Real R2,
                                     const Standard_Real angle1,
                                     const Standard_Real angle2);

  static shell make_shell_from_torus(const Standard_Real R1,
                                     const Standard_Real R2,
                                     const Standard_Real angle1,
                                     const Standard_Real angle2,
                                     const Standard_Real angle);

  static shell make_shell_from_torus(const gp_Ax2 &Axes, const Standard_Real R1,
                                     const Standard_Real R2);

  static shell make_shell_from_torus(const gp_Ax2 &Axes, const Standard_Real R1,
                                     const Standard_Real R2,
                                     const Standard_Real angle);

  static shell make_shell_from_torus(const gp_Ax2 &Axes, const Standard_Real R1,
                                     const Standard_Real R2,
                                     const Standard_Real angle1,
                                     const Standard_Real angle2);

  static shell make_shell_from_torus(const gp_Ax2 &Axes, const Standard_Real R1,
                                     const Standard_Real R2,
                                     const Standard_Real angle1,
                                     const Standard_Real angle2,
                                     const Standard_Real angle);

  static shell make_shell_from_wedge(const Standard_Real dx,
                                     const Standard_Real dy,
                                     const Standard_Real dz,
                                     const Standard_Real ltx);

  static shell make_shell_from_wedge(const gp_Ax2 &Axes, const Standard_Real dx,
                                     const Standard_Real dy,
                                     const Standard_Real dz,
                                     const Standard_Real ltx);

  static shell
  make_shell_from_wedge(const Standard_Real dx, const Standard_Real dy,
                        const Standard_Real dz, const Standard_Real xmin,
                        const Standard_Real zmin, const Standard_Real xmax,
                        const Standard_Real zmax);

  static shell
  make_shell_from_wedge(const gp_Ax2 &Axes, const Standard_Real dx,
                        const Standard_Real dy, const Standard_Real dz,
                        const Standard_Real xmin, const Standard_Real zmin,
                        const Standard_Real xmax, const Standard_Real zmax);

  int sweep(const wire &spine, std::vector<shape> profiles, int cornerMode);

  TopoDS_Shell &value();
  const TopoDS_Shell &value() const;

  virtual geometry_object_type type() const override {
    return geometry_object_type::ShellType;
  }

  virtual shape copy(bool deep = true) const override;

  shell(TopoDS_Shape shp, bool forConstruction = false)
      : shape(shp, forConstruction) {}
  shell(const shape &s, TopoDS_Shape shp) : shape(s, shp) {}

protected:
  friend class shell_iterator;
  friend class shape;
};

class shell_iterator {
public:
  TopExp_Explorer ex;
  shell_iterator(shape &arg) : ex(arg.value(), TopAbs_SHELL) {}
  void reset() { ex.ReInit(); }
  boost::optional<shell> next() {
    if (ex.More()) {
      shell ret{ex.Current()};
      ex.Next();
      return {ret};
    } else {
      return boost::none;
    }
  }
};
} // namespace topo
} // namespace flywave

namespace std {

template <> struct hash<flywave::topo::shell> {
  size_t operator()(const flywave::topo::shell &v) const {
    return v.hash_code();
  }
};

} // namespace std
#endif // __FLYWAVE_MESH_TOPO_SHELL_HH__
