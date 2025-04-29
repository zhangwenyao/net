#include "distribution_stat_all.h"
#ifdef MAIN_REWIRE_DISTRIBUTION_STAT_ALL

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;

//**//****************************************************//*
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
      statistics::sum(prename.c_str(), sufname.c_str(), kSeedMin, kSeedMax,
          coefficient_string.c_str(), sx, sxx, n);
      if (n > 0) {
        x_mean = sx / n;
        x_sigma = sxx / n - x_mean * x_mean;
        x_sigma = x_sigma > 0 ? sqrt(x_sigma) : 0;
        os << e << "\t" << n << "\t" << x_mean << "\t" << x_sigma << endl;
      }
      os.close();
    }
  } // e
  return 0;
}

//**//****************************************************//*
#endif
