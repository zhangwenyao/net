#ifndef NETWORK_ACT_SPREAD_H
#define NETWORK_ACT_SPREAD_H
#include "ActSpread.h"
#ifdef ACT_SPREAD

#include <iostream>

//**//****************************************************//*
class Act_spread {
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

    Act_spread(void);
    friend std::ostream& operator<<(std::ostream& os, const Act_spread& spread);
    int save_params(std::ostream& os) const;
    int save_params(const char* name = NULL) const;
    int save_data(const char* name = NULL) const;
    int save(const char* name = NULL) const;
    int read_params_1(std::string& s, std::istream& is);
    Act_spread& clear(void);
};
std::ostream& operator<<(std::ostream& os, const Act_spread& spread);

//**//****************************************************//*
#endif  // ACT_SPREAD
#endif  // NETWORK_ACT_SPREAD_H

