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

int network::statistics::sums_relativity(const char* prename,
    const char* sufname, const int seed_min, const int seed_max, double* sx,
    double* sx2, size_t& n, const size_t len)
{
  for (int seed = seed_min; seed <= seed_max; ++seed) {
    string fn_full = prename + to_string(seed) + sufname;
    VVDouble results(3, VDouble(len, 0));
    if (0 == read2(fn_full.c_str(), results)) {
      ++n;
      for (size_t i = 0; i < len; ++i) {
        double r2 = results[1][i];
        r2 *= r2;
        double x = (results[0][i] - r2) / (results[2][i] - r2);
        sx[i] += x;
        sx2[i] += x * x;
      }
    }
  } // for seed
  return 0;
}

int network::statistics::sums_relativity_bc(const char* prename,
    const char* sufname, const int seed_min, const int seed_max, double* sxa,
    double* sx2a, double* sxb, double* sx2b, double* sxc, double* sx2c,
    size_t& n, const size_t len)
{
  for (int seed = seed_min; seed <= seed_max; ++seed) {
    string fn_full = prename + to_string(seed) + sufname;
    VVDouble results(3, VDouble(len, 0));
    if (0 == read2(fn_full.c_str(), results)) {
      ++n;
      for (size_t i = 0; i < len; ++i) {
        double a = results[0][i], b = results[1][i], c = results[2][i];
        sxa[i] += a;
        sx2a[i] += a * a;
        sxb[i] += b;
        sx2b[i] += b * b;
        sxc[i] += c;
        sx2c[i] += c * c;
      }
    }
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
