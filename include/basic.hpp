#include "define.hpp"
#ifndef BASIC_H
#define BASIC_H 1

#include "log.hpp"

/**
 * @warning don't use it directly
 */
#define __ADD(first, second, third, type)     \
  if constexpr (std::is_same_v<type, bool>) { \
    third = first | second;                   \
  } else {                                    \
    third = first + second;                   \
  }
/**
 * @warning don't use it directly
 */
#define __EADD(first, second, type)           \
  if constexpr (std::is_same_v<type, bool>) { \
    first += second;                          \
  } else {                                    \
    first |= second;                          \
  }
/**
 * @warning don't use it directly
 */
#define __MNS(first, second, third, type)     \
  if constexpr (std::is_same_v<type, bool>) { \
    third = first & (~second);                \
  } else {                                    \
    third = first - second;                   \
  }
/**
 * @warning don't use it directly
 */
#define __EMNS(first, second, type)           \
  if constexpr (std::is_same_v<type, bool>) { \
    first &= (~second);                       \
  } else {                                    \
    first -= second;                          \
  }
/**
 * @warning don't use it directly
 */
#define __MUL(first, second, third, type)     \
  if constexpr (std::is_same_v<type, bool>) { \
    third = first & second;                   \
  } else {                                    \
    third = first * second;                   \
  }
/**
 * @warning don't use it directly
 */
#define __EMUL(first, second, type)           \
  if constexpr (std::is_same_v<type, bool>) { \
    first &= second;                          \
  } else {                                    \
    first *= second;                          \
  }
/**
 * @warning don't use it directly
 */
#define __DIV(first, second, third, type)     \
  if constexpr (std::is_same_v<type, bool>) { \
    third = first ^ second;                   \
  } else {                                    \
    third = first / second;                   \
  }
/**
 * @warning don't use it directly
 */
#define __EDIV(first, second, type)           \
  if constexpr (std::is_same_v<type, bool>) { \
    first ^= second;                          \
  } else {                                    \
    first /= second;                          \
  }
/**
 * @brief add
 * @param first the first operand
 * @param second the second operand
 * @param third the answer
 * @param type the type of the operands
 */
#define ADD(first, second, third, type) __ADD(first, second, third, type);
/**
 * @brief add
 * @param first the first operand
 * @param second the second operand
 * @param type the type of the operands
 */
#define EADD(first, second, type) __EADD(first, second, type);

/**
 * @brief sub
 * @param first the first operand
 * @param second the second operand
 * @param third the answer
 * @param type the type of the operands
 */
#define MNS(first, second, third, type) __MNS(first, second, third, type);
/**
 * @brief sub
 * @param first the first operand
 * @param second the second operand
 * @param type the type of the operands
 */
#define EMNS(first, second, type) __EMNS(first, second, type);

/**
 * @brief mul
 * @param first the first operand
 * @param second the second operand
 * @param third the answer
 * @param type the type of the operands
 */
#define MUL(first, second, third, type) __MUL(first, second, third, type);
/**
 * @brief mul
 * @param first the first operand
 * @param second the second operand
 * @param type the type of the operands
 */
#define EMUL(first, second, type) __EMUL(first, second, type);

/**
 * @brief div
 * @param first the first operand
 * @param second the second operand
 * @param third the answer
 * @param type the type of the operands
 */
#define DIV(first, second, third, type) __DIV(first, second, third, type);
/**
 * @brief div
 * @param first the first operand
 * @param second the second operand
 * @param type the type of the operands
 */
#define EDIV(first, second, type) __EDIV(first, second, type);

namespace basic_math {
constexpr size_t PRINT_ACCURACY = 3;
constexpr FloatType EXPRISION = static_cast<FloatType>(std::exp(1.0F));

class BasicSupport {
 public:
  /**
   * @warning don't use it directly
   */
  static std::mt19937 generator_;
  /**
   * @warning don't use it directly
   */
  static inline void init() noexcept {
    BasicSupport::generator_.seed(static_cast<unsigned long long>(time(0)));
    LOG("S:Basic init");
    return;
  }
};
/**
 * @return the number of digits in an unsigned integer.
 * @param alpha The number to determine the number of digits in
 * @return The number of digits in alpha, only return number of digits before
 * the decimal point
 * @throws None
 */
template <typename U>
inline size_t intDigits(U const& __alpha) noexcept(basic_math::support<U>) {
  LOG("C:intDigits");
  if constexpr (std::is_same_v<U, bool>) return size_t(1);
  if (__alpha > -1 && __alpha < 1) return size_t(1);
  return static_cast<size_t>(std::floor(std::log10(std::abs(__alpha)) + 1));
}
/**
 * Generates a random number within the range [min, max] based on the input
 * type.
 *
 * @param min The minimum value of the range
 * @param max The maximum value of the range
 *
 * @return A random number within the specified range based on the input type
 * @throw if the type isn't support, throw.
 */
template <typename U>
inline U random(U const& __min,
                U const& __max) noexcept(basic_math::support<U>) {
  if constexpr (std::is_same_v<bool, U>) {
    LOG("C:random<bool>");
    std::uniform_int_distribution<int> dist(0, 1);
    return static_cast<bool>(dist(BasicSupport::generator_));
  } else if constexpr (std::is_integral_v<U>) {
    LOG("C:random<intergral>");
    std::uniform_int_distribution<U> dist(__min, __max);
    return dist(BasicSupport::generator_);
  } else if constexpr (std::is_floating_point_v<U>) {
    LOG("C:random<float_point>");
    std::uniform_real_distribution<U> dist(__min, __max);
    return dist(BasicSupport::generator_);
  } else {
    LOG("B:unsupport type for random");
    throw system_message::Error("unsupport type for random\n");
    U ans;
    return ans;
  }
}
}  // namespace basic_math
namespace storage {
class StoryBase {
 public:
  /**
   * @brief base constructor
   */
  StoryBase() {}
  /**
   * @brief base destructor
   */
  virtual ~StoryBase() {}
  /**
   * @brief size
   * @return the size
   */
  inline virtual size_t size() const noexcept = 0;
  /**
   * @brief capacity
   * @return the memorysize
   */
  inline virtual size_t capacity() const noexcept = 0;
};
}  // namespace ling_lg
/**
 * @warning don't use it
 */
#define BASIC_CON basic_math::BasicSupport::init();

#endif