#ifndef DYNAMICS__SPREAD__NETWORK_H_
#define DYNAMICS__SPREAD__NETWORK_H_
#include "spread.h"
#ifdef ACT_SPREAD

#include <iostream>

namespace network {
class Networks;
namespace spread {
  // ******************************************************
  class Spread {
public:
    std::string mode;
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
    // friend std::ostream& operator<<(std::ostream& os, const Spread&
    // spread);
    int init(const Networks& net);
    int check(const Networks& net);
    int save_params(std::ostream& os) const;
    int save_params(const char* name = NULL) const;
    int save_data(const char* name, const char priChar = '\n') const;
    int save(const char* name = NULL) const;
    int read_params_1(std::string& s, std::istream& is);
    Spread& clear(void);

    int spread_same(const Networks& net);
    int spread_diff(const Networks& net);
    int calData(void);

private:
    void update_nei1(const NodeType nj);
    void update_nei(const Networks& net, const NodeType ni);
  };
}
}

// ******************************************************
std::ostream& operator<<(
    std::ostream& os, const network::spread::Spread& spread);

#endif // ACT_SPREAD
#endif // NETWORK_ACT_SPREAD_H
