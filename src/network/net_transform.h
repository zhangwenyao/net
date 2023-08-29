#ifndef NETWORK__NET_TRANSFORM_H_
#define NETWORK__NET_TRANSFORM_H_

#include "net.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace network {
// *******************************************************
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
int p2pOut_2_p2pIn(VVNodeType& p2pIn, const VVNodeType& p2p);
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
int link_2_p2p(VVNodeType& p2p, const VNodeType& link, NodeType& nodeSize);
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

int lkk3_2_lkk2(VVLkk2LinkType& lkk2, const VLkk3LinkType& lkk3,
    const VNodeType& degArrVal);
int lkk2_2_lkk3(VLkk3LinkType& lkk3, const VVLkk2LinkType& lkk2,
    const VNodeType& degArrVal);

} // end namespace network

// *******************************************************
#include "net_transform_template.h"
#endif // NET_H
