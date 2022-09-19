#ifndef MODEL__DEGREE__NETWORK_H
#define MODEL__DEGREE__NETWORK_H
#include "degree.h"
#ifdef NET_DEGREE

#include <iostream>

// **************************************************************
namespace network {
namespace degree {
  class Degree {
public:
#ifdef DEG_POISSON
    double poisson_p;
#endif

#ifdef DEG_POWER
    double power_gamma;
#endif
    Degree(void);
    // friend std::ostream& operator<<(std::ostream& os, const Degree&
    // degree);
    int save_params(std::ostream& os) const;
    int save_params(const char* name = NULL) const;
    int save_data(const char* name = NULL) const;
    int save(const char* name = NULL) const;
    int read_params_1(std::string& s, std::istream& is);
  };
} // end namespace degree
} // end namespace network

// ******************************************************
std::ostream& operator<<(
    std::ostream& os, const network::degree::Degree& degree);

#endif // NET_DEGREE
#endif // NETWORK_DEGREE_H
