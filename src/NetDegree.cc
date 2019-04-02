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

int net_degree::read_prob_sum(
    const char* filename, VNodeType& degProbSumVal, VDouble& degProbSumArr)
{
  degProbSumVal.clear();
  degProbSumArr.clear();
  _ERR(filename == NULL || filename[0] == '\0');
  string f = filename;
  ifstream is(filename);
  _ERR(!is);
  NodeType i;
  Double p;
  while (is >> i >> p) {
    degProbSumVal.push_back(i);
    degProbSumArr.push_back(p);
  }
  is.close();
  return 0;
}

// 生成度分布累计序列
int net_degree::power_cal_deg_arr_prob_sum_arr(const NodeType nodeSize,
    const NodeType kMin, const NodeType kMax,
    std::function<Double(const NodeType)> prob_func,
    const VNodeType& degProbSumVal, const VDouble& degProbSumArr,
    VNodeType& degArrVal, VNodeType& degArrSize)
{
  degArrVal.clear();
  degArrSize.clear();
  if (kMin < 1 || kMin > kMax || nodeSize < 2) {
    ERROR();
    return -1;
  }
  if (kMax >= NodeType(1) << (degProbSumArr.size() + 1)) {
    ERROR();
    return -1;
  }
  NodeType size = nodeSize, n1 = 0;
  for (; size > 0 && n1 + 1 < degProbSumArr.size(); ++n1) {
    NodeType k = degProbSumVal[n1], km = degProbSumVal[n1 + 1];
    Double probSum = degProbSumArr[n1], probSum2 = degProbSumArr[n1 + 1];
    if (size * (probSum - probSum2) / probSum / (km - k) <= 1.0 / (1 << 2))
      break;
    for (; size > 0 && probSum > 0 && k < km; ++k) {
      Double prob = prob_func(k);
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
  }
  if (size)
    _ERR(net_degree::power_cal_deg_arr_prob_sum_arr2(size, n1, prob_func,
        degProbSumVal, degProbSumArr, degArrVal, degArrSize));
  _ERR(degArrVal.size() <= 0 || degArrVal.front() != kMin
      || degArrVal.back() != kMax);
  return 0;
}

int net_degree::power_cal_deg_arr_prob_sum_arr2(const NodeType nodeSize,
    const NodeType kMinN, std::function<Double(const NodeType)> prob_func,
    const VNodeType& degProbSumVal, const VDouble& degProbSumArr,
    VNodeType& degArrVal, VNodeType& degArrSize)
{
  NodeType kMaxN = degProbSumVal.size() - 2, kMax = degProbSumVal.back() - 1,
           size = nodeSize, n1 = kMinN;
  for (; size > 0 && n1 <= kMaxN; ++n1) {
    NodeType k1 = degProbSumVal[n1], km = degProbSumVal[n1 + 1];
    Double probSum = degProbSumArr[n1], probSum2 = degProbSumArr[n1 + 1],
           p = (probSum - probSum2) / probSum;
    if (size * p / (km - k1) <= 1.0 / (1 << 4))
      break;
    VNodeType degVal;
    binomial_distribution<NodeType> bd(size, p);
    NodeType n = bd(rand2);
    if (n1 == kMaxN) {
      degVal.push_back(kMax);
      n = --size;
    } else if (n <= 0)
      continue;
    else if (n == size)
      --n;
    const Double pMax = prob_func(k1);
    uniform_int_distribution<NodeType> uid(k1, km - 1);
    size -= n;
    while (n > 0) {
      const NodeType k = uid(rand2);
      if (rand_double() * pMax <= prob_func(k)) {
        degVal.push_back(k);
        --n;
      }
    }
    sort(degVal.begin(), degVal.end());
    for (auto i = degVal.begin(); i != degVal.end(); ++i) {
      NodeType k = *i, n = 1;
      while (i + 1 != degVal.end() && k == *(i + 1)) {
        ++i;
        ++n;
      }
      degArrVal.push_back(k);
      degArrSize.push_back(n);
    }
  }
  if (size)
    _ERR(net_degree::power_cal_deg_arr_prob_sum_arr3(size, n1, prob_func,
        degProbSumVal, degProbSumArr, degArrVal, degArrSize));
  _ERR(degArrVal.size() <= 0 || degArrVal.back() != degProbSumVal.back() - 1);
  return 0;
}

int net_degree::power_cal_deg_arr_prob_sum_arr3(const NodeType nodeSize,
    const NodeType kMinN, std::function<Double(const NodeType)> prob_func,
    const VNodeType& degProbSumVal, const VDouble& degProbSumArr,
    VNodeType& degArrVal, VNodeType& degArrSize)
{
  NodeType kMaxN = degProbSumVal.size() - 2, kMax = degProbSumVal.back() - 1,
           size = nodeSize, n1 = kMinN;
  for (; size > 0 && n1 <= kMaxN; ++n1) {
    NodeType k = degProbSumVal[n1], km = degProbSumVal[n1 + 1];
    Double probSum = degProbSumArr[n1], probSum2 = degProbSumArr[n1 + 1],
           p_all = probSum - probSum2, p = p_all / probSum, r;
    VNodeType degVal;
    binomial_distribution<NodeType> bd(size, p);
    NodeType n = bd(rand2);
    if (n1 == kMaxN) {
      degVal.push_back(kMax);
      n = --size;
    } else if (n <= 0)
      continue;
    else if (n == size)
      --n;
    size -= n;
    VDouble deg_prob;
    for (NodeType i = 0; i < n; ++i)
      deg_prob.push_back(rand_double() * p_all);
    sort(deg_prob.begin(), deg_prob.end());
    r = deg_prob.front();
    for (NodeType i = 0, im = deg_prob.size(); i < im; ++i) {
      while (r > 0) {
        r -= prob_func(k++);
        if (k > km)
          break;
      }
      degVal.push_back(k - 1);
      while (i + 1 < im && r <= 0) {
        r += deg_prob[i + 1] - deg_prob[i];
        if (r <= 0) {
          degVal.push_back(k - 1);
          ++i;
        } else
          break;
      }
    }
    sort(degVal.begin(), degVal.end());
    for (auto i = degVal.begin(); i != degVal.end(); ++i) {
      NodeType k = *i, n = 1;
      while (i + 1 != degVal.end() && k == *(i + 1)) {
        ++i;
        ++n;
      }
      degArrVal.push_back(k);
      degArrSize.push_back(n);
    }
  }
  _ERR(size > 0 || degArrVal.size() <= 0
      || degArrVal.back() != degProbSumVal.back() - 1);
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
