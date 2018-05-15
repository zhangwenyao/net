// g++ -o main.exe *.cpp -O3 -Wall
#include "main.h"
#ifdef MAIN_FITNESS_COMPLEXITY_COUNT

#include "common.h"
#include "networks.h"
using namespace std;
//**//**************************************************//**//*

int recommend(Networks& net, const VVNodeType& mcp, VVNodeType& pc, VVNodeType& pp, const string method, const char* name = NULL)
{
  Mcp_2_C_P(mcp, net.recommend.user_p_object, net.recommend.object_p_user);
  net.act_recommend(method.c_str());
  if (name != NULL && name[0] != '\0')
    common_save2(name, net.recommend.rcm);
  return 0;
}

int count_k1(const size_t NC, const size_t NP, const VVNodeType& mcp, VNodeType& k1, const char* name = NULL)
{
  k1.assign(NC, 0);
  for (size_t c = 0; c < NC; c++) {
    for (size_t p = 0; p < NP; p++) {
      if (mcp[c][p] != 0)
        k1[c]++;
    }
  }
  if (name != NULL && name[0] != '\0')
    common_save1(name, k1, '\n');
  return 0;
}

int count_cpNew(const size_t NC, const size_t NP, const VVNodeType& mcp, const VVNodeType& mcp2, VVNodeType& cpNew, const char* name = NULL)
{
  cpNew.resize(NC);
  for (size_t c = 0; c < NC; c++) {
    cpNew[c].clear();
    for (size_t p = 0; p < NP; p++) {
      if (mcp[c][p] == 0 && mcp2[c][p] != 0)
        cpNew[c].push_back(p);
    }
  }
  if (name != NULL && name[0] != '\0')
    common_save2(name, cpNew);
  return 0;
}

int count_kNew(VNodeType& kNew, const VVNodeType& cpNew, const char* name = NULL)
{
  kNew.resize(cpNew.size());
  for (size_t c = 0; c < cpNew.size(); c++) {
    kNew[c] = cpNew[c].size();
  }
  if (name != NULL && name[0] != '\0')
    common_save1(name, kNew, '\n');
  return 0;
}

int count_pcNewRank(const VDouble& pc, const size_t NC, const size_t NP, const VVNodeType& cpNew, VVNodeType& rankNew, const char* name = NULL)
{
  rankNew.resize(NC);
  VNodeType rk(NP, 0), rk2(NP, 0);
  for (size_t p = 0; p < NP; p++)
    rk[p] = p;
  common_sort_p_val_less(&rk[0], &rk[NP], &pc[0]);
  for (size_t p = 0; p < NP; p++)
    rk2[rk[p]] = p;
  for (size_t c = 0; c < NC; c++) {
    for (size_t p = 0; p < cpNew[c].size(); p++)
      rankNew[c].push_back(rk2[cpNew[c][p]]);
  }
  if (name != NULL && name[0] != '\0')
    common_save2(name, rankNew);
  return 0;
}

int count_rankNew(const VVDouble& rcm, const size_t NC, const size_t NP, const VVNodeType& cpNew, VVNodeType& rankNew, const char* name = NULL)
{
  rankNew.resize(NC);
  VNodeType rk(NP, 0), rk2(NP, 0);
  for (size_t c = 0; c < NC; c++) {
    for (size_t p = 0; p < NP; p++)
      rk[p] = p;
    common_sort_p_val_less(&rk[0], &rk[NP], &rcm[c][0]);
    for (size_t p = 0; p < NP; p++)
      rk2[rk[p]] = p;
    for (size_t p = 0; p < cpNew[c].size(); p++)
      rankNew[c].push_back(rk2[cpNew[c][p]]);
  }
  if (name != NULL && name[0] != '\0')
    common_save2(name, rankNew);
  return 0;
}

int count_rankingScore(const VVDouble& rcm, const size_t NC, const size_t NP, const VVNodeType& mcp, const VVNodeType& mcp2, VDouble& rankingScore, const char* name = NULL)
{
  rankingScore.assign(NC, 0);
  VNodeType rk(NP, 0);
  for (size_t c = 0; c < NC; c++) {
    for (size_t p = 0; p < NP; p++)
      rk[p] = p;
    common_sort_p_val_less(&rk[0], &rk[NP], &rcm[c][0]);
    recommend_rankingScore(rk, mcp[c], mcp2[c], rankingScore[c]);
  }
  if (name != NULL && name[0] != '\0')
    common_save1(name, rankingScore, '\n');
  return 0;
}

int main(int argc, char** argv)
{
  SHOW_TIME(cout); // 显示系统时间

  const string DIR = "../../swiss/economic-complexity/201803/", DIR2 = DIR + "1995-2010/";
  const string methods[] = { "mass", "heat", "hybrid" };
  //const string methods[] = { "hybrid" };
  const size_t NMETHOD = sizeof(methods) / sizeof(methods[0]);
  const int YEAR1 = 1995, YEAR2 = 2010;
  //const int YEAR1 = 2000, YEAR2 = 2000;
  for (size_t iMethod = 0; iMethod < NMETHOD; iMethod++) {
    string method = methods[iMethod];
    cout << method << endl;

    for (int year = YEAR1; year < YEAR2; year++) {
      string y1, y2;
      stringstream ss;
      ss.clear();
      ss.str("");
      ss << year;
      y1 = ss.str();
      ss.clear();
      ss.str("");
      ss << year + 1;
      y2 = ss.str();

      VVNodeType mcp;
      common_read2_0((DIR2 + y1 + ".mcp.txt").c_str(), mcp);
      const size_t NC = mcp.size(), NP = mcp[0].size();

      Networks net;
      net.saveName = DIR2 + y1;
      // recommend(net, mcp, pc, pp, method, (dir + y1 + "." + method + ".rcm.txt").c_str());
      common_read2_0((DIR2 + y1 + "." + method + ".rcm.txt").c_str(), net.recommend.rcm);

      VVNodeType mcp2;
      common_read2_0((DIR2 + y2 + ".mcp.txt").c_str(), mcp2);
      if (mcp2.size() != NC || net.recommend.rcm.size() != NC) {
        ERROR();
        return -1;
      }
      for (size_t c = 0; c < NC; c++) {
        if (mcp[c].size() != NP || mcp2[c].size() != NP) {
          ERROR(mcp[c].size(), "\t", mcp2.size());
          break;
        }
      }
      cout << "\t" << year << "\t" << NC << "\t" << NP << "\t" << net.recommend.rcm.size() << endl;

      VNodeType k1;
      //count_k1(NC, NP, mcp, k1, (DIR2 + y1 + ".country.product.k.txt").c_str());
      common_read1_0((DIR2 + y1 + ".country.product.k.txt").c_str(), k1);

      VNodeType k2;
      //count_k1(NC, NP, mcp2, k2, (DIR2 + y2 + ".country.product.k.txt").c_str());
      common_read1_0((DIR2 + y2 + ".country.product.k.txt").c_str(), k2);

      VVNodeType cpNew;
      //count_cpNew(NC, NP, mcp, mcp2, cpNew, (DIR2 + y1 + ".country.product.new.txt").c_str());
      common_read2_0((DIR2 + y1 + ".country.product.new.txt").c_str(), cpNew);
      VNodeType kNew;
      //count_kNew(kNew, cpNew, (DIR2 + y1 + ".country.product.new.k.txt").c_str());
      common_read1_0((DIR2 + y1 + ".country.product.new.k.txt").c_str(), kNew);

      VDouble pc;
      common_read1_0((DIR2 + y1 + ".product.complexity.txt").c_str(), pc);

      VVNodeType pcNewRank;
      //count_pcNewRank(pc, NC, NP, cpNew, pcNewRank, (DIR2 + y1 + ".country.product.new.rank.txt").c_str());
      common_read2_0((DIR2 + y1 + ".country.product.new.rank.txt").c_str(), pcNewRank);

      VVNodeType newRank;
      //count_rankNew(net.recommend.rcm, NC, NP, cpNew, newRank, (DIR2 + y1 + "." + method + ".new.rank.txt").c_str());
      common_read2_0((DIR2 + y1 + "." + method + ".new.rank.txt").c_str(), newRank);
      VDouble rankingScore;
      //count_rankingScore(net.recommend.rcm, NC, NP, mcp, mcp2, rankingScore, (DIR2 + y1 + "." + method + ".rankingScore.txt").c_str());
      common_read1_0((DIR2 + y1 + "." + method + ".rankingScore.txt").c_str(), rankingScore);

      VDouble cf;
      common_read1_0((DIR2 + y1 + ".country.fitness.txt").c_str(), cf);

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
      common_save1((DIR2 + y1 + "." + method + ".rankingScoreStatic10.txt").c_str(), rs10, '\n');
      common_save1((DIR2 + y1 + "." + method + ".rankingScoreStatic10deviation.txt").c_str(), rs10_2, '\n');
      common_save1((DIR2 + y1 + "." + method + ".countryFitness10.txt").c_str(), cf10, '\n');

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
      common_save1((DIR2 + y1 + ".country.product.complexity.mean.txt").c_str(), pcMean, '\n');

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
      common_save1((DIR2 + y1 + "." + method + ".country.product.complexity.new.mean.txt").c_str(), pcNewMean, '\n');

    } // year
  }   // method

  SHOW_TIME(cout); // 显示系统时间
  return 0;
}

//**//**************************************************//**//*
#endif
