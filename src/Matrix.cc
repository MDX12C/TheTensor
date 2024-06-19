#include "../includes/matrix.hpp"
#include "../includes/basic.hpp"
#include <chrono>
#include <thread>
#define MATRIX_C
/*Define Matrix*/
namespace Linalg {
/*Constructor_Datas
Enter 1.Matrix_shape 2.pointer to init datas
use the shape to construct a Matrix and init it with the array
no return */
template <typename Data>
Matrix<Data>::Matrix(MaShape const &beta, Data *const &alpha) {
  if (!check_legal(beta)) {
    this->_shape = MaShape{1, 1};
    this->_size = 1;
#ifdef _THREAD_MODE_
    this->_real_shape.lines = Basic_Math::vec_len;
    this->_real_shape.rows = Basic_Math::vec_len;
    this->_real_size = Basic_Math::vec_len * Basic_Math::vec_len;
    if constexpr (Basic_Math::check_simd<Data>) {
      this->storage_space = (Data *)_mm_malloc(this->_real_size * sizeof(Data),
                                               Basic_Math::align_size);
    } else {
      this->storage_space = (Data *)malloc(this->_real_size * sizeof(Data));
    }
    Memory_Maintain::_mmy_sign(this->_real_size * sizeof(Data), this);
    int run_times = this->_real_size / Basic_Math::align_size;
    std::thread run_arry[run_times];
    for (int i = 0, j = 0; i < this->_real_size;
         i += Basic_Math::align_size, j++) {
      run_arry[j] = std::thread(Basic_Math::tuple_set<Data>,
                                &this->storage_space[i], static_cast<Data>(0));
      run_arry[j].detach();
    }
    if constexpr (Basic_Math::check_simd<Data>) {
      std::this_thread::sleep_for(
          std::chrono::microseconds(Basic_Math::wait_time));
    } else {
      std::this_thread::sleep_for(std::chrono::microseconds(
          Basic_Math::wait_time * Basic_Math::set_delay));
    }
#else
    this->storage_space = new Data[this->_size];
    Memory_Maintain::_mmy_sign(this->_size * sizeof(Data), this);
    for (int i = 0; i < this->_size; i++) {
      this->storage_space[i] = static_cast<Data>(0);
    }
#endif
    return;
  }
  this->_shape = beta;
  this->_size = this->_shape.lines * this->_shape.rows;
#ifdef _THREAD_MODE_
  this->_real_shape.lines = Basic_Math::size_check(this->_shape.lines);
  this->_real_shape.rows = Basic_Math::size_check(this->_shape.rows);
  this->_real_size = this->_real_shape.lines * this->_real_shape.rows;
  if constexpr (Basic_Math::check_simd<Data>) {
    this->storage_space = (Data *)_mm_malloc(this->_real_size * sizeof(Data),
                                             Basic_Math::align_size);
  } else {
    this->storage_space = (Data *)malloc(this->_real_size * sizeof(Data));
  }
  Memory_Maintain::_mmy_sign(this->_real_size * sizeof(Data), this);
  int v_dex = 0, d_dex = 0, t_dex = 0, j;
  const int side = Basic_Math::vec_len -
                   (this->_real_shape.lines - this->_shape.lines),
            wide = this->_real_shape.lines / Basic_Math::align_size - 1;
  std::thread run_array_1[wide * this->_shape.rows];
  std::thread
      run_array_2[(this->_real_shape.rows - this->_shape.rows) * (wide + 1)];
  for (int i = 0; i < this->_shape.rows; i++) {
    for (j = 0; j < wide; j++) {
      run_array_1[t_dex] =
          std::thread(Basic_Math::tuple_load<Data>, &alpha[d_dex],
                      &this->storage_space[v_dex]);
      run_array_1[t_dex].detach();
      t_dex++;
      d_dex += Basic_Math::vec_len;
      v_dex += Basic_Math::vec_len;
    }
    for (j = 0; j < side; j++) {
      this->storage_space[v_dex] = alpha[d_dex];
      d_dex++;
      v_dex++;
    }
    for (; j < Basic_Math::vec_len; j++) {
      this->storage_space[v_dex] = static_cast<Data>(0);
      v_dex++;
    }
  }
  t_dex = 0;
  while (v_dex < this->_real_size) {
    run_array_2[t_dex] =
        std::thread(Basic_Math::tuple_set<Data>, &this->storage_space[v_dex],
                    static_cast<Data>(0));
    run_array_2[t_dex].detach();
    t_dex++;
    v_dex += Basic_Math::vec_len;
  }
  if constexpr (Basic_Math::check_simd<Data>) {
    std::this_thread::sleep_for(
        std::chrono::microseconds(Basic_Math::wait_time));
  } else {
    std::this_thread::sleep_for(std::chrono::microseconds(
        Basic_Math::wait_time * Basic_Math::set_delay));
  }
#else
  this->storage_space = new Data[this->_size];
  Memory_Maintain::_mmy_sign(this->_size, this);
  for (int i = 0; i < this->_size; i++) {
    this->storage_space[i] = alpha[i];
  }
#endif
  return;
}
/*Constructor_Shape
Enter 1.Matrix_shape
use the shape to construct a Matrix and init it with 0
no return */
template <typename Data> Matrix<Data>::Matrix(MaShape const &alpha) {
  if (!check_legal(alpha)) {
    this->_shape.rows = this->_shape.lines = 1;
    this->_size = 1;
  } else {
    this->_shape = alpha;
  }
#ifdef _THREAD_MODE_
  this->_real_shape.lines = Basic_Math::size_check(this->_shape.lines);
  this->_real_shape.rows = Basic_Math::size_check(this->_shape.rows);
  this->_real_size = this->_real_shape.rows * this->_real_shape.lines;
  if constexpr (Basic_Math::check_simd<Data>) {
    this->storage_space = (Data *)_mm_malloc(this->_real_size * sizeof(Data),
                                             Basic_Math::align_size);
  } else {
    this->storage_space = (Data *)malloc(this->_real_size * sizeof(Data));
  }
  Memory_Maintain::_mmy_sign(this->_real_size * sizeof(Data), this);
  const int run_times = this->_real_size / Basic_Math::vec_len;
  std::thread run_array[run_times];
  for (int i = 0, j = 0; i < this->_real_size; i += Basic_Math::vec_len, j++) {
    run_array[j] = std::thread(Basic_Math::tuple_set<Data>,
                               &this->storage_space[i], static_cast<Data>(0));
    run_array[j].detach();
  }
  if constexpr (Basic_Math::check_simd<Data>) {
    std::this_thread::sleep_for(
        std::chrono::microseconds(Basic_Math::wait_time));
  } else {
    std::this_thread::sleep_for(std::chrono::microseconds(
        Basic_Math::wait_time * Basic_Math::set_delay));
  }
#else
  this->storage_space = new Data[this->_size];
  Memory_Maintain::_mmy_sign(this->_size, this);
  for (int i = 0; i < this->_size; i++) {
    this->storage_space[i] = static_cast<Data>(0);
  }
#endif
  return;
}
/*Default constructor
Enter: none
construct an Matrix with 1*1 and init it with 0
no return */
template <typename Data> Matrix<Data>::Matrix() {
  this->_shape = MaShape{1, 1};
  this->_size = 1;
#ifdef _SIMD_MODE_
  this->_real_shape = MaShape{Basic_Math::vec_len, Basic_Math::vec_len};
  this->_real_size = Basic_Math::vec_len * Basic_Math::vec_len;
  if constexpr (Basic_Math::check_simd<Data>) {
    this->storage_space = (Data *)_mm_malloc(this->_real_size * sizeof(Data),
                                             Basic_Math::align_size);
  } else {
    this->storage_space = (Data *)malloc(this->_real_size);
  }
  if (!Memory_Maintain::_mmy_sign(this->_real_size, this)) {
    std::cerr << "~!bad sign!~\n";
    exit(1);
  }
  const int alpha = this->_real_size / Basic_Math::vec_len;
  std::thread beta[alpha];
  for (int i = 0, j = 0; i < this->_real_size; i += Basic_Math::vec_len, j++) {
    beta[j] = std::thread(Basic_Math::tuple_set<Data>,
                          &(this->storage_space[i]), static_cast<Data>(0));
    beta[j].detach();
  }
  if constexpr (Basic_Math::check_simd<Data>) {
    std::this_thread::sleep_for(
        std::chrono::microseconds(Basic_Math::wait_time));
  } else {
    std::this_thread::sleep_for(std::chrono::microseconds(
        Basic_Math::wait_time * Basic_Math::set_delay));
  }
#else
  this->storage_space = new Data[this->_size];
  if (!Memory_Maintain::_mmy_sign(this->_size, this)) {
    std::cerr << "~!bad sign!~\n";
    exit(1);
  }
  for (int i = 0; i < this->_size; i++) {
    this->storage_space[i] = static_cast<Data>(0);
  }
#endif
  return;
}
/*Copy constructor
Enter: 1.Matrix
copy the Matrix
no return */
template <typename Data> Matrix<Data>::Matrix(const Matrix &alpha) {
  this->_shape = alpha._shape;
  this->_size = alpha._size;
#ifdef _SIMD_MODE_
  this->_real_size = alpha._real_size;
  this->_real_shape = alpha._real_shape;
  if constexpr (Basic_Math::check_simd<Data>) {
    this->storage_space = (Data *)_mm_malloc(this->_real_size * sizeof(Data),
                                             Basic_Math::align_size);
  } else {
    this->storage_space = (Data *)malloc(this->_real_size * sizeof(Data));
  }
  if (!Memory_Maintain::_mmy_sign(this->_real_size * sizeof(Data), this)) {
    std::cerr << "~!bad sign!~\n";
    exit(1);
  }
  const int beta = this->_real_size / Basic_Math::vec_len;
  std::thread gamma[beta];
  for (int i = 0, j = 0; i < this->_real_size; i += Basic_Math::vec_len, j++) {
    gamma[j] =
        std::thread(Basic_Math::tuple_load<Data>, &(alpha.storage_space[i]),
                    &(this->storage_space[i]));
    gamma[j].detach();
  }
  if constexpr (Basic_Math::check_simd<Data>) {
    std::this_thread::sleep_for(
        std::chrono::microseconds(Basic_Math::wait_time));
  } else {
    std::this_thread::sleep_for(std::chrono::microseconds(
        Basic_Math::wait_time * Basic_Math::set_delay));
  }
#else
  this->storage_space = new Data[this->_size];
  if (!Memory_Maintain::_mmy_sign(this->_size * sizeof(Data), this)) {
    std::cerr << "~!bad sign!~\n";
    exit(1);
  }
  for (int i = 0; i < this->_size; i++) {
    this->storage_space[i] = static_cast<Data>(0);
  }
#endif
  return;
}
/*Destructor
Enter: none
destruct the Matrix
no return */
template <typename Data> Matrix<Data>::~Matrix() {
#ifdef _SIMD_MODE_
  if constexpr (Basic_Math::check_simd<Data>) {
    _mm_free(this->storage_space);
  } else {
    free(this->storage_space);
  }
#else
  delete[] this->storage_space;
#endif
  return;
}
/*Operator []
Enter: 1.coordinate
do nothing
return the data in the coordinate*/
template <typename Data> Data &Matrix<Data>::operator[](MaShape const &alpha) {
#ifdef _SIMD_MODE_
  if ((alpha < this->_shape) && (check_legal(alpha)))
    return this
        ->storage_space[alpha.rows * this->_real_shape.lines + alpha.lines];
#else
  if ((alpha < this->_shape) && (check_legal(alpha)))
    return this->storage_space[alpha.rows * this->_shape.lines + alpha.lines];
#endif
  if constexpr (std::is_same_v<Data, int>) {
    return Basic_Math::int_leak;
  } else if constexpr (std::is_same_v<Data, bool>) {
    return Basic_Math::bool_leak;
  } else {
    return Basic_Math::float_leak;
  }
}
/*Sum
 * Enter: none
 * add the whole Matrix
 * return the sum of Matrix*/
template <typename Data> Data Matrix<Data>::sum() {
#ifdef _SIMD_MODE_
  if constexpr (std::is_same_v<Data, bool>) {
    int gamma = 0, alpha = 0, j = 0;
    const int beta = this->_real_shape.lines - this->_shape.lines;
    for (int i = 0; i < this->_shape.rows; i++) {
      for (j = 0; j < this->_shape.lines; j++, alpha++)
        gamma += this->storage_space[alpha] ? 1 : -1;
      alpha += beta;
    }
    return static_cast<Data>((gamma > 0) ? true : false);
  } else {
    int alpha = 0, j = 0;
    const int beta = this->_real_shape.lines - this->_shape.lines;
    Data gamma = static_cast<Data>(0);
    for (int i = 0; i < this->_shape.rows; i++) {
      for (j = 0; j < this->_shape.lines; j++, alpha++)
        gamma += this->storage_space[alpha];
      alpha += beta;
    }
    return gamma;
  }
#else
  if constexpr (std::is_same_v<Data, bool>) {
    int gamma = 0;
    for (int i = 0; i < this->_real_size; i++) {
      gamma += this->storage_space[i] ? 1 : -1;
    }
    return static_cast<Data>((gamma > 0) ? true : false);
  } else {
    Data gamma = static_cast<Data>(0);
    for (int i = 0; i < this->_real_size; i++) {
      gamma += this->storage_space[i];
    }
    return gamma;
  }
#endif
}
/*Transpose matrix
Enter: none
flip the matrix
return the transpose of matrix*/
template <typename Data> Matrix<Data> Matrix<Data>::T() {
  Matrix<Data> temp(MaShape{this->_shape.lines, this->_shape.rows});
#ifdef _THREAD_MODE_
  const int run_time = this->_real_size / Basic_Math::vec_len;
  MaShape coord;
  std::thread run_arry[run_time];
  int times = 0;
  for (coord.rows = 0; coord.rows < this->_real_shape.rows;
       coord.rows += Basic_Math::vec_len) {
    for (coord.lines = 0; coord.lines < this->_real_shape.lines;
         coord.lines += Basic_Math::vec_len) {
      run_arry[times] =
          std::thread(Basic_Math::tuple_transpose<Data>, this->storage_space,
                      temp.storage_space, this->_real_shape, coord);
      run_arry[times].detach();
      times += 1;
    }
  }
  if constexpr (Basic_Math::check_simd<Data>) {
    std::this_thread::sleep_for(
        std::chrono::microseconds(Basic_Math::wait_time));
  } else {
    std::this_thread::sleep_for(std::chrono::microseconds(
        Basic_Math::wait_time * Basic_Math::set_delay));
  }
#else
  for (int i = 0; i < this->_shape.rows; i++) {
    for (int j = 0; j < this->_shape.lines; j++)
      temp.storage_space[j * temp._shape.lines + i] =
          this->storage_space[i * this->_shape.lines + j];
  }
#endif
  return temp;
}
/*endow_
Enter: 1.coordinate 2.value
endow the value at the coordinate
return if endow is successful*/
template <typename Data>
bool Matrix<Data>::endow_(MaShape const &alpha, Data const &beta) {
  if ((alpha < this->_shape) && (Linalg::check_legal(alpha))) {
#ifdef _THREAD_MODE_
    this->storage_space[this->_real_shape.lines * alpha.rows + alpha.lines] =
        beta;
#else
    this->storage_space[this->_shape.lines * alpha.rows + alpha.lines] = beta;
#endif
    return true;
  }
  return false;
}
/*flat
Enter: none
flat the Matrix into Vector
return the Vector*/
template <typename Data> Vector<Data> Matrix<Data>::flat() {
  Vector<Data> temp(this->_size, this->storage_space);
  return temp;
}
/*stand
Enter: none
stand the Vector into Matrix
return if stand is successful*/
template <typename Data>
bool Matrix<Data>::stand_(Vector<Data> const &alpha, MaShape const &beta) {
  if (alpha._shape != (beta.rows * beta.lines))
    return false;
  if (this->_size)
    delete[] this->storage_space;
  this->_shape = beta;
  this->_size = beta.rows * beta.lines;
  this->storage_space = new Data[this->_size];
  for (int i = 0; i < this->_size; i++)
    this->storage_space[i] = alpha.storage_space[i];
  return true;
}
/*operator=
Enter: 1.Matrix 2.Matrix
copy the second Matrix to the first
return this*/
template <typename Data>
Matrix<Data> &Matrix<Data>::operator=(Matrix const &alpha) {
  this->_shape = alpha._shape;
  this->_size = alpha._size;
  if (storage_space != nullptr)
    delete[] storage_space;
  this->storage_space = new Data[this->_size];
  for (int i = 0; i < this->_size; i++)
    this->storage_space[i] = alpha.storage_space[i];
  return (*this);
}
/*operator=
Enter: 1.Matrix 2.value
let the Matrix fulled with the value
return this*/
template <typename Data>
Matrix<Data> &Matrix<Data>::operator=(Data const &alpha) {
  if (this->storage_space == nullptr)
    this->resize_(MaShape{1, 1});
  for (int i = 0; i < this->_size; i++)
    this->storage_space[i] = alpha;
  return (*this);
}
/*operator+
Enter: 1.Matrix 2.Matrix
add two Matrix
return the result*/
template <typename Data>
Matrix<Data> Matrix<Data>::operator+(Matrix const &alpha) {
  if (!(this->_shape == alpha._shape))
    return *this;
  Matrix<Data> temp(*this);
  for (int i = 0; i < temp._size; i++) {
    temp.storage_space[i] += alpha.storage_space[i];
  }
  return temp;
}
/*operator+
Enter: 1.Matrix 2.value
add the Matrix and the value
return the result*/
template <typename Data>
Matrix<Data> Matrix<Data>::operator+(Data const &alpha) {
  Matrix<Data> temp(*this);
  for (int i = 0; i < temp._size; i++) {
    temp.storage_space[i] += alpha;
  }
  return temp;
}
/*operator-
Enter: 1.Matrix 2.Matrix
the first Matrix minus the second Matrix
return the result*/
template <typename Data>
Matrix<Data> Matrix<Data>::operator-(Matrix const &alpha) {
  if (!(this->_shape == alpha._shape))
    return *this;
  Matrix<Data> temp(*this);
  for (int i = 0; i < temp._size; i++) {
    temp.storage_space[i] -= alpha.storage_space[i];
  }
  return temp;
}
/*operator-
Enter: 1.Matrix 2.value
the Matrix minus the value
return the result*/
template <typename Data>
Matrix<Data> Matrix<Data>::operator-(Data const &alpha) {
  Matrix<Data> temp(*this);
  for (int i = 0; i < temp._size; i++) {
    temp.storage_space[i] -= alpha;
  }
  return temp;
}
/*operator*
Enter: 1.Matrix 2.Matrix
multiply every element in the two Matrix
return the result*/
template <typename Data>
Matrix<Data> Matrix<Data>::operator*(Matrix const &alpha) {
  if (!(this->_shape == alpha._shape))
    return *this;
  Matrix<Data> temp(*this);
  for (int i = 0; i < temp._size; i++) {
    temp.storage_space[i] *= alpha.storage_space[i];
  }
  return temp;
}
/*operator*
Enter: 1.Matrix 2.value
multiply every element and the value
return the result*/
template <typename Data>
Matrix<Data> Matrix<Data>::operator*(Data const &alpha) {
  Matrix<Data> temp(*this);
  for (int i = 0; i < temp._size; i++) {
    temp.storage_space[i] *= alpha;
  }
  return temp;
}
/*operator/
Enter: 1.Matrix 2.Matrix
divide elements in the first Matrix by elements in the second Matrix
return the result*/
template <typename Data>
Matrix<Data> Matrix<Data>::operator/(Matrix const &alpha) {
  if (!(this->_shape == alpha._shape))
    return *this;
  Matrix<Data> temp(*this);
  for (int i = 0; i < temp._size; i++) {
    temp.storage_space[i] /= alpha.storage_space[i];
  }
  return temp;
}
/*operator/
Enter: 1.Matrix 2.value
divide every element in the Matrix by the value
return the result*/
template <typename Data>
Matrix<Data> Matrix<Data>::operator/(Data const &alpha) {
  Matrix<Data> temp(*this);
  for (int i = 0; i < temp._size; i++) {
    temp.storage_space[i] /= alpha;
  }
  return temp;
}
/*operator+=
Enter: 1.Matrix 2.Matrix
add elements in the second Matrix into the first Matrix
return this*/
template <typename Data>
Matrix<Data> &Matrix<Data>::operator+=(Matrix const &alpha) {
  if (!(this->_shape == alpha._shape))
    return (*this);
  for (int i = 0; i < alpha._size; i++) {
    this->storage_space[i] += alpha.storage_space[i];
  }
  return (*this);
}
/*operator+=
Enter: 1.Matrix 2.value
add the value into the Matrix
return this*/
template <typename Data>
Matrix<Data> &Matrix<Data>::operator+=(Data const &alpha) {
  for (int i = 0; i < this->_size; i++) {
    this->storage_space[i] += alpha;
  }
  return (*this);
}
/*operator-=
Enter: 1.Matrix 2.Matrix
subtract elements in the second Matrix from the first Matrix
return this*/
template <typename Data>
Matrix<Data> &Matrix<Data>::operator-=(Matrix const &alpha) {
  if (!(this->_shape == alpha._shape))
    return (*this);
  for (int i = 0; i < this->_size; i++) {
    this->storage_space[i] -= alpha.storage_space[i];
  }
  return (*this);
}
/*operator-=
Enter: 1.Matrix 2.value
subtract every element in the Matrix by the value
return this*/
template <typename Data>
Matrix<Data> &Matrix<Data>::operator-=(Data const &alpha) {
  for (int i = 0; i < this->_size; i++) {
    this->storage_space[i] -= alpha;
  }
  return (*this);
}
/*operator*=
Enter: 1.Matrix 2.Matrix
multiply every in the first Matrix by the second Matrix
return this*/
template <typename Data>
Matrix<Data> &Matrix<Data>::operator*=(Matrix const &alpha) {
  if (!(this->_shape == alpha._shape))
    return (*this);
  for (int i = 0; i < this->_size; i++) {
    this->storage_space[i] *= alpha.storage_space[i];
  }
  return (*this);
}
/*operator*=
Enter: 1.Matrix 2.value
mutiply every element in the Matrix by the value
return this*/
template <typename Data>
Matrix<Data> &Matrix<Data>::operator*=(Data const &alpha) {
  for (int i = 0; i < this->_size; i++) {
    this->storage_space[i] *= alpha;
  }
  return (*this);
}
/*operator/=
Enter: 1.Matrix 2.Matrix
divide every element in the first Matrix by the elements in the second Matrix
return this*/
template <typename Data>
Matrix<Data> &Matrix<Data>::operator/=(Matrix const &alpha) {
  if (!(this->_shape == alpha._shape))
    return (*this);
  for (int i = 0; i < this->_size; i++) {
    this->storage_space[i] /= alpha.storage_space[i];
  }
  return (*this);
}
/*operator/=
Enter: 1.Matrix 2.value
divide every elements in the Matrix by the value
return this*/
template <typename Data>
Matrix<Data> &Matrix<Data>::operator/=(Data const &alpha) {
  for (int i = 0; i < this->_size; i++) {
    this->storage_space[i] /= alpha;
  }
  return (*this);
}
/*resize
Enter: 1.Mashape
resize the Matrix into the shape, and the beyond's elements will be filled with
0 return if resize successfully*/
template <typename Data> bool Matrix<Data>::resize_(MaShape const &alpha) {
  if (this->_shape == alpha)
    return true;
  if (alpha.lines <= 0 || alpha.rows <= 0)
    return false;
  Linalg::MaShape beta;
  Matrix<Data> temp(*this);
  Data value = static_cast<Data>(0);
  delete[] this->storage_space;
  this->_shape = alpha;
  this->_size = this->_shape.rows * this->_shape.lines;
  this->storage_space = new Data[this->_size];
  for (beta.rows = 0; beta.rows < this->_shape.rows; beta.rows++) {
    for (beta.lines = 0; beta.lines < this->_shape.lines; beta.lines++) {
      if (beta < temp._shape) {
        this->storage_space[this->_shape.lines * beta.rows + beta.lines] =
            temp[beta];
      } else {
        this->storage_space[this->_shape.lines * beta.rows + beta.lines] =
            value;
      }
    }
  }
  return true;
}
/*reshape
Enter: 1.MaShape
reshape the Matrix into the shape, and the number of elements must be the same
return if reshape successfully*/
template <typename Data> bool Matrix<Data>::reshape_(MaShape const &alpha) {
  if (this->_shape == alpha)
    return true;
  if (alpha.lines <= 0 || alpha.rows <= 0)
    return false;
  if ((alpha.rows * alpha.lines) != this->_size)
    return false;
  this->_shape.lines = alpha.lines;
  this->_shape.rows = alpha.rows;
  return true;
}
/*freedom
Enter: none
free the Matrix and set the shape to 1,1
no return*/
template <typename Data> void Matrix<Data>::freedom_() {
  delete[] this->storage_space;
  this->_shape.lines = 1;
  this->_shape.rows = 1;
  this->storage_space = new Data[1];
  this->storage_space[0] = static_cast<Data>(0);
  this->_size = 1;
  return;
}

/*dot
Enter: 1.Matrix 2.Matrix
dot the first matrix and the second matrix
return the result*/
template <typename Data>
Matrix<Data> dot(Matrix<Data> const &beta, Matrix<Data> const &alpha) {
  if (beta._shape.lines != alpha._shape.rows)
    return beta;
  int n = beta._shape.lines;
  Matrix<Data> temp(MaShape{beta._shape.rows, alpha._shape.lines});
  for (int i = 0; i < temp._shape.rows; i++) {
    for (int j = 0; j < temp._shape.lines; j++) {
      for (int l = 0; l < n; l++) {
        temp.storage_space[i * temp._shape.lines + j] +=
            beta.storage_space[i * beta._shape.lines + l] *
            alpha.storage_space[l * alpha._shape.lines + j];
      }
    }
  }
  return temp;
}
/*operator<<
Enter: 1.ostream 2.Matrix
print the Matrix
return the ostream*/
template <typename Data>
std::ostream &operator<<(std::ostream &beta, Matrix<Data> const &alpha) {
  int digits = 1;
  for (int gamma = 0; gamma < alpha._size; gamma++) {
    digits =
        std::max(digits, Basic_Math::Int_Digits(alpha.storage_space[gamma]));
  }
  beta << alpha._shape << "size: " << alpha._size << '\n';
  for (int i = 0; i < alpha._shape.rows; i++) {
    for (int j = 0; j < alpha._shape.lines; j++) {
      beta << std::setprecision(Basic_Math::Float16_Accuracy) << std::fixed
           << std::setfill(' ') << std::showpoint << std::showpos
           << std::internal
           << std::setw(Basic_Math::Float16_Accuracy + digits + 2)
           << alpha.storage_space[i * alpha._shape.lines + j];
      if (j != alpha._shape.lines - 1)
        beta << ' ';
    }
    beta << '\n';
  }
  return beta;
}
/*Add Line
Enter: 1.Matrix 2.Vector
add the Vector to the end of the Matrix(Line)
no return*/
template <typename Data>
void AddLine_(Matrix<Data> &alpha, Vector<Data> const &beta) {
  if (alpha._shape.rows != beta._shape)
    return;
  int gamma = alpha._shape.lines;
  alpha.resize_(MaShape{alpha._shape.rows, alpha._shape.lines + 1});
  for (int theta = 0; theta < beta._shape; theta++) {
    alpha.storage_space[alpha._shape.lines * theta + gamma] =
        beta.storage_space[theta];
  }
  return;
}
/*Add Row
Enter: 1.Matrix 2.Vector
add the Vector to the end of the Matrix(Row)
no return*/
template <typename Data>
void AddRow_(Matrix<Data> &alpha, Vector<Data> const &beta) {
  if (alpha._shape.lines != beta._shape)
    return;
  int gamma = alpha._shape.rows;
  alpha.resize_(MaShape{alpha._shape.rows + 1, alpha._shape.lines});
  for (int theta = 0; theta < beta._shape; theta++) {
    alpha.storage_space[alpha._shape.lines * gamma + theta] =
        beta.storage_space[theta];
  }
  return;
}
} // namespace Linalg
namespace Basic_Math {
/*random Matrix
Enter: 1.Matrix shape 2.min vlaue 3.max value
random a matrix
return the matrix*/
template <typename Data>
Linalg::Matrix<Data> random(Linalg::MaShape const &gamma, Data const &alpha,
                            Data const &beta) {
  Linalg::Matrix<Data> temp(gamma);
  Linalg::MaShape omega;
  for (omega.rows = 0; omega.rows < gamma.rows; omega.rows++) {
    for (omega.lines = 0; omega.lines < gamma.lines; omega.lines++) {
      temp.endow_(omega, random(alpha, beta));
    }
  }
  return temp;
}
} // namespace Basic_Math
template class Linalg::Matrix<int>;
template class Linalg::Matrix<bool>;
template class Linalg::Matrix<float>;
template std::ostream &Linalg::operator<<(std::ostream &,
                                          Linalg::Matrix<int> const &);
template std::ostream &Linalg::operator<<(std::ostream &,
                                          Linalg::Matrix<bool> const &);
template std::ostream &Linalg::operator<<(std::ostream &,
                                          Linalg::Matrix<float> const &);
template Linalg::Matrix<int> Linalg::dot(Linalg::Matrix<int> const &,
                                         Linalg::Matrix<int> const &);
template Linalg::Matrix<bool> Linalg::dot(Linalg::Matrix<bool> const &,
                                          Linalg::Matrix<bool> const &);
template Linalg::Matrix<float> Linalg::dot(Linalg::Matrix<float> const &,
                                           Linalg::Matrix<float> const &);
template void Linalg::AddLine_(Linalg::Matrix<int> &,
                               Linalg::Vector<int> const &);
template void Linalg::AddLine_(Linalg::Matrix<bool> &,
                               Linalg::Vector<bool> const &);
template void Linalg::AddLine_(Linalg::Matrix<float> &,
                               Linalg::Vector<float> const &);
template void Linalg::AddRow_(Linalg::Matrix<int> &,
                              Linalg::Vector<int> const &);
template void Linalg::AddRow_(Linalg::Matrix<bool> &,
                              Linalg::Vector<bool> const &);
template void Linalg::AddRow_(Linalg::Matrix<float> &,
                              Linalg::Vector<float> const &);
template Linalg::Matrix<int> Basic_Math::random(Linalg::MaShape const &,
                                                int const &, int const &);
template Linalg::Matrix<bool> Basic_Math::random(Linalg::MaShape const &,
                                                 bool const &, bool const &);
template Linalg::Matrix<float> Basic_Math::random(Linalg::MaShape const &,
                                                  float const &, float const &);
