#include "../includes/math.hpp"
#include <cstdlib>
#include <ctime>
#define show(x)                                                                \
  { std::cout << #x << ':' << '\n' << x << '\n'; }
const int Max_hight = 10;
const int Max_wide = 10;
const int Int_Val = 30;
const _Float32 _Float32_Val = 30.0;
int random(int const &);
_Float32 random(_Float32 const &);
Linalg::Matrix<_Float32> initer(const Linalg::MaShape &, bool);
signed main() {
  std::srand(std::time(0));
  _Float32 value = 0;
  Linalg::MaShape theta, omega;
  /*below is init block*/
  omega.lines = 1 + random(Max_wide - 1);
  theta.rows = 1 + random(Max_hight - 1);
  theta.lines = omega.rows = 1 + random(Max_wide - 1);
  value = 100.0;
  /*below is testing block*/
  Linalg::Matrix<_Float32> A = initer(theta, false);
  show(A);
  Linalg::Matrix<_Float32> B = initer(omega, true);
  show(B);
  Linalg::Matrix<_Float32> C = Linalg::dot(A, B);
  show(C);
  /*above is testing block*/
  return 0;
}

int random(int const &alpha) { return std::rand() % (alpha + 1); }
_Float32 random(_Float32 const &alpha) {
  return (static_cast<_Float32>(std::rand()) / RAND_MAX) * alpha;
}
Linalg::Matrix<_Float32> initer(const Linalg::MaShape &alpha, bool) {
  Linalg::Matrix<_Float32> temp(alpha);
  Linalg::MaShape beta;
  for (beta.rows = 0; beta.rows < alpha.rows; beta.rows++) {
    for (beta.lines = 0; beta.lines < alpha.lines; beta.lines++) {
      temp.endow_(beta, random(_Float32_Val));
    }
  }
  return temp;
}