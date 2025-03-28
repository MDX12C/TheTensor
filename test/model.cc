#include "interface.hpp"

#define SHOW(X) std::cout << #X << ":\n" << X << std::endl;
#define PAUSE system_message::Status::pause();
#if __DEBUG_MODE__
#define PAUSED PAUSE
#else
#define PAUSED
#endif

namespace model_cc {
constexpr size_t TIMES = 50;
constexpr size_t INPUTS = 28 * 28;
constexpr size_t CORE_1 = 30;
constexpr size_t CORE_2 = 20;
constexpr size_t CORE_3 = 10;
char* TEMP;
auto IO_FUNC = [](const char* const& __str) -> size_t {
  std::cout << "===\nNow will do " << __str << ", how many?\n";
  int alpha;
  std::cin >> alpha;
  std::cin.get();
  std::cout << "===\n";
  return static_cast<size_t>(alpha);
};
auto CHECK_CONTINUE = [](const char* const& __str) {
  char c;
  std::cout << "===\nContinue to " << __str << "? (y/n)\n";
  std::cin.get(c);
  std::cin.get();
  if (c != 'y') endOfMainFunction();
};
}  // namespace model_cc
namespace mdcc = model_cc;
using sys = system_message::Status;
signed main() {
  CONSTRUCT;
  size_t times = 0, kid = 0, mother = 0;
  mdcc::TEMP = new char[log_file::FORMAT_LENTH];
  sys::announce("Natural Network, differ numbers' shape.");
  system_message::Status::refresh("setting");
  system_message::Status::print();
  network::Input layerIn;
  network::Affine layer1;
  network::Tanh layer2;
  network::Affine layer3;
  network::Tanh layer4;
  network::Affine layer5;
  network::Sigmoid layer6;
  network::SoftMax layer7;
  network::Tidy layerTidy;
  network::MSE layerLoss;
  network::Input layerOut;
  file_io::FileIOOrdered inputData, outputData;
  file_io::FileIO weightData;
  lina_lg::MatrixF alpha, beta;
  lina_lg::VectorF gamma;
  layerIn.set(mdcc::INPUTS, mdcc::TIMES);
  layer1.set(mdcc::CORE_1, mdcc::INPUTS);
  layer3.set(mdcc::CORE_2, mdcc::CORE_1);
  layer5.set(mdcc::CORE_3, mdcc::CORE_2);
  layerOut.set(mdcc::CORE_3, mdcc::TIMES);
  layerLoss.set();
  inputData.setFile(__FILE__, "train_images");
  outputData.setFile(__FILE__, "train_labels");
  weightData.setFile(__FILE__, "weight");
  PAUSE;
  [&] {
    bool retrain;
    std::cout << "retrain?(1,0)\n";
    std::cin >> retrain;
    std::cin.get();
    if (retrain) {
      layer1.init();
      layer3.init();
      layer5.init();
    } else {
      weightData.switchMode(file_io::FileIO::reading);
      layer1.read("layer1", weightData);
      layer3.read("layer3", weightData);
      layer5.read("layer5", weightData);
      weightData.switchMode();
    }
  }();
  inputData.switchMode(file_io::FileIOOrdered::reading);
  outputData.switchMode(file_io::FileIOOrdered::reading);
  do {
    times = mdcc::IO_FUNC("train");
  } while (!times);
  PAUSE;
  sys::refresh("training");
  sys::print();
  for (size_t i = 0; i < times; i += mdcc::TIMES) {
    if (!layerIn.forward(inputData, alpha)) break;
    PAUSED;
    sprintf(mdcc::TEMP, "The [%ld,%ld] of %ld", i + 1, i + mdcc::TIMES, times);
    system_message::Status::announce(mdcc::TEMP);
    layerTidy.forward(alpha);
    PAUSED;
    layer1.forward(alpha);
    PAUSED;
    layer2.forward(alpha);
    PAUSED;
    layerTidy.forward(alpha);
    PAUSED;
    layer3.forward(alpha);
    PAUSED;
    layer4.forward(alpha);
    PAUSED;
    layerTidy.forward(alpha);
    PAUSED;
    layer5.forward(alpha);
    PAUSED;
    layer6.forward(alpha);
    PAUSED;
    layer7.forward(alpha);
    PAUSED;
    sys::announce("backward");
    layerOut.forward(outputData, beta);
    mother += mdcc::TIMES;
    kid += static_cast<size_t>((beta * network::Output::format(alpha)).sum());
    gamma = std::move(layerLoss.backward(beta, alpha));
    std::cout << "\nLoss:\n" << gamma << '\n';
    PAUSED;
    layer7.backward(alpha);
    PAUSED;
    layer6.backward(alpha);
    PAUSED;
    layer5.backward(alpha);
    PAUSED;
    layerTidy.backward(alpha);
    PAUSED;
    layer4.backward(alpha);
    PAUSED;
    layer3.backward(alpha);
    PAUSED;
    layerTidy.backward(alpha);
    PAUSED;
    layer2.backward(alpha);
    PAUSED;
    layer1.backward(alpha);
    sys::announce("end a train");
  }
  inputData.switchMode();
  outputData.switchMode();
  sprintf(mdcc::TEMP, "The accuracy is %.2f%%", (float(kid) / mother) * 100);
  sys::announce(mdcc::TEMP);
  mdcc::CHECK_CONTINUE("write weight file");
  sys::refresh("writing the weight file");
  sys::print();
  weightData.switchMode(file_io::FileIO::writing);
  if (layer1.write("layer1", weightData) & layer5.write("layer5", weightData) &
      layer3.write("layer3", weightData))
    sys::announce("write success!");
  else
    sys::announce("write fail!");
  weightData.switchMode();
  mdcc::CHECK_CONTINUE("test the training result");
  times = 0;
  do {
    times = mdcc::IO_FUNC("test");
  } while (!times);
  sys::refresh("test for learning result");
  sys::print();
  kid = mother = 0;
  inputData.setFile(__FILE__, "test_images");
  outputData.setFile(__FILE__, "test_labels");
  inputData.switchMode(file_io::FileIOOrdered::reading);
  outputData.switchMode(file_io::FileIOOrdered::reading);
  for (size_t i = 0; i < times; i += mdcc::TIMES) {
    if (!layerIn.forward(inputData, alpha)) break;
    PAUSED;
    sprintf(mdcc::TEMP, "The [%ld,%ld] of %ld", i + 1, i + mdcc::TIMES, times);
    sys::announce(mdcc::TEMP);
    layerTidy.forward(alpha);
    PAUSED;
    layer1.forward(alpha);
    PAUSED;
    layer2.forward(alpha);
    PAUSED;
    layerTidy.forward(alpha);
    PAUSED;
    layer3.forward(alpha);
    PAUSED;
    layer4.forward(alpha);
    PAUSED;
    layerTidy.forward(alpha);
    PAUSED;
    layer5.forward(alpha);
    PAUSED;
    layer6.forward(alpha);
    PAUSED;
    layer7.forward(alpha);
    PAUSED;
    layerOut.forward(outputData, beta);
    mother += mdcc::TIMES;
    kid += static_cast<size_t>((beta * network::Output::format(alpha)).sum());
    gamma = std::move(layerLoss.backward(beta, alpha));
    std::cout << "\nLoss:\n" << gamma << '\n';
    sys::announce("end a test");
  }
  inputData.switchMode();
  outputData.switchMode();
  sprintf(mdcc::TEMP, "The accuracy is %.2f%%", (float(kid) / mother) * 100);
  sys::announce(mdcc::TEMP);
  delete[] mdcc::TEMP;
  DESTRUCT;
}