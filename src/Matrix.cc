#include "../includes/matrix.hpp"
/*Define Matrix*/
namespace Linalg
{
    /*Mashape operator*/
    bool operator==(MaShape const &alpha, MaShape const &beta)
    {
        return (alpha.row == beta.row) && (alpha.lines == beta.lines);
    }
    /*Constructor_01*/
    template <typename Data>
    Matrix<Data>::Matrix(MaShape const &beta, Data const &alpha)
    {
        shape = beta;
        storage_space = new Data[shape.row * shape.lines];
        for (int i = 0; i < shape.row * shape.lines; i++)
        {
            storage_space[i] = alpha;
        }
        return;
    }
    /*constructor_02*/
    template <typename Data>
    Matrix<Data>::Matrix(MaShape const &beta, Data *const &alpha)
    {
        shape = beta;
        storage_space = new Data[shape.row * shape.lines];
        for (int i = 0; i < shape.row * shape.lines; i++)
        {
            storage_space[i] = alpha[i];
        }
        return;
    }
    /*Destructor*/
    template <typename Data>
    Matrix<Data>::~Matrix()
    {
        delete[] storage_space;
        return;
    }
    /*return pointer of item*/
    template <typename Data>
    Data *Matrix<Data>::item(MaShape const &alpha)
    {
        return &storage_space[alpha.row * shape.lines + alpha.lines];
    }
    /*return transpose matrix*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::T()
    {
        Matrix<Data> temp({shape.lines, shape.row}, Data(0));
        for (int i = 0; i < shape.row; i++)
        {
            for (int j = 0; j < shape.lines; j++)
            {
                temp.storage_space[i * shape.lines + j] = storage_space[j * shape.row + i];
            }
        }
        return temp;
    }
    /*operator= Matrix*/
    template <typename Data>
    void Matrix<Data>::operator=(Matrix const &alpha)
    {
        shape = alpha.shape;
        storage_space = new Data[shape.row * shape.lines];
        for (int i = 0; i < shape.row * shape.lines; i++)
        {
            storage_space[i] = alpha.storage_space[i];
        }
        return;
    }
    /*operator= Data*/
    template <typename Data>
    void Matrix<Data>::operator=(Data const &alpha)
    {
        for (int i = 0; i < shape.row * shape.lines; i++)
        {
            storage_space[i] = alpha;
        }
        return;
    }
    /*operator+ Matrix*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator+(Matrix const &alpha)
    {
        if (!(shape == alpha.shape))
            return *this;
        Matrix<Data> temp(shape, Data(0));
        for (int i = 0; i < shape.row * shape.lines; i++)
        {
            temp.storage_space[i] = storage_space[i] + alpha.storage_space[i];
        }
        return temp;
    }
    /*operator+ Data*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator+(Data const &alpha)
    {
        Matrix<Data> temp(shape, storage_space);
        for (int i = 0; i < shape.row * shape.lines; i++)
        {
            temp.storage_space[i] += alpha;
        }
        return temp;
    }
    /*operator- Matrix*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator-(Matrix const &alpha)
    {
        if (!(shape == alpha.shape))
            return *this;
        Matrix<Data> temp(shape, Data(0));
        for (int i = 0; i < shape.row * shape.lines; i++)
        {
            temp.storage_space[i] -= alpha.storage_space[i];
        }
        return temp;
    }
    /*operator- Data*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator-(Data const &alpha)
    {
        Matrix<Data> temp(shape, storage_space);
        for (int i = 0; i < shape.row * shape.lines; i++)
        {
            temp.storage_space[i] -= alpha;
        }
        return temp;
    }
    /*operator* Matrix*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator*(Matrix const &alpha)
    {
        if (shape.lines != alpha.shape.row)
            return *this;
        int n = shape.lines;
        Data k = Data(0);
        Matrix<Data> temp({shape.row, alpha.shape.lines}, Data(0));
        for (int i = 0; i < temp.shape.row; i++)
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
    Matrix<Data> Matrix<Data>::operator*(Data const &alpha)
    {
        Matrix<Data> temp(shape, storage_space);
        for (int i = 0; i < shape.row * shape.lines; i++)
        {
            temp.storage_space[i] *= alpha;
        }
        return temp;
    }
    /*operator/ Data*/
    template <typename Data>
    Matrix<Data> Matrix<Data>::operator/(Data const &alpha)
    {
        Matrix<Data> temp(shape, storage_space);
        for (int i = 0; i < shape.row * shape.lines; i++)
        {
            temp.storage_space[i] /= alpha;
        }
        return temp;
    }
    /*add line*/
    template <typename Data>
    void Matrix<Data>::add_line_(Data const &alpha)
    {
        /////////////////////////////////////
    }
    /*operator+= Matrix*/

    // template <typename Data>
    // void Matrix<Data>::operator+=(Matrix const& alpha){
    //     if(!(this->shape==alpha.shape))
    //         return;
    //     for(int i=0;i<alpha.shape.row*alpha.shape.lines;i++)
    //         this->storage_space[i]+=alpha.storage_space[i];
    //     return;
    // }

    /*operator+= Data*/

    // template <typename Data>
    // void Matrix<Data>::operator+=(Data const&){
    //     for(int i=0;i<this->shape.row*this->shape.lines;i++){
    //         this->storage_space[i]+=alpha;
    //     }
    //     return;
    // }

    /*operator-= Matrix*/

    // template <typename Data>
    // void Matrix<Data>::operator-=(Matrix const& alpha){
    //     if(!(this->shape==alpha.shape))
    //         return;
    //     for(int i=0;i<alpha.shape.row*alpha.shape.lines;i++)
    //         this->storage_space[i]-=alpha.storage_space[i];
    //     return;
    // }

    /*operator-= Data*/

    // template <typename Data>
    // void Matrix<Data>::operator-=(Data const& alpha){
    //     for(int i=0;i<this->shape.row*this->shape.lines;i++){
    //         this->storage_space[i]-=alpha;
    //     }
    //     return;
    // }

    /*operator*= Matrix*/

    // template <typename Data>
    // void Matrix<Data>::operator*=(Matrix const& alpha){
    //     //////////////////////////////
    // }

    /*show Matrix*/
    template <typename Data>
    void show_Matrix(Matrix<Data> const &alpha)
    {
        for (int i = 0; i < alpha.shape.row; i++)
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
template class Linalg::Matrix<int>;
template class Linalg::Matrix<float>;
template class Linalg::Matrix<long long>;
template class Linalg::Matrix<double>;
template void Linalg::show_Matrix<int>(Linalg::Matrix<int> const &);
template void Linalg::show_Matrix<float>(Linalg::Matrix<float> const &);
template void Linalg::show_Matrix<long long>(Linalg::Matrix<long long> const &);
template void Linalg::show_Matrix<double>(Linalg::Matrix<double> const &);