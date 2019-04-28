#ifndef MODEL__RANDOM__NETWORK_H_
#define MODEL__RANDOM__NETWORK_H_
#include "random.h"
#ifdef NET_RANDOM

#include <iostream>

// ******************************************************
namespace network {
namespace random {
  class Random {
public:
    double p;
    Random(void);
    // friend std::ostream& operator<<(std::ostream& os, const Random&
    // random);
    int save_params(std::ostream& os) const;
    int save_params(const char* name = NULL) const;
    int save_data(const char* name = NULL) const;
    int save(const char* name = NULL) const;
    int read_params_1(std::string& s, std::istream& is);
  };
}
}

// ******************************************************
std::ostream& operator<<(
    std::ostream& os, const network::random::Random& random);

#endif // NET_RANDOM
#endif // NETWORK_RANDOM_H
