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
  gp_GTrsf wrapped;

  void _rotate(const gp_Ax1 &direction, double angle) {
    gp_Trsf newTrsf;
    newTrsf.SetRotation(direction, angle);
    wrapped.Multiply(gp_GTrsf(newTrsf));
  }

public:
  // Constructors
  topo_matrix() : wrapped() {} // Default identity matrix

  topo_matrix(const gp_GTrsf &trsf) : wrapped(trsf) {}

  explicit topo_matrix(const gp_Trsf &trsf) : wrapped(trsf) {}

  topo_matrix(const std::vector<std::vector<double>> &matrix) {
    // Validate matrix size
    if (matrix.size() != 3 && matrix.size() != 4) {
      throw std::runtime_error("topo_matrix must have 3 or 4 rows");
    }

    for (const auto &row : matrix) {
      if (row.size() != 4) {
        throw std::runtime_error("Each matrix row must have 4 elements");
      }
    }

    // Check last row if provided
    if (matrix.size() == 4) {
      const auto &lastRow = matrix[3];
      if (lastRow[0] != 0.0 || lastRow[1] != 0.0 || lastRow[2] != 0.0 ||
          lastRow[3] != 1.0) {
        throw std::runtime_error("Last row must be [0,0,0,1]");
      }
    }

    // Initialize as identity first
    wrapped = gp_GTrsf();

    // Set values from input matrix
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 4; ++j) {
        wrapped.SetValue(i + 1, j + 1, matrix[i][j]);
      }
    }
  }

  // Rotation methods
  void rotateX(double angle) { _rotate(gp::OX(), angle); }

  void rotateY(double angle) { _rotate(gp::OY(), angle); }

  void rotateZ(double angle) { _rotate(gp::OZ(), angle); }

  // topo_matrix operations
  topo_matrix inverse() const { return topo_matrix(wrapped.Inverted()); }

  topo_matrix multiply(const topo_matrix &other) const {
    return topo_matrix(wrapped.Multiplied(other.wrapped));
  }

  operator gp_GTrsf() const { return gp_GTrsf(wrapped); }

  // Accessors
  double get(int row, int col) const {
    if (row < 0 || row > 3 || col < 0 || col > 3) {
      throw std::out_of_range("topo_matrix indices must be between 0 and 3");
    }

    if (row < 3) {
      return wrapped.Value(row + 1, col + 1);
    } else {
      // Handle implied last row
      return (col == 3) ? 1.0 : 0.0;
    }
  }

  // Transposed list for export
  std::vector<double> transposedList() const {
    std::vector<double> result(16);

    // First 3 rows from the matrix
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 4; ++j) {
        result[j * 4 + i] = wrapped.Value(i + 1, j + 1);
      }
    }

    // Last row is always [0,0,0,1]
    result[12] = 0.0;
    result[13] = 0.0;
    result[14] = 0.0;
    result[15] = 1.0;

    return result;
  }

  // String representation
  std::string toString() const {
    std::ostringstream oss;
    auto tlist = transposedList();

    oss << "topo_matrix([";
    for (int i = 0; i < 4; ++i) {
      if (i > 0)
        oss << "        ";
      oss << "[" << tlist[i * 4] << ", " << tlist[i * 4 + 1] << ", "
          << tlist[i * 4 + 2] << ", " << tlist[i * 4 + 3] << "]";
      if (i < 3)
        oss << ",\n";
    }
    oss << "])";

    return oss.str();
  }

  // Serialization
  std::vector<std::vector<double>> __getstate__() const {
    std::vector<std::vector<double>> result(3, std::vector<double>(4));

    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 4; ++j) {
        result[i][j] = wrapped.Value(i + 1, j + 1);
      }
    }

    return result;
  }

  void __setstate__(const std::vector<std::vector<double>> &state) {
    if (state.size() != 3 || state[0].size() != 4) {
      throw std::runtime_error("Invalid matrix state");
    }

    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 4; ++j) {
        wrapped.SetValue(i + 1, j + 1, state[i][j]);
      }
    }
  }

  // Operator overload for matrix multiplication
  topo_matrix operator*(const topo_matrix &other) const {
    return multiply(other);
  }

  // Access to wrapped OCCT object
  const gp_GTrsf &getWrapped() const { return wrapped; }
  gp_GTrsf &getWrapped() { return wrapped; }
};

// Helper function to multiply matrix with vector
topo_vector operator*(const topo_matrix &m, const topo_vector &v) {
  // Convert vector to point (to include translation)
  gp_Pnt p = v.toPnt();
  p.Transform(m.getWrapped().Trsf());
  return topo_vector(p.X(), p.Y(), p.Z());
}
} // namespace topo
} // namespace flywave
