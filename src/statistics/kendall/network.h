#ifndef STATISTICS__KENDALL__NETWORK_H_
#define STATISTICS__KENDALL__NETWORK_H_
#include "kendall.h"
#ifdef STAT_KENDALL

#include <iostream>

namespace network {
namespace kendall {
  // ******************************************************
  class Kendall {
public:
    double kendall, OutIn;

    Kendall(void);
    //friend std::ostream& operator<<(std::ostream& os, const Kendall& kendall);
    int save_params(std::ostream& os) const;
    int save_params(const char* name = NULL) const;
    int save_data(const char* name = NULL, const char priChar = '\n',
        const char priChar2 = '\t') const;
    int save(const char* name = NULL, const char priChar = '\n',
        const char priChar2 = '\n') const;
    int read_params_1(std::string& s, std::istream& is);
    Kendall& clear(void);
  };
}
}

// ******************************************************
std::ostream& operator<<(
    std::ostream& os, const network::kendall::Kendall& kendall);

#endif // STAT_KENDALL
#endif // NETWORK_STAT_KENDALL_H
