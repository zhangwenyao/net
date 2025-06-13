#include "main.h"
#ifdef MAIN_BETWEENNESS

#include "../../common/common.h"
// #include "../../network/net.h"
#include "betweenness.h"

using namespace std;
using namespace common;
// using namespace network;
using namespace main_func::betweenness;

// ******************************************************
namespace main_func {
namespace betweenness {
string kDataDir = std::string("data/DataSet");
string kStatDir = kDataDir;
vector<string> kDatasetNames = {"example", "Email",      "Facebook2012",
                                "CondMat", "EmailEnron", "Facebook"};
int configs_2_main(void);
}  // namespace betweenness
}  // namespace main_func
// ******************************************************
int main_func::betweenness::configs_2_main(void) {
  if (configs.contains("kDataDir"))
    main_func::betweenness::kDataDir = configs["kDataDir"].get<string>();
  if (configs.contains("kStatDir"))
    main_func::betweenness::kStatDir = configs["kStatDir"].get<string>();
  if (configs.contains("kDatasetNames"))
    main_func::betweenness::kDatasetNames =
        configs["kDatasetNames"].get<vector<string>>();
  INFORM("main_func::betweenness configs");
  cout << "kDataDir: " << main_func::betweenness::kDataDir << "\n"
       << "kStatDir: " << main_func::betweenness::kStatDir << "\n"
       << "kDatasetNames: " << main_func::betweenness::kDatasetNames << "\n"
       << flush;
  return EXIT_SUCCESS;
}

// ******************************************************
int main_func::main_betweenness(int argc, char** argv) {
  string dirData = kDataDir, dirStat = kStatDir;
  mkdirs(dirStat.c_str());

  _ERR(common::check_args_config(argc, argv));
  _ERR(betweenness::configs_2_main());

#ifdef MAIN_BETWEENNESS_DATA
  _ERR(betweenness::networks_data(argc, argv));
#endif

#ifdef MAIN_BETWEENNESS_STAT
  _ERR(betweenness::networks_stat(argc, argv));
#endif

#ifdef MAIN_BETWEENNESS_TEST
  _ERR(betweenness::networks_test(argc, argv));
#endif

  return 0;
}

#endif
