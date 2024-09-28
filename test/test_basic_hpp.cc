#include <iostream>

#include "interface.hpp"

#define show(x) std::cout << #x << " : " << x << std::endl;

signed main() {
  CONSTRUCT;
  auto c = basic_math::random<int>(0, 100);
  show(c);
  std::cout << basic_math::intDigits(-123.8) << std::endl;
  auto f = basic_math::random<float>(0, 100);
  show(f);
  DESTRUCT;
  return 0;
}