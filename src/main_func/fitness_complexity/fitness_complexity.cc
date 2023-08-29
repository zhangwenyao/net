#include "fitness_complexity.h"
#ifdef MAIN_FITNESS_COMPLEXITY_MAIN

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;

// ******************************************************
int main_func::fitness_complexity::fitness_complexity_main(int argc, char** argv)
{
  const string mcp_dir2 = ".mcp.txt",
               mcpDeg_dir2 = ".country.product.mcp.deg.txt",
               cf_dir2 = ".country.fitness.txt",
               pc_dir2 = ".product.complexity.txt",
               cRank_dir2 = ".country.fitness.rank.txt",
               cRankIndex_dir2 = ".country.fitness.rankIndex.txt",
               pRank_dir2 = ".product.complexity.rank.txt",
               pRankIndex_dir2 = ".product.complexity.rankIndex.txt", _;
  for (size_t year = YEAR1; year <= YEAR2; year++) {
    size_t NC, NP;
    // export to mcp
    VVLinkType e;
    _ERR(common_read2_0((DIR_DATA + to_string(year) + ep_dir2).c_str(), e));
    NC = e.size();
    NP = e[0].size();
    INFORM(year, "\t", NC, "\t", NP);

    VVNodeType mcp;
    _ERR(export_2_Mcp(e, mcp));
    _ERR(common_save2((DIR_DATA + to_string(year) + mcp_dir2).c_str(), mcp));
    // common_read2_0((DIR_DATA + y + mcp_dir2).c_str(), mcp);

    VNodeType deg, product_deg;
    _ERR(count_deg(
        mcp, deg, (DIR_DATA + to_string(year) + mcpDeg_dir2).c_str()));
    _ERR(count_product_deg(mcp, product_deg,
        (DIR_DATA + to_string(year) + mcpDeg_dir2).c_str()));

    // Mcp to country fitness & product complexity
    VDouble cf, pc;
    _ERR(Mcp_2_FC(cf, pc, mcp));
    _ERR(common_save1(
        (DIR_DATA + to_string(year) + cf_dir2).c_str(), cf, '\n'));
    _ERR(common_save1(
        (DIR_DATA + to_string(year) + pc_dir2).c_str(), pc, '\n'));

    VNodeType cRank, cRankIndex;
    cRank.resize(cf.size());
    cRankIndex.resize(cf.size());
    for (NodeType i = 0; i < cf.size(); ++i)
      cRank[i] = i;
    common_sort_p_val_less(cRank.begin(), cRank.end(), &cf[0]);
    _ERR(common_save1(
        (DIR_DATA + to_string(year) + cRank_dir2).c_str(), cRank, '\n'));
    for (NodeType i = 0; i < cf.size(); ++i)
      cRankIndex[cRank[i]] = i;
    _ERR(common_save1((DIR_DATA + to_string(year) + cRankIndex_dir2).c_str(),
        cRankIndex, '\n'));

    VNodeType pRank, pRankIndex;
    pRank.resize(pc.size());
    pRankIndex.resize(pc.size());
    for (NodeType i = 0; i < pc.size(); ++i)
      pRank[i] = i;
    common_sort_p_val_less(pRank.begin(), pRank.end(), &pc[0]);
    _ERR(common_save1(
        (DIR_DATA + to_string(year) + pRank_dir2).c_str(), pRank, '\n'));
    for (NodeType i = 0; i < pc.size(); ++i)
      pRankIndex[pRank[i]] = i;
    _ERR(common_save1((DIR_DATA + to_string(year) + pRankIndex_dir2).c_str(),
        pRankIndex, '\n'));

    // break;
  } // year

  return 0;
}

// ******************************************************
#endif
