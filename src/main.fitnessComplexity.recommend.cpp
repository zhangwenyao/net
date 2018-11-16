#include "main.h"
#ifdef MAIN_FITNESS_COMPLEXITY_RECOMMEND

#include "common.h"
#include "networks.h"
using namespace std;
// ********************************************************
int main_fitness_complexity_recommend(int argc, char** argv)
{
  const string DIR0 = "data/complexity/OEC.sitc_rev2/",
               DIR_DATA0 = DIR0 + "data0/", DIR_DATA = DIR0 + "data/",
               DIR_INFO = DIR0 + "info/";
  const size_t YEAR1 = 2001, YEAR2 = 2014;
  // const string methods[] = { "mass", "heat", "hybrid", "proximity" };
  const string methods[] = { "proximity" };
  const size_t NMETHOD = sizeof(methods) / sizeof(methods[0]);

  for (size_t iMethod = 0; iMethod < NMETHOD; iMethod++) {
    string method = methods[iMethod];
    INFORM(method);

    for (size_t year = YEAR1; year <= YEAR2; year++) {
      VVDistType mcp;
      _ERR(common_read2_0(
          (DIR_DATA + to_string(year) + ".mcp.txt").c_str(), mcp));
      const NodeType NC = mcp.size(), NP = mcp[0].size();
      cout << "\t" << year << "\t" << NC << "\t" << NP << endl;

      Networks net;
      net.saveName = DIR_DATA + to_string(year);
      net.recommend.lambda = 0.1;
      _ERR(linkMatr_2_p2p2(
          net.recommend.user_p_object, net.recommend.object_p_user, mcp));
      common_change_type_vector2(mcp, net.recommend.user_object);
      net.act_recommend(method.c_str());
      _ERR(common_save2(
          (DIR_DATA + to_string(year) + "." + method + ".rcm.txt").c_str(),
          net.recommend.rcm));
      // common_read2_0((DIR_DATA + to_string(year) + "." + method +
      // ".txt").c_str(), net.recommend.rcm);

    } // year
  }   // method

  return 0;
}

// ********************************************************
#endif
