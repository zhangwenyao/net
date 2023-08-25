#include "new_networks.h"
#ifdef MAIN_REWIRE_NEW_NETWORKS

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;
using namespace main_func::rewire;

// **********************************************************
int main_func::rewire::new_networks(int argc, char** argv)
{
  for (int e = kEMin; e <= kEMax; ++e) {
    string data_dir = kDataDir + "2^" + to_string(e) + "/", fn_full;
    for (int seed = kSeedMin; seed <= kSeedMax; ++seed) {
      SHOW_TIME(cout); // 显示系统时间
      Networks net;
      fn_full = data_dir + "kMin4_" + to_string(seed);
      net.readName = fn_full;
      net.read_params();
      net.readName = fn_full;
      net.saveName = fn_full + ".Random";
      net.dirFlag = 1;
      net.argv = "--init_seed0";

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
      }

      net.readName = fn_full;
      _ERR(net.run("--cal_deg read_degArr").runStatus);
      net.degArrValOut = net.degArrValIn = net.degArrVal;
      net.degArrSizeOut = net.degArrSizeIn = net.degArrSize;
      net.degArrVal.clear();
      net.degArrSize.clear();
      _ERR(degArr_2_nodeDeg(
          net.nodeDegOut, net.degArrValOut, net.degArrSizeOut));
      net.nodeDegIn = net.nodeDegOut;
      _ERR(nodeDegIO_2_nodeDeg(net.nodeDeg, net.nodeDegOut, net.nodeDegIn));
      _ERR(nodeDeg_2_degArr(
          net.nodeDeg, net.degArrVal, net.degArrSize, net.degArrSum));
      _ERR(degArr_2_linkSize(net.linkSize, net.degArrVal, net.degArrSize));
      net.kMax = net.kMin = 0;
      _ERR(net.run("--cal_p2p Random").runStatus);
      net.saveName = fn_full + ".Random";
      _ERR(net.save().runStatus);

      _ERR(0
          != rewire_rho_dir(
                 net.linkSize * kRewireRate, rho, net.p2pOut, net.link));
      net.saveName = fn_full + ".rewire_" + kRhoString;
      _ERR(net.save_p2p().runStatus);

      _ERR(net.run("--print").runStatus);
    }
  }
  return 0;
}

#endif
