#include "interface.hpp"

#define SHOW(X) std::cout << #X << ":\n" << X << std::endl;

namespace test_network_cc {
constexpr size_t TIMES = 2;
constexpr size_t INPUTS = 15;
constexpr size_t CORE_1 = 18;
constexpr size_t CORE_2 = 10;
}  // namespace test_network_cc
namespace tncc = test_network_cc;
signed main() {
  CONSTRUCT;
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
  file_io::FileIOOrdered trainDatas, standardAns;
  file_io::FileIO weightFile;
  lina_lg::MatrixF alpha;
  lina_lg::VectorF temp;
  input.set(tncc::INPUTS, tncc::TIMES);
  layer1.set(tncc::CORE_1, tncc::INPUTS);
  layer3.set(tncc::CORE_2, tncc::CORE_1);
  [&] {
    bool retrain;
    std::cout << "retrain?\n";
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
  trainDatas.setFile(__FILE__, "in");
  standardAns.setFile(__FILE__, "out");
  trainDatas.switchMode(file_io::FileIOOrdered::reading);
  standardAns.switchMode(file_io::FileIOOrdered::reading);
  system_message::Status::refresh("training");
  system_message::Status::print();
  while (input.forward(trainDatas, alpha)) {
    system_message::Status::announce("a new train");
    tidy.forward(alpha);
    layer1.forward(alpha);
    layer2.forward(alpha);
    tidy.forward(alpha);
    layer3.forward(alpha);
    layer4.forward(alpha);
    layer5.forward(alpha);
    std::cout << "the answer is:\n" << alpha;
    system_message::Status::announce("backward");
    temp = loss.backward(standardAns, alpha);
    std::cout << "\nthe loss is:\n" << temp << '\n';
    layer5.backward(alpha);
    layer4.backward(alpha);
    layer3.backward(alpha);
    tidy.backward(alpha);
    layer2.backward(alpha);
    layer1.backward(alpha);
  }
  weightFile.switchMode(file_io::FileIO::writing);
  layer1.write("layer1", weightFile);
  layer3.write("layer3", weightFile);
  weightFile.switchMode();
  DESTRUCT;
}