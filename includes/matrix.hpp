#include <iostream>
#ifndef MATRIX_H
#define MATRIX_H
namespace Linalg
{
    typedef struct
    {
        int rows = 1;
        int lines = 1;
    } MaShape;
    bool operator==(MaShape const&, MaShape const&);
    bool belongs(MaShape const&, MaShape const&);
    std::ostream& operator<<(std::ostream&, MaShape const&);
    std::istream& operator>>(std::istream&, MaShape&);
    template <typename Data>
    class Matrix
    {
    private:
        Data* storage_space;
        MaShape shape;

        template <typename PLUS>
        friend Matrix<PLUS> operator+(PLUS const&, Matrix<PLUS> const&);
        template <typename MINUS>
        friend Matrix<MINUS> operator-(MINUS const&, Matrix<MINUS> const&);
        template <typename MULTI>
        friend Matrix<MULTI> operator*(MULTI const&, Matrix<MULTI> const&);
        template <typename DIV>
        friend Matrix<DIV> operator/(DIV const&, Matrix<DIV> const&);
        template <typename W>
        friend std::ostream& operator<<(std::ostream&, Matrix<W> const&);
        template <typename C>
        friend std::istream& operator>>(std::istream&, Matrix<C>&);
        template <typename T>
        friend Matrix<T> dot(Matrix<T> const&, Matrix<T> const&);
    public:
        Matrix(MaShape const&, Data* const&);
        Matrix(MaShape const&, Data const&);
        Matrix(MaShape const&);
        Matrix();
        Matrix(const Matrix&);
        ~Matrix();
        Matrix T();
        inline MaShape size() { return this->shape; }
        void endow_(MaShape const&, Data const&);
        void resize_(MaShape const&);
        void reshape_(MaShape const&);
        Data operator[](MaShape const&);
        void operator=(Matrix const&);
        void operator=(Data const&);
        void operator+=(Matrix const&);
        void operator+=(Data const&);
        void operator-=(Matrix const&);
        void operator-=(Data const&);
        void operator*=(Matrix const&);
        void operator*=(Data const&);
        void operator/=(Data const&);
        void operator/=(Matrix const&);
        Matrix operator+(Matrix const&);
        Matrix operator+(Data const&);
        Matrix operator-(Matrix const&);
        Matrix operator-(Data const&);
        Matrix operator*(Matrix const&);
        Matrix operator*(Data const&);
        Matrix operator/(Matrix const&);
        Matrix operator/(Data const&);
    };
    template <typename Data>
    Matrix<Data> operator+(Data const&, Matrix<Data> const&);
    template <typename Data>
    Matrix<Data> operator-(Data const&, Matrix<Data> const&);
    template <typename Data>
    Matrix<Data> operator*(Data const&, Matrix<Data> const&);
    template <typename Data>
    Matrix<Data> operator/(Data const&, Matrix<Data> const&);
    template <typename Data>
    std::ostream& operator<<(std::ostream&, Matrix<Data> const&);
    template <typename Data>
    std::istream& operator>>(std::istream&, Matrix<Data>&);
    template <typename Data>
    Matrix<Data> dot(Matrix<Data> const&, Matrix<Data> const&);
};
#endif