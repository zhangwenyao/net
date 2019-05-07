#include "main.h"
#ifdef MAIN_EXTREMUM

#include "../../common/common.h"
using namespace std;
using namespace common;

// **********************************************************
int main_func::main_extremum(int argc, char** argv)
{
#ifdef MAIN_EXTREMUM_NEW
  _ERR(extremum_new(argc, argv));
#endif

#ifdef MAIN_EXTREMUM_STAT
  _ERR(extremum_stat(argc, argv));
#endif

  return 0;
}

#endif
