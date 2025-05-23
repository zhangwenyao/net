#include "betweenness.h"
#ifdef STAT_BETWEENNESS

#include "../../common/common.h"
using namespace std;
using namespace common;
using namespace network;

// ******************************************************
int network::betweenness::cal_betweenness0(
    VDouble &betwNode, VVDouble &betwEdge, double &meanNode, double &meanEdge,
    VVDistType &minDistMatr, VDouble &minDistMean, const VVNodeType &p2p,
    const VVNodeType &p2pIn) {
  if (p2p.size() <= 0 || p2pIn.size() <= 0) {
    ERROR();
    return -1;
  }

  const NodeType nodeSize =
      p2p.size() >= p2pIn.size() ? p2p.size() : p2pIn.size();
  betwNode.assign(nodeSize, 0);
  meanNode = 0;
  betwEdge.assign(nodeSize, VDouble(nodeSize, 0));
  meanEdge = 0;
  minDistMatr.resize(nodeSize, VDistType(nodeSize, 0));
  minDistMean.assign(nodeSize, 0);
  if (nodeSize < 2) return 0;

  VDistType d(nodeSize);
  VNodeType nodeStk(nodeSize);
  VLinkType wayNum(nodeSize);  // i到j最短路径的数目
  VDouble b(nodeSize);         // i节点出发的介数
  NodeType stk_end, stk_head;
  for (NodeType i = 0; i < nodeSize; i++) {  // 计算从i节点出发的最短路径、介数
    // 广度搜索算法，计算最短距离、最短路径路径数目，按距离存储编号nodeStk数组中
    if (p2p[i].size() <= 0) {
      minDistMatr[i].assign(nodeSize, 0);
      continue;
    }
    d.assign(nodeSize, DistMax);  // 最短距离
    d[i] = 0;
    wayNum.assign(nodeSize, 0);
    wayNum[i] = 1;
    nodeStk[0] = i;
    stk_head = 0;
    stk_end = 1;
    while (stk_head != stk_end) {
      NodeType iTmp = nodeStk[stk_head];
      for (VNodeTypeCItr itr = p2p[iTmp].begin(); itr != p2p[iTmp].end();
           ++itr) {
        NodeType j = *itr;
        if (d[j] == DistMax) {
          d[j] = d[iTmp] + 1;
          wayNum[j] = wayNum[iTmp];
          nodeStk[stk_end++] = j;
        } else if (d[j] > d[iTmp]) {
          wayNum[j] += wayNum[iTmp];
        }
      }
      stk_head++;
    }
    minDistMatr[i] = d;
    for (VDistTypeItr t = minDistMatr[i].begin(); t != minDistMatr[i].end();
         t++)
      if (*t == DistMax) *t = 0;
    if (stk_end > 1) {
      for (NodeType t = 1; t < stk_end; t++) minDistMean[i] += d[nodeStk[t]];
      minDistMean[i] /= (stk_end - 1);
    }

    // 计算i节点出发的介数
    b.assign(nodeSize, 0);  // 介数
    while (stk_end-- > 0) {
      NodeType jTmp = nodeStk[stk_end];
      DistType dTmp = d[jTmp];
      if (jTmp != i) betwNode[jTmp] += b[jTmp];  // 累计介数
      b[jTmp] += 1;
      double t = b[jTmp] / wayNum[jTmp];
      for (VNodeTypeCItr itr = p2pIn[jTmp].begin(); itr != p2pIn[jTmp].end();
           itr++) {
        if (d[*itr] < dTmp) {
          double t2 = wayNum[*itr] * t;
          b[*itr] += t2;
          betwEdge[*itr][jTmp] += t2;
        }
      }
    }
  }

  // 归一化、统计介数
  if (nodeSize > 1) {
    double linkSize = 0;
    for (auto &p : p2p) linkSize += p.size();
    double t = 1. / nodeSize / (nodeSize - 1);
    for (NodeType i = 0; i < nodeSize; i++) {
      for (NodeType j = 0; j < nodeSize; j++)
        if (j != i) meanEdge += betwEdge[i][j] *= t;
      meanEdge /= linkSize;
    }
  }
  if (nodeSize > 2) {
    double t = 1. / (nodeSize - 1) / (nodeSize - 2);
    for (NodeType i = 0; i < nodeSize; i++) meanNode += betwNode[i] *= t;
    meanNode /= nodeSize;
  }

  return 0;
}

inline unsigned long link_key(const unsigned long x, const unsigned long y) {
  return x <= y ? (x << 32 | y) : (y << 32 | x);
}
int network::betweenness::cal_betweenness0_large(
    VDouble &betwNode, VDouble &betwLink, double &meanNode, double &meanEdge,
    VDouble &minDistMean, const VVNodeType &p2p, const VVNodeType &p2pIn,
    const VNodeType &link) {
  if (p2p.size() <= 0 || p2pIn.size() <= 0) {
    ERROR();
    return -1;
  }

  const NodeType nodeSize =
      p2p.size() >= p2pIn.size() ? p2p.size() : p2pIn.size();
  const LinkType linkSize = link.size() / 2;
  betwNode.assign(nodeSize, 0);
  meanNode = 0;
  betwLink.assign(linkSize, 0);
  meanEdge = 0;
  minDistMean.assign(nodeSize, 0);
  if (nodeSize < 2) return 0;

  unordered_map<unsigned long, LinkType> linkID;
  for (LinkType i = 0, p = 0; i < linkSize; i++) {
    NodeType x = link[p++];
    NodeType y = link[p++];
    linkID[link_key(x, y)] = i;
  }

#pragma omp parallel for reduction(+ : betwNode, betwLink)
  for (NodeType i = 0; i < nodeSize; i++) {  // 计算从i节点出发的最短路径、介数
    if (i % 1000 == 0) INFORM(i);
    // 广度搜索算法，计算最短距离、最短路径路径数目，按距离存储编号nodeStk数组中
    if (p2p[i].size() <= 0) {
      continue;
    }
    VDistType d(nodeSize, DistMax);  // 最短距离
    VNodeType nodeStk(nodeSize);
    VLinkType wayNum(nodeSize);  // i到j最短路径的数目
    NodeType stk_end, stk_head;
    d[i] = 0;
    wayNum.assign(nodeSize, 0);
    wayNum[i] = 1;
    nodeStk[0] = i;
    stk_head = 0;
    stk_end = 1;
    while (stk_head != stk_end) {
      NodeType iTmp = nodeStk[stk_head];
      for (VNodeTypeCItr itr = p2p[iTmp].begin(); itr != p2p[iTmp].end();
           ++itr) {
        NodeType j = *itr;
        if (d[j] == DistMax) {
          d[j] = d[iTmp] + 1;
          wayNum[j] = wayNum[iTmp];
          nodeStk[stk_end++] = j;
        } else if (d[j] > d[iTmp]) {
          wayNum[j] += wayNum[iTmp];
        }
      }
      stk_head++;
    }
    if (stk_end > 1) {
      for (NodeType t = 1; t < stk_end; t++) minDistMean[i] += d[nodeStk[t]];
      minDistMean[i] /= (stk_end - 1);
    }

    // 计算i节点出发的介数
    VDouble b(nodeSize, 0);  // i节点出发的介数
    while (stk_end-- > 0) {
      NodeType jTmp = nodeStk[stk_end];
      DistType dTmp = d[jTmp];
      if (jTmp != i) betwNode[jTmp] += b[jTmp];  // 累计介数
      b[jTmp] += 1;
      double t = b[jTmp] / wayNum[jTmp];
      for (auto i2 : p2pIn[jTmp]) {
        if (d[i2] < dTmp) {
          double t2 = wayNum[i2] * t;
          b[i2] += t2;
          betwLink[linkID[link_key(i2, jTmp)]] += t2;
        }
      }
    }
  }

  // 归一化、统计介数
  if (nodeSize > 1) {
    double t = 1. / nodeSize / (nodeSize - 1);
    for (auto &be : betwLink) meanEdge += be *= t;
    meanEdge /= linkSize;
  }
  if (nodeSize > 2) {
    double t = 1. / (nodeSize - 1) / (nodeSize - 2);
    for (NodeType i = 0; i < nodeSize; i++) meanNode += betwNode[i] *= t;
    meanNode /= nodeSize;
  }

  return 0;
}

// ******************************************************
int network::betweenness::cal_betweenness(
    VDouble &betwNode, VVDouble &betwEdge, double &meanNode, double &meanEdge,
    VVDistType &minDistMatr, VDouble &minDistMean, const VVNodeType &p2p,
    const VVNodeType &p2pIn, const VVDistType &linkMatr) {
  if (p2p.size() <= 0 || p2pIn.size() <= 0 || linkMatr.size() <= 0 ||
      linkMatr.size() != p2p.size()) {
    ERROR();
    return -1;
  }

  const NodeType nodeSize = linkMatr.size();
  betwNode.assign(nodeSize, 0);
  meanNode = 0;
  betwEdge.assign(nodeSize, VDouble(nodeSize, 0));
  meanEdge = 0;
  minDistMatr.resize(nodeSize, VDistType(nodeSize, 0));
  minDistMean.assign(nodeSize, 0);
  if (nodeSize < 2) return 0;

  VNodeType nodeStk(nodeSize),
      stkNum(
          nodeSize);  // nodeStk:按与节点i距离排序的节点j编号的堆栈，stkNum:j在堆栈中的位置
  VDistType d(nodeSize);                     // d:i-j最短距离
  VLinkType wayNum(nodeSize);                // i到j最短路径的数目
  VDouble b(nodeSize);                       // i节点出发的介数
  for (NodeType i = 0; i < nodeSize; i++) {  // 计算从i节点出发的最短路径、介数
    if (p2p[i].size() <= 0) {
      minDistMatr[i].assign(nodeSize, 0);
      continue;
    }
    // 初始化d、wayNum
    d.assign(nodeSize, DistMax);
    d[i] = 0;
    wayNum.assign(nodeSize, 0);
    wayNum[i] = 1;
    // 初始化nodeStk、stkNum
    for (NodeType j = 1; j < nodeSize; j++) nodeStk[j] = j;
    nodeStk[0] = i;
    nodeStk[i] = 0;
    // common_sort_p_val(&nodeStk[1], &nodeStk[nodeSize - 1], &linkMatr[i][0]);
    for (NodeType j = 0; j < nodeSize; j++) stkNum[nodeStk[j]] = j;

    // 广度搜索算法，计算最短距离、最短路径的路径数目
    DistType dii = 0;
    NodeType stk_end = 1;
    for (NodeType stk_head = 0; stk_head != stk_end; ++stk_head) {
      NodeType ii = nodeStk[stk_head];
      if (dii < d[ii]) {
        dii = d[ii];
      }
      for (VNodeTypeCItr itr = p2p[ii].begin(); itr != p2p[ii].end(); itr++) {
        NodeType j = *itr, jNum = stkNum[j];
        if (jNum <= stk_head) continue;
        if (jNum >= stk_end || d[j] > dii + linkMatr[ii][j]) {
          // d[j]变小，同步更新nodeStk、stkNum
          d[j] = dii + linkMatr[ii][j];
          wayNum[j] = wayNum[ii];
          if (jNum >= stk_end) {
            if (jNum > stk_end) {
              nodeStk[jNum] = nodeStk[stk_end];
              stkNum[nodeStk[stk_end]] = jNum;
              nodeStk[stk_end] = j;
              stkNum[j] = stk_end;
            }
            stk_end++;
          }
          for (NodeType t = stk_end - 2, jj; t > stk_head; --t) {
            jj = nodeStk[t];
            if (d[jj] <= d[j]) {
              if (jNum != t) {
                nodeStk[t] = j;
                stkNum[j] = t;
              }
              break;
            }
            nodeStk[t + 1] = jj;
            ++stkNum[jj];
          }
        } else if (d[j] == dii + linkMatr[ii][j]) {
          wayNum[j] += wayNum[ii];
        }
      }
    }
    minDistMatr[i] = d;
    for (VDistTypeItr t = minDistMatr[i].begin(); t != minDistMatr[i].end();
         t++)
      if (*t == DistMax) *t = 0;
    if (stk_end > 1) {
      for (NodeType t = 1; t < stk_end; ++t) minDistMean[i] += d[nodeStk[t]];
      minDistMean[i] /= (stk_end - 1);
    }

    // 计算i节点出发的介数
    b.assign(nodeSize, 0);  // 介数
    while (stk_end-- > 0) {
      NodeType jTmp = nodeStk[stk_end];
      DistType dTmp = d[jTmp];
      if (jTmp != i) betwNode[jTmp] += b[jTmp];  // 累计介数
      b[jTmp] += 1;
      double t = b[jTmp] / wayNum[jTmp];
      for (VNodeTypeCItr itr = p2pIn[jTmp].begin(); itr != p2pIn[jTmp].end();
           itr++) {
        if (d[*itr] + linkMatr[*itr][jTmp] == dTmp) {  // *itr--jTmp在最短路径上
          double t2 = wayNum[*itr] * t;
          b[*itr] += t2;
          betwEdge[*itr][jTmp] += t2;
        }
      }
    }
  }

  // 归一化、统计介数
  if (nodeSize > 1) {
    double t = 1. / nodeSize / (nodeSize - 1), linkSize = 0;
    for (auto p : p2p) linkSize += p.size();
    for (NodeType i = 0; i < nodeSize; i++)
      for (NodeType j = 0; j < nodeSize; j++)
        if (j != i) meanEdge += betwEdge[i][j] *= t;
    meanEdge /= linkSize;
  }
  if (nodeSize > 2) {
    double t = 1. / (nodeSize - 1) / (nodeSize - 2);
    for (NodeType i = 0; i < nodeSize; i++) meanNode += betwNode[i] *= t;
    meanNode /= nodeSize;
  }

  return 0;
}

// ******************************************************
#endif  // STAT_BETWEENNESS
