#ifndef NETWORK_ACT_SIS_H
#define NETWORK_ACT_SIS_H

#include <iostream>
#include "networks.h"

#ifdef ACT_SIS
//**//****************************************************//*
int net_save_params_act_SIS(std::ostream& os, const Network& net);
int net_act_SIS(Network& net);
int net_act_SIS_tau(Network& net);

//**//****************************************************//*
#endif  // ACT_SIS

#endif  // NETWORK_ACT_SIS_H
