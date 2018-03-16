#ifndef ACT_RECOMMEND_H
#define ACT_RECOMMEND_H

#include "net.h"

#ifdef ACT_RECOMMEND
//**//*****************************************************//*
int act_recommend_readP2p(VVNodeType& pu, VVNodeType& po, std::istream& is);
int act_recommend_start(const VNodeType p2pI, VDouble& o);
int act_recommend_mass_1(VDouble& o2, const VVNodeType& uP2p,
    const VVNodeType& oP2p, const NodeType i);
int act_recommend_mass(
    VVDouble& rcm, const VVNodeType& uP2p, const VVNodeType& oP2p);
int act_recommend_heat_1(VDouble& o2, const VVNodeType& uP2p,
    const VVNodeType& oP2p, const NodeType i);
int act_recommend_heat(
    VVDouble& rcm, const VVNodeType& uP2p, const VVNodeType& oP2p);
int act_recommend_pagerank(const VVNodeType& p2p, VDouble& v);
int act_recommend_pagerank(
    std::ofstream& os, const VVNodeType& p2p, VDouble& v);
int act_recommend_pagerank(
    const char* name, const VVNodeType& p2p, VDouble& v);
int act_recommend_commonNeighbour(const VVNodeType& p2p, VDouble& v);

int recommend_RAC(const VDouble& v0, const VDouble& v, double& r);
int recommend_RMAE(const VDouble& v0, const VDouble& v, double& r);
int recommend_NMAE(const VDouble& v0, const VDouble& v, double& r);
int recommend_F(const VNodeType& v0, const VNodeType& v, double& recall,
    double& precision, double& F);
int recommend_rankingScore(const VNodeType& R, const VNodeType& L, double& rs);
int recommend_rankingScore(
    const VNodeType& rk, const VNodeType& L0, const VNodeType& L, double& rs);

//**//*****************************************************//*
#endif // ACT_RECOMMEND
#endif // ACT_RECOMMEND_H
