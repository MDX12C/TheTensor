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
    /*random int
    Enter: 1.min value 2.max value
    random a number in the range
    return the number*/
    int32_t random(int32_t const& alpha, int32_t const& beta) {
        if (!set_seed) {
            std::srand(int(std::time(0)));
            set_seed = true;
        }
        int64_t range = static_cast<int64_t>(beta) - static_cast<int64_t>(alpha) + 1;
        int64_t ans = static_cast<int64_t>(std::rand()) * 2;
        if (range < 0) {
            range *= -1;
            ans %= range;
            return static_cast<int32_t>(beta + ans);
        }
        else {
            ans %= range;
            return static_cast<int32_t>(alpha + ans);
        }
    }
    /*random float
    Enter: 1.min value 2.max value
    random a number in the range
    return the number*/
    _Float32 random(_Float32 const& alpha, _Float32 const& beta) {
        if (!set_seed) {
            std::srand(int(std::time(0)));
            set_seed = true;
        }
        _Float64 range = static_cast<_Float64>(beta) - static_cast<_Float64>(alpha) + 1;
        _Float64 floating = static_cast<_Float64>(std::rand()) / RAND_MAX;
        if (range < 0) {
            range *= -1;
            floating *= range;
            return static_cast<_Float32>(beta + floating);
        }
        else {
            floating *= range;
            return static_cast<_Float32>(alpha + floating);
        }
    }
}
template int Basic_Math::Int_Digits(int32_t const&);
template int Basic_Math::Int_Digits(_Float32 const&);