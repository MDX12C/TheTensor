#include "define.hpp"
#ifndef LOG_H
#define LOG_H 1
#include <chrono>
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <mutex>
#include <queue>
#include <thread>

/**
 * the system space
 */
namespace log_file {
#define CHECK_O(X)                               \
  {                                              \
    if (!X.is_open()) {                          \
      throw system_message::Error("open fail!"); \
    }                                            \
  }
#define CHECK_C(X)                                \
  {                                               \
    if (X.is_open()) {                            \
      throw system_message::Error("close fail!"); \
    }                                             \
  }
constexpr int CARRY = 16;
constexpr int FILE_DIGITS = 2;
constexpr int FORMAT_LENTH = 256;
constexpr int BUFFER_LENTH = 512;
constexpr int DOCS_WIDE = 15;
constexpr int WAIT_TIME = 10;
constexpr int WHOLE_NUMBER = std::pow(CARRY, FILE_DIGITS);

extern const char* const CARRY_ARRAY;
extern std::string TEMP_STRING;
inline int8_t prioirty(const char* const& alpha) {
  if (alpha[0] == 'L') {
    if ((alpha[1] == '1') || (alpha[1] == '2')) return int8_t(0);
    if ((alpha[1] == '3') || (alpha[1] == '4')) return int8_t(8);
    if (alpha[1] == '5') return int8_t(-1);
  }
  if (alpha[0] == 'S') return int8_t(3);
  if (alpha[0] == 'B') return int8_t(4);
  if (alpha[0] == 'E') return int8_t(5);
  if (alpha[0] == 'C') return int8_t(7);
  return int8_t(3);
}

struct CharCompare {
  bool operator()(const char* const& a, const char* const& b) {
    return prioirty(b) < prioirty(a);
  }
};
/**
 * the support class, please don't use it directly
 */
class LogSupport {
 public:
  /**
   * L1: check logWorker is alive, from checkAlive
   * L2: answer logWorker is alive, from logWorker
   * L3: apply to end, from logPack
   * L4: check the end, from logWorker
   * L5: call force shut down
   */
  static std::priority_queue<char*,std::vector<char*>,CharCompare> taskQueue;
  static char* mainBuffer;
  static char* formatBuffer;
  static std::mutex queueLock;
  /**
   * @brief the worker function, please don't use it directly
   */
  static void logWorker(std::filesystem::path fileLocation) {
    std::ofstream writer;
    writer.open(fileLocation, std::ios::binary | std::ios::app);
    CHECK_O(writer);
    char* workSpace;
    while (true) {
      LogSupport::queueLock.lock();
      if (LogSupport::taskQueue.empty()) {
        LogSupport::queueLock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_TIME));
      } else {
        workSpace = LogSupport::taskQueue.top();
        LogSupport::taskQueue.pop();
        LogSupport::queueLock.unlock();
        if (workSpace[0] == 'L') {
          if (workSpace[1] == '1') {
            delete[] workSpace;
            workSpace = new char[4];
            sprintf(workSpace, "L2");
            LogSupport::queueLock.lock();
            LogSupport::taskQueue.emplace(workSpace);
            LogSupport::queueLock.unlock();
            workSpace = nullptr;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            continue;
          } else if (workSpace[1] == '3') {
            delete[] workSpace;
            break;
          } else if (workSpace[1] == '5') {
            delete[] workSpace;
            return;
          }
        }
        for (unsigned int i = 0; i < std::strlen(workSpace); i++)
          writer.put(workSpace[i]);
        for (int i = 0; i < DOCS_WIDE; i++) writer.put('-');
        writer.put('\n');
        delete[] workSpace;
      }
    }
    LogSupport::queueLock.lock();
    while (!LogSupport::taskQueue.empty()) {
      workSpace = LogSupport::taskQueue.top();
      LogSupport::taskQueue.pop();
      for (unsigned int i = 0; i < std::strlen(workSpace); i++)
        writer.put(workSpace[i]);
      for (int i = 0; i < DOCS_WIDE; i++) writer.put('-');
      writer.put('\n');
      delete[] workSpace;
    }
    writer.close();
    CHECK_C(writer);
    workSpace = new char[4];
    sprintf(workSpace, "L4");
    LogSupport::taskQueue.emplace(workSpace);
    LogSupport::queueLock.unlock();
    workSpace = nullptr;
    return;
  }
};

/**
 * the init function, please don't use it directly
 */
inline void logInit() {
  std::ifstream reader;
  std::ofstream writer;
  std::time_t timer = std::time(NULL);
  std::map<char, int> carryMap;
  for (int i = 0; i < 10; i++)
    carryMap.insert(std::pair(static_cast<char>(48 + i), i));
  for (int i = 0; i < CARRY - 10; i++)
    carryMap.insert(std::pair(static_cast<char>(65 + i), i + 10));
  std::string filename = "../log/log_00.txt";
  std::filesystem::path fileLocation =
      std::filesystem::current_path() / filename;
  int serial = 0, temp, serialTemp;
  reader.open(fileLocation, std::ios::binary);
  CHECK_O(reader);
  for (auto i = 0; i < FILE_DIGITS; i++) {
    serial *= CARRY;
    serial += carryMap[reader.get()];
  }
  serial++;
  serial %= WHOLE_NUMBER;
  if (serial == 0) serial++;
  serialTemp = serial;
  reader.close();
  CHECK_C(reader);
  writer.open(fileLocation, std::ios::binary | std::ios::trunc);
  CHECK_O(writer);
  for (int i = FILE_DIGITS - 1; i >= 0; i--) {
    temp = static_cast<int>(std::pow(CARRY, i));
    writer.put(CARRY_ARRAY[serialTemp / temp]);
    serialTemp %= temp;
  }
  writer.close();
  CHECK_C(writer);
  serialTemp = serial;
  for (int i = 10 + FILE_DIGITS; i > 10; i--) {
    filename[i] = CARRY_ARRAY[serialTemp % CARRY];
    serialTemp /= CARRY;
  }
  fileLocation = std::filesystem::current_path() / filename;
  writer.open(fileLocation, std::ios::binary);
  CHECK_O(writer);
  LogSupport::mainBuffer = new char[BUFFER_LENTH];
  sprintf(LogSupport::mainBuffer, "run at : %s", std::ctime(&timer));
  writer.write(LogSupport::mainBuffer, std::strlen(LogSupport::mainBuffer));
  writer.close();
  CHECK_C(writer);
  LogSupport::mainBuffer = nullptr;
  while (!LogSupport::taskQueue.empty()) LogSupport::taskQueue.pop();
  std::thread taskThread = std::thread(LogSupport::logWorker, fileLocation);
  taskThread.detach();
  LogSupport::formatBuffer = new char[FORMAT_LENTH];
  return;
}
/**
 * the pack function, please don't use it directly
 */
inline void logPack(bool __force = false) {
  if (__force) {
    LogSupport::mainBuffer = new char[4];
    sprintf(LogSupport::mainBuffer, "L5");
    LogSupport::queueLock.lock();
    LogSupport::taskQueue.emplace(LogSupport::mainBuffer);
    LogSupport::queueLock.unlock();
    LogSupport::mainBuffer = nullptr;
    printf("~~~~~\nshut down in 2s\n~~~~~\n");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    LogSupport::queueLock.lock();
    while (!LogSupport::taskQueue.empty()) {
      delete[] LogSupport::taskQueue.top();
      LogSupport::taskQueue.pop();
    }
    LogSupport::queueLock.unlock();
    delete[] LogSupport::formatBuffer;
    return;
  } else {
    LogSupport::mainBuffer = new char[4];
    sprintf(LogSupport::mainBuffer, "L3");
    LogSupport::queueLock.lock();
    LogSupport::taskQueue.emplace(LogSupport::mainBuffer);
    LogSupport::queueLock.unlock();
    LogSupport::mainBuffer = nullptr;
    printf("~~~~~\nplease wait 3s\n~~~~~\n");
    std::this_thread::sleep_for(std::chrono::seconds(3));
    while (true) {
      LogSupport::queueLock.lock();
      if (!LogSupport::taskQueue.empty()) {
        LogSupport::mainBuffer = LogSupport::taskQueue.top();
        LogSupport::queueLock.unlock();
        if ((LogSupport::mainBuffer[0] == 'L') &&
            (LogSupport::mainBuffer[1] == '4')) {
          delete[] LogSupport::mainBuffer;
          break;
        }
      } else {
        LogSupport::queueLock.unlock();
        printf("the log is still being writing\n");
        std::this_thread::sleep_for(std::chrono::seconds(1));
      }
    }
    LogSupport::queueLock.lock();
    while (!LogSupport::taskQueue.empty()) LogSupport::taskQueue.pop();
    LogSupport::queueLock.unlock();
    delete[] LogSupport::formatBuffer;
  }
  return;
}

inline bool checkAlive() noexcept {
  char* alpha = new char[4];
  sprintf(alpha, "L1");
  LogSupport::queueLock.lock();
  LogSupport::taskQueue.emplace(alpha);
  LogSupport::queueLock.unlock();
  alpha = nullptr;
  printf("\n~~~~~\nplease wait 1s\n~~~~~\n");
  std::this_thread::sleep_for(std::chrono::seconds(1));
  while (true) {
    LogSupport::queueLock.lock();
    if (LogSupport::taskQueue.empty()) return false;
    alpha = LogSupport::taskQueue.top();
#if __DEBUG_MODE__
    printf("%s\n", alpha);
#endif
    if (alpha[0] == 'L') {
      if (alpha[1] == '2') {
        LogSupport::taskQueue.pop();
        LogSupport::queueLock.unlock();
        delete[] alpha;
        return true;
      } else {
        LogSupport::queueLock.unlock();
        alpha = nullptr;
        std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_TIME * 5));
      }
    } else {
      LogSupport::queueLock.unlock();
      alpha = nullptr;
      std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_TIME * 5));
    }
  }
}
inline void cut(const char* const& __str) noexcept {
  TEMP_STRING = __str;
  TEMP_STRING = TEMP_STRING.substr(TEMP_STRING.find_last_of('/') + 1);
}
}  // namespace log_file

/**
 * the relay define, please use LOG()
 */
#define __LOG_MAKER(FMT, ...)                                                  \
  do {                                                                         \
    log_file::cut(__FILE__);                                                   \
    sprintf(log_file::LogSupport::formatBuffer, FMT, ##__VA_ARGS__);           \
    log_file::LogSupport::mainBuffer = new char[log_file::BUFFER_LENTH];       \
    sprintf(log_file::LogSupport::mainBuffer, "%s\n%s:%d\n",      \ 
          log_file::LogSupport::formatBuffer,                                  \
            log_file::TEMP_STRING.c_str(), __LINE__);                          \
    log_file::LogSupport::queueLock.lock();                                    \
    log_file::LogSupport::taskQueue.emplace(log_file::LogSupport::mainBuffer); \
    log_file::LogSupport::queueLock.unlock();                                  \
  } while (false);

#define __LOG                                                               \
  printf("\n++++++++++\n%s : %d\n%s\n++++++++++\n", __FUNCTION__, __LINE__, \
         __FILE__);

#if __SPEED_MODE__
#define LOG(__FORMAT, ...)                                      \
  if constexpr ((__FORMAT[0] == 'B') || (__FORMAT[0] == 'E') || \
                (__FORMAT[0] == 'S')) {                         \
    __LOG_MAKER(__FORMAT, ##__VA_ARGS__);                       \
  }
#else
/**
 * @brief write the log in the logfile
 * @param _FORMAT the format string.
 * The first character of the string is limited!!
 * @param C check: check for value or memory, also used as check work process
 * @param E error: happened error, but had solved
 * @param B bug: happened the unexpect bug and can't solve it
 * @param S system message: the reserved word, use it carefully
 */
#define LOG(__FORMAT, ...) __LOG_MAKER(__FORMAT, ##__VA_ARGS__)
#endif
/**
 * the initalize of the logfile, please use it in the front of main function
 */
#define LOG_CON                                                                \
  do {                                                                         \
    log_file::logInit();                                                       \
    log_file::LogSupport::mainBuffer = new char[log_file::BUFFER_LENTH];       \
    log_file::cut(__FILE__);                                                   \
    sprintf(log_file::LogSupport::mainBuffer,                                  \
            "code version : %s\nrun by : %s\n", __TIMESTAMP__,                 \
            log_file::TEMP_STRING.c_str());                                    \
    log_file::LogSupport::queueLock.lock();                                    \
    log_file::LogSupport::taskQueue.emplace(log_file::LogSupport::mainBuffer); \
    log_file::LogSupport::queueLock.unlock();                                  \
  } while (false);

#define LOG_DES(X) log_file::logPack(X);
#endif