#include <iostream>

#include "../include/basic.hpp"

signed main() {
  BASIC_CON;
  int c;
  c = basic_math::random<int>(0, 100);
  std::cout << c << std::endl;
  std::cout << basic_math::intDigits(-123.8) << std::endl;
  return 0;
}