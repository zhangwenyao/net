#ifndef NETWORK_DEGREE_H
#define NETWORK_DEGREE_H
#include "NetDegree.h"
#ifdef NET_DEGREE

#include <iostream>

// **************************************************************
class Net_degree {
  public:
#ifdef DEG_POISSON
    double poisson_p;
#endif

#ifdef DEG_POWER
    double power_gamma;
#endif
    Net_degree(void);
    friend std::ostream& operator<<(std::ostream& os, const Net_degree& degree);
    int save_params(std::ostream& os) const;
    int save_params(const char* name = NULL) const;
    int save_data(const char* name = NULL) const;
    int save(const char* name = NULL) const;
    int read_params_1(std::string& s, std::istream& is);
};

std::ostream& operator<<(std::ostream& os, const Net_degree& degree);

// ******************************************************
#endif  // NET_DEGREE
#endif  // NETWORK_DEGREE_H

