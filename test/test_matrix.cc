#include "interface.hpp"
#define SHOW(X) std::cout << #X << " = " << (X) << std::endl;
using sms = system_message::Status;
namespace bsm = basic_math;
namespace ll = lina_lg;
auto mks = *lina_lg::makeShape;
signed main() {
  CONSTRUCT;
  sms::refresh("struct function");
  sms::print();
  [] {
    sms::announce("defult constructor");
    ll::Matrix<int> alpha;
    SHOW(alpha);
    sms::announce("shape constructor");
    ll::Matrix<int> beta(mks(4, 3));
    SHOW(beta);
    sms::announce("init constructor");
    int init[8] = {9, 3, 0, -1, 3, -5, 0, 1};
    ll::Matrix<int> gamma(mks(2, 4), init);
    SHOW(gamma);
    sms::announce("copy constructor");
    ll::Matrix<int> delta(gamma);
    SHOW(delta);
    memory_manage::MemorySupport::displayUsage();
    sms::announce("move constructor");
    ll::Matrix<int> zeta(std::move(delta));
    SHOW(zeta);
    memory_manage::MemorySupport::displayUsage();
    sms::announce("bad type constructor");
    try {
      ll::Matrix<char*> omega;
      SHOW(omega);
    } catch (system_message::Error& __epsilon) {
      __epsilon.print();
    }
  }();
  sms::refresh("member function");
  sms::print();
  [] {
    ll::Matrix<int> alpha;
    SHOW(alpha);
    sms::announce("resize");
    alpha.resize(mks(2, 3));
    SHOW(alpha);
    sms::announce("load");
    int init[6] = {0, -1, 5, 3, 2, 10};
    alpha.load(mks(3, 2), init);
    SHOW(alpha);
    sms::announce("resize");
    alpha.resize(mks(2, 4));
    SHOW(alpha);
    SHOW(alpha.shape());
    SHOW(alpha.size());
    SHOW(alpha.capacity());
    SHOW(alpha.sum());
    SHOW(alpha.transpose());
    sms::announce("reshape");
    alpha.reshape(mks(1, 8));
    SHOW(alpha);
    sms::announce("wrong way to use resize");
    try {
      alpha.resize(4);
    } catch (system_message::Error& __epsilon) {
      __epsilon.print();
    }
    sms::announce("sum for bool");
    bool temp[5] = {false, true, true, false, true};
    ll::Matrix<bool> beta(mks(1, 5), temp);
    SHOW(beta);
    SHOW(beta.sum());
    sms::announce("range based for loop");
    for (auto i : alpha) SHOW(i);
    sms::announce("freedom");
    alpha.freedom();
    SHOW(alpha);
  }();
  system_message::Status::refresh("operator overloading for float");
  system_message::Status::print();
  [] {
    auto alpha = bsm::uniformRand(mks(2, 3), (float)-10, (float)10);
    auto beta = bsm::uniformRand(mks(2, 3), (float)-10, (float)10);
    auto sigma = bsm::uniformRand((float)-10, (float)10);
    SHOW(alpha);
    SHOW(beta);
    SHOW(alpha + beta);
    SHOW(alpha - beta);
    SHOW(alpha * beta);
    SHOW(alpha / beta);
    SHOW(alpha += beta);
    SHOW(alpha *= beta);
    SHOW(!alpha);
    SHOW(beta);
    SHOW(sigma);
    SHOW(beta + sigma);
    SHOW(alpha);
    SHOW(sigma + alpha);
  }();
  system_message::Status::refresh("operator overloading for bool");
  system_message::Status::print();
  [] {
    auto alpha = bsm::uniformRand(mks(2, 5), false, true);
    auto beta = bsm::uniformRand(mks(2, 5), false, true);
    SHOW(alpha);
    SHOW(beta);
    SHOW(alpha + beta);
    SHOW(alpha - beta);
    SHOW(alpha * beta);
    SHOW(alpha / beta);
  }();
  system_message::Status::refresh("compare operator for Matrix");
  system_message::Status::print();
  [] {
    auto alpha = bsm::uniformRand(mks(2, 5), 1, 5);
    auto beta = bsm::uniformRand(mks(2, 5), 1, 5);
    SHOW(alpha);
    SHOW(beta);
    SHOW(alpha == beta);
    SHOW(alpha != beta);
    SHOW(alpha >= beta);
    SHOW(alpha <= beta);
    SHOW(alpha > beta);
    SHOW(alpha < beta);
  }();
  system_message::Status::refresh("other support function");
  system_message::Status::print();
  [] {
    auto alpha = bsm::uniformRand(mks(2, 3), 1, 10);
    auto beta = bsm::uniformRand(mks(2, 3), -5, 5);
    SHOW(alpha);
    SHOW(ll::mergeUD(alpha, beta));
    SHOW(ll::mergeLR(alpha, beta));
    sms::announce("make new alpha");
    alpha = std::move(bsm::uniformRand(mks(6, 8), 1, 10));
    SHOW(alpha);
    SHOW(ll::scan(alpha, mks(1, 2), mks(6, 5)));
    alpha.resize(beta.shape());
    SHOW(alpha);
    SHOW(beta);
    [&] {
      auto gamma = alpha.transpose();
      SHOW(bsm::dot(gamma, beta));
    }();
    SHOW(bsm::absolute(beta));
    SHOW(bsm::pow(2, alpha));
    SHOW(bsm::pow(beta, 2));
    SHOW(bsm::pow(beta, alpha));
    auto gamma = bsm::uniformRand(10, 2.0F, 1024.0F);
    SHOW(gamma);
    SHOW(bsm::log(gamma));
  }();
  DESTRUCT;
  return 0;
}
