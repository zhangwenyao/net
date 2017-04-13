#include <algorithm>
#include <fstream>
#include <iostream>
#include "common.h"
#include "networks.h"
#ifdef NET_FOODWEB

using namespace std;
//**//************************** code example *****************************//*
int main(int argc, char **argv) {
  do {
    Network net;
    net.readName = "database/foodWeb/Grassland/Grassland";
    net.saveName = net.readName + "_n0";
    net.dirFlag = 1;
    net.argv = "cal_p2p read_link stat save0 print";
    if (0 != net_run(net) || net.status < 0) {
      ERROR("net_new");
      break;
    }
  } while (0);
  do {
    Network net;
    net.readName = "database/foodWeb/Grassland/Grassland";
    net.saveName = net.readName + "_n1";
    net.dirFlag = 1;
    net.argv = "cal_p2p p2p stat save0 print";

    // net.argv = "init_seed0 cal_p2p p2p stat save print";
    // 带参数运行
    if (argc > 1 && 0 != net_read_params(net, argc - 1, argv + 1)) {
      ERROR("net_read(argc, argv)");
      break;
    }

    // 读取link -> p2p
    if (0 !=
        data_read_foodweb1(net.link, (net.readName + "_link.txt").c_str())) {
      ERROR();
      break;
    }

    // 功能模块
    if (0 != net_run(net) || net.status < 0) {
      ERROR("net_new");
      break;
    }
  } while (0);
  return 0;
}

//**//********************************************************************
#endif
