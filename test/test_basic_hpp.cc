#include <iostream>

#include "interface.hpp"

#define show(x) std::cout << #x << " : " << x << std::endl;

signed main() {
  CONSTRUCT;
  int c = basic_math::random(0, 100);
  show(c);
  std::cout << basic_math::intDigits(-123.8) << std::endl;
  float f = basic_math::random(0.0F, 100.0F);
  show(f);
  DESTRUCT;
  return 0;
}