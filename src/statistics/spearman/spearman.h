#ifndef STATISTICS__SPEARMAN__SPEARMAN_H_
#define STATISTICS__SPEARMAN__SPEARMAN_H_
#include "../../network/net.h"
#ifdef STAT_SPEARMAN

namespace network {
namespace spearman {
  // ******************************************************
  int cal_lkkProb_gauss_sum(double& sum, VDouble& deg2ArrVal,
      VNodeType& degArrVal, VNodeType& degArrSize, const double s2,
      const NodeType xi, const double r);
  int cal_lkkProb_gaussS2(double& s2, VDouble& deg2ArrVal,
      VNodeType& degArrVal, VNodeType& degArrSize, const NodeType xi,
      const double r);
  int cal_lkkProb_gauss(VVDouble& lkkProb, const VDouble& s2,
      const VDouble& deg2ArrVal, const double r);

  int cal_lkkProb_expS2(double& s2, VDouble& deg2ArrVal, VNodeType& degArrVal,
      VNodeType& degArrSize, const LinkType linkSize, const NodeType xi,
      const double r);
  int cal_lkkProb_exp(VVDouble& lkkProb, const VDouble& s2,
      const VDouble& deg2ArrVal, const VNodeType& degArrVal, const double r);

  int cal_lkkProb_exp0S2(double& s2, VDouble& deg2ArrVal,
      VNodeType& degArrVal, VNodeType& degArrSize, const LinkType linkSize,
      const NodeType xi, const double r);
  int cal_lkkProb_exp0(VVDouble& lkkProb, const VDouble& s2,
      const VDouble& deg2ArrVal, const VNodeType& degArrVal, const double r);

  int cal_nodeNeiAveDeg2(VDouble& nodeNeiAveDeg2, const VVNodeType& p2p,
      const VDouble& deg2ArrVal, MNodeType& degArrNo);
  int cal_nodeNeiAveDeg2_nodeDeg(VDouble& nodeNeiAveDeg2,
      const VVNodeType& p2p, const VNodeType& nodeDeg,
      const VDouble& deg2ArrVal, MNodeType& degArrNo);
  int cal_nodeNeiAveDeg2_weight(VDouble& nodeNeiAveDeg2,
      const VVNodeType& p2p, const VNodeType& nodeDegIn,
      const VDouble& deg2ArrValIn, MNodeType& degArrNoIn,
      const VVWeightType& vvweight, const VWeightType& nodeWeightOut,
      const int weightFlag);
  int cal_neiAveDeg2(VDouble& neiAveDeg2, const VDouble& nodeNeiAveDeg2,
      const VNodeType& nodeDeg, const VNodeType& degArrSize,
      MNodeType& degArrNo, const VNodeType& degArrVal);
  int cal_neiAveDeg2_weight(VDouble& neiAveDeg2,
      const VDouble& nodeNeiAveDeg2, const VNodeType& nodeDeg,
      const VNodeType& degArrSize, MNodeType& degArrNo,
      const VNodeType& degArrVal, const VWeightSumType& degArrWeight,
      const VWeightType& nodeWeightOut, const int weightFlag);
  int cal_nodeNeiAveDeg2_AllAll(VDouble& nodeNeiAveDeg2,
      const VVNodeType& p2p, const VNodeType& nodeDeg,
      const VDouble& deg2ArrVal, MNodeType& degArrNo,
      const VVWeightType& vvweight, const VWeightType& nodeWeight,
      const int weightFlag);

  int cal_spearman_lkk(double& spearman, const VVLinkType& lkk,
      const VDouble& deg2ArrVal, const LinkType linkSize);
  int cal_spearman_lkk3(double& spearman, const VLkk3LinkType& lkk3,
      const VDouble& deg2ArrVal, const LinkType linkSize);
  int cal_spearman(double& spearman, const VVNodeType& p2p,
      const VDouble& deg2ArrVal, MNodeType& degArrNo,
      const LinkType linkSize);
  int cal_spearman_dir(double& spearman, double& rho, const VVNodeType& p2p,
      const double linkSize, const VNodeType& nodeDeg1, MNodeType& degArrNo1,
      const VDouble& deg2ArrVal1, const VNodeType& nodeDeg2,
      MNodeType& degArrNo2, const VDouble& deg2ArrVal2);
  int cal_spearman_dir_weight(double& spearman, double& rho,
      const VVNodeType& p2p, const VVWeightType& vvweight,
      const double netWeight, const VNodeType& nodeDeg1, MNodeType& degArrNo1,
      const VDouble& deg2ArrVal1, const VNodeType& nodeDeg2,
      MNodeType& degArrNo2, const VDouble& deg2ArrVal2, const int weightFlag);
  int cal_spearman_link(double& spearman, VNodeType& link,
      const VNodeType& nodeDeg, VDouble& deg2ArrVal, MNodeType& degArrNo);

  // ******************************************************
}
}
#endif // STAT_SPEARMAN
#endif // STAT_SPEARMAN_H
