#ifndef NETWORK_STAT_MODULARITY_H
#define NETWORK_STAT_MODULARITY_H
#include "StatModularity.h"
#ifdef STAT_MODULARITY

#include <iostream>

// ******************************************************
class Stat_modularity {
  public:
    double coef;       // 网络分组系数Q
    VDouble NodeCoef;  // 节点分组系数P
    VNodeType Val;     // 各节点分组的序号
    VNodeType Stk;     // 按分组序号排列的节点编号
    VNodeType Num;     // 节点在moduStk中的位置
    VRNodeType Range;  // 各分组的范围
    VVLinkType LKK;    // 不同组之间连边数目

    Stat_modularity(void);
    friend std::ostream& operator<<(std::ostream& os,
        const Stat_modularity& modularity);
    int save_params(std::ostream& os) const;
    int save_params(const char* name = NULL) const;
    int save_data(const char* name = NULL, const char priChar = '\n',
        const char priChar2 = '\t') const;
    int save_Stk(const char* name = NULL, const char priChar2 = '\t') const;
    int save(const char* name = NULL, const char priChar = '\n',
        const char priChar2 = '\n') const;
    int read_params_1(std::string& s, std::istream& is);
    Stat_modularity& clear(void);
};
std::ostream& operator<<(std::ostream& os, const Stat_modularity& modularity);

// ******************************************************
#endif  // STAT_MODULARITY
#endif  // NETWORK_NET_MODULARITY_H

