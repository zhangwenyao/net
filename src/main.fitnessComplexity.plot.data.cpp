#include "main.h"
#ifdef MAIN_FITNESS_COMPLEXITY_PLOTDATA

#include "common.h"
#include "networks.h"
using namespace std;
// ********************************************************

int main_fitness_complexity_plotdata(int argc, char** argv)
{
  const string DIR0 = "data/complexity/OEC.sitc_rev2/",
               DIR_DATA0 = DIR0 + "data0/", DIR_DATA = DIR0 + "data/",
               DIR_INFO = DIR0 + "info/", DIR_COMMON = DIR0 + "dataCommon/",
               DIR_PLOT_DATA = DIR0 + "plotData/";
  const size_t YEAR1 = 2001, YEAR2 = 2014 + 1;
  const string methods[] = { "mass", "heat", "hybrid" };
  const size_t NMETHOD = sizeof(methods) / sizeof(methods[0]);

  VNodeType cIndex, pIndex, gIndex, cIndex0;
  ERROR_TEST(common_read1_0(
      (DIR_INFO + "country.namesFull.common.trade.index.not0.txt").c_str(),
      cIndex));
  ERROR_TEST(common_read1_0(
      (DIR_INFO + "country.namesFull.common.gdp.index.not0.txt").c_str(),
      gIndex));
  ERROR_TEST(common_read1_0(
      (DIR_INFO + "product.index.export.not0.txt").c_str(), pIndex));
  ERROR_TEST(common_read1_0(
      (DIR_INFO + "country.index.export.not0.txt").c_str(), cIndex0));
  const size_t NG = gIndex.size(), NC = cIndex.size(), NP = pIndex.size(),
               NC0 = cIndex0.size();
  cout << NG << "\t" << NC0 << "\t" << NP << endl;
  ERROR_TEST(NG != NC);

  VVLinkType gdps0;
  ERROR_TEST(
      common_read2_0((DIR_DATA0 + "2001-2014.gdps.txt").c_str(), gdps0));
  VVDouble gdpGrows0;
  ERROR_TEST(common_read2_0(
      (DIR_DATA0 + "2001-2016.gdpGrows.txt").c_str(), gdpGrows0));

  for (size_t year = YEAR1; year < YEAR2; year++) {

    VDouble gdp, gdpScale;
    VDouble gdpGrow, cf, cfScale, cpcMean;
    VVNodeType mcp, mcpMcp;
    VNodeType mcpDeg;
    VDouble pc, pcScale;
    {
      // gdp
      for (size_t i = 0, g; i < NG; i++) {
        g = gIndex[i];
        gdp.push_back(gdps0[g][year - 2001]);
        gdpGrow.push_back(gdpGrows0[g][year - 2001]);
      }
      ERROR_TEST(common_save1(
          (DIR_COMMON + to_string(year) + ".gdp.txt").c_str(), gdp, '\n'));
      ERROR_TEST(common_save1(
          (DIR_COMMON + to_string(year) + ".gdpGrow.txt").c_str(), gdpGrow,
          '\n'));
      save_val_2_rankScale(
          gdp, (DIR_COMMON + to_string(year) + ".gdp").c_str());
      ERROR_TEST(common_read1_0(
          (DIR_COMMON + to_string(year) + ".gdp.rankLessV2.scale.txt")
              .c_str(),
          gdpScale));

      // cp, mcp
      VDouble cf0, cfScale0;
      VVNodeType mcp0, mcpMcp0;
      VNodeType mcpDeg0;
      ERROR_TEST(common_read1_0(
          (DIR_DATA + to_string(year) + ".country.fitness.txt").c_str(),
          cf0));
      ERROR_TEST(common_read1_0((DIR_DATA + to_string(year)
                                    + ".country.fitness.rankLessV2.scale.txt")
                                    .c_str(),
          cfScale0));
      ERROR_TEST(common_read2_0(
          (DIR_DATA + to_string(year) + ".mcp.txt").c_str(), mcp0));
      ERROR_TEST(common_read1_0(
          (DIR_DATA + to_string(year) + ".country.product.mcp.deg.txt")
              .c_str(),
          mcpDeg0));
      ERROR_TEST(common_read2_0(
          (DIR_DATA + to_string(year) + ".country.product.mcp.txt").c_str(),
          mcpMcp0));
      for (size_t cc = 0, c; cc < NC; ++cc) {
        c = cIndex[cc];
        cf.push_back(cf0[c]);
        cfScale.push_back(cfScale0[c]);
        mcp.push_back(mcp0[c]);
        mcpDeg.push_back(mcpDeg0[c]);
        mcpMcp.push_back(mcpMcp0[c]);
      }
      ERROR_TEST(common_save1(
          (DIR_COMMON + to_string(year) + ".country.fitness.txt").c_str(), cf,
          '\n'));
      ERROR_TEST(common_save1((DIR_COMMON + to_string(year)
                                  + ".country.fitness.rankLessV2.scale.txt")
                                  .c_str(),
          cfScale, '\n'));
      ERROR_TEST(common_save2(
          (DIR_COMMON + to_string(year) + ".mcp.txt").c_str(), mcp));
      ERROR_TEST(common_save1(
          (DIR_COMMON + to_string(year) + ".country.product.mcp.deg.txt")
              .c_str(),
          mcpDeg, '\n'));
      ERROR_TEST(common_save2(
          (DIR_COMMON + to_string(year) + ".country.product.mcp.txt").c_str(),
          mcpMcp));

      ERROR_TEST(common_read1_0(
          (DIR_DATA + to_string(year) + ".product.complexity.txt").c_str(),
          pc));
      ERROR_TEST(
          common_read1_0((DIR_DATA + to_string(year)
                             + ".product.complexity.rankLessV2.scale.txt")
                             .c_str(),
              pcScale));
    }

    if (year <= YEAR1)
      continue;
    // ************************************************************

    VVNodeType mcp0;
    {
      ERROR_TEST(common_read2_0(
          (DIR_COMMON + to_string(year - 1) + ".mcp.txt").c_str(), mcp0));
    }

    VVNodeType mcpNew;
    {
      VVNodeType mcpNew0;
      VDouble pcNewMean, pcNewMeanDev, pcNewMean0, pcNewMeanDev0;
      VDouble pcMcpMean, pcMcpMeanDev, pcMcpMean0, pcMcpMeanDev0;
      ERROR_TEST(common_read2_0(
          (DIR_DATA + to_string(year) + ".country.product.new.txt").c_str(),
          mcpNew0));
      common_read1_0((DIR_DATA + to_string(year)
                         + ".country.product.complexity.new.mean.txt")
                         .c_str(),
          pcNewMean0);
      common_read1_0((DIR_DATA + to_string(year)
                         + ".country.product.complexity.new.dev.txt")
                         .c_str(),
          pcNewMeanDev0);
      common_read1_0((DIR_DATA + to_string(year)
                         + ".country.product.complexity.mcp.mean.txt")
                         .c_str(),
          pcMcpMean0);
      common_read1_0((DIR_DATA + to_string(year)
                         + ".country.product.complexity.mcp.dev.txt")
                         .c_str(),
          pcMcpMeanDev0);

      for (size_t cc = 0, c; cc < NC; ++cc) {
        c = cIndex[cc];
        mcpNew.push_back(mcpNew0[c]);
        pcNewMean.push_back(pcNewMean0[c]);
        pcNewMeanDev.push_back(pcNewMeanDev0[c]);
        pcMcpMean.push_back(pcMcpMean0[c]);
        pcMcpMeanDev.push_back(pcMcpMeanDev0[c]);
      }

      common_save2(
          (DIR_COMMON + to_string(year) + ".country.product.new.txt").c_str(),
          mcpNew);
      common_save1((DIR_COMMON + to_string(year)
                       + ".country.product.complexity.new.mean.txt")
                       .c_str(),
          pcNewMean, '\n');
      common_save1((DIR_COMMON + to_string(year)
                       + ".country.product.complexity.new.dev.txt")
                       .c_str(),
          pcNewMeanDev, '\n');
      common_save1((DIR_COMMON + to_string(year)
                       + ".country.product.complexity.mcp.mean.txt")
                       .c_str(),
          pcMcpMean, '\n');
      common_save1((DIR_COMMON + to_string(year)
                       + ".country.product.complexity.mcp.dev.txt")
                       .c_str(),
          pcMcpMeanDev, '\n');
    }

    VVDouble rcm0[NMETHOD], rcmNewScale0[NMETHOD];
    for (size_t i = 0; i < NMETHOD; i++) {
      string method = methods[i];
      common_read2_0(
          (DIR_DATA + to_string(year) + "." + method + ".rcm.txt").c_str(),
          rcm0[i]);
      common_read2_0(
          (DIR_DATA + to_string(year) + "." + method + ".rcm.newScale.txt")
              .c_str(),
          rcmNewScale0[i]);

      VDouble rks, rksDev, rks0, rksDev0;
      ERROR_TEST(common_read1_0((DIR_DATA + to_string(year) + "." + method
                                    + ".country.rankingScore.txt")
                                    .c_str(),
          rks0));
      ERROR_TEST(common_read1_0((DIR_DATA + to_string(year) + "." + method
                                    + ".country.rankingScoreDev.txt")
                                    .c_str(),
          rksDev0));
      for (size_t cc = 0, c; cc < NC; ++cc) {
        c = cIndex[cc];
        rks.push_back(rks0[c]);
        rksDev.push_back(rksDev0[c]);
      }
      ERROR_TEST(common_save1((DIR_COMMON + to_string(year) + "." + method
                                  + ".country.rankingScore.txt")
                                  .c_str(),
          rks, '\n'));
      ERROR_TEST(common_save1((DIR_COMMON + to_string(year) + "." + method
                                  + ".country.rankingScoreDev.txt")
                                  .c_str(),
          rksDev, '\n'));
      for (size_t cc = 0, c; cc < NC; ++cc) {
        c = cIndex[cc];
      }
    } // method

    {
      ofstream os((DIR_COMMON + to_string(year) + ".new.datas.txt").c_str());
      os << "year\tproductId\trecRankMass\trecRankHeat\trecRankHydrid\t"
            "complexity\tcomplexityRank\tcountryId\tfitness\tfitnessRank"
            "\tGDP\tGDPRank\n";
      for (size_t c = 0, cc; c < NC; c++) {
        if (mcpNew[c].size() <= 0)
          continue;
        for (size_t i = 0, p, mi = 0; i < mcpNew[c].size(); i++) {
          p = mcpNew[c][i];
          for (mi = 0; mcpMcp[c][mi] < p; ++mi)
            continue;
          cc = cIndex[c];
          os << year << '\t' << p << '\t' << rcmNewScale0[0][cc][p] << '\t'
             << rcmNewScale0[1][cc][p] << '\t' << rcmNewScale0[2][cc][p]
             << '\t' << pc[p] << '\t' << pcScale[p] << '\t' << c << '\t'
             << cf[c] << '\t' << cfScale[c] << '\t' << gdp[c] << '\t'
             << gdpScale[c] << '\n';
        }
      }
      os.close();
    }
  } // year

  return 0;
}

// ********************************************************
#endif
