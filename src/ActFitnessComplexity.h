#ifndef ACT_FITNESS_COMPLEXITY_H
#define ACT_FITNESS_COMPLEXITY_H

#include "net.h"

#ifdef ACT_FITNESS_COMPLEXITY
// *******************************************************
template <typename T, typename T2>
int export_2_Mcp(
    const std::vector<std::vector<T>>& e, std::vector<std::vector<T2>>& mcp);
template <typename T>
int Mcp_2_C_P(
    const std::vector<std::vector<T>>& mcp, VVNodeType& pc, VVNodeType& pp);
template <typename T>
int Mcp_2_FC(
    VDouble& Fc, VDouble& Cp, const std::vector<std::vector<T>>& Mcp);

int count_deg(const VVNodeType& mcp, VNodeType& deg, const char* name = NULL);
int count_product_deg(
    const VVNodeType& mcp, VNodeType& deg, const char* name = NULL);
int count_mcpNew(const VVNodeType& mcp0, const VVNodeType& mcp,
    VVNodeType& mcpNew, VVNodeType& mcpRemain);
int count_pcNewRankV2(const VNodeType& pcRankV2, const VVNodeType& mcpNew,
    VVNodeType& pcNewRankV2);
int count_pcNewRemainRankV2(const VNodeType& pcRankV2, const VVNodeType& mcp,
    const VVNodeType& mcpNew, VVNodeType& pcNewRemainRankV2);
int count_newScale(const size_t NC, const size_t NP, const VNodeType& deg,
    const VVNodeType& newRemainRank, VVDouble& newScale,
    const char* name = NULL);
int count_newRank(const VVDouble& rcm, const size_t NC, const size_t NP,
    const VVNodeType& mcpNew, VVNodeType& newRank, const char* name = NULL);
int count_newRemainRank(const VVDouble& rcm, const size_t NC, const size_t NP,
    const VVNodeType& mcp, const VVNodeType& mcpNew,
    VVNodeType& newRemainRank, const char* name = NULL);

int cal_val_2_rankScale(const VDouble& val, VNodeType& rk, VNodeType& rkIndex,
    VNodeType& rkV2, VNodeType& rkV2Index, VDouble& rkScale, const size_t N);
int cal_val_2_rankScale_p(const VDouble& val, const NodeType* p,
    VNodeType& rk, VNodeType& rkIndex, VNodeType& rkV2, VNodeType& rkV2Index,
    VDouble& rkScale, const size_t N);

template <typename T>
int count_rankingScore(const VVDouble& rcm, const size_t NC, const size_t NP,
    const std::vector<std::vector<T> >& mcp,
    const std::vector<std::vector<T> >& mcp2, VDouble& rankingScore,
    const char* name);

// 筛选进出口数据的国家和产品名
int filter_trade_name(const char* tradeFilename, const char* countryFilename,
    const char* productFilename);
int filter_trade_name_OEC(const char* tradeFilename,
    const char* countryFilename, const char* productFilename,
    const NodeType YEAR1 = 2001, const NodeType YEAR2 = 2015);
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
    const char* dirSave, const NodeType YEAR1 = 2001,
    const NodeType YEAR2 = 2015);
int filter_sum_trade_NBER_wtf(const char* tradeFilename,
    const char* countryFilename, const char* productFilename,
    const char* saveName);
int filter_sum_trade_NBER_wtf2(const char* tradeFilename,
    const char* countryFilename, const char* productFilename,
    const char* saveName);

// 筛选进出口和 gdp 的共同国家名
int filter_export_gdp_country_name(
    const char* exportNames, const char* gdpNames, const char* savePrefix);
int filter_index_same_all(const char* namesFull, const char* sameAll);
int filter_index_same_all_OEC(const char* namesFull);
int filter_index_same_not0_OEC(
    const char* namesFull, const char* countryNot0);
int filter_index_gdp_0(const char* gdpFile, const char* cIndexFile);
int filter_index_export_0_OEC(const char* epDIR, const char* cIndexFile,
    const char* pIndexFile, const char* countryFilename = NULL,
    const char* productFilename = NULL, const NodeType YEAR1 = 2001,
    const NodeType YEAR2 = 2015);
int filter_index_export_0_NBER_wtf(const char* epDIR, const char* cIndexFile,
    const char* pIndexFile, const char* pIndexFileAll = NULL,
    const NodeType YEAR1 = 1984, const NodeType YEAR2 = 2001,
    const NodeType YEAR0 = 1993);
int filter_index_export_gdp(const char* gdpIndexFile0,
    const char* gdpIndexFile, const char* gdpIndexFile2,
    const char* exportIndexFile, const char* exportIndexFile0,
    const char* exportIndexFile2);

int filter_data_export(const char* exportDIR, const char* countryIndexFile,
    const char* productIndexFile, const char* DATA_DIR, const NodeType YEAR1,
    const NodeType YEAR2);
int filter_data(const char* gdpFile, const char* gdpIndexFile,
    const char* exportFile, const char* countryIndexFile,
    const char* productIndexFile, const char* DATA_DIR);
int filter_common_gdp(const char* name, const char* dir, const size_t YEAR1,
    const size_t YEAR2, size_t YEAR0);

// *******************************************************
#include "ActFitnessComplexity.template.h"
#endif // ACT_FITNESS_COMPLEXITY
#endif // _H
