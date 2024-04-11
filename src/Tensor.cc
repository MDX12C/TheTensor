#include"../includes/tensor.hpp"
namespace Linalg {
    /*Constructor Datas
    Enter: 1.Teshape 2.Data pointer
    construct a Tensor with inited Datas
    no return*/
    template <typename Data>
    Tensor<Data>::Tensor(bsm::Teshape const& alpha, Data* const& beta) {
        this->_shape = alpha;
        int gamma = this->_shape.size();
        this->storage_space = new Data[gamma];
        for (int zeta = 0; zeta < gamma; zeta++) {
            this->storage_space[zeta] = beta[zeta];
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
        int gamma = this->_shape.size();
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
    Tensor<Data>::Tensor(bsm::Teshape const& alpha){
        this->_shape=alpha;
        int gamma = this->_shape.size();
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
        if(this->_shape.size())
            delete[] this->storage_space;
        this->_shape = alpha._shape;
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
        if(this->_shape.size())
            delete[] this->storage_space;
        return;
    }
    /*freedom
    Enter: none
    free all the space of the Tensor and init the Tensor with shape 1
    no return*/
    template <typename Data>
    void Tensor<Data>::freedom_() {
        if(this->_shape.size())
            delete[] this->storage_space;
        this->_shape.freedom_();
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
        if(!(bsm::belongs(alpha, this->_shape)))
            return;
        /**/
    }
}