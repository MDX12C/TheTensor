#include "interface.hpp"
#define show(x) std::cout << #x << " : " << x << std::endl;

signed main() {
  CONSTRUCT;
  linalg::MaShape firstShape{4, 6};
  show(firstShape);
  auto alpha = basic_math::random(4, 6, 0.0F, 10.0F);
  show(alpha);
  DESTRUCT;
  return 0;
}