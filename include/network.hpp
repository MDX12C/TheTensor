#ifndef NETWORK_H
#define NETWORK_H 1
#include "basic.hpp"
#include "define.hpp"
#include "log.hpp"
#include "matrix.hpp"
#include "vector.hpp"

namespace layer {
template <typename T>
inline linalg::Matrix<float> tanh(linalg::Matrix<T> const&);
template <typename T>
inline linalg::Matrix<float> sigmoid(linalg::Matrix<T> const&);
template <typename T>
inline linalg::Matrix<float> softmax(linalg::Matrix<T> const&);
template <typename T>
inline linalg::Vector<float> meanSquaredError(linalg::Matrix<T> const&,
                                              linalg::Matrix<T> const&);
template <typename T>
inline linalg::Vector<float> crossEntropy(linalg::Matrix<T> const&,
                                          linalg::Matrix<T> const&);
class Affine {
 private:
  char id_;
  linalg::Matrix<float>* weight_;
  linalg::Matrix<float>* input_;

 public:
  Affine();
  Affine(Affine const&);
  ~Affine();
  inline void autoInit(bool const&);
  inline void initWeight(unsigned int const&, unsigned int const&);
  inline bool read();
  inline bool write();
  inline linalg::Matrix<float> forward(linalg::Matrix<float>&);
  inline linalg::Matrix<float> backward(linalg::Matrix<float>&);
};
#if 0
class Input;
class Sigmoid;
class Tanh;
class ReLu;
class Output;
#endif
}  // namespace layer

namespace layer {
/**
 * @brief tanh function
 * @param param the matrix
 * @return the result
 */
template <typename T>
linalg::Matrix<float> tanh(linalg::Matrix<T> const& param) {
  LOG("C:tanh")
  auto alpha = linalg::Matrix<float>(param);
  alpha = basic_math::pow(basic_math::exprision, alpha);
  alpha.powF(2);
  return (alpha - 1) / (alpha + 1);
}
/**
 * @brief sigmoid function
 * @param param the matrix
 * @return the result
 */
template <typename T>
linalg::Matrix<float> sigmoid(linalg::Matrix<T> const& param) {
  LOG("C:sigmoid");
  auto alpha = linalg::Matrix<float>(param);
  alpha = basic_math::pow(basic_math::exprision, alpha);
  return alpha / (alpha + 1);
}
/**
 * @brief softmax function
 * @param param the datas cols is data's groups
 * @return the result
 */
template <typename T>
linalg::Matrix<float> softmax(linalg::Matrix<T> const& param) {
  LOG("C:softmax");
  auto alpha = linalg::Matrix<float>(param);
  float sum;
  float* const ptr = alpha.begin();
  unsigned int const high = alpha.shape().rows;
  unsigned int const step = alpha.shape().cols;
  unsigned int phi;
  for (unsigned int j = 0; j < alpha.shape().cols; j++) {
    phi = j;
    sum = 0;
    for (unsigned int i = 0; i < high; i++) {
      sum += ptr[phi];
      phi += step;
    }
    phi = j;
    for (unsigned int i = 0; i < high; i++) {
      ptr[phi] /= sum;
      phi += step;
    }
  }
  return alpha;
}
/**
 * @brief mean squared error
 * @param stdAns the correct answer
 * @param outAns the output answer
 * @return loss for every datas in vector
 */
template <typename T>
linalg::Vector<float> meanSquaredError(linalg::Matrix<T> const& stdAns,
                                       linalg::Matrix<T> const& outAns) {
  LOG("C:meanSquaredError");
  auto alpha = linalg::Matrix<float>(stdAns);
  alpha -= linalg::Matrix<float>(outAns);
  alpha.powF(2);
  unsigned int sigma = 0;
  unsigned int const omega = alpha.shape().cols;
  linalg::Vector<float> beta(omega);
  for (auto gamma : alpha) {
    if (sigma == omega) sigma = 0;
    beta[sigma] += gamma;
    sigma++;
  }
  beta /= alpha.shape().rows;
  return beta;
}
/**
 * @brief cross entropy
 * @param stdAns the correct answer
 * @param outAns the output answer
 * @return loss for every datas in vector
 */
template <typename T>
linalg::Vector<float> crossEntropy(linalg::Matrix<T> const& stdAns,
                                   linalg::Matrix<T> const& outAns) {
  LOG("C:cross entropy");
  auto alpha = linalg::Matrix<float>(stdAns);
  auto beta = linalg::Matrix<float>(outAns);
  auto gamma = alpha * basic_math::log(beta);
  gamma += (1.0F - alpha) * basic_math::log(1.0F - beta);
  gamma *= -1;
  unsigned int const sigma = gamma.shape().cols;
  unsigned int phi = 0;
  linalg::Vector<float> omega(sigma);
  for (auto delta : gamma) {
    if (phi == sigma) phi = 0;
    omega[phi] += delta;
    phi++;
  }
  return omega;
}

}  // namespace layer
#endif