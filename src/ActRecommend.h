#ifndef ACT_RECOMMEND_H
#define ACT_RECOMMEND_H

#include "net.h"

#ifdef ACT_RECOMMEND
//**//*****************************************************//*
int act_recommend_readP2p(VVNodeType& pu, VVNodeType& po, std::istream& is);
int act_recommend_start(const VNodeType p2pI, VDouble& o);
int act_recommend_mass(
    std::ostream& os, const VVNodeType& uP2p, const VVNodeType& oP2p);
int act_recommend_mass(
    const char* name, const VVNodeType& uP2p, const VVNodeType& oP2p);
int act_recommend_heat(
    std::ostream& os, const VVNodeType& uP2p, const VVNodeType& oP2p);
int act_recommend_heat(
    const char* name, const VVNodeType& uP2p, const VVNodeType& oP2p);
int act_recommend_pagerank(
    std::ofstream& os, const VVNodeType& p2p, VDouble& v);
int act_recommend_pagerank(
    const char* name, const VVNodeType& p2p, VDouble& v);

//**//*****************************************************//*
#endif // ACT_RECOMMEND
#endif // ACT_RECOMMEND_H
