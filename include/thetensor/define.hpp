#include "define.h"
#ifndef DEFINE_HH
#define DEFINE_HH 1

/*control block*/
#if __F16__
using FloatType = __fp16;
#else
using FloatType = float_t;
#endif

#include <atomic>
#include <cfloat>
#include <chrono>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <numbers>
#include <random>
#include <set>
#include <thread>
#include <type_traits>
#include <utility>

extern inline void endOfMainFunction() noexcept;
namespace basic_math {
template <typename T>
struct the_type_is_absolute_supportable {
  static constexpr bool value =
      (std::is_integral_v<T> | std::is_floating_point_v<T> |
       std::is_same_v<T, bool>);
};
template <typename T>
inline constexpr bool support = the_type_is_absolute_supportable<T>::value;
template <typename T>
struct the_type_is_relative_longer {
  static constexpr bool value =
      (std::is_same_v<T, uint64_t> | std::is_same_v<T, int64_t> |
       std::is_same_v<T, double_t> | sizeof(T) >= 8);
};
template <typename T>
inline constexpr bool longer = the_type_is_relative_longer<T>::value;
}  // namespace basic_math
namespace system_control {
class Error final : public std::exception {
 private:
  std::string message_;

 public:
  /**
   * @brief print the message
   * @param __out the ostream, std::cerr is default
   */
  inline void print(std::ostream& __out = std::cerr) const noexcept {
    for (int i = 0; i < 45; i++) __out << '*';
    __out << '\n' << this->message_ << '\n';
    for (int i = 0; i < 45; i++) __out << '*';
    __out << '\n';
    return;
  }
  /**
   * @return the c-style string of message
   */
  constexpr const char* what() const noexcept override {
    return message_.c_str();
  }
  /**
   * @brief default constructor
   */
  Error() noexcept { this->message_ = "unknown error"; }
  /**
   * @brief init constructor
   * @param __init the init message
   */
  Error(const char* const __init) noexcept { message_ = __init; }
};

}  // namespace system_control

#endif  // DEFINE_HH