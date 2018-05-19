// g++ -o main.exe *.cpp -O3 -Wall
#include "main.h"
#ifdef MAIN_STAT_LKK_EXTREMUM

#include "common.h"
#include "networks.h"
using namespace std;
// *************************************************//*****
double func_0(
    const VNodeType degArrVal, const VNodeType& degArrSize, const double a)
{
  double sum = 0;
  for (size_t i = 0; i < degArrVal.size(); ++i) {
    const double ki = degArrVal[i], si = degArrSize[i];
    sum += pow(ki, a + 1) * si;
  }
  return sum;
}

double func(const VVLinkType& lkk, const VNodeType degArrVal, const double a)
{
  double sum = 0;
  for (size_t i = 0; i < lkk.size(); ++i) {
    const double ki = degArrVal[i];
    for (size_t j = 0; j < lkk[i].size(); ++j) {
      const double kj = degArrVal[j];
      sum += pow(ki, a) * pow(kj, a) * lkk[i][j];
    }
  }
  return sum;
}

double func2_0(const VDouble degArrVal2, const VNodeType& degArrVal,
    const VNodeType& degArrSize, const double a)
{
  double sum = 0;
  for (size_t i = 0; i < degArrVal.size(); ++i) {
    const double k2i = degArrVal2[i], ki = degArrVal[i], si = degArrSize[i];
    sum += pow(k2i, a) * ki * si;
  }
  return sum;
}

double func2(const VVLinkType& lkk, const VDouble degArrVal2, const double a)
{
  double sum = 0;
  for (size_t i = 0; i < lkk.size(); ++i) {
    const double k2i = degArrVal2[i];
    for (size_t j = 0; j < lkk[i].size(); ++j) {
      const double k2j = degArrVal2[j];
      sum += pow(k2i, a) * pow(k2j, a) * lkk[i][j];
    }
  }
  return sum;
}

int main(int argc, char** argv)
{
  SHOW_TIME(cout); // 显示系统时间
  const double gamma = 2.5;
  //const int N = 11;
  //string names[N] = { "2", "r-1", "1", "r-2", "(r-2)d1.5", "(r-2)d2",
    //"(r-2)d3", "(2-r)d2", "2-r", "1.5-r", "1-r" };
  //double alphas[N] = { 2, gamma - 1, 1, gamma - 2, (gamma - 2) / 1.5,
    //(gamma - 2) / 2, (gamma - 2) / 3, (2 - gamma) / 2, 2 - gamma, 1.5 - gamma,
    //1 - gamma };
  const int N = 4;
  string names[N] ={"2(r-2)", "1.5(r-2)", "1.5(2-r)", "2(2-r)"};
  double alphas[N] = {2*(gamma-2), 1.5*(gamma-2), 1.5*(2-gamma), 2*(2-gamma)};
  const string dirDeg = "/media/yao/Server1T/net/data/power/nature",
               dirLkk = "/media/yao/Server1T/net/data/extremum/nature",
               dirSave = "/media/yao/Server1T/net/data/extremum/nature";
  // const string dirDeg = "data/power/nature", dirLkk =
  // "data/extremum/nature",
  // dirSave = "data/extremum/nature";
  // const int seed_max = 300, EMIN = 12, EMAX = 29;
  const int seed_max = 300, EMIN = 12, EMAX = 29;
  ofstream osMax[N], osMin[N];
  for (int n = 0; n < N; ++n) {
    osMax[n].open((dirSave + "/max_" + names[n] + ".txt").c_str());
    osMin[n].open((dirSave + "/min_" + names[n] + ".txt").c_str());
    if (!osMax[n] || !osMin[n]) {
      ERROR();
      return -1;
    }
  }
  const NodeType kMin = 4;
  string fn;
  char name[200];
  NodeType degSize;
  VNodeType val, size;
  VDouble val2;
  for (int e = EMIN; e <= EMAX; ++e) {
    SHOW_TIME(cout); // 显示系统时间
    cout << e << endl;
    double maxMean[N] = { 0 }, maxErr[N] = { 0 }, minMean[N] = { 0 },
           minErr[N] = { 0 };
    for (int seed = 1; seed <= seed_max; ++seed) {
      // if (e % 20 == 0)
      // cout << "\t" << seed << endl;

      sprintf(name, "%s/2^%d/%d_%g_%d", dirDeg.c_str(), e, kMin, gamma, seed);
      fn = name;
      val.clear();
      common_read1_0((fn + ".degArrVal.txt").c_str(), val);
      degSize = val.size();
      size.resize(degSize);
      common_read1((fn + ".degArrSize.txt").c_str(), size);
      LinkType L2 = 0;
      for (NodeType i = 0; i < degSize; ++i)
        L2 += (LinkType)val[i] * size[i];
      const LinkType L = L2 / 2;
      double ei[N] = { 0 }, ei2[N] = { 0 };
      for (NodeType i = 0; i < degSize; ++i) {
        LinkType s = (LinkType)val[i] * size[i];
        for (int n = 0; n < N; ++n) {
          double t = pow(val[i], alphas[n]);
          ei[n] += t * s;
          ei2[n] += t * t * s;
        }
      }
      // degArrVal_2_deg2ArrVal(val2, size, val, L);
      // double ei = func2_0(val2, val, size, 1) / L2;
      // double ei2 = func2_0(val2, val, size, 2) / L2;

      // max
      sprintf(
          name, "%s/2^%d/%d_%g_max_%d", dirLkk.c_str(), e, kMin, gamma, seed);
      fn = name;
      ifstream is((fn + ".lkk3.txt").c_str());
      if (!is) {
        ERROR();
        return -1;
      }
      LinkType l;
      double eijMax[N] = { 0 };
      for (NodeType i, j; is >> i >> j >> l;) {
        for (int n = 0; n < N; ++n) {
          eijMax[n] += pow((double)val[i] * val[j], alphas[n]) * l;
        }
      }
      is.close();
      for (int n = 0; n < N; ++n) {
        ei[n] /= L2;
        ei2[n] /= L2;
        eijMax[n] /= L;
        double rho = (eijMax[n] - ei[n] * ei[n]) / (ei2[n] - ei[n] * ei[n]);
        maxMean[n] += rho;
        maxErr[n] += rho * rho;
      }

      // min
      sprintf(
          name, "%s/2^%d/%d_%g_min_%d", dirLkk.c_str(), e, kMin, gamma, seed);
      fn = name;
      is.open((fn + ".lkk3.txt").c_str());
      if (!is) {
        ERROR();
        return -1;
      }
      double eijMin[N] = { 0 };
      for (NodeType i, j; is >> i >> j >> l;) {
        for (int n = 0; n < N; ++n) {
          eijMin[n] += pow((double)val[i] * val[j], alphas[n]) * l;
        }
      }
      is.close();
      for (int n = 0; n < N; ++n) {
        eijMin[n] /= L;
        double rho = (eijMin[n] - ei[n] * ei[n]) / (ei2[n] - ei[n] * ei[n]);
        minMean[n] += rho;
        minErr[n] += rho * rho;
      }
    }

    for (int n = 0; n < N; ++n) {
      maxMean[n] /= seed_max;
      maxErr[n] = sqrt(maxErr[n] / seed_max - maxMean[n] * maxMean[n]);
      osMax[n] << (1 << e) << '\t' << maxMean[n] << '\t' << maxErr[n] << '\t'
               << seed_max << '\n';
      cout << names[n] << '\t' << (1 << e) << '\t' << maxMean[n] << '\t'
           << maxErr[n] << '\t' << seed_max << '\n';

      minMean[n] /= seed_max;
      minErr[n] = sqrt(minErr[n] / seed_max - minMean[n] * minMean[n]);
      osMin[n] << (1 << e) << '\t' << minMean[n] << '\t' << minErr[n] << '\t'
               << seed_max << '\n';
      cout << names[n] << '\t' << (1 << e) << '\t' << minMean[n] << '\t'
           << minErr[n] << '\t' << seed_max << '\n';
    }
  }

  for (int n = 0; n < N; ++n) {
    osMax[n].close();
    osMin[n].close();
  }

  SHOW_TIME(cout); // 显示系统时间
  return 0;
}

// *************************************************//*****
#endif
