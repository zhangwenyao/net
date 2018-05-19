#include "NetBA.h"
#ifdef NET_BA

#include "common.h"
using namespace std;

// ******************************************************
int BA_new(const NodeType M, const NodeType M0, const NodeType nodeSize,
    VVNodeType& p2p, NodeType& kMin, NodeType& kMax)
{
  if (M <= 0 || M0 < M || nodeSize < M0)
    return -1;
  p2p.resize(nodeSize);

  // 全连通子网络
  VVNodeTypeItr itr = p2p.begin();
  for (NodeType i = 0; i < M0; i++, itr++) {
    itr->resize(0);
    itr->reserve(M0 - 1);
  }
  for (NodeType i = M0; i < nodeSize; i++, itr++) {
    itr->resize(0);
    itr->reserve(M);
  }
  for (NodeType i = 1; i < M0; i++) {
    for (NodeType j = 0; j < i; j++) {
      p2p[i].push_back(j);
      p2p[j].push_back(i);
    }
  }

  kMin = M;
  kMax = M0 - 1;
  VNodeType tmp(nodeSize);
  for (NodeType i = 0; i < nodeSize; i++)
    tmp[i] = i;                              // 已连边的节点编号
  for (NodeType i = M0; i < nodeSize; i++) { // 按正比于度大小的概率随机连边
    for (NodeType j = 0; j < M; j++) {
      NodeType k, t;
      std::uniform_int_distribution<NodeType> dis(j, i - 1);
      std::uniform_int_distribution<NodeType> dis2(0, kMax - 1);
      do {
        k = dis(rand2);                       // 抽出前面第k个节点
        t = tmp[k];                           // 第k个节点的编号为t
      } while (dis2(rand2) >= p2p[t].size()); // 与最大度比较，按概率选取
      // 连接选中的节点t，并放到前面第j个位置
      tmp[k] = tmp[j];
      tmp[j] = t;
      p2p[t].push_back(i);
      p2p[i].push_back(t);
      if (p2p[t].size() > kMax)
        kMax = p2p[t].size();
    }
  }
  return 0;
}

// ******************************************************
NodeType BA_get_distance(const NodeType ni, const NodeType nj,
    const NodeType nodeSize, const VVNodeType& p2p)
{
  static VNodeType tmp;
  if (ni >= nodeSize || nj >= nodeSize)
    return nodeSize;
  if (ni == nj)
    return 0;
  if (BA_get_shortPath(tmp, ni, nj, nodeSize, p2p) != 0)
    return nodeSize;
  return tmp.size() - 1;
}

inline int BA_get_path(VNodeType& path, const NodeType ni, const NodeType nj,
    const NodeType nodeSize, const VVNodeType& p2p)
{
  return BA_get_shortPath(path, ni, nj, nodeSize, p2p);
}

int BA_get_shortPath(VNodeType& path, const NodeType ni, const NodeType nj,
    const NodeType nodeSize, const VVNodeType& p2p)
{
  static VNodeType tmp_d, tmp_stk, tmp_source; // 距离，访问过的节点，源

  if (ni >= nodeSize || nj >= nodeSize) {
    path.clear();
    return -1;
  }
  if (ni == nj) {
    path.assign(1, ni);
    return 0;
  }

  tmp_stk.assign(1, ni);
  tmp_d.assign(nodeSize, nodeSize);
  tmp_source.resize(nodeSize);
  tmp_d[ni] = 0;
  for (NodeType now = 0; now < tmp_stk.size(); now++) { // 广度搜索
    NodeType ti = tmp_stk[now], dj = tmp_d[ti] + 1;
    for (VNodeTypeCItr itr = p2p[ti].begin(); itr != p2p[ti].end();
         itr++) { // 逐个标记ti的邻居tj的距离
      NodeType tj = *itr;
      if (tmp_d[tj] > dj) {
        tmp_d[tj] = dj;
        tmp_source[tj] = ti;
        if (tj == nj) {
          tmp_stk.clear();
          break;
        }
        tmp_stk.push_back(tj);
      }
    }
  }
  NodeType dj = tmp_d[nj];
  if (dj == nodeSize) { // 找不到路径
    path.clear();
    return -1;
  }
  path.resize(dj + 1);
  path[dj] = nj;
  for (NodeType j = dj; j > 0; j--) { //从nj倒着回溯源ni得到路径
    NodeType tj = path[j];
    path[j - 1] = tmp_source[tj];
  }

  return 0;
}

NodeType BA_get_maxDistance(const NodeType nodeSize)
{
  if (nodeSize <= 0)
    return 0;
  return nodeSize - 1;
}
// ******************************************************

#endif // NET_BA
