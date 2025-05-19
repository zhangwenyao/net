#include "main.h"
#ifdef MAIN_SPREADER

#include "../../common/common.h"
// #include "../../network/net.h"
#include "spreader.h"

using namespace std;
using namespace common;
// using namespace network;
using namespace main_func::spreader;

int main_func::check_args(int argc, char** argv) { return EXIT_SUCCESS; }

// ******************************************************
int main_func::main_spreader(int argc, char** argv) {
  string dirData = kDataDir, dirStat = kStatDir;
  mkdirs(dirStat.c_str());

  check_args(argc, argv);

#ifdef MAIN_SPREADER_DATA
  _ERR(spreader::networks_data(argc, argv));
#endif

#ifdef MAIN_SPREADER_CALC
  _ERR(spreader::networks_calc(argc, argv));
#endif

#ifdef MAIN_SPREADER_STAT
  _ERR(spreader::networks_stat(argc, argv));
#endif

#ifdef MAIN_SPREADER_TEST
  _ERR(spreader::networks_test(argc, argv));
#endif

  return 0;
}

#endif
