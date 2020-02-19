#include "stat_all.h"
#ifdef MAIN_EXTREMUM_STAT_ALL

#include "../../common/common.h"
#include "../../model/extremum/extremum.h"
#include "../../network/networks.h"
#include "../../statistics/stat.h"
using namespace std;
using namespace common;
using namespace network;

//**//****************************************************//*
int main_func::extremum::stat_all(int argc, char** argv)
{
  const string save_prename = kStatDir + "kMin4";

#ifdef STAT_PEARSON
#ifdef MAIN_EXTREMUM_STAT_MINIMAL
  {
    cout << "statistics pearson minimal" << endl;
    string save_fullname = save_prename + ".pearson.minimal.txt";
    ofstream os(save_fullname.c_str());
    if (!os) {
      ERROR();
    } else {
      for (int e = kEMin; e <= kEMax; ++e) {
        double sx = 0, sxx = 0, x_mean = 0, x_sigma = 0;
        size_t n = 0;
        cout << "\te\t" << e << endl;
        string prename = kStatDir + "2^" + to_string(e) + "/kMin4_",
               sufname = ".Min.params.txt",
               coefficient_string = "--pearson.pearson";
        statistics::sum(prename.c_str(), sufname.c_str(), 1, 100,
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
#ifdef MAIN_EXTREMUM_STAT_MAXIMAL
  {
    cout << "statistics pearson maximal" << endl;
    string save_fullname = save_prename + ".pearson.maximal.txt";
    ofstream os(save_fullname.c_str());
    if (!os) {
      ERROR();
    } else {
      for (int e = kEMin; e <= kEMax; ++e) {
        double sx = 0, sxx = 0, x_mean = 0, x_sigma = 0;
        size_t n = 0;
        cout << "\te\t" << e << endl;
        string prename = kStatDir + "2^" + to_string(e) + "/kMin4_",
               sufname = ".Max.params.txt",
               coefficient_string = "--pearson.pearson";
        statistics::sum(prename.c_str(), sufname.c_str(), 1, 100,
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
#endif

#ifdef STAT_SPEARMAN
#ifdef MAIN_EXTREMUM_STAT_MINIMAL
  {
    cout << "statistics spearman minimal" << endl;
    string save_fullname = save_prename + ".spearman.minimal.txt";
    ofstream os(save_fullname.c_str());
    if (!os) {
      ERROR();
    } else {
      for (int e = kEMin; e <= kEMax; ++e) {
        double sx = 0, sxx = 0, x_mean = 0, x_sigma = 0;
        size_t n = 0;
        cout << "\te\t" << e << endl;
        string prename = kStatDir + "2^" + to_string(e) + "/kMin4_",
               sufname = ".Min.params.txt",
               coefficient_string = "--spearman.spearman";
        statistics::sum(prename.c_str(), sufname.c_str(), 1, 100,
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
#ifdef MAIN_EXTREMUM_STAT_MAXIMAL
  {
    cout << "statistics spearman maximal" << endl;
    string save_fullname = save_prename + ".spearman.maximal.txt";
    ofstream os(save_fullname.c_str());
    if (!os) {
      ERROR();
    } else {
      for (int e = kEMin; e <= kEMax; ++e) {
        double sx = 0, sxx = 0, x_mean = 0, x_sigma = 0;
        size_t n = 0;
        cout << "\te\t" << e << endl;
        string prename = kStatDir + "2^" + to_string(e) + "/kMin4_",
               sufname = ".Max.params.txt",
               coefficient_string = "--spearman.spearman";
        statistics::sum(prename.c_str(), sufname.c_str(), 1, 100,
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
#endif

#ifdef STAT_RELATIVITY
#ifdef MAIN_EXTREMUM_STAT_MINIMAL
  {
    cout << "statistics relativity minimal" << endl;
    string save_fullname
        = save_prename + ".relativity" + alpha_string + ".minimal.txt";
    ofstream os(save_fullname.c_str());
    if (!os) {
      ERROR();
    } else {
      for (int e = kEMin; e <= kEMax; ++e) {
        double sx = 0, sxx = 0, x_mean = 0, x_sigma = 0;
        size_t n = 0;
        cout << "\te\t" << e << endl;
        string prename = kStatDir + "2^" + to_string(e) + "/kMin4_",
               sufname = ".Min.params.txt",
               coefficient_string = "--relativity.relativity";
        statistics::sum(prename.c_str(), sufname.c_str(), 1, 100,
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
#ifdef MAIN_EXTREMUM_STAT_MAXIMAL
  {
    cout << "statistics relativity maximal" << endl;
    string save_fullname
        = save_prename + ".relativity" + alpha_string + ".maximal.txt";
    ofstream os(save_fullname.c_str());
    if (!os) {
      ERROR();
    } else {
      for (int e = kEMin; e <= kEMax; ++e) {
        double sx = 0, sxx = 0, x_mean = 0, x_sigma = 0;
        size_t n = 0;
        cout << "\te\t" << e << endl;
        string prename = kStatDir + "2^" + to_string(e) + "/kMin4_",
               sufname = ".Max.params.txt",
               coefficient_string = "--relativity.relativity";
        statistics::sum(prename.c_str(), sufname.c_str(), 1, 100,
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
#endif

  return 0;
}

//**//****************************************************//*
#endif
