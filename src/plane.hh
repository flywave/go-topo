#pragma once

#include <BRepBndLib.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <Bnd_Box.hxx>
#include <TopoDS_Shape.hxx>
#include <cmath>
#include <gp_Ax3.hxx>
#include <gp_Dir.hxx>
#include <gp_GTrsf.hxx>
#include <gp_Pln.hxx>
#include <gp_Pnt.hxx>
#include <gp_Trsf.hxx>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "location.hh"
#include "matrix.hh"
#include "vector.hh"

namespace flywave {
namespace topo {

class shape;

class topo_plane {
private:
  topo_vector _x_dir;
  topo_vector _y_dir;
  topo_vector _z_dir;
  topo_vector _origin;
  gp_Ax3 _lcs;
  topo_matrix _rG;
  topo_matrix _fG;

  static constexpr double _eq_tolerance_origin = 1e-6;
  static constexpr double _eq_tolerance_dot = 1e-6;

  void set_plane_dir(const topo_vector &xDir);

  void calc_transforms();

public:
  static topo_plane named(const std::string &stdName,
                          const topo_vector &origin = topo_vector(0, 0, 0));

  topo_plane(const topo_vector &origin, const topo_vector &xDir,
             const topo_vector &normal = topo_vector(0, 0, 1));
  topo_plane(gp_Pln pln);

  topo_plane(const topo_plane &) = default;
  topo_plane(topo_plane &&) noexcept = default;
  topo_plane &operator=(const topo_plane &) = default;
  topo_plane &operator=(topo_plane &&) noexcept = default;

  static topo_plane XY(const topo_vector &origin = topo_vector(0, 0, 0),
                       const topo_vector &xDir = topo_vector(1, 0, 0));

  static topo_plane YZ(const topo_vector &origin = topo_vector(0, 0, 0),
                       const topo_vector &xDir = topo_vector(0, 1, 0));

  static topo_plane ZX(const topo_vector &origin = topo_vector(0, 0, 0),
                       const topo_vector &xDir = topo_vector(0, 0, 1));

  static topo_plane XZ(const topo_vector &origin = topo_vector(0, 0, 0),
                       const topo_vector &xDir = topo_vector(1, 0, 0));

  static topo_plane YX(const topo_vector &origin = topo_vector(0, 0, 0),
                       const topo_vector &xDir = topo_vector(0, 1, 0));

  static topo_plane ZY(const topo_vector &origin = topo_vector(0, 0, 0),
                       const topo_vector &xDir = topo_vector(0, 0, 1));

  static topo_plane front(const topo_vector &origin = topo_vector(0, 0, 0),
                          const topo_vector &xDir = topo_vector(1, 0, 0));

  static topo_plane back(const topo_vector &origin = topo_vector(0, 0, 0),
                         const topo_vector &xDir = topo_vector(-1, 0, 0));

  static topo_plane left(const topo_vector &origin = topo_vector(0, 0, 0),
                         const topo_vector &xDir = topo_vector(0, 0, 1));

  static topo_plane right(const topo_vector &origin = topo_vector(0, 0, 0),
                          const topo_vector &xDir = topo_vector(0, 0, -1));

  static topo_plane top(const topo_vector &origin = topo_vector(0, 0, 0),
                        const topo_vector &xDir = topo_vector(1, 0, 0));

  static topo_plane bottom(const topo_vector &origin = topo_vector(0, 0, 0),
                           const topo_vector &xDir = topo_vector(1, 0, 0));

  operator gp_Pln() const { return gp_Pln(_lcs); }

  topo_vector origin() const { return _origin; }
  topo_vector x_dir() const { return _x_dir; }
  topo_vector y_dir() const { return _y_dir; }
  topo_vector z_dir() const { return _z_dir; }

  topo_vector to_world_coords(const topo_vector &v) const {
    return v.transform(_rG);
  }

  shape to_world_coords(const shape &v) const;

  topo_vector to_local_coords(const topo_vector &v) const {
    return v.transform(_fG);
  }

  topo_location location() const { return topo_location(*this); }

  shape to_local_coords(const shape &v) const;

  void set_origin(const topo_vector &newOrigin) {
    _origin = newOrigin;
    calc_transforms();
  }

  void set_origin2d(double x, double y) {
    _origin = to_world_coords(topo_vector(x, y, 0));
  }

  topo_plane rotated(const topo_vector &rotate = topo_vector(0, 0, 0)) const;

  std::vector<shape> mirror_in_plane(const std::vector<shape> &shapes,
                                     const std::string &axis = "X") const;

private:
  friend class workplane;
};

} // namespace topo
} // namespace flywave
