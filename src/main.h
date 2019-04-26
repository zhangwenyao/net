#ifndef MAIN_H_
#define MAIN_H_
// g++ *.cpp -O3 -Wall -std=c++11 -o main.exe
//#include "common/common.h"
#include <string>

// *******************************************************
#define MAIN_TEST

//#define MAIN_NET_BA
//#define MAIN_NET_EXTREMUM

//#define MAIN_STAT_LKK_K
//#define MAIN_STAT_LKK_EXTREMUM
//#define MAIN_STAT_BETWEENNESS

//#define FITNESS_COMPLEXITY_MAIN_FILTER
//#define FITNESS_COMPLEXITY_MAIN
//#define FITNESS_COMPLEXITY_MAIN_RECOMMEND
//#define FITNESS_COMPLEXITY_MAIN_COUNT
//#define FITNESS_COMPLEXITY_MAIN_PLOTDATA

// *******************************************************
//namespace main_vars {
////#define MAIN_FILTER 0
//#define MAIN_FILTER 1E9
//const int YEAR1 = 2001, YEAR2 = 2014; // YEAR_FILTER = 2008;
//const std::string DIR0 = "data/complexity/OEC.sitc_rev2/",
                  //DIR_DATA0 = DIR0 + "data0/", DIR_INFO = DIR0 + "info/",
                  //DIR_DATA = DIR0 + "data/" + TOSTRING(MAIN_FILTER) + "/",
                  //DIR_COMMON = DIR0 + "dataCommon/", ep_dir2 = ".export.txt",
                  //mcp_dir2 = ".mcp.txt", rcm_dir2 = ".rcm.txt";
//// const string methods[] = { "mass", "heat", "hybrid", "proximity" };
//const std::string methods[] = { "proximity_wcp", "proximity_phi" };
//const size_t NMETHOD = sizeof(methods) / sizeof(methods[0]);
//}

// *******************************************************
#ifdef MAIN_TEST
#include "test.h"
#endif

#ifdef MAIN_NET_BA
int main_net_ba(int argc, char** argv);
#endif

#ifdef MAIN_NET_EXTREMUM
int main_net_extremum(int argc, char** argv);
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
#endif
