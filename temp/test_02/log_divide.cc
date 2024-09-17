#include "log_divide.hpp"

namespace log_file {
const char* const CARRY_ARRAY = "0123456789ABCDEF";
std::queue<char*> LogSupport::taskQueue;
char* LogSupport::mainBuffer = nullptr;
char* LogSupport::formatBuffer = nullptr;
std::mutex LogSupport::queueLock;

}  // namespace log_file