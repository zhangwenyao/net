#include "distribution.h"
#ifdef MAIN_REWIRE_DISTRIBUTION

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;
using namespace network::correlation;
using namespace main_func::rewire;

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
  return 0;
}

#endif
