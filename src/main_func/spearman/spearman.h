#ifndef MAIN__SPEARMAN_H_
#define MAIN__SPEARMAN_H_
#include "main.h"
#ifdef MAIN_SPEARMAN

namespace main_func {
namespace spearman {
  // ******************************************************
#if defined MAIN_SPEARMAN_RANDOM
  int networks_random(int argc, char** argv);
#elif defined MAIN_SPEARMAN_GAUSS
  int networks_gauss(int argc, char** argv);
#elif defined MAIN_SPEARMAN_R_RANDOM
  int networks_r_random(int argc, char** argv);
#elif defined MAIN_SPEARMAN_R_GAUSS
  int networks_r_gauss(int argc, char** argv);
#elif defined MAIN_SPEARMAN_R_STAT
  int networks_r_stat(int argc, char** argv);
#elif defined MAIN_SPEARMAN_TEST
  int networks_test(int argc, char** argv);
#endif

  // ******************************************************
}
}
#endif // MAIN
#endif // _H_
