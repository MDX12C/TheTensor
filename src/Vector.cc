#include"../includes/vector.hpp"
namespace Linalg{
    /*constructor with datas
    Enter: 1.size 2.datas array
    declare a vector and array into it
    no return*/
    template <typename Data>
    Vector<Data>::Vector(int const& alpha, Data* const& beta){
        if(alpha<=0){
            this->_shape = 1;
            this->storage_space = new Data[1];
            this->storage_space[0] = static_cast<Data>(0);
            return;
        }
        this->_shape = alpha;
        this->storage_space = new Data[alpha];
        for (int i=0;i<alpha;i++)
            this->storage_space[i] = beta[i];
        return;
    }
    /*constructor with value
    Enter: 1.size 2.value
    declare a vector filled with value
    no reture*/
    template <typename Data>
    Vector<Data>::Vector(int const& alpha, Data const& beta){
        if(alpha<=0){
            this->_shape = 1;
            this->storage_space = new Data[1];
            this->storage_space[0] = beta;
            return;
        }
        this->_shape = alpha;
        this->storage_space = new Data[alpha];
        for (int i=0;i<alpha;i++)
            this->storage_space[i] = beta;
        return;
    }
    /*constructor only size
    Enter: 1.size
    declare a vector filled with 0
    no return*/
    template <typename Data>
    Vector<Data>::Vector(int const& alpha){
        if(alpha<=0){
            this->_shape = 1;
            this->storage_space = new Data[1];
            this->storage_space[0] = static_cast<Data>(0);
            return;
        }
        this->_shape = alpha;
        this->storage_space = new Data[alpha];
        for (int i=0;i<alpha;i++)
            this->storage_space[i] = static_cast<Data>(0);
        return;
    }
    /*defult constructor
    Enter: none
    declare a vector of size 1 filled with 0
    no return*/
    template <typename Data>
    Vector<Data>::Vector(){
        this->_shape = 1;
        this->storage_space = new Data[1];
        this->storage_space[0] = static_cast<Data>(0);
        return;
    }
    /*copy constructor
    Enter: 1.vector
    declare a vector with same datas
    no return*/
    template <typename Data>
    Vector<Data>::Vector(Vector<Data> const& alpha){
        this->_shape = alpha._shape;
        this->storage_space = new Data[this->_shape];
        for (int i=0;i<this->_shape;i++)
            this->storage_space[i] = alpha.storage_space[i];
        return;
    }
    /*destructor
    Enter: none
    delete vector
    no return*/
    template <typename Data>
    Vector<Data>::~Vector(){
        if (this->_shape)
            delete[] storage_space;
        return;
    }
    /*endow
    Enter: 1.coordinate 2.value
    endow the value at the coordinate
    no return*/
    template <typename Data>
    void Vector<Data>::endow_(int const& alpha, Data const& beta){
        if(alpha < 0 || alpha >= this->_shape)
            return;
        this->storage_space[alpha] = beta;
        return;
    }
    /*resize
    Enter: 1.new size
    resize the vector. the beyond data will be deleted
    no return*/
    template <typename Data>
    void Vector<Data>::resize_(int const& alpha){
        if(alpha <= 0)
            return;
        if(alpha == this->_shape)
            return;
        Vector<Data> temp=*this;
        if(this->_shape)
            delete[] this->storage_space;
        this->_shape = alpha;
        this->storage_space = new Data[this->_shape];
        for (int i=0;i<this->_shape;i++){
            if(i<temp._shape)
                this->storage_space[i] = temp.storage_space[i];
            else
                this->storage_space[i] = static_cast<Data>(0);
        }
        return;
    }
    /*operator[]
    Enter: 1.coordinate
    do nothing
    return the data in the coordinate*/
    template <typename Data>
    Data& Vector<Data>::operator[](int const& alpha){
        if(alpha < 0 || alpha >= this->_shape)
            return static_cast<Data>(0);
        return this->storage_space[alpha];
    }
    /*operator= Vector
    Enter: 1.vector 2.vector
    copy the second vector into the first one
    no return*/
    template <typename Data>
    void Vector<Data>::operator=(Vector<Data> const& alpha){
        if(this->_shape)
            delete[] this->storage_space;
        this->_shape = alpha._shape;
        this->storage_space = new Data[this->_shape];
        for (int i=0;i<this->_shape;i++)
            this->storage_space[i] = alpha.storage_space[i];
        return;
    }
    /*operator= value
    Enter: 1.vector 2.value
    copy the value into the vector
    no return*/
    template <typename Data>
    void Vector<Data>::operator=(Data const& alpha){
        for (int i=0;i<this->_shape;i++)
            this->storage_space[i] = alpha;
        return;
    }
    /*operator+ Vector
    Enter: 1.vector 2.vector
    add the two vector 
    return the result*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator+(Vector<Data> const& alpha){
        if(this->_shape != alpha._shape)
            return *this;
        Vector<Data> temp(*this);
        for (int i=0;i<this->_shape;i++)
            temp.storage_space[i] += alpha.storage_space[i];
        return temp;
    }
    /*operator+ value
    Enter: 1.vector 2.value
    add the vector and the value
    return the result*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator+(Data const& alpha){
        Vector<Data> temp(*this);
        for (int i=0;i<this->_shape;i++)
            temp.storage_space[i] += alpha;
        return temp;
    }
    /*operator- Vector
    Enter: 1.vector 2.vector
    subtract the first vector from the second
    return the result*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator-(Vector<Data> const& alpha){
        if(this->_shape != alpha._shape)
            return *this;
        Vector<Data> temp(*this);
        for (int i=0;i<this->_shape;i++)
            temp.storage_space[i] -= alpha.storage_space[i];
        return temp;
    }
    /*operator- vlaue
    Enter: 1.vector 2.value
    subtract the value from the vector
    return the result*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator-(Data const& alpha){
        Vector<Data> temp(*this);
        for (int i=0;i<this->_shape;i++)
            temp.storage_space[i] -= alpha;
        return temp;
    }
    /*operator* Vector
    Enter: 1.vector 2.vector
    multiply every element in the two vector
    return the result*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator*(Vector<Data> const& alpha){
        if(this->_shape != alpha._shape)
            return *this;
        Vector<Data> temp(*this);
        for (int i=0;i<this->_shape;i++)
            temp.storage_space[i] *= alpha.storage_space[i];
        return temp;
    }
    /*operator* value
    Enter: 1.vector 2.value
    multiply every element in the vector and the value
    return the result*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator*(Data const& alpha){
        Vector<Data> temp(*this);
        for (int i=0;i<this->_shape;i++)
            temp.storage_space[i] *= alpha;
        return temp;
    }
    /*operator/ Vector
    Enter: 1.vector 2.vector
    divide every element in the first vector by the second vector
    return the result*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator/(Vector<Data> const& alpha){
        if(this->_shape != alpha._shape)
            return *this;
        Vector<Data> temp(*this);
        for (int i=0;i<this->_shape;i++)
            temp.storage_space[i] /= alpha.storage_space[i];
        return temp;
    }
    /*operator/ value
    Enter: 1.vector 2.value
    divide every element in the vector by the value
    return the result*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator/(Data const& alpha){
        Vector<Data> temp(*this);
        for (int i=0;i<this->_shape;i++)
            temp.storage_space[i] /= alpha;
        return temp;
    }
    /*operator+= vector
    Enter: 1.vector 2.vector
    add the second vector into the first one
    no return*/
    template <typename Data>
    void Vector<Data>::operator+=(Vector<Data> const& alpha){
        if(this->_shape != alpha._shape)
            return;
        for (int i=0;i<this->_shape;i++)
            this->storage_space[i] += alpha.storage_space[i];
        return;
    }
    /*operator+= value
    Enter: 1.vector 2.value
    add the value into the vector
    no return*/
    template <typename Data>
    void Vector<Data>::operator+=(Data const& alpha){
        for (int i=0;i<this->_shape;i++)
            this->storage_space[i] += alpha;
        return;
    }
    /*operator-= vector
    Enter: 1.vector 2.vector
    subtract the second vector from the first one
    no return*/
    template <typename Data>
    void Vector<Data>::operator-=(Vector<Data> const& alpha){
        if(this->_shape != alpha._shape)
            return;
        for (int i=0;i<this->_shape;i++)
            this->storage_space[i] -= alpha.storage_space[i];
        return;
    }
    /*operator-= value
    Enter: 1.vector 2.value
    subtract the value from the vector
    no return*/
    template <typename Data>
    void Vector<Data>::operator-=(Data const& alpha){
        for (int i=0;i<this->_shape;i++)
            this->storage_space[i] -= alpha;
        return;
    }
    /*operator*= vector
    Enter: 1.vector 2.vector
    multiply every element in the second vector into the first one
    no return*/
    template <typename Data>
    void Vector<Data>::operator*=(Vector<Data> const& alpha){
        if(this->_shape != alpha._shape)
            return;
        for (int i=0;i<this->_shape;i++)
            this->storage_space[i] *= alpha.storage_space[i];
        return;
    }
    /*operator*= value
    Enter: 1.vector 2.value
    multiply every element in the vector with the value
    no return*/
    template <typename Data>
    void Vector<Data>::operator*=(Data const& alpha){
        for (int i=0;i<this->_shape;i++)
            this->storage_space[i] *= alpha;
        return;
    }
    /*operator/= vector
    Enter: 1.vector 2.vector
    divide every element in the first vector by the second vector
    no return*/
    template <typename Data>
    void Vector<Data>::operator/=(Vector<Data> const& alpha){
        if(this->_shape != alpha._shape)
            return;
        for (int i=0;i<this->_shape;i++)
            this->storage_space[i] /= alpha.storage_space[i];
        return;
    }
    /*operator/= value
    Enter: 1.vector 2.value
    divide every element in the vector by the value
    no return*/
    template <typename Data>
    void Vector<Data>::operator/=(Data const& alpha){
        for (int i=0;i<this->_shape;i++)
            this->storage_space[i] /= alpha;
        return;
    }
    /*freedom 
    Enter: none
    free the space of the vector and set the shape to 1
    no return*/
    template <typename Data>
    void Vector<Data>::freedom_(){
        delete[] this->storage_space;
        this->_shape = 1;
        this->storage_space = new Data[1];
        this->storage_space[0] = static_cast<Data>(0);
        return;
    }
    /*operator<<
    Enter: 1.ostream 2.vector
    print every element in the vector
    return the ostream*/
    template <typename Data>
    std::ostream& operator<<(std::ostream& beta, Vector<Data> const& alpha){
        beta<<"size: "<<alpha._shape<<'\n';
        for (int i=0;i<alpha._shape;i++){
            beta<<alpha.storage_space[i];
            if(i!=alpha._shape-1)
                beta<<' ';
        }
        beta<<'\n';
        return beta;
    }
    /*dot
    Enter: 1.vector 2.vector
    dot every element in the vector
    return the result*/
    template <typename Data>
    Data dot(Vector<Data> const& beta, Vector<Data> const& alpha){
        if (beta._shape != alpha._shape)
            return static_cast<Data>(0);
        Data gamma = static_cast<Data>(0);
        for (int i=0;i<beta._shape;i++)
            gamma += beta.storage_space[i] * alpha.storage_space[i];
        return gamma;
    }
}
template class Linalg::Vector<int32_t>;
template class Linalg::Vector<_Float32>;
template class Linalg::Vector<bool>;
template std::ostream& Linalg::operator<<(std::ostream&, Linalg::Vector<int32_t> const&);
template std::ostream& Linalg::operator<<(std::ostream&, Linalg::Vector<_Float32> const&);
template std::ostream& Linalg::operator<<(std::ostream&, Linalg::Vector<bool> const&);
template int32_t Linalg::dot(Linalg::Vector<int32_t> const&, Linalg::Vector<int32_t> const&);
template _Float32 Linalg::dot(Linalg::Vector<_Float32> const&, Linalg::Vector<_Float32> const&);
template bool Linalg::dot(Linalg::Vector<bool> const&, Linalg::Vector<bool> const&);