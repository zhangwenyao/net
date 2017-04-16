#include "net.h"
#ifdef NET_FOODWEB

#include "common.h"
#include "networks.h"
#include "NetFoodweb.h"
using namespace std;
//**//****************************************************//*
int main(int argc, char **argv) {
  SHOW_TIME(cout);  // 显示系统时间

  // do {
  // Networks net;
  // net.readName = "database/foodWeb/Grassland/Grassland";
  // net.saveName = net.readName + "_n0";
  // net.dirFlag = 1;
  // net.argv = "cal_p2p read_link stat save0 print";
  // if (0 != net.run().runStatus) {
  // ERROR("net.run");
  // break;
  //}
  //} while (0);

  do {
    Networks net;
    net.readName = "database/foodWeb/Grassland/Grassland";
    net.saveName = net.readName + "_n1";
    net.dirFlag = 1;
    net.seed = 1;
    net.argv = "init_seed0 cal_p2p p2p stat save0 print";

    // 带参数运行
    if (argc > 1 && 0 != net.read_params(argc - 1, argv + 1).runStatus) {
      ERROR("net.read_params(argc, argv)");
      break;
    }

    // 读取link -> p2p
    if (0 !=
        data_read_foodweb1(net.link, (net.readName + "_link.txt").c_str())) {
      ERROR();
      break;
    }

    // 功能模块
    if (0 != net.run().runStatus) {
      ERROR("net.run");
      cerr << net << endl;
      break;
    }
  } while (0);

  SHOW_TIME(cout);  // 显示系统时间
  return 0;
}

//**//****************************************************//*
#endif
