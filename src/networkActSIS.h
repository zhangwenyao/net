#ifndef NETWORK_ACT_SIS_H
#define NETWORK_ACT_SIS_H

#include <iostream>
#include "networks.h"

#ifdef ACT_SIS
//**//****************************************************//*
struct ParamsSIS{
    unsigned    M;
    double      p0, p, lambda;
    double      t_r, t_av, ksi;
    LinkType    nSum, n2Sum;
    NodeType    nNum;
    VVNodeType  statusSN, SN;
    VNodeType   N_i;
    VLinkType   NDeg_i;
    VDouble     t;
};

int net_act_SIS(Network &net, ParamsSIS& params);

//**//****************************************************//*
#endif  // ACT_SIS

#endif  // NETWORK_ACT_SIS_H


