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
	Linalg::Vector<float> Alpha = bsm::random(size, static_cast<float>(-1), static_cast<float>(1));
	show(Alpha);
	Linalg::Vector<float> Beta = bsm::random(size, static_cast<float>(-1), static_cast<float>(1));
	show(Beta);
	Linalg::Vector<float> Gamma = Alpha + Beta;
	show(Gamma);
	return 0;
}