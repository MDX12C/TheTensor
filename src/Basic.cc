#include "../includes/basic.hpp"
namespace Basic_Math {
    /*Interface Digits
    Enter: 1.value
    count how many numbers before the point
    return the number*/
    template <typename Data>
    int Int_Digits(Data const& alpha) {
        if constexpr (std::is_same_v<Data, bool>) {
            return 1;
        }
        else {
            if (alpha < static_cast<Data>(0)) {
                return (std::floor(std::log10(-alpha)) + 1);
            }
            else {
                return (std::floor(std::log10(alpha)) + 1);
            }
        }
    }
    /*random
    Enter: 1.min value 2.max value
    random a number in the range
    return the number*/
    template <typename Data>
    Data random(Data const& alpha, Data const& beta) {
        if (!set_seed) {
            std::srand(int(std::time(0)));
            set_seed = true;
        }
        if constexpr (std::is_same_v<Data, int>) {
#ifdef _DEBUG_MODE_
            printf("int random\n");
#endif
            long long range = static_cast<long long>(beta) - static_cast<long long>(alpha) + 1;
            long long ans = static_cast<long long>(std::rand()) * 2;
            if (range < 0) {
                range *= -1;
                ans %= range;
                return static_cast<int>(beta + ans);
            }
            else {
                ans %= range;
                return static_cast<int>(alpha + ans);
            }
        }
        else if constexpr (std::is_same_v<Data, float>) {
#ifdef _DEBUG_MODE_
            printf("float random\n");
#endif
            long double range = static_cast<long double>(beta) - static_cast<long double>(alpha) + 1;
            long double floating = static_cast<long double>(std::rand()) / RAND_MAX;
            if (range < 0) {
                range *= -1;
                floating *= range;
                return static_cast<float>(beta + floating);
            }
            else {
                floating *= range;
                return static_cast<float>(alpha + floating);
            }
        }
        else if constexpr (std::is_same_v<Data, bool>) {
#ifdef _DEBUG_MODE_
            printf("bool random\n");
#endif
            return static_cast<bool>(std::rand() % 2);
        }
        else {
            Data range = beta - alpha + 1;
            return alpha + (std::rand() % range);
        }
    }
    void status() {
        std::cout << "\nset_seed:" << set_seed << '\n';
#ifdef _TREAD_MODE_
        std::cout << "_TREAD_MODE_\n";
#endif
        if (SIMD_ON) {
            std::cout << "_SIMD_MODE_";
#ifdef _SIMD_01_
            std::cout << "01_\n\n";
#else 
            std::cout << "02_\n\n";
#endif
        }
        return;
    }
}
template int Basic_Math::Int_Digits(int const&);
template int Basic_Math::Int_Digits(float const&);
template int Basic_Math::Int_Digits(bool const&);
template int Basic_Math::random(int const&, int const&);
template float Basic_Math::random(float const&, float const&);
template bool Basic_Math::random(bool const&, bool const&);