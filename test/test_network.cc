#include "interface.hpp"
using sys = system_control::Status;
#define __ANC(X, ...)                \
  sprintf(buffer, X, ##__VA_ARGS__); \
  sys::announce(buffer);
#define ANC(__format, ...) __ANC(__format, ##__VA_ARGS__)

signed main() {
  CONSTRUCT;
  auto buffer = new char[100];
  //=====
  sys::refresh("Basic Test", true);
  ANC("learning rate= %.2f", network::LEARNING_RATE);
  ANC("OperateType == StorageBase* : %d",
      std::is_same_v<network::OperateType, storage::StoryBase*>);
  //=====
  sys::refresh("Tanh Test", true);
  [&] {
    auto layer = new network::Tanh;
    std::cout << "name= " << layer->name();
    auto beta = new lina_lg::MatrixF;
    (*beta) = std::move(basic_math::uniformRand({4, 5}, -5.0F, 5.0F));
    auto alpha = dynamic_cast<network::OperateType>(beta);
    std::cout << "\nbeta:\n" << (*beta) << '\n';
    layer->forward(alpha);
    std::cout << "beta:\n" << (*beta) << '\n';
    layer->backward(alpha);
    std::cout << "beta:\n" << (*beta) << '\n';
    delete layer;
    delete beta;
  }();
  //=====
  sys::refresh("Sigmoid Test", true);
  [&] {
    auto layer = new network::Sigmoid;
    std::cout << "name= " << layer->name();
    auto beta = new lina_lg::MatrixF;
    (*beta) = std::move(basic_math::uniformRand({4, 5}, -5.0F, 5.0F));
    auto alpha = dynamic_cast<network::OperateType>(beta);
    std::cout << "\nbeta:\n" << (*beta) << '\n';
    layer->forward(alpha);
    std::cout << "beta:\n" << (*beta) << '\n';
    layer->backward(alpha);
    std::cout << "beta:\n" << (*beta) << '\n';
    delete layer;
    delete beta;
  }();
  //=====
  sys::refresh("ReLU Test", true);
  [&] {
    auto layer = new network::ReLU;
    std::cout << "name= " << layer->name();
    auto beta = new lina_lg::MatrixF;
    (*beta) = std::move(basic_math::uniformRand({4, 5}, -5.0F, 5.0F));
    auto alpha = dynamic_cast<network::OperateType>(beta);
    std::cout << "\nbeta:\n" << (*beta) << '\n';
    layer->forward(alpha);
    std::cout << "beta:\n" << (*beta) << '\n';
    layer->backward(alpha);
    std::cout << "beta:\n" << (*beta) << '\n';
    delete layer;
    delete beta;
  }();
  //=====
  sys::refresh("Leaky ReLU Test", true);
  [&] {
    auto layer = new network::ReLU<FloatType(0.01)>;
    std::cout << "name= " << layer->name();
    auto beta = new lina_lg::MatrixF;
    (*beta) = std::move(basic_math::uniformRand({4, 5}, -5.0F, 5.0F));
    auto alpha = dynamic_cast<network::OperateType>(beta);
    std::cout << "\nbeta:\n" << (*beta) << '\n';
    layer->forward(alpha);
    std::cout << "beta:\n" << (*beta) << '\n';
    layer->backward(alpha);
    std::cout << "beta:\n" << (*beta) << '\n';
    delete layer;
    delete beta;
  }();
  //=====
  sys::refresh("Dense Test", true);
  [&] {
    auto layer = new network::Dense;
    layer->setCores(3, 4);
    layer->setLR();
    layer->setAct(dynamic_cast<network::LayerBase*>(new network::Tanh));
    layer->init(basic_math::normalRand<FloatType>, -0.1F, 0.1F);
    std::cout << "name= " << layer->name();
    auto beta = new lina_lg::MatrixF;
    (*beta) = std::move(basic_math::uniformRand({4, 5}, -1.0F, 1.0F));
    auto alpha = dynamic_cast<network::OperateType>(beta);
    std::cout << "\nbeta:\n" << (*beta) << '\n';
    layer->forward(alpha);
    std::cout << "beta:\n" << (*beta) << '\n';
    layer->backward(alpha);
    std::cout << "beta:\n" << (*beta) << '\n';
    layer->print();
    delete layer;
    delete beta;
  }();
  //=====
  sys::refresh("Input Test", true);
  [&] {
    auto layer = new network::FlatInput;
    layer->setSize(10, 3);
    file_io::FileIOOrdered file;
    file.setFile("/mnist.", "train_labels");
    file.switchMode(file_io::FileIOOrdered::reading);
    std::cout << "name= " << layer->name();
    auto beta = new lina_lg::MatrixF;
    auto alpha = dynamic_cast<network::OperateType>(beta);
    std::cout << "\nbeta:\n" << (*beta);
    layer->forward(file, alpha);
    std::cout << "\nbeta:\n" << (*beta) << '\n';
    delete layer;
    delete beta;
  }();
  //=====
  sys::refresh("SoftMax Test", true);
  [&] {
    auto layer = new network::SoftMax;
    std::cout << "name= " << layer->name();
    auto beta = new lina_lg::MatrixF;
    (*beta) = std::move(basic_math::uniformRand({4, 5}, 0.0F, 3.0F));
    auto alpha = dynamic_cast<network::OperateType>(beta);
    std::cout << "\nbeta:\n" << (*beta);
    layer->forward(alpha);
    std::cout << "\nbeta:\n" << (*beta) << '\n';
    delete layer;
    delete beta;
  }();
  //=====
  sys::refresh("meanSquareError Test", true);
  [&] {
    auto outAns = new lina_lg::MatrixF;
    auto stdAns = new lina_lg::MatrixF;
    lina_lg::VectorF* loss;
    auto input = new network::FlatInput;
    file_io::FileIOOrdered file;
    input->setSize(10, 8);
    file.setFile("/mnist.", "train_labels");
    file.switchMode(file_io::FileIOOrdered::reading);
    (*outAns) = std::move(basic_math::uniformRand({10, 8}, 0.0F, 3.0F));
    {
      auto theta = dynamic_cast<network::OperateType>(stdAns);
      input->forward(file, theta);
    }
    std::cout << "outAns:\n" << (*outAns) << '\n';
    std::cout << "stdAns:\n" << (*stdAns) << '\n';
    {
      auto alpha = dynamic_cast<network::OperateType>(stdAns);
      auto beta = dynamic_cast<network::OperateType>(outAns);
      loss = dynamic_cast<lina_lg::VectorF*>(
          network::meanSquareError(alpha, beta));
    }
    std::cout << "loss:\n" << (*loss) << '\n';
    std::cout << "backward:\n" << (*outAns) << '\n';
    delete outAns;
    delete stdAns;
    delete loss;
    delete input;
  }();
  //=====
  sys::refresh("Cross Entropy Test", true);
  [&] {
    auto outAns = new lina_lg::MatrixF;
    auto stdAns = new lina_lg::MatrixF;
    lina_lg::VectorF* loss;
    auto input = new network::FlatInput;
    file_io::FileIOOrdered file;
    input->setSize(10, 8);
    file.setFile("/mnist.", "train_labels");
    file.switchMode(file_io::FileIOOrdered::reading);
    (*outAns) = std::move(basic_math::uniformRand({10, 8}, 0.0F, 3.0F));
    {
      auto theta = dynamic_cast<network::OperateType>(stdAns);
      input->forward(file, theta);
      network::SoftMax max;
      auto alpha = dynamic_cast<network::OperateType>(outAns);
      max.forward(alpha);
    }
    std::cout << "outAns:\n" << (*outAns) << '\n';
    std::cout << "stdAns:\n" << (*stdAns) << '\n';
    {
      auto alpha = dynamic_cast<network::OperateType>(stdAns);
      auto beta = dynamic_cast<network::OperateType>(outAns);
      loss = dynamic_cast<lina_lg::VectorF*>(
          network::crossEntropyLoss(alpha, beta));
    }
    std::cout << "loss:\n" << (*loss) << '\n';
    std::cout << "backward:\n" << (*outAns) << '\n';
    delete outAns;
    delete stdAns;
    delete loss;
    delete input;
  }();
  //=====
  sys::refresh("Format Test", true);
  [&] {
    auto beta = new lina_lg::MatrixF;
    auto alpha = dynamic_cast<network::OperateType>(beta);
    (*beta) = std::move(basic_math::uniformRand({3, 6}, -1.0F, 3.0F));
    std::cout << (*beta) << '\n';
    auto gamma = network::oneHotFormat(alpha);
    std::cout << (*dynamic_cast<lina_lg::MatrixF*>(gamma)) << '\n';
    delete beta;
    delete gamma;
  }();
  delete[] buffer;
  DESTRUCT;
}