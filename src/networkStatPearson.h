#ifndef NETWORK_STAT_PEARSON_H
#define NETWORK_STAT_PEARSON_H

#include <iostream>
#include "network.h"

#ifdef STAT_PEARSON
//**//****************************************************//*
int net_clear_pearson(Network& net);
int net_cal_pearson(Network& net);
int net_read_params_pearson(std::istream& is, Network& net);
int net_save_params_pearson(std::ostream& os, const Network& net);
int net_save_pearson(const Network& net, const char* name = NULL);

//**//****************************************************//*
#endif  // STAT_PEARSON
#endif  // NETWORK_STAT_PEARSON_H
