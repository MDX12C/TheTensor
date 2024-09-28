#include "interface.hpp"
#define show(x) std::cout << #x << " : " << (x) << std::endl;

signed main() {
  CONSTRUCT;
  linalg::MaShape firstShape{4, 6};
  show(firstShape);
  auto alpha =
      basic_math::random(firstShape.rows, firstShape.cols, -15.0F, 15.0F);
  show(alpha);
  auto beta =
      basic_math::random(firstShape.rows, firstShape.cols, -15.0F, 15.0F);
  show(beta);
  show(alpha + beta);
  show(alpha - beta);
  show(alpha * beta);
  show(alpha / beta);
  show(alpha == beta);
  show(alpha != beta);
  show(alpha < beta);
  show(alpha <= beta);
  show(alpha > beta);
  show(alpha >= beta);
  show(basic_math::absolute(alpha));
  show(basic_math::pow(alpha, 2));
  beta.reshape(6, 4);
  show(beta);
  show(basic_math::dot(alpha, beta));
  for (auto i : alpha) show(i);
  show(alpha.transpose());
  auto gamma = basic_math::random(6, -15.0F, 15.0F);
  show(gamma);
  alpha.load(2, 3, gamma.begin());
  show(alpha);
  DESTRUCT;
  return 0;
}