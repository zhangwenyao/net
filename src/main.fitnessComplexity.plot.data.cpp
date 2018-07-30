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

  VVLinkType gdps;
  common_read2_0((DIR_DATA0 + "2001-2014.gdps.txt").c_str(), gdps);
  VVDouble gdpGrows;
  common_read2_0((DIR_DATA0 + "2001-2016.gdpGrows.txt").c_str(), gdpGrows);

  for (size_t year = YEAR1; year < YEAR2; year++) {
    cout << year << endl;

    VLinkType gdp;
    VNodeType rk;
    VDouble gdpGrow, cf, cpcMean;
    VVNodeType mcp;
    {
      for (size_t i = 0, g; i < NG; i++) {
        g = gIndex[i];
        gdp.push_back(gdps[g][year - 2001]);
        gdpGrow.push_back(gdpGrows[g][year - 2001]);
        rk.push_back(i);
      }
      common_save1(
          (DIR_COMMON + to_string(year) + ".gdp.txt").c_str(), gdp, '\n');
      common_save1((DIR_COMMON + to_string(year) + ".gdpGrow.txt").c_str(),
          gdpGrow, '\n');
      common_sort_p_val_less(&rk[0], &rk[NG], &gdp[0]);
      common_save1(
          (DIR_COMMON + to_string(year) + ".gdp.rankLess.txt").c_str(), rk,
          '\n');

      VDouble cf0, cpcMean0;
      VVNodeType mcp0;
      common_read1_0(
          (DIR_DATA + to_string(year) + ".country.fitness.txt").c_str(), cf0);
      common_read1_0((DIR_DATA + to_string(year)
                         + ".country.product.complexity.mean.txt")
                         .c_str(),
          cpcMean0);
      common_read2_0((DIR_DATA + to_string(year) + ".mcp.txt").c_str(), mcp0);
      for (size_t cc = 0, c; cc < NC; ++cc) {
        c = cIndex[cc];
        cf.push_back(cf0[c]);
        cpcMean.push_back(cpcMean0[c]);
        mcp.push_back(mcp0[c]);
      }
      common_save1(
          (DIR_COMMON + to_string(year) + ".country.fitness.txt").c_str(), cf,
          '\n');
      common_save1((DIR_COMMON + to_string(year)
                       + ".country.product.complexity.mean.txt")
                       .c_str(),
          cpcMean, '\n');
      common_save2((DIR_COMMON + to_string(year) + ".mcp.txt").c_str(), mcp);
    }

    const size_t N = 10;
    VVNodeType rks;
    rks.resize(N);
    for (size_t i = 0; i < NG; i++) {
      size_t j = N * i / NG;
      rks[j].push_back(rk[i]);
    }
    common_save2(
        (DIR_COMMON + to_string(year) + ".gdp.rank10.txt").c_str(), rks);

    if (year <= YEAR1)
      continue;
    // ************************************************************

    VVNodeType mcp0;
    ERROR_TEST(common_read2_0(
        (DIR_COMMON + to_string(year - 1) + ".mcp.txt").c_str(), mcp0));
    ERROR_TEST(mcp0.size() != NC);

    VVNodeType cpNew;
    common_read2_0(
        (DIR_DATA + to_string(year) + ".country.product.new.txt").c_str(),
        cpNew);
    cpNew.resize(NC0);

    VVDouble cpNewScale, newScale[NMETHOD];
    common_read2_0((DIR_DATA + to_string(year)
                       + ".country.product.new.rankLessV2.scale.txt")
                       .c_str(),
        cpNewScale);
    cpNewScale.resize(NC0);

    VDouble cpcNewMean;
    {
      VDouble cpcNewMean0;
      common_read1_0((DIR_DATA + to_string(year)
                         + ".country.product.complexity.new.mean.txt")
                         .c_str(),
          cpcNewMean0);
      for (size_t cc = 0, c; cc < NC; ++cc) {
        c = cIndex[cc];
        cpcNewMean.push_back(cpcNewMean0[c]);
      }
      common_save1((DIR_COMMON + to_string(year)
                       + ".country.product.complexity.new.mean.txt")
                       .c_str(),
          cpcNewMean, '\n');
    }
    VDouble cpcNewMeanR(NC, 0);
    {
      VDouble cpcDev0;
      common_read1_0((DIR_DATA + to_string(year)
                         + ".country.product.complexity.deviation.txt")
                         .c_str(),
          cpcDev0);
      for (size_t i = 0, c; i < NC; ++i) {
        c = cIndex[i];
        if (cpcDev0[c] > 0)
          cpcNewMeanR[i] = (cpcNewMean[i] - cpcMean[i]) / cpcDev0[c];
      }
      common_save1((DIR_COMMON + to_string(year)
                       + ".country.product.complexity.new.mean.R.txt")
                       .c_str(),
          cpcNewMeanR, '\n');
    }

    for (size_t i = 0; i < NMETHOD; i++) {
      string method = methods[i];
      common_read2_0((DIR_DATA + to_string(year) + "." + method
                         + ".new.rankLessV2.scale.txt")
                         .c_str(),
          newScale[i]);
      newScale[i].resize(NC0);
    }

    if (0) {
      ofstream os((DIR_COMMON + to_string(year) + ".scale.txt").c_str());
      for (size_t cc = 0, c; cc < NC; cc++) {
        c = cIndex[cc];
        for (size_t j = 0; j < cpNew[c].size(); j++) {
          size_t p = cpNew[c][j];
          os << c << '\t' << p << '\t' << cpNewScale[c][j];
          for (size_t ii = 0; ii < NMETHOD; ii++) {
            os << '\t' << newScale[ii][c][j];
          }
          os << '\n';
        }
      }
      os.close();

      for (size_t i = 0; i < N; i++) {
        ofstream os((DIR_COMMON + to_string(year) + ".scale.rank10."
                        + to_string(i) + ".txt")
                        .c_str());
        for (size_t cc = 0, c; cc < rks[i].size(); cc++) {
          c = rks[i][cc];
          for (size_t j = 0; j < cpNew[c].size(); j++) {
            size_t p = cpNew[c][j];
            os << c << '\t' << p << '\t' << cpNewScale[c][j];
            for (size_t ii = 0; ii < NMETHOD; ii++) {
              os << '\t' << newScale[ii][c][j];
            }
            os << '\n';
          }
        }
        os.close();
      }
    }

    VDouble pc;
    VVDouble rcm[NMETHOD];
    cpNew.resize(NC0);
    common_read1_0(
        (DIR_DATA + to_string(year) + ".product.complexity.txt").c_str(), pc);
    for (size_t i = 0; i < NMETHOD; i++) {
      string method = methods[i];
      common_read2_0(
          (DIR_DATA + to_string(year) + "." + method + ".rcm.txt").c_str(),
          rcm[i]);
    }

    if (0) {
      ofstream os((DIR_COMMON + to_string(year) + ".val.txt").c_str());
      for (size_t cc = 0, c; cc < NG; cc++) {
        c = cIndex[cc];
        for (size_t j = 0; j < cpNew[c].size(); j++) {
          size_t p = cpNew[c][j];
          os << c << '\t' << p << '\t' << pc[p];
          for (size_t ii = 0; ii < NMETHOD; ii++) {
            os << '\t' << rcm[ii][c][p];
          }
          os << '\n';
        }
      }
      os.close();

      for (size_t i = 0; i < N; i++) {
        ofstream os((DIR_COMMON + to_string(year) + ".val.rank10."
                        + to_string(i) + +".txt")
                        .c_str());
        for (size_t cc = 0, c; cc < rks[i].size(); cc++) {
          c = rks[i][cc];
          for (size_t j = 0; j < cpNew[c].size(); j++) {
            size_t p = cpNew[c][j];
            os << c << '\t' << p << '\t' << pc[p];
            for (size_t ii = 0; ii < NMETHOD; ii++) {
              os << '\t' << rcm[ii][c][p];
            }
            os << '\n';
          }
        }
        os.close();
      }
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

    for (size_t i = 0; i < NMETHOD; i++) {
      string method = methods[i];
      VDouble rankingScore(NC, 0), rankingScoreDev(NC, 0);
      VVDouble r;
      for (size_t cc = 0, c; cc < NC; cc++) {
        c = cIndex[cc];
        r.push_back(rcm[i][c]);
      }
      count_rankingScore(r, NC, NP, mcp0, mcp, rankingScore, rankingScoreDev);
      common_save1((DIR_COMMON + to_string(year) + "." + method
                       + +".country.product.complexity.new.rankingScore.txt")
                       .c_str(),
          rankingScore, '\n');
      common_save1(
          (DIR_COMMON + to_string(year) + "." + method
              + ".country.product.complexity.new.rankingScoreDev.txt")
              .c_str(),
          rankingScoreDev, '\n');
    }

  } // year

  return 0;
}

// ********************************************************
#endif
