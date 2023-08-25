#ifndef NETWORK__NET_H_
#define NETWORK__NET_H_

#include "type.h"
#include <cfloat>
#include <climits>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace network {
const std::string NET_VERSION = "net3.0: " __DATE__ ", " __TIME__;
// *******************************************************
#define NET_DEGREE //节点度分布
//#define DEG_POISSON //泊松分布
#define DEG_POWER //幂律分布

//#define NET_EXTREMUM // 特例网络
//#define NET_RANDOM // 随机网络
//#define NET_BA // BA网络
//#define NET_GRID     // 网格网络
//#define NET_ACTOR     // 演员合作网络

// const bool STAT_TYPE_DIRAA = 0; // 0 : OutIn, 1 : OutIn OutOut InOut InIn
// #define STAT_STAT
// #define STAT_PEARSON
// #define STAT_SPEARMAN
// #define SPEARMAN_NEI2
//#define MODEL_GAUSS
//#define MODEL_EXP
//#define STAT_KENDALLI
//#define STAT_RELATIVITY
//#define STAT_CORRELATION2
//#define STAT_BETWEENNESS
//#define STAT_MODULARITY
//#define STAT_CLUSTER
//#define STAT_SIMILARITY

//#define ACT_SIS
//#define ACT_SPREAD
#define ACT_FITNESS_COMPLEXITY
//#define ACT_RECOMMEND
// #define ACT_CORRELATION

// *******************************************************
int nodeDeg_update_nodeMap(VNodeType& nodeDeg, const VRNodeType& nodeMap);

// *******************************************************
int init_linkMatrC(VVChar& linkMatrC, const NodeType nodeSize);
int linkMatr_fix_0(VVDistType& linkMatr, const DistType MaxDist = DistMax);
int linkMatr_fix_max(VVDistType& linkMatr, const DistType MaxDist = DistMax);

int check_nodeDeg0(const VNodeType& nodeDeg);
int fix_degArr_kExtremum(VNodeType& degArrSize, const VNodeType& degArrVal,
    const VDouble& degArrProb);
int fix_degArr_linkSize(VNodeType& degArrSize, const VNodeType& degArrVal,
    const VDouble& degArrProb, LinkType& linkSize);
int fix_degArr_linkSize3(VNodeType& degArrSize, const VNodeType& degArrVal,
    const VDouble& degArrProb, LinkType& linkSize);
int fix_degArr_linkSize2(VNodeType& degArrSize, const VNodeType& degArrVal,
    const VDouble& degArrProbSum, LinkType& linkSize);
int fix_nodeDeg(VNodeType& nodeDeg, const VDouble& degArrProb,
    const VNodeType& degArrVal, LinkType& linkSize);
int fix_degArrSize_0(VNodeType& degArrSize, VNodeType& degArrVal);

// *******************************************************
int sort_p2p(VVNodeType& p2p);
int fix_p2p(VVNodeType& p2p, const int dirFlag = 0);
int qsort_p2p(VVNodeType& p2p, const VVDistType& linkMatr);

int del_pij(const NodeType i, const NodeType j, VVNodeType& p2p,
    VVNodeType& p2pIn, const int dirFlag);
int add_pij(const NodeType i, const NodeType j, VVNodeType& p2p,
    VVNodeType& p2pIn, const int dirFlag);

int sort_link_betwEdge(
    VNodeType& link, VVDouble& betwEdge, LinkType linkSize = 0);

// *******************************************************
int addLink_linkMatrC_ranNode(
    VVChar& linkMatrC, LinkType& linkRemain); // 每次直接随机抽取两个点连边
int addLink_linkMatr_ranNode(
    VVDistType& linkMatr, LinkType& linkRemain); // 每次直接随机抽取两个点连边
int addLink_linkMatrC_ranNode2(VVChar& linkMatrC, VNodeType& nodeDeg,
    VNodeType& p2pSize, VNodeType& remPoiNum, LinkType& linkRemain,
    const LinkType tryCount = 10); // 每次直接随机抽取两个点连边
int addLink_linkMatr_ranNode2(VVDistType& linkMatr, VNodeType& nodeDeg,
    VNodeType& p2pSize, VNodeType& remPoiNum, LinkType& linkRemain,
    const LinkType tryCount = 10); // 每次直接随机抽取两个点连边

int addLink_p2p_ranNode(VVNodeType& p2p, VNodeType& nodeDeg,
    VNodeType& remPoiNum, LinkType& linkRemain,
    const LinkType tryCount); // 每次直接随机抽取两个点连边
int addLink_p2p_ranNode0(VVNodeType& p2p, VNodeType& link, VNodeType& nodeDeg,
    VNodeType& remPoiNum, LinkType& linkRemain,
    const LinkType tryCount); // 每次直接随机抽取两个点连边

int addLink_linkMatrC_proNode(VVChar& linkMatrC, LinkType& linkSize,
    const double p); // 所有点按概率p连边
int addLink_linkMatr_proNode(VVDistType& linkMatr, LinkType& linkSize,
    const double p); // 所有点按概率p连边

int addLink_p2p_proDeg(VVNodeType& p2p, VNodeType& link,
    const VNodeType& nodeDeg, const NodeType kMax, VNodeType& remPoiNum,
    LinkType& linkRemain,
    const LinkType tryCount); // 随机选节点，概率正比于节点度

int addLink_p2p_ranLink(VVNodeType& p2p, VNodeType& nodeDeg,
    NodeType& remPoiSize, LinkType& linkRemain, VNodeType& link,
    const LinkType tryCount); // 所有度中随机选
int addLink_p2p_ranLink_lkkProb(VVNodeType& p2p, const VNodeType& nodeDeg,
    VVDouble& lkkProb, MNodeType& degArrNo, NodeType& remPoiSize,
    LinkType& linkRemain, VNodeType& link,
    const LinkType tryCount); // 剩余度中随机选点，且概率正比于lkkProb

int delLink_p2p_ranLink(VVNodeType& p2p, VNodeType& nodeDeg,
    VNodeType& remPoiNum, LinkType& linkRemain, const LinkType linkSize,
    VNodeType& link,
    LinkType delCount); // 随机选边
int delLink_linkMatrC_ranNode(VVChar& linkMatrC, const NodeType nodeSize,
    VNodeType& nodeDeg, VNodeType& p2pSize, VNodeType& remPoiNum,
    LinkType& linkRemain, const LinkType linkSize,
    LinkType delCount); // 随机选点删边
int delLink_linkMatrC_randNode10(VVChar& linkMatrC, const NodeType nodeSize,
    VNodeType& nodeDeg, VNodeType& p2pSize, VNodeType& remPoiNum,
    LinkType& linkRemain, const LinkType linkSize,
    LinkType delCount); // 随机选点删边
int delLink_p2p_ranNode(VVNodeType& p2p, const NodeType nodeSize,
    const VNodeType& nodeDeg, VNodeType& remPoiNum, NodeType& remPoiSize,
    LinkType& linkRemain, const LinkType linkSize,
    LinkType delCount); // 随机选点删边
int delLink_p2p_ranNode1(VVNodeType& p2p, const NodeType nodeSize,
    VNodeType& nodeDeg, VNodeType& remPoiNum, NodeType& remPoiSize,
    LinkType& linkRemain, const LinkType linkSize,
    LinkType delCount); // 随机选点再选边删除
int delLink_link_ranLink(VNodeType& link, LinkType delCount); //随机删边
int delNode_p2p_max(VVNodeType& p2p, const NodeType n); //删除节点 [n,...)
//int delLink_p2p_ranLink_lkkProb(VVNodeType& p2p, VNodeType& nodeDeg,
    //VVDouble& lkkProb, MNodeType& degArrNo, NodeType& remPoiSize,
    //LinkType& linkRemain, const LinkType linkSize, VNodeType& link,
    //LinkType delCount); // 随机选边删除，且概率正比于lkkProb

int addLink_p2p_full(VVNodeType& p2p, NodeType M = 0,
    const NodeType n = 0); // 添加节点 [n,M) 的全连通网络
int addLink_p2p_link_full(VVNodeType& p2p, VNodeType& link, NodeType M = 0,
    const NodeType n = 0); // 添加节点 [n,M) 的全连通网络

// *******************************************************
int check_p2pSize_linkSize(const VVNodeType& p2p, const LinkType linkSize);
int check_p2p(const VVNodeType& p2p);
int check_p2p_nodeDeg(const VVNodeType& p2p, const VNodeType& nodeDeg);
int check_link(VNodeType& link);

int sort_link_greater_1(VNodeType& link, const VNodeType& nodeDeg);
int sort_link_smaller_1(VNodeType& link, const VNodeType& nodeDeg);
int sort_link_num_greater_1(VNodeType& link);
int sort_link_num_smaller_1(VNodeType& link);
int sort_link_greater_all(VNodeType& link, const VNodeType& p2pSize);
int sort_link_num_greater_all(VNodeType& link);
int sort_link_smaller_all(VNodeType& link, const VNodeType& p2pSize);
int sort_link_num_smaller_all(VNodeType& link);

// *************************************************************
int exchange_linkC_deg_same(VVChar& linkMatrC, VNodeType& link,
    const VNodeType& p2pSize, LinkType count);
int exchange_linkC_degDiff(VVChar& linkMatrC, VNodeType& link,
    const VNodeType& p2pSize, LinkType count);
int exchange_link_deg_same(VVDistType& linkMatr, VNodeType& link,
    const VNodeType& p2pSize, LinkType count);
int exchange_link_deg_diff(VVDistType& linkMatr, VNodeType& link,
    const VNodeType& p2pSize, LinkType count);

int exchange_linkC_num_same(
    VVChar& linkMatrC, VNodeType& link, LinkType count);
int exchange_linkC_num_diff(
    VVChar& linkMatrC, VNodeType& link, LinkType count);
int exchange_link_num_same(
    VVDistType& linkMatr, VNodeType& link, LinkType count);
int exchange_link_num_diff(
    VVDistType& linkMatr, VNodeType& link, LinkType count);

int count_sameAdiff(LinkType& sum, LinkType& sum1, LinkType& sum3,
    LinkType& sum4, VLinkType& link, VNodeType& nodeDeg);

int rewire_rho(
    LinkType L, const double rho, VVNodeType& p2p, VNodeType& link);
int rewire_rho_dir(
    LinkType L, const double rho, VVNodeType& p2p, VNodeType& link);
int change_p2p_link(
    VVNodeType& p2p, const NodeType i1, const NodeType i2, const NodeType j2);
} // end namespace network

// *******************************************************
#include "net_io.h"
#include "net_transform.h"
// *******************************************************
#include "net_template.h"
#endif // NET_H
