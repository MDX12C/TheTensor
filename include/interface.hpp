#ifndef INTERFACE_HH
#define INTERFACE_HH 1

#include "mnist/mnist_reader.hpp"
#include "thetensor/basic.hpp"
#include "thetensor/define.h"
#include "thetensor/define.hpp"
#include "thetensor/file.hpp"
#include "thetensor/log.hpp"
#include "thetensor/matrix.hpp"
#include "thetensor/memory.hpp"
#include "thetensor/network.hpp"
#include "thetensor/parallel.h"
#include "thetensor/random.hpp"
#include "thetensor/story.hpp"
#include "thetensor/vector.hpp"

/**
 * @brief initialize all the constants
 */
#define CONSTRUCT                   \
  do {                              \
    LOG_HH_CON;                     \
    if constexpr (__SPEED_MODE__) { \
      LOG("S:SPEED MODE\n");        \
    }                               \
    RANDOM_HH_CON;                  \
    BASIC_HH_CON;                   \
    MEMORY_HH_CON;                  \
    LOG("S:main start");            \
  } while (false);
/**
 * @brief deinitialize all the constants
 */
#define DESTRUCT       \
  do {                 \
    LOG("S:main end"); \
    LOG_HH_DES(false); \
  } while (false);

/**
 * @brief exit
 * @warning don't use it without urgent situation
 */
inline __attribute__((__noreturn__)) void endOfMainFunction() noexcept {
  LOG("S:!!Urgent Exit!!");
  printf("!!Urgent Exit!!\n");
  LOG_HH_DES(true);
  exit(1);
}

#endif