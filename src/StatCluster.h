#ifndef STAT_CLUSTER_H
#define STAT_CLUSTER_H

#include "net.h"

#ifdef STAT_CLUSTER
//**//****************************************************//*
int cal_cluster_directed_weight(double &cluster_c, VDouble &cluster, VVWeightType& weightMatr, const VVDistType& linkMatr);
int cal_cluster_directed_unweight(double &cluster_c, VDouble &cluster, const VVDistType& linkMatr);

//**//****************************************************//*
#endif  // STAT_CLUSTER
#endif  // STAT_CLUSTER_H
