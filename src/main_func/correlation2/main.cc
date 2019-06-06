#include "main.h"
#ifdef MAIN_CORRELATION2

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;
using namespace main_func::correlation2;

// **********************************************************
int main_func::main_correlation2(int argc, char** argv)
{
  do {
    Networks net;
    net.readName = dirData + "www";
    net.saveName = dirStat + "www";
    net.argv = "--cal_deg read_degArr --cal_p2p read_p2p --stat --print";

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
      net.save_params();
    }
  } while (0);
  return 0;
}

#endif
