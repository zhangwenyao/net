#ifndef STATISTICS__PEARSON__NETWORK_H_
#define STATISTICS__PEARSON__NETWORK_H_
#include "pearson.h"
#ifdef STAT_PEARSON

#include <iostream>

namespace network {
namespace pearson {
  // ******************************************************
  class Pearson {
public:
    double pearson, InIn, InOut, OutIn, OutOut;
    double No, NoInIn, NoInOut, NoOutIn, NoOutOut;
    double rho, rhoInIn, rhoInOut, rhoOutIn, rhoOutOut;

    VDouble nodeNeiAveDeg, nodeNeiAveDegIn,
        nodeNeiAveDegOut; // [nodeSize]   各点的邻居平均度
    VDouble neiAveDeg, neiAveDegInIn, neiAveDegInOut, neiAveDegOutIn,
        neiAveDegOutOut; // [degSize]    各度的邻居平均度
    VDouble nodeNeiAveNo, nodeNeiAveNoInIn, nodeNeiAveNoInOut,
        nodeNeiAveNoOutIn,
        nodeNeiAveNoOutOut; // [nodeSize]   各点的邻居编号平均值
    VDouble neiAveNo, neiAveNoInIn, neiAveNoInOut, neiAveNoOutIn,
        neiAveNoOutOut; // [degSize]    各度的邻居编号平均值

    Pearson(void);
    // friend std::ostream& operator<<(std::ostream& os, const Pearson&
    // pearson);
    int save_params(std::ostream& os, const int dirFlag = 0) const;
    int save_params(const char* name = NULL, const int dirFlag = 0) const;
    int save_data(const char* name = NULL, const int dirFlag = 0,
        const char priChar = '\n', const char priChar2 = '\t') const;
    int save(const char* name = NULL, const int dirFlag = 0,
        const char priChar = '\n', const char priChar2 = '\n') const;
    int read_params_1(std::string& s, std::istream& is);
    Pearson& clear(void);
  };
}
}

// ******************************************************
std::ostream& operator<<(
    std::ostream& os, const network::pearson::Pearson& pearson);

#endif //
#endif // _H_
