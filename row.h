#ifndef ROW_H
#define ROW_H
#include <ostream>
#include <vector>
class Row {
private:
  std::vector<double> _data;

public:
  Row(const std::vector<double> &orig);

  size_t size() const;

  double operator[](size_t index) const;

  Row operator+(const Row &other) const;
  Row &operator+=(const Row &other);
  Row operator-(const Row &r2) const;
  Row &operator-=(const Row &other);
  Row operator*(double scalar) const;
  Row &operator*=(double scalar);
  Row operator/(double scalar) const;
  Row &operator/=(double scalar);
  Row operator-() const;
  std::ostream &write(std::ostream &os) const;
};

std::ostream &operator<<(std::ostream &os, const Row &r);
#endif