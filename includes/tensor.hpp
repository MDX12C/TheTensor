#ifndef TENSOR_H
#define TENSOR_H
#include "./matrix.hpp"
#define bsm Basic_Math
namespace Linalg {
    class Teshape {
    private:
        int _dimansion = 1;
        int _size = 1;
        int* shape = nullptr;
        friend std::istream& operator>>(std::istream&, Teshape&);
        friend std::ostream& operator<<(std::ostream&, Teshape const&);
        friend bool belongs(Teshape const&, Teshape const&);
        template <typename Data>
        friend class Linalg::Tensor;
    public:
        Teshape(int const&);
        Teshape(int const&, int* const&);
        Teshape(Teshape const&);
        Teshape();
        ~Teshape();
        bool endow_(int const&, int const&);
        int operator[](int const&);
        Teshape operator=(Teshape const&);
        bool operator==(Teshape const&);
        inline int dimansion() { return this->_dimansion; }
        inline int size() { return this->_size; }
        bool reshape_(Teshape const&);
        void freedom_();
        int coordinate(Teshape const&);
        Teshape coordinate(int const&);
    };
    std::istream& operator>>(std::istream&, Teshape&);
    std::ostream& operator<<(std::ostream&, Teshape const&);
    bool belongs(Teshape const&, Teshape const&);

    template <typename Data>
    class Tensor {
    private:
        Data* storage_space;
        Data _sum;
        Teshape _shape;
        int _digits;

        friend class Linalg::Matrix<Data>;
        friend class Linalg::Vector<Data>;
    public:
        Tensor(Teshape const&, Data* const&);
        Tensor(Teshape const&);
        Tensor();
        Tensor(Tensor const&);
        ~Tensor();
        inline Teshape shape() { return this->_shape; }
        void freedom_();
        bool endow_(Teshape const&, Data const&);
        bool resize_(Teshape const&);
        bool reshape_(Teshape const&);
        Matrix<Data> flat(int const&);
        Vector<Data> flat();
        bool stand_(Vector<Data> const&, Teshape const&);
        Data operator[](Teshape const&);
        Tensor operator=(Tensor const&);
        Tensor operator=(Data const&);
    };
}
#undef bsm
#endif