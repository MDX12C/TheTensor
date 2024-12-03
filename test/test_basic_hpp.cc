#include "interface.hpp"

signed main() {
  CONSTRUCT;
  LOG("C: float:%d", basic_math::support<float>);
  LOG("C: int:%d", basic_math::support<int>);
  LOG("C: bool:%d", basic_math::support<bool>);
  LOG("C: char:%d", basic_math::support<char>);
  if constexpr (std::is_same_v<FloatType, float>) {
    LOG("C: FloatType == float");
  } else {
    LOG("C: FloatType != float");
  }
  LOG("C: exp=%f", basic_math::EXPRISION);
  float a;
  a = 0.5;
  LOG("C:digit(%.*f)=%d", basic_math::PRINT_ACCURACY, a,
      basic_math::intDigits(a));
  a = 2;
  LOG("C:digit(%f)=%d", a, basic_math::intDigits(a));
  a = 10;
  LOG("C:digit(%f)=%d", a, basic_math::intDigits(a));
  a = -8;
  LOG("C:digit(%f)=%d", a, basic_math::intDigits(a));
  try {
    LOG("C:rand int: %d", basic_math::random(-5, 5));
    LOG("C:rand float: %f", basic_math::random(-1.0F, 1.0F));
    LOG("C:rand bool: %d", basic_math::random(false, true));
    LOG("C:rand char: %c", basic_math::random('A', 'D'));
  } catch (system_message::Error& epsilon) {
    epsilon.print();
  }
  DESTRUCT;
  return 0;
}