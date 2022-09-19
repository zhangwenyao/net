#ifndef STATISTICS__CORRELATION2__NETWORK_H_
#define STATISTICS__CORRELATION2__NETWORK_H_
#include "correlation2.h"
#ifdef STAT_CORRELATION2

#include <iostream>

namespace network {
namespace correlation2 {
  // ******************************************************
  class Correlation2 {
public:
    double node, node_spearman, link, link_spearman;
    double InIn, InOut, OutIn, OutOut;
    double No, NoInIn, NoInOut, NoOutIn, NoOutOut;
    double rho, rhoInIn, rhoInOut, rhoOutIn, rhoOutOut;
    VDouble node_correlation2, node_correlation2_spearman;
    VLinkType node_correlation2_size;
    VDouble histogram_val, histogram_mean, histogram_deviation;
    VLinkType histogram_size;
    VDouble histogram_val_spearman0, histogram_mean_spearman0,
        histogram_deviation_spearman0;
    VLinkType histogram_size_spearman0;
    VDouble histogram_val_spearman, histogram_mean_spearman,
        histogram_deviation_spearman;
    VLinkType histogram_size_spearman;

    VDouble nodeNeiAveDeg, nodeNeiAveDegIn,
        nodeNeiAveDegOut; // [nodeSize]   各点的邻居平均度
    VDouble neiAveDeg, neiAveDegInIn, neiAveDegInOut, neiAveDegOutIn,
        neiAveDegOutOut; // [degSize]    各度的邻居平均度
    VDouble nodeNeiAveNo, nodeNeiAveNoInIn, nodeNeiAveNoInOut,
        nodeNeiAveNoOutIn,
        nodeNeiAveNoOutOut; // [nodeSize]   各点的邻居编号平均值
    VDouble neiAveNo, neiAveNoInIn, neiAveNoInOut, neiAveNoOutIn,
        neiAveNoOutOut; // [degSize]    各度的邻居编号平均值

    Correlation2(void);
    // friend std::ostream& operator<<(std::ostream& os, const Correlation2&
    // correlation2);
    int save_params(std::ostream& os, const int dirFlag = 0) const;
    int save_params(const char* name = NULL, const int dirFlag = 0) const;
    int save_data(const char* name = NULL, const int dirFlag = 0,
        const char priChar = '\n', const char priChar2 = '\t') const;
    int save(const char* name = NULL, const int dirFlag = 0,
        const char priChar = '\n', const char priChar2 = '\t') const;
    int read_params_1(std::string& s, std::istream& is);
    Correlation2& clear(void);
  };
}
}

// ******************************************************
std::ostream& operator<<(std::ostream& os,
    const network::correlation2::Correlation2& correlation2);

#endif //
#endif // _H_
