// g++ -o main.exe *.cpp -O3 -Wall
#include "main.h"
#ifdef MAIN_FITNESS_COMPLEXITY_COUNT

#include "common.h"
#include "networks.h"
using namespace std;
//**//**************************************************//**//*

int recommend(Networks& net, const VVNodeType& mcp, VVNodeType& pc,
    VVNodeType& pp, const string method, const char* name = NULL)
{
  Mcp_2_C_P(mcp, pc, pp);
  net.recommend.user_p_object = &pc;
  net.recommend.object_p_user = &pp;
  net.act_recommend(method.c_str());
  if (name != NULL && name[0] != '\0')
    common_save2(name, net.recommend.rcm);
  return 0;
}

int count_k1(const size_t NC, const size_t NP, const VVNodeType& mcp,
    VNodeType& k1, const char* name = NULL)
{
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

int count_kNew(const size_t NC, const size_t NP, const VVNodeType& mcp,
    const VVNodeType& mcp2, VNodeType& kNew, const char* name = NULL)
{
  for (size_t c = 0; c < NC; c++) {
    for (size_t p = 0; p < NP; p++) {
      if (mcp[c][p] == 0 && mcp2[c][p] != 0)
        kNew[c]++;
    }
  }
  if (name != NULL && name[0] != '\0')
    common_save1(name, kNew, '\n');
  return 0;
}

int count_rankingScore(Networks& net, const size_t NC, const size_t NP,
    const VVNodeType& mcp, const VVNodeType& mcp2, VDouble& rankingScore,
    const char* name = NULL)
{
  VNodeType rk(NP, 0);
  for (size_t c = 0; c < NC; c++) {
    for (size_t p = 0; p < NP; p++)
      rk[p] = p;
    common_sort_p_val_less(&rk[0], &rk[NP], &net.recommend.rcm[c][0]);
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
  const string methods[] = { "mass" };
  // const string methods[] = { "mass", "heat" };
  const size_t NMETHOD = sizeof(methods) / sizeof(methods[0]);
  //const int YEAR1 = 1995, YEAR2=2005;
  const int YEAR1 = 2009, YEAR2 = 2009;
  for (size_t iMethod = 0; iMethod < NMETHOD; iMethod++) {
    string method = methods[iMethod];
    cout << method << endl;

    for (int year = YEAR1; year <= YEAR2; year++) {
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
      // VVNodeType pc, pp;
      // recommend(net, mcp, pc, pp, method,
      //(dir + y1 + "." + method + ".txt").c_str());
      common_read2_0((DIR2 + y1 + "." + method + ".txt").c_str(), net.recommend.rcm);

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
      cout << year << "\t" << NC << "\t" << NP << "\t"
           << net.recommend.rcm.size() << endl;

      VNodeType k1(NC, 0);
      // count_k1(NC, NP, mcp, k1, (dir + y1 + ".k.txt").c_str());
      common_read1((DIR2 + y1 + ".k.txt").c_str(), k1);

      VNodeType k2(NC, 0);
      // count_k1(NC, NP, mcp2, k2, (dir + y2 + ".k.txt").c_str());
      common_read1((DIR2 + y2 + ".k.txt").c_str(), k2);

      VNodeType kNew(NC, 0);
      //count_kNew(NC, NP, mcp, mcp2, kNew, (dir + y1 + ".kNew.txt").c_str());
      common_read1((DIR2 + y1 + ".kNew.txt").c_str(), kNew);

      VDouble rankingScore(NC, 0);
      //count_rankingScore(net, NC, NP, mcp, mcp2, rankingScore,
      //(DIR2 + y1 + "." + method + ".rankingScore.txt").c_str());
      common_read1_0((DIR2 + y1 + "." + method + ".rankingScore.txt").c_str(),
          rankingScore);

      VDouble fc(NC, 0);
      common_read1_0((DIR2 + y1 + ".fc.txt").c_str(), fc);

      const size_t NRS = NP / 10 + 1;
      VNodeType nrs10(NRS, 0);
      VDouble rs10(NRS, 0), rs10_2(NRS, 0), fc10(NRS, 0);
      for (size_t c = 0; c < NC; c++) {
        if (kNew[c] <= 0)
          continue;
        NodeType i = k1[c] / 10;
        nrs10[i]++;
        const double t = rankingScore[c];
        rs10[i] += t;
        rs10_2[i] += t * t;
        fc10[i] += fc[c];
      }
      for (size_t i = 0; i < NRS; i++) {
        if (nrs10[i] > 0) {
          rs10[i] /= nrs10[i];
          rs10_2[i] = sqrt(rs10_2[i] / nrs10[i] - rs10[i] * rs10[i]);
          fc[i] /= nrs10[i];
        }
      }
      // common_save1((DIR2 + y1 + "." + method + ".rankingScoreStatic10.txt").c_str(),
      // rs10, '\n');
      // common_save1((DIR2 + y1 + "." + method + ".rankingScoreStatic10deviation.txt").c_str(), rs10_2, '\n');
      // common_save1((DIR2 + y1 + "." + method + ".fc10.txt").c_str(), fc10, '\n');

      VDouble cp(NP, 0), cpMean(NC, 0);
      common_read1_0((DIR2 + y1 + ".cp.txt").c_str(), cp);
      for (size_t c = 0; c < NC; c++) {
        if (k1[c] <= 0)
          continue;
        for (size_t p = 0; p < NP; p++) {
          if (mcp[c][p] != 0) {
            cpMean[c] += cp[p];
          }
        }
        cpMean[c] /= k1[c];
      }
      common_save1((DIR2 + y1 + ".cpMean.txt").c_str(), cpMean, '\n');

      VDouble cpNewMean(NC, 0);
      for (size_t c = 0; c < NC; c++) {
        if (kNew[c] <= 0)
          continue;
        for (size_t p = 0; p < NP; p++) {
          if (mcp[c][p] == 0 && mcp2[c][p] != 0) {
            cpNewMean[c] += cp[p];
          }
        }
        cpNewMean[c] /= kNew[c];
      }
      common_save1((DIR2 + y1 + "." + method + ".cpNewMean.txt").c_str(),
          cpNewMean, '\n');

    } // year
  }   // method

  SHOW_TIME(cout); // 显示系统时间
  return 0;
}

//**//**************************************************//**//*
#endif
