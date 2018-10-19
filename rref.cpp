#include "matrix.h"
#include "row.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

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

  std::cout << "Triangular form:\n";
  std::cout << m.triangular();

  std::cout << "Showing the steps for rref:\n";
  Matrix result = m.rref(&std::cout);

  std::cout << "Result:\n";
  std::cout << result << "\n";

  if(result.no_solutions()) {
    std::cout << "No solutions!\n";
  }

  else if(result.infinite_solutions()) {
    std::cout << "Infinite solutions!\n";
  }

  else {
    std::cout << "A single, unique solution exists.\n";
  }

  return 0;
}
