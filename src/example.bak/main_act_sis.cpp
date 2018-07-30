// g++ -o main.exe *.cpp -O3 -Wall
#include "net.h"
#ifdef ACT_SIS

#include "common.h"
#include "networks.h"
using namespace std;
//**//****************************************************//*
int main(int argc, char **argv) {
  SHOW_TIME(cout);  // 显示系统时间

  do {
    Networks net, net2;
    net.saveName = net.readName = "data/sis";
    net.dirFlag = 0;
    net.nodeSize = 10000;
    net.kMin = 3;
    net.degree.power_gamma = 2;
    net.sis.M = 70;
    net.sis.rho = 0.1;
    net.sis.p = 0.01;
    net.sis.lambda = 0.01;
    net.sis.tau = 100;
    net.sis.t_av = 10;
    net.seed = 1;
    net.argv = "init_seed0 cal_deg power cal_p2p Random stat print save0";
    if (0 != cal_kMax_PowerLaw_NatureCutoff(net.kMax, net.nodeSize, net.kMin,
                                            net.degree.power_gamma)) {
      ERROR();
      break;
    }

    // 带参数运行
    if (argc > 1 && 0 != net.read_params(argc - 1, argv + 1).runStatus) {
      ERROR("net.read_params(argc, argv)");
      break;
    }

    // 功能模块
    if (0 != net.run().runStatus || 0 != net.p2p_2_degArr().runStatus) {
      ERROR();
      break;
    }
    if (0 != net.act_sis_tau()) {
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
