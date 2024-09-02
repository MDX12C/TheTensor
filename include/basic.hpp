#ifndef BASIC_H
#define BASIC_H

#include "define.hpp"

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
extern std::mt19937 generator;

static inline __attribute__((__constructor__(101), __used__)) void init() {
  generator.seed(static_cast<unsigned long long>(time(0)));
  return;
}

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
    std::uniform_int_distribution<int> dist(min, max);
    return dist(generator);
  } else if constexpr (std::is_same_v<U, float>) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(generator);
  } else if constexpr (std::is_same_v<U, bool>) {
    std::uniform_int_distribution<int> dist(0, 1);
    return static_cast<bool>(dist(generator));
  } else {
    static_assert(std::is_arithmetic_v<U>, "Unsupported type");
    std::uniform_real_distribution<U> dist(min, max);
    return dist(generator);
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

#endif  // BASIC_H