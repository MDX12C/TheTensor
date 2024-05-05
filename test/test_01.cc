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
  float beta = 2;
  Linalg::Vector<float> alpha = Basic_Math::random(size, static_cast<float>(-1), static_cast<float>(1));
  show(alpha);
  show(beta);
  Basic_Math::status();
  Linalg::Vector<float> gamma = beta / alpha;
  Basic_Math::status();
  show(gamma);
  return 0;
}