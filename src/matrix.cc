#include "matrix.hh"

namespace flywave {
namespace topo {

void topo_matrix::_rotate(const gp_Ax1 &direction, double angle) {
  gp_Trsf newTrsf;
  newTrsf.SetRotation(direction, angle);
  _value.Multiply(gp_GTrsf(newTrsf));
}

topo_matrix::topo_matrix(const std::vector<std::vector<double>> &matrix) {
  if (matrix.size() != 3 && matrix.size() != 4) {
    throw std::runtime_error("topo_matrix must have 3 or 4 rows");
  }

  for (const auto &row : matrix) {
    if (row.size() != 4) {
      throw std::runtime_error("Each matrix row must have 4 elements");
    }
  }

  if (matrix.size() == 4) {
    const auto &lastRow = matrix[3];
    if (lastRow[0] != 0.0 || lastRow[1] != 0.0 || lastRow[2] != 0.0 ||
        lastRow[3] != 1.0) {
      throw std::runtime_error("Last row must be [0,0,0,1]");
    }
  }

  _value = gp_GTrsf();

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      _value.SetValue(i + 1, j + 1, matrix[i][j]);
    }
  }
}

double topo_matrix::get(int row, int col) const {
  if (row < 0 || row > 3 || col < 0 || col > 3) {
    throw std::out_of_range("topo_matrix indices must be between 0 and 3");
  }

  if (row < 3) {
    return _value.Value(row + 1, col + 1);
  } else {
    return (col == 3) ? 1.0 : 0.0;
  }
}

std::vector<double> topo_matrix::transposed_list() const {
  std::vector<double> result(16);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      result[j * 4 + i] = _value.Value(i + 1, j + 1);
    }
  }

  result[12] = 0.0;
  result[13] = 0.0;
  result[14] = 0.0;
  result[15] = 1.0;

  return result;
}

std::string topo_matrix::to_string() const {
  std::ostringstream oss;
  auto tlist = transposed_list();

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

topo_vector operator*(const topo_matrix &m, const topo_vector &v) {
  gp_Pnt p = v.to_pnt();
  p.Transform(m.get_value().Trsf());
  return topo_vector(p.X(), p.Y(), p.Z());
}

} // namespace topo
} // namespace flywave