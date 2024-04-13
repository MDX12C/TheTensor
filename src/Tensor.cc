#include"../includes/tensor.hpp"
namespace Linalg {
    /*Constructor Datas
    Enter: 1.Teshape 2.Data pointer
    construct a Tensor with inited Datas
    no return*/
    template <typename Data>
    Tensor<Data>::Tensor(bsm::Teshape const& alpha, Data* const& beta) {
        this->_shape = alpha;
        this->_sum = static_cast<Data>(0);
        this->_digits = 1;
        int gamma = this->_shape.size();
        this->storage_space = new Data[gamma];
        for (int zeta = 0; zeta < gamma; zeta++) {
            this->storage_space[zeta] = beta[zeta];
            this->_sum += beta[zeta];
            this->_digits = std::max(this->_digits, Basic_Math::Int_Digits(this->storage_space[zeta]));
        }
        return;
    }
    /*Constructor value
    Enter: 1.Teshape 2.init value
    construct a Tensor fill with the value
    no return*/
    template <typename Data>
    Tensor<Data>::Tensor(bsm::Teshape const& alpha, Data const& beta) {
        this->_shape = alpha;
        this->_digits = bsm::Int_Digits(beta);
        int gamma = this->_shape.size();
        this->_sum = beta * static_cast<Data>(gamma);
        this->storage_space = new Data[gamma];
        for (int zeta = 0; zeta < gamma; zeta++) {
            this->storage_space[zeta] = beta;
        }
        return;
    }
    /*constructor Teshape
    Enter: 1.Teshape
    constructor a Tensor with the shape and fill with 0
    no return*/
    template <typename Data>
    Tensor<Data>::Tensor(bsm::Teshape const& alpha) {
        this->_shape = alpha;
        int gamma = this->_shape.size();
        this->storage_space = new Data[gamma];
        for (int zeta = 0; zeta < gamma; zeta++) {
            this->storage_space[zeta] = static_cast<Data>(0);
        }
        this->_sum = static_cast<Data>(0);
        this->_digits = 1;
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
        this->_sum = static_cast<Data>(0);
        this->_digits = 1;
        return;
    }
    /*copy constructor
    Enter: 1.Tensor
    construct a Tensor from another Tensor
    no return*/
    template <typename Data>
    Tensor<Data>::Tensor(Tensor<Data> const& alpha) {
        if (this->_shape.size())
            delete[] this->storage_space;
        this->_shape = alpha._shape;
        this->_sum = alpha._sum;
        this->_digits = alpha._digits;
        int gamma = this->_shape.size();
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
        if (this->_shape.size())
            delete[] this->storage_space;
        return;
    }
    /*freedom
    Enter: none
    free all the space of the Tensor and init the Tensor with shape 1
    no return*/
    template <typename Data>
    void Tensor<Data>::freedom_() {
        if (this->_shape.size())
            delete[] this->storage_space;
        this->_shape.freedom_();
        this->_sum = static_cast<Data>(0);
        this->_digits = 1;
        this->storage_space = new Data[1];
        this->storage_space[0] = static_cast<Data>(0);
        return;
    }
    /*endow
    Enter: 1.coordinate 2.value
    endow the value at the coordinate
    no return*/
    template <typename Data>
    void Tensor<Data>::endow_(bsm::Teshape const& alpha, Data const& beta) {
        if (!(bsm::belongs(alpha, this->_shape)))
            return;
        this->_sum += beta - this->storage_space[alpha];
        this->storage_space[alpha] = beta;
        this->_digits = 1;
        for (int i = 0; i < this->_shape.size(); i++)
            this->_digits = std::max(this->_digits, Basic_Math::Int_Digits(this->storage_space[i]));
        return;
    }
    /*resize
    Enter: 1.Teshape
    resize the Tensor，the beyond data will be fill with 0
    no return*/
    template <typename Data>
    void Tensor<Data>::resize_(bsm::Teshape const& alpha) {
        //
    }
}