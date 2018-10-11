#include <iostream>
#include <vector>
#include <utility>

// zip is the same as the Python function.
template <typename T1, typename T2>
std::vector<std::pair<T1, T2>> zip(const std::vector<T1> &v1,
                                   const std::vector<T2> &v2);

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

int main()
{
    std::vector<double> v1 = {1, 2, 3, 9};
    std::vector<double> v2 = {2, -1, 1, 8};
    std::vector<double> v3 = {3, 0, -1, 3};

    Row r1(v1);
    Row r2(v2);
    Row r3(v3);

    std::vector<Row> r_v = {v1, v2, v3};

    Matrix m(r_v);

    std::cout << m.rref();

    return 0;
}