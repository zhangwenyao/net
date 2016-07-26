#ifndef NETWORK_ACT_RECOMMEND_H
#define NETWORK_ACT_RECOMMEND_H

#include <iostream>
#include "networks.h"

#ifdef ACT_RECOMMEND
//**//****************************************************//*
// 参数：   mass
//          heat
int net_recommend(Network &net);

int net_read_params_recommend(std::istream& is, Network& net);
int net_save_params_recommend(std::ostream& os, const Network& net);
//**//****************************************************//*
#endif  // ACT_RECOMMEND

#endif  // NETWORK_ACT_RECOMMEND_H


