#include "define.hpp"
#ifndef RANDOM_HH
#define RANDOM_HH 1
#include "log.hpp"

namespace basic_math {
class RandomSupport {
 public:
  /**
   * @warning don't use it directly
   */
  static std::mt19937_64 generator_;
  /**
   * @warning don't use it directly
   */
  static inline void init() noexcept {
    LOG("S:Random init");
#if __LIMIT_MODE__
    RandomSupport::generator_.seed(static_cast<unsigned long long>(time(0)));
#else
    std::random_device rd;
    RandomSupport::generator_.seed(rd());
#endif
    return;
  }
};
/**
 *  Generates a uniformRand number with uniform distribution in specified range.
 *
 * @param min The minimum value of the range
 * @param max The maximum value of the range
 *
 * @return A uniformRand number: interal in [min,max] and floating in [min,max)
 * @throw if the type isn't support, throw.
 */
template <typename U>
inline U uniformRand(U const& __min, U const& __max) noexcept(support<U>) {
  if constexpr (std::is_same_v<bool, U>) {
    LOG("C:uniformRand<bool>");
    std::bernoulli_distribution dist;
    return dist(RandomSupport::generator_);
  } else if constexpr (std::is_integral_v<U>) {
    LOG("C:uniformRand<intergral>");
    std::uniform_int_distribution<U> dist(__min, __max);
    return dist(RandomSupport::generator_);
  } else if constexpr (std::is_floating_point_v<U>) {
    LOG("C:uniformRand<float_point>");
    std::uniform_real_distribution<U> dist(__min, __max);
    return dist(RandomSupport::generator_);
  } else {
    LOG("B:unsupport type for uniformRand");
    throw system_message::Error("unsupport type for uniformRand\n");
    return U();
  }
}
template <typename U>
inline U normalRand(U const& __mean, U const& __variant) {
  if constexpr (std::is_floating_point_v<U>) {
    LOG("C:normalRandom<float_point>");
    std::normal_distribution<U> dist(__mean, __variant);
    return dist(RandomSupport::generator_);
  }
  LOG("B:unsupport type for normalRand");
  throw system_message::Error("unsupport type for normalRand\n");
  return U();
}
template <typename U>
inline U binomialRand(U const& __times, float_t const& __probability) {
  if constexpr (std::is_integral_v<U>) {
    std::binomial_distribution<U> dist(__times, __probability);
    return dist(RandomSupport::generator_);
  }
  LOG("B:unsupport type for binomialRand");
  throw system_message::Error("unsupport type for binomialRand\n");
  return U();
}
}  // namespace basic_math
/**
 * @warning don't use it
 */
#define RANDOM_HH_CON basic_math::RandomSupport::init();
#endif