// ShapeOperations.h
#pragma once

#include <gp.hxx>
#include <gp_Ax1.hxx>
#include <gp_GTrsf.hxx>
#include <gp_Trsf.hxx>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "vector.hh"

namespace flywave {
namespace topo {

class topo_matrix {
private:
  gp_GTrsf _value;

  void _rotate(const gp_Ax1 &direction, double angle);

public:
  // Constructors
  topo_matrix() : _value() {} // Default identity matrix

  topo_matrix(const gp_GTrsf &trsf) : _value(trsf) {}

  explicit topo_matrix(const gp_Trsf &trsf) : _value(gp_GTrsf(trsf)) {}

  topo_matrix(const topo_matrix &) = default;
  topo_matrix(topo_matrix &&) noexcept = default;
  topo_matrix &operator=(const topo_matrix &) = default;
  topo_matrix &operator=(topo_matrix &&) noexcept = default;

  topo_matrix(const std::vector<std::vector<double>> &matrix);

  // Rotation methods
  void rotate_x(double angle) { _rotate(gp::OX(), angle); }

  void rotate_y(double angle) { _rotate(gp::OY(), angle); }

  void rotate_z(double angle) { _rotate(gp::OZ(), angle); }

  // topo_matrix operations
  topo_matrix inverse() const { return topo_matrix(_value.Inverted()); }

  topo_matrix multiply(const topo_matrix &other) const {
    return topo_matrix(_value.Multiplied(other._value));
  }

  operator gp_GTrsf() const { return gp_GTrsf(_value); }

  // Accessors
  double get(int row, int col) const;

  // Transposed list for export
  std::vector<double> transposed_list() const;

  // String representation
  std::string to_string() const;

  // Serialization
  std::vector<std::vector<double>> to_vector() const {
    std::vector<std::vector<double>> result(3, std::vector<double>(4));

    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 4; ++j) {
        result[i][j] = _value.Value(i + 1, j + 1);
      }
    }

    return result;
  }

  // Operator overload for matrix multiplication
  topo_matrix operator*(const topo_matrix &other) const {
    return multiply(other);
  }

  // Access to wrapped OCCT object
  const gp_GTrsf &get_value() const { return _value; }
  gp_GTrsf &get_value() { return _value; }
};

topo_vector operator*(const topo_matrix &m, const topo_vector &v);

} // namespace topo
} // namespace flywave
