#include "memory.h"

namespace memory_maintainer {

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

unsigned long long MemoryManager::getTotalUsage() const {
  std::lock_guard<std::mutex> lock(mtx);
  return totalUsage;
}

int MemoryManager::getBlockCount() const {
  std::lock_guard<std::mutex> lock(mtx);
  return blockCount;
}

void MemoryManager::displayUsage() const {
  std::lock_guard<std::mutex> lock(mtx);

  std::cout << "Total blocks: " << blockCount << ", Total usage: " << totalUsage
            << " bytes\n";
  for (const auto& [ptr, block] : memoryMap) {
    std::cout << "Pointer: " << ptr << ", Size: " << block.size
              << " bytes, Type: " << static_cast<int>(block.type) << '\n';
  }
}

MemoryType MemoryManager::getMemoryType(std::type_index typeIdx) const {
  if (typeIdx == typeid(std::vector<int>)) return MemoryType::VectorInt;
  if (typeIdx == typeid(std::vector<bool>)) return MemoryType::VectorBool;
  if (typeIdx == typeid(std::vector<float>)) return MemoryType::VectorFloat;
  if (typeIdx == typeid(std::vector<std::vector<int>>))
    return MemoryType::MatrixInt;
  if (typeIdx == typeid(std::vector<std::vector<bool>>))
    return MemoryType::MatrixBool;
  if (typeIdx == typeid(std::vector<std::vector<float>>))
    return MemoryType::MatrixFloat;
  throw std::invalid_argument("Unsupported type");
}
}  // namespace memory_maintainer
