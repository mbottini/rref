#include "row.h"

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

std::ostream &Row::write(std::ostream &os) const {
  os << "[ ";
  for (double elem : _data) {
    os << elem << " ";
  }
  os << "]";
  return os;
}

std::ostream &operator<<(std::ostream &os, const Row &r) { return r.write(os); }

template <typename T1, typename T2>
std::vector<std::pair<T1, T2>> zip(const std::vector<T1> &v1,
                                   const std::vector<T2> &v2) {
  std::vector<std::pair<T1, T2>> result_vec;
  auto it1 = v1.begin();
  auto it2 = v2.begin();
  for (; it1 != v1.end() && it2 != v2.end(); ++it1, ++it2) {
    result_vec.emplace_back(*it1, *it2);
  }
  return result_vec;
}
