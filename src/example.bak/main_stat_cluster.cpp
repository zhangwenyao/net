// g++ -o main.exe *.cpp -O3 -Wall
#include "net.h"
#ifdef STAT_CLUSTER

#include "common.h"
#include "networks.h"
using namespace std;
//**//****************************************************//*
int main(int argc, char **argv) {
  SHOW_TIME(cout);  // 显示系统时间

  Networks net;
  do {
    net.seed = 1;
    net.weightFlag = 1;
    net.dirFlag = 1;
    net.readName = "data/example/2";
    net.saveName = "data/cluster";
    if (0 != common_read2_0("data/example/2_linkMatr.txt", net.weightMatr) ||
        net.weightMatr.size() <= 0 || net.weightMatr[0].size() <= 0) {
      ERROR();
      break;
    }
    weightMatr_2_linkMatr(net.linkMatr, net.weightMatr);

    net.argv = "--initseed0 --cal_p2p p2p --stat --print --save0";
    // 带参数运行
    if (argc > 1 && 0 != net.read_params(argc - 1, argv + 1).runStatus) {
      ERROR("net.read_params(argc, argv)");
      break;
    }

    // 功能模块
    if (0 != net.run().runStatus) {
      ERROR("net.run");
      net.saveName += "_error";
      net.save();
      break;
    }
  } while (0);

  SHOW_TIME(cout);  // 显示系统时间
  return 0;
}
//**//****************************************************//*
#endif
