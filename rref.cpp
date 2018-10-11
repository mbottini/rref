#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <string>
#include <limits>

// zip is the same as the Python function.
template <typename T1, typename T2>
std::vector<std::pair<T1, T2>> zip(const std::vector<T1> &v1,
                                   const std::vector<T2> &v2);

// Literally just a wrapper around a vector, with arithmetic operations.
class Row
{
  private:
    std::vector<double> _data;

  public:
    Row(const std::vector<double> &orig)
    {
        _data = orig;
    }

    size_t size() const
    {
        return _data.size();
    }

    double operator[](size_t index) const
    {
        return _data.at(index);
    }

    friend Row operator+(const Row &r1, const Row &r2)
    {
        std::vector<double> result_vec;
        for (auto p : zip(r1._data, r2._data))
        {
            result_vec.push_back(p.first + p.second);
        }
        return result_vec;
    }

    Row &operator+=(const Row &other)
    {
        *this = *this + other;
        return *this;
    }

    friend Row operator-(const Row &r1, const Row &r2)
    {
        return r1 + (-r2);
    }

    Row &operator-=(const Row &other)
    {
        *this = *this - other;
        return *this;
    }

    friend Row operator*(const Row &orig, double scalar)
    {
        std::vector<double> result_vec;
        for (double elem : orig._data)
        {
            result_vec.push_back(elem * scalar);
        }
        return Row(result_vec);
    }

    Row &operator*=(double scalar)
    {
        *this = *this * scalar;
        return *this;
    }

    friend Row operator/(const Row &orig, double scalar)
    {
        return orig * (1 / scalar);
    }

    Row &operator/=(double scalar)
    {
        *this = *this / scalar;
        return *this;
    }

    friend Row operator-(const Row &orig)
    {
        std::vector<double> result_vec;
        for (double elem : orig._data)
        {
            result_vec.push_back(-elem);
        }
        return Row(result_vec);
    }

    friend std::ostream &operator<<(std::ostream &os, const Row &r)
    {
        os << "[ ";
        for (double elem : r._data)
        {
            os << elem << " ";
        }
        os << "]";
        return os;
    }
};

// Just a wrapper around a vector of Rows.
// Contains an rref operation for solving systems of equations.
class Matrix
{
  private:
    std::vector<Row> _rows;

  public:
    Matrix(const std::vector<Row> &rows)
    {
        _rows = rows;
    }

    // Modifies the matrix!
    void swap_rows(size_t i1, size_t i2)
    {
        std::swap(_rows[i1], _rows[i2]);
    }

    // Modifies the matrix!
    void rref_mut(std::ostream *os = 0)
    {
        bool has_index;
        for (size_t i = 0; i < _rows[0].size() - 1; i++)
        {
            has_index = true;
            // If the current row has a 0 in the current column, we have to swap
            // it with another row that does have that index.
            if (_rows[i][i] == 0)
            {
                has_index = false;
                for (size_t j = i + 1; j < _rows.size(); j++)
                {
                    if (_rows[j][i] != 0)
                    {
                        swap_rows(i, j);
                        has_index = true;
                        break;
                    }
                }
                // If we can't find the index, skip this column.
                if (!has_index)
                {
                    continue;
                }
            }

            // Ensure that there's a 1 in that index.
            _rows[i] /= _rows[i][i];

            // Now we eliminate that column from all of the other rows.
            for (size_t j = i + 1; j < _rows.size(); j++)
            {
                _rows[j] -= _rows[i] * _rows[j][i];
            }

            for (size_t j = 0; j < i; j++)
            {
                _rows[j] -= _rows[i] * _rows[j][i];
            }

            if (os)
            {
                *os << *this << "\n";
            }
        }
    }

    Matrix rref(std::ostream *os = 0) const
    {
        Matrix result = *this;
        result.rref_mut(os);
        return result;
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &m)
    {
        for (auto v : m._rows)
        {
            os << v << "\n";
        }
        return os;
    }
};

template <typename T1, typename T2>
std::vector<std::pair<T1, T2>> zip(const std::vector<T1> &v1,
                                   const std::vector<T2> &v2)
{
    std::vector<std::pair<T1, T2>> result_vec;
    for (auto it1 = v1.begin(), it2 = v2.begin();
         it1 != v1.end() && it2 != v2.end();
         ++it1, ++it2)
    {
        result_vec.emplace_back(*it1, *it2);
    }
    return result_vec;
}

Matrix create_matrix(size_t rows, size_t cols)
{
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

    for (size_t i = 0; i < rows; i++)
    {
        do
        {
            parsed_line.clear();
            good_input = true;
            std::cout << "Input a line for row " << i + 1 << ": ";
            std::getline(std::cin, input_line);
            ss = std::stringstream(input_line);
            while (parsed_line.size() != cols && ss >> current_double)
            {
                parsed_line.push_back(current_double);
            }
            // If the stream ran out of chars, or there are leftover chars,
            // it's invalid input.
            if (ss.fail() || ss.rdbuf()->in_avail() > 0)
            {
                good_input = false;
                std::cout << "Invalid input. Try again.\n";
            }
        } while (!good_input);
        result_vec.push_back(parsed_line);
    }

    return Matrix(result_vec);
}

int main()
{
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