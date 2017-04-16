#ifndef NETWORK_STAT_CLUSTER_H
#define NETWORK_STAT_CLUSTER_H

#include "net.h"
#ifdef STAT_CLUSTER

#include <iostream>
#include "network.h"
//**//****************************************************//*
int net_read_params_cluster(std::istream& is, Network& net);
int net_save_params_cluster(std::ostream& os, const Network& net);
int net_save_cluster(const Network& net, const char* name = NULL);

int net_clear_cluster(Network& net);

int net_cal_cluster(Network& net);

//**//****************************************************//*
#endif  // STAT_CLUSTER
#endif  // NETWORK_STAT_CLUSTER_H
