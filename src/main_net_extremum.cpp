// g++ -o main.exe *.cpp -O3 -Wall
#include "net.h"
#ifdef NET_EXTREMUM

#include "common.h"
#include "networks.h"
using namespace std;
//**//**************************************************//**//*
int main(int argc, char **argv) {
  SHOW_TIME(cout);  // 显示系统时间

  do {
    Networks net;
    net.saveName = net.readName = "data/extremum/e";
    net.nodeSize = 1000;           // 节点数
    net.degree.power_gamma = 2.5;  // 度分布幂律分布的幂指数
    net.kMin = 4;                  // 最小度
    net.kMax = net.kMin + sqrt(net.nodeSize) - 1;  // 最大度
    //net.argv = "cal_deg power cal_p2p Max stat print save0";
    net.argv = "cal_deg power cal_p2p Max stat print save";

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
