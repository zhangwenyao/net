#include "extremum.h"
#ifdef MAIN_EXTREMUM

#include "../../common/common.h"
#include "../../model/extremum/extremum.h"
#include "../../network/networks.h"
#include "../../statistics/stat.h"
using namespace std;
using namespace common;
using namespace network;

//**//**************************************************//**//*
int main_func::extremum::new_deg_arr(int argc, char** argv)
{
  for (int e = kEMin; e <= kEMax; ++e) {
    cout << "e\t" << e << endl;
    string data_dir = kDataDir + "2^" + to_string(e) + "/", fn_full;

    for (int seed = kSeedMin; seed <= kSeedMax; ++seed) {
      SHOW_TIME(cout); // 显示系统时间
      cout << "e\t" << e << "\nseed\t" << seed << endl;
      Networks net;
      net.seed = seed;
      net.nodeSize = (NodeType)1 << e; // 节点数
      net.degree.power_gamma = kGamma; // 度分布幂律分布的幂指数
      net.kMin = 4;                    // 最小度
      net.readName = data_dir + "kMin" + to_string(net.kMin);
      net.saveName = net.readName;
      net.argv = "--init_seed0 "
                 "--cal_deg power_arr "
                 "--save_seed "
                 "--print";

      fn_full = net.readName + ".probSum.txt";
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

  return 0;
}

#ifdef MAIN_EXTREMUM_NONE
int main_func::extremum::new_minimal(int argc, char** argv)
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
      net.saveName = fn_full + ".Min";
      net.lkk_type = lkk3_lkk3;
      net.argv = "--init_seed0 "
                 "--cal_deg read_degArr "
                 "--cal_p2p Min_lkk3 "
                 "--print";

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
        net.save_p2p();
      }
    }
  }

  return 0;
}

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

int main_func::extremum::stat_minimal(int argc, char** argv)
{
  mkdirs(kStatDir.c_str());
  for (int e = kEMin; e <= kEMax; ++e) {
    cout << "e\t" << e << endl;
    string data_dir = kDataDir + "2^" + to_string(e) + "/",
           stat_dir = kStatDir + "2^" + to_string(e) + "/";
    mkdirs(stat_dir.c_str());

    for (int seed = kSeedMin; seed <= kSeedMax; ++seed) {
      SHOW_TIME(cout); // 显示系统时间
      cout << "e\t" << e << "\tseed\t" << seed << endl;
      Networks net;
      string fn_full0 = data_dir + "kMin4_" + to_string(seed),
             fn_full = fn_full0 + ".Min";
      net.readName = fn_full;
      _ERR(0 != net.read_params().runStatus);
      net.readName = fn_full;
      _ERR(0 != net.read_degArr(fn_full0.c_str()).runStatus);
      _ERR(0 != net.read_lkk().runStatus);
#ifdef STAT_RELATIVITY
      net.relativity.alpha = relativity_alpha;
#endif
      _ERR(argc > 1 && 0 != net.read_params(argc - 1, argv + 1).runStatus);
      _ERR(0 != net.stat().runStatus);
      net.saveName = stat_dir + "kMin4_" + to_string(seed) + ".Min";
      net.save_params();
    } // for seed
  }   // for e

  return 0;
}

int main_func::extremum::stat_maximal(int argc, char** argv)
{
  mkdirs(kStatDir.c_str());
  for (int e = kEMin; e <= kEMax; ++e) {
    cout << "e\t" << e << endl;
    string data_dir = kDataDir + "2^" + to_string(e) + "/",
           stat_dir = kStatDir + "2^" + to_string(e) + "/";
    mkdirs(stat_dir.c_str());

    for (int seed = kSeedMin; seed <= kSeedMax; ++seed) {
      SHOW_TIME(cout); // 显示系统时间
      cout << "e\t" << e << "\tseed\t" << seed << endl;
      Networks net;
      string fn_full0 = data_dir + "kMin4_" + to_string(seed),
             fn_full = fn_full0 + ".Max";
      net.readName = fn_full;
      _ERR(0 != net.read_params().runStatus);
      net.readName = fn_full;
      _ERR(0 != net.read_degArr(fn_full0.c_str()).runStatus);
      _ERR(0 != net.read_lkk().runStatus);
#ifdef STAT_RELATIVITY
      net.relativity.alpha = relativity_alpha;
#endif
      _ERR(argc > 1 && 0 != net.read_params(argc - 1, argv + 1).runStatus);
      _ERR(0 != net.stat().runStatus);
      net.saveName = stat_dir + "kMin4_" + to_string(seed) + ".Max";
      net.save_params();
    } // for seed
  }   // for e

  return 0;
}

//**//****************************************************//*
int main_func::extremum::stat_all(int argc, char** argv)
{
  const string save_prename = kStatDir + "kMin4";

#ifdef STAT_PEARSON
#ifdef MAIN_EXTREMUM_STAT_MINIMAL
  {
    cout << "statistics pearson minimal" << endl;
    string save_fullname = save_prename + ".pearson.minimal.txt";
    ofstream os(save_fullname.c_str());
    if (!os) {
      ERROR();
    } else {
      for (int e = kEMin; e <= kEMax; ++e) {
        double sx = 0, sxx = 0, x_mean = 0, x_sigma = 0;
        size_t n = 0;
        cout << "\te\t" << e << endl;
        string prename = kStatDir + "2^" + to_string(e) + "/kMin4_",
               sufname = ".Min.params.txt",
               coefficient_string = "--pearson.pearson";
        statistics::sum(prename.c_str(), sufname.c_str(), 1, 100,
            coefficient_string.c_str(), sx, sxx, n);
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
#ifdef MAIN_EXTREMUM_STAT_MAXIMAL
  {
    cout << "statistics pearson maximal" << endl;
    string save_fullname = save_prename + ".pearson.maximal.txt";
    ofstream os(save_fullname.c_str());
    if (!os) {
      ERROR();
    } else {
      for (int e = kEMin; e <= kEMax; ++e) {
        double sx = 0, sxx = 0, x_mean = 0, x_sigma = 0;
        size_t n = 0;
        cout << "\te\t" << e << endl;
        string prename = kStatDir + "2^" + to_string(e) + "/kMin4_",
               sufname = ".Max.params.txt",
               coefficient_string = "--pearson.pearson";
        statistics::sum(prename.c_str(), sufname.c_str(), 1, 100,
            coefficient_string.c_str(), sx, sxx, n);
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
#endif

#ifdef STAT_SPEARMAN
#ifdef MAIN_EXTREMUM_STAT_MINIMAL
  {
    cout << "statistics spearman minimal" << endl;
    string save_fullname = save_prename + ".spearman.minimal.txt";
    ofstream os(save_fullname.c_str());
    if (!os) {
      ERROR();
    } else {
      for (int e = kEMin; e <= kEMax; ++e) {
        double sx = 0, sxx = 0, x_mean = 0, x_sigma = 0;
        size_t n = 0;
        cout << "\te\t" << e << endl;
        string prename = kStatDir + "2^" + to_string(e) + "/kMin4_",
               sufname = ".Min.params.txt",
               coefficient_string = "--spearman.spearman";
        statistics::sum(prename.c_str(), sufname.c_str(), 1, 100,
            coefficient_string.c_str(), sx, sxx, n);
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
#ifdef MAIN_EXTREMUM_STAT_MAXIMAL
  {
    cout << "statistics spearman maximal" << endl;
    string save_fullname = save_prename + ".spearman.maximal.txt";
    ofstream os(save_fullname.c_str());
    if (!os) {
      ERROR();
    } else {
      for (int e = kEMin; e <= kEMax; ++e) {
        double sx = 0, sxx = 0, x_mean = 0, x_sigma = 0;
        size_t n = 0;
        cout << "\te\t" << e << endl;
        string prename = kStatDir + "2^" + to_string(e) + "/kMin4_",
               sufname = ".Max.params.txt",
               coefficient_string = "--spearman.spearman";
        statistics::sum(prename.c_str(), sufname.c_str(), 1, 100,
            coefficient_string.c_str(), sx, sxx, n);
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
#endif

#ifdef STAT_RELATIVITY
#ifdef MAIN_EXTREMUM_STAT_MINIMAL
  {
    cout << "statistics relativity minimal" << endl;
    string save_fullname
        = save_prename + ".relativity" + alpha_string + ".minimal.txt";
    ofstream os(save_fullname.c_str());
    if (!os) {
      ERROR();
    } else {
      for (int e = kEMin; e <= kEMax; ++e) {
        double sx = 0, sxx = 0, x_mean = 0, x_sigma = 0;
        size_t n = 0;
        cout << "\te\t" << e << endl;
        string prename = kStatDir + "2^" + to_string(e) + "/kMin4_",
               sufname = ".Min.params.txt",
               coefficient_string = "--relativity.relativity";
        statistics::sum(prename.c_str(), sufname.c_str(), 1, 100,
            coefficient_string.c_str(), sx, sxx, n);
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
#ifdef MAIN_EXTREMUM_STAT_MAXIMAL
  {
    cout << "statistics relativity maximal" << endl;
    string save_fullname
        = save_prename + ".relativity" + alpha_string + ".maximal.txt";
    ofstream os(save_fullname.c_str());
    if (!os) {
      ERROR();
    } else {
      for (int e = kEMin; e <= kEMax; ++e) {
        double sx = 0, sxx = 0, x_mean = 0, x_sigma = 0;
        size_t n = 0;
        cout << "\te\t" << e << endl;
        string prename = kStatDir + "2^" + to_string(e) + "/kMin4_",
               sufname = ".Max.params.txt",
               coefficient_string = "--relativity.relativity";
        statistics::sum(prename.c_str(), sufname.c_str(), 1, 100,
            coefficient_string.c_str(), sx, sxx, n);
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
#endif

  return 0;
}

//**//****************************************************//*
#elif defined(STAT_RELATIVITY) && defined(MAIN_EXTREMUM_ALPHAS)
int main_func::extremum::alphas_stat_maximal_lkk(int argc, char** argv)
{
  mkdirs(kStatDir.c_str());
  for (int e = kEMin; e <= kEMax; ++e) {
    cout << "e\t" << e << endl;
    string data_dir = kDataDir + "2^" + to_string(e) + "/",
           stat_dir = kStatDir + "2^" + to_string(e) + "/";
    mkdirs(stat_dir.c_str());

    for (int seed = kSeedMin; seed <= kSeedMax; ++seed) {
      SHOW_TIME(cout); // 显示系统时间
      cout << "e\t" << e << "\tseed\t" << seed << endl;
      Networks net;
      string fn_full0 = data_dir + "kMin4_" + to_string(seed),
             fn_full = fn_full0 + ".Max";
      net.readName = fn_full0;
      _ERR(0 != net.read_params().runStatus);
      _ERR(0 != net.read_degArr(fn_full0.c_str()).runStatus);

      VDouble alphas(alpha_len);
      VVDouble results(3, VDouble(alpha_len, 0));
      _ERR(0
          != network::extremum::cal_Max_lkk_statistics(net.degArrVal,
                 net.degArrSize, relativity_alphas, results[0]));
      for (auto& x : results[0])
        x /= net.linkSize;
      for (size_t i = 0; i < alpha_len; ++i)
        alphas[i] = relativity_alphas[i] + 1;
      _ERR(0
          != network::statistics::cal_degArr_sum_alphas(
                 net.degArrVal, net.degArrSize, &alphas[0], results[1]));
      for (auto& x : results[1])
        x /= net.linkSize * 2;
      for (size_t i = 0; i < alpha_len; ++i)
        alphas[i] = relativity_alphas[i] * 2 + 1;
      _ERR(0
          != network::statistics::cal_degArr_sum_alphas(
                 net.degArrVal, net.degArrSize, &alphas[0], results[2]));
      for (auto& x : results[2])
        x /= net.linkSize * 2;
      // for (size_t i = 0; i < alpha_len; ++i) {
      // const double exx = results[1][i] * results[1][i];
      // if (results[2][i] - exx != 0)
      // results[3][i] = (results[0][i] - exx) / (results[2][i] - exx);
      //}
      string savename
          = stat_dir + "kMin4_" + to_string(seed) + ".Max.alphas.txt";
      common::save_double2(savename.c_str(), results);
    } // for seed
  }   // for e

  return 0;
}

int main_func::extremum::alphas_stat_all(int argc, char** argv)
{
#ifdef MAIN_EXTREMUM_ALPHAS_STAT_MAXIMAL_COLLECT
  const string kStatDir = main_func_extremum_kStatDir0,
               save_prename = kStatDir + "kMin4";
  cout << "statistics relativity maximal" << endl;
      for (int e = kEMin; e <= kEMax; ++e) {
      for (int seed = kSeedMin; seed <= kSeedMax; ++seed) {

  for (size_t ai = 0; ai < alpha_len; ++ai) {
    relativity_alpha = relativity_alphas[ai];
    const string alpha_string = alpha_strings[ai];
    string save_fullname
        = save_prename + ".relativity" + alpha_string + ".maximal.alphas.txt";
        VDouble sx(alpha_len, 0), sxx = sx, x_mean = sx, x_sigma = sx;
        size_t n = 0;
        cout << "\te\t" << e << endl;
        string prename = kStatDir + "2^" + to_string(e) + "/kMin4_",
               sufname = ".Max.alphas.txt";
        relativity::alphas_sum(
            prename.c_str(), sufname.c_str(), 1, 100, sx, sxx, n);
        if (n > 0) {
          for (size_t i = 0; i < alpha_len; ++i) {
            x_mean[i] = sx[i] / n;
            x_sigma[i] = sxx[i] / n - x_mean[i] * x_mean[i];
            x_sigma[i] = x_sigma[i] > 0 ? sqrt(x_sigma[i]) : 0;
            os[i] << e << "\t" << n << "\t" << x_mean << "\t" << x_sigma
                  << endl;
          }
        }
      }
    }
#endif
    return 0;
  }
#endif

//**//****************************************************//*
#endif
