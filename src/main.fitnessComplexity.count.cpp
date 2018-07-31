#include "main.h"
#ifdef MAIN_FITNESS_COMPLEXITY_COUNT

#include "common.h"
#include "networks.h"
using namespace std;
// ******************************************************

int main_fitness_complexity_count(int argc, char** argv)
{
  const string DIR0 = "data/complexity/OEC.sitc_rev2/",
               DIR_DATA0 = DIR0 + "data0/", DIR_DATA = DIR0 + "data/",
               DIR_INFO = DIR0 + "info/";
  const size_t YEAR1 = 2001, YEAR2 = 2014 + 1;
  const string methods[] = { "mass", "heat", "hybrid" };
  // const string methods[] = { "hybrid" };
  const size_t NMETHOD = sizeof(methods) / sizeof(methods[0]);

  VNodeType cIndex, pIndex;
  VString gNames;
  {
    ERROR_TEST(common_read1_0(
        (DIR_INFO + "country.index.export.not0.txt").c_str(), cIndex));
    ERROR_TEST(common_read1_0(
        (DIR_INFO + "product.index.export.not0.txt").c_str(), pIndex));
    ERROR_TEST(common_read1_0(
        (DIR_INFO + "country.namesFull.gdp.txt").c_str(), gNames));
  }
  const size_t NC = cIndex.size(), NP = pIndex.size(), NG = gNames.size();
  cout << NC << "\t" << NP << "\t" << NG << endl;

  for (size_t year = YEAR1; year < YEAR2; year++) {
    INFORM(year);

    VVNodeType mcp;
    VNodeType mcpDeg;
    VDouble pc;
    {
      ERROR_TEST(common_read2_0(
          (DIR_DATA + to_string(year) + ".mcp.txt").c_str(), mcp));
      ERROR_TEST(mcp.size() != NC);
      for (NodeType c = 0; c < NC; c++)
        ERROR_TEST(mcp[c].size() != NP);
      ERROR_TEST(common_read1_0(
          (DIR_DATA + to_string(year) + ".country.product.mcp.deg.txt")
              .c_str(),
          mcpDeg));
      ERROR_TEST(common_read1_0(
          (DIR_DATA + to_string(year) + ".product.complexity.txt").c_str(),
          pc));
      save_val_2_rankScale(
          pc, (DIR_DATA + to_string(year) + ".product.complexity").c_str());
    }

    if (year <= YEAR1)
      continue;
    //**********************************************************
    // count 2 var
    VVNodeType mcp0;
    VNodeType mcpDeg0;
    {
      ERROR_TEST(common_read2_0(
          (DIR_DATA + to_string(year - 1) + ".mcp.txt").c_str(), mcp0));
      ERROR_TEST(common_read1_0(
          (DIR_DATA + to_string(year - 1) + ".country.product.mcp.deg.txt")
              .c_str(),
          mcpDeg0));
    }

    VVNodeType mcpNew, mcpRemain;
    VNodeType mcpNewDeg;
    {
      count_mcpNew(mcp0, mcp, mcpNew, mcpRemain);
      common_save2(
          (DIR_DATA + to_string(year) + ".country.product.new.txt").c_str(),
          mcpNew);
      common_save2(
          (DIR_DATA + to_string(year) + ".country.product.remain.txt")
              .c_str(),
          mcpRemain);
      p2p_2_nodeDeg(mcpNewDeg, mcpNew);
      common_save1(
          (DIR_DATA + to_string(year) + ".country.product.new.deg.txt")
              .c_str(),
          mcpNewDeg, '\n');
    }

    for (size_t iMethod = 0; iMethod < NMETHOD; iMethod++) {
      string method = methods[iMethod];
      cout << "\t" << method << endl;

      Networks net;
      net.saveName = DIR_DATA + to_string(year);
      common_read2_0(
          (DIR_DATA + to_string(year) + "." + method + ".rcm.txt").c_str(),
          net.recommend.rcm);
      ERROR_TEST(net.recommend.rcm.size() != NC);


    } // year
  }   // method

  return 0;
}

// ******************************************************
#endif
