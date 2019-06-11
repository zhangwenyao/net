#ifndef STATISTICS__CORRELATION2__CORRELATION2_H_
#define STATISTICS__CORRELATION2__CORRELATION2_H_
#include "../../network/net.h"
#ifdef STAT_CORRELATION2

namespace network {
namespace correlation2 {
  // ******************************************************
  int cal_correlation2_node(double& node, const VVNodeType& p2p);
  int cal_correlation2_node_spearman(double& node, const VVNodeType& p2p,
      const VNodeType& degArrVal, const VDouble& deg2ArrVal);
  int cal_correlation2_link(double& link, const VVNodeType& p2p);
  int cal_correlation2_link_spearman(double& link, const VVNodeType& p2p,
      const VNodeType& degArrVal, const VDouble& deg2ArrVal);
  int cal_correlation2_node_k(VDouble& node_correlation2,
      VLinkType& node_correlation2_size, const VVNodeType& p2p,
      const VNodeType& degArrVal);
}
}

// ******************************************************
#endif // STAT_CORRELATION2
#endif // STAT_CORRELATION2_H
