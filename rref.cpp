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

    friend Row operator*(const Row &orig, double scalar)
    {
        std::vector<double> result_vec;
        for (double elem : orig._data)
        {
            result_vec.push_back(elem * scalar);
        }
        return Row(result_vec);
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

    friend Row operator+(const Row &r1, const Row &r2)
    {
        std::vector<double> result_vec;
        for (auto p : zip(r1._data, r2._data))
        {
            result_vec.push_back(p.first + p.second);
        }
        return result_vec;
    }

    friend Row operator-(const Row &r1, const Row &r2)
    {
        return r1 + (-r2);
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
    std::vector<double> v1 = {1, 2, 3};
    std::vector<double> v2 = {2, 3, 4};
    Row r1(v1);
    Row r2(v2);

    std::cout << r1 + r2 << "\n";
    std::cout << r1 - r2 << "\n";
    std::cout << r1 * 3 << "\n";
    std::cout << -r1 << "\n";

    return 0;
}