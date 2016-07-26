#ifndef NETWORK_RANDOM_H
#define NETWORK_RANDOM_H

#include <iostream>
#include "network.h"

#ifdef NET_RANDOM
//**//****************************************************//*
// ER随机网络参数
//      ER_p        连边概率p
//      nodeSize    节点数目
int net_random_clear(Network& net);
int net_random_init(Network& net);

int net_ER(Network& net);
int net_read_params_ER(std::istream& is, Network& net);
int net_save_params_ER(std::ostream& os, const Network& net);

int net_random_node_prob(Network& net);    // 所有点按概率p连边
int net_random_remDeg(Network& net);   // 随机抽取剩余度连边
int net_random_ranNode_link(Network& net); // 随机选点连边，重连时所有边中随机选

int net_random_ranNode(Network& net);  // 每次直接随机抽取两个点连边
//**//****************************************************//*
#endif  // NET_RANDOM
#endif  // NETWORK_RANDOM_H

