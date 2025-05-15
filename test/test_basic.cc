#include "interface.hpp"

signed main() {
  CONSTRUCT;
  system_control::Status::refresh("c test", true);
  checkBaseType();
  printf("DEBUG: %d\n", __DEBUG_MODE__);
  printf("SPEED: %d\n", __SPEED_MODE__);
  printf("Float16: %d\n", __F16__);
  printf("LIMIT: %d\n", __LIMIT_MODE__);
  printf("CUDA: %d\n", __CUDA_MODE__);
  printf("GNUC: %d\n", __GNUC__);
  printf("CPP: %d\n", __cplusplus);
  system_control::Status::refresh("cpp test");
  system_control::Status::print();
  printf("C: float:%d\n", basic_math::support<float>);
  printf("C: int:%d\n", basic_math::support<int>);
  printf("C: bool:%d\n", basic_math::support<bool>);
  printf("C: char:%d\n", basic_math::support<char>);
  printf("C: exp=%f\n", (float)basic_math::EXPRISION);
  float a;
  a = 0.5;
  printf("C:digit(%.*f)=%d\n", basic_math::PRINT_ACCURACY, a,
         basic_math::intDigits(a));
  a = 2;
  printf("C:digit(%.*f)=%d\n", a, basic_math::PRINT_ACCURACY,
         basic_math::intDigits(a));
  a = 10;
  printf("C:digit(%.*f)=%d\n", basic_math::PRINT_ACCURACY, a,
         basic_math::intDigits(a));
  a = -8;
  printf("C:digit(%.*f)=%d\n", basic_math::PRINT_ACCURACY, a,
         basic_math::intDigits(a));
  DESTRUCT;
  return 0;
}