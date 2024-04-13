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
}
#endif