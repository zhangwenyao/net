#include "networks.h"
#ifdef NET_BA

#include "common.h"
using namespace std;
//**//**************************************************//**//*
int main(int argc, char **argv) {
  SHOW_TIME(cout);  // 显示系统时间

  do {
    Networks net;
    net.saveName = net.readName = "data/BA";
    net.nodeSize = 100;  // 节点数
    net.ba.M0 = 3;
    net.ba.M = 2;
    net.seed = -1;
    net.argv = "init_seed0 cal_p2p BA stat print save0";

    // 带参数运行
    if (argc > 1 && 0 != net.read_params(argc - 1, argv + 1).runStatus) {
      ERROR("net.read_params(argc, argv)");
      break;
    }

    // 功能模块
    if (0 != net.run().runStatus) {
      ERROR("net.run");
      cerr << net << endl;
      break;
    }
  } while (0);

  SHOW_TIME(cout);  // 显示系统时间
  return 0;
}
//**//**************************************************//**//*
#endif
