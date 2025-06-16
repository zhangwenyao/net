#include "main.h"
#ifdef MAIN_INDEXES

#include "../../common/common.h"
// #include "../../network/net.h"
#include "indexes.h"

using namespace std;
using namespace common;
// using namespace network;
using namespace main_func::indexes;

// ******************************************************
namespace main_func {
namespace indexes {
string kDataDir = std::string("data/DataSet");
string kStatDir = kDataDir;
vector<string> kDatasetNames = {"example"};
bool kClean = false;
int configs_2_main(void);
}  // namespace indexes
}  // namespace main_func
// ******************************************************
int main_func::indexes::configs_2_main(void) {
  if (configs.contains("kDataDir"))
    main_func::indexes::kDataDir = configs["kDataDir"].get<string>();
  if (configs.contains("kStatDir"))
    main_func::indexes::kStatDir = configs["kStatDir"].get<string>();
  if (configs.contains("kDatasetNames"))
    main_func::indexes::kDatasetNames =
        configs["kDatasetNames"].get<vector<string>>();
  if (configs.contains("kClean"))
    main_func::indexes::kClean = configs["kClean"].get<bool>();
  INFORM("main_func::indexes configs");
  cout << "kDataDir: " << main_func::indexes::kDataDir << "\n"
       << "kStatDir: " << main_func::indexes::kStatDir << "\n"
       << "kDatasetNames: " << main_func::indexes::kDatasetNames << "\n"
       << "kClean: " << main_func::indexes::kClean << "\n"
       << flush;
  return EXIT_SUCCESS;
}

// ******************************************************
int main_func::main_indexes(int argc, char** argv) {
  string dirData = kDataDir, dirStat = kStatDir;
  mkdirs(dirStat.c_str());

  _ERR(common::check_args_config(argc, argv));
  _ERR(indexes::configs_2_main());

#ifdef MAIN_INDEXES_DATA
  _ERR(indexes::networks_data(argc, argv));
#endif

#ifdef MAIN_INDEXES_STAT
  _ERR(indexes::networks_stat(argc, argv));
#endif

#ifdef MAIN_INDEXES_TEST
  _ERR(indexes::networks_test(argc, argv));
#endif

  return 0;
}

#endif
