#include "main.h"
#ifdef MAIN_CORRELATION2

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;
using namespace main_func::correlation2;

string main_func::correlation2::name, main_func::correlation2::dirData,
    main_func::correlation2::dirStat;
// **********************************************************
int main_func::main_correlation2(int argc, char** argv)
{
  for (auto& name_i : names) {
    name = name_i;
    // name = "BA";
    dirData = dirData0;
    dirStat = dirStat0;
    mkdirs(dirData.c_str());
    mkdirs(dirStat.c_str());
    do {
      Networks net;
      net.readName = dirData + name;
      net.saveName = dirStat + name;
      net.argv = "--cal_p2p read_p2p_fix "
                 "--stat "
                 "--save "
                 "--print";
      // net.seed = 0;
      // net.nodeSize = (NodeType)1 << 17;
      // net.random.p = 10.0 / net.nodeSize; // ER
      // net.ba.M = 5; // BA
      // net.argv = "--init_seed0 "
      //"--cal_p2p BA "
      //"--stat "
      //"--save "
      //"--print";

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
        net.save_params();
      } else {
        // net.save_params();
      }
    } while (0);
  }
  return 0;
}

#endif
