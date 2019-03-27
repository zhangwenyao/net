// g++ -o main.exe *.cpp -O3 -Wall -std=c++11
#include "main.h"
#include "common.h"
#include "networks.h"
using namespace std;
// **********************************************************

int main(int argc, char** argv)
{
  SHOW_TIME(cout); // 显示系统时间

#ifdef MAIN_NET_BA
  _ERR(main_net_ba(argc, argv));
#endif

#ifdef MAIN_NET_EXTREMUM
  _ERR(main_net_extremum(argc, argv));
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

  SHOW_TIME(cout); // 显示系统时间
  return 0;
}
