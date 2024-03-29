#include "main.h"
#ifdef MAIN_EXTREMUM

#include "../../common/common.h"
#include "../../network/net.h"
#include "extremum.h"

using namespace std;
using namespace common;
using namespace network;
using namespace main_func::extremum;

// ******************************************************
#ifdef STAT_RELATIVITY
double main_func::extremum::relativity_alpha = 0;
string main_func::extremum::alpha_string, main_func::extremum::kStatDir;
#endif

int main_func::main_extremum(int argc, char** argv)
{
#ifdef MAIN_EXTREMUM_NEW_DEG_ARR
  _ERR(extremum::new_deg_arr(argc, argv));
#endif

#if defined(MAIN_EXTREMUM_NONE)
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
#endif // ifdef MAIN_EXTREMUM_STAT_ALL_COLLECT
#ifdef MAIN_EXTREMUM_STAT_ALL
  _ERR(extremum::stat_all(argc, argv));
#endif

#else // ifdef STAT_RELATIVITY
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
#endif // ifndef MAIN_EXTREMUM_STAT_ALL_COLLECT
#ifdef MAIN_EXTREMUM_STAT_ALL
    _ERR(extremum::stat_all(argc, argv));
#endif
  }
#endif // ifdef STAT_RELATIVITY

#elif defined(MAIN_EXTREMUM_ALPHAS)
  kStatDir = main_func_extremum_kStatDirAlphas;
#ifdef MAIN_EXTREMUM_ALPHAS_STAT_MAXIMAL
  _ERR(extremum::alphas_stat_maximal_lkk(argc, argv));
#endif
#ifdef MAIN_EXTREMUM_ALPHAS_STAT_MINIMAL
  _ERR(extremum::alphas_stat_minimal_lkk(argc, argv));
#endif
#if defined(MAIN_EXTREMUM_ALPHAS_STAT_MAXIMAL_COLLECT)                       \
    || defined(MAIN_EXTREMUM_ALPHAS_STAT_MINIMAL_COLLECT)
  _ERR(extremum::alphas_stat_all(argc, argv));
#endif

#ifdef MAIN_EXTREMUM_ALPHAS_STAT_BC_COLLECT
  _ERR(extremum::stat_bc_collect(argc, argv));
#endif

  return 0;
}

#endif
