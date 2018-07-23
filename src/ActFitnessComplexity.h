#ifndef ACT_FITNESS_COMPLEXITY_H
#define ACT_FITNESS_COMPLEXITY_H

#include "net.h"

#ifdef ACT_FITNESS_COMPLEXITY
// *******************************************************
template <typename T, typename T2>
int export_2_Mcp(const std::vector<std::vector<T> >& e,
    std::vector<std::vector<T2> >& mcp);
template <typename T>
int Mcp_2_C_P(
    const std::vector<std::vector<T> >& mcp, VVNodeType& pc, VVNodeType& pp);
template <typename T>
int Mcp_2_FC(
    VDouble& Fc, VDouble& Cp, const std::vector<std::vector<T> >& Mcp);

int count_k1(const VVNodeType& mcp, VNodeType& k1, const char* name = NULL);
int count_product_k1(
    const VVNodeType& mcp, VNodeType& k1, const char* name = NULL);
int count_mcpNew(const NodeType NC, const NodeType NP, const VVNodeType& mcp,
    const VVNodeType& mcp2, VVNodeType& mcpNew, const char* name = NULL);
int count_kNew(
    VNodeType& kNew, const VVNodeType& mcpNew, const char* name = NULL);
int count_pcNewRank(const VDouble& pc, const size_t NC, const size_t NP,
    const VVNodeType& mcpNew, VVNodeType& pcNewRank, const char* name = NULL);
int count_pcNewRemainRank(const VDouble& pc, const size_t NC, const size_t NP,
    const VVNodeType& mcp, const VVNodeType& mcpNew,
    VVNodeType& pcNewRemainRank, const char* name = NULL);
int count_newScale(const size_t NC, const size_t NP, const VNodeType& k1,
    const VVNodeType& newRemainRank, VVDouble& newScale,
    const char* name = NULL);
int count_newRank(const VVDouble& rcm, const size_t NC, const size_t NP,
    const VVNodeType& mcpNew, VVNodeType& newRank, const char* name = NULL);
int count_newRemainRank(const VVDouble& rcm, const size_t NC, const size_t NP,
    const VVNodeType& mcp, const VVNodeType& mcpNew,
    VVNodeType& newRemainRank, const char* name = NULL);

// 筛选进出口数据的国家和产品名
int filter_trade_name(const char* tradeFilename, const char* countryFilename,
    const char* productFilename);
int filter_trade_name_OEC(const char* tradeFilename,
    const char* countryFilename, const char* productFilename,
    const NodeType YEAR1 = 1962, const NodeType YEAR2 = 2015);
int filter_trade_name_NBERUN_wtf(const char* tradeFilename,
    const char* countryFilename, const char* productFilename,
    const char* countryFilename0 = NULL, const char* productFilename0 = NULL);
int filter_trade_name_NBERUN_wtf2(const char* tradeFilename,
    const char* countryFilename, const char* productFilename,
    const char* countryFilename0 = NULL, const char* productFilename0 = NULL);

// 合并进出口数据
int read_country_names(
    const char* countryFilename, NodeType& NC, VNodeType& cVal);
int read_product_names(
    const char* productFilename, NodeType& NP, VNodeType& pVal);
int filter_sum_trade(const char* tradeFilename, const char* countryFilename,
    const char* productFilename, const char* dirSave);
int filter_sum_trade_OEC(const char* tradeFilename,
    const char* countryFilename, const char* productFilename,
    const char* dirSave, const NodeType YEAR1 = 1962,
    const NodeType YEAR2 = 2015);
int filter_sum_trade_NBER_wtf(const char* tradeFilename,
    const char* countryFilename, const char* productFilename,
    const char* saveName);
int filter_sum_trade_NBER_wtf2(const char* tradeFilename,
    const char* countryFilename, const char* productFilename,
    const char* saveName);

// 筛选进出口和 gdp 的共同国家名
int filter_export_gdp_country_name(const char* exportNames,
    const char* exportNames3c, const char* gdpNames, const char* savePrefix);
int filter_index_same_all(const char* namesFull, const char* sameAll);
int filter_index_gdp_0(const char* gdpFile, const char* indexFile);
int filter_index_export_0(const char* epDIR, const char* indexFile,
    const char* pdIndexFile, const NodeType YEAR1 = 1995,
    const NodeType YEAR2 = 2014);
int filter_index_export_0_NBER_wtf(const char* epDIR, const char* indexFile,
    const char* pdIndexFile, const NodeType YEAR1 = 1962,
    const NodeType YEAR2 = 2000, const NodeType YEAR0 = 1993);
int filter_index_export_gdp(const char* gdpIndexFile0,
    const char* gdpIndexFile, const char* gdpIndexFile2,
    const char* exportIndexFile, const char* exportIndexFile0,
    const char* exportIndexFile2);
int filter_data_export(const char* exportDIR, const char* countryIndexFile,
    const char* productIndexFile, const char* DATA_DIR,
    const NodeType YEAR1 = 1995, const NodeType YEAR2 = 2014,
    const NodeType YEAR0 = 1993);
int filter_data(const char* gdpFile, const char* gdpIndexFile,
    const char* exportFile, const char* countryIndexFile,
    const char* productIndexFile, const char* DATA_DIR);

// *******************************************************
#include "ActFitnessComplexity.template.h"
#endif // ACT_FITNESS_COMPLEXITY
#endif // _H
