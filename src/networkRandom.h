#ifndef NETWORK_RANDOM_H
#define NETWORK_RANDOM_H

#include <iostream>
#include "network.h"

#ifdef NET_RANDOM
//**//****************************************************//*
int net_random_clear(Network& net);
int net_random_init(Network& net);

// ER随机网络参数
//      p           连边概率p
//      nodeSize    节点数目
int net_read_params_ER(std::istream& is, Network& net);
int net_save_params_ER(std::ostream& os, const Network& net);
int net_ER(Network& net);

//**//****************************************************//*
/*
    ranLink_ranNode     // 直接随机选点连边；用到linkMatr,p2p
    ranLink_proNode     // 所有点按概率连边；用到linkMatr,p2p
    ranLink_remDeg      // 随机选取剩余度连边；用到p2p,link
    ranLink_remDegGauss // 随机选剩余度按点的度之差的相应高斯概率连边、重连时所有边中随机选；用到p2p,remNodeNum,link
    ranLink_remDegExp   // 随机选剩余度按点的度之差的相应指数概率连边、重连时所有边中随机选；用到p2p,remNodeNum,link
    ranLink_remDegExp0  // 随机选剩余度按点的度之差的相应指数概率连边、重连时所有边中随机选；用到p2p,remNodeNum,link
    ranNode_link        // 随机选点连边、重连时所有边中随机选；用到p2p,remNodeNum,link
    ranNode_deg         // 随机按度选点连边、重连时所有边中随机选；用到p2p,remNodeNum,link
    ranNode_node        // 随机选点连边、重连时随机选点；用到p2p,remNodeNum
    ranNode_nodeM       // 随机选点连边、重连时随机选点；用到linkMatr,p2p,remNodeNum
    ranNode_Gauss       // 随机选点按点的度之差的相应高斯概率连边、重连时所有边中随机选；用到p2p,remNodeNum,link
    ranNode_node        // 随机选点连边、重连时随机选点再选边；用到p2p,remNodeNum
 *//**/
int net_random_node_prob(Network& net);    // 所有点按概率p连边
int net_random_remDeg(Network& net);   // 随机抽取剩余度连边
int net_random_ranNode_link(Network& net); // 随机选点连边，重连时所有边中随机选

int net_random_ranNode(Network& net);  // 每次直接随机抽取两个点连边
//**//****************************************************//*
#endif  // NET_RANDOM
#endif  // NETWORK_RANDOM_H

