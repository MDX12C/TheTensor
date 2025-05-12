#include "interface.hpp"

#define TEST_ADD 1
#define TEST_MNS 1
#define TEST_MUL 1
#define TEST_DIV 1
#define TEST_SUM 1
#define TEST_DOT 1

size_t stressLevel__;
template <typename T>
inline bool check(T* const&, T* const&, size_t const&) noexcept;
template <typename T>
inline void testAdd(size_t const&) noexcept;
template <typename T>
inline void testMns(size_t const&) noexcept;
template <typename T>
inline void testMul(size_t const&) noexcept;
template <typename T>
inline void testDiv(size_t const&) noexcept;
template <typename T>
inline void testHV(size_t const&);
template <>
inline void testHV<bool>(size_t const&);
template <typename T>
inline void testDot(size_t const&) noexcept;

signed main() {
  CONSTRUCT;
  system_control::Status::refresh("0");
  size_t TEST_SIZE = 512;
  std::cout << "THREADS= " << THREADS << " CUDA= " << __CUDA_MODE__ << '\n';
  auto getTimes = [](const char* const& __s) -> size_t {
    int a = -1;
    do {
      std::cout << "put number of " << __s << ":\n";
      std::cin >> a;
      std::cin.get();
    } while (a <= 0);
    return size_t(a);
  };
  // ###############################################################
#if TEST_ADD
  system_control::Status::refresh("Test for add function", true);
  TEST_SIZE = getTimes("test times");
  stressLevel__ = getTimes("stress level");
  system_control::Status::announce("bool");
  testAdd<bool>(TEST_SIZE);
  system_control::Status::pause();
  system_control::Status::announce("int 8");
  testAdd<int8_t>(TEST_SIZE);
  system_control::Status::announce("int 16");
  testAdd<int16_t>(TEST_SIZE);
  system_control::Status::pause();
  system_control::Status::announce("int 32");
  testAdd<int32_t>(TEST_SIZE);
  system_control::Status::announce("int 64");
  testAdd<int64_t>(TEST_SIZE);
  system_control::Status::pause();
  system_control::Status::announce("unsigned int 8");
  testAdd<uint8_t>(TEST_SIZE);
  system_control::Status::announce("unsigned int 16");
  testAdd<uint16_t>(TEST_SIZE);
  system_control::Status::pause();
  system_control::Status::announce("unsigned int 32");
  testAdd<uint32_t>(TEST_SIZE);
  system_control::Status::announce("unsigned int 64");
  testAdd<uint64_t>(TEST_SIZE);
  TEST_SIZE = getTimes("test times");
  stressLevel__ = getTimes("stress level");
  system_control::Status::announce("float");
  testAdd<float_t>(TEST_SIZE);
  system_control::Status::announce("double");
  testAdd<double_t>(TEST_SIZE);
#endif
  // ###############################################################
#if TEST_MNS
  system_control::Status::refresh("Test for minus function", true);
  TEST_SIZE = getTimes("test times");
  stressLevel__ = getTimes("stress level");
  system_control::Status::announce("bool");
  testMns<bool>(TEST_SIZE);
  system_control::Status::pause();
  system_control::Status::announce("int 8");
  testMns<int8_t>(TEST_SIZE);
  system_control::Status::announce("int 16");
  testMns<int16_t>(TEST_SIZE);
  system_control::Status::pause();
  system_control::Status::announce("int 32");
  testMns<int32_t>(TEST_SIZE);
  system_control::Status::announce("int 64");
  testMns<int64_t>(TEST_SIZE);
  system_control::Status::pause();
  system_control::Status::announce("unsigned int 8");
  testMns<uint8_t>(TEST_SIZE);
  system_control::Status::announce("unsigned int 16");
  testMns<uint16_t>(TEST_SIZE);
  system_control::Status::pause();
  system_control::Status::announce("unsigned int 32");
  testMns<uint32_t>(TEST_SIZE);
  system_control::Status::announce("unsigned int 64");
  testMns<uint64_t>(TEST_SIZE);
  TEST_SIZE = getTimes("test times");
  stressLevel__ = getTimes("stress level");
  system_control::Status::announce("float");
  testMns<float_t>(TEST_SIZE);
  system_control::Status::announce("double");
  testMns<double_t>(TEST_SIZE);
#endif
// ###############################################################
#if TEST_MUL
  system_control::Status::refresh("Test for mutiple function", true);
  TEST_SIZE = getTimes("test times");
  stressLevel__ = getTimes("stress level");
  system_control::Status::announce("bool");
  testMul<bool>(TEST_SIZE);
  system_control::Status::pause();
  system_control::Status::announce("int 8");
  testMul<int8_t>(TEST_SIZE);
  system_control::Status::announce("int 16");
  testMul<int16_t>(TEST_SIZE);
  system_control::Status::pause();
  system_control::Status::announce("int 32");
  testMul<int32_t>(TEST_SIZE);
  system_control::Status::announce("int 64");
  testMul<int64_t>(TEST_SIZE);
  system_control::Status::pause();
  system_control::Status::announce("unsigned int 8");
  testMul<uint8_t>(TEST_SIZE);
  system_control::Status::announce("unsigned int 16");
  testMul<uint16_t>(TEST_SIZE);
  system_control::Status::pause();
  system_control::Status::announce("unsigned int 32");
  testMul<uint32_t>(TEST_SIZE);
  system_control::Status::announce("unsigned int 64");
  testMul<uint64_t>(TEST_SIZE);
  TEST_SIZE = getTimes("test times");
  stressLevel__ = getTimes("stress level");
  system_control::Status::announce("float");
  testMul<float_t>(TEST_SIZE);
  system_control::Status::announce("double");
  testMul<double_t>(TEST_SIZE);
#endif
// ###############################################################
#if TEST_DIV
  system_control::Status::refresh("Test for divide function", true);
  TEST_SIZE = getTimes("test times");
  stressLevel__ = getTimes("stress level");
  system_control::Status::announce("bool");
  testDiv<bool>(TEST_SIZE);
  system_control::Status::pause();
  system_control::Status::announce("int 8");
  testDiv<int8_t>(TEST_SIZE);
  system_control::Status::announce("int 16");
  testDiv<int16_t>(TEST_SIZE);
  system_control::Status::pause();
  system_control::Status::announce("int 32");
  testDiv<int32_t>(TEST_SIZE);
  system_control::Status::announce("int 64");
  testDiv<int64_t>(TEST_SIZE);
  system_control::Status::pause();
  system_control::Status::announce("unsigned int 8");
  testDiv<uint8_t>(TEST_SIZE);
  system_control::Status::announce("unsigned int 16");
  testDiv<uint16_t>(TEST_SIZE);
  system_control::Status::pause();
  system_control::Status::announce("unsigned int 32");
  testDiv<uint32_t>(TEST_SIZE);
  system_control::Status::announce("unsigned int 64");
  testDiv<uint64_t>(TEST_SIZE);
  TEST_SIZE = getTimes("test times");
  stressLevel__ = getTimes("stress level");
  system_control::Status::announce("float");
  testDiv<float_t>(TEST_SIZE);
  system_control::Status::announce("double");
  testDiv<double_t>(TEST_SIZE);
#endif
// ###############################################################
#if TEST_SUM
  system_control::Status::refresh("Test for Horizontal and Vertical Sum", true);
  TEST_SIZE = getTimes("test times");
  stressLevel__ = getTimes("stress level");
  system_control::Status::announce("bool");
  testHV<bool>(TEST_SIZE);
  system_control::Status::pause();
  system_control::Status::announce("int 8");
  testHV<int8_t>(TEST_SIZE);
  system_control::Status::announce("int 16");
  testHV<int16_t>(TEST_SIZE);
  system_control::Status::pause();
  system_control::Status::announce("int 32");
  testHV<int32_t>(TEST_SIZE);
  system_control::Status::announce("int 64");
  testHV<int64_t>(TEST_SIZE);
  system_control::Status::pause();
  system_control::Status::announce("unsigned int 8");
  testHV<uint8_t>(TEST_SIZE);
  system_control::Status::announce("unsigned int 16");
  testHV<uint16_t>(TEST_SIZE);
  system_control::Status::pause();
  system_control::Status::announce("unsigned int 32");
  testHV<uint32_t>(TEST_SIZE);
  system_control::Status::announce("unsigned int 64");
  testHV<uint64_t>(TEST_SIZE);
  TEST_SIZE = getTimes("test times");
  stressLevel__ = getTimes("stress level");
  system_control::Status::announce("float");
  testHV<float_t>(TEST_SIZE);
  system_control::Status::announce("double");
  testHV<double_t>(TEST_SIZE);
#endif
// ###############################################################
#if TEST_DOT
  system_control::Status::refresh("Test for matrix dot", true);
  TEST_SIZE = getTimes("test times");
  stressLevel__ = getTimes("stress level");
  system_control::Status::announce("bool");
  testDot<bool>(TEST_SIZE);
  system_control::Status::pause();
  system_control::Status::announce("int 8");
  testDot<int8_t>(TEST_SIZE);
  system_control::Status::announce("int 16");
  testDot<int16_t>(TEST_SIZE);
  system_control::Status::pause();
  system_control::Status::announce("int 32");
  testDot<int32_t>(TEST_SIZE);
  system_control::Status::announce("int 64");
  testDot<int64_t>(TEST_SIZE);
  system_control::Status::pause();
  system_control::Status::announce("unsigned int 8");
  testDot<uint8_t>(TEST_SIZE);
  system_control::Status::announce("unsigned int 16");
  testDot<uint16_t>(TEST_SIZE);
  system_control::Status::pause();
  system_control::Status::announce("unsigned int 32");
  testDot<uint32_t>(TEST_SIZE);
  system_control::Status::announce("unsigned int 64");
  testDot<uint64_t>(TEST_SIZE);
  TEST_SIZE = getTimes("test times");
  stressLevel__ = getTimes("stress level");
  system_control::Status::announce("float");
  testDot<float_t>(TEST_SIZE);
  system_control::Status::announce("double");
  testDot<double_t>(TEST_SIZE);
#endif
  // ###############################################################
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
  system_control::Status::bar(1, 1);
  std::cout << "\nCompute success!\n";
  return true;
}
template <typename T>
inline void testAdd(size_t const& __size) noexcept {
  auto alpha = new T[__size];
  auto beta = new T[__size];
  auto gamma = new T[__size];
  T theta, phi;
  if constexpr (std::is_same_v<T, bool>) {
    theta = basic_math::uniformRand<T>(0, 1);
    phi = basic_math::uniformRand<T>(0, 1);
  } else {
    theta = basic_math::uniformRand<T>(0, 5);
    phi = basic_math::uniformRand<T>(0, 5);
  }
  std::string tips("initializing...");
  for (size_t i = 0; i < __size; i++) {
    system_control::Status::bar(i, __size, tips);
    if constexpr (std::is_same_v<T, bool>) {
      alpha[i] = basic_math::uniformRand<T>(0, 1);
      beta[i] = basic_math::uniformRand<T>(0, 1);
    } else {
      alpha[i] = basic_math::uniformRand<T>(0, 5);
      beta[i] = basic_math::uniformRand<T>(0, 5);
    }
  }
  system_control::Status::bar(1, 1);
  std::cout << "\ncuda in vec + vec:\n";
  basic_math::add<T, true>(alpha, beta, gamma, __size);
  tips = "checking answer...";
  [&] {
    for (size_t i = 0; i < __size; i++) {
      system_control::Status::bar(i, __size, tips);
      if constexpr (std::is_same_v<T, bool>) {
        if (gamma[i] != (alpha[i] || beta[i])) {
          std::cout << "\nError: bad answer when i= " << i << '\n';
          LOG("E:error answer");
          return;
        }
      } else {
        if (gamma[i] != (alpha[i] + beta[i])) {
          std::cout << "\nError: bad answer when i= " << i << '\n';
          LOG("E:error answer");
          return;
        }
      }
    }
    system_control::Status::bar(1, 1);
    std::cout << "\nOperate success!\n";
    return;
  }();
  std::cout << "cuda in vec + scl:\n";
  basic_math::add<T, true>(alpha, theta, gamma, __size);
  [&] {
    for (size_t i = 0; i < __size; i++) {
      system_control::Status::bar(i, __size, tips);
      if constexpr (std::is_same_v<T, bool>) {
        if (gamma[i] != (alpha[i] || theta)) {
          std::cout << "\nError: bad answer when i= " << i << '\n';
          LOG("E:error answer");
          return;
        }
      } else {
        if (gamma[i] != (alpha[i] + theta)) {
          std::cout << "\nError: bad answer when i= " << i << '\n';
          LOG("E:error answer");
          return;
        }
      }
    }
    system_control::Status::bar(1, 1);
    std::cout << "\nOperate success!\n";
    return;
  }();
  std::cout << "cuda in scl + vec:\n";
  basic_math::add<T, true>(phi, beta, gamma, __size);
  [&] {
    for (size_t i = 0; i < __size; i++) {
      system_control::Status::bar(i, __size, tips);
      if constexpr (std::is_same_v<T, bool>) {
        if (gamma[i] != (phi || beta[i])) {
          std::cout << "\nError: bad answer when i= " << i << '\n';
          LOG("E:error answer");
          return;
        }
      } else {
        if (gamma[i] != (phi + beta[i])) {
          std::cout << "\nError: bad answer when i= " << i << '\n';
          LOG("E:error answer");
          return;
        }
      }
    }
    system_control::Status::bar(1, 1);
    std::cout << "\nOperate success!\n";
    return;
  }();
  std::clock_t point1, point2, point3;
  point1 = std::clock();
  basic_math::add<T, true>(alpha, beta, gamma, __size);
  point2 = std::clock();
  basic_math::add<T, false>(alpha, beta, gamma, __size);
  point3 = std::clock();
  point3 -= point2;
  point2 -= point1;
  std::cout << "GPU use " << point2 << " and CPU use " << point3
            << "\ncuda stress test:\n";
  for (auto i = 0; i < stressLevel__; i++) {
    system_control::Status::bar(i, stressLevel__);
    basic_math::add<T, true>(alpha, beta, gamma, __size);
  }
  system_control::Status::bar(1, 1);
  std::cout << '\n';
  delete[] alpha;
  delete[] beta;
  delete[] gamma;
}
template <typename T>
inline void testMns(size_t const& __size) noexcept {
  auto alpha = new T[__size];
  auto beta = new T[__size];
  auto gamma = new T[__size];
  T theta, phi;
  if constexpr (std::is_same_v<T, bool>) {
    theta = basic_math::uniformRand<T>(0, 1);
    phi = basic_math::uniformRand<T>(0, 1);
  } else {
    theta = basic_math::uniformRand<T>(0, 5);
    phi = basic_math::uniformRand<T>(15, 20);
  }
  std::string tips("initializing...");
  for (size_t i = 0; i < __size; i++) {
    system_control::Status::bar(i, __size, tips);
    if constexpr (std::is_same_v<T, bool>) {
      alpha[i] = basic_math::uniformRand<T>(0, 1);
      beta[i] = basic_math::uniformRand<T>(0, 1);
    } else {
      alpha[i] = basic_math::uniformRand<T>(10, 15);
      beta[i] = basic_math::uniformRand<T>(5, 10);
    }
  }
  system_control::Status::bar(1, 1);
  std::cout << "\ncuda in vec - vec:\n";
  basic_math::mns<T, true>(alpha, beta, gamma, __size);
  tips = "checking answer...";
  [&] {
    for (size_t i = 0; i < __size; i++) {
      system_control::Status::bar(i, __size, tips);
      if constexpr (std::is_same_v<T, bool>) {
        if (gamma[i] != (alpha[i] && (!beta[i]))) {
          std::cout << "\nError: bad answer when i= " << i << '\n';
          LOG("E:error answer");
          return;
        }
      } else {
        if (gamma[i] != (alpha[i] - beta[i])) {
          std::cout << "\nError: bad answer when i= " << i << '\n';
          LOG("E:error answer");
          return;
        }
      }
    }
    system_control::Status::bar(1, 1);
    std::cout << "\nOperate success!\n";
    return;
  }();
  std::cout << "cuda in vec - scl:\n";
  basic_math::mns<T, true>(alpha, theta, gamma, __size);
  [&] {
    for (size_t i = 0; i < __size; i++) {
      system_control::Status::bar(i, __size, tips);
      if constexpr (std::is_same_v<T, bool>) {
        if (gamma[i] != (alpha[i] && (!theta))) {
          std::cout << "\nError: bad answer when i= " << i << '\n';
          LOG("E:error answer");
          return;
        }
      } else {
        if (gamma[i] != (alpha[i] - theta)) {
          std::cout << "\nError: bad answer when i= " << i << '\n';
          LOG("E:error answer");
          return;
        }
      }
    }
    system_control::Status::bar(1, 1);
    std::cout << "\nOperate success!\n";
    return;
  }();
  std::cout << "cuda in scl - vec:\n";
  basic_math::mns<T, true>(phi, beta, gamma, __size);
  [&] {
    for (size_t i = 0; i < __size; i++) {
      system_control::Status::bar(i, __size, tips);
      if constexpr (std::is_same_v<T, bool>) {
        if (gamma[i] != (phi && (!beta[i]))) {
          std::cout << "\nError: bad answer when i= " << i << '\n';
          LOG("E:error answer");
          return;
        }
      } else {
        if (gamma[i] != (phi - beta[i])) {
          std::cout << "\nError: bad answer when i= " << i << '\n';
          LOG("E:error answer");
          return;
        }
      }
    }
    system_control::Status::bar(1, 1);
    std::cout << "\nOperate success!\n";
    return;
  }();
  std::clock_t point1, point2, point3;
  point1 = std::clock();
  basic_math::mns<T, true>(alpha, beta, gamma, __size);
  point2 = std::clock();
  basic_math::mns<T, false>(alpha, beta, gamma, __size);
  point3 = std::clock();
  point3 -= point2;
  point2 -= point1;
  std::cout << "GPU use " << point2 << " and CPU use " << point3
            << "\ncuda stress test:\n";
  for (auto i = 0; i < stressLevel__; i++) {
    system_control::Status::bar(i, stressLevel__);
    basic_math::mns<T, true>(alpha, beta, gamma, __size);
  }
  system_control::Status::bar(1, 1);
  std::cout << '\n';
  delete[] alpha;
  delete[] beta;
  delete[] gamma;
}
template <typename T>
inline void testMul(size_t const& __size) noexcept {
  auto alpha = new T[__size];
  auto beta = new T[__size];
  auto gamma = new T[__size];
  T theta, phi;
  if constexpr (std::is_same_v<T, bool>) {
    theta = basic_math::uniformRand<T>(0, 1);
    phi = basic_math::uniformRand<T>(0, 1);
  } else {
    theta = basic_math::uniformRand<T>(0, 5);
    phi = basic_math::uniformRand<T>(0, 5);
  }
  std::string tips("initializing...");
  for (size_t i = 0; i < __size; i++) {
    system_control::Status::bar(i, __size, tips);
    if constexpr (std::is_same_v<T, bool>) {
      alpha[i] = basic_math::uniformRand<T>(0, 1);
      beta[i] = basic_math::uniformRand<T>(0, 1);
    } else {
      alpha[i] = basic_math::uniformRand<T>(0, 5);
      beta[i] = basic_math::uniformRand<T>(0, 5);
    }
  }
  system_control::Status::bar(1, 1);
  std::cout << "\ncuda in vec * vec:\n";
  basic_math::mul<T, true>(alpha, beta, gamma, __size);
  tips = "checking answer...";
  [&] {
    for (size_t i = 0; i < __size; i++) {
      system_control::Status::bar(i, __size, tips);
      if constexpr (std::is_same_v<T, bool>) {
        if (gamma[i] != (alpha[i] && beta[i])) {
          std::cout << "\nError: bad answer when i= " << i << '\n';
          LOG("E:error answer");
          return;
        }
      } else {
        if (gamma[i] != (alpha[i] * beta[i])) {
          std::cout << "\nError: bad answer when i= " << i << '\n';
          LOG("E:error answer");
          return;
        }
      }
    }
    system_control::Status::bar(1, 1);
    std::cout << "\nOperate success!\n";
    return;
  }();
  std::cout << "cuda in vec * scl:\n";
  basic_math::mul<T, true>(alpha, theta, gamma, __size);
  [&] {
    for (size_t i = 0; i < __size; i++) {
      system_control::Status::bar(i, __size, tips);
      if constexpr (std::is_same_v<T, bool>) {
        if (gamma[i] != (alpha[i] && theta)) {
          std::cout << "\nError: bad answer when i= " << i << '\n';
          LOG("E:error answer");
          return;
        }
      } else {
        if (gamma[i] != (alpha[i] * theta)) {
          std::cout << "\nError: bad answer when i= " << i << '\n';
          LOG("E:error answer");
          return;
        }
      }
    }
    system_control::Status::bar(1, 1);
    std::cout << "\nOperate success!\n";
    return;
  }();
  std::cout << "cuda in scl * vec:\n";
  basic_math::mul<T, true>(phi, beta, gamma, __size);
  [&] {
    for (size_t i = 0; i < __size; i++) {
      system_control::Status::bar(i, __size, tips);
      if constexpr (std::is_same_v<T, bool>) {
        if (gamma[i] != (phi && beta[i])) {
          std::cout << "\nError: bad answer when i= " << i << '\n';
          LOG("E:error answer");
          return;
        }
      } else {
        if (gamma[i] != (phi * beta[i])) {
          std::cout << "\nError: bad answer when i= " << i << '\n';
          LOG("E:error answer");
          return;
        }
      }
    }
    system_control::Status::bar(1, 1);
    std::cout << "\nOperate success!\n";
    return;
  }();
  std::clock_t point1, point2, point3;
  point1 = std::clock();
  basic_math::mul<T, true>(alpha, beta, gamma, __size);
  point2 = std::clock();
  basic_math::mul<T, false>(alpha, beta, gamma, __size);
  point3 = std::clock();
  point3 -= point2;
  point2 -= point1;
  std::cout << "GPU use " << point2 << " and CPU use " << point3
            << "\ncuda stress test:\n";
  for (auto i = 0; i < stressLevel__; i++) {
    system_control::Status::bar(i, stressLevel__);
    basic_math::mul<T, true>(alpha, beta, gamma, __size);
  }
  system_control::Status::bar(1, 1);
  std::cout << '\n';
  delete[] alpha;
  delete[] beta;
  delete[] gamma;
}
template <typename T>
inline void testDiv(size_t const& __size) noexcept {
  auto alpha = new T[__size];
  auto beta = new T[__size];
  auto gamma = new T[__size];
  T theta, phi;
  if constexpr (std::is_same_v<T, bool>) {
    theta = basic_math::uniformRand<T>(0, 1);
    phi = basic_math::uniformRand<T>(0, 1);
  } else {
    theta = basic_math::uniformRand<T>(1, 5);
    phi = basic_math::uniformRand<T>(50, 100);
  }
  std::string tips("initializing...");
  for (size_t i = 0; i < __size; i++) {
    system_control::Status::bar(i, __size, tips);
    if constexpr (std::is_same_v<T, bool>) {
      alpha[i] = basic_math::uniformRand<T>(0, 1);
      beta[i] = basic_math::uniformRand<T>(0, 1);
    } else {
      alpha[i] = basic_math::uniformRand<T>(30, 50);
      beta[i] = basic_math::uniformRand<T>(5, 10);
    }
  }
  system_control::Status::bar(1, 1);
  std::cout << "\ncuda in vec / vec:\n";
  basic_math::div<T, true>(alpha, beta, gamma, __size);
  tips = "checking answer...";
  [&] {
    for (size_t i = 0; i < __size; i++) {
      system_control::Status::bar(i, __size, tips);
      if constexpr (std::is_same_v<T, bool>) {
        if (gamma[i] != (alpha[i] ^ beta[i])) {
          std::cout << "\nError: bad answer when i= " << i << '\n';
          LOG("E:error answer");
          return;
        }
      } else {
        if (gamma[i] != (alpha[i] / beta[i])) {
          std::cout << "\nError: bad answer when i= " << i << '\n';
          LOG("E:error answer");
          return;
        }
      }
    }
    system_control::Status::bar(1, 1);
    std::cout << "\nOperate success!\n";
    return;
  }();
  std::cout << "cuda in vec / scl:\n";
  basic_math::div<T, true>(alpha, theta, gamma, __size);
  [&] {
    for (size_t i = 0; i < __size; i++) {
      system_control::Status::bar(i, __size, tips);
      if constexpr (std::is_same_v<T, bool>) {
        if (gamma[i] != (alpha[i] ^ theta)) {
          std::cout << "\nError: bad answer when i= " << i << '\n';
          LOG("E:error answer");
          return;
        }
      } else {
        if (gamma[i] != (alpha[i] / theta)) {
          std::cout << "\nError: bad answer when i= " << i << '\n';
          LOG("E:error answer");
          return;
        }
      }
    }
    system_control::Status::bar(1, 1);
    std::cout << "\nOperate success!\n";
    return;
  }();
  std::cout << "cuda in scl / vec:\n";
  basic_math::div<T, true>(phi, beta, gamma, __size);
  [&] {
    for (size_t i = 0; i < __size; i++) {
      system_control::Status::bar(i, __size, tips);
      if constexpr (std::is_same_v<T, bool>) {
        if (gamma[i] != (phi ^ beta[i])) {
          std::cout << "\nError: bad answer when i= " << i << '\n';
          LOG("E:error answer");
          return;
        }
      } else {
        if (gamma[i] != (phi / beta[i])) {
          std::cout << "\nError: bad answer when i= " << i << '\n';
          LOG("E:error answer");
          return;
        }
      }
    }
    system_control::Status::bar(1, 1);
    std::cout << "\nOperate success!\n";
    return;
  }();
  std::clock_t point1, point2, point3;
  point1 = std::clock();
  basic_math::div<T, true>(alpha, beta, gamma, __size);
  point2 = std::clock();
  basic_math::div<T, false>(alpha, beta, gamma, __size);
  point3 = std::clock();
  point3 -= point2;
  point2 -= point1;
  std::cout << "GPU use " << point2 << " and CPU use " << point3
            << "\ncuda stress test:\n";
  for (auto i = 0; i < stressLevel__; i++) {
    system_control::Status::bar(i, stressLevel__);
    basic_math::div<T, true>(alpha, beta, gamma, __size);
  }
  system_control::Status::bar(1, 1);
  std::cout << '\n';
  delete[] alpha;
  delete[] beta;
  delete[] gamma;
}
template <typename T>
inline void testHV(size_t const& __size) {
  size_t lenth = std::sqrt(__size);
  lina_lg::Matrix<T> alpha({lenth, lenth});
  lina_lg::Vector<T> beta(lenth), gamma(lenth);
  for (auto& i : alpha) i = basic_math::uniformRand<T>(0, 1);
  std::cout << "horizontal sum:\n";
  basic_math::hSum<T, true>(alpha.begin(), static_cast<void*>(beta.begin()),
                            lenth, lenth);
  basic_math::hSum<T, false>(alpha.begin(), static_cast<void*>(gamma.begin()),
                             lenth, lenth);
  check(beta.begin(), gamma.begin(), lenth);
  std::cout << "vertical sum:\n";
  beta = 0;
  gamma = 0;
  basic_math::vSum<T, true>(alpha.begin(), static_cast<void*>(beta.begin()),
                            lenth, lenth);
  basic_math::vSum<T, false>(alpha.begin(), static_cast<void*>(gamma.begin()),
                             lenth, lenth);
  check(beta.begin(), gamma.begin(), lenth);

  std::clock_t point1, point2, point3;
  point1 = std::clock();
  basic_math::hSum<T, true>(alpha.begin(), static_cast<void*>(beta.begin()),
                            lenth, lenth);
  point2 = std::clock();
  basic_math::hSum<T, false>(alpha.begin(), static_cast<void*>(gamma.begin()),
                             lenth, lenth);
  point3 = std::clock();
  point3 -= point2;
  point2 -= point1;
  std::cout << "in horizontal, GPU use " << point2 << " and CPU use " << point3;
  point1 = std::clock();
  basic_math::vSum<T, true>(alpha.begin(), static_cast<void*>(beta.begin()),
                            lenth, lenth);
  point2 = std::clock();
  basic_math::vSum<T, false>(alpha.begin(), static_cast<void*>(gamma.begin()),
                             lenth, lenth);
  point3 = std::clock();
  point3 -= point2;
  point2 -= point1;
  std::cout << "\nin vertical, GPU use " << point2 << " and CPU use " << point3
            << "\ncuda stress test\n";
  for (auto i = 0; i < stressLevel__; i++) {
    system_control::Status::bar(i, stressLevel__);
    beta = 0;
    gamma = 0;
    basic_math::hSum<T, true>(alpha.begin(), static_cast<void*>(beta.begin()),
                              lenth, lenth);
    beta = 0;
    gamma = 0;
    basic_math::vSum<T, true>(alpha.begin(), static_cast<void*>(beta.begin()),
                              lenth, lenth);
  }
  system_control::Status::bar(1, 1);
  std::cout << '\n';
  return;
}
template <>
inline void testHV<bool>(size_t const& __size) {
  size_t lenth = std::sqrt(__size);
  lina_lg::Matrix<bool> alpha({lenth, lenth});
  lina_lg::Vector<size_t> beta(lenth), gamma(lenth);
  for (auto& i : alpha) i = basic_math::uniformRand<bool>(0, 1);
  std::cout << "horizontal sum:\n";
  basic_math::hSum<bool, true>(alpha.begin(), static_cast<void*>(beta.begin()),
                               lenth, lenth);
  basic_math::hSum<bool, false>(
      alpha.begin(), static_cast<void*>(gamma.begin()), lenth, lenth);
  check(beta.begin(), gamma.begin(), lenth);
  std::cout << "vertical sum:\n";
  beta = 0;
  gamma = 0;
  basic_math::vSum<bool, true>(alpha.begin(), static_cast<void*>(beta.begin()),
                               lenth, lenth);
  basic_math::vSum<bool, false>(
      alpha.begin(), static_cast<void*>(gamma.begin()), lenth, lenth);
  check(beta.begin(), gamma.begin(), lenth);

  std::clock_t point1, point2, point3;
  point1 = std::clock();
  basic_math::hSum<bool, true>(alpha.begin(), static_cast<void*>(beta.begin()),
                               lenth, lenth);
  point2 = std::clock();
  basic_math::hSum<bool, false>(
      alpha.begin(), static_cast<void*>(gamma.begin()), lenth, lenth);
  point3 = std::clock();
  point3 -= point2;
  point2 -= point1;
  std::cout << "in horizontal, GPU use " << point2 << " and CPU use " << point3;
  point1 = std::clock();
  basic_math::vSum<bool, true>(alpha.begin(), static_cast<void*>(beta.begin()),
                               lenth, lenth);
  point2 = std::clock();
  basic_math::vSum<bool, false>(
      alpha.begin(), static_cast<void*>(gamma.begin()), lenth, lenth);
  point3 = std::clock();
  point3 -= point2;
  point2 -= point1;
  std::cout << "\nin vertical, GPU use " << point2 << " and CPU use " << point3
            << "\ncuda stress test\n";
  for (auto i = 0; i < stressLevel__; i++) {
    system_control::Status::bar(i, stressLevel__);
    beta = 0;
    gamma = 0;
    basic_math::hSum<bool, true>(
        alpha.begin(), static_cast<void*>(beta.begin()), lenth, lenth);
    beta = 0;
    gamma = 0;
    basic_math::vSum<bool, true>(
        alpha.begin(), static_cast<void*>(beta.begin()), lenth, lenth);
  }
  system_control::Status::bar(1, 1);
  std::cout << '\n';
  return;
}
template <typename T>
inline void testDot(size_t const& __size) noexcept {
  size_t lenth = std::sqrt(__size);
  lina_lg::Matrix<T> alpha, beta, gamma, delta;
  alpha.resize({lenth, lenth});
  beta.resize(alpha.shape());
  gamma.resize(alpha.shape());
  delta.resize(alpha.shape());
  gamma = 0;
  delta = 0;
  for (auto& i : alpha) i = basic_math::uniformRand<T>(0, 2);
  for (auto& i : beta) i = basic_math::uniformRand<T>(0, 2);
  std::cout << "matrix dot:\n";
  basic_math::mDot<T, false>(alpha.begin(), beta.begin(), gamma.begin(), lenth,
                             lenth, lenth);
  basic_math::mDot<T, true>(alpha.begin(), beta.begin(), delta.begin(), lenth,
                            lenth, lenth);
  check(delta.begin(), gamma.begin(), lenth * lenth);
  gamma = 0;
  delta = 0;

  std::clock_t point1, point2, point3;
  point1 = std::clock();
  basic_math::mDot<T, true>(alpha.begin(), beta.begin(), delta.begin(), lenth,
                            lenth, lenth);
  point2 = std::clock();
  basic_math::mDot<T, false>(alpha.begin(), beta.begin(), gamma.begin(), lenth,
                             lenth, lenth);
  point3 = std::clock();
  point3 -= point2;
  point2 -= point1;
  std::cout << "GPU use " << point2 << " and CPU use " << point3
            << "\ncuda stress test\n";
  for (auto i = 0; i < stressLevel__ / 10; i++) {
    system_control::Status::bar(i, stressLevel__ / 10);
    delta = 0;
    gamma = 0;
    basic_math::mDot<T, true>(alpha.begin(), beta.begin(), delta.begin(), lenth,
                              lenth, lenth);
  }
  system_control::Status::bar(1, 1);
  std::cout << '\n';
  return;
}