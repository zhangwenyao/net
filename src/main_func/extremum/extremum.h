#ifndef MAIN__EXTREMUM_H_
#define MAIN__EXTREMUM_H_
#include "main.h"
#ifdef MAIN_EXTREMUM

namespace main_func {
namespace extremum {
  // ******************************************************
  int new_deg_arr(int argc, char** argv);
  int new_minimal(int argc, char** argv);
  int new_maximal(int argc, char** argv);
  int stat_minimal(int argc, char** argv);
  int stat_maximal(int argc, char** argv);
  int stat_all(int argc, char** argv);

#ifdef STAT_RELATIVITY
  int alphas_stat_maximal_lkk(int argc, char** argv);
#endif
  // ******************************************************
}
}
#endif // MAIN
#endif // _H_
