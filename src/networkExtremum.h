#ifndef NETWORK_EXTREMUM_H
#define NETWORK_EXTREMUM_H

#include "network.h"

#ifdef NET_EXTREMUM
//**//****************************************************//*
// 特殊网络参数
//      nodeSize    网络节点数目
//      nodeDeg     节点度分布序列
// Max: 极大同配网络
// Min: 极小同配网络（极大异配网络）
int net_Max_new(Network& net);   // 最大相关网络
int net_Min_new(Network& net);   // 最小相关网络
int net_Min_new_lkk_p2p(Network& net, const int fix);  // 最小相关网络
int net_Min_new_lkk(Network& net, const int fix = 0);
int net_extreme_lkk(Network& net, const int extrMax, const unsigned countN = 3);

int extreme_main(int argc, char **argv);
//**//****************************************************//*
#endif  // NET_EXTREMUM
#endif  // NETWORK_EXTREMUM_H

