#ifndef STATISTICS__CLUSTER__CLUSTER_H_
#define STATISTICS__CLUSTER__CLUSTER_H_
#include "../../network/net.h"
#ifdef STAT_CLUSTER

namespace network {
namespace cluster {
  // ******************************************************
  int cal_cluster_directed_weight(double& cluster_c, VDouble& cluster,
      VVWeightType& weightMatr, const VVDistType& linkMatr);
  int cal_cluster_directed_unweight(
      double& cluster_c, VDouble& cluster, const VVDistType& linkMatr);
}
}

// ******************************************************
#endif // STAT_CLUSTER
#endif // STAT_CLUSTER_H
