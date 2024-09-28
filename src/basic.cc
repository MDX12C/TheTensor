#ifndef BASIC_CC
#define BASIC_CC 1
#include "basic.hpp"

namespace basic_math {
std::mt19937 BasicSupport::generator;
}  // namespace basic_math
namespace linalg {
bool operator==(MaShape const& alpha, MaShape const& beta) {
  return (alpha.rows == beta.rows) && (alpha.cols == beta.cols);
}
bool operator<(MaShape const& alpha, MaShape const& beta) {
  return (alpha.rows < beta.rows) && (alpha.cols < beta.cols);
}
bool operator<=(MaShape const& alpha, MaShape const& beta) {
  return (alpha.rows <= beta.rows) && (alpha.cols <= beta.cols);
}
bool operator!=(MaShape const& alpha, MaShape const& beta) {
  return (alpha.rows != beta.rows) || (alpha.cols != beta.cols);
}
std::ostream& operator<<(std::ostream& os, const MaShape& ms) {
  LOG("C:matrix shape [%d,%d]", ms.rows, ms.cols);
  os << std::noshowpos << '(' << ms.rows << ',' << ms.cols << ')';
  return os;
}
}  // namespace linalg
#endif