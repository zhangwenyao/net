#ifndef MAIN__SPEARMAN__MAIN_H_
#define MAIN__SPEARMAN__MAIN_H_
#include "../../main.h"
#ifdef MAIN_SPEARMAN

#include "../../common/common.h"
#include "../../network/net.h"
#include <string>
#define MAIN_FUNC main_func::main_spearman

//#define MAIN_SPEARMAN_RANDOM
//#define MAIN_SPEARMAN_GAUSS
//#define MAIN_SPEARMAN_R_RANDOM
//#define MAIN_SPEARMAN_R_GAUSS
#define MAIN_SPEARMAN_R_STAT
//#define MAIN_SPEARMAN_TEST

// ******************************************************
namespace main_func {
int main_spearman(int argc, char** argv);
namespace spearman {
  constexpr int kSeed0 = 1;
  constexpr int kMin = 3, kEMin = 14, kEMax = 14, kSeedMin = 1,
                kSeedMax = 300;
  constexpr double kGamma = 2.5;
  const std::string kGammaString = "2.5";
  const std::string kDataDir
      = std::string("/media/yao/Samsung_T5/net/data/spearman/sqrt/random/")
      + kGammaString + "_" + std::to_string(kMin) + "/",
      kStatDir = kDataDir + "stat/";
  constexpr double kNs[] = { 0.1, 0.3, 0.5, 0.7, 0.9 };
  constexpr double rho = 0.9;
  const std::string kRhoString = "0.9";
  constexpr double kRewireRate = 1 << 7;
  // constexpr double kRhos[]
  //= { 0.05, 0.15, 0.25, 0.35, 0.45, 0.55, 0.65, 0.75, 0.85, 0.95 };
  // const std::string kRhoStrings[] = { "0.05", "0.15", "0.25", "0.35",
  // "0.45", "0.55", "0.65", "0.75", "0.85", "0.95" };
  constexpr double kRhos[]
      = { 0.00, 0.10, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1.00 };
  const std::string kRhoStrings[] = { "0.00", "0.10", "0.20", "0.30", "0.40",
    "0.50", "0.60", "0.70", "0.80", "0.90", "1.00" };
  constexpr size_t rho_len = sizeof(kRhos) / sizeof(kRhos[0]);
  constexpr double kSpearmanRs[] = { -0.740593, -0.486063, -0.306593,
    -0.156328, 0.0196967, 0.112153, 0.245352, 0.387978, 0.554167, 0.780197 };
}
}

// ******************************************************
#endif // MAIN
#endif // _H_
