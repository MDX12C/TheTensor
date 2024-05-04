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
  const int size = 20;
  Linalg::Vector<float> alpha = Basic_Math::random(size, Basic_Math::float_value_min, Basic_Math::float_value_max);
  Linalg::Vector<float> beta = Basic_Math::random(size, Basic_Math::float_value_min, Basic_Math::float_value_max);
  show(alpha);
  show(beta);
  Linalg::Vector<float> gamma = alpha + beta;
  show(gamma);
  return 0;
}