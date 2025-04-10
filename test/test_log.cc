#include "interface.hpp"

signed main() {
  CONSTRUCT;
  LOG("S:main start");
  LOG("C:check test");
  LOG("E:error test");
  LOG("B:bug test");
  if (log_file::checkAlive()) {
    LOG("S:alive");
  } else {
    LOG("S:not alive");
  }
  int a = 18;
  LOG("C:a=%d", a);
  DESTRUCT;
  return 0;
}