#include "main.h"

#include "common/common.h"
using namespace std;
using namespace common;

// *******************************************************
#ifdef MAIN_TEST
#include "test.h"
#endif

#ifdef MAIN_DATA
#include "main_func/data/main.h"
#endif

#ifdef MAIN_DISTRIBUTION
#include "main_func/distribution/main.h"
#endif

#ifdef MAIN_EXTREMUM
#include "main_func/extremum/main.h"
#endif

#ifdef MAIN_CORRELATION2
#include "main_func/correlation2/main.h"
#endif

#ifdef MAIN_SPEARMAN
#include "main_func/spearman/main.h"
#endif

#ifdef MAIN_REWIRE
#include "main_func/rewire/main.h"
#endif

#ifdef MAIN_FITNESS_COMPLEXITY
#include "main_func/fitness_complexity/main.h"
#endif

#ifdef MAIN_BETWEENNESS
#include "main_func/betweenness/main.h"
#endif

#ifdef MAIN_SPREADER
#include "main_func/spreader/main.h"
#endif

#ifndef MAIN_FUNC
#define MAIN_FUNC main_default
namespace {
int main_default(int argc, char **argv) {
  for (int i = 0; i < argc && argv[i] != NULL; ++i) {
    cout << i << '\t' << argv[i] << '\n';
  }
  return EXIT_SUCCESS;
}
}  // namespace
#endif

// **********************************************************

int main(int argc, char **argv) {
  // std::ios::sync_with_stdio(false);
  // cin.tie(NULL);
  // common::SHOW_TIME(cout);  // 显示系统时间
  INFORM("START...");
  init_config();

#ifdef MAIN_FUNC_DATA
  _ERR(MAIN_FUNC_DATA(argc, argv));
#endif

  _ERR(MAIN_FUNC(argc, argv));

  INFORM("DONE!");
  // common::SHOW_TIME(cout);  // 显示系统时间
  return EXIT_SUCCESS;
}
