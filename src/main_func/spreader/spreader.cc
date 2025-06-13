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
  return EXIT_SUCCESS;
}
#endif  // MAIN_SPREADER_DATA

#ifdef MAIN_SPREADER_CALC
int main_func::spreader::networks_calc(int argc, char** argv) {
  for (auto& dataset : kDatasetNames) {
    string data_dir = kDataDir + "/" + dataset + "/",
           stat_dir = kStatDir + "/" + dataset + "/" + kStatDir2 + "/";
    INFORM(dataset, " in ", data_dir);
    mkdirs(stat_dir.c_str());

    Networks net;
    string fn_full = data_dir + dataset;
    net.readName = fn_full;
    net.saveName = stat_dir + dataset + ".spreader";
    // net.seed = 1;
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
      // _ERR(net.p2p_2_lkk().runStatus);
      INFORM("nodeSize: ", net.nodeSize, "\tlinkSize: ", net.linkSize);
    }

    {  // spread
      double lambda_c;
      network::sir::act_sir_cal_lambdac(lambda_c, net.p2p);
      auto& sir = net.sir;
      sir.beta = lambda_c * kLambdac;
      for (int seed = kSeedMin; seed <= kSeedMax; seed++) {
        // INFORM("seed: ", seed, " [", kSeedMin, "-", kSeedMax, "], ",
        //  seed - kSeedMin, "/", kSeedMax - kSeedMin + 1, ", ", dataset,
        //  ", beta: ", kBeta, ", gamma: ", kGamma);
        INFORM("seed: ", seed, " [", kSeedMin, "-", kSeedMax, "], ",
               seed - kSeedMin, "/", kSeedMax - kSeedMin + 1);
        // cout << "seed:\t" << seed << "/" << kSeedMax - kSeedMin + 1 << "\r"
        //  << flush;
        rand_seed(seed);
        // sir::act_sir(sir.Rs, sir.beta, sir.gamma, net.p2p, net.nodeSize);
        // network::sir::act_sir_cal_modularity(net.p2p, sir.modularity_nums,
        //  sir.modularity_nums2, nodeSize);
        network::sir::act_sir_lambda(sir.Rs, sir.beta, net.p2p, net.nodeSize);
        // net.sir.save_data((net.saveName + ".sir").c_str());
        if (save1(
                (net.saveName + ".R_nums_" + to_string(seed) + ".txt").c_str(),
                sir.Rs, net.priChar) != 0)
          return EXIT_FAILURE;
      }
      INFORM(dataset, " DONE!\tkSeedMin: ", kSeedMin, "\tkSeedMax: ", kSeedMax);
    }
  }  // end for dataset
  return EXIT_SUCCESS;
}
#endif  // MAIN_SPREADER_CALC

#ifdef MAIN_SPREADER_STAT
int main_func::spreader::networks_stat(int argc, char** argv) {
  for (auto& dataset : kDatasetNames) {
    string data_dir = kDataDir + "/" + dataset + "/",
           stat_dir = kStatDir + "/" + dataset + "/" + kStatDir2 + "/";
    INFORM(dataset, " in ", data_dir);
    mkdirs(stat_dir.c_str());

    Networks net;
    string fn_full = data_dir + dataset;
    // net.readName = fn_full + ".spreader";
    net.readName = fn_full;
    net.read_params();
    net.readName = fn_full + ".spreader";
    net.saveName = stat_dir + dataset + ".spreader";

    {  // stat spreader
      auto& sir = net.sir;
      VDouble Rmean(net.nodeSize, 0), Rstd(net.nodeSize, 0);
      VLinkType Rsum(net.nodeSize, 0), Rsum2(net.nodeSize, 0);
      sir.Rs.resize(net.nodeSize);
      int ns = 0;
      for (int seed = kSeedMin; seed <= kSeedMax; seed++) {
        if (read1(
                (net.saveName + ".R_nums_" + to_string(seed) + ".txt").c_str(),
                sir.Rs, false) != 0)
          // return EXIT_FAILURE;
          continue;
        for (NodeType i = 0; i < net.nodeSize; i++) {
          Rsum[i] += sir.Rs[i];
          Rsum2[i] += (LinkType)sir.Rs[i] * sir.Rs[i];
        }
        ns++;
      }
      INFORM("samples: ", ns);
      if (ns <= 0) continue;

      // INFORM("kSeedMin: ", kSeedMin, "\tkSeedMax: ", kSeedMax);
      // double nseed = kSeedMax - kSeedMin + 1;
      double nsr = 1.0 / ns;
      for (NodeType i = 0; i < net.nodeSize; i++) {
        Rmean[i] = (double)Rsum[i] * nsr;
        Rstd[i] = sqrt((double)Rsum2[i] * nsr - Rmean[i] * Rmean[i]);
      }
      _ERR(save1((net.readName + "." + kStatDir2 + ".R_mean.txt").c_str(),
                 Rmean, net.priChar));
      _ERR(save1((net.readName + "." + kStatDir2 + ".R_std.txt").c_str(), Rstd,
                 net.priChar));
    }
  }
  return EXIT_SUCCESS;
}
#endif  // MAIN_SPREADER_STAT

//**//****************************************************//*
#endif