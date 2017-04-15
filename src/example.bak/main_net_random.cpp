// g++ -o main.exe *.cpp -O3 -Wall
#include "networks.h"
#ifdef NET_RANDOM

#include "common.h"
using namespace std;
//**//********************************************************************
int main(int argc, char **argv) {
  SHOW_TIME(cout);  // 显示系统时间

  do {
    Networks net;
    net.saveName = net.readName = "data/random";
    net.nodeSize = 1000;            // 节点数
    net.degree.power_gamma = 2.7;  // 度分布幂律分布的幂指数
    net.kMin = 3;
    net.seed = 1;
    net.argv = "init_seed cal_deg power cal_p2p random stat print save";

    // 带参数运行
    if (argc > 1 && 0 != net.read_params(argc - 1, argv + 1).runStatus) {
      ERROR("net.read_params(argc, argv)");
      break;
    }

    net.kMax = net.kMin * pow(net.nodeSize, 1 / (net.degree.power_gamma - 1.));
    if (net.kMax < net.kMin) net.kMax = net.kMin;
    if (net.kMax >= net.nodeSize) net.kMax = net.nodeSize - 1;

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
//**//********************************************************************
#endif
