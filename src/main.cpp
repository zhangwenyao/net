// g++ -o main.exe *.cpp -O3 -Wall -std=c++11
#include "main.h"
#include "common.h"
#include "networks.h"
using namespace std;
// **********************************************************

int main(int argc, char** argv)
{
  SHOW_TIME(cout); // 显示系统时间

#ifdef MAIN_FITNESS_COMPLEXITY_FILTER
  ERROR_TEST(main_fitness_complexity_filter(argc, argv));
#endif

#ifdef MAIN_FITNESS_COMPLEXITY
  ERROR_TEST(main_fitness_complexity(argc, argv));
#endif

#ifdef MAIN_FITNESS_COMPLEXITY_RECOMMEND
  ERROR_TEST(main_fitness_complexity_recommend(argc, argv));
#endif

#ifdef MAIN_FITNESS_COMPLEXITY_COUNT
  ERROR_TEST(main_fitness_complexity_count(argc, argv));
#endif

#ifdef MAIN_FITNESS_COMPLEXITY_PLOTDATA
  ERROR_TEST(main_fitness_complexity_plotdata(argc, argv));
#endif

  SHOW_TIME(cout); // 显示系统时间
  return 0;
}
