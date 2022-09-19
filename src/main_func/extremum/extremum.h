#ifndef MAIN__EXTREMUM_H_
#define MAIN__EXTREMUM_H_
#include "main.h"
#ifdef MAIN_EXTREMUM

namespace main_func {
namespace extremum {
  // ******************************************************
#ifdef MAIN_EXTREMUM_NEW_DEG_ARR
  int new_deg_arr(int argc, char** argv);
#endif

#ifdef MAIN_EXTREMUM_NEW_MINIMAL
  int new_minimal(int argc, char** argv);
#endif
#ifdef MAIN_EXTREMUM_NEW_MAXIMAL
  int new_maximal(int argc, char** argv);
#endif
#ifdef MAIN_EXTREMUM_NONE
  int stat_minimal(int argc, char** argv);
  int stat_maximal(int argc, char** argv);
  int stat_all(int argc, char** argv);
#elif defined(STAT_RELATIVITY) && defined(MAIN_EXTREMUM_ALPHAS)
  int alphas_stat_maximal_lkk(int argc, char** argv);
  int alphas_stat_minimal_lkk(int argc, char** argv);
  int alphas_stat_all(int argc, char** argv);
#endif

#ifdef MAIN_EXTREMUM_ALPHAS_STAT_BC_COLLECT
  int stat_bc_collect(int argc, char** argv);
#endif

  // ******************************************************
}
}
#endif // MAIN
#endif // _H_
