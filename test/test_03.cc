#include <stdio.h>
bool right();
class __gobal__ {
private:
  friend bool right();
  static int __status;
  static bool test(int a) {
    return bool(a % 2);
  }
public:
  static void __switch(int);
  static int __get();
};
bool right() {
  return __gobal__::test(5);
}
int __gobal__::__status = 0;
void __gobal__::__switch(int a) {
  __gobal__::__status = a;
  return;
}
int __gobal__::__get() { return __gobal__::__status; }
__attribute__((__constructor__(105), __used__)) void init() {
  printf("~construct~\n");
  return;
}
signed main() {
  printf("~main function~\n");
  if (right()) {
    printf("right\n");
  }
  else {
    printf("wrong\n");
  }
  return 0;
}
__attribute__((__destructor__(105), __used__)) void over() {
  printf("~destruct~\n");
  return;
}
__attribute__((__constructor__(101), __destructor__(109), __used__)) void
lam() {
  printf("bbll\n");
}
