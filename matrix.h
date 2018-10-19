#ifndef MATRIX_H
#define MATRIX_H
#include "row.h"

// Just a wrapper around a vector of Rows.
// Contains an rref operation for solving systems of equations.

class Matrix {
private:
  std::vector<Row> _rows;

public:
  Matrix(const std::vector<Row> &rows);
  void swap_rows(size_t i1, size_t i2);
  void rref_mut(std::ostream *os = 0);
  Matrix rref(std::ostream *os = 0) const;
  void triangular_mut(std::ostream *os = 0);
  Matrix triangular(std::ostream *os = 0) const;
  bool no_solutions() const;
  bool infinite_solutions() const;
  size_t num_variables() const;
  size_t num_nonzero_rows() const;
  std::ostream &write(std::ostream &os) const;
};

std::ostream &operator<<(std::ostream &os, const Matrix &m);
#endif
