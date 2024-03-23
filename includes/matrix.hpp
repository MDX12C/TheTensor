﻿#include <iostream>
#ifndef MATRIX_H
#define MATRIX_H
namespace Linalg
{
    typedef struct
    {
        int row;
        int lines;
    } MaShape;
    bool operator==(MaShape const &, MaShape const &);

    template <typename Data>
    class Matrix
    {
    private:
        Data *storage_space;
        MaShape shape;

        template <typename T>
        friend void show_Matrix(Matrix<T> const &);
    public:
        Matrix(MaShape const &, Data *const &);
        Matrix(MaShape const &, Data const &);
        ~Matrix();
        Data *item(MaShape const &);
        Matrix T();
        void operator=(Matrix const &);
        void operator=(Data const &);
        // void operator+=(Matrix const&);
        // void operator+=(Data const&);
        // void operator-=(Matrix const&);
        // void operator-=(Data const&);
        // void operator*=(Matrix const&);
        // void operator*=(Data const&);
        // void operator/=(Data const&);
        Matrix operator+(Matrix const &);
        Matrix operator+(Data const &);
        Matrix operator-(Matrix const &);
        Matrix operator-(Data const &);
        Matrix operator*(Matrix const &);
        Matrix operator*(Data const &);
        Matrix operator/(Data const &);
        void add_line_(Data const &);
    };
    template <typename Data>
    void show_Matrix(Matrix<Data> const &);
};

#endif