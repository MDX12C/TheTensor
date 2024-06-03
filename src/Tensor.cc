#include"../includes/tensor.hpp"
#define bsm Basic_Math
namespace Linalg {
    /*constructor with Dimansion
    Enter: 1.Dimansion
    construct a Teshape with the Dimansion but the shape is 1
    no return*/
    Teshape::Teshape(int const& alpha) {
        this->_dimansion = alpha > 0 ? alpha : 1;
        this->_size = 1;
        this->shape = new int[this->_dimansion];
        for (int i = 0; i < this->_dimansion; i++)
            this->shape[i] = 1;
        return;
    }
    /*constructor with inited shape
    Enter: 1.Dimansion 2.inited shape array
    construct a Teshape with the Dimansion and the inited shape
    no return*/
    Teshape::Teshape(int const& alpha, int* const& beta) {
        this->_dimansion = alpha > 0 ? alpha : 1;
        this->shape = new int[this->_dimansion];
        this->_size = 1;
        for (int i = 0; i < this->_dimansion; i++) {
            this->shape[i] = beta[i] > 0 ? beta[i] : 1;
            this->_size *= this->shape[i];
        }
        return;
    }
    /*copy constructor
    Enter: 1.Teshape
    copy the Teshape
    no return*/
    Teshape::Teshape(Teshape const& alpha) {
        this->_dimansion = alpha._dimansion;
        this->_size = alpha._size;
        this->shape = new int[this->_dimansion];
        for (int i = 0; i < this->_dimansion; i++)
            this->shape[i] = alpha.shape[i];
        return;
    }
    /*defult constructor
    Enter: none
    construct a Teshape with the Dimansion is 1 and the shape is 1
    no return*/
    Teshape::Teshape() {
        this->_dimansion = 1;
        this->_size = 1;
        this->shape = new int[1];
        this->shape[0] = 1;
        return;
    }
    /*destructor
    Enter: none
    destruct the Teshape
    no return*/
    Teshape::~Teshape() {
        delete[] this->shape;
        return;
    }
    /*endow    Warning!!!
    Enter: 1.coordinate 2.value
    endow the value at the coordinate
    return if endow is successful*/
    bool Teshape::endow_(int const& alpha, int const& beta) {
        if (alpha < 0 || alpha >= this->_dimansion)
            return false;
        this->_size /= this->shape[alpha];
        this->shape[alpha] = beta > 0 ? beta : 1;
        this->_size *= this->shape[alpha];
        return true;
    }
    /*operator[]
    Enter: 1.coordinate
    do nothing
    return the data in the coordinate*/
    int Teshape::operator[](int const& alpha) {
        if (alpha < 0 || alpha >= this->_dimansion)
            return 0;
        return this->shape[alpha];
    }
    /*operator=
    Enter: 1.Teshape
    copy the Teshape
    return this*/
    Teshape Teshape::operator=(Teshape const& alpha) {
        if (this->_dimansion)
            delete[] this->shape;
        this->_dimansion = alpha._dimansion;
        this->_size = alpha._size;
        this->shape = new int[this->_dimansion];
        for (int i = 0; i < this->_dimansion; i++)
            this->shape[i] = alpha.shape[i];
        return (*this);
    }
    /*operator==
    Enter: 1.Teshape 2.Teshape
    compare the Teshape
    return true if they are equal*/
    bool Teshape::operator==(Teshape const& alpha) {
        if (this->_dimansion != alpha._dimansion)
            return false;
        for (int i = 0; i < this->_dimansion; i++)
            if (this->shape[i] != alpha.shape[i])
                return false;
        return true;
    }
    /*reshape
    Enter: 1.Teshape
    reshape this through the Teshape
    return true if the shape is reshaped*/
    bool Teshape::reshape_(Teshape const& alpha) {
        if (this->_size != alpha._size)
            return false;
        if ((*this) == alpha)
            return true;
        if (this->_dimansion)
            delete[] this->shape;
        this->_dimansion = alpha._dimansion;
        this->shape = new int[this->_dimansion];
        for (int i = 0; i < this->_dimansion; i++)
            this->shape[i] = alpha.shape[i];
        return true;
    }
    /*freedom
    Enter: none
    free the space of the Teshape and set the shape to 1
    no return*/
    void Teshape::freedom_() {
        delete[] this->shape;
        this->_dimansion = 1;
        this->_size = 1;
        this->shape = new int[1];
        this->shape[0] = 1;
        return;
    }
    /*coordinate
    Enter: 1.coordinate
    count the steps of the coordinate
    return the steps*/
    int Teshape::coordinate(Teshape const& alpha) {
        if (belongs(alpha, (*this)))
            return 0;
        int temp = 0;
        for (int i = 0; i < this->_dimansion - 1; i++) {
            temp += alpha.shape[i];
            temp *= this->shape[i + 1];
        }
        temp += this->shape[this->_dimansion - 1];
        return temp;
    }
    /*coordinate
    Enter: 1.sequence
    count the coordinate of the sequence
    return the coordinate*/
    Teshape Teshape::coordinate(int const& alpha) {
        Teshape temp(this->_dimansion);
        for (int i = 0; i < this->_dimansion; i++)
            temp.shape[i] = 0;
        if (alpha < 0 || alpha >= this->_size)
            return temp;
        int gamma = alpha;
        for (int i = this->_dimansion - 1; i >= 0; i--) {
            temp.shape[i] = gamma % this->shape[i];
            gamma /= this->shape[i];
            if (gamma == 0)
                break;
        }
        return temp;
    }
    /*operator>>
    Enter: 1.istream 2.Teshape
    read the Teshape from the istream
    return the istream*/
    std::istream& operator>>(std::istream& alpha, Teshape& beta) {
        int gamma;
        if (beta._dimansion)
            delete[] beta.shape;
        alpha >> gamma;
        beta._dimansion = gamma > 0 ? gamma : 1;
        beta._size = 1;
        beta.shape = new int[beta._dimansion];
        for (int i = 0; i < beta._dimansion; i++) {
            alpha >> gamma;
            beta.shape[i] = gamma > 0 ? gamma : 1;
            beta._size *= beta.shape[i];
        }
        return alpha;
    }
    /*operator<<
    Enter: 1.ostream 2.Teshape
    print the Teshape in the ostream
    return the ostream*/
    std::ostream& operator<<(std::ostream& alpha, Teshape const& beta) {
        alpha << beta._dimansion << " : ";
        for (int i = 0; i < beta._dimansion; i++) {
            alpha << beta.shape[i] << ' ';
        }
        alpha << "= " << beta._size << '\n';
        return alpha;
    }
    /*belongs
    Enter: 1.coordinate 2.Teshape
    check if the coordinate is in the Teshape
    return true if it is*/
    bool belongs(Teshape const& alpha, Teshape const& beta) {
        if (alpha._dimansion != beta._dimansion)
            return false;
        for (int i = 0; i < alpha._dimansion; i++) {
            if ((alpha.shape[i] < 0) || (alpha.shape[i] >= beta.shape[i]))
                return false;
        }
        return true;
    }
    /*Constructor Datas
    Enter: 1.Teshape 2.Data pointer
    construct a Tensor with inited Datas
    no return*/
    template <typename Data>
    Tensor<Data>::Tensor(Teshape const& alpha, Data* const& beta) {
        this->_shape = alpha;
        int gamma = this->_shape._size;
        this->storage_space = new Data[gamma];
        for (int zeta = 0; zeta < gamma; zeta++) {
            this->storage_space[zeta] = beta[zeta];
        }
        return;
    }
    /*constructor Teshape
    Enter: 1.Teshape
    constructor a Tensor with the shape and fill with 0
    no return*/
    template <typename Data>
    Tensor<Data>::Tensor(Teshape const& alpha) {
        this->_shape = alpha;
        int gamma = this->_shape._size;
        this->storage_space = new Data[gamma];
        for (int zeta = 0; zeta < gamma; zeta++) {
            this->storage_space[zeta] = static_cast<Data>(0);
        }
        return;
    }
    /*default constructor
    Enter: none
    construct a Tensor with shape 1 and fill with 0
    no return*/
    template <typename Data>
    Tensor<Data>::Tensor() {
        this->_shape.freedom_();
        this->storage_space = new Data[1];
        this->storage_space[0] = static_cast<Data>(0);
        return;
    }
    /*copy constructor
    Enter: 1.Tensor
    construct a Tensor from another Tensor
    no return*/
    template <typename Data>
    Tensor<Data>::Tensor(Tensor<Data> const& alpha) {
        if (this->_shape._size)
            delete[] this->storage_space;
        this->_shape = alpha._shape;
        int gamma = this->_shape._size;
        this->storage_space = new Data[gamma];
        for (int zeta = 0; zeta < gamma; zeta++) {
            this->storage_space[zeta] = alpha.storage_space[zeta];
        }
        return;
    }
    /*destructor
    Enter: none
    destruct the Tensor
    no return*/
    template <typename Data>
    Tensor<Data>::~Tensor() {
        if (this->_shape._size)
            delete[] this->storage_space;
        return;
    }
    /*freedom
    Enter: none
    free all the space of the Tensor and init the Tensor with shape 1
    no return*/
    template <typename Data>
    void Tensor<Data>::freedom_() {
        if (this->_shape._size)
            delete[] this->storage_space;
        this->_shape.freedom_();
        this->storage_space = new Data[1];
        this->storage_space[0] = static_cast<Data>(0);
        return;
    }
    /*endow
    Enter: 1.coordinate 2.value
    endow the value at the coordinate
    return if endow is successful*/
    template <typename Data>
    bool Tensor<Data>::endow_(Teshape const& alpha, Data const& beta) {
        if (!(belongs(alpha, this->_shape)))
            return false;
        this->storage_space[this->_shape.coordinate(alpha)] = beta;
        return true;
    }
    /*resize
    Enter: 1.Teshape
    resize the Tensor，the beyond data will be fill with 0
    return if resize successfully*/
    template <typename Data>
    bool Tensor<Data>::resize_(Teshape const& alpha) {
        if (this->_shape._dimansion != alpha._dimansion)
            return false;
        Tensor<Data> temp(*this);
        Data gamma = static_cast<Data>(0);
        delete[] this->storage_space;
        this->_shape = alpha;
        Teshape omega(this->_shape._dimansion);
        this->storage_space = new Data[this->_shape._size];
        for (int i = 0; i < this->_shape._size; i++) {
            omega = this->_shape.coordinate(i);
            if (belongs(omega, temp._shape)) {
                this->storage_space[i] = temp[omega];
            }
            else {
                this->storage_space[i] = gamma;
            }
        }
        return true;
    }
    /*reshape
    Enter: 1.Teshape
    reshape the Tensor
    return if reshape successfully*/
    template <typename Data>
    bool Tensor<Data>::reshape_(Teshape const& alpha) {
        if (this->_shape == alpha)
            return true;
        if (this->_shape._size != alpha._size)
            return false;
        this->_shape = alpha;
        return true;
    }
    /*operator[]
    Enter: 1.coordinate
    do nothing
    return the data in the coordinate*/
    template <typename Data>
    Data Tensor<Data>::operator[](Teshape const& alpha) {
        if (!(belongs(alpha, this->_shape)))
            return static_cast<Data>(0);
        return this->storage_space[this->_shape.coordinate(alpha)];
    }
    /*operator=
    Enter: 1.Tensor
    copy the Tensor
    return this*/
    template <typename Data>
    Tensor<Data> Tensor<Data>::operator=(Tensor<Data> const& alpha) {
        if (this->_shape._size)
            delete[] this->storage_space;
        this->_shape = alpha._shape;
        int gamma = this->_shape._size;
        this->storage_space = new Data[gamma];
        for (int zeta = 0; zeta < gamma; zeta++) {
            this->storage_space[zeta] = alpha.storage_space[zeta];
        }
        return (*this);
    }
    /*operator=
    Enter: 1.value
    copy the value into the Tensor
    return this*/
    template <typename Data>
    Tensor<Data> Tensor<Data>::operator=(Data const& alpha) {
        int gamma = this->_shape._size;
        for (int zeta = 0; zeta < gamma; zeta++) {
            this->storage_space[zeta] = alpha;
        }
        return (*this);
    }
    /*flat to Vector
    Enter: none
    flat the Tensor into Vector
    return the Vector*/
    template <typename Data>
    Vector<Data> Tensor<Data>::flat() {
        Vector<Data> temp(this->_shape._size, this->storage_space);
        return temp;
    }
    /*flat to Matrix
    Enter: 1.dividing line
    flat the Tensor into Matrix
    return the Matrix*/
    template <typename Data>
    Matrix<Data> Tensor<Data>::flat(int const& alpha) {
        MaShape gamma = { 1,0 };
        for (int i = 0; i < alpha; i++)
            gamma.rows *= this->_shape[i];
        gamma.lines = this->_shape._size / gamma.rows;
        Matrix<Data> temp(gamma, this->storage_space);
        return temp;
    }
    /*stand
    Enter: 1.Vector 2.Teshape
    stand the Vector into Tensor
    return if stand successfully*/
    template <typename Data>
    bool Tensor<Data>::stand_(Vector<Data> const& alpha, Teshape const& beta) {
        if (alpha._shape != beta._size)
            return false;
        if (this->_shape._size)
            delete[] this->storage_space;
        this->_shape = beta;
        this->storage_space = new Data[this->_shape._size];
        for (int i = 0; i < this->_shape._size; i++)
            this->storage_space[i] = alpha.storage_space[i];
        return true;
    }
}
#undef bsm
template class Linalg::Tensor<int>;
//template class Linalg::Tensor<int64_t>;
template class Linalg::Tensor<float>;
//template class Linalg::Tensor<_Float64>;
//template class Linalg::Tensor<__fp16>;