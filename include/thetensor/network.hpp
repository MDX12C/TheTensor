#include "define.hpp"
#ifndef NETWORK_H
#define NETWORK_H 1
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
  typedef enum { tanh, sigmoid } activationType;
  virtual ~LayerBase() noexcept {};
  inline virtual void forward(OperateType &) = 0;
  inline virtual void backward(OperateType &) = 0;
  inline virtual std::string name() = 0;
};
class Tanh final : public LayerBase {
 private:
  lina_lg::MatrixF output_;

 public:
  Tanh() noexcept { LOG("C:constructor of Tanh") }
  ~Tanh() noexcept { LOG("C:destructor of Tanh") }
  inline virtual void forward(OperateType &) noexcept override;
  inline virtual void backward(OperateType &) noexcept override;
  inline virtual std::string name() noexcept override {
    return std::string("Tanh");
  }
};
inline void Tanh::forward(OperateType &__input) noexcept {
  LOG("C:forward of Tanh");
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
  LOG("C:backward of Tanh");
  auto input = dynamic_cast<lina_lg::MatrixF *>(__input);
  output_ = std::move(basic_math::pow(output_, static_cast<FloatType>(2)));
  (*input) *= (static_cast<FloatType>(1) - output_);
  return;
}
class Sigmoid final : public LayerBase {
 private:
  lina_lg::MatrixF output_;

 public:
  Sigmoid() noexcept { LOG("C:constructor of Sigmoid") }
  ~Sigmoid() noexcept { LOG("C:destructor of Sigmoid") }
  inline virtual void forward(OperateType &) noexcept override;
  inline virtual void backward(OperateType &) noexcept override;
  inline virtual std::string name() noexcept override {
    return std::string("Sigmoid");
  }
};
inline void Sigmoid::forward(OperateType &__input) noexcept {
  LOG("C:forward of Sigmoid");
  auto input = dynamic_cast<lina_lg::MatrixF *>(__input);
  output_ = std::move(basic_math::pow(basic_math::EXPRISION, (*input)));
  output_ /= (output_ + static_cast<FloatType>(1));
  (*input) = output_;
  return;
}
inline void Sigmoid::backward(OperateType &__input) noexcept {
  LOG("C:backward of Sigmoid");
  auto input = dynamic_cast<lina_lg::MatrixF *>(__input);
  (*input) *= output_;
  (*input) *= (static_cast<FloatType>(1) - output_);
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
    readFile,
    simpleUniform,
  } initialType;
  Dense() noexcept { LOG("C:constructor of Dense") }
  ~Dense() noexcept {
    LOG("C:destructor of Dense")
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
  LOG("C:tidy forward by Dense");
  __input->resize({__input->shape().row_ + 1, __input->shape().col_});
  auto j = __input->end(), i = j - __input->shape().col_;
  while (i != j) {
    (*i) = static_cast<FloatType>(1);
    i++;
  }
  return;
}
inline void Dense::tidyBackward(lina_lg::MatrixF *&__input) noexcept {
  LOG("C:tidy backward by Dense");
  __input->resize({__input->shape().row_ - 1, __input->shape().col_});
  return;
}
inline void Dense::setCores(size_t const &__cores,
                            size_t const &__inputs) noexcept {
  LOG("C:set core of Dense");
  weight_.resize({__cores, __inputs + 1});
  return;
}
inline void Dense::setAct(LayerBase *__act) noexcept {
  LOG("C:set activation of Dense");
  activation_ = __act;
  return;
}
inline void Dense::setLR(FloatType const &__rate = LEARNING_RATE) noexcept {
  LOG("C:set learning rate of Dense");
  learningRate_ = __rate;
  return;
}
inline void Dense::init(initializer __func, FloatType const &__a,
                        FloatType const &__b) noexcept {
  LOG("C:init of Dense");
  for (auto &i : weight_) i = __func(__a, __b);
  return;
}
template <typename __STRING>
inline bool Dense::read(__STRING &__str, file_io::FileIO &__io) noexcept {
  LOG("C:read of Dense");
  return __io.read(__str, weight_.begin(), weight_.size());
}
template <typename __STRING>
inline bool Dense::write(__STRING &__str, file_io::FileIO &__io) noexcept {
  LOG("C:write of Dense");
  return __io.write(__str, weight_.begin(), weight_.size());
}
inline void Dense::print(std::ostream &__os = std::cout) const noexcept {
  LOG("C:print of Dense");
  for (auto i = 0; i < 10; i++) __os.put('+');
  __os << "\nlearning rate: " << learningRate_
       << "\nactivation function: " << activation_->name() << "\nweight:\n"
       << weight_ << "\nthe last input:\n"
       << input_ << '\n';
  for (auto i = 0; i < 10; i++) __os.put('+');
  __os.put('\n');
}
inline void Dense::forward(OperateType &__input) noexcept {
  LOG("C:forward of Dense");
  auto input = dynamic_cast<lina_lg::MatrixF *>(__input);
  Dense::tidyForward(input);
  input_ = std::move(*input);
  (*input) = std::move(basic_math::dot(weight_, input_));
  activation_->forward(__input);
  return;
}
inline void Dense::backward(OperateType &__input) noexcept {
  LOG("C:backward of Dense");
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
  FlatInput() noexcept { LOG("C:constructor of FlatInput"); }
  ~FlatInput() noexcept { LOG("C:destructor of FlatInput"); }
  inline void setSize(size_t const &, size_t const &) noexcept;
  inline virtual bool forward(file_io::FileIOOrdered &,
                              OperateType &) noexcept override;
  inline virtual std::string name() noexcept override {
    return std::string("FlatInput");
  }
};
inline void FlatInput::setSize(size_t const &__inputs,
                               size_t const &__batchs) noexcept {
  LOG("C:set size for FlatInput");
  temp_.resize({__batchs, __inputs});
}
inline bool FlatInput::forward(file_io::FileIOOrdered &__file,
                               OperateType &__alpha) noexcept {
  LOG("C:forward of FlatInput");
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
  SoftMax() noexcept { LOG("C:constructor of SoftMax"); }
  ~SoftMax() noexcept { LOG("C:destructor of SoftMax"); }
  inline virtual void forward(OperateType &) noexcept override;
  inline virtual void backward(OperateType &) noexcept override {
    LOG("C:baward of SoftMax");
    return;
  }
  inline virtual std::string name() noexcept override {
    return std::string("SoftMax");
  }
};
inline void SoftMax::forward(OperateType &__input) noexcept {
  LOG("C:forward of SoftMax");
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
  LOG("C:backward of meanSquareError");
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
inline OperateType oneHotFormat(OperateType &__input) noexcept {
  LOG("C:one hot format");
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
  template <typename __STRING>
  inline void setName(__STRING const &__name) noexcept {
    LOG("C:set name of Linear Model");
    myName_ = __name;
    return;
  }
  inline size_t &counter() noexcept { return temp_; }
  inline file_io::FileIOOrdered &inFile() noexcept { return inFile_; }
  inline file_io::FileIOOrdered &outFile() noexcept { return outFile_; }
  inline file_io::FileIO &weightFile() noexcept { return weightFile_; }
  inline void setFlatInput(size_t const &, size_t const &) noexcept;
  inline void setFlatOutput(size_t const &) noexcept;
  inline void setLossFunction(lossFunction const &) noexcept;
  inline void addSoftMax() noexcept;
  inline void addDense(size_t const &, LayerBase::activationType const &,
                       Dense::initialType const &, FloatType const &);
  inline bool forward() noexcept;
  inline void backward() noexcept;
  inline const OperateType &loss(bool const &) noexcept;
  inline bool write() noexcept;
};
LinearModel::LinearModel() noexcept {
  LOG("C:constructor of Linear Model");
  operand_[0] = dynamic_cast<OperateType>(new lina_lg::MatrixF);
  operand_[1] = dynamic_cast<OperateType>(new lina_lg::MatrixF);
  operand_[2] = nullptr;
  hiddenL_.clear();
  temp_ = 0;
  myName_ = "LinearModel";
  return;
}
LinearModel::~LinearModel() noexcept {
  LOG("C:destructor of Linear Model");
  delete operand_[0];
  delete operand_[1];
  if (operand_[2]) delete operand_[2];
  for (auto &i : hiddenL_) delete i;
  delete inputL_;
  delete outputL_;
  return;
}
inline void LinearModel::setFlatInput(size_t const &__input,
                                      size_t const &__batch) noexcept {
  LOG("C:set input of Linear Model");
  auto alpha = new FlatInput;
  alpha->setSize(__input, __batch);
  inputL_ = dynamic_cast<InputBase *>(alpha);
  temp_ = __input;
  return;
}
inline void LinearModel::setFlatOutput(size_t const &__batch) noexcept {
  LOG("C:set output of Linear Model");
  auto alpha = new FlatInput;
  alpha->setSize(temp_, __batch);
  outputL_ = dynamic_cast<InputBase *>(alpha);
  temp_ = 0;
  return;
}
inline void LinearModel::setLossFunction(lossFunction const &__loss) noexcept {
  LOG("C:set loss function of Linear Model");
  lossF_ = __loss;
  return;
}
inline void LinearModel::addSoftMax() noexcept {
  LOG("C:add Soft Max of Linear Model");
  hiddenL_.push_back(dynamic_cast<LayerBase *>(new SoftMax));
  return;
}
inline void LinearModel::addDense(
    size_t const &__cores, LayerBase::activationType const &__act,
    Dense::initialType const &__init = Dense::initialType::simpleUniform,
    FloatType const &__lr = LEARNING_RATE) {
  LOG("C:add Dense of Linear Model");
  auto alpha = new Dense;
  alpha->setCores(__cores, temp_);
  temp_ = __cores;
  alpha->setLR(__lr);
  switch (__act) {
    case LayerBase::activationType::tanh:
      alpha->setAct(dynamic_cast<LayerBase *>(new Tanh));
      break;
    case LayerBase::activationType::sigmoid:
      alpha->setAct(dynamic_cast<LayerBase *>(new Sigmoid));
      break;
    default:
      LOG("B:unsupport activation function");
      break;
  }
  std::string str;
  auto size = hiddenL_.size();
  switch (__init) {
    case Dense::initialType::readFile:
      DEBUG(__init);
      file_io::numToString(str, size);
      str = myName_ + str.substr(1);
      if (!alpha->read(str, weightFile_)) {
        LOG("E:bad read");
      }
      break;
    case Dense::initialType::simpleUniform:
      alpha->init(basic_math::uniformRand<FloatType>, FloatType(-0.1),
                  FloatType(0.1));
      break;
    default:
      LOG("B:unsupport initial type");
      break;
  }
  hiddenL_.push_back(dynamic_cast<LayerBase *>(alpha));
}
inline bool LinearModel::forward() noexcept {
  LOG("C:forward of Linear Model");
  if (!inputL_->forward(inFile_, operand_[0])) return false;
  for (size_t i = 0; i < hiddenL_.size(); i++)
    hiddenL_[i]->forward(operand_[0]);
  return true;
}
inline const OperateType &LinearModel::loss(
    bool const &__skip = false) noexcept {
  LOG("C:loss of Linear Model");
  outputL_->forward(outFile_, operand_[1]);
  if (operand_[2]) delete operand_[2];
  operand_[2] = oneHotFormat(operand_[0]);
  {
    auto alpha = dynamic_cast<lina_lg::MatrixF *>(operand_[2]);
    auto beta = dynamic_cast<lina_lg::MatrixF *>(operand_[1]);
    temp_ += static_cast<size_t>(((*alpha) * (*beta)).sum());
  }
  if (__skip) return static_cast<OperateType>(nullptr);
  delete operand_[2];
  operand_[2] = lossF_(operand_[1], operand_[0]);
  return operand_[2];
}
inline void LinearModel::backward() noexcept {
  LOG("C:backward of Linead Model");
  for (size_t i = hiddenL_.size() - 1; i > 0; i--)
    hiddenL_[i]->backward(operand_[0]);
  hiddenL_[0]->backward(operand_[0]);
  return;
}
inline bool LinearModel::write() noexcept {
  LOG("C:write of Linear Model");
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