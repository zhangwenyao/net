#ifndef MAIN__REWIRE__MAIN_H_
#define MAIN__REWIRE__MAIN_H_
#include "../../main.h"
#ifdef MAIN_REWIRE

#include "../../network/net.h"
#include "../../statistics/stat.h"
#include <string>
#define MAIN_FUNC main_func::main_rewire

//#define MAIN_REWIRE_DISTRIBUTION
//#define MAIN_REWIRE_DISTRIBUTION_STAT
#define MAIN_REWIRE_DISTRIBUTION_STAT_ALL
//#define MAIN_REWIRE_NEW_NETWORKS
//#define MAIN_REWIRE_STAT
//#define MAIN_REWIRE_STAT_ALL

// ******************************************************
namespace main_func {
int main_rewire(int argc, char** argv);
namespace rewire {
  const int kEMin = 10, kEMax = 10, kSeedMin = 1, kSeedMax = 10000;
  const double kGamma = 2.5;
  const std::string kGammaString = "2.5";
  const std::string kDataDir
      = std::string("/media/yao/Samsung_T5/net/data/rewire/") + kGammaString
      + "_4/",
      kStatDir = kDataDir + "stat/";
  const double rho = 0.7;
  const std::string kRhoString = "0.7";
  const double kRewireRate = 10;
  const double kNs[] = { 0.1, 0.3, 0.5, 0.7, 0.9 };
}
}

// ******************************************************
#endif // MAIN
#endif // _H_
