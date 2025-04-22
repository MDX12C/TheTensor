#include "thetensor/random.hpp"

#include "thetensor/define.hpp"
#if RANDOM_HH
namespace basic_math {
std::mt19937_64 RandomSupport::generator_;
}  // namespace basic_math
#endif