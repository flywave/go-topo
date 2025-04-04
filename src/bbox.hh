#pragma once

#include <BRepBndLib.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <Bnd_Box.hxx>
#include <TopoDS_Shape.hxx>
#include <atomic>
#include <cmath>
#include <memory>
#include <mutex>

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

  void ensure_properties() const {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!properties_valid_) {
      wrapped_.Get(xmin_, ymin_, zmin_, xmax_, ymax_, zmax_);
      xlen_ = xmax_ - xmin_;
      ylen_ = ymax_ - ymin_;
      zlen_ = zmax_ - zmin_;
      center_ = topo_vector((xmax_ + xmin_) / 2.0, (ymax_ + ymin_) / 2.0,
                            (zmax_ + zmin_) / 2.0);
      diagonal_length_ = std::sqrt(wrapped_.SquareExtent());
      properties_valid_ = true;
    }
  }

public:
  // Constructors
  topo_bbox() = default;
  explicit topo_bbox(const Bnd_Box &bb) : wrapped_(bb) {}

  topo_bbox(const topo_bbox &other) {
    std::lock_guard<std::mutex> lock(other.mutex_);
    wrapped_ = other.wrapped_;
    properties_valid_ = other.properties_valid_.load();
    if (properties_valid_) {
      xmin_ = other.xmin_;
      xmax_ = other.xmax_;
      ymin_ = other.ymin_;
      ymax_ = other.ymax_;
      zmin_ = other.zmin_;
      zmax_ = other.zmax_;
      xlen_ = other.xlen_;
      ylen_ = other.ylen_;
      zlen_ = other.zlen_;
      center_ = other.center_;
      diagonal_length_ = other.diagonal_length_;
    }
  }

  // 添加拷贝赋值运算符
  topo_bbox &operator=(const topo_bbox &other) {
    if (this != &other) {
      std::lock_guard<std::mutex> lock(mutex_);
      std::lock_guard<std::mutex> lock_other(other.mutex_);
      wrapped_ = other.wrapped_;
      properties_valid_ = other.properties_valid_.load();
      if (properties_valid_) {
        xmin_ = other.xmin_;
        xmax_ = other.xmax_;
        ymin_ = other.ymin_;
        ymax_ = other.ymax_;
        zmin_ = other.zmin_;
        zmax_ = other.zmax_;
        xlen_ = other.xlen_;
        ylen_ = other.ylen_;
        zlen_ = other.zlen_;
        center_ = other.center_;
        diagonal_length_ = other.diagonal_length_;
      }
    }
    return *this;
  }

  topo_bbox(topo_bbox &&other) noexcept {
    std::lock_guard<std::mutex> lock(other.mutex_);
    wrapped_ = std::move(other.wrapped_);
    properties_valid_ = other.properties_valid_.load();
    if (properties_valid_) {
      xmin_ = other.xmin_;
      xmax_ = other.xmax_;
      ymin_ = other.ymin_;
      ymax_ = other.ymax_;
      zmin_ = other.zmin_;
      zmax_ = other.zmax_;
      xlen_ = other.xlen_;
      ylen_ = other.ylen_;
      zlen_ = other.zlen_;
      center_ = other.center_;
      diagonal_length_ = other.diagonal_length_;
    }
  }

  // Properties with lazy evaluation
  double XMin() const {
    ensure_properties();
    return xmin_;
  }
  double XMax() const {
    ensure_properties();
    return xmax_;
  }
  double XLength() const {
    ensure_properties();
    return xlen_;
  }

  double YMin() const {
    ensure_properties();
    return ymin_;
  }
  double YMax() const {
    ensure_properties();
    return ymax_;
  }
  double YLength() const {
    ensure_properties();
    return ylen_;
  }

  double ZMin() const {
    ensure_properties();
    return zmin_;
  }
  double ZMax() const {
    ensure_properties();
    return zmax_;
  }
  double ZLength() const {
    ensure_properties();
    return zlen_;
  }

  topo_vector Min() const {
    ensure_properties();
    return {xmin_, ymin_, zmin_};
  }
  topo_vector Max() const {
    ensure_properties();
    return {xmax_, ymax_, zmax_};
  }
  topo_vector Center() const {
    ensure_properties();
    return center_;
  }
  double DiagonalLength() const {
    ensure_properties();
    return diagonal_length_;
  }

  // Improved bounding box operations with tolerance
  topo_bbox add(const topo_vector &obj, double tol = 1e-6) const {
    Bnd_Box tmp;
    tmp.SetGap(tol);
    tmp.Add(wrapped_);
    tmp.Update(obj.x(), obj.y(), obj.z());
    return topo_bbox(tmp);
  }

  topo_bbox add(const topo_bbox &other, double tol = 1e-6) const {
    Bnd_Box tmp;
    tmp.SetGap(tol);
    tmp.Add(wrapped_);
    tmp.Add(other.wrapped_);
    return topo_bbox(tmp);
  }

  // More robust comparison with tolerance
  bool isInside(const topo_bbox &other, double tol = 1e-6) const {
    ensure_properties();
    other.ensure_properties();
    return (other.xmin_ >= xmin_ - tol && other.ymin_ >= ymin_ - tol &&
            other.zmin_ >= zmin_ - tol && other.xmax_ <= xmax_ + tol &&
            other.ymax_ <= ymax_ + tol && other.zmax_ <= zmax_ + tol);
  }

  static boost::optional<topo_bbox> FindOutsideBox2D(const topo_bbox &bb1,
                                                     const topo_bbox &bb2,
                                                     double tol = 1e-6) {
    bb1.ensure_properties();
    bb2.ensure_properties();

    auto check_contains = [tol](const topo_bbox &outer,
                                const topo_bbox &inner) {
      return (inner.xmin_ >= outer.xmin_ - tol &&
              inner.xmax_ <= outer.xmax_ + tol &&
              inner.ymin_ >= outer.ymin_ - tol &&
              inner.ymax_ <= outer.ymax_ + tol);
    };

    if (check_contains(bb1, bb2))
      return bb1;
    if (check_contains(bb2, bb1))
      return bb2;
    return boost::none;
  }

  // Factory method with better error handling
  static topo_bbox FromTopoDS(const TopoDS_Shape &shape, double tol = 1e-6,
                              bool optimal = true) {
    if (shape.IsNull()) {
      throw std::invalid_argument("Null shape provided");
    }

    Bnd_Box bbox;
    bbox.SetGap(tol);

    try {
      if (optimal) {
        BRepBndLib::AddOptimal(shape, bbox);
      } else {
        BRepMesh_IncrementalMesh mesh(shape, tol, true);
        mesh.Perform();
        if (!mesh.IsDone()) {
          throw std::runtime_error("Mesh generation failed");
        }
        BRepBndLib::Add(shape, bbox, true);
      }
    } catch (const Standard_Failure &e) {
      throw std::runtime_error(e.GetMessageString());
    }

    return topo_bbox(bbox);
  }

  // Access to wrapped OCCT object
  const Bnd_Box &GetWrapped() const { return wrapped_; }
};
} // namespace topo
} // namespace flywave