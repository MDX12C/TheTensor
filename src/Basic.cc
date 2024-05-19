#include "../includes/basic.hpp"
namespace Basic_Math {
    std::atomic<bool> set_seed(false);
    std::atomic<unsigned long long> memory_heap(0);
    float float_leak = 0;
    bool bool_leak = false;
    int int_leak = 0;
}