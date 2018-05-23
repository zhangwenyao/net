// g++ -o main.exe *.cpp -O3 -Wall
#include "main.h"
#ifdef MAIN_FITNESS_COMPLEXITY_RECOMMEND

#include "common.h"
#include "networks.h"
using namespace std;
// *************************************************//*****
int main(int argc, char** argv)
{
  SHOW_TIME(cout); // 显示系统时间

  const string DIR_DATA = "data/complexity/data/";
  const string methods[] = { "mass", "heat", "hybrid" };
  // const string methods[] = { "hybrid" };
  const size_t NMETHOD = sizeof(methods) / sizeof(methods[0]);
  const int YEAR1 = 1995, YEAR2 = 2014;
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
      common_read2_0((DIR_DATA + y1 + ".mcp.txt").c_str(), mcp);
      const NodeType NC = mcp.size(), NP = mcp[0].size();
      cout << "\t" << year << "\t" << NC << "\t" << NP << endl;

      Networks net;
      net.saveName = DIR_DATA + y1;
      net.recommend.lambda = 0.1;
      linkMatr_2_p2p2(
          net.recommend.user_p_object, net.recommend.object_p_user, mcp);
      net.act_recommend(method.c_str());
      common_save2((DIR_DATA + y1 + "." + method + ".rcm.txt").c_str(),
          net.recommend.rcm);
      // common_read2_0((DIR_DATA + y1 + "." + method + ".txt").c_str(),
      // net.recommend.rcm);

    } // year
  }   // method

  SHOW_TIME(cout); // 显示系统时间
  return 0;
}

// *************************************************//*****
#endif
