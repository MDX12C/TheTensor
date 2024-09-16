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
constexpr int FORMAT_LENTH = 128;
constexpr int BUFFER_LENTH = 256;
constexpr int DOCS_WIDE = 50;
constexpr int WAIT_TIME = 150;
constexpr int WHOLE_NUMBER = std::pow(CARRY, FILE_DIGITS);

static const char* const CARRY_ARRAY = "0123456789ABCDEF";

/**
 * the support class, please don't use it directly
 */
class LogSupport {
 public:
  static std::queue<char*> taskQueue;
  static char* mainBuffer;
  static char* formatBuffer;
  static std::mutex queueLock;

 private:
  static void worker(std::filesystem::path fileLocation) {
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
        workSpace = LogSupport::taskQueue.front();
        LogSupport::taskQueue.pop();
        LogSupport::queueLock.unlock();
        if (workSpace[0] == 'A' && workSpace[1] == 'P') {
          delete[] workSpace;
          writer.close();
          CHECK_C(writer);
          workSpace = new char[3];
          sprintf(workSpace, "FN");
          LogSupport::queueLock.lock();
          LogSupport::taskQueue.push(workSpace);
          LogSupport::queueLock.unlock();
          workSpace = nullptr;
          return;
        }
        writer.write(workSpace, std::strlen(workSpace));
        for (auto i = 0; i < DOCS_WIDE; i++) writer.put('-');
        writer.put('\n');
        delete[] workSpace;
      }
    }
    return;
  }
  static void __attribute__((constructor(110))) init() {
    std::ifstream reader;
    std::ofstream writer;
    while (!LogSupport::taskQueue.empty()) LogSupport::taskQueue.pop();
    std::time_t timer = std::time(NULL);
    std::map<char, int> carryMap;
    for (int i = 0; i < 10; i++)
      carryMap.insert(std::pair(static_cast<char>(48 + i), i));
    for (int i = 0; i < CARRY - 10; i++)
      carryMap.insert(std::pair(static_cast<char>(65 + i), i + 10));
    std::string filename = "log/log_00000.txt";
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
    for (int i = 12; i > 12 - FILE_DIGITS; i--) {
      filename[i] = CARRY_ARRAY[serialTemp % CARRY];
      serialTemp /= CARRY;
    }
    fileLocation = std::filesystem::current_path() / filename;
    writer.open(fileLocation, std::ios::binary);
    CHECK_O(writer);
    LogSupport::mainBuffer = new char[BUFFER_LENTH];
    sprintf(LogSupport::mainBuffer, "code version: %s\nrun at: %s",
            __TIMESTAMP__, std::ctime(&timer));
    writer.write(LogSupport::mainBuffer, std::strlen(LogSupport::mainBuffer));
    for (auto i = 0; i < DOCS_WIDE; i++) writer.put('-');
    writer.put('\n');
    writer.close();
    CHECK_C(writer);
    LogSupport::mainBuffer = nullptr;
    std::thread taskThread = std::thread(LogSupport::worker, fileLocation);
    taskThread.detach();
    LogSupport::formatBuffer = new char[FORMAT_LENTH];
    return;
  }
  static void __attribute__((destructor(110))) pack() {
    LogSupport::mainBuffer = new char[3];
    sprintf(LogSupport::mainBuffer, "AP");
    LogSupport::queueLock.lock();
    LogSupport::taskQueue.push(LogSupport::mainBuffer);
    LogSupport::queueLock.unlock();
    LogSupport::mainBuffer = nullptr;
    printf("#####\nplease wait 3s\n");
    std::this_thread::sleep_for(std::chrono::seconds(3));
    while (true) {
      LogSupport::queueLock.lock();
      if (!LogSupport::taskQueue.empty()) {
        LogSupport::mainBuffer = LogSupport::taskQueue.front();
        LogSupport::taskQueue.pop();
        LogSupport::queueLock.unlock();
        if (LogSupport::mainBuffer[0] == 'F' &&
            LogSupport::mainBuffer[1] == 'N') {
          delete[] LogSupport::mainBuffer;
          break;
        }
      } else {
        LogSupport::queueLock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_TIME * 3));
      }
    }
    LogSupport::queueLock.lock();
    while (!LogSupport::taskQueue.empty()) LogSupport::taskQueue.pop();
    LogSupport::queueLock.unlock();
    delete[] LogSupport::formatBuffer;
    return;
  }
};
std::queue<char*> LogSupport::taskQueue;
char* LogSupport::mainBuffer = nullptr;
char* LogSupport::formatBuffer = nullptr;
std::mutex LogSupport::queueLock;
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

void hello() {
  LOG("C:hello\n");
  return;
}

signed main() {
  LOG_INIT;
  int a = 1203;
  std::cout << "a= " << a << '\n';
  LOG("C:a= %d\n", a);
  std::cin >> a;
  char c[100];
  std::cin.get();
  std::cin.getline(c, 80);
  std::cout << "\na= " << a << "\nc= " << c << '\n';
  LOG("C:a= %d\nc= %s\n", a, c);
  hello();
  LOG("C:all pass\n");
  return 0;
}