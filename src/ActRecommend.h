#ifndef ACT_RECOMMEND_H
#define ACT_RECOMMEND_H

#include "net.h"

#ifdef ACT_RECOMMEND
//**//*****************************************************//*
int act_recommend_readP2p(VVNodeType& pu, VVNodeType& po, istream& is);
int act_recommend_start(VNodeType p2pI, VDouble& o);
int act_recommend_mass(VNodeType p2pI, VDouble& o, const double t);
int act_recommend_heat(VNodeType p2pJ, VDouble u, double& t);

//**//*****************************************************//*
#endif  // ACT_RECOMMEND
#endif  // ACT_RECOMMEND_H
