#ifndef NETWORK_STAT_SPREAD_H
#define NETWORK_STAT_SPREAD_H

#include "net.h"
#ifdef STAT_SPREAD

#include <iostream>
#include "networks.h"
//**//*****************************************************//*
int net_clear_spread(Networks& net);

int net_read_params_spread(std::istream& is, Networks& net);
int net_save_params_spread(std::ostream& os, const Networks& net);
//**//*****************************************************//*
#endif  // STAT_SPREAD
#endif  // NETWORK_STAT_SPREAD_H
