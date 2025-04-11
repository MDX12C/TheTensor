#include "interface.hpp"
#define SHOW(X) std::cout << #X << " = " << (X) << std::endl;

using sms = system_message::Status;
namespace bsm = basic_math;
namespace ll = lina_lg;
signed main() {
  CONSTRUCT;
  sms::refresh("struct function");
  sms::print();
  [] {
    sms::announce("defult constructor");
    ll::Vector<int> alpha;
    SHOW(alpha);
    sms::announce("size constructor");
    ll::Vector<int> beta(5);
    SHOW(beta);
    sms::announce("init constructor");
    int init[8] = {9, 3, 0, -1, 3, -5, 0, 1};
    ll::Vector<int> gamma(8, init);
    SHOW(gamma);
    sms::announce("copy constructor");
    ll::Vector<int> delta(gamma);
    SHOW(delta);
    memory_manage::MemorySupport::displayUsage();
    sms::announce("move constructor");
    ll::Vector<int> zeta(std::move(delta));
    SHOW(zeta);
    memory_manage::MemorySupport::displayUsage();
    sms::announce("bad type constructor");
    try {
      ll::Vector<char*> omega;
      SHOW(omega);
    } catch (system_message::Error& __epsilon) {
      __epsilon.print();
    }
  }();
  sms::refresh("member function");
  sms::print();
  [] {
    ll::Vector<int> alpha;
    SHOW(alpha);
    sms::announce("resize");
    alpha.resize(3);
    SHOW(alpha);
    sms::announce("load");
    int init[6] = {0, -1, 5, 3, 2, 10};
    alpha.load(6, init);
    SHOW(alpha);
    sms::announce("resize");
    alpha.resize(4);
    SHOW(alpha);
    SHOW(alpha.size());
    SHOW(alpha.capacity());
    SHOW(alpha.sum());
    sms::announce("sum for bool");
    bool temp[5] = {false, true, true, false, true};
    ll::Vector<bool> beta(5, temp);
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
    auto alpha = bsm::uniformRand(10, (float)-10, (float)10);
    auto beta = bsm::uniformRand(10, (float)-10, (float)10);
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
    auto alpha = bsm::uniformRand(10, false, true);
    auto beta = bsm::uniformRand(10, false, true);
    SHOW(alpha);
    SHOW(beta);
    SHOW(alpha + beta);
    SHOW(alpha - beta);
    SHOW(alpha * beta);
    SHOW(alpha / beta);
  }();
  system_message::Status::refresh("compare operator for Vector");
  system_message::Status::print();
  [] {
    auto alpha = bsm::uniformRand(10, 1, 5);
    auto beta = bsm::uniformRand(10, 1, 5);
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
    auto alpha = bsm::uniformRand(9, 1, 10);
    auto beta = bsm::uniformRand(7, -5, 5);
    SHOW(alpha);
    SHOW(ll::merge(alpha, beta));
    SHOW(ll::scan(alpha, 2, 6));
    SHOW(alpha);
    SHOW(beta);
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
