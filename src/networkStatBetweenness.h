#ifndef NETWORK_STAT_BETWEENNESS_H
#define NETWORK_STAT_BETWEENNESS_H

#include <iostream>
#include "network.h"

#ifdef STAT_BETWEENNESS
//**//****************************************************//*
int net_read_params_betweenness(std::istream& is, Network& net);
int net_save_params_betweenness(std::ostream& os, const Network& net);
int net_save_betweenness(const Network& net, const char *name = NULL);

int net_clear_betweenness(Network& net);

int net_cal_betweenness0(Network& net);
int net_cal_betweenness(Network& net);
int net_betweenness(Network& net);

//**//****************************************************//*
#endif  // STAT_BETWEENNESS
#endif  //NETWORK_STAT_BETWEENNESS_H

