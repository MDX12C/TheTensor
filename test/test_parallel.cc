#include "interface.hpp"
typedef int32_t Type;
signed main() {
  CONSTRUCT;
  size_t TEST_SIZE = 512;
  std::cout << "THREADS= " << THREADS << " BLOCKS= " << BLOCKS
            << " GROUP= " << GROUP;
  TEST_SIZE = []() -> size_t {
    int a = -1;
    do {
      std::cout << "\nput test size: ";
      std::cin >> a;
    } while (a <= 0);
    return size_t(a);
  }();
  auto alpha = new Type[TEST_SIZE];
  auto beta = new Type[TEST_SIZE];
  auto gamma = new Type[TEST_SIZE];
  std::string tips("initializing...");
  for (size_t i = 0; i < TEST_SIZE; i++) {
    system_message::Status::bar(i, TEST_SIZE, tips);
    alpha[i] = basic_math::uniformRand<Type>(-5, 5);
    beta[i] = basic_math::uniformRand<Type>(-5, 5);
  }
  system_message::Status::bar(1, 1);
  std::cout << "\ntest for cuda...\n";
  vv_add_i32(alpha, beta, gamma, TEST_SIZE);
  tips = "checking answer...";
  [&] {
    for (size_t i = 0; i < TEST_SIZE; i++) {
      system_message::Status::bar(i, TEST_SIZE, tips);
      if (gamma[i] != (alpha[i] + beta[i])) {
        std::cout << "\nError: bad answer when i= " << i << std::endl;
        return;
      }
    }
    system_message::Status::bar(1, 1);
    std::cout << "\nOperate success!\n";
    return;
  }();
  delete[] alpha;
  delete[] beta;
  delete[] gamma;
  DESTRUCT;
}