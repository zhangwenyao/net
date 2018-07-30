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
  cout << NC << "\t" << NC << "\t" << NP << endl;

  for (size_t year = YEAR1; year < YEAR2; year++) {
    INFORM(year);

    VVNodeType mcp;
    ERROR_TEST(common_read2_0(
        (DIR_DATA + to_string(year) + ".mcp.txt").c_str(), mcp));
    ERROR_TEST(mcp.size() != NC);
    for (NodeType c = 0; c < NC; c++)
      ERROR_TEST(mcp[c].size() != NP);

    VNodeType mcpDeg;
    ERROR_TEST(common_read1_0(
        (DIR_DATA + to_string(year) + ".country.product.mcp.deg.txt").c_str(),
        mcpDeg));
    INFORM();

    VDouble pc;
    ERROR_TEST(common_read1_0(
        (DIR_DATA + to_string(year) + ".product.complexity.txt").c_str(),
        pc));

    INFORM();
    VNodeType pcRank(NP), pcRankIndex(NP), pcRankV2(NP), pcRankV2Index(NP);
    VDouble pcRankScale(NP);
    cal_val_2_rankScale(
        pc, pcRank, pcRankIndex, pcRankV2, pcRankV2Index, pcRankScale, NP);
    // for (size_t p = 0; p < NP; ++p)
    // pcRank[p] = p;
    // common_sort_p_val_less(pcRank.begin(), pcRank.end(), &pc.front());
    common_save1(
        (DIR_DATA + to_string(year) + ".pruduct.complexity.rankLess.txt")
            .c_str(),
        pcRank, '\n');
    // common_get_index(pcRank.begin(), pcRank.end(), &pcRankIndex.front());
    common_save1((DIR_DATA + to_string(year)
                     + ".pruduct.complexity.rankLess.index.txt")
                     .c_str(),
        pcRankIndex, '\n');
    // common_sort_rankV2(
    //&pc.front(), pcRank.begin(), pcRank.end(), &pcRankV2.front());
    common_save1(
        (DIR_DATA + to_string(year) + ".pruduct.complexity.rankLessV2.txt")
            .c_str(),
        pcRankV2, '\n');
    // common_get_index_val(pcRank.begin(), pcRank.end(),
    // &pcRankV2Index.front(), &pcRankIndex.front());
    common_save1((DIR_DATA + to_string(year)
                     + ".pruduct.complexity.rankLessV2.index.txt")
                     .c_str(),
        pcRankV2Index, '\n');
    // if (NP > 1)
    // for (size_t p = 0; p < NP; ++p)
    // pcRankScale[p] = (double)pcRankV2Index[p] / 2 / (NP - 1);
    common_save1((DIR_DATA + to_string(year)
                     + ".pruduct.complexity.rankLessV2.scale.txt")
                     .c_str(),
        pcRankScale, '\n');
    INFORM();

    // count 2 var

    if (year <= YEAR1)
      continue;
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
    INFORM();

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
    INFORM();

    VNodeType newDeg;
    p2p_2_nodeDeg(newDeg, mcpNew);
    common_save1(
        (DIR_DATA + to_string(year) + ".country.product.new.deg.txt").c_str(),
        newDeg, '\n');
    // common_read1_0((DIR_DATA + to_string(year) +
    // ".country.product.new.deg.txt").c_str(), newDeg);
    // newDeg.resize(NC);
    INFORM();

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
      const size_t deg = mcpDeg[c];
      if (deg <= 0)
        continue;
      INFORM();

      VNodeType& pcRank = mcpPcRank[c];
      VNodeType& pcRankIndex = mcpPcRankIndex[c];
      VNodeType& pcRankV2 = mcpPcRankV2[c];
      VNodeType& pcRankV2Index = mcpPcRankV2Index[c];
      VDouble& pcRankScale = mcpPcRankScale[c];
      // VDouble mcpPc(deg);
      // pcRank.resize(deg);
      // pcRankIndex.resize(deg);
      // pcRankV2.resize(deg);
      // pcRankV2Index.resize(deg);
      // pcRankScale.resize(deg);
      // for (size_t p = 0; p < deg; ++p) {
      // pcRank[p] = p;
      // mcpPc[p] = pc[mcpNew[c][p]];
      //}
      cal_val_2_rankScale_p(pc, &mcpNew[c][0], pcRank, pcRankIndex, pcRankV2,
          pcRankV2Index, pcRankScale, deg);
      // common_sort_p_val_less(pcRank.begin(), pcRank.end(), &mcpPc.front());
      // common_get_index(pcRank.begin(), pcRank.end(), &pcRankIndex.front());
      // common_sort_rankV2(
      //&mcpPc.front(), pcRank.begin(), pcRank.end(), &pcRankV2.front());
      // common_get_index_val(pcRank.begin(), pcRank.end(),
      //&pcRankV2Index.front(), &pcRankIndex.front());
      // if (deg > 1)
      // for (size_t p = 0; p < deg; ++p)
      // pcRankScale[p] = (double)pcRankV2Index[p] / 2 / (deg - 1);
      INFORM();

      for (size_t p = 0, i = 0; p < NP; ++p)
        if (mcp[c][p] != 0) {
          if (mcp0[c][p] == 0) { // New
            mcpNewPcRank[c].push_back(pcRank[i]);
            mcpNewPcRankIndex[c].push_back(pcRankIndex[i]);
            mcpNewPcRankV2[c].push_back(pcRankV2[i]);
            mcpNewPcRankV2Index[c].push_back(pcRankV2Index[i]);
            mcpNewPcRankScale[c].push_back(pcRankScale[i]);
          } else { // remain
            mcpRemainPcRank[c].push_back(pcRank[i]);
            mcpRemainPcRankIndex[c].push_back(pcRankIndex[i]);
            mcpRemainPcRankV2[c].push_back(pcRankV2[i]);
            mcpRemainPcRankV2Index[c].push_back(pcRankV2Index[i]);
            mcpRemainPcRankScale[c].push_back(pcRankScale[i]);
          }
          ++i;
        }
    }
    INFORM();
    common_save2(
        (DIR_DATA + to_string(year) + ".pruduct.complexity.mcp.rankLess.txt")
            .c_str(),
        mcpPcRank);
    common_save2((DIR_DATA + to_string(year)
                     + ".pruduct.complexity.mcp.rankLess.index.txt")
                     .c_str(),
        mcpPcRankIndex);
    common_save2((DIR_DATA + to_string(year)
                     + ".pruduct.complexity.mcp.rankLessV2.txt")
                     .c_str(),
        mcpPcRankV2);
    common_save2((DIR_DATA + to_string(year)
                     + ".pruduct.complexity.mcp.rankLessV2.index.txt")
                     .c_str(),
        mcpPcRankV2Index);
    common_save2((DIR_DATA + to_string(year)
                     + ".pruduct.complexity.mcp.rankLessV2.scale.txt")
                     .c_str(),
        mcpPcRankScale);
    common_save2(
        (DIR_DATA + to_string(year) + ".pruduct.complexity.new.rankLess.txt")
            .c_str(),
        mcpNewPcRank);
    common_save2((DIR_DATA + to_string(year)
                     + ".pruduct.complexity.new.rankLess.index.txt")
                     .c_str(),
        mcpNewPcRankIndex);
    common_save2((DIR_DATA + to_string(year)
                     + ".pruduct.complexity.new.rankLessV2.txt")
                     .c_str(),
        mcpNewPcRankV2);
    common_save2((DIR_DATA + to_string(year)
                     + ".pruduct.complexity.new.rankLessV2.index.txt")
                     .c_str(),
        mcpNewPcRankV2Index);
    common_save2((DIR_DATA + to_string(year)
                     + ".pruduct.complexity.new.rankLessV2.scale.txt")
                     .c_str(),
        mcpNewPcRankScale);
    common_save2((DIR_DATA + to_string(year)
                     + ".pruduct.complexity.remain.rankLess.txt")
                     .c_str(),
        mcpRemainPcRank);
    common_save2((DIR_DATA + to_string(year)
                     + ".pruduct.complexity.remain.rankLess.index.txt")
                     .c_str(),
        mcpRemainPcRankIndex);
    common_save2((DIR_DATA + to_string(year)
                     + ".pruduct.complexity.remain.rankLessV2.txt")
                     .c_str(),
        mcpRemainPcRankV2);
    common_save2((DIR_DATA + to_string(year)
                     + ".pruduct.complexity.remain.rankLessV2.index.txt")
                     .c_str(),
        mcpRemainPcRankV2Index);
    common_save2((DIR_DATA + to_string(year)
                     + ".pruduct.complexity.remain.rankLessV2.scale.txt")
                     .c_str(),
        mcpRemainPcRankScale);
    INFORM();

    for (size_t iMethod = 0; iMethod < NMETHOD; iMethod++) {
      string method = methods[iMethod];
      cout << "\t" << method << endl;

      Networks net;
      net.saveName = DIR_DATA + to_string(year);
      common_read2_0(
          (DIR_DATA + to_string(year) + "." + method + ".rcm.txt").c_str(),
          net.recommend.rcm);
      ERROR_TEST(net.recommend.rcm.size() != NC);

      // VVNodeType newRank;
      // count_newRank(net.recommend.rcm, NC, NP, mcpNew, newRank,
      //(DIR_DATA + to_string(year) + "." + method + ".new.rank.txt")
      //.c_str());
      // common_read2_0((DIR_DATA + year + "." + method +
      // ".new.rank.txt").c_str(), newRank);
      // newRank.resize(NC);

      // VVNodeType newRemainRank;
      // count_newRemainRank(net.recommend.rcm, NC, NP, mcp, mcpNew,
      // newRemainRank,
      //(DIR_DATA + to_string(year) + "." + method + ".new.remain.rank.txt")
      //.c_str());
      // common_read2_0((DIR_DATA + year +"."+method+
      // ".new.remain.rank.txt").c_str(), newRemainRank);
      // newRemainRank.resize(NC);

      // VVDouble newScale;
      // count_newScale(NC, NP, deg0, newRemainRank, newScale,
      //(DIR_DATA + to_string(year) + "." + method + ".new.scale.txt")
      //.c_str());
      // common_read2_0((DIR_DATA + year + "." + method +
      // ".new.scale.txt").c_str(), newScale);
      // newScale.resize(NC);

      return 0;
      VNodeType rk, rkIndex, rkV2, rkV2Index;
      VDouble rkScale;
      // cal_val_2_rankScale_p(rcm[c], mcpNew[c]);

      VDouble rankingScore;
      count_rankingScore(net.recommend.rcm, NC, NP, mcp0, mcp, rankingScore,
          (DIR_DATA + to_string(year) + "." + method + ".rankingScore.txt")
              .c_str());
      // common_read1_0((DIR_DATA + year + "." + method +
      // ".rankingScore.txt").c_str(), rankingScore);

      VDouble cf;
      common_read1_0(
          (DIR_DATA + to_string(year) + ".country.fitness.txt").c_str(), cf);
      continue;

      const size_t NRS = NP / 10 + 1;
      VNodeType nrs10(NRS, 0);
      VDouble rs10(NRS, 0), rs10_2(NRS, 0), cf10(NRS, 0);
      for (size_t c = 0; c < NC; c++) {
        if (newDeg[c] <= 0)
          continue;
        NodeType i = mcpDeg0[c] / 10;
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

      VDouble pcMean(NC, 0);
      for (size_t c = 0; c < NC; c++) {
        if (mcpDeg0[c] <= 0)
          continue;
        for (size_t p = 0; p < NP; p++) {
          if (mcp[c][p] != 0) {
            pcMean[c] += pc[p];
          }
        }
        pcMean[c] /= mcpDeg0[c];
      }
      common_save1((DIR_DATA + to_string(year)
                       + ".country.product.complexity.mean.txt")
                       .c_str(),
          pcMean, '\n');

      VDouble newPcMean(NC, 0);
      for (size_t c = 0; c < NC; c++) {
        if (newDeg[c] <= 0)
          continue;
        for (size_t p = 0; p < NP; p++) {
          if (mcp[c][p] == 0 && mcp[c][p] != 0) {
            newPcMean[c] += pc[p];
          }
        }
        newPcMean[c] /= newDeg[c];
      }
      common_save1((DIR_DATA + to_string(year) + "." + method
                       + ".country.product.complexity.new.mean.txt")
                       .c_str(),
          newPcMean, '\n');

    } // year
  }   // method

  return 0;
}

// ******************************************************
#endif
