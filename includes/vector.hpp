#ifndef VECTOR_H
#define VECTOR_H
#include"./basic.hpp"
namespace Linalg
{
    template <typename Data>
    class Vector
    {
    private:
        Data* storage_space;
        Data _sum;
        int _shape;
        int _digits;
        template <typename T>
        friend std::ostream& operator<<(std::ostream&, Vector<T> const&);
        template <typename T>
        friend T dot(Vector<T> const&, Vector<T> const&);
        template <typename T>
        friend void AddLine_(Matrix<T>&, Vector<T> const&);
        template <typename T>
        friend void AddRow_(Matrix<T>&, Vector<T> const&);
        friend class Linalg::Matrix<Data>;
        friend class Linalg::Tensor<Data>;
    public:
        Vector(int const&, Data* const&);
        Vector(int const&);
        Vector();
        Vector(Vector const&);
        ~Vector();
        inline int size() { return this->_shape; }
        inline Data sum() { return this->_sum; }
        inline int digits() { return this->_digits; }
        void freedom_();
        bool endow_(int const&, Data const&);
        bool resize_(int const&);
        Data operator[](int const&);
        Vector operator=(Vector const&);
        Vector operator=(Data const&);
        Vector operator+=(Vector const&);
        Vector operator+=(Data const&);
        Vector operator-=(Vector const&);
        Vector operator-=(Data const&);
        Vector operator*=(Vector const&);
        Vector operator*=(Data const&);
        Vector operator/=(Vector const&);
        Vector operator/=(Data const&);
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