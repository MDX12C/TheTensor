#include <iostream>
#include <memory>

#include "basic.hpp"
#include "vector.hpp"

int main() {
  auto a = linalg::Vector<int>::create(
      10, new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
  std::cout << *a << std::endl;
  return 0;
}