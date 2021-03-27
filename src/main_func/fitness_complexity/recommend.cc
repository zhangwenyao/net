#include "recommend.h"
#ifdef MAIN_FITNESS_COMPLEXITY_RECOMMEND

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;

// ********************************************************
int main_func::fitness_complexity::recommend(int argc, char** argv)
{
  for (size_t iMethod = 0; iMethod < NMETHOD; iMethod++) {
    string method = methods[iMethod];
    INFORM(method);

    for (size_t year = YEAR1; year <= YEAR2; year++) {
      VVDistType mcp;
      _ERR(common_read2_0(
          (DIR_DATA + to_string(year) + mcp_dir2).c_str(), mcp));
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
          (DIR_DATA + to_string(year) + "." + method + rcm_dir2).c_str(),
          net.recommend.rcm));
      // common_read2_0((DIR_DATA + to_string(year) + "." + method +
      // rcm_dir2).c_str(), net.recommend.rcm);

    } // year
  }   // method

  return 0;
}

// ********************************************************
#endif
