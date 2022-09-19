#include "new_networks.h"
#ifdef MAIN_CORRELATION2_NEW_NETWORKS

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;

// **********************************************************
int main_func::correlation2::new_networks(int argc, char** argv)
{
  do {
    Networks net;
    net.readName = dirData + name;
    net.saveName = dirStat + name;
    net.seed = 1;
    net.nodeSize = (NodeType)1 << 17;
    net.argv = "--init_seed";
#ifdef NET_ER
    if (name == "ER") {
      net.random.p = 6.0 / net.nodeSize; // ER
      net.argv += " --cal_p2p ER";
    }
#endif
#ifdef NET_BA
    if (name == "BA" || strncmp(name.c_str(), "BA_", 3) == 0) {
      net.ba.M = 6; // BA
      net.argv += " --cal_p2p BA";
    }
#endif
    net.argv += " --save"
                " --print";

    // 带参数运行
    if (argc > 1 && 0 != net.read_params(argc - 1, argv + 1).runStatus) {
      ERROR("net.read_params(argc, argv)");
      break;
    }

    //功能模块
    if (0 != net.run().runStatus) {
      ERROR("net.run");
      cerr << net << endl;
      net.saveName += "_error";
      net.save_params();
    } else {
      net.saveName += "_origin";
      net.save_params();
    }
  } while (0);
  return 0;
}

#endif
