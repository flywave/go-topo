#pragma once

#include <BRepBndLib.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <Bnd_Box.hxx>
#include <TopoDS_Shape.hxx>
#include <atomic>
#include <cmath>
#include <memory>
#include <mutex>

#include <boost/optional.hpp>

#include "vector.hh"

namespace flywave {
namespace topo {

class topo_bbox {
private:
  mutable std::mutex mutex_;
  Bnd_Box wrapped_;
  mutable std::atomic<bool> properties_valid_{false};
  mutable double xmin_, xmax_, ymin_, ymax_, zmin_, zmax_;
  mutable double xlen_, ylen_, zlen_;
  mutable topo_vector center_;
  mutable double diagonal_length_;

  void ensure_properties() const;

public:
  topo_bbox() = default;
  explicit topo_bbox(const Bnd_Box &bb) : wrapped_(bb) {}

  topo_bbox(double minx, double miny, double minz, double maxx, double maxy,
            double maxz)
      : wrapped_({minx, miny, minz}, {maxx, maxy, maxz}) {}

  topo_bbox(const topo_bbox &other);
  topo_bbox &operator=(const topo_bbox &other);

  topo_bbox(topo_bbox &&other) noexcept;
  topo_bbox &operator=(topo_bbox &&other) noexcept;

  double x_min() const {
    ensure_properties();
    return xmin_;
  }
  double x_max() const {
    ensure_properties();
    return xmax_;
  }
  double x_length() const {
    ensure_properties();
    return xlen_;
  }

  double y_min() const {
    ensure_properties();
    return ymin_;
  }
  double y_max() const {
    ensure_properties();
    return ymax_;
  }
  double y_length() const {
    ensure_properties();
    return ylen_;
  }

  double z_min() const {
    ensure_properties();
    return zmin_;
  }
  double z_max() const {
    ensure_properties();
    return zmax_;
  }
  double z_length() const {
    ensure_properties();
    return zlen_;
  }

  topo_vector min() const {
    ensure_properties();
    return {xmin_, ymin_, zmin_};
  }
  topo_vector max() const {
    ensure_properties();
    return {xmax_, ymax_, zmax_};
  }

  topo_vector center() const {
    ensure_properties();
    return center_;
  }
  double diagonal_length() const {
    ensure_properties();
    return diagonal_length_;
  }

  topo_bbox add(const topo_vector &obj, double tol = 1e-6) const;

  topo_bbox add(const topo_bbox &other, double tol = 1e-6) const;

  bool is_inside(const topo_bbox &other, double tol = 1e-6) const;

  topo_bbox enlarge(double tol = 1e-6) const;

  static boost::optional<topo_bbox> find_outside_box2d(const topo_bbox &bb1,
                                                       const topo_bbox &bb2,
                                                       double tol = 1e-6);

  static topo_bbox from_shape(const TopoDS_Shape &shape, double tol = 1e-6,
                              bool optimal = true);

  const Bnd_Box &get_value() const { return wrapped_; }
};
} // namespace topo
} // namespace flywave