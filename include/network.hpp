#include "define.hpp"
#ifndef NETWORK_H
#define NETWORK_H 1
#include "basic.hpp"
#include "log.hpp"
#include "matrix.hpp"
#include "rom.hpp"
#include "vector.hpp"
namespace network {
constexpr FloatType LEARN_RATE = static_cast<FloatType>(0.01);
class Affine {
 private:
  lina_lg::MatrixF weight_;
  lina_lg::MatrixF input_;

 public:
  Affine() noexcept;
  ~Affine() noexcept;
  inline void set(size_t const&, size_t const&) noexcept;
  inline void init() noexcept;
  template <typename T>
  inline bool read(T&, file_io::FileIO&) noexcept;
  template <typename T>
  inline bool write(T&, file_io::FileIO&) noexcept;
  inline void print(std::ostream&) noexcept;
  inline void forward(lina_lg::MatrixF&) noexcept;
  inline void backward(lina_lg::MatrixF&) noexcept;
};
Affine::Affine() noexcept { LOG("C:constructor of Affine"); }
Affine::~Affine() noexcept { LOG("C:destructor of Affine"); }
inline void Affine::set(size_t const& __cores,
                        size_t const& __inputs) noexcept {
  LOG("C:set of Affine");
  weight_.resize(lina_lg::makeShape(__cores, __inputs + 1));
  return;
}
inline void Affine::init() noexcept {
  LOG("C:init of Affine");
  weight_ = std::move(basic_math::random(weight_.shape(),
                                         static_cast<FloatType>(-0.1),
                                         static_cast<FloatType>(0.1)));
  return;
}
template <typename T>
inline bool Affine::read(T& __str, file_io::FileIO& __io) noexcept {
  LOG("C:read of Affine");
  return __io.read(__str, weight_.begin(), weight_.size());
}
template <typename T>
inline bool Affine::write(T& __str, file_io::FileIO& __io) noexcept {
  LOG("C:write of Affine");
  return __io.write(__str, weight_.begin(), weight_.size());
}
inline void Affine::print(std::ostream& __os = std::cout) noexcept {
  LOG("C:print of Affine");
  __os << "++++++++++\nweight:\n"
       << weight_ << "the last input:\n"
       << input_ << "++++++++++\n";
  return;
}
inline void Affine::forward(lina_lg::MatrixF& __input) noexcept {
  LOG("C:forward of Affine");
  input_ = std::move(__input);
  __input = std::move(basic_math::dot(weight_, input_));
  return;
}
inline void Affine::backward(lina_lg::MatrixF& __input) noexcept {
  LOG("C:backward of Affine");
  auto xT = std::move(input_.transpose());
  auto aT = std::move(weight_.transpose());
  weight_ -= basic_math::dot(__input, xT);
  __input = std::move(basic_math::dot(aT, __input));
  return;
}
class Input {
 private:
  lina_lg::MatrixF temp_;

 public:
  Input() noexcept;
  ~Input() noexcept;
  inline void set(size_t const&, size_t const&) noexcept;
  inline bool forward(file_io::FileIOOrdered&, lina_lg::MatrixF&) noexcept;
};
Input::Input() noexcept { LOG("C:constructor of Input"); }
Input::~Input() noexcept { LOG("C:destructor of Input"); }
inline void Input::set(size_t const& __inputs, size_t const& __times) noexcept {
  LOG("C:set of Input");
  temp_.resize(lina_lg::makeShape(__times, __inputs));
  return;
}
inline bool Input::forward(file_io::FileIOOrdered& __file,
                           lina_lg::MatrixF& __alpha) noexcept {
  LOG("C:forward of Input");
  const auto shape = temp_.shape();
  temp_ = static_cast<FloatType>(0);
  bool reading;
  FloatType* ptr = temp_.begin();
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
  __alpha = std::move(temp_.transpose());
  return true;
}
class Tidy {
 public:
  Tidy() noexcept;
  ~Tidy() noexcept;
  inline void forward(lina_lg::MatrixF&) noexcept;
  inline void backward(lina_lg::MatrixF&) noexcept;
};
Tidy::Tidy() noexcept { LOG("C:constructor of Tidy"); }
Tidy::~Tidy() noexcept { LOG("C:destructor of Tidy"); }
inline void Tidy::forward(lina_lg::MatrixF& __input) noexcept {
  LOG("C:forward of Tidy");
  __input.resize(
      lina_lg::makeShape(__input.shape().row_ + 1, __input.shape().col_));
  auto j = __input.end(), i = j - __input.shape().col_;
  while (i != j) {
    (*i) = static_cast<FloatType>(1);
    i++;
  }
  return;
}
inline void Tidy::backward(lina_lg::MatrixF& __input) noexcept {
  LOG("C:backward of Tidy");
  __input.resize(
      lina_lg::makeShape(__input.shape().row_ - 1, __input.shape().col_));
  return;
}
class Tanh {
 private:
  lina_lg::MatrixF output_;

 public:
  Tanh() noexcept;
  ~Tanh() noexcept;
  inline void forward(lina_lg::MatrixF&) noexcept;
  inline void backward(lina_lg::MatrixF&) noexcept;
};
Tanh::Tanh() noexcept { LOG("C:constructor of Tanh"); }
Tanh::~Tanh() noexcept { LOG("C:destructor of Tanh"); }
inline void Tanh::forward(lina_lg::MatrixF& __input) noexcept {
  LOG("C:forward of Tanh");
  __input *= static_cast<FloatType>(2);
  output_ = std::move(basic_math::pow(basic_math::EXPRISION, __input));
  output_ += static_cast<FloatType>(1);
  __input = std::move(output_ - static_cast<FloatType>(2));
  __input /= output_;
  output_ = __input;
  return;
}
inline void Tanh::backward(lina_lg::MatrixF& __input) noexcept {
  LOG("C:backward of Tanh");
  output_ = std::move(basic_math::pow(output_, static_cast<FloatType>(2)));
  __input = std::move(static_cast<FloatType>(1) - output_);
  return;
}
class Sigmoid {
 private:
  lina_lg::MatrixF output_;

 public:
  Sigmoid() noexcept;
  ~Sigmoid() noexcept;
  inline void forward(lina_lg::MatrixF&) noexcept;
  inline void backward(lina_lg::MatrixF&) noexcept;
};
Sigmoid::Sigmoid() noexcept { LOG("C:constructor of Sigmoid"); }
Sigmoid::~Sigmoid() noexcept { LOG("C:destructor of Sigmoid"); }
inline void Sigmoid::forward(lina_lg::MatrixF& __input) noexcept {
  LOG("C:forward of Sigmoid");
  output_ = std::move(basic_math::pow(basic_math::EXPRISION, __input));
  output_ /= (output_ - static_cast<FloatType>(1));
  __input = output_;
  return;
}
inline void Sigmoid::backward(lina_lg::MatrixF& __input) noexcept {
  LOG("C:backward of Sigmoid");
  __input *= output_;
  __input *= (static_cast<FloatType>(1) - output_);
  return;
}
class SoftMax {
 public:
  SoftMax() noexcept;
  ~SoftMax() noexcept;
  inline void forward(lina_lg::MatrixF& __input) noexcept;
  inline void backward(lina_lg::MatrixF& __input) noexcept {
    LOG("C:backward of SoftMax");
  }
};
SoftMax::SoftMax() noexcept { LOG("C:constructor of SoftMax"); }
SoftMax::~SoftMax() noexcept { LOG("C:destructor of SoftMax"); }
inline void SoftMax::forward(lina_lg::MatrixF& __input) noexcept {
  LOG("C:forward of SoftMax");
  const auto size = __input.size(), wide = __input.shape().col_;
  auto ptr = __input.begin();
  lina_lg::VectorF temp(wide);
  for (size_t i = 0, j = 0; i < size; i++, j++) {
    if (j == wide) j = 0;
    temp[j] += ptr[i];
  }
  for (size_t i = 0, j = 0; i < size; i++, j++) {
    if (j == wide) j = 0;
    ptr[i] /= temp[j];
  }
  return;
}
class MSE {
 public:
  MSE() noexcept;
  ~MSE() noexcept;
  inline lina_lg::VectorF backward(file_io::FileIOOrdered&,
                                   lina_lg::MatrixF&) noexcept;
};
MSE::MSE() noexcept { LOG("C:constructor of MSE"); }
MSE::~MSE() noexcept { LOG("C:destructor of MSE"); }
inline lina_lg::VectorF MSE::backward(file_io::FileIOOrdered& __file,
                                      lina_lg::MatrixF& __input) noexcept {
  LOG("C:backward of MSE");
  lina_lg::MatrixF standard(
      lina_lg::makeShape(__input.shape().col_, __input.shape().row_));
  [&] {
    auto ptr = standard.begin();
    auto shape = standard.shape();
    for (size_t i = 0; i < shape.row_; i++) {
      if (__file.read(ptr, shape.col_)) {
        ptr += shape.col_;
      } else {
        break;
      }
    }
  }();
  __input -= standard.transpose();
  standard = std::move(basic_math::pow(__input, static_cast<FloatType>(2)));
  lina_lg::VectorF answer(standard.shape().col_);
  [&] {
    const auto size = standard.size(), wide = standard.shape().col_;
    const auto ptr = standard.begin();
    for (size_t i = 0, j = 0; i < size; i++, j++) {
      if (j == wide) j = 0;
      answer[j] += ptr[i];
    }
    answer /= static_cast<FloatType>(standard.shape().row_);
  }();
  return answer;
}
}  // namespace network
#endif