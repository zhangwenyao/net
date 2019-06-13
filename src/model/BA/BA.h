#ifndef MODEL__BA__BA_H_
#define MODEL__BA__BA_H_
#include "../../network/net.h"
#ifdef NET_BA

namespace network {
namespace ba {
  // ******************************************************
  int BA_new(const NodeType M, const NodeType M0, const NodeType nodeSize,
      VVNodeType& p2p, NodeType& kMin, NodeType& kMax); // 生成BA网络
  int BA_new(const NodeType M, const NodeType M0, const NodeType nodeSize,
      VVNodeType& p2p, VNodeType& link, NodeType& kMin, NodeType& kMax);

  NodeType BA_get_distance(const NodeType ni, const NodeType nj,
      const NodeType nodeSize, const VVNodeType& p2p);
  int BA_get_shortPath(VNodeType& path, const NodeType ni, const NodeType nj,
      const NodeType nodeSize,
      const VVNodeType& p2p); // 两点间路径
  int BA_get_shortPath(VNodeType& path, const NodeType ni, const NodeType nj,
      const NodeType nodeSize,
      const VVNodeType& p2p); // 两点间最短路径
  NodeType BA_get_maxDistance(const NodeType nodeSize); // 网络两点间最大距离

  // ******************************************************
}
}
#endif // NET_BA
#endif // NET_BA_H
