#include "main.h"
#include "common/common.h"

using namespace std;
using namespace main_func;

// **********************************************************
int main(int argc, char** argv)
{
  common::SHOW_TIME(cout); // 显示系统时间

#ifdef MAIN_TEST
  test(argc, argv);
#endif

#ifdef MAIN_NET_BA
  _ERR(main_net_ba(argc, argv));
#endif

#ifdef MAIN_EXTREMUM
  _ERR(main_extremum(argc, argv));
#endif

#ifdef MAIN_CORRELATION2
  _ERR(main_correlation2(argc, argv));
#endif

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

  common::SHOW_TIME(cout); // 显示系统时间
  return 0;
}
