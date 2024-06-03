#ifndef MATRIX_H
#define MATRIX_H
#include"./vector.hpp"
namespace Basic_Math {
    template <typename Data>
    Linalg::Matrix<Data> random(Linalg::MaShape const&, Data const&, Data const&);
    template <typename Data>
    Linalg::Matrix<Data> absolute(Linalg::Vector<Data> const&);
}
namespace Linalg
{
    template <typename Data>
    class Matrix
    {
    private:
        Data* storage_space;
        MaShape _shape;
        MaShape _real_shape;
        int _size;
        int _real_size;

        template <typename T>
        friend std::ostream& operator<<(std::ostream&, Matrix<T> const&);
        template <typename T>
        friend Matrix<T> dot(Matrix<T> const&, Matrix<T> const&);
        template <typename T>
        friend void AddLine_(Matrix<T>&, Vector<T> const&);
        template <typename T>
        friend void AddRow_(Matrix<T>&, Vector<T> const&);

        friend class Linalg::Vector<Data>;
        friend class Linalg::Tensor<Data>;
        template <typename T>
        friend class Linalg::Matrix;

        template<typename T>
        friend Matrix<T> operator+(T const&, Matrix<T> const&);
        template<typename T>
        friend Matrix<T> operator-(T const&, Matrix<T> const&);
        template<typename T>
        friend Matrix<T> operator*(T const&, Matrix<T> const&);
        template<typename T>
        friend Matrix<T> operator/(T const&, Matrix<T> const&);

        template<typename T>
        friend Matrix<bool> operator==(T const&, Matrix<T> const&);
        template<typename T>
        friend Matrix<bool> operator!=(T const&, Matrix<T> const&);
        template<typename T>
        friend Matrix<bool> operator>=(T const&, Matrix<T> const&);
        template<typename T>
        friend Matrix<bool> operator<=(T const&, Matrix<T> const&);
        template<typename T>
        friend Matrix<bool> operator>(T const&, Matrix<T> const&);
        template<typename T>
        friend Matrix<bool> operator<(T const&, Matrix<T> const&);

        template <typename T>
        friend Matrix<T> Basic_Math::random(Linalg::MaShape const&, T const&, T const&);
        template <typename T>
        friend Matrix<T> Basic_Math::absolute(Matrix<T> const&);
    public:
        Matrix(MaShape const&, Data* const&);
        Matrix(MaShape const&);
        Matrix();
        Matrix(const Matrix&);
        ~Matrix();

        Matrix T();
        inline MaShape shape() { return this->_shape; }
        inline int size() { return this->_size; }
        void freedom_();
        bool endow_(MaShape const&, Data const&);
        bool resize_(MaShape const&);
        bool reshape_(MaShape const&);
        Data sum();
        Vector<Data> flat();
        bool load_(MaShape const&, Data* const&);
        bool stand_(Vector<Data> const&, MaShape const&);

        Data& operator[](MaShape const&);
        Matrix& operator=(Matrix const&);
        Matrix& operator+=(Matrix const&);
        Matrix& operator-=(Matrix const&);
        Matrix& operator*=(Matrix const&);
        Matrix& operator/=(Matrix const&);

        Matrix operator+(Matrix const&);
        Matrix operator-(Matrix const&);
        Matrix operator*(Matrix const&);
        Matrix operator/(Matrix const&);

        Matrix<bool> operator==(Matrix const&);
        Matrix<bool> operator!=(Matrix const&);
        Matrix<bool> operator>=(Matrix const&);
        Matrix<bool> operator<=(Matrix const&);
        Matrix<bool> operator>(Matrix const&);
        Matrix<bool> operator<(Matrix const&);

        Matrix& operator=(Data const&);
        Matrix& operator+=(Data const&);
        Matrix& operator-=(Data const&);
        Matrix& operator*=(Data const&);
        Matrix& operator/=(Data const&);

        Matrix operator+(Data const&);
        Matrix operator-(Data const&);
        Matrix operator*(Data const&);
        Matrix operator/(Data const&);

        Matrix<bool> operator==(Data const&);
        Matrix<bool> operator!=(Data const&);
        Matrix<bool> operator>=(Data const&);
        Matrix<bool> operator<=(Data const&);
        Matrix<bool> operator>(Data const&);
        Matrix<bool> operator<(Data const&);
    };

    template<typename T>
    Matrix<T> operator+(T const&, Matrix<T> const&);
    template<typename T>
    Matrix<T> operator-(T const&, Matrix<T> const&);
    template<typename T>
    Matrix<T> operator*(T const&, Matrix<T> const&);
    template<typename T>
    Matrix<T> operator/(T const&, Matrix<T> const&);

    template<typename T>
    Matrix<bool> operator==(T const&, Matrix<T> const&);
    template<typename T>
    Matrix<bool> operator!=(T const&, Matrix<T> const&);
    template<typename T>
    Matrix<bool> operator>=(T const&, Matrix<T> const&);
    template<typename T>
    Matrix<bool> operator<=(T const&, Matrix<T> const&);
    template<typename T>
    Matrix<bool> operator>(T const&, Matrix<T> const&);
    template<typename T>
    Matrix<bool> operator<(T const&, Matrix<T> const&);
    template <typename Data>
    std::ostream& operator<<(std::ostream&, Matrix<Data> const&);
    template <typename Data>
    Matrix<Data> dot(Matrix<Data> const&, Matrix<Data> const&);
}

#endif