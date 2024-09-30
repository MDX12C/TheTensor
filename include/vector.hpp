#ifndef VECTOR_H
#define VECTOR_H 1

#include <algorithm>
#include <iostream>
#include <memory>

#include "basic.hpp"
#include "log.hpp"
#include "memory.hpp"

namespace basic_math {
template <typename T>
linalg::Vector<T> random(unsigned int const&, T const&, T const&);
template <typename T>
linalg::Vector<T> absolute(linalg::Vector<T> const&);
template <typename T, typename U>
linalg::Vector<T> pow(linalg::Vector<T> const&, U const&);
template <typename T, typename U>
linalg::Vector<T> pow(T const&, linalg::Vector<U> const&);
}  // namespace basic_math

namespace linalg {

template <typename T>
class Vector {
 private:
  T* data_;
  unsigned int size_;

  // friends
  template <typename U>
  friend std::ostream& operator<<(std::ostream&, Vector<U> const&);
  template <typename U>
  friend Vector<U> basic_math::random(unsigned int const&, U const&, U const&);
  template <typename U>
  friend Vector<U> basic_math::absolute(Vector<U> const&);
  template <typename U, typename V>
  friend Vector<U> basic_math::pow(Vector<U> const&, V const&);
  template <typename W, typename U>
  friend Vector<W> basic_math::pow(W const&, Vector<U> const&);
  template <typename U>
  friend class Vector;
  template <typename U>
  friend class Matrix;

 public:
  // Constructors
  Vector(unsigned int const&, T* const&);
  Vector(unsigned int const&);
  Vector();
  Vector(const Vector&);
  ~Vector();

  // Member functions
  inline unsigned int const& size() const { return size_; }
  T sum() const;
  void freedom();
  void resize(unsigned int const&);
  void load(unsigned int const&, T* const&);
  inline T* begin() { return data_; }
  inline T* end() { return data_ + size_; }

  // Operator overloads
  T& operator[](unsigned int const&) const;
  template <typename U>
  operator Vector<U>() {
    LOG("C:cast operator in Vector");
    if constexpr (std::is_same_v<U, T>) return *this;
    Vector<U> result(size_);
    for (unsigned int i = 0; i < size_; i++)
      result.data_[i] = static_cast<U>(data_[i]);
    return result;
  }
  Vector& operator=(const Vector&);
  Vector& operator+=(const Vector&);
  Vector& operator-=(const Vector&);
  Vector& operator*=(const Vector&);
  Vector& operator/=(const Vector&);

  Vector operator+(const Vector&) const;
  Vector operator-(const Vector&) const;
  Vector operator*(const Vector&) const;
  Vector operator/(const Vector&) const;

  Vector<bool> operator==(const Vector&) const;
  Vector<bool> operator!=(const Vector&) const;
  Vector<bool> operator<(const Vector&) const;
  Vector<bool> operator<=(const Vector&) const;
  Vector<bool> operator>(const Vector&) const;
  Vector<bool> operator>=(const Vector&) const;

  Vector& operator=(T const&);
  Vector& operator+=(T const&);
  Vector& operator-=(T const&);
  Vector& operator*=(T const&);
  Vector& operator/=(T const&);

  Vector operator+(T const&) const;
  Vector operator-(T const&) const;
  Vector operator*(T const&) const;
  Vector operator/(T const&) const;

  Vector operator-() const;

  Vector<bool> operator==(T const&) const;
  Vector<bool> operator!=(T const&) const;
  Vector<bool> operator<(T const&) const;
  Vector<bool> operator<=(T const&) const;
  Vector<bool> operator>(T const&) const;
  Vector<bool> operator>=(T const&) const;
};

template <typename Data>
std::ostream& operator<<(std::ostream&, const Vector<Data>&);

}  // namespace linalg

// Implementation
namespace linalg {

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
  LOG("C:print vector of %d elements", vec.size_);
  unsigned int digits = 0;
  os << std::noshowpos << '(' << vec.size_ << ')';
  if constexpr (std::is_same_v<T, float> || std::is_same_v<T, double>) {
    for (unsigned int i = 0; i < vec.size_; i++) {
      digits = std::max(digits, basic_math::intDigits(vec.data_[i]));
    }
    digits += 2;
    digits += basic_math::ACCURACY;
    os << std::setprecision(basic_math::ACCURACY) << std::fixed << std::showpos
       << std::internal << std::setfill(' ') << std::showpoint << '[';
  } else if constexpr (std::is_same_v<T, bool>) {
    digits = 1;
    os << '[';
  } else {
    for (unsigned int i = 0; i < vec.size_; i++) {
      digits = std::max(digits, basic_math::intDigits(vec.data_[i]));
    }
    digits += 1;
    os << std::showpos << std::internal << std::setfill(' ') << '[';
  }
  for (unsigned int i = 0; i < vec.size_; i++) {
    os << std::setw(digits) << vec.data_[i];
    if (i != vec.size_ - 1) os << ",";
  }
  os << "]\n";
  return os;
}

template <typename T>
Vector<T>::Vector(unsigned int const& vecSize, T* const& data)
    : size_(vecSize) {
  LOG("C:init constructor ptr=%p,size=%d", static_cast<void*>(data), vecSize);
  if (vecSize == 0) {
    size_ = 1;
    LOG("E:the illegal size: %d has fixed to 1", vecSize);
  }
  this->data_ = new T[size_];
  if (data == nullptr) {
    for (unsigned int i = 0; i < size_; i++) data_[i] = static_cast<T>(0);
    LOG("E:null pointer can't be init data,all thing in vector will be 0");
  } else {
    std::copy(data, data + size_, data_);
  }
  if (!memory_maintainer::MemoryManager::signUp<linalg::Vector<T>>(
          size_ * sizeof(T), this)) {
    LOG("B:MemoryManager return fail signUp of %p", static_cast<void*>(this));
  }
  return;
}

template <typename T>
Vector<T>::Vector(unsigned int const& vecSize) : size_(vecSize) {
  LOG("C:size constrcutor size=%d", vecSize);
  if (vecSize == 0) {
    size_ = 1;
    LOG("E:the illegal size: %d has fixed to 1", vecSize);
  }
  this->data_ = new T[size_];
  for (unsigned int i = 0; i < size_; i++) data_[i] = static_cast<T>(0);
  if (!memory_maintainer::MemoryManager::signUp<linalg::Vector<T>>(
          size_ * sizeof(T), this)) {
    LOG("B:MemoryManager return fail signUp of %p", static_cast<void*>(this));
  }
  return;
}

template <typename T>
Vector<T>::Vector() : size_(1), data_(new T[1]) {
  LOG("C:default constructor");
  data_[0] = static_cast<T>(0);
  if (!memory_maintainer::MemoryManager::signUp<linalg::Vector<T>>(
          size_ * sizeof(T), this)) {
    LOG("B:MemoryManager return fail signUp of %p", static_cast<void*>(this));
  }
  return;
}

template <typename T>
Vector<T>::Vector(const Vector& other)
    : size_(other.size_), data_(new T[other.size_]) {
  LOG("C:copy constructor");
  std::copy(other.data_, other.data_ + other.size_, data_);
  if (!memory_maintainer::MemoryManager::signUp<linalg::Vector<T>>(
          size_ * sizeof(T), this)) {
    LOG("B:MemoryManager return fail signUp of %p", static_cast<void*>(this));
  }
  return;
}

template <typename T>
Vector<T>::~Vector() {
  LOG("C:destructor");
  if (!memory_maintainer::MemoryManager::release<linalg::Vector<T>>(this)) {
    LOG("B:MemoryManager return fail release of %p", static_cast<void*>(this));
  }
  delete[] data_;
}

template <typename T>
void Vector<T>::freedom() {
  LOG("C:freedom");
  delete[] data_;
  size_ = 1;
  data_ = new T[size_];
  data_[0] = static_cast<T>(0);
  if (!memory_maintainer::MemoryManager::modify<linalg::Vector<T>>(
          size_ * sizeof(T), this)) {
    LOG("B:MemoryManager return fail modify of %p", static_cast<void*>(this));
  }
  return;
}

template <typename T>
T& Vector<T>::operator[](unsigned int const& i) const {
  if (i >= size_) {
    LOG("E:exceed boundary");
    return data_[0];
  }
  return data_[i];
}

template <typename T>
T Vector<T>::sum() const {
  LOG("C:sum");
  if (std::is_same_v<T, bool>) {
    T sum = 0;
    for (unsigned int i = 0; i < size_; i++) sum += data_[i] ? 1 : -1;
    return sum > 0 ? true : false;
  }

  T sum = 0;
  for (unsigned int i = 0; i < size_; i++) sum += data_[i];
  return sum;
}

template <typename T>
void Vector<T>::resize(unsigned int const& newSize) {
  LOG("C:resize newSize=%d", newSize);
  if (newSize == size_) return;
  if (newSize == 0) {
    LOG("B:the illegal size: %d", newSize);
    return;
  }

  T* newData = new T[newSize];

  // Copy only up to the smaller of the old and new sizes
  unsigned int copySize = std::min(size_, newSize);
  std::copy(data_, data_ + copySize, newData);

  // If the new size is larger, initialize the new elements
  for (auto i = copySize; i < newSize; ++i) {
    newData[i] = static_cast<T>(0);  // Default-initialize new elements
  }

  delete[] data_;
  if (!memory_maintainer::MemoryManager::modify<linalg::Vector<T>>(
          newSize * sizeof(T), this)) {
    LOG("B:MemoryManager return fail modify of %p", static_cast<void*>(this));
  }
  data_ = newData;
  size_ = newSize;
  return;
}

template <typename T>
void Vector<T>::load(unsigned int const& vecSize, T* const& data) {
  LOG("C:load size=%d data=%p", vecSize, static_cast<void*>(data));
  if (data == nullptr) {
    LOG("B:reading for null pointer");
    return;
  }
  if (vecSize == 0) {
    LOG("B:the illegal size: %d", vecSize);
    return;
  }
  T* newData = new T[vecSize];
  std::copy(data, data + vecSize, newData);

  delete[] data_;
  data_ = newData;
  size_ = vecSize;

  if (!memory_maintainer::MemoryManager::modify<linalg::Vector<T>>(
          size_ * sizeof(T), this)) {
    LOG("B:MemoryManager return fail modify of %p", static_cast<void*>(this));
  }

  return;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
  if (this != &other) {
    delete[] data_;
    data_ = new T[other.size_];
    std::copy(other.data_, other.data_ + other.size_, data_);
    size_ = other.size_;
  }
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(T const& value) {
  for (unsigned int i = 0; i < size_; i++) data_[i] = value;
  return *this;
}

template <typename T>
Vector<T> Vector<T>::operator+(const Vector<T>& other) const {
  if (size_ != other.size_) {
    LOG("E:operate vectors in differ size (%d,%d)", this->size_, other.size_);
    return *this;
  }
  Vector<T> result(size_);
  for (unsigned int i = 0; i < size_; i++)
    __ADD(data_[i], other.data_[i], result.data_[i], T);
  return result;
}

template <typename T>
Vector<T> Vector<T>::operator+(T const& value) const {
  Vector<T> result(size_);
  for (unsigned int i = 0; i < size_; i++)
    __ADD(data_[i], value, result.data_[i], T);
  return result;
}

template <typename T>
Vector<T> Vector<T>::operator-(const Vector<T>& other) const {
  if (size_ != other.size_) {
    LOG("E:operate vectors in differ size (%d,%d)", this->size_, other.size_);
    return *this;
  }
  Vector<T> result(size_);
  for (unsigned int i = 0; i < size_; i++)
    __MNS(data_[i], other.data_[i], result.data_[i], T);
  return result;
}

template <typename T>
Vector<T> Vector<T>::operator-(T const& value) const {
  Vector<T> result(size_);
  for (unsigned int i = 0; i < size_; i++)
    __MNS(data_[i], value, result.data_[i], T);
  return result;
}

template <typename T>
Vector<T> Vector<T>::operator*(const Vector<T>& other) const {
  if (size_ != other.size_) {
    LOG("E:operate vectors in differ size (%d,%d)", this->size_, other.size_);
    return *this;
  }
  Vector<T> result(size_);
  for (unsigned int i = 0; i < size_; i++)
    __MUL(data_[i], other.data_[i], result.data_[i], T);
  return result;
}

template <typename T>
Vector<T> Vector<T>::operator*(T const& value) const {
  Vector<T> result(size_);
  for (unsigned int i = 0; i < size_; i++)
    __MUL(data_[i], value, result.data_[i], T);
  return result;
}

template <typename T>
Vector<T> Vector<T>::operator/(const Vector<T>& other) const {
  if (size_ != other.size_) {
    LOG("E:operate vectors in differ size (%d,%d)", this->size_, other.size_);
    return *this;
  }
  Vector<T> result(size_);
  for (unsigned int i = 0; i < size_; i++)
    __DIV(data_[i], other.data_[i], result.data_[i], T);
  return result;
}

template <typename T>
Vector<T> Vector<T>::operator/(T const& value) const {
  Vector<T> result(size_);
  for (unsigned int i = 0; i < size_; i++)
    __DIV(data_[i], value, result.data_[i], T);
  return result;
}

template <typename T>
Vector<bool> Vector<T>::operator==(const Vector<T>& other) const {
  if (size_ != other.size_) {
    LOG("E:operate vectors in differ size (%d,%d)", this->size_, other.size_);
    Vector<bool> temp(this->size_);
    temp = false;
    return temp;
  }
  Vector<bool> result(size_);
  for (unsigned int i = 0; i < size_; i++)
    result.data_[i] = (data_[i] == other.data_[i]);
  return result;
}

template <typename T>
Vector<bool> Vector<T>::operator==(T const& value) const {
  Vector<bool> result(size_);
  for (unsigned int i = 0; i < size_; i++)
    result.data_[i] = (data_[i] == value);
  return result;
}

template <typename T>
Vector<bool> Vector<T>::operator!=(const Vector<T>& other) const {
  if (size_ != other.size_) {
    LOG("E:operate vectors in differ size (%d,%d)", this->size_, other.size_);
    Vector<bool> temp(this->size_);
    temp = false;
    return temp;
  }
  Vector<bool> result(size_);
  for (unsigned int i = 0; i < size_; i++)
    result.data_[i] = (data_[i] != other.data_[i]);
  return result;
}

template <typename T>
Vector<bool> Vector<T>::operator!=(T const& value) const {
  Vector<bool> result(size_);
  for (unsigned int i = 0; i < size_; i++)
    result.data_[i] = (data_[i] != value);
  return result;
}

template <typename T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& other) {
  if (size_ != other.size_) {
    LOG("E:operate vectors in differ size (%d,%d)", this->size_, other.size_);
    return *this;
  }
  for (unsigned int i = 0; i < size_; i++)
    __ADD(data_[i], other.data_[i], data_[i], T);
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator+=(T const& value) {
  for (unsigned int i = 0; i < size_; i++) __ADD(data_[i], value, data_[i], T);
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator-=(const Vector<T>& other) {
  if (size_ != other.size_) {
    LOG("E:operate vectors in differ size (%d,%d)", this->size_, other.size_);
    return *this;
  }
  for (unsigned int i = 0; i < size_; i++)
    __MNS(data_[i], other.data_[i], data_[i], T);
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator-=(T const& value) {
  for (unsigned int i = 0; i < size_; i++) __MNS(data_[i], value, data_[i], T);
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator*=(const Vector<T>& other) {
  if (size_ != other.size_) {
    LOG("E:operate vectors in differ size (%d,%d)", this->size_, other.size_);
    return *this;
  }
  for (unsigned int i = 0; i < size_; i++)
    __MUL(data_[i], other.data_[i], data_[i], T);
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator*=(T const& value) {
  for (unsigned int i = 0; i < size_; i++) __MUL(data_[i], value, data_[i], T);
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator/=(const Vector<T>& other) {
  if (size_ != other.size_) {
    LOG("E:operate vectors in differ size (%d,%d)", this->size_, other.size_);
    return *this;
  }
  for (unsigned int i = 0; i < size_; i++)
    __DIV(data_[i], other.data_[i], data_[i], T);
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator/=(T const& value) {
  for (unsigned int i = 0; i < size_; i++) __DIV(data_[i], value, data_[i], T);
  return *this;
}

template <typename T>
Vector<T> Vector<T>::operator-() const {
  Vector<T> result(size_);
  for (unsigned int i = 0; i < size_; i++) result.data_[i] = -data_[i];
  return result;
}

template <typename T>
Vector<bool> Vector<T>::operator<(const Vector<T>& other) const {
  if (size_ != other.size_) {
    LOG("E:operate vectors in differ size (%d,%d)", this->size_, other.size_);
    Vector<bool> temp(this->size_);
    temp = false;
    return temp;
  }
  Vector<bool> result(size_);
  for (unsigned int i = 0; i < size_; i++)
    result.data_[i] = (data_[i] < other.data_[i]);
  return result;
}

template <typename T>
Vector<bool> Vector<T>::operator>(const Vector<T>& other) const {
  if (size_ != other.size_) {
    LOG("E:operate vectors in differ size (%d,%d)", this->size_, other.size_);
    Vector<bool> temp(this->size_);
    temp = false;
    return temp;
  }
  Vector<bool> result(size_);
  for (unsigned int i = 0; i < size_; i++)
    result.data_[i] = (data_[i] > other.data_[i]);
  return result;
}

template <typename T>
Vector<bool> Vector<T>::operator<=(const Vector<T>& other) const {
  if (size_ != other.size_) {
    LOG("E:operate vectors in differ size (%d,%d)", this->size_, other.size_);
    Vector<bool> temp(this->size_);
    temp = false;
    return temp;
  }
  Vector<bool> result(size_);
  for (unsigned int i = 0; i < size_; i++)
    result.data_[i] = (data_[i] <= other.data_[i]);
  return result;
}

template <typename T>
Vector<bool> Vector<T>::operator>=(const Vector<T>& other) const {
  if (size_ != other.size_) {
    LOG("E:operate vectors in differ size (%d,%d)", this->size_, other.size_);
    Vector<bool> temp(this->size_);
    temp = false;
    return temp;
  }
  Vector<bool> result(size_);
  for (unsigned int i = 0; i < size_; i++)
    result.data_[i] = (data_[i] >= other.data_[i]);
  return result;
}

template <typename T>
Vector<bool> Vector<T>::operator<(T const& value) const {
  Vector<bool> result(size_);
  for (unsigned int i = 0; i < size_; i++) result.data_[i] = (data_[i] < value);
  return result;
}

template <typename T>
Vector<bool> Vector<T>::operator>(T const& value) const {
  Vector<bool> result(size_);
  for (auto i = 0; i < size_; i++) result.data_[i] = (data_[i] > value);
  return result;
}

template <typename T>
Vector<bool> Vector<T>::operator<=(T const& value) const {
  Vector<bool> result(size_);
  for (unsigned int i = 0; i < size_; i++)
    result.data_[i] = (data_[i] <= value);
  return result;
}

template <typename T>
Vector<bool> Vector<T>::operator>=(T const& value) const {
  Vector<bool> result(size_);
  for (unsigned int i = 0; i < size_; i++)
    result.data_[i] = (data_[i] >= value);
  return result;
}
}  // namespace linalg
namespace basic_math {
template <typename T>
linalg::Vector<T> random(unsigned int const& size, T const& min, T const& max) {
  LOG("C:random vector");
  linalg::Vector<T> result(size);
  for (unsigned int i = 0; i < size; i++)
    result.data_[i] = basic_math::random(min, max);
  return result;
}

template <typename T>
linalg::Vector<T> absolute(linalg::Vector<T> const& param) {
  LOG("C:absolute vector");
  linalg::Vector<T> result(param);
  if constexpr (std::is_same_v<bool, T>) return result;
  for (unsigned int i = 0; i < result.size_; i++)
    if (result.data_[i] < 0) result.data_[i] *= static_cast<T>(-1);
  return result;
}

template <typename T, typename U>
linalg::Vector<T> pow(linalg::Vector<T> const& param, U const& value) {
  LOG("C:pow vector");
  linalg::Vector<T> result(param);
  if constexpr (std::is_same_v<bool, T>) return result;
  for (unsigned int i = 0; i < result.size_; i++)
    result.data_[i] = std::pow(result.data_[i], value);
  return result;
}

template <typename T, typename U>
linalg::Vector<T> pow(T const& value, linalg::Vector<U> const& param) {
  LOG("C:pow vector");
  linalg::Vector<T> result(param.size_);
  if constexpr (std::is_same_v<T, bool>) {
    result = value;
    return result;
  }
  for (unsigned int i = 0; i < result.size_; i++) {
    result.data_[i] = std::pow(value, param.data_[i]);
  }
  return result;
}
}  // namespace basic_math

#endif  // VECTOR_H
