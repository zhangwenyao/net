#ifndef STAT_BETWEENNESS_H
#define STAT_BETWEENNESS_H

#include "net.h"

#ifdef STAT_BETWEENNESS
//**//****************************************************//*
int cal_betweenness0(VDouble &betw, VVDouble &betwEdge, double &bt, double& btEdge, VVDistType& minDistMatr, VDistType& minDistMean, const VVNodeType& p2p, const VVNodeType& p2pIn);   // 无权网络介数
int cal_betweenness(VDouble  &betw, VVDouble &betwEdge, double &bt, double& btEdge, VVDistType& minDistMatr, VDistType& minDistMean, const VVNodeType& p2p, const VVNodeType& p2pIn, const VVDistType& linkMatr); // 加权网络介数

//**//****************************************************//*
#endif  // STAT_BETWEENNESS
#endif  // STAT_BETWEENNESS_H
