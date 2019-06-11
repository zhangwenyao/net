#include "correlation2.h"
#ifdef STAT_CORRELATION2

#include "../../common/common.h"
#include <map>
#include <set>
using namespace std;
using namespace common;
using namespace network;

// ******************************************************
int correlation2::cal_correlation2_node(double& node, const VVNodeType& p2p)
{
  double sxy = 0, sx = 0, sx2 = 0;
  LinkType l = 0;
  node = 0;
  set<NodeType> nnodes;
  const NodeType nodeSize = p2p.size();
  for (NodeType i = 0; i < nodeSize; ++i) {
    nnodes.clear();
    for (auto j : p2p[i])
      if (j > i)
        nnodes.insert(j);
    const double x = p2p[i].size(), x2 = x * x, x2p = x * 2.0;
    for (auto const j : p2p[i]) {
      for (auto const k : p2p[j]) {
        if (k <= i || nnodes.find(k) != nnodes.end())
          continue;
        nnodes.insert(k);
        const double y = p2p[k].size();
        sxy += x2p * y;
        sx += x + y;
        sx2 += x2 + y * y;
        ++l;
      }
    }
    if (i % 10000 == 9999)
      INFORM(i + 1, "\t/ ", nodeSize);
  }
  if (l > 0)
    node = (2.0 * l * sxy - sx * sx) / (2.0 * l * sx2 - sx * sx);
  return 0;
}

int correlation2::cal_correlation2_node_spearman(double& node,
    const VVNodeType& p2p, const VNodeType& degArrVal,
    const VDouble& deg2ArrVal)
{
  double sxy = 0, sx = 0, sx2 = 0;
  LinkType l = 0;
  node = 0;
  set<NodeType> nnodes;
  const NodeType nodeSize = p2p.size(), degSize = degArrVal.size();
  map<NodeType, NodeType> degArrVal_map_no;
  for (NodeType i = 0; i < degSize; ++i)
    degArrVal_map_no[degArrVal[i]] = i;
  for (NodeType i = 0; i < nodeSize; ++i) {
    nnodes.clear();
    for (auto j : p2p[i])
      if (j > i)
        nnodes.insert(j);
    const double x = deg2ArrVal[degArrVal_map_no[p2p[i].size()]], x2 = x * x,
                 x2p = x * 2.0;
    for (auto const j : p2p[i]) {
      for (auto const k : p2p[j]) {
        if (k <= i || nnodes.find(k) != nnodes.end())
          continue;
        nnodes.insert(k);
        const double y = deg2ArrVal[degArrVal_map_no[p2p[k].size()]];
        sxy += x2p * y;
        sx += x + y;
        sx2 += x2 + y * y;
        ++l;
      }
    }
    if (i % 10000 == 9999)
      INFORM(i + 1, "\t/ ", nodeSize);
  }
  if (l > 0)
    node = (2.0 * l * sxy - sx * sx) / (2.0 * l * sx2 - sx * sx);
  return 0;
}

int correlation2::cal_correlation2_link(double& link, const VVNodeType& p2p)
{
  double sxy = 0, sx = 0, sx2 = 0;
  LinkType l = 0;
  link = 0;
  const NodeType nodeSize = p2p.size();
  vector<set<NodeType>> nodess(nodeSize);
  for (NodeType i = 0; i < nodeSize; ++i) {
    for (auto j : p2p[i])
      nodess[i].insert(j);
  }
  for (NodeType i = 0; i < nodeSize; ++i) {
    const NodeType deg_i = p2p[i].size();
    for (NodeType ij = 0; ij < deg_i; ++ij) {
      const NodeType j = p2p[i][ij];
      auto& nodes = nodess[j];
      const double x = p2p[j].size(), x2 = x * x, x2p = 2.0 * x;
      for (NodeType ik = ij + 1; ik < deg_i; ++ik) {
        const NodeType k = p2p[i][ik];
        if (k == j || nodes.find(k) != nodes.end())
          continue;
        const double y = p2p[k].size();
        sxy += x2p * y;
        sx += x + y;
        sx2 += x2 + y * y;
        ++l;
      }
    }
    if (i % 10000 == 9999)
      INFORM(i + 1, "\t/ ", nodeSize);
  }
  if (l > 0)
    link = (2.0 * l * sxy - sx * sx) / (2.0 * l * sx2 - sx * sx);
  return 0;
}

int correlation2::cal_correlation2_link_spearman(double& link,
    const VVNodeType& p2p, const VNodeType& degArrVal,
    const VDouble& deg2ArrVal)
{
  double sxy = 0, sx = 0, sx2 = 0;
  LinkType l = 0;
  link = 0;
  const NodeType nodeSize = p2p.size(), degSize = degArrVal.size();
  vector<set<NodeType>> nodess(nodeSize);
  map<NodeType, NodeType> degArrVal_map_no;
  for (NodeType i = 0; i < degSize; ++i)
    degArrVal_map_no[degArrVal[i]] = i;
  for (NodeType i = 0; i < nodeSize; ++i) {
    for (auto j : p2p[i])
      nodess[i].insert(j);
  }
  for (NodeType i = 0; i < nodeSize; ++i) {
    const NodeType deg_i = p2p[i].size();
    for (NodeType ij = 0; ij < deg_i; ++ij) {
      const NodeType j = p2p[i][ij];
      auto& nodes = nodess[j];
      const double x = deg2ArrVal[degArrVal_map_no[p2p[j].size()]],
                   x2 = x * x, x2p = x * 2.0;
      for (NodeType ik = ij + 1; ik < deg_i; ++ik) {
        const NodeType k = p2p[i][ik];
        if (k == j || nodes.find(k) != nodes.end())
          continue;
        const double y = deg2ArrVal[degArrVal_map_no[p2p[k].size()]];
        sxy += x2p * y;
        sx += x + y;
        sx2 += x2 + y * y;
        ++l;
      }
    }
    if (i % 10000 == 9999)
      INFORM(i + 1, "\t/ ", nodeSize);
  }
  if (l > 0)
    link = (2.0 * l * sxy - sx * sx) / (2.0 * l * sx2 - sx * sx);
  return 0;
}

// ******************************************************
int correlation2::cal_correlation2_node_k(VDouble& node_correlation2,
    VLinkType& node_correlation2_size, const VVNodeType& p2p,
    const VNodeType& degArrVal)
{
  const NodeType degSize = degArrVal.size(), nodeSize = p2p.size();
  VDouble sxy, sx, sx2;
  node_correlation2.assign(degSize, 0);
  node_correlation2_size.assign(degSize, 0);
  sxy.assign(degSize, 0);
  sx.assign(degSize, 0);
  sx2.assign(degSize, 0);
  map<NodeType, NodeType> degArrVal_map_no;
  for (NodeType i = 0; i < degSize; ++i)
    degArrVal_map_no[degArrVal[i]] = i;
  set<NodeType> nnodes;
  for (NodeType i = 0; i < nodeSize; ++i) {
    nnodes.clear();
    for (auto j : p2p[i])
      if (j > i)
        nnodes.insert(j);
    const double x = p2p[i].size(), x2 = x * x, x2p = x * 2.0;
    for (auto const j : p2p[i]) {
      const NodeType deg_j = p2p[j].size(), j_no = degArrVal_map_no[deg_j];
      for (auto const k : p2p[j]) {
        if (k <= i || nnodes.find(k) != nnodes.end())
          continue;
        nnodes.insert(k);
        const double y = p2p[k].size();
        sxy[j_no] += x2p * y;
        sx[j_no] += x + y;
        sx2[j_no] += x2 + y * y;
        ++node_correlation2_size[j_no];
      }
    }
    if (i % 10000 == 9999)
      INFORM(i + 1, "\t/ ", nodeSize);
  }
  for (NodeType i = 0; i < degSize; ++i) {
    if (node_correlation2_size[i] > 0)
      node_correlation2[i]
          = (2.0 * node_correlation2_size[i] * sxy[i] - sx[i] * sx[i])
          / (2.0 * node_correlation2_size[i] * sx2[i] - sx[i] * sx[i]);
  }
  return 0;
}

// ******************************************************
#endif // STAT_CORRELATION2
