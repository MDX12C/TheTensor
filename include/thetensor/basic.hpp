#include "define.hpp"
#ifndef BASIC_H
#define BASIC_H 1

#include "log.hpp"
#include "random.hpp"
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
    first |= second;                          \
  } else {                                    \
    first += second;                          \
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
#define ADD(first, second, third, type) \
  __ADD((first), (second), (third), type);
/**
 * @brief add
 * @param first the first operand
 * @param second the second operand
 * @param type the type of the operands
 */
#define EADD(first, second, type) __EADD((first), (second), type);

/**
 * @brief sub
 * @param first the first operand
 * @param second the second operand
 * @param third the answer
 * @param type the type of the operands
 */
#define MNS(first, second, third, type) \
  __MNS((first), (second), (third), type);
/**
 * @brief sub
 * @param first the first operand
 * @param second the second operand
 * @param type the type of the operands
 */
#define EMNS(first, second, type) __EMNS((first), (second), type);

/**
 * @brief mul
 * @param first the first operand
 * @param second the second operand
 * @param third the answer
 * @param type the type of the operands
 */
#define MUL(first, second, third, type) \
  __MUL((first), (second), (third), type);
/**
 * @brief mul
 * @param first the first operand
 * @param second the second operand
 * @param type the type of the operands
 */
#define EMUL(first, second, type) __EMUL((first), (second), type);

/**
 * @brief div
 * @param first the first operand
 * @param second the second operand
 * @param third the answer
 * @param type the type of the operands
 */
#define DIV(first, second, third, type) \
  __DIV((first), (second), (third), type);
/**
 * @brief div
 * @param first the first operand
 * @param second the second operand
 * @param type the type of the operands
 */
#define EDIV(first, second, type) __EDIV((first), (second), type);
namespace system_message {
class Status {
 private:
  static size_t blocks_;
  static std::string progress_;

 public:
  /**
   * @brief refresh Status
   * @param __progress the new status
   * @return the sequence
   * @throw none
   */
  static inline size_t refresh(std::string const& __progress,
                               bool const& __prt = false,
                               std::ostream& __os = std::cout) noexcept {
    LOG("S:progress:\n%s", __progress.c_str());
    Status::progress_ = __progress;
    Status::blocks_++;
    if (__prt) Status::print(__os);
    return Status::blocks_;
  }
  /**
   * @brief refresh Status
   * @param __progress the new status
   * @return the sequence
   * @throw none
   */
  static inline size_t refresh(const char* const& __progress,
                               bool const& __prt = false,
                               std::ostream& __os = std::cout) noexcept {
    LOG("S:progress:\n%s", __progress);
    Status::progress_ = __progress;
    Status::blocks_++;
    if (__prt) Status::print(__os);
    return Status::blocks_;
  }
  /**
   * @return the sequence now
   * @throw none
   */
  static inline size_t blocks() noexcept { return Status::blocks_; }
  /**
   * @return the progress now
   * @throw none
   */
  static inline std::string progress() noexcept { return Status::progress_; }
  /**
   * @warning don't use it directly
   */
  static inline void init() {
    LOG("S:system init");
    Status::blocks_ = 0;
    Status::progress_ = "Start";
    return;
  }
  static inline void print(std::ostream& __os = std::cout) noexcept {
    __os << '/';
    for (size_t i = 0; i < log_file::DOCS_WIDE * 3; i++) __os << '-';
    __os << "\\\nBlock sequence: " << Status::blocks_
         << " \nProgress: " << Status::progress_ << "\n\\";
    for (size_t i = 0; i < log_file::DOCS_WIDE * 3; i++) __os << '-';
    __os << "/\n";
    return;
  }
  /**
   * @brief announce the message
   * @param __it the content
   * @param __os the ostream, std::cout in default
   * @throw none
   */
  static inline void announce(std::string const& __it,
                              std::ostream& __os = std::cout) noexcept {
    for (size_t i = 0; i < log_file::DOCS_WIDE * 3; i++) __os << '/';
    __os << '\n' << __it << '\n';
    for (size_t i = 0; i < log_file::DOCS_WIDE * 3; i++) __os << '\\';
    __os << '\n';
    return;
  }
  /**
   * @brief announce the message
   * @param __it the content
   * @param __os the ostream, std::cout in default
   * @throw none
   */
  static inline void announce(const char* const& __it,
                              std::ostream& __os = std::cout) noexcept {
    for (size_t i = 0; i < log_file::DOCS_WIDE * 3; i++) __os << '/';
    __os << '\n' << __it << '\n';
    for (size_t i = 0; i < log_file::DOCS_WIDE * 3; i++) __os << '\\';
    __os << '\n';
    return;
  }
  template <typename T>
  static inline void debug(T& __item, const char* const& __name,
                           std::ostream& __os = std::cout) noexcept {
    __os << "\n###debug\n" << __name << "=\n" << __item << "\n########\n";
    return;
  }
  static inline void pause() noexcept {
    std::cout << "==========\npause Enter to continue\n==========\n";
    std::cin.get();
    return;
  }
};
}  // namespace system_message
namespace basic_math {
constexpr size_t PRINT_ACCURACY = 3;
constexpr FloatType EXPRISION = std::numbers::e_v<FloatType>;

/**
 * @return the number of digits in an unsigned integer.
 * @param alpha The number to determine the number of digits in
 * @return The number of digits in alpha, only return number of digits before
 * the decimal point
 * @throws None
 */
template <typename U>
inline size_t intDigits(U const& __alpha) noexcept(support<U>) {
  LOG("C:intDigits");
  if constexpr (support<U>) {
    if constexpr (std::is_same_v<U, bool>) return size_t(1);
    if constexpr (std::is_signed_v<U>) {
      if (__alpha > -1 && __alpha < 1) return size_t(1);
      return static_cast<size_t>(std::floor(std::log10(std::abs(__alpha)) + 1));
    } else {
      if (__alpha < 1) return size_t(1);
      return static_cast<size_t>(std::floor(std::log10(__alpha) + 1));
    }
  } else {
    throw system_message::Error("unsupport type for intDigits");
    return size_t(0);
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
}  // namespace storage
/**
 * @warning don't use it
 */
#define BASIC_CON system_message::Status::init();

#if __DEBUG_MODE__
#define __DEBUG(X)                        \
  do {                                    \
    __LOG;                                \
    system_message::Status::debug(X, #X); \
  } while (false);
#else
#define __DEBUG(X)
#endif
#define DEBUG(X) __DEBUG(X)
#endif