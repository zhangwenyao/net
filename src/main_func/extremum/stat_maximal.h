#ifndef MAIN__EXTREMUM__STAT_MAXIMAL_H_
#define MAIN__EXTREMUM__STAT_MAXIMAL_H_
#include "main.h"
#ifdef MAIN_EXTREMUM_STAT_MAXIMAL

namespace main_func {
namespace extremum {
  // ******************************************************
  int stat_maximal(int argc, char** argv);

#ifdef STAT_RELATIVITY
  int stat_maximal_lkk_alphas(int argc, char** argv);
#endif

  // ******************************************************
}
}
#endif // MAIN
#endif // _H_
