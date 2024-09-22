#ifndef BASIC_H
#define BASIC_H 1

#include "define.hpp"
#include "log.hpp"

#define __ADD(first, second, third, type)     \
  if constexpr (std::is_same_v<type, bool>) { \
    third = first || second;                  \
  } else {                                    \
    third = first + second;                   \
  }
#define __MNS(first, second, third, type)     \
  if constexpr (std::is_same_v<type, bool>) { \
    third = first && (!second);               \
  } else {                                    \
    third = first - second;                   \
  }
#define __MUL(first, second, third, type)     \
  if constexpr (std::is_same_v<type, bool>) { \
    third = first && second;                  \
  } else {                                    \
    third = first * second;                   \
  }
#define __DIV(first, second, third, type)              \
  if constexpr (std::is_same_v<type, bool>) {          \
    third = (first || second) && (!(first && second)); \
  } else {                                             \
    third = first / second;                            \
  }

namespace basic_math {

class BasicSupport {
 public:
  static std::mt19937 generator;
  static void init() {
    BasicSupport::generator.seed(static_cast<unsigned long long>(time(0)));
    LOG("C:set seed");
    return;
  }
};
/**
 * Returns the number of digits in an integer.
 *
 * @param alpha The number to determine the number of digits in
 *
 * @return The number of digits in alpha, only return number of digits before
 * the decimal point
 *
 * @throws None
 */
template <typename U>
inline unsigned int intDigits(U const &alpha) {
  LOG("C:");
  if constexpr (std::is_same_v<U, bool>) return 1;
  if (alpha > -1 && alpha < 1) return 1;
  return static_cast<unsigned int>(std::floor(std::log10(std::abs(alpha)) + 1));
}

/**
 * Generates a random number within the range [min, max] based on the input
 * type.
 *
 * @param min The minimum value of the range
 * @param max The maximum value of the range
 *
 * @return A random number within the specified range based on the input type
 *
 * @throws None
 */
template <typename U>
inline U random(U const &min, U const &max) {
  if constexpr (std::is_same_v<U, int>) {
    LOG("C:random<int>");
    std::uniform_int_distribution<int> dist(min, max);
    return dist(BasicSupport::generator);
  } else if constexpr (std::is_same_v<U, float>) {
    LOG("C:random<float>");
    std::uniform_real_distribution<float> dist(min, max);
    return dist(BasicSupport::generator);
  } else if constexpr (std::is_same_v<U, bool>) {
    LOG("C:random<bool>");
    std::uniform_int_distribution<int> dist(0, 1);
    return static_cast<bool>(dist(BasicSupport::generator));
  } else {
    LOG("C:random<U>");
    if (std::is_arithmetic_v<U>) {
      std::uniform_real_distribution<U> dist(min, max);
      return dist(BasicSupport::generator);
    } else {
      LOG("E:arithmetic unsupported type will be set to 0");
      return static_cast<U>(0);
    }
  }
}
}  // namespace basic_math

namespace linalg {
typedef struct MatrixShape {
  unsigned int rows;
  unsigned int cols;
} MaShape;

bool operator==(MaShape const &, MaShape const &);
bool operator<(MaShape const &, MaShape const &);
bool operator<=(MaShape const &, MaShape const &);
std::ostream &operator<<(std::ostream &, MaShape const &);

template <typename U>
class Vector;
template <typename U>
class Matrix;
}  // namespace linalg

/**
 * init of basic.hpp
 */
#define BASIC_CON basic_math::BasicSupport::init();

#endif  // BASIC_H