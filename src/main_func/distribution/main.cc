#include "main.h"
#ifdef MAIN_DISTRIBUTION

#include "../../common/common.h"
//#include "../../network/net.h"
#include "distribution.h"

using namespace std;
using namespace common;
// using namespace network;
using namespace main_func::distribution;

// ******************************************************

int main_func::main_distribution(int argc, char** argv)
{
  _ERR(distribution::new_distribution(argc, argv));
  return 0;
}

#endif
