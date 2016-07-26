#ifndef NETWORK_BA_H
#define NETWORK_BA_H

#include <iostream>
#include "networks.h"

#ifdef NET_BA
//**//****************************************************//*
// 参数：   M0  全连通子网络节点数目
//          M   新节点的度（M<=M0）
//          nodeize 网络总节点数
int net_BA(Network &net);

int net_read_params_BA(std::istream& is, Network& net);
int net_save_params_BA(std::ostream& os, const Network& net);
//**//****************************************************//*
#endif  // NET_BA

#endif  // NETWORK_BA_H

