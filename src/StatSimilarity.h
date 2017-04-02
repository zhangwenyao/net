#ifndef STAT_SIMILARITY_H
#define STAT_SIMILARITY_H

#include "net.h"

#ifdef STAT_SIMILARITY
//**//****************************************************//*
int cal_similarity(VVDouble &simiNodeCoef, VVDouble &simiEdgeCoef, const VNodeType& link1, const VNodeType& link2, const int dirFlag = 0); // 计算网络相似性

int cal_similarity_update(VVDouble &simiNodeCoef, VVDouble &simiEdgeCoef, const VNodeType& link1, const VNodeType& link2, VVDouble &x, double &x2Sum, VVDouble &y, double &y2Sum, const int dirFlag = 0);

//**//****************************************************//*
#endif  // STAT_SIMILARITY
#endif  // STAT_SIMILARITY_H

