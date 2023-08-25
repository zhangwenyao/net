#ifndef MAIN__FITNESS_COMPLEXITY__MAIN_H_
#define MAIN__FITNESS_COMPLEXITY__MAIN_H_
#include "../../main.h"
#ifdef MAIN_FITNESS_COMPLEXITY

#include "../../network/net.h"
#include <string>
#define MAIN_FUNC main_func::main_fitness_complexity

//#define MAIN_FITNESS_COMPLEXITY_FILTER
#define MAIN_FITNESS_COMPLEXITY_MAIN
//#define MAIN_FITNESS_COMPLEXITY_RECOMMEND
//#define MAIN_FITNESS_COMPLEXITY_COUNT
//#define MAIN_FITNESS_COMPLEXITY_PLOT_DATA

//#define MAIN_FITNESS_COMPLEXITY
//#define MAIN_STAT_LKK_K
//#define MAIN_STAT_LKK_EXTREMUM
//#define MAIN_STAT_BETWEENNESS

// ******************************************************
namespace main_func {
int main_fitness_complexity(int argc, char** argv);
namespace fitness_complexity {

}
}

// ******************************************************
#endif // MAIN
#endif // _H_
