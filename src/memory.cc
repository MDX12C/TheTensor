#include "thetensor/memory.hpp"

#include "thetensor/define.hpp"
#if MEMORY_HH
namespace memory_manage {
size_t MemorySupport::blocks_ = 0;
std::set<storage::StoryBase*> MemorySupport::zone_;

/**
 * @brief display usage
 * @param __output the ostream, std::cout is defult
 */
void MemorySupport::displayUsage(std::ostream& __output) noexcept {
  unsigned long long total = 0;
  for (auto& item : MemorySupport::zone_) {
    __output << '\n';
    for (auto i = 0; i < log_file::DOCS_WIDE; i++) __output << '-';

    __output << "\nid: " << (void*)item << "\ntype: " << item->type()
             << "\nsize: " << item->size()
             << "\ncapacity: " << item->capacity();
    total += item->capacity();
  }
  __output << '\n';
  for (auto i = 0; i < log_file::DOCS_WIDE; i++) __output << '-';
  __output << "\ntotal " << total << " bytes in " << MemorySupport::blocks_
           << " blocks\n\n";
  return;
}
/**
 * @brief count total usage
 * @return total usage counted in bytes
 */
unsigned long long MemorySupport::getTotalUsage() noexcept {
  unsigned long long total = 0;
  for (auto& item : MemorySupport::zone_) {
    total += item->capacity();
  }
  return total;
}
/**
 * @brief track
 * @param __item the pointer
 */
bool MemorySupport::track(storage::StoryBase* __item) noexcept {
  if (MemorySupport::zone_.count(__item)) {
    LOG("E:%p has already been tracked", (void*)__item);
    return false;
  }
  MemorySupport::blocks_ += 1;
  MemorySupport::zone_.insert(__item);
  return true;
}
/**
 * @brief untrack
 * @param __item the pointer
 */
bool MemorySupport::untrack(storage::StoryBase* __item) noexcept {
  if (!MemorySupport::zone_.count(__item)) {
    LOG("E:%p hasn't been tracked", (void*)__item);
    return false;
  }
  MemorySupport::blocks_ -= 1;
  MemorySupport::zone_.erase(__item);
  return true;
}
}  // namespace memory_manage
#endif
