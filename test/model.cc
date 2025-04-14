#include "interface.hpp"
// #define PRINT
namespace mdcc {
constexpr size_t INPUT = 784;
constexpr size_t CORE_1 = 50;
constexpr size_t CORE_2 = 25;
constexpr size_t CORE_3 = 10;
constexpr size_t BATCH = 50;
char* buffer_;
}  // namespace mdcc
signed main() {
  CONSTRUCT;
  mdcc::buffer_ = new char[100];
  system_message::Status::refresh("set", true);
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
  std::cout << "skip train?";
  std::cin >> skip;
  if (skip > 0) {
    model.addDense(mdcc::CORE_1, network::LayerBase::tanh,
                   network::Dense::readFile);
    model.addDense(mdcc::CORE_2, network::LayerBase::tanh,
                   network::Dense::readFile);
    model.addDense(mdcc::CORE_3, network::LayerBase::sigmoid,
                   network::Dense::readFile);
  } else {
    model.addDense(mdcc::CORE_1, network::LayerBase::tanh);
    model.addDense(mdcc::CORE_2, network::LayerBase::tanh);
    model.addDense(mdcc::CORE_3, network::LayerBase::sigmoid);
  }
  model.addSoftMax();
  model.setFlatOutput(mdcc::BATCH);
  model.setLossFunction(network::meanSquareError);
  system_message::Status::announce("end setting");
  size_t times = 0;
  [&]() -> void {
    if (skip > 0) return;
    do {
      int a;
      std::cout << "put times:";
      std::cin >> a;
      if (a > 0) times = a;
    } while (!times);
    system_message::Status::refresh("train", true);
    model.counter() = 0;
    network::OperateType alpha;
    for (size_t i = 0; i < times; i += mdcc::BATCH) {
#ifdef PRINT
      sprintf(mdcc::buffer_, "the [%d,%d] of %d", i + 1, i + mdcc::BATCH,
              times);
      system_message::Status::announce(mdcc::buffer_);
#endif
      if (!model.forward()) break;
      alpha = model.loss();
#ifdef PRINT
      std::cout << "loss=\n"
                << (*dynamic_cast<lina_lg::VectorF*>(alpha)) << '\n';
#endif
      model.backward();
    }
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
  system_message::Status::refresh("test", true);
  model.counter() = 0;
  model.inFile().setFile("/mnist.", "train_images");
  model.inFile().switchMode();
  model.inFile().switchMode(file_io::FileIOOrdered::reading);
  model.outFile().setFile("/mnist.", "train_labels");
  model.outFile().switchMode();
  model.outFile().switchMode(file_io::FileIOOrdered::reading);
  for (size_t i = 0; i < times; i += mdcc::BATCH) {
#ifdef PRINT
    sprintf(mdcc::buffer_, "the [%d,%d] of %d", i + 1, i + mdcc::BATCH, times);
    system_message::Status::announce(mdcc::buffer_);
#endif
    if (!model.forward()) break;
    model.loss(true);
  }
  sprintf(mdcc::buffer_, "the accuracy is %.3f",
          (static_cast<FloatType>(model.counter()) / times) * 100);
  system_message::Status::announce(mdcc::buffer_);
  delete[] mdcc::buffer_;
  DESTRUCT;
}
