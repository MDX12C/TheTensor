#ifndef MEMORY_CC
#define MEMORY_CC 1
#include "memory.hpp"

#include "basic.hpp"
#include "matrix.hpp"
#include "vector.hpp"

namespace memory_maintainer {
unsigned long long MemoryManager::totalUsage = 0;
unsigned int MemoryManager::blockCount = 0;
std::unordered_map<void*, MemoryManager::MemoryBlock> MemoryManager::memoryMap;
std::mutex MemoryManager::mtx;

/**
 * Returns the total usage of memory in bytes.
 *
 * @return The total usage of memory in bytes.
 *
 * @throws None.
 */  // namespace memory_maintainer
unsigned long long MemoryManager::getTotalUsage() {
  std::lock_guard<std::mutex> lock(mtx);
  return totalUsage;
}

/**
 * Returns the number of memory blocks registered in the MemoryManager.
 *
 * @return The number of memory blocks.
 *
 * @throws None.
 */
unsigned int MemoryManager::getBlockCount() {
  std::lock_guard<std::mutex> lock(mtx);
  return blockCount;
}

/**
 * Displays the usage of memory blocks in the MemoryManager.
 *
 * @throws None.
 */
void MemoryManager::displayUsage() {
  std::lock_guard<std::mutex> lock(mtx);

  std::cout << "Total blocks: " << blockCount << ", Total usage: " << totalUsage
            << " bytes\n";
  for (const auto& [ptr, block] : memoryMap) {
    std::cout << "Pointer: " << ptr << ", Size: " << block.size
              << " bytes, Type: " << static_cast<int>(block.type) << '\n';
  }
}

/**
 * Determines the MemoryType of the provided type index.
 *
 * @param typeIdx The type index to determine the MemoryType for.
 *
 * @return The MemoryType corresponding to the type index.
 *
 * @throws std::invalid_argument if the type index is unsupported.
 */
MemoryType MemoryManager::getMemoryType(std::type_index typeIdx) {
  if (typeIdx == typeid(linalg::Vector<int>)) return MemoryType::VectorInt;
  if (typeIdx == typeid(linalg::Vector<bool>)) return MemoryType::VectorBool;
  if (typeIdx == typeid(linalg::Vector<float>)) return MemoryType::VectorFloat;
  if (typeIdx == typeid(linalg::Matrix<int>)) return MemoryType::MatrixInt;
  if (typeIdx == typeid(linalg::Matrix<bool>)) return MemoryType::MatrixBool;
  if (typeIdx == typeid(linalg::Matrix<float>)) return MemoryType::MatrixFloat;
  throw std::invalid_argument("Unsupported type");
}
}  // namespace memory_maintainer
#endif