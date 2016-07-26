#ifndef ACT_RECOMMEND_H
#define ACT_RECOMMEND_H

#include "net.h"

#ifdef NET_RECOMMEND
//**//*****************************************************//*
int recommend_readP2p(VVNodeType& pu, VVNodeType& po, istream& is);
int recommend_start(VNodeType p2pI, VDouble& o);
int recommend_mass(VNodeType p2pI, VDouble& o, const double t);
int recommend_heat(VNodeType p2pJ, VDouble u, double& t);

//**//*****************************************************//*
#endif  // NET_RECOMMEND
#endif  // ACT_RECOMMEND_H

