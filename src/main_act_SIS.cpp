// g++ -o main.exe *.cpp -O3 -Wall
#include "common.h"
#include "networks.h"
#ifdef ACT_SIS

using namespace std;
//**//****************************************************//*
int main(int argc, char **argv) {
  SHOW_TIME(cout);  // 显示系统时间

  do {
    Network net, net2;
    net.saveName = net.readName = "data/random-power2";
    net.dirFlag = 0;
    net.nodeSize = 100000;
    net.params_degree.power_gamma = 2;
    net.kMin = 3;
    if (0 != cal_kmax_PowerLaw_NatureCutoff(net.kMax, net.nodeSize, net.kMin,
                                            net.params_degree.power_gamma)) {
      ERROR();
      return -1;
    }

    net.params_SIS.M = 70;
    net.params_SIS.rho = 0.1;
    net.params_SIS.p = 0.01;
    net.params_SIS.lambda = 0.01;
    net.params_SIS.tau = 10000;
    net.params_SIS.t_av = 100;

    // while(0 == (net.seed = RAND2_INIT(net.seed)));    // 初始化随机数种子
    net.seed = RAND2_INIT(1);  // 初始化随机数种子
    if (0 != net_run(net, "cal_deg power cal_p2p random stat") ||
        0 != net_p2p_2_degArr(net)) {
      ERROR();
      break;
    }
    if (0 != net_act_SIS_tau(net)) {
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
//**//****************************************************//*
#endif
