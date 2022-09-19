#include "spearman.h"
#ifdef MAIN_SPEARMAN

#include "../../common/common.h"
#include "../../network/networks.h"
#include "../../statistics/spearman/spearman.h"
#include "../../statistics/stat.h"
using namespace std;
using namespace common;
using namespace network;

//**//**************************************************//**//*
#ifdef MAIN_SPEARMAN_RANDOM
int main_func::spearman::networks_random(int argc, char** argv)
{
  for (int e = kEMin; e <= kEMax; ++e) {
    string data_dir = kDataDir + "2^" + to_string(e) + "/", fn_full;
    SHOW_TIME(cout); // 显示系统时间
    Networks net;
    fn_full = data_dir + "kMin" + to_string(kMin);
    net.readName = fn_full + ".Random";
    net.saveName = net.readName;
    net.degree.power_gamma = kGamma; // 度分布幂律分布的幂指数
    net.nodeSize = (NodeType)1 << e; // 节点数
    net.kMin = kMin;
    net.seed = kSeed0;
    net.dirFlag = 0;
    net.lkk_type = lkk_lkk;
    net.argv = "--init_seed0"
               " --cal_deg power_arr";

    // 带参数运行
    if (argc > 1 && 0 != net.read_params(argc - 1, argv + 1).runStatus) {
      ERROR("net.read_params(argc, argv)");
      break;
    }

    _ERR(degree::read_prob_sum((fn_full + ".probSum.txt").c_str(),
        net.degProbSumVal, net.degProbSumArr));
    net.kMax = net.degProbSumVal.back() - 1;

    //功能模块
    if (0 != net.run().runStatus) {
      ERROR("net.run");
      cerr << net << endl;
      net.saveName += "_error";
      net.save_params();
    }

    _ERR(degArr_2_nodeDeg(net.nodeDeg, net.degArrVal, net.degArrSize));
    _ERR(net.run("--cal_p2p Random").runStatus);
    _ERR(0 != net.stat().runStatus);
    _ERR(net.save().runStatus);
  }
  return EXIT_SUCCESS;
}
#endif

#ifdef MAIN_SPEARMAN_GAUSS
int main_func::spearman::networks_gauss(int argc, char** argv)
{
  for (int e = kEMin; e <= kEMax; ++e) {
    string data_dir = kDataDir + "2^" + to_string(e) + "/", fn_full;
    SHOW_TIME(cout); // 显示系统时间
    Networks net;
    fn_full = data_dir + "kMin" + to_string(kMin);
    net.readName = fn_full + ".Random";
    net.saveName = fn_full + ".gauss";
    net.degree.power_gamma = kGamma; // 度分布幂律分布的幂指数
    net.nodeSize = (NodeType)1 << e; // 节点数
    net.kMin = kMin;
    net.seed = kSeed0;
    net.dirFlag = 0;
    net.lkk_type = lkk_lkk;
    net.argv = "--init_seed0"
               //" --cal_deg read_degArr"
               " --cal_p2p read_p2p";

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

    _ERR(0 != net.stat().runStatus);

    // net.lkk.clear();
    // net.nodeDeg.clear();
    _ERR(net.save_params().runStatus);

    net.link.clear();
    net.p2p.clear();
    net.lkk.clear();
    for (size_t i = 0; i < 1; ++i) {
      // for (size_t i = 1; i < rho_len; ++i) {
      // const double rho = kRhos[i];
      double sr = kSpearmanRs[i];
      cout << '\t' << kRhoStrings[i] << '\t' << sr << endl;
      net.saveName = fn_full + +".gauss_" + kRhoStrings[i];

      net.spearman.r0 = kSpearmanRs[i];
      net.spearman_cal_lkkProb_gauss();
      net.spearman_gauss_new_ranLink();

      _ERR(p2p_2_lkk(net.lkk, net.p2p, net.degArrNo, net.degArrVal.size()));
      _ERR(0 != net.stat().runStatus);
      _ERR(0 != net.save().runStatus);
      //_ERR(0 != net.save_params().runStatus);
      //_ERR(0 != net.save_p2p().runStatus);
      //_ERR(0 != net.save_lkk().runStatus);
    }
  }
  return EXIT_SUCCESS;
}
#endif

#ifdef MAIN_SPEARMAN_R_RANDOM
int main_func::spearman::networks_r_random(int argc, char** argv)
{
  string data_dir = kDataDir + "data/", fn_full;
  SHOW_TIME(cout); // 显示系统时间
  Networks net;
  fn_full = data_dir + "kMin" + to_string(kMin);
  net.readName = fn_full;
  net.saveName = net.readName + ".Random";
  net.degree.power_gamma = kGamma; // 度分布幂律分布的幂指数
  net.dirFlag = 0;
  net.lkk_type = lkk_lkk;
  _ERR(net.run("--cal_deg read_degArr").runStatus);
  _ERR(degArr_2_nodeDeg(net.nodeDeg, net.degArrVal, net.degArrSize));

  net.argv = " --init_seed0"
             " --cal_p2p Random"
             " --stat";
  for (int seed = kSeedMin; seed <= kSeedMax; ++seed) {
    net.p2p.clear();
    net.link.clear();
    net.lkk.clear();
    net.seed = seed;
    _ERR(net.run().runStatus);
    net.save_params((net.saveName + "_" + to_string(seed)).c_str());
    net.save_lkk((net.saveName + "_" + to_string(seed)).c_str());
  }
  return EXIT_SUCCESS;
}
#endif

#ifdef MAIN_SPEARMAN_R_GAUSS
int main_func::spearman::networks_r_gauss(int argc, char** argv)
{
  do {
    SHOW_TIME(cout); // 显示系统时间
    string data_dir = kDataDir + "sqrt" + "/", fn_full;
    Networks net;
    fn_full = data_dir + "kMin" + to_string(kMin);
    net.readName = fn_full;
    net.saveName = fn_full + ".gauss";
    net.degree.power_gamma = kGamma; // 度分布幂律分布的幂指数
    // net.nodeSize = (NodeType)1 << e; // 节点数
    // net.kMin = kMin;
    net.seed = kSeed0;
    net.dirFlag = 0;
    net.lkk_type = lkk_lkk;
    net.argv = "--init_seed0"
               " --cal_deg read_degArr"
               " --cal_p2p Random";

    // 带参数运行
    if (argc > 1 && 0 != net.read_params(argc - 1, argv + 1).runStatus) {
      ERROR("net.read_params(argc, argv)");
      break;
    }

    ////功能模块
    // if (0 != net.run().runStatus) {
    // ERROR("net.run");
    // cerr << net << endl;
    // net.saveName += "_error";
    // net.save_params();
    //}

    _ERR(0 != net.init_seed0(net.seed).runStatus);
    _ERR(0 != net.read_degArr().runStatus);
    _ERR(degArr_2_nodeDeg(net.nodeDeg, net.degArrVal, net.degArrSize));
    _ERR(net.run("--cal_p2p Random").runStatus);
    _ERR(0 != net.stat().runStatus);
    //_ERR(degArr_2_nodeDeg(net.nodeDeg, net.degArrVal, net.degArrSize));

    net.lkk.clear();
    net.nodeDeg.clear();
    _ERR(net.save_params().runStatus);

    net.link.clear();
    net.p2p.clear();
    net.lkk.clear();
    {
      double sr = 0.76;
      net.saveName = fn_full + +".gauss_0.76";

      net.spearman.r0 = sr;
      net.spearman_cal_lkkProb_gauss();
      net.spearman_gauss_new_ranLink();

      _ERR(p2p_2_lkk(net.lkk, net.p2p, net.degArrNo, net.degArrVal.size()));
      _ERR(0 != net.stat().runStatus);
      _ERR(0 != net.save().runStatus);
      lkk_nDir_2_dir(net.lkk);
      _ERR(common::save2((net.saveName + ".lkkDir.txt").c_str(), net.lkk));
    }
  } while (0);
  return EXIT_SUCCESS;
}
#endif

#ifdef MAIN_SPEARMAN_R_STAT
int main_func::spearman::networks_r_stat(int argc, char** argv)
{
  string data_dir = kDataDir + "data/", stat_dir = kStatDir;
  SHOW_TIME(cout); // 显示系统时间
  mkdirs(stat_dir.c_str());

  const string save_prename = stat_dir + "kMin" + to_string(kMin) + ".Random",
               sufname = ".params.txt";
#ifdef STAT_PEARSON
  {
    cout << "statistics pearson" << endl;
    string save_fullname = save_prename + ".pearson.txt";
    ofstream os(save_fullname.c_str());
    if (!os) {
      ERROR();
    } else {
      double sx = 0, sxx = 0, x_mean = 0, x_sigma = 0;
      size_t n = 0;
      string prename = data_dir + "kMin" + to_string(kMin) + ".Random_",
             coefficient_string = "--pearson.pearson";
      statistics::sum(prename.c_str(), sufname.c_str(), kSeedMin, kSeedMax,
          coefficient_string.c_str(), sx, sxx, n);
      if (n > 0) {
        x_mean = sx / n;
        x_sigma = sxx / n - x_mean * x_mean;
        x_sigma = x_sigma > 0 ? sqrt(x_sigma) : 0;
        os << n << "\t" << x_mean << "\t" << x_sigma << endl;
      }
    }
    os.close();
  }
#endif

#ifdef STAT_SPEARMAN
  {
    cout << "statistics spearman" << endl;
    string save_fullname = save_prename + ".spearman.txt";
    ofstream os(save_fullname.c_str());
    if (!os) {
      ERROR();
    } else {
      double sx = 0, sxx = 0, x_mean = 0, x_sigma = 0;
      size_t n = 0;
      string prename = data_dir + "kMin" + to_string(kMin) + ".Random_",
             coefficient_string = "--spearman.spearman";
      statistics::sum(prename.c_str(), sufname.c_str(), kSeedMin, kSeedMax,
          coefficient_string.c_str(), sx, sxx, n);
      if (n > 0) {
        x_mean = sx / n;
        x_sigma = sxx / n - x_mean * x_mean;
        x_sigma = x_sigma > 0 ? sqrt(x_sigma) : 0;
        os << n << "\t" << x_mean << "\t" << x_sigma << endl;
      }
    }
    os.close();
  }
#endif

  {
    cout << "lkk mean" << endl;
    string spn = save_prename + ".lkk";
    string prename = data_dir + "kMin" + to_string(kMin) + ".Random_",
           sufname = ".lkk.txt";
    _ERR(statistics::mean2<double>(
        prename.c_str(), sufname.c_str(), kSeedMin, kSeedMax, spn.c_str()));
  }

  return EXIT_SUCCESS;
}
#endif

#ifdef MAIN_SPEARMAN_TEST
int main_func::spearman::networks_test(int argc, char** argv)
{
  for (int e = kEMin; e <= kEMax; ++e) {
    string data_dir = kDataDir + "2^" + to_string(e) + "/", fn_full;
    SHOW_TIME(cout); // 显示系统时间
    Networks net;
    fn_full = data_dir + "kMin" + to_string(kMin);
    net.readName = fn_full + ".Random";
    net.saveName = fn_full + ".gauss";
    net.degree.power_gamma = kGamma; // 度分布幂律分布的幂指数
    net.nodeSize = (NodeType)1 << e; // 节点数
    net.kMin = kMin;
    net.seed = kSeed0;
    net.dirFlag = 0;
    net.lkk_type = lkk_lkk;
    // net.argv = "--init_seed0"
    //" --cal_deg read_degArr"
    //" --cal_p2p read_p2p";

    // 带参数运行
    if (argc > 1 && 0 != net.read_params(argc - 1, argv + 1).runStatus) {
      ERROR("net.read_params(argc, argv)");
      break;
    }

    //功能模块
    // if (0 != net.run().runStatus) {
    // ERROR("net.run");
    // cerr << net << endl;
    // net.saveName += "_error";
    // net.save_params();
    //}

    for (size_t i = 1; i < rho_len; ++i) {
      double sr = kSpearmanRs[i];
      cout << '\t' << kRhoStrings[i] << '\t' << sr << endl;
      net.saveName = fn_full + +".gauss_" + kRhoStrings[i];
      net.lkk.clear();
      _ERR(common::read2_0((net.saveName + ".lkk.txt").c_str(), net.lkk));
      lkk_nDir_2_dir(net.lkk);
      _ERR(common::save2((net.saveName + ".lkkDir.txt").c_str(), net.lkk));
    }
  }
  return EXIT_SUCCESS;
}
#endif

//**//****************************************************//*
#endif
