#include "interface.hpp"

signed main() {
  CONSTRUCT;
  system_control::Status::refresh("first");
  system_control::Status::print();
  printf("C: float:%d\n", basic_math::support<float>);
  printf("C: int:%d\n", basic_math::support<int>);
  printf("C: bool:%d\n", basic_math::support<bool>);
  printf("C: char:%d\n", basic_math::support<char>);
  if constexpr (std::is_same_v<FloatType, float>) {
    printf("C: FloatType == float\n");
  } else {
    printf("C: FloatType != float\n");
  }
  printf("C: exp=%f\n", basic_math::EXPRISION);
  float a;
  a = 0.5;
  printf("C:digit(%.*f)=%d\n", basic_math::PRINT_ACCURACY, a,
         basic_math::intDigits(a));
  a = 2;
  printf("C:digit(%f)=%d\n", a, basic_math::intDigits(a));
  a = 10;
  printf("C:digit(%f)=%d\n", a, basic_math::intDigits(a));
  a = -8;
  printf("C:digit(%f)=%d\n", a, basic_math::intDigits(a));
  checkBaseType();
  DESTRUCT;
  return 0;
}