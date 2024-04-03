#include "../includes/matrix.hpp"
/*Define Matrix*/
namespace Linalg
{
    /*Mashape operator==*/
    bool operator==(MaShape const& alpha, MaShape const& beta)
    {
        return (alpha.rows == beta.rows) && (alpha.lines == beta.lines);
    }
    /*show Mashape*/
    void show_Mashape(MaShape const& alpha){
        std::cout<<"rows: "<<alpha.rows<<"\nlines: "<<alpha.lines<<'\n';
        return;
    }
    /*Constructor_01*/
    template <typename Data>
    Matrix<Data>::Matrix(MaShape const& beta, Data const& alpha)
    {
        shape = beta;
        storage_space = new Data[shape.rows * shape.lines];
        for (int i = 0; i < shape.rows * shape.lines; i++)
        {
            storage_space[i] = alpha;
        }
        return;
    }
    /*constructor_02*/
    template <typename Data>
    Matrix<Data>::Matrix(MaShape const& beta, Data* const& alpha)
    {
        shape = beta;
        storage_space = new Data[shape.rows * shape.lines];
        for (int i = 0; i < shape.rows * shape.lines; i++)
        {
            storage_space[i] = alpha[i];
        }
        return;
    }
    /*constructor_03*/
    template <typename Data>
    Matrix<Data>::Matrix(MaShape const& alpha) {
        this->shape = alpha;
        this->storage_space = new Data[this->shape.rows * this->shape.lines];
        return;
    }
    /*default constructor*/
    template <typename Data>
    Matrix<Data>::Matrix() {
        this->shape.rows = this->shape.lines = 1;
        this->storage_space = new Data[1];
        return;
    }
    /*copy constructor*/
    template <typename Data>
    Matrix<Data>::Matrix(const Matrix& alpha){
        this->shape = alpha.shape;
        this->storage_space = new Data[shape.rows * shape.lines];
        for (int i = 0; i < shape.rows * shape.lines; i++)
        {
            storage_space[i] = alpha.storage_space[i];
        }
        return;
    }
    /*Destructor*/
    template <typename Data>
    Matrix<Data>::~Matrix()
    {
        if(storage_space != nullptr)
            delete[] storage_space;
        return;
    }
    /*return value of item*/
    template <typename Data>
    Data Matrix<Data>::item(MaShape const& alpha)
    {
        return storage_space[alpha.rows * shape.lines + alpha.lines];
    }
    /*return transpose matrix*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::T()
    {
        Matrix<Data> temp({ shape.lines, shape.rows }, Data(0));
        for (int i = 0; i < shape.rows; i++)
        {
            for (int j = 0; j < shape.lines; j++)
            {
                temp.storage_space[i * shape.lines + j] = storage_space[j * shape.rows + i];
            }
        }
        return temp;
    }
    /*endow_*/
    template <typename Data>
    void Matrix<Data>::endow_(MaShape const& alpha, Data const& beta) {
        this->storage_space[alpha.rows * shape.lines + alpha.lines] = beta;
        return;
    }
    /*operator= Matrix*/
    template <typename Data>
    void Matrix<Data>::operator=(Matrix const& alpha)
    {
        shape = alpha.shape;
        if(storage_space != nullptr)
            delete[] storage_space;
        storage_space = new Data[shape.rows * shape.lines];
        for (int i = 0; i < shape.rows * shape.lines; i++)
        {
            storage_space[i] = alpha.storage_space[i];
        }
        return;
    }
    /*operator= Data*/
    template <typename Data>
    void Matrix<Data>::operator=(Data const& alpha)
    {
        if(storage_space == nullptr)
            this->resize_({ 1, 1 });
        for (int i = 0; i < shape.rows * shape.lines; i++)
        {
            storage_space[i] = alpha;
        }
        return;
    }
    /*operator+ Matrix*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator+(Matrix const& alpha)
    {
        if (!(shape == alpha.shape))
            return *this;
        Matrix<Data> temp(shape, Data(0));
        for (int i = 0; i < shape.rows * shape.lines; i++)
        {
            temp.storage_space[i] = storage_space[i] + alpha.storage_space[i];
        }
        return temp;
    }
    /*operator+ Data*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator+(Data const& alpha)
    {
        Matrix<Data> temp(shape, storage_space);
        for (int i = 0; i < shape.rows * shape.lines; i++)
        {
            temp.storage_space[i] += alpha;
        }
        return temp;
    }
    /*operator- Matrix*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator-(Matrix const& alpha)
    {
        if (!(shape == alpha.shape))
            return *this;
        Matrix<Data> temp(shape, Data(0));
        for (int i = 0; i < shape.rows * shape.lines; i++)
        {
            temp.storage_space[i] -= alpha.storage_space[i];
        }
        return temp;
    }
    /*operator- Data*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator-(Data const& alpha)
    {
        Matrix<Data> temp(shape, storage_space);
        for (int i = 0; i < shape.rows * shape.lines; i++)
        {
            temp.storage_space[i] -= alpha;
        }
        return temp;
    }
    /*operator* Matrix*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator*(Matrix const& alpha)
    {
        if (shape.lines != alpha.shape.rows)
            return *this;
        int n = shape.lines;
        Data k = Data(0);
        Matrix<Data> temp({ shape.rows, alpha.shape.lines }, Data(0));
        for (int i = 0; i < temp.shape.rows; i++)
        {
            for (int j = 0; j < temp.shape.lines; j++)
            {
                for (int l = 0; l < n; l++)
                {
                    k += storage_space[i * shape.lines + l] * alpha.storage_space[l * alpha.shape.lines + j];
                }
                temp.storage_space[i * temp.shape.lines + j] = k;
            }
        }
        return temp;
    }
    /*operator* Data*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator*(Data const& alpha)
    {
        Matrix<Data> temp(shape, storage_space);
        for (int i = 0; i < shape.rows * shape.lines; i++)
        {
            temp.storage_space[i] *= alpha;
        }
        return temp;
    }
    /*operator/ Data*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator/(Data const& alpha)
    {
        Matrix<Data> temp(shape, storage_space);
        for (int i = 0; i < shape.rows * shape.lines; i++)
        {
            temp.storage_space[i] /= alpha;
        }
        return temp;
    }
    /*operator+= Matrix*/
    template <typename Data>
    void Matrix<Data>::operator+=(Matrix const& alpha) {
        if (!(this->shape == alpha.shape))
            return;
        for (int i = 0; i < alpha.shape.rows * alpha.shape.lines; i++)
            this->storage_space[i] += alpha.storage_space[i];
        return;
    }
    /*operator+= Data*/
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
    void Matrix<Data>::reshape_(MaShape const& alpha){
        if(alpha.rows * alpha.lines != this->shape.rows * this->shape.lines)
            return;
        this->shape.lines=alpha.lines;
        this->shape.rows=alpha.rows;
        return;
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