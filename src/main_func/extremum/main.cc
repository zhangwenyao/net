#include "main.h"
#ifdef MAIN_EXTREMUM

#include "../../common/common.h"
using namespace std;
using namespace common;

// **********************************************************
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

  return 0;
}

#endif
