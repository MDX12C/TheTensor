#include "define.hpp"
#ifndef STORY_H
#define STORY_H 1
#include "basic.hpp"
#include "memory.hpp"
namespace storage {
template <typename T>
class Story : public StoryBase {
  template <typename W>
  friend class Story;
  template <typename W>
  friend std::ostream& operator<<(std::ostream& __stream,
                                  Story<W> const& __item) noexcept;

 protected:
  T* datas_;
  size_t size_;

 public:
  Story() noexcept(basic_math::support<T>);
  Story(size_t const&) noexcept(basic_math::support<T>);
  Story(size_t const&, T* const&) noexcept(basic_math::support<T>);
  Story(Story const&) noexcept(basic_math::support<T>);
  virtual ~Story() noexcept;
  inline T sum() const noexcept;
  inline virtual size_t size() const noexcept override { return this->size_; }
  inline virtual size_t capacity() const noexcept override {
    return this->size_ * sizeof(T);
  }
  inline virtual bool resize(size_t const&);
  inline virtual bool load(size_t const&, T* const&);
  inline virtual void freedom() noexcept;
  inline T* const begin() const noexcept { return this->datas_; }
  inline T* const end() const noexcept { return this->datas_ + this->size_; }
  inline virtual T& at(size_t const&) const;
  inline virtual T& operator[](size_t const&) const;
  template <typename U>
  inline operator Story<U>() const noexcept(basic_math::support<T>) {
    LOG("C:cast operator of Story");
    if constexpr (!basic_math::support<U>) {
      LOG("B:unsupportted type");
      throw system_message::Error("unsupport type of Story");
    }
    if constexpr (std::is_same_v<T, U>) return *this;
    Story<U> result(this->size_);
    for (size_t i = 0; i < this->size_; i++)
      result.datas_[i] = static_cast<U>(this->datas_[i]);
    return result;
  }
  inline Story& operator=(Story const&) noexcept;
  inline Story& operator=(T const&) noexcept;
};
template <typename T>
std::ostream& operator<<(std::ostream& __stream,
                         Story<T> const& __item) noexcept {
  LOG("C:ostream to Story");
  size_t digits = 0;
  __stream << std::noshowpos << '(' << __item.size_ << ')';
  if constexpr (std::is_same_v<T, bool>) {
    digits = 1;
    __stream << '[';
  } else if constexpr (std::is_floating_point_v<T>) {
    for (size_t i = 0; i < __item.size_; i++)
      digits = std::max(digits, basic_math::intDigits(__item.datas_[i]));
    digits += 2;
    digits += basic_math::PRINT_ACCURACY;
    __stream << std::setprecision(basic_math::PRINT_ACCURACY) << std::fixed
             << std::showpos << std::internal << std::setfill(' ')
             << std::showpoint << '[';
  } else {
    for (size_t i = 0; i < __item.size_; i++)
      digits = std::max(digits, basic_math::intDigits(__item.datas_[i]));
    digits += 1;
    __stream << std::showpos << std::internal << std::setfill(' ') << '[';
  }
  __stream << std::setw(digits) << __item.datas_[0];
  for (size_t i = 0; i < __item.size_; i++) {
    __stream << ',' << std::setw(digits) << __item.datas_[i];
  }
  __stream << "]\n";
  return __stream;
}
/**
 * @brief default constructor
 */
template <typename T>
Story<T>::Story() noexcept(basic_math::support<T>) : StoryBase() {
  LOG("C:Default consructor of Story");
  if constexpr (basic_math::support<T>) {
    memory_manage::MemorySupport::track(dynamic_cast<StoryBase*>(this));
    this->size_ = 1;
    this->datas_ = new T[1];
    this->datas_[0] = static_cast<T>(0);
    return;
  } else {
    LOG("B:unsupport type for Story");
    throw system_message::Error("unsupport type for Story");
    return;
  }
}
/**
 * @brief size constructor
 * @param lenth the lenth of memory
 */
template <typename T>
Story<T>::Story(size_t const& __lenth) noexcept(basic_math::support<T>)
    : StoryBase() {
  LOG("C:Size constructor of Story");
  if constexpr (!basic_math::support<T>) {
    LOG("B:unsupport type for Story");
    throw system_message::Error("unsupport type for Story");
    return;
  } else {
    memory_manage::MemorySupport::track(dynamic_cast<StoryBase*>(this));
    if (__lenth) {
      this->size_ = __lenth;
    } else {
      LOG("E:size can't be 0");
      this->size_ = 1;
    }
    this->datas_ = new T[this->size_];
    for (size_t i = 0; i < this->size_; i++)
      this->datas_[i] = static_cast<T>(0);
    return;
  }
}
/**
 * @brief init constructor
 * @param lenth the lenth of memory
 * @param init the init datas
 * @warning if the size isn't equal to the lenth of datas, it will come to
 * memory leak
 */
template <typename T>
Story<T>::Story(size_t const& __lenth,
                T* const& __init) noexcept(basic_math::support<T>)
    : StoryBase() {
  LOG("C:Init constructor of Story");
  if constexpr (!basic_math::support<T>) {
    LOG("B:unsupport type for Story");
    throw system_message::Error("unsupport type for Story");
    return;
  } else {
    memory_manage::MemorySupport::track(dynamic_cast<StoryBase*>(this));
    if (__lenth && __init) {
      this->size_ = __lenth;
      this->datas_ = new T[this->size_];
      std::copy(__init, __init + __lenth, this->datas_);
    } else {
      LOG("E:bad lenth or null datas");
      this->size_ = 1;
      this->datas_ = new T[1];
      this->datas_[0] = static_cast<T>(0);
    }
    return;
  }
}
/**
 * @brief copy constructor
 * @param other the copy one
 */
template <typename T>
Story<T>::Story(Story const& __other) noexcept(basic_math::support<T>)
    : StoryBase() {
  LOG("C:Copy constructor of Story");
  if constexpr (!basic_math::support<T>) {
    LOG("B:unsupport type for Story");
    throw system_message::Error("unsupport type for Story");
    return;
  } else {
    memory_manage::MemorySupport::track(dynamic_cast<StoryBase*>(this));
    this->size_ = __other.size_;
    this->datas_ = new T[this->size_];
    std::copy(__other.datas_, __other.datas_ + this->size_, this->datas_);
    return;
  }
}
/**
 * @brief destructor
 */
template <typename T>
Story<T>::~Story() noexcept {
  LOG("C:Destructor of Story");
  if constexpr (basic_math::support<T>) {
    memory_manage::MemorySupport::untrack(dynamic_cast<StoryBase*>(this));
  }
  delete[] this->datas_;
  return;
}
/**
 * @brief summer
 * @return the total, if the type is bool, return the majority
 */
template <typename T>
inline T Story<T>::sum() const noexcept {
  LOG("C:Sum of Story");
  if constexpr (std::is_same_v<T, bool>) {
    size_t total = 0;
    for (size_t i = 0; i < this->size_; i++)
      if (this->datas_[i]) total++;
    return static_cast<bool>((this->size_ / 2) > total ? false : true);
  } else {
    T total = static_cast<T>(0);
    for (size_t i = 0; i < this->size_; i++) total += this->datas_[i];
    return total;
  }
}
/**
 * @brief resize the Story,
 * the exceed part of older will be cut,
 * the exceed part of newer will be set 0
 * @param __argSize the size argument
 * @return If the argSize is same to original size or 0, return false. True,
 * otherwise.
 * @throw none
 */
template <typename T>
inline bool Story<T>::resize(size_t const& __argSize) {
  LOG("C:Resize of Story");
  if (__argSize == 0) {
    LOG("E:bad lenth");
    return false;
  }
  if (__argSize == this->size_) {
    return false;
  }
  size_t newSize = __argSize, copySize = std::min(newSize, this->size_);
  T* newStory = new T[newSize];
  std::copy(this->datas_, this->datas_ + copySize, newStory);
  for (size_t i = copySize; i < newSize; i++) newStory[i] = static_cast<T>(0);
  delete[] this->datas_;
  this->size_ = newSize;
  this->datas_ = newStory;
  return true;
}
/**
 * @brief load for datas
 * @param __size the new alloc size
 * @param __datas the new datas
 * @return If the size is 0, or the data is null, false. True, otherwise.
 * @warning if the size isn't equal to the lenth of datas, it will come to
 * memory leak
 * @throw none
 */
template <typename T>
inline bool Story<T>::load(size_t const& __size, T* const& __datas) {
  LOG("C:Load of Story");
  if (__size && __datas) {
    delete[] this->datas_;
    this->datas_ = new T[__size];
    this->size_ = __size;
    std::copy(__datas, __datas + __size, this->datas_);
    return true;
  } else {
    LOG("E:bad lenth or null datas");
    return false;
  }
}
/**
 * @brief freedom for memory
 */
template <typename T>
inline void Story<T>::freedom() noexcept {
  LOG("C:Freedom of Story");
  delete[] this->datas_;
  this->size_ = 1;
  this->datas_ = new T[1];
  this->datas_[0] = static_cast<T>(0);
  return;
}
/**
 * @brief the function does as you think
 */
template <typename T>
inline T& Story<T>::at(size_t const& __where) const {
  LOG("C:At of Story");
  if (__where >= this->size_) {
    LOG("E:memory overflow");
    return this->datas_[0];
  }
  return this->datas_[__where];
}
template <typename T>
inline T& Story<T>::operator[](size_t const& __where) const {
  LOG("C:operator[] of Story");
  return this->datas_[__where];
}
template <typename T>
inline Story<T>& Story<T>::operator=(Story<T> const& __other) noexcept {
  LOG("C:operator= of Story");
  if (!(this->size_ == __other.size_)) {
    delete[] this->datas_;
    this->datas_ = new T[__other.size_];
    this->size_ = __other.size_;
  }
  std::copy(__other.datas_, __other.datas_ + __other.size_, this->datas_);
  return *this;
}
template <typename T>
inline Story<T>& Story<T>::operator=(T const& __other) noexcept {
  LOG("C:operator= of Story");
  for (size_t i = 0; i < this->size_; i++) this->datas_[i] = __other;
  return *this;
}
}  // namespace storage
#endif