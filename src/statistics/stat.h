#ifndef STATISTICS__STAT_H_
#define STATISTICS__STAT_H_
#include "../network/net.h"
#ifdef STAT_STAT

namespace network {
namespace statistics {
  // ******************************************************
  int sum(const char* prename, const char* sufname, const int seed_min,
      const int seed_max, const char* coefficient_string, double& sx,
      double& sx2, size_t& n);

  int cal_degArr_sum_alphas(const VNodeType& degArrVal,
      const VNodeType& degArrSize, const double* alphas, VDouble& results);

  // ******************************************************
}
}
#endif
#endif // _H_
