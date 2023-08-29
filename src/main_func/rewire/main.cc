#include "main.h"
#ifdef MAIN_REWIRE

#include "../../common/common.h"
#include "../../network/networks.h"
#include "rewire.h"

using namespace std;
using namespace common;
using namespace network;
using namespace main_func::rewire;

// **********************************************************

int main_func::main_rewire(int argc, char** argv)
{
  string dirData = kDataDir, dirStat = kStatDir;
  mkdirs(dirData.c_str());
  mkdirs(dirStat.c_str());

#ifdef MAIN_REWIRE_DISTRIBUTION
  _ERR(rewire::distribution(argc, argv));
#endif

#ifdef MAIN_REWIRE_DISTRIBUTION_STAT
  _ERR(rewire::distribution_stat(argc, argv));
#endif

#ifdef MAIN_REWIRE_DISTRIBUTION_STAT_ALL
  _ERR(rewire::distribution_stat_all(argc, argv));
#endif

#ifdef MAIN_REWIRE_NETWORKS_RANDOM
  _ERR(rewire::networks_random(argc, argv));
#endif

#ifdef MAIN_REWIRE_NETWORKS_RANDOM1
  _ERR(rewire::networks_random1(argc, argv));
#endif

#ifdef MAIN_REWIRE_STAT
  _ERR(rewire::stat(argc, argv));
#endif

#ifdef MAIN_REWIRE_STAT_ALL
  _ERR(rewire::stat_all(argc, argv));
#endif

  return 0;
}

#endif
