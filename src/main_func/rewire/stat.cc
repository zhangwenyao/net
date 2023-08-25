#include "stat.h"
#ifdef MAIN_REWIRE_STAT

#include "../../common/common.h"
#include "../../model/extremum/extremum.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;

//**//****************************************************//*
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
      string fn_full0 = data_dir + "kMin4_" + to_string(seed),
             fn_full = fn_full0 + ".rewire_" + kRhoString;
      net.readName = fn_full0;
      _ERR(0 != net.read_params().runStatus);
      _ERR(0 != net.read_degArr(fn_full0.c_str()).runStatus);
      net.readName = fn_full;
      _ERR(0 != net.read_p2p().runStatus);
#ifdef STAT_RELATIVITY
      net.relativity.alpha = relativity_alpha;
#endif
      _ERR(argc > 1 && 0 != net.read_params(argc - 1, argv + 1).runStatus);
      _ERR(0 != net.stat().runStatus);
      net.saveName
          = stat_dir + "kMin4_" + to_string(seed) + ".rewire_" + kRhoString;
      net.save_params();
    } // for seed
  }   // for e

  return 0;
}

//**//****************************************************//*
#endif
