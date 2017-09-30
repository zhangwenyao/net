#ifndef NET_DEGREE_H
#define NET_DEGREE_H

#include "net.h"

#ifdef NET_DEGREE
//**//************** 泊松网络 type:deg_poisson *************//*
int poisson_cal_degArrProb(const double r, VNodeType& degArrVal,
    VDouble& degArrProb, const NodeType kMin, const NodeType kMax,
    NodeType& nodeSize); // 计算度分布概率

//**//************** 幂律网络 type:deg_power *************//*
int power_cal_degArrProb(const double p, VNodeType& degArrVal,
    VDouble& degArrProb, const NodeType kMin,
    const NodeType kMax); // 计算度分布概率
int power_cal_deg_arr(VNodeType& degArrSize, const VNodeType& degArrVal,
    const VDouble& degArrProb, NodeType nodeSize); // 生成度分布累计序列

//**//*****************************************************************//*
#endif // NET_DEGREE
#endif // NET_DEGREE_H
