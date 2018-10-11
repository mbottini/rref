#include "matrix.h"
#include "row.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// zip is the same as the Python function.
template <typename T1, typename T2>
std::vector<std::pair<T1, T2>> zip(const std::vector<T1> &v1,
                                   const std::vector<T2> &v2);

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

Row Row::operator/(double scalar) { return *this * (1 / scalar); }

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

Matrix create_matrix(size_t rows, size_t cols) {
  std::stringstream ss;
  std::string input_line;
  double current_double;
  std::vector<double> parsed_line;
  std::vector<Row> result_vec;
  bool good_input;

  // Clearing std::cin before we do anything, as it's likely that someone used
  // the >> operator on cin before this function. The two don't mix :(
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  for (size_t i = 0; i < rows; i++) {
    do {
      parsed_line.clear();
      good_input = true;
      std::cout << "Input a line for row " << i + 1 << ": ";
      std::getline(std::cin, input_line);
      ss = std::stringstream(input_line);
      while (parsed_line.size() != cols && ss >> current_double) {
        parsed_line.push_back(current_double);
      }
      // If the stream ran out of chars, or there are leftover chars,
      // it's invalid input.
      if (ss.fail() || ss.rdbuf()->in_avail() > 0) {
        good_input = false;
        std::cout << "Invalid input. Try again.\n";
      }
    } while (!good_input);
    result_vec.push_back(parsed_line);
  }

  return Matrix(result_vec);
}

int main() {
  size_t rows, cols;

  std::cout << "Input the number of rows: ";
  std::cin >> rows;

  std::cout << "Input the number of columns: ";
  std::cin >> cols;

  Matrix m = create_matrix(rows, cols);

  std::cout << "Your matrix:\n";
  std::cout << m;

  std::cout << "Showing the steps:\n";
  Matrix result = m.rref(&std::cout);

  std::cout << "Result:\n";
  std::cout << result << "\n";

  return 0;
}