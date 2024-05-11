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
	const int size = 5;
	Linalg::Vector<float> alpha = Basic_Math::random(size, static_cast<float>(-1), static_cast<float>(1));
	show(alpha);
	Linalg::Vector<float> gamma = bsm::absolute(alpha);
	show(gamma);
	return 0;
}