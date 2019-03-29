#ifndef NET_DEGREE_H
#define NET_DEGREE_H

#include "net.h"

#ifdef NET_DEGREE
namespace net_degree {
// *******************************************************************
int sum_prob(const NodeType kMin, const NodeType kMax,
    std::function<double(const NodeType n)>, double& prob_sum);

// ************* 泊松网络 type:deg_poisson ****************
int poisson_cal_degArrProb(const double r, VNodeType& degArrVal,
    VDouble& degArrProb, const NodeType kMin, const NodeType kMax,
    NodeType& nodeSize); // 计算度分布概率

// ************* 幂律网络 type:deg_power ****************
Double power_prob(const NodeType n, const Double r);

int power_cal_degArrProb(const double p, VNodeType& degArrVal,
    VDouble& degArrProb, const NodeType kMin,
    const NodeType kMax); // 计算度分布概率
int power_cal_deg_arr(VNodeType& degArrSize, const VNodeType& degArrVal,
    const VDouble& degArrProb, NodeType nodeSize); // 生成度分布累计序列
int power_cal_deg_arr_func(const NodeType nodeSize, const NodeType kMin,
    const NodeType kMax, std::function<double(const NodeType)> prob_func,
    const double degProbSum, VNodeType& degArrVal, VNodeType& degArrSize);
int read_prob_sum(
    const char* filename, VNodeType& degProbSumVal, VDouble& degProbSumArr);
int power_cal_deg_arr_prob_sum_arr(const NodeType nodeSize,
    const NodeType kMin, const NodeType kMax,
    std::function<Double(const NodeType)> prob_func,
    const VNodeType& degProbSumVal, const VDouble& degProbSumArr,
    VNodeType& degArrVal, VNodeType& degArrSize);
int fix_degArr_linkSize_lkk3_fast(
    const VNodeType& degArrVal, VNodeType& degArrSize, LinkType& linkSize);

int power_nature_cutoff(NodeType& kMax, const NodeType nodeSize,
    const NodeType kMin, const double gamma);

// *******************************************************************
}
#endif // NET_DEGREE
#endif // NET_DEGREE_H
