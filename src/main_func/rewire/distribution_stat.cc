#include "distribution_stat.h"
#ifdef MAIN_REWIRE_DISTRIBUTION_STAT

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;

//**//****************************************************//*
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
  return 0;
}

//**//****************************************************//*
#endif
