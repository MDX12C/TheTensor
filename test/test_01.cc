#define _VERSION_04_29_
#ifdef _VERSION_04_29_
#include "../includes/basic.hpp"
namespace bsm = Basic_Math;
#else 
#include "../includes/math.hpp"
#endif
#define show(x)                                                                \
  { std::cout << #x << ':' << '\n' << x << '\n'; }
signed main() {
  bool alpha = bsm::random(false, true);
  std::cout << alpha;
  return 0;
}