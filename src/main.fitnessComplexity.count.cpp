#include "main.h"
#ifdef MAIN_FITNESS_COMPLEXITY_COUNT

#include "common.h"
#include "networks.h"
using namespace std;
// ******************************************************

int main_fitness_complexity_count(int argc, char** argv)
{
  const string DIR0 = "data/complexity/", DIR_DATA = DIR0 + "data/";
  // const string methods[] = { "mass", "heat", "hybrid" };
  const string methods[] = { "heat" };
  const size_t NMETHOD = sizeof(methods) / sizeof(methods[0]);
  const size_t YEAR1 = 2001, YEAR2 = 2014+1, NC = 228, NCGDP = 197, NP = 1241;

  for (size_t year = YEAR1; year < YEAR2; year++) {
    cout << year << endl;
    string y1;
    stringstream ss;
    ss.clear();
    ss.str("");
    ss << year;
    y1 = ss.str();
    string y2;
    ss.clear();
    ss.str("");
    ss << year + 1;
    y2 = ss.str();

    VVNodeType mcp;
    common_read2_0((DIR_DATA + y1 + ".mcp.txt").c_str(), mcp);
    VVNodeType mcp2;
    common_read2_0((DIR_DATA + y2 + ".mcp.txt").c_str(), mcp2);
    if (mcp.size() != NC || mcp2.size() != NC) {
      ERROR();
      return -1;
    }
    for (NodeType c = 0; c < NC; c++) {
      if (mcp[c].size() != NP || mcp2[c].size() != NP) {
        ERROR(mcp[c].size(), "\t", mcp2.size());
        break;
      }
    }
    cout << "\t" << NC << "\t" << NP << endl;
    VNodeType k1;
    common_read1_0((DIR_DATA + y1 + ".country.product.k.txt").c_str(), k1);
    VNodeType k2;
    common_read1_0((DIR_DATA + y2 + ".country.product.k.txt").c_str(), k2);

    VVNodeType mcpNew;
    count_mcpNew(NC, NP, mcp, mcp2, mcpNew,
        (DIR_DATA + y1 + ".country.product.new.txt").c_str());
    // common_read2_0((DIR_DATA + y1 + ".country.product.new.txt").c_str(),
    // cpNew);
    // cpNew.resize(NC);

    VNodeType kNew;
    count_kNew(
        kNew, mcpNew, (DIR_DATA + y1 + ".country.product.new.k.txt").c_str());
    // common_read1_0((DIR_DATA + y1 +
    // ".country.product.new.k.txt").c_str(), kNew);

    VDouble pc;
    common_read1_0((DIR_DATA + y1 + ".product.complexity.txt").c_str(), pc);

    VVNodeType pcNewRank;
    count_pcNewRank(pc, NC, NP, mcpNew, pcNewRank,
        (DIR_DATA + y1 + ".country.product.new.rank.txt").c_str());
    // common_read2_0(
    //(DIR_DATA + y1 + ".country.product.new.rank.txt").c_str(),
    // pcNewRank);
    // pcNewRank.resize(NC);

    VVNodeType pcNewRemainRank;
    count_pcNewRemainRank(pc, NC, NP, mcp, mcpNew, pcNewRemainRank,
        (DIR_DATA + y1 + ".country.product.new.remain.rank.txt").c_str());
    // common_read2_0(
    //(DIR_DATA + y1 + ".country.product.new.remain.rank.txt").c_str(),
    // pcNewRemainRank);
    // pcNewRemainRank.resize(NC);

    VVDouble pcNewScale;
    count_newScale(NC, NP, k1, pcNewRemainRank, pcNewScale,
        (DIR_DATA + y1 + ".country.product.new.scale.txt").c_str());
    // common_read2_0((DIR_DATA + y1 +
    // ".country.product.new.scale.txt").c_str(), pcNewScale);
    // pcNewScale.resize(NC);
    break;

    for (size_t iMethod = 0; iMethod < NMETHOD; iMethod++) {
      string method = methods[iMethod];
      cout << "\t" << method << endl;

      Networks net;
      net.saveName = DIR_DATA + y1;
      common_read2_0((DIR_DATA + y1 + "." + method + ".rcm.txt").c_str(),
          net.recommend.rcm);
      if (net.recommend.rcm.size() != NC) {
        ERROR();
        return -1;
      }

      VVNodeType newRank;
      count_newRank(net.recommend.rcm, NC, NP, mcpNew, newRank,
          (DIR_DATA + y1 + "." + method + ".new.rank.txt").c_str());
      // common_read2_0((DIR_DATA + y1 + "." + method +
      // ".new.rank.txt").c_str(), newRank);
      // newRank.resize(NC);

      VVNodeType newRemainRank;
      count_newRemainRank(net.recommend.rcm, NC, NP, mcp, mcpNew,
          newRemainRank,
          (DIR_DATA + y1 + "." + method + ".new.remain.rank.txt").c_str());
      // common_read2_0((DIR_DATA + y1 +"."+method+
      // ".new.remain.rank.txt").c_str(), newRemainRank);
      // newRemainRank.resize(NC);

      VVDouble newScale;
      count_newScale(NC, NP, k1, newRemainRank, newScale,
          (DIR_DATA + y1 + "." + method + ".new.scale.txt").c_str());
      // common_read2_0((DIR_DATA + y1 + "." + method +
      // ".new.scale.txt").c_str(), newScale);
      // newScale.resize(NC);

      VDouble rankingScore;
      count_rankingScore(net.recommend.rcm, NC, NP, mcp, mcp2, rankingScore,
          (DIR_DATA + y1 + "." + method + ".rankingScore.txt").c_str());
      // common_read1_0((DIR_DATA + y1 + "." + method +
      // ".rankingScore.txt").c_str(), rankingScore);

      VDouble cf;
      common_read1_0((DIR_DATA + y1 + ".country.fitness.txt").c_str(), cf);
      continue;

      const size_t NRS = NP / 10 + 1;
      VNodeType nrs10(NRS, 0);
      VDouble rs10(NRS, 0), rs10_2(NRS, 0), cf10(NRS, 0);
      for (size_t c = 0; c < NC; c++) {
        if (kNew[c] <= 0)
          continue;
        NodeType i = k1[c] / 10;
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
      common_save1(
          (DIR_DATA + y1 + "." + method + ".rankingScoreStatic10.txt")
              .c_str(),
          rs10, '\n');
      common_save1((DIR_DATA + y1 + "." + method
                       + ".rankingScoreStatic10deviation.txt")
                       .c_str(),
          rs10_2, '\n');
      common_save1(
          (DIR_DATA + y1 + "." + method + ".countryFitness10.txt").c_str(),
          cf10, '\n');

      VDouble pcMean(NC, 0);
      for (size_t c = 0; c < NC; c++) {
        if (k1[c] <= 0)
          continue;
        for (size_t p = 0; p < NP; p++) {
          if (mcp[c][p] != 0) {
            pcMean[c] += pc[p];
          }
        }
        pcMean[c] /= k1[c];
      }
      common_save1(
          (DIR_DATA + y1 + ".country.product.complexity.mean.txt").c_str(),
          pcMean, '\n');

      VDouble pcNewMean(NC, 0);
      for (size_t c = 0; c < NC; c++) {
        if (kNew[c] <= 0)
          continue;
        for (size_t p = 0; p < NP; p++) {
          if (mcp[c][p] == 0 && mcp2[c][p] != 0) {
            pcNewMean[c] += pc[p];
          }
        }
        pcNewMean[c] /= kNew[c];
      }
      common_save1((DIR_DATA + y1 + "." + method
                       + ".country.product.complexity.new.mean.txt")
                       .c_str(),
          pcNewMean, '\n');

    } // year
  }   // method

  return 0;
}

// ******************************************************
#endif
