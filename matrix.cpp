#include "matrix.h"

Matrix::Matrix(const std::vector<Row> &rows) { _rows = rows; }

// Modifies the matrix!
void Matrix::swap_rows(size_t i1, size_t i2) {
  std::swap(_rows[i1], _rows[i2]);
}

// Modifies the matrix!
// Note the pointer to an ostream. If you call this function with a reference
// to an ostream, it'll print each step of the rref process for you.
void Matrix::rref_mut(std::ostream *os) {
  bool has_index;
  for (size_t i = 0; i < _rows[0].size() - 1 && i < _rows.size(); i++) {
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

void Matrix::triangular_mut(std::ostream *os) {
  bool has_index;
  for (size_t i = 0; i < _rows[0].size() - 1 && i < _rows.size(); i++) {
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

    double factor = _rows[i][i];

    // Now we eliminate that column from all of the other rows.
    for (size_t j = i + 1; j < _rows.size(); j++) {
      _rows[j] -= _rows[i] * _rows[j][i] / factor;
    }

    if (os) {
      *os << *this << "\n";
    }
  }
}

// Non-mutable version of the above. Creates a new matrix and performs
// the mutable rref on that.
Matrix Matrix::rref(std::ostream *os) const {
  Matrix result = *this;
  result.rref_mut(os);
  return result;
}

Matrix Matrix::triangular(std::ostream *os) const {
  Matrix result = *this;
  result.triangular_mut(os);
  return result;
}

bool Matrix::no_solutions() const {
  for (auto &row : _rows) {
    if (row.no_solutions()) {
      return true;
    }
  }
  return false;
}

bool Matrix::infinite_solutions() const {
  return num_nonzero_rows() - num_variables() > 0;
}

size_t Matrix::num_variables() const {
  size_t num_columns = _rows[0].size();
  size_t num_vars = 0;
  for (int i = 0; i < num_columns - 1; i++) {
    for (auto &row : _rows) {
      if (fabs(row[i]) > DELTA) {
        num_vars++;
        break;
      }
    }
  }
  return num_vars;
}

size_t Matrix::num_nonzero_rows() const {
  size_t nonzero_rows = 0;
  for (auto &row : _rows) {
    if (!row.is_zero()) {
      nonzero_rows++;
    }
  }
  return nonzero_rows;
}

size_t Matrix::num_rows() const { return _rows.size(); }

size_t Matrix::num_cols() const { return _rows[0].size(); }

Matrix Matrix::operator>>(const Matrix &other) const {
  std::vector<Row> result_vec;
  for (auto const &pair : zip(_rows, other._rows)) {
    result_vec.push_back(pair.first >> pair.second);
  }
  return result_vec;
}

Matrix Matrix::remove_middle(size_t stop_left, size_t extra) const {
  std::vector<Row> result_vec;
  for (auto v : _rows) {
    result_vec.push_back(v.remove_middle(stop_left, extra));
  }
  return result_vec;
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
