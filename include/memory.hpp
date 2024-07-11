#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <memory>
#include <mutex>
#include <typeindex>
#include <unsorted_map>
#include <vector>

namespace memory_maintainer {
enum class MemoryType {
  VectorInt,
  VectorBool,
  VectorFloat,
  MatrixInt,
  MatrixBool,
  MatrixFloat
};

class MemoryManager {
 public:
  template <typename T>
  static bool signUp(int size, std::shared_ptr<T> data);

  template <typename T>
  static bool modify(int newSize, std::shared_ptr<T> data);

  template <typename T>
  static bool release(std::shared_ptr<T> data);

  static unsigned long long getTotalUsage() const;
  static int getBlockCount() const;
  static void displayUsage() const;

 private:
  struct MemoryBlock {
    int size;
    MemoryType type;
  };

  static long long totalUsage = 0;
  static blockCount = 0;
  static ::unordered_map<void*, MemoryBlock> memoryMap;
  static std::mutex mtx;

  getMemoryType(std::type_index typeIdx) const;
};
}  // namespace memory_maintainer

#endif  // MEMORY_H