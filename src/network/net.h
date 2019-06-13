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
//#define NET_DEGREE //节点度分布
//#define DEG_POISSON //泊松分布
//#define DEG_POWER //幂律分布

//#define NET_EXTREMUM // 特例网络
//#define NET_RANDOM // 随机网络
#define NET_BA // BA网络
//#define NET_GRID     // 网格网络
//#define NET_ACTOR     // 演员合作网络

const bool STAT_TYPE_DIRAA = 0; // 0 : OutIn, 1 : OutIn OutOut InOut InIn
#define STAT_PEARSON
#define STAT_SPEARMAN
//#define MODEL_GAUSS
//#define MODEL_EXP
//#define STAT_KENDALLI
//#define STAT_RELATIVITY
#define STAT_CORRELATION2
//#define STAT_BETWEENNESS
//#define STAT_MODULARITY
//#define STAT_CLUSTER
//#define STAT_SIMILARITY

//#define ACT_SIS
//#define ACT_SPREAD
//#define ACT_FITNESS_COMPLEXITY
//#define ACT_RECOMMEND

// *******************************************************
int nodeDeg_update_nodeMap(VNodeType& nodeDeg, const VRNodeType& nodeMap);

// *******************************************************
int init_linkMatrC(VVChar& linkMatrC, const NodeType nodeSize);
int linkMatr_fix_0(VVDistType& linkMatr, const DistType MaxDist = DistMax);
int linkMatr_fix_max(VVDistType& linkMatr, const DistType MaxDist = DistMax);

template <typename T, typename T2>
int linkMatr_2_nodeDeg(
    std::vector<T>& nodeDeg, const std::vector<std::vector<T2>>& linkMatr);
template <typename T, typename T2>
int linkMatr_2_p2p(std::vector<std::vector<T2>>& p2p,
    const std::vector<std::vector<T>>& linkMatr);
template <typename T, typename T2>
int linkMatr_2_p2pIn(std::vector<std::vector<T2>>& p2pIn,
    const std::vector<std::vector<T>>& linkMatr);
int linkMatrC_2_p2p(VVNodeType& p2p, const VVChar& linkMatrC);

int p2p_2_linkMatr(VVDistType& linkMatr, const VVNodeType& p2p);
int p2p_2_p2pIn(VVNodeType& p2pIn, const VVNodeType& p2p);
int p2p_2_vvweight_sort(VVWeightType& vvweight, const VVNodeType& p2p);

int p2p_2_nodeSize(NodeType& nodeSize, const VVNodeType& p2p);
int p2p_2_nodeDeg(VNodeType& nodeDeg, const VVNodeType& p2p);
int nodeDeg_2_degArr(const VNodeType& nodeDeg, VNodeType& degArrVal,
    VNodeType& degArrSize, VNodeType& degArrSum);
int nodeDeg_2_degArr_Sort(const VNodeType& nodeDeg, VNodeType& degArrVal,
    VNodeType& degArrSize, VNodeType& degArrSum);
int degArr_2_nodeSize(NodeType& nodeSize, const VNodeType& degArrSize);
int degArr_2_nodeDeg(VNodeType& nodeDeg, const VNodeType& degArrVal,
    const VNodeType& degArrSize);
int degArrVal_2_degArrNo(MNodeType& degArrNo, const VNodeType& degArrVal);

int degArrSize_2_degArrSum(VNodeType& degArrSum, const VNodeType& degArrSize);
int degArr_2_linkSize(LinkType& linkSize, const VNodeType& degArrVal,
    const VNodeType& degArrSize, const int dirFlag = 0);
int degArr_2_linkSum(VLinkType& linkSum, const VNodeType& degArrVal,
    const VNodeType& degArrSize);
int nodeDeg_2_linkSize(
    LinkType& linkSize, const VNodeType& nodeDeg, const int dirFlag = 0);
int degArrVal_2_deg2ArrVal(VDouble& deg2ArrVal, const VNodeType& degArrSize,
    const VNodeType& degArrVal, const LinkType linkSize,
    const int dirFlag = 0);
int degArrWeight_2_netWeight(
    WeightSumType& netWeight, const VWeightSumType& degArrWeight);
int degArrWeight_2_deg2ArrVal(VDouble& deg2ArrVal,
    const VWeightSumType& degArrWeight, const WeightSumType netWeight);

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

int p2p_2_lkk(VVLinkType& lkk, const VVNodeType& p2p, const VNodeType& degNum,
    const NodeType degSize);
int p2p_2_lkk_dir(VVLinkType& lkkOutIn, const VVNodeType& p2p,
    const VNodeType& nodeDegOut, const VNodeType& nodeDegIn,
    MNodeType& degArrNoOut, MNodeType& degArrNoIn, const NodeType degOutSize,
    const NodeType degInSize);
int p2p_2_lkk(VVLinkType& lkk, const VVNodeType& p2p, MNodeType& degArrNo,
    const NodeType degSize);
int p2p_2_lkk_noDir(VVLinkType& lkk, const VVNodeType& p2p,
    MNodeType& degArrNo, const VNodeType& nodeDeg, const NodeType degSize);
int lkk_dir_2_nDir(VVLinkType& lkk);
int lkk_nDir_2_dir(VVLinkType& lkk);
int lkk_2_lkkSum(VVLinkType& lkkSum, const VVLinkType& lkk, const int dir);
int link_2_nodeSize(NodeType& nodeSize, const VNodeType& link);
int link_2_p2p(VVNodeType& p2p, const VNodeType& link, VVNodeType& p2pIn,
    NodeType& nodeSize, const int dirFlag);
int link_2_p2p_out(VVNodeType& p2p, const VNodeType& link, NodeType& nodeSize,
    const int dirFlag);
int link_2_p2p_out_linkSize(VVNodeType& p2p, const VNodeType& link,
    NodeType& nodeSize, LinkType linkSize, const int dirFlag);
int link_2_p2p_in(VVNodeType& p2pIn, const VNodeType& link,
    NodeType& nodeSize, const int dirFlag);
int p2p_2_link(VNodeType& link, const VVNodeType& p2p, const int dirFlag);
int vvweight_2_vvweightIn(VVWeightType& vvweightIn,
    const VVWeightType& vvweight, const VVNodeType& p2p);
int weightMatr_2_linkMatr(
    VVDistType& linkMatr, const VVWeightType& weightMatr);

int link_2_lkk(VVLinkType& lkk, const VNodeType& link,
    const VNodeType& nodeDeg, MNodeType& degArrNo, const LinkType linkSize,
    const NodeType degSize);

int vvweight_2_nodeWeight(VWeightType& nodeWeight, const VVNodeType& p2p,
    const VVWeightType& vvweight, WeightSumType& netWeight);
int nodeDegIO_2_nodeDeg(VNodeType& nodeDeg, const VNodeType& nodeDegOut,
    const VNodeType& nodeDegIn);
int nodeWeightIO_2_nodeWeight(VWeightType& nodeWeight,
    const VWeightType& nodeWeightOut, const VWeightType& nodeWeightIn);
int nodeWeight_2_degArrWeight(VWeightSumType& degArrWeight,
    const VWeightSumType& nodeWeight, const VNodeType& nodeDeg,
    MNodeType& degArrNo, const NodeType degSize);
int degArrWeight_2_degArrWeightSum(
    VWeightSumType& degArrWeightSum, const VWeightSumType& degArrWeight);

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

} // end namespace network

// *******************************************************
#include "net_io.h"
// *******************************************************
#include "net_template.h"
#endif // NET_H
