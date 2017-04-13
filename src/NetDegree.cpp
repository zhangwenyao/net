#include "NetDegree.h"
#ifdef NET_DEGREE

#include <cmath>
using namespace std;

//**//*****************************************************************//*
// 生成度分布概率
int poisson_cal_degArr(const double p, VNodeType& degArrVal,
                       VDouble& degArrProb, const NodeType kMin,
                       const NodeType kMax, NodeType& nodeSize) {
  const NodeType kSize = kMax - kMin + 1;
  degArrVal.resize(kSize);
  degArrProb.resize(kSize);
  double maxProb = 0.;
  for (NodeType k = kMin, i = 0; i < kSize; k++, i++) {
    degArrVal[i] = k;
    if (k <= 0) {
      degArrProb[i] = 0.;
      continue;
    }
    degArrProb[i] = pow(p, k) * pow(1 - p, nodeSize - 1 - k);
    for (NodeType j = 1; j <= k; j++)
      degArrProb[i] *= (double)(nodeSize - j) / j;
    if (degArrProb[i] > maxProb) maxProb = degArrProb[i];
  }
  for (NodeType i = 0; i < kSize; i++) degArrProb[i] /= maxProb;
  return 0;
}

//**//*****************************************************************//*
// 生成度分布概率
int power_cal_degArr(const double r, VNodeType& degArrVal, VDouble& degArrProb,
                     const NodeType kMin, const NodeType kMax) {
  const NodeType kSize = kMax - kMin + 1;
  degArrVal.resize(kSize);
  degArrProb.resize(kSize);
  double maxProb = 0.;
  for (NodeType k = kMin, i = 0; i < kSize; k++, i++) {
    degArrVal[i] = k;
    if (k <= 0) {
      degArrProb[i] = 0.;
      continue;
    }
    degArrProb[i] = pow(k, -r);  // 按最大概率点归一，提高舍选的概率
    if (degArrProb[i] > maxProb) maxProb = degArrProb[i];
  }
  for (NodeType i = 0; i < kSize; i++) degArrProb[i] /= maxProb;
  return 0;
}

//**//*****************************************************************//*
#endif  // NET_DEGREE
