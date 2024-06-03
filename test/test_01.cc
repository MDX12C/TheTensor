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
  Linalg::Vector<float> alpha = Basic_Math::random(20, float(-1), float(1));
  show(alpha);
  Linalg::Vector<float> beta = Basic_Math::random(20, float(-1), float(1));
  show(beta);
  Linalg::Vector<float> gamma = alpha + beta;
  show(gamma);
  return 0;
}