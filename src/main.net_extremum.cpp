// g++ -o main.exe *.cpp -O3 -Wall
#include "main.h"
#ifdef MAIN_NET_EXTREMUM

#include "common.h"
#include "networks.h"
using namespace std;
//**//**************************************************//**//*
int main(int argc, char** argv)
{
  SHOW_TIME(cout); // 显示系统时间

  char name[200];
  const int EMIN = 27, EMAX = 29, seed_min = 1, seed_max = 300;
  const string dirRead = "/media/yao/Server1T/net/data/power/nature",
               dirSave = "/media/yao/Server1T/net/data/extremum/nature";
  for (int e = EMIN; e <= EMAX; ++e) {
    for (int seed = seed_min; seed <= seed_max; ++seed) {
      SHOW_TIME(cout); // 显示系统时间
      cout << "--e\t" << e << "\n"
           << "--seed\t" << seed << endl;
      Networks net;
      net.seed = seed;
      sprintf(name, "%s/2^%d/4_2.5_%ld", dirRead.c_str(), e, net.seed);
      net.readName = name;
      sprintf(name, "%s/2^%d/4_2.5_max", dirSave.c_str(), e);
      net.saveName = name;
      net.nodeSize = 1 << e;        // 节点数
      net.degree.power_gamma = 2.5; // 度分布幂律分布的幂指数
      net.kMin = 4;                 // 最小度
      net.argv = "--init_seed0 --cal_deg read_degArr --cal_p2p Max_lkk";
      net.lkk_saveType = 3;
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
      } else {
        net.save_params();
        string fn;
        stringstream ss;
        ss.clear();
        ss << seed;
        fn = net.saveName + "_" + ss.str();
        save_lkk_3((fn + ".lkk3.txt").c_str(), net.lkk);
      }
    }
  }

  SHOW_TIME(cout); // 显示系统时间
  return 0;
}
//**//**************************************************//**//*
#endif
