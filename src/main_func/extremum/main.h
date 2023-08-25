#ifndef MAIN_FUNC__EXTREMUM__MAIN_H_
#define MAIN_FUNC__EXTREMUM__MAIN_H_
#include "../../main.h"
#ifdef MAIN_EXTREMUM

#include "../../common/common.h"
#include "../../network/net.h"
#include <string>
#define MAIN_FUNC main_func::main_extremum

// #define MAIN_EXTREMUM_NEW_DEG_ARR

// #define MAIN_EXTREMUM_NONE
// #define MAIN_EXTREMUM_NEW_MAXIMAL
// #define MAIN_EXTREMUM_NEW_MINIMAL
// #define MAIN_EXTREMUM_STAT_MAXIMAL
// #define MAIN_EXTREMUM_STAT_MINIMAL
// #define MAIN_EXTREMUM_STAT_ALL
// #define MAIN_EXTREMUM_STAT_ALL_COLLECT

#define MAIN_EXTREMUM_ALPHAS
// #define MAIN_EXTREMUM_ALPHAS11
// #define MAIN_EXTREMUM_ALPHAS16
#define MAIN_EXTREMUM_ALPHAS20
// #define MAIN_EXTREMUM_ALPHAS_STAT_MAXIMAL
// #define MAIN_EXTREMUM_ALPHAS_STAT_MINIMAL
#define MAIN_EXTREMUM_ALPHAS_STAT_MAXIMAL_COLLECT
#define MAIN_EXTREMUM_ALPHAS_STAT_MINIMAL_COLLECT

// ******************************************************
namespace main_func {
int main_extremum(int argc, char** argv);
namespace extremum {
#ifndef KEXTREMUM_GAMMA
  constexpr double kGamma = 2.3;
  const std::string kGammaString = "2.3";
#else
  constexpr double kGamma = KEXTREMUM_GAMMA;
  const std::string kGammaString = TOSTRING(KEXTREMUM_GAMMA);
#endif
#ifndef KEXTREMUM_KMIN
  constexpr int kMin = 4;
#else
  constexpr int kMin = KEXTREMUM_KMIN;
#endif
#ifndef KEXTREMUM_EMIN
  constexpr int kEMin = 10;
#else
  constexpr int kEMin = KEXTREMUM_EMIN;
#endif
#ifndef KEXTREMUM_EMAX
  constexpr int kEMax = 60;
#else
  constexpr int kEMax = KEXTREMUM_EMAX;
#endif
#ifndef KEXTREMUM_SEEDMIN
  constexpr int kSeedMin = 1;
#else
  constexpr int kSeedMin = KEXTREMUM_SEEDMIN;
#endif
#ifndef KEXTREMUM_SEEDMAX
  constexpr int kSeedMax = 300;
#else
  constexpr int kSeedMax = KEXTREMUM_SEEDMAX;
#endif
  // const std::string kDataDir = std::string("data/extremum/nature/")
  //+ kGammaString + "_" + to_string(kMin) + "/data/";
  const std::string kDataDir
      //= std::string("/media/yao/tsb1T/net/data/extremum/nature/")
      = std::string("/media/yao/Samsung_T5/net/data/extremum/nature/")
      + kGammaString + "_" + std::to_string(kMin) + "/";
#ifndef STAT_RELATIVITY
  const std::string kStatDir = std::string("data/extremum/nature/")
      + kGammaString + "_" + std::to_string(kMin) + "/stat/pearson_spearman/";
#else
  constexpr double kGamma_2 = kGamma - 2.0;

#ifdef MAIN_EXTREMUM_ALPHAS
#if defined(MAIN_EXTREMUM_ALPHAS11)
  const double relativity_alphas[] = { 1.0, 2.0, kGamma_2 * 2,
    kGamma_2 * 3 / 2, kGamma_2, kGamma_2 * 3 / 4, kGamma_2 / 2, kGamma_2 / 4,
    -kGamma_2 / 2, -kGamma_2, -kGamma_2 * 2 };
  const std::string alpha_strings[] = { "C1", "C2", "2", "3d2", "1", "3d4",
    "1d2", "1d4", "-1d2", "-1", "-2" };
#elif defined(MAIN_EXTREMUM_ALPHAS16)
  const double relativity_alphas[] = { 1.0, 2.0, -1.0, -2.0, kGamma_2 * 2,
    kGamma_2 * 3 / 2, kGamma_2 * 1, kGamma_2 * 3 / 4, kGamma_2 * 1 / 2,
    kGamma_2 * 1 / 4, kGamma_2 * -1 / 4, kGamma_2 * -1 / 2, kGamma_2 * -1,
    kGamma_2 * -2, kGamma_2 * -3, kGamma_2 * -4 };
  const std::string alpha_strings[] = { "C1", "C2", "C-1", "C-2", "2", "3d2",
    "1", "3d4", "1d2", "1d4", "-1d4", "-1d2", "-1", "-2", "-3", "-4" };
#else // defined(MAIN_EXTREMUM_ALPHAS20)
  const double relativity_alphas[] = { 1.0, 2.0, -1.0, -2.0, kGamma_2 * 4,
    kGamma_2 * 3, kGamma_2 * 2, kGamma_2 * 3 / 2, kGamma_2 * 1,
    kGamma_2 * 3 / 4, kGamma_2 * 1 / 2, kGamma_2 * 1 / 4, kGamma_2 * -1 / 4,
    kGamma_2 * -1 / 2, kGamma_2 * -3 / 4, kGamma_2 * -1, kGamma_2 * -3 / 2,
    kGamma_2 * -2, kGamma_2 * -3, kGamma_2 * -4 };
  const std::string alpha_strings[]
      = { "C1", "C2", "C-1", "C-2", "4", "3", "2", "3d2", "1", "3d4", "1d2",
          "1d4", "-1d4", "-1d2", "-3d4", "-1", "-3d2", "-2", "-3", "-4" };
#endif
#endif

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
