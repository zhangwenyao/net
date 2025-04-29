#include "distribution.h"
#ifdef MAIN_DISTRIBUTION

#include "../../common/common.h"
#include "../../network/networks.h"
#include "../../statistics/stat.h"
using namespace std;
using namespace common;
using namespace network;

//**//**************************************************//**//*
int main_func::distribution::new_distribution(int argc, char** argv)
{
  mkdirs(kStatDir.c_str());
  for (int e = kEMin; e <= kEMax; ++e) {
    cout << "e\t" << e << endl;
    string data_dir = kDataDir + "2^" + to_string(e) + "/",
           stat_dir = kStatDir + "2^" + to_string(e) + "/";
    mkdirs(stat_dir.c_str());

    for (int seed = kSeedMin; seed <= kSeedMax; ++seed) {
      SHOW_TIME(cout); // 显示系统时间
      cout << "e\t" << e << "\nseed\t" << seed << endl;
      Networks net;
      net.seed = seed;
      net.nodeSize = (NodeType)1 << e; // 节点数
      net.degree.power_gamma = kGamma; // 度分布幂律分布的幂指数
      net.kMin = kMin;                 // 最小度
      net.readName = data_dir + "kMin" + to_string(net.kMin);
      net.saveName = net.readName;
      net.argv = "--init_seed0"
                 " --cal_deg power_arr"
                 " --save_seed"
                 " --print";

      string fn_full = net.readName + ".probSum.txt";
      _ERR(degree::read_prob_sum(
          fn_full.c_str(), net.degProbSumVal, net.degProbSumArr));
      net.kMax = net.degProbSumVal.back() - 1;

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
        net.save();
        break;
      }
    }
  }

  return EXIT_SUCCESS;
}

//**//****************************************************//*
#endif
