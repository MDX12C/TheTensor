#include "../includes/matrix.hpp"
/*Define Matrix*/
namespace Linalg
{
    /*MaShape operator==
    Enter: 1.MaShape 2.MaShape
    compare two MaShape
    return true if they are equal */
    bool operator==(MaShape const& alpha, MaShape const& beta)
    {
        return (alpha.rows == beta.rows) && (alpha.lines == beta.lines);
    }
    /*MaShape operator<<
    Enter: 1.ostream 2.MaShape
    show the MaShape's rows and lines
    return the ostream */
    std::ostream& operator<<(std::ostream& beta, MaShape const& alpha) {
        beta << "rows: " << alpha.rows << "\nlines: " << alpha.lines << '\n';
        return beta;
    }
    /*MaShape operator>>
    Enter: 1.istream 2.MaShape
    read the MaShape's rows and lines from the istream
    return the istream*/
    std::istream& operator>>(std::istream& beta, MaShape& alpha) {
        beta >> alpha.rows >> alpha.lines;
        return beta;
    }
    /*belong
    Enter: 1.coordinate 2.MaShape
    check if the coordinate is in the MaShape
    return true if it is*/
    bool belongs(MaShape const& alpha, MaShape const& beta) {
        return (alpha.lines < beta.lines) && (alpha.rows < beta.rows);
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
            this->shape.lines = this->shape.rows = 1;
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
        Matrix<Data> temp(MaShape{ this->shape.lines, this->shape.rows }, static_cast<Data>(0));
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
        if (!(this->shape == alpha.shape))
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
    Matrix<Data> Matrix<Data>::operator/(Matrix const& alpha) {
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
    /*operator-=
    Enter: 1.Matrix 2.Matrix
    subtract elements in the second Matrix from the first Matrix
    no return*/
    template <typename Data>
    void Matrix<Data>::operator-=(Matrix const& alpha) {
        if (!(this->shape == alpha.shape))
            return;
        for (int i = 0; i < this->shape.rows * this->shape.lines; i++)
            this->storage_space[i] -= alpha.storage_space[i];
        return;
    }
    /*operator-=
    Enter: 1.Matrix 2.value
    subtract every element in the Matrix by the value
    no return*/
    template <typename Data>
    void Matrix<Data>::operator-=(Data const& alpha) {
        for (int i = 0; i < this->shape.rows * this->shape.lines; i++) {
            this->storage_space[i] -= alpha;
        }
        return;
    }
    /*operator*=
    Enter: 1.Matrix 2.Matrix
    multiply every in the first Matrix by the second Matrix
    no return*/
    template <typename Data>
    void Matrix<Data>::operator*=(Matrix const& alpha) {
        if (!(this->shape == alpha.shape))
            return;
        for (int i = 0; i < this->shape.rows * this->shape.lines; i++)
            this->storage_space[i] *= alpha.storage_space[i];
        return;
    }
    /*operator*=
    Enter: 1.Matrix 2.value
    mutiply every element in the Matrix by the value
    no return*/
    template <typename Data>
    void Matrix<Data>::operator*=(Data const& alpha) {
        for (int i = 0; i < this->shape.rows * this->shape.lines; i++) {
            this->storage_space[i] *= alpha;
        }
        return;
    }
    /*operator/=
    Enter: 1.Matrix 2.Matrix
    divide every element in the first Matrix by the elements in the second Matrix
    no return*/
    template <typename Data>
    void Matrix<Data>::operator/=(Matrix const& alpha) {
        if (!(this->shape == alpha.shape))
            return;
        for (int i = 0; i < this->shape.rows * this->shape.lines; i++)
            this->storage_space[i] /= alpha.storage_space[i];
        return;
    }
    /*operator/=
    Enter: 1.Matrix 2.value
    divide every elements in the Matrix by the value
    no return*/
    template <typename Data>
    void Matrix<Data>::operator/=(Data const& alpha) {
        for (int i = 0; i < this->shape.rows * this->shape.lines; i++) {
            this->storage_space[i] /= alpha;
        }
        return;
    }
    /*resize
    Enter: 1.Mashape
    resize the Matrix into the shape, and the beyond's elements will be filled with 1
    no return*/
    template <typename Data>
    void Matrix<Data>::resize_(MaShape const& alpha)
    {
        Linalg::MaShape beta;
        Matrix<Data> temp = *this;
        Data value = static_cast<Data>(1);
        delete[] this->storage_space;
        this->shape = alpha;
        this->storage_space = new Data[this->shape.rows * this->shape.lines];
        for (beta.rows = 0; beta.rows < this->shape.rows; beta.rows++) {
            for (beta.lines = 0; beta.lines < this->shape.lines; beta.lines++) {
                if (Linalg::belongs(beta, temp.shape)) {
                    this->storage_space[this->shape.lines * beta.rows + beta.lines] = temp[beta];
                }
                else {
                    this->storage_space[this->shape.lines * beta.rows + beta.lines] = value;
                }
            }
        }
        return;
    }
    /*reshape
    Enter: 1.MaShape
    reshape the Matrix into the shape, and the number of elements must be the same
    no return*/
    template <typename Data>
    void Matrix<Data>::reshape_(MaShape const& alpha) {
        if (alpha.rows * alpha.lines != this->shape.rows * this->shape.lines)
            return;
        this->shape.lines = alpha.lines;
        this->shape.rows = alpha.rows;
        return;
    }

    /*operator+
    Enter: 1.value 2.Matrix
    add the value and the Matrix
    return the result*/
    template <typename Data>
    Matrix<Data> operator+(Data const& alpha, Matrix<Data> const& beta) {
        Matrix<Data> temp = beta;
        temp += alpha;
        return temp;
    }
    /*operator-
    Enter: 1.value 2.Matrix
    subtract the value from the Matrix
    return the result*/
    template <typename Data>
    Matrix<Data> operator-(Data const& alpha, Matrix<Data> const& beta) {
        Matrix<Data> temp = beta;
        temp *= static_cast<Data>(-1);
        temp += alpha;
        return temp;
    }
    /*operator*
    Enter: 1.value 2.Matrix
    multiply the value to the Matrix
    return the result*/
    template <typename Data>
    Matrix<Data> operator*(Data const& alpha, Matrix<Data> const& beta) {
        Matrix<Data> temp = beta;
        temp *= alpha;
        return temp;
    }
    /*operator/
    Enter: 1.value 2.Matrix
    divide the value to the Matrix
    return the result*/
    template <typename Data>
    Matrix<Data> operator/(Data const& alpha, Matrix<Data> const& beta) {
        Matrix<Data> temp(beta.shape, alpha);
        temp /= beta;
        return temp;
    }
    /*dot
    Enter: 1.Matrix 2.Matrix
    dot the first matrix and the second matrix
    return the result*/
    template <typename Data>
    Matrix<Data> dot(Matrix<Data> const& beta, Matrix<Data> const& alpha)
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
    /*operator<<
    Enter: 1.ostream 2.Matrix
    print the Matrix
    return the ostream*/
    template <typename Data>
    std::ostream& operator<<(std::ostream& beta, Matrix<Data> const& alpha)
    {
        beta << alpha.shape;
        for (int i = 0; i < alpha.shape.rows; i++)
        {
            for (int j = 0; j < alpha.shape.lines; j++)
            {
                beta << alpha.storage_space[i * alpha.shape.lines + j];
                if (j != alpha.shape.lines - 1)
                    beta << ' ';
            }
            beta << '\n';
        }
        return beta;
    }
    /*operator>>
    Enter: 1.istream 2.Matrix
    read the shape and the value from the istream
    return the istream*/
    template <typename Data>
    std::istream& operator>>(std::istream& beta, Matrix<Data>& alpha) {
        Linalg::MaShape theta;
        beta >> alpha.shape;
        for (theta.rows = 0; theta.rows < alpha.shape.rows; theta.rows++) {
            for (theta.lines = 0; theta.lines < alpha.shape.lines; theta.lines++)
                beta >> alpha.storage_space[theta.rows * alpha.shape.lines + theta.lines];
        }
        return beta;
    }
}
template class Linalg::Matrix<int8_t>;
template class Linalg::Matrix<int16_t>;
template class Linalg::Matrix<int32_t>;
template class Linalg::Matrix<int64_t>;
template class Linalg::Matrix<_Float32>;
template class Linalg::Matrix<_Float64>;
template class Linalg::Matrix<bool>;
// template Linalg::Matrix<int8_t> Linalg::operator+(int8_t const&, Linalg::Matrix<int8_t> const&);
// template Linalg::Matrix<int16_t> Linalg::operator+(int16_t const&, Linalg::Matrix<int16_t> const&);
// template Linalg::Matrix<int32_t> Linalg::operator+(int32_t const&, Linalg::Matrix<int32_t> const&);
// template Linalg::Matrix<int64_t> Linalg::operator+(int64_t const&, Linalg::Matrix<int64_t> const&);
// template Linalg::Matrix<_Float32> Linalg::operator+(float const&, Linalg::Matrix<_Float32> const&);
// template Linalg::Matrix<_Float64> Linalg::operator+(double const&, Linalg::Matrix<_Float64> const&);
// template Linalg::Matrix<bool> Linalg::operator+(bool const&, Linalg::Matrix<bool> const&);
// template Linalg::Matrix<int8_t> Linalg::operator-(int8_t const&, Linalg::Matrix<int8_t> const&);
// template Linalg::Matrix<int16_t> Linalg::operator-(int16_t const&, Linalg::Matrix<int16_t> const&);
// template Linalg::Matrix<int32_t> Linalg::operator-(int32_t const&, Linalg::Matrix<int32_t> const&);
// template Linalg::Matrix<int64_t> Linalg::operator-(int64_t const&, Linalg::Matrix<int64_t> const&);
// template Linalg::Matrix<_Float32> Linalg::operator-(float const&, Linalg::Matrix<_Float32> const&);
// template Linalg::Matrix<_Float64> Linalg::operator-(double const&, Linalg::Matrix<_Float64> const&);
// template Linalg::Matrix<bool> Linalg::operator-(bool const&, Linalg::Matrix<bool> const&);
// template Linalg::Matrix<int8_t> Linalg::operator*(int8_t const&, Linalg::Matrix<int8_t> const&);
// template Linalg::Matrix<int16_t> Linalg::operator*(int16_t const&, Linalg::Matrix<int16_t> const&);
// template Linalg::Matrix<int32_t> Linalg::operator*(int32_t const&, Linalg::Matrix<int32_t> const&);
// template Linalg::Matrix<int64_t> Linalg::operator*(int64_t const&, Linalg::Matrix<int64_t> const&);
// template Linalg::Matrix<_Float32> Linalg::operator*(float const&, Linalg::Matrix<_Float32> const&);
// template Linalg::Matrix<_Float64> Linalg::operator*(double const&, Linalg::Matrix<_Float64> const&);
// template Linalg::Matrix<bool> Linalg::operator*(bool const&, Linalg::Matrix<bool> const&);
// template Linalg::Matrix<int8_t> Linalg::operator/(int8_t const&, Linalg::Matrix<int8_t> const&);
// template Linalg::Matrix<int16_t> Linalg::operator/(int16_t const&, Linalg::Matrix<int16_t> const&);
// template Linalg::Matrix<int32_t> Linalg::operator/(int32_t const&, Linalg::Matrix<int32_t> const&);
// template Linalg::Matrix<int64_t> Linalg::operator/(int64_t const&, Linalg::Matrix<int64_t> const&);
// template Linalg::Matrix<_Float32> Linalg::operator/(float const&, Linalg::Matrix<_Float32> const&);
// template Linalg::Matrix<_Float64> Linalg::operator/(double const&, Linalg::Matrix<_Float64> const&);
// template Linalg::Matrix<bool> Linalg::operator/(bool const&, Linalg::Matrix<bool> const&);
template std::ostream& Linalg::operator<<(std::ostream&, Linalg::Matrix<int8_t> const&);
template std::ostream& Linalg::operator<<(std::ostream&, Linalg::Matrix<int16_t> const&);
template std::ostream& Linalg::operator<<(std::ostream&, Linalg::Matrix<int32_t> const&);
template std::ostream& Linalg::operator<<(std::ostream&, Linalg::Matrix<int64_t> const&);
template std::ostream& Linalg::operator<<(std::ostream&, Linalg::Matrix<_Float32> const&);
template std::ostream& Linalg::operator<<(std::ostream&, Linalg::Matrix<_Float64> const&);
template std::ostream& Linalg::operator<<(std::ostream&, Linalg::Matrix<bool> const&);
template std::istream& Linalg::operator>>(std::istream&, Linalg::Matrix<int8_t>&);
template std::istream& Linalg::operator>>(std::istream&, Linalg::Matrix<int16_t>&);
template std::istream& Linalg::operator>>(std::istream&, Linalg::Matrix<int32_t>&);
template std::istream& Linalg::operator>>(std::istream&, Linalg::Matrix<int64_t>&);
template std::istream& Linalg::operator>>(std::istream&, Linalg::Matrix<_Float32>&);
template std::istream& Linalg::operator>>(std::istream&, Linalg::Matrix<_Float64>&);
template std::istream& Linalg::operator>>(std::istream&, Linalg::Matrix<bool>&);
template Linalg::Matrix<int8_t> Linalg::dot(Linalg::Matrix<int8_t> const&, Linalg::Matrix<int8_t> const&);
template Linalg::Matrix<int16_t> Linalg::dot(Linalg::Matrix<int16_t> const&, Linalg::Matrix<int16_t> const&);
template Linalg::Matrix<int32_t> Linalg::dot(Linalg::Matrix<int32_t> const&, Linalg::Matrix<int32_t> const&);
template Linalg::Matrix<int64_t> Linalg::dot(Linalg::Matrix<int64_t> const&, Linalg::Matrix<int64_t> const&);
template Linalg::Matrix<_Float32> Linalg::dot(Linalg::Matrix<_Float32> const&, Linalg::Matrix<_Float32> const&);
template Linalg::Matrix<_Float64> Linalg::dot(Linalg::Matrix<_Float64> const&, Linalg::Matrix<_Float64> const&);
template Linalg::Matrix<bool> Linalg::dot(Linalg::Matrix<bool> const&, Linalg::Matrix<bool> const&);