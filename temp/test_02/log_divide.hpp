#ifndef LOG_DIVIDE_H
#define LOG_DIVIDE_H 1
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

#define DEBUG

/**
 * the system space
 */
namespace log_file {
#define CHECK_O(X)                               \
  {                                              \
    if (!X.is_open()) {                          \
      throw std::invalid_argument("open fail!"); \
    }                                            \
  }
#define CHECK_C(X)                                \
  {                                               \
    if (X.is_open()) {                            \
      throw std::invalid_argument("close fail!"); \
    }                                             \
  }
constexpr int CARRY = 16;
constexpr int FILE_DIGITS = 5;
constexpr int FORMAT_LENTH = 256;
constexpr int BUFFER_LENTH = 512;
constexpr int DOCS_WIDE = 50;
constexpr int WAIT_TIME = 150;
constexpr int WHOLE_NUMBER = std::pow(CARRY, FILE_DIGITS);

extern const char* const CARRY_ARRAY;

/**
 * the support class, please don't use it directly
 */
class LogSupport {
 public:
  static std::queue<char*> taskQueue;
  static char* mainBuffer;
  static char* formatBuffer;
  static std::mutex queueLock;

  static void worker(std::filesystem::path fileLocation) {
#ifdef DEBUG
    printf("worker,file is:\n%s\n", fileLocation.string().c_str());
#endif
    std::ofstream writer;
    writer.open(fileLocation, std::ios::binary | std::ios::app);
    CHECK_O(writer);
    char* workSpace;
#ifdef DEBUG
    printf("start\n");
#endif
    while (true) {
      LogSupport::queueLock.lock();
      if (LogSupport::taskQueue.empty()) {
        LogSupport::queueLock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_TIME));
      } else {
#ifdef DEBUG
        printf("not empty\n");
#endif
        workSpace = LogSupport::taskQueue.front();
#ifdef DEBUG
        printf("pop\n");
#endif
        LogSupport::taskQueue.pop();
        LogSupport::queueLock.unlock();
#ifdef DEBUG
        printf("pop success\n");
#endif
        if (static_cast<int>(workSpace[0]) == 65) {
#ifdef DEBUG
          printf("All Pass\n");
#endif
          delete[] workSpace;
          writer.close();
          CHECK_C(writer);
          workSpace = new char[3];
          sprintf(workSpace, "F\n");
          LogSupport::queueLock.lock();
          LogSupport::taskQueue.push(workSpace);
          LogSupport::queueLock.unlock();
          workSpace = nullptr;
#ifdef DEBUG
          printf("worker end\n");
#endif
          return;
        }
#ifdef DEBUG
        printf("strlen=%ld ,str:\n%s\n-\n", std::strlen(workSpace), workSpace);
#endif
        for (auto i = 0; i < std::strlen(workSpace); i++)
          writer.put(workSpace[i]);
        for (auto i = 0; i < DOCS_WIDE; i++) writer.put('-');
        writer.put('\n');
        delete[] workSpace;
      }
    }
    return;
  }
};

}  // namespace log_file

/**
 * the relay define, please use LOG()
 */
#define __LOG_MAKER(FMT, ...)                                               \
  do {                                                                      \
    sprintf(log_file::LogSupport::formatBuffer, FMT, ##__VA_ARGS__);        \
    log_file::LogSupport::mainBuffer = new char[log_file::BUFFER_LENTH];    \
    sprintf(log_file::LogSupport::mainBuffer,                               \
            "%s\nline: %d function: %s\nfile: %s\n",      \ 
          log_file::LogSupport::formatBuffer,                               \
            __LINE__, __FUNCTION__, __FILE__);                              \
    log_file::LogSupport::queueLock.lock();                                 \
    log_file::LogSupport::taskQueue.push(log_file::LogSupport::mainBuffer); \
    log_file::LogSupport::queueLock.unlock();                               \
    log_file::LogSupport::mainBuffer = nullptr;                             \
  } while (false);
/**
 * @brief write the log in the logfile
 * @param _FORMAT the format string.
 * The first character of the string is limited!!
 * @param C check: check for value or memory, also used as check work process
 * @param E error: happened error, but had solved
 * @param B bug: happened the unexpect bug and can't solve it
 * @param AP all pass: the reserved word, don't use it
 * @param FN finish: the reserved word, don't use it
 */
#define LOG(_FORMAT, ...) __LOG_MAKER(_FORMAT, ##__VA_ARGS__)
/**
 * the initalize of the logfile, please use it in the front of main function
 */
#define LOG_INIT                                                            \
  do {                                                                      \
    log_file::LogSupport::mainBuffer = new char[log_file::BUFFER_LENTH];    \
    sprintf(log_file::LogSupport::mainBuffer, "run by : %s\n", __FILE__);   \
    log_file::LogSupport::queueLock.lock();                                 \
    log_file::LogSupport::taskQueue.push(log_file::LogSupport::mainBuffer); \
    log_file::LogSupport::queueLock.unlock();                               \
    log_file::LogSupport::mainBuffer = nullptr;                             \
  } while (false);

#endif  // LOG_DIVIDE_H