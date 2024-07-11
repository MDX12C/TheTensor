#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <memory>
#include <mutex>
#include <typeindex>
#include <unordered_map>
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
  template <typename U>
  static bool signUp(int size, std::shared_ptr<U> data);

  template <typename U>
  static bool modify(int newSize, std::shared_ptr<U> data);

  template <typename U>
  static bool release(U* data);

  static unsigned long long getTotalUsage();
  static int getBlockCount();
  static void displayUsage();

 private:
  struct MemoryBlock {
    int size;
    MemoryType type;
  };

  static long long totalUsage;
  static int blockCount;
  static std::unordered_map<void*, MemoryManager::MemoryBlock> memoryMap;
  static std::mutex mtx;

  static MemoryType getMemoryType(std::type_index typeIdx);
};

}  // namespace memory_maintainer

namespace memory_maintainer {
/**
 * Registers a block of memory with the MemoryManager.
 *
 * @param size The size of the memory block in bytes.
 * @param data A shared pointer to the memory block.
 *
 * @return True if the memory block was successfully registered, false
 * otherwise.
 *
 * @throws None.
 */
template <typename U>
bool MemoryManager::signUp(int size, std::shared_ptr<U> data) {
  std::lock_guard<std::mutex> lock(mtx);

  if (size <= 0 || !data) return false;

  void* rawPtr = data.get();
  MemoryType type = getMemoryType(typeid(U));

  memoryMap[rawPtr] = {size, type};
  totalUsage += size;
  blockCount++;
  return true;
}

/**
 * Modifies the size of a registered memory block stored   in the MemoryManager.
 *
 * @param newSize The new size of the memory block in bytes.
 * @param data A shared pointer to the memory block.
 *
 * @return True if the memory block was successfully modified, false otherwise.
 *
 * @throws None.
 */
template <typename U>
bool MemoryManager::modify(int newSize, std::shared_ptr<U> data) {
  std::lock_guard<std::mutex> lock(mtx);

  if (newSize <= 0 || !data) return false;

  void* rawPtr = data.get();
  auto it = memoryMap.find(rawPtr);
  if (it == memoryMap.end()) return false;

  totalUsage += newSize - it->second.size;
  it->second.size = newSize;
  return true;
}

/**
 * Releases a registered memory block from the MemoryManager.
 *
 * @param data A shared pointer to the memory block.
 *
 * @return True if the memory block was successfully released, false otherwise.
 *
 * @throws None.
 */
template <typename U>
bool MemoryManager::release(U* data) {
  std::lock_guard<std::mutex> lock(mtx);

  if (!data) return false;

  void* rawPtr = static_cast<void*>(data);
  auto it = memoryMap.find(rawPtr);
  if (it == memoryMap.end()) return false;

  totalUsage -= it->second.size;
  memoryMap.erase(it);
  blockCount--;
  return true;
}

}  // namespace memory_maintainer

#endif  // MEMORY_H