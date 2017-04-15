#ifndef NETWORK_STAT_SPREAD_H
#define NETWORK_STAT_SPREAD_H

#include <iostream>
#include "network.h"

#ifdef #endif  // STAT_SPREAD

//**//***************************************************************
int net_clear_spread(Networks& net);

int net_read_params_spread(istream& is, Networks& net);
int net_save_params_spread(ostream& os, const Networks& net);
//**//***************************************************************
#endif  // STAT_SPREAD
#endif  // NETWORK_STAT_SPREAD_H
