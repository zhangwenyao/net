#include "main.h"
#ifdef MAIN_SPEARMAN

#include "../../common/common.h"
#include "../../network/net.h"
#include "spearman.h"

using namespace std;
using namespace common;
using namespace network;
using namespace main_func::spearman;

// ******************************************************
int main_func::main_spearman(int argc, char** argv)
{
  string dirData = kDataDir, dirStat = kStatDir;
  mkdirs(dirData.c_str());
  mkdirs(dirStat.c_str());

#ifdef MAIN_SPEARMAN_RANDOM
  _ERR(spearman::networks_random(argc, argv));
#endif

#ifdef MAIN_SPEARMAN_GAUSS
  _ERR(spearman::networks_gauss(argc, argv));
#endif

#ifdef MAIN_SPEARMAN_R_RANDOM
  _ERR(spearman::networks_r_random(argc, argv));
#endif

#ifdef MAIN_SPEARMAN_R_GAUSS
  _ERR(spearman::networks_r_gauss(argc, argv));
#endif

#ifdef MAIN_SPEARMAN_R_STAT
  _ERR(spearman::networks_r_stat(argc, argv));
#endif

#ifdef MAIN_SPEARMAN_TEST
  _ERR(spearman::networks_test(argc, argv));
#endif

  return 0;
}

#endif
