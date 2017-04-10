#ifndef NETWORK_DEGREE_H
#define NETWORK_DEGREE_H

#include <iostream>
#include "network.h"

#ifdef NET_DEGREE
//**//****************************************************//*
// Poisson度分布参数
//      poison_p    连接概率p
//      nodeSize    网络节点数目
#ifdef DEG_POISSON
int net_deg_poisson(Network& net); // 生成度序列 各点均按概率取任意度
int net_read_params_poisson(std::istream& is, Network& net);
int net_save_params_poisson(std::ostream& os, const Network& net);
#endif  // DEG_POISSON

// 幂律度分布参数
//      power_gamma 幂指数
//      nodeSize    节点数目
//      kMin        最小度
//      kMax        最大度
//
#ifdef DEG_POWER
int net_power_check_params(Network& net);
int net_deg_power(Network& net);
int net_read_params_power(std::istream& is, Network& net);
int net_save_params_power(std::ostream& os, const Network& net);
#endif  // DEG_POWER

//**//****************************************************//*
#endif  // NET_DEGREE
#endif  // NETWORK_DEGREE_H

