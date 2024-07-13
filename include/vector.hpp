#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <iostream>
#include <memory>

#include "basic.hpp"
#include "memory.hpp"

namespace linalg {

template <typename T>
class Vector : public std::enable_shared_from_this<Vector<T>> {
 private:
  T* data_;   // pointer to the data
  int size_;  // size of the vector

  template <typename U>
  friend std::ostream& operator<<(std::ostream&, Vector<U> const&);

  template <typename U>
  friend U dot(Vector<U> const&, Vector<U> const&);

  template <typename U>
  friend Vector<U> cross(Vector<U> const&, Vector<U> const&);

  template <typename U>
  friend Vector<U> basic_math::random(int, U const&, U const&);

 public:
  // Factory functions to create and initialize a Vector instance
  static std::shared_ptr<Vector<T>> create(int size, T* const& data);
  static std::shared_ptr<Vector<T>> create(int size);
  static std::shared_ptr<Vector<T>> create();

  // Constructors
  Vector(int size, T* const& data);
  Vector(int size);
  Vector();
  Vector(const Vector& other);
  ~Vector();

  void initialize();  // Method to register with MemoryManager

  // Member functions
  inline int size() const { return this->size_; }
  T sum() const;
  void freedom();
  void endow(int const& index,
             T const& value);  // Modifies the value at the index
  void resize(int newSize);
  void load(int size, T* const& data);

  // Operator overloads
  T& operator[](int index);
  const T& operator[](int index) const;
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

  Vector<bool> operator==(T const& value) const;
  Vector<bool> operator!=(T const& value) const;
  Vector<bool> operator<(T const& value) const;
  Vector<bool> operator<=(T const& value) const;
  Vector<bool> operator>(T const& value) const;
  Vector<bool> operator>=(T const& value) const;
};

template <typename Data>
std::ostream& operator<<(std::ostream&, const Vector<Data>&);

template <typename Data>
Data dot(const Vector<Data>&, const Vector<Data>&);

}  // namespace linalg

// Implementation
namespace linalg {

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
  os << "(" << vec.size() << ")";
  os << "[";
  for (int i = 0; i < vec.size(); i++) {
    os << vec.data_[i];
    if (i != vec.size() - 1) os << ", ";
  }
  os << "]";
  return os;
}

template <typename T>
std::shared_ptr<Vector<T>> Vector<T>::create(int size, T* const& data) {
  auto vec = std::make_shared<Vector<T>>(size, data);
  vec->initialize();
  return vec;
}

template <typename T>
std::shared_ptr<Vector<T>> Vector<T>::create(int size) {
  auto vec = std::make_shared<Vector<T>>(size);
  vec->initialize();
  return vec;
}

template <typename T>
std::shared_ptr<Vector<T>> Vector<T>::create() {
  auto vec = std::make_shared<Vector<T>>();
  vec->initialize();
  return vec;
}

template <typename T>
Vector<T>::Vector(int size, T* const& data) : size_(size), data_(new T[size]) {
  if (data == nullptr) {
    for (int i = 0; i < size; i++) data_[i] = 0;
  } else {
    std::copy(data, data + size, data_);
  }
}

template <typename T>
Vector<T>::Vector(int size) : size_(size), data_(new T[size]) {
  for (int i = 0; i < size; i++) data_[i] = 0;
}

template <typename T>
Vector<T>::Vector() : size_(0), data_(nullptr) {}

template <typename T>
Vector<T>::Vector(const Vector& other)
    : size_(other.size_), data_(new T[other.size_]) {
  std::copy(other.data_, other.data_ + other.size_, data_);
}

template <typename T>
Vector<T>::~Vector() {
  memory_maintainer::MemoryManager::release<linalg::Vector<T>>(this);
  delete[] data_;
}

template <typename T>
void Vector<T>::initialize() {
  memory_maintainer::MemoryManager::signUp<linalg::Vector<T>>(
      size_, this->shared_from_this());
}

template <typename T>
void Vector<T>::freedom() {
  delete[] data_;
  data_ = new T[size_];
  for (int i = 0; i < size_; i++) data_[i] = 0;
  memory_maintainer::MemoryManager::release<linalg::Vector<T>>(this);
}

template <typename T>
T& Vector<T>::operator[](int i) {
  return data_[i];
}

template <typename T>
T const& Vector<T>::operator[](int i) const {
  return data_[i];
}

template <typename T>
T Vector<T>::sum() const {
  if (std::is_same_v<T, bool>) {
    T sum = 0;
    for (int i = 0; i < size(); i++) sum += data_[i] ? 1 : -1;
    return static_cast<bool>(sum);
  }

  T sum = 0;
  for (int i = 0; i < size(); i++) sum += data_[i];
  return sum;
}

template <typename T>
T sum(const Vector<T>& vec) {
  T sum = 0;
  for (int i = 0; i < vec.size(); i++) sum += vec.data_[i];
  return sum;
}

template <typename T>
T dot(const Vector<T>& a, const Vector<T>& b) {
  T sum = 0;
  for (int i = 0; i < a.size(); i++) sum += a.data_[i] * b.data_[i];
  return sum;
}

template <typename T>
void Vector<T>::endow(int const& index, T const& value) {
  if (index < 0 || index >= size_)
    throw std::out_of_range("Index out of range");
  data_[index] = value;
}

template <typename T>
void Vector<T>::resize(int newSize) {
  if (newSize <= 0) throw std::invalid_argument("New size must be positive");

  T* newData = new T[newSize];

  // Copy only up to the smaller of the old and new sizes
  int copySize = std::min(size_, newSize);
  std::copy(data_, data_ + copySize, newData);

  // If the new size is larger, initialize the new elements
  for (int i = copySize; i < newSize; ++i) {
    newData[i] = T();  // Default-initialize new elements
  }

  delete[] data_;
  memory_maintainer::MemoryManager::modify<linalg::Vector<T>>(
      newSize, this->shared_from_this());
  data_ = newData;
  size_ = newSize;
}

template <typename T>
void Vector<T>::load(int size, T* const& data) {
  if (size < 0 || size >= size_)
    throw std::invalid_argument(
        "Size must be non-negative and less than the size of the vector");
  if (data == nullptr) throw std::invalid_argument("Data cannot be null");

  T* newData = new T[size];
  std::copy(data, data + size, newData);

  delete[] data_;
  data_ = newData;
  size_ = size;

  memory_maintainer::MemoryManager::modify<linalg::Vector<T>>(
      size, this->shared_from_this());
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
  for (int i = 0; i < size_; i++) data_[i] = value;
  return *this;
}

template <typename T>
Vector<T> Vector<T>::operator+(const Vector<T>& other) const {
  if (size_ != other.size_)
    throw std::invalid_argument("Vectors must have the same size");
  Vector<T> result(size_);
  for (int i = 0; i < size_; i++)
    __ADD(data_[i], other.data_[i], result.data_[i], T);
  return result;
}

template <typename T>
Vector<T> Vector<T>::operator+(T const& value) const {
  Vector<T> result(size_);
  for (int i = 0; i < size_; i++) __ADD(data_[i], value, result.data_[i], T);
  return result;
}

template <typename T>
Vector<T> Vector<T>::operator-(const Vector<T>& other) const {
  if (size_ != other.size_)
    throw std::invalid_argument("Vectors must have the same size");
  Vector<T> result(size_);
  for (int i = 0; i < size_; i++)
    __MNS(data_[i], other.data_[i], result.data_[i], T);
  return result;
}

template <typename T>
Vector<T> Vector<T>::operator-(T const& value) const {
  Vector<T> result(size_);
  for (int i = 0; i < size_; i++) __MNS(data_[i], value, result.data_[i], T);
  return result;
}

template <typename T>
Vector<T> Vector<T>::operator*(const Vector<T>& other) const {
  if (size_ != other.size_)
    throw std::invalid_argument("Vectors must have the same size");
  Vector<T> result(size_);
  for (int i = 0; i < size_; i++)
    __MUL(data_[i], other.data_[i], result.data_[i], T);
  return result;
}

template <typename T>
Vector<T> Vector<T>::operator*(T const& value) const {
  Vector<T> result(size_);
  for (int i = 0; i < size_; i++) __MUL(data_[i], value, result.data_[i], T);
  return result;
}

template <typename T>
Vector<T> Vector<T>::operator/(const Vector<T>& other) const {
  if (size_ != other.size_)
    throw std::invalid_argument("Vectors must have the same size");
  Vector<T> result(size_);
  for (int i = 0; i < size_; i++)
    __DIV(data_[i], other.data_[i], result.data_[i], T);
  return result;
}

template <typename T>
Vector<T> Vector<T>::operator/(T const& value) const {
  Vector<T> result(size_);
  for (int i = 0; i < size_; i++) __DIV(data_[i], value, result.data_[i], T);
  return result;
}

template <typename T>
Vector<bool> Vector<T>::operator==(const Vector<T>& other) const {
  if (size_ != other.size_)
    throw std::invalid_argument("Vectors must have the same size");
  Vector<bool> result(size_);
  for (int i = 0; i < size_; i++)
    result.data_[i] = (data_[i] == other.data_[i]);
  return result;
}

template <typename T>
Vector<bool> Vector<T>::operator==(T const& value) const {
  Vector<bool> result(size_);
  for (int i = 0; i < size_; i++) result.data_[i] = (data_[i] == value);
  return result;
}

template <typename T>
Vector<bool> Vector<T>::operator!=(const Vector<T>& other) const {
  if (size_ != other.size_)
    throw std::invalid_argument("Vectors must have the same size");
  Vector<bool> result(size_);
  for (int i = 0; i < size_; i++)
    result.data_[i] = (data_[i] != other.data_[i]);
  return result;
}

template <typename T>
Vector<bool> Vector<T>::operator!=(T const& value) const {
  Vector<bool> result(size_);
  for (int i = 0; i < size_; i++) result.data_[i] = (data_[i] != value);
  return result;
}

template <typename T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& other) {
  if (size_ != other.size_)
    throw std::invalid_argument("Vectors must have the same size");
  for (int i = 0; i < size_; i++) __ADD(data_[i], other.data_[i], data_[i], T);
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator+=(T const& value) {
  for (int i = 0; i < size_; i++) __ADD(data_[i], value, data_[i], T);
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator-=(const Vector<T>& other) {
  if (size_ != other.size_)
    throw std::invalid_argument("Vectors must have the same size");
  for (int i = 0; i < size_; i++) __MNS(data_[i], other.data_[i], data_[i], T);
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator-=(T const& value) {
  for (int i = 0; i < size_; i++) __MNS(data_[i], value, data_[i], T);
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator*=(const Vector<T>& other) {
  if (size_ != other.size_)
    throw std::invalid_argument("Vectors must have the same size");
  for (int i = 0; i < size_; i++) __MUL(data_[i], other.data_[i], data_[i], T);
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator*=(T const& value) {
  for (int i = 0; i < size_; i++) __MUL(data_[i], value, data_[i], T);
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator/=(const Vector<T>& other) {
  if (size_ != other.size_)
    throw std::invalid_argument("Vectors must have the same size");
  for (int i = 0; i < size_; i++) __DIV(data_[i], other.data_[i], data_[i], T);
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator/=(T const& value) {
  for (int i = 0; i < size_; i++) __DIV(data_[i], value, data_[i], T);
  return *this;
}

template <typename T>
Vector<T> Vector<T>::operator-() const {
  Vector<T> result(size_);
  for (int i = 0; i < size_; i++) result.data_[i] = -data_[i];
  return result;
}

template <typename T>
Vector<bool> Vector<T>::operator<(const Vector<T>& other) const {
  if (size_ != other.size_)
    throw std::invalid_argument("Vectors must have the same size");
  Vector<bool> result(size_);
  for (int i = 0; i < size_; i++) result.data_[i] = (data_[i] < other.data_[i]);
  return result;
}

template <typename T>
Vector<bool> Vector<T>::operator>(const Vector<T>& other) const {
  if (size_ != other.size_)
    throw std::invalid_argument("Vectors must have the same size");
  Vector<bool> result(size_);
  for (int i = 0; i < size_; i++) result.data_[i] = (data_[i] > other.data_[i]);
  return result;
}

tamplate<typename T> Vector<bool> Vector<T>::operator<=(
    const Vector<T>& other) const {
  if (size_ != other.size_)
    throw std::invalid_argument("Vectors must have the same size");
  Vector<bool> result(size_);
  for (int i = 0; i < size_; i++)
    result.data_[i] = (data_[i] <= other.data_[i]);
  return result;
}

template <typename T>
Vector<bool> Vector<T>::operator>=(const Vector<T>& other) const {
  if (size_ != other.size_)
    throw std::invalid_argument("Vectors must have the same size");
  Vector<bool> result(size_);
  for (int i = 0; i < size_; i++)
    result.data_[i] = (data_[i] >= other.data_[i]);
  return result;
}

template <typename T>
Vector<bool> Vector<T>::operator<(T const& value) const {
  Vector<bool> result(size_);
  for (int i = 0; i < size_; i++) result.data_[i] = (data_[i] < value);
  return result;
}

template <typename T>
Vector<bool> Vector<T>::operator>(T const& value) const {
  Vector<bool> result(size_);
  for (int i = 0; i < size_; i++) result.data_[i] = (data_[i] > value);
  return result;
}

template <typename T>
Vector<bool> Vector<T>::operator<=(T const& value) const {
  Vector<bool> result(size_);
  for (int i = 0; i < size_; i++) result.data_[i] = (data_[i] <= value);
  return result;
}

template <typename T>
Vector<bool> Vector<T>::operator>=(T const& value) const {
  Vector<bool> result(size_);
  for (int i = 0; i < size_; i++) result.data_[i] = (data_[i] >= value);
  return result;
}
}  // namespace linalg

#endif  // VECTOR_H