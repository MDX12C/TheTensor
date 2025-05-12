#include "interface.hpp"

using sys = system_control::Status;
signed main() {
  CONSTRUCT;
  constexpr size_t TIMES = 1E6;
  char* buffer = new char[100];
  auto print = [&](size_t const& __times) {
    for (size_t i = 0; i < __times; i++) std::cout.put('+');
    std::cout << '\n';
    return;
  };
  sys::refresh("uniform random", true);
  [&] {
    sprintf(buffer, "test bool for %ld times", TIMES);
    sys::announce(buffer);
    size_t trueC = 0, falseC = 0;
    for (size_t i = 0; i < TIMES; i++) {
      if (basic_math::uniformRand(false, true))
        trueC++;
      else
        falseC++;
    }
    std::cout << " true: ";
    print(std::round(double(trueC) / 1E4));
    std::cout << "false: ";
    print(std::round(double(falseC) / 1E4));
  }();
  [&] {
    sprintf(buffer, "test interal in [0,9] for %ld times", TIMES);
    sys::announce(buffer);
    size_t count[10] = {0};
    for (size_t i = 0; i < TIMES; i++) count[basic_math::uniformRand(0, 9)]++;
    for (size_t i = 0; i < 10; i++) {
      std::cout << i << ": ";
      print(std::round(double(count[i]) / 2E3));
    }
  }();
  [&] {
    sprintf(buffer, "test floating in [0,10) for %ld times", TIMES);
    sys::announce(buffer);
    size_t count[40] = {0};
    for (size_t i = 0; i < TIMES; i++)
      count[int(std::floor(basic_math::uniformRand(0.0F, 10.0F) * 4))]++;
    for (size_t i = 0; i < 40; i++) {
      printf("in [%5.2f,%5.2f): ", float(i) / 4, float(i) / 4 + 0.25);
      print(double(count[i]) / 2E3);
    }
  }();
  sys::refresh("binomial random", true);
  [&] {
    sprintf(buffer, "test in B[32,0.5]");
    sys::announce(buffer);
    size_t count[32] = {0};
    for (size_t i = 0; i < TIMES; i++)
      count[basic_math::binomialRand(size_t(32), 0.5)]++;
    for (size_t i = 0; i < 32; i++) {
      printf("%2d: ", i);
      print(double(count[i]) / 2E3);
    }
  }();
  [&] {
    sprintf(buffer, "test in B[32,0.2]");
    sys::announce(buffer);
    size_t count[32] = {0};
    for (size_t i = 0; i < TIMES; i++)
      count[basic_math::binomialRand(size_t(32), 0.2)]++;
    for (size_t i = 0; i < 32; i++) {
      printf("%2d: ", i);
      print(double(count[i]) / 2E3);
    }
  }();
  [&] {
    sprintf(buffer, "test in B[32,0.7]");
    sys::announce(buffer);
    size_t count[32] = {0};
    for (size_t i = 0; i < TIMES; i++)
      count[basic_math::binomialRand(size_t(32), 0.7)]++;
    for (size_t i = 0; i < 32; i++) {
      printf("%2d: ", i);
      print(double(count[i]) / 2E3);
    }
  }();
  sys::refresh("normal random", true);
  [&] {
    sprintf(buffer, "test: mean=0, variant=1");
    sys::announce(buffer);
    size_t count[101] = {0};
    int temp;
    for (size_t i = 0; i < TIMES; i++) {
      temp = std::floor(basic_math::normalRand(0.0F, 1.0F) * 20) + 50;
      count[((temp < 100) && (temp >= 0)) ? temp : 100]++;
    }
    temp = 0;
    for (float lower = -2.5; temp < 100; temp++, lower += 0.05) {
      printf("[%4.1f,%4.1f): ", lower, lower + 0.05);
      print(double(count[temp]) / 2E2);
    }
  }();
  [&] {
    sprintf(buffer, "test: mean=1, variant=0.5");
    sys::announce(buffer);
    size_t count[101] = {0};
    int temp;
    for (size_t i = 0; i < TIMES; i++) {
      temp = std::floor(basic_math::normalRand(1.0F, 0.5F) * 20) + 50;
      count[((temp < 100) && (temp >= 0)) ? temp : 100]++;
    }
    temp = 0;
    for (float lower = -2.5; temp < 100; temp++, lower += 0.05) {
      printf("[%4.1f,%4.1f): ", lower, lower + 0.05);
      print(double(count[temp]) / 4E2);
    }
  }();
  [&] {
    sprintf(buffer, "test: mean=0, variant=1.5");
    sys::announce(buffer);
    size_t count[101] = {0};
    int temp;
    for (size_t i = 0; i < TIMES; i++) {
      temp = std::floor(basic_math::normalRand(0.0F, 1.5F) * 10) + 50;
      count[((temp < 100) && (temp >= 0)) ? temp : 100]++;
    }
    temp = 0;
    for (float lower = -5.0; temp < 100; temp++, lower += 0.1) {
      printf("[%4.1f,%4.1f): ", lower, lower + 0.1);
      print(double(count[temp]) / 5E2);
    }
  }();
  delete[] buffer;
  DESTRUCT;
}