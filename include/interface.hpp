#ifndef INTERFACE_H
#define INTERFACE_H 1
#include "basic.hpp"
#include "define.hpp"
#include "memory.hpp"
#include "vector.hpp"

/**
 * @brief initialize all the constants
 */
#define INITIALIZE                      \
  do {                                  \
    if constexpr (BASIC_H) {            \
      basic_math::BasicSupport::init(); \
    }                                   \
  } while (false);

#endif