#include "thetensor/basic.hpp"

#include "thetensor/define.hpp"
#if BASIC_H
namespace basic_math {
std::mt19937 BasicSupport::generator_;
}  // namespace basic_math
namespace system_message {
size_t Status::blocks_;
std::string Status::progress_;
}  // namespace system_message
#endif
