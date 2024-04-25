#include "../includes/math.hpp"
#include <cstdlib>
#include <ctime>
#define show(x)                                                                \
  { std::cout << #x << ':' << '\n' << x << '\n'; }
const int Max_hight = 20;
const int Max_wide = 20;
const int Int_Val = 1;
const float Float_Val = static_cast<float>(1.0);
int random(int const&);
float random(float const&);
Linalg::Matrix<float> initer(const Linalg::MaShape&, bool);
signed main() {
  std::srand(std::time(0));
  float value = static_cast<float>(0.0);
  Linalg::MaShape theta, omega;
  /*below is init block*/
  omega.lines = 1 + random(Max_wide - 1);
  theta.rows = 1 + random(Max_hight - 1);
  theta.lines = omega.rows = 1 + random(Max_wide - 1);
  /*below is testing block*/
  Linalg::Matrix<float> A = initer(theta, false);
  show(A);
  Linalg::Matrix<float> B = initer(omega, true);
  show(B);
  Linalg::Matrix<float> C = Linalg::dot(A, B);
  show(C);
  /*above is testing block*/
  return 0;
}

int random(int const& alpha) { return std::rand() % (alpha + 1); }
float random(float const& alpha) {
  return (static_cast<float>(std::rand()) / RAND_MAX) * alpha;
}
Linalg::Matrix<float> initer(const Linalg::MaShape& alpha, bool) {
  Linalg::Matrix<float> temp(alpha);
  Linalg::MaShape beta;
  for (beta.rows = 0; beta.rows < alpha.rows; beta.rows++) {
    for (beta.lines = 0; beta.lines < alpha.lines; beta.lines++) {
      temp.endow_(beta, random(Float_Val));
    }
  }
  return temp;
}