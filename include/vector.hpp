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
    unsigned int size_;  // size of the vector

    template <typename U>
    friend std::ostream& operator<<(std::ostream&, Vector<U> const&);

    template <typename U>
    friend U dot(Vector<U> const&, Vector<U> const&);

    template <typename U>
    friend Vector<U> basic_math::random(unsigned int const&, U const&, U const&);

  public:
    // Factory functions to create and initialize a Vector instance
    static std::shared_ptr<Vector<T>> create(unsigned int const& size, T* const& data);
    static std::shared_ptr<Vector<T>> create(unsigned int const& size);
    static std::shared_ptr<Vector<T>> create();

    // Constructors
    Vector(unsigned int const& size, T* const& data);
    Vector(unsigned int const& size);
    Vector();
    Vector(const Vector& other);
    ~Vector();

    void initialize();  // Method to register with MemoryManager

    // Member functions
    inline unsigned int size() const { return this->size_; }
    T sum() const;
    void freedom();
    void resize(unsigned int const& newSize);
    void load(unsigned int const& size, T* const& data);

    // Operator overloads
    T& operator[](unsigned int const& index)const;
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

  template <typename Data>
  Data dot(const Vector<Data>&, const Vector<Data>&);

}  // namespace linalg

// Implementation
namespace linalg {

  template <typename T>
  std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
    os << "(" << vec.size() << ")";
    os << "[";
    for (auto i = 0; i < vec.size(); i++) {
      os << vec.data_[i];
      if (i != vec.size() - 1) os << ", ";
    }
    os << "]";
    return os;
  }

  template <typename T>
  std::shared_ptr<Vector<T>> Vector<T>::create(unsigned int const& size, T* const& data) {
    return std::make_shared<Vector<T>>(size, data);
  }

  template <typename T>
  std::shared_ptr<Vector<T>> Vector<T>::create(unsigned int const& size) {
    return std::make_shared<Vector<T>>(size);
  }

  template <typename T>
  std::shared_ptr<Vector<T>> Vector<T>::create() {
    return std::make_shared<Vector<T>>();
  }

  template <typename T>
  Vector<T>::Vector(unsigned int const& size, T* const& data) : size_(size), data_(new T[size]) {
    if (size == 0) throw std::invalid_argument("Size cannot be zero");
    if (data == nullptr) {
      throw std::invalid_argument("Pointer to array cannot be null");
    }
    else {
      std::copy(data, data + size, data_);
    }
    this->initialize();
    return;
  }

  template <typename T>
  Vector<T>::Vector(unsigned int const& size) : size_(size), data_(new T[size]) {
    if (size == 0) throw std::invalid_argument("Size cannot be zero");
    for (auto i = 0; i < size; i++) data_[i] = 0;
    this->initialize();
    return;
  }

  template <typename T>
  Vector<T>::Vector() : size_(1), data_(new T[1]) {
    data_[0] = 0;
    this->initialize();
    return;
  }

  template <typename T>
  Vector<T>::Vector(const Vector& other)
    : size_(other.size_), data_(new T[other.size_]) {
    std::copy(other.data_, other.data_ + other.size_, data_);
    this->initialize();
    return;
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
    for (auto i = 0; i < size_; i++) data_[i] = 0;
    memory_maintainer::MemoryManager::release<linalg::Vector<T>>(this);
  }

  template <typename T>
  T& Vector<T>::operator[](unsigned int const& i) const {
    if (i >= size_) throw std::invalid_argument("Index out of bounds");
    return data_[i];
  }

  template <typename T>
  T Vector<T>::sum() const {
    if (std::is_same_v<T, bool>) {
      T sum = 0;
      for (auto i = 0; i < size(); i++) sum += data_[i] ? 1 : -1;
      return static_cast<bool>(sum);
    }

    T sum = 0;
    for (auto i = 0; i < size(); i++) sum += data_[i];
    return sum;
  }

  template <typename T>
  T dot(const Vector<T>& a, const Vector<T>& b) {
    if (a.size() != b.size())
      throw std::invalid_argument("Vectors must have the same size");
    auto c = a * b;
    return c.sum();
  }

  template <typename T>
  void Vector<T>::resize(unsigned int const& newSize) {
    if (newSize == 0) throw std::invalid_argument("Size cannot be zero");
    if (newSize == size_) return;
    T* newData = new T[newSize];

    // Copy only up to the smaller of the old and new sizes
    unsigned int copySize = std::min(size_, newSize);
    std::copy(data_, data_ + copySize, newData);

    // If the new size is larger, initialize the new elements
    for (auto i = copySize; i < newSize; ++i) {
      newData[i] = static_cast<T>(0);  // Default-initialize new elements
    }

    delete[] data_;
    memory_maintainer::MemoryManager::modify<linalg::Vector<T>>(
      newSize, this->shared_from_this());
    data_ = newData;
    size_ = newSize;
    return;
  }

  template <typename T>
  void Vector<T>::load(unsigned int const& size, T* const& data) {
    if (data == nullptr) throw std::invalid_argument("Data cannot be null");

    T* newData = new T[size];
    std::copy(data, data + size, newData);

    delete[] data_;
    data_ = newData;
    size_ = size;

    memory_maintainer::MemoryManager::modify<linalg::Vector<T>>(size, this->shared_from_this());
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
    for (auto i = 0; i < size_; i++) data_[i] = value;
    return *this;
  }

  template <typename T>
  Vector<T> Vector<T>::operator+(const Vector<T>& other) const {
    if (size_ != other.size_)
      throw std::invalid_argument("Vectors must have the same size");
    Vector<T> result(size_);
    for (auto i = 0; i < size_; i++)
      __ADD(data_[i], other.data_[i], result.data_[i], T);
    return result;
  }

  template <typename T>
  Vector<T> Vector<T>::operator+(T const& value) const {
    Vector<T> result(size_);
    for (auto i = 0; i < size_; i++) __ADD(data_[i], value, result.data_[i], T);
    return result;
  }

  template <typename T>
  Vector<T> Vector<T>::operator-(const Vector<T>& other) const {
    if (size_ != other.size_)
      throw std::invalid_argument("Vectors must have the same size");
    Vector<T> result(size_);
    for (auto i = 0; i < size_; i++)
      __MNS(data_[i], other.data_[i], result.data_[i], T);
    return result;
  }

  template <typename T>
  Vector<T> Vector<T>::operator-(T const& value) const {
    Vector<T> result(size_);
    for (auto i = 0; i < size_; i++) __MNS(data_[i], value, result.data_[i], T);
    return result;
  }

  template <typename T>
  Vector<T> Vector<T>::operator*(const Vector<T>& other) const {
    if (size_ != other.size_)
      throw std::invalid_argument("Vectors must have the same size");
    Vector<T> result(size_);
    for (auto i = 0; i < size_; i++)
      __MUL(data_[i], other.data_[i], result.data_[i], T);
    return result;
  }

  template <typename T>
  Vector<T> Vector<T>::operator*(T const& value) const {
    Vector<T> result(size_);
    for (auto i = 0; i < size_; i++) __MUL(data_[i], value, result.data_[i], T);
    return result;
  }

  template <typename T>
  Vector<T> Vector<T>::operator/(const Vector<T>& other) const {
    if (size_ != other.size_)
      throw std::invalid_argument("Vectors must have the same size");
    Vector<T> result(size_);
    for (auto i = 0; i < size_; i++)
      __DIV(data_[i], other.data_[i], result.data_[i], T);
    return result;
  }

  template <typename T>
  Vector<T> Vector<T>::operator/(T const& value) const {
    Vector<T> result(size_);
    for (auto i = 0; i < size_; i++) __DIV(data_[i], value, result.data_[i], T);
    return result;
  }

  template <typename T>
  Vector<bool> Vector<T>::operator==(const Vector<T>& other) const {
    if (size_ != other.size_)
      throw std::invalid_argument("Vectors must have the same size");
    Vector<bool> result(size_);
    for (auto i = 0; i < size_; i++)
      result.data_[i] = (data_[i] == other.data_[i]);
    return result;
  }

  template <typename T>
  Vector<bool> Vector<T>::operator==(T const& value) const {
    Vector<bool> result(size_);
    for (auto i = 0; i < size_; i++) result.data_[i] = (data_[i] == value);
    return result;
  }

  template <typename T>
  Vector<bool> Vector<T>::operator!=(const Vector<T>& other) const {
    if (size_ != other.size_)
      throw std::invalid_argument("Vectors must have the same size");
    Vector<bool> result(size_);
    for (auto i = 0; i < size_; i++)
      result.data_[i] = (data_[i] != other.data_[i]);
    return result;
  }

  template <typename T>
  Vector<bool> Vector<T>::operator!=(T const& value) const {
    Vector<bool> result(size_);
    for (auto i = 0; i < size_; i++) result.data_[i] = (data_[i] != value);
    return result;
  }

  template <typename T>
  Vector<T>& Vector<T>::operator+=(const Vector<T>& other) {
    if (size_ != other.size_)
      throw std::invalid_argument("Vectors must have the same size");
    for (auto i = 0; i < size_; i++) __ADD(data_[i], other.data_[i], data_[i], T);
    return *this;
  }

  template <typename T>
  Vector<T>& Vector<T>::operator+=(T const& value) {
    for (auto i = 0; i < size_; i++) __ADD(data_[i], value, data_[i], T);
    return *this;
  }

  template <typename T>
  Vector<T>& Vector<T>::operator-=(const Vector<T>& other) {
    if (size_ != other.size_)
      throw std::invalid_argument("Vectors must have the same size");
    for (auto i = 0; i < size_; i++) __MNS(data_[i], other.data_[i], data_[i], T);
    return *this;
  }

  template <typename T>
  Vector<T>& Vector<T>::operator-=(T const& value) {
    for (auto i = 0; i < size_; i++) __MNS(data_[i], value, data_[i], T);
    return *this;
  }

  template <typename T>
  Vector<T>& Vector<T>::operator*=(const Vector<T>& other) {
    if (size_ != other.size_)
      throw std::invalid_argument("Vectors must have the same size");
    for (auto i = 0; i < size_; i++) __MUL(data_[i], other.data_[i], data_[i], T);
    return *this;
  }

  template <typename T>
  Vector<T>& Vector<T>::operator*=(T const& value) {
    for (auto i = 0; i < size_; i++) __MUL(data_[i], value, data_[i], T);
    return *this;
  }

  template <typename T>
  Vector<T>& Vector<T>::operator/=(const Vector<T>& other) {
    if (size_ != other.size_)
      throw std::invalid_argument("Vectors must have the same size");
    for (auto i = 0; i < size_; i++) __DIV(data_[i], other.data_[i], data_[i], T);
    return *this;
  }

  template <typename T>
  Vector<T>& Vector<T>::operator/=(T const& value) {
    for (auto i = 0; i < size_; i++) __DIV(data_[i], value, data_[i], T);
    return *this;
  }

  template <typename T>
  Vector<T> Vector<T>::operator-() const {
    Vector<T> result(size_);
    for (auto i = 0; i < size_; i++) result.data_[i] = -data_[i];
    return result;
  }

  template <typename T>
  Vector<bool> Vector<T>::operator<(const Vector<T>& other) const {
    if (size_ != other.size_)
      throw std::invalid_argument("Vectors must have the same size");
    Vector<bool> result(size_);
    for (auto i = 0; i < size_; i++) result.data_[i] = (data_[i] < other.data_[i]);
    return result;
  }

  template <typename T>
  Vector<bool> Vector<T>::operator>(const Vector<T>& other) const {
    if (size_ != other.size_)
      throw std::invalid_argument("Vectors must have the same size");
    Vector<bool> result(size_);
    for (auto i = 0; i < size_; i++) result.data_[i] = (data_[i] > other.data_[i]);
    return result;
  }

  template <typename T>
  Vector<bool> Vector<T>::operator<=(const Vector<T>& other) const {
    if (size_ != other.size_)
      throw std::invalid_argument("Vectors must have the same size");
    Vector<bool> result(size_);
    for (auto i = 0; i < size_; i++)
      result.data_[i] = (data_[i] <= other.data_[i]);
    return result;
  }

  template <typename T>
  Vector<bool> Vector<T>::operator>=(const Vector<T>& other) const {
    if (size_ != other.size_)
      throw std::invalid_argument("Vectors must have the same size");
    Vector<bool> result(size_);
    for (auto i = 0; i < size_; i++)
      result.data_[i] = (data_[i] >= other.data_[i]);
    return result;
  }

  template <typename T>
  Vector<bool> Vector<T>::operator<(T const& value) const {
    Vector<bool> result(size_);
    for (auto i = 0; i < size_; i++) result.data_[i] = (data_[i] < value);
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
    for (auto i = 0; i < size_; i++) result.data_[i] = (data_[i] <= value);
    return result;
  }

  template <typename T>
  Vector<bool> Vector<T>::operator>=(T const& value) const {
    Vector<bool> result(size_);
    for (auto i = 0; i < size_; i++) result.data_[i] = (data_[i] >= value);
    return result;
  }
}  // namespace linalg

#endif  // VECTOR_H
