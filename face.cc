#include "edge.hh"
#include "face.hh"
#include "solid.hh"
#include "wire.hh"

#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepBuilderAPI_Copy.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepCheck_Analyzer.hxx>
#include <BRepGProp.hxx>
#include <BRepOffsetAPI_MakeFilling.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepOffset_MakeOffset.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <GProp_GProps.hxx>
#include <TopExp.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopoDS.hxx>

namespace flywave {
namespace topo {

TopoDS_Face &face::value() { return TopoDS::Face(_shape); }

const TopoDS_Face &face::value() const { return TopoDS::Face(_shape); }

shape face::copy(bool deep) const {
  try {
    BRepBuilderAPI_Copy _copy(_shape, deep);
    _copy.Build();

    if (!_copy.IsDone())
      throw std::runtime_error("Section operation failed");

    auto shp = _copy.Shape();

    if (shp.IsNull())
      throw std::runtime_error("Shell operation resulted in Null shape");

    return face{shp};
  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
  }
  return face{};
}

face face::make_face(const face &F) {
  BRepBuilderAPI_MakeFace mf(F.value());
  return face{mf.Face()};
}

face face::make_face(const plane &P) {
  BRepBuilderAPI_MakeFace mf(cast_to_gp(P));
  return face{mf.Face()};
}

face face::make_face(const cylinder &C) {
  BRepBuilderAPI_MakeFace mf(cast_to_gp(C));
  return face{mf.Face()};
}

face face::make_face(const cone &C) {
  BRepBuilderAPI_MakeFace mf(cast_to_gp(C));
  return face{mf.Face()};
}

face face::make_face(const sphere &S) {
  BRepBuilderAPI_MakeFace mf(cast_to_gp(S));
  return face{mf.Face()};
}

face face::make_face(const torus &C) {
  BRepBuilderAPI_MakeFace mf(cast_to_gp(C));
  return face{mf.Face()};
}

face face::make_face(const geom_surface &S, const Standard_Real TolDegen) {
  BRepBuilderAPI_MakeFace mf(S, TolDegen);
  return face{mf.Face()};
}

face face::make_face(const plane &P, const Standard_Real UMin,
                     const Standard_Real UMax, const Standard_Real VMin,
                     const Standard_Real VMax) {
  BRepBuilderAPI_MakeFace mf(cast_to_gp(P), UMin, UMax, VMin, VMax);
  return face{mf.Face()};
}

face face::make_face(const cylinder &C, const Standard_Real UMin,
                     const Standard_Real UMax, const Standard_Real VMin,
                     const Standard_Real VMax) {
  BRepBuilderAPI_MakeFace mf(cast_to_gp(C), UMin, UMax, VMin, VMax);
  return face{mf.Face()};
}

face face::make_face(const cone &C, const Standard_Real UMin,
                     const Standard_Real UMax, const Standard_Real VMin,
                     const Standard_Real VMax) {
  BRepBuilderAPI_MakeFace mf(cast_to_gp(C), UMin, UMax, VMin, VMax);
  return face{mf.Face()};
}

face face::make_face(const sphere &S, const Standard_Real UMin,
                     const Standard_Real UMax, const Standard_Real VMin,
                     const Standard_Real VMax) {
  BRepBuilderAPI_MakeFace mf(cast_to_gp(S), UMin, UMax, VMin, VMax);
  return face{mf.Face()};
}

face face::make_face(const torus &C, const Standard_Real UMin,
                     const Standard_Real UMax, const Standard_Real VMin,
                     const Standard_Real VMax) {
  BRepBuilderAPI_MakeFace mf(cast_to_gp(C), UMin, UMax, VMin, VMax);
  return face{mf.Face()};
}

face face::make_face(const geom_surface &S, const Standard_Real UMin,
                     const Standard_Real UMax, const Standard_Real VMin,
                     const Standard_Real VMax, const Standard_Real TolDegen) {
  BRepBuilderAPI_MakeFace mf(S, UMin, UMax, VMin, VMax, TolDegen);
  return face{mf.Face()};
}

face face::make_face(const wire &W, const bool OnlyPlane) {
  BRepBuilderAPI_MakeFace mf(W.value(), OnlyPlane);
  return face{mf.Face()};
}

face face::make_face(const plane &P, const wire &W, const bool Inside) {
  BRepBuilderAPI_MakeFace mf(cast_to_gp(P), W.value(), Inside);
  return face{mf.Face()};
}

face face::make_face(const cylinder &C, const wire &W, const bool Inside) {
  BRepBuilderAPI_MakeFace mf(cast_to_gp(C), W.value(), Inside);
  return face{mf.Face()};
}

face face::make_face(const cone &C, const wire &W, const bool Inside) {
  BRepBuilderAPI_MakeFace mf(cast_to_gp(C), W.value(), Inside);
  return face{mf.Face()};
}

face face::make_face(const sphere &S, const wire &W, const bool Inside) {
  BRepBuilderAPI_MakeFace mf(cast_to_gp(S), W.value(), Inside);
  return face{mf.Face()};
}

face face::make_face(const torus &C, const wire &W, const bool Inside) {
  BRepBuilderAPI_MakeFace mf(cast_to_gp(C), W.value(), Inside);
  return face{mf.Face()};
}

face face::make_face(const geom_surface &S, const wire &W, const bool Inside) {
  BRepBuilderAPI_MakeFace mf(S, W.value(), Inside);
  return face{mf.Face()};
}

face face::make_face(const face &F, const wire &W) {
  BRepBuilderAPI_MakeFace mf(F.value(), W.value());
  return face{mf.Face()};
}

face face::make_face(std::vector<wire> &wires) {
  face f;
  try {
    const TopoDS_Wire &outerwire = wires[0].value();

    if (!wires[0].is_closed())
      throw std::runtime_error("Outer wire not closed");

    BRepBuilderAPI_MakeFace MF(outerwire);

    for (unsigned i = 1; i < wires.size(); i++) {
      const TopoDS_Wire &wire = wires[i].value();
      if (!wires[i].is_closed())
        throw std::runtime_error("Outer wire not closed");

      if (wire.Orientation() != outerwire.Orientation()) {
        MF.Add(TopoDS::Wire(wire.Reversed()));
      } else {
        MF.Add(wire);
      }
    }
    f = face{MF.Shape()};

    if (!f.fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to create face");
    }
  }
  return f;
}

face face::make_face(std::initializer_list<wire> wires) {
  face f;
  try {
    auto iter = wires.begin();
    const TopoDS_Wire &outerwire = iter->value();

    if (!wires.begin()->is_closed())
      throw std::runtime_error("Outer wire not closed");

    BRepBuilderAPI_MakeFace MF(outerwire);
    for (iter++; iter != wires.end(); iter++) {
      const TopoDS_Wire &wire = iter->value();
      if (!iter->is_closed())
        throw std::runtime_error("Outer wire not closed");

      if (wire.Orientation() != outerwire.Orientation()) {
        MF.Add(TopoDS::Wire(wire.Reversed()));
      } else {
        MF.Add(wire);
      }
    }
    f = face{MF.Shape()};

    if (!f.fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to create face");
    }
  }
  return f;
}

face face::make_face(std::vector<edge> &edges,
                     std::vector<vector3<Standard_Real>> points) {
  face f;
  try {
    BRepOffsetAPI_MakeFilling aGenerator;
    for (unsigned i = 0; i < edges.size(); i++) {
      edge *edge = &edges[i];
      aGenerator.Add(edge->value(), GeomAbs_C0);
    }
    for (unsigned i = 0; i < points.size(); i++) {
      gp_Pnt aPnt(points[i].x, points[i].y, points[i].z);
      aGenerator.Add(aPnt);
    }
    aGenerator.Build();
    f = face{aGenerator.Shape()};

    if (!f.fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to create face");
    }
  }
  return f;
}

face face::make_face(std::vector<vector3<Standard_Real>> points) {
  face f;
  try {
    BRepBuilderAPI_MakePolygon MP;
    for (unsigned i = 0; i < points.size(); i++) {
      MP.Add(gp_Pnt(points[i].x, points[i].y, points[i].z));
    }
    MP.Close();
    if (!MP.IsDone()) {
      throw std::runtime_error("failed to create face");
    }
    BRepBuilderAPI_MakeFace MF(MP.Wire(), false);

    f = face{MF.Face()};

    if (!f.fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to create face");
    }
  }
  return f;
}

face face::make_face(std::initializer_list<vector3<Standard_Real>> points) {
  face f;
  try {
    BRepBuilderAPI_MakePolygon MP;
    for (auto _p : points) {
      MP.Add(gp_Pnt(_p.x, _p.y, _p.z));
    }
    MP.Close();
    if (!MP.IsDone()) {
      throw std::runtime_error("failed to create face");
    }
    BRepBuilderAPI_MakeFace MF(MP.Wire(), false);

    f = face{MF.Face()};

    if (!f.fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to create face");
    }
  }
  return f;
}

int face::num_wires() const {
  TopTools_IndexedMapOfShape anIndices;
  TopExp::MapShapes(value(), TopAbs_WIRE, anIndices);
  return anIndices.Extent();
}

int face::num_faces() const {
  TopTools_IndexedMapOfShape anIndices;
  const TopoDS_Shape &shp = value();
  if (shp.ShapeType() == TopAbs_FACE) {
    return 1;
  } else {
    TopExp::MapShapes(shp, TopAbs_FACE, anIndices);
    return anIndices.Extent();
  }
}

double face::area() const {
  GProp_GProps prop;
  BRepGProp::SurfaceProperties(value(), prop);
  return prop.Mass();
}

bbox3d face::inertia() const {
  GProp_GProps prop;
  BRepGProp::SurfaceProperties(value(), prop);
  gp_Mat mat = prop.MatrixOfInertia();
  return bbox3d{{mat(1, 1), mat(2, 2), mat(3, 3)},
                {mat(1, 2), mat(1, 3), mat(2, 3)}};
}

double3 face::centre_of_mass() const {
  double3 ret;
  GProp_GProps prop;
  BRepGProp::SurfaceProperties(value(), prop);
  gp_Pnt cg = prop.CentreOfMass();
  return double3{cg.X(), cg.Y(), cg.Z()};
}

float face::tolerance() const { return BRep_Tool::Tolerance(value()); }

face::operator geom_surface() const {
  Handle(Geom_Surface) aSurface = BRep_Tool::Surface(value());
  return geom_surface{aSurface};
}

int face::offset(double offset, double tolerance) {
  try {
    BRepOffset_MakeOffset MO(value(), offset, tolerance, BRepOffset_Skin,
                             Standard_False, Standard_False,
                             GeomAbs_Intersection, Standard_False);

    if (!MO.IsDone()) {
      throw std::runtime_error("Failed to offset face");
    }

    const TopoDS_Shape &tmp = MO.Shape();
    BRepCheck_Analyzer aChecker(tmp);

    if (tmp.IsNull() || !aChecker.IsValid()) {
      throw std::runtime_error("offset result not valid");
    }

    _shape = tmp;

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
    return 0;
  }
  return 1;
}

int face::extrude(const shape &shp, double3 p1, double3 p2) {
  try {
    const TopoDS_Shape &shp = value();
    TopAbs_ShapeEnum type = shp.ShapeType();
    if (type != TopAbs_EDGE && type != TopAbs_WIRE) {
      throw std::runtime_error("expected Edge or Wire");
    }

    gp_Vec direction(gp_Pnt(p1.x, p1.y, p1.z), gp_Pnt(p2.x, p2.y, p2.z));
    gp_Ax1 axisOfRevolution(gp_Pnt(p1.x, p1.y, p1.z), direction);

    BRepPrimAPI_MakePrism MP(shp, direction, Standard_False);
    _shape = MP.Shape();

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to extrude");
    }
    return 0;
  }
  return 1;
}

int face::revolve(const shape &shp, double3 p1, double3 p2, double angle) {
  try {
    const TopoDS_Shape &shp = value();

    TopAbs_ShapeEnum type = shp.ShapeType();
    if (type != TopAbs_EDGE && type != TopAbs_WIRE) {
      throw std::runtime_error("Expected Edge or Wire");
    }

    gp_Dir direction(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
    gp_Ax1 axisOfRevolution(gp_Pnt(p1.x, p1.y, p1.z), direction);

    BRepPrimAPI_MakeRevol MR(shp, axisOfRevolution, angle, Standard_False);
    if (!MR.IsDone()) {
      throw std::runtime_error("Failed in revolve operation");
      ;
    }
    _shape = MR.Shape();

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to revolve");
    }
    return 0;
  }
  return 1;
}

int face::sweep(const wire &spine, std::vector<shape *> profiles,
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
      PS.Add(*profiles[i]);
    }
    if (!PS.IsReady()) {
      throw std::runtime_error("Failed in sweep operation");
    }
    PS.Build();

    _shape = PS.Shape();

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to sweep");
    }
    return 0;
  }
  return 1;
}

int face::loft(std::vector<shape> profiles, bool ruled, double tolerance) {
  try {
    Standard_Boolean isSolid = Standard_False;
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

    TS.Build();
    if (!TS.IsDone()) {
      throw std::runtime_error("Failed in loft operation");
      ;
    }
    _shape = TS.Shape();

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to loft");
    }
    return 0;
  }
  return 1;
}

int face::boolean(const face &tool, bool_op_type op) {
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

} // namespace topo
} // namespace flywave
