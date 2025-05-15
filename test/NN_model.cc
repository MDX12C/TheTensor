#include "interface.hpp"

namespace mdcc {
constexpr size_t INPUT = 784;
constexpr size_t CORE_1 = 75;
constexpr size_t CORE_2 = 40;
constexpr size_t BATCH = 100;
char* buffer_;
}  // namespace mdcc
signed main() {
  CONSTRUCT;
  mdcc::buffer_ = new char[100];

  system_control::Status::refresh("set", true);
  network::LinearModel model;
  model.setName("NerualNetwork");
  model.inFile().setFile("/mnist.", "train_images");
  model.inFile().switchMode(file_io::FileIOOrdered::reading);
  model.outFile().setFile("/mnist.", "train_labels");
  model.outFile().switchMode(file_io::FileIOOrdered::reading);
  model.weightFile().setFile("/model.", "weight");
  model.weightFile().switchMode(file_io::FileIO::reading);
  model.setFlatInput(mdcc::INPUT, mdcc::BATCH);
  int skip;
  std::cout << "read file?";
  std::cin >> skip;
  if (skip > 0) {
    model.addDense(mdcc::CORE_1, network::LayerBase::relu,
                   network::Dense::readFile);
    model.addDense(mdcc::CORE_2, network::LayerBase::sigmoid,
                   network::Dense::readFile);
  } else {
    model.addDense(mdcc::CORE_1, network::LayerBase::relu);
    model.addDense(mdcc::CORE_2, network::LayerBase::sigmoid);
  }
  model.addSoftMax();
  model.setFlatOutput(mdcc::BATCH);
  model.setLossFunction(network::meanSquareError);
  system_control::Status::announce("end setting");

  size_t times = 0;
  if (skip > 0) {
    std::cout << "skip train?";
    std::cin >> skip;
  } else {
    skip = 0;
  }
  [&]() -> void {
    if (skip > 0) return;
    do {
      int a;
      std::cout << "put times:";
      std::cin >> a;
      if (a > 0) times = a;
    } while (!times);
    std::string str;
    system_control::Status::refresh("train", true);
    model.counter() = 0;
    FloatType alpha;
    for (size_t i = 0; i < times; i += mdcc::BATCH) {
      system_control::Status::bar(i, times, str);
      if (!model.forward()) break;
      alpha = model.loss();
      file_io::numToString(str, alpha);
      str = std::move("mean loss= " + str);
      model.backward();
    }
    system_control::Status::bar(1, 1);
    std::cout << '\n';
    model.weightFile().switchMode(file_io::FileIO::writing);
    if (model.write())
      std::cout << "write success!\n";
    else
      std::cout << "write fail!\n";
  }();

  times = 0;
  do {
    int a;
    std::cout << "put times:";
    std::cin >> a;
    if (a > 0) times = a;
  } while (!times);
  system_control::Status::refresh("test", true);
  model.counter() = 0;
  model.inFile().setFile("/mnist.", "train_images");
  model.inFile().switchMode();
  model.inFile().switchMode(file_io::FileIOOrdered::reading);
  model.outFile().setFile("/mnist.", "train_labels");
  model.outFile().switchMode();
  model.outFile().switchMode(file_io::FileIOOrdered::reading);
  for (size_t i = 0; i < times; i += mdcc::BATCH) {
    system_control::Status::bar(i, times);
    if (!model.forward()) break;
    model.loss(true);
  }
  system_control::Status::bar(1, 1);
  std::cout << '\n';
  sprintf(mdcc::buffer_, "the accuracy is %.3f",
          (static_cast<float>(model.counter()) / times) * 100);
  system_control::Status::announce(mdcc::buffer_);

  delete[] mdcc::buffer_;
  DESTRUCT;
}
