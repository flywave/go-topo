// ShapeOperations.h
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
  topo_vector xDir;
  topo_vector yDir;
  topo_vector zDir;
  topo_vector origin;
  gp_Ax3 lcs;
  topo_matrix rG;
  topo_matrix fG;

  static constexpr double _eq_tolerance_origin = 1e-6;
  static constexpr double _eq_tolerance_dot = 1e-6;

  void _setPlaneDir(const topo_vector &xDir) {
    this->xDir = xDir.normalized();
    this->yDir = zDir.cross(this->xDir).normalized();
    _calcTransforms();
  }

  void _calcTransforms() {
    gp_Trsf forwardT;
    gp_Trsf inverseT;

    gp_Ax3 global_coord_system;
    gp_Ax3 local_coord_system(origin.toPnt(), zDir.toDir(), xDir.toDir());

    forwardT.SetTransformation(global_coord_system, local_coord_system);
    fG = topo_matrix(forwardT);

    inverseT.SetTransformation(local_coord_system, global_coord_system);
    rG = topo_matrix(inverseT);

    lcs = local_coord_system;
  }

public:
  static topo_plane named(const std::string &stdName,
                          const topo_vector &origin = topo_vector(0, 0, 0)) {
    static const std::map<std::string, std::tuple<topo_vector, topo_vector>>
        namedPlanes = {
            {"XY", {topo_vector(1, 0, 0), topo_vector(0, 0, 1)}},
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

    auto [xDir, normal] = it->second;
    return topo_plane(origin, xDir, normal);
  }

  topo_plane(const topo_vector &origin, const topo_vector &xDir,
             const topo_vector &normal = topo_vector(0, 0, 1)) {
    zDir = normal;
    if (zDir.Length() == 0.0) {
      throw std::runtime_error("normal should be non null");
    }
    zDir = zDir.normalized();

    gp_Ax3 ax3(origin.toPnt(), normal.toDir());
    topo_vector defaultXDir(ax3.XDirection().X(), ax3.XDirection().Y(),
                            ax3.XDirection().Z());

    if (xDir.Length() == 0.0) {
      throw std::runtime_error("xDir should be non null");
    }

    this->origin = origin;
    _setPlaneDir(xDir);
  }

  operator gp_Pln() const { return gp_Pln(lcs); }

  topo_vector getOrigin() const { return origin; }
  topo_vector getXDir() const { return xDir; }
  topo_vector getYDir() const { return yDir; }
  topo_vector getZDir() const { return zDir; }

  topo_vector toWorldCoords(const topo_vector &v) const {
    return v.transform(rG);
  }

  shape toWorldCoords(const shape &v) const;

  topo_vector toLocalCoords(const topo_vector &v) const {
    return v.transform(fG);
  }

  // location
  topo_location location() const { return topo_location(*this); }

  // set_origin
  shape toLocalCoords(const shape &v) const;

  void setOrigin(const topo_vector &newOrigin) {
    origin = newOrigin;
    _calcTransforms();
  }

  void setOrigin2d(double x, double y) {
    origin = toWorldCoords(topo_vector(x, y, 0));
  }

  topo_plane rotated(const topo_vector &rotate = topo_vector(0, 0, 0)) const {
    topo_vector radians =
        topo_vector(rotate.x() * M_PI / 180.0, rotate.y() * M_PI / 180.0,
                    rotate.z() * M_PI / 180.0);

    gp_Trsf T1, T2, T3;
    T1.SetRotation(
        gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(xDir.x(), xDir.y(), xDir.z())),
        radians.x());
    T2.SetRotation(
        gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(yDir.x(), yDir.y(), yDir.z())),
        radians.y());
    T3.SetRotation(
        gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(zDir.x(), zDir.y(), zDir.z())),
        radians.z());

    gp_Trsf T = T1 * T2 * T3;
    topo_matrix m(T);

    topo_vector newXdir = xDir.transform(m);
    topo_vector newZdir = zDir.transform(m);

    return topo_plane(origin, newXdir, newZdir);
  }

  std::vector<shape> mirrorInPlane(const std::vector<shape> &shapes,
                                   const std::string &axis = "X") const;

  gp_Pln toPln() const { return gp_Pln(lcs); }

private:
  friend class workplane;
};

} // namespace topo
} // namespace flywave
