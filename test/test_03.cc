#include <stdio.h>
class __gobal__ {
private:
  static int __status;

public:
  static void __switch(int);
  static int __get();
};
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
  printf("value=%d\n", __gobal__::__get());
  int a = 5;
  __gobal__::__switch(a);
  printf("now value=%d\n", __gobal__::__get());
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
