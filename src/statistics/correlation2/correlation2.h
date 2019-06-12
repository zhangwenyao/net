#ifndef STATISTICS__CORRELATION2__CORRELATION2_H_
#define STATISTICS__CORRELATION2__CORRELATION2_H_
#include "../../network/net.h"
#ifdef STAT_CORRELATION2

//#define STAT_CORRELATION2_LINK

namespace network {
namespace correlation2 {
  // ******************************************************
  int cal_correlation2_node(double& node, const VVNodeType& p2p);
  int cal_correlation2_node_spearman(double& node_spearman,
      const VVNodeType& p2p, const VNodeType& degArrVal,
      const VDouble& deg2ArrVal);
  int cal_correlation2_link(double& link, const VVNodeType& p2p);
  int cal_correlation2_link_spearman(double& link_spearman,
      const VVNodeType& p2p, const VNodeType& degArrVal,
      const VDouble& deg2ArrVal);
  int cal_correlation2_node_k(VDouble& node_correlation2,
      VLinkType& node_correlation2_size, const VVNodeType& p2p,
      const VNodeType& degArrVal);
  int cal_correlation2_node_spearman_k(VDouble& node_correlation2_spearman,
      VLinkType& node_correlation2_size, const VVNodeType& p2p,
      const VNodeType& degArrVal, const VDouble& deg2ArrVal);
}
}

// ******************************************************
#endif // STAT_CORRELATION2
#endif // STAT_CORRELATION2_H
