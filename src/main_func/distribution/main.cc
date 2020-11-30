#include "main.h"
#ifdef MAIN_DISTRIBUTION

//#include "../../common/common.h"
//#include "../../network/net.h"
//#include "distribution.h"

using namespace std;
// using namespace common;
// using namespace network;
// using namespace main_func::distribution;

// ******************************************************

int main_func::main_distribution(int argc, char** argv)
{
  //_ERR(distribution::new_distribution(argc, argv));
  unsigned sum = 0;
  for (unsigned j = 0; j < 10; ++j)
#ifdef NET_OMP
#pragma omp parallel for reduction(+ : sum)
#endif
    for (unsigned i = 0; i < UINT_MAX; ++i) {
      sum += i >> 25;
    }
  cout << sum << endl;

  return 0;
}

#endif
