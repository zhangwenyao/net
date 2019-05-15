#ifndef STATISTICS__RELATIVITY__RELATIVITY_H_
#define STATISTICS__RELATIVITY__RELATIVITY_H_
#include "../../network/net.h"
#ifdef STAT_RELATIVITY

namespace network {
namespace relativity {
  // ******************************************************
  int cal_relativity_lkk(double& relativity, const VVLinkType& lkk,
      const VNodeType& degArrVal, const LinkType& linkSize, const double alpha);
  int cal_relativity_lkk3(double& relativity, const VLkk3LinkType& lkk3,
      const VNodeType& degArrVal, const LinkType& linkSize, const double alpha);
  int cal_relativity_p2p(
      double& relativity, const VVNodeType& p2p, const LinkType linkSize, const double alpha);
  int cal_relativity_link(
      double& relativity, const VNodeType& link, const VNodeType& nodeDeg, const double alpha);
}
}

// ******************************************************
#endif // STAT_RELATIVITY
#endif // _H_
