#ifndef NETWORK_ACT_RECOMMEND_H
#define NETWORK_ACT_RECOMMEND_H

#include <iostream>
#include "networks.h"

#ifdef ACT_RECOMMEND
//**//****************************************************//*
// 参数：   mass
//          heat
int net_recommend(Network &net);
int net_recommend_mass(VDouble& o, VDouble& u2, VDouble& o2, VVNodeType& pu, VVNodeType& po);

//**//****************************************************//*
#endif  // ACT_RECOMMEND

#endif  // NETWORK_ACT_RECOMMEND_H


