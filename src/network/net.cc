#include "net.h"
#include "../common/common.h"

using namespace std;
using namespace common;
using namespace network;

// ******************************************************
int network::init_linkMatrC(VVChar& linkMatrC, const NodeType nodeSize)
{
  const NodeType len = nodeSize / 8 + 1;
  linkMatrC.resize(nodeSize);
  linkMatrC[0].assign(len, 0);
  for (NodeType i = 1; i < nodeSize; i++)
    linkMatrC[i] = linkMatrC[0];
  return 0;
}

// ******************************************************
int network::linkMatr_fix_0(VVDistType& linkMatr, const DistType MaxDist)
{
  const NodeType nodeSize = linkMatr.size();
  for (NodeType i = 0; i < nodeSize; i++) {
    for (NodeType j = 0; j < nodeSize; j++) {
      if (i != j && linkMatr[i][j] >= MaxDist)
        linkMatr[i][j] = 0;
    }
  }
  return 0;
}

int network::linkMatr_fix_max(VVDistType& linkMatr, const DistType MaxDist)
{
  const NodeType nodeSize = linkMatr.size();
  for (NodeType i = 0; i < nodeSize; i++) {
    for (NodeType j = 0; j < nodeSize; j++) {
      if (i != j && linkMatr[i][j] == 0)
        linkMatr[i][j] = MaxDist;
    }
  }
  return 0;
}

int network::check_nodeDeg0(const VNodeType& nodeDeg)
{
  if (nodeDeg.empty())
    return -1;
  for (VNodeTypeCItr i = nodeDeg.begin(); i != nodeDeg.end(); i++)
    if (*i <= 0)
      return 1;
  return 0;
}

int network::fix_degArr_kExtremum(VNodeType& degArrSize,
    const VNodeType& degArrVal, const VDouble& degArrProb)
{
  const NodeType degSize = degArrVal.size();
  if (degSize <= 0 || (degSize == 1 && degArrVal[0] <= 1)) {
    ERROR();
    return -1;
  }
  for (NodeType k1, k2; degArrSize[0] <= 0 || degArrSize[degSize - 1] <= 0;) {
    if (degArrSize[0] <= 0)
      k1 = 0;
    else if (degArrSize[degSize - 1] <= 0)
      k1 = degSize - 1;
    while (1) {
      k2 = std::uniform_int_distribution<NodeType>(0, degSize - 2)(rand2);
      if (k1 == 0)
        ++k2;
      if (degArrSize[k2] > 0 && (k2 != 0 || degArrSize[0] > 1)
          && (k2 != degSize - 1 || degArrSize[degSize - 1] > 1)
          && rand_double() < degArrProb[k2])
        break;
    }
    ++degArrSize[k1];
    --degArrSize[k2];
  }
  return 0;
}

int network::fix_degArr_linkSize(VNodeType& degArrSize,
    const VNodeType& degArrVal, const VDouble& degArrProb, LinkType& linkSize)
{
  const NodeType degSize = degArrVal.size();
  if (degSize < 2)
    return -1;
  NodeType k1, k2;
  while (1) {
    while (1) {
      k1 = std::uniform_int_distribution<NodeType>(0, degSize - 1)(rand2);
      if (degArrSize[k1] > 0 && (k1 != 0 || degArrSize[0] > 1)
          && (k1 != degSize - 1 || degArrSize[degSize - 1] > 1)
          && rand_double() < degArrProb[k1])
        break;
    }
    while (1) {
      k2 = std::uniform_int_distribution<NodeType>(0, degSize - 2)(rand2);
      if (k2 <= k1)
        ++k2;
      if (rand_double() < degArrProb[k2])
        break;
    }
    if (degArrVal[k1] % 2 != degArrVal[k2] % 2)
      break;
  }
  linkSize = linkSize - degArrVal[k1] + degArrVal[k2];
  --degArrSize[k1];
  ++degArrSize[k2];
  return 0;
}

int network::fix_degArr_linkSize3(VNodeType& degArrSize,
    const VNodeType& degArrVal, const VDouble& degArrProb, LinkType& linkSize)
{
  const NodeType degSize = degArrVal.size();
  if (degSize < 2)
    return -1;
  NodeType k1, k2;
  double sum = 0;
  total(&degArrProb[0], degSize, sum);
  while (1) {
    while (1) {
      k1 = new_prob_sum(&degArrProb[0], degSize, sum);
      if (degArrSize[k1] > 0 && (k1 != 0 || degArrSize[0] > 1)
          && (k1 != degSize - 1 || degArrSize[degSize - 1] > 1))
        break;
    }
    while (1) {
      k2 = new_prob_sum(&degArrProb[0], degSize, sum);
      if (k2 <= k1)
        ++k2;
      if (k2 != k1)
        break;
    }
    if (degArrVal[k1] % 2 != degArrVal[k2] % 2)
      break;
  }
  linkSize = linkSize - degArrVal[k1] + degArrVal[k2];
  --degArrSize[k1];
  ++degArrSize[k2];
  return 0;
}

int network::fix_degArr_linkSize2(VNodeType& degArrSize,
    const VNodeType& degArrVal, const VDouble& degArrProbSum,
    LinkType& linkSize)
{
  const NodeType degSize = degArrVal.size();
  if (degSize < 2)
    return -1;
  NodeType k1, k2;
  while (1) {
    while (1) {
      k1 = new_probSum(&degArrProbSum[0], degSize);
      if (degArrSize[k1] > 0 && (k1 != 0 || degArrSize[0] > 1)
          && (k1 != degSize - 1 || degArrSize[degSize - 1] > 1))
        break;
    }
    while (1) {
      k2 = new_probSum(&degArrProbSum[0], degSize);
      if (k2 != k1)
        break;
    }
    if (degArrVal[k1] % 2 != degArrVal[k2] % 2)
      break;
  }
  linkSize = linkSize - degArrVal[k1] + degArrVal[k2];
  --degArrSize[k1];
  ++degArrSize[k2];
  return 0;
}

int network::fix_nodeDeg(VNodeType& nodeDeg, const VDouble& degArrProb,
    const VNodeType& degArrVal, LinkType& linkSize)
{
  const NodeType nodeSize = nodeDeg.size(), degSize = degArrVal.size();
  for (NodeType num, k; 1;) {
    num = std::uniform_int_distribution<NodeType>(0, nodeSize - 1)(rand2);
    k = std::uniform_int_distribution<NodeType>(0, degSize - 1)(rand2);
    if (nodeDeg[num] % 2 != degArrVal[k] % 2)
      if (rand_double() < degArrProb[k]) {
        linkSize = linkSize - nodeDeg[num] + degArrVal[k];
        nodeDeg[num] = degArrVal[k];
        break;
      }
  }
  return 0;
}

int network::fix_degArrSize_0(VNodeType& degArrSize, VNodeType& degArrVal)
{
  size_t d = degArrVal.size(), h = 0;
  if (degArrSize.size() != d) {
    ERROR();
    return -1;
  }
  for (size_t i = 0; i < d; ++i) {
    if (degArrSize[i] > 0) {
      if (i != h) {
        degArrVal[h] = degArrVal[i];
        degArrSize[h] = degArrSize[i];
      }
      ++h;
    }
  }
  if (h < d) {
    degArrVal.resize(h);
    degArrSize.resize(h);
  }
  return 0;
}

// ******************************************************
int network::sort_p2p(VVNodeType& p2p)
{
  for (VVNodeTypeItr i = p2p.begin(); i != p2p.end(); i++)
    if (!i->empty())
      sort(i->begin(), i->end());
  return 0;
}

int network::fix_p2p(VVNodeType& p2p, const int dirFlag)
{
  LinkType self = 0, multi = 0, miss = 0;
  for (NodeType i = 0; i < p2p.size(); i++) {
    // 自环
    if (p2p[i].empty())
      continue;
    for (NodeType j = 0; j < p2p[i].size();) {
      if (p2p[i][j] == i) {
        self++;
        p2p[i][j] = p2p[i][p2p[i].size() - 1];
        p2p[i].pop_back();
      } else
        j++;
    }
    if (p2p[i].empty())
      continue;
    sort(p2p[i].begin(), p2p[i].end()); // 从小到大排序
    if (p2p.size() <= p2p[i].back() + 1)
      p2p.resize(p2p[i].back() + 1);
    // 重边
    if (p2p[i].size() <= 1)
      continue;
    VNodeTypeCItr e = p2p[i].end();
    VNodeTypeItr j = p2p[i].begin();
    while (j + 1 != e && *j != *(j + 1))
      j++;
    if (j + 1 != e) {
      for (VNodeTypeCItr k = j + 1; k != e; k++) {
        if (*j != *k)
          *++j = *k;
      }
    }
    NodeType t = j + 1 - p2p[i].begin();
    if (p2p[i].size() > t) {
      multi += p2p[i].size() - t;
      p2p[i].resize(t);
    }
  }
  if (!dirFlag) { // 无向网络相互连接
    for (NodeType i = 0; i < p2p.size(); i++) {
      for (VNodeTypeCItr iItr = p2p[i].begin(), jItr; iItr != p2p[i].end();
           iItr++) {
        VVNodeTypeItr j = p2p.begin() + *iItr;
        for (jItr = j->begin(); jItr < j->end(); jItr++)
          if (*jItr == i)
            break;
        if (jItr >= j->end()) {
          miss++;
          j->push_back(i);
        }
      }
    }
    for (VVNodeTypeItr i = p2p.begin(); i != p2p.end(); i++)
      sort(i->begin(), i->end()); // 从小到大排序
  }
  cout << "fix_p2p\tself\t" << self << "\n\tmulti\t" << multi << "\n\tmiss\t"
       << miss << '\n';
  return 0;
}

int network::qsort_p2p(VVNodeType& p2p, const VVDistType& linkMatr)
{
  for (NodeType i = 0; i < p2p.size(); i++) {
    if (p2p[i].size() >= 2)
      common::sort_p_val(p2p[i].begin(), p2p[i].end(), &linkMatr[i].front());
  }
  return 0;
}

int network::del_pij(const NodeType i, const NodeType j, VVNodeType& p2p,
    VVNodeType& p2pIn, const int dirFlag)
{
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

int network::add_pij(const NodeType i, const NodeType j, VVNodeType& p2p,
    VVNodeType& p2pIn, const int dirFlag)
{
  int flag = 1;
  for (NodeType n = 0; n < p2p[i].size(); n++)
    if (p2p[i][n] == j) {
      flag = 0;
      break;
    }
  if (flag)
    p2p[i].push_back(j);
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
    if (flag)
      p2pIn[j].push_back(i);
  }
  return 0;
}

int network::sort_link_betwEdge(
    VNodeType& link, VVDouble& betwEdge, LinkType linkSize)
{
  if (linkSize == 1 || link.size() < 4)
    return 0;
  if (linkSize < 1)
    linkSize = link.size() / 2;

  stack<common::RangeP<PNodeType>> st;
  st.push(common::RangeP<PNodeType>(
      &link.front(), &link.front() + (linkSize - 1) * 2));
  while (!st.empty()) {
    common::RangeP<PNodeType> range = st.top();
    st.pop();
    PNodeType start = range.start, end = range.end;
    if (betwEdge[*start][start[1]] > betwEdge[*end][end[1]]) {
      swap(*start, *end);
      swap(start[1], end[1]);
    }
    if (start + 2 >= end)
      continue;
    double pivot = betwEdge[*(start + (end - start) / 2)]
                           [*(start + (end - start) / 2 + 1)];
    if (betwEdge[*start][start[1]] > pivot)
      pivot = betwEdge[*start][start[1]];
    else if (betwEdge[*end][end[1]] < pivot)
      pivot = betwEdge[*end][end[1]];
    while (start < end) {
      while (start < end && betwEdge[*start][start[1]] <= pivot)
        start += 2;
      while (start < end && betwEdge[*end][end[1]] >= pivot)
        end -= 2;
      if (start < end) {
        swap(*start, *end);
        swap(start[1], end[1]);
        start += 2;
        end -= 2;
      }
    }
    while (start > range.start && betwEdge[*start][start[1]] >= pivot)
      start -= 2;
    while (end < range.end && betwEdge[*end][end[1]] <= pivot)
      end += 2;
    if (range.start < start)
      st.push(common::RangeP<PNodeType>(range.start, start));
    if (end < range.end)
      st.push(common::RangeP<PNodeType>(end, range.end));
  }

  return 0;
}

// ******************************************************
int network::addLink_linkMatrC_ranNode(
    VVChar& linkMatrC, LinkType& linkRemain) // 每次直接随机抽取两个点连边
{
  const NodeType nodeSize = linkMatrC.size();
  while (linkRemain > 0) {
    NodeType i
        = std::uniform_int_distribution<NodeType>(0, nodeSize - 1)(rand2),
        j = std::uniform_int_distribution<NodeType>(0, nodeSize - 2)(rand2);
    if (j >= i)
      j++;
    if (linkMatrC[i][j >> 3] & (1 << (j & 7)))
      continue;                             // linkMatrC[i][j]
    linkMatrC[i][j >> 3] |= (1 << (j & 7)); // linkMatrC[i][j] = 1;
    linkMatrC[j][i >> 3] |= (1 << (i & 7)); // linkMatrC[j][i] = 1;
    linkRemain--;
  }
  return 0;
}

int network::addLink_linkMatrC_proNode(VVChar& linkMatrC, LinkType& linkSize,
    const double p) // 所有点按概率p连边
{
  const NodeType nodeSize = linkMatrC.size();
  const NodeType size = nodeSize / 8 + 1;
  linkMatrC.resize(nodeSize);
  linkMatrC[0].assign(size, 0);
  for (NodeType i = 1; i < nodeSize; i++)
    for (NodeType j = 0; j < i; j++)
      if (rand_double() < p) {
        linkMatrC[i][j >> 3] |= (1 << (j & 7)); // linkMatrC[i][j] = 1;
        linkMatrC[j][i >> 3] |= (1 << (i & 7)); // linkMatrC[j][i] = 1;
        linkSize++;
      }
  return 0;
}

int network::addLink_linkMatr_ranNode(VVDistType& linkMatr,
    LinkType& linkRemain) // 每次直接随机抽取两个点连边
{
  const NodeType nodeSize = linkMatr.size();
  while (linkRemain > 0) {
    NodeType i
        = std::uniform_int_distribution<NodeType>(0, nodeSize - 1)(rand2),
        j = std::uniform_int_distribution<NodeType>(0, nodeSize - 2)(rand2);
    if (j >= i)
      j++;
    if (linkMatr[i][j])
      continue;         // linkMatr[i][j]
    linkMatr[i][j] = 1; // linkMatr[i][j] = 1;
    linkMatr[j][i] = 1; // linkMatr[j][i] = 1;
    linkRemain--;
  }
  return 0;
}

int network::addLink_linkMatr_proNode(VVDistType& linkMatr,
    LinkType& linkSize,
    const double p) // 所有点按概率p连边
{
  const NodeType nodeSize = linkMatr.size();
  linkMatr.resize(nodeSize);
  linkMatr[0].assign(nodeSize, 0);
  for (NodeType i = 1; i < nodeSize; i++)
    linkMatr[i] = linkMatr[0];
  for (NodeType i = 1; i < nodeSize; i++)
    for (NodeType j = 0; j < i; j++)
      if (rand_double() < p) {
        linkMatr[i][j] = 1; // linkMatr[i][j] = 1;
        linkMatr[j][i] = 1; // linkMatr[j][i] = 1;
        linkSize++;
      }
  return 0;
}

int network::addLink_linkMatrC_ranNode2(VVChar& linkMatrC, VNodeType& nodeDeg,
    VNodeType& p2pSize, VNodeType& remPoiNum, LinkType& linkRemain,
    const LinkType tryCount) // 每次直接随机抽取两个点连边
{
  for (LinkType try0 = 0; linkRemain > 0 && remPoiNum.size() > 1;) {
    NodeType ik = std::uniform_int_distribution<NodeType>(
        0, remPoiNum.size() - 1)(rand2);
    NodeType i = remPoiNum[ik];
    if (p2pSize[i] >= nodeDeg[i]) {
      remPoiNum[ik] = remPoiNum.back();
      remPoiNum.pop_back();
      continue;
    }
    NodeType jk = std::uniform_int_distribution<NodeType>(
        0, remPoiNum.size() - 2)(rand2);
    if (jk >= ik)
      jk++;
    NodeType j = remPoiNum[jk];
    if (p2pSize[j] >= nodeDeg[j]) {
      remPoiNum[jk] = remPoiNum.back();
      remPoiNum.pop_back();
      continue;
    }
    if (linkMatrC[i][j >> 3] & (1 << (j & 7))) { // linkMatrC[i][j] == 1
      if (++try0 >= tryCount)
        break;
      else
        continue;
    }
    linkMatrC[i][j >> 3] ^= (1 << (j & 7)); // linkMatrC[i][j] = 1;
    linkMatrC[j][i >> 3] ^= (1 << (i & 7)); // linkMatrC[j][i] = 1;
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

int network::addLink_linkMatr_ranNode2(VVDistType& linkMatr,
    VNodeType& nodeDeg, VNodeType& p2pSize, VNodeType& remPoiNum,
    LinkType& linkRemain,
    const LinkType tryCount) // 每次直接随机抽取两个点连边
{
  for (LinkType try0 = 0; linkRemain > 0 && remPoiNum.size() > 1;) {
    NodeType ik = std::uniform_int_distribution<NodeType>(
        0, remPoiNum.size() - 1)(rand2);
    NodeType i = remPoiNum[ik];
    if (p2pSize[i] >= nodeDeg[i]) {
      remPoiNum[ik] = remPoiNum.back();
      remPoiNum.pop_back();
      continue;
    }
    NodeType jk = std::uniform_int_distribution<NodeType>(
        0, remPoiNum.size() - 2)(rand2);
    if (jk >= ik)
      jk++;
    NodeType j = remPoiNum[jk];
    if (p2pSize[j] >= nodeDeg[j]) {
      remPoiNum[jk] = remPoiNum.back();
      remPoiNum.pop_back();
      continue;
    }
    if (linkMatr[i][j] != 0) { // linkMatr[i][j] == 1
      if (++try0 >= tryCount)
        break;
      else
        continue;
    }
    linkMatr[i][j] = 1; // linkMatr[i][j] = 1;
    linkMatr[j][i] = 1; // linkMatr[j][i] = 1;
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

int network::addLink_p2p_ranNode0(VVNodeType& p2p, VNodeType& link,
    VNodeType& nodeDeg, VNodeType& remPoiNum, LinkType& linkRemain,
    const LinkType tryCount)
{
  for (LinkType try0 = 0; linkRemain > 0 && remPoiNum.size() > 1;) {
    NodeType ik = std::uniform_int_distribution<NodeType>(
                 0, remPoiNum.size() - 1)(rand2),
             i;
    i = remPoiNum[ik];
    if (p2p[i].size() >= nodeDeg[i]) {
      remPoiNum[ik] = remPoiNum.back();
      remPoiNum.pop_back();
      continue;
    }
    NodeType jk = std::uniform_int_distribution<NodeType>(
                 0, remPoiNum.size() - 2)(rand2),
             j;
    if (jk >= ik)
      jk++;
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
      if (p2p[i][t] == j)
        break;
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

int network::addLink_p2p_proDeg(VVNodeType& p2p, VNodeType& link,
    const VNodeType& nodeDeg, const NodeType kMax, VNodeType& remPoiNum,
    LinkType& linkRemain, const LinkType tryCount)
{
  for (LinkType try0 = 0; linkRemain > 0 && remPoiNum.size() > 1;) {
    NodeType ik = std::uniform_int_distribution<NodeType>(
                 0, remPoiNum.size() - 1)(rand2),
             i;
    i = remPoiNum[ik];
    if (p2p[i].size() >= nodeDeg[i]) {
      remPoiNum[ik] = remPoiNum.back();
      remPoiNum.pop_back();
      continue;
    }
    if (rand_double() * kMax > nodeDeg[i])
      continue;
    NodeType jk = std::uniform_int_distribution<NodeType>(
                 0, remPoiNum.size() - 2)(rand2),
             j;
    if (jk >= ik)
      jk++;
    j = remPoiNum[jk];
    if (p2p[j].size() >= nodeDeg[j]) {
      remPoiNum[jk] = remPoiNum.back();
      remPoiNum.pop_back();
      continue;
    }
    if (rand_double() * kMax > nodeDeg[j])
      continue;
    NodeType t;
    if (p2p[i].size() > p2p[j].size()) {
      t = ik;
      ik = jk;
      jk = t;
      i = remPoiNum[ik];
      j = remPoiNum[jk];
    }
    for (t = 0; t < p2p[i].size(); t++)
      if (p2p[i][t] == j)
        break;
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

int network::addLink_p2p_ranNode(VVNodeType& p2p, VNodeType& nodeDeg,
    VNodeType& remPoiNum, LinkType& linkRemain, const LinkType tryCount)
{
  for (LinkType try0 = 0; linkRemain > 0 && remPoiNum.size() > 1;) {
    NodeType ik = std::uniform_int_distribution<NodeType>(
                 0, remPoiNum.size() - 1)(rand2),
             i;
    i = remPoiNum[ik];
    if (p2p[i].size() >= nodeDeg[i]) {
      remPoiNum[ik] = remPoiNum.back();
      remPoiNum.pop_back();
      continue;
    }
    NodeType jk = std::uniform_int_distribution<NodeType>(
                 0, remPoiNum.size() - 2)(rand2),
             j;
    if (jk >= ik)
      jk++;
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
      if (p2p[i][t] == j)
        break;
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

int network::addLink_p2p_ranLink(VVNodeType& p2p, VNodeType& nodeDeg,
    NodeType& remPoiSize, LinkType& linkRemain, VNodeType& link,
    const LinkType tryCount)
{
  for (LinkType try0 = 0; linkRemain > 0 && remPoiSize > 1;) {
    LinkType ik = std::uniform_int_distribution<LinkType>(
                 0, linkRemain * 2 - 1)(rand2),
             jk;
    NodeType i = link[ik], j;
    do {
      jk = std::uniform_int_distribution<LinkType>(0, linkRemain * 2 - 2)(
          rand2);
      if (jk >= ik)
        jk++;
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
      if (p2p[i][k] == j)
        break;
    if (k < p2p[i].size()) {
      if (++try0 >= tryCount)
        break;
      else
        continue;
    }
    p2p[i].push_back(j);
    p2p[j].push_back(i);
    if (p2p[i].size() == nodeDeg[i])
      remPoiSize--;
    if (p2p[j].size() == nodeDeg[j])
      remPoiSize--;
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

int network::addLink_p2p_ranLink_lkkProb(VVNodeType& p2p,
    const VNodeType& nodeDeg, VVDouble& lkkProb, MNodeType& degArrNo,
    NodeType& remPoiSize, LinkType& linkRemain, VNodeType& link,
    const LinkType tryCount)
{
  for (LinkType try0 = 0; linkRemain > 0 && remPoiSize > 1;) {
    LinkType ik, jk;
    NodeType i, j;
    while (1) {
      ik = std::uniform_int_distribution<LinkType>(0, linkRemain * 2 - 1)(
          rand2);
      i = link[ik];
      jk = std::uniform_int_distribution<LinkType>(0, linkRemain * 2 - 2)(
          rand2);
      if (jk >= ik)
        jk++;
      j = link[jk];
      if (i != j
          && rand_double()
              <= lkkProb[degArrNo[nodeDeg[i]]][degArrNo[nodeDeg[j]]])
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
      if (p2p[i][k] == j)
        break;
    if (k < p2p[i].size()) {
      if (++try0 >= tryCount)
        break;
      else
        continue;
    }
    p2p[i].push_back(j);
    p2p[j].push_back(i);
    if (p2p[i].size() == nodeDeg[i])
      remPoiSize--;
    if (p2p[j].size() == nodeDeg[j])
      remPoiSize--;
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

// 添加节点 [n,M) 的全连通网络
int network::addLink_p2p_full(VVNodeType& p2p, NodeType M, const NodeType n)
{
  if (M > p2p.size() || n > M)
    return -1;
  if (M == 0)
    M = p2p.size();
  if (M <= 1)
    return 0;
  for (NodeType i = n + 1; i < M; ++i)
    for (NodeType j = n; j < i; ++j) {
      p2p[i].push_back(j);
      p2p[j].push_back(i);
    }
  return 0;
}

int network::addLink_p2p_link_full(
    VVNodeType& p2p, VNodeType& link, NodeType M, const NodeType n)
{
  if (M > p2p.size() || n > M)
    return -1;
  if (M == 0)
    M = p2p.size();
  if (M <= 1)
    return 0;
  for (NodeType i = n + 1; i < M; ++i)
    for (NodeType j = n; j < i; ++j) {
      p2p[i].push_back(j);
      p2p[j].push_back(i);
      link.push_back(j);
      link.push_back(i);
    }
  return 0;
}

int network::delLink_p2p_ranLink(VVNodeType& p2p, VNodeType& nodeDeg,
    VNodeType& remPoiNum, LinkType& linkRemain, const LinkType linkSize,
    VNodeType& link, LinkType delCount)
{
  while (delCount > 0 && linkRemain < linkSize) {
    NodeType i, j;
    LinkType l = std::uniform_int_distribution<LinkType>(
        linkRemain, linkSize - 1)(rand2);
    i = link[l * 2];
    j = link[l * 2 + 1];
    if (p2p[i].size() == nodeDeg[i])
      remPoiNum.push_back(i);
    for (NodeType k = p2p[i].size(), *p = &p2p[i][0]; k > 0; p++, k--) {
      if (*p == j) {
        *p = p2p[i].back();
        p2p[i].pop_back();
        break;
      }
    }
    if (p2p[j].size() == nodeDeg[j])
      remPoiNum.push_back(j);
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

int network::delLink_linkMatrC_ranNode(VVChar& linkMatrC,
    const NodeType nodeSize, VNodeType& nodeDeg, VNodeType& p2pSize,
    VNodeType& remPoiNum, LinkType& linkRemain, const LinkType linkSize,
    LinkType delCount) // 随机选点删边
{
  while (delCount > 0 && linkRemain < linkSize) {
    NodeType i;
    do {
      i = std::uniform_int_distribution<NodeType>(0, nodeSize - 1)(rand2);
    } while (p2pSize[i] <= 0);
    NodeType j;
    do {
      j = std::uniform_int_distribution<NodeType>(0, nodeSize - 2)(rand2);
      if (j >= i)
        j++;
    } while (p2pSize[j] <= 0);
    if (linkMatrC[i][j >> 3] & (1 << (j & 7))) { // linkMatr[i][j] == 1
      linkMatrC[i][j >> 3] ^= (1 << (j & 7));    // linkMatr[i][j] = 0
      linkMatrC[j][i >> 3] ^= (1 << (i & 7));    // linkMatr[j][i] = 0
      if (p2pSize[i]-- == nodeDeg[i])
        remPoiNum.push_back(i);
      if (p2pSize[j]-- == nodeDeg[j])
        remPoiNum.push_back(j);
      linkRemain++;
      delCount--;
    }
  }
  return (delCount > 0 ? -1 : 0);
}

int network::delLink_p2p_ranNode(VVNodeType& p2p, const NodeType nodeSize,
    const VNodeType& nodeDeg, VNodeType& remPoiNum, NodeType& remPoiSize,
    LinkType& linkRemain, const LinkType linkSize,
    LinkType delCount) // 随机选点删边
{
  while (delCount > 0 && linkRemain < linkSize) {
    NodeType i;
    do {
      i = std::uniform_int_distribution<NodeType>(0, nodeSize - 1)(rand2);
    } while (p2p[i].size() <= 0);
    NodeType j;
    do {
      j = std::uniform_int_distribution<NodeType>(0, nodeSize - 2)(rand2);
      if (j >= i)
        j++;
    } while (p2p[j].size() <= 0);
    NodeType k;
    if (p2p[i].size() > p2p[j].size()) {
      k = i;
      i = j;
      j = k;
    }
    for (k = 0; k < p2p[i].size(); k++)
      if (p2p[i][k] == j)
        break;
    if (k >= p2p[i].size())
      continue;
    if (p2p[i].size() == nodeDeg[i])
      remPoiNum.push_back(i);
    if (p2p[j].size() == nodeDeg[j])
      remPoiNum.push_back(j);
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

int network::delLink_p2p_ranNode1(VVNodeType& p2p, const NodeType nodeSize,
    VNodeType& nodeDeg, VNodeType& remPoiNum, NodeType& remPoiSize,
    LinkType& linkRemain, const LinkType linkSize,
    LinkType delCount) // 随机选点再选边删除
{
  while (delCount > 0 && linkRemain < linkSize) {
    NodeType i;
    do {
      i = std::uniform_int_distribution<NodeType>(0, nodeSize - 1)(rand2);
    } while (p2p[i].size() <= 0);
    NodeType k = std::uniform_int_distribution<NodeType>(
                 0, p2p[i].size() - 1)(rand2),
             j;
    j = p2p[i][k];
    if (p2p[i].size() == nodeDeg[i])
      remPoiNum.push_back(i);
    if (p2p[j].size() == nodeDeg[j])
      remPoiNum.push_back(j);
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

int network::delLink_link_ranLink(VNodeType& link, LinkType delCount)
{
  LinkType size = link.size();
  if (delCount * 2 > size || size % 2 != 0)
    return -1;
  for (LinkType i_max = size / 2 - 1, i; delCount > 0; --i_max, --delCount) {
    size -= 2;
    std::uniform_int_distribution<LinkType> dis(0, i_max);
    i = dis(rand2);
    if (i != i_max) {
      link[i * 2] = link[size];
      link[i * 2 + 1] = link[size + 1];
    }
    link.resize(size);
  }
  return 0;
}

int network::delNode_p2p_max(VVNodeType& p2p, const NodeType n)
{
  if (n > p2p.size())
    return -1;
  if (n == p2p.size())
    return 0;
  p2p.resize(n);
  for (NodeType i = 0; i < n; ++i) {
    NodeType head = 0, end = 0, deg_i = p2p[i].size();
    while (head < deg_i && p2p[i][head] < n)
      ++head;
    if (head >= deg_i)
      continue;
    for (end = head + 1; end < deg_i; ++end) {
      if (p2p[i][end] < n) {
        p2p[i][head++] = p2p[i][end];
      }
    }
    p2p[i].resize(head);
  }
  return 0;
}

// *********************************************************************
int network::check_p2pSize_linkSize(
    const VVNodeType& p2p, const LinkType linkSize)
{
  LinkType t = 0;
  for (NodeType i = 0; i < p2p.size(); i++)
    t += p2p[i].size();
  if (t != linkSize * 2)
    return -1;
  return 0;
}

int network::check_p2p(const VVNodeType& p2p)
{
  for (NodeType i = 0, nodeSize = p2p.size(); i < nodeSize; i++) {
    if (p2p[i].size() >= nodeSize)
      return -1;
    for (NodeType j = 0; j < p2p[i].size(); j++) {
      NodeType k = p2p[i][j], t;
      if (k == i || k >= nodeSize || p2p[k].size() >= nodeSize)
        return -1;
      for (t = 0; t < p2p[k].size(); t++)
        if (p2p[k][t] == i)
          break;
      if (t >= p2p[k].size())
        return -1;
    }
  }
  return 0;
}

int network::check_p2p_nodeDeg(
    const VVNodeType& p2p, const VNodeType& nodeDeg)
{
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

int network::check_link(VNodeType& link)
{
  if (link.size() % 2 != 0)
    return -1;
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

int network::sort_link_greater_1(VNodeType& link, const VNodeType& nodeDeg)
{
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

int network::sort_link_smaller_1(VNodeType& link, const VNodeType& nodeDeg)
{
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

int network::sort_link_num_greater_1(VNodeType& link)
{
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

int network::sort_link_num_smaller_1(VNodeType& link)
{
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

int network::sort_link_greater_all(VNodeType& link, const VNodeType& p2pSize)
{
  const LinkType linkSize = link.size() / 2;
  if (linkSize < 2)
    return 0;
  NodeType* p0 = &link[linkSize * 2 - 2];
  for (char flag = 1; flag; p0 -= 2) {
    flag = 0;
    for (NodeType* p = &link[0]; p < p0; p += 2) {
      if (p2pSize[*p] > p2pSize[p[2]]
          || (p2pSize[*p] == p2pSize[p[2]]
                 && p2pSize[p[1]] > p2pSize[p[3]])) {
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

int network::sort_link_num_greater_all(VNodeType& link)
{
  const LinkType linkSize = link.size() / 2;
  if (linkSize < 2)
    return 0;
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

int network::sort_link_smaller_all(VNodeType& link, const VNodeType& p2pSize)
{
  const LinkType linkSize = link.size() / 2;
  if (linkSize < 2)
    return 0;
  NodeType* p0 = &link[linkSize * 2 - 2];
  for (char flag = 1; flag; p0 -= 2) {
    flag = 0;
    for (NodeType* p = &link[0]; p < p0; p += 2) {
      if (p2pSize[*p] < p2pSize[p[2]]
          || (p2pSize[*p] == p2pSize[p[2]]
                 && p2pSize[p[1]] < p2pSize[p[3]])) {
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

int network::sort_link_num_smaller_all(VNodeType& link)
{
  const LinkType linkSize = link.size() / 2;
  if (linkSize < 2)
    return 0;
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

int network::exchange_linkC_deg_same(VVChar& linkMatrC, VNodeType& link,
    const VNodeType& p2pSize, LinkType count)
{
  const LinkType linkSize = link.size() / 2;
  if (linkSize < 2)
    return -1;
  while (count > 0) {
    LinkType ik
        = std::uniform_int_distribution<LinkType>(0, linkSize - 1)(rand2),
        jk = std::uniform_int_distribution<LinkType>(0, linkSize - 2)(rand2);
    if (jk >= ik)
      jk++;
    ik <<= 1;
    jk <<= 1;
    NodeType i1 = link[ik], i2 = link[ik | 1], j1 = link[jk],
             j2 = link[jk | 1];
    NodeType pi1 = p2pSize[i1], pi2 = p2pSize[i2], pj1 = p2pSize[j1],
             pj2 = p2pSize[j2];
    if (pi1 >= pj2 || pj1 >= pi2 || i1 == j1 || i2 == j2)
      continue;
    if (pi1 != pj1 && pi2 != pj2
        && ((pj1 < pi1 && pi2 < pj2) || (pi1 < pj1 && pj2 < pi2))
        && (linkMatrC[i1][j2 >> 3] & (1 << (j2 & 7))) == 0
        && (linkMatrC[i2][j1 >> 3] & (1 << (j1 & 7))) == 0) {
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
    if ((linkMatrC[i1][j1 >> 3] & (1 << (j1 & 7)))
        || (linkMatrC[i2][j2 >> 3] & (1 << (j2 & 7))))
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

int network::exchange_linkC_degDiff(VVChar& linkMatrC, VNodeType& link,
    const VNodeType& p2pSize, LinkType count)
{
  const LinkType linkSize = link.size() / 2;
  if (linkSize < 2)
    return -1;
  while (count > 0) {
    LinkType ik
        = std::uniform_int_distribution<LinkType>(0, linkSize - 1)(rand2),
        jk = std::uniform_int_distribution<LinkType>(0, linkSize - 2)(rand2);
    if (jk >= ik)
      jk++;
    ik <<= 1;
    jk <<= 1;
    NodeType i1 = link[ik], i2 = link[ik | 1], j1 = link[jk],
             j2 = link[jk | 1];
    NodeType pi1 = p2pSize[i1], pi2 = p2pSize[i2], pj1 = p2pSize[j1],
             pj2 = p2pSize[j2];
    if (i1 == j2 || i2 == j1 || (pi1 <= pj1 && pj2 <= pi2)
        || (pj1 <= pi1 && pi2 <= pj2))
      continue;
    if ((pi2 <= pj1 || pj2 <= pi1)
        && (linkMatrC[i1][j1 >> 3] & (1 << (j1 & 7))) == 0
        && (linkMatrC[i2][j2 >> 3] & (1 << (j2 & 7))) == 0) {
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
    if ((linkMatrC[i1][j2 >> 3] & (1 << (j2 & 7))) == 0
        && (linkMatrC[i2][j1 >> 3] & (1 << (j1 & 7))) == 0) {
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

int network::exchange_link_deg_same(VVDistType& linkMatr, VNodeType& link,
    const VNodeType& p2pSize, LinkType count)
{
  const LinkType linkSize = link.size() / 2;
  if (linkSize < 2)
    return -1;
  while (count > 0) {
    LinkType ik
        = std::uniform_int_distribution<LinkType>(0, linkSize - 1)(rand2),
        jk = std::uniform_int_distribution<LinkType>(0, linkSize - 2)(rand2);
    if (jk >= ik)
      jk++;
    ik <<= 1;
    jk <<= 1;
    NodeType i1 = link[ik], i2 = link[ik | 1], j1 = link[jk],
             j2 = link[jk | 1];
    NodeType pi1 = p2pSize[i1], pi2 = p2pSize[i2], pj1 = p2pSize[j1],
             pj2 = p2pSize[j2];
    if (pi1 >= pj2 || pj1 >= pi2 || i1 == j1 || i2 == j2)
      continue;
    if (pi1 != pj1 && pi2 != pj2
        && ((pj1 < pi1 && pi2 < pj2) || (pi1 < pj1 && pj2 < pi2))
        && linkMatr[i1][j2] == 0 && linkMatr[i2][j1] == 0) {
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
    if (linkMatr[i1][j1] || linkMatr[i2][j2])
      continue;
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

int network::exchange_link_deg_diff(VVDistType& linkMatr, VNodeType& link,
    const VNodeType& p2pSize, LinkType count)
{
  const LinkType linkSize = link.size() / 2;
  if (linkSize < 2)
    return -1;
  while (count > 0) {
    LinkType ik
        = std::uniform_int_distribution<LinkType>(0, linkSize - 1)(rand2),
        jk = std::uniform_int_distribution<LinkType>(0, linkSize - 2)(rand2);
    if (jk >= ik)
      jk++;
    ik <<= 1;
    jk <<= 1;
    NodeType i1 = link[ik], i2 = link[ik | 1], j1 = link[jk],
             j2 = link[jk | 1];
    NodeType pi1 = p2pSize[i1], pi2 = p2pSize[i2], pj1 = p2pSize[j1],
             pj2 = p2pSize[j2];
    if (i1 == j2 || j1 == i2 || (pi1 <= pj1 && pj2 <= pi2)
        || (pj1 <= pi1 && pi2 <= pj2))
      continue;
    if ((pi2 <= pj1 || pj2 <= pi1) && linkMatr[i1][j1] == 0
        && linkMatr[i2][j2] == 0) {
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

int network::exchange_linkC_num_same(
    VVChar& linkMatrC, VNodeType& link, LinkType count)
{
  const LinkType linkSize = link.size();
  if (linkSize < 2)
    return -1;
  while (count > 0) {
    LinkType ik
        = std::uniform_int_distribution<LinkType>(0, linkSize - 1)(rand2),
        jk = std::uniform_int_distribution<LinkType>(0, linkSize - 2)(rand2);
    if (jk >= ik)
      jk++;
    ik <<= 1;
    jk <<= 1;
    NodeType i1 = link[ik], i2 = link[ik | 1], j1 = link[jk],
             j2 = link[jk | 1];
    if (i1 >= j2 || j1 >= i2 || i1 == j1 || i2 == j2)
      continue;
    if (((j1 < i1 && i2 < j2) || (i1 < j1 && j2 < i2))
        && (linkMatrC[i1][j2 >> 3] & (1 << (j2 & 7))) == 0
        && (linkMatrC[i2][j1 >> 3] & (1 << (j1 & 7))) == 0) {
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
    if ((linkMatrC[i1][j1 >> 3] & (1 << (j1 & 7)))
        || (linkMatrC[i2][j2 >> 3] & (1 << (j2 & 7))))
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

int network::exchange_linkC_num_diff(
    VVChar& linkMatrC, VNodeType& link, LinkType count)
{
  const LinkType linkSize = link.size();
  if (linkSize < 2)
    return -1;
  while (count > 0) {
    LinkType ik
        = std::uniform_int_distribution<LinkType>(0, linkSize - 1)(rand2),
        jk = std::uniform_int_distribution<LinkType>(0, linkSize - 2)(rand2);
    if (jk >= ik)
      jk++;
    ik <<= 1;
    jk <<= 1;
    NodeType i1 = link[ik], i2 = link[ik | 1], j1 = link[jk],
             j2 = link[jk | 1];
    if (i1 == j2 || j1 == i2 || (i1 <= j1 && j2 <= i2)
        || (j1 <= i1 && i2 <= j2))
      continue;
    if ((i1 > j2 || j1 > i2)
        && (linkMatrC[i1][j1 >> 3] & (1 << (j1 & 7))) == 0
        && (linkMatrC[i2][j2 >> 3] & (1 << (j2 & 7))) == 0) {
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
    if ((linkMatrC[i1][j2 >> 3] & (1 << (j2 & 7))) == 0
        && (linkMatrC[i2][j1 >> 3] & (1 << (j1 & 7))) == 0) {
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

int network::exchange_link_num_same(
    VVDistType& linkMatr, VNodeType& link, LinkType count)
{
  const LinkType linkSize = link.size();
  if (linkSize < 2)
    return -1;
  while (count > 0) {
    LinkType ik
        = std::uniform_int_distribution<LinkType>(0, linkSize - 1)(rand2),
        jk = std::uniform_int_distribution<LinkType>(0, linkSize - 2)(rand2);
    if (jk >= ik)
      jk++;
    ik <<= 1;
    jk <<= 1;
    NodeType i1 = link[ik], i2 = link[ik | 1], j1 = link[jk],
             j2 = link[jk | 1];
    if (i1 >= j2 || j1 >= i2 || i1 == j1 || i2 == j2)
      continue;
    if (((j1 < i1 && i2 < j2) || (i1 < j1 && j2 < i2))
        && linkMatr[i1][j2] == 0 && linkMatr[i2][j1] == 0) {
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
    if (linkMatr[i1][j1] || linkMatr[i2][j2])
      continue;
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

int network::exchange_link_num_diff(
    VVDistType& linkMatr, VNodeType& link, LinkType count)
{
  const LinkType linkSize = link.size();
  if (linkSize < 2)
    return -1;
  while (count > 0) {
    LinkType ik
        = std::uniform_int_distribution<LinkType>(0, linkSize - 1)(rand2),
        jk = std::uniform_int_distribution<LinkType>(0, linkSize - 2)(rand2);
    if (jk >= ik)
      jk++;
    ik <<= 1;
    jk <<= 1;
    NodeType i1 = link[ik], i2 = link[ik | 1], j1 = link[jk],
             j2 = link[jk | 1];
    if ((i1 <= j1 && j2 <= i2) || (j1 <= i1 && i2 <= j2) || i1 == j2
        || i2 == j1)
      continue;
    if ((i2 < j1 || j2 < i1) && linkMatr[i1][j1] == 0
        && linkMatr[i2][j2] == 0) {
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

int network::count_sameAdiff(LinkType& sum, LinkType& sum1, LinkType& sum3,
    LinkType& sum4, VLinkType& link, VNodeType& nodeDeg)
{
  const LinkType linkSize = link.size() / 2;
  sum = 0 /*同配*/;
  sum1 = 0 /*异配*/;
  sum3 = 0 /*3点相同*/;
  sum4 = 0 /*全同*/;
  for (LinkType l = 1; l < linkSize; l++) {
    NodeType i1 = link[l * 2], i2 = link[2 * l + 1];
    for (LinkType ll = 0; ll < l; ll++) {
      NodeType j1 = link[ll * 2], j2 = link[ll * 2 + 1];
      if (i1 == j1 || i1 == j2 || i2 == j1 || i2 == j2)
        continue;
      NodeType di1 = nodeDeg[i1], di2 = nodeDeg[i2], dj1 = nodeDeg[j1],
               dj2 = nodeDeg[j2];
      if (di1 == di2 || dj1 == dj2) { //有某边两端点度相同 i-i j-k
        if (di1 == di2 && dj1 == dj2) { //两边的两端点度分别相同 i-i j-j
          if (di1 == dj1)
            sum4++; //度全相同 i==j
          else
            sum++; // i!=j  同配
          continue;
        }
        if (di1 == dj1 || di2 == dj2) { //有3点度相同 i-i i-j
          sum3++;
          continue;
        }
        if (di1 > dj2 || dj1 > di2)
          sum++; // i-i,j-k : i<j<k || j<k<i
        else
          sum1++; // i-i,j-k: j<i<k
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

int network::rewire_rho(
    LinkType L, const double rho, VVNodeType& p2p, VNodeType& link)
{
  // const NodeType NodeSize = p2p.size();
  const LinkType LinkSize = link.size() / 2;
  uniform_int_distribution<long> ra(0, LinkSize - 1), ra2(0, LinkSize - 2);
  while (L > 0) {
    LinkType l = ra(rand2), l2 = l * 2;
    NodeType a1 = link[l2], a2 = link[l2 + 1], sa1 = p2p[a1].size(),
             sa2 = p2p[a2].size();

    LinkType m = ra2(rand2), m2;
    if (m >= l)
      ++m;
    m2 = m * 2;
    NodeType b1 = link[m2], b2 = link[m2 + 1], sb1 = p2p[b1].size(),
             sb2 = p2p[b2].size();

    if (sa1 == sb1 || sa2 == sb2) {
      if (sa1 == sa2 || sb1 == sb2)
        continue;
      swap(b1, b2);
      swap(sb1, sb2);
    }
    int disassortative_flag = (sa1 < sb1) ^ (sa2 < sb2);
    bool rewire_flag = (rho >= rand_double()) ^ disassortative_flag;
    if (!rewire_flag)
      continue;
    _ERR(change_p2p_link(p2p, a1, a2, b2));
    _ERR(change_p2p_link(p2p, a2, a1, b1));
    _ERR(change_p2p_link(p2p, b1, b2, a2));
    _ERR(change_p2p_link(p2p, b2, b1, a1));
    link[l2 + 1] = b2;
    link[m2] = b1;
    link[m2 + 1] = a2;
    --L;
  }
  return 0;
}

int network::rewire_rho_dir(
    LinkType L, const double rho, VVNodeType& p2p, VNodeType& link)
{
  const LinkType LinkSize = link.size() / 2;
  uniform_int_distribution<long> ra(0, LinkSize - 1), ra2(0, LinkSize - 2);
  while (L > 0) {
    LinkType l = ra(rand2), l2 = l * 2;
    NodeType a1 = link[l2], a2 = link[l2 + 1], sa1 = p2p[a1].size(),
             sa2 = p2p[a2].size();

    LinkType m = ra2(rand2), m2;
    if (m >= l)
      ++m;
    m2 = m * 2;
    NodeType b1 = link[m2], b2 = link[m2 + 1], sb1 = p2p[b1].size(),
             sb2 = p2p[b2].size();

    if (sa1 == sb1 || sa2 == sb2)
      continue;
    int disassortative_flag = (sa1 < sb1) ^ (sa2 < sb2);
    bool rewire_flag = (rho >= rand_double()) ^ disassortative_flag;
    if (!rewire_flag)
      continue;
    _ERR(change_p2p_link(p2p, a1, a2, b2));
    _ERR(change_p2p_link(p2p, b1, b2, a2));
    link[l2 + 1] = b2;
    link[m2 + 1] = a2;
    --L;
  }
  return 0;
}

int network::change_p2p_link(
    VVNodeType& p2p, const NodeType i1, const NodeType i2, const NodeType j2)
{
  int flag = -1;
  for (auto& i : p2p[i1])
    if (i == i2) {
      i = j2;
      flag = 0;
      break;
    }
  return flag;
}

// *************************************************************
bool cmp_RNodeType_start(const RNodeType& a, const RNodeType& b)
{
  return a.start < b.start;
}

bool cmp_RNodeType_end(const RNodeType& a, const RNodeType& b)
{
  return a.end < b.end;
}

int network::nodeDeg_update_nodeMap(
    VNodeType& nodeDeg, const VRNodeType& nodeMap)
{
  if (nodeDeg.size() != nodeMap.size())
    return -1;
  VNodeType t(nodeDeg.size());
  for (VRNodeTypeCItr i = nodeMap.begin(); i != nodeMap.end(); i++)
    t[i->end] = nodeDeg[i->start];
  swap(nodeDeg, t);
  return 0;
}

// *************************************************************
