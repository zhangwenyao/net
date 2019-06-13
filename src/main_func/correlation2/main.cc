#include "main.h"
#ifdef MAIN_CORRELATION2

#include "../../common/common.h"
#include "../../network/networks.h"

#ifdef MAIN_CORRELATION2_NEW_NETWORKS
#include "new_networks.h"
#endif

#ifdef MAIN_CORRELATION2_STATISTICS_NETWORKS
#include "statistics_networks.h"
#endif

#ifdef MAIN_CORRELATION2_EVOLUTION
#include "evolution.h"
#endif

using namespace std;
using namespace common;
using namespace network;
using namespace main_func::correlation2;

// **********************************************************
string main_func::correlation2::name, main_func::correlation2::dirData,
    main_func::correlation2::dirStat;

int main_func::main_correlation2(int argc, char** argv)
{
  for (auto& name_i : names) {
    name = name_i;
    dirData = dirData0;
    dirStat = dirStat0;
    mkdirs(dirData.c_str());
    mkdirs(dirStat.c_str());

#ifdef MAIN_CORRELATION2_NEW_NETWORKS
    _ERR(correlation2::new_networks(argc, argv));
#endif

#ifdef MAIN_CORRELATION2_STATISTICS_NETWORKS
    _ERR(correlation2::statistics_networks(argc, argv));
#endif

#ifdef MAIN_CORRELATION2_EVOLUTION
    _ERR(correlation2::evolution(argc, argv));
#endif
  }
  return 0;
}

#endif
