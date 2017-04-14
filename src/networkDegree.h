#ifndef NETWORK_DEGREE_H
#define NETWORK_DEGREE_H

#include <iostream>
#include "networks.h"

#ifdef NET_DEGREE
//**//****************************************************//*
std::ostream& operator<<(std::ostream& os, const Net_degree& degree);

//**//****************************************************//*
// Poisson度分布参数
//      poisson_p    连接概率p
//      nodeSize    网络节点数目
#ifdef DEG_POISSON
int net_read_params_poisson(std::istream& is, Networks& net);
int net_save_params_poisson(std::ostream& os, const Networks& net);
#endif  // DEG_POISSON

// 幂律度分布参数
//      power_gamma 幂指数
//      nodeSize    节点数目
//      kMin        最小度
//      kMax        最大度
//
#ifdef DEG_POWER
int net_read_params_power(std::istream& is, Networks& net);
int net_save_params_power(std::ostream& os, const Networks& net);
#endif  // DEG_POWER

//**//****************************************************//*
#endif  // NET_DEGREE
#endif  // NETWORK_DEGREE_H
