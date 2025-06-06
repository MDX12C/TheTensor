#include "interface.hpp"

#define SHOW(X) std::cout << #X << ":\n" << X << std::endl;

signed main() {
  CONSTRUCT;
  try {
    auto alpha = new storage::Story<float>();
    *alpha = 23.5F;
    SHOW(*alpha);

    auto beta = new storage::Story<int>();
    *beta = (storage::Story<int>)(*alpha);
    beta->resize(0);
    SHOW(*beta);
    beta->resize(6);
    SHOW(*beta);
    for (size_t i = 0; i < beta->size(); i++) beta->at(i) += i;
    SHOW(*beta);
    SHOW(beta->sum());
    beta->freedom();
    SHOW(*beta);
    int temp[10] = {3, 2, 4, 6, 7, 1, 8, 9, 1, 0};
    SHOW(beta->load(10, temp));
    SHOW(*beta);

    auto gamma = new storage::Story<char*>();
    memory_manage::MemorySupport::displayUsage();
  } catch (system_message::Error& __epsilon) {
    __epsilon.print();
  }
  DESTRUCT;
  return 0;
}