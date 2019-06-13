#include "evolution.h"
#ifdef MAIN_CORRELATION2_EVOLUTION

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;

// **********************************************************
int main_func::correlation2::evolution(int argc, char** argv)
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
      cerr << net << endl;
      net.saveName += "_error";
      net.save_params();
    } else {
      // net.saveName += "_origin";
      // net.save_params();
    }
  } while (0);
  return 0;
}

#endif
