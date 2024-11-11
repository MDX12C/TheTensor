#ifndef LOG_CC
#define LOG_CC 1
#include "log.hpp"
#if LOG_H
namespace log_file {
const char* const CARRY_ARRAY = "0123456789ABCDEF";
std::queue<char*> LogSupport::taskQueue;
char* LogSupport::mainBuffer = nullptr;
char* LogSupport::formatBuffer = nullptr;
std::mutex LogSupport::queueLock;

}  // namespace log_file
#endif
#endif