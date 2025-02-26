#include "interface.hpp"

signed main() {
  CONSTRUCT;
  LOG("S:main start");
  LOG("C:check test");
  LOG("E:error test");
  LOG("B:bug test");
  int a = 18;
  LOG("C:a=%d", a);
  if (a == 18) {
    endOfMainFunction();
  }
  DESTRUCT;
  return 0;
}