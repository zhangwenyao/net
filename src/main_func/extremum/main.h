#ifndef MAIN__EXTREMUM__MAIN_H_
#define MAIN__EXTREMUM__MAIN_H_
#include "../../main.h"
#ifdef MAIN_EXTREMUM

//#define MAIN_EXTREMUM_NEW_DEG_ARR
#define MAIN_EXTREMUM_NEW_MINIMAL
//#define MAIN_EXTREMUM_NEW_MAXIMAL
//#define MAIN_EXTREMUM_STAT_MINIMAL
//#define MAIN_EXTREMUM_STAT_MAXIMAL
//#define MAIN_EXTREMUM_STAT_ALL

#include <string>
// ******************************************************
namespace main_func {
int main_extremum(int argc, char** argv);
namespace extremum {
  // const double kGamma = 2.7;
  // const std::string kDataDir = "data/extremum/nature/2.7/data/";
  // const std::string kStatDir = "data/extremum/nature/2.7/stat/";

  const double kGamma = 2.5;
  const std::string kDataDir
      = "/media/yao/Server1T/net/data/extremum/nature/2.5_4/";
  const std::string kStatDir
      = "/media/yao/Server1T/net/data/extremum/nature/2.5_4/stat/";

  const int kEMin = 35, kEMax = 60, kSeedMin = 1, kSeedMax = 100;
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
