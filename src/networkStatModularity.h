#ifndef NETWORK_STAT_MODULARITY_H
#define NETWORK_STAT_MODULARITY_H

#include <iostream>
#include "network.h"

#ifdef STAT_MODULARITY
//**//****************************************************//*
int net_read_params_modularity(std::istream& is, Network& net);
int net_save_params_modularity(std::ostream& os, const Network& net);
int net_save_modularity(const Network& net, const char* name = NULL);

int net_clear_modularity(Network& net);

int net_save_moduStk(const Network& net, std::ostream& os, const char c = '\t');
int net_save_moduStk(const Network& net, const char* name = NULL,
                     const char c = '\t');

int net_modularity(Network& net);
int net_cal_modularity(Network& net);

#ifdef STAT_BETWEENNESS
int net_newman_modularity(double& qMax, Network& net, NodeType mSize = 0);
#endif
//**//****************************************************//*
#endif  // STAT_MODULARITY
#endif  // NETWORK_NET_MODULARITY_H
