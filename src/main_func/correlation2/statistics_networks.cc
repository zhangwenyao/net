#include "statistics_networks.h"
#ifdef MAIN_CORRELATION2_STATISTICS_NETWORKS

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;

// **********************************************************
int main_func::correlation2::statistics_networks(int argc, char** argv)
{
  do {
    Networks net;
    net.readName = dirData + name;
    net.saveName = dirStat + name;
    net.argv = "--cal_p2p read_p2p_fix "
               "--stat "
               "--save "
               "--print";

    // 带参数运行
    if (argc > 1 && 0 != net.read_params(argc - 1, argv + 1).runStatus) {
      ERROR("net.read_params(argc, argv)");
      break;
    }

    //功能模块
    if (0 != net.run().runStatus) {
      ERROR("net.run");
      net.saveName += "_error";
      net.save_params();
      cerr << net << endl;
    }
  }
  return 0;
}

#endif
