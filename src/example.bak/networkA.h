#ifndef NETWORK_A_H
#define NETWORK_A_H

#include <iostream>
#include "networks.h"

#ifdef NET_A
//**//*******************************************************
// 参数：   nodeize 网络总节点数
int net_A(Network &net);

int net_read_params_A(std::istream& is, Network& net);
int net_save_params_A(std::ostream& os, const Network& net);
int net_clear_A(Network& net);
//**//*******************************************************
#endif  // NET_A
#endif  // NETWORK_A_H

