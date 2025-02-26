#include "interface.hpp"

signed main() {
  CONSTRUCT;
  system_message::Status::refresh("first");
  system_message::Status::print();
  printf("C: float:%d", basic_math::support<float>);
  printf("C: int:%d", basic_math::support<int>);
  printf("C: bool:%d", basic_math::support<bool>);
  printf("C: char:%d", basic_math::support<char>);
  if constexpr (std::is_same_v<FloatType, float>) {
    printf("C: FloatType == float");
  } else {
    printf("C: FloatType != float");
  }
  printf("C: exp=%f", basic_math::EXPRISION);
  float a;
  a = 0.5;
  printf("C:digit(%.*f)=%d", basic_math::PRINT_ACCURACY, a,
         basic_math::intDigits(a));
  a = 2;
  printf("C:digit(%f)=%d", a, basic_math::intDigits(a));
  a = 10;
  printf("C:digit(%f)=%d", a, basic_math::intDigits(a));
  a = -8;
  printf("C:digit(%f)=%d", a, basic_math::intDigits(a));
  system_message::Status::refresh("second");
  system_message::Status::print();
  try {
    printf("C:rand int: %d", basic_math::random(-5, 5));
    printf("C:rand float: %f", basic_math::random(-1.0F, 1.0F));
    printf("C:rand bool: %d", basic_math::random(false, true));
    printf("C:rand char: %c", basic_math::random('A', 'D'));
  } catch (system_message::Error& epsilon) {
    epsilon.print();
  }
  DESTRUCT;
  return 0;
}