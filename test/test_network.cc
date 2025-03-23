#include "interface.hpp"

#define SHOW(X) std::cout << #X << ":\n" << X << std::endl;
#define PAUSE system_message::Status::pause();
#if __DEBUG_MODE__
#define PAUSED PAUSE
#else
#define PAUSED
#endif

namespace test_network_cc {
constexpr size_t WIDE = 3;
constexpr size_t TIMES = 2;
constexpr size_t INPUTS = 15;
constexpr size_t CORE_1 = 18;
constexpr size_t CORE_2 = 10;
char* TEMP;
inline void getInput(FloatType* const& __ptr) {
  char c;
  for (size_t i = 0, j = 0; i < INPUTS; i++, j++) {
    if (j == WIDE) {
      std::cin.get();
      j = 0;
    }
    std::cin.get(c);
    __ptr[i] = static_cast<FloatType>(c - '0');
  }
  std::cin.get();
  return;
}
inline void print(FloatType* const& __ptr) {
  for (size_t i = 0, j = 0; i < INPUTS; i++, j++) {
    if (j == WIDE) {
      std::cout << '\n';
      j = 0;
    }
    std::cout << __ptr[i];
  }
  std::cout << '\n';
  return;
}
}  // namespace test_network_cc
namespace tncc = test_network_cc;
signed main() {
  CONSTRUCT;
  size_t times;
  tncc::TEMP = new char[log_file::FORMAT_LENTH];
  system_message::Status::announce(
      "This is a test for natrual network,\nwith differ the shape of numbers.");
  system_message::Status::refresh("setting");
  system_message::Status::print();
  network::Input input;
  network::Tidy tidy;
  network::Affine layer1;
  network::Tanh layer2;
  network::Affine layer3;
  network::Sigmoid layer4;
  network::SoftMax layer5;
  network::MSE loss;
  network::Input output;
  file_io::FileIOOrdered trainDatas, standardAns;
  file_io::FileIO weightFile;
  lina_lg::MatrixF alpha;
  lina_lg::MatrixF beta;
  lina_lg::VectorF temp;
  input.set(tncc::INPUTS, tncc::TIMES);
  layer1.set(tncc::CORE_1, tncc::INPUTS);
  layer3.set(tncc::CORE_2, tncc::CORE_1);
  output.set(tncc::CORE_2, tncc::TIMES);
  loss.set();
  trainDatas.setFile(__FILE__, "in");
  standardAns.setFile(__FILE__, "out");
  weightFile.setFile(__FILE__,"weight");
  PAUSE;
  [&] {
    bool retrain;
    std::cout << "retrain?(1,0)\n";
    std::cin >> retrain;
    std::cin.get();
    if (retrain) {
      layer1.init();
      layer3.init();
    } else {
      weightFile.switchMode(file_io::FileIO::reading);
      layer1.read("layer1", weightFile);
      layer3.read("layer3", weightFile);
    }
  }();
  trainDatas.switchMode(file_io::FileIOOrdered::reading);
  standardAns.switchMode(file_io::FileIOOrdered::reading);
  std::cout << "How many times? ";
  std::cin >> times;
  std::cin.get();
  PAUSE;
  system_message::Status::refresh("training");
  system_message::Status::print();
  for (size_t i = 0; i < times; i += tncc::TIMES) {
    if (!input.forward(trainDatas, alpha)) break;
    PAUSED;
    sprintf(tncc::TEMP, "The [%ld,%ld] of %ld", i + 1, i + tncc::TIMES, times);
    system_message::Status::announce(tncc::TEMP);
    tidy.forward(alpha);
    PAUSED;
    layer1.forward(alpha);
    PAUSED;
    layer2.forward(alpha);
    PAUSED;
    tidy.forward(alpha);
    PAUSED;
    layer3.forward(alpha);
    PAUSED;
    layer4.forward(alpha);
    PAUSED;
    layer5.forward(alpha);
    std::cout << "the answer is:\n" << alpha;
    PAUSED;
    system_message::Status::announce("backward");
    output.forward(standardAns, beta);
    temp = loss.backward(beta, alpha);
    std::cout << "\nthe loss is:\n" << temp << '\n';
    PAUSED;
    layer5.backward(alpha);
    PAUSED;
    layer4.backward(alpha);
    PAUSED;
    layer3.backward(alpha);
    PAUSED;
    tidy.backward(alpha);
    PAUSED;
    layer2.backward(alpha);
    PAUSED;
    layer1.backward(alpha);
    system_message::Status::announce("end a train");
  }
  system_message::Status::refresh("writing the files");
  system_message::Status::print();
  weightFile.switchMode(file_io::FileIO::writing);
  if (!(layer1.write("layer1", weightFile) &&
        layer3.write("layer3", weightFile))) {
    system_message::Status::announce("Fail to write");
  }
  weightFile.switchMode();
  system_message::Status::refresh("test for learning result");
  system_message::Status::print();
  FloatType testBuffer[tncc::INPUTS];
  std::cout << "test how many times?";
  std::cin >> times;
  std::cin.get();
  for (size_t i = 0; i < times; i++) {
    PAUSE;
    system_message::Status::announce("test");
    std::cout << "put datas:\n";
    tncc::getInput(testBuffer);
    std::cout << "the datas is:\n";
    tncc::print(testBuffer);
    alpha.load({tncc::INPUTS, 1}, testBuffer);
    tidy.forward(alpha);
    layer1.forward(alpha);
    layer2.forward(alpha);
    tidy.forward(alpha);
    layer3.forward(alpha);
    layer4.forward(alpha);
    layer5.forward(alpha);
    std::cout << "the answer is:\n" << alpha << '\n';
  }
  delete[] tncc::TEMP;
  DESTRUCT;
}