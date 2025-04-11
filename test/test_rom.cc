#include "interface.hpp"

#define IO(X)                                     \
  do {                                            \
    std::cout << "put value of " << #X << " :\n"; \
    std::cin >> (X);                              \
  } while (false);
#define SHOW(X)                                   \
  do {                                            \
    std::cout << #X << " = " << (X) << std::endl; \
  } while (false);

signed main() {
  CONSTRUCT;
  if constexpr (false) {
    try {
      std::string s;
      system_message::Status::refresh("try function between num and string");
      system_message::Status::print();
      [&](bool __skip) {
        if (__skip) return;
        system_message::Status::announce("int");
        int alpha;
        IO(alpha);
        file_io::numToString(s, alpha);
        SHOW(s);
        file_io::stringToNum(s, alpha);
        SHOW(alpha);
      }(true);
      [&](bool __skip) {
        if (__skip) return;
        system_message::Status::announce("unsigned int");
        unsigned int alpha;
        IO(alpha);
        file_io::numToString(s, alpha);
        SHOW(s);
        file_io::stringToNum(s, alpha);
        SHOW(alpha);
      }(true);
      [&](bool __skip) {
        if (__skip) return;
        system_message::Status::announce("long long");
        long long alpha;
        IO(alpha);
        file_io::numToString(s, alpha);
        SHOW(s);
        file_io::stringToNum(s, alpha);
        SHOW(alpha);
      }(true);
      [&](bool __skip) {
        if (__skip) return;
        system_message::Status::announce("unsigned long long");
        unsigned long long alpha;
        IO(alpha);
        file_io::numToString(s, alpha);
        SHOW(s);
        file_io::stringToNum(s, alpha);
        SHOW(alpha);
      }(true);
      [&](bool __skip) {
        if (__skip) return;
        system_message::Status::announce("float");
        float alpha;
        IO(alpha);
        file_io::numToString(s, alpha);
        SHOW(s);
        file_io::stringToNum(s, alpha);
        SHOW(alpha);
      }(false);
      [&](bool __skip) {
        if (__skip) return;
        system_message::Status::announce("double");
        double alpha;
        IO(alpha);
        file_io::numToString(s, alpha);
        SHOW(s);
        file_io::stringToNum(s, alpha);
        SHOW(alpha);
      }(false);
      [&](bool __skip) {
        if (__skip) return;
        system_message::Status::announce("bool");
        bool alpha;
        IO(alpha);
        file_io::numToString(s, alpha);
        SHOW(s);
        file_io::stringToNum(s, alpha);
        SHOW(alpha);
      }(true);
    } catch (system_message::Error& __epsilon) {
      __epsilon.print();
    }
  }
  if constexpr (false) {
    system_message::Status::refresh("try rom io");
    system_message::Status::print();
    file_io::FileIO file;
    try {
      [&] {
        system_message::Status::announce("<set file> function of RomIO");
        file.setFile(__FILE__, "in");
        file.print();
      }();
    } catch (system_message::Error& __epsilon) {
      __epsilon.print();
    }
    try {
      [&] {
        system_message::Status::announce("<writing file> function of RomIO 01");
        file.switchMode(file_io::FileIO::writing);
        file.print();
        auto alpha = basic_math::uniformRand(8, -5, 5);
        SHOW(alpha);
        SHOW(file.write("alpha", alpha.begin(), alpha.size()));
      }();
    } catch (system_message::Error& __epsilon) {
      __epsilon.print();
    }
    try {
      [&] {
        system_message::Status::announce("<writing file> function of RomIO 02");
        file.switchMode(file_io::FileIO::writing);
        file.print();
        auto beta = basic_math::uniformRand(15, -7, 7);
        SHOW(beta);
        SHOW(file.write("beta", beta.begin(), beta.size()));
      }();
    } catch (system_message::Error& __epsilon) {
      __epsilon.print();
    }
    try {
      [&] {
        system_message::Status::announce("<reading file> function of RomIO");
        file.switchMode(file_io::FileIO::reading);
        file.print();
        lina_lg::Vector<int> beta;
        beta.resize(15);
        SHOW(beta);
        SHOW(file.read("beta", beta.begin(), beta.size()));
        SHOW(beta);
      }();
    } catch (system_message::Error& __epsilon) {
      __epsilon.print();
    }
    try {
      [&] {
        system_message::Status::announce("<reading file> function of RomIO");
        file.switchMode(file_io::FileIO::reading);
        file.print();
        lina_lg::Vector<int> alpha;
        alpha.resize(8);
        SHOW(alpha);
        SHOW(file.read("alpha", alpha.begin(), alpha.size()));
        SHOW(alpha);
      }();
    } catch (system_message::Error& __epsilon) {
      __epsilon.print();
    }

    file.switchMode();
    file.print();
  }
  if constexpr (true) {
    system_message::Status::refresh("File IO Ordered");
    system_message::Status::print();
    file_io::FileIOOrdered orderFile;
    orderFile.setFile(__FILE__, "order");
    orderFile.print();
    [&] {
      system_message::Status::announce("write file");
      auto alpha = basic_math::uniformRand(8, -5, 5);
      SHOW(alpha);
      auto beta = basic_math::uniformRand(15, -5.0F, 5.0F);
      SHOW(beta);
      orderFile.switchMode(file_io::FileIOOrdered::writing);
      orderFile.print();
      orderFile.write(alpha.begin(), alpha.size());
      orderFile.write(beta.begin(), beta.size());
    }();
    [&] {
      system_message::Status::announce("read file");
      lina_lg::Vector<int> alpha(8);
      lina_lg::Vector<float> beta(15);
      SHOW(alpha);
      SHOW(beta);
      orderFile.switchMode(file_io::FileIOOrdered::reading);
      orderFile.print();
      orderFile.read(alpha.begin(), alpha.size());
      orderFile.read(beta.begin(), beta.size());
      SHOW(alpha);
      SHOW(beta);
    }();
    orderFile.switchMode();
    orderFile.print();
  }
  DESTRUCT;
}