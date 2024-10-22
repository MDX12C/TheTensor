#ifndef INTERFACE_H
#define INTERFACE_H 1
#include "basic.hpp"
#include "define.hpp"
#include "log.hpp"
#include "matrix.hpp"
#include "memory.hpp"
#include "network.hpp"
#include "rom.hpp"
#include "vector.hpp"

#ifndef _SPEED_MODE_
#define _SPEED_MODE_ 0
#endif
#ifndef _AVX2_WILL_BE_USED_ON_
#define _AVX2_WILL_BE_USED_ON_ 0
#endif
#ifndef _SIMD_MODE_
#define _SIMD_MODE_ 0
#endif
#ifndef BASIC_H
#define BASIC_H 0
#endif
#ifndef LOG_H
#define LOG_H 0
#endif
#ifndef MEMORY_H
#define MEMORY_H 0
#endif
#ifndef VECTOR_H
#define VECTOR_H 0
#endif
#ifndef DEFINE_H
#define DEFINE_H 0
#endif
#ifndef MATRIX_H
#define MATRIX_H 0
#endif
#ifndef NETWORK_H
#define NETWORK_H 0
#endif
#ifndef ROM_H
#define ROM_H 0
#endif
#ifndef BASIC_CON
#define BASIC_CON
#endif
#ifndef BASIC_DES
#define BASIC_DES
#endif
#ifndef MEMORY_CON
#define MEMORY_CON
#endif
#ifndef MEMORY_DES
#define MEMORY_DES
#endif
#ifndef VECTOR_CON
#define VECTOR_CON
#endif
#ifndef VECTOR_DES
#define VECTOR_DES
#endif
#ifndef LOG_CON
#define LOG_CON
#endif
#ifndef LOG_DES
#define LOG_DES
#endif
#ifndef MATRIX_CON
#define MATRIX_CON
#endif
#ifndef MATRIX_DES
#define MATRIX_DES
#endif
#ifndef NETWORK_CON
#define NETWORK_CON
#endif
#ifndef NETWORK_DES
#define NETWORK_DES
#endif
#ifndef ROM_CON
#define ROM_CON
#endif
#ifndef ROM_DES
#define ROM_DES
#endif

/**
 * @brief initialize all the constants
 */
#define CONSTRUCT                 \
  if constexpr (LOG_H) {          \
    LOG_CON;                      \
    if constexpr (_SPEED_MODE_) { \
      LOG("S:SPEED MODE\n");      \
    }                             \
  }                               \
  if constexpr (BASIC_H) {        \
    BASIC_CON;                    \
  }                               \
  if constexpr (MEMORY_H) {       \
    MEMORY_CON;                   \
  }                               \
  if constexpr (VECTOR_H) {       \
    VECTOR_CON;                   \
  }                               \
  if constexpr (MATRIX_H) {       \
    MATRIX_CON;                   \
  }                               \
  if constexpr (NETWORK_H) {      \
    NETWORK_CON;                  \
  }                               \
  if constexpr (ROM_H) {          \
    ROM_CON;                      \
  }

/**
 * @brief deinitialize all the constants
 */
#define DESTRUCT             \
  if constexpr (VECTOR_H) {  \
    VECTOR_DES;              \
  }                          \
  if constexpr (MEMORY_H) {  \
    MEMORY_DES;              \
  }                          \
  if constexpr (BASIC_H) {   \
    BASIC_DES;               \
  }                          \
  if constexpr (MATRIX_H) {  \
    MATRIX_DES;              \
  }                          \
  if constexpr (NETWORK_H) { \
    NETWORK_DES;             \
  }                          \
  if constexpr (ROM_H) {     \
    ROM_DES;                 \
  }                          \
  if constexpr (LOG_H) {     \
    LOG_DES;                 \
  }

/**
 * @brief exit
 * @warning don't use it without urgent situation
 */
inline void endOfMainFunction() {
  LOG("B:!!Urgent Exit!!");
  printf("!!Urgent Exit!!\n");
  DESTRUCT;
  exit(1);
}

#endif