#include "random.h"
#ifdef NET_RANDOM

#include "../../common/common.h"
using namespace std;
using namespace common;
using namespace network;

// ******************************************************
int network::random::addLink_linkMatr_proNode(VVDistType& linkMatr,
    LinkType& linkSize, const double p,
    const int dirFlag) // 所有点按概率p连边
{
  const NodeType nodeSize = linkMatr.size();
  linkMatr.resize(nodeSize);
  linkMatr[0].assign(nodeSize, 0);
  for (NodeType i = 1; i < nodeSize; i++)
    linkMatr[i] = linkMatr[0];
  if (dirFlag) {
    for (NodeType i = 0; i < nodeSize; i++)
      for (NodeType j = 0; j < nodeSize; j++)
        if (j != i || rand_double() < p) {
          linkMatr[i][j] = 1; // linkMatr[i][j] = 1;
          linkSize++;
        }
  } else {
    for (NodeType i = 1; i < nodeSize; i++)
      for (NodeType j = 0; j < i; j++)
        if (rand_double() < p) {
          linkMatr[i][j] = 1; // linkMatr[i][j] = 1;
          linkMatr[j][i] = 1; // linkMatr[j][i] = 1;
          linkSize++;
        }
  }
  return 0;
}

int network::random::addLink_linkMatrC_ranNode2(VVChar& linkMatrC,
    const VNodeType& nodeDeg, VNodeType& p2pSize, VNodeType& remNodeNum,
    LinkType& linkRemain,
    const LinkType tryCount) // 每次直接随机抽取两个点连边
{
  for (LinkType try0 = 0; linkRemain > 0 && remNodeNum.size() > 1;) {
    std::uniform_int_distribution<NodeType> dis(0, remNodeNum.size() - 1);
    NodeType ik = dis(rand2);
    NodeType i = remNodeNum[ik];
    if (p2pSize[i] >= nodeDeg[i]) {
      remNodeNum[ik] = remNodeNum.back();
      remNodeNum.pop_back();
      continue;
    }
    std::uniform_int_distribution<NodeType> dis2(0, remNodeNum.size() - 2);
    NodeType jk = dis2(rand2);
    if (jk >= ik)
      jk++;
    NodeType j = remNodeNum[jk];
    if (p2pSize[j] >= nodeDeg[j]) {
      remNodeNum[jk] = remNodeNum.back();
      remNodeNum.pop_back();
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
        remNodeNum[jk] = remNodeNum.back();
        remNodeNum.pop_back();
      }
      if (p2pSize[i] == nodeDeg[i]) {
        remNodeNum[ik] = remNodeNum.back();
        remNodeNum.pop_back();
      }
    } else {
      if (p2pSize[i] == nodeDeg[i]) {
        remNodeNum[ik] = remNodeNum.back();
        remNodeNum.pop_back();
      }
      if (p2pSize[j] == nodeDeg[j]) {
        remNodeNum[jk] = remNodeNum.back();
        remNodeNum.pop_back();
      }
    }
  }
  return (linkRemain <= 0 ? 0 : -1);
}

int network::random::addLink_linkMatr_ranNode2(VVDistType& linkMatr,
    const VNodeType& nodeDeg, VNodeType& p2pSize, VNodeType& remNodeNum,
    LinkType& linkRemain,
    const LinkType tryCount) // 每次直接随机抽取两个点连边
{
  for (LinkType try0 = 0; linkRemain > 0 && remNodeNum.size() > 1;) {
    std::uniform_int_distribution<NodeType> dis(0, remNodeNum.size() - 1);
    NodeType ik = dis(rand2);
    NodeType i = remNodeNum[ik];
    if (p2pSize[i] >= nodeDeg[i]) {
      remNodeNum[ik] = remNodeNum.back();
      remNodeNum.pop_back();
      continue;
    }
    std::uniform_int_distribution<NodeType> dis2(0, remNodeNum.size() - 2);
    NodeType jk = dis2(rand2);
    if (jk >= ik)
      jk++;
    NodeType j = remNodeNum[jk];
    if (p2pSize[j] >= nodeDeg[j]) {
      remNodeNum[jk] = remNodeNum.back();
      remNodeNum.pop_back();
      continue;
    }
    if (linkMatr[i][j >> 3] & (1 << (j & 7))) { // linkMatr[i][j] == 1
      if (++try0 >= tryCount)
        break;
      else
        continue;
    }
    linkMatr[i][j >> 3] ^= (1 << (j & 7)); // linkMatr[i][j] = 1;
    linkMatr[j][i >> 3] ^= (1 << (i & 7)); // linkMatr[j][i] = 1;
    p2pSize[i]++;
    p2pSize[j]++;
    linkRemain--;
    try0 = 0;
    if (ik < jk) {
      if (p2pSize[j] == nodeDeg[j]) {
        remNodeNum[jk] = remNodeNum.back();
        remNodeNum.pop_back();
      }
      if (p2pSize[i] == nodeDeg[i]) {
        remNodeNum[ik] = remNodeNum.back();
        remNodeNum.pop_back();
      }
    } else {
      if (p2pSize[i] == nodeDeg[i]) {
        remNodeNum[ik] = remNodeNum.back();
        remNodeNum.pop_back();
      }
      if (p2pSize[j] == nodeDeg[j]) {
        remNodeNum[jk] = remNodeNum.back();
        remNodeNum.pop_back();
      }
    }
  }
  return (linkRemain <= 0 ? 0 : -1);
}

int network::random::addLink_p2p_ranNode0(VVNodeType& p2p, VNodeType& link,
    const VNodeType& nodeDeg, VNodeType& remNodeNum, LinkType& linkRemain,
    const LinkType tryCount)
{
  for (LinkType try0 = 0; linkRemain > 0 && remNodeNum.size() > 1;) {
    std::uniform_int_distribution<NodeType> dis(0, remNodeNum.size() - 1);
    NodeType ik = dis(rand2), i;
    i = remNodeNum[ik];
    if (p2p[i].size() >= nodeDeg[i]) {
      remNodeNum[ik] = remNodeNum.back();
      remNodeNum.pop_back();
      continue;
    }
    std::uniform_int_distribution<NodeType> dis2(0, remNodeNum.size() - 2);
    NodeType jk = dis(rand2), j;
    if (jk >= ik)
      jk++;
    j = remNodeNum[jk];
    if (p2p[j].size() >= nodeDeg[j]) {
      remNodeNum[jk] = remNodeNum.back();
      remNodeNum.pop_back();
      continue;
    }
    NodeType t;
    if (p2p[i].size() > p2p[j].size()) {
      t = ik;
      ik = jk;
      jk = t;
      i = remNodeNum[ik];
      j = remNodeNum[jk];
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
        remNodeNum[jk] = remNodeNum.back();
        remNodeNum.pop_back();
      }
      if (p2p[i].size() == nodeDeg[i]) {
        remNodeNum[ik] = remNodeNum.back();
        remNodeNum.pop_back();
      }
    } else {
      if (p2p[i].size() == nodeDeg[i]) {
        remNodeNum[ik] = remNodeNum.back();
        remNodeNum.pop_back();
      }
      if (p2p[j].size() == nodeDeg[j]) {
        remNodeNum[jk] = remNodeNum.back();
        remNodeNum.pop_back();
      }
    }
  }
  return (linkRemain <= 0 ? 0 : -1);
}

int network::random::addLink_p2p_ranNode(VVNodeType& p2p,
    const VNodeType& nodeDeg, VNodeType& remNodeNum, LinkType& linkRemain,
    const LinkType tryCount)
{
  for (LinkType try0 = 0; linkRemain > 0 && remNodeNum.size() > 1;) {
    std::uniform_int_distribution<NodeType> dis(0, remNodeNum.size() - 1);
    NodeType ik = dis(rand2), i;
    i = remNodeNum[ik];
    if (p2p[i].size() >= nodeDeg[i]) {
      remNodeNum[ik] = remNodeNum.back();
      remNodeNum.pop_back();
      continue;
    }
    std::uniform_int_distribution<NodeType> dis2(0, remNodeNum.size() - 2);
    NodeType jk = dis2(rand2), j;
    if (jk >= ik)
      jk++;
    j = remNodeNum[jk];
    if (p2p[j].size() >= nodeDeg[j]) {
      remNodeNum[jk] = remNodeNum.back();
      remNodeNum.pop_back();
      continue;
    }
    NodeType t;
    if (p2p[i].size() > p2p[j].size()) {
      t = ik;
      ik = jk;
      jk = t;
      i = remNodeNum[ik];
      j = remNodeNum[jk];
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
        remNodeNum[jk] = remNodeNum.back();
        remNodeNum.pop_back();
      }
      if (p2p[i].size() == nodeDeg[i]) {
        remNodeNum[ik] = remNodeNum.back();
        remNodeNum.pop_back();
      }
    } else {
      if (p2p[i].size() == nodeDeg[i]) {
        remNodeNum[ik] = remNodeNum.back();
        remNodeNum.pop_back();
      }
      if (p2p[j].size() == nodeDeg[j]) {
        remNodeNum[jk] = remNodeNum.back();
        remNodeNum.pop_back();
      }
    }
  }
  return (linkRemain <= 0 ? 0 : -1);
}

int network::random::addLink_p2p_remDeg(VVNodeType& p2p,
    const VNodeType& nodeDeg, VNodeType& remNodeNum, LinkType& linkRemain,
    VNodeType& link, const LinkType tryCount)
{
  for (LinkType try0 = 0; linkRemain > 0 && remNodeNum.size() > 1;) {
    std::uniform_int_distribution<LinkType> dis(0, linkRemain * 2 - 1);
    std::uniform_int_distribution<LinkType> dis2(0, linkRemain * 2 - 2);
    LinkType ik = dis(rand2), jk;
    NodeType i = link[ik], j;
    do {
      jk = dis2(rand2);
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
      remNodeNum.pop_back();
    if (p2p[j].size() == nodeDeg[j])
      remNodeNum.pop_back();
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

int network::random::addLink_p2p_remDeg_dir(VVNodeType& p2p,
    const VNodeType& nodeDegOut, VNodeType& remNodeNum, LinkType& linkRemain,
    VNodeType& link, const LinkType tryCount)
{
  for (LinkType try0 = 0; linkRemain > 0;) {
    std::uniform_int_distribution<LinkType> dis(0, linkRemain - 1);
    LinkType ik = dis(rand2), jk = dis(rand2);
    NodeType i = link[ik * 2], j = link[jk * 2 + 1], k = 0;
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
    if (p2p[i].size() == nodeDegOut[i])
      remNodeNum[i] = 0;
    --linkRemain;
    try0 = 0;
    if (ik < linkRemain) {
      link[ik * 2] = link[linkRemain * 2];
      link[linkRemain * 2] = i;
    }
    if (jk < linkRemain) {
      link[jk * 2 + 1] = link[linkRemain * 2 + 1];
      link[linkRemain * 2 + 1] = j;
    }
  }
  return (linkRemain <= 0 ? 0 : -1);
}

int network::random::addLink_p2p_ranLink_lkkProb(VVNodeType& p2p,
    const VNodeType& nodeDeg, VVDouble& lkkProb, VNodeType& degArrNo,
    VNodeType& remNodeNum, LinkType& linkRemain, VNodeType& link,
    const LinkType tryCount)
{
  for (LinkType try0 = 0; linkRemain > 0 && remNodeNum.size() > 1;) {
    LinkType ik, jk;
    NodeType i, j;
    while (1) {
      std::uniform_int_distribution<LinkType> dis(0, linkRemain * 2 - 1),
          dis2(0, linkRemain * 2 - 2);
      ik = dis(rand2);
      i = link[ik];
      jk = dis2(rand2);
      if (jk >= ik)
        jk++;
      j = link[jk];
      if (i != j
          && rand_double()
              <= lkkProb[degArrNo[nodeDeg[i]]][degArrNo[nodeDeg[j]]])
        ;
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
      remNodeNum.pop_back();
    if (p2p[j].size() == nodeDeg[j])
      remNodeNum.pop_back();
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

int network::random::delLink_p2p_ranLink(VVNodeType& p2p,
    const VNodeType& nodeDeg, VNodeType& remNodeNum, LinkType& linkRemain,
    VNodeType& link, LinkType delCount)
{
  const LinkType linkSize = link.size() / 2;
  while (delCount > 0 && linkRemain < linkSize) {
    NodeType i, j;
    std::uniform_int_distribution<LinkType> dis(linkRemain, linkSize - 1);
    LinkType l = dis(rand2);
    i = link[l * 2];
    j = link[l * 2 + 1];
    if (p2p[i].size() == nodeDeg[i])
      remNodeNum.push_back(i);
    for (NodeType k = p2p[i].size(), *p = &p2p[i][0]; k > 0; p++, k--) {
      if (*p == j) {
        *p = p2p[i].back();
        p2p[i].pop_back();
        break;
      }
    }
    if (p2p[j].size() == nodeDeg[j])
      remNodeNum.push_back(j);
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

int network::random::delLink_p2p_ranLink_dir(VVNodeType& p2p,
    const VNodeType& nodeDegOut, VNodeType& remNodeNum, LinkType& linkRemain,
    VNodeType& link, LinkType delCount)
{
  const LinkType linkSize = link.size() / 2;
  while (delCount > 0 && linkRemain < linkSize) {
    NodeType i, j;
    std::uniform_int_distribution<LinkType> dis(linkRemain, linkSize - 1);
    LinkType l = dis(rand2);
    i = link[l * 2];
    j = link[l * 2 + 1];
    if (p2p[i].size() == nodeDegOut[i])
      remNodeNum[i] = 1;
    for (auto& k : p2p[i]) {
      if (k == j) {
        k = p2p[i].back();
        p2p[i].pop_back();
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

int network::random::delLink_linkMatrC_ranNode(VVChar& linkMatrC,
    const NodeType nodeSize, const VNodeType& nodeDeg, VNodeType& p2pSize,
    VNodeType& remNodeNum, LinkType& linkRemain, const LinkType linkSize,
    LinkType delCount) // 随机选点删边
{
  while (delCount > 0 && linkRemain < linkSize) {
    NodeType i;
    std::uniform_int_distribution<NodeType> dis(0, nodeSize - 1);
    do {
      i = dis(rand2);
    } while (p2pSize[i] <= 0);
    NodeType j;
    std::uniform_int_distribution<NodeType> dis2(0, nodeSize - 2);
    do {
      j = dis2(rand2);
      if (j >= i)
        j++;
    } while (p2pSize[j] <= 0);
    if (linkMatrC[i][j >> 3] & (1 << (j & 7))) { // linkMatr[i][j] == 1
      linkMatrC[i][j >> 3] ^= (1 << (j & 7));    // linkMatr[i][j] = 0
      linkMatrC[j][i >> 3] ^= (1 << (i & 7));    // linkMatr[j][i] = 0
      if (p2pSize[i]-- == nodeDeg[i])
        remNodeNum.push_back(i);
      if (p2pSize[j]-- == nodeDeg[j])
        remNodeNum.push_back(j);
      linkRemain++;
      delCount--;
    }
  }
  return (delCount > 0 ? -1 : 0);
}

int network::random::delLink_p2p_ranNode(VVNodeType& p2p,
    const NodeType nodeSize, const VNodeType& nodeDeg, VNodeType& remNodeNum,
    LinkType& linkRemain, const LinkType linkSize,
    LinkType delCount) // 随机选点删边
{
  while (delCount > 0 && linkRemain < linkSize) {
    NodeType i;
    std::uniform_int_distribution<NodeType> dis(0, nodeSize - 1);
    do {
      i = dis(rand2);
    } while (p2p[i].size() <= 0);
    NodeType j;
    std::uniform_int_distribution<NodeType> dis2(0, nodeSize - 2);
    do {
      j = dis2(rand2);
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
      remNodeNum.push_back(i);
    if (p2p[j].size() == nodeDeg[j])
      remNodeNum.push_back(j);
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

int network::random::delLink_p2p_ranNode1(VVNodeType& p2p,
    const NodeType nodeSize, const VNodeType& nodeDeg, VNodeType& remNodeNum,
    LinkType& linkRemain, const LinkType linkSize,
    LinkType delCount) // 随机选点再选边删除
{
  while (delCount > 0 && linkRemain < linkSize) {
    NodeType i;
    std::uniform_int_distribution<NodeType> dis(0, nodeSize - 1);
    do {
      i = dis(rand2);
    } while (p2p[i].size() <= 0);
    std::uniform_int_distribution<NodeType> dis2(0, p2p[i].size() - 1);
    NodeType k = dis2(rand2), j;
    j = p2p[i][k];
    if (p2p[i].size() == nodeDeg[i])
      remNodeNum.push_back(i);
    if (p2p[j].size() == nodeDeg[j])
      remNodeNum.push_back(j);
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

// ******************************************************
#endif // NET_RANDOM
