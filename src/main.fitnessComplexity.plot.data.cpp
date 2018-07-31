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
    cout << year << endl;

    VDouble pc;
    {
      ERROR_TEST(common_read1_0(
          (DIR_DATA + to_string(year) + ".product.complexity.txt").c_str(),
          pc));
    }

    VLinkType gdp;
    VNodeType rk;
    VDouble gdpGrow, cf, cpcMean;
    VVNodeType mcp;
    VNodeType mcpDeg;
    {
      // gdp
      for (size_t i = 0, g; i < NG; i++) {
        g = gIndex[i];
        gdp.push_back(gdps0[g][year - 2001]);
        gdpGrow.push_back(gdpGrows0[g][year - 2001]);
        rk.push_back(i);
      }
      ERROR_TEST(common_save1(
          (DIR_COMMON + to_string(year) + ".gdp.txt").c_str(), gdp, '\n'));
      ERROR_TEST(common_save1(
          (DIR_COMMON + to_string(year) + ".gdpGrow.txt").c_str(), gdpGrow,
          '\n'));
      common_sort_p_val_less(&rk[0], &rk[NG], &gdp[0]);
      ERROR_TEST(common_save1(
          (DIR_COMMON + to_string(year) + ".gdp.rankLess.txt").c_str(), rk,
          '\n'));

      // cp, mcp
      VDouble cf0;
      VVNodeType mcp0, cpNew0;
      VNodeType mcpDeg0;
      ERROR_TEST(common_read1_0(
          (DIR_DATA + to_string(year) + ".country.fitness.txt").c_str(),
          cf0));
      ERROR_TEST(common_read2_0(
          (DIR_DATA + to_string(year) + ".mcp.txt").c_str(), mcp0));
      ERROR_TEST(common_read1_0(
          (DIR_DATA + to_string(year) + ".country.product.mcp.deg.txt")
              .c_str(),
          mcpDeg0));
      for (size_t cc = 0, c; cc < NC; ++cc) {
        c = cIndex[cc];
        cf.push_back(cf0[c]);
        mcpDeg.push_back(mcpDeg0[c]);
      }
      ERROR_TEST(common_save1(
          (DIR_COMMON + to_string(year) + ".country.fitness.txt").c_str(), cf,
          '\n'));
      ERROR_TEST(common_save2(
          (DIR_COMMON + to_string(year) + ".mcp.txt").c_str(), mcp));
      ERROR_TEST(common_save1(
          (DIR_COMMON + to_string(year) + ".country.product.mcp.deg.txt")
              .c_str(),
          mcpDeg));
    }

    if (year <= YEAR1)
      continue;
    // ************************************************************

    VVNodeType mcp0;
    {
      ERROR_TEST(common_read2_0(
          (DIR_COMMON + to_string(year - 1) + ".mcp.txt").c_str(), mcp0));
    }

    VVNodeType cpNew;
    {
      VVNodeType cpNew0;
      ERROR_TEST(common_read2_0(
          (DIR_DATA + to_string(year) + ".country.product.new.txt").c_str(),
          cpNew0));

      for (size_t cc = 0, c; cc < NC; ++cc) {
        c = cIndex[cc];
        cpNew.push_back(cpNew0[c]);
      }
    }

    VVDouble rcm[NMETHOD];
    for (size_t i = 0; i < NMETHOD; i++) {
      string method = methods[i];
      common_read2_0(
          (DIR_DATA + to_string(year) + "." + method + ".rcm.txt").c_str(),
          rcm[i]);
    }

    {
      VDouble rankingScore(NC, 0), rankingScoreDev(NC, 0);
      VNodeType rk(NP, 0);
      for (size_t c = 0; c < NC; c++) {
        for (size_t p = 0; p < NP; p++)
          rk[p] = p;
        common_sort_p_val_less(&rk[0], &rk[NP], &pc[0]);
        recommend_rankingScore(
            rk, mcp0[c], mcp[c], rankingScore[c], rankingScoreDev[c]);
      }
      common_save1((DIR_COMMON + to_string(year)
                       + ".country.product.complexity.new.rankingScore.txt")
                       .c_str(),
          rankingScore, '\n');
      common_save1(
          (DIR_COMMON + to_string(year)
              + ".country.product.complexity.new.rankingScoreDev.txt")
              .c_str(),
          rankingScoreDev, '\n');
    }

    ;
    for (size_t i = 0; i < NMETHOD; i++) {
      string method = methods[i];
      VDouble rankingScore(NC, 0), rankingScoreDev(NC, 0);
      VVDouble r;
      for (size_t cc = 0, c; cc < NC; cc++) {
        c = cIndex[cc];
        r.push_back(rcm[i][c]);
      }
    }

  } // year

  return 0;
}

// ********************************************************
#endif
