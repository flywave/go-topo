#include "bbox.hh"

namespace flywave {
namespace topo {

void topo_bbox::ensure_properties() const {
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

topo_bbox::topo_bbox(const topo_bbox &other) {
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

topo_bbox &topo_bbox::operator=(const topo_bbox &other) {
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

topo_bbox::topo_bbox(topo_bbox &&other) noexcept {
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

topo_bbox &topo_bbox::operator=(topo_bbox &&other) noexcept {
  if (this != &other) {
    std::lock_guard<std::mutex> lock(mutex_);
    std::lock_guard<std::mutex> lock_other(other.mutex_);
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
  return *this;
}

topo_bbox topo_bbox::add(const topo_vector &obj, double tol) const {
  Bnd_Box tmp;
  tmp.SetGap(tol);
  tmp.Add(wrapped_);
  tmp.Update(obj.x(), obj.y(), obj.z());
  return topo_bbox(tmp);
}

topo_bbox topo_bbox::add(const topo_bbox &other, double tol) const {
  Bnd_Box tmp;
  tmp.SetGap(tol);
  tmp.Add(wrapped_);
  tmp.Add(other.wrapped_);
  return topo_bbox(tmp);
}

bool topo_bbox::is_inside(const topo_bbox &other, double tol) const {
  ensure_properties();
  other.ensure_properties();
  return (other.xmin_ >= xmin_ - tol && other.ymin_ >= ymin_ - tol &&
          other.zmin_ >= zmin_ - tol && other.xmax_ <= xmax_ + tol &&
          other.ymax_ <= ymax_ + tol && other.zmax_ <= zmax_ + tol);
}

boost::optional<topo_bbox> topo_bbox::find_outside_box2d(const topo_bbox &bb1,
                                                         const topo_bbox &bb2,
                                                         double tol) {
  bb1.ensure_properties();
  bb2.ensure_properties();

  auto check_contains = [tol](const topo_bbox &outer, const topo_bbox &inner) {
    return (
        inner.xmin_ >= outer.xmin_ - tol && inner.xmax_ <= outer.xmax_ + tol &&
        inner.ymin_ >= outer.ymin_ - tol && inner.ymax_ <= outer.ymax_ + tol);
  };

  if (check_contains(bb1, bb2))
    return bb1;
  if (check_contains(bb2, bb1))
    return bb2;
  return boost::none;
}

topo_bbox topo_bbox::from_shape(const TopoDS_Shape &shape, double tol,
                                bool optimal) {
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

topo_bbox topo_bbox::enlarge(double tol) const {
  Bnd_Box tmp;
  tmp.SetGap(wrapped_.GetGap());
  tmp.Add(wrapped_);
  tmp.Enlarge(tol);
  return topo_bbox(tmp);
}

} // namespace topo
} // namespace flywave