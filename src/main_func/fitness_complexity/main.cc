#include "main.h"
#ifdef MAIN_FITNESS_COMPLEXITY

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;
using namespace main_func::fitness_complexity;

// **********************************************************
int main_func::main_fitness_complexity(int argc, char** argv)
{
#ifdef FITNESS_COMPLEXITY_MAIN_FILTER
  _ERR(main_fitness_complexity_filter(argc, argv));
#endif

#ifdef FITNESS_COMPLEXITY_MAIN
  _ERR(main_fitness_complexity(argc, argv));
#endif

#ifdef FITNESS_COMPLEXITY_MAIN_RECOMMEND
  _ERR(main_fitness_complexity_recommend(argc, argv));
#endif

#ifdef FITNESS_COMPLEXITY_MAIN_COUNT
  _ERR(main_fitness_complexity_count(argc, argv));
#endif

#ifdef FITNESS_COMPLEXITY_MAIN_PLOTDATA
  _ERR(main_fitness_complexity_plotdata(argc, argv));
#endif

  return 0;
}

#endif
