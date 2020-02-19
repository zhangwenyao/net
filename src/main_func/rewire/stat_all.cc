#include "stat_all.h"
#ifdef MAIN_REWIRE_STAT_ALL

#include "../../common/common.h"
#include "../../network/networks.h"
#include "../../statistics/stat.h"
using namespace std;
using namespace common;
using namespace network;

//**//****************************************************//*
int main_func::rewire::stat_all(int argc, char** argv)
{
  const string save_prename = kStatDir + "kMin4_0.7",
               sufname = string(".rewire_") + kRhoString + ".params.txt";

#ifdef STAT_PEARSON
  {
    cout << "statistics pearson" << endl;
    string save_fullname = save_prename + ".pearson.txt";
    ofstream os(save_fullname.c_str());
    if (!os) {
      ERROR();
    } else {
      for (int e = kEMin; e <= kEMax; ++e) {
        double sx = 0, sxx = 0, x_mean = 0, x_sigma = 0;
        size_t n = 0;
        cout << "\te\t" << e << endl;
        string prename = kStatDir + "2^" + to_string(e) + "/kMin4_",
               coefficient_string = "--pearson.pearson";
        statistics::sum(prename.c_str(), sufname.c_str(), kSeedMin, kSeedMax,
            coefficient_string.c_str(), sx, sxx, n);
        if (n > 0) {
          x_mean = sx / n;
          x_sigma = sxx / n - x_mean * x_mean;
          x_sigma = x_sigma > 0 ? sqrt(x_sigma) : 0;
          os << e << "\t" << n << "\t" << x_mean << "\t" << x_sigma << endl;
        }
      }
      os.close();
    }
  }
#endif

#ifdef STAT_SPEARMAN
  {
    cout << "statistics spearman" << endl;
    string save_fullname = save_prename + ".spearman.txt";
    ofstream os(save_fullname.c_str());
    if (!os) {
      ERROR();
    } else {
      for (int e = kEMin; e <= kEMax; ++e) {
        double sx = 0, sxx = 0, x_mean = 0, x_sigma = 0;
        size_t n = 0;
        cout << "\te\t" << e << endl;
        string prename = kStatDir + "2^" + to_string(e) + "/kMin4_",
               coefficient_string = "--spearman.spearman";
        statistics::sum(prename.c_str(), sufname.c_str(), kSeedMin, kSeedMax,
            coefficient_string.c_str(), sx, sxx, n);
        if (n > 0) {
          x_mean = sx / n;
          x_sigma = sxx / n - x_mean * x_mean;
          x_sigma = x_sigma > 0 ? sqrt(x_sigma) : 0;
          os << e << "\t" << n << "\t" << x_mean << "\t" << x_sigma << endl;
        }
      }
      os.close();
    }
  }
#endif

#ifdef STAT_RELATIVITY
  {
    cout << "statistics relativity" << endl;
    string save_fullname
        = save_prename + ".relativity" + alpha_string + ".txt";
    ofstream os(save_fullname.c_str());
    if (!os) {
      ERROR();
    } else {
      for (int e = kEMin; e <= kEMax; ++e) {
        double sx = 0, sxx = 0, x_mean = 0, x_sigma = 0;
        size_t n = 0;
        cout << "\te\t" << e << endl;
        string prename = kStatDir + "2^" + to_string(e) + "/kMin4_",
               coefficient_string = "--relativity.relativity";
        statistics::sum(prename.c_str(), sufname.c_str(), kSeedMin, kSeedMax,
            coefficient_string.c_str(), sx, sxx, n);
        if (n > 0) {
          x_mean = sx / n;
          x_sigma = sxx / n - x_mean * x_mean;
          x_sigma = x_sigma > 0 ? sqrt(x_sigma) : 0;
          os << e << "\t" << n << "\t" << x_mean << "\t" << x_sigma << endl;
        }
      }
      os.close();
    }
  }
#endif

  return 0;
}

//**//****************************************************//*
#endif
