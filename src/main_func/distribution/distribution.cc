#include "distribution.h"
#ifdef MAIN_DISTRIBUTION

#include "../../common/common.h"
#include "../../network/networks.h"
#include "../../statistics/stat.h"
using namespace std;
using namespace common;
using namespace network;

//**//**************************************************//**//*
int main_func::distribution::new_distribution(int argc, char** argv)
{
  // int n = 100;
  unsigned sum = 0;
#ifdef NET_OMP
#pragma omp parallel for reduction(+ : sum)
#endif
  for (unsigned j = 0; j < 40; ++j) {
#ifdef NET_OMP
//#pragma omp parallel for
#endif
    for (unsigned i = 0; i < UINT_MAX; ++i) {
      sum += i >> 25;
    }
  }
  cout << sum << endl;

  return 0;
}

//**//****************************************************//*
#endif
