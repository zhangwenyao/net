#ifndef MAIN__FITNESS_COMPLEXITY__MAIN_H_
#define MAIN__FITNESS_COMPLEXITY__MAIN_H_
#include "../../main.h"
#ifdef MAIN_FITNESS_COMPLEXITY

#include <ctime>
#include <string>

#include "../../network/net.h"
#define MAIN_FUNC main_func::main_fitness_complexity

//#define MAIN_FITNESS_COMPLEXITY_FILTER
// #define MAIN_FITNESS_COMPLEXITY_MAIN
//#define MAIN_FITNESS_COMPLEXITY_RECOMMEND
//#define MAIN_FITNESS_COMPLEXITY_COUNT
//#define MAIN_FITNESS_COMPLEXITY_PLOT_DATA

#define MAIN_FITNESS_COMPLEXITY_USER_ITEM

//#define MAIN_FITNESS_COMPLEXITY
//#define MAIN_STAT_LKK_K
//#define MAIN_STAT_LKK_EXTREMUM
//#define MAIN_STAT_BETWEENNESS

// ******************************************************
namespace main_func {
int main_fitness_complexity(int argc, char **argv);
namespace fitness_complexity {
const std::string DIR_DAT =
    std::string("/Users/zwy/data/xiaotong_trip_hotel_order/ds/");
const std::string DIR_DATA = std::string("data");
}  // namespace fitness_complexity
}  // namespace main_func

// ******************************************************
#endif  // MAIN
#endif  // _H_
