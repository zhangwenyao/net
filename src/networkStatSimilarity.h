#ifndef NETWORK_STAT_SIMILARITY_H
#define NETWORK_STAT_SIMILARITY_H

#include <iostream>
#include "network.h"

#ifdef STAT_SIMILARITY
//**//****************************************************//*
int net_read_params_similarity(std::istream& is, Network& net);
int net_save_params_similarity(std::ostream& os, const Network& net);
int net_save_similarity(const Network& net, const char* name = NULL);

int net_clear_similarity(Network& net);

int net_similarity(Network& net, Network& net2);
int net_cal_similarity(Network& net);

//**//****************************************************//*
#endif  // STAT_SIMILARITY
#endif  // NETWORK_NET_SIMILARITY_H
