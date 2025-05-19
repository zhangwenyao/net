#ifndef MODEL__SPEARMAN__SPEARMAN_H_
#define MODEL__SPEARMAN__SPEARMAN_H_
#include "../../network/net.h"
#if defined(NET_SPEARMAN) && defined(STAT_SPEARMAN)

namespace network {
namespace spearman {
  // ******************************************************
  int network_guass(const NodeType M, const NodeType M0,
      const NodeType nodeSize, VVNodeType& p2p, NodeType& kMin,
      NodeType& kMax); // 生成网络
}
}
#endif // NET_SPEARMAN
#endif // _H
