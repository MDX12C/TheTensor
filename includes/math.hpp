﻿#ifndef MATH_H
#define MATH_H
#include "./basic.hpp"
#include "./matrix.hpp"
#include "./tensor.hpp"
#include "./vector.hpp"
namespace Memory_Maintain {
inline void _mmy_clean() {
  _mmy_node *alpha = _mmy_top;
  while (alpha != nullptr) {
    if (alpha->data.type == Vi) {
      alpha->data.ptr.vi->freedom_();
    } else if (alpha->data.type == Vb) {
      alpha->data.ptr.vb->freedom_();
    } else if (alpha->data.type == Vf) {
      alpha->data.ptr.vf->freedom_();
    } else if (alpha->data.type == Mi) {
      alpha->data.ptr.mi->freedom_();
    } else if (alpha->data.type == Mb) {
      alpha->data.ptr.mb->freedom_();
    } else if (alpha->data.type == Mf) {
      alpha->data.ptr.mf->freedom_();
    } else if (alpha->data.type == Ti) {
      alpha->data.ptr.ti->freedom_();
    } else if (alpha->data.type == Tb) {
      alpha->data.ptr.tb->freedom_();
    } else if (alpha->data.type == Tf) {
      alpha->data.ptr.tf->freedom_();
    } else if (alpha->data.type == S) {
      alpha->data.ptr.s->freedom_();
    }
    alpha = alpha->back;
  }
  return;
}
} // namespace Memory_Maintain
#endif
