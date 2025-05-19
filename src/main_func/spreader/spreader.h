#ifndef MAIN__SPREADER_H_
#define MAIN__SPREADER_H_
#include "main.h"
#ifdef MAIN_SPREADER

namespace main_func {
namespace spreader {
// ******************************************************
#ifdef MAIN_SPREADER_DATA
int networks_data(int argc, char** argv);
#endif
#ifdef MAIN_SPREADER_CALC
int networks_calc(int argc, char** argv);
#endif
#ifdef MAIN_SPREADER_STAT
int networks_stat(int argc, char** argv);
#endif
#ifdef MAIN_SPREADER_TEST
int networks_test(int argc, char** argv);
#endif

// ******************************************************
}  // namespace spreader
}  // namespace main_func
#endif  // MAIN
#endif  // _H_
