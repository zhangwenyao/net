// g++ -o main.exe *.cpp -O3 -Wall
#include "common.h"
#include "networks.h"
#ifdef NET_EXTREMUM

using namespace std;
//**//********************************************************************
int main(int argc, char **argv) {
  SHOW_TIME(cout);  // 显示系统时间

  do {
    Network net;
    net.saveName = net.readName = "data/Max_power2.5";
    net.nodeSize = 1024;               // 节点数
    net.params_degree.power_gamma = 2.5;  // 度分布幂律分布的幂指数
    net.kMin = 4;                      // 最小度
    net.kMax = net.kMin + sqrt(net.nodeSize) - 1;  // 最大度
    while (0 == (net.seed = RAND2_INIT(net.seed)));  // 初始化随机数种子
    if (0 != net_run(net, "cal_deg power cal_p2p Max save")) {
      ERROR();
      break;
    }
  } while (0);

  SHOW_TIME(cout);  // 显示系统时间
  return 0;
}
//**//********************************************************************
#endif
