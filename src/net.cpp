#include "net.h"
#include "common.h"

using namespace std;

//**//****************************************************//*
ostream& operator<<(ostream& os, const RNodeType& r) {
  os << r.start << '\t' << r.end;
  return os;
}

istream& operator>>(istream& is, RNodeType& r) {
  is >> r.start >> r.end;
  return is;
}

int save_VRNodeType_start(ostream& os, const VRNodeType& v, const char c) {
  if (!os) return -1;
  if (!v.empty()) {
    VRNodeTypeCItr i = v.begin();
    os << (i++)->start;
    while (i != v.end()) os << c << (i++)->start;
  }
  return 0;
}

int save_VRNodeType_start(const char* name, const VRNodeType& v, const char c) {
  if (name == NULL || name[0] == '\0') return -1;
  ofstream os(name);
  if (!os) return -1;
  save_VRNodeType_start(os, v, c);
  os.close();
  return 0;
}

int save_VRNodeType_end(ostream& os, const VRNodeType& v, const char c) {
  if (!os) return -1;
  if (!v.empty()) {
    VRNodeTypeCItr i = v.begin();
    os << (i++)->end;
    while (i != v.end()) os << c << (i++)->end;
  }
  return 0;
}

int save_VRNodeType_end(const char* name, const VRNodeType& v, const char c) {
  if (name == NULL || name[0] == '\0') return -1;
  ofstream os(name);
  if (!os) return -1;
  save_VRNodeType_end(os, v, c);
  os.close();
  return 0;
}

//**//****************************************************//*
int init_linkMatrC(VVChar& linkMatrC, const NodeType nodeSize) {
  const NodeType len = nodeSize / 8 + 1;
  linkMatrC.resize(nodeSize);
  linkMatrC[0].assign(len, 0);
  for (NodeType i = 1; i < nodeSize; i++) linkMatrC[i] = linkMatrC[0];
  return 0;
}

//**//****************************************************//*
int linkMatr_fix_0(VVDistType& linkMatr, const DistType MaxDist) {
  const NodeType nodeSize = linkMatr.size();
  for (NodeType i = 0; i < nodeSize; i++) {
    for (NodeType j = 0; j < nodeSize; j++) {
      if (i != j && linkMatr[i][j] >= MaxDist) linkMatr[i][j] = 0;
    }
  }
  return 0;
}

int linkMatr_fix_max(VVDistType& linkMatr, const DistType MaxDist) {
  const NodeType nodeSize = linkMatr.size();
  for (NodeType i = 0; i < nodeSize; i++) {
    for (NodeType j = 0; j < nodeSize; j++) {
      if (i != j && linkMatr[i][j] == 0) linkMatr[i][j] = MaxDist;
    }
  }
  return 0;
}

int linkMatr_2_p2p(VVNodeType& p2p, const VVDistType& linkMatr) {
  const NodeType nodeSize = linkMatr.size();
  p2p.clear();
  p2p.resize(nodeSize);
  for (NodeType i = 0; i < nodeSize; i++) {
    for (NodeType j = 0; j < nodeSize; j++) {
      if (j != i && linkMatr[i][j] != 0) {
        p2p[i].push_back(j);
      }
    }
  }
  return 0;
}

int linkMatrC_2_p2p(VVNodeType& p2p, const VVChar& linkMatrC) {
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

int p2p_2_linkMatr(VVDistType& linkMatr, const VVNodeType& p2p) {
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

int p2p_2_p2pIn(VVNodeType& p2pIn, const VVNodeType& p2p) {
  p2pIn.clear();
  for (NodeType i = 0; i < p2p.size(); i++) {
    for (VNodeTypeCItr j = p2p[i].begin(); j != p2p[i].end(); j++) {
      const NodeType t = *j;
      if (p2pIn.size() <= t) p2pIn.resize(t + 1);
      p2pIn[t].push_back(i);
    }
  }
  return 0;
}

int p2p_2_vvweight_sort(VVWeightType& vvweight, const VVNodeType& p2p) {
  const NodeType nodeSize = p2p.size();
  vvweight.clear();
  vvweight.resize(nodeSize);
  VVWeightTypeItr wi = vvweight.begin();
  for (NodeType i = 0; i < nodeSize; wi++, i++) {
    for (VNodeTypeCItr jt = p2p[i].begin(), je = p2p[i].end(); jt != je; jt++) {
      wi->push_back(1);
      while (jt + 1 != je && *jt == *(jt + 1)) {
        wi->back()++;
        jt++;
      }
    }
  }
  return 0;
}

int vvweight_2_vvweightIn(VVWeightType& vvweightIn,
                          const VVWeightType& vvweight, const VVNodeType& p2p) {
  if (!vvweightIn.empty()) {
    ERROR();
    return -1;
  }
  for (NodeType i = 0; i < vvweight.size(); i++) {
    for (VNodeTypeCItr j = p2p[i].begin(); j != p2p[i].end(); j++) {
      const NodeType t = *j;
      if (vvweightIn.size() <= t) vvweightIn.resize(t + 1);
      vvweightIn[t].push_back(vvweight[i][t]);
    }
  }
  return 0;
}

int p2p_2_nodeSize(NodeType& nodeSize, const VVNodeType& p2p) {
  nodeSize = p2p.size();
  for (VVNodeTypeCItr i = p2p.begin(); i != p2p.end(); i++)
    for (VNodeTypeCItr j = i->begin(); j != i->end(); j++)
      if (nodeSize <= *j) nodeSize = *j + 1;
  return 0;
}

int p2p_2_nodeDeg(VNodeType& nodeDeg, const VVNodeType& p2p) {
  const NodeType nodeSize = p2p.size();
  nodeDeg.resize(nodeSize);
  for (NodeType i = 0; i < nodeSize; i++) nodeDeg[i] = p2p[i].size();
  return 0;
}

int nodeDeg_2_degArr(const VNodeType& nodeDeg, VNodeType& degArrVal,
                     VNodeType& degArrSize, VNodeType& degArrSum) {
  const NodeType nodeSize = nodeDeg.size();
  degArrVal.clear();
  degArrSize.clear();
  degArrSum.clear();
  MNodeType degArr;
  if (nodeSize <= 0) return 0;
  for (VNodeTypeCItr i = nodeDeg.begin(); i != nodeDeg.end(); i++) degArr[*i]++;
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

int nodeDeg_2_degArr_Sort(const VNodeType& nodeDeg, VNodeType& degArrVal,
                          VNodeType& degArrSize, VNodeType& degArrSum) {
  const NodeType nodeSize = nodeDeg.size();
  degArrVal.clear();
  degArrSize.clear();
  degArrSum.clear();
  if (nodeSize <= 0) return 0;
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

int degArr_2_nodeSize(NodeType& nodeSize, const VNodeType& degArrSize) {
  if (nodeSize != 0 || degArrSize.empty()) {
    ERROR();
    return -1;
  }
  for (VNodeTypeCItr i = degArrSize.begin(); i != degArrSize.end(); i++)
    nodeSize += *i;
  return 0;
}

int degArr_2_nodeDeg(VNodeType& nodeDeg, const VNodeType& degArrVal,
                     const VNodeType& degArrSize) {
  if (!nodeDeg.empty() || degArrVal.empty() ||
      degArrVal.size() != degArrSize.size()) {
    ERROR();
    return -1;
  }
  for (NodeType i = 0; i < degArrVal.size(); i++) {
    for (NodeType s = 0, t = degArrVal[i]; s < degArrSize[i]; s++)
      nodeDeg.push_back(t);
  }
  return 0;
}

int degArrVal_2_degArrNo(MNodeType& degArrNo, const VNodeType& degArrVal) {
  if (!degArrNo.empty()) return -1;
  for (NodeType i = 0; i < degArrVal.size(); i++) degArrNo[degArrVal[i]] = i;
  return 0;
}

int degArrSize_2_degArrSum(VNodeType& degArrSum, const VNodeType& degArrSize) {
  const NodeType degSize = degArrSize.size();
  degArrSum.resize(degSize);
  for (NodeType i = 0, sum = 0; i < degSize; i++)
    degArrSum[i] = sum += degArrSize[i];
  return 0;
}

int degArr_2_linkSize(LinkType& linkSize, const VNodeType& degArrVal,
                      const VNodeType& degArrSize, const int dirFlag) {
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

int degArr_2_linkSum(VLinkType& linkSum, const VNodeType& degArrVal,
                     const VNodeType& degArrSize) {
  const NodeType degSize = degArrVal.size();
  linkSum.resize(degSize);
  LinkType sum = 0;
  for (NodeType i = 0; i < degSize; i++)
    linkSum[i] = sum += (LinkType)degArrVal[i] * degArrSize[i];
  return 0;
}

int nodeDeg_2_linkSize(LinkType& linkSize, const VNodeType& nodeDeg,
                       const int dirFlag) {
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

int check_nodeDeg0(const VNodeType& nodeDeg) {
  if (nodeDeg.empty()) return -1;
  for (VNodeTypeCItr i = nodeDeg.begin(); i != nodeDeg.end(); i++)
    if (*i <= 0) return 1;
  return 0;
}

int fix_nodeDeg(VNodeType& nodeDeg, const VDouble& degArrProb,
                const VNodeType& degArrVal, LinkType& linkSize) {
  const NodeType nodeSize = nodeDeg.size(), degSize = degArrVal.size();
  for (NodeType num, k; 1;) {
    num = RAND2() % nodeSize;
    k = RAND2() % degSize;
    if (nodeDeg[num] % 2 != degArrVal[k] % 2)
      if (RAND2() < degArrProb[k] * RAND2_MAX) {
        linkSize = linkSize - nodeDeg[num] + degArrVal[k];
        nodeDeg[num] = degArrVal[k];
        break;
      }
  }
  return 0;
}

int p2p_2_lkk(VVLinkType& lkk, const VVNodeType& p2p, const VNodeType& degNum,
              const NodeType degSize) {
  lkk.clear();
  if (degSize <= 0) return 0;
  lkk.assign(degSize, VLinkType(degSize, 0));
  NodeType ti = 0;
  for (VVNodeTypeCItr i = p2p.begin(); i != p2p.end(); ti++, i++) {
    const NodeType ni = degNum[i->size()];
    LinkType* li = &lkk[ni][0];
    for (VNodeTypeCItr j = i->begin(); j != i->end(); j++) {
      if (ti <= *j) {
        const NodeType nj = degNum[p2p[*j].size()];
        if (ni >= nj)
          li[nj]++;
        else
          lkk[nj][ni]++;
      }
    }
  }
  return 0;
}

int p2p_2_lkk_dir(VVLinkType& lkkOutIn, const VVNodeType& p2p,
                  const VNodeType& nodeDegOut, const VNodeType& nodeDegIn,
                  MNodeType& degArrNoOut, MNodeType& degArrNoIn,
                  const NodeType degOutSize, const NodeType degInSize) {
  lkkOutIn.assign(degOutSize, VLinkType(degInSize, 0));
  if (degOutSize <= 0 || degInSize <= 0) return 0;
  VNodeTypeCItr nodeDegOutI = nodeDegOut.begin();
  for (VVNodeTypeCItr i = p2p.begin(); i != p2p.end(); i++) {
    LinkType* li = &lkkOutIn[degArrNoOut[*nodeDegOutI++]][0];
    for (VNodeTypeCItr j = i->begin(); j != i->end(); j++) {
      li[degArrNoIn[nodeDegIn[*j]]]++;
    }
  }
  return 0;
}

int p2p_2_lkk(VVLinkType& lkk, const VVNodeType& p2p, MNodeType& degArrNo,
              const NodeType degSize) {
  lkk.clear();
  if (degSize <= 0) return 0;
  lkk.resize(degSize);
  for (NodeType i = 0; i < degSize; i++) lkk[i].assign(i + 1, 0);
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

int p2p_2_lkk_noDir(VVLinkType& lkk, const VVNodeType& p2p, MNodeType& degArrNo,
                    const VNodeType& nodeDeg, const NodeType degSize) {
  lkk.clear();
  if (degSize <= 0) return 0;
  lkk.resize(degSize);
  for (NodeType i = 0; i < degSize; i++) lkk[i].assign(i + 1, 0);
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

int lkk_dir_2_nDir(VVLinkType& lkk) {
  if (lkk.empty()) return 0;
  const NodeType degSize = lkk.size();
  for (NodeType i = 0; i < degSize; i++) {
    if (lkk[i].size() != degSize) {
      ERROR();
      return -1;
    }
    for (NodeType j = i + 1; j < degSize; j++) lkk[j][i] += lkk[i][j];
    lkk[i].resize(i);
  }
  return 0;
}

int lkk_nDir_2_dir(VVLinkType& lkk) {
  if (lkk.empty()) return 0;
  const NodeType degSize = lkk.size();
  for (NodeType i = 0; i < degSize; i++) {
    if (lkk[i].size() > degSize || lkk[i].size() < i) {
      ERROR();
      return -1;
    }
    if (lkk[i].size() < degSize) lkk[i].resize(degSize, 0);
    for (NodeType j = i + 1; j < degSize; j++) {
      if (lkk[i][j] != 0 || lkk[j][i] % 2 != 0) {
        ERROR();
        return -1;
      }
      lkk[i][j] = lkk[j][i] /= 2;
    }
  }
  return 0;
}

int lkk_2_lkkSum(VVLinkType& lkkSum, const VVLinkType& lkk, const int dir) {
  lkkSum = lkk;
  if (lkk.empty() || lkk[0].empty()) return 0;
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
  } else {  // dir
    const NodeType degSize2 = lkkSum[0].size();
    for (NodeType i = 1; i < degSize; i++) {
      for (NodeType j = 0; j < degSize2; j++) {
        lkkSum[i][j] += lkkSum[i - 1][j];
      }
    }
  }
  return 0;
}

int link_2_nodeSize(NodeType& nodeSize, const VNodeType& link) {
  nodeSize = 0;
  for (LinkType i = 0; i < link.size(); i++)
    if (link[i] >= nodeSize) nodeSize = link[i] + 1;
  return 0;
}

int link_2_p2p(VVNodeType& p2p, const VNodeType& link, VVNodeType& p2pIn,
               NodeType& nodeSize, const int dirFlag) {
  link_2_nodeSize(nodeSize, link);
  p2p.clear();
  p2p.resize(nodeSize);
  if (dirFlag) {
    p2pIn.clear();
    p2pIn.resize(nodeSize);
  }
  for (LinkType n = 0; n < link.size(); n += 2) {
    NodeType i = link[n], j = link[n + 1];
    p2p[i].push_back(j);
    if (dirFlag)
      p2pIn[j].push_back(i);
    else
      p2p[j].push_back(i);
  }
  return 0;
}

int link_2_p2p_out(VVNodeType& p2p, const VNodeType& link, NodeType& nodeSize,
                   const int dirFlag) {
  return link_2_p2p_out_linkSize(p2p, link, nodeSize, link.size() / 2, dirFlag);
}

int link_2_p2p_out_linkSize(VVNodeType& p2p, const VNodeType& link,
                            NodeType& nodeSize, LinkType linkSize,
                            const int dirFlag) {
  p2p.clear();
  link_2_nodeSize(nodeSize, link);
  p2p.resize(nodeSize);
  if (linkSize > link.size()) linkSize = link.size();
  for (LinkType n = 0; n < linkSize; ++n) {
    NodeType i = link[n * 2], j = link[n * 2 + 1];
    p2p[i].push_back(j);
    if (!dirFlag) p2p[j].push_back(i);
  }
  return 0;
}

int link_2_p2p_in(VVNodeType& p2pIn, const VNodeType& link, NodeType& nodeSize,
                  const int dirFlag) {
  if (!dirFlag) return -1;
  link_2_nodeSize(nodeSize, link);
  p2pIn.clear();
  p2pIn.resize(nodeSize);
  for (LinkType n = 0; n < link.size(); n += 2) {
    NodeType i = link[n], j = link[n + 1];
    p2pIn[j].push_back(i);
  }
  return 0;
}

int p2p_2_link(VNodeType& link, const VVNodeType& p2p, const int dirFlag) {
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

int link_2_lkk(VVLinkType& lkk, const VNodeType& link, const VNodeType& nodeDeg,
               MNodeType& degArrNo, const LinkType linkSize,
               const NodeType degSize) {
  lkk.resize(degSize);
  lkk[0].assign(degSize, 0);
  for (NodeType i = 1; i < degSize; i++) lkk[i] = lkk[0];
  for (LinkType i = 0; i < linkSize; i++) {
    const NodeType x = degArrNo[nodeDeg[link[i * 2]]],
                   y = degArrNo[nodeDeg[link[i * 2 + 1]]];
    lkk[x][y]++;
    lkk[y][x]++;
  }
  return 0;
}

int vvweight_2_nodeWeight(VWeightType& nodeWeight, const VVNodeType& p2p,
                          const VVWeightType& vvweight,
                          WeightSumType& netWeight) {
  nodeWeight.assign(p2p.size(), 0);
  netWeight = 0;
  for (NodeType i = 0; i < p2p.size(); i++) {
    if (p2p[i].size() <= 0) continue;
    WeightType t = 0;
    for (NodeType j = 0; j < p2p[i].size(); j++) t += vvweight[i][j];
    netWeight += nodeWeight[i] = t;
  }
  return 0;
}

int weightMatr_2_linkMatr(VVDistType& linkMatr,
                          const VVWeightType& weightMatr) {
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

int nodeDegIO_2_nodeDeg(VNodeType& nodeDeg, const VNodeType& nodeDegOut,
                        const VNodeType& nodeDegIn) {
  if (!nodeDeg.empty() || nodeDegOut.empty() || nodeDegIn.empty()) {
    ERROR();
    return -1;
  }
  if (nodeDegOut.size() >= nodeDegIn.size()) {
    nodeDeg = nodeDegOut;
    for (NodeType i = 0; i < nodeDegIn.size(); i++) nodeDeg[i] += nodeDegIn[i];
  } else {
    nodeDeg = nodeDegIn;
    for (NodeType i = 0; i < nodeDegOut.size(); i++)
      nodeDeg[i] += nodeDegOut[i];
  }
  return 0;
}

int nodeWeightIO_2_nodeWeight(VWeightType& nodeWeight,
                              const VWeightType& nodeWeightOut,
                              const VWeightType& nodeWeightIn) {
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

int nodeWeight_2_degArrWeight(VWeightSumType& degArrWeight,
                              const VWeightSumType& nodeWeight,
                              const VNodeType& nodeDeg, MNodeType& degArrNo,
                              const NodeType degSize) {
  degArrWeight.assign(degSize, 0);
  for (NodeType i = 0; i < nodeWeight.size(); i++) {
    degArrWeight[degArrNo[nodeDeg[i]]] += nodeWeight[i];
  }
  return 0;
}

int degArrWeight_2_degArrWeightSum(VWeightSumType& degArrWeightSum,
                                   const VWeightSumType& degArrWeight) {
  const NodeType degSize = degArrWeight.size();
  degArrWeightSum.resize(degSize + 1);
  degArrWeightSum[0] = 0;
  WeightSumType sum = 0;
  for (NodeType i = 0; i < degSize; i++)
    degArrWeightSum[i + 1] = sum += degArrWeight[i];
  return 0;
}

//**//****************************************************//*
int sort_p2p(VVNodeType& p2p) {
  for (VVNodeTypeItr i = p2p.begin(); i != p2p.end(); i++)
    if (!i->empty()) sort(i->begin(), i->end());
  return 0;
}

int fix_p2p(VVNodeType& p2p, const int dirFlag) {
  LinkType self = 0, multi = 0, lack = 0;
  for (NodeType i = 0; i < p2p.size(); i++) {
    // 自环
    if (p2p[i].empty()) continue;
    for (NodeType j = 0; j < p2p[i].size();) {
      if (p2p[i][j] == i) {
        self++;
        p2p[i][j] = p2p[i][p2p[i].size() - 1];
        p2p[i].pop_back();
      } else
        j++;
    }
    if (p2p[i].empty()) continue;
    sort(p2p[i].begin(), p2p[i].end());  // 从小到大排序
    if (p2p.size() <= p2p[i].back() + 1) p2p.resize(p2p[i].back() + 1);
    // 重边
    if (p2p[i].size() <= 1) continue;
    VNodeTypeCItr e = p2p[i].end();
    VNodeTypeItr j = p2p[i].begin();
    while (j + 1 != e && *j != *(j + 1)) j++;
    if (j + 1 != e) {
      for (VNodeTypeCItr k = j + 1; k != e; k++) {
        if (*j != *k) *++j = *k;
      }
    }
    NodeType t = j + 1 - p2p[i].begin();
    if (p2p[i].size() > t) {
      multi += p2p[i].size() - t;
      p2p[i].resize(t);
    }
  }
  if (!dirFlag) {  // 无向网络相互连接
    for (NodeType i = 0; i < p2p.size(); i++) {
      for (VNodeTypeCItr iItr = p2p[i].begin(), jItr; iItr != p2p[i].end();
           iItr++) {
        VVNodeTypeItr j = p2p.begin() + *iItr;
        for (jItr = j->begin(); jItr < j->end(); jItr++)
          if (*jItr == i) break;
        if (jItr >= j->end()) {
          lack++;
          j->push_back(i);
        }
      }
    }
    for (VVNodeTypeItr i = p2p.begin(); i != p2p.end(); i++)
      sort(i->begin(), i->end());  // 从小到大排序
  }
  cout << "fix_p2p\tself\t" << self << "\n\tmulti\t" << multi << "\n\tlack\t"
       << lack << '\n';
  return 0;
}

int qsort_p2p(VVNodeType& p2p, const VVDistType& linkMatr) {
  for (NodeType i = 0; i < p2p.size(); i++) {
    if (p2p[i].size() >= 2)
      common_sort_p_val(p2p[i].begin(), p2p[i].end(), &linkMatr[i].front());
  }
  return 0;
}

int del_pij(const NodeType i, const NodeType j, VVNodeType& p2p,
            VVNodeType& p2pIn, const int dirFlag) {
  for (NodeType n = 0; n < p2p[i].size(); n++)
    if (p2p[i][n] == j) {
      p2p[i][n] = p2p[i].back();
      p2p[i].pop_back();
      break;
    }
  if (!dirFlag) {
    for (NodeType n = 0; n < p2p[j].size(); n++)
      if (p2p[j][n] == i) {
        p2p[j][n] = p2p[j].back();
        p2p[j].pop_back();
        break;
      }
  } else {
    for (NodeType n = 0; n < p2pIn[j].size(); n++)
      if (p2pIn[j][n] == i) {
        p2pIn[j][n] = p2p[j].back();
        p2pIn[j].pop_back();
        break;
      }
  }
  return 0;
}

int add_pij(const NodeType i, const NodeType j, VVNodeType& p2p,
            VVNodeType& p2pIn, const int dirFlag) {
  int flag = 1;
  for (NodeType n = 0; n < p2p[i].size(); n++)
    if (p2p[i][n] == j) {
      flag = 0;
      break;
    }
  if (flag) p2p[i].push_back(j);
  if (!dirFlag) {
    flag = 1;
    for (NodeType n = 0; n < p2p[j].size(); n++)
      if (p2p[i][n] == i) {
        flag = 0;
        break;
      }
    if (flag) {
      p2p[j].push_back(i);
      flag = 0;
    }
  } else {
    flag = 1;
    for (NodeType n = 0; n < p2pIn[j].size(); n++)
      if (p2pIn[j][n] == i) {
        flag = 0;
        break;
      }
    if (flag) p2pIn[j].push_back(i);
  }
  return 0;
}

int sort_link_betwEdge(VNodeType& link, VVDouble& betwEdge, LinkType linkSize) {
  if (linkSize == 1 || link.size() < 4) return 0;
  if (linkSize < 1) linkSize = link.size() / 2;

  stack<Common_RangeP<PNodeType>> st;
  st.push(Common_RangeP<PNodeType>(&link.front(),
                                   &link.front() + (linkSize - 1) * 2));
  while (!st.empty()) {
    Common_RangeP<PNodeType> range = st.top();
    st.pop();
    PNodeType start = range.start, end = range.end;
    if (betwEdge[*start][start[1]] > betwEdge[*end][end[1]]) {
      swap(*start, *end);
      swap(start[1], end[1]);
    }
    if (start + 2 >= end) continue;
    double pivot = betwEdge[*(start + (end - start) / 2)]
                           [*(start + (end - start) / 2 + 1)];
    if (betwEdge[*start][start[1]] > pivot)
      pivot = betwEdge[*start][start[1]];
    else if (betwEdge[*end][end[1]] < pivot)
      pivot = betwEdge[*end][end[1]];
    while (start < end) {
      while (start < end && betwEdge[*start][start[1]] <= pivot) start += 2;
      while (start < end && betwEdge[*end][end[1]] >= pivot) end -= 2;
      if (start < end) {
        swap(*start, *end);
        swap(start[1], end[1]);
        start += 2;
        end -= 2;
      }
    }
    while (start > range.start && betwEdge[*start][start[1]] >= pivot)
      start -= 2;
    while (end < range.end && betwEdge[*end][end[1]] <= pivot) end += 2;
    if (range.start < start)
      st.push(Common_RangeP<PNodeType>(range.start, start));
    if (end < range.end) st.push(Common_RangeP<PNodeType>(end, range.end));
  }

  return 0;
}

//**//****************************************************//*
int addLink_linkMatrC_ranNode(
    VVChar& linkMatrC, LinkType& linkRemain)  // 每次直接随机抽取两个点连边
{
  const NodeType nodeSize = linkMatrC.size();
  while (linkRemain > 0) {
    NodeType i = RAND2() % nodeSize, j = RAND2() % (nodeSize - 1);
    if (j >= i) j++;
    if (linkMatrC[i][j >> 3] & (1 << (j & 7))) continue;  // linkMatrC[i][j]
    linkMatrC[i][j >> 3] |= (1 << (j & 7));  // linkMatrC[i][j] = 1;
    linkMatrC[j][i >> 3] |= (1 << (i & 7));  // linkMatrC[j][i] = 1;
    linkRemain--;
  }
  return 0;
}

int addLink_linkMatrC_proNode(VVChar& linkMatrC, LinkType& linkSize,
                              const double p)  // 所有点按概率p连边
{
  const NodeType nodeSize = linkMatrC.size();
  const NodeType size = nodeSize / 8 + 1;
  linkMatrC.resize(nodeSize);
  linkMatrC[0].assign(size, 0);
  const int x = p * RAND2_MAX;
  for (NodeType i = 1; i < nodeSize; i++)
    for (NodeType j = 0; j < i; j++)
      if (RAND2() < x) {
        linkMatrC[i][j >> 3] |= (1 << (j & 7));  // linkMatrC[i][j] = 1;
        linkMatrC[j][i >> 3] |= (1 << (i & 7));  // linkMatrC[j][i] = 1;
        linkSize++;
      }
  return 0;
}

int addLink_linkMatr_ranNode(
    VVDistType& linkMatr, LinkType& linkRemain)  // 每次直接随机抽取两个点连边
{
  const NodeType nodeSize = linkMatr.size();
  while (linkRemain > 0) {
    NodeType i = RAND2() % nodeSize, j = RAND2() % (nodeSize - 1);
    if (j >= i) j++;
    if (linkMatr[i][j]) continue;  // linkMatr[i][j]
    linkMatr[i][j] = 1;            // linkMatr[i][j] = 1;
    linkMatr[j][i] = 1;            // linkMatr[j][i] = 1;
    linkRemain--;
  }
  return 0;
}

int addLink_linkMatr_proNode(VVDistType& linkMatr, LinkType& linkSize,
                             const double p)  // 所有点按概率p连边
{
  const NodeType nodeSize = linkMatr.size();
  linkMatr.resize(nodeSize);
  linkMatr[0].assign(nodeSize, 0);
  for (NodeType i = 1; i < nodeSize; i++) linkMatr[i] = linkMatr[0];
  const int x = p * RAND2_MAX;
  for (NodeType i = 1; i < nodeSize; i++)
    for (NodeType j = 0; j < i; j++)
      if (RAND2() < x) {
        linkMatr[i][j] = 1;  // linkMatr[i][j] = 1;
        linkMatr[j][i] = 1;  // linkMatr[j][i] = 1;
        linkSize++;
      }
  return 0;
}

int addLink_linkMatrC_ranNode2(
    VVChar& linkMatrC, VNodeType& nodeDeg, VNodeType& p2pSize,
    VNodeType& remPoiNum, LinkType& linkRemain,
    const LinkType tryCount)  // 每次直接随机抽取两个点连边
{
  for (LinkType try0 = 0; linkRemain > 0 && remPoiNum.size() > 1;) {
    NodeType ik = RAND2() % remPoiNum.size();
    NodeType i = remPoiNum[ik];
    if (p2pSize[i] >= nodeDeg[i]) {
      remPoiNum[ik] = remPoiNum.back();
      remPoiNum.pop_back();
      continue;
    }
    NodeType jk = RAND2() % (remPoiNum.size() - 1);
    if (jk >= ik) jk++;
    NodeType j = remPoiNum[jk];
    if (p2pSize[j] >= nodeDeg[j]) {
      remPoiNum[jk] = remPoiNum.back();
      remPoiNum.pop_back();
      continue;
    }
    if (linkMatrC[i][j >> 3] & (1 << (j & 7))) {  // linkMatrC[i][j] == 1
      if (++try0 >= tryCount)
        break;
      else
        continue;
    }
    linkMatrC[i][j >> 3] ^= (1 << (j & 7));  // linkMatrC[i][j] = 1;
    linkMatrC[j][i >> 3] ^= (1 << (i & 7));  // linkMatrC[j][i] = 1;
    p2pSize[i]++;
    p2pSize[j]++;
    linkRemain--;
    try0 = 0;
    if (ik < jk) {
      if (p2pSize[j] == nodeDeg[j]) {
        remPoiNum[jk] = remPoiNum.back();
        remPoiNum.pop_back();
      }
      if (p2pSize[i] == nodeDeg[i]) {
        remPoiNum[ik] = remPoiNum.back();
        remPoiNum.pop_back();
      }
    } else {
      if (p2pSize[i] == nodeDeg[i]) {
        remPoiNum[ik] = remPoiNum.back();
        remPoiNum.pop_back();
      }
      if (p2pSize[j] == nodeDeg[j]) {
        remPoiNum[jk] = remPoiNum.back();
        remPoiNum.pop_back();
      }
    }
  }
  return (linkRemain <= 0 ? 0 : -1);
}

int addLink_linkMatr_ranNode2(
    VVDistType& linkMatr, VNodeType& nodeDeg, VNodeType& p2pSize,
    VNodeType& remPoiNum, LinkType& linkRemain,
    const LinkType tryCount)  // 每次直接随机抽取两个点连边
{
  for (LinkType try0 = 0; linkRemain > 0 && remPoiNum.size() > 1;) {
    NodeType ik = RAND2() % remPoiNum.size();
    NodeType i = remPoiNum[ik];
    if (p2pSize[i] >= nodeDeg[i]) {
      remPoiNum[ik] = remPoiNum.back();
      remPoiNum.pop_back();
      continue;
    }
    NodeType jk = RAND2() % (remPoiNum.size() - 1);
    if (jk >= ik) jk++;
    NodeType j = remPoiNum[jk];
    if (p2pSize[j] >= nodeDeg[j]) {
      remPoiNum[jk] = remPoiNum.back();
      remPoiNum.pop_back();
      continue;
    }
    if (linkMatr[i][j] != 0) {  // linkMatr[i][j] == 1
      if (++try0 >= tryCount)
        break;
      else
        continue;
    }
    linkMatr[i][j] = 1;  // linkMatr[i][j] = 1;
    linkMatr[j][i] = 1;  // linkMatr[j][i] = 1;
    p2pSize[i]++;
    p2pSize[j]++;
    linkRemain--;
    try0 = 0;
    if (ik < jk) {
      if (p2pSize[j] == nodeDeg[j]) {
        remPoiNum[jk] = remPoiNum.back();
        remPoiNum.pop_back();
      }
      if (p2pSize[i] == nodeDeg[i]) {
        remPoiNum[ik] = remPoiNum.back();
        remPoiNum.pop_back();
      }
    } else {
      if (p2pSize[i] == nodeDeg[i]) {
        remPoiNum[ik] = remPoiNum.back();
        remPoiNum.pop_back();
      }
      if (p2pSize[j] == nodeDeg[j]) {
        remPoiNum[jk] = remPoiNum.back();
        remPoiNum.pop_back();
      }
    }
  }
  return (linkRemain <= 0 ? 0 : -1);
}

int addLink_p2p_ranNode0(VVNodeType& p2p, VNodeType& link, VNodeType& nodeDeg,
                         VNodeType& remPoiNum, LinkType& linkRemain,
                         const LinkType tryCount) {
  for (LinkType try0 = 0; linkRemain > 0 && remPoiNum.size() > 1;) {
    NodeType ik = RAND2() % remPoiNum.size(), i;
    i = remPoiNum[ik];
    if (p2p[i].size() >= nodeDeg[i]) {
      remPoiNum[ik] = remPoiNum.back();
      remPoiNum.pop_back();
      continue;
    }
    NodeType jk = RAND2() % (remPoiNum.size() - 1), j;
    if (jk >= ik) jk++;
    j = remPoiNum[jk];
    if (p2p[j].size() >= nodeDeg[j]) {
      remPoiNum[jk] = remPoiNum.back();
      remPoiNum.pop_back();
      continue;
    }
    NodeType t;
    if (p2p[i].size() > p2p[j].size()) {
      t = ik;
      ik = jk;
      jk = t;
      i = remPoiNum[ik];
      j = remPoiNum[jk];
    }
    for (t = 0; t < p2p[i].size(); t++)
      if (p2p[i][t] == j) break;
    if (t < p2p[i].size()) {
      if (++try0 >= tryCount)
        break;
      else
        continue;
    }
    p2p[i].push_back(j);
    p2p[j].push_back(i);
    --linkRemain;
    link[linkRemain * 2] = i;
    link[linkRemain * 2 + 1] = j;
    try0 = 0;
    if (ik < jk) {
      if (p2p[j].size() == nodeDeg[j]) {
        remPoiNum[jk] = remPoiNum.back();
        remPoiNum.pop_back();
      }
      if (p2p[i].size() == nodeDeg[i]) {
        remPoiNum[ik] = remPoiNum.back();
        remPoiNum.pop_back();
      }
    } else {
      if (p2p[i].size() == nodeDeg[i]) {
        remPoiNum[ik] = remPoiNum.back();
        remPoiNum.pop_back();
      }
      if (p2p[j].size() == nodeDeg[j]) {
        remPoiNum[jk] = remPoiNum.back();
        remPoiNum.pop_back();
      }
    }
  }
  return (linkRemain <= 0 ? 0 : -1);
}

int addLink_p2p_proDeg(VVNodeType& p2p, VNodeType& link,
                       const VNodeType& nodeDeg, const NodeType kMax,
                       VNodeType& remPoiNum, LinkType& linkRemain,
                       const LinkType tryCount) {
  const double r_degMax = (double)RAND2_MAX / kMax;
  for (LinkType try0 = 0; linkRemain > 0 && remPoiNum.size() > 1;) {
    NodeType ik = RAND2() % remPoiNum.size(), i;
    i = remPoiNum[ik];
    if (p2p[i].size() >= nodeDeg[i]) {
      remPoiNum[ik] = remPoiNum.back();
      remPoiNum.pop_back();
      continue;
    }
    if (RAND2() > r_degMax * nodeDeg[i]) continue;
    NodeType jk = RAND2() % (remPoiNum.size() - 1), j;
    if (jk >= ik) jk++;
    j = remPoiNum[jk];
    if (p2p[j].size() >= nodeDeg[j]) {
      remPoiNum[jk] = remPoiNum.back();
      remPoiNum.pop_back();
      continue;
    }
    if (RAND2() > r_degMax * nodeDeg[j]) continue;
    NodeType t;
    if (p2p[i].size() > p2p[j].size()) {
      t = ik;
      ik = jk;
      jk = t;
      i = remPoiNum[ik];
      j = remPoiNum[jk];
    }
    for (t = 0; t < p2p[i].size(); t++)
      if (p2p[i][t] == j) break;
    if (t < p2p[i].size()) {
      if (++try0 >= tryCount)
        break;
      else
        continue;
    }
    p2p[i].push_back(j);
    p2p[j].push_back(i);
    --linkRemain;
    link[linkRemain * 2] = i;
    link[linkRemain * 2 + 1] = j;
    try0 = 0;
    if (ik < jk) {
      if (p2p[j].size() == nodeDeg[j]) {
        remPoiNum[jk] = remPoiNum.back();
        remPoiNum.pop_back();
      }
      if (p2p[i].size() == nodeDeg[i]) {
        remPoiNum[ik] = remPoiNum.back();
        remPoiNum.pop_back();
      }
    } else {
      if (p2p[i].size() == nodeDeg[i]) {
        remPoiNum[ik] = remPoiNum.back();
        remPoiNum.pop_back();
      }
      if (p2p[j].size() == nodeDeg[j]) {
        remPoiNum[jk] = remPoiNum.back();
        remPoiNum.pop_back();
      }
    }
  }
  return (linkRemain <= 0 ? 0 : -1);
}

int addLink_p2p_ranNode(VVNodeType& p2p, VNodeType& nodeDeg,
                        VNodeType& remPoiNum, LinkType& linkRemain,
                        const LinkType tryCount) {
  for (LinkType try0 = 0; linkRemain > 0 && remPoiNum.size() > 1;) {
    NodeType ik = RAND2() % remPoiNum.size(), i;
    i = remPoiNum[ik];
    if (p2p[i].size() >= nodeDeg[i]) {
      remPoiNum[ik] = remPoiNum.back();
      remPoiNum.pop_back();
      continue;
    }
    NodeType jk = RAND2() % (remPoiNum.size() - 1), j;
    if (jk >= ik) jk++;
    j = remPoiNum[jk];
    if (p2p[j].size() >= nodeDeg[j]) {
      remPoiNum[jk] = remPoiNum.back();
      remPoiNum.pop_back();
      continue;
    }
    NodeType t;
    if (p2p[i].size() > p2p[j].size()) {
      t = ik;
      ik = jk;
      jk = t;
      i = remPoiNum[ik];
      j = remPoiNum[jk];
    }
    for (t = 0; t < p2p[i].size(); t++)
      if (p2p[i][t] == j) break;
    if (t < p2p[i].size()) {
      if (++try0 >= tryCount)
        break;
      else
        continue;
    }
    p2p[i].push_back(j);
    p2p[j].push_back(i);
    --linkRemain;
    try0 = 0;
    if (ik < jk) {
      if (p2p[j].size() == nodeDeg[j]) {
        remPoiNum[jk] = remPoiNum.back();
        remPoiNum.pop_back();
      }
      if (p2p[i].size() == nodeDeg[i]) {
        remPoiNum[ik] = remPoiNum.back();
        remPoiNum.pop_back();
      }
    } else {
      if (p2p[i].size() == nodeDeg[i]) {
        remPoiNum[ik] = remPoiNum.back();
        remPoiNum.pop_back();
      }
      if (p2p[j].size() == nodeDeg[j]) {
        remPoiNum[jk] = remPoiNum.back();
        remPoiNum.pop_back();
      }
    }
  }
  return (linkRemain <= 0 ? 0 : -1);
}

int addLink_p2p_ranLink(VVNodeType& p2p, VNodeType& nodeDeg,
                        NodeType& remPoiSize, LinkType& linkRemain,
                        VNodeType& link, const LinkType tryCount) {
  for (LinkType try0 = 0; linkRemain > 0 && remPoiSize > 1;) {
    LinkType ik = RAND2L() % (linkRemain * 2), jk;
    NodeType i = link[ik], j;
    do {
      jk = RAND2L() % (linkRemain * 2 - 1);
      if (jk >= ik) jk++;
      j = link[jk];
    } while (i == j);
    if (p2p[i].size() > p2p[j].size()) {
      NodeType k = ik;
      ik = jk;
      jk = k;
      i = link[ik];
      j = link[jk];
    }
    NodeType k = 0;
    for (; k < p2p[i].size(); k++)
      if (p2p[i][k] == j) break;
    if (k < p2p[i].size()) {
      if (++try0 >= tryCount)
        break;
      else
        continue;
    }
    p2p[i].push_back(j);
    p2p[j].push_back(i);
    if (p2p[i].size() == nodeDeg[i]) remPoiSize--;
    if (p2p[j].size() == nodeDeg[j]) remPoiSize--;
    --linkRemain;
    try0 = 0;
    if (ik > jk) {
      NodeType k = ik;
      ik = jk;
      jk = k;
      i = link[ik];
      j = link[jk];
    }
    if (jk < linkRemain * 2) {
      link[ik] = link[linkRemain * 2];
      link[jk] = link[linkRemain * 2 + 1];
      link[linkRemain * 2] = i;
      link[linkRemain * 2 + 1] = j;
    } else if (jk == linkRemain * 2) {
      link[ik] = link[linkRemain * 2 + 1];
      link[linkRemain * 2 + 1] = i;
    } else if (ik < linkRemain * 2) {
      link[ik] = link[linkRemain * 2];
      link[linkRemain * 2] = i;
    }
  }
  return (linkRemain <= 0 ? 0 : -1);
}

int addLink_p2p_ranLink_lkkProb(VVNodeType& p2p, const VNodeType& nodeDeg,
                                VVDouble& lkkProb, MNodeType& degArrNo,
                                NodeType& remPoiSize, LinkType& linkRemain,
                                VNodeType& link, const LinkType tryCount) {
  for (LinkType try0 = 0; linkRemain > 0 && remPoiSize > 1;) {
    LinkType ik, jk;
    NodeType i, j;
    while (1) {
      ik = RAND2() % (linkRemain * 2);
      i = link[ik];
      jk = RAND2() % (linkRemain * 2 - 1);
      if (jk >= ik) jk++;
      j = link[jk];
      if (i != j &&
          RAND2() <=
              lkkProb[degArrNo[nodeDeg[i]]][degArrNo[nodeDeg[j]]] * RAND2_MAX)
        break;
    }
    if (p2p[i].size() > p2p[j].size()) {
      NodeType k = ik;
      ik = jk;
      jk = k;
      i = link[ik];
      j = link[jk];
    }
    NodeType k = 0;
    for (; k < p2p[i].size(); k++)
      if (p2p[i][k] == j) break;
    if (k < p2p[i].size()) {
      if (++try0 >= tryCount)
        break;
      else
        continue;
    }
    p2p[i].push_back(j);
    p2p[j].push_back(i);
    if (p2p[i].size() == nodeDeg[i]) remPoiSize--;
    if (p2p[j].size() == nodeDeg[j]) remPoiSize--;
    --linkRemain;
    try0 = 0;
    if (ik > jk) {
      NodeType k = ik;
      ik = jk;
      jk = k;
      i = link[ik];
      j = link[jk];
    }
    if (jk < linkRemain * 2) {
      link[ik] = link[linkRemain * 2];
      link[jk] = link[linkRemain * 2 + 1];
      link[linkRemain * 2] = i;
      link[linkRemain * 2 + 1] = j;
    } else if (jk == linkRemain * 2) {
      link[ik] = link[linkRemain * 2 + 1];
      link[linkRemain * 2 + 1] = i;
    } else if (ik < linkRemain * 2) {
      link[ik] = link[linkRemain * 2];
      link[linkRemain * 2] = i;
    }
  }
  return (linkRemain <= 0 ? 0 : -1);
}

int delLink_p2p_ranLink(VVNodeType& p2p, VNodeType& nodeDeg,
                        VNodeType& remPoiNum, LinkType& linkRemain,
                        const LinkType linkSize, VNodeType& link,
                        LinkType delCount) {
  while (delCount > 0 && linkRemain < linkSize) {
    NodeType i, j;
    LinkType l = RAND2L() % (linkSize - linkRemain) + linkRemain;
    i = link[l * 2];
    j = link[l * 2 + 1];
    if (p2p[i].size() == nodeDeg[i]) remPoiNum.push_back(i);
    for (NodeType k = p2p[i].size(), *p = &p2p[i][0]; k > 0; p++, k--) {
      if (*p == j) {
        *p = p2p[i].back();
        p2p[i].pop_back();
        break;
      }
    }
    if (p2p[j].size() == nodeDeg[j]) remPoiNum.push_back(j);
    for (NodeType k = p2p[j].size(), *p = &p2p[j][0]; k > 0; p++, k--) {
      if (*p == i) {
        *p = p2p[j].back();
        p2p[j].pop_back();
        break;
      }
    }
    link[l * 2] = link[linkRemain * 2];
    link[l * 2 + 1] = link[linkRemain * 2 + 1];
    link[linkRemain * 2] = i;
    link[linkRemain * 2 + 1] = j;
    linkRemain++;
    delCount--;
  }
  return (delCount > 0 ? -1 : 0);
}

int delLink_linkMatrC_ranNode(VVChar& linkMatrC, const NodeType nodeSize,
                              VNodeType& nodeDeg, VNodeType& p2pSize,
                              VNodeType& remPoiNum, LinkType& linkRemain,
                              const LinkType linkSize,
                              LinkType delCount)  // 随机选点删边
{
  while (delCount > 0 && linkRemain < linkSize) {
    NodeType i;
    do {
      i = RAND2() % nodeSize;
    } while (p2pSize[i] <= 0);
    NodeType j;
    do {
      j = RAND2() % (nodeSize - 1);
      if (j >= i) j++;
    } while (p2pSize[j] <= 0);
    if (linkMatrC[i][j >> 3] & (1 << (j & 7))) {  // linkMatr[i][j] == 1
      linkMatrC[i][j >> 3] ^= (1 << (j & 7));     // linkMatr[i][j] = 0
      linkMatrC[j][i >> 3] ^= (1 << (i & 7));     // linkMatr[j][i] = 0
      if (p2pSize[i]-- == nodeDeg[i]) remPoiNum.push_back(i);
      if (p2pSize[j]-- == nodeDeg[j]) remPoiNum.push_back(j);
      linkRemain++;
      delCount--;
    }
  }
  return (delCount > 0 ? -1 : 0);
}

int delLink_p2p_ranNode(VVNodeType& p2p, const NodeType nodeSize,
                        const VNodeType& nodeDeg, VNodeType& remPoiNum,
                        NodeType& remPoiSize, LinkType& linkRemain,
                        const LinkType linkSize,
                        LinkType delCount)  // 随机选点删边
{
  while (delCount > 0 && linkRemain < linkSize) {
    NodeType i;
    do {
      i = RAND2() % nodeSize;
    } while (p2p[i].size() <= 0);
    NodeType j;
    do {
      j = RAND2() % (nodeSize - 1);
      if (j >= i) j++;
    } while (p2p[j].size() <= 0);
    NodeType k;
    if (p2p[i].size() > p2p[j].size()) {
      k = i;
      i = j;
      j = k;
    }
    for (k = 0; k < p2p[i].size(); k++)
      if (p2p[i][k] == j) break;
    if (k >= p2p[i].size()) continue;
    if (p2p[i].size() == nodeDeg[i]) remPoiNum.push_back(i);
    if (p2p[j].size() == nodeDeg[j]) remPoiNum.push_back(j);
    p2p[i][k] = p2p[i].back();
    p2p[i].pop_back();
    for (NodeType k = 0; k < p2p[j].size(); k++)
      if (p2p[j][k] == i) {
        p2p[j][k] = p2p[j].back();
        p2p[j].pop_back();
        break;
      }
    linkRemain++;
    delCount--;
  }
  return (delCount > 0 ? -1 : 0);
}

int delLink_p2p_ranNode1(VVNodeType& p2p, const NodeType nodeSize,
                         VNodeType& nodeDeg, VNodeType& remPoiNum,
                         NodeType& remPoiSize, LinkType& linkRemain,
                         const LinkType linkSize,
                         LinkType delCount)  // 随机选点再选边删除
{
  while (delCount > 0 && linkRemain < linkSize) {
    NodeType i;
    do {
      i = RAND2() % nodeSize;
    } while (p2p[i].size() <= 0);
    NodeType k = RAND2() % p2p[i].size(), j;
    j = p2p[i][k];
    if (p2p[i].size() == nodeDeg[i]) remPoiNum.push_back(i);
    if (p2p[j].size() == nodeDeg[j]) remPoiNum.push_back(j);
    p2p[i][k] = p2p[i].back();
    p2p[i].pop_back();
    for (NodeType k = 0; k < p2p[j].size(); k++)
      if (p2p[j][k] == i) {
        p2p[j][k] = p2p[j].back();
        p2p[j].pop_back();
        break;
      }
    linkRemain++;
    delCount--;
  }
  return (delCount > 0 ? -1 : 0);
}

//**//*******************************************************************//*
int check_p2pSize_linkSize(const VVNodeType& p2p, const LinkType linkSize) {
  LinkType t = 0;
  for (NodeType i = 0; i < p2p.size(); i++) t += p2p[i].size();
  if (t != linkSize * 2) return -1;
  return 0;
}

int check_p2p(const VVNodeType& p2p) {
  for (NodeType i = 0, nodeSize = p2p.size(); i < nodeSize; i++) {
    if (p2p[i].size() >= nodeSize) return -1;
    for (NodeType j = 0; j < p2p[i].size(); j++) {
      NodeType k = p2p[i][j], t;
      if (k == i || k >= nodeSize || p2p[k].size() >= nodeSize) return -1;
      for (t = 0; t < p2p[k].size(); t++)
        if (p2p[k][t] == i) break;
      if (t >= p2p[k].size()) return -1;
    }
  }
  return 0;
}

int check_p2p_nodeDeg(const VVNodeType& p2p, const VNodeType& nodeDeg) {
  if (p2p.size() != nodeDeg.size()) {
    ERROR();
    return -1;
  }
  for (NodeType i = 0; i < p2p.size(); i++) {
    if (p2p[i].size() != nodeDeg[i]) {
      ERROR(i);
      return -1;
    }
  }
  return 0;
}

int check_link(VNodeType& link) {
  if (link.size() % 2 != 0) return -1;
  const LinkType linkSize = link.size() / 2;
  sort_link_num_greater_1(link);
  sort_link_num_greater_all(link);
  NodeType* p = &link[0];
  for (LinkType i = 0; i < linkSize; i++, p += 2) {
    if (*p >= linkSize || p[1] >= linkSize || *p == p[1]) {
      ERROR("\tlink[", i, "]:\t", p[0], "\t", p[1]);
      return -1;
    };
  }
  p = &link[0];
  for (LinkType i = 1; i < linkSize; i++)
    if (*p == p[2] && p[1] == p[3]) {
      ERROR("\n\tlink[", i - 1, "]:\t", p[0], "\t", p[1], "\n\tlink[", i,
            "]:\t", p[2], "\t", p[3]);
      return -1;
    } else
      p += 2;
  return 0;
}

int sort_link_greater_1(VNodeType& link, const VNodeType& nodeDeg) {
  const LinkType linkSize = link.size() / 2;
  NodeType* p = &link[0];
  for (LinkType i = 0; i < linkSize; i++, p += 2) {
    if (nodeDeg[*p] > nodeDeg[p[1]]) {
      NodeType t = *p;
      *p = p[1];
      p[1] = t;
    }
  }
  return 0;
}

int sort_link_smaller_1(VNodeType& link, const VNodeType& nodeDeg) {
  const LinkType linkSize = link.size() / 2;
  NodeType* p = &link[0];
  for (LinkType i = 0; i < linkSize; i++, p += 2) {
    if (nodeDeg[*p] < nodeDeg[p[1]]) {
      NodeType t = *p;
      *p = p[1];
      p[1] = t;
    }
  }
  return 0;
}

int sort_link_num_greater_1(VNodeType& link) {
  const LinkType linkSize = link.size() / 2;
  NodeType* p = &link[0];
  for (LinkType i = 0; i < linkSize; i++, p += 2) {
    if (*p > p[1]) {
      NodeType t = *p;
      *p = p[1];
      p[1] = t;
    }
  }
  return 0;
}

int sort_link_num_smaller_1(VNodeType& link) {
  const LinkType linkSize = link.size() / 2;
  NodeType* p = &link[0];
  for (LinkType i = 0; i < linkSize; i++, p += 2) {
    if (*p < p[1]) {
      NodeType t = *p;
      *p = p[1];
      p[1] = t;
    }
  }
  return 0;
}

int sort_link_greater_all(VNodeType& link, const VNodeType& p2pSize) {
  const LinkType linkSize = link.size() / 2;
  if (linkSize < 2) return 0;
  NodeType* p0 = &link[linkSize * 2 - 2];
  for (char flag = 1; flag; p0 -= 2) {
    flag = 0;
    for (NodeType* p = &link[0]; p < p0; p += 2) {
      if (p2pSize[*p] > p2pSize[p[2]] ||
          (p2pSize[*p] == p2pSize[p[2]] && p2pSize[p[1]] > p2pSize[p[3]])) {
        NodeType t = *p;
        *p = p[1];
        p[1] = t;
        t = p[1];
        p[1] = p[3];
        p[3] = t;
        flag = 1;
      }
    }
  }
  return 0;
}

int sort_link_num_greater_all(VNodeType& link) {
  const LinkType linkSize = link.size() / 2;
  if (linkSize < 2) return 0;
  char flag = 1;
  for (NodeType* p0 = &link[(linkSize - 1) * 2]; flag; p0 -= 2) {
    flag = 0;
    for (NodeType* p = &link[0]; p < p0; p += 2) {
      if (*p > p[2] || (*p == p[2] && p[1] > p[3])) {
        NodeType t = *p;
        *p = p[2];
        p[2] = t;
        t = p[1];
        p[1] = p[3];
        p[3] = t;
        flag = 1;
      }
    }
  }
  return 0;
}

int sort_link_smaller_all(VNodeType& link, const VNodeType& p2pSize) {
  const LinkType linkSize = link.size() / 2;
  if (linkSize < 2) return 0;
  NodeType* p0 = &link[linkSize * 2 - 2];
  for (char flag = 1; flag; p0 -= 2) {
    flag = 0;
    for (NodeType* p = &link[0]; p < p0; p += 2) {
      if (p2pSize[*p] < p2pSize[p[2]] ||
          (p2pSize[*p] == p2pSize[p[2]] && p2pSize[p[1]] < p2pSize[p[3]])) {
        NodeType t = *p;
        *p = p[1];
        p[1] = t;
        t = p[1];
        p[1] = p[3];
        p[3] = t;
        flag = 1;
      }
    }
  }
  return 0;
}

int sort_link_num_smaller_all(VNodeType& link) {
  const LinkType linkSize = link.size() / 2;
  if (linkSize < 2) return 0;
  char flag = 1;
  for (NodeType* p0 = &link[(linkSize - 1) * 2]; flag; p0 -= 2) {
    flag = 0;
    for (NodeType* p = &link[0]; p < p0; p += 2) {
      if (*p < p[2] || (*p == p[2] && p[1] < p[3])) {
        NodeType t = *p;
        *p = p[2];
        p[2] = t;
        t = p[1];
        p[1] = p[3];
        p[3] = t;
        flag = 1;
      }
    }
  }
  return 0;
}

int exchange_linkC_deg_same(VVChar& linkMatrC, VNodeType& link,
                            const VNodeType& p2pSize, LinkType count) {
  const LinkType linkSize = link.size() / 2;
  if (linkSize < 2) return -1;
  while (count > 0) {
    LinkType ik = RAND2_LONG() % linkSize, jk = RAND2_LONG() % (linkSize - 1);
    if (jk >= ik) jk++;
    ik <<= 1;
    jk <<= 1;
    NodeType i1 = link[ik], i2 = link[ik | 1], j1 = link[jk], j2 = link[jk | 1];
    NodeType pi1 = p2pSize[i1], pi2 = p2pSize[i2], pj1 = p2pSize[j1],
             pj2 = p2pSize[j2];
    if (pi1 >= pj2 || pj1 >= pi2 || i1 == j1 || i2 == j2) continue;
    if (pi1 != pj1 && pi2 != pj2 &&
        ((pj1 < pi1 && pi2 < pj2) || (pi1 < pj1 && pj2 < pi2)) &&
        (linkMatrC[i1][j2 >> 3] & (1 << (j2 & 7))) == 0 &&
        (linkMatrC[i2][j1 >> 3] & (1 << (j1 & 7))) == 0) {
      // i1-i2
      linkMatrC[i1][i2 >> 3] ^= 1 << (i2 & 7);
      linkMatrC[i2][i1 >> 3] ^= 1 << (i1 & 7);
      // j1-j2
      linkMatrC[j1][j2 >> 3] ^= 1 << (j2 & 7);
      linkMatrC[j2][j1 >> 3] ^= 1 << (j1 & 7);
      // i1-j2
      linkMatrC[i1][j2 >> 3] ^= 1 << (j2 & 7);
      linkMatrC[j2][i1 >> 3] ^= 1 << (i1 & 7);
      // i2-j1
      linkMatrC[i2][j1 >> 3] ^= 1 << (j1 & 7);
      linkMatrC[j1][i2 >> 3] ^= 1 << (i2 & 7);
      link[ik | 1] = j2;
      link[jk | 1] = i2;
      count--;
      continue;
    }
    if ((linkMatrC[i1][j1 >> 3] & (1 << (j1 & 7))) ||
        (linkMatrC[i2][j2 >> 3] & (1 << (j2 & 7))))
      continue;
    // i1-i2
    linkMatrC[i1][i2 >> 3] ^= 1 << (i2 & 7);
    linkMatrC[i2][i1 >> 3] ^= 1 << (i1 & 7);
    // j1-j2
    linkMatrC[j1][j2 >> 3] ^= 1 << (j2 & 7);
    linkMatrC[j2][j1 >> 3] ^= 1 << (j1 & 7);
    // i1-j1
    linkMatrC[i1][j1 >> 3] ^= 1 << (j1 & 7);
    linkMatrC[j1][i1 >> 3] ^= 1 << (i1 & 7);
    // i2-j2
    linkMatrC[i2][j2 >> 3] ^= 1 << (j2 & 7);
    linkMatrC[j2][i2 >> 3] ^= 1 << (i2 & 7);
    if (i1 < j1) {
      link[ik] = i1;
      link[ik | 1] = j1;
    } else {
      link[ik] = j1;
      link[ik | 1] = i1;
    }
    if (i2 < j2) {
      link[jk] = i2;
      link[jk | 1] = j2;
    } else {
      link[jk] = j2;
      link[jk | 1] = i2;
    }
    count--;
  }
  return 0;
}

int exchange_linkC_degDiff(VVChar& linkMatrC, VNodeType& link,
                           const VNodeType& p2pSize, LinkType count) {
  const LinkType linkSize = link.size() / 2;
  if (linkSize < 2) return -1;
  while (count > 0) {
    LinkType ik = RAND2_LONG() % linkSize, jk = RAND2_LONG() % (linkSize - 1);
    if (jk >= ik) jk++;
    ik <<= 1;
    jk <<= 1;
    NodeType i1 = link[ik], i2 = link[ik | 1], j1 = link[jk], j2 = link[jk | 1];
    NodeType pi1 = p2pSize[i1], pi2 = p2pSize[i2], pj1 = p2pSize[j1],
             pj2 = p2pSize[j2];
    if (i1 == j2 || i2 == j1 || (pi1 <= pj1 && pj2 <= pi2) ||
        (pj1 <= pi1 && pi2 <= pj2))
      continue;
    if ((pi2 <= pj1 || pj2 <= pi1) &&
        (linkMatrC[i1][j1 >> 3] & (1 << (j1 & 7))) == 0 &&
        (linkMatrC[i2][j2 >> 3] & (1 << (j2 & 7))) == 0) {
      // i1-i2
      linkMatrC[i1][i2 >> 3] ^= 1 << (i2 & 7);
      linkMatrC[i2][i1 >> 3] ^= 1 << (i1 & 7);
      // j1-j2
      linkMatrC[j1][j2 >> 3] ^= 1 << (j2 & 7);
      linkMatrC[j2][j1 >> 3] ^= 1 << (j1 & 7);
      // i1-j1
      linkMatrC[i1][j1 >> 3] ^= 1 << (j1 & 7);
      linkMatrC[j1][i1 >> 3] ^= 1 << (i1 & 7);
      // i2-j2
      linkMatrC[i2][j2 >> 3] ^= 1 << (j2 & 7);
      linkMatrC[j2][i2 >> 3] ^= 1 << (i2 & 7);
      if (i1 < j1) {
        link[ik] = i1;
        link[ik | 1] = j1;
      } else {
        link[ik] = j1;
        link[ik | 1] = i1;
      }
      if (i2 < j2) {
        link[jk] = i2;
        link[jk | 1] = j2;
      } else {
        link[jk] = j2;
        link[jk | 1] = i2;
      }
      count--;
      continue;
    }
    if ((linkMatrC[i1][j2 >> 3] & (1 << (j2 & 7))) == 0 &&
        (linkMatrC[i2][j1 >> 3] & (1 << (j1 & 7))) == 0) {
      // i1-i2
      linkMatrC[i1][i2] = 0;
      linkMatrC[i2][i1] = 0;
      // j1-j2
      linkMatrC[j1][j2] = 0;
      linkMatrC[j2][j1] = 0;
      // i1-j2
      linkMatrC[i1][j2] = 1;
      linkMatrC[j2][i1] = 1;
      // i2-j1
      linkMatrC[i2][j1] = 1;
      linkMatrC[j1][i2] = 1;
      link[ik | 1] = j2;
      link[jk | 1] = i2;
      count--;
    }
  }
  return 0;
}

int exchange_link_deg_same(VVDistType& linkMatr, VNodeType& link,
                           const VNodeType& p2pSize, LinkType count) {
  const LinkType linkSize = link.size() / 2;
  if (linkSize < 2) return -1;
  while (count > 0) {
    LinkType ik = RAND2_LONG() % linkSize, jk = RAND2_LONG() % (linkSize - 1);
    if (jk >= ik) jk++;
    ik <<= 1;
    jk <<= 1;
    NodeType i1 = link[ik], i2 = link[ik | 1], j1 = link[jk], j2 = link[jk | 1];
    NodeType pi1 = p2pSize[i1], pi2 = p2pSize[i2], pj1 = p2pSize[j1],
             pj2 = p2pSize[j2];
    if (pi1 >= pj2 || pj1 >= pi2 || i1 == j1 || i2 == j2) continue;
    if (pi1 != pj1 && pi2 != pj2 &&
        ((pj1 < pi1 && pi2 < pj2) || (pi1 < pj1 && pj2 < pi2)) &&
        linkMatr[i1][j2] == 0 && linkMatr[i2][j1] == 0) {
      // i1-i2
      linkMatr[i1][i2] = 0;
      linkMatr[i2][i1] = 0;
      // j1-j2
      linkMatr[j1][j2] = 0;
      linkMatr[j2][j1] = 0;
      // i1-j2
      linkMatr[i1][j2] = 1;
      linkMatr[j2][i1] = 1;
      // i2-j1
      linkMatr[i2][j1] = 1;
      linkMatr[j1][i2] = 1;
      link[ik | 1] = j2;
      link[jk | 1] = i2;
      count--;
      continue;
    }
    if (linkMatr[i1][j1] || linkMatr[i2][j2]) continue;
    // i1-i2
    linkMatr[i1][i2] = 0;
    linkMatr[i2][i1] = 0;
    // j1-j2
    linkMatr[j1][j2] = 0;
    linkMatr[j2][j1] = 0;
    // i1-j1
    linkMatr[i1][j1] = 1;
    linkMatr[j1][i1] = 1;
    // i2-j2
    linkMatr[i2][j2] = 1;
    linkMatr[j2][i2] = 1;
    if (i1 < j1) {
      link[ik] = i1;
      link[ik | 1] = j1;
    } else {
      link[ik] = j1;
      link[ik | 1] = i1;
    }
    if (i2 < j2) {
      link[jk] = i2;
      link[jk | 1] = j2;
    } else {
      link[jk] = j2;
      link[jk | 1] = i2;
    }
    count--;
  }
  return 0;
}

int exchange_link_deg_diff(VVDistType& linkMatr, VNodeType& link,
                           const VNodeType& p2pSize, LinkType count) {
  const LinkType linkSize = link.size() / 2;
  if (linkSize < 2) return -1;
  while (count > 0) {
    LinkType ik = RAND2_LONG() % linkSize, jk = RAND2_LONG() % (linkSize - 1);
    if (jk >= ik) jk++;
    ik <<= 1;
    jk <<= 1;
    NodeType i1 = link[ik], i2 = link[ik | 1], j1 = link[jk], j2 = link[jk | 1];
    NodeType pi1 = p2pSize[i1], pi2 = p2pSize[i2], pj1 = p2pSize[j1],
             pj2 = p2pSize[j2];
    if (i1 == j2 || j1 == i2 || (pi1 <= pj1 && pj2 <= pi2) ||
        (pj1 <= pi1 && pi2 <= pj2))
      continue;
    if ((pi2 <= pj1 || pj2 <= pi1) && linkMatr[i1][j1] == 0 &&
        linkMatr[i2][j2] == 0) {
      // i1-i2
      linkMatr[i1][i2] = 0;
      linkMatr[i2][i1] = 0;
      // j1-j2
      linkMatr[j1][j2] = 0;
      linkMatr[j2][j1] = 0;
      // i1-j1
      linkMatr[i1][j1] = 1;
      linkMatr[j1][i1] = 1;
      // i2-j2
      linkMatr[i2][j2] = 1;
      linkMatr[j2][i2] = 1;
      if (i1 < j1) {
        link[ik] = i1;
        link[ik | 1] = j1;
      } else {
        link[ik] = j1;
        link[ik | 1] = i1;
      }
      if (i2 < j2) {
        link[jk] = i2;
        link[jk | 1] = j2;
      } else {
        link[jk] = j2;
        link[jk | 1] = i2;
      }
      count--;
      continue;
    }
    if (linkMatr[i1][j2] == 0 && linkMatr[i2][j1] == 0) {
      // i1-i2
      linkMatr[i1][i2] = 0;
      linkMatr[i2][i1] = 0;
      // j1-j2
      linkMatr[j1][j2] = 0;
      linkMatr[j2][j1] = 0;
      // i1-j2
      linkMatr[i1][j2] = 1;
      linkMatr[j2][i1] = 1;
      // i2-j1
      linkMatr[i2][j1] = 1;
      linkMatr[j1][i2] = 1;
      link[ik | 1] = j2;
      link[jk | 1] = i2;
      count--;
    }
  }
  return 0;
}

int exchange_linkC_num_same(VVChar& linkMatrC, VNodeType& link,
                            LinkType count) {
  const LinkType linkSize = link.size();
  if (linkSize < 2) return -1;
  while (count > 0) {
    LinkType ik = RAND2_LONG() % linkSize, jk = RAND2_LONG() % (linkSize - 1);
    if (jk >= ik) jk++;
    ik <<= 1;
    jk <<= 1;
    NodeType i1 = link[ik], i2 = link[ik | 1], j1 = link[jk], j2 = link[jk | 1];
    if (i1 >= j2 || j1 >= i2 || i1 == j1 || i2 == j2) continue;
    if (((j1 < i1 && i2 < j2) || (i1 < j1 && j2 < i2)) &&
        (linkMatrC[i1][j2 >> 3] & (1 << (j2 & 7))) == 0 &&
        (linkMatrC[i2][j1 >> 3] & (1 << (j1 & 7))) == 0) {
      // i1-i2
      linkMatrC[i1][i2 >> 3] ^= 1 << (i2 & 7);
      linkMatrC[i2][i1 >> 3] ^= 1 << (i1 & 7);
      // j1-j2
      linkMatrC[j1][j2 >> 3] ^= 1 << (j2 & 7);
      linkMatrC[j2][j1 >> 3] ^= 1 << (j1 & 7);
      // i1-j2
      linkMatrC[i1][j2 >> 3] ^= 1 << (j2 & 7);
      linkMatrC[j2][i1 >> 3] ^= 1 << (i1 & 7);
      // i2-j1
      linkMatrC[i2][j1 >> 3] ^= 1 << (j1 & 7);
      linkMatrC[j1][i2 >> 3] ^= 1 << (i2 & 7);
      link[ik | 1] = j2;
      link[jk | 1] = i2;
      count--;
      continue;
    }
    if ((linkMatrC[i1][j1 >> 3] & (1 << (j1 & 7))) ||
        (linkMatrC[i2][j2 >> 3] & (1 << (j2 & 7))))
      continue;
    // i1-i2
    linkMatrC[i1][i2 >> 3] ^= 1 << (i2 & 7);
    linkMatrC[i2][i1 >> 3] ^= 1 << (i1 & 7);
    // j1-j2
    linkMatrC[j1][j2 >> 3] ^= 1 << (j2 & 7);
    linkMatrC[j2][j1 >> 3] ^= 1 << (j1 & 7);
    // i1-j1
    linkMatrC[i1][j1 >> 3] ^= 1 << (j1 & 7);
    linkMatrC[j1][i1 >> 3] ^= 1 << (i1 & 7);
    // i2-j2
    linkMatrC[i2][j2 >> 3] ^= 1 << (j2 & 7);
    linkMatrC[j2][i2 >> 3] ^= 1 << (i2 & 7);
    if (i1 < j1) {
      link[ik] = i1;
      link[ik | 1] = j1;
    } else {
      link[ik] = j1;
      link[ik | 1] = i1;
    }
    if (i2 < j2) {
      link[jk] = i2;
      link[jk | 1] = j2;
    } else {
      link[jk] = j2;
      link[jk | 1] = i2;
    }
    count--;
  }
  return 0;
}

int exchange_linkC_num_diff(VVChar& linkMatrC, VNodeType& link,
                            LinkType count) {
  const LinkType linkSize = link.size();
  if (linkSize < 2) return -1;
  while (count > 0) {
    LinkType ik = RAND2_LONG() % linkSize, jk = RAND2_LONG() % (linkSize - 1);
    if (jk >= ik) jk++;
    ik <<= 1;
    jk <<= 1;
    NodeType i1 = link[ik], i2 = link[ik | 1], j1 = link[jk], j2 = link[jk | 1];
    if (i1 == j2 || j1 == i2 || (i1 <= j1 && j2 <= i2) ||
        (j1 <= i1 && i2 <= j2))
      continue;
    if ((i1 > j2 || j1 > i2) &&
        (linkMatrC[i1][j1 >> 3] & (1 << (j1 & 7))) == 0 &&
        (linkMatrC[i2][j2 >> 3] & (1 << (j2 & 7))) == 0) {
      // i1-i2
      linkMatrC[i1][i2 >> 3] ^= 1 << (i2 & 7);
      linkMatrC[i2][i1 >> 3] ^= 1 << (i1 & 7);
      // j1-j2
      linkMatrC[j1][j2 >> 3] ^= 1 << (j2 & 7);
      linkMatrC[j2][j1 >> 3] ^= 1 << (j1 & 7);
      // i1-j1
      linkMatrC[i1][j1 >> 3] ^= 1 << (j1 & 7);
      linkMatrC[j1][i1 >> 3] ^= 1 << (i1 & 7);
      // i2-j2
      linkMatrC[i2][j2 >> 3] ^= 1 << (j2 & 7);
      linkMatrC[j2][i2 >> 3] ^= 1 << (i2 & 7);
      if (i1 < j1) {
        link[ik] = i1;
        link[ik | 1] = j1;
      } else {
        link[ik] = j1;
        link[ik | 1] = i1;
      }
      if (i2 < j2) {
        link[jk] = i2;
        link[jk | 1] = j2;
      } else {
        link[jk] = j2;
        link[jk | 1] = i2;
      }
      count--;
      continue;
    }
    if ((linkMatrC[i1][j2 >> 3] & (1 << (j2 & 7))) == 0 &&
        (linkMatrC[i2][j1 >> 3] & (1 << (j1 & 7))) == 0) {
      // i1-i2
      linkMatrC[i1][i2] = 0;
      linkMatrC[i2][i1] = 0;
      // j1-j2
      linkMatrC[j1][j2] = 0;
      linkMatrC[j2][j1] = 0;
      // i1-j2
      linkMatrC[i1][j2] = 1;
      linkMatrC[j2][i1] = 1;
      // i2-j1
      linkMatrC[i2][j1] = 1;
      linkMatrC[j1][i2] = 1;
      link[ik | 1] = j2;
      link[jk | 1] = i2;
      count--;
    }
  }
  return 0;
}

int exchange_link_num_same(VVDistType& linkMatr, VNodeType& link,
                           LinkType count) {
  const LinkType linkSize = link.size();
  if (linkSize < 2) return -1;
  while (count > 0) {
    LinkType ik = RAND2_LONG() % linkSize, jk = RAND2_LONG() % (linkSize - 1);
    if (jk >= ik) jk++;
    ik <<= 1;
    jk <<= 1;
    NodeType i1 = link[ik], i2 = link[ik | 1], j1 = link[jk], j2 = link[jk | 1];
    if (i1 >= j2 || j1 >= i2 || i1 == j1 || i2 == j2) continue;
    if (((j1 < i1 && i2 < j2) || (i1 < j1 && j2 < i2)) &&
        linkMatr[i1][j2] == 0 && linkMatr[i2][j1] == 0) {
      // i1-i2
      linkMatr[i1][i2] = 0;
      linkMatr[i2][i1] = 0;
      // j1-j2
      linkMatr[j1][j2] = 0;
      linkMatr[j2][j1] = 0;
      // i1-j2
      linkMatr[i1][j2] = 1;
      linkMatr[j2][i1] = 1;
      // i2-j1
      linkMatr[i2][j1] = 1;
      linkMatr[j1][i2] = 1;
      link[ik | 1] = j2;
      link[jk | 1] = i2;
      count--;
      continue;
    }
    if (linkMatr[i1][j1] || linkMatr[i2][j2]) continue;
    // i1-i2
    linkMatr[i1][i2] = 0;
    linkMatr[i2][i1] = 0;
    // j1-j2
    linkMatr[j1][j2] = 0;
    linkMatr[j2][j1] = 0;
    // i1-j1
    linkMatr[i1][j1] = 1;
    linkMatr[j1][i1] = 1;
    // i2-j2
    linkMatr[i2][j2] = 1;
    linkMatr[j2][i2] = 1;
    if (i1 < j1) {
      link[ik] = i1;
      link[ik | 1] = j1;
    } else {
      link[ik] = j1;
      link[ik | 1] = i1;
    }
    if (i2 < j2) {
      link[jk] = i2;
      link[jk | 1] = j2;
    } else {
      link[jk] = j2;
      link[jk | 1] = i2;
    }
    count--;
  }
  return 0;
}

int exchange_link_num_diff(VVDistType& linkMatr, VNodeType& link,
                           LinkType count) {
  const LinkType linkSize = link.size();
  if (linkSize < 2) return -1;
  while (count > 0) {
    LinkType ik = RAND2_LONG() % linkSize, jk = RAND2_LONG() % (linkSize - 1);
    if (jk >= ik) jk++;
    ik <<= 1;
    jk <<= 1;
    NodeType i1 = link[ik], i2 = link[ik | 1], j1 = link[jk], j2 = link[jk | 1];
    if ((i1 <= j1 && j2 <= i2) || (j1 <= i1 && i2 <= j2) || i1 == j2 ||
        i2 == j1)
      continue;
    if ((i2 < j1 || j2 < i1) && linkMatr[i1][j1] == 0 &&
        linkMatr[i2][j2] == 0) {
      // i1-i2
      linkMatr[i1][i2] = 0;
      linkMatr[i2][i1] = 0;
      // j1-j2
      linkMatr[j1][j2] = 0;
      linkMatr[j2][j1] = 0;
      // i1-j1
      linkMatr[i1][j1] = 1;
      linkMatr[j1][i1] = 1;
      // i2-j2
      linkMatr[i2][j2] = 1;
      linkMatr[j2][i2] = 1;
      if (i1 < j1) {
        link[ik] = i1;
        link[ik | 1] = j1;
      } else {
        link[ik] = j1;
        link[ik | 1] = i1;
      }
      if (i2 < j2) {
        link[jk] = i2;
        link[jk | 1] = j2;
      } else {
        link[jk] = j2;
        link[jk | 1] = i2;
      }
      count--;
      continue;
    }
    if (linkMatr[i1][j2] == 0 && linkMatr[i2][j1] == 0) {
      // i1-i2
      linkMatr[i1][i2] = 0;
      linkMatr[i2][i1] = 0;
      // j1-j2
      linkMatr[j1][j2] = 0;
      linkMatr[j2][j1] = 0;
      // i1-j2
      linkMatr[i1][j2] = 1;
      linkMatr[j2][i1] = 1;
      // i2-j1
      linkMatr[i2][j1] = 1;
      linkMatr[j1][i2] = 1;
      link[ik | 1] = j2;
      link[jk | 1] = i2;
      count--;
    }
  }
  return 0;
}

int count_sameAdiff(LinkType& sum, LinkType& sum1, LinkType& sum3,
                    LinkType& sum4, VLinkType& link, VNodeType& nodeDeg) {
  const LinkType linkSize = link.size() / 2;
  sum = 0 /*同配*/;
  sum1 = 0 /*异配*/;
  sum3 = 0 /*3点相同*/;
  sum4 = 0 /*全同*/;
  for (LinkType l = 1; l < linkSize; l++) {
    NodeType i1 = link[l * 2], i2 = link[2 * l + 1];
    for (LinkType ll = 0; ll < l; ll++) {
      NodeType j1 = link[ll * 2], j2 = link[ll * 2 + 1];
      if (i1 == j1 || i1 == j2 || i2 == j1 || i2 == j2) continue;
      NodeType di1 = nodeDeg[i1], di2 = nodeDeg[i2], dj1 = nodeDeg[j1],
               dj2 = nodeDeg[j2];
      if (di1 == di2 || dj1 == dj2) {  //有某边两端点度相同 i-i j-k
        if (di1 == di2 && dj1 == dj2) {  //两边的两端点度分别相同 i-i j-j
          if (di1 == dj1)
            sum4++;  //度全相同 i==j
          else
            sum++;  // i!=j  同配
          continue;
        }
        if (di1 == dj1 || di2 == dj2) {  //有3点度相同 i-i i-j
          sum3++;
          continue;
        }
        if (di1 > dj2 || dj1 > di2)
          sum++;  // i-i,j-k : i<j<k || j<k<i
        else
          sum1++;  // i-i,j-k: j<i<k
        continue;
      }
      // i-j k-l
      if (di1 >= dj2 || dj1 >= di2)
        sum++;
      else if ((di1 <= dj1 && dj2 <= di2) || (dj1 <= di1 && di2 <= dj2))
        sum1++;
      else
        sum++;
      continue;
    }
  }
  return 0;
}

//**//***********************************************************//*
bool cmp_RNodeType_start(const RNodeType& a, const RNodeType& b) {
  return a.start < b.start;
}

bool cmp_RNodeType_end(const RNodeType& a, const RNodeType& b) {
  return a.end < b.end;
}

int nodeDeg_update_nodeMap(VNodeType& nodeDeg, const VRNodeType& nodeMap) {
  if (nodeDeg.size() != nodeMap.size()) return -1;
  VNodeType t(nodeDeg.size());
  for (VRNodeTypeCItr i = nodeMap.begin(); i != nodeMap.end(); i++)
    t[i->end] = nodeDeg[i->start];
  swap(nodeDeg, t);
  return 0;
}

//**//***********************************************************//*
int read0_link(VNodeType& link, const char* name, const unsigned n) {
  if (n < 2 || name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  ifstream is(name);
  if (!is) {
    ERROR(name);
    return -1;
  }
  LinkType c = 0;
  for (NodeType i, j; is >> i >> j; c++) {
    link.push_back(i);
    link.push_back(j);
    unsigned t = 2;
    for (string x; t < n && (is >> x); t++)
      continue;
    if (t < n) {
      is.close();
      ERROR(name, "\t", c, "\t", t);
      return -1;
    }
  }
  is.close();
  cout << name << "\tlink, size:\t" << c << '\n';
  return 0;
}

int read_link(VNodeType& link, const char* name) {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  ifstream is(name);
  if (!is) {
    ERROR(name);
    return -1;
  }
  LinkType c = 0;
  for (NodeType i, j; is >> i >> j; c++) {
    link.push_back(i);
    link.push_back(j);
  }
  is.close();
  cout << name << "\tlink, size:\t" << c << '\n';
  return 0;
}

int read_weight_link(VVWeightType& vvweight, VVWeightType& vvweightIn,
                     const LinkType linkSize, const char* name,
                     const unsigned weight_m, const unsigned weight_n,
                     const int dirFlag) {
  if (weight_m < 2 || weight_m >= weight_n || name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  ifstream is(name);
  if (!is) {
    ERROR(name);
    return -1;
  }
  LinkType l = 0;
  for (NodeType i, j; l < linkSize && is >> i >> j; l++) {
    unsigned c = 2;
    for (string s; c < weight_m && is >> s; c++)
      continue;
    if (c < weight_m) {
      is.close();
      ERROR(name, '\t', l, ":\t", c);
      return -1;
    }
    WeightType w;
    if (!(is >> w)) {
      is.close();
      ERROR(name, '\t', l, ":\t", c);
      return -1;
    }
    if (!dirFlag) {
      NodeType m = i >= j ? i : j;
      if (vvweight.size() <= m) vvweight.resize(m + 1);
      vvweight[i].push_back(w);
      vvweight[j].push_back(w);
    } else {
      if (vvweight.size() <= i + 1) vvweight.resize(i + 1);
      vvweight[i].push_back(w);
      if (vvweightIn.size() <= j) vvweightIn.resize(j + 1);
      vvweightIn[j].push_back(w);
    }
    c++;
    for (string s; c < weight_n && is >> s; c++)
      continue;
    if (c < weight_n) {
      is.close();
      ERROR(name, '\t', l, ':', c);
      return -1;
    }
  }
  is.close();
  if (l < linkSize) {
    is.close();
    ERROR(name, '\t', l);
    return -1;
  }
  cout << name << "\tvvweight, size:\t" << l << '\n';
  return 0;
}

int read_link_weight_0(VNodeType& link, LinkType& linkSize,
                       VVWeightType& vvweight, VVWeightType& vvweightIn,
                       const char* name, const unsigned weight_m,
                       const unsigned weight_n, const int dirFlag) {
  if (weight_m < 2 || weight_m >= weight_n || name == NULL || name[0] == '\0' ||
      !link.empty() || !vvweight.empty()) {
    ERROR();
    return -1;
  }
  ifstream is(name);
  if (!is) {
    ERROR(name);
    return -1;
  }
  for (NodeType i, j; is >> i >> j; linkSize++) {
    link.push_back(i);
    link.push_back(j);
    unsigned c = 2;
    for (string s; c < weight_m && is >> s; c++)
      continue;
    if (c < weight_m) {
      is.close();
      ERROR(name, '\t', linkSize, ":\t", c);
      return -1;
    }

    WeightType w;
    if (!(is >> w)) {
      is.close();
      ERROR(name, '\t', linkSize, ":\t", c);
      return -1;
    }
    c++;

    if (!dirFlag) {
      NodeType m = i >= j ? i : j;
      if (vvweight.size() <= m) vvweight.resize(m + 1);
      vvweight[i].push_back(w);
      vvweight[j].push_back(w);
    } else {
      if (vvweight.size() <= i) vvweight.resize(i + 1);
      vvweight[i].push_back(w);
      if (vvweightIn.size() <= j) vvweightIn.resize(j + 1);
      vvweightIn[j].push_back(w);
    }
    for (string s; c < weight_n && is >> s; c++)
      continue;
    if (c < weight_n) {
      is.close();
      ERROR(name, '\t', linkSize, ':', c);
      return -1;
    }
  }
  is.close();
  cout << name << "\tlink vvweight, size:\t" << linkSize << '\n';
  return 0;
}

//**//***********************************************************//*
int cal_kMax_PowerLaw_NatureCutoff(NodeType& kMax, const NodeType nodeSize,
                                   const NodeType kMin, const double gamma) {
  if (kMin < 1 || nodeSize < kMin) {
    ERROR();
    return -1;
  }
  double r, c = 0, km;
  if (gamma <= 3)
    r = 0.5;
  else
    r = 1 / (gamma - 1);
  kMax = pow(nodeSize, r);
  if (kMax < kMin) return -1;
  for (NodeType i = kMin; i <= kMax; ++i) c += pow(i, r);
  km = pow(c / nodeSize, -1. / r);
  if (kMax > km) kMax = km;
  if (kMax < kMin) return -1;
  return 0;
}

//**//***********************************************************//*
