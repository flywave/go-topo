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
#include <array>

namespace flywave {
namespace topo {

class topo_vector {
private:
  gp_Vec _value;

public:
  topo_vector() : _value(0, 0, 0) {}

  topo_vector(double x, double y, double z = 0.0) : _value(x, y, z) {}

  topo_vector(std::array<double, 3> vec) : _value(vec[0], vec[1], vec[2]) {}

  topo_vector(const gp_Vec &vec) : _value(vec) {}

  topo_vector(const gp_Pnt &pnt) : _value(pnt.X(), pnt.Y(), pnt.Z()) {}

  topo_vector(const gp_Dir &dir) : _value(dir.X(), dir.Y(), dir.Z()) {}

  topo_vector(const gp_XYZ &xyz) : _value(xyz) {}

  topo_vector(const topo_vector &) = default;
  topo_vector(topo_vector &&) noexcept = default;
  topo_vector &operator=(const topo_vector &) = default;
  topo_vector &operator=(topo_vector &&) noexcept = default;

  double x() const { return _value.X(); }
  void set_x(double value) { _value.SetX(value); }

  double y() const { return _value.Y(); }
  void set_y(double value) { _value.SetY(value); }

  double z() const { return _value.Z(); }
  void set_z(double value) { _value.SetZ(value); }

  double length() const { return _value.Magnitude(); }
  double magnitude() const { return std::abs(_value.Magnitude()); }

  double angle(const topo_vector &v) const { return _value.Angle(v._value); }

  std::tuple<double, double, double> to_tuple() const {
    return std::make_tuple(x(), y(), z());
  }

  gp_Pnt to_pnt() const { return gp_Pnt(_value.XYZ()); }
  gp_Dir to_dir() const { return gp_Dir(_value.XYZ()); }
  gp_Vec to_vec() const { return _value; }
  gp_XYZ to_xyz() const { return _value.XYZ(); }

  topo_vector cross(const topo_vector &v) const {
    return topo_vector(_value.Crossed(v._value));
  }

  operator gp_Pnt() const { return gp_Pnt(x(), y(), z()); }
  operator gp_Vec() const { return gp_Vec(x(), y(), z()); }
  operator gp_Dir() const { return gp_Dir(x(), y(), z()); }
  operator gp_XYZ() const { return gp_XYZ(x(), y(), z()); }
  operator std::array<double, 3>() const { return {x(), y(), z()}; }

  double dot(const topo_vector &v) const { return _value.Dot(v._value); }

  topo_vector sub(const topo_vector &v) const {
    return topo_vector(_value.Subtracted(v._value));
  }

  topo_vector add(const topo_vector &v) const {
    return topo_vector(_value.Added(v._value));
  }

  topo_vector multiply(double scale) const {
    return topo_vector(_value.Multiplied(scale));
  }

  topo_vector normalized() const {
    if (length() == 0.0) {
      throw std::runtime_error("Cannot normalize zero vector");
    }
    return topo_vector(_value.Normalized());
  }

  double get_angle(const topo_vector &v) const {
    return _value.Angle(v._value);
  }

  double get_signed_angle(const topo_vector &v) const {
    gp_Vec ref(0, 0, -1);
    return _value.AngleWithRef(v._value, ref);
  }

  topo_vector project_to_line(const topo_vector &line) const {
    double lineLength = line.length();
    if (lineLength == 0.0) {
      throw std::runtime_error("Cannot project to zero-length line");
    }
    return line * (this->dot(line) / (lineLength * lineLength));
  }

  topo_vector project_to_plane(const class topo_plane &plane) const;

  topo_vector operator-() const { return multiply(-1.0); }

  topo_vector operator+(const topo_vector &v) const { return add(v); }
  topo_vector operator-(const topo_vector &v) const { return sub(v); }
  topo_vector operator*(double scale) const { return multiply(scale); }
  topo_vector operator/(double denom) const { return multiply(1.0 / denom); }

  bool operator==(const topo_vector &other) const {
    return _value.IsEqual(other._value, 1e-5, 1e-5);
  }

  bool operator!=(const topo_vector &other) const { return !(*this == other); }

  bool is_equal(const topo_vector &other, double tolerance) const {
    return _value.IsEqual(other._value, tolerance, tolerance);
  }

  std::string to_string() const {
    std::ostringstream oss;
    oss << "topo_vector: (" << x() << ", " << y() << ", " << z() << ")";
    return oss.str();
  }

  friend std::ostream &operator<<(std::ostream &os, const topo_vector &v) {
    os << v.to_string();
    return os;
  }

  topo_vector transform(const class topo_matrix &T) const;
};

inline topo_vector operator*(double scale, const topo_vector &v) {
  return v.multiply(scale);
}
} // namespace topo
} // namespace flywave
