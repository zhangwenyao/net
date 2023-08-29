#ifndef STATISTICS__CLUSTER__NETWORK_H_
#define STATISTICS__CLUSTER__NETWORK_H_
#include "cluster.h"
#ifdef STAT_CLUSTER

#include <iostream>

namespace network {
namespace cluster {
  // ******************************************************
  class Cluster {
public:
    double coef;
    VDouble Node; // clustering coefficient

    Cluster(void);
    // friend std::ostream& operator<<(std::ostream& os,
    // const Cluster& cluster);
    int save_params(std::ostream& os) const;
    int save_params(const char* name = NULL) const;
    int save_data(const char* name = NULL, const int dirFlag = 0,
        const char priChar = '\n', const char priChar2 = '\t') const;
    int save(const char* name = NULL, const int dirFlag = 0,
        const char priChar = '\n', const char priChar2 = '\t') const;
    int read_params_1(std::string& s, std::istream& is);
    Cluster& clear(void);
  };
}
}

// ******************************************************
std::ostream& operator<<(
    std::ostream& os, const network::cluster::Cluster& cluster);

#endif // STAT_CLUSTER
#endif // NETWORK_STAT_CLUSTER_H
