#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <BRepBuilderAPI_Copy.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeSolid.hxx>
#include <BRepBuilderAPI_NurbsConvert.hxx>
#include <BRepClass3d_SolidClassifier.hxx>
#include <BRepFeat_Gluer.hxx>
#include <BRepFeat_MakeDPrism.hxx>
#include <BRepFeat_MakeLinearForm.hxx>
#include <BRepFeat_MakePipe.hxx>
#include <BRepFeat_MakePrism.hxx>
#include <BRepFeat_MakeRevol.hxx>
#include <BRepFeat_MakeRevolutionForm.hxx>
#include <BRepFilletAPI_MakeChamfer.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepGProp.hxx>
#include <BRepOffsetAPI_DraftAngle.hxx>
#include <BRepOffsetAPI_MakeDraft.hxx>
#include <BRepOffsetAPI_MakeEvolved.hxx>
#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepOffsetAPI_MakeThickSolid.hxx>
#include <BRepOffsetAPI_Sewing.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <BRepPrimAPI_MakeRevolution.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakeWedge.hxx>
#include <BRep_Builder.hxx>
#include <GProp_GProps.hxx>
#include <ShapeAnalysis_FreeBounds.hxx>
#include <ShapeFix_Wire.hxx>
#include <TopExp.hxx>
#include <TopTools_HSequenceOfShape.hxx>
#include <TopoDS.hxx>

#include "comp_solid.hh"
#include "edge.hh"
#include "face.hh"
#include "shell.hh"
#include "solid.hh"
#include "wire.hh"

namespace flywave {
namespace topo {

solid::solid(TopoDS_Shape shp) : shape(shp) {
  TopAbs_ShapeEnum type = shp.ShapeType();
  if (type == TopAbs_SOLID || type == TopAbs_COMPSOLID) {
    _shape = shp;
  } else {
    int solids = 0;
    TopExp_Explorer ex;

    for (ex.Init(shp, TopAbs_SOLID); ex.More(); ex.Next()) {
      solids++;
    }

    for (ex.Init(shp, TopAbs_COMPSOLID); ex.More(); ex.Next()) {
      solids++;
    }

    if (solids == 1) {
      for (ex.Init(shp, TopAbs_SOLID); ex.More(); ex.Next()) {
        _shape = ex.Current();
      }
      for (ex.Init(shp, TopAbs_COMPSOLID); ex.More(); ex.Next()) {
        _shape = ex.Current();
      }
    } else {
      BRep_Builder B;
      TopoDS_Compound C;
      B.MakeCompound(C);

      for (ex.Init(shp, TopAbs_SOLID); ex.More(); ex.Next()) {
        B.Add(C, ex.Current());
      }

      for (ex.Init(shp, TopAbs_COMPSOLID); ex.More(); ex.Next()) {
        B.Add(C, ex.Current());
      }
      _shape = C;
    }
  }
}

TopoDS_Solid &solid::value() { return TopoDS::Solid(_shape); }

const TopoDS_Solid &solid::value() const { return TopoDS::Solid(_shape); }

shape solid::copy(bool deep) const {
  try {
    BRepBuilderAPI_Copy _copy(_shape, deep);
    _copy.Build();

    if (!_copy.IsDone())
      throw std::runtime_error("Section operation failed");

    auto shp = _copy.Shape();

    if (shp.IsNull())
      throw std::runtime_error("Shell operation resulted in Null shape");

    return solid{shp};
  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
  }
  return solid{};
}

solid solid::make_solid(const comp_solid &S) {
  try {
    BRepBuilderAPI_MakeSolid ms(S.value());
    return solid{ms.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid(const topo::shell &S) {
  try {
    BRepBuilderAPI_MakeSolid ms(S.value());
    return solid{ms.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid(const topo::shell &S1, const topo::shell &S2) {
  try {
    BRepBuilderAPI_MakeSolid ms(S1.value(), S2.value());
    return solid{ms.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid(const topo::shell &S1, const topo::shell &S2,
                        const topo::shell &S3) {
  try {
    BRepBuilderAPI_MakeSolid ms(S1.value(), S2.value(), S3.value());
    return solid{ms.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid(std::vector<shell> &shells) {
  try {
    BRepBuilderAPI_MakeSolid ms;
    for (auto _shell : shells) {
      ms.Add(_shell.value());
    }
    return solid{ms.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid(std::initializer_list<shell> shells) {
  try {
    BRepBuilderAPI_MakeSolid ms;
    for (auto _shell : shells) {
      ms.Add(_shell.value());
    }
    return solid{ms.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid(const solid &So) {
  try {
    BRepBuilderAPI_MakeSolid ms(So.value());
    return solid{ms.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid(const solid &So, const topo::shell &S) {
  try {
    BRepBuilderAPI_MakeSolid ms(So.value(), S.value());
    return solid{ms.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_box(const Standard_Real dx, const Standard_Real dy,
                                 const Standard_Real dz) {
  try {
    BRepPrimAPI_MakeBox mb(dx, dy, dz);
    return solid{mb.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_box(const gp_Pnt &P, const Standard_Real dx,
                                 const Standard_Real dy,
                                 const Standard_Real dz) {
  try {
    BRepPrimAPI_MakeBox mb(P, dx, dy, dz);
    return solid{mb.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_box(const gp_Pnt &P1, const gp_Pnt &P2) {
  try {
    BRepPrimAPI_MakeBox mb(P1, P2);
    return solid{mb.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_box(const gp_Ax2 &Axes, const Standard_Real dx,
                                 const Standard_Real dy,
                                 const Standard_Real dz) {
  try {
    BRepPrimAPI_MakeBox mb(Axes, dx, dy, dz);
    return solid{mb.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_cylinder(const Standard_Real R,
                                      const Standard_Real H) {
  try {
    BRepPrimAPI_MakeCylinder mw(R, H);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_cylinder(const Standard_Real R,
                                      const Standard_Real H,
                                      const Standard_Real Angle) {
  try {
    BRepPrimAPI_MakeCylinder mw(R, H, Angle);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_cylinder(const gp_Ax2 &Axes, const Standard_Real R,
                                      const Standard_Real H) {
  try {
    BRepPrimAPI_MakeCylinder mw(Axes, R, H);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_cylinder(const gp_Ax2 &Axes, const Standard_Real R,
                                      const Standard_Real H,
                                      const Standard_Real Angle) {
  try {
    BRepPrimAPI_MakeCylinder mw(Axes, R, H, Angle);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_cone(const Standard_Real R1,
                                  const Standard_Real R2,
                                  const Standard_Real H) {
  try {
    BRepPrimAPI_MakeCone mw(R1, R2, H);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
} // namespace topo

solid solid::make_solid_from_cone(const Standard_Real R1,
                                  const Standard_Real R2, const Standard_Real H,
                                  const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeCone mw(R1, R2, H, angle);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_cone(const gp_Ax2 &Axes, const Standard_Real R1,
                                  const Standard_Real R2,
                                  const Standard_Real H) {
  try {
    BRepPrimAPI_MakeCone mw(Axes, R1, R2, H);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_cone(const gp_Ax2 &Axes, const Standard_Real R1,
                                  const Standard_Real R2, const Standard_Real H,
                                  const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeCone mw(Axes, R1, R2, H, angle);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_revolution(const Handle(Geom_Curve) & Meridian) {
  try {
    BRepPrimAPI_MakeRevolution mw(Meridian);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_revolution(const Handle(Geom_Curve) & Meridian,
                                        const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeRevolution mw(Meridian, angle);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_revolution(const Handle(Geom_Curve) & Meridian,
                                        const Standard_Real VMin,
                                        const Standard_Real VMax) {
  try {
    BRepPrimAPI_MakeRevolution mw(Meridian, VMin, VMax);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_revolution(const Handle(Geom_Curve) & Meridian,
                                        const Standard_Real VMin,
                                        const Standard_Real VMax,
                                        const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeRevolution mw(Meridian, VMin, VMax, angle);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_revolution(const gp_Ax2 &Axes,
                                        const Handle(Geom_Curve) & Meridian) {
  try {
    BRepPrimAPI_MakeRevolution mw(Axes, Meridian);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_revolution(const gp_Ax2 &Axes,
                                        const Handle(Geom_Curve) & Meridian,
                                        const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeRevolution mw(Axes, Meridian, angle);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_revolution(const gp_Ax2 &Axes,
                                        const Handle(Geom_Curve) & Meridian,
                                        const Standard_Real VMin,
                                        const Standard_Real VMax) {
  try {
    BRepPrimAPI_MakeRevolution mw(Axes, Meridian, VMin, VMax);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_revolution(const gp_Ax2 &Axes,
                                        const Handle(Geom_Curve) & Meridian,
                                        const Standard_Real VMin,
                                        const Standard_Real VMax,
                                        const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeRevolution mw(Axes, Meridian, VMin, VMax, angle);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_sphere(const Standard_Real R) {
  try {
    BRepPrimAPI_MakeSphere mw(R);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_sphere(const Standard_Real R,
                                    const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeSphere mw(R, angle);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_sphere(const Standard_Real R,
                                    const Standard_Real angle1,
                                    const Standard_Real angle2) {
  try {
    BRepPrimAPI_MakeSphere mw(R, angle1, angle2);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_sphere(const Standard_Real R,
                                    const Standard_Real angle1,
                                    const Standard_Real angle2,
                                    const Standard_Real angle3) {
  try {
    BRepPrimAPI_MakeSphere mw(R, angle1, angle2, angle3);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_sphere(const gp_Pnt &Center,
                                    const Standard_Real R) {
  try {
    BRepPrimAPI_MakeSphere mw(Center, R);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_sphere(const gp_Pnt &Center, const Standard_Real R,
                                    const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeSphere mw(Center, R, angle);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_sphere(const gp_Pnt &Center, const Standard_Real R,
                                    const Standard_Real angle1,
                                    const Standard_Real angle2) {
  try {
    BRepPrimAPI_MakeSphere mw(Center, R, angle1, angle2);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_sphere(const gp_Pnt &Center, const Standard_Real R,
                                    const Standard_Real angle1,
                                    const Standard_Real angle2,
                                    const Standard_Real angle3) {
  try {
    BRepPrimAPI_MakeSphere mw(Center, R, angle1, angle2, angle3);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_sphere(const gp_Ax2 &Axis, const Standard_Real R) {
  try {
    BRepPrimAPI_MakeSphere ms(Axis, R);
    return solid{ms.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_sphere(const gp_Ax2 &Axis, const Standard_Real R,
                                    const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeSphere ms(Axis, R, angle);
    return solid{ms.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_sphere(const gp_Ax2 &Axis, const Standard_Real R,
                                    const Standard_Real angle1,
                                    const Standard_Real angle2) {
  try {
    BRepPrimAPI_MakeSphere ms(Axis, R, angle1, angle2);
    return solid{ms.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_sphere(const gp_Ax2 &Axis, const Standard_Real R,
                                    const Standard_Real angle1,
                                    const Standard_Real angle2,
                                    const Standard_Real angle3) {
  try {
    BRepPrimAPI_MakeSphere ms(Axis, R, angle1, angle2, angle3);
    return solid{ms.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_torus(const Standard_Real R1,
                                   const Standard_Real R2) {
  try {
    BRepPrimAPI_MakeTorus mw(R1, R2);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_torus(const Standard_Real R1,
                                   const Standard_Real R2,
                                   const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeTorus mw(R1, R2, angle);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_torus(const Standard_Real R1,
                                   const Standard_Real R2,
                                   const Standard_Real angle1,
                                   const Standard_Real angle2) {
  try {
    BRepPrimAPI_MakeTorus mw(R1, R2, angle1, angle2);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
} // namespace topo

solid solid::make_solid_from_torus(const Standard_Real R1,
                                   const Standard_Real R2,
                                   const Standard_Real angle1,
                                   const Standard_Real angle2,
                                   const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeTorus mw(R1, R2, angle1, angle2, angle);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_torus(const gp_Ax2 &Axes, const Standard_Real R1,
                                   const Standard_Real R2) {
  try {
    BRepPrimAPI_MakeTorus mw(Axes, R1, R2);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
} // namespace flywave

solid solid::make_solid_from_torus(const gp_Ax2 &Axes, const Standard_Real R1,
                                   const Standard_Real R2,
                                   const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeTorus mw(Axes, R1, R2, angle);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_torus(const gp_Ax2 &Axes, const Standard_Real R1,
                                   const Standard_Real R2,
                                   const Standard_Real angle1,
                                   const Standard_Real angle2) {
  try {
    BRepPrimAPI_MakeTorus mw(Axes, R1, R2, angle1, angle2);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_torus(const gp_Ax2 &Axes, const Standard_Real R1,
                                   const Standard_Real R2,
                                   const Standard_Real angle1,
                                   const Standard_Real angle2,
                                   const Standard_Real angle) {
  try {
    BRepPrimAPI_MakeTorus mw(Axes, R1, R2, angle1, angle2, angle);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_wedge(const Standard_Real dx,
                                   const Standard_Real dy,
                                   const Standard_Real dz,
                                   const Standard_Real ltx) {
  try {
    BRepPrimAPI_MakeWedge mw(dx, dy, dz, ltx);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_wedge(const gp_Ax2 &Axes, const Standard_Real dx,
                                   const Standard_Real dy,
                                   const Standard_Real dz,
                                   const Standard_Real ltx) {
  try {
    BRepPrimAPI_MakeWedge mw(Axes, dx, dy, dz, ltx);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_wedge(
    const Standard_Real dx, const Standard_Real dy, const Standard_Real dz,
    const Standard_Real xmin, const Standard_Real zmin,
    const Standard_Real xmax, const Standard_Real zmax) {
  try {
    BRepPrimAPI_MakeWedge mw(dx, dy, dz, xmin, zmin, xmax, zmax);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid_from_wedge(
    const gp_Ax2 &Axes, const Standard_Real dx, const Standard_Real dy,
    const Standard_Real dz, const Standard_Real xmin, const Standard_Real zmin,
    const Standard_Real xmax, const Standard_Real zmax) {
  try {
    BRepPrimAPI_MakeWedge mw(Axes, dx, dy, dz, xmin, zmin, xmax, zmax);
    return solid{mw.Solid()};
  } catch (...) {
    return solid{};
  }
}

solid solid::make_solid(std::vector<face> &faces, double tolerance) {
  solid s;
  try {
    BRep_Builder B;
    TopoDS_Shape aShape, sh;

    tolerance = std::max(Precision::Confusion() * 10.0, tolerance);

    BRepOffsetAPI_Sewing SW(tolerance);
    unsigned i = 0;
    for (; i < faces.size(); i++) {
      SW.Add(faces[i].value());
    }
    SW.Perform();

    sh = SW.SewedShape();
    if (sh.ShapeType() == TopAbs_FACE && i == 1) {
      TopoDS_Shell ss;
      B.MakeShell(ss);
      B.Add(ss, sh);
      aShape = ss;
    } else {
      TopExp_Explorer exp(sh, TopAbs_SHELL);
      Standard_Integer ish = 0;
      for (; exp.More(); exp.Next()) {
        aShape = exp.Current();
        ish++;
      }

      if (ish != 1)
        aShape = SW.SewedShape();
    }

    TopoDS_Solid sol;
    B.MakeSolid(sol);
    B.Add(sol, aShape);

    BRepClass3d_SolidClassifier SC(sol);
    SC.PerformInfinitePoint(Precision::Confusion());
    if (SC.State() == TopAbs_IN) {
      B.MakeSolid(sol);
      B.Add(sol, aShape.Reversed());
    }

    s = solid{sol};

    if (!s.fix_shape())
      throw std::runtime_error("solid not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to create solid");
    }
  }
  return s;
}

solid solid::make_solid(std::initializer_list<face> faces, double tolerance) {
  solid s;
  try {
    BRep_Builder B;
    TopoDS_Shape aShape, sh;

    tolerance = std::max(Precision::Confusion() * 10.0, tolerance);

    BRepOffsetAPI_Sewing SW(tolerance);
    unsigned i = 0;
    for (auto _f : faces) {
      SW.Add(_f.value());
    }
    SW.Perform();

    sh = SW.SewedShape();
    if (sh.ShapeType() == TopAbs_FACE && i == 1) {
      TopoDS_Shell ss;
      B.MakeShell(ss);
      B.Add(ss, sh);
      aShape = ss;
    } else {
      TopExp_Explorer exp(sh, TopAbs_SHELL);
      Standard_Integer ish = 0;
      for (; exp.More(); exp.Next()) {
        aShape = exp.Current();
        ish++;
      }

      if (ish != 1)
        aShape = SW.SewedShape();
    }

    TopoDS_Solid sol;
    B.MakeSolid(sol);
    B.Add(sol, aShape);

    BRepClass3d_SolidClassifier SC(sol);
    SC.PerformInfinitePoint(Precision::Confusion());
    if (SC.State() == TopAbs_IN) {
      B.MakeSolid(sol);
      B.Add(sol, aShape.Reversed());
    }

    s = solid{sol};

    if (!s.fix_shape())
      throw std::runtime_error("solid not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to create solid");
    }
  }
  return s;
}

int solid::num_solids() const {
  const TopoDS_Shape &shp = value();
  if (shp.ShapeType() == TopAbs_SOLID) {
    return 1;
  } else {
    TopTools_IndexedMapOfShape compsolids;
    TopExp::MapShapes(shp, TopAbs_COMPSOLID, compsolids);

    TopTools_IndexedMapOfShape solids;
    TopExp::MapShapes(shp, TopAbs_SOLID, solids);

    return solids.Extent() + compsolids.Extent();
  }
}

int solid::num_faces() const {
  TopTools_IndexedMapOfShape anIndices;
  TopExp::MapShapes(value(), TopAbs_FACE, anIndices);
  return anIndices.Extent();
}

double solid::area() const {
  GProp_GProps prop;
  BRepGProp::SurfaceProperties(value(), prop);
  return prop.Mass();
}

double solid::volume() const {
  GProp_GProps prop;
  BRepGProp::VolumeProperties(value(), prop);
  return prop.Mass();
}

Bnd_Box solid::inertia() const {
  GProp_GProps prop;
  BRepGProp::VolumeProperties(value(), prop);
  gp_Mat mat = prop.MatrixOfInertia();
  Bnd_Box bbox;
  bbox.Update(mat(1, 1), mat(2, 2), mat(3, 3), mat(1, 2), mat(1, 3), mat(2, 3));
  return bbox;
}

gp_Pnt solid::centre_of_mass() const {
  GProp_GProps prop;
  BRepGProp::VolumeProperties(value(), prop);
  gp_Pnt cg = prop.CentreOfMass();
  return cg;
}

int solid::extrude(const face &f, gp_Pnt p1, gp_Pnt p2) {
  try {
    gp_Vec direction(gp_Pnt(p1.X(), p1.Y(), p1.Z()),
                     gp_Pnt(p2.X(), p2.Y(), p2.Z()));
    gp_Ax1 axisOfRevolution(gp_Pnt(p1.X(), p1.Y(), p1.Z()), direction);

    BRepPrimAPI_MakePrism MP(f.value(), direction, Standard_False);

    _shape = MP.Shape();

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to extrude");
    }
    return 0;
  }
  return 1;
}

int solid::extrude(const face &f, gp_Vec d) {
  try {
    BRepPrimAPI_MakePrism MP(f.value(), d, Standard_False);

    _shape = MP.Shape();

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to extrude");
    }
    return 0;
  }
  return 1;
}

int solid::revolve(const face &f, gp_Pnt p1, gp_Pnt p2, double angle) {
  try {
    gp_Dir direction(p2.X() - p1.X(), p2.Y() - p1.Y(), p2.Z() - p1.Z());
    gp_Ax1 axisOfRevolution(gp_Pnt(p1.X(), p1.Y(), p1.Z()), direction);
    BRepPrimAPI_MakeRevol MR(f.value(), axisOfRevolution, angle,
                             Standard_False);

    _shape = MR.Shape();

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to revolve");
    }
    return 0;
  }
  return 1;
}

int solid::loft(std::vector<shape> &profiles, bool ruled, double tolerance) {
  try {
    Standard_Boolean isSolid = Standard_True;
    Standard_Boolean isRuled = Standard_True;

    if (!ruled)
      isRuled = Standard_False;

    BRepOffsetAPI_ThruSections TS(isSolid, isRuled, tolerance);

    for (unsigned i = 0; i < profiles.size(); i++) {
      if (profiles[i].value().ShapeType() == TopAbs_WIRE) {
        TS.AddWire(TopoDS::Wire(profiles[i].value()));
      } else {
        TS.AddVertex(TopoDS::Vertex(profiles[i].value()));
      }
    }

    TS.CheckCompatibility(Standard_False);
    TS.Build();

    _shape = TS.Shape();

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to loft");
    }
    return 0;
  }
  return 1;
}

int solid::pipe(const face &f, const wire &w) {
  try {
    BRepOffsetAPI_MakePipe MP(w.value(), f.value());
    _shape = MP.Shape();

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to create pipe");
    }
    return 0;
  }
  return 1;
}

int solid::sweep(const wire &spine, std::vector<shape> &profiles,
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
      PS.Add(profiles[i].value(),false,true);
    }
    if (!PS.IsReady()) {
      throw std::runtime_error("Failed to create sweep");
    }
    PS.Build();
    if (!PS.MakeSolid()) {
      throw std::runtime_error("Failed to create a solid object from sweep");
    }
    _shape = PS.Shape();

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to create sweep");
    }
    return 0;
  }
  return 1;
}

int solid::boolean(const solid &tool, bool_op_type op) {
  try {
    TopoDS_Shape shape;
    switch (op) {
    case bool_op_type::BOOL_FUSE: {
      BRepAlgoAPI_Fuse FU(_shape, tool._shape);
      if (!FU.IsDone())
        throw std::runtime_error("operation failed");
      shape = FU.Shape();
      break;
    }
    case bool_op_type::BOOL_CUT: {
      BRepAlgoAPI_Cut CU(_shape, tool._shape);
      if (!CU.IsDone())
        throw std::runtime_error("operation failed");
      shape = CU.Shape();
      break;
    }
    case bool_op_type::BOOL_COMMON: {
      BRepAlgoAPI_Common CO(tool._shape, _shape);
      if (!CO.IsDone())
        throw std::runtime_error("operation failed");
      shape = CO.Shape();
      break;
    }
    default:
      throw std::runtime_error("unknown operation");
      break;
    }

    TopoDS_Iterator It(shape, Standard_True, Standard_True);
    int found = 0;
    for (; It.More(); It.Next())
      found++;
    if (found == 0) {
      throw std::runtime_error("result object is empty compound");
    }

    _shape = shape;

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed in boolean operation");
    }
    return 0;
  }
  return 1;
}

int solid::fillet(std::vector<edge> &edges, std::vector<double> radius) {
  int edges_size = edges.size();
  int radius_size = radius.size();

  try {
    BRepFilletAPI_MakeFillet fill(_shape);

    TopTools_IndexedDataMapOfShapeListOfShape mapEdgeFace;
    TopExp::MapShapesAndAncestors(_shape, TopAbs_EDGE, TopAbs_FACE,
                                  mapEdgeFace);

    for (unsigned i = 0; i < edges.size(); i++) {
      edge *e = &edges[i];

      if (BRep_Tool::Degenerated(e->value()))
        continue;

      const TopoDS_Face &face =
          TopoDS::Face(mapEdgeFace.FindFromKey(e->value()).First());

      if (BRep_Tool::IsClosed(e->value(), face))
        continue;

      if (radius_size == 1) {
        fill.Add(radius[0], e->value());
      } else if (radius_size == edges_size) {
        fill.Add(radius[i], e->value());
      } else if (radius_size == 2 * edges_size) {
        fill.Add(radius[2 * i + 0], radius[2 * i + 1], e->value());
      } else {
        throw std::runtime_error("radius argument size not valid");
        ;
      }
    }

    fill.Build();

    if (!fill.IsDone())
      throw std::runtime_error("Filler operation failed");

    const TopoDS_Shape &tmp = fill.Shape();

    if (tmp.IsNull())
      throw std::runtime_error("Fillet operation resulted in Null shape");

    _shape = tmp;

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to fillet solid");
    }
    return 0;
  }
  return 1;
}

int solid::chamfer(std::vector<edge> &edges, std::vector<double> distances) {
  int edges_size = edges.size();
  int distances_size = distances.size();

  try {
    BRepFilletAPI_MakeChamfer CF(_shape);

    TopTools_IndexedDataMapOfShapeListOfShape mapEdgeFace;
    TopExp::MapShapesAndAncestors(_shape, TopAbs_EDGE, TopAbs_FACE,
                                  mapEdgeFace);

    for (unsigned i = 0; i < edges.size(); i++) {
      edge *e = &edges[i];

      if (BRep_Tool::Degenerated(e->value()))
        continue;

      const TopoDS_Face &face =
          TopoDS::Face(mapEdgeFace.FindFromKey(e->value()).First());

      if (BRep_Tool::IsClosed(e->value(), face))
        continue;

      if (distances_size == 1) {
        CF.Add(distances[0], e->value(), face);

      } else if (distances_size == edges_size) {
        CF.Add(distances[i], e->value(), face);

      } else {
        throw std::runtime_error("size of distances argument not correct");
        ;
      }
    }

    CF.Build();

    if (!CF.IsDone())
      throw std::runtime_error("Failed to chamfer solid");

    const TopoDS_Shape &tmp = CF.Shape();

    if (tmp.IsNull())
      throw std::runtime_error("Chamfer operaton return Null shape");

    _shape = tmp;

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to chamfer solid");
    }
    return 0;
  }
  return 1;
}

int solid::shelling(std::vector<face> &faces, double offset, double tolerance) {
  try {
    TopTools_ListOfShape facelist;
    for (unsigned i = 0; i < faces.size(); i++) {
      face *f = &faces[i];
      facelist.Append(f->value());
    }

    BRepOffsetAPI_MakeThickSolid TS(_shape, facelist, offset, tolerance);
    TS.Build();

    if (!TS.IsDone())
      throw std::runtime_error("Shell operation failed");

    const TopoDS_Shape &tmp = TS.Shape();

    if (tmp.IsNull())
      throw std::runtime_error("Shell operation resulted in Null shape");

    _shape = tmp;

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to shell solid");
    }
    return 0;
  }
  return 1;
}

int solid::offset(const face &f, double offset, double tolerance) {
  try {
    BRepOffset_MakeOffset MO(f.value(), offset, tolerance, BRepOffset_Skin,
                             Standard_False, Standard_False, GeomAbs_Arc,
                             Standard_True);

    _shape = MO.Shape();

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
    return 0;
  }
  return 1;
}

int solid::draft(std::vector<face> &faces, gp_Dir d, double angle, gp_Pln p) {
  try {
    BRepOffsetAPI_DraftAngle MD;
    for (unsigned i = 0; i < faces.size(); i++) {
      face *f = &faces[i];
      MD.Add(f->value(), d, angle, p);
    }
    MD.Build();

    if (!MD.IsDone())
      throw std::runtime_error("draft operation failed");

    const TopoDS_Shape &tmp = MD.Shape();

    if (tmp.IsNull())
      throw std::runtime_error("draft operation resulted in Null shape");

    _shape = tmp;

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
    return 0;
  }
  return 1;
}

int solid::evolved(const face &Spine, const wire &Profil) {
  try {
    BRepOffsetAPI_MakeEvolved MD(Spine.value(), Profil.value(), GeomAbs_Arc,
                                 true, true);

    MD.Build();

    if (!MD.IsDone())
      throw std::runtime_error("evolved operation failed");

    const TopoDS_Shape &tmp = MD.Shape();

    if (tmp.IsNull())
      throw std::runtime_error("evolved operation resulted in Null shape");

    _shape = tmp;

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
    return 0;
  }
  return 1;
}

int solid::evolved(const wire &Spine, const wire &Profil) {
  try {
    BRepOffsetAPI_MakeEvolved MD(Spine.value(), Profil.value(), GeomAbs_Arc,
                                 true, true);

    MD.Build();

    if (!MD.IsDone())
      throw std::runtime_error("evolved operation failed");

    const TopoDS_Shape &tmp = MD.Shape();

    if (tmp.IsNull())
      throw std::runtime_error("evolved operation resulted in Null shape");

    _shape = tmp;

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
    return 0;
  }
  return 1;
}

int solid::feat_prism(const face &f, gp_Dir d, double height, bool fuse) {
  try {
    BRepFeat_MakePrism MP(_shape, f.value(), TopoDS_Face(), d, fuse, false);
    MP.Perform(height);

    if (!MP.IsDone())
      throw std::runtime_error("evolved operation failed");

    const TopoDS_Shape &tmp = MP.Shape();

    if (tmp.IsNull())
      throw std::runtime_error("evolved operation resulted in Null shape");

    _shape = tmp;

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
    return 0;
  }
  return 1;
}

int solid::feat_prism(const face &f, gp_Dir d, const face &from,
                      const face &end, bool fuse) {
  try {
    BRepFeat_MakePrism MP(_shape, f.value(), TopoDS_Face(), d, fuse, false);
    MP.Perform(from.value(), end.value());

    if (!MP.IsDone())
      throw std::runtime_error("evolved operation failed");

    const TopoDS_Shape &tmp = MP.Shape();

    if (tmp.IsNull())
      throw std::runtime_error("evolved operation resulted in Null shape");

    _shape = tmp;

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
    return 0;
  }
  return 1;
}

int solid::feat_prism(const face &f, gp_Dir d, const face &until, bool fuse) {
  try {
    BRepFeat_MakePrism MP(_shape, f.value(), TopoDS_Face(), d, fuse, false);
    MP.Perform(until.value());

    if (!MP.IsDone())
      throw std::runtime_error("evolved operation failed");

    const TopoDS_Shape &tmp = MP.Shape();

    if (tmp.IsNull())
      throw std::runtime_error("evolved operation resulted in Null shape");

    _shape = tmp;

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
    return 0;
  }
  return 1;
}

int solid::feat_draft_prism(const face &f, double angle, double height,
                            bool fuse) {
  try {
    BRepFeat_MakeDPrism MP(_shape, f.value(), TopoDS_Face(), angle, fuse,
                           false);
    MP.Perform(height);

    if (!MP.IsDone())
      throw std::runtime_error("evolved operation failed");

    const TopoDS_Shape &tmp = MP.Shape();

    if (tmp.IsNull())
      throw std::runtime_error("evolved operation resulted in Null shape");

    _shape = tmp;

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
    return 0;
  }
  return 1;
}

int solid::feat_draft_prism(const face &f, double angle, const face &from,
                            const face &end, bool fuse) {
  try {
    BRepFeat_MakeDPrism MP(_shape, f.value(), TopoDS_Face(), angle, fuse,
                           false);
    MP.Perform(from.value(), end.value());

    if (!MP.IsDone())
      throw std::runtime_error("evolved operation failed");

    const TopoDS_Shape &tmp = MP.Shape();

    if (tmp.IsNull())
      throw std::runtime_error("evolved operation resulted in Null shape");

    _shape = tmp;

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
    return 0;
  }
  return 1;
}

int solid::feat_draft_prism(const face &f, double angle, const face &until,
                            bool fuse) {
  try {
    BRepFeat_MakeDPrism MP(_shape, f.value(), TopoDS_Face(), angle, fuse,
                           false);
    MP.Perform(until.value());

    if (!MP.IsDone())
      throw std::runtime_error("evolved operation failed");

    const TopoDS_Shape &tmp = MP.Shape();

    if (tmp.IsNull())
      throw std::runtime_error("evolved operation resulted in Null shape");

    _shape = tmp;

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
    return 0;
  }
  return 1;
}

int solid::feat_revol(const face &f, const gp_Ax1 &Axes, const face &from,
                      const face &end, bool fuse) {
  try {
    BRepFeat_MakeRevol MP(_shape, f.value(), TopoDS_Face(), Axes, fuse, false);
    MP.Perform(from.value(), end.value());

    if (!MP.IsDone())
      throw std::runtime_error("evolved operation failed");

    const TopoDS_Shape &tmp = MP.Shape();

    if (tmp.IsNull())
      throw std::runtime_error("evolved operation resulted in Null shape");

    _shape = tmp;

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
    return 0;
  }
  return 1;
}

int solid::feat_revol(const face &f, const gp_Ax1 &Axes, const face &until,
                      bool fuse) {
  try {
    BRepFeat_MakeRevol MP(_shape, f.value(), TopoDS_Face(), Axes, fuse, false);
    MP.Perform(until.value());

    if (!MP.IsDone())
      throw std::runtime_error("evolved operation failed");

    const TopoDS_Shape &tmp = MP.Shape();

    if (tmp.IsNull())
      throw std::runtime_error("evolved operation resulted in Null shape");

    _shape = tmp;

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
    return 0;
  }
  return 1;
}

int solid::feat_pipe(const face &f, const wire &Spine, const face &from,
                     const face &end, bool fuse) {
  try {
    BRepFeat_MakePipe MP(_shape, f.value(), TopoDS_Face(), Spine.value(), fuse,
                         false);
    MP.Perform(from.value(), end.value());

    if (!MP.IsDone())
      throw std::runtime_error("evolved operation failed");

    const TopoDS_Shape &tmp = MP.Shape();

    if (tmp.IsNull())
      throw std::runtime_error("evolved operation resulted in Null shape");

    _shape = tmp;

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
    return 0;
  }
  return 1;
}

int solid::feat_pipe(const face &f, const wire &Spine, const face &until,
                     bool fuse) {
  try {
    BRepFeat_MakePipe MP(_shape, f.value(), TopoDS_Face(), Spine.value(), fuse,
                         false);
    MP.Perform(until.value());

    if (!MP.IsDone())
      throw std::runtime_error("evolved operation failed");

    const TopoDS_Shape &tmp = MP.Shape();

    if (tmp.IsNull())
      throw std::runtime_error("evolved operation resulted in Null shape");

    _shape = tmp;

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
    return 0;
  }
  return 1;
}

int solid::linear_form(const wire &w, const Handle(Geom_Plane) & p, gp_Dir d,
                       gp_Dir d1, bool fuse) {
  try {
    BRepFeat_MakeLinearForm MLF(_shape, w.value(), p, d, d1, fuse, false);
    MLF.Perform();

    if (!MLF.IsDone())
      throw std::runtime_error("evolved operation failed");

    const TopoDS_Shape &tmp = MLF.Shape();

    if (tmp.IsNull())
      throw std::runtime_error("evolved operation resulted in Null shape");

    _shape = tmp;

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
    return 0;
  }
  return 1;
}

int solid::revolution_form(const wire &w, const Handle(Geom_Plane) & p,
                           const gp_Ax1 &Axes, Standard_Real h1,
                           Standard_Real h2, bool fuse) {
  try {
    bool Sliding = false;
    BRepFeat_MakeRevolutionForm MRF(_shape, w.value(), p, Axes, h1, h2, fuse,
                                    Sliding);
    MRF.Perform();

    if (!MRF.IsDone())
      throw std::runtime_error("evolved operation failed");

    const TopoDS_Shape &tmp = MRF.Shape();

    if (tmp.IsNull())
      throw std::runtime_error("evolved operation resulted in Null shape");

    _shape = tmp;

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
    return 0;
  }
  return 1;
}

boost::optional<face> solid::section(gp_Pnt pnt, gp_Pnt nor) {
  Handle(TopTools_HSequenceOfShape) wires = new TopTools_HSequenceOfShape;
  Handle(TopTools_HSequenceOfShape) edges = new TopTools_HSequenceOfShape;
  TopExp_Explorer ex;
  face ret;
  try {
    gp_Pln pln(gp_Pnt(pnt.X(), pnt.Y(), pnt.Z()),
               gp_Dir(nor.X(), nor.Y(), nor.Z()));

    BRepAlgoAPI_Section mkSection(_shape, pln);
    if (!mkSection.IsDone())
      throw std::runtime_error("Section operation failed");

    for (ex.Init(mkSection.Shape(), TopAbs_EDGE); ex.More(); ex.Next()) {
      if (!ex.Current().IsNull()) {
        edges->Append(TopoDS::Edge(ex.Current()));
      }
    }

    ShapeAnalysis_FreeBounds::ConnectEdgesToWires(edges, Precision::Confusion(),
                                                  Standard_True, wires);
    if (wires->Length() != 1)
      throw std::runtime_error("No edges created");

    const TopoDS_Wire &wire = TopoDS::Wire(wires->Value(1));

    BRepBuilderAPI_MakeFace MFInit(pln, wire, Standard_True);
    MFInit.Build();
    if (!MFInit.IsDone())
      throw std::runtime_error("Could not create face");

    ShapeFix_Wire fixer(wire, MFInit.Face(), 1.0e-6);
    fixer.FixEdgeCurves();
    fixer.Perform();

    BRepBuilderAPI_MakeFace MFRes(pln, fixer.Wire(), Standard_True);
    MFRes.Build();

    _shape = MFRes.Face();

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to create section");
    }
    return boost::none;
  }
  return {ret};
}

int solid::convert_to_nurbs() {
  try {
    BRepBuilderAPI_NurbsConvert nc;
    nc.Perform(_shape);
    TopoDS_Shape Slocal = nc.Shape();

    if (Slocal.IsNull())
      throw std::runtime_error("Shell operation resulted in Null shape");

    _shape = Slocal;

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
    return 0;
  }
  return 1;
}

} // namespace topo
} // namespace flywave
