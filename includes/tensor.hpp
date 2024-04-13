#ifndef TENSOR_H
#define TENSOR_H
#include "./matrix.hpp"
namespace bsm=Basic_Math;
namespace Linalg {
    template <typename Data>
    class Tensor {
    private:
        Data* storage_space;
        Data _sum;
        bsm::Teshape _shape;
        int _digits;
    public:
        Tensor(bsm::Teshape const&, Data* const&);
        Tensor(bsm::Teshape const&, Data const&);
        Tensor(bsm::Teshape const&);
        Tensor();
        Tensor(Tensor const&);
        ~Tensor();
        inline bsm::Teshape shape() { return this->_shape; }
        inline Data sum() { return this->_sum; }
        void freedom_();
        void endow_(bsm::Teshape const&, Data const&);
        void resize_(bsm::Teshape const&);
        void reshape_(bsm::Teshape const&);
        Matrix flat(int const&);
        Data operator[](bsm::Teshape const&);
        void operator=(Tensor const&);
        void operator=(Data const&);
    };
}
#endif