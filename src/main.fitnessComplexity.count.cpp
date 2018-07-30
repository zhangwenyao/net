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
  const size_t NG = gIndex.size(), NP = pIndex.size(), NC = cIndex0.size();
  cout << NG << "\t" << NC << "\t" << NP << endl;

  for (size_t year = YEAR1; year < YEAR2; year++) {
    cout << year << endl;
    VVNodeType mcp;
    ERROR_TEST(common_read2_0(
        (DIR_DATA + to_string(year) + ".mcp.txt").c_str(), mcp));
    ERROR_TEST(mcp.size() != NC);
    for (NodeType c = 0; c < NC; c++)
      ERROR_TEST(mcp[c].size() != NP);

    VDouble cf(NC, 0);
    common_read1(
        (DIR_DATA + to_string(year) + ".country.fitness.txt").c_str(), cf);

    VNodeType mcpDeg;
    ERROR_TEST(common_read1_0(
        (DIR_DATA + to_string(year) + ".country.product.mcp.deg.txt").c_str(),
        mcpDeg));

    VDouble pc;
    ERROR_TEST(common_read1_0(
        (DIR_DATA + to_string(year) + ".product.complexity.txt").c_str(),
        pc));

    VNodeType pcRank(NP), pcRankIndex(NP), pcRankV2(NP), pcRankV2Index(NP);
    VDouble pcRankScale(NP);
    cal_val_2_rankScale(
        pc, pcRank, pcRankIndex, pcRankV2, pcRankV2Index, pcRankScale, NP);
    save_rankScale(
        (DIR_DATA + to_string(year) + ".product.complexity.rankLess").c_str(),
        pcRank, pcRankIndex, pcRankV2, pcRankV2Index, pcRankScale);

    VVNodeType mcpMcp;
    count_mcpMcp(mcp, mcpMcp);
    common_save2(
        (DIR_DATA + to_string(year) + ".country.product.mcp.txt").c_str(),
        mcpMcp);

    VDouble pcMean(NC, 0);
    for (size_t c = 0; c < NC; c++) {
      if (mcpDeg[c] <= 0)
        continue;
      common_total_p(&pc[0], &mcpMcp[c][0], mcpDeg[c], pcMean[c]);
      pcMean[c] /= mcpDeg[c];
    }
    common_save1(
        (DIR_DATA + to_string(year) + ".country.product.complexity.mean.txt")
            .c_str(),
        pcMean, '\n');
    {
      VDouble _pcMean(NC, 0);
      for (size_t c = 0; c < NC; c++) {
        if (mcpDeg[c] <= 0)
          continue;
        for (size_t i = 0; i < mcpDeg[c]; ++i) {
          double t = pc[mcpMcp[c][i]];
          _pcMean[c] += t * t;
        }
        _pcMean[c] = sqrt(_pcMean[c] / mcpDeg[c]);
      }
      common_save1((DIR_DATA + to_string(year)
                       + ".country.product.complexity.deviation.txt")
                       .c_str(),
          _pcMean, '\n');
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

      save_rankScale2_val(
          (DIR_DATA + to_string(year) + "." + method + ".rankLess").c_str(),
          net.recommend.rcm);

      save_rankScale2_val_p(
          (DIR_DATA + to_string(year) + "." + method + ".mcp.rankLess")
              .c_str(),
          net.recommend.rcm, mcpMcp);

      VVDouble scales;
      common_read2_0((DIR_DATA + to_string(year) + "." + method
                         + ".rankLessV2.scale.txt")
                         .c_str(),
          scales);
      scales.resize(NC);

    } // methods

    if (year <= YEAR1)
      continue;
    // ***************************************************************
    // count 2 var

    VVNodeType mcp0;
    ERROR_TEST(common_read2_0(
        (DIR_DATA + to_string(year - 1) + ".mcp.txt").c_str(), mcp0));
    ERROR_TEST(mcp0.size() != NC);
    for (NodeType c = 0; c < NC; c++)
      ERROR_TEST(mcp0[c].size() != NP);

    VNodeType mcpDeg0;
    ERROR_TEST(common_read1_0(
        (DIR_DATA + to_string(year - 1) + ".country.product.mcp.deg.txt")
            .c_str(),
        mcpDeg0));
    ERROR_TEST(mcpDeg0.size() != NC);

    VVNodeType mcpNew, mcpRemain;
    count_mcpNew(mcp0, mcp, mcpNew, mcpRemain);
    common_save2(
        (DIR_DATA + to_string(year) + ".country.product.new.txt").c_str(),
        mcpNew);
    common_save2(
        (DIR_DATA + to_string(year) + ".country.product.remain.txt").c_str(),
        mcpRemain);
    // common_read2_0((DIR_DATA + to_string(year) +
    // ".country.product.new.txt").c_str(),
    // mcpNew);
    // mcpNew.resize(NC);

    VNodeType newDeg, remainDeg;
    p2p_2_nodeDeg(newDeg, mcpNew);
    common_save1(
        (DIR_DATA + to_string(year) + ".country.product.new.deg.txt").c_str(),
        newDeg, '\n');
    p2p_2_nodeDeg(remainDeg, mcpRemain);
    common_save1(
        (DIR_DATA + to_string(year) + ".country.product.remain.deg.txt")
            .c_str(),
        remainDeg, '\n');
    // common_read1_0((DIR_DATA + to_string(year) +
    // ".country.product.new.deg.txt").c_str(), newDeg);
    // newDeg.resize(NC);

    VDouble newPcMean(NC, 0);
    for (size_t c = 0; c < NC; c++) {
      if (newDeg[c] <= 0)
        continue;
      common_total_p(&pc[0], &mcpNew[c][0], newDeg[c], newPcMean[c]);
      newPcMean[c] /= newDeg[c];
    }
    common_save1((DIR_DATA + to_string(year)
                     + +".country.product.complexity.new.mean.txt")
                     .c_str(),
        newPcMean, '\n');

    VVNodeType mcpPcRank(NC), mcpPcRankIndex(NC), mcpPcRankV2(NC),
        mcpPcRankV2Index(NC);
    VVDouble mcpPcRankScale(NC);
    VVNodeType mcpNewPcRank(NC), mcpNewPcRankIndex(NC), mcpNewPcRankV2(NC),
        mcpNewPcRankV2Index(NC);
    VVDouble mcpNewPcRankScale(NC);
    VVNodeType mcpRemainPcRank(NC), mcpRemainPcRankIndex(NC),
        mcpRemainPcRankV2(NC), mcpRemainPcRankV2Index(NC);
    VVDouble mcpRemainPcRankScale(NC);
    for (size_t c = 0; c < NC; ++c) {
      cal_val_2_rankScale_p(pc, &mcpMcp[c][0], mcpPcRank[c],
          mcpPcRankIndex[c], mcpPcRankV2[c], mcpPcRankV2Index[c],
          mcpPcRankScale[c], mcpDeg[c]);
      for (size_t p = 0, i = 0; p < NP; ++p)
        if (mcp[c][p] != 0) {
          if (mcp0[c][p] == 0) { // New
            mcpNewPcRank[c].push_back(mcpPcRank[c][i]);
            mcpNewPcRankIndex[c].push_back(mcpPcRankIndex[c][i]);
            mcpNewPcRankV2[c].push_back(mcpPcRankV2[c][i]);
            mcpNewPcRankV2Index[c].push_back(mcpPcRankV2Index[c][i]);
            mcpNewPcRankScale[c].push_back(mcpPcRankScale[c][i]);
          } else { // remain
            mcpRemainPcRank[c].push_back(mcpPcRank[c][i]);
            mcpRemainPcRankIndex[c].push_back(mcpPcRankIndex[c][i]);
            mcpRemainPcRankV2[c].push_back(mcpPcRankV2[c][i]);
            mcpRemainPcRankV2Index[c].push_back(mcpPcRankV2Index[c][i]);
            mcpRemainPcRankScale[c].push_back(mcpPcRankScale[c][i]);
          }
          ++i;
        }
    }
    save_rankScale2(
        (DIR_DATA + to_string(year) + ".country.product.mcp.rankLess")
            .c_str(),
        mcpPcRank, mcpPcRankIndex, mcpPcRankV2, mcpPcRankV2Index,
        mcpPcRankScale);
    save_rankScale2(
        (DIR_DATA + to_string(year) + ".country.product.new.rankLess")
            .c_str(),
        mcpNewPcRank, mcpNewPcRankIndex, mcpNewPcRankV2, mcpNewPcRankV2Index,
        mcpNewPcRankScale);
    save_rankScale2(
        (DIR_DATA + to_string(year) + ".country.product.remain.rankLess")
            .c_str(),
        mcpRemainPcRank, mcpRemainPcRankIndex, mcpRemainPcRankV2,
        mcpRemainPcRankV2Index, mcpRemainPcRankScale);

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
      common_save1((DIR_DATA + to_string(year)
                       + ".country.product.complexity.new.rankingScore.txt")
                       .c_str(),
          rankingScore, '\n');
      common_save1(
          (DIR_DATA + to_string(year)
              + ".country.product.complexity.new.rankingScoreDev.txt")
              .c_str(),
          rankingScoreDev, '\n');
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

      save_rankScale2_val_mcp(
          (DIR_DATA + to_string(year) + "." + method).c_str(),
          net.recommend.rcm, mcp0, mcp, mcpMcp);

      VVDouble scales;
      common_read2_0((DIR_DATA + to_string(year) + "." + method
                         + ".rankLessV2.scale.txt")
                         .c_str(),
          scales);
      scales.resize(NC);

      VDouble rankingScore(NC, 0), rankingScoreDev(NC, 0);
      for (size_t cc = 0, c; cc < NC; cc++) {
        c = cIndex[cc];
      }
      count_rankingScore(net.recommend.rcm, NC, NP, mcp0, mcp, rankingScore,
          rankingScoreDev);
      common_save1((DIR_DATA + to_string(year) + "." + method
                       + +".country.product.complexity.new.rankingScore.txt")
                       .c_str(),
          rankingScore, '\n');
      common_save1(
          (DIR_DATA + to_string(year) + "." + method
              + ".country.product.complexity.new.rankingScoreDev.txt")
              .c_str(),
          rankingScoreDev, '\n');

      const size_t C_N = 10, NRS = NP / C_N + 1;
      VNodeType nrs10(NRS, 0);
      VDouble rs10(NRS, 0), rs10_2(NRS, 0), cf10(NRS, 0);
      for (size_t c = 0; c < NC; c++) {
        if (mcpDeg[c] <= 0)
          continue;
        NodeType i = mcpDeg[c] / C_N;
        nrs10[i]++;
        const double t = rankingScore[c];
        rs10[i] += t;
        rs10_2[i] += t * t;
        cf10[i] += cf[c];
      }
      for (size_t i = 0; i < NRS; i++) {
        if (nrs10[i] > 0) {
          rs10[i] /= nrs10[i];
          rs10_2[i] = sqrt(rs10_2[i] / nrs10[i] - rs10[i] * rs10[i]);
          cf[i] /= nrs10[i];
        }
      }
      common_save1((DIR_DATA + to_string(year) + "." + method
                       + ".rankingScoreStatic10.txt")
                       .c_str(),
          rs10, '\n');
      common_save1((DIR_DATA + to_string(year) + "." + method
                       + ".rankingScoreStatic10deviation.txt")
                       .c_str(),
          rs10_2, '\n');
      common_save1((DIR_DATA + to_string(year) + "." + method
                       + ".countryFitness10.txt")
                       .c_str(),
          cf10, '\n');

    } // methods

  } // year

  return 0;
}

// ******************************************************
#endif
