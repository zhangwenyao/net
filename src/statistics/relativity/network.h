#ifndef STATISTICS__RELATIVITY__NETWORK_H_
#define STATISTICS__RELATIVITY__NETWORK_H_
#include "relativity.h"
#ifdef STAT_RELATIVITY

#include <iostream>

namespace network {
namespace relativity {
  // ******************************************************
  class Relativity {
public:
    double relativity, alpha;

    Relativity(void);
    int save_params(std::ostream& os, const int dirFlag = 0) const;
    int save_params(const char* name = NULL, const int dirFlag = 0) const;
    int save_data(const char* name = NULL, const int dirFlag = 0,
        const char priChar = '\n', const char priChar2 = '\t') const;
    int save(const char* name = NULL, const int dirFlag = 0,
        const char priChar = '\n', const char priChar2 = '\t') const;
    int read_params_1(std::string& s, std::istream& is);
    Relativity& clear(void);
  };
}
}

// ******************************************************
std::ostream& operator<<(
    std::ostream& os, const network::relativity::Relativity& relativity);

#endif //
#endif // _H_
