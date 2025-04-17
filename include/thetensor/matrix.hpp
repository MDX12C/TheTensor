#include "define.hpp"
#ifndef MATRIX_H
#define MATRIX_H 1
#include "basic.hpp"
#include "story.hpp"
namespace lina_lg {
typedef struct ShapeOfMatrix {
  // row: horizontal
  size_t row_;
  // column: vertical
  size_t col_;
  static constexpr size_t LIMIT = 65536;
  inline ShapeOfMatrix& operator=(ShapeOfMatrix const& __other) noexcept {
    row_ = __other.row_;
    col_ = __other.col_;
    return *this;
  }
  inline ShapeOfMatrix& operator+=(ShapeOfMatrix const& __other) noexcept {
    row_ += __other.row_;
    col_ += __other.col_;
    return *this;
  }
  inline ShapeOfMatrix& operator-=(ShapeOfMatrix const& __other) noexcept {
    row_ -= __other.row_;
    col_ -= __other.col_;
    return *this;
  }
  inline bool operator==(ShapeOfMatrix const& __other) const noexcept {
    return (row_ == __other.row_) && (col_ == __other.col_);
  }
  inline bool operator<(ShapeOfMatrix const& __other) const noexcept {
    return (row_ < __other.row_) && (col_ < __other.col_);
  }
  inline bool operator!=(ShapeOfMatrix const& __other) const noexcept {
    return (row_ != __other.row_) || (col_ != __other.col_);
  }
  inline bool operator<=(ShapeOfMatrix const& __other) const noexcept {
    return (row_ <= __other.row_) && (col_ <= __other.col_);
  }
  inline ShapeOfMatrix operator+(ShapeOfMatrix const& __other) const noexcept {
    return ShapeOfMatrix{row_ + __other.row_, col_ + __other.col_};
  }
  inline ShapeOfMatrix operator-(ShapeOfMatrix const& __other) const noexcept {
    return ShapeOfMatrix{row_ - __other.row_, col_ - __other.col_};
  }
} MatrixShape;
using MaShape = MatrixShape;
/**
 * @brief check if the MatrixShape is legal
 */
inline bool legalShape(MatrixShape const& __param) noexcept {
  return __param.row_ && __param.col_ && (__param.row_ < MaShape::LIMIT) &&
         (__param.col_ < MaShape::LIMIT);
}
/**
 * @brief the MatrixShape's size
 */
inline size_t sizeofShape(MatrixShape const& __param) noexcept {
  return __param.col_ * __param.row_;
}
/**
 * @brief make Shape
 * @param __row the row
 * @param __col the col
 * @return the shape
 * @throw none
 */
inline MaShape makeShape(size_t const& __row, size_t const& __col) noexcept {
  MatrixShape ans;
  ans.row_ = __row;
  ans.col_ = __col;
  return ans;
}
template <typename T>
class Matrix final : public storage::Story<T> {
  template <typename W>
  friend class Matrix;
  template <typename W>
  friend inline Matrix<W> operator+(W const&, Matrix<W> const&) noexcept;
  template <typename W>
  friend inline Matrix<W> operator-(W const&, Matrix<W> const&) noexcept;
  template <typename W>
  friend inline Matrix<W> operator*(W const&, Matrix<W> const&) noexcept;
  template <typename W>
  friend inline Matrix<W> operator/(W const&, Matrix<W> const&) noexcept;
  template <typename W>
  friend inline Matrix<bool> operator==(W const&, Matrix<W> const&) noexcept;
  template <typename W>
  friend inline Matrix<bool> operator!=(W const&, Matrix<W> const&) noexcept;
  template <typename W>
  friend inline Matrix<bool> operator>=(W const&, Matrix<W> const&) noexcept;
  template <typename W>
  friend inline Matrix<bool> operator<=(W const&, Matrix<W> const&) noexcept;
  template <typename W>
  friend inline Matrix<bool> operator>(W const&, Matrix<W> const&) noexcept;
  template <typename W>
  friend inline Matrix<bool> operator<(W const&, Matrix<W> const&) noexcept;
  template <typename W>
  friend inline Matrix<W> mergeUD(Matrix<W> const&, Matrix<W> const&) noexcept;
  template <typename W>
  friend inline Matrix<W> mergeLR(Matrix<W> const&, Matrix<W> const&) noexcept;
  template <typename W>
  friend inline Matrix<W> scan(Matrix<W> const&, MaShape const&,
                               MaShape const&) noexcept;
  template <typename W>
  friend std::ostream& operator<<(std::ostream& __stream,
                                  Matrix<W> const& __item) noexcept;

 protected:
  MatrixShape shape_;

 public:
  inline virtual bool resize(size_t const& __temp) override {
    throw system_message::Error("unsupport function of Matrix");
    return false;
  }
  inline virtual bool load(size_t const& __size, T* const& __data) override {
    throw system_message::Error("unsupport function of Matrix");
    return false;
  }
  Matrix() noexcept(basic_math::support<T>);
  Matrix(MatrixShape const&) noexcept(basic_math::support<T>);
  Matrix(MatrixShape const&, T* const&) noexcept(basic_math::support<T>);
  Matrix(Matrix const&) noexcept(basic_math::support<T>);
  Matrix(Matrix&&) noexcept(basic_math::support<T>);
  ~Matrix() noexcept;

  inline MatrixShape shape() const noexcept { return this->shape_; }
  inline bool resize(MatrixShape const&) noexcept;
  inline bool reshape(MatrixShape const&) noexcept;
  inline bool load(MatrixShape const&, T* const&) noexcept;
  inline virtual void freedom() noexcept override;
  inline Matrix transpose() const noexcept;
  template <typename U>
  inline operator Matrix<U>() const noexcept(basic_math::support<T>) {
    LOG("C:cast operator of Matrix");
    if constexpr (!basic_math::support<U>) {
      LOG("B:unsupportted type");
      throw system_message::Error("unsupport type of Matrix");
    }
    if constexpr (std::is_same_v<T, U>) return *this;
    Matrix<U> result(this->shape_);
    for (size_t i = 0; i < this->size_; i++)
      result.datas_[i] = static_cast<U>(this->datas_[i]);
    return result;
  }
  inline T& at(MatrixShape const&) const noexcept;
  inline T& at(size_t const&, size_t const&) const noexcept;
  inline T& operator[](MatrixShape const&) const noexcept;
  inline Matrix& operator=(Matrix const&) noexcept;
  inline Matrix& operator+=(Matrix const&) noexcept;
  inline Matrix& operator-=(Matrix const&) noexcept;
  inline Matrix& operator*=(Matrix const&) noexcept;
  inline Matrix& operator/=(Matrix const&) noexcept;
  inline Matrix& operator=(Matrix&&) noexcept;
  inline Matrix& operator=(T const&) noexcept;
  inline Matrix& operator+=(T const&) noexcept;
  inline Matrix& operator-=(T const&) noexcept;
  inline Matrix& operator*=(T const&) noexcept;
  inline Matrix& operator/=(T const&) noexcept;

  inline Matrix operator!() const;

  inline Matrix operator+(Matrix const&) noexcept;
  inline Matrix operator-(Matrix const&) noexcept;
  inline Matrix operator*(Matrix const&) noexcept;
  inline Matrix operator/(Matrix const&) noexcept;
  inline Matrix operator+(T const&) const noexcept;
  inline Matrix operator-(T const&) const noexcept;
  inline Matrix operator*(T const&) const noexcept;
  inline Matrix operator/(T const&) const noexcept;

  inline Matrix<bool> operator==(Matrix const&) noexcept;
  inline Matrix<bool> operator!=(Matrix const&) noexcept;
  inline Matrix<bool> operator>=(Matrix const&) noexcept;
  inline Matrix<bool> operator<=(Matrix const&) noexcept;
  inline Matrix<bool> operator>(Matrix const&) noexcept;
  inline Matrix<bool> operator<(Matrix const&) noexcept;
  inline Matrix<bool> operator==(T const&) const noexcept;
  inline Matrix<bool> operator!=(T const&) const noexcept;
  inline Matrix<bool> operator>=(T const&) const noexcept;
  inline Matrix<bool> operator<=(T const&) const noexcept;
  inline Matrix<bool> operator>(T const&) const noexcept;
  inline Matrix<bool> operator<(T const&) const noexcept;
};
typedef Matrix<FloatType> MatrixF;
std::ostream& operator<<(std::ostream& __os, MaShape const& __shape) noexcept {
  LOG("C:operator<< to MatrixShape");
  __os << std::noshowpos << '(' << __shape.row_ << ',' << __shape.col_ << ')';
  return __os;
}
template <typename T>
std::ostream& operator<<(std::ostream& __os, Matrix<T> const& __it) noexcept {
  LOG("C:ostream to Matrix");
  size_t digits = 0;
  __os << __it.shape_;
  if constexpr (std::is_same_v<T, bool>) {
    digits = 1;
  } else if constexpr (std::is_floating_point_v<T>) {
    for (size_t i = 0; i < __it.size_; i++)
      digits = std::max(digits, basic_math::intDigits(__it.datas_[i]));
    digits += 2;
    digits += basic_math::PRINT_ACCURACY;
    __os << std::setprecision(basic_math::PRINT_ACCURACY) << std::fixed
         << std::showpos << std::internal << std::setfill(' ')
         << std::showpoint;
  } else {
    for (size_t i = 0; i < __it.size_; i++)
      digits = std::max(digits, basic_math::intDigits(__it.datas_[i]));
    digits += 1;
    __os << std::showpos << std::internal << std::setfill(' ');
  }
  size_t i = 0;
  for (size_t r = 0; r < __it.shape_.row_; r++) {
    __os << "\n[" << std::setw(digits) << __it.datas_[i];
    i++;
    for (size_t c = 1; c < __it.shape_.col_; c++) {
      __os << ',' << std::setw(digits) << __it.datas_[i];
      i++;
    }
    __os << ']';
  }
  return __os;
}
template <typename T>
inline Matrix<T> operator+(T const&, Matrix<T> const&) noexcept;
template <typename T>
inline Matrix<T> operator-(T const&, Matrix<T> const&) noexcept;
template <typename T>
inline Matrix<T> operator*(T const&, Matrix<T> const&) noexcept;
template <typename T>
inline Matrix<T> operator/(T const&, Matrix<T> const&) noexcept;
template <typename T>
inline Matrix<bool> operator==(T const&, Matrix<T> const&) noexcept;
template <typename T>
inline Matrix<bool> operator!=(T const&, Matrix<T> const&) noexcept;
template <typename T>
inline Matrix<bool> operator>=(T const&, Matrix<T> const&) noexcept;
template <typename T>
inline Matrix<bool> operator<=(T const&, Matrix<T> const&) noexcept;
template <typename T>
inline Matrix<bool> operator>(T const&, Matrix<T> const&) noexcept;
template <typename T>
inline Matrix<bool> operator<(T const&, Matrix<T> const&) noexcept;
template <typename T>
inline Matrix<T> mergeUD(Matrix<T> const&, Matrix<T> const&) noexcept;
template <typename T>
inline Matrix<T> mergeLR(Matrix<T> const&, Matrix<T> const&) noexcept;
template <typename T>
inline Matrix<T> scan(Matrix<T> const&, MaShape const&,
                      MaShape const&) noexcept;
}  // namespace lina_lg
namespace basic_math {
template <typename T>
inline lina_lg::Matrix<T> uniformRand(lina_lg::MaShape const&, T const&,
                                      T const&) noexcept;
template <typename T>
inline lina_lg::Matrix<T> absolute(lina_lg::Matrix<T>&) noexcept;
template <typename T>
inline lina_lg::Matrix<T> pow(lina_lg::Matrix<T>&, T const&) noexcept;
template <typename T>
inline lina_lg::Matrix<T> pow(T const&, lina_lg::Matrix<T>&) noexcept;
template <typename T>
inline lina_lg::Matrix<T> pow(lina_lg::Matrix<T>&,
                              lina_lg::Matrix<T>&) noexcept;
template <typename T>
inline lina_lg::Matrix<T> log(lina_lg::Matrix<T>&) noexcept;
template <typename T>
inline lina_lg::Matrix<T> dot(lina_lg::Matrix<T>&,
                              lina_lg::Matrix<T>&) noexcept;
}  // namespace basic_math
namespace lina_lg {
/**
 * @brief defult constructor
 */
template <typename T>
Matrix<T>::Matrix() noexcept(basic_math::support<T>) : storage::Story<T>() {
  LOG("C:defult constructor of Matrix");
  this->shape_.col_ = this->shape_.row_ = 1;
  return;
}
/**
 * @brief size constructor
 * @param __shape the init shape
 */
template <typename T>
Matrix<T>::Matrix(MatrixShape const& __shape) noexcept(basic_math::support<T>)
    : storage::Story<T>(sizeofShape(__shape)) {
  LOG("C:size constructor of Matrix");
  if (legalShape(__shape))
    this->shape_ = __shape;
  else
    this->shape_.col_ = this->shape_.row_ = 1;
  return;
}
/**
 * @brief init constructor
 * @param __shape the init shape
 * @param __init init datas
 */
template <typename T>
Matrix<T>::Matrix(MatrixShape const& __shape,
                  T* const& __init) noexcept(basic_math::support<T>)
    : storage::Story<T>(sizeofShape(__shape), __init) {
  LOG("C:init constructor of Matrix");
  if (legalShape(__shape))
    this->shape_ = __shape;
  else
    this->shape_.col_ = this->shape_.row_ = 1;
  return;
}
/**
 * @brief copy constructor
 * @param __other the other one
 */
template <typename T>
Matrix<T>::Matrix(Matrix const& __other) noexcept(basic_math::support<T>)
    : storage::Story<T>(__other.size_, __other.datas_) {
  LOG("C:copy constructor of Matrix");
  this->shape_ = __other.shape_;
  return;
}
/**
 * @brief move constructor
 * @param __other the other one
 * @warning the other will be unusable after the constructor
 */
template <typename T>
Matrix<T>::Matrix(Matrix&& __other) noexcept(basic_math::support<T>)
    : storage::Story<T>() {
  LOG("C:move constructor of Matrix");
  delete[] this->datas_;
  this->datas_ = __other.datas_;
  this->size_ = __other.size_;
  this->shape_ = __other.shape_;
  __other.datas_ = nullptr;
  return;
}
/**
 * @brief destructor
 */
template <typename T>
Matrix<T>::~Matrix() noexcept {
  LOG("C:destructor of Matrix");
  return;
}
template <typename T>
inline T& Matrix<T>::operator[](MatrixShape const& __shape) const noexcept {
  LOG("C:operator[] of Matrix");
  return this->datas_[__shape.row_ * this->shape_.col_ + __shape.col_];
}
/**
 * @brief resize the Matrix, the overflow zone will be cut and the new zone will
 * be filled with defult
 * @param __shape the new shape
 * @return true is success, false otherwise
 */
template <typename T>
inline bool Matrix<T>::resize(MatrixShape const& __shape) noexcept {
  LOG("C:resize of Matrix");
  if (!legalShape(__shape)) {
    LOG("E:error shape");
    return false;
  }
  if (this->shape_ == __shape) return true;
  T* temp = new T[sizeofShape(__shape)];
  MatrixShape shape;
  for (shape.row_ = 0; shape.row_ < __shape.row_; shape.row_++) {
    for (shape.col_ = 0; shape.col_ < __shape.col_; shape.col_++) {
      temp[shape.row_ * __shape.col_ + shape.col_] =
          shape < this->shape_
              ? this->datas_[shape.row_ * this->shape_.col_ + shape.col_]
              : static_cast<T>(0);
    }
  }
  delete[] this->datas_;
  this->datas_ = temp;
  this->size_ = sizeofShape(__shape);
  this->shape_ = __shape;
  return true;
}
/**
 * @brief reshape the Matrix, only shape
 * @param __shape the new shape, the size of new shape need be equal to the old
 * one
 * @return true is success, false otherwise
 */
template <typename T>
inline bool Matrix<T>::reshape(MatrixShape const& __shape) noexcept {
  LOG("C:reshape of Matrix");
  if (!legalShape(__shape)) {
    LOG("E:error shape");
    return false;
  }
  if (this->shape_ == __shape) return true;
  if (this->size_ == sizeofShape(__shape))
    this->shape_ = __shape;
  else
    return false;
  return true;
}
/**
 * @brief load the memory
 * @param __shape the new shape
 * @param __init the new datas
 * @return true is success, false otherwise
 */
template <typename T>
inline bool Matrix<T>::load(MatrixShape const& __shape,
                            T* const& __init) noexcept {
  LOG("C:load of Matrix");
  if (!legalShape(__shape)) {
    LOG("E:error shape");
    return false;
  }
  if (this->size_ != sizeofShape(__shape)) {
    delete[] this->datas_;
    this->size_ = sizeofShape(__shape);
    this->datas_ = new T[this->size_];
  }
  this->shape_ = __shape;
  std::copy(__init, __init + this->size_, this->datas_);
  return true;
}
/**
 * @brief freedom, freedom the memory
 */
template <typename T>
inline void Matrix<T>::freedom() noexcept {
  LOG("C:freedom of Matrix");
  delete[] this->datas_;
  this->datas_ = new T[1];
  this->datas_[0] = static_cast<T>(0);
  this->size_ = this->shape_.col_ = this->shape_.row_ = 1;
  return;
};
/**
 * @brief transpose matrix
 */
template <typename T>
inline Matrix<T> Matrix<T>::transpose() const noexcept {
  LOG("C:transpose of Matrix");
  Matrix<T> result(makeShape(this->shape_.col_, this->shape_.row_));
  MatrixShape shape;
  for (shape.row_ = 0; shape.row_ < this->shape_.col_; shape.row_++) {
    for (shape.col_ = 0; shape.col_ < this->shape_.row_; shape.col_++) {
      result.datas_[shape.row_ * this->shape_.row_ + shape.col_] =
          this->datas_[shape.col_ * this->shape_.col_ + shape.row_];
    }
  }
  return result;
}
/**
 * @brief at, the function does as you think
 * @param __where where
 */
template <typename T>
T& Matrix<T>::at(MatrixShape const& __where) const noexcept {
  LOG("C:at of Matrix");
  if (__where < this->shape_) {
    return this->datas_[this->shape_.col_ * __where.row_ + __where.col_];
  }
  LOG("E:memory overflow");
  return this->datas_[0];
}
/**
 * @brief at, the function does as you think
 * @param __row the row
 * @param __col the column
 */
template <typename T>
T& Matrix<T>::at(size_t const& __row, size_t const& __col) const noexcept {
  LOG("C:at of Matrix");
  if ((this->shape_.row_ > __row) && (this->shape_.col_ > __col)) {
    return this->datas_[this->shape_.col_ * __row + __col];
  }
  LOG("E:memory overflow");
  return this->datas_[0];
}
template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T> const& __other) noexcept {
  LOG("C:operator= of Matrix");
  if (this->size_ != __other.size_) {
    delete[] this->datas_;
    this->size_ = __other.size_;
    this->datas_ = new T[this->size_];
  }
  this->shape_ = __other.shape_;
  for (size_t i = 0; i < this->size_; i++) this->datas_[i] = __other.datas_[i];
  return *this;
}
template <typename T>
inline Matrix<T>& Matrix<T>::operator=(Matrix<T>&& __other) noexcept {
  LOG("C:move operator= of Matrix");
  if (this == &__other) {
    LOG("B:inlegal way to move between one Matrix");
    return *this;
  }
  if (this->datas_) delete[] this->datas_;
  this->datas_ = __other.datas_;
  this->shape_ = __other.shape_;
  this->size_ = __other.size_;
  __other.datas_ = nullptr;
  return *this;
}
template <typename T>
Matrix<T>& Matrix<T>::operator=(T const& __other) noexcept {
  LOG("C:operator= of Matrix");
  for (size_t i = 0; i < this->size_; i++) this->datas_[i] = __other;
  return *this;
}
template <typename T>
Matrix<T>& Matrix<T>::operator+=(Matrix<T> const& __other) noexcept {
  LOG("C:operator+= of Matrix");
  if (this->shape_ != __other.shape_) {
    LOG("E:encounter size will be suited");
    this->resize(__other.shape_);
  }
  for (size_t i = 0; i < this->size_; i++)
    EADD(this->datas_[i], __other.datas_[i], T);
  return *this;
}
template <typename T>
Matrix<T>& Matrix<T>::operator+=(T const& __other) noexcept {
  LOG("C:operator+= of Vetor");
  for (size_t i = 0; i < this->size_; i++) EADD(this->datas_[i], __other, T);
  return *this;
}
template <typename T>
Matrix<T>& Matrix<T>::operator-=(Matrix<T> const& __other) noexcept {
  LOG("C:operator-= of Matrix");
  if (this->shape_ != __other.shape_) {
    LOG("E:encounter size will be suited");
    this->resize(__other.shape_);
  }
  for (size_t i = 0; i < this->size_; i++)
    EMNS(this->datas_[i], __other.datas_[i], T);
  return *this;
}
template <typename T>
Matrix<T>& Matrix<T>::operator-=(T const& __other) noexcept {
  LOG("C:operator-= of Vetor");
  for (size_t i = 0; i < this->size_; i++) EMNS(this->datas_[i], __other, T);
  return *this;
}
template <typename T>
Matrix<T>& Matrix<T>::operator*=(Matrix<T> const& __other) noexcept {
  LOG("C:operator*= of Matrix");
  if (this->shape_ != __other.shape_) {
    LOG("E:encounter size will be suited");
    this->resize(__other.shape_);
  }
  for (size_t i = 0; i < this->size_; i++)
    EMUL(this->datas_[i], __other.datas_[i], T);
  return *this;
}
template <typename T>
Matrix<T>& Matrix<T>::operator*=(T const& __other) noexcept {
  LOG("C:operator*= of Vetor");
  for (size_t i = 0; i < this->size_; i++) EMUL(this->datas_[i], __other, T);
  return *this;
}
template <typename T>
Matrix<T>& Matrix<T>::operator/=(Matrix<T> const& __other) noexcept {
  LOG("C:operator/= of Matrix");
  if (this->shape_ != __other.shape_) {
    LOG("E:encounter size will be suited");
    this->resize(__other.shape_);
  }
  for (size_t i = 0; i < this->size_; i++)
    EDIV(this->datas_[i], __other.datas_[i], T);
  return *this;
}
template <typename T>
Matrix<T>& Matrix<T>::operator/=(T const& __other) noexcept {
  LOG("C:operator/= of Vetor");
  for (size_t i = 0; i < this->size_; i++) EDIV(this->datas_[i], __other, T);
  return *this;
}
template <typename T>
Matrix<T> Matrix<T>::operator!() const {
  LOG("C:operator! of Matrix");
  if constexpr (std::is_unsigned_v<T>) {
    LOG("B:the type can't be signed");
    throw system_message::Error("the type can't be signed");
  }
  Matrix<T> result(this->shape_);
  for (size_t i = 0; i < this->size_; i++)
    if constexpr (std::is_same_v<T, bool>) {
      result.datas_[i] = !this->datas_[i];
    } else {
      result.datas_[i] = -this->datas_[i];
    }
  return result;
}
template <typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T> const& __other) noexcept {
  LOG("C:operator+ of Matrix");
  if (this->shape_ != __other.shape_) {
    LOG("E:encounter size will be suited");
    this->resize(__other.shape_);
  }
  Matrix<T> result(*this);
  for (size_t i = 0; i < this->size_; i++)
    EADD(result.datas_[i], __other.datas_[i], T);
  return result;
}
template <typename T>
Matrix<T> Matrix<T>::operator+(T const& __other) const noexcept {
  LOG("C:operator+ of Matrix");
  Matrix<T> result(*this);
  for (size_t i = 0; i < this->size_; i++) EADD(result.datas_[i], __other, T);
  return result;
}
template <typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T> const& __other) noexcept {
  LOG("C:operator- of Matrix");
  if (this->shape_ != __other.shape_) {
    LOG("E:encounter size will be suited");
    this->resize(__other.shape_);
  }
  Matrix<T> result(*this);
  for (size_t i = 0; i < this->size_; i++)
    EMNS(result.datas_[i], __other.datas_[i], T);
  return result;
}
template <typename T>
Matrix<T> Matrix<T>::operator-(T const& __other) const noexcept {
  LOG("C:operator- of Matrix");
  Matrix<T> result(*this);
  for (size_t i = 0; i < this->size_; i++) EMNS(result.datas_[i], __other, T);
  return result;
}
template <typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> const& __other) noexcept {
  LOG("C:operator* of Matrix");
  if (this->shape_ != __other.shape_) {
    LOG("E:encounter size will be suited");
    this->resize(__other.shape_);
  }
  Matrix<T> result(*this);
  for (size_t i = 0; i < this->size_; i++)
    EMUL(result.datas_[i], __other.datas_[i], T);
  return result;
}
template <typename T>
Matrix<T> Matrix<T>::operator*(T const& __other) const noexcept {
  LOG("C:operator* of Matrix");
  Matrix<T> result(*this);
  for (size_t i = 0; i < this->size_; i++) EMUL(result.datas_[i], __other, T);
  return result;
}
template <typename T>
Matrix<T> Matrix<T>::operator/(Matrix<T> const& __other) noexcept {
  LOG("C:operator/ of Matrix");
  if (this->shape_ != __other.shape_) {
    LOG("E:encounter size will be suited");
    this->resize(__other.shape_);
  }
  Matrix<T> result(*this);
  for (size_t i = 0; i < this->size_; i++)
    EDIV(result.datas_[i], __other.datas_[i], T);
  return result;
}
template <typename T>
Matrix<T> Matrix<T>::operator/(T const& __other) const noexcept {
  LOG("C:operator/ of Matrix");
  Matrix<T> result(*this);
  for (size_t i = 0; i < this->size_; i++) EDIV(result.datas_[i], __other, T);
  return result;
}
template <typename T>
Matrix<bool> Matrix<T>::operator==(Matrix<T> const& __other) noexcept {
  LOG("C:operator== of Matrix");
  if (this->shape_ != __other.shape_) {
    LOG("E:encounter size will be suited");
    this->resize(__other.shape_);
  }
  Matrix<bool> result(this->shape_);
  for (size_t i = 0; i < this->size_; i++)
    result.datas_[i] = this->datas_[i] == __other.datas_[i];
  return result;
}
template <typename T>
Matrix<bool> Matrix<T>::operator==(T const& __other) const noexcept {
  LOG("C:operator== of Matrix");
  Matrix<bool> result(this->shape_);
  for (size_t i = 0; i < this->size_; i++)
    result.datas_[i] = this->datas_[i] == __other;
  return result;
}
template <typename T>
Matrix<bool> Matrix<T>::operator!=(Matrix<T> const& __other) noexcept {
  LOG("C:operator!= of Matrix");
  if (this->shape_ != __other.shape_) {
    LOG("E:encounter size will be suited");
    this->resize(__other.shape_);
  }
  Matrix<bool> result(this->shape_);
  for (size_t i = 0; i < this->size_; i++)
    result.datas_[i] = this->datas_[i] != __other.datas_[i];
  return result;
}
template <typename T>
Matrix<bool> Matrix<T>::operator!=(T const& __other) const noexcept {
  LOG("C:operator!= of Matrix");
  Matrix<bool> result(this->shape_);
  for (size_t i = 0; i < this->size_; i++)
    result.datas_[i] = this->datas_[i] != __other;
  return result;
}
template <typename T>
Matrix<bool> Matrix<T>::operator>=(Matrix<T> const& __other) noexcept {
  LOG("C:operator>= of Matrix");
  if (this->shape_ != __other.shape_) {
    LOG("E:encounter size will be suited");
    this->resize(__other.shape_);
  }
  Matrix<bool> result(this->shape_);
  for (size_t i = 0; i < this->size_; i++)
    result.datas_[i] = this->datas_[i] >= __other.datas_[i];
  return result;
}
template <typename T>
Matrix<bool> Matrix<T>::operator>=(T const& __other) const noexcept {
  LOG("C:operator>= of Matrix");
  Matrix<bool> result(this->shape_);
  for (size_t i = 0; i < this->size_; i++)
    result.datas_[i] = this->datas_[i] >= __other;
  return result;
}
template <typename T>
Matrix<bool> Matrix<T>::operator<=(Matrix<T> const& __other) noexcept {
  LOG("C:operator<= of Matrix");
  if (this->shape_ != __other.shape_) {
    LOG("E:encounter size will be suited");
    this->resize(__other.shape_);
  }
  Matrix<bool> result(this->shape_);
  for (size_t i = 0; i < this->size_; i++)
    result.datas_[i] = this->datas_[i] <= __other.datas_[i];
  return result;
}
template <typename T>
Matrix<bool> Matrix<T>::operator<=(T const& __other) const noexcept {
  LOG("C:operator<= of Matrix");
  Matrix<bool> result(this->shape_);
  for (size_t i = 0; i < this->size_; i++)
    result.datas_[i] = this->datas_[i] <= __other;
  return result;
}
template <typename T>
Matrix<bool> Matrix<T>::operator>(Matrix<T> const& __other) noexcept {
  LOG("C:operator> of Matrix");
  if (this->shape_ != __other.shape_) {
    LOG("E:encounter size will be suited");
    this->resize(__other.shape_);
  }
  Matrix<bool> result(this->shape_);
  for (size_t i = 0; i < this->size_; i++)
    result.datas_[i] = this->datas_[i] > __other.datas_[i];
  return result;
}
template <typename T>
Matrix<bool> Matrix<T>::operator>(T const& __other) const noexcept {
  LOG("C:operator> of Matrix");
  Matrix<bool> result(this->shape_);
  for (size_t i = 0; i < this->size_; i++)
    result.datas_[i] = this->datas_[i] > __other;
  return result;
}
template <typename T>
Matrix<bool> Matrix<T>::operator<(Matrix<T> const& __other) noexcept {
  LOG("C:operator< of Matrix");
  if (this->shape_ != __other.shape_) {
    LOG("E:encounter size will be suited");
    this->resize(__other.shape_);
  }
  Matrix<bool> result(this->shape_);
  for (size_t i = 0; i < this->size_; i++)
    result.datas_[i] = this->datas_[i] < __other.datas_[i];
  return result;
}
template <typename T>
Matrix<bool> Matrix<T>::operator<(T const& __other) const noexcept {
  LOG("C:operator< of Matrix");
  Matrix<bool> result(this->shape_);
  for (size_t i = 0; i < this->size_; i++)
    result.datas_[i] = this->datas_[i] < __other;
  return result;
}
template <typename T>
inline Matrix<T> operator+(T const& __first,
                           Matrix<T> const& __second) noexcept {
  LOG("C:operator+ to Matrix");
  Matrix<T> result(__second.shape_);
  for (size_t i = 0; i < __second.size_; i++)
    ADD(__first, __second.datas_[i], result.datas_[i], T);
  return result;
}
template <typename T>
inline Matrix<T> operator-(T const& __first,
                           Matrix<T> const& __second) noexcept {
  LOG("C:operator- to Matrix");
  Matrix<T> result(__second.shape_);
  for (size_t i = 0; i < __second.size_; i++)
    MNS(__first, __second.datas_[i], result.datas_[i], T);
  return result;
}
template <typename T>
inline Matrix<T> operator*(T const& __first,
                           Matrix<T> const& __second) noexcept {
  LOG("C:operator* to Matrix");
  Matrix<T> result(__second.shape_);
  for (size_t i = 0; i < __second.size_; i++)
    MUL(__first, __second.datas_[i], result.datas_[i], T);
  return result;
}
template <typename T>
inline Matrix<T> operator/(T const& __first,
                           Matrix<T> const& __second) noexcept {
  LOG("C:operator/ to Matrix");
  Matrix<T> result(__second.shape_);
  for (size_t i = 0; i < __second.size_; i++)
    DIV(__first, __second.datas_[i], result.datas_[i], T);
  return result;
}
template <typename T>
inline Matrix<bool> operator==(T const& __first,
                               Matrix<T> const& __second) noexcept {
  LOG("C:operator== to Matrix");
  Matrix<bool> result(__second.shape_);
  for (size_t i = 0; i < __second.size_; i++)
    result.datas_[i] = __first == __second.datas_[i];
  return result;
}
template <typename T>
inline Matrix<bool> operator!=(T const& __first,
                               Matrix<T> const& __second) noexcept {
  LOG("C:operator!= to Matrix");
  Matrix<bool> result(__second.shape_);
  for (size_t i = 0; i < __second.size_; i++)
    result.datas_[i] = __first != __second.datas_[i];
  return result;
}
template <typename T>
inline Matrix<bool> operator>=(T const& __first,
                               Matrix<T> const& __second) noexcept {
  LOG("C:operator>= to Matrix");
  Matrix<bool> result(__second.shape_);
  for (size_t i = 0; i < __second.size_; i++)
    result.datas_[i] = __first >= __second.datas_[i];
  return result;
}
template <typename T>
inline Matrix<bool> operator<=(T const& __first,
                               Matrix<T> const& __second) noexcept {
  LOG("C:operator<= to Matrix");
  Matrix<bool> result(__second.shape_);
  for (size_t i = 0; i < __second.size_; i++)
    result.datas_[i] = __first <= __second.datas_[i];
  return result;
}
template <typename T>
inline Matrix<bool> operator>(T const& __first,
                              Matrix<T> const& __second) noexcept {
  LOG("C:operator> to Matrix");
  Matrix<bool> result(__second.shape_);
  for (size_t i = 0; i < __second.size_; i++)
    result.datas_[i] = __first > __second.datas_[i];
  return result;
}
template <typename T>
inline Matrix<bool> operator<(T const& __first,
                              Matrix<T> const& __second) noexcept {
  LOG("C:operator< to Matrix");
  Matrix<bool> result(__second.shape_);
  for (size_t i = 0; i < __second.size_; i++)
    result.datas_[i] = __first < __second.datas_[i];
  return result;
}
/**
 * @brief merge up and down
 * @param __up the up one
 * @param __down the down one
 * @return the merge one
 * @throw none
 */
template <typename T>
inline Matrix<T> mergeUD(Matrix<T> const& __up,
                         Matrix<T> const& __down) noexcept {
  LOG("C:mergeUD to Matrix");
  if (__up.shape_.col_ != __down.shape_.col_) {
    LOG("E:unmatch size");
    return Matrix<T>();
  }
  if ((__up.shape_.row_ + __down.shape_.row_) >= MaShape::LIMIT) {
    LOG("E:too big shape may cause unpredictable result");
    return Matrix<T>();
  }
  Matrix<T> ans({__up.shape_.row_ + __down.shape_.row_, __up.shape_.col_});
  std::copy(__up.datas_, __up.datas_ + __up.size_, ans.datas_);
  std::copy(__down.datas_, __down.datas_ + __down.size_,
            ans.datas_ + __up.size_);
  return ans;
}
/**
 * @brief merge left and right
 * @param __left the left one
 * @param __right the right one
 * @return the merge one
 * @throw none
 */
template <typename T>
inline Matrix<T> mergeLR(Matrix<T> const& __left,
                         Matrix<T> const& __right) noexcept {
  LOG("C:mergeLR to Matrix");
  if (__left.shape_.row_ != __right.shape_.row_) {
    LOG("E:unmatch size");
    return Matrix<T>();
  }
  if ((__left.shape_.col_ + __right.shape_.col_) >= MaShape::LIMIT) {
    LOG("E:too big shape may cause unpredictable result");
    return Matrix<T>();
  }
  Matrix<T> ans({__left.shape_.row_, __left.shape_.col_ + __right.shape_.col_});
  T *left = __left.datas_, *right = __right.datas_, *answer = ans.datas_;
  for (size_t i = 0; i < __left.shape_.row_; i++) {
    answer = std::copy(left, left + __left.shape_.col_, answer);
    left += __left.shape_.col_;
    answer = std::copy(right, right + __right.shape_.col_, answer);
    right += __right.shape_.col_;
  }
  return ans;
}
/**
 * @brief scan matrix from a matrix
 * @param __matrix the base matrix
 * @param __low the lower bond
 * @param __up the upper bond
 * @return the sub matrix
 * @throw none
 */
template <typename T>
inline Matrix<T> scan(Matrix<T> const& __matrix, MaShape const& __low,
                      MaShape const& __up) noexcept {
  LOG("C:scan to Matrix");
  if (!((__low < __up) && (__up <= __matrix.shape_))) {
    LOG("E:bad param");
    return Matrix<T>();
  }
  MaShape ansShape;
  ansShape = __up - __low;
  Matrix<T> ans(ansShape);
  T *alpha = __matrix.datas_ + __matrix.shape_.col_ * __low.row_ + __low.col_,
    *beta = ans.datas_;
  for (size_t i = 0; i < ansShape.row_; i++) {
    beta = std::copy(alpha, alpha + ansShape.col_, beta);
    alpha += __matrix.shape_.col_;
  }
  return ans;
}
}  // namespace lina_lg
namespace basic_math {
/**
 * @brief uniformRand
 * @param __shape the shape of Matrix
 * @param __min the min
 * @param __max the max
 * @return the answer
 * @throw none
 */
template <typename T>
inline lina_lg::Matrix<T> uniformRand(lina_lg::MaShape const& __shape,
                                      T const& __min, T const& __max) noexcept {
  LOG("C:uniformRand to Matrix");
  lina_lg::Matrix<T> result(__shape);
  for (auto& i : result) i = uniformRand(__min, __max);
  return result;
}
/**
 * @brief absolute
 * @param __matrix the Matrix
 * @return the answer
 * @throw none
 */
template <typename T>
inline lina_lg::Matrix<T> absolute(lina_lg::Matrix<T>& __matrix) noexcept {
  LOG("C:absolute to Matrix");
  lina_lg::Matrix<T> result(__matrix);
  for (auto& i : result) i = std::abs(i);
  return result;
}
/**
 * @brief pow
 * @param __matrix the base
 * @param __exponent the exponent
 * @return the answer
 * @throw none
 */
template <typename T>
inline lina_lg::Matrix<T> pow(lina_lg::Matrix<T>& __matrix,
                              T const& __exponent) noexcept {
  LOG("C:absolute to Matrix");
  lina_lg::Matrix<T> result(__matrix);
  for (auto& i : result)
    if (i > static_cast<T>(0))
      i = std::pow(i, __exponent);
    else {
      LOG("E:invalid basement");
      i = static_cast<T>(0);
    }
  return result;
}
/**
 * @brief pow
 * @param __base the base
 * @param __matrix the exponent
 * @return the answer
 * @throw none
 */
template <typename T>
inline lina_lg::Matrix<T> pow(T const& __base,
                              lina_lg::Matrix<T>& __matrix) noexcept {
  LOG("C:absolute to Matrix");
  lina_lg::Matrix<T> result(__matrix);
  if (__base > static_cast<T>(0))
    for (auto& i : result) i = std::pow(__base, i);
  else {
    LOG("E:invalid basement");
    result = static_cast<T>(0);
  }
  return result;
}
/**
 * @brief log
 * @param __matrix the Matrix
 * @return the answer
 * @throw none
 */
template <typename T>
inline lina_lg::Matrix<T> log(lina_lg::Matrix<T>& __matrix) noexcept {
  LOG("C:absolute to Matrix");
  lina_lg::Matrix<T> result(__matrix);
  for (auto& i : result)
    if (i > static_cast<T>(0))
      i = std::log(i);
    else {
      LOG("E:invalid log");
      i = static_cast<T>(0);
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
inline lina_lg::Matrix<T> pow(lina_lg::Matrix<T>& __base,
                              lina_lg::Matrix<T>& __exponent) noexcept {
  LOG("C:pow to Matrix");
  if (__base.shape() != __exponent.shape()) {
    LOG("E:unmatch shape");
    return lina_lg::Matrix<T>(__base);
  }
  lina_lg::Matrix<T> result(__base);
  auto i = result.begin(), w = __exponent.begin();
  while (i != result.end()) {
    if ((*i) > static_cast<T>(0))
      (*i) = std::pow(*i, *w);
    else {
      LOG("E:invalid basement");
      (*i) = static_cast<T>(0);
    }
    i++;
    w++;
  }
  return result;
}
/**
 * @brief dot
 * @param __alpha the first
 * @param __beta the second one
 * @return the answer itself
 * @throw none
 */
template <typename T>
inline lina_lg::Matrix<T> dot(lina_lg::Matrix<T>& __alpha,
                              lina_lg::Matrix<T>& __beta) noexcept {
  LOG("C:dot to Matrix");
  if (__alpha.shape().col_ != __beta.shape().row_) {
    LOG("E:bad size for dot");
    return lina_lg::Matrix<T>(__alpha);
  }
  lina_lg::MaShape shape, where;
  size_t step = __alpha.shape().col_;
  shape = {__alpha.shape().row_, __beta.shape().col_};
  lina_lg::Matrix<T> result(shape);
  for (where.row_ = 0; where.row_ < shape.row_; where.row_++) {
    for (where.col_ = 0; where.col_ < shape.col_; where.col_++) {
      result[where] = static_cast<T>(0);
      for (size_t k = 0; k < step; k++) {
        result[where] += __alpha[lina_lg::MaShape{where.row_, k}] *
                         __beta[lina_lg::MaShape{k, where.col_}];
      }
    }
  }
  return result;
}
}  // namespace basic_math
#endif