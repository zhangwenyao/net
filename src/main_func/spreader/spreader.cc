#include "spreader.h"
#ifdef MAIN_SPREADER

#include "../../common/common.h"
#include "../../network/networks.h"
// #include "../../statistics/spreader/spreader.h"
// #include "../../statistics/stat.h"
using namespace std;
using namespace common;
using namespace network;

//**//**************************************************//**//*
#ifdef MAIN_SPREADER_DATA
int main_func::spreader::networks_data(int argc, char** argv) {
  for (int i = 0; i < DATASET_SIZE; i++) {
    string dataset = DATASET_NAMES[i];
    string data_dir = kDataDir + dataset + "/";
    string link_name = data_dir + dataset + ".linkname.txt",
           name_file = data_dir + dataset + ".name.txt",
           link_file0 = data_dir + dataset + ".link0.txt",
           link_file = data_dir + dataset + ".link.txt";
    INFORM(dataset, ": ", link_file0);
    linkname_2_link<NodeType>(link_name.c_str(), name_file.c_str(),
                              link_file0.c_str(), link_file.c_str());
  }
  return EXIT_SUCCESS;
}
#endif  // MAIN_SPREADER_DATA

#ifdef MAIN_SPREADER_CALC
int main_func::spreader::networks_calc(int argc, char** argv) {
  for (int i = 0; i < DATASET_SIZE; i++) {
    string dataset = DATASET_NAMES[i];
    string data_dir = kDataDir + dataset + "/", stat_dir = data_dir;
    INFORM(dataset, " in ", data_dir);
    mkdirs(stat_dir.c_str());

    Networks net;
    string fn_full = data_dir + dataset;
    net.readName = fn_full;
    net.saveName = fn_full + ".spreader";
    net.seed = 1;
    net.dirFlag = 0;
    net.argv =
        " --cal_p2p read_link"
        " --stat"
        " --save";
    // 带参数运行
    if (argc > 1 && 0 != net.read_params(argc - 1, argv + 1).runStatus) {
      ERROR("net.read_params(argc, argv)");
      break;
    }

    // 功能模块
    // if (0 != net.run().runStatus) {
    //   ERROR("net.run");
    //   cerr << net << endl;
    //   net.saveName += "_error";
    //   net.save_params();
    // }

    {  // read links
      _ERR(read_link(net.link, (fn_full + ".link.txt").c_str()));
      net.linkSize = net.link.size() / 2;
      link_2_nodeSize(net.nodeSize, net.link);

      _ERR(link_2_p2p(net.p2p, net.link, net.nodeSize));
      _ERR(net.p2p_2_degArr().runStatus);
      net.kMin = net.degArrVal.front();
      net.kMax = net.degArrVal.back();
      net.status = 1;
      auto& sir = net.sir;
      sir.beta = 0.2;
      sir.gamma = 1.0;
      // _ERR(net.p2p_2_lkk().runStatus);
      INFORM("nodeSize: ", net.nodeSize, "\tlinkSize: ", net.linkSize);
    }

    {  // calc spreader
      // net.act_sir();
      auto& sir = net.sir;
      network::sir::act_sir_cal_modularity(net.p2p, sir.modularity_nums,
                                           sir.modularity_nums2, net.nodeSize);
      // sir::act_sir(sir.Rs, sir.beta, sir.gamma, net.p2p, net.nodeSize);
      // net.sir.save_data((net.saveName + ".sir").c_str());
      if (save1((net.saveName + ".modularity.txt").c_str(), sir.modularity_nums,
                net.priChar) != 0)
        return EXIT_FAILURE;
      if (save1((net.saveName + ".modularity2.txt").c_str(),
                sir.modularity_nums2, net.priChar) != 0)
        return EXIT_FAILURE;
    }
    _ERR(net.save_params().runStatus);

    for (int seed = kSeedMin; seed <= kSeedMax; seed++) {
      INFORM("seed: ", seed);
      rand_seed(seed);
      auto& sir = net.sir;
      // sir::act_sir(sir.Rs, sir.beta, sir.gamma, net.p2p, net.nodeSize);
      // network::sir::act_sir_cal_modularity(net.p2p, sir.modularity_nums,
      //  sir.modularity_nums2, nodeSize);
      network::sir::act_sir(sir.Rs, sir.beta, sir.gamma, net.p2p, net.nodeSize);
      // net.sir.save_data((net.saveName + ".sir").c_str());
      if (save1((net.saveName + ".R_nums_" + to_string(seed) + ".txt").c_str(),
                sir.Rs, net.priChar) != 0)
        return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
#endif  // MAIN_SPREADER_CALC

#ifdef MAIN_SPREADER_STAT
int main_func::spreader::networks_stat(int argc, char** argv) {
  for (int i = 0; i < DATASET_SIZE; i++) {
    string dataset = DATASET_NAMES[i];
    string data_dir = kDataDir + dataset + "/", stat_dir = data_dir;
    INFORM(dataset, " in ", data_dir);
    mkdirs(stat_dir.c_str());

    Networks net;
    string fn_full = data_dir + dataset;
    net.readName = fn_full + ".spreader";
    net.saveName = net.readName;
    net.read_params();

    {  // stat spreader
      auto& sir = net.sir;
      VDouble Rmean(net.nodeSize, 0), Rstd(net.nodeSize, 0);
      VLinkType Rsum(net.nodeSize, 0), Rsum2(net.nodeSize, 0);
      sir.Rs.resize(net.nodeSize);
      for (int seed = kSeedMin; seed <= kSeedMax; seed++) {
        if (read1(
                (net.saveName + ".R_nums_" + to_string(seed) + ".txt").c_str(),
                sir.Rs) != 0)
          return EXIT_FAILURE;
        for (NodeType i = 0; i < net.nodeSize; i++) {
          Rsum[i] += sir.Rs[i];
          Rsum2[i] += (LinkType)sir.Rs[i] * sir.Rs[i];
        }
      }
      double nseed = kSeedMax - kSeedMin + 1;
      for (NodeType i = 0; i < net.nodeSize; i++) {
        Rmean[i] = (double)Rsum[i] / nseed;
        Rstd[i] = sqrt((double)Rsum2[i] / nseed - Rmean[i] * Rmean[i]);
      }
      if (save1((net.saveName + ".R_mean.txt").c_str(), Rmean, net.priChar) !=
          0)
        return EXIT_FAILURE;
      if (save1((net.saveName + ".R_std.txt").c_str(), Rstd, net.priChar) != 0)
        return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
#endif  // MAIN_SPREADER_STAT

//**//****************************************************//*
#endif