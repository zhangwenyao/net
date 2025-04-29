#include "main.h"
#ifdef MAIN_BETWEENNESS

#include "../../common/common.h"
// #include "../../network/net.h"
#include "betweenness.h"

using namespace std;
using namespace common;
// using namespace network;
using namespace main_func::betweenness;

int main_func::check_args(int argc, char** argv) {
  return EXIT_SUCCESS;
}

// ******************************************************
int main_func::main_betweenness(int argc, char** argv) {
  string dirData = kDataDir, dirStat = kStatDir;
  mkdirs(dirStat.c_str());

  check_args(argc, argv);

#ifdef MAIN_BETWEENNESS_DATA
  _ERR(betweenness::networks_data(argc, argv));
#endif

#ifdef MAIN_BETWEENNESS_STAT
  _ERR(betweenness::networks_stat(argc, argv));
#endif
#ifdef MAIN_BETWEENNESS_STAT_BOOST
  _ERR(betweenness::networks_stat_boost(argc, argv));
#endif

#ifdef MAIN_BETWEENNESS_TEST
  _ERR(betweenness::networks_test(argc, argv));
#endif

  return 0;
}

#endif
