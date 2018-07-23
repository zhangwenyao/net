#include "NetDegree.h"
#ifdef NET_DEGREE

#include "common.h"
#include <cmath>
#include <random>
using namespace std;

// *******************************************************************
// 生成度分布概率
int poisson_cal_degArrProb(const double p, VNodeType& degArrVal,
    VDouble& degArrProb, const NodeType kMin, const NodeType kMax,
    NodeType& nodeSize)
{
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
    if (degArrProb[i] > maxProb)
      maxProb = degArrProb[i];
  }
  // 按最大概率点归一，提高舍选的概率
  for (NodeType i = 0; i < kSize; i++)
    degArrProb[i] /= maxProb;
  return 0;
}

// *******************************************************************
// 生成度分布概率
int power_cal_degArrProb(const double r, VNodeType& degArrVal,
    VDouble& degArrProb, const NodeType kMin, const NodeType kMax)
{
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
    degArrProb[i] = pow(k, -r);
    if (degArrProb[i] > maxProb)
      maxProb = degArrProb[i];
  }
  // 按最大概率点归一，提高舍选的概率
  for (NodeType i = 0; i < kSize; i++)
    degArrProb[i] /= maxProb;
  return 0;
}

// 生成度分布累计序列
int power_cal_deg_arr(VNodeType& degArrSize, const VNodeType& degArrVal,
    const VDouble& degArrProb, NodeType nodeSize)
{
  const NodeType kSize = degArrVal.size();
  if (degArrProb.size() != kSize) {
    ERROR();
    return -1;
  }
  degArrSize.assign(kSize, 0);
  double probSum = 0.;
  for (NodeType i = 0; i < kSize; i++) {
    probSum += degArrProb[i];
  }
  for (NodeType i = 0; nodeSize > 0 && probSum > 0 && i < kSize; i++) {
    binomial_distribution<NodeType> bd(nodeSize, degArrProb[i] / probSum);
    nodeSize -= degArrSize[i] = bd(rand2);
    probSum -= degArrProb[i];
  }
  return 0;
}

// ********************************************************
int PowerLaw_NatureCutoff(NodeType& kMax, const NodeType nodeSize,
    const NodeType kMin, const double gamma)
{
  if (kMin < 1 || nodeSize <= kMin || gamma <= 1) {
    ERROR();
    return -1;
  }
  kMax = (kMin - 0.5) * pow((double)nodeSize, 1 / (gamma - 1));
  if (kMax > nodeSize - 1)
    kMax = nodeSize - 1;
  if (kMax < kMin) {
    ERROR();
    return -1;
  }
  return 0;
}

// *******************************************************************
#endif // NET_DEGREE
