#ifndef NETWORK_RANDOM_H
#define NETWORK_RANDOM_H
#include "NetRandom.h"
#ifdef NET_RANDOM
#include <iostream>

//**//****************************************************//*
class Net_random {
  public:
    double p;
    Net_random(void);
    friend std::ostream& operator<<(std::ostream& os, const Net_random& random);
    int save_params(std::ostream& os) const;
    int save_params(const char* name = NULL) const;
    int save_data(const char* name = NULL) const;
    int save(const char* name = NULL) const;
    int read_params_1(std::string& s, std::istream& is);
};
std::ostream& operator<<(std::ostream& os, const Net_random& random);

//**//****************************************************//*
#endif  // NET_RANDOM
#endif  // NETWORK_RANDOM_H

