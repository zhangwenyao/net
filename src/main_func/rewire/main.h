#ifndef MAIN__REWIRE__MAIN_H_
#define MAIN__REWIRE__MAIN_H_
#include "../../main.h"
#ifdef MAIN_REWIRE

#include "../../network/net.h"
#include <string>
#define MAIN_FUNC main_func::main_rewire

//#define MAIN_REWIRE_DISTRIBUTION
//#define MAIN_REWIRE_DISTRIBUTION_STAT
//#define MAIN_REWIRE_DISTRIBUTION_STAT_ALL
//#define MAIN_REWIRE_NETWORKS_RANDOM
#define MAIN_REWIRE_NETWORKS_RANDOM1
//#define MAIN_REWIRE_STAT
//#define MAIN_REWIRE_STAT_ALL

// ******************************************************
namespace main_func {
int main_rewire(int argc, char** argv);
namespace rewire {
  constexpr int kSeed0 = 1;
  constexpr int kMin = 4, kEMin = 14, kEMax = 14, kSeedMin = 1,
                kSeedMax = 300;
  constexpr double kGamma = 2.5;
  const std::string kGammaString = "2.5";
  const std::string kDataDir
      = std::string("/media/yao/Samsung_T5/net/data/rewire/random")
      + std::to_string(kSeed0) + "/" + kGammaString + "_"
      + std::to_string(kMin) + "/",
      kStatDir = kDataDir + "stat/";
  constexpr double kNs[] = { 0.1, 0.3, 0.5, 0.7, 0.9 };
  constexpr double rho = 0.9;
  const std::string kRhoString = "0.9";
  constexpr double kRewireRate = 1 << 7;
  constexpr double kRhos[]
      = { 0.05, 0.15, 0.25, 0.35, 0.45, 0.55, 0.65, 0.75, 0.85, 0.95 };
  const std::string kRhoStrings[] = { "0.05", "0.15", "0.25", "0.35", "0.45",
    "0.55", "0.65", "0.75", "0.85", "0.95" };
}
}

// ******************************************************
#endif // MAIN
#endif // _H_
