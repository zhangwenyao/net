#ifndef MAIN_H_
#define MAIN_H_
// g++ *.cpp -O3 -Wall -std=c++11 -o main.exe
//#include "common/common.h"
#include <string>

// *******************************************************
//#define MAIN_TEST

//#define MAIN_NET_BA
//#define MAIN_NET_ER
//#define MAIN_EXTREMUM
#define MAIN_CORRELATION2
//#define MAIN_FITNESS_COMPLEXITY

//#define MAIN_STAT_LKK_K
//#define MAIN_STAT_LKK_EXTREMUM
//#define MAIN_STAT_BETWEENNESS

// *******************************************************
#ifdef MAIN_TEST
#include "test.h"
#define MAIN_FUNC main_test
#endif

#ifdef MAIN_NET_BA
#include "main_func/ba/main.h"
#define MAIN_FUNC main_ba
#endif

#ifdef MAIN_EXTREMUM
#include "main_func/extremum/main.h"
#define MAIN_FUNC main_extremum
#endif

#ifdef MAIN_CORRELATION2
#include "main_func/correlation2/main.h"
#define MAIN_FUNC main_correlation2
#endif

#ifdef MAIN_FITNESS_COMPLEXITY
#include "main_func/fitness_complexity/main.h"
#define MAIN_FUNC main_fitness_complexity
#endif

// *******************************************************
namespace main_func {
}
// *******************************************************
#endif
