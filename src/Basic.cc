#include "../includes/basic.hpp"
namespace Basic_Math {
    std::atomic<bool> set_seed(false);
    std::atomic<unsigned long long> memory_heap(0);
    float float_leak = 0;
    bool bool_leak = false;
    int int_leak = 0;
    const float float_value_max = static_cast<float>(200);
    const float float_value_min = (-1) * float_value_max;
    const int int_value_max = static_cast<int>(200);
    const int int_value_min = (-1) * int_value_max;
    const bool bool_value_max = true;
    const bool bool_value_min = false;
}