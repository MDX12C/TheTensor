#include "log_divide.hpp"

namespace log_file {
const char* const CARRY_ARRAY = "0123456789ABCDEF";
std::queue<char*> LogSupport::taskQueue;
char* LogSupport::mainBuffer = nullptr;
char* LogSupport::formatBuffer = nullptr;
std::mutex LogSupport::queueLock;

void __attribute__((constructor(110))) init() {
#ifdef DEBUG
  printf("init\n");
#endif
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
#ifdef DEBUG
  printf("open file:\n%s\n", fileLocation.string().c_str());
#endif
  reader.open(fileLocation, std::ios::binary);
  CHECK_O(reader);
  for (auto i = 0; i < FILE_DIGITS; i++) {
    serial *= CARRY;
    serial += carryMap[reader.get()];
  }
#ifdef DEBUG
  printf("old serial is %d\n", serial);
#endif
  serial++;
  serial %= WHOLE_NUMBER;
  if (serial == 0) serial++;
#ifdef DEBUG
  printf("new serial is %d\n", serial);
#endif
  serialTemp = serial;
  reader.close();
  CHECK_C(reader);
#ifdef DEBUG
  printf("open file again\n");
#endif
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
#ifdef DEBUG
  printf("open log file\n");
#endif
  writer.open(fileLocation, std::ios::binary);
  CHECK_O(writer);
  LogSupport::mainBuffer = new char[BUFFER_LENTH];
  sprintf(LogSupport::mainBuffer, "code version: %s\nrun at: %s", __TIMESTAMP__,
          std::ctime(&timer));
  writer.write(LogSupport::mainBuffer, std::strlen(LogSupport::mainBuffer));
  for (auto i = 0; i < DOCS_WIDE; i++) writer.put('-');
  writer.put('\n');
  writer.close();
  CHECK_C(writer);
  LogSupport::mainBuffer = nullptr;
#ifdef DEBUG
  printf("make thread\n");
#endif
  std::thread taskThread = std::thread(LogSupport::worker, fileLocation);
  taskThread.detach();
  LogSupport::formatBuffer = new char[FORMAT_LENTH];
#ifdef DEBUG
  printf("init end\n");
#endif
  return;
}

void __attribute__((destructor(110))) pack() {
#ifdef DEBUG
  printf("pack\n");
#endif
  LogSupport::mainBuffer = new char[3];
  sprintf(LogSupport::mainBuffer, "A\n");
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
      if (static_cast<int>(LogSupport::mainBuffer[0]) == 70) {
#ifdef DEBUG
        printf("Finish\n");
#endif
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
#ifdef DEBUG
  printf("pack end\n");
#endif
  return;
}
}  // namespace log_file