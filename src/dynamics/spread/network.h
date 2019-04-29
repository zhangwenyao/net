#ifndef DYNAMICS__SPREAD__NETWORK_H_
#define DYNAMICS__SPREAD__NETWORK_H_
#include "spread.h"
#ifdef ACT_SPREAD

#include <iostream>

namespace network {
namespace spread {
  // ******************************************************
  class Spread {
public:
    NodeType SOURCE_HEAD, SOURCE_NULL;
    std::vector<NodeType> source, nei, num, stk, time;
    NodeType spreadSize;
    NodeType head, nei1, nei0;
    LinkType neiCountSize;

    double prob;
    std::vector<double> prob_rand;

    NodeType dataSize;
    std::vector<NodeType> data_node, data_time;

    Spread(void);
    //friend std::ostream& operator<<(std::ostream& os, const Spread& spread);
    int save_params(std::ostream& os) const;
    int save_params(const char* name = NULL) const;
    int save_data(const char* name = NULL) const;
    int save(const char* name = NULL) const;
    int read_params_1(std::string& s, std::istream& is);
    Spread& clear(void);
  };
}
}

// ******************************************************
std::ostream& operator<<(
    std::ostream& os, const network::spread::Spread& spread);

#endif // ACT_SPREAD
#endif // NETWORK_ACT_SPREAD_H
