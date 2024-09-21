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
}  // namespace basic_math

namespace linalg {

template <typename T>
class Vector {
 private:
  T* data_;            // pointer to the data
  unsigned int size_;  // size of the vector

  template <typename U>
  friend std::ostream& operator<<(std::ostream&, Vector<U> const&);

  template <typename U>
  friend Vector<U> basic_math::random(unsigned int const&, U const&, U const&);

  template <typename U>
  friend Vector<U> basic_math::absolute(Vector<U> const&);

  template <typename U, typename V>
  friend Vector<U> basic_math::pow(Vector<U> const&, V const&);

  template <typename U>
  friend class Vector;

 public:
  // Constructors
  Vector(unsigned int const& size, T* const& data);
  Vector(unsigned int const& size);
  Vector();
  Vector(const Vector& other);
  ~Vector();

  // Member functions
  inline unsigned int size() const { return this->size_; }
  T sum() const;
  void freedom();
  void resize(unsigned int const& newSize);
  void load(unsigned int const& size, T* const& data);
  inline T* begin() { return data_; }
  inline T* end() { return data_ + size_; }

  // Operator overloads
  T& operator[](unsigned int const& index) const;
  template <typename U>
  operator Vector<U>() {
    LOG("C:cast operator");
    if constexpr (std::is_same_v<U, T>) return *this;
    Vector<U> result(size_);
    for (unsigned int i = 0; i < size_; i++)
      result.data_[i] = static_cast<U>(data_[i]);
    return result;
  }
  Vector& operator=(const Vector& other);
  Vector& operator+=(const Vector& other);
  Vector& operator-=(const Vector& other);
  Vector& operator*=(const Vector& other);
  Vector& operator/=(const Vector& other);

  Vector operator+(const Vector& other) const;
  Vector operator-(const Vector& other) const;
  Vector operator*(const Vector& other) const;
  Vector operator/(const Vector& other) const;

  Vector<bool> operator==(const Vector& other) const;
  Vector<bool> operator!=(const Vector& other) const;
  Vector<bool> operator<(const Vector& other) const;
  Vector<bool> operator<=(const Vector& other) const;
  Vector<bool> operator>(const Vector& other) const;
  Vector<bool> operator>=(const Vector& other) const;

  Vector& operator=(T const& value);
  Vector& operator+=(T const& value);
  Vector& operator-=(T const& value);
  Vector& operator*=(T const& value);
  Vector& operator/=(T const& value);

  Vector operator+(T const& value) const;
  Vector operator-(T const& value) const;
  Vector operator*(T const& value) const;
  Vector operator/(T const& value) const;

  Vector operator-() const;

  Vector<bool> operator==(T const& value) const;
  Vector<bool> operator!=(T const& value) const;
  Vector<bool> operator<(T const& value) const;
  Vector<bool> operator<=(T const& value) const;
  Vector<bool> operator>(T const& value) const;
  Vector<bool> operator>=(T const& value) const;
};

template <typename Data>
std::ostream& operator<<(std::ostream&, const Vector<Data>&);

}  // namespace linalg

// Implementation
namespace linalg {

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
  LOG("C:print vector of %d elements", vec.size_);
  os << "(" << vec.size_ << ")";
  os << "[";
  for (unsigned int i = 0; i < vec.size_; i++) {
    os << vec.data_[i];
    if (i != vec.size_ - 1) os << ", ";
  }
  os << "]\n";
  return os;
}

template <typename T>
Vector<T>::Vector(unsigned int const& size, T* const& data) : size_(size) {
  LOG("C:init constructor ptr=%p,size=%d", static_cast<void*>(data), size);
  if (size == 0) {
    size_ = 1;
    LOG("E:the illegal size: %d has fixed to 1", size);
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
Vector<T>::Vector(unsigned int const& size) : size_(size) {
  LOG("C:size constrcutor size=%d", size);
  if (size == 0) {
    size_ = 1;
    LOG("E:the illegal size: %d has fixed to 1", size);
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
    return static_cast<bool>(sum);
  }

  T sum = 0;
  for (unsigned int i = 0; i < size(); i++) sum += data_[i];
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
void Vector<T>::load(unsigned int const& size, T* const& data) {
  LOG("C:load size=%d data=%p", size, static_cast<void*>(data));
  if (data == nullptr) {
    LOG("B:reading for null pointer");
    return;
  }
  if (size == 0) {
    LOG("B:the illegal size: %d", size);
    return;
  }
  T* newData = new T[size];
  std::copy(data, data + size, newData);

  delete[] data_;
  data_ = newData;
  size_ = size;

  if (!memory_maintainer::MemoryManager::modify<linalg::Vector<T>>(
          size * sizeof(T), this)) {
    LOG("B:MemoryManager return fail modify of %p", static_cast<void*>(this));
  }
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
    LOG("B:operate vectors in differ size (%d,%d)", this->size_, other.size_);
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
    LOG("B:operate vectors in differ size (%d,%d)", this->size_, other.size_);
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
    LOG("B:operate vectors in differ size (%d,%d)", this->size_, other.size_);
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
    LOG("B:operate vectors in differ size (%d,%d)", this->size_, other.size_);
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
    LOG("B:operate vectors in differ size (%d,%d)", this->size_, other.size_);
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
    LOG("B:operate vectors in differ size (%d,%d)", this->size_, other.size_);
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
    LOG("B:operate vectors in differ size (%d,%d)", this->size_, other.size_);
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
    LOG("B:operate vectors in differ size (%d,%d)", this->size_, other.size_);
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
    LOG("B:operate vectors in differ size (%d,%d)", this->size_, other.size_);
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
    LOG("B:operate vectors in differ size (%d,%d)", this->size_, other.size_);
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
    LOG("B:operate vectors in differ size (%d,%d)", this->size_, other.size_);
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
    LOG("B:operate vectors in differ size (%d,%d)", this->size_, other.size_);
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
    LOG("B:operate vectors in differ size (%d,%d)", this->size_, other.size_);
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
    LOG("B:operate vectors in differ size (%d,%d)", this->size_, other.size_);
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
  LOG("random vector");
  linalg::Vector<T> result(size);
  for (unsigned int i = 0; i < size; i++)
    result.data_[i] = basic_math::random(min, max);
  return result;
}

template <typename T>
linalg::Vector<T> absolute(linalg::Vector<T> const& param) {
  LOG("absolute vector");
  linalg::Vector<T> result(param);
  if constexpr (std::is_same_v<bool, T>) return result;
  for (unsigned int i = 0; i < result.size_; i++)
    if (result.data_[i] < 0) result.data_[i] *= static_cast<T>(-1);
  return result;
}

template <typename T, typename U>
linalg::Vector<T> pow(linalg::Vector<T> const& param, U const& value) {
  LOG("pow vector");
  linalg::Vector<T> result(param);
  if constexpr (std::is_same_v<bool, T>) return result;
  for (unsigned int i = 0; i < result.size_; i++)
    result.data_[i] = std::pow(result.data_[i], value);
  return result;
}
}  // namespace basic_math

#endif  // VECTOR_H
