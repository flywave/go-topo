#pragma once

#include "ogg_handle.hh"

#include <Poly_Polygon3D.hxx>
#include <Poly_Triangulation.hxx>
#include <Standard_Version.hxx>

class gp_XYZ;

namespace flywave {
namespace mesh_utils {

double triangle_signed_volume(const gp_XYZ &p1, const gp_XYZ &p2,
                              const gp_XYZ &p3);
double triangle_area(const gp_XYZ &p1, const gp_XYZ &p2, const gp_XYZ &p3);

double
triangulation_volume(const ogg_handle<Poly_Triangulation> &triangulation);
double triangulation_area(const ogg_handle<Poly_Triangulation> &triangulation);

#if OCC_VERSION_HEX >= 0x070600
using Poly_Triangulation_NormalType = gp_Vec3f;
#else
using Poly_Triangulation_NormalType = gp_Vec;
#endif

void set_node(const ogg_handle<Poly_Triangulation> &triangulation, int index,
              const gp_Pnt &pnt);
void set_normal(const ogg_handle<Poly_Triangulation> &triangulation, int index,
                const Poly_Triangulation_NormalType &n);
void set_triangle(const ogg_handle<Poly_Triangulation> &triangulation,
                  int index, const Poly_Triangle &triangle);
void set_uv_node(const ogg_handle<Poly_Triangulation> &triangulation, int index,
                 double u, double v);

void allocate_normals(const ogg_handle<Poly_Triangulation> &triangulation);

Poly_Triangulation_NormalType
normal(const ogg_handle<Poly_Triangulation> &triangulation, int index);
const Poly_Array1OfTriangle &
triangles(const ogg_handle<Poly_Triangulation> &triangulation);

enum class Orientation { Unknown, Clockwise, CounterClockwise };

class adaptor_polyline2d {
public:
  virtual gp_Pnt2d point_at(int index) const = 0;
  virtual int point_count() const = 0;
  virtual bool empty() const { return this->point_count() <= 0; }
};

class adaptor_polyline3d {
public:
  virtual const gp_Pnt &point_at(int i) const = 0;
  virtual int point_count() const = 0;
  virtual int empty() const { return this->point_count() <= 0; }
};

Orientation orientation(const adaptor_polyline2d &polyline);
gp_Vec direction_at(const adaptor_polyline3d &polyline, int i);

class polygon3d_builder {
public:
  enum class parameters_option { None, With };

  polygon3d_builder(int nodeCount,
                    parameters_option option = parameters_option::None);

  void set_node(int i, const gp_Pnt &pnt);
  void set_parameter(int i, double u);
  void finalize();
  ogg_handle<Poly_Polygon3D> get() const;

private:
  bool _is_finalized = false;
  ogg_handle<Poly_Polygon3D> _polygon;
#if OCC_VERSION_HEX < 0x070500
  TColgp_Array1OfPnt _nodes;
  TColStd_Array1OfReal _params;
#endif
  TColgp_Array1OfPnt *_ptr_nodes = nullptr;
  TColStd_Array1OfReal *_ptr_params = nullptr;
};

} // namespace mesh_utils
} // namespace flywave