#ifndef VECTOR_H
#define VECTOR_H

#include "basic.hpp"
#include "memory.hpp"

namespace linalg {
template <typename T>
class Vector {
 private:
  T* data_;   // pointer to the data
  int size_;  // size of the vector

  template <typename T>
  friend std::ostream& operator<<(std::ostream&, Vector<T> const&);

  template <typename T>
  friend T dot(Vector<T> const&, Vector<T> const&);

  template <typename T>
  friend Vector<T> cross(Vector<T> const&, Vector<T> const&);

  friend class linalg::Matrix<T>;

  template <typename T>
  friend Vector<T> basic_math::random(int, T const&, T const&);

  // TODO: AddRow and AddColumn for Matrix

 public:
  Vector(int size, Data* const& data);
  Vector(int size);
  Vector();
  Vector(const Vector& other);
  ~Vector();

  // Member functions
  inline int size() const { return this->size_; }
  Data sum() const;
  void freedom();
  bool endow(int index, Data const& value);
  bool resize(int newSize);
  bool load(int size, Data* const& data);

  // Operator overloads
  Data& operator[](int index);
  const Data& operator[](int index) const;
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

  Vector& operator=(Data const& value);
  Vector& operator+=(Data const& value);
  Vector& operator-=(Data const& value);
  Vector& operator*=(Data const& value);
  Vector& operator/=(Data const& value);

  Vector operator+(Data const& value) const;
  Vector operator-(Data const& value) const;
  Vector operator*(Data const& value) const;
  Vector operator/(Data const& value) const;

  Vector<bool> operator==(Data const& value) const;
  Vector<bool> operator!=(Data const& value) const;
  Vector<bool> operator<(Data const& value) const;
  Vector<bool> operator<=(Data const& value) const;
  Vector<bool> operator>(Data const& value) const;
  Vector<bool> operator>=(Data const& value) const;
};

template <typename Data>
std::ostream& operator<<(std::ostream&, const Vector<Data>&);

template <typename Data>
Data dot(const Vector<Data>&, const Vector<Data>&);
}  // namespace linalg

namespace linalg {

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
  os << "[";
  for (int i = 0; i < vec.size(); i++) {
    os << vec[i];
    if (i != vec.size() - 1) os << ", ";
  }
  os << "]";
  return os;
}

/**
 * Constructs a Vector object with the specified size and initializes its data
 * with the provided array. If the provided array is nullptr, the data is
 * initialized with zeros. The MemoryManager is then called to sign up the
 * allocated memory.
 *
 * @param size The size of the Vector.
 * @param data The array of data to initialize the Vector with.
 *
 * @throws None.
 */
template <typename T>
Vector<T>::Vector(int size, Data* const& data)
    : size(size), data_(new T[size]) {
  if (data == nullptr) {
    for (int i = 0; i < size; i++) data_[i] = 0;
  } else {
    std::copy(data, data + size, data_);
  }

  memory_maintainer::MemoryManager::signUp<T>(size, std::shared_ptr<T>(data_));
}

/**
 * Constructor for Vector class with a specified size.
 *
 * @param size The size of the Vector.
 *
 * @return None.
 *
 * @throws None.
 */
template <typename T>
Vector<T>::Vector(int size) : size(size), data_(new T[size]) {
  for (int i = 0; i < size; i++) data_[i] = 0;
  memory_maintainer::MemoryManager::signUp<T>(size, std::shared_ptr<T>(data_));
}

/**
 * Constructor for Vector class with default initialization.
 *
 * @param None.
 *
 * @return None.
 *
 * @throws None.
 */
template <typename T>
Vector<T>::Vector() : size(0), data_(nullptr) {
  memory_maintainer::MemoryManager::signUp<T>(0, std::shared_ptr<T>(data_));
}

/**
 * Copy constructor for the Vector class.
 *
 * @param other The Vector object to be copied.
 *
 * @throws None.
 */
template <typename T>
Vector<T>::Vector(const Vector& other) : size(other.size_), data_(new T[size]) {
  std::copy(other.data_, other.data_ + size, data_);
  memory_maintainer::MemoryManager::signUp<T>(size, std::shared_ptr<T>(data_));
}

template <typename T>
Vector<T>::~Vector() {
  memory_maintainer::MemoryManager::release<T>(std::shared_ptr<T>(data_));
}

}  // namespace linalg
#endif  // VECTOR_H