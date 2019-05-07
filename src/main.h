#ifndef MAIN_H_
#define MAIN_H_
// g++ *.cpp -O3 -Wall -std=c++11 -o main.exe
//#include "common/common.h"
#include <string>

// *******************************************************
//#define MAIN_TEST

//#define MAIN_NET_BA
#define MAIN_EXTREMUM

//#define MAIN_STAT_LKK_K
//#define MAIN_STAT_LKK_EXTREMUM
//#define MAIN_STAT_BETWEENNESS

//#define FITNESS_COMPLEXITY_MAIN_FILTER
//#define FITNESS_COMPLEXITY_MAIN
//#define FITNESS_COMPLEXITY_MAIN_RECOMMEND
//#define FITNESS_COMPLEXITY_MAIN_COUNT
//#define FITNESS_COMPLEXITY_MAIN_PLOTDATA

// *******************************************************
#ifdef MAIN_TEST
#include "test.h"
#endif

#ifdef MAIN_NET_BA
int main_net_ba(int argc, char** argv);
#endif

#ifdef MAIN_EXTREMUM
#include "main_func/extremum/main.h"
#endif

#ifdef FITNESS_COMPLEXITY_MAIN_FILTER
int main_fitness_complexity_filter(int argc, char** argv);
#endif

#ifdef FITNESS_COMPLEXITY_MAIN
int main_fitness_complexity(int argc, char** argv);
#endif

#ifdef FITNESS_COMPLEXITY_MAIN_RECOMMEND
int main_fitness_complexity_recommend(int argc, char** argv);
#endif

#ifdef FITNESS_COMPLEXITY_MAIN_COUNT
int main_fitness_complexity_count(int argc, char** argv);
#endif

#ifdef FITNESS_COMPLEXITY_MAIN_PLOTDATA
int main_fitness_complexity_plotdata(int argc, char** argv);
#endif

// *******************************************************
namespace main_func {
}
// *******************************************************
#endif
