#include "rewire.h"
#ifdef MAIN_REWIRE

#include "../../common/common.h"
#include "../../dynamics/correlation/correlation.h"
#include "../../network/networks.h"
#include "../../statistics/stat.h"
using namespace std;
using namespace common;
using namespace network;

// **********************************************************
int main_func::rewire::distribution(int argc, char** argv)
{
  for (int e = kEMin; e <= kEMax; ++e) {
    string data_dir = kDataDir + "dis/2^" + to_string(e) + "/", fn_full;
    mkdirs(data_dir.c_str());
    const NodeType N = 1 << e;
    for (int seed = kSeedMin; seed <= kSeedMax; ++seed) {
      fn_full = data_dir + to_string(seed) + ".rewire";
      VNodeType v;
      v.resize(N);
      for (size_t i = 0; i < N; ++i)
        v[i] = i;
      network::correlation::rewire(v, N * kRewireRate, rho);
      string name = fn_full + ".v.txt";
      save1(name.c_str(), v, '\n');
    } // seed
  }   // e
  return EXIT_SUCCESS;
}

int main_func::rewire::distribution_stat(int argc, char** argv)
{
  for (int e = kEMin; e <= kEMax; ++e) {
    string data_dir = kDataDir + "dis/2^" + to_string(e) + "/",
           stat_dir = kStatDir + "2^" + to_string(e) + "/stat/", fn_full;
    mkdirs(data_dir.c_str());
    mkdirs(stat_dir.c_str());
    const NodeType N = 1 << e;
    // const size_t kN_size = sizeof(kNs) / sizeof(kNs[0]);
    const size_t kN_size = N;
    NodeType ns[kN_size];
    VLinkType counts[kN_size];
    for (size_t ni = 0; ni < kN_size; ++ni) {
      // ns[ni] = kNs[ni] * N + 0.5;
      ns[ni] = ni;
      counts[ni].assign(N, 0);
    }
    for (int seed = kSeedMin; seed <= kSeedMax; ++seed) {
      fn_full = data_dir + to_string(seed) + ".rewire.v.txt";
      VNodeType v;
      v.resize(N);
      read1(fn_full.c_str(), v);
      for (size_t ni = 0; ni < kN_size; ++ni) {
        ++counts[ni][v[ns[ni]]];
      }
    } // seed
    for (size_t ni = 0; ni < kN_size; ++ni) {
      save1((stat_dir + to_string(ns[ni]) + ".dis.txt").c_str(), counts[ni],
          '\n');
    }
  } // e
  return EXIT_SUCCESS;
}

int main_func::rewire::distribution_stat_all(int argc, char** argv)
{
  for (int e = kEMin; e <= kEMax; ++e) {
    string data_dir = kDataDir + "dis/2^" + to_string(e) + "/",
           stat_dir = kStatDir + "2^" + to_string(e) + "/", fn_full;
    mkdirs(data_dir.c_str());
    mkdirs((stat_dir + "stat/").c_str());
    const NodeType N = 1 << e;
    for (int seed = kSeedMin; seed <= kSeedMax; ++seed) {
      VNodeType v;
      v.resize(N);
      fn_full = data_dir + to_string(seed) + ".rewire.v.txt";
      read1(fn_full.c_str(), v);
      double pearson = 0;
      _ERR(0 != network::correlation::pearson(v, pearson));
      fn_full = stat_dir + "stat/" + to_string(seed) + ".params.txt";
      ofstream os(fn_full.c_str());
      os << "--pearson\t" << pearson << "\n";
      os.close();
    } // seed
    {
      string save_fullname = stat_dir + "pearson.txt";
      ofstream os(save_fullname.c_str());
      double sx = 0, sxx = 0, x_mean = 0, x_sigma = 0;
      size_t n = 0;
      string prename = stat_dir + "stat/", sufname = ".params.txt",
             coefficient_string = "--pearson";
      network::statistics::sum(prename.c_str(), sufname.c_str(), kSeedMin,
          kSeedMax, coefficient_string.c_str(), sx, sxx, n);
      if (n > 0) {
        x_mean = sx / n;
        x_sigma = sxx / n - x_mean * x_mean;
        x_sigma = x_sigma > 0 ? sqrt(x_sigma) : 0;
        os << e << "\t" << n << "\t" << x_mean << "\t" << x_sigma << endl;
      }
      os.close();
    }
  } // e
  return EXIT_SUCCESS;
}

int main_func::rewire::networks_random_dir(int argc, char** argv)
{
  for (int e = kEMin; e <= kEMax; ++e) {
    string data_dir = kDataDir + "2^" + to_string(e) + "/", fn_full;
    for (int seed = kSeedMin; seed <= kSeedMax; ++seed) {
      SHOW_TIME(cout); // 显示系统时间
      Networks net;
      net.dirFlag = 1;
      net.argv = "--init_seed0";
      fn_full = data_dir + "kMin" + to_string(kMin);
      net.readName = fn_full + "_" + to_string(seed);
      net.saveName = net.readName + ".Random";
      net.nodeSize = (NodeType)1 << e; // 节点数
      net.degree.power_gamma = kGamma; // 度分布幂律分布的幂指数
      net.kMin = kMin;
      net.seed = seed;
      net.dirFlag = 1;
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
      _ERR(degArr_2_linkSize(
          net.linkSize, net.degArrValOut, net.degArrSizeOut, 1));
      net.kMax = net.kMin = 0;
      _ERR(net.run("--cal_p2p Random").runStatus);
      _ERR(net.save().runStatus);

      VVNodeType p2pOut = move(net.p2pOut);
      VNodeType link = move(net.link);
      net.lkk.clear();
      _ERR(net.save().runStatus);

      constexpr size_t rs = sizeof(kRhos) / sizeof(kRhos[0]);
      for (size_t i = 0; i < rs; ++i) {
        net.p2pOut = p2pOut;
        net.link = link;
        cout << '\t' << kRhoStrings[i] << endl;
        const double rho = kRhos[i];
        net.saveName = net.readName + ".rewire_" + kRhoStrings[i];
        _ERR(0
            != rewire_rho_dir(
                net.linkSize * kRewireRate, rho, net.p2pOut, net.link));
        _ERR(0 != net.stat().runStatus);
        _ERR(0 != net.save_params().runStatus);
      }
    }
  }
  return EXIT_SUCCESS;
}

int main_func::rewire::networks_random(int argc, char** argv)
{
  for (int e = kEMin; e <= kEMax; ++e) {
    string data_dir = kDataDir + "2^" + to_string(e) + "/", fn_full;
    for (int seed = kSeedMin; seed <= kSeedMax; ++seed) {
      SHOW_TIME(cout); // 显示系统时间
      Networks net;
      fn_full = data_dir + "kMin" + to_string(kMin);
      net.readName = fn_full + "_" + to_string(seed);
      net.saveName = net.readName + ".Random";
      net.nodeSize = (NodeType)1 << e; // 节点数
      net.degree.power_gamma = kGamma; // 度分布幂律分布的幂指数
      net.kMin = kMin;
      net.seed = seed;
      net.dirFlag = 0;
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

      VVNodeType p2p = move(net.p2p);
      VNodeType link = move(net.link);
      net.lkk.clear();
      net.nodeDeg.clear();
      _ERR(net.save().runStatus);

      constexpr size_t rs = sizeof(kRhos) / sizeof(kRhos[0]);
      for (size_t i = 0; i < rs; ++i) {
        net.p2p = p2p;
        net.link = link;
        cout << '\t' << kRhoStrings[i] << endl;
        const double rho = kRhos[i];
        net.saveName = net.readName + ".rewire_" + kRhoStrings[i];
        _ERR(0
            != rewire_rho(
                net.linkSize * kRewireRate, rho, net.p2p, net.link));
        _ERR(0 != net.stat().runStatus);
        _ERR(0 != net.save_params().runStatus);
        //_ERR(net.save_p2p().runStatus);
      }
    }
  }
  return EXIT_SUCCESS;
}

// 同一个度分布，不同种子seed、交换概率rho
int main_func::rewire::networks_random1(int argc, char** argv)
{
  for (int e = kEMin; e <= kEMax; ++e) {
    SHOW_TIME(cout); // 显示系统时间
    string data_dir = kDataDir + "2^" + to_string(e) + "/", fn_full;
    Networks net;
    fn_full = data_dir + "kMin" + to_string(kMin);
    net.readName = fn_full;
    net.saveName = net.readName + ".Random";
    net.nodeSize = (NodeType)1 << e; // 节点数
    net.degree.power_gamma = kGamma; // 度分布幂律分布的幂指数
    net.kMin = kMin;
    net.seed = kSeed0;
    net.dirFlag = 0;
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
    net.lkk.clear();
    _ERR(0 != net.stat().runStatus);

    VVNodeType p2p = move(net.p2p);
    VNodeType link = move(net.link);
    _ERR(net.save().runStatus);

    constexpr size_t rs = sizeof(kRhos) / sizeof(kRhos[0]);
    for (size_t i = 0; i < rs; ++i) {
      cout << '\t' << kRhoStrings[i] << endl;
      for (int seed = kSeedMin; seed <= kSeedMax; ++seed) {
        cout << '\t' << seed << endl;
        net.init_seed0(seed);
        net.p2p = p2p;
        net.link = link;
        const double rho = kRhos[i];
        net.saveName = net.readName + "_" + to_string(seed) + ".rewire_"
            + kRhoStrings[i];
        _ERR(0
            != rewire_rho(
                net.linkSize * kRewireRate, rho, net.p2p, net.link));
        //_ERR(0 != p2p_2_lkk(net.lkk, net.p2p, net.degArrNo, net.degSize));
        _ERR(0 != net.stat().runStatus);
        _ERR(0 != net.save_params().runStatus);
        save1((net.saveName + ".nodeNeiAveDeg2.txt").c_str(),
            net.spearman.nodeNeiAveDeg2);
        save1((net.saveName + ".neiAveDeg2.txt").c_str(),
            net.spearman.neiAveDeg2);
      }
    }
  }
  return EXIT_SUCCESS;
}

int main_func::rewire::stat(int argc, char** argv)
{
  for (int e = kEMin; e <= kEMax; ++e) {
    cout << "e\t" << e << endl;
    string data_dir = kDataDir + "2^" + to_string(e) + "/",
           stat_dir = kStatDir + "2^" + to_string(e) + "/";
    mkdirs(stat_dir.c_str());

    for (int seed = kSeedMin; seed <= kSeedMax; ++seed) {
      SHOW_TIME(cout); // 显示系统时间
      cout << "e\t" << e << "\tseed\t" << seed << endl;
      Networks net;
      string fn_read
          = data_dir + "kMin" + to_string(kMin) + "_" + to_string(seed),
          fn_save
          = stat_dir + "kMin" + to_string(kMin) + "_" + to_string(seed);
      net.readName = fn_read + ".Random";
      _ERR(0 != net.read_params().runStatus);
      net.readName = fn_read + ".Random";
      _ERR(0 != net.read_degArr().runStatus);
#ifdef STAT_RELATIVITY
      net.relativity.alpha = relativity_alpha;
#endif
      constexpr size_t rs = sizeof(kRhos) / sizeof(kRhos[0]);
      for (size_t i = 0; i < rs; ++i) {
        net.readName = fn_read + ".rewire_" + kRhoStrings[i];
        net.saveName = fn_save + ".rewire_" + kRhoStrings[i];
        _ERR(0 != net.read_p2p().runStatus);
        _ERR(0 != net.stat().runStatus);
        net.save_params();
      }
    } // for seed
  }   // for e

  return EXIT_SUCCESS;
}

int main_func::rewire::stat_all(int argc, char** argv)
{
  constexpr size_t rs = sizeof(kRhos) / sizeof(kRhos[0]);
  for (size_t i = 0; i < rs; ++i) {
    const string save_prename = kStatDir + "kMin" + to_string(kMin);
    string sufname = string(".rewire_") + kRhoStrings[i] + ".params.txt";

#ifdef STAT_PEARSON
    {
      cout << "statistics pearson" << endl;
      string save_fullname
          = save_prename + ".rewire_" + kRhoStrings[i] + ".pearson.txt";
      ofstream os(save_fullname.c_str());
      if (!os) {
        ERROR();
      } else {
        for (int e = kEMin; e <= kEMax; ++e) {
          double sx = 0, sxx = 0, x_mean = 0, x_sigma = 0;
          size_t n = 0;
          cout << "\te\t" << e << endl;
          string prename = kDataDir + "2^" + to_string(e) + "/kMin"
              + to_string(kMin) + "_",
                 coefficient_string = "--pearson.pearson";
          statistics::sum(prename.c_str(), sufname.c_str(), kSeedMin,
              kSeedMax, coefficient_string.c_str(), sx, sxx, n);
          if (n > 0) {
            x_mean = sx / n;
            x_sigma = sxx / n - x_mean * x_mean;
            x_sigma = x_sigma > 0 ? sqrt(x_sigma) : 0;
            os << e << "\t" << n << "\t" << x_mean << "\t" << x_sigma << endl;
          }
        }
        os.close();
      }
    }
#endif

#ifdef STAT_SPEARMAN
    {
      cout << "statistics spearman" << endl;
      string save_fullname
          = save_prename + ".rewire_" + kRhoStrings[i] + ".spearman.txt";
      ofstream os(save_fullname.c_str());
      if (!os) {
        ERROR();
      } else {
        for (int e = kEMin; e <= kEMax; ++e) {
          double sx = 0, sxx = 0, x_mean = 0, x_sigma = 0;
          size_t n = 0;
          cout << "\te\t" << e << endl;
          string prename = kDataDir + "2^" + to_string(e) + "/kMin"
              + to_string(kMin) + "_",
                 coefficient_string = "--spearman.spearman";
          statistics::sum(prename.c_str(), sufname.c_str(), kSeedMin,
              kSeedMax, coefficient_string.c_str(), sx, sxx, n);
          if (n > 0) {
            x_mean = sx / n;
            x_sigma = sxx / n - x_mean * x_mean;
            x_sigma = x_sigma > 0 ? sqrt(x_sigma) : 0;
            os << e << "\t" << n << "\t" << x_mean << "\t" << x_sigma << endl;
          }
        }
        os.close();
      }
    }
#endif

#ifdef STAT_RELATIVITY
    {
      cout << "statistics relativity" << endl;
      string save_fullname = save_prename + ".rewire_" + kRhoStrings[i]
          + ".relativity" + alpha_string + ".txt";
      ofstream os(save_fullname.c_str());
      if (!os) {
        ERROR();
      } else {
        for (int e = kEMin; e <= kEMax; ++e) {
          double sx = 0, sxx = 0, x_mean = 0, x_sigma = 0;
          size_t n = 0;
          cout << "\te\t" << e << endl;
          string prename = kDataDir + "2^" + to_string(e) + "/kMin"
              + to_string(kMin) + "_",
                 coefficient_string = "--relativity.relativity";
          statistics::sum(prename.c_str(), sufname.c_str(), kSeedMin,
              kSeedMax, coefficient_string.c_str(), sx, sxx, n);
          if (n > 0) {
            x_mean = sx / n;
            x_sigma = sxx / n - x_mean * x_mean;
            x_sigma = x_sigma > 0 ? sqrt(x_sigma) : 0;
            os << e << "\t" << n << "\t" << x_mean << "\t" << x_sigma << endl;
          }
        }
        os.close();
      }
    }
#endif
  }

  return EXIT_SUCCESS;
}

// **********************************************************
#endif
