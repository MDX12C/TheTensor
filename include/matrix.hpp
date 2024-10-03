#ifndef MATRIX_H
#define MATRIX_H 1

#include "basic.hpp"
#include "log.hpp"
#include "memory.hpp"

namespace basic_math {
template <typename T>
inline linalg::Matrix<T> random(unsigned int const&, unsigned int const&,
                                T const&, T const&);
template <typename T>
inline linalg::Matrix<T> absolute(linalg::Matrix<T> const&);
template <typename T, typename U>
inline linalg::Matrix<T> pow(linalg::Matrix<T> const&, U const&);
template <typename T, typename U>
inline linalg::Matrix<U> pow(U const&, linalg::Matrix<T> const&);
template <typename T>
inline linalg::Matrix<T> dot(linalg::Matrix<T> const&,
                             linalg::Matrix<T> const&);
}  // namespace basic_math

namespace linalg {

template <typename T>
class Matrix {
 private:
  T* data_;
  MaShape shape_;

  // friends
  template <typename U>
  friend inline std::ostream& operator<<(std::ostream&, Matrix<U> const&);
  template <typename U>
  friend inline Matrix<U> basic_math::random(unsigned int const&,
                                             unsigned int const&, U const&,
                                             U const&);
  template <typename U>
  friend inline Matrix<U> basic_math::absolute(Matrix<U> const&);
  template <typename U, typename W>
  friend inline Matrix<U> basic_math::pow(Matrix<U> const&, W const&);
  template <typename U, typename W>
  friend inline Matrix<W> basic_math::pow(W const&, Matrix<U> const&);
  template <typename U>
  friend inline Matrix<U> basic_math::dot(Matrix<U> const&, Matrix<U> const&);
  template <typename U>
  friend inline Matrix<U> mergeUD(Matrix<U> const&, Matrix<U> const&);
  template <typename U>
  friend inline Matrix<U> mergeLR(Matrix<U> const&, Matrix<U> const&);
  template <typename U>
  friend inline std::pair<Matrix<U>, Matrix<U>> divideUD(Matrix<U> const&,
                                                         unsigned int const&);
  template <typename U>
  friend inline std::pair<Matrix<U>, Matrix<U>> divideLR(Matrix<U> const&,
                                                         unsigned int const&);
  template <typename U>
  friend class Vector;
  template <typename U>
  friend class Matrix;

 public:
  // Constructors
  Matrix(unsigned int const&, unsigned int const&, T* const&);
  Matrix(unsigned int const&, unsigned int const&);
  Matrix(MaShape const&);
  Matrix();
  Matrix(const Matrix&);
  ~Matrix();

  // Member functions
  inline MaShape const& shape() const { return shape_; }
  inline unsigned int const& size() const { return msSize(shape_); }
  inline T sum() const;
  inline void freedom();
  inline void reshape(unsigned int const&, unsigned int const&);
  inline void reshape(MaShape const&);
  inline void load(unsigned int const&, unsigned int const&, T* const&);
  inline void load(MaShape const&, T* const&);
  inline Matrix transpose() const;
  inline T* begin() { return data_; }
  inline T* end() { return data_ + msSize(shape_); }

  // Operator overloads
  inline T& operator[](MaShape const&) const;
  template <typename U>
  inline operator Matrix<U>() {
    LOG("C:cast operator in Matrix");
    if constexpr (std::is_same_v<T, U>) return *this;
    Matrix<U> result(shape_);
    for (unsigned int i = 0; i < msSize(shape_); i++)
      result.data_[i] = static_cast<U>(data_[i]);
    return result;
  }
  inline Matrix& operator=(const Matrix&);
  inline Matrix& operator+=(const Matrix&);
  inline Matrix& operator-=(const Matrix&);
  inline Matrix& operator*=(const Matrix&);
  inline Matrix& operator/=(const Matrix&);

  inline Matrix operator+(const Matrix&) const;
  inline Matrix operator-(const Matrix&) const;
  inline Matrix operator*(const Matrix&) const;
  inline Matrix operator/(const Matrix&) const;

  inline Matrix<bool> operator==(const Matrix&) const;
  inline Matrix<bool> operator!=(const Matrix&) const;
  inline Matrix<bool> operator<(const Matrix&) const;
  inline Matrix<bool> operator<=(const Matrix&) const;
  inline Matrix<bool> operator>(const Matrix&) const;
  inline Matrix<bool> operator>=(const Matrix&) const;

  inline Matrix& operator=(T const&);
  inline Matrix& operator+=(T const&);
  inline Matrix& operator-=(T const&);
  inline Matrix& operator*=(T const&);
  inline Matrix& operator/=(T const&);

  inline Matrix operator+(T const&) const;
  inline Matrix operator-(T const&) const;
  inline Matrix operator*(T const&) const;
  inline Matrix operator/(T const&) const;

  inline Matrix operator-() const;

  inline Matrix<bool> operator==(T const&) const;
  inline Matrix<bool> operator!=(T const&) const;
  inline Matrix<bool> operator<(T const&) const;
  inline Matrix<bool> operator<=(T const&) const;
  inline Matrix<bool> operator>(T const&) const;
  inline Matrix<bool> operator>=(T const&) const;
};

template <typename Data>
inline std::ostream& operator<<(std::ostream&, const Matrix<Data>&);

template <typename T>
inline Matrix<T> mergeUD(Matrix<T> const&, Matrix<T> const&);
template <typename T>
inline Matrix<T> mergeLR(Matrix<T> const&, Matrix<T> const&);
template <typename T>
inline std::pair<Matrix<T>, Matrix<T>> divideUD(Matrix<T> const&,
                                                unsigned int const&);
template <typename T>
inline std::pair<Matrix<T>, Matrix<T>> divideLR(Matrix<T> const&,
                                                unsigned int const&);
}  // namespace linalg

namespace linalg {

template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat) {
  LOG("C:print matrix");
  unsigned int digits = 0;
  os << mat.shape_;
  if constexpr (std::is_same_v<T, float> || std::is_same_v<T, double>) {
    for (unsigned int i = 0; i < msSize(mat.shape_); i++) {
      digits = std::max(digits, basic_math::intDigits(mat.data_[i]));
    }
    digits += 2;
    digits += basic_math::ACCURACY;
    os << std::setprecision(basic_math::ACCURACY) << std::fixed << std::showpos
       << std::internal << std::setfill(' ') << std::showpoint << "[\n";
  } else if constexpr (std::is_same_v<T, bool>) {
    digits = 1;
    os << "[\n";
  } else {
    for (unsigned int i = 0; i < msSize(mat.shape_); i++) {
      digits = std::max(digits, basic_math::intDigits(mat.data_[i]));
    }
    digits += 1;
    os << std::showpos << std::internal << std::setfill(' ') << "[\n";
  }
  for (unsigned int i = 0, j = 1; i < msSize(mat.shape_); i++) {
    if (j == mat.shape_.cols) {
      os << std::setw(digits) << mat.data_[i] << '\n';
      j = 1;
    } else {
      os << std::setw(digits) << mat.data_[i] << ",";
      j++;
    }
  }
  os << "]\n";
  return os;
}
/**
 * @brief data constructor
 * @param iRows the rows
 * @param iCols the cols
 * @param data the init datas
 */
template <typename T>
Matrix<T>::Matrix(unsigned int const& iRows, unsigned int const& iCols,
                  T* const& data) {
  LOG("C:init constructor ptr=%p,shape(%d,%d)", static_cast<void*>(data), iRows,
      iCols);
  shape_.rows = iRows;
  shape_.cols = iCols;
  if (!msLegal(shape_)) {
    shape_.cols = shape_.rows = 1;
    LOG("E:the illegal shape has fixed to (1,1)");
  }
  this->data_ = new T[msSize(shape_)];
  if (data == nullptr) {
    for (unsigned int i = 0; i < msSize(shape_); i++)
      data_[i] = static_cast<T>(0);
    LOG("E:null pointer can't be init data,all thing in matrix will be 0");
  } else {
    std::copy(data, data + msSize(shape_), data_);
  }
  if (!memory_maintainer::MemoryManager::signUp<linalg::Matrix<T>>(
          msSize(shape_) * sizeof(T), this)) {
    LOG("B:MemoryManager return fail signUp of %p", static_cast<void*>(this));
  }
  return;
}
/**
 * @brief size constructor
 * @param iRows the rows
 * @param iCols the cols
 */
template <typename T>
Matrix<T>::Matrix(unsigned int const& iRows, unsigned int const& iCols) {
  LOG("C:init constructor shape(%d,%d)", iRows, iCols);
  shape_.rows = iRows;
  shape_.cols = iCols;
  if (!msLegal(shape_)) {
    shape_.cols = shape_.rows = 1;
    LOG("E:the illegal shape has fixed to (1,1)");
  }
  this->data_ = new T[msSize(shape_)];
  for (unsigned int i = 0; i < msSize(shape_); i++)
    data_[i] = static_cast<T>(0);
  if (!memory_maintainer::MemoryManager::signUp<linalg::Matrix<T>>(
          msSize(shape_) * sizeof(T), this)) {
    LOG("B:MemoryManager return fail signUp of %p", static_cast<void*>(this));
  }
  return;
}
/**
 * @brief shape constructor
 * @param iShape the shape
 */
template <typename T>
Matrix<T>::Matrix(MaShape const& iShape) {
  LOG("C:init constructor shape(%d,%d)", iShape.rows, iShape.cols);
  shape_ = iShape;
  if (!msLegal(shape_)) {
    shape_.cols = shape_.rows = 1;
    LOG("E:the illegal shape has fixed to (1,1)");
  }
  this->data_ = new T[msSize(shape_)];
  for (unsigned int i = 0; i < msSize(shape_); i++)
    data_[i] = static_cast<T>(0);
  if (!memory_maintainer::MemoryManager::signUp<linalg::Matrix<T>>(
          msSize(shape_) * sizeof(T), this)) {
    LOG("B:MemoryManager return fail signUp of %p", static_cast<void*>(this));
  }
  return;
}
/**
 * @brief default constructor
 */
template <typename T>
Matrix<T>::Matrix() {
  LOG("C:default constructor");
  shape_.rows = shape_.cols = 1;
  this->data_ = new T[1];
  data_[0] = static_cast<T>(0);
  if (!memory_maintainer::MemoryManager::signUp<linalg::Matrix<T>>(
          1 * sizeof(T), this)) {
    LOG("B:MemoryManager return fail signUp of %p", static_cast<void*>(this));
  }
  return;
}
/**
 * @brief copy constructor
 * @param other
 */
template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) : shape_(other.shape_) {
  LOG("C:copy constructor");
  this->data_ = new T[msSize(shape_)];
  std::copy(other.data_, other.data_ + msSize(shape_), data_);
  if (!memory_maintainer::MemoryManager::signUp<linalg::Matrix<T>>(
          msSize(shape_) * sizeof(T), this)) {
    LOG("B:MemoryManager return fail signUp of %p", static_cast<void*>(this));
  }
  return;
}

template <typename T>
Matrix<T>::~Matrix() {
  LOG("C:destructor");
  if (!memory_maintainer::MemoryManager::release<linalg::Matrix<T>>(this)) {
    LOG("B:MemoryManager return fail release of %p", static_cast<void*>(this));
  }
  delete[] data_;
}
/**
 * @brief freedom
 */
template <typename T>
void Matrix<T>::freedom() {
  LOG("C:freedom");
  delete[] data_;
  shape_.rows = shape_.cols = 1;
  this->data_ = new T[1];
  data_[0] = static_cast<T>(0);
  if (!memory_maintainer::MemoryManager::modify<linalg::Matrix<T>>(
          1 * sizeof(T), this)) {
    LOG("B:MemoryManager return fail modify of %p", static_cast<void*>(this));
  }
  return;
}

template <typename T>
T& Matrix<T>::operator[](MaShape const& iIndex) const {
  if (msLegal(iIndex) && iIndex < shape_) {
    return data_[iIndex.rows * shape_.cols + iIndex.cols];
  }
  LOG("E:the index is illegal");
  return data_[0];
}
/**
 * @brief sum
 * @return the sum,if the type is bool,return true or false
 */
template <typename T>
T Matrix<T>::sum() const {
  LOG("C:sum");
  T sum = 0;
  if (std::is_same_v<T, bool>) {
    for (unsigned int i = 0; i < msSize(shape_); i++) sum += data_[i] ? 1 : -1;
    return sum > 0 ? true : false;
  }

  for (unsigned int i = 0; i < msSize(shape_); i++) sum += data_[i];
  return sum;
}
/**
 * @brief reshape
 * @param iRows the new rows
 * @param iCols the new cols
 */
template <typename T>
void Matrix<T>::reshape(unsigned int const& iRows, unsigned int const& iCols) {
  LOG("C:resize shape(%d,%d)", iRows, iCols);
  MaShape iShape = {iRows, iCols};
  if (iShape == shape_) return;
  if (!msLegal(iShape)) {
    LOG("B:the illegal shape");
    return;
  }
  T* newData = new T[msSize(iShape)];
  for (unsigned int i = 0; i < iShape.rows; i++) {
    for (unsigned int j = 0; j < iShape.cols; j++) {
      if (i < shape_.rows && j < shape_.cols) {
        newData[i * iShape.cols + j] = data_[i * shape_.cols + j];
      } else {
        newData[i * iShape.cols + j] = static_cast<T>(0);
      }
    }
  }

  delete[] data_;
  if (!memory_maintainer::MemoryManager::modify<linalg::Matrix<T>>(
          msSize(iShape) * sizeof(T), this)) {
    LOG("B:MemoryManager return fail modify of %p", static_cast<void*>(this));
  }
  data_ = newData;
  shape_ = iShape;
  return;
}
/**
 * @brief reshape
 * @param iShape the new shape
 */
template <typename T>
void Matrix<T>::reshape(MaShape const& iShape) {
  LOG("C:resize shape(%d,%d)", iShape.rows, iShape.cols);
  if (iShape == shape_) return;
  if (!msLegal(iShape)) {
    LOG("B:the illegal shape");
    return;
  }
  T* newData = new T[msSize(iShape)];
  for (unsigned int i = 0; i < iShape.rows; i++) {
    for (unsigned int j = 0; j < iShape.cols; j++) {
      if (i < shape_.rows && j < shape_.cols) {
        newData[i * iShape.cols + j] = data_[i * shape_.cols + j];
      } else {
        newData[i * iShape.cols + j] = static_cast<T>(0);
      }
    }
  }

  delete[] data_;
  if (!memory_maintainer::MemoryManager::modify<linalg::Matrix<T>>(
          msSize(iShape) * sizeof(T), this)) {
    LOG("B:MemoryManager return fail modify of %p", static_cast<void*>(this));
  }
  data_ = newData;
  shape_ = iShape;
  return;
}
/**
 * @brief load
 * @param iRows the rows
 * @param iCols the cols
 * @param data the new datas
 */
template <typename T>
void Matrix<T>::load(unsigned int const& iRows, unsigned int const& iCols,
                     T* const& data) {
  MaShape iShape = {iRows, iCols};
  LOG("C:load shape(%d,%d) data=%p", iShape.rows, iShape.cols,
      static_cast<void*>(data));
  if (data == nullptr) {
    LOG("B:reading for null pointer");
    return;
  }
  if (!msLegal(iShape)) {
    LOG("B:the illegal shape");
    return;
  }
  T* newData = new T[msSize(iShape)];
  std::copy(data, data + msSize(iShape), newData);
  if (!memory_maintainer::MemoryManager::modify<linalg::Matrix<T>>(
          msSize(iShape) * sizeof(T), this)) {
    LOG("B:MemoryManager return fail modify of %p", static_cast<void*>(this));
  }
  delete[] data_;
  data_ = newData;
  shape_ = iShape;
  return;
}
/**
 * @brief load
 * @param iShape the shape
 * @param data the new datas
 */
template <typename T>
void Matrix<T>::load(MaShape const& iShape, T* const& data) {
  LOG("C:load shape(%d,%d) data=%p", iShape.rows, iShape.cols,
      static_cast<void*>(data));
  if (data == nullptr) {
    LOG("B:reading for null pointer");
    return;
  }
  if (!msLegal(iShape)) {
    LOG("B:the illegal shape");
    return;
  }
  T* newData = new T[msSize(iShape)];
  std::copy(data, data + msSize(iShape), newData);
  if (!memory_maintainer::MemoryManager::modify<linalg::Matrix<T>>(
          msSize(iShape) * sizeof(T), this)) {
    LOG("B:MemoryManager return fail modify of %p", static_cast<void*>(this));
  }
  delete[] data_;
  data_ = newData;
  shape_ = iShape;
  return;
}
/**
 * @brief transpose
 * @return the transpose matrix
 */
template <typename T>
Matrix<T> Matrix<T>::transpose() const {
  LOG("C:transpose");
  Matrix<T> transposed(shape_.cols, shape_.rows);
  for (unsigned int i = 0; i < shape_.rows; i++) {
    for (unsigned int j = 0; j < shape_.cols; j++) {
      transposed.data_[j * shape_.rows + i] = data_[i * shape_.cols + j];
    }
  }
  return transposed;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T> const& other) {
  if (this == &other) return *this;
  delete[] data_;
  data_ = new T[msSize(other.shape_)];
  std::copy(other.data_, other.data_ + msSize(other.shape_), data_);
  shape_ = other.shape_;
  if (!memory_maintainer::MemoryManager::modify<linalg::Matrix<T>>(
          msSize(shape_) * sizeof(T), this)) {
    LOG("B:MemoryManager return fail modify of %p", static_cast<void*>(this));
  }
  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(T const& value) {
  for (unsigned int i = 0; i < msSize(shape_); i++) data_[i] = value;
  return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T> const& other) const {
  if (shape_ != other.shape_) {
    LOG("E:matrix shape not same:(%d,%d) + (%d,%d)", shape_.rows, shape_.cols,
        other.shape_.rows, other.shape_.cols);
    return *this;
  }
  Matrix<T> ret(shape_);
  for (unsigned int i = 0; i < msSize(shape_); i++)
    __ADD(data_[i], other.data_[i], ret.data_[i], T);
  return ret;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(T const& value) const {
  Matrix<T> ret(shape_);
  for (unsigned int i = 0; i < msSize(shape_); i++)
    __ADD(data_[i], value, ret.data_[i], T);
  return ret;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T> const& other) const {
  if (shape_ != other.shape_) {
    LOG("E:matrix shape not same:(%d,%d) - (%d,%d)", shape_.rows, shape_.cols,
        other.shape_.rows, other.shape_.cols);
    return *this;
  }
  Matrix<T> ret(shape_);
  for (unsigned int i = 0; i < msSize(shape_); i++)
    __MNS(data_[i], other.data_[i], ret.data_[i], T);
  return ret;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(T const& value) const {
  Matrix<T> ret(shape_);
  for (unsigned int i = 0; i < msSize(shape_); i++)
    __MNS(data_[i], value, ret.data_[i], T);
  return ret;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> const& other) const {
  if (shape_ != other.shape_) {
    LOG("E:matrix shape not same:(%d,%d) * (%d,%d)", shape_.rows, shape_.cols,
        other.shape_.rows, other.shape_.cols);
    return *this;
  }
  Matrix<T> ret(shape_);
  for (unsigned int i = 0; i < msSize(shape_); i++)
    __MUL(data_[i], other.data_[i], ret.data_[i], T);
  return ret;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(T const& value) const {
  Matrix<T> ret(shape_);
  for (unsigned int i = 0; i < msSize(shape_); i++)
    __MUL(data_[i], value, ret.data_[i], T);
  return ret;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(Matrix<T> const& other) const {
  if (shape_ != other.shape_) {
    LOG("E:matrix shape not same:(%d,%d) / (%d,%d)", shape_.rows, shape_.cols,
        other.shape_.rows, other.shape_.cols);
    return *this;
  }
  Matrix<T> ret(shape_);
  for (unsigned int i = 0; i < msSize(shape_); i++)
    __DIV(data_[i], other.data_[i], ret.data_[i], T);
  return ret;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(T const& value) const {
  Matrix<T> ret(shape_);
  for (unsigned int i = 0; i < msSize(shape_); i++)
    __DIV(data_[i], value, ret.data_[i], T);
  return ret;
}

template <typename T>
Matrix<bool> Matrix<T>::operator==(Matrix<T> const& other) const {
  if (shape_ != other.shape_) {
    LOG("E:matrix shape not same:(%d,%d) == (%d,%d)", shape_.rows, shape_.cols,
        other.shape_.rows, other.shape_.cols);
    Matrix<bool> ret(shape_);
    ret = false;
    return ret;
  }
  Matrix<bool> ret(shape_);
  for (unsigned int i = 0; i < msSize(shape_); i++)
    ret.data_[i] = data_[i] == other.data_[i];
  return ret;
}

template <typename T>
Matrix<bool> Matrix<T>::operator==(T const& value) const {
  Matrix<bool> ret(shape_);
  for (unsigned int i = 0; i < msSize(shape_); i++)
    ret.data_[i] = data_[i] == value;
  return ret;
}

template <typename T>
Matrix<bool> Matrix<T>::operator!=(Matrix<T> const& other) const {
  if (shape_ != other.shape_) {
    LOG("E:matrix shape not same:(%d,%d) != (%d,%d)", shape_.rows, shape_.cols,
        other.shape_.rows, other.shape_.cols);
    Matrix<bool> ret(shape_);
    ret = false;
    return ret;
  }
  Matrix<bool> ret(shape_);
  for (unsigned int i = 0; i < msSize(shape_); i++)
    ret.data_[i] = data_[i] != other.data_[i];
  return ret;
}

template <typename T>
Matrix<bool> Matrix<T>::operator!=(T const& value) const {
  Matrix<bool> ret(shape_);
  for (unsigned int i = 0; i < msSize(shape_); i++)
    ret.data_[i] = data_[i] != value;
  return ret;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(Matrix<T> const& other) {
  if (shape_ != other.shape_) {
    LOG("E:matrix shape not same:(%d,%d) += (%d,%d)", shape_.rows, shape_.cols,
        other.shape_.rows, other.shape_.cols);
    return *this;
  }
  for (unsigned int i = 0; i < msSize(shape_); i++)
    __ADD(data_[i], other.data_[i], data_[i], T);
  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(T const& value) {
  for (unsigned int i = 0; i < msSize(shape_); i++)
    __ADD(data_[i], value, data_[i], T);
  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(Matrix<T> const& other) {
  if (shape_ != other.shape_) {
    LOG("E:matrix shape not same:(%d,%d) -= (%d,%d)", shape_.rows, shape_.cols,
        other.shape_.rows, other.shape_.cols);
    return *this;
  }
  for (unsigned int i = 0; i < msSize(shape_); i++)
    __MNS(data_[i], other.data_[i], data_[i], T);
  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(T const& value) {
  for (unsigned int i = 0; i < msSize(shape_); i++)
    __MNS(data_[i], value, data_[i], T);
  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(Matrix<T> const& other) {
  if (shape_ != other.shape_) {
    LOG("E:matrix shape not same:(%d,%d) *= (%d,%d)", shape_.rows, shape_.cols,
        other.shape_.rows, other.shape_.cols);
    return *this;
  }
  for (unsigned int i = 0; i < msSize(shape_); i++)
    __MUL(data_[i], other.data_[i], data_[i], T);
  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(T const& value) {
  for (unsigned int i = 0; i < msSize(shape_); i++)
    __MUL(data_[i], value, data_[i], T);
  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator/=(Matrix<T> const& other) {
  if (shape_ != other.shape_) {
    LOG("E:matrix shape not same:(%d,%d) /= (%d,%d)", shape_.rows, shape_.cols,
        other.shape_.rows, other.shape_.cols);
    return *this;
  }
  for (unsigned int i = 0; i < msSize(shape_); i++)
    __DIV(data_[i], other.data_[i], data_[i], T);
  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator/=(T const& value) {
  for (unsigned int i = 0; i < msSize(shape_); i++)
    __DIV(data_[i], value, data_[i], T);
  return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator-() const {
  Matrix<T> ret(shape_);
  for (unsigned int i = 0; i < msSize(shape_); i++) ret.data_[i] = -data_[i];
  return ret;
}

template <typename T>
Matrix<bool> Matrix<T>::operator<(Matrix<T> const& other) const {
  if (shape_ != other.shape_) {
    LOG("E:matrix shape not same:(%d,%d) < (%d,%d)", shape_.rows, shape_.cols,
        other.shape_.rows, other.shape_.cols);
    Matrix<bool> ret(shape_);
    ret = false;
    return ret;
  }
  Matrix<bool> ret(shape_);
  for (unsigned int i = 0; i < msSize(shape_); i++)
    ret.data_[i] = data_[i] < other.data_[i];
  return ret;
}

template <typename T>
Matrix<bool> Matrix<T>::operator<=(Matrix<T> const& other) const {
  if (shape_ != other.shape_) {
    LOG("E:matrix shape not same:(%d,%d) <= (%d,%d)", shape_.rows, shape_.cols,
        other.shape_.rows, other.shape_.cols);
    Matrix<bool> ret(shape_);
    ret = false;
    return ret;
  }
  Matrix<bool> ret(shape_);
  for (unsigned int i = 0; i < msSize(shape_); i++)
    ret.data_[i] = data_[i] <= other.data_[i];
  return ret;
}

template <typename T>
Matrix<bool> Matrix<T>::operator>(Matrix<T> const& other) const {
  if (shape_ != other.shape_) {
    LOG("E:matrix shape not same:(%d,%d) > (%d,%d)", shape_.rows, shape_.cols,
        other.shape_.rows, other.shape_.cols);
    Matrix<bool> ret(shape_);
    ret = false;
    return ret;
  }
  Matrix<bool> ret(shape_);
  for (unsigned int i = 0; i < msSize(shape_); i++)
    ret.data_[i] = data_[i] > other.data_[i];
  return ret;
}

template <typename T>
Matrix<bool> Matrix<T>::operator>=(Matrix<T> const& other) const {
  if (shape_ != other.shape_) {
    LOG("E:matrix shape not same:(%d,%d) >= (%d,%d)", shape_.rows, shape_.cols,
        other.shape_.rows, other.shape_.cols);
    Matrix<bool> ret(shape_);
    ret = false;
    return ret;
  }
  Matrix<bool> ret(shape_);
  for (unsigned int i = 0; i < msSize(shape_); i++)
    ret.data_[i] = data_[i] >= other.data_[i];
  return ret;
}

template <typename T>
Matrix<bool> Matrix<T>::operator<(T const& value) const {
  Matrix<bool> ret(shape_);
  for (unsigned int i = 0; i < msSize(shape_); i++)
    ret.data_[i] = data_[i] < value;
  return ret;
}

template <typename T>
Matrix<bool> Matrix<T>::operator<=(T const& value) const {
  Matrix<bool> ret(shape_);
  for (unsigned int i = 0; i < msSize(shape_); i++)
    ret.data_[i] = data_[i] <= value;
  return ret;
}

template <typename T>
Matrix<bool> Matrix<T>::operator>(T const& value) const {
  Matrix<bool> ret(shape_);
  for (unsigned int i = 0; i < msSize(shape_); i++)
    ret.data_[i] = data_[i] > value;
  return ret;
}

template <typename T>
Matrix<bool> Matrix<T>::operator>=(T const& value) const {
  Matrix<bool> ret(shape_);
  for (unsigned int i = 0; i < msSize(shape_); i++)
    ret.data_[i] = data_[i] >= value;
  return ret;
}
/**
 * @brief merge two matrix above and below
 * @param upOne the matrix above
 * @param downOne the matrix below
 * @return the merged matrix
 */
template <typename T>
Matrix<T> mergeUD(Matrix<T> const& upOne, Matrix<T> const& downOne) {
  LOG("C:mergeUD");
  if (upOne.shape_.cols != downOne.shape_.cols) {
    LOG("E:merge side not same(%d and %d)", upOne.shape_.cols,
        downOne.shape_.cols);
    Matrix<T> ret(upOne);
    return ret;
  }
  MaShape newShape{upOne.shape_.rows + downOne.shape_.rows, upOne.shape_.cols};
  Matrix<T> ret(newShape);
  std::copy(upOne.data_, upOne.data_ + msSize(upOne.shape_), ret.data_);
  std::copy(downOne.data_, downOne.data_ + msSize(downOne.shape_),
            ret.data_ + msSize(upOne.shape_));
  return ret;
}
/**
 * @brief merge two matrix left and right
 * @param leftOne the matrix left
 * @param rightOne the matrix right
 * @return the merged matrix
 */
template <typename T>
Matrix<T> mergeLR(Matrix<T> const& leftOne, Matrix<T> const& rightOne) {
  LOG("C:mergeLR");
  if (leftOne.shape_.rows != rightOne.shape_.rows) {
    LOG("E:merge side not same(%d and %d)", leftOne.shape_.rows,
        rightOne.shape_.rows);
    Matrix<T> ret(leftOne);
    return ret;
  }
  MaShape newShape{leftOne.shape_.rows,
                   leftOne.shape_.cols + rightOne.shape_.cols};
  Matrix<T> ret(newShape);
  for (unsigned int i = 0; i < leftOne.shape_.rows; i++) {
    for (unsigned int j = 0; j < leftOne.shape_.cols; j++) {
      ret.data_[i * newShape.cols + j] =
          leftOne.data_[i * leftOne.shape_.cols + j];
    }
    for (unsigned int j = 0; j < rightOne.shape_.cols; j++) {
      ret.data_[i * newShape.cols + j + leftOne.shape_.cols] =
          rightOne.data_[i * rightOne.shape_.cols + j];
    }
  }
  return ret;
}
/**
 * @brief divide two matrix above and below
 * @param param the matrix to divide
 * @param size the high of the above one
 * @return the divided matrixs
 */
template <typename T>
std::pair<Matrix<T>, Matrix<T>> divideUD(Matrix<T> const& param,
                                         unsigned int const& size) {
  LOG("C:divideUD");
  Matrix<T> upper, lower;
  if (size >= param.shape_.rows) {
    upper = param;
    lower.reshape(1, 1);
    lower = static_cast<T>(0);
  } else if (size == 0) {
    lower = param;
    upper.reshape(1, 1);
    upper = static_cast<T>(0);
  } else {
    upper.reshape(size, param.shape_.cols);
    lower.reshape(param.shape_.rows - size, param.shape_.cols);
    std::copy(param.data_, param.data_ + msSize(upper.shape_), upper.data_);
    std::copy(param.data_ + msSize(upper.shape_),
              param.data_ + msSize(param.shape_), lower.data_);
  }
  std::pair<Matrix<T>, Matrix<T>> ret = {upper, lower};
  return ret;
}
/**
 * @brief divide two matrix left and right
 * @param param the matrix to divide
 * @param size the width of the left one
 * @return the divided matrixs
 */
template <typename T>
std::pair<Matrix<T>, Matrix<T>> divideLR(Matrix<T> const& param,
                                         unsigned int const& size) {
  LOG("C:divideLR");
  Matrix<T> lefter, righter;
  if (size >= param.shape_.cols) {
    lefter = param;
    righter.reshape(1, 1);
    righter = static_cast<T>(0);
  } else if (size == 0) {
    righter = param;
    lefter.reshape(1, 1);
    lefter = static_cast<T>(0);
  } else {
    lefter.reshape(param.shape_.rows, size);
    righter.reshape(param.shape_.rows, param.shape_.cols - size);
    for (unsigned int i = 0; i < param.shape_.rows; i++) {
      for (unsigned int j = 0; j < lefter.shape_.cols; j++) {
        lefter.data_[i * lefter.shape_.cols + j] =
            param.data_[i * param.shape_.cols + j];
      }
      for (unsigned int j = 0; j < righter.shape_.cols; j++) {
        righter.data_[i * righter.shape_.cols + j] =
            param.data_[i * param.shape_.cols + j + lefter.shape_.cols];
      }
    }
  }
  std::pair<Matrix<T>, Matrix<T>> ret = {lefter, righter};
  return ret;
}
}  // namespace linalg
namespace basic_math {
/**
 * @brief matrix dot
 * @param a the left matrix
 * @param b the right matrix
 * @return the dot matrix
 */
template <typename T>
linalg::Matrix<T> dot(linalg::Matrix<T> const& a, linalg::Matrix<T> const& b) {
  if (a.shape_.cols != b.shape_.rows) {
    LOG("E:matrix shape not same:(%d,%d)dot(%d,%d)", a.shape_.rows,
        a.shape_.cols, b.shape_.rows, b.shape_.cols);
    linalg::Matrix<T> ret(linalg::MaShape{a.shape_.rows, b.shape_.cols});
    return ret;
  }
  linalg::Matrix<T> ret(linalg::MaShape{a.shape_.rows, b.shape_.cols});
  T temp;
  for (unsigned int i = 0; i < a.shape_.rows; i++) {
    for (unsigned int j = 0; j < b.shape_.cols; j++) {
      for (unsigned int k = 0; k < a.shape_.cols; k++) {
        __MUL(a.data_[i * a.shape_.cols + k], b.data_[k * b.shape_.cols + j],
              temp, T);
        __ADD(ret.data_[i * ret.shape_.cols + j], temp,
              ret.data_[i * ret.shape_.cols + j], T);
      }
    }
  }
  return ret;
}
/**
 * @brief random matrix
 * @param iRows the rows
 * @param iCols the cols
 * @param min the min limit
 * @param max the max limit
 * @return the random matrix
 */
template <typename T>
linalg::Matrix<T> random(unsigned int const& iRows, unsigned int const& iCols,
                         T const& min, T const& max) {
  LOG("C:random matrix");
  linalg::Matrix<T> result(iRows, iCols);
  for (unsigned int i = 0; i < iRows * iCols; i++) {
    result.data_[i] = basic_math::random<T>(min, max);
  }
  return result;
}
/**
 * @brief absolute
 * @param param the matrix
 * @return the absolute of the matrix
 */
template <typename T>
linalg::Matrix<T> absolute(linalg::Matrix<T> const& param) {
  LOG("C:absolute matrix");
  linalg::Matrix<T> result(param);
  if constexpr (std::is_same_v<bool, T>) return result;
  for (unsigned int i = 0; i < linalg::msSize(param.shape_); i++)
    if (result.data_[i] < 0) result.data_[i] *= static_cast<T>(-1);
  return result;
}
/**
 * @brief pow
 * @param param the matrix
 * @param value the power
 * @return param^value
 */
template <typename T, typename U>
linalg::Matrix<T> pow(linalg::Matrix<T> const& param, U const& value) {
  LOG("C:pow matrix");
  linalg::Matrix<T> result(param);
  if constexpr (std::is_same_v<bool, T>) return result;
  for (unsigned int i = 0; i < linalg::msSize(param.shape_); i++) {
    result.data_[i] = std::pow(result.data_[i], value);
  }
  return result;
}
/**
 * @brief pow
 * @param value the base
 * @param param the matrix
 * @return value^param
 */
template <typename T, typename U>
linalg::Matrix<U> pow(U const& value, linalg::Matrix<T> const& param) {
  LOG("C:pow matrix");
  linalg::Matrix<U> result(param.shape_);
  if constexpr (std::is_same_v<bool, U>) {
    result = value;
    return result;
  }
  for (unsigned int i = 0; i < linalg::msSize(param.shape_); i++) {
    result.data_[i] = std::pow(value, param.data_[i]);
  }
  return result;
}
}  // namespace basic_math
#endif