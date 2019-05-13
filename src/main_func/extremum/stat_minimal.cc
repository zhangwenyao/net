#include "stat_minimal.h"
#ifdef MAIN_EXTREMUM_STAT_MINIMAL

#include "../../common/common.h"
#include "../../model/extremum/extremum.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;
using namespace network::extremum;

//**//****************************************************//*
int main_func::extremum::stat_minimal(int argc, char** argv)
{
  MKDIR(kStatDir.c_str());
  for (int e = kEMin; e <= kEMax; ++e) {
    cout << "e\t" << e << endl;
    string data_dir = kDataDir + "2^" + to_string(e) + "/",
           stat_dir = kStatDir + "2^" + to_string(e) + "/";
    MKDIR(stat_dir.c_str());

    for (int seed = kSeedMin; seed <= kSeedMax; ++seed) {
      cout << "e\t" << e << "\tseed\t" << seed << endl;
      Networks net;
      string fn_full = data_dir + "kMin4_" + to_string(seed) + ".Min";
      net.readName = fn_full;
      _ERR(0 != net.read_params().runStatus);
      _ERR(argc > 1 && 0 != net.read_params(argc - 1, argv + 1).runStatus);
      _ERR(0 != net.read_degArr().runStatus);
      _ERR(0 != net.read_lkk(net.saveName.c_str()).runStatus);
      _ERR(0 != net.stat().runStatus);
      net.saveName = stat_dir + "kMin4_" + to_string(seed) + ".Min";
      net.save_params();
    } // for seed
  }   // for e

  return 0;
}

//**//****************************************************//*
#endif
