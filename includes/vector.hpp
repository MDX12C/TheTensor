#include"./basic.hpp"
#include<iostream>
#include<float.h>
#include<iomanip>
#ifndef VECTOR_H
#define VECTOR_H
namespace Linalg
{
    template <typename Data>
    class Vector
    {
    private:
        Data *storage_space;
        int _shape;
        template <typename T>
        friend std::ostream &operator<<(std::ostream &, Vector<T> const &);
        template <typename T>
        friend T dot(Vector<T> const &, Vector<T> const &);
    public:
        Vector(int const&, Data* const&);
        Vector(int const&, Data const&);
        Vector(int const&);
        Vector();
        Vector(Vector const&);
        ~Vector();
        void freedom_();
        inline int size() { return this->_shape; }
        void endow_(int const&, Data const&);
        void resize_(int const&);
        Data& operator[](int const&);
        void operator=(Vector const&);
        void operator=(Data const&);
        void operator+=(Vector const&);
        void operator+=(Data const&);
        void operator-=(Vector const&);
        void operator-=(Data const&);
        void operator*=(Vector const&);
        void operator*=(Data const&);
        void operator/=(Vector const&);
        void operator/=(Data const&);
        Vector operator+(Vector const&);
        Vector operator+(Data const&);
        Vector operator-(Vector const&);
        Vector operator-(Data const&);
        Vector operator*(Vector const&);
        Vector operator*(Data const&);
        Vector operator/(Vector const&);
        Vector operator/(Data const&);
    };
    template <typename Data>
    std::ostream& operator<<(std::ostream&, Vector<Data> const&);
    template <typename Data>
    Data dot(Vector<Data> const&, Vector<Data> const&);
}
#endif