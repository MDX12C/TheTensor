#include "define.hpp"
#ifndef MEMORY_H
#define MEMORY_H 1
#include <set>

#include "basic.hpp"
#include "log.hpp"

namespace memory_manage {
class MemorySupport {
 private:
  static size_t blocks_;
  static std::set<storage::StoryBase*> zone_;

 public:
  static inline unsigned long long getTotalUsage() noexcept;
  static inline const size_t& getBlocks() noexcept {
    return MemorySupport::blocks_;
  }
  static inline void displayUsage(std::ostream&) noexcept;
  static inline bool track(storage::StoryBase*) noexcept; 
  static inline bool untrack(storage::StoryBase*) noexcept;
  /**
   * @warning don't use it
   */
  static inline void init() noexcept {
    LOG("S:memory init");
    MemorySupport::blocks_ = 0;
    MemorySupport::zone_.clear();
  }
};
}  // namespace memory_manage

#define MEMORY_CON memory_manage::MemorySupport::init();
#endif