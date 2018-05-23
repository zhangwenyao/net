#ifndef ACT_FITNESS_COMPLEXITY_H
#define ACT_FITNESS_COMPLEXITY_H

#include "net.h"

#ifdef ACT_FITNESS_COMPLEXITY
// *******************************************************
template <typename T, typename T2>
int exp_2_Mcp(const std::vector<std::vector<T> >& e,
    std::vector<std::vector<T2> >& mcp);
template <typename T>
int Mcp_2_C_P(
    const std::vector<std::vector<T> >& mcp, VVNodeType& pc, VVNodeType& pp);
template <typename T>
int Mcp_2_FC(
    VDouble& Fc, VDouble& Cp, const std::vector<std::vector<T> >& Mcp);

int count_k1(const NodeType NC, const NodeType NP, const VVNodeType& mcp,
    VNodeType& k1, const char* name = NULL);
int count_cpNew(const NodeType NC, const NodeType NP, const VVNodeType& mcp,
    const VVNodeType& mcp2, VVNodeType& cpNew, const char* name = NULL);
int count_kNew(
    VNodeType& kNew, const VVNodeType& cpNew, const char* name = NULL);
int count_pcNewRemainRank(const VDouble& pc, const size_t NC, const size_t NP,
    const VVNodeType& mcp, const VVNodeType& cpNew, VVNodeType& rankNew,
    const char* name = NULL);
int count_pcNewScale(const size_t NC, const size_t NP, const VNodeType& k1,
    const VVNodeType& cpNewRemainRank, VVDouble& scale,
    const char* name = NULL);
int count_pcNewRank(const VDouble& pc, const size_t NC, const size_t NP,
    const VVNodeType& cpNew, VVNodeType& rankNew, const char* name = NULL);
int count_newRemainRank(const VVDouble& rcm, const size_t NC, const size_t NP,
    const VVNodeType& mcp, const VVNodeType& cpNew, VVNodeType& newRemainRank,
    const char* name = NULL);
int count_rankNew(const VVDouble& rcm, const size_t NC, const size_t NP,
    const VVNodeType& cpNew, VVNodeType& rankNew, const char* name = NULL);

// 筛选出国家和商品名
int filter_trade_name(const char* tradeFilename, const char* countryFilename,
    const char* productFilename);

int read_country_names(
    const char* countryFilename, NodeType& NC, VNodeType& cVal);
int read_product_names(
    const char* productFilename, NodeType& NP, VNodeType& pVal);

// 合并进出口数据
int filter_sum_trade(const char* tradeFilename, const char* countryFilename,
    const char* productFilename, const char* dirSave);

int filter_index(const NodeType N, VVNodeType& indexs, VNodeType& index);

// *******************************************************
#include "ActFitnessComplexity.template.h"
#endif // ACT_FITNESS_COMPLEXITY
#endif // _H
