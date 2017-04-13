#include "ActRecommend.h"
#ifdef ACT_RECOMMEND

#include "common.h"
using namespace std;

//**//*****************************************************//*
int act_recommend_readP2p(VVNodeType& pu, VVNodeType& po, istream& is) {
  if (!is) {
    ERROR();
    return -1;
  }
  common_read2(is, pu);
  p2p_2_p2pIn(po, pu);
  return 0;
}

int act_recommend_start(VNodeType p2pI, VDouble& o) {
  for (VNodeTypeItr p = p2pI.begin(); p != p2pI.end(); p++) o[*p] = 1;
  return 0;
}

int act_recommend_mass(VNodeType p2pI, VDouble& o, const double t) {
  if (p2pI.empty()) return 0;
  for (VNodeTypeItr p = p2pI.begin(); p != p2pI.end(); p++) o[*p] += t;
  return 0;
}

int act_recommend_heat(VNodeType p2pJ, VDouble u, double& t) {
  t = 0;
  if (p2pJ.empty()) return 0;
  for (VNodeTypeItr p = p2pJ.begin(); p != p2pJ.end(); p++) t += u[*p];
  t /= p2pJ.size();
  return 0;
}
//**//*****************************************************//*
#endif  // ACT_RECOMMEND
