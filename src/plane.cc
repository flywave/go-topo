#include "plane.hh"
#include "shape.hh"

namespace flywave {
namespace topo {

shape topo_plane::to_world_coords(const shape &v) const {
  return v.transformed(_rG);
}
shape topo_plane::to_local_coords(const shape &v) const {
  return v.transformed(_fG);
}

topo_plane topo_plane::XY(const topo_vector &origin, const topo_vector &xDir) {
  topo_plane plane(origin, xDir, topo_vector(0, 0, 1));
  return plane;
}

topo_plane topo_plane::YZ(const topo_vector &origin, const topo_vector &xDir) {
  topo_plane plane(origin, xDir, topo_vector(1, 0, 0));
  return plane;
}

topo_plane topo_plane::ZX(const topo_vector &origin, const topo_vector &xDir) {
  topo_plane plane(origin, xDir, topo_vector(0, 1, 0));
  return plane;
}

topo_plane topo_plane::XZ(const topo_vector &origin, const topo_vector &xDir) {
  topo_plane plane(origin, xDir, topo_vector(0, -1, 0));
  return plane;
}

topo_plane topo_plane::YX(const topo_vector &origin, const topo_vector &xDir) {
  topo_plane plane(origin, xDir, topo_vector(0, 0, -1));
  return plane;
}

topo_plane topo_plane::ZY(const topo_vector &origin, const topo_vector &xDir) {
  topo_plane plane(origin, xDir, topo_vector(-1, 0, 0));
  return plane;
}

topo_plane topo_plane::front(const topo_vector &origin,
                             const topo_vector &xDir) {
  topo_plane plane(origin, xDir, topo_vector(1, 0, 0));
  return plane;
}

topo_plane topo_plane::back(const topo_vector &origin,
                            const topo_vector &xDir) {
  topo_plane plane(origin, xDir, topo_vector(-1, 0, 0));
  return plane;
}

topo_plane topo_plane::left(const topo_vector &origin,
                            const topo_vector &xDir) {
  topo_plane plane(origin, xDir, topo_vector(0, 0, 1));
  return plane;
}

topo_plane topo_plane::right(const topo_vector &origin,
                             const topo_vector &xDir) {
  topo_plane plane(origin, xDir, topo_vector(0, 0, -1));
  return plane;
}

topo_plane topo_plane::top(const topo_vector &origin, const topo_vector &xDir) {
  topo_plane plane(origin, xDir, topo_vector(1, 0, 0));
  return plane;
}

topo_plane topo_plane::bottom(const topo_vector &origin,
                              const topo_vector &xDir) {
  topo_plane plane(origin, xDir, topo_vector(1, 0, 0));
  return plane;
}

topo_plane::topo_plane(gp_Pln pln) {
  _origin =
      topo_vector(pln.Location().X(), pln.Location().Y(), pln.Location().Z());
  _x_dir = topo_vector(pln.XAxis().Direction().X(), pln.XAxis().Direction().Y(),
                       pln.XAxis().Direction().Z());
  _y_dir = topo_vector(pln.YAxis().Direction().X(), pln.YAxis().Direction().Y(),
                       pln.YAxis().Direction().Z());
  _z_dir = topo_vector(pln.Axis().Direction().X(), pln.Axis().Direction().Y(),
                       pln.Axis().Direction().Z());
  calc_transforms();
}

void topo_plane::set_plane_dir(const topo_vector &xDir) {
  this->_x_dir = xDir.normalized();
  this->_y_dir = _z_dir.cross(this->_x_dir).normalized();
  calc_transforms();
}

void topo_plane::calc_transforms() {
  gp_Trsf forwardT;
  gp_Trsf inverseT;

  gp_Ax3 global_coord_system;
  gp_Ax3 local_coord_system(_origin.to_pnt(), _z_dir.to_dir(), _x_dir.to_dir());

  forwardT.SetTransformation(global_coord_system, local_coord_system);
  _fG = topo_matrix(forwardT);

  inverseT.SetTransformation(local_coord_system, global_coord_system);
  _rG = topo_matrix(inverseT);

  _lcs = local_coord_system;
}

std::vector<shape> topo_plane::mirror_in_plane(const std::vector<shape> &shapes,
                                               const std::string &axis) const {
  gp_Ax3 localCoordSystem(_origin.to_pnt(), _z_dir, _x_dir);

  gp_Trsf transformation;

  if (axis == "X") {
    transformation.SetMirror(
        gp_Ax1(_origin.to_pnt(), localCoordSystem.XDirection()));
  } else if (axis == "Y") {
    transformation.SetMirror(
        gp_Ax1(_origin.to_pnt(), localCoordSystem.YDirection()));
  } else {
    throw std::invalid_argument(
        "Unsupported mirror axis. Only 'X' and 'Y' are supported.");
  }

  std::vector<shape> mirroredShapes;
  for (const auto &s : shapes) {
    shape mirrored = s.transformed(topo_matrix(transformation));
    mirroredShapes.push_back(mirrored);
  }

  return mirroredShapes;
}

topo_plane topo_plane::named(const std::string &stdName,
                             const topo_vector &origin) {
  static const std::map<std::string, std::tuple<topo_vector, topo_vector>>
      namedPlanes = {{"XY", {topo_vector(1, 0, 0), topo_vector(0, 0, 1)}},
                     {"YZ", {topo_vector(0, 1, 0), topo_vector(1, 0, 0)}},
                     {"ZX", {topo_vector(0, 0, 1), topo_vector(0, 1, 0)}},
                     {"XZ", {topo_vector(1, 0, 0), topo_vector(0, -1, 0)}},
                     {"YX", {topo_vector(0, 1, 0), topo_vector(0, 0, -1)}},
                     {"ZY", {topo_vector(0, 0, 1), topo_vector(-1, 0, 0)}},
                     {"front", {topo_vector(1, 0, 0), topo_vector(0, 0, 1)}},
                     {"back", {topo_vector(-1, 0, 0), topo_vector(0, 0, -1)}},
                     {"left", {topo_vector(0, 0, 1), topo_vector(-1, 0, 0)}},
                     {"right", {topo_vector(0, 0, -1), topo_vector(1, 0, 0)}},
                     {"top", {topo_vector(1, 0, 0), topo_vector(0, 1, 0)}},
                     {"bottom", {topo_vector(1, 0, 0), topo_vector(0, -1, 0)}}};

  auto it = namedPlanes.find(stdName);
  if (it == namedPlanes.end()) {
    throw std::runtime_error("Unsupported plane name");
  }

  auto tp = it->second;
  return topo_plane(origin, std::get<0>(tp), std::get<1>(tp));
}

topo_plane::topo_plane(const topo_vector &origin, const topo_vector &xDir,
                       const topo_vector &normal) {
  _z_dir = normal;
  if (_z_dir.length() == 0.0) {
    throw std::runtime_error("normal should be non null");
  }
  _z_dir = _z_dir.normalized();

  gp_Ax3 ax3(origin.to_pnt(), normal.to_dir());
  topo_vector defaultXDir(ax3.XDirection().X(), ax3.XDirection().Y(),
                          ax3.XDirection().Z());

  if (xDir.length() == 0.0) {
    throw std::runtime_error("xDir should be non null");
  }

  this->_origin = origin;
  set_plane_dir(xDir);
}

topo_plane topo_plane::rotated(const topo_vector &rotate) const {
  topo_vector radians =
      topo_vector(rotate.x() * M_PI / 180.0, rotate.y() * M_PI / 180.0,
                  rotate.z() * M_PI / 180.0);

  gp_Trsf T1, T2, T3;
  T1.SetRotation(
      gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(_x_dir.x(), _x_dir.y(), _x_dir.z())),
      radians.x());
  T2.SetRotation(
      gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(_y_dir.x(), _y_dir.y(), _y_dir.z())),
      radians.y());
  T3.SetRotation(
      gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(_z_dir.x(), _z_dir.y(), _z_dir.z())),
      radians.z());

  gp_Trsf T = T1 * T2 * T3;
  topo_matrix m(T);

  topo_vector newXdir = _x_dir.transform(m);
  topo_vector newZdir = _x_dir.transform(m);

  return topo_plane(_origin, newXdir, newZdir);
}

} // namespace topo
} // namespace flywave
