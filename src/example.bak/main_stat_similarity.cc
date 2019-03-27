// g++ -o main.exe *.cpp -O3 -Wall
#include "net.h"
#ifdef STAT_SIMILARITY

#include "common.h"
#include "networks.h"
using namespace std;
//**//****************************************************//*
int main(int argc, char **argv) {
  SHOW_TIME(cout);  // 显示系统时间

  do {
    Networks net, net2;
    net.saveName = net.readName = "data/matrix2";
    net2.saveName = net2.readName = "data/matrix3";
    net.dirFlag = net2.dirFlag = 1;
    // net.seed = RAND2_INIT(1);    // 初始化随机数种子
    // while(0 == (net.seed = RAND2_INIT(net.seed)))
    //   continue;    // 初始化随机数种子
    if (0 != net.read_linkMatr("data/example/2.linkMatr.txt").runStatus ||
        0 != linkMatr_2_p2p(net.p2p, net.linkMatr) ||
        0 != net.p2p_2_degArr().runStatus) {
      ERROR();
      break;
    }
    if (0 != net2.read_linkMatr("data/example/3.linkMatr.txt").runStatus ||
        0 != linkMatr_2_p2p(net2.p2p, net2.linkMatr) ||
        0 != net2.p2p_2_degArr().runStatus) {
      ERROR();
      break;
    }
    if (0 != net.stat_similarity(net2).runStatus) {
      ERROR();
      break;
    }
    if (0 != net.save().runStatus) {
      ERROR();
      break;
    }
  } while (0);

  SHOW_TIME(cout);  // 显示系统时间
  return 0;
}
//**//****************************************************//*
#endif
