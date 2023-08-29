#ifndef STATISTICS__MODULARITY__NETWORK_H_
#define STATISTICS__MODULARITY__NETWORK_H_
#include "modularity.h"
#ifdef STAT_MODULARITY

#include <iostream>

namespace network {
namespace modularity {
  // ******************************************************
  class Modularity {
public:
    double coef;      // 网络分组系数Q
    VDouble NodeCoef; // 节点分组系数P
    VNodeType Val;    // 各节点分组的序号
    VNodeType Stk;    // 按分组序号排列的节点编号
    VNodeType Num;    // 节点在moduStk中的位置
    VRNodeType Range; // 各分组的范围
    VVLinkType LKK;   // 不同组之间连边数目

    Modularity(void);
    // friend std::ostream& operator<<(std::ostream& os,
    // const Modularity& modularity);
    int save_params(std::ostream& os) const;
    int save_params(const char* name = NULL) const;
    int save_data(const char* name = NULL, const int dirFlag = 0,
        const char priChar = '\n', const char priChar2 = '\t') const;
    int save_Stk(const char* name = NULL, const char priChar2 = '\t') const;
    int save(const char* name = NULL, const int dirFlag = 0,
        const char priChar = '\n', const char priChar2 = '\t') const;
    int read_params_1(std::string& s, std::istream& is);
    Modularity& clear(void);
  };
}
}

// ******************************************************
std::ostream& operator<<(
    std::ostream& os, const network::modularity::Modularity& modularity);

#endif // STAT_MODULARITY
#endif // NETWORK_NET_MODULARITY_H
