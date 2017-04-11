// g++ -o main.exe *.cpp -O3 -Wall
#include "common.h"
#include "networks.h"
#ifdef STAT_SIMILARITY

using namespace std;
//**//****************************************************//*
int main(int argc, char **argv) {
  SHOW_TIME(cout);  // 显示系统时间

  do {
    Network net, net2;
    net.saveName = net.readName = "data/matrix1";
    net2.saveName = net2.readName = "data/matrix2";
    net.dirFlag = net2.dirFlag = 1;
    // while(0 == (net.seed = RAND2_INIT(net.seed)));    // 初始化随机数种子
    // net.seed = RAND2_INIT(1);    // 初始化随机数种子
    if (0 != net_read_linkMatr_0(net, "data/example/linkMatr1.txt") ||
        0 != linkMatr_2_p2p(net.p2p, net.linkMatr) ||
        0 != net_p2p_2_degArr(net)) {
      ERROR();
      break;
    }
    if (0 != net_read_linkMatr_0(net2, "data/example/linkMatr2.txt") ||
        0 != linkMatr_2_p2p(net2.p2p, net2.linkMatr) ||
        0 != net_p2p_2_degArr(net2)) {
      ERROR();
      break;
    }
    if (0 != net_similarity(net, net2)) {
      ERROR();
      break;
    }
    if (0 != net_save(net)) {
      ERROR();
      break;
    }
  } while (0);

  SHOW_TIME(cout);  // 显示系统时间
  return 0;
}
#endif
