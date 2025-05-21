#include "main.h"
#ifdef MAIN_SPREADER

#include "../../common/common.h"
// #include "../../network/net.h"
#include "spreader.h"

using namespace std;
using namespace common;
// using namespace network;
using namespace main_func::spreader;

// ******************************************************
namespace main_func {
namespace spreader {
int kSeedMin = 1, kSeedMax = 10;
string kDataDir = std::string("data/spreader");
string kStatDir = kDataDir, kStatDir2 = "beta0.05_gamma1";
vector<string> kDatasetNames = {
    // "example"
    "CondMat"
    // "Email-Enron"
    // "Facebook"
};
double kBeta = 0.05, kGamma = 1.0;
bool kCalcFlag = false, kStatFlag = false;
}  // namespace spreader
}  // namespace main_func
// ******************************************************
int configs_2_main(void) {
  if (configs.contains("kBeta"))
    main_func::spreader::kBeta = configs["kBeta"].get<double>();
  if (configs.contains("kGamma"))
    main_func::spreader::kGamma = configs["kGamma"].get<double>();
  if (configs.contains("kSeedMin"))
    main_func::spreader::kSeedMin = configs["kSeedMin"].get<int>();
  if (configs.contains("kSeedMax"))
    main_func::spreader::kSeedMax = configs["kSeedMax"].get<int>();
  if (configs.contains("kDataDir"))
    main_func::spreader::kDataDir = configs["kDataDir"].get<string>();
  if (configs.contains("kStatDir"))
    main_func::spreader::kStatDir = configs["kStatDir"].get<string>();
  if (configs.contains("kStatDir2"))
    main_func::spreader::kStatDir2 = configs["kStatDir2"].get<string>();
  if (configs.contains("kDatasetNames"))
    main_func::spreader::kDatasetNames =
        configs["kDatasetNames"].get<vector<string>>();
  if (configs.contains("kCalcFlag"))
    main_func::spreader::kCalcFlag = configs["kCalcFlag"].get<bool>();
  if (configs.contains("kStatFlag"))
    main_func::spreader::kStatFlag = configs["kStatFlag"].get<bool>();
  INFORM("main_func::spreader configs");
  cout << "kBeta: " << main_func::spreader::kBeta << "\n"
       << "kGamma: " << main_func::spreader::kGamma << "\n"
       << "kSeedMin: " << main_func::spreader::kSeedMin << "\n"
       << "kSeedMax: " << main_func::spreader::kSeedMax << "\n"
       << "kDataDir: " << main_func::spreader::kDataDir << "\n"
       << "kStatDir: " << main_func::spreader::kStatDir << "\n"
       << "kStatDir2: " << main_func::spreader::kStatDir2 << "\n"
       << "kDatasetNames: " << main_func::spreader::kDatasetNames << "\n"
       << "kCalcFlag: " << main_func::spreader::kCalcFlag << "\n"
       << "kStatFlag: " << main_func::spreader::kStatFlag << "\n"
       << flush;
  return EXIT_SUCCESS;
}

int main_func::check_args(int argc, char** argv) {
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      if (0 == strcmp(argv[i], "--config")) {
        if (i + 1 < argc) {
          cout << argv[i] << " " << argv[i + 1] << "\n";
          ifstream ifs(argv[i + 1]);
          if (!ifs.is_open()) {
            cout << "Error: config file " << config_file << " not found!\n";
            return EXIT_FAILURE;
          }
          ifs >> configs;
          ifs.close();
          i++;
        }
      }
    }
  }
  _ERR(configs_2_main());
  return EXIT_SUCCESS;
}

int main_func::main_spreader(int argc, char** argv) {
  string dirData = kDataDir, dirStat = kStatDir;
  mkdirs(dirStat.c_str());

  _ERR(check_args(argc, argv));

#ifdef MAIN_SPREADER_DATA
  _ERR(spreader::networks_data(argc, argv));
#endif

#ifdef MAIN_SPREADER_CALC
  if (spreader::kCalcFlag) _ERR(spreader::networks_calc(argc, argv));
#endif

#ifdef MAIN_SPREADER_STAT
  if (spreader::kStatFlag) _ERR(spreader::networks_stat(argc, argv));
#endif

#ifdef MAIN_SPREADER_TEST
  _ERR(spreader::networks_test(argc, argv));
#endif

  return 0;
}

#endif
