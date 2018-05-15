// g++ -o main.exe *.cpp -O3 -Wall
#include "main.h"
#ifdef MAIN_FITNESS_COMPLEXITY_RECOMMEND

#include "common.h"
#include "networks.h"
using namespace std;
//**//**************************************************//**//*
int main(int argc, char** argv)
{
  SHOW_TIME(cout); // 显示系统时间

  const string dir = "../../swiss/economic-complexity/201803/1995-2010/";
  //const string methods[] = { "mass", "heat", "hybrid" };
  const string methods[] = { "hybrid" };
  const size_t NMETHOD = sizeof(methods) / sizeof(methods[0]);
  const int YEAR1 = 1995, YEAR2 = 2010;
  //const int YEAR1 = 2000, YEAR2 = 2000;
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

      VVDistType mcp;
      common_read2_0((dir + y1 + ".mcp.txt").c_str(), mcp);
      const size_t NC = mcp.size(), NP = mcp[0].size();
      cout << "\t" << year << "\t" << NC << "\t" << NP << endl;

      Networks net;
      net.saveName = dir + y1;
      net.recommend.lambda = 0.1;
      linkMatr_2_p2p2(net.recommend.user_p_object, net.recommend.object_p_user, mcp);
      net.act_recommend(method.c_str());
      //cout << net.recommend.rcm << endl;
      common_save2((dir + y1 + "." + method + ".rcm.txt").c_str(), net.recommend.rcm);
      //common_read2_0((dir + y1 + "." + method + ".txt").c_str(), net.recommend.rcm);

      //VVNodeType mcp2;
      //common_read2_0((dir + y2 + ".mcp.txt").c_str(), mcp2);
      //if (mcp2.size() != NC || net.recommend.rcm.size() != NC) {
      //ERROR();
      //return -1;
      //}
      //for (size_t c = 0; c < NC; c++) {
      //if (mcp[c].size() != NP || mcp2[c].size() != NP) {
      //ERROR(mcp[c].size(), "\t", mcp2.size());
      //break;
      //}
      //}
      //cout << year << "\t" << NC << "\t" << NP << "\t" << net.recommend.rcm.size() << endl;

      //VNodeType k1(NC, 0);
      //common_read1((dir + y1 + ".k.txt").c_str(), k1);

      //VNodeType k2(NC, 0);
      //common_read1((dir + y2 + ".k.txt").c_str(), k2);

      //VNodeType kNew(NC, 0);
      //common_read1((dir + y1 + ".kNew.txt").c_str(), kNew);

    } // year
  }   // method

  SHOW_TIME(cout); // 显示系统时间
  return 0;
}

//**//**************************************************//**//*
#endif