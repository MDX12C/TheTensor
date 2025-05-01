#include "interface.hpp"

#define PRINT 0
typedef int32_t Type;
template <typename T>
inline bool check(T* const& __a, T* const& __b, size_t const& __size) noexcept {
  std::string extand;
  extand.reserve(50);
  for (size_t i = 0; i < __size; i++) {
    sprintf(extand.data(), "check %ld in %ld", i + 1, __size);
    system_message::Status::bar(i, __size, extand);
    if (__a[i] != __b[i]) {
      LOG("E:bad answer");
      printf("\nbad answer when i= %ld\n", i);
      return false;
    }
  }
  system_message::Status::bar(1, 1);
  std::cout << "\nCompute success!\n";
  return true;
}
template <typename T>
inline void matrixDot(T* const&, T* const&, T* const&, size_t const&,
                      size_t const&, size_t const&);

signed main() {
  CONSTRUCT;
  auto getTimes = []() -> size_t {
    int alpha = -1;
    do {
      std::cout << "how many times:\n";
      std::cin >> alpha;
      std::cin.get();
    } while (alpha <= 0);
    return static_cast<size_t>(alpha);
  };
  std::clock_t p1, p2, p3;
  size_t rows = getTimes(), lines = getTimes(), cols = getTimes();
  lina_lg::Matrix<Type> alpha, beta, gamma, delta;
  alpha.resize({rows, lines});
  beta.resize({lines, cols});
  for (auto& i : alpha) i = basic_math::uniformRand<Type>(0, 1);
  for (auto& i : beta) i = basic_math::uniformRand<Type>(0, 1);
#if PRINT
  std::cout << "alpha:\n" << alpha << "\nbeta:\n" << beta;
#endif
  gamma.resize({rows, cols});
  delta.resize(gamma.shape());
  p1 = std::clock();
  basic_math::mDot<Type, false>(alpha.begin(), beta.begin(), gamma.begin(),
                                rows, lines, cols);
  p2 = std::clock();
  basic_math::mDot<Type, true>(alpha.begin(), beta.begin(), delta.begin(), rows,
                               lines, cols);
  p3 = std::clock();
#if PRINT
  std::cout << "\ngamma:\n" << gamma << "\ndelta:\n" << delta << '\n';
#endif
  check(gamma.begin(), delta.begin(), rows * cols);
  p3 -= p2;
  p2 -= p1;
  std::cout << "CPU use " << p2 << " GPU use " << p3 << '\n';
  DESTRUCT;
}
template <typename T>
inline void matrixDot(T* const& __a, T* const& __b, T* const& __c,
                      size_t const& __row, size_t const& __line,
                      size_t const& __col) {
  T *beta, *gamma, *alpha = __a;
  for (size_t i = 0, row = 0; row < __row; row++, alpha += __line) {
    beta = __b;
    for (size_t col = 0; col < __col; i++, col++, beta++) {
      gamma = beta;
      for (size_t k = 0; k < __line; k++, gamma += __col)
        __c[i] += alpha[k] * (*gamma);
    }
  }
  return;
}