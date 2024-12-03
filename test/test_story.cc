#include "interface.hpp"

#define SHOW(X) std::cout << #X << ":\n" << X << std::endl;

signed main() {
  CONSTRUCT;
  auto alpha = new storage::Story<int>();
  *alpha = 23;
  SHOW(*alpha);
  memory_manage::MemorySupport::displayUsage(std::cout);
  DESTRUCT;
  return 0;
}