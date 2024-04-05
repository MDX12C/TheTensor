﻿#include "../includes/matrix.hpp"
/*Define Matrix*/
namespace Linalg
{
    /*Mashape operator==
    Enter: 1.Mashape 2.Mashape
    compare two mashape
    return true if they are equal */
    bool operator==(MaShape const& alpha, MaShape const& beta)
    {
        return (alpha.rows == beta.rows) && (alpha.lines == beta.lines);
    }
    /*Show Mashape
    Enter: 1.Mashape
    show the mashape's rows and lines
    no return */
    void show_Mashape(MaShape const& alpha) {
        std::cout << "rows: " << alpha.rows << "\nlines: " << alpha.lines << '\n';
        return;
    }
    /*Constructor_Value
    Enter 1.Matrix_shape 2.init data
    use the shape to construct a Matrix full of the init data
    no return */
    template <typename Data>
    Matrix<Data>::Matrix(MaShape const& beta, Data const& alpha)
    {
        this->shape.lines = beta.lines > 0 ? beta.lines : 1;
        this->shape.rows = beta.rows > 0 ? beta.rows : 1;
        this->storage_space = new Data[this->shape.rows * this->shape.lines];
        for (int i = 0; i < this->shape.rows * this->shape.lines; i++)
            this->storage_space[i] = alpha;
        return;
    }
    /*Constructor_Values
    Enter 1.Matrix_shape 2.pointer to init datas
    use the shape to construct a Matrix and init it with the array
    no return */
    template <typename Data>
    Matrix<Data>::Matrix(MaShape const& beta, Data* const& alpha)
    {
        this->shape = beta;
        if (this->shape.rows <= 0 || this->shape.lines <= 0)
            this->shape.lines=this->shape.rows=1;
        this->storage_space = new Data[this->shape.rows * this->shape.lines];
        for (int i = 0; i < this->shape.rows * this->shape.lines; i++)
            this->storage_space[i] = alpha[i];
        return;
    }
    /*Constructor_Shape
    Enter 1.Matrix_shape
    use the shape to construct a Matrix and init it with 0
    no return */
    template <typename Data>
    Matrix<Data>::Matrix(MaShape const& alpha) {
        this->shape.lines = alpha.lines > 0 ? alpha.lines : 1;
        this->shape.rows = alpha.rows > 0 ? alpha.rows : 1;
        this->storage_space = new Data[this->shape.rows * this->shape.lines];
        for (int i = 0; i < this->shape.rows * this->shape.lines; i++)
            this->storage_space[i] = static_cast<Data>(0);
        return;
    }
    /*Default constructor
    Enter: none
    construct an Matrix with 1*1 and init it with 0
    no return */
    template <typename Data>
    Matrix<Data>::Matrix() {
        this->shape.rows = this->shape.lines = 1;
        this->storage_space = new Data[1];
        this->storage_space[0] = static_cast<Data>(0);
        return;
    }
    /*Copy constructor
    Enter: 1.Matrix
    copy the Matrix
    no return */
    template <typename Data>
    Matrix<Data>::Matrix(const Matrix& alpha) {
        this->shape = alpha.shape;
        this->storage_space = new Data[this->shape.rows * this->shape.lines];
        for (int i = 0; i < this->shape.rows * this->shape.lines; i++)
            this->storage_space[i] = alpha.storage_space[i];
        return;
    }
    /*Destructor
    Enter: none
    destruct the Matrix
    no return */
    template <typename Data>
    Matrix<Data>::~Matrix()
    {
        if (this->shape.rows * this->shape.lines)
            delete[] this->storage_space;
        return;
    }
    /*Operator []
    Enter: 1.coordinate
    do nothing 
    return the data in the coordinate*/
    template <typename Data>
    Data Matrix<Data>::operator[](MaShape const& alpha)
    {
        return this->storage_space[alpha.rows * this->shape.lines + alpha.lines];
    }
    /*Transpose matrix
    Enter: none
    flip the matrix
    return the transpose of matrix*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::T()
    {
        Matrix<Data> temp(MaShape{this->shape.lines, this->shape.rows}, static_cast<Data>(0));
        for (int i = 0; i < this->shape.rows; i++)
        {
            for (int j = 0; j < this->shape.lines; j++)
                temp.storage_space[i * this->shape.lines + j] = this->storage_space[j * this->shape.rows + i];
        }
        return temp;
    }
    /*endow_
    Enter: 1.coordinate 2.value
    endow the value in the coordinate
    no return*/
    template <typename Data>
    void Matrix<Data>::endow_(MaShape const& alpha, Data const& beta) {
        this->storage_space[alpha.rows * this->shape.lines + alpha.lines] = beta;
        return;
    }
    /*operator=
    Enter: 1.Matrix 2.Matrix
    copy the second Matrix to the first
    no return*/
    template <typename Data>
    void Matrix<Data>::operator=(Matrix const& alpha)
    {
        this->shape = alpha.shape;
        if (storage_space != nullptr)
            delete[] storage_space;
        this->storage_space = new Data[this->shape.rows * this->shape.lines];
        for (int i = 0; i < this->shape.rows * this->shape.lines; i++)
            this->storage_space[i] = alpha.storage_space[i];
        return;
    }
    /*operator= 
    Enter: 1.Matrix 2.value
    let the Matrix fulled with the value
    no return*/
    template <typename Data>
    void Matrix<Data>::operator=(Data const& alpha)
    {
        if (this->storage_space == nullptr)
            this->resize_(MaShape{ 1, 1 });
        for (int i = 0; i < this->shape.rows * this->shape.lines; i++)
            this->storage_space[i] = alpha;
        return;
    }
    /*operator+
    Enter: 1.Matrix 2.Matrix
    add two Matrix
    return the result*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator+(Matrix const& alpha)
    {
        if (!(this->shape == alpha.shape))
            return *this;
        Matrix<Data> temp(*this);
        for (int i = 0; i < temp.shape.rows * temp.shape.lines; i++)
            temp.storage_space[i] += alpha.storage_space[i];
        return temp;
    }
    /*operator+ 
    Enter: 1.Matrix 2.value
    add the Matrix and the value
    return the result*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator+(Data const& alpha)
    {
        Matrix<Data> temp(*this);
        for (int i = 0; i < temp.shape.rows * temp.shape.lines; i++)
            temp.storage_space[i] += alpha;
        return temp;
    }
    /*operator- 
    Enter: 1.Matrix 2.Matrix
    the first Matrix minus the second Matrix
    return the result*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator-(Matrix const& alpha)
    {
        if (!(this->shape == alpha.shape))
            return *this;
        Matrix<Data> temp(*this);
        for (int i = 0; i < temp.shape.rows * temp.shape.lines; i++)
            temp.storage_space[i] -= alpha.storage_space[i];
        return temp;
    }
    /*operator-
    Enter: 1.Matrix 2.value
    the Matrix minus the value
    return the result*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator-(Data const& alpha)
    {
        Matrix<Data> temp(*this);
        for (int i = 0; i < temp.shape.rows * temp.shape.lines; i++)
            temp.storage_space[i] -= alpha;
        return temp;
    }
    /*operator*
    Enter: 1.Matrix 2.Matrix
    multiply every element in the two Matrix
    return the result*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator*(Matrix const& alpha)
    {
        if (!(this->shape==alpha.shape))
            return *this;
        Matrix<Data> temp(*this);
        for (int i = 0; i < temp.shape.rows * temp.shape.lines; i++)
            temp.storage_space[i] *= alpha.storage_space[i];
        return temp;
    }
    /*operator*
    Enter: 1.Matrix 2.value
    multiply every element and the value
    return the result*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator*(Data const& alpha)
    {
        Matrix<Data> temp(*this);
        for (int i = 0; i < temp.shape.rows * temp.shape.lines; i++)
            temp.storage_space[i] *= alpha;
        return temp;
    }
    /*operator/ 
    Enter: 1.Matrix 2.Matrix
    divide elements in the first Matrix by elements in the second Matrix
    return the result*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator/(Matrix const& alpha){
        if (!(this->shape == alpha.shape))
            return *this;
        Matrix<Data> temp(*this);
        for (int i = 0; i < temp.shape.rows * temp.shape.lines; i++)
            temp.storage_space[i] /= alpha.storage_space[i];
        return temp;
    }
    /*operator/ 
    Enter: 1.Matrix 2.value
    divide every element in the Matrix by the value
    return the result*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator/(Data const& alpha)
    {
        Matrix<Data> temp(*this);
        for (int i = 0; i < temp.shape.rows * temp.shape.lines; i++)
        {
            temp.storage_space[i] /= alpha;
        }
        return temp;
    }
    /*operator+= 
    Enter: 1.Matrix 2.Matrix
    add elements in the second Matrix into the first Matrix
    no return*/
    template <typename Data>
    void Matrix<Data>::operator+=(Matrix const& alpha) {
        if (!(this->shape == alpha.shape))
            return;
        for (int i = 0; i < alpha.shape.rows * alpha.shape.lines; i++)
            this->storage_space[i] += alpha.storage_space[i];
        return;
    }
    /*operator+=
    Enter: 1.Matrix 2.value
    add the value into the Matrix
    no return*/
    template <typename Data>
    void Matrix<Data>::operator+=(Data const& alpha) {
        for (int i = 0; i < this->shape.rows * this->shape.lines; i++) {
            this->storage_space[i] += alpha;
        }
        return;
    }
    /*operator-= Matrix*/
    template <typename Data>
    void Matrix<Data>::operator-=(Matrix const& alpha) {
        if (!(this->shape == alpha.shape))
            return;
        for (int i = 0; i < alpha.shape.rows * alpha.shape.lines; i++)
            this->storage_space[i] -= alpha.storage_space[i];
        return;
    }
    /*operator-= Data*/
    template <typename Data>
    void Matrix<Data>::operator-=(Data const& alpha) {
        for (int i = 0; i < this->shape.rows * this->shape.lines; i++) {
            this->storage_space[i] -= alpha;
        }
        return;
    }
    /*operator*= Matrix*/
    template <typename Data>
    void Matrix<Data>::operator*=(Matrix const& alpha) {
        if (!(this->shape.lines == alpha.shape.rows)) {
            return;
        }
        Matrix<Data> temp = *this;
        *this = temp * alpha;
        return;
    }
    /*operator*= Data*/
    template <typename Data>
    void Matrix<Data>::operator*=(Data const& alpha) {
        for (int i = 0; i < this->shape.rows * this->shape.lines; i++) {
            this->storage_space[i] *= alpha;
        }
        return;
    }
    /*operator/= Data*/
    template <typename Data>
    void Matrix<Data>::operator/=(Data const& alpha) {
        for (int i = 0; i < this->shape.rows * this->shape.lines; i++) {
            this->storage_space[i] /= alpha;
        }
        return;
    }
    /*resize*/
    template <typename Data>
    void Matrix<Data>::resize_(MaShape const& alpha)
    {
        Matrix<Data> temp = *this;
        Data value = Data(1);
        delete[] storage_space;
        shape = alpha;
        storage_space = new Data[shape.rows * shape.lines];
        for (int i = 0; i < shape.rows; i++) {
            for (int j = 0; j < shape.lines; j++) {
                if (i < temp.shape.rows && j < temp.shape.lines) {
                    storage_space[i * shape.lines + j] = temp.storage_space[i * temp.shape.lines + j];
                }
                else {
                    storage_space[i * shape.lines + j] = value;
                }
            }
        }
        temp.~Matrix();
        return;
    }
    /*reshape*/
    template <typename Data>
    void Matrix<Data>::reshape_(MaShape const& alpha) {
        if (alpha.rows * alpha.lines != this->shape.rows * this->shape.lines)
            return;
        this->shape.lines = alpha.lines;
        this->shape.rows = alpha.rows;
        return;
    }

    /*dot
    Enter: 1.Matrix 2.Matrix
    dot the first matrix and the second matrix
    return the result*/
    template <typename Data>
    Matrix<Data> dot(Matrix<Data> const& beta,Matrix<Data> const& alpha)
    {
        if (beta.shape.lines != alpha.shape.rows)
            return beta;
        int n = beta.shape.lines;
        Data k = static_cast<Data>(0);
        Matrix<Data> temp({ beta.shape.rows, alpha.shape.lines }, k);
        for (int i = 0; i < temp.shape.rows; i++)
        {
            for (int j = 0; j < temp.shape.lines; j++)
            {
                for (int l = 0; l < n; l++)
                    temp.storage_space[i * temp.shape.lines + j] += beta.storage_space[i * beta.shape.lines + l] * alpha.storage_space[l * alpha.shape.lines + j];
            }
        }
        return temp;
    }
    /*show Matrix*/
    template <typename Data>
    void show_Matrix(Matrix<Data> const& alpha)
    {
        for (int i = 0; i < alpha.shape.rows; i++)
        {
            for (int j = 0; j < alpha.shape.lines; j++)
            {
                std::cout << alpha.storage_space[i * alpha.shape.lines + j];
                if (j != alpha.shape.lines - 1)
                    std::cout << ' ';
            }
            std::cout << '\n';
        }
        return;
    }
}
template class Linalg::Matrix<int8_t>;
template class Linalg::Matrix<int16_t>;
template class Linalg::Matrix<int32_t>;
template class Linalg::Matrix<int64_t>;
template class Linalg::Matrix<_Float32>;
template void Linalg::show_Matrix<int8_t>(Linalg::Matrix<int8_t> const&);
template void Linalg::show_Matrix<int16_t>(Linalg::Matrix<int16_t> const&);
template void Linalg::show_Matrix<int32_t>(Linalg::Matrix<int32_t> const&);
template void Linalg::show_Matrix<int64_t>(Linalg::Matrix<int64_t> const&);
template void Linalg::show_Matrix<_Float32>(Linalg::Matrix<_Float32> const&);