#ifndef MAIN__FITNESS_COMPLEXITY__MAIN_H_
#define MAIN__FITNESS_COMPLEXITY__MAIN_H_
#include "../../main.h"
#ifdef MAIN_FITNESS_COMPLEXITY

#include <string>

#include "../../network/net.h"
#define MAIN_FUNC main_func::main_fitness_complexity

#define MAIN_FITNESS_COMPLEXITY_HOTEL
// #define MAIN_FITNESS_COMPLEXITY_HOTEL_FILTER
#define MAIN_FITNESS_COMPLEXITY_HOTEL_MAIN

//#define MAIN_FITNESS_COMPLEXITY_FILTER
//#define MAIN_FITNESS_COMPLEXITY_MAIN
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
const std::string DIR_DAT =
    std::string("/Users/zwy/data/xiaotong_trip_hotel_order/");
const std::string DIR_DATA = std::string("data/hotel/");
// const std::string DATA_PRE = "";
const std::string DATA_PRE = "ordNum2_";

constexpr int YEAR1 = 2016, YEAR2 = 2016;
// const int YEAR1 = 2016, YEAR2 = 2021;
}  // namespace fitness_complexity
}  // namespace main_func

// ******************************************************
#endif  // MAIN
#endif  // _H_
