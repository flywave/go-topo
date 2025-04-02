// ShapeOperations.h
#pragma once

#include <cmath>
#include <gp_Dir.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>
#include <gp_XYZ.hxx>
#include <sstream>
#include <stdexcept>
#include <string>

namespace flywave {
namespace topo {

class topo_vector {
private:
  gp_Vec wrapped;

public:
  // Constructors
  topo_vector() : wrapped(0, 0, 0) {}

  topo_vector(double x, double y, double z = 0.0) : wrapped(x, y, z) {}

  topo_vector(const gp_Vec &vec) : wrapped(vec) {}

  topo_vector(const gp_Pnt &pnt) : wrapped(pnt.X(), pnt.Y(), pnt.Z()) {}

  topo_vector(const gp_Dir &dir) : wrapped(dir.X(), dir.Y(), dir.Z()) {}

  topo_vector(const gp_XYZ &xyz) : wrapped(xyz) {}

  topo_vector(const topo_vector &other) : wrapped(other.wrapped) {}

  // Properties
  double x() const { return wrapped.X(); }
  void setX(double value) { wrapped.SetX(value); }

  double y() const { return wrapped.Y(); }
  void setY(double value) { wrapped.SetY(value); }

  double z() const { return wrapped.Z(); }
  void setZ(double value) { wrapped.SetZ(value); }

  // Length properties
  double Length() const { return wrapped.Magnitude(); }
  double Magnitude() const { return wrapped.Magnitude(); }

  double Angle(const topo_vector &v) const { return wrapped.Angle(v.wrapped); }

  // Conversion methods
  std::tuple<double, double, double> toTuple() const {
    return std::make_tuple(x(), y(), z());
  }

  gp_Pnt toPnt() const { return gp_Pnt(wrapped.XYZ()); }
  gp_Dir toDir() const { return gp_Dir(wrapped.XYZ()); }
  gp_Vec toVec() const { return wrapped; }

  // topo_vector operations
  topo_vector cross(const topo_vector &v) const {
    return topo_vector(wrapped.Crossed(v.wrapped));
  }

  operator gp_Pnt() const { return gp_Pnt(x(), y(), z()); }
  operator gp_Vec() const { return gp_Vec(x(), y(), z()); }
  operator gp_Dir() const { return gp_Dir(x(), y(), z()); }

  double dot(const topo_vector &v) const { return wrapped.Dot(v.wrapped); }

  topo_vector sub(const topo_vector &v) const {
    return topo_vector(wrapped.Subtracted(v.wrapped));
  }

  topo_vector add(const topo_vector &v) const {
    return topo_vector(wrapped.Added(v.wrapped));
  }

  topo_vector multiply(double scale) const {
    return topo_vector(wrapped.Multiplied(scale));
  }

  topo_vector normalized() const {
    if (Length() == 0.0) {
      throw std::runtime_error("Cannot normalize zero vector");
    }
    return topo_vector(wrapped.Normalized());
  }

  // Geometric operations
  double getAngle(const topo_vector &v) const {
    return wrapped.Angle(v.wrapped);
  }

  double getSignedAngle(const topo_vector &v) const {
    gp_Vec ref(0, 0, -1);
    return wrapped.AngleWithRef(v.wrapped, ref);
  }

  topo_vector projectToLine(const topo_vector &line) const {
    double lineLength = line.Length();
    if (lineLength == 0.0) {
      throw std::runtime_error("Cannot project to zero-length line");
    }
    return line * (this->dot(line) / (lineLength * lineLength));
  }

  topo_vector projectToPlane(const class topo_plane &plane) const;

  // Operator overloads
  topo_vector operator-() const { return multiply(-1.0); }

  topo_vector operator+(const topo_vector &v) const { return add(v); }
  topo_vector operator-(const topo_vector &v) const { return sub(v); }
  topo_vector operator*(double scale) const { return multiply(scale); }
  topo_vector operator/(double denom) const { return multiply(1.0 / denom); }

  bool operator==(const topo_vector &other) const {
    return wrapped.IsEqual(other.wrapped, 1e-5, 1e-5);
  }

  bool operator!=(const topo_vector &other) const { return !(*this == other); }

  bool is_equal(const topo_vector &other, double tolerance) const {
    return wrapped.IsEqual(other.wrapped, tolerance, tolerance);
  }

  // String representation
  std::string toString() const {
    std::ostringstream oss;
    oss << "topo_vector: (" << x() << ", " << y() << ", " << z() << ")";
    return oss.str();
  }

  friend std::ostream &operator<<(std::ostream &os, const topo_vector &v) {
    os << v.toString();
    return os;
  }

  // Serialization
  std::tuple<double, double, double> __getstate__() const { return toTuple(); }

  void __setstate__(const std::tuple<double, double, double> &state) {
    wrapped.SetX(std::get<0>(state));
    wrapped.SetY(std::get<1>(state));
    wrapped.SetZ(std::get<2>(state));
  }

  // Transformation
  topo_vector transform(const class topo_matrix &T) const;
};

// Non-member operator for scalar multiplication
inline topo_vector operator*(double scale, const topo_vector &v) {
  return v.multiply(scale);
}
} // namespace topo
} // namespace flywave
