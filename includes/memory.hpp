#include"math.hpp"
namespace Linalg{
    struct meta{
        int* shape=nullptr;
        int Dimensions=0;
    };

    template<typename Data>
    class Tensor{
        private:
        Data *storage_space;
        meta meta;
        public:
        Tensor(Data const&,meta const&);
        Tensor(Data* const&,meta const&);
        ~Tensor();
        void operator=(Data const&);
        void operator=(Tensor const&);
        Tensor operator+(Data const&);
        Tensor operator+(Tensor const&);
        Tensor operator-(Data const&);
        Tensor operator-(Tensor const&);
        Tensor operator*(Data const&);
        Tensor operator*(Tensor const&);
        Tensor operator/(Data const&);
        Tensor operator/(Tensor const&);
        void reshape_(meta const&);
    };
}