#ifndef MEMORY_H
#define MEMORY_H 1

#include <iostream>
#include <memory>
#include <mutex>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "log.hpp"

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
  static bool signUp(unsigned int const& size, U* const& data);

  template <typename U>
  static bool modify(unsigned int const& newSize, U* const& data);

  template <typename U>
  static bool release(U* const& data);

  static unsigned long long getTotalUsage();
  static unsigned int getBlockCount();
  static void displayUsage();
  static inline void init() {
    MemoryManager::blockCount = 0;
    MemoryManager::totalUsage = 0;
    MemoryManager::memoryMap.clear();
    return;
  }

 private:
  struct MemoryBlock {
    unsigned int size;
    MemoryType type;
  };

  static unsigned long long totalUsage;
  static unsigned int blockCount;
  static std::unordered_map<void*, MemoryManager::MemoryBlock> memoryMap;
  static std::mutex mtx;

  static MemoryType getMemoryType(std::type_index typeIdx);
};

}  // namespace memory_maintainer

namespace memory_maintainer {
/**
 * Registers a block of memory with the MemoryManager.
 *
 * @param size The size of the memory block in per class.
 * @param data A shared pointer to the memory block.
 *
 * @return True if the memory block was successfully registered, false
 * otherwise.
 *
 * @throws None.
 */
template <typename U>
bool MemoryManager::signUp(unsigned int const& size, U* const& data) {
  LOG("C:");
  std::lock_guard<std::mutex> lock(mtx);

  if (data == nullptr) return false;

  void* rawPtr = static_cast<void*>(data);
  if (memoryMap.find(rawPtr) != memoryMap.end()) return false;
  MemoryType type = getMemoryType(typeid(U));

  memoryMap[rawPtr] = {size, type};
  totalUsage += size;
  blockCount++;
  return true;
}

/**
 * Modifies the size of a registered memory block stored   in the MemoryManager.
 *
 * @param newSize The new size of the memory block in per class.
 * @param data A shared pointer to the memory block.
 *
 * @return True if the memory block was successfully modified, false otherwise.
 *
 * @throws None.
 */
template <typename U>
bool MemoryManager::modify(unsigned int const& newSize, U* const& data) {
  LOG("C:");
  std::lock_guard<std::mutex> lock(mtx);

  if (data == nullptr) return false;

  void* rawPtr = static_cast<void*>(data);
  auto it = memoryMap.find(rawPtr);
  if (it == memoryMap.end()) return false;

  totalUsage += newSize;
  totalUsage -= it->second.size;
  it->second.size = newSize;
  return true;
}

/**
 * Releases a registered memory block from the MemoryManager.
 *
 * @param data A pointer to the memory block.
 *
 * @return True if the memory block was successfully released, false otherwise.
 *
 * @throws None.
 */
template <typename U>
bool MemoryManager::release(U* const& data) {
  LOG("C:");
  std::lock_guard<std::mutex> lock(mtx);

  if (data == nullptr) return false;

  void* rawPtr = static_cast<void*>(data);
  auto it = memoryMap.find(rawPtr);
  if (it == memoryMap.end()) return false;

  totalUsage -= it->second.size;
  memoryMap.erase(it);
  blockCount--;
  return true;
}

}  // namespace memory_maintainer

/**
 * init of memory.hpp
 */
#define MEMORY_CON memory_maintainer::MemoryManager::init();

#endif  // MEMORY_H