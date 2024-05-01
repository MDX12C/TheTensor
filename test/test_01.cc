#define _VERSION_
#ifdef _VERSION_
#include "../includes/vector.hpp"
namespace bsm = Basic_Math;
#else 
#include "../includes/math.hpp"
#endif
#define show(x)                                                                \
  { std::cout << #x << ':' << '\n' << x << '\n'; }
signed main() {
  Basic_Math::status();
  const int size = 10;
  Linalg::Vector<int> alpha = Basic_Math::random(size, Basic_Math::int_value_min, Basic_Math::int_value_max);
  std::cout << alpha;
  alpha.freedom_();
  return 0;
}