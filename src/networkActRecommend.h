#ifndef NETWORK_ACT_RECOMMEND_H
#define NETWORK_ACT_RECOMMEND_H

#include "net.h"
#ifdef ACT_RECOMMEND

#include <iostream>
#include "networks.h"
//**//****************************************************//*
// 参数：   mass
//          heat
int net_act_recommend(Network& net, const string s = "");
int net_act_recommend_mass(VDouble& o, VDouble& u2, VDouble& o2, VVNodeType& pu,
                           VVNodeType& po);

//**//****************************************************//*
#endif  // ACT_RECOMMEND
#endif  // NETWORK_ACT_RECOMMEND_H
