#include "interface.hpp"
#define SHOW(X) std::cout << #X << " = " << X << std::endl;
signed main() {
  CONSTRUCT;
  lina_lg::Vector<int> alpha;

  SHOW(alpha.size());
  DESTRUCT;
  return;
}