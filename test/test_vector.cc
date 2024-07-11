#include <iostream>

#include "basic.hpp"
#include "vector.hpp"

int main() {
  linalg::Vector a(5, new int[5]{1, 2, 3, 4, 5});
  std::cout << a << std::endl;

  return 0;
}