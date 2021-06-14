#ifndef MAIN__DISTRIBUTION__MAIN_H_
#define MAIN__DISTRIBUTION__MAIN_H_
#include "../../main.h"
#ifdef MAIN_DISTRIBUTION

#include "../../network/net.h"
#include <string>
#define MAIN_FUNC main_func::main_distribution

// ******************************************************
namespace main_func {
int main_distribution(int argc, char** argv);
namespace distribution {
  static constexpr int kMin = 4, kEMin = 14, kEMax = 14, kSeedMin = 1,
                       kSeedMax = 1;
  constexpr double kGamma = 2.5;
  const std::string kGammaString = "2.5";
  const std::string kDataDir
      = std::string("/media/yao/Samsung_T5/net/data/distribution/")
      + kGammaString + "_" + std::to_string(kMin) + "/",
      kStatDir = kDataDir + "stat/";
  static constexpr int n = 100;
}
}

// ******************************************************
#endif // MAIN
#endif // _H_
