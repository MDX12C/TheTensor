#include "memory.h"

#include "basic.hpp"

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
template <typename T>
bool MemoryManager::signUp(int size, std::shared_ptr<T> data) {
  std::lock_guard<std::mutex> lock(mtx);

  if (size <= 0 || !data) return false;

  void* rawPtr = data.get();
  MemoryType type = getMemoryType(typeid(T));

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
template <typename T>
bool MemoryManager::modify(int newSize, std::shared_ptr<T> data) {
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
template <typename T>
bool MemoryManager::release(std::shared_ptr<T> data) {
  std::lock_guard<std::mutex> lock(mtx);

  if (!data) return false;

  void* rawPtr = data.get();
  auto it = memoryMap.find(rawPtr);
  if (it == memoryMap.end()) return false;

  totalUsage -= it->second.size;
  memoryMap.erase(it);
  blockCount--;
  return true;
}

/**
 * Returns the total usage of memory in bytes.
 *
 * @return The total usage of memory in bytes.
 *
 * @throws None.
 */
unsigned long long MemoryManager::getTotalUsage() const {
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
int MemoryManager::getBlockCount() const {
  std::lock_guard<std::mutex> lock(mtx);
  return blockCount;
}

/**
 * Displays the usage of memory blocks in the MemoryManager.
 *
 * @throws None.
 */
void MemoryManager::displayUsage() const {
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
MemoryType MemoryManager::getMemoryType(std::type_index typeIdx) const {
  if (typeIdx == typeid(linalg::Vector<int>)) return MemoryType::VectorInt;
  if (typeIdx == typeid(linalg::Vector<bool>)) return MemoryType::VectorBool;
  if (typeIdx == typeid(linalg::Vector<float>)) return MemoryType::VectorFloat;
  if (typeIdx == typeid(linalg::Matrix<int>)) return MemoryType::MatrixInt;
  if (typeIdx == typeid(linalg::Matrix<bool>)) return MemoryType::MatrixBool;
  return MemoryType::MatrixBool;
  if (typeIdx == typeid(linalg::Matrix<float>)) return MemoryType::MatrixFloat;
  throw std::invalid_argument("Unsupported type");
}
}  // namespace memory_maintainer
