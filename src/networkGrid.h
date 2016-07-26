#ifndef NETWORK_GRID_H
#define NETWORK_GRID_H

#include <iostream>
#include "network.h"

#ifdef NET_GRID
//**//************************************************************//*
// 参数：    Grid_NX X方向格点数目
//          Grid_NY Y方向格点数目
// 节点i对应坐标（x，y）：i=x*NX+y
int net_Grid_new(Network &net);

int net_read_params_Grid(std::istream& is, Network& net);
int net_save_params_Grid(std::ostream& os, const Network& net);
//**//************************************************************//*
#endif  // NET_GRID
#endif  // NETWORK_GRID_H

