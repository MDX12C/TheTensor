#ifndef VECTOR_H
#define VECTOR_H
#include"./basic.hpp"
namespace Basic_Math {
    template <typename Data>
    Linalg::Vector<Data> random(int const&, Data const&, Data const&);
    template <typename Data>
    Linalg::Vector<Data> absolute(Linalg::Vector<Data> const&);
}
namespace Linalg
{
    template <typename Data>
    class Vector
    {
    private:
        Data* storage_space;
        int _shape;
        int _real_shape;
        template <typename T>
        friend std::ostream& operator<<(std::ostream&, Vector<T> const&);
        template <typename T>
        friend T dot(Vector<T> const&, Vector<T> const&);
        template <typename T>
        friend void AddLine_(Matrix<T>&, Vector<T> const&);
        template <typename T>
        friend void AddRow_(Matrix<T>&, Vector<T> const&);
        template <typename op_pls>
        Vector<op_pls> friend operator+(op_pls const&, Vector<op_pls> const&);
        template <typename op_mns>
        Vector<op_mns> friend operator-(op_mns const&, Vector<op_mns> const&);
        template <typename op_mul>
        Vector<op_mul> friend operator*(op_mul const&, Vector<op_mul> const&);
        template <typename op_div>
        Vector<op_div> friend operator/(op_div const&, Vector<op_div> const&);
        template <typename T>
        friend Vector<bool> operator==(T const&, Vector<T> const&);
        template <typename T>
        friend Vector<bool> operator!=(T const&, Vector<T> const&);
        template <typename T>
        friend Vector<bool> operator>(T const&, Vector<T> const&);
        template <typename T>
        friend Vector<bool> operator<(T const&, Vector<T> const&);
        template <typename T>
        friend Vector<bool> operator>=(T const&, Vector<T> const&);
        template <typename T>
        friend Vector<bool> operator<=(T const&, Vector<T> const&);
        friend class Linalg::Matrix<Data>;
        friend class Linalg::Tensor<Data>;
        template <typename T>
        friend class Linalg::Vector;
        template <typename T>
        friend Vector<T> Basic_Math::random(int const&, T const&, T const&);
        template <typename T>
        friend Vector<T> Basic_Math::absolute(Vector<T> const&);
    public:
        Vector(int const&, Data* const&);
        Vector(int const&);
        Vector();
        Vector(Vector const&);
        ~Vector();
        inline int size() { return this->_shape; }
        Data sum();
        void freedom_();
        bool endow_(int const&, Data const&);
        bool resize_(int const&);
        bool load_(int const&, Data* const&);
        Data& operator[](int const&);
        Vector& operator=(Vector const&);
        Vector& operator+=(Vector const&);
        Vector& operator-=(Vector const&);
        Vector& operator*=(Vector const&);
        Vector& operator/=(Vector const&);
        Vector operator+(Vector const&);
        Vector operator-(Vector const&);
        Vector operator*(Vector const&);
        Vector operator/(Vector const&);
        Vector& operator=(Data const&);
        Vector& operator+=(Data const&);
        Vector& operator-=(Data const&);
        Vector& operator*=(Data const&);
        Vector& operator/=(Data const&);
        Vector operator+(Data const&);
        Vector operator-(Data const&);
        Vector operator*(Data const&);
        Vector operator/(Data const&);
        Vector<bool> operator==(Vector const&);
        Vector<bool> operator<(Vector const&);
        Vector<bool> operator<=(Vector const&);
        Vector<bool> operator>(Vector const&);
        Vector<bool> operator>=(Vector const&);
        Vector<bool> operator!=(Vector const&);
        Vector<bool> operator==(Data const&);
        Vector<bool> operator<(Data const&);
        Vector<bool> operator<=(Data const&);
        Vector<bool> operator>(Data const&);
        Vector<bool> operator>=(Data const&);
        Vector<bool> operator!=(Data const&);
    };
    template <typename Data>
    std::ostream& operator<<(std::ostream&, Vector<Data> const&);
    template <typename Data>
    Data dot(Vector<Data> const&, Vector<Data> const&);
    template <typename op_pls>
    Vector<op_pls> operator+(op_pls const&, Vector<op_pls> const&);
    template <typename op_mns>
    Vector<op_mns> operator-(op_mns const&, Vector<op_mns> const&);
    template <typename op_mul>
    Vector<op_mul> operator*(op_mul const&, Vector<op_mul> const&);
    template <typename op_div>
    Vector<op_div> operator/(op_div const&, Vector<op_div> const&);
    template <typename Data>
    Vector<bool> operator==(Data const&, Vector<Data> const&);
    template <typename Data>
    Vector<bool> operator<(Data const&, Vector<Data> const&);
    template <typename Data>
    Vector<bool> operator<=(Data const&, Vector<Data> const&);
    template <typename Data>
    Vector<bool> operator>(Data const&, Vector<Data> const&);
    template <typename Data>
    Vector<bool> operator>=(Data const&, Vector<Data> const&);
    template <typename Data>
    Vector<bool> operator!=(Data const&, Vector<Data> const&);
}
#endif //BASIC_H