#ifndef NETWORK_STAT_CLUSTER_H
#define NETWORK_STAT_CLUSTER_H
#include "StatCluster.h"
#ifdef STAT_CLUSTER

#include <iostream>

// ******************************************************
class Stat_cluster {
  public:
    double coef;
    VDouble Node;  // clustering coefficient

    Stat_cluster(void);
    friend std::ostream& operator<<(std::ostream& os,
        const Stat_cluster& cluster);
    int save_params(std::ostream& os) const;
    int save_params(const char* name = NULL) const;
    int save_data(const char* name = NULL, const char priChar = '\n',
        const char priChar2 = '\n') const;
    int save(const char* name = NULL, const char priChar = '\n',
        const char priChar2 = '\n') const;
    int read_params_1(std::string& s, std::istream& is);
    Stat_cluster& clear(void);
};
std::ostream& operator<<(std::ostream& os, const Stat_cluster& cluster);

// ******************************************************
#endif  // STAT_CLUSTER
#endif  //NETWORK_STAT_CLUSTER_H
