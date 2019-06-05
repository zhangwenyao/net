#include "stat.h"

#include "../common/common.h"
using namespace std;
using namespace common;

//**//****************************************************//*
int network::statistics::sum(const char* prename, const char* sufname,
    const int seed_min, const int seed_max, const char* coefficient_string,
    double& sx, double& sx2, unsigned& n)
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
          ERROR();
        }
        break;
      }
    }
    is.close();
  } // for seed
  return 0;
}

//**//****************************************************//*
