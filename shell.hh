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

  static shell make_shell(const geom_surface &S, const bool Segment = false);

  static shell make_shell(const geom_surface &S, const Standard_Real UMin,
                          const Standard_Real UMax, const Standard_Real VMin,
                          const Standard_Real VMax, const bool Segment = false);

  static shell make_shell_from_box(const Standard_Real dx,
                                   const Standard_Real dy,
                                   const Standard_Real dz);

  static shell make_shell_from_box(const vector3<Standard_Real> &P,
                                   const Standard_Real dx,
                                   const Standard_Real dy,
                                   const Standard_Real dz);

  static shell make_shell_from_box(const vector3<Standard_Real> &P1,
                                   const vector3<Standard_Real> &P2);

  static shell make_shell_from_box(const axis2 &Axes, const Standard_Real dx,
                                   const Standard_Real dy,
                                   const Standard_Real dz);

  static shell make_shell_from_cylinder(const Standard_Real R,
                                        const Standard_Real H);

  static shell make_shell_from_cylinder(const Standard_Real R,
                                        const Standard_Real H,
                                        const Standard_Real Angle);

  static shell make_shell_from_cylinder(const axis2 &Axes,
                                        const Standard_Real R,
                                        const Standard_Real H);

  static shell make_shell_from_cylinder(const axis2 &Axes,
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

  static shell make_shell_from_cone(const axis2 &Axes, const Standard_Real R1,
                                    const Standard_Real R2,
                                    const Standard_Real H);

  static shell make_shell_from_cone(const axis2 &Axes, const Standard_Real R1,
                                    const Standard_Real R2,
                                    const Standard_Real H,
                                    const Standard_Real angle);

  static shell make_shell_from_revolution(const geom_curve &Meridian);

  static shell make_shell_from_revolution(const geom_curve &Meridian,
                                          const Standard_Real angle);

  static shell make_shell_from_revolution(const geom_curve &Meridian,
                                          const Standard_Real VMin,
                                          const Standard_Real VMax);

  static shell make_shell_from_revolution(const geom_curve &Meridian,
                                          const Standard_Real VMin,
                                          const Standard_Real VMax,
                                          const Standard_Real angle);

  static shell make_shell_from_revolution(const axis2 &Axes,
                                          const geom_curve &Meridian);

  static shell make_shell_from_revolution(const axis2 &Axes,
                                          const geom_curve &Meridian,
                                          const Standard_Real angle);

  static shell make_shell_from_revolution(const axis2 &Axes,
                                          const geom_curve &Meridian,
                                          const Standard_Real VMin,
                                          const Standard_Real VMax);

  static shell make_shell_from_revolution(const axis2 &Axes,
                                          const geom_curve &Meridian,
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

  static shell make_shell_from_sphere(const vector3<Standard_Real> &Center,
                                      const Standard_Real R);

  static shell make_shell_from_sphere(const vector3<Standard_Real> &Center,
                                      const Standard_Real R,
                                      const Standard_Real angle);

  static shell make_shell_from_sphere(const vector3<Standard_Real> &Center,
                                      const Standard_Real R,
                                      const Standard_Real angle1,
                                      const Standard_Real angle2);

  static shell make_shell_from_sphere(const vector3<Standard_Real> &Center,
                                      const Standard_Real R,
                                      const Standard_Real angle1,
                                      const Standard_Real angle2,
                                      const Standard_Real angle3);

  static shell make_shell_from_sphere(const axis2 &Axis, const Standard_Real R);

  static shell make_shell_from_sphere(const axis2 &Axis, const Standard_Real R,
                                      const Standard_Real angle);

  static shell make_shell_from_sphere(const axis2 &Axis, const Standard_Real R,
                                      const Standard_Real angle1,
                                      const Standard_Real angle2);

  static shell make_shell_from_sphere(const axis2 &Axis, const Standard_Real R,
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

  static shell make_shell_from_torus(const axis2 &Axes, const Standard_Real R1,
                                     const Standard_Real R2);

  static shell make_shell_from_torus(const axis2 &Axes, const Standard_Real R1,
                                     const Standard_Real R2,
                                     const Standard_Real angle);

  static shell make_shell_from_torus(const axis2 &Axes, const Standard_Real R1,
                                     const Standard_Real R2,
                                     const Standard_Real angle1,
                                     const Standard_Real angle2);

  static shell make_shell_from_torus(const axis2 &Axes, const Standard_Real R1,
                                     const Standard_Real R2,
                                     const Standard_Real angle1,
                                     const Standard_Real angle2,
                                     const Standard_Real angle);

  static shell make_shell_from_wedge(const Standard_Real dx,
                                     const Standard_Real dy,
                                     const Standard_Real dz,
                                     const Standard_Real ltx);

  static shell make_shell_from_wedge(const axis2 &Axes, const Standard_Real dx,
                                     const Standard_Real dy,
                                     const Standard_Real dz,
                                     const Standard_Real ltx);

  static shell
  make_shell_from_wedge(const Standard_Real dx, const Standard_Real dy,
                        const Standard_Real dz, const Standard_Real xmin,
                        const Standard_Real zmin, const Standard_Real xmax,
                        const Standard_Real zmax);

  static shell
  make_shell_from_wedge(const axis2 &Axes, const Standard_Real dx,
                        const Standard_Real dy, const Standard_Real dz,
                        const Standard_Real xmin, const Standard_Real zmin,
                        const Standard_Real xmax, const Standard_Real zmax);

  int sweep(const wire &spine, std::vector<shape *> profiles, int cornerMode);

  TopoDS_Shell &value();
  const TopoDS_Shell &value() const;

  virtual geometry_object_type type() const override {
    return geometry_object_type::ShellType;
  }

  virtual shape copy(bool deep = true) const override;

protected:
  friend class shell_iterator;
  friend class shape;

  shell(TopoDS_Shape shp) : shape(shp) {}
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

#endif // __FLYWAVE_MESH_TOPO_SHELL_HH__
