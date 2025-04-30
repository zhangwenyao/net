#ifndef MAIN__BETWEENNESS_H_
#define MAIN__BETWEENNESS_H_
#include "main.h"
#ifdef MAIN_BETWEENNESS

namespace main_func {
namespace betweenness {
// ******************************************************
#ifdef MAIN_BETWEENNESS_DATA
int networks_data(int argc, char** argv);
#endif
#ifdef MAIN_BETWEENNESS_STAT
int networks_stat(int argc, char** argv);
#endif
#ifdef MAIN_BETWEENNESS_TEST
int networks_test(int argc, char** argv);
#endif

// ******************************************************
}  // namespace betweenness
}  // namespace main_func
#endif  // MAIN
#endif  // _H_
