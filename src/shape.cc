#include "shape.hh"
#include "point3d_with_tolerance.hh"

#include "comp_solid.hh"
#include "compound.hh"
#include "edge.hh"
#include "face.hh"
#include "shell.hh"
#include "solid.hh"
#include "vertex.hh"
#include "wire.hh"

#include <BRepBndLib.hxx>
#include <BRepBuilderAPI_Copy.hxx>
#include <BRepBuilderAPI_FindPlane.hxx>
#include <BRepBuilderAPI_GTransform.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepCheck_Analyzer.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <BRepTools.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <BRep_Tool.hxx>
#include <Bnd_Box.hxx>
#include <Geom_Line.hxx>
#include <Geom_Plane.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Poly.hxx>
#include <Poly_Triangulation.hxx>
#include <ShapeFix_Shape.hxx>
#include <ShapeFix_ShapeTolerance.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <TShort_Array1OfShortReal.hxx>
#include <TopExp.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopoDS.hxx>
#include <gp_Quaternion.hxx>

#include <unordered_map>
#include <limits>

namespace flywave {
namespace topo {

shape::shape()
    : _shape(), _surface_colour(Quantity_NOC_WHITE),
      _curve_colour(Quantity_NOC_WHITE), _u_origin(0.), _v_origin(0.),
      _u_repeat(1.), _v_repeat(1.), _scale_u(1.), _scale_v(1.),
      _auto_scale_size_on_u(1.), _auto_scale_size_on_v(1.),
      _txture_map_type(texture_normal), _rotation_angle(0.) {}

shape::shape(TopoDS_Shape shp)
    : _shape(shp), _surface_colour(Quantity_NOC_WHITE),
      _curve_colour(Quantity_NOC_WHITE), _u_origin(0.), _v_origin(0.),
      _u_repeat(1.), _v_repeat(1.), _scale_u(1.), _scale_v(1.),
      _auto_scale_size_on_u(1.), _auto_scale_size_on_v(1.),
      _txture_map_type(texture_normal), _rotation_angle(0.) {}

shape::shape(const shape &s, TopoDS_Shape shp)
    : _shape(shp), _surface_colour(s._surface_colour),
      _curve_colour(s._curve_colour), _u_origin(s._u_origin),
      _v_origin(s._v_origin), _u_repeat(s._u_repeat), _v_repeat(s._v_repeat),
      _scale_u(s._scale_u), _scale_v(s._scale_v),
      _auto_scale_size_on_u(s._auto_scale_size_on_u),
      _auto_scale_size_on_v(s._auto_scale_size_on_v),
      _txture_map_type(s._txture_map_type), _rotation_angle(s._rotation_angle) {
}

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
      _txture_map_type(o._txture_map_type), _rotation_angle(o._rotation_angle) {
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
  if (!o._shape.IsNull())
    o._shape.Free();
  return *this;
}

shape shape::copy(bool deep) const {
  try {
    BRepBuilderAPI_Copy _copy(_shape, deep);
    _copy.Build();

    if (!_copy.IsDone())
      throw std::runtime_error("Section operation failed");

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
  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
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
  } catch (Standard_Failure &err) {
    Bnd_Box aBox;
    aBox.Update(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    return aBox;
  }
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
  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
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
  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to translate object");
    }
    return 0;
  }
  return 1;
}

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
  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
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
  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
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
  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
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
  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
    if (msg != NULL && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to scale object");
    }
    return 0;
  }
  return 1;
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
  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
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
  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
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
  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
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

gp_Pln shape::find_plane(double tolerance) {
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
  } catch (Standard_Failure &err) {
    Handle_Standard_Failure e = Standard_Failure::Caught();
    const Standard_CString msg = e->GetMessageString();
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
                                             angle,Standard_True);
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
      const TColgp_Array1OfPnt &nodes = mesh->Nodes();
      Poly::ComputeNormals(mesh);

      if (hasSeam) {
        TColStd_Array1OfReal norms(1, mesh->Normals().Length());
        for (Standard_Integer i = 1; i <= mesh->NbNodes() * 3; i += 3) {
          gp_Dir dir(mesh->Normals().Value(i), mesh->Normals().Value(i + 1),
                     mesh->Normals().Value(i + 2));
          if (faceReversed)
            dir.Reverse();
          dir = quaternion.Multiply(dir);
          norms.SetValue(i, dir.X());
          norms.SetValue(i + 1, dir.Y());
          norms.SetValue(i + 2, dir.Z());
        }
        std::unordered_map<point3d_with_tolerance, int> uniquePointsOnFace;
        for (Standard_Integer j = 1; j <= mesh->NbNodes(); j++) {
          gp_Pnt p = nodes.Value(j);
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
          const TColgp_Array1OfPnt2d &UVNodes = mesh->UVNodes();
          TColgp_Array1OfPnt2d coords(1, UVNodes.Length());
          for (int i = UVNodes.Lower(); i <= UVNodes.Upper(); i++) {
            if (_txture_map_type == texture_cube) {
              gp_Dir dir(norms.Value((i * 3) + 1), norms.Value((i * 3) + 2),
                         norms.Value((i * 3) + 3));
              get_box_texture_coordinate(
                  nodes(i).Transformed(loc.Transformation()),
                  dir.Transformed(loc.Transformation()), _coord_p);
              d_coord.SetX(
                  (-_u_origin + (_u_repeat * _coord_p.X()) / _bnd_box_sz) /
                  _scale_u);
              d_coord.SetY(
                  (-_v_origin + (_v_repeat * _coord_p.Y()) / _bnd_box_sz) /
                  _scale_v);
            } else {
              d_coord = UVNodes(i);
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
            gp_Pnt p = nodes.Value(j + 1);
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
            gp_Pnt p = nodes.Value(j + 1);
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
          const TColgp_Array1OfPnt2d &UVNodes = mesh->UVNodes();
          TColgp_Array1OfPnt2d coords(1, UVNodes.Length());
          for (int i = UVNodes.Lower(); i <= UVNodes.Upper(); i++) {
            if (_txture_map_type == texture_cube) {
              gp_Dir dir(mesh->Normals().Value((i * 3) + 1),
                         mesh->Normals().Value((i * 3) + 2),
                         mesh->Normals().Value((i * 3) + 3));
              get_box_texture_coordinate(
                  nodes(i).Transformed(loc.Transformation()),
                  dir.Transformed(loc.Transformation()), _coord_p);
              d_coord.SetX(
                  (-_u_origin + (_u_repeat * _coord_p.X()) / _bnd_box_sz) /
                  _scale_u);
              d_coord.SetY(
                  (-_v_origin + (_v_repeat * _coord_p.Y()) / _bnd_box_sz) /
                  _scale_v);
            } else {
              d_coord = UVNodes(i);
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
            gp_Pnt p = nodes.Value(j + 1);
            Standard_Real px = p.X();
            Standard_Real py = p.Y();
            Standard_Real pz = p.Z();
            transform.Transforms(px, py, pz);
            gp_Dir dir(mesh->Normals().Value((j * 3) + 1),
                       mesh->Normals().Value((j * 3) + 2),
                       mesh->Normals().Value((j * 3) + 3));
            if (faceReversed)
              dir.Reverse();
            dir = quaternion.Multiply(dir);
            gp_Pnt2d coord = coords(j + 1);
            meshReceiver.append_node(faceId, gp_Pnt{px, py, pz},
                                     gp_Pnt{dir.X(), dir.Y(), dir.Z()}, coord);
          }
        } else {
          for (Standard_Integer j = 0; j < mesh->NbNodes(); j++) {
            gp_Pnt p = nodes.Value(j + 1);
            Standard_Real px = p.X();
            Standard_Real py = p.Y();
            Standard_Real pz = p.Z();
            transform.Transforms(px, py, pz);
            gp_Dir dir(mesh->Normals().Value((j * 3) + 1),
                       mesh->Normals().Value((j * 3) + 2),
                       mesh->Normals().Value((j * 3) + 3));
            if (faceReversed)
              dir.Reverse();
            dir = quaternion.Multiply(dir);
            meshReceiver.append_node(faceId, gp_Pnt{px, py, pz},
                                     gp_Pnt{dir.X(), dir.Y(), dir.Z()});
          }
        }
      }

      Standard_Integer t[3];
      const Poly_Array1OfTriangle &triangles = mesh->Triangles();

      for (Standard_Integer j = 1; j <= mesh->NbTriangles(); j++) {
        if (faceReversed)
          triangles(j).Get(t[2], t[1], t[0]);
        else
          triangles(j).Get(t[0], t[1], t[2]);
        int tri[3];
        tri[0] = t[0] - 1;
        tri[1] = t[1] - 1;
        tri[2] = t[2] - 1;
        meshReceiver.append_triangle(faceId, tri);
      }
    }

    meshReceiver.end();
    return 0;
  } catch (Standard_Failure &err) {
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
      return vertex(_shape);
    case TopAbs_EDGE:
      return edge(_shape);
    case TopAbs_WIRE:
      return wire(_shape);
    case TopAbs_FACE:
      return face(_shape);
    case TopAbs_SHELL:
      return shell(_shape);
    case TopAbs_SOLID:
      return solid(_shape);
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
    default:
      break;
    }
  }
  return boost::none;
}

std::string shape::shape_type() const {
  std::string type = "clue";
  switch (_shape.ShapeType()) {
  case TopAbs_COMPOUND:
    type = "compound";
    break;
  case TopAbs_COMPSOLID:
    type = "compound solid";
    break;
  case TopAbs_SOLID:
    type = "solid";
    break;
  case TopAbs_SHELL:
    type = "shell";
    break;
  case TopAbs_FACE:
    type = "face";
    break;
  case TopAbs_WIRE:
    type = "wire";
    break;
  case TopAbs_EDGE:
    type = "edge";
    break;
  case TopAbs_VERTEX:
    type = "vertex";
    break;
  case TopAbs_SHAPE:
    type = "shape";
    break;
  default:
    break;
  }

  return type;
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

} // namespace topo
} // namespace flywave
