#include "main.h"
#ifdef MAIN_NET_EXTREMUM

#include "common.h"
#include "networks.h"
using namespace std;

//**//**************************************************//**//*
int main_net_extremum(int argc, char** argv)
{
  // e: max 60
  // 56:25  57:28   58:42   59:48     60:75
  for (int e = 12; e <= 60; ++e) {
    cout << "e\t" << e << endl;
    string data_dir = string("/media/yao/YAO2/net/")
        + "data/extremum/nature/2.5/data/2^" + to_string(e) + "/";
    // string data_dir
    //= string("data/extremum/nature/2.5/data/2^") + to_string(e) + "/";
    ::common_mkdir(data_dir.c_str());
    for (int seed = 1; seed <= 100; ++seed) {
      SHOW_TIME(cout); // 显示系统时间
      cout << "e\t" << e << "\nseed\t" << seed << endl;
      Networks net;
      net.saveName = net.readName = data_dir + to_string(seed);
      net.nodeSize = (NodeType)1 << e; // 节点数
      net.degree.power_gamma = 2.5;    // 度分布幂律分布的幂指数
      net.kMin = 4;                    // 最小度
      // net.argv = "--init_seed0"
      // " --cal_deg power_arr"
      // " --cal_p2p Max_lkk"
      // " --stat"
      // " --print";
      net.argv = " --init_seed0"
                 " --cal_deg power_arr"
                 " --cal_p2p Min_lkk3"
                 " --print";
      net.seed = seed;

      // 带参数运行
      if (argc > 1 && 0 != net.read_params(argc - 1, argv + 1).runStatus) {
        ERROR("net.read_params(argc, argv)");
        break;
      }

      // if (0
      //!= net_degree::power_nature_cutoff(net.kMax, net.nodeSize, net.kMin,
      // net.degree.power_gamma)) { // 最大度
      // ERROR();
      // break;
      //}
      _ERR(net_degree::read_prob_sum((data_dir + "prob_sum.txt").c_str(),
          net.degProbSumVal, net.degProbSumArr));
      net.kMax = net.degProbSumVal.back() - 1;

      //功能模块
      if (0 != net.run().runStatus) {
        ERROR("net.run");
        // cerr << net << endl;
        net.saveName += "_error";
        net.save();
        // break;
      } else {
        net.save_deg(net.saveName.c_str());
        net.save_params((net.saveName + ".Min").c_str());
        ::common_save1(
            (net.saveName + ".Min.lkk3.txt").c_str(), net.lkk3, '\n');
      }
    }
  }

  return 0;
}
//**//**************************************************//**//*
#endif
