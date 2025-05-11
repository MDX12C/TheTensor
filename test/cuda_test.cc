#include "interface.hpp"

template <typename T>
inline bool check(T* const&, T* const&, size_t const&) noexcept;

signed main() {
  CONSTRUCT;
  auto getTimes = [](const char* const& __str) -> size_t {
    int alpha = -1;
    do {
      std::cout << "number of " << __str << " :\n";
      std::cin >> alpha;
      std::cin.get();
    } while (alpha <= 0);
    return static_cast<size_t>(alpha);
  };
  const size_t TEST_LENTH = getTimes("test lenth");
  std::cout << "size= " << TEST_LENTH << '\n';
  auto vecA = basic_math::uniformRand<float_t>(TEST_LENTH, -1, 1);
  auto vecB = basic_math::uniformRand<float_t>(TEST_LENTH, -1, 1);
  lina_lg::Vector<float_t> ansC(TEST_LENTH), ansG(TEST_LENTH);
  auto cpuCost = [&]() {
    clock_t first, second;
    auto alpha = vecA.begin(), beta = vecB.begin(), gamma = ansC.begin();
    first = clock();
    for (size_t i = 0; i < TEST_LENTH; i++) gamma[i] = alpha[i] + beta[i];
    second = clock();
    return second - first;
  }();
  auto gpuCost =
      test_for_vram(vecA.begin(), vecB.begin(), ansG.begin(), TEST_LENTH);
  std::cout << "cpu used " << cpuCost << " gpu used " << gpuCost << '\n';
  check(ansC.begin(), ansG.begin(), TEST_LENTH);
  DESTRUCT;
}

template <typename T>
inline bool check(T* const& __a, T* const& __b, size_t const& __size) noexcept {
  std::string extand;
  extand.reserve(50);
  for (size_t i = 0; i < __size; i++) {
    sprintf(extand.data(), "check %ld in %ld", i + 1, __size);
    system_message::Status::bar(i, __size, extand);
    if constexpr (std::is_floating_point_v<T>) {
      if ((__a[i] - __b[i]) > static_cast<T>(0.001)) {
        LOG("E:bad answer");
        printf("\nbad answer when i= %ld\n", i);
        return false;
      }
    } else {
      if (__a[i] != __b[i]) {
        LOG("E:bad answer");
        printf("\nbad answer when i= %ld\n", i);
        return false;
      }
    }
  }
  system_message::Status::bar(1, 1);
  printf("Operate Success!\n");
  return true;
}
