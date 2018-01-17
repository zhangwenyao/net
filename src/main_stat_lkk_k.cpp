// g++ -o main.exe *.cpp -O3 -Wall
#include "main.h"
#ifdef MAIN_STAT_LKK_K

#include "common.h"
#include "networks.h"
using namespace std;
//**//**************************************************//**//*
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

  // const double gamma = 2.5;
  // const double alpha = gamma * 0.5 - 1;
  // const double alpha = 1;
  const int seed_max = 100, EMIN = 12, EMAX = 26;
  string dir = "data/extremum/nature";
  ofstream os((dir + "/k.txt").c_str());
  if (!os) {
    ERROR();
    if (os)
      os.close();
    return -1;
  }
  string name, fn;
  stringstream ss;
  NodeType degSize;
  VNodeType val, size;
  VDouble val2;
  VVLinkType lkk;
  for (int e = EMIN; e <= EMAX; ++e) {
    cout << e << endl;
    ss.clear();
    ss.str("");
    ss << dir << "/2^" << e << "/2^" << e;
    name = ss.str();
    double kMean = 0, kErr = 0;
    double k2Mean = 0, k2Err = 0;
    for (int seed = 1; seed <= seed_max; ++seed) {
      ss.clear();
      ss.str("");
      ss << name << "_" << seed;
      fn = ss.str();

      val.clear();
      common_read1_0((fn + ".degArrVal.txt").c_str(), val);
      degSize = val.size();

      size.resize(degSize);
      common_read1((fn + ".degArrSize.txt").c_str(), size);
      LinkType L;
      degArr_2_linkSize(L, val, size);
      const LinkType L2 = L * 2;

      double ei = func_0(val, size, 1) / L2;
      kMean += ei;
      kErr += ei * ei;

      double ei2 = func_0(val, size, 1 * 2) / L2;
      k2Mean += ei2;
      k2Err += ei2 * ei2;

      // degArrVal_2_deg2ArrVal(val2, size, val, L);
      // double ei = func2_0(val2, val, size, 1) / L2;
      // double ei2 = func2_0(val2, val, size, 2) / L2;

      //// max
      // lkk.resize(degSize);
      // for (size_t i = 0; i < degSize; ++i)
      // lkk[i].assign(i + 1, 0);
      // read_lkk_3((fn + ".Max.lkk3.txt").c_str(), lkk, degSize, 1);
      // double eij = func(lkk, val, alpha) / L;
      // double rho = (eij - ei * ei) / (ei2 - ei * ei);
      //// cout << "max\t" << ei << "\t" << ei2 << "\t" << eij << "\t" << rho
      ///<<
      // endl;
      // maxMean += rho;
      // maxErr += rho * rho;

      //// min
      // lkk.resize(degSize);
      // for (size_t i = 0; i < degSize; ++i)
      // lkk[i].assign(i + 1, 0);
      // read_lkk_3((fn + ".Min.lkk3.txt").c_str(), lkk);
      // eij = func(lkk, val, alpha) / L;
      // rho = (eij - ei * ei) / (ei2 - ei * ei);
      //// cout << "min\t" << ei << "\t" << ei2 << "\t" << eij << "\t" << rho
      ///<<
      //// endl;
      // minMean += rho;
      // minErr += rho * rho;
    }
    os << (1 << e);

    kMean /= seed_max;
    kErr = sqrt(kErr / seed_max - kMean * kMean);
    os << "\t" << kMean << "\t" << kErr;

    k2Mean /= seed_max;
    k2Err = sqrt(k2Err / seed_max - k2Mean * k2Mean);
    os << "\t" << k2Mean << "\t" << k2Err;

    os << "\n";
  }

  os.close();

  SHOW_TIME(cout); // 显示系统时间
  return 0;
}

//**//**************************************************//**//*
#endif
