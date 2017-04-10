#ifndef NETWORK_STAT_KENDALL_H
#define NETWORK_STAT_KENDALL_H

#include <iostream>
#include "network.h"

#ifdef STAT_KENDALL
//**//****************************************************//*
int net_clear_kendallTau(Network& net);
int net_cal_kendallTau(Network& net);
int net_read_params_kendallTau(std::istream& is, Network& net);
int net_save_params_kendallTau(std::ostream& os, const Network& net);
int net_save_kendallTau(const Network& net, const char *name = NULL);

//**//****************************************************//*
#endif  // STAT_KENDALL
#endif  // NETWORK_STAT_KENDALL_H

