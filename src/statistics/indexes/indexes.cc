#include "indexes.h"
#ifdef STAT_INDEXES

#include "../../common/common.h"
using namespace std;
using namespace common;
using namespace network;

// ******************************************************
typedef unordered_map<NodeType, NodeType> FatherType;
NodeType get_father(FatherType &father, const NodeType i) {
  return father[i] == i ? i : (father[i] = get_father(father, father[i]));
}
bool merge(FatherType &father, FatherType &sizes, NodeType i, NodeType j) {
  if (i > j) swap(i, j);
  NodeType fi = get_father(father, i), fj = get_father(father, j);
  if (fi != fj) {
    if (sizes[i] >= sizes[j]) {
      father[fj] = fi;
      sizes[fi] += sizes[fj];
      sizes[fj] = 0;
    } else {
      father[fi] = fj;
      sizes[fj] += sizes[fi];
      sizes[fi] = 0;
    }
    return true;
  } else {
    return false;
  }
}
int network::indexes::cal_local_index1(VLinkType &local_index1,
                                       VNodeType &neibor_communities,
                                       const VVNodeType &p2p) {
  _ERR(p2p.size() <= 0);
  const NodeType nodeSize = p2p.size();
  local_index1.assign(nodeSize, 0);
  neibor_communities.assign(nodeSize, 0);
  FatherType father, nodes;
  unordered_set<NodeType> communities;
  for (NodeType i = 0; i < nodeSize; i++) {
    // init
    father.clear();
    nodes.clear();
    for (auto j : p2p[i]) {
      father[j] = j;
      nodes[j] = 1;
    }
    // merge
    for (auto j : p2p[i]) {
      for (auto k : p2p[j]) {
        if (!father.count(k)) continue;
        merge(father, nodes, j, k);
      }
    }
    // communities
    communities.clear();
    for (auto j : p2p[i]) communities.insert(get_father(father, j));
    neibor_communities[i] = communities.size();
    // local_index1
    for (auto c : communities) {
      local_index1[i] += nodes[c] * nodes[c];
    }
  }
  return EXIT_SUCCESS;
}

int network::indexes::cal_local_index2(VLinkType &local_index2,
                                       VNodeType &neibor2_numbers,
                                       VNodeType &neibor2_communities,
                                       const VVNodeType &p2p) {
  _ERR(p2p.size() <= 0);
  const NodeType nodeSize = p2p.size();
  local_index2.assign(nodeSize, 0);
  neibor2_numbers.assign(nodeSize, 0);
  neibor2_communities.assign(nodeSize, 0);
  FatherType father, nodes, degrees;
  for (NodeType i = 0; i < nodeSize; i++) {
    // init
    father.clear();
    nodes.clear();
    NodeType merged = 0;
    for (auto j : p2p[i]) {
      father[j] = j;
      nodes[j] = 1;
      for (auto k : p2p[j]) {
        if (k == i || father.count(k)) continue;
        father[k] = k;
        nodes[k] = 1;
        merged += merge(father, nodes, j, k);
      }
    }
    neibor2_numbers[i] = father.size();
    // merge
    for (auto it : father) {
      if (merged + 1 >= father.size()) break;
      auto j = it.first;
      for (auto k : p2p[j]) {
        if (merged + 1 >= father.size()) break;
        if (!father.count(k)) continue;
        merged += merge(father, nodes, j, k);
      }
    }
    neibor2_communities[i] = neibor2_numbers[i] - merged;
    // degrees
    degrees.clear();
    for (auto j : p2p[i]) {
      auto fj = get_father(father, j);
      degrees[fj]++;
    }
    // local_index1
    for (auto it : degrees) {
      local_index2[i] += degrees[it.second] * nodes[it.first];
    }
  }
  return EXIT_SUCCESS;
}

// ******************************************************
#endif  // STAT_INDEXES
