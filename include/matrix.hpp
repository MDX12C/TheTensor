#include "define.hpp"
#ifndef MATRIX_H
#define MATRIX_H 1
#include "basic.hpp"
#include "story.hpp"
namespace lina_lg {
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

 public:
  typedef struct MatrixShape {
    // row: horizontal
    size_t row_;
    // column: vertical
    size_t col_;
    inline MatrixShape& operator=(MatrixShape const& __other) const noexcept {
      row_ = __other.row_;
      col_ = __other.col_;
      return *this;
    }
    inline bool operator==(MatrixShape const& __other) const noexcept {
      return (row_ == __other.row_) && (col_ == __other.col_);
    }
    inline bool operator<(MatrixShape const& __other) const noexcept {
      return (row_ < __other.row_) && (col_ < __other.col_);
    }
    inline bool operator!=(MatrixShape const& __other) const noexcept {
      return (row_ != __other.row_) || (col_ != __other.col_);
    }
  } MaShape;
  /**
   * @brief check if the MatrixShape is legal
   */
  static inline bool legalShape(MatrixShape const& __param) noexcept {
    return __param.row_ && __param.col_;
  }
  /**
   * @brief the MatrixShape's size
   */
  static inline size_t sizeofShape(MatrixShape const& __param) noexcept {
    return __param.col_ * __param.row_;
  }

 protected:
  MaShape shape_;

 public:
  inline virtual bool resize(size_t const& __temp) override {
    LOG("B:unsupport function");
    throw system_message::Error("unsupport function of Matrix");
    return false;
  }
  inline virtual bool load(size_t const& __size, T* const __data) override {
    LOG("B:unsupport function");
    throw system_message::Error("unsupport function of Matrix");
    return false;
  }
  inline virtual T& at(size_t const& __temp) const override {
    LOG("B:unsupport function");
    throw system_message::Error("unsupport function of Matrix");
    return false;
  }
  inline virtual T& operator[](size_t const& __temp) const override {
    LOG("B:unsupport function");
    throw system_message::Error("unsupport function of Matrix");
    return false;
  }
  Matrix() noexcept(basic_math::support<T>);
  Matrix(MaShape const&) noexcept(basic_math::support<T>);
  Matrix(MaShape const&, T* const&) noexcept(basic_math::support<T>);
  Matrix(Matrix const&) noexcept(basic_math::support<T>);
  ~Matrix() noexcept;

  inline MaShape shape() const noexcept { return this->shape_; }
  inline bool resize(MaShape const&) noexcept;
  inline bool reshape(MaShape const&) noexcept;
  inline bool load(MaShape const&, T* const&) noexcept;
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
  inline T& at(MaShape const&) const noexcept;
  inline T& operator[](MaShape const&) const noexcept;
  inline Matrix& operator=(Matrix const&) noexcept;
  inline Matrix& operator+=(Matrix const&) noexcept;
  inline Matrix& operator-=(Matrix const&) noexcept;
  inline Matrix& operator*=(Matrix const&) noexcept;
  inline Matrix& operator/=(Matrix const&) noexcept;
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
template <typename T>
std::ostream& operator<<(std::ostream& __stream, Matrix<T>& __item) noexcept {
  LOG("C:ostream to Matrix");
  __stream << '(' << __item.shape().row_ << __item.shape().col_ << ")\n";
  auto wide = __item.shape().col_;
  size_t i = 0;
  for (auto w : __item) {
    if (i == 0) {
      __stream << '[';
    }
    __stream << w;
    i++;
    if (i == wide) {
      __stream << "]\n";
      i = 0;
    } else {
      __stream << ',';
    }
  }
  return __stream;
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
}  // namespace lina_lg
namespace basic_math {
template <typename T>
inline lina_lg::Matrix<T>& random(lina_lg::Matrix<T>&, T const&,
                                  T const&) noexcept;
template <typename T>
inline lina_lg::Matrix<T>& absolute(lina_lg::Matrix<T>&) noexcept;
template <typename T>
inline lina_lg::Matrix<T>& pow(lina_lg::Matrix<T>&, T const&) noexcept;
template <typename T>
inline lina_lg::Matrix<T>& pow(T const&, lina_lg::Matrix<T>&) noexcept;
template <typename T>
inline lina_lg::Matrix<T>& log(lina_lg::Matrix<T>&) noexcept;
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
Matrix<T>::Matrix(MaShape const& __shape) noexcept(basic_math::support<T>)
    : storage::Story<T>(Matrix::sizeofShape(__shape)) {
  LOG("C:size constructor of Matrix");
  if (Matrix::legalShape(__shape))
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
Matrix<T>::Matrix(MaShape const& __shape,
                  T* const& __init) noexcept(basic_math::support<T>)
    : storage::Story<T>(Matrix::sizeofShape(__shape), __init) {
  LOG("C:init constructor of Matrix");
  if (Matrix::legalShape(__shape))
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
 * @brief destructor
 */
template <typename T>
Matrix<T>::~Matrix() noexcept {
  LOG("C:destructor of Matrix");
  return;
}
/**
 * @brief resize the Matrix, the overflow zone will be cut and the new zone will
 * be filled with defult
 * @param __shape the new shape
 * @return true is success, false otherwise
 */
template <typename T>
inline bool Matrix<T>::resize(MaShape const& __shape) noexcept {
  LOG("C:resize of Matrix");
  if (!Matrix::legalShape(__shape)) {
    LOG("E:error shape");
    return false;
  }
  if (this->shape_ == __shape) return true;
  T* temp = new T[Matrix::sizeofShape(__shape)];
  MaShape shape;
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
  this->size_ = Matrix::sizeofShape(__shape);
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
inline bool Matrix<T>::reshape(MaShape const& __shape) noexcept {
  LOG("C:reshape of Matrix");
  if (!Matrix::legalShape(__shape)) {
    LOG("E:error shape");
    return false;
  }
  if (this->shape_ == __shape) return true;
  if (this->size_ == Matrix::sizeofShape(__shape))
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
inline bool Matrix<T>::load(MaShape const& __shape, T* const& __init) noexcept {
  LOG("C:load of Matrix");
  if (!Matrix::legalShape(__shape)) {
    LOG("E:error shape");
    return false;
  }
  if (this->size_ != Matrix::sizeofShape(__shape)) {
    delete[] this->datas_;
    this->size_ = Matrix::sizeofShape(__shape);
    this->datas_ = new T[this->size_];
  }
  this->shape_ = __shape;
  std::copy(__init, __init + this->size_; this->datas_);
  return true;
}
/**
 * @brief freedom, freedom the memory
 */
template <typename T>
inline void Matrix<T>::freedom() noexcept override {
  LOG("C:freedom of Matrix");
  delete[] this->datas_;
  this->datas_ = new T[1];
  this->datas_[0] = static_cast<T>(0);
  this->size_ = this->shape_.col = this->shape_.row = 1;
  return;
};
/**
 * @brief transpose matrix
 */
template <typename T>
inline Matrix<T> Matrix<T>::transpose() const noexcept {
  LOG("C:transpose of Matrix");
  Matrix<T> result(MaShape{this->shape_.col, this->shape_.row});
  MaShape shape;
  for (shape.row_ = 0; shape.row_ < this->shape_.col_; shape.row_++) {
    for (shape.col_ = 0; shape.col_ < this->shape_.row_; shape.col_++) {
      result.datas_[shape.row_ * this->shape_.row_ + shape.row_] =
          this->datas_[shape.col_ * this->shape_.col_ + shape.row_];
    }
  }
  return result;
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
  for (size_t i = 0; i < this->size_; i++) this->datas_[i] = __other->datas_[i];
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
  for (size_t i = 0; i < __second.size; i++)
    ADD(__first, __second.datas_[i], result.datas_[i], T);
  return result;
}
template <typename T>
inline Matrix<T> operator-(T const& __first,
                           Matrix<T> const& __second) noexcept {
  LOG("C:operator- to Matrix");
  Matrix<T> result(__second.shape_);
  for (size_t i = 0; i < __second.size; i++)
    MNS(__first, __second.datas_[i], result.datas_[i], T);
  return result;
}
template <typename T>
inline Matrix<T> operator*(T const& __first,
                           Matrix<T> const& __second) noexcept {
  LOG("C:operator* to Matrix");
  Matrix<T> result(__second.shape_);
  for (size_t i = 0; i < __second.size; i++)
    MUL(__first, __second.datas_[i], result.datas_[i], T);
  return result;
}
template <typename T>
inline Matrix<T> operator/(T const& __first,
                           Matrix<T> const& __second) noexcept {
  LOG("C:operator/ to Matrix");
  Matrix<T> result(__second.shape_);
  for (size_t i = 0; i < __second.size; i++)
    DIV(__first, __second.datas_[i], result.datas_[i], T);
  return result;
}
template <typename T>
inline Matrix<bool> operator==(T const& __first,
                               Matrix<T> const& __second) noexcept {
  LOG("C:operator== to Matrix");
  Matrix<bool> result(__second.shape_);
  for (size_t i = 0; i < __second.size; i++)
    result.datas_[i] = __first == __second.datas_[i];
  return result;
}
template <typename T>
inline Matrix<bool> operator!=(T const& __first,
                               Matrix<T> const& __second) noexcept {
  LOG("C:operator!= to Matrix");
  Matrix<bool> result(__second.shape_);
  for (size_t i = 0; i < __second.size; i++)
    result.datas_[i] = __first != __second.datas_[i];
  return result;
}
template <typename T>
inline Matrix<bool> operator>=(T const& __first,
                               Matrix<T> const& __second) noexcept {
  LOG("C:operator>= to Matrix");
  Matrix<bool> result(__second.shape_);
  for (size_t i = 0; i < __second.size; i++)
    result.datas_[i] = __first >= __second.datas_[i];
  return result;
}
template <typename T>
inline Matrix<bool> operator<=(T const& __first,
                               Matrix<T> const& __second) noexcept {
  LOG("C:operator<= to Matrix");
  Matrix<bool> result(__second.shape_);
  for (size_t i = 0; i < __second.size; i++)
    result.datas_[i] = __first <= __second.datas_[i];
  return result;
}
template <typename T>
inline Matrix<bool> operator>(T const& __first,
                              Matrix<T> const& __second) noexcept {
  LOG("C:operator> to Matrix");
  Matrix<bool> result(__second.shape_);
  for (size_t i = 0; i < __second.size; i++)
    result.datas_[i] = __first > __second.datas_[i];
  return result;
}
template <typename T>
inline Matrix<bool> operator<(T const& __first,
                              Matrix<T> const& __second) noexcept {
  LOG("C:operator< to Matrix");
  Matrix<bool> result(__second.shape_);
  for (size_t i = 0; i < __second.size; i++)
    result.datas_[i] = __first < __second.datas_[i];
  return result;
}
}  // namespace lina_lg
namespace basic_math {
/**
 * @brief random
 * @param __matrix the reference of Matrix
 * @param __min the min
 * @param __max the max
 * @return itself
 * @throw none
 */
template <typename T>
inline lina_lg::Matrix<T>& random(lina_lg::Matrix<T>& __matrix, T const& __min,
                                  T const& __max) noexcept {
  LOG("C:random to Matrix");
  for (auto& i : __matrix) i = random(__min, __max);
  return __matrix;
}
/**
 * @brief absolute
 * @param __matrix the reference of Matrix
 * @return itself
 * @throw none
 */
template <typename T>
inline lina_lg::Matrix<T>& absolute(lina_lg::Matrix<T>& __matrix) noexcept {
  LOG("C:absolute to Matrix");
  for (auto& i : __matrix) i = std::abs(i);
  return __matrix;
}
/**
 * @brief pow
 * @param __matrix the base
 * @param __exponent the exponent
 * @return itself
 * @throw none
 */
template <typename T>
inline lina_lg::Matrix<T>& pow(lina_lg::Matrix<T>& __matrix,
                               T const& __exponent) noexcept {
  LOG("C:absolute to Matrix");
  for (auto& i : __matrix) i = std::pow(i, __exponent);
  return __matrix;
}
/**
 * @brief pow
 * @param __base the base
 * @param __matrix the exponent
 * @return itself
 * @throw none
 */
template <typename T>
inline lina_lg::Matrix<T>& pow(T const& __base,
                               lina_lg::Matrix<T>& __matrix) noexcept {
  LOG("C:absolute to Matrix");
  for (auto& i : __matrix) i = std::pow(__base, i);
  return __matrix;
}
/**
 * @brief log
 * @param __matrix the Matrix
 * @return itself
 * @throw none
 */
template <typename T>
inline lina_lg::Matrix<T>& log(lina_lg::Matrix<T>& __matrix) noexcept {
  LOG("C:absolute to Matrix");
  for (auto& i : __matrix) i = std::log(i);
  return __matrix;
}
}  // namespace basic_math
#endif