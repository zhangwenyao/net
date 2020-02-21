#include "stat_maximal.h"
#ifdef MAIN_EXTREMUM_STAT_MAXIMAL

#include "../../common/common.h"
#include "../../model/extremum/extremum.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;
using namespace network::extremum;

//**//****************************************************//*
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

#ifdef STAT_RELATIVITY
int main_func::extremum::stat_maximal_lkk_alphas(int argc, char** argv)
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
          != cal_Max_lkk_statistics(net.degArrVal, net.degArrSize,
                 relativity_alphas, results[0]));
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
#endif

//**//****************************************************//*
#endif
