#include <BRepBuilderAPI_Copy.hxx>
#include <BRepBuilderAPI_MakeShell.hxx>
#include <BRepOffsetAPI_MakeDraft.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeRevolution.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakeWedge.hxx>
#include <TopoDS.hxx>

#include "face.hh"
#include "shell.hh"
#include "wire.hh"

namespace flywave {
namespace topo {

TopoDS_Shell &shell::value() { return TopoDS::Shell(_shape); }
const TopoDS_Shell &shell::value() const { return TopoDS::Shell(_shape); }

shape shell::copy(bool deep) const {
  try {
    BRepBuilderAPI_Copy _copy(_shape, deep);
    _copy.Build();

    if (!_copy.IsDone())
      throw std::runtime_error("Section operation failed");

    auto shp = _copy.Shape();

    if (shp.IsNull())
      throw std::runtime_error("Shell operation resulted in Null shape");

    return shell{shp};
  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
  }
  return shell{};
}

shell shell::make_shell(const Handle(Geom_Surface) & S, const bool segment) {
  try {
    BRepBuilderAPI_MakeShell mb(S, segment);
    return shell{mb.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell(const Handle(Geom_Surface) & S,
                        const Standard_Real UMin, const Standard_Real UMax,
                        const Standard_Real VMin, const Standard_Real VMax,
                        const bool segment) {
  try {
    BRepBuilderAPI_MakeShell mb(S, UMin, UMax, VMin, VMax, segment);
    return shell{mb.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_box(const Standard_Real dx, const Standard_Real dy,
                                 const Standard_Real dz) {
  try {
    BRepPrimAPI_MakeBox mb(dx, dy, dz);
    return shell{mb.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_box(const gp_Pnt &P, const Standard_Real dx,
                                 const Standard_Real dy,
                                 const Standard_Real dz) {
  try {
    BRepPrimAPI_MakeBox mb(P, dx, dy, dz);
    return shell{mb.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_box(const gp_Pnt &P1, const gp_Pnt &P2) {
  try {
    BRepPrimAPI_MakeBox mb(P1, P2);
    return shell{mb.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_box(const gp_Ax2 &Axes, const Standard_Real dx,
                                 const Standard_Real dy,
                                 const Standard_Real dz) {
  try {
    BRepPrimAPI_MakeBox mb(Axes, dx, dy, dz);
    return shell{mb.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_cylinder(const Standard_Real R,
                                      const Standard_Real H) {
  try {
    BRepPrimAPI_MakeCylinder mw(R, H);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_cylinder(const Standard_Real R,
                                      const Standard_Real H,
                                      const Standard_Real Angle) {
  try {
    BRepPrimAPI_MakeCylinder mw(R, H, Angle);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_cylinder(const gp_Ax2 &Axes, const Standard_Real R,
                                      const Standard_Real H) {
  try {
    BRepPrimAPI_MakeCylinder mw(Axes, R, H);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_cylinder(const gp_Ax2 &Axes, const Standard_Real R,
                                      const Standard_Real H,
                                      const Standard_Real Angle) {
  try {
    BRepPrimAPI_MakeCylinder mw(Axes, R, H, Angle);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_cone(const Standard_Real R1,
                                  const Standard_Real R2,
                                  const Standard_Real H) {
  try {
    BRepPrimAPI_MakeCone mw(R1, R2, H);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_cone(const Standard_Real R1,
                                  const Standard_Real R2, const Standard_Real H,
                                  const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeCone mw(R1, R2, H, angle);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_cone(const gp_Ax2 &Axes, const Standard_Real R1,
                                  const Standard_Real R2,
                                  const Standard_Real H) {
  try {
    BRepPrimAPI_MakeCone mw(Axes, R1, R2, H);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_cone(const gp_Ax2 &Axes, const Standard_Real R1,
                                  const Standard_Real R2, const Standard_Real H,
                                  const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeCone mw(Axes, R1, R2, H, angle);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_revolution(const Handle(Geom_Curve) & Meridian) {
  try {
    BRepPrimAPI_MakeRevolution mw(Meridian);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_revolution(const Handle(Geom_Curve) & Meridian,
                                        const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeRevolution mw(Meridian, angle);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_revolution(const Handle(Geom_Curve) & Meridian,
                                        const Standard_Real VMin,
                                        const Standard_Real VMax) {
  try {
    BRepPrimAPI_MakeRevolution mw(Meridian, VMin, VMax);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_revolution(const Handle(Geom_Curve) & Meridian,
                                        const Standard_Real VMin,
                                        const Standard_Real VMax,
                                        const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeRevolution mw(Meridian, VMin, VMax, angle);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_revolution(const gp_Ax2 &Axes,
                                        const Handle(Geom_Curve) & Meridian) {
  try {
    BRepPrimAPI_MakeRevolution mw(Axes, Meridian);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_revolution(const gp_Ax2 &Axes,
                                        const Handle(Geom_Curve) & Meridian,
                                        const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeRevolution mw(Axes, Meridian, angle);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_revolution(const gp_Ax2 &Axes,
                                        const Handle(Geom_Curve) & Meridian,
                                        const Standard_Real VMin,
                                        const Standard_Real VMax) {
  try {
    BRepPrimAPI_MakeRevolution mw(Axes, Meridian, VMin, VMax);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_revolution(const gp_Ax2 &Axes,
                                        const Handle(Geom_Curve) & Meridian,
                                        const Standard_Real VMin,
                                        const Standard_Real VMax,
                                        const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeRevolution mw(Axes, Meridian, VMin, VMax, angle);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_sphere(const Standard_Real R) {
  try {
    BRepPrimAPI_MakeSphere mw(R);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_sphere(const Standard_Real R,
                                    const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeSphere mw(R, angle);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_sphere(const Standard_Real R,
                                    const Standard_Real angle1,
                                    const Standard_Real angle2) {
  try {
    BRepPrimAPI_MakeSphere mw(R, angle1, angle2);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_sphere(const Standard_Real R,
                                    const Standard_Real angle1,
                                    const Standard_Real angle2,
                                    const Standard_Real angle3) {
  try {
    BRepPrimAPI_MakeSphere mw(R, angle1, angle2, angle3);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_sphere(const gp_Pnt &Center,
                                    const Standard_Real R) {
  try {
    BRepPrimAPI_MakeSphere mw(Center, R);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_sphere(const gp_Pnt &Center, const Standard_Real R,
                                    const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeSphere mw(Center, R, angle);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_sphere(const gp_Pnt &Center, const Standard_Real R,
                                    const Standard_Real angle1,
                                    const Standard_Real angle2) {
  try {
    BRepPrimAPI_MakeSphere mw(Center, R, angle1, angle2);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_sphere(const gp_Pnt &Center, const Standard_Real R,
                                    const Standard_Real angle1,
                                    const Standard_Real angle2,
                                    const Standard_Real angle3) {
  try {
    BRepPrimAPI_MakeSphere mw(Center, R, angle1, angle2, angle3);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_sphere(const gp_Ax2 &Axis, const Standard_Real R) {
  try {
    BRepPrimAPI_MakeSphere ms(Axis, R);
    return shell{ms.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_sphere(const gp_Ax2 &Axis, const Standard_Real R,
                                    const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeSphere ms(Axis, R, angle);
    return shell{ms.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_sphere(const gp_Ax2 &Axis, const Standard_Real R,
                                    const Standard_Real angle1,
                                    const Standard_Real angle2) {
  try {
    BRepPrimAPI_MakeSphere ms(Axis, R, angle1, angle2);
    return shell{ms.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_sphere(const gp_Ax2 &Axis, const Standard_Real R,
                                    const Standard_Real angle1,
                                    const Standard_Real angle2,
                                    const Standard_Real angle3) {
  try {
    BRepPrimAPI_MakeSphere ms(Axis, R, angle1, angle2, angle3);
    return shell{ms.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_torus(const Standard_Real R1,
                                   const Standard_Real R2) {
  try {
    BRepPrimAPI_MakeTorus mw(R1, R2);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
} // namespace topo

shell shell::make_shell_from_torus(const Standard_Real R1,
                                   const Standard_Real R2,
                                   const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeTorus mw(R1, R2, angle);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_torus(const Standard_Real R1,
                                   const Standard_Real R2,
                                   const Standard_Real angle1,
                                   const Standard_Real angle2) {
  try {
    BRepPrimAPI_MakeTorus mw(R1, R2, angle1, angle2);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_torus(const Standard_Real R1,
                                   const Standard_Real R2,
                                   const Standard_Real angle1,
                                   const Standard_Real angle2,
                                   const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeTorus mw(R1, R2, angle1, angle2, angle);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_torus(const gp_Ax2 &Axes, const Standard_Real R1,
                                   const Standard_Real R2) {
  try {
    BRepPrimAPI_MakeTorus mw(Axes, R1, R2);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_torus(const gp_Ax2 &Axes, const Standard_Real R1,
                                   const Standard_Real R2,
                                   const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeTorus mw(Axes, R1, R2, angle);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_torus(const gp_Ax2 &Axes, const Standard_Real R1,
                                   const Standard_Real R2,
                                   const Standard_Real angle1,
                                   const Standard_Real angle2) {
  try {
    BRepPrimAPI_MakeTorus mw(Axes, R1, R2, angle1, angle2);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_torus(const gp_Ax2 &Axes, const Standard_Real R1,
                                   const Standard_Real R2,
                                   const Standard_Real angle1,
                                   const Standard_Real angle2,
                                   const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeTorus mw(Axes, R1, R2, angle1, angle2, angle);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_wedge(const Standard_Real dx,
                                   const Standard_Real dy,
                                   const Standard_Real dz,
                                   const Standard_Real ltx) {
  try {
    BRepPrimAPI_MakeWedge mw(dx, dy, dz, ltx);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_wedge(const gp_Ax2 &Axes, const Standard_Real dx,
                                   const Standard_Real dy,
                                   const Standard_Real dz,
                                   const Standard_Real ltx) {
  try {
    BRepPrimAPI_MakeWedge mw(Axes, dx, dy, dz, ltx);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_wedge(
    const Standard_Real dx, const Standard_Real dy, const Standard_Real dz,
    const Standard_Real xmin, const Standard_Real zmin,
    const Standard_Real xmax, const Standard_Real zmax) {
  try {
    BRepPrimAPI_MakeWedge mw(dx, dy, dz, xmin, zmin, xmax, zmax);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

shell shell::make_shell_from_wedge(
    const gp_Ax2 &Axes, const Standard_Real dx, const Standard_Real dy,
    const Standard_Real dz, const Standard_Real xmin, const Standard_Real zmin,
    const Standard_Real xmax, const Standard_Real zmax) {
  try {
    BRepPrimAPI_MakeWedge mw(Axes, dx, dy, dz, xmin, zmin, xmax, zmax);
    return shell{mw.Shell()};
  } catch (...) {
    return shell{};
  }
}

int shell::sweep(const wire &spine, std::vector<shape *> profiles,
                 int cornerMode) {
  try {
    BRepOffsetAPI_MakePipeShell PS(spine.value());

    switch (cornerMode) {
    case 1:
      PS.SetTransitionMode(BRepBuilderAPI_RightCorner);
      break;
    case 2:
      PS.SetTransitionMode(BRepBuilderAPI_RoundCorner);
      break;
    default:
      PS.SetTransitionMode(BRepBuilderAPI_Transformed);
      break;
    }

    for (unsigned i = 0; i < profiles.size(); i++) {
      PS.Add(profiles[i]->value());
    }

    if (!PS.IsReady()) {
      throw std::runtime_error("Failed to create sweep");
    }

    PS.Build();

    _shape = PS.Shape();

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to create sweep");
    }
    return 0;
  }
  return 1;
}

} // namespace topo
} // namespace flywave
