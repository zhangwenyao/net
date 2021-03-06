#ifndef STATISTICS__PEARSON__PEARSON_H_
#define STATISTICS__PEARSON__PEARSON_H_
#include "../../network/net.h"
#ifdef STAT_PEARSON

namespace network {
namespace pearson {
  // ******************************************************
  int cal_nodeNeiAveDeg(VDouble& nodeNeiAveDeg,
      const VVNodeType& p2p); // 计算各点邻居平均度
  int cal_nodeNeiAveDeg_nodeDeg(VDouble& nodeNeiAveDeg, const VVNodeType& p2p,
      const VNodeType& nodeDegIn);
  int cal_nodeNeiAveDeg_weight(VDouble& nodeNeiAveDeg, const VVNodeType& p2p,
      const VNodeType& nodeDegIn, const VVWeightType& vvweight,
      const VWeightType& nodeWeightOut, const int weightFlag);
  int cal_nodeNeiAveDeg_AllAll_weight(VDouble& nodeNeiAveDeg,
      const VVNodeType& p2p, const VNodeType& nodeDeg,
      const VVWeightType& vvweight, const VWeightType& nodeWeight,
      const int weightFlag);
  int cal_neiAveDeg(VDouble& neiAveDeg, const VDouble& nodeNeiAveDeg,
      const VNodeType& nodeDeg, const VNodeType& degArrSize,
      MNodeType& degArrNo,
      const VNodeType& degArrVal); // 计算各度的邻居平均度
  int cal_neiAveDeg_weight(VDouble& neiAveDeg, const VDouble& nodeNeiAveDeg,
      const VNodeType& nodeDeg, const VNodeType& degArrSize,
      MNodeType& degArrNo, const VNodeType& degArrVal,
      const VWeightSumType& degArrWeight, const VWeightType& nodeWeight,
      const int weightFlag);

  int cal_nodeNeiAveNo(VDouble& nodeNeiAveNo, const VVNodeType& p2p);

  int cal_pearson_lkk(double& pearson, const VVLinkType& lkk,
      const VNodeType& degArrVal, const LinkType& linkSize);
  int cal_pearson_lkk3(double& pearson, const VLkk3LinkType& lkk3,
      const VNodeType& degArrVal, const LinkType& linkSize);
  int cal_pearson(
      double& pearson, const VVNodeType& p2p, const LinkType linkSize);
  int cal_pearson_dir(double& pearson, double& rho, const VVNodeType& p2p,
      const LinkType linkSize, const VNodeType& nodeDegOut,
      const VNodeType& nodeDegIn);
  int cal_pearson_dir_weight(double& pearson, double& rho,
      const VVNodeType& p2p, const VVWeightType& vvweight,
      const WeightSumType netWeight, const VNodeType& nodeDegOut,
      const VNodeType& nodeDegIn, const int weightFlag);
  int cal_pearson_link(
      double& pearson, const VNodeType& link, const VNodeType& nodeDeg);

  int cal_No(double& No, const VVNodeType& p2p, const LinkType linkSize);
  int cal_No_link(double& No, const VNodeType& link);
}
}

// ******************************************************
#endif // STAT_PEARSON
#endif // STAT_PEARSON_H
