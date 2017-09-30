// g++ -o main.exe *.cpp -O3 -Wall
#include "net.h"
#ifdef NET_EXTREMUM

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
    sum += pow(ki, a) * si;
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

  char name[200];
  const int seed_max = 300;
  ofstream po("data/extremum/pearson.txt");
  ofstream so("data/extremum/spearman2.txt");
  ofstream to("data/extremum/spearman.txt");
  for (int e = 5; e <= 29; ++e) {
    // for (int e = 5; e <= 29; ++e) {
    double pmean = 0, perr = 0;
    double smean = 0, serr = 0;
    double tmean = 0, terr = 0;
    sprintf(name, "data/extremum/2^%d/2^%d", e, e);
    for (int seed = 1; seed <= seed_max; ++seed) {
      SHOW_TIME(cout); // 显示系统时间
      Networks net;
      net.saveName = net.readName = name;
      net.nodeSize = 1 << e;        // 节点数
      net.degree.power_gamma = 2.5; // 度分布幂律分布的幂指数
      net.kMin = 4;                 // 最小度
      net.kMax = net.kMin + sqrt(net.nodeSize) - 1; // 最大度
      net.seed = seed;

      string fn;
      stringstream ss;
      ss.clear();
      ss << seed;
      fn = net.saveName + '_' + ss.str();
      net.read_params((fn + ".params.txt").c_str());
      common_read1_0((fn + ".degArrVal.txt").c_str(), net.degArrVal);
      common_read1_0((fn + ".degArrSize.txt").c_str(), net.degArrSize);
      const NodeType degSize = net.degArrVal.size();
      net.lkk.resize(degSize);
      for (size_t i = 0; i < degSize; ++i)
        net.lkk[i].resize(i + 1, 0);
      read_lkk_3((fn + ".lkk3.txt").c_str(), net.lkk);
      degArrVal_2_deg2ArrVal(net.spearman.deg2ArrVal, net.degArrSize,
          net.degArrVal, net.linkSize, net.dirFlag);

      const LinkType L = net.linkSize, L2 = L * 2;
      double ei = func_0(net.degArrVal, net.degArrSize, 2) / L2;
      double ei2 = func_0(net.degArrVal, net.degArrSize, 3) / L2;
      double eij = func(net.lkk, net.degArrVal, 1) / L;
      double p = (eij - ei * ei) / (ei2 - ei * ei);
      cout << ei << "\t" << ei2 << "\t" << eij << "\t" << p << endl;
      pmean += p;
      perr += p * p;

      double si
          = func_0(net.degArrVal, net.degArrSize, 3 - net.degree.power_gamma)
          / L2;
      double si2 = func_0(net.degArrVal, net.degArrSize,
                       5 - 2 * net.degree.power_gamma)
          / L2;
      double sij
          = func(net.lkk, net.degArrVal, 2 - net.degree.power_gamma) / L;
      double s = (sij - si * si) / (si2 - si * si);
      cout << si << "\t" << si2 << "\t" << sij << "\t" << s << endl;
      smean += s;
      serr += s * s;

      double ti
          = func2_0(net.spearman.deg2ArrVal, net.degArrVal, net.degArrSize, 1)
          / L2;
      double ti2
          = func2_0(net.spearman.deg2ArrVal, net.degArrVal, net.degArrSize, 2)
          / L2;
      double tij = func2(net.lkk, net.spearman.deg2ArrVal, 1) / L;
      double t = (tij - ti * ti) / (ti2 - ti * ti);
      cout << ti << "\t" << ti2 << "\t" << tij << "\t" << t << endl;
      tmean += t;
      terr += t * t;
    }
    pmean /= seed_max;
    perr = sqrt(perr / seed_max - pmean * pmean);
    cout << pmean << "\t" << perr << endl;
    po << pmean << "\t" << perr << "\n";

    smean /= seed_max;
    serr = sqrt(serr / seed_max - smean * smean);
    cout << smean << "\t" << serr << endl;
    so << smean << "\t" << serr << "\n";

    tmean /= seed_max;
    terr = sqrt(terr / seed_max - tmean * tmean);
    cout << tmean << "\t" << terr << endl;
    to << tmean << "\t" << terr << "\n";
  }
  po.close();
  so.close();

  SHOW_TIME(cout); // 显示系统时间
  return 0;
}
//**//**************************************************//**//*
#endif
