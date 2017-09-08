#ifndef NETWORK_STAT_BETWEENNESS_H
#define NETWORK_STAT_BETWEENNESS_H
#include "StatBetweenness.h"
#ifdef STAT_BETWEENNESS

#include <iostream>

//**//****************************************************//*
class Stat_betweenness {
  public:
    double meanNode, meanEdge;  // 平均介数
    VDouble betwNode;           // 各点介数
    VVDouble betwEdge;          // 各边介数
    VVDistType minDistMatr;     // 最短距离
    VDouble minDistMean;        // 平均最短距离

    Stat_betweenness(void);
    friend std::ostream& operator<<(std::ostream& os,
        const Stat_betweenness& betweenness);
    int save_params(std::ostream& os) const;
    int save_params(const char* name = NULL) const;
    int save_data(const char* name = NULL, const char priChar = '\n',
        const char priChar2 = '\t') const;
    int save(const char* name = NULL, const char priChar = '\n',
        const char priChar2 = '\n') const;
    int read_params_1(std::string& s, std::istream& is);
    Stat_betweenness& clear(void);
};
std::ostream& operator<<(std::ostream& os, const Stat_betweenness& betweenness);

//**//****************************************************//*
#endif  // STAT_BETWEENNESS
#endif  //NETWORK_STAT_BETWEENNESS_H

