// g++ -o main.exe *.cpp -O3 -Wall
#include "common.h"
#include "networks.h"
#ifdef ACT_SIS

using namespace std;
//**//****************************************************//*
int main(int argc, char **argv) {
  SHOW_TIME(cout);  // 显示系统时间

  do {
    Networks net, net2;
    net.saveName = net.readName = "data/random-power2";
    net.dirFlag = 0;
    net.nodeSize = 100000;
    net.degree.power_gamma = 2;
    net.kMin = 3;
    if (0 != cal_kmax_PowerLaw_NatureCutoff(net.kMax, net.nodeSize, net.kMin,
                                            net.degree.power_gamma)) {
      ERROR();
      return -1;
    }

    net.sis.M = 70;
    net.sis.rho = 0.1;
    net.sis.p = 0.01;
    net.sis.lambda = 0.01;
    net.sis.tau = 100;
    net.sis.t_av = 10;

    // while(0 == (net.seed = RAND2_INIT(net.seed)));    // 初始化随机数种子
    net.seed = RAND2_INIT(1);  // 初始化随机数种子
    if (0 != net.run("cal_deg power cal_p2p random stat").runStatus ||
        0 != net.p2p_2_degArr().runStatus) {
      ERROR();
      break;
    }
    if (0 != net.cal_SIS_tau()) {
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
