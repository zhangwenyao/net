#ifndef MAIN__EXTREMUM__MAIN_H_
#define MAIN__EXTREMUM__MAIN_H_
#include "../../main.h"
#ifdef MAIN_EXTREMUM

//#define MAIN_EXTREMUM_NEW_DEG_ARR
//#define MAIN_EXTREMUM_NEW_MINIMAL
//#define MAIN_EXTREMUM_NEW_MAXIMAL
#define MAIN_EXTREMUM_STAT_MINIMAL
#define MAIN_EXTREMUM_STAT_MAXIMAL
#define MAIN_EXTREMUM_STAT_ALL
//#define MAIN_EXTREMUM_STAT_ALL_COLLECT

#include <string>
// ******************************************************
namespace main_func {
int main_extremum(int argc, char** argv);
namespace extremum {
  const int kEMin = 12, kEMax = 30, kSeedMin = 1, kSeedMax = 100;
  const double kGamma = 2.5;
  const std::string kGammaString = "2.5";
  const std::string kDataDir
      = std::string("/media/yao/Server1T/net/data/extremum/nature/")
      + kGammaString + "_4/";
  //= std::string("data/extremum/nature/") + kGammaString + "_4/data/";
  const std::string kStatDir = std::string("data/extremum/nature/")
      + kGammaString + "_4/stat/relativity/";
  const double relativity_alpha = -0.5;
  const std::string alpha_string = "-0.5";
}
}

// ******************************************************
#ifdef MAIN_EXTREMUM_NEW_DEG_ARR
#include "new_deg_arr.h"
#endif

#ifdef MAIN_EXTREMUM_NEW_MINIMAL
#include "new_minimal.h"
#endif

#ifdef MAIN_EXTREMUM_NEW_MAXIMAL
#include "new_maximal.h"
#endif

#ifdef MAIN_EXTREMUM_STAT_MINIMAL
#include "stat_minimal.h"
#endif

#ifdef MAIN_EXTREMUM_STAT_MAXIMAL
#include "stat_maximal.h"
#endif

#ifdef MAIN_EXTREMUM_STAT_ALL
#include "stat_all.h"
#endif

// ******************************************************
#endif // MAIN
#endif // _H_
