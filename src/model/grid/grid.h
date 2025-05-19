#ifndef MODEL__GRID__GRID_H_
#define MODEL__GRID__GRID_H_
#include "../../network/net.h"
#ifdef NET_GRID

namespace network {
namespace grid {
  // ******************************************************
  int Grid_new(const NodeType NX, const NodeType NY, NodeType& kMin,
      NodeType& kMax, NodeType& nodeSize,
      VVNodeType& p2p); // 生成格点网络
  int Grid_check(const NodeType NX, const NodeType NY,
      const NodeType nodeSize,
      const VVNodeType& p2p); // 检查格点网络
  NodeType Grid_get_distance(const NodeType ni, const NodeType nj,
      const NodeType NX,
      const NodeType NY); // 两点间的距离
  int Grid_get_path(VNodeType& path, const NodeType ni, const NodeType nj,
      const NodeType nodeSize, const VVNodeType& p2p, const NodeType NX,
      const NodeType NY); // 两点间的路径
  int Grid_get_shortPath(VNodeType& path, const NodeType ni,
      const NodeType nj, const NodeType nodeSize, const VVNodeType& p2p,
      const NodeType NX,
      const NodeType NY); // 两点间的最短路径
  NodeType Grid_get_maxDistance(const NodeType NX,
      const NodeType NY); // 格点网络两点间的最大距离

  // ******************************************************
}
}
#endif // NET_GRID
#endif // NET_GRID_H
