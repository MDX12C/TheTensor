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
        beta << std::noshowpos << "rows: " << alpha.rows << " lines: " << alpha.lines << '\n';
        return beta;
    }
    /*belong
    Enter: 1.coordinate 2.MaShape
    check if the coordinate is in the MaShape
    return true if it is*/
    bool belongs(MaShape const& alpha, MaShape const& beta) {
        if (alpha.lines < 0 || alpha.rows < 0)
            return false;
        return (alpha.lines < beta.lines) && (alpha.rows < beta.rows);
    }
    /*Constructor_Value
    Enter 1.Matrix_shape 2.init value
    use the shape to construct a Matrix full of the init data
    no return */
    template <typename Data>
    Matrix<Data>::Matrix(MaShape const& beta, Data const& alpha)
    {
        this->_shape.lines = beta.lines > 0 ? beta.lines : 1;
        this->_shape.rows = beta.rows > 0 ? beta.rows : 1;
        this->_size = this->_shape.lines * this->_shape.rows;
        this->storage_space = new Data[this->_size];
        for (int i = 0; i < this->_size; i++)
            this->storage_space[i] = alpha;
        this->_sum = static_cast<Data>(this->_size) * alpha;
        this->_digits = Basic_Math::Int_Digits(alpha);
        return;
    }
    /*Constructor_Datas
    Enter 1.Matrix_shape 2.pointer to init datas
    use the shape to construct a Matrix and init it with the array
    no return */
    template <typename Data>
    Matrix<Data>::Matrix(MaShape const& beta, Data* const& alpha)
    {
        this->_shape = beta;
        if (this->_shape.rows <= 0 || this->_shape.lines <= 0) {
            this->_shape.lines = this->_shape.rows = this->_size = 1;
            this->storage_space = new Data[1];
            this->_sum = static_cast<Data>(0);
            this->_digits = 1;
            this->storage_space[0] = static_cast<Data>(0);
            return;
        }
        this->_digits = 1;
        this->_sum = static_cast<Data>(0);
        this->_size = this->_shape.lines * this->_shape.rows;
        this->storage_space = new Data[this->_size];
        for (int i = 0; i < this->_size; i++) {
            this->storage_space[i] = alpha[i];
            this->_sum += alpha[i];
            this->_digits = std::max(this->_digits, Basic_Math::Int_Digits(alpha[i]));
        }
        return;
    }
    /*Constructor_Shape
    Enter 1.Matrix_shape
    use the shape to construct a Matrix and init it with 0
    no return */
    template <typename Data>
    Matrix<Data>::Matrix(MaShape const& alpha) {
        this->_shape.lines = alpha.lines > 0 ? alpha.lines : 1;
        this->_shape.rows = alpha.rows > 0 ? alpha.rows : 1;
        this->_size = this->_shape.lines * this->_shape.rows;
        this->storage_space = new Data[this->_size];
        this->_sum = static_cast<Data>(0);
        this->_digits = 1;
        for (int i = 0; i < this->_size; i++)
            this->storage_space[i] = static_cast<Data>(0);
        return;
    }
    /*Default constructor
    Enter: none
    construct an Matrix with 1*1 and init it with 0
    no return */
    template <typename Data>
    Matrix<Data>::Matrix() {
        this->_shape.rows = this->_shape.lines = this->_size = 1;
        this->storage_space = new Data[1];
        this->storage_space[0] = static_cast<Data>(0);
        this->_sum = static_cast<Data>(0);
        this->_digits = 1;
        return;
    }
    /*Copy constructor
    Enter: 1.Matrix
    copy the Matrix
    no return */
    template <typename Data>
    Matrix<Data>::Matrix(const Matrix& alpha) {
        this->_shape = alpha._shape;
        this->_size = alpha._size;
        this->_sum = alpha._sum;
        this->_digits = alpha._digits;
        this->storage_space = new Data[this->_size];
        for (int i = 0; i < this->_size; i++)
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
        if (this->_size)
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
        if (belongs(alpha, this->_shape))
            return this->storage_space[alpha.rows * this->_shape.lines + alpha.lines];
        return static_cast<Data>(0);
    }
    /*Transpose matrix
    Enter: none
    flip the matrix
    return the transpose of matrix*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::T()
    {
        Matrix<Data> temp(MaShape{ this->_shape.lines, this->_shape.rows }, static_cast<Data>(0));
        for (int i = 0; i < this->_shape.rows; i++)
        {
            for (int j = 0; j < this->_shape.lines; j++)
                temp.storage_space[j * temp._shape.lines + i] = this->storage_space[i * this->_shape.lines + j];
        }
        temp._sum = this->_sum;
        temp._digits = this->_digits;
        return temp;
    }
    /*endow_
    Enter: 1.coordinate 2.value
    endow the value at the coordinate
    no return*/
    template <typename Data>
    void Matrix<Data>::endow_(MaShape const& alpha, Data const& beta) {
        if (!belongs(alpha, this->_shape)) {
            return;
        }
        this->_sum -= this->storage_space[alpha.rows * this->_shape.lines + alpha.lines];
        this->_sum += this->storage_space[alpha.rows * this->_shape.lines + alpha.lines] = beta;
        this->_digits = 1;
        for (int i = 0; i < this->_size; i++)
            this->_digits = std::max(this->_digits, Basic_Math::Int_Digits(this->storage_space[i]));
        return;
    }
    /*operator=
    Enter: 1.Matrix 2.Matrix
    copy the second Matrix to the first
    no return*/
    template <typename Data>
    void Matrix<Data>::operator=(Matrix const& alpha)
    {
        this->_shape = alpha._shape;
        this->_size = alpha._size;
        this->_sum = alpha._sum;
        this->_digits = alpha._digits;
        if (storage_space != nullptr)
            delete[] storage_space;
        this->storage_space = new Data[this->_size];
        for (int i = 0; i < this->_size; i++)
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
        for (int i = 0; i < this->_size; i++)
            this->storage_space[i] = alpha;
        this->_sum = static_cast<Data>(this->_size) * alpha;
        this->_digits = Basic_Math::Int_Digits(alpha);
        return;
    }
    /*operator+
    Enter: 1.Matrix 2.Matrix
    add two Matrix
    return the result*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator+(Matrix const& alpha)
    {
        if (!(this->_shape == alpha._shape))
            return *this;
        Matrix<Data> temp(*this);
        temp._digits = 1;
        for (int i = 0; i < temp._size; i++) {
            temp.storage_space[i] += alpha.storage_space[i];
            temp._digits = std::max(temp._digits, Basic_Math::Int_Digits(temp.storage_space[i]));
        }
        temp._sum += alpha._sum;
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
        temp._digits = 1;
        for (int i = 0; i < temp._size; i++) {
            temp.storage_space[i] += alpha;
            temp._digits = std::max(temp._digits, Basic_Math::Int_Digits(temp.storage_space[i]));
        }
        temp._sum += static_cast<Data>(temp._size) * alpha;
        return temp;
    }
    /*operator-
    Enter: 1.Matrix 2.Matrix
    the first Matrix minus the second Matrix
    return the result*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator-(Matrix const& alpha)
    {
        if (!(this->_shape == alpha._shape))
            return *this;
        Matrix<Data> temp(*this);
        temp._digits = 1;
        for (int i = 0; i < temp._size; i++) {
            temp.storage_space[i] -= alpha.storage_space[i];
            temp._digits = std::max(temp._digits, Basic_Math::Int_Digits(temp.storage_space[i]));
        }
        temp._sum -= alpha._sum;
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
        temp._digits = 1;
        for (int i = 0; i < temp._size; i++) {
            temp.storage_space[i] -= alpha;
            temp._digits = std::max(temp._digits, Basic_Math::Int_Digits(temp.storage_space[i]));
        }
        temp._sum -= static_cast<Data>(temp._size) * alpha;
        return temp;
    }
    /*operator*
    Enter: 1.Matrix 2.Matrix
    multiply every element in the two Matrix
    return the result*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator*(Matrix const& alpha)
    {
        if (!(this->_shape == alpha._shape))
            return *this;
        Matrix<Data> temp(*this);
        temp._digits = 1;
        temp._sum = static_cast<Data>(0);
        for (int i = 0; i < temp._size; i++) {
            temp.storage_space[i] *= alpha.storage_space[i];
            temp._digits = std::max(temp._digits, Basic_Math::Int_Digits(temp.storage_space[i]));
            temp._sum += temp.storage_space[i];
        }
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
        temp._digits = 1;
        for (int i = 0; i < temp._size; i++) {
            temp.storage_space[i] *= alpha;
            temp._digits = std::max(temp._digits, Basic_Math::Int_Digits(temp.storage_space[i]));
        }
        temp._sum *= alpha;
        return temp;
    }
    /*operator/
    Enter: 1.Matrix 2.Matrix
    divide elements in the first Matrix by elements in the second Matrix
    return the result*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator/(Matrix const& alpha) {
        if (!(this->_shape == alpha._shape))
            return *this;
        Matrix<Data> temp(*this);
        temp._digits = 1;
        temp._sum = static_cast<Data>(0);
        for (int i = 0; i < temp._size; i++) {
            temp.storage_space[i] /= alpha.storage_space[i];
            temp._digits = std::max(temp._digits, Basic_Math::Int_Digits(temp.storage_space[i]));
            temp._sum += temp.storage_space[i];
        }
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
        temp._digits = 1;
        for (int i = 0; i < temp._size; i++)
        {
            temp.storage_space[i] /= alpha;
            temp._digits = std::max(temp._digits, Basic_Math::Int_Digits(temp.storage_space[i]));
        }
        temp._sum /= alpha;
        return temp;
    }
    /*operator+=
    Enter: 1.Matrix 2.Matrix
    add elements in the second Matrix into the first Matrix
    no return*/
    template <typename Data>
    void Matrix<Data>::operator+=(Matrix const& alpha) {
        if (!(this->_shape == alpha._shape))
            return;
        this->_digits = 1;
        for (int i = 0; i < alpha._size; i++) {
            this->storage_space[i] += alpha.storage_space[i];
            this->_digits = std::max(this->_digits, Basic_Math::Int_Digits(this->storage_space[i]));
        }
        this->_sum += alpha._sum;
        return;
    }
    /*operator+=
    Enter: 1.Matrix 2.value
    add the value into the Matrix
    no return*/
    template <typename Data>
    void Matrix<Data>::operator+=(Data const& alpha) {
        this->_digits = 1;
        for (int i = 0; i < this->_size; i++) {
            this->storage_space[i] += alpha;
            this->_digits = std::max(this->_digits, Basic_Math::Int_Digits(this->storage_space[i]));
        }
        this->_sum += static_cast<Data>(this->_size) * alpha;
        return;
    }
    /*operator-=
    Enter: 1.Matrix 2.Matrix
    subtract elements in the second Matrix from the first Matrix
    no return*/
    template <typename Data>
    void Matrix<Data>::operator-=(Matrix const& alpha) {
        if (!(this->_shape == alpha._shape))
            return;
        this->_digits = 1;
        for (int i = 0; i < this->_size; i++) {
            this->storage_space[i] -= alpha.storage_space[i];
            this->_digits = std::max(this->_digits, Basic_Math::Int_Digits(this->storage_space[i]));
        }
        this->_sum -= alpha._sum;
        return;
    }
    /*operator-=
    Enter: 1.Matrix 2.value
    subtract every element in the Matrix by the value
    no return*/
    template <typename Data>
    void Matrix<Data>::operator-=(Data const& alpha) {
        this->_digits = 1;
        for (int i = 0; i < this->_size; i++) {
            this->storage_space[i] -= alpha;
            this->_digits = std::max(this->_digits, Basic_Math::Int_Digits(this->storage_space[i]));
        }
        this->_sum -= static_cast<Data>(this->_size) * alpha;
        return;
    }
    /*operator*=
    Enter: 1.Matrix 2.Matrix
    multiply every in the first Matrix by the second Matrix
    no return*/
    template <typename Data>
    void Matrix<Data>::operator*=(Matrix const& alpha) {
        if (!(this->_shape == alpha._shape))
            return;
        this->_digits = 1;
        this->_sum = static_cast<Data>(0);
        for (int i = 0; i < this->_size; i++) {
            this->storage_space[i] *= alpha.storage_space[i];
            this->_digits = std::max(this->_digits, Basic_Math::Int_Digits(this->storage_space[i]));
            this->_sum += this->storage_space[i];
        }
        return;
    }
    /*operator*=
    Enter: 1.Matrix 2.value
    mutiply every element in the Matrix by the value
    no return*/
    template <typename Data>
    void Matrix<Data>::operator*=(Data const& alpha) {
        this->_digits = 1;
        for (int i = 0; i < this->_size; i++) {
            this->storage_space[i] *= alpha;
            this->_digits = std::max(this->_digits, Basic_Math::Int_Digits(this->storage_space[i]));
        }
        this->_sum *= alpha;
        return;
    }
    /*operator/=
    Enter: 1.Matrix 2.Matrix
    divide every element in the first Matrix by the elements in the second Matrix
    no return*/
    template <typename Data>
    void Matrix<Data>::operator/=(Matrix const& alpha) {
        if (!(this->_shape == alpha._shape))
            return;
        this->_digits = 1;
        for (int i = 0; i < this->_size; i++) {
            this->storage_space[i] /= alpha.storage_space[i];
            this->_digits = std::max(this->_digits, Basic_Math::Int_Digits(this->storage_space[i]));
            this->_sum += this->storage_space[i];
        }
        return;
    }
    /*operator/=
    Enter: 1.Matrix 2.value
    divide every elements in the Matrix by the value
    no return*/
    template <typename Data>
    void Matrix<Data>::operator/=(Data const& alpha) {
        this->_digits = 1;
        for (int i = 0; i < this->_size; i++) {
            this->storage_space[i] /= alpha;
            this->_digits = std::max(this->_digits, Basic_Math::Int_Digits(this->storage_space[i]));
        }
        this->_sum /= alpha;
        return;
    }
    /*resize
    Enter: 1.Mashape
    resize the Matrix into the shape, and the beyond's elements will be filled with 0
    no return*/
    template <typename Data>
    void Matrix<Data>::resize_(MaShape const& alpha)
    {
        if (this->_shape == alpha) return;
        if (alpha.lines <= 0 || alpha.rows <= 0) return;
        Linalg::MaShape beta;
        Matrix<Data> temp(*this);
        Data value = static_cast<Data>(0);
        delete[] this->storage_space;
        this->_shape = alpha;
        this->_size = this->_shape.rows * this->_shape.lines;
        this->_digits = 1;
        this->_sum = value;
        this->storage_space = new Data[this->_size];
        for (beta.rows = 0; beta.rows < this->_shape.rows; beta.rows++) {
            for (beta.lines = 0; beta.lines < this->_shape.lines; beta.lines++) {
                if (Linalg::belongs(beta, temp._shape)) {
                    this->storage_space[this->_shape.lines * beta.rows + beta.lines] = temp[beta];
                    this->_sum += this->storage_space[this->_shape.lines * beta.rows + beta.lines];
                    this->_digits = std::max(this->_digits, Basic_Math::Int_Digits(this->storage_space[this->_shape.lines * beta.rows + beta.lines]));
                }
                else {
                    this->storage_space[this->_shape.lines * beta.rows + beta.lines] = value;
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
        if (this->_shape == alpha) return;
        if (alpha.lines <= 0 || alpha.rows <= 0) return;
        if ((alpha.rows * alpha.lines) != this->_size)
            return;
        this->_shape.lines = alpha.lines;
        this->_shape.rows = alpha.rows;
        return;
    }
    /*freedom
    Enter: none
    free the Matrix and set the shape to 1,1
    no return*/
    template <typename Data>
    void Matrix<Data>::freedom_() {
        delete[] this->storage_space;
        this->_shape.lines = 1;
        this->_shape.rows = 1;
        this->storage_space = new Data[1];
        this->storage_space[0] = static_cast<Data>(0);
        this->_size = 1;
        this->_sum = static_cast<Data>(0);
        this->_digits = 1;
        return;
    }

    /*dot
    Enter: 1.Matrix 2.Matrix
    dot the first matrix and the second matrix
    return the result*/
    template <typename Data>
    Matrix<Data> dot(Matrix<Data> const& beta, Matrix<Data> const& alpha)
    {
        if (beta._shape.lines != alpha._shape.rows)
            return beta;
        int n = beta._shape.lines;
        Matrix<Data> temp(MaShape{ beta._shape.rows, alpha._shape.lines });
        for (int i = 0; i < temp._shape.rows; i++)
        {
            for (int j = 0; j < temp._shape.lines; j++)
            {
                for (int l = 0; l < n; l++) {
                    temp.storage_space[i * temp._shape.lines + j] += beta.storage_space[i * beta._shape.lines + l] * alpha.storage_space[l * alpha._shape.lines + j];
                    temp._sum += temp.storage_space[i * temp._shape.lines + j];
                    temp._digits = std::max(temp._digits, Basic_Math::Int_Digits(temp.storage_space[i * temp._shape.lines + j]));
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
    std::ostream& operator<<(std::ostream& beta, Matrix<Data> const& alpha)
    {
        beta << alpha._shape << "size: " << alpha._size << " sum: " << alpha._sum << '\n';
        for (int i = 0; i < alpha._shape.rows; i++)
        {
            for (int j = 0; j < alpha._shape.lines; j++)
            {
                beta << std::setprecision(Basic_Math::Float16_Accuracy) \
                    << std::fixed << std::setfill(' ') << std::showpoint \
                    << std::showpos << std::internal \
                    << std::setw(Basic_Math::Float16_Accuracy + alpha._digits + 2) \
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
    void AddLine_(Matrix<Data>& alpha, Vector<Data> const& beta) {
        if (alpha._shape.rows != beta._shape)
            return;
        int gamma = alpha._shape.lines;
        alpha.resize_(MaShape{ alpha._shape.rows, alpha._shape.lines + 1 });
        for (int theta = 0; theta < beta._shape; theta++) {
            alpha.storage_space[alpha._shape.lines * theta + gamma] = beta[theta];
        }
        alpha._sum += beta._sum;
        alpha._digits = std::max(alpha._digits, beta._digits);
        return;
    }
    /*Add Row
    Enter: 1.Matrix 2.Vector
    add the Vector to the end of the Matrix(Row)
    no return*/
    template <typename Data>
    void AddRow_(Matrix<Data>& alpha, Vector<Data> const& beta) {
        if (alpha._shape.lines != beta._shape)
            return;
        int gamma = alpha._shape.rows;
        alpha.resize_(MaShape{ alpha._shape.rows + 1, alpha._shape.lines });
        for (int theta = 0; theta < beta._shape; theta++) {
            alpha.storage_space[alpha._shape.lines * gamma + theta] = beta[theta];
        }
        alpha._sum += beta._sum;
        alpha._digits = std::max(alpha._digits, beta._digits);
        return;
    }
}
template class Linalg::Matrix<int32_t>;
template class Linalg::Matrix<_Float32>;
template class Linalg::Matrix<bool>;
template std::ostream& Linalg::operator<<(std::ostream&, Linalg::Matrix<int32_t> const&);
template std::ostream& Linalg::operator<<(std::ostream&, Linalg::Matrix<_Float32> const&);
template std::ostream& Linalg::operator<<(std::ostream&, Linalg::Matrix<bool> const&);
template Linalg::Matrix<int32_t> Linalg::dot(Linalg::Matrix<int32_t> const&, Linalg::Matrix<int32_t> const&);
template Linalg::Matrix<_Float32> Linalg::dot(Linalg::Matrix<_Float32> const&, Linalg::Matrix<_Float32> const&);
template Linalg::Matrix<bool> Linalg::dot(Linalg::Matrix<bool> const&, Linalg::Matrix<bool> const&);