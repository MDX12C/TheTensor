#include<iostream>
#include<iomanip>
#include<cfloat>
#include<cmath>

#ifndef BASIC_H
#define BASIC_H
namespace Basic_Math {
    constexpr int Float16_Accuracy = 3;
    constexpr int Float32_Accuracy = 7;
    template <typename Data>
    int Int_Digits(Data const&);
    class Teshape {
    private:
        int _dimansion = 1;
        int _size = 1;
        int* shape = nullptr;
        friend std::istream& operator>>(std::istream&, Teshape&);
        friend std::ostream& operator<<(std::ostream&, Teshape const&);
        friend bool belongs(Teshape const&, Teshape const&);
    public:
        Teshape(int const&);
        Teshape(int const&, int* const&);
        Teshape(Teshape const&);
        Teshape();
        ~Teshape();
        void endow_(int const&, int const&);
        int operator[](int const&);
        void operator=(Teshape const&);
        bool operator==(Teshape const&);
        inline int dimansion() { return this->_dimansion; }
        inline int size() { return this->_size; }
        bool reshape_(Teshape const&);
        void freedom_();
        int coordinate(Teshape const&);
    };
    std::istream& operator>>(std::istream&, Teshape&);
    std::ostream& operator<<(std::ostream&, Teshape const&);
    bool belongs(Teshape const&, Teshape const&);
}
#endif