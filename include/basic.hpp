#ifndef BASIC_H
#define BASIC_H

#include <cpuid.h>

#include <atomic>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>
#include <type_traits>
#include <utility>

#define __ADD(first, second, third, type)     \
  if constexpr (std::is_same_v<type, bool>) { \
    third = first || second;                  \
  } else {                                    \
    third = first + second;                   \
  }
#define __MNS(first, second, third, type)     \
  if constexpr (std::is_same_v<type, bool>) { \
    third = first || (!second);               \
  } else {                                    \
    third = first - second;                   \
  }
#define __MUT(first, second, third, type)     \
  if constexpr (std::is_same_v<type, bool>) { \
    third = first && second;                  \
  } else {                                    \
    third = first / second;                   \
  }
#define __DIV(first, second, third, type)              \
  if constexpr (std::is_same_v<type, bool>) {          \
    third = (first || second) && (!(first && second)); \
  } else {                                             \
    third = first / second;                            \
  }

namespace basic_math {
extern std::atomic<bool> set_seed;
extern std::mt19937 generator;

template <typename T>
inline int intDigits(T const& alpha) {
  if constexpr (alpha == 0) return 1;
  if constexpr (std::is_same_v<T, bool>) return 1;
  return static_cast<int>(std::floor(std::log10(std::abs(alpha)) + 1));
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
template <typename T>
inline T random(T const& min, T const& max) {
  if (!set_seed.load()) {
    generator.seed(static_cast<unsigned long long>(time(0)));
    set_seed.store(true);
  }
  if constexpr (std::is_same_v<T, int>) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(generator);
  } else if constexpr (std::is_same_v<T, float>) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(generator);
  } else if constexpr (std::is_same_v<T, bool>) {
    std::uniform_int_distribution<int> dist(0, 1);
    return static_cast<bool>(dist(generator));
  } else {
    static_assert(std::is_arithmetic_v<T>, "Unsupported type");
    std::uniform_real_distribution<T> dist(min, max);
    return dist(generator);
  }
}
}  // namespace basic_math

#endif