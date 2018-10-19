#ifndef MATRIX_H
#define MATRIX_H
#include "row.h"
class Matrix {
private:
  std::vector<Row> _rows;

public:
  Matrix(const std::vector<Row> &rows);
  void swap_rows(size_t i1, size_t i2);
  void rref_mut(std::ostream *os = 0);
  void triangular_mut(std::ostream *os = 0);
  Matrix rref(std::ostream *os = 0) const;
  Matrix triangular(std::ostream *os = 0) const;
  bool no_solutions() const;
  bool infinite_solutions() const;
  std::ostream &write(std::ostream &os) const;
};

std::ostream &operator<<(std::ostream &os, const Matrix &m);
#endif
