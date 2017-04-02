#ifndef STAT_SIMILARITY_H
#define STAT_SIMILARITY_H

#include "net.h"

#ifdef STAT_SIMILARITY
//**//****************************************************//*
int cal_similarity(VVDouble &simiNodeCoef, VVDouble &simiEdgeCoef, const VVNodeType& p2p1, const VVNodeType& p2pIn1, const VNodeType& link1, const VVLinkType& p2p1_linkPos, const VVLinkType& p2pIn1_linkPos, const VVNodeType& p2p2, const VVNodeType& p2pIn2, const VNodeType& link2, const VVLinkType& p2p2_linkPos, const VVLinkType& p2pIn2_linkPos, const int dirFlag = 0); // 计算网络相似性

int cal_similarity_update(VVDouble &simiNodeCoef, VVDouble &simiEdgeCoef, const VVNodeType& p2p1, const VVNodeType& p2pIn1, const VNodeType& link1, const VVLinkType& p2p1_linkPos, const VVLinkType& p2pIn1_linkPos, const VVNodeType& p2p2, const VVNodeType& p2pIn2, const VNodeType& link2, const VVLinkType& p2p2_linkPos, const VVLinkType& p2pIn2_linkPos, VVDouble &x, double &xSum, VVDouble &y, double &ySum, const int dirFlag = 0);

//**//****************************************************//*
#endif  // STAT_SIMILARITY
#endif  // STAT_SIMILARITY_H

