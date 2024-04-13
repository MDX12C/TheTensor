﻿#include"./vector.hpp"
#include <iostream>
#include<float.h>
#include<iomanip>
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
    template <typename Data>
    class Matrix
    {
    private:
        Data* storage_space;
        MaShape _shape;

        template <typename T>
        friend std::ostream& operator<<(std::ostream&, Matrix<T> const&);
        template <typename T>
        friend Matrix<T> dot(Matrix<T> const&, Matrix<T> const&);
        template <typename T>
        friend void AddLine_(Matrix<T>&, Vector<T> const&);
        template <typename T>
        friend void AddRow_(Matrix<T>&, Vector<T> const&);
    public:
        Matrix(MaShape const&, Data* const&);
        Matrix(MaShape const&, Data const&);
        Matrix(MaShape const&);
        Matrix();
        Matrix(const Matrix&);
        ~Matrix();
        Matrix T();
        inline MaShape shape() { return this->_shape; }
        void freedom_();
        void endow_(MaShape const&, Data const&);
        void resize_(MaShape const&);
        void reshape_(MaShape const&);
        Data& operator[](MaShape const&);
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
    std::ostream& operator<<(std::ostream&, Matrix<Data> const&);
    template <typename Data>
    Matrix<Data> dot(Matrix<Data> const&, Matrix<Data> const&);
    template <typename Data>
    void AddLine_(Matrix<Data>&, Vector<Data> const&);
    template <typename Data>
    void AddRow_(Matrix<Data>&, Vector<Data> const&);
};
#endif