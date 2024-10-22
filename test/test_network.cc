#include "interface.hpp"
#define show(x) std::cout << #x << ":\n" << x << std::endl;
signed main() {
  CONSTRUCT;
  auto alpha = basic_math::random(3, 2, -1.0F, 1.0F);
  show(alpha);
  show(layer::tanh(alpha));
  show(layer::sigmoid(alpha));
  alpha.random(0.0F, 1.0F);
  show(layer::softmax(alpha));
  linalg::Matrix<float> beta;
  float gamma[6] = {1, 0, 0, 1, 0, 0};
  beta.load(3, 2, gamma);
  alpha = layer::sigmoid(alpha);
  alpha = layer::softmax(alpha);
  show(alpha);
  show(beta);
  show(layer::meanSquaredError(beta, alpha));
  show(layer::crossEntropy(beta, alpha));
  DESTRUCT;
}