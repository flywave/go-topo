#include "face.hh"
#include "compound.hh"
#include "edge.hh"
#include "geom_utils.hh"
#include "solid.hh"
#include "vertex.hh"
#include "wire.hh"

#include <Adaptor3d_IsoCurve.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <BRepAlgo.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepBuilderAPI_Copy.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepCheck_Analyzer.hxx>
#include <BRepFill.hxx>
#include <BRepFilletAPI_MakeFillet2d.hxx>
#include <BRepGProp.hxx>
#include <BRepGProp_Face.hxx>
#include <BRepLib_FindSurface.hxx>
#include <BRepOffsetAPI_MakeFilling.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepOffset_MakeOffset.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <BRepTools.hxx>
#include <GProp_GProps.hxx>
#include <GeomAPI_PointsToBSplineSurface.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <GeomAdaptor_Surface.hxx>
#include <Geom_BSplineSurface.hxx>
#include <ShapeAnalysis_Surface.hxx>
#include <ShapeFix_Face.hxx>
#include <ShapeFix_Shape.hxx>
#include <TColgp_HArray2OfPnt.hxx>
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

    return face{*this, shp};
  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
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

face face::make_face(const gp_Pln &P) {
  BRepBuilderAPI_MakeFace mf(P);
  return face{mf.Face()};
}

face face::make_face(const gp_Cylinder &C) {
  BRepBuilderAPI_MakeFace mf(C);
  return face{mf.Face()};
}

face face::make_face(const gp_Cone &C) {
  BRepBuilderAPI_MakeFace mf(C);
  return face{mf.Face()};
}

face face::make_face(const gp_Sphere &S) {
  BRepBuilderAPI_MakeFace mf(S);
  return face{mf.Face()};
}

face face::make_face(const gp_Torus &C) {
  BRepBuilderAPI_MakeFace mf(C);
  return face{mf.Face()};
}

face face::make_face(const Handle(Geom_Surface) & S,
                     const Standard_Real TolDegen) {
  BRepBuilderAPI_MakeFace mf(S, TolDegen);
  return face{mf.Face()};
}

face face::make_face(const gp_Pln &P, const Standard_Real UMin,
                     const Standard_Real UMax, const Standard_Real VMin,
                     const Standard_Real VMax) {
  BRepBuilderAPI_MakeFace mf(P, UMin, UMax, VMin, VMax);
  return face{mf.Face()};
}

face face::make_face(const gp_Cylinder &C, const Standard_Real UMin,
                     const Standard_Real UMax, const Standard_Real VMin,
                     const Standard_Real VMax) {
  BRepBuilderAPI_MakeFace mf(C, UMin, UMax, VMin, VMax);
  return face{mf.Face()};
}

face face::make_face(const gp_Cone &C, const Standard_Real UMin,
                     const Standard_Real UMax, const Standard_Real VMin,
                     const Standard_Real VMax) {
  BRepBuilderAPI_MakeFace mf(C, UMin, UMax, VMin, VMax);
  return face{mf.Face()};
}

face face::make_face(const gp_Sphere &S, const Standard_Real UMin,
                     const Standard_Real UMax, const Standard_Real VMin,
                     const Standard_Real VMax) {
  BRepBuilderAPI_MakeFace mf(S, UMin, UMax, VMin, VMax);
  return face{mf.Face()};
}

face face::make_face(const gp_Torus &C, const Standard_Real UMin,
                     const Standard_Real UMax, const Standard_Real VMin,
                     const Standard_Real VMax) {
  BRepBuilderAPI_MakeFace mf(C, UMin, UMax, VMin, VMax);
  return face{mf.Face()};
}

face face::make_face(const Handle(Geom_Surface) & S, const Standard_Real UMin,
                     const Standard_Real UMax, const Standard_Real VMin,
                     const Standard_Real VMax, const Standard_Real TolDegen) {
  BRepBuilderAPI_MakeFace mf(S, UMin, UMax, VMin, VMax, TolDegen);
  return face{mf.Face()};
}

face face::make_face(const wire &W, const bool OnlyPlane) {
  BRepBuilderAPI_MakeFace mf(W.value(), OnlyPlane);
  return face{mf.Face()};
}

face face::make_face(const gp_Pln &P, const wire &W, const bool Inside) {
  BRepBuilderAPI_MakeFace mf(P, W.value(), Inside);
  return face{mf.Face()};
}

face face::make_face(const gp_Cylinder &C, const wire &W, const bool Inside) {
  BRepBuilderAPI_MakeFace mf(C, W.value(), Inside);
  return face{mf.Face()};
}

face face::make_face(const gp_Cone &C, const wire &W, const bool Inside) {
  BRepBuilderAPI_MakeFace mf(C, W.value(), Inside);
  return face{mf.Face()};
}

face face::make_face(const gp_Sphere &S, const wire &W, const bool Inside) {
  BRepBuilderAPI_MakeFace mf(S, W.value(), Inside);
  return face{mf.Face()};
}

face face::make_face(const gp_Torus &C, const wire &W, const bool Inside) {
  BRepBuilderAPI_MakeFace mf(C, W.value(), Inside);
  return face{mf.Face()};
}

face face::make_face(const Handle(Geom_Surface) & S, const wire &W,
                     const bool Inside) {
  BRepBuilderAPI_MakeFace mf(S, W.value(), Inside);
  return face{mf.Face()};
}

face face::make_face(const face &F, const wire &W) {
  BRepBuilderAPI_MakeFace mf(F.value(), W.value());
  return face{mf.Face()};
}

face face::make_face(const face &F, const wire &outer,
                     const std::vector<wire> &inners) {
  BRepBuilderAPI_MakeFace mf(F.value(), outer.value());
  for (unsigned i = 0; i < inners.size(); i++) {
    mf.Add(TopoDS::Wire(inners[i].value()));
  }
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

  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
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

  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to create face");
    }
  }
  return f;
}

face face::make_face(std::vector<edge> &edges, std::vector<gp_Pnt> points) {
  face f;
  try {
    BRepOffsetAPI_MakeFilling aGenerator;
    for (unsigned i = 0; i < edges.size(); i++) {
      edge *edge = &edges[i];
      aGenerator.Add(edge->value(), GeomAbs_C0);
    }
    for (unsigned i = 0; i < points.size(); i++) {
      gp_Pnt aPnt(points[i].X(), points[i].Y(), points[i].Z());
      aGenerator.Add(aPnt);
    }
    aGenerator.Build();
    f = face{aGenerator.Shape()};

    if (!f.fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to create face");
    }
  }
  return f;
}

face face::make_face(std::vector<gp_Pnt> points) {
  face f;
  try {
    BRepBuilderAPI_MakePolygon MP;
    for (unsigned i = 0; i < points.size(); i++) {
      MP.Add(gp_Pnt(points[i].X(), points[i].Y(), points[i].Z()));
    }
    MP.Close();
    if (!MP.IsDone()) {
      throw std::runtime_error("failed to create face");
    }
    BRepBuilderAPI_MakeFace MF(MP.Wire(), false);

    switch (MF.Error()) {
    case BRepBuilderAPI_FaceDone:
      f = face{MF.Face()};
      break;
    default:
      throw std::runtime_error(
          "Error. Undefined status. Please check the code.\n");
      break;
    }

  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to create face");
    }
  }
  return f;
}

face face::make_face(std::initializer_list<gp_Pnt> points) {
  face f;
  try {
    BRepBuilderAPI_MakePolygon MP;
    for (auto _p : points) {
      MP.Add(gp_Pnt(_p.X(), _p.Y(), _p.Z()));
    }
    MP.Close();
    if (!MP.IsDone()) {
      throw std::runtime_error("failed to create face");
    }
    BRepBuilderAPI_MakeFace MF(MP.Wire(), false);

    f = face{MF.Face()};

    if (!f.fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to create face");
    }
  }
  return f;
}

face face::make_face(
    const std::vector<boost::variant<wire, edge>> &edges,
    const std::vector<boost::variant<wire, edge, gp_Pnt>> &constraints,
    GeomAbs_Shape continuity, int degree, int nbPtsOnCur, int nbIter,
    bool anisotropy, double tol2d, double tol3d, double tolAng, double tolCurv,
    int maxDeg, int maxSegments) {
  // Validate parameters
  if (degree < 2)
    throw std::invalid_argument("Degree must be >= 2");
  if (nbPtsOnCur < 15)
    throw std::invalid_argument("nbPtsOnCur must be >= 15");
  if (nbIter < 2)
    throw std::invalid_argument("nbIter must be >= 2");
  if (tol2d <= 0)
    throw std::invalid_argument("tol2d must be > 0");
  if (tol3d <= 0)
    throw std::invalid_argument("tol3d must be > 0");
  if (tolCurv <= 0)
    throw std::invalid_argument("tolCurv must be > 0");
  if (maxDeg < 2)
    throw std::invalid_argument("maxDeg must be >= 2");
  if (maxSegments < 2)
    throw std::invalid_argument("maxSegments must be >= 2");

  // Create the filling surface builder
  BRepOffsetAPI_MakeFilling n_sided(degree, nbPtsOnCur, nbIter, anisotropy,
                                    tol2d, tol3d, tolAng, tolCurv, maxDeg,
                                    maxSegments);

  // Visitor for edges
  struct EdgeVisitor : public boost::static_visitor<> {
    BRepOffsetAPI_MakeFilling &builder;
    GeomAbs_Shape cont;

    EdgeVisitor(BRepOffsetAPI_MakeFilling &b, GeomAbs_Shape c)
        : builder(b), cont(c) {}

    void operator()(const edge &e) const { builder.Add(e.value(), cont); }

    void operator()(const wire &w) const {
      for (const edge &e : w.edges()) {
        builder.Add(e.value(), cont);
      }
    }
  };

  // Add outer edges
  EdgeVisitor edgeVisitor(n_sided, continuity);
  for (const auto &el : edges) {
    boost::apply_visitor(edgeVisitor, el);
  }

  // Visitor for constraints
  struct ConstraintVisitor : public boost::static_visitor<> {
    BRepOffsetAPI_MakeFilling &builder;

    ConstraintVisitor(BRepOffsetAPI_MakeFilling &b) : builder(b) {}

    void operator()(const gp_Pnt &p) const { builder.Add(p); }

    void operator()(const edge &e) const {
      builder.Add(e.value(), GeomAbs_C0, false);
    }

    void operator()(const wire &w) const {
      for (const edge &e : w.edges()) {
        builder.Add(e.value(), GeomAbs_C0, false);
      }
    }
  };

  // Add constraints
  ConstraintVisitor constraintVisitor(n_sided);
  for (const auto &c : constraints) {
    boost::apply_visitor(constraintVisitor, c);
  }

  // Build the surface
  n_sided.Build();
  if (!n_sided.IsDone()) {
    throw std::runtime_error("Failed to create n-sided surface");
  }

  auto ret = face(n_sided.Shape());
  ret.fix_shape();
  return ret;
}
face face::make_plane(const gp_Pnt &basePnt, const gp_Dir &dir,
                      boost::optional<double> length,
                      boost::optional<double> width) {
  gp_Pln pln(basePnt, dir);

  if (length && width) {
    double halfWidth = *width * 0.5;
    double halfLength = *length * 0.5;
    return face(BRepBuilderAPI_MakeFace(pln, -halfWidth, halfWidth, -halfLength,
                                        halfLength)
                    .Face());
  } else {
    return face(BRepBuilderAPI_MakeFace(pln).Face());
  }
}

face face::make_face(const edge &edge1, const edge &edge2) {
  return face(BRepFill::Face(edge1.value(), edge2.value()));
}

face face::make_face(const wire &wire1, const wire &wire2) {
  return face(BRepFill::Shell(wire1.value(), wire2.value()));
}

face face::make_face(const wire &outerWire,
                     const std::vector<wire> &innerWires) {
  // Validate outer wire
  if (!innerWires.empty() && !outerWire.is_closed()) {
    throw std::invalid_argument(
        "Cannot build face(s): outer wire is not closed");
  }

  // Check if wires are coplanar
  std::vector<shape> allWires = {outerWire};
  allWires.insert(allWires.end(), innerWires.begin(), innerWires.end());
  compound ws = compound::make_compound(allWires);

  if (!BRepLib_FindSurface(ws.value(), true).Found()) {
    throw std::invalid_argument("Cannot build face(s): wires not planar");
  }

  // Fix outer wire
  ShapeFix_Shape sf_s(outerWire.value());
  sf_s.Perform();
  TopoDS_Wire wo = TopoDS::Wire(sf_s.Shape());

  // Build face
  BRepBuilderAPI_MakeFace faceBuilder(wo, true);

  // Add inner wires
  for (const wire &w : innerWires) {
    if (!w.is_closed()) {
      throw std::invalid_argument(
          "Cannot build face(s): inner wire is not closed");
    }
    faceBuilder.Add(w.value());
  }

  faceBuilder.Build();

  if (!faceBuilder.IsDone()) {
    throw std::runtime_error("Cannot build face(s): " +
                             std::to_string(faceBuilder.Error()));
  }

  // Fix face orientation
  ShapeFix_Face sf_f(faceBuilder.Face());
  sf_f.FixOrientation();
  sf_f.Perform();

  return face(sf_f.Result());
}

face face::make_spline_approx(
    const std::vector<std::vector<gp_Pnt>> &points, double tol,
    const std::tuple<double, double, double> *smoothing, int minDeg,
    int maxDeg) {
  if (points.empty() || points[0].empty()) {
    throw std::invalid_argument("Point array cannot be empty");
  }

  TColgp_Array2OfPnt pointsArray =
      TColgp_Array2OfPnt(1, static_cast<int>(points.size()), 1, static_cast<int>(points[0].size()));

  for (size_t i = 0; i < points.size(); ++i) {
    for (size_t j = 0; j < points[i].size(); ++j) {
      pointsArray.SetValue(i + 1, j + 1, points[i][j]);
    }
  }

  Handle(Geom_BSplineSurface) spline;
  if (smoothing) {
    double w1, w2, w3;
    std::tie(w1, w2, w3) = *smoothing;
    GeomAPI_PointsToBSplineSurface splineBuilder(pointsArray, w1, w2, w3,
                                                 maxDeg, GeomAbs_C2, tol);
    spline = splineBuilder.Surface();
  } else {
    GeomAPI_PointsToBSplineSurface splineBuilder(pointsArray, minDeg, maxDeg,
                                                 GeomAbs_C2, tol);
    spline = splineBuilder.Surface();
  }

  if (spline.IsNull()) {
    throw std::runtime_error("B-spline approximation failed");
  }

  auto surface = Handle(Geom_Surface)::DownCast(spline);

  BRepBuilderAPI_MakeFace faceBuilder(surface, Precision::Confusion());
  if (!faceBuilder.IsDone()) {
    throw std::runtime_error("Failed to create face from spline");
  }

  return face(faceBuilder.Face());
}

double face::area() const {
  GProp_GProps prop;
  BRepGProp::SurfaceProperties(value(), prop);
  return prop.Mass();
}

Bnd_Box face::inertia() const {
  GProp_GProps prop;
  BRepGProp::SurfaceProperties(value(), prop);
  gp_Mat mat = prop.MatrixOfInertia();
  Bnd_Box bbox;
  bbox.Update(mat(1, 1), mat(2, 2), mat(3, 3), mat(1, 2), mat(1, 3), mat(2, 3));
  return bbox;
}

gp_Pnt face::centre_of_mass() const {
  gp_Pnt ret;
  GProp_GProps prop;
  BRepGProp::SurfaceProperties(value(), prop);
  gp_Pnt cg = prop.CentreOfMass();
  return gp_Pnt{cg.X(), cg.Y(), cg.Z()};
}

float face::tolerance() const { return BRep_Tool::Tolerance(value()); }

face::operator Handle(Geom_Surface)() const {
  Handle(Geom_Surface) aSurface = BRep_Tool::Surface(value());
  return Handle(Geom_Surface){aSurface};
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

  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
    return 0;
  }
  return 1;
}

int face::extrude(const shape &shp, gp_Pnt p1, gp_Pnt p2) {
  try {
    const TopoDS_Shape &shp = value();
    TopAbs_ShapeEnum type = shp.ShapeType();
    if (type != TopAbs_EDGE && type != TopAbs_WIRE) {
      throw std::runtime_error("expected Edge or Wire");
    }

    gp_Vec direction(gp_Pnt(p1.X(), p1.Y(), p1.Z()),
                     gp_Pnt(p2.X(), p2.Y(), p2.Z()));
    gp_Ax1 axisOfRevolution(gp_Pnt(p1.X(), p1.Y(), p1.Z()), direction);

    BRepPrimAPI_MakePrism MP(shp, direction, Standard_False);
    _shape = MP.Shape();

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to extrude");
    }
    return 0;
  }
  return 1;
}

int face::revolve(const shape &shp, gp_Pnt p1, gp_Pnt p2, double angle) {
  try {
    const TopoDS_Shape &shp = value();

    TopAbs_ShapeEnum type = shp.ShapeType();
    if (type != TopAbs_EDGE && type != TopAbs_WIRE) {
      throw std::runtime_error("Expected Edge or Wire");
    }

    gp_Dir direction(p2.X() - p1.X(), p2.Y() - p1.Y(), p2.Z() - p1.Z());
    gp_Ax1 axisOfRevolution(gp_Pnt(p1.X(), p1.Y(), p1.Z()), direction);

    BRepPrimAPI_MakeRevol MR(shp, axisOfRevolution, angle, Standard_False);
    if (!MR.IsDone()) {
      throw std::runtime_error("Failed in revolve operation");
      ;
    }
    _shape = MR.Shape();

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to revolve");
    }
    return 0;
  }
  return 1;
}

int face::sweep(const wire &spine, std::vector<shape> profiles,
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
      PS.Add(profiles[i]);
    }
    if (!PS.IsReady()) {
      throw std::runtime_error("Failed in sweep operation");
    }
    PS.Build();

    _shape = PS.Shape();

    if (!this->fix_shape())
      throw std::runtime_error("Shapes not valid");

  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
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

  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
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

  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed in boolean operation");
    }
    return 0;
  }
  return 1;
}

Handle_Geom_Surface face::get_geom() const {
  return BRep_Tool::Surface(value());
}

face face::fillet2d(double radius, const std::vector<vertex> &vertices) const {
  BRepFilletAPI_MakeFillet2d filletBuilder(this->value());

  for (const vertex &v : vertices) {
    filletBuilder.AddFillet(v.value(), radius);
  }

  filletBuilder.Build();
  if (!filletBuilder.IsDone()) {
    throw std::runtime_error("Failed to create 2D fillets");
  }

  return face(filletBuilder.Shape());
}

face face::chamfer2d(double distances,
                     const std::vector<vertex> &vertices) const {
  BRepFilletAPI_MakeFillet2d chamferBuilder(this->value());
  auto edgeMap = this->get_entities_from(TopAbs_VERTEX, TopAbs_EDGE);

  for (const vertex &v : vertices) {
    auto edges = edgeMap[v];
    if (edges.size() < 2) {
      throw std::invalid_argument("Cannot chamfer at this location");
    }

    chamferBuilder.AddChamfer(TopoDS::Edge(edges[0].value()),
                              TopoDS::Edge(edges[1].value()), distances,
                              distances);
  }

  chamferBuilder.Build();
  if (!chamferBuilder.IsDone()) {
    throw std::runtime_error("Failed to create 2D chamfers");
  }

  auto f = face(chamferBuilder.Shape());
  f.fix_shape();

  return f;
}

wire face::outer_wire() const {
  return wire(BRepTools::OuterWire(this->value()));
}

std::vector<wire> face::inner_wires() const {
  wire outer = this->outer_wire();
  std::vector<wire> innerWires;

  for (const wire &wire : this->wires()) {
    if (!wire.is_same(outer)) {
      innerWires.push_back(wire);
    }
  }

  return innerWires;
}

std::tuple<double, double, double, double> face::uv_bounds() const {
  double umin, umax, vmin, vmax;
  BRepTools::UVBounds(this->value(), umin, umax, vmin, vmax);
  return std::make_tuple(umin, umax, vmin, vmax);
}

std::pair<double, double> face::param_at(const gp_Pnt &pt) const {
  Handle(Geom_Surface) surface = this->get_geom();
  GeomAPI_ProjectPointOnSurf projector(pt, surface);

  double u, v;
  projector.LowerDistanceParameters(u, v);

  return std::make_pair(u, v);
}

std::pair<std::vector<double>, std::vector<double>>
face::params(const std::vector<gp_Pnt> &pts, double tol) const {
  std::vector<double> us;
  std::vector<double> vs;
  us.reserve(pts.size());
  vs.reserve(pts.size());

  Handle(Geom_Surface) surface = this->get_geom();
  ShapeAnalysis_Surface projector(surface);

  if (pts.empty()) {
    return std::make_pair(us, vs);
  }

  gp_Pnt2d uv = projector.ValueOfUV(pts[0], tol);
  us.push_back(uv.X());
  vs.push_back(uv.Y());

  for (size_t i = 1; i < pts.size(); i++) {
    uv = projector.NextValueOfUV(uv, pts[i], tol);
    us.push_back(uv.X());
    vs.push_back(uv.Y());
  }

  return std::make_pair(us, vs);
}

gp_Pnt face::position_at(double u, double v) const {
  gp_Pnt p;
  gp_Vec vn;
  BRepGProp_Face(this->value()).Normal(u, v, p, vn);
  return p;
}

std::vector<gp_Pnt>
face::positions(const std::vector<std::pair<double, double>> &uvs) const {
  std::vector<gp_Pnt> results;
  results.reserve(uvs.size());

  gp_Pnt p;
  gp_Vec vn;
  BRepGProp_Face faceProp(this->value());

  for (const auto &uv : uvs) {
    faceProp.Normal(uv.first, uv.second, p, vn);
    results.push_back(p);
  }

  return results;
}

gp_Vec face::normal_at(const gp_Pnt *locationVector) const {
  Handle(Geom_Surface) surface = this->get_geom();
  double u, v;

  if (locationVector == nullptr) {
    double u0, u1, v0, v1;
    std::tie(u0, u1, v0, v1) = this->uv_bounds();
    u = 0.5 * (u0 + u1);
    v = 0.5 * (v0 + v1);
  } else {
    GeomAPI_ProjectPointOnSurf projector(*locationVector, surface);
    projector.LowerDistanceParameters(u, v);
  }

  gp_Pnt p;
  gp_Vec vn;
  BRepGProp_Face(this->value()).Normal(u, v, p, vn);
  return vn.Normalized();
}

std::pair<gp_Vec, gp_Pnt> face::normal_at(double u, double v) const {
  gp_Pnt p;
  gp_Vec vn;
  BRepGProp_Face(this->value()).Normal(u, v, p, vn);
  return std::make_pair(vn.Normalized(), p);
}

std::pair<std::vector<gp_Vec>, std::vector<gp_Pnt>>
face::normals(const std::vector<double> &us,
              const std::vector<double> &vs) const {
  if (us.size() != vs.size()) {
    throw std::invalid_argument("UV parameter lists must have equal length");
  }

  std::vector<gp_Vec> normals;
  std::vector<gp_Pnt> positions;
  normals.reserve(us.size());
  positions.reserve(us.size());

  BRepGProp_Face faceProp(this->value());
  gp_Pnt p;
  gp_Vec vn;

  for (size_t i = 0; i < us.size(); i++) {
    faceProp.Normal(us[i], vs[i], p, vn);
    normals.push_back(vn.Normalized());
    positions.push_back(p);
  }

  return std::make_pair(normals, positions);
}

gp_Pnt face::center() const {
  GProp_GProps props;
  BRepGProp::SurfaceProperties(this->value(), props);
  return props.CentreOfMass();
}

gp_Pln face::to_plane() const {
  BRepAdaptor_Surface adaptor(this->value());

  if (adaptor.GetType() != GeomAbs_Plane) {
    throw std::runtime_error("Face is not planar - cannot convert to gp_Pln");
  }

  return adaptor.Plane();
}

solid face::thicken(double thickness) const {
  BRepOffset_MakeOffset builder;

  // Initialize the offset builder with parameters
  builder.Initialize(this->value(),        // Input shape
                     thickness,            // Offset distance
                     1.0e-6,               // Tolerance
                     BRepOffset_Skin,      // Offset mode (skin)
                     false,                // Intersection flag
                     false,                // Self-interference flag
                     GeomAbs_Intersection, // Join type
                     true                  // Make solid flag (important!)
  );

  builder.MakeOffsetShape();

  if (!builder.IsDone()) {
    throw std::runtime_error("Failed to thicken face");
  }

  return solid(builder.Shape());
}

struct WireExtractor : public boost::static_visitor<wire> {
  wire operator()(const wire &w) const { return w; }
  template <typename T> wire operator()(const T &) const {
    throw std::runtime_error("Projection did not produce a wire");
  }
};

face face::project(const face &other, const gp_Vec &direction) const {
  WireExtractor extractor;

  // 处理外轮廓线
  wire outerP = boost::apply_visitor(
      extractor, this->outer_wire().projected(other, direction));

  // 处理内轮廓线
  std::vector<wire> innerP;
  for (const wire &w : this->inner_wires()) {
    innerP.push_back(
        boost::apply_visitor(extractor, w.projected(other, direction)));
  }

  return face::make_face(other, outerP, innerP);
}

face face::to_arcs(double tolerance) const {
  if (tolerance <= 0) {
    throw std::invalid_argument("Tolerance must be positive");
  }
  return face(BRepAlgo::ConvertFace(this->value(), tolerance));
}

face face::trim(double u0, double u1, double v0, double v1, double tol) const {
  Handle(Geom_Surface) surface = this->get_geom();
  BRepBuilderAPI_MakeFace faceBuilder(surface, u0, u1, v0, v1, tol);

  if (!faceBuilder.IsDone()) {
    throw std::runtime_error("Failed to trim face");
  }

  return face(faceBuilder.Shape());
}

edge face::isoline(double param, const std::string &direction) const {
  double u1, u2, v1, v2;
  std::tie(u1, u2, v1, v2) = this->uv_bounds();

  GeomAbs_IsoType isoType;
  double p1, p2;

  if (direction == "u") {
    isoType = GeomAbs_IsoU;
    p1 = v1;
    p2 = v2;
  } else if (direction == "v") {
    isoType = GeomAbs_IsoV;
    p1 = u1;
    p2 = u2;
  } else {
    throw std::invalid_argument("Direction must be 'u' or 'v'");
  }

  Handle(Geom_Surface) surface = this->get_geom();
  Handle(Adaptor3d_Surface) hanle = new GeomAdaptor_Surface(surface);
  Adaptor3d_IsoCurve adaptor(hanle, isoType, param);

  return edge(geom_utils::adaptor_curve_to_edge(adaptor, p1, p2));
}

std::vector<edge> face::isolines(const std::vector<double> &params,
                                 const std::string &direction) const {
  std::vector<edge> result;
  result.reserve(params.size());

  for (double p : params) {
    result.push_back(this->isoline(p, direction));
  }

  return result;
}

std::vector<face> face::make_from_wires(const wire &outer,
                                        const std::vector<wire> &inners) {
  BRepBuilderAPI_MakeFace faceBuilder;

  faceBuilder.Add(TopoDS::Wire(outer.value()));

  for (const wire &w : inners) {
    faceBuilder.Add(TopoDS::Wire(w.value()));
  }

  TopoDS_Shape result = faceBuilder.Shape();
  if (result.ShapeType() == TopAbs_COMPOUND) {
    std::vector<face> faces;
    TopExp_Explorer exp(result, TopAbs_FACE);
    for (; exp.More(); exp.Next()) {
      faces.emplace_back(TopoDS::Face(exp.Current()));
    }
    return faces;
  } else {
    return {face(TopoDS::Face(result))};
  }
}

} // namespace topo
} // namespace flywave
