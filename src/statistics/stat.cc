#include "stat.h"
#ifdef STAT_STAT

#include "../common/common.h"
using namespace std;
using namespace common;

//**//****************************************************//*
int network::statistics::sum(const char* prename, const char* sufname,
    const int seed_min, const int seed_max, const char* coefficient_string,
    double& sx, double& sx2, size_t& n)
{
  string s, fn0 = prename, fn_full, cs = coefficient_string;
  double x;
  for (int seed = seed_min; seed <= seed_max; ++seed) {
    fn_full = fn0 + to_string(seed) + sufname;
    ifstream is(fn_full.c_str());
    if (!is) {
      ERROR(fn_full);
      continue;
    }
    while (is >> s) {
      if (s == cs) {
        if (is >> x) {
          sx += x;
          sx2 += x * x;
          ++n;
        } else {
          ERROR(fn_full);
        }
        break;
      }
    }
    is.close();
  } // for seed
  return 0;
}

int network::statistics::cal_degArr_sum_alphas(const VNodeType& degArrVal,
    const VNodeType& degArrSize, const double* alphas, VDouble& results)
{
  const size_t degSize = degArrVal.size(), na = results.size();
  for (size_t i = 0; i < degSize; ++i) {
    for (size_t ai = 0; ai < na; ++ai)
      results[ai] += pow(degArrVal[i], alphas[ai]) * degArrSize[i];
  }
  return 0;
}
//**//****************************************************//*
#endif
