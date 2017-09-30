// g++ -o main.exe *.cpp -O3 -Wall
#include "net.h"
#ifdef NET_EXTREMUM

#include "common.h"
#include "networks.h"
using namespace std;
//**//**************************************************//**//*
int main(int argc, char** argv)
{
  SHOW_TIME(cout); // 显示系统时间

  char name[200];
  for (int e = 5; e <= 29; ++e) {
    sprintf(name, "data/extremum/2^%d/2^%d", e, e);
    for (int seed = 1; seed <= 300; ++seed) {
      SHOW_TIME(cout); // 显示系统时间
      Networks net;
      net.saveName = net.readName = name;
      net.nodeSize = 1 << e;        // 节点数
      net.degree.power_gamma = 2.5; // 度分布幂律分布的幂指数
      net.kMin = 4;                 // 最小度
      net.kMax = net.kMin + sqrt(net.nodeSize) - 1; // 最大度
      // net.argv = "cal_deg power cal_p2p Max stat print save0";
      net.argv
          = "init_seed0 cal_deg power_arr cal_p2p Min_lkk stat print save";
      net.seed = seed;

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
        net.save();
        break;
      }
    }
  }

  SHOW_TIME(cout); // 显示系统时间
  return 0;
}
//**//**************************************************//**//*
#endif
