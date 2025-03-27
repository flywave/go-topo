
#include "mesh_utils.hh"
#include "math_utils.hh"

#include <cassert>
#include <cmath>
#include <stdexcept>

namespace flywave {
namespace mesh_utils {
namespace {

[[maybe_unused]] TColStd_Array1OfReal createArray1OfReal(int count) {
  if (count > 0)
    return TColStd_Array1OfReal(1, count);
  else
    return TColStd_Array1OfReal();
}

} // namespace

double triangle_signed_volume(const gp_XYZ &p1, const gp_XYZ &p2,
                              const gp_XYZ &p3) {
  return p1.Dot(p2.Crossed(p3)) / 6.0f;
}

double triangle_area(const gp_XYZ &p1, const gp_XYZ &p2, const gp_XYZ &p3) {
  const double ax = p2.X() - p1.X();
  const double ay = p2.Y() - p1.Y();
  const double az = p2.Z() - p1.Z();
  const double bx = p3.X() - p1.X();
  const double by = p3.Y() - p1.Y();
  const double bz = p3.Z() - p1.Z();
  const double cx = ay * bz - az * by;
  const double cy = az * bx - ax * bz;
  const double cz = ax * by - ay * bx;
  return 0.5 * std::sqrt(cx * cx + cy * cy + cz * cz);
}

double
triangulation_volume(const ogg_handle<Poly_Triangulation> &triangulation) {
  if (!triangulation)
    return 0;

  double volume = 0;
  // TODO Parallelize computation
  for (const Poly_Triangle &tri : mesh_utils::triangles(triangulation)) {
    int v1, v2, v3;
    tri.Get(v1, v2, v3);
    volume += mesh_utils::triangle_signed_volume(
        triangulation->Node(v1).Coord(), triangulation->Node(v2).Coord(),
        triangulation->Node(v3).Coord());
  }

  return std::abs(volume);
}

double triangulation_area(const ogg_handle<Poly_Triangulation> &triangulation) {
  if (!triangulation)
    return 0;

  double area = 0;
  // TODO Parallelize computation
  for (const Poly_Triangle &tri : mesh_utils::triangles(triangulation)) {
    int v1, v2, v3;
    tri.Get(v1, v2, v3);
    area += mesh_utils::triangle_area(triangulation->Node(v1).Coord(),
                                      triangulation->Node(v2).Coord(),
                                      triangulation->Node(v3).Coord());
  }

  return area;
}

void set_node(const ogg_handle<Poly_Triangulation> &triangulation, int index,
              const gp_Pnt &pnt) {
#if OCC_VERSION_HEX >= 0x070600
  triangulation->SetNode(index, pnt);
#else
  triangulation->ChangeNode(index) = pnt;
#endif
}

void set_triangle(const ogg_handle<Poly_Triangulation> &triangulation,
                  int index, const Poly_Triangle &triangle) {
#if OCC_VERSION_HEX >= 0x070600
  triangulation->SetTriangle(index, triangle);
#else
  triangulation->ChangeTriangle(index) = triangle;
#endif
}

void set_normal(const ogg_handle<Poly_Triangulation> &triangulation, int index,
                const Poly_Triangulation_NormalType &n) {
#if OCC_VERSION_HEX >= 0x070600
  triangulation->SetNormal(index, n);
#else
  TShort_Array1OfShortReal &normals = triangulation->ChangeNormals();
  normals.ChangeValue(index * 3 - 2) = static_cast<float>(n.X());
  normals.ChangeValue(index * 3 - 1) = static_cast<float>(n.Y());
  normals.ChangeValue(index * 3) = static_cast<float>(n.Z());
#endif
}

void set_uv_node(const ogg_handle<Poly_Triangulation> &triangulation, int index,
                 double u, double v) {
#if OCC_VERSION_HEX >= 0x070600
  triangulation->SetUVNode(index, gp_Pnt2d{u, v});
#else
  triangulation->ChangeUVNode(index) = gp_Pnt2d{u, v};
#endif
}

void allocate_normals(const ogg_handle<Poly_Triangulation> &triangulation) {
#if OCC_VERSION_HEX >= 0x070600
  triangulation->AddNormals();
#else
  auto normalCoords =
      new TShort_HArray1OfShortReal(1, 3 * triangulation->NbNodes());
  triangulation->set_normals(normalCoords);
#endif
}

Poly_Triangulation_NormalType
normal(const ogg_handle<Poly_Triangulation> &triangulation, int index) {
  Poly_Triangulation_NormalType nvec;
#if OCC_VERSION_HEX >= 0x070600
  triangulation->Normal(index, nvec);
#else
  const TShort_Array1OfShortReal &normals = triangulation->Normals();
  nvec.SetX(normals.Value(index * 3 - 2));
  nvec.SetY(normals.Value(index * 3 - 1));
  nvec.SetZ(normals.Value(index * 3));
#endif
  return nvec;
}

const Poly_Array1OfTriangle &
triangles(const ogg_handle<Poly_Triangulation> &triangulation) {
#if OCC_VERSION_HEX < 0x070600
  return triangulation->Triangles();
#else
  // Note: Poly_Triangulation::Triangles() was deprecated starting from
  // OpenCascade v7.6.0
  return triangulation->InternalTriangles();
#endif
}

// Adapted from http://cs.smith.edu/~jorourke/Code/polyorient.C
mesh_utils::Orientation orientation(const adaptor_polyline2d &polyline) {
  const int pntCount = polyline.point_count();
  if (pntCount < 2)
    return Orientation::Unknown;

  gp_Pnt2d pntExtreme = polyline.point_at(0);
  int indexPntExtreme = 0;
  for (int i = 1; i < pntCount; ++i) {
    const gp_Pnt2d pnt = polyline.point_at(i);
    if (pnt.Y() < pntExtreme.Y() ||
        (math_utils::fuzzy_equal(pnt.Y(), pntExtreme.Y()) &&
         (pnt.X() > pntExtreme.X()))) {
      pntExtreme = pnt;
      indexPntExtreme = i;
    }
  }

  const gp_Pnt2d beforeExtremePnt =
      polyline.point_at((indexPntExtreme + (pntCount - 1)) % pntCount);
  const gp_Pnt2d afterExtremePnt =
      polyline.point_at((indexPntExtreme + 1) % pntCount);
  const gp_Pnt2d &a = beforeExtremePnt;
  const gp_Pnt2d &b = pntExtreme;
  const gp_Pnt2d &c = afterExtremePnt;
  const double triangle_area = a.X() * b.Y() - a.Y() * b.X() + a.Y() * c.X() -
                               a.X() * c.Y() + b.Y() * c.X() - c.X() * b.Y();

  auto fnQualifyArea = [](double area) {
    if (area > 0)
      return Orientation::CounterClockwise;
    else if (area < 0)
      return Orientation::Clockwise;
    else
      return Orientation::Unknown;
  };

  const Orientation orientation = fnQualifyArea(triangle_area);
  if (orientation != Orientation::Unknown) {
    return orientation;
  } else {
    double polylineArea = 0.;
    for (int i = 0; i < pntCount; ++i) {
      const gp_Pnt2d pntBefore =
          polyline.point_at((i + (pntCount - 1)) % pntCount);
      const gp_Pnt2d pntCurrent = polyline.point_at(i);
      const gp_Pnt2d pntAfter = polyline.point_at((i + 1) % pntCount);
      polylineArea += pntCurrent.X() * (pntAfter.Y() - pntBefore.Y());
    }

    return fnQualifyArea(polylineArea);
  }
}

gp_Vec direction_at(const adaptor_polyline3d &polyline, int i) {
  const int pntCount = polyline.point_count();
  if (pntCount > 1) {
    const gp_Pnt &pnt = polyline.point_at(i);
    const int indexLastPos = pntCount - 1;
    if (i < indexLastPos) {
      const gp_Pnt &nextPnt = polyline.point_at(i + 1);
      return gp_Vec(pnt, nextPnt);
    } else if (i == indexLastPos) {
      const gp_Pnt &prevPnt = polyline.point_at(i - 1);
      return gp_Vec(prevPnt, pnt);
    }
  }

  return gp_Vec();
}

polygon3d_builder::polygon3d_builder(int nodeCount, parameters_option option)
#if OCC_VERSION_HEX >= 0x070500
    : _polygon(
          new Poly_Polygon3D(nodeCount, option == parameters_option::With)),
      _ptr_nodes(&_polygon->ChangeNodes()),
      _ptr_params(option == parameters_option::With
                      ? &_polygon->ChangeParameters()
                      : nullptr)
#else
    : _nodes(1, nodeCount),
      _params(std::move(createArray1OfReal(
          option == parameters_option::With ? nodeCount : 0))),
      _ptr_nodes(&_nodes),
      _ptr_params(option == parameters_option::With ? &_params : nullptr)
#endif
{
  assert(_ptr_nodes);
  assert((option == parameters_option::None && !_ptr_params) ||
         (option == parameters_option::With && _ptr_params));
}

void polygon3d_builder::set_node(int i, const gp_Pnt &pnt) {
  if (_is_finalized)
    throw std::runtime_error(
        "Can't call set_node() on finalized polygon3d_builder object");

  _ptr_nodes->ChangeValue(i) = pnt;
}

void polygon3d_builder::set_parameter(int i, double u) {
  if (_is_finalized)
    throw std::runtime_error(
        "Can't call set_parameter() on finalized polygon3d_builder object");

  if (_ptr_params)
    _ptr_params->ChangeValue(i) = u;
}

void polygon3d_builder::finalize() {
  if (_is_finalized)
    return;

#if OCC_VERSION_HEX < 0x070500
  if (_ptr_params)
    _polygon = new Poly_Polygon3D(_nodes, _params);
  else
    _polygon = new Poly_Polygon3D(_nodes);
#endif
  _is_finalized = true;
}

ogg_handle<Poly_Polygon3D> polygon3d_builder::get() const {
  if (!_is_finalized)
    throw std::runtime_error(
        "Can't call get() on non finalized polygon3d_builder object");

  return _polygon;
}

} // namespace mesh_utils
} // namespace flywave