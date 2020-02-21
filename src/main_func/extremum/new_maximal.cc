#include "new_maximal.h"
#ifdef MAIN_EXTREMUM_NEW_MAXIMAL

#include "../../common/common.h"
#include "../../model/extremum/extremum.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;
using namespace network::extremum;

//**//**************************************************//**//*
int main_func::extremum::new_maximal(int argc, char** argv)
{
  for (int e = kEMin; e <= kEMax; ++e) {
    string data_dir = kDataDir + "2^" + to_string(e) + "/", fn_full;

    for (int seed = kSeedMin; seed <= kSeedMax; ++seed) {
      SHOW_TIME(cout); // 显示系统时间
      cout << "e\t" << e << "\nseed\t" << seed << endl;
      Networks net;
      fn_full = data_dir + "kMin4_" + to_string(seed);
      net.readName = fn_full;
      net.read_params();
      net.readName = fn_full;
      net.saveName = fn_full + ".Max";
      net.lkk_type = lkk2_lkk2;
      net.argv = "--init_seed0"
                 " --cal_deg read_degArr"
                 " --cal_p2p Max_lkk2"
                 " --print";

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
        net.save_params();
        net.save_lkk();
      }
    }
  }

  return 0;
}
//**//**************************************************//**//*
#endif
