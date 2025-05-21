#include "define.hpp"
#ifndef VECTOR_HH
#define VECTOR_HH 1
#include "basic.hpp"
#include "memory.hpp"
#include "story.hpp"

namespace lina_lg {
template <typename T>
class Vector final : public storage::Story<T> {
  template <typename W>
  friend class Vector;

 public:
  Vector() noexcept(basic_math::support<T>) {}
  Vector(size_t const&) noexcept(basic_math::support<T>);
  Vector(size_t const&, T* const&) noexcept(basic_math::support<T>);
  Vector(Vector const&) noexcept(basic_math::support<T>);
  Vector(Vector&&) noexcept(basic_math::support<T>);
  ~Vector() noexcept {}
  inline virtual std::string type() const noexcept override {
    std::string ret = "VC00";
    if constexpr (std::is_floating_point_v<T>)
      ret[2] = 'F';
    else
      ret[2] = 'I';
    ret[3] += static_cast<char>(std::log2(sizeof(T)));
    return ret;
  }
  template <typename U>
  inline operator Vector<U>() const noexcept(basic_math::support<U>) {
    if constexpr (!basic_math::support<U>) {
      LOG("B:unsupport type");
      throw system_control::Error("unsupport type of Vector");
    }
    if constexpr (std::is_same_v<T, U>) return *this;
    Vector<U> result(this->size_);
    for (size_t i = 0; i < this->size_; i++)
      result.datas_[i] = static_cast<U>(this->datas_[i]);
    return result;
  }
  inline Vector& operator=(Vector const&) noexcept;
  inline Vector& operator+=(Vector const&) noexcept;
  inline Vector& operator-=(Vector const&) noexcept;
  inline Vector& operator*=(Vector const&) noexcept;
  inline Vector& operator/=(Vector const&) noexcept;
  inline Vector& operator=(Vector&&) noexcept;
  inline Vector& operator=(T const&) noexcept;
  inline Vector& operator+=(T const&) noexcept;
  inline Vector& operator-=(T const&) noexcept;
  inline Vector& operator*=(T const&) noexcept;
  inline Vector& operator/=(T const&) noexcept;

  inline Vector operator!() const;

  inline Vector operator+(Vector const&) noexcept;
  inline Vector operator-(Vector const&) noexcept;
  inline Vector operator*(Vector const&) noexcept;
  inline Vector operator/(Vector const&) noexcept;
  inline Vector operator+(T const&) const noexcept;
  inline Vector operator-(T const&) const noexcept;
  inline Vector operator*(T const&) const noexcept;
  inline Vector operator/(T const&) const noexcept;

  inline Vector<bool> operator==(Vector const&) noexcept;
  inline Vector<bool> operator!=(Vector const&) noexcept;
  inline Vector<bool> operator>=(Vector const&) noexcept;
  inline Vector<bool> operator<=(Vector const&) noexcept;
  inline Vector<bool> operator>(Vector const&) noexcept;
  inline Vector<bool> operator<(Vector const&) noexcept;
  inline Vector<bool> operator==(T const&) const noexcept;
  inline Vector<bool> operator!=(T const&) const noexcept;
  inline Vector<bool> operator>=(T const&) const noexcept;
  inline Vector<bool> operator<=(T const&) const noexcept;
  inline Vector<bool> operator>(T const&) const noexcept;
  inline Vector<bool> operator<(T const&) const noexcept;
};
typedef Vector<FloatType> VectorF;
template <typename T>
std::ostream& operator<<(std::ostream& __stream,
                         Vector<T> const& __item) noexcept {
  size_t digits = 0;
  auto datas = __item.begin();
  auto size = __item.size();
  __stream << std::noshowpos << '(' << size << ')';
  if constexpr (std::is_same_v<T, bool>) {
    digits = 1;
    __stream << '[';
  } else if constexpr (std::is_floating_point_v<T>) {
    for (size_t i = 0; i < size; i++)
      digits = std::max(digits, basic_math::intDigits(datas[i]));
    digits += 2;
    digits += basic_math::PRINT_ACCURACY;
    __stream << std::setprecision(basic_math::PRINT_ACCURACY) << std::fixed
             << std::showpos << std::internal << std::setfill(' ')
             << std::showpoint << '[';
  } else {
    for (size_t i = 0; i < size; i++)
      digits = std::max(digits, basic_math::intDigits(datas[i]));
    digits += 1;
    __stream << std::showpos << std::internal << std::setfill(' ') << '[';
  }
  __stream << std::setw(digits) << datas[0];
  for (size_t i = 1; i < size; i++) {
    __stream << ',' << std::setw(digits) << datas[i];
  }
  __stream << ']';
  return __stream;
}
template <typename T>
inline Vector<T> operator+(T const&, Vector<T> const&) noexcept;
template <typename T>
inline Vector<T> operator-(T const&, Vector<T> const&) noexcept;
template <typename T>
inline Vector<T> operator*(T const&, Vector<T> const&) noexcept;
template <typename T>
inline Vector<T> operator/(T const&, Vector<T> const&) noexcept;
template <typename T>
inline Vector<bool> operator==(T const&, Vector<T> const&) noexcept;
template <typename T>
inline Vector<bool> operator!=(T const&, Vector<T> const&) noexcept;
template <typename T>
inline Vector<bool> operator>=(T const&, Vector<T> const&) noexcept;
template <typename T>
inline Vector<bool> operator<=(T const&, Vector<T> const&) noexcept;
template <typename T>
inline Vector<bool> operator>(T const&, Vector<T> const&) noexcept;
template <typename T>
inline Vector<bool> operator<(T const&, Vector<T> const&) noexcept;
template <typename T>
inline Vector<T> merge(Vector<T> const&, Vector<T> const&) noexcept;
template <typename T>
inline Vector<T> scan(Vector<T> const&, size_t const&, size_t const&) noexcept;
}  // namespace lina_lg
namespace basic_math {
template <typename T>
inline lina_lg::Vector<T> uniformRand(size_t const&, T const&,
                                      T const&) noexcept;
template <typename T>
inline lina_lg::Vector<T> absolute(lina_lg::Vector<T> const&) noexcept;
template <typename T>
inline lina_lg::Vector<T> pow(lina_lg::Vector<T> const&, T const&) noexcept;
template <typename T>
inline lina_lg::Vector<T> pow(T const&, lina_lg::Vector<T> const&) noexcept;
template <typename T>
inline lina_lg::Vector<T> pow(lina_lg::Vector<T> const&,
                              lina_lg::Vector<T> const&) noexcept;
template <typename T>
inline lina_lg::Vector<T> log(lina_lg::Vector<T> const&) noexcept;
}  // namespace basic_math

namespace lina_lg {
/**
 * @brief size constructor
 * @param __size the init size
 */
template <typename T>
Vector<T>::Vector(size_t const& __size) noexcept(basic_math::support<T>)
    : storage::Story<T>(__size) {
  return;
}
/**
 * @brief init constructor
 * @param __size init size
 * @param __init init datas
 */
template <typename T>
Vector<T>::Vector(size_t const& __size,
                  T* const& __init) noexcept(basic_math::support<T>)
    : storage::Story<T>(__size, __init) {
  return;
}
/**
 * @brief copy constructor
 * @param __other the other one
 */
template <typename T>
Vector<T>::Vector(Vector const& __other) noexcept(basic_math::support<T>)
    : storage::Story<T>(__other.size_, __other.datas_) {
  return;
}
/**
 * @brief
 */
template <typename T>
Vector<T>::Vector(Vector&& __other) noexcept(basic_math::support<T>)
    : storage::Story<T>() {
  delete[] this->datas_;
  this->datas_ = __other.datas_;
  this->size_ = __other.size_;
  __other.datas_ = nullptr;
  return;
}
template <typename T>
inline Vector<T>& Vector<T>::operator=(Vector<T> const& __other) noexcept {
  if (this->size_ != __other.size_) {
    delete[] this->datas_;
    this->size_ = __other.size_;
    this->datas_ = new T[this->size_];
  }
  std::copy(__other.datas_, __other.datas_ + __other.size_, this->datas_);
  return *this;
}
template <typename T>
inline Vector<T>& Vector<T>::operator=(Vector<T>&& __other) noexcept {
  if (this == &__other) {
    LOG("B:inlegal way to move between one Vector");
    return *this;
  }
  if (this->datas_) delete[] this->datas_;
  this->datas_ = __other.datas_;
  this->size_ = __other.size_;
  __other.datas_ = nullptr;
  return *this;
}
template <typename T>
inline Vector<T>& Vector<T>::operator=(T const& __other) noexcept {
  for (size_t i = 0; i < this->size_; i++) this->datas_[i] = __other;
  return *this;
}
template <typename T>
inline Vector<T>& Vector<T>::operator+=(Vector<T> const& __other) noexcept {
  if (this->size_ != __other.size_) {
    LOG("E:encounter size will be suited");
    T* temp = new T[__other.size_];
    size_t copySize = std::min(this->size_, __other.size_);
    std::copy(this->datas_, this->datas_ + copySize, temp);
    for (auto i = copySize; i < __other.size_; i++) temp[i] = static_cast<T>(0);
    this->size_ = __other.size_;
    delete[] this->datas_;
    this->datas_ = temp;
  }
  for (size_t i = 0; i < this->size_; i++)
    EADD(this->datas_[i], __other.datas_[i], T);
  return *this;
}
template <typename T>
inline Vector<T>& Vector<T>::operator+=(T const& __other) noexcept {
  for (size_t i = 0; i < this->size_; i++) EADD(this->datas_[i], __other, T);
  return *this;
}
template <typename T>
inline Vector<T>& Vector<T>::operator-=(Vector<T> const& __other) noexcept {
  if (this->size_ != __other.size_) {
    LOG("E:encounter size will be suited");
    T* temp = new T[__other.size_];
    size_t copySize = std::min(this->size_, __other.size_);
    std::copy(this->datas_, this->datas_ + copySize, temp);
    for (auto i = copySize; i < __other.size_; i++) temp[i] = static_cast<T>(0);
    this->size_ = __other.size_;
    delete[] this->datas_;
    this->datas_ = temp;
  }
  for (size_t i = 0; i < this->size_; i++)
    EMNS(this->datas_[i], __other.datas_[i], T);
  return *this;
}
template <typename T>
inline Vector<T>& Vector<T>::operator-=(T const& __other) noexcept {
  for (size_t i = 0; i < this->size_; i++) EMNS(this->datas_[i], __other, T);
  return *this;
}
template <typename T>
inline Vector<T>& Vector<T>::operator*=(Vector<T> const& __other) noexcept {
  if (this->size_ != __other.size_) {
    LOG("E:encounter size will be suited");
    T* temp = new T[__other.size_];
    size_t copySize = std::min(this->size_, __other.size_);
    std::copy(this->datas_, this->datas_ + copySize, temp);
    for (auto i = copySize; i < __other.size_; i++) temp[i] = static_cast<T>(0);
    this->size_ = __other.size_;
    delete[] this->datas_;
    this->datas_ = temp;
  }
  for (size_t i = 0; i < this->size_; i++)
    EMUL(this->datas_[i], __other.datas_[i], T);
  return *this;
}
template <typename T>
inline Vector<T>& Vector<T>::operator*=(T const& __other) noexcept {
  for (size_t i = 0; i < this->size_; i++) EMUL(this->datas_[i], __other, T);
  return *this;
}
template <typename T>
inline Vector<T>& Vector<T>::operator/=(Vector<T> const& __other) noexcept {
  if (this->size_ != __other.size_) {
    LOG("E:encounter size will be suited");
    T* temp = new T[__other.size_];
    size_t copySize = std::min(this->size_, __other.size_);
    std::copy(this->datas_, this->datas_ + copySize, temp);
    for (auto i = copySize; i < __other.size_; i++) temp[i] = static_cast<T>(0);
    this->size_ = __other.size_;
    delete[] this->datas_;
    this->datas_ = temp;
  }
  for (size_t i = 0; i < this->size_; i++)
    EDIV(this->datas_[i], __other.datas_[i], T);
  return *this;
}
template <typename T>
inline Vector<T>& Vector<T>::operator/=(T const& __other) noexcept {
  for (size_t i = 0; i < this->size_; i++) EDIV(this->datas_[i], __other, T);
  return *this;
}
template <typename T>
inline Vector<T> Vector<T>::operator!() const {
  if constexpr (std::is_unsigned_v<T>) {
    LOG("B:the type can't be signed");
    throw system_control::Error("the type can't be signed");
  }
  Vector<T> result(this->size_);
  for (size_t i = 0; i < this->size_; i++)
    if constexpr (std::is_same_v<T, bool>) {
      result.datas_[i] = !this->datas_[i];
    } else {
      result.datas_[i] = -this->datas_[i];
    }
  return result;
}
template <typename T>
inline Vector<T> Vector<T>::operator+(Vector<T> const& __other) noexcept {
  if (this->size_ != __other.size_) {
    LOG("E:encounter size will be suited");
    T* temp = new T[__other.size_];
    size_t copySize = std::min(this->size_, __other.size_);
    std::copy(this->datas_, this->datas_ + copySize, temp);
    for (auto i = copySize; i < __other.size_; i++) temp[i] = static_cast<T>(0);
    this->size_ = __other.size_;
    delete[] this->datas_;
    this->datas_ = temp;
  }
  Vector<T> result(*this);
  for (size_t i = 0; i < this->size_; i++)
    EADD(result.datas_[i], __other.datas_[i], T);
  return result;
}
template <typename T>
inline Vector<T> Vector<T>::operator+(T const& __other) const noexcept {
  Vector<T> result(*this);
  for (size_t i = 0; i < this->size_; i++) EADD(result.datas_[i], __other, T);
  return result;
}
template <typename T>
inline Vector<T> Vector<T>::operator-(Vector<T> const& __other) noexcept {
  if (this->size_ != __other.size_) {
    LOG("E:encounter size will be suited");
    T* temp = new T[__other.size_];
    size_t copySize = std::min(this->size_, __other.size_);
    std::copy(this->datas_, this->datas_ + copySize, temp);
    for (auto i = copySize; i < __other.size_; i++) temp[i] = static_cast<T>(0);
    this->size_ = __other.size_;
    delete[] this->datas_;
    this->datas_ = temp;
  }
  Vector<T> result(*this);
  for (size_t i = 0; i < this->size_; i++)
    EMNS(result.datas_[i], __other.datas_[i], T);
  return result;
}
template <typename T>
inline Vector<T> Vector<T>::operator-(T const& __other) const noexcept {
  Vector<T> result(*this);
  for (size_t i = 0; i < this->size_; i++) EMNS(result.datas_[i], __other, T);
  return result;
}
template <typename T>
inline Vector<T> Vector<T>::operator*(Vector<T> const& __other) noexcept {
  if (this->size_ != __other.size_) {
    LOG("E:encounter size will be suited");
    T* temp = new T[__other.size_];
    size_t copySize = std::min(this->size_, __other.size_);
    std::copy(this->datas_, this->datas_ + copySize, temp);
    for (auto i = copySize; i < __other.size_; i++) temp[i] = static_cast<T>(0);
    this->size_ = __other.size_;
    delete[] this->datas_;
    this->datas_ = temp;
  }
  Vector<T> result(*this);
  for (size_t i = 0; i < this->size_; i++)
    EMUL(result.datas_[i], __other.datas_[i], T);
  return result;
}
template <typename T>
inline Vector<T> Vector<T>::operator*(T const& __other) const noexcept {
  Vector<T> result(*this);
  for (size_t i = 0; i < this->size_; i++) EMUL(result.datas_[i], __other, T);
  return result;
}
template <typename T>
inline Vector<T> Vector<T>::operator/(Vector<T> const& __other) noexcept {
  if (this->size_ != __other.size_) {
    LOG("E:encounter size will be suited");
    T* temp = new T[__other.size_];
    size_t copySize = std::min(this->size_, __other.size_);
    std::copy(this->datas_, this->datas_ + copySize, temp);
    for (auto i = copySize; i < __other.size_; i++) temp[i] = static_cast<T>(0);
    this->size_ = __other.size_;
    delete[] this->datas_;
    this->datas_ = temp;
  }
  Vector<T> result(*this);
  for (size_t i = 0; i < this->size_; i++)
    EDIV(result.datas_[i], __other.datas_[i], T);
  return result;
}
template <typename T>
inline Vector<T> Vector<T>::operator/(T const& __other) const noexcept {
  Vector<T> result(*this);
  for (size_t i = 0; i < this->size_; i++) EDIV(result.datas_[i], __other, T);
  return result;
}
template <typename T>
inline Vector<bool> Vector<T>::operator==(Vector<T> const& __other) noexcept {
  if (this->size_ != __other.size_) {
    LOG("E:encounter size will be suited");
    T* temp = new T[__other.size_];
    size_t copySize = std::min(this->size_, __other.size_);
    std::copy(this->datas_, this->datas_ + copySize, temp);
    for (auto i = copySize; i < __other.size_; i++) temp[i] = static_cast<T>(0);
    this->size_ = __other.size_;
    delete[] this->datas_;
    this->datas_ = temp;
  }
  Vector<bool> result(this->size_);
  for (size_t i = 0; i < this->size_; i++)
    result.datas_[i] = this->datas_[i] == __other.datas_[i];
  return result;
}
template <typename T>
inline Vector<bool> Vector<T>::operator==(T const& __other) const noexcept {
  Vector<bool> result(this->size_);
  for (size_t i = 0; i < this->size_; i++)
    result.datas_[i] = this->datas_[i] == __other;
  return result;
}
template <typename T>
inline Vector<bool> Vector<T>::operator!=(Vector<T> const& __other) noexcept {
  if (this->size_ != __other.size_) {
    LOG("E:encounter size will be suited");
    T* temp = new T[__other.size_];
    size_t copySize = std::min(this->size_, __other.size_);
    std::copy(this->datas_, this->datas_ + copySize, temp);
    for (auto i = copySize; i < __other.size_; i++) temp[i] = static_cast<T>(0);
    this->size_ = __other.size_;
    delete[] this->datas_;
    this->datas_ = temp;
  }
  Vector<bool> result(this->size_);
  for (size_t i = 0; i < this->size_; i++)
    result.datas_[i] = this->datas_[i] != __other.datas_[i];
  return result;
}
template <typename T>
inline Vector<bool> Vector<T>::operator!=(T const& __other) const noexcept {
  Vector<bool> result(this->size_);
  for (size_t i = 0; i < this->size_; i++)
    result.datas_[i] = this->datas_[i] != __other;
  return result;
}
template <typename T>
inline Vector<bool> Vector<T>::operator>=(Vector<T> const& __other) noexcept {
  if (this->size_ != __other.size_) {
    LOG("E:encounter size will be suited");
    T* temp = new T[__other.size_];
    size_t copySize = std::min(this->size_, __other.size_);
    std::copy(this->datas_, this->datas_ + copySize, temp);
    for (auto i = copySize; i < __other.size_; i++) temp[i] = static_cast<T>(0);
    this->size_ = __other.size_;
    delete[] this->datas_;
    this->datas_ = temp;
  }
  Vector<bool> result(this->size_);
  for (size_t i = 0; i < this->size_; i++)
    result.datas_[i] = this->datas_[i] >= __other.datas_[i];
  return result;
}
template <typename T>
inline Vector<bool> Vector<T>::operator>=(T const& __other) const noexcept {
  Vector<bool> result(this->size_);
  for (size_t i = 0; i < this->size_; i++)
    result.datas_[i] = this->datas_[i] >= __other;
  return result;
}
template <typename T>
inline Vector<bool> Vector<T>::operator<=(Vector<T> const& __other) noexcept {
  if (this->size_ != __other.size_) {
    LOG("E:encounter size will be suited");
    T* temp = new T[__other.size_];
    size_t copySize = std::min(this->size_, __other.size_);
    std::copy(this->datas_, this->datas_ + copySize, temp);
    for (auto i = copySize; i < __other.size_; i++) temp[i] = static_cast<T>(0);
    this->size_ = __other.size_;
    delete[] this->datas_;
    this->datas_ = temp;
  }
  Vector<bool> result(this->size_);
  for (size_t i = 0; i < this->size_; i++)
    result.datas_[i] = this->datas_[i] <= __other.datas_[i];
  return result;
}
template <typename T>
inline Vector<bool> Vector<T>::operator<=(T const& __other) const noexcept {
  Vector<bool> result(this->size_);
  for (size_t i = 0; i < this->size_; i++)
    result.datas_[i] = this->datas_[i] <= __other;
  return result;
}
template <typename T>
inline Vector<bool> Vector<T>::operator>(Vector<T> const& __other) noexcept {
  if (this->size_ != __other.size_) {
    LOG("E:encounter size will be suited");
    T* temp = new T[__other.size_];
    size_t copySize = std::min(this->size_, __other.size_);
    std::copy(this->datas_, this->datas_ + copySize, temp);
    for (auto i = copySize; i < __other.size_; i++) temp[i] = static_cast<T>(0);
    this->size_ = __other.size_;
    delete[] this->datas_;
    this->datas_ = temp;
  }
  Vector<bool> result(this->size_);
  for (size_t i = 0; i < this->size_; i++)
    result.datas_[i] = this->datas_[i] > __other.datas_[i];
  return result;
}
template <typename T>
inline Vector<bool> Vector<T>::operator>(T const& __other) const noexcept {
  Vector<bool> result(this->size_);
  for (size_t i = 0; i < this->size_; i++)
    result.datas_[i] = this->datas_[i] > __other;
  return result;
}
template <typename T>
inline Vector<bool> Vector<T>::operator<(Vector<T> const& __other) noexcept {
  if (this->size_ != __other.size_) {
    LOG("E:encounter size will be suited");
    T* temp = new T[__other.size_];
    size_t copySize = std::min(this->size_, __other.size_);
    std::copy(this->datas_, this->datas_ + copySize, temp);
    for (auto i = copySize; i < __other.size_; i++) temp[i] = static_cast<T>(0);
    this->size_ = __other.size_;
    delete[] this->datas_;
    this->datas_ = temp;
  }
  Vector<bool> result(this->size_);
  for (size_t i = 0; i < this->size_; i++)
    result.datas_[i] = this->datas_[i] < __other.datas_[i];
  return result;
}
template <typename T>
inline Vector<bool> Vector<T>::operator<(T const& __other) const noexcept {
  Vector<bool> result(this->size_);
  for (size_t i = 0; i < this->size_; i++)
    result.datas_[i] = this->datas_[i] < __other;
  return result;
}
template <typename T>
inline Vector<T> operator+(T const& __first,
                           Vector<T> const& __second) noexcept {
  auto size = __second.size();
  Vector<T> result(size);
  auto retDatas = result.begin(), datas = __second.begin();
  for (size_t i = 0; i < size; i++) ADD(__first, datas[i], retDatas[i], T);
  return result;
}
template <typename T>
inline Vector<T> operator-(T const& __first,
                           Vector<T> const& __second) noexcept {
  auto size = __second.size();
  Vector<T> result(size);
  auto retDatas = result.begin(), datas = __second.begin();
  for (size_t i = 0; i < size; i++) MNS(__first, datas[i], retDatas[i], T);
  return result;
}
template <typename T>
inline Vector<T> operator*(T const& __first,
                           Vector<T> const& __second) noexcept {
  auto size = __second.size();
  Vector<T> result(size);
  auto retDatas = result.begin(), datas = __second.begin();
  for (size_t i = 0; i < size; i++) MUL(__first, datas[i], retDatas[i], T);
  return result;
}
template <typename T>
inline Vector<T> operator/(T const& __first,
                           Vector<T> const& __second) noexcept {
  auto size = __second.size();
  Vector<T> result(size);
  auto retDatas = result.begin(), datas = __second.begin();
  for (size_t i = 0; i < size; i++) DIV(__first, datas[i], retDatas[i], T);
  return result;
}
template <typename T>
inline Vector<bool> operator==(T const& __first,
                               Vector<T> const& __second) noexcept {
  auto size = __second.size();
  Vector<bool> result(size);
  auto retDatas = result.begin(), datas = __second.begin();
  for (size_t i = 0; i < size; i++) retDatas[i] = __first == datas[i];
  return result;
}
template <typename T>
inline Vector<bool> operator!=(T const& __first,
                               Vector<T> const& __second) noexcept {
  auto size = __second.size();
  Vector<bool> result(size);
  auto retDatas = result.begin(), datas = __second.begin();
  for (size_t i = 0; i < size; i++) retDatas[i] = __first != datas[i];
  return result;
}
template <typename T>
inline Vector<bool> operator>=(T const& __first,
                               Vector<T> const& __second) noexcept {
  auto size = __second.size();
  Vector<bool> result(size);
  auto retDatas = result.begin(), datas = __second.begin();
  for (size_t i = 0; i < size; i++) retDatas[i] = __first >= datas[i];
  return result;
}
template <typename T>
inline Vector<bool> operator<=(T const& __first,
                               Vector<T> const& __second) noexcept {
  auto size = __second.size();
  Vector<bool> result(size);
  auto retDatas = result.begin(), datas = __second.begin();
  for (size_t i = 0; i < size; i++) retDatas[i] = __first <= datas[i];
  return result;
}
template <typename T>
inline Vector<bool> operator>(T const& __first,
                              Vector<T> const& __second) noexcept {
  auto size = __second.size();
  Vector<bool> result(size);
  auto retDatas = result.begin(), datas = __second.begin();
  for (size_t i = 0; i < size; i++) retDatas[i] = __first > datas[i];
  return result;
}
template <typename T>
inline Vector<bool> operator<(T const& __first,
                              Vector<T> const& __second) noexcept {
  auto size = __second.size();
  Vector<bool> result(size);
  auto retDatas = result.begin(), datas = __second.begin();
  for (size_t i = 0; i < size; i++) retDatas[i] = __first < datas[i];
  return result;
}
/**
 * @brief merge two Vector into one
 * @param __first the first one
 * @param __second the second one
 * @return the merged one
 * @throw none
 */
template <typename T>
inline Vector<T> merge(Vector<T> const& __first,
                       Vector<T> const& __second) noexcept {
  auto firstSize = __first.size();
  Vector<T> result(firstSize + __second.size());
  std::copy(__first.begin(), __first.end(), result.begin());
  std::copy(__second.begin(), __second.end(), result.begin() + firstSize);
  return result;
}
/**
 * @brief scan a sub Vector from the Vector
 * @param __vec the base vector
 * @param __low the lowwer bond
 * @param __up the upper bond
 * @return the sub Vector
 * @throw none
 */
template <typename T>
inline Vector<T> scan(Vector<T> const& __vec, size_t const& __low,
                      size_t const& __up) noexcept {
  if ((__low >= __up) || (__up > __vec.size())) {
    LOG("E:bad param");
    return Vector<T>();
  }
  Vector<T> ans(__up - __low);
  std::copy(__vec.begin() + __low, __vec.begin() + __up, ans.begin());
  return ans;
}
}  // namespace lina_lg
namespace basic_math {
/**
 * @brief uniformRand
 * @param __size the size of Vector
 * @param __min the min
 * @param __max the max
 * @return the answer
 * @throw none
 */
template <typename T>
inline lina_lg::Vector<T> uniformRand(size_t const& __size, T const& __min,
                                      T const& __max) noexcept {
  lina_lg::Vector<T> result(__size);
  for (auto& i : result) i = uniformRand(__min, __max);
  return result;
}
/**
 * @brief absolute
 * @param __vector the vector
 * @return the answer
 * @throw none
 */
template <typename T>
inline lina_lg::Vector<T> absolute(
    lina_lg::Vector<T> const& __vector) noexcept {
  lina_lg::Vector<T> result(__vector);
  for (auto& i : result) i = std::abs(i);
  return result;
}
/**
 * @brief pow
 * @param __vector the base
 * @param __exponent the exponent
 * @return the answer
 * @throw none
 */
template <typename T>
inline lina_lg::Vector<T> pow(lina_lg::Vector<T> const& __vector,
                              T const& __exponent) noexcept {
  lina_lg::Vector<T> result(__vector);
  for (auto& i : result) {
    if (i <= static_cast<T>(0)) LOG("E:danger basement");
    i = std::pow(i, __exponent);
  }
  return result;
}
/**
 * @brief pow
 * @param __base the base
 * @param __vector the exponent
 * @return the answer
 * @throw none
 */
template <typename T>
inline lina_lg::Vector<T> pow(T const& __base,
                              lina_lg::Vector<T> const& __vector) noexcept {
  lina_lg::Vector<T> result(__vector);
  if (__base > static_cast<T>(0))
    for (auto& i : result) i = std::pow(__base, i);
  else {
    LOG("E:danger basement");
    for (auto& i : result) i = std::pow(__base, i);
  }
  return result;
}
/**
 * @brief pow
 * @param __base the base
 * @param __exponent the exponent, size match to __base
 * @return the answer
 * @throw none
 */
template <typename T>
inline lina_lg::Vector<T> pow(lina_lg::Vector<T>const& __base,
                              lina_lg::Vector<T>const& __exponent) noexcept {
  if (__base.size() != __exponent.size()) {
    LOG("E:unmatch size");
    return lina_lg::Vector<T>(__base);
  }
  lina_lg::Vector<T> result(__base);
  auto i = result.begin(), w = __exponent.begin();
  while (i != result.end()) {
    if ((*i) <= static_cast<T>(0)) LOG("E:danger basement");
    (*i) = std::pow(*i, *w);
    i++;
    w++;
  }
  return result;
}
/**
 * @brief log
 * @param __vector the vector
 * @return the answer
 * @throw none
 */
template <typename T>
inline lina_lg::Vector<T> log(lina_lg::Vector<T>const& __vector) noexcept {
  lina_lg::Vector<T> result(__vector);
  for (auto& i : result)
    if (i > static_cast<T>(0))
      i = std::log(i);
    else {
      LOG("E:invalid log");
      i = static_cast<T>(0);
    }
  return result;
}
}  // namespace basic_math
#endif