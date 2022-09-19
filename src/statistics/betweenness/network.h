#ifndef STATISTICS__BETWEENNESS__NETWORK_H_
#define STATISTICS__BETWEENNESS__NETWORK_H_
#include "betweenness.h"
#ifdef STAT_BETWEENNESS

#include <iostream>

namespace network {
namespace betweenness {
  // ******************************************************
  class Betweenness {
public:
    double meanNode, meanEdge; // 平均介数
    VDouble betwNode;          // 各点介数
    VVDouble betwEdge;         // 各边介数
    VVDistType minDistMatr;    // 最短距离
    VDouble minDistMean;       // 平均最短距离

    Betweenness(void);
    // friend std::ostream& operator<<(
    // std::ostream& os, const Betweenness& betweenness);
    int save_params(std::ostream& os) const;
    int save_params(const char* name = NULL) const;
    int save_data(const char* name = NULL, const int dirFlag = 0,
        const char priChar = '\n', const char priChar2 = '\t') const;
    int save(const char* name = NULL, const int dirFlag = 0,
        const char priChar = '\n', const char priChar2 = '\t') const;
    int read_params_1(std::string& s, std::istream& is);
    Betweenness& clear(void);
  };
}
}

// ******************************************************
std::ostream& operator<<(
    std::ostream& os, const network::betweenness::Betweenness& betweenness);

#endif // STAT_BETWEENNESS
#endif // NETWORK_STAT_BETWEENNESS_H
