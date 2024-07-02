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
  bool signUp(int size, std::shared_ptr<T> data);

  template <typename T>
  bool modify(int newSize, std::shared_ptr<T> data);

  template <typename T>
  bool release(std::shared_ptr<T> data);

  unsigned long long getTotalUsage() const;
  int getBlockCount() const;
  void displayUsage() const;

 private:
  struct MemoryBlock {
    int size;
    MemoryType type;
  };

  unsigned long long totalUsage = 0;
  int blockCount = 0;
  std::unordered_map<void*, MemoryBlock> memoryMap;
  mutable std::mutex mtx;

  MemoryType getMemoryType(std::type_index typeIdx) const;
};
}  // namespace memory_maintainer

#endif  // MEMORY_H