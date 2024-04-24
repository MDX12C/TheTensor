#include "../includes/math.hpp"
#include <iostream>

#define float _Float32

#define show(x)                                                                \
  { std::cout << #x << ':' << '\n' << x << '\n'; }
const int Max_hight = 10;
const int Max_wide = 10;
const int Int_Val = 30;
const float Float_Val = 30.0;

int random(int const &);
float random(float const &);
Linalg::Matrix<float> initialize(const Linalg::MaShape &, bool);

signed main() {
  Linalg::Matrix<float> A = initialize({3, 3}, 1.0);
  Linalg::Matrix<float> B = initialize({3, 3}, 1.0);
  Linalg::Matrix<float> C = Linalg::dot(A, B);
  show(C);
}

int random(int const &alpha) { return std::rand() % (alpha + 1); }

float random(float const &alpha) {
  return (static_cast<float>(std::rand()) / RAND_MAX) * alpha;
}

Linalg::Matrix<float> initialize(const Linalg::MaShape &alpha, bool) {
  Linalg::Matrix<float> temp(alpha);
  Linalg::MaShape beta;
  for (beta.rows = 0; beta.rows < alpha.rows; beta.rows++) {
    for (beta.lines = 0; beta.lines < alpha.lines; beta.lines++) {
      temp.endow_(beta, random(Float_Val));
    }
  }
  return temp;
}