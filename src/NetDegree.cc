#include "NetDegree.h"
#ifdef NET_DEGREE

#include "common.h"
#include <cmath>
#include <random>
using namespace std;

// *******************************************************************
// 生成度分布概率
int net_degree::poisson_cal_degArrProb(const double p, VNodeType& degArrVal,
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
int net_degree::power_cal_degArrProb(const double r, VNodeType& degArrVal,
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
int net_degree::power_cal_deg_arr(VNodeType& degArrSize,
    const VNodeType& degArrVal, const VDouble& degArrProb, NodeType nodeSize)
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

// 生成度分布累计序列
int net_degree::power_cal_deg_arr_func(const NodeType nodeSize,
    const NodeType kMin, const NodeType kMax,
    std::function<double(const NodeType)> prob_func, const double degProbSum,
    VNodeType& degArrVal, VNodeType& degArrSize)
{
  degArrVal.clear();
  degArrSize.clear();
  if (kMin < 1 || kMin > kMax || nodeSize < 2) {
    ERROR();
    return -1;
  }
  double probSum = degProbSum;
  for (NodeType k = kMin, size = nodeSize;
       size > 0 && probSum > 0 && k <= kMax; ++k) {
    double prob = prob_func(k);
    binomial_distribution<NodeType> bd(size, prob / probSum);
    NodeType n = bd(rand2);
    if (k == kMin && n <= 0)
      n = 1;
    if (size == 1) {
      k = kMax;
      n = size;
      probSum = 0;
    }
    if (n == size && k < kMax)
      --n;
    if (n > 0) {
      degArrVal.push_back(k);
      degArrSize.push_back(n);
      size -= n;
    }
    probSum -= prob;
  }
  if (degArrVal.size() <= 0 || degArrVal.front() != kMin
      || degArrVal.back() != kMax)
    ERROR();
  return 0;
}

int net_degree::fix_degArr_linkSize_lkk3_fast(
    const VNodeType& degArrVal, VNodeType& degArrSize, LinkType& linkSize)
{
  const NodeType degSize = degArrVal.size();
  if (degSize < 2)
    return -1;
  NodeType n1 = 0, k1 = degArrVal[n1], n2 = 1, k2 = degArrVal[n2];
  bool dk_greater = true;
  if (k1 > k2) {
    dk_greater = false;
    n1 = degSize - 1;
    n2 = degSize - 2;
    k1 = degArrVal[n1];
    k2 = degArrVal[n2];
  }
  while (k2 % 2 == k1 % 2 && 0 < n2 && n2 < degSize - 1) {
    n2 = dk_greater ? n2 + 1 : n2 - 1;
    k2 = degArrVal[n2];
  }
  linkSize = linkSize - k1 + k2;
  --degArrSize[n1];
  ++degArrSize[n2];
  return 0;
}

// ********************************************************
int net_degree::power_nature_cutoff(NodeType& kMax, const NodeType nodeSize,
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
