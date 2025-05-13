#include "define.hpp"
#ifndef NETWORK_HH
#define NETWORK_HH 1
#include "basic.hpp"
#include "file.hpp"
#include "log.hpp"
#include "matrix.hpp"
#include "vector.hpp"
namespace network {
constexpr FloatType LEARNING_RATE = static_cast<FloatType>(0.01);
// the type that networks do operate
using OperateType = storage::StoryBase *;
// the type of initializer
typedef FloatType (*initializer)(FloatType const &, FloatType const &);
// the type of loss function
typedef OperateType (*lossFunction)(OperateType &, OperateType &);
// the basement of input layer
class InputBase {
 public:
  virtual ~InputBase() noexcept {};
  inline virtual bool forward(file_io::FileIOOrdered &, OperateType &) = 0;
  inline virtual std::string name() = 0;
};
// the basement of layer
class LayerBase {
 public:
  typedef enum { tanh, sigmoid, relu, leakyRelu } activationType;
  virtual ~LayerBase() noexcept {};
  inline virtual void forward(OperateType &) = 0;
  inline virtual void backward(OperateType &) = 0;
  inline virtual std::string name() = 0;
};
class Tanh final : public LayerBase {
 private:
  lina_lg::MatrixF output_;

 public:
  Tanh() noexcept {}
  ~Tanh() noexcept {}
  inline virtual void forward(OperateType &) noexcept override;
  inline virtual void backward(OperateType &) noexcept override;
  inline virtual std::string name() noexcept override {
    return std::string("Tanh");
  }
};
inline void Tanh::forward(OperateType &__input) noexcept {
  auto input = dynamic_cast<lina_lg::MatrixF *>(__input);
  (*input) *= static_cast<FloatType>(2);
  output_ = std::move(basic_math::pow(basic_math::EXPRISION, (*input)));
  output_ += static_cast<FloatType>(1);
  (*input) = std::move(output_ - static_cast<FloatType>(2));
  (*input) /= output_;
  output_ = (*input);
  return;
}
inline void Tanh::backward(OperateType &__input) noexcept {
  auto input = dynamic_cast<lina_lg::MatrixF *>(__input);
  output_ = std::move(basic_math::pow(output_, static_cast<FloatType>(2)));
  (*input) *= (static_cast<FloatType>(1) - output_);
  return;
}
class Sigmoid final : public LayerBase {
 private:
  lina_lg::MatrixF output_;

 public:
  Sigmoid() noexcept {}
  ~Sigmoid() noexcept {}
  inline virtual void forward(OperateType &) noexcept override;
  inline virtual void backward(OperateType &) noexcept override;
  inline virtual std::string name() noexcept override {
    return std::string("Sigmoid");
  }
};
inline void Sigmoid::forward(OperateType &__input) noexcept {
  auto input = dynamic_cast<lina_lg::MatrixF *>(__input);
  output_ = std::move(basic_math::pow(basic_math::EXPRISION, (*input)));
  output_ /= (output_ + static_cast<FloatType>(1));
  (*input) = output_;
  return;
}
inline void Sigmoid::backward(OperateType &__input) noexcept {
  auto input = dynamic_cast<lina_lg::MatrixF *>(__input);
  (*input) *= output_;
  (*input) *= (static_cast<FloatType>(1) - output_);
  return;
}
template <FloatType ALPHA = static_cast<FloatType>(0)>
class ReLU final : public LayerBase {
 private:
  lina_lg::MatrixF tangent_;

 public:
  ReLU() noexcept {}
  ~ReLU() noexcept {}
  inline virtual void forward(OperateType &) noexcept override;
  inline virtual void backward(OperateType &) noexcept override;
  inline virtual std::string name() noexcept override {
    if constexpr (ALPHA)
      return std::string("LeakyReLU");
    else
      return std::string("ReLU");
  }
};
template <FloatType ALPHA>
inline void ReLU<ALPHA>::forward(OperateType &__input) noexcept {
  auto input = dynamic_cast<lina_lg::MatrixF *>(__input);
  tangent_.resize(input->shape());
  auto in = input->begin(), out = tangent_.begin();
  for (size_t i = 0; i < tangent_.size(); i++) {
    if (in[i] > 0) {
      out[i] = static_cast<FloatType>(1);
    } else {
      in[i] *= ALPHA;
      out[i] = ALPHA;
    }
  }
  return;
}
template <FloatType ALPHA>
inline void ReLU<ALPHA>::backward(OperateType &__input) noexcept {
  auto input = dynamic_cast<lina_lg::MatrixF *>(__input);
  (*input) *= tangent_;
  return;
}
class Dense final : public LayerBase {
 private:
  lina_lg::MatrixF weight_;
  lina_lg::MatrixF input_;
  LayerBase *activation_;
  FloatType learningRate_;

 public:
  typedef enum {
    // read from file
    readFile,
    // U[-0.01,0.01)
    simpleUniform,
    glorotUniform,
    glorotNormal,
    heUniform,
    heNormal
  } initialType;
  Dense() noexcept {}
  ~Dense() noexcept {
    if (activation_) delete activation_;
  }
  inline void setCores(size_t const &, size_t const &) noexcept;
  inline void setAct(LayerBase *) noexcept;
  inline void setLR(FloatType const &) noexcept;
  inline void init(initializer, FloatType const &, FloatType const &) noexcept;
  template <typename __STRING>
  inline bool read(__STRING &, file_io::FileIO &) noexcept;
  template <typename __STRING>
  inline bool write(__STRING &, file_io::FileIO &) noexcept;
  inline void print(std::ostream &) const noexcept;
  inline virtual void forward(OperateType &) noexcept override;
  inline virtual void backward(OperateType &) noexcept override;
  inline virtual std::string name() noexcept override {
    return std::string("Dense");
  }
  static inline void tidyForward(lina_lg::MatrixF *&) noexcept;
  static inline void tidyBackward(lina_lg::MatrixF *&) noexcept;
};
inline void Dense::tidyForward(lina_lg::MatrixF *&__input) noexcept {
  __input->resize({__input->shape().row_ + 1, __input->shape().col_});
  auto j = __input->end(), i = j - __input->shape().col_;
  while (i != j) {
    (*i) = static_cast<FloatType>(1);
    i++;
  }
  return;
}
inline void Dense::tidyBackward(lina_lg::MatrixF *&__input) noexcept {
  __input->resize({__input->shape().row_ - 1, __input->shape().col_});
  return;
}
inline void Dense::setCores(size_t const &__cores,
                            size_t const &__inputs) noexcept {
  weight_.resize({__cores, __inputs + 1});
  return;
}
inline void Dense::setAct(LayerBase *__act) noexcept {
  activation_ = __act;
  return;
}
inline void Dense::setLR(FloatType const &__rate = LEARNING_RATE) noexcept {
  learningRate_ = __rate;
  return;
}
inline void Dense::init(initializer __func, FloatType const &__a,
                        FloatType const &__b) noexcept {
  for (auto &i : weight_) i = __func(__a, __b);
  return;
}
template <typename __STRING>
inline bool Dense::read(__STRING &__str, file_io::FileIO &__io) noexcept {
  return __io.read(__str, weight_.begin(), weight_.size());
}
template <typename __STRING>
inline bool Dense::write(__STRING &__str, file_io::FileIO &__io) noexcept {
  return __io.write(__str, weight_.begin(), weight_.size());
}
inline void Dense::print(std::ostream &__os = std::cout) const noexcept {
  for (auto i = 0; i < 10; i++) __os.put('+');
  __os << "\nlearning rate: " << learningRate_
       << "\nactivation function: " << activation_->name() << "\nweight:\n"
       << weight_ << "\nthe last input:\n"
       << input_ << '\n';
  for (auto i = 0; i < 10; i++) __os.put('+');
  __os.put('\n');
}
inline void Dense::forward(OperateType &__input) noexcept {
  auto input = dynamic_cast<lina_lg::MatrixF *>(__input);
  Dense::tidyForward(input);
  input_ = std::move(*input);
  (*input) = std::move(basic_math::dot(weight_, input_));
  activation_->forward(__input);
  return;
}
inline void Dense::backward(OperateType &__input) noexcept {
  activation_->backward(__input);
  auto xT = std::move(input_.transpose());
  auto aT = std::move(weight_.transpose());
  auto input = dynamic_cast<lina_lg::MatrixF *>(__input);
  weight_ -= basic_math::dot((*input), xT) * learningRate_;
  (*input) = std::move(basic_math::dot(aT, (*input)));
  Dense::tidyBackward(input);
  return;
}
class FlatInput final : public InputBase {
 private:
  lina_lg::MatrixF temp_;

 public:
  FlatInput() noexcept {}
  ~FlatInput() noexcept {}
  inline void setSize(size_t const &, size_t const &) noexcept;
  inline virtual bool forward(file_io::FileIOOrdered &,
                              OperateType &) noexcept override;
  inline virtual std::string name() noexcept override {
    return std::string("FlatInput");
  }
};
inline void FlatInput::setSize(size_t const &__inputs,
                               size_t const &__batchs) noexcept {
  temp_.resize({__batchs, __inputs});
}
inline bool FlatInput::forward(file_io::FileIOOrdered &__file,
                               OperateType &__alpha) noexcept {
  const auto shape = temp_.shape();
  temp_ = static_cast<FloatType>(0);
  bool reading;
  FloatType *ptr = temp_.begin();
  for (size_t i = 0; i < shape.row_; i++) {
    reading = __file.read(ptr, shape.col_);
    if (reading) {
      ptr += shape.col_;
    } else {
      if (i) {
        break;
      }
      return false;
    }
  }
  (*dynamic_cast<lina_lg::MatrixF *>(__alpha)) = std::move(temp_.transpose());
  return true;
}
class SoftMax final : public LayerBase {
 public:
  SoftMax() noexcept {}
  ~SoftMax() noexcept {}
  inline virtual void forward(OperateType &) noexcept override;
  inline virtual void backward(OperateType &) noexcept override {}
  inline virtual std::string name() noexcept override {
    return std::string("SoftMax");
  }
};
inline void SoftMax::forward(OperateType &__input) noexcept {
  auto input = dynamic_cast<lina_lg::MatrixF *>(__input);
  const auto size = input->size(), wide = input->shape().col_;
  auto ptr = input->begin();
  lina_lg::VectorF stretch(wide);
  stretch = 0;
  for (size_t i = 0, j = 0; i < size; i++, j++) {
    if (j == wide) j = 0;
    stretch[j] += ptr[i];
  }
  for (size_t i = 0, j = 0; i < size; i++, j++) {
    if (j == wide) j = 0;
    ptr[i] /= stretch[j];
  }
  return;
}
inline OperateType meanSquareError(OperateType &__standard,
                                   OperateType &__input) noexcept {
  auto input = dynamic_cast<lina_lg::MatrixF *>(__input),
       standard = dynamic_cast<lina_lg::MatrixF *>(__standard);
  (*input) -= (*standard);
  (*standard) = std::move(basic_math::pow((*input), static_cast<FloatType>(2)));
  auto answer = new lina_lg::VectorF(standard->shape().col_);
  const auto size = standard->size(), wide = standard->shape().col_;
  const auto ptr = standard->begin();
  for (size_t i = 0, j = 0; i < size; i++, j++) {
    if (j == wide) j = 0;
    answer->operator[](j) += ptr[i];
  }
  (*answer) /= static_cast<FloatType>(standard->shape().row_);
  return dynamic_cast<OperateType>(answer);
}
inline OperateType crossEntropyLoss(OperateType &__standard,
                                    OperateType &__input) noexcept {
  auto input = dynamic_cast<lina_lg::MatrixF *>(__input),
       standard = dynamic_cast<lina_lg::MatrixF *>(__standard);
  (*standard) *= static_cast<FloatType>(-1);
  auto answer = new lina_lg::VectorF(standard->shape().col_);
  auto alpha = std::move((*standard) * basic_math::log(*input));
  auto ptr = alpha.begin();
  for (size_t i = 0, j = 0; i < alpha.size(); i++, j++) {
    if (j == alpha.shape().col_) j = 0;
    answer->operator[](j) += ptr[i];
  }
  (*input) = std::move((*standard) / (*input));
  return dynamic_cast<OperateType>(answer);
}
inline OperateType oneHotFormat(OperateType &__input) noexcept {
  auto input = dynamic_cast<lina_lg::MatrixF *>(__input);
  auto shape = input->shape();
  auto ret = new lina_lg::MatrixF(shape);
  auto size = shape.col_ * shape.row_;
  auto const ptr = input->begin();
  struct count {
    FloatType value_ = 0;
    size_t position_ = 0;
  } table[shape.col_];
  for (size_t i = 0, w = 0; w < shape.row_; w++) {
    for (size_t k = 0; k < shape.col_; k++, i++) {
      if (ptr[i] > table[k].value_) {
        table[k].value_ = ptr[i];
        table[k].position_ = w;
      }
    }
  }
  size = shape.col_;
  for (size_t i = 0; i < size; i++) {
    shape.col_ = i;
    shape.row_ = table[i].position_;
    ret->operator[](shape) = static_cast<FloatType>(1);
  }
  return ret;
}
class LinearModel {
 private:
  std::vector<LayerBase *> hiddenL_;
  InputBase *inputL_;
  InputBase *outputL_;
  lossFunction lossF_;
  OperateType operand_[3];
  file_io::FileIOOrdered inFile_;
  file_io::FileIOOrdered outFile_;
  file_io::FileIO weightFile_;
  size_t temp_;
  std::string myName_;

 public:
  LinearModel() noexcept;
  ~LinearModel() noexcept;
  // set the name of the model
  template <typename __STRING>
  inline void setName(__STRING const &__name) noexcept {
    myName_ = __name;
    return;
  }
  /**
   * @brief return the counter
   * @warning don't modify the value during setting the model
   */
  inline size_t &counter() noexcept { return temp_; }
  // the reference of input file
  inline file_io::FileIOOrdered &inFile() noexcept { return inFile_; }
  // the reference of output file
  inline file_io::FileIOOrdered &outFile() noexcept { return outFile_; }
  // the reference of weight file
  inline file_io::FileIO &weightFile() noexcept { return weightFile_; }
  inline void setFlatInput(size_t const &, size_t const &) noexcept;
  inline void setFlatOutput(size_t const &) noexcept;
  inline void setLossFunction(lossFunction const &) noexcept;
  inline void addSoftMax() noexcept;
  inline void addDense(size_t const &, LayerBase::activationType const &,
                       Dense::initialType const &, FloatType const &);
  inline bool forward() noexcept;
  inline void backward() noexcept;
  inline FloatType loss(bool const &) noexcept;
  inline bool write() noexcept;
};
LinearModel::LinearModel() noexcept {
  operand_[0] = dynamic_cast<OperateType>(new lina_lg::MatrixF);
  operand_[1] = dynamic_cast<OperateType>(new lina_lg::MatrixF);
  operand_[2] = nullptr;
  hiddenL_.clear();
  temp_ = 0;
  myName_ = "LinearModel";
  return;
}
LinearModel::~LinearModel() noexcept {
  delete operand_[0];
  delete operand_[1];
  if (operand_[2]) delete operand_[2];
  for (auto &i : hiddenL_) delete i;
  delete inputL_;
  delete outputL_;
  return;
}
// set the input size and batch
inline void LinearModel::setFlatInput(size_t const &__input,
                                      size_t const &__batch) noexcept {
  auto alpha = new FlatInput;
  alpha->setSize(__input, __batch);
  inputL_ = dynamic_cast<InputBase *>(alpha);
  temp_ = __input;
  return;
}
// set the batch of output
inline void LinearModel::setFlatOutput(size_t const &__batch) noexcept {
  auto alpha = new FlatInput;
  alpha->setSize(temp_, __batch);
  outputL_ = dynamic_cast<InputBase *>(alpha);
  temp_ = 0;
  return;
}
// choose the loss function
inline void LinearModel::setLossFunction(lossFunction const &__loss) noexcept {
  lossF_ = __loss;
  return;
}
// add a Soft-max layer
inline void LinearModel::addSoftMax() noexcept {
  hiddenL_.push_back(dynamic_cast<LayerBase *>(new SoftMax));
  return;
}
// add a Dense layer with ordering [cores,activation,init way,learning rate]
inline void LinearModel::addDense(
    size_t const &__cores,
    LayerBase::activationType const &__act = LayerBase::activationType::relu,
    Dense::initialType const &__init = Dense::initialType::simpleUniform,
    FloatType const &__lr = LEARNING_RATE) {
  auto alpha = new Dense;
  alpha->setCores(__cores, temp_);
  alpha->setLR(__lr);
  switch (__act) {
    case LayerBase::activationType::tanh:
      alpha->setAct(dynamic_cast<LayerBase *>(new Tanh));
      break;
    case LayerBase::activationType::sigmoid:
      alpha->setAct(dynamic_cast<LayerBase *>(new Sigmoid));
      break;
    case LayerBase::activationType::relu:
      alpha->setAct(dynamic_cast<LayerBase *>(new ReLU));
      break;
    case LayerBase::activationType::leakyRelu:
      alpha->setAct(
          dynamic_cast<LayerBase *>(new ReLU<static_cast<FloatType>(0.01)>));
      break;
    default:
      LOG("B:unsupport activation function");
      endOfMainFunction();
      break;
  }
  switch (__init) {
    case Dense::initialType::readFile:
      [&] {
        std::string str;
        auto size = hiddenL_.size();
        file_io::numToString(str, size);
        str = myName_ + str.substr(1);
        if (!alpha->read(str, weightFile_)) {
          LOG("E:bad read");
        }
      }();
      break;
    case Dense::initialType::simpleUniform:
      alpha->init(basic_math::uniformRand<FloatType>, FloatType(-0.1),
                  FloatType(0.1));
      break;
    case Dense::initialType::glorotUniform:
      [&] {
        FloatType limit = std::sqrt((FloatType)6 / (temp_ + __cores));
        alpha->init(basic_math::uniformRand<FloatType>, limit * (-1), limit);
      }();
      break;
    case Dense::initialType::glorotNormal:
      [&] {
        FloatType varient = (FloatType)2 / (temp_ + __cores);
        alpha->init(basic_math::normalRand<FloatType>, (FloatType)0, varient);
      }();
      break;
    case Dense::initialType::heUniform:
      [&] {
        FloatType limit = std::sqrt((FloatType)6 / temp_);
        alpha->init(basic_math::uniformRand<FloatType>, limit * (-1), limit);
      }();
      break;
    case Dense::initialType::heNormal:
      [&] {
        FloatType varient = (FloatType)2 / temp_;
        alpha->init(basic_math::normalRand<FloatType>, (FloatType)0, varient);
      }();
      break;
    default:
      LOG("B:unsupport initial type");
      endOfMainFunction();
      break;
  }
  temp_ = __cores;
  hiddenL_.push_back(dynamic_cast<LayerBase *>(alpha));
}
inline bool LinearModel::forward() noexcept {
  if (!inputL_->forward(inFile_, operand_[0])) return false;
  for (size_t i = 0; i < hiddenL_.size(); i++)
    hiddenL_[i]->forward(operand_[0]);
  return true;
}
inline FloatType LinearModel::loss(bool const &__skip = false) noexcept {
  outputL_->forward(outFile_, operand_[1]);
  if (operand_[2]) delete operand_[2];
  operand_[2] = oneHotFormat(operand_[0]);
  {
    auto alpha = dynamic_cast<lina_lg::MatrixF *>(operand_[2]);
    auto beta = dynamic_cast<lina_lg::MatrixF *>(operand_[1]);
    temp_ += static_cast<size_t>(((*alpha) * (*beta)).sum());
  }
  if (__skip) return static_cast<FloatType>(0);
  delete operand_[2];
  operand_[2] = lossF_(operand_[1], operand_[0]);
  auto alpha = dynamic_cast<lina_lg::VectorF *>(operand_[2]);
  return alpha->sum() / alpha->size();
}
inline void LinearModel::backward() noexcept {
  for (size_t i = hiddenL_.size() - 1; i > 0; i--)
    hiddenL_[i]->backward(operand_[0]);
  hiddenL_[0]->backward(operand_[0]);
  return;
}
inline bool LinearModel::write() noexcept {
  std::string str;
  Dense *alpha;
  for (size_t i = 0; i < hiddenL_.size(); i++) {
    if (hiddenL_[i]->name() == "Dense") {
      file_io::numToString(str, i);
      str = myName_ + str.substr(1);
      alpha = dynamic_cast<Dense *>(hiddenL_[i]);
      if (!alpha->write(str, weightFile_)) return false;
    }
  }
  return true;
}
}  // namespace network
#endif