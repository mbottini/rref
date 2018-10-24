#include "row.h"
#include <iostream>

Row::Row(const std::vector<double> &orig) { _data = orig; }

size_t Row::size() const { return _data.size(); }

double Row::operator[](size_t index) const { return _data.at(index); }

Row Row::operator+(const Row &other) const {
  std::vector<double> result_vec;
  for (auto p : zip(this->_data, other._data)) {
    result_vec.push_back(p.first + p.second);
  }
  return result_vec;
}

Row &Row::operator+=(const Row &other) {
  *this = *this + other;
  return *this;
}

Row Row::operator-(const Row &r2) const { return *this + (-r2); }

Row &Row::operator-=(const Row &other) {
  *this = *this - other;
  return *this;
}

Row Row::operator*(double scalar) const {
  std::vector<double> result_vec;
  for (double elem : _data) {
    result_vec.push_back(elem * scalar);
  }
  return Row(result_vec);
}

Row &Row::operator*=(double scalar) {
  *this = *this * scalar;
  return *this;
}

Row Row::operator/(double scalar) const { return *this * (1 / scalar); }

Row &Row::operator/=(double scalar) {
  *this = *this / scalar;
  return *this;
}

Row Row::operator-() const {
  std::vector<double> result_vec;
  for (double elem : _data) {
    result_vec.push_back(-elem);
  }
  return Row(result_vec);
}

Row Row::operator>>(const Row &other) const {
  std::vector<double> result_vec = _data;
  result_vec.insert(result_vec.end(), other._data.begin(), other._data.end());
  return result_vec;
}

Row Row::remove_middle(size_t stop_left, size_t extra) const {
  std::vector<double> result_vec;
  for (int i = 0; i < stop_left; i++) {
    result_vec.push_back(_data[i]);
  }
  result_vec.push_back(_data[extra]);
  return Row(result_vec);
}

bool Row::no_solutions() const {
  bool all_zeros = true;
  for (auto it = _data.begin(); it != _data.end() - 1; ++it) {
    if (fabs(*it) >= DELTA) {
      all_zeros = false;
    }
  }
  return all_zeros && _data.back() != 0;
}

bool Row::is_zero() const {
  bool all_zeros = true;
  for (auto it = _data.begin(); it != _data.end() - 1; ++it) {
    if (fabs(*it) >= DELTA) {
      all_zeros = false;
    }
  }
  return all_zeros && _data.back() == 0;
}

Row Row::prettify() const {
  std::vector<double> result_row;
  for (double d : _data) {
    result_row.push_back(fabs(d) < DELTA ? 0 : d);
  }
  return Row(result_row);
}

std::ostream &Row::write(std::ostream &os) const {
  os << "[ ";
  for (double elem : _data) {
    os << elem << " ";
  }
  os << "]";
  return os;
}

std::ostream &operator<<(std::ostream &os, const Row &r) { return r.write(os); }
