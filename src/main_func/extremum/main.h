#ifndef MAIN__EXTREMUM__MAIN_H_
#define MAIN__EXTREMUM__MAIN_H_
#include "../../main.h"
#ifdef MAIN_EXTREMUM

#include "../../network/net.h"
#include <string>
#define MAIN_FUNC main_func::main_extremum

#define MAIN_EXTREMUM_NEW_DEG_ARR

//#define MAIN_EXTREMUM_NONE
//#define MAIN_EXTREMUM_NEW_MAXIMAL
//#define MAIN_EXTREMUM_NEW_MINIMAL
//#define MAIN_EXTREMUM_STAT_MAXIMAL
//#define MAIN_EXTREMUM_STAT_MINIMAL
//#define MAIN_EXTREMUM_STAT_ALL
//#define MAIN_EXTREMUM_STAT_ALL_COLLECT

#define MAIN_EXTREMUM_ALPHAS
//#define MAIN_EXTREMUM_ALPHAS_STAT_MAXIMAL
#define MAIN_EXTREMUM_ALPHAS_STAT_MINIMAL
//#define MAIN_EXTREMUM_ALPHAS_STAT_MAXIMAL_COLLECT
//#define MAIN_EXTREMUM_ALPHAS_STAT_MINIMAL_COLLECT

// ******************************************************
namespace main_func {
int main_extremum(int argc, char** argv);
namespace extremum {
  const int kEMin = 58, kEMax = 60, kSeedMin = 101, kSeedMax = 300;
  constexpr int kMin = 4;
  constexpr double kGamma = 2.5;
  const std::string kGammaString = "2.5";
  // const std::string kDataDir = std::string("data/extremum/nature/")
  //+ kGammaString + "_" + to_string(kMin) + "/data/";
  const std::string kDataDir
      = std::string("/media/yao/Samsung_T5/net/data/extremum/nature/")
      + kGammaString + "_" + std::to_string(kMin) + "/";
#ifndef STAT_RELATIVITY
  const std::string kStatDir = std::string("data/extremum/nature/")
      + kGammaString + "_" + std::to_string(kMin) + "/stat/pearson_spearman/";
#else
  constexpr double kGamma_2 = kGamma - 2.0;
  const double relativity_alphas[] = { 1.0, 2.0, -1.0, -2.0, kGamma_2 * 2,
    kGamma_2 * 3 / 2, kGamma_2, kGamma_2 * 3 / 4, kGamma_2 / 2, kGamma_2 / 4,
    kGamma_2*(-1.0 / 4), kGamma_2*(-1.0 / 2), kGamma_2*(-1.0),
    kGamma_2*(-2.0), kGamma_2*(-3.0), kGamma_2*(-4.0) };
  const std::string alpha_strings[] = { "C1", "C2", "C-1", "C-2", "2", "3d2",
    "1", "3d4", "1d2", "1d4", "-1d4", "-1d2", "-1", "-2", "-3", "-4" };
  // const double relativity_alphas[] = { -kGamma_2 * 2 };
  // const std::string alpha_strings[] = { "-2" };
  constexpr size_t alpha_len
      = sizeof(relativity_alphas) / sizeof(relativity_alphas[0]);
  extern double relativity_alpha;
  extern std::string alpha_string, kStatDir;
#define main_func_extremum_kStatDir0                                         \
  (std::string("data/extremum/nature/") + main_func::extremum::kGammaString  \
      + "_" + std::to_string(kMin) + "/stat/relativity/"                     \
      + main_func::extremum::alpha_string + "/")
#define main_func_extremum_kStatDirAlphas                                    \
  (std::string("data/extremum/nature/") + main_func::extremum::kGammaString  \
      + "_" + std::to_string(kMin) + "/stat/")
#endif
}
}

// ******************************************************
#endif // MAIN
#endif // _H_
