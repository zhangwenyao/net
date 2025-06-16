#ifndef MAIN__INDEXES_H_
#define MAIN__INDEXES_H_
#include "main.h"
#ifdef MAIN_INDEXES

namespace main_func {
namespace indexes {
// ******************************************************
#ifdef MAIN_INDEXES_DATA
int networks_data(int argc, char** argv);
#endif
#ifdef MAIN_INDEXES_STAT
int networks_stat(int argc, char** argv);
#endif
#ifdef MAIN_INDEXES_TEST
int networks_test(int argc, char** argv);
#endif

// ******************************************************
}  // namespace indexes
}  // namespace main_func
#endif  // MAIN
#endif  // _H_
