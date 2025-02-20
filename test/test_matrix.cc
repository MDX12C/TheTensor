#include "interface.hpp"
#define TEST_MATRIX 1
#define SHOW(X) std::cout << #X << ":\n" << (X) << std::endl;
#define DO(X)                           \
  system_message::Status::announce(#X); \
  (X);
namespace ll = lina_lg;
namespace bsm = basic_math;
namespace stms = system_message;
signed main() {
  CONSTRUCT;
#if 1
  system_message::Status::refresh("math function and member function");
  system_message::Status::print();
  lina_lg::Matrix<float> alpha;
  SHOW(alpha);
  DO(alpha.resize(lina_lg::makeShape(2, 4)))
  SHOW(alpha);
  system_message::Status::announce("beta=random(alpha,-10,10)");
  auto beta = basic_math::random(alpha, (float)-10, (float)10);
  SHOW(alpha);
  SHOW(beta);
  DO(basic_math::absolute(alpha));
  DO(basic_math::pow((float)2, beta));
  SHOW(alpha);
  SHOW(beta);
  system_message::Status::announce("mu=Matrix<int>(alpha)");
  auto mu = (lina_lg::Matrix<int>)alpha;
  SHOW(mu);
  DO(basic_math::pow(mu, 4));
  SHOW(mu);
  DO(alpha = (lina_lg::Matrix<float>)mu);
  SHOW(alpha);
  DO(alpha.resize(lina_lg::makeShape(1, 3)));
  SHOW(alpha);
  DO(basic_math::log(alpha));
  SHOW(alpha);
  system_message::Status::announce("nu(alpha.shape(),alpha.begin());");
  lina_lg::Matrix<float> nu(alpha.shape(), alpha.begin());
  SHOW(nu);
  SHOW(nu.transpose());
  memory_manage::MemorySupport::displayUsage();
#endif
#if 1
  system_message::Status::refresh("operator overloading for float");
  system_message::Status::print();
  lina_lg::Matrix<float> delta, omega;
  SHOW(delta);
  SHOW(omega);
  DO(delta.resize(lina_lg::makeShape(2, 5)));
  DO(omega.resize(lina_lg::makeShape(2, 5)));
  SHOW(delta);
  SHOW(omega);
  DO(basic_math::random(delta, (float)-10, (float)10));
  DO(basic_math::random(omega, (float)-10, (float)10));
  SHOW(delta);
  SHOW(omega);
  SHOW(delta + omega);
  SHOW(delta - omega);
  SHOW(delta * omega);
  SHOW(delta / omega);
  SHOW(delta += omega);
  SHOW(delta *= omega);
  SHOW(!delta);
  SHOW(omega);
  SHOW(basic_math::EXPRISION);
  SHOW(omega + basic_math::EXPRISION);
  memory_manage::MemorySupport::displayUsage();
#endif
#if 1
  system_message::Status::refresh("operator overloading for bool");
  system_message::Status::print();
  lina_lg::Matrix<bool> zeta, eta;
  DO(zeta.resize(lina_lg::makeShape(2, 5)));
  DO(eta.resize(lina_lg::makeShape(2, 5)));
  DO(basic_math::random(zeta, false, true));
  DO(basic_math::random(eta, false, true));
  SHOW(zeta);
  SHOW(eta);
  SHOW(zeta + eta);
  SHOW(zeta - eta);
  SHOW(zeta * eta);
  SHOW(zeta / eta);
  memory_manage::MemorySupport::displayUsage();
#endif
#if 1
  system_message::Status::refresh("compare operator for Matrix");
  system_message::Status::print();
  lina_lg::Matrix<int> theta, lota;
  DO(theta.resize(lina_lg::makeShape(2, 5)));
  DO(lota.resize(lina_lg::makeShape(2, 5)));
  DO(basic_math::random(theta, 1, 5));
  DO(basic_math::random(lota, 1, 5));
  SHOW(theta);
  SHOW(lota);
  SHOW(theta == lota);
  SHOW(theta != lota);
  SHOW(theta >= lota);
  SHOW(theta <= lota);
  SHOW(theta > lota);
  SHOW(theta < lota);
  memory_manage::MemorySupport::displayUsage();
#endif
#if 1
  system_message::Status::refresh("other function");
  system_message::Status::print();
  DO(alpha.resize(beta.shape()));
  SHOW(alpha);
  SHOW(beta);
  SHOW(lina_lg::mergeLR(alpha, beta));
  SHOW(lina_lg::mergeUD(alpha, beta));
  DO(alpha = lina_lg::mergeUD(alpha, beta));
  SHOW(alpha);
  SHOW(ll::scan(alpha, ll::makeShape(1, 1), ll::makeShape(3, 4)));
  DO(alpha.resize(ll::makeShape(5, 6)));
  DO(bsm::random(alpha, (float)-10, (float)10));
  SHOW(alpha);
  SHOW(ll::scan(alpha, ll::makeShape(2, 1), ll::makeShape(4, 4)));
  DO(theta.resize(ll::makeShape(2, 3)));
  DO(lota.resize(ll::makeShape(2, 3)));
  SHOW(theta);
  SHOW(lota);
  stms::Status::announce("finalAnswer");
  ll::Matrix<int> finalAnswer;
  DO(finalAnswer = theta.transpose());
  SHOW(finalAnswer);
  SHOW(bsm::dot(finalAnswer, lota, theta));
  memory_manage::MemorySupport::displayUsage();
#endif
  DESTRUCT;
}