#include "../include/interface.hpp"

signed main() {
  CONSTRUCT;
  LOG("C:hello world\n");
  int a = 1203;
  LOG("C:a= %d\n", a);
  DESTRUCT;
  return 0;
}