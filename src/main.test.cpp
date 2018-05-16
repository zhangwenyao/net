// g++ -o main.exe *.cpp -O3 -Wall
#include "main.h"
#ifdef MAIN_TEST

#include "common.h"
#include "networks.h"
using namespace std;
//**//**************************************************//**//*
int main(int argc, char** argv)
{
  SHOW_TIME(cout); // 显示系统时间

  const int seed_max = 1, EMIN = 7, EMAX = 7;
  string dir = "data/test", name, fn;
  stringstream ss;
  for (int e = EMIN; e <= EMAX; ++e) {
    cout << e << endl;
    ss.clear();
    ss.str("");
    ss << dir << "/2^" << e;
    name = ss.str();
    for (int seed = 1; seed <= seed_max; ++seed) {
      cout << seed << endl;
      Networks net;
      net.saveName = net.readName = name;
      net.nodeSize = 1 << e;        // 节点数
      net.degree.power_gamma = 2.5; // 度分布幂律分布的幂指数
      net.kMin = 4;                 // 最小度
      net.seed = seed;
      net.argv = "--initseed0 --cal_deg power_arr";
      net.run();
      net.save();
    }
  }

  SHOW_TIME(cout); // 显示系统时间
  return 0;
}

//**//**************************************************//**//*
#endif
