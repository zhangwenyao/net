#ifndef NETWORK_BA_H
#define NETWORK_BA_H
#include "NetBA.h"
#ifdef NET_BA

#include <iostream>

//**//****************************************************//*
class Net_BA {
  public:
    int M0, M;

    Net_BA(void);
    friend std::ostream& operator<<(std::ostream& os, const Net_BA& ba);
    int save_params(std::ostream& os) const;
    int save_params(const char* name = NULL) const;
    int save_data(const char* name = NULL) const;
    int save(const char* name = NULL) const;
    int read_params_1(std::string& s, std::istream& is);
};
std::ostream& operator<<(std::ostream& os, const Net_BA& ba);

//**//****************************************************//*
#endif  // NET_BA
#endif  // NETWORK_BA_H

