#ifndef MODEL__BA__NETWORK_H_
#define MODEL__BA__NETWORK_H_
#include "BA.h"
#ifdef NET_BA

#include <iostream>

// ******************************************************
namespace network {
namespace ba {
  class Ba {
public:
    int M0, M;

    Ba(void);
    // friend std::ostream& operator<<(std::ostream& os, const Ba& ba);
    int save_params(std::ostream& os) const;
    int save_params(const char* name = NULL) const;
    int save_data(const char* name = NULL, const int dirFlag = 0,
        const char priChar = '\n', const char priChar2 = '\t') const;
    int save(const char* name = NULL, const int dirFlag = 0,
        const char priChar = '\n', const char priChar2 = '\t') const;
    int read_params_1(std::string& s, std::istream& is);
  };
}
}
// ******************************************************
std::ostream& operator<<(std::ostream& os, const network::ba::Ba& ba);

#endif // NET_BA
#endif // NETWORK_BA_H
