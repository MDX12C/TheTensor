#include"../includes/basic.hpp"
namespace Basic_Math {
    /*Interface Digits
    Enter: 1.value
    count how many numbers before the point
    return the number*/
    template <typename Data>
    int Int_Digits(Data const& alpha) {
        if (alpha < static_cast<Data>(0)) {
            return (std::floor(std::log10(-alpha)) + 1);
        }
        else {
            return (std::floor(std::log10(alpha)) + 1);
        }
    }
}
template int Basic_Math::Int_Digits(int32_t const&);
template int Basic_Math::Int_Digits(_Float32 const&);