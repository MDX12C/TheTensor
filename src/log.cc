#include "thetensor/log.hpp"

#include "thetensor/define.hpp"
#if LOG_HH
namespace log_file {
const char* const CARRY_ARRAY = "0123456789ABCDEF";
std::string TEMP_STRING;
std::priority_queue<char*, std::vector<char*>, CharCompare>
    LogSupport::taskQueue;
char* LogSupport::mainBuffer = nullptr;
char* LogSupport::formatBuffer = nullptr;
std::mutex LogSupport::queueLock;

}  // namespace log_file
#endif
