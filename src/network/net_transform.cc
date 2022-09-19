#include "net_transform.h"
#include "../common/common.h"

using namespace std;
using namespace common;
using namespace network;

// ******************************************************
int network::linkMatrC_2_p2p(VVNodeType& p2p, const VVChar& linkMatrC)
{
  const NodeType nodeSize = linkMatrC.size();
  p2p.resize(nodeSize);
  for (NodeType i = 0; i < nodeSize; i++) {
    p2p[i].clear();
    for (NodeType j = 0, num = 0; j <= nodeSize / 8; j++) {
      for (NodeType k = 0; k < 8 && num++ < nodeSize; k++) {
        if (linkMatrC[i][j] & (1 << k)) {
          p2p[i].push_back(j * 8 + k);
        }
      }
    }
  }
  return 0;
}

int network::p2p_2_linkMatr(VVDistType& linkMatr, const VVNodeType& p2p)
{
  const NodeType nodeSize = p2p.size();
  linkMatr.clear();
  linkMatr.resize(nodeSize);
  for (NodeType i = 0; i < nodeSize; i++) {
    linkMatr[i].assign(nodeSize, 0);
    for (VNodeTypeCItr itr = p2p[i].begin(); itr != p2p[i].end(); itr++) {
      linkMatr[i][*itr] = 1;
    }
  }
  return 0;
}

int network::p2pOut_2_p2pIn(VVNodeType& p2pIn, const VVNodeType& p2p)
{
  p2pIn.clear();
  for (NodeType i = 0; i < p2p.size(); i++) {
    for (VNodeTypeCItr j = p2p[i].begin(); j != p2p[i].end(); j++) {
      const NodeType t = *j;
      if (p2pIn.size() <= t)
        p2pIn.resize(t + 1);
      p2pIn[t].push_back(i);
    }
  }
  return 0;
}

int network::p2p_2_vvweight_sort(
    VVWeightType& vvweight, const VVNodeType& p2p)
{
  const NodeType nodeSize = p2p.size();
  vvweight.clear();
  vvweight.resize(nodeSize);
  VVWeightTypeItr wi = vvweight.begin();
  for (NodeType i = 0; i < nodeSize; wi++, i++) {
    for (VNodeTypeCItr jt = p2p[i].begin(), je = p2p[i].end(); jt != je;
         jt++) {
      wi->push_back(1);
      while (jt + 1 != je && *jt == *(jt + 1)) {
        wi->back()++;
        jt++;
      }
    }
  }
  return 0;
}

int network::vvweight_2_vvweightIn(VVWeightType& vvweightIn,
    const VVWeightType& vvweight, const VVNodeType& p2p)
{
  if (!vvweightIn.empty()) {
    ERROR();
    return -1;
  }
  for (NodeType i = 0; i < vvweight.size(); i++) {
    for (VNodeTypeCItr j = p2p[i].begin(); j != p2p[i].end(); j++) {
      const NodeType t = *j;
      if (vvweightIn.size() <= t)
        vvweightIn.resize(t + 1);
      vvweightIn[t].push_back(vvweight[i][t]);
    }
  }
  return 0;
}

int network::p2p_2_nodeSize(NodeType& nodeSize, const VVNodeType& p2p)
{
  nodeSize = p2p.size();
  for (VVNodeTypeCItr i = p2p.begin(); i != p2p.end(); i++)
    for (VNodeTypeCItr j = i->begin(); j != i->end(); j++)
      if (nodeSize <= *j)
        nodeSize = *j + 1;
  return 0;
}

int network::p2p_2_nodeDeg(VNodeType& nodeDeg, const VVNodeType& p2p)
{
  const NodeType nodeSize = p2p.size();
  nodeDeg.resize(nodeSize);
  for (NodeType i = 0; i < nodeSize; i++)
    nodeDeg[i] = p2p[i].size();
  return 0;
}

int network::nodeDeg_2_degArr(const VNodeType& nodeDeg, VNodeType& degArrVal,
    VNodeType& degArrSize, VNodeType& degArrSum)
{
  const NodeType nodeSize = nodeDeg.size();
  degArrVal.clear();
  degArrSize.clear();
  degArrSum.clear();
  MNodeType degArr;
  if (nodeSize <= 0)
    return 0;
  for (VNodeTypeCItr i = nodeDeg.begin(); i != nodeDeg.end(); i++)
    degArr[*i]++;
  NodeType degSize = degArr.size(), t = 0;
  degArrVal.assign(degSize, 0);
  degArrSize.assign(degSize, 0);
  for (MNodeTypeCItr itr = degArr.begin(); itr != degArr.end(); itr++, t++) {
    degArrVal[t] = itr->first;
    degArrSize[t] = itr->second;
  }
  degArrSize_2_degArrSum(degArrSum, degArrSize);
  return 0;
}

int network::nodeDeg_2_degArr_Sort(const VNodeType& nodeDeg,
    VNodeType& degArrVal, VNodeType& degArrSize, VNodeType& degArrSum)
{
  const NodeType nodeSize = nodeDeg.size();
  degArrVal.clear();
  degArrSize.clear();
  degArrSum.clear();
  if (nodeSize <= 0)
    return 0;
  degArrVal.push_back(nodeDeg[0]);
  degArrSize.push_back(1);
  for (NodeType i = 1, di = nodeDeg[0]; i < nodeSize; i++) {
    if (nodeDeg[i] == di)
      degArrSize.back()++;
    else {
      degArrVal.push_back(di = nodeDeg[i]);
      degArrSize.push_back(1);
    }
  }
  degArrSize_2_degArrSum(degArrSum, degArrSize);
  return 0;
}

int network::degArr_2_nodeSize(
    NodeType& nodeSize, const VNodeType& degArrSize)
{
  if (nodeSize != 0 || degArrSize.empty()) {
    ERROR();
    return -1;
  }
  for (VNodeTypeCItr i = degArrSize.begin(); i != degArrSize.end(); i++)
    nodeSize += *i;
  return 0;
}

int network::degArr_2_nodeDeg(VNodeType& nodeDeg, const VNodeType& degArrVal,
    const VNodeType& degArrSize)
{
  if (!nodeDeg.empty() || degArrVal.empty()
      || degArrVal.size() != degArrSize.size()) {
    ERROR();
    return -1;
  }
  for (NodeType i = 0; i < degArrVal.size(); i++) {
    for (NodeType s = 0, t = degArrVal[i]; s < degArrSize[i]; s++)
      nodeDeg.push_back(t);
  }
  return 0;
}

int network::degArrVal_2_degArrNo(
    MNodeType& degArrNo, const VNodeType& degArrVal)
{
  if (!degArrNo.empty())
    return -1;
  for (NodeType i = 0; i < degArrVal.size(); i++)
    degArrNo[degArrVal[i]] = i;
  return 0;
}

int network::degArrSize_2_degArrSum(
    VNodeType& degArrSum, const VNodeType& degArrSize)
{
  const NodeType degSize = degArrSize.size();
  degArrSum.resize(degSize);
  for (NodeType i = 0, sum = 0; i < degSize; i++)
    degArrSum[i] = sum += degArrSize[i];
  return 0;
}

int network::degArr_2_linkSize(LinkType& linkSize, const VNodeType& degArrVal,
    const VNodeType& degArrSize, const int dirFlag)
{
  linkSize = 0;
  const NodeType degSize = degArrVal.size();
  for (NodeType i = 0; i < degSize; i++)
    linkSize += (LinkType)degArrVal[i] * degArrSize[i];
  if (!dirFlag) {
    if (linkSize % 2 != 0)
      return -1;
    else
      linkSize /= 2;
  }
  return 0;
}

int network::degArr_2_linkSum(VLinkType& linkSum, const VNodeType& degArrVal,
    const VNodeType& degArrSize)
{
  const NodeType degSize = degArrVal.size();
  linkSum.resize(degSize);
  LinkType sum = 0;
  for (NodeType i = 0; i < degSize; i++)
    linkSum[i] = sum += (LinkType)degArrVal[i] * degArrSize[i];
  return 0;
}

int network::nodeDeg_2_linkSize(
    LinkType& linkSize, const VNodeType& nodeDeg, const int dirFlag)
{
  linkSize = 0;
  for (VNodeTypeCItr i = nodeDeg.begin(); i != nodeDeg.end(); i++)
    linkSize += *i;
  if (!dirFlag) {
    if (linkSize % 2 != 0) {
      return -1;
    } else
      linkSize /= 2;
  }
  return 0;
}

int network::degArrVal_2_deg2ArrVal(VDouble& deg2ArrVal,
    const VNodeType& degArrSize, const VNodeType& degArrVal,
    const LinkType linkSize, const int dirFlag)
{
  const NodeType degSize = degArrVal.size();
  deg2ArrVal.resize(degSize);
  LinkType sum = 0, l = dirFlag ? linkSize : linkSize * 2;
  for (NodeType i = 0; i < degSize; i++) {
    deg2ArrVal[i] = (sum + 0.5 * degArrSize[i] * degArrVal[i]) / l;
    sum += (LinkType)degArrSize[i] * degArrVal[i];
  }
  return 0;
}

int network::degArrWeight_2_netWeight(
    WeightSumType& netWeight, const VWeightSumType& degArrWeight)
{
  netWeight = 0;
  for (VWeightTypeCItr i = degArrWeight.begin(); i != degArrWeight.end(); i++)
    netWeight += *i;
  return 0;
}

int network::degArrWeight_2_deg2ArrVal(VDouble& deg2ArrVal,
    const VWeightSumType& degArrWeight, const WeightSumType netWeight)
{
  deg2ArrVal.resize(degArrWeight.size());
  double sum = 0;
  for (NodeType i = 0; i < degArrWeight.size(); i++) {
    deg2ArrVal[i] = (sum + 0.5 * degArrWeight[i]) / netWeight;
    sum += degArrWeight[i];
  }
  return 0;
}

int network::p2p_2_lkk(VVLinkType& lkk, const VVNodeType& p2p,
    const VNodeType& degNo, const NodeType degSize)
{
  lkk.clear();
  if (degSize <= 0)
    return 0;
  lkk.assign(degSize, VLinkType(degSize, 0));
  NodeType ti = 0;
  for (VVNodeTypeCItr i = p2p.begin(); i != p2p.end(); ti++, i++) {
    const NodeType ni = degNo[i->size()];
    LinkType* li = &lkk[ni][0];
    for (VNodeTypeCItr j = i->begin(); j != i->end(); j++) {
      if (ti <= *j) {
        const NodeType nj = degNo[p2p[*j].size()];
        if (ni >= nj)
          li[nj]++;
        else
          lkk[nj][ni]++;
      }
    }
  }
  return 0;
}

int network::p2p_2_lkk_dir(VVLinkType& lkkOutIn, const VVNodeType& p2p,
    const VNodeType& nodeDegOut, const VNodeType& nodeDegIn,
    MNodeType& degArrNoOut, MNodeType& degArrNoIn, const NodeType degOutSize,
    const NodeType degInSize)
{
  lkkOutIn.assign(degOutSize, VLinkType(degInSize, 0));
  if (degOutSize <= 0 || degInSize <= 0)
    return 0;
  VNodeTypeCItr nodeDegOutI = nodeDegOut.begin();
  for (VVNodeTypeCItr i = p2p.begin(); i != p2p.end(); i++) {
    LinkType* li = &lkkOutIn[degArrNoOut[*nodeDegOutI++]][0];
    for (VNodeTypeCItr j = i->begin(); j != i->end(); j++) {
      li[degArrNoIn[nodeDegIn[*j]]]++;
    }
  }
  return 0;
}

int network::p2p_2_lkk(VVLinkType& lkk, const VVNodeType& p2p,
    MNodeType& degArrNo, const NodeType degSize)
{
  lkk.clear();
  if (degSize <= 0)
    return 0;
  lkk.resize(degSize);
  for (NodeType i = 0; i < degSize; i++)
    lkk[i].assign(i + 1, 0);
  NodeType ti = 0;
  for (VVNodeTypeCItr i = p2p.begin(); i != p2p.end(); ti++, i++) {
    const NodeType ni = degArrNo[i->size()];
    LinkType* li = &lkk[ni][0];
    for (VNodeTypeCItr j = i->begin(); j != i->end(); j++) {
      if (ti < *j) {
        const NodeType nj = degArrNo[p2p[*j].size()];
        if (ni >= nj)
          li[nj]++;
        else
          lkk[nj][ni]++;
      }
    }
  }
  return 0;
}

int network::p2p_2_lkk_noDir(VVLinkType& lkk, const VVNodeType& p2p,
    MNodeType& degArrNo, const VNodeType& nodeDeg, const NodeType degSize)
{
  lkk.clear();
  if (degSize <= 0)
    return 0;
  lkk.resize(degSize);
  for (NodeType i = 0; i < degSize; i++)
    lkk[i].assign(i + 1, 0);
  NodeType ti = 0;
  for (VVNodeTypeCItr i = p2p.begin(); i != p2p.end(); ti++, i++) {
    const NodeType ni = degArrNo[nodeDeg[ti]];
    LinkType* li = &lkk[ni][0];
    for (VNodeTypeCItr j = i->begin(); j != i->end(); j++) {
      const NodeType nj = degArrNo[nodeDeg[*j]];
      if (ni >= nj)
        li[nj]++;
      else
        lkk[nj][ni]++;
    }
  }
  return 0;
}

int network::lkk_2_lkkSum(
    VVLinkType& lkkSum, const VVLinkType& lkk, const int dir)
{
  lkkSum = lkk;
  if (lkk.empty() || lkk[0].empty())
    return 0;
  for (VVLinkTypeItr i = lkkSum.begin(); i != lkkSum.end(); i++) {
    LinkType sum = 0;
    for (VLinkTypeItr j = i->begin(); j != i->end(); j++) {
      *j = sum += *j;
    }
  }
  const NodeType degSize = lkkSum.size();
  if (!dir) {
    for (NodeType i = 1; i < degSize; i++) {
      for (NodeType j = 0; j < i; j++) {
        lkkSum[i][j] += lkkSum[i - 1][j];
      }
      lkkSum[i][i] += lkkSum[i - 1][i - 1];
    }
  } else { // dir
    const NodeType degSize2 = lkkSum[0].size();
    for (NodeType i = 1; i < degSize; i++) {
      for (NodeType j = 0; j < degSize2; j++) {
        lkkSum[i][j] += lkkSum[i - 1][j];
      }
    }
  }
  return 0;
}

int network::link_2_nodeSize(NodeType& nodeSize, const VNodeType& link)
{
  nodeSize = 0;
  for (LinkType i = 0; i < link.size(); i++)
    if (link[i] >= nodeSize)
      nodeSize = link[i] + 1;
  return 0;
}

int network::link_2_p2p(
    VVNodeType& p2p, const VNodeType& link, NodeType& nodeSize)
{
  link_2_nodeSize(nodeSize, link);
  p2p.clear();
  p2p.resize(nodeSize);
  for (LinkType n = 0; n < link.size(); n += 2) {
    NodeType i = link[n], j = link[n + 1];
    p2p[i].push_back(j);
    p2p[j].push_back(i);
  }
  return 0;
}

int network::link_2_p2p(VVNodeType& p2p, const VNodeType& link,
    VVNodeType& p2pIn, NodeType& nodeSize, const int dirFlag)
{
  if (!dirFlag)
    return link_2_p2p(p2p, link, nodeSize);
  link_2_nodeSize(nodeSize, link);
  p2p.clear();
  p2p.resize(nodeSize);
  p2pIn.clear();
  p2pIn.resize(nodeSize);
  for (LinkType n = 0; n < link.size(); n += 2) {
    NodeType i = link[n], j = link[n + 1];
    p2p[i].push_back(j);
    p2pIn[j].push_back(i);
  }
  return 0;
}

int network::link_2_p2p_out(VVNodeType& p2p, const VNodeType& link,
    NodeType& nodeSize, const int dirFlag)
{
  return link_2_p2p_out_linkSize(
      p2p, link, nodeSize, link.size() / 2, dirFlag);
}

int network::link_2_p2p_out_linkSize(VVNodeType& p2p, const VNodeType& link,
    NodeType& nodeSize, LinkType linkSize, const int dirFlag)
{
  p2p.clear();
  link_2_nodeSize(nodeSize, link);
  p2p.resize(nodeSize);
  if (linkSize > link.size())
    linkSize = link.size();
  for (LinkType n = 0; n < linkSize; ++n) {
    NodeType i = link[n * 2], j = link[n * 2 + 1];
    p2p[i].push_back(j);
    if (!dirFlag)
      p2p[j].push_back(i);
  }
  return 0;
}

int network::link_2_p2p_in(VVNodeType& p2pIn, const VNodeType& link,
    NodeType& nodeSize, const int dirFlag)
{
  if (!dirFlag)
    return -1;
  link_2_nodeSize(nodeSize, link);
  p2pIn.clear();
  p2pIn.resize(nodeSize);
  for (LinkType n = 0; n < link.size(); n += 2) {
    NodeType i = link[n], j = link[n + 1];
    p2pIn[j].push_back(i);
  }
  return 0;
}

int network::p2p_2_link(
    VNodeType& link, const VVNodeType& p2p, const int dirFlag)
{
  link.clear();
  for (NodeType i = 0; i < p2p.size(); i++) {
    for (NodeType j = 0; j < p2p[i].size(); j++) {
      if (dirFlag || i <= p2p[i][j]) {
        link.push_back(i);
        link.push_back(p2p[i][j]);
      }
    }
  }
  return 0;
}

int network::link_2_lkk(VVLinkType& lkk, const VNodeType& link,
    const VNodeType& nodeDeg, MNodeType& degArrNo, const LinkType linkSize,
    const NodeType degSize)
{
  lkk.resize(degSize);
  lkk[0].assign(degSize, 0);
  for (NodeType i = 1; i < degSize; i++)
    lkk[i] = lkk[0];
  for (LinkType i = 0; i < linkSize; i++) {
    const NodeType x = degArrNo[nodeDeg[link[i * 2]]],
                   y = degArrNo[nodeDeg[link[i * 2 + 1]]];
    lkk[x][y]++;
    lkk[y][x]++;
  }
  return 0;
}

int network::vvweight_2_nodeWeight(VWeightType& nodeWeight,
    const VVNodeType& p2p, const VVWeightType& vvweight,
    WeightSumType& netWeight)
{
  nodeWeight.assign(p2p.size(), 0);
  netWeight = 0;
  for (NodeType i = 0; i < p2p.size(); i++) {
    if (p2p[i].size() <= 0)
      continue;
    WeightType t = 0;
    for (NodeType j = 0; j < p2p[i].size(); j++)
      t += vvweight[i][j];
    netWeight += nodeWeight[i] = t;
  }
  return 0;
}

int network::weightMatr_2_linkMatr(
    VVDistType& linkMatr, const VVWeightType& weightMatr)
{
  if (weightMatr.empty() || !linkMatr.empty()) {
    ERROR();
    return -1;
  }
  const NodeType nodeSize = weightMatr.size();
  linkMatr.clear();
  linkMatr.resize(nodeSize);
  for (NodeType i = 0; i < nodeSize; i++) {
    linkMatr[i].assign(nodeSize, 0);
    for (NodeType j = 0; j < nodeSize; j++) {
      if (weightMatr[i][j] != 0) {
        linkMatr[i][j] = 1;
      }
    }
  }
  return 0;
}

int network::nodeDegIO_2_nodeDeg(VNodeType& nodeDeg,
    const VNodeType& nodeDegOut, const VNodeType& nodeDegIn)
{
  if (!nodeDeg.empty() || nodeDegOut.empty() || nodeDegIn.empty()) {
    ERROR();
    return -1;
  }
  if (nodeDegOut.size() >= nodeDegIn.size()) {
    nodeDeg = nodeDegOut;
    for (NodeType i = 0; i < nodeDegIn.size(); i++)
      nodeDeg[i] += nodeDegIn[i];
  } else {
    nodeDeg = nodeDegIn;
    for (NodeType i = 0; i < nodeDegOut.size(); i++)
      nodeDeg[i] += nodeDegOut[i];
  }
  return 0;
}

int network::nodeWeightIO_2_nodeWeight(VWeightType& nodeWeight,
    const VWeightType& nodeWeightOut, const VWeightType& nodeWeightIn)
{
  if (nodeWeightOut.size() >= nodeWeightIn.size()) {
    nodeWeight = nodeWeightOut;
    for (NodeType i = 0; i < nodeWeightIn.size(); i++)
      nodeWeight[i] += nodeWeightIn[i];
  } else {
    nodeWeight = nodeWeightIn;
    for (NodeType i = 0; i < nodeWeightOut.size(); i++)
      nodeWeight[i] += nodeWeightOut[i];
  }
  return 0;
}

int network::nodeWeight_2_degArrWeight(VWeightSumType& degArrWeight,
    const VWeightSumType& nodeWeight, const VNodeType& nodeDeg,
    MNodeType& degArrNo, const NodeType degSize)
{
  degArrWeight.assign(degSize, 0);
  for (NodeType i = 0; i < nodeWeight.size(); i++) {
    degArrWeight[degArrNo[nodeDeg[i]]] += nodeWeight[i];
  }
  return 0;
}

int network::degArrWeight_2_degArrWeightSum(
    VWeightSumType& degArrWeightSum, const VWeightSumType& degArrWeight)
{
  const NodeType degSize = degArrWeight.size();
  degArrWeightSum.resize(degSize + 1);
  degArrWeightSum[0] = 0;
  WeightSumType sum = 0;
  for (NodeType i = 0; i < degSize; i++)
    degArrWeightSum[i + 1] = sum += degArrWeight[i];
  return 0;
}

int network::lkk3_2_lkk2(VVLkk2LinkType& lkk2, const VLkk3LinkType& lkk3,
    const VNodeType& degArrVal)
{
  const NodeType degSize = degArrVal.size();
  lkk2.clear();
  lkk2.resize(degSize);
  for (auto const& v : lkk3) {
    lkk2[v.y].push_back({ v.x, v.val });
  }
  return 0;
}

int network::lkk2_2_lkk3(VLkk3LinkType& lkk3, const VVLkk2LinkType& lkk2,
    const VNodeType& degArrVal)
{
  const NodeType degSize = degArrVal.size();
  lkk3.clear();
  for (NodeType i = 0; i < degSize; ++i) {
    for (auto const& lij : lkk2[i]) {
      lkk3.push_back({ lij.x, i, lij.y });
    }
  }
  return 0;
}

// *************************************************************
