#include "shape.hh"
#include "point3d_with_tolerance.hh"

#include "comp_solid.hh"
#include "compound.hh"
#include "edge.hh"
#include "face.hh"
#include "matrix.hh"
#include "shell.hh"
#include "solid.hh"
#include "vertex.hh"
#include "wire.hh"

#include <BRepAdaptor_Curve.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Splitter.hxx>
#include <BRepBndLib.hxx>
#include <BRepBuilderAPI_Copy.hxx>
#include <BRepBuilderAPI_FindPlane.hxx>
#include <BRepBuilderAPI_GTransform.hxx>
#include <BRepBuilderAPI_NurbsConvert.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepCheck_Analyzer.hxx>
#include <BRepExtrema_DistShapeShape.hxx>
#include <BRepGProp.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <BRepTools.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <BRep_Tool.hxx>
#include <Bnd_Box.hxx>
#include <GCPnts_TangentialDeflection.hxx>
#include <GProp_GProps.hxx>
#include <GeomAbs_CurveType.hxx>
#include <GeomAbs_SurfaceType.hxx>
#include <Geom_Line.hxx>
#include <Geom_Plane.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Interface_Static.hxx>
#include <Poly.hxx>
#include <Poly_Triangulation.hxx>
#include <STEPControl_Writer.hxx>
#include <ShapeCustom.hxx>
#include <ShapeCustom_BSplineRestriction.hxx>
#include <ShapeCustom_RestrictionParameters.hxx>
#include <ShapeFix_Shape.hxx>
#include <ShapeFix_ShapeTolerance.hxx>
#include <ShapeUpgrade_UnifySameDomain.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <TShort_Array1OfShortReal.hxx>
#include <TopAbs.hxx>
#include <TopExp.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopoDS.hxx>
#include <gp_Quaternion.hxx>

#include <limits>
#include <unordered_map>
#include <unordered_set>

namespace flywave {
namespace topo {

namespace {
std::pair<double, std::pair<gp_Pnt, gp_Pnt>>
distance_with_points(const TopoDS_Shape &shape1, const TopoDS_Shape &shape2) {
  if (shape1.IsNull() || shape2.IsNull()) {
    throw std::invalid_argument("Cannot compute distance for null shapes");
  }

  BRepExtrema_DistShapeShape distTool(shape1, shape2);

  if (!distTool.IsDone() || distTool.NbSolution() == 0) {
    throw std::runtime_error("Distance computation failed");
  }

  return {distTool.Value(),
          {distTool.PointOnShape1(1), distTool.PointOnShape2(1)}};
}

void compute_properties(const TopoDS_Shape &shape, GProp_GProps &props) {
  switch (shape.ShapeType()) {
  case TopAbs_SOLID:
  case TopAbs_COMPSOLID:
    BRepGProp::VolumeProperties(shape, props);
    break;
  case TopAbs_FACE:
  case TopAbs_SHELL:
    BRepGProp::SurfaceProperties(shape, props);
    break;
  case TopAbs_EDGE:
  case TopAbs_WIRE:
    BRepGProp::LinearProperties(shape, props);
    break;
  default:
    throw std::runtime_error("Unsupported shape type for mass calculation");
  }
}

const shape_geom_type &get_geom_type(const TopoDS_Shape &shape) {
  static const std::unordered_map<TopAbs_ShapeEnum, shape_geom_type> geomLUT = {
      {TopAbs_VERTEX, shape_geom_vertex},
      {TopAbs_WIRE, shape_geom_wire},
      {TopAbs_SHELL, shape_geom_shell},
      {TopAbs_SOLID, shape_geom_solid},
      {TopAbs_COMPSOLID, shape_geom_compsolid},
      {TopAbs_COMPOUND, shape_geom_compound}};

  static const std::unordered_map<GeomAbs_CurveType, shape_geom_type>
      edgeGeomLUT = {{GeomAbs_Line, shape_geom_line},
                     {GeomAbs_Circle, shape_geom_circle},
                     {GeomAbs_Ellipse, shape_geom_ellipse},
                     {GeomAbs_Hyperbola, shape_geom_hyperbola},
                     {GeomAbs_Parabola, shape_geom_parabola},
                     {GeomAbs_BezierCurve, shape_geom_bezier_curve},
                     {GeomAbs_BSplineCurve, shape_geom_bspline_curve},
                     {GeomAbs_OffsetCurve, shape_geom_offset_curve},
                     {GeomAbs_OtherCurve, shape_geom_other_curve}};

  static const std::unordered_map<GeomAbs_SurfaceType, shape_geom_type>
      faceGeomLUT = {{GeomAbs_Plane, shape_geom_plane},
                     {GeomAbs_Cylinder, shape_geom_cylinder},
                     {GeomAbs_Cone, shape_geom_cone},
                     {GeomAbs_Sphere, shape_geom_sphere},
                     {GeomAbs_Torus, shape_geom_torus},
                     {GeomAbs_BezierSurface, shape_geom_bezier_surface},
                     {GeomAbs_BSplineSurface, shape_geom_bspline_surface},
                     {GeomAbs_SurfaceOfRevolution, shape_geom_revolved_surface},
                     {GeomAbs_SurfaceOfExtrusion, shape_geom_extruded_surface},
                     {GeomAbs_OffsetSurface, shape_geom_offset_surface},
                     {GeomAbs_OtherSurface, shape_geom_other_surface}};

  TopAbs_ShapeEnum shapeType = shape.ShapeType();

  auto it = geomLUT.find(shapeType);
  if (it != geomLUT.end()) {
    return it->second;
  }

  if (shapeType == TopAbs_EDGE) {
    BRepAdaptor_Curve curve(TopoDS::Edge(shape));
    auto curveType = curve.GetType();
    return edgeGeomLUT.at(curveType);
  }

  if (shapeType == TopAbs_FACE) {
    BRepAdaptor_Surface surface(TopoDS::Face(shape));
    auto surfaceType = surface.GetType();
    return faceGeomLUT.at(surfaceType);
  }

  throw std::runtime_error("Unknown shape type");
}
} // namespace

struct TopoDS_ShapeHasher {
  std::size_t operator()(const TopoDS_Shape &shape) const {
    if (shape.IsNull()) {
      return 0;
    }
    return std::hash<const void *>{}(shape.TShape().get());
  }
};

shape::shape()
    : _shape(), _surface_colour(Quantity_NOC_WHITE),
      _curve_colour(Quantity_NOC_WHITE), _u_origin(0.), _v_origin(0.),
      _u_repeat(1.), _v_repeat(1.), _scale_u(1.), _scale_v(1.),
      _auto_scale_size_on_u(1.), _auto_scale_size_on_v(1.),
      _txture_map_type(texture_normal), _rotation_angle(0.),
      _for_construction(false) {}

shape::shape(TopoDS_Shape shp, bool forConstruction)
    : _shape(shp), _surface_colour(Quantity_NOC_WHITE),
      _curve_colour(Quantity_NOC_WHITE), _u_origin(0.), _v_origin(0.),
      _u_repeat(1.), _v_repeat(1.), _scale_u(1.), _scale_v(1.),
      _auto_scale_size_on_u(1.), _auto_scale_size_on_v(1.),
      _txture_map_type(texture_normal), _rotation_angle(0.),
      _for_construction(forConstruction) {}

shape::shape(const shape &s, TopoDS_Shape shp)
    : _shape(shp), _surface_colour(s._surface_colour),
      _curve_colour(s._curve_colour), _u_origin(s._u_origin),
      _v_origin(s._v_origin), _u_repeat(s._u_repeat), _v_repeat(s._v_repeat),
      _scale_u(s._scale_u), _scale_v(s._scale_v),
      _auto_scale_size_on_u(s._auto_scale_size_on_u),
      _auto_scale_size_on_v(s._auto_scale_size_on_v),
      _txture_map_type(s._txture_map_type), _rotation_angle(s._rotation_angle),
      _for_construction(s._for_construction) {}

TopoDS_Shape &shape::value() { return _shape; }

const TopoDS_Shape &shape::value() const { return _shape; }

shape::operator TopoDS_Shape &() { return _shape; }

shape::operator const TopoDS_Shape &() const { return _shape; }

shape::shape(shape &&o) noexcept
    : _shape(o._shape), _surface_colour(o._surface_colour),
      _curve_colour(o._curve_colour), _u_origin(o._u_origin),
      _v_origin(o._v_origin), _u_repeat(o._u_repeat), _v_repeat(o._v_repeat),
      _scale_u(o._scale_u), _scale_v(o._scale_v),
      _auto_scale_size_on_u(o._auto_scale_size_on_u),
      _auto_scale_size_on_v(o._auto_scale_size_on_v),
      _txture_map_type(o._txture_map_type), _rotation_angle(o._rotation_angle),
      _for_construction(o._for_construction) {
  if (!o._shape.IsNull())
    o._shape.Free();
}

shape &shape::operator=(shape &&o) noexcept {
  _shape = o._shape;
  _surface_colour = o._surface_colour;
  _curve_colour = o._curve_colour;
  _u_origin = o._u_origin;
  _v_origin = o._v_origin;
  _u_repeat = o._u_repeat;
  _v_repeat = o._v_repeat;
  _scale_u = o._scale_u;
  _scale_v = o._scale_v;
  _auto_scale_size_on_u = o._auto_scale_size_on_u;
  _auto_scale_size_on_v = o._auto_scale_size_on_v;
  _txture_map_type = o._txture_map_type;
  _rotation_angle = o._rotation_angle;
  _for_construction = o._for_construction;
  if (!o._shape.IsNull())
    o._shape.Free();
  return *this;
}

shape shape::copy(bool deep) const {
  try {
    BRepBuilderAPI_Copy _copy(_shape, deep);
    _copy.Build();

    if (!_copy.IsDone()) {
      _copy.Shape().Free();
      throw std::runtime_error("Section operation failed");
    }

    auto shp = _copy.Shape();

    if (shp.IsNull())
      throw std::runtime_error("Shell operation resulted in Null shape");

    switch (shp.ShapeType()) {
    case TopAbs_VERTEX:
      return vertex(*this, shp);
    case TopAbs_EDGE:
      return edge(*this, shp);
    case TopAbs_WIRE:
      return wire(*this, shp);
    case TopAbs_FACE:
      return face(*this, shp);
    case TopAbs_SHELL:
      return shell(*this, shp);
    case TopAbs_SOLID:
      return solid(*this, shp);
    default:
      break;
    }
    return shape{};
  } catch (...) {
    throw;
  }
  return shape{};
}

bool shape::is_null() const { return _shape.IsNull(); }

bool shape::is_valid() const {
  if (_shape.IsNull())
    return false;
  BRepCheck_Analyzer aChecker(_shape);
  return aChecker.IsValid() ? true : false;
}

shape::operator bool() const { return !is_null(); }

geometry_object_type shape::type() const {
  switch (_shape.ShapeType()) {
  case TopAbs_COMPOUND:
    return geometry_object_type::CompoundType;
  case TopAbs_COMPSOLID:
    return geometry_object_type::CompSolidType;
  case TopAbs_SOLID:
    return geometry_object_type::SolidType;
  case TopAbs_SHELL:
    return geometry_object_type::ShellType;
  case TopAbs_FACE:
    return geometry_object_type::FaceType;
  case TopAbs_WIRE:
    return geometry_object_type::WireType;
  case TopAbs_EDGE:
    return geometry_object_type::EdgeType;
  case TopAbs_VERTEX:
    return geometry_object_type::VertexType;
  case TopAbs_SHAPE:
    return geometry_object_type::ShapeType;
  default:
    break;
  }
  return geometry_object_type::ShapeType;
}

Bnd_Box shape::bounding_box(double tolerance) const {
  try {
    const TopoDS_Shape &shape = _shape;
    Bnd_Box aBox;
    BRepBndLib::Add(shape, aBox);
    aBox.SetGap(tolerance);
    return aBox;
  } catch (Standard_Failure &e) {
    Bnd_Box aBox;
    aBox.Update(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    return aBox;
  }
}

topo_bbox shape::bbox(double tolerance) const {
  return topo_bbox(bounding_box(tolerance));
}

int shape::hash_code() const {
  return _shape.HashCode(std::numeric_limits<int>::max());
}

bool shape::equals(const geometry_object &other) const {
  if (dynamic_cast<const shape *>(&other)) {
    if (this->_shape.IsEqual(dynamic_cast<const shape *>(&other)->_shape))
      return true;
  }
  return false;
}

int shape::transform(gp_Trsf mat) { return transform_impl(mat); }

int shape::transform(const topo_matrix &mat) {
  try {
    TopoDS_Shape &shape = _shape;
    BRepBuilderAPI_Transform transformer(shape, mat.get_value().Trsf(),
                                         true // Make copy of the shape
    );

    transformer.Build();
    if (!transformer.IsDone())
      return 0;
    _shape = transformer.Shape();
    return 1;
  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to transform object");
    }
    return 0;
  }
  return 1;
}

int shape::transform_impl(gp_Trsf &trans) {
  try {
    TopoDS_Shape &shape = _shape;

    if (shape.IsNull())
      throw std::runtime_error("Null shape");
    BRepBuilderAPI_Transform aTrans(trans);
    aTrans.Perform(shape);
    if (!aTrans.IsDone())
      return 0;
    _shape = aTrans.Shape();
  } catch (Standard_Failure &e) {

    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to transform object");
    }
    return 0;
  }
  return 1;
}

int shape::translate(gp_Vec delta) {
  try {
    TopoDS_Shape &shape = _shape;

    if (shape.IsNull())
      throw std::runtime_error("Null shape");

    gp_Trsf trans;
    trans.SetTranslation(gp_Pnt(0, 0, 0),
                         gp_Pnt(delta.X(), delta.Y(), delta.Z()));
    BRepBuilderAPI_Transform aTrans(trans);
    aTrans.Perform(shape);
    if (!aTrans.IsDone())
      return 0;
    _shape = aTrans.Shape();
  } catch (Standard_Failure &e) {

    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to translate object");
    }
    return 0;
  }
  return 1;
}

bool shape::is_same(const shape &o) const { return _shape.IsSame(o._shape); }

bool shape::for_construction() const { return false; }

int shape::rotate(double angle, gp_Pnt p1, gp_Pnt p2) {
  try {
    TopoDS_Shape &shape = _shape;

    if (shape.IsNull())
      throw std::runtime_error("Null shape");

    gp_Trsf trans;
    gp_Vec dir(gp_Pnt(p1.X(), p1.Y(), p1.Z()), gp_Pnt(p2.X(), p2.Y(), p2.Z()));
    gp_Ax1 axis(gp_Pnt(p1.X(), p1.Y(), p1.Z()), dir);
    trans.SetRotation(axis, angle);
    BRepBuilderAPI_Transform aTrans(trans);
    aTrans.Perform(shape);
    if (!aTrans.IsDone())
      return 0;
    _shape = aTrans.Shape();
  } catch (Standard_Failure &e) {

    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to rotate object");
    }
    return 0;
  }
  return 1;
}

int shape::rotate(double angle, gp_Ax1 a) {
  try {
    TopoDS_Shape &shape = _shape;

    if (shape.IsNull())
      throw std::runtime_error("Null shape");

    gp_Trsf trans;
    trans.SetRotation(a, angle);
    BRepBuilderAPI_Transform aTrans(trans);
    aTrans.Perform(shape);
    if (!aTrans.IsDone())
      return 0;
    _shape = aTrans.Shape();
  } catch (Standard_Failure &e) {

    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to rotate object");
    }
    return 0;
  }
  return 1;
}

int shape::rotate(gp_Quaternion R) {
  try {
    TopoDS_Shape &shape = _shape;

    if (shape.IsNull())
      throw std::runtime_error("Null shape");

    gp_Trsf trans;
    trans.SetRotation(R);
    BRepBuilderAPI_Transform aTrans(trans);
    aTrans.Perform(shape);
    if (!aTrans.IsDone())
      return 0;
    _shape = aTrans.Shape();
  } catch (Standard_Failure &e) {

    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to rotate object");
    }
    return 0;
  }
  return 1;
}

int shape::scale(gp_Pnt pnt, double scale) {
  try {
    TopoDS_Shape &shape = _shape;

    if (shape.IsNull())
      throw std::runtime_error("Null shape");

    gp_Trsf trans;
    trans.SetScale(gp_Pnt(pnt.X(), pnt.Y(), pnt.Z()), scale);
    BRepBuilderAPI_Transform aTrans(trans);
    aTrans.Perform(shape);
    if (!aTrans.IsDone())
      return 0;
    _shape = aTrans.Shape();
  } catch (Standard_Failure &e) {

    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to scale object");
    }
    return 0;
  }
  return 1;
}

int shape::mirror(gp_Pnt pnt, gp_Vec nor) {
  return mirror(pnt, gp_Pnt(nor.X(), nor.Y(), nor.Z()));
}

int shape::mirror(gp_Pnt pnt, gp_Pnt nor) {
  try {
    TopoDS_Shape &shape = _shape;

    if (shape.IsNull())
      throw std::runtime_error("Null shape");

    gp_Ax2 ax2(gp_Pnt(pnt.X(), pnt.Y(), pnt.Z()),
               gp_Dir(nor.X(), nor.Y(), nor.Z()));
    gp_Trsf trans;
    trans.SetMirror(ax2);
    BRepBuilderAPI_Transform aTrans(trans);
    aTrans.Perform(shape);
    if (!aTrans.IsDone())
      return 0;
    _shape = aTrans.Shape();
  } catch (Standard_Failure &e) {

    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to mirror object");
    }
    return 0;
  }
  return 1;
}

int shape::mirror(gp_Ax1 a) {
  try {
    TopoDS_Shape &shape = _shape;

    if (shape.IsNull())
      throw std::runtime_error("Null shape");

    gp_Trsf trans;
    trans.SetMirror(a);
    BRepBuilderAPI_Transform aTrans(trans);
    aTrans.Perform(shape);
    if (!aTrans.IsDone())
      return 0;
    _shape = aTrans.Shape();
  } catch (Standard_Failure &e) {

    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to mirror object");
    }
    return 0;
  }
  return 1;
}

int shape::mirror(gp_Ax2 a) {
  try {
    TopoDS_Shape &shape = _shape;

    if (shape.IsNull())
      throw std::runtime_error("Null shape");

    gp_Trsf trans;
    trans.SetMirror(a);
    BRepBuilderAPI_Transform aTrans(trans);
    aTrans.Perform(shape);
    if (!aTrans.IsDone())
      return 0;
    _shape = aTrans.Shape();
  } catch (Standard_Failure &e) {

    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to mirror object");
    }
    return 0;
  }
  return 1;
}

shape shape::transformed(gp_Trsf mat) const {
  auto shp = copy();
  shp.transform(mat);
  return shp;
}

shape shape::transformed(const topo_matrix &mat) const {
  auto shp = copy();
  shp.transform(mat);
  return shp;
}

shape shape::translated(gp_Vec delta) const {
  auto shp = copy();
  shp.translate(delta);
  return shp;
}

shape shape::rotated(double angle, gp_Pnt p1, gp_Pnt p2) const {
  auto shp = copy();
  shp.rotate(angle, p1, p2);
  return shp;
}

shape shape::rotated(double angle, gp_Ax1 a) const {
  auto shp = copy();
  shp.rotate(angle, a);
  return shp;
}

shape shape::rotated(gp_Quaternion R) const {
  auto shp = copy();
  shp.rotate(R);
  return shp;
}

shape shape::scaled(gp_Pnt pnt, double scale) const {
  auto shp = copy();
  shp.scale(pnt, scale);
  return shp;
}

shape shape::mirrored(gp_Pnt pnt, gp_Pnt nor) const {
  auto shp = copy();
  shp.mirror(pnt, nor);
  return shp;
}

shape shape::mirrored(gp_Pnt pnt, gp_Vec nor) const {
  auto shp = copy();
  shp.mirror(pnt, nor);
  return shp;
}

shape shape::mirrored(gp_Ax1 a) const {
  auto shp = copy();
  shp.mirror(a);
  return shp;
}

shape shape::mirrored(gp_Ax2 a) const {
  auto shp = copy();
  shp.mirror(a);
  return shp;
}

gp_Pln shape::find_plane(double tolerance) const {
  try {
    const TopoDS_Shape &shape = _shape;
    BRepBuilderAPI_FindPlane FP(shape, tolerance);
    if (!FP.Found())
      throw std::runtime_error("Plane not found");
    const Handle_Geom_Plane plane = FP.Plane();
    const gp_Ax1 axis = plane->Axis();

    const gp_Pnt loc = axis.Location();
    const gp_Dir dir = axis.Direction();
    return gp_Pln(loc, dir);
  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to find plane");
    }
  }
}

topo_location shape::location() const {
  return topo_location(_shape.Location());
}

gp_Pnt shape::centre_of_mass() const {
  GProp_GProps system;
  BRepGProp::VolumeProperties(_shape, system);
  return system.CentreOfMass();
}

gp_Pnt shape::center_of_bound_box() const { return this->bbox().center(); }

double shape::compute_area() const {
  GProp_GProps system;
  BRepGProp::SurfaceProperties(_shape, system);
  return system.Mass();
}

double shape::compute_mass() const {
  GProp_GProps system;
  BRepGProp::VolumeProperties(_shape, system);
  return system.Mass();
}

bool shape::location(double *loc) const {
  if (loc != nullptr && !_shape.IsNull()) {
    TopLoc_Location shape_location = _shape.Location();
    gp_Pnt pt = gp_Pnt(0., 0., 0.).Transformed(shape_location);
    loc[0] = pt.X();
    loc[1] = pt.Y();
    loc[2] = pt.Z();
    return true;
  }
  return false;
}

bool shape::surface_colour(double *colour) const {
  if (colour != nullptr) {
    colour[0] = _surface_colour.Red();
    colour[1] = _surface_colour.Green();
    colour[2] = _surface_colour.Blue();
  }
  return false;
}

void shape::set_location(const topo_location &loc) { _shape.Location(loc); }

shape shape::located(const topo_location &loc) const {
  shape result(value().Located(loc));
  result._for_construction = _for_construction;
  return result;
}

int shape::move(const topo_location &loc) {
  gp_Trsf trsf = loc;
  value().Move(trsf);
  return 1;
}

int shape::move(double x, double y, double z, double rx, double ry, double rz) {
  topo_location loc(gp_Vec(x, y, z), rx, ry, rz);
  gp_Trsf trsf = loc;
  value().Move(trsf);
  return 1;
}

int shape::move(const gp_Vec &vec) {
  gp_Trsf trsf;
  trsf.SetTranslation(vec);
  value().Move(trsf);
  return 1;
}

shape shape::moved(const topo_location &loc) const {
  gp_Trsf trsf = loc;
  TopoDS_Shape movedShape =
      BRepBuilderAPI_Transform(value(), trsf, true).Shape();
  shape result(movedShape);
  result._for_construction = _for_construction;
  return result;
}

shape shape::moved(std::initializer_list<topo_location> locs) const {
  return moved(std::vector<topo_location>(locs));
}

shape shape::moved(const std::vector<topo_location> &locs) const {
  TopTools_ListOfShape shapeList;

  for (const auto &loc : locs) {
    shapeList.Append(moved(loc).value());
  }

  if (shapeList.Size() == 1) {
    return shape(shapeList.First());
  }

  TopoDS_Compound compound;
  BRep_Builder builder;
  builder.MakeCompound(compound);

  for (auto &shape : shapeList) {
    builder.Add(compound, shape);
  }

  return shape(compound);
}

shape shape::moved(double x, double y, double z, double rx, double ry,
                   double rz) const {
  topo_location loc(gp_Vec(x, y, z), rx, ry, rz);
  gp_Trsf trsf = loc;
  return moved(topo_location(trsf));
}

shape shape::moved(const gp_Vec &vec) const {
  gp_Trsf trsf;
  trsf.SetTranslation(vec);
  return moved(topo_location(trsf));
}

shape shape::moved(std::initializer_list<gp_Vec> vecs) const {
  std::vector<topo_location> locs;
  for (const auto &vec : vecs) {
    locs.emplace_back(topo_location(vec));
  }
  return moved(locs);
}

shape shape::moved(const std::vector<gp_Vec> &vecs) const {
  std::vector<topo_location> locs;
  for (const auto &vec : vecs) {
    locs.emplace_back(topo_location(vec));
  }
  return moved(locs);
}

orientation shape::get_orientation() const {
  switch (_shape.Orientation()) {
  case TopAbs_FORWARD:
    return orientation::FORWARD;
  case TopAbs_REVERSED:
    return orientation::REVERSED;
  case TopAbs_INTERNAL:
    return orientation::INTERNAL;
  case TopAbs_EXTERNAL:
    return orientation::EXTERNAL;
  default:
    break;
  }
  return orientation::UNKNOW;
}

void shape::set_orientation(orientation ori) {
  switch (ori) {
  case orientation::FORWARD:
    _shape.Orientation(TopAbs_FORWARD);
    break;
  case orientation::REVERSED:
    _shape.Orientation(TopAbs_REVERSED);
    break;
  case orientation::INTERNAL:
    _shape.Orientation(TopAbs_INTERNAL);
    break;
  case orientation::EXTERNAL:
    _shape.Orientation(TopAbs_EXTERNAL);
    break;
  default:
    break;
  }
}

shape shape::oriented(orientation ori) const {
  auto shp = copy();
  shp.set_orientation(ori);
  return shp;
}

bool shape::fix_shape() {
  if (_shape.IsNull())
    return false;

  BRepCheck_Analyzer aChecker(_shape);
  if (!aChecker.IsValid()) {
    ShapeFix_ShapeTolerance aSFT;
    aSFT.LimitTolerance(_shape, Precision::Confusion(), Precision::Confusion());

    Handle(ShapeFix_Shape) aSfs = new ShapeFix_Shape(_shape);
    aSfs->SetPrecision(Precision::Confusion());
    aSfs->Perform();

    const TopoDS_Shape aShape = aSfs->Shape();
    aChecker.Init(aShape, Standard_False);

    if (aChecker.IsValid()) {
      _shape = aShape;
    }
  }
  return aChecker.IsValid();
}

boost::optional<compound> shape::ancestors(const shape &shape,
                                           TopAbs_ShapeEnum kind) const {
  if (is_null() || shape.is_null()) {
    return boost::none;
  }

  TopTools_IndexedDataMapOfShapeListOfShape shapeMap;
  TopExp::MapShapesAndAncestors(shape, value().ShapeType(), kind, shapeMap);

  if (!shapeMap.Contains(*this)) {
    return boost::none;
  }

  BRep_Builder builder;
  TopoDS_Compound result;
  builder.MakeCompound(result);
  const TopTools_ListOfShape &ancestors = shapeMap.FindFromKey(*this);

  TopTools_ListIteratorOfListOfShape it(ancestors);
  for (; it.More(); it.Next()) {
    builder.Add(result, it.Value());
  }

  return boost::make_optional<compound>(result);
}

boost::optional<compound>
shape::siblings(const shape &shape, TopAbs_ShapeEnum kind, int level) const {
  TopTools_IndexedDataMapOfShapeListOfShape shapeMap;
  TopTools_MapOfShape exclude;
  BRep_Builder builder;
  TopoDS_Compound result;
  builder.MakeCompound(result);

  TopExp::MapShapesAndAncestors(shape, kind, value().ShapeType(), shapeMap);

  std::function<std::vector<TopoDS_Shape>(const std::vector<TopoDS_Shape> &,
                                          int)>
      findSiblings;
  findSiblings = [&](const std::vector<TopoDS_Shape> &shapes,
                     int currentLevel) {
    std::unordered_set<TopoDS_Shape, TopoDS_ShapeHasher> siblingsSet;

    for (const auto &s : shapes) {
      exclude.Add(s);
    }

    for (const auto &s : shapes) {
      TopTools_IndexedMapOfShape entities;
      TopExp::MapShapes(s, kind, entities);

      for (int i = 1; i <= entities.Extent(); ++i) {
        const TopoDS_Shape &entity = entities(i);
        if (shapeMap.Contains(entity)) {
          const TopTools_ListOfShape &sharingShapes =
              shapeMap.FindFromKey(entity);
          TopTools_ListIteratorOfListOfShape sit(sharingShapes);
          for (; sit.More(); sit.Next()) {
            const TopoDS_Shape &sibling = sit.Value();
            if (!exclude.Contains(sibling)) {
              siblingsSet.insert(sibling);
            }
          }
        }
      }
    }

    std::vector<TopoDS_Shape> siblingsVec(siblingsSet.begin(),
                                          siblingsSet.end());

    if (currentLevel > 1 && !siblingsVec.empty()) {
      return findSiblings(siblingsVec, currentLevel - 1);
    }

    return siblingsVec;
  };

  std::vector<TopoDS_Shape> initialShapes = {*this};
  auto siblings = findSiblings(initialShapes, level);

  for (const auto &s : siblings) {
    builder.Add(result, s);
  }

  return boost::make_optional<compound>(result);
}

void shape::set_txture_map_type(texture_mapping_rule t) {
  _txture_map_type = t;
  if (_txture_map_type == texture_cube) {
    prepare_box_texture_coordinates(_shape);
  }
}

int shape::write_triangulation(mesh_receiver &meshReceiver, double tolerance,
                               double deflection, double angle,
                               bool uv_coords) {
  Standard_Real Umin;
  Standard_Real Umax;
  Standard_Real Vmin;
  Standard_Real Vmax;

  Standard_Real dUmax;
  Standard_Real dVmax;

  gp_Vec2d _coord_p;
  gp_Pnt2d d_coord;

  try {
    TopTools_IndexedMapOfShape faceMap;
    TopoDS_Shape shape = *this;
    TopExp::MapShapes(shape, TopAbs_FACE, faceMap);
    int faceCount = faceMap.Extent();
    if (faceCount == 0)
      return 1;
    std::vector<bool> hasSeams;
    hasSeams.resize(faceCount);
    for (int f = 0; f < faceMap.Extent(); f++) {
      TopTools_IndexedMapOfShape edgeMap;
      TopExp::MapShapes(faceMap(f + 1), TopAbs_EDGE, edgeMap);
      hasSeams[f] = false;
      for (Standard_Integer i = 1; i <= edgeMap.Extent(); i++) {
        hasSeams[f] = (BRep_Tool::IsClosed(edgeMap(i)) == Standard_True);
        if (hasSeams[f])
          break;
      }
    }

    BRepMesh_IncrementalMesh incrementalMesh(*this, deflection, Standard_False,
                                             angle, Standard_True);
    Quantity_Color color(1., 1., 1., Quantity_TOC_RGB);
    for (int f = 1; f <= faceMap.Extent(); f++) {
      meshReceiver.begin();

      const TopoDS_Face &face = TopoDS::Face(faceMap(f));
      int faceId = meshReceiver.append_face(color);
      bool faceReversed = (face.Orientation() == TopAbs_REVERSED);

      TopLoc_Location loc;
      const Handle(Poly_Triangulation) &mesh =
          BRep_Tool::Triangulation(face, loc);
      if (mesh.IsNull())
        continue;
      bool hasSeam = hasSeams[f - 1];
      gp_Trsf transform = loc.Transformation();
      gp_Quaternion quaternion = transform.GetRotation();
      Handle(TColgp_HArray1OfPnt) nodes = mesh->MapNodeArray();
      Poly::ComputeNormals(mesh);

      if (hasSeam) {
        TColStd_Array1OfReal norms(1, mesh->MapNormalArray()->Length());
        for (Standard_Integer i = 1; i <= mesh->NbNodes() * 3; i += 3) {
          gp_Dir dir(mesh->MapNormalArray()->Value(i),
                     mesh->MapNormalArray()->Value(i + 1),
                     mesh->MapNormalArray()->Value(i + 2));
          if (faceReversed)
            dir.Reverse();
          dir = quaternion.Multiply(dir);
          norms.SetValue(i, dir.X());
          norms.SetValue(i + 1, dir.Y());
          norms.SetValue(i + 2, dir.Z());
        }
        std::unordered_map<point3d_with_tolerance, int> uniquePointsOnFace;
        for (Standard_Integer j = 1; j <= mesh->NbNodes(); j++) {
          gp_Pnt p = nodes->Value(j);
          point3d_with_tolerance pt(p.X(), p.Y(), p.Z(), tolerance);
          int nodeIndex;
          if (uniquePointsOnFace.find(pt) != uniquePointsOnFace.end()) {
            nodeIndex = uniquePointsOnFace[pt];
            gp_Vec normalA(norms.Value(nodeIndex), norms.Value(nodeIndex) + 1,
                           norms.Value(nodeIndex) + 2);
            gp_Vec normalB(norms.Value(j), norms.Value(j) + 1,
                           norms.Value(j) + 2);
            gp_Vec normalBalanced = normalA + normalB;
            normalBalanced.Normalize();
            norms.SetValue(nodeIndex, normalBalanced.X());
            norms.SetValue(nodeIndex + 1, normalBalanced.Y());
            norms.SetValue(nodeIndex + 2, normalBalanced.Z());
            norms.SetValue(j, normalBalanced.X());
            norms.SetValue(j + 1, normalBalanced.Y());
            norms.SetValue(j + 2, normalBalanced.Z());
          } else
            uniquePointsOnFace.emplace(pt, j);
        }

        if (uv_coords) {
          if (_txture_map_type == texture_normal ||
              _txture_map_type == texture_normal_auto_scale) {
            BRepTools::UVBounds(face, Umin, Umax, Vmin, Vmax);
            dUmax = (Umax - Umin);
            dVmax = (Vmax - Vmin);
            if (_txture_map_type == texture_normal_auto_scale) {
              _scale_u = _auto_scale_size_on_u / dUmax;
              _scale_v = _auto_scale_size_on_v / dVmax;
            }
          }
          Handle(TColgp_HArray1OfPnt2d) UVNodes = mesh->MapUVNodeArray();
          TColgp_Array1OfPnt2d coords(1, UVNodes->Length());
          for (int i = UVNodes->Lower(); i <= UVNodes->Upper(); i++) {
            if (_txture_map_type == texture_cube) {
              gp_Dir dir(norms.Value((i * 3) + 1), norms.Value((i * 3) + 2),
                         norms.Value((i * 3) + 3));
              get_box_texture_coordinate(
                  (*nodes)(i).Transformed(loc.Transformation()),
                  dir.Transformed(loc.Transformation()), _coord_p);
              d_coord.SetX(
                  (-_u_origin + (_u_repeat * _coord_p.X()) / _bnd_box_sz) /
                  _scale_u);
              d_coord.SetY(
                  (-_v_origin + (_v_repeat * _coord_p.Y()) / _bnd_box_sz) /
                  _scale_v);
            } else {
              d_coord = (*UVNodes)(i);
              d_coord.SetX(
                  (-_u_origin + (_u_repeat * (d_coord.X() - Umin)) / dUmax) /
                  _scale_u);
              d_coord.SetY(
                  (-_v_origin + (_v_repeat * (d_coord.Y() - Vmin)) / dVmax) /
                  _scale_v);
            }
            d_coord.Rotate(gp::Origin2d(), _rotation_angle);
            coords.SetValue(i, d_coord);
          }

          for (Standard_Integer j = 0; j < mesh->NbNodes(); j++) {
            gp_Pnt p = nodes->Value(j + 1);
            Standard_Real px = p.X();
            Standard_Real py = p.Y();
            Standard_Real pz = p.Z();
            transform.Transforms(px, py, pz);
            gp_Dir dir(norms.Value((j * 3) + 1), norms.Value((j * 3) + 2),
                       norms.Value((j * 3) + 3));
            gp_Pnt2d coord = coords(j + 1);
            meshReceiver.append_node(faceId, gp_Pnt{px, py, pz},
                                     gp_Pnt{dir.X(), dir.Y(), dir.Z()}, coord);
          }
        } else {
          for (Standard_Integer j = 0; j < mesh->NbNodes(); j++) {
            gp_Pnt p = nodes->Value(j + 1);
            Standard_Real px = p.X();
            Standard_Real py = p.Y();
            Standard_Real pz = p.Z();
            transform.Transforms(px, py, pz);
            gp_Dir dir(norms.Value((j * 3) + 1), norms.Value((j * 3) + 2),
                       norms.Value((j * 3) + 3));
            meshReceiver.append_node(faceId, gp_Pnt{px, py, pz},
                                     gp_Pnt{dir.X(), dir.Y(), dir.Z()});
          }
        }
      } else {
        if (uv_coords) {
          if (_txture_map_type == texture_normal ||
              _txture_map_type == texture_normal_auto_scale) {
            BRepTools::UVBounds(face, Umin, Umax, Vmin, Vmax);
            dUmax = (Umax - Umin);
            dVmax = (Vmax - Vmin);
            if (_txture_map_type == texture_normal_auto_scale) {
              _scale_u = _auto_scale_size_on_u / dUmax;
              _scale_v = _auto_scale_size_on_v / dVmax;
            }
          }
          Handle(TColgp_HArray1OfPnt2d) UVNodes = mesh->MapUVNodeArray();
          TColgp_Array1OfPnt2d coords(1, UVNodes->Length());
          for (int i = UVNodes->Lower(); i <= UVNodes->Upper(); i++) {
            if (_txture_map_type == texture_cube) {
              gp_Dir dir(mesh->MapNormalArray()->Value((i * 3) + 1),
                         mesh->MapNormalArray()->Value((i * 3) + 2),
                         mesh->MapNormalArray()->Value((i * 3) + 3));
              get_box_texture_coordinate(
                  (*nodes)(i).Transformed(loc.Transformation()),
                  dir.Transformed(loc.Transformation()), _coord_p);
              d_coord.SetX(
                  (-_u_origin + (_u_repeat * _coord_p.X()) / _bnd_box_sz) /
                  _scale_u);
              d_coord.SetY(
                  (-_v_origin + (_v_repeat * _coord_p.Y()) / _bnd_box_sz) /
                  _scale_v);
            } else {
              d_coord = (*UVNodes)(i);
              d_coord.SetX(
                  (-_u_origin + (_u_repeat * (d_coord.X() - Umin)) / dUmax) /
                  _scale_u);
              d_coord.SetY(
                  (-_v_origin + (_v_repeat * (d_coord.Y() - Vmin)) / dVmax) /
                  _scale_v);
            }
            d_coord.Rotate(gp::Origin2d(), _rotation_angle);
            coords.SetValue(i, d_coord);
          }

          for (Standard_Integer j = 0; j < mesh->NbNodes(); j++) {
            gp_Pnt p = nodes->Value(j + 1);
            Standard_Real px = p.X();
            Standard_Real py = p.Y();
            Standard_Real pz = p.Z();
            transform.Transforms(px, py, pz);
            gp_Dir dir(mesh->MapNormalArray()->Value((j * 3) + 1),
                       mesh->MapNormalArray()->Value((j * 3) + 2),
                       mesh->MapNormalArray()->Value((j * 3) + 3));
            if (faceReversed)
              dir.Reverse();
            dir = quaternion.Multiply(dir);
            gp_Pnt2d coord = coords(j + 1);
            meshReceiver.append_node(faceId, gp_Pnt{px, py, pz},
                                     gp_Pnt{dir.X(), dir.Y(), dir.Z()}, coord);
          }
        } else {
          for (Standard_Integer j = 0; j < mesh->NbNodes(); j++) {
            gp_Pnt p = nodes->Value(j + 1);
            Standard_Real px = p.X();
            Standard_Real py = p.Y();
            Standard_Real pz = p.Z();
            transform.Transforms(px, py, pz);
            gp_Dir dir(mesh->MapNormalArray()->Value((j * 3) + 1),
                       mesh->MapNormalArray()->Value((j * 3) + 2),
                       mesh->MapNormalArray()->Value((j * 3) + 3));
            if (faceReversed)
              dir.Reverse();
            dir = quaternion.Multiply(dir);
            meshReceiver.append_node(faceId, gp_Pnt{px, py, pz},
                                     gp_Pnt{dir.X(), dir.Y(), dir.Z()});
          }
        }
      }

      Standard_Integer t[3];
      Handle(Poly_HArray1OfTriangle) triangles = mesh->MapTriangleArray();

      for (Standard_Integer j = 1; j <= mesh->NbTriangles(); j++) {
        if (faceReversed)
          triangles->Value(j).Get(t[2], t[1], t[0]);
        else
          triangles->Value(j).Get(t[0], t[1], t[2]);
        int tri[3];
        tri[0] = t[0] - 1;
        tri[1] = t[1] - 1;
        tri[2] = t[2] - 1;
        meshReceiver.append_triangle(faceId, tri);
      }
    }

    meshReceiver.end();
    return 0;
  } catch (Standard_Failure &e) {
    return 1;
  } catch (...) {
    return 1;
  }
}

int shape::mesh_edges(mesh_edges_receiver &receiver, double tolerance,
                      double angular_tolerance) const {
  try {
    std::unordered_set<int> recorded_edges;
    receiver.begin();

    TopLoc_Location location;

    for (const auto &face : faces()) {
      Handle(Poly_Triangulation) triangulation =
          BRep_Tool::Triangulation(face.value(), location);
      if (triangulation.IsNull())
        continue;

      for (const auto &edge : face.edges()) {
        int edge_hash = edge.hash_code();
        if (recorded_edges.count(edge_hash))
          continue;

        TopLoc_Location edge_loc;
        Handle(Poly_PolygonOnTriangulation) polygon =
            BRep_Tool::PolygonOnTriangulation(edge.value(), triangulation,
                                              edge_loc);

        if (polygon.IsNull())
          continue;

        const TColStd_Array1OfInteger &nodes = polygon->Nodes();

        Quantity_Color color(1., 1., 1., Quantity_TOC_RGB);
        int edge_id = receiver.append_edge(color);
        for (int i = nodes.Lower(); i <= nodes.Upper(); ++i) {
          gp_Pnt p = triangulation->Node(nodes(i)).Transformed(
              edge_loc.Transformation());
          receiver.append_point(edge_id, p);
        }

        recorded_edges.insert(edge_hash);
      }
    }

    for (const auto &edge : edges()) {
      int edge_hash = edge.hash_code();
      if (recorded_edges.count(edge_hash))
        continue;

      Quantity_Color color(1., 1., 1., Quantity_TOC_RGB);

      BRepAdaptor_Curve curve(edge.value());
      GCPnts_TangentialDeflection discretizer(curve, tolerance,
                                              angular_tolerance, 2, 1e-9, 1e-7);
      int edge_id = receiver.append_edge(color);
      for (int i = 1; i <= discretizer.NbPoints(); ++i) {
        gp_Pnt p = discretizer.Value(i).Transformed(location.Transformation());
        receiver.append_point(edge_id, p);
      }

      recorded_edges.insert(edge_hash);
    }

    receiver.end();
    return 0;
  } catch (Standard_Failure &e) {
    return 1;
  } catch (...) {
    return 1;
  }
}

namespace detail {

template <typename T> struct shape_type {
  static const TopAbs_ShapeEnum value = TopAbs_SHAPE;

  static TopoDS_Shape &cast(TopoDS_Shape &shp) { return shp; }
};

template <> struct shape_type<compound> {
  static const TopAbs_ShapeEnum value = TopAbs_COMPOUND;

  static TopoDS_Compound &cast(TopoDS_Shape &shp) {
    return TopoDS::Compound(shp);
  }
};

template <> struct shape_type<comp_solid> {
  static const TopAbs_ShapeEnum value = TopAbs_COMPSOLID;

  static TopoDS_CompSolid &cast(TopoDS_Shape &shp) {
    return TopoDS::CompSolid(shp);
  }
};

template <> struct shape_type<solid> {
  static const TopAbs_ShapeEnum value = TopAbs_SOLID;
  static TopoDS_Solid &cast(TopoDS_Shape &shp) { return TopoDS::Solid(shp); }
};

template <> struct shape_type<shell> {
  static const TopAbs_ShapeEnum value = TopAbs_SHELL;
  static TopoDS_Shell &cast(TopoDS_Shape &shp) { return TopoDS::Shell(shp); }
};

template <> struct shape_type<face> {
  static const TopAbs_ShapeEnum value = TopAbs_FACE;

  static TopoDS_Face &cast(TopoDS_Shape &shp) { return TopoDS::Face(shp); }
};

template <> struct shape_type<wire> {
  static const TopAbs_ShapeEnum value = TopAbs_WIRE;

  static TopoDS_Wire &cast(TopoDS_Shape &shp) { return TopoDS::Wire(shp); }
};

template <> struct shape_type<edge> {
  static const TopAbs_ShapeEnum value = TopAbs_EDGE;

  static TopoDS_Edge &cast(TopoDS_Shape &shp) { return TopoDS::Edge(shp); }
};

template <> struct shape_type<vertex> {
  static const TopAbs_ShapeEnum value = TopAbs_VERTEX;

  static TopoDS_Vertex &cast(TopoDS_Shape &shp) { return TopoDS::Vertex(shp); }
};

} // namespace detail

template <typename TShape> boost::optional<TShape> shape::cast() const {
  if (_shape.ShapeType() == detail::shape_type<TShape>::value) {
    return TShape(_shape);
  }
  return boost::none;
}

template boost::optional<shape> shape::cast<shape>() const;
template boost::optional<compound> shape::cast<compound>() const;
template boost::optional<comp_solid> shape::cast<comp_solid>() const;
template boost::optional<solid> shape::cast<solid>() const;
template boost::optional<shell> shape::cast<shell>() const;
template boost::optional<face> shape::cast<face>() const;
template boost::optional<wire> shape::cast<wire>() const;
template boost::optional<edge> shape::cast<edge>() const;
template boost::optional<vertex> shape::cast<vertex>() const;

boost::optional<shape> shape::auto_cast() const {
  if (!_shape.IsNull()) {
    switch (_shape.ShapeType()) {
    case TopAbs_VERTEX:
      return vertex(*this, _shape);
    case TopAbs_EDGE:
      return edge(*this, _shape);
    case TopAbs_WIRE:
      return wire(*this, _shape);
    case TopAbs_FACE:
      return face(*this, _shape);
    case TopAbs_SHELL:
      return shell(*this, _shape);
    case TopAbs_SOLID:
      return solid(*this, _shape);
    case TopAbs_COMPOUND:
      return compound(*this, _shape);
    case TopAbs_COMPSOLID:
      return comp_solid(*this, _shape);
    default:
      break;
    }
  }
  return boost::none;
}

boost::optional<shape> shape::make_shape(TopoDS_Shape shp) {
  if (!shp.IsNull()) {
    switch (shp.ShapeType()) {
    case TopAbs_VERTEX:
      return vertex(shp);
    case TopAbs_EDGE:
      return edge(shp);
    case TopAbs_WIRE:
      return wire(shp);
    case TopAbs_FACE:
      return face(shp);
    case TopAbs_SHELL:
      return shell(shp);
    case TopAbs_SOLID:
      return solid(shp);
    case TopAbs_COMPOUND:
      return compound(shp);
    default:
      break;
    }
  }
  return boost::none;
}

TopAbs_ShapeEnum shape::shape_type() const { return _shape.ShapeType(); }

shape_geom_type shape::geom_type() const {
  if (_shape.IsNull()) {
    return shape_geom_null;
  }
  return get_geom_type(_shape);
}

void shape::build_maps() {
  TopExp::MapShapes(_shape, TopAbs_VERTEX, _vmap);
  TopExp::MapShapes(_shape, TopAbs_EDGE, _emap);
  TopExp::MapShapes(_shape, TopAbs_FACE, _fmap);
}

void shape::clear_maps() {
  _vmap.Clear();
  _emap.Clear();
  _fmap.Clear();
}

void shape::prepare_box_texture_coordinates(const TopoDS_Shape &aShape) {
  Bnd_Box aBox;
  Standard_Real aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;

  BRepBndLib::Add(aShape, aBox);
  aBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

  Standard_Real xDim = std::abs((long)aXmax - (long)aXmin);
  Standard_Real yDim = std::abs((long)aYmax - (long)aYmin);
  Standard_Real zDim = std::abs((long)aZmax - (long)aZmin);

  if ((xDim > yDim) && (xDim > zDim)) {
    aYmin -= (xDim - yDim) / 2;
    aYmax += (xDim - yDim) / 2;

    aZmin -= (xDim - zDim) / 2;
    aZmax += (xDim - zDim) / 2;
  } else if ((yDim > xDim) && (yDim > zDim)) {
    aXmin -= (yDim - xDim) / 2;
    aXmax += (yDim - xDim) / 2;

    aZmin -= (yDim - zDim) / 2;
    aZmax += (yDim - zDim) / 2;
  } else {
    aXmin -= (zDim - xDim) / 2;
    aXmax += (zDim - xDim) / 2;

    aYmin -= (zDim - yDim) / 2;
    aYmax += (zDim - yDim) / 2;
  }

  _bnd_box_sz = aXmax - aXmin;
}

void shape::get_box_texture_coordinate(const gp_Pnt &p, const gp_Dir &N1,
                                       gp_Vec2d &_coord_p) {
  Standard_Real x = std::abs(N1.X());
  Standard_Real y = std::abs(N1.Y());
  Standard_Real z = std::abs(N1.Z());

  if (x >= y && x >= z) {
    if (N1.X() > 0) {
      _coord_p.SetX(p.Y() - _Ymin);
      _coord_p.SetY(p.Z() - _Zmin);
      _coord_p.Rotate(M_PI / 2.);
    } else {
      _coord_p.SetX(p.Z() - _Zmin);
      _coord_p.SetY(p.Y() - _Ymin);
    }
  } else if ((y >= z) && (y >= x)) {
    if (N1.Y() > 0) {
      _coord_p.SetX(p.X() - _Xmin);
      _coord_p.SetY(-(p.Z() - _Zmin));
    } else {
      _coord_p.SetY(p.Z() - _Zmin);
      _coord_p.SetX(p.X() - _Xmin);
      _coord_p.Rotate(M_PI);
    }
  } else {
    if (N1.Z() > 0) {
      _coord_p.SetX(p.X() - _Xmin);
      _coord_p.SetY(p.Y() - _Ymin);
    } else {
      _coord_p.SetX(p.Y() - _Ymin);
      _coord_p.SetY(p.X() - _Xmin);
      _coord_p.Rotate(M_PI / 2.);
    }
  }
}

shape shape::clean() {
  Handle(ShapeUpgrade_UnifySameDomain) upgrader =
      new ShapeUpgrade_UnifySameDomain(_shape, Standard_True, Standard_True,
                                       Standard_True);
  upgrader->AllowInternalEdges(Standard_False);
  upgrader->Build();
  return upgrader->Shape();
}

bool shape::export_step(const std::string &fileName, bool write_pcurves,
                        int precision_mode) const {
  Interface_Static::SetIVal("write.surfacecurve.mode", write_pcurves ? 1 : 0);
  Interface_Static::SetIVal("write.precision.mode", precision_mode);

  STEPControl_Writer writer;
  writer.Transfer(_shape, STEPControl_AsIs);
  return writer.Write(fileName.c_str());
}

bool shape::export_brep(const std::string &fileName) const {
  return BRepTools::Write(_shape, fileName.c_str());
}

boost::optional<shape> shape::import_from_brep(const std::string &fileName) {
  TopoDS_Shape shp;
  BRep_Builder builder;

  if (!BRepTools::Read(shp, fileName.c_str(), builder)) {
    return boost::none;
  }

  if (shp.IsNull()) {
    return boost::none;
  }

  return boost::make_optional<shape>(shp);
}

gp_Pnt shape::combined_center(const std::vector<shape> &shapes) {
  if (shapes.empty()) {
    throw std::invalid_argument("Empty shape list");
  }

  double totalMass = 0.0;
  gp_Pnt weightedSum(0, 0, 0);

  for (const auto &s : shapes) {
    GProp_GProps props;
    compute_properties(s, props);
    double mass = props.Mass();
    gp_Pnt com = props.CentreOfMass();

    totalMass += mass;
    weightedSum.ChangeCoord().Add(com.XYZ().Multiplied(mass));
  }

  if (totalMass <= 0.0) {
    throw std::runtime_error("Total mass must be positive");
  }

  return gp_Pnt(weightedSum.XYZ().Divided(totalMass));
}

gp_Pnt
shape::combined_center_of_bounding_box(const std::vector<shape> &shapes) {
  if (shapes.empty()) {
    throw std::invalid_argument("Empty shape list");
  }

  Bnd_Box combinedBox;
  for (const auto &s : shapes) {
    Bnd_Box shapeBox;
    BRepBndLib::Add(s, shapeBox);
    combinedBox.Add(shapeBox);
  }

  double xMin, yMin, zMin, xMax, yMax, zMax;
  combinedBox.Get(xMin, yMin, zMin, xMax, yMax, zMax);

  return gp_Pnt((xMin + xMax) / 2.0, (yMin + yMax) / 2.0, (zMin + zMax) / 2.0);
}

boost::optional<shape> shape::to_splines(int degree, double tolerance,
                                         bool nurbs) const {

  if (this->is_null()) {
    return boost::none;
  }

  TopoDS_Shape result =
      ShapeCustom::BSplineRestriction(_shape,
                                      tolerance, // 3D容差
                                      tolerance, // 2D容差
                                      degree,
                                      1,             // 段数 (被degree参数主导)
                                      GeomAbs_C0,    // 连续性
                                      GeomAbs_C0,    // 连续性
                                      Standard_True, // degree参数主导
                                      !nurbs,        // 是否禁用有理样条
                                      nullptr);

  if (result.IsNull()) {
    return boost::none;
  }

  return boost::make_optional<shape>(result);
}

boost::optional<shape> shape::to_nurbs() const {
  if (this->is_null()) {
    return boost::none;
  }

  BRepBuilderAPI_NurbsConvert converter(_shape,
                                        Standard_True); // Standard_True = Copy
  converter.Perform(_shape);

  if (!converter.IsDone()) {
    return boost::none;
  }

  const TopoDS_Shape &result = converter.Shape();
  if (result.IsNull()) {
    throw std::runtime_error("Resulting shape is null");
  }

  return boost::make_optional<shape>(result);
}

double shape::distance(const shape &o) const {
  return distance_with_points(_shape, o.value()).first;
}

std::unordered_map<shape, std::vector<shape>>
shape::get_entities_from(TopAbs_ShapeEnum childType,
                         TopAbs_ShapeEnum parentType) const {
  TopTools_IndexedDataMapOfShapeListOfShape resultMap;

  TopExp::MapShapesAndAncestors(this->value(), childType, parentType,
                                resultMap);

  std::unordered_map<shape, std::vector<shape>> outputMap;

  for (int i = 1; i <= resultMap.Extent(); i++) {
    const TopoDS_Shape &keyShape = resultMap.FindKey(i);
    const TopTools_ListOfShape &valueList = resultMap.FindFromIndex(i);

    std::vector<shape> valueVector;
    TopTools_ListIteratorOfListOfShape it(valueList);
    for (; it.More(); it.Next()) {
      valueVector.push_back(shape(it.Value()));
    }

    outputMap[shape(keyShape)] = valueVector;
  }

  return outputMap;
}

std::vector<shape> shape::children() const {
  std::vector<shape> result;

  TopExp_Explorer exp(this->value(), TopAbs_SHAPE);
  for (; exp.More(); exp.Next()) {
    result.emplace_back(exp.Current());
  }

  return result;
}

std::vector<shape> shape::get_shapes(TopAbs_ShapeEnum kind) const {
  std::vector<shape> result;

  if (kind == TopAbs_SHAPE) {
    TopoDS_Iterator it(this->value());

    for (; it.More(); it.Next()) {
      result.push_back(shape(it.Value()));
    }
  } else {

    TopExp_Explorer exp(this->value(), kind);

    for (; exp.More(); exp.Next()) {
      result.emplace_back(exp.Current());
    }
  }

  return result;
}

void shape::set_for_construction(bool for_construction) const {
  _for_construction = for_construction;
}

std::string shape::to_string(double tolerance, double angularTolerance) const {
  STEPControl_Writer stepWriter;
  stepWriter.Transfer(this->value(), STEPControl_AsIs);

  std::ostringstream stepStream;
  if (stepWriter.WriteStream(stepStream)) {
    return stepStream.str();
  }
  return "";
}

std::vector<vertex> shape::vertices() const {
  return extract_entities<vertex>(TopAbs_VERTEX);
}

std::vector<edge> shape::edges() const {
  return extract_entities<edge>(TopAbs_EDGE);
}

std::vector<compound> shape::compounds() const {
  return extract_entities<compound>(TopAbs_COMPOUND);
}

std::vector<wire> shape::wires() const {
  return extract_entities<wire>(TopAbs_WIRE);
}

std::vector<face> shape::faces() const {
  return extract_entities<face>(TopAbs_FACE);
}

std::vector<shell> shape::shells() const {
  return extract_entities<shell>(TopAbs_SHELL);
}

std::vector<solid> shape::solids() const {
  return extract_entities<solid>(TopAbs_SOLID);
}

std::vector<comp_solid> shape::comp_solids() const {
  return extract_entities<comp_solid>(TopAbs_COMPSOLID);
}

int shape::num_entities(TopAbs_ShapeEnum type) const {
  TopTools_IndexedMapOfShape anIndices;
  TopExp::MapShapes(_shape, type, anIndices);
  return anIndices.Extent();
}

shape shape::filter(const selector_ptr &sel, const std::vector<shape> &shapes) {
  std::vector<shape> selected;

  if (sel) {
    selected = sel->filter(shapes);
  } else {
    selected = shapes;
  }

  if (selected.size() == 1) {
    return selected[0];
  } else {
    return compound::make_compound(selected);
  }
}

bool shape::is_solid() const {
  if (_shape.IsNull()) {
    return false;
  }

  const TopAbs_ShapeEnum shapeType = _shape.ShapeType();

  if (shapeType == TopAbs_SOLID) {
    return true;
  }

  if (shapeType == TopAbs_COMPOUND) {
    TopExp_Explorer exp(_shape, TopAbs_SOLID);
    return exp.More();
  }

  return false;
}

std::vector<double> shape::distances(const std::vector<shape> &others) const {
  std::vector<double> results;
  results.reserve(others.size());

  BRepExtrema_DistShapeShape distCalc;
  distCalc.LoadS1(_shape);

  for (const auto &other : others) {
    distCalc.LoadS2(other);
    distCalc.Perform();

    if (distCalc.IsDone()) {
      results.push_back(distCalc.Value());
    } else {
      results.push_back(-1.0); // Using -1.0 as error indicator
    }
  }

  return results;
}

template <typename OpType>
shape shape::bool_op(const std::vector<shape> &args,
                     const std::vector<shape> &tools, OpType &op,
                     bool parallel) const {
  TopTools_ListOfShape argList;
  for (const auto &obj : args) {
    argList.Append(obj);
  }

  TopTools_ListOfShape toolList;
  for (const auto &obj : tools) {
    toolList.Append(obj);
  }

  op.SetArguments(argList);
  op.SetTools(toolList);
  op.SetRunParallel(parallel);
  op.Build();

  if (!op.IsDone()) {
    throw std::runtime_error("Boolean operation failed");
  }

  return shape(op.Shape());
}

} // namespace topo
} // namespace flywave
