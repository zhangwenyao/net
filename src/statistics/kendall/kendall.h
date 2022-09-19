#ifndef STATISTICS__KENDALL__KENDALL_H_
#define STATISTICS__KENDALL__KENDALL_H_
#include "../../network/net.h"
#ifdef STAT_KENDALL

namespace network {
namespace kendall {
  // ******************************************************
  int cal_kendall_lkk(double& tau, const VVLinkType& lkk,
      const LinkType linkSize, const int dir);
  int cal_kendall_lkkSum(double& tau, const VVLinkType& lkk,
      const VVLinkType& lkkSum, const int dir);
  int cal_kendall_p2p(double tau, const VVNodeType& p2p,
      const VNodeType& nodeDegOut, const VNodeType& nodeDegIn,
      const LinkType linkSize, const int dir);
}
}

// ******************************************************
#endif // STAT_KENDALL
#endif // STAT_KENDALL_H
