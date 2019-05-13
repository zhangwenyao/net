#ifndef STATISTICS__STAT_H_
#define STATISTICS__STAT_H_

namespace network {
namespace statistics {
  // ******************************************************
  int sum(const char* prename, const char* sufname, const int seed_min,
      const int seed_max, const char* coefficient_string, double& sx,
      double& sx2, unsigned& n);

  // ******************************************************
}
}
#endif // _H_
