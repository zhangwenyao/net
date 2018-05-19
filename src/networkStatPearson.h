#ifndef NETWORK_STAT_PEARSON_H
#define NETWORK_STAT_PEARSON_H
#include "StatPearson.h"
#ifdef STAT_PEARSON

#include <iostream>

// ******************************************************
class Stat_pearson {
  public:
    double pearson, InIn, InOut, OutIn, OutOut;
    double No, NoInIn, NoInOut, NoOutIn, NoOutOut;
    double rho, rhoInIn, rhoInOut, rhoOutIn, rhoOutOut;

    VDouble nodeNeiAveDeg, nodeNeiAveDegIn,
            nodeNeiAveDegOut;  // [nodeSize]   各点的邻居平均度
    VDouble neiAveDeg, neiAveDegInIn, neiAveDegInOut, neiAveDegOutIn,
            neiAveDegOutOut;  // [degSize]    各度的邻居平均度
    VDouble nodeNeiAveNo, nodeNeiAveNoInIn, nodeNeiAveNoInOut, nodeNeiAveNoOutIn,
            nodeNeiAveNoOutOut;  // [nodeSize]   各点的邻居编号平均值
    VDouble neiAveNo, neiAveNoInIn, neiAveNoInOut, neiAveNoOutIn,
            neiAveNoOutOut;  // [degSize]    各度的邻居编号平均值

    Stat_pearson(void);
    friend std::ostream& operator<<(std::ostream& os,
        const Stat_pearson& pearson);
    int save_params(std::ostream& os, const int dirFlag = 0) const;
    int save_params(const char* name = NULL, const int dirFlag = 0) const;
    int save_data(const char* name = NULL, const int dirFlag = 0, const char priChar = '\n',
        const char priChar2 = '\t') const;
    int save(const char* name = NULL, const int dirFlag = 0,
        const char priChar = '\n', const char priChar2 = '\n') const;
    int read_params_1(std::string& s, std::istream& is);
    Stat_pearson& clear(void);
};
std::ostream& operator<<(std::ostream& os, const Stat_pearson& pearson);

// ******************************************************
#endif  // STAT_KENDALL
#endif  // NETWORK_STAT_KENDALL_H
