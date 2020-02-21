#include "main.h"
#ifdef MAIN_EXTREMUM

#include "../../common/common.h"
#include "../../network/net.h"

#ifdef MAIN_EXTREMUM_NEW_DEG_ARR
#include "new_deg_arr.h"
#endif

#ifdef MAIN_EXTREMUM_NEW_MINIMAL
#include "new_minimal.h"
#endif

#ifdef MAIN_EXTREMUM_NEW_MAXIMAL
#include "new_maximal.h"
#endif

#ifdef MAIN_EXTREMUM_STAT_MINIMAL
#include "stat_minimal.h"
#endif

#ifdef MAIN_EXTREMUM_STAT_MAXIMAL
#include "stat_maximal.h"
#endif

#ifdef MAIN_EXTREMUM_STAT_ALL
#include "stat_all.h"
#endif

using namespace std;
using namespace common;
using namespace network;
using namespace main_func::extremum;

// ******************************************************
#ifdef STAT_RELATIVITY
double main_func::extremum::relativity_alpha;
string main_func::extremum::alpha_string, main_func::extremum::kStatDir;
#endif

int main_func::main_extremum(int argc, char** argv)
{
#ifdef MAIN_EXTREMUM_NEW_DEG_ARR
  _ERR(extremum::new_deg_arr(argc, argv));
#endif

#ifdef MAIN_EXTREMUM_NEW_MINIMAL
  _ERR(extremum::new_minimal(argc, argv));
#endif

#ifdef MAIN_EXTREMUM_NEW_MAXIMAL
  _ERR(extremum::new_maximal(argc, argv));
#endif

#ifndef STAT_RELATIVITY
#ifndef MAIN_EXTREMUM_STAT_ALL_COLLECT
#ifdef MAIN_EXTREMUM_STAT_MINIMAL
  _ERR(extremum::stat_minimal(argc, argv));
#endif
#ifdef MAIN_EXTREMUM_STAT_MAXIMAL
  _ERR(extremum::stat_maximal(argc, argv));
#endif
#endif
#ifdef MAIN_EXTREMUM_STAT_ALL
  _ERR(extremum::stat_all(argc, argv));
#endif

#else  // ifdef STAT_RELATIVITY
  /*
  for (size_t i = 0; i < alpha_len; ++i) {
    relativity_alpha = relativity_alphas[i];
    alpha_string = alpha_strings[i];
    kStatDir = main_func_extremum_kStatDir0;
#ifndef MAIN_EXTREMUM_STAT_ALL_COLLECT
#ifdef MAIN_EXTREMUM_STAT_MINIMAL
    _ERR(extremum::stat_minimal(argc, argv));
#endif
#ifdef MAIN_EXTREMUM_STAT_MAXIMAL
    _ERR(extremum::stat_maximal(argc, argv));
#endif
#endif
#ifdef MAIN_EXTREMUM_STAT_ALL
    _ERR(extremum::stat_all(argc, argv));
#endif
  }
  */
  kStatDir = main_func_extremum_kStatDir0;
  _ERR(extremum::stat_maximal_lkk_alphas(argc, argv));
#endif // STAT_RELATIVITY

  return 0;
}

#endif
