#ifndef MAIN__SPEARMAN_H_
#define MAIN__SPEARMAN_H_
#include "main.h"
#ifdef MAIN_SPEARMAN

namespace main_func {
namespace spearman {
  // ******************************************************
  int networks_random(int argc, char** argv);
  int networks_gauss(int argc, char** argv);
  int networks_r_random(int argc, char** argv);
  int networks_r_gauss(int argc, char** argv);
  int networks_r_stat(int argc, char** argv);
  int networks_test(int argc, char** argv);

  // ******************************************************
}
}
#endif // MAIN
#endif // _H_
