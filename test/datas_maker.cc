#include "interface.hpp"

namespace datas_maker_cc {
constexpr size_t WIDE = 3;
constexpr size_t HIGHT = 5;
constexpr size_t INPUT = WIDE * HIGHT;
constexpr size_t OUTPUT = 10;
}  // namespace datas_maker_cc
namespace dmcc = datas_maker_cc;

inline void getInput(FloatType* const&);

signed main() {
  CONSTRUCT;
  system_control::Status::announce(
      "This is the datas maker of file:\ntest_network.cc");
  file_io::FileIOOrdered inputFile, outputFile;
  inputFile.setFile("./test_network.cc", "in");
  outputFile.setFile("./test_network.cc", "out");
  [&] {
    char c;
    std::cout << "override? (y/n)\n";
    std::cin.get(c);
    std::cin.get();
    if (c == 'y') {
      inputFile.switchMode(file_io::FileIOOrdered::writing);
      outputFile.switchMode(file_io::FileIOOrdered::writing);
    } else {
      inputFile.switchMode(file_io::FileIOOrdered::writing, true);
      outputFile.switchMode(file_io::FileIOOrdered::writing, true);
    }
  }();
  size_t times, position;
  char c;
  std::cout << "put the times:\n";
  std::cin >> times;
  std::cout << "times= " << times << '\n';

  auto input = new FloatType[dmcc::INPUT], output = new FloatType[dmcc::OUTPUT];
  for (size_t i = 0; i < times; i++) {
  START:
    std::cout << "\nThe " << i + 1 << " of " << times
              << "\nput the standard answer:\n";
    std::cin >> position;
    std::cin.get();
    for (size_t w = 0; w < dmcc::OUTPUT; w++) {
      output[w] = static_cast<FloatType>(0);
      if (w == position) output[w] = static_cast<FloatType>(1);
    }
    getInput(input);
    for (auto k = 0; k < 20; k++) std::cout << '-';
    std::cout << "\ncheck the datas:\n";
    for (size_t w = 0, g = 0; w < dmcc::INPUT; w++, g++) {
      if (g == dmcc::WIDE) {
        std::cout << '\n';
        g = 0;
      }
      std::cout << input[w];
    }
    std::cout << "\nanswer:\n";
    for (size_t w = 0; w < dmcc::OUTPUT; w++) {
      std::cout << output[w];
    }
    std::cout << '\n';
    for (auto k = 0; k < 20; k++) {
      std::cout << '-';
    }
    std::cout << "\nput in? (y/n)\n";
    std::cin.get(c);
    std::cin.get();
    if (c == 'y') {
      inputFile.write(input, dmcc::INPUT);
      outputFile.write(output, dmcc::OUTPUT);
    } else {
      goto START;
    }
  }
  delete[] input;
  delete[] output;
  DESTRUCT;
}

inline void getInput(FloatType* const& __ptr) {
  char c;
  for (size_t i = 0, j = 0; i < dmcc::INPUT; i++, j++) {
    if (j == dmcc::WIDE) {
      std::cin.get();
      j = 0;
    }
    std::cin.get(c);
    __ptr[i] = static_cast<FloatType>(c - '0');
  }
  std::cin.get();
  return;
}