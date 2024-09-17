#ifndef INTERFACE_H
#define INTERFACE_H 1
#include "basic.hpp"
#include "define.hpp"
#include "log.hpp"
#include "memory.hpp"
#include "vector.hpp"

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

/**
 * @brief initialize all the constants
 */
#define CONSTRUCT           \
  if constexpr (LOG_H) {    \
    LOG_CON;                \
  }                         \
  if constexpr (BASIC_H) {  \
    BASIC_CON;              \
  }                         \
  if constexpr (MEMORY_H) { \
    MEMORY_CON;             \
  }                         \
  if constexpr (VECTOR_H) { \
    VECTOR_CON;             \
  }

/**
 * @brief deinitialize all the constants
 */
#define DESTRUCT            \
  if constexpr (LOG_H) {    \
    LOG_DES;                \
  }                         \
  if constexpr (VECTOR_H) { \
    VECTOR_DES;             \
  }                         \
  if constexpr (MEMORY_H) { \
    MEMORY_DES;             \
  }                         \
  if constexpr (BASIC_H) {  \
    BASIC_DES;              \
  }

#endif