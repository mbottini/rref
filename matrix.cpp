#include "matrix.h"
// Just a wrapper around a vector of Rows.
// Contains an rref operation for solving systems of equations.
Matrix::Matrix(const std::vector<Row> &rows) { _rows = rows; }

// Modifies the matrix!
void Matrix::swap_rows(size_t i1, size_t i2) {
  std::swap(_rows[i1], _rows[i2]);
}

// Modifies the matrix!
void Matrix::rref_mut(std::ostream *os) {
  bool has_index;
  for (size_t i = 0; i < _rows[0].size() - 1; i++) {
    // If the current row has a 0 in the current column, we have to swap
    // it with another row that does have that index.
    if (_rows[i][i] == 0) {
      has_index = false;
      for (size_t j = i + 1; j < _rows.size(); j++) {
        if (_rows[j][i] != 0) {
          swap_rows(i, j);
          has_index = true;
          break;
        }
      }
      // If we can't find the index, skip this column.
      if (!has_index) {
        continue;
      }
    }

    // Ensure that there's a 1 in that index.
    _rows[i] /= _rows[i][i];

    // Now we eliminate that column from all of the other rows.
    for (size_t j = i + 1; j < _rows.size(); j++) {
      _rows[j] -= _rows[i] * _rows[j][i];
    }

    for (size_t j = 0; j < i; j++) {
      _rows[j] -= _rows[i] * _rows[j][i];
    }

    if (os) {
      *os << *this << "\n";
    }
  }
}

Matrix Matrix::rref(std::ostream *os) const {
  Matrix result = *this;
  result.rref_mut(os);
  return result;
}

std::ostream &Matrix::write(std::ostream &os) const {
  for (auto v : _rows) {
    os << v << "\n";
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, const Matrix &m) {
  return m.write(os);
}
