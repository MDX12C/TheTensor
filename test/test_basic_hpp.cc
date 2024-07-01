#include <iostream>

#include "basic.hpp"

int main() {
  int c;
  c = basic_math::random<int>(0, 100);
  std::cout << c << std::endl;
  return 0;
}