#include "interface.hpp"

template <typename T>
inline bool check(T* const&, T* const&, size_t const&) noexcept;

signed main() {
  CONSTRUCT;
  auto getNumber = [](const char* const& __str) -> size_t {
    int alpha = -1;
    std::cout << "number of " << __str << " :\n";
    std::cin >> alpha;
    std::cin.get();
    return alpha <= 0 ? 1 : static_cast<size_t>(alpha);
  };
  system_control::Status::refresh("test of cuda", true);
  auto const TOTAL_SIZE = getNumber("test size"),
             SUB_OFFEST = getNumber("sub offest"),
             SUB_SIZE = getNumber("sub size"),
             SUB_BYTES = SUB_SIZE * sizeof(int32_t);
  if (TOTAL_SIZE < SUB_OFFEST + SUB_SIZE) endOfMainFunction();
  auto alpha = basic_math::uniformRand<int32_t>(TOTAL_SIZE, -10, 10);
  auto beta = lina_lg::scan(alpha, SUB_OFFEST, SUB_OFFEST + SUB_SIZE);
  int32_t *gpuVec, *cpuVec = new int32_t[SUB_SIZE];
  vramAlloc((void**)&gpuVec, SUB_BYTES);
  vramCopy(gpuVec, alpha.begin() + SUB_OFFEST, SUB_BYTES, 1);
  vramCopy(cpuVec, gpuVec, SUB_BYTES, 2);
  check(cpuVec, beta.begin(), SUB_SIZE);
  delete[] cpuVec;
  vramFree((void**)&gpuVec);
  DESTRUCT;
}

template <typename T>
inline bool check(T* const& __a, T* const& __b, size_t const& __size) noexcept {
  std::string extand;
  extand.reserve(50);
  for (size_t i = 0; i < __size; i++) {
    sprintf(extand.data(), "check %ld in %ld", i + 1, __size);
    system_control::Status::bar(i, __size, extand);
    if constexpr (std::is_floating_point_v<T>) {
      if (std::abs(__a[i] - __b[i]) > static_cast<T>(0.001)) {
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
  system_control::Status::bar(1, 1);
  printf("Operate Success!\n");
  return true;
}
