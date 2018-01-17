// g++ -o main.exe *.cpp -O3 -Wall
#include "main.h"
#ifdef MAIN_STAT_BETWEENNESS

#include "common.h"
#include "networks.h"
using namespace std;
//**//****************************************************//*
int main(int argc, char** argv)
{
  SHOW_TIME(cout); // 显示系统时间

  do {
    Networks net;
    //net.readName = "data/example/1";
    net.readName = "data/example/adDSN";
    net.saveName = net.readName;
    net.seed = 1;
    net.argv = "--initseed0 --cal_p2p read_link --stat --print --save0";

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

  SHOW_TIME(cout); // 显示系统时间
  return 0;
}
//**//****************************************************//*
#endif
